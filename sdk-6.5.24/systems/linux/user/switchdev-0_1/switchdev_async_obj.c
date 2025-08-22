#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/queue.h>

#include <net/if.h>
#include <arpa/inet.h>

#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <fcntl.h>
#include <linux/netdevice.h>
#include <linux/if_bridge.h>
#include <pthread.h>

#ifndef NO_SAL_APPL
#include <sal/appl/sal.h>
#include <sal/appl/config.h>
#include <appl/diag/bslmgmt.h>
#include <appl/diag/opennsa_diag.h>
#endif

#include <bcm/init.h>
#include <bcm/error.h>
#include <soc/cmext.h>
#include <soc/opensoc.h>
#include <sal/core/boot.h>
#include <linux-bde.h>

#ifdef BCM_WARM_BOOT_SUPPORT
#include <bcm/switch.h>
#endif

/*
 * These includes are needed for do_per_switch_setup() part of the demo.
 */
#include <bcm/port.h>
#include <bcm/stg.h>

#if defined(BCM_LTSW_SUPPORT)
#include <appl/diag/sysconf_ltsw.h>
#endif

#include <opennsa/link.h>
#include <opennsa/l3.h>

#include "switchdev_async_obj.h"



/*
 * base async object
 */

int async_object_create(async_object_t *obj)
{
    switch_service_t  *sys = NULL;

    //put obj into download list, which will be used by obj download thread

    if (!(sys = system_get_instance()))
        return -1;
   
    if(!obj) {
        return -1;
    }

    pthread_mutex_lock(&obj->lock);

    switch(obj->state) {
        case ASYNC_OBJ_STATE_NEW:
            obj->state = ASYNC_OBJ_STATE_IDLE;
            break;
        case ASYNC_OBJ_STATE_IDLE:
        case ASYNC_OBJ_STATE_PENDING:
        case ASYNC_OBJ_STATE_ACTIVE:
            break;
        case ASYNC_OBJ_STATE_FAILED:
            obj->state = ASYNC_OBJ_STATE_IDLE;
            break;
        case ASYNC_OBJ_STATE_DELETING:
            obj->state = ASYNC_OBJ_STATE_ACTIVE;
        default:
            break;
    }

    pthread_mutex_unlock(&obj->lock);

    return 0;
}


static void async_object_free(async_object_t **obj)
{
    async_obj_entry_t      *entry = NULL;

    if (obj == NULL)
        return;

    entry = container_of(obj, struct async_obj_entry_s, obj);

    LIST_REMOVE(entry, system_next);

    entry->obj = NULL;

    if (!(*obj)) {
        free(*obj);
    }
    free(entry);

    return;

}

async_object_t** async_object_find(async_object_t *obj)
{
    switch_service_t   *sys   = NULL;
    async_obj_entry_t  *entry = NULL;

    if ((sys = system_get_instance()) == NULL)
        return NULL;

    LIST_FOREACH(entry, &(sys->object_db), system_next) {
       if(entry->obj == obj) {
           return &(entry->obj);
       }
    }

    return NULL;
}

static void async_object_find_and_free(async_object_t *obj)
{
     async_object_t **objp = NULL;

     objp = async_object_find(obj);

     if(objp) {
         async_object_free(objp);
     }
     return;
}

int async_object_delete(async_object_t **obj)
{
    async_obj_entry_t *entry = NULL;
    switch_service_t  *sys = NULL;

    //put obj into download list, which will be used by obj download thread

    if (!(sys = system_get_instance()))
        return -1;
   
    if(!obj || !*obj) {
        return -1;
    }

    //printf("async_object_delete type %d state %d\n", (*obj)->type, (*obj)->state); 

    switch((*obj)->state) {
        case ASYNC_OBJ_STATE_NEW:
        case ASYNC_OBJ_STATE_IDLE:
        case ASYNC_OBJ_STATE_PENDING:
        case ASYNC_OBJ_STATE_FAILED:
            //should not exist in work queue (sys->object_list)
            async_object_free(obj);
            break;

        case ASYNC_OBJ_STATE_ACTIVE:
            (*obj)->state = ASYNC_OBJ_STATE_DELETING;
            //add to work queue (sys->object_list)
            entry = (async_obj_entry_t *)malloc(sizeof(async_obj_entry_t));
            if (!entry) {
                //printf("async_object_download malloc failed\n");
                break;
            }

            entry->obj = *obj;

            pthread_mutex_lock(&(sys->object_lock));
            LIST_INSERT_HEAD(&(sys->object_list), entry, system_next);
            pthread_mutex_unlock(&(sys->object_lock));

            pthread_cond_signal(&sys->object_cond);
            break;
        case ASYNC_OBJ_STATE_DELETING:
            //should already inserted into work queue (sys->object_list)
            break;
        default:
            break;
    }


    return 0;
}


int async_object_download(async_object_t *obj)
{
    async_obj_entry_t *entry = NULL;
    switch_service_t  *sys = NULL;

    //put obj into download list, which will be used by obj download thread

    if (!(sys = system_get_instance()))
        return -1;
   
    if(!obj) {
        return -1;
    }

    //printf("async_object_download  type %d state %d\n", obj->type, obj->state);

    switch(obj->state) {
        case ASYNC_OBJ_STATE_IDLE:
            obj->state = ASYNC_OBJ_STATE_PENDING;
            break;
        case ASYNC_OBJ_STATE_PENDING:
            //could be triggered again by parent
            break;

        case ASYNC_OBJ_STATE_NEW:
        case ASYNC_OBJ_STATE_FAILED:
        case ASYNC_OBJ_STATE_ACTIVE:
            //should not handle object_download at these states
            return -1;
        case ASYNC_OBJ_STATE_DELETING:
            //could be triggered again by child
            break;
        default:
            break;

    }

    entry = (async_obj_entry_t *)malloc(sizeof(async_obj_entry_t));
    if (!entry) {
        //printf("async_object_download malloc failed\n");
        return -1;
    }

    entry->obj = obj;

    //printf("async_object_download obj %p \n", obj);

    pthread_mutex_lock(&(sys->object_lock));
    LIST_INSERT_HEAD(&(sys->object_list), entry, system_next);
    pthread_mutex_unlock(&(sys->object_lock));

    pthread_cond_signal(&sys->object_cond);
    return 0;
}

int async_object_add_parent(async_object_t *obj, async_object_t *parent)
{
    async_obj_entry_t *entry = NULL, *entry_p = NULL;
    switch_service_t  *sys = NULL;
    int                rc = 0;

    if (!(sys = system_get_instance())) {
        return 0;
    }

    if(!obj || !parent) {
        return -1;
    }

    //printf("async_object_add_parent...\n");

    //only allowed if obj->state is ASYNC_OBJ_STATE_IDLE or NEW
    if (obj->state != ASYNC_OBJ_STATE_IDLE &&
        obj->state != ASYNC_OBJ_STATE_NEW) {
        //printf("async_object_add_parent obj %p state %d not allowed\n", obj, obj->state); 
        return -1;
    }

    entry = (async_obj_entry_t *)malloc(sizeof(async_obj_entry_t));
    if (!entry) {
        //printf("async_object_add_parent malloc failed\n");
        return -1;
    }

    entry_p = (async_obj_entry_t *)malloc(sizeof(async_obj_entry_t));
    if (!entry_p) {
        printf("async_object_add_parent malloc failed\n");
        free(entry);
        return -1;
    }    

    //update parent's child list
    memset(entry, 0, sizeof(async_obj_entry_t));
    entry->obj = obj;
    pthread_mutex_lock(&(parent->lock));
    LIST_INSERT_HEAD(&(parent->child_list), entry, system_next);
    pthread_mutex_unlock(&(parent->lock));

    //update self's parent list
    memset(entry_p, 0, sizeof(async_obj_entry_t));
    entry_p->obj = parent;
    pthread_mutex_lock(&(obj->lock));
    LIST_INSERT_HEAD(&(obj->parent_list), entry_p, system_next);
    pthread_mutex_unlock(&(obj->lock));

    //if parent is not in download list, add parent to download list
    pthread_mutex_lock(&(parent->lock));
    if (parent->state == ASYNC_OBJ_STATE_IDLE) {
        //printf("async_object_add_parent trigger parent download\n");
        rc = async_object_download(parent);
        if (rc) {
            printf("async_object_add_parent object download failed rc = %d\n", rc);
        } else {
            parent->state = ASYNC_OBJ_STATE_PENDING;
        }
    }
    pthread_mutex_unlock(&(parent->lock));

    return 0;
}



/*
 * neigh async object
 */

async_obj_neigh_t** async_obj_neigh_find(ip_address_t *nh)
{
    switch_service_t  *sys   = NULL;
    async_obj_entry_t *entry = NULL;
    async_obj_neigh_t *obj   = NULL;

    if ((sys = system_get_instance()) == NULL)
        return NULL;

    LIST_FOREACH(entry, &sys->object_db, system_next)
    {
        obj = (async_obj_neigh_t *)entry->obj;
        if (obj) {
            if (memcmp(&(obj->nh), nh, sizeof(ip_address_t)) == 0)
                return (async_obj_neigh_t**)&(entry->obj);
        }
    }

    return NULL;
}


int async_obj_neigh_create_cb(struct async_object_s *obj)
{
    async_obj_neigh_t *neigh = (async_obj_neigh_t *)obj;
    bcm_l3_egress_t    egress_object;
    int                object_id = -1;
    int                rc        = 0;

    //printf("async_obj_neigh_create_cb enter\n");

    if (!neigh) {
        return -1;
    }

    if (!neigh->local_if) {
        printf("async_obj_neigh_create_cb local_if NULL\n");
        return -1;
    }
    
    //TODO if object_id exist, do not need to program ASIC


    bcm_l3_egress_t_init(&egress_object);
    egress_object.intf = neigh->local_if->l3_intf;
    egress_object.port = neigh->local_if->hw_port;
    egress_object.vlan = neigh->local_if->vlan;      //should always be 4095
    memcpy(egress_object.mac_addr, neigh->mac_addr, ETHER_ADDR_LEN);

    // create l3 egress
    rc = bcm_l3_egress_create(0, 0, &egress_object, &object_id);    
    if (BCM_FAILURE(rc)) {
        printf("async_obj_neigh_create_cb l3_egress create failed %d\n", rc);
    } 
    neigh->object_id = object_id;

    return rc;
}

int async_obj_neigh_update_cb(struct async_object_s *obj)
{
    return 0;
}

int async_obj_neigh_delete_cb(struct async_object_s *obj)
{
    async_obj_neigh_t *neigh = (async_obj_neigh_t *)obj;
    int                rc    = 0;

    if (!neigh) {
        return -1;
    }
    
    if (neigh->object_id == -1) {
        return 0;
    }
    rc = bcm_l3_egress_destroy(0, neigh->object_id);
    if (BCM_FAILURE(rc)) {
        printf("async_obj_neigh_delete_cb l3_egress delete failed %d\n", rc);
    } 
    return rc;
}


async_obj_neigh_t** async_obj_neigh_find_or_new(ip_address_t *nh)
{
    switch_service_t   *sys   = NULL;
    async_obj_entry_t  *neigh = NULL;
    async_obj_neigh_t  *obj   = NULL;
    async_obj_neigh_t **objp  = NULL;

    if (!(sys = system_get_instance()))
        return NULL;
   
    if ((objp = async_obj_neigh_find(nh)))
        return objp;

    if (!(neigh = (async_obj_entry_t*)malloc(sizeof(async_obj_entry_t))))
    {
        printf("neigh entry malloc failed nh 0x%x \n",  nh->ip[0]);
        return NULL;
    }

    if (!(obj = (async_obj_neigh_t*)malloc(sizeof(async_obj_neigh_t))))
    {
        free(neigh);
        printf("neigh object malloc failed nh 0x%x \n",  nh->ip[0]);
        return NULL;
    }

    //printf("async_obj_neigh_find_or_new new obj for 0x%x\n", nh->ip[0]);

    memset(neigh, 0, sizeof(async_obj_entry_t));
    neigh->obj = (async_object_t *)obj;

    memset(obj, 0, sizeof(async_obj_neigh_t));
    //initialize object base
    obj->state      = ASYNC_OBJ_STATE_NEW;
    obj->type       = ASYNC_OBJ_TYPE_NEIGH;
    pthread_mutex_init(&obj->lock, NULL);
    LIST_INIT(&(obj->parent_list));
    LIST_INIT(&(obj->child_list));

    obj->object_create     = async_object_create;    
    obj->object_delete     = async_object_delete;
    obj->object_download   = async_object_download;
    obj->object_add_parent = async_object_add_parent;

    obj->object_create_cb  = async_obj_neigh_create_cb;
    obj->object_update_cb  = async_obj_neigh_update_cb;
    obj->object_delete_cb  = async_obj_neigh_delete_cb;

    //initialize object specific
    obj->object_id  = -1;
    memcpy(&obj->nh, nh, sizeof(ip_address_t));

    LIST_INSERT_HEAD(&sys->object_db, neigh, system_next);

    return (async_obj_neigh_t**)&(neigh->obj);
}



/*
 * fib async object
 */

async_obj_fib_t** async_obj_fib_find(int ifindex, ip_address_t *nh, ip_address_t *dst, int dst_len)
{
    switch_service_t   *sys   = NULL;
    async_obj_entry_t  *entry = NULL;
    async_obj_fib_t    *obj   = NULL;

    if ((sys = system_get_instance()) == NULL)
        return NULL;

    LIST_FOREACH(entry, &(sys->object_db), system_next)
    {
        if (entry->obj && (entry->obj->type == ASYNC_OBJ_TYPE_FIB)) {
            obj = (async_obj_fib_t *)entry->obj;
            if ((obj->ifindex == ifindex) &&
                (memcmp(&obj->nh, nh, sizeof(ip_address_t)) == 0)&&
                (memcmp(&obj->dst, dst, sizeof(ip_address_t)) == 0) &&
                (obj->dst_len == dst_len)) {
                return (async_obj_fib_t**)&(entry->obj);
            }
        }
    }

    return NULL;
}


static void ipv6_create_mask(uint8 *ip6_mask, uint32 prefix_length) {
    int i;

    for (i=15; i>=0; i--) {
        if (i < prefix_length/8) {
            ip6_mask[i] = 0xFF;
        } else if (i == prefix_length/8) {
            ip6_mask[i] = 0xFF - ((1 << (8 -(prefix_length % 8))) - 1);
        } else {
            ip6_mask[i] = 0X00;
        }
    }
}

int async_obj_fib_create_cb(struct async_object_s *obj)
{
    async_obj_fib_t   *fib = (async_obj_fib_t *)obj;
    async_obj_entry_t *entry = NULL;
    async_obj_neigh_t *neigh = NULL;
    bcm_l3_route_t     route_info;
    int                rc    = 0;

    if (!fib) {
        return -1;
    }

    LIST_FOREACH(entry, &(fib->parent_list), system_next)
    {
        if(entry->obj->type == ASYNC_OBJ_TYPE_NEIGH) {
            neigh = (async_obj_neigh_t *)entry->obj;
            break;
        }
    }
    if (!neigh) {
        //should not happen
        printf("async_obj_fib_create_cb neigh parent not found\n");
        return -1;
    }

    //TODO if object_id exist, do not need to program ASIC

    bcm_l3_route_t_init(&route_info);

    if (fib->dst.protocol == AF_INET) {
        route_info.l3a_subnet  = ntohl(fib->dst.ip[0]);
        route_info.l3a_ip_mask = (0xFFFFFFFF << (32 - fib->dst_len)) & 0xFFFFFFFF;
    } else {
        route_info.l3a_flags = BCM_L3_IP6;
        memcpy(route_info.l3a_ip6_net, fib->dst.ip, 16);
        ipv6_create_mask(route_info.l3a_ip6_mask, fib->dst_len);
    } 
    route_info.l3a_intf = neigh->object_id;
    rc = bcm_l3_route_add(0, &route_info);
    if (BCM_FAILURE(rc)) {
        printf("async_obj_fib_create_cb l3 route create failed: %s\n", bcm_errmsg(rc));
    }

    return rc;
}

int async_obj_fib_update_cb(struct async_object_s *obj)
{
    return 0;
}

int async_obj_fib_delete_cb(struct async_object_s *obj)
{
    async_obj_fib_t *fib = (async_obj_fib_t *)obj;
    bcm_l3_route_t   route_info;
    int              rc = 0;

    if (!fib) {
        return -1;
    }
    
    if (!LIST_EMPTY(&fib->child_list)) {
        //should not happen
        printf("async_obj_fib_delete_cb fib child not empty\n");
        return -1;
    }

    bcm_l3_route_t_init(&route_info);
    route_info.l3a_subnet  = ntohl(fib->dst.ip[0]);
    route_info.l3a_ip_mask = (0xFFFFFFFF << (32 - fib->dst_len)) & 0xFFFFFFFF;
    rc = bcm_l3_route_delete(0, &route_info);

    if (BCM_FAILURE(rc)) {
        printf("async_obj_fib_delete_cb l3_egress delete failed %d\n", rc);
    } 
    return rc;
}


async_obj_fib_t** async_obj_fib_find_or_new(int ifindex, ip_address_t *nh, ip_address_t *dst, int dst_len)
{
    switch_service_t   *sys   = NULL;
    async_obj_entry_t  *fib   = NULL;
    async_obj_fib_t    *obj   = NULL;
    async_obj_fib_t   **objp  = NULL;

    if (!(sys = system_get_instance()))
        return NULL;
   
    if ((objp = async_obj_fib_find(ifindex, nh, dst, dst_len)))
        return objp;

    if (!(fib = (async_obj_entry_t*)malloc(sizeof(async_obj_entry_t))))
    {
        printf("fib entry malloc failed ifindex %d ipv4 0x%x/%d nh 0x%x ", 
               ifindex, dst->ip[0], dst_len, nh->ip[0]);
        return NULL;
    }

    if (!(obj = (async_obj_fib_t*)malloc(sizeof(async_obj_fib_t))))
    {
        free(fib);
        printf("fib object malloc failedifindex %d ipv4 0x%x/%d nh 0x%x ", 
               ifindex, dst->ip[0], dst_len, nh->ip[0]);
        return NULL;
    }

    //printf("async_obj_fib_find_or_new new obj ifindex %d ip 0x%x/%d nh 0x%x\n",
    //       ifindex, dst->ip[0], dst_len, nh->ip[0]);

    memset(fib, 0, sizeof(async_obj_entry_t));
    fib->obj = (async_object_t *)obj;

    memset(obj, 0, sizeof(async_obj_fib_t));
    //initialize object base
    obj->state      = ASYNC_OBJ_STATE_NEW;
    obj->type       = ASYNC_OBJ_TYPE_FIB;
    pthread_mutex_init(&obj->lock, NULL);
    LIST_INIT(&(obj->parent_list));
    LIST_INIT(&(obj->child_list));

    obj->object_create     = async_object_create;    
    obj->object_delete     = async_object_delete;    
    obj->object_download   = async_object_download;
    obj->object_add_parent = async_object_add_parent;

    obj->object_create_cb  = async_obj_fib_create_cb;
    obj->object_update_cb  = async_obj_fib_update_cb;
    obj->object_delete_cb  = async_obj_fib_delete_cb;

    //initialize object specific
    obj->ifindex    = ifindex;
    obj->dst_len    = dst_len;
    memcpy(&obj->nh, nh, sizeof(ip_address_t));
    memcpy(&obj->dst, dst, sizeof(ip_address_t));
    
    LIST_INSERT_HEAD(&sys->object_db, fib, system_next);

    return (async_obj_fib_t**)&(fib->obj);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////

//TASK handling object download
int process_async_object(async_obj_entry_t *entry) 
{
    async_object_t     *obj    = NULL;
    async_obj_entry_t  *parent = NULL, *child = NULL;
    switch_service_t   *sys    = NULL;
    int                 rc     = 0;

    obj = entry->obj;

    if(!obj) {
        return -1;
    }

    sys = system_get_instance();
    if(!sys) {
        return -1;
    }

    //printf("process_async_object obj %p type %d state %d\n", obj, obj->type, obj->state);

    switch(obj->state) {
        case ASYNC_OBJ_STATE_NEW:
        case ASYNC_OBJ_STATE_IDLE:
        case ASYNC_OBJ_STATE_FAILED:
        case ASYNC_OBJ_STATE_ACTIVE:
            //need to remove from work queue
            entry->obj = NULL;
            free(entry);
            break;

        case ASYNC_OBJ_STATE_PENDING:  
            // check parents, make sure all parents are ACTIVE
            LIST_FOREACH(parent, &(obj->parent_list), system_next) {
                if (!parent->obj) {
                    //should not happen, ignore this parent
                    continue;
                }
                if(parent->obj->state != ASYNC_OBJ_STATE_ACTIVE) {
                    //printf("process_async_object parent %p state %d\n", parent->obj, parent->obj->state);
                    //remove from workqueue, will be add back to workqueue if child download success 
                    entry->obj = NULL;
                    free(entry);
                    return -1;              
                }
            }
            
            rc = obj->object_create_cb(obj);
            if (rc) {
                obj->state = ASYNC_OBJ_STATE_FAILED;
            } else {
                obj->state = ASYNC_OBJ_STATE_ACTIVE;
            }
            //printf("process_async_object obj %p state %d  create_cb rc %d\n", obj, obj->state, rc);

            //check if there is child waiting for download, put them into work queue
            LIST_FOREACH(child, &(obj->child_list), system_next) {
               if (!child->obj) {
                   //should not happen, ignore
                   continue;
               }

               if (child->obj->state == ASYNC_OBJ_STATE_PENDING) {
                   child->obj->object_download(child->obj);
               }
            }

            //free workqueue item
            entry->obj = NULL;
            free(entry);
            break;
        case ASYNC_OBJ_STATE_DELETING:
            // check childs, make sure child is empty
            if (!LIST_EMPTY(&obj->child_list)) {
                //remove from workqueue, will be add back if parent delete success
                //printf("process_async_object %p child not NULL, skip\n", obj);
                entry->obj = NULL;
                free(entry);
                return -1;              
            }
                 
            obj->object_delete_cb(obj);

            //update parent's child list
            LIST_FOREACH(parent, &(obj->parent_list), system_next) {
                if (!parent->obj) {
                    continue;
                }
                if (!LIST_EMPTY(&(parent->obj->child_list))) {
                    async_obj_entry_t *found = NULL;

                    pthread_mutex_lock(&(parent->obj->lock));
                    LIST_FOREACH(child, &(parent->obj->child_list), system_next) {
                        if (child->obj == obj) {
                            found = child;
                            break;
                        }
                    }
                    if (found) {
                         LIST_REMOVE(found, system_next);
                         found->obj = NULL;
                         free(found);
                    }

                    pthread_mutex_unlock(&(parent->obj->lock));
                }
                //check if there is parent waiting for delete, put them into workqueue
                if(parent->obj->state == ASYNC_OBJ_STATE_DELETING) {
                    parent->obj->object_download(parent->obj);
                }
            }

            //delete is always successful
            //remove from object db
            async_object_find_and_free(obj);

            //remove workqueue item
            entry->obj = NULL;
            free(entry);

            break;
            
        default:
            break;
    }

    return 0;
}

int switchdev_async_obj_main(switch_service_t *sys)
{
    async_obj_entry_t *entry = NULL;
    async_object_t    *obj   = NULL;

    if (!sys) {
        return 0;
    } 

    while(1) {
        pthread_mutex_lock(&sys->object_lock);
        while (LIST_EMPTY(&sys->object_list)) {
            pthread_cond_wait(&sys->object_cond, &sys->object_lock);
        }

        entry = LIST_FIRST(&sys->object_list);

        LIST_REMOVE(entry, system_next);

        pthread_mutex_unlock(&sys->object_lock);

        obj = entry->obj;

        if(!obj) {
            free(entry);
            continue;
        }

        process_async_object(entry);
    }

    return 0;
}


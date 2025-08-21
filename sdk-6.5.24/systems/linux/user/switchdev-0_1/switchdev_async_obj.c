#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/queue.h>

#include <net/if.h>

#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <fcntl.h>
#include <linux/netdevice.h>
#include <linux/if_bridge.h>

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
    async_obj_entry_t *entry = NULL;
    switch_service_t  *sys = NULL;

    //put obj into download list, which will be used by obj download thread

    if (!(sys = system_get_instance()))
        return NULL;
   
    if(!obj) {
        return -1;
    }

    pthread_mutex_lock(&obj->lock);

    switch(obj->state) {
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


static void async_object_free(async_object_t *obj)
{
    if(!obj) {
        return;
    }

    switch(obj->type) {
        case ASYNC_OBJ_TYPE_NEIGH:
            async_obj_neigh_free(obj);
            break;
        case ASYNC_OBJ_TYPE_FIB:
            async_obj_fib_free(obj);
            break;
        default:
            break;
    }

    return;
}

int async_object_delete(async_object_t *obj)
{
    async_obj_entry_t *entry = NULL;
    switch_service_t  *sys = NULL;

    //put obj into download list, which will be used by obj download thread

    if (!(sys = system_get_instance()))
        return NULL;
   
    if(!obj) {
        return -1;
    }

    switch(obj->state) {
        case ASYNC_OBJ_STATE_IDLE:
        case ASYNC_OBJ_STATE_PENDING:
        case ASYNC_OBJ_STATE_FAILED:
            //should not exist in work queue (sys->object_list)
            async_object_free(obj);
            break;

        case ASYNC_OBJ_STATE_ACTIVE:
            obj->state = ASYNC_OBJ_STATE_DELETING;
            //add to work queue (sys->object_list)
            entry = (async_obj_entry_t *)malloc(sizeof(async_obj_entry_t));
            if (!entry) {
                printf("async_object_download malloc failed\n");
                break;
            }

            entry->obj = obj;

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
        return NULL;
   
    if(!obj) {
        return -1;
    }

    switch(obj->state) {
        case ASYNC_OBJ_STATE_IDLE:
            obj->state = ASYNC_OBJ_STATE_PENDING;
            break;
        
        case ASYNC_OBJ_STATE_PENDING:
        case ASYNC_OBJ_STATE_FAILED:
        case ASYNC_OBJ_STATE_ACTIVE:
        case ASYNC_OBJ_STATE_DELETING:
            //should not handle object_download at these states
            return;
        default:
            break;

    }

    entry = (async_obj_entry_t *)malloc(sizeof(async_obj_entry_t));
    if (!entry) {
        printf("async_object_download malloc failed\n");
        return -1;
    }

    entry->obj = obj;

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
        return NULL;
    }

    if(!obj || !parent) {
        return -1;
    }

    //only allowed if obj->state is ASYNC_OBJ_STATE_IDLE
    if (obj->state != ASYNC_OBJ_STATE_IDLE) {
        return -1;
    }

    entry = (async_obj_entry_t *)malloc(sizeof(async_obj_entry_t));
    if (!entry) {
        printf("async_object_add_parent malloc failed\n");
        return -1;
    }

    entry_p = (async_obj_entry_t *)malloc(sizeof(async_obj_entry_t));
    if (!entry_p) {
        printf("async_object_add_parent malloc failed\n");
        free(entry);
        return -1;
    }    

    //update parent's sibling list
    entry->obj = obj;
    pthread_mutex_lock(&(parent->lock));
    LIST_INSERT_HEAD(&(parent->sibling_list), entry, system_next);
    pthread_mutex_unlock(&(parent->lock));

    //update self's parent list
    entry_p->obj = parent;
    pthread_mutex_lock(&(obj->lock));
    LIST_INSERT_HEAD(&(obj->parent_list), entry, system_next);
    pthread_mutex_unlock(&(obj->lock));

    //if parent is not in download list, add parent to download list
    pthread_mutex_lock(&(parent->lock));
    if (parent->state != ASYNC_OBJ_STATE_PENDING) {
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

async_obj_t* async_obj_neigh_find(ip_address_t *nh)
{
    switch_service_t  *sys   = NULL;
    neigh_entry_t     *neigh = NULL;
    async_obj_neigh_t *obj = NULL;

    if ((sys = system_get_instance()) == NULL)
        return NULL;

    LIST_FOREACH(neigh, &sys->neigh_list, system_next)
    {
        obj = neigh->obj;
        if (obj) {
            if (memcmp(&(obj->nh), nh, sizeof(ip_address_t)) == 0)
                return obj;
        }
    }

    return NULL;
}

void async_obj_neigh_free(async_obj_neigh_t *obj)
{
    neigh_entry_t      *neigh = NULL;

    if (obj == NULL)
        return;

    neigh = container_of(obj, neigh_entry_t, obj);

    LIST_REMOVE(neigh, system_next);

    free(obj);
    free(neigh);

    return;
}




int async_obj_neigh_create_cb(struct async_object_s *obj)
{
    async_obj_neigh_t *neigh = (async_obj_neigh_t *)obj;
    bcm_l3_egress_t    egress_object;
    int                object_id = -1;

    printf("async_obj_neigh_create_cb enter\n");

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


async_obj_neigh_t* async_obj_neigh_create(ip_address_t *nh)
{
    switch_service_t   *sys   = NULL;
    neigh_entry_t      *neigh = NULL;
    async_obj_neigh_t  *obj   = NULL;

    if (!(sys = system_get_instance()))
        return NULL;
   
    if ((obj = async_obj_neigh_find(nh)))
        return obj;

    if (!(neigh = (neigh_entry_t*)malloc(sizeof(neigh_entry_t))))
    {
        printf("neigh entry malloc failed nh 0x%x \n",  nh->ip[0]);
        return NULL;
    }

    if (!(obj = (async_obj_neigh_t*)malloc(sizeof(async_obj_neigh_t))))
    {
        free(neigh)
        printf("neigh object malloc failed nh 0x%x \n",  nh->ip[0]);
        return NULL;
    }

    memset(neigh, 0, sizeof(neigh_entry_t));
    neigh->obj = obj;

    memset(obj, 0, sizeof(async_obj_neigh_t));
    //initialize object base
    obj->state      = ASYNC_OBJ_STATE_IDLE;
    obj->type       = ASYNC_OBJ_TYPE_NEIGH;
    pthread_mutex_init(&obj->lock, NULL);
    LIST_INIT(&(obj->parent_list));
    LIST_INIT(&(obj->sibling_list));

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

    LIST_INSERT_HEAD(&sys->neigh_list, neigh, system_next);

    return obj;
}



/*
 * fib async object
 */

async_obj_t* async_obj_fib_find(int ifindex, ip_address_t *nh, ip_address_t *dst, int dst_len)
{
    switch_service_t *sys = NULL;
    fib_entry_t      *fib = NULL;
    async_obj_fib_t  *obj = NULL;

    if ((sys = system_get_instance()) == NULL)
        return NULL;

    LIST_FOREACH(fib, &(sys->fib_list), system_next)
    {
        obj = fib->obj;
        if (obj) {
            if ((obj->ifindex == ifindex) &&
                (memcmp(&obj->nh, nh, sizeof(ip_address_t)) == 0)&&
                (memcmp(&obj->dst,dst, sizeof(ip_address_t)) == 0) &&
                (obj->dst_len == dst_len)) {
                return obj;
            }
        }
    }

    return NULL;
}

void async_obj_fib_free(async_obj_fib_t *obj)
{
    fib_entry_t      *fib = NULL;

    if (obj == NULL)
        return;

    fib = container_of(obj, fib_entry_t, obj);

    if (fib == NULL)
        return;

    LIST_REMOVE(fib, system_next);

    free(obj);
    free(fib);

    return;
}


static void ipv6_create_mask(bcm_ip6_t *ip6_mask, uint32 prefix_length) {
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
    int                object_id = -1;

    if (!fib) {
        return -1;
    }

    if (!fib->local_if) {
        return -1;
    }
    
    LIST_FOREACH(entry, &fib->parent_list, system_next)
    {
        if(entry->obj->type == ASYNC_OBJ_NEIGH) {
            neigh = entry->obj;
            break;
        }
    }
    if (!neigh) {
        //should not happen
        print("async_obj_fib_create_cb neigh parent not found\n");
        return -1;
    }

    //TODO if object_id exist, do not need to program ASIC

    bcm_l3_route_t_init(&route_info);

    if (fib->ip_dst.protocol == AF_INET) {
        route_info.l3a_subnet  = ntohl(fib->ip_dst.ip[0]);
        route_info.l3a_ip_mask = (0xFFFFFFFF << (32 - fib->dst_len)) & 0xFFFFFFFF;
    } else {
        route_info.l3a_flags = BCM_L3_IP6;
        memcpy(route_info.l3a_ip6_net, fib->ip_dst.ip, 16);
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

    if (!fib) {
        return -1;
    }
    
    if (!LIST_EMPTY(&fib->sibling_list)) {
        //should not happen
        print("async_obj_fib_delete_cb fib sibling not empty\n");
        return -1;
    }

    bcm_l3_route_t_init(&route_info);
    route_info.l3a_subnet  = ntohl(fib->ip_dst.ip[0]);
    route_info.l3a_ip_mask = (0xFFFFFFFF << (32 - fib->dst_len)) & 0xFFFFFFFF;
    rc = bcm_l3_route_delete(0, &route_info);

    if (BCM_FAILURE(rc)) {
        printf("async_obj_fib_delete_cb l3_egress delete failed %d\n", rc);
    } 
    return rc;
}


async_obj_fib_t* async_obj_fib_create(int ifindex, ip_address_t *nh, ip_address_t *dst, int dst_len)
{
    switch_service_t   *sys   = NULL;
    fib_entry_t        *fib   = NULL;
    async_obj_fib_t    *obj   = NULL;

    if (!(sys = system_get_instance()))
        return NULL;
   
    if ((obj = async_obj_fib_find(ifindex, nh, dst, dst_len)))
        return obj;

    if (!(fib = (fib_entry_t*)malloc(sizeof(fib_entry_t))))
    {
        printf("fib entry malloc failed ifindex %d ipv4 0x%x/%d nh 0x%x ", 
               ifindex, dst->ip[0], dst_len, nh->ip[0]);
        return NULL;
    }

    if (!(obj = (async_obj_neigh_t*)malloc(sizeof(async_obj_neigh_t))))
    {
        free(fib);
        printf("fib object malloc failedifindex %d ipv4 0x%x/%d nh 0x%x ", 
               ifindex, dst->ip[0], dst_len, nh->ip[0]);
        return NULL;
    }

    memset(fib, 0, sizeof(fib_entry_t));
    fib->obj = obj;

    memset(obj, 0, sizeof(async_obj_fib_t));
    //initialize object base
    obj->state      = ASYNC_OBJ_STATE_IDLE;
    obj->type       = ASYNC_OBJ_TYPE_FIB;
    pthread_mutex_init(&obj->lock, NULL);
    LIST_INIT(&(obj->parent_list));
    LIST_INIT(&(obj->sibling_list));

    obj->object_create     = async_object_create;    
    obj->object_delete     = async_object_delete;    
    obj->object_download   = async_object_download;
    obj->object_add_parent = async_object_add_parent;

    obj->object_create_cb  = async_obj_fib_create_cb;
    obj->object_update_cb  = async_obj_fib_update_cb;
    obj->object_delete_cb  = async_obj_fib_delete_cb;

    //initialize object specific
    obj->object_id  = -1;
    obj->ifindex    = ifindex;
    obj->dst_len    = dst_len;
    memcpy(&obj->nh, nh, sizeof(ip_address_t));
    memcpy(&obj->dst, dst, sizeof(ip_address_t));
    
    LIST_INSERT_HEAD(&sys->fib_list, fib, system_next);

    return obj;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////

//TASK handling object download
int process_async_object(async_obj_entry_t *entry) 
{
    async_object_t     *obj    = NULL;
    async_obj_entry_t  *parent = NULL, *sibling = NULL;

    obj = entry->obj;

    if(!obj) {
        return -1;
    }

    switch(obj->state) {
        case ASYNC_OBJ_STATE_IDLE:
        case ASYNC_OBJ_STATE_FAILED:
        case ASYNC_OBJ_STATE_ACTIVE:
            //need to remove from work queue
            entry->obj = NULL;
            free(entry);
            break;

        case ASYNC_OBJ_STATE_PENDING:  
            // check parents, make sure all parents are ACTIVE
            LIST_FOREACH(parent, obj->parent_list, system_next) {
                if (!parent->obj) {
                    //should not happen, ignore this parent
                    continue;
                }
                if(parent->obj->state != ASYNC_OBJ_STATE_ACTIVE) {
                    //keep in PENDING state, put back into work queue
                    pthread_mutex_lock(&(sys->object_lock));
                    LIST_INSERT_HEAD(&(sys->object_list), entry, system_next);
                    pthread_mutex_unlock(&(sys->object_lock));      
                    return -1;              
                }
            }
            
            rc = obj->object_create_cb(obj);
            if (rc) {
                obj->state = ASYNC_OBJ_STATE_FAILED;
            } else {
                obj->state = ASYNC_OBJ_STATE_ACTIVE;
            }
            //remove from work queue
            entry->obj = NULL;
            free(entry);
            break;
        case ASYNC_OBJ_STATE_DELETING:
            // check siblings, make sure sibling is empty
            if (!LIST_EMPTY(&obj->sibling_list)) {
                //keep in DELETING state, put back into work queue
                pthread_mutex_lock(&(sys->object_lock));
                LIST_INSERT_HEAD(&(sys->object_list), entry, system_next);
                pthread_mutex_unlock(&(sys->object_lock));      
                return -1;              
            }
                 
            obj->object_delete_cb(obj);

            //update parent's sibling list
            LIST_FOREACH(parent, obj->parent_list, system_next) {
                if (!parent->obj) {
                    continue;
                }
                if (LIST_EMPTY(parent->obj->sibling_list)) {
                    //this parent's sibling list is empty
                    continue;
                }

                pthread_mutex_lock(&(parent->lock));
                LIST_FOREACH(sibling, parent->obj->sibling_list, system_next) {
                    if (sibling->obj == obj) {
                        //remove sibling from list
                        LIST_REMOVE(sibling, system_next);
                        sibling->obj = NULL;
                        free(sibling);
                    }
                }
                pthread_mutex_unlock(&(parent->lock));
            }

            //delete is always successful ???
            free(obj);
            entry->obj = NULL;
            free(entry);
            break;
            
        default:
            break;
    }

}

int switchdev_async_obj_main(switch_service_t *sys)
{
    async_obj_entry_t *entry = NULL;
    async_object_t    *obj   = NULL;
    int                rc    = 0;

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
            break;
        }

        process_async_object(entry);
    }

    return 0;
}


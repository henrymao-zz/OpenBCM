#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#include <net/if.h>
#include <arpa/inet.h>

#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <fcntl.h>
#include <linux/netdevice.h>
#include <linux/if_bridge.h>
#include <pthread.h>


#include "switchdev_utils.h"
#include "switchdev_async_obj.h"
#include "switchdev_broadcom.h"



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

    //printf("async_object_create type %d state %d\n", obj->type, obj->state);
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

    LIST_FOREACH(entry, &(sys->switch_db.object_db), system_next) {
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
    async_queue_entry_t *work = NULL;
    switch_service_t    *sys  = NULL;

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
            //should not exist in work queue (sys->asyncq.object_queue)
            async_object_free(obj);
            break;

        case ASYNC_OBJ_STATE_ACTIVE:
            (*obj)->state = ASYNC_OBJ_STATE_DELETING;
            //add to work queue (sys->asyncq.object_queue)
            work = (async_queue_entry_t *)malloc(sizeof(async_queue_entry_t));
            if (!work) {
                //printf("async_object_delete malloc failed\n");
                break;
            }

            work->obj = *obj;

            pthread_mutex_lock(&(sys->asyncq.object_lock));
            TAILQ_INSERT_TAIL(&(sys->asyncq.object_queue), work, _links);
            pthread_mutex_unlock(&(sys->asyncq.object_lock));

            pthread_cond_signal(&sys->asyncq.object_cond);
            break;
        case ASYNC_OBJ_STATE_DELETING:
            //should already inserted into work queue (sys->object_queue)
            break;
        default:
            break;
    }


    return 0;
}


int async_object_download(async_object_t *obj)
{
    async_queue_entry_t *work   = NULL;
    async_obj_entry_t   *parent = NULL;
    switch_service_t    *sys    = NULL;

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

    work = (async_queue_entry_t *)malloc(sizeof(async_queue_entry_t));
    if (!work) {
        //printf("async_object_download malloc failed\n");
        return -1;
    }

    work->obj = obj;

    //printf("async_object_download obj %p \n", obj);

    // if parent is not in download list, add parent to download list
    //if parent is not in download list, add parent to download list
    LIST_FOREACH(parent, &(obj->parent_list), system_next) {
        if (!parent->obj) {
            //should not happen, ignore this parent
            continue;
        }

        if (parent->obj->state == ASYNC_OBJ_STATE_IDLE) {
            //printf("async_object_add_parent trigger parent download %p\n", parent);
            parent->obj->object_download(parent->obj);
        }
    }

    pthread_mutex_lock(&(sys->asyncq.object_lock));
    TAILQ_INSERT_TAIL(&(sys->asyncq.object_queue), work, _links);
    pthread_mutex_unlock(&(sys->asyncq.object_lock));

    pthread_cond_signal(&sys->asyncq.object_cond);
    return 0;
}

int async_object_add_parent(async_object_t *obj, async_object_t *parent)
{
    async_obj_entry_t *entry = NULL, *entry_p = NULL;
    switch_service_t  *sys = NULL;

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

    return 0;
}

/******************************************************************************************/
/*     ASYNC_OBJ_TYPE_SWITCH                                                              */
/******************************************************************************************/
async_obj_switch_t** async_obj_switch_find_or_new(int unit)
{
    switch_service_t    *sys   = NULL;
    async_obj_entry_t   *entry = NULL;
    async_obj_switch_t  *obj   = NULL;
    async_obj_switch_t **objp  = NULL;

    if (!(sys = system_get_instance()))
        return NULL;
   
    if ((objp = async_obj_switch_find(unit)))
        return objp;

    if (!(entry = (async_obj_entry_t*)malloc(sizeof(async_obj_entry_t))))
    {
        printf("switch obj malloc failed unit 0x%x \n",  unit);
        return NULL;
    }

    if (!(obj = (async_obj_switch_t*)malloc(sizeof(async_obj_switch_t))))
    {
        free(entry);
        printf("switch object malloc failed unit %d \n",  unit);
        return NULL;
    }

    //printf("async_obj_switch_find_or_new new obj for unit %d\n", unit);

    memset(entry, 0, sizeof(async_obj_entry_t));
    entry->obj = (async_object_t *)obj;

    memset(obj, 0, sizeof(async_obj_switch_t));
    //initialize object base
    obj->state      = ASYNC_OBJ_STATE_NEW;
    obj->type       = ASYNC_OBJ_TYPE_SWITCH;
    pthread_mutex_init(&obj->lock, NULL);
    LIST_INIT(&(obj->parent_list));
    LIST_INIT(&(obj->child_list));

    obj->object_create     = async_object_create;    
    obj->object_delete     = async_object_delete;
    obj->object_download   = async_object_download;
    obj->object_add_parent = async_object_add_parent;

    obj->object_create_cb  = async_obj_switch_create_cb;
    obj->object_update_cb  = async_obj_switch_update_cb;
    obj->object_delete_cb  = async_obj_switch_delete_cb;

    //initialize object specific
    obj->unit = unit;

    LIST_INSERT_HEAD(&sys->switch_db.switch_list, entry, system_next);

    return (async_obj_switch_t**)&(entry->obj);
}

async_obj_switch_t** async_obj_switch_find(int unit)
{
    switch_service_t   *sys   = NULL;
    async_obj_entry_t  *entry = NULL;
    async_obj_switch_t *obj   = NULL;

    if ((sys = system_get_instance()) == NULL)
        return NULL;

    LIST_FOREACH(entry, &sys->switch_db.switch_list, system_next)
    {
        obj = (async_obj_switch_t *)entry->obj;
        if (obj) {
            if (unit == obj->unit) {
                return (async_obj_switch_t**)&(entry->obj);
            }
        }
    }

    return NULL;
}

/******************************************************************************************/
/*     ASYNC_OBJ_TYPE_VLAN                                                                */
/******************************************************************************************/
async_obj_vlan_t** async_obj_vlan_find_or_new(int vid)
{
    switch_service_t    *sys   = NULL;
    async_obj_entry_t   *entry = NULL;
    async_obj_vlan_t    *obj   = NULL;
    async_obj_vlan_t   **objp  = NULL;

    if (!(sys = system_get_instance()))
        return NULL;
   
    if ((objp = async_obj_vlan_find(vid)))
        return objp;

    if (!(entry = (async_obj_entry_t*)malloc(sizeof(async_obj_entry_t))))
    {
        printf("vlan obj malloc failed vlan 0x%x \n",  vid);
        return NULL;
    }

    if (!(obj = (async_obj_vlan_t*)malloc(sizeof(async_obj_vlan_t))))
    {
        free(entry);
        printf("vlan object malloc failed vlan %d \n",  vid);
        return NULL;
    }

    //printf("async_obj_vlan_find_or_new new obj for vlan %d\n", vid);

    memset(entry, 0, sizeof(async_obj_entry_t));
    entry->obj = (async_object_t *)obj;

    memset(obj, 0, sizeof(async_obj_vlan_t));
    //initialize object base
    obj->state      = ASYNC_OBJ_STATE_NEW;
    obj->type       = ASYNC_OBJ_TYPE_VLAN;
    pthread_mutex_init(&obj->lock, NULL);
    LIST_INIT(&(obj->parent_list));
    LIST_INIT(&(obj->child_list));

    obj->object_create     = async_object_create;    
    obj->object_delete     = async_object_delete;
    obj->object_download   = async_object_download;
    obj->object_add_parent = async_object_add_parent;

    obj->object_create_cb  = async_obj_vlan_create_cb;
    obj->object_update_cb  = async_obj_vlan_update_cb;
    obj->object_delete_cb  = async_obj_vlan_delete_cb;

    //initialize object specific
    obj->vid = vid;

    LIST_INSERT_HEAD(&sys->switch_db.vlan_list, entry, system_next);

    return (async_obj_vlan_t**)&(entry->obj);
}

async_obj_vlan_t** async_obj_vlan_find(int vid)
{
    switch_service_t   *sys   = NULL;
    async_obj_entry_t  *entry = NULL;
    async_obj_vlan_t   *obj   = NULL;

    if ((sys = system_get_instance()) == NULL)
        return NULL;

    LIST_FOREACH(entry, &(sys->switch_db.vlan_list), system_next)
    {
        obj = (async_obj_vlan_t *)entry->obj;
        if (obj && obj->vid == vid)
            return (async_obj_vlan_t **)&(entry->obj);
    }

    return NULL;

}

/******************************************************************************************/
/*     ASYNC_OBJ_TYPE_INTF                                                                */
/******************************************************************************************/
async_obj_intf_t** async_obj_intf_find(int ifindex)
{
    switch_service_t   *sys   = NULL;
    async_obj_entry_t  *entry = NULL;
    async_obj_intf_t   *obj   = NULL;

    if ((sys = system_get_instance()) == NULL)
        return NULL;

    LIST_FOREACH(entry, &(sys->switch_db.lif_list), system_next)
    {
        obj = (async_obj_intf_t *)entry->obj;
        if (obj && obj->ifindex == ifindex)
            return (async_obj_intf_t **)&(entry->obj);
    }

    return NULL;
}

async_obj_intf_t** async_obj_intf_find_by_name(char *ifname)
{
    switch_service_t   *sys   = NULL;
    async_obj_entry_t  *entry = NULL;
    async_obj_intf_t   *obj   = NULL;

    if ((sys = system_get_instance()) == NULL)
        return NULL;

    LIST_FOREACH(entry, &(sys->switch_db.lif_list), system_next)
    {
        obj = (async_obj_intf_t *)entry->obj;
        if (obj && (strncmp(obj->name, ifname, IF_NAMESIZE) == 0))
            return (async_obj_intf_t **)&(entry->obj);
    }

    return NULL;
}


async_obj_intf_t** async_obj_intf_new(char* ifname)
{
    switch_service_t   *sys   = NULL;
    async_obj_entry_t  *entry = NULL;
    async_obj_intf_t   *obj   = NULL;

    if (!ifname)
        return NULL;

    if (!(sys = system_get_instance()))
        return NULL;

    if (!(entry = (async_obj_entry_t*)malloc(sizeof(async_obj_entry_t))))
    {
        printf("intf entry malloc failed %s \n",  ifname);
        return NULL;
    }

    if (!(obj = (async_obj_intf_t*)malloc(sizeof(async_obj_intf_t))))
    {
        free(entry);
        printf("intf object malloc failed ifname %s \n", ifname);
        return NULL;
    }

    //printf("async_obj_intf_new new obj for ifname %s\n", ifname);

    memset(entry, 0, sizeof(async_obj_entry_t));
    entry->obj = (async_object_t *)obj;

    memset(obj, 0, sizeof(async_obj_intf_t));
    //initialize object base
    obj->state      = ASYNC_OBJ_STATE_NEW;
    obj->type       = ASYNC_OBJ_TYPE_INTF;
    pthread_mutex_init(&obj->lock, NULL);
    LIST_INIT(&(obj->parent_list));
    LIST_INIT(&(obj->child_list));

    obj->object_create     = async_object_create;    
    obj->object_delete     = async_object_delete;
    obj->object_download   = async_object_download;
    obj->object_add_parent = async_object_add_parent;

    obj->object_create_cb  = async_obj_intf_create_cb;
    obj->object_update_cb  = async_obj_intf_update_cb;
    obj->object_delete_cb  = async_obj_intf_delete_cb;

    //initialize object specific
    obj->l3_intf = -1;

    snprintf(obj->name, IF_NAMESIZE, "%s", ifname);

    LIST_INSERT_HEAD(&(sys->switch_db.lif_list), entry, system_next);

    return (async_obj_intf_t**)&(entry->obj);
}

/******************************************************************************************/
/*     ASYNC_OBJ_TYPE_L3HOST                                                              */
/******************************************************************************************/
async_obj_l3host_t** async_obj_l3host_find_or_new(ip_address_t *host)
{
    switch_service_t    *sys   = NULL;
    async_obj_entry_t   *entry = NULL;
    async_obj_l3host_t  *obj   = NULL;
    async_obj_l3host_t **objp  = NULL;

    if (!(sys = system_get_instance()))
        return NULL;
   
    if ((objp = async_obj_l3host_find(host)))
        return objp;

    if (!(entry = (async_obj_entry_t*)malloc(sizeof(async_obj_entry_t))))
    {
        printf("l3host entry malloc failed host %s\n",  ipaddr2str(host));
        return NULL;
    }

    if (!(obj = (async_obj_l3host_t*)malloc(sizeof(async_obj_l3host_t))))
    {
        free(entry);
        printf("l3host object malloc failed host %s\n",  ipaddr2str(host));
        return NULL;
    }

    //printf("async_obj_l3host_find_or_new new obj for 0x%x\n", host->ip[0]);

    memset(entry, 0, sizeof(async_obj_entry_t));
    entry->obj = (async_object_t *)obj;

    memset(obj, 0, sizeof(async_obj_l3host_t));
    //initialize object base
    obj->state      = ASYNC_OBJ_STATE_NEW;
    obj->type       = ASYNC_OBJ_TYPE_L3HOST;
    pthread_mutex_init(&obj->lock, NULL);
    LIST_INIT(&(obj->parent_list));
    LIST_INIT(&(obj->child_list));

    obj->object_create     = async_object_create;    
    obj->object_delete     = async_object_delete;
    obj->object_download   = async_object_download;
    obj->object_add_parent = async_object_add_parent;

    obj->object_create_cb  = async_obj_l3host_create_cb;
    obj->object_update_cb  = async_obj_l3host_update_cb;
    obj->object_delete_cb  = async_obj_l3host_delete_cb;

    //initialize object specific
    memcpy(&obj->host, host, sizeof(ip_address_t));

    LIST_INSERT_HEAD(&sys->switch_db.object_db, entry, system_next);

    return (async_obj_l3host_t**)&(entry->obj);

}

async_obj_l3host_t** async_obj_l3host_find(ip_address_t *host)
{
    switch_service_t   *sys   = NULL;
    async_obj_entry_t  *entry = NULL;
    async_obj_l3host_t *obj   = NULL;

    if ((sys = system_get_instance()) == NULL)
        return NULL;

    LIST_FOREACH(entry, &sys->switch_db.object_db, system_next)
    {
        obj = (async_obj_l3host_t *)entry->obj;
        if (obj &&obj->type == ASYNC_OBJ_TYPE_L3HOST) {
            if (memcmp(&(obj->host), host, sizeof(ip_address_t)) == 0)
                return (async_obj_l3host_t**)&(entry->obj);
        }
    }

    return NULL;

}

/******************************************************************************************/
/*     ASYNC_OBJ_TYPE_NEIGH                                                               */
/******************************************************************************************/
async_obj_neigh_t** async_obj_neigh_find(ip_address_t *nh)
{
    switch_service_t  *sys   = NULL;
    async_obj_entry_t *entry = NULL;
    async_obj_neigh_t *obj   = NULL;

    if ((sys = system_get_instance()) == NULL)
        return NULL;

    LIST_FOREACH(entry, &sys->switch_db.object_db, system_next)
    {
        obj = (async_obj_neigh_t *)entry->obj;
        if (obj) {
            if (memcmp(&(obj->nh), nh, sizeof(ip_address_t)) == 0)
                return (async_obj_neigh_t**)&(entry->obj);
        }
    }

    return NULL;
}

async_obj_neigh_t** async_obj_neigh_find_type(int neigh_type)
{
    switch_service_t  *sys   = NULL;
    async_obj_entry_t *entry = NULL;
    async_obj_neigh_t *obj   = NULL;

    if ((sys = system_get_instance()) == NULL)
        return NULL;

    LIST_FOREACH(entry, &sys->switch_db.object_db, system_next)
    {
        obj = (async_obj_neigh_t *)entry->obj;
        if (obj) {
            if (obj->neigh_type == neigh_type)
                return (async_obj_neigh_t**)&(entry->obj);
        }
    }

    return NULL;
}


async_obj_neigh_t** async_obj_neigh_new(void)
{
    switch_service_t   *sys   = NULL;
    async_obj_entry_t  *entry = NULL;
    async_obj_neigh_t  *obj   = NULL;

    if (!(sys = system_get_instance()))
        return NULL;
   
    if (!(entry = (async_obj_entry_t*)malloc(sizeof(async_obj_entry_t))))
    {
        printf("neigh entry malloc failed\n");
        return NULL;
    }

    if (!(obj = (async_obj_neigh_t*)malloc(sizeof(async_obj_neigh_t))))
    {
        free(entry);
        printf("neigh object malloc failed\n");
        return NULL;
    }

    //printf("async_obj_neigh_new new obj \n");

    memset(entry, 0, sizeof(async_obj_entry_t));
    entry->obj = (async_object_t *)obj;

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
    obj->neigh_type       = NEIGH_DYNAMIC;

    LIST_INSERT_HEAD(&sys->switch_db.object_db, entry, system_next);

    return (async_obj_neigh_t**)&(entry->obj);
}


async_obj_neigh_t** async_obj_neigh_find_or_new(ip_address_t *nh)
{
    switch_service_t   *sys   = NULL;
    async_obj_neigh_t **obj   = NULL;

    if (!(sys = system_get_instance()))
        return NULL;
   
    if ((obj = async_obj_neigh_find(nh)))
        return obj;

    //printf("async_obj_neigh_find_or_new new obj for 0x%x\n", nh->ip[0]);

    obj = async_obj_neigh_new();
    if(!obj || !(*obj)) {
        return NULL;
    }

    memcpy(&((*obj)->nh), nh, sizeof(ip_address_t));

    return obj;
}



/******************************************************************************************/
/*     ASYNC_OBJ_TYPE_FIB                                                                 */
/******************************************************************************************/

async_obj_fib_t** async_obj_fib_find(ip_address_t *dst, int dst_len)
{
    switch_service_t   *sys   = NULL;
    async_obj_entry_t  *entry = NULL;
    async_obj_fib_t    *obj   = NULL;

    if ((sys = system_get_instance()) == NULL)
        return NULL;

    LIST_FOREACH(entry, &(sys->switch_db.object_db), system_next)
    {
        if (entry->obj && (entry->obj->type == ASYNC_OBJ_TYPE_FIB)) {
            obj = (async_obj_fib_t *)entry->obj;
            if ((memcmp(&obj->dst, dst, sizeof(ip_address_t)) == 0) &&
                (obj->dst_len == dst_len)) {
                return (async_obj_fib_t**)&(entry->obj);
            }
        }
    }

    return NULL;
}

async_obj_fib_t** async_obj_fib_find_or_new(ip_address_t *dst, int dst_len)
{
    switch_service_t   *sys   = NULL;
    async_obj_entry_t  *fib   = NULL;
    async_obj_fib_t    *obj   = NULL;
    async_obj_fib_t   **objp  = NULL;

    if (!(sys = system_get_instance()))
        return NULL;
   
    if ((objp = async_obj_fib_find(dst, dst_len)))
        return objp;

    if (!(fib = (async_obj_entry_t*)malloc(sizeof(async_obj_entry_t))))
    {
        printf("fib entry malloc failed ipv4 %s/%d\n", 
               ipaddr2str(dst), dst_len );
        return NULL;
    }

    if (!(obj = (async_obj_fib_t*)malloc(sizeof(async_obj_fib_t))))
    {
        free(fib);
        printf("fib object malloc failed ipv4 %s/%d\n", 
               ipaddr2str(dst), dst_len);
        return NULL;
    }

    //printf("async_obj_fib_find_or_new new obj ip 0x%x/%d nh 0x%x\n",
    //       dst->ip[0], dst_len, nh->ip[0]);

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
    obj->dst_len    = dst_len;

    memcpy(&obj->dst, dst, sizeof(ip_address_t));
    
    LIST_INSERT_HEAD(&sys->switch_db.object_db, fib, system_next);

    return (async_obj_fib_t**)&(fib->obj);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////

//TASK handling object download
int process_async_object(async_queue_entry_t *work) 
{
    async_object_t     *obj    = NULL;
    async_obj_entry_t  *parent = NULL, *child = NULL;
    switch_service_t   *sys    = NULL;
    int                 rc     = 0;

    obj = work->obj;

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
            work->obj = NULL;
            free(work);
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
                    work->obj = NULL;
                    free(work);
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
               //printf("    child %p, state %d type %d\n", child->obj, child->obj->state, child->obj->type);
               if (!child->obj) {
                   //should not happen, ignore
                   continue;
               }

               if (child->obj->state == ASYNC_OBJ_STATE_PENDING) {
                   child->obj->object_download(child->obj);
               }
            }

            //free workqueue item
            work->obj = NULL;
            free(work);
            break;
        case ASYNC_OBJ_STATE_DELETING:
            // check childs, make sure child is empty
            if (!LIST_EMPTY(&obj->child_list)) {
                //remove from workqueue, will be add back if parent delete success
                //printf("process_async_object %p child not NULL, skip\n", obj);
                work->obj = NULL;
                free(work);
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
            work->obj = NULL;
            free(work);

            break;
            
        default:
            break;
    }

    return 0;
}

int switchdev_async_obj_main(switch_service_t *sys)
{
    async_queue_entry_t *work  = NULL;
    async_object_t      *obj   = NULL;

    if (!sys) {
        return 0;
    } 

    while(1) {
        pthread_mutex_lock(&sys->asyncq.object_lock);
        while (TAILQ_EMPTY(&sys->asyncq.object_queue)) {
            pthread_cond_wait(&sys->asyncq.object_cond, &sys->asyncq.object_lock);
        }

        work = TAILQ_FIRST(&sys->asyncq.object_queue);

        TAILQ_REMOVE(&sys->asyncq.object_queue, work, _links);

        pthread_mutex_unlock(&sys->asyncq.object_lock);

        obj = work->obj;

        if(!obj) {
            free(work);
            continue;
        }

        process_async_object(work);
    }

    return 0;
}


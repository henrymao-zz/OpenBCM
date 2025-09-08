#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/queue.h>
#include <net/if.h>
#include <pthread.h>

#ifndef NO_SAL_APPL
#include <sal/appl/sal.h>
#include <sal/appl/config.h>
#include <appl/diag/bslmgmt.h>
#include <appl/diag/opennsa_diag.h>
#endif

#include "switchdev_utils.h"
#include "switchdev_netlink.h"
#include "switchdev_async_obj.h"




//load port_config.ini and create interfaces
int switchdev_portconfig_init(int unit)
{
    FILE *fp         = NULL;
    char *token      = NULL;    
    char  line[256];
    int   port;
    char  ifname[IF_NAMESIZE+1]; 
    async_obj_intf_t **local_if = NULL;
    async_obj_vlan_t **vlan     = NULL;    

    /* open file, allocate buffer and read file into buffer */
    fp = sal_fopen("/etc/bcm/port_config.ini", "rb");
  
    if (!fp) {
       printf("port_config.ini open failed \n");
       return 0;
    }

    while (fgets(line, sizeof(line), fp)) {
        //printf("%s", line);         //Name
        // skip comments
        if(line[0] == '#') {
            continue;
        }

        token = strtok(line, " ");  //name
        sal_strncpy(ifname, token, IF_NAMESIZE);

        token = strtok (NULL, " "); //lanes
        token = strtok (NULL, " "); //alias
        token = strtok (NULL, " "); //index
        port = atoi(token);   //hw port

        /* intf default l3 routed mode, and put in vlan 4095 
         * if vlan 4095 does not exist, create a new obj
         */
        vlan = async_obj_vlan_find_or_new(4095);
        if (!vlan || !(*vlan)) {
            printf("Failed to create vlan for routed port %s\n", ifname);
            fclose(fp);
            return -1;
        }            

        local_if = async_obj_intf_new(ifname);
        if(!local_if || !(*local_if)) {
            printf("Failed to new async_obj_intf for %s\n", ifname);
            continue;
        }
        (*local_if)->if_type   = INTF_TYPE_PHYSICAL;
        (*local_if)->hw_port   = port;
        (*local_if)->port_mode = TYPE_ROUTED_PORT;
        (*local_if)->autoneg   = true;
        (*local_if)->pause_tx  = false;
        (*local_if)->pause_rx  = false;

    
        (*local_if)->object_add_parent((async_object_t *)*local_if, (async_object_t *)*vlan);
        (*local_if)->object_create((async_object_t *)*local_if);
        (*local_if)->object_download((async_object_t *)*local_if);        
    }

    fclose(fp);
    return 0;
}


/* switchdev netlink thread */
static int switchdev_netlink_thread_priority = 100;
static volatile sal_thread_t switchdev_netlink_thread_id        = SAL_THREAD_ERROR;


static void switchdev_system_init(switch_service_t* sys)
{
    if (sys == NULL )
        return;

    memset(sys, 0, sizeof(switch_service_t));

    LIST_INIT(&(sys->switch_db.switch_list));
    pthread_rwlock_init(&(sys->switch_db.switch_rwlock), NULL);

    LIST_INIT(&(sys->switch_db.vlan_list));
    pthread_rwlock_init(&(sys->switch_db.vlan_rwlock), NULL);

    LIST_INIT(&(sys->switch_db.lif_list));
    pthread_rwlock_init(&(sys->switch_db.lif_rwlock), NULL);

    LIST_INIT(&(sys->switch_db.l3host_list));
    pthread_rwlock_init(&(sys->switch_db.l3host_rwlock), NULL);

    LIST_INIT(&(sys->switch_db.neigh_list));
    pthread_rwlock_init(&(sys->switch_db.neigh_rwlock), NULL);

    LIST_INIT(&(sys->switch_db.fib_list));
    pthread_rwlock_init(&(sys->switch_db.fib_rwlock), NULL);

    TAILQ_INIT(&(sys->asyncq.object_queue));
    pthread_mutex_init(&sys->asyncq.object_lock, NULL);
    pthread_cond_init(&sys->asyncq.object_cond, NULL);

    return;
}

/* Singleton */
switch_service_t* system_get_instance()
{
    static switch_service_t* sys = NULL;

    if (sys == NULL )
    {
        sys = (switch_service_t*)malloc(sizeof(switch_service_t));
        if (sys == NULL )
        {
            printf("Failed to obtain system instance.\n");
            return NULL;
        }
        switchdev_system_init(sys);
    }

    return sys;
}


/* System instance tear down */
void system_finalize()
{
    static switch_service_t *sys      = NULL;
    async_obj_entry_t       *entry    = NULL;

    if ((sys = system_get_instance()) == NULL )
        return;

    /* Release all port objects */
    while (!LIST_EMPTY(&(sys->switch_db.lif_list)))
    {
        entry = LIST_FIRST(&(sys->switch_db.lif_list));
        LIST_REMOVE(entry, system_next);
        if (entry->obj) {
            free(entry->obj);
        }
        entry->obj = NULL;
        free(entry);
    }

    /* Release all objects */
    while (!LIST_EMPTY(&(sys->switch_db.vlan_list)))
    {
        entry = LIST_FIRST(&(sys->switch_db.vlan_list));
        LIST_REMOVE(entry, system_next);
        if (entry->obj) {
            free(entry->obj);
        }
        entry->obj = NULL;
        free(entry);
    }    
}

static void
switchdev_netlink_thread(void *cookie)
{
    COMPILER_REFERENCE(cookie);

    switchdev_netlink_main();

    sal_thread_exit(0);
}

int switchdev_netlink_init(void)
{
    switchdev_netlink_thread_id = sal_thread_create("netlink",
                                         SAL_THREAD_STKSZ,
                                         switchdev_netlink_thread_priority,
                                         switchdev_netlink_thread, NULL);
    if (switchdev_netlink_thread_id == SAL_THREAD_ERROR) {
        sal_thread_destroy(switchdev_netlink_thread_id);
        switchdev_netlink_thread_id = SAL_THREAD_ERROR;
        return -1;
    }
    return 0;
}


/*
 * Main loop.
 */
int main( int argc, char *argv[] )
{
    int                   rc     = 0;
    switch_service_t     *sys    = NULL;
    async_obj_switch_t  **sw     = NULL;
    async_obj_vlan_t    **vlan   = NULL;
    async_obj_intf_t    **intf   = NULL;
    async_obj_fib_t     **fib    = NULL;
    async_obj_neigh_t   **neigh  = NULL;
    ip_address_t          ip_default;
    uint8_t               system_mac[ETHER_ADDR_LEN] = {0x20, 0x88, 0x10, 0x58, 0xf9, 0x80}; //need to get from eeprom

    //parse argv

    if ((sys = system_get_instance()) == NULL )
        return -1;    

    // start system processes
    /* Initialize netlink to switchdev kernel module */
    switchdev_netlink_init();

    //create switch object - hardcode for unit 0 for now
    sw = async_obj_switch_find_or_new(0);
    if (!sw || !(*sw)) {
        goto init_fail;
    }
    (*sw)->unit       = 0;
    (*sw)->route_vlan = 4095;
    memcpy((*sw)->system_mac, system_mac, ETHER_ADDR_LEN);
    (*sw)->object_create((async_object_t *)*sw);
    (*sw)->object_download((async_object_t *)*sw);


    //Create vlan 4095 - internal vlan for routed port
    vlan = async_obj_vlan_find_or_new((*sw)->route_vlan);
    if (!vlan || !(*vlan)) {
        goto init_fail;
    }    
    (*vlan)->if_class        = 1;
    (*vlan)->block_broadcast = 1;

    (*vlan)->object_add_parent((async_object_t *)*vlan, (async_object_t *)*sw);
    (*vlan)->object_create((async_object_t *)*vlan);
    (*vlan)->object_download((async_object_t *)*vlan);

    //Create CPU neighbour (FORUS)
    neigh = async_obj_neigh_new();
    if (!neigh || !(*neigh)) {
        // should not happen
        goto init_fail;
    }
    (*neigh)->neigh_type = NEIGH_FORUS;
    (*neigh)->vlan_id    = (*sw)->route_vlan;
    (*neigh)->hw_port    = 0;
    (*neigh)->ifindex    = -1;    
    memcpy((*neigh)->mac_addr, system_mac, ETHER_ADDR_LEN);
    (*neigh)->object_add_parent((async_object_t *)(*neigh),(async_object_t *)*vlan);
    (*neigh)->object_create((async_object_t *)(*neigh));
    (*neigh)->object_download((async_object_t *)*neigh);

    //Create vlan 1 - default vlan, enable l3
    vlan = NULL;
    vlan = async_obj_vlan_find_or_new(1);
    if (!vlan || !(*vlan)) {
        goto init_fail;
    }      
    (*vlan)->object_add_parent((async_object_t *)*vlan, (async_object_t *)*sw);
    (*vlan)->object_create((async_object_t *)*vlan);
    (*vlan)->object_download((async_object_t *)*vlan);

    //Create vlan 1 virtual interface 
    intf = async_obj_intf_new("Vlan1");
    if(!intf || !(*intf)) {
        printf("Failed to new async_obj_intf for Vlan1\n");
        goto init_fail;
    }
    (*intf)->if_type   = INTF_TYPE_VLAN;
    (*intf)->port_mode = TYPE_ROUTED_PORT;
    (*intf)->vlan      = 1;

    (*intf)->object_add_parent((async_object_t *)*intf, (async_object_t *)*vlan);
    (*intf)->object_create((async_object_t *)*intf);
    (*intf)->object_download((async_object_t *)*intf);     

    //create vlan 1 neigh forus 
    neigh = NULL;
    neigh = async_obj_neigh_new();
    if (!neigh || !(*neigh)) {
        // should not happen
        goto init_fail;
    }
    (*neigh)->neigh_type = NEIGH_FORUS;
    (*neigh)->vlan_id    = 1;
    (*neigh)->hw_port    = 0;
    (*neigh)->ifindex    = -1;
    sprintf((*neigh)->ifname, "%s", "Vlan1");
    memcpy((*neigh)->mac_addr, (*sw)->system_mac, ETHER_ADDR_LEN);
    (*neigh)->object_add_parent((async_object_t *)*neigh, (async_object_t *)*intf);
    (*neigh)->object_create((async_object_t *)*neigh);
    (*neigh)->object_download((async_object_t *)*neigh);         

    //Create default ipv4  route for vlan 1
    ip_default.protocol = AF_INET;
    ip_default.ip[0]    = 0;
    ip_default.ip[1]    = 0;
    ip_default.ip[2]    = 0;
    ip_default.ip[3]    = 0;
    fib = async_obj_fib_find_or_new(&ip_default, 0, 0);
    if (!fib || !(*fib)) {
        // should not happen
        goto init_fail;
    }

    (*fib)->object_add_parent((async_object_t *)*fib, (async_object_t *)*neigh);
    (*fib)->object_create((async_object_t *)*fib);
    (*fib)->object_download((async_object_t *)*fib);

    //Create default ipv6 route for vlan 1
    ip_default.protocol = AF_INET6;
    fib = async_obj_fib_find_or_new(&ip_default, 0, 0);
    if (!fib || !(*fib)) {
        // should not happen
        goto init_fail;
    }

    (*fib)->object_add_parent((async_object_t *)*fib, (async_object_t *)*neigh);
    (*fib)->object_create((async_object_t *)*fib);
    (*fib)->object_download((async_object_t *)*fib);

    //Create ports from port_config.ini
    rc = switchdev_portconfig_init(0);
    if(rc) {
        goto init_fail;
    }

    //main thread handle obj processing
    rc = switchdev_async_obj_main(sys);

init_fail:
    system_finalize();

    return rc;
}

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pty.h>
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
        if (!vlan) {
            printf("Failed to create vlan for routed port %s\n", ifname);
            fclose(fp);
            return -1;
        }            

        local_if = async_obj_intf_new(ifname);
        if(local_if) {
            printf("Failed to new async_obj_intf for %s\n", ifname);
            continue;
        }
        (*local_if)->hw_port   = port;
        (*local_if)->port_type = TYPE_ROUTED_PORT;

    
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

    LIST_INIT(&(sys->switch_db.lif_list));

    LIST_INIT(&(sys->switch_db.object_db));

    LIST_INIT(&(sys->object_list));
    pthread_mutex_init(&sys->object_lock, NULL);
    pthread_cond_init(&sys->object_cond, NULL);

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
    local_interface_t       *local_if = NULL;
    async_obj_entry_t       *entry    = NULL;

    if ((sys = system_get_instance()) == NULL )
        return;

    /* Release all port objects */
    while (!LIST_EMPTY(&(sys->switch_db.lif_list)))
    {
        local_if = LIST_FIRST(&(sys->switch_db.lif_list));
        LIST_REMOVE(local_if, system_next);
        local_if_finalize(local_if);
    }

    /* Release all objects */
    while (!LIST_EMPTY(&(sys->switch_db.object_db)))
    {
        entry = LIST_FIRST(&(sys->switch_db.object_db));
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
        return BCM_E_MEMORY;
    }
    return BCM_E_NONE;
}


/*
 * Main loop.
 */
int main( int argc, char *argv[] )
{
    int                   rc     = 0;
    switch_service_t     *sys    = NULL;
    async_obj_switch_t  **switch = NULL;
    async_obj_vlan_t    **vlan   = NULL;

    //parse argv

    if ((sys = system_get_instance()) == NULL )
        return;    

    // start system processes
    /* Initialize netlink to switchdev kernel module */
    switchdev_netlink_init();

    //create switch object - hardcode for unit 0 for now
    switch = async_obj_switch_find_or_new(0);
    if (!switch) {
        goto init_fail;
    }
    switch->unit       = 0;
    switch->route_vlan = 4095;
    (*switch)->object_create((async_object_t *)*switch);
    (*switch)->object_download((async_object_t *)*switch);


    //Create vlan 4095 - default vlan for routed port
    vlan = async_obj_vlan_find_or_new(switch->route_vlan);
    if (!vlan) {
        return -1;
    }    
    (*vlan)->if_class        = 1;
    (*vlan)->block_broadcast = 1;

    (*vlan)->object_add_parent((async_object_t *)*vlan, (async_object_t *)*switch);
    (*vlan)->object_create((async_object_t *)*vlan);
    (*vlan)->object_download((async_object_t *)*vlan);

    //Create ports from port_config.ini
    rc = switchdev_portconfig_init(0);
    if(!rc) {
        goto init_fail;
    }

    //main thread handle obj processing
    rc = switchdev_async_obj_main(sys);

init_fail:
    system_finalize();

    return rc;
}

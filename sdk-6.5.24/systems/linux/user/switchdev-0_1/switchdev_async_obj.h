#ifndef SWITCHDEV_ASYNC_OBJ_H
#define SWITCHDEV_ASYNC_OBJ_H



#ifndef container_of
#define container_of(PTR, TYPE, FIELD) ({			\
	__typeof__(((TYPE *)0)->FIELD) *__FIELD_PTR = (PTR);	\
	(TYPE *)((char *) __FIELD_PTR - offsetof(TYPE, FIELD));	\
})
#endif

#define ETHER_ADDR_LEN 6

// async object base definition
enum object_state_e {
    ASYNC_OBJ_STATE_NEW,
    ASYNC_OBJ_STATE_IDLE,
	ASYNC_OBJ_STATE_PENDING,
	ASYNC_OBJ_STATE_ACTIVE,
	ASYNC_OBJ_STATE_DELETING,
	ASYNC_OBJ_STATE_FAILED,
	ASYNC_OBJ_STATE_MAX    
};

enum async_obj_type_e {
    ASYNC_OBJ_TYPE_SWITCH,            //root object of a switch
    ASYNC_OBJ_TYPE_VLAN,
    ASYNC_OBJ_TYPE_INTF,
    ASYNC_OBJ_TYPE_L3HOST,
    ASYNC_OBJ_TYPE_NEIGH,
    ASYNC_OBJ_TYPE_FIB,

    ASYNC_OBJ_TYPE_MAX    
};

struct async_obj_entry_s;
struct async_object_s;

typedef int (*object_create_func)(struct async_object_s *);
typedef int (*object_delete_func)(struct async_object_s **);
typedef int (*object_download_func)(struct async_object_s *);
typedef int (*object_add_parent_func)(struct async_object_s *, struct async_object_s *);
typedef int (*object_create_cb_func)(struct async_object_s *);
typedef int (*object_update_cb_func)(struct async_object_s *);
typedef int (*object_delete_cb_func)(struct async_object_s *);


typedef struct async_object_s {
    int              state;
    int              type;
	pthread_mutex_t  lock;

	LIST_HEAD(obj_parent_list_t, async_obj_entry_s)  parent_list;
	LIST_HEAD(obj_child_list_t, async_obj_entry_s)  child_list;

    object_create_func     object_create;
    object_delete_func     object_delete;
	object_download_func   object_download;
	object_add_parent_func object_add_parent;

	object_create_cb_func  object_create_cb;
	object_update_cb_func  object_update_cb;
	object_delete_cb_func  object_delete_cb;
} async_object_t;


//async_obj_entry stored in list
typedef struct async_obj_entry_s {
	struct async_object_s  *obj;

    LIST_ENTRY(async_obj_entry_s) system_next;
}async_obj_entry_t;


/******************************************************************************************/
/*     ASYNC_OBJ_TYPE_SWITCH                                                              */
/******************************************************************************************/
typedef struct async_obj_switch_s {
    //base object, must be same as async_object_t
    int              state;
    int              type;    
	pthread_mutex_t  lock;

	LIST_HEAD(obj_switch_parent_list_t, async_obj_entry_s)   parent_list;
	LIST_HEAD(obj_switch_child_list_t, async_obj_entry_s)    child_list;

    object_create_func     object_create;
    object_delete_func     object_delete;
	object_download_func   object_download;
	object_add_parent_func object_add_parent;

	object_create_cb_func  object_create_cb;
	object_update_cb_func  object_update_cb;
	object_delete_cb_func  object_delete_cb;

    //switch specfic
    int                    unit;
    int                    route_vlan;
    uint8_t                system_mac[ETHER_ADDR_LEN];

} async_obj_switch_t;

async_obj_switch_t** async_obj_switch_find_or_new(int unit);
async_obj_switch_t** async_obj_switch_find(int unit);


/******************************************************************************************/
/*     ASYNC_OBJ_TYPE_VLAN                                                                */
/******************************************************************************************/
typedef struct async_obj_vlan_s {
    //base object, must be same as async_object_t
    int              state;
    int              type;    
	pthread_mutex_t  lock;

	LIST_HEAD(obj_vlan_parent_list_t, async_obj_entry_s)   parent_list;
	LIST_HEAD(obj_vlan_child_list_t, async_obj_entry_s)    child_list;

    object_create_func     object_create;
    object_delete_func     object_delete;
	object_download_func   object_download;
	object_add_parent_func object_add_parent;

	object_create_cb_func  object_create_cb;
	object_update_cb_func  object_update_cb;
	object_delete_cb_func  object_delete_cb;

    //vlan specfic
    int                    vid;
    int                    if_class;
    int                    block_broadcast;

} async_obj_vlan_t;

async_obj_vlan_t** async_obj_vlan_find_or_new(int vid);
async_obj_vlan_t** async_obj_vlan_find(int vid);


/******************************************************************************************/
/*     ASYNC_OBJ_TYPE_INTF                                                                */
/******************************************************************************************/
enum port_mode_e {
    TYPE_ROUTED_PORT,
    TYPE_SWITCH_PORT,
};

enum port_type_e {
    INTF_TYPE_VLAN,
    INTF_TYPE_PHYSICAL,
};


typedef struct async_obj_intf_s {
    //base object, must be same as async_object_t
    int              state;
    int              type;    
	pthread_mutex_t  lock;

	LIST_HEAD(obj_intf_parent_list_t, async_obj_entry_s)   parent_list;
	LIST_HEAD(obj_intf_child_list_t, async_obj_entry_s)    child_list;

    object_create_func     object_create;
    object_delete_func     object_delete;
	object_download_func   object_download;
	object_add_parent_func object_add_parent;

	object_create_cb_func  object_create_cb;
	object_update_cb_func  object_update_cb;
	object_delete_cb_func  object_delete_cb;

    int  ifindex;                 // linux ifindex
    char name[IF_NAMESIZE+1]; 

    /* hardware information */
    int  if_type;                  // VLAN, PHYSICAL etc
    
    int  admin_state;              // enable = TRUE, disable = FALSE
    bool admin_state_changed;

    int  hw_port;                  // hardware port id
    int  port_mode;                // routed port vs switchport
    int  l3_intf;
    int  vlan;                     // should always be 4095 for routed port

    int  autoneg;
    int  pause_tx;
    int  pause_rx;

}async_obj_intf_t;

async_obj_intf_t** async_obj_intf_new(char* ifname);
async_obj_intf_t** async_obj_intf_find(int ifindex);
async_obj_intf_t** async_obj_intf_find_by_name(char *ifname);

/******************************************************************************************/
/*     ASYNC_OBJ_TYPE_L3HOST                                                              */
/******************************************************************************************/
typedef struct async_obj_l3host_s {
    //base object, must be same as async_object_t
    int              state;
    int              type;    
	pthread_mutex_t  lock;

	LIST_HEAD(obj_l3host_parent_list_t, async_obj_entry_s)   parent_list;
	LIST_HEAD(obj_l3host_child_list_t, async_obj_entry_s)    child_list;

    object_create_func     object_create;
    object_delete_func     object_delete;
	object_download_func   object_download;
	object_add_parent_func object_add_parent;

	object_create_cb_func  object_create_cb;
	object_update_cb_func  object_update_cb;
	object_delete_cb_func  object_delete_cb;

    //l3host specfic	
    ip_address_t       host;
    int                lookup_class;
} async_obj_l3host_t;

async_obj_l3host_t** async_obj_l3host_find_or_new(ip_address_t *host);
async_obj_l3host_t** async_obj_l3host_find(ip_address_t *host);


/******************************************************************************************/
/*     ASYNC_OBJ_TYPE_NEIGH                                                               */
/******************************************************************************************/

enum neigh_type_e {
     NEIGH_DYNAMIC,
     NEIGH_FORUS,
};

typedef struct async_obj_neigh_s {
    //base object, must be same as async_object_t
    int              state;
    int              type;    
	pthread_mutex_t  lock;

	LIST_HEAD(obj_neigh_parent_list_t, async_obj_entry_s)   parent_list;
	LIST_HEAD(obj_neigh_child_list_t, async_obj_entry_s)    child_list;

    object_create_func     object_create;
    object_delete_func     object_delete;
	object_download_func   object_download;
	object_add_parent_func object_add_parent;

	object_create_cb_func  object_create_cb;
	object_update_cb_func  object_update_cb;
	object_delete_cb_func  object_delete_cb;

    //neigh specfic	
    int                neigh_type;
    int                object_id;
    ip_address_t       nh;
    uint8_t            mac_addr[ETHER_ADDR_LEN];
    int                ifindex;               //linux ifindex
    char               ifname[IF_NAMESIZE];   //linux ifname
    int                hw_port;               // asic port
    int                vlan_id;
} async_obj_neigh_t;

async_obj_neigh_t** async_obj_neigh_find_or_new(ip_address_t *nh);
async_obj_neigh_t** async_obj_neigh_new(void);
async_obj_neigh_t** async_obj_neigh_find(ip_address_t *nh);
async_obj_neigh_t** async_obj_neigh_find_type(int type);


/******************************************************************************************/
/*     ASYNC_OBJ_TYPE_FIB                                                                 */
/******************************************************************************************/
#define ECMP_MAX_PATH  16
typedef struct async_obj_fib_s {
    //base object, must be same as async_object_t
    int              state;
    int              type;    
	pthread_mutex_t  lock;

	LIST_HEAD(obj_fib_parent_list_t, async_obj_entry_s)   parent_list;
	LIST_HEAD(obj_fib_child_list_t, async_obj_entry_s)    child_list;

    object_create_func     object_create;
    object_delete_func     object_delete;
	object_download_func   object_download;
	object_add_parent_func object_add_parent;

	object_create_cb_func  object_create_cb;
	object_update_cb_func  object_update_cb;
	object_delete_cb_func  object_delete_cb;
    
    //fib specfic	
    int           ifindex;              // linux ifindex
    ip_address_t  dst;                  // dst address
    int           dst_len;              // dst subnet prefix len

    int           is_ecmp;              // ecmp route flag
    int           fib_nhs;              // number of next hop
    ip_address_t  nh[ECMP_MAX_PATH];    // next hop
    int           ecmp_group_id;        // ecmp group id
}async_obj_fib_t;

async_obj_fib_t** async_obj_fib_find_or_new(ip_address_t *dst, int dst_len);
async_obj_fib_t** async_obj_fib_find(ip_address_t *dst, int dst_len);

//////////////////////////////////////////////////////////

typedef struct switch_object_db_s {
     //list of switch objects
    LIST_HEAD(switch_list_t, async_obj_entry_s)   switch_list;

    // list of vlan objects
    LIST_HEAD(vlan_list_t, async_obj_entry_s)     vlan_list;

    //list of interfaces objects
    LIST_HEAD(lif_list_t, async_obj_entry_s)      lif_list;

    //object store - in memory storage of async objects 
    // TODO need to be more efficient
    LIST_HEAD(async_obj_db_t, async_obj_entry_s)  object_db;
}switch_object_db_t;

typedef struct  async_queue_entry_s {
    TAILQ_ENTRY(async_queue_entry_s) _links;

    struct async_object_s  *obj; 
}async_queue_entry_t;

typedef struct async_workqueue_s {
    TAILQ_HEAD(obj_q_t, async_queue_entry_s)      object_queue;
	pthread_mutex_t                               object_lock;
	pthread_cond_t                                object_cond;
} async_workqueue_t;

typedef struct switch_netlink_s {
    struct  nl_sock *generic_sock;
    struct  nl_sock *ucsk;
    struct  nl_sock *mcsk;
    struct  nl_sock *route_event_sock;
    int     generic_sock_seq;

    int     ucsk_fd;
    int     mcsk_fd;
    int     route_event_fd;
    int     timer_fd;
    int     epoll_fd;   
    int     generic_sock_fd;
}switch_netlink_t;

typedef struct switch_service_s {
    // netlink 
    switch_netlink_t                              netlink;

    //object store - in memory storage of async objects 
    switch_object_db_t                            switch_db;

    //object work queue for object download
    async_workqueue_t                             asyncq;

}switch_service_t;

switch_service_t* system_get_instance();

int switchdev_async_obj_main(switch_service_t *sys);


#endif 

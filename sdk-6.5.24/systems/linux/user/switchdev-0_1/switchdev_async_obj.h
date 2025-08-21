#ifndef SWITCHDEV_ASYNC_OBJ_H
#define SWITCHDEV_ASYNC_OBJ_H


// async object base definition
enum object_state_e {
    ASYNC_OBJ_STATE_IDLE,
	ASYNC_OBJ_STATE_PENDING,
	ASYNC_OBJ_STATE_ACTIVE,
	ASYNC_OBJ_STATE_DELETING,
	ASYNC_OBJ_STATE_FAILED,
	ASYNC_OBJ_STATE_MAX    
};

enum async_obj_type_e {
    ASYNC_OBJ_TYPE_NEIGH,
    ASYNC_OBJ_TYPE_FIB,

    ASYNC_OBJ_TYPE_MAX    
};

typedef int (*object_create_func)(struct async_object_s *);
typedef int (*object_delete_func)(struct async_object_s *);
typedef int (*object_download_func)(struct async_object_s *);
typedef int (*object_add_parent_func)(struct async_object_s *, struct async_object_s *);
typedef int (*object_create_cb_func)(struct async_object_s *);
typedef int (*object_update_cb_func)(struct async_object_s *);
typedef int (*object_delete_cb_func)(struct async_object_s *);


typedef struct async_obj_entry_s {
	async_object_t  *obj;

    LIST_ENTRY(async_obj_entry_s) system_next;
}async_obj_entry_t;


typedef struct async_object_s {
    int              state;
    int              type;
	pthread_mutex_t  lock;

	LIST_HEAD(obj_parent_list_t, async_obj_entry_s)  parent_list;
	LIST_HEAD(obj_sibling_list_t, async_obj_entry_s)  sibling_list;

    object_create_func     object_create;
    object_delete_func     object_delete;
	object_download_func   object_download;
	object_add_parent_func object_add_parent;

	object_create_cb_func  object_create_cb;
	object_update_cb_func  object_update_cb;
	object_delete_cb_func  object_delete_cb;
} async_object_t;


/*
 * neigh async object
 */

#define ETHER_ADDR_LEN 6


typedef struct async_obj_neigh_s {
    //base object, must be same as async_object_t
    int              state;
    int              type;    
	pthread_mutex_t  lock;

	LIST_HEAD(obj_parent_list_t, async_object_list_entry_s)  parent_list;
	LIST_HEAD(obj_sibling_list_t, async_object_list_entry_s)  sibling_list;

    object_create_func     object_create;
    object_delete_func     object_delete;
	object_download_func   object_download;
	object_add_parent_func object_add_parent;

	object_create_cb_func  object_create_cb;
	object_update_cb_func  object_update_cb;
	object_delete_cb_func  object_delete_cb;

    //neigh specfic	
    int                object_id;
    ip_address_t       nh;
    uint8              mac_addr[ETHER_ADDR_LEN];
    local_interface_t *local_if;
} async_obj_neigh_t;

async_obj_neigh_t* async_obj_neigh_create(ip_address_t *nh);
async_obj_neigh_t* async_obj_neigh_find(ip_address_t *nh);
void async_obj_neigh_free(async_obj_neigh_t* neigh);

typedef struct neigh_entry_s {
	async_object_t  *obj;

    LIST_ENTRY(neigh_list_s) system_next;
}neigh_entry_t;



typedef struct ip_address_s {
    uint32 protocol;      //AF_INET4 AF_INET6
    uint32 ip[4];
}ip_address_t;

typedef struct async_obj_fib_s {
    //base object, must be same as async_object_t
    int              state;
    int              type;    
	pthread_mutex_t  lock;

	LIST_HEAD(obj_parent_list_t, async_object_list_entry_s)  parent_list;
	LIST_HEAD(obj_sibling_list_t, async_object_list_entry_s)  sibling_list;

    object_create_func     object_create;
    object_delete_func     object_delete;
	object_download_func   object_download;
	object_add_parent_func object_add_parent;

	object_create_cb_func  object_create_cb;
	object_update_cb_func  object_update_cb;
	object_delete_cb_func  object_delete_cb;
    
    //fib specfic	
    int           ifindex;      // linux ifindex
    ip_address_t  dst;          // dst address
    ip_address_t  nh;           // next hop
    int           dst_len;
}async_obj_fib_t;

async_obj_fib_t* async_obj_fib_create(int ifindex, ip_address_t *nh, ip_address_t *dst, int dst_len);
void async_obj_fib_free(async_obj_fib_t* fib);

typedef struct fib_entry_s {
	async_object_t  *obj;

    LIST_ENTRY(fib_list_s) system_next;
}fib_entry_t;


#endif 

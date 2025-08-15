#ifndef SWITCHDEV_NETLINK_H
#define SWITCHDEV_NETLINK_H

/*
 * This header includes definitions that are shared with kernel space and user
 * space. This header would be put in a place visible to user space.
 */

#define SWITCHDEV_GENL_NAME "SWITCHDEV"
#define SWITCHDEV_GENL_VERSION 1
#define SWITCHDEV_MC_GRP_NAME "SWITCHDEV_GRP"


/* commands  
 */
enum {
    SWITCHDEV_EVENT_KEEPALIVE,
    SWITCHDEV_EVENT_START,
    SWITCHDEV_EVENT_NETDEV,
    SWITCHDEV_EVENT_PORT,

    __SWITCHDEV_EVENT_MAX,
    SWITCHDEV_EVENT_MAX = __SWITCHDEV_EVENT_MAX - 1
};


enum {
    SWITCHDEV_A_NETDEV_EVENT_ID = 1,
    SWITCHDEV_A_NETDEV_PORT,
    SWITCHDEV_A_NETDEV_IF_NAME,
	
    __SWITCHDEV_A_NETDEV_EVENT_MAX,
    SWITCHDEV_A_NETDEV_EVENT_MAX = (__SWITCHDEV_A_NETDEV_EVENT_MAX - 1)
};

enum {
    SWITCHDEV_A_KEEPALIVE = 1,
    SWITCHDEV_A_START,

    __SWITCHDEV_A_MAX,
    SWITCHDEV_A_MAX = (__SWITCHDEV_A_MAX - 1)
};


enum {
    SWITCHDEV_A_PORT_EVENT_ID = 1,
    SWITCHDEV_A_PORT_IF_FLAG,
    SWITCHDEV_A_PORT_IF_PORT,
    SWITCHDEV_A_PORT_IF_NAME,
    SWITCHDEV_A_PORT_OBJ_ID,
    SWITCHDEV_A_PORT_VLAN_ID,
    SWITCHDEV_A_PORT_VLAN_FLAGS,
	
    __SWITCHDEV_A_PORT_MAX,
    SWITCHDEV_A_PORT_MAX = (__SWITCHDEV_A_PORT_MAX - 1)
};


//from include/linux/netdevice.h
/* netdevice notifier chain. Please remember to update netdev_cmd_to_name()
 * and the rtnetlink notification exclusion list in rtnetlink_event() when
 * adding new types.
 */
enum netdev_cmd {
	NETDEV_UP	= 1,	/* For now you can't veto a device up/down */
	NETDEV_DOWN,
	NETDEV_REBOOT,		/* Tell a protocol stack a network interface
				   detected a hardware crash and restarted
				   - we can use this eg to kick tcp sessions
				   once done */
	NETDEV_CHANGE,		/* Notify device state change */
	NETDEV_REGISTER,
	NETDEV_UNREGISTER,
	NETDEV_CHANGEMTU,	/* notify after mtu change happened */
	NETDEV_CHANGEADDR,	/* notify after the address change */
	NETDEV_PRE_CHANGEADDR,	/* notify before the address change */
	NETDEV_GOING_DOWN,
	NETDEV_CHANGENAME,
	NETDEV_FEAT_CHANGE,
	NETDEV_BONDING_FAILOVER,
	NETDEV_PRE_UP,
	NETDEV_PRE_TYPE_CHANGE,
	NETDEV_POST_TYPE_CHANGE,
	NETDEV_POST_INIT,
	NETDEV_PRE_UNINIT,
	NETDEV_RELEASE,
	NETDEV_NOTIFY_PEERS,
	NETDEV_JOIN,
	NETDEV_CHANGEUPPER,
	NETDEV_RESEND_IGMP,
	NETDEV_PRECHANGEMTU,	/* notify before mtu change happened */
	NETDEV_CHANGEINFODATA,
	NETDEV_BONDING_INFO,
	NETDEV_PRECHANGEUPPER,
	NETDEV_CHANGELOWERSTATE,
	NETDEV_UDP_TUNNEL_PUSH_INFO,
	NETDEV_UDP_TUNNEL_DROP_INFO,
	NETDEV_CHANGE_TX_QUEUE_LEN,
	NETDEV_CVLAN_FILTER_PUSH_INFO,
	NETDEV_CVLAN_FILTER_DROP_INFO,
	NETDEV_SVLAN_FILTER_PUSH_INFO,
	NETDEV_SVLAN_FILTER_DROP_INFO,
	NETDEV_OFFLOAD_XSTATS_ENABLE,
	NETDEV_OFFLOAD_XSTATS_DISABLE,
	NETDEV_OFFLOAD_XSTATS_REPORT_USED,
	NETDEV_OFFLOAD_XSTATS_REPORT_DELTA,
	NETDEV_XDP_FEAT_CHANGE,
};


// from include/net/switchdev.h
enum switchdev_notifier_type {
	SWITCHDEV_FDB_ADD_TO_BRIDGE = 1,
	SWITCHDEV_FDB_DEL_TO_BRIDGE,
	SWITCHDEV_FDB_ADD_TO_DEVICE,
	SWITCHDEV_FDB_DEL_TO_DEVICE,
	SWITCHDEV_FDB_OFFLOADED,
	SWITCHDEV_FDB_FLUSH_TO_BRIDGE,

	SWITCHDEV_PORT_OBJ_ADD, /* Blocking. */
	SWITCHDEV_PORT_OBJ_DEL, /* Blocking. */
	SWITCHDEV_PORT_ATTR_SET, /* May be blocking . */

	SWITCHDEV_VXLAN_FDB_ADD_TO_BRIDGE,
	SWITCHDEV_VXLAN_FDB_DEL_TO_BRIDGE,
	SWITCHDEV_VXLAN_FDB_ADD_TO_DEVICE,
	SWITCHDEV_VXLAN_FDB_DEL_TO_DEVICE,
	SWITCHDEV_VXLAN_FDB_OFFLOADED,

	SWITCHDEV_BRPORT_OFFLOADED,
	SWITCHDEV_BRPORT_UNOFFLOADED,
	SWITCHDEV_BRPORT_REPLAY,
};

enum switchdev_obj_id {
	SWITCHDEV_OBJ_ID_UNDEFINED,
	SWITCHDEV_OBJ_ID_PORT_VLAN,
	SWITCHDEV_OBJ_ID_PORT_MDB,
	SWITCHDEV_OBJ_ID_HOST_MDB,
	SWITCHDEV_OBJ_ID_MRP,
	SWITCHDEV_OBJ_ID_RING_TEST_MRP,
	SWITCHDEV_OBJ_ID_RING_ROLE_MRP,
	SWITCHDEV_OBJ_ID_RING_STATE_MRP,
	SWITCHDEV_OBJ_ID_IN_TEST_MRP,
	SWITCHDEV_OBJ_ID_IN_ROLE_MRP,
	SWITCHDEV_OBJ_ID_IN_STATE_MRP,
};

typedef struct local_interface_s {
    int  ifindex;                 // linux ifindex
    char name[IF_NAMESIZE+1]; 

    /* hardware information */
    int hw_port;                  // hardware port id
    int l3_intf;
    int vlan;                     // should always be 4095 for routed port

    LIST_ENTRY(local_interface_s) system_next;
}local_interface_t;

void local_if_finalize(local_interface_t* lif);
local_interface_t* local_if_create(char* ifname, int hw_port);
local_interface_t* local_if_find_by_ifindex(int ifindex);

typedef struct fib_entry_s {
	int  ifindex;      // linux ifindex
	int  ipv4_dst;     // dst address
	int  nh;           // next hop
    int  dst_len;

    LIST_ENTRY(fib_entry_s) system_next;
}fib_entry_t;
void fib_entry_finalize(fib_entry_t* fib);
fib_entry_t* fib_entry_create(int ifindex, int nh, int ipv4_dst, int dst_len);
fib_entry_t* fib_entry_find_by_nh(int nh);


typedef struct switch_service_s {
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

   //list of interfaces managed by switchdev module
   LIST_HEAD(lif_list, local_interface_s) lif_list;

   //list of FIB pending download to ASIC
   LIST_HEAD(fib_list, fib_entry_s) fib_list;


}switch_service_t;

int switchdev_netlink_main(void);
switch_service_t* system_get_instance();

#endif 

#ifndef _BCM_SWITCHDEV_H_
#define _BCM_SWITCHDEV_H_



/*****************************************************************************************/
/*                              switchdev                                                */
/*****************************************************************************************/


struct bcm_switchdev_event_work {
	struct work_struct work;
	netdevice_tracker dev_tracker;
	union {
		struct switchdev_notifier_fdb_info fdb_info;
		struct switchdev_notifier_vxlan_fdb_info vxlan_fdb_info;
	};
	struct net_device *dev;
	unsigned long event;
};

struct bcm_switchdev {
	struct list_head bridge_list;
	bool bridge_8021q_exists;
	struct notifier_block swdev_nb_blk;
	struct notifier_block swdev_nb;
    struct notifier_block netdev_nb;
};


/* commands  
 * also used as NETLINK attribute type value
 */
enum {
    SWITCHDEV_EVENT_UNSPEC = 0,
    SWITCHDEV_EVENT_ECHO,
	SWITCHDEV_EVENT_NETDEV,

    __SWITCHDEV_EVENT_MAX,
    SWITCHDEV_EVENT_MAX = __SWITCHDEV_EVENT_MAX - 1
};

struct switchdev_ipc_msg {
	unsigned int		type;
	unsigned int		sz;
	unsigned char		payload[];
};


struct switchdev_server_config {
	unsigned int		flags;
	unsigned int		state;
	short			    signing;
	unsigned short		ipc_timeout;
	unsigned long		ipc_last_active;
};


struct switchdev_netdev_event {
	uint8_t  name[16];
	uint32_t event;
};



#define TEST_GENL_MSG_FROM_KERNEL "Hello from switchdev Kernel!"

#endif

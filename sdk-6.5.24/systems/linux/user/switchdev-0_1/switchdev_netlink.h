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

    __SWITCHDEV_EVENT_MAX,
    SWITCHDEV_EVENT_MAX = __SWITCHDEV_EVENT_MAX - 1
};



enum {
	SWITCHDEV_A_NETDEV_EVENT_ID = 1,
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



#endif 

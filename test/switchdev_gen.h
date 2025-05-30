#ifndef SWITCHDEV_H
#define SWITCHDEV_H

/*
 * This header includes definitions that are shared with kernel space and user
 * space. This header would be put in a place visible to user space.
 */

#define SWITCHDEV_GENL_NAME "SWITCHDEV"
#define SWITCHDEV_GENL_VERSION 1
#define SWITCHDEV_MC_GRP_NAME "SWITCHDEV_GRP"

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


#endif 

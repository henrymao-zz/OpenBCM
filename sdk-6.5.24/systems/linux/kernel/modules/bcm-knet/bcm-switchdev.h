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
};


/* netlink attributes */
enum {
    SWITCHDEV_A_UNSPEC,
    SWITCHDEV_A_MSG,
    __SWITCHDEV_A_MAX,
};

#define SWITCHDEV_A_MAX (__SWITCHDEV_A_MAX - 1)
 
/* attribute policy */
static struct nla_policy switchdev_genl_policy[SWITCHDEV_A_MAX + 1] = {
      [SWITCHDEV_A_MAX] = { .type = NLA_NUL_STRING },

};


/* commands  */
enum {
    SWITCHDEV_C_UNSPEC,
    SWITCHDEV_C_ECHO,
    __SWITCHDEV_C_MAX,
};
#define SWITCHDEV_C_MAX (__SWITCHDEV_C_MAX - 1)



/* netlink family definition */
static struct genl_family switchdev_genl_family = {
    .id = GENL_ID_GENERATE,   
    .hdrsize = 0,             
    .name = "SWITCHDEV",      
    .version = 1,
    .maxattr = SWITCHDEV_A_MAX,
};

/* operation definition */
static struct genl_ops switchdev_genl_ops_echo = {
    .cmd = SWITCHDEV_C_ECHO,
    .flags = 0,
    .policy = switchdev_genl_policy,
    .doit = switchdev_echo,
    .dumpit = NULL,
};



#endif

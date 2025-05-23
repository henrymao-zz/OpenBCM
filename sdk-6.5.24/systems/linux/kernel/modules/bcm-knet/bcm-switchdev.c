#include <gmodule.h>
#include <linux-bde.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/skbuff.h>
#include <linux/if_vlan.h>
#include <linux/if_bridge.h>
#include <linux/workqueue.h>
#include <linux/jiffies.h>
#include <linux/rtnetlink.h>
#include <linux/netlink.h>
#include <net/switchdev.h>
#include <net/vxlan.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <kcom.h>
#include <bcm-knet.h>


static struct workqueue_struct *swdev_wq;


/*****************************************************************************************/
/*                             netlink                                                   */
/*****************************************************************************************/
 
 
static struct genl_multicast_group switchdev_genl_mcgrp = {
    .name = "SWITCHDEV_GRP",
};

static inline int genl_msg_prepare_usr_msg(u8 cmd, size_t size, pid_t pid, struct sk_buff **skbp)
{
    struct sk_buff *skb;

    /* create a new netlink msg */
    skb = genlmsg_new(size, GFP_KERNEL);
    if (skb == NULL) {
        return -ENOMEM;  
    }

    /* Add a new netlink message to an skb */
    genlmsg_put(skb, pid, 0, &doc_exmpl_genl_family, 0, cmd);

    *skbp = skb;
    return 0;
}

static inline int genl_msg_mk_usr_msg(struct sk_buff *skb, int type, void *data, int len)
{
    int rc;

    /* add a netlink attribute to a socket buffer */
    if ((rc = nla_put(skb, type, len, data)) != 0) {
        return rc;
    }
    return 0;
}

/**
* genl_msg_send_to_user 
*/
int genl_msg_send_to_user(void *data, int len, pid_t pid)
{
    struct sk_buff *skb;
    size_t size;
    void *head;
    int rc;

    size = nla_total_size(len); /* total length of attribute including padding */

    rc = genl_msg_prepare_usr_msg(SWITCHDEV_C_ECHO, size, pid, &skb);
    if (rc) {
        return rc;
    }

    rc = genl_msg_mk_usr_msg(skb, SWITCHDEV_A_MSG, data, len);
    if (rc) {
        kfree_skb(skb);
        return rc;
    }

    head = genlmsg_data(nlmsg_data(nlmsg_hdr(skb)));

    rc = genlmsg_end(skb, head);
    if (rc < 0) {
        kfree_skb(skb);
        return rc;
    }

    rc = genlmsg_unicast(&init_net, skb, pid);
    if (rc < 0) {
        return rc;
    }

    return 0;
}

static int switchdev_echo(struct sk_buff *skb, struct genl_info *info)
{
    /* message handling code goes here; return 0 on success, negative values on failure */
    struct nlmsghdr *nlhdr;
    struct genlmsghdr *genlhdr;
    struct nlattr *nlh;
    char *str;
    int ret;

    nlhdr = nlmsg_hdr(skb);
    genlhdr = nlmsg_data(nlhdr);
    nlh = genlmsg_data(genlhdr);
    str = nla_data(nlh);

    printk("switchdev_echo get: %s\n", str);

    ret = genl_msg_send_to_user(TEST_GENL_MSG_FROM_KERNEL,
            strlen(TEST_GENL_MSG_FROM_KERNEL) + 1,  nlhdr->nlmsg_pid);

    return ret;
}

static int genetlink_init(void)
{
    int rc;
 
    /**
     * 1. Registering A Family
     * This function doesn't exist past linux 3.12
     */
    rc = genl_register_family(&switchdev_genl_family);
    if (rc != 0)
        goto err_out1;
 
    rc = genl_register_ops(&switchdev_genl_family, &switchdev_genl_ops_echo);
    if (rc != 0)
        goto err_out2;
 
    /*
     * for multicast
     */
    rc = genl_register_mc_group(&switchdev_genl_family, &switchdev_genl_mcgrp);
    if (rc != 0)
        goto err_out3;
 
    printk("switchdev_genl_mcgrp.id=%d", switchdev_genl_mcgrp.id);
    printk("genetlink_init OK");
    return 0;
 
err_out3:
    genl_unregister_ops(&switchdev_genl_family, &switchdev_genl_ops_echo);
err_out2:
    genl_unregister_family(&switchdev_genl_family);
err_out1:
    printk("Error occured while inserting switchdev netlink module\n");
    return rc;
}
 
static void genetlink_exit(void)
{
    printk("switchdev Netlink Module unloaded.");
 
    genl_unregister_mc_group(&switchdev_genl_family, &switchdev_genl_mcgrp);
    genl_unregister_ops(&switchdev_genl_family, &switchdev_genl_ops_echo);
    genl_unregister_family(&switchdev_genl_family);
}



/*****************************************************************************************/
/*                             switchdev                                                 */
/*****************************************************************************************/


static void bcm_fdb_event_work(struct work_struct *work)
{
    //struct switchdev_notifier_fdb_info *fdb_info;
    struct bcm_switchdev_event_work *switchdev_work;
    //struct prestera_port *port;
    struct net_device *dev;

    switchdev_work = container_of(work, struct bcm_switchdev_event_work, work);
    dev = switchdev_work->dev;

    rtnl_lock();

#if 0
    port = prestera_port_dev_lower_find(dev);
    if (!port)
        goto out_unlock;

    switch (switchdev_work->event) {
    case SWITCHDEV_FDB_ADD_TO_DEVICE:
        fdb_info = &switchdev_work->fdb_info;
        if (!fdb_info->added_by_user || fdb_info->is_local)
            break;

        err = bcm_port_fdb_set(port, fdb_info, true);
        if (err)
            break;

        bcm_fdb_offload_notify(port, fdb_info);
        break;

    case SWITCHDEV_FDB_DEL_TO_DEVICE:
        fdb_info = &switchdev_work->fdb_info;
        bcm_port_fdb_set(port, fdb_info, false);
        break;
    }

out_unlock:
#endif
    rtnl_unlock();

    kfree(switchdev_work->fdb_info.addr);
    kfree(switchdev_work);
    dev_put(dev);
}

extern bool bkn_port_dev_check(const struct net_device *dev);

static int bcm_switchdev_event(struct notifier_block *unused,
                    unsigned long event, void *ptr)
{
    struct net_device *dev = switchdev_notifier_info_to_dev(ptr);
    struct switchdev_notifier_fdb_info *fdb_info;
    struct switchdev_notifier_info *info = ptr;
    struct bcm_switchdev_event_work *switchdev_work;
    struct net_device *upper;
    //int err;

    printk("bcm_switchdev_event \n");
    if (event == SWITCHDEV_PORT_ATTR_SET) {
#if 0
        err = switchdev_handle_port_attr_set(dev, ptr,
                             bkn_port_dev_check,
                             bcm_port_obj_attr_set);
        return notifier_from_errno(err);
#endif
        return NOTIFY_DONE;
    }

    if (!bkn_port_dev_check(dev))
        return NOTIFY_DONE;


    switch (event) {
    case SWITCHDEV_FDB_ADD_TO_DEVICE:
    case SWITCHDEV_FDB_DEL_TO_DEVICE:
        fdb_info = container_of(info,
                    struct switchdev_notifier_fdb_info,
                    info);

        INIT_WORK(&switchdev_work->work, bcmsw_fdb_event_work);
        memcpy(&switchdev_work->fdb_info, ptr,
               sizeof(switchdev_work->fdb_info));

        switchdev_work->fdb_info.addr = kzalloc(ETH_ALEN, GFP_ATOMIC);
        if (!switchdev_work->fdb_info.addr)
            goto out_bad;

        ether_addr_copy((u8 *)switchdev_work->fdb_info.addr,
                fdb_info->addr);
        dev_hold(dev);
        break;

    default:
        kfree(switchdev_work);
        return NOTIFY_DONE;
    }

    queue_work(swdev_wq, &switchdev_work->work);
    return NOTIFY_DONE;

out_bad:
    return NOTIFY_BAD;
}


int switchdev_port_obj_add_netlink(struct net_device *dev, const void *ctx,
                 const struct switchdev_obj *obj,
                 struct netlink_ext_ack *extack)
{
    printk("switchdev_port_obj_add_netlink \n");
    return 0;
}
int switchdev_port_obj_del_netlink(struct net_device *dev, const void *ctx,
                 const struct switchdev_obj *obj)
{
    printk("switchdev_port_obj_del_netlink \n");
    return 0;
}
int switchdev_port_obj_attr_set_netlink(struct net_device *dev, const void *ctx,
                  const struct switchdev_attr *attr,
                  struct netlink_ext_ack *extack)
{
    printk("switchdev_port_obj_attr_set_netlink \n");
    return 0;
}


static int bcm_switchdev_blk_event(struct notifier_block *unused,
                    unsigned long event, void *ptr)
{
    struct net_device *dev = switchdev_notifier_info_to_dev(ptr);
    int err;

    switch (event) {
    case SWITCHDEV_PORT_OBJ_ADD:
        err = switchdev_handle_port_obj_add(dev, ptr,
                            bkn_port_dev_check,
                            switchdev_port_obj_add_netlink);
        break;
    case SWITCHDEV_PORT_OBJ_DEL:
        err = switchdev_handle_port_obj_del(dev, ptr,
                            bkn_port_dev_check,
                            switchdev_port_obj_del_netlink);
        break;
    case SWITCHDEV_PORT_ATTR_SET:
        err = switchdev_handle_port_attr_set(dev, ptr,
                             bkn_port_dev_check,
                             switchdev_port_obj_attr_set_netlink);
        break;
    default:
        return NOTIFY_DONE;
    }

    return notifier_from_errno(err);
}


static int bcm_switchdev_handler_init(void)
{
    int err;

    swdev->swdev_nb.notifier_call = bcm_switchdev_event;
    err = register_switchdev_notifier(&swdev->swdev_nb);
    if (err)
        goto err_register_swdev_notifier;

    swdev->swdev_nb_blk.notifier_call = bcm_switchdev_blk_event;
    err = register_switchdev_blocking_notifier(&swdev->swdev_nb_blk);
    if (err)
        goto err_register_blk_swdev_notifier;

    return 0;

err_register_blk_swdev_notifier:
    unregister_switchdev_notifier(&swdev->swdev_nb);
err_register_swdev_notifier:
    destroy_workqueue(swdev_wq);
    return err;
}



int bcm_switchdev_init_internal(void)
{
    struct bcm_switchdev *swdev;
    int err;

    swdev = kzalloc(sizeof(*swdev), GFP_KERNEL);
    if (!swdev)
        return -ENOMEM;

    sw->swdev = swdev;
    swdev->sw = sw;

    INIT_LIST_HEAD(&swdev->bridge_list);

    swdev_wq = alloc_ordered_workqueue("%s_ordered", 0, "bcm_switchdev");
    if (!swdev_wq) {
        err = -ENOMEM;
        goto err_alloc_wq;
    }

    err = bcm_switchdev_handler_init(swdev);
    if (err)
        goto err_swdev_init;

    return 0;

//err_fdb_init:
err_swdev_init:
    destroy_workqueue(swdev_wq);
err_alloc_wq:
    kfree(swdev);

    return err;
}


int bcm_switchdev_init(void)
{
    int err = 0;
        
    printk("Initializing switchdev...\n");

    err = bcm_switchdev_init_internal();
    if (err)
    goto err_swdev_init;


    //initialize netlink 
    genetlink_init();

err_swdev_init:
    return err;    
}



int bcm_switchdev_uninit(void)
{

    genetlink_exit();

    return 0;
}

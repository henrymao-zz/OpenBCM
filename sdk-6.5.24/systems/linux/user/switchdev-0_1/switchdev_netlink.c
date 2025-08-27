/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Generic Netlink libnl example program
 *
 * An example on how to use the libnl library for communicating over Generic
 * Netlink with kernel modules, with unicast and multicast group messages.
 *
 *  Copyright (c) 2022 Yaroslav de la Peña Smirnov <yps@yaroslavps.com>
 */
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/queue.h>

#include <netlink/socket.h>
#include <netlink/netlink.h>
#include <netlink/msg.h>
#include <netlink/attr.h>
#include <netlink/types.h>
#include <netlink/route/addr.h>
#include <netlink/genl/ctrl.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/family.h>
#include <netlink/route/link.h>
#include <net/if.h>

#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <fcntl.h>
#include <linux/netdevice.h>
#include <linux/if_bridge.h>

#include "switchdev_netlink.h"
#include "switchdev_async_obj.h"

#define prerr(...) fprintf(stderr, "error: " __VA_ARGS__)


#if 0
/*
 * switchdev netlink handlers
 */
static int switchdev_ops_ack_handler(struct nl_msg *msg, void *arg)
{
    bool *acked = arg;

    *acked = true;

    return NL_STOP;
}

static int switchdev_ops_seq_check_handler(struct nl_msg *msg, void *arg)
{
    unsigned int *seq = arg;
    struct nlmsghdr *hdr = nlmsg_hdr(msg);

    if (hdr->nlmsg_seq != *seq)
        return NL_SKIP;

    return NL_OK;
}
int switchdev_ops_send_and_recv(switch_service_t *sys, struct nl_msg *msg,
                       int (*valid_handler)(struct nl_msg *, void *),
                       void *valid_data)
{
    int ret;
    struct nl_cb *cb;
    struct nl_cb *orig_cb;
    bool acked;
    unsigned int seq = sys->generic_sock_seq++;
    int err;

    ret = nl_send_auto(sys->generic_sock, msg);
    nlmsg_free(msg);
    if (ret < 0) {
        printf("ops_send_and_recv send_auto ret %d\n", ret);
        return ret;
    }

    orig_cb = nl_socket_get_cb(sys->generic_sock);
    cb = nl_cb_clone(orig_cb);
    nl_cb_put(orig_cb);
    if (!cb)
        return -ENOMEM;

    nl_cb_set(cb, NL_CB_ACK, NL_CB_CUSTOM, switchdev_ops_ack_handler, &acked);
    nl_cb_set(cb, NL_CB_SEQ_CHECK, NL_CB_CUSTOM, switchdev_ops_seq_check_handler, &seq);
    if (valid_handler)
        nl_cb_set(cb, NL_CB_VALID, NL_CB_CUSTOM, valid_handler, valid_data);

    /* There is a bug in libnl. When implicit sequence number checking is in
     * use the expected next number is increased when NLMSG_DONE is
     * received. The ACK which comes after that correctly includes the
     * original sequence number. However libnl is checking that number
     * against the incremented one and therefore ack handler is never called
     * and nl_recvmsgs finished with an error. To resolve this, custom
     * sequence number checking is used here.
     */

    acked = false;

    while (!acked)
    {
        ret = nl_recvmsgs(sys->generic_sock, cb);
        if (ret)
        {
            //printf("ops_send_and_recv nl_recvmsgs ret %d  %s\n", ret, nl_geterror(ret));
            err = ret;
            goto put_cb;
        }
    }

    err = 0;
put_cb:
    nl_cb_put(cb);
    return err;
}
#endif


static int handle_switchdev_port_vlan_add(struct nlattr *tb[])
{
# if 0
    char *ifname;
    int   port, if_flag;
    int   vlan, vlan_flags;
    int   err = 0;
    bool  untagged;
    bcm_pbmp_t pbmp, ubmp;

    port = nla_get_u32(tb[SWITCHDEV_A_PORT_IF_PORT]);
    if_flag = nla_get_u32(tb[SWITCHDEV_A_PORT_IF_FLAG]);
    ifname = nla_get_string(tb[SWITCHDEV_A_PORT_IF_NAME]);
    vlan = nla_get_u32(tb[SWITCHDEV_A_PORT_VLAN_ID]);
    vlan_flags = nla_get_u32(tb[SWITCHDEV_A_PORT_VLAN_FLAGS]);
    
    printf("switchdev_port_vlan_add name %s port %d vlan %d flag 0x%x vlan_flags 0x%x\n", 
        ifname, port, vlan, if_flag, vlan_flags);
    
    //TODO check flag for Bridge root
    
    
    //check vlan_flags
    //pvid = vlan_flags & BRIDGE_VLAN_INFO_PVID;
    untagged = vlan_flags & BRIDGE_VLAN_INFO_UNTAGGED;
    
    bcm_vlan_create(0, vlan); // create if does not exist
    
    //config port
    /* Untagged vlan classification */
    BCM_PBMP_PORT_SET(pbmp, port);

    if (untagged) {
        BCM_PBMP_PORT_SET(ubmp, port);
    } else {
        BCM_PBMP_CLEAR(ubmp);
    }

    err = bcm_vlan_port_add(0, vlan, pbmp, ubmp);

    return err;
#endif
    return 0;
}

static int handle_switchdev_port_obj_add(struct nlattr *tb[])
{
	int   obj_id;
	int   err = 0;

	obj_id = nla_get_u32(tb[SWITCHDEV_A_PORT_OBJ_ID]);

	switch (obj_id) {
		case SWITCHDEV_OBJ_ID_PORT_VLAN:
		    err = handle_switchdev_port_vlan_add(tb);
			break;
        
        case SWITCHDEV_OBJ_ID_PORT_MDB:
		case SWITCHDEV_OBJ_ID_HOST_MDB:
		default:
		    break;
    }
	
	return err;
}



static int handle_switchdev_port_vlan_del(struct nlattr *tb[])
{
#if 0
	char *ifname;
	int   port, if_flag;
	int   vlan, vlan_flags;
	int   err = 0;
    bcm_pbmp_t pbmp;

    port = nla_get_u32(tb[SWITCHDEV_A_PORT_IF_PORT]);
	if_flag = nla_get_u32(tb[SWITCHDEV_A_PORT_IF_FLAG]);
    ifname = nla_get_string(tb[SWITCHDEV_A_PORT_IF_NAME]);
	vlan = nla_get_u32(tb[SWITCHDEV_A_PORT_VLAN_ID]);
	vlan_flags = nla_get_u32(tb[SWITCHDEV_A_PORT_VLAN_FLAGS]);
	


	printf("switchdev_port_vlan_del name %s port %d vlan %d flag 0x%x vlan_flags 0x%x\n", 
            ifname, port, vlan, if_flag, vlan_flags);

	//TODO check flag for Bridge root

	//config port
	/* Untagged vlan classification */
    BCM_PBMP_PORT_SET(pbmp, port);

    err = bcm_vlan_port_remove(0, vlan, pbmp);

	return err;
#endif
   return 0;
}

static int handle_switchdev_port_obj_del(struct nlattr *tb[])
{
	int   obj_id;
	int   err = 0;

	obj_id = nla_get_u32(tb[SWITCHDEV_A_PORT_OBJ_ID]);

	switch (obj_id) {
		case SWITCHDEV_OBJ_ID_PORT_VLAN:
		    err = handle_switchdev_port_vlan_del(tb);
			break;
        
        case SWITCHDEV_OBJ_ID_PORT_MDB:
		case SWITCHDEV_OBJ_ID_HOST_MDB:
		default:
		    break;
    }
	
	return err;
}


static int handle_switchdev_port_event(struct nl_msg *msg)
{
	struct genlmsghdr *genlhdr = nlmsg_data(nlmsg_hdr(msg));
	struct nlattr	  *tb[SWITCHDEV_A_PORT_MAX + 1];
    int   err = 0;
	int   event;


    printf("switchdev port event received:\n");
	/* Parse the attributes */
	err = nla_parse(tb, SWITCHDEV_A_PORT_MAX, genlmsg_attrdata(genlhdr, 0),
			genlmsg_attrlen(genlhdr, 0), NULL);
	if (err) {
		prerr("unable to parse message: %s\n", strerror(-err));
		return NL_SKIP;
	}

    event = nla_get_u32(tb[SWITCHDEV_A_PORT_EVENT_ID]);

	switch (event) {
        case SWITCHDEV_PORT_OBJ_ADD:
            err = handle_switchdev_port_obj_add(tb);
		    break;
	    case SWITCHDEV_PORT_OBJ_DEL:
            err = handle_switchdev_port_obj_del(tb);
		    break;
	   default:
	       break;

	}
	return err;
}

void switchdev_event_handler_rtm_newaddr(struct nl_object *obj, void *arg)
{
    async_obj_intf_t   **local_if  = NULL;
    async_obj_l3host_t **l3host    = NULL;    
    struct nl_addr      *nl_addr   = NULL;
    struct rtnl_addr    *addr      = NULL;
    uint32_t             ifindex;    
    char                 ifname[IF_NAMESIZE+1];
    uint32_t             ipv4_addr, *ipv6_addr;
    ip_address_t         host;


    addr = (struct rtnl_addr *)obj;

    ifindex = rtnl_addr_get_ifindex(addr);
    if_indextoname(ifindex, ifname);

    local_if = async_obj_intf_find(ifindex);
    if(!local_if || !(*local_if)) {
        printf("handle newaddr failed to find local if %d %s\n", ifindex, ifname);
        return;
    }

    nl_addr = rtnl_addr_get_local(addr);

    if (rtnl_addr_get_family(addr) == AF_INET) {
        ipv4_addr     = *(uint32_t *) nl_addr_get_binary_addr(nl_addr);
        host.protocol = AF_INET;
        host.ip[0]    = ntohl(ipv4_addr);

        //printf("ipv4 l3 host add: index %d %s address 0x%x prefix %d\n",
        //        ifindex, ifname, ipv4_addr, prefixlen);
    } else if  (rtnl_addr_get_family(addr) == AF_INET6) {
        ipv6_addr     = (uint32_t *) nl_addr_get_binary_addr(nl_addr);
        host.protocol = AF_INET6;        
        memcpy(host.ip, ipv6_addr, 16);

        //printf("ipv6 l3 host add: index %d %s address 0x%x 0x%x 0x%x 0x%x  prefix %d\n",
        //        ifindex, ifname, ipv6_addr[0], ipv6_addr[1], ipv6_addr[2], ipv6_addr[3], prefixlen);

    }

    l3host = async_obj_l3host_find_or_new(&host);

    if (!l3host || !(*l3host)) {
        printf("handle_rtm_newaddr l3host new failed\n");
        return;
    }
    (*l3host)->lookup_class = 1;

    //may need to add host neigh as parent

    (*l3host)->object_create((async_object_t *)(*l3host));
    (*l3host)->object_download((async_object_t *)(*l3host));

    return;
}

void switchdev_event_handler_rtm_deladdr(struct nl_object *obj, void *arg)
{
    async_obj_intf_t   **local_if  = NULL;
    async_obj_l3host_t **l3host    = NULL;    
    struct nl_addr      *nl_addr   = NULL;
    struct rtnl_addr    *addr      = NULL;
    uint32_t             ifindex;    
    char                 ifname[IF_NAMESIZE+1];
    uint32_t             ipv4_addr, *ipv6_addr;
    ip_address_t         host;


    addr = (struct rtnl_addr *)obj;

    ifindex = rtnl_addr_get_ifindex(addr);
    if_indextoname(ifindex, ifname);

    local_if = async_obj_intf_find(ifindex);
    if(!local_if || !(*local_if)) {
        printf("handle deladdr failed to find local if %d %s\n", ifindex, ifname);
        return;
    }

    nl_addr = rtnl_addr_get_local(addr);

    if (rtnl_addr_get_family(addr) == AF_INET) {
        ipv4_addr     = *(uint32_t *) nl_addr_get_binary_addr(nl_addr);
        host.protocol = AF_INET;
        host.ip[0]    = ntohl(ipv4_addr);

        //printf("ipv4 l3 host add: index %d %s address 0x%x prefix %d\n",
        //        ifindex, ifname, ipv4_addr, prefixlen);
    } else if  (rtnl_addr_get_family(addr) == AF_INET6) {
        ipv6_addr     = (uint32_t *) nl_addr_get_binary_addr(nl_addr);
        host.protocol = AF_INET6;        
        memcpy(host.ip, ipv6_addr, 16);

        //printf("ipv6 l3 host add: index %d %s address 0x%x 0x%x 0x%x 0x%x  prefix %d\n",
        //        ifindex, ifname, ipv6_addr[0], ipv6_addr[1], ipv6_addr[2], ipv6_addr[3], prefixlen);

    }

    l3host = async_obj_l3host_find(&host);

    if (!l3host || !(*l3host)) {
        printf("handle_rtm_deladdr l3host find failed\n");
        return;
    }
    (*l3host)->lookup_class = 1;

    (*l3host)->object_delete((async_object_t **)l3host);

    return;
}

#ifndef NDA_RTA
#define NDA_RTA(r) \
    ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct ndmsg))))
#endif

void ifm_parse_rtattr(struct rtattr **tb, int max, struct rtattr *rta, int len)
{
    while (RTA_OK(rta, len))
    {
        if (rta->rta_type <= max)
            tb[rta->rta_type] = rta;
        rta = RTA_NEXT(rta, len);
    }
}


void switchdev_event_handler_rtm_newlink(struct nl_object *obj, void *arg)
{
    struct rtnl_link  *link = (struct rtnl_link *)obj;
    uint32_t           ifindex = 0;
    char              *ifname;
    //int                op_state = 0;
    int                link_flag = 0;
    async_obj_intf_t **local_if = NULL;
    

    ifindex    = rtnl_link_get_ifindex(link);
    //op_state   = rtnl_link_get_operstate(link);
    ifname     = rtnl_link_get_name(link);
    link_flag  = rtnl_link_get_flags(link);

    //printf("handle newlink for %d %s state %d\n", ifindex, ifname, op_state);

    local_if = async_obj_intf_find(ifindex);
    if(!local_if||!(*local_if)) {
        printf("handle rmt_newlink failed to find local if %d %s\n", ifindex, ifname);
        return;
    }

    
    //update 
    if (link_flag & IFF_LOWER_UP) {
        (*local_if)->admin_state         = true;
        (*local_if)->admin_state_changed = true;
    } else if (!(link_flag & IFF_LOWER_UP)) {
        (*local_if)->admin_state         = false;
        (*local_if)->admin_state_changed = true;
    }

    (*local_if)->object_download((async_object_t *)(*local_if));

    return;
}

static int switchdev_handle_rtm_neigh(struct nlmsghdr *n)
{
    struct ndmsg  *ndm = NLMSG_DATA(n);
    struct rtattr *tb[NDA_MAX + 1] = {0};	
    int            len = n->nlmsg_len;
    int            is_del = 0;
    int            msgtype = n->nlmsg_type;
    uint8_t        mac_addr[ETHER_ADDR_LEN];
    ip_address_t   ip_addr;
    int            rc = 0;
    char           ifname[IF_NAMESIZE+1];
    async_obj_intf_t **intf     = NULL;
    switch_service_t  *sys      = NULL;

    if ((sys = system_get_instance()) == NULL)
        return 0;    

    if (n->nlmsg_type == NLMSG_DONE) {
        return 0;
    }

    //printf("handle neigh msg %d if_index %d state %d type %d\n", 
    //       msgtype, ndm->ndm_ifindex, ndm->ndm_state, ndm->ndm_type);

    /* process msg_type RTM_NEWNEIGH, RTM_GETNEIGH, RTM_DELNEIGH */
    if (n->nlmsg_type != RTM_NEWNEIGH && n->nlmsg_type  != RTM_DELNEIGH )
        return(0);

    ifm_parse_rtattr(tb, NDA_MAX, NDA_RTA(ndm), len);


    //only handle reachable and delete 
    if (msgtype != RTM_DELNEIGH) {
        if ((ndm->ndm_state != NUD_PERMANENT) &&
            (ndm->ndm_state != NUD_REACHABLE)) {
            return (0);
        }
    } else {
        if (ndm->ndm_state != NUD_FAILED) {
            return (0);
        }
        is_del = 1;
    }

    if (!tb[NDA_DST] || ndm->ndm_type != RTN_UNICAST)
    {
        return(0);
    }

    if_indextoname(ndm->ndm_ifindex, ifname);

    intf = async_obj_intf_find(ndm->ndm_ifindex);
    if (!intf || !(*intf)) {
        return 0;
    }
    //printf("handle neigh msg %d if_index %d %s\n", msgtype, ndm->ndm_ifindex, ifname);

    memset(&ip_addr, 0, sizeof(ip_addr));
    ip_addr.protocol = ndm->ndm_family;
    memcpy(ip_addr.ip, RTA_DATA(tb[NDA_DST]), RTA_PAYLOAD(tb[NDA_DST]));

    if (!is_del && tb[NDA_LLADDR]) {
        memcpy(mac_addr, RTA_DATA(tb[NDA_LLADDR]), RTA_PAYLOAD(tb[NDA_LLADDR]));
    }

    //printf("handle neigh msg %d if_index %d %s, ip_addr 0x%x mac %x:%x:%x:%x:%x:%x \n",
    //       msgtype, ndm->ndm_ifindex, ifname, ipv4_addr, 
	//       mac_addr[5], mac_addr[4],mac_addr[3], mac_addr[2],mac_addr[1],mac_addr[0]);        
    if (msgtype != RTM_DELNEIGH) { 
        async_obj_neigh_t   **neigh = NULL;

        neigh = async_obj_neigh_find_or_new(&ip_addr);
        if (!neigh) {
            return 0;
        }
        memcpy((*neigh)->mac_addr, mac_addr, ETHER_ADDR_LEN);
        (*neigh)->ifindex = ndm->ndm_ifindex;

        //TODO, handle neigh MAC change case
        (*neigh)->object_create((async_object_t *)(*neigh));

        // special handling for neigh object, trigger download only if there is child
        if (!LIST_EMPTY(&(*neigh)->child_list)) {
            (*neigh)->object_download((async_object_t *)*neigh);
        }
        return rc;
    } else {
        async_obj_neigh_t   **neigh = NULL;
        //del, remove l3 egress object
        neigh = async_obj_neigh_find(&ip_addr);
        if(!neigh) {
            //printf("switchdev_handle_rtm_neigh neigh not found for 0x%x\n", ipv4_addr);
            return 0;
        }
        (*neigh)->object_delete((async_object_t **)neigh);
    }

    return (rc);
}

#if 0
static int ipneigh_get_handler(struct nl_msg *msg, void *arg)
{
    struct nlmsghdr *nlh = nlmsg_hdr(msg);
    struct ndmsg    *ndm = NLMSG_DATA(nlh);
    struct rtattr   *tb[NDA_MAX + 1] = {0};	    
    int              len = nlh->nlmsg_len;
    uint8_t         *mac_addr  = (uint8_t *)arg;


    //printf("ipneigh_get_handler...\n");
    ifm_parse_rtattr(tb, NDA_MAX, NDA_RTA(ndm), len);

    if (tb[NDA_LLADDR]) {
        //TODO, add support for different lladdr types
        memcpy(mac_addr, RTA_DATA(tb[NDA_LLADDR]), RTA_PAYLOAD(tb[NDA_LLADDR]));
        //printf("ipneigh_get_handler %02x:%02x:%02x:%02x:%02x:%02x\n", 
        //       mac_addr[5],mac_addr[4], mac_addr[3],mac_addr[2], mac_addr[1],mac_addr[0]);
	return (0);
    }

    return (-1);
}

static int ipneigh_get(uint8_t family, uint32_t *addr, uint32_t ifindex, uint8_t *mac_addr)
{
    struct nl_msg    *msg;
    struct ndmsg      ndm;
    switch_service_t *sys;
    int               err;

    sys = system_get_instance();
    if (sys == NULL) {
       return -1;
    }

    memset(&ndm, 0, sizeof(ndm));
    ndm.ndm_family = family;
    ndm.ndm_ifindex = ifindex;

    msg = nlmsg_alloc_simple(RTM_GETNEIGH,NLM_F_REQUEST);
    if (!msg) {
        printf("ipneigh_get alloc msg failed \n");
        return -1;
    }

    err = nlmsg_append(msg, &ndm, sizeof(ndm), NLMSG_ALIGNTO);
    if (err) {
        printf("ipneigh_get append failed %d\n", err);
        return err;
    }

    err = nla_put_u32(msg, NDA_DST, *addr);
    if (err) {
        printf("ipneigh_get put addr failed %d addr 0x%x\n", err, *addr);
    	return err;
    }    

    err = switchdev_ops_send_and_recv(sys, msg, ipneigh_get_handler, mac_addr);
    if (err) {
        //printf("ipneigh_get ops failed %d addr 0x%x\n", err, *addr);
        return err;
    }

    //printf("ipneigh_get addr 0x%x %02x:%02x:%02x:%02x:%02x:%02x\n", 
    //        *addr, mac_addr[5],mac_addr[4], mac_addr[3],mac_addr[2], mac_addr[1],mac_addr[0]);

    return 0;
}
#endif 


static int switchdev_handle_rtm_route(struct nlmsghdr *n)
{
    struct rtmsg      *rtm = NLMSG_DATA(n);
    struct rtattr     *tb[NDA_MAX + 1] = {0};	
    int                len = n->nlmsg_len;
    int                msgtype = n->nlmsg_type;
    ip_address_t       ip_dst, ip_gw;
    uint32_t           ifindex = 0;
    char               ifname[IF_NAMESIZE+1];
    async_obj_intf_t **intf  = NULL;
    switch_service_t  *sys   = NULL;

    if ((sys = system_get_instance()) == NULL)
        return 0;    

    if (n->nlmsg_type == NLMSG_DONE) {
        return 0;
    }

    /* process msg_type RTM_NEWROUTE, RTM_DELROUTE */
    if (n->nlmsg_type != RTM_NEWROUTE && n->nlmsg_type  != RTM_DELROUTE )
        return(0);

    ifm_parse_rtattr(tb, NDA_MAX, NDA_RTA(rtm), len);

    memset(&ip_dst, 0, sizeof(ip_address_t));
    ip_dst.protocol = rtm->rtm_family;
    memcpy(ip_dst.ip, RTA_DATA(tb[RTA_DST]), RTA_PAYLOAD(tb[RTA_DST]));

    memset(&ip_gw, 0, sizeof(ip_address_t));
    if (tb[RTA_GATEWAY]) {
        ip_gw.protocol = rtm->rtm_family;
        memcpy(ip_gw.ip, RTA_DATA(tb[RTA_GATEWAY]), RTA_PAYLOAD(tb[RTA_GATEWAY]));
    } else {
        //printf("handle_route_request missing gateway\n");
        return 0;
    }

    if (tb[RTA_OIF]) {
        memcpy(&ifindex, RTA_DATA(tb[RTA_OIF]), RTA_PAYLOAD(tb[RTA_OIF]));
    } else {
        printf("handle_route_request missing oif\n");
	    return 0;
	}

    if_indextoname(ifindex, ifname);
    intf = async_obj_intf_find(ifindex);

    if (!intf || !(*intf)) {
        printf("handle_route_request for port %d %s\n",ifindex, ifname);
        return 0;
    }

    if (rtm->rtm_scope != RT_SCOPE_UNIVERSE || rtm->rtm_type != RTN_UNICAST) {
          printf("msgtype %d route scope %d type %d ifindex %d dst 0x%x/%d gw 0x%x\n",
                 msgtype, rtm->rtm_scope, rtm->rtm_type, ifindex, ip_dst.ip[0], rtm->rtm_dst_len, ip_gw.ip[0]);
          return 0;
    }

    if (msgtype == RTM_NEWROUTE) {
        async_obj_neigh_t   **neigh = NULL;
        async_obj_fib_t     **fib   = NULL;

        printf("add ipv4 route : ifindex %d  dst 0x%x/%d gw 0x%x\n",
               ifindex, ip_dst.ip[0], rtm->rtm_dst_len, ip_gw.ip[0]);        

        // if ip neigh does not exist, create a new obj
        neigh = async_obj_neigh_find_or_new(&ip_gw);
        if (!neigh) {
            // should not happen
            return 0;
        }

        // if fib does not exist, create a new fib
        fib = async_obj_fib_find_or_new(ifindex, &ip_gw, &ip_dst, rtm->rtm_dst_len);
        if (!fib) {
            // should not happen
            return 0;
        }

        (*fib)->object_add_parent((async_object_t *)*fib, (async_object_t *)*neigh);

        (*fib)->object_create((async_object_t *)*fib);

        (*fib)->object_download((async_object_t *)*fib);
        
        return (0);
    } else {
        async_obj_fib_t     **fib = NULL;

        printf("del ipv4 route : ifindex %d  dst 0x%x/%d gw 0x%x\n",
               ifindex, ip_dst.ip[0], rtm->rtm_dst_len, ip_gw.ip[0]);
        fib = async_obj_fib_find(ifindex, &ip_gw, &ip_dst, rtm->rtm_dst_len);

        if (!fib) {
            return (0);
        }

        (*fib)->object_delete((async_object_t **)fib);
    }        

    return (0);
}

static int switchdev_route_event_handler(struct nl_msg *msg, void *arg)
{
    struct nlmsghdr *nlh = nlmsg_hdr(msg);
    //unsigned int event = 1;

    /* Update netlink message counters */
    //system_update_netlink_counters(nlh->nlmsg_type, nlh);

    switch (nlh->nlmsg_type)
    {
        case RTM_NEWLINK:
            if (nl_msg_parse(msg, &switchdev_event_handler_rtm_newlink, NULL) < 0) {
                printf("Unknown message type.");
			}
            break;

        case RTM_DELLINK:
            break;

        case RTM_NEWNEIGH:
        case RTM_DELNEIGH:
	        switchdev_handle_rtm_neigh(nlh);        
            break;

        case RTM_NEWADDR:
            if (nl_msg_parse(msg, &switchdev_event_handler_rtm_newaddr, NULL) < 0) {
                printf("Unknown message type.");
			}
            break;
        case RTM_DELADDR:
            if (nl_msg_parse(msg, &switchdev_event_handler_rtm_deladdr, NULL) < 0) {
                printf("Unknown message type.");
		    }
            break;

        case RTM_NEWROUTE:
        case RTM_DELROUTE:
            switchdev_handle_rtm_route(nlh);
        default:
            return NL_OK;
    }

    return NL_STOP;
}


/*
 * Handler for all received messages from our Generic Netlink family, both
 * unicast and multicast.
 */
static int message_handler(struct nl_msg *msg, void *arg)
{
	int		   err	   = 0;
	struct genlmsghdr *genlhdr = nlmsg_data(nlmsg_hdr(msg));
	
	switch (genlhdr->cmd) {
	    case SWITCHDEV_EVENT_PORT:
		   err = handle_switchdev_port_event(msg);
		   break;

		case SWITCHDEV_EVENT_START:
		   printf("start response received\n");
		   break;

		case SWITCHDEV_EVENT_KEEPALIVE:
		default:
		   break;
	}


	return err;
}

/* Send (unicast) SWITCHDEV_EVENT_KEEPALIVE request message */
static int send_keepalive_msg(struct nl_sock *sk, int fam)
{
	int	       err = 0;
	struct nl_msg *msg = nlmsg_alloc();
	if (!msg) {
		return -ENOMEM;
	}

	/* Put the genl header inside message buffer */
	void *hdr = genlmsg_put(msg, NL_AUTO_PORT, NL_AUTO_SEQ, fam, 0, 0,
				SWITCHDEV_EVENT_KEEPALIVE, SWITCHDEV_GENL_VERSION);
	if (!hdr) {
		return -EMSGSIZE;
	}

	/* Put the string inside the message. */
	err = nla_put_string(msg, SWITCHDEV_EVENT_KEEPALIVE,
			     "Hello from User Space, Netlink!");
	if (err < 0) {
		return -err;
	}

	/* Send the message. */
	err = nl_send_auto(sk, msg);
	err = err >= 0 ? 0 : err;

	nlmsg_free(msg);

	return err;
}

/* Send (unicast) SWITCHDEV_EVENT_START request message */
static int send_start_msg(struct nl_sock *sk, int fam)
{
	int	       err = 0;
	struct nl_msg *msg = nlmsg_alloc();
	if (!msg) {
		return -ENOMEM;
	}

	/* Put the genl header inside message buffer */
	void *hdr = genlmsg_put(msg, NL_AUTO_PORT, NL_AUTO_SEQ, fam, 0, 0,
				SWITCHDEV_EVENT_START, SWITCHDEV_GENL_VERSION);
	if (!hdr) {
		return -EMSGSIZE;
	}

	printf("START message sent\n");

	/* Send the message. */
	err = nl_send_auto(sk, msg);
	err = err >= 0 ? 0 : err;

	nlmsg_free(msg);

	return err;
}

/* Allocate netlink socket and connect to generic netlink */
static int conn(struct nl_sock **sk)
{
    *sk = nl_socket_alloc();
    if (!sk) {
    	return -ENOMEM;
    }
    
    return genl_connect(*sk);
}

/* Disconnect and release socket */
static void disconn(struct nl_sock *sk)
{
    nl_close(sk);
    nl_socket_free(sk);
}

/* Modify the callback for replies to handle all received messages */
static inline int set_cb(struct nl_sock *sk)
{
    return nl_socket_modify_cb(sk, NL_CB_VALID, NL_CB_CUSTOM,
                               message_handler, NULL);
}

static void set_nonblocking(int fd) 
{
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}


#define EPOLL_MAX_EVENTS 10
int switchdev_netlink_main(void)
{
    struct epoll_event ev, events[EPOLL_MAX_EVENTS];
	struct itimerspec keepalive_value = {
        .it_value = {1, 0},  
        .it_interval = {1, 0}
    };
    switch_service_t *sys = system_get_instance();
    int               ret = 1;


    /*
     * We use one socket to receive asynchronous "notifications" over
     * multicast group, and another for ops. We do this so that we don't mix
     * up responses from ops with notifications to make handling easier.
     */
    if ((ret = conn(&sys->ucsk)) || (ret = conn(&sys->mcsk))) {
    	prerr("failed to connect to generic netlink\n");
    	goto out;
    }
    
    /* Resolve the genl family. One family for both unicast and multicast. */
    int fam = genl_ctrl_resolve(sys->ucsk, SWITCHDEV_GENL_NAME);
    if (fam < 0) {
    	prerr("failed to resolve generic netlink family: %s\n",
    	      strerror(-fam));
    	goto out;
    }
    
    /* Disable sequence checks for asynchronous multicast messages. */
    nl_socket_disable_seq_check(sys->mcsk);
    
    /* Disable sequence checks for unicast messages. */
    nl_socket_disable_seq_check(sys->ucsk);
    
    /* Resolve the multicast group. */
    int mcgrp = genl_ctrl_resolve_grp(sys->mcsk, SWITCHDEV_GENL_NAME,
    				  SWITCHDEV_MC_GRP_NAME);
    if (mcgrp < 0) {
    	prerr("failed to resolve generic netlink multicast group: %s\n",
    	      strerror(-mcgrp));
    	goto out;
    }
    /* Join the multicast group. */
    if ((ret = nl_socket_add_membership(sys->mcsk, mcgrp) < 0)) {
    	prerr("failed to join multicast group: %s\n", strerror(-ret));
    	goto out;
    }
    
    if ((ret = set_cb(sys->ucsk)) || (ret = set_cb(sys->mcsk))) {
    	prerr("failed to set callback: %s\n", strerror(-ret));
    	goto out;
    }

    // send start and listen for response
    if ((ret = send_start_msg(sys->ucsk, fam))) {
    	prerr("failed to send message: %s\n", strerror(-ret));
    }
    printf("listening for messages\n");
    nl_recvmsgs_default(sys->ucsk);
    
    //TimerFD 
    sys->timer_fd = timerfd_create(CLOCK_MONOTONIC, 0);
    timerfd_settime(sys->timer_fd, 0, &keepalive_value, NULL);

    sys->ucsk_fd = nl_socket_get_fd(sys->ucsk);
    set_nonblocking(sys->ucsk_fd);

    sys->mcsk_fd = nl_socket_get_fd(sys->mcsk);
    set_nonblocking(sys->mcsk_fd);

    sys->epoll_fd = epoll_create1(0);

    if (sys->epoll_fd < 0) {
        perror("epoll_create1 failed");
        goto out;
    }

    ev.events = EPOLLIN;
    ev.data.fd = sys->ucsk_fd;
    epoll_ctl(sys->epoll_fd, EPOLL_CTL_ADD, sys->ucsk_fd, &ev);

    ev.events = EPOLLIN;
    ev.data.fd = sys->mcsk_fd;
    epoll_ctl(sys->epoll_fd, EPOLL_CTL_ADD, sys->mcsk_fd, &ev);	

    ev.events = EPOLLIN;
    ev.data.fd = sys->timer_fd;
    epoll_ctl(sys->epoll_fd, EPOLL_CTL_ADD, sys->timer_fd, &ev);
	
#if 0
    //create netlink socket for ops
    sys->generic_sock = nl_socket_alloc();
    sys->generic_sock_seq = time(NULL);
    ret = nl_connect(sys->generic_sock, NETLINK_ROUTE);
    if (ret)
    {
        printf("Failed to connect to netlink generic_sock. ");
        goto out;
    }
    nl_socket_disable_seq_check(sys->generic_sock);
    sys->generic_sock_fd = nl_socket_get_fd(sys->generic_sock);
#endif

    //create netlink socket for route event
    sys->route_event_sock = nl_socket_alloc();
    ret = nl_connect(sys->route_event_sock, NETLINK_ROUTE);
    if (ret)
    {
        printf("Failed to connect to netlink route_event_sock. ");
		goto out;
    }
    nl_socket_disable_seq_check(sys->route_event_sock);
    sys->route_event_fd = nl_socket_get_fd(sys->route_event_sock);
    set_nonblocking(sys->route_event_fd);

    nl_socket_modify_cb(sys->route_event_sock, NL_CB_VALID, NL_CB_CUSTOM,
                        switchdev_route_event_handler, NULL);

    ret = nl_socket_add_membership(sys->route_event_sock, RTNLGRP_NEIGH);
    if (ret < 0)
    {
        printf("Failed to add netlink neigh membership.");
        goto out;
    }

    ret = nl_socket_add_membership(sys->route_event_sock, RTNLGRP_LINK);
    if (ret < 0)
    {
        printf("Failed to add netlink neigh membership.");
        goto out;
    }
 
    ret = nl_socket_add_membership(sys->route_event_sock, RTNLGRP_IPV4_IFADDR);
    if (ret < 0)
    {
        printf("Failed to add netlink ipv4 if addr membership.");
        goto out;
    }

    ret = nl_socket_add_membership(sys->route_event_sock, RTNLGRP_IPV6_IFADDR);
    if (ret < 0)
    {
        printf("Failed to add netlink ipv6 ifaddr membership.");
        goto out;
    }

    ret = nl_socket_add_membership(sys->route_event_sock, RTNLGRP_IPV4_ROUTE);
    if (ret < 0)
    {
        printf("Failed to add netlink ipv4 route membership.");
        goto out;
    }

    ret = nl_socket_add_membership(sys->route_event_sock, RTNLGRP_IPV6_ROUTE);
    if (ret < 0)
    {
        printf("Failed to add netlink ipv6 route membership.");
        goto out;
    }    
    ev.events = EPOLLIN;
    ev.data.fd = sys->route_event_fd;
    epoll_ctl(sys->epoll_fd, EPOLL_CTL_ADD, sys->route_event_fd, &ev);

    while (1) {
        int nfds = epoll_wait(sys->epoll_fd, events, 10, -1);
        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == sys->ucsk_fd) {
                nl_recvmsgs_default(sys->ucsk);
            } else if (events[i].data.fd == sys->mcsk_fd) {
                nl_recvmsgs_default(sys->mcsk);
            } else if (events[i].data.fd == sys->timer_fd) {
                //send_keepalive_msg(sys->ucsk, fam);
            } else if (events[i].data.fd == sys->route_event_fd) {
                nl_recvmsgs_default(sys->route_event_sock);
            } else {
               prerr("unknown event %d\n", events[i].data.fd);
            }
        }
    }

    ret = 0;
out:
    disconn(sys->ucsk);
    disconn(sys->mcsk);
    disconn(sys->route_event_sock);
    return ret;
}


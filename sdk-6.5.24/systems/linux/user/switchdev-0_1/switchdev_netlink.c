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

#include "switchdev_utils.h"
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

void switchdev_event_handle_rtm_newaddr(struct nl_object *obj, void *arg)
{
    async_obj_intf_t   **local_if  = NULL;
    async_obj_l3host_t **l3host    = NULL;    
    struct nl_addr      *nl_addr   = NULL;
    struct rtnl_addr    *addr      = NULL;
    uint32_t             ifindex;    
    char                 ifname[IF_NAMESIZE+1];
    uint32_t             ipv4_addr, *ipv6_addr;
    ip_address_t         host;
    //int                  prefixlen;


    addr = (struct rtnl_addr *)obj;

    ifindex = rtnl_addr_get_ifindex(addr);
    if_indextoname(ifindex, ifname);

    local_if = async_obj_intf_find(ifindex);
    if(!local_if || !(*local_if)) {
        printf("handle newaddr ignoring none local if %d %s\n", ifindex, ifname);
        return;
    }

    nl_addr   = rtnl_addr_get_local(addr);
    //prefixlen = rtnl_addr_get_prefixlen(addr);

    memset(&host, 0, sizeof(host));
    if (rtnl_addr_get_family(addr) == AF_INET) {
        ipv4_addr     = *(uint32_t *) nl_addr_get_binary_addr(nl_addr);
        host.protocol = AF_INET;
        host.ip[0]    = ipv4_addr;
    } else if  (rtnl_addr_get_family(addr) == AF_INET6) {
        ipv6_addr     = (uint32_t *) nl_addr_get_binary_addr(nl_addr);
        host.protocol = AF_INET6;        
        memcpy(host.ip, ipv6_addr, 16);
    }
    //printf("handle_rtm_newaddr l3 host add: index %d %s address %s/%d\n",
    //       ifindex, ifname, ipaddr2str(&host), prefixlen); 

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

void switchdev_event_handle_rtm_deladdr(struct nl_object *obj, void *arg)
{
    async_obj_intf_t   **local_if  = NULL;
    async_obj_l3host_t **l3host    = NULL;    
    struct nl_addr      *nl_addr   = NULL;
    struct rtnl_addr    *addr      = NULL;
    uint32_t             ifindex;    
    char                 ifname[IF_NAMESIZE+1];
    uint32_t             ipv4_addr, *ipv6_addr;
    ip_address_t         host;
    //int                  prefixlen;


    addr = (struct rtnl_addr *)obj;

    ifindex = rtnl_addr_get_ifindex(addr);
    if_indextoname(ifindex, ifname);

    local_if = async_obj_intf_find(ifindex);
    if(!local_if || !(*local_if)) {
        printf("handle deladdr failed to find local if %d %s\n", ifindex, ifname);
        return;
    }

    nl_addr   = rtnl_addr_get_local(addr);
    //prefixlen = rtnl_addr_get_prefixlen(addr);

    memset(&host, 0, sizeof(host));

    if (rtnl_addr_get_family(addr) == AF_INET) {
        ipv4_addr     = *(uint32_t *) nl_addr_get_binary_addr(nl_addr);
        host.protocol = AF_INET;
        host.ip[0]    = ipv4_addr;
    } else if  (rtnl_addr_get_family(addr) == AF_INET6) {
        ipv6_addr     = (uint32_t *) nl_addr_get_binary_addr(nl_addr);
        host.protocol = AF_INET6;        
        memcpy(host.ip, ipv6_addr, 16);
    }
    //printf("handle_rtm_deladdr l3 host del: index %d %s address %s/%d\n",
    //       ifindex, ifname, ipaddr2str(&host), prefixlen); 

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

void parse_rtattr(struct rtattr **tb, int max, struct rtattr *rta, int len)
{
    while (RTA_OK(rta, len))
    {
        if (rta->rta_type <= max)
            tb[rta->rta_type] = rta;
        rta = RTA_NEXT(rta, len);
    }
}


void switchdev_event_handle_rtm_newlink(struct nl_object *obj, void *arg)
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

static int ipneigh_set(async_obj_neigh_t *neigh)
{
    struct nl_msg    *msg = NULL;
    struct ndmsg      ndm;
    switch_service_t *sys = NULL;
    int               err = 0;

    sys = system_get_instance();
    if (sys == NULL) {
       return -1;
    }

    memset(&ndm, 0, sizeof(ndm));
    ndm.ndm_family   = neigh->nh.protocol;
    ndm.ndm_ifindex  = neigh->ifindex;
    ndm.ndm_type     = RTN_UNICAST;
    ndm.ndm_state    = NUD_DELAY;
    ndm.ndm_flags    = NTF_USE;

    msg = nlmsg_alloc_simple(RTM_NEWNEIGH,NLM_F_REQUEST | NLM_F_ACK | NLM_F_CREATE | NLM_F_REPLACE);
    if (!msg) {
        printf("ipneigh_set alloc msg failed \n");
        return -1;
    }

    err = nlmsg_append(msg, &ndm, sizeof(ndm), NLMSG_ALIGNTO);
    if (err) {
        printf("ipneigh_set append failed %d\n", err);
        return err;
    }

    err = nla_put(msg, 
                  NDA_DST, 
                  (ndm.ndm_family == AF_INET)?sizeof(struct in_addr) : sizeof(struct in6_addr),
                  neigh->nh.ip);
    if (err) {
        printf("ipneigh_set put addr failed %d addr %s\n", err, ipaddr2str(&neigh->nh));
        return err;
    }

    err = nl_send_auto(sys->netlink.generic_sock, msg);
    nlmsg_free(msg);
    if (err < 0) {
        printf("ipneigh_set send_auto ret %d\n", err);
        return err;
    }

    return err;
}


static int switchdev_handle_rtm_neigh(struct nlmsghdr *n)
{
    struct ndmsg  *ndm = NLMSG_DATA(n);
    struct rtattr *tb[NDA_MAX + 1] = {0};	
    int            len = n->nlmsg_len;
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

    parse_rtattr(tb, NDA_MAX, NDA_RTA(ndm), len);

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

    if (tb[NDA_LLADDR]) {
        memcpy(mac_addr, RTA_DATA(tb[NDA_LLADDR]), RTA_PAYLOAD(tb[NDA_LLADDR]));
    }

    //printf("handle neigh msg %d state %d if_index %d %s, ip_addr %s mac %s\n",
    //       msgtype, ndm->ndm_state, ndm->ndm_ifindex, ifname, 
    //       ipaddr2str(&ip_addr), macaddr2str(mac_addr));

    if (msgtype != RTM_DELNEIGH) { 
        async_obj_neigh_t   **neigh = NULL;

        switch(ndm->ndm_state) {
            case NUD_PERMANENT:
            case NUD_REACHABLE:
                neigh = async_obj_neigh_find_or_new(&ip_addr);
                if (!neigh || !(*neigh)) {
                    return 0;
                }
                memcpy((*neigh)->mac_addr, mac_addr, ETHER_ADDR_LEN);
                (*neigh)->ifindex = ndm->ndm_ifindex;

                //TODO, handle neigh MAC change case
                //printf("   neigh %p nh 0x%x\n", *neigh, (*neigh)->nh.ip[0]);
                (*neigh)->object_create((async_object_t *)(*neigh));

                // special handling for neigh object, trigger download only if there is child
                if (!LIST_EMPTY(&(*neigh)->child_list)) {
                    (*neigh)->object_download((async_object_t *)*neigh);
                }
                break;

            case NUD_STALE:
                neigh = async_obj_neigh_find(&ip_addr);
                if (neigh && (*neigh)) {
                    //try to refresh neigh state if neigh is used 
                    if (!LIST_EMPTY(&(*neigh)->child_list)) {
                        ipneigh_set(*neigh);
                    }
                }
            default:
                break;
        }
    } else {
        async_obj_neigh_t   **neigh = NULL;

        switch(ndm->ndm_state) {
            case NUD_FAILED:
                //del, remove l3 egress object
                neigh = async_obj_neigh_find(&ip_addr);
                if(!neigh) {
                    return 0;
                }
                //printf("switchdev_handle_rtm_neigh neigh delete 0x%x\n", ipv4_addr);
                (*neigh)->object_delete((async_object_t **)neigh);
                break;

            default:
                break;
        }
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
    parse_rtattr(tb, NDA_MAX, NDA_RTA(ndm), len);

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
    struct rtmsg      *rtm     = NLMSG_DATA(n);
    struct rtattr     *tb[NDA_MAX + 1] = {0};	
    int                len     = n->nlmsg_len;
    int                msgtype = n->nlmsg_type;
    ip_address_t       ip_dst;
    ip_address_t       nh[ECMP_MAX_PATH];    
    uint32_t           ifindex[ECMP_MAX_PATH];
    int                nhs     = 0;
    int                is_ecmp = 0;
    char               ifname[IF_NAMESIZE+1];
    async_obj_intf_t **intf    = NULL;
    switch_service_t  *sys     = NULL;

    if ((sys = system_get_instance()) == NULL)
        return 0;    

    if (n->nlmsg_type == NLMSG_DONE) {
        return 0;
    }

    parse_rtattr(tb, RTA_MAX, RTM_RTA(rtm), len);

    memset(&ip_dst, 0, sizeof(ip_address_t));
    ip_dst.protocol = rtm->rtm_family;
    memcpy(ip_dst.ip, RTA_DATA(tb[RTA_DST]), RTA_PAYLOAD(tb[RTA_DST]));

    if (rtm->rtm_scope != RT_SCOPE_UNIVERSE ) {
        //printf("unhandled rtm_route msgtype %d route scope %d type %d dst %s/%d\n",
        //         msgtype, rtm->rtm_scope, rtm->rtm_type, ipaddr2str(&ip_dst), rtm->rtm_dst_len);
        return 0;
    }
    if ((rtm->rtm_type != RTN_UNICAST && rtm->rtm_type != RTN_UNREACHABLE)) {
          printf("unhandled rtm_route msgtype %d route scope %d type %d dst %s/%d\n",
                 msgtype, rtm->rtm_scope, rtm->rtm_type, ipaddr2str(&ip_dst), rtm->rtm_dst_len);
          return 0;
    }

    // via
    if (tb[RTA_GATEWAY]) {
        memset(&nh[nhs], 0, sizeof(ip_address_t));
        nh[nhs].protocol = rtm->rtm_family;
        memcpy(&(nh[nhs].ip), RTA_DATA(tb[RTA_GATEWAY]), RTA_PAYLOAD(tb[RTA_GATEWAY]));
        nhs++;

        // intf
        if (tb[RTA_OIF]) {
            memcpy(&ifindex[0], RTA_DATA(tb[RTA_OIF]), RTA_PAYLOAD(tb[RTA_OIF]));
        } else {
            printf("handle_route_request missing oif\n");
	        return 0;
	    }

        if_indextoname(ifindex[0], ifname);
        intf = async_obj_intf_find(ifindex[0]);

        if (!intf || !(*intf)) {
            printf("handle_route_request for port %d %s\n",ifindex[0], ifname);
            return 0;
        }
    } else if (tb[RTA_MULTIPATH]) {
        // multipath, via list
        struct rtnexthop *nhptr     = (struct rtnexthop *)RTA_DATA(tb[RTA_MULTIPATH]);
        int               rtnhp_len = RTA_PAYLOAD(tb[RTA_MULTIPATH]);
        struct rtattr    *attr[RTA_MAX + 1];

        while(rtnhp_len >= sizeof(struct rtnexthop)) {
            if (nhptr->rtnh_len > rtnhp_len)
                break;

            if (nhptr->rtnh_len > sizeof(*nhptr)) {
                /*Retrieve attributes */
                parse_rtattr(attr, RTA_MAX, RTNH_DATA(nhptr), nhptr->rtnh_len - sizeof(*nhptr));

                if (attr[RTA_GATEWAY]) {
                    memset(&nh[nhs], 0, sizeof(ip_address_t));
                    nh[nhs].protocol = rtm->rtm_family;
                    memcpy(&(nh[nhs].ip), RTA_DATA(attr[RTA_GATEWAY]), RTA_PAYLOAD(attr[RTA_GATEWAY]));

                    ifindex[nhs] = nhptr->rtnh_ifindex;
                    if_indextoname(ifindex[nhs], ifname);
                    intf = async_obj_intf_find(ifindex[nhs]);

                    if (!intf || !(*intf)) {
                        printf("handle_route_request ecmp ignoring none local if %s[%d]\n", ifname, ifindex[nhs]);
                        return 0;
                    }
                    nhs++;
                }
            }
            rtnhp_len -= NLMSG_ALIGN(nhptr->rtnh_len);
            nhptr = RTNH_NEXT(nhptr);
        }
        is_ecmp = true;
    }

    if (rtm->rtm_type == RTN_UNREACHABLE) {
        msgtype = RTM_DELROUTE;
    }

    if (msgtype != RTM_DELROUTE) {
        async_obj_neigh_t   **neigh = NULL;
        async_obj_fib_t     **fib   = NULL;
        int                   i     = 0;

        printf("%s route : dst %s/%d ",
               (msgtype == RTM_NEWROUTE)?"add":"update",
               ipaddr2str(&ip_dst), rtm->rtm_dst_len);    

        if (nhs == 0) {
            printf("missing nexthop,ignore\n");
            return 0;
        }
        if (!is_ecmp) {    
            printf("via %s dev %s[%d]\n", ipaddr2str(&nh[0]), ifname, ifindex[0]);
        } else {
            for(i = 0; i <nhs; i++) {
                if_indextoname(ifindex[i], ifname);
                printf("\n    nexthop via %s dev %s[%d]", ipaddr2str(&nh[i]), ifname, ifindex[i]);
            }
            printf("\n");
        }

        // if fib does not exist, create a new fib
        fib = async_obj_fib_find_or_new(&ip_dst, rtm->rtm_dst_len, is_ecmp);
        if (!fib || !(*fib)) {
            // should not happen
            return 0;
        }
        (*fib)->ifindex  = ifindex[0];
        (*fib)->is_ecmp = is_ecmp;
        (*fib)->fib_nhs = nhs;

        // todo handle update nh case
        // if ip neigh does not exist, create a new obj
        for (i = 0; i < nhs; i++) {
            neigh = async_obj_neigh_find(&nh[i]);
            if (!neigh || !(*neigh)) {
                neigh = async_obj_neigh_find_or_new(&nh[i]);
                if (!neigh || !(*neigh)) {
                    // should not happen
                    return 0;
                }
                // neigh does not exist yet, send create request to kernel
                (*neigh)->ifindex = ifindex[i];
                ipneigh_set(*neigh);
            }
            //printf("    neigh %p state %d ip %s\n",(*neigh), (*neigh)->state, ipaddr2str(&(*neigh)->nh));
            memcpy(&(*fib)->nh[i], &nh[i], sizeof(ip_address_t));
            (*fib)->object_add_parent((async_object_t *)*fib, (async_object_t *)*neigh);
        }

        (*fib)->object_create((async_object_t *)*fib);
        (*fib)->object_download((async_object_t *)*fib);
        
        return (0);
    } else {
        async_obj_fib_t     **fib = NULL;
        int                   i   = 0;

        printf("del route : dst %s/%d ",
               ipaddr2str(&ip_dst), rtm->rtm_dst_len);
        if (rtm->rtm_type == RTN_UNREACHABLE) {
            // can happen if interface IP is removed
            // no nexthop info
            printf("\n");
        } else if (!is_ecmp) {    
            printf("via %s dev %s[%d]\n", ipaddr2str(&nh[0]), ifname, ifindex[0]);
        } else {
            for(i = 0; i <nhs; i++) {
                if_indextoname(ifindex[i], ifname);
                printf("\n    nexthop via %s dev %s[%d]", ipaddr2str(&nh[i]), ifname, ifindex[i]);
            }
            printf("\n");
        }

        fib = async_obj_fib_find(&ip_dst, rtm->rtm_dst_len, is_ecmp);

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
            if (nl_msg_parse(msg, &switchdev_event_handle_rtm_newlink, NULL) < 0) {
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
            if (nl_msg_parse(msg, &switchdev_event_handle_rtm_newaddr, NULL) < 0) {
                printf("Unknown message type.");
			}
            break;
        case RTM_DELADDR:
            if (nl_msg_parse(msg, &switchdev_event_handle_rtm_deladdr, NULL) < 0) {
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
    if ((ret = conn(&sys->netlink.ucsk)) || (ret = conn(&sys->netlink.mcsk))) {
    	prerr("failed to connect to generic netlink\n");
    	goto out;
    }
    
    /* Resolve the genl family. One family for both unicast and multicast. */
    int fam = genl_ctrl_resolve(sys->netlink.ucsk, SWITCHDEV_GENL_NAME);
    if (fam < 0) {
    	prerr("failed to resolve generic netlink family: %s\n",
    	      strerror(-fam));
    	goto out;
    }
    
    /* Disable sequence checks for asynchronous multicast messages. */
    nl_socket_disable_seq_check(sys->netlink.mcsk);
    
    /* Disable sequence checks for unicast messages. */
    nl_socket_disable_seq_check(sys->netlink.ucsk);
    
    /* Resolve the multicast group. */
    int mcgrp = genl_ctrl_resolve_grp(sys->netlink.mcsk, SWITCHDEV_GENL_NAME,
    				  SWITCHDEV_MC_GRP_NAME);
    if (mcgrp < 0) {
    	prerr("failed to resolve generic netlink multicast group: %s\n",
    	      strerror(-mcgrp));
    	goto out;
    }
    /* Join the multicast group. */
    if ((ret = nl_socket_add_membership(sys->netlink.mcsk, mcgrp) < 0)) {
    	prerr("failed to join multicast group: %s\n", strerror(-ret));
    	goto out;
    }
    
    if ((ret = set_cb(sys->netlink.ucsk)) || (ret = set_cb(sys->netlink.mcsk))) {
    	prerr("failed to set callback: %s\n", strerror(-ret));
    	goto out;
    }

    // send start and listen for response
    if ((ret = send_start_msg(sys->netlink.ucsk, fam))) {
    	prerr("failed to send message: %s\n", strerror(-ret));
    }
    printf("listening for messages\n");
    nl_recvmsgs_default(sys->netlink.ucsk);
    
    //TimerFD 
    sys->netlink.timer_fd = timerfd_create(CLOCK_MONOTONIC, 0);
    timerfd_settime(sys->netlink.timer_fd, 0, &keepalive_value, NULL);

    sys->netlink.ucsk_fd = nl_socket_get_fd(sys->netlink.ucsk);
    set_nonblocking(sys->netlink.ucsk_fd);

    sys->netlink.mcsk_fd = nl_socket_get_fd(sys->netlink.mcsk);
    set_nonblocking(sys->netlink.mcsk_fd);

    sys->netlink.epoll_fd = epoll_create1(0);

    if (sys->netlink.epoll_fd < 0) {
        perror("epoll_create1 failed");
        goto out;
    }

    ev.events = EPOLLIN;
    ev.data.fd = sys->netlink.ucsk_fd;
    epoll_ctl(sys->netlink.epoll_fd, EPOLL_CTL_ADD, sys->netlink.ucsk_fd, &ev);

    ev.events = EPOLLIN;
    ev.data.fd = sys->netlink.mcsk_fd;
    epoll_ctl(sys->netlink.epoll_fd, EPOLL_CTL_ADD, sys->netlink.mcsk_fd, &ev);	

    ev.events = EPOLLIN;
    ev.data.fd = sys->netlink.timer_fd;
    epoll_ctl(sys->netlink.epoll_fd, EPOLL_CTL_ADD, sys->netlink.timer_fd, &ev);
	
    //create netlink socket for ops
    sys->netlink.generic_sock = nl_socket_alloc();
    sys->netlink.generic_sock_seq = time(NULL);
    ret = nl_connect(sys->netlink.generic_sock, NETLINK_ROUTE);
    if (ret)
    {
        printf("Failed to connect to netlink generic_sock. ");
        goto out;
    }
    nl_socket_disable_seq_check(sys->netlink.generic_sock);
    sys->netlink.generic_sock_fd = nl_socket_get_fd(sys->netlink.generic_sock);

    //create netlink socket for route event
    sys->netlink.route_event_sock = nl_socket_alloc();
    ret = nl_connect(sys->netlink.route_event_sock, NETLINK_ROUTE);
    if (ret)
    {
        printf("Failed to connect to netlink route_event_sock. ");
		goto out;
    }
    nl_socket_disable_seq_check(sys->netlink.route_event_sock);
    sys->netlink.route_event_fd = nl_socket_get_fd(sys->netlink.route_event_sock);
    set_nonblocking(sys->netlink.route_event_fd);

    nl_socket_modify_cb(sys->netlink.route_event_sock, NL_CB_VALID, NL_CB_CUSTOM,
                        switchdev_route_event_handler, NULL);

    ret = nl_socket_add_membership(sys->netlink.route_event_sock, RTNLGRP_NEIGH);
    if (ret < 0)
    {
        printf("Failed to add netlink neigh membership.");
        goto out;
    }

    ret = nl_socket_add_membership(sys->netlink.route_event_sock, RTNLGRP_LINK);
    if (ret < 0)
    {
        printf("Failed to add netlink neigh membership.");
        goto out;
    }
 
    ret = nl_socket_add_membership(sys->netlink.route_event_sock, RTNLGRP_IPV4_IFADDR);
    if (ret < 0)
    {
        printf("Failed to add netlink ipv4 if addr membership.");
        goto out;
    }

    ret = nl_socket_add_membership(sys->netlink.route_event_sock, RTNLGRP_IPV6_IFADDR);
    if (ret < 0)
    {
        printf("Failed to add netlink ipv6 ifaddr membership.");
        goto out;
    }

    ret = nl_socket_add_membership(sys->netlink.route_event_sock, RTNLGRP_IPV4_ROUTE);
    if (ret < 0)
    {
        printf("Failed to add netlink ipv4 route membership.");
        goto out;
    }

    ret = nl_socket_add_membership(sys->netlink.route_event_sock, RTNLGRP_IPV6_ROUTE);
    if (ret < 0)
    {
        printf("Failed to add netlink ipv6 route membership.");
        goto out;
    }    
    ev.events = EPOLLIN;
    ev.data.fd = sys->netlink.route_event_fd;
    epoll_ctl(sys->netlink.epoll_fd, EPOLL_CTL_ADD, sys->netlink.route_event_fd, &ev);

    while (1) {
        int nfds = epoll_wait(sys->netlink.epoll_fd, events, 10, 100);
        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == sys->netlink.ucsk_fd) {
                nl_recvmsgs_default(sys->netlink.ucsk);
            } else if (events[i].data.fd == sys->netlink.mcsk_fd) {
                nl_recvmsgs_default(sys->netlink.mcsk);
            } else if (events[i].data.fd == sys->netlink.timer_fd) {
                //send_keepalive_msg(sys->ucsk, fam);
            } else if (events[i].data.fd == sys->netlink.route_event_fd) {
                nl_recvmsgs_default(sys->netlink.route_event_sock);
            } else {
               prerr("unknown event %d\n", events[i].data.fd);
            }
        }
    }

    ret = 0;
out:
    disconn(sys->netlink.ucsk);
    disconn(sys->netlink.mcsk);
    disconn(sys->netlink.route_event_sock);
    return ret;
}


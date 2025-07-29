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

#ifndef NO_SAL_APPL
#include <sal/appl/sal.h>
#include <sal/appl/config.h>
#include <appl/diag/bslmgmt.h>
#include <appl/diag/opennsa_diag.h>
#endif

#include <bcm/init.h>
#include <bcm/error.h>
#include <soc/cmext.h>
#include <soc/opensoc.h>
#include <sal/core/boot.h>
#include <linux-bde.h>

#ifdef BCM_WARM_BOOT_SUPPORT
#include <bcm/switch.h>
#endif

/*
 * These includes are needed for do_per_switch_setup() part of the demo.
 */
#include <bcm/port.h>
#include <bcm/stg.h>

#if defined(BCM_LTSW_SUPPORT)
#include <appl/diag/sysconf_ltsw.h>
#endif

#include <opennsa/link.h>
#include <opennsa/l3.h>

#include "switchdev_netlink.h"

#define prerr(...) fprintf(stderr, "error: " __VA_ARGS__)

/*
 * libnl docs and API: https://www.infradead.org/~tgr/libnl/
 * Current libnl repo: https://github.com/thom311/libnl
 */

static int handle_netdev_event(struct nl_msg *msg)
{
	struct genlmsghdr *genlhdr = nlmsg_data(nlmsg_hdr(msg));
	struct nlattr	  *tb[SWITCHDEV_A_NETDEV_EVENT_MAX + 1];
    int   err = 0;
	int   event;
	char *ifname;
	int   port;

    printf("netdev event received:\n");
	/* Parse the attributes */
	err = nla_parse(tb, SWITCHDEV_A_NETDEV_EVENT_MAX, genlmsg_attrdata(genlhdr, 0),
			genlmsg_attrlen(genlhdr, 0), NULL);
	if (err) {
		prerr("unable to parse message: %s\n", strerror(-err));
		return NL_SKIP;
	}

	event = nla_get_u32(tb[SWITCHDEV_A_NETDEV_EVENT_ID]);
    port = nla_get_u32(tb[SWITCHDEV_A_NETDEV_PORT]);
    ifname = nla_get_string(tb[SWITCHDEV_A_NETDEV_IF_NAME]);

	printf("    interface name %s event %d port %d\n", ifname, event, port);

	switch (event) {
       case NETDEV_PRE_UP:
          err = bcm_port_enable_set(0, port, TRUE);
		  break;
	   case NETDEV_DOWN:
          err = bcm_port_enable_set(0, port, FALSE);
		  break;
	   case NETDEV_CHANGEUPPER:
          break;
	   default:
	       break;

	}
	return err;
}

static int handle_switchdev_port_vlan_add(struct nlattr *tb[])
{
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

extern bcm_if_t punt_l3_interface;

void switchdev_event_handler_obj_input_newaddr(struct nl_object *obj, void *arg)
{
    struct nl_addr   *nl_addr;
    uint32_t          ifindex;
	struct rtnl_addr *addr;
	char              ifname[IF_NAMESIZE+1];
    uint32_t          ipv4_addr, *ipv6_addr;
    uint8_t           prefixlen;
	bcm_l3_host_t     host_info;


	addr = (struct rtnl_addr *)obj;

	ifindex = rtnl_addr_get_ifindex(addr);
	if_indextoname(ifindex, ifname);
    nl_addr = rtnl_addr_get_local(addr);

    if (rtnl_addr_get_family(addr) == AF_INET) {
        ipv4_addr = *(uint32_t *) nl_addr_get_binary_addr(nl_addr);
        prefixlen = nl_addr_get_prefixlen(nl_addr);

        printf("add index %d %s address 0x%x prefix %d\n",
                ifindex, ifname, ipv4_addr, prefixlen);

		//Create l3table, and bind to l3 egress object
		//TODO, need to be more accurate
		if (!strncmp(ifname, "Ethernet", strlen("Ethernet"))) {
			bcm_l3_host_t_init(&host_info);
            host_info.l3a_ip_addr = ntohl(ipv4_addr); // struct in_addr is in network byte order
			host_info.l3a_intf = punt_l3_interface;
			host_info.l3a_lookup_class = 1;
            bcm_l3_host_add(0, &host_info);
		}

	} else if  (rtnl_addr_get_family(addr) == AF_INET6) {
        ipv6_addr = (uint32_t *) nl_addr_get_binary_addr(nl_addr);
        prefixlen = nl_addr_get_prefixlen(nl_addr);

        printf("add index %d %s address 0x%x 0x%x 0x%x 0x%x  prefix %d\n",
                ifindex, ifname, ipv6_addr[0], ipv6_addr[1], ipv6_addr[2], ipv6_addr[3], prefixlen);

        if (!strncmp(ifname, "Ethernet", strlen("Ethernet"))) {
            bcm_l3_host_t_init(&host_info);
            host_info.l3a_flags =  BCM_L3_IP6;
            host_info.l3a_intf = punt_l3_interface; 
            host_info.l3a_lookup_class = 1;
            memcpy(host_info.l3a_ip6_addr, ipv6_addr, 16);
            bcm_l3_host_add(0, &host_info);
        }
	}
}
void switchdev_event_handler_obj_input_deladdr(struct nl_object *obj, void *arg)
{
    struct nl_addr   *nl_addr;
    uint32_t          ifindex;
	struct rtnl_addr *addr;
	char              ifname[IF_NAMESIZE+1];
    uint32_t          ipv4_addr, *ipv6_addr;
    uint8_t           prefixlen;
	bcm_l3_host_t     host_info;


	addr = (struct rtnl_addr *)obj;

	ifindex = rtnl_addr_get_ifindex(addr);
	if_indextoname(ifindex, ifname);
    nl_addr = rtnl_addr_get_local(addr);

    if (rtnl_addr_get_family(addr) == AF_INET) {
        ipv4_addr = *(uint32_t *) nl_addr_get_binary_addr(nl_addr);
        prefixlen = nl_addr_get_prefixlen(nl_addr);

        printf("del index %d %s address 0x%x prefix %d\n",
                ifindex, ifname, ipv4_addr, prefixlen);

		//TODO, need to be more accurate
		if (!strncmp(ifname, "Ethernet", strlen("Ethernet"))) {
			bcm_l3_host_t_init(&host_info);
            host_info.l3a_ip_addr = ntohl(ipv4_addr); // struct in_addr is in network byte order
			host_info.l3a_intf = punt_l3_interface;
			host_info.l3a_lookup_class = 1;
            bcm_l3_host_delete(0, &host_info);
		}

	} else if  (rtnl_addr_get_family(addr) == AF_INET6) {
        ipv6_addr = (uint32_t *) nl_addr_get_binary_addr(nl_addr);
        prefixlen = nl_addr_get_prefixlen(nl_addr);

        printf("del index %d %s address 0x%x 0x%x 0x%x 0x%x  prefix %d\n",
                ifindex, ifname, ipv6_addr[0], ipv6_addr[1], ipv6_addr[2], ipv6_addr[3], prefixlen);

        if (!strncmp(ifname, "Ethernet", strlen("Ethernet"))) {
            bcm_l3_host_t_init(&host_info);
            host_info.l3a_flags =  BCM_L3_IP6;
            host_info.l3a_intf = punt_l3_interface; 
            host_info.l3a_lookup_class = 1;
            memcpy(host_info.l3a_ip6_addr, ipv6_addr, 16);
            bcm_l3_host_delete(0, &host_info);
        }
	
	}
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

static int switchdv_handle_neigh_request(struct nlmsghdr *n)
{
    struct ndmsg  *ndm = NLMSG_DATA(n);
    struct rtattr *tb[NDA_MAX + 1] = {0};	
    int        len = n->nlmsg_len;
    int        is_del = 0;
    int        msgtype = n->nlmsg_type;
    uint8_t    mac_addr[6];
    uint32_t   ipv4_addr;


    if (n->nlmsg_type == NLMSG_DONE)
    {
        return 0;
    }

    /* process msg_type RTM_NEWNEIGH, RTM_GETNEIGH, RTM_DELNEIGH */
    if (n->nlmsg_type != RTM_NEWNEIGH && n->nlmsg_type  != RTM_DELNEIGH )
        return(0);

    ifm_parse_rtattr(tb, NDA_MAX, NDA_RTA(ndm), len);

    if (ndm->ndm_state == NUD_INCOMPLETE
        || ndm->ndm_state == NUD_FAILED
        || ndm->ndm_state == NUD_NOARP
        || ndm->ndm_state == NUD_PERMANENT
        || ndm->ndm_state == NUD_NONE)
    {
        if ((ndm->ndm_state == NUD_FAILED)
                || (ndm->ndm_state == NUD_INCOMPLETE))
        {
            is_del = 1;
            msgtype = RTM_DELNEIGH;
        }

        if (!is_del) {
            return(0);
        }
    }

    if (!tb[NDA_DST] || ndm->ndm_type != RTN_UNICAST)
    {
        return(0);
    }

    memcpy(&ipv4_addr, RTA_DATA(tb[NDA_DST]), RTA_PAYLOAD(tb[NDA_DST]));
    
    if (!is_del && tb[NDA_LLADDR]) {
    memcpy(&mac_addr, RTA_DATA(tb[NDA_LLADDR]), RTA_PAYLOAD(tb[NDA_LLADDR]));
    }
    
    printf("handle neigh msg %d if_index %d ip_addr 0x%x\n mac %x:%x:%x:%x:%x:%x ",
           msgtype, ndm->ndm_ifindex, ipv4_addr, mac_addr[5], mac_addr[4],mac_addr[3], mac_addr[2],mac_addr[1],mac_addr[0]);

    if (ndm->ndm_family == AF_INET)
    {
        //do_arp_learn_from_kernel(ndm, tb, msgtype, is_del);

    }

    if (ndm->ndm_family == AF_INET6)
    {
        //do_ndisc_learn_from_kernel(ndm, tb, msgtype, is_del);
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
            break;

        case RTM_DELLINK:
            break;

        case RTM_NEWNEIGH:
        case RTM_DELNEIGH:
		    switchdv_handle_neigh_request(nlh);
            break;

        case RTM_NEWADDR:
            if (nl_msg_parse(msg, &switchdev_event_handler_obj_input_newaddr, NULL) < 0) {
                printf("Unknown message type.");
			}
            break;
        case RTM_DELADDR:
            if (nl_msg_parse(msg, &switchdev_event_handler_obj_input_deladdr, NULL) < 0) {
                printf("Unknown message type.");
		    }
            break;

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
        case SWITCHDEV_EVENT_NETDEV:
	       err = handle_netdev_event(msg);
		   break;

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
	int		ret = 1;
	struct  nl_sock *ucsk, *mcsk, *route_event_sock;
	int     ucsk_fd, mcsk_fd, route_event_fd, timer_fd;
	int     epoll_fd;
    struct epoll_event ev, events[EPOLL_MAX_EVENTS];
	struct itimerspec keepalive_value = {
        .it_value = {1, 0},  
        .it_interval = {1, 0}
    };

	/*
	 * We use one socket to receive asynchronous "notifications" over
	 * multicast group, and another for ops. We do this so that we don't mix
	 * up responses from ops with notifications to make handling easier.
	 */
	if ((ret = conn(&ucsk)) || (ret = conn(&mcsk))) {
		prerr("failed to connect to generic netlink\n");
		goto out;
	}

	/* Resolve the genl family. One family for both unicast and multicast. */
	int fam = genl_ctrl_resolve(ucsk, SWITCHDEV_GENL_NAME);
	if (fam < 0) {
		prerr("failed to resolve generic netlink family: %s\n",
		      strerror(-fam));
		goto out;
	}

	/* Disable sequence checks for asynchronous multicast messages. */
	nl_socket_disable_seq_check(mcsk);

	/* Disable sequence checks for unicast messages. */
	nl_socket_disable_seq_check(ucsk);

	/* Resolve the multicast group. */
	int mcgrp = genl_ctrl_resolve_grp(mcsk, SWITCHDEV_GENL_NAME,
					  SWITCHDEV_MC_GRP_NAME);
	if (mcgrp < 0) {
		prerr("failed to resolve generic netlink multicast group: %s\n",
		      strerror(-mcgrp));
		goto out;
	}
	/* Join the multicast group. */
	if ((ret = nl_socket_add_membership(mcsk, mcgrp) < 0)) {
		prerr("failed to join multicast group: %s\n", strerror(-ret));
		goto out;
	}

	if ((ret = set_cb(ucsk)) || (ret = set_cb(mcsk))) {
		prerr("failed to set callback: %s\n", strerror(-ret));
		goto out;
	}

    // send start and listen for response
   	if ((ret = send_start_msg(ucsk, fam))) {
		prerr("failed to send message: %s\n", strerror(-ret));
	}
	printf("listening for messages\n");
	nl_recvmsgs_default(ucsk);
	
	//TimerFD 
    timer_fd = timerfd_create(CLOCK_MONOTONIC, 0);
    timerfd_settime(timer_fd, 0, &keepalive_value, NULL);

    ucsk_fd = nl_socket_get_fd(ucsk);
    set_nonblocking(ucsk_fd);

	mcsk_fd = nl_socket_get_fd(mcsk);
	set_nonblocking(mcsk_fd);

    epoll_fd = epoll_create1(0);

	if (epoll_fd < 0) {
        perror("epoll_create1 failed");
        goto out;
    }

    ev.events = EPOLLIN;
    ev.data.fd = ucsk_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, ucsk_fd, &ev);

    ev.events = EPOLLIN;
    ev.data.fd = mcsk_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, mcsk_fd, &ev);	

	ev.events = EPOLLIN;
    ev.data.fd = timer_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, timer_fd, &ev);
	

	//create netlink socket for route event
    route_event_sock = nl_socket_alloc();
	ret = nl_connect(route_event_sock, NETLINK_ROUTE);
    if (ret)
    {
        printf("Failed to connect to netlink route_event_sock. ");
		goto out;
    }
    nl_socket_disable_seq_check(route_event_sock);
	route_event_fd = nl_socket_get_fd(route_event_sock);
	set_nonblocking(route_event_fd);

    nl_socket_modify_cb(route_event_sock, NL_CB_VALID, NL_CB_CUSTOM,
                        switchdev_route_event_handler, NULL);

    ret = nl_socket_add_membership(route_event_sock, RTNLGRP_IPV4_IFADDR);
    if (ret < 0)
    {
        printf("Failed to add netlink ipv4 membership.");
        goto out;
    }

    ret = nl_socket_add_membership(route_event_sock, RTNLGRP_IPV6_IFADDR);
    if (ret < 0)
    {
        printf("Failed to add netlink ipv6 membership.");
        goto out;
    }

	ev.events = EPOLLIN;
    ev.data.fd = route_event_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, route_event_fd, &ev);

    while (1) {
        int nfds = epoll_wait(epoll_fd, events, 10, -1);
        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == ucsk_fd) {
                nl_recvmsgs_default(ucsk);
            } else if (events[i].data.fd == mcsk_fd) {
                nl_recvmsgs_default(mcsk);
			} else if (events[i].data.fd == timer_fd) {
                send_keepalive_msg(ucsk, fam);
			} else if (events[i].data.fd == route_event_fd) {
                nl_recvmsgs_default(route_event_sock);
			} else {
               prerr("unknown event %d\n", events[i].data.fd);
			}
        }
    }

	ret = 0;
out:
	disconn(ucsk);
	disconn(mcsk);
	disconn(route_event_sock);
	return ret;
}


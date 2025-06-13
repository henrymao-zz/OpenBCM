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
#include <netlink/genl/ctrl.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/family.h>

#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <fcntl.h>

#include "switchdev_netlink.h"

#define prerr(...) fprintf(stderr, "error: " __VA_ARGS__)

/*
 * libnl docs and API: https://www.infradead.org/~tgr/libnl/
 * Current libnl repo: https://github.com/thom311/libnl
 */

static int handle_netdev_event(struct nl_msg *msg)
{
	struct genlmsghdr *genlhdr = nlmsg_data(nlmsg_hdr(msg));
	struct nlattr	  *tb[SWITCHDEV_EVENT_MAX + 1];
    int err = 0;

    printf("netdev event received:\n");
	/* Parse the attributes */
	err = nla_parse(tb, SWITCHDEV_EVENT_MAX, genlmsg_attrdata(genlhdr, 0),
			genlmsg_attrlen(genlhdr, 0), NULL);
	if (err) {
		prerr("unable to parse message: %s\n", strerror(-err));
		return NL_SKIP;
	}

	printf("    interface name %s event %d\n", 
            nla_get_string(tb[SWITCHDEV_A_NETDEV_IF_NAME]),
            nla_get_u32(tb[SWITCHDEV_A_NETDEV_EVENT_ID]));

	return 0;
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
	struct  nl_sock *ucsk, *mcsk;
	int     ucsk_fd, mcsk_fd, timer_fd;
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

    while (1) {
        int nfds = epoll_wait(epoll_fd, events, 10, -1);
        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == ucsk_fd) {
                nl_recvmsgs_default(ucsk);
            } else if (events[i].data.fd == mcsk_fd) {
                nl_recvmsgs_default(mcsk);
			} else if (events[i].data.fd == timer_fd) {
                send_keepalive_msg(ucsk, fam);
			} else {
               prerr("unknown event %d\n", events[i].data.fd);
			}
        }
    }

	ret = 0;
out:
	disconn(ucsk);
	disconn(mcsk);
	return ret;
}


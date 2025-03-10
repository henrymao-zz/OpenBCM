/*
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * The l3uc test checks TDM and L3 unicast functionality and performance by
 * streaming IPv4 packets on all ports at maximum rate. All ports are
 * configured in MAC loopback mode and each port is paired with a same speed
 * port. The test calculates the number of packets needed to saturate the ports
 * and send the IPv4 packets from the CPU to each port pairs initially.
 * Then the packets are L3 switched between the port pairs indefinitely. The
 * MAC DA, MAC SA, and VLAN are changed every time a packet is L3 switched. Once
 * the traffic reaches steady state, rate calculation is done by dividing the
 * transmit packet count changes and transmit byte count changes over a
 * programmable interval. The rates are checked against expected rates based on
 * port configuration and oversubscription ratio. Finally, packet integrity
 * check is achieved by redirecting the packets back to the CPU and compared
 * against expected packets.
 *
 * Configuration parameters passed from CLI:
 * PktSize: Packet size in bytes. Set to 0 for worst case packet sizes on all
 *          ports (145B for ENET, 76B for HG2). Set to 1 for random packet sizes
 * FloodCnt: Number of packets in each swill. Setting this to 0 will let the
 *           test calculate the number of packets that can be sent to achieve
 *           a lossless swirl at full rate. Set to 0 by default.
 * RateCalcInt: Interval in seconds over which rate is to be calculated
 * TolLr: Rate tolerance percentage for linerate ports (1% by default).
 * TolOv: Rate tolerance percentage for oversubscribed ports (3% by default).
 * ChkPktInteg: Set to 0 to disable packet integrity checks, 1 to enable
                (default).
 * MaxNumCells: Max number of cells for random packet sizes. Default = 4. Set
 *              to 0 for random.
 * TrafficLoad: Percentage of traffic load are allowed to pass through based on
 * port speed.
 * VfpEnable: Enable Vfp and fill it with miss entries.
 * EfpEnable: Enable Efp and fill it with miss entries.
 * VfpMatch: Program a hit entry in Vfp.
 * EfpMatch: Program a hit entry in Efp.
 * L3EcmpEnable: Enable ecmp for l3 routing.
 */

#include <appl/diag/system.h>
#include <shared/alloc.h>
#include <shared/bsl.h>

#include <soc/cm.h>
#include <soc/dma.h>
#include <soc/drv.h>
#include <soc/dcb.h>
#include <soc/cmicm.h>
#include <soc/cmic.h>

#include <sal/types.h>
#include <appl/diag/parse.h>
#include <bcm/port.h>
#include <bcm/vlan.h>

#include "testlist.h"
#include "gen_pkt.h"
#include "streaming_lib.h"

#define RMAC_ADDR {0x00, 0x11, 0x40, 0x88, 0x00, 0xff}
#define MAC_BASE {0x00, 0x11, 0x40, 0x88, 0x00, 0xff}
#define MAC_DA {0x00, 0x11, 0x40, 0x88, 0x00, 0xff}
#define MAC_SA {0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54}
#define VLAN 0x0a00
#define TTL 255
#define IPV4_ADDR 0xc0a80001
#define IPV6_ADDR { 0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
                    0x00, 0x00, 0x00, 0x00, 0xc0, 0xa8, 0x00, 0x01 };


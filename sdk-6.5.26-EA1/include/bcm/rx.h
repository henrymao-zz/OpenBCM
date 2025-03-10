/*
 * 
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 */

#ifndef __BCM_RX_H__
#define __BCM_RX_H__

#include <shared/bitop.h>
#include <bcm/types.h>
#include <bcm/pkt.h>
#include <bcm/tx.h>
#include <bcm/mirror.h>

#define BCM_RX_COS              64         /* Number of COS supported. */
#define BCM_RX_COS_ALL          -1         /* Affect all COS. */
#define BCM_RX_CHANNELS         4          /* Max. number of RX channels. */
#define BCM_CMICX_RX_CHANNELS   8          /* Max. number of CMICx RX channels. */

/* 
 * This is the default time between minimum token refreshes. It is also
 * the maximum time between RX thread wake-ups.
 */
#define BCM_RX_TOKEN_CHECK_US_DEFAULT   100000     /* 10 times/sec. */

/* 
 * This is the default value for match rule which SDK uses to identify
 * OLP packets.
 */
#define BCM_DEFAULT_OLP_MATCH_RULE  255        /* Olp Match Rule (default) */

/* bcm_rx_token_check_us */
extern int bcm_rx_token_check_us;

/* 
 * RX Callback Flags
 * 
 * The lower eight bits of the flag value are used to indicate which
 * COS(es) a callback should look at.
 * 
 *   BCM_RX_F_INTERRUPT_SET(flags) Add the interrupt flags
 *   BCM_RX_F_COS_ADD(flags, cos)  Add COS to flags
 * 
 *   BCM_RCO_F_COS_ACCEPT_MASK             Bits used for COS
 *   BCM_RCO_F_COS_ACCEPT(cos)             Generate bit for given COS
 *   BCM_RCO_F_INTR                        Interrupt level callback
 */
#define BCM_RCO_F_COS_ACCEPT_MASK   0xc0ff     
#define BCM_RCO_F_COS_ACCEPT(cos)   (1 << (cos)) 
#define BCM_RCO_F_ALL_COS           0x40000000 
#define BCM_RCO_F_INTR              0x80000000 

#define BCM_RX_F_INTERRUPT_SET(flags)  ((flags) |= BCM_RCO_F_INTR) 
#define BCM_RX_F_COS_ADD(flags, cos)  ((flags) |= BCM_RCO_F_COS_ACCEPT(cos)) 

#define BCM_RX_RATE_NOLIMIT         0          
#define BCM_RX_SCHED_ALL_PACKETS    -1         

/* Rx trap MTU layer types */
typedef enum bcm_rx_trap_mtu_layer_type_e {
    bcmRxTrapMtuLayerTypeDefault = 0, 
    bcmRxTrapMtuLayerTypeEth = 1, 
    bcmRxTrapMtuLayerTypeIpv4 = 2, 
    bcmRxTrapMtuLayerTypeIpv6 = 3, 
    bcmRxTrapMtuLayerTypeMpls = 4, 
    bcmRxTrapMtuLayerTypeCount = 5 
} bcm_rx_trap_mtu_layer_type_t;

/* Return values from PKT RX callout routines. */
typedef enum bcm_rx_e {
    BCM_RX_INVALID = 0,         /* Invalid return value. */
    BCM_RX_NOT_HANDLED = 1,     /* Packet not processed. */
    BCM_RX_HANDLED = 2,         /* Packet handled, not owned. */
    BCM_RX_HANDLED_OWNED = 3    /* Packet handled and owned. */
} bcm_rx_t;

/* Max. allowed packets per chain. */
#define BCM_RX_PPC_MAX                     

/* Callback function type for applications using bcm RX facility. */
typedef bcm_rx_t (*bcm_rx_cb_f)(
    int unit, 
    bcm_pkt_t *pkt, 
    void *cookie);

/* Callback function type for applications implementing RX scheduling. */
typedef int (*bcm_rx_sched_cb)(
    int unit, 
    int *sched_unit, 
    bcm_cos_queue_t *sched_cosq, 
    int *sched_count);

/* RX packet buffer allocation function. */
typedef int (*bcm_rx_alloc_f)(
    int unit, 
    int size, 
    uint32 flags, 
    void **pkt_buf);

/* RX packet buffer free function. */
typedef int (*bcm_rx_free_f)(
    int unit, 
    void *pkt_buf);

#define bcm_data_alloc_f        bcm_rx_alloc_f 
#define bcm_data_free_f         bcm_rx_free_f 

/* RX registration function. */
typedef int (*bcm_rx_reg_f)(
    int unit, 
    const char *name, 
    bcm_rx_cb_f callback, 
    uint8 priority, 
    void *cookie, 
    uint32 flags);

/* RX unregistration function. */
typedef int (*bcm_rx_unreg_f)(
    int unit, 
    bcm_rx_cb_f callback, 
    uint8 priority);

/* 
 * Channel-specific RX data.
 * 
 * The number of chains allowed for the channel controls the burst size
 * that the channel accepts.
 * 
 * The 'rate_pps' field is DEPRECATED. The rate may be set on a per-COS
 * basis using bcm_rx_rate_set/get.
 * 
 * IMPORTANT: If BCM_RX_F_MULTI_DCB is NOT used (single DCB per packet)
 * then the rx_free routine must be given the allocation pointer
 * (pkt->alloc_ptr) rather than the packet data pointer
 * (pkt->_pkt_data.data or pkt->pkt_data[0].data).
 */
typedef struct bcm_rx_chan_cfg_s {
    int chains;     /* Number of chains (DVs) set up. 0 means channel not used. */
    int rate_pps;   /* Deprecated: Use bcm_rx_cos_rate_set/get. */
    int flags;      /* See BCM_RX_F_* definitions. */
    uint32 cos_bmp; /* COS bitmap, if supported. */
} bcm_rx_chan_cfg_t;

/* Flags for bcm_rx_chan_cfg_t. */
#define BCM_RX_F_CRC_STRIP              0x1        /* Strip CRC from packets. */
#define BCM_RX_F_VTAG_STRIP             0x2        /* Strip VLAN tag from
                                                      packets. */
#define BCM_RX_F_RATE_STALL             0x4        /* Use stall instead of
                                                      discard. */
#define BCM_RX_F_MULTI_DCB              0x8        /* Scatter data with multiple
                                                      DCBs. */
#define BCM_RX_F_OVERSIZED_OK           0x10       /* Accept packets larger than
                                                      bufsize. */
#define BCM_RX_F_PKT_UNPARSED           0x20       /* Do not parse received
                                                      packets. */
#define BCM_RX_F_TAKE_PORT_FROM_PARSER  0x40       /* Indicate to set received
                                                      port per result of RX
                                                      parser. */

/* User-configurable, per-unit RX configuration. */
typedef struct bcm_rx_cfg_s {
    int pkt_size;                       /* Default packet size. */
    int pkts_per_chain;                 /* Packets per DMA chain. */
    int global_pps;                     /* Global rate limiting as packets per
                                           second. */
    int max_burst;                      /* Max. packets to be received in a
                                           single burst. */
    bcm_rx_chan_cfg_t chan_cfg[BCM_CMICX_RX_CHANNELS]; /* RX channel configuration. */
    bcm_rx_alloc_f rx_alloc;            /* RX packet allocation function. */
    bcm_rx_free_f rx_free;              /* RX packet free function. */
    int32 flags;                        /* See BCM_RX_F_* definitions. */
    int num_of_cpu_addresses;           /* Explicitly set the relevant num of
                                           CPU addresses - ignore if not
                                           relevant. */
    int *cpu_address;                   /* Explicitly set the relevant CPU
                                           addresses - ignore if not relevant. */
} bcm_rx_cfg_t;

/* Flags for bcm_rx_cfg_t. */
#define BCM_RX_F_IGNORE_HGHDR   0x1        /* Force HiGig Header into packet for
                                              fabric device. */
#define BCM_RX_F_IGNORE_SLTAG   0x2        /* Force SL tag into packet on SL
                                              stacking. */

/* Structure of transport related function pointers. */
typedef struct bcm_trans_ptr_s {
    bcm_rx_alloc_f tp_data_alloc;   /* Packet data allocation function. */
    bcm_rx_free_f tp_data_free;     /* Packet data free function. */
    bcm_pkt_alloc_f tp_pkt_alloc;   /* Packet structure (bcm_pkt_t) allocation
                                       function. */
    bcm_pkt_free_f tp_pkt_free;     /* Packet structure (bcm_pkt_t) free
                                       function. */
    bcm_rx_reg_f tp_rx_reg;         /* RX registration function. */
    bcm_rx_unreg_f tp_rx_unreg;     /* RX unregistration function. */
    bcm_tx_pkt_setup_f tp_setup_tx; /* TX packet setup function. */
    bcm_tx_f tp_tx;                 /* TX single packet transmit function. */
    bcm_tx_list_f tp_tx_list;       /* TX function for sending a list of
                                       packets. */
    bcm_tx_array_f tp_tx_array;     /* TX function for sending an array of
                                       packets. */
    bcm_pkt_l2_map_f tp_l2_map;     /* Map a packet's L2 information into a port
                                       bitmap. */
    int tp_unit;                    /* Default unit to use for allocation/free
                                       functions. */
} bcm_trans_ptr_t;

/* bcm_rx_chan_t */
typedef int bcm_rx_chan_t;

/* Standard BCM transport pointer structure. */
extern bcm_trans_ptr_t bcm_trans_ptr;

#define BCM_RX_REASON_NAMES_INITIALIZER _SHR_RX_REASON_NAMES_INITIALIZER 

/* 
 * PKT RX Packet Reasons; reason CPU received the packet.
 * 
 * It is possible no reasons are set (directed to CPU from ARL for
 * example), or multiple reasons may be set.
 */
typedef enum bcm_rx_reason_e {
    bcmRxReasonInvalid = _SHR_RX_INVALID, 
    bcmRxReasonArp = _SHR_RX_ARP, 
    bcmRxReasonBpdu = _SHR_RX_BPDU, 
    bcmRxReasonBroadcast = _SHR_RX_BROADCAST, 
    bcmRxReasonClassBasedMove = _SHR_RX_CLASS_BASED_MOVE, 
    bcmRxReasonClassTagPackets = _SHR_RX_CLASS_TAG_PACKETS, 
    bcmRxReasonControl = _SHR_RX_CONTROL, 
    bcmRxReasonCpuLearn = _SHR_RX_CPU_LEARN, 
    bcmRxReasonDestLookupFail = _SHR_RX_DEST_LOOKUP_FAIL, 
    bcmRxReasonDhcp = _SHR_RX_DHCP, 
    bcmRxReasonDosAttack = _SHR_RX_DOS_ATTACK, 
    bcmRxReasonE2eHolIbp = _SHR_RX_E2E_HOL_IBP, 
    bcmRxReasonEncapHigigError = _SHR_RX_ENCAP_HIGIG_ERROR, 
    bcmRxReasonFilterMatch = _SHR_RX_FILTER_MATCH, 
    bcmRxReasonGreChecksum = _SHR_RX_GRE_CHECKSUM, 
    bcmRxReasonGreSourceRoute = _SHR_RX_GRE_SOURCE_ROUTE, 
    bcmRxReasonHigigControl = _SHR_RX_HIGIG_CONTROL, 
    bcmRxReasonHigigHdrError = _SHR_RX_HIGIG_HDR_ERROR, 
    bcmRxReasonIcmpRedirect = _SHR_RX_ICMP_REDIRECT, 
    bcmRxReasonIgmp = _SHR_RX_IGMP, 
    bcmRxReasonIngressFilter = _SHR_RX_INGRESS_FILTER, 
    bcmRxReasonIp = _SHR_RX_IP, 
    bcmRxReasonIpfixRateViolation = _SHR_RX_IPFIX_RATE_VIOLATION, 
    bcmRxReasonIpMcastMiss = _SHR_RX_IP_MCAST_MISS, 
    bcmRxReasonIpmcReserved = _SHR_RX_IPMC_RSVD, 
    bcmRxReasonIpOptionVersion = _SHR_RX_IP_OPTION_VERSION, 
    bcmRxReasonIpmc = _SHR_RX_IPMC, 
    bcmRxReasonL2Cpu = _SHR_RX_L2_CPU, 
    bcmRxReasonL2DestMiss = _SHR_RX_L2_DEST_MISS, 
    bcmRxReasonL2LearnLimit = _SHR_RX_L2_LEARN_LIMIT, 
    bcmRxReasonL2Move = _SHR_RX_L2_MOVE, 
    bcmRxReasonL2MtuFail = _SHR_RX_L2_MTU_FAIL, 
    bcmRxReasonL2NonUnicastMiss = _SHR_RX_L2_NON_UNICAST_MISS, 
    bcmRxReasonL2SourceMiss = _SHR_RX_L2_SOURCE_MISS, 
    bcmRxReasonL3AddrBindFail = _SHR_RX_L3_ADDR_BIND_FAIL, 
    bcmRxReasonL3DestMiss = _SHR_RX_L3_DEST_MISS, 
    bcmRxReasonL3HeaderError = _SHR_RX_L3_HEADER_ERROR, 
    bcmRxReasonL3MtuFail = _SHR_RX_L3_MTU_FAIL, 
    bcmRxReasonL3Slowpath = _SHR_RX_L3_SLOW_PATH, 
    bcmRxReasonL3SourceMiss = _SHR_RX_L3_SOURCE_MISS, 
    bcmRxReasonL3SourceMove = _SHR_RX_L3_SOUCE_MOVE, 
    bcmRxReasonMartianAddr = _SHR_RX_MARTIAN_ADDR, 
    bcmRxReasonMcastIdxError = _SHR_RX_MCAST_IDX_ERROR, 
    bcmRxReasonMcastMiss = _SHR_RX_MCAST_MISS, 
    bcmRxReasonMimServiceError = _SHR_RX_MIM_SERVICE_ERROR, 
    bcmRxReasonMplsCtrlWordError = _SHR_RX_MPLS_CTRL_WORD_ERROR, 
    bcmRxReasonMplsError = _SHR_RX_MPLS_ERROR, 
    bcmRxReasonMplsInvalidAction = _SHR_RX_MPLS_INVALID_ACTION, 
    bcmRxReasonMplsInvalidPayload = _SHR_RX_MPLS_INVALID_PAYLOAD, 
    bcmRxReasonMplsLabelMiss = _SHR_RX_MPLS_LABEL_MISS, 
    bcmRxReasonMplsSequenceNumber = _SHR_RX_MPLS_SEQUENCE_NUMBER, 
    bcmRxReasonMplsTtl = _SHR_RX_MPLS_TTL, 
    bcmRxReasonMulticast = _SHR_RX_MULTICAST, 
    bcmRxReasonNhop = _SHR_RX_NHOP, 
    bcmRxReasonOAMError = _SHR_RX_OAM_ERROR, 
    bcmRxReasonOAMSlowpath = _SHR_RX_OAM_SLOW_PATH, 
    bcmRxReasonOAMLMDM = _SHR_RX_OAM_LMDM, 
    bcmRxReasonParityError = _SHR_RX_PARITY_ERROR, 
    bcmRxReasonProtocol = _SHR_RX_PROTOCOL, 
    bcmRxReasonSampleDest = _SHR_RX_SAMPLE_DEST, 
    bcmRxReasonSampleSource = _SHR_RX_SAMPLE_SOURCE, 
    bcmRxReasonSharedVlanMismatch = _SHR_RX_SHARED_VLAN_MISMATCH, 
    bcmRxReasonSourceRoute = _SHR_RX_SOURCE_ROUTE, 
    bcmRxReasonTimeStamp = _SHR_RX_TIME_STAMP, 
    bcmRxReasonTtl = _SHR_RX_TTL, 
    bcmRxReasonTtl1 = _SHR_RX_TTL1, 
    bcmRxReasonTunnelError = _SHR_RX_TUNNEL_ERROR, 
    bcmRxReasonUdpChecksum = _SHR_RX_UDP_CHECKSUM, 
    bcmRxReasonUnknownVlan = _SHR_RX_UNKNOWN_VLAN, 
    bcmRxReasonUrpfFail = _SHR_RX_URPF_FAIL, 
    bcmRxReasonVcLabelMiss = _SHR_RX_VC_LABEL_MISS, 
    bcmRxReasonVlanFilterMatch = _SHR_RX_VLAN_FILTER_MATCH, 
    bcmRxReasonWlanClientError = _SHR_RX_WLAN_CLIENT_ERROR, 
    bcmRxReasonWlanSlowpath = _SHR_RX_WLAN_SLOW_PATH, 
    bcmRxReasonWlanDot1xDrop = _SHR_RX_WLAN_DOT1X_DROP, 
    bcmRxReasonTimeSync = _SHR_RX_TIMESYNC, 
    bcmRxReasonEAVData = _SHR_RX_EAV_DATA, 
    bcmRxReasonSamePortBridge = _SHR_RX_SAME_PORT_BRIDGE, 
    bcmRxReasonSplitHorizon = _SHR_RX_SPLIT_HORIZON, 
    bcmRxReasonL4Error = _SHR_RX_L4_ERROR, 
    bcmRxReasonStp = _SHR_RX_STP, 
    bcmRxReasonVlanTranslate = _SHR_RX_VLAN_TRANSLATE, 
    bcmRxReasonMmrp = _SHR_RX_MMRP, 
    bcmRxReasonSrp = _SHR_RX_SRP, 
    bcmRxReasonTunnelControl = _SHR_RX_TUNNEL_CONTROL, 
    bcmRxReasonL2Marked = _SHR_RX_L2_MARKED, 
    bcmRxReasonWlanSlowpathKeepalive = _SHR_RX_WLAN_SLOWPATH_KEEPALIVE, 
    bcmRxReasonStation = _SHR_RX_STATION, 
    bcmRxReasonNiv = _SHR_RX_NIV, 
    bcmRxReasonNivPrioDrop = _SHR_RX_NIV_PRIO_DROP, 
    bcmRxReasonNivInterfaceMiss = _SHR_RX_NIV_INTERFACE_MISS, 
    bcmRxReasonNivRpfFail = _SHR_RX_NIV_RPF_FAIL, 
    bcmRxReasonNivTagInvalid = _SHR_RX_NIV_TAG_INVALID, 
    bcmRxReasonNivTagDrop = _SHR_RX_NIV_TAG_DROP, 
    bcmRxReasonNivUntagDrop = _SHR_RX_NIV_UNTAG_DROP, 
    bcmRxReasonTrill = _SHR_RX_TRILL, 
    bcmRxReasonTrillInvalid = _SHR_RX_TRILL_INVALID, 
    bcmRxReasonTrillMiss = _SHR_RX_TRILL_MISS, 
    bcmRxReasonTrillRpfFail = _SHR_RX_TRILL_RPF_FAIL, 
    bcmRxReasonTrillSlowpath = _SHR_RX_TRILL_SLOWPATH, 
    bcmRxReasonTrillCoreIsIs = _SHR_RX_TRILL_CORE_IS_IS, 
    bcmRxReasonTrillTtl = _SHR_RX_TRILL_TTL, 
    bcmRxReasonTrillName = _SHR_RX_TRILL_NAME, 
    bcmRxReasonBfdSlowpath = _SHR_RX_BFD_SLOWPATH, 
    bcmRxReasonBfd = _SHR_RX_BFD_ERROR, 
    bcmRxReasonMirror = _SHR_RX_MIRROR, 
    bcmRxReasonRegexAction = _SHR_RX_REGEX_ACTION, 
    bcmRxReasonRegexMatch = _SHR_RX_REGEX_MATCH, 
    bcmRxReasonFailoverDrop = _SHR_RX_FAILOVER_DROP, 
    bcmRxReasonWlanTunnelError = _SHR_RX_WLAN_TUNNEL_ERROR, 
    bcmRxReasonCongestionCnmProxy = _SHR_RX_CONGESTION_CNM_PROXY, 
    bcmRxReasonCongestionCnmProxyError = _SHR_RX_CONGESTION_CNM_PROXY_ERROR, 
    bcmRxReasonCongestionCnm = _SHR_RX_CONGESTION_CNM, 
    bcmRxReasonMplsUnknownAch = _SHR_RX_MPLS_UNKNOWN_ACH, 
    bcmRxReasonMplsLookupsExceeded = _SHR_RX_MPLS_LOOKUPS_EXCEEDED, 
    bcmRxReasonMplsReservedEntropyLabel = _SHR_RX_MPLS_RESERVED_ENTROPY_LABEL, 
    bcmRxReasonMplsIllegalReservedLabel = _SHR_RX_MPLS_ILLEGAL_RESERVED_LABEL, 
    bcmRxReasonMplsRouterAlertLabel = _SHR_RX_MPLS_ROUTER_ALERT_LABEL, 
    bcmRxReasonNivPrune = _SHR_RX_NIV_PRUNE, 
    bcmRxReasonVirtualPortPrune = _SHR_RX_VIRTUAL_PORT_PRUNE, 
    bcmRxReasonNonUnicastDrop = _SHR_RX_NON_UNICAST_DROP, 
    bcmRxReasonTrillPacketPortMismatch = _SHR_RX_TRILL_PACKET_PORT_MISMATCH, 
    bcmRxReasonWlanClientMove = _SHR_RX_WLAN_CLIENT_MOVE, 
    bcmRxReasonWlanSourcePortMiss = _SHR_RX_WLAN_SOURCE_PORT_MISS, 
    bcmRxReasonWlanClientSourceMiss = _SHR_RX_WLAN_CLIENT_SOURCE_MISS, 
    bcmRxReasonWlanClientDestMiss = _SHR_RX_WLAN_CLIENT_DEST_MISS, 
    bcmRxReasonWlanMtu = _SHR_RX_WLAN_MTU, 
    bcmRxReasonL2GreSipMiss = _SHR_RX_L2GRE_SIP_MISS, 
    bcmRxReasonL2GreVpnIdMiss = _SHR_RX_L2GRE_VPN_ID_MISS, 
    bcmRxReasonTimesyncUnknownVersion = _SHR_RX_TIMESYNC_UNKNOWN_VERSION, 
    bcmRxReasonBfdUnknownVersion = _SHR_RX_BFD_UNKNOWN_VERSION, 
    bcmRxReasonBfdInvalidVersion = _SHR_RX_BFD_INVALID_VERSION, 
    bcmRxReasonBfdLookupFailure = _SHR_RX_BFD_LOOKUP_FAILURE, 
    bcmRxReasonBfdInvalidPacket = _SHR_RX_BFD_INVALID_PACKET, 
    bcmRxReasonVxlanSipMiss = _SHR_RX_VXLAN_SIP_MISS, 
    bcmRxReasonVxlanVpnIdMiss = _SHR_RX_VXLAN_VPN_ID_MISS, 
    bcmRxReasonFcoeZoneCheckFail = _SHR_RX_FCOE_ZONE_CHECK_FAIL, 
    bcmRxReasonIpmcInterfaceMismatch = _SHR_RX_IPMC_INTERFACE_MISMATCH, 
    bcmRxReasonNat = _SHR_RX_NAT, 
    bcmRxReasonTcpUdpNatMiss = _SHR_RX_TCP_UDP_NAT_MISS, 
    bcmRxReasonIcmpNatMiss = _SHR_RX_ICMP_NAT_MISS, 
    bcmRxReasonNatFragment = _SHR_RX_NAT_FRAGMENT, 
    bcmRxReasonNatMiss = _SHR_RX_NAT_MISS, 
    bcmRxReasonOAMCCMSlowpath = _SHR_RX_OAM_CCM_SLOWPATH, 
    bcmRxReasonBHHOAM = _SHR_RX_BHH_OAM_PACKET, 
    bcmRxReasonUnknownSubtendingPort = _SHR_RX_UNKNOWN_SUBTENTING_PORT, 
    bcmRxReasonReserved0 = _SHR_RX_RESERVED_0, 
    bcmRxReasonOAMMplsLmDm = _SHR_RX_OAM_MPLS_LMDM, 
    bcmRxReasonSat = _SHR_RX_SAT, 
    bcmRxReasonSampleSourceFlex = _SHR_RX_SAMPLE_SOURCE_FLEX, 
    bcmRxReasonFlexSflow = _SHR_RX_FLEX_SFLOW, 
    bcmRxReasonVxltMiss = _SHR_RX_VXLT_MISS, 
    bcmRxReasonTunnelDecapEcnError = _SHR_RX_TUNNEL_DECAP_ECN_ERROR, 
    bcmRxReasonTunnelObjectValidationFail = _SHR_RX_TUNNEL_OBJECT_VALIDATION_FAIL, 
    bcmRxReasonL3Cpu = _SHR_RX_L3_CPU, 
    bcmRxReasonTunnelAdaptLookupMiss = _SHR_RX_TUNNEL_ADAPT_LOOKUP_MISS, 
    bcmRxReasonPacketFlowSelectMiss = _SHR_RX_PACKET_FLOW_SELECT_MISS, 
    bcmRxReasonProtectionDataDrop = _SHR_RX_PROTECTION_DATA_DROP, 
    bcmRxReasonPacketFlowSelect = _SHR_RX_PACKET_FLOW_SELECT, 
    bcmRxReasonOtherLookupMiss = _SHR_RX_OTHER_LOOKUP_MISS, 
    bcmRxReasonInvalidTpid = _SHR_RX_INVALID_TPID, 
    bcmRxReasonMplsControlPacket = _SHR_RX_MPLS_CONTROL_PACKET, 
    bcmRxReasonTunnelTtlError = _SHR_RX_TUNNEL_TTL_ERROR, 
    bcmRxReasonL2HeaderError = _SHR_RX_L2_HEADER_ERROR, 
    bcmRxReasonOtherLookupHit = _SHR_RX_OTHER_LOOKUP_HIT, 
    bcmRxReasonL2SrcLookupMiss = _SHR_RX_L2_SRC_LOOKUP_MISS, 
    bcmRxReasonL2SrcLookupHit = _SHR_RX_L2_SRC_LOOKUP_HIT, 
    bcmRxReasonL2DstLookupMiss = _SHR_RX_L2_DST_LOOKUP_MISS, 
    bcmRxReasonL2DstLookupHit = _SHR_RX_L2_DST_LOOKUP_HIT, 
    bcmRxReasonL3SrcRouteLookupMiss = _SHR_RX_L3_SRC_ROUTE_LOOKUP_MISS, 
    bcmRxReasonL3SrcHostLookupMiss = _SHR_RX_L3_SRC_HOST_LOOKUP_MISS, 
    bcmRxReasonL3SrcRouteLookupHit = _SHR_RX_L3_SRC_ROUTE_LOOKUP_HIT, 
    bcmRxReasonL3SrcHostLookupHit = _SHR_RX_L3_SRC_HOST_LOOKUP_HIT, 
    bcmRxReasonL3DstRouteLookupMiss = _SHR_RX_L3_DST_ROUTE_LOOKUP_MISS, 
    bcmRxReasonL3DstHostLookupMiss = _SHR_RX_L3_DST_HOST_LOOKUP_MISS, 
    bcmRxReasonL3DstRouteLookupHit = _SHR_RX_L3_DST_ROUTE_LOOKUP_HIT, 
    bcmRxReasonL3DstHostLookupHit = _SHR_RX_L3_DST_HOST_LOOKUP_HIT, 
    bcmRxReasonVlanTranslate1Lookup1Miss = _SHR_RX_VLAN_TRANSLATE1_LOOKUP1_MISS, 
    bcmRxReasonVlanTranslate1Lookup2Miss = _SHR_RX_VLAN_TRANSLATE1_LOOKUP2_MISS, 
    bcmRxReasonMplsLookup1Miss = _SHR_RX_MPLS_LOOKUP1_MISS, 
    bcmRxReasonMplsLookup2Miss = _SHR_RX_MPLS_LOOKUP2_MISS, 
    bcmRxReasonL3TunnelLookupMiss = _SHR_RX_L3_TUNNEL_LOOKUP_MISS, 
    bcmRxReasonVlanTranslate2Lookup1Miss = _SHR_RX_VLAN_TRANSLATE2_LOOKUP1_MISS, 
    bcmRxReasonVlanTranslate2Lookup2Miss = _SHR_RX_VLAN_TRANSLATE2_LOOKUP2_MISS, 
    bcmRxReasonL2StuFail = _SHR_RX_L2_STU_FAIL, 
    bcmRxReasonSrCounterExceeded = _SHR_RX_SR_COUNTER_EXCEEDED, 
    bcmRxReasonSrCopyToCpuBit0 = _SHR_RX_SR_COPY_TO_CPU_BIT0, 
    bcmRxReasonSrCopyToCpuBit1 = _SHR_RX_SR_COPY_TO_CPU_BIT1, 
    bcmRxReasonSrCopyToCpuBit2 = _SHR_RX_SR_COPY_TO_CPU_BIT2, 
    bcmRxReasonSrCopyToCpuBit3 = _SHR_RX_SR_COPY_TO_CPU_BIT3, 
    bcmRxReasonSrCopyToCpuBit4 = _SHR_RX_SR_COPY_TO_CPU_BIT4, 
    bcmRxReasonSrCopyToCpuBit5 = _SHR_RX_SR_COPY_TO_CPU_BIT5, 
    bcmRxReasonL3HeaderMismatch = _SHR_RX_L3_HEADER_MISMATCH, 
    bcmRxReasonDLBMonitor = _SHR_RX_DLB_MONITOR, 
    bcmRxReasonETrapMonitor = _SHR_RX_ETRAP_MONITOR, 
    bcmRxReasonIntTurnAround = _SHR_RX_INT_TURNAROUND, 
    bcmRxReasonIntHopLimit = _SHR_RX_INT_HOP_LIMIT, 
    bcmRxReasonProtStatDown = _SHR_RX_PROTECTION_STATUS_DOWN, 
    bcmRxReasonCount = _SHR_RX_REASON_COUNT 
} bcm_rx_reason_t;

/* 
 * Macro to check if a reason (bcmRxReason*) is included in a set of
 * reasons (bcm_rx_reasons_t).
 * 
 * Returns:
 *   zero     => reason is not included in the set
 *   non-zero => reason is included in the set
 */
#define BCM_RX_REASON_GET(_reasons, _reason)  \
   _SHR_RX_REASON_GET(_reasons, _reason) 

/* 
 * Macro to add a reason (bcmRxReason*) to a set of reasons
 * (bcm_rx_reasons_t).
 */
#define BCM_RX_REASON_SET(_reasons, _reason)  \
   _SHR_RX_REASON_SET(_reasons, _reason) 

/* 
 * Macro to add all reasons (bcmRxReason*) to a set of reasons
 * (bcm_rx_reasons_t).
 */
#define BCM_RX_REASON_SET_ALL(_reasons)  \
   _SHR_RX_REASON_SET_ALL(_reasons) 

/* 
 * Macro to clear a reason (bcmRxReason*) from a set of reasons
 * (bcm_rx_reasons_t).
 */
#define BCM_RX_REASON_CLEAR(_reasons, _reason)  \
   _SHR_RX_REASON_CLEAR(_reasons, _reason) 

/* Macro to clear a set of reasons (bcm_rx_reasons_t). */
#define BCM_RX_REASON_CLEAR_ALL(_reasons)  \
   _SHR_RX_REASON_CLEAR_ALL(_reasons) 

/* Macro to check if a set of reasons (bcm_rx_reasons_t) is empty. */
#define BCM_RX_REASON_IS_NULL(_reasons)  \
   _SHR_RX_REASON_IS_NULL(_reasons) 

/* Macro to itterate over a set of reasons (bcm_rx_reasons_t). */
#define BCM_RX_REASON_ITER(_reasons, _reason)  \
   _SHR_RX_REASON_ITER(_reasons, _reason) 

/* 
 * Macro to count number of active reasons in a set of reasons
 * (bcm_rx_reasons_t).
 */
#define BCM_RX_REASON_COUNT(_reasons, count)  \
   _SHR_RX_REASON_COUNT(_reasons, count) 

/* Macro to compare two sets of reasons (bcm_rx_reasons_t). */
#define BCM_RX_REASON_EQ(_reasons1, _reasons2)  \
   _SHR_RX_REASON_EQ(_reasons1, _reasons2) 

/* Macro to negative compare two sets of reasons (bcm_rx_reasons_t). */
#define BCM_RX_REASON_NEQ(_reasons1, _reasons2)  \
   _SHR_RX_REASON_NEQ(_reasons1, _reasons2) 

/* 
 * Macro to perform logical AND operation on two sets of reasons
 * (bcm_rx_reasons_t).
 */
#define BCM_RX_REASON_AND(_reasons1, _reasons2)  \
   _SHR_RX_REASON_AND(_reasons1, _reasons2) 

/* 
 * Macro to perform logical OR operation on two sets of reasons
 * (bcm_rx_reasons_t).
 */
#define BCM_RX_REASON_OR(_reasons1, _reasons2)  \
   _SHR_RX_REASON_OR(_reasons1, _reasons2) 

/* 
 * Macro to perform logical XOR operation on two sets of reasons
 * (bcm_rx_reasons_t).
 */
#define BCM_RX_REASON_XOR(_reasons1, _reasons2)  \
   _SHR_RX_REASON_XOR(_reasons1, _reasons2) 

/* 
 * Macro to remove set of reasons2 (bcm_rx_reasons_t) from set of
 * reasons1 (bcm_rx_reasons_t).
 */
#define BCM_RX_REASON_REMOVE(_reasons1, _reasons2)  \
   _SHR_RX_REASON_REMOVE(_reasons1, _reasons2) 

/* Macro to negate two sets of reasons (bcm_rx_reasons_t). */
#define BCM_RX_REASON_NEGATE(_reasons1, _reasons2)  \
   _SHR_RX_REASON_NEGATE(_reasons1, _reasons2) 

#ifndef BCM_HIDE_DISPATCHABLE

/* Associate a policer to the specified set of reason codes. */
extern int bcm_rx_reasons_policer_set(
    int unit, 
    bcm_rx_reasons_t rx_reasons, 
    bcm_policer_t polid);

#endif /* BCM_HIDE_DISPATCHABLE */

/* 
 * Macro to map virtual id of MC_RESERVED traps from range [0,7] to HW
 * trap_id range [24,31]
 */
#define BCM_RX_TRAP_VIRTUAL_HW_TRAP_ID_MC_RESERVED(_id, _trap_id)  \
    (_id >7 ? _trap_id=-1 : (_trap_id = _id + 24) ) 

/* 
 * Macro to map virtual id of GENERAL/PROGRAMABLE traps from range [0,3]
 * to HW trap_id range [38,41]
 */
#define BCM_RX_TRAP_VIRTUAL_HW_TRAP_ID_PROG(_id, _trap_id)  \
    (_id >3 ? _trap_id=-1 : (_trap_id = _id + 38) ) 

/* 
 * Defines for priorities of registered PKT RX handlers. PKT RX handlers
 * are always called from highest priority to lowest priority until one
 * of the handlers returns rx_handled or rx_handled_owned.
 * 
 * When started, a default PKT RX handler is installed at PKT_RX_PRIO_MIN
 * that discards the packets.
 */
#define BCM_RX_PRIO_MIN         ((uint8)0) 
#define BCM_RX_PRIO_MAX         ((uint8)255) 

#define BCM_RX_INIT_DONE(unit)  (bcm_rx_cfg_get(unit, NULL) == 0) 

#ifndef BCM_HIDE_DISPATCHABLE

/* Initialize the RX software module for the given device. */
extern int bcm_rx_init(
    int unit);

/* Re-initialize the user level configuration for the RX module. */
extern int bcm_rx_cfg_init(
    int unit);

/* Start packet reception for the given device. */
extern int bcm_rx_start(
    int unit, 
    bcm_rx_cfg_t *cfg);

/* Stop the RX software module. */
extern int bcm_rx_stop(
    int unit, 
    bcm_rx_cfg_t *cfg);

/* Get the current configuration for the given device. */
extern int bcm_rx_cfg_get(
    int unit, 
    bcm_rx_cfg_t *cfg);

/* Boolean indication of whether RX is running on this device. */
extern int bcm_rx_active(
    int unit);

/* Start sync RX. */
extern int bcm_rx_sync_start(
    int unit, 
    uint32 flags, 
    int *sn);

/* Stop sync RX. */
extern int bcm_rx_sync_stop(
    int unit, 
    int sn);

/* Sync RX. */
extern int bcm_rx_sync(
    int unit, 
    int sn, 
    bcm_pkt_t **pkt, 
    int usec);

/* Register CPU bound packets scheduler. */
extern int bcm_rx_sched_register(
    int unit, 
    bcm_rx_sched_cb sched_cb);

/* Unregister CPU bound packets scheduler. */
extern int bcm_rx_sched_unregister(
    int unit);

/* Get next unit with CPU rx enabled. */
extern int bcm_rx_unit_next_get(
    int unit, 
    int *next_unit);

/* Get maximum cos queue number for the device. */
extern int bcm_rx_queue_max_get(
    int unit, 
    bcm_cos_queue_t *cosq);

/* 
 * Get number of packet takens available for the specific device/queue
 *                 BCM_RX_SCHED_ALL_PACKETS - queue doesn't limit number
 * of packets.
 */
extern int bcm_rx_queue_rate_limit_status_get(
    int unit, 
    bcm_cos_queue_t cosq, 
    int *packet_tokens);

/* 
 * Get number of packets awaiting processing in the specific device,
 * queue.
 */
extern int bcm_rx_queue_packet_count_get(
    int unit, 
    bcm_cos_queue_t cosq, 
    int *packet_count);

/* Register or unregister to receive callbacks for received packets. */
extern int bcm_rx_register(
    int unit, 
    const char *name, 
    bcm_rx_cb_f callback, 
    uint8 priority, 
    void *cookie, 
    uint32 flags);

/* Register or unregister to receive callbacks for received packets. */
extern int bcm_rx_unregister(
    int unit, 
    bcm_rx_cb_f callback, 
    uint8 priority);

/* 
 * Register a callback function to be called when a packet is received on
 * the specified CPU COS queue.
 */
extern int bcm_rx_queue_register(
    int unit, 
    const char *name, 
    bcm_cos_queue_t cosq, 
    bcm_rx_cb_f callback, 
    uint8 priority, 
    void *cookie, 
    uint32 flags);

/* Unregister CPU COS callback function. */
extern int bcm_rx_queue_unregister(
    int unit, 
    bcm_cos_queue_t cosq, 
    bcm_rx_cb_f callback, 
    uint8 priority);

#endif /* BCM_HIDE_DISPATCHABLE */

#define BCM_RX_COSQ_PACKET_TYPE_SWITCHED    0x1        
#define BCM_RX_COSQ_PACKET_TYPE_NON_UNICAST 0x2        
#define BCM_RX_COSQ_PACKET_TYPE_MIRROR      0x4        

#define BCM_RX_TRAP_EG_TRAP_ID_DEFAULT  0x800      

#define BCM_RX_TRAP_EG_TX_TRAP_ID_DEFAULT   0xC00      
#define BCM_RX_TRAP_EG_TX_TRAP_ID_DROP      0xC01      

#ifndef BCM_HIDE_DISPATCHABLE

/* Get number of packet to CPU COS queue mappings. */
extern int bcm_rx_cosq_mapping_size_get(
    int unit, 
    int *size);

/* Map packets to a CPU COS queue. */
extern int bcm_rx_cosq_mapping_set(
    int unit, 
    int index, 
    bcm_rx_reasons_t reasons, 
    bcm_rx_reasons_t reasons_mask, 
    uint8 int_prio, 
    uint8 int_prio_mask, 
    uint32 packet_type, 
    uint32 packet_type_mask, 
    bcm_cos_queue_t cosq);

/* Get packets to CPU COS queue mappings. */
extern int bcm_rx_cosq_mapping_get(
    int unit, 
    int index, 
    bcm_rx_reasons_t *reasons, 
    bcm_rx_reasons_t *reasons_mask, 
    uint8 *int_prio, 
    uint8 *int_prio_mask, 
    uint32 *packet_type, 
    uint32 *packet_type_mask, 
    bcm_cos_queue_t *cosq);

/* Unmap packets to a CPU COS queue. */
extern int bcm_rx_cosq_mapping_delete(
    int unit, 
    int index);

/* Get all supported reasons for CPU COS queue mapping. */
extern int bcm_rx_cosq_mapping_reasons_get(
    int unit, 
    bcm_rx_reasons_t *reasons);

/* Get all supported reasons for rx packets. */
extern int bcm_rx_reasons_get(
    int unit, 
    bcm_rx_reasons_t *reasons);

/* Assign a RX channel to a cosq. */
extern int bcm_rx_queue_channel_set(
    int unit, 
    bcm_cos_queue_t queue_id, 
    bcm_rx_chan_t chan_id);

/* Get the RX channel assigned to the given cosq. */
extern int bcm_rx_queue_channel_get(
    int unit, 
    bcm_cos_queue_t queue_id, 
    bcm_rx_chan_t *chan_id);

/* bcm_rx_channels_running */
extern int bcm_rx_channels_running(
    int unit, 
    uint32 *channels);

/* Allocate or deallocate a packet buffer as configured. */
extern int bcm_rx_alloc(
    int unit, 
    int pkt_size, 
    uint32 flags, 
    void **buf);

/* Allocate or deallocate a packet buffer as configured. */
extern int bcm_rx_free(
    int unit, 
    void *pkt_data);

/* Enqueue a data buffer to be freed later. */
extern int bcm_rx_free_enqueue(
    int unit, 
    void *pkt_data);

/* Set/get the overall packet rate for the given device. */
extern int bcm_rx_rate_set(
    int unit, 
    int pps);

/* Set/get the overall packet rate for the given device. */
extern int bcm_rx_rate_get(
    int unit, 
    int *pps);

/* 
 * Set/get the overall packet rate for the CPU that given device is
 * attached to.
 */
extern int bcm_rx_cpu_rate_set(
    int unit, 
    int pps);

/* 
 * Set/get the overall packet rate for the CPU that given device is
 * attached to.
 */
extern int bcm_rx_cpu_rate_get(
    int unit, 
    int *pps);

/* Set/get the burst size for the given device. */
extern int bcm_rx_burst_set(
    int unit, 
    int burst);

/* Set/get the burst size for the given device. */
extern int bcm_rx_burst_get(
    int unit, 
    int *burst);

/* Set/get the RX per-COS rate limiting value. */
extern int bcm_rx_cos_rate_set(
    int unit, 
    int cos, 
    int pps);

/* Set/get the RX per-COS rate limiting value. */
extern int bcm_rx_cos_rate_get(
    int unit, 
    int cos, 
    int *pps);

/* Set/get the per-COS burst setting. */
extern int bcm_rx_cos_burst_set(
    int unit, 
    int cos, 
    int burst);

/* Set/get the per-COS burst setting. */
extern int bcm_rx_cos_burst_get(
    int unit, 
    int cos, 
    int *burst);

/* Set/get the per-COS max queue length. */
extern int bcm_rx_cos_max_len_set(
    int unit, 
    int cos, 
    int max_q_len);

/* Set/get the per-COS max queue length. */
extern int bcm_rx_cos_max_len_get(
    int unit, 
    int cos, 
    int *max_q_len);

/* Clear all the RX configuration. */
extern int bcm_rx_clear(
    int unit);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Initialize a BCM RX configuration structure. */
extern void bcm_rx_cfg_t_init(
    bcm_rx_cfg_t *rx_cfg);

#if defined(BCM_RPC_SUPPORT) || defined(BCM_RCPU_SUPPORT)
#define BCM_RX_PKTLIST_COUNT_DEFAULT    64         
#endif

#if defined(BCM_RPC_SUPPORT) || defined(BCM_RCPU_SUPPORT)
/* bcm_rx_pktlist_count */
extern int bcm_rx_pktlist_count;
#endif

#if defined(BCM_RPC_SUPPORT) || defined(BCM_RCPU_SUPPORT)
/* bcm_rx_remote_pkt_alloc */
extern int bcm_rx_remote_pkt_alloc(
    int len, 
    bcm_pkt_t **pkt);
#endif

#if defined(BCM_RPC_SUPPORT) || defined(BCM_RCPU_SUPPORT)
/* bcm_rx_remote_pkt_free */
extern int bcm_rx_remote_pkt_free(
    bcm_pkt_t *pkt);
#endif

#ifndef BCM_HIDE_DISPATCHABLE

/* bcm_rx_remote_pkt_enqueue */
extern int bcm_rx_remote_pkt_enqueue(
    int unit, 
    bcm_pkt_t *pkt);

#if defined(BROADCOM_DEBUG)
/* bcm_rx_show */
extern int bcm_rx_show(
    int unit);
#endif

#endif /* BCM_HIDE_DISPATCHABLE */

/* 
 * RX Pool
 * 
 * RX Pool is not really a true API, but an implementation of an
 * efficient buffer management scheme. RX uses the RX Pool allocation and
 * free routines as the default, and the application is free to change
 * them.
 */

/* Set up the RX pool software module. */
extern int bcm_rx_pool_setup(
    int pkt_count, 
    int bytes_per_pkt);

/* Set up the per unit RX pool software module. */
extern int bcm_rx_pool_per_unit_setup(
    int unit, 
    int pkt_count, 
    int bytes_per_pkt);

/* Boolean indication of whether the RX pool module is currently set up. */
extern int bcm_rx_pool_setup_done(
    void );

/* 
 * Boolean indication of whether the per unit RX pool module is currently
 * set up.
 */
extern int bcm_rx_pool_per_unit_setup_done(
    int unit);

/* Deallocate RX pool structures. */
extern int bcm_rx_pool_cleanup(
    void );

/* Deallocate per unit RX pool structures. */
extern int bcm_rx_pool_per_unit_cleanup(
    int unit);

/* Allocate a buffer from RX pool. */
extern int bcm_rx_pool_alloc(
    int unit, 
    int size, 
    uint32 flags, 
    void **pool);

/* Deallocate a buffer allocated with =bcm_rx_pool_alloc. */
extern int bcm_rx_pool_free(
    int unit, 
    void *buf);

#if defined(BCM_RXP_DEBUG)
/* Display information on RX pool buffer status. */
extern void bcm_rx_pool_dump(
    int min, 
    int max);
#endif

#if defined(BCM_RXP_DEBUG)
/* Verify the RX pool free buffer list. */
extern void bcm_rx_pool_free_verify(void);
#endif

#if defined(BCM_RXP_DEBUG)
/* Indicate ownership of an RX pool buffer. */
extern void bcm_rx_pool_own(
    void *buf, 
    void *owner);
#endif

#if defined(BCM_RXP_DEBUG)
/* Send RX pool debugging information to an output stream. */
extern void bcm_rx_pool_report(
    int min, 
    int max);
#endif

typedef enum bcm_rx_control_e {
    bcmRxControlCRCStrip = 0,       /* Strip CRC from packets. */
    bcmRxControlVTagStrip = 1,      /* Strip VLAN tag from packets. */
    bcmRxControlRateStall = 2,      /* Use stall instead of discard. */
    bcmRxControlMultiDCB = 3,       /* Scatter data with multiple DCBs. */
    bcmRxControlOversizedOK = 4,    /* Accept packets larger than bufsize. */
    bcmRxControlIgnoreHGHeader = 5, /* Force HiGig Header into packet for fabric
                                       device. */
    bcmRxControlIgnoreSLHeader = 6, /* Force SL tag into packet on SL stacking. */
    bcmRxControlTmSnoopCount = 7    /* Indicate the number of snoop commands
                                       used for Traffic Management (TM)
                                       processing. */
} bcm_rx_control_t;

#ifndef BCM_HIDE_DISPATCHABLE

/* Get RX operating modes. */
extern int bcm_rx_control_get(
    int unit, 
    bcm_rx_control_t type, 
    int *arg);

/* Configure RX operating modes. */
extern int bcm_rx_control_set(
    int unit, 
    bcm_rx_control_t type, 
    int arg);

#endif /* BCM_HIDE_DISPATCHABLE */

typedef enum bcm_rx_redirect_e {
    bcmRxRedirectNormal = _SHR_RX_REDIRECT_NORMAL, /* Rx redirect reasons for normal
                                           packets. */
    bcmRxRedirectHigig = _SHR_RX_REDIRECT_HIGIG, /* Rx redirect reasons for higig
                                           packets. */
    bcmRxRedirectTruncated = _SHR_RX_REDIRECT_TRUNCATED /* Rx redirect reasons for truncated
                                           packets. */
} bcm_rx_redirect_t;

#ifndef BCM_HIDE_DISPATCHABLE

/* Get mode specific configured redirection reasons for rx packets. */
extern int bcm_rx_redirect_reasons_get(
    int unit, 
    bcm_rx_redirect_t mode, 
    bcm_rx_reasons_t *reasons);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Return values from PKT RX callout routines. */
typedef enum bcm_rx_trap_e {
    bcmRxTrapMimDiscardMacsaFwd = 0,    /* Triggered by port control
                                           bcmPortControlDiscardMacsaAction with
                                           BCM_PORT_CONTROL_DISCARD_MACSA_FWD. */
    bcmRxTrapMimDiscardMacsaDrop = 1,   /* Triggered by port control
                                           bcmPortControlDiscardMacsaAction with
                                           BCM_PORT_CONTROL_DISCARD_MACSA_DROP. */
    bcmRxTrapMimDiscardMacsaTrap = 2,   /*  Triggered by port control
                                           bcmPortControlDiscardMacsaAction with
                                           BCM_PORT_CONTROL_DISCARD_MACSA_TRAP. */
    bcmRxTrapMimDiscardMacsaSnoop = 3,  /* Triggered by port control
                                           bcmPortControlDiscardMacsaAction with
                                           BCM_PORT_CONTROL_DISCARD_MACSA_SNOOP. */
    bcmRxTrapMimTeSaMove = 4,           /*  Packet's BVID is in TE-BVID range,
                                           SA lookup succeeds, butSystem Port ID
                                           of SA lookup is different from source
                                           system Port ID. */
    bcmRxTrapMimTeSaUnknown = 5,        /*  Packet's BVID is in TE-BVID range,
                                           SA lookup fails. */
    bcmRxTrapMimSaMove = 6,             /* Packet's BVID is not in TE-BVID
                                           range, SA lookup succeeds. */
    bcmRxTrapMimSaUnknown = 7,          /* Packet's BVID is not in TE-BVID
                                           range, SA lookup fails. */
    bcmRxTrapAuthSaLookupFail = 8,      /* SA authentication fails: SA lookup
                                           fails. */
    bcmRxTrapAuthSaPortFail = 9,        /* SA authentication fails: SA lookup
                                           succeeds in an unpermitted port. */
    bcmRxTrapAuthSaVlanFail = 10,       /* SA authentication fails: SA lookup
                                           succeeds in an unpermitted VLAN. */
    bcmRxTrapSaMulticast = 11,          /* SA is multicast. */
    bcmRxTrapSaEqualsDa = 12,           /* SA equals DA. */
    bcmRxTrap8021xFail = 13,            /* 8021x authentication fails. */
    bcmRxTrapArpMyIp = 14,              /* If InPort is enabled for ARP trapping
                                           AND ARP request TPA is equal to My-IP
                                           (two configurable IP addresses). */
    bcmRxTrapArp = 15,                  /* ARP Request incoming on InPort which
                                           is enabled for ARP trapping. If DA is
                                           set to be ignored for ARP replies,
                                           ARP replies are also trapped with
                                           this trap code. */
    bcmRxTrapIgmpMembershipQuery = 16,  /* Packet is IGMP and first octet in the
                                           IGMP payload is 0x11. */
    bcmRxTrapIgmpReportLeaveMsg = 17,   /* Packet is IGMP and first octet in the
                                           IGMP payload is 0x12, 0x16, 0x17, or
                                           0x22. */
    bcmRxTrapIgmpUndefined = 18,        /* Packet is IGMP and first octet in the
                                           IGMP payload is not 0x11, 0x12, 0x16,
                                           0x17, or 0x22. */
    bcmRxTrapIcmpv6MldMcListenerQuery = 19, /* . */
    bcmRxTrapL2Cache = 20,              /* Triggered by  bcm_l2_cache_set 
                                           entry. */
    bcmRxTrapDhcpv6Server = 21,         /* DHCP packet sent to server over
                                           IPv6oE. */
    bcmRxTrapDhcpv6Client = 22,         /* DHCP packet sent to client over
                                           IPv6oE. */
    bcmRxTrapPortNotVlanMember = 23,    /*  Initial VID membership error. */
    bcmRxTrapHeaderSizeErr = 24,        /* Parser indicates header size error. */
    bcmRxTrapMyBmacUknownTunnel = 25,   /* BSA lookup fail and (BDA = My-BDA). */
    bcmRxTrapMyBmacUnknownISid = 26,    /*   Unknown I-SID. */
    bcmRxTrapStpStateBlock = 27,        /* Packet ingresses on a blocked port.
                                           Note - BPDU will be forwarded with
                                           strength 6. */
    bcmRxTrapStpStateLearn = 28,        /* Packet ingresses a port in a LEARN
                                           state. */
    bcmRxTrapIpCompMcInvalidIp = 29,    /*   L2 compatible MC, but IP does not
                                           match. */
    bcmRxTrapMyMacAndIpDisabled = 30,   /*   Terminated My-MAC over IP, but
                                           routing is disabled for InRIF. */
    bcmRxTrapTrillVersion = 31,         /* Invalid TRILL version. */
    bcmRxTrapTrillTtl0 = 32,            /* Invalid TRILL TTL. */
    bcmRxTrapTrillChbh = 33,            /* Unsupported TRILL option flags. */
    bcmRxTrapTrillUnknonwnIngressNickname = 34, /* Unknown ingress nickname. */
    bcmRxTrapTrillCite = 35,            /* Unsupported TRILL options flags. */
    bcmRxTrapTrillIllegalInnerMc = 36,  /*  Invalid packet format. */
    bcmRxTrapMyMacAndMplsDisable = 37,  /* Terminated My-MAC over MPLS, but MPLS
                                           is disabled for InRIF. */
    bcmRxTrapArpReply = 38,             /* ARP reply to My-MAC. */
    bcmRxTrapMyMacAndUnknownL3 = 39,    /* Terminated My-MAC but L3 protocol is
                                           unknown. */
    bcmRxTrapMplsLabel0150 = 40,        /* Triggered by MPLS labels 0-15
                                           forwarding Trap Code. */
    bcmRxTrapMplsLabel0151 = 41,        /* Triggered by MPLS labels 0-15
                                           forwarding Trap Code. */
    bcmRxTrapMplsLabel0152 = 42,        /* Triggered by MPLS labels 0-15
                                           forwarding Trap Code. */
    bcmRxTrapMplsLabel0153 = 43,        /* Triggered by MPLS labels 0-15
                                           forwarding Trap Code. */
    bcmRxTrapMplsTerminationFail = 44,  /* MPLS already terminated twice by
                                           label range match. Additional labels
                                           may not be terminated by Label range
                                           match. */
    bcmRxTrapMplsUnexpectedBos = 45,    /* Terminated MPLS label indicates that
                                           another MPLS shim is to follow,
                                           however the terminated label is BOS. */
    bcmRxTrapMplsUnexpectedNoBos = 46,  /* Reserved MPLS label (0.15) is mapped
                                           to this action by
                                           ppd_mpls_term_reserved_label_info_set(). */
    bcmRxTrapCfmAcceleratedIngress = 47, /* ITU Y.1731 packet observed (CFM). */
    bcmRxTrapIllegelPacketFormat = 48,  /* Parser failure. */
    bcmRxTrapL2DiscardMacsaFwd = 49,    /* Triggered by control
                                           bcmPortControlDiscardMacsaAction with
                                            BCM_PORT_CONTROL_DISCARD_MACSA_FWD. */
    bcmRxTrapL2DiscardMacsaDrop = 50,   /* Triggered by control
                                           bcmPortControlDiscardMacsaAction with
                                            BCM_PORT_CONTROL_DISCARD_MACSA_FWD . */
    bcmRxTrapL2DiscardMacsaTrap = 51,   /* Triggered by control
                                           bcmPortControlDiscardMacsaAction with
                                            BCM_PORT_CONTROL_DISCARD_MACSA_DROP. */
    bcmRxTrapL2DiscardMacsaSnoop = 52,  /* Triggered by control
                                           bcmPortControlDiscardMacsaAction with
                                            BCM_PORT_CONTROL_DISCARD_MACSA_TRAP. */
    bcmRxTrapL2Learn0 = 53,             /* Triggered by bcm_port_learn_set with
                                           flag =
                                           BCM_PORT_LEARN_ARL|BCM_PORT_LEARN_FWD. */
    bcmRxTrapL2Learn1 = 54,             /* Triggered by bcm_port_learn_set with
                                           flag =
                                           BCM_PORT_LEARN_CPU|BCM_PORT_LEARN_FWD. */
    bcmRxTrapL2Learn2 = 55,             /* Triggered by bcm_port_learn_set with
                                           flag = BCM_PORT_LEARN_ARL. */
    bcmRxTrapL2Learn3 = 56,             /* Triggered by bcm_port_learn_set with
                                           flag = BCM_PORT_LEARN_FWD |
                                           BCM_PORT_LEARN_CPU. */
    bcmRxTrapVlanUnknownDa = 57,        /* Per VLAN/VSI 8 flooding profiled can
                                           be set for unknown packets. These
                                           Trap code define the flooding
                                           profile. The flooding multicast group
                                           is the VLAN/VSI base flooding group +
                                           the flooding offset. */
    bcmRxTrapExternalLookupError = 58,  /* ELK is accessed and returns an error. */
    bcmRxTrapL2DlfFwd = 59,             /* per port trap when DA is not found,
                                           see bcmPortControlUnknownMacDaAction
                                           BCM_PORT_CONTROL_UNKNOWN_MACDA_FWD. */
    bcmRxTrapL2DlfDrop = 60,            /* BCM_PORT_CONTROL_UNKNOWN_MACDA_DROP. */
    bcmRxTrapL2DlfTrap = 61,            /* BCM_PORT_CONTROL_UNKNOWN_MACDA_TRAP. */
    bcmRxTrapL2DlfSnoop = 62,           /* BCM_PORT_CONTROL_UNKNOWN_MACDA_SNOOP. */
    bcmRxTrapExtendedP2pLookupFail = 63, /* Transparent P2P Lookup key is not
                                           found in the ELK/LEM. */
    bcmRxTrapSameInterface = 64,        /* Source interface is equal to
                                           destination interface (hair-pin). */
    bcmRxTrapTrillUnknownUc = 65,       /* Forwarding Code is TRILL, lookup key
                                           is not found in ELK/LEM. */
    bcmRxTrapTrillUnknownMc = 66,       /* Forwarding Code is TRILL, lookup key
                                           is not found in ELK/LEM. */
    bcmRxTrapUcLooseRpfFail = 67,       /* Forwarding Code is IPv4 UC and RPF
                                           FEC Pointer Valid is not set. */
    bcmRxTrapDefaultUcv6 = 68,          /* IPv6 UC default forwarding. */
    bcmRxTrapDefaultMcv6 = 69,          /* IPv6 MC default forwarding. */
    bcmRxTrapMplsP2pNoBos = 70,         /* Lookup key is found in ELK/LEM,
                                           P2P-Service If lookup result is set,
                                           and header is not BOS.. */
    bcmRxTrapMplsControlWordTrap = 71,  /* Lookup key is found in ELK/LEM,
                                           P2P-Service If lookup result is set,
                                           lookup result determines that there's
                                           a control word, nibble after MPLS
                                           stack equal '1'. */
    bcmRxTrapMplsControlWordDrop = 72,  /* Lookup key is found in ELK/LEM,
                                           P2P-Service If lookup result is set,
                                           lookup result determines that there's
                                           a control word, nibble after MPLS
                                           stack does not equal '1' or '0'. */
    bcmRxTrapMplsUnknownLabel = 73,     /* Lookup key is not found in ELK/LEM. */
    bcmRxTrapMplsExtendP2pMplsx4 = 74,  /* Extended P2P service with 4 MPLS
                                           labels. */
    bcmRxTrapFrwrdIgmpMembershipQuery = 75, /* Forwarded packet is IGMP and first
                                           octet in the IGMP payload is 0x11. */
    bcmRxTrapFrwrdIgmpReportLeaveMsg = 76, /* Forwarded packet is IGMP and first
                                           octet in the IGMP payload is 0x12,
                                           0x16, 0x17, or 0x22. */
    bcmRxTrapFrwrdIgmpUndefined = 77,   /* Forwarded packet is IGMP and first
                                           octet in the IGMP payload is not
                                           0x11, 0x12, 0x16, 0x17, or 0x22. */
    bcmRxTrapFrwrdIcmpv6MldMcListenerQuery = 78, /* Forwarded packet is ICMPv6 with an
                                           MLD type, IPv6 packet with IP
                                           protocol 58 and the ICMPv6 type is
                                           130. */
    bcmRxTrapFrwrdIcmpv6MldReportDone = 79, /* Forwarded packet is ICMPv6 with an
                                           MLD type, IPv6 packet with IP
                                           protocol 58 and the ICMPv6 type is
                                           131,132 or 143. */
    bcmRxTrapFrwrdIcmpv6MldUndefined = 80, /* Forwarded packet is ICMPv6 with an
                                           MLD type, IPv6 packet with IP
                                           protocol 58 and the ICMPv6 type is
                                           other than 130,131,132 or 143. */
    bcmRxTrapIpv4VersionError = 81,     /* Version is different than 4. */
    bcmRxTrapIpv4ChecksumError = 82,    /*  IHL is 5 and the checksum over the
                                           first 20 bytes doesn't verify. */
    bcmRxTrapIpv4HeaderLengthError = 83, /* IHL (Internet Header Length) is less
                                           than 5. */
    bcmRxTrapIpv4TotalLengthError = 84, /* Total length is less than 20. */
    bcmRxTrapIpv4Ttl0 = 85,             /* TTL is equal to 0. */
    bcmRxTrapIpv4HasOptions = 86,       /* IHL (Internet Header Length) is
                                           greater than 5. */
    bcmRxTrapIpv4Ttl1 = 87,             /* In-TTL is 0. */
    bcmRxTrapIpv4SipEqualDip = 88,      /* Source-IP is equal to destination IP. */
    bcmRxTrapIpv4DipZero = 89,          /* Destination IP is 0. */
    bcmRxTrapIpv4SipIsMc = 90,          /* Source-IP is multicast. */
    bcmRxTrapIpv4TunnelTerminationAndFragmented = 91, /* Fragmented  IPv4 packet over an IPv4
                                           tunnel. */
    bcmRxTrapIpv6VersionError = 92,     /* Version is different than 6. */
    bcmRxTrapIpv6HopCount0 = 93,        /* Hop count (TTL) is 0. */
    bcmRxTrapIpv6HopCount1 = 94,        /* Hop count (TTL) is 1. */
    bcmRxTrapIpv6UnspecifiedDestination = 95, /* Forwarding header DIP = ::. */
    bcmRxTrapIpv6LoopbackAddress = 96,  /* DIP = ::1 or SIP = ::1. */
    bcmRxTrapIpv6MulticastSource = 97,  /* The MSB of the SIP = 0xFF. */
    bcmRxTrapIpv6NextHeaderNull = 98,   /* Next-protocol is zero. */
    bcmRxTrapIpv6UnspecifiedSource = 99, /* SIP = ::. */
    bcmRxTrapIpv6LocalLinkDestination = 100, /* Bits 127:118 of the destination-IP
                                           are equal to 0x3FA. */
    bcmRxTrapIpv6LocalSiteDestination = 101, /* Bits 127:118 of the DIP = 0x3FB
                                           (deprecated). */
    bcmRxTrapIpv6LocalLinkSource = 102, /* Bits 127:118 of the SIP = 0x3FA. */
    bcmRxTrapIpv6LocalSiteSource = 103, /* Bits 127:118 of the SIP = 0x3FB. */
    bcmRxTrapIpv6Ipv4CompatibleDestination = 104, /* Bits 127:32 of the DIP = 0. */
    bcmRxTrapIpv6Ipv4MappedDestination = 105, /* Bits 127:32 of the DIP are equal to
                                           0000_FFF_0000_0000_0000_0000. */
    bcmRxTrapIpv6MulticastDestination = 106, /* MSB of the DIP=0xFF. */
    bcmRxTrapMplsTtl0 = 107,            /* TTL is equal to 0. */
    bcmRxTrapMplsTtl1 = 108,            /* TTL is equal to 1. */
    bcmRxTrapTcpSnFlagsZero = 109,      /* L4 Sequence-Number and Flags (6) are
                                           both zero. */
    bcmRxTrapTcpSnZeroFlagsSet = 110,   /* L4 Sequence-Number is zero and either
                                           Flags. FIN, Flags. URG or FLAGS. PSH
                                           are set. */
    bcmRxTrapTcpSynFin = 111,           /* Both Flags. SYN and Flags. FIN are
                                           set. */
    bcmRxTrapTcpEqualPorts = 112,       /* Source-Port equals Destination-Port. */
    bcmRxTrapTcpFragmentIncompleteHeader = 113, /* L3 is IPv4 and IP-Header. Fragmented
                                           and IP-Header. Fragment-Offset zero
                                           and (IPv4-Header. Total-Length - 4 *
                                           IPv4-Header. IHL) is less than 20B. */
    bcmRxTrapTcpFragmentOffsetLt8 = 114, /* L3 is IPv4 and IP-Header. Fragmented
                                           and IP-Header. Fragment-Offset is
                                           less than 8. */
    bcmRxTrapUdpEqualPorts = 115,       /* Source-Port equals Destination-Port. */
    bcmRxTrapIcmpDataGt576 = 116,       /* L3 is IPv4 and (IPv4-Header.
                                           Total-Length - 4* IPv4-Header. IHL)
                                           is greater than 576B or layer-3 is
                                           IPv6 and IPv6-Header. Payload-Length
                                           is greater than 576B. */
    bcmRxTrapIcmpFragmented = 117,      /* IP-Header. Fragmented is set. */
    bcmRxTrapFailoverFacilityInvalid = 118, /* Both Destination-0-Valid and
                                           Destination-1-Valid are not set. */
    bcmRxTrapUcStrictRpfFail = 119,     /* UC-RPF-Mode is 'Strict' and OutRIF is
                                           not equal to packet InRIF . */
    bcmRxTrapMcExplicitRpfFail = 120,   /* RPF-Entry. Expected-InRIF is not
                                           equal to packet InRIF Relevant when
                                           FEC-Entry. MC-RPF-Mode is 'Explicit'. */
    bcmRxTrapMcUseSipRpfFail = 121,     /* Out-RIF is not equal to In-RIF when
                                           MC-RPF-Mode is 'Use-SIP-WITH-ECMP'
                                           Note: . */
    bcmRxTrapMcUseSipMultipath = 122,   /* Found RPF-ECMP-Group-Size > '1'
                                           Relevant when MC-RPF-Mode is
                                           'Use-SIP'. */
    bcmRxTrapIcmpRedirect = 123,        /* ICMP-Redirect is enabled,
                                           Forwarding-Code is IPv4|6-UC, and
                                           packet InRIF is equal to FEC-Entry.
                                           OutRIF. */
    bcmRxTrapOamp = 124,                /* . */
    bcmRxTrapOampTrapErr = 125,         /* Packet arrived to the OAMP with
                                           illegal trap code. */
    bcmRxTrapOampTypeErr = 126,         /* Packet arrived to the OAMP with
                                           illegal mep type. */
    bcmRxTrapOampRmepErr = 127,         /* Packet arrived to the OAMP with RMEP
                                           index miss. */
    bcmRxTrapOampMaidErr = 128,         /* Packet arrived to the OAMP with MAID
                                           miss. */
    bcmRxTrapOampMdlErr = 129,          /* Packet arrived to the OAMP with MDL
                                           miss. */
    bcmRxTrapOampCcmIntrvErr = 130,     /* Packet arrived to the OAMP with CCM
                                           interval miss. */
    bcmRxTrapOampMyDiscErr = 131,       /* Packet arrived to the OAMP with My
                                           Discriminator miss (BFD). */
    bcmRxTrapOampSrcIpErr = 132,        /* Packet arrived to the OAMP with
                                           source IP address miss (BFD). */
    bcmRxTrapOampYourDiscErr = 133,     /* Packet arrived to the OAMP with Your
                                           Discriminator miss (BFD). */
    bcmRxTrapOampSrcPortErr = 134,      /* Packet arrived to the OAMP with UDP
                                           source port miss (BFD). */
    bcmRxTrapOampRmepStateChange = 135, /* BFD packet arrived that does not
                                           match the current RMEP state. */
    bcmRxTrapOampParityErr = 136,       /* Parity error occurred in the OAMP. */
    bcmRxTrapOampTimestampErr = 137,    /* Packet arrived to the OAMP with
                                           timestamp miss. */
    bcmRxTrapOampProtection = 138,      /* OAMP protection packet. */
    bcmRxTrapOamEthAccelerated = 139,   /* . */
    bcmRxTrapOamMplsAccelerated = 140,  /* In T20E this trap code cannot be used
                                           in
                                           ppd_trap_frwrd_profile_info_set(),ppd_trap_snoop*_profile_info_set()
                                           as trap_ndx, it's only used as
                                           Trap-code in the packet header. */
    bcmRxTrapOamBfdIpTunnelAccelerated = 141, /* . */
    bcmRxTrapOamBfdPweAccelerated = 142, /* . */
    bcmRxTrapOamEthUpAccelerated = 143, /* . */
    bcmRxTrapEgPortNotVlanMember = 144, /* egress vlan membership. */
    bcmRxTrapEgHairPinFilter = 145,     /* . */
    bcmRxTrapEgSplitHorizonFilter = 146, /* . */
    bcmRxTrapEgUnknownDa = 147,         /* uc unknown DA. */
    bcmRxTrapEgMtuFilter = 148,         /* packet size > mtu. */
    bcmRxTrapEgPvlanFilter = 149,       /* private vlan filter. */
    bcmRxTrapEgDiscardFrameTypeFilter = 150, /* not acceptable frame type on port
                                           (tagged, untagged). */
    bcmRxTrapEgTrillHairPinFilter = 151, /* trill same in/out interface. */
    bcmRxTrapEgTrillBounceBack = 152,   /* prevent bounce back of trill
                                           terminated unicast packets by the
                                           egress router bridge in case of a DA
                                           not found. */
    bcmRxTrapEgTrillTtl0 = 153,         /* trill invalid ttl (egress). */
    bcmRxTrapEgIpmcTtlErr = 154,        /* IPv4 MC packet with invalid ttl. */
    bcmRxTrapEgCfmAccelerated = 155,    /* CFM packet at egress. */
    bcmRxTrapDssStacking = 156,         /* Trap according to Dss stacking denail
                                           (history Bitmap). */
    bcmRxTrapLagMulticast = 157,        /* Trap Lag Multicast Packets. */
    bcmRxTrapExEgCnm = 158,             /* CNM packet. */
    bcmRxTrapTrillDesignatedVlanNoMymac = 159, /* EoTrilloE packet is not designtated
                                           vlan but with my-mac, or designated
                                           vlan but without my-mac. Disable
                                           bridging for such packets. */
    bcmRxTrapAdjacentCheckFail = 160,   /* TRILL adjacent check fail. */
    bcmRxTrapFcoeSrcIdMismatchSa = 161, /* FCoE, where FC.SrC is mismatch
                                           Eth.SA. */
    bcmRxTrapSipMove = 162,             /* sip transplant. */
    bcmRxTrapOamY1731MplsTp = 163,      /* . */
    bcmRxTrapOamY1731Pwe = 164,         /* . */
    bcmRxTrapOamBfdIpv4 = 165,          /* . */
    bcmRxTrapOamBfdMpls = 166,          /* . */
    bcmRxTrapOamBfdPwe = 167,           /* . */
    bcmRxTrapOamBfdCcMplsTp = 168,      /* . */
    bcmRxTrapOamBfdCvMplsTp = 169,      /* . */
    bcmRxTrapOamLevel = 170,            /* OAM packet with mdlevel below highest
                                           MEP on active side. */
    bcmRxTrapOamPassive = 171,          /* OAM packet equal or below highest MEP
                                           level on passive side. */
    bcmRxTrap1588 = 172,                /* 1588 protocol packet. */
    bcmRxTrapMplsLabelIndexNoSupport = 173, /* No support to forward according to
                                           MPLS forth label. */
    bcmRxTrapDhcpv4Client = 174,        /* DHCP packet sent to client over
                                           IPv4oE. */
    bcmRxTrapDhcpv4Server = 175,        /* DHCP packet sent to server over
                                           IPv4oE. */
    bcmRxTrapEtherIpVersion = 176,      /* IPv4 version error, for
                                           IPv4oEtheroIPv4oEth packet. */
    bcmRxTrapEgressObjectAccessed = 177, /* Egress object entry was accessed due
                                           to packet lookup. */
    bcmRxTrapIcmpv6MldReportDone = 178, /* ICMPv6 packet with an MLD with done
                                           message. */
    bcmRxTrapIcmpv6MldUndefined = 179,  /* ICMPv6 packet with an MLD with other
                                           message. */
    bcmRxTrapFailover1Plus1Fail = 180,  /* 1 plus 1 protected LIF and failover
                                           status is down. */
    bcmRxTrapEgInvalidDestPort = 181,   /* Egress trap: Invalid out port number. */
    bcmRxTrapEgIpv4VersionError = 182,  /* Egress trap: Version is different
                                           than 4.. */
    bcmRxTrapEgIpv4ChecksumError = 183, /* Egress trap: IHL is 5 and the
                                           checksum over the first 20 bytes
                                           doesn't verify. */
    bcmRxTrapEgIpv4HeaderLengthError = 184, /* Egress trap: IHL (Internet Header
                                           Length) is less than 5. */
    bcmRxTrapEgIpv4TotalLengthError = 185, /* Egress trap: Total length is less
                                           than 20. */
    bcmRxTrapEgIpv4Ttl0 = 186,          /* Egress trap: TTL is equal to 0. */
    bcmRxTrapEgIpv4HasOptions = 187,    /* Egress trap: IHL (Internet Header
                                           Length) is greater than 5. */
    bcmRxTrapEgIpv4Ttl1 = 188,          /* Egress trap: In-TTL is 0. */
    bcmRxTrapEgIpv4SipEqualDip = 189,   /* Egress trap: Source-IP is equal to
                                           destination IP. */
    bcmRxTrapEgIpv4DipZero = 190,       /* Egress trap: Destination IP is 0. */
    bcmRxTrapEgIpv4SipIsMc = 191,       /* Egress trap: Source-IP is multicast. */
    bcmRxTrapEgIpv6UnspecifiedDestination = 192, /* Egress trap: Forwarding header DIP =
                                           ::. */
    bcmRxTrapEgIpv6LoopbackAddress = 193, /* Egress trap: DIP = ::1 or SIP = ::1. */
    bcmRxTrapEgIpv6MulticastSource = 194, /* Egress trap: The MSB of the SIP =
                                           0xFF. */
    bcmRxTrapEgIpv6UnspecifiedSource = 195, /* Egress trap: SIP = ::. */
    bcmRxTrapEgIpv6LocalLinkDestination = 196, /* Egress trap: Bits 127:118 of the
                                           destination-IP are equal to 0x3FA. */
    bcmRxTrapEgIpv6LocalSiteDestination = 197, /* Egress trap: Bits 127:118 of the DIP
                                           = 0x3FB (deprecated). */
    bcmRxTrapEgIpv6LocalLinkSource = 198, /* Egress trap: Bits 127:118 of the SIP
                                           = 0x3FA. */
    bcmRxTrapEgIpv6LocalSiteSource = 199, /* Egress trap: Bits 127:118 of the SIP
                                           = 0x3FB. */
    bcmRxTrapEgIpv6Ipv4CompatibleDestination = 200, /* Egress trap: Bits 127:32 of the DIP =
                                           0. */
    bcmRxTrapEgIpv6Ipv4MappedDestination = 201, /* Egress trap: Bits 127:32 of the DIP
                                           are equal to
                                           0000_FFF_0000_0000_0000_0000. */
    bcmRxTrapEgIpv6MulticastDestination = 202, /* Egress trap: MSB of the DIP=0xFF. */
    bcmRxTrapEgIpv6NextHeaderNull = 203, /* Egress trap: Next-protocol is zero. */
    bcmRxTrapUserDefine = 204,          /* User define traps. */
    bcmRxTrapReserved = 205,            /* Reserved */
    bcmRxTrapFcoeZoneCheckFail = 206,   /* Fcoe zone check failed. */
    bcmRxTrapArplookupFail = 207,       /* For ARP packet, lookup for VRF and
                                           TPA (IP) failed. */
    bcmRxTrapL2cpPeer = 208,            /* L2CP trapped to peer destination. */
    bcmRxTrapL2cpDrop = 209,            /* L2CP dropped. */
    bcmRxTrapMimMyBmacMulticastContinue = 210, /* Terminated BMAC header indicates
                                           Multicast. Continue on both BMAC
                                           header and CMAC header. */
    bcmRxTrapBfdEchoOverIpv4 = 211,     /* IPv4 BFD Echo. */
    bcmRxTrapDfltDroppedPacket = 212,   /* Dropped packet */
    bcmRxTrapDfltRedirectToCpuPacket = 213, /* Packet redirected to CPU */
    bcmRxTrapRedirectToCpuOamPacket = 214, /* OAM Packet redirected to CPU */
    bcmRxTrapSnoopOamPacket = 215,      /* OAM Packet snooped */
    bcmRxTrapRecycleOamPacket = 216,    /* RxTrapRecycleOamPacket */
    bcmRxTrapItmhSnoop0 = 217,          /* ITMH packet with Snoop field equal to
                                           0 */
    bcmRxTrapItmhSnoop1 = 218,          /* ITMH packet with Snoop field equal to
                                           1 */
    bcmRxTrapItmhSnoop2 = 219,          /* ITMH packet with Snoop field equal to
                                           2 */
    bcmRxTrapItmhSnoop3 = 220,          /* ITMH packet with Snoop field equal to
                                           3 */
    bcmRxTrapItmhSnoop4 = 221,          /* ITMH packet with Snoop field equal to
                                           4 */
    bcmRxTrapItmhSnoop5 = 222,          /* ITMH packet with Snoop field equal to
                                           5 */
    bcmRxTrapItmhSnoop6 = 223,          /* ITMH packet with Snoop field equal to
                                           6 */
    bcmRxTrapItmhSnoop7 = 224,          /* ITMH packet with Snoop field equal to
                                           7 */
    bcmRxTrapItmhSnoop8 = 225,          /* ITMH packet with Snoop field equal to
                                           8 */
    bcmRxTrapItmhSnoop9 = 226,          /* ITMH packet with Snoop field equal to
                                           9 */
    bcmRxTrapItmhSnoop10 = 227,         /* ITMH packet with Snoop field equal to
                                           10 */
    bcmRxTrapItmhSnoop11 = 228,         /* ITMH packet with Snoop field equal to
                                           11 */
    bcmRxTrapItmhSnoop12 = 229,         /* ITMH packet with Snoop field equal to
                                           12 */
    bcmRxTrapItmhSnoop13 = 230,         /* ITMH packet with Snoop field equal to
                                           13 */
    bcmRxTrapItmhSnoop14 = 231,         /* ITMH packet with Snoop field equal to
                                           14 */
    bcmRxTrapItmhSnoop15 = 232,         /* ITMH packet with Snoop field equal to
                                           15 */
    bcmRxTrapFcoeFcfPacket = 233,       /* FCF FCoE packets with fixed
                                           forwarding-header location */
    bcmRxTrapVlanTagDiscard = 234,      /* Discarded packets according to their
                                           VLAN Tag configuration */
    bcmRxTrapVlanTagAccept = 235,       /* Accepted packets according to their
                                           VLAN Tag configuration */
    bcmRxTrap1588Discard = 236,         /* Discarded 1588 packets */
    bcmRxTrap1588Accepted = 237,        /* Accepted 1588 packets */
    bcmRxTrapInnerIpCompMcInvalidIp = 238, /* L2 compatible MC in inner Ethernet,
                                           but IP does not match */
    bcmRxTrapIllegalReservedLabel = 239, /* Unexpected MPLS reserved label. */
    bcmRxTrapInnerMyMacAndIpDisabled = 240, /* Terminated Inner-My-MAC over IP, but
                                           routing is disabled for InRIF */
    bcmRxTrapEgTxFieldSnoop0 = 241,     /* Egress snoop from Egress Field
                                           Processor profile 0 */
    bcmRxTrapEgTxFieldSnoop1 = 242,     /* Egress snoop from Egress Field
                                           Processor profile 1 */
    bcmRxTrapEgTxFieldSnoop2 = 243,     /* Egress snoop from Egress Field
                                           Processor profile 2 */
    bcmRxTrapEgTxFieldSnoop3 = 244,     /* Egress snoop from Egress Field
                                           Processor profile 3 */
    bcmRxTrapEgTxFieldSnoop4 = 245,     /* Egress snoop from Egress Field
                                           Processor profile 4 */
    bcmRxTrapEgTxFieldSnoop5 = 246,     /* Egress snoop from Egress Field
                                           Processor profile 5 */
    bcmRxTrapEgTxFieldSnoop6 = 247,     /* Egress snoop from Egress Field
                                           Processor profile 6 */
    bcmRxTrapEgTxFieldSnoop7 = 248,     /* Egress snoop from Egress Field
                                           Processor profile 7 */
    bcmRxTrapEgTxFieldSnoop8 = 249,     /* Egress snoop from Egress Field
                                           Processor profile 8 */
    bcmRxTrapEgTxFieldSnoop9 = 250,     /* Egress snoop from Egress Field
                                           Processor profile 9 */
    bcmRxTrapEgTxFieldSnoop10 = 251,    /* Egress snoop from Egress Field
                                           Processor profile 10 */
    bcmRxTrapEgTxFieldSnoop11 = 252,    /* Egress snoop from Egress Field
                                           Processor profile 11 */
    bcmRxTrapEgTxFieldSnoop12 = 253,    /* Egress snoop from Egress Field
                                           Processor profile 12 */
    bcmRxTrapEgTxFieldSnoop13 = 254,    /* Egress snoop from Egress Field
                                           Processor profile 13 */
    bcmRxTrapEgTxFieldSnoop14 = 255,    /* Egress snoop from Egress Field
                                           Processor profile 14 */
    bcmRxTrapEgTxFieldSnoop15 = 256,    /* Egress snoop from Egress Field
                                           Processor profile 15 */
    bcmRxTrapOutVPortDiscard = 257,     /* Out-VPort discarding any traffic */
    bcmRxTrapEgTxStpStateFail = 258,    /* ess STP state failure */
    bcmRxTrapEgTxProtectionPathUnexpected = 259, /* Unexpected Traffic on a Protecting
                                           Path */
    bcmRxTrapOutVPortLookupFail = 260,  /* Out-VPort lookup fail */
    bcmRxTrapOamBfdIpv6 = 261,          /* Bfd over Ipv6 trap code */
    bcmRxTrapOamMipSnoop2ndPass = 262,  /* Snoop OAM packets with egress info
                                           (out port). */
    bcmRxTrapSat0 = 263,                /* Sat trap code No 0 */
    bcmRxTrapSat1 = 264,                /* Sat trap code No 1 */
    bcmRxTrapSat2 = 265,                /* Sat trap code No 2 */
    bcmRxTrapEgTxPortNotVlanMember = 266, /* Egress STP state failure */
    bcmRxTrapEgTxDiscardFrameTypeFilter = 267, 
    bcmRxTrapEgTxMtuFilter = 268, 
    bcmRxTrapEgTxSplitHorizonFilter = 269, 
    bcmRxTrapOamUpMEP = 270,            /* Default trap code for OAM Up MEPs */
    bcmRxTrapBfdOamDownMEP = 271,       /* Default trap code for OAM Down MEPs
                                           and BFD */
    bcmRxTrapOamUpMEP2 = 272,           /* Default destination is OAMP */
    bcmRxTrapOamUpMEP3 = 273, 
    bcmRxTrapOamUpMEP4 = 274,           /* To be used by
                                           bcm_oam_endpoint_action_set */
    bcmRxTrapSer = 275,                 /* Packet which has SER (mem-soft-error)
                                           which accumulated along the pipe
                                           Ingress . */
    bcmRxTrapEgTxSer = 276,             /* ETPP SW Error Recovery trap. */
    bcmRxTrapEgSer = 277,               /* ERPP SW Error Recovery trap. */
    bcmRxTrapMplsTunnelTerminationTtl0 = 278, /* Mpls tunnel termination trap with TTL
                                           equal to 0. */
    bcmRxTrapMplsTunnelTerminationTtl1 = 279, /* Mpls tunnel termination trap with TTL
                                           equal to 1. */
    bcmRxTrapMplsForwardingTtl0 = 280,  /* Mpls forwarding trap with TTL equal
                                           to 0. */
    bcmRxTrapMplsForwardingTtl1 = 281,  /* Mpls forwarding trap with TTL equal
                                           to 1. */
    bcmRxTrapOampChanTypeMissErr = 282, /* Mpls OAM channel type mismatch error */
    bcmRxTrapOampFlexCrcMissErr = 283,  /* OAM PDU flex CRC mismacth error */
    bcmRxTrapNdp = 284,                 /* An ICMP-NDP Neighbor Solicitation
                                           request is identified when the packet
                                           is ICMPoIPv6 packet, and the ICMP
                                           type is 135. */
    bcmRxTrapNdpMyIp = 285,             /* A packet is considered NdpMyIp when
                                           its Target-Address matches one of two
                                           configurable MyNDP IPv6 addresses. */
    bcmRxTrapEgTxLatency = 286,         /* Latency ETPP trap */
    bcmRxTrapEgTxMetering = 287,        /* Metering ETPP trap */
    bcmRxTrapEgTxGlem = 288,            /* GLEM error ETPP trap */
    bcmRxTrapEgTxOamUpMEPOamp = 289,    /* ETPP trap for OAM Up MEPs with
                                           destination OAMP */
    bcmRxTrapEgTxOamUpMEPDest1 = 290,   /* ETPP trap for OAM Up MEPs with
                                           configurable destination */
    bcmRxTrapEgTxOamUpMEPDest2 = 291,   /* ETPP trap for OAM Up MEPs with
                                           configurable destination */
    bcmRxTrapEgTxOamPassive = 292,      /* OAM passive error ETPP trap */
    bcmRxTrapEgTxOamLevel = 293,        /* OAM level error ETPP trap */
    bcmRxTrapEgRqpDiscard = 294,        /* RQP discard ERPP trap */
    bcmRxTrapEgTdmDiscard = 295,        /* TDM discard ERPP trap */
    bcmRxTrapEgExcludeSrc = 296,        /* Exclude source ERPP trap */
    bcmRxTrapEgGlemPpTrap = 297,        /* GLEM PP ERPP trap */
    bcmRxTrapEgGlemNonePpTrap = 298,    /* GLEM None PP ERPP trap */
    bcmRxTrapEgIpv4Error = 299,         /* IPV4 error ERPP trap */
    bcmRxTrapEgIpv6Error = 300,         /* IPV6 error ERPP trap */
    bcmRxTrapEgL4Error = 301,           /* Layer4 error ERPP trap */
    bcmRxTrapOamReflector = 302,        /* down MEP OAM reflector Trap */
    bcmRxTrapEgTxOamReflector = 303,    /* up MEP OAM reflector Trap */
    bcmRxTrapEgUserDefine = 304,        /* User defined ERPP Trap */
    bcmRxTrapEgTxUserDefine = 305,      /* User defined ETPP Trap */
    bcmRxTrapLinkLayerVlanTagDiscard = 306, /* Discarded packets according to their
                                           VLAN Tag configuration */
    bcmRxTrapTerminatedVlanTagDiscard = 307, /* Discarded packets according to their
                                           terminated VLAN Tag configuration */
    bcmRxTrapLinkLayerVlanTagAccept = 308, /* Accepted packets according to their
                                           VLAN Tag configuration */
    bcmRxTrapTerminatedVlanTagAccept = 309, /* Accepted packets according to their
                                           terminated VLAN Tag configuration */
    bcmRxTrapLinkLayerSaEqualsDa = 310, /* SA equals DA. */
    bcmRxTrapTerminatedSaEqualsDa = 311, /* SA equals DA. */
    bcmRxTrapLinkLayerSaMulticast = 312, /* SA is multicast. */
    bcmRxTrapTerminatedSaMulticast = 313, /* SA is multicast. */
    bcmRxTrapLinkLayerHeaderSizeErr = 314, /* Parser indicates header size error. */
    bcmRxTrapTerminatedHeaderSizeErr = 315, /* Parser indicates terminated header
                                           size error. */
    bcmRxTrapForwardingIpv4VersionError = 316, /* Version is different than 4. */
    bcmRxTrapTerminatedIpv4VersionError = 317, /* Terminated IPv4 Version is different
                                           than 4. */
    bcmRxTrapForwardingIpv4ChecksumError = 318, /* IHL is 5 and the checksum over the
                                           first 20 bytes doesn't verify. */
    bcmRxTrapTerminatedIpv4ChecksumError = 319, /* Terminated IPv4 IHL is 5 and the
                                           checksum over the first 20 bytes
                                           doesn't verify. */
    bcmRxTrapForwardingIpv4HeaderLengthError = 320, /* IHL (Internet Header Length) is less
                                           than 5. */
    bcmRxTrapTerminatedIpv4HeaderLengthError = 321, /* Terminated IPv4 IHL (Internet Header
                                           Length) is less than 5. */
    bcmRxTrapForwardingIpv4TotalLengthError = 322, /* Total length is less than 20. */
    bcmRxTrapTerminatedIpv4TotalLengthError = 323, /* Terminated IPv4 Total length is less
                                           than 20. */
    bcmRxTrapForwardingIpv4HasOptions = 324, /* IHL (Internet Header Length) is
                                           greater than 5. */
    bcmRxTrapTerminatedIpv4HasOptions = 325, /* Terminated IPv4 IHL (Internet Header
                                           Length) is greater than 5. */
    bcmRxTrapForwardingIpv4SipEqualDip = 326, /* Source-IP is equal to destination IP. */
    bcmRxTrapTerminatedIpv4SipEqualDip = 327, /* Terminated IPv4 Source-IP is equal to
                                           destination IP. */
    bcmRxTrapForwardingIpv4DipZero = 328, /* Destination IP is 0. */
    bcmRxTrapTerminatedIpv4DipZero = 329, /* Terminated IPv4 Destination IP is 0. */
    bcmRxTrapForwardingIpv4SipIsMc = 330, /* Source-IP is multicast. */
    bcmRxTrapTerminatedIpv4SipIsMc = 331, /* Terminated IPv4 Source-IP is
                                           multicast. */
    bcmRxTrapForwardingIpv4Ttl0 = 332,  /* Fwd IPv4 TTL is equal to 0. */
    bcmRxTrapTerminatedIpv4Ttl0 = 333,  /* Terminated IPv4 TTL is equal to 0. */
    bcmRxTrapForwardingIpv4Ttl1 = 334,  /* Fwd IPv4 TTL is equal 1. */
    bcmRxTrapTerminatedIpv4Ttl1 = 335,  /* Terminated IPv4 In-TTL is 0. */
    bcmRxTrapForwardingIpv6VersionError = 336, /* Version is different than 6. */
    bcmRxTrapTerminatedIpv6VersionError = 337, /* Terminated IPv6 Version is different
                                           than 6. */
    bcmRxTrapForwardingIpv6UnspecifiedDestination = 338, /* Forwarding header DIP = ::. */
    bcmRxTrapTerminatedIpv6UnspecifiedDestination = 339, /* Terminated IPv6 header DIP = ::. */
    bcmRxTrapForwardingIpv6LoopbackAddress = 340, /* DIP = ::1 or SIP = ::1. */
    bcmRxTrapTerminatedIpv6LoopbackAddress = 341, /* Terminated IPv6 DIP = ::1 or SIP =
                                           ::1. */
    bcmRxTrapForwardingIpv6MulticastSource = 342, /* The MSB of the SIP = 0xFF. */
    bcmRxTrapTerminatedIpv6MulticastSource = 343, /* Terminated IPv6 MSB of the SIP =
                                           0xFF. */
    bcmRxTrapForwardingIpv6NextHeaderNull = 344, /* Next-protocol is zero. */
    bcmRxTrapTerminatedIpv6NextHeaderNull = 345, /* Terminated IPv6 Next-protocol is
                                           zero. */
    bcmRxTrapForwardingIpv6UnspecifiedSource = 346, /* SIP = ::. */
    bcmRxTrapTerminatedIpv6UnspecifiedSource = 347, /* Terminated IPv6 SIP = ::. */
    bcmRxTrapForwardingIpv6LocalLinkDestination = 348, /* Bits 127:118 of the destination-IP
                                           are equal to 0x3FA. */
    bcmRxTrapTerminatedIpv6LocalLinkDestination = 349, /* Terminated IPv6 Bits 127:118 of the
                                           destination-IP are equal to 0x3FA. */
    bcmRxTrapForwardingIpv6LocalSiteDestination = 350, /* Bits 127:118 of the DIP = 0x3FB
                                           (deprecated). */
    bcmRxTrapTerminatedIpv6LocalSiteDestination = 351, /* Terminated IPv6 Bits 127:118 of the
                                           DIP = 0x3FB (deprecated). */
    bcmRxTrapForwardingIpv6LocalLinkSource = 352, /* Bits 127:118 of the SIP = 0x3FA. */
    bcmRxTrapTerminatedIpv6LocalLinkSource = 353, /* Terminated IPv6 Bits 127:118 of the
                                           SIP = 0x3FA. */
    bcmRxTrapForwardingIpv6LocalSiteSource = 354, /* Bits 127:118 of the SIP = 0x3FB. */
    bcmRxTrapTerminatedIpv6LocalSiteSource = 355, /* Terminated IPv6 Bits 127:118 of the
                                           SIP = 0x3FB. */
    bcmRxTrapForwardingIpv6Ipv4CompatibleDestination = 356, /* Bits 127:32 of the DIP = 0. */
    bcmRxTrapTerminatedIpv6Ipv4CompatibleDestination = 357, /* Terminated IPv6 Bits 127:32 of the
                                           DIP = 0. */
    bcmRxTrapForwardingIpv6Ipv4MappedDestination = 358, /* Bits 127:32 of the DIP are equal to
                                           0000_FFF_0000_0000_0000_0000. */
    bcmRxTrapTerminatedIpv6Ipv4MappedDestination = 359, /* Terminated IPv6 Bits 127:32 of the
                                           DIP are equal to
                                           0000_FFF_0000_0000_0000_0000. */
    bcmRxTrapForwardingIpv6MulticastDestination = 360, /* MSB of the DIP=0xFF. */
    bcmRxTrapTerminatedIpv6MulticastDestination = 361, /* Terminated IPv6 MSB of the DIP=0xFF. */
    bcmRxTrapOutlifOverflow = 362,      /* outlif array overflow. */
    bcmRxTrapTerminatedCoeFlowControl = 363, /* CoE Flow Control Packet. */
    bcmRxTrapTerminatedGenericCoeFlowControl = 364, /* CoE Generic Flow Control Packet. */
    bcmRxTrapTerminatedIpv4Fragmented = 365, /* Terminated IPv4 which is fragmented. */
    bcmRxTrapTerminatedMplsControlWordTrap = 366, /* Lookup key is found in ELK/LEM,
                                           P2P-Service If lookup result is set,
                                           lookup result determines that there's
                                           a control word, nibble after
                                           terminated MPLS stack equal '1'. */
    bcmRxTrapTerminatedMplsControlWordDrop = 367, /* Lookup key is found in ELK/LEM,
                                           P2P-Service If lookup result is set,
                                           lookup result determines that there's
                                           a control word, nibble after
                                           terminated MPLS stack does not equal
                                           '1' or '0'. */
    bcmRxTrapTerminatedVridMyMac = 368, /* VRID-My-Mac is invalid. */
    bcmRxTrapMplsPreprocessingBosOrTtl = 369, /* Error of BOS or TTL was idendefined
                                           in MPLS preprocessing. */
    bcmRxTrapUnknownDest = 370,         /* Unkown destination trap */
    bcmRxTrapDefault = 371,             /* Default trap. */
    bcmRxTrapBfdEchoOverIpv6 = 372,     /* BFDoIPv6 echo Trap. */
    bcmRxTrapEgressTrapped2ndPass = 373, /* Egress trapped packet on 2nd pass
                                           Trap. */
    bcmRxTrap1588User1 = 374,           /* 1588 protocol user trap #1. */
    bcmRxTrap1588User2 = 375,           /* 1588 protocol user trap #2. */
    bcmRxTrap1588User3 = 376,           /* 1588 protocol user trap #3. */
    bcmRxTrap1588User4 = 377,           /* 1588 protocol user trap #4. */
    bcmRxTrap1588User5 = 378,           /* 1588 protocol user trap #5. */
    bcmRxTrapEgTxVisibility = 379,      /* ETPP visibility trap. */
    bcmRxTrapEgBfdIpv6InvalidUdpChecksum = 380, /* BFD IPv6 trap for invalid UDP
                                           checksum. */
    bcmRxTrapOampPuntNextGoodPacket = 381, /* OAMP punt good packet trap. */
    bcmRxTrapEgTcpSnFlagsZero = 382,    /* ERPP L4 Sequence-Number and Flags (6)
                                           are both zero. */
    bcmRxTrapEgTcpSnZeroFlagsSet = 383, /* ERPP L4 Sequence-Number is zero and
                                           either Flags. FIN, Flags. URG or
                                           FLAGS. PSH are set. */
    bcmRxTrapEgTcpSynFin = 384,         /* ERPP Both Flags. SYN and Flags. FIN
                                           are set. */
    bcmRxTrapEgTcpEqualPorts = 385,     /* ERPP Source-Port equals
                                           Destination-Port. */
    bcmRxTrapEgTcpFragmentIncompleteHeader = 386, /* ERPP L3 is IPv4 and IP-Header.
                                           Fragmented and IP-Header.
                                           Fragment-Offset zero and
                                           (IPv4-Header. Total-Length - 4 *
                                           IPv4-Header. IHL) is less than 20B. */
    bcmRxTrapEgTcpFragmentOffsetLt8 = 387, /* ERPP L3 is IPv4 and IP-Header.
                                           Fragmented and IP-Header.
                                           Fragment-Offset is less than 8. */
    bcmRxTrapEgUdpEqualPorts = 388,     /* ERPP Source-Port equals
                                           Destination-Port. */
    bcmRxTrapEgIpv6VersionError = 389,  /* ERPP Version is different than 6.. */
    bcmRxTrapOamPerformanceEthAccelerated = 390, /* Down MEP trapping of LM/DM to OAMP */
    bcmRxTrapOamPerformanceY1731MplsTp = 391, /* MPLS-TP trapping of LM/DM to OAMP */
    bcmRxTrapOamPerformanceY1731Pwe = 392, /* PWE trapping of LM/DM to OAMP */
    bcmRxTrapTerminatedSaEqualsZero = 393, /* Termination SA equals Zero. */
    bcmRxTrapForwardingSaEqualsZero = 394, /* Forwarding SA equals Zero. */
    bcmRxTrapFwdDomainAssignmentModeTrap = 395, /* Forward Domain Assignment Mode trap. */
    bcmRxTrapOampMplsLmDmErr = 396,     /* Packet arrived to the OAMP with
                                           MplsLmDm. */
    bcmRxTrapForwardingIpv6Ttl0 = 397,  /* Fwd IPv6 TTL is equal to 0. */
    bcmRxTrapForwardingIpv6Ttl1 = 398,  /* Fwd IPv6 TTL is equal to 1. */
    bcmRxTrapEgTxIfaEgressMetadata = 399, /* ETPP trap for IFA Egress Node with
                                           metadata mirroring. */
    bcmRxTrapOampBfdProtection = 400,   /* OAMP protection packet. */
    bcmRxTrapOampRmepEccErr = 401,      /* Packet arrived to the OAMP hit a MEP
                                           DB or RMEP DB entry with ECC error */
    bcmRxTrapOampChecksumErr = 402,     /* Packet arrived to the OAMP failed
                                           checksum in validity checks */
    bcmRxTrapSrv6Usp = 403,             /* Identify SRv6 USP flow */
    bcmRxTrapOamPerformanceEthAcceleratedResponse = 404, /* Down MEP trapping of LMR/DMR to OAMP. */
    bcmRxTrapOamPerformanceY1731MplsTpAcceleratedResponse = 405, /* MPLS-TP, PWE trapping of LM/DM to
                                           OAMP. */
    bcmRxTrapOampErrorIndicationMiss = 406, /* OAM PDU Error Indication mismatch. */
    bcmRxTrapEgTxOamUpMEPOampPerformenceResponsePriority = 407, /* ETPP trap Up MEP trapping of LMR/DMR
                                           per priority to OAMP. */
    bcmRxTrapEgTxOamUpMEPOampPerformenceResponse = 408, /* ETPP trap Up MEP trapping of LMR/DMR
                                           to OAMP. */
    bcmRxTrapCount = 409                /* Must be last: enum count size. */
} bcm_rx_trap_t;

#define BCM_RX_TRAP_MAX_STAT_OBJ_ARR_LEN    10         

/* Forwarding header position overridden value */
typedef enum bcm_rx_trap_forwarding_header_e {
    bcmRxTrapForwardingHeaderPacketStart = 0, /* Start of packet. */
    bcmRxTrapForwardingHeaderL2Header = 1, /* Ethernet header. */
    bcmRxTrapForwardingHeaderFirstHeader = 2, /* First header after Ethernet. */
    bcmRxTrapForwardingHeaderSecondHeader = 3, /* Second header after Ethernet. */
    bcmRxTrapForwardingHeaderThirdHeader = 4, /* Third header after Ethernet. */
    bcmRxTrapForwardingHeaderFourthHeader = 5, /* Fourth header after Ethernet. */
    bcmRxTrapForwardingHeaderOamBfdPdu = 6, /* OAM or BFD PDU header. */
    bcmRxTrapForwardingHeaderCount = 7  /* Always Last. Not a usable value. */
} bcm_rx_trap_forwarding_header_t;

/* User-configurable, per-unit-core RX destination configuration. */
typedef struct bcm_rx_trap_core_config_s {
    bcm_gport_t dest_port;  /* Destination port */
    bcm_if_t encap_id;      /* Encap-ID */
    bcm_if_t encap_id2;     /* Encap-ID #2 */
} bcm_rx_trap_core_config_t;

/* User-configurable, statistical object overwrite configuration. */
typedef struct bcm_rx_trap_stat_obj_config_s {
    int counter_command_id;         /* Command id (interface id), 0-9 */
    uint32 stat_id;                 /* Object statistic id (the counter_pointer
                                       value as sent to the crps) */
    uint8 is_offset_by_qual_enable; /* StatObjValue is added a trap qualifier
                                       offset */
    int stat_object_type;           /* Statistic object type in range
                                       0-BCM_STAT_MAX_NUMBER_OF_OBJECT_TYPES-1 */
    uint8 is_meter;                 /* Allow metering */
    int stat_profile;               /* Statistic object profile */
} bcm_rx_trap_stat_obj_config_t;

/* User-configurable, per-unit RX configuration. */
typedef struct bcm_rx_trap_config_s {
    uint32 flags;                       /* BCM_RX_TRAP_XXX FLAGS. */
    bcm_gport_t dest_port;              /* Destination port. */
    bcm_multicast_t dest_group;         /* Destination group. */
    int prio;                           /* Internal priority of the packet. */
    bcm_color_t color;                  /* Color of the packet. */
    bcm_policer_t ether_policer_id;     /* Ethernet Policer. */
    bcm_policer_t policer_id;           /* general policer id. */
    int counter_num;                    /* counter. */
    int trap_strength;                  /* Strength of this trap, strongest trap
                                           in processing holds. */
    int snoop_cmnd;                     /* snoop command. */
    int snoop_strength;                 /* Strength of this trap, strongest
                                           snoop in processing holds. */
    bcm_forwarding_type_t forwarding_type; /* Forwarding type value */
    bcm_rx_trap_forwarding_header_t forwarding_header; /* Forwarding header position overridden
                                           value */
    bcm_if_t encap_id;                  /* Encap-ID */
    bcm_mirror_options_t *mirror_cmd;   /* Mirror options in ETPP traps */
    bcm_rx_trap_core_config_t *core_config_arr; /* Destinations information per core */
    int core_config_arr_len;            /* core_config_arr length */
    int qos_map_id;                     /* cos profile handle */
    int tunnel_termination_trap_strength; /* Strength of tunnel termination trap,
                                           strongest trap in processing holds. */
    int tunnel_termination_snoop_strength; /* Strength of tunnel termination trap,
                                           strongest snoop in processing holds. */
    int meter_cmd;                      /* meter command. */
    uint8 mapped_trap_strength;         /* mapped trap strength */
    uint8 is_recycle_high_priority;     /* recycle high priority indication */
    uint8 is_recycle_crop_pkt;          /* crop recycle packet indication */
    uint8 is_recycle_append_ftmh;       /* indication regarding appending the
                                           original FTMH to the recycle packet */
    bcm_gport_t cpu_trap_gport;         /* cpu trap gport */
    int stamped_trap_code;              /* trap code stamped on packet headers */
    bcm_if_t encap_id2;                 /* Encap-ID #2 */
    uint8 ecn_value;                    /* Ethernet encapsulation */
    uint16 vsq;                         /* Statistics VSQ pointer */
    uint8 latency_flow_id_clear;        /* Indication if to clear
                                           latency_flow_id */
    uint8 visibility_value;             /* Visibility value */
    uint32 stat_clear_bitmap;           /* Bitmap indicating which statistical
                                           objects are to clear */
    bcm_rx_trap_stat_obj_config_t stat_obj_config_arr[BCM_RX_TRAP_MAX_STAT_OBJ_ARR_LEN]; /* Overwrite configuration of
                                           statistical objects */
    uint32 stat_obj_config_len;         /* stat_obj_config_arr length */
    uint32 stat_metadata_mask;          /* Statistical metadata mask */
    int mirror_profile;                 /* mirror action profile */
    uint32 egress_forwarding_index;     /* Egress forwarding(parsing) index */
    int pp_drop_reason;                 /* Packet processing drop reason */
    uint32 flags2;                      /* BCM_RX_TRAP_FLAGS2_XXX FLAGS. */
    uint8 is_exem_learn;                /* indication if EXEM learning is needed
                                           or not */
    int fabric_header;                  /* system header profile value to
                                           override */
} bcm_rx_trap_config_t;

/* Initialize the rx_trap_config_t structure. */
extern void bcm_rx_trap_config_t_init(
    bcm_rx_trap_config_t *trap_config);

/* User-configurable, per-unit RX configuration. */
typedef struct bcm_rx_snoop_config_s {
    uint32 flags;               /* BCM_RX_SNOOP_XXX FLAGS. */
    bcm_gport_t dest_port;      /* Destination port. */
    bcm_multicast_t dest_group; /* Destination group. */
    int prio;                   /* Internal priority of the packet. */
    bcm_color_t color;          /* Color of the packet. */
    bcm_policer_t policer_id;   /* policer_id. */
    int counter_num;            /* counter. */
    int size;                   /* what portion of the packet to snoop to CPU,
                                   use -1 to indicate full packet snooping. */
    int probability;            /* snooping probability. Value represents
                                   percentage with percisionof a thousandth of a
                                   percent (100000 is 100.000%),  range 0 -
                                   100000. */
    bcm_if_t encap_id;          /* Encap-ID */
} bcm_rx_snoop_config_t;

/* Initialize the rx_snoop_config_t structure. */
extern void bcm_rx_snoop_config_t_init(
    bcm_rx_snoop_config_t *snoop_config);

#ifndef BCM_HIDE_DISPATCHABLE

/* rx_trap_type_create. */
extern int bcm_rx_trap_type_create(
    int unit, 
    int flags, 
    bcm_rx_trap_t type, 
    int *trap_id);

/* rx_trap_type_get. */
extern int bcm_rx_trap_type_get(
    int unit, 
    int flags, 
    bcm_rx_trap_t type, 
    int *trap_id);

/* Get RX trap type from trap ID */
extern int bcm_rx_trap_type_from_id_get(
    int unit, 
    int flags, 
    int trap_id, 
    bcm_rx_trap_t *trap_type);

/* rx_trap_type_destroy. */
extern int bcm_rx_trap_type_destroy(
    int unit, 
    int trap_id);

/* rx_trap_set. */
extern int bcm_rx_trap_set(
    int unit, 
    int trap_id, 
    bcm_rx_trap_config_t *config);

/* rx_trap_get. */
extern int bcm_rx_trap_get(
    int unit, 
    int trap_id, 
    bcm_rx_trap_config_t *config);

/* rx_snoop_set. */
extern int bcm_rx_snoop_set(
    int unit, 
    int snoop_cmnd, 
    bcm_rx_snoop_config_t *config);

/* rx_snoop_get. */
extern int bcm_rx_snoop_get(
    int unit, 
    int snoop_cmnd, 
    bcm_rx_snoop_config_t *config);

/* rx_snoop_create. */
extern int bcm_rx_snoop_create(
    int unit, 
    int flags, 
    int *snoop_cmnd);

/* rx_trap_type_destroy. */
extern int bcm_rx_snoop_destroy(
    int unit, 
    int flags, 
    int snoop_cmnd);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Flags for bcm_rx_trap_t. */
#define BCM_RX_TRAP_UPDATE_DEST             0x00000001 /* update destination. */
#define BCM_RX_TRAP_UPDATE_PRIO             0x00000002 /* update priority. */
#define BCM_RX_TRAP_UPDATE_COLOR            0x00000004 /* update color. */
#define BCM_RX_TRAP_UPDATE_POLICER          0x00000008 /* update policer id No.1 */
#define BCM_RX_TRAP_UPDATE_ETHERNET_POLICER 0x00000010 /* update Ethernet
                                                          policer. */
#define BCM_RX_TRAP_UPDATE_COUNTER          0x00000020 /* update counter. */
#define BCM_RX_TRAP_DEST_MULTICAST          0x00000040 /* destination is
                                                          multicast. */
#define BCM_RX_TRAP_TRAP                    0x00000080 /* if present packet is
                                                          trapped to CPU (with
                                                          trap information)
                                                          otherwise packet is
                                                          forwarded to
                                                          destination port/CPU. */
#define BCM_RX_TRAP_BYPASS_FILTERS          0x00000100 /* bypass filtering. */
#define BCM_RX_TRAP_LEARN_DISABLE           0x00000200 /* disable learning . */
#define BCM_RX_TRAP_WITH_ID                 0x00000400 /* Use the specified
                                                          trap/snoop id. */
#define BCM_RX_TRAP_REPLACE                 0x00000800 /* Replace config of
                                                          existing trap/snoop. */
#define BCM_RX_TRAP_POLICER_RESULT_INGRESS  0x00001000 /* User policer result on
                                                          ingress. */
#define BCM_RX_TRAP_POLICER_RESULT_EGRESS   0x00002000 /* User policer result on
                                                          egress. */
#define BCM_RX_TRAP_UPDATE_ADD_VLAN         0x00004000 /* Add VLAN to the final
                                                          destination value */
#define BCM_RX_TRAP_UPDATE_FORWARDING_TYPE  0x00008000 /* Replace the forwarding
                                                          type */
#define BCM_RX_TRAP_UPDATE_COUNTER_2        0x00010000 /* update counter No.2 */
#define BCM_RX_TRAP_UPDATE_FORWARDING_HEADER 0x00020000 /* Override the
                                                          Forwarding header */
#define BCM_RX_TRAP_UPDATE_ENCAP_ID         0x00040000 /* Update Encap-id */
#define BCM_RX_TRAP_DROP_AND_LEARN          0x00080000 /* Enable learning for
                                                          dropped packets */
#define BCM_RX_TRAP_UPDATE_POLICER_2        0x00100000 /* update policer id No.2 */
#define BCM_RX_TRAP_UPDATE_QOS_MAP_ID       0x00200000 /* update cos profile */
#define BCM_RX_TRAP_UPDATE_TUNNEL_TERMINATION_STRENGTH 0x00400000 /* update tunnel
                                                          termination trap/snoop
                                                          strengths */
#define BCM_RX_TRAP_UPDATE_METER_CMD        0x00800000 /* update meter command */
#define BCM_RX_TRAP_UPDATE_MAPPED_STRENGTH  0x01000000 /* update mapped strength */
#define BCM_RX_TRAP_UPDATE_ECN_VALUE        0x02000000 /* update ECN value */
#define BCM_RX_TRAP_UPDATE_VSQ              0x04000000 /* update VSQ */
#define BCM_RX_TRAP_UPDATE_VISIBILITY       0x08000000 /* update visibility */
#define BCM_RX_TRAP_UPDATE_EGRESS_FWD_INDEX 0x10000000 /* update egress
                                                          forwarding index */
#define BCM_RX_TRAP_COPY_DROP               0x20000000 /* Set drop to recycle
                                                          copy generation */

/* Flags for bcm_rx_snoop_t. */
#define BCM_RX_SNOOP_UPDATE_DEST            0x00000001 /* update destination. */
#define BCM_RX_SNOOP_UPDATE_PRIO            0x00000002 /* update priority. */
#define BCM_RX_SNOOP_UPDATE_COLOR           0x00000004 /* update color. */
#define BCM_RX_SNOOP_UPDATE_POLICER         0x00000008 /* update policer id. */
#define BCM_RX_SNOOP_UPDATE_ETHERNET_POLICER 0x00000010 /* update Ethernet
                                                          policer. */
#define BCM_RX_SNOOP_UPDATE_COUNTER         0x00000020 /* update counter. */
#define BCM_RX_SNOOP_DEST_MULTICAST         0x00000040 /* destination is
                                                          multicast. */
#define BCM_RX_SNOOP_WITH_ID                0x00000080 /* Use the specified
                                                          trap/snoop id. */
#define BCM_RX_SNOOP_REPLACE                0x00000100 /* Replace config of
                                                          existing trap/snoop. */
#define BCM_RX_SNOOP_POLICER_RESULT_INGRESS 0x00000200 /* User policer result on
                                                          ingress. */
#define BCM_RX_SNOOP_POLICER_RESULT_EGRESS  0x00000400 /* User policer result on
                                                          egress. */
#define BCM_RX_SNOOP_UPDATE_ENCAP_ID        0x00000800 /* Update Encap-id */
#define BCM_RX_SNOOP_UPDATE_COUNTER_1       0x00001000 /* update counter No.1 */
#define BCM_RX_SNOOP_UPDATE_COUNTER_2       0x00002000 /* update counter No.2 */

#ifndef BCM_HIDE_DISPATCHABLE

/* Set mode specific redirection reasons for rx packets. */
extern int bcm_rx_redirect_reasons_set(
    int unit, 
    bcm_rx_redirect_t mode, 
    bcm_rx_reasons_t reasons);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Options to configure copy to CPU properties */
#define BCM_RX_COPYTOCPU_WITH_ID    0x00000001 /* Option to replace an existing
                                                  entry */
#define BCM_RX_COPYTOCPU_REPLACE    0x00000002 /* Option to use an index that is
                                                  passed in */

/* Options for bcm_rx_mtu_set API */
#define BCM_RX_MTU_RIF          0x00000001 /* Set MTU filter for RIF, input is
                                              RIF */
#define BCM_RX_MTU_LIF          0x00000002 /* Set MTU filter for LIF, input is
                                              LIF */
#define BCM_RX_MTU_PORT         0x00000004 /* Set MTU filter for PORT, input is
                                              port */

/* Flags to configure copy to CPU properties */
#define BCM_RX_COPYTOCPU_TRUNCATE   0x00000001 /* If set, packets copied to CPU
                                                  will be truncated */

/* Buffer priority of copy to CPU packets */
#define BCM_RX_COPYTOCPU_BUFFER_PRIORITY_LOW 0x00000001 /* If set, a low buffer
                                                          priority will be used
                                                          for packets copied to
                                                          CPU */
#define BCM_RX_COPYTOCPU_BUFFER_PRIORITY_MEDIUM 0x00000002 /* If set, a medium
                                                          buffer priority will
                                                          be used for packets
                                                          copied to CPU */
#define BCM_RX_COPYTOCPU_BUFFER_PRIORITY_HIGH 0x00000004 /* If set, a high buffer
                                                          priority will be used
                                                          for packets copied to
                                                          CPU */

/* Copy to CPU attributes */
typedef struct bcm_rx_CopyToCpu_config_s {
    int flags;                          /* Flags to pass with configuration data */
    int index;                          /* Index of the entry */
    bcm_pkt_drop_reasons_t drop_reason_vector; /* Array of drop reasons */
    int strength;                       /* Strength of the entry */
    int buffer_priority;                /* Buffering priority of the redirected
                                           packet */
    int cpu_cosq;                       /* CPU CoS queue to use */
} bcm_rx_CopyToCpu_config_t;

/* Initialize a copy to CPU config structure */
extern void bcm_rx_CopyToCpu_config_t_init(
    bcm_rx_CopyToCpu_config_t *copyToCpu_config);

#ifndef BCM_HIDE_DISPATCHABLE

/* Add a copy to CPU entry criteria */
extern int bcm_rx_CopyToCpu_config_add(
    int unit, 
    uint32 options, 
    bcm_rx_CopyToCpu_config_t *copyToCpu_config);

/* Delete a copy to CPU entry */
extern int bcm_rx_CopyToCpu_config_delete(
    int unit, 
    int index);

/* Get a copy to CPU entry */
extern int bcm_rx_CopyToCpu_config_get(
    int unit, 
    int index, 
    bcm_rx_CopyToCpu_config_t *copyToCpu_config);

/* Get all copy to CPU entries */
extern int bcm_rx_CopyToCpu_config_get_all(
    int unit, 
    int entries_max, 
    bcm_rx_CopyToCpu_config_t *copyToCpu_config, 
    int *entries_count);

/* Delete all copy to CPU entries */
extern int bcm_rx_CopyToCpu_config_delete_all(
    int unit);

#endif /* BCM_HIDE_DISPATCHABLE */

/* User-configurable, key to configure MTU profile. */
typedef struct bcm_rx_mtu_profile_key_s {
    uint8 cmp_layer_type;   /* Compressed layer type - Only relevant for LIF/RIF */
    uint8 mtu_profile;      /* MTU profile to configure */
} bcm_rx_mtu_profile_key_t;

/* User-configurable, value to configure MTU profile. */
typedef struct bcm_rx_mtu_profile_value_s {
    uint32 mtu_val;         /* MTU value to configure */
    bcm_gport_t trap_gport; /* Trap GPORT (Action Profile, FWD and SNP Strength) */
} bcm_rx_mtu_profile_value_t;

#ifndef BCM_HIDE_DISPATCHABLE

/* 
 * Configure MTU profile indexed by mtu_key with values given in
 * mtu_value
 */
extern int bcm_rx_mtu_profile_set(
    int unit, 
    uint32 flags, 
    bcm_rx_mtu_profile_key_t *mtu_key, 
    bcm_rx_mtu_profile_value_t *mtu_value);

/* Retrieve values of MTU profile indexed by mtu_key */
extern int bcm_rx_mtu_profile_get(
    int unit, 
    uint32 flags, 
    bcm_rx_mtu_profile_key_t *mtu_key, 
    bcm_rx_mtu_profile_value_t *mtu_value);

#endif /* BCM_HIDE_DISPATCHABLE */

/* User-configurable, MTU value per LIF/RIF. */
typedef struct bcm_rx_mtu_config_s {
    uint32 flags;       /* BCM_RX_MTU_FLAG_XXX */
    bcm_if_t intf;      /* Interface  RIF */
    bcm_gport_t gport;  /* GPORT LIF */
    uint32 mtu;         /* MTU value to set for LIF/RIF */
    uint8 mtu_profile;  /* MTU profile to configure */
} bcm_rx_mtu_config_t;

#ifndef BCM_HIDE_DISPATCHABLE

/* maps the MTU value from input to LIF/RIF value from input */
extern int bcm_rx_mtu_set(
    int unit, 
    bcm_rx_mtu_config_t *config);

/* return MTU value that was set for LIF/RIF */
extern int bcm_rx_mtu_get(
    int unit, 
    bcm_rx_mtu_config_t *config);

/* Maps between SW trap id to HW trap id */
extern int bcm_rx_trap_sw_to_hw_id_map_get(
    int unit, 
    uint32 flags, 
    int sw_trap_id, 
    int *hw_trap_id);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Copy to CPU trace event reasons bitmap structure. */
typedef struct bcm_rx_pkt_trace_reasons_s {
    SHR_BITDCL rbits[_SHR_BITDCLSIZE(bcmPktTraceEventCount)]; 
} bcm_rx_pkt_trace_reasons_t;

/* 
 * Macro to check if a reason (bcmPktTraceEvent*) is included in a set of
 * reasons (bcm_rx_pkt_trace_reasons_t).
 * 
 * Returns:
 *   zero     => reason is not included in the set
 *   non-zero => reason is included in the set
 */
#define BCM_RX_PKT_TRACE_REASON_GET(_trace_reasons, _trace_reason)  \
   SHR_BITGET(((_trace_reasons).rbits), (_trace_reason)) 

/* 
 * Macro to add a reason (bcmPktTraceEvent*) to a set of reasons
 * (bcm_rx_pkt_trace_reasons_t).
 */
#define BCM_RX_PKT_TRACE_REASON_SET(_trace_reasons, _trace_reason)  \
   SHR_BITSET(((_trace_reasons).rbits), (_trace_reason)) 

/* 
 * Macro to add all reasons (bcmPktTraceEvent*) to a set of reasons
 * (bcm_rx_pkt_trace_reasons_t).
 */
#define BCM_RX_PKT_TRACE_REASON_SET_ALL(_trace_reasons)  \
   SHR_BITSET_RANGE(((_trace_reasons).rbits), 0, bcmPktTraceEventCount) 

/* 
 * Macro to clear a reason (bcmPktTraceEvent*) from a set of reasons
 * (bcm_rx_pkt_trace_reasons_t).
 */
#define BCM_RX_PKT_TRACE_REASON_CLEAR(_trace_reasons, _trace_reason)  \
   SHR_BITCLR(((_trace_reasons).rbits), (_trace_reason)) 

/* Macro to clear a set of reasons (bcm_rx_pkt_trace_reasons_t). */
#define BCM_RX_PKT_TRACE_REASON_CLEAR_ALL(_trace_reasons)  \
   SHR_BITCLR_RANGE(((_trace_reasons).rbits), 0, bcmPktTraceEventCount) 

/* 
 * Macro to check if a set of reasons (bcm_rx_pkt_trace_reasons_t) is
 * empty.
 */
#define BCM_RX_PKT_TRACE_REASON_IS_NULL(_trace_reasons)  \
   SHR_BITNULL_RANGE(((_trace_reasons).rbits), 0, bcmPktTraceEventCount) 

/* Macro to itterate over a set of reasons (bcm_rx_pkt_trace_reasons_t). */
#define BCM_RX_PKT_TRACE_REASON_ITER(_trace_reasons, _trace_reason)  \
   for(_trace_reason = bcmPktTraceEventIngressCmlFlags; _trace_reason < (int)bcmPktTraceEventCount; _trace_reason++) if(SHR_BITGET(((_trace_reasons).rbits), (_trace_reason))) 

/* 
 * Macro to count number of active reasons in a set of reasons
 * (bcm_rx_pkt_trace_reasons_t).
 */
#define BCM_RX_PKT_TRACE_REASON_COUNT(_trace_reasons, count)  \
                SHR_BITCOUNT_RANGE(((_trace_reasons).rbits), count, 0, bcmPktTraceEventCount)
 

/* Macro to compare two sets of reasons (bcm_rx_pkt_trace_reasons_t). */
#define BCM_RX_PKT_TRACE_REASON_EQ(_trace_reasons1, _trace_reasons2)  \
   SHR_BITEQ_RANGE(((_trace_reasons1).rbits), ((_trace_reasons2).rbits), 0, bcmPktTraceEventCount)
 

/* 
 * Macro to negative compare two sets of reasons
 * (bcm_rx_pkt_trace_reasons_t).
 */
#define BCM_RX_PKT_TRACE_REASON_NEQ(_trace_reasons1, _trace_reasons2)  \
                (!SHR_BITEQ_RANGE(((_trace_reasons1).rbits), ((_trace_reasons2).rbits), 0, bcmPktTraceEventCount))
 

/* 
 * Macro to perform logical AND operation on two sets of reasons
 * (bcm_rx_pkt_trace_reasons_t).
 */
#define BCM_RX_PKT_TRACE_REASON_AND(_trace_reasons1, _trace_reasons2)  \
                SHR_BITAND_RANGE(((_trace_reasons1).rbits), ((_trace_reasons2).rbits), 0, bcmPktTraceEventCount, ((_trace_reasons1).rbits))
 

/* 
 * Macro to perform logical OR operation on two sets of reasons
 * (bcm_rx_pkt_trace_reasons_t).
 */
#define BCM_RX_PKT_TRACE_REASON_OR(_trace_reasons1, _trace_reasons2)  \
                SHR_BITOR_RANGE(((_trace_reasons1).rbits), ((_trace_reasons2).rbits), 0, bcmPktTraceEventCount, ((_trace_reasons1).rbits))
 

/* 
 * Macro to remove set of reasons2 (bcm_rx_pkt_trace_reasons_t) from set
 * of reasons1 (bcm_rx_pkt_trace_reasons_t).
 */
#define BCM_RX_PKT_TRACE_REASON_REMOVE(_trace_reasons1, _trace_reasons2)  \
   SHR_BITREMOVE_RANGE(((_trace_reasons1).rbits), ((_trace_reasons2).rbits), 0, bcmPktTraceEventCount, ((_trace_reasons1).rbits)); 

/* Macro to negate two sets of reasons (bcm_rx_pkt_trace_reasons_t). */
#define BCM_RX_PKT_TRACE_REASON_NEGATE(_trace_reasons1, _trace_reasons2)  \
                SHR_BITNEGATE_RANGE(((_trace_reasons2).rbits), 0, bcmPktTraceEventCount, ((_trace_reasons1).rbits));
 

/* Options for RX cosq mapping API. */
#define BCM_RX_COSQ_MAPPING_OPTIONS_REPLACE 0x00000001 /* Replace a CPU COS map. */

/* Flags for RX COSQ mapping */
#define BCM_RX_COSQ_MAPPING_COPYTOCPU_TRUNCATE 0x00000001 /* If set, packets copied
                                                          to CPU will be
                                                          truncated. */

/* Rx cosq mapping. */
typedef struct bcm_rx_cosq_mapping_s {
    uint32 flags;                       /* flags */
    int index;                          /* Index into COSQ mapping table (0 is
                                           highest match priority) */
    bcm_rx_reasons_t reasons;           /* packet reasons bitmap */
    bcm_rx_reasons_t reasons_mask;      /* mask for packet reasons bitmap */
    uint8 int_prio;                     /* internal priority value */
    uint8 int_prio_mask;                /* mask for internal priority value */
    uint32 packet_type;                 /* packet type bitmap */
    uint32 packet_type_mask;            /* mask for packet type bitmap */
    bcm_cos_queue_t cosq;               /* cosq value */
    uint32 flex_key1;                   /* Flex key 1. */
    uint32 flex_key1_mask;              /* Mask for flex key 1. */
    uint32 flex_key2;                   /* Flex key 2. */
    uint32 flex_key2_mask;              /* Mask for flex key 2. */
    bcm_rx_pkt_trace_reasons_t trace_reasons; /* Copy to CPU trace event reasons
                                           bitmap. */
    bcm_rx_pkt_trace_reasons_t trace_reasons_mask; /* Mask for copy to CPU trace event
                                           reasons bitmap. */
    bcm_pkt_drop_event_t drop_event;    /* Drop event. */
    bcm_pkt_drop_event_t drop_event_mask; /* Mask for drop event. */
    int priority;                       /* Entry priority. */
} bcm_rx_cosq_mapping_t;

/* Initialize a BCM RX cosq mapping structure. */
extern void bcm_rx_cosq_mapping_t_init(
    bcm_rx_cosq_mapping_t *rx_cosq_mapping);

#ifndef BCM_HIDE_DISPATCHABLE

/* Map packets to a CPU COS queue. */
extern int bcm_rx_cosq_mapping_extended_set(
    int unit, 
    uint32 options, 
    bcm_rx_cosq_mapping_t *rx_cosq_mapping);

/* Get packets to CPU COS queue mappings. */
extern int bcm_rx_cosq_mapping_extended_get(
    int unit, 
    bcm_rx_cosq_mapping_t *rx_cosq_mapping);

/* Add a CPU COS map. */
extern int bcm_rx_cosq_mapping_extended_add(
    int unit, 
    uint32 options, 
    bcm_rx_cosq_mapping_t *rx_cosq_mapping);

/* Delete a CPU COS map. */
extern int bcm_rx_cosq_mapping_extended_delete(
    int unit, 
    bcm_rx_cosq_mapping_t *rx_cosq_mapping);

/* Delete all CPU COS maps. */
extern int bcm_rx_cosq_mapping_extended_delete_all(
    int unit);

#endif /* BCM_HIDE_DISPATCHABLE */

/* User-configurable, protocol trap key parameters. */
typedef struct bcm_rx_trap_protocol_key_s {
    bcm_rx_trap_t protocol_type;    /* one of L2CP/ICMP/IGMP/Non-Authorized
                                       802.1x/DHCP/ARP/NDP. */
    uint8 protocol_trap_profile;    /* protocol trap handling profile,
                                       values:0-3. */
    uint32 trap_args;               /* argument according to protocol_type. */
} bcm_rx_trap_protocol_key_t;

/* User-configurable, trap profile of each protocol. */
typedef struct bcm_rx_trap_protocol_profiles_s {
    uint8 icmpv6_trap_profile;          /* ICMP IPv6 trap profile, also used for
                                           NDP trap profile. */
    uint8 icmpv4_trap_profile;          /* ICMP IPv4 trap profile. */
    uint8 l2cp_trap_profile;            /* L2CP trap profile. */
    uint8 arp_trap_profile;             /* ARP trap profile. */
    uint8 igmp_trap_profile;            /* IGMP trap profile. */
    uint8 dhcp_trap_profile;            /* DHCP trap profile. */
    uint8 non_auth_8021x_trap_profile;  /* non authorized 802.1x trap profile,
                                           MSB - collision bit, LSB - profile
                                           bit. */
} bcm_rx_trap_protocol_profiles_t;

#ifndef BCM_HIDE_DISPATCHABLE

/* rx_trap_protocol_set. */
extern int bcm_rx_trap_protocol_set(
    int unit, 
    bcm_rx_trap_protocol_key_t *key_p, 
    bcm_gport_t trap_gport);

/* rx_trap_protocol_get. */
extern int bcm_rx_trap_protocol_get(
    int unit, 
    bcm_rx_trap_protocol_key_t *key_p, 
    bcm_gport_t *trap_gport_p);

/* rx_trap_protocol_clear. */
extern int bcm_rx_trap_protocol_clear(
    int unit, 
    bcm_rx_trap_protocol_key_t *key_p);

/* rx_trap_protocol_profiles_set. */
extern int bcm_rx_trap_protocol_profiles_set(
    int unit, 
    bcm_gport_t port, 
    bcm_rx_trap_protocol_profiles_t *protocol_profiles_p);

/* rx_trap_protocol_profiles_get. */
extern int bcm_rx_trap_protocol_profiles_get(
    int unit, 
    bcm_gport_t port, 
    bcm_rx_trap_protocol_profiles_t *protocol_profiles_p);

/* rx_trap_action_profile_set. */
extern int bcm_rx_trap_action_profile_set(
    int unit, 
    uint32 flags, 
    bcm_rx_trap_t trap_type, 
    bcm_gport_t gport);

/* rx_trap_action_profile_get. */
extern int bcm_rx_trap_action_profile_get(
    int unit, 
    bcm_rx_trap_t trap_type, 
    bcm_gport_t *gport);

/* rx_trap_action_profile_clear. */
extern int bcm_rx_trap_action_profile_clear(
    int unit, 
    bcm_rx_trap_t trap_type);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Rx Program Enable Types */
typedef enum bcm_rx_trap_prog_enable_e {
    bcmRxTrapProgDisable = 0, 
    bcmRxTrapProgEnableMatch = 1, 
    bcmRxTrapProgEnableMismatch = 2 
} bcm_rx_trap_prog_enable_t;

/* Programmable trap structure. */
typedef struct bcm_rx_trap_prog_config_s {
    bcm_rx_trap_prog_enable_t src_mac_enable; 
    bcm_mac_t src_mac; 
    uint8 src_mac_nof_bits; 
    bcm_rx_trap_prog_enable_t dest_mac_enable; 
    bcm_mac_t dest_mac; 
    uint8 dest_mac_nof_bits; 
    bcm_rx_trap_prog_enable_t ether_type_enable; 
    uint16 ether_type; 
    bcm_rx_trap_prog_enable_t sub_type_enable; 
    uint8 sub_type; 
    uint8 sub_type_mask; 
    bcm_rx_trap_prog_enable_t ip_protocol_enable; 
    uint8 ip_protocol; 
    bcm_rx_trap_prog_enable_t l4_ports_enable; 
    bcm_port_t src_port; 
    uint16 src_port_mask; 
    bcm_port_t dest_port; 
    uint16 dest_port_mask; 
    bcm_rx_trap_prog_enable_t tcp_flags_enable; 
    uint16 tcp_flags; 
    uint16 tcp_flags_mask; 
    bcm_rx_trap_prog_enable_t tcp_seq_is_zero_enable; 
    bcm_gport_t trap_gport; 
} bcm_rx_trap_prog_config_t;

/* Initialize programmable trap configuration. */
extern void bcm_rx_trap_prog_config_t_init(
    bcm_rx_trap_prog_config_t *prog_config_p);

#ifndef BCM_HIDE_DISPATCHABLE

/* Set programmable trap configuration. */
extern int bcm_rx_trap_prog_set(
    int unit, 
    uint32 flags, 
    uint8 prog_index, 
    bcm_rx_trap_prog_config_t *prog_config_p);

/* Get programmable trap configuration. */
extern int bcm_rx_trap_prog_get(
    int unit, 
    uint8 prog_index, 
    bcm_rx_trap_prog_config_t *prog_config_p);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Initialize the MTU profile key struct to init values. */
extern void bcm_rx_mtu_profile_key_t_init(
    bcm_rx_mtu_profile_key_t *mtu_key);

/* Initialize the MTU profile value struct to init values. */
extern void bcm_rx_mtu_profile_value_t_init(
    bcm_rx_mtu_profile_value_t *mtu_value);

/* Initialize the MTU struct to init values. */
extern void bcm_rx_mtu_config_t_init(
    bcm_rx_mtu_config_t *mtu_config);

/* LIF types for trap configuration */
typedef enum bcm_rx_trap_lif_type_e {
    bcmRxTrapLifTypeInLif = 0, 
    bcmRxTrapLifTypeInRif = 1, 
    bcmRxTrapLifTypeOutLif = 2, 
    bcmRxTrapLifTypeOutRif = 3, 
    bcmRxTrapLifTypeCount = 4 
} bcm_rx_trap_lif_type_t;

/* LIf traps configuration structure. */
typedef struct bcm_rx_trap_lif_config_s {
    bcm_rx_trap_lif_type_t lif_type; 
    bcm_if_t rif_intf;                  /* Interface  RIF */
    bcm_gport_t lif_gport;              /* GPORT LIF */
    bcm_gport_t action_gport;           /* hold theTrap-Action-Profile or
                                           mirror_cmd(only for egress) to
                                           configure */
} bcm_rx_trap_lif_config_t;

/* Initialize LIF trap configuration. */
extern void bcm_rx_trap_lif_config_t_init(
    bcm_rx_trap_lif_config_t *lif_config_p);

#ifndef BCM_HIDE_DISPATCHABLE

/* Set LIF trap configuration. */
extern int bcm_rx_trap_lif_set(
    int unit, 
    uint32 flags, 
    bcm_rx_trap_lif_config_t *lif_config_p);

/* Get LIF trap configuration. */
extern int bcm_rx_trap_lif_get(
    int unit, 
    bcm_rx_trap_lif_config_t *lif_config_p);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Initialize the protocol trap key struct to init values. */
extern void bcm_rx_trap_protocol_key_t_init(
    bcm_rx_trap_protocol_key_t *key_p);

/* Initialize the protocol trap profiles struct to init values. */
extern void bcm_rx_trap_protocol_profiles_t_init(
    bcm_rx_trap_protocol_profiles_t *protocol_profiles_p);

/* SVTag configuration Key structure. */
typedef struct bcm_rx_trap_svtag_key_s {
    uint32 flags;                   /* BCM_RX_TRAP_SVTAG_XXX */
    bcm_svtag_pkt_type_t pkt_type; 
    uint8 sci_profile;              /* Secure Context Index Profile */
    uint8 error_code_profile;       /* Error Code profile */
} bcm_rx_trap_svtag_key_t;

/* Initialize the SV tag key struct with default values. */
extern void bcm_rx_trap_svtag_key_t_init(
    bcm_rx_trap_svtag_key_t *svtag_trap_key);

#ifndef BCM_HIDE_DISPATCHABLE

/* Set the SVTag trap Action Profile configuration per SVTAG. */
extern int bcm_rx_trap_svtag_set(
    int unit, 
    bcm_rx_trap_svtag_key_t *svtag_trap_key, 
    bcm_gport_t action_gport);

/* Get the SVTag trap Action Profile configuration per SVTAG. */
extern int bcm_rx_trap_svtag_get(
    int unit, 
    bcm_rx_trap_svtag_key_t *svtag_trap_key, 
    bcm_gport_t *action_gport);

#endif /* BCM_HIDE_DISPATCHABLE */

#define BCM_RX_TRAP_SVTAG_IPSEC 0x1        

/* Flags2 for bcm_rx_trap_t. */
#define BCM_RX_TRAP_FLAGS2_SNOOP_CODE_CLEAR 0x00000001 /* Sets 1b field in the
                                                          trap action table to
                                                          clear the Snoop Code. */
#define BCM_RX_TRAP_FLAGS2_MIRROR_CODE_CLEAR 0x00000002 /* Sets 1b field in the
                                                          trap action table to
                                                          clear the Mirror Code. */
#define BCM_RX_TRAP_FLAGS2_STAT_SAMPLING_CODE_CLEAR 0x00000004 /* Sets 1b field in the
                                                          trap action table to
                                                          clear the Statistical
                                                          Sampling Code. */
#define BCM_RX_TRAP_FLAGS2_KEEP_FABRIC_HEADER 0x00000008 /* Enables the trap to
                                                          keep the original
                                                          headers of the packet. */
#define BCM_RX_TRAP_FLAGS2_UPDATE_ACL_PROFILE 0x00000010 /* Enables the trap to
                                                          update the ACL
                                                          profile. */
#define BCM_RX_TRAP_FLAGS2_INT_STAT_DISABLE 0x00000020 /* Disable internal
                                                          statistics. */
#define BCM_RX_TRAP_FLAGS2_FABRIC_HEADER_SET 0x00000040 /* Indication to override
                                                          system header profile
                                                          value. */
#define BCM_RX_TRAP_FLAGS2_UPDATE_EXEM_LEARN 0x00000080 /* Indication to override
                                                          is exem learn value. */
#define BCM_RX_TRAP_FLAGS2_REPLICATION_FAILOVER_DISABLE 0x00000100 /* Disable replication
                                                          failover. */
#define BCM_RX_TRAP_FLAGS2_FALLBACK_TO_BRIDGE_ENABLE 0x00000200 /* Enable fallback to
                                                          bridge. */
#define BCM_RX_TRAP_FLAGS2_NETWORK_GROUP_ENABLE 0x00000400 /* Enable network group
                                                          filter. */
#define BCM_RX_TRAP_FLAGS2_SAME_INTERFACE_ENABLE 0x00000800 /* Enable same interface
                                                          filter. */
#define BCM_RX_TRAP_FLAGS2_UPDATE_TRUNK_MEMBERS_LOCAL_ONLY 0x0001000  /* Indicates that the LAG
                                                          member is local. */
#define BCM_RX_TRAP_FLAGS2_START_PACKET_STRIP_CLEAR 0x00002000 /* Indication to set
                                                          bytes to strip to 0. */

#ifndef BCM_HIDE_DISPATCHABLE

/* rx_trap_protocol_interface_profiles_set. */
extern int bcm_rx_trap_protocol_interface_profiles_set(
    int unit, 
    bcm_if_t intf, 
    bcm_rx_trap_protocol_profiles_t *protocol_profiles_p);

/* rx_trap_protocol_interface_profiles_get. */
extern int bcm_rx_trap_protocol_interface_profiles_get(
    int unit, 
    bcm_if_t intf, 
    bcm_rx_trap_protocol_profiles_t *protocol_profiles_p);

#endif /* BCM_HIDE_DISPATCHABLE */

#endif /* __BCM_RX_H__ */

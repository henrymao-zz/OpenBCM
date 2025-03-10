/*
 * 
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 */

#ifndef __BCM_VXLAN_H__
#define __BCM_VXLAN_H__

#if defined(INCLUDE_L3)

#include <bcm/types.h>
#include <bcm/l3.h>
#include <bcm/tunnel.h>
#include <bcm/vlan.h>

#if defined(INCLUDE_L3)
/* BCM_VXLAN_VPN_* flags for VXLAN VPN Create. */
#define BCM_VXLAN_VPN_ELINE                 0x00000001 
#define BCM_VXLAN_VPN_ELAN                  0x00000002 
#define BCM_VXLAN_VPN_WITH_ID               0x00000004 
#define BCM_VXLAN_VPN_WITH_VPNID            0x00000008 
#define BCM_VXLAN_VPN_SERVICE_TAGGED        0x00000010 
#define BCM_VXLAN_VPN_SERVICE_VLAN_ADD      0x00000020 
#define BCM_VXLAN_VPN_SERVICE_VLAN_REPLACE  0x00000040 
#define BCM_VXLAN_VPN_SERVICE_VLAN_DELETE   0x00000080 
#define BCM_VXLAN_VPN_SERVICE_VLAN_TPID_REPLACE 0x00000100 
#define BCM_VXLAN_VPN_SERVICE_VLAN_PRI_TPID_REPLACE 0x00000200 
#define BCM_VXLAN_VPN_SERVICE_VLAN_PRI_REPLACE 0x00000400 
#define BCM_VXLAN_VPN_SERVICE_PRI_REPLACE   0x00000800 
#define BCM_VXLAN_VPN_SERVICE_TPID_REPLACE  0x00001000 
#define BCM_VXLAN_VPN_REPLACE               0x00002000 
#define BCM_VXLAN_VPN_UNKNOWN_UCAST_REPLACE 0x00004000 
#define BCM_VXLAN_VPN_UNKNOWN_MCAST_REPLACE 0x00008000 
#define BCM_VXLAN_VPN_BCAST_REPLACE         0x00010000 
#define BCM_VXLAN_VPN_TUNNEL_BASED_VNID     0x00020000 
#endif

#if defined(INCLUDE_L3)
/* BCM_VXLAN_MULTICAST_TUNNEL_STATE_BUD_* flags. */
#define BCM_VXLAN_MULTICAST_TUNNEL_STATE_BUD_ENABLE 0x00000001 
#define BCM_VXLAN_MULTICAST_TUNNEL_STATE_BUD_DISABLE 0x00000002 
#endif

#if defined(INCLUDE_L3)
/* VXLAN VPN Definitions. */
#define BCM_VXLAN_VPN_INVALID   0xFFFF     /* Invalid VXLAN VPN */
#endif

#if defined(INCLUDE_L3)
/* VXLAN VPN Config Structure. */
typedef struct bcm_vxlan_vpn_config_s {
    uint32 flags;                       /* BCM_VXLAN_VPN_xxx. */
    bcm_vpn_t vpn;                      /* VXLAN VPN */
    uint32 vnid;                        /* VNID */
    uint8 pkt_pri;                      /* Packet Priority */
    uint8 pkt_cfi;                      /* Packet CFI */
    uint16 egress_service_tpid;         /* Service TPID */
    bcm_vlan_t egress_service_vlan;     /* Service VLAN */
    bcm_multicast_t broadcast_group; 
    bcm_multicast_t unknown_unicast_group; 
    bcm_multicast_t unknown_multicast_group; 
    bcm_vlan_protocol_packet_ctrl_t protocol_pkt; 
    bcm_vlan_t vlan;                    /* Outer VLAN */
    bcm_gport_t match_port_class;       /* local port vlan domain */
    bcm_vlan_t default_vlan;            /* default vlan for untag payload */
} bcm_vxlan_vpn_config_t;
#endif

#if defined(INCLUDE_L3)
/* Initialize VXLAN VPN config structure. */
extern void bcm_vxlan_vpn_config_t_init(
    bcm_vxlan_vpn_config_t *info);
#endif

#ifndef BCM_HIDE_DISPATCHABLE

#if defined(INCLUDE_L3)
/* 
 * Create or update VXLAN VPN.
 *  When create a VXLAN VPN:
 * If use BCM_VXLAN_VPN_WITH_VPNID, both VFI and VNID will be created.
 * If not use flag BCM_VXLAN_VPN_WITH_VPNID, only VFI will be created.
 *  When update an exist VXLAN VPN(BCM_VXLAN_VPN_REPLACE should be used):
 * If use both BCM_VXLAN_VPN_REPLACE and BCM_VXLAN_VPN_WITH_VPNID, both
 * VFI and VNID will be created.
 * If only use BCM_VXLAN_VPN_REPLACE, the VNID will be removed.
 * If the flex counter is attached to the VPN, the previous flex counter
 * information can be kept.
 */
extern int bcm_vxlan_vpn_create(
    int unit, 
    bcm_vxlan_vpn_config_t *info);
#endif

#if defined(INCLUDE_L3)
/* Destroy VXLAN VPN. */
extern int bcm_vxlan_vpn_destroy(
    int unit, 
    bcm_vpn_t l2vpn);
#endif

#if defined(INCLUDE_L3)
/* Destroy VXLAN VPN. */
extern int bcm_vxlan_vpn_destroy_all(
    int unit);
#endif

#if defined(INCLUDE_L3)
/* Get VXLAN VPN. */
extern int bcm_vxlan_vpn_get(
    int unit, 
    bcm_vpn_t l2vpn, 
    bcm_vxlan_vpn_config_t *info);
#endif

#endif /* BCM_HIDE_DISPATCHABLE */

/* VXLAN vpn callback function prototype */
#if defined(INCLUDE_L3)
typedef int(*bcm_vxlan_vpn_traverse_cb)(
    int unit, 
    bcm_vxlan_vpn_config_t *info, 
    void *user_data);
#endif

#ifndef BCM_HIDE_DISPATCHABLE

#if defined(INCLUDE_L3)
/* 
 * Traverse all valid VXLAN VPN entries and call the supplied callback
 * routine.
 */
extern int bcm_vxlan_vpn_traverse(
    int unit, 
    bcm_vxlan_vpn_traverse_cb cb, 
    void *user_data);
#endif

#endif /* BCM_HIDE_DISPATCHABLE */

#if defined(INCLUDE_L3)
/* VXLAN port match criteria. */
typedef enum bcm_vxlan_port_match_e {
    BCM_VXLAN_PORT_MATCH_INVALID = 0,   /* Illegal. */
    BCM_VXLAN_PORT_MATCH_NONE = 1,      /* No source match criteria. */
    BCM_VXLAN_PORT_MATCH_PORT = 2,      /* {Module, Port} or Trunk. */
    BCM_VXLAN_PORT_MATCH_PORT_VLAN = 3, /* Mod/port/trunk + outer VLAN. */
    BCM_VXLAN_PORT_MATCH_PORT_INNER_VLAN = 4, /* Mod/port/trunk + inner VLAN. */
    BCM_VXLAN_PORT_MATCH_PORT_VLAN_STACKED = 5, /* Mod/port/trunk + outer/inner VLAN. */
    BCM_VXLAN_PORT_MATCH_VLAN_PRI = 6,  /* Mod/port/trunk + VLAN-PRI + VLAN-CFI. */
    BCM_VXLAN_PORT_MATCH_VN_ID = 7,     /* Match VXLAN VN_ID */
    BCM_VXLAN_PORT_MATCH_SHARE = 8,     /* Shared logical port */
    BCM_VXLAN_PORT_MATCH_PORT_ITAG = 9, /* Mod/port/trunk + inner vlan tag. */
    BCM_VXLAN_PORT_MATCH_PORT_ETAG_VLAN = 10, /* Mod/port/trunk + ETAG VLAN ID + outer
                                           VLAN ID */
    BCM_VXLAN_PORT_MATCH_COUNT = 11     /* Must be last. */
} bcm_vxlan_port_match_t;
#endif

#if defined(INCLUDE_L3)
/* BCM_VXLAN_* flags. */
#define BCM_VXLAN_PORT_WITH_ID              (1U << 0)  /* create VXLAN port with
                                                          specified ID */
#define BCM_VXLAN_PORT_DROP                 (1U << 1)  /* Drop matching packets */
#define BCM_VXLAN_PORT_NETWORK              (1U << 2)  /* Network facing
                                                          interface */
#define BCM_VXLAN_PORT_COUNTED              (1U << 3)  /* Maintain packet/byte
                                                          counts */
#define BCM_VXLAN_PORT_REPLACE              (1U << 4)  /* Replace existing entry */
#define BCM_VXLAN_PORT_INT_PRI_SET          (1U << 5)  /* Use Specified pri for
                                                          internal priority */
#define BCM_VXLAN_PORT_INT_PRI_MAP          (1U << 6)  /* Use specified exp_map
                                                          for internal priority */
#define BCM_VXLAN_PORT_EGRESS_TUNNEL        (1U << 7)  /* Specified Egress
                                                          tunnel is valid */
#define BCM_VXLAN_PORT_SERVICE_TAGGED       (1U << 8)  /* Service tag mode */
#define BCM_VXLAN_PORT_SERVICE_VLAN_ADD     (1U << 9)  /* Add SD-tag */
#define BCM_VXLAN_PORT_SERVICE_VLAN_REPLACE (1U << 10) /* Replace VLAN not TPID */
#define BCM_VXLAN_PORT_SERVICE_VLAN_DELETE  (1U << 11) /* Delete VLAN Tag */
#define BCM_VXLAN_PORT_SERVICE_VLAN_TPID_REPLACE (1U << 12) /* Replace VLAN and TPID */
#define BCM_VXLAN_PORT_SERVICE_VLAN_PRI_TPID_REPLACE (1U << 13) /* Replace VLAN, VLAN-PRI
                                                          and TPID */
#define BCM_VXLAN_PORT_SERVICE_VLAN_PRI_REPLACE (1U << 14) /* Replace VLAN and
                                                          VLAN-PRI */
#define BCM_VXLAN_PORT_SERVICE_PRI_REPLACE  (1U << 15) /* Replace VLAN-PRI only */
#define BCM_VXLAN_PORT_SERVICE_TPID_REPLACE (1U << 16) /* Replace TPID only */
#define BCM_VXLAN_PORT_EGRESS_OBJECT        (1U << 17) /* Specified Egress
                                                          interface is valid */
#define BCM_VXLAN_PORT_MULTICAST            (1U << 19) /* Create Multicast-only
                                                          VXLAN Tunnel */
#define BCM_VXLAN_PORT_DEFAULT              (1U << 20) /* Create VXLAN Default
                                                          Network Port */
#define BCM_VXLAN_PORT_ENABLE_VLAN_CHECKS   (1U << 21) /* Enable stp check on
                                                          ingress physical port,
                                                          only for access VP
                                                          derived from
                                                          VLAN_XLATE */
#define BCM_VXLAN_PORT_SHARE                (1U << 22) /* Create shared
                                                          multicast VXLAN
                                                          network port */
#define BCM_VXLAN_PORT_ENCAP_LOCAL          (1U << 23) /* Encapsulate the VXLAN
                                                          tunnel on local device */
#define BCM_VXLAN_PORT_TUNNEL_QOS_MAP       (1U << 24) /* Use QoS mapped
                                                          priority for egress
                                                          Tunnel packet priority
                                                          control */
#define BCM_VXLAN_PORT_TUNNEL_OUTER_VLAN_DELETE (1U << 25) /* Delete Tunnel Outer
                                                          VLAN Tag */
#define BCM_VXLAN_PORT_TUNNEL_INNER_VLAN_DELETE (1U << 26) /* Delete Tunnel Inner
                                                          VLAN Tag */
#define BCM_VXLAN_PORT_UDP_SRC_PORT_RANGE_ENABLE (1U << 27) /* UDP source port range
                                                          checking for Entropy */
#define BCM_VXLAN_PORT_VPN_BASED            (1U << 28) /* To specify the VP is
                                                          per VPN based */
#define BCM_VXLAN_PORT_LOOPBACK             (1U << 29) /* Loopback facing
                                                          interface for 2-pass
                                                          RIOT */
#define BCM_VXLAN_PORT_NO_SPLIT_HORIZON_EGRESS (1U << 30) /* Disable the egress
                                                          split horizon check on
                                                          the destination
                                                          network port. */
#define BCM_VXLAN_PORT_NO_SPLIT_HORIZON_INGRESS (1U << 31) /* Disable the ingress
                                                          split horizon check on
                                                          the destination
                                                          network port when RIOT
                                                          is disabled. */
#endif

#if defined(INCLUDE_L3)
/* BCM_VXLAN_PORT_FLAGS2* flags. */
#define BCM_VXLAN_PORT_FLAGS2_UT_VLAN_ACTION_NO_CLEAR (1 << 0)   /* Do not clear untagged
                                                          VLAN actions. Used
                                                          only when
                                                          BCM_VXLAN_MATCH_PORT
                                                          is set. */
#define BCM_VXLAN_PORT_FLAGS2_NO_SPLIT_HORIZON_SOURCE (1 << 1)   /* Disable the split
                                                          horizon check on the
                                                          source network port. */
#define BCM_VXLAN_PORT_FLAGS2_VNI_FLOW_TERMINATOR (1 << 2)   /* Indicate the VNI flow
                                                          terminator of the
                                                          VXLAN. */
#endif

#if defined(INCLUDE_L3)
/* VXLAN Gport */
typedef struct bcm_vxlan_port_s {
    bcm_gport_t vxlan_port_id;          /* GPORT identifier. */
    uint32 flags;                       /* BCM_VXLAN_PORT_xxx. */
    uint32 if_class;                    /* Interface class ID. */
    uint16 int_pri;                     /* Internal Priority */
    uint8 pkt_pri;                      /* Packet Priority */
    uint8 pkt_cfi;                      /* Packet CFI */
    uint16 egress_service_tpid;         /* Service Vlan TPID Value */
    bcm_vlan_t egress_service_vlan;     /* SD-TAG Vlan ID. */
    uint16 mtu;                         /* MTU */
    bcm_gport_t match_port;             /* Match port / trunk */
    bcm_vxlan_port_match_t criteria;    /* Match criteria */
    bcm_vlan_t match_vlan;              /* Outer VLAN ID to match. */
    bcm_vlan_t match_inner_vlan;        /* Inner VLAN ID to match. */
    bcm_gport_t egress_tunnel_id;       /* Tunnel Initiator ID */
    bcm_gport_t match_tunnel_id;        /* Tunnel Terminator ID */
    bcm_if_t egress_if;                 /* VXLAN egress object. */
    bcm_switch_network_group_t network_group_id; /* Split Horizon network group
                                           identifier. */
    uint32 vnid;                        /* VXLAN packet VNID. */
    int qos_map_id;                     /* QoS Mapped priority */
    uint8 tunnel_pkt_pri;               /* Tunnel Packet Priority */
    uint8 tunnel_pkt_cfi;               /* Tunnel Packet CFI */
    uint32 flags2;                      /* BCM_VXLAN_PORT_FLAGS2_xxx. */
    bcm_vpn_t default_vpn;              /* default vxlan vpn */
    bcm_vlan_t match_etag_vlan;         /* Match ETAG VLAN ID */
} bcm_vxlan_port_t;
#endif

extern void bcm_vxlan_port_t_init(
    bcm_vxlan_port_t *vxlan_port);

#ifndef BCM_HIDE_DISPATCHABLE

#if defined(INCLUDE_L3)
/* Initialize the BCM VXLAN subsystem. */
extern int bcm_vxlan_init(
    int unit);
#endif

#if defined(INCLUDE_L3)
/* Detach the BCM VXLAN subsystem. */
extern int bcm_vxlan_cleanup(
    int unit);
#endif

#if defined(INCLUDE_L3)
/* bcm_vxlan_port_add adds a Access or Network VXLAN port */
extern int bcm_vxlan_port_add(
    int unit, 
    bcm_vpn_t l2vpn, 
    bcm_vxlan_port_t *vxlan_port);
#endif

#if defined(INCLUDE_L3)
/* bcm_vxlan_port_delete VXLAN port from VXLAN network. */
extern int bcm_vxlan_port_delete(
    int unit, 
    bcm_vpn_t l2vpn, 
    bcm_gport_t vxlan_port_id);
#endif

#if defined(INCLUDE_L3)
/* bcm_vxlan_port_delete VXLAN port from VXLAN network. */
extern int bcm_vxlan_port_delete_all(
    int unit, 
    bcm_vpn_t l2vpn);
#endif

#if defined(INCLUDE_L3)
/* Get VXLAN port information. */
extern int bcm_vxlan_port_get(
    int unit, 
    bcm_vpn_t l2vpn, 
    bcm_vxlan_port_t *vxlan_port);
#endif

#if defined(INCLUDE_L3)
/* Get all VXLAN port information. */
extern int bcm_vxlan_port_get_all(
    int unit, 
    bcm_vpn_t l2vpn, 
    int port_max, 
    bcm_vxlan_port_t *port_array, 
    int *port_count);
#endif

#if defined(INCLUDE_L3)
/* Create VXLAN Tunnel Initiator. */
extern int bcm_vxlan_tunnel_initiator_create(
    int unit, 
    bcm_tunnel_initiator_t *info);
#endif

#if defined(INCLUDE_L3)
/* Delete VXLAN Tunnel Initiator. */
extern int bcm_vxlan_tunnel_initiator_destroy(
    int unit, 
    bcm_gport_t vxlan_tunnel_id);
#endif

#if defined(INCLUDE_L3)
/* Destroy all VXLAN Tunnel Initiators */
extern int bcm_vxlan_tunnel_initiator_destroy_all(
    int unit);
#endif

#if defined(INCLUDE_L3)
/* Get  VXLAN Tunnel Initiator. */
extern int bcm_vxlan_tunnel_initiator_get(
    int unit, 
    bcm_tunnel_initiator_t *info);
#endif

#if defined(INCLUDE_L3)
/* Traverse VXLAN Tunnel initiator. */
extern int bcm_vxlan_tunnel_initiator_traverse(
    int unit, 
    bcm_tunnel_initiator_traverse_cb cb, 
    void *user_data);
#endif

#if defined(INCLUDE_L3)
/* Create VXLAN Tunnel terminator. */
extern int bcm_vxlan_tunnel_terminator_create(
    int unit, 
    bcm_tunnel_terminator_t *info);
#endif

#if defined(INCLUDE_L3)
/* Update multicast/active state per VXLAN Tunnel terminator. */
extern int bcm_vxlan_tunnel_terminator_update(
    int unit, 
    bcm_tunnel_terminator_t *info);
#endif

#if defined(INCLUDE_L3)
/* Delete VXLAN Tunnel terminator. */
extern int bcm_vxlan_tunnel_terminator_destroy(
    int unit, 
    bcm_gport_t vxlan_tunnel_id);
#endif

#if defined(INCLUDE_L3)
/* Destroy all VXLAN Tunnel terminators */
extern int bcm_vxlan_tunnel_terminator_destroy_all(
    int unit);
#endif

#if defined(INCLUDE_L3)
/* Get VXLAN Tunnel terminator. */
extern int bcm_vxlan_tunnel_terminator_get(
    int unit, 
    bcm_tunnel_terminator_t *info);
#endif

#if defined(INCLUDE_L3)
/* Traverse VXLAN Tunnel terminator. */
extern int bcm_vxlan_tunnel_terminator_traverse(
    int unit, 
    bcm_tunnel_terminator_traverse_cb cb, 
    void *user_data);
#endif

#endif /* BCM_HIDE_DISPATCHABLE */

/* Ingress and Egress statistics maintained per Vxlan. */
typedef enum bcm_vxlan_stat_e {
    bcmVxlanInPackets = 0,  /* Packets that ingress on the vxlan */
    bcmVxlanOutPackets = 1, /* Packets that egress on the vxlan */
    bcmVxlanInBytes = 2,    /* Bytes that ingress on the vxlan */
    bcmVxlanOutBytes = 3    /* Bytes that egress on the vxlan */
} bcm_vxlan_stat_t;

/* Ingress statistics maintained per Vxlan Dip. */
typedef enum bcm_vxlan_dip_stat_e {
    bcmVxlanDipInPackets = 0,   /* Packets that ingress on the Vxlan Dip . */
    bcmVxlanDipInBytes = 1      /* Bytes that ingress on the Vxlan Dip . */
} bcm_vxlan_dip_stat_t;

#ifndef BCM_HIDE_DISPATCHABLE

/* Attach counters entries to the given vxlan vp/vpn index */
extern int bcm_vxlan_stat_attach(
    int unit, 
    bcm_gport_t port, 
    bcm_vpn_t vpn, 
    uint32 stat_counter_id);

/* Detach  counters entries to the given vxlan vp/vpn index. */
extern int bcm_vxlan_stat_detach(
    int unit, 
    bcm_gport_t port, 
    bcm_vpn_t vpn);

/* Get counter statistic values for a vxlan vp/vpn index. */
extern int bcm_vxlan_stat_counter_get(
    int unit, 
    bcm_gport_t port, 
    bcm_vpn_t vpn, 
    bcm_vxlan_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    bcm_stat_value_t *counter_values);

/* 
 * Force an immediate counter update and retrieve counter statistic
 * values for
 * a vxlan vp/vpn index.
 */
extern int bcm_vxlan_stat_counter_sync_get(
    int unit, 
    bcm_gport_t port, 
    bcm_vpn_t vpn, 
    bcm_vxlan_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    bcm_stat_value_t *counter_values);

/* Set counter statistic values for a vxlan vp/vpn index */
extern int bcm_vxlan_stat_counter_set(
    int unit, 
    bcm_gport_t port, 
    bcm_vpn_t vpn, 
    bcm_vxlan_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    bcm_stat_value_t *counter_values);

/* Get multiple counter statistic values for multiple vxlan vp/vpn index. */
extern int bcm_vxlan_stat_multi_get(
    int unit, 
    bcm_gport_t port, 
    bcm_vpn_t vpn, 
    int nstat, 
    bcm_vxlan_stat_t *stat_arr, 
    uint64 *value_arr);

/* 
 * Get 32bit multiple counter statistic values for multiple vxlan vp/vpn
 * index.
 */
extern int bcm_vxlan_stat_multi_get32(
    int unit, 
    bcm_gport_t port, 
    bcm_vpn_t vpn, 
    int nstat, 
    bcm_vxlan_stat_t *stat_arr, 
    uint32 *value_arr);

/* Set multiple counter statistic values for multiple vxlan vp/vpn index. */
extern int bcm_vxlan_stat_multi_set(
    int unit, 
    bcm_gport_t port, 
    bcm_vpn_t vpn, 
    int nstat, 
    bcm_vxlan_stat_t *stat_arr, 
    uint64 *value_arr);

/* 
 * Set 32bit multiple counter statistic values for multiple vxlan vp/vpn
 * index.
 */
extern int bcm_vxlan_stat_multi_set32(
    int unit, 
    bcm_gport_t port, 
    bcm_vpn_t vpn, 
    int nstat, 
    bcm_vxlan_stat_t *stat_arr, 
    uint32 *value_arr);

/* Get stat counter ID associated with given vxlan vp/vpn index. */
extern int bcm_vxlan_stat_id_get(
    int unit, 
    bcm_gport_t port, 
    bcm_vpn_t vpn, 
    bcm_vxlan_stat_t stat, 
    uint32 *stat_counter_id);

/* Enable/Disable collection of statistics on the indicated port or vpn */
extern int bcm_vxlan_stat_enable_set(
    int unit, 
    bcm_gport_t port, 
    bcm_vpn_t vpn, 
    int enable);

/* Attach counters entries to a given VXLAN DIP. */
extern int bcm_vxlan_dip_stat_attach(
    int unit, 
    bcm_ip_t vxlan_dip, 
    uint32 stat_counter_id);

/* Detach counters entries to a given VXLAN DIP. */
extern int bcm_vxlan_dip_stat_detach(
    int unit, 
    bcm_ip_t vxlan_dip);

/* Get the specified counter statistic for a given VXLAN DIP. */
extern int bcm_vxlan_dip_stat_counter_get(
    int unit, 
    bcm_ip_t vxlan_dip, 
    bcm_vxlan_dip_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    bcm_stat_value_t *counter_values);

/* Set the specified counter statistic for a given VXLAN DIP. */
extern int bcm_vxlan_dip_stat_counter_set(
    int unit, 
    bcm_ip_t vxlan_dip, 
    bcm_vxlan_dip_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    bcm_stat_value_t *counter_values);

/* Get 64-bit counter value for multiple VXLAN DIP statistic types. */
extern int bcm_vxlan_dip_stat_multi_get(
    int unit, 
    bcm_ip_t vxlan_dip, 
    int nstat, 
    bcm_vxlan_dip_stat_t *stat_arr, 
    uint64 *value_arr);

/* Get 32-bit counter value for multiple VXLAN DIP statistic types. */
extern int bcm_vxlan_dip_stat_multi_get32(
    int unit, 
    bcm_ip_t vxlan_dip, 
    int nstat, 
    bcm_vxlan_dip_stat_t *stat_arr, 
    uint32 *value_arr);

/* set 64-bit counter value for multiple VXLAN DIP statistic types. */
extern int bcm_vxlan_dip_stat_multi_set(
    int unit, 
    bcm_ip_t vxlan_dip, 
    int nstat, 
    bcm_vxlan_dip_stat_t *stat_arr, 
    uint64 *value_arr);

/* set 32-bit counter value for multiple VXLAN DIP statistic types. */
extern int bcm_vxlan_dip_stat_multi_set32(
    int unit, 
    bcm_ip_t vxlan_dip, 
    int nstat, 
    bcm_vxlan_dip_stat_t *stat_arr, 
    uint32 *value_arr);

/* Retrieve associated stat counter for a given VXLAN DIP. */
extern int bcm_vxlan_dip_stat_id_get(
    int unit, 
    bcm_ip_t vxlan_dip, 
    bcm_vxlan_dip_stat_t stat, 
    uint32 *stat_counter_id);

#endif /* BCM_HIDE_DISPATCHABLE */

/* VXLAN port callback function prototype */
#if defined(INCLUDE_L3)
typedef int(*bcm_vxlan_port_traverse_cb)(
    int unit, 
    bcm_vxlan_port_t *info, 
    void *user_data);
#endif

#ifndef BCM_HIDE_DISPATCHABLE

#if defined(INCLUDE_L3)
/* Traverse all valid VXLAN port and call the supplied callback routine. */
extern int bcm_vxlan_port_traverse(
    int unit, 
    bcm_vxlan_port_traverse_cb cb, 
    void *user_data);
#endif

#endif /* BCM_HIDE_DISPATCHABLE */

#if defined(INCLUDE_L3)
/* Invalid VXLAN VNI. */
#define BCM_VXLAN_VNI_INVALID   -1         /* Invalid VXLAN VNI */
#endif

#if defined(INCLUDE_L3)
/* VXLAN Network Domain Config Structure. */
typedef struct bcm_vxlan_network_domain_config_s {
    uint32 flags;               /* BCM_VXLAN_NETWORK_DOMAIN_CONFIG_XXX. */
    uint32 vsi;                 /* Virtual switch instance. Populated for l2
                                   mapping only. */
    bcm_vrf_t vrf;              /* Virtual router instance. Populated for l3
                                   mapping only. */
    uint32 network_domain;      /* Network identifier. Used to distinct between
                                   multiple network. */
    uint32 vni;                 /* VXLAN packet VNID. */
    int qos_map_id;             /* QoS Mapped priority */
    bcm_gport_t vlan_port_id;   /* Vlan gport identifier */
    uint32 stat_id;             /* object statistic id (the counter_pointer
                                   value as sent to the crps) */
    int stat_pp_profile;        /* profile */
} bcm_vxlan_network_domain_config_t;
#endif

#if defined(INCLUDE_L3)
/* Flags for bcm_vxlan_network_domain_config_t. */
#define BCM_VXLAN_NETWORK_DOMAIN_CONFIG_INGRESS_ONLY 0x00000001 /* Add only ingress
                                                          mapping. */
#define BCM_VXLAN_NETWORK_DOMAIN_CONFIG_EGRESS_ONLY 0x00000002 /* Add only egress
                                                          mapping. */
#define BCM_VXLAN_NETWORK_DOMAIN_CONFIG_L2_MAPPING 0x00000004 /* Add L2 mapping. */
#define BCM_VXLAN_NETWORK_DOMAIN_CONFIG_L3_MAPPING 0x00000008 /* Add L3 mapping. */
#define BCM_VXLAN_NETWORK_DOMAIN_CONFIG_REPLACE 0x00000010 /* Replace the mapping. */
#endif

#if defined(INCLUDE_L3)
/* VXLAN Network Domain Config Structure. */
typedef struct bcm_vxlan_network_domain_config_additional_info_s {
    uint32 flags;   /* BCM_VXLAN_NETWORK_DOMAIN_CONFIG_XXX. */
} bcm_vxlan_network_domain_config_additional_info_t;
#endif

#if defined(INCLUDE_L3)
/* Initialize the VXLAN Network domain structure. */
extern void bcm_vxlan_network_domain_config_t_init(
    bcm_vxlan_network_domain_config_t *config);
#endif

/* VXLAN port callback function prototype */
#if defined(INCLUDE_L3)
typedef int(*bcm_vxlan_network_domain_config_traverse_cb)(
    int unit, 
    bcm_vxlan_network_domain_config_t *info, 
    void *user_data);
#endif

#ifndef BCM_HIDE_DISPATCHABLE

#if defined(INCLUDE_L3)
/* Add a local identifier (vsi or vrf) with a VNI mapping. */
extern int bcm_vxlan_network_domain_config_add(
    int unit, 
    bcm_vxlan_network_domain_config_t *config);
#endif

#if defined(INCLUDE_L3)
/* Get local identifier (vsi or vrf) with VNI mapping. */
extern int bcm_vxlan_network_domain_config_get(
    int unit, 
    bcm_vxlan_network_domain_config_t *config);
#endif

#if defined(INCLUDE_L3)
/* Remove local identifier (vsi or vrf) with VNI mapping. */
extern int bcm_vxlan_network_domain_config_remove(
    int unit, 
    bcm_vxlan_network_domain_config_t *config);
#endif

#if defined(INCLUDE_L3)
/* Traverse local identifier (vsi or vrf) with VNI mapping. */
extern int bcm_vxlan_network_domain_config_traverse(
    int unit, 
    bcm_vxlan_network_domain_config_additional_info_t *additional_info, 
    bcm_vxlan_network_domain_config_traverse_cb cb, 
    void *user_data);
#endif

#endif /* defined(INCLUDE_L3) */

#endif /* BCM_HIDE_DISPATCHABLE */

#endif /* __BCM_VXLAN_H__ */

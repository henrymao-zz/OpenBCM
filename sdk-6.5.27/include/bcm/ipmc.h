/*
 * 
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 */

#ifndef __BCM_IPMC_H__
#define __BCM_IPMC_H__

#if defined(INCLUDE_L3)

#include <bcm/types.h>
#include <bcm/l3.h>

/* IPMC address type. */
typedef struct bcm_ipmc_addr_s {
    bcm_ip_t s_ip_addr;                 /* IPv4 Source address. */
    bcm_ip_t mc_ip_addr;                /* IPv4 Destination address. */
    bcm_ip6_t s_ip6_addr;               /* IPv6 Source address. */
    bcm_ip6_t mc_ip6_addr;              /* IPv6 Destination address. */
    bcm_vlan_t vid;                     /* VLAN identifier. */
    bcm_vrf_t vrf;                      /* Virtual Router Instance. */
    bcm_cos_t cos;                      /* COS based on dst IP multicast addr. */
    int ts;                             /* Source port or TGID bit. */
    int port_tgid;                      /* Source port or TGID. */
    int v;                              /* Valid bit. */
    int mod_id;                         /* Module ID. */
    bcm_multicast_t group;              /* Use this index to program IPMC table
                                           for XGS chips based on flags value */
    uint32 flags;                       /* See BCM_IPMC_XXX flag definitions. */
    int lookup_class;                   /* Classification lookup class ID. */
    bcm_fabric_distribution_t distribution_class; /* Fabric Distribution Class. */
    bcm_if_t l3a_intf;                  /* L3 interface associated with route. */
    int rp_id;                          /* Rendezvous point ID. */
    bcm_ip_t s_ip_mask;                 /* IPv4 Source subnet mask. */
    bcm_if_t ing_intf;                  /* L3 interface associated with this
                                           Entry */
    bcm_ip_t mc_ip_mask;                /* IPv4 Destination subnet mask. */
    bcm_ip6_t mc_ip6_mask;              /* IPv6 Destination subnet mask. */
    bcm_multicast_t group_l2;           /* Use this index to program IPMC table
                                           for l2 recipients if TTL/RPF check
                                           fails. */
    uint32 stat_id;                     /* Object statistics ID. */
    int stat_pp_profile;                /* Statistics profile. */
    bcm_ip6_t s_ip6_mask;               /* IPv6 Source subnet mask. */
    int priority;                       /* Entry priority. */
    uint32 flow_handle;                 /* FLOW handle for flex entries. */
    uint32 flow_option_handle;          /* FLOW option handle for flex entries. */
    bcm_flow_logical_field_t logical_fields[BCM_FLOW_MAX_NOF_LOGICAL_FIELDS]; /* logical fields array for flex
                                           entries. */
    uint32 num_logical_fields;          /* number of logical fields. */
    int mtu;                            /* MTU. */
    int opaque_ctrl_id;                 /* Opaque control ID. */
    uint32 policer_counter_id;          /*  Policer counter index */
    uint32 policer_profile_id;          /*  Policer profile index */
} bcm_ipmc_addr_t;

/* IPMC address flags. */
#define BCM_IPMC_KEEP_ENTRY                 0x00000001 /* Internal use. */
#define BCM_IPMC_HIT                        0x00000002 /* On get, indicates if
                                                          L3 hit is on for
                                                          entry. */
#define BCM_IPMC_SOURCE_PORT_NOCHECK        0x80000000 /* Do not source port
                                                          check this entry (XGS
                                                          only). */
#define BCM_IPMC_DISABLED                   0x00000008 /* Add entry in disabled
                                                          state. */
#define BCM_IPMC_REPLACE                    0x00000010 /* Replace an existing
                                                          entry. */
#define BCM_IPMC_IP6                        0x00000020 /* IPv6 support. */
#define BCM_IPMC_HIT_CLEAR                  0x00000040 /* Clear hit bit. */
#define BCM_IPMC_SETPRI                     0x00000080 /* Pick up new priority
                                                          (XGS3 only). */
#define BCM_IPMC_PROXY_IP6                  0x00000100 /* IPv6 Proxy MC egress
                                                          ports on XGS2. */
#define BCM_IPMC_ADD_DISABLED               BCM_IPMC_DISABLED 
#define BCM_IPMC_USE_FABRIC_DISTRIBUTION    0x00000400 /* Use specified fabric
                                                          distribution class. */
#define BCM_IPMC_COPYTOCPU                  0x00000800 /* When set, Copy the
                                                          packet to CPU. */
#define BCM_IPMC_POST_LOOKUP_RPF_CHECK      0x00001000 /* When set, perform RPF
                                                          check. */
#define BCM_IPMC_RPF_FAIL_DROP              0x00002000 /* Drop packet on RPF
                                                          failure. */
#define BCM_IPMC_RPF_FAIL_TOCPU             0x00004000 /* Copy packets to CPU on
                                                          RPF failure. */
#define BCM_IPMC_L2                         0x00008000 /* XGS: Define IPMC L2
                                                          domain lookup
                                                          (VLAN/VFI) in L3 IPMC
                                                          table. DNX: Add a
                                                          bridged MC entry */
#define BCM_IPMC_RAW_ENTRY                  0x00010000 /* Insert raw data
                                                          payload */
#define BCM_IPMC_DECAP_ROE_HEADER           0x00020000 /* Indicates the
                                                          decapsulation of
                                                          ROE/ROE Custom Header. */
#define BCM_IPMC_TCAM                       0x00040000 /* Indicates MC TCAM
                                                          entry. */
#define BCM_IPMC_RP_ID_EXPECTED_INTF_RESOLVE 0x00080000 /* Indicates
                                                          configuration
                                                          resolution between
                                                          rendezvous point ID
                                                          (l3a_rp) and L3
                                                          interface
                                                          (l3a_expected_intf) is
                                                          not successful during
                                                          route
                                                          get/find/traverse
                                                          APIs. bcm_l3_route_t
                                                          has l3a_rp and
                                                          l3a_expected_intf
                                                          members set without
                                                          BCM_IPMC_POST_LOOKUP_RPF_CHECK
                                                          in l3a_ipmc_flags. End
                                                          user application
                                                          should resolve based
                                                          on application
                                                          configuration. Flag is
                                                          set as a result of
                                                          route get, find and
                                                          traverse operations
                                                          and is not applicable
                                                          for any other
                                                          operations. */
#define BCM_IPMC_DISCARD                    0x00100000 /* Indicates to discard
                                                          packets on entry hit. */
#define BCM_IPMC_DEFAULT_ENTRY              0x00200000 /* Indicates a default
                                                          entry. */
#define BCM_IPMC_HIT_ENABLE                 0x00400000 /* Indicates to enable
                                                          hit-bit on entry. */
#define BCM_IPMC_LPM                        0x00800000 /* Indicates MC LPM
                                                          entry. */

/* Invalid value for rendezvous point ID parameter. */
#define BCM_IPMC_RP_ID_INVALID  -1         /* Invalid rendezvous point ID */

/* IPMC counters structure. */
typedef struct bcm_ipmc_counters_s {
    uint64 rmca;    /* Received L2 multicast frame. */
    uint64 tmca;    /* Transmit L2 multicast packet counter. */
    uint64 imbp;    /* Number of IPMC packets bridged. */
    uint64 imrp;    /* Number of IPMC packets routed. */
    uint64 rimdr;   /* Number of IPMC dropped in ingress. */
    uint64 timdr;   /* Number of IPMC dropped in egress. */
} bcm_ipmc_counters_t;

/* bcm_ipmc_traverse_cb */
typedef int (*bcm_ipmc_traverse_cb)(
    int unit, 
    bcm_ipmc_addr_t *info, 
    void *user_data);

#ifndef BCM_HIDE_DISPATCHABLE

/* Initialize the BCM IPMC subsystem. */
extern int bcm_ipmc_init(
    int unit);

/* Detach the BCM IPMC subsystem. */
extern int bcm_ipmc_detach(
    int unit);

/* Enable/disable IPMC support. */
extern int bcm_ipmc_enable(
    int unit, 
    int enable);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Initialize a bcm_ipmc_addr_t. */
extern void bcm_ipmc_addr_t_init(
    bcm_ipmc_addr_t *data);

#ifndef BCM_HIDE_DISPATCHABLE

/* Add a new entry to IPMC table. */
extern int bcm_ipmc_add(
    int unit, 
    bcm_ipmc_addr_t *data);

/* Find info about an IPMC entry. */
extern int bcm_ipmc_find(
    int unit, 
    bcm_ipmc_addr_t *data);

/* Remove an entry from IPMC table. */
extern int bcm_ipmc_remove(
    int unit, 
    bcm_ipmc_addr_t *data);

/* Remove all entries from IPMC table. */
extern int bcm_ipmc_remove_all(
    int unit);

/* Set the age timer for the IPMC entries (0 to disable). */
extern int bcm_ipmc_age_timer_set(
    int unit, 
    int seconds);

/* Get the age timer for IPMC entries (0 for timer disable). */
extern int bcm_ipmc_age_timer_get(
    int unit, 
    int *seconds);

/* Set flex counter object value for the given IPMC group. */
extern int bcm_ipmc_flexctr_object_set(
    int unit, 
    bcm_ipmc_addr_t *info, 
    uint32 value);

/* Get flex counter object value for the given IPMC group. */
extern int bcm_ipmc_flexctr_object_get(
    int unit, 
    bcm_ipmc_addr_t *info, 
    uint32 *value);

/* Reinitialize/clear the egress IP multicast configuration. */
extern int bcm_ipmc_egress_port_init(
    int unit);

/* Configure the IP Multicast egress properties. */
extern int bcm_ipmc_egress_port_set(
    int unit, 
    bcm_port_t port, 
    const bcm_mac_t mac, 
    int untag, 
    bcm_vlan_t vid, 
    int ttl_threshold);

/* Get the egress IP multicast configuration properties. */
extern int bcm_ipmc_egress_port_get(
    int unit, 
    bcm_port_t port, 
    bcm_mac_t mac, 
    int *untag, 
    bcm_vlan_t *vid, 
    int *ttl_threshold);

/* Get the combined IP multicast statistics. */
extern int bcm_ipmc_counters_get(
    int unit, 
    bcm_port_t port, 
    bcm_ipmc_counters_t *counters);

/* Provides the maximum IPMC index that this fabric can handle. */
extern int bcm_ipmc_bitmap_max_get(
    int unit, 
    int *max_index);

/* Set the IPMC forwarding port bitmap. */
extern int bcm_ipmc_bitmap_set(
    int unit, 
    int ipmc_idx, 
    bcm_port_t port, 
    bcm_pbmp_t pbmp);

/* Get the IPMC forwarding port bitmap */
extern int bcm_ipmc_bitmap_get(
    int unit, 
    int ipmc_idx, 
    bcm_port_t port, 
    bcm_pbmp_t *pbmp);

/* Remove IPMC forwarding port bitmap */
extern int bcm_ipmc_bitmap_del(
    int unit, 
    int ipmc_idx, 
    bcm_port_t port, 
    bcm_pbmp_t pbmp);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Initialize an IPMC counters structure. */
extern void bcm_ipmc_counters_t_init(
    bcm_ipmc_counters_t *ipmc_counter);

#ifndef BCM_HIDE_DISPATCHABLE

/* Run IPMC table aging. */
extern int bcm_ipmc_age(
    int unit, 
    uint32 flags, 
    bcm_ipmc_traverse_cb age_cb, 
    void *user_data);

/* 
 * Traverse through the IPMC table and run callback at each valid IPMC
 * entry.
 */
extern int bcm_ipmc_traverse(
    int unit, 
    uint32 flags, 
    bcm_ipmc_traverse_cb cb, 
    void *user_data);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Types of IPMC aging events that will be notified to applications. */
typedef enum bcm_ipmc_age_event_e {
    bcmIpmcAgeEventDelete = 0,          /* Delete IPMC entry. */
    bcmIpmcAgeEventDeleteCancel = 1,    /* Cancel the deletion on IPMC entry. */
    bcmIpmcAgeEventCount = 2 
} bcm_ipmc_age_event_t;

/* Callback function used for receiving aging notification. */
typedef int (*bcm_ipmc_age_cb_t)(
    int unit, 
    bcm_ipmc_addr_t *info, 
    bcm_ipmc_age_event_t event, 
    void *user_data);

#ifndef BCM_HIDE_DISPATCHABLE

/* Register a callback routine. */
extern int bcm_ipmc_age_cb_register(
    int unit, 
    bcm_ipmc_age_cb_t cb, 
    void *user_data);

/* Unregister a callback routine. */
extern int bcm_ipmc_age_cb_unregister(
    int unit, 
    bcm_ipmc_age_cb_t cb, 
    void *user_data);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Rendezvous point flags. */
#define BCM_IPMC_RP_WITH_ID     0x00000001 /* Rendezvous point ID is provided. */

/* Configurational flags for cascaded entries */
#define BCM_IPMC_CONFIG_TRAVERSE_DELETE_ALL 0x1        /* Cleared
                                                          configurational tables */

#ifndef BCM_HIDE_DISPATCHABLE

/* Create a rendezvous point tree. */
extern int bcm_ipmc_rp_create(
    int unit, 
    uint32 flags, 
    int *rp_id);

/* Destroy a rendezvous point tree. */
extern int bcm_ipmc_rp_destroy(
    int unit, 
    int rp_id);

/* Set active L3 interfaces of a rendezvous point tree. */
extern int bcm_ipmc_rp_set(
    int unit, 
    int rp_id, 
    int intf_count, 
    bcm_if_t *intf_array);

/* Get active L3 interfaces of a rendezvous point tree. */
extern int bcm_ipmc_rp_get(
    int unit, 
    int rp_id, 
    int intf_max, 
    bcm_if_t *intf_array, 
    int *intf_count);

/* Add an active L3 interface to a rendezvous point tree. */
extern int bcm_ipmc_rp_add(
    int unit, 
    int rp_id, 
    bcm_if_t intf_id);

/* Delete an active L3 interface from a rendezvous point tree. */
extern int bcm_ipmc_rp_delete(
    int unit, 
    int rp_id, 
    bcm_if_t intf_id);

/* Delete all active L3 interfaces from a rendezvous point tree. */
extern int bcm_ipmc_rp_delete_all(
    int unit, 
    int rp_id);

#endif /* BCM_HIDE_DISPATCHABLE */

/* IPMC address range info. */
typedef struct bcm_ipmc_range_s {
    uint32 flags;               /* BCM_IPMC_RANGE_xxx flags. */
    int priority;               /* Priority. */
    bcm_ip_t mc_ip_addr;        /* IPv4 group address. */
    bcm_ip_t mc_ip_addr_mask;   /* IPv4 group address mask. */
    bcm_ip6_t mc_ip6_addr;      /* IPv6 group address. */
    bcm_ip6_t mc_ip6_addr_mask; /* IPv6 group address mask. */
    bcm_vrf_t vrf;              /* Virtual router instance. */
    bcm_vrf_t vrf_mask;         /* Virtual router instance mask. */
    int rp_id;                  /* Rendezvous Point ID */
} bcm_ipmc_range_t;

/* Flags for bcm_ipmc_range APIs. */
#define BCM_IPMC_RANGE_WITH_ID      (1 << 0)   /* Use the specified range ID. */
#define BCM_IPMC_RANGE_REPLACE      (1 << 1)   /* Replace an existing range. */
#define BCM_IPMC_RANGE_IP6          (1 << 2)   /* IPv6 group address range is
                                                  valid. */
#define BCM_IPMC_RANGE_PIM_BIDIR    (1 << 3)   /* Packets matching this range
                                                  are subject to PIM-BIDIR
                                                  processing. */

/* Encap Id used to add or delete a trunk member */
#define BCM_ENCAP_TRUNK_MEMBER  0xfffffffe /* Encap Identifier */

/* Initialize a bcm_ipmc_range_t structure. */
extern void bcm_ipmc_range_t_init(
    bcm_ipmc_range_t *range);

#ifndef BCM_HIDE_DISPATCHABLE

/* Add a range of IP multicast addresses. */
extern int bcm_ipmc_range_add(
    int unit, 
    int *range_id, 
    bcm_ipmc_range_t *range);

/* Delete a range of IP multicast addresses. */
extern int bcm_ipmc_range_delete(
    int unit, 
    int range_id);

/* Delete all ranges of IP multicast addresses. */
extern int bcm_ipmc_range_delete_all(
    int unit);

/* Get a range of IP multicast addresses. */
extern int bcm_ipmc_range_get(
    int unit, 
    int range_id, 
    bcm_ipmc_range_t *range);

/* Get the maximum number of IP multicast address ranges supported. */
extern int bcm_ipmc_range_size_get(
    int unit, 
    int *size);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Ipmc statistics maintained per IPMC group. */
typedef enum bcm_ipmc_stat_e {
    bcmIpmcInPackets = 0,   /* Packets that ingress on the IPMC group. */
    bcmIpmcInBytes = 1      /* Bytes that ingress on the IPMC group. */
} bcm_ipmc_stat_t;

#ifndef BCM_HIDE_DISPATCHABLE

/* Attach counters entries to the given IPMC group. */
extern int bcm_ipmc_stat_attach(
    int unit, 
    bcm_ipmc_addr_t *info, 
    uint32 stat_counter_id);

/* Detach counters entries to the given IPMC group. */
extern int bcm_ipmc_stat_detach(
    int unit, 
    bcm_ipmc_addr_t *info);

/* Get counter statistic values for an IPMC group. */
extern int bcm_ipmc_stat_counter_get(
    int unit, 
    bcm_ipmc_addr_t *info, 
    bcm_ipmc_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    bcm_stat_value_t *counter_values);

/* 
 * Force an immediate counter update and retrieve counter statistic
 * values
 * for an IPMC group.
 */
extern int bcm_ipmc_stat_counter_sync_get(
    int unit, 
    bcm_ipmc_addr_t *info, 
    bcm_ipmc_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    bcm_stat_value_t *counter_values);

/* Set counter statistic values for an IPMC group. */
extern int bcm_ipmc_stat_counter_set(
    int unit, 
    bcm_ipmc_addr_t *info, 
    bcm_ipmc_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    bcm_stat_value_t *counter_values);

/* Get multiple counter statistic values for multiple IPMC group. */
extern int bcm_ipmc_stat_multi_get(
    int unit, 
    bcm_ipmc_addr_t *info, 
    int nstat, 
    bcm_ipmc_stat_t *stat_arr, 
    uint64 *value_arr);

/* Get 32bit multiple counter statistic values for multiple IPMC group. */
extern int bcm_ipmc_stat_multi_get32(
    int unit, 
    bcm_ipmc_addr_t *info, 
    int nstat, 
    bcm_ipmc_stat_t *stat_arr, 
    uint32 *value_arr);

/* Set multiple counter statistic values for multiple IPMC group. */
extern int bcm_ipmc_stat_multi_set(
    int unit, 
    bcm_ipmc_addr_t *info, 
    int nstat, 
    bcm_ipmc_stat_t *stat_arr, 
    uint64 *value_arr);

/* Set 32bit multiple counter statistic values for multiple IPMC group. */
extern int bcm_ipmc_stat_multi_set32(
    int unit, 
    bcm_ipmc_addr_t *info, 
    int nstat, 
    bcm_ipmc_stat_t *stat_arr, 
    uint32 *value_arr);

/* Get stat counter ID associated with given IPMC group. */
extern int bcm_ipmc_stat_id_get(
    int unit, 
    bcm_ipmc_addr_t *info, 
    bcm_ipmc_stat_t stat, 
    uint32 *stat_counter_id);

#endif /* BCM_HIDE_DISPATCHABLE */

/* bcm_ipmc_config_traverse_cb */
typedef int (*bcm_ipmc_config_traverse_cb)(
    int unit, 
    bcm_ipmc_addr_t *info, 
    void *user_data);

#ifndef BCM_HIDE_DISPATCHABLE

/* Add a new configurational entry. */
extern int bcm_ipmc_config_add(
    int unit, 
    bcm_ipmc_addr_t *config);

/* Find a configurational entry. */
extern int bcm_ipmc_config_find(
    int unit, 
    bcm_ipmc_addr_t *config);

/* Remove a configurational entry */
extern int bcm_ipmc_config_remove(
    int unit, 
    bcm_ipmc_addr_t *config);

/* Traverse all configurational entries. */
extern int bcm_ipmc_config_traverse(
    int unit, 
    uint32 flags, 
    bcm_ipmc_config_traverse_cb cb, 
    void *user_data);

#endif /* defined(INCLUDE_L3) */

#endif /* BCM_HIDE_DISPATCHABLE */

#endif /* __BCM_IPMC_H__ */

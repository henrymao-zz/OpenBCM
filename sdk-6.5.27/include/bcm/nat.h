/*
 * 
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 */

#ifndef __BCM_NAT_H__
#define __BCM_NAT_H__

#if defined(INCLUDE_L3)

#include <bcm/types.h>
#include <bcm/l3.h>

/* L3 NAT definitions. */
#define BCM_L3_NAT_REALM_ID_INVALID -1         /* Invalid NAT realm ID. */

/* L3 NAT ingress. */
#define BCM_L3_NAT_INGRESS_DNAT             (1 << 0)   /* 1: DNAT entry, 0: SNAT
                                                          entry. */
#define BCM_L3_NAT_INGRESS_DNAT_POOL        (1 << 1)   /* Indicates DNAT pool
                                                          entry. */
#define BCM_L3_NAT_INGRESS_TYPE_NAPT        (1 << 2)   /* 0: Indicates NAT
                                                          entry. 1: Indicates
                                                          NAPT entry. */
#define BCM_L3_NAT_INGRESS_RPE              (1 << 3)   /* Assign internal
                                                          priority from DNAT
                                                          entry. */
#define BCM_L3_NAT_INGRESS_DST_DISCARD      (1 << 4)   /* Discard the packet on
                                                          DIP match. */
#define BCM_L3_NAT_INGRESS_MULTIPATH        (1 << 5)   /* Entry is for ECMP. */
#define BCM_L3_NAT_INGRESS_HIT              (1 << 6)   /* SNAT/DNAT entry match. */
#define BCM_L3_NAT_INGRESS_REPLACE          (1 << 7)   /* Replace existing
                                                          entry. */
#define BCM_L3_NAT_INGRESS_MULTICAST_SNAT   (1 << 8)   /* Entry is for Multicast
                                                          SNAT/SNAPT */

/* L3 NAT egress packet edit flags. */
#define BCM_L3_NAT_EGRESS_SNAT      (1 << 0)   /* Entry is for SNAT. */
#define BCM_L3_NAT_EGRESS_DNAT      (1 << 1)   /* Entry is for DNAT. */
#define BCM_L3_NAT_EGRESS_NAPT      (1 << 2)   /* Entry is for NAPT. */
#define BCM_L3_NAT_EGRESS_REPLACE   (1 << 3)   /* Replace existing entry. */
#define BCM_L3_NAT_EGRESS_WITH_ID   (1 << 4)   /* ID is provided. */

/* Egress nat table entry specification. */
typedef struct bcm_l3_nat_egress_s {
    uint32 flags;               /* See BCM_L3_NAT_EGRESS_XXX flag definitions. */
    bcm_l3_nat_id_t nat_id;     /* Index into packet edit table. */
    bcm_ip_t sip_addr;          /* Translated source IP. */
    bcm_ip_t sip_addr_mask;     /* Bits of source IP prefix to translate. */
    uint16 src_port;            /* Source l4 port for NAPT */
    bcm_ip_t dip_addr;          /* Translated dest IP. */
    bcm_ip_t dip_addr_mask;     /* Bits of dest IP prefix to translate. */
    uint16 dst_port;            /* Destination l4 port for NAPT */
    bcm_l3_nat_id_t snat_id;    /* Key for source and twice NAT/NAPT hash edit
                                   table. */
    bcm_l3_nat_id_t dnat_id;    /* Key for destination and twice NAT/NAPT hash
                                   edit table. */
    int nat_class_id;           /* NAT classid from L3 interface. */
} bcm_l3_nat_egress_t;

/* 
 * L3 Ingress NAT Structure.
 * 
 * Contains information required for manipulating either DNAT, DNAT pool
 * or SNAT table entries.
 */
typedef struct bcm_l3_nat_ingress_s {
    uint32 flags;           /* See BCM_L3_NAT_INGRESS_XXX flag definitions. */
    bcm_ip_t ip_addr;       /* IP address to be translated. */
    bcm_vrf_t vrf;          /* Virtual router instance. */
    uint16 l4_port;         /* TCP/UDP port. */
    uint8 ip_proto;         /* IP proto. */
    bcm_l3_nat_id_t nat_id; /* nat edit index to use on egress on hit. */
    bcm_cos_t pri;          /* New priority in packet. */
    int class_id;           /* Classification lookup class id. */
    bcm_if_t nexthop;       /* Nexthop of ecmp_ptr depending on MULTIPATH flag
                               setting. */
    int realm_id;           /* Realm ID for NAT. */
    int nat_class_id;       /* NAT classid from L3 interface. */
} bcm_l3_nat_ingress_t;

/* bcm_l3_nat_egress_traverse_cb */
typedef int (*bcm_l3_nat_egress_traverse_cb)(
    int unit, 
    int index, 
    bcm_l3_nat_egress_t *nat_info, 
    void *user_data);

/* Initialize a bcm_l3_nat_egress_t structure. */
extern void bcm_l3_nat_egress_t_init(
    bcm_l3_nat_egress_t *nat_info);

#ifndef BCM_HIDE_DISPATCHABLE

/* 
 * Add an egress NAT packet edit entry and return the index in nat_id
 * field of nat_info structure. If REPLACE flag is specified then use
 * nat_id field as the location to add the entry.
 */
extern int bcm_l3_nat_egress_add(
    int unit, 
    bcm_l3_nat_egress_t *nat_info);

/* Delete an egress NAT packet edit entry at the specified index nat_id */
extern int bcm_l3_nat_egress_delete(
    int unit, 
    bcm_l3_nat_id_t nat_id);

/* 
 * Delete an egress NAT hash entry. BCM_L3_NAT_EGRESS_XXX flags and
 * corresponding snat_id or dnat_id as hash key must be specified.
 */
extern int bcm_l3_nat_egress_destroy(
    int unit, 
    bcm_l3_nat_egress_t *nat_info);

/* 
 * Retrieve the egress NAT packet edit entry at the specified index in
 * nat_info structure
 */
extern int bcm_l3_nat_egress_get(
    int unit, 
    bcm_l3_nat_egress_t *nat_info);

/* 
 * Traverse through the egress NAT packet edit table and invoke a user
 * provided callback for each valid entry.
 */
extern int bcm_l3_nat_egress_traverse(
    int unit, 
    uint32 flags, 
    uint32 start, 
    uint32 end, 
    bcm_l3_nat_egress_traverse_cb cb, 
    void *user_data);

#endif /* BCM_HIDE_DISPATCHABLE */

/* L3 NAT statistics maintained per l3 egress nat. */
typedef enum bcm_l3_nat_egress_stat_e {
    bcmL3NatOutPackets = 0, /* Packets that egress on the l3 Nat nat */
    bcmL3NatOutBytes = 1    /* Bytes that egress on the l3 Nat */
} bcm_l3_nat_egress_stat_t;

#ifndef BCM_HIDE_DISPATCHABLE

/* Attach counter entries to the given l3 Egress NAT. */
extern int bcm_l3_nat_egress_stat_attach(
    int unit, 
    bcm_l3_nat_egress_t *info, 
    uint32 stat_counter_id);

/* Detach counter entries to the given l3 Egress NAT. */
extern int bcm_l3_nat_egress_stat_detach(
    int unit, 
    bcm_l3_nat_egress_t *info);

/* Get egress nat counter value for specified l3 Egress NAT */
extern int bcm_l3_nat_egress_stat_counter_get(
    int unit, 
    bcm_l3_nat_egress_t *info, 
    bcm_l3_nat_egress_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    bcm_stat_value_t *counter_values);

/* Get egress nat counter value for specified l3 Egress NAT */
extern int bcm_l3_nat_egress_stat_counter_sync_get(
    int unit, 
    bcm_l3_nat_egress_t *info, 
    bcm_l3_nat_egress_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    bcm_stat_value_t *counter_values);

/* Set egress nat counter value for specified l3 Egress NAT */
extern int bcm_l3_nat_egress_stat_counter_set(
    int unit, 
    bcm_l3_nat_egress_t *info, 
    bcm_l3_nat_egress_stat_t stat, 
    uint32 num_entries, 
    uint32 *counter_indexes, 
    bcm_stat_value_t *counter_values);

/* Get 64-bit counter value for multiple egress nat statistic types. */
extern int bcm_l3_nat_egress_stat_multi_get(
    int unit, 
    bcm_l3_nat_egress_t *info, 
    int nstat, 
    bcm_l3_nat_egress_stat_t *stat_arr, 
    uint64 *value_arr);

/* 
 * Get lower 32-bit counter value for multiple egress nat statistic
 * types.
 */
extern int bcm_l3_nat_egress_stat_multi_get32(
    int unit, 
    bcm_l3_nat_egress_t *info, 
    int nstat, 
    bcm_l3_nat_egress_stat_t *stat_arr, 
    uint32 *value_arr);

/* Set 64-bit counter value for multiple egress nat statistic types. */
extern int bcm_l3_nat_egress_stat_multi_set(
    int unit, 
    bcm_l3_nat_egress_t *info, 
    int nstat, 
    bcm_l3_nat_egress_stat_t *stat_arr, 
    uint64 *value_arr);

/* 
 * Set lower 32-bit counter value for multiple egress nat statistic
 * types.
 */
extern int bcm_l3_nat_egress_stat_multi_set32(
    int unit, 
    bcm_l3_nat_egress_t *info, 
    int nstat, 
    bcm_l3_nat_egress_stat_t *stat_arr, 
    uint32 *value_arr);

/* Provide stat counter ids associated with given l3 Egress NAT */
extern int bcm_l3_nat_egress_stat_id_get(
    int unit, 
    bcm_l3_nat_egress_t *info, 
    bcm_l3_nat_egress_stat_t stat, 
    uint32 *stat_counter_id);

#endif /* BCM_HIDE_DISPATCHABLE */

/* bcm_l3_nat_ingress_traverse_cb */
typedef int (*bcm_l3_nat_ingress_traverse_cb)(
    int unit, 
    int index, 
    bcm_l3_nat_ingress_t *nat_info, 
    void *user_data);

/* Initialize a bcm_l3_nat_ingress_t structure. */
extern void bcm_l3_nat_ingress_t_init(
    bcm_l3_nat_ingress_t *nat_info);

#ifndef BCM_HIDE_DISPATCHABLE

/* 
 * Add an ingress NAT table entry. Depending on the flags settings an
 * entry is added to either the ingress DNAT pool table, DNAT session
 * table or SNAT session table.
 */
extern int bcm_l3_nat_ingress_add(
    int unit, 
    bcm_l3_nat_ingress_t *nat_info);

/* 
 * Delete an ingress NAT table entry. Depending on the flags settings an
 * entry is deleted from either the ingress DNAT pool table, DNAT session
 * table or SNAT session table.
 */
extern int bcm_l3_nat_ingress_delete(
    int unit, 
    bcm_l3_nat_ingress_t *nat_info);

/* 
 * Find an ingress NAT table entry. Depending on the flags settings an
 * entry is searched for in  either the ingress DNAT pool table, DNAT
 * session table or SNAT session table.
 */
extern int bcm_l3_nat_ingress_find(
    int unit, 
    bcm_l3_nat_ingress_t *nat_info);

/* 
 * Delete all entries in an ingress NAT table. Depending on the flags
 * settings entries are deleted from either the ingress DNAT pool table,
 * DNAT session table or SNAT session table.
 */
extern int bcm_l3_nat_ingress_delete_all(
    int unit, 
    bcm_l3_nat_ingress_t *nat_info);

/* Run aging on either DNAT session or SNAT session table. */
extern int bcm_l3_nat_ingress_age(
    int unit, 
    uint32 flags, 
    bcm_l3_nat_ingress_traverse_cb age_cb, 
    void *user_data);

/* 
 * Traverse through the ingress NAT table specified by flags and invoke a
 * user provided callback for each valid entry.
 */
extern int bcm_l3_nat_ingress_traverse(
    int unit, 
    uint32 flags, 
    uint32 start, 
    uint32 end, 
    bcm_l3_nat_ingress_traverse_cb cb, 
    void *user_data);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Requires BROADCOM_PREMIUM license */
#define BCM_L3_LARGE_NAT_EGRESS_SNAT        (1 << 0)   /* Entry is for SNAT. */
#define BCM_L3_LARGE_NAT_EGRESS_DNAT        (1 << 1)   /* Entry is for DNAT. */
#define BCM_L3_LARGE_NAT_EGRESS_NAPT        (1 << 2)   /* Entry is for NAPT. */
#define BCM_L3_LARGE_NAT_EGRESS_REPLACE     (1 << 3)   /* Replace existing
                                                          entry. */
#define BCM_L3_LARGE_NAT_EGRESS_MULTICAST   (1 << 4)   /* Multicast Entry for
                                                          Large Scale NAT. */
#define BCM_L3_LARGE_NAT_EGRESS_MACDA_UPDATE (1 << 5)   /* Update MACDA on
                                                          Multicast NAT. */
#define BCM_L3_LARGE_NAT_EGRESS_DNAPT_SNAT  (1 << 6)   /* Entry is for
                                                          DNAPT_SNAT. */

/* Requires BROADCOM_PREMIUM license */
typedef struct bcm_l3_large_nat_egress_s {
    uint32 flags; 
    bcm_ip_t sip_addr; 
    uint16 src_port; 
    bcm_ip_t dip_addr; 
    uint16 dst_port; 
    int intf_class_id; 
    uint32 nat_class_id; 
    int replication_id; 
} bcm_l3_large_nat_egress_t;

/* Requires BROADCOM_PREMIUM license */
typedef int (*bcm_l3_large_nat_egress_traverse_cb)(
    int unit, 
    bcm_l3_large_nat_egress_t *nat_info, 
    void *user_data);

/* Requires BROADCOM_PREMIUM license */
extern void bcm_l3_large_nat_egress_t_init(
    bcm_l3_large_nat_egress_t *nat_info);

#ifndef BCM_HIDE_DISPATCHABLE

/* Requires BROADCOM_PREMIUM license */
extern int bcm_l3_large_nat_egress_add(
    int unit, 
    bcm_l3_large_nat_egress_t *nat_info);

/* Requires BROADCOM_PREMIUM license */
extern int bcm_l3_large_nat_egress_delete(
    int unit, 
    bcm_l3_large_nat_egress_t *nat_info);

/* Requires BROADCOM_PREMIUM license */
extern int bcm_l3_large_nat_egress_get(
    int unit, 
    bcm_l3_large_nat_egress_t *nat_info);

/* Requires BROADCOM_PREMIUM license */
extern int bcm_l3_large_nat_egress_traverse(
    int unit, 
    bcm_l3_large_nat_egress_traverse_cb cb, 
    void *user_data);

#endif /* defined(INCLUDE_L3) */

#endif /* BCM_HIDE_DISPATCHABLE */

#endif /* __BCM_NAT_H__ */

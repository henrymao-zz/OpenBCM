/** \file algo/swstate/auto_generated/access/algo_bfd_access.h
 *
 * sw state functions declarations
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 *
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifndef __ALGO_BFD_ACCESS_H__
#define __ALGO_BFD_ACCESS_H__

#include <bcm_int/dnx/algo/swstate/auto_generated/types/algo_bfd_types.h>
#include <bcm_int/dnx/algo/bfd/algo_bfd.h>
#include <bcm_int/dnx/algo/oamp/algo_oamp_v1.h>
#include <bcm_int/dnx/algo/template_mngr/template_mngr.h>
#include <bcm_int/dnx/algo/template_mngr/template_mngr_internal.h>
/*
 * TYPEDEFs
 */

/**
 * implemented by: algo_bfd_db_is_init
 */
typedef int (*algo_bfd_db_is_init_cb)(
    int unit, uint8 *is_init);

/**
 * implemented by: algo_bfd_db_init
 */
typedef int (*algo_bfd_db_init_cb)(
    int unit);

/**
 * implemented by: algo_bfd_db_bfd_oama_action_set
 */
typedef int (*algo_bfd_db_bfd_oama_action_set_cb)(
    int unit, dnx_algo_template_t bfd_oama_action);

/**
 * implemented by: algo_bfd_db_bfd_oama_action_get
 */
typedef int (*algo_bfd_db_bfd_oama_action_get_cb)(
    int unit, dnx_algo_template_t *bfd_oama_action);

/**
 * implemented by: algo_bfd_db_bfd_oama_action_create
 */
typedef int (*algo_bfd_db_bfd_oama_action_create_cb)(
    int unit, dnx_algo_template_create_data_t * data, void *extra_arguments);

/**
 * implemented by: algo_bfd_db_bfd_oama_action_allocate_single
 */
typedef int (*algo_bfd_db_bfd_oama_action_allocate_single_cb)(
    int unit, uint32 flags, dnx_bfd_mep_profile_t *profile_data, void *extra_arguments, int *profile, uint8 *first_reference);

/**
 * implemented by: algo_bfd_db_bfd_oama_action_free_single
 */
typedef int (*algo_bfd_db_bfd_oama_action_free_single_cb)(
    int unit, int profile, uint8 *last_reference);

/**
 * implemented by: algo_bfd_db_bfd_oama_action_profile_data_get
 */
typedef int (*algo_bfd_db_bfd_oama_action_profile_data_get_cb)(
    int unit, int profile, int *ref_count, dnx_bfd_mep_profile_t *profile_data);

/**
 * implemented by: algo_bfd_db_bfd_oamb_action_set
 */
typedef int (*algo_bfd_db_bfd_oamb_action_set_cb)(
    int unit, dnx_algo_template_t bfd_oamb_action);

/**
 * implemented by: algo_bfd_db_bfd_oamb_action_get
 */
typedef int (*algo_bfd_db_bfd_oamb_action_get_cb)(
    int unit, dnx_algo_template_t *bfd_oamb_action);

/**
 * implemented by: algo_bfd_db_bfd_oamb_action_create
 */
typedef int (*algo_bfd_db_bfd_oamb_action_create_cb)(
    int unit, dnx_algo_template_create_data_t * data, void *extra_arguments);

/**
 * implemented by: algo_bfd_db_bfd_oamb_action_allocate_single
 */
typedef int (*algo_bfd_db_bfd_oamb_action_allocate_single_cb)(
    int unit, uint32 flags, dnx_bfd_mep_profile_t *profile_data, void *extra_arguments, int *profile, uint8 *first_reference);

/**
 * implemented by: algo_bfd_db_bfd_oamb_action_free_single
 */
typedef int (*algo_bfd_db_bfd_oamb_action_free_single_cb)(
    int unit, int profile, uint8 *last_reference);

/**
 * implemented by: algo_bfd_db_bfd_oamb_action_profile_data_get
 */
typedef int (*algo_bfd_db_bfd_oamb_action_profile_data_get_cb)(
    int unit, int profile, int *ref_count, dnx_bfd_mep_profile_t *profile_data);

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tos_ttl_set
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tos_ttl_set_cb)(
    int unit, dnx_algo_template_t bfd_oamp_v1_tos_ttl);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tos_ttl_get
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tos_ttl_get_cb)(
    int unit, dnx_algo_template_t *bfd_oamp_v1_tos_ttl);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tos_ttl_create
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tos_ttl_create_cb)(
    int unit, dnx_algo_template_create_data_t * data, void *extra_arguments);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tos_ttl_allocate_single
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tos_ttl_allocate_single_cb)(
    int unit, uint32 flags, dnx_bfd_tos_ttl_t *profile_data, void *extra_arguments, int *profile, uint8 *first_reference);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tos_ttl_free_single
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tos_ttl_free_single_cb)(
    int unit, int profile, uint8 *last_reference);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tos_ttl_profile_data_get
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tos_ttl_profile_data_get_cb)(
    int unit, int profile, int *ref_count, dnx_bfd_tos_ttl_t *profile_data);
#endif /* BCM_DNX2_SUPPORT*/ 

/**
 * implemented by: algo_bfd_db_bfd_your_discr_range_set
 */
typedef int (*algo_bfd_db_bfd_your_discr_range_set_cb)(
    int unit, dnx_algo_template_t bfd_your_discr_range);

/**
 * implemented by: algo_bfd_db_bfd_your_discr_range_get
 */
typedef int (*algo_bfd_db_bfd_your_discr_range_get_cb)(
    int unit, dnx_algo_template_t *bfd_your_discr_range);

/**
 * implemented by: algo_bfd_db_bfd_your_discr_range_create
 */
typedef int (*algo_bfd_db_bfd_your_discr_range_create_cb)(
    int unit, dnx_algo_template_create_data_t * data, void *extra_arguments);

/**
 * implemented by: algo_bfd_db_bfd_your_discr_range_allocate_single
 */
typedef int (*algo_bfd_db_bfd_your_discr_range_allocate_single_cb)(
    int unit, uint32 flags, dnx_bfd_discr_range_t *profile_data, void *extra_arguments, int *profile, uint8 *first_reference);

/**
 * implemented by: algo_bfd_db_bfd_your_discr_range_free_single
 */
typedef int (*algo_bfd_db_bfd_your_discr_range_free_single_cb)(
    int unit, int profile, uint8 *last_reference);

/**
 * implemented by: algo_bfd_db_bfd_your_discr_range_profile_data_get
 */
typedef int (*algo_bfd_db_bfd_your_discr_range_profile_data_get_cb)(
    int unit, int profile, int *ref_count, dnx_bfd_discr_range_t *profile_data);

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tx_rate_set
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tx_rate_set_cb)(
    int unit, dnx_algo_template_t bfd_oamp_v1_tx_rate);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tx_rate_get
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tx_rate_get_cb)(
    int unit, dnx_algo_template_t *bfd_oamp_v1_tx_rate);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tx_rate_create
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tx_rate_create_cb)(
    int unit, dnx_algo_template_create_data_t * data, void *extra_arguments);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tx_rate_allocate_single
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tx_rate_allocate_single_cb)(
    int unit, uint32 flags, dnx_bfd_tx_period_t *profile_data, void *extra_arguments, int *profile, uint8 *first_reference);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tx_rate_free_single
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tx_rate_free_single_cb)(
    int unit, int profile, uint8 *last_reference);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tx_rate_replace_data
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tx_rate_replace_data_cb)(
    int unit, int profile,  const dnx_bfd_tx_period_t *new_profile_data);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tx_rate_profile_data_get
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tx_rate_profile_data_get_cb)(
    int unit, int profile, int *ref_count, dnx_bfd_tx_period_t *profile_data);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_req_interval_set
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_req_interval_set_cb)(
    int unit, dnx_algo_template_t bfd_oamp_v1_req_interval);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_req_interval_get
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_req_interval_get_cb)(
    int unit, dnx_algo_template_t *bfd_oamp_v1_req_interval);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_req_interval_create
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_req_interval_create_cb)(
    int unit, dnx_algo_template_create_data_t * data, void *extra_arguments);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_req_interval_allocate_single
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_req_interval_allocate_single_cb)(
    int unit, uint32 flags, uint32 *profile_data, void *extra_arguments, int *profile, uint8 *first_reference);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_req_interval_free_single
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_req_interval_free_single_cb)(
    int unit, int profile, uint8 *last_reference);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_req_interval_profile_data_get
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_req_interval_profile_data_get_cb)(
    int unit, int profile, int *ref_count, uint32 *profile_data);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_my_discr_range_start_set
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_my_discr_range_start_set_cb)(
    int unit, dnx_algo_template_t bfd_oamp_v1_my_discr_range_start);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_my_discr_range_start_get
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_my_discr_range_start_get_cb)(
    int unit, dnx_algo_template_t *bfd_oamp_v1_my_discr_range_start);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_my_discr_range_start_create
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_my_discr_range_start_create_cb)(
    int unit, dnx_algo_template_create_data_t * data, void *extra_arguments);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_my_discr_range_start_allocate_single
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_my_discr_range_start_allocate_single_cb)(
    int unit, uint32 flags, uint32 *profile_data, void *extra_arguments, int *profile, uint8 *first_reference);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_my_discr_range_start_free_single
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_my_discr_range_start_free_single_cb)(
    int unit, int profile, uint8 *last_reference);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_my_discr_range_start_profile_data_get
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_my_discr_range_start_profile_data_get_cb)(
    int unit, int profile, int *ref_count, uint32 *profile_data);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_set
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_set_cb)(
    int unit, dnx_algo_template_t bfd_oamp_v1_ipv4_src_addr);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_get
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_get_cb)(
    int unit, dnx_algo_template_t *bfd_oamp_v1_ipv4_src_addr);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_create
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_create_cb)(
    int unit, dnx_algo_template_create_data_t * data, void *extra_arguments);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_allocate_single
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_allocate_single_cb)(
    int unit, uint32 flags, uint32 *profile_data, void *extra_arguments, int *profile, uint8 *first_reference);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_free_single
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_free_single_cb)(
    int unit, int profile, uint8 *last_reference);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_profile_data_get
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_profile_data_get_cb)(
    int unit, int profile, int *ref_count, uint32 *profile_data);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_udp_sport_set
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_udp_sport_set_cb)(
    int unit, dnx_algo_template_t bfd_oamp_v1_udp_sport);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_udp_sport_get
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_udp_sport_get_cb)(
    int unit, dnx_algo_template_t *bfd_oamp_v1_udp_sport);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_udp_sport_create
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_udp_sport_create_cb)(
    int unit, dnx_algo_template_create_data_t * data, void *extra_arguments);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_udp_sport_allocate_single
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_udp_sport_allocate_single_cb)(
    int unit, uint32 flags, uint16 *profile_data, void *extra_arguments, int *profile, uint8 *first_reference);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_udp_sport_free_single
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_udp_sport_free_single_cb)(
    int unit, int profile, uint8 *last_reference);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_udp_sport_profile_data_get
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_udp_sport_profile_data_get_cb)(
    int unit, int profile, int *ref_count, uint16 *profile_data);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_mpls_sport_set
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_mpls_sport_set_cb)(
    int unit, dnx_algo_template_t bfd_oamp_v1_mpls_sport);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_mpls_sport_get
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_mpls_sport_get_cb)(
    int unit, dnx_algo_template_t *bfd_oamp_v1_mpls_sport);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_mpls_sport_create
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_mpls_sport_create_cb)(
    int unit, dnx_algo_template_create_data_t * data, void *extra_arguments);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_mpls_sport_allocate_single
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_mpls_sport_allocate_single_cb)(
    int unit, uint32 flags, uint16 *profile_data, void *extra_arguments, int *profile, uint8 *first_reference);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_mpls_sport_free_single
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_mpls_sport_free_single_cb)(
    int unit, int profile, uint8 *last_reference);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_mpls_sport_profile_data_get
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_mpls_sport_profile_data_get_cb)(
    int unit, int profile, int *ref_count, uint16 *profile_data);
#endif /* BCM_DNX2_SUPPORT*/ 

/**
 * implemented by: algo_bfd_db_bfd_local_min_echo_set
 */
typedef int (*algo_bfd_db_bfd_local_min_echo_set_cb)(
    int unit, dnx_algo_template_t bfd_local_min_echo);

/**
 * implemented by: algo_bfd_db_bfd_local_min_echo_get
 */
typedef int (*algo_bfd_db_bfd_local_min_echo_get_cb)(
    int unit, dnx_algo_template_t *bfd_local_min_echo);

/**
 * implemented by: algo_bfd_db_bfd_local_min_echo_create
 */
typedef int (*algo_bfd_db_bfd_local_min_echo_create_cb)(
    int unit, dnx_algo_template_create_data_t * data, void *extra_arguments);

/**
 * implemented by: algo_bfd_db_bfd_local_min_echo_allocate_single
 */
typedef int (*algo_bfd_db_bfd_local_min_echo_allocate_single_cb)(
    int unit, uint32 flags, uint32 *profile_data, void *extra_arguments, int *profile, uint8 *first_reference);

/**
 * implemented by: algo_bfd_db_bfd_local_min_echo_free_single
 */
typedef int (*algo_bfd_db_bfd_local_min_echo_free_single_cb)(
    int unit, int profile, uint8 *last_reference);

/**
 * implemented by: algo_bfd_db_bfd_local_min_echo_replace_data
 */
typedef int (*algo_bfd_db_bfd_local_min_echo_replace_data_cb)(
    int unit, int profile,  const uint32 *new_profile_data);

/**
 * implemented by: algo_bfd_db_bfd_local_min_echo_profile_data_get
 */
typedef int (*algo_bfd_db_bfd_local_min_echo_profile_data_get_cb)(
    int unit, int profile, int *ref_count, uint32 *profile_data);

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tx_period_cluster_set
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tx_period_cluster_set_cb)(
    int unit, dnx_algo_template_t bfd_oamp_v1_tx_period_cluster);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tx_period_cluster_get
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tx_period_cluster_get_cb)(
    int unit, dnx_algo_template_t *bfd_oamp_v1_tx_period_cluster);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tx_period_cluster_create
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tx_period_cluster_create_cb)(
    int unit, dnx_algo_template_create_data_t * data, void *extra_arguments);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tx_period_cluster_allocate_single
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tx_period_cluster_allocate_single_cb)(
    int unit, uint32 flags, uint8 *profile_data, void *extra_arguments, int *profile, uint8 *first_reference);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tx_period_cluster_free_single
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tx_period_cluster_free_single_cb)(
    int unit, int profile, uint8 *last_reference);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tx_period_cluster_replace_data
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tx_period_cluster_replace_data_cb)(
    int unit, int profile,  const uint8 *new_profile_data);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_tx_period_cluster_profile_data_get
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_tx_period_cluster_profile_data_get_cb)(
    int unit, int profile, int *ref_count, uint8 *profile_data);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_single_hop_tos_set
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_single_hop_tos_set_cb)(
    int unit, dnx_algo_template_t bfd_oamp_v1_single_hop_tos);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_single_hop_tos_get
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_single_hop_tos_get_cb)(
    int unit, dnx_algo_template_t *bfd_oamp_v1_single_hop_tos);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_single_hop_tos_create
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_single_hop_tos_create_cb)(
    int unit, dnx_algo_template_create_data_t * data, void *extra_arguments);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_single_hop_tos_allocate_single
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_single_hop_tos_allocate_single_cb)(
    int unit, uint32 flags, uint8 *profile_data, void *extra_arguments, int *profile, uint8 *first_reference);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_single_hop_tos_free_single
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_single_hop_tos_free_single_cb)(
    int unit, int profile, uint8 *last_reference);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_single_hop_tos_replace_data
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_single_hop_tos_replace_data_cb)(
    int unit, int profile,  const uint8 *new_profile_data);
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * implemented by: algo_bfd_db_bfd_oamp_v1_single_hop_tos_profile_data_get
 */
typedef int (*algo_bfd_db_bfd_oamp_v1_single_hop_tos_profile_data_get_cb)(
    int unit, int profile, int *ref_count, uint8 *profile_data);
#endif /* BCM_DNX2_SUPPORT*/ 

/**
 * implemented by: algo_bfd_db_bfd_seamless_udp_sport_set
 */
typedef int (*algo_bfd_db_bfd_seamless_udp_sport_set_cb)(
    int unit, dnx_algo_template_t bfd_seamless_udp_sport);

/**
 * implemented by: algo_bfd_db_bfd_seamless_udp_sport_get
 */
typedef int (*algo_bfd_db_bfd_seamless_udp_sport_get_cb)(
    int unit, dnx_algo_template_t *bfd_seamless_udp_sport);

/**
 * implemented by: algo_bfd_db_bfd_seamless_udp_sport_create
 */
typedef int (*algo_bfd_db_bfd_seamless_udp_sport_create_cb)(
    int unit, dnx_algo_template_create_data_t * data, void *extra_arguments);

/**
 * implemented by: algo_bfd_db_bfd_seamless_udp_sport_allocate_single
 */
typedef int (*algo_bfd_db_bfd_seamless_udp_sport_allocate_single_cb)(
    int unit, uint32 flags, uint16 *profile_data, void *extra_arguments, int *profile, uint8 *first_reference);

/**
 * implemented by: algo_bfd_db_bfd_seamless_udp_sport_free_single
 */
typedef int (*algo_bfd_db_bfd_seamless_udp_sport_free_single_cb)(
    int unit, int profile, uint8 *last_reference);

/**
 * implemented by: algo_bfd_db_bfd_seamless_udp_sport_profile_data_get
 */
typedef int (*algo_bfd_db_bfd_seamless_udp_sport_profile_data_get_cb)(
    int unit, int profile, int *ref_count, uint16 *profile_data);

/**
 * implemented by: algo_bfd_db_bfd_server_trap_codes_set
 */
typedef int (*algo_bfd_db_bfd_server_trap_codes_set_cb)(
    int unit, dnx_algo_template_t bfd_server_trap_codes);

/**
 * implemented by: algo_bfd_db_bfd_server_trap_codes_get
 */
typedef int (*algo_bfd_db_bfd_server_trap_codes_get_cb)(
    int unit, dnx_algo_template_t *bfd_server_trap_codes);

/**
 * implemented by: algo_bfd_db_bfd_server_trap_codes_create
 */
typedef int (*algo_bfd_db_bfd_server_trap_codes_create_cb)(
    int unit, dnx_algo_template_create_data_t * data, void *extra_arguments);

/**
 * implemented by: algo_bfd_db_bfd_server_trap_codes_allocate_single
 */
typedef int (*algo_bfd_db_bfd_server_trap_codes_allocate_single_cb)(
    int unit, uint32 flags, uint16 *profile_data, void *extra_arguments, int *profile, uint8 *first_reference);

/**
 * implemented by: algo_bfd_db_bfd_server_trap_codes_free_single
 */
typedef int (*algo_bfd_db_bfd_server_trap_codes_free_single_cb)(
    int unit, int profile, uint8 *last_reference);

/**
 * implemented by: algo_bfd_db_bfd_server_trap_codes_profile_data_get
 */
typedef int (*algo_bfd_db_bfd_server_trap_codes_profile_data_get_cb)(
    int unit, int profile, int *ref_count, uint16 *profile_data);

/**
 * implemented by: algo_bfd_db_bfd_dip_set
 */
typedef int (*algo_bfd_db_bfd_dip_set_cb)(
    int unit, dnx_algo_template_t bfd_dip);

/**
 * implemented by: algo_bfd_db_bfd_dip_get
 */
typedef int (*algo_bfd_db_bfd_dip_get_cb)(
    int unit, dnx_algo_template_t *bfd_dip);

/**
 * implemented by: algo_bfd_db_bfd_dip_create
 */
typedef int (*algo_bfd_db_bfd_dip_create_cb)(
    int unit, dnx_algo_template_create_data_t * data, void *extra_arguments);

/**
 * implemented by: algo_bfd_db_bfd_dip_allocate_single
 */
typedef int (*algo_bfd_db_bfd_dip_allocate_single_cb)(
    int unit, uint32 flags, uint8 *profile_data, void *extra_arguments, int *profile, uint8 *first_reference);

/**
 * implemented by: algo_bfd_db_bfd_dip_free_single
 */
typedef int (*algo_bfd_db_bfd_dip_free_single_cb)(
    int unit, int profile, uint8 *last_reference);

/**
 * implemented by: algo_bfd_db_bfd_dip_profile_data_get
 */
typedef int (*algo_bfd_db_bfd_dip_profile_data_get_cb)(
    int unit, int profile, int *ref_count, uint8 *profile_data);

/**
 * implemented by: algo_bfd_db_bfd_server_device_index_set
 */
typedef int (*algo_bfd_db_bfd_server_device_index_set_cb)(
    int unit, dnx_algo_template_t bfd_server_device_index);

/**
 * implemented by: algo_bfd_db_bfd_server_device_index_get
 */
typedef int (*algo_bfd_db_bfd_server_device_index_get_cb)(
    int unit, dnx_algo_template_t *bfd_server_device_index);

/**
 * implemented by: algo_bfd_db_bfd_server_device_index_create
 */
typedef int (*algo_bfd_db_bfd_server_device_index_create_cb)(
    int unit, dnx_algo_template_create_data_t * data, void *extra_arguments);

/**
 * implemented by: algo_bfd_db_bfd_server_device_index_allocate_single
 */
typedef int (*algo_bfd_db_bfd_server_device_index_allocate_single_cb)(
    int unit, uint32 flags, uint8 *profile_data, void *extra_arguments, int *profile, uint8 *first_reference);

/**
 * implemented by: algo_bfd_db_bfd_server_device_index_free_single
 */
typedef int (*algo_bfd_db_bfd_server_device_index_free_single_cb)(
    int unit, int profile, uint8 *last_reference);

/**
 * implemented by: algo_bfd_db_bfd_server_device_index_profile_data_get
 */
typedef int (*algo_bfd_db_bfd_server_device_index_profile_data_get_cb)(
    int unit, int profile, int *ref_count, uint8 *profile_data);

/*
 * STRUCTs
 */

/**
 * This structure holds the access functions for the variable bfd_oama_action
 */
typedef struct {
    algo_bfd_db_bfd_oama_action_set_cb set;
    algo_bfd_db_bfd_oama_action_get_cb get;
    algo_bfd_db_bfd_oama_action_create_cb create;
    algo_bfd_db_bfd_oama_action_allocate_single_cb allocate_single;
    algo_bfd_db_bfd_oama_action_free_single_cb free_single;
    algo_bfd_db_bfd_oama_action_profile_data_get_cb profile_data_get;
} algo_bfd_db_bfd_oama_action_cbs;

/**
 * This structure holds the access functions for the variable bfd_oamb_action
 */
typedef struct {
    algo_bfd_db_bfd_oamb_action_set_cb set;
    algo_bfd_db_bfd_oamb_action_get_cb get;
    algo_bfd_db_bfd_oamb_action_create_cb create;
    algo_bfd_db_bfd_oamb_action_allocate_single_cb allocate_single;
    algo_bfd_db_bfd_oamb_action_free_single_cb free_single;
    algo_bfd_db_bfd_oamb_action_profile_data_get_cb profile_data_get;
} algo_bfd_db_bfd_oamb_action_cbs;

#ifdef BCM_DNX2_SUPPORT
/**
 * This structure holds the access functions for the variable bfd_oamp_v1_tos_ttl
 */
typedef struct {
    algo_bfd_db_bfd_oamp_v1_tos_ttl_set_cb set;
    algo_bfd_db_bfd_oamp_v1_tos_ttl_get_cb get;
    algo_bfd_db_bfd_oamp_v1_tos_ttl_create_cb create;
    algo_bfd_db_bfd_oamp_v1_tos_ttl_allocate_single_cb allocate_single;
    algo_bfd_db_bfd_oamp_v1_tos_ttl_free_single_cb free_single;
    algo_bfd_db_bfd_oamp_v1_tos_ttl_profile_data_get_cb profile_data_get;
} algo_bfd_db_bfd_oamp_v1_tos_ttl_cbs;
#endif /* BCM_DNX2_SUPPORT*/ 

/**
 * This structure holds the access functions for the variable bfd_your_discr_range
 */
typedef struct {
    algo_bfd_db_bfd_your_discr_range_set_cb set;
    algo_bfd_db_bfd_your_discr_range_get_cb get;
    algo_bfd_db_bfd_your_discr_range_create_cb create;
    algo_bfd_db_bfd_your_discr_range_allocate_single_cb allocate_single;
    algo_bfd_db_bfd_your_discr_range_free_single_cb free_single;
    algo_bfd_db_bfd_your_discr_range_profile_data_get_cb profile_data_get;
} algo_bfd_db_bfd_your_discr_range_cbs;

#ifdef BCM_DNX2_SUPPORT
/**
 * This structure holds the access functions for the variable bfd_oamp_v1_tx_rate
 */
typedef struct {
    algo_bfd_db_bfd_oamp_v1_tx_rate_set_cb set;
    algo_bfd_db_bfd_oamp_v1_tx_rate_get_cb get;
    algo_bfd_db_bfd_oamp_v1_tx_rate_create_cb create;
    algo_bfd_db_bfd_oamp_v1_tx_rate_allocate_single_cb allocate_single;
    algo_bfd_db_bfd_oamp_v1_tx_rate_free_single_cb free_single;
    algo_bfd_db_bfd_oamp_v1_tx_rate_replace_data_cb replace_data;
    algo_bfd_db_bfd_oamp_v1_tx_rate_profile_data_get_cb profile_data_get;
} algo_bfd_db_bfd_oamp_v1_tx_rate_cbs;
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * This structure holds the access functions for the variable bfd_oamp_v1_req_interval
 */
typedef struct {
    algo_bfd_db_bfd_oamp_v1_req_interval_set_cb set;
    algo_bfd_db_bfd_oamp_v1_req_interval_get_cb get;
    algo_bfd_db_bfd_oamp_v1_req_interval_create_cb create;
    algo_bfd_db_bfd_oamp_v1_req_interval_allocate_single_cb allocate_single;
    algo_bfd_db_bfd_oamp_v1_req_interval_free_single_cb free_single;
    algo_bfd_db_bfd_oamp_v1_req_interval_profile_data_get_cb profile_data_get;
} algo_bfd_db_bfd_oamp_v1_req_interval_cbs;
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * This structure holds the access functions for the variable bfd_oamp_v1_my_discr_range_start
 */
typedef struct {
    algo_bfd_db_bfd_oamp_v1_my_discr_range_start_set_cb set;
    algo_bfd_db_bfd_oamp_v1_my_discr_range_start_get_cb get;
    algo_bfd_db_bfd_oamp_v1_my_discr_range_start_create_cb create;
    algo_bfd_db_bfd_oamp_v1_my_discr_range_start_allocate_single_cb allocate_single;
    algo_bfd_db_bfd_oamp_v1_my_discr_range_start_free_single_cb free_single;
    algo_bfd_db_bfd_oamp_v1_my_discr_range_start_profile_data_get_cb profile_data_get;
} algo_bfd_db_bfd_oamp_v1_my_discr_range_start_cbs;
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * This structure holds the access functions for the variable bfd_oamp_v1_ipv4_src_addr
 */
typedef struct {
    algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_set_cb set;
    algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_get_cb get;
    algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_create_cb create;
    algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_allocate_single_cb allocate_single;
    algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_free_single_cb free_single;
    algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_profile_data_get_cb profile_data_get;
} algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_cbs;
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * This structure holds the access functions for the variable bfd_oamp_v1_udp_sport
 */
typedef struct {
    algo_bfd_db_bfd_oamp_v1_udp_sport_set_cb set;
    algo_bfd_db_bfd_oamp_v1_udp_sport_get_cb get;
    algo_bfd_db_bfd_oamp_v1_udp_sport_create_cb create;
    algo_bfd_db_bfd_oamp_v1_udp_sport_allocate_single_cb allocate_single;
    algo_bfd_db_bfd_oamp_v1_udp_sport_free_single_cb free_single;
    algo_bfd_db_bfd_oamp_v1_udp_sport_profile_data_get_cb profile_data_get;
} algo_bfd_db_bfd_oamp_v1_udp_sport_cbs;
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * This structure holds the access functions for the variable bfd_oamp_v1_mpls_sport
 */
typedef struct {
    algo_bfd_db_bfd_oamp_v1_mpls_sport_set_cb set;
    algo_bfd_db_bfd_oamp_v1_mpls_sport_get_cb get;
    algo_bfd_db_bfd_oamp_v1_mpls_sport_create_cb create;
    algo_bfd_db_bfd_oamp_v1_mpls_sport_allocate_single_cb allocate_single;
    algo_bfd_db_bfd_oamp_v1_mpls_sport_free_single_cb free_single;
    algo_bfd_db_bfd_oamp_v1_mpls_sport_profile_data_get_cb profile_data_get;
} algo_bfd_db_bfd_oamp_v1_mpls_sport_cbs;
#endif /* BCM_DNX2_SUPPORT*/ 

/**
 * This structure holds the access functions for the variable bfd_local_min_echo
 */
typedef struct {
    algo_bfd_db_bfd_local_min_echo_set_cb set;
    algo_bfd_db_bfd_local_min_echo_get_cb get;
    algo_bfd_db_bfd_local_min_echo_create_cb create;
    algo_bfd_db_bfd_local_min_echo_allocate_single_cb allocate_single;
    algo_bfd_db_bfd_local_min_echo_free_single_cb free_single;
    algo_bfd_db_bfd_local_min_echo_replace_data_cb replace_data;
    algo_bfd_db_bfd_local_min_echo_profile_data_get_cb profile_data_get;
} algo_bfd_db_bfd_local_min_echo_cbs;

#ifdef BCM_DNX2_SUPPORT
/**
 * This structure holds the access functions for the variable bfd_oamp_v1_tx_period_cluster
 */
typedef struct {
    algo_bfd_db_bfd_oamp_v1_tx_period_cluster_set_cb set;
    algo_bfd_db_bfd_oamp_v1_tx_period_cluster_get_cb get;
    algo_bfd_db_bfd_oamp_v1_tx_period_cluster_create_cb create;
    algo_bfd_db_bfd_oamp_v1_tx_period_cluster_allocate_single_cb allocate_single;
    algo_bfd_db_bfd_oamp_v1_tx_period_cluster_free_single_cb free_single;
    algo_bfd_db_bfd_oamp_v1_tx_period_cluster_replace_data_cb replace_data;
    algo_bfd_db_bfd_oamp_v1_tx_period_cluster_profile_data_get_cb profile_data_get;
} algo_bfd_db_bfd_oamp_v1_tx_period_cluster_cbs;
#endif /* BCM_DNX2_SUPPORT*/ 

#ifdef BCM_DNX2_SUPPORT
/**
 * This structure holds the access functions for the variable bfd_oamp_v1_single_hop_tos
 */
typedef struct {
    algo_bfd_db_bfd_oamp_v1_single_hop_tos_set_cb set;
    algo_bfd_db_bfd_oamp_v1_single_hop_tos_get_cb get;
    algo_bfd_db_bfd_oamp_v1_single_hop_tos_create_cb create;
    algo_bfd_db_bfd_oamp_v1_single_hop_tos_allocate_single_cb allocate_single;
    algo_bfd_db_bfd_oamp_v1_single_hop_tos_free_single_cb free_single;
    algo_bfd_db_bfd_oamp_v1_single_hop_tos_replace_data_cb replace_data;
    algo_bfd_db_bfd_oamp_v1_single_hop_tos_profile_data_get_cb profile_data_get;
} algo_bfd_db_bfd_oamp_v1_single_hop_tos_cbs;
#endif /* BCM_DNX2_SUPPORT*/ 

/**
 * This structure holds the access functions for the variable bfd_seamless_udp_sport
 */
typedef struct {
    algo_bfd_db_bfd_seamless_udp_sport_set_cb set;
    algo_bfd_db_bfd_seamless_udp_sport_get_cb get;
    algo_bfd_db_bfd_seamless_udp_sport_create_cb create;
    algo_bfd_db_bfd_seamless_udp_sport_allocate_single_cb allocate_single;
    algo_bfd_db_bfd_seamless_udp_sport_free_single_cb free_single;
    algo_bfd_db_bfd_seamless_udp_sport_profile_data_get_cb profile_data_get;
} algo_bfd_db_bfd_seamless_udp_sport_cbs;

/**
 * This structure holds the access functions for the variable bfd_server_trap_codes
 */
typedef struct {
    algo_bfd_db_bfd_server_trap_codes_set_cb set;
    algo_bfd_db_bfd_server_trap_codes_get_cb get;
    algo_bfd_db_bfd_server_trap_codes_create_cb create;
    algo_bfd_db_bfd_server_trap_codes_allocate_single_cb allocate_single;
    algo_bfd_db_bfd_server_trap_codes_free_single_cb free_single;
    algo_bfd_db_bfd_server_trap_codes_profile_data_get_cb profile_data_get;
} algo_bfd_db_bfd_server_trap_codes_cbs;

/**
 * This structure holds the access functions for the variable bfd_dip
 */
typedef struct {
    algo_bfd_db_bfd_dip_set_cb set;
    algo_bfd_db_bfd_dip_get_cb get;
    algo_bfd_db_bfd_dip_create_cb create;
    algo_bfd_db_bfd_dip_allocate_single_cb allocate_single;
    algo_bfd_db_bfd_dip_free_single_cb free_single;
    algo_bfd_db_bfd_dip_profile_data_get_cb profile_data_get;
} algo_bfd_db_bfd_dip_cbs;

/**
 * This structure holds the access functions for the variable bfd_server_device_index
 */
typedef struct {
    algo_bfd_db_bfd_server_device_index_set_cb set;
    algo_bfd_db_bfd_server_device_index_get_cb get;
    algo_bfd_db_bfd_server_device_index_create_cb create;
    algo_bfd_db_bfd_server_device_index_allocate_single_cb allocate_single;
    algo_bfd_db_bfd_server_device_index_free_single_cb free_single;
    algo_bfd_db_bfd_server_device_index_profile_data_get_cb profile_data_get;
} algo_bfd_db_bfd_server_device_index_cbs;

/**
 * This structure holds the access functions for the variable algo_bfd_sw_state_t
 */
typedef struct {
    algo_bfd_db_is_init_cb is_init;
    algo_bfd_db_init_cb init;
    /**
     * Access struct for bfd_oama_action
     */
    algo_bfd_db_bfd_oama_action_cbs bfd_oama_action;
    /**
     * Access struct for bfd_oamb_action
     */
    algo_bfd_db_bfd_oamb_action_cbs bfd_oamb_action;
#ifdef BCM_DNX2_SUPPORT
    /**
     * Access struct for bfd_oamp_v1_tos_ttl
     */
    algo_bfd_db_bfd_oamp_v1_tos_ttl_cbs bfd_oamp_v1_tos_ttl;
#endif /* BCM_DNX2_SUPPORT*/ 
    /**
     * Access struct for bfd_your_discr_range
     */
    algo_bfd_db_bfd_your_discr_range_cbs bfd_your_discr_range;
#ifdef BCM_DNX2_SUPPORT
    /**
     * Access struct for bfd_oamp_v1_tx_rate
     */
    algo_bfd_db_bfd_oamp_v1_tx_rate_cbs bfd_oamp_v1_tx_rate;
#endif /* BCM_DNX2_SUPPORT*/ 
#ifdef BCM_DNX2_SUPPORT
    /**
     * Access struct for bfd_oamp_v1_req_interval
     */
    algo_bfd_db_bfd_oamp_v1_req_interval_cbs bfd_oamp_v1_req_interval;
#endif /* BCM_DNX2_SUPPORT*/ 
#ifdef BCM_DNX2_SUPPORT
    /**
     * Access struct for bfd_oamp_v1_my_discr_range_start
     */
    algo_bfd_db_bfd_oamp_v1_my_discr_range_start_cbs bfd_oamp_v1_my_discr_range_start;
#endif /* BCM_DNX2_SUPPORT*/ 
#ifdef BCM_DNX2_SUPPORT
    /**
     * Access struct for bfd_oamp_v1_ipv4_src_addr
     */
    algo_bfd_db_bfd_oamp_v1_ipv4_src_addr_cbs bfd_oamp_v1_ipv4_src_addr;
#endif /* BCM_DNX2_SUPPORT*/ 
#ifdef BCM_DNX2_SUPPORT
    /**
     * Access struct for bfd_oamp_v1_udp_sport
     */
    algo_bfd_db_bfd_oamp_v1_udp_sport_cbs bfd_oamp_v1_udp_sport;
#endif /* BCM_DNX2_SUPPORT*/ 
#ifdef BCM_DNX2_SUPPORT
    /**
     * Access struct for bfd_oamp_v1_mpls_sport
     */
    algo_bfd_db_bfd_oamp_v1_mpls_sport_cbs bfd_oamp_v1_mpls_sport;
#endif /* BCM_DNX2_SUPPORT*/ 
    /**
     * Access struct for bfd_local_min_echo
     */
    algo_bfd_db_bfd_local_min_echo_cbs bfd_local_min_echo;
#ifdef BCM_DNX2_SUPPORT
    /**
     * Access struct for bfd_oamp_v1_tx_period_cluster
     */
    algo_bfd_db_bfd_oamp_v1_tx_period_cluster_cbs bfd_oamp_v1_tx_period_cluster;
#endif /* BCM_DNX2_SUPPORT*/ 
#ifdef BCM_DNX2_SUPPORT
    /**
     * Access struct for bfd_oamp_v1_single_hop_tos
     */
    algo_bfd_db_bfd_oamp_v1_single_hop_tos_cbs bfd_oamp_v1_single_hop_tos;
#endif /* BCM_DNX2_SUPPORT*/ 
    /**
     * Access struct for bfd_seamless_udp_sport
     */
    algo_bfd_db_bfd_seamless_udp_sport_cbs bfd_seamless_udp_sport;
    /**
     * Access struct for bfd_server_trap_codes
     */
    algo_bfd_db_bfd_server_trap_codes_cbs bfd_server_trap_codes;
    /**
     * Access struct for bfd_dip
     */
    algo_bfd_db_bfd_dip_cbs bfd_dip;
    /**
     * Access struct for bfd_server_device_index
     */
    algo_bfd_db_bfd_server_device_index_cbs bfd_server_device_index;
} algo_bfd_db_cbs;

/*
 * Global Variables
 */

/*
 * Global Variables
 */

extern algo_bfd_db_cbs algo_bfd_db;

#endif /* __ALGO_BFD_ACCESS_H__ */

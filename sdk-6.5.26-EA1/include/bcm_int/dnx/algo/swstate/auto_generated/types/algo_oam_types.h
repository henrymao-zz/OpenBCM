/** \file algo/swstate/auto_generated/types/algo_oam_types.h
 *
 * sw state types (structs/enums/typedefs)
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

#ifndef __ALGO_OAM_TYPES_H__
#define __ALGO_OAM_TYPES_H__

#include <soc/dnxc/swstate/dnxc_sw_state_h_includes.h>
#include <bcm_int/dnx/algo/oam/algo_oam.h>
#include <bcm_int/dnx/algo/oamp/algo_oamp.h>
#include <bcm_int/dnx/algo/oamp/algo_oamp_v1.h>
#include <bcm_int/dnx/algo/res_mngr/res_mngr.h>
#include <bcm_int/dnx/algo/res_mngr/res_mngr_internal.h>
#include <bcm_int/dnx/algo/template_mngr/template_mngr.h>
#include <bcm_int/dnx/algo/template_mngr/template_mngr_internal.h>
#include <src/bcm/dnx/oam/oam_oamp.h>
/*
 * STRUCTs
 */

/**
 * OAM related sw state
 */
typedef struct {
    /**
     * OAM_GROUP_ID
     */
    dnx_algo_res_t oam_group_id;
    /**
     * OAM_PROFILE_ID_ING
     */
    dnx_algo_res_t oam_profile_id_ing;
    /**
     * OAM_PROFILE_ID_EG
     */
    dnx_algo_res_t oam_profile_id_eg;
    /**
     * OAM_PROFILE_ID_ING_ACC
     */
    dnx_algo_res_t oam_profile_id_ing_acc;
    /**
     * OAM_PROFILE_ID_EG_ACC
     */
    dnx_algo_res_t oam_profile_id_eg_acc;
#ifdef BCM_DNX2_SUPPORT
    /**
     * OAM_RMEP_ID_BELOW_THRESHOLD
     */
    dnx_algo_res_t oamp_v1_rmep_id_below_threshold;
#endif /* BCM_DNX2_SUPPORT*/ 
#ifdef BCM_DNX2_SUPPORT
    /**
     * OAM_RMEP_ID_ABOVE_THRESHOLD
     */
    dnx_algo_res_t oamp_v1_rmep_id_above_threshold;
#endif /* BCM_DNX2_SUPPORT*/ 
    /**
     * OAM ITMH PRIORITY PROFILE
     */
    dnx_algo_template_t oamp_itmh_pph_priority_profile;
#ifdef BCM_DNX2_SUPPORT
    /**
     * OAM MPLS/PWE EXP+TTL PROFILE
     */
    dnx_algo_template_t oam_mpls_pwe_exp_ttl_profile;
#endif /* BCM_DNX2_SUPPORT*/ 
    /**
     * OAMP_PUNT_EVENT_PROF_TEMPLATE
     */
    dnx_algo_template_t oamp_punt_event_prof_template;
    /**
     * OAM_SA_MAC_MSB_PROFILE_TEMPLATE
     */
    dnx_algo_template_t oam_sa_mac_msb_profile_template;
    /**
     * ETH OAM TPID PROFILE
     */
    dnx_algo_template_t eth_oam_tpid_profile;
    /**
     * OAM_GROUP_ICC_PROFILE
     */
    dnx_algo_template_t oam_group_icc_profile;
#ifdef BCM_DNX2_SUPPORT
    /**
     * OAM MEP PROFILE
     */
    dnx_algo_template_t oam_mep_profile;
#endif /* BCM_DNX2_SUPPORT*/ 
#ifdef BCM_DNX2_SUPPORT
    /**
     * OAM_DA_MAC_MSB_PROFILE_TEMPLATE
     */
    dnx_algo_template_t oam_da_mac_msb_profile_template;
#endif /* BCM_DNX2_SUPPORT*/ 
#ifdef BCM_DNX2_SUPPORT
    /**
     * OAM_DA_MAC_LSB_PROFILE_TEMPLATE
     */
    dnx_algo_template_t oam_da_mac_lsb_profile_template;
#endif /* BCM_DNX2_SUPPORT*/ 
    /**
     * OAM DEFAULT MEP PROFILE
     */
    dnx_algo_res_t oam_default_mep_profiles;
    /**
     * OAM_TRAP_TCAM_INDEX
     */
    dnx_algo_template_t oam_trap_tcam_index;
    /**
     * SLR measurement period
     */
    dnx_algo_template_t slm_oamp_measurement_period;
    /**
     * indicate if mpls_tp_mdl_ignore is enabled
     */
    uint32 mpls_tp_mdl_ignore;
    /**
     * indicate if eth_dmac_mdl_match_check is enabled
     */
    uint32 eth_dmac_mdl_match_check;
    /**
     * OAMP STAMP TLV profile
     */
    dnx_algo_template_t oamp_v2_stamp_tlv_profile;
    /**
     * OAMP TLV profile
     */
    dnx_algo_template_t oamp_v2_tlv_profile;
    /**
     * OAM candidate header small entry profile
     */
    dnx_algo_template_t oamp_v2_oam_ch_2_small_profile;
    /**
     * OAM_SERVER_DEVICE_INDEX
     */
    dnx_algo_template_t oam_server_device_index;
    /**
     * indicate if mpls oam native eth over pwe classify is enabled
     */
    uint32 mpls_oam_native_eth_over_pwe_classify;
} algo_oam_sw_state_t;


#endif /* __ALGO_OAM_TYPES_H__ */


/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_SOCDNX_GENERAL

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_fc.h>




extern shr_error_e jr2_a0_data_fc_attach(
    int unit);


extern shr_error_e j2c_a0_data_fc_attach(
    int unit);


extern shr_error_e q2a_a0_data_fc_attach(
    int unit);


extern shr_error_e j2p_a0_data_fc_attach(
    int unit);


extern shr_error_e j2x_a0_data_fc_attach(
    int unit);




static shr_error_e
dnx_data_fc_general_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "general";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_fc_general_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data fc general features");

    submodule_data->features[dnx_data_fc_general_fc_to_nif_status].name = "fc_to_nif_status";
    submodule_data->features[dnx_data_fc_general_fc_to_nif_status].doc = "";
    submodule_data->features[dnx_data_fc_general_fc_to_nif_status].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_ilu_fc_status].name = "ilu_fc_status";
    submodule_data->features[dnx_data_fc_general_ilu_fc_status].doc = "";
    submodule_data->features[dnx_data_fc_general_ilu_fc_status].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_ilu_fc_status_per_tdm].name = "ilu_fc_status_per_tdm";
    submodule_data->features[dnx_data_fc_general_ilu_fc_status_per_tdm].doc = "";
    submodule_data->features[dnx_data_fc_general_ilu_fc_status_per_tdm].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_inb_ilkn_rx_status].name = "inb_ilkn_rx_status";
    submodule_data->features[dnx_data_fc_general_inb_ilkn_rx_status].doc = "";
    submodule_data->features[dnx_data_fc_general_inb_ilkn_rx_status].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_glb_res_lp_to_llfc].name = "glb_res_lp_to_llfc";
    submodule_data->features[dnx_data_fc_general_glb_res_lp_to_llfc].doc = "";
    submodule_data->features[dnx_data_fc_general_glb_res_lp_to_llfc].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_vsqd_to_llfc_pfc].name = "vsqd_to_llfc_pfc";
    submodule_data->features[dnx_data_fc_general_vsqd_to_llfc_pfc].doc = "";
    submodule_data->features[dnx_data_fc_general_vsqd_to_llfc_pfc].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_vsq_thr_en].name = "vsq_thr_en";
    submodule_data->features[dnx_data_fc_general_vsq_thr_en].doc = "";
    submodule_data->features[dnx_data_fc_general_vsq_thr_en].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_oob_tx_reset].name = "oob_tx_reset";
    submodule_data->features[dnx_data_fc_general_oob_tx_reset].doc = "";
    submodule_data->features[dnx_data_fc_general_oob_tx_reset].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_additional_enablers].name = "additional_enablers";
    submodule_data->features[dnx_data_fc_general_additional_enablers].doc = "";
    submodule_data->features[dnx_data_fc_general_additional_enablers].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_ilkn_inb_llfc].name = "ilkn_inb_llfc";
    submodule_data->features[dnx_data_fc_general_ilkn_inb_llfc].doc = "";
    submodule_data->features[dnx_data_fc_general_ilkn_inb_llfc].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_flexe_flow_control].name = "flexe_flow_control";
    submodule_data->features[dnx_data_fc_general_flexe_flow_control].doc = "";
    submodule_data->features[dnx_data_fc_general_flexe_flow_control].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_glb_rsc_oob_en].name = "glb_rsc_oob_en";
    submodule_data->features[dnx_data_fc_general_glb_rsc_oob_en].doc = "";
    submodule_data->features[dnx_data_fc_general_glb_rsc_oob_en].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_cat2_oob_en].name = "cat2_oob_en";
    submodule_data->features[dnx_data_fc_general_cat2_oob_en].doc = "";
    submodule_data->features[dnx_data_fc_general_cat2_oob_en].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_pfc_rec_cdu_shift].name = "pfc_rec_cdu_shift";
    submodule_data->features[dnx_data_fc_general_pfc_rec_cdu_shift].doc = "";
    submodule_data->features[dnx_data_fc_general_pfc_rec_cdu_shift].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_pfc_status_regs_double_read].name = "pfc_status_regs_double_read";
    submodule_data->features[dnx_data_fc_general_pfc_status_regs_double_read].doc = "";
    submodule_data->features[dnx_data_fc_general_pfc_status_regs_double_read].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_ilkn_oob_fast_llfc].name = "ilkn_oob_fast_llfc";
    submodule_data->features[dnx_data_fc_general_ilkn_oob_fast_llfc].doc = "";
    submodule_data->features[dnx_data_fc_general_ilkn_oob_fast_llfc].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_pp_inb_enable].name = "pp_inb_enable";
    submodule_data->features[dnx_data_fc_general_pp_inb_enable].doc = "";
    submodule_data->features[dnx_data_fc_general_pp_inb_enable].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_fc_from_llfc_vsq_status_sel].name = "fc_from_llfc_vsq_status_sel";
    submodule_data->features[dnx_data_fc_general_fc_from_llfc_vsq_status_sel].doc = "";
    submodule_data->features[dnx_data_fc_general_fc_from_llfc_vsq_status_sel].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_if_2_cfc_enablers].name = "if_2_cfc_enablers";
    submodule_data->features[dnx_data_fc_general_if_2_cfc_enablers].doc = "";
    submodule_data->features[dnx_data_fc_general_if_2_cfc_enablers].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_ilkn_oob_en].name = "ilkn_oob_en";
    submodule_data->features[dnx_data_fc_general_ilkn_oob_en].doc = "";
    submodule_data->features[dnx_data_fc_general_ilkn_oob_en].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_ilkn_polarity_set].name = "ilkn_polarity_set";
    submodule_data->features[dnx_data_fc_general_ilkn_polarity_set].doc = "";
    submodule_data->features[dnx_data_fc_general_ilkn_polarity_set].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_additional_rx_pfc_bmp_types].name = "additional_rx_pfc_bmp_types";
    submodule_data->features[dnx_data_fc_general_additional_rx_pfc_bmp_types].doc = "";
    submodule_data->features[dnx_data_fc_general_additional_rx_pfc_bmp_types].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_disable_pfc_mask_on_link_fail].name = "disable_pfc_mask_on_link_fail";
    submodule_data->features[dnx_data_fc_general_disable_pfc_mask_on_link_fail].doc = "";
    submodule_data->features[dnx_data_fc_general_disable_pfc_mask_on_link_fail].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_gen_pfc_from_llfc_bitmap_per_type].name = "gen_pfc_from_llfc_bitmap_per_type";
    submodule_data->features[dnx_data_fc_general_gen_pfc_from_llfc_bitmap_per_type].doc = "";
    submodule_data->features[dnx_data_fc_general_gen_pfc_from_llfc_bitmap_per_type].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_llfc_handled_in_cfc].name = "llfc_handled_in_cfc";
    submodule_data->features[dnx_data_fc_general_llfc_handled_in_cfc].doc = "";
    submodule_data->features[dnx_data_fc_general_llfc_handled_in_cfc].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_coe_vid_mapping].name = "coe_vid_mapping";
    submodule_data->features[dnx_data_fc_general_coe_vid_mapping].doc = "";
    submodule_data->features[dnx_data_fc_general_coe_vid_mapping].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_ilkn_inband_support].name = "ilkn_inband_support";
    submodule_data->features[dnx_data_fc_general_ilkn_inband_support].doc = "";
    submodule_data->features[dnx_data_fc_general_ilkn_inband_support].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_oob_support].name = "oob_support";
    submodule_data->features[dnx_data_fc_general_oob_support].doc = "";
    submodule_data->features[dnx_data_fc_general_oob_support].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_coe_support].name = "coe_support";
    submodule_data->features[dnx_data_fc_general_coe_support].doc = "";
    submodule_data->features[dnx_data_fc_general_coe_support].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_nif_pfc_bitmaps_e_f_support].name = "nif_pfc_bitmaps_e_f_support";
    submodule_data->features[dnx_data_fc_general_nif_pfc_bitmaps_e_f_support].doc = "";
    submodule_data->features[dnx_data_fc_general_nif_pfc_bitmaps_e_f_support].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_qmlf_fc_high_and_low_rmcs_support].name = "qmlf_fc_high_and_low_rmcs_support";
    submodule_data->features[dnx_data_fc_general_qmlf_fc_high_and_low_rmcs_support].doc = "";
    submodule_data->features[dnx_data_fc_general_qmlf_fc_high_and_low_rmcs_support].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_qmlf_rmcs_thresholds_per_profile_support].name = "qmlf_rmcs_thresholds_per_profile_support";
    submodule_data->features[dnx_data_fc_general_qmlf_rmcs_thresholds_per_profile_support].doc = "";
    submodule_data->features[dnx_data_fc_general_qmlf_rmcs_thresholds_per_profile_support].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_is_used].name = "is_used";
    submodule_data->features[dnx_data_fc_general_is_used].doc = "";
    submodule_data->features[dnx_data_fc_general_is_used].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_fc_general_power_down_supported].name = "power_down_supported";
    submodule_data->features[dnx_data_fc_general_power_down_supported].doc = "";
    submodule_data->features[dnx_data_fc_general_power_down_supported].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnx_data_fc_general_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data fc general defines");

    submodule_data->defines[dnx_data_fc_general_define_nof_glb_rsc].name = "nof_glb_rsc";
    submodule_data->defines[dnx_data_fc_general_define_nof_glb_rsc].doc = "";
    
    submodule_data->defines[dnx_data_fc_general_define_nof_glb_rsc].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_general_define_nof_gen_bmps].name = "nof_gen_bmps";
    submodule_data->defines[dnx_data_fc_general_define_nof_gen_bmps].doc = "";
    
    submodule_data->defines[dnx_data_fc_general_define_nof_gen_bmps].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_general_define_gen_bmp_first_id].name = "gen_bmp_first_id";
    submodule_data->defines[dnx_data_fc_general_define_gen_bmp_first_id].doc = "";
    
    submodule_data->defines[dnx_data_fc_general_define_gen_bmp_first_id].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_general_define_nof_af_nif_indications].name = "nof_af_nif_indications";
    submodule_data->defines[dnx_data_fc_general_define_nof_af_nif_indications].doc = "";
    
    submodule_data->defines[dnx_data_fc_general_define_nof_af_nif_indications].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_general_define_nof_cal_llfcs].name = "nof_cal_llfcs";
    submodule_data->defines[dnx_data_fc_general_define_nof_cal_llfcs].doc = "";
    
    submodule_data->defines[dnx_data_fc_general_define_nof_cal_llfcs].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_general_define_nof_entries_qmlf].name = "nof_entries_qmlf";
    submodule_data->defines[dnx_data_fc_general_define_nof_entries_qmlf].doc = "";
    
    submodule_data->defines[dnx_data_fc_general_define_nof_entries_qmlf].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_general_define_nof_bits_in_pfc_status_select].name = "nof_bits_in_pfc_status_select";
    submodule_data->defines[dnx_data_fc_general_define_nof_bits_in_pfc_status_select].doc = "";
    
    submodule_data->defines[dnx_data_fc_general_define_nof_bits_in_pfc_status_select].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_general_define_nof_rmc_thresholds_profiles].name = "nof_rmc_thresholds_profiles";
    submodule_data->defines[dnx_data_fc_general_define_nof_rmc_thresholds_profiles].doc = "";
    
    submodule_data->defines[dnx_data_fc_general_define_nof_rmc_thresholds_profiles].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_general_define_rmc_pfc_set_threshold_default].name = "rmc_pfc_set_threshold_default";
    submodule_data->defines[dnx_data_fc_general_define_rmc_pfc_set_threshold_default].doc = "";
    
    submodule_data->defines[dnx_data_fc_general_define_rmc_pfc_set_threshold_default].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_general_define_rmc_pfc_clear_threshold_default].name = "rmc_pfc_clear_threshold_default";
    submodule_data->defines[dnx_data_fc_general_define_rmc_pfc_clear_threshold_default].doc = "";
    
    submodule_data->defines[dnx_data_fc_general_define_rmc_pfc_clear_threshold_default].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_general_define_rmc_llfc_set_threshold_default].name = "rmc_llfc_set_threshold_default";
    submodule_data->defines[dnx_data_fc_general_define_rmc_llfc_set_threshold_default].doc = "";
    
    submodule_data->defines[dnx_data_fc_general_define_rmc_llfc_set_threshold_default].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_general_define_rmc_llfc_clear_threshold_default].name = "rmc_llfc_clear_threshold_default";
    submodule_data->defines[dnx_data_fc_general_define_rmc_llfc_clear_threshold_default].doc = "";
    
    submodule_data->defines[dnx_data_fc_general_define_rmc_llfc_clear_threshold_default].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_general_define_nof_bits_in_nif_eth_rmc_id].name = "nof_bits_in_nif_eth_rmc_id";
    submodule_data->defines[dnx_data_fc_general_define_nof_bits_in_nif_eth_rmc_id].doc = "";
    
    submodule_data->defines[dnx_data_fc_general_define_nof_bits_in_nif_eth_rmc_id].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_fc_general_define_bcm_cos_count].name = "bcm_cos_count";
    submodule_data->defines[dnx_data_fc_general_define_bcm_cos_count].doc = "";
    
    submodule_data->defines[dnx_data_fc_general_define_bcm_cos_count].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_fc_general_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data fc general tables");


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_fc_general_feature_get(
    int unit,
    dnx_data_fc_general_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_general, feature);
}


uint32
dnx_data_fc_general_nof_glb_rsc_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_general, dnx_data_fc_general_define_nof_glb_rsc);
}

uint32
dnx_data_fc_general_nof_gen_bmps_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_general, dnx_data_fc_general_define_nof_gen_bmps);
}

uint32
dnx_data_fc_general_gen_bmp_first_id_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_general, dnx_data_fc_general_define_gen_bmp_first_id);
}

uint32
dnx_data_fc_general_nof_af_nif_indications_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_general, dnx_data_fc_general_define_nof_af_nif_indications);
}

uint32
dnx_data_fc_general_nof_cal_llfcs_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_general, dnx_data_fc_general_define_nof_cal_llfcs);
}

uint32
dnx_data_fc_general_nof_entries_qmlf_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_general, dnx_data_fc_general_define_nof_entries_qmlf);
}

uint32
dnx_data_fc_general_nof_bits_in_pfc_status_select_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_general, dnx_data_fc_general_define_nof_bits_in_pfc_status_select);
}

uint32
dnx_data_fc_general_nof_rmc_thresholds_profiles_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_general, dnx_data_fc_general_define_nof_rmc_thresholds_profiles);
}

uint32
dnx_data_fc_general_rmc_pfc_set_threshold_default_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_general, dnx_data_fc_general_define_rmc_pfc_set_threshold_default);
}

uint32
dnx_data_fc_general_rmc_pfc_clear_threshold_default_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_general, dnx_data_fc_general_define_rmc_pfc_clear_threshold_default);
}

uint32
dnx_data_fc_general_rmc_llfc_set_threshold_default_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_general, dnx_data_fc_general_define_rmc_llfc_set_threshold_default);
}

uint32
dnx_data_fc_general_rmc_llfc_clear_threshold_default_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_general, dnx_data_fc_general_define_rmc_llfc_clear_threshold_default);
}

uint32
dnx_data_fc_general_nof_bits_in_nif_eth_rmc_id_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_general, dnx_data_fc_general_define_nof_bits_in_nif_eth_rmc_id);
}

uint32
dnx_data_fc_general_bcm_cos_count_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_general, dnx_data_fc_general_define_bcm_cos_count);
}










static shr_error_e
dnx_data_fc_calendar_common_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "calendar_common";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_fc_calendar_common_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data fc calendar_common features");

    
    submodule_data->nof_defines = _dnx_data_fc_calendar_common_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data fc calendar_common defines");

    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_pfc].name = "rx_dest_pfc";
    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_pfc].doc = "";
    
    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_pfc].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_nif_llfc].name = "rx_dest_nif_llfc";
    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_nif_llfc].doc = "";
    
    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_nif_llfc].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_port_2_prio].name = "rx_dest_port_2_prio";
    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_port_2_prio].doc = "";
    
    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_port_2_prio].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_port_4_prio].name = "rx_dest_port_4_prio";
    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_port_4_prio].doc = "";
    
    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_port_4_prio].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_port_8_prio].name = "rx_dest_port_8_prio";
    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_port_8_prio].doc = "";
    
    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_port_8_prio].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_pfc_generic_bmp].name = "rx_dest_pfc_generic_bmp";
    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_pfc_generic_bmp].doc = "";
    
    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_pfc_generic_bmp].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_empty].name = "rx_dest_empty";
    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_empty].doc = "";
    
    submodule_data->defines[dnx_data_fc_calendar_common_define_rx_dest_empty].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_vsq_a_b_c].name = "tx_src_vsq_a_b_c";
    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_vsq_a_b_c].doc = "";
    
    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_vsq_a_b_c].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_vsq_d].name = "tx_src_vsq_d";
    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_vsq_d].doc = "";
    
    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_vsq_d].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_llfc_vsq].name = "tx_src_llfc_vsq";
    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_llfc_vsq].doc = "";
    
    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_llfc_vsq].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_pfc_vsq].name = "tx_src_pfc_vsq";
    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_pfc_vsq].doc = "";
    
    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_pfc_vsq].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_glb_rsc].name = "tx_src_glb_rsc";
    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_glb_rsc].doc = "";
    
    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_glb_rsc].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_nif_llfc].name = "tx_src_nif_llfc";
    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_nif_llfc].doc = "";
    
    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_nif_llfc].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_empty].name = "tx_src_empty";
    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_empty].doc = "";
    
    submodule_data->defines[dnx_data_fc_calendar_common_define_tx_src_empty].flags |= DNXC_DATA_F_DEFINE;

    
    submodule_data->nof_tables = _dnx_data_fc_calendar_common_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data fc calendar_common tables");


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_fc_calendar_common_feature_get(
    int unit,
    dnx_data_fc_calendar_common_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_calendar_common, feature);
}


uint32
dnx_data_fc_calendar_common_rx_dest_pfc_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_calendar_common, dnx_data_fc_calendar_common_define_rx_dest_pfc);
}

uint32
dnx_data_fc_calendar_common_rx_dest_nif_llfc_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_calendar_common, dnx_data_fc_calendar_common_define_rx_dest_nif_llfc);
}

uint32
dnx_data_fc_calendar_common_rx_dest_port_2_prio_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_calendar_common, dnx_data_fc_calendar_common_define_rx_dest_port_2_prio);
}

uint32
dnx_data_fc_calendar_common_rx_dest_port_4_prio_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_calendar_common, dnx_data_fc_calendar_common_define_rx_dest_port_4_prio);
}

uint32
dnx_data_fc_calendar_common_rx_dest_port_8_prio_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_calendar_common, dnx_data_fc_calendar_common_define_rx_dest_port_8_prio);
}

uint32
dnx_data_fc_calendar_common_rx_dest_pfc_generic_bmp_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_calendar_common, dnx_data_fc_calendar_common_define_rx_dest_pfc_generic_bmp);
}

uint32
dnx_data_fc_calendar_common_rx_dest_empty_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_calendar_common, dnx_data_fc_calendar_common_define_rx_dest_empty);
}

uint32
dnx_data_fc_calendar_common_tx_src_vsq_a_b_c_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_calendar_common, dnx_data_fc_calendar_common_define_tx_src_vsq_a_b_c);
}

uint32
dnx_data_fc_calendar_common_tx_src_vsq_d_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_calendar_common, dnx_data_fc_calendar_common_define_tx_src_vsq_d);
}

uint32
dnx_data_fc_calendar_common_tx_src_llfc_vsq_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_calendar_common, dnx_data_fc_calendar_common_define_tx_src_llfc_vsq);
}

uint32
dnx_data_fc_calendar_common_tx_src_pfc_vsq_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_calendar_common, dnx_data_fc_calendar_common_define_tx_src_pfc_vsq);
}

uint32
dnx_data_fc_calendar_common_tx_src_glb_rsc_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_calendar_common, dnx_data_fc_calendar_common_define_tx_src_glb_rsc);
}

uint32
dnx_data_fc_calendar_common_tx_src_nif_llfc_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_calendar_common, dnx_data_fc_calendar_common_define_tx_src_nif_llfc);
}

uint32
dnx_data_fc_calendar_common_tx_src_empty_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_calendar_common, dnx_data_fc_calendar_common_define_tx_src_empty);
}










static shr_error_e
dnx_data_fc_coe_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "coe";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_fc_coe_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data fc coe features");

    submodule_data->features[dnx_data_fc_coe_both_modes_support].name = "both_modes_support";
    submodule_data->features[dnx_data_fc_coe_both_modes_support].doc = "";
    submodule_data->features[dnx_data_fc_coe_both_modes_support].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnx_data_fc_coe_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data fc coe defines");

    submodule_data->defines[dnx_data_fc_coe_define_nof_coe_cal_instances].name = "nof_coe_cal_instances";
    submodule_data->defines[dnx_data_fc_coe_define_nof_coe_cal_instances].doc = "";
    
    submodule_data->defines[dnx_data_fc_coe_define_nof_coe_cal_instances].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_coe_define_nof_supported_chan_ids].name = "nof_supported_chan_ids";
    submodule_data->defines[dnx_data_fc_coe_define_nof_supported_chan_ids].doc = "";
    
    submodule_data->defines[dnx_data_fc_coe_define_nof_supported_chan_ids].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_coe_define_nof_coe_vid_mask_width].name = "nof_coe_vid_mask_width";
    submodule_data->defines[dnx_data_fc_coe_define_nof_coe_vid_mask_width].doc = "";
    
    submodule_data->defines[dnx_data_fc_coe_define_nof_coe_vid_mask_width].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_coe_define_nof_coe_vid_right_shift_width].name = "nof_coe_vid_right_shift_width";
    submodule_data->defines[dnx_data_fc_coe_define_nof_coe_vid_right_shift_width].doc = "";
    
    submodule_data->defines[dnx_data_fc_coe_define_nof_coe_vid_right_shift_width].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_coe_define_nof_coe_ptc_mask_width].name = "nof_coe_ptc_mask_width";
    submodule_data->defines[dnx_data_fc_coe_define_nof_coe_ptc_mask_width].doc = "";
    
    submodule_data->defines[dnx_data_fc_coe_define_nof_coe_ptc_mask_width].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_coe_define_nof_coe_ptc_left_shift_width].name = "nof_coe_ptc_left_shift_width";
    submodule_data->defines[dnx_data_fc_coe_define_nof_coe_ptc_left_shift_width].doc = "";
    
    submodule_data->defines[dnx_data_fc_coe_define_nof_coe_ptc_left_shift_width].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_coe_define_max_coe_ticks].name = "max_coe_ticks";
    submodule_data->defines[dnx_data_fc_coe_define_max_coe_ticks].doc = "";
    
    submodule_data->defines[dnx_data_fc_coe_define_max_coe_ticks].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_coe_define_fc_support].name = "fc_support";
    submodule_data->defines[dnx_data_fc_coe_define_fc_support].doc = "";
    
    submodule_data->defines[dnx_data_fc_coe_define_fc_support].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_coe_define_map_value_size_in_bits].name = "map_value_size_in_bits";
    submodule_data->defines[dnx_data_fc_coe_define_map_value_size_in_bits].doc = "";
    
    submodule_data->defines[dnx_data_fc_coe_define_map_value_size_in_bits].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_fc_coe_define_calendar_pause_resolution].name = "calendar_pause_resolution";
    submodule_data->defines[dnx_data_fc_coe_define_calendar_pause_resolution].doc = "";
    
    submodule_data->defines[dnx_data_fc_coe_define_calendar_pause_resolution].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_fc_coe_define_data_offset].name = "data_offset";
    submodule_data->defines[dnx_data_fc_coe_define_data_offset].doc = "";
    
    submodule_data->defines[dnx_data_fc_coe_define_data_offset].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_fc_coe_define_ethertype].name = "ethertype";
    submodule_data->defines[dnx_data_fc_coe_define_ethertype].doc = "";
    
    submodule_data->defines[dnx_data_fc_coe_define_ethertype].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_fc_coe_define_control_opcode].name = "control_opcode";
    submodule_data->defines[dnx_data_fc_coe_define_control_opcode].doc = "";
    
    submodule_data->defines[dnx_data_fc_coe_define_control_opcode].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_fc_coe_define_coe_vid_offset].name = "coe_vid_offset";
    submodule_data->defines[dnx_data_fc_coe_define_coe_vid_offset].doc = "";
    
    submodule_data->defines[dnx_data_fc_coe_define_coe_vid_offset].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_fc_coe_define_coe_vid_mask].name = "coe_vid_mask";
    submodule_data->defines[dnx_data_fc_coe_define_coe_vid_mask].doc = "";
    
    submodule_data->defines[dnx_data_fc_coe_define_coe_vid_mask].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_fc_coe_define_coe_vid_right_shift].name = "coe_vid_right_shift";
    submodule_data->defines[dnx_data_fc_coe_define_coe_vid_right_shift].doc = "";
    
    submodule_data->defines[dnx_data_fc_coe_define_coe_vid_right_shift].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_fc_coe_define_coe_ptc_mask].name = "coe_ptc_mask";
    submodule_data->defines[dnx_data_fc_coe_define_coe_ptc_mask].doc = "";
    
    submodule_data->defines[dnx_data_fc_coe_define_coe_ptc_mask].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_fc_coe_define_coe_ptc_left_shift].name = "coe_ptc_left_shift";
    submodule_data->defines[dnx_data_fc_coe_define_coe_ptc_left_shift].doc = "";
    
    submodule_data->defines[dnx_data_fc_coe_define_coe_ptc_left_shift].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_fc_coe_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data fc coe tables");

    
    submodule_data->tables[dnx_data_fc_coe_table_calendar_mode].name = "calendar_mode";
    submodule_data->tables[dnx_data_fc_coe_table_calendar_mode].doc = "";
    submodule_data->tables[dnx_data_fc_coe_table_calendar_mode].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_fc_coe_table_calendar_mode].size_of_values = sizeof(dnx_data_fc_coe_calendar_mode_t);
    submodule_data->tables[dnx_data_fc_coe_table_calendar_mode].entry_get = dnx_data_fc_coe_calendar_mode_entry_str_get;

    
    submodule_data->tables[dnx_data_fc_coe_table_calendar_mode].nof_keys = 0;

    
    submodule_data->tables[dnx_data_fc_coe_table_calendar_mode].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_fc_coe_table_calendar_mode].values, dnxc_data_value_t, submodule_data->tables[dnx_data_fc_coe_table_calendar_mode].nof_values, "_dnx_data_fc_coe_table_calendar_mode table values");
    submodule_data->tables[dnx_data_fc_coe_table_calendar_mode].values[0].name = "mode";
    submodule_data->tables[dnx_data_fc_coe_table_calendar_mode].values[0].type = "int";
    submodule_data->tables[dnx_data_fc_coe_table_calendar_mode].values[0].doc = "";
    submodule_data->tables[dnx_data_fc_coe_table_calendar_mode].values[0].offset = UTILEX_OFFSETOF(dnx_data_fc_coe_calendar_mode_t, mode);

    
    submodule_data->tables[dnx_data_fc_coe_table_mac_address].name = "mac_address";
    submodule_data->tables[dnx_data_fc_coe_table_mac_address].doc = "";
    submodule_data->tables[dnx_data_fc_coe_table_mac_address].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_fc_coe_table_mac_address].size_of_values = sizeof(dnx_data_fc_coe_mac_address_t);
    submodule_data->tables[dnx_data_fc_coe_table_mac_address].entry_get = dnx_data_fc_coe_mac_address_entry_str_get;

    
    submodule_data->tables[dnx_data_fc_coe_table_mac_address].nof_keys = 0;

    
    submodule_data->tables[dnx_data_fc_coe_table_mac_address].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_fc_coe_table_mac_address].values, dnxc_data_value_t, submodule_data->tables[dnx_data_fc_coe_table_mac_address].nof_values, "_dnx_data_fc_coe_table_mac_address table values");
    submodule_data->tables[dnx_data_fc_coe_table_mac_address].values[0].name = "mac";
    submodule_data->tables[dnx_data_fc_coe_table_mac_address].values[0].type = "uint8[6]";
    submodule_data->tables[dnx_data_fc_coe_table_mac_address].values[0].doc = "";
    submodule_data->tables[dnx_data_fc_coe_table_mac_address].values[0].offset = UTILEX_OFFSETOF(dnx_data_fc_coe_mac_address_t, mac);

    
    submodule_data->tables[dnx_data_fc_coe_table_calender_length].name = "calender_length";
    submodule_data->tables[dnx_data_fc_coe_table_calender_length].doc = "";
    submodule_data->tables[dnx_data_fc_coe_table_calender_length].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_fc_coe_table_calender_length].size_of_values = sizeof(dnx_data_fc_coe_calender_length_t);
    submodule_data->tables[dnx_data_fc_coe_table_calender_length].entry_get = dnx_data_fc_coe_calender_length_entry_str_get;

    
    submodule_data->tables[dnx_data_fc_coe_table_calender_length].nof_keys = 1;
    submodule_data->tables[dnx_data_fc_coe_table_calender_length].keys[0].name = "cal_id";
    submodule_data->tables[dnx_data_fc_coe_table_calender_length].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_fc_coe_table_calender_length].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_fc_coe_table_calender_length].values, dnxc_data_value_t, submodule_data->tables[dnx_data_fc_coe_table_calender_length].nof_values, "_dnx_data_fc_coe_table_calender_length table values");
    submodule_data->tables[dnx_data_fc_coe_table_calender_length].values[0].name = "len";
    submodule_data->tables[dnx_data_fc_coe_table_calender_length].values[0].type = "int";
    submodule_data->tables[dnx_data_fc_coe_table_calender_length].values[0].doc = "";
    submodule_data->tables[dnx_data_fc_coe_table_calender_length].values[0].offset = UTILEX_OFFSETOF(dnx_data_fc_coe_calender_length_t, len);


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_fc_coe_feature_get(
    int unit,
    dnx_data_fc_coe_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, feature);
}


uint32
dnx_data_fc_coe_nof_coe_cal_instances_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_define_nof_coe_cal_instances);
}

uint32
dnx_data_fc_coe_nof_supported_chan_ids_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_define_nof_supported_chan_ids);
}

uint32
dnx_data_fc_coe_nof_coe_vid_mask_width_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_define_nof_coe_vid_mask_width);
}

uint32
dnx_data_fc_coe_nof_coe_vid_right_shift_width_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_define_nof_coe_vid_right_shift_width);
}

uint32
dnx_data_fc_coe_nof_coe_ptc_mask_width_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_define_nof_coe_ptc_mask_width);
}

uint32
dnx_data_fc_coe_nof_coe_ptc_left_shift_width_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_define_nof_coe_ptc_left_shift_width);
}

uint32
dnx_data_fc_coe_max_coe_ticks_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_define_max_coe_ticks);
}

uint32
dnx_data_fc_coe_fc_support_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_define_fc_support);
}

uint32
dnx_data_fc_coe_map_value_size_in_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_define_map_value_size_in_bits);
}

uint32
dnx_data_fc_coe_calendar_pause_resolution_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_define_calendar_pause_resolution);
}

uint32
dnx_data_fc_coe_data_offset_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_define_data_offset);
}

uint32
dnx_data_fc_coe_ethertype_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_define_ethertype);
}

uint32
dnx_data_fc_coe_control_opcode_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_define_control_opcode);
}

uint32
dnx_data_fc_coe_coe_vid_offset_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_define_coe_vid_offset);
}

uint32
dnx_data_fc_coe_coe_vid_mask_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_define_coe_vid_mask);
}

uint32
dnx_data_fc_coe_coe_vid_right_shift_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_define_coe_vid_right_shift);
}

uint32
dnx_data_fc_coe_coe_ptc_mask_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_define_coe_ptc_mask);
}

uint32
dnx_data_fc_coe_coe_ptc_left_shift_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_define_coe_ptc_left_shift);
}



const dnx_data_fc_coe_calendar_mode_t *
dnx_data_fc_coe_calendar_mode_get(
    int unit)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_table_calendar_mode);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    return (const dnx_data_fc_coe_calendar_mode_t *) data;

}

const dnx_data_fc_coe_mac_address_t *
dnx_data_fc_coe_mac_address_get(
    int unit)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_table_mac_address);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    return (const dnx_data_fc_coe_mac_address_t *) data;

}

const dnx_data_fc_coe_calender_length_t *
dnx_data_fc_coe_calender_length_get(
    int unit,
    int cal_id)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_table_calender_length);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, cal_id, 0);
    return (const dnx_data_fc_coe_calender_length_t *) data;

}


shr_error_e
dnx_data_fc_coe_calendar_mode_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_fc_coe_calendar_mode_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_table_calendar_mode);
    data = (const dnx_data_fc_coe_calendar_mode_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, 0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->mode);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_fc_coe_mac_address_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_fc_coe_mac_address_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_table_mac_address);
    data = (const dnx_data_fc_coe_mac_address_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, 0, 0);
    switch (value_index)
    {
        case 0:
            DNXC_DATA_MGMT_ARR_STR(buffer, 6, data->mac);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_fc_coe_calender_length_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_fc_coe_calender_length_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_table_calender_length);
    data = (const dnx_data_fc_coe_calender_length_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->len);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnx_data_fc_coe_calendar_mode_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_table_calendar_mode);

}

const dnxc_data_table_info_t *
dnx_data_fc_coe_mac_address_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_table_mac_address);

}

const dnxc_data_table_info_t *
dnx_data_fc_coe_calender_length_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_coe, dnx_data_fc_coe_table_calender_length);

}






static shr_error_e
dnx_data_fc_oob_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "oob";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_fc_oob_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data fc oob features");

    
    submodule_data->nof_defines = _dnx_data_fc_oob_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data fc oob defines");

    submodule_data->defines[dnx_data_fc_oob_define_nof_oob_ids].name = "nof_oob_ids";
    submodule_data->defines[dnx_data_fc_oob_define_nof_oob_ids].doc = "";
    
    submodule_data->defines[dnx_data_fc_oob_define_nof_oob_ids].flags |= DNXC_DATA_F_DEFINE;

    
    submodule_data->nof_tables = _dnx_data_fc_oob_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data fc oob tables");

    
    submodule_data->tables[dnx_data_fc_oob_table_calender_length].name = "calender_length";
    submodule_data->tables[dnx_data_fc_oob_table_calender_length].doc = "";
    submodule_data->tables[dnx_data_fc_oob_table_calender_length].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_fc_oob_table_calender_length].size_of_values = sizeof(dnx_data_fc_oob_calender_length_t);
    submodule_data->tables[dnx_data_fc_oob_table_calender_length].entry_get = dnx_data_fc_oob_calender_length_entry_str_get;

    
    submodule_data->tables[dnx_data_fc_oob_table_calender_length].nof_keys = 1;
    submodule_data->tables[dnx_data_fc_oob_table_calender_length].keys[0].name = "oob_id";
    submodule_data->tables[dnx_data_fc_oob_table_calender_length].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_fc_oob_table_calender_length].nof_values = 2;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_fc_oob_table_calender_length].values, dnxc_data_value_t, submodule_data->tables[dnx_data_fc_oob_table_calender_length].nof_values, "_dnx_data_fc_oob_table_calender_length table values");
    submodule_data->tables[dnx_data_fc_oob_table_calender_length].values[0].name = "tx";
    submodule_data->tables[dnx_data_fc_oob_table_calender_length].values[0].type = "int";
    submodule_data->tables[dnx_data_fc_oob_table_calender_length].values[0].doc = "";
    submodule_data->tables[dnx_data_fc_oob_table_calender_length].values[0].offset = UTILEX_OFFSETOF(dnx_data_fc_oob_calender_length_t, tx);
    submodule_data->tables[dnx_data_fc_oob_table_calender_length].values[1].name = "rx";
    submodule_data->tables[dnx_data_fc_oob_table_calender_length].values[1].type = "int";
    submodule_data->tables[dnx_data_fc_oob_table_calender_length].values[1].doc = "";
    submodule_data->tables[dnx_data_fc_oob_table_calender_length].values[1].offset = UTILEX_OFFSETOF(dnx_data_fc_oob_calender_length_t, rx);

    
    submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].name = "calender_rep_count";
    submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].doc = "";
    submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].size_of_values = sizeof(dnx_data_fc_oob_calender_rep_count_t);
    submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].entry_get = dnx_data_fc_oob_calender_rep_count_entry_str_get;

    
    submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].nof_keys = 1;
    submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].keys[0].name = "oob_id";
    submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].nof_values = 2;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].values, dnxc_data_value_t, submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].nof_values, "_dnx_data_fc_oob_table_calender_rep_count table values");
    submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].values[0].name = "tx";
    submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].values[0].type = "int";
    submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].values[0].doc = "";
    submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].values[0].offset = UTILEX_OFFSETOF(dnx_data_fc_oob_calender_rep_count_t, tx);
    submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].values[1].name = "rx";
    submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].values[1].type = "int";
    submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].values[1].doc = "";
    submodule_data->tables[dnx_data_fc_oob_table_calender_rep_count].values[1].offset = UTILEX_OFFSETOF(dnx_data_fc_oob_calender_rep_count_t, rx);

    
    submodule_data->tables[dnx_data_fc_oob_table_tx_freq].name = "tx_freq";
    submodule_data->tables[dnx_data_fc_oob_table_tx_freq].doc = "";
    submodule_data->tables[dnx_data_fc_oob_table_tx_freq].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_fc_oob_table_tx_freq].size_of_values = sizeof(dnx_data_fc_oob_tx_freq_t);
    submodule_data->tables[dnx_data_fc_oob_table_tx_freq].entry_get = dnx_data_fc_oob_tx_freq_entry_str_get;

    
    submodule_data->tables[dnx_data_fc_oob_table_tx_freq].nof_keys = 1;
    submodule_data->tables[dnx_data_fc_oob_table_tx_freq].keys[0].name = "oob_id";
    submodule_data->tables[dnx_data_fc_oob_table_tx_freq].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_fc_oob_table_tx_freq].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_fc_oob_table_tx_freq].values, dnxc_data_value_t, submodule_data->tables[dnx_data_fc_oob_table_tx_freq].nof_values, "_dnx_data_fc_oob_table_tx_freq table values");
    submodule_data->tables[dnx_data_fc_oob_table_tx_freq].values[0].name = "ratio";
    submodule_data->tables[dnx_data_fc_oob_table_tx_freq].values[0].type = "int";
    submodule_data->tables[dnx_data_fc_oob_table_tx_freq].values[0].doc = "";
    submodule_data->tables[dnx_data_fc_oob_table_tx_freq].values[0].offset = UTILEX_OFFSETOF(dnx_data_fc_oob_tx_freq_t, ratio);

    
    submodule_data->tables[dnx_data_fc_oob_table_port].name = "port";
    submodule_data->tables[dnx_data_fc_oob_table_port].doc = "";
    submodule_data->tables[dnx_data_fc_oob_table_port].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_fc_oob_table_port].size_of_values = sizeof(dnx_data_fc_oob_port_t);
    submodule_data->tables[dnx_data_fc_oob_table_port].entry_get = dnx_data_fc_oob_port_entry_str_get;

    
    submodule_data->tables[dnx_data_fc_oob_table_port].nof_keys = 1;
    submodule_data->tables[dnx_data_fc_oob_table_port].keys[0].name = "oob_id";
    submodule_data->tables[dnx_data_fc_oob_table_port].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_fc_oob_table_port].nof_values = 2;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_fc_oob_table_port].values, dnxc_data_value_t, submodule_data->tables[dnx_data_fc_oob_table_port].nof_values, "_dnx_data_fc_oob_table_port table values");
    submodule_data->tables[dnx_data_fc_oob_table_port].values[0].name = "type";
    submodule_data->tables[dnx_data_fc_oob_table_port].values[0].type = "int";
    submodule_data->tables[dnx_data_fc_oob_table_port].values[0].doc = "";
    submodule_data->tables[dnx_data_fc_oob_table_port].values[0].offset = UTILEX_OFFSETOF(dnx_data_fc_oob_port_t, type);
    submodule_data->tables[dnx_data_fc_oob_table_port].values[1].name = "mode";
    submodule_data->tables[dnx_data_fc_oob_table_port].values[1].type = "int";
    submodule_data->tables[dnx_data_fc_oob_table_port].values[1].doc = "";
    submodule_data->tables[dnx_data_fc_oob_table_port].values[1].offset = UTILEX_OFFSETOF(dnx_data_fc_oob_port_t, mode);

    
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].name = "indication_invert";
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].doc = "";
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].size_of_values = sizeof(dnx_data_fc_oob_indication_invert_t);
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].entry_get = dnx_data_fc_oob_indication_invert_entry_str_get;

    
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].nof_keys = 1;
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].keys[0].name = "oob_id";
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].nof_values = 3;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_fc_oob_table_indication_invert].values, dnxc_data_value_t, submodule_data->tables[dnx_data_fc_oob_table_indication_invert].nof_values, "_dnx_data_fc_oob_table_indication_invert table values");
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].values[0].name = "ilkn_tx";
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].values[0].type = "int";
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].values[0].doc = "";
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].values[0].offset = UTILEX_OFFSETOF(dnx_data_fc_oob_indication_invert_t, ilkn_tx);
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].values[1].name = "ilkn_rx";
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].values[1].type = "int";
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].values[1].doc = "";
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].values[1].offset = UTILEX_OFFSETOF(dnx_data_fc_oob_indication_invert_t, ilkn_rx);
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].values[2].name = "spi";
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].values[2].type = "int";
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].values[2].doc = "";
    submodule_data->tables[dnx_data_fc_oob_table_indication_invert].values[2].offset = UTILEX_OFFSETOF(dnx_data_fc_oob_indication_invert_t, spi);


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_fc_oob_feature_get(
    int unit,
    dnx_data_fc_oob_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_oob, feature);
}


uint32
dnx_data_fc_oob_nof_oob_ids_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_oob, dnx_data_fc_oob_define_nof_oob_ids);
}



const dnx_data_fc_oob_calender_length_t *
dnx_data_fc_oob_calender_length_get(
    int unit,
    int oob_id)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_oob, dnx_data_fc_oob_table_calender_length);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, oob_id, 0);
    return (const dnx_data_fc_oob_calender_length_t *) data;

}

const dnx_data_fc_oob_calender_rep_count_t *
dnx_data_fc_oob_calender_rep_count_get(
    int unit,
    int oob_id)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_oob, dnx_data_fc_oob_table_calender_rep_count);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, oob_id, 0);
    return (const dnx_data_fc_oob_calender_rep_count_t *) data;

}

const dnx_data_fc_oob_tx_freq_t *
dnx_data_fc_oob_tx_freq_get(
    int unit,
    int oob_id)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_oob, dnx_data_fc_oob_table_tx_freq);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, oob_id, 0);
    return (const dnx_data_fc_oob_tx_freq_t *) data;

}

const dnx_data_fc_oob_port_t *
dnx_data_fc_oob_port_get(
    int unit,
    int oob_id)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_oob, dnx_data_fc_oob_table_port);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, oob_id, 0);
    return (const dnx_data_fc_oob_port_t *) data;

}

const dnx_data_fc_oob_indication_invert_t *
dnx_data_fc_oob_indication_invert_get(
    int unit,
    int oob_id)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_oob, dnx_data_fc_oob_table_indication_invert);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, oob_id, 0);
    return (const dnx_data_fc_oob_indication_invert_t *) data;

}


shr_error_e
dnx_data_fc_oob_calender_length_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_fc_oob_calender_length_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_oob, dnx_data_fc_oob_table_calender_length);
    data = (const dnx_data_fc_oob_calender_length_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->tx);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->rx);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_fc_oob_calender_rep_count_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_fc_oob_calender_rep_count_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_oob, dnx_data_fc_oob_table_calender_rep_count);
    data = (const dnx_data_fc_oob_calender_rep_count_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->tx);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->rx);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_fc_oob_tx_freq_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_fc_oob_tx_freq_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_oob, dnx_data_fc_oob_table_tx_freq);
    data = (const dnx_data_fc_oob_tx_freq_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->ratio);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_fc_oob_port_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_fc_oob_port_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_oob, dnx_data_fc_oob_table_port);
    data = (const dnx_data_fc_oob_port_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->type);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->mode);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_fc_oob_indication_invert_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_fc_oob_indication_invert_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_oob, dnx_data_fc_oob_table_indication_invert);
    data = (const dnx_data_fc_oob_indication_invert_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->ilkn_tx);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->ilkn_rx);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->spi);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnx_data_fc_oob_calender_length_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_oob, dnx_data_fc_oob_table_calender_length);

}

const dnxc_data_table_info_t *
dnx_data_fc_oob_calender_rep_count_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_oob, dnx_data_fc_oob_table_calender_rep_count);

}

const dnxc_data_table_info_t *
dnx_data_fc_oob_tx_freq_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_oob, dnx_data_fc_oob_table_tx_freq);

}

const dnxc_data_table_info_t *
dnx_data_fc_oob_port_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_oob, dnx_data_fc_oob_table_port);

}

const dnxc_data_table_info_t *
dnx_data_fc_oob_indication_invert_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_oob, dnx_data_fc_oob_table_indication_invert);

}






static shr_error_e
dnx_data_fc_inband_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "inband";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_fc_inband_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data fc inband features");

    
    submodule_data->nof_defines = _dnx_data_fc_inband_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data fc inband defines");

    submodule_data->defines[dnx_data_fc_inband_define_nof_inband_intlkn_cal_instances].name = "nof_inband_intlkn_cal_instances";
    submodule_data->defines[dnx_data_fc_inband_define_nof_inband_intlkn_cal_instances].doc = "";
    
    submodule_data->defines[dnx_data_fc_inband_define_nof_inband_intlkn_cal_instances].flags |= DNXC_DATA_F_DEFINE;

    
    submodule_data->nof_tables = _dnx_data_fc_inband_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data fc inband tables");

    
    submodule_data->tables[dnx_data_fc_inband_table_calender_length].name = "calender_length";
    submodule_data->tables[dnx_data_fc_inband_table_calender_length].doc = "";
    submodule_data->tables[dnx_data_fc_inband_table_calender_length].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_fc_inband_table_calender_length].size_of_values = sizeof(dnx_data_fc_inband_calender_length_t);
    submodule_data->tables[dnx_data_fc_inband_table_calender_length].entry_get = dnx_data_fc_inband_calender_length_entry_str_get;

    
    submodule_data->tables[dnx_data_fc_inband_table_calender_length].nof_keys = 1;
    submodule_data->tables[dnx_data_fc_inband_table_calender_length].keys[0].name = "ilkn_id";
    submodule_data->tables[dnx_data_fc_inband_table_calender_length].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_fc_inband_table_calender_length].nof_values = 2;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_fc_inband_table_calender_length].values, dnxc_data_value_t, submodule_data->tables[dnx_data_fc_inband_table_calender_length].nof_values, "_dnx_data_fc_inband_table_calender_length table values");
    submodule_data->tables[dnx_data_fc_inband_table_calender_length].values[0].name = "tx";
    submodule_data->tables[dnx_data_fc_inband_table_calender_length].values[0].type = "int";
    submodule_data->tables[dnx_data_fc_inband_table_calender_length].values[0].doc = "";
    submodule_data->tables[dnx_data_fc_inband_table_calender_length].values[0].offset = UTILEX_OFFSETOF(dnx_data_fc_inband_calender_length_t, tx);
    submodule_data->tables[dnx_data_fc_inband_table_calender_length].values[1].name = "rx";
    submodule_data->tables[dnx_data_fc_inband_table_calender_length].values[1].type = "int";
    submodule_data->tables[dnx_data_fc_inband_table_calender_length].values[1].doc = "";
    submodule_data->tables[dnx_data_fc_inband_table_calender_length].values[1].offset = UTILEX_OFFSETOF(dnx_data_fc_inband_calender_length_t, rx);

    
    submodule_data->tables[dnx_data_fc_inband_table_port].name = "port";
    submodule_data->tables[dnx_data_fc_inband_table_port].doc = "";
    submodule_data->tables[dnx_data_fc_inband_table_port].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_fc_inband_table_port].size_of_values = sizeof(dnx_data_fc_inband_port_t);
    submodule_data->tables[dnx_data_fc_inband_table_port].entry_get = dnx_data_fc_inband_port_entry_str_get;

    
    submodule_data->tables[dnx_data_fc_inband_table_port].nof_keys = 1;
    submodule_data->tables[dnx_data_fc_inband_table_port].keys[0].name = "ilkn_id";
    submodule_data->tables[dnx_data_fc_inband_table_port].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_fc_inband_table_port].nof_values = 2;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_fc_inband_table_port].values, dnxc_data_value_t, submodule_data->tables[dnx_data_fc_inband_table_port].nof_values, "_dnx_data_fc_inband_table_port table values");
    submodule_data->tables[dnx_data_fc_inband_table_port].values[0].name = "mode";
    submodule_data->tables[dnx_data_fc_inband_table_port].values[0].type = "int";
    submodule_data->tables[dnx_data_fc_inband_table_port].values[0].doc = "";
    submodule_data->tables[dnx_data_fc_inband_table_port].values[0].offset = UTILEX_OFFSETOF(dnx_data_fc_inband_port_t, mode);
    submodule_data->tables[dnx_data_fc_inband_table_port].values[1].name = "llfc_mode";
    submodule_data->tables[dnx_data_fc_inband_table_port].values[1].type = "int";
    submodule_data->tables[dnx_data_fc_inband_table_port].values[1].doc = "";
    submodule_data->tables[dnx_data_fc_inband_table_port].values[1].offset = UTILEX_OFFSETOF(dnx_data_fc_inband_port_t, llfc_mode);


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_fc_inband_feature_get(
    int unit,
    dnx_data_fc_inband_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_inband, feature);
}


uint32
dnx_data_fc_inband_nof_inband_intlkn_cal_instances_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_inband, dnx_data_fc_inband_define_nof_inband_intlkn_cal_instances);
}



const dnx_data_fc_inband_calender_length_t *
dnx_data_fc_inband_calender_length_get(
    int unit,
    int ilkn_id)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_inband, dnx_data_fc_inband_table_calender_length);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, ilkn_id, 0);
    return (const dnx_data_fc_inband_calender_length_t *) data;

}

const dnx_data_fc_inband_port_t *
dnx_data_fc_inband_port_get(
    int unit,
    int ilkn_id)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_inband, dnx_data_fc_inband_table_port);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, ilkn_id, 0);
    return (const dnx_data_fc_inband_port_t *) data;

}


shr_error_e
dnx_data_fc_inband_calender_length_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_fc_inband_calender_length_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_inband, dnx_data_fc_inband_table_calender_length);
    data = (const dnx_data_fc_inband_calender_length_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->tx);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->rx);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_fc_inband_port_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_fc_inband_port_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_inband, dnx_data_fc_inband_table_port);
    data = (const dnx_data_fc_inband_port_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->mode);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->llfc_mode);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnx_data_fc_inband_calender_length_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_inband, dnx_data_fc_inband_table_calender_length);

}

const dnxc_data_table_info_t *
dnx_data_fc_inband_port_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_inband, dnx_data_fc_inband_table_port);

}






static shr_error_e
dnx_data_fc_pfc_deadlock_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "pfc_deadlock";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_fc_pfc_deadlock_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data fc pfc_deadlock features");

    
    submodule_data->nof_defines = _dnx_data_fc_pfc_deadlock_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data fc pfc_deadlock defines");

    submodule_data->defines[dnx_data_fc_pfc_deadlock_define_cdum_intr_id].name = "cdum_intr_id";
    submodule_data->defines[dnx_data_fc_pfc_deadlock_define_cdum_intr_id].doc = "";
    
    submodule_data->defines[dnx_data_fc_pfc_deadlock_define_cdum_intr_id].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_fc_pfc_deadlock_define_cdu_intr_id].name = "cdu_intr_id";
    submodule_data->defines[dnx_data_fc_pfc_deadlock_define_cdu_intr_id].doc = "";
    
    submodule_data->defines[dnx_data_fc_pfc_deadlock_define_cdu_intr_id].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_fc_pfc_deadlock_define_clu_intr_id].name = "clu_intr_id";
    submodule_data->defines[dnx_data_fc_pfc_deadlock_define_clu_intr_id].doc = "";
    
    submodule_data->defines[dnx_data_fc_pfc_deadlock_define_clu_intr_id].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_fc_pfc_deadlock_define_nof_bits_in_port_num].name = "nof_bits_in_port_num";
    submodule_data->defines[dnx_data_fc_pfc_deadlock_define_nof_bits_in_port_num].doc = "";
    
    submodule_data->defines[dnx_data_fc_pfc_deadlock_define_nof_bits_in_port_num].flags |= DNXC_DATA_F_DEFINE;

    
    submodule_data->nof_tables = _dnx_data_fc_pfc_deadlock_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data fc pfc_deadlock tables");


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_fc_pfc_deadlock_feature_get(
    int unit,
    dnx_data_fc_pfc_deadlock_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_pfc_deadlock, feature);
}


uint32
dnx_data_fc_pfc_deadlock_cdum_intr_id_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_pfc_deadlock, dnx_data_fc_pfc_deadlock_define_cdum_intr_id);
}

uint32
dnx_data_fc_pfc_deadlock_cdu_intr_id_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_pfc_deadlock, dnx_data_fc_pfc_deadlock_define_cdu_intr_id);
}

uint32
dnx_data_fc_pfc_deadlock_clu_intr_id_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_pfc_deadlock, dnx_data_fc_pfc_deadlock_define_clu_intr_id);
}

uint32
dnx_data_fc_pfc_deadlock_nof_bits_in_port_num_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_fc, dnx_data_fc_submodule_pfc_deadlock, dnx_data_fc_pfc_deadlock_define_nof_bits_in_port_num);
}







shr_error_e
dnx_data_fc_init(
    int unit,
    dnxc_data_module_t *module_data)
{
    SHR_FUNC_INIT_VARS(unit);

    
    module_data->name = "fc";
    module_data->nof_submodules = _dnx_data_fc_submodule_nof;
    DNXC_DATA_ALLOC(module_data->submodules, dnxc_data_submodule_t, module_data->nof_submodules, "_dnxc_data fc submodules");

    
    SHR_IF_ERR_EXIT(dnx_data_fc_general_init(unit, &module_data->submodules[dnx_data_fc_submodule_general]));
    SHR_IF_ERR_EXIT(dnx_data_fc_calendar_common_init(unit, &module_data->submodules[dnx_data_fc_submodule_calendar_common]));
    SHR_IF_ERR_EXIT(dnx_data_fc_coe_init(unit, &module_data->submodules[dnx_data_fc_submodule_coe]));
    SHR_IF_ERR_EXIT(dnx_data_fc_oob_init(unit, &module_data->submodules[dnx_data_fc_submodule_oob]));
    SHR_IF_ERR_EXIT(dnx_data_fc_inband_init(unit, &module_data->submodules[dnx_data_fc_submodule_inband]));
    SHR_IF_ERR_EXIT(dnx_data_fc_pfc_deadlock_init(unit, &module_data->submodules[dnx_data_fc_submodule_pfc_deadlock]));
    

    if (dnxc_data_mgmt_is_jr2_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_fc_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_jr2_b0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_fc_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_jr2_b1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_fc_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2c_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_fc_attach(unit));
        SHR_IF_ERR_EXIT(j2c_a0_data_fc_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2c_a1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_fc_attach(unit));
        SHR_IF_ERR_EXIT(j2c_a0_data_fc_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_q2a_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_fc_attach(unit));
        SHR_IF_ERR_EXIT(q2a_a0_data_fc_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_q2a_b0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_fc_attach(unit));
        SHR_IF_ERR_EXIT(q2a_a0_data_fc_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_q2a_b1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_fc_attach(unit));
        SHR_IF_ERR_EXIT(q2a_a0_data_fc_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2p_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_fc_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a0_data_fc_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2p_a1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_fc_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a0_data_fc_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2p_a2(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_fc_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a0_data_fc_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2x_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_fc_attach(unit));
        SHR_IF_ERR_EXIT(j2x_a0_data_fc_attach(unit));
    }
    else

    {
        SHR_EXIT();
    }

exit:
    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


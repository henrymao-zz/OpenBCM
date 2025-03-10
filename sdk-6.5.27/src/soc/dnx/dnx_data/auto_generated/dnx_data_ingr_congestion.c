
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_COSQ

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_ingr_congestion.h>




extern shr_error_e jr2_a0_data_ingr_congestion_attach(
    int unit);


extern shr_error_e jr2_b0_data_ingr_congestion_attach(
    int unit);


extern shr_error_e j2c_a0_data_ingr_congestion_attach(
    int unit);


extern shr_error_e j2c_a1_data_ingr_congestion_attach(
    int unit);


extern shr_error_e q2a_a0_data_ingr_congestion_attach(
    int unit);


extern shr_error_e j2p_a0_data_ingr_congestion_attach(
    int unit);


extern shr_error_e j2x_a0_data_ingr_congestion_attach(
    int unit);




static shr_error_e
dnx_data_ingr_congestion_config_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "config";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_ingr_congestion_config_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data ingr_congestion config features");

    submodule_data->features[dnx_data_ingr_congestion_config_pp_port_by_reassembly_overwrite].name = "pp_port_by_reassembly_overwrite";
    submodule_data->features[dnx_data_ingr_congestion_config_pp_port_by_reassembly_overwrite].doc = "";
    submodule_data->features[dnx_data_ingr_congestion_config_pp_port_by_reassembly_overwrite].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_ingr_congestion_config_inband_telemetry_ftmh_extension_eco_fix].name = "inband_telemetry_ftmh_extension_eco_fix";
    submodule_data->features[dnx_data_ingr_congestion_config_inband_telemetry_ftmh_extension_eco_fix].doc = "";
    submodule_data->features[dnx_data_ingr_congestion_config_inband_telemetry_ftmh_extension_eco_fix].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnx_data_ingr_congestion_config_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data ingr_congestion config defines");

    submodule_data->defines[dnx_data_ingr_congestion_config_define_guarantee_mode].name = "guarantee_mode";
    submodule_data->defines[dnx_data_ingr_congestion_config_define_guarantee_mode].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_config_define_guarantee_mode].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_config_define_wred_packet_size].name = "wred_packet_size";
    submodule_data->defines[dnx_data_ingr_congestion_config_define_wred_packet_size].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_config_define_wred_packet_size].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_ingr_congestion_config_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data ingr_congestion config tables");


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_ingr_congestion_config_feature_get(
    int unit,
    dnx_data_ingr_congestion_config_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_config, feature);
}


uint32
dnx_data_ingr_congestion_config_guarantee_mode_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_config, dnx_data_ingr_congestion_config_define_guarantee_mode);
}

uint32
dnx_data_ingr_congestion_config_wred_packet_size_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_config, dnx_data_ingr_congestion_config_define_wred_packet_size);
}










static shr_error_e
dnx_data_ingr_congestion_info_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "info";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_ingr_congestion_info_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data ingr_congestion info features");

    submodule_data->features[dnx_data_ingr_congestion_info_soft_dram_block_supported].name = "soft_dram_block_supported";
    submodule_data->features[dnx_data_ingr_congestion_info_soft_dram_block_supported].doc = "";
    submodule_data->features[dnx_data_ingr_congestion_info_soft_dram_block_supported].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_ingr_congestion_info_cgm_hw_support].name = "cgm_hw_support";
    submodule_data->features[dnx_data_ingr_congestion_info_cgm_hw_support].doc = "";
    submodule_data->features[dnx_data_ingr_congestion_info_cgm_hw_support].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_ingr_congestion_info_global_ecn_marking_supported].name = "global_ecn_marking_supported";
    submodule_data->features[dnx_data_ingr_congestion_info_global_ecn_marking_supported].doc = "";
    submodule_data->features[dnx_data_ingr_congestion_info_global_ecn_marking_supported].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_ingr_congestion_info_wred_c1_high_precision_supported].name = "wred_c1_high_precision_supported";
    submodule_data->features[dnx_data_ingr_congestion_info_wred_c1_high_precision_supported].doc = "";
    submodule_data->features[dnx_data_ingr_congestion_info_wred_c1_high_precision_supported].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_ingr_congestion_info_wred_continuous_probabilty_supported].name = "wred_continuous_probabilty_supported";
    submodule_data->features[dnx_data_ingr_congestion_info_wred_continuous_probabilty_supported].doc = "";
    submodule_data->features[dnx_data_ingr_congestion_info_wred_continuous_probabilty_supported].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnx_data_ingr_congestion_info_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data ingr_congestion info defines");

    submodule_data->defines[dnx_data_ingr_congestion_info_define_threshold_granularity].name = "threshold_granularity";
    submodule_data->defines[dnx_data_ingr_congestion_info_define_threshold_granularity].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_info_define_threshold_granularity].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_info_define_words_resolution].name = "words_resolution";
    submodule_data->defines[dnx_data_ingr_congestion_info_define_words_resolution].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_info_define_words_resolution].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_info_define_bytes_threshold_granularity].name = "bytes_threshold_granularity";
    submodule_data->defines[dnx_data_ingr_congestion_info_define_bytes_threshold_granularity].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_info_define_bytes_threshold_granularity].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_info_define_nof_dropped_reasons_cgm].name = "nof_dropped_reasons_cgm";
    submodule_data->defines[dnx_data_ingr_congestion_info_define_nof_dropped_reasons_cgm].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_info_define_nof_dropped_reasons_cgm].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_info_define_wred_max_gain].name = "wred_max_gain";
    submodule_data->defines[dnx_data_ingr_congestion_info_define_wred_max_gain].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_info_define_wred_max_gain].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_info_define_wred_granularity].name = "wred_granularity";
    submodule_data->defines[dnx_data_ingr_congestion_info_define_wred_granularity].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_info_define_wred_granularity].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_info_define_nof_pds_in_pdb].name = "nof_pds_in_pdb";
    submodule_data->defines[dnx_data_ingr_congestion_info_define_nof_pds_in_pdb].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_info_define_nof_pds_in_pdb].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_info_define_max_jumbo_packet_size].name = "max_jumbo_packet_size";
    submodule_data->defines[dnx_data_ingr_congestion_info_define_max_jumbo_packet_size].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_info_define_max_jumbo_packet_size].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_info_define_max_sram_pdbs].name = "max_sram_pdbs";
    submodule_data->defines[dnx_data_ingr_congestion_info_define_max_sram_pdbs].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_info_define_max_sram_pdbs].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_info_define_max_dram_bdbs].name = "max_dram_bdbs";
    submodule_data->defines[dnx_data_ingr_congestion_info_define_max_dram_bdbs].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_info_define_max_dram_bdbs].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_info_define_max_total_bytes].name = "max_total_bytes";
    submodule_data->defines[dnx_data_ingr_congestion_info_define_max_total_bytes].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_info_define_max_total_bytes].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_info_define_nof_active_drams].name = "nof_active_drams";
    submodule_data->defines[dnx_data_ingr_congestion_info_define_nof_active_drams].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_info_define_nof_active_drams].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_info_define_total_bytes].name = "total_bytes";
    submodule_data->defines[dnx_data_ingr_congestion_info_define_total_bytes].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_info_define_total_bytes].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_ingr_congestion_info_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data ingr_congestion info tables");

    
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].name = "resource";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].size_of_values = sizeof(dnx_data_ingr_congestion_info_resource_t);
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].entry_get = dnx_data_ingr_congestion_info_resource_entry_str_get;

    
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].nof_keys = 1;
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].keys[0].name = "type";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].nof_values = 5;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values, dnxc_data_value_t, submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].nof_values, "_dnx_data_ingr_congestion_info_table_resource table values");
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[0].name = "max";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[0].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[0].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[0].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_info_resource_t, max);
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[1].name = "hw_resolution_max";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[1].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[1].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[1].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_info_resource_t, hw_resolution_max);
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[2].name = "hw_resolution_nof_bits";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[2].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[2].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[2].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_info_resource_t, hw_resolution_nof_bits);
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[3].name = "fadt_alpha_min";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[3].type = "int";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[3].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[3].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_info_resource_t, fadt_alpha_min);
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[4].name = "fadt_alpha_max";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[4].type = "int";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[4].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_resource].values[4].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_info_resource_t, fadt_alpha_max);

    
    submodule_data->tables[dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop].name = "dp_free_res_presentage_drop";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop].size_of_values = sizeof(dnx_data_ingr_congestion_info_dp_free_res_presentage_drop_t);
    submodule_data->tables[dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop].entry_get = dnx_data_ingr_congestion_info_dp_free_res_presentage_drop_entry_str_get;

    
    submodule_data->tables[dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop].nof_keys = 1;
    submodule_data->tables[dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop].keys[0].name = "dp";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop].values, dnxc_data_value_t, submodule_data->tables[dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop].nof_values, "_dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop table values");
    submodule_data->tables[dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop].values[0].name = "drop_precentage";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop].values[0].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop].values[0].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop].values[0].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_info_dp_free_res_presentage_drop_t, drop_precentage);

    
    submodule_data->tables[dnx_data_ingr_congestion_info_table_admission_preferences].name = "admission_preferences";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_admission_preferences].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_admission_preferences].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_ingr_congestion_info_table_admission_preferences].size_of_values = sizeof(dnx_data_ingr_congestion_info_admission_preferences_t);
    submodule_data->tables[dnx_data_ingr_congestion_info_table_admission_preferences].entry_get = dnx_data_ingr_congestion_info_admission_preferences_entry_str_get;

    
    submodule_data->tables[dnx_data_ingr_congestion_info_table_admission_preferences].nof_keys = 1;
    submodule_data->tables[dnx_data_ingr_congestion_info_table_admission_preferences].keys[0].name = "dp";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_admission_preferences].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_ingr_congestion_info_table_admission_preferences].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_ingr_congestion_info_table_admission_preferences].values, dnxc_data_value_t, submodule_data->tables[dnx_data_ingr_congestion_info_table_admission_preferences].nof_values, "_dnx_data_ingr_congestion_info_table_admission_preferences table values");
    submodule_data->tables[dnx_data_ingr_congestion_info_table_admission_preferences].values[0].name = "is_guarantee_over_admit";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_admission_preferences].values[0].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_admission_preferences].values[0].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_info_table_admission_preferences].values[0].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_info_admission_preferences_t, is_guarantee_over_admit);


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_ingr_congestion_info_feature_get(
    int unit,
    dnx_data_ingr_congestion_info_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, feature);
}


uint32
dnx_data_ingr_congestion_info_threshold_granularity_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_define_threshold_granularity);
}

uint32
dnx_data_ingr_congestion_info_words_resolution_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_define_words_resolution);
}

uint32
dnx_data_ingr_congestion_info_bytes_threshold_granularity_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_define_bytes_threshold_granularity);
}

uint32
dnx_data_ingr_congestion_info_nof_dropped_reasons_cgm_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_define_nof_dropped_reasons_cgm);
}

uint32
dnx_data_ingr_congestion_info_wred_max_gain_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_define_wred_max_gain);
}

uint32
dnx_data_ingr_congestion_info_wred_granularity_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_define_wred_granularity);
}

uint32
dnx_data_ingr_congestion_info_nof_pds_in_pdb_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_define_nof_pds_in_pdb);
}

uint32
dnx_data_ingr_congestion_info_max_jumbo_packet_size_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_define_max_jumbo_packet_size);
}

uint32
dnx_data_ingr_congestion_info_max_sram_pdbs_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_define_max_sram_pdbs);
}

uint32
dnx_data_ingr_congestion_info_max_dram_bdbs_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_define_max_dram_bdbs);
}

uint32
dnx_data_ingr_congestion_info_max_total_bytes_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_define_max_total_bytes);
}

uint32
dnx_data_ingr_congestion_info_nof_active_drams_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_define_nof_active_drams);
}

uint32
dnx_data_ingr_congestion_info_total_bytes_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_define_total_bytes);
}



const dnx_data_ingr_congestion_info_resource_t *
dnx_data_ingr_congestion_info_resource_get(
    int unit,
    int type)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_table_resource);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, type, 0);
    return (const dnx_data_ingr_congestion_info_resource_t *) data;

}

const dnx_data_ingr_congestion_info_dp_free_res_presentage_drop_t *
dnx_data_ingr_congestion_info_dp_free_res_presentage_drop_get(
    int unit,
    int dp)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, dp, 0);
    return (const dnx_data_ingr_congestion_info_dp_free_res_presentage_drop_t *) data;

}

const dnx_data_ingr_congestion_info_admission_preferences_t *
dnx_data_ingr_congestion_info_admission_preferences_get(
    int unit,
    int dp)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_table_admission_preferences);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, dp, 0);
    return (const dnx_data_ingr_congestion_info_admission_preferences_t *) data;

}


shr_error_e
dnx_data_ingr_congestion_info_resource_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_ingr_congestion_info_resource_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_table_resource);
    data = (const dnx_data_ingr_congestion_info_resource_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->max);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->hw_resolution_max);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->hw_resolution_nof_bits);
            break;
        case 3:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->fadt_alpha_min);
            break;
        case 4:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->fadt_alpha_max);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_ingr_congestion_info_dp_free_res_presentage_drop_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_ingr_congestion_info_dp_free_res_presentage_drop_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop);
    data = (const dnx_data_ingr_congestion_info_dp_free_res_presentage_drop_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->drop_precentage);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_ingr_congestion_info_admission_preferences_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_ingr_congestion_info_admission_preferences_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_table_admission_preferences);
    data = (const dnx_data_ingr_congestion_info_admission_preferences_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->is_guarantee_over_admit);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnx_data_ingr_congestion_info_resource_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_table_resource);

}

const dnxc_data_table_info_t *
dnx_data_ingr_congestion_info_dp_free_res_presentage_drop_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_table_dp_free_res_presentage_drop);

}

const dnxc_data_table_info_t *
dnx_data_ingr_congestion_info_admission_preferences_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_info, dnx_data_ingr_congestion_info_table_admission_preferences);

}






static shr_error_e
dnx_data_ingr_congestion_fadt_tail_drop_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "fadt_tail_drop";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_ingr_congestion_fadt_tail_drop_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data ingr_congestion fadt_tail_drop features");

    
    submodule_data->nof_defines = _dnx_data_ingr_congestion_fadt_tail_drop_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data ingr_congestion fadt_tail_drop defines");

    submodule_data->defines[dnx_data_ingr_congestion_fadt_tail_drop_define_default_max_size_byte_threshold_for_ocb_only].name = "default_max_size_byte_threshold_for_ocb_only";
    submodule_data->defines[dnx_data_ingr_congestion_fadt_tail_drop_define_default_max_size_byte_threshold_for_ocb_only].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_fadt_tail_drop_define_default_max_size_byte_threshold_for_ocb_only].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_ingr_congestion_fadt_tail_drop_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data ingr_congestion fadt_tail_drop tables");


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_ingr_congestion_fadt_tail_drop_feature_get(
    int unit,
    dnx_data_ingr_congestion_fadt_tail_drop_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_fadt_tail_drop, feature);
}


uint32
dnx_data_ingr_congestion_fadt_tail_drop_default_max_size_byte_threshold_for_ocb_only_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_fadt_tail_drop, dnx_data_ingr_congestion_fadt_tail_drop_define_default_max_size_byte_threshold_for_ocb_only);
}










static shr_error_e
dnx_data_ingr_congestion_dram_bound_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "dram_bound";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_ingr_congestion_dram_bound_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data ingr_congestion dram_bound features");

    
    submodule_data->nof_defines = _dnx_data_ingr_congestion_dram_bound_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data ingr_congestion dram_bound defines");

    submodule_data->defines[dnx_data_ingr_congestion_dram_bound_define_fadt_alpha_min].name = "fadt_alpha_min";
    submodule_data->defines[dnx_data_ingr_congestion_dram_bound_define_fadt_alpha_min].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dram_bound_define_fadt_alpha_min].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_dram_bound_define_fadt_alpha_max].name = "fadt_alpha_max";
    submodule_data->defines[dnx_data_ingr_congestion_dram_bound_define_fadt_alpha_max].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dram_bound_define_fadt_alpha_max].flags |= DNXC_DATA_F_DEFINE;

    
    submodule_data->nof_tables = _dnx_data_ingr_congestion_dram_bound_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data ingr_congestion dram_bound tables");

    
    submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].name = "resource";
    submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].size_of_values = sizeof(dnx_data_ingr_congestion_dram_bound_resource_t);
    submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].entry_get = dnx_data_ingr_congestion_dram_bound_resource_entry_str_get;

    
    submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].nof_keys = 1;
    submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].keys[0].name = "type";
    submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].nof_values = 2;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].values, dnxc_data_value_t, submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].nof_values, "_dnx_data_ingr_congestion_dram_bound_table_resource table values");
    submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].values[0].name = "max";
    submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].values[0].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].values[0].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].values[0].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_dram_bound_resource_t, max);
    submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].values[1].name = "is_resource_range";
    submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].values[1].type = "int";
    submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].values[1].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_dram_bound_table_resource].values[1].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_dram_bound_resource_t, is_resource_range);


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_ingr_congestion_dram_bound_feature_get(
    int unit,
    dnx_data_ingr_congestion_dram_bound_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dram_bound, feature);
}


uint32
dnx_data_ingr_congestion_dram_bound_fadt_alpha_min_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dram_bound, dnx_data_ingr_congestion_dram_bound_define_fadt_alpha_min);
}

uint32
dnx_data_ingr_congestion_dram_bound_fadt_alpha_max_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dram_bound, dnx_data_ingr_congestion_dram_bound_define_fadt_alpha_max);
}



const dnx_data_ingr_congestion_dram_bound_resource_t *
dnx_data_ingr_congestion_dram_bound_resource_get(
    int unit,
    int type)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dram_bound, dnx_data_ingr_congestion_dram_bound_table_resource);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, type, 0);
    return (const dnx_data_ingr_congestion_dram_bound_resource_t *) data;

}


shr_error_e
dnx_data_ingr_congestion_dram_bound_resource_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_ingr_congestion_dram_bound_resource_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dram_bound, dnx_data_ingr_congestion_dram_bound_table_resource);
    data = (const dnx_data_ingr_congestion_dram_bound_resource_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->max);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->is_resource_range);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnx_data_ingr_congestion_dram_bound_resource_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dram_bound, dnx_data_ingr_congestion_dram_bound_table_resource);

}






static shr_error_e
dnx_data_ingr_congestion_voq_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "voq";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_ingr_congestion_voq_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data ingr_congestion voq features");

    
    submodule_data->nof_defines = _dnx_data_ingr_congestion_voq_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data ingr_congestion voq defines");

    submodule_data->defines[dnx_data_ingr_congestion_voq_define_nof_rate_class].name = "nof_rate_class";
    submodule_data->defines[dnx_data_ingr_congestion_voq_define_nof_rate_class].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_voq_define_nof_rate_class].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_voq_define_rate_class_nof_bits].name = "rate_class_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_voq_define_rate_class_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_voq_define_rate_class_nof_bits].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_voq_define_nof_compensation_profiles].name = "nof_compensation_profiles";
    submodule_data->defines[dnx_data_ingr_congestion_voq_define_nof_compensation_profiles].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_voq_define_nof_compensation_profiles].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_voq_define_default_compensation].name = "default_compensation";
    submodule_data->defines[dnx_data_ingr_congestion_voq_define_default_compensation].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_voq_define_default_compensation].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_voq_define_voq_congestion_notification_fifo_size].name = "voq_congestion_notification_fifo_size";
    submodule_data->defines[dnx_data_ingr_congestion_voq_define_voq_congestion_notification_fifo_size].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_voq_define_voq_congestion_notification_fifo_size].flags |= DNXC_DATA_F_DEFINE;

    
    submodule_data->nof_tables = _dnx_data_ingr_congestion_voq_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data ingr_congestion voq tables");


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_ingr_congestion_voq_feature_get(
    int unit,
    dnx_data_ingr_congestion_voq_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_voq, feature);
}


uint32
dnx_data_ingr_congestion_voq_nof_rate_class_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_voq, dnx_data_ingr_congestion_voq_define_nof_rate_class);
}

uint32
dnx_data_ingr_congestion_voq_rate_class_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_voq, dnx_data_ingr_congestion_voq_define_rate_class_nof_bits);
}

uint32
dnx_data_ingr_congestion_voq_nof_compensation_profiles_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_voq, dnx_data_ingr_congestion_voq_define_nof_compensation_profiles);
}

uint32
dnx_data_ingr_congestion_voq_default_compensation_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_voq, dnx_data_ingr_congestion_voq_define_default_compensation);
}

uint32
dnx_data_ingr_congestion_voq_voq_congestion_notification_fifo_size_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_voq, dnx_data_ingr_congestion_voq_define_voq_congestion_notification_fifo_size);
}










static shr_error_e
dnx_data_ingr_congestion_vsq_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "vsq";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_ingr_congestion_vsq_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data ingr_congestion vsq features");

    submodule_data->features[dnx_data_ingr_congestion_vsq_size_watermark_support].name = "size_watermark_support";
    submodule_data->features[dnx_data_ingr_congestion_vsq_size_watermark_support].doc = "";
    submodule_data->features[dnx_data_ingr_congestion_vsq_size_watermark_support].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_ingr_congestion_vsq_colorless_guaranteed_support].name = "colorless_guaranteed_support";
    submodule_data->features[dnx_data_ingr_congestion_vsq_colorless_guaranteed_support].doc = "";
    submodule_data->features[dnx_data_ingr_congestion_vsq_colorless_guaranteed_support].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_ingr_congestion_vsq_vsq_with_id_on_nif_port_support].name = "vsq_with_id_on_nif_port_support";
    submodule_data->features[dnx_data_ingr_congestion_vsq_vsq_with_id_on_nif_port_support].doc = "";
    submodule_data->features[dnx_data_ingr_congestion_vsq_vsq_with_id_on_nif_port_support].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnx_data_ingr_congestion_vsq_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data ingr_congestion vsq defines");

    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_rate_class_nof].name = "vsq_rate_class_nof";
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_rate_class_nof].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_rate_class_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_a_rate_class_nof].name = "vsq_a_rate_class_nof";
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_a_rate_class_nof].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_a_rate_class_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_a_nof].name = "vsq_a_nof";
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_a_nof].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_a_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_b_nof].name = "vsq_b_nof";
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_b_nof].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_b_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_c_nof].name = "vsq_c_nof";
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_c_nof].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_c_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_d_nof].name = "vsq_d_nof";
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_d_nof].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_d_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_e_nof].name = "vsq_e_nof";
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_e_nof].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_e_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_e_hw_nof].name = "vsq_e_hw_nof";
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_e_hw_nof].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_e_hw_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_f_nof].name = "vsq_f_nof";
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_f_nof].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_f_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_f_hw_nof].name = "vsq_f_hw_nof";
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_f_hw_nof].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_f_hw_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_pool_nof].name = "pool_nof";
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_pool_nof].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_pool_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_connection_class_nof].name = "connection_class_nof";
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_connection_class_nof].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_connection_class_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_tc_pg_profile_nof].name = "tc_pg_profile_nof";
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_tc_pg_profile_nof].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_tc_pg_profile_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_e_congestion_notification_fifo_size].name = "vsq_e_congestion_notification_fifo_size";
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_e_congestion_notification_fifo_size].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_e_congestion_notification_fifo_size].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_f_congestion_notification_fifo_size].name = "vsq_f_congestion_notification_fifo_size";
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_f_congestion_notification_fifo_size].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_f_congestion_notification_fifo_size].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_oversubscription_bubble_width].name = "oversubscription_bubble_width";
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_oversubscription_bubble_width].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_oversubscription_bubble_width].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_e_default].name = "vsq_e_default";
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_e_default].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_e_default].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_f_default].name = "vsq_f_default";
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_f_default].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_vsq_define_vsq_f_default].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_ingr_congestion_vsq_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data ingr_congestion vsq tables");

    
    submodule_data->tables[dnx_data_ingr_congestion_vsq_table_info].name = "info";
    submodule_data->tables[dnx_data_ingr_congestion_vsq_table_info].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_vsq_table_info].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_ingr_congestion_vsq_table_info].size_of_values = sizeof(dnx_data_ingr_congestion_vsq_info_t);
    submodule_data->tables[dnx_data_ingr_congestion_vsq_table_info].entry_get = dnx_data_ingr_congestion_vsq_info_entry_str_get;

    
    submodule_data->tables[dnx_data_ingr_congestion_vsq_table_info].nof_keys = 1;
    submodule_data->tables[dnx_data_ingr_congestion_vsq_table_info].keys[0].name = "vsq_group";
    submodule_data->tables[dnx_data_ingr_congestion_vsq_table_info].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_ingr_congestion_vsq_table_info].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_ingr_congestion_vsq_table_info].values, dnxc_data_value_t, submodule_data->tables[dnx_data_ingr_congestion_vsq_table_info].nof_values, "_dnx_data_ingr_congestion_vsq_table_info table values");
    submodule_data->tables[dnx_data_ingr_congestion_vsq_table_info].values[0].name = "nof";
    submodule_data->tables[dnx_data_ingr_congestion_vsq_table_info].values[0].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_vsq_table_info].values[0].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_vsq_table_info].values[0].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_vsq_info_t, nof);


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_ingr_congestion_vsq_feature_get(
    int unit,
    dnx_data_ingr_congestion_vsq_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, feature);
}


uint32
dnx_data_ingr_congestion_vsq_vsq_rate_class_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_define_vsq_rate_class_nof);
}

uint32
dnx_data_ingr_congestion_vsq_vsq_a_rate_class_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_define_vsq_a_rate_class_nof);
}

uint32
dnx_data_ingr_congestion_vsq_vsq_a_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_define_vsq_a_nof);
}

uint32
dnx_data_ingr_congestion_vsq_vsq_b_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_define_vsq_b_nof);
}

uint32
dnx_data_ingr_congestion_vsq_vsq_c_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_define_vsq_c_nof);
}

uint32
dnx_data_ingr_congestion_vsq_vsq_d_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_define_vsq_d_nof);
}

uint32
dnx_data_ingr_congestion_vsq_vsq_e_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_define_vsq_e_nof);
}

uint32
dnx_data_ingr_congestion_vsq_vsq_e_hw_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_define_vsq_e_hw_nof);
}

uint32
dnx_data_ingr_congestion_vsq_vsq_f_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_define_vsq_f_nof);
}

uint32
dnx_data_ingr_congestion_vsq_vsq_f_hw_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_define_vsq_f_hw_nof);
}

uint32
dnx_data_ingr_congestion_vsq_pool_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_define_pool_nof);
}

uint32
dnx_data_ingr_congestion_vsq_connection_class_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_define_connection_class_nof);
}

uint32
dnx_data_ingr_congestion_vsq_tc_pg_profile_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_define_tc_pg_profile_nof);
}

uint32
dnx_data_ingr_congestion_vsq_vsq_e_congestion_notification_fifo_size_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_define_vsq_e_congestion_notification_fifo_size);
}

uint32
dnx_data_ingr_congestion_vsq_vsq_f_congestion_notification_fifo_size_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_define_vsq_f_congestion_notification_fifo_size);
}

uint32
dnx_data_ingr_congestion_vsq_oversubscription_bubble_width_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_define_oversubscription_bubble_width);
}

uint32
dnx_data_ingr_congestion_vsq_vsq_e_default_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_define_vsq_e_default);
}

uint32
dnx_data_ingr_congestion_vsq_vsq_f_default_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_define_vsq_f_default);
}



const dnx_data_ingr_congestion_vsq_info_t *
dnx_data_ingr_congestion_vsq_info_get(
    int unit,
    int vsq_group)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_table_info);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, vsq_group, 0);
    return (const dnx_data_ingr_congestion_vsq_info_t *) data;

}


shr_error_e
dnx_data_ingr_congestion_vsq_info_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_ingr_congestion_vsq_info_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_table_info);
    data = (const dnx_data_ingr_congestion_vsq_info_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->nof);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnx_data_ingr_congestion_vsq_info_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_vsq, dnx_data_ingr_congestion_vsq_table_info);

}






static shr_error_e
dnx_data_ingr_congestion_init_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "init";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_ingr_congestion_init_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data ingr_congestion init features");

    
    submodule_data->nof_defines = _dnx_data_ingr_congestion_init_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data ingr_congestion init defines");

    submodule_data->defines[dnx_data_ingr_congestion_init_define_fifo_size].name = "fifo_size";
    submodule_data->defines[dnx_data_ingr_congestion_init_define_fifo_size].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_init_define_fifo_size].flags |= DNXC_DATA_F_DEFINE;

    
    submodule_data->nof_tables = _dnx_data_ingr_congestion_init_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data ingr_congestion init tables");

    
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].name = "vsq_words_rjct_map";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].size_of_values = sizeof(dnx_data_ingr_congestion_init_vsq_words_rjct_map_t);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].entry_get = dnx_data_ingr_congestion_init_vsq_words_rjct_map_entry_str_get;

    
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].nof_keys = 1;
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].keys[0].name = "index";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].nof_values = 6;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values, dnxc_data_value_t, submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].nof_values, "_dnx_data_ingr_congestion_init_table_vsq_words_rjct_map table values");
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[0].name = "is_total_shared_blocked";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[0].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[0].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[0].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_vsq_words_rjct_map_t, is_total_shared_blocked);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[1].name = "is_port_pg_shared_blocked";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[1].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[1].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[1].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_vsq_words_rjct_map_t, is_port_pg_shared_blocked);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[2].name = "is_total_headroom_blocked";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[2].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[2].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[2].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_vsq_words_rjct_map_t, is_total_headroom_blocked);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[3].name = "is_port_pg_headroom_blocked";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[3].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[3].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[3].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_vsq_words_rjct_map_t, is_port_pg_headroom_blocked);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[4].name = "is_voq_in_guaranteed";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[4].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[4].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[4].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_vsq_words_rjct_map_t, is_voq_in_guaranteed);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[5].name = "vsq_guaranteed_status";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[5].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[5].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_words_rjct_map].values[5].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_vsq_words_rjct_map_t, vsq_guaranteed_status);

    
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].name = "vsq_sram_rjct_map";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].size_of_values = sizeof(dnx_data_ingr_congestion_init_vsq_sram_rjct_map_t);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].entry_get = dnx_data_ingr_congestion_init_vsq_sram_rjct_map_entry_str_get;

    
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].nof_keys = 1;
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].keys[0].name = "index";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].nof_values = 8;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values, dnxc_data_value_t, submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].nof_values, "_dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map table values");
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[0].name = "is_total_shared_blocked";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[0].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[0].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[0].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_vsq_sram_rjct_map_t, is_total_shared_blocked);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[1].name = "is_port_pg_shared_blocked";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[1].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[1].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[1].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_vsq_sram_rjct_map_t, is_port_pg_shared_blocked);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[2].name = "is_headroom_extension_blocked";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[2].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[2].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[2].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_vsq_sram_rjct_map_t, is_headroom_extension_blocked);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[3].name = "is_total_headroom_blocked";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[3].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[3].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[3].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_vsq_sram_rjct_map_t, is_total_headroom_blocked);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[4].name = "is_port_headroom_blocked";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[4].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[4].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[4].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_vsq_sram_rjct_map_t, is_port_headroom_blocked);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[5].name = "is_pg_headroom_blocked";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[5].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[5].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[5].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_vsq_sram_rjct_map_t, is_pg_headroom_blocked);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[6].name = "is_voq_in_guaranteed";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[6].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[6].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[6].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_vsq_sram_rjct_map_t, is_voq_in_guaranteed);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[7].name = "vsq_guaranteed_status";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[7].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[7].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map].values[7].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_vsq_sram_rjct_map_t, vsq_guaranteed_status);

    
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].name = "dp_global_sram_buffer_drop";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].size_of_values = sizeof(dnx_data_ingr_congestion_init_dp_global_sram_buffer_drop_t);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].entry_get = dnx_data_ingr_congestion_init_dp_global_sram_buffer_drop_entry_str_get;

    
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].nof_keys = 1;
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].keys[0].name = "dp";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].nof_values = 2;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].values, dnxc_data_value_t, submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].nof_values, "_dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop table values");
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].values[0].name = "set_threshold";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].values[0].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].values[0].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].values[0].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_dp_global_sram_buffer_drop_t, set_threshold);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].values[1].name = "clear_threshold";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].values[1].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].values[1].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop].values[1].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_dp_global_sram_buffer_drop_t, clear_threshold);

    
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].name = "dp_global_sram_pdb_drop";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].size_of_values = sizeof(dnx_data_ingr_congestion_init_dp_global_sram_pdb_drop_t);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].entry_get = dnx_data_ingr_congestion_init_dp_global_sram_pdb_drop_entry_str_get;

    
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].nof_keys = 1;
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].keys[0].name = "dp";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].nof_values = 2;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].values, dnxc_data_value_t, submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].nof_values, "_dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop table values");
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].values[0].name = "set_threshold";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].values[0].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].values[0].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].values[0].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_dp_global_sram_pdb_drop_t, set_threshold);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].values[1].name = "clear_threshold";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].values[1].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].values[1].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop].values[1].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_dp_global_sram_pdb_drop_t, clear_threshold);

    
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].name = "dp_global_dram_bdb_drop";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].size_of_values = sizeof(dnx_data_ingr_congestion_init_dp_global_dram_bdb_drop_t);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].entry_get = dnx_data_ingr_congestion_init_dp_global_dram_bdb_drop_entry_str_get;

    
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].nof_keys = 1;
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].keys[0].name = "dp";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].nof_values = 2;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].values, dnxc_data_value_t, submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].nof_values, "_dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop table values");
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].values[0].name = "set_threshold";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].values[0].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].values[0].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].values[0].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_dp_global_dram_bdb_drop_t, set_threshold);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].values[1].name = "clear_threshold";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].values[1].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].values[1].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop].values[1].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_dp_global_dram_bdb_drop_t, clear_threshold);

    
    submodule_data->tables[dnx_data_ingr_congestion_init_table_equivalent_global_drop].name = "equivalent_global_drop";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_equivalent_global_drop].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_equivalent_global_drop].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_ingr_congestion_init_table_equivalent_global_drop].size_of_values = sizeof(dnx_data_ingr_congestion_init_equivalent_global_drop_t);
    submodule_data->tables[dnx_data_ingr_congestion_init_table_equivalent_global_drop].entry_get = dnx_data_ingr_congestion_init_equivalent_global_drop_entry_str_get;

    
    submodule_data->tables[dnx_data_ingr_congestion_init_table_equivalent_global_drop].nof_keys = 1;
    submodule_data->tables[dnx_data_ingr_congestion_init_table_equivalent_global_drop].keys[0].name = "type";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_equivalent_global_drop].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_ingr_congestion_init_table_equivalent_global_drop].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_ingr_congestion_init_table_equivalent_global_drop].values, dnxc_data_value_t, submodule_data->tables[dnx_data_ingr_congestion_init_table_equivalent_global_drop].nof_values, "_dnx_data_ingr_congestion_init_table_equivalent_global_drop table values");
    submodule_data->tables[dnx_data_ingr_congestion_init_table_equivalent_global_drop].values[0].name = "drop";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_equivalent_global_drop].values[0].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_equivalent_global_drop].values[0].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_init_table_equivalent_global_drop].values[0].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_init_equivalent_global_drop_t, drop);


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_ingr_congestion_init_feature_get(
    int unit,
    dnx_data_ingr_congestion_init_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, feature);
}


uint32
dnx_data_ingr_congestion_init_fifo_size_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_define_fifo_size);
}



const dnx_data_ingr_congestion_init_vsq_words_rjct_map_t *
dnx_data_ingr_congestion_init_vsq_words_rjct_map_get(
    int unit,
    int index)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_table_vsq_words_rjct_map);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, index, 0);
    return (const dnx_data_ingr_congestion_init_vsq_words_rjct_map_t *) data;

}

const dnx_data_ingr_congestion_init_vsq_sram_rjct_map_t *
dnx_data_ingr_congestion_init_vsq_sram_rjct_map_get(
    int unit,
    int index)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, index, 0);
    return (const dnx_data_ingr_congestion_init_vsq_sram_rjct_map_t *) data;

}

const dnx_data_ingr_congestion_init_dp_global_sram_buffer_drop_t *
dnx_data_ingr_congestion_init_dp_global_sram_buffer_drop_get(
    int unit,
    int dp)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, dp, 0);
    return (const dnx_data_ingr_congestion_init_dp_global_sram_buffer_drop_t *) data;

}

const dnx_data_ingr_congestion_init_dp_global_sram_pdb_drop_t *
dnx_data_ingr_congestion_init_dp_global_sram_pdb_drop_get(
    int unit,
    int dp)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, dp, 0);
    return (const dnx_data_ingr_congestion_init_dp_global_sram_pdb_drop_t *) data;

}

const dnx_data_ingr_congestion_init_dp_global_dram_bdb_drop_t *
dnx_data_ingr_congestion_init_dp_global_dram_bdb_drop_get(
    int unit,
    int dp)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, dp, 0);
    return (const dnx_data_ingr_congestion_init_dp_global_dram_bdb_drop_t *) data;

}

const dnx_data_ingr_congestion_init_equivalent_global_drop_t *
dnx_data_ingr_congestion_init_equivalent_global_drop_get(
    int unit,
    int type)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_table_equivalent_global_drop);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, type, 0);
    return (const dnx_data_ingr_congestion_init_equivalent_global_drop_t *) data;

}


shr_error_e
dnx_data_ingr_congestion_init_vsq_words_rjct_map_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_ingr_congestion_init_vsq_words_rjct_map_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_table_vsq_words_rjct_map);
    data = (const dnx_data_ingr_congestion_init_vsq_words_rjct_map_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->is_total_shared_blocked);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->is_port_pg_shared_blocked);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->is_total_headroom_blocked);
            break;
        case 3:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->is_port_pg_headroom_blocked);
            break;
        case 4:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->is_voq_in_guaranteed);
            break;
        case 5:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->vsq_guaranteed_status);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_ingr_congestion_init_vsq_sram_rjct_map_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_ingr_congestion_init_vsq_sram_rjct_map_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map);
    data = (const dnx_data_ingr_congestion_init_vsq_sram_rjct_map_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->is_total_shared_blocked);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->is_port_pg_shared_blocked);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->is_headroom_extension_blocked);
            break;
        case 3:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->is_total_headroom_blocked);
            break;
        case 4:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->is_port_headroom_blocked);
            break;
        case 5:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->is_pg_headroom_blocked);
            break;
        case 6:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->is_voq_in_guaranteed);
            break;
        case 7:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->vsq_guaranteed_status);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_ingr_congestion_init_dp_global_sram_buffer_drop_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_ingr_congestion_init_dp_global_sram_buffer_drop_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop);
    data = (const dnx_data_ingr_congestion_init_dp_global_sram_buffer_drop_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->set_threshold);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->clear_threshold);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_ingr_congestion_init_dp_global_sram_pdb_drop_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_ingr_congestion_init_dp_global_sram_pdb_drop_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop);
    data = (const dnx_data_ingr_congestion_init_dp_global_sram_pdb_drop_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->set_threshold);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->clear_threshold);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_ingr_congestion_init_dp_global_dram_bdb_drop_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_ingr_congestion_init_dp_global_dram_bdb_drop_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop);
    data = (const dnx_data_ingr_congestion_init_dp_global_dram_bdb_drop_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->set_threshold);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->clear_threshold);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_ingr_congestion_init_equivalent_global_drop_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_ingr_congestion_init_equivalent_global_drop_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_table_equivalent_global_drop);
    data = (const dnx_data_ingr_congestion_init_equivalent_global_drop_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->drop);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnx_data_ingr_congestion_init_vsq_words_rjct_map_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_table_vsq_words_rjct_map);

}

const dnxc_data_table_info_t *
dnx_data_ingr_congestion_init_vsq_sram_rjct_map_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_table_vsq_sram_rjct_map);

}

const dnxc_data_table_info_t *
dnx_data_ingr_congestion_init_dp_global_sram_buffer_drop_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_table_dp_global_sram_buffer_drop);

}

const dnxc_data_table_info_t *
dnx_data_ingr_congestion_init_dp_global_sram_pdb_drop_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_table_dp_global_sram_pdb_drop);

}

const dnxc_data_table_info_t *
dnx_data_ingr_congestion_init_dp_global_dram_bdb_drop_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_table_dp_global_dram_bdb_drop);

}

const dnxc_data_table_info_t *
dnx_data_ingr_congestion_init_equivalent_global_drop_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_init, dnx_data_ingr_congestion_init_table_equivalent_global_drop);

}






static shr_error_e
dnx_data_ingr_congestion_dbal_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "dbal";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_ingr_congestion_dbal_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data ingr_congestion dbal features");

    submodule_data->features[dnx_data_ingr_congestion_dbal_fabric_and_dram_separate_dequeue_pkt_counters].name = "fabric_and_dram_separate_dequeue_pkt_counters";
    submodule_data->features[dnx_data_ingr_congestion_dbal_fabric_and_dram_separate_dequeue_pkt_counters].doc = "";
    submodule_data->features[dnx_data_ingr_congestion_dbal_fabric_and_dram_separate_dequeue_pkt_counters].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnx_data_ingr_congestion_dbal_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data ingr_congestion dbal defines");

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_admission_test_nof].name = "admission_test_nof";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_admission_test_nof].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_admission_test_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_dram_bdbs_th_nof_bits].name = "dram_bdbs_th_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_dram_bdbs_th_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_dram_bdbs_th_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_pdbs_th_nof_bits].name = "sram_pdbs_th_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_pdbs_th_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_pdbs_th_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffer_th_nof_bits].name = "sram_buffer_th_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffer_th_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffer_th_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffer_free_th_nof_bits].name = "sram_buffer_free_th_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffer_free_th_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffer_free_th_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_pds_th_nof_bits].name = "sram_pds_th_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_pds_th_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_pds_th_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_total_bytes_th_nof_bits].name = "total_bytes_th_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_total_bytes_th_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_total_bytes_th_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_dram_bdbs_nof_bits].name = "dram_bdbs_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_dram_bdbs_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_dram_bdbs_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_pdbs_nof_bits].name = "sram_pdbs_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_pdbs_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_pdbs_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffer_nof_bits].name = "sram_buffer_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffer_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffer_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sqm_debug_pkt_ctr_nof_bits].name = "sqm_debug_pkt_ctr_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sqm_debug_pkt_ctr_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sqm_debug_pkt_ctr_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffer_per_pool_nof_bits].name = "sram_buffer_per_pool_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffer_per_pool_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffer_per_pool_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_pds_per_pool_nof_bits].name = "sram_pds_per_pool_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_pds_per_pool_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_pds_per_pool_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_compensation_delta_nof_bits].name = "compensation_delta_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_compensation_delta_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_compensation_delta_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffer_size_voq_occupancy_nof_bits].name = "sram_buffer_size_voq_occupancy_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffer_size_voq_occupancy_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffer_size_voq_occupancy_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_size_in_words_sram_voq_occupancy_nof_bits].name = "size_in_words_sram_voq_occupancy_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_size_in_words_sram_voq_occupancy_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_size_in_words_sram_voq_occupancy_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_pds_size_occupancy_nof_bits].name = "sram_pds_size_occupancy_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_pds_size_occupancy_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_pds_size_occupancy_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffer_size_vsq_occupancy_nof_bits].name = "sram_buffer_size_vsq_occupancy_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffer_size_vsq_occupancy_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffer_size_vsq_occupancy_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_size_in_words_occupancy_nof_bits].name = "size_in_words_occupancy_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_size_in_words_occupancy_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_size_in_words_occupancy_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_dram_bounds_sram_words_th_nof_bits].name = "dram_bounds_sram_words_th_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_dram_bounds_sram_words_th_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_dram_bounds_sram_words_th_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffers_vsq_th_nof_bits].name = "sram_buffers_vsq_th_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffers_vsq_th_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_buffers_vsq_th_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_vsq_pds_th_nof_bits].name = "sram_vsq_pds_th_nof_bits";
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_vsq_pds_th_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_dbal_define_sram_vsq_pds_th_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_ingr_congestion_dbal_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data ingr_congestion dbal tables");

    
    submodule_data->tables[dnx_data_ingr_congestion_dbal_table_admission_bits_mapping].name = "admission_bits_mapping";
    submodule_data->tables[dnx_data_ingr_congestion_dbal_table_admission_bits_mapping].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_dbal_table_admission_bits_mapping].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_ingr_congestion_dbal_table_admission_bits_mapping].size_of_values = sizeof(dnx_data_ingr_congestion_dbal_admission_bits_mapping_t);
    submodule_data->tables[dnx_data_ingr_congestion_dbal_table_admission_bits_mapping].entry_get = dnx_data_ingr_congestion_dbal_admission_bits_mapping_entry_str_get;

    
    submodule_data->tables[dnx_data_ingr_congestion_dbal_table_admission_bits_mapping].nof_keys = 1;
    submodule_data->tables[dnx_data_ingr_congestion_dbal_table_admission_bits_mapping].keys[0].name = "rjct_bit";
    submodule_data->tables[dnx_data_ingr_congestion_dbal_table_admission_bits_mapping].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_ingr_congestion_dbal_table_admission_bits_mapping].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_ingr_congestion_dbal_table_admission_bits_mapping].values, dnxc_data_value_t, submodule_data->tables[dnx_data_ingr_congestion_dbal_table_admission_bits_mapping].nof_values, "_dnx_data_ingr_congestion_dbal_table_admission_bits_mapping table values");
    submodule_data->tables[dnx_data_ingr_congestion_dbal_table_admission_bits_mapping].values[0].name = "index";
    submodule_data->tables[dnx_data_ingr_congestion_dbal_table_admission_bits_mapping].values[0].type = "int";
    submodule_data->tables[dnx_data_ingr_congestion_dbal_table_admission_bits_mapping].values[0].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_dbal_table_admission_bits_mapping].values[0].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_dbal_admission_bits_mapping_t, index);


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_ingr_congestion_dbal_feature_get(
    int unit,
    dnx_data_ingr_congestion_dbal_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, feature);
}


uint32
dnx_data_ingr_congestion_dbal_admission_test_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_admission_test_nof);
}

uint32
dnx_data_ingr_congestion_dbal_dram_bdbs_th_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_dram_bdbs_th_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_sram_pdbs_th_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_sram_pdbs_th_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_sram_buffer_th_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_sram_buffer_th_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_sram_buffer_free_th_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_sram_buffer_free_th_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_sram_pds_th_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_sram_pds_th_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_total_bytes_th_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_total_bytes_th_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_dram_bdbs_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_dram_bdbs_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_sram_pdbs_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_sram_pdbs_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_sram_buffer_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_sram_buffer_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_sqm_debug_pkt_ctr_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_sqm_debug_pkt_ctr_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_sram_buffer_per_pool_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_sram_buffer_per_pool_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_sram_pds_per_pool_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_sram_pds_per_pool_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_compensation_delta_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_compensation_delta_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_sram_buffer_size_voq_occupancy_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_sram_buffer_size_voq_occupancy_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_size_in_words_sram_voq_occupancy_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_size_in_words_sram_voq_occupancy_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_sram_pds_size_occupancy_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_sram_pds_size_occupancy_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_sram_buffer_size_vsq_occupancy_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_sram_buffer_size_vsq_occupancy_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_size_in_words_occupancy_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_size_in_words_occupancy_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_dram_bounds_sram_words_th_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_dram_bounds_sram_words_th_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_sram_buffers_vsq_th_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_sram_buffers_vsq_th_nof_bits);
}

uint32
dnx_data_ingr_congestion_dbal_sram_vsq_pds_th_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_define_sram_vsq_pds_th_nof_bits);
}



const dnx_data_ingr_congestion_dbal_admission_bits_mapping_t *
dnx_data_ingr_congestion_dbal_admission_bits_mapping_get(
    int unit,
    int rjct_bit)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_table_admission_bits_mapping);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, rjct_bit, 0);
    return (const dnx_data_ingr_congestion_dbal_admission_bits_mapping_t *) data;

}


shr_error_e
dnx_data_ingr_congestion_dbal_admission_bits_mapping_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_ingr_congestion_dbal_admission_bits_mapping_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_table_admission_bits_mapping);
    data = (const dnx_data_ingr_congestion_dbal_admission_bits_mapping_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->index);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnx_data_ingr_congestion_dbal_admission_bits_mapping_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_dbal, dnx_data_ingr_congestion_dbal_table_admission_bits_mapping);

}






static shr_error_e
dnx_data_ingr_congestion_mirror_on_drop_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "mirror_on_drop";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_ingr_congestion_mirror_on_drop_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data ingr_congestion mirror_on_drop features");

    submodule_data->features[dnx_data_ingr_congestion_mirror_on_drop_is_supported].name = "is_supported";
    submodule_data->features[dnx_data_ingr_congestion_mirror_on_drop_is_supported].doc = "";
    submodule_data->features[dnx_data_ingr_congestion_mirror_on_drop_is_supported].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnx_data_ingr_congestion_mirror_on_drop_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data ingr_congestion mirror_on_drop defines");

    submodule_data->defines[dnx_data_ingr_congestion_mirror_on_drop_define_nof_groups].name = "nof_groups";
    submodule_data->defines[dnx_data_ingr_congestion_mirror_on_drop_define_nof_groups].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_mirror_on_drop_define_nof_groups].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_mirror_on_drop_define_aging_clocks_resolution].name = "aging_clocks_resolution";
    submodule_data->defines[dnx_data_ingr_congestion_mirror_on_drop_define_aging_clocks_resolution].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_mirror_on_drop_define_aging_clocks_resolution].flags |= DNXC_DATA_F_DEFINE;

    
    submodule_data->nof_tables = _dnx_data_ingr_congestion_mirror_on_drop_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data ingr_congestion mirror_on_drop tables");


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_ingr_congestion_mirror_on_drop_feature_get(
    int unit,
    dnx_data_ingr_congestion_mirror_on_drop_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_mirror_on_drop, feature);
}


uint32
dnx_data_ingr_congestion_mirror_on_drop_nof_groups_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_mirror_on_drop, dnx_data_ingr_congestion_mirror_on_drop_define_nof_groups);
}

uint32
dnx_data_ingr_congestion_mirror_on_drop_aging_clocks_resolution_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_mirror_on_drop, dnx_data_ingr_congestion_mirror_on_drop_define_aging_clocks_resolution);
}










static shr_error_e
dnx_data_ingr_congestion_sram_buffer_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "sram_buffer";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_ingr_congestion_sram_buffer_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data ingr_congestion sram_buffer features");

    
    submodule_data->nof_defines = _dnx_data_ingr_congestion_sram_buffer_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data ingr_congestion sram_buffer defines");

    submodule_data->defines[dnx_data_ingr_congestion_sram_buffer_define_nof_drop_profiles].name = "nof_drop_profiles";
    submodule_data->defines[dnx_data_ingr_congestion_sram_buffer_define_nof_drop_profiles].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_sram_buffer_define_nof_drop_profiles].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_ingr_congestion_sram_buffer_define_nof_drop_profiles_bits].name = "nof_drop_profiles_bits";
    submodule_data->defines[dnx_data_ingr_congestion_sram_buffer_define_nof_drop_profiles_bits].doc = "";
    
    submodule_data->defines[dnx_data_ingr_congestion_sram_buffer_define_nof_drop_profiles_bits].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_ingr_congestion_sram_buffer_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data ingr_congestion sram_buffer tables");

    
    submodule_data->tables[dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds].name = "drop_tresholds";
    submodule_data->tables[dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds].size_of_values = sizeof(dnx_data_ingr_congestion_sram_buffer_drop_tresholds_t);
    submodule_data->tables[dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds].entry_get = dnx_data_ingr_congestion_sram_buffer_drop_tresholds_entry_str_get;

    
    submodule_data->tables[dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds].nof_keys = 1;
    submodule_data->tables[dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds].keys[0].name = "index";
    submodule_data->tables[dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds].values, dnxc_data_value_t, submodule_data->tables[dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds].nof_values, "_dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds table values");
    submodule_data->tables[dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds].values[0].name = "value";
    submodule_data->tables[dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds].values[0].type = "uint32";
    submodule_data->tables[dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds].values[0].doc = "";
    submodule_data->tables[dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds].values[0].offset = UTILEX_OFFSETOF(dnx_data_ingr_congestion_sram_buffer_drop_tresholds_t, value);


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_ingr_congestion_sram_buffer_feature_get(
    int unit,
    dnx_data_ingr_congestion_sram_buffer_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_sram_buffer, feature);
}


uint32
dnx_data_ingr_congestion_sram_buffer_nof_drop_profiles_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_sram_buffer, dnx_data_ingr_congestion_sram_buffer_define_nof_drop_profiles);
}

uint32
dnx_data_ingr_congestion_sram_buffer_nof_drop_profiles_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_sram_buffer, dnx_data_ingr_congestion_sram_buffer_define_nof_drop_profiles_bits);
}



const dnx_data_ingr_congestion_sram_buffer_drop_tresholds_t *
dnx_data_ingr_congestion_sram_buffer_drop_tresholds_get(
    int unit,
    int index)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_sram_buffer, dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, index, 0);
    return (const dnx_data_ingr_congestion_sram_buffer_drop_tresholds_t *) data;

}


shr_error_e
dnx_data_ingr_congestion_sram_buffer_drop_tresholds_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_ingr_congestion_sram_buffer_drop_tresholds_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_sram_buffer, dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds);
    data = (const dnx_data_ingr_congestion_sram_buffer_drop_tresholds_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->value);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnx_data_ingr_congestion_sram_buffer_drop_tresholds_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_ingr_congestion, dnx_data_ingr_congestion_submodule_sram_buffer, dnx_data_ingr_congestion_sram_buffer_table_drop_tresholds);

}



shr_error_e
dnx_data_ingr_congestion_init(
    int unit,
    dnxc_data_module_t *module_data)
{
    SHR_FUNC_INIT_VARS(unit);

    
    module_data->name = "ingr_congestion";
    module_data->nof_submodules = _dnx_data_ingr_congestion_submodule_nof;
    DNXC_DATA_ALLOC(module_data->submodules, dnxc_data_submodule_t, module_data->nof_submodules, "_dnxc_data ingr_congestion submodules");

    
    SHR_IF_ERR_EXIT(dnx_data_ingr_congestion_config_init(unit, &module_data->submodules[dnx_data_ingr_congestion_submodule_config]));
    SHR_IF_ERR_EXIT(dnx_data_ingr_congestion_info_init(unit, &module_data->submodules[dnx_data_ingr_congestion_submodule_info]));
    SHR_IF_ERR_EXIT(dnx_data_ingr_congestion_fadt_tail_drop_init(unit, &module_data->submodules[dnx_data_ingr_congestion_submodule_fadt_tail_drop]));
    SHR_IF_ERR_EXIT(dnx_data_ingr_congestion_dram_bound_init(unit, &module_data->submodules[dnx_data_ingr_congestion_submodule_dram_bound]));
    SHR_IF_ERR_EXIT(dnx_data_ingr_congestion_voq_init(unit, &module_data->submodules[dnx_data_ingr_congestion_submodule_voq]));
    SHR_IF_ERR_EXIT(dnx_data_ingr_congestion_vsq_init(unit, &module_data->submodules[dnx_data_ingr_congestion_submodule_vsq]));
    SHR_IF_ERR_EXIT(dnx_data_ingr_congestion_init_init(unit, &module_data->submodules[dnx_data_ingr_congestion_submodule_init]));
    SHR_IF_ERR_EXIT(dnx_data_ingr_congestion_dbal_init(unit, &module_data->submodules[dnx_data_ingr_congestion_submodule_dbal]));
    SHR_IF_ERR_EXIT(dnx_data_ingr_congestion_mirror_on_drop_init(unit, &module_data->submodules[dnx_data_ingr_congestion_submodule_mirror_on_drop]));
    SHR_IF_ERR_EXIT(dnx_data_ingr_congestion_sram_buffer_init(unit, &module_data->submodules[dnx_data_ingr_congestion_submodule_sram_buffer]));
    

    if (dnxc_data_mgmt_is_jr2_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_ingr_congestion_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_jr2_b0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_ingr_congestion_attach(unit));
        SHR_IF_ERR_EXIT(jr2_b0_data_ingr_congestion_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_jr2_b1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_ingr_congestion_attach(unit));
        SHR_IF_ERR_EXIT(jr2_b0_data_ingr_congestion_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2c_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_ingr_congestion_attach(unit));
        SHR_IF_ERR_EXIT(j2c_a0_data_ingr_congestion_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2c_a1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_ingr_congestion_attach(unit));
        SHR_IF_ERR_EXIT(j2c_a0_data_ingr_congestion_attach(unit));
        SHR_IF_ERR_EXIT(j2c_a1_data_ingr_congestion_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_q2a_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_ingr_congestion_attach(unit));
        SHR_IF_ERR_EXIT(q2a_a0_data_ingr_congestion_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_q2a_b0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_ingr_congestion_attach(unit));
        SHR_IF_ERR_EXIT(q2a_a0_data_ingr_congestion_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_q2a_b1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_ingr_congestion_attach(unit));
        SHR_IF_ERR_EXIT(q2a_a0_data_ingr_congestion_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2p_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_ingr_congestion_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a0_data_ingr_congestion_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2p_a1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_ingr_congestion_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a0_data_ingr_congestion_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2p_a2(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_ingr_congestion_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a0_data_ingr_congestion_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2x_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_ingr_congestion_attach(unit));
        SHR_IF_ERR_EXIT(j2x_a0_data_ingr_congestion_attach(unit));
    }
    else

    {
        SHR_EXIT();
    }

exit:
    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE



/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_MACSEC

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_macsec.h>




extern shr_error_e jr2_a0_data_macsec_attach(
    int unit);


extern shr_error_e j2p_a0_data_macsec_attach(
    int unit);


extern shr_error_e j2p_a2_data_macsec_attach(
    int unit);


extern shr_error_e j2x_a0_data_macsec_attach(
    int unit);




static shr_error_e
dnx_data_macsec_general_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "general";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_macsec_general_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data macsec general features");

    submodule_data->features[dnx_data_macsec_general_macsec_block_exists].name = "macsec_block_exists";
    submodule_data->features[dnx_data_macsec_general_macsec_block_exists].doc = "";
    submodule_data->features[dnx_data_macsec_general_macsec_block_exists].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_macsec_general_is_hw_reset_init_done_supported].name = "is_hw_reset_init_done_supported";
    submodule_data->features[dnx_data_macsec_general_is_hw_reset_init_done_supported].doc = "";
    submodule_data->features[dnx_data_macsec_general_is_hw_reset_init_done_supported].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_macsec_general_is_shared_macsec_supported].name = "is_shared_macsec_supported";
    submodule_data->features[dnx_data_macsec_general_is_shared_macsec_supported].doc = "";
    submodule_data->features[dnx_data_macsec_general_is_shared_macsec_supported].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_macsec_general_is_macsec_wrapper_main_enable].name = "is_macsec_wrapper_main_enable";
    submodule_data->features[dnx_data_macsec_general_is_macsec_wrapper_main_enable].doc = "";
    submodule_data->features[dnx_data_macsec_general_is_macsec_wrapper_main_enable].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_macsec_general_is_port_based_supported].name = "is_port_based_supported";
    submodule_data->features[dnx_data_macsec_general_is_port_based_supported].doc = "";
    submodule_data->features[dnx_data_macsec_general_is_port_based_supported].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_macsec_general_an_full_range_supported].name = "an_full_range_supported";
    submodule_data->features[dnx_data_macsec_general_an_full_range_supported].doc = "";
    submodule_data->features[dnx_data_macsec_general_an_full_range_supported].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_macsec_general_rfc_6054_supported].name = "rfc_6054_supported";
    submodule_data->features[dnx_data_macsec_general_rfc_6054_supported].doc = "";
    submodule_data->features[dnx_data_macsec_general_rfc_6054_supported].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_macsec_general_multiple_pms_per_macsec_instance].name = "multiple_pms_per_macsec_instance";
    submodule_data->features[dnx_data_macsec_general_multiple_pms_per_macsec_instance].doc = "";
    submodule_data->features[dnx_data_macsec_general_multiple_pms_per_macsec_instance].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_macsec_general_pfc_and_pause_frame_supported].name = "pfc_and_pause_frame_supported";
    submodule_data->features[dnx_data_macsec_general_pfc_and_pause_frame_supported].doc = "";
    submodule_data->features[dnx_data_macsec_general_pfc_and_pause_frame_supported].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnx_data_macsec_general_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data macsec general defines");

    submodule_data->defines[dnx_data_macsec_general_define_macsec_nof].name = "macsec_nof";
    submodule_data->defines[dnx_data_macsec_general_define_macsec_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_general_define_macsec_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_general_define_macsec_in_core_nof].name = "macsec_in_core_nof";
    submodule_data->defines[dnx_data_macsec_general_define_macsec_in_core_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_general_define_macsec_in_core_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_general_define_ports_in_macsec_nof].name = "ports_in_macsec_nof";
    submodule_data->defines[dnx_data_macsec_general_define_ports_in_macsec_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_general_define_ports_in_macsec_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_general_define_etype_nof].name = "etype_nof";
    submodule_data->defines[dnx_data_macsec_general_define_etype_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_general_define_etype_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_general_define_etype_not_zero_verify].name = "etype_not_zero_verify";
    submodule_data->defines[dnx_data_macsec_general_define_etype_not_zero_verify].doc = "";
    
    submodule_data->defines[dnx_data_macsec_general_define_etype_not_zero_verify].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_general_define_tx_threshold].name = "tx_threshold";
    submodule_data->defines[dnx_data_macsec_general_define_tx_threshold].doc = "";
    
    submodule_data->defines[dnx_data_macsec_general_define_tx_threshold].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_general_define_macsec_tdm_cal_max_depth].name = "macsec_tdm_cal_max_depth";
    submodule_data->defines[dnx_data_macsec_general_define_macsec_tdm_cal_max_depth].doc = "";
    
    submodule_data->defines[dnx_data_macsec_general_define_macsec_tdm_cal_max_depth].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_general_define_macsec_tdm_cal_hw_depth].name = "macsec_tdm_cal_hw_depth";
    submodule_data->defines[dnx_data_macsec_general_define_macsec_tdm_cal_hw_depth].doc = "";
    
    submodule_data->defines[dnx_data_macsec_general_define_macsec_tdm_cal_hw_depth].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_general_define_association_number_full_range_nof].name = "association_number_full_range_nof";
    submodule_data->defines[dnx_data_macsec_general_define_association_number_full_range_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_general_define_association_number_full_range_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_general_define_macsec_gen].name = "macsec_gen";
    submodule_data->defines[dnx_data_macsec_general_define_macsec_gen].doc = "";
    
    submodule_data->defines[dnx_data_macsec_general_define_macsec_gen].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_general_define_pfc_and_pause_timer_nof_bits].name = "pfc_and_pause_timer_nof_bits";
    submodule_data->defines[dnx_data_macsec_general_define_pfc_and_pause_timer_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_macsec_general_define_pfc_and_pause_timer_nof_bits].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_general_define_sectag_offset_min_value].name = "sectag_offset_min_value";
    submodule_data->defines[dnx_data_macsec_general_define_sectag_offset_min_value].doc = "";
    
    submodule_data->defines[dnx_data_macsec_general_define_sectag_offset_min_value].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_macsec_general_define_supported_entries_nof].name = "supported_entries_nof";
    submodule_data->defines[dnx_data_macsec_general_define_supported_entries_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_general_define_supported_entries_nof].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_macsec_general_define_is_macsec_enabled].name = "is_macsec_enabled";
    submodule_data->defines[dnx_data_macsec_general_define_is_macsec_enabled].doc = "";
    
    submodule_data->defines[dnx_data_macsec_general_define_is_macsec_enabled].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_macsec_general_define_is_power_optimization_enabled].name = "is_power_optimization_enabled";
    submodule_data->defines[dnx_data_macsec_general_define_is_power_optimization_enabled].doc = "";
    
    submodule_data->defines[dnx_data_macsec_general_define_is_power_optimization_enabled].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_macsec_general_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data macsec general tables");

    
    submodule_data->tables[dnx_data_macsec_general_table_pm_to_macsec].name = "pm_to_macsec";
    submodule_data->tables[dnx_data_macsec_general_table_pm_to_macsec].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_pm_to_macsec].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_macsec_general_table_pm_to_macsec].size_of_values = sizeof(dnx_data_macsec_general_pm_to_macsec_t);
    submodule_data->tables[dnx_data_macsec_general_table_pm_to_macsec].entry_get = dnx_data_macsec_general_pm_to_macsec_entry_str_get;

    
    submodule_data->tables[dnx_data_macsec_general_table_pm_to_macsec].nof_keys = 1;
    submodule_data->tables[dnx_data_macsec_general_table_pm_to_macsec].keys[0].name = "ethu_index";
    submodule_data->tables[dnx_data_macsec_general_table_pm_to_macsec].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_macsec_general_table_pm_to_macsec].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_macsec_general_table_pm_to_macsec].values, dnxc_data_value_t, submodule_data->tables[dnx_data_macsec_general_table_pm_to_macsec].nof_values, "_dnx_data_macsec_general_table_pm_to_macsec table values");
    submodule_data->tables[dnx_data_macsec_general_table_pm_to_macsec].values[0].name = "macsec_id";
    submodule_data->tables[dnx_data_macsec_general_table_pm_to_macsec].values[0].type = "uint32";
    submodule_data->tables[dnx_data_macsec_general_table_pm_to_macsec].values[0].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_pm_to_macsec].values[0].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_pm_to_macsec_t, macsec_id);

    
    submodule_data->tables[dnx_data_macsec_general_table_macsec_instances].name = "macsec_instances";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_instances].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_instances].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_macsec_general_table_macsec_instances].size_of_values = sizeof(dnx_data_macsec_general_macsec_instances_t);
    submodule_data->tables[dnx_data_macsec_general_table_macsec_instances].entry_get = dnx_data_macsec_general_macsec_instances_entry_str_get;

    
    submodule_data->tables[dnx_data_macsec_general_table_macsec_instances].nof_keys = 1;
    submodule_data->tables[dnx_data_macsec_general_table_macsec_instances].keys[0].name = "macsec_id";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_instances].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_macsec_general_table_macsec_instances].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_macsec_general_table_macsec_instances].values, dnxc_data_value_t, submodule_data->tables[dnx_data_macsec_general_table_macsec_instances].nof_values, "_dnx_data_macsec_general_table_macsec_instances table values");
    submodule_data->tables[dnx_data_macsec_general_table_macsec_instances].values[0].name = "nof_pms";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_instances].values[0].type = "uint32";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_instances].values[0].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_instances].values[0].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_macsec_instances_t, nof_pms);

    
    submodule_data->tables[dnx_data_macsec_general_table_macsec_block_mapping].name = "macsec_block_mapping";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_block_mapping].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_block_mapping].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_macsec_general_table_macsec_block_mapping].size_of_values = sizeof(dnx_data_macsec_general_macsec_block_mapping_t);
    submodule_data->tables[dnx_data_macsec_general_table_macsec_block_mapping].entry_get = dnx_data_macsec_general_macsec_block_mapping_entry_str_get;

    
    submodule_data->tables[dnx_data_macsec_general_table_macsec_block_mapping].nof_keys = 2;
    submodule_data->tables[dnx_data_macsec_general_table_macsec_block_mapping].keys[0].name = "is_mss";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_block_mapping].keys[0].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_block_mapping].keys[1].name = "block_id";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_block_mapping].keys[1].doc = "";

    
    submodule_data->tables[dnx_data_macsec_general_table_macsec_block_mapping].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_macsec_general_table_macsec_block_mapping].values, dnxc_data_value_t, submodule_data->tables[dnx_data_macsec_general_table_macsec_block_mapping].nof_values, "_dnx_data_macsec_general_table_macsec_block_mapping table values");
    submodule_data->tables[dnx_data_macsec_general_table_macsec_block_mapping].values[0].name = "instance_id";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_block_mapping].values[0].type = "uint32";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_block_mapping].values[0].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_block_mapping].values[0].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_macsec_block_mapping_t, instance_id);

#ifdef INCLUDE_XFLOW_MACSEC

    
    submodule_data->tables[dnx_data_macsec_general_table_macsec_control_options].name = "macsec_control_options";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_control_options].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_control_options].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_macsec_general_table_macsec_control_options].size_of_values = sizeof(dnx_data_macsec_general_macsec_control_options_t);
    submodule_data->tables[dnx_data_macsec_general_table_macsec_control_options].entry_get = dnx_data_macsec_general_macsec_control_options_entry_str_get;

    
    submodule_data->tables[dnx_data_macsec_general_table_macsec_control_options].nof_keys = 1;
    submodule_data->tables[dnx_data_macsec_general_table_macsec_control_options].keys[0].name = "control_option";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_control_options].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_macsec_general_table_macsec_control_options].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_macsec_general_table_macsec_control_options].values, dnxc_data_value_t, submodule_data->tables[dnx_data_macsec_general_table_macsec_control_options].nof_values, "_dnx_data_macsec_general_table_macsec_control_options table values");
    submodule_data->tables[dnx_data_macsec_general_table_macsec_control_options].values[0].name = "is_supported";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_control_options].values[0].type = "uint32";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_control_options].values[0].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_macsec_control_options].values[0].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_macsec_control_options_t, is_supported);

#endif 
#ifdef INCLUDE_XFLOW_MACSEC

    
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].name = "stat_special_map";
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].size_of_values = sizeof(dnx_data_macsec_general_stat_special_map_t);
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].entry_get = dnx_data_macsec_general_stat_special_map_entry_str_get;

    
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].nof_keys = 1;
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].keys[0].name = "index";
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].nof_values = 3;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].values, dnxc_data_value_t, submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].nof_values, "_dnx_data_macsec_general_table_stat_special_map table values");
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].values[0].name = "stat_from";
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].values[0].type = "int";
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].values[0].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].values[0].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_stat_special_map_t, stat_from);
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].values[1].name = "stat_to";
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].values[1].type = "int";
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].values[1].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].values[1].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_stat_special_map_t, stat_to);
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].values[2].name = "oper";
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].values[2].type = "uint8";
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].values[2].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_stat_special_map].values[2].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_stat_special_map_t, oper);

#endif 
#ifdef INCLUDE_XFLOW_MACSEC

    
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].name = "counter_map";
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].size_of_values = sizeof(dnx_data_macsec_general_counter_map_t);
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].entry_get = dnx_data_macsec_general_counter_map_entry_str_get;

    
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].nof_keys = 1;
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].keys[0].name = "counter_id";
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].nof_values = 4;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_macsec_general_table_counter_map].values, dnxc_data_value_t, submodule_data->tables[dnx_data_macsec_general_table_counter_map].nof_values, "_dnx_data_macsec_general_table_counter_map table values");
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].values[0].name = "hw_access";
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].values[0].type = "int";
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].values[0].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].values[0].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_counter_map_t, hw_access);
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].values[1].name = "counter_name";
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].values[1].type = "char *";
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].values[1].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].values[1].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_counter_map_t, counter_name);
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].values[2].name = "is_reg";
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].values[2].type = "uint8";
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].values[2].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].values[2].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_counter_map_t, is_reg);
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].values[3].name = "valid";
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].values[3].type = "uint8";
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].values[3].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_counter_map].values[3].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_counter_map_t, valid);

#endif 
#if defined(INCLUDE_XFLOW_MACSEC) && defined(BCM_ACCESS_SUPPORT) 

    
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].name = "access_counter_map";
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].size_of_values = sizeof(dnx_data_macsec_general_access_counter_map_t);
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].entry_get = dnx_data_macsec_general_access_counter_map_entry_str_get;

    
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].nof_keys = 1;
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].keys[0].name = "counter_id";
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].nof_values = 4;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].values, dnxc_data_value_t, submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].nof_values, "_dnx_data_macsec_general_table_access_counter_map table values");
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].values[0].name = "hw_access";
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].values[0].type = "int";
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].values[0].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].values[0].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_access_counter_map_t, hw_access);
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].values[1].name = "counter_name";
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].values[1].type = "char *";
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].values[1].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].values[1].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_access_counter_map_t, counter_name);
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].values[2].name = "is_reg";
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].values[2].type = "uint8";
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].values[2].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].values[2].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_access_counter_map_t, is_reg);
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].values[3].name = "valid";
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].values[3].type = "uint8";
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].values[3].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_access_counter_map].values[3].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_access_counter_map_t, valid);

#endif 
#if defined(INCLUDE_XFLOW_MACSEC) && defined(BCM_ACCESS_SUPPORT) 

    
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].name = "access_stat_map";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].size_of_values = sizeof(dnx_data_macsec_general_access_stat_map_t);
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].entry_get = dnx_data_macsec_general_access_stat_map_entry_str_get;

    
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].nof_keys = 1;
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].keys[0].name = "stat_type";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].nof_values = 7;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values, dnxc_data_value_t, submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].nof_values, "_dnx_data_macsec_general_table_access_stat_map table values");
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[0].name = "counter_id";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[0].type = "int";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[0].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[0].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_access_stat_map_t, counter_id);
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[1].name = "field";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[1].type = "int";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[1].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[1].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_access_stat_map_t, field);
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[2].name = "direction";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[2].type = "uint8";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[2].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[2].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_access_stat_map_t, direction);
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[3].name = "id_type";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[3].type = "int";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[3].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[3].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_access_stat_map_t, id_type);
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[4].name = "macsec_supported";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[4].type = "uint8";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[4].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[4].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_access_stat_map_t, macsec_supported);
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[5].name = "ipsec_supported";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[5].type = "uint8";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[5].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[5].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_access_stat_map_t, ipsec_supported);
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[6].name = "valid";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[6].type = "uint8";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[6].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_access_stat_map].values[6].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_access_stat_map_t, valid);

#endif 
#ifdef INCLUDE_XFLOW_MACSEC

    
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].name = "stat_map";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].size_of_values = sizeof(dnx_data_macsec_general_stat_map_t);
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].entry_get = dnx_data_macsec_general_stat_map_entry_str_get;

    
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].nof_keys = 1;
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].keys[0].name = "stat_type";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].nof_values = 7;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_macsec_general_table_stat_map].values, dnxc_data_value_t, submodule_data->tables[dnx_data_macsec_general_table_stat_map].nof_values, "_dnx_data_macsec_general_table_stat_map table values");
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[0].name = "counter_id";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[0].type = "int";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[0].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[0].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_stat_map_t, counter_id);
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[1].name = "field";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[1].type = "int";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[1].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[1].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_stat_map_t, field);
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[2].name = "direction";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[2].type = "uint8";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[2].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[2].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_stat_map_t, direction);
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[3].name = "id_type";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[3].type = "int";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[3].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[3].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_stat_map_t, id_type);
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[4].name = "macsec_supported";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[4].type = "uint8";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[4].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[4].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_stat_map_t, macsec_supported);
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[5].name = "ipsec_supported";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[5].type = "uint8";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[5].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[5].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_stat_map_t, ipsec_supported);
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[6].name = "valid";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[6].type = "uint8";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[6].doc = "";
    submodule_data->tables[dnx_data_macsec_general_table_stat_map].values[6].offset = UTILEX_OFFSETOF(dnx_data_macsec_general_stat_map_t, valid);

#endif 

exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_macsec_general_feature_get(
    int unit,
    dnx_data_macsec_general_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, feature);
}


uint32
dnx_data_macsec_general_macsec_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_define_macsec_nof);
}

uint32
dnx_data_macsec_general_macsec_in_core_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_define_macsec_in_core_nof);
}

uint32
dnx_data_macsec_general_ports_in_macsec_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_define_ports_in_macsec_nof);
}

uint32
dnx_data_macsec_general_etype_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_define_etype_nof);
}

uint32
dnx_data_macsec_general_etype_not_zero_verify_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_define_etype_not_zero_verify);
}

uint32
dnx_data_macsec_general_tx_threshold_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_define_tx_threshold);
}

uint32
dnx_data_macsec_general_macsec_tdm_cal_max_depth_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_define_macsec_tdm_cal_max_depth);
}

uint32
dnx_data_macsec_general_macsec_tdm_cal_hw_depth_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_define_macsec_tdm_cal_hw_depth);
}

uint32
dnx_data_macsec_general_association_number_full_range_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_define_association_number_full_range_nof);
}

uint32
dnx_data_macsec_general_macsec_gen_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_define_macsec_gen);
}

uint32
dnx_data_macsec_general_pfc_and_pause_timer_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_define_pfc_and_pause_timer_nof_bits);
}

uint32
dnx_data_macsec_general_sectag_offset_min_value_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_define_sectag_offset_min_value);
}

uint32
dnx_data_macsec_general_supported_entries_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_define_supported_entries_nof);
}

uint32
dnx_data_macsec_general_is_macsec_enabled_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_define_is_macsec_enabled);
}

uint32
dnx_data_macsec_general_is_power_optimization_enabled_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_define_is_power_optimization_enabled);
}



const dnx_data_macsec_general_pm_to_macsec_t *
dnx_data_macsec_general_pm_to_macsec_get(
    int unit,
    int ethu_index)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_pm_to_macsec);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, ethu_index, 0);
    return (const dnx_data_macsec_general_pm_to_macsec_t *) data;

}

const dnx_data_macsec_general_macsec_instances_t *
dnx_data_macsec_general_macsec_instances_get(
    int unit,
    int macsec_id)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_macsec_instances);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, macsec_id, 0);
    return (const dnx_data_macsec_general_macsec_instances_t *) data;

}

const dnx_data_macsec_general_macsec_block_mapping_t *
dnx_data_macsec_general_macsec_block_mapping_get(
    int unit,
    int is_mss,
    int block_id)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_macsec_block_mapping);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, is_mss, block_id);
    return (const dnx_data_macsec_general_macsec_block_mapping_t *) data;

}

#ifdef INCLUDE_XFLOW_MACSEC

const dnx_data_macsec_general_macsec_control_options_t *
dnx_data_macsec_general_macsec_control_options_get(
    int unit,
    int control_option)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_macsec_control_options);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, control_option, 0);
    return (const dnx_data_macsec_general_macsec_control_options_t *) data;

}


#endif 
#ifdef INCLUDE_XFLOW_MACSEC

const dnx_data_macsec_general_stat_special_map_t *
dnx_data_macsec_general_stat_special_map_get(
    int unit,
    int index)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_stat_special_map);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, index, 0);
    return (const dnx_data_macsec_general_stat_special_map_t *) data;

}


#endif 
#ifdef INCLUDE_XFLOW_MACSEC

const dnx_data_macsec_general_counter_map_t *
dnx_data_macsec_general_counter_map_get(
    int unit,
    int counter_id)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_counter_map);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, counter_id, 0);
    return (const dnx_data_macsec_general_counter_map_t *) data;

}


#endif 
#if defined(INCLUDE_XFLOW_MACSEC) && defined(BCM_ACCESS_SUPPORT) 

const dnx_data_macsec_general_access_counter_map_t *
dnx_data_macsec_general_access_counter_map_get(
    int unit,
    int counter_id)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_access_counter_map);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, counter_id, 0);
    return (const dnx_data_macsec_general_access_counter_map_t *) data;

}


#endif 
#if defined(INCLUDE_XFLOW_MACSEC) && defined(BCM_ACCESS_SUPPORT) 

const dnx_data_macsec_general_access_stat_map_t *
dnx_data_macsec_general_access_stat_map_get(
    int unit,
    int stat_type)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_access_stat_map);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, stat_type, 0);
    return (const dnx_data_macsec_general_access_stat_map_t *) data;

}


#endif 
#ifdef INCLUDE_XFLOW_MACSEC

const dnx_data_macsec_general_stat_map_t *
dnx_data_macsec_general_stat_map_get(
    int unit,
    int stat_type)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_stat_map);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, stat_type, 0);
    return (const dnx_data_macsec_general_stat_map_t *) data;

}


#endif 

shr_error_e
dnx_data_macsec_general_pm_to_macsec_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_macsec_general_pm_to_macsec_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_pm_to_macsec);
    data = (const dnx_data_macsec_general_pm_to_macsec_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->macsec_id);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_macsec_general_macsec_instances_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_macsec_general_macsec_instances_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_macsec_instances);
    data = (const dnx_data_macsec_general_macsec_instances_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->nof_pms);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_macsec_general_macsec_block_mapping_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_macsec_general_macsec_block_mapping_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_macsec_block_mapping);
    data = (const dnx_data_macsec_general_macsec_block_mapping_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, key1);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->instance_id);
            break;
    }

    SHR_FUNC_EXIT;
}

#ifdef INCLUDE_XFLOW_MACSEC

shr_error_e
dnx_data_macsec_general_macsec_control_options_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_macsec_general_macsec_control_options_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_macsec_control_options);
    data = (const dnx_data_macsec_general_macsec_control_options_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->is_supported);
            break;
    }

    SHR_FUNC_EXIT;
}


#endif 
#ifdef INCLUDE_XFLOW_MACSEC

shr_error_e
dnx_data_macsec_general_stat_special_map_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_macsec_general_stat_special_map_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_stat_special_map);
    data = (const dnx_data_macsec_general_stat_special_map_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->stat_from);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->stat_to);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->oper);
            break;
    }

    SHR_FUNC_EXIT;
}


#endif 
#ifdef INCLUDE_XFLOW_MACSEC

shr_error_e
dnx_data_macsec_general_counter_map_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_macsec_general_counter_map_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_counter_map);
    data = (const dnx_data_macsec_general_counter_map_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->hw_access);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%s", data->counter_name == NULL ? "" : data->counter_name);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->is_reg);
            break;
        case 3:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->valid);
            break;
    }

    SHR_FUNC_EXIT;
}


#endif 
#if defined(INCLUDE_XFLOW_MACSEC) && defined(BCM_ACCESS_SUPPORT) 

shr_error_e
dnx_data_macsec_general_access_counter_map_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_macsec_general_access_counter_map_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_access_counter_map);
    data = (const dnx_data_macsec_general_access_counter_map_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->hw_access);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%s", data->counter_name == NULL ? "" : data->counter_name);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->is_reg);
            break;
        case 3:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->valid);
            break;
    }

    SHR_FUNC_EXIT;
}


#endif 
#if defined(INCLUDE_XFLOW_MACSEC) && defined(BCM_ACCESS_SUPPORT) 

shr_error_e
dnx_data_macsec_general_access_stat_map_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_macsec_general_access_stat_map_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_access_stat_map);
    data = (const dnx_data_macsec_general_access_stat_map_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->counter_id);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->field);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->direction);
            break;
        case 3:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->id_type);
            break;
        case 4:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->macsec_supported);
            break;
        case 5:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->ipsec_supported);
            break;
        case 6:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->valid);
            break;
    }

    SHR_FUNC_EXIT;
}


#endif 
#ifdef INCLUDE_XFLOW_MACSEC

shr_error_e
dnx_data_macsec_general_stat_map_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_macsec_general_stat_map_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_stat_map);
    data = (const dnx_data_macsec_general_stat_map_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->counter_id);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->field);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->direction);
            break;
        case 3:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->id_type);
            break;
        case 4:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->macsec_supported);
            break;
        case 5:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->ipsec_supported);
            break;
        case 6:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->valid);
            break;
    }

    SHR_FUNC_EXIT;
}


#endif 

const dnxc_data_table_info_t *
dnx_data_macsec_general_pm_to_macsec_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_pm_to_macsec);

}

const dnxc_data_table_info_t *
dnx_data_macsec_general_macsec_instances_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_macsec_instances);

}

const dnxc_data_table_info_t *
dnx_data_macsec_general_macsec_block_mapping_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_macsec_block_mapping);

}

#ifdef INCLUDE_XFLOW_MACSEC

const dnxc_data_table_info_t *
dnx_data_macsec_general_macsec_control_options_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_macsec_control_options);

}


#endif 
#ifdef INCLUDE_XFLOW_MACSEC

const dnxc_data_table_info_t *
dnx_data_macsec_general_stat_special_map_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_stat_special_map);

}


#endif 
#ifdef INCLUDE_XFLOW_MACSEC

const dnxc_data_table_info_t *
dnx_data_macsec_general_counter_map_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_counter_map);

}


#endif 
#if defined(INCLUDE_XFLOW_MACSEC) && defined(BCM_ACCESS_SUPPORT) 

const dnxc_data_table_info_t *
dnx_data_macsec_general_access_counter_map_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_access_counter_map);

}


#endif 
#if defined(INCLUDE_XFLOW_MACSEC) && defined(BCM_ACCESS_SUPPORT) 

const dnxc_data_table_info_t *
dnx_data_macsec_general_access_stat_map_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_access_stat_map);

}


#endif 
#ifdef INCLUDE_XFLOW_MACSEC

const dnxc_data_table_info_t *
dnx_data_macsec_general_stat_map_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_general, dnx_data_macsec_general_table_stat_map);

}


#endif 





static shr_error_e
dnx_data_macsec_ingress_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "ingress";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_macsec_ingress_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data macsec ingress features");

    submodule_data->features[dnx_data_macsec_ingress_restricted_hw_ids_exist].name = "restricted_hw_ids_exist";
    submodule_data->features[dnx_data_macsec_ingress_restricted_hw_ids_exist].doc = "";
    submodule_data->features[dnx_data_macsec_ingress_restricted_hw_ids_exist].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_macsec_ingress_svtag_mapping].name = "svtag_mapping";
    submodule_data->features[dnx_data_macsec_ingress_svtag_mapping].doc = "";
    submodule_data->features[dnx_data_macsec_ingress_svtag_mapping].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnx_data_macsec_ingress_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data macsec ingress defines");

    submodule_data->defines[dnx_data_macsec_ingress_define_flow_nof].name = "flow_nof";
    submodule_data->defines[dnx_data_macsec_ingress_define_flow_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_ingress_define_flow_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_ingress_define_policy_nof].name = "policy_nof";
    submodule_data->defines[dnx_data_macsec_ingress_define_policy_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_ingress_define_policy_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_ingress_define_secure_assoc_nof].name = "secure_assoc_nof";
    submodule_data->defines[dnx_data_macsec_ingress_define_secure_assoc_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_ingress_define_secure_assoc_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_ingress_define_udf_nof_bits].name = "udf_nof_bits";
    submodule_data->defines[dnx_data_macsec_ingress_define_udf_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_macsec_ingress_define_udf_nof_bits].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_ingress_define_mgmt_rule_exact_nof].name = "mgmt_rule_exact_nof";
    submodule_data->defines[dnx_data_macsec_ingress_define_mgmt_rule_exact_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_ingress_define_mgmt_rule_exact_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_ingress_define_tpid_nof].name = "tpid_nof";
    submodule_data->defines[dnx_data_macsec_ingress_define_tpid_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_ingress_define_tpid_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_ingress_define_cpu_flex_map_nof].name = "cpu_flex_map_nof";
    submodule_data->defines[dnx_data_macsec_ingress_define_cpu_flex_map_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_ingress_define_cpu_flex_map_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_ingress_define_sc_tcam_nof].name = "sc_tcam_nof";
    submodule_data->defines[dnx_data_macsec_ingress_define_sc_tcam_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_ingress_define_sc_tcam_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_ingress_define_sa_per_sc_nof].name = "sa_per_sc_nof";
    submodule_data->defines[dnx_data_macsec_ingress_define_sa_per_sc_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_ingress_define_sa_per_sc_nof].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_macsec_ingress_define_invalidate_sa].name = "invalidate_sa";
    submodule_data->defines[dnx_data_macsec_ingress_define_invalidate_sa].doc = "";
    
    submodule_data->defines[dnx_data_macsec_ingress_define_invalidate_sa].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_macsec_ingress_define_secure_channel_nof].name = "secure_channel_nof";
    submodule_data->defines[dnx_data_macsec_ingress_define_secure_channel_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_ingress_define_secure_channel_nof].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_macsec_ingress_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data macsec ingress tables");

    
    submodule_data->tables[dnx_data_macsec_ingress_table_udf].name = "udf";
    submodule_data->tables[dnx_data_macsec_ingress_table_udf].doc = "";
    submodule_data->tables[dnx_data_macsec_ingress_table_udf].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_macsec_ingress_table_udf].size_of_values = sizeof(dnx_data_macsec_ingress_udf_t);
    submodule_data->tables[dnx_data_macsec_ingress_table_udf].entry_get = dnx_data_macsec_ingress_udf_entry_str_get;

    
    submodule_data->tables[dnx_data_macsec_ingress_table_udf].nof_keys = 1;
    submodule_data->tables[dnx_data_macsec_ingress_table_udf].keys[0].name = "type";
    submodule_data->tables[dnx_data_macsec_ingress_table_udf].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_macsec_ingress_table_udf].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_macsec_ingress_table_udf].values, dnxc_data_value_t, submodule_data->tables[dnx_data_macsec_ingress_table_udf].nof_values, "_dnx_data_macsec_ingress_table_udf table values");
    submodule_data->tables[dnx_data_macsec_ingress_table_udf].values[0].name = "payload_len";
    submodule_data->tables[dnx_data_macsec_ingress_table_udf].values[0].type = "uint32";
    submodule_data->tables[dnx_data_macsec_ingress_table_udf].values[0].doc = "";
    submodule_data->tables[dnx_data_macsec_ingress_table_udf].values[0].offset = UTILEX_OFFSETOF(dnx_data_macsec_ingress_udf_t, payload_len);

    
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sc_tcam_id].name = "restricted_sc_tcam_id";
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sc_tcam_id].doc = "";
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sc_tcam_id].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sc_tcam_id].size_of_values = sizeof(dnx_data_macsec_ingress_restricted_sc_tcam_id_t);
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sc_tcam_id].entry_get = dnx_data_macsec_ingress_restricted_sc_tcam_id_entry_str_get;

    
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sc_tcam_id].nof_keys = 1;
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sc_tcam_id].keys[0].name = "key_index";
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sc_tcam_id].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sc_tcam_id].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sc_tcam_id].values, dnxc_data_value_t, submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sc_tcam_id].nof_values, "_dnx_data_macsec_ingress_table_restricted_sc_tcam_id table values");
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sc_tcam_id].values[0].name = "hw_id";
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sc_tcam_id].values[0].type = "uint32";
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sc_tcam_id].values[0].doc = "";
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sc_tcam_id].values[0].offset = UTILEX_OFFSETOF(dnx_data_macsec_ingress_restricted_sc_tcam_id_t, hw_id);

    
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sp_tcam_id].name = "restricted_sp_tcam_id";
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sp_tcam_id].doc = "";
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sp_tcam_id].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sp_tcam_id].size_of_values = sizeof(dnx_data_macsec_ingress_restricted_sp_tcam_id_t);
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sp_tcam_id].entry_get = dnx_data_macsec_ingress_restricted_sp_tcam_id_entry_str_get;

    
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sp_tcam_id].nof_keys = 1;
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sp_tcam_id].keys[0].name = "key_index";
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sp_tcam_id].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sp_tcam_id].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sp_tcam_id].values, dnxc_data_value_t, submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sp_tcam_id].nof_values, "_dnx_data_macsec_ingress_table_restricted_sp_tcam_id table values");
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sp_tcam_id].values[0].name = "hw_id";
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sp_tcam_id].values[0].type = "uint32";
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sp_tcam_id].values[0].doc = "";
    submodule_data->tables[dnx_data_macsec_ingress_table_restricted_sp_tcam_id].values[0].offset = UTILEX_OFFSETOF(dnx_data_macsec_ingress_restricted_sp_tcam_id_t, hw_id);


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_macsec_ingress_feature_get(
    int unit,
    dnx_data_macsec_ingress_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, feature);
}


uint32
dnx_data_macsec_ingress_flow_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_define_flow_nof);
}

uint32
dnx_data_macsec_ingress_policy_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_define_policy_nof);
}

uint32
dnx_data_macsec_ingress_secure_assoc_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_define_secure_assoc_nof);
}

uint32
dnx_data_macsec_ingress_udf_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_define_udf_nof_bits);
}

uint32
dnx_data_macsec_ingress_mgmt_rule_exact_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_define_mgmt_rule_exact_nof);
}

uint32
dnx_data_macsec_ingress_tpid_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_define_tpid_nof);
}

uint32
dnx_data_macsec_ingress_cpu_flex_map_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_define_cpu_flex_map_nof);
}

uint32
dnx_data_macsec_ingress_sc_tcam_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_define_sc_tcam_nof);
}

uint32
dnx_data_macsec_ingress_sa_per_sc_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_define_sa_per_sc_nof);
}

uint32
dnx_data_macsec_ingress_invalidate_sa_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_define_invalidate_sa);
}

uint32
dnx_data_macsec_ingress_secure_channel_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_define_secure_channel_nof);
}



const dnx_data_macsec_ingress_udf_t *
dnx_data_macsec_ingress_udf_get(
    int unit,
    int type)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_table_udf);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, type, 0);
    return (const dnx_data_macsec_ingress_udf_t *) data;

}

const dnx_data_macsec_ingress_restricted_sc_tcam_id_t *
dnx_data_macsec_ingress_restricted_sc_tcam_id_get(
    int unit,
    int key_index)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_table_restricted_sc_tcam_id);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, key_index, 0);
    return (const dnx_data_macsec_ingress_restricted_sc_tcam_id_t *) data;

}

const dnx_data_macsec_ingress_restricted_sp_tcam_id_t *
dnx_data_macsec_ingress_restricted_sp_tcam_id_get(
    int unit,
    int key_index)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_table_restricted_sp_tcam_id);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, key_index, 0);
    return (const dnx_data_macsec_ingress_restricted_sp_tcam_id_t *) data;

}


shr_error_e
dnx_data_macsec_ingress_udf_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_macsec_ingress_udf_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_table_udf);
    data = (const dnx_data_macsec_ingress_udf_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->payload_len);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_macsec_ingress_restricted_sc_tcam_id_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_macsec_ingress_restricted_sc_tcam_id_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_table_restricted_sc_tcam_id);
    data = (const dnx_data_macsec_ingress_restricted_sc_tcam_id_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->hw_id);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_macsec_ingress_restricted_sp_tcam_id_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_macsec_ingress_restricted_sp_tcam_id_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_table_restricted_sp_tcam_id);
    data = (const dnx_data_macsec_ingress_restricted_sp_tcam_id_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->hw_id);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnx_data_macsec_ingress_udf_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_table_udf);

}

const dnxc_data_table_info_t *
dnx_data_macsec_ingress_restricted_sc_tcam_id_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_table_restricted_sc_tcam_id);

}

const dnxc_data_table_info_t *
dnx_data_macsec_ingress_restricted_sp_tcam_id_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_ingress, dnx_data_macsec_ingress_table_restricted_sp_tcam_id);

}






static shr_error_e
dnx_data_macsec_egress_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "egress";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_macsec_egress_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data macsec egress features");

    submodule_data->features[dnx_data_macsec_egress_dedicated_pn_soft_expiry_threshold_masks].name = "dedicated_pn_soft_expiry_threshold_masks";
    submodule_data->features[dnx_data_macsec_egress_dedicated_pn_soft_expiry_threshold_masks].doc = "";
    submodule_data->features[dnx_data_macsec_egress_dedicated_pn_soft_expiry_threshold_masks].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_macsec_egress_dedicated_ipsec_soft_expiry_thresholds].name = "dedicated_ipsec_soft_expiry_thresholds";
    submodule_data->features[dnx_data_macsec_egress_dedicated_ipsec_soft_expiry_thresholds].doc = "";
    submodule_data->features[dnx_data_macsec_egress_dedicated_ipsec_soft_expiry_thresholds].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_macsec_egress_multiple_nh_profiles].name = "multiple_nh_profiles";
    submodule_data->features[dnx_data_macsec_egress_multiple_nh_profiles].doc = "";
    submodule_data->features[dnx_data_macsec_egress_multiple_nh_profiles].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnx_data_macsec_egress_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data macsec egress defines");

    submodule_data->defines[dnx_data_macsec_egress_define_secure_assoc_nof].name = "secure_assoc_nof";
    submodule_data->defines[dnx_data_macsec_egress_define_secure_assoc_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_egress_define_secure_assoc_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_egress_define_soft_expiry_threshold_profiles_nof].name = "soft_expiry_threshold_profiles_nof";
    submodule_data->defines[dnx_data_macsec_egress_define_soft_expiry_threshold_profiles_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_egress_define_soft_expiry_threshold_profiles_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_egress_define_an_bit_nof].name = "an_bit_nof";
    submodule_data->defines[dnx_data_macsec_egress_define_an_bit_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_egress_define_an_bit_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_egress_define_nh_profiles_nof].name = "nh_profiles_nof";
    submodule_data->defines[dnx_data_macsec_egress_define_nh_profiles_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_egress_define_nh_profiles_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_egress_define_association_number_actual_range_nof].name = "association_number_actual_range_nof";
    submodule_data->defines[dnx_data_macsec_egress_define_association_number_actual_range_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_egress_define_association_number_actual_range_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_egress_define_sa_per_sc_nof].name = "sa_per_sc_nof";
    submodule_data->defines[dnx_data_macsec_egress_define_sa_per_sc_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_egress_define_sa_per_sc_nof].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_macsec_egress_define_secure_channel_nof].name = "secure_channel_nof";
    submodule_data->defines[dnx_data_macsec_egress_define_secure_channel_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_egress_define_secure_channel_nof].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_macsec_egress_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data macsec egress tables");


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_macsec_egress_feature_get(
    int unit,
    dnx_data_macsec_egress_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_egress, feature);
}


uint32
dnx_data_macsec_egress_secure_assoc_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_egress, dnx_data_macsec_egress_define_secure_assoc_nof);
}

uint32
dnx_data_macsec_egress_soft_expiry_threshold_profiles_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_egress, dnx_data_macsec_egress_define_soft_expiry_threshold_profiles_nof);
}

uint32
dnx_data_macsec_egress_an_bit_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_egress, dnx_data_macsec_egress_define_an_bit_nof);
}

uint32
dnx_data_macsec_egress_nh_profiles_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_egress, dnx_data_macsec_egress_define_nh_profiles_nof);
}

uint32
dnx_data_macsec_egress_association_number_actual_range_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_egress, dnx_data_macsec_egress_define_association_number_actual_range_nof);
}

uint32
dnx_data_macsec_egress_sa_per_sc_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_egress, dnx_data_macsec_egress_define_sa_per_sc_nof);
}

uint32
dnx_data_macsec_egress_secure_channel_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_egress, dnx_data_macsec_egress_define_secure_channel_nof);
}










static shr_error_e
dnx_data_macsec_wrapper_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "wrapper";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_macsec_wrapper_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data macsec wrapper features");

    
    submodule_data->nof_defines = _dnx_data_macsec_wrapper_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data macsec wrapper defines");

    submodule_data->defines[dnx_data_macsec_wrapper_define_macsec_arb_ports_nof].name = "macsec_arb_ports_nof";
    submodule_data->defines[dnx_data_macsec_wrapper_define_macsec_arb_ports_nof].doc = "";
    
    submodule_data->defines[dnx_data_macsec_wrapper_define_macsec_arb_ports_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_wrapper_define_per_port_speed_max_mbps].name = "per_port_speed_max_mbps";
    submodule_data->defines[dnx_data_macsec_wrapper_define_per_port_speed_max_mbps].doc = "";
    
    submodule_data->defines[dnx_data_macsec_wrapper_define_per_port_speed_max_mbps].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_wrapper_define_wrapper_speed_max_mbps].name = "wrapper_speed_max_mbps";
    submodule_data->defines[dnx_data_macsec_wrapper_define_wrapper_speed_max_mbps].doc = "";
    
    submodule_data->defines[dnx_data_macsec_wrapper_define_wrapper_speed_max_mbps].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_wrapper_define_framer_ports_offset].name = "framer_ports_offset";
    submodule_data->defines[dnx_data_macsec_wrapper_define_framer_ports_offset].doc = "";
    
    submodule_data->defines[dnx_data_macsec_wrapper_define_framer_ports_offset].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_wrapper_define_tdm_calendar_sbus_slot].name = "tdm_calendar_sbus_slot";
    submodule_data->defines[dnx_data_macsec_wrapper_define_tdm_calendar_sbus_slot].doc = "";
    
    submodule_data->defines[dnx_data_macsec_wrapper_define_tdm_calendar_sbus_slot].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_wrapper_define_tdm_calendar_nof_slots_per_line].name = "tdm_calendar_nof_slots_per_line";
    submodule_data->defines[dnx_data_macsec_wrapper_define_tdm_calendar_nof_slots_per_line].doc = "";
    
    submodule_data->defines[dnx_data_macsec_wrapper_define_tdm_calendar_nof_slots_per_line].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_wrapper_define_tdm_calendar_speed_granularity].name = "tdm_calendar_speed_granularity";
    submodule_data->defines[dnx_data_macsec_wrapper_define_tdm_calendar_speed_granularity].doc = "";
    
    submodule_data->defines[dnx_data_macsec_wrapper_define_tdm_calendar_speed_granularity].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_macsec_wrapper_define_nof_tags].name = "nof_tags";
    submodule_data->defines[dnx_data_macsec_wrapper_define_nof_tags].doc = "";
    
    submodule_data->defines[dnx_data_macsec_wrapper_define_nof_tags].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_macsec_wrapper_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data macsec wrapper tables");


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_macsec_wrapper_feature_get(
    int unit,
    dnx_data_macsec_wrapper_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_wrapper, feature);
}


uint32
dnx_data_macsec_wrapper_macsec_arb_ports_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_wrapper, dnx_data_macsec_wrapper_define_macsec_arb_ports_nof);
}

uint32
dnx_data_macsec_wrapper_per_port_speed_max_mbps_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_wrapper, dnx_data_macsec_wrapper_define_per_port_speed_max_mbps);
}

uint32
dnx_data_macsec_wrapper_wrapper_speed_max_mbps_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_wrapper, dnx_data_macsec_wrapper_define_wrapper_speed_max_mbps);
}

uint32
dnx_data_macsec_wrapper_framer_ports_offset_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_wrapper, dnx_data_macsec_wrapper_define_framer_ports_offset);
}

uint32
dnx_data_macsec_wrapper_tdm_calendar_sbus_slot_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_wrapper, dnx_data_macsec_wrapper_define_tdm_calendar_sbus_slot);
}

uint32
dnx_data_macsec_wrapper_tdm_calendar_nof_slots_per_line_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_wrapper, dnx_data_macsec_wrapper_define_tdm_calendar_nof_slots_per_line);
}

uint32
dnx_data_macsec_wrapper_tdm_calendar_speed_granularity_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_wrapper, dnx_data_macsec_wrapper_define_tdm_calendar_speed_granularity);
}

uint32
dnx_data_macsec_wrapper_nof_tags_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_macsec, dnx_data_macsec_submodule_wrapper, dnx_data_macsec_wrapper_define_nof_tags);
}







shr_error_e
dnx_data_macsec_init(
    int unit,
    dnxc_data_module_t *module_data)
{
    SHR_FUNC_INIT_VARS(unit);

    
    module_data->name = "macsec";
    module_data->nof_submodules = _dnx_data_macsec_submodule_nof;
    DNXC_DATA_ALLOC(module_data->submodules, dnxc_data_submodule_t, module_data->nof_submodules, "_dnxc_data macsec submodules");

    
    SHR_IF_ERR_EXIT(dnx_data_macsec_general_init(unit, &module_data->submodules[dnx_data_macsec_submodule_general]));
    SHR_IF_ERR_EXIT(dnx_data_macsec_ingress_init(unit, &module_data->submodules[dnx_data_macsec_submodule_ingress]));
    SHR_IF_ERR_EXIT(dnx_data_macsec_egress_init(unit, &module_data->submodules[dnx_data_macsec_submodule_egress]));
    SHR_IF_ERR_EXIT(dnx_data_macsec_wrapper_init(unit, &module_data->submodules[dnx_data_macsec_submodule_wrapper]));
    

    if (dnxc_data_mgmt_is_jr2_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_macsec_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_jr2_b0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_macsec_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_jr2_b1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_macsec_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2c_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_macsec_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2c_a1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_macsec_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_q2a_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_macsec_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_q2a_b0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_macsec_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_q2a_b1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_macsec_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2p_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_macsec_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a0_data_macsec_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2p_a1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_macsec_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a0_data_macsec_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2p_a2(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_macsec_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a0_data_macsec_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a2_data_macsec_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2x_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_macsec_attach(unit));
        SHR_IF_ERR_EXIT(j2x_a0_data_macsec_attach(unit));
    }
    else

    {
        SHR_EXIT();
    }

exit:
    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


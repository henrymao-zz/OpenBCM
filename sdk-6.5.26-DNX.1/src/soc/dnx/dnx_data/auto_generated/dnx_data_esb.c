
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_EGRESSDNX

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_esb.h>




extern shr_error_e jr2_a0_data_esb_attach(
    int unit);


extern shr_error_e j2c_a0_data_esb_attach(
    int unit);


extern shr_error_e q2a_a0_data_esb_attach(
    int unit);


extern shr_error_e j2p_a0_data_esb_attach(
    int unit);


extern shr_error_e j2x_a0_data_esb_attach(
    int unit);




static shr_error_e
dnx_data_esb_general_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "general";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_esb_general_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data esb general features");

    submodule_data->features[dnx_data_esb_general_esb_support].name = "esb_support";
    submodule_data->features[dnx_data_esb_general_esb_support].doc = "";
    submodule_data->features[dnx_data_esb_general_esb_support].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_esb_general_add_remove_queues_support].name = "add_remove_queues_support";
    submodule_data->features[dnx_data_esb_general_add_remove_queues_support].doc = "";
    submodule_data->features[dnx_data_esb_general_add_remove_queues_support].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_esb_general_slow_port_dedicated_queue_support].name = "slow_port_dedicated_queue_support";
    submodule_data->features[dnx_data_esb_general_slow_port_dedicated_queue_support].doc = "";
    submodule_data->features[dnx_data_esb_general_slow_port_dedicated_queue_support].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_esb_general_flexe_l1_dest_dedicated_queue_support].name = "flexe_l1_dest_dedicated_queue_support";
    submodule_data->features[dnx_data_esb_general_flexe_l1_dest_dedicated_queue_support].doc = "";
    submodule_data->features[dnx_data_esb_general_flexe_l1_dest_dedicated_queue_support].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_esb_general_graceful_calendar_switching].name = "graceful_calendar_switching";
    submodule_data->features[dnx_data_esb_general_graceful_calendar_switching].doc = "";
    submodule_data->features[dnx_data_esb_general_graceful_calendar_switching].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_esb_general_per_priority_queues_mapping].name = "per_priority_queues_mapping";
    submodule_data->features[dnx_data_esb_general_per_priority_queues_mapping].doc = "";
    submodule_data->features[dnx_data_esb_general_per_priority_queues_mapping].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_esb_general_internal_offset_mapping_not_supported].name = "internal_offset_mapping_not_supported";
    submodule_data->features[dnx_data_esb_general_internal_offset_mapping_not_supported].doc = "";
    submodule_data->features[dnx_data_esb_general_internal_offset_mapping_not_supported].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_esb_general_is_used].name = "is_used";
    submodule_data->features[dnx_data_esb_general_is_used].doc = "";
    submodule_data->features[dnx_data_esb_general_is_used].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_esb_general_power_down_supported].name = "power_down_supported";
    submodule_data->features[dnx_data_esb_general_power_down_supported].doc = "";
    submodule_data->features[dnx_data_esb_general_power_down_supported].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnx_data_esb_general_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data esb general defines");

    submodule_data->defines[dnx_data_esb_general_define_total_nof_esb_queues].name = "total_nof_esb_queues";
    submodule_data->defines[dnx_data_esb_general_define_total_nof_esb_queues].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_total_nof_esb_queues].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_nof_nif_eth_queues].name = "nof_nif_eth_queues";
    submodule_data->defines[dnx_data_esb_general_define_nof_nif_eth_queues].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_nof_nif_eth_queues].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_nof_eth_lp_queues].name = "nof_eth_lp_queues";
    submodule_data->defines[dnx_data_esb_general_define_nof_eth_lp_queues].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_nof_eth_lp_queues].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_nof_nif_ilkn_queues].name = "nof_nif_ilkn_queues";
    submodule_data->defines[dnx_data_esb_general_define_nof_nif_ilkn_queues].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_nof_nif_ilkn_queues].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_nof_ilkn_tdm_or_lp_queues].name = "nof_ilkn_tdm_or_lp_queues";
    submodule_data->defines[dnx_data_esb_general_define_nof_ilkn_tdm_or_lp_queues].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_nof_ilkn_tdm_or_lp_queues].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_nof_flexe_queues].name = "nof_flexe_queues";
    submodule_data->defines[dnx_data_esb_general_define_nof_flexe_queues].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_nof_flexe_queues].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_nof_special_queues].name = "nof_special_queues";
    submodule_data->defines[dnx_data_esb_general_define_nof_special_queues].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_nof_special_queues].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_nof_reserved_queues].name = "nof_reserved_queues";
    submodule_data->defines[dnx_data_esb_general_define_nof_reserved_queues].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_nof_reserved_queues].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_nof_fpc].name = "nof_fpc";
    submodule_data->defines[dnx_data_esb_general_define_nof_fpc].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_nof_fpc].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_total_nof_buffers].name = "total_nof_buffers";
    submodule_data->defines[dnx_data_esb_general_define_total_nof_buffers].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_total_nof_buffers].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_mux_cal_len].name = "mux_cal_len";
    submodule_data->defines[dnx_data_esb_general_define_mux_cal_len].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_mux_cal_len].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_mux_cal_window_size].name = "mux_cal_window_size";
    submodule_data->defines[dnx_data_esb_general_define_mux_cal_window_size].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_mux_cal_window_size].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_nif_credits_resolution].name = "nif_credits_resolution";
    submodule_data->defines[dnx_data_esb_general_define_nif_credits_resolution].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_nif_credits_resolution].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_nif_credits_rate_resolution].name = "nif_credits_rate_resolution";
    submodule_data->defines[dnx_data_esb_general_define_nif_credits_rate_resolution].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_nif_credits_rate_resolution].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_fpc_ptr_size].name = "fpc_ptr_size";
    submodule_data->defines[dnx_data_esb_general_define_fpc_ptr_size].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_fpc_ptr_size].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_nof_buffers_per_fpc].name = "nof_buffers_per_fpc";
    submodule_data->defines[dnx_data_esb_general_define_nof_buffers_per_fpc].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_nof_buffers_per_fpc].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_l1_mux_cal_res].name = "l1_mux_cal_res";
    submodule_data->defines[dnx_data_esb_general_define_l1_mux_cal_res].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_l1_mux_cal_res].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_tm_egr_queuing_mux_cal_res].name = "tm_egr_queuing_mux_cal_res";
    submodule_data->defines[dnx_data_esb_general_define_tm_egr_queuing_mux_cal_res].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_tm_egr_queuing_mux_cal_res].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_flexe_queue_id_base].name = "flexe_queue_id_base";
    submodule_data->defines[dnx_data_esb_general_define_flexe_queue_id_base].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_flexe_queue_id_base].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_ilkn_queue_id_base].name = "ilkn_queue_id_base";
    submodule_data->defines[dnx_data_esb_general_define_ilkn_queue_id_base].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_ilkn_queue_id_base].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_ilkn_tdm_or_lp_queue_id_base].name = "ilkn_tdm_or_lp_queue_id_base";
    submodule_data->defines[dnx_data_esb_general_define_ilkn_tdm_or_lp_queue_id_base].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_ilkn_tdm_or_lp_queue_id_base].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_eth_lp_queue_id_base].name = "eth_lp_queue_id_base";
    submodule_data->defines[dnx_data_esb_general_define_eth_lp_queue_id_base].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_eth_lp_queue_id_base].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_nof_egr_txi_interfaces].name = "nof_egr_txi_interfaces";
    submodule_data->defines[dnx_data_esb_general_define_nof_egr_txi_interfaces].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_nof_egr_txi_interfaces].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_max_queue_to_map_to_nif].name = "max_queue_to_map_to_nif";
    submodule_data->defines[dnx_data_esb_general_define_max_queue_to_map_to_nif].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_max_queue_to_map_to_nif].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_general_define_txi_irdy_th_factor].name = "txi_irdy_th_factor";
    submodule_data->defines[dnx_data_esb_general_define_txi_irdy_th_factor].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_txi_irdy_th_factor].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_esb_general_define_txi_irdy_th_divident].name = "txi_irdy_th_divident";
    submodule_data->defines[dnx_data_esb_general_define_txi_irdy_th_divident].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_txi_irdy_th_divident].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_esb_general_define_slow_port_dedicated_queue].name = "slow_port_dedicated_queue";
    submodule_data->defines[dnx_data_esb_general_define_slow_port_dedicated_queue].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_slow_port_dedicated_queue].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_esb_general_define_flexe_l1_dest_dedicated_queue].name = "flexe_l1_dest_dedicated_queue";
    submodule_data->defines[dnx_data_esb_general_define_flexe_l1_dest_dedicated_queue].doc = "";
    
    submodule_data->defines[dnx_data_esb_general_define_flexe_l1_dest_dedicated_queue].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_esb_general_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data esb general tables");

    
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].name = "if_esb_params";
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].doc = "";
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].size_of_values = sizeof(dnx_data_esb_general_if_esb_params_t);
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].entry_get = dnx_data_esb_general_if_esb_params_entry_str_get;

    
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].nof_keys = 1;
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].keys[0].name = "idx";
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].nof_values = 5;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values, dnxc_data_value_t, submodule_data->tables[dnx_data_esb_general_table_if_esb_params].nof_values, "_dnx_data_esb_general_table_if_esb_params table values");
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[0].name = "speed";
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[0].type = "int";
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[0].doc = "";
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[0].offset = UTILEX_OFFSETOF(dnx_data_esb_general_if_esb_params_t, speed);
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[1].name = "if_id";
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[1].type = "int";
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[1].doc = "";
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[1].offset = UTILEX_OFFSETOF(dnx_data_esb_general_if_esb_params_t, if_id);
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[2].name = "queue_id";
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[2].type = "int";
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[2].doc = "";
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[2].offset = UTILEX_OFFSETOF(dnx_data_esb_general_if_esb_params_t, queue_id);
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[3].name = "interleave_queue_id";
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[3].type = "int";
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[3].doc = "";
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[3].offset = UTILEX_OFFSETOF(dnx_data_esb_general_if_esb_params_t, interleave_queue_id);
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[4].name = "min_gap";
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[4].type = "int";
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[4].doc = "";
    submodule_data->tables[dnx_data_esb_general_table_if_esb_params].values[4].offset = UTILEX_OFFSETOF(dnx_data_esb_general_if_esb_params_t, min_gap);


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_esb_general_feature_get(
    int unit,
    dnx_data_esb_general_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, feature);
}


uint32
dnx_data_esb_general_total_nof_esb_queues_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_total_nof_esb_queues);
}

uint32
dnx_data_esb_general_nof_nif_eth_queues_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_nof_nif_eth_queues);
}

uint32
dnx_data_esb_general_nof_eth_lp_queues_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_nof_eth_lp_queues);
}

uint32
dnx_data_esb_general_nof_nif_ilkn_queues_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_nof_nif_ilkn_queues);
}

uint32
dnx_data_esb_general_nof_ilkn_tdm_or_lp_queues_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_nof_ilkn_tdm_or_lp_queues);
}

uint32
dnx_data_esb_general_nof_flexe_queues_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_nof_flexe_queues);
}

uint32
dnx_data_esb_general_nof_special_queues_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_nof_special_queues);
}

uint32
dnx_data_esb_general_nof_reserved_queues_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_nof_reserved_queues);
}

uint32
dnx_data_esb_general_nof_fpc_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_nof_fpc);
}

uint32
dnx_data_esb_general_total_nof_buffers_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_total_nof_buffers);
}

uint32
dnx_data_esb_general_mux_cal_len_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_mux_cal_len);
}

uint32
dnx_data_esb_general_mux_cal_window_size_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_mux_cal_window_size);
}

uint32
dnx_data_esb_general_nif_credits_resolution_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_nif_credits_resolution);
}

uint32
dnx_data_esb_general_nif_credits_rate_resolution_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_nif_credits_rate_resolution);
}

uint32
dnx_data_esb_general_fpc_ptr_size_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_fpc_ptr_size);
}

uint32
dnx_data_esb_general_nof_buffers_per_fpc_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_nof_buffers_per_fpc);
}

uint32
dnx_data_esb_general_l1_mux_cal_res_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_l1_mux_cal_res);
}

uint32
dnx_data_esb_general_tm_egr_queuing_mux_cal_res_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_tm_egr_queuing_mux_cal_res);
}

uint32
dnx_data_esb_general_flexe_queue_id_base_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_flexe_queue_id_base);
}

uint32
dnx_data_esb_general_ilkn_queue_id_base_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_ilkn_queue_id_base);
}

uint32
dnx_data_esb_general_ilkn_tdm_or_lp_queue_id_base_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_ilkn_tdm_or_lp_queue_id_base);
}

uint32
dnx_data_esb_general_eth_lp_queue_id_base_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_eth_lp_queue_id_base);
}

uint32
dnx_data_esb_general_nof_egr_txi_interfaces_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_nof_egr_txi_interfaces);
}

uint32
dnx_data_esb_general_max_queue_to_map_to_nif_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_max_queue_to_map_to_nif);
}

uint32
dnx_data_esb_general_txi_irdy_th_factor_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_txi_irdy_th_factor);
}

uint32
dnx_data_esb_general_txi_irdy_th_divident_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_txi_irdy_th_divident);
}

uint32
dnx_data_esb_general_slow_port_dedicated_queue_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_slow_port_dedicated_queue);
}

uint32
dnx_data_esb_general_flexe_l1_dest_dedicated_queue_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_define_flexe_l1_dest_dedicated_queue);
}



const dnx_data_esb_general_if_esb_params_t *
dnx_data_esb_general_if_esb_params_get(
    int unit,
    int idx)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_table_if_esb_params);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, idx, 0);
    return (const dnx_data_esb_general_if_esb_params_t *) data;

}


shr_error_e
dnx_data_esb_general_if_esb_params_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_esb_general_if_esb_params_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_table_if_esb_params);
    data = (const dnx_data_esb_general_if_esb_params_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->speed);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->if_id);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->queue_id);
            break;
        case 3:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->interleave_queue_id);
            break;
        case 4:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->min_gap);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnx_data_esb_general_if_esb_params_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_general, dnx_data_esb_general_table_if_esb_params);

}






static shr_error_e
dnx_data_esb_dbal_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "dbal";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_esb_dbal_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data esb dbal features");

    
    submodule_data->nof_defines = _dnx_data_esb_dbal_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data esb dbal defines");

    submodule_data->defines[dnx_data_esb_dbal_define_pm_internal_port_size].name = "pm_internal_port_size";
    submodule_data->defines[dnx_data_esb_dbal_define_pm_internal_port_size].doc = "";
    
    submodule_data->defines[dnx_data_esb_dbal_define_pm_internal_port_size].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_dbal_define_counter_config_mask_size].name = "counter_config_mask_size";
    submodule_data->defines[dnx_data_esb_dbal_define_counter_config_mask_size].doc = "";
    
    submodule_data->defines[dnx_data_esb_dbal_define_counter_config_mask_size].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_dbal_define_credit_size_bits].name = "credit_size_bits";
    submodule_data->defines[dnx_data_esb_dbal_define_credit_size_bits].doc = "";
    
    submodule_data->defines[dnx_data_esb_dbal_define_credit_size_bits].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_esb_dbal_define_txi_irdy_thresh_size].name = "txi_irdy_thresh_size";
    submodule_data->defines[dnx_data_esb_dbal_define_txi_irdy_thresh_size].doc = "";
    
    submodule_data->defines[dnx_data_esb_dbal_define_txi_irdy_thresh_size].flags |= DNXC_DATA_F_DEFINE;

    
    submodule_data->nof_tables = _dnx_data_esb_dbal_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data esb dbal tables");


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_esb_dbal_feature_get(
    int unit,
    dnx_data_esb_dbal_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_dbal, feature);
}


uint32
dnx_data_esb_dbal_pm_internal_port_size_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_dbal, dnx_data_esb_dbal_define_pm_internal_port_size);
}

uint32
dnx_data_esb_dbal_counter_config_mask_size_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_dbal, dnx_data_esb_dbal_define_counter_config_mask_size);
}

uint32
dnx_data_esb_dbal_credit_size_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_dbal, dnx_data_esb_dbal_define_credit_size_bits);
}

uint32
dnx_data_esb_dbal_txi_irdy_thresh_size_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_esb, dnx_data_esb_submodule_dbal, dnx_data_esb_dbal_define_txi_irdy_thresh_size);
}







shr_error_e
dnx_data_esb_init(
    int unit,
    dnxc_data_module_t *module_data)
{
    SHR_FUNC_INIT_VARS(unit);

    
    module_data->name = "esb";
    module_data->nof_submodules = _dnx_data_esb_submodule_nof;
    DNXC_DATA_ALLOC(module_data->submodules, dnxc_data_submodule_t, module_data->nof_submodules, "_dnxc_data esb submodules");

    
    SHR_IF_ERR_EXIT(dnx_data_esb_general_init(unit, &module_data->submodules[dnx_data_esb_submodule_general]));
    SHR_IF_ERR_EXIT(dnx_data_esb_dbal_init(unit, &module_data->submodules[dnx_data_esb_submodule_dbal]));
    

    if (dnxc_data_mgmt_is_jr2_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_esb_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_jr2_b0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_esb_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_jr2_b1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_esb_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2c_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_esb_attach(unit));
        SHR_IF_ERR_EXIT(j2c_a0_data_esb_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2c_a1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_esb_attach(unit));
        SHR_IF_ERR_EXIT(j2c_a0_data_esb_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_q2a_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_esb_attach(unit));
        SHR_IF_ERR_EXIT(q2a_a0_data_esb_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_q2a_b0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_esb_attach(unit));
        SHR_IF_ERR_EXIT(q2a_a0_data_esb_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_q2a_b1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_esb_attach(unit));
        SHR_IF_ERR_EXIT(q2a_a0_data_esb_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2p_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_esb_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a0_data_esb_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2p_a1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_esb_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a0_data_esb_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2p_a2(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_esb_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a0_data_esb_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2x_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_esb_attach(unit));
        SHR_IF_ERR_EXIT(j2x_a0_data_esb_attach(unit));
    }
    else

    {
        SHR_EXIT();
    }

exit:
    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE



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

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_egr_queuing.h>







static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_conditional_crdt_table_access_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_conditional_crdt_table_access;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 0;

    
    feature->data = 0;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_if_attributes_profile_exist_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_if_attributes_profile_exist;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_cos_map_is_per_pp_port_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_cos_map_is_per_pp_port;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_cos_map_per_pp_or_tm_selector_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_cos_map_per_pp_or_tm_selector;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_phantom_queues_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_phantom_queues;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_phantom_queues_prob_thresh_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_phantom_queues_prob_thresh;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_almost_empty_delay_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_almost_empty_delay;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 0;

    
    feature->data = 0;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_fqp_calender_set_select_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_fqp_calender_set_select;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_txq_max_byte_dedicated_th_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_txq_max_byte_dedicated_th;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_sub_calendar_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_sub_calendar;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 0;

    
    feature->data = 0;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_txq_tdm_irdy_sel_exist_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_txq_tdm_irdy_sel_exist;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 0;

    
    feature->data = 0;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_total_shaper_max_burst_exist_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_total_shaper_max_burst_exist;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_tcg_mapping_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_tcg_mapping;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 0;

    
    feature->data = 0;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_txq_reduce_max_credits_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_txq_reduce_max_credits;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_reserved_if_fc_config_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_reserved_if_fc_config;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 0;

    
    feature->data = 0;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_credit_init_mode_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_credit_init_mode;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_set_select_needs_to_be_set_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_set_select_needs_to_be_set;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 0;

    
    feature->data = 0;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_shared_hp_tdm_config_is_supported_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_shared_hp_tdm_config_is_supported;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 0;

    
    feature->data = 0;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_enhanced_nif_calendar_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_enhanced_nif_calendar;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_unicast_fifo_depth_not_supported_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_unicast_fifo_depth_not_supported;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_cal_read_en_is_supported_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_cal_read_en_is_supported;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_cal_windows_is_supported_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_cal_windows_is_supported;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_channel_id_mapping_is_supported_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_channel_id_mapping_is_supported;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_calendar_low_range_config_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int feature_index = dnx_data_egr_queuing_params_calendar_low_range_config;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}



static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_nof_bits_in_q_pair_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_nof_bits_in_q_pair;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_nof_bits_in_channel_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_nof_bits_in_channel;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 9;

    
    define->data = 9;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_nof_bits_in_chan_arb_calendar_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_nof_bits_in_chan_arb_calendar_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_nof_bits_in_port_prio_calendar_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_nof_bits_in_port_prio_calendar_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_nof_bits_in_tcg_calendar_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_nof_bits_in_tcg_calendar_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 10;

    
    define->data = 10;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_nof_calendars_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_nof_calendars;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 17;

    
    define->data = 17;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_nof_bits_in_egr_interface_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_nof_bits_in_egr_interface;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 9;

    
    define->data = 9;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_nof_bits_mirror_prio_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_nof_bits_mirror_prio;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_nof_bits_in_egr_ch_interface_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_nof_bits_in_egr_ch_interface;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 4;

    
    define->data = 4;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_nof_egr_interfaces_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_nof_egr_interfaces;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 392;

    
    define->data = 392;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_first_lp_egr_interface_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_first_lp_egr_interface;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 392;

    
    define->data = 392;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_nof_egr_ch_interfaces_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_nof_egr_ch_interfaces;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1 << dnx_data_egr_queuing.params.nof_bits_in_egr_ch_interface_get(unit);

    
    define->data = 1 << dnx_data_egr_queuing.params.nof_bits_in_egr_ch_interface_get(unit);

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_nof_egr_rcy_interfaces_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_nof_egr_rcy_interfaces;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_reserved_if_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_reserved_if;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 127;

    
    define->data = 127;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_egr_if_nif_base_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_egr_if_nif_base;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_nof_bits_in_nif_cal_len_pqp_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_nof_bits_in_nif_cal_len_pqp;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 14;

    
    define->data = 14;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_nif_cal_len_pqp_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_nif_cal_len_pqp;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 192*64;

    
    define->data = 192*64;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_nof_bits_in_nif_cal_len_fqp_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_nof_bits_in_nif_cal_len_fqp;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 14;

    
    define->data = 14;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_nif_cal_len_fqp_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_nif_cal_len_fqp;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 192*64;

    
    define->data = 192*64;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_sub_calendar_ifc_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_sub_calendar_ifc;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 127;

    
    define->data = 127;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_txq_max_credits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_txq_max_credits;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 90112;

    
    define->data = 90112;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_txq_max_credits_reduce_factor_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_txq_max_credits_reduce_factor;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 44;

    
    define->data = 44;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_pqp_ifc_almost_empty_th_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_pqp_ifc_almost_empty_th;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 22;

    
    define->data = 22;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_pqp_port_almost_empty_th_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_pqp_port_almost_empty_th;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 22;

    
    define->data = 22;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_pqp_queue_almost_empty_th_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_pqp_queue_almost_empty_th;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 14;

    
    define->data = 14;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_if_min_gap_priority_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_if_min_gap_priority_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 5;

    
    define->data = 5;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_egr_if_flexe_base_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_egr_if_flexe_base;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 72;

    
    define->data = 72;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_nof_dedicated_flexe_interfaces_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_nof_dedicated_flexe_interfaces;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 320;

    
    define->data = 320;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_egr_if_nif_alloc_start_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_egr_if_nif_alloc_start;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_egr_if_nif_alloc_end_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_egr_if_nif_alloc_end;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 71;

    
    define->data = 71;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_egr_if_ilkn_alloc_start_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_egr_if_ilkn_alloc_start;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 6;

    
    define->data = 6;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_egr_if_ilkn_alloc_end_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_egr_if_ilkn_alloc_end;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 7;

    
    define->data = 7;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_nof_fqp_profiles_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_nof_fqp_profiles;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 64;

    
    define->data = 64;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_min_gap_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_min_gap_bits;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 4;

    
    define->data = 4;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_burst_size_below_mtu_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int define_index = dnx_data_egr_queuing_params_define_burst_size_below_mtu;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_CUSTOM_FEATURE;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_suffix_enable;
    define->property.method_str = "suffix_enable";
    define->property.suffix = "burst_size_below_mtu";

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}



static shr_error_e
j2x_a0_dnx_data_egr_queuing_params_if_speed_params_set(
    int unit)
{
    int idx_index;
    int clock_rate_idx_index;
    dnx_data_egr_queuing_params_if_speed_params_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_params;
    int table_index = dnx_data_egr_queuing_params_table_if_speed_params;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 26;
    table->info_get.key_size[0] = 26;
    table->keys[1].size = 1;
    table->info_get.key_size[1] = 1;

    
    table->values[0].default_val = "-1";
    table->values[1].default_val = "-1";
    table->values[2].default_val = "-1";
    table->values[3].default_val = "-1";
    table->values[4].default_val = "-1";
    table->values[5].default_val = "-1";
    table->values[6].default_val = "-1";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }
    if (table->keys[1].size == 0 || table->info_get.key_size[1] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_egr_queuing_params_if_speed_params_t, (1 * (table->keys[0].size) * (table->keys[1].size) + 1  ), "data of dnx_data_egr_queuing_params_table_if_speed_params");

    
    default_data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->speed = -1;
    default_data->if_id = -1;
    default_data->crdt_size = -1;
    default_data->irdy_thr = -1;
    default_data->txq_max_bytes = -1;
    default_data->min_gap_hp = -1;
    default_data->fqp_min_gap = -1;
    
    for (idx_index = 0; idx_index < table->keys[0].size; idx_index++)
    {
        for (clock_rate_idx_index = 0; clock_rate_idx_index < table->keys[1].size; clock_rate_idx_index++)
        {
            data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, idx_index, clock_rate_idx_index);
            sal_memcpy(data, default_data, table->size_of_values);
        }
    }
    
    if (0 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->if_id = dnx_data_egr_queuing.params.egr_if_cpu_get(unit);
        data->crdt_size = 484;
        data->irdy_thr = 264;
        data->txq_max_bytes = 800;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 3;
    }
    if (1 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->if_id = dnx_data_egr_queuing.params.egr_if_oam_get(unit);
        data->crdt_size = 484;
        data->irdy_thr = 264;
        data->txq_max_bytes = 800;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 3;
    }
    if (2 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->if_id = dnx_data_egr_queuing.params.egr_if_olp_get(unit);
        data->crdt_size = 132;
        data->irdy_thr = 77;
        data->txq_max_bytes = 800;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 8;
    }
    if (3 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->if_id = dnx_data_egr_queuing.params.egr_if_eventor_get(unit);
        data->crdt_size = 176;
        data->irdy_thr = 99;
        data->txq_max_bytes = 800;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 8;
    }
    if (4 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->if_id = dnx_data_egr_queuing.params.egr_if_sat_get(unit);
        data->crdt_size = 2332;
        data->irdy_thr = 911;
        data->txq_max_bytes = 800;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 0;
    }
    if (6 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->if_id = dnx_data_egr_queuing.params.egr_if_rcy_get(unit);
        data->crdt_size = 3916;
        data->irdy_thr = 911;
        data->txq_max_bytes = 800;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 0;
    }
    if (7 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->speed = 10000;
        data->crdt_size = 132;
        data->irdy_thr = 77;
        data->txq_max_bytes = 32;
        data->min_gap_hp = 6;
        data->fqp_min_gap = 8;
    }
    if (8 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->speed = 25000;
        data->crdt_size = 176;
        data->irdy_thr = 99;
        data->txq_max_bytes = 96;
        data->min_gap_hp = 6;
        data->fqp_min_gap = 8;
    }
    if (9 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->speed = 40000;
        data->crdt_size = 264;
        data->irdy_thr = 143;
        data->txq_max_bytes = 96;
        data->min_gap_hp = 6;
        data->fqp_min_gap = 8;
    }
    if (10 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->speed = 50000;
        data->crdt_size = 308;
        data->irdy_thr = 170;
        data->txq_max_bytes = 256;
        data->min_gap_hp = 4;
        data->fqp_min_gap = 6;
    }
    if (11 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 0);
        data->speed = 100000;
        data->crdt_size = 572;
        data->irdy_thr = 308;
        data->txq_max_bytes = 256;
        data->min_gap_hp = 1;
        data->fqp_min_gap = 3;
    }
    if (12 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 0);
        data->speed = 200000;
        data->crdt_size = 1100;
        data->irdy_thr = 583;
        data->txq_max_bytes = 400;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 1;
    }
    if (13 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 0);
        data->speed = 300000;
        data->crdt_size = 1672;
        data->irdy_thr = 891;
        data->txq_max_bytes = 400;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 0;
    }
    if (14 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 14, 0);
        data->speed = 400000;
        data->crdt_size = 1936;
        data->irdy_thr = 911;
        data->txq_max_bytes = 400;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 0;
    }
    if (15 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 15, 0);
        data->speed = 600000;
        data->crdt_size = 2464;
        data->irdy_thr = 911;
        data->txq_max_bytes = 400;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 0;
    }
    if (16 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 16, 0);
        data->speed = 700000;
        data->crdt_size = 2552;
        data->irdy_thr = 911;
        data->txq_max_bytes = 400;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 0;
    }
    if (17 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 17, 0);
        data->speed = 800000;
        data->crdt_size = 2684;
        data->irdy_thr = 911;
        data->txq_max_bytes = 400;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 0;
    }
    if (18 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 18, 0);
        data->speed = 900000;
        data->crdt_size = 2904;
        data->irdy_thr = 911;
        data->txq_max_bytes = 400;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 0;
    }
    if (19 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 19, 0);
        data->speed = 1000000;
        data->crdt_size = 3124;
        data->irdy_thr = 911;
        data->txq_max_bytes = 400;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 0;
    }
    if (20 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 20, 0);
        data->speed = 1100000;
        data->crdt_size = 3344;
        data->irdy_thr = 911;
        data->txq_max_bytes = 400;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 0;
    }
    if (21 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 21, 0);
        data->speed = 1200000;
        data->crdt_size = 3388;
        data->irdy_thr = 911;
        data->txq_max_bytes = 400;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 0;
    }
    if (22 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 22, 0);
        data->speed = 1300000;
        data->crdt_size = 3608;
        data->irdy_thr = 911;
        data->txq_max_bytes = 400;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 0;
    }
    if (23 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 23, 0);
        data->speed = 1400000;
        data->crdt_size = 3828;
        data->irdy_thr = 911;
        data->txq_max_bytes = 400;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 0;
    }
    if (24 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 24, 0);
        data->speed = 1500000;
        data->crdt_size = 4004;
        data->irdy_thr = 911;
        data->txq_max_bytes = 400;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 0;
    }
    if (25 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_egr_queuing_params_if_speed_params_t *) dnxc_data_mgmt_table_data_get(unit, table, 25, 0);
        data->speed = 1600000;
        data->crdt_size = 4092;
        data->irdy_thr = 911;
        data->txq_max_bytes = 400;
        data->min_gap_hp = 0;
        data->fqp_min_gap = 0;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}





static shr_error_e
j2x_a0_dnx_data_egr_queuing_rate_measurement_is_supported_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_rate_measurement;
    int feature_index = dnx_data_egr_queuing_rate_measurement_is_supported;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}



static shr_error_e
j2x_a0_dnx_data_egr_queuing_rate_measurement_max_interval_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_rate_measurement;
    int define_index = dnx_data_egr_queuing_rate_measurement_define_max_interval;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0x1845C;

    
    define->data = 0x1845C;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_rate_measurement_promile_factor_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_rate_measurement;
    int define_index = dnx_data_egr_queuing_rate_measurement_define_promile_factor;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8*1000;

    
    define->data = 8*1000;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_rate_measurement_max_granularity_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_rate_measurement;
    int define_index = dnx_data_egr_queuing_rate_measurement_define_max_granularity;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 7;

    
    define->data = 7;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_rate_measurement_min_bytes_for_granularity_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_rate_measurement;
    int define_index = dnx_data_egr_queuing_rate_measurement_define_min_bytes_for_granularity;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 700;

    
    define->data = 700;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}







static shr_error_e
j2x_a0_dnx_data_egr_queuing_phantom_queues_nof_threshold_profiles_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_phantom_queues;
    int define_index = dnx_data_egr_queuing_phantom_queues_define_nof_threshold_profiles;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 4;

    
    define->data = 4;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_phantom_queues_max_threshold_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_phantom_queues;
    int define_index = dnx_data_egr_queuing_phantom_queues_define_max_threshold;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1000;

    
    define->data = 1000;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}






static shr_error_e
j2x_a0_dnx_data_egr_queuing_reassembly_prs_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_reassembly;
    int feature_index = dnx_data_egr_queuing_reassembly_prs;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 0;

    
    feature->data = 0;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}







static shr_error_e
j2x_a0_dnx_data_egr_queuing_general_is_used_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_general;
    int feature_index = dnx_data_egr_queuing_general_is_used;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = dnx_data_nif.global.l1_only_mode_get(unit) != DNX_PORT_NIF_L1_ONLY_MODE_WITHOUT_ILKN ||                                           (dnx_data_fabric.general.connect_mode_get(unit) != DNX_FABRIC_CONNECT_MODE_SINGLE_FAP && dnx_data_tdm.params.feature_get(unit, dnx_data_tdm_params_egress_bypass_enable) == 0);

    
    feature->data = dnx_data_nif.global.l1_only_mode_get(unit) != DNX_PORT_NIF_L1_ONLY_MODE_WITHOUT_ILKN ||                                           (dnx_data_fabric.general.connect_mode_get(unit) != DNX_FABRIC_CONNECT_MODE_SINGLE_FAP && dnx_data_tdm.params.feature_get(unit, dnx_data_tdm_params_egress_bypass_enable) == 0);

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_egr_queuing_general_power_down_supported_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = dnx_data_egr_queuing_submodule_general;
    int feature_index = dnx_data_egr_queuing_general_power_down_supported;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}





shr_error_e
j2x_a0_data_egr_queuing_attach(
    int unit)
{
    dnxc_data_module_t *module = NULL;
    dnxc_data_submodule_t *submodule = NULL;
    dnxc_data_define_t *define = NULL;
    dnxc_data_feature_t *feature = NULL;
    dnxc_data_table_t *table = NULL;
    int module_index = dnx_data_module_egr_queuing;
    int submodule_index = -1, data_index = -1;
    SHR_FUNC_INIT_VARS(unit);

    COMPILER_REFERENCE(define);
    COMPILER_REFERENCE(feature);
    COMPILER_REFERENCE(table);
    COMPILER_REFERENCE(submodule);
    COMPILER_REFERENCE(data_index);
    COMPILER_REFERENCE(submodule_index);
    module = &_dnxc_data[unit].modules[module_index];
    
    submodule_index = dnx_data_egr_queuing_submodule_params;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_egr_queuing_params_define_nof_bits_in_q_pair;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_nof_bits_in_q_pair_set;
    data_index = dnx_data_egr_queuing_params_define_nof_bits_in_channel;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_nof_bits_in_channel_set;
    data_index = dnx_data_egr_queuing_params_define_nof_bits_in_chan_arb_calendar_size;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_nof_bits_in_chan_arb_calendar_size_set;
    data_index = dnx_data_egr_queuing_params_define_nof_bits_in_port_prio_calendar_size;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_nof_bits_in_port_prio_calendar_size_set;
    data_index = dnx_data_egr_queuing_params_define_nof_bits_in_tcg_calendar_size;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_nof_bits_in_tcg_calendar_size_set;
    data_index = dnx_data_egr_queuing_params_define_nof_calendars;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_nof_calendars_set;
    data_index = dnx_data_egr_queuing_params_define_nof_bits_in_egr_interface;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_nof_bits_in_egr_interface_set;
    data_index = dnx_data_egr_queuing_params_define_nof_bits_mirror_prio;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_nof_bits_mirror_prio_set;
    data_index = dnx_data_egr_queuing_params_define_nof_bits_in_egr_ch_interface;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_nof_bits_in_egr_ch_interface_set;
    data_index = dnx_data_egr_queuing_params_define_nof_egr_interfaces;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_nof_egr_interfaces_set;
    data_index = dnx_data_egr_queuing_params_define_first_lp_egr_interface;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_first_lp_egr_interface_set;
    data_index = dnx_data_egr_queuing_params_define_nof_egr_ch_interfaces;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_nof_egr_ch_interfaces_set;
    data_index = dnx_data_egr_queuing_params_define_nof_egr_rcy_interfaces;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_nof_egr_rcy_interfaces_set;
    data_index = dnx_data_egr_queuing_params_define_reserved_if;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_reserved_if_set;
    data_index = dnx_data_egr_queuing_params_define_egr_if_nif_base;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_egr_if_nif_base_set;
    data_index = dnx_data_egr_queuing_params_define_nof_bits_in_nif_cal_len_pqp;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_nof_bits_in_nif_cal_len_pqp_set;
    data_index = dnx_data_egr_queuing_params_define_nif_cal_len_pqp;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_nif_cal_len_pqp_set;
    data_index = dnx_data_egr_queuing_params_define_nof_bits_in_nif_cal_len_fqp;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_nof_bits_in_nif_cal_len_fqp_set;
    data_index = dnx_data_egr_queuing_params_define_nif_cal_len_fqp;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_nif_cal_len_fqp_set;
    data_index = dnx_data_egr_queuing_params_define_sub_calendar_ifc;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_sub_calendar_ifc_set;
    data_index = dnx_data_egr_queuing_params_define_txq_max_credits;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_txq_max_credits_set;
    data_index = dnx_data_egr_queuing_params_define_txq_max_credits_reduce_factor;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_txq_max_credits_reduce_factor_set;
    data_index = dnx_data_egr_queuing_params_define_pqp_ifc_almost_empty_th;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_pqp_ifc_almost_empty_th_set;
    data_index = dnx_data_egr_queuing_params_define_pqp_port_almost_empty_th;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_pqp_port_almost_empty_th_set;
    data_index = dnx_data_egr_queuing_params_define_pqp_queue_almost_empty_th;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_pqp_queue_almost_empty_th_set;
    data_index = dnx_data_egr_queuing_params_define_if_min_gap_priority_size;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_if_min_gap_priority_size_set;
    data_index = dnx_data_egr_queuing_params_define_egr_if_flexe_base;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_egr_if_flexe_base_set;
    data_index = dnx_data_egr_queuing_params_define_nof_dedicated_flexe_interfaces;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_nof_dedicated_flexe_interfaces_set;
    data_index = dnx_data_egr_queuing_params_define_egr_if_nif_alloc_start;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_egr_if_nif_alloc_start_set;
    data_index = dnx_data_egr_queuing_params_define_egr_if_nif_alloc_end;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_egr_if_nif_alloc_end_set;
    data_index = dnx_data_egr_queuing_params_define_egr_if_ilkn_alloc_start;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_egr_if_ilkn_alloc_start_set;
    data_index = dnx_data_egr_queuing_params_define_egr_if_ilkn_alloc_end;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_egr_if_ilkn_alloc_end_set;
    data_index = dnx_data_egr_queuing_params_define_nof_fqp_profiles;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_nof_fqp_profiles_set;
    data_index = dnx_data_egr_queuing_params_define_min_gap_bits;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_min_gap_bits_set;
    data_index = dnx_data_egr_queuing_params_define_burst_size_below_mtu;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_params_burst_size_below_mtu_set;

    
    data_index = dnx_data_egr_queuing_params_conditional_crdt_table_access;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_conditional_crdt_table_access_set;
    data_index = dnx_data_egr_queuing_params_if_attributes_profile_exist;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_if_attributes_profile_exist_set;
    data_index = dnx_data_egr_queuing_params_cos_map_is_per_pp_port;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_cos_map_is_per_pp_port_set;
    data_index = dnx_data_egr_queuing_params_cos_map_per_pp_or_tm_selector;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_cos_map_per_pp_or_tm_selector_set;
    data_index = dnx_data_egr_queuing_params_phantom_queues;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_phantom_queues_set;
    data_index = dnx_data_egr_queuing_params_phantom_queues_prob_thresh;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_phantom_queues_prob_thresh_set;
    data_index = dnx_data_egr_queuing_params_almost_empty_delay;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_almost_empty_delay_set;
    data_index = dnx_data_egr_queuing_params_fqp_calender_set_select;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_fqp_calender_set_select_set;
    data_index = dnx_data_egr_queuing_params_txq_max_byte_dedicated_th;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_txq_max_byte_dedicated_th_set;
    data_index = dnx_data_egr_queuing_params_sub_calendar;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_sub_calendar_set;
    data_index = dnx_data_egr_queuing_params_txq_tdm_irdy_sel_exist;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_txq_tdm_irdy_sel_exist_set;
    data_index = dnx_data_egr_queuing_params_total_shaper_max_burst_exist;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_total_shaper_max_burst_exist_set;
    data_index = dnx_data_egr_queuing_params_tcg_mapping;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_tcg_mapping_set;
    data_index = dnx_data_egr_queuing_params_txq_reduce_max_credits;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_txq_reduce_max_credits_set;
    data_index = dnx_data_egr_queuing_params_reserved_if_fc_config;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_reserved_if_fc_config_set;
    data_index = dnx_data_egr_queuing_params_credit_init_mode;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_credit_init_mode_set;
    data_index = dnx_data_egr_queuing_params_set_select_needs_to_be_set;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_set_select_needs_to_be_set_set;
    data_index = dnx_data_egr_queuing_params_shared_hp_tdm_config_is_supported;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_shared_hp_tdm_config_is_supported_set;
    data_index = dnx_data_egr_queuing_params_enhanced_nif_calendar;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_enhanced_nif_calendar_set;
    data_index = dnx_data_egr_queuing_params_unicast_fifo_depth_not_supported;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_unicast_fifo_depth_not_supported_set;
    data_index = dnx_data_egr_queuing_params_cal_read_en_is_supported;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_cal_read_en_is_supported_set;
    data_index = dnx_data_egr_queuing_params_cal_windows_is_supported;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_cal_windows_is_supported_set;
    data_index = dnx_data_egr_queuing_params_channel_id_mapping_is_supported;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_channel_id_mapping_is_supported_set;
    data_index = dnx_data_egr_queuing_params_calendar_low_range_config;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_params_calendar_low_range_config_set;

    
    data_index = dnx_data_egr_queuing_params_table_if_speed_params;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_egr_queuing_params_if_speed_params_set;
    
    submodule_index = dnx_data_egr_queuing_submodule_rate_measurement;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_egr_queuing_rate_measurement_define_max_interval;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_rate_measurement_max_interval_set;
    data_index = dnx_data_egr_queuing_rate_measurement_define_promile_factor;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_rate_measurement_promile_factor_set;
    data_index = dnx_data_egr_queuing_rate_measurement_define_max_granularity;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_rate_measurement_max_granularity_set;
    data_index = dnx_data_egr_queuing_rate_measurement_define_min_bytes_for_granularity;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_rate_measurement_min_bytes_for_granularity_set;

    
    data_index = dnx_data_egr_queuing_rate_measurement_is_supported;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_rate_measurement_is_supported_set;

    
    
    submodule_index = dnx_data_egr_queuing_submodule_phantom_queues;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_egr_queuing_phantom_queues_define_nof_threshold_profiles;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_phantom_queues_nof_threshold_profiles_set;
    data_index = dnx_data_egr_queuing_phantom_queues_define_max_threshold;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_egr_queuing_phantom_queues_max_threshold_set;

    

    
    
    submodule_index = dnx_data_egr_queuing_submodule_reassembly;
    submodule = &module->submodules[submodule_index];

    

    
    data_index = dnx_data_egr_queuing_reassembly_prs;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_reassembly_prs_set;

    
    
    submodule_index = dnx_data_egr_queuing_submodule_general;
    submodule = &module->submodules[submodule_index];

    

    
    data_index = dnx_data_egr_queuing_general_is_used;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_general_is_used_set;
    data_index = dnx_data_egr_queuing_general_power_down_supported;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_egr_queuing_general_power_down_supported_set;

    

    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


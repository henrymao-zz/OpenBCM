
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_DEVICE

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_device.h>
#include <shared/utilex/utilex_integer_arithmetic.h>
#include <soc/dnxc/dnxc_otp.h>







static shr_error_e
jr2_a0_dnx_data_device_general_production_ready_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_production_ready;
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
jr2_a0_dnx_data_device_general_hard_reset_disable_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_hard_reset_disable;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 0;

    
    feature->data = 0;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;
    
    feature->property.name = spn_CUSTOM_FEATURE;
    feature->property.doc = 
        "\n"
    ;
    feature->property.method = dnxc_data_property_method_suffix_enable;
    feature->property.method_str = "suffix_enable";
    feature->property.suffix = "init_without_device_hard_reset";
    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &feature->property, -1, &feature->data));
    
    feature->flags |= (DNXC_DATA_F_PROPERTY);


    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_stop_on_access_init_error_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_stop_on_access_init_error;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;
    
    feature->property.name = spn_CUSTOM_FEATURE;
    feature->property.doc = 
        "\n"
    ;
    feature->property.method = dnxc_data_property_method_suffix_enable;
    feature->property.method_str = "suffix_enable";
    feature->property.suffix = "stop_on_access_init_error";
    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &feature->property, -1, &feature->data));
    
    feature->flags |= (DNXC_DATA_F_PROPERTY);


    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_multi_core_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_multi_core;
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
jr2_a0_dnx_data_device_general_rqp_ecc_err_exist_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_rqp_ecc_err_exist;
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
jr2_a0_dnx_data_device_general_new_crc32_calc_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_new_crc32_calc;
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
jr2_a0_dnx_data_device_general_delay_exist_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_delay_exist;
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
jr2_a0_dnx_data_device_general_serdes_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_serdes_support;
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
jr2_a0_dnx_data_device_general_snooping_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_snooping_support;
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
jr2_a0_dnx_data_device_general_mirroring_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_mirroring_support;
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
jr2_a0_dnx_data_device_general_injection_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_injection_support;
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
jr2_a0_dnx_data_device_general_fabric_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_fabric_support;
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
jr2_a0_dnx_data_device_general_flexe_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_flexe_support;
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
jr2_a0_dnx_data_device_general_cmic_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_cmic_support;
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
jr2_a0_dnx_data_device_general_real_interrupts_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_real_interrupts_support;
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
jr2_a0_dnx_data_device_general_i2c_hw_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_i2c_hw_support;
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
jr2_a0_dnx_data_device_general_ring_protection_hw_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_ring_protection_hw_support;
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
jr2_a0_dnx_data_device_general_hw_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_hw_support;
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
jr2_a0_dnx_data_device_general_fai_unknown_address_supported_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_fai_unknown_address_supported;
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
jr2_a0_dnx_data_device_general_itpp_cud_valid_check_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_itpp_cud_valid_check;
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
jr2_a0_dnx_data_device_general_high_traffic_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_high_traffic_support;
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
jr2_a0_dnx_data_device_general_ire_negative_delta_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_ire_negative_delta_support;
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
jr2_a0_dnx_data_device_general_disable_gated_top_level_sampling_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_disable_gated_top_level_sampling;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 1;

    
    feature->data = 1;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;
    
    feature->property.name = spn_CUSTOM_FEATURE;
    feature->property.doc = 
        "\n"
    ;
    feature->property.method = dnxc_data_property_method_suffix_enable;
    feature->property.method_str = "suffix_enable";
    feature->property.suffix = "disable_gated_top_level_sampling";
    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &feature->property, -1, &feature->data));
    
    feature->flags |= (DNXC_DATA_F_PROPERTY);


    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_ignore_mdb_sample_diff_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int feature_index = dnx_data_device_general_ignore_mdb_sample_diff;
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
jr2_a0_dnx_data_device_general_max_nof_system_ports_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_max_nof_system_ports;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 32*1024;

    
    define->data = 32*1024;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_invalid_system_port_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_invalid_system_port;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_device.general.max_nof_system_ports_get(unit) - 1;

    
    define->data = dnx_data_device.general.max_nof_system_ports_get(unit) - 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_fmq_system_port_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_fmq_system_port;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_device.general.max_nof_system_ports_get(unit) - 2;

    
    define->data = dnx_data_device.general.max_nof_system_ports_get(unit) - 2;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_invalid_fap_id_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_invalid_fap_id;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 2*1024 - 1;

    
    define->data = 2*1024 - 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_fap_ids_per_core_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_fap_ids_per_core_bits;
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
jr2_a0_dnx_data_device_general_nof_cores_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_nof_cores;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 2;

    
    define->data = 2;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_valid_cores_bitmap_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_valid_cores_bitmap;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0x3;

    
    define->data = 0x3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_nof_cores_for_traffic_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_nof_cores_for_traffic;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 2;

    
    define->data = 2;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_max_nof_layer_protocols_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_max_nof_layer_protocols;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 32;

    
    define->data = 32;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_nof_core_groups_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_nof_core_groups;
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
jr2_a0_dnx_data_device_general_nof_cores_per_core_group_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_nof_cores_per_core_group;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = (dnx_data_device.general.nof_cores_get(unit)/dnx_data_device.general.nof_core_groups_get(unit));

    
    define->data = (dnx_data_device.general.nof_cores_get(unit)/dnx_data_device.general.nof_core_groups_get(unit));

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_nof_avs_status_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_nof_avs_status_bits;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 3;

    
    define->data = 3;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_core_max_nof_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_core_max_nof_bits;
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
jr2_a0_dnx_data_device_general_max_nof_fap_ids_per_core_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_max_nof_fap_ids_per_core;
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
jr2_a0_dnx_data_device_general_max_nof_fap_ids_per_device_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_max_nof_fap_ids_per_device;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_device.general.nof_cores_get(unit) * dnx_data_device.general.max_nof_fap_ids_per_core_get(unit);

    
    define->data = dnx_data_device.general.nof_cores_get(unit) * dnx_data_device.general.max_nof_fap_ids_per_core_get(unit);

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_core_clock_khz_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_core_clock_khz;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1000000;

    
    define->data = 1000000;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_CORE_CLOCK_SPEED;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_suffix_range;
    define->property.method_str = "suffix_range";
    define->property.suffix = "khz";
    define->property.range_min = 300000;
    define->property.range_max = 3000000;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_system_ref_core_clock_khz_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_system_ref_core_clock_khz;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1200000;

    
    define->data = 1200000;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_SYSTEM_REF_CORE_CLOCK;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_suffix_range;
    define->property.method_str = "suffix_range";
    define->property.suffix = "khz";
    define->property.range_min = 300000;
    define->property.range_max = 3000000;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_ref_core_clock_mhz_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_ref_core_clock_mhz;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 25;

    
    define->data = 25;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_core_clock_ndiv_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_core_clock_ndiv_size;
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
jr2_a0_dnx_data_device_general_core_clock_mdiv_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_core_clock_mdiv_size;
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
jr2_a0_dnx_data_device_general_core_clock_ndiv_offset_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_core_clock_ndiv_offset;
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
jr2_a0_dnx_data_device_general_core_clock_mdiv_offset_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_core_clock_mdiv_offset;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 24;

    
    define->data = 24;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_bus_size_in_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_bus_size_in_bits;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 4096;

    
    define->data = 4096;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_maximal_core_bandwidth_mbps_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_maximal_core_bandwidth_mbps;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_device.general.bus_size_in_bits_get(unit)*(dnx_data_device.general.core_clock_khz_get(unit) / 1000);

    
    define->data = dnx_data_device.general.bus_size_in_bits_get(unit)*(dnx_data_device.general.core_clock_khz_get(unit) / 1000);

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_enforce_maximal_core_bandwidth_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_enforce_maximal_core_bandwidth;
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
jr2_a0_dnx_data_device_general_max_mpps_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_max_mpps;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = -1;

    
    define->data = -1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_packet_per_clock_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_packet_per_clock;
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
jr2_a0_dnx_data_device_general_nof_faps_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_nof_faps;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 2*1024;

    
    define->data = 2*1024;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_FABRIC_CONNECT_MODE;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_direct_map;
    define->property.method_str = "direct_map";
    define->property.nof_mapping = 3;
    DNXC_DATA_ALLOC(define->property.mapping, dnxc_data_property_map_t, define->property.nof_mapping, "dnxc_data property mapping");

    define->property.mapping[0].name = "FE";
    define->property.mapping[0].val = 2*1024;
    define->property.mapping[0].is_default = 1 ;
    define->property.mapping[1].name = "SINGLE_FAP";
    define->property.mapping[1].val = 16;
    define->property.mapping[2].name = "MESH";
    define->property.mapping[2].val = 16;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_device_id_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_device_id;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0x8690;

    
    define->data = 0x8690;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_nof_sku_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_nof_sku_bits;
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
jr2_a0_dnx_data_device_general_bist_enable_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_bist_enable;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_BIST_ENABLE;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_range;
    define->property.method_str = "range";
    define->property.range_min = 0;
    define->property.range_max = 9999;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_nof_bits_for_nof_cores_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int define_index = dnx_data_device_general_define_nof_bits_for_nof_cores;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = utilex_log2_round_up(dnx_data_device.general.nof_cores_get(unit));

    
    define->data = utilex_log2_round_up(dnx_data_device.general.nof_cores_get(unit));

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}



static shr_error_e
jr2_a0_dnx_data_device_general_ecc_err_masking_key_map(
    int unit,
    int key0_val,
    int key1_val,
    int *key0_index,
    int *key1_index)
{
    SHR_FUNC_INIT_VARS(unit);

    switch (key0_val)
    {
        case SOC_BLK_CGM:
            *key0_index = 0;
            break;
        case SOC_BLK_ECGM:
            *key0_index = 1;
            break;
        default:
            *key0_index = -1;
            break;
    }

    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_ecc_err_masking_key_reverse_map(
    int unit,
    int key0_index,
    int key1_index,
    int *key0_val,
    int *key1_val)
{
    SHR_FUNC_INIT_VARS(unit);

    switch (key0_index)
    {
        case 0:
            *key0_val = SOC_BLK_CGM;
            break;
        case 1:
            *key0_val = SOC_BLK_ECGM;
            break;
        default:
            *key0_val = -1;
            break;
    }

    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_ecc_err_masking_set(
    int unit)
{
    int block_type_index;
    dnx_data_device_general_ecc_err_masking_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int table_index = dnx_data_device_general_table_ecc_err_masking;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 2;
    table->info_get.key_size[0] = 2;

    
    table->values[0].default_val = "-1";
    table->values[1].default_val = "-1";
    table->values[2].default_val = "-1";
    table->values[3].default_val = "-1";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_device_general_ecc_err_masking_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_device_general_table_ecc_err_masking");

    
    default_data = (dnx_data_device_general_ecc_err_masking_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->ecc_1bit_err_mask_reg = -1;
    default_data->ecc_1bit_err_field[0] = -1;
    default_data->ecc_2bit_err_mask_reg = -1;
    default_data->ecc_2bit_err_field[0] = -1;
    
    for (block_type_index = 0; block_type_index < table->keys[0].size; block_type_index++)
    {
        data = (dnx_data_device_general_ecc_err_masking_t *) dnxc_data_mgmt_table_data_get(unit, table, block_type_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    table->key_map = jr2_a0_dnx_data_device_general_ecc_err_masking_key_map;
    table->key_map_reverse = jr2_a0_dnx_data_device_general_ecc_err_masking_key_reverse_map;
    
    data = (dnx_data_device_general_ecc_err_masking_t *) dnxc_data_mgmt_table_data_get(unit, table, SOC_BLK_ECGM, 0);
    data->ecc_1bit_err_mask_reg = ECGM_ECC_ERR_1B_MONITOR_MEM_MASKr;
    SHR_RANGE_VERIFY(12, 0, DNX_MAX_NOF_ECC_ERR_MEMS, _SHR_E_INTERNAL, "out of bound access to array")
    data->ecc_1bit_err_field[0] = QDCM_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[1] = QQSM_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[2] = PDCM_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[3] = PQSM_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[4] = FDCM_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[5] = FQSM_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[6] = -1;
    data->ecc_1bit_err_field[7] = -1;
    data->ecc_1bit_err_field[8] = -1;
    data->ecc_1bit_err_field[9] = -1;
    data->ecc_1bit_err_field[10] = -1;
    data->ecc_1bit_err_field[11] = -1;
    data->ecc_2bit_err_mask_reg = ECGM_ECC_ERR_2B_MONITOR_MEM_MASKr;
    SHR_RANGE_VERIFY(12, 0, DNX_MAX_NOF_ECC_ERR_MEMS, _SHR_E_INTERNAL, "out of bound access to array")
    data->ecc_2bit_err_field[0] = QDCM_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[1] = QQSM_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[2] = PDCM_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[3] = PQSM_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[4] = FDCM_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[5] = FQSM_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[6] = -1;
    data->ecc_2bit_err_field[7] = -1;
    data->ecc_2bit_err_field[8] = -1;
    data->ecc_2bit_err_field[9] = -1;
    data->ecc_2bit_err_field[10] = -1;
    data->ecc_2bit_err_field[11] = -1;
    data = (dnx_data_device_general_ecc_err_masking_t *) dnxc_data_mgmt_table_data_get(unit, table, SOC_BLK_CGM, 0);
    data->ecc_1bit_err_mask_reg = CGM_ECC_ERR_1B_MONITOR_MEM_MASKr;
    SHR_RANGE_VERIFY(12, 0, DNX_MAX_NOF_ECC_ERR_MEMS, _SHR_E_INTERNAL, "out of bound access to array")
    data->ecc_1bit_err_field[0] = VSQE_WORDS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[1] = VSQE_SRAM_PDS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[2] = VSQE_SRAM_BUFFERS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[3] = VSQC_WORDS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[4] = VSQD_SRAM_PDS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[5] = VSQD_SRAM_BUFFERS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[6] = VSQD_WORDS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[7] = VSQF_SRAM_BUFFERS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[8] = VSQF_WORDS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[9] = VSQF_SRAM_PDS_STATE_ECC_1B_ERR_MASKf;
    data->ecc_1bit_err_field[10] = -1;
    data->ecc_1bit_err_field[11] = -1;
    data->ecc_2bit_err_mask_reg = CGM_ECC_ERR_2B_MONITOR_MEM_MASKr;
    SHR_RANGE_VERIFY(12, 0, DNX_MAX_NOF_ECC_ERR_MEMS, _SHR_E_INTERNAL, "out of bound access to array")
    data->ecc_2bit_err_field[0] = VSQE_WORDS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[1] = VSQE_SRAM_PDS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[2] = VSQE_SRAM_BUFFERS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[3] = VSQC_WORDS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[4] = VSQD_SRAM_PDS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[5] = VSQD_SRAM_BUFFERS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[6] = VSQD_WORDS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[7] = VSQF_SRAM_BUFFERS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[8] = VSQF_WORDS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[9] = VSQF_SRAM_PDS_STATE_ECC_2B_ERR_MASKf;
    data->ecc_2bit_err_field[10] = -1;
    data->ecc_2bit_err_field[11] = -1;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_general_ctest_full_file_indentifier_set(
    int unit)
{
    dnx_data_device_general_ctest_full_file_indentifier_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_general;
    int table_index = dnx_data_device_general_table_ctest_full_file_indentifier;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "DNX";
    table->values[1].default_val = "\0";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_device_general_ctest_full_file_indentifier_t, (1 + 1  ), "data of dnx_data_device_general_table_ctest_full_file_indentifier");

    
    default_data = (dnx_data_device_general_ctest_full_file_indentifier_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->family_name = "DNX";
    default_data->family_number = "\0";
    
    data = (dnx_data_device_general_ctest_full_file_indentifier_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}







static shr_error_e
jr2_a0_dnx_data_device_regression_regression_parms_set(
    int unit)
{
    dnx_data_device_regression_regression_parms_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_regression;
    int table_index = dnx_data_device_regression_table_regression_parms;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "\0";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_device_regression_regression_parms_t, (1 + 1  ), "data of dnx_data_device_regression_table_regression_parms");

    
    default_data = (dnx_data_device_regression_regression_parms_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->system_mode_name = "\0";
    
    data = (dnx_data_device_regression_regression_parms_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);
    
    table->values[0].property.name = "dvapi_system_indicator";
    table->values[0].property.doc =
        "\n"
    ;
    table->values[0].property.method = dnxc_data_property_method_str;
    table->values[0].property.method_str = "str";

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));

    data = (dnx_data_device_regression_regression_parms_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &table->values[0].property, -1, &data->system_mode_name));
    
    table->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}





static shr_error_e
jr2_a0_dnx_data_device_emulation_fmac_supported_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_emulation;
    int feature_index = dnx_data_device_emulation_fmac_supported;
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
jr2_a0_dnx_data_device_emulation_ecc_enable_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_emulation;
    int feature_index = dnx_data_device_emulation_ecc_enable;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 0;

    
    feature->data = 0;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;
    
    feature->property.name = spn_CUSTOM_FEATURE;
    feature->property.doc = 
        "\n"
    ;
    feature->property.method = dnxc_data_property_method_suffix_enable;
    feature->property.method_str = "suffix_enable";
    feature->property.suffix = "ecc_enable";
    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &feature->property, -1, &feature->data));
    
    feature->flags |= (DNXC_DATA_F_PROPERTY);


    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}



static shr_error_e
jr2_a0_dnx_data_device_emulation_emulation_system_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_emulation;
    int define_index = dnx_data_device_emulation_define_emulation_system;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_DIAG_EMULATOR_PARTIAL_INIT;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_range;
    define->property.method_str = "range";
    define->property.range_min = 0;
    define->property.range_max = 3;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}







static shr_error_e
jr2_a0_dnx_data_device_otp_nof_words_in_row_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_otp;
    int define_index = dnx_data_device_otp_define_nof_words_in_row;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 2;

    
    define->data = 2;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_otp_read_timeout_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_otp;
    int define_index = dnx_data_device_otp_define_read_timeout;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 100000;

    
    define->data = 100000;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}



static shr_error_e
jr2_a0_dnx_data_device_otp_otp_instance_attributes_set(
    int unit)
{
    int otp_instance_index_index;
    dnx_data_device_otp_otp_instance_attributes_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_otp;
    int table_index = dnx_data_device_otp_table_otp_instance_attributes;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = SOC_DNXC_OTP_INSTANCE_COUNT;
    table->info_get.key_size[0] = SOC_DNXC_OTP_INSTANCE_COUNT;

    
    table->values[0].default_val = "-1";
    table->values[1].default_val = "0";
    table->values[2].default_val = "-1";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_device_otp_otp_instance_attributes_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_device_otp_table_otp_instance_attributes");

    
    default_data = (dnx_data_device_otp_otp_instance_attributes_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->block_id = -1;
    default_data->is_supported = 0;
    default_data->size = -1;
    
    for (otp_instance_index_index = 0; otp_instance_index_index < table->keys[0].size; otp_instance_index_index++)
    {
        data = (dnx_data_device_otp_otp_instance_attributes_t *) dnxc_data_mgmt_table_data_get(unit, table, otp_instance_index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (SOC_DNXC_OTP_INSTANCE_GENERAL_USE < table->keys[0].size)
    {
        data = (dnx_data_device_otp_otp_instance_attributes_t *) dnxc_data_mgmt_table_data_get(unit, table, SOC_DNXC_OTP_INSTANCE_GENERAL_USE, 0);
        data->block_id = 1056;
        data->is_supported = 1;
        data->size = 18432;
    }
    if (SOC_DNXC_OTP_INSTANCE_HBM_0 < table->keys[0].size)
    {
        data = (dnx_data_device_otp_otp_instance_attributes_t *) dnxc_data_mgmt_table_data_get(unit, table, SOC_DNXC_OTP_INSTANCE_HBM_0, 0);
        data->block_id = 896;
        data->is_supported = 1;
    }
    if (SOC_DNXC_OTP_INSTANCE_HBM_1 < table->keys[0].size)
    {
        data = (dnx_data_device_otp_otp_instance_attributes_t *) dnxc_data_mgmt_table_data_get(unit, table, SOC_DNXC_OTP_INSTANCE_HBM_1, 0);
        data->block_id = 912;
        data->is_supported = 1;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_device_otp_reg_addresses_set(
    int unit)
{
    dnx_data_device_otp_reg_addresses_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_otp;
    int table_index = dnx_data_device_otp_table_reg_addresses;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "0x200";
    table->values[1].default_val = "0x228";
    table->values[2].default_val = "0x204";
    table->values[3].default_val = "0x208";
    table->values[4].default_val = "0x20c";
    table->values[5].default_val = "0x210";
    table->values[6].default_val = "0x25c";
    table->values[7].default_val = "0x260";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_device_otp_reg_addresses_t, (1 + 1  ), "data of dnx_data_device_otp_table_reg_addresses");

    
    default_data = (dnx_data_device_otp_reg_addresses_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->mode = 0x200;
    default_data->cpu_addr = 0x228;
    default_data->cmd = 0x204;
    default_data->cmd_start = 0x208;
    default_data->cpu_status = 0x20c;
    default_data->cpu_data_0 = 0x210;
    default_data->cpu_data_1 = 0x25c;
    default_data->cpu_data_2 = 0x260;
    
    data = (dnx_data_device_otp_reg_addresses_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}





static shr_error_e
jr2_a0_dnx_data_device_docs_is_fap_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_device;
    int submodule_index = dnx_data_device_submodule_docs;
    int feature_index = dnx_data_device_docs_is_fap;
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
jr2_a0_data_device_attach(
    int unit)
{
    dnxc_data_module_t *module = NULL;
    dnxc_data_submodule_t *submodule = NULL;
    dnxc_data_define_t *define = NULL;
    dnxc_data_feature_t *feature = NULL;
    dnxc_data_table_t *table = NULL;
    int module_index = dnx_data_module_device;
    int submodule_index = -1, data_index = -1;
    SHR_FUNC_INIT_VARS(unit);

    COMPILER_REFERENCE(define);
    COMPILER_REFERENCE(feature);
    COMPILER_REFERENCE(table);
    COMPILER_REFERENCE(submodule);
    COMPILER_REFERENCE(data_index);
    COMPILER_REFERENCE(submodule_index);
    module = &_dnxc_data[unit].modules[module_index];
    
    submodule_index = dnx_data_device_submodule_general;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_device_general_define_max_nof_system_ports;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_max_nof_system_ports_set;
    data_index = dnx_data_device_general_define_invalid_system_port;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_invalid_system_port_set;
    data_index = dnx_data_device_general_define_fmq_system_port;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_fmq_system_port_set;
    data_index = dnx_data_device_general_define_invalid_fap_id;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_invalid_fap_id_set;
    data_index = dnx_data_device_general_define_fap_ids_per_core_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_fap_ids_per_core_bits_set;
    data_index = dnx_data_device_general_define_nof_cores;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_nof_cores_set;
    data_index = dnx_data_device_general_define_valid_cores_bitmap;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_valid_cores_bitmap_set;
    data_index = dnx_data_device_general_define_nof_cores_for_traffic;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_nof_cores_for_traffic_set;
    data_index = dnx_data_device_general_define_max_nof_layer_protocols;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_max_nof_layer_protocols_set;
    data_index = dnx_data_device_general_define_nof_core_groups;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_nof_core_groups_set;
    data_index = dnx_data_device_general_define_nof_cores_per_core_group;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_nof_cores_per_core_group_set;
    data_index = dnx_data_device_general_define_nof_avs_status_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_nof_avs_status_bits_set;
    data_index = dnx_data_device_general_define_core_max_nof_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_core_max_nof_bits_set;
    data_index = dnx_data_device_general_define_max_nof_fap_ids_per_core;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_max_nof_fap_ids_per_core_set;
    data_index = dnx_data_device_general_define_max_nof_fap_ids_per_device;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_max_nof_fap_ids_per_device_set;
    data_index = dnx_data_device_general_define_core_clock_khz;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_core_clock_khz_set;
    data_index = dnx_data_device_general_define_system_ref_core_clock_khz;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_system_ref_core_clock_khz_set;
    data_index = dnx_data_device_general_define_ref_core_clock_mhz;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_ref_core_clock_mhz_set;
    data_index = dnx_data_device_general_define_core_clock_ndiv_size;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_core_clock_ndiv_size_set;
    data_index = dnx_data_device_general_define_core_clock_mdiv_size;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_core_clock_mdiv_size_set;
    data_index = dnx_data_device_general_define_core_clock_ndiv_offset;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_core_clock_ndiv_offset_set;
    data_index = dnx_data_device_general_define_core_clock_mdiv_offset;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_core_clock_mdiv_offset_set;
    data_index = dnx_data_device_general_define_bus_size_in_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_bus_size_in_bits_set;
    data_index = dnx_data_device_general_define_maximal_core_bandwidth_mbps;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_maximal_core_bandwidth_mbps_set;
    data_index = dnx_data_device_general_define_enforce_maximal_core_bandwidth;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_enforce_maximal_core_bandwidth_set;
    data_index = dnx_data_device_general_define_max_mpps;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_max_mpps_set;
    data_index = dnx_data_device_general_define_packet_per_clock;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_packet_per_clock_set;
    data_index = dnx_data_device_general_define_nof_faps;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_nof_faps_set;
    data_index = dnx_data_device_general_define_device_id;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_device_id_set;
    data_index = dnx_data_device_general_define_nof_sku_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_nof_sku_bits_set;
    data_index = dnx_data_device_general_define_bist_enable;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_bist_enable_set;
    data_index = dnx_data_device_general_define_nof_bits_for_nof_cores;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_general_nof_bits_for_nof_cores_set;

    
    data_index = dnx_data_device_general_production_ready;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_production_ready_set;
    data_index = dnx_data_device_general_hard_reset_disable;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_hard_reset_disable_set;
    data_index = dnx_data_device_general_stop_on_access_init_error;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_stop_on_access_init_error_set;
    data_index = dnx_data_device_general_multi_core;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_multi_core_set;
    data_index = dnx_data_device_general_rqp_ecc_err_exist;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_rqp_ecc_err_exist_set;
    data_index = dnx_data_device_general_new_crc32_calc;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_new_crc32_calc_set;
    data_index = dnx_data_device_general_delay_exist;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_delay_exist_set;
    data_index = dnx_data_device_general_serdes_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_serdes_support_set;
    data_index = dnx_data_device_general_snooping_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_snooping_support_set;
    data_index = dnx_data_device_general_mirroring_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_mirroring_support_set;
    data_index = dnx_data_device_general_injection_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_injection_support_set;
    data_index = dnx_data_device_general_fabric_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_fabric_support_set;
    data_index = dnx_data_device_general_flexe_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_flexe_support_set;
    data_index = dnx_data_device_general_cmic_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_cmic_support_set;
    data_index = dnx_data_device_general_real_interrupts_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_real_interrupts_support_set;
    data_index = dnx_data_device_general_i2c_hw_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_i2c_hw_support_set;
    data_index = dnx_data_device_general_ring_protection_hw_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_ring_protection_hw_support_set;
    data_index = dnx_data_device_general_hw_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_hw_support_set;
    data_index = dnx_data_device_general_fai_unknown_address_supported;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_fai_unknown_address_supported_set;
    data_index = dnx_data_device_general_itpp_cud_valid_check;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_itpp_cud_valid_check_set;
    data_index = dnx_data_device_general_high_traffic_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_high_traffic_support_set;
    data_index = dnx_data_device_general_ire_negative_delta_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_ire_negative_delta_support_set;
    data_index = dnx_data_device_general_disable_gated_top_level_sampling;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_disable_gated_top_level_sampling_set;
    data_index = dnx_data_device_general_ignore_mdb_sample_diff;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_general_ignore_mdb_sample_diff_set;

    
    data_index = dnx_data_device_general_table_ecc_err_masking;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_dnx_data_device_general_ecc_err_masking_set;
    data_index = dnx_data_device_general_table_ctest_full_file_indentifier;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_dnx_data_device_general_ctest_full_file_indentifier_set;
    
    submodule_index = dnx_data_device_submodule_regression;
    submodule = &module->submodules[submodule_index];

    

    

    
    data_index = dnx_data_device_regression_table_regression_parms;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_dnx_data_device_regression_regression_parms_set;
    
    submodule_index = dnx_data_device_submodule_emulation;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_device_emulation_define_emulation_system;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_emulation_emulation_system_set;

    
    data_index = dnx_data_device_emulation_fmac_supported;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_emulation_fmac_supported_set;
    data_index = dnx_data_device_emulation_ecc_enable;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_emulation_ecc_enable_set;

    
    
    submodule_index = dnx_data_device_submodule_otp;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_device_otp_define_nof_words_in_row;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_otp_nof_words_in_row_set;
    data_index = dnx_data_device_otp_define_read_timeout;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_device_otp_read_timeout_set;

    

    
    data_index = dnx_data_device_otp_table_otp_instance_attributes;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_dnx_data_device_otp_otp_instance_attributes_set;
    data_index = dnx_data_device_otp_table_reg_addresses;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_dnx_data_device_otp_reg_addresses_set;
    
    submodule_index = dnx_data_device_submodule_docs;
    submodule = &module->submodules[submodule_index];

    

    
    data_index = dnx_data_device_docs_is_fap;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_device_docs_is_fap_set;

    

    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


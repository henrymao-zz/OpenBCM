
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_PTP

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_ptp.h>







static shr_error_e
jr2_a0_dnx_data_ptp_general_has_trap_code_offset_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_ptp;
    int submodule_index = dnx_data_ptp_submodule_general;
    int feature_index = dnx_data_ptp_general_has_trap_code_offset;
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
jr2_a0_dnx_data_ptp_general_has_external_brcm_mac_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_ptp;
    int submodule_index = dnx_data_ptp_submodule_general;
    int feature_index = dnx_data_ptp_general_has_external_brcm_mac;
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
jr2_a0_dnx_data_ptp_general_has_tx_compensation_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_ptp;
    int submodule_index = dnx_data_ptp_submodule_general;
    int feature_index = dnx_data_ptp_general_has_tx_compensation;
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
jr2_a0_dnx_data_ptp_general_has_f1588_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_ptp;
    int submodule_index = dnx_data_ptp_submodule_general;
    int feature_index = dnx_data_ptp_general_has_f1588;
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
jr2_a0_dnx_data_ptp_general_has_pp_dsp_ieee_1588_mac_enable_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_ptp;
    int submodule_index = dnx_data_ptp_submodule_general;
    int feature_index = dnx_data_ptp_general_has_pp_dsp_ieee_1588_mac_enable;
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
jr2_a0_dnx_data_ptp_general_nof_port_profiles_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_ptp;
    int submodule_index = dnx_data_ptp_submodule_general;
    int define_index = dnx_data_ptp_general_define_nof_port_profiles;
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
jr2_a0_dnx_data_ptp_ptp_firmware_ptp_cosq_port_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_ptp;
    int submodule_index = dnx_data_ptp_submodule_ptp_firmware;
    int define_index = dnx_data_ptp_ptp_firmware_define_ptp_cosq_port;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 204;

    
    define->data = 204;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_CUSTOM_FEATURE;
    define->property.doc = 
        "\n"
        "Local port used for PTP Firmware's packets RX and TX.\n"
        "\n"
    ;
    define->property.method = dnxc_data_property_method_suffix_range;
    define->property.method_str = "suffix_range";
    define->property.suffix = "ptp_cosq_port";
    define->property.range_min = 1;
    define->property.range_max = 65536;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}




shr_error_e
jr2_a0_data_ptp_attach(
    int unit)
{
    dnxc_data_module_t *module = NULL;
    dnxc_data_submodule_t *submodule = NULL;
    dnxc_data_define_t *define = NULL;
    dnxc_data_feature_t *feature = NULL;
    dnxc_data_table_t *table = NULL;
    int module_index = dnx_data_module_ptp;
    int submodule_index = -1, data_index = -1;
    SHR_FUNC_INIT_VARS(unit);

    COMPILER_REFERENCE(define);
    COMPILER_REFERENCE(feature);
    COMPILER_REFERENCE(table);
    COMPILER_REFERENCE(submodule);
    COMPILER_REFERENCE(data_index);
    COMPILER_REFERENCE(submodule_index);
    module = &_dnxc_data[unit].modules[module_index];
    
    submodule_index = dnx_data_ptp_submodule_general;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_ptp_general_define_nof_port_profiles;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_ptp_general_nof_port_profiles_set;

    
    data_index = dnx_data_ptp_general_has_trap_code_offset;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_ptp_general_has_trap_code_offset_set;
    data_index = dnx_data_ptp_general_has_external_brcm_mac;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_ptp_general_has_external_brcm_mac_set;
    data_index = dnx_data_ptp_general_has_tx_compensation;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_ptp_general_has_tx_compensation_set;
    data_index = dnx_data_ptp_general_has_f1588;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_ptp_general_has_f1588_set;
    data_index = dnx_data_ptp_general_has_pp_dsp_ieee_1588_mac_enable;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_ptp_general_has_pp_dsp_ieee_1588_mac_enable_set;

    
    
    submodule_index = dnx_data_ptp_submodule_ptp_firmware;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_ptp_ptp_firmware_define_ptp_cosq_port;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_ptp_ptp_firmware_ptp_cosq_port_set;

    

    

    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE



/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_PORT

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_led.h>







static shr_error_e
q2a_b0_dnx_data_led_general_flexe_in_scan_chain_is_adjusted_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_led;
    int submodule_index = dnx_data_led_submodule_general;
    int feature_index = dnx_data_led_general_flexe_in_scan_chain_is_adjusted;
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
q2a_b0_data_led_attach(
    int unit)
{
    dnxc_data_module_t *module = NULL;
    dnxc_data_submodule_t *submodule = NULL;
    dnxc_data_define_t *define = NULL;
    dnxc_data_feature_t *feature = NULL;
    dnxc_data_table_t *table = NULL;
    int module_index = dnx_data_module_led;
    int submodule_index = -1, data_index = -1;
    SHR_FUNC_INIT_VARS(unit);

    COMPILER_REFERENCE(define);
    COMPILER_REFERENCE(feature);
    COMPILER_REFERENCE(table);
    COMPILER_REFERENCE(submodule);
    COMPILER_REFERENCE(data_index);
    COMPILER_REFERENCE(submodule_index);
    module = &_dnxc_data[unit].modules[module_index];
    
    submodule_index = dnx_data_led_submodule_general;
    submodule = &module->submodules[submodule_index];

    

    
    data_index = dnx_data_led_general_flexe_in_scan_chain_is_adjusted;
    feature = &submodule->features[data_index];
    feature->set = q2a_b0_dnx_data_led_general_flexe_in_scan_chain_is_adjusted_set;

    

    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


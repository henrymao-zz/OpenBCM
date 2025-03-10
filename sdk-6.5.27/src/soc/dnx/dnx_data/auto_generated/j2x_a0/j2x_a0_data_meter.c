
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_POLICER

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_meter.h>
#include <bcm/policer.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_crps.h>
#include <shared/utilex/utilex_integer_arithmetic.h>







static shr_error_e
j2x_a0_dnx_data_meter_general_is_used_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_meter;
    int submodule_index = dnx_data_meter_submodule_general;
    int feature_index = dnx_data_meter_general_is_used;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = dnx_data_nif.global.l1_only_mode_get(unit) == DNX_PORT_NIF_L1_ONLY_MODE_DISABLED;

    
    feature->data = dnx_data_nif.global.l1_only_mode_get(unit) == DNX_PORT_NIF_L1_ONLY_MODE_DISABLED;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_meter_general_power_down_supported_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_meter;
    int submodule_index = dnx_data_meter_submodule_general;
    int feature_index = dnx_data_meter_general_power_down_supported;
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
j2x_a0_dnx_data_meter_profile_ir_mant_nof_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_meter;
    int submodule_index = dnx_data_meter_submodule_profile;
    int define_index = dnx_data_meter_profile_define_ir_mant_nof_bits;
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
j2x_a0_dnx_data_meter_diag_rate_measurements_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_meter;
    int submodule_index = dnx_data_meter_submodule_diag;
    int feature_index = dnx_data_meter_diag_rate_measurements_support;
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
j2x_a0_dnx_data_meter_meter_db_refresh_range_minus_one_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_meter;
    int submodule_index = dnx_data_meter_submodule_meter_db;
    int feature_index = dnx_data_meter_meter_db_refresh_range_minus_one;
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
j2x_a0_dnx_data_meter_meter_db_tcsm_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_meter;
    int submodule_index = dnx_data_meter_submodule_meter_db;
    int feature_index = dnx_data_meter_meter_db_tcsm_support;
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
j2x_a0_dnx_data_meter_mem_mgmt_meter_pointer_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_meter;
    int submodule_index = dnx_data_meter_submodule_mem_mgmt;
    int define_index = dnx_data_meter_mem_mgmt_define_meter_pointer_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 20;

    
    define->data = 20;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_meter_mem_mgmt_invalid_bank_id_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_meter;
    int submodule_index = dnx_data_meter_submodule_mem_mgmt;
    int define_index = dnx_data_meter_mem_mgmt_define_invalid_bank_id;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 63;

    
    define->data = 63;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_meter_mem_mgmt_bank_id_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_meter;
    int submodule_index = dnx_data_meter_submodule_mem_mgmt;
    int define_index = dnx_data_meter_mem_mgmt_define_bank_id_size;
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
j2x_a0_dnx_data_meter_mem_mgmt_sections_offset_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_meter;
    int submodule_index = dnx_data_meter_submodule_mem_mgmt;
    int define_index = dnx_data_meter_mem_mgmt_define_sections_offset;
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
j2x_a0_dnx_data_meter_compensation_per_ingress_pp_port_delta_range_set(
    int unit)
{
    dnx_data_meter_compensation_per_ingress_pp_port_delta_range_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_meter;
    int submodule_index = dnx_data_meter_submodule_compensation;
    int table_index = dnx_data_meter_compensation_table_per_ingress_pp_port_delta_range;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "-256";
    table->values[1].default_val = "255";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_meter_compensation_per_ingress_pp_port_delta_range_t, (1 + 1  ), "data of dnx_data_meter_compensation_table_per_ingress_pp_port_delta_range");

    
    default_data = (dnx_data_meter_compensation_per_ingress_pp_port_delta_range_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->min = -256;
    default_data->max = 255;
    
    data = (dnx_data_meter_compensation_per_ingress_pp_port_delta_range_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}





static shr_error_e
j2x_a0_dnx_data_meter_expansion_expansion_based_on_tc_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_meter;
    int submodule_index = dnx_data_meter_submodule_expansion;
    int feature_index = dnx_data_meter_expansion_expansion_based_on_tc_support;
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
j2x_a0_dnx_data_meter_expansion_expansion_for_uuc_umc_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_meter;
    int submodule_index = dnx_data_meter_submodule_expansion;
    int feature_index = dnx_data_meter_expansion_expansion_for_uuc_umc_support;
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
j2x_a0_dnx_data_meter_expansion_max_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_meter;
    int submodule_index = dnx_data_meter_submodule_expansion;
    int define_index = dnx_data_meter_expansion_define_max_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 7;

    
    define->data = 7;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}




shr_error_e
j2x_a0_data_meter_attach(
    int unit)
{
    dnxc_data_module_t *module = NULL;
    dnxc_data_submodule_t *submodule = NULL;
    dnxc_data_define_t *define = NULL;
    dnxc_data_feature_t *feature = NULL;
    dnxc_data_table_t *table = NULL;
    int module_index = dnx_data_module_meter;
    int submodule_index = -1, data_index = -1;
    SHR_FUNC_INIT_VARS(unit);

    COMPILER_REFERENCE(define);
    COMPILER_REFERENCE(feature);
    COMPILER_REFERENCE(table);
    COMPILER_REFERENCE(submodule);
    COMPILER_REFERENCE(data_index);
    COMPILER_REFERENCE(submodule_index);
    module = &_dnxc_data[unit].modules[module_index];
    
    submodule_index = dnx_data_meter_submodule_general;
    submodule = &module->submodules[submodule_index];

    

    
    data_index = dnx_data_meter_general_is_used;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_meter_general_is_used_set;
    data_index = dnx_data_meter_general_power_down_supported;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_meter_general_power_down_supported_set;

    
    
    submodule_index = dnx_data_meter_submodule_profile;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_meter_profile_define_ir_mant_nof_bits;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_meter_profile_ir_mant_nof_bits_set;

    

    
    
    submodule_index = dnx_data_meter_submodule_diag;
    submodule = &module->submodules[submodule_index];

    

    
    data_index = dnx_data_meter_diag_rate_measurements_support;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_meter_diag_rate_measurements_support_set;

    
    
    submodule_index = dnx_data_meter_submodule_meter_db;
    submodule = &module->submodules[submodule_index];

    

    
    data_index = dnx_data_meter_meter_db_refresh_range_minus_one;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_meter_meter_db_refresh_range_minus_one_set;
    data_index = dnx_data_meter_meter_db_tcsm_support;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_meter_meter_db_tcsm_support_set;

    
    
    submodule_index = dnx_data_meter_submodule_mem_mgmt;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_meter_mem_mgmt_define_meter_pointer_size;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_meter_mem_mgmt_meter_pointer_size_set;
    data_index = dnx_data_meter_mem_mgmt_define_invalid_bank_id;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_meter_mem_mgmt_invalid_bank_id_set;
    data_index = dnx_data_meter_mem_mgmt_define_bank_id_size;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_meter_mem_mgmt_bank_id_size_set;
    data_index = dnx_data_meter_mem_mgmt_define_sections_offset;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_meter_mem_mgmt_sections_offset_set;

    

    
    
    submodule_index = dnx_data_meter_submodule_compensation;
    submodule = &module->submodules[submodule_index];

    

    

    
    data_index = dnx_data_meter_compensation_table_per_ingress_pp_port_delta_range;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_meter_compensation_per_ingress_pp_port_delta_range_set;
    
    submodule_index = dnx_data_meter_submodule_expansion;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_meter_expansion_define_max_size;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_meter_expansion_max_size_set;

    
    data_index = dnx_data_meter_expansion_expansion_based_on_tc_support;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_meter_expansion_expansion_based_on_tc_support_set;
    data_index = dnx_data_meter_expansion_expansion_for_uuc_umc_support;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_meter_expansion_expansion_for_uuc_umc_support_set;

    

    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


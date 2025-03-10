
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_TRUNK

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_trunk.h>
#include <shared/utilex/utilex_integer_arithmetic.h>







static shr_error_e
j2x_a0_dnx_data_trunk_egress_trunk_multiple_egress_trunk_sizes_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_trunk;
    int submodule_index = dnx_data_trunk_submodule_egress_trunk;
    int feature_index = dnx_data_trunk_egress_trunk_multiple_egress_trunk_sizes;
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
j2x_a0_dnx_data_trunk_egress_trunk_nof_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_trunk;
    int submodule_index = dnx_data_trunk_submodule_egress_trunk;
    int define_index = dnx_data_trunk_egress_trunk_define_nof;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = (dnx_data_trunk.egress_trunk.nof_lb_keys_per_profile_get(unit) == 128 ) ? 512 : 256;

    
    define->data = (dnx_data_trunk.egress_trunk.nof_lb_keys_per_profile_get(unit) == 128 ) ? 512 : 256;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_trunk_egress_trunk_nof_lb_keys_per_profile_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_trunk;
    int submodule_index = dnx_data_trunk_submodule_egress_trunk;
    int define_index = dnx_data_trunk_egress_trunk_define_nof_lb_keys_per_profile;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = UTILEX_MAX( dnx_data_trunk.parameters.pool_info_get(unit, 0)->max_nof_members_in_group, dnx_data_trunk.parameters.pool_info_get(unit, 1)->max_nof_members_in_group) > 64 ? 256 : 128;

    
    define->data = UTILEX_MAX( dnx_data_trunk.parameters.pool_info_get(unit, 0)->max_nof_members_in_group, dnx_data_trunk.parameters.pool_info_get(unit, 1)->max_nof_members_in_group) > 64 ? 256 : 128;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_TRUNK_EGRESS_NOF_LOAD_BALANCING_KEYS;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_direct_map;
    define->property.method_str = "direct_map";
    define->property.nof_mapping = 2;
    DNXC_DATA_ALLOC(define->property.mapping, dnxc_data_property_map_t, define->property.nof_mapping, "dnxc_data property mapping");

    define->property.mapping[0].name = "128";
    define->property.mapping[0].val = 128;
    define->property.mapping[1].name = "256";
    define->property.mapping[1].val = 256;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_trunk_egress_trunk_dbal_egress_trunk_index_multiplier_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_trunk;
    int submodule_index = dnx_data_trunk_submodule_egress_trunk;
    int define_index = dnx_data_trunk_egress_trunk_define_dbal_egress_trunk_index_multiplier;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = (dnx_data_trunk.egress_trunk.nof_lb_keys_per_profile_get(unit) == 128 ) ? 16 : 32;

    
    define->data = (dnx_data_trunk.egress_trunk.nof_lb_keys_per_profile_get(unit) == 128 ) ? 16 : 32;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_trunk_egress_trunk_dbal_entry_index_divider_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_trunk;
    int submodule_index = dnx_data_trunk_submodule_egress_trunk;
    int define_index = dnx_data_trunk_egress_trunk_define_dbal_entry_index_divider;
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
j2x_a0_dnx_data_trunk_egress_trunk_dbal_entry_index_msb_multiplier_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_trunk;
    int submodule_index = dnx_data_trunk_submodule_egress_trunk;
    int define_index = dnx_data_trunk_egress_trunk_define_dbal_entry_index_msb_multiplier;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8192;

    
    define->data = 8192;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_trunk_egress_trunk_size_mode_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_trunk;
    int submodule_index = dnx_data_trunk_submodule_egress_trunk;
    int define_index = dnx_data_trunk_egress_trunk_define_size_mode;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_trunk.egress_trunk.nof_get(unit) == 128 ? 0 : 1;

    
    define->data = dnx_data_trunk.egress_trunk.nof_get(unit) == 128 ? 0 : 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}






static shr_error_e
j2x_a0_dnx_data_trunk_flow_agg_member_resolution_v1_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_trunk;
    int submodule_index = dnx_data_trunk_submodule_flow_agg;
    int feature_index = dnx_data_trunk_flow_agg_member_resolution_v1;
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
j2x_a0_dnx_data_trunk_flow_agg_nof_flow_aggs_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_trunk;
    int submodule_index = dnx_data_trunk_submodule_flow_agg;
    int define_index = dnx_data_trunk_flow_agg_define_nof_flow_aggs;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 16383;

    
    define->data = 16383;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}




shr_error_e
j2x_a0_data_trunk_attach(
    int unit)
{
    dnxc_data_module_t *module = NULL;
    dnxc_data_submodule_t *submodule = NULL;
    dnxc_data_define_t *define = NULL;
    dnxc_data_feature_t *feature = NULL;
    dnxc_data_table_t *table = NULL;
    int module_index = dnx_data_module_trunk;
    int submodule_index = -1, data_index = -1;
    SHR_FUNC_INIT_VARS(unit);

    COMPILER_REFERENCE(define);
    COMPILER_REFERENCE(feature);
    COMPILER_REFERENCE(table);
    COMPILER_REFERENCE(submodule);
    COMPILER_REFERENCE(data_index);
    COMPILER_REFERENCE(submodule_index);
    module = &_dnxc_data[unit].modules[module_index];
    
    submodule_index = dnx_data_trunk_submodule_egress_trunk;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_trunk_egress_trunk_define_nof;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_trunk_egress_trunk_nof_set;
    data_index = dnx_data_trunk_egress_trunk_define_nof_lb_keys_per_profile;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_trunk_egress_trunk_nof_lb_keys_per_profile_set;
    data_index = dnx_data_trunk_egress_trunk_define_dbal_egress_trunk_index_multiplier;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_trunk_egress_trunk_dbal_egress_trunk_index_multiplier_set;
    data_index = dnx_data_trunk_egress_trunk_define_dbal_entry_index_divider;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_trunk_egress_trunk_dbal_entry_index_divider_set;
    data_index = dnx_data_trunk_egress_trunk_define_dbal_entry_index_msb_multiplier;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_trunk_egress_trunk_dbal_entry_index_msb_multiplier_set;
    data_index = dnx_data_trunk_egress_trunk_define_size_mode;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_trunk_egress_trunk_size_mode_set;

    
    data_index = dnx_data_trunk_egress_trunk_multiple_egress_trunk_sizes;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_trunk_egress_trunk_multiple_egress_trunk_sizes_set;

    
    
    submodule_index = dnx_data_trunk_submodule_flow_agg;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_trunk_flow_agg_define_nof_flow_aggs;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_trunk_flow_agg_nof_flow_aggs_set;

    
    data_index = dnx_data_trunk_flow_agg_member_resolution_v1;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_trunk_flow_agg_member_resolution_v1_set;

    

    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


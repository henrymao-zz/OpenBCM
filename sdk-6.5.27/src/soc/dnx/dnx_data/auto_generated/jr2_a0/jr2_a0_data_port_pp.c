
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_PORT_PP

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_port_pp.h>







static shr_error_e
jr2_a0_dnx_data_port_pp_general_split_horizon_per_port_outlif_profile_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_general;
    int feature_index = dnx_data_port_pp_general_split_horizon_per_port_outlif_profile_support;
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
jr2_a0_dnx_data_port_pp_general_prt_tcam_is_direct_access_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_general;
    int feature_index = dnx_data_port_pp_general_prt_tcam_is_direct_access;
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
jr2_a0_dnx_data_port_pp_general_recycle_app_sbfd_reflector_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_general;
    int feature_index = dnx_data_port_pp_general_recycle_app_sbfd_reflector;
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
jr2_a0_dnx_data_port_pp_general_rcy_info_prt_qualifier_eth_over_append64_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_general;
    int feature_index = dnx_data_port_pp_general_rcy_info_prt_qualifier_eth_over_append64_support;
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
jr2_a0_dnx_data_port_pp_general_prt_qualifier_injected_2_jr1_reserved_parsing_context_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_general;
    int feature_index = dnx_data_port_pp_general_prt_qualifier_injected_2_jr1_reserved_parsing_context_support;
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
jr2_a0_dnx_data_port_pp_general_nof_ingress_llvp_profiles_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_general;
    int define_index = dnx_data_port_pp_general_define_nof_ingress_llvp_profiles;
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
jr2_a0_dnx_data_port_pp_general_nof_egress_llvp_profiles_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_general;
    int define_index = dnx_data_port_pp_general_define_nof_egress_llvp_profiles;
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
jr2_a0_dnx_data_port_pp_general_default_ingress_native_ac_llvp_profile_id_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_general;
    int define_index = dnx_data_port_pp_general_define_default_ingress_native_ac_llvp_profile_id;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_port_pp_general_default_egress_native_ac_llvp_profile_id_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_general;
    int define_index = dnx_data_port_pp_general_define_default_egress_native_ac_llvp_profile_id;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_port_pp_general_nof_egress_sit_profile_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_general;
    int define_index = dnx_data_port_pp_general_define_nof_egress_sit_profile;
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
jr2_a0_dnx_data_port_pp_general_nof_egress_acceptable_frame_type_profile_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_general;
    int define_index = dnx_data_port_pp_general_define_nof_egress_acceptable_frame_type_profile;
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
jr2_a0_dnx_data_port_pp_general_sit_inner_eth_additional_tag_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_general;
    int define_index = dnx_data_port_pp_general_define_sit_inner_eth_additional_tag;
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
jr2_a0_dnx_data_port_pp_general_nof_virtual_port_tcam_entries_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_general;
    int define_index = dnx_data_port_pp_general_define_nof_virtual_port_tcam_entries;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 512;

    
    define->data = 512;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}






static shr_error_e
jr2_a0_dnx_data_port_pp_filters_acceptable_frame_type_filter_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_filters;
    int feature_index = dnx_data_port_pp_filters_acceptable_frame_type_filter_support;
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
jr2_a0_dnx_data_port_pp_filters_dss_stacking_filter_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_filters;
    int feature_index = dnx_data_port_pp_filters_dss_stacking_filter_support;
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
jr2_a0_dnx_data_port_pp_filters_lag_egress_multicast_filter_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_filters;
    int feature_index = dnx_data_port_pp_filters_lag_egress_multicast_filter_support;
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
jr2_a0_dnx_data_port_pp_filters_exclude_source_filter_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_filters;
    int feature_index = dnx_data_port_pp_filters_exclude_source_filter_support;
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
jr2_a0_dnx_data_port_pp_filters_ipv6_hop_by_hop_filter_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_filters;
    int feature_index = dnx_data_port_pp_filters_ipv6_hop_by_hop_filter_support;
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
jr2_a0_dnx_data_port_pp_filters_glem_filter_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_filters;
    int feature_index = dnx_data_port_pp_filters_glem_filter_support;
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
jr2_a0_dnx_data_port_pp_filters_ppmc_not_found_filter_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_filters;
    int feature_index = dnx_data_port_pp_filters_ppmc_not_found_filter_support;
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
jr2_a0_dnx_data_port_pp_filters_rqp_discard_and_invalid_otm_filters_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_filters;
    int feature_index = dnx_data_port_pp_filters_rqp_discard_and_invalid_otm_filters_support;
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
jr2_a0_dnx_data_port_pp_filters_egress_filters_enable_per_recycle_port_supported_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = dnx_data_port_pp_submodule_filters;
    int feature_index = dnx_data_port_pp_filters_egress_filters_enable_per_recycle_port_supported;
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
jr2_a0_data_port_pp_attach(
    int unit)
{
    dnxc_data_module_t *module = NULL;
    dnxc_data_submodule_t *submodule = NULL;
    dnxc_data_define_t *define = NULL;
    dnxc_data_feature_t *feature = NULL;
    dnxc_data_table_t *table = NULL;
    int module_index = dnx_data_module_port_pp;
    int submodule_index = -1, data_index = -1;
    SHR_FUNC_INIT_VARS(unit);

    COMPILER_REFERENCE(define);
    COMPILER_REFERENCE(feature);
    COMPILER_REFERENCE(table);
    COMPILER_REFERENCE(submodule);
    COMPILER_REFERENCE(data_index);
    COMPILER_REFERENCE(submodule_index);
    module = &_dnxc_data[unit].modules[module_index];
    
    submodule_index = dnx_data_port_pp_submodule_general;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_port_pp_general_define_nof_ingress_llvp_profiles;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_port_pp_general_nof_ingress_llvp_profiles_set;
    data_index = dnx_data_port_pp_general_define_nof_egress_llvp_profiles;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_port_pp_general_nof_egress_llvp_profiles_set;
    data_index = dnx_data_port_pp_general_define_default_ingress_native_ac_llvp_profile_id;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_port_pp_general_default_ingress_native_ac_llvp_profile_id_set;
    data_index = dnx_data_port_pp_general_define_default_egress_native_ac_llvp_profile_id;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_port_pp_general_default_egress_native_ac_llvp_profile_id_set;
    data_index = dnx_data_port_pp_general_define_nof_egress_sit_profile;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_port_pp_general_nof_egress_sit_profile_set;
    data_index = dnx_data_port_pp_general_define_nof_egress_acceptable_frame_type_profile;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_port_pp_general_nof_egress_acceptable_frame_type_profile_set;
    data_index = dnx_data_port_pp_general_define_sit_inner_eth_additional_tag;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_port_pp_general_sit_inner_eth_additional_tag_set;
    data_index = dnx_data_port_pp_general_define_nof_virtual_port_tcam_entries;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_port_pp_general_nof_virtual_port_tcam_entries_set;

    
    data_index = dnx_data_port_pp_general_split_horizon_per_port_outlif_profile_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_port_pp_general_split_horizon_per_port_outlif_profile_support_set;
    data_index = dnx_data_port_pp_general_prt_tcam_is_direct_access;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_port_pp_general_prt_tcam_is_direct_access_set;
    data_index = dnx_data_port_pp_general_recycle_app_sbfd_reflector;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_port_pp_general_recycle_app_sbfd_reflector_set;
    data_index = dnx_data_port_pp_general_rcy_info_prt_qualifier_eth_over_append64_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_port_pp_general_rcy_info_prt_qualifier_eth_over_append64_support_set;
    data_index = dnx_data_port_pp_general_prt_qualifier_injected_2_jr1_reserved_parsing_context_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_port_pp_general_prt_qualifier_injected_2_jr1_reserved_parsing_context_support_set;

    
    
    submodule_index = dnx_data_port_pp_submodule_filters;
    submodule = &module->submodules[submodule_index];

    

    
    data_index = dnx_data_port_pp_filters_acceptable_frame_type_filter_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_port_pp_filters_acceptable_frame_type_filter_support_set;
    data_index = dnx_data_port_pp_filters_dss_stacking_filter_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_port_pp_filters_dss_stacking_filter_support_set;
    data_index = dnx_data_port_pp_filters_lag_egress_multicast_filter_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_port_pp_filters_lag_egress_multicast_filter_support_set;
    data_index = dnx_data_port_pp_filters_exclude_source_filter_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_port_pp_filters_exclude_source_filter_support_set;
    data_index = dnx_data_port_pp_filters_ipv6_hop_by_hop_filter_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_port_pp_filters_ipv6_hop_by_hop_filter_support_set;
    data_index = dnx_data_port_pp_filters_glem_filter_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_port_pp_filters_glem_filter_support_set;
    data_index = dnx_data_port_pp_filters_ppmc_not_found_filter_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_port_pp_filters_ppmc_not_found_filter_support_set;
    data_index = dnx_data_port_pp_filters_rqp_discard_and_invalid_otm_filters_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_port_pp_filters_rqp_discard_and_invalid_otm_filters_support_set;
    data_index = dnx_data_port_pp_filters_egress_filters_enable_per_recycle_port_supported;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_port_pp_filters_egress_filters_enable_per_recycle_port_supported_set;

    

    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


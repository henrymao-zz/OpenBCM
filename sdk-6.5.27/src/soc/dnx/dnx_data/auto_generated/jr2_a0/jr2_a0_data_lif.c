
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_LIF

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_lif.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_device.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_mdb.h>







static shr_error_e
jr2_a0_dnx_data_lif_global_lif_prevent_tunnel_update_rif_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int feature_index = dnx_data_lif_global_lif_prevent_tunnel_update_rif;
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
jr2_a0_dnx_data_lif_global_lif_glem_bypass_per_phase_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int feature_index = dnx_data_lif_global_lif_glem_bypass_per_phase;
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
jr2_a0_dnx_data_lif_global_lif_outlif_profile_in_glem_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int feature_index = dnx_data_lif_global_lif_outlif_profile_in_glem;
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
jr2_a0_dnx_data_lif_global_lif_use_mdb_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int define_index = dnx_data_lif_global_lif_define_use_mdb_size;
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
jr2_a0_dnx_data_lif_global_lif_glem_rif_optimization_enabled_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int define_index = dnx_data_lif_global_lif_define_glem_rif_optimization_enabled;
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
jr2_a0_dnx_data_lif_global_lif_null_lif_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int define_index = dnx_data_lif_global_lif_define_null_lif;
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
jr2_a0_dnx_data_lif_global_lif_three_intf_glem_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int define_index = dnx_data_lif_global_lif_define_three_intf_glem;
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
jr2_a0_dnx_data_lif_global_lif_nof_global_in_lifs_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int define_index = dnx_data_lif_global_lif_define_nof_global_in_lifs;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0x300000;

    
    define->data = 0x300000;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_SYSTEM_HEADERS_MODE;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_direct_map;
    define->property.method_str = "direct_map";
    define->property.nof_mapping = 2;
    DNXC_DATA_ALLOC(define->property.mapping, dnxc_data_property_map_t, define->property.nof_mapping, "dnxc_data property mapping");

    define->property.mapping[0].name = "0";
    define->property.mapping[0].val = 0x40000;
    define->property.mapping[1].name = "1";
    define->property.mapping[1].val = 0x300000;
    define->property.mapping[1].is_default = 1 ;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_global_lif_nof_global_out_lifs_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int define_index = dnx_data_lif_global_lif_define_nof_global_out_lifs;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.global_lif.nof_global_in_lifs_get(unit);

    
    define->data = dnx_data_lif.global_lif.nof_global_in_lifs_get(unit);

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_global_lif_egress_in_lif_null_value_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int define_index = dnx_data_lif_global_lif_define_egress_in_lif_null_value;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0x0;

    
    define->data = 0x0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_SYSTEM_HEADERS_MODE;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_direct_map;
    define->property.method_str = "direct_map";
    define->property.nof_mapping = 2;
    DNXC_DATA_ALLOC(define->property.mapping, dnxc_data_property_map_t, define->property.nof_mapping, "dnxc_data property mapping");

    define->property.mapping[0].name = "0";
    define->property.mapping[0].val = 0x0;
    define->property.mapping[0].is_default = 1 ;
    define->property.mapping[1].name = "1";
    define->property.mapping[1].val = 0x0;
    define->property.mapping[1].is_default = 1 ;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_global_lif_egress_out_lif_null_value_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int define_index = dnx_data_lif_global_lif_define_egress_out_lif_null_value;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0x0;

    
    define->data = 0x0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_SYSTEM_HEADERS_MODE;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_direct_map;
    define->property.method_str = "direct_map";
    define->property.nof_mapping = 2;
    DNXC_DATA_ALLOC(define->property.mapping, dnxc_data_property_map_t, define->property.nof_mapping, "dnxc_data property mapping");

    define->property.mapping[0].name = "0";
    define->property.mapping[0].val = 0x3FFFF;
    define->property.mapping[1].name = "1";
    define->property.mapping[1].val = 0x0;
    define->property.mapping[1].is_default = 1 ;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_global_lif_nof_global_l2_gport_lifs_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int define_index = dnx_data_lif_global_lif_define_nof_global_l2_gport_lifs;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0x100000;

    
    define->data = 0x100000;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_SYSTEM_HEADERS_MODE;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_direct_map;
    define->property.method_str = "direct_map";
    define->property.nof_mapping = 2;
    DNXC_DATA_ALLOC(define->property.mapping, dnxc_data_property_map_t, define->property.nof_mapping, "dnxc_data property mapping");

    define->property.mapping[0].name = "0";
    define->property.mapping[0].val = 0x40000;
    define->property.mapping[1].name = "1";
    define->property.mapping[1].val = 0x100000;
    define->property.mapping[1].is_default = 1 ;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_global_lif_global_lif_bta_max_val_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int define_index = dnx_data_lif_global_lif_define_global_lif_bta_max_val;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 150 : 0;

    
    define->data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 150 : 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_global_lif_global_lif_tag_nof_bta_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int define_index = dnx_data_lif_global_lif_define_global_lif_tag_nof_bta_bits;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 8 : 0;

    
    define->data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 8 : 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_global_lif_global_lif_intf_max_val_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int define_index = dnx_data_lif_global_lif_define_global_lif_intf_max_val;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.out_lif.global_lif_allocation_outlif_intf_enable_get(unit) == 1 ? 3 : 0;

    
    define->data = dnx_data_lif.out_lif.global_lif_allocation_outlif_intf_enable_get(unit) == 1 ? 3 : 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_global_lif_global_lif_tag_nof_intf_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int define_index = dnx_data_lif_global_lif_define_global_lif_tag_nof_intf_bits;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.out_lif.global_lif_allocation_outlif_intf_enable_get(unit) == 1 ? 2 : 0;

    
    define->data = dnx_data_lif.out_lif.global_lif_allocation_outlif_intf_enable_get(unit) == 1 ? 2 : 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_global_lif_global_lif_group_max_val_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int define_index = dnx_data_lif_global_lif_define_global_lif_group_max_val;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.out_lif.global_lif_allocation_outlif_group_enable_get(unit) == 1 ? 127 : 0;

    
    define->data = dnx_data_lif.out_lif.global_lif_allocation_outlif_group_enable_get(unit) == 1 ? 127 : 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_global_lif_global_lif_tag_nof_group_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int define_index = dnx_data_lif_global_lif_define_global_lif_tag_nof_group_bits;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.out_lif.global_lif_allocation_outlif_group_enable_get(unit) == 1 ? 7 : 0;

    
    define->data = dnx_data_lif.out_lif.global_lif_allocation_outlif_group_enable_get(unit) == 1 ? 7 : 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_global_lif_global_lif_grain_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_global_lif;
    int define_index = dnx_data_lif_global_lif_define_global_lif_grain_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.out_lif.global_lif_allocation_outlif_group_enable_get(unit) == 1 ? 16384 : 8192;

    
    define->data = dnx_data_lif.out_lif.global_lif_allocation_outlif_group_enable_get(unit) == 1 ? 16384 : 8192;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}







static shr_error_e
jr2_a0_dnx_data_lif_virtual_lif_flow_ingress_ids_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_virtual_lif;
    int define_index = dnx_data_lif_virtual_lif_define_flow_ingress_ids;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.global_lif.nof_global_in_lifs_get(unit)>>2;

    
    define->data = dnx_data_lif.global_lif.nof_global_in_lifs_get(unit)>>2;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_virtual_lif_flow_egress_ids_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_virtual_lif;
    int define_index = dnx_data_lif_virtual_lif_define_flow_egress_ids;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.virtual_lif.flow_ingress_ids_get(unit);

    
    define->data = dnx_data_lif.virtual_lif.flow_ingress_ids_get(unit);

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}






static shr_error_e
jr2_a0_dnx_data_lif_in_lif_mapped_in_lif_profile_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int feature_index = dnx_data_lif_in_lif_mapped_in_lif_profile;
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
jr2_a0_dnx_data_lif_in_lif_in_lif_profile_iop_mode_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int feature_index = dnx_data_lif_in_lif_in_lif_profile_iop_mode;
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
jr2_a0_dnx_data_lif_in_lif_phy_db_dpc_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int feature_index = dnx_data_lif_in_lif_phy_db_dpc;
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
jr2_a0_dnx_data_lif_in_lif_cs_in_lif_profile_based_on_stages_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int feature_index = dnx_data_lif_in_lif_cs_in_lif_profile_based_on_stages;
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
jr2_a0_dnx_data_lif_in_lif_p2p_or_mp_based_on_cs_in_lif_profile_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int feature_index = dnx_data_lif_in_lif_p2p_or_mp_based_on_cs_in_lif_profile;
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
jr2_a0_dnx_data_lif_in_lif_use_mapped_in_lif_profile_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int feature_index = dnx_data_lif_in_lif_use_mapped_in_lif_profile;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = dnx_data_headers.system_headers.system_headers_mode_get(unit) == dnx_data_headers.system_headers.system_headers_mode_jericho2_get(unit) ? dnx_data_lif.in_lif.feature_get(unit, dnx_data_lif_in_lif_mapped_in_lif_profile) : 0;

    
    feature->data = dnx_data_headers.system_headers.system_headers_mode_get(unit) == dnx_data_headers.system_headers.system_headers_mode_jericho2_get(unit) ? dnx_data_lif.in_lif.feature_get(unit, dnx_data_lif_in_lif_mapped_in_lif_profile) : 0;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_use_in_lif_profile_range_allocation_per_pmf_profiles_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int feature_index = dnx_data_lif_in_lif_use_in_lif_profile_range_allocation_per_pmf_profiles;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = dnx_data_headers.system_headers.system_headers_mode_get(unit) == dnx_data_headers.system_headers.system_headers_mode_jericho2_get(unit) ? 1 : 0;

    
    feature->data = dnx_data_headers.system_headers.system_headers_mode_get(unit) == dnx_data_headers.system_headers.system_headers_mode_jericho2_get(unit) ? 1 : 0;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_use_eth_rif_profile_range_allocation_per_pmf_profiles_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int feature_index = dnx_data_lif_in_lif_use_eth_rif_profile_range_allocation_per_pmf_profiles;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = dnx_data_headers.system_headers.system_headers_mode_get(unit) == dnx_data_headers.system_headers.system_headers_mode_jericho2_get(unit) ? 1 : 0;

    
    feature->data = dnx_data_headers.system_headers.system_headers_mode_get(unit) == dnx_data_headers.system_headers.system_headers_mode_jericho2_get(unit) ? 1 : 0;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_use_mapped_in_lif_profile_field_mapping_table_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int feature_index = dnx_data_lif_in_lif_use_mapped_in_lif_profile_field_mapping_table;
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
jr2_a0_dnx_data_lif_in_lif_in_lif_profile_mc_bridge_fallback_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int feature_index = dnx_data_lif_in_lif_in_lif_profile_mc_bridge_fallback_support;
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
jr2_a0_dnx_data_lif_in_lif_separate_ipv4_ipv6_urpf_mode_config_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int feature_index = dnx_data_lif_in_lif_separate_ipv4_ipv6_urpf_mode_config;
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
jr2_a0_dnx_data_lif_in_lif_ingress_interface_vip_supported_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int feature_index = dnx_data_lif_in_lif_ingress_interface_vip_supported;
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
jr2_a0_dnx_data_lif_in_lif_vxlan_vni2lif_supported_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int feature_index = dnx_data_lif_in_lif_vxlan_vni2lif_supported;
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
jr2_a0_dnx_data_lif_in_lif_inlif_index_bit_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_inlif_index_bit_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 60;

    
    define->data = 60;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_inlif_minimum_index_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_inlif_minimum_index_size;
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
jr2_a0_dnx_data_lif_in_lif_inlif_resource_tag_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_inlif_resource_tag_size;
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
jr2_a0_dnx_data_lif_in_lif_nof_in_lif_profiles_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_nof_in_lif_profiles;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 256;

    
    define->data = 256;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_nof_used_in_lif_profile_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_nof_used_in_lif_profile_bits;
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
jr2_a0_dnx_data_lif_in_lif_nof_used_eth_rif_profile_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_nof_used_eth_rif_profile_bits;
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
jr2_a0_dnx_data_lif_in_lif_nof_in_lif_incoming_orientation_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_nof_in_lif_incoming_orientation;
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
jr2_a0_dnx_data_lif_in_lif_nof_eth_rif_profiles_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_nof_eth_rif_profiles;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 128;

    
    define->data = 128;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_nof_da_not_found_destination_profiles_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_nof_da_not_found_destination_profiles;
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
jr2_a0_dnx_data_lif_in_lif_default_da_not_found_destination_profile_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_default_da_not_found_destination_profile;
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
jr2_a0_dnx_data_lif_in_lif_drop_in_lif_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_drop_in_lif;
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
jr2_a0_dnx_data_lif_in_lif_mc_bridge_fallback_per_lif_profile_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_mc_bridge_fallback_per_lif_profile;
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
jr2_a0_dnx_data_lif_in_lif_max_number_of_orientation_bits_iop_mode_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_max_number_of_orientation_bits_iop_mode;
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
jr2_a0_dnx_data_lif_in_lif_max_number_of_egress_lif_profile_bits_iop_mode_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_max_number_of_egress_lif_profile_bits_iop_mode;
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
jr2_a0_dnx_data_lif_in_lif_algo_flow_inlif_bank_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_algo_flow_inlif_bank_size;
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
jr2_a0_dnx_data_lif_in_lif_nof_routing_enable_profiles_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_nof_routing_enable_profiles;
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
jr2_a0_dnx_data_lif_in_lif_nof_shift_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_nof_shift_bits;
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
jr2_a0_dnx_data_lif_in_lif_generic_data_1_start_position_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_generic_data_1_start_position;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 16;

    
    define->data = 16;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_in_lif_profile_pmf_reserved_start_bit_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_in_lif_profile_pmf_reserved_start_bit;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.in_lif.nof_used_in_lif_profile_bits_get(unit)-dnx_data_field.profile_bits.nof_ing_in_lif_get(unit);

    
    define->data = dnx_data_lif.in_lif.nof_used_in_lif_profile_bits_get(unit)-dnx_data_field.profile_bits.nof_ing_in_lif_get(unit);

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_eth_rif_profile_pmf_reserved_start_bit_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_eth_rif_profile_pmf_reserved_start_bit;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.in_lif.nof_used_eth_rif_profile_bits_get(unit)-dnx_data_field.profile_bits.nof_ing_eth_rif_get(unit);

    
    define->data = dnx_data_lif.in_lif.nof_used_eth_rif_profile_bits_get(unit)-dnx_data_field.profile_bits.nof_ing_eth_rif_get(unit);

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_in_lif_profile_egress_reserved_start_bit_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_in_lif_profile_egress_reserved_start_bit;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.in_lif.feature_get(unit, dnx_data_lif_in_lif_use_mapped_in_lif_profile) == 1 ? 0 : dnx_data_lif.in_lif.in_lif_profile_pmf_reserved_start_bit_get(unit)-dnx_data_lif.in_lif.nof_in_lif_egress_reserved_bits_get(unit);

    
    define->data = dnx_data_lif.in_lif.feature_get(unit, dnx_data_lif_in_lif_use_mapped_in_lif_profile) == 1 ? 0 : dnx_data_lif.in_lif.in_lif_profile_pmf_reserved_start_bit_get(unit)-dnx_data_lif.in_lif.nof_in_lif_egress_reserved_bits_get(unit);

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_in_lif_profile_allocate_indexed_mode_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_in_lif_profile_allocate_indexed_mode;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = "in_lif_profile_allocate";
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_suffix_range;
    define->property.method_str = "suffix_range";
    define->property.suffix = "indexed_mode";
    define->property.range_min = 0;
    define->property.range_max = 2;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_nof_in_lif_profile_allocate_orientation_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_nof_in_lif_profile_allocate_orientation_bits;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = utilex_log2_round_up(dnx_data_lif.in_lif.in_lif_profile_allocate_orientation_get(unit));

    
    define->data = utilex_log2_round_up(dnx_data_lif.in_lif.in_lif_profile_allocate_orientation_get(unit));

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_nof_in_lif_profile_allocate_policer_inner_dp_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_nof_in_lif_profile_allocate_policer_inner_dp_bits;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = utilex_log2_round_up(dnx_data_lif.in_lif.in_lif_profile_allocate_policer_inner_dp_get(unit));

    
    define->data = utilex_log2_round_up(dnx_data_lif.in_lif.in_lif_profile_allocate_policer_inner_dp_get(unit));

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_nof_in_lif_profile_allocate_policer_outer_dp_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_nof_in_lif_profile_allocate_policer_outer_dp_bits;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = utilex_log2_round_up(dnx_data_lif.in_lif.in_lif_profile_allocate_policer_outer_dp_get(unit));

    
    define->data = utilex_log2_round_up(dnx_data_lif.in_lif.in_lif_profile_allocate_policer_outer_dp_get(unit));

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_nof_in_lif_profile_allocate_same_interface_mode_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_nof_in_lif_profile_allocate_same_interface_mode_bits;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = utilex_log2_round_up(dnx_data_lif.in_lif.in_lif_profile_allocate_same_interface_mode_get(unit));

    
    define->data = utilex_log2_round_up(dnx_data_lif.in_lif.in_lif_profile_allocate_same_interface_mode_get(unit));

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_nof_in_lif_egress_reserved_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_nof_in_lif_egress_reserved_bits;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.in_lif.feature_get(unit, dnx_data_lif_in_lif_use_mapped_in_lif_profile) == 1 ? 0 : dnx_data_lif.in_lif.nof_in_lif_profile_allocate_orientation_bits_get(unit)+dnx_data_lif.in_lif.nof_in_lif_profile_allocate_policer_outer_dp_bits_get(unit)+dnx_data_lif.in_lif.nof_in_lif_profile_allocate_policer_inner_dp_bits_get(unit)+dnx_data_lif.in_lif.nof_in_lif_profile_allocate_same_interface_mode_bits_get(unit);

    
    define->data = dnx_data_lif.in_lif.feature_get(unit, dnx_data_lif_in_lif_use_mapped_in_lif_profile) == 1 ? 0 : dnx_data_lif.in_lif.nof_in_lif_profile_allocate_orientation_bits_get(unit)+dnx_data_lif.in_lif.nof_in_lif_profile_allocate_policer_outer_dp_bits_get(unit)+dnx_data_lif.in_lif.nof_in_lif_profile_allocate_policer_inner_dp_bits_get(unit)+dnx_data_lif.in_lif.nof_in_lif_profile_allocate_same_interface_mode_bits_get(unit);

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_eth_rif_profile_egress_reserved_nof_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_eth_rif_profile_egress_reserved_nof_bits;
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
jr2_a0_dnx_data_lif_in_lif_eth_rif_profile_egress_reserved_start_bit_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_eth_rif_profile_egress_reserved_start_bit;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.in_lif.eth_rif_profile_pmf_reserved_start_bit_get(unit)-dnx_data_lif.in_lif.eth_rif_profile_egress_reserved_nof_bits_get(unit);

    
    define->data = dnx_data_lif.in_lif.eth_rif_profile_pmf_reserved_start_bit_get(unit)-dnx_data_lif.in_lif.eth_rif_profile_egress_reserved_nof_bits_get(unit);

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_in_lif_profile_native_indexed_mode_start_bit_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_in_lif_profile_native_indexed_mode_start_bit;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.in_lif.in_lif_profile_pmf_reserved_start_bit_get(unit)-dnx_data_lif.in_lif.nof_in_lif_egress_reserved_bits_get(unit)-dnx_data_lif.in_lif.nof_in_lif_profile_allocate_indexed_mode_bits_get(unit);

    
    define->data = dnx_data_lif.in_lif.in_lif_profile_pmf_reserved_start_bit_get(unit)-dnx_data_lif.in_lif.nof_in_lif_egress_reserved_bits_get(unit)-dnx_data_lif.in_lif.nof_in_lif_profile_allocate_indexed_mode_bits_get(unit);

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_nof_in_lif_profile_allocate_indexed_mode_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_nof_in_lif_profile_allocate_indexed_mode_bits;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = utilex_log2_round_up(dnx_data_lif.in_lif.in_lif_profile_allocate_indexed_mode_get(unit));

    
    define->data = utilex_log2_round_up(dnx_data_lif.in_lif.in_lif_profile_allocate_indexed_mode_get(unit));

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_in_lif_profile_allocate_orientation_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_in_lif_profile_allocate_orientation;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 4;

    
    define->data = 4;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = "in_lif_profile_egress_allocate";
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_suffix_range;
    define->property.method_str = "suffix_range";
    define->property.suffix = "orientation";
    define->property.range_min = 0;
    define->property.range_max = 8;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_in_lif_profile_allocate_policer_inner_dp_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_in_lif_profile_allocate_policer_inner_dp;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = "in_lif_profile_egress_allocate";
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_suffix_range;
    define->property.method_str = "suffix_range";
    define->property.suffix = "policer_inner_dp";
    define->property.range_min = 0;
    define->property.range_max = 4;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_in_lif_profile_allocate_policer_outer_dp_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_in_lif_profile_allocate_policer_outer_dp;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = "in_lif_profile_egress_allocate";
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_suffix_range;
    define->property.method_str = "suffix_range";
    define->property.suffix = "policer_outer_dp";
    define->property.range_min = 0;
    define->property.range_max = 4;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_in_lif_in_lif_profile_allocate_same_interface_mode_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_in_lif;
    int define_index = dnx_data_lif_in_lif_define_in_lif_profile_allocate_same_interface_mode;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = "in_lif_profile_egress_allocate";
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_suffix_range;
    define->property.method_str = "suffix_range";
    define->property.suffix = "same_interface_mode";
    define->property.range_min = 0;
    define->property.range_max = 3;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}






static shr_error_e
jr2_a0_dnx_data_lif_out_lif_per_phase_algo_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int feature_index = dnx_data_lif_out_lif_per_phase_algo;
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
jr2_a0_dnx_data_lif_out_lif_data_entries_supported_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int feature_index = dnx_data_lif_out_lif_data_entries_supported;
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
jr2_a0_dnx_data_lif_out_lif_nof_out_lif_profiles_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_nof_out_lif_profiles;
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
jr2_a0_dnx_data_lif_out_lif_nof_erpp_out_lif_profiles_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_nof_erpp_out_lif_profiles;
    SHR_FUNC_INIT_VARS(unit);

    
    if (!soc_is(unit, DNX2_DEVICE))
    {
        dnxc_data_mgmt_inaccessible_data_set(unit, "nof_erpp_out_lif_profiles", "DNX2");
    }

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8;

    
    define->data = 8;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}




static shr_error_e
jr2_a0_dnx_data_lif_out_lif_nof_out_lif_outgoing_orientation_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_nof_out_lif_outgoing_orientation;
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
jr2_a0_dnx_data_lif_out_lif_outrif_profile_width_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_outrif_profile_width;
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
jr2_a0_dnx_data_lif_out_lif_glem_result_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_glem_result;
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
jr2_a0_dnx_data_lif_out_lif_physical_bank_pointer_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_physical_bank_pointer_size;
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
jr2_a0_dnx_data_lif_out_lif_outlif_eedb_banks_pointer_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_outlif_eedb_banks_pointer_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 19;

    
    define->data = 19;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_global_outlif_bta_sop_resolution_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_global_outlif_bta_sop_resolution;
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
jr2_a0_dnx_data_lif_out_lif_pmf_outlif_profile_width_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_pmf_outlif_profile_width;
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
jr2_a0_dnx_data_lif_out_lif_pmf_outrif_profile_width_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_pmf_outrif_profile_width;
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
jr2_a0_dnx_data_lif_out_lif_etpp_out_lif_profile_default_mpls_profile_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_etpp_out_lif_profile_default_mpls_profile;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 28;

    
    define->data = 28;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_etpp_out_lif_profile_default_port_profile_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_etpp_out_lif_profile_default_port_profile;
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
jr2_a0_dnx_data_lif_out_lif_etpp_out_lif_profile_default_orientation_profile_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_etpp_out_lif_profile_default_orientation_profile;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 56;

    
    define->data = 56;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_outlif_pointer_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_outlif_pointer_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 19;

    
    define->data = 19;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_OUTLIF_NOF_BITS;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_direct_map;
    define->property.method_str = "direct_map";
    define->property.nof_mapping = 2;
    DNXC_DATA_ALLOC(define->property.mapping, dnxc_data_property_map_t, define->property.nof_mapping, "dnxc_data property mapping");

    define->property.mapping[0].name = "19";
    define->property.mapping[0].val = 19;
    define->property.mapping[0].is_default = 1 ;
    define->property.mapping[1].name = "20";
    define->property.mapping[1].val = 20;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_allocation_bank_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_allocation_bank_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 8192;

    
    define->data = 8192;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_OUTLIF_NOF_BITS;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_direct_map;
    define->property.method_str = "direct_map";
    define->property.nof_mapping = 2;
    DNXC_DATA_ALLOC(define->property.mapping, dnxc_data_property_map_t, define->property.nof_mapping, "dnxc_data property mapping");

    define->property.mapping[0].name = "19";
    define->property.mapping[0].val = 8192;
    define->property.mapping[0].is_default = 1 ;
    define->property.mapping[1].name = "20";
    define->property.mapping[1].val = 16384;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_local_outlif_width_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_local_outlif_width;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 19;

    
    define->data = 19;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_OUTLIF_NOF_BITS;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_direct_map;
    define->property.method_str = "direct_map";
    define->property.nof_mapping = 2;
    DNXC_DATA_ALLOC(define->property.mapping, dnxc_data_property_map_t, define->property.nof_mapping, "dnxc_data property mapping");

    define->property.mapping[0].name = "19";
    define->property.mapping[0].val = 19;
    define->property.mapping[0].is_default = 1 ;
    define->property.mapping[1].name = "20";
    define->property.mapping[1].val = 20;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_outlif_profile_width_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_outlif_profile_width;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1;

    
    define->data = 1;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_OUTLIF_NOF_BITS;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_direct_map;
    define->property.method_str = "direct_map";
    define->property.nof_mapping = 2;
    DNXC_DATA_ALLOC(define->property.mapping, dnxc_data_property_map_t, define->property.nof_mapping, "dnxc_data property mapping");

    define->property.mapping[0].name = "19";
    define->property.mapping[0].val = 1;
    define->property.mapping[0].is_default = 1 ;
    define->property.mapping[1].name = "20";
    define->property.mapping[1].val = 0;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_nof_local_out_lifs_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_nof_local_out_lifs;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0x80000;

    
    define->data = 0x80000;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_OUTLIF_NOF_BITS;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_direct_map;
    define->property.method_str = "direct_map";
    define->property.nof_mapping = 2;
    DNXC_DATA_ALLOC(define->property.mapping, dnxc_data_property_map_t, define->property.nof_mapping, "dnxc_data property mapping");

    define->property.mapping[0].name = "19";
    define->property.mapping[0].val = 0x80000;
    define->property.mapping[0].is_default = 1 ;
    define->property.mapping[1].name = "20";
    define->property.mapping[1].val = 0x100000;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_physical_bank_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_physical_bank_size;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0x1000;

    
    define->data = 0x1000;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_OUTLIF_NOF_BITS;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_direct_map;
    define->property.method_str = "direct_map";
    define->property.nof_mapping = 2;
    DNXC_DATA_ALLOC(define->property.mapping, dnxc_data_property_map_t, define->property.nof_mapping, "dnxc_data property mapping");

    define->property.mapping[0].name = "19";
    define->property.mapping[0].val = 0x1000;
    define->property.mapping[0].is_default = 1 ;
    define->property.mapping[1].name = "20";
    define->property.mapping[1].val = 0x2000;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_global_ipv6_outlif_bta_sop_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_global_ipv6_outlif_bta_sop;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 40 : 0;

    
    define->data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 40 : 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_global_vxlan_outlif_bta_sop_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_global_vxlan_outlif_bta_sop;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 36 : 0;

    
    define->data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 36 : 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_global_mpls_outlif_bta_sop_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_global_mpls_outlif_bta_sop;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 4 : 0;

    
    define->data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 4 : 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_global_srv6_outlif_bta_sop_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_global_srv6_outlif_bta_sop;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 16 : 0;

    
    define->data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 16 : 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_global_sflow_extended_gateway_two_outlif_bta_sop_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_global_sflow_extended_gateway_two_outlif_bta_sop;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 112 : 0;

    
    define->data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 112 : 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_global_sflow_extended_gateway_one_outlif_bta_sop_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_global_sflow_extended_gateway_one_outlif_bta_sop;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 35 : 0;

    
    define->data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 35 : 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_global_sflow_header_sampling_outlif_bta_sop_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_global_sflow_header_sampling_outlif_bta_sop;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 80 : 0;

    
    define->data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 80 : 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_global_sflow_dp_outlif_bta_sop_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_global_sflow_dp_outlif_bta_sop;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 126 : 0;

    
    define->data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 126 : 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_global_gtp_concat_ip_outlif_bta_sop_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_global_gtp_concat_ip_outlif_bta_sop;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 36 : 0;

    
    define->data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 36 : 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_global_bier_outlif_bta_sop_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_global_bier_outlif_bta_sop;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 40 : 0;

    
    define->data = dnx_data_lif.out_lif.global_lif_allocation_estimated_encap_size_enable_get(unit) == 1 ? 40 : 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_global_lif_allocation_estimated_encap_size_enable_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_global_lif_allocation_estimated_encap_size_enable;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_GLOBAL_LIF_ALLOCATION;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_suffix_enable;
    define->property.method_str = "suffix_enable";
    define->property.suffix = "estimated_encap_size_enable";

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_global_lif_allocation_outlif_intf_enable_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_global_lif_allocation_outlif_intf_enable;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_GLOBAL_LIF_ALLOCATION;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_suffix_enable;
    define->property.method_str = "suffix_enable";
    define->property.suffix = "outlif_intf_enable";

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_out_lif_global_lif_allocation_outlif_group_enable_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int define_index = dnx_data_lif_out_lif_define_global_lif_allocation_outlif_group_enable;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0;

    
    define->data = 0;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = spn_GLOBAL_LIF_ALLOCATION;
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_suffix_enable;
    define->property.method_str = "suffix_enable";
    define->property.suffix = "outlif_group_enable";

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &define->property, -1, &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}



static shr_error_e
jr2_a0_dnx_data_lif_out_lif_logical_to_physical_phase_map_set(
    int unit)
{
    int logical_phase_index;
    dnx_data_lif_out_lif_logical_to_physical_phase_map_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_out_lif;
    int table_index = dnx_data_lif_out_lif_table_logical_to_physical_phase_map;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 9;
    table->info_get.key_size[0] = 9;

    
    table->values[0].default_val = "-1";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_lif_out_lif_logical_to_physical_phase_map_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_lif_out_lif_table_logical_to_physical_phase_map");

    
    default_data = (dnx_data_lif_out_lif_logical_to_physical_phase_map_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->physical_phase = -1;
    
    for (logical_phase_index = 0; logical_phase_index < table->keys[0].size; logical_phase_index++)
    {
        data = (dnx_data_lif_out_lif_logical_to_physical_phase_map_t *) dnxc_data_mgmt_table_data_get(unit, table, logical_phase_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    table->values[0].property.name = spn_OUTLIF_LOGICAL_TO_PHYSICAL_PHASE_MAP;
    table->values[0].property.doc =
        "\n"
    ;
    table->values[0].property.method = dnxc_data_property_method_suffix_direct_map;
    table->values[0].property.method_str = "suffix_direct_map";
    table->values[0].property.suffix = "";
    table->values[0].property.nof_mapping = 8;
    DNXC_DATA_ALLOC(table->values[0].property.mapping, dnxc_data_property_map_t, table->values[0].property.nof_mapping, "dnx_data_lif_out_lif_logical_to_physical_phase_map_t property mapping");

    table->values[0].property.mapping[0].name = "XL";
    table->values[0].property.mapping[0].val = 0;
    table->values[0].property.mapping[1].name = "L1";
    table->values[0].property.mapping[1].val = 2;
    table->values[0].property.mapping[2].name = "L2";
    table->values[0].property.mapping[2].val = 4;
    table->values[0].property.mapping[3].name = "M1";
    table->values[0].property.mapping[3].val = 6;
    table->values[0].property.mapping[4].name = "M2";
    table->values[0].property.mapping[4].val = 7;
    table->values[0].property.mapping[5].name = "M3";
    table->values[0].property.mapping[5].val = 5;
    table->values[0].property.mapping[6].name = "S1";
    table->values[0].property.mapping[6].val = 3;
    table->values[0].property.mapping[7].name = "S2";
    table->values[0].property.mapping[7].val = 1;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));

    for (logical_phase_index = 0; logical_phase_index < table->keys[0].size; logical_phase_index++)
    {
        data = (dnx_data_lif_out_lif_logical_to_physical_phase_map_t *) dnxc_data_mgmt_table_data_get(unit, table, logical_phase_index, 0);
        SHR_IF_ERR_EXIT(dnxc_data_mgmt_property_read(unit, &table->values[0].property, logical_phase_index, &data->physical_phase));
    }
    
    table->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}





static shr_error_e
jr2_a0_dnx_data_lif_lif_table_manager_skip_in_lif_example_table_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_lif_table_manager;
    int feature_index = dnx_data_lif_lif_table_manager_skip_in_lif_example_table;
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
jr2_a0_dnx_data_lif_lif_table_manager_use_per_field_attributes_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_lif_table_manager;
    int feature_index = dnx_data_lif_lif_table_manager_use_per_field_attributes;
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
jr2_a0_dnx_data_lif_lif_table_manager_max_nof_lif_tables_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_lif_table_manager;
    int define_index = dnx_data_lif_lif_table_manager_define_max_nof_lif_tables;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 100;

    
    define->data = 100;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_lif_table_manager_max_nof_result_types_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_lif_table_manager;
    int define_index = dnx_data_lif_lif_table_manager_define_max_nof_result_types;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 30;

    
    define->data = 30;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_lif_lif_table_manager_max_fields_per_result_type_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_lif_table_manager;
    int define_index = dnx_data_lif_lif_table_manager_define_max_fields_per_result_type;
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
jr2_a0_dnx_data_lif_lif_table_manager_max_fields_per_table_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_lif_table_manager;
    int define_index = dnx_data_lif_lif_table_manager_define_max_fields_per_table;
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
jr2_a0_dnx_data_lif_feature_iop_mode_outlif_selection_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_feature;
    int feature_index = dnx_data_lif_feature_iop_mode_outlif_selection;
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
jr2_a0_dnx_data_lif_feature_iop_mode_orientation_selection_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_feature;
    int feature_index = dnx_data_lif_feature_iop_mode_orientation_selection;
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
jr2_a0_dnx_data_lif_feature_in_lif_tunnel_wide_data_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_feature;
    int feature_index = dnx_data_lif_feature_in_lif_tunnel_wide_data;
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
jr2_a0_dnx_data_lif_feature_ingress_egress_vsi_separation_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_feature;
    int feature_index = dnx_data_lif_feature_ingress_egress_vsi_separation;
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
jr2_a0_dnx_data_lif_feature_copy_outlif0_to_egress_container_by_epmf_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_lif;
    int submodule_index = dnx_data_lif_submodule_feature;
    int feature_index = dnx_data_lif_feature_copy_outlif0_to_egress_container_by_epmf;
    SHR_FUNC_INIT_VARS(unit);

    feature = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].features[feature_index];
    
    feature->default_data = 0;

    
    feature->data = 0;

    
    feature->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_feature_value_set(unit, feature));

exit:
    SHR_FUNC_EXIT;
}





shr_error_e
jr2_a0_data_lif_attach(
    int unit)
{
    dnxc_data_module_t *module = NULL;
    dnxc_data_submodule_t *submodule = NULL;
    dnxc_data_define_t *define = NULL;
    dnxc_data_feature_t *feature = NULL;
    dnxc_data_table_t *table = NULL;
    int module_index = dnx_data_module_lif;
    int submodule_index = -1, data_index = -1;
    SHR_FUNC_INIT_VARS(unit);

    COMPILER_REFERENCE(define);
    COMPILER_REFERENCE(feature);
    COMPILER_REFERENCE(table);
    COMPILER_REFERENCE(submodule);
    COMPILER_REFERENCE(data_index);
    COMPILER_REFERENCE(submodule_index);
    module = &_dnxc_data[unit].modules[module_index];
    
    submodule_index = dnx_data_lif_submodule_global_lif;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_lif_global_lif_define_use_mdb_size;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_global_lif_use_mdb_size_set;
    data_index = dnx_data_lif_global_lif_define_glem_rif_optimization_enabled;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_global_lif_glem_rif_optimization_enabled_set;
    data_index = dnx_data_lif_global_lif_define_null_lif;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_global_lif_null_lif_set;
    data_index = dnx_data_lif_global_lif_define_three_intf_glem;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_global_lif_three_intf_glem_set;
    data_index = dnx_data_lif_global_lif_define_nof_global_in_lifs;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_global_lif_nof_global_in_lifs_set;
    data_index = dnx_data_lif_global_lif_define_nof_global_out_lifs;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_global_lif_nof_global_out_lifs_set;
    data_index = dnx_data_lif_global_lif_define_egress_in_lif_null_value;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_global_lif_egress_in_lif_null_value_set;
    data_index = dnx_data_lif_global_lif_define_egress_out_lif_null_value;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_global_lif_egress_out_lif_null_value_set;
    data_index = dnx_data_lif_global_lif_define_nof_global_l2_gport_lifs;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_global_lif_nof_global_l2_gport_lifs_set;
    data_index = dnx_data_lif_global_lif_define_global_lif_bta_max_val;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_global_lif_global_lif_bta_max_val_set;
    data_index = dnx_data_lif_global_lif_define_global_lif_tag_nof_bta_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_global_lif_global_lif_tag_nof_bta_bits_set;
    data_index = dnx_data_lif_global_lif_define_global_lif_intf_max_val;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_global_lif_global_lif_intf_max_val_set;
    data_index = dnx_data_lif_global_lif_define_global_lif_tag_nof_intf_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_global_lif_global_lif_tag_nof_intf_bits_set;
    data_index = dnx_data_lif_global_lif_define_global_lif_group_max_val;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_global_lif_global_lif_group_max_val_set;
    data_index = dnx_data_lif_global_lif_define_global_lif_tag_nof_group_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_global_lif_global_lif_tag_nof_group_bits_set;
    data_index = dnx_data_lif_global_lif_define_global_lif_grain_size;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_global_lif_global_lif_grain_size_set;

    
    data_index = dnx_data_lif_global_lif_prevent_tunnel_update_rif;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_global_lif_prevent_tunnel_update_rif_set;
    data_index = dnx_data_lif_global_lif_glem_bypass_per_phase;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_global_lif_glem_bypass_per_phase_set;
    data_index = dnx_data_lif_global_lif_outlif_profile_in_glem;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_global_lif_outlif_profile_in_glem_set;

    
    
    submodule_index = dnx_data_lif_submodule_virtual_lif;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_lif_virtual_lif_define_flow_ingress_ids;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_virtual_lif_flow_ingress_ids_set;
    data_index = dnx_data_lif_virtual_lif_define_flow_egress_ids;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_virtual_lif_flow_egress_ids_set;

    

    
    
    submodule_index = dnx_data_lif_submodule_in_lif;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_lif_in_lif_define_inlif_index_bit_size;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_inlif_index_bit_size_set;
    data_index = dnx_data_lif_in_lif_define_inlif_minimum_index_size;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_inlif_minimum_index_size_set;
    data_index = dnx_data_lif_in_lif_define_inlif_resource_tag_size;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_inlif_resource_tag_size_set;
    data_index = dnx_data_lif_in_lif_define_nof_in_lif_profiles;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_nof_in_lif_profiles_set;
    data_index = dnx_data_lif_in_lif_define_nof_used_in_lif_profile_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_nof_used_in_lif_profile_bits_set;
    data_index = dnx_data_lif_in_lif_define_nof_used_eth_rif_profile_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_nof_used_eth_rif_profile_bits_set;
    data_index = dnx_data_lif_in_lif_define_nof_in_lif_incoming_orientation;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_nof_in_lif_incoming_orientation_set;
    data_index = dnx_data_lif_in_lif_define_nof_eth_rif_profiles;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_nof_eth_rif_profiles_set;
    data_index = dnx_data_lif_in_lif_define_nof_da_not_found_destination_profiles;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_nof_da_not_found_destination_profiles_set;
    data_index = dnx_data_lif_in_lif_define_default_da_not_found_destination_profile;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_default_da_not_found_destination_profile_set;
    data_index = dnx_data_lif_in_lif_define_drop_in_lif;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_drop_in_lif_set;
    data_index = dnx_data_lif_in_lif_define_mc_bridge_fallback_per_lif_profile;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_mc_bridge_fallback_per_lif_profile_set;
    data_index = dnx_data_lif_in_lif_define_max_number_of_orientation_bits_iop_mode;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_max_number_of_orientation_bits_iop_mode_set;
    data_index = dnx_data_lif_in_lif_define_max_number_of_egress_lif_profile_bits_iop_mode;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_max_number_of_egress_lif_profile_bits_iop_mode_set;
    data_index = dnx_data_lif_in_lif_define_algo_flow_inlif_bank_size;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_algo_flow_inlif_bank_size_set;
    data_index = dnx_data_lif_in_lif_define_nof_routing_enable_profiles;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_nof_routing_enable_profiles_set;
    data_index = dnx_data_lif_in_lif_define_nof_shift_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_nof_shift_bits_set;
    data_index = dnx_data_lif_in_lif_define_generic_data_1_start_position;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_generic_data_1_start_position_set;
    data_index = dnx_data_lif_in_lif_define_in_lif_profile_pmf_reserved_start_bit;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_in_lif_profile_pmf_reserved_start_bit_set;
    data_index = dnx_data_lif_in_lif_define_eth_rif_profile_pmf_reserved_start_bit;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_eth_rif_profile_pmf_reserved_start_bit_set;
    data_index = dnx_data_lif_in_lif_define_in_lif_profile_egress_reserved_start_bit;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_in_lif_profile_egress_reserved_start_bit_set;
    data_index = dnx_data_lif_in_lif_define_in_lif_profile_allocate_indexed_mode;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_in_lif_profile_allocate_indexed_mode_set;
    data_index = dnx_data_lif_in_lif_define_nof_in_lif_profile_allocate_orientation_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_nof_in_lif_profile_allocate_orientation_bits_set;
    data_index = dnx_data_lif_in_lif_define_nof_in_lif_profile_allocate_policer_inner_dp_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_nof_in_lif_profile_allocate_policer_inner_dp_bits_set;
    data_index = dnx_data_lif_in_lif_define_nof_in_lif_profile_allocate_policer_outer_dp_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_nof_in_lif_profile_allocate_policer_outer_dp_bits_set;
    data_index = dnx_data_lif_in_lif_define_nof_in_lif_profile_allocate_same_interface_mode_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_nof_in_lif_profile_allocate_same_interface_mode_bits_set;
    data_index = dnx_data_lif_in_lif_define_nof_in_lif_egress_reserved_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_nof_in_lif_egress_reserved_bits_set;
    data_index = dnx_data_lif_in_lif_define_eth_rif_profile_egress_reserved_nof_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_eth_rif_profile_egress_reserved_nof_bits_set;
    data_index = dnx_data_lif_in_lif_define_eth_rif_profile_egress_reserved_start_bit;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_eth_rif_profile_egress_reserved_start_bit_set;
    data_index = dnx_data_lif_in_lif_define_in_lif_profile_native_indexed_mode_start_bit;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_in_lif_profile_native_indexed_mode_start_bit_set;
    data_index = dnx_data_lif_in_lif_define_nof_in_lif_profile_allocate_indexed_mode_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_nof_in_lif_profile_allocate_indexed_mode_bits_set;
    data_index = dnx_data_lif_in_lif_define_in_lif_profile_allocate_orientation;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_in_lif_profile_allocate_orientation_set;
    data_index = dnx_data_lif_in_lif_define_in_lif_profile_allocate_policer_inner_dp;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_in_lif_profile_allocate_policer_inner_dp_set;
    data_index = dnx_data_lif_in_lif_define_in_lif_profile_allocate_policer_outer_dp;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_in_lif_profile_allocate_policer_outer_dp_set;
    data_index = dnx_data_lif_in_lif_define_in_lif_profile_allocate_same_interface_mode;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_in_lif_in_lif_profile_allocate_same_interface_mode_set;

    
    data_index = dnx_data_lif_in_lif_mapped_in_lif_profile;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_in_lif_mapped_in_lif_profile_set;
    data_index = dnx_data_lif_in_lif_in_lif_profile_iop_mode;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_in_lif_in_lif_profile_iop_mode_set;
    data_index = dnx_data_lif_in_lif_phy_db_dpc;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_in_lif_phy_db_dpc_set;
    data_index = dnx_data_lif_in_lif_cs_in_lif_profile_based_on_stages;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_in_lif_cs_in_lif_profile_based_on_stages_set;
    data_index = dnx_data_lif_in_lif_p2p_or_mp_based_on_cs_in_lif_profile;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_in_lif_p2p_or_mp_based_on_cs_in_lif_profile_set;
    data_index = dnx_data_lif_in_lif_use_mapped_in_lif_profile;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_in_lif_use_mapped_in_lif_profile_set;
    data_index = dnx_data_lif_in_lif_use_in_lif_profile_range_allocation_per_pmf_profiles;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_in_lif_use_in_lif_profile_range_allocation_per_pmf_profiles_set;
    data_index = dnx_data_lif_in_lif_use_eth_rif_profile_range_allocation_per_pmf_profiles;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_in_lif_use_eth_rif_profile_range_allocation_per_pmf_profiles_set;
    data_index = dnx_data_lif_in_lif_use_mapped_in_lif_profile_field_mapping_table;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_in_lif_use_mapped_in_lif_profile_field_mapping_table_set;
    data_index = dnx_data_lif_in_lif_in_lif_profile_mc_bridge_fallback_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_in_lif_in_lif_profile_mc_bridge_fallback_support_set;
    data_index = dnx_data_lif_in_lif_separate_ipv4_ipv6_urpf_mode_config;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_in_lif_separate_ipv4_ipv6_urpf_mode_config_set;
    data_index = dnx_data_lif_in_lif_ingress_interface_vip_supported;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_in_lif_ingress_interface_vip_supported_set;
    data_index = dnx_data_lif_in_lif_vxlan_vni2lif_supported;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_in_lif_vxlan_vni2lif_supported_set;

    
    
    submodule_index = dnx_data_lif_submodule_out_lif;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_lif_out_lif_define_nof_out_lif_profiles;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_nof_out_lif_profiles_set;

    if (soc_is(unit, DNX2_DEVICE))
    {
        data_index = dnx_data_lif_out_lif_define_nof_erpp_out_lif_profiles;
        define = &submodule->defines[data_index];
        define->set = jr2_a0_dnx_data_lif_out_lif_nof_erpp_out_lif_profiles_set;
    }

    data_index = dnx_data_lif_out_lif_define_nof_out_lif_outgoing_orientation;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_nof_out_lif_outgoing_orientation_set;
    data_index = dnx_data_lif_out_lif_define_outrif_profile_width;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_outrif_profile_width_set;
    data_index = dnx_data_lif_out_lif_define_glem_result;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_glem_result_set;
    data_index = dnx_data_lif_out_lif_define_physical_bank_pointer_size;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_physical_bank_pointer_size_set;
    data_index = dnx_data_lif_out_lif_define_outlif_eedb_banks_pointer_size;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_outlif_eedb_banks_pointer_size_set;
    data_index = dnx_data_lif_out_lif_define_global_outlif_bta_sop_resolution;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_global_outlif_bta_sop_resolution_set;
    data_index = dnx_data_lif_out_lif_define_pmf_outlif_profile_width;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_pmf_outlif_profile_width_set;
    data_index = dnx_data_lif_out_lif_define_pmf_outrif_profile_width;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_pmf_outrif_profile_width_set;
    data_index = dnx_data_lif_out_lif_define_etpp_out_lif_profile_default_mpls_profile;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_etpp_out_lif_profile_default_mpls_profile_set;
    data_index = dnx_data_lif_out_lif_define_etpp_out_lif_profile_default_port_profile;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_etpp_out_lif_profile_default_port_profile_set;
    data_index = dnx_data_lif_out_lif_define_etpp_out_lif_profile_default_orientation_profile;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_etpp_out_lif_profile_default_orientation_profile_set;
    data_index = dnx_data_lif_out_lif_define_outlif_pointer_size;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_outlif_pointer_size_set;
    data_index = dnx_data_lif_out_lif_define_allocation_bank_size;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_allocation_bank_size_set;
    data_index = dnx_data_lif_out_lif_define_local_outlif_width;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_local_outlif_width_set;
    data_index = dnx_data_lif_out_lif_define_outlif_profile_width;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_outlif_profile_width_set;
    data_index = dnx_data_lif_out_lif_define_nof_local_out_lifs;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_nof_local_out_lifs_set;
    data_index = dnx_data_lif_out_lif_define_physical_bank_size;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_physical_bank_size_set;
    data_index = dnx_data_lif_out_lif_define_global_ipv6_outlif_bta_sop;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_global_ipv6_outlif_bta_sop_set;
    data_index = dnx_data_lif_out_lif_define_global_vxlan_outlif_bta_sop;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_global_vxlan_outlif_bta_sop_set;
    data_index = dnx_data_lif_out_lif_define_global_mpls_outlif_bta_sop;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_global_mpls_outlif_bta_sop_set;
    data_index = dnx_data_lif_out_lif_define_global_srv6_outlif_bta_sop;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_global_srv6_outlif_bta_sop_set;
    data_index = dnx_data_lif_out_lif_define_global_sflow_extended_gateway_two_outlif_bta_sop;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_global_sflow_extended_gateway_two_outlif_bta_sop_set;
    data_index = dnx_data_lif_out_lif_define_global_sflow_extended_gateway_one_outlif_bta_sop;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_global_sflow_extended_gateway_one_outlif_bta_sop_set;
    data_index = dnx_data_lif_out_lif_define_global_sflow_header_sampling_outlif_bta_sop;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_global_sflow_header_sampling_outlif_bta_sop_set;
    data_index = dnx_data_lif_out_lif_define_global_sflow_dp_outlif_bta_sop;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_global_sflow_dp_outlif_bta_sop_set;
    data_index = dnx_data_lif_out_lif_define_global_gtp_concat_ip_outlif_bta_sop;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_global_gtp_concat_ip_outlif_bta_sop_set;
    data_index = dnx_data_lif_out_lif_define_global_bier_outlif_bta_sop;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_global_bier_outlif_bta_sop_set;
    data_index = dnx_data_lif_out_lif_define_global_lif_allocation_estimated_encap_size_enable;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_global_lif_allocation_estimated_encap_size_enable_set;
    data_index = dnx_data_lif_out_lif_define_global_lif_allocation_outlif_intf_enable;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_global_lif_allocation_outlif_intf_enable_set;
    data_index = dnx_data_lif_out_lif_define_global_lif_allocation_outlif_group_enable;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_out_lif_global_lif_allocation_outlif_group_enable_set;

    
    data_index = dnx_data_lif_out_lif_per_phase_algo;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_out_lif_per_phase_algo_set;
    data_index = dnx_data_lif_out_lif_data_entries_supported;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_out_lif_data_entries_supported_set;

    
    data_index = dnx_data_lif_out_lif_table_logical_to_physical_phase_map;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_dnx_data_lif_out_lif_logical_to_physical_phase_map_set;
    
    submodule_index = dnx_data_lif_submodule_lif_table_manager;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_lif_lif_table_manager_define_max_nof_lif_tables;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_lif_table_manager_max_nof_lif_tables_set;
    data_index = dnx_data_lif_lif_table_manager_define_max_nof_result_types;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_lif_table_manager_max_nof_result_types_set;
    data_index = dnx_data_lif_lif_table_manager_define_max_fields_per_result_type;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_lif_table_manager_max_fields_per_result_type_set;
    data_index = dnx_data_lif_lif_table_manager_define_max_fields_per_table;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_lif_lif_table_manager_max_fields_per_table_set;

    
    data_index = dnx_data_lif_lif_table_manager_skip_in_lif_example_table;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_lif_table_manager_skip_in_lif_example_table_set;
    data_index = dnx_data_lif_lif_table_manager_use_per_field_attributes;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_lif_table_manager_use_per_field_attributes_set;

    
    
    submodule_index = dnx_data_lif_submodule_feature;
    submodule = &module->submodules[submodule_index];

    

    
    data_index = dnx_data_lif_feature_iop_mode_outlif_selection;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_feature_iop_mode_outlif_selection_set;
    data_index = dnx_data_lif_feature_iop_mode_orientation_selection;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_feature_iop_mode_orientation_selection_set;
    data_index = dnx_data_lif_feature_in_lif_tunnel_wide_data;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_feature_in_lif_tunnel_wide_data_set;
    data_index = dnx_data_lif_feature_ingress_egress_vsi_separation;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_feature_ingress_egress_vsi_separation_set;
    data_index = dnx_data_lif_feature_copy_outlif0_to_egress_container_by_epmf;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_lif_feature_copy_outlif0_to_egress_container_by_epmf_set;

    

    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


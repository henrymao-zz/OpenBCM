
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_ESEM

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_esem.h>








static shr_error_e
jr2_a0_dnx_data_esem_access_cmd_nof_esem_accesses_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int define_index = dnx_data_esem_access_cmd_define_nof_esem_accesses;
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
jr2_a0_dnx_data_esem_access_cmd_app_di_id_size_in_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int define_index = dnx_data_esem_access_cmd_define_app_di_id_size_in_bits;
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
jr2_a0_dnx_data_esem_access_cmd_default_native_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int define_index = dnx_data_esem_access_cmd_define_default_native;
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
jr2_a0_dnx_data_esem_access_cmd_sflow_sample_interface_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int define_index = dnx_data_esem_access_cmd_define_sflow_sample_interface;
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
jr2_a0_dnx_data_esem_access_cmd_ip_tunnel_no_action_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int define_index = dnx_data_esem_access_cmd_define_ip_tunnel_no_action;
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
jr2_a0_dnx_data_esem_access_cmd_arp_plus_ac_port_svtag_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int define_index = dnx_data_esem_access_cmd_define_arp_plus_ac_port_svtag;
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
jr2_a0_dnx_data_esem_access_cmd_nof_esem_cmd_default_profiles_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int define_index = dnx_data_esem_access_cmd_define_nof_esem_cmd_default_profiles;
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
jr2_a0_dnx_data_esem_access_cmd_nof_cmds_size_in_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int define_index = dnx_data_esem_access_cmd_define_nof_cmds_size_in_bits;
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
jr2_a0_dnx_data_esem_access_cmd_nof_cmds_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int define_index = dnx_data_esem_access_cmd_define_nof_cmds;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 1 << dnx_data_esem.access_cmd.nof_cmds_size_in_bits_get(unit);

    
    define->data = 1 << dnx_data_esem.access_cmd.nof_cmds_size_in_bits_get(unit);

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_esem_access_cmd_min_size_for_esem_cmd_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int define_index = dnx_data_esem_access_cmd_define_min_size_for_esem_cmd;
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
jr2_a0_dnx_data_esem_access_cmd_esem_cmd_arr_prefix_gre_any_ipv4_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int define_index = dnx_data_esem_access_cmd_define_esem_cmd_arr_prefix_gre_any_ipv4;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0x00;

    
    define->data = 0x00;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_esem_access_cmd_esem_cmd_arr_prefix_vxlan_gpe_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int define_index = dnx_data_esem_access_cmd_define_esem_cmd_arr_prefix_vxlan_gpe;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0x34;

    
    define->data = 0x34;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_esem_access_cmd_esem_cmd_arr_prefix_ip_tunnel_no_action_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int define_index = dnx_data_esem_access_cmd_define_esem_cmd_arr_prefix_ip_tunnel_no_action;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0x3C;

    
    define->data = 0x3C;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_esem_access_cmd_esem_cmd_arr_prefix_arp_plus_ac_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int define_index = dnx_data_esem_access_cmd_define_esem_cmd_arr_prefix_arp_plus_ac;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0x3C;

    
    define->data = 0x3C;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_esem_access_cmd_esem_cmd_predefine_allocations_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int define_index = dnx_data_esem_access_cmd_define_esem_cmd_predefine_allocations;
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
jr2_a0_dnx_data_esem_access_cmd_no_action_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int define_index = dnx_data_esem_access_cmd_define_no_action;
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
jr2_a0_dnx_data_esem_access_cmd_default_ac_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int define_index = dnx_data_esem_access_cmd_define_default_ac;
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
jr2_a0_dnx_data_esem_access_cmd_allocation_mngr_default_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int define_index = dnx_data_esem_access_cmd_define_allocation_mngr_default;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = dnx_data_esem.access_cmd.no_action_get(unit);

    
    define->data = dnx_data_esem.access_cmd.no_action_get(unit);

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}



static shr_error_e
jr2_a0_dnx_data_esem_access_cmd_esem_cmd_table_map_set(
    int unit)
{
    dnx_data_esem_access_cmd_esem_cmd_table_map_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_access_cmd;
    int table_index = dnx_data_esem_access_cmd_table_esem_cmd_table_map;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->values[0].default_val = "DBAL_TABLE_ESEM_ACCESS_CMD_TABLE";
    table->values[1].default_val = "DBAL_FIELD_ESEM_COMMAND";
    table->values[2].default_val = "DBAL_FIELD_ESEM_ACCESS_1_VALID,DBAL_FIELD_ESEM_ACCESS_2_VALID,DBAL_FIELD_ESEM_ACCESS_3_VALID";
    table->values[3].default_val = "DBAL_FIELD_ESEM_1_APP_DB_ID,DBAL_FIELD_ESEM_2_APP_DB_ID,DBAL_FIELD_ESEM_3_APP_DB_ID";
    table->values[4].default_val = "DBAL_FIELD_ESEM_1_DESIGNATED_OFFSET,DBAL_FIELD_ESEM_2_DESIGNATED_OFFSET,DBAL_FIELD_ESEM_3_DESIGNATED_OFFSET";
    table->values[5].default_val = "DBAL_FIELD_ESEM_1_DEFAULT_RESULT_PROFILE,DBAL_FIELD_ESEM_2_DEFAULT_RESULT_PROFILE,DBAL_FIELD_ESEM_3_DEFAULT_RESULT_PROFILE";
    
    DNXC_DATA_ALLOC(table->data, dnx_data_esem_access_cmd_esem_cmd_table_map_t, (1 + 1  ), "data of dnx_data_esem_access_cmd_table_esem_cmd_table_map");

    
    default_data = (dnx_data_esem_access_cmd_esem_cmd_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->table_name = DBAL_TABLE_ESEM_ACCESS_CMD_TABLE;
    default_data->esem_cmd = DBAL_FIELD_ESEM_COMMAND;
    SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_ESEM_ACCESS_CMD_NOF_ESEM_ACCESSES, _SHR_E_INTERNAL, "out of bound access to array")
    default_data->access_valid[0] = DBAL_FIELD_ESEM_ACCESS_1_VALID;
    default_data->access_valid[1] = DBAL_FIELD_ESEM_ACCESS_2_VALID;
    default_data->access_valid[2] = DBAL_FIELD_ESEM_ACCESS_3_VALID;
    SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_ESEM_ACCESS_CMD_NOF_ESEM_ACCESSES, _SHR_E_INTERNAL, "out of bound access to array")
    default_data->access_program[0] = DBAL_FIELD_ESEM_1_APP_DB_ID;
    default_data->access_program[1] = DBAL_FIELD_ESEM_2_APP_DB_ID;
    default_data->access_program[2] = DBAL_FIELD_ESEM_3_APP_DB_ID;
    SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_ESEM_ACCESS_CMD_NOF_ESEM_ACCESSES, _SHR_E_INTERNAL, "out of bound access to array")
    default_data->access_designated_offset[0] = DBAL_FIELD_ESEM_1_DESIGNATED_OFFSET;
    default_data->access_designated_offset[1] = DBAL_FIELD_ESEM_2_DESIGNATED_OFFSET;
    default_data->access_designated_offset[2] = DBAL_FIELD_ESEM_3_DESIGNATED_OFFSET;
    SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_ESEM_ACCESS_CMD_NOF_ESEM_ACCESSES, _SHR_E_INTERNAL, "out of bound access to array")
    default_data->access_default_result[0] = DBAL_FIELD_ESEM_1_DEFAULT_RESULT_PROFILE;
    default_data->access_default_result[1] = DBAL_FIELD_ESEM_2_DEFAULT_RESULT_PROFILE;
    default_data->access_default_result[2] = DBAL_FIELD_ESEM_3_DEFAULT_RESULT_PROFILE;
    
    data = (dnx_data_esem_access_cmd_esem_cmd_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
    sal_memcpy(data, default_data, table->size_of_values);

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}





static shr_error_e
jr2_a0_dnx_data_esem_default_result_profile_default_ac_2tag_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_default_result_profile;
    int feature_index = dnx_data_esem_default_result_profile_default_ac_2tag;
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
jr2_a0_dnx_data_esem_default_result_profile_default_native_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_default_result_profile;
    int define_index = dnx_data_esem_default_result_profile_define_default_native;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 12;

    
    define->data = 12;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_esem_default_result_profile_default_ac_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_default_result_profile;
    int define_index = dnx_data_esem_default_result_profile_define_default_ac;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 13;

    
    define->data = 13;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_esem_default_result_profile_sflow_sample_interface_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_default_result_profile;
    int define_index = dnx_data_esem_default_result_profile_define_sflow_sample_interface;
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
jr2_a0_dnx_data_esem_default_result_profile_default_dual_homing_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_default_result_profile;
    int define_index = dnx_data_esem_default_result_profile_define_default_dual_homing;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 15;

    
    define->data = 15;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_esem_default_result_profile_vxlan_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_default_result_profile;
    int define_index = dnx_data_esem_default_result_profile_define_vxlan;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 11;

    
    define->data = 11;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_esem_default_result_profile_nof_profiles_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_default_result_profile;
    int define_index = dnx_data_esem_default_result_profile_define_nof_profiles;
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
jr2_a0_dnx_data_esem_default_result_profile_nof_allocable_profiles_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_default_result_profile;
    int define_index = dnx_data_esem_default_result_profile_define_nof_allocable_profiles;
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
jr2_a0_dnx_data_esem_feature_etps_properties_assignment_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_feature;
    int feature_index = dnx_data_esem_feature_etps_properties_assignment;
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
jr2_a0_dnx_data_esem_feature_key_with_sspa_contains_member_id_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_feature;
    int feature_index = dnx_data_esem_feature_key_with_sspa_contains_member_id;
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
jr2_a0_dnx_data_esem_feature_esem_is_dpc_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_feature;
    int feature_index = dnx_data_esem_feature_esem_is_dpc;
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
jr2_a0_dnx_data_esem_feature_esem_name_space_nof_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_esem;
    int submodule_index = dnx_data_esem_submodule_feature;
    int define_index = dnx_data_esem_feature_define_esem_name_space_nof_bits;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 9;

    
    define->data = 9;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}




shr_error_e
jr2_a0_data_esem_attach(
    int unit)
{
    dnxc_data_module_t *module = NULL;
    dnxc_data_submodule_t *submodule = NULL;
    dnxc_data_define_t *define = NULL;
    dnxc_data_feature_t *feature = NULL;
    dnxc_data_table_t *table = NULL;
    int module_index = dnx_data_module_esem;
    int submodule_index = -1, data_index = -1;
    SHR_FUNC_INIT_VARS(unit);

    COMPILER_REFERENCE(define);
    COMPILER_REFERENCE(feature);
    COMPILER_REFERENCE(table);
    COMPILER_REFERENCE(submodule);
    COMPILER_REFERENCE(data_index);
    COMPILER_REFERENCE(submodule_index);
    module = &_dnxc_data[unit].modules[module_index];
    
    submodule_index = dnx_data_esem_submodule_access_cmd;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_esem_access_cmd_define_nof_esem_accesses;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_access_cmd_nof_esem_accesses_set;
    data_index = dnx_data_esem_access_cmd_define_app_di_id_size_in_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_access_cmd_app_di_id_size_in_bits_set;
    data_index = dnx_data_esem_access_cmd_define_default_native;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_access_cmd_default_native_set;
    data_index = dnx_data_esem_access_cmd_define_sflow_sample_interface;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_access_cmd_sflow_sample_interface_set;
    data_index = dnx_data_esem_access_cmd_define_ip_tunnel_no_action;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_access_cmd_ip_tunnel_no_action_set;
    data_index = dnx_data_esem_access_cmd_define_arp_plus_ac_port_svtag;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_access_cmd_arp_plus_ac_port_svtag_set;
    data_index = dnx_data_esem_access_cmd_define_nof_esem_cmd_default_profiles;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_access_cmd_nof_esem_cmd_default_profiles_set;
    data_index = dnx_data_esem_access_cmd_define_nof_cmds_size_in_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_access_cmd_nof_cmds_size_in_bits_set;
    data_index = dnx_data_esem_access_cmd_define_nof_cmds;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_access_cmd_nof_cmds_set;
    data_index = dnx_data_esem_access_cmd_define_min_size_for_esem_cmd;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_access_cmd_min_size_for_esem_cmd_set;
    data_index = dnx_data_esem_access_cmd_define_esem_cmd_arr_prefix_gre_any_ipv4;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_access_cmd_esem_cmd_arr_prefix_gre_any_ipv4_set;
    data_index = dnx_data_esem_access_cmd_define_esem_cmd_arr_prefix_vxlan_gpe;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_access_cmd_esem_cmd_arr_prefix_vxlan_gpe_set;
    data_index = dnx_data_esem_access_cmd_define_esem_cmd_arr_prefix_ip_tunnel_no_action;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_access_cmd_esem_cmd_arr_prefix_ip_tunnel_no_action_set;
    data_index = dnx_data_esem_access_cmd_define_esem_cmd_arr_prefix_arp_plus_ac;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_access_cmd_esem_cmd_arr_prefix_arp_plus_ac_set;
    data_index = dnx_data_esem_access_cmd_define_esem_cmd_predefine_allocations;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_access_cmd_esem_cmd_predefine_allocations_set;
    data_index = dnx_data_esem_access_cmd_define_no_action;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_access_cmd_no_action_set;
    data_index = dnx_data_esem_access_cmd_define_default_ac;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_access_cmd_default_ac_set;
    data_index = dnx_data_esem_access_cmd_define_allocation_mngr_default;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_access_cmd_allocation_mngr_default_set;

    

    
    data_index = dnx_data_esem_access_cmd_table_esem_cmd_table_map;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_dnx_data_esem_access_cmd_esem_cmd_table_map_set;
    
    submodule_index = dnx_data_esem_submodule_default_result_profile;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_esem_default_result_profile_define_default_native;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_default_result_profile_default_native_set;
    data_index = dnx_data_esem_default_result_profile_define_default_ac;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_default_result_profile_default_ac_set;
    data_index = dnx_data_esem_default_result_profile_define_sflow_sample_interface;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_default_result_profile_sflow_sample_interface_set;
    data_index = dnx_data_esem_default_result_profile_define_default_dual_homing;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_default_result_profile_default_dual_homing_set;
    data_index = dnx_data_esem_default_result_profile_define_vxlan;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_default_result_profile_vxlan_set;
    data_index = dnx_data_esem_default_result_profile_define_nof_profiles;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_default_result_profile_nof_profiles_set;
    data_index = dnx_data_esem_default_result_profile_define_nof_allocable_profiles;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_default_result_profile_nof_allocable_profiles_set;

    
    data_index = dnx_data_esem_default_result_profile_default_ac_2tag;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_esem_default_result_profile_default_ac_2tag_set;

    
    
    submodule_index = dnx_data_esem_submodule_feature;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_esem_feature_define_esem_name_space_nof_bits;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_esem_feature_esem_name_space_nof_bits_set;

    
    data_index = dnx_data_esem_feature_etps_properties_assignment;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_esem_feature_etps_properties_assignment_set;
    data_index = dnx_data_esem_feature_key_with_sspa_contains_member_id;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_esem_feature_key_with_sspa_contains_member_id_set;
    data_index = dnx_data_esem_feature_esem_is_dpc;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_esem_feature_esem_is_dpc_set;

    

    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


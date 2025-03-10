
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_MDBDNX

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_mdb.h>












static shr_error_e
j2x_a0_dnx_data_mdb_dh_bpu_setup_extended_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int feature_index = dnx_data_mdb_dh_bpu_setup_extended_support;
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
j2x_a0_dnx_data_mdb_dh_max_nof_cluster_interfaces_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int define_index = dnx_data_mdb_dh_define_max_nof_cluster_interfaces;
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
j2x_a0_dnx_data_mdb_dh_nof_ddha_blocks_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int define_index = dnx_data_mdb_dh_define_nof_ddha_blocks;
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
j2x_a0_dnx_data_mdb_dh_nof_ddhb_blocks_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int define_index = dnx_data_mdb_dh_define_nof_ddhb_blocks;
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
j2x_a0_dnx_data_mdb_dh_nof_dhc_blocks_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int define_index = dnx_data_mdb_dh_define_nof_dhc_blocks;
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
j2x_a0_dnx_data_mdb_dh_bpu_setup_bb_connected_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int define_index = dnx_data_mdb_dh_define_bpu_setup_bb_connected;
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
j2x_a0_dnx_data_mdb_dh_bpu_setup_size_120_240_120_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int define_index = dnx_data_mdb_dh_define_bpu_setup_size_120_240_120;
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
j2x_a0_dnx_data_mdb_dh_bpu_setup_size_480_odd_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int define_index = dnx_data_mdb_dh_define_bpu_setup_size_480_odd;
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
j2x_a0_dnx_data_mdb_dh_bpu_setup_size_480_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int define_index = dnx_data_mdb_dh_define_bpu_setup_size_480;
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
j2x_a0_dnx_data_mdb_dh_bpu_setup_size_360_120_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int define_index = dnx_data_mdb_dh_define_bpu_setup_size_360_120;
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
j2x_a0_dnx_data_mdb_dh_bpu_setup_size_120_360_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int define_index = dnx_data_mdb_dh_define_bpu_setup_size_120_360;
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
j2x_a0_dnx_data_mdb_dh_bpu_setup_size_240_240_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int define_index = dnx_data_mdb_dh_define_bpu_setup_size_240_240;
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
j2x_a0_dnx_data_mdb_dh_bpu_setup_size_120_120_240_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int define_index = dnx_data_mdb_dh_define_bpu_setup_size_120_120_240;
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
j2x_a0_dnx_data_mdb_dh_bpu_setup_size_240_120_120_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int define_index = dnx_data_mdb_dh_define_bpu_setup_size_240_120_120;
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
j2x_a0_dnx_data_mdb_dh_bpu_setup_size_120_120_120_120_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int define_index = dnx_data_mdb_dh_define_bpu_setup_size_120_120_120_120;
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
j2x_a0_dnx_data_mdb_dh_dh_info_set(
    int unit)
{
    int mdb_table_id_index;
    dnx_data_mdb_dh_dh_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int table_index = dnx_data_mdb_dh_table_dh_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = MDB_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = MDB_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "0";
    table->values[2].default_val = "0";
    table->values[3].default_val = "0";
    table->values[4].default_val = "0";
    table->values[5].default_val = "0";
    table->values[6].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_dh_dh_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_dh_table_dh_info");

    
    default_data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->table_macro_interface_mapping[0] = 0;
    default_data->cluster_if_offsets_values[0] = 0;
    default_data->if_cluster_offsets_values[0] = 0;
    default_data->macro_mapping[0] = 0;
    default_data->dh_in_width = 0;
    default_data->dh_out_width = 0;
    default_data->two_ways_connectivity_bm = 0;
    
    for (mdb_table_id_index = 0; mdb_table_id_index < table->keys[0].size; mdb_table_id_index++)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, mdb_table_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (MDB_PHYSICAL_TABLE_ISEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ISEM_1, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0x0;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0x1;
        data->table_macro_interface_mapping[17] = 0x2;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0x4;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x05;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x01;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0x00;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0x00;
        data->macro_mapping[17] = 0x00;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 35;
        data->dh_out_width = 24;
        data->two_ways_connectivity_bm = 0x4;
    }
    if (MDB_PHYSICAL_TABLE_INLIF_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_INLIF_1, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0x0;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0x1;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x06;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0x00;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0x00;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 180;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_IVSI < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_IVSI, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0x0;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0x1;
        data->table_macro_interface_mapping[18] = 0x2;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x0a;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x02;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x03;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0x00;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0x02;
        data->macro_mapping[18] = 0x00;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 90;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_ISEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ISEM_2, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0x0;
        data->table_macro_interface_mapping[13] = 0x1;
        data->table_macro_interface_mapping[14] = 0x2;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0x3;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0x4;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x05;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x0a;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x01;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x03;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x01;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0x00;
        data->macro_mapping[13] = 0x00;
        data->macro_mapping[14] = 0x01;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0x01;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 75;
        data->dh_out_width = 24;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_INLIF_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_INLIF_2, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0x0;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0x1;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0x2;
        data->table_macro_interface_mapping[18] = 0x3;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x0a;
        data->cluster_if_offsets_values[18] = 0x0a;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x06;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x05;
        data->if_cluster_offsets_values[18] = 0x04;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x06;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0x01;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0x00;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0x03;
        data->macro_mapping[18] = 0x02;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 180;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_ISEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ISEM_3, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0x0;
        data->table_macro_interface_mapping[13] = 0x1;
        data->table_macro_interface_mapping[14] = 0x2;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0x3;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0x4;
        data->table_macro_interface_mapping[20] = 0x5;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x0a;
        data->cluster_if_offsets_values[13] = 0x0a;
        data->cluster_if_offsets_values[14] = 0x0f;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x05;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x0a;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x01;
        data->if_cluster_offsets_values[13] = 0x01;
        data->if_cluster_offsets_values[14] = 0x02;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x01;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x01;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0x01;
        data->macro_mapping[13] = 0x01;
        data->macro_mapping[14] = 0x02;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0x01;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0x00;
        data->dh_in_width = 75;
        data->dh_out_width = 24;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_INLIF_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_INLIF_3, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0x0;
        data->table_macro_interface_mapping[2] = 0x1;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0x2;
        data->table_macro_interface_mapping[19] = 0x3;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x0a;
        data->cluster_if_offsets_values[19] = 0x0a;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x03;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x0a;
        data->if_cluster_offsets_values[19] = 0x01;
        data->if_cluster_offsets_values[20] = 0x06;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0x01;
        data->macro_mapping[2] = 0x00;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0x03;
        data->macro_mapping[19] = 0x01;
        data->dh_in_width = 0;
        data->dh_out_width = 180;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_LEM, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0x0;
        data->table_macro_interface_mapping[2] = 0x1;
        data->table_macro_interface_mapping[3] = 0x2;
        data->table_macro_interface_mapping[4] = 0x3;
        data->table_macro_interface_mapping[5] = 0x4;
        data->table_macro_interface_mapping[6] = 0x5;
        data->table_macro_interface_mapping[7] = 0x6;
        data->table_macro_interface_mapping[8] = 0x7;
        data->table_macro_interface_mapping[9] = 0x8;
        data->table_macro_interface_mapping[10] = 0x9;
        data->table_macro_interface_mapping[11] = 0xA;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xB;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x13;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x09;
        data->if_cluster_offsets_values[2] = 0x06;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x0c;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x06;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x04;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0x02;
        data->macro_mapping[2] = 0x01;
        data->macro_mapping[3] = 0x00;
        data->macro_mapping[4] = 0x02;
        data->macro_mapping[5] = 0x00;
        data->macro_mapping[6] = 0x00;
        data->macro_mapping[7] = 0x01;
        data->macro_mapping[8] = 0x00;
        data->macro_mapping[9] = 0x00;
        data->macro_mapping[10] = 0x00;
        data->macro_mapping[11] = 0x00;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 147;
        data->dh_out_width = 120;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_ADS_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ADS_1, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x0;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0x1;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0x2;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x13;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x13;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x19;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x04;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x0a;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x03;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x04;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x01;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0x02;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0x03;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 120;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_ADS_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ADS_2, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0x0;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x1;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x13;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x06;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x08;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x04;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0x01;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x02;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 120;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_BIG_KAPS_BB_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_BIG_KAPS_BB_1, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0x0;
        data->table_macro_interface_mapping[4] = 0x1;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0x2;
        data->table_macro_interface_mapping[8] = 0x3;
        data->table_macro_interface_mapping[9] = 0x4;
        data->table_macro_interface_mapping[10] = 0x5;
        data->table_macro_interface_mapping[11] = 0x6;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0x7;
        data->table_macro_interface_mapping[14] = 0x8;
        data->table_macro_interface_mapping[15] = 0x9;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xA;
        data->table_macro_interface_mapping[19] = 0xB;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x13;
        data->cluster_if_offsets_values[4] = 0x13;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x13;
        data->cluster_if_offsets_values[8] = 0x13;
        data->cluster_if_offsets_values[9] = 0x13;
        data->cluster_if_offsets_values[10] = 0x13;
        data->cluster_if_offsets_values[11] = 0x13;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x14;
        data->cluster_if_offsets_values[14] = 0x19;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x0a;
        data->cluster_if_offsets_values[19] = 0x0a;
        data->cluster_if_offsets_values[20] = 0x14;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x04;
        data->if_cluster_offsets_values[4] = 0x10;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x0e;
        data->if_cluster_offsets_values[8] = 0x04;
        data->if_cluster_offsets_values[9] = 0x04;
        data->if_cluster_offsets_values[10] = 0x04;
        data->if_cluster_offsets_values[11] = 0x04;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x02;
        data->if_cluster_offsets_values[14] = 0x07;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x10;
        data->if_cluster_offsets_values[19] = 0x07;
        data->if_cluster_offsets_values[20] = 0x01;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0x01;
        data->macro_mapping[4] = 0x03;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0x03;
        data->macro_mapping[8] = 0x01;
        data->macro_mapping[9] = 0x01;
        data->macro_mapping[10] = 0x01;
        data->macro_mapping[11] = 0x01;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0x02;
        data->macro_mapping[14] = 0x04;
        data->macro_mapping[15] = 0x00;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0x04;
        data->macro_mapping[19] = 0x02;
        data->dh_in_width = 160;
        data->dh_out_width = 30;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_BIG_KAPS_BB_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_BIG_KAPS_BB_2, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0x0;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0x1;
        data->table_macro_interface_mapping[9] = 0x2;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0x3;
        data->table_macro_interface_mapping[15] = 0x4;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0x5;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x13;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x27;
        data->cluster_if_offsets_values[9] = 0x27;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x2d;
        data->cluster_if_offsets_values[15] = 0x14;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x0a;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x14;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x0d;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x05;
        data->if_cluster_offsets_values[9] = 0x05;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x08;
        data->if_cluster_offsets_values[15] = 0x01;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x0b;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x01;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0x03;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0x02;
        data->macro_mapping[9] = 0x02;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0x05;
        data->macro_mapping[15] = 0x01;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0x04;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 160;
        data->dh_out_width = 30;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_IOEM_0 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_IOEM_0, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0x0;
        data->table_macro_interface_mapping[13] = 0x1;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0x2;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x14;
        data->cluster_if_offsets_values[13] = 0x28;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x03;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x02;
        data->if_cluster_offsets_values[13] = 0x03;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x02;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0x02;
        data->macro_mapping[13] = 0x03;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 19;
        data->dh_out_width = 48;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_IOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_IOEM_1, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0x0;
        data->table_macro_interface_mapping[13] = 0x1;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0x2;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x17;
        data->cluster_if_offsets_values[13] = 0x2b;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x03;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x04;
        data->if_cluster_offsets_values[13] = 0x05;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x02;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0x03;
        data->macro_mapping[13] = 0x04;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 19;
        data->dh_out_width = 48;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_MAP < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_MAP, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0x0;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0x1;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0x2;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x13;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x1a;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x0f;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x04;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x06;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x02;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x04;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0x01;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0x04;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0x02;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 120;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_FEC_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_FEC_1, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0x0;
        data->table_macro_interface_mapping[1] = 0x1;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0x2;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0x3;
        data->table_macro_interface_mapping[7] = 0x4;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0x5;
        data->table_macro_interface_mapping[11] = 0x6;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x27;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x27;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x13;
        data->cluster_if_offsets_values[7] = 0x27;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x27;
        data->cluster_if_offsets_values[11] = 0x27;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x0a;
        data->if_cluster_offsets_values[1] = 0x0e;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x11;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x08;
        data->if_cluster_offsets_values[7] = 0x0f;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x05;
        data->if_cluster_offsets_values[11] = 0x05;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x05;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0x02;
        data->macro_mapping[1] = 0x04;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0x04;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0x02;
        data->macro_mapping[7] = 0x04;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0x02;
        data->macro_mapping[11] = 0x02;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 150;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_FEC_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_FEC_2, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0x0;
        data->table_macro_interface_mapping[1] = 0x1;
        data->table_macro_interface_mapping[2] = 0x2;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x3;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0x4;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0x5;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x27;
        data->cluster_if_offsets_values[2] = 0x13;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x13;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x27;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x28;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x0f;
        data->if_cluster_offsets_values[1] = 0x13;
        data->if_cluster_offsets_values[2] = 0x0a;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x0c;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x0a;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x02;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x05;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0x03;
        data->macro_mapping[1] = 0x05;
        data->macro_mapping[2] = 0x02;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x03;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0x03;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0x02;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 150;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_FEC_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_FEC_3, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0x0;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0x1;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x13;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x27;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x0f;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x14;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x05;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0x03;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0x05;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 150;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_MC_ID < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_MC_ID, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0x0;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0x1;
        data->table_macro_interface_mapping[20] = 0x2;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x1a;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x1e;
        data->cluster_if_offsets_values[20] = 0x02;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x0a;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x08;
        data->if_cluster_offsets_values[20] = 0x04;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0x05;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0x03;
        data->dh_in_width = 11;
        data->dh_out_width = 110;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_GLEM_0 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_GLEM_0, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0x0;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x1;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0x2;
        data->table_macro_interface_mapping[11] = 0x3;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0x4;
        data->table_macro_interface_mapping[17] = 0x6;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0x7;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x27;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x13;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x27;
        data->cluster_if_offsets_values[11] = 0x27;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x0f;
        data->cluster_if_offsets_values[17] = 0x1e;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x02;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x05;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x11;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x0f;
        data->if_cluster_offsets_values[11] = 0x0a;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x06;
        data->if_cluster_offsets_values[17] = 0x0c;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x01;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0x02;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x04;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0x04;
        data->macro_mapping[11] = 0x03;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0x03;
        data->macro_mapping[17] = 0x05;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 11;
        data->dh_out_width = 24;
        data->two_ways_connectivity_bm = 0x10;
    }
    if (MDB_PHYSICAL_TABLE_GLEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_GLEM_1, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0x0;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x1;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0x2;
        data->table_macro_interface_mapping[11] = 0x3;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0x4;
        data->table_macro_interface_mapping[17] = 0x6;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0x7;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x29;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x15;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x29;
        data->cluster_if_offsets_values[11] = 0x29;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x13;
        data->cluster_if_offsets_values[17] = 0x20;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x02;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x06;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x12;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x10;
        data->if_cluster_offsets_values[11] = 0x0b;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x08;
        data->if_cluster_offsets_values[17] = 0x0d;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x01;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0x03;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x05;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0x05;
        data->macro_mapping[11] = 0x04;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0x05;
        data->macro_mapping[17] = 0x06;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 11;
        data->dh_out_width = 24;
        data->two_ways_connectivity_bm = 0x10;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_1_LL < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_1_LL, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0x0;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0x1;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0x2;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0x3;
        data->table_macro_interface_mapping[15] = 0x4;
        data->table_macro_interface_mapping[16] = 0x5;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0x04;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0x03;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0x03;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0x06;
        data->macro_mapping[15] = 0x03;
        data->macro_mapping[16] = 0x07;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 0;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_1_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_1_DATA, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0x0;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0x1;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0x2;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0x3;
        data->table_macro_interface_mapping[15] = 0x4;
        data->table_macro_interface_mapping[16] = 0x5;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0x04;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0x03;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0x03;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0x06;
        data->macro_mapping[15] = 0x03;
        data->macro_mapping[16] = 0x07;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 0;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_2_LL < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_2_LL, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0x0;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0x1;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0x2;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0x3;
        data->table_macro_interface_mapping[15] = 0x4;
        data->table_macro_interface_mapping[16] = 0x5;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0x04;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0x03;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0x03;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0x06;
        data->macro_mapping[15] = 0x03;
        data->macro_mapping[16] = 0x07;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 0;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_2_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_2_DATA, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0x0;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0x1;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0x2;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0x3;
        data->table_macro_interface_mapping[15] = 0x4;
        data->table_macro_interface_mapping[16] = 0x5;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0x04;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0x03;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0x03;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0x06;
        data->macro_mapping[15] = 0x03;
        data->macro_mapping[16] = 0x07;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 0;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_1_2_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_1_2_DATA, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0x0;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0x1;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0x2;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0x3;
        data->table_macro_interface_mapping[15] = 0x4;
        data->table_macro_interface_mapping[16] = 0x5;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0x6;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x2b;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x13;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x3b;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x41;
        data->cluster_if_offsets_values[15] = 0x28;
        data->cluster_if_offsets_values[16] = 0x17;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x07;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x0d;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x06;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x09;
        data->if_cluster_offsets_values[15] = 0x07;
        data->if_cluster_offsets_values[16] = 0x0a;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x04;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0x04;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0x03;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0x03;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0x06;
        data->macro_mapping[15] = 0x03;
        data->macro_mapping[16] = 0x07;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 120;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_3_LL < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_3_LL, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0x0;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x1;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0x2;
        data->table_macro_interface_mapping[9] = 0x3;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0x4;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0x05;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x06;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0x04;
        data->macro_mapping[9] = 0x03;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0x07;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 0;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_3_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_3_DATA, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0x0;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x1;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0x2;
        data->table_macro_interface_mapping[9] = 0x3;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0x4;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0x05;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x06;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0x04;
        data->macro_mapping[9] = 0x03;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0x07;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 0;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_4_LL < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_4_LL, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0x0;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x1;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0x2;
        data->table_macro_interface_mapping[9] = 0x3;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0x4;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0x05;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x06;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0x04;
        data->macro_mapping[9] = 0x03;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0x07;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 0;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_4_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_4_DATA, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0x0;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x1;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0x2;
        data->table_macro_interface_mapping[9] = 0x3;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0x4;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0x05;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x06;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0x04;
        data->macro_mapping[9] = 0x03;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0x07;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 0;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_3_4_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_3_4_DATA, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0x0;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x1;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0x2;
        data->table_macro_interface_mapping[9] = 0x3;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0x4;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0x5;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x2b;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x17;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x3b;
        data->cluster_if_offsets_values[9] = 0x3b;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x22;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x0b;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x13;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x0a;
        data->if_cluster_offsets_values[9] = 0x06;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x0e;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x04;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0x05;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x06;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0x04;
        data->macro_mapping[9] = 0x03;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0x07;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 120;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_5_LL < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_5_LL, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x0;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0x1;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0x2;
        data->table_macro_interface_mapping[15] = 0x3;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0x4;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x07;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0x06;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0x07;
        data->macro_mapping[15] = 0x04;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0x05;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 0;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_5_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_5_DATA, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x0;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0x1;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0x2;
        data->table_macro_interface_mapping[15] = 0x3;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0x4;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x07;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0x06;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0x07;
        data->macro_mapping[15] = 0x04;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0x05;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 0;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_6_LL < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_6_LL, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x0;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0x1;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0x2;
        data->table_macro_interface_mapping[15] = 0x3;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0x4;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x07;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0x06;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0x07;
        data->macro_mapping[15] = 0x04;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0x05;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 0;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_6_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_6_DATA, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x0;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0x1;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0x2;
        data->table_macro_interface_mapping[15] = 0x3;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0x4;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x07;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0x06;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0x07;
        data->macro_mapping[15] = 0x04;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0x05;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 0;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_5_6_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_5_6_DATA, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x0;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0x1;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0x2;
        data->table_macro_interface_mapping[15] = 0x3;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0x4;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0x5;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x17;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x1c;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x41;
        data->cluster_if_offsets_values[15] = 0x28;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x1e;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x17;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x0e;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x0d;
        data->if_cluster_offsets_values[15] = 0x0b;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x11;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x04;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x07;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0x06;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0x07;
        data->macro_mapping[15] = 0x04;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0x05;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 120;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_7_LL < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_7_LL, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0x0;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x1;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0x2;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0x06;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x08;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0x08;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 0;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_7_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_7_DATA, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0x0;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x1;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0x2;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0x06;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x08;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0x08;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 0;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_8_LL < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_8_LL, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0x0;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x1;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0x2;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0x06;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x08;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0x08;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 0;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_8_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_8_DATA, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0x0;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x1;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0x2;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0x06;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x08;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0x08;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 0;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_7_8_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_7_8_DATA, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0x0;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0x1;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0x2;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0x3;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x2b;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x17;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x17;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x0f;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x1b;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x0e;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x04;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0x06;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0x08;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0x08;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 120;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EOEM_0 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EOEM_0, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0x0;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0x1;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0x2;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0x3;
        data->table_macro_interface_mapping[20] = 0x4;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x2e;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x28;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x22;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x20;
        data->cluster_if_offsets_values[20] = 0x03;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x07;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x0f;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x12;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x0c;
        data->if_cluster_offsets_values[20] = 0x02;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0x05;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0x05;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0x08;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0x04;
        data->dh_in_width = 19;
        data->dh_out_width = 48;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EOEM_1, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0x0;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0x1;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0x2;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0x3;
        data->table_macro_interface_mapping[20] = 0x4;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x31;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x2b;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x25;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x23;
        data->cluster_if_offsets_values[20] = 0x03;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x09;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x11;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x14;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x0e;
        data->if_cluster_offsets_values[20] = 0x02;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0x06;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0x06;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0x09;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0x05;
        data->dh_in_width = 19;
        data->dh_out_width = 48;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_ESEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ESEM, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0x0;
        data->table_macro_interface_mapping[9] = 0x1;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0x2;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0x3;
        data->table_macro_interface_mapping[20] = 0x5;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x3b;
        data->cluster_if_offsets_values[9] = 0x3b;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x34;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x26;
        data->cluster_if_offsets_values[20] = 0x05;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x0e;
        data->if_cluster_offsets_values[9] = 0x0a;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x0b;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x10;
        data->if_cluster_offsets_values[20] = 0x03;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0x05;
        data->macro_mapping[9] = 0x04;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0x07;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0x06;
        data->dh_in_width = 35;
        data->dh_out_width = 90;
        data->two_ways_connectivity_bm = 0x8;
    }
    if (MDB_PHYSICAL_TABLE_EVSI < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EVSI, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0x0;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0x1;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0xF;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x2b;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x17;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x00;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x0c;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x12;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x01;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0x05;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0x09;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 0;
        data->dh_out_width = 30;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_1, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0x0;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0x1;
        data->table_macro_interface_mapping[11] = 0x2;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0x3;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x13;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x2b;
        data->cluster_if_offsets_values[11] = 0x2b;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x09;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x11;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x11;
        data->if_cluster_offsets_values[11] = 0x0d;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x02;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0x04;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0x06;
        data->macro_mapping[11] = 0x06;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 67;
        data->dh_out_width = 60;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_2, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0x0;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0x1;
        data->table_macro_interface_mapping[11] = 0x2;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0x3;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x1c;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x34;
        data->cluster_if_offsets_values[11] = 0x34;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x09;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x13;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x13;
        data->if_cluster_offsets_values[11] = 0x0f;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x02;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0x05;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0x07;
        data->macro_mapping[11] = 0x07;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 67;
        data->dh_out_width = 60;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_3, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0x0;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0x1;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0x2;
        data->table_macro_interface_mapping[10] = 0x3;
        data->table_macro_interface_mapping[11] = 0x4;
        data->table_macro_interface_mapping[12] = 0xF;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0x5;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0x6;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x27;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x25;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x40;
        data->cluster_if_offsets_values[10] = 0x3d;
        data->cluster_if_offsets_values[11] = 0x3d;
        data->cluster_if_offsets_values[12] = 0x00;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x2e;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x09;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x16;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x15;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x0d;
        data->if_cluster_offsets_values[10] = 0x15;
        data->if_cluster_offsets_values[11] = 0x11;
        data->if_cluster_offsets_values[12] = 0x00;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x13;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x02;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0x05;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0x06;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0x05;
        data->macro_mapping[10] = 0x08;
        data->macro_mapping[11] = 0x08;
        data->macro_mapping[12] = 0xFF;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0x07;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 67;
        data->dh_out_width = 60;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_4 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_4, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0x0;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0x1;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0xF;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0x2;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0x3;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x1c;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x00;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x1e;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x13;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x14;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x12;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x00;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x15;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x02;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0x04;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0x07;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0xFF;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0x06;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 147;
        data->dh_out_width = 60;
        data->two_ways_connectivity_bm = 0x0;
    }
    if (MDB_PHYSICAL_TABLE_RMEP < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_dh_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_RMEP, 0);
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_EM_OVF_OR_EEDB_BANK, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_macro_interface_mapping[0] = 0xF;
        data->table_macro_interface_mapping[1] = 0xF;
        data->table_macro_interface_mapping[2] = 0xF;
        data->table_macro_interface_mapping[3] = 0xF;
        data->table_macro_interface_mapping[4] = 0xF;
        data->table_macro_interface_mapping[5] = 0xF;
        data->table_macro_interface_mapping[6] = 0xF;
        data->table_macro_interface_mapping[7] = 0xF;
        data->table_macro_interface_mapping[8] = 0xF;
        data->table_macro_interface_mapping[9] = 0xF;
        data->table_macro_interface_mapping[10] = 0xF;
        data->table_macro_interface_mapping[11] = 0xF;
        data->table_macro_interface_mapping[12] = 0x0;
        data->table_macro_interface_mapping[13] = 0xF;
        data->table_macro_interface_mapping[14] = 0xF;
        data->table_macro_interface_mapping[15] = 0xF;
        data->table_macro_interface_mapping[16] = 0x1;
        data->table_macro_interface_mapping[17] = 0xF;
        data->table_macro_interface_mapping[18] = 0xF;
        data->table_macro_interface_mapping[19] = 0xF;
        data->table_macro_interface_mapping[20] = 0x2;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->cluster_if_offsets_values[0] = 0x00;
        data->cluster_if_offsets_values[1] = 0x00;
        data->cluster_if_offsets_values[2] = 0x00;
        data->cluster_if_offsets_values[3] = 0x00;
        data->cluster_if_offsets_values[4] = 0x00;
        data->cluster_if_offsets_values[5] = 0x00;
        data->cluster_if_offsets_values[6] = 0x00;
        data->cluster_if_offsets_values[7] = 0x00;
        data->cluster_if_offsets_values[8] = 0x00;
        data->cluster_if_offsets_values[9] = 0x00;
        data->cluster_if_offsets_values[10] = 0x00;
        data->cluster_if_offsets_values[11] = 0x00;
        data->cluster_if_offsets_values[12] = 0x2f;
        data->cluster_if_offsets_values[13] = 0x00;
        data->cluster_if_offsets_values[14] = 0x00;
        data->cluster_if_offsets_values[15] = 0x00;
        data->cluster_if_offsets_values[16] = 0x17;
        data->cluster_if_offsets_values[17] = 0x00;
        data->cluster_if_offsets_values[18] = 0x00;
        data->cluster_if_offsets_values[19] = 0x00;
        data->cluster_if_offsets_values[20] = 0x06;
        SHR_RANGE_VERIFY(21, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->if_cluster_offsets_values[0] = 0x00;
        data->if_cluster_offsets_values[1] = 0x00;
        data->if_cluster_offsets_values[2] = 0x00;
        data->if_cluster_offsets_values[3] = 0x00;
        data->if_cluster_offsets_values[4] = 0x00;
        data->if_cluster_offsets_values[5] = 0x00;
        data->if_cluster_offsets_values[6] = 0x00;
        data->if_cluster_offsets_values[7] = 0x00;
        data->if_cluster_offsets_values[8] = 0x00;
        data->if_cluster_offsets_values[9] = 0x00;
        data->if_cluster_offsets_values[10] = 0x00;
        data->if_cluster_offsets_values[11] = 0x00;
        data->if_cluster_offsets_values[12] = 0x14;
        data->if_cluster_offsets_values[13] = 0x00;
        data->if_cluster_offsets_values[14] = 0x00;
        data->if_cluster_offsets_values[15] = 0x00;
        data->if_cluster_offsets_values[16] = 0x13;
        data->if_cluster_offsets_values[17] = 0x00;
        data->if_cluster_offsets_values[18] = 0x00;
        data->if_cluster_offsets_values[19] = 0x00;
        data->if_cluster_offsets_values[20] = 0x04;
        SHR_RANGE_VERIFY(20, 0, DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES_PLUS_DATA_WIDTH, _SHR_E_INTERNAL, "out of bound access to array")
        data->macro_mapping[0] = 0xFF;
        data->macro_mapping[1] = 0xFF;
        data->macro_mapping[2] = 0xFF;
        data->macro_mapping[3] = 0xFF;
        data->macro_mapping[4] = 0xFF;
        data->macro_mapping[5] = 0xFF;
        data->macro_mapping[6] = 0xFF;
        data->macro_mapping[7] = 0xFF;
        data->macro_mapping[8] = 0xFF;
        data->macro_mapping[9] = 0xFF;
        data->macro_mapping[10] = 0xFF;
        data->macro_mapping[11] = 0xFF;
        data->macro_mapping[12] = 0x08;
        data->macro_mapping[13] = 0xFF;
        data->macro_mapping[14] = 0xFF;
        data->macro_mapping[15] = 0xFF;
        data->macro_mapping[16] = 0x0a;
        data->macro_mapping[17] = 0xFF;
        data->macro_mapping[18] = 0xFF;
        data->macro_mapping[19] = 0xFF;
        data->dh_in_width = 43;
        data->dh_out_width = 110;
        data->two_ways_connectivity_bm = 0x0;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_dh_block_info_set(
    int unit)
{
    int global_macro_index_index;
    dnx_data_mdb_dh_block_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int table_index = dnx_data_mdb_dh_table_block_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = dnx_data_mdb.dh.total_nof_macroes_get(unit);
    table->info_get.key_size[0] = dnx_data_mdb.dh.total_nof_macroes_get(unit);

    
    table->values[0].default_val = "DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_NONE";
    table->values[1].default_val = "-1";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_dh_block_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_dh_table_block_info");

    
    default_data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_NONE;
    default_data->block_index = -1;
    
    for (global_macro_index_index = 0; global_macro_index_index < table->keys[0].size; global_macro_index_index++)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, global_macro_index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHB;
        data->block_index = 0;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHB;
        data->block_index = 1;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHB;
        data->block_index = 2;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHB;
        data->block_index = 3;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHB;
        data->block_index = 0;
    }
    if (5 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHB;
        data->block_index = 1;
    }
    if (6 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHB;
        data->block_index = 2;
    }
    if (7 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHB;
        data->block_index = 3;
    }
    if (8 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHA;
        data->block_index = 0;
    }
    if (9 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHA;
        data->block_index = 0;
    }
    if (10 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHA;
        data->block_index = 0;
    }
    if (11 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHA;
        data->block_index = 0;
    }
    if (12 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHB;
        data->block_index = 0;
    }
    if (13 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHB;
        data->block_index = 1;
    }
    if (14 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 14, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHB;
        data->block_index = 2;
    }
    if (15 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 15, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHB;
        data->block_index = 3;
    }
    if (16 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 16, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHB;
        data->block_index = 0;
    }
    if (17 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 17, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHB;
        data->block_index = 1;
    }
    if (18 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 18, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHB;
        data->block_index = 2;
    }
    if (19 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_block_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 19, 0);
        data->block_type = DBAL_ENUM_FVAL_MDB_BLOCK_TYPES_DDHB;
        data->block_index = 3;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_dh_macro_type_info_set(
    int unit)
{
    int macro_type_index;
    dnx_data_mdb_dh_macro_type_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int table_index = dnx_data_mdb_dh_table_macro_type_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = MDB_NOF_MACRO_TYPES;
    table->info_get.key_size[0] = MDB_NOF_MACRO_TYPES;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "0";
    table->values[2].default_val = "0";
    table->values[3].default_val = "0";
    table->values[4].default_val = "0";
    table->values[5].default_val = "invalid";
    table->values[6].default_val = "invalid";
    table->values[7].default_val = "TRUE";
    table->values[8].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_dh_macro_type_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_dh_table_macro_type_info");

    
    default_data = (dnx_data_mdb_dh_macro_type_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->nof_macros = 0;
    default_data->nof_clusters = 0;
    default_data->nof_rows = 0;
    default_data->nof_address_bits = 0;
    default_data->global_start_index = 0;
    default_data->xml_str = "invalid";
    default_data->name = "invalid";
    default_data->hitbit_support = TRUE;
    default_data->blk_core_group_inc = 0;
    
    for (macro_type_index = 0; macro_type_index < table->keys[0].size; macro_type_index++)
    {
        data = (dnx_data_mdb_dh_macro_type_info_t *) dnxc_data_mgmt_table_data_get(unit, table, macro_type_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (MDB_MACRO_A < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_macro_type_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_MACRO_A, 0);
        data->nof_macros = 12;
        data->nof_clusters = 8;
        data->nof_rows = 16384;
        data->nof_address_bits = 14;
        data->global_start_index = 0;
        data->xml_str = "dha";
        data->name = "MACRO_A";
    }
    if (MDB_MACRO_B < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_macro_type_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_MACRO_B, 0);
        data->nof_macros = 8;
        data->nof_clusters = 8;
        data->nof_rows = 8192;
        data->nof_address_bits = 13;
        data->global_start_index = 12;
        data->xml_str = "dhb";
        data->name = "MACRO_B";
    }
    if (MDB_EEDB_BANK < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_macro_type_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_EEDB_BANK, 0);
        data->nof_macros = 1;
        data->nof_clusters = 64;
        data->nof_rows = 2048;
        data->nof_address_bits = 11;
        data->global_start_index = 0;
        data->xml_str = "eedb_bank";
        data->name = "EEDB_BANK";
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_dh_entry_banks_info_set(
    int unit)
{
    int global_macro_index_index;
    dnx_data_mdb_dh_entry_banks_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int table_index = dnx_data_mdb_dh_table_entry_banks_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = dnx_data_mdb.dh.total_nof_macroes_get(unit);
    table->info_get.key_size[0] = dnx_data_mdb.dh.total_nof_macroes_get(unit);

    
    table->values[0].default_val = "INVALIDm";
    table->values[1].default_val = "INVALIDr";
    table->values[2].default_val = "INVALIDm";
    table->values[3].default_val = "INVALIDm";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_dh_entry_banks_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_dh_table_entry_banks_info");

    
    default_data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->entry_bank = INVALIDm;
    default_data->overflow_reg = INVALIDr;
    default_data->abk_bank_a = INVALIDm;
    default_data->abk_bank_b = INVALIDm;
    
    for (global_macro_index_index = 0; global_macro_index_index < table->keys[0].size; global_macro_index_index++)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, global_macro_index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->entry_bank = DDHB_MACRO_0_ENTRY_BANKm;
        data->overflow_reg = DDHB_REG_0135r;
        data->abk_bank_a = DDHB_MACRO_0_ABK_BANK_Am;
        data->abk_bank_b = DDHB_MACRO_0_ABK_BANK_Bm;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->entry_bank = DDHB_MACRO_0_ENTRY_BANKm;
        data->overflow_reg = DDHB_REG_0135r;
        data->abk_bank_a = DDHB_MACRO_0_ABK_BANK_Am;
        data->abk_bank_b = DDHB_MACRO_0_ABK_BANK_Bm;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->entry_bank = DDHB_MACRO_0_ENTRY_BANKm;
        data->overflow_reg = DDHB_REG_0135r;
        data->abk_bank_a = DDHB_MACRO_0_ABK_BANK_Am;
        data->abk_bank_b = DDHB_MACRO_0_ABK_BANK_Bm;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->entry_bank = DDHB_MACRO_0_ENTRY_BANKm;
        data->overflow_reg = DDHB_REG_0135r;
        data->abk_bank_a = DDHB_MACRO_0_ABK_BANK_Am;
        data->abk_bank_b = DDHB_MACRO_0_ABK_BANK_Bm;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->entry_bank = DDHB_MACRO_1_ENTRY_BANKm;
        data->overflow_reg = DDHB_REG_0236r;
        data->abk_bank_a = DDHB_MACRO_1_ABK_BANK_Am;
        data->abk_bank_b = DDHB_MACRO_1_ABK_BANK_Bm;
    }
    if (5 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->entry_bank = DDHB_MACRO_1_ENTRY_BANKm;
        data->overflow_reg = DDHB_REG_0236r;
        data->abk_bank_a = DDHB_MACRO_1_ABK_BANK_Am;
        data->abk_bank_b = DDHB_MACRO_1_ABK_BANK_Bm;
    }
    if (6 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->entry_bank = DDHB_MACRO_1_ENTRY_BANKm;
        data->overflow_reg = DDHB_REG_0236r;
        data->abk_bank_a = DDHB_MACRO_1_ABK_BANK_Am;
        data->abk_bank_b = DDHB_MACRO_1_ABK_BANK_Bm;
    }
    if (7 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->entry_bank = DDHB_MACRO_1_ENTRY_BANKm;
        data->overflow_reg = DDHB_REG_0236r;
        data->abk_bank_a = DDHB_MACRO_1_ABK_BANK_Am;
        data->abk_bank_b = DDHB_MACRO_1_ABK_BANK_Bm;
    }
    if (8 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->entry_bank = DDHA_MACRO_0_ENTRY_BANKm;
        data->overflow_reg = DDHA_REG_0134r;
        data->abk_bank_a = DDHA_MACRO_0_ABK_BANK_Am;
        data->abk_bank_b = DDHA_MACRO_0_ABK_BANK_Bm;
    }
    if (9 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->entry_bank = DDHA_MACRO_1_ENTRY_BANKm;
        data->overflow_reg = DDHA_REG_0234r;
        data->abk_bank_a = DDHA_MACRO_1_ABK_BANK_Am;
        data->abk_bank_b = DDHA_MACRO_1_ABK_BANK_Bm;
    }
    if (10 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->entry_bank = DDHA_MACRO_2_ENTRY_BANKm;
        data->overflow_reg = DDHA_REG_0335r;
        data->abk_bank_a = DDHA_MACRO_2_ABK_BANK_Am;
        data->abk_bank_b = DDHA_MACRO_2_ABK_BANK_Bm;
    }
    if (11 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 0);
        data->entry_bank = DDHA_MACRO_3_ENTRY_BANKm;
        data->overflow_reg = DDHA_REG_0434r;
        data->abk_bank_a = DDHA_MACRO_3_ABK_BANK_Am;
        data->abk_bank_b = DDHA_MACRO_3_ABK_BANK_Bm;
    }
    if (12 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 0);
        data->entry_bank = DDHB_MACRO_2_ENTRY_BANKm;
        data->overflow_reg = DDHB_REG_0335r;
        data->abk_bank_a = DDHB_MACRO_2_ABK_BANK_Am;
        data->abk_bank_b = DDHB_MACRO_2_ABK_BANK_Bm;
    }
    if (13 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 0);
        data->entry_bank = DDHB_MACRO_2_ENTRY_BANKm;
        data->overflow_reg = DDHB_REG_0335r;
        data->abk_bank_a = DDHB_MACRO_2_ABK_BANK_Am;
        data->abk_bank_b = DDHB_MACRO_2_ABK_BANK_Bm;
    }
    if (14 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 14, 0);
        data->entry_bank = DDHB_MACRO_2_ENTRY_BANKm;
        data->overflow_reg = DDHB_REG_0335r;
        data->abk_bank_a = DDHB_MACRO_2_ABK_BANK_Am;
        data->abk_bank_b = DDHB_MACRO_2_ABK_BANK_Bm;
    }
    if (15 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 15, 0);
        data->entry_bank = DDHB_MACRO_2_ENTRY_BANKm;
        data->overflow_reg = DDHB_REG_0335r;
        data->abk_bank_a = DDHB_MACRO_2_ABK_BANK_Am;
        data->abk_bank_b = DDHB_MACRO_2_ABK_BANK_Bm;
    }
    if (16 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 16, 0);
        data->entry_bank = DDHB_MACRO_3_ENTRY_BANKm;
        data->overflow_reg = DDHB_REG_0436r;
        data->abk_bank_a = DDHB_MACRO_3_ABK_BANK_Am;
        data->abk_bank_b = DDHB_MACRO_3_ABK_BANK_Bm;
    }
    if (17 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 17, 0);
        data->entry_bank = DDHB_MACRO_3_ENTRY_BANKm;
        data->overflow_reg = DDHB_REG_0436r;
        data->abk_bank_a = DDHB_MACRO_3_ABK_BANK_Am;
        data->abk_bank_b = DDHB_MACRO_3_ABK_BANK_Bm;
    }
    if (18 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 18, 0);
        data->entry_bank = DDHB_MACRO_3_ENTRY_BANKm;
        data->overflow_reg = DDHB_REG_0436r;
        data->abk_bank_a = DDHB_MACRO_3_ABK_BANK_Am;
        data->abk_bank_b = DDHB_MACRO_3_ABK_BANK_Bm;
    }
    if (19 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_entry_banks_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 19, 0);
        data->entry_bank = DDHB_MACRO_3_ENTRY_BANKm;
        data->overflow_reg = DDHB_REG_0436r;
        data->abk_bank_a = DDHB_MACRO_3_ABK_BANK_Am;
        data->abk_bank_b = DDHB_MACRO_3_ABK_BANK_Bm;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_dh_mdb_1_info_set(
    int unit)
{
    int global_macro_index_index;
    dnx_data_mdb_dh_mdb_1_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int table_index = dnx_data_mdb_dh_table_mdb_1_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = dnx_data_mdb.dh.total_nof_macroes_get(unit);
    table->info_get.key_size[0] = dnx_data_mdb.dh.total_nof_macroes_get(unit);

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "0";
    table->values[2].default_val = "1";
    table->values[3].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_dh_mdb_1_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_dh_table_mdb_1_info");

    
    default_data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->dbal_table = 0;
    default_data->mdb_item_1_field_size = 0;
    default_data->mdb_item_2_array_size = 1;
    default_data->mdb_item_3_field_size = 0;
    
    for (global_macro_index_index = 0; global_macro_index_index < table->keys[0].size; global_macro_index_index++)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, global_macro_index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_0;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_2_array_size = 7;
        data->mdb_item_3_field_size = 6;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_1;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_2_array_size = 7;
        data->mdb_item_3_field_size = 6;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_2;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_2_array_size = 7;
        data->mdb_item_3_field_size = 6;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_3;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_2_array_size = 7;
        data->mdb_item_3_field_size = 6;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_4;
        data->mdb_item_1_field_size = 4;
        data->mdb_item_2_array_size = 9;
        data->mdb_item_3_field_size = 6;
    }
    if (5 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_5;
        data->mdb_item_1_field_size = 4;
        data->mdb_item_2_array_size = 9;
        data->mdb_item_3_field_size = 6;
    }
    if (6 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_6;
        data->mdb_item_1_field_size = 4;
        data->mdb_item_2_array_size = 9;
        data->mdb_item_3_field_size = 6;
    }
    if (7 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_7;
        data->mdb_item_1_field_size = 4;
        data->mdb_item_2_array_size = 9;
        data->mdb_item_3_field_size = 6;
    }
    if (8 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_8;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_2_array_size = 6;
        data->mdb_item_3_field_size = 6;
    }
    if (9 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_9;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_2_array_size = 6;
        data->mdb_item_3_field_size = 7;
    }
    if (10 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_10;
        data->mdb_item_1_field_size = 4;
        data->mdb_item_2_array_size = 9;
        data->mdb_item_3_field_size = 7;
    }
    if (11 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_11;
        data->mdb_item_1_field_size = 4;
        data->mdb_item_2_array_size = 9;
        data->mdb_item_3_field_size = 7;
    }
    if (12 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_12;
        data->mdb_item_1_field_size = 4;
        data->mdb_item_2_array_size = 9;
        data->mdb_item_3_field_size = 7;
    }
    if (13 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_13;
        data->mdb_item_1_field_size = 4;
        data->mdb_item_2_array_size = 9;
        data->mdb_item_3_field_size = 7;
    }
    if (14 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 14, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_14;
        data->mdb_item_1_field_size = 4;
        data->mdb_item_2_array_size = 9;
        data->mdb_item_3_field_size = 7;
    }
    if (15 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 15, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_15;
        data->mdb_item_1_field_size = 4;
        data->mdb_item_2_array_size = 9;
        data->mdb_item_3_field_size = 7;
    }
    if (16 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 16, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_16;
        data->mdb_item_1_field_size = 4;
        data->mdb_item_2_array_size = 11;
        data->mdb_item_3_field_size = 6;
    }
    if (17 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 17, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_17;
        data->mdb_item_1_field_size = 4;
        data->mdb_item_2_array_size = 11;
        data->mdb_item_3_field_size = 6;
    }
    if (18 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 18, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_18;
        data->mdb_item_1_field_size = 4;
        data->mdb_item_2_array_size = 11;
        data->mdb_item_3_field_size = 6;
    }
    if (19 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_1_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 19, 0);
        data->dbal_table = DBAL_TABLE_MDB_1_GLOBAL_INDEX_19;
        data->mdb_item_1_field_size = 4;
        data->mdb_item_2_array_size = 11;
        data->mdb_item_3_field_size = 6;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_dh_mdb_2_info_set(
    int unit)
{
    int global_macro_index_index;
    dnx_data_mdb_dh_mdb_2_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int table_index = dnx_data_mdb_dh_table_mdb_2_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = dnx_data_mdb.dh.total_nof_macroes_get(unit);
    table->info_get.key_size[0] = dnx_data_mdb.dh.total_nof_macroes_get(unit);

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_dh_mdb_2_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_dh_table_mdb_2_info");

    
    default_data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->dbal_table = 0;
    default_data->mdb_item_1_field_size = 0;
    
    for (global_macro_index_index = 0; global_macro_index_index < table->keys[0].size; global_macro_index_index++)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, global_macro_index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_0;
        data->mdb_item_1_field_size = 5;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_1;
        data->mdb_item_1_field_size = 5;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_2;
        data->mdb_item_1_field_size = 5;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_3;
        data->mdb_item_1_field_size = 5;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_4;
        data->mdb_item_1_field_size = 5;
    }
    if (5 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_5;
        data->mdb_item_1_field_size = 5;
    }
    if (6 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_6;
        data->mdb_item_1_field_size = 5;
    }
    if (7 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_7;
        data->mdb_item_1_field_size = 5;
    }
    if (8 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_8;
        data->mdb_item_1_field_size = 5;
    }
    if (9 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_9;
        data->mdb_item_1_field_size = 5;
    }
    if (10 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_10;
        data->mdb_item_1_field_size = 5;
    }
    if (11 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_11;
        data->mdb_item_1_field_size = 5;
    }
    if (12 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_12;
        data->mdb_item_1_field_size = 5;
    }
    if (13 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_13;
        data->mdb_item_1_field_size = 5;
    }
    if (14 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 14, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_14;
        data->mdb_item_1_field_size = 5;
    }
    if (15 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 15, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_15;
        data->mdb_item_1_field_size = 5;
    }
    if (16 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 16, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_16;
        data->mdb_item_1_field_size = 5;
    }
    if (17 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 17, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_17;
        data->mdb_item_1_field_size = 5;
    }
    if (18 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 18, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_18;
        data->mdb_item_1_field_size = 5;
    }
    if (19 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_2_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 19, 0);
        data->dbal_table = DBAL_TABLE_MDB_2_GLOBAL_INDEX_19;
        data->mdb_item_1_field_size = 5;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_dh_mdb_3_info_set(
    int unit)
{
    int global_macro_index_index;
    dnx_data_mdb_dh_mdb_3_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_dh;
    int table_index = dnx_data_mdb_dh_table_mdb_3_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = dnx_data_mdb.dh.total_nof_macroes_get(unit);
    table->info_get.key_size[0] = dnx_data_mdb.dh.total_nof_macroes_get(unit);

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "1";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_dh_mdb_3_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_dh_table_mdb_3_info");

    
    default_data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->dbal_table = 0;
    default_data->mdb_item_0_array_size = 1;
    
    for (global_macro_index_index = 0; global_macro_index_index < table->keys[0].size; global_macro_index_index++)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, global_macro_index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_0;
        data->mdb_item_0_array_size = 24;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_1;
        data->mdb_item_0_array_size = 24;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_2;
        data->mdb_item_0_array_size = 24;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_3;
        data->mdb_item_0_array_size = 24;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_4;
        data->mdb_item_0_array_size = 31;
    }
    if (5 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_5;
        data->mdb_item_0_array_size = 31;
    }
    if (6 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_6;
        data->mdb_item_0_array_size = 31;
    }
    if (7 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_7;
        data->mdb_item_0_array_size = 31;
    }
    if (8 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_8;
        data->mdb_item_0_array_size = 17;
    }
    if (9 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_9;
        data->mdb_item_0_array_size = 15;
    }
    if (10 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 10, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_10;
        data->mdb_item_0_array_size = 23;
    }
    if (11 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 11, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_11;
        data->mdb_item_0_array_size = 19;
    }
    if (12 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 12, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_12;
        data->mdb_item_0_array_size = 24;
    }
    if (13 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 13, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_13;
        data->mdb_item_0_array_size = 24;
    }
    if (14 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 14, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_14;
        data->mdb_item_0_array_size = 24;
    }
    if (15 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 15, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_15;
        data->mdb_item_0_array_size = 24;
    }
    if (16 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 16, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_16;
        data->mdb_item_0_array_size = 23;
    }
    if (17 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 17, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_17;
        data->mdb_item_0_array_size = 23;
    }
    if (18 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 18, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_18;
        data->mdb_item_0_array_size = 23;
    }
    if (19 < table->keys[0].size)
    {
        data = (dnx_data_mdb_dh_mdb_3_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 19, 0);
        data->dbal_table = DBAL_TABLE_MDB_3_GLOBAL_INDEX_19;
        data->mdb_item_0_array_size = 23;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}






static shr_error_e
j2x_a0_dnx_data_mdb_pdbs_max_nof_interface_dhs_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_pdbs;
    int define_index = dnx_data_mdb_pdbs_define_max_nof_interface_dhs;
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
j2x_a0_dnx_data_mdb_pdbs_mesh_mode_support_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_pdbs;
    int define_index = dnx_data_mdb_pdbs_define_mesh_mode_support;
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
j2x_a0_dnx_data_mdb_pdbs_table_mdb_9_mdb_item_1_array_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_pdbs;
    int define_index = dnx_data_mdb_pdbs_define_table_mdb_9_mdb_item_1_array_size;
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
j2x_a0_dnx_data_mdb_pdbs_table_mdb_9_mdb_item_2_array_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_pdbs;
    int define_index = dnx_data_mdb_pdbs_define_table_mdb_9_mdb_item_2_array_size;
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
j2x_a0_dnx_data_mdb_pdbs_table_mdb_9_mdb_item_3_array_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_pdbs;
    int define_index = dnx_data_mdb_pdbs_define_table_mdb_9_mdb_item_3_array_size;
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
j2x_a0_dnx_data_mdb_pdbs_table_mdb_40_mdb_item_0_array_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_pdbs;
    int define_index = dnx_data_mdb_pdbs_define_table_mdb_40_mdb_item_0_array_size;
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
j2x_a0_dnx_data_mdb_pdbs_table_mdb_dynamic_memory_access_memory_access_field_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_pdbs;
    int define_index = dnx_data_mdb_pdbs_define_table_mdb_dynamic_memory_access_memory_access_field_size;
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
j2x_a0_dnx_data_mdb_pdbs_table_mdb_mact_dynamic_memory_access_memory_access_field_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_pdbs;
    int define_index = dnx_data_mdb_pdbs_define_table_mdb_mact_dynamic_memory_access_memory_access_field_size;
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
j2x_a0_dnx_data_mdb_pdbs_table_mdb_kaps_dynamic_memory_access_sbc_memory_access_field_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_pdbs;
    int define_index = dnx_data_mdb_pdbs_define_table_mdb_kaps_dynamic_memory_access_sbc_memory_access_field_size;
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
j2x_a0_dnx_data_mdb_pdbs_table_mdb_ddhb_dynamic_memory_access_memory_access_field_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_pdbs;
    int define_index = dnx_data_mdb_pdbs_define_table_mdb_ddhb_dynamic_memory_access_memory_access_field_size;
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
j2x_a0_dnx_data_mdb_pdbs_table_mdb_kaps_dynamic_memory_access_memory_access_field_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_pdbs;
    int define_index = dnx_data_mdb_pdbs_define_table_mdb_kaps_dynamic_memory_access_memory_access_field_size;
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
j2x_a0_dnx_data_mdb_pdbs_table_mdb_ddha_dynamic_memory_access_memory_access_field_size_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_pdbs;
    int define_index = dnx_data_mdb_pdbs_define_table_mdb_ddha_dynamic_memory_access_memory_access_field_size;
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
j2x_a0_dnx_data_mdb_em_entry_counter_decrease_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int feature_index = dnx_data_mdb_em_entry_counter_decrease_support;
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
j2x_a0_dnx_data_mdb_em_entry_type_parser_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int feature_index = dnx_data_mdb_em_entry_type_parser;
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
j2x_a0_dnx_data_mdb_em_step_table_any_cmds_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int feature_index = dnx_data_mdb_em_step_table_any_cmds_support;
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
j2x_a0_dnx_data_mdb_em_is_isem_dpc_in_vtt5_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int feature_index = dnx_data_mdb_em_is_isem_dpc_in_vtt5;
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
j2x_a0_dnx_data_mdb_em_age_support_per_entry_size_ratio_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int define_index = dnx_data_mdb_em_define_age_support_per_entry_size_ratio;
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
j2x_a0_dnx_data_mdb_em_flush_tcam_rule_counter_support_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int define_index = dnx_data_mdb_em_define_flush_tcam_rule_counter_support;
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
j2x_a0_dnx_data_mdb_em_max_nof_spn_sizes_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int define_index = dnx_data_mdb_em_define_max_nof_spn_sizes;
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
j2x_a0_dnx_data_mdb_em_defragmentation_priority_supported_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int define_index = dnx_data_mdb_em_define_defragmentation_priority_supported;
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
j2x_a0_dnx_data_mdb_em_disable_cuckoo_loop_detection_support_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int define_index = dnx_data_mdb_em_define_disable_cuckoo_loop_detection_support;
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
j2x_a0_dnx_data_mdb_em_disable_cuckoo_hit_bit_sync_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int define_index = dnx_data_mdb_em_define_disable_cuckoo_hit_bit_sync;
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
j2x_a0_dnx_data_mdb_em_age_profile_per_ratio_support_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int define_index = dnx_data_mdb_em_define_age_profile_per_ratio_support;
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
j2x_a0_dnx_data_mdb_em_flex_mag_supported_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int define_index = dnx_data_mdb_em_define_flex_mag_supported;
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
j2x_a0_dnx_data_mdb_em_flex_fully_supported_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int define_index = dnx_data_mdb_em_define_flex_fully_supported;
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
j2x_a0_dnx_data_mdb_em_extra_vmv_shift_registers_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int define_index = dnx_data_mdb_em_define_extra_vmv_shift_registers;
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
j2x_a0_dnx_data_mdb_em_scan_bank_participate_in_cuckoo_support_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int define_index = dnx_data_mdb_em_define_scan_bank_participate_in_cuckoo_support;
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
j2x_a0_dnx_data_mdb_em_scan_bank_participate_in_cuckoo_partial_support_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int define_index = dnx_data_mdb_em_define_scan_bank_participate_in_cuckoo_partial_support;
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
j2x_a0_dnx_data_mdb_em_sbus_error_code_support_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int define_index = dnx_data_mdb_em_define_sbus_error_code_support;
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
j2x_a0_dnx_data_mdb_em_defrag_interrupt_support_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int define_index = dnx_data_mdb_em_define_defrag_interrupt_support;
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
j2x_a0_dnx_data_mdb_em_flush_max_supported_payload_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int define_index = dnx_data_mdb_em_define_flush_max_supported_payload;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 64;

    
    define->data = 64;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;
    
    define->property.name = "dummy_name_use_custom";
    define->property.doc = 
        "\n"
    ;
    define->property.method = dnxc_data_property_method_custom;
    define->property.method_str = "custom";

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));

    SHR_IF_ERR_EXIT(dnx_data_property_mdb_em_flush_max_supported_payload_read(unit, (uint32 *) &define->data));
    
    define->flags |= (DNXC_DATA_F_PROPERTY);

exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_flush_payload_max_bus_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int define_index = dnx_data_mdb_em_define_flush_payload_max_bus;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 80;

    
    define->data = 80;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}



static shr_error_e
j2x_a0_dnx_data_mdb_em_spn_set(
    int unit)
{
    int dbal_id_index;
    dnx_data_mdb_em_spn_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_spn;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = DBAL_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = DBAL_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_spn_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_spn");

    
    default_data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->nof_spn_size = 0;
    default_data->spn_array[0] = 0;
    
    for (dbal_id_index = 0; dbal_id_index < table->keys[0].size; dbal_id_index++)
    {
        data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, dbal_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (DBAL_PHYSICAL_TABLE_ISEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_1, 0);
        data->nof_spn_size = 6;
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_MDB_EM_MAX_NOF_SPN_SIZES, _SHR_E_INTERNAL, "out of bound access to array")
        data->spn_array[0] = 20;
        data->spn_array[1] = 24;
        data->spn_array[2] = 32;
        data->spn_array[3] = 40;
        data->spn_array[4] = 44;
        data->spn_array[5] = 48;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_2, 0);
        data->nof_spn_size = 7;
        SHR_RANGE_VERIFY(7, 0, DNX_DATA_MAX_MDB_EM_MAX_NOF_SPN_SIZES, _SHR_E_INTERNAL, "out of bound access to array")
        data->spn_array[0] = 20;
        data->spn_array[1] = 32;
        data->spn_array[2] = 40;
        data->spn_array[3] = 64;
        data->spn_array[4] = 80;
        data->spn_array[5] = 84;
        data->spn_array[6] = 88;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_3, 0);
        data->nof_spn_size = 7;
        SHR_RANGE_VERIFY(7, 0, DNX_DATA_MAX_MDB_EM_MAX_NOF_SPN_SIZES, _SHR_E_INTERNAL, "out of bound access to array")
        data->spn_array[0] = 20;
        data->spn_array[1] = 32;
        data->spn_array[2] = 40;
        data->spn_array[3] = 64;
        data->spn_array[4] = 80;
        data->spn_array[5] = 84;
        data->spn_array[6] = 88;
    }
    if (DBAL_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEM, 0);
        data->nof_spn_size = 6;
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_MDB_EM_MAX_NOF_SPN_SIZES, _SHR_E_INTERNAL, "out of bound access to array")
        data->spn_array[0] = 24;
        data->spn_array[1] = 32;
        data->spn_array[2] = 48;
        data->spn_array[3] = 64;
        data->spn_array[4] = 80;
        data->spn_array[5] = 144;
    }
    if (DBAL_PHYSICAL_TABLE_IOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_IOEM_1, 0);
        data->nof_spn_size = 3;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_MDB_EM_MAX_NOF_SPN_SIZES, _SHR_E_INTERNAL, "out of bound access to array")
        data->spn_array[0] = 24;
        data->spn_array[1] = 28;
        data->spn_array[2] = 32;
    }
    if (DBAL_PHYSICAL_TABLE_IOEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_IOEM_2, 0);
        data->nof_spn_size = 3;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_MDB_EM_MAX_NOF_SPN_SIZES, _SHR_E_INTERNAL, "out of bound access to array")
        data->spn_array[0] = 24;
        data->spn_array[1] = 28;
        data->spn_array[2] = 32;
    }
    if (DBAL_PHYSICAL_TABLE_EOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_EOEM_1, 0);
        data->nof_spn_size = 3;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_MDB_EM_MAX_NOF_SPN_SIZES, _SHR_E_INTERNAL, "out of bound access to array")
        data->spn_array[0] = 24;
        data->spn_array[1] = 28;
        data->spn_array[2] = 32;
    }
    if (DBAL_PHYSICAL_TABLE_EOEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_EOEM_2, 0);
        data->nof_spn_size = 3;
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_MDB_EM_MAX_NOF_SPN_SIZES, _SHR_E_INTERNAL, "out of bound access to array")
        data->spn_array[0] = 24;
        data->spn_array[1] = 28;
        data->spn_array[2] = 32;
    }
    if (DBAL_PHYSICAL_TABLE_PPMC < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_PPMC, 0);
        data->nof_spn_size = 2;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_MAX_NOF_SPN_SIZES, _SHR_E_INTERNAL, "out of bound access to array")
        data->spn_array[0] = 20;
        data->spn_array[1] = 24;
    }
    if (DBAL_PHYSICAL_TABLE_GLEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_GLEM_1, 0);
        data->nof_spn_size = 2;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_MAX_NOF_SPN_SIZES, _SHR_E_INTERNAL, "out of bound access to array")
        data->spn_array[0] = 20;
        data->spn_array[1] = 24;
    }
    if (DBAL_PHYSICAL_TABLE_GLEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_GLEM_2, 0);
        data->nof_spn_size = 2;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_MAX_NOF_SPN_SIZES, _SHR_E_INTERNAL, "out of bound access to array")
        data->spn_array[0] = 20;
        data->spn_array[1] = 24;
    }
    if (DBAL_PHYSICAL_TABLE_ESEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ESEM, 0);
        data->nof_spn_size = 5;
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_MDB_EM_MAX_NOF_SPN_SIZES, _SHR_E_INTERNAL, "out of bound access to array")
        data->spn_array[0] = 24;
        data->spn_array[1] = 32;
        data->spn_array[2] = 40;
        data->spn_array[3] = 44;
        data->spn_array[4] = 48;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_1, 0);
        data->nof_spn_size = 8;
        SHR_RANGE_VERIFY(8, 0, DNX_DATA_MAX_MDB_EM_MAX_NOF_SPN_SIZES, _SHR_E_INTERNAL, "out of bound access to array")
        data->spn_array[0] = 20;
        data->spn_array[1] = 24;
        data->spn_array[2] = 32;
        data->spn_array[3] = 40;
        data->spn_array[4] = 48;
        data->spn_array[5] = 64;
        data->spn_array[6] = 72;
        data->spn_array[7] = 80;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_2, 0);
        data->nof_spn_size = 8;
        SHR_RANGE_VERIFY(8, 0, DNX_DATA_MAX_MDB_EM_MAX_NOF_SPN_SIZES, _SHR_E_INTERNAL, "out of bound access to array")
        data->spn_array[0] = 20;
        data->spn_array[1] = 24;
        data->spn_array[2] = 32;
        data->spn_array[3] = 40;
        data->spn_array[4] = 48;
        data->spn_array[5] = 64;
        data->spn_array[6] = 72;
        data->spn_array[7] = 80;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_3, 0);
        data->nof_spn_size = 8;
        SHR_RANGE_VERIFY(8, 0, DNX_DATA_MAX_MDB_EM_MAX_NOF_SPN_SIZES, _SHR_E_INTERNAL, "out of bound access to array")
        data->spn_array[0] = 20;
        data->spn_array[1] = 24;
        data->spn_array[2] = 32;
        data->spn_array[3] = 40;
        data->spn_array[4] = 48;
        data->spn_array[5] = 64;
        data->spn_array[6] = 72;
        data->spn_array[7] = 80;
    }
    if (DBAL_PHYSICAL_TABLE_LEXEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEXEM, 0);
        data->nof_spn_size = 6;
        SHR_RANGE_VERIFY(6, 0, DNX_DATA_MAX_MDB_EM_MAX_NOF_SPN_SIZES, _SHR_E_INTERNAL, "out of bound access to array")
        data->spn_array[0] = 24;
        data->spn_array[1] = 32;
        data->spn_array[2] = 48;
        data->spn_array[3] = 64;
        data->spn_array[4] = 80;
        data->spn_array[5] = 144;
    }
    if (DBAL_PHYSICAL_TABLE_RMEP_EM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_spn_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_RMEP_EM, 0);
        data->nof_spn_size = 4;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_MDB_EM_MAX_NOF_SPN_SIZES, _SHR_E_INTERNAL, "out of bound access to array")
        data->spn_array[0] = 20;
        data->spn_array[1] = 32;
        data->spn_array[2] = 40;
        data->spn_array[3] = 52;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_compare_size_set(
    int unit)
{
    int entry_size_index;
    dnx_data_mdb_em_compare_size_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_compare_size;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = MDB_STEP_TABLE_NOF_ENTRY_SIZES;
    table->info_get.key_size[0] = MDB_STEP_TABLE_NOF_ENTRY_SIZES;

    
    table->values[0].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_compare_size_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_compare_size");

    
    default_data = (dnx_data_mdb_em_compare_size_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->max_compare_size = 0;
    
    for (entry_size_index = 0; entry_size_index < table->keys[0].size; entry_size_index++)
    {
        data = (dnx_data_mdb_em_compare_size_t *) dnxc_data_mgmt_table_data_get(unit, table, entry_size_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (MDB_STEP_TABLE_ENTRY_SIZE_ONE < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_compare_size_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_STEP_TABLE_ENTRY_SIZE_ONE, 0);
        data->max_compare_size = 150;
    }
    if (MDB_STEP_TABLE_ENTRY_SIZE_HALF < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_compare_size_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_STEP_TABLE_ENTRY_SIZE_HALF, 0);
        data->max_compare_size = 120;
    }
    if (MDB_STEP_TABLE_ENTRY_SIZE_QUARTER < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_compare_size_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_STEP_TABLE_ENTRY_SIZE_QUARTER, 0);
        data->max_compare_size = 60;
    }
    if (MDB_STEP_TABLE_ENTRY_SIZE_EIGHTH < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_compare_size_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_STEP_TABLE_ENTRY_SIZE_EIGHTH, 0);
        data->max_compare_size = 28;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_em_info_set(
    int unit)
{
    int dbal_id_index;
    dnx_data_mdb_em_em_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_em_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = DBAL_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = DBAL_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "INVALIDm";
    table->values[2].default_val = "0";
    table->values[3].default_val = "INVALIDr";
    table->values[4].default_val = "0";
    table->values[5].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_em_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_em_info");

    
    default_data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->tid_size = 0;
    default_data->em_interface = INVALIDm;
    default_data->entry_size = 0;
    default_data->status_reg = INVALIDr;
    default_data->step_table_size = 0;
    default_data->ovf_cam_size = 0;
    
    for (dbal_id_index = 0; dbal_id_index < table->keys[0].size; dbal_id_index++)
    {
        data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, dbal_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (DBAL_PHYSICAL_TABLE_PPMC < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_PPMC, 0);
        data->tid_size = 2;
        data->em_interface = MDB_MC_IDm;
        data->entry_size = 137;
        data->status_reg = MDB_REG_290r;
        data->step_table_size = 1024;
        data->ovf_cam_size = 8;
    }
    if (DBAL_PHYSICAL_TABLE_RMEP_EM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_RMEP_EM, 0);
        data->tid_size = 3;
        data->em_interface = MDB_RMEPm;
        data->entry_size = 137;
        data->status_reg = MDB_REG_570r;
        data->step_table_size = 1024;
        data->ovf_cam_size = 8;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_1, 0);
        data->tid_size = 6;
        data->em_interface = MDB_ISEM_1m;
        data->entry_size = 137;
        data->status_reg = MDB_REG_117r;
        data->step_table_size = 1024;
        data->ovf_cam_size = 8;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_2, 0);
        data->tid_size = 6;
        data->em_interface = MDB_ISEM_2m;
        data->entry_size = 137;
        data->status_reg = MDB_REG_138r;
        data->step_table_size = 1024;
        data->ovf_cam_size = 8;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_3, 0);
        data->tid_size = 6;
        data->em_interface = MDB_ISEM_3m;
        data->entry_size = 137;
        data->status_reg = MDB_REG_160r;
        data->step_table_size = 1024;
        data->ovf_cam_size = 8;
    }
    if (DBAL_PHYSICAL_TABLE_GLEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_GLEM_1, 0);
        data->tid_size = 2;
        data->em_interface = MDB_GLEM_0m;
        data->entry_size = 137;
        data->status_reg = MDB_REG_311r;
        data->step_table_size = 512;
        data->ovf_cam_size = 8;
    }
    if (DBAL_PHYSICAL_TABLE_GLEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_GLEM_2, 0);
        data->tid_size = 2;
        data->em_interface = MDB_GLEM_1m;
        data->entry_size = 137;
        data->status_reg = MDB_REG_332r;
        data->step_table_size = 512;
        data->ovf_cam_size = 8;
    }
    if (DBAL_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEM, 0);
        data->tid_size = 6;
        data->em_interface = MDB_LEMm;
        data->entry_size = 257;
        data->status_reg = MDB_REG_212r;
        data->step_table_size = 2048;
        data->ovf_cam_size = 8;
    }
    if (DBAL_PHYSICAL_TABLE_ESEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ESEM, 0);
        data->tid_size = 6;
        data->em_interface = MDB_ESEMm;
        data->entry_size = 137;
        data->status_reg = MDB_REG_396r;
        data->step_table_size = 1024;
        data->ovf_cam_size = 8;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_1, 0);
        data->tid_size = 6;
        data->em_interface = MDB_EXEM_1m;
        data->entry_size = 137;
        data->status_reg = MDB_REG_417r;
        data->step_table_size = 1024;
        data->ovf_cam_size = 8;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_2, 0);
        data->tid_size = 6;
        data->em_interface = MDB_EXEM_2m;
        data->entry_size = 137;
        data->status_reg = MDB_REG_438r;
        data->step_table_size = 1024;
        data->ovf_cam_size = 8;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_3, 0);
        data->tid_size = 6;
        data->em_interface = MDB_EXEM_3m;
        data->entry_size = 137;
        data->status_reg = MDB_REG_494r;
        data->step_table_size = 1024;
        data->ovf_cam_size = 8;
    }
    if (DBAL_PHYSICAL_TABLE_LEXEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEXEM, 0);
        data->tid_size = 6;
        data->em_interface = MDB_EXEM_4m;
        data->entry_size = 257;
        data->status_reg = MDB_REG_546r;
        data->step_table_size = 2048;
        data->ovf_cam_size = 8;
    }
    if (DBAL_PHYSICAL_TABLE_EOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_EOEM_1, 0);
        data->tid_size = 6;
        data->em_interface = MDB_EOEM_0m;
        data->entry_size = 137;
        data->status_reg = MDB_REG_353r;
        data->step_table_size = 1024;
        data->ovf_cam_size = 8;
    }
    if (DBAL_PHYSICAL_TABLE_EOEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_EOEM_2, 0);
        data->tid_size = 6;
        data->em_interface = MDB_EOEM_1m;
        data->entry_size = 137;
        data->status_reg = MDB_REG_374r;
        data->step_table_size = 1024;
        data->ovf_cam_size = 8;
    }
    if (DBAL_PHYSICAL_TABLE_IOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_IOEM_1, 0);
        data->tid_size = 6;
        data->em_interface = MDB_IOEM_0m;
        data->entry_size = 137;
        data->status_reg = MDB_REG_249r;
        data->step_table_size = 1024;
        data->ovf_cam_size = 8;
    }
    if (DBAL_PHYSICAL_TABLE_IOEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_IOEM_2, 0);
        data->tid_size = 6;
        data->em_interface = MDB_IOEM_1m;
        data->entry_size = 137;
        data->status_reg = MDB_REG_270r;
        data->step_table_size = 1024;
        data->ovf_cam_size = 8;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_step_table_pdb_max_depth_set(
    int unit)
{
    int dbal_id_index;
    dnx_data_mdb_em_step_table_pdb_max_depth_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_step_table_pdb_max_depth;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = DBAL_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = DBAL_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "16";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_step_table_pdb_max_depth_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_step_table_pdb_max_depth");

    
    default_data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->max_depth = 16;
    
    for (dbal_id_index = 0; dbal_id_index < table->keys[0].size; dbal_id_index++)
    {
        data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, dbal_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (DBAL_PHYSICAL_TABLE_PPMC < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_PPMC, 0);
        data->max_depth = 24;
    }
    if (DBAL_PHYSICAL_TABLE_RMEP_EM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_RMEP_EM, 0);
        data->max_depth = 24;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_1, 0);
        data->max_depth = 32;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_2, 0);
        data->max_depth = 32;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_3, 0);
        data->max_depth = 32;
    }
    if (DBAL_PHYSICAL_TABLE_GLEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_GLEM_1, 0);
        data->max_depth = 8;
    }
    if (DBAL_PHYSICAL_TABLE_GLEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_GLEM_2, 0);
        data->max_depth = 8;
    }
    if (DBAL_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEM, 0);
        data->max_depth = 32;
    }
    if (DBAL_PHYSICAL_TABLE_ESEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ESEM, 0);
        data->max_depth = 32;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_1, 0);
        data->max_depth = 24;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_2, 0);
        data->max_depth = 24;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_3, 0);
        data->max_depth = 32;
    }
    if (DBAL_PHYSICAL_TABLE_LEXEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEXEM, 0);
        data->max_depth = 32;
    }
    if (DBAL_PHYSICAL_TABLE_EOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_EOEM_1, 0);
        data->max_depth = 24;
    }
    if (DBAL_PHYSICAL_TABLE_EOEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_EOEM_2, 0);
        data->max_depth = 24;
    }
    if (DBAL_PHYSICAL_TABLE_IOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_IOEM_1, 0);
        data->max_depth = 24;
    }
    if (DBAL_PHYSICAL_TABLE_IOEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_step_table_pdb_max_depth_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_IOEM_2, 0);
        data->max_depth = 24;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_step_table_max_depth_possible_set(
    int unit)
{
    int step_table_size_indication_index;
    int aspect_ratio_combination_index;
    dnx_data_mdb_em_step_table_max_depth_possible_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_step_table_max_depth_possible;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 3;
    table->info_get.key_size[0] = 3;
    table->keys[1].size = 16;
    table->info_get.key_size[1] = 16;

    
    table->values[0].default_val = "20";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }
    if (table->keys[1].size == 0 || table->info_get.key_size[1] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_step_table_max_depth_possible_t, (1 * (table->keys[0].size) * (table->keys[1].size) + 1  ), "data of dnx_data_mdb_em_table_step_table_max_depth_possible");

    
    default_data = (dnx_data_mdb_em_step_table_max_depth_possible_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->max_depth = 20;
    
    for (step_table_size_indication_index = 0; step_table_size_indication_index < table->keys[0].size; step_table_size_indication_index++)
    {
        for (aspect_ratio_combination_index = 0; aspect_ratio_combination_index < table->keys[1].size; aspect_ratio_combination_index++)
        {
            data = (dnx_data_mdb_em_step_table_max_depth_possible_t *) dnxc_data_mgmt_table_data_get(unit, table, step_table_size_indication_index, aspect_ratio_combination_index);
            sal_memcpy(data, default_data, table->size_of_values);
        }
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_set(
    int unit)
{
    int aspect_ratio_index;
    int nof_ways_index;
    dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_step_table_max_depth_nof_ways_ar;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 5;
    table->info_get.key_size[0] = 5;
    table->keys[1].size = DNX_DATA_MAX_MDB_PDBS_MAX_NOF_INTERFACE_DHS;
    table->info_get.key_size[1] = DNX_DATA_MAX_MDB_PDBS_MAX_NOF_INTERFACE_DHS;

    
    table->values[0].default_val = "3";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }
    if (table->keys[1].size == 0 || table->info_get.key_size[1] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t, (1 * (table->keys[0].size) * (table->keys[1].size) + 1  ), "data of dnx_data_mdb_em_table_step_table_max_depth_nof_ways_ar");

    
    default_data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->max_depth = 3;
    
    for (aspect_ratio_index = 0; aspect_ratio_index < table->keys[0].size; aspect_ratio_index++)
    {
        for (nof_ways_index = 0; nof_ways_index < table->keys[1].size; nof_ways_index++)
        {
            data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, aspect_ratio_index, nof_ways_index);
            sal_memcpy(data, default_data, table->size_of_values);
        }
    }
    
    if (0 < table->keys[0].size && 2 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 2);
        data->max_depth = 20;
    }
    if (0 < table->keys[0].size && 3 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 3);
        data->max_depth = 11;
    }
    if (0 < table->keys[0].size && 4 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 4);
        data->max_depth = 7;
    }
    if (0 < table->keys[0].size && 5 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 5);
        data->max_depth = 6;
    }
    if (0 < table->keys[0].size && 6 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 6);
        data->max_depth = 6;
    }
    if (0 < table->keys[0].size && 7 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 7);
        data->max_depth = 5;
    }
    if (0 < table->keys[0].size && 8 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 8);
        data->max_depth = 5;
    }
    if (0 < table->keys[0].size && 9 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 9);
        data->max_depth = 5;
    }
    if (0 < table->keys[0].size && 10 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 10);
        data->max_depth = 4;
    }
    if (0 < table->keys[0].size && 11 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 11);
        data->max_depth = 4;
    }
    if (1 < table->keys[0].size && 2 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 2);
        data->max_depth = 11;
    }
    if (1 < table->keys[0].size && 3 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 3);
        data->max_depth = 6;
    }
    if (1 < table->keys[0].size && 4 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 4);
        data->max_depth = 5;
    }
    if (1 < table->keys[0].size && 5 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 5);
        data->max_depth = 4;
    }
    if (1 < table->keys[0].size && 6 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 6);
        data->max_depth = 4;
    }
    if (1 < table->keys[0].size && 7 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 7);
        data->max_depth = 4;
    }
    if (1 < table->keys[0].size && 8 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 8);
        data->max_depth = 4;
    }
    if (1 < table->keys[0].size && 9 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 9);
        data->max_depth = 3;
    }
    if (1 < table->keys[0].size && 10 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 10);
        data->max_depth = 3;
    }
    if (1 < table->keys[0].size && 11 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 11);
        data->max_depth = 3;
    }
    if (2 < table->keys[0].size && 2 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 2);
        data->max_depth = 6;
    }
    if (2 < table->keys[0].size && 3 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 3);
        data->max_depth = 4;
    }
    if (2 < table->keys[0].size && 4 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 4);
        data->max_depth = 4;
    }
    if (2 < table->keys[0].size && 5 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 5);
        data->max_depth = 3;
    }
    if (2 < table->keys[0].size && 6 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 6);
        data->max_depth = 3;
    }
    if (2 < table->keys[0].size && 7 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 7);
        data->max_depth = 3;
    }
    if (2 < table->keys[0].size && 8 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 8);
        data->max_depth = 3;
    }
    if (2 < table->keys[0].size && 9 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 9);
        data->max_depth = 3;
    }
    if (2 < table->keys[0].size && 10 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 10);
        data->max_depth = 3;
    }
    if (2 < table->keys[0].size && 11 < table->keys[1].size)
    {
        data = (dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 11);
        data->max_depth = 3;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_mdb_15_info_set(
    int unit)
{
    int dbal_id_index;
    dnx_data_mdb_em_mdb_15_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_mdb_15_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = DBAL_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = DBAL_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_mdb_15_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_mdb_15_info");

    
    default_data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->dbal_table = 0;
    default_data->mdb_item_5_field_size = 0;
    
    for (dbal_id_index = 0; dbal_id_index < table->keys[0].size; dbal_id_index++)
    {
        data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, dbal_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (DBAL_PHYSICAL_TABLE_ISEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_15_ISEM_1;
        data->mdb_item_5_field_size = 4;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_15_ISEM_2;
        data->mdb_item_5_field_size = 4;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_15_ISEM_3;
        data->mdb_item_5_field_size = 4;
    }
    if (DBAL_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_15_LEM;
        data->mdb_item_5_field_size = 4;
    }
    if (DBAL_PHYSICAL_TABLE_IOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_IOEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_15_IOEM_0;
        data->mdb_item_5_field_size = 4;
    }
    if (DBAL_PHYSICAL_TABLE_IOEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_IOEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_15_IOEM_1;
        data->mdb_item_5_field_size = 4;
    }
    if (DBAL_PHYSICAL_TABLE_PPMC < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_PPMC, 0);
        data->dbal_table = DBAL_TABLE_MDB_15_MC_ID;
        data->mdb_item_5_field_size = 4;
    }
    if (DBAL_PHYSICAL_TABLE_GLEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_GLEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_15_GLEM_0;
        data->mdb_item_5_field_size = 4;
    }
    if (DBAL_PHYSICAL_TABLE_GLEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_GLEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_15_GLEM_1;
        data->mdb_item_5_field_size = 4;
    }
    if (DBAL_PHYSICAL_TABLE_EOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_EOEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_15_EOEM_0;
        data->mdb_item_5_field_size = 4;
    }
    if (DBAL_PHYSICAL_TABLE_EOEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_EOEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_15_EOEM_1;
        data->mdb_item_5_field_size = 4;
    }
    if (DBAL_PHYSICAL_TABLE_ESEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ESEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_15_ESEM;
        data->mdb_item_5_field_size = 4;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_15_EXEM_1;
        data->mdb_item_5_field_size = 4;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_15_EXEM_2;
        data->mdb_item_5_field_size = 4;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_15_EXEM_3;
        data->mdb_item_5_field_size = 4;
    }
    if (DBAL_PHYSICAL_TABLE_LEXEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEXEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_15_EXEM_4;
        data->mdb_item_5_field_size = 4;
    }
    if (DBAL_PHYSICAL_TABLE_RMEP_EM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_15_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_RMEP_EM, 0);
        data->dbal_table = DBAL_TABLE_MDB_15_RMEP;
        data->mdb_item_5_field_size = 4;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_mdb_16_info_set(
    int unit)
{
    int mdb_table_id_index;
    dnx_data_mdb_em_mdb_16_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_mdb_16_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = MDB_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = MDB_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_mdb_16_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_mdb_16_info");

    
    default_data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->dbal_table = 0;
    default_data->mdb_item_0_field_size = 0;
    
    for (mdb_table_id_index = 0; mdb_table_id_index < table->keys[0].size; mdb_table_id_index++)
    {
        data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, mdb_table_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (MDB_PHYSICAL_TABLE_ISEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ISEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_16_ISEM_1;
        data->mdb_item_0_field_size = 9;
    }
    if (MDB_PHYSICAL_TABLE_ISEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ISEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_16_ISEM_2;
        data->mdb_item_0_field_size = 9;
    }
    if (MDB_PHYSICAL_TABLE_ISEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ISEM_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_16_ISEM_3;
        data->mdb_item_0_field_size = 11;
    }
    if (MDB_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_LEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_16_LEM;
        data->mdb_item_0_field_size = 12;
    }
    if (MDB_PHYSICAL_TABLE_IOEM_0 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_IOEM_0, 0);
        data->dbal_table = DBAL_TABLE_MDB_16_IOEM_0;
        data->mdb_item_0_field_size = 5;
    }
    if (MDB_PHYSICAL_TABLE_IOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_IOEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_16_IOEM_1;
        data->mdb_item_0_field_size = 5;
    }
    if (MDB_PHYSICAL_TABLE_EOEM_0 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EOEM_0, 0);
        data->dbal_table = DBAL_TABLE_MDB_16_EOEM_0;
        data->mdb_item_0_field_size = 9;
    }
    if (MDB_PHYSICAL_TABLE_EOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EOEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_16_EOEM_1;
        data->mdb_item_0_field_size = 9;
    }
    if (MDB_PHYSICAL_TABLE_MC_ID < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_MC_ID, 0);
        data->dbal_table = DBAL_TABLE_MDB_16_MC_ID;
        data->mdb_item_0_field_size = 5;
    }
    if (MDB_PHYSICAL_TABLE_GLEM_0 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_GLEM_0, 0);
        data->dbal_table = DBAL_TABLE_MDB_16_GLEM_0;
        data->mdb_item_0_field_size = 15;
    }
    if (MDB_PHYSICAL_TABLE_GLEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_GLEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_16_GLEM_1;
        data->mdb_item_0_field_size = 15;
    }
    if (MDB_PHYSICAL_TABLE_ESEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ESEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_16_ESEM;
        data->mdb_item_0_field_size = 11;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_16_EXEM_1;
        data->mdb_item_0_field_size = 7;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_16_EXEM_2;
        data->mdb_item_0_field_size = 7;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_16_EXEM_3;
        data->mdb_item_0_field_size = 13;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_4 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_4, 0);
        data->dbal_table = DBAL_TABLE_MDB_16_EXEM_4;
        data->mdb_item_0_field_size = 4;
    }
    if (MDB_PHYSICAL_TABLE_RMEP < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_16_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_RMEP, 0);
        data->dbal_table = DBAL_TABLE_MDB_16_RMEP;
        data->mdb_item_0_field_size = 5;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_mdb_21_info_set(
    int unit)
{
    int mdb_table_id_index;
    dnx_data_mdb_em_mdb_21_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_mdb_21_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = MDB_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = MDB_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_mdb_21_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_mdb_21_info");

    
    default_data = (dnx_data_mdb_em_mdb_21_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->dbal_table = 0;
    default_data->mdb_item_0_field_size = 0;
    
    for (mdb_table_id_index = 0; mdb_table_id_index < table->keys[0].size; mdb_table_id_index++)
    {
        data = (dnx_data_mdb_em_mdb_21_info_t *) dnxc_data_mgmt_table_data_get(unit, table, mdb_table_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (MDB_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_21_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_LEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_21_LEM;
        data->mdb_item_0_field_size = 4;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_21_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_21_EXEM_3;
        data->mdb_item_0_field_size = 8;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_4 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_21_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_4, 0);
        data->dbal_table = DBAL_TABLE_MDB_21_EXEM_4;
        data->mdb_item_0_field_size = 8;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_mdb_23_info_set(
    int unit)
{
    int mdb_table_id_index;
    dnx_data_mdb_em_mdb_23_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_mdb_23_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = MDB_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = MDB_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "0";
    table->values[2].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_mdb_23_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_mdb_23_info");

    
    default_data = (dnx_data_mdb_em_mdb_23_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->dbal_table = 0;
    default_data->mdb_item_0_field_size = 0;
    default_data->mdb_item_1_field_size = 0;
    
    for (mdb_table_id_index = 0; mdb_table_id_index < table->keys[0].size; mdb_table_id_index++)
    {
        data = (dnx_data_mdb_em_mdb_23_info_t *) dnxc_data_mgmt_table_data_get(unit, table, mdb_table_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (MDB_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_23_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_LEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_23_LEM;
        data->mdb_item_0_field_size = 12;
        data->mdb_item_1_field_size = 4;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_23_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_23_EXEM_3;
        data->mdb_item_0_field_size = 13;
        data->mdb_item_1_field_size = 4;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_4 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_23_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_4, 0);
        data->dbal_table = DBAL_TABLE_MDB_23_EXEM_4;
        data->mdb_item_0_field_size = 4;
        data->mdb_item_1_field_size = 2;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_mdb_24_info_set(
    int unit)
{
    int mdb_table_id_index;
    dnx_data_mdb_em_mdb_24_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_mdb_24_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = MDB_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = MDB_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "1";
    table->values[2].default_val = "0";
    table->values[3].default_val = "1";
    table->values[4].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_mdb_24_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_mdb_24_info");

    
    default_data = (dnx_data_mdb_em_mdb_24_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->dbal_table = 0;
    default_data->mdb_item_0_array_size = 1;
    default_data->mdb_item_0_field_size = 0;
    default_data->mdb_item_1_array_size = 1;
    default_data->mdb_item_1_field_size = 0;
    
    for (mdb_table_id_index = 0; mdb_table_id_index < table->keys[0].size; mdb_table_id_index++)
    {
        data = (dnx_data_mdb_em_mdb_24_info_t *) dnxc_data_mgmt_table_data_get(unit, table, mdb_table_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (MDB_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_24_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_LEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_24_LEM;
        data->mdb_item_0_array_size = 12;
        data->mdb_item_0_field_size = 5;
        data->mdb_item_1_array_size = 12;
        data->mdb_item_1_field_size = 18;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_24_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_24_EXEM_3;
        data->mdb_item_0_array_size = 13;
        data->mdb_item_0_field_size = 5;
        data->mdb_item_1_array_size = 13;
        data->mdb_item_1_field_size = 18;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_4 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_24_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_4, 0);
        data->dbal_table = DBAL_TABLE_MDB_24_EXEM_4;
        data->mdb_item_0_array_size = 4;
        data->mdb_item_0_field_size = 5;
        data->mdb_item_1_array_size = 4;
        data->mdb_item_1_field_size = 16;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_mdb_29_info_set(
    int unit)
{
    int mdb_table_id_index;
    dnx_data_mdb_em_mdb_29_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_mdb_29_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = MDB_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = MDB_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "1";
    table->values[2].default_val = "1";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_mdb_29_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_mdb_29_info");

    
    default_data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->dbal_table = 0;
    default_data->mdb_item_0_array_size = 1;
    default_data->mdb_item_1_array_size = 1;
    
    for (mdb_table_id_index = 0; mdb_table_id_index < table->keys[0].size; mdb_table_id_index++)
    {
        data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, mdb_table_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (MDB_PHYSICAL_TABLE_ISEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ISEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_29_ISEM_1;
        data->mdb_item_0_array_size = 4;
        data->mdb_item_1_array_size = 4;
    }
    if (MDB_PHYSICAL_TABLE_ISEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ISEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_29_ISEM_2;
        data->mdb_item_0_array_size = 4;
        data->mdb_item_1_array_size = 4;
    }
    if (MDB_PHYSICAL_TABLE_ISEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ISEM_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_29_ISEM_3;
        data->mdb_item_0_array_size = 5;
        data->mdb_item_1_array_size = 5;
    }
    if (MDB_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_LEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_29_LEM;
        data->mdb_item_0_array_size = 11;
        data->mdb_item_1_array_size = 11;
    }
    if (MDB_PHYSICAL_TABLE_IOEM_0 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_IOEM_0, 0);
        data->dbal_table = DBAL_TABLE_MDB_29_IOEM_0;
        data->mdb_item_0_array_size = 2;
        data->mdb_item_1_array_size = 2;
    }
    if (MDB_PHYSICAL_TABLE_IOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_IOEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_29_IOEM_1;
        data->mdb_item_0_array_size = 2;
        data->mdb_item_1_array_size = 2;
    }
    if (MDB_PHYSICAL_TABLE_EOEM_0 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EOEM_0, 0);
        data->dbal_table = DBAL_TABLE_MDB_29_EOEM_0;
        data->mdb_item_0_array_size = 4;
        data->mdb_item_1_array_size = 4;
    }
    if (MDB_PHYSICAL_TABLE_EOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EOEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_29_EOEM_1;
        data->mdb_item_0_array_size = 4;
        data->mdb_item_1_array_size = 4;
    }
    if (MDB_PHYSICAL_TABLE_MC_ID < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_MC_ID, 0);
        data->dbal_table = DBAL_TABLE_MDB_29_MC_ID;
        data->mdb_item_0_array_size = 2;
        data->mdb_item_1_array_size = 2;
    }
    if (MDB_PHYSICAL_TABLE_GLEM_0 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_GLEM_0, 0);
        data->dbal_table = DBAL_TABLE_MDB_29_GLEM_0;
        data->mdb_item_0_array_size = 7;
        data->mdb_item_1_array_size = 7;
    }
    if (MDB_PHYSICAL_TABLE_GLEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_GLEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_29_GLEM_1;
        data->mdb_item_0_array_size = 7;
        data->mdb_item_1_array_size = 7;
    }
    if (MDB_PHYSICAL_TABLE_ESEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ESEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_29_ESEM;
        data->mdb_item_0_array_size = 5;
        data->mdb_item_1_array_size = 5;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_29_EXEM_1;
        data->mdb_item_0_array_size = 3;
        data->mdb_item_1_array_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_29_EXEM_2;
        data->mdb_item_0_array_size = 3;
        data->mdb_item_1_array_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_29_EXEM_3;
        data->mdb_item_0_array_size = 6;
        data->mdb_item_1_array_size = 6;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_4 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_4, 0);
        data->dbal_table = DBAL_TABLE_MDB_29_EXEM_4;
        data->mdb_item_0_array_size = 3;
        data->mdb_item_1_array_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_RMEP < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_29_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_RMEP, 0);
        data->dbal_table = DBAL_TABLE_MDB_29_RMEP;
        data->mdb_item_0_array_size = 2;
        data->mdb_item_1_array_size = 2;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_mdb_32_info_set(
    int unit)
{
    int dbal_id_index;
    dnx_data_mdb_em_mdb_32_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_mdb_32_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = DBAL_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = DBAL_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_mdb_32_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_mdb_32_info");

    
    default_data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->dbal_table = 0;
    default_data->mdb_item_0_field_size = 0;
    
    for (dbal_id_index = 0; dbal_id_index < table->keys[0].size; dbal_id_index++)
    {
        data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, dbal_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (DBAL_PHYSICAL_TABLE_ISEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_32_ISEM_1;
        data->mdb_item_0_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_32_ISEM_2;
        data->mdb_item_0_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_32_ISEM_3;
        data->mdb_item_0_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_32_LEM;
        data->mdb_item_0_field_size = 11;
    }
    if (DBAL_PHYSICAL_TABLE_IOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_IOEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_32_IOEM_0;
        data->mdb_item_0_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_IOEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_IOEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_32_IOEM_1;
        data->mdb_item_0_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_PPMC < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_PPMC, 0);
        data->dbal_table = DBAL_TABLE_MDB_32_MC_ID;
        data->mdb_item_0_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_GLEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_GLEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_32_GLEM_0;
        data->mdb_item_0_field_size = 9;
    }
    if (DBAL_PHYSICAL_TABLE_GLEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_GLEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_32_GLEM_1;
        data->mdb_item_0_field_size = 9;
    }
    if (DBAL_PHYSICAL_TABLE_EOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_EOEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_32_EOEM_0;
        data->mdb_item_0_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_EOEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_EOEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_32_EOEM_1;
        data->mdb_item_0_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_ESEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ESEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_32_ESEM;
        data->mdb_item_0_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_32_EXEM_1;
        data->mdb_item_0_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_32_EXEM_2;
        data->mdb_item_0_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_32_EXEM_3;
        data->mdb_item_0_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_LEXEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEXEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_32_EXEM_4;
        data->mdb_item_0_field_size = 11;
    }
    if (DBAL_PHYSICAL_TABLE_RMEP_EM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_32_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_RMEP_EM, 0);
        data->dbal_table = DBAL_TABLE_MDB_32_RMEP;
        data->mdb_item_0_field_size = 10;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_mdb_41_info_set(
    int unit)
{
    int dbal_id_index;
    dnx_data_mdb_em_mdb_41_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_mdb_41_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = DBAL_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = DBAL_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "1";
    table->values[2].default_val = "0";
    table->values[3].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_mdb_41_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_mdb_41_info");

    
    default_data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->dbal_table = 0;
    default_data->array_size = 1;
    default_data->mdb_item_2_field_size = 0;
    default_data->mdb_item_3_field_size = 0;
    
    for (dbal_id_index = 0; dbal_id_index < table->keys[0].size; dbal_id_index++)
    {
        data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, dbal_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (DBAL_PHYSICAL_TABLE_ISEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_ISEM_1;
        data->array_size = 10;
        data->mdb_item_2_field_size = 10;
        data->mdb_item_3_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_ISEM_2;
        data->array_size = 10;
        data->mdb_item_2_field_size = 10;
        data->mdb_item_3_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_ISEM_3;
        data->array_size = 10;
        data->mdb_item_2_field_size = 10;
        data->mdb_item_3_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_LEM;
        data->array_size = 11;
        data->mdb_item_2_field_size = 11;
        data->mdb_item_3_field_size = 11;
    }
    if (DBAL_PHYSICAL_TABLE_IOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_IOEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_IOEM_0;
        data->array_size = 10;
        data->mdb_item_2_field_size = 10;
        data->mdb_item_3_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_IOEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_IOEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_IOEM_1;
        data->array_size = 10;
        data->mdb_item_2_field_size = 10;
        data->mdb_item_3_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_PPMC < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_PPMC, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_MC_ID;
        data->array_size = 10;
        data->mdb_item_2_field_size = 10;
        data->mdb_item_3_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_GLEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_GLEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_GLEM_0;
        data->array_size = 9;
        data->mdb_item_2_field_size = 9;
        data->mdb_item_3_field_size = 9;
    }
    if (DBAL_PHYSICAL_TABLE_GLEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_GLEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_GLEM_1;
        data->array_size = 9;
        data->mdb_item_2_field_size = 9;
        data->mdb_item_3_field_size = 9;
    }
    if (DBAL_PHYSICAL_TABLE_EOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_EOEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_EOEM_0;
        data->array_size = 10;
        data->mdb_item_2_field_size = 10;
        data->mdb_item_3_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_EOEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_EOEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_EOEM_1;
        data->array_size = 10;
        data->mdb_item_2_field_size = 10;
        data->mdb_item_3_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_ESEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ESEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_ESEM;
        data->array_size = 10;
        data->mdb_item_2_field_size = 10;
        data->mdb_item_3_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_EXEM_1;
        data->array_size = 10;
        data->mdb_item_2_field_size = 10;
        data->mdb_item_3_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_EXEM_2;
        data->array_size = 10;
        data->mdb_item_2_field_size = 10;
        data->mdb_item_3_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_EXEM_3;
        data->array_size = 10;
        data->mdb_item_2_field_size = 10;
        data->mdb_item_3_field_size = 10;
    }
    if (DBAL_PHYSICAL_TABLE_LEXEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEXEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_EXEM_4;
        data->array_size = 11;
        data->mdb_item_2_field_size = 11;
        data->mdb_item_3_field_size = 11;
    }
    if (DBAL_PHYSICAL_TABLE_RMEP_EM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_41_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_RMEP_EM, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_RMEP;
        data->array_size = 10;
        data->mdb_item_2_field_size = 10;
        data->mdb_item_3_field_size = 10;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_mdb_emp_tables_mapping_set(
    int unit)
{
    int mdb_table_index;
    dnx_data_mdb_em_mdb_emp_tables_mapping_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_mdb_emp_tables_mapping;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = MDB_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = MDB_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_mdb_emp_tables_mapping_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_mdb_emp_tables_mapping");

    
    default_data = (dnx_data_mdb_em_mdb_emp_tables_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->emp_age_cfg_table = 0;
    default_data->mdb_22_table = 0;
    
    for (mdb_table_index = 0; mdb_table_index < table->keys[0].size; mdb_table_index++)
    {
        data = (dnx_data_mdb_em_mdb_emp_tables_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, mdb_table_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (MDB_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_emp_tables_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_LEM, 0);
        data->emp_age_cfg_table = DBAL_TABLE_MDB_20_LEM;
        data->mdb_22_table = DBAL_TABLE_MDB_22_LEM;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_emp_tables_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_3, 0);
        data->emp_age_cfg_table = DBAL_TABLE_MDB_20_EXEM_3;
        data->mdb_22_table = DBAL_TABLE_MDB_22_EXEM_3;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_4 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_emp_tables_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_4, 0);
        data->emp_age_cfg_table = DBAL_TABLE_MDB_20_EXEM_4;
        data->mdb_22_table = DBAL_TABLE_MDB_22_EXEM_4;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_mdb_em_shift_vmv_regs_set(
    int unit)
{
    int dbal_id_index;
    dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_mdb_em_shift_vmv_regs;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = DBAL_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = DBAL_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "DBAL_TABLE_EMPTY";
    table->values[2].default_val = "DBAL_FIELD_EMPTY";
    table->values[3].default_val = "DBAL_FIELD_EMPTY";
    table->values[4].default_val = "0";
    table->values[5].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_mdb_em_shift_vmv_regs_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_mdb_em_shift_vmv_regs");

    
    default_data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->nof_valid_regs = 0;
    default_data->table_name_arr[0] = DBAL_TABLE_EMPTY;
    default_data->field_name_arr[0] = DBAL_FIELD_EMPTY;
    default_data->key_name_arr[0] = DBAL_FIELD_EMPTY;
    default_data->stage_index_arr[0] = 0;
    default_data->esem_cmd_indication[0] = 0;
    
    for (dbal_id_index = 0; dbal_id_index < table->keys[0].size; dbal_id_index++)
    {
        data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, dbal_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (DBAL_PHYSICAL_TABLE_ISEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_1, 0);
        data->nof_valid_regs = 2;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_name_arr[0] = DBAL_TABLE_MDB_VTT_ST_ONE_LE_VMV_SHIFT;
        data->table_name_arr[1] = DBAL_TABLE_MDB_VTT_ST_ONE_LE_VMV_SHIFT;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->field_name_arr[0] = DBAL_FIELD_VTT_ST_ONE_LE_VMV_SHIFT_VALUE_MAP;
        data->field_name_arr[1] = DBAL_FIELD_VTT_ST_ONE_LE_VMV_SHIFT_VALUE_MAP;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_name_arr[0] = DBAL_FIELD_STAGE_INDEX;
        data->key_name_arr[1] = DBAL_FIELD_STAGE_INDEX;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->stage_index_arr[0] = 1;
        data->stage_index_arr[1] = 2;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_2, 0);
        data->nof_valid_regs = 4;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_name_arr[0] = DBAL_TABLE_MDB_VTT_ST_TWO_LE_VMV_SHIFT;
        data->table_name_arr[1] = DBAL_TABLE_MDB_VTT_ST_TWO_LE_VMV_SHIFT;
        data->table_name_arr[2] = DBAL_TABLE_MDB_VTT_ST_TH_LE_VMV_SHIFT;
        data->table_name_arr[3] = DBAL_TABLE_MDB_VTT_ST_TH_LE_VMV_SHIFT;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->field_name_arr[0] = DBAL_FIELD_VTT_ST_TWO_LE_VMV_SHIFT_VALUE_MAP;
        data->field_name_arr[1] = DBAL_FIELD_VTT_ST_TWO_LE_VMV_SHIFT_VALUE_MAP;
        data->field_name_arr[2] = DBAL_FIELD_VTT_ST_TH_LE_VMV_SHIFT_VALUE_MAP;
        data->field_name_arr[3] = DBAL_FIELD_VTT_ST_TH_LE_VMV_SHIFT_VALUE_MAP;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_name_arr[0] = DBAL_FIELD_STAGE_INDEX;
        data->key_name_arr[1] = DBAL_FIELD_STAGE_INDEX;
        data->key_name_arr[2] = DBAL_FIELD_STAGE_INDEX;
        data->key_name_arr[3] = DBAL_FIELD_STAGE_INDEX;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->stage_index_arr[0] = 1;
        data->stage_index_arr[1] = 2;
        data->stage_index_arr[2] = 1;
        data->stage_index_arr[3] = 2;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_3, 0);
        data->nof_valid_regs = 0;
    }
    if (DBAL_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEM, 0);
        data->nof_valid_regs = 2;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_name_arr[0] = DBAL_TABLE_MDB_FLPLE_VMV_SHIFT;
        data->table_name_arr[1] = DBAL_TABLE_MDB_VMV_SHIFT_EXTRA_REGS;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->field_name_arr[0] = DBAL_FIELD_FLPLE_VMV_SHIFT_VALUE;
        data->field_name_arr[1] = DBAL_FIELD_IPPB_LEL_VMV_SHIFT_VALUE_MAP;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_name_arr[0] = DBAL_FIELD_STAGE_INDEX;
        data->key_name_arr[1] = DBAL_FIELD_EMPTY;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->stage_index_arr[0] = 0;
        data->stage_index_arr[1] = 0;
    }
    if (DBAL_PHYSICAL_TABLE_IOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_IOEM_1, 0);
        data->nof_valid_regs = 1;
        data->table_name_arr[0] = DBAL_TABLE_MDB_VMV_SHIFT;
        data->field_name_arr[0] = DBAL_FIELD_IPPB_OAM_VMV_SHIFT_VALUE;
        data->key_name_arr[0] = DBAL_FIELD_EMPTY;
    }
    if (DBAL_PHYSICAL_TABLE_IOEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_IOEM_2, 0);
        data->nof_valid_regs = 0;
    }
    if (DBAL_PHYSICAL_TABLE_EOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_EOEM_1, 0);
        data->nof_valid_regs = 1;
        data->table_name_arr[0] = DBAL_TABLE_MDB_VMV_SHIFT;
        data->field_name_arr[0] = DBAL_FIELD_ETPPC_OAM_VMV_SHIFT_VALUE;
        data->key_name_arr[0] = DBAL_FIELD_EMPTY;
    }
    if (DBAL_PHYSICAL_TABLE_EOEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_EOEM_2, 0);
        data->nof_valid_regs = 0;
    }
    if (DBAL_PHYSICAL_TABLE_PPMC < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_PPMC, 0);
        data->nof_valid_regs = 0;
    }
    if (DBAL_PHYSICAL_TABLE_GLEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_GLEM_1, 0);
        data->nof_valid_regs = 0;
    }
    if (DBAL_PHYSICAL_TABLE_GLEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_GLEM_2, 0);
        data->nof_valid_regs = 0;
    }
    if (DBAL_PHYSICAL_TABLE_ESEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ESEM, 0);
        data->nof_valid_regs = 2;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_name_arr[0] = DBAL_TABLE_MDB_VMV_SHIFT;
        data->table_name_arr[1] = DBAL_TABLE_MDB_VMV_SHIFT;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->field_name_arr[0] = DBAL_FIELD_ESEM_1_SHIFT_VAL;
        data->field_name_arr[1] = DBAL_FIELD_ESEM_2_SHIFT_VAL;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_name_arr[0] = DBAL_FIELD_EMPTY;
        data->key_name_arr[1] = DBAL_FIELD_EMPTY;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->stage_index_arr[0] = 0;
        data->stage_index_arr[1] = 0;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->esem_cmd_indication[0] = 1;
        data->esem_cmd_indication[1] = 1;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_1, 0);
        data->nof_valid_regs = 2;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_name_arr[0] = DBAL_TABLE_MDB_VTT_ST_ONE_LE_VMV_SHIFT;
        data->table_name_arr[1] = DBAL_TABLE_MDB_VTT_ST_TWO_LE_VMV_SHIFT;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->field_name_arr[0] = DBAL_FIELD_VTT_ST_ONE_LE_VMV_SHIFT_VALUE_MAP;
        data->field_name_arr[1] = DBAL_FIELD_VTT_ST_TWO_LE_VMV_SHIFT_VALUE_MAP;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_name_arr[0] = DBAL_FIELD_STAGE_INDEX;
        data->key_name_arr[1] = DBAL_FIELD_STAGE_INDEX;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->stage_index_arr[0] = 0;
        data->stage_index_arr[1] = 0;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_2, 0);
        data->nof_valid_regs = 2;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_name_arr[0] = DBAL_TABLE_MDB_FLPLE_VMV_SHIFT;
        data->table_name_arr[1] = DBAL_TABLE_MDB_VMV_SHIFT;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->field_name_arr[0] = DBAL_FIELD_FLPLE_VMV_SHIFT_VALUE;
        data->field_name_arr[1] = DBAL_FIELD_ESEM_3_SHIFT_VAL;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_name_arr[0] = DBAL_FIELD_STAGE_INDEX;
        data->key_name_arr[1] = DBAL_FIELD_EMPTY;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->stage_index_arr[0] = 2;
        data->stage_index_arr[1] = 0;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->esem_cmd_indication[0] = 0;
        data->esem_cmd_indication[1] = 1;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_3, 0);
        data->nof_valid_regs = 4;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_name_arr[0] = DBAL_TABLE_MDB_FLPLE_VMV_SHIFT;
        data->table_name_arr[1] = DBAL_TABLE_MDB_VTT_ST_TH_LE_VMV_SHIFT;
        data->table_name_arr[2] = DBAL_TABLE_MDB_VMV_SHIFT_EXTRA_REGS_WITH_STAGE;
        data->table_name_arr[3] = DBAL_TABLE_MDB_VMV_SHIFT_EXTRA_REGS;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->field_name_arr[0] = DBAL_FIELD_FLPLE_VMV_SHIFT_VALUE;
        data->field_name_arr[1] = DBAL_FIELD_VTT_ST_TH_LE_VMV_SHIFT_VALUE_MAP;
        data->field_name_arr[2] = DBAL_FIELD_IPPC_VMV_SHIFT_VALUE_MAP;
        data->field_name_arr[3] = DBAL_FIELD_IPPD_VMV_SHIFT_VALUE_MAP;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_name_arr[0] = DBAL_FIELD_STAGE_INDEX;
        data->key_name_arr[1] = DBAL_FIELD_STAGE_INDEX;
        data->key_name_arr[2] = DBAL_FIELD_STAGE_INDEX;
        data->key_name_arr[3] = DBAL_FIELD_EMPTY;
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->stage_index_arr[0] = 1;
        data->stage_index_arr[1] = 0;
        data->stage_index_arr[2] = 1;
        data->stage_index_arr[3] = 0;
    }
    if (DBAL_PHYSICAL_TABLE_LEXEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEXEM, 0);
        data->nof_valid_regs = 2;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->table_name_arr[0] = DBAL_TABLE_MDB_VMV_SHIFT_EXTRA_REGS;
        data->table_name_arr[1] = DBAL_TABLE_MDB_VMV_SHIFT_EXTRA_REGS_WITH_STAGE;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->field_name_arr[0] = DBAL_FIELD_ERPP_VMV_SHIFT_VALUE_MAP;
        data->field_name_arr[1] = DBAL_FIELD_IPPC_VMV_SHIFT_VALUE_MAP;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->key_name_arr[0] = DBAL_FIELD_EMPTY;
        data->key_name_arr[1] = DBAL_FIELD_STAGE_INDEX;
        SHR_RANGE_VERIFY(2, 0, DNX_DATA_MAX_MDB_EM_SHIFT_VMV_MAX_REGS_PER_TABLE, _SHR_E_INTERNAL, "out of bound access to array")
        data->stage_index_arr[0] = 0;
        data->stage_index_arr[1] = 0;
    }
    if (DBAL_PHYSICAL_TABLE_RMEP_EM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_shift_vmv_regs_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_RMEP_EM, 0);
        data->nof_valid_regs = 0;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_em_emp_set(
    int unit)
{
    int dbal_id_index;
    dnx_data_mdb_em_em_emp_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_em_emp;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = DBAL_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = DBAL_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "INVALIDm";
    table->values[1].default_val = "INVALIDm";
    table->values[2].default_val = "INVALIDf";
    table->values[3].default_val = "INVALIDr";
    table->values[4].default_val = "INVALIDf";
    table->values[5].default_val = "INVALIDf";
    table->values[6].default_val = "INVALIDf";
    table->values[7].default_val = "INVALIDf";
    table->values[8].default_val = "INVALIDf";
    table->values[9].default_val = "INVALIDf";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_em_emp_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_em_emp");

    
    default_data = (dnx_data_mdb_em_em_emp_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->age_mem = INVALIDm;
    default_data->age_ovf_cam_mem = INVALIDm;
    default_data->emp_scan_status_field = INVALIDf;
    default_data->emp_age_cfg_reg = INVALIDr;
    default_data->global_value = INVALIDf;
    default_data->global_masks = INVALIDf;
    default_data->external_profile = INVALIDf;
    default_data->age_disable = INVALIDf;
    default_data->elephant_disable = INVALIDf;
    default_data->initial_values = INVALIDf;
    
    for (dbal_id_index = 0; dbal_id_index < table->keys[0].size; dbal_id_index++)
    {
        data = (dnx_data_mdb_em_em_emp_t *) dnxc_data_mgmt_table_data_get(unit, table, dbal_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (DBAL_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_emp_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEM, 0);
        data->age_mem = MDB_MEM_0200000m;
        data->age_ovf_cam_mem = MDB_MEM_21000m;
        data->emp_scan_status_field = ITEM_37_38f;
        data->emp_age_cfg_reg = MDB_REG_182r;
        data->global_value = ITEM_0_63f;
        data->global_masks = ITEM_64_127f;
        data->external_profile = ITEM_128_135f;
        data->age_disable = ITEM_136_143f;
        data->elephant_disable = ITEM_144_151f;
        data->initial_values = ITEM_152_279f;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_emp_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_3, 0);
        data->age_mem = MDB_MEM_210000m;
        data->age_ovf_cam_mem = MDB_MEM_80000m;
        data->emp_scan_status_field = ITEM_37_38f;
        data->emp_age_cfg_reg = MDB_REG_461r;
        data->global_value = ITEM_0_63f;
        data->global_masks = ITEM_64_127f;
        data->external_profile = ITEM_128_135f;
        data->age_disable = ITEM_136_143f;
        data->elephant_disable = ITEM_144_151f;
        data->initial_values = ITEM_152_407f;
    }
    if (DBAL_PHYSICAL_TABLE_LEXEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_em_emp_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEXEM, 0);
        data->age_mem = MDB_MEM_220000m;
        data->age_ovf_cam_mem = MDB_MEM_89000m;
        data->emp_scan_status_field = ITEM_37_38f;
        data->emp_age_cfg_reg = MDB_REG_514r;
        data->global_value = ITEM_0_63f;
        data->global_masks = ITEM_64_127f;
        data->external_profile = ITEM_128_135f;
        data->age_disable = ITEM_136_143f;
        data->elephant_disable = ITEM_144_151f;
        data->initial_values = ITEM_152_407f;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_mdb_step_table_map_set(
    int unit)
{
    int mdb_table_index;
    dnx_data_mdb_em_mdb_step_table_map_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_mdb_step_table_map;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = DBAL_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = DBAL_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_mdb_step_table_map_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_mdb_step_table_map");

    
    default_data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->dbal_table = 0;
    
    for (mdb_table_index = 0; mdb_table_index < table->keys[0].size; mdb_table_index++)
    {
        data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, mdb_table_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (DBAL_PHYSICAL_TABLE_ISEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_ISEM_1;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_ISEM_2;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_ISEM_3;
    }
    if (DBAL_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_LEM;
    }
    if (DBAL_PHYSICAL_TABLE_IOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_IOEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_IOEM_0;
    }
    if (DBAL_PHYSICAL_TABLE_IOEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_IOEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_IOEM_1;
    }
    if (DBAL_PHYSICAL_TABLE_PPMC < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_PPMC, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_MC_ID;
    }
    if (DBAL_PHYSICAL_TABLE_GLEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_GLEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_GLEM_0;
    }
    if (DBAL_PHYSICAL_TABLE_GLEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_GLEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_GLEM_1;
    }
    if (DBAL_PHYSICAL_TABLE_EOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_EOEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_EOEM_0;
    }
    if (DBAL_PHYSICAL_TABLE_EOEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_EOEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_EOEM_1;
    }
    if (DBAL_PHYSICAL_TABLE_ESEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ESEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_ESEM;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_EXEM_1;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_EXEM_2;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_EXEM_3;
    }
    if (DBAL_PHYSICAL_TABLE_LEXEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEXEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_EXEM_4;
    }
    if (DBAL_PHYSICAL_TABLE_RMEP_EM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_step_table_map_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_RMEP_EM, 0);
        data->dbal_table = DBAL_TABLE_MDB_41_RMEP;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_set(
    int unit)
{
    int dbal_id_index;
    dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_mdb_em_dbal_phy_tables_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = DBAL_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = DBAL_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "DBAL_TABLE_EMPTY";
    table->values[1].default_val = "DBAL_TABLE_EMPTY";
    table->values[2].default_val = "DBAL_TABLE_EMPTY";
    table->values[3].default_val = "DBAL_TABLE_EMPTY";
    table->values[4].default_val = "DBAL_TABLE_EMPTY";
    table->values[5].default_val = "DBAL_TABLE_EMPTY";
    table->values[6].default_val = "DBAL_TABLE_EMPTY";
    table->values[7].default_val = "DBAL_TABLE_EMPTY";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_mdb_em_dbal_phy_tables_info");

    
    default_data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->mdb_13_table = DBAL_TABLE_EMPTY;
    default_data->mdb_14_table = DBAL_TABLE_EMPTY;
    default_data->mdb_17_table = DBAL_TABLE_EMPTY;
    default_data->mdb_18_table = DBAL_TABLE_EMPTY;
    default_data->mdb_33_table = DBAL_TABLE_EMPTY;
    default_data->mdb_34_table = DBAL_TABLE_EMPTY;
    default_data->mdb_46_table = DBAL_TABLE_EMPTY;
    default_data->mdb_52_table = DBAL_TABLE_EMPTY;
    
    for (dbal_id_index = 0; dbal_id_index < table->keys[0].size; dbal_id_index++)
    {
        data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, dbal_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (DBAL_PHYSICAL_TABLE_ISEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_1, 0);
        data->mdb_13_table = DBAL_TABLE_MDB_13_ISEM_1;
        data->mdb_14_table = DBAL_TABLE_MDB_14_ISEM_1;
        data->mdb_17_table = DBAL_TABLE_MDB_17_ISEM_1;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_2, 0);
        data->mdb_13_table = DBAL_TABLE_MDB_13_ISEM_2;
        data->mdb_14_table = DBAL_TABLE_MDB_14_ISEM_2;
        data->mdb_17_table = DBAL_TABLE_MDB_17_ISEM_2;
    }
    if (DBAL_PHYSICAL_TABLE_ISEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ISEM_3, 0);
        data->mdb_13_table = DBAL_TABLE_MDB_13_ISEM_3;
        data->mdb_14_table = DBAL_TABLE_MDB_14_ISEM_3;
        data->mdb_17_table = DBAL_TABLE_MDB_17_ISEM_3;
    }
    if (DBAL_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEM, 0);
        data->mdb_13_table = DBAL_TABLE_MDB_13_LEM;
        data->mdb_14_table = DBAL_TABLE_MDB_14_LEM;
        data->mdb_17_table = DBAL_TABLE_MDB_17_LEM;
        data->mdb_18_table = DBAL_TABLE_MDB_18_LEM;
        data->mdb_33_table = DBAL_TABLE_MDB_33_LEM;
        data->mdb_34_table = DBAL_TABLE_MDB_34_LEM;
        data->mdb_46_table = DBAL_TABLE_MDB_46_LEM;
    }
    if (DBAL_PHYSICAL_TABLE_IOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_IOEM_1, 0);
        data->mdb_13_table = DBAL_TABLE_MDB_13_IOEM_0;
        data->mdb_14_table = DBAL_TABLE_MDB_14_IOEM_0;
        data->mdb_17_table = DBAL_TABLE_MDB_17_IOEM_0;
    }
    if (DBAL_PHYSICAL_TABLE_IOEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_IOEM_2, 0);
        data->mdb_13_table = DBAL_TABLE_MDB_13_IOEM_1;
        data->mdb_14_table = DBAL_TABLE_MDB_14_IOEM_1;
        data->mdb_17_table = DBAL_TABLE_MDB_17_IOEM_1;
    }
    if (DBAL_PHYSICAL_TABLE_PPMC < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_PPMC, 0);
        data->mdb_13_table = DBAL_TABLE_MDB_13_MC_ID;
        data->mdb_14_table = DBAL_TABLE_MDB_14_MC_ID;
        data->mdb_17_table = DBAL_TABLE_MDB_17_MC_ID;
    }
    if (DBAL_PHYSICAL_TABLE_GLEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_GLEM_1, 0);
        data->mdb_13_table = DBAL_TABLE_MDB_13_GLEM_0;
        data->mdb_14_table = DBAL_TABLE_MDB_14_GLEM_0;
        data->mdb_17_table = DBAL_TABLE_MDB_17_GLEM_0;
    }
    if (DBAL_PHYSICAL_TABLE_GLEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_GLEM_2, 0);
        data->mdb_13_table = DBAL_TABLE_MDB_13_GLEM_1;
        data->mdb_14_table = DBAL_TABLE_MDB_14_GLEM_1;
        data->mdb_17_table = DBAL_TABLE_MDB_17_GLEM_1;
    }
    if (DBAL_PHYSICAL_TABLE_EOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_EOEM_1, 0);
        data->mdb_13_table = DBAL_TABLE_MDB_13_EOEM_0;
        data->mdb_14_table = DBAL_TABLE_MDB_14_EOEM_0;
        data->mdb_17_table = DBAL_TABLE_MDB_17_EOEM_0;
    }
    if (DBAL_PHYSICAL_TABLE_EOEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_EOEM_2, 0);
        data->mdb_13_table = DBAL_TABLE_MDB_13_EOEM_1;
        data->mdb_14_table = DBAL_TABLE_MDB_14_EOEM_1;
        data->mdb_17_table = DBAL_TABLE_MDB_17_EOEM_1;
    }
    if (DBAL_PHYSICAL_TABLE_ESEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_ESEM, 0);
        data->mdb_13_table = DBAL_TABLE_MDB_13_ESEM;
        data->mdb_14_table = DBAL_TABLE_MDB_14_ESEM;
        data->mdb_17_table = DBAL_TABLE_MDB_17_ESEM;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_1, 0);
        data->mdb_13_table = DBAL_TABLE_MDB_13_EXEM_1;
        data->mdb_14_table = DBAL_TABLE_MDB_14_EXEM_1;
        data->mdb_17_table = DBAL_TABLE_MDB_17_EXEM_1;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_2, 0);
        data->mdb_13_table = DBAL_TABLE_MDB_13_EXEM_2;
        data->mdb_14_table = DBAL_TABLE_MDB_14_EXEM_2;
        data->mdb_17_table = DBAL_TABLE_MDB_17_EXEM_2;
    }
    if (DBAL_PHYSICAL_TABLE_SEXEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_SEXEM_3, 0);
        data->mdb_13_table = DBAL_TABLE_MDB_13_EXEM_3;
        data->mdb_14_table = DBAL_TABLE_MDB_14_EXEM_3;
        data->mdb_17_table = DBAL_TABLE_MDB_17_EXEM_3;
        data->mdb_18_table = DBAL_TABLE_MDB_18_EXEM_3;
        data->mdb_33_table = DBAL_TABLE_MDB_33_EXEM_3;
        data->mdb_34_table = DBAL_TABLE_MDB_34_EXEM_3;
        data->mdb_46_table = DBAL_TABLE_MDB_46_EXEM_3;
    }
    if (DBAL_PHYSICAL_TABLE_LEXEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEXEM, 0);
        data->mdb_13_table = DBAL_TABLE_MDB_13_EXEM_4;
        data->mdb_14_table = DBAL_TABLE_MDB_14_EXEM_4;
        data->mdb_17_table = DBAL_TABLE_MDB_17_EXEM_4;
        data->mdb_18_table = DBAL_TABLE_MDB_18_EXEM_4;
        data->mdb_33_table = DBAL_TABLE_MDB_33_EXEM_4;
        data->mdb_34_table = DBAL_TABLE_MDB_34_EXEM_4;
        data->mdb_46_table = DBAL_TABLE_MDB_46_EXEM_4;
    }
    if (DBAL_PHYSICAL_TABLE_RMEP_EM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_RMEP_EM, 0);
        data->mdb_13_table = DBAL_TABLE_MDB_13_RMEP;
        data->mdb_14_table = DBAL_TABLE_MDB_14_RMEP;
        data->mdb_17_table = DBAL_TABLE_MDB_17_RMEP;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_filter_rules_set(
    int unit)
{
    int dbal_id_index;
    dnx_data_mdb_em_filter_rules_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_filter_rules;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = DBAL_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = DBAL_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "0";
    table->values[2].default_val = "0";
    table->values[3].default_val = "0";
    table->values[4].default_val = "0";
    table->values[5].default_val = "0";
    table->values[6].default_val = "0";
    table->values[7].default_val = "0";
    table->values[8].default_val = "0";
    table->values[9].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_filter_rules_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_filter_rules");

    
    default_data = (dnx_data_mdb_em_filter_rules_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->table_name = 0;
    default_data->valid = 0;
    default_data->entry_mask = 0;
    default_data->entry_filter = 0;
    default_data->src_mask = 0;
    default_data->src_filter = 0;
    default_data->appdb_id_mask = 0;
    default_data->appdb_id_filter = 0;
    default_data->accessed_mask = 0;
    default_data->accessed_filter = 0;
    
    for (dbal_id_index = 0; dbal_id_index < table->keys[0].size; dbal_id_index++)
    {
        data = (dnx_data_mdb_em_filter_rules_t *) dnxc_data_mgmt_table_data_get(unit, table, dbal_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (DBAL_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_filter_rules_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEM, 0);
        data->table_name = MDB_MEM_19000m;
        data->valid = ITEM_0_0f;
        data->entry_mask = ITEM_8_264f;
        data->entry_filter = ITEM_275_531f;
        data->src_mask = ITEM_265_267f;
        data->src_filter = ITEM_532_534f;
        data->appdb_id_mask = ITEM_2_7f;
        data->appdb_id_filter = ITEM_269_274f;
        data->accessed_mask = ITEM_1_1f;
        data->accessed_filter = ITEM_268_268f;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_em_data_rules_set(
    int unit)
{
    int dbal_id_index;
    dnx_data_mdb_em_data_rules_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_em;
    int table_index = dnx_data_mdb_em_table_data_rules;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = DBAL_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = DBAL_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "0";
    table->values[2].default_val = "0";
    table->values[3].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_em_data_rules_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_em_table_data_rules");

    
    default_data = (dnx_data_mdb_em_data_rules_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->table_name = 0;
    default_data->command = 0;
    default_data->payload_mask = 0;
    default_data->payload = 0;
    
    for (dbal_id_index = 0; dbal_id_index < table->keys[0].size; dbal_id_index++)
    {
        data = (dnx_data_mdb_em_data_rules_t *) dnxc_data_mgmt_table_data_get(unit, table, dbal_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (DBAL_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_em_data_rules_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_PHYSICAL_TABLE_LEM, 0);
        data->table_name = MDB_MEM_20000m;
        data->command = ITEM_0_3f;
        data->payload_mask = ITEM_4_99f;
        data->payload = ITEM_100_195f;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}





static shr_error_e
j2x_a0_dnx_data_mdb_direct_fec_abk_mapping_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_direct;
    int feature_index = dnx_data_mdb_direct_fec_abk_mapping;
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
j2x_a0_dnx_data_mdb_direct_physical_address_ovf_enable_val_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_direct;
    int define_index = dnx_data_mdb_direct_define_physical_address_ovf_enable_val;
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
j2x_a0_dnx_data_mdb_direct_mdb_11_info_set(
    int unit)
{
    int mdb_table_id_index;
    dnx_data_mdb_direct_mdb_11_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_direct;
    int table_index = dnx_data_mdb_direct_table_mdb_11_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = MDB_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = MDB_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "1";
    table->values[2].default_val = "0";
    table->values[3].default_val = "0";
    table->values[4].default_val = "1";
    table->values[5].default_val = "0";
    table->values[6].default_val = "1";
    table->values[7].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_direct_mdb_11_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_direct_table_mdb_11_info");

    
    default_data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->dbal_table = 0;
    default_data->mdb_item_0_array_size = 1;
    default_data->mdb_item_0_field_size = 0;
    default_data->mdb_item_1_field_size = 0;
    default_data->mdb_item_3_array_size = 1;
    default_data->mdb_item_3_field_size = 0;
    default_data->mdb_item_4_array_size = 1;
    default_data->mdb_item_4_field_size = 0;
    
    for (mdb_table_id_index = 0; mdb_table_id_index < table->keys[0].size; mdb_table_id_index++)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, mdb_table_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (MDB_PHYSICAL_TABLE_INLIF_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_INLIF_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_INLIF_1;
        data->mdb_item_0_array_size = 16;
        data->mdb_item_0_field_size = 1;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 1;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 1;
        data->mdb_item_4_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_INLIF_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_INLIF_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_INLIF_2;
        data->mdb_item_0_array_size = 16;
        data->mdb_item_0_field_size = 2;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 1;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 1;
        data->mdb_item_4_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_INLIF_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_INLIF_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_INLIF_3;
        data->mdb_item_0_array_size = 16;
        data->mdb_item_0_field_size = 2;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 1;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 1;
        data->mdb_item_4_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_IVSI < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_IVSI, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_IVSI;
        data->mdb_item_0_array_size = 16;
        data->mdb_item_0_field_size = 2;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 1;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 1;
        data->mdb_item_4_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_ADS_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ADS_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_ADS_1;
        data->mdb_item_0_array_size = 8;
        data->mdb_item_0_field_size = 2;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 1;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 1;
        data->mdb_item_4_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_ADS_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ADS_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_ADS_2;
        data->mdb_item_0_array_size = 8;
        data->mdb_item_0_field_size = 1;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 1;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 1;
        data->mdb_item_4_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_MAP < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_MAP, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_MAP;
        data->mdb_item_0_array_size = 16;
        data->mdb_item_0_field_size = 2;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 1;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 1;
        data->mdb_item_4_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_FEC_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_FEC_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_FEC_1;
        data->mdb_item_0_array_size = 32;
        data->mdb_item_0_field_size = 3;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 1;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 1;
        data->mdb_item_4_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_FEC_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_FEC_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_FEC_2;
        data->mdb_item_0_array_size = 32;
        data->mdb_item_0_field_size = 3;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 1;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 1;
        data->mdb_item_4_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_FEC_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_FEC_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_FEC_3;
        data->mdb_item_0_array_size = 32;
        data->mdb_item_0_field_size = 1;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 1;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 1;
        data->mdb_item_4_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_1_LL < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_1_LL, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_EEDB_1_LL;
        data->mdb_item_0_array_size = 64;
        data->mdb_item_0_field_size = 1;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 1;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 1;
        data->mdb_item_4_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_1_2_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_1_2_DATA, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_EEDB_1_2_DATA;
        data->mdb_item_0_array_size = 128;
        data->mdb_item_0_field_size = 3;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 2;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 2;
        data->mdb_item_4_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_3_LL < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_3_LL, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_EEDB_3_LL;
        data->mdb_item_0_array_size = 64;
        data->mdb_item_0_field_size = 1;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 1;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 1;
        data->mdb_item_4_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_3_4_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_3_4_DATA, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_EEDB_3_4_DATA;
        data->mdb_item_0_array_size = 128;
        data->mdb_item_0_field_size = 3;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 2;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 2;
        data->mdb_item_4_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_5_LL < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_5_LL, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_EEDB_5_LL;
        data->mdb_item_0_array_size = 64;
        data->mdb_item_0_field_size = 1;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 1;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 1;
        data->mdb_item_4_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_5_6_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_5_6_DATA, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_EEDB_5_6_DATA;
        data->mdb_item_0_array_size = 128;
        data->mdb_item_0_field_size = 3;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 2;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 2;
        data->mdb_item_4_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_7_LL < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_7_LL, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_EEDB_7_LL;
        data->mdb_item_0_array_size = 64;
        data->mdb_item_0_field_size = 1;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 1;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 1;
        data->mdb_item_4_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_7_8_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_7_8_DATA, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_EEDB_7_8_DATA;
        data->mdb_item_0_array_size = 128;
        data->mdb_item_0_field_size = 2;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 2;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 2;
        data->mdb_item_4_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_EVSI < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_11_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EVSI, 0);
        data->dbal_table = DBAL_TABLE_MDB_11_EVSI;
        data->mdb_item_0_array_size = 16;
        data->mdb_item_0_field_size = 1;
        data->mdb_item_1_field_size = 3;
        data->mdb_item_3_array_size = 1;
        data->mdb_item_3_field_size = 3;
        data->mdb_item_4_array_size = 1;
        data->mdb_item_4_field_size = 3;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_direct_mdb_26_info_set(
    int unit)
{
    int mdb_table_id_index;
    dnx_data_mdb_direct_mdb_26_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_direct;
    int table_index = dnx_data_mdb_direct_table_mdb_26_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = MDB_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = MDB_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "0";
    table->values[2].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_direct_mdb_26_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_direct_table_mdb_26_info");

    
    default_data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->dbal_table = 0;
    default_data->mdb_item_0_field_size = 0;
    default_data->mdb_item_1_field_size = 0;
    
    for (mdb_table_id_index = 0; mdb_table_id_index < table->keys[0].size; mdb_table_id_index++)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, mdb_table_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (MDB_PHYSICAL_TABLE_ISEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ISEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_ISEM_1;
        data->mdb_item_0_field_size = 4;
        data->mdb_item_1_field_size = 4;
    }
    if (MDB_PHYSICAL_TABLE_ISEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ISEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_ISEM_2;
        data->mdb_item_0_field_size = 4;
        data->mdb_item_1_field_size = 4;
    }
    if (MDB_PHYSICAL_TABLE_ISEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ISEM_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_ISEM_3;
        data->mdb_item_0_field_size = 5;
        data->mdb_item_1_field_size = 5;
    }
    if (MDB_PHYSICAL_TABLE_INLIF_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_INLIF_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_INLIF_1;
        data->mdb_item_0_field_size = 2;
        data->mdb_item_1_field_size = 2;
    }
    if (MDB_PHYSICAL_TABLE_INLIF_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_INLIF_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_INLIF_2;
        data->mdb_item_0_field_size = 4;
        data->mdb_item_1_field_size = 4;
    }
    if (MDB_PHYSICAL_TABLE_INLIF_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_INLIF_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_INLIF_3;
        data->mdb_item_0_field_size = 4;
        data->mdb_item_1_field_size = 4;
    }
    if (MDB_PHYSICAL_TABLE_IVSI < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_IVSI, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_IVSI;
        data->mdb_item_0_field_size = 3;
        data->mdb_item_1_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_LEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_LEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_LEM;
        data->mdb_item_0_field_size = 11;
        data->mdb_item_1_field_size = 11;
    }
    if (MDB_PHYSICAL_TABLE_ADS_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ADS_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_ADS_1;
        data->mdb_item_0_field_size = 3;
        data->mdb_item_1_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_ADS_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ADS_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_ADS_2;
        data->mdb_item_0_field_size = 2;
        data->mdb_item_1_field_size = 2;
    }
    if (MDB_PHYSICAL_TABLE_BIG_KAPS_BB_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_BIG_KAPS_BB_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_KAPS_1;
        data->mdb_item_0_field_size = 12;
        data->mdb_item_1_field_size = 12;
    }
    if (MDB_PHYSICAL_TABLE_BIG_KAPS_BB_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_BIG_KAPS_BB_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_KAPS_2;
        data->mdb_item_0_field_size = 6;
        data->mdb_item_1_field_size = 6;
    }
    if (MDB_PHYSICAL_TABLE_IOEM_0 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_IOEM_0, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_IOEM_0;
        data->mdb_item_0_field_size = 2;
        data->mdb_item_1_field_size = 2;
    }
    if (MDB_PHYSICAL_TABLE_IOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_IOEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_IOEM_1;
        data->mdb_item_0_field_size = 2;
        data->mdb_item_1_field_size = 2;
    }
    if (MDB_PHYSICAL_TABLE_EOEM_0 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EOEM_0, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_EOEM_0;
        data->mdb_item_0_field_size = 4;
        data->mdb_item_1_field_size = 4;
    }
    if (MDB_PHYSICAL_TABLE_EOEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EOEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_EOEM_1;
        data->mdb_item_0_field_size = 4;
        data->mdb_item_1_field_size = 4;
    }
    if (MDB_PHYSICAL_TABLE_MAP < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_MAP, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_MAP;
        data->mdb_item_0_field_size = 3;
        data->mdb_item_1_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_FEC_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_FEC_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_FEC_1;
        data->mdb_item_0_field_size = 7;
        data->mdb_item_1_field_size = 7;
    }
    if (MDB_PHYSICAL_TABLE_FEC_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_FEC_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_FEC_2;
        data->mdb_item_0_field_size = 6;
        data->mdb_item_1_field_size = 6;
    }
    if (MDB_PHYSICAL_TABLE_FEC_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_FEC_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_FEC_3;
        data->mdb_item_0_field_size = 2;
        data->mdb_item_1_field_size = 2;
    }
    if (MDB_PHYSICAL_TABLE_MC_ID < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_MC_ID, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_MC_ID;
        data->mdb_item_0_field_size = 2;
        data->mdb_item_1_field_size = 2;
    }
    if (MDB_PHYSICAL_TABLE_GLEM_0 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_GLEM_0, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_GLEM_0;
        data->mdb_item_0_field_size = 7;
        data->mdb_item_1_field_size = 7;
    }
    if (MDB_PHYSICAL_TABLE_GLEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_GLEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_GLEM_1;
        data->mdb_item_0_field_size = 7;
        data->mdb_item_1_field_size = 7;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_1_LL < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_1_LL, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_EEDB_1_LL;
        data->mdb_item_0_field_size = 1;
        data->mdb_item_1_field_size = 1;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_1_2_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_1_2_DATA, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_EEDB_1_2_DATA;
        data->mdb_item_0_field_size = 7;
        data->mdb_item_1_field_size = 7;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_3_LL < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_3_LL, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_EEDB_3_LL;
        data->mdb_item_0_field_size = 1;
        data->mdb_item_1_field_size = 1;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_3_4_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_3_4_DATA, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_EEDB_3_4_DATA;
        data->mdb_item_0_field_size = 6;
        data->mdb_item_1_field_size = 6;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_5_LL < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_5_LL, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_EEDB_5_LL;
        data->mdb_item_0_field_size = 1;
        data->mdb_item_1_field_size = 1;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_5_6_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_5_6_DATA, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_EEDB_5_6_DATA;
        data->mdb_item_0_field_size = 6;
        data->mdb_item_1_field_size = 6;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_7_LL < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_7_LL, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_EEDB_7_LL;
        data->mdb_item_0_field_size = 1;
        data->mdb_item_1_field_size = 1;
    }
    if (MDB_PHYSICAL_TABLE_EEDB_7_8_DATA < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EEDB_7_8_DATA, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_EEDB_7_8_DATA;
        data->mdb_item_0_field_size = 4;
        data->mdb_item_1_field_size = 4;
    }
    if (MDB_PHYSICAL_TABLE_ESEM < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_ESEM, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_ESEM;
        data->mdb_item_0_field_size = 5;
        data->mdb_item_1_field_size = 5;
    }
    if (MDB_PHYSICAL_TABLE_EVSI < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EVSI, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_EVSI;
        data->mdb_item_0_field_size = 2;
        data->mdb_item_1_field_size = 2;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_1, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_EXEM_1;
        data->mdb_item_0_field_size = 3;
        data->mdb_item_1_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_2, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_EXEM_2;
        data->mdb_item_0_field_size = 3;
        data->mdb_item_1_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_3, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_EXEM_3;
        data->mdb_item_0_field_size = 6;
        data->mdb_item_1_field_size = 6;
    }
    if (MDB_PHYSICAL_TABLE_EXEM_4 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_EXEM_4, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_EXEM_4;
        data->mdb_item_0_field_size = 3;
        data->mdb_item_1_field_size = 3;
    }
    if (MDB_PHYSICAL_TABLE_RMEP < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_26_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_RMEP, 0);
        data->dbal_table = DBAL_TABLE_MDB_26_RMEP;
        data->mdb_item_0_field_size = 2;
        data->mdb_item_1_field_size = 2;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_direct_mdb_direct_mdb_phy_tables_info_set(
    int unit)
{
    int mdb_table_id_index;
    dnx_data_mdb_direct_mdb_direct_mdb_phy_tables_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_direct;
    int table_index = dnx_data_mdb_direct_table_mdb_direct_mdb_phy_tables_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = MDB_NOF_PHYSICAL_TABLES;
    table->info_get.key_size[0] = MDB_NOF_PHYSICAL_TABLES;

    
    table->values[0].default_val = "DBAL_TABLE_EMPTY";
    table->values[1].default_val = "DBAL_TABLE_EMPTY";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_direct_mdb_direct_mdb_phy_tables_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_direct_table_mdb_direct_mdb_phy_tables_info");

    
    default_data = (dnx_data_mdb_direct_mdb_direct_mdb_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->mdb_12_table = DBAL_TABLE_EMPTY;
    default_data->mdb_42_table = DBAL_TABLE_EMPTY;
    
    for (mdb_table_id_index = 0; mdb_table_id_index < table->keys[0].size; mdb_table_id_index++)
    {
        data = (dnx_data_mdb_direct_mdb_direct_mdb_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, mdb_table_id_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (MDB_PHYSICAL_TABLE_FEC_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_direct_mdb_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_FEC_1, 0);
        data->mdb_12_table = DBAL_TABLE_MDB_12_FEC_1;
        data->mdb_42_table = DBAL_TABLE_MDB_42_FEC_1;
    }
    if (MDB_PHYSICAL_TABLE_FEC_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_direct_mdb_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_FEC_2, 0);
        data->mdb_12_table = DBAL_TABLE_MDB_12_FEC_2;
        data->mdb_42_table = DBAL_TABLE_MDB_42_FEC_2;
    }
    if (MDB_PHYSICAL_TABLE_FEC_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_direct_mdb_direct_mdb_phy_tables_info_t *) dnxc_data_mgmt_table_data_get(unit, table, MDB_PHYSICAL_TABLE_FEC_3, 0);
        data->mdb_12_table = DBAL_TABLE_MDB_12_FEC_3;
        data->mdb_42_table = DBAL_TABLE_MDB_42_FEC_3;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}





static shr_error_e
j2x_a0_dnx_data_mdb_eedb_eedb_bank_hitbit_masked_clear_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_eedb;
    int feature_index = dnx_data_mdb_eedb_eedb_bank_hitbit_masked_clear;
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
j2x_a0_dnx_data_mdb_eedb_nof_eedb_banks_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_eedb;
    int define_index = dnx_data_mdb_eedb_define_nof_eedb_banks;
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
j2x_a0_dnx_data_mdb_eedb_entry_format_bits_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_eedb;
    int define_index = dnx_data_mdb_eedb_define_entry_format_bits;
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
j2x_a0_dnx_data_mdb_eedb_entry_bank_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_eedb;
    int define_index = dnx_data_mdb_eedb_define_entry_bank;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = MDB_MEM_02000000m;

    
    define->data = MDB_MEM_02000000m;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_eedb_abk_bank_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_eedb;
    int define_index = dnx_data_mdb_eedb_define_abk_bank;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = MDB_MEM_2400000m;

    
    define->data = MDB_MEM_2400000m;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}



static shr_error_e
j2x_a0_dnx_data_mdb_eedb_phase_info_set(
    int unit)
{
    int phase_number_index;
    dnx_data_mdb_eedb_phase_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_eedb;
    int table_index = dnx_data_mdb_eedb_table_phase_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES;
    table->info_get.key_size[0] = DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES;

    
    table->values[0].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_eedb_phase_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_eedb_table_phase_info");

    
    default_data = (dnx_data_mdb_eedb_phase_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->nof_available_banks = 0;
    
    for (phase_number_index = 0; phase_number_index < table->keys[0].size; phase_number_index++)
    {
        data = (dnx_data_mdb_eedb_phase_info_t *) dnxc_data_mgmt_table_data_get(unit, table, phase_number_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (DBAL_ENUM_FVAL_MDB_EEDB_PHASE_PHASE_1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_eedb_phase_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_MDB_EEDB_PHASE_PHASE_1, 0);
        data->nof_available_banks = 64;
    }
    if (DBAL_ENUM_FVAL_MDB_EEDB_PHASE_PHASE_2 < table->keys[0].size)
    {
        data = (dnx_data_mdb_eedb_phase_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_MDB_EEDB_PHASE_PHASE_2, 0);
        data->nof_available_banks = 8;
    }
    if (DBAL_ENUM_FVAL_MDB_EEDB_PHASE_PHASE_3 < table->keys[0].size)
    {
        data = (dnx_data_mdb_eedb_phase_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_MDB_EEDB_PHASE_PHASE_3, 0);
        data->nof_available_banks = 32;
    }
    if (DBAL_ENUM_FVAL_MDB_EEDB_PHASE_PHASE_4 < table->keys[0].size)
    {
        data = (dnx_data_mdb_eedb_phase_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_MDB_EEDB_PHASE_PHASE_4, 0);
        data->nof_available_banks = 8;
    }
    if (DBAL_ENUM_FVAL_MDB_EEDB_PHASE_PHASE_5 < table->keys[0].size)
    {
        data = (dnx_data_mdb_eedb_phase_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_MDB_EEDB_PHASE_PHASE_5, 0);
        data->nof_available_banks = 32;
    }
    if (DBAL_ENUM_FVAL_MDB_EEDB_PHASE_PHASE_6 < table->keys[0].size)
    {
        data = (dnx_data_mdb_eedb_phase_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_MDB_EEDB_PHASE_PHASE_6, 0);
        data->nof_available_banks = 16;
    }
    if (DBAL_ENUM_FVAL_MDB_EEDB_PHASE_PHASE_7 < table->keys[0].size)
    {
        data = (dnx_data_mdb_eedb_phase_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_MDB_EEDB_PHASE_PHASE_7, 0);
        data->nof_available_banks = 16;
    }
    if (DBAL_ENUM_FVAL_MDB_EEDB_PHASE_PHASE_8 < table->keys[0].size)
    {
        data = (dnx_data_mdb_eedb_phase_info_t *) dnxc_data_mgmt_table_data_get(unit, table, DBAL_ENUM_FVAL_MDB_EEDB_PHASE_PHASE_8, 0);
        data->nof_available_banks = 16;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}





static shr_error_e
j2x_a0_dnx_data_mdb_kaps_flex_bb_row_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_kaps;
    int feature_index = dnx_data_mdb_kaps_flex_bb_row;
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
j2x_a0_dnx_data_mdb_kaps_tcam_read_valid_bits_lsbits_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_kaps;
    int feature_index = dnx_data_mdb_kaps_tcam_read_valid_bits_lsbits;
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
j2x_a0_dnx_data_mdb_kaps_max_fmt_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_kaps;
    int define_index = dnx_data_mdb_kaps_define_max_fmt;
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
j2x_a0_dnx_data_mdb_kaps_rpb_field_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_kaps;
    int define_index = dnx_data_mdb_kaps_define_rpb_field;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = RPB_RESETN_Nf;

    
    define->data = RPB_RESETN_Nf;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_kaps_big_kaps_revision_val_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_kaps;
    int define_index = dnx_data_mdb_kaps_define_big_kaps_revision_val;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 0x00050003;

    
    define->data = 0x00050003;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}



static shr_error_e
j2x_a0_dnx_data_mdb_kaps_big_bb_blk_id_mapping_set(
    int unit)
{
    int pair_id_index;
    int blk_id_index;
    dnx_data_mdb_kaps_big_bb_blk_id_mapping_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_kaps;
    int table_index = dnx_data_mdb_kaps_table_big_bb_blk_id_mapping;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = DNX_DATA_MAX_MDB_KAPS_NOF_DBS/MDB_LPM_DBS_IN_PAIR;
    table->info_get.key_size[0] = DNX_DATA_MAX_MDB_KAPS_NOF_DBS/MDB_LPM_DBS_IN_PAIR;
    table->keys[1].size = DNX_DATA_MAX_MDB_KAPS_NOF_BIG_BBS_BLK_IDS;
    table->info_get.key_size[1] = DNX_DATA_MAX_MDB_KAPS_NOF_BIG_BBS_BLK_IDS;

    
    table->values[0].default_val = "DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }
    if (table->keys[1].size == 0 || table->info_get.key_size[1] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_kaps_big_bb_blk_id_mapping_t, (1 * (table->keys[0].size) * (table->keys[1].size) + 1  ), "data of dnx_data_mdb_kaps_table_big_bb_blk_id_mapping");

    
    default_data = (dnx_data_mdb_kaps_big_bb_blk_id_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->global_macro_index = DNX_DATA_MAX_MDB_DH_TOTAL_NOF_MACROES;
    
    for (pair_id_index = 0; pair_id_index < table->keys[0].size; pair_id_index++)
    {
        for (blk_id_index = 0; blk_id_index < table->keys[1].size; blk_id_index++)
        {
            data = (dnx_data_mdb_kaps_big_bb_blk_id_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, pair_id_index, blk_id_index);
            sal_memcpy(data, default_data, table->size_of_values);
        }
    }
    
    if (0 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_mdb_kaps_big_bb_blk_id_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->global_macro_index = 1;
    }
    if (0 < table->keys[0].size && 1 < table->keys[1].size)
    {
        data = (dnx_data_mdb_kaps_big_bb_blk_id_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 1);
        data->global_macro_index = 3;
    }
    if (0 < table->keys[0].size && 2 < table->keys[1].size)
    {
        data = (dnx_data_mdb_kaps_big_bb_blk_id_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 2);
        data->global_macro_index = 4;
    }
    if (0 < table->keys[0].size && 3 < table->keys[1].size)
    {
        data = (dnx_data_mdb_kaps_big_bb_blk_id_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 3);
        data->global_macro_index = 7;
    }
    if (0 < table->keys[0].size && 4 < table->keys[1].size)
    {
        data = (dnx_data_mdb_kaps_big_bb_blk_id_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 4);
        data->global_macro_index = 8;
    }
    if (0 < table->keys[0].size && 5 < table->keys[1].size)
    {
        data = (dnx_data_mdb_kaps_big_bb_blk_id_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 5);
        data->global_macro_index = 9;
    }
    if (0 < table->keys[0].size && 6 < table->keys[1].size)
    {
        data = (dnx_data_mdb_kaps_big_bb_blk_id_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 6);
        data->global_macro_index = 10;
    }
    if (0 < table->keys[0].size && 7 < table->keys[1].size)
    {
        data = (dnx_data_mdb_kaps_big_bb_blk_id_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 7);
        data->global_macro_index = 11;
    }
    if (0 < table->keys[0].size && 8 < table->keys[1].size)
    {
        data = (dnx_data_mdb_kaps_big_bb_blk_id_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 8);
        data->global_macro_index = 13;
    }
    if (0 < table->keys[0].size && 9 < table->keys[1].size)
    {
        data = (dnx_data_mdb_kaps_big_bb_blk_id_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 9);
        data->global_macro_index = 14;
    }
    if (0 < table->keys[0].size && 10 < table->keys[1].size)
    {
        data = (dnx_data_mdb_kaps_big_bb_blk_id_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 10);
        data->global_macro_index = 15;
    }
    if (0 < table->keys[0].size && 11 < table->keys[1].size)
    {
        data = (dnx_data_mdb_kaps_big_bb_blk_id_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 11);
        data->global_macro_index = 17;
    }
    if (0 < table->keys[0].size && 12 < table->keys[1].size)
    {
        data = (dnx_data_mdb_kaps_big_bb_blk_id_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 12);
        data->global_macro_index = 18;
    }
    if (0 < table->keys[0].size && 13 < table->keys[1].size)
    {
        data = (dnx_data_mdb_kaps_big_bb_blk_id_mapping_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 13);
        data->global_macro_index = 19;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_kaps_db_info_set(
    int unit)
{
    int db_idx_index;
    dnx_data_mdb_kaps_db_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_kaps;
    int table_index = dnx_data_mdb_kaps_table_db_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = dnx_data_mdb.kaps.nof_dbs_get(unit);
    table->info_get.key_size[0] = dnx_data_mdb.kaps.nof_dbs_get(unit);

    
    table->values[0].default_val = "DBAL_NOF_PHYSICAL_TABLES";
    table->values[1].default_val = "MDB_NOF_PHYSICAL_TABLES";
    table->values[2].default_val = "MDB_NOF_PHYSICAL_TABLES";
    table->values[3].default_val = "MDB_NOF_PHYSICAL_TABLES";
    table->values[4].default_val = "DEFAULT_KAPS_DB_NAME";
    table->values[5].default_val = "DBAL_NOF_DYNAMIC_AND_STATIC_TABLES";
    table->values[6].default_val = "0";
    table->values[7].default_val = "0";
    table->values[8].default_val = "0";
    table->values[9].default_val = "0";
    table->values[10].default_val = "0";
    table->values[11].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_kaps_db_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_mdb_kaps_table_db_info");

    
    default_data = (dnx_data_mdb_kaps_db_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->dbal_id = DBAL_NOF_PHYSICAL_TABLES;
    default_data->mdb_bb_id = MDB_NOF_PHYSICAL_TABLES;
    default_data->mdb_ads_id = MDB_NOF_PHYSICAL_TABLES;
    default_data->mdb_direct_id = MDB_NOF_PHYSICAL_TABLES;
    default_data->name = "DEFAULT_KAPS_DB_NAME";
    default_data->dbal_table_db_atr = DBAL_NOF_DYNAMIC_AND_STATIC_TABLES;
    default_data->nof_rows_in_rpb = 0;
    default_data->nof_rows_in_small_ads = 0;
    default_data->nof_rows_in_small_bb = 0;
    default_data->nof_rows_in_small_rpb_hitbits = 0;
    default_data->nof_connected_big_bbs = 0;
    default_data->nof_result_types = 0;
    
    for (db_idx_index = 0; db_idx_index < table->keys[0].size; db_idx_index++)
    {
        data = (dnx_data_mdb_kaps_db_info_t *) dnxc_data_mgmt_table_data_get(unit, table, db_idx_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_mdb_kaps_db_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->dbal_id = DBAL_PHYSICAL_TABLE_KAPS_1;
        data->mdb_bb_id = MDB_PHYSICAL_TABLE_BIG_KAPS_BB_1;
        data->mdb_ads_id = MDB_PHYSICAL_TABLE_ADS_1;
        data->mdb_direct_id = MDB_NOF_PHYSICAL_TABLES;
        data->name = "PRIVATE";
        data->dbal_table_db_atr = DBAL_TABLE_MDB_28_KAPS_1;
        data->nof_rows_in_rpb = 2048;
        data->nof_rows_in_small_ads = 1024;
        data->nof_rows_in_small_bb = 512;
        data->nof_rows_in_small_rpb_hitbits = 64;
        data->nof_connected_big_bbs = 12;
        data->nof_result_types = 1;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_mdb_kaps_db_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->dbal_id = DBAL_PHYSICAL_TABLE_KAPS_2;
        data->mdb_bb_id = MDB_PHYSICAL_TABLE_BIG_KAPS_BB_2;
        data->mdb_ads_id = MDB_PHYSICAL_TABLE_ADS_2;
        data->mdb_direct_id = MDB_NOF_PHYSICAL_TABLES;
        data->name = "PUBLIC";
        data->dbal_table_db_atr = DBAL_TABLE_MDB_28_KAPS_2;
        data->nof_rows_in_rpb = 2048;
        data->nof_rows_in_small_ads = 1024;
        data->nof_rows_in_small_bb = 512;
        data->nof_rows_in_small_rpb_hitbits = 64;
        data->nof_connected_big_bbs = 6;
        data->nof_result_types = 1;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
j2x_a0_dnx_data_mdb_kaps_kaps_lookup_result_set(
    int unit)
{
    int db_idx_index;
    int core_index;
    dnx_data_mdb_kaps_kaps_lookup_result_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_kaps;
    int table_index = dnx_data_mdb_kaps_table_kaps_lookup_result;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 2;
    table->info_get.key_size[0] = 2;
    table->keys[1].size = dnx_data_device.general.nof_cores_get(unit);
    table->info_get.key_size[1] = dnx_data_device.general.nof_cores_get(unit);

    
    table->values[0].default_val = "0";
    table->values[1].default_val = "0";
    table->values[2].default_val = "0";
    table->values[3].default_val = "0";
    table->values[4].default_val = "0";
    table->values[5].default_val = "0";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }
    if (table->keys[1].size == 0 || table->info_get.key_size[1] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_mdb_kaps_kaps_lookup_result_t, (1 * (table->keys[0].size) * (table->keys[1].size) + 1  ), "data of dnx_data_mdb_kaps_table_kaps_lookup_result");

    
    default_data = (dnx_data_mdb_kaps_kaps_lookup_result_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->lookup_result = 0;
    default_data->payload_field = 0;
    default_data->prefix_length_field = 0;
    default_data->result_found_field = 0;
    default_data->result_error_field = 0;
    default_data->result_type_field = 0;
    
    for (db_idx_index = 0; db_idx_index < table->keys[0].size; db_idx_index++)
    {
        for (core_index = 0; core_index < table->keys[1].size; core_index++)
        {
            data = (dnx_data_mdb_kaps_kaps_lookup_result_t *) dnxc_data_mgmt_table_data_get(unit, table, db_idx_index, core_index);
            sal_memcpy(data, default_data, table->size_of_values);
        }
    }
    
    if (0 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_mdb_kaps_kaps_lookup_result_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->lookup_result = MDB_REG_2002r;
    }
    if (1 < table->keys[0].size && 0 < table->keys[1].size)
    {
        data = (dnx_data_mdb_kaps_kaps_lookup_result_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->lookup_result = MDB_REG_2010r;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}





static shr_error_e
j2x_a0_dnx_data_mdb_feature_step_table_supports_mix_ar_algo_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_feature;
    int feature_index = dnx_data_mdb_feature_step_table_supports_mix_ar_algo;
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
j2x_a0_dnx_data_mdb_feature_eedb_bank_traffic_lock_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_feature;
    int feature_index = dnx_data_mdb_feature_eedb_bank_traffic_lock;
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
j2x_a0_dnx_data_mdb_feature_em_dfg_ovf_cam_disabled_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_feature;
    int feature_index = dnx_data_mdb_feature_em_dfg_ovf_cam_disabled;
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
j2x_a0_dnx_data_mdb_feature_em_mact_transplant_no_reply_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_feature;
    int feature_index = dnx_data_mdb_feature_em_mact_transplant_no_reply;
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
j2x_a0_dnx_data_mdb_feature_em_mact_use_refresh_on_insert_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_feature;
    int feature_index = dnx_data_mdb_feature_em_mact_use_refresh_on_insert;
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
j2x_a0_dnx_data_mdb_feature_em_mact_delete_transplant_no_reply_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_feature;
    int feature_index = dnx_data_mdb_feature_em_mact_delete_transplant_no_reply;
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
j2x_a0_dnx_data_mdb_feature_em_mact_insert_flush_drop_on_exceed_limit_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_feature;
    int feature_index = dnx_data_mdb_feature_em_mact_insert_flush_drop_on_exceed_limit;
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
j2x_a0_dnx_data_mdb_feature_em_sbus_interface_shutdown_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_feature;
    int feature_index = dnx_data_mdb_feature_em_sbus_interface_shutdown;
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
j2x_a0_dnx_data_mdb_feature_em_ecc_simple_command_deadlock_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_feature;
    int feature_index = dnx_data_mdb_feature_em_ecc_simple_command_deadlock;
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
j2x_a0_dnx_data_mdb_feature_em_compare_init_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_feature;
    int feature_index = dnx_data_mdb_feature_em_compare_init;
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
j2x_a0_dnx_data_mdb_feature_bubble_pulse_width_too_short_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_feature;
    int feature_index = dnx_data_mdb_feature_bubble_pulse_width_too_short;
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
j2x_a0_dnx_data_mdb_feature_kaps_rpb_ecc_valid_shared_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_mdb;
    int submodule_index = dnx_data_mdb_submodule_feature;
    int feature_index = dnx_data_mdb_feature_kaps_rpb_ecc_valid_shared;
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
j2x_a0_data_mdb_attach(
    int unit)
{
    dnxc_data_module_t *module = NULL;
    dnxc_data_submodule_t *submodule = NULL;
    dnxc_data_define_t *define = NULL;
    dnxc_data_feature_t *feature = NULL;
    dnxc_data_table_t *table = NULL;
    int module_index = dnx_data_module_mdb;
    int submodule_index = -1, data_index = -1;
    SHR_FUNC_INIT_VARS(unit);

    COMPILER_REFERENCE(define);
    COMPILER_REFERENCE(feature);
    COMPILER_REFERENCE(table);
    COMPILER_REFERENCE(submodule);
    COMPILER_REFERENCE(data_index);
    COMPILER_REFERENCE(submodule_index);
    module = &_dnxc_data[unit].modules[module_index];
    
    submodule_index = dnx_data_mdb_submodule_global;
    submodule = &module->submodules[submodule_index];

    

    

    
    
    submodule_index = dnx_data_mdb_submodule_dh;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_mdb_dh_define_max_nof_cluster_interfaces;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_dh_max_nof_cluster_interfaces_set;
    data_index = dnx_data_mdb_dh_define_nof_ddha_blocks;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_dh_nof_ddha_blocks_set;
    data_index = dnx_data_mdb_dh_define_nof_ddhb_blocks;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_dh_nof_ddhb_blocks_set;
    data_index = dnx_data_mdb_dh_define_nof_dhc_blocks;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_dh_nof_dhc_blocks_set;
    data_index = dnx_data_mdb_dh_define_bpu_setup_bb_connected;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_dh_bpu_setup_bb_connected_set;
    data_index = dnx_data_mdb_dh_define_bpu_setup_size_120_240_120;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_dh_bpu_setup_size_120_240_120_set;
    data_index = dnx_data_mdb_dh_define_bpu_setup_size_480_odd;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_dh_bpu_setup_size_480_odd_set;
    data_index = dnx_data_mdb_dh_define_bpu_setup_size_480;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_dh_bpu_setup_size_480_set;
    data_index = dnx_data_mdb_dh_define_bpu_setup_size_360_120;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_dh_bpu_setup_size_360_120_set;
    data_index = dnx_data_mdb_dh_define_bpu_setup_size_120_360;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_dh_bpu_setup_size_120_360_set;
    data_index = dnx_data_mdb_dh_define_bpu_setup_size_240_240;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_dh_bpu_setup_size_240_240_set;
    data_index = dnx_data_mdb_dh_define_bpu_setup_size_120_120_240;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_dh_bpu_setup_size_120_120_240_set;
    data_index = dnx_data_mdb_dh_define_bpu_setup_size_240_120_120;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_dh_bpu_setup_size_240_120_120_set;
    data_index = dnx_data_mdb_dh_define_bpu_setup_size_120_120_120_120;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_dh_bpu_setup_size_120_120_120_120_set;

    
    data_index = dnx_data_mdb_dh_bpu_setup_extended_support;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_dh_bpu_setup_extended_support_set;

    
    data_index = dnx_data_mdb_dh_table_dh_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_dh_dh_info_set;
    data_index = dnx_data_mdb_dh_table_block_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_dh_block_info_set;
    data_index = dnx_data_mdb_dh_table_macro_type_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_dh_macro_type_info_set;
    data_index = dnx_data_mdb_dh_table_entry_banks_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_dh_entry_banks_info_set;
    data_index = dnx_data_mdb_dh_table_mdb_1_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_dh_mdb_1_info_set;
    data_index = dnx_data_mdb_dh_table_mdb_2_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_dh_mdb_2_info_set;
    data_index = dnx_data_mdb_dh_table_mdb_3_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_dh_mdb_3_info_set;
    
    submodule_index = dnx_data_mdb_submodule_pdbs;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_mdb_pdbs_define_max_nof_interface_dhs;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_pdbs_max_nof_interface_dhs_set;
    data_index = dnx_data_mdb_pdbs_define_mesh_mode_support;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_pdbs_mesh_mode_support_set;
    data_index = dnx_data_mdb_pdbs_define_table_mdb_9_mdb_item_1_array_size;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_pdbs_table_mdb_9_mdb_item_1_array_size_set;
    data_index = dnx_data_mdb_pdbs_define_table_mdb_9_mdb_item_2_array_size;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_pdbs_table_mdb_9_mdb_item_2_array_size_set;
    data_index = dnx_data_mdb_pdbs_define_table_mdb_9_mdb_item_3_array_size;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_pdbs_table_mdb_9_mdb_item_3_array_size_set;
    data_index = dnx_data_mdb_pdbs_define_table_mdb_40_mdb_item_0_array_size;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_pdbs_table_mdb_40_mdb_item_0_array_size_set;
    data_index = dnx_data_mdb_pdbs_define_table_mdb_dynamic_memory_access_memory_access_field_size;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_pdbs_table_mdb_dynamic_memory_access_memory_access_field_size_set;
    data_index = dnx_data_mdb_pdbs_define_table_mdb_mact_dynamic_memory_access_memory_access_field_size;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_pdbs_table_mdb_mact_dynamic_memory_access_memory_access_field_size_set;
    data_index = dnx_data_mdb_pdbs_define_table_mdb_kaps_dynamic_memory_access_sbc_memory_access_field_size;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_pdbs_table_mdb_kaps_dynamic_memory_access_sbc_memory_access_field_size_set;
    data_index = dnx_data_mdb_pdbs_define_table_mdb_ddhb_dynamic_memory_access_memory_access_field_size;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_pdbs_table_mdb_ddhb_dynamic_memory_access_memory_access_field_size_set;
    data_index = dnx_data_mdb_pdbs_define_table_mdb_kaps_dynamic_memory_access_memory_access_field_size;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_pdbs_table_mdb_kaps_dynamic_memory_access_memory_access_field_size_set;
    data_index = dnx_data_mdb_pdbs_define_table_mdb_ddha_dynamic_memory_access_memory_access_field_size;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_pdbs_table_mdb_ddha_dynamic_memory_access_memory_access_field_size_set;

    

    
    
    submodule_index = dnx_data_mdb_submodule_em;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_mdb_em_define_age_support_per_entry_size_ratio;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_em_age_support_per_entry_size_ratio_set;
    data_index = dnx_data_mdb_em_define_flush_tcam_rule_counter_support;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_em_flush_tcam_rule_counter_support_set;
    data_index = dnx_data_mdb_em_define_max_nof_spn_sizes;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_em_max_nof_spn_sizes_set;
    data_index = dnx_data_mdb_em_define_defragmentation_priority_supported;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_em_defragmentation_priority_supported_set;
    data_index = dnx_data_mdb_em_define_disable_cuckoo_loop_detection_support;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_em_disable_cuckoo_loop_detection_support_set;
    data_index = dnx_data_mdb_em_define_disable_cuckoo_hit_bit_sync;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_em_disable_cuckoo_hit_bit_sync_set;
    data_index = dnx_data_mdb_em_define_age_profile_per_ratio_support;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_em_age_profile_per_ratio_support_set;
    data_index = dnx_data_mdb_em_define_flex_mag_supported;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_em_flex_mag_supported_set;
    data_index = dnx_data_mdb_em_define_flex_fully_supported;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_em_flex_fully_supported_set;
    data_index = dnx_data_mdb_em_define_extra_vmv_shift_registers;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_em_extra_vmv_shift_registers_set;
    data_index = dnx_data_mdb_em_define_scan_bank_participate_in_cuckoo_support;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_em_scan_bank_participate_in_cuckoo_support_set;
    data_index = dnx_data_mdb_em_define_scan_bank_participate_in_cuckoo_partial_support;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_em_scan_bank_participate_in_cuckoo_partial_support_set;
    data_index = dnx_data_mdb_em_define_sbus_error_code_support;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_em_sbus_error_code_support_set;
    data_index = dnx_data_mdb_em_define_defrag_interrupt_support;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_em_defrag_interrupt_support_set;
    data_index = dnx_data_mdb_em_define_flush_max_supported_payload;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_em_flush_max_supported_payload_set;
    data_index = dnx_data_mdb_em_define_flush_payload_max_bus;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_em_flush_payload_max_bus_set;

    
    data_index = dnx_data_mdb_em_entry_counter_decrease_support;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_em_entry_counter_decrease_support_set;
    data_index = dnx_data_mdb_em_entry_type_parser;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_em_entry_type_parser_set;
    data_index = dnx_data_mdb_em_step_table_any_cmds_support;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_em_step_table_any_cmds_support_set;
    data_index = dnx_data_mdb_em_is_isem_dpc_in_vtt5;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_em_is_isem_dpc_in_vtt5_set;

    
    data_index = dnx_data_mdb_em_table_spn;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_spn_set;
    data_index = dnx_data_mdb_em_table_compare_size;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_compare_size_set;
    data_index = dnx_data_mdb_em_table_em_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_em_info_set;
    data_index = dnx_data_mdb_em_table_step_table_pdb_max_depth;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_step_table_pdb_max_depth_set;
    data_index = dnx_data_mdb_em_table_step_table_max_depth_possible;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_step_table_max_depth_possible_set;
    data_index = dnx_data_mdb_em_table_step_table_max_depth_nof_ways_ar;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_step_table_max_depth_nof_ways_ar_set;
    data_index = dnx_data_mdb_em_table_mdb_15_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_mdb_15_info_set;
    data_index = dnx_data_mdb_em_table_mdb_16_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_mdb_16_info_set;
    data_index = dnx_data_mdb_em_table_mdb_21_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_mdb_21_info_set;
    data_index = dnx_data_mdb_em_table_mdb_23_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_mdb_23_info_set;
    data_index = dnx_data_mdb_em_table_mdb_24_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_mdb_24_info_set;
    data_index = dnx_data_mdb_em_table_mdb_29_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_mdb_29_info_set;
    data_index = dnx_data_mdb_em_table_mdb_32_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_mdb_32_info_set;
    data_index = dnx_data_mdb_em_table_mdb_41_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_mdb_41_info_set;
    data_index = dnx_data_mdb_em_table_mdb_emp_tables_mapping;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_mdb_emp_tables_mapping_set;
    data_index = dnx_data_mdb_em_table_mdb_em_shift_vmv_regs;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_mdb_em_shift_vmv_regs_set;
    data_index = dnx_data_mdb_em_table_em_emp;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_em_emp_set;
    data_index = dnx_data_mdb_em_table_mdb_step_table_map;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_mdb_step_table_map_set;
    data_index = dnx_data_mdb_em_table_mdb_em_dbal_phy_tables_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_mdb_em_dbal_phy_tables_info_set;
    data_index = dnx_data_mdb_em_table_filter_rules;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_filter_rules_set;
    data_index = dnx_data_mdb_em_table_data_rules;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_em_data_rules_set;
    
    submodule_index = dnx_data_mdb_submodule_direct;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_mdb_direct_define_physical_address_ovf_enable_val;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_direct_physical_address_ovf_enable_val_set;

    
    data_index = dnx_data_mdb_direct_fec_abk_mapping;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_direct_fec_abk_mapping_set;

    
    data_index = dnx_data_mdb_direct_table_mdb_11_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_direct_mdb_11_info_set;
    data_index = dnx_data_mdb_direct_table_mdb_26_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_direct_mdb_26_info_set;
    data_index = dnx_data_mdb_direct_table_mdb_direct_mdb_phy_tables_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_direct_mdb_direct_mdb_phy_tables_info_set;
    
    submodule_index = dnx_data_mdb_submodule_eedb;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_mdb_eedb_define_nof_eedb_banks;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_eedb_nof_eedb_banks_set;
    data_index = dnx_data_mdb_eedb_define_entry_format_bits;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_eedb_entry_format_bits_set;
    data_index = dnx_data_mdb_eedb_define_entry_bank;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_eedb_entry_bank_set;
    data_index = dnx_data_mdb_eedb_define_abk_bank;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_eedb_abk_bank_set;

    
    data_index = dnx_data_mdb_eedb_eedb_bank_hitbit_masked_clear;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_eedb_eedb_bank_hitbit_masked_clear_set;

    
    data_index = dnx_data_mdb_eedb_table_phase_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_eedb_phase_info_set;
    
    submodule_index = dnx_data_mdb_submodule_kaps;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_mdb_kaps_define_max_fmt;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_kaps_max_fmt_set;
    data_index = dnx_data_mdb_kaps_define_rpb_field;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_kaps_rpb_field_set;
    data_index = dnx_data_mdb_kaps_define_big_kaps_revision_val;
    define = &submodule->defines[data_index];
    define->set = j2x_a0_dnx_data_mdb_kaps_big_kaps_revision_val_set;

    
    data_index = dnx_data_mdb_kaps_flex_bb_row;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_kaps_flex_bb_row_set;
    data_index = dnx_data_mdb_kaps_tcam_read_valid_bits_lsbits;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_kaps_tcam_read_valid_bits_lsbits_set;

    
    data_index = dnx_data_mdb_kaps_table_big_bb_blk_id_mapping;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_kaps_big_bb_blk_id_mapping_set;
    data_index = dnx_data_mdb_kaps_table_db_info;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_kaps_db_info_set;
    data_index = dnx_data_mdb_kaps_table_kaps_lookup_result;
    table = &submodule->tables[data_index];
    table->set = j2x_a0_dnx_data_mdb_kaps_kaps_lookup_result_set;
    
    submodule_index = dnx_data_mdb_submodule_feature;
    submodule = &module->submodules[submodule_index];

    

    
    data_index = dnx_data_mdb_feature_step_table_supports_mix_ar_algo;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_feature_step_table_supports_mix_ar_algo_set;
    data_index = dnx_data_mdb_feature_eedb_bank_traffic_lock;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_feature_eedb_bank_traffic_lock_set;
    data_index = dnx_data_mdb_feature_em_dfg_ovf_cam_disabled;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_feature_em_dfg_ovf_cam_disabled_set;
    data_index = dnx_data_mdb_feature_em_mact_transplant_no_reply;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_feature_em_mact_transplant_no_reply_set;
    data_index = dnx_data_mdb_feature_em_mact_use_refresh_on_insert;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_feature_em_mact_use_refresh_on_insert_set;
    data_index = dnx_data_mdb_feature_em_mact_delete_transplant_no_reply;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_feature_em_mact_delete_transplant_no_reply_set;
    data_index = dnx_data_mdb_feature_em_mact_insert_flush_drop_on_exceed_limit;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_feature_em_mact_insert_flush_drop_on_exceed_limit_set;
    data_index = dnx_data_mdb_feature_em_sbus_interface_shutdown;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_feature_em_sbus_interface_shutdown_set;
    data_index = dnx_data_mdb_feature_em_ecc_simple_command_deadlock;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_feature_em_ecc_simple_command_deadlock_set;
    data_index = dnx_data_mdb_feature_em_compare_init;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_feature_em_compare_init_set;
    data_index = dnx_data_mdb_feature_bubble_pulse_width_too_short;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_feature_bubble_pulse_width_too_short_set;
    data_index = dnx_data_mdb_feature_kaps_rpb_ecc_valid_shared;
    feature = &submodule->features[data_index];
    feature->set = j2x_a0_dnx_data_mdb_feature_kaps_rpb_ecc_valid_shared_set;

    

    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE



/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_STAT

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_stat.h>
#include <soc/mcm/allenum.h>
#include <bcm/stat.h>







static shr_error_e
jr2_a0_dnx_data_stat_stat_pp_epp_combined_interfaces_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_stat_pp;
    int feature_index = dnx_data_stat_stat_pp_epp_combined_interfaces;
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
jr2_a0_dnx_data_stat_stat_pp_full_stat_support_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_stat_pp;
    int feature_index = dnx_data_stat_stat_pp_full_stat_support;
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
jr2_a0_dnx_data_stat_stat_pp_erpp_counter_profile_per_outlif_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_stat_pp;
    int feature_index = dnx_data_stat_stat_pp_erpp_counter_profile_per_outlif;
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
jr2_a0_dnx_data_stat_stat_pp_max_irpp_profile_value_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_stat_pp;
    int define_index = dnx_data_stat_stat_pp_define_max_irpp_profile_value;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 31;

    
    define->data = 31;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_stat_stat_pp_max_etpp_profile_value_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_stat_pp;
    int define_index = dnx_data_stat_stat_pp_define_max_etpp_profile_value;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 31;

    
    define->data = 31;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_stat_stat_pp_max_etpp_counting_profile_value_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_stat_pp;
    int define_index = dnx_data_stat_stat_pp_define_max_etpp_counting_profile_value;
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
jr2_a0_dnx_data_stat_stat_pp_max_etpp_metering_profile_value_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_stat_pp;
    int define_index = dnx_data_stat_stat_pp_define_max_etpp_metering_profile_value;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 31;

    
    define->data = 31;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_stat_stat_pp_max_erpp_profile_value_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_stat_pp;
    int define_index = dnx_data_stat_stat_pp_define_max_erpp_profile_value;
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
jr2_a0_dnx_data_stat_stat_pp_etpp_reversed_stat_cmd_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_stat_pp;
    int define_index = dnx_data_stat_stat_pp_define_etpp_reversed_stat_cmd;
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
jr2_a0_dnx_data_stat_stat_pp_etpp_enc_stat_cmd_is_reversed_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_stat_pp;
    int define_index = dnx_data_stat_stat_pp_define_etpp_enc_stat_cmd_is_reversed;
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
jr2_a0_dnx_data_stat_stat_pp_etpp_egress_vsi_always_pushed_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_stat_pp;
    int define_index = dnx_data_stat_stat_pp_define_etpp_egress_vsi_always_pushed;
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
jr2_a0_dnx_data_stat_stat_pp_irpp_start_profile_value_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_stat_pp;
    int define_index = dnx_data_stat_stat_pp_define_irpp_start_profile_value;
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
jr2_a0_dnx_data_stat_stat_pp_erpp_start_profile_value_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_stat_pp;
    int define_index = dnx_data_stat_stat_pp_define_erpp_start_profile_value;
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
jr2_a0_dnx_data_stat_stat_pp_etpp_start_profile_value_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_stat_pp;
    int define_index = dnx_data_stat_stat_pp_define_etpp_start_profile_value;
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
jr2_a0_dnx_data_stat_stat_pp_etpp_counting_start_profile_value_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_stat_pp;
    int define_index = dnx_data_stat_stat_pp_define_etpp_counting_start_profile_value;
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
jr2_a0_dnx_data_stat_stat_pp_etpp_metering_start_profile_value_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_stat_pp;
    int define_index = dnx_data_stat_stat_pp_define_etpp_metering_start_profile_value;
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
jr2_a0_dnx_data_stat_stat_pp_supported_egress_interface_counter_enum_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_stat_pp;
    int define_index = dnx_data_stat_stat_pp_define_supported_egress_interface_counter_enum;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = bcmStatCounterInterfaceEgressTransmitPp;

    
    define->data = bcmStatCounterInterfaceEgressTransmitPp;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}








static shr_error_e
jr2_a0_dnx_data_stat_diag_counter_ovf_info_set(
    int unit)
{
    int index_index;
    dnx_data_stat_diag_counter_ovf_info_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_diag_counter;
    int table_index = dnx_data_stat_diag_counter_table_ovf_info;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = 10;
    table->info_get.key_size[0] = 10;

    
    table->values[0].default_val = "INVALIDr";
    table->values[1].default_val = "INVALIDf";
    table->values[2].default_val = "INVALIDf";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_stat_diag_counter_ovf_info_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_stat_diag_counter_table_ovf_info");

    
    default_data = (dnx_data_stat_diag_counter_ovf_info_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->reg = INVALIDr;
    default_data->cnt_field = INVALIDf;
    default_data->ovf_field = INVALIDf;
    
    for (index_index = 0; index_index < table->keys[0].size; index_index++)
    {
        data = (dnx_data_stat_diag_counter_ovf_info_t *) dnxc_data_mgmt_table_data_get(unit, table, index_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (0 < table->keys[0].size)
    {
        data = (dnx_data_stat_diag_counter_ovf_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 0, 0);
        data->reg = EVNT_TX_ENG_EVENTS_CNTr;
        data->cnt_field = TX_ENG_EVENTS_CNT_Nf;
        data->ovf_field = TX_ENG_EVENTS_CNT_OVF_Nf;
    }
    if (1 < table->keys[0].size)
    {
        data = (dnx_data_stat_diag_counter_ovf_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 1, 0);
        data->reg = FCR_CELL_DROP_COUNTER_1r;
        data->cnt_field = AUTO_DOC_NAME_9f;
        data->ovf_field = AUTO_DOC_NAME_10f;
    }
    if (2 < table->keys[0].size)
    {
        data = (dnx_data_stat_diag_counter_ovf_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 2, 0);
        data->reg = FDR_P_1_FDR_DISCARD_COUNTER_MACNr;
        data->cnt_field = P_1_FDR_DISC_CNT_MACNf;
        data->ovf_field = P_1_TSC_DISC_MAC_N_CNT_OVERFLOWf;
    }
    if (3 < table->keys[0].size)
    {
        data = (dnx_data_stat_diag_counter_ovf_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 3, 0);
        data->reg = FDR_P_1_FDR_FIFO_DISCARD_COUNTER_MACNr;
        data->cnt_field = P_1_FDR_FIFO_DISC_CNT_MACNf;
        data->ovf_field = P_1_SRT_DISC_MAC_N_CNT_OVERFLOWf;
    }
    if (4 < table->keys[0].size)
    {
        data = (dnx_data_stat_diag_counter_ovf_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 4, 0);
        data->reg = FDR_P_2_FDR_DISCARD_COUNTER_MACNr;
        data->cnt_field = P_2_FDR_DISC_CNT_MACNf;
        data->ovf_field = P_2_TSC_DISC_MAC_N_CNT_OVERFLOWf;
    }
    if (5 < table->keys[0].size)
    {
        data = (dnx_data_stat_diag_counter_ovf_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 5, 0);
        data->reg = FDR_P_2_FDR_FIFO_DISCARD_COUNTER_MACNr;
        data->cnt_field = P_2_FDR_FIFO_DISC_CNT_MACNf;
        data->ovf_field = P_2_SRT_DISC_MAC_N_CNT_OVERFLOWf;
    }
    if (6 < table->keys[0].size)
    {
        data = (dnx_data_stat_diag_counter_ovf_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 6, 0);
        data->reg = FDR_P_3_FDR_DISCARD_COUNTER_MACNr;
        data->cnt_field = P_3_FDR_DISC_CNT_MACNf;
        data->ovf_field = P_3_TSC_DISC_MAC_N_CNT_OVERFLOWf;
    }
    if (7 < table->keys[0].size)
    {
        data = (dnx_data_stat_diag_counter_ovf_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 7, 0);
        data->reg = FDR_P_3_FDR_FIFO_DISCARD_COUNTER_MACNr;
        data->cnt_field = P_3_FDR_FIFO_DISC_CNT_MACNf;
        data->ovf_field = P_3_SRT_DISC_MAC_N_CNT_OVERFLOWf;
    }
    if (8 < table->keys[0].size)
    {
        data = (dnx_data_stat_diag_counter_ovf_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 8, 0);
        data->reg = SCH_DBG_CML_SCHEDULER_COUNTERr;
        data->cnt_field = CML_SCH_CREDIT_CNTf;
        data->ovf_field = CML_SCH_CREDIT_OVFf;
    }
    if (9 < table->keys[0].size)
    {
        data = (dnx_data_stat_diag_counter_ovf_info_t *) dnxc_data_mgmt_table_data_get(unit, table, 9, 0);
        data->reg = SCH_DBG_CREDIT_COUNTERr;
        data->cnt_field = CREDIT_CNTf;
        data->ovf_field = CREDIT_OVFf;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}






static shr_error_e
jr2_a0_dnx_data_stat_drop_reasons_nof_drop_reasons_set(
    int unit)
{
    dnxc_data_define_t *define;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_drop_reasons;
    int define_index = dnx_data_stat_drop_reasons_define_nof_drop_reasons;
    SHR_FUNC_INIT_VARS(unit);

    define = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].defines[define_index];
    
    define->default_data = 45;

    
    define->data = 45;

    
    define->flags |= DNXC_DATA_F_SUPPORTED;

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_define_value_set(unit, define));


exit:
    SHR_FUNC_EXIT;
}



static shr_error_e
jr2_a0_dnx_data_stat_drop_reasons_group_drop_reason_index_set(
    int unit)
{
    int group_index;
    dnx_data_stat_drop_reasons_group_drop_reason_index_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_drop_reasons;
    int table_index = dnx_data_stat_drop_reasons_table_group_drop_reason_index;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = bcmStatCounterGroupFilterCount;
    table->info_get.key_size[0] = bcmStatCounterGroupFilterCount;

    
    table->values[0].default_val = "-1";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_stat_drop_reasons_group_drop_reason_index_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_stat_drop_reasons_table_group_drop_reason_index");

    
    default_data = (dnx_data_stat_drop_reasons_group_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->index = -1;
    
    for (group_index = 0; group_index < table->keys[0].size; group_index++)
    {
        data = (dnx_data_stat_drop_reasons_group_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, group_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (bcmStatCounterGroupFilterGlobalResourcesDrop < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_group_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmStatCounterGroupFilterGlobalResourcesDrop, 0);
        data->index = 0;
    }
    if (bcmStatCounterGroupFilterVoqResourcesDrop < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_group_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmStatCounterGroupFilterVoqResourcesDrop, 0);
        data->index = 1;
    }
    if (bcmStatCounterGroupFilterWredDrop < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_group_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmStatCounterGroupFilterWredDrop, 0);
        data->index = 2;
    }
    if (bcmStatCounterGroupFilterOcbResourcesDrop < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_group_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmStatCounterGroupFilterOcbResourcesDrop, 0);
        data->index = 3;
    }
    if (bcmStatCounterGroupFilterVsqResourcesDrop < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_group_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmStatCounterGroupFilterVsqResourcesDrop, 0);
        data->index = 4;
    }
    if (bcmStatCounterGroupFilterMiscDrop < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_group_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmStatCounterGroupFilterMiscDrop, 0);
        data->index = 6;
    }
    if (bcmStatCounterGroupFilterUserDefinedGroup < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_group_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmStatCounterGroupFilterUserDefinedGroup, 0);
        data->index = 7;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_stat_drop_reasons_drop_reason_index_set(
    int unit)
{
    int drop_reason_bit_index;
    dnx_data_stat_drop_reasons_drop_reason_index_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_drop_reasons;
    int table_index = dnx_data_stat_drop_reasons_table_drop_reason_index;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = bcmCosqDropReasonRejectCount;
    table->info_get.key_size[0] = bcmCosqDropReasonRejectCount;

    
    table->values[0].default_val = "-1";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_stat_drop_reasons_drop_reason_index_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_stat_drop_reasons_table_drop_reason_index");

    
    default_data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->index = -1;
    
    for (drop_reason_bit_index = 0; drop_reason_bit_index < table->keys[0].size; drop_reason_bit_index++)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, drop_reason_bit_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (bcmCosqDropReasonGlobalDramBdbsReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonGlobalDramBdbsReject, 0);
        data->index = 0;
    }
    if (bcmCosqDropReasonGlobalSramBuffersReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonGlobalSramBuffersReject, 0);
        data->index = 1;
    }
    if (bcmCosqDropReasonGlobalSramPdbsReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonGlobalSramPdbsReject, 0);
        data->index = 2;
    }
    if (bcmCosqDropReasonDropPrecedenceLevelReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonDropPrecedenceLevelReject, 0);
        data->index = 3;
    }
    if (bcmCosqDropReasonQueueNumResolutionErrorReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonQueueNumResolutionErrorReject, 0);
        data->index = 4;
    }
    if (bcmCosqDropReasonQueueNumNotValidReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonQueueNumNotValidReject, 0);
        data->index = 5;
    }
    if (bcmCosqDropReasonMulticastReplicationErrorReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonMulticastReplicationErrorReject, 0);
        data->index = 6;
    }
    if (bcmCosqDropReasonMulticastFifoFullReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonMulticastFifoFullReject, 0);
        data->index = 7;
    }
    if (bcmCosqDropReasonTarFifoFullReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonTarFifoFullReject, 0);
        data->index = 8;
    }
    if (bcmCosqDropReasonPacketSizeErrorReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonPacketSizeErrorReject, 0);
        data->index = 9;
    }
    if (bcmCosqDropReasonSramResourceErrorReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonSramResourceErrorReject, 0);
        data->index = 10;
    }
    if (bcmCosqDropReasonExternalErrorReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonExternalErrorReject, 0);
        data->index = 11;
    }
    if (bcmCosqDropReasonVoqSramPdsTotalFreeSharedReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVoqSramPdsTotalFreeSharedReject, 0);
        data->index = 12;
    }
    if (bcmCosqDropReasonVoqSramPdsSharedMaxSizeReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVoqSramPdsSharedMaxSizeReject, 0);
        data->index = 13;
    }
    if (bcmCosqDropReasonVoqSramBuffersTotalFreeSharedReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVoqSramBuffersTotalFreeSharedReject, 0);
        data->index = 14;
    }
    if (bcmCosqDropReasonVoqSramBuffersSharedMaxSizeReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVoqSramBuffersSharedMaxSizeReject, 0);
        data->index = 15;
    }
    if (bcmCosqDropReasonVoqWordsTotalFreeSharedReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVoqWordsTotalFreeSharedReject, 0);
        data->index = 16;
    }
    if (bcmCosqDropReasonVoqWordsSharedMaxSizeReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVoqWordsSharedMaxSizeReject, 0);
        data->index = 17;
    }
    if (bcmCosqDropReasonVoqSystemRedReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVoqSystemRedReject, 0);
        data->index = 18;
    }
    if (bcmCosqDropReasonVoqWredReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVoqWredReject, 0);
        data->index = 19;
    }
    if (bcmCosqDropReasonVoqDramBlockReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVoqDramBlockReject, 0);
        data->index = 20;
    }
    if (bcmCosqDropReasonPbVsqSramPdsTotalFreeSharedReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonPbVsqSramPdsTotalFreeSharedReject, 0);
        data->index = 21;
    }
    if (bcmCosqDropReasonPbVsqSramPdsSharedMaxSizeReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonPbVsqSramPdsSharedMaxSizeReject, 0);
        data->index = 22;
    }
    if (bcmCosqDropReasonVsqDSramPdsSharedMaxSizeReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVsqDSramPdsSharedMaxSizeReject, 0);
        data->index = 23;
    }
    if (bcmCosqDropReasonVsqCSramPdsSharedMaxSizeReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVsqCSramPdsSharedMaxSizeReject, 0);
        data->index = 24;
    }
    if (bcmCosqDropReasonVsqBSramPdsSharedMaxSizeReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVsqBSramPdsSharedMaxSizeReject, 0);
        data->index = 25;
    }
    if (bcmCosqDropReasonVsqASramPdsSharedMaxSizeReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVsqASramPdsSharedMaxSizeReject, 0);
        data->index = 26;
    }
    if (bcmCosqDropReasonPbVsqSramBuffersTotalFreeSharedReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonPbVsqSramBuffersTotalFreeSharedReject, 0);
        data->index = 27;
    }
    if (bcmCosqDropReasonPbVsqSramBuffersSharedMaxSizeReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonPbVsqSramBuffersSharedMaxSizeReject, 0);
        data->index = 28;
    }
    if (bcmCosqDropReasonVsqDSramBuffersSharedMaxSizeReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVsqDSramBuffersSharedMaxSizeReject, 0);
        data->index = 29;
    }
    if (bcmCosqDropReasonVsqCSramBuffersSharedMaxSizeReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVsqCSramBuffersSharedMaxSizeReject, 0);
        data->index = 30;
    }
    if (bcmCosqDropReasonVsqBSramBuffersSharedMaxSizeReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVsqBSramBuffersSharedMaxSizeReject, 0);
        data->index = 31;
    }
    if (bcmCosqDropReasonVsqASramBuffersSharedMaxSizeReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVsqASramBuffersSharedMaxSizeReject, 0);
        data->index = 32;
    }
    if (bcmCosqDropReasonPbVsqWordsTotalFreeSharedReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonPbVsqWordsTotalFreeSharedReject, 0);
        data->index = 33;
    }
    if (bcmCosqDropReasonPbVsqWordsSharedMaxSizeReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonPbVsqWordsSharedMaxSizeReject, 0);
        data->index = 34;
    }
    if (bcmCosqDropReasonVsqDWordsSharedMaxSizeReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVsqDWordsSharedMaxSizeReject, 0);
        data->index = 35;
    }
    if (bcmCosqDropReasonVsqCWordsSharedMaxSizeReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVsqCWordsSharedMaxSizeReject, 0);
        data->index = 36;
    }
    if (bcmCosqDropReasonVsqBWordsSharedMaxSizeReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVsqBWordsSharedMaxSizeReject, 0);
        data->index = 37;
    }
    if (bcmCosqDropReasonVsqAWordsSharedMaxSizeReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVsqAWordsSharedMaxSizeReject, 0);
        data->index = 38;
    }
    if (bcmCosqDropReasonVsqFWredReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVsqFWredReject, 0);
        data->index = 39;
    }
    if (bcmCosqDropReasonVsqEWredReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVsqEWredReject, 0);
        data->index = 40;
    }
    if (bcmCosqDropReasonVsqDWredReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVsqDWredReject, 0);
        data->index = 41;
    }
    if (bcmCosqDropReasonVsqCWredReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVsqCWredReject, 0);
        data->index = 42;
    }
    if (bcmCosqDropReasonVsqBWredReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVsqBWredReject, 0);
        data->index = 43;
    }
    if (bcmCosqDropReasonVsqAWredReject < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reason_index_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmCosqDropReasonVsqAWredReject, 0);
        data->index = 44;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}


static shr_error_e
jr2_a0_dnx_data_stat_drop_reasons_drop_reasons_groups_set(
    int unit)
{
    int name_index;
    dnx_data_stat_drop_reasons_drop_reasons_groups_t *data, *default_data;
    dnxc_data_table_t *table;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_drop_reasons;
    int table_index = dnx_data_stat_drop_reasons_table_drop_reasons_groups;
    SHR_FUNC_INIT_VARS(unit);

    table = &_dnxc_data[unit].modules[module_index].submodules[submodule_index].tables[table_index];
    
    table->flags |= DNXC_DATA_F_SUPPORTED;

    
    table->keys[0].size = bcmStatCounterGroupFilterCount;
    table->info_get.key_size[0] = bcmStatCounterGroupFilterCount;

    
    table->values[0].default_val = "bcmCosqDropReasonRejectCount";
    
    if (table->keys[0].size == 0 || table->info_get.key_size[0] == 0)
    {
        SHR_EXIT();
    }

    
    DNXC_DATA_ALLOC(table->data, dnx_data_stat_drop_reasons_drop_reasons_groups_t, (1 * (table->keys[0].size) + 1  ), "data of dnx_data_stat_drop_reasons_table_drop_reasons_groups");

    
    default_data = (dnx_data_stat_drop_reasons_drop_reasons_groups_t *) dnxc_data_mgmt_table_data_get(unit, table, -1, -1);
    default_data->drop_reasons[0] = bcmCosqDropReasonRejectCount;
    
    for (name_index = 0; name_index < table->keys[0].size; name_index++)
    {
        data = (dnx_data_stat_drop_reasons_drop_reasons_groups_t *) dnxc_data_mgmt_table_data_get(unit, table, name_index, 0);
        sal_memcpy(data, default_data, table->size_of_values);
    }
    
    if (bcmStatCounterGroupFilterGlobalResourcesDrop < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reasons_groups_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmStatCounterGroupFilterGlobalResourcesDrop, 0);
        SHR_RANGE_VERIFY(4, 0, DNX_DATA_MAX_STAT_DROP_REASONS_NOF_DROP_REASONS, _SHR_E_INTERNAL, "out of bound access to array")
        data->drop_reasons[0] = bcmCosqDropReasonGlobalDramBdbsReject;
        data->drop_reasons[1] = bcmCosqDropReasonGlobalSramBuffersReject;
        data->drop_reasons[2] = bcmCosqDropReasonGlobalSramPdbsReject;
        data->drop_reasons[3] = bcmCosqDropReasonRejectCount;
    }
    if (bcmStatCounterGroupFilterVoqResourcesDrop < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reasons_groups_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmStatCounterGroupFilterVoqResourcesDrop, 0);
        SHR_RANGE_VERIFY(3, 0, DNX_DATA_MAX_STAT_DROP_REASONS_NOF_DROP_REASONS, _SHR_E_INTERNAL, "out of bound access to array")
        data->drop_reasons[0] = bcmCosqDropReasonVoqWordsTotalFreeSharedReject;
        data->drop_reasons[1] = bcmCosqDropReasonVoqWordsSharedMaxSizeReject;
        data->drop_reasons[2] = bcmCosqDropReasonRejectCount;
    }
    if (bcmStatCounterGroupFilterWredDrop < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reasons_groups_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmStatCounterGroupFilterWredDrop, 0);
        SHR_RANGE_VERIFY(9, 0, DNX_DATA_MAX_STAT_DROP_REASONS_NOF_DROP_REASONS, _SHR_E_INTERNAL, "out of bound access to array")
        data->drop_reasons[0] = bcmCosqDropReasonVoqSystemRedReject;
        data->drop_reasons[1] = bcmCosqDropReasonVoqWredReject;
        data->drop_reasons[2] = bcmCosqDropReasonVsqFWredReject;
        data->drop_reasons[3] = bcmCosqDropReasonVsqEWredReject;
        data->drop_reasons[4] = bcmCosqDropReasonVsqDWredReject;
        data->drop_reasons[5] = bcmCosqDropReasonVsqCWredReject;
        data->drop_reasons[6] = bcmCosqDropReasonVsqBWredReject;
        data->drop_reasons[7] = bcmCosqDropReasonVsqAWredReject;
        data->drop_reasons[8] = bcmCosqDropReasonRejectCount;
    }
    if (bcmStatCounterGroupFilterOcbResourcesDrop < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reasons_groups_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmStatCounterGroupFilterOcbResourcesDrop, 0);
        SHR_RANGE_VERIFY(5, 0, DNX_DATA_MAX_STAT_DROP_REASONS_NOF_DROP_REASONS, _SHR_E_INTERNAL, "out of bound access to array")
        data->drop_reasons[0] = bcmCosqDropReasonVoqSramPdsTotalFreeSharedReject;
        data->drop_reasons[1] = bcmCosqDropReasonVoqSramPdsSharedMaxSizeReject;
        data->drop_reasons[2] = bcmCosqDropReasonVoqSramBuffersTotalFreeSharedReject;
        data->drop_reasons[3] = bcmCosqDropReasonVoqSramBuffersSharedMaxSizeReject;
        data->drop_reasons[4] = bcmCosqDropReasonRejectCount;
    }
    if (bcmStatCounterGroupFilterVsqResourcesDrop < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reasons_groups_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmStatCounterGroupFilterVsqResourcesDrop, 0);
        SHR_RANGE_VERIFY(19, 0, DNX_DATA_MAX_STAT_DROP_REASONS_NOF_DROP_REASONS, _SHR_E_INTERNAL, "out of bound access to array")
        data->drop_reasons[0] = bcmCosqDropReasonPbVsqSramPdsTotalFreeSharedReject;
        data->drop_reasons[1] = bcmCosqDropReasonPbVsqSramPdsSharedMaxSizeReject;
        data->drop_reasons[2] = bcmCosqDropReasonVsqDSramPdsSharedMaxSizeReject;
        data->drop_reasons[3] = bcmCosqDropReasonVsqCSramPdsSharedMaxSizeReject;
        data->drop_reasons[4] = bcmCosqDropReasonVsqBSramPdsSharedMaxSizeReject;
        data->drop_reasons[5] = bcmCosqDropReasonVsqASramPdsSharedMaxSizeReject;
        data->drop_reasons[6] = bcmCosqDropReasonPbVsqSramBuffersTotalFreeSharedReject;
        data->drop_reasons[7] = bcmCosqDropReasonPbVsqSramBuffersSharedMaxSizeReject;
        data->drop_reasons[8] = bcmCosqDropReasonVsqDSramBuffersSharedMaxSizeReject;
        data->drop_reasons[9] = bcmCosqDropReasonVsqCSramBuffersSharedMaxSizeReject;
        data->drop_reasons[10] = bcmCosqDropReasonVsqBSramBuffersSharedMaxSizeReject;
        data->drop_reasons[11] = bcmCosqDropReasonVsqASramBuffersSharedMaxSizeReject;
        data->drop_reasons[12] = bcmCosqDropReasonPbVsqWordsTotalFreeSharedReject;
        data->drop_reasons[13] = bcmCosqDropReasonPbVsqWordsSharedMaxSizeReject;
        data->drop_reasons[14] = bcmCosqDropReasonVsqDWordsSharedMaxSizeReject;
        data->drop_reasons[15] = bcmCosqDropReasonVsqCWordsSharedMaxSizeReject;
        data->drop_reasons[16] = bcmCosqDropReasonVsqBWordsSharedMaxSizeReject;
        data->drop_reasons[17] = bcmCosqDropReasonVsqAWordsSharedMaxSizeReject;
        data->drop_reasons[18] = bcmCosqDropReasonRejectCount;
    }
    if (bcmStatCounterGroupFilterMiscDrop < table->keys[0].size)
    {
        data = (dnx_data_stat_drop_reasons_drop_reasons_groups_t *) dnxc_data_mgmt_table_data_get(unit, table, bcmStatCounterGroupFilterMiscDrop, 0);
        SHR_RANGE_VERIFY(10, 0, DNX_DATA_MAX_STAT_DROP_REASONS_NOF_DROP_REASONS, _SHR_E_INTERNAL, "out of bound access to array")
        data->drop_reasons[0] = bcmCosqDropReasonDropPrecedenceLevelReject;
        data->drop_reasons[1] = bcmCosqDropReasonQueueNumResolutionErrorReject;
        data->drop_reasons[2] = bcmCosqDropReasonQueueNumNotValidReject;
        data->drop_reasons[3] = bcmCosqDropReasonMulticastReplicationErrorReject;
        data->drop_reasons[4] = bcmCosqDropReasonMulticastFifoFullReject;
        data->drop_reasons[5] = bcmCosqDropReasonTarFifoFullReject;
        data->drop_reasons[6] = bcmCosqDropReasonPacketSizeErrorReject;
        data->drop_reasons[7] = bcmCosqDropReasonSramResourceErrorReject;
        data->drop_reasons[8] = bcmCosqDropReasonVoqDramBlockReject;
        data->drop_reasons[9] = bcmCosqDropReasonRejectCount;
    }

    
    SHR_IF_ERR_EXIT(dnxc_data_dyn_loader_table_value_set(unit, table));


exit:
    SHR_FUNC_EXIT;
}





static shr_error_e
jr2_a0_dnx_data_stat_feature_itpp_cud_count_always_stamp_set(
    int unit)
{
    dnxc_data_feature_t *feature;
    int module_index = dnx_data_module_stat;
    int submodule_index = dnx_data_stat_submodule_feature;
    int feature_index = dnx_data_stat_feature_itpp_cud_count_always_stamp;
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
jr2_a0_data_stat_attach(
    int unit)
{
    dnxc_data_module_t *module = NULL;
    dnxc_data_submodule_t *submodule = NULL;
    dnxc_data_define_t *define = NULL;
    dnxc_data_feature_t *feature = NULL;
    dnxc_data_table_t *table = NULL;
    int module_index = dnx_data_module_stat;
    int submodule_index = -1, data_index = -1;
    SHR_FUNC_INIT_VARS(unit);

    COMPILER_REFERENCE(define);
    COMPILER_REFERENCE(feature);
    COMPILER_REFERENCE(table);
    COMPILER_REFERENCE(submodule);
    COMPILER_REFERENCE(data_index);
    COMPILER_REFERENCE(submodule_index);
    module = &_dnxc_data[unit].modules[module_index];
    
    submodule_index = dnx_data_stat_submodule_stat_pp;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_stat_stat_pp_define_max_irpp_profile_value;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_stat_stat_pp_max_irpp_profile_value_set;
    data_index = dnx_data_stat_stat_pp_define_max_etpp_profile_value;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_stat_stat_pp_max_etpp_profile_value_set;
    data_index = dnx_data_stat_stat_pp_define_max_etpp_counting_profile_value;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_stat_stat_pp_max_etpp_counting_profile_value_set;
    data_index = dnx_data_stat_stat_pp_define_max_etpp_metering_profile_value;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_stat_stat_pp_max_etpp_metering_profile_value_set;
    data_index = dnx_data_stat_stat_pp_define_max_erpp_profile_value;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_stat_stat_pp_max_erpp_profile_value_set;
    data_index = dnx_data_stat_stat_pp_define_etpp_reversed_stat_cmd;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_stat_stat_pp_etpp_reversed_stat_cmd_set;
    data_index = dnx_data_stat_stat_pp_define_etpp_enc_stat_cmd_is_reversed;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_stat_stat_pp_etpp_enc_stat_cmd_is_reversed_set;
    data_index = dnx_data_stat_stat_pp_define_etpp_egress_vsi_always_pushed;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_stat_stat_pp_etpp_egress_vsi_always_pushed_set;
    data_index = dnx_data_stat_stat_pp_define_irpp_start_profile_value;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_stat_stat_pp_irpp_start_profile_value_set;
    data_index = dnx_data_stat_stat_pp_define_erpp_start_profile_value;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_stat_stat_pp_erpp_start_profile_value_set;
    data_index = dnx_data_stat_stat_pp_define_etpp_start_profile_value;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_stat_stat_pp_etpp_start_profile_value_set;
    data_index = dnx_data_stat_stat_pp_define_etpp_counting_start_profile_value;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_stat_stat_pp_etpp_counting_start_profile_value_set;
    data_index = dnx_data_stat_stat_pp_define_etpp_metering_start_profile_value;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_stat_stat_pp_etpp_metering_start_profile_value_set;
    data_index = dnx_data_stat_stat_pp_define_supported_egress_interface_counter_enum;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_stat_stat_pp_supported_egress_interface_counter_enum_set;

    
    data_index = dnx_data_stat_stat_pp_epp_combined_interfaces;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_stat_stat_pp_epp_combined_interfaces_set;
    data_index = dnx_data_stat_stat_pp_full_stat_support;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_stat_stat_pp_full_stat_support_set;
    data_index = dnx_data_stat_stat_pp_erpp_counter_profile_per_outlif;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_stat_stat_pp_erpp_counter_profile_per_outlif_set;

    
    
    submodule_index = dnx_data_stat_submodule_diag_counter;
    submodule = &module->submodules[submodule_index];

    

    

    
    data_index = dnx_data_stat_diag_counter_table_ovf_info;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_dnx_data_stat_diag_counter_ovf_info_set;
    
    submodule_index = dnx_data_stat_submodule_drop_reasons;
    submodule = &module->submodules[submodule_index];

    
    data_index = dnx_data_stat_drop_reasons_define_nof_drop_reasons;
    define = &submodule->defines[data_index];
    define->set = jr2_a0_dnx_data_stat_drop_reasons_nof_drop_reasons_set;

    

    
    data_index = dnx_data_stat_drop_reasons_table_group_drop_reason_index;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_dnx_data_stat_drop_reasons_group_drop_reason_index_set;
    data_index = dnx_data_stat_drop_reasons_table_drop_reason_index;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_dnx_data_stat_drop_reasons_drop_reason_index_set;
    data_index = dnx_data_stat_drop_reasons_table_drop_reasons_groups;
    table = &submodule->tables[data_index];
    table->set = jr2_a0_dnx_data_stat_drop_reasons_drop_reasons_groups_set;
    
    submodule_index = dnx_data_stat_submodule_feature;
    submodule = &module->submodules[submodule_index];

    

    
    data_index = dnx_data_stat_feature_itpp_cud_count_always_stamp;
    feature = &submodule->features[data_index];
    feature->set = jr2_a0_dnx_data_stat_feature_itpp_cud_count_always_stamp_set;

    

    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


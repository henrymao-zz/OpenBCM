
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_COSQ

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal_sch.h>




extern shr_error_e jr2_a0_data_sch_attach(
    int unit);


extern shr_error_e j2c_a0_data_sch_attach(
    int unit);


extern shr_error_e q2a_a0_data_sch_attach(
    int unit);


extern shr_error_e j2p_a0_data_sch_attach(
    int unit);


extern shr_error_e j2x_a0_data_sch_attach(
    int unit);




static shr_error_e
dnx_data_sch_general_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "general";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_sch_general_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data sch general features");

    submodule_data->features[dnx_data_sch_general_lag_scheduler_supported].name = "lag_scheduler_supported";
    submodule_data->features[dnx_data_sch_general_lag_scheduler_supported].doc = "";
    submodule_data->features[dnx_data_sch_general_lag_scheduler_supported].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_sch_general_fsm_modes_config_supported].name = "fsm_modes_config_supported";
    submodule_data->features[dnx_data_sch_general_fsm_modes_config_supported].doc = "";
    submodule_data->features[dnx_data_sch_general_fsm_modes_config_supported].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_sch_general_calrx_rxi_enable_supported].name = "calrx_rxi_enable_supported";
    submodule_data->features[dnx_data_sch_general_calrx_rxi_enable_supported].doc = "";
    submodule_data->features[dnx_data_sch_general_calrx_rxi_enable_supported].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_sch_general_tcg_mapping_hardcoded].name = "tcg_mapping_hardcoded";
    submodule_data->features[dnx_data_sch_general_tcg_mapping_hardcoded].doc = "";
    submodule_data->features[dnx_data_sch_general_tcg_mapping_hardcoded].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_sch_general_global_tcg_strict_priority].name = "global_tcg_strict_priority";
    submodule_data->features[dnx_data_sch_general_global_tcg_strict_priority].doc = "";
    submodule_data->features[dnx_data_sch_general_global_tcg_strict_priority].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_sch_general_fc_on_channelized_if_only].name = "fc_on_channelized_if_only";
    submodule_data->features[dnx_data_sch_general_fc_on_channelized_if_only].doc = "";
    submodule_data->features[dnx_data_sch_general_fc_on_channelized_if_only].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_sch_general_priority_propagation_on_channelized_if_only].name = "priority_propagation_on_channelized_if_only";
    submodule_data->features[dnx_data_sch_general_priority_propagation_on_channelized_if_only].doc = "";
    submodule_data->features[dnx_data_sch_general_priority_propagation_on_channelized_if_only].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_sch_general_low_rate_connectors_token_count_update].name = "low_rate_connectors_token_count_update";
    submodule_data->features[dnx_data_sch_general_low_rate_connectors_token_count_update].doc = "";
    submodule_data->features[dnx_data_sch_general_low_rate_connectors_token_count_update].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_sch_general_scheduler_allocation_legacy_api_supported].name = "scheduler_allocation_legacy_api_supported";
    submodule_data->features[dnx_data_sch_general_scheduler_allocation_legacy_api_supported].doc = "";
    submodule_data->features[dnx_data_sch_general_scheduler_allocation_legacy_api_supported].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_sch_general_is_used].name = "is_used";
    submodule_data->features[dnx_data_sch_general_is_used].doc = "";
    submodule_data->features[dnx_data_sch_general_is_used].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_sch_general_power_down_supported].name = "power_down_supported";
    submodule_data->features[dnx_data_sch_general_power_down_supported].doc = "";
    submodule_data->features[dnx_data_sch_general_power_down_supported].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnx_data_sch_general_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data sch general defines");

    submodule_data->defines[dnx_data_sch_general_define_nof_slow_profiles].name = "nof_slow_profiles";
    submodule_data->defines[dnx_data_sch_general_define_nof_slow_profiles].doc = "";
    
    submodule_data->defines[dnx_data_sch_general_define_nof_slow_profiles].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_general_define_nof_slow_levels].name = "nof_slow_levels";
    submodule_data->defines[dnx_data_sch_general_define_nof_slow_levels].doc = "";
    
    submodule_data->defines[dnx_data_sch_general_define_nof_slow_levels].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_general_define_cycles_per_credit_token].name = "cycles_per_credit_token";
    submodule_data->defines[dnx_data_sch_general_define_cycles_per_credit_token].doc = "";
    
    submodule_data->defines[dnx_data_sch_general_define_cycles_per_credit_token].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_general_define_nof_fmq_class].name = "nof_fmq_class";
    submodule_data->defines[dnx_data_sch_general_define_nof_fmq_class].doc = "";
    
    submodule_data->defines[dnx_data_sch_general_define_nof_fmq_class].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_general_define_port_priority_propagation_version].name = "port_priority_propagation_version";
    submodule_data->defines[dnx_data_sch_general_define_port_priority_propagation_version].doc = "";
    
    submodule_data->defines[dnx_data_sch_general_define_port_priority_propagation_version].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_general_define_port_priority_propagation_enable].name = "port_priority_propagation_enable";
    submodule_data->defines[dnx_data_sch_general_define_port_priority_propagation_enable].doc = "";
    
    submodule_data->defines[dnx_data_sch_general_define_port_priority_propagation_enable].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_sch_general_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data sch general tables");

    
    submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].name = "low_rate_factor_to_dbal_enum";
    submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].doc = "";
    submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].size_of_values = sizeof(dnx_data_sch_general_low_rate_factor_to_dbal_enum_t);
    submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].entry_get = dnx_data_sch_general_low_rate_factor_to_dbal_enum_entry_str_get;

    
    submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].nof_keys = 1;
    submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].keys[0].name = "low_rate_factor";
    submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].nof_values = 2;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].values, dnxc_data_value_t, submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].nof_values, "_dnx_data_sch_general_table_low_rate_factor_to_dbal_enum table values");
    submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].values[0].name = "dbal_enum";
    submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].values[0].type = "dbal_enum_value_field_low_rate_factor_e";
    submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].values[0].doc = "";
    submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].values[0].offset = UTILEX_OFFSETOF(dnx_data_sch_general_low_rate_factor_to_dbal_enum_t, dbal_enum);
    submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].values[1].name = "valid";
    submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].values[1].type = "int";
    submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].values[1].doc = "";
    submodule_data->tables[dnx_data_sch_general_table_low_rate_factor_to_dbal_enum].values[1].offset = UTILEX_OFFSETOF(dnx_data_sch_general_low_rate_factor_to_dbal_enum_t, valid);

    
    submodule_data->tables[dnx_data_sch_general_table_dbal_enum_to_low_rate_factor].name = "dbal_enum_to_low_rate_factor";
    submodule_data->tables[dnx_data_sch_general_table_dbal_enum_to_low_rate_factor].doc = "";
    submodule_data->tables[dnx_data_sch_general_table_dbal_enum_to_low_rate_factor].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_sch_general_table_dbal_enum_to_low_rate_factor].size_of_values = sizeof(dnx_data_sch_general_dbal_enum_to_low_rate_factor_t);
    submodule_data->tables[dnx_data_sch_general_table_dbal_enum_to_low_rate_factor].entry_get = dnx_data_sch_general_dbal_enum_to_low_rate_factor_entry_str_get;

    
    submodule_data->tables[dnx_data_sch_general_table_dbal_enum_to_low_rate_factor].nof_keys = 1;
    submodule_data->tables[dnx_data_sch_general_table_dbal_enum_to_low_rate_factor].keys[0].name = "dbal_enum";
    submodule_data->tables[dnx_data_sch_general_table_dbal_enum_to_low_rate_factor].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_sch_general_table_dbal_enum_to_low_rate_factor].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_sch_general_table_dbal_enum_to_low_rate_factor].values, dnxc_data_value_t, submodule_data->tables[dnx_data_sch_general_table_dbal_enum_to_low_rate_factor].nof_values, "_dnx_data_sch_general_table_dbal_enum_to_low_rate_factor table values");
    submodule_data->tables[dnx_data_sch_general_table_dbal_enum_to_low_rate_factor].values[0].name = "low_rate_factor";
    submodule_data->tables[dnx_data_sch_general_table_dbal_enum_to_low_rate_factor].values[0].type = "int";
    submodule_data->tables[dnx_data_sch_general_table_dbal_enum_to_low_rate_factor].values[0].doc = "";
    submodule_data->tables[dnx_data_sch_general_table_dbal_enum_to_low_rate_factor].values[0].offset = UTILEX_OFFSETOF(dnx_data_sch_general_dbal_enum_to_low_rate_factor_t, low_rate_factor);

    
    submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].name = "slow_rate_max_bucket";
    submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].doc = "";
    submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].size_of_values = sizeof(dnx_data_sch_general_slow_rate_max_bucket_t);
    submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].entry_get = dnx_data_sch_general_slow_rate_max_bucket_entry_str_get;

    
    submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].nof_keys = 1;
    submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].keys[0].name = "idx";
    submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].nof_values = 2;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].values, dnxc_data_value_t, submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].nof_values, "_dnx_data_sch_general_table_slow_rate_max_bucket table values");
    submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].values[0].name = "rate";
    submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].values[0].type = "int";
    submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].values[0].doc = "";
    submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].values[0].offset = UTILEX_OFFSETOF(dnx_data_sch_general_slow_rate_max_bucket_t, rate);
    submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].values[1].name = "max_bucket";
    submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].values[1].type = "uint32";
    submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].values[1].doc = "";
    submodule_data->tables[dnx_data_sch_general_table_slow_rate_max_bucket].values[1].offset = UTILEX_OFFSETOF(dnx_data_sch_general_slow_rate_max_bucket_t, max_bucket);


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_sch_general_feature_get(
    int unit,
    dnx_data_sch_general_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_general, feature);
}


uint32
dnx_data_sch_general_nof_slow_profiles_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_general, dnx_data_sch_general_define_nof_slow_profiles);
}

uint32
dnx_data_sch_general_nof_slow_levels_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_general, dnx_data_sch_general_define_nof_slow_levels);
}

uint32
dnx_data_sch_general_cycles_per_credit_token_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_general, dnx_data_sch_general_define_cycles_per_credit_token);
}

uint32
dnx_data_sch_general_nof_fmq_class_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_general, dnx_data_sch_general_define_nof_fmq_class);
}

uint32
dnx_data_sch_general_port_priority_propagation_version_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_general, dnx_data_sch_general_define_port_priority_propagation_version);
}

uint32
dnx_data_sch_general_port_priority_propagation_enable_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_general, dnx_data_sch_general_define_port_priority_propagation_enable);
}



const dnx_data_sch_general_low_rate_factor_to_dbal_enum_t *
dnx_data_sch_general_low_rate_factor_to_dbal_enum_get(
    int unit,
    int low_rate_factor)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_general, dnx_data_sch_general_table_low_rate_factor_to_dbal_enum);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, low_rate_factor, 0);
    return (const dnx_data_sch_general_low_rate_factor_to_dbal_enum_t *) data;

}

const dnx_data_sch_general_dbal_enum_to_low_rate_factor_t *
dnx_data_sch_general_dbal_enum_to_low_rate_factor_get(
    int unit,
    int dbal_enum)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_general, dnx_data_sch_general_table_dbal_enum_to_low_rate_factor);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, dbal_enum, 0);
    return (const dnx_data_sch_general_dbal_enum_to_low_rate_factor_t *) data;

}

const dnx_data_sch_general_slow_rate_max_bucket_t *
dnx_data_sch_general_slow_rate_max_bucket_get(
    int unit,
    int idx)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_general, dnx_data_sch_general_table_slow_rate_max_bucket);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, idx, 0);
    return (const dnx_data_sch_general_slow_rate_max_bucket_t *) data;

}


shr_error_e
dnx_data_sch_general_low_rate_factor_to_dbal_enum_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_sch_general_low_rate_factor_to_dbal_enum_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_general, dnx_data_sch_general_table_low_rate_factor_to_dbal_enum);
    data = (const dnx_data_sch_general_low_rate_factor_to_dbal_enum_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->dbal_enum);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->valid);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_sch_general_dbal_enum_to_low_rate_factor_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_sch_general_dbal_enum_to_low_rate_factor_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_general, dnx_data_sch_general_table_dbal_enum_to_low_rate_factor);
    data = (const dnx_data_sch_general_dbal_enum_to_low_rate_factor_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->low_rate_factor);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_sch_general_slow_rate_max_bucket_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_sch_general_slow_rate_max_bucket_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_general, dnx_data_sch_general_table_slow_rate_max_bucket);
    data = (const dnx_data_sch_general_slow_rate_max_bucket_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->rate);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->max_bucket);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnx_data_sch_general_low_rate_factor_to_dbal_enum_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_general, dnx_data_sch_general_table_low_rate_factor_to_dbal_enum);

}

const dnxc_data_table_info_t *
dnx_data_sch_general_dbal_enum_to_low_rate_factor_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_general, dnx_data_sch_general_table_dbal_enum_to_low_rate_factor);

}

const dnxc_data_table_info_t *
dnx_data_sch_general_slow_rate_max_bucket_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_general, dnx_data_sch_general_table_slow_rate_max_bucket);

}






static shr_error_e
dnx_data_sch_ps_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "ps";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_sch_ps_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data sch ps features");

    
    submodule_data->nof_defines = _dnx_data_sch_ps_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data sch ps defines");

    submodule_data->defines[dnx_data_sch_ps_define_min_priority_for_tcg].name = "min_priority_for_tcg";
    submodule_data->defines[dnx_data_sch_ps_define_min_priority_for_tcg].doc = "";
    
    submodule_data->defines[dnx_data_sch_ps_define_min_priority_for_tcg].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_ps_define_max_nof_tcg].name = "max_nof_tcg";
    submodule_data->defines[dnx_data_sch_ps_define_max_nof_tcg].doc = "";
    
    submodule_data->defines[dnx_data_sch_ps_define_max_nof_tcg].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_ps_define_nof_hrs_in_ps].name = "nof_hrs_in_ps";
    submodule_data->defines[dnx_data_sch_ps_define_nof_hrs_in_ps].doc = "";
    
    submodule_data->defines[dnx_data_sch_ps_define_nof_hrs_in_ps].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_ps_define_max_tcg_weight].name = "max_tcg_weight";
    submodule_data->defines[dnx_data_sch_ps_define_max_tcg_weight].doc = "";
    
    submodule_data->defines[dnx_data_sch_ps_define_max_tcg_weight].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_ps_define_tc_tcg_calendar_access_period].name = "tc_tcg_calendar_access_period";
    submodule_data->defines[dnx_data_sch_ps_define_tc_tcg_calendar_access_period].doc = "";
    
    submodule_data->defines[dnx_data_sch_ps_define_tc_tcg_calendar_access_period].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_ps_define_max_port_rate_mbps].name = "max_port_rate_mbps";
    submodule_data->defines[dnx_data_sch_ps_define_max_port_rate_mbps].doc = "";
    
    submodule_data->defines[dnx_data_sch_ps_define_max_port_rate_mbps].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_ps_define_max_burst].name = "max_burst";
    submodule_data->defines[dnx_data_sch_ps_define_max_burst].doc = "";
    
    submodule_data->defines[dnx_data_sch_ps_define_max_burst].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_ps_define_assigned_credit_worth_multiplier].name = "assigned_credit_worth_multiplier";
    submodule_data->defines[dnx_data_sch_ps_define_assigned_credit_worth_multiplier].doc = "";
    
    submodule_data->defines[dnx_data_sch_ps_define_assigned_credit_worth_multiplier].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_sch_ps_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data sch ps tables");


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_sch_ps_feature_get(
    int unit,
    dnx_data_sch_ps_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_ps, feature);
}


uint32
dnx_data_sch_ps_min_priority_for_tcg_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_ps, dnx_data_sch_ps_define_min_priority_for_tcg);
}

uint32
dnx_data_sch_ps_max_nof_tcg_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_ps, dnx_data_sch_ps_define_max_nof_tcg);
}

uint32
dnx_data_sch_ps_nof_hrs_in_ps_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_ps, dnx_data_sch_ps_define_nof_hrs_in_ps);
}

uint32
dnx_data_sch_ps_max_tcg_weight_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_ps, dnx_data_sch_ps_define_max_tcg_weight);
}

uint32
dnx_data_sch_ps_tc_tcg_calendar_access_period_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_ps, dnx_data_sch_ps_define_tc_tcg_calendar_access_period);
}

uint32
dnx_data_sch_ps_max_port_rate_mbps_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_ps, dnx_data_sch_ps_define_max_port_rate_mbps);
}

uint32
dnx_data_sch_ps_max_burst_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_ps, dnx_data_sch_ps_define_max_burst);
}

uint32
dnx_data_sch_ps_assigned_credit_worth_multiplier_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_ps, dnx_data_sch_ps_define_assigned_credit_worth_multiplier);
}










static shr_error_e
dnx_data_sch_flow_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "flow";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_sch_flow_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data sch flow features");

    submodule_data->features[dnx_data_sch_flow_cl_fq_cl_fq_quartet].name = "cl_fq_cl_fq_quartet";
    submodule_data->features[dnx_data_sch_flow_cl_fq_cl_fq_quartet].doc = "";
    submodule_data->features[dnx_data_sch_flow_cl_fq_cl_fq_quartet].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_sch_flow_flex_quartet_supported].name = "flex_quartet_supported";
    submodule_data->features[dnx_data_sch_flow_flex_quartet_supported].doc = "";
    submodule_data->features[dnx_data_sch_flow_flex_quartet_supported].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_sch_flow_interdigitated_supported].name = "interdigitated_supported";
    submodule_data->features[dnx_data_sch_flow_interdigitated_supported].doc = "";
    submodule_data->features[dnx_data_sch_flow_interdigitated_supported].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnx_data_sch_flow_multi_low_rate_ranges].name = "multi_low_rate_ranges";
    submodule_data->features[dnx_data_sch_flow_multi_low_rate_ranges].doc = "";
    submodule_data->features[dnx_data_sch_flow_multi_low_rate_ranges].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnx_data_sch_flow_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data sch flow defines");

    submodule_data->defines[dnx_data_sch_flow_define_nof_hr].name = "nof_hr";
    submodule_data->defines[dnx_data_sch_flow_define_nof_hr].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_nof_hr].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_nof_cl].name = "nof_cl";
    submodule_data->defines[dnx_data_sch_flow_define_nof_cl].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_nof_cl].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_nof_se].name = "nof_se";
    submodule_data->defines[dnx_data_sch_flow_define_nof_se].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_nof_se].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_nof_flows].name = "nof_flows";
    submodule_data->defines[dnx_data_sch_flow_define_nof_flows].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_nof_flows].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_region_size].name = "region_size";
    submodule_data->defines[dnx_data_sch_flow_define_region_size].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_region_size].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_nof_regions].name = "nof_regions";
    submodule_data->defines[dnx_data_sch_flow_define_nof_regions].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_nof_regions].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_nof_hr_regions].name = "nof_hr_regions";
    submodule_data->defines[dnx_data_sch_flow_define_nof_hr_regions].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_nof_hr_regions].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_nof_connectors_only_regions].name = "nof_connectors_only_regions";
    submodule_data->defines[dnx_data_sch_flow_define_nof_connectors_only_regions].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_nof_connectors_only_regions].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_flow_in_region_mask].name = "flow_in_region_mask";
    submodule_data->defines[dnx_data_sch_flow_define_flow_in_region_mask].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_flow_in_region_mask].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_min_connector_bundle_size].name = "min_connector_bundle_size";
    submodule_data->defines[dnx_data_sch_flow_define_min_connector_bundle_size].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_min_connector_bundle_size].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_conn_idx_interdig_flow].name = "conn_idx_interdig_flow";
    submodule_data->defines[dnx_data_sch_flow_define_conn_idx_interdig_flow].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_conn_idx_interdig_flow].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_shaper_flipflops_nof].name = "shaper_flipflops_nof";
    submodule_data->defines[dnx_data_sch_flow_define_shaper_flipflops_nof].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_shaper_flipflops_nof].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_nof_flows_in_quartet_order_group].name = "nof_flows_in_quartet_order_group";
    submodule_data->defines[dnx_data_sch_flow_define_nof_flows_in_quartet_order_group].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_nof_flows_in_quartet_order_group].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_nof_regions_in_quartet_order_group].name = "nof_regions_in_quartet_order_group";
    submodule_data->defines[dnx_data_sch_flow_define_nof_regions_in_quartet_order_group].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_nof_regions_in_quartet_order_group].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_nof_quartet_order_groups].name = "nof_quartet_order_groups";
    submodule_data->defines[dnx_data_sch_flow_define_nof_quartet_order_groups].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_nof_quartet_order_groups].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_nof_low_rate_ranges].name = "nof_low_rate_ranges";
    submodule_data->defines[dnx_data_sch_flow_define_nof_low_rate_ranges].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_nof_low_rate_ranges].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_nof_low_rate_regions].name = "nof_low_rate_regions";
    submodule_data->defines[dnx_data_sch_flow_define_nof_low_rate_regions].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_nof_low_rate_regions].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_low_rate_pattern_mask].name = "low_rate_pattern_mask";
    submodule_data->defines[dnx_data_sch_flow_define_low_rate_pattern_mask].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_low_rate_pattern_mask].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_low_rate_flow_resolution].name = "low_rate_flow_resolution";
    submodule_data->defines[dnx_data_sch_flow_define_low_rate_flow_resolution].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_low_rate_flow_resolution].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_flow_define_erp_hr].name = "erp_hr";
    submodule_data->defines[dnx_data_sch_flow_define_erp_hr].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_erp_hr].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_flow_define_reserved_hr].name = "reserved_hr";
    submodule_data->defines[dnx_data_sch_flow_define_reserved_hr].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_reserved_hr].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_flow_define_max_se].name = "max_se";
    submodule_data->defines[dnx_data_sch_flow_define_max_se].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_max_se].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_flow_define_max_flow].name = "max_flow";
    submodule_data->defines[dnx_data_sch_flow_define_max_flow].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_max_flow].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_flow_define_first_hr_region].name = "first_hr_region";
    submodule_data->defines[dnx_data_sch_flow_define_first_hr_region].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_first_hr_region].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_flow_define_first_se_flow_id].name = "first_se_flow_id";
    submodule_data->defines[dnx_data_sch_flow_define_first_se_flow_id].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_first_se_flow_id].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_flow_define_hr_se_id_min].name = "hr_se_id_min";
    submodule_data->defines[dnx_data_sch_flow_define_hr_se_id_min].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_hr_se_id_min].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_flow_define_hr_se_id_max].name = "hr_se_id_max";
    submodule_data->defines[dnx_data_sch_flow_define_hr_se_id_max].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_hr_se_id_max].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_flow_define_virtual_flow_mapped_queue].name = "virtual_flow_mapped_queue";
    submodule_data->defines[dnx_data_sch_flow_define_virtual_flow_mapped_queue].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_virtual_flow_mapped_queue].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_flow_define_default_credit_source_se_id].name = "default_credit_source_se_id";
    submodule_data->defines[dnx_data_sch_flow_define_default_credit_source_se_id].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_default_credit_source_se_id].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_flow_define_runtime_performance_optimize_enable_sched_allocation].name = "runtime_performance_optimize_enable_sched_allocation";
    submodule_data->defines[dnx_data_sch_flow_define_runtime_performance_optimize_enable_sched_allocation].doc = "";
    
    submodule_data->defines[dnx_data_sch_flow_define_runtime_performance_optimize_enable_sched_allocation].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_sch_flow_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data sch flow tables");

    
    submodule_data->tables[dnx_data_sch_flow_table_region_type].name = "region_type";
    submodule_data->tables[dnx_data_sch_flow_table_region_type].doc = "";
    submodule_data->tables[dnx_data_sch_flow_table_region_type].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_sch_flow_table_region_type].size_of_values = sizeof(dnx_data_sch_flow_region_type_t);
    submodule_data->tables[dnx_data_sch_flow_table_region_type].entry_get = dnx_data_sch_flow_region_type_entry_str_get;

    
    submodule_data->tables[dnx_data_sch_flow_table_region_type].nof_keys = 2;
    submodule_data->tables[dnx_data_sch_flow_table_region_type].keys[0].name = "core";
    submodule_data->tables[dnx_data_sch_flow_table_region_type].keys[0].doc = "";
    submodule_data->tables[dnx_data_sch_flow_table_region_type].keys[1].name = "region";
    submodule_data->tables[dnx_data_sch_flow_table_region_type].keys[1].doc = "";

    
    submodule_data->tables[dnx_data_sch_flow_table_region_type].nof_values = 2;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_sch_flow_table_region_type].values, dnxc_data_value_t, submodule_data->tables[dnx_data_sch_flow_table_region_type].nof_values, "_dnx_data_sch_flow_table_region_type table values");
    submodule_data->tables[dnx_data_sch_flow_table_region_type].values[0].name = "type";
    submodule_data->tables[dnx_data_sch_flow_table_region_type].values[0].type = "uint32";
    submodule_data->tables[dnx_data_sch_flow_table_region_type].values[0].doc = "";
    submodule_data->tables[dnx_data_sch_flow_table_region_type].values[0].offset = UTILEX_OFFSETOF(dnx_data_sch_flow_region_type_t, type);
    submodule_data->tables[dnx_data_sch_flow_table_region_type].values[1].name = "propagation_direction";
    submodule_data->tables[dnx_data_sch_flow_table_region_type].values[1].type = "uint32";
    submodule_data->tables[dnx_data_sch_flow_table_region_type].values[1].doc = "";
    submodule_data->tables[dnx_data_sch_flow_table_region_type].values[1].offset = UTILEX_OFFSETOF(dnx_data_sch_flow_region_type_t, propagation_direction);

    
    submodule_data->tables[dnx_data_sch_flow_table_nof_remote_cores].name = "nof_remote_cores";
    submodule_data->tables[dnx_data_sch_flow_table_nof_remote_cores].doc = "";
    submodule_data->tables[dnx_data_sch_flow_table_nof_remote_cores].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_sch_flow_table_nof_remote_cores].size_of_values = sizeof(dnx_data_sch_flow_nof_remote_cores_t);
    submodule_data->tables[dnx_data_sch_flow_table_nof_remote_cores].entry_get = dnx_data_sch_flow_nof_remote_cores_entry_str_get;

    
    submodule_data->tables[dnx_data_sch_flow_table_nof_remote_cores].nof_keys = 2;
    submodule_data->tables[dnx_data_sch_flow_table_nof_remote_cores].keys[0].name = "core";
    submodule_data->tables[dnx_data_sch_flow_table_nof_remote_cores].keys[0].doc = "";
    submodule_data->tables[dnx_data_sch_flow_table_nof_remote_cores].keys[1].name = "region";
    submodule_data->tables[dnx_data_sch_flow_table_nof_remote_cores].keys[1].doc = "";

    
    submodule_data->tables[dnx_data_sch_flow_table_nof_remote_cores].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_sch_flow_table_nof_remote_cores].values, dnxc_data_value_t, submodule_data->tables[dnx_data_sch_flow_table_nof_remote_cores].nof_values, "_dnx_data_sch_flow_table_nof_remote_cores table values");
    submodule_data->tables[dnx_data_sch_flow_table_nof_remote_cores].values[0].name = "val";
    submodule_data->tables[dnx_data_sch_flow_table_nof_remote_cores].values[0].type = "uint32";
    submodule_data->tables[dnx_data_sch_flow_table_nof_remote_cores].values[0].doc = "";
    submodule_data->tables[dnx_data_sch_flow_table_nof_remote_cores].values[0].offset = UTILEX_OFFSETOF(dnx_data_sch_flow_nof_remote_cores_t, val);

    
    submodule_data->tables[dnx_data_sch_flow_table_quartet_type].name = "quartet_type";
    submodule_data->tables[dnx_data_sch_flow_table_quartet_type].doc = "";
    submodule_data->tables[dnx_data_sch_flow_table_quartet_type].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_sch_flow_table_quartet_type].size_of_values = sizeof(dnx_data_sch_flow_quartet_type_t);
    submodule_data->tables[dnx_data_sch_flow_table_quartet_type].entry_get = dnx_data_sch_flow_quartet_type_entry_str_get;

    
    submodule_data->tables[dnx_data_sch_flow_table_quartet_type].nof_keys = 2;
    submodule_data->tables[dnx_data_sch_flow_table_quartet_type].keys[0].name = "core";
    submodule_data->tables[dnx_data_sch_flow_table_quartet_type].keys[0].doc = "";
    submodule_data->tables[dnx_data_sch_flow_table_quartet_type].keys[1].name = "group";
    submodule_data->tables[dnx_data_sch_flow_table_quartet_type].keys[1].doc = "";

    
    submodule_data->tables[dnx_data_sch_flow_table_quartet_type].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_sch_flow_table_quartet_type].values, dnxc_data_value_t, submodule_data->tables[dnx_data_sch_flow_table_quartet_type].nof_values, "_dnx_data_sch_flow_table_quartet_type table values");
    submodule_data->tables[dnx_data_sch_flow_table_quartet_type].values[0].name = "type";
    submodule_data->tables[dnx_data_sch_flow_table_quartet_type].values[0].type = "uint32";
    submodule_data->tables[dnx_data_sch_flow_table_quartet_type].values[0].doc = "";
    submodule_data->tables[dnx_data_sch_flow_table_quartet_type].values[0].offset = UTILEX_OFFSETOF(dnx_data_sch_flow_quartet_type_t, type);

    
    submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].name = "quartet_index_conversion";
    submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].doc = "";
    submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].size_of_values = sizeof(dnx_data_sch_flow_quartet_index_conversion_t);
    submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].entry_get = dnx_data_sch_flow_quartet_index_conversion_entry_str_get;

    
    submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].nof_keys = 1;
    submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].keys[0].name = "quartet_type";
    submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].nof_values = 2;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].values, dnxc_data_value_t, submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].nof_values, "_dnx_data_sch_flow_table_quartet_index_conversion table values");
    submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].values[0].name = "flow_to_se";
    submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].values[0].type = "uint32[4]";
    submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].values[0].doc = "";
    submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].values[0].offset = UTILEX_OFFSETOF(dnx_data_sch_flow_quartet_index_conversion_t, flow_to_se);
    submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].values[1].name = "se_to_flow";
    submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].values[1].type = "uint32[4]";
    submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].values[1].doc = "";
    submodule_data->tables[dnx_data_sch_flow_table_quartet_index_conversion].values[1].offset = UTILEX_OFFSETOF(dnx_data_sch_flow_quartet_index_conversion_t, se_to_flow);


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_sch_flow_feature_get(
    int unit,
    dnx_data_sch_flow_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, feature);
}


uint32
dnx_data_sch_flow_nof_hr_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_nof_hr);
}

uint32
dnx_data_sch_flow_nof_cl_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_nof_cl);
}

uint32
dnx_data_sch_flow_nof_se_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_nof_se);
}

uint32
dnx_data_sch_flow_nof_flows_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_nof_flows);
}

uint32
dnx_data_sch_flow_region_size_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_region_size);
}

uint32
dnx_data_sch_flow_nof_regions_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_nof_regions);
}

uint32
dnx_data_sch_flow_nof_hr_regions_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_nof_hr_regions);
}

uint32
dnx_data_sch_flow_nof_connectors_only_regions_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_nof_connectors_only_regions);
}

uint32
dnx_data_sch_flow_flow_in_region_mask_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_flow_in_region_mask);
}

uint32
dnx_data_sch_flow_min_connector_bundle_size_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_min_connector_bundle_size);
}

uint32
dnx_data_sch_flow_conn_idx_interdig_flow_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_conn_idx_interdig_flow);
}

uint32
dnx_data_sch_flow_shaper_flipflops_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_shaper_flipflops_nof);
}

uint32
dnx_data_sch_flow_nof_flows_in_quartet_order_group_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_nof_flows_in_quartet_order_group);
}

uint32
dnx_data_sch_flow_nof_regions_in_quartet_order_group_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_nof_regions_in_quartet_order_group);
}

uint32
dnx_data_sch_flow_nof_quartet_order_groups_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_nof_quartet_order_groups);
}

uint32
dnx_data_sch_flow_nof_low_rate_ranges_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_nof_low_rate_ranges);
}

uint32
dnx_data_sch_flow_nof_low_rate_regions_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_nof_low_rate_regions);
}

uint32
dnx_data_sch_flow_low_rate_pattern_mask_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_low_rate_pattern_mask);
}

uint32
dnx_data_sch_flow_low_rate_flow_resolution_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_low_rate_flow_resolution);
}

uint32
dnx_data_sch_flow_erp_hr_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_erp_hr);
}

uint32
dnx_data_sch_flow_reserved_hr_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_reserved_hr);
}

uint32
dnx_data_sch_flow_max_se_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_max_se);
}

uint32
dnx_data_sch_flow_max_flow_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_max_flow);
}

uint32
dnx_data_sch_flow_first_hr_region_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_first_hr_region);
}

uint32
dnx_data_sch_flow_first_se_flow_id_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_first_se_flow_id);
}

uint32
dnx_data_sch_flow_hr_se_id_min_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_hr_se_id_min);
}

uint32
dnx_data_sch_flow_hr_se_id_max_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_hr_se_id_max);
}

uint32
dnx_data_sch_flow_virtual_flow_mapped_queue_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_virtual_flow_mapped_queue);
}

uint32
dnx_data_sch_flow_default_credit_source_se_id_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_default_credit_source_se_id);
}

uint32
dnx_data_sch_flow_runtime_performance_optimize_enable_sched_allocation_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_define_runtime_performance_optimize_enable_sched_allocation);
}



const dnx_data_sch_flow_region_type_t *
dnx_data_sch_flow_region_type_get(
    int unit,
    int core,
    int region)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_table_region_type);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, core, region);
    return (const dnx_data_sch_flow_region_type_t *) data;

}

const dnx_data_sch_flow_nof_remote_cores_t *
dnx_data_sch_flow_nof_remote_cores_get(
    int unit,
    int core,
    int region)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_table_nof_remote_cores);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, core, region);
    return (const dnx_data_sch_flow_nof_remote_cores_t *) data;

}

const dnx_data_sch_flow_quartet_type_t *
dnx_data_sch_flow_quartet_type_get(
    int unit,
    int core,
    int group)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_table_quartet_type);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, core, group);
    return (const dnx_data_sch_flow_quartet_type_t *) data;

}

const dnx_data_sch_flow_quartet_index_conversion_t *
dnx_data_sch_flow_quartet_index_conversion_get(
    int unit,
    int quartet_type)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_table_quartet_index_conversion);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, quartet_type, 0);
    return (const dnx_data_sch_flow_quartet_index_conversion_t *) data;

}


shr_error_e
dnx_data_sch_flow_region_type_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_sch_flow_region_type_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_table_region_type);
    data = (const dnx_data_sch_flow_region_type_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, key1);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->type);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->propagation_direction);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_sch_flow_nof_remote_cores_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_sch_flow_nof_remote_cores_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_table_nof_remote_cores);
    data = (const dnx_data_sch_flow_nof_remote_cores_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, key1);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->val);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_sch_flow_quartet_type_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_sch_flow_quartet_type_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_table_quartet_type);
    data = (const dnx_data_sch_flow_quartet_type_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, key1);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->type);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_sch_flow_quartet_index_conversion_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_sch_flow_quartet_index_conversion_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_table_quartet_index_conversion);
    data = (const dnx_data_sch_flow_quartet_index_conversion_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            DNXC_DATA_MGMT_ARR_STR(buffer, 4, data->flow_to_se);
            break;
        case 1:
            DNXC_DATA_MGMT_ARR_STR(buffer, 4, data->se_to_flow);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnx_data_sch_flow_region_type_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_table_region_type);

}

const dnxc_data_table_info_t *
dnx_data_sch_flow_nof_remote_cores_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_table_nof_remote_cores);

}

const dnxc_data_table_info_t *
dnx_data_sch_flow_quartet_type_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_table_quartet_type);

}

const dnxc_data_table_info_t *
dnx_data_sch_flow_quartet_index_conversion_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_flow, dnx_data_sch_flow_table_quartet_index_conversion);

}






static shr_error_e
dnx_data_sch_se_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "se";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_sch_se_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data sch se features");

    
    submodule_data->nof_defines = _dnx_data_sch_se_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data sch se defines");

    submodule_data->defines[dnx_data_sch_se_define_default_cos].name = "default_cos";
    submodule_data->defines[dnx_data_sch_se_define_default_cos].doc = "";
    
    submodule_data->defines[dnx_data_sch_se_define_default_cos].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_se_define_nof_color_group].name = "nof_color_group";
    submodule_data->defines[dnx_data_sch_se_define_nof_color_group].doc = "";
    
    submodule_data->defines[dnx_data_sch_se_define_nof_color_group].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_se_define_max_hr_weight].name = "max_hr_weight";
    submodule_data->defines[dnx_data_sch_se_define_max_hr_weight].doc = "";
    
    submodule_data->defines[dnx_data_sch_se_define_max_hr_weight].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_se_define_cl_class_profile_nof].name = "cl_class_profile_nof";
    submodule_data->defines[dnx_data_sch_se_define_cl_class_profile_nof].doc = "";
    
    submodule_data->defines[dnx_data_sch_se_define_cl_class_profile_nof].flags |= DNXC_DATA_F_DEFINE;

    
    submodule_data->nof_tables = _dnx_data_sch_se_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data sch se tables");

    
    submodule_data->tables[dnx_data_sch_se_table_quartet_offset_to_cl_num].name = "quartet_offset_to_cl_num";
    submodule_data->tables[dnx_data_sch_se_table_quartet_offset_to_cl_num].doc = "";
    submodule_data->tables[dnx_data_sch_se_table_quartet_offset_to_cl_num].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_sch_se_table_quartet_offset_to_cl_num].size_of_values = sizeof(dnx_data_sch_se_quartet_offset_to_cl_num_t);
    submodule_data->tables[dnx_data_sch_se_table_quartet_offset_to_cl_num].entry_get = dnx_data_sch_se_quartet_offset_to_cl_num_entry_str_get;

    
    submodule_data->tables[dnx_data_sch_se_table_quartet_offset_to_cl_num].nof_keys = 1;
    submodule_data->tables[dnx_data_sch_se_table_quartet_offset_to_cl_num].keys[0].name = "quartet_offset";
    submodule_data->tables[dnx_data_sch_se_table_quartet_offset_to_cl_num].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_sch_se_table_quartet_offset_to_cl_num].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_sch_se_table_quartet_offset_to_cl_num].values, dnxc_data_value_t, submodule_data->tables[dnx_data_sch_se_table_quartet_offset_to_cl_num].nof_values, "_dnx_data_sch_se_table_quartet_offset_to_cl_num table values");
    submodule_data->tables[dnx_data_sch_se_table_quartet_offset_to_cl_num].values[0].name = "cl_num";
    submodule_data->tables[dnx_data_sch_se_table_quartet_offset_to_cl_num].values[0].type = "int";
    submodule_data->tables[dnx_data_sch_se_table_quartet_offset_to_cl_num].values[0].doc = "";
    submodule_data->tables[dnx_data_sch_se_table_quartet_offset_to_cl_num].values[0].offset = UTILEX_OFFSETOF(dnx_data_sch_se_quartet_offset_to_cl_num_t, cl_num);


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_sch_se_feature_get(
    int unit,
    dnx_data_sch_se_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_se, feature);
}


uint32
dnx_data_sch_se_default_cos_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_se, dnx_data_sch_se_define_default_cos);
}

uint32
dnx_data_sch_se_nof_color_group_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_se, dnx_data_sch_se_define_nof_color_group);
}

uint32
dnx_data_sch_se_max_hr_weight_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_se, dnx_data_sch_se_define_max_hr_weight);
}

uint32
dnx_data_sch_se_cl_class_profile_nof_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_se, dnx_data_sch_se_define_cl_class_profile_nof);
}



const dnx_data_sch_se_quartet_offset_to_cl_num_t *
dnx_data_sch_se_quartet_offset_to_cl_num_get(
    int unit,
    int quartet_offset)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_se, dnx_data_sch_se_table_quartet_offset_to_cl_num);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, quartet_offset, 0);
    return (const dnx_data_sch_se_quartet_offset_to_cl_num_t *) data;

}


shr_error_e
dnx_data_sch_se_quartet_offset_to_cl_num_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_sch_se_quartet_offset_to_cl_num_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_se, dnx_data_sch_se_table_quartet_offset_to_cl_num);
    data = (const dnx_data_sch_se_quartet_offset_to_cl_num_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->cl_num);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnx_data_sch_se_quartet_offset_to_cl_num_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_se, dnx_data_sch_se_table_quartet_offset_to_cl_num);

}






static shr_error_e
dnx_data_sch_interface_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "interface";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_sch_interface_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data sch interface features");

    submodule_data->features[dnx_data_sch_interface_non_channelized_calendar].name = "non_channelized_calendar";
    submodule_data->features[dnx_data_sch_interface_non_channelized_calendar].doc = "";
    submodule_data->features[dnx_data_sch_interface_non_channelized_calendar].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnx_data_sch_interface_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data sch interface defines");

    submodule_data->defines[dnx_data_sch_interface_define_nof_big_calendars].name = "nof_big_calendars";
    submodule_data->defines[dnx_data_sch_interface_define_nof_big_calendars].doc = "";
    
    submodule_data->defines[dnx_data_sch_interface_define_nof_big_calendars].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_interface_define_nof_channelized_calendars].name = "nof_channelized_calendars";
    submodule_data->defines[dnx_data_sch_interface_define_nof_channelized_calendars].doc = "";
    
    submodule_data->defines[dnx_data_sch_interface_define_nof_channelized_calendars].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_interface_define_max_calendar_size].name = "max_calendar_size";
    submodule_data->defines[dnx_data_sch_interface_define_max_calendar_size].doc = "";
    
    submodule_data->defines[dnx_data_sch_interface_define_max_calendar_size].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_interface_define_nof_sch_interfaces].name = "nof_sch_interfaces";
    submodule_data->defines[dnx_data_sch_interface_define_nof_sch_interfaces].doc = "";
    
    submodule_data->defines[dnx_data_sch_interface_define_nof_sch_interfaces].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_interface_define_cal_speed_resolution].name = "cal_speed_resolution";
    submodule_data->defines[dnx_data_sch_interface_define_cal_speed_resolution].doc = "";
    
    submodule_data->defines[dnx_data_sch_interface_define_cal_speed_resolution].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_interface_define_reserved].name = "reserved";
    submodule_data->defines[dnx_data_sch_interface_define_reserved].doc = "";
    
    submodule_data->defines[dnx_data_sch_interface_define_reserved].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_interface_define_max_if_rate_mbps].name = "max_if_rate_mbps";
    submodule_data->defines[dnx_data_sch_interface_define_max_if_rate_mbps].doc = "";
    
    submodule_data->defines[dnx_data_sch_interface_define_max_if_rate_mbps].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_sch_interface_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data sch interface tables");

    
    submodule_data->tables[dnx_data_sch_interface_table_shaper_resolution].name = "shaper_resolution";
    submodule_data->tables[dnx_data_sch_interface_table_shaper_resolution].doc = "";
    submodule_data->tables[dnx_data_sch_interface_table_shaper_resolution].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_sch_interface_table_shaper_resolution].size_of_values = sizeof(dnx_data_sch_interface_shaper_resolution_t);
    submodule_data->tables[dnx_data_sch_interface_table_shaper_resolution].entry_get = dnx_data_sch_interface_shaper_resolution_entry_str_get;

    
    submodule_data->tables[dnx_data_sch_interface_table_shaper_resolution].nof_keys = 1;
    submodule_data->tables[dnx_data_sch_interface_table_shaper_resolution].keys[0].name = "channelized";
    submodule_data->tables[dnx_data_sch_interface_table_shaper_resolution].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_sch_interface_table_shaper_resolution].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_sch_interface_table_shaper_resolution].values, dnxc_data_value_t, submodule_data->tables[dnx_data_sch_interface_table_shaper_resolution].nof_values, "_dnx_data_sch_interface_table_shaper_resolution table values");
    submodule_data->tables[dnx_data_sch_interface_table_shaper_resolution].values[0].name = "resolution";
    submodule_data->tables[dnx_data_sch_interface_table_shaper_resolution].values[0].type = "uint32";
    submodule_data->tables[dnx_data_sch_interface_table_shaper_resolution].values[0].doc = "";
    submodule_data->tables[dnx_data_sch_interface_table_shaper_resolution].values[0].offset = UTILEX_OFFSETOF(dnx_data_sch_interface_shaper_resolution_t, resolution);


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_sch_interface_feature_get(
    int unit,
    dnx_data_sch_interface_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_interface, feature);
}


uint32
dnx_data_sch_interface_nof_big_calendars_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_interface, dnx_data_sch_interface_define_nof_big_calendars);
}

uint32
dnx_data_sch_interface_nof_channelized_calendars_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_interface, dnx_data_sch_interface_define_nof_channelized_calendars);
}

uint32
dnx_data_sch_interface_max_calendar_size_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_interface, dnx_data_sch_interface_define_max_calendar_size);
}

uint32
dnx_data_sch_interface_nof_sch_interfaces_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_interface, dnx_data_sch_interface_define_nof_sch_interfaces);
}

uint32
dnx_data_sch_interface_cal_speed_resolution_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_interface, dnx_data_sch_interface_define_cal_speed_resolution);
}

uint32
dnx_data_sch_interface_reserved_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_interface, dnx_data_sch_interface_define_reserved);
}

uint32
dnx_data_sch_interface_max_if_rate_mbps_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_interface, dnx_data_sch_interface_define_max_if_rate_mbps);
}



const dnx_data_sch_interface_shaper_resolution_t *
dnx_data_sch_interface_shaper_resolution_get(
    int unit,
    int channelized)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_interface, dnx_data_sch_interface_table_shaper_resolution);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, channelized, 0);
    return (const dnx_data_sch_interface_shaper_resolution_t *) data;

}


shr_error_e
dnx_data_sch_interface_shaper_resolution_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_sch_interface_shaper_resolution_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_interface, dnx_data_sch_interface_table_shaper_resolution);
    data = (const dnx_data_sch_interface_shaper_resolution_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->resolution);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnx_data_sch_interface_shaper_resolution_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_interface, dnx_data_sch_interface_table_shaper_resolution);

}






static shr_error_e
dnx_data_sch_device_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "device";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_sch_device_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data sch device features");

    submodule_data->features[dnx_data_sch_device_shared_drm].name = "shared_drm";
    submodule_data->features[dnx_data_sch_device_shared_drm].doc = "";
    submodule_data->features[dnx_data_sch_device_shared_drm].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnx_data_sch_device_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data sch device defines");

    submodule_data->defines[dnx_data_sch_device_define_drm_resolution].name = "drm_resolution";
    submodule_data->defines[dnx_data_sch_device_define_drm_resolution].doc = "";
    
    submodule_data->defines[dnx_data_sch_device_define_drm_resolution].flags |= DNXC_DATA_F_DEFINE;

    
    submodule_data->nof_tables = _dnx_data_sch_device_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data sch device tables");


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_sch_device_feature_get(
    int unit,
    dnx_data_sch_device_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_device, feature);
}


uint32
dnx_data_sch_device_drm_resolution_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_device, dnx_data_sch_device_define_drm_resolution);
}










static shr_error_e
dnx_data_sch_sch_alloc_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "sch_alloc";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_sch_sch_alloc_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data sch sch_alloc features");

    
    submodule_data->nof_defines = _dnx_data_sch_sch_alloc_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data sch sch_alloc defines");

    submodule_data->defines[dnx_data_sch_sch_alloc_define_tag_aggregate_se_2].name = "tag_aggregate_se_2";
    submodule_data->defines[dnx_data_sch_sch_alloc_define_tag_aggregate_se_2].doc = "";
    
    submodule_data->defines[dnx_data_sch_sch_alloc_define_tag_aggregate_se_2].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_sch_alloc_define_tag_aggregate_se_4].name = "tag_aggregate_se_4";
    submodule_data->defines[dnx_data_sch_sch_alloc_define_tag_aggregate_se_4].doc = "";
    
    submodule_data->defines[dnx_data_sch_sch_alloc_define_tag_aggregate_se_4].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_sch_alloc_define_tag_aggregate_se_8].name = "tag_aggregate_se_8";
    submodule_data->defines[dnx_data_sch_sch_alloc_define_tag_aggregate_se_8].doc = "";
    
    submodule_data->defines[dnx_data_sch_sch_alloc_define_tag_aggregate_se_8].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_sch_alloc_define_shared_shaper_max_tag_value].name = "shared_shaper_max_tag_value";
    submodule_data->defines[dnx_data_sch_sch_alloc_define_shared_shaper_max_tag_value].doc = "";
    
    submodule_data->defines[dnx_data_sch_sch_alloc_define_shared_shaper_max_tag_value].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_sch_alloc_define_tag_size_aggregate_se].name = "tag_size_aggregate_se";
    submodule_data->defines[dnx_data_sch_sch_alloc_define_tag_size_aggregate_se].doc = "";
    
    submodule_data->defines[dnx_data_sch_sch_alloc_define_tag_size_aggregate_se].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_sch_alloc_define_tag_size_con].name = "tag_size_con";
    submodule_data->defines[dnx_data_sch_sch_alloc_define_tag_size_con].doc = "";
    
    submodule_data->defines[dnx_data_sch_sch_alloc_define_tag_size_con].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_sch_alloc_define_type_con_reg_start].name = "type_con_reg_start";
    submodule_data->defines[dnx_data_sch_sch_alloc_define_type_con_reg_start].doc = "";
    
    submodule_data->defines[dnx_data_sch_sch_alloc_define_type_con_reg_start].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_sch_alloc_define_alloc_invalid_flow].name = "alloc_invalid_flow";
    submodule_data->defines[dnx_data_sch_sch_alloc_define_alloc_invalid_flow].doc = "";
    
    submodule_data->defines[dnx_data_sch_sch_alloc_define_alloc_invalid_flow].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_sch_alloc_define_dealloc_flow_ids].name = "dealloc_flow_ids";
    submodule_data->defines[dnx_data_sch_sch_alloc_define_dealloc_flow_ids].doc = "";
    
    submodule_data->defines[dnx_data_sch_sch_alloc_define_dealloc_flow_ids].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_sch_alloc_define_type_con_reg_end].name = "type_con_reg_end";
    submodule_data->defines[dnx_data_sch_sch_alloc_define_type_con_reg_end].doc = "";
    
    submodule_data->defines[dnx_data_sch_sch_alloc_define_type_con_reg_end].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_sch_alloc_define_type_hr_reg_start].name = "type_hr_reg_start";
    submodule_data->defines[dnx_data_sch_sch_alloc_define_type_hr_reg_start].doc = "";
    
    submodule_data->defines[dnx_data_sch_sch_alloc_define_type_hr_reg_start].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_sch_sch_alloc_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data sch sch_alloc tables");

    
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].name = "region";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].size_of_values = sizeof(dnx_data_sch_sch_alloc_region_t);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].entry_get = dnx_data_sch_sch_alloc_region_entry_str_get;

    
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].nof_keys = 2;
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].keys[0].name = "quartet_type";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].keys[0].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].keys[1].name = "region_type";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].keys[1].doc = "";

    
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].nof_values = 5;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values, dnxc_data_value_t, submodule_data->tables[dnx_data_sch_sch_alloc_table_region].nof_values, "_dnx_data_sch_sch_alloc_table_region table values");
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[0].name = "flow_type";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[0].type = "dnx_sch_element_se_type_e[4]";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[0].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[0].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_region_t, flow_type);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[1].name = "odd_even_mode";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[1].type = "dnx_scheduler_region_odd_even_mode_t";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[1].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[1].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_region_t, odd_even_mode);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[2].name = "cl_half_pattern";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[2].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[2].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[2].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_region_t, cl_half_pattern);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[3].name = "fq_half_pattern";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[3].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[3].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[3].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_region_t, fq_half_pattern);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[4].name = "enhanced_cl_compact";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[4].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[4].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_region].values[4].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_region_t, enhanced_cl_compact);

    
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].name = "connector";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].size_of_values = sizeof(dnx_data_sch_sch_alloc_connector_t);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].entry_get = dnx_data_sch_sch_alloc_connector_entry_str_get;

    
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].nof_keys = 2;
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].keys[0].name = "composite";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].keys[0].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].keys[1].name = "interdigitated";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].keys[1].doc = "";

    
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].nof_values = 4;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].values, dnxc_data_value_t, submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].nof_values, "_dnx_data_sch_sch_alloc_table_connector table values");
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].values[0].name = "alignment";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].values[0].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].values[0].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].values[0].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_connector_t, alignment);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].values[1].name = "pattern";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].values[1].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].values[1].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].values[1].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_connector_t, pattern);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].values[2].name = "pattern_size";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].values[2].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].values[2].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].values[2].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_connector_t, pattern_size);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].values[3].name = "nof_in_pattern";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].values[3].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].values[3].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_connector].values[3].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_connector_t, nof_in_pattern);

    
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].name = "se_per_region_type";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].size_of_values = sizeof(dnx_data_sch_sch_alloc_se_per_region_type_t);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].entry_get = dnx_data_sch_sch_alloc_se_per_region_type_entry_str_get;

    
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].nof_keys = 2;
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].keys[0].name = "flow_type";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].keys[0].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].keys[1].name = "region_type";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].keys[1].doc = "";

    
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].nof_values = 6;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values, dnxc_data_value_t, submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].nof_values, "_dnx_data_sch_sch_alloc_table_se_per_region_type table values");
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[0].name = "valid";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[0].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[0].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[0].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_se_per_region_type_t, valid);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[1].name = "alignment";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[1].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[1].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[1].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_se_per_region_type_t, alignment);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[2].name = "pattern";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[2].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[2].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[2].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_se_per_region_type_t, pattern);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[3].name = "pattern_size";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[3].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[3].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[3].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_se_per_region_type_t, pattern_size);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[4].name = "nof_offsets";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[4].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[4].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[4].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_se_per_region_type_t, nof_offsets);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[5].name = "offset";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[5].type = "uint32[4]";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[5].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se_per_region_type].values[5].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_se_per_region_type_t, offset);

    
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].name = "se";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].size_of_values = sizeof(dnx_data_sch_sch_alloc_se_t);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].entry_get = dnx_data_sch_sch_alloc_se_entry_str_get;

    
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].nof_keys = 1;
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].keys[0].name = "flow_type";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].keys[0].doc = "";

    
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].nof_values = 5;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values, dnxc_data_value_t, submodule_data->tables[dnx_data_sch_sch_alloc_table_se].nof_values, "_dnx_data_sch_sch_alloc_table_se table values");
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[0].name = "alignment";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[0].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[0].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[0].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_se_t, alignment);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[1].name = "pattern";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[1].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[1].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[1].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_se_t, pattern);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[2].name = "pattern_size";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[2].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[2].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[2].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_se_t, pattern_size);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[3].name = "nof_offsets";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[3].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[3].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[3].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_se_t, nof_offsets);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[4].name = "offset";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[4].type = "uint32[4]";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[4].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_se].values[4].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_se_t, offset);

    
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].name = "composite_se_per_region_type";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].size_of_values = sizeof(dnx_data_sch_sch_alloc_composite_se_per_region_type_t);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].entry_get = dnx_data_sch_sch_alloc_composite_se_per_region_type_entry_str_get;

    
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].nof_keys = 2;
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].keys[0].name = "flow_type";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].keys[0].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].keys[1].name = "region_type";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].keys[1].doc = "";

    
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].nof_values = 4;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].values, dnxc_data_value_t, submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].nof_values, "_dnx_data_sch_sch_alloc_table_composite_se_per_region_type table values");
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].values[0].name = "valid";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].values[0].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].values[0].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].values[0].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_composite_se_per_region_type_t, valid);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].values[1].name = "alignment";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].values[1].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].values[1].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].values[1].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_composite_se_per_region_type_t, alignment);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].values[2].name = "pattern";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].values[2].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].values[2].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].values[2].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_composite_se_per_region_type_t, pattern);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].values[3].name = "pattern_size";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].values[3].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].values[3].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se_per_region_type].values[3].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_composite_se_per_region_type_t, pattern_size);

    
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].name = "composite_se";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].size_of_values = sizeof(dnx_data_sch_sch_alloc_composite_se_t);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].entry_get = dnx_data_sch_sch_alloc_composite_se_entry_str_get;

    
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].nof_keys = 2;
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].keys[0].name = "flow_type";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].keys[0].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].keys[1].name = "odd_even_mode";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].keys[1].doc = "";

    
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].nof_values = 3;
    DNXC_DATA_ALLOC(submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].values, dnxc_data_value_t, submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].nof_values, "_dnx_data_sch_sch_alloc_table_composite_se table values");
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].values[0].name = "alignment";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].values[0].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].values[0].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].values[0].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_composite_se_t, alignment);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].values[1].name = "pattern";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].values[1].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].values[1].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].values[1].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_composite_se_t, pattern);
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].values[2].name = "pattern_size";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].values[2].type = "uint32";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].values[2].doc = "";
    submodule_data->tables[dnx_data_sch_sch_alloc_table_composite_se].values[2].offset = UTILEX_OFFSETOF(dnx_data_sch_sch_alloc_composite_se_t, pattern_size);


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_sch_sch_alloc_feature_get(
    int unit,
    dnx_data_sch_sch_alloc_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, feature);
}


uint32
dnx_data_sch_sch_alloc_tag_aggregate_se_2_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_define_tag_aggregate_se_2);
}

uint32
dnx_data_sch_sch_alloc_tag_aggregate_se_4_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_define_tag_aggregate_se_4);
}

uint32
dnx_data_sch_sch_alloc_tag_aggregate_se_8_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_define_tag_aggregate_se_8);
}

uint32
dnx_data_sch_sch_alloc_shared_shaper_max_tag_value_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_define_shared_shaper_max_tag_value);
}

uint32
dnx_data_sch_sch_alloc_tag_size_aggregate_se_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_define_tag_size_aggregate_se);
}

uint32
dnx_data_sch_sch_alloc_tag_size_con_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_define_tag_size_con);
}

uint32
dnx_data_sch_sch_alloc_type_con_reg_start_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_define_type_con_reg_start);
}

uint32
dnx_data_sch_sch_alloc_alloc_invalid_flow_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_define_alloc_invalid_flow);
}

uint32
dnx_data_sch_sch_alloc_dealloc_flow_ids_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_define_dealloc_flow_ids);
}

uint32
dnx_data_sch_sch_alloc_type_con_reg_end_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_define_type_con_reg_end);
}

uint32
dnx_data_sch_sch_alloc_type_hr_reg_start_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_define_type_hr_reg_start);
}



const dnx_data_sch_sch_alloc_region_t *
dnx_data_sch_sch_alloc_region_get(
    int unit,
    int quartet_type,
    int region_type)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_table_region);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, quartet_type, region_type);
    return (const dnx_data_sch_sch_alloc_region_t *) data;

}

const dnx_data_sch_sch_alloc_connector_t *
dnx_data_sch_sch_alloc_connector_get(
    int unit,
    int composite,
    int interdigitated)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_table_connector);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, composite, interdigitated);
    return (const dnx_data_sch_sch_alloc_connector_t *) data;

}

const dnx_data_sch_sch_alloc_se_per_region_type_t *
dnx_data_sch_sch_alloc_se_per_region_type_get(
    int unit,
    int flow_type,
    int region_type)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_table_se_per_region_type);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, flow_type, region_type);
    return (const dnx_data_sch_sch_alloc_se_per_region_type_t *) data;

}

const dnx_data_sch_sch_alloc_se_t *
dnx_data_sch_sch_alloc_se_get(
    int unit,
    int flow_type)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_table_se);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, flow_type, 0);
    return (const dnx_data_sch_sch_alloc_se_t *) data;

}

const dnx_data_sch_sch_alloc_composite_se_per_region_type_t *
dnx_data_sch_sch_alloc_composite_se_per_region_type_get(
    int unit,
    int flow_type,
    int region_type)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_table_composite_se_per_region_type);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, flow_type, region_type);
    return (const dnx_data_sch_sch_alloc_composite_se_per_region_type_t *) data;

}

const dnx_data_sch_sch_alloc_composite_se_t *
dnx_data_sch_sch_alloc_composite_se_get(
    int unit,
    int flow_type,
    int odd_even_mode)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_table_composite_se);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, flow_type, odd_even_mode);
    return (const dnx_data_sch_sch_alloc_composite_se_t *) data;

}


shr_error_e
dnx_data_sch_sch_alloc_region_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_sch_sch_alloc_region_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_table_region);
    data = (const dnx_data_sch_sch_alloc_region_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, key1);
    switch (value_index)
    {
        case 0:
            DNXC_DATA_MGMT_ARR_STR(buffer, 4, data->flow_type);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->odd_even_mode);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->cl_half_pattern);
            break;
        case 3:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->fq_half_pattern);
            break;
        case 4:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->enhanced_cl_compact);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_sch_sch_alloc_connector_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_sch_sch_alloc_connector_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_table_connector);
    data = (const dnx_data_sch_sch_alloc_connector_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, key1);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->alignment);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->pattern);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->pattern_size);
            break;
        case 3:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->nof_in_pattern);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_sch_sch_alloc_se_per_region_type_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_sch_sch_alloc_se_per_region_type_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_table_se_per_region_type);
    data = (const dnx_data_sch_sch_alloc_se_per_region_type_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, key1);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->valid);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->alignment);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->pattern);
            break;
        case 3:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->pattern_size);
            break;
        case 4:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->nof_offsets);
            break;
        case 5:
            DNXC_DATA_MGMT_ARR_STR(buffer, 4, data->offset);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_sch_sch_alloc_se_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_sch_sch_alloc_se_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_table_se);
    data = (const dnx_data_sch_sch_alloc_se_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->alignment);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->pattern);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->pattern_size);
            break;
        case 3:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->nof_offsets);
            break;
        case 4:
            DNXC_DATA_MGMT_ARR_STR(buffer, 4, data->offset);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_sch_sch_alloc_composite_se_per_region_type_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_sch_sch_alloc_composite_se_per_region_type_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_table_composite_se_per_region_type);
    data = (const dnx_data_sch_sch_alloc_composite_se_per_region_type_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, key1);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->valid);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->alignment);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->pattern);
            break;
        case 3:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->pattern_size);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_data_sch_sch_alloc_composite_se_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnx_data_sch_sch_alloc_composite_se_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_table_composite_se);
    data = (const dnx_data_sch_sch_alloc_composite_se_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, key1);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->alignment);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->pattern);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->pattern_size);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnx_data_sch_sch_alloc_region_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_table_region);

}

const dnxc_data_table_info_t *
dnx_data_sch_sch_alloc_connector_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_table_connector);

}

const dnxc_data_table_info_t *
dnx_data_sch_sch_alloc_se_per_region_type_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_table_se_per_region_type);

}

const dnxc_data_table_info_t *
dnx_data_sch_sch_alloc_se_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_table_se);

}

const dnxc_data_table_info_t *
dnx_data_sch_sch_alloc_composite_se_per_region_type_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_table_composite_se_per_region_type);

}

const dnxc_data_table_info_t *
dnx_data_sch_sch_alloc_composite_se_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_sch_alloc, dnx_data_sch_sch_alloc_table_composite_se);

}






static shr_error_e
dnx_data_sch_dbal_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "dbal";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_sch_dbal_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data sch dbal features");

    
    submodule_data->nof_defines = _dnx_data_sch_dbal_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data sch dbal defines");

    submodule_data->defines[dnx_data_sch_dbal_define_scheduler_enable_grouping_factor].name = "scheduler_enable_grouping_factor";
    submodule_data->defines[dnx_data_sch_dbal_define_scheduler_enable_grouping_factor].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_scheduler_enable_grouping_factor].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_dbal_define_scheduler_enable_dbal_mult_factor].name = "scheduler_enable_dbal_mult_factor";
    submodule_data->defines[dnx_data_sch_dbal_define_scheduler_enable_dbal_mult_factor].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_scheduler_enable_dbal_mult_factor].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_dbal_define_flow_bits].name = "flow_bits";
    submodule_data->defines[dnx_data_sch_dbal_define_flow_bits].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_flow_bits].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_dbal_define_se_bits].name = "se_bits";
    submodule_data->defines[dnx_data_sch_dbal_define_se_bits].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_se_bits].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_dbal_define_cl_bits].name = "cl_bits";
    submodule_data->defines[dnx_data_sch_dbal_define_cl_bits].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_cl_bits].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_dbal_define_hr_bits].name = "hr_bits";
    submodule_data->defines[dnx_data_sch_dbal_define_hr_bits].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_hr_bits].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_dbal_define_interface_bits].name = "interface_bits";
    submodule_data->defines[dnx_data_sch_dbal_define_interface_bits].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_interface_bits].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_dbal_define_calendar_bits].name = "calendar_bits";
    submodule_data->defines[dnx_data_sch_dbal_define_calendar_bits].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_calendar_bits].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_dbal_define_flow_shaper_mant_bits].name = "flow_shaper_mant_bits";
    submodule_data->defines[dnx_data_sch_dbal_define_flow_shaper_mant_bits].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_flow_shaper_mant_bits].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_dbal_define_flow_shaper_max_burst_bits].name = "flow_shaper_max_burst_bits";
    submodule_data->defines[dnx_data_sch_dbal_define_flow_shaper_max_burst_bits].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_flow_shaper_max_burst_bits].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_dbal_define_ps_shaper_quanta_bits].name = "ps_shaper_quanta_bits";
    submodule_data->defines[dnx_data_sch_dbal_define_ps_shaper_quanta_bits].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_ps_shaper_quanta_bits].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_dbal_define_ps_shaper_max_burst_bits].name = "ps_shaper_max_burst_bits";
    submodule_data->defines[dnx_data_sch_dbal_define_ps_shaper_max_burst_bits].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_ps_shaper_max_burst_bits].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_dbal_define_drm_nof_links_max].name = "drm_nof_links_max";
    submodule_data->defines[dnx_data_sch_dbal_define_drm_nof_links_max].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_drm_nof_links_max].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_dbal_define_token_count_default].name = "token_count_default";
    submodule_data->defines[dnx_data_sch_dbal_define_token_count_default].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_token_count_default].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_dbal_define_priority_propagation_if_group_max].name = "priority_propagation_if_group_max";
    submodule_data->defines[dnx_data_sch_dbal_define_priority_propagation_if_group_max].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_priority_propagation_if_group_max].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_dbal_define_max_sch_interfaces_with_fc].name = "max_sch_interfaces_with_fc";
    submodule_data->defines[dnx_data_sch_dbal_define_max_sch_interfaces_with_fc].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_max_sch_interfaces_with_fc].flags |= DNXC_DATA_F_DEFINE;

    submodule_data->defines[dnx_data_sch_dbal_define_scheduler_enable_key_size].name = "scheduler_enable_key_size";
    submodule_data->defines[dnx_data_sch_dbal_define_scheduler_enable_key_size].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_scheduler_enable_key_size].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_dbal_define_flow_id_pair_key_size].name = "flow_id_pair_key_size";
    submodule_data->defines[dnx_data_sch_dbal_define_flow_id_pair_key_size].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_flow_id_pair_key_size].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_dbal_define_flow_id_pair_max].name = "flow_id_pair_max";
    submodule_data->defines[dnx_data_sch_dbal_define_flow_id_pair_max].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_flow_id_pair_max].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_dbal_define_ps_bits].name = "ps_bits";
    submodule_data->defines[dnx_data_sch_dbal_define_ps_bits].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_ps_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_dbal_define_flow_shaper_descr_bits].name = "flow_shaper_descr_bits";
    submodule_data->defines[dnx_data_sch_dbal_define_flow_shaper_descr_bits].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_flow_shaper_descr_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_dbal_define_ps_shaper_bits].name = "ps_shaper_bits";
    submodule_data->defines[dnx_data_sch_dbal_define_ps_shaper_bits].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_ps_shaper_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_dbal_define_cl_profile_bits].name = "cl_profile_bits";
    submodule_data->defines[dnx_data_sch_dbal_define_cl_profile_bits].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_cl_profile_bits].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnx_data_sch_dbal_define_priority_propagation_if_group_nof_bits].name = "priority_propagation_if_group_nof_bits";
    submodule_data->defines[dnx_data_sch_dbal_define_priority_propagation_if_group_nof_bits].doc = "";
    
    submodule_data->defines[dnx_data_sch_dbal_define_priority_propagation_if_group_nof_bits].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnx_data_sch_dbal_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data sch dbal tables");


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_sch_dbal_feature_get(
    int unit,
    dnx_data_sch_dbal_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, feature);
}


uint32
dnx_data_sch_dbal_scheduler_enable_grouping_factor_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_scheduler_enable_grouping_factor);
}

uint32
dnx_data_sch_dbal_scheduler_enable_dbal_mult_factor_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_scheduler_enable_dbal_mult_factor);
}

uint32
dnx_data_sch_dbal_flow_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_flow_bits);
}

uint32
dnx_data_sch_dbal_se_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_se_bits);
}

uint32
dnx_data_sch_dbal_cl_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_cl_bits);
}

uint32
dnx_data_sch_dbal_hr_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_hr_bits);
}

uint32
dnx_data_sch_dbal_interface_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_interface_bits);
}

uint32
dnx_data_sch_dbal_calendar_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_calendar_bits);
}

uint32
dnx_data_sch_dbal_flow_shaper_mant_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_flow_shaper_mant_bits);
}

uint32
dnx_data_sch_dbal_flow_shaper_max_burst_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_flow_shaper_max_burst_bits);
}

uint32
dnx_data_sch_dbal_ps_shaper_quanta_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_ps_shaper_quanta_bits);
}

uint32
dnx_data_sch_dbal_ps_shaper_max_burst_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_ps_shaper_max_burst_bits);
}

uint32
dnx_data_sch_dbal_drm_nof_links_max_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_drm_nof_links_max);
}

uint32
dnx_data_sch_dbal_token_count_default_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_token_count_default);
}

uint32
dnx_data_sch_dbal_priority_propagation_if_group_max_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_priority_propagation_if_group_max);
}

uint32
dnx_data_sch_dbal_max_sch_interfaces_with_fc_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_max_sch_interfaces_with_fc);
}

uint32
dnx_data_sch_dbal_scheduler_enable_key_size_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_scheduler_enable_key_size);
}

uint32
dnx_data_sch_dbal_flow_id_pair_key_size_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_flow_id_pair_key_size);
}

uint32
dnx_data_sch_dbal_flow_id_pair_max_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_flow_id_pair_max);
}

uint32
dnx_data_sch_dbal_ps_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_ps_bits);
}

uint32
dnx_data_sch_dbal_flow_shaper_descr_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_flow_shaper_descr_bits);
}

uint32
dnx_data_sch_dbal_ps_shaper_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_ps_shaper_bits);
}

uint32
dnx_data_sch_dbal_cl_profile_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_cl_profile_bits);
}

uint32
dnx_data_sch_dbal_priority_propagation_if_group_nof_bits_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_dbal, dnx_data_sch_dbal_define_priority_propagation_if_group_nof_bits);
}










static shr_error_e
dnx_data_sch_features_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "features";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_sch_features_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data sch features features");

    submodule_data->features[dnx_data_sch_features_dlm].name = "dlm";
    submodule_data->features[dnx_data_sch_features_dlm].doc = "";
    submodule_data->features[dnx_data_sch_features_dlm].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnx_data_sch_features_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data sch features defines");

    
    submodule_data->nof_tables = _dnx_data_sch_features_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data sch features tables");


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_sch_features_feature_get(
    int unit,
    dnx_data_sch_features_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_features, feature);
}











static shr_error_e
dnx_data_sch_fc_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "fc";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnx_data_sch_fc_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data sch fc features");

    submodule_data->features[dnx_data_sch_fc_context_based_mapping].name = "context_based_mapping";
    submodule_data->features[dnx_data_sch_fc_context_based_mapping].doc = "";
    submodule_data->features[dnx_data_sch_fc_context_based_mapping].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnx_data_sch_fc_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data sch fc defines");

    
    submodule_data->nof_tables = _dnx_data_sch_fc_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data sch fc tables");


exit:
    SHR_FUNC_EXIT;
}


int
dnx_data_sch_fc_feature_get(
    int unit,
    dnx_data_sch_fc_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnx_data_module_sch, dnx_data_sch_submodule_fc, feature);
}








shr_error_e
dnx_data_sch_init(
    int unit,
    dnxc_data_module_t *module_data)
{
    SHR_FUNC_INIT_VARS(unit);

    
    module_data->name = "sch";
    module_data->nof_submodules = _dnx_data_sch_submodule_nof;
    DNXC_DATA_ALLOC(module_data->submodules, dnxc_data_submodule_t, module_data->nof_submodules, "_dnxc_data sch submodules");

    
    SHR_IF_ERR_EXIT(dnx_data_sch_general_init(unit, &module_data->submodules[dnx_data_sch_submodule_general]));
    SHR_IF_ERR_EXIT(dnx_data_sch_ps_init(unit, &module_data->submodules[dnx_data_sch_submodule_ps]));
    SHR_IF_ERR_EXIT(dnx_data_sch_flow_init(unit, &module_data->submodules[dnx_data_sch_submodule_flow]));
    SHR_IF_ERR_EXIT(dnx_data_sch_se_init(unit, &module_data->submodules[dnx_data_sch_submodule_se]));
    SHR_IF_ERR_EXIT(dnx_data_sch_interface_init(unit, &module_data->submodules[dnx_data_sch_submodule_interface]));
    SHR_IF_ERR_EXIT(dnx_data_sch_device_init(unit, &module_data->submodules[dnx_data_sch_submodule_device]));
    SHR_IF_ERR_EXIT(dnx_data_sch_sch_alloc_init(unit, &module_data->submodules[dnx_data_sch_submodule_sch_alloc]));
    SHR_IF_ERR_EXIT(dnx_data_sch_dbal_init(unit, &module_data->submodules[dnx_data_sch_submodule_dbal]));
    SHR_IF_ERR_EXIT(dnx_data_sch_features_init(unit, &module_data->submodules[dnx_data_sch_submodule_features]));
    SHR_IF_ERR_EXIT(dnx_data_sch_fc_init(unit, &module_data->submodules[dnx_data_sch_submodule_fc]));
    

    if (dnxc_data_mgmt_is_jr2_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_sch_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_jr2_b0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_sch_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_jr2_b1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_sch_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2c_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_sch_attach(unit));
        SHR_IF_ERR_EXIT(j2c_a0_data_sch_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2c_a1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_sch_attach(unit));
        SHR_IF_ERR_EXIT(j2c_a0_data_sch_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_q2a_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_sch_attach(unit));
        SHR_IF_ERR_EXIT(q2a_a0_data_sch_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_q2a_b0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_sch_attach(unit));
        SHR_IF_ERR_EXIT(q2a_a0_data_sch_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_q2a_b1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_sch_attach(unit));
        SHR_IF_ERR_EXIT(q2a_a0_data_sch_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2p_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_sch_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a0_data_sch_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2p_a1(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_sch_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a0_data_sch_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2p_a2(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_sch_attach(unit));
        SHR_IF_ERR_EXIT(j2p_a0_data_sch_attach(unit));
    }
    else


    if (dnxc_data_mgmt_is_j2x_a0(unit))
    {
        SHR_IF_ERR_EXIT(jr2_a0_data_sch_attach(unit));
        SHR_IF_ERR_EXIT(j2x_a0_data_sch_attach(unit));
    }
    else

    {
        SHR_EXIT();
    }

exit:
    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


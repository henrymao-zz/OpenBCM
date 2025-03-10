
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_INTR

#include <soc/dnxf/dnxf_data/auto_generated/dnxf_data_internal_intr.h>



#ifdef BCM_DNXF1_SUPPORT

extern shr_error_e ramon_a0_data_intr_attach(
    int unit);

#endif 



static shr_error_e
dnxf_data_intr_general_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "general";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnxf_data_intr_general_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data intr general features");

    submodule_data->features[dnxf_data_intr_general_new_access_support].name = "new_access_support";
    submodule_data->features[dnxf_data_intr_general_new_access_support].doc = "";
    submodule_data->features[dnxf_data_intr_general_new_access_support].flags |= DNXC_DATA_F_FEATURE;

    submodule_data->features[dnxf_data_intr_general_soft_init_for_debug].name = "soft_init_for_debug";
    submodule_data->features[dnxf_data_intr_general_soft_init_for_debug].doc = "";
    submodule_data->features[dnxf_data_intr_general_soft_init_for_debug].flags |= DNXC_DATA_F_FEATURE;

    
    submodule_data->nof_defines = _dnxf_data_intr_general_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data intr general defines");

    submodule_data->defines[dnxf_data_intr_general_define_nof_interrupts].name = "nof_interrupts";
    submodule_data->defines[dnxf_data_intr_general_define_nof_interrupts].doc = "";
    
    submodule_data->defines[dnxf_data_intr_general_define_nof_interrupts].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnxf_data_intr_general_define_polled_irq_mode].name = "polled_irq_mode";
    submodule_data->defines[dnxf_data_intr_general_define_polled_irq_mode].doc = "";
    
    submodule_data->defines[dnxf_data_intr_general_define_polled_irq_mode].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnxf_data_intr_general_define_ser_event_generate_support].name = "ser_event_generate_support";
    submodule_data->defines[dnxf_data_intr_general_define_ser_event_generate_support].doc = "";
    
    submodule_data->defines[dnxf_data_intr_general_define_ser_event_generate_support].flags |= DNXC_DATA_F_NUMERIC;

    submodule_data->defines[dnxf_data_intr_general_define_ser_reset_cb_en_support].name = "ser_reset_cb_en_support";
    submodule_data->defines[dnxf_data_intr_general_define_ser_reset_cb_en_support].doc = "";
    
    submodule_data->defines[dnxf_data_intr_general_define_ser_reset_cb_en_support].flags |= DNXC_DATA_F_NUMERIC;

    
    submodule_data->nof_tables = _dnxf_data_intr_general_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data intr general tables");

    
    submodule_data->tables[dnxf_data_intr_general_table_active_on_init].name = "active_on_init";
    submodule_data->tables[dnxf_data_intr_general_table_active_on_init].doc = "";
    submodule_data->tables[dnxf_data_intr_general_table_active_on_init].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_intr_general_table_active_on_init].size_of_values = sizeof(dnxf_data_intr_general_active_on_init_t);
    submodule_data->tables[dnxf_data_intr_general_table_active_on_init].entry_get = dnxf_data_intr_general_active_on_init_entry_str_get;

    
    submodule_data->tables[dnxf_data_intr_general_table_active_on_init].nof_keys = 1;
    submodule_data->tables[dnxf_data_intr_general_table_active_on_init].keys[0].name = "offset";
    submodule_data->tables[dnxf_data_intr_general_table_active_on_init].keys[0].doc = "";

    
    submodule_data->tables[dnxf_data_intr_general_table_active_on_init].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_intr_general_table_active_on_init].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_intr_general_table_active_on_init].nof_values, "_dnxf_data_intr_general_table_active_on_init table values");
    submodule_data->tables[dnxf_data_intr_general_table_active_on_init].values[0].name = "intr";
    submodule_data->tables[dnxf_data_intr_general_table_active_on_init].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_intr_general_table_active_on_init].values[0].doc = "";
    submodule_data->tables[dnxf_data_intr_general_table_active_on_init].values[0].offset = UTILEX_OFFSETOF(dnxf_data_intr_general_active_on_init_t, intr);

    
    submodule_data->tables[dnxf_data_intr_general_table_disable_on_init].name = "disable_on_init";
    submodule_data->tables[dnxf_data_intr_general_table_disable_on_init].doc = "";
    submodule_data->tables[dnxf_data_intr_general_table_disable_on_init].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_intr_general_table_disable_on_init].size_of_values = sizeof(dnxf_data_intr_general_disable_on_init_t);
    submodule_data->tables[dnxf_data_intr_general_table_disable_on_init].entry_get = dnxf_data_intr_general_disable_on_init_entry_str_get;

    
    submodule_data->tables[dnxf_data_intr_general_table_disable_on_init].nof_keys = 1;
    submodule_data->tables[dnxf_data_intr_general_table_disable_on_init].keys[0].name = "offset";
    submodule_data->tables[dnxf_data_intr_general_table_disable_on_init].keys[0].doc = "";

    
    submodule_data->tables[dnxf_data_intr_general_table_disable_on_init].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_intr_general_table_disable_on_init].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_intr_general_table_disable_on_init].nof_values, "_dnxf_data_intr_general_table_disable_on_init table values");
    submodule_data->tables[dnxf_data_intr_general_table_disable_on_init].values[0].name = "intr";
    submodule_data->tables[dnxf_data_intr_general_table_disable_on_init].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_intr_general_table_disable_on_init].values[0].doc = "";
    submodule_data->tables[dnxf_data_intr_general_table_disable_on_init].values[0].offset = UTILEX_OFFSETOF(dnxf_data_intr_general_disable_on_init_t, intr);

    
    submodule_data->tables[dnxf_data_intr_general_table_disable_print_on_init].name = "disable_print_on_init";
    submodule_data->tables[dnxf_data_intr_general_table_disable_print_on_init].doc = "";
    submodule_data->tables[dnxf_data_intr_general_table_disable_print_on_init].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_intr_general_table_disable_print_on_init].size_of_values = sizeof(dnxf_data_intr_general_disable_print_on_init_t);
    submodule_data->tables[dnxf_data_intr_general_table_disable_print_on_init].entry_get = dnxf_data_intr_general_disable_print_on_init_entry_str_get;

    
    submodule_data->tables[dnxf_data_intr_general_table_disable_print_on_init].nof_keys = 1;
    submodule_data->tables[dnxf_data_intr_general_table_disable_print_on_init].keys[0].name = "offset";
    submodule_data->tables[dnxf_data_intr_general_table_disable_print_on_init].keys[0].doc = "";

    
    submodule_data->tables[dnxf_data_intr_general_table_disable_print_on_init].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_intr_general_table_disable_print_on_init].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_intr_general_table_disable_print_on_init].nof_values, "_dnxf_data_intr_general_table_disable_print_on_init table values");
    submodule_data->tables[dnxf_data_intr_general_table_disable_print_on_init].values[0].name = "intr";
    submodule_data->tables[dnxf_data_intr_general_table_disable_print_on_init].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_intr_general_table_disable_print_on_init].values[0].doc = "";
    submodule_data->tables[dnxf_data_intr_general_table_disable_print_on_init].values[0].offset = UTILEX_OFFSETOF(dnxf_data_intr_general_disable_print_on_init_t, intr);

    
    submodule_data->tables[dnxf_data_intr_general_table_skip_clear_on_regress].name = "skip_clear_on_regress";
    submodule_data->tables[dnxf_data_intr_general_table_skip_clear_on_regress].doc = "";
    submodule_data->tables[dnxf_data_intr_general_table_skip_clear_on_regress].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_intr_general_table_skip_clear_on_regress].size_of_values = sizeof(dnxf_data_intr_general_skip_clear_on_regress_t);
    submodule_data->tables[dnxf_data_intr_general_table_skip_clear_on_regress].entry_get = dnxf_data_intr_general_skip_clear_on_regress_entry_str_get;

    
    submodule_data->tables[dnxf_data_intr_general_table_skip_clear_on_regress].nof_keys = 1;
    submodule_data->tables[dnxf_data_intr_general_table_skip_clear_on_regress].keys[0].name = "offset";
    submodule_data->tables[dnxf_data_intr_general_table_skip_clear_on_regress].keys[0].doc = "";

    
    submodule_data->tables[dnxf_data_intr_general_table_skip_clear_on_regress].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_intr_general_table_skip_clear_on_regress].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_intr_general_table_skip_clear_on_regress].nof_values, "_dnxf_data_intr_general_table_skip_clear_on_regress table values");
    submodule_data->tables[dnxf_data_intr_general_table_skip_clear_on_regress].values[0].name = "intr";
    submodule_data->tables[dnxf_data_intr_general_table_skip_clear_on_regress].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_intr_general_table_skip_clear_on_regress].values[0].doc = "";
    submodule_data->tables[dnxf_data_intr_general_table_skip_clear_on_regress].values[0].offset = UTILEX_OFFSETOF(dnxf_data_intr_general_skip_clear_on_regress_t, intr);

    
    submodule_data->tables[dnxf_data_intr_general_table_block_intr_field_mapping].name = "block_intr_field_mapping";
    submodule_data->tables[dnxf_data_intr_general_table_block_intr_field_mapping].doc = "";
    submodule_data->tables[dnxf_data_intr_general_table_block_intr_field_mapping].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_intr_general_table_block_intr_field_mapping].size_of_values = sizeof(dnxf_data_intr_general_block_intr_field_mapping_t);
    submodule_data->tables[dnxf_data_intr_general_table_block_intr_field_mapping].entry_get = dnxf_data_intr_general_block_intr_field_mapping_entry_str_get;

    
    submodule_data->tables[dnxf_data_intr_general_table_block_intr_field_mapping].nof_keys = 1;
    submodule_data->tables[dnxf_data_intr_general_table_block_intr_field_mapping].keys[0].name = "offset";
    submodule_data->tables[dnxf_data_intr_general_table_block_intr_field_mapping].keys[0].doc = "";

    
    submodule_data->tables[dnxf_data_intr_general_table_block_intr_field_mapping].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_intr_general_table_block_intr_field_mapping].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_intr_general_table_block_intr_field_mapping].nof_values, "_dnxf_data_intr_general_table_block_intr_field_mapping table values");
    submodule_data->tables[dnxf_data_intr_general_table_block_intr_field_mapping].values[0].name = "intr";
    submodule_data->tables[dnxf_data_intr_general_table_block_intr_field_mapping].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_intr_general_table_block_intr_field_mapping].values[0].doc = "";
    submodule_data->tables[dnxf_data_intr_general_table_block_intr_field_mapping].values[0].offset = UTILEX_OFFSETOF(dnxf_data_intr_general_block_intr_field_mapping_t, intr);

    
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].name = "chip_intr_remap";
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].doc = "";
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].size_of_values = sizeof(dnxf_data_intr_general_chip_intr_remap_t);
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].entry_get = dnxf_data_intr_general_chip_intr_remap_entry_str_get;

    
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].nof_keys = 1;
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].keys[0].name = "offset";
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].keys[0].doc = "";

    
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].nof_values = 3;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].nof_values, "_dnxf_data_intr_general_table_chip_intr_remap table values");
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].values[0].name = "start";
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].values[0].doc = "";
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].values[0].offset = UTILEX_OFFSETOF(dnxf_data_intr_general_chip_intr_remap_t, start);
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].values[1].name = "end";
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].values[1].type = "uint32";
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].values[1].doc = "";
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].values[1].offset = UTILEX_OFFSETOF(dnxf_data_intr_general_chip_intr_remap_t, end);
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].values[2].name = "vector";
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].values[2].type = "uint32";
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].values[2].doc = "";
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_remap].values[2].offset = UTILEX_OFFSETOF(dnxf_data_intr_general_chip_intr_remap_t, vector);

    
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_enable].name = "chip_intr_enable";
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_enable].doc = "";
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_enable].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_enable].size_of_values = sizeof(dnxf_data_intr_general_chip_intr_enable_t);
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_enable].entry_get = dnxf_data_intr_general_chip_intr_enable_entry_str_get;

    
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_enable].nof_keys = 1;
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_enable].keys[0].name = "offset";
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_enable].keys[0].doc = "";

    
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_enable].nof_values = 1;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_intr_general_table_chip_intr_enable].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_intr_general_table_chip_intr_enable].nof_values, "_dnxf_data_intr_general_table_chip_intr_enable table values");
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_enable].values[0].name = "bit";
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_enable].values[0].type = "uint32";
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_enable].values[0].doc = "";
    submodule_data->tables[dnxf_data_intr_general_table_chip_intr_enable].values[0].offset = UTILEX_OFFSETOF(dnxf_data_intr_general_chip_intr_enable_t, bit);


exit:
    SHR_FUNC_EXIT;
}


int
dnxf_data_intr_general_feature_get(
    int unit,
    dnxf_data_intr_general_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, feature);
}


uint32
dnxf_data_intr_general_nof_interrupts_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_define_nof_interrupts);
}

uint32
dnxf_data_intr_general_polled_irq_mode_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_define_polled_irq_mode);
}

uint32
dnxf_data_intr_general_ser_event_generate_support_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_define_ser_event_generate_support);
}

uint32
dnxf_data_intr_general_ser_reset_cb_en_support_get(
    int unit)
{
    return dnxc_data_mgmt_define_data_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_define_ser_reset_cb_en_support);
}



const dnxf_data_intr_general_active_on_init_t *
dnxf_data_intr_general_active_on_init_get(
    int unit,
    int offset)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_active_on_init);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, offset, 0);
    return (const dnxf_data_intr_general_active_on_init_t *) data;

}

const dnxf_data_intr_general_disable_on_init_t *
dnxf_data_intr_general_disable_on_init_get(
    int unit,
    int offset)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_disable_on_init);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, offset, 0);
    return (const dnxf_data_intr_general_disable_on_init_t *) data;

}

const dnxf_data_intr_general_disable_print_on_init_t *
dnxf_data_intr_general_disable_print_on_init_get(
    int unit,
    int offset)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_disable_print_on_init);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, offset, 0);
    return (const dnxf_data_intr_general_disable_print_on_init_t *) data;

}

const dnxf_data_intr_general_skip_clear_on_regress_t *
dnxf_data_intr_general_skip_clear_on_regress_get(
    int unit,
    int offset)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_skip_clear_on_regress);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, offset, 0);
    return (const dnxf_data_intr_general_skip_clear_on_regress_t *) data;

}

const dnxf_data_intr_general_block_intr_field_mapping_t *
dnxf_data_intr_general_block_intr_field_mapping_get(
    int unit,
    int offset)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_block_intr_field_mapping);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, offset, 0);
    return (const dnxf_data_intr_general_block_intr_field_mapping_t *) data;

}

const dnxf_data_intr_general_chip_intr_remap_t *
dnxf_data_intr_general_chip_intr_remap_get(
    int unit,
    int offset)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_chip_intr_remap);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, offset, 0);
    return (const dnxf_data_intr_general_chip_intr_remap_t *) data;

}

const dnxf_data_intr_general_chip_intr_enable_t *
dnxf_data_intr_general_chip_intr_enable_get(
    int unit,
    int offset)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_chip_intr_enable);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, offset, 0);
    return (const dnxf_data_intr_general_chip_intr_enable_t *) data;

}


shr_error_e
dnxf_data_intr_general_active_on_init_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_intr_general_active_on_init_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_active_on_init);
    data = (const dnxf_data_intr_general_active_on_init_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->intr);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnxf_data_intr_general_disable_on_init_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_intr_general_disable_on_init_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_disable_on_init);
    data = (const dnxf_data_intr_general_disable_on_init_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->intr);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnxf_data_intr_general_disable_print_on_init_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_intr_general_disable_print_on_init_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_disable_print_on_init);
    data = (const dnxf_data_intr_general_disable_print_on_init_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->intr);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnxf_data_intr_general_skip_clear_on_regress_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_intr_general_skip_clear_on_regress_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_skip_clear_on_regress);
    data = (const dnxf_data_intr_general_skip_clear_on_regress_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->intr);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnxf_data_intr_general_block_intr_field_mapping_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_intr_general_block_intr_field_mapping_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_block_intr_field_mapping);
    data = (const dnxf_data_intr_general_block_intr_field_mapping_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->intr);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnxf_data_intr_general_chip_intr_remap_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_intr_general_chip_intr_remap_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_chip_intr_remap);
    data = (const dnxf_data_intr_general_chip_intr_remap_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->start);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->end);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->vector);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnxf_data_intr_general_chip_intr_enable_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_intr_general_chip_intr_enable_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_chip_intr_enable);
    data = (const dnxf_data_intr_general_chip_intr_enable_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->bit);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnxf_data_intr_general_active_on_init_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_active_on_init);

}

const dnxc_data_table_info_t *
dnxf_data_intr_general_disable_on_init_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_disable_on_init);

}

const dnxc_data_table_info_t *
dnxf_data_intr_general_disable_print_on_init_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_disable_print_on_init);

}

const dnxc_data_table_info_t *
dnxf_data_intr_general_skip_clear_on_regress_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_skip_clear_on_regress);

}

const dnxc_data_table_info_t *
dnxf_data_intr_general_block_intr_field_mapping_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_block_intr_field_mapping);

}

const dnxc_data_table_info_t *
dnxf_data_intr_general_chip_intr_remap_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_chip_intr_remap);

}

const dnxc_data_table_info_t *
dnxf_data_intr_general_chip_intr_enable_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_general, dnxf_data_intr_general_table_chip_intr_enable);

}






static shr_error_e
dnxf_data_intr_ser_init(
    int unit,
    dnxc_data_submodule_t *submodule_data)
{
    SHR_FUNC_INIT_VARS(unit);

    submodule_data->name = "ser";
    submodule_data->doc = "";
    
    submodule_data->nof_features = _dnxf_data_intr_ser_feature_nof;
    DNXC_DATA_ALLOC(submodule_data->features, dnxc_data_feature_t,  submodule_data->nof_features, "_dnxc_data intr ser features");

    
    submodule_data->nof_defines = _dnxf_data_intr_ser_define_nof;
    DNXC_DATA_ALLOC(submodule_data->defines, dnxc_data_define_t, submodule_data->nof_defines, "_dnxc_data intr ser defines");

    
    submodule_data->nof_tables = _dnxf_data_intr_ser_table_nof;
    DNXC_DATA_ALLOC(submodule_data->tables, dnxc_data_table_t, submodule_data->nof_tables, "_dnxc_data intr ser tables");

    
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].name = "mem_mask";
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].doc = "";
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].size_of_values = sizeof(dnxf_data_intr_ser_mem_mask_t);
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].entry_get = dnxf_data_intr_ser_mem_mask_entry_str_get;

    
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].nof_keys = 1;
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].keys[0].name = "index";
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].keys[0].doc = "";

    
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].nof_values = 3;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].nof_values, "_dnxf_data_intr_ser_table_mem_mask table values");
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].values[0].name = "reg";
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].values[0].type = "soc_reg_t";
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].values[0].doc = "";
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].values[0].offset = UTILEX_OFFSETOF(dnxf_data_intr_ser_mem_mask_t, reg);
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].values[1].name = "field";
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].values[1].type = "soc_field_t";
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].values[1].doc = "";
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].values[1].offset = UTILEX_OFFSETOF(dnxf_data_intr_ser_mem_mask_t, field);
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].values[2].name = "mode";
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].values[2].type = "dnxc_mem_mask_mode_e";
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].values[2].doc = "";
    submodule_data->tables[dnxf_data_intr_ser_table_mem_mask].values[2].offset = UTILEX_OFFSETOF(dnxf_data_intr_ser_mem_mask_t, mode);

    
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].name = "xor_mem";
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].doc = "";
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].flags |= DNXC_DATA_F_TABLE;
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].size_of_values = sizeof(dnxf_data_intr_ser_xor_mem_t);
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].entry_get = dnxf_data_intr_ser_xor_mem_entry_str_get;

    
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].nof_keys = 1;
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].keys[0].name = "index";
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].keys[0].doc = "";

    
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].nof_values = 3;
    DNXC_DATA_ALLOC(submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].values, dnxc_data_value_t, submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].nof_values, "_dnxf_data_intr_ser_table_xor_mem table values");
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].values[0].name = "mem";
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].values[0].type = "soc_mem_t";
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].values[0].doc = "";
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].values[0].offset = UTILEX_OFFSETOF(dnxf_data_intr_ser_xor_mem_t, mem);
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].values[1].name = "sram_banks_bits";
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].values[1].type = "int";
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].values[1].doc = "";
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].values[1].offset = UTILEX_OFFSETOF(dnxf_data_intr_ser_xor_mem_t, sram_banks_bits);
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].values[2].name = "entry_used_bits";
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].values[2].type = "int";
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].values[2].doc = "";
    submodule_data->tables[dnxf_data_intr_ser_table_xor_mem].values[2].offset = UTILEX_OFFSETOF(dnxf_data_intr_ser_xor_mem_t, entry_used_bits);


exit:
    SHR_FUNC_EXIT;
}


int
dnxf_data_intr_ser_feature_get(
    int unit,
    dnxf_data_intr_ser_feature_e feature)
{
    return dnxc_data_mgmt_feature_data_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_ser, feature);
}




const dnxf_data_intr_ser_mem_mask_t *
dnxf_data_intr_ser_mem_mask_get(
    int unit,
    int index)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_ser, dnxf_data_intr_ser_table_mem_mask);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, index, 0);
    return (const dnxf_data_intr_ser_mem_mask_t *) data;

}

const dnxf_data_intr_ser_xor_mem_t *
dnxf_data_intr_ser_xor_mem_get(
    int unit,
    int index)
{
    char *data;
    dnxc_data_table_t *table;

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_ser, dnxf_data_intr_ser_table_xor_mem);
    
    data = dnxc_data_mgmt_table_data_get(unit, table, index, 0);
    return (const dnxf_data_intr_ser_xor_mem_t *) data;

}


shr_error_e
dnxf_data_intr_ser_mem_mask_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_intr_ser_mem_mask_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_ser, dnxf_data_intr_ser_table_mem_mask);
    data = (const dnxf_data_intr_ser_mem_mask_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->reg);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->field);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->mode);
            break;
    }

    SHR_FUNC_EXIT;
}

shr_error_e
dnxf_data_intr_ser_xor_mem_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index)
{
    dnxc_data_table_t *table;
    const dnxf_data_intr_ser_xor_mem_t *data;
    SHR_FUNC_INIT_VARS(unit);

    
    table = dnxc_data_mgmt_table_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_ser, dnxf_data_intr_ser_table_xor_mem);
    data = (const dnxf_data_intr_ser_xor_mem_t *) dnxc_data_mgmt_table_data_diag_get(unit, table, key0, 0);
    switch (value_index)
    {
        case 0:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->mem);
            break;
        case 1:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->sram_banks_bits);
            break;
        case 2:
            sal_snprintf(buffer, DNXC_DATA_MGMT_MAX_TABLE_VALUE_LENGTH, "%d", data->entry_used_bits);
            break;
    }

    SHR_FUNC_EXIT;
}


const dnxc_data_table_info_t *
dnxf_data_intr_ser_mem_mask_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_ser, dnxf_data_intr_ser_table_mem_mask);

}

const dnxc_data_table_info_t *
dnxf_data_intr_ser_xor_mem_info_get(
    int unit)
{

    
    return dnxc_data_mgmt_table_info_get(unit, dnxf_data_module_intr, dnxf_data_intr_submodule_ser, dnxf_data_intr_ser_table_xor_mem);

}



shr_error_e
dnxf_data_intr_init(
    int unit,
    dnxc_data_module_t *module_data)
{
    SHR_FUNC_INIT_VARS(unit);

    
    module_data->name = "intr";
    module_data->nof_submodules = _dnxf_data_intr_submodule_nof;
    DNXC_DATA_ALLOC(module_data->submodules, dnxc_data_submodule_t, module_data->nof_submodules, "_dnxc_data intr submodules");

    
    SHR_IF_ERR_EXIT(dnxf_data_intr_general_init(unit, &module_data->submodules[dnxf_data_intr_submodule_general]));
    SHR_IF_ERR_EXIT(dnxf_data_intr_ser_init(unit, &module_data->submodules[dnxf_data_intr_submodule_ser]));
    
#ifdef BCM_DNXF1_SUPPORT

    if (dnxc_data_mgmt_is_ramon(unit))
    {
        SHR_IF_ERR_EXIT(ramon_a0_data_intr_attach(unit));
    }
    else

#endif 
    {
        SHR_EXIT();
    }

exit:
    SHR_FUNC_EXIT;
}
#undef BSL_LOG_MODULE


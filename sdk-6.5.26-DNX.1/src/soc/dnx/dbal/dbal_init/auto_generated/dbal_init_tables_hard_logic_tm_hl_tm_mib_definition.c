
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 * 
 */

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_fabric_stat_ctrl_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_FABRIC_STAT_CTRL;
    int is_valid = dnx_data_fabric.general.feature_get(unit, dnx_data_fabric_general_blocks_exist);
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_HIGH;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_FABRIC_STAT_CTRL, is_valid, maturity_level, "FABRIC_STAT_CTRL", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 2;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    table_entry->table_labels[1] = DBAL_LABEL_FABRIC;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 1);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_FMAC_ID, DBAL_FIELD_TYPE_DEF_FMAC_BLK_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 5);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LANE_SELECT, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 4;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_COUNTER_SELECT, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 5;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CLEAR_ON_READ, DBAL_FIELD_TYPE_DEF_BOOL, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 1;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_COUNTER_MODE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 2;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_DATA_COUNTER_HEADER, DBAL_FIELD_TYPE_DEF_BOOL, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 1;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_LANE_SELECT;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, FMAC_FMAL_STATISTICS_OUTPUT_CONTROLr, LANE_SELECTf));
                    access_params->block_index.formula_cb = fabric_stat_ctrl_lane_select_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_COUNTER_SELECT;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, FMAC_FMAL_STATISTICS_OUTPUT_CONTROLr, COUNTER_SELECTf));
                    access_params->block_index.formula_cb = fabric_stat_ctrl_lane_select_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CLEAR_ON_READ;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, FMAC_FMAL_STATISTICS_OUTPUT_CONTROLr, COUNTER_CLEAR_ON_READf));
                    access_params->block_index.formula_cb = fabric_stat_ctrl_lane_select_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_COUNTER_MODE;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, FMAC_FMAL_STATISTICS_OUTPUT_CONTROLr, DATA_COUNTER_MODEf));
                    access_params->block_index.formula_cb = fabric_stat_ctrl_lane_select_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_DATA_COUNTER_HEADER;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, FMAC_FMAL_STATISTICS_OUTPUT_CONTROLr, DATA_BYTE_COUNTER_HEADERf));
                    access_params->block_index.formula_cb = fabric_stat_ctrl_lane_select_blockindex_0_cb;
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_FABRIC_STAT_CTRL, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_fabric_stat_counters_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_FABRIC_STAT_COUNTERS;
    int is_valid = dnx_data_fabric.general.feature_get(unit, dnx_data_fabric_general_blocks_exist);
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_HIGH;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_FABRIC_STAT_COUNTERS, is_valid, maturity_level, "FABRIC_STAT_COUNTERS", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 2;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    table_entry->table_labels[1] = DBAL_LABEL_FABRIC;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 1);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_FMAC_ID, DBAL_FIELD_TYPE_DEF_FMAC_BLK_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 1);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_FMAC_COUNTER, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 48;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_FMAC_COUNTER;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, FMAC_FMAL_STATISTICS_OUTPUTr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = fabric_stat_ctrl_lane_select_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_FABRIC_STAT_COUNTERS, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_rx_part1_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_RX_PART1;
    int is_valid = TRUE;
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_RX_PART1, is_valid, maturity_level, "NIF_CDMAC_MIB_COUNTERS_RX_PART1", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PM_INDEX, DBAL_FIELD_TYPE_DEF_PM_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.max_value = dnx_data_nif.eth.nof_cdu_pms_get(unit);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LANE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 32);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R64, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R127, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R255, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R511, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R1023, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R1518, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RMGV, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R2047, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R4095, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R9216, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R16383, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RBCA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPROG0, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPROG1, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPROG2, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPROG3, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPKT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPOK, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RUCA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_NIF_CDMAC_MIB_COUNTERS_RX_PART1_RESERVED0, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RMCA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RXPF, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RXPP, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RXCF, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RFCS, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RERPKT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RFLR, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RJBR, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RMTUE, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_ROVR, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RVLN, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RDVLN, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R64;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R127;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R255;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R511;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R1023;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R1518;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RMGV;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R2047;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R4095;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R9216;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R16383;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RBCA;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPROG0;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPROG1;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPROG2;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPROG3;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPKT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_rpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPOK;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_rpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RUCA;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_rpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_NIF_CDMAC_MIB_COUNTERS_RX_PART1_RESERVED0;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_rpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RMCA;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_rpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RXPF;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_rpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RXPP;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_rpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RXCF;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_rpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RFCS;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_rfcs_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RERPKT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_rfcs_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RFLR;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_rfcs_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RJBR;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_rfcs_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RMTUE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_rfcs_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_ROVR;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_rfcs_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RVLN;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_rfcs_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RDVLN;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_rfcs_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_RX_PART1, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_rx_part2_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_RX_PART2;
    int is_valid = TRUE;
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_RX_PART2, is_valid, maturity_level, "NIF_CDMAC_MIB_COUNTERS_RX_PART2", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PM_INDEX, DBAL_FIELD_TYPE_DEF_PM_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.max_value = dnx_data_nif.eth.nof_cdu_pms_get(unit);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LANE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 26);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RXUO, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RXUDA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RXWSA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPRM, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFC0, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFCOFF0, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFC1, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFCOFF1, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFC2, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFCOFF2, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFC3, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFCOFF3, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFC4, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFCOFF4, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFC5, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFCOFF5, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFC6, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFCOFF6, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFC7, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFCOFF7, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RUND, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RFRG, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RRPKT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RESERVED1, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RBYT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 48;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RRBYT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 48;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RXUO;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rxuo_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RXUDA;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rxuo_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RXWSA;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rxuo_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPRM;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rxuo_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFC0;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rxuo_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFCOFF0;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rxuo_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFC1;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rxuo_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFCOFF1;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rxuo_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFC2;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rpfc2_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFCOFF2;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rpfc2_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFC3;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rpfc2_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFCOFF3;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rpfc2_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFC4;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rpfc2_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFCOFF4;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rpfc2_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFC5;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rpfc2_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFCOFF5;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rpfc2_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFC6;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rpfc6_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFCOFF6;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rpfc6_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFC7;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rpfc6_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFCOFF7;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rpfc6_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RUND;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rpfc6_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RFRG;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rpfc6_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RRPKT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rpfc6_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RESERVED1;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rpfc6_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RBYT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rbyt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RRBYT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rbyt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_RX_PART2, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_tx_part1_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_TX_PART1;
    int is_valid = TRUE;
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_TX_PART1, is_valid, maturity_level, "NIF_CDMAC_MIB_COUNTERS_TX_PART1", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PM_INDEX, DBAL_FIELD_TYPE_DEF_PM_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.max_value = dnx_data_nif.eth.nof_cdu_pms_get(unit);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LANE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 24);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T64, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T127, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T255, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T511, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T1023, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T1518, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TMGV, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T2047, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T4095, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T9216, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T16383, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TBCA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFC0, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFCOFF0, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFC1, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFCOFF1, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFC2, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFCOFF2, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFC3, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFCOFF3, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFC4, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFCOFF4, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFC5, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFCOFF5, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T64;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_t64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T127;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_t64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T255;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_t64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T511;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_t64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T1023;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_t64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T1518;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_t64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TMGV;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_t64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T2047;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_t64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T4095;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_t4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T9216;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_t4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T16383;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_t4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TBCA;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_t4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFC0;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_t4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFCOFF0;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_t4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFC1;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_t4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFCOFF1;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_t4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFC2;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_tpfc2_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFCOFF2;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_tpfc2_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFC3;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_tpfc2_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFCOFF3;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_tpfc2_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFC4;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_tpfc2_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFCOFF4;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_tpfc2_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFC5;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_tpfc2_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFCOFF5;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_tpfc2_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_TX_PART1, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_tx_part2_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_TX_PART2;
    int is_valid = TRUE;
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_TX_PART2, is_valid, maturity_level, "NIF_CDMAC_MIB_COUNTERS_TX_PART2", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PM_INDEX, DBAL_FIELD_TYPE_DEF_PM_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.max_value = dnx_data_nif.eth.nof_cdu_pms_get(unit);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LANE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 21);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFC6, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFCOFF6, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFC7, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFCOFF7, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPKT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPOK, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TUCA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TUFL, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TMCA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TXPF, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TXPP, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TXCF, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TFCS, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TERR, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TOVR, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TJBR, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TRPKT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TFRG, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TVLN, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TDVLN, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TBYT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 48;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFC6;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part2_tpfc6_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFCOFF6;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part2_tpfc6_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFC7;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part2_tpfc6_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFCOFF7;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part2_tpfc6_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPKT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part2_tpfc6_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPOK;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part2_tpfc6_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TUCA;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part2_tpfc6_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TUFL;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part2_tpfc6_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TMCA;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part2_tmca_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TXPF;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part2_tmca_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TXPP;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part2_tmca_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TXCF;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part2_tmca_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TFCS;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part2_tmca_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TERR;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part2_tmca_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TOVR;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part2_tmca_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TJBR;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part2_tmca_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TRPKT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rbyt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TFRG;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rbyt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TVLN;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rbyt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TDVLN;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rbyt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TBYT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rbyt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_TX_PART2, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_preempt_counters_rx_part1_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CDMAC_MIB_PREEMPT_COUNTERS_RX_PART1;
    int is_valid = dnx_data_mib.general.feature_get(unit, dnx_data_mib_general_mib_preempt_counters_support);
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CDMAC_MIB_PREEMPT_COUNTERS_RX_PART1, is_valid, maturity_level, "NIF_CDMAC_MIB_PREEMPT_COUNTERS_RX_PART1", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PM_INDEX, DBAL_FIELD_TYPE_DEF_PM_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.max_value = dnx_data_nif.eth.nof_cdu_pms_get(unit);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LANE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 32);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_R64, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_R127, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_R255, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_R511, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_R1023, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_R1518, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RMGV, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_R2047, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_R4095, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_R9216, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_R16383, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RBCA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RPROG0, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RPROG1, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RPROG2, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RPROG3, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RPKT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RPOK, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RUCA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_NIF_CDMAC_MIB_COUNTERS_RX_PART1_RESERVED3, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RMCA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RXPF, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RXPP, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RXCF, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RFCS, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RERPKT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RFLR, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RJBR, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RMTUE, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_ROVR, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RVLN, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RDVLN, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_R64;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_R127;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_R255;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_R511;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_R1023;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_R1518;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RMGV;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_R2047;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_R4095;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_R9216;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_R16383;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RBCA;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RPROG0;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RPROG1;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RPROG2;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RPROG3;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RPKT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RPOK;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RUCA;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_NIF_CDMAC_MIB_COUNTERS_RX_PART1_RESERVED3;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RMCA;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RXPF;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RXPP;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RXCF;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RFCS;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_rfcs_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RERPKT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_rfcs_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RFLR;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_rfcs_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RJBR;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_rfcs_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RMTUE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_rfcs_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_ROVR;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_rfcs_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RVLN;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_rfcs_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RDVLN;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_rfcs_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CDMAC_MIB_PREEMPT_COUNTERS_RX_PART1, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_preempt_counters_rx_part2_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CDMAC_MIB_PREEMPT_COUNTERS_RX_PART2;
    int is_valid = dnx_data_mib.general.feature_get(unit, dnx_data_mib_general_mib_preempt_counters_support);
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CDMAC_MIB_PREEMPT_COUNTERS_RX_PART2, is_valid, maturity_level, "NIF_CDMAC_MIB_PREEMPT_COUNTERS_RX_PART2", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PM_INDEX, DBAL_FIELD_TYPE_DEF_PM_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.max_value = dnx_data_nif.eth.nof_cdu_pms_get(unit);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LANE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 15);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RXUO, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RXUDA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RXWSA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RPRM, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RMFSE, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RMFAE, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RMFAO, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RMFC, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RMDIS, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RNFFMSE, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RFFMSE, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RREPLY, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RVERIFY, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RBYT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 48;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_RRBYT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 48;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RXUO;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part2_preempt_rxuo_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RXUDA;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part2_preempt_rxuo_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RXWSA;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part2_preempt_rxuo_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RPRM;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part2_preempt_rxuo_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RMFSE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part2_preempt_rxuo_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RMFAE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part2_preempt_rxuo_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RMFAO;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part2_preempt_rxuo_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RMFC;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part2_preempt_rxuo_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RMDIS;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part2_preempt_rmdis_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RNFFMSE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part2_preempt_rmdis_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RFFMSE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part2_preempt_rmdis_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RREPLY;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part2_preempt_rmdis_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RVERIFY;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part2_preempt_rmdis_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RBYT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part2_preempt_rbyt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_RRBYT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part2_preempt_rbyt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CDMAC_MIB_PREEMPT_COUNTERS_RX_PART2, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_preempt_counters_tx_part1_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CDMAC_MIB_PREEMPT_COUNTERS_TX_PART1;
    int is_valid = dnx_data_mib.general.feature_get(unit, dnx_data_mib_general_mib_preempt_counters_support);
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CDMAC_MIB_PREEMPT_COUNTERS_TX_PART1, is_valid, maturity_level, "NIF_CDMAC_MIB_PREEMPT_COUNTERS_TX_PART1", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PM_INDEX, DBAL_FIELD_TYPE_DEF_PM_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.max_value = dnx_data_nif.eth.nof_cdu_pms_get(unit);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LANE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 16);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_T64, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_T127, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_T255, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_T511, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_T1023, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_T1518, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TMGV, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_T2047, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_T4095, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_T9216, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_T16383, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TBCA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TMFAE, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TMFC, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TVERIFY, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TREPLY, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_T64;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part1_preempt_t64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_T127;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part1_preempt_t64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_T255;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part1_preempt_t64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_T511;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part1_preempt_t64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_T1023;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part1_preempt_t64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_T1518;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part1_preempt_t64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TMGV;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part1_preempt_t64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_T2047;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part1_preempt_t64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_T4095;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part1_preempt_t4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_T9216;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part1_preempt_t4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_T16383;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part1_preempt_t4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TBCA;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part1_preempt_t4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TMFAE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part1_preempt_t4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TMFC;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part1_preempt_t4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TVERIFY;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part1_preempt_t4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TREPLY;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part1_preempt_t4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CDMAC_MIB_PREEMPT_COUNTERS_TX_PART1, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_preempt_counters_tx_part2_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CDMAC_MIB_PREEMPT_COUNTERS_TX_PART2;
    int is_valid = dnx_data_mib.general.feature_get(unit, dnx_data_mib_general_mib_preempt_counters_support);
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CDMAC_MIB_PREEMPT_COUNTERS_TX_PART2, is_valid, maturity_level, "NIF_CDMAC_MIB_PREEMPT_COUNTERS_TX_PART2", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PM_INDEX, DBAL_FIELD_TYPE_DEF_PM_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.max_value = dnx_data_nif.eth.nof_cdu_pms_get(unit);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LANE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 15);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TPKT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TPOK, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TUCA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TUFL, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TMCA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TXCF, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TFCS, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TERR, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TOVR, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TJBR, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TRPKT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TFRG, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TVLN, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TDVLN, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PREEMPT_TBYT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 48;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TPKT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part2_preempt_tpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TPOK;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part2_preempt_tpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TUCA;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part2_preempt_tpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TUFL;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part2_preempt_tpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TMCA;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part2_preempt_tmca_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TXCF;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part2_preempt_tmca_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TFCS;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part2_preempt_tmca_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 256;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TERR;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part2_preempt_tmca_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 320;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TOVR;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part2_preempt_tmca_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TJBR;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part2_preempt_tmca_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 448;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TRPKT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part2_preempt_trpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TFRG;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part2_preempt_trpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 64;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TVLN;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part2_preempt_trpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 128;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TDVLN;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part2_preempt_trpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 192;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PREEMPT_TBYT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part2_preempt_trpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 384;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CDMAC_MIB_PREEMPT_COUNTERS_TX_PART2, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_row0_2_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW0_2;
    int is_valid = TRUE;
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW0_2, is_valid, maturity_level, "NIF_CDMAC_MIB_COUNTERS_ROW0_2", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PM_INDEX, DBAL_FIELD_TYPE_DEF_PM_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.max_value = dnx_data_nif.eth.nof_cdu_pms_get(unit);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LANE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 3);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW0, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW1, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW2, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW0;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW1;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW2;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_rpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW0_2, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_row3_5_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW3_5;
    int is_valid = TRUE;
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW3_5, is_valid, maturity_level, "NIF_CDMAC_MIB_COUNTERS_ROW3_5", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PM_INDEX, DBAL_FIELD_TYPE_DEF_PM_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.max_value = dnx_data_nif.eth.nof_cdu_pms_get(unit);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LANE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 3);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW3, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW4, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW5, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW3;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part1_rfcs_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW4;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rxuo_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW5;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rpfc2_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW3_5, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_row6_8_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW6_8;
    int is_valid = TRUE;
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW6_8, is_valid, maturity_level, "NIF_CDMAC_MIB_COUNTERS_ROW6_8", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PM_INDEX, DBAL_FIELD_TYPE_DEF_PM_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.max_value = dnx_data_nif.eth.nof_cdu_pms_get(unit);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LANE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 3);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW6, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW7, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW8, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW6;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rpfc6_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW7;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_t64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW8;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_t4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW6_8, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_row9_11_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW9_11;
    int is_valid = TRUE;
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW9_11, is_valid, maturity_level, "NIF_CDMAC_MIB_COUNTERS_ROW9_11", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PM_INDEX, DBAL_FIELD_TYPE_DEF_PM_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.max_value = dnx_data_nif.eth.nof_cdu_pms_get(unit);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LANE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 3);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW9, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW10, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW11, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW9;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part1_tpfc2_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW10;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part2_tpfc6_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW11;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_tx_part2_tmca_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW9_11, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_row12_12_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW12_12;
    int is_valid = TRUE;
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW12_12, is_valid, maturity_level, "NIF_CDMAC_MIB_COUNTERS_ROW12_12", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PM_INDEX, DBAL_FIELD_TYPE_DEF_PM_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.max_value = dnx_data_nif.eth.nof_cdu_pms_get(unit);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LANE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 1);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW12, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW12;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_rx_part2_rbyt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW12_12, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_row13_15_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW13_15;
    int is_valid = dnx_data_mib.general.feature_get(unit, dnx_data_mib_general_mib_preempt_counters_support);
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW13_15, is_valid, maturity_level, "NIF_CDMAC_MIB_COUNTERS_ROW13_15", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PM_INDEX, DBAL_FIELD_TYPE_DEF_PM_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.max_value = dnx_data_nif.eth.nof_cdu_pms_get(unit);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LANE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 3);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW13, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW14, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW15, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW13;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW14;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_r4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW15;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part1_preempt_rfcs_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW13_15, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_row16_18_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW16_18;
    int is_valid = dnx_data_mib.general.feature_get(unit, dnx_data_mib_general_mib_preempt_counters_support);
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW16_18, is_valid, maturity_level, "NIF_CDMAC_MIB_COUNTERS_ROW16_18", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PM_INDEX, DBAL_FIELD_TYPE_DEF_PM_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.max_value = dnx_data_nif.eth.nof_cdu_pms_get(unit);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LANE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 3);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW16, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW17, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW18, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW16;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part2_preempt_rxuo_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW17;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_rx_part2_preempt_rmdis_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW18;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_counters_row16_18_cdmac_mib_row18_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW16_18, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_row19_21_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW19_21;
    int is_valid = dnx_data_mib.general.feature_get(unit, dnx_data_mib_general_mib_preempt_counters_support);
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW19_21, is_valid, maturity_level, "NIF_CDMAC_MIB_COUNTERS_ROW19_21", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PM_INDEX, DBAL_FIELD_TYPE_DEF_PM_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.max_value = dnx_data_nif.eth.nof_cdu_pms_get(unit);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LANE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 3);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW19, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW20, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW21, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW19;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part1_preempt_t64_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW20;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part1_preempt_t4095_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW21;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part2_preempt_tpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW19_21, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_row22_23_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW22_23;
    int is_valid = dnx_data_mib.general.feature_get(unit, dnx_data_mib_general_mib_preempt_counters_support);
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW22_23, is_valid, maturity_level, "NIF_CDMAC_MIB_COUNTERS_ROW22_23", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PM_INDEX, DBAL_FIELD_TYPE_DEF_PM_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.max_value = dnx_data_nif.eth.nof_cdu_pms_get(unit);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LANE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 2);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW22, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CDMAC_MIB_ROW23, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 512;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW22;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part2_preempt_tmca_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CDMAC_MIB_ROW23;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDMIB_MEMm, MIB_DATAf));
                    access_params->entry_offset.formula_cb = nif_cdmac_mib_preempt_counters_tx_part2_preempt_trpkt_entryoffset_0_cb;
                    access_params->block_index.formula_cb = nif_cdmac_mib_counters_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CDMAC_MIB_COUNTERS_ROW22_23, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_clmac_mib_counters_common_rx_part1_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CLMAC_MIB_COUNTERS_COMMON_RX_PART1;
    int is_valid = dnx_data_nif.eth.feature_get(unit, dnx_data_nif_eth_is_clu_supported);
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_HIGH;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CLMAC_MIB_COUNTERS_COMMON_RX_PART1, is_valid, maturity_level, "NIF_CLMAC_MIB_COUNTERS_COMMON_RX_PART1", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 1);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CLU_LOGICAL_PORT, DBAL_FIELD_TYPE_DEF_CLU_LOGICAL_PORT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 27);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R64, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R127, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R255, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R511, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R1023, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R1518, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RMGV, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R2047, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R4095, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R9216, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_R16383, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RBCA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPROG0, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPROG1, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPROG2, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPROG3, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPKT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPOK, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RUCA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RMCA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RXPF, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RXPP, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RXCF, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RFCS, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RERPKT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RFLR, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RJBR, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R64;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_R64r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R127;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_R127r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R255;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_R255r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R511;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_R511r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R1023;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_R1023r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R1518;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_R1518r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RMGV;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RMGVr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R2047;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_R2047r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R4095;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_R4095r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R9216;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_R9216r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_R16383;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_R16383r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RBCA;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RBCAr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPROG0;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPROG0r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPROG1;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPROG1r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPROG2;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPROG2r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPROG3;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPROG3r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPKT;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPKTr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPOK;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPOKr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RUCA;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RUCAr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RMCA;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RMCAr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RXPF;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RXPFr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RXPP;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RXPPr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RXCF;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RXCFr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RFCS;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RFCSr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RERPKT;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RERPKTr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RFLR;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RFLRr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RJBR;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RJBRr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CLMAC_MIB_COUNTERS_COMMON_RX_PART1, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_clmac_mib_counters_common_rx_part2_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CLMAC_MIB_COUNTERS_COMMON_RX_PART2;
    int is_valid = dnx_data_nif.eth.feature_get(unit, dnx_data_nif_eth_is_clu_supported);
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_HIGH;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CLMAC_MIB_COUNTERS_COMMON_RX_PART2, is_valid, maturity_level, "NIF_CLMAC_MIB_COUNTERS_COMMON_RX_PART2", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 1);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CLU_LOGICAL_PORT, DBAL_FIELD_TYPE_DEF_CLU_LOGICAL_PORT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 29);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RMTUE, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_ROVR, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RVLN, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RDVLN, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RXUO, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RXUDA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RXWSA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPRM, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFC0, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFCOFF0, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFC1, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFCOFF1, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFC2, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFCOFF2, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFC3, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFCOFF3, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFC4, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFCOFF4, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFC5, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFCOFF5, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFC6, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFCOFF6, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFC7, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RPFCOFF7, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RUND, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RFRG, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RRPKT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RBYT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 48;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RRBYT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 48;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RMTUE;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RMTUEr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_ROVR;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_ROVRr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RVLN;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RVLNr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RDVLN;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RDVLNr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RXUO;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RXUOr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RXUDA;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RXUDAr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RXWSA;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RXWSAr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPRM;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPRMr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFC0;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPFC0r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFCOFF0;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPFCOFF0r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFC1;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPFC1r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFCOFF1;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPFCOFF1r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFC2;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPFC2r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFCOFF2;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPFCOFF2r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFC3;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPFC3r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFCOFF3;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPFCOFF3r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFC4;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPFC4r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFCOFF4;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPFCOFF4r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFC5;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPFC5r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFCOFF5;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPFCOFF5r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFC6;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPFC6r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFCOFF6;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPFCOFF6r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFC7;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPFC7r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RPFCOFF7;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RPFCOFF7r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RUND;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RUNDr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RFRG;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RFRGr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RRPKT;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RRPKTr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RBYT;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RBYTr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RRBYT;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RRBYTr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CLMAC_MIB_COUNTERS_COMMON_RX_PART2, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_clmac_mib_counters_common_tx_part1_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CLMAC_MIB_COUNTERS_COMMON_TX_PART1;
    int is_valid = dnx_data_nif.eth.feature_get(unit, dnx_data_nif_eth_is_clu_supported);
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_HIGH;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CLMAC_MIB_COUNTERS_COMMON_TX_PART1, is_valid, maturity_level, "NIF_CLMAC_MIB_COUNTERS_COMMON_TX_PART1", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 1);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CLU_LOGICAL_PORT, DBAL_FIELD_TYPE_DEF_CLU_LOGICAL_PORT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 21);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T64, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T127, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T255, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T511, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T1023, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T1518, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TMGV, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T2047, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T4095, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T9216, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_T16383, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TBCA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFC0, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFCOFF0, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFC1, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFCOFF1, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFC2, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFCOFF2, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFC3, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFCOFF3, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFC4, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T64;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_T64r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T127;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_T127r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T255;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_T255r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T511;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_T511r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T1023;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_T1023r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T1518;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_T1518r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TMGV;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TMGVr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T2047;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_T2047r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T4095;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_T4095r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T9216;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_T9216r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_T16383;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_T16383r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TBCA;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TBCAr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFC0;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TPFC0r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFCOFF0;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TPFCOFF0r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFC1;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TPFC1r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFCOFF1;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TPFCOFF1r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFC2;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TPFC2r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFCOFF2;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TPFCOFF2r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFC3;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TPFC3r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFCOFF3;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TPFCOFF3r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFC4;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TPFC4r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CLMAC_MIB_COUNTERS_COMMON_TX_PART1, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_clmac_mib_counters_common_tx_part2_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CLMAC_MIB_COUNTERS_COMMON_TX_PART2;
    int is_valid = dnx_data_nif.eth.feature_get(unit, dnx_data_nif_eth_is_clu_supported);
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_HIGH;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CLMAC_MIB_COUNTERS_COMMON_TX_PART2, is_valid, maturity_level, "NIF_CLMAC_MIB_COUNTERS_COMMON_TX_PART2", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 1);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CLU_LOGICAL_PORT, DBAL_FIELD_TYPE_DEF_CLU_LOGICAL_PORT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 24);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFCOFF4, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFC5, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFCOFF5, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFC6, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFCOFF6, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFC7, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPFCOFF7, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPKT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TPOK, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TUCA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TUFL, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TMCA, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TXPF, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TXPP, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TXCF, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TFCS, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TERR, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TOVR, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TJBR, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TRPKT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TFRG, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TVLN, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TDVLN, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TBYT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 48;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFCOFF4;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TPFCOFF4r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFC5;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TPFC5r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFCOFF5;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TPFCOFF5r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFC6;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TPFC6r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFCOFF6;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TPFCOFF6r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFC7;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TPFC7r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPFCOFF7;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TPFCOFF7r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPKT;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TPKTr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TPOK;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TPOKr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TUCA;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TUCAr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TUFL;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TUFLr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TMCA;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TMCAr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TXPF;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TXPFr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TXPP;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TXPPr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TXCF;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TXCFr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TFCS;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TFCSr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TERR;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TERRr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TOVR;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TOVRr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TJBR;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TJBRr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TRPKT;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TRPKTr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TFRG;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TFRGr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TVLN;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TVLNr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TDVLN;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TDVLNr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TBYT;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TBYTr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CLMAC_MIB_COUNTERS_COMMON_TX_PART2, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_clmac_mib_counters_dedicated_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_CLMAC_MIB_COUNTERS_DEDICATED;
    int is_valid = dnx_data_nif.eth.feature_get(unit, dnx_data_nif_eth_is_clu_supported);
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_HIGH;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_CLMAC_MIB_COUNTERS_DEDICATED, is_valid, maturity_level, "NIF_CLMAC_MIB_COUNTERS_DEDICATED", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 1);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CLU_LOGICAL_PORT, DBAL_FIELD_TYPE_DEF_CLU_LOGICAL_PORT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 28);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RVERIFY, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RREPLY, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RMCRC, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RTRFU, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RSCHCRC, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RX_EEE_LPI_EVENT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RX_EEE_LPI_DURATION, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RX_LLFC_PHY, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RX_LLFC_LOG, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RX_LLFC_CRC, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RX_HCFC, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RX_HCFC_CRC, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TVERIFY, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TREPLY, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TSCL, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TMCL, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TLCL, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TXCL, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TX_EEE_LPI_EVENT, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TX_EEE_LPI_DURATION, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TX_LLFC_LOG, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TX_HCFC, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TNCL, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_XTHOL, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 40;
            db_field.permission = DBAL_PERMISSION_TRIGGER;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TSPARE0, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 48;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TSPARE1, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 48;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TSPARE2, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 48;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TSPARE3, DBAL_FIELD_TYPE_DEF_ARRAY32, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 48;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RVERIFY;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RVERIFYr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RREPLY;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RREPLYr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RMCRC;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RMCRCr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RTRFU;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RTRFUr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RSCHCRC;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RSCHCRCr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RX_EEE_LPI_EVENT;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RX_EEE_LPI_EVENT_COUNTERr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RX_EEE_LPI_DURATION;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RX_EEE_LPI_DURATION_COUNTERr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RX_LLFC_PHY;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RX_LLFC_PHY_COUNTERr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RX_LLFC_LOG;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RX_LLFC_LOG_COUNTERr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RX_LLFC_CRC;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RX_LLFC_CRC_COUNTERr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RX_HCFC;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RX_HCFC_COUNTERr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RX_HCFC_CRC;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_RX_HCFC_CRC_COUNTERr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TVERIFY;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TVERIFYr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TREPLY;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TREPLYr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TSCL;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TSCLr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TMCL;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TMCLr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TLCL;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TLCLr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TXCL;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TXCLr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TX_EEE_LPI_EVENT;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TX_EEE_LPI_EVENT_COUNTERr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TX_EEE_LPI_DURATION;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TX_EEE_LPI_DURATION_COUNTERr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TX_LLFC_LOG;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TX_LLFC_LOG_COUNTERr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TX_HCFC;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TX_HCFC_COUNTERr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TNCL;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TNCLr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_XTHOL;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_XTHOLr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TSPARE0;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TSPARE0r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TSPARE1;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TSPARE1r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TSPARE2;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TSPARE2r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TSPARE3;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CLMIB_TSPARE3r, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->block_index.formula_cb = nif_clmac_mib_counters_common_rx_part1_r64_blockindex_0_cb;
                    {
                        access_params->data_offset.formula_int = 0;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_CLMAC_MIB_COUNTERS_DEDICATED, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_fabric_stat_gtimer_ctrl_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_FABRIC_STAT_GTIMER_CTRL;
    int is_valid = dnx_data_fabric.general.feature_get(unit, dnx_data_fabric_general_blocks_exist);
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_HIGH;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_FABRIC_STAT_GTIMER_CTRL, is_valid, maturity_level, "FABRIC_STAT_GTIMER_CTRL", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 2;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    table_entry->table_labels[1] = DBAL_LABEL_FABRIC;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 1);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_FMAC_ID, DBAL_FIELD_TYPE_DEF_FMAC_BLK_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 2);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_GTIMER_PERIOD, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 31;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_GTIMER_START, DBAL_FIELD_TYPE_DEF_BOOL, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 1;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_GTIMER_PERIOD;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, FMAC_FMAL_STATISTICS_GTIMERr, GTIMER_PERIODf));
                    access_params->block_index.formula_cb = fabric_stat_ctrl_lane_select_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_GTIMER_START;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, FMAC_FMAL_STATISTICS_GTIMERr, GTIMER_STARTf));
                    access_params->block_index.formula_cb = fabric_stat_ctrl_lane_select_blockindex_0_cb;
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_FABRIC_STAT_GTIMER_CTRL, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_ilkn_rx_stats_acc_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_ILKN_RX_STATS_ACC;
    int is_valid = TRUE;
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_ILKN_RX_STATS_ACC, is_valid, maturity_level, "NIF_ILKN_RX_STATS_ACC", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 1);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LOGICAL_PORT, DBAL_FIELD_TYPE_DEF_LOGICAL_PORT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 3);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LOGICAL_PORT_TYPE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 4;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CMD, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_ADDR, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 9;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_LOGICAL_PORT_TYPE;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILKN_SLE_RX_STATS_ACCr, SLE_RX_STATS_ACC_TYPEf));
                    access_params->block_index.formula_cb = nif_ilkn_rx_stats_acc_logical_port_type_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CMD;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILKN_SLE_RX_STATS_ACCr, SLE_RX_STATS_ACC_CMDf));
                    access_params->block_index.formula_cb = nif_ilkn_rx_stats_acc_logical_port_type_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_ADDR;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILKN_SLE_RX_STATS_ACCr, SLE_RX_STATS_ACC_ADDRf));
                    access_params->block_index.formula_cb = nif_ilkn_rx_stats_acc_logical_port_type_blockindex_0_cb;
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_ILKN_RX_STATS_ACC, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_ilkn_tx_stats_acc_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_ILKN_TX_STATS_ACC;
    int is_valid = TRUE;
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_ILKN_TX_STATS_ACC, is_valid, maturity_level, "NIF_ILKN_TX_STATS_ACC", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 1);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LOGICAL_PORT, DBAL_FIELD_TYPE_DEF_LOGICAL_PORT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 3);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LOGICAL_PORT_TYPE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 4;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CMD, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 3;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_ADDR, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 9;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_LOGICAL_PORT_TYPE;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILKN_SLE_TX_STATS_ACCr, SLE_TX_STATS_ACC_TYPEf));
                    access_params->block_index.formula_cb = nif_ilkn_rx_stats_acc_logical_port_type_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CMD;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILKN_SLE_TX_STATS_ACCr, SLE_TX_STATS_ACC_CMDf));
                    access_params->block_index.formula_cb = nif_ilkn_rx_stats_acc_logical_port_type_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_ADDR;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILKN_SLE_TX_STATS_ACCr, SLE_TX_STATS_ACC_ADDRf));
                    access_params->block_index.formula_cb = nif_ilkn_rx_stats_acc_logical_port_type_blockindex_0_cb;
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_ILKN_TX_STATS_ACC, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_ilkn_stats_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_ILKN_STATS;
    int is_valid = TRUE;
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_ILKN_STATS, is_valid, maturity_level, "NIF_ILKN_STATS", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 1);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LOGICAL_PORT, DBAL_FIELD_TYPE_DEF_LOGICAL_PORT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 12);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RX_PACKETS_LOW, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 32;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RX_PACKETS_HIGH, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 32;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RX_BYTES_LOW, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 32;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RX_BYTES_HIGH, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 32;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RX_ERR_PACKETS_LOW, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 32;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RX_ERR_PACKETS_HIGH, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 32;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TX_PACKETS_LOW, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 32;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TX_PACKETS_HIGH, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 32;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TX_BYTES_LOW, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 32;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TX_BYTES_HIGH, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 32;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TX_ERR_PACKETS_LOW, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 32;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TX_ERR_PACKETS_HIGH, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 32;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RX_PACKETS_LOW;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILKN_SLE_RX_STATS_RD_PKT_LOWr, SLE_RX_STATS_RD_PKT_LOW_RDATAf));
                    access_params->block_index.formula_cb = nif_ilkn_rx_stats_acc_logical_port_type_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RX_PACKETS_HIGH;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILKN_SLE_RX_STATS_RD_PKT_HIGHr, SLE_RX_STATS_RD_PKT_HIGH_RDATAf));
                    access_params->block_index.formula_cb = nif_ilkn_rx_stats_acc_logical_port_type_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RX_BYTES_LOW;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILKN_SLE_RX_STATS_RD_BYTE_LOWr, SLE_RX_STATS_RD_BYTE_LOW_RDATAf));
                    access_params->block_index.formula_cb = nif_ilkn_rx_stats_acc_logical_port_type_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RX_BYTES_HIGH;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILKN_SLE_RX_STATS_RD_BYTE_HIGHr, SLE_RX_STATS_RD_BYTE_HIGH_RDATAf));
                    access_params->block_index.formula_cb = nif_ilkn_rx_stats_acc_logical_port_type_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RX_ERR_PACKETS_LOW;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILKN_SLE_RX_STATS_RD_ERR_LOWr, SLE_RX_STATS_RD_ERR_LOW_RDATAf));
                    access_params->block_index.formula_cb = nif_ilkn_rx_stats_acc_logical_port_type_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RX_ERR_PACKETS_HIGH;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILKN_SLE_RX_STATS_RD_ERR_HIGHr, SLE_RX_STATS_RD_ERR_HIGH_RDATAf));
                    access_params->block_index.formula_cb = nif_ilkn_rx_stats_acc_logical_port_type_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TX_PACKETS_LOW;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILKN_SLE_TX_STATS_RD_PKT_LOWr, SLE_TX_STATS_RD_PKT_LOW_RDATAf));
                    access_params->block_index.formula_cb = nif_ilkn_rx_stats_acc_logical_port_type_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TX_PACKETS_HIGH;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILKN_SLE_TX_STATS_RD_PKT_HIGHr, SLE_TX_STATS_RD_PKT_HIGH_RDATAf));
                    access_params->block_index.formula_cb = nif_ilkn_rx_stats_acc_logical_port_type_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TX_BYTES_LOW;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILKN_SLE_TX_STATS_RD_BYTE_LOWr, SLE_TX_STATS_RD_BYTE_LOW_RDATAf));
                    access_params->block_index.formula_cb = nif_ilkn_rx_stats_acc_logical_port_type_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TX_BYTES_HIGH;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILKN_SLE_TX_STATS_RD_BYTE_HIGHr, SLE_TX_STATS_RD_BYTE_HIGH_RDATAf));
                    access_params->block_index.formula_cb = nif_ilkn_rx_stats_acc_logical_port_type_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TX_ERR_PACKETS_LOW;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILKN_SLE_TX_STATS_RD_ERR_LOWr, SLE_TX_STATS_RD_ERR_LOW_RDATAf));
                    access_params->block_index.formula_cb = nif_ilkn_rx_stats_acc_logical_port_type_blockindex_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TX_ERR_PACKETS_HIGH;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILKN_SLE_TX_STATS_RD_ERR_HIGHr, SLE_TX_STATS_RD_ERR_HIGH_RDATAf));
                    access_params->block_index.formula_cb = nif_ilkn_rx_stats_acc_logical_port_type_blockindex_0_cb;
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_ILKN_STATS, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_ilkn_elk_fec_counters_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_NIF_ILKN_ELK_FEC_COUNTERS;
    int is_valid = dnx_data_nif.ilkn.feature_get(unit, dnx_data_nif_ilkn_is_fec_supported);
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_HIGH;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_NIF_ILKN_ELK_FEC_COUNTERS, is_valid, maturity_level, "NIF_ILKN_ELK_FEC_COUNTERS", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MIB;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CORE_ID, DBAL_FIELD_TYPE_DEF_CORE_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_FEC_UNIT, DBAL_FIELD_TYPE_DEF_ILKN_FEC_UNIT_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        table_entry->nof_key_fields = field_index;
        dbal_db_init_table_calculate_key_size(table_entry);
    }
    {
        int field_index = 0;
        int result_type_counter = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 1);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 2);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RX_FEC_CORRECTED_CNT, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 32;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RX_FEC_UNCORRECTED_CNT, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 32;
            db_field.permission = DBAL_PERMISSION_READONLY;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    table_entry->core_mode = DBAL_CORE_MODE_DPC;
    dbal_db_init_table_add_result_type_physical_values_by_result_type_index(table_entry);
    {
        int map_idx = 0;
        int access_counter;
        map_idx = 0;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, EMPTY, sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        if (DBAL_IS_JR2_A0 || DBAL_IS_JR2_B0 || DBAL_IS_J2P_A0)
        {
            {
                table_db_access_params_struct_t * access_params;
                {
                    access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                    dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                    access_counter++;
                    access_params->access_field_id = DBAL_FIELD_RX_FEC_CORRECTED_CNT;
                    access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                    {
                        SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILE_RX_FEC_DECODER_CORRECTED_CODE_WORD_CNTr, RX_FEC_N_CORRECTED_CODE_WORD_CNTf));
                        access_params->array_offset.formula_cb = nif_ilkn_fec_enable_fec_tx_serdes_en_arrayoffset_0_cb;
                        access_params->block_index.formula_cb = example_table_register_group_threshold_blockindex_1_cb;
                    }
                }
            }
        }
        if (DBAL_IS_J2C_A0)
        {
            {
                table_db_access_params_struct_t * access_params;
                {
                    access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                    dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                    access_counter++;
                    access_params->access_field_id = DBAL_FIELD_RX_FEC_CORRECTED_CNT;
                    access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                    {
                        SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDU_RX_FEC_DECODER_CORRECTED_CODE_WORD_CNTr, RX_FEC_N_CORRECTED_CODE_WORD_CNTf));
                        access_params->array_offset.formula_cb = nif_ilkn_fec_enable_fec_tx_serdes_en_arrayoffset_1_cb;
                        access_params->block_index.formula_cb = nif_ilkn_elk_fec_counters_rx_fec_corrected_cnt_blockindex_0_cb;
                    }
                }
            }
        }
        if (DBAL_IS_JR2_A0 || DBAL_IS_JR2_B0 || DBAL_IS_J2P_A0)
        {
            {
                table_db_access_params_struct_t * access_params;
                {
                    access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                    dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                    access_counter++;
                    access_params->access_field_id = DBAL_FIELD_RX_FEC_UNCORRECTED_CNT;
                    access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                    {
                        SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ILE_RX_FEC_DECODER_UNCORRECTED_CODE_WORD_CNTr, RX_FEC_N_UNCORRECTED_CODE_WORD_CNTf));
                        access_params->array_offset.formula_cb = nif_ilkn_fec_enable_fec_tx_serdes_en_arrayoffset_0_cb;
                        access_params->block_index.formula_cb = example_table_register_group_threshold_blockindex_1_cb;
                    }
                }
            }
        }
        if (DBAL_IS_J2C_A0)
        {
            {
                table_db_access_params_struct_t * access_params;
                {
                    access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                    dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                    access_counter++;
                    access_params->access_field_id = DBAL_FIELD_RX_FEC_UNCORRECTED_CNT;
                    access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                    {
                        SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, CDU_RX_FEC_DECODER_UNCORRECTED_CODE_WORD_CNTr, RX_FEC_N_UNCORRECTED_CODE_WORD_CNTf));
                        access_params->array_offset.formula_cb = nif_ilkn_fec_enable_fec_tx_serdes_en_arrayoffset_1_cb;
                        access_params->block_index.formula_cb = nif_ilkn_elk_fec_counters_rx_fec_corrected_cnt_blockindex_0_cb;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_NIF_ILKN_ELK_FEC_COUNTERS, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_fabric_stat_ctrl_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_fabric_stat_counters_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_rx_part1_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_rx_part2_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_tx_part1_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_tx_part2_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_preempt_counters_rx_part1_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_preempt_counters_rx_part2_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_preempt_counters_tx_part1_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_preempt_counters_tx_part2_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_row0_2_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_row3_5_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_row6_8_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_row9_11_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_row12_12_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_row13_15_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_row16_18_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_row19_21_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_cdmac_mib_counters_row22_23_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_clmac_mib_counters_common_rx_part1_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_clmac_mib_counters_common_rx_part2_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_clmac_mib_counters_common_tx_part1_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_clmac_mib_counters_common_tx_part2_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_clmac_mib_counters_dedicated_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_fabric_stat_gtimer_ctrl_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_ilkn_rx_stats_acc_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_ilkn_tx_stats_acc_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_ilkn_stats_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_tm_hl_tm_mib_definition_nif_ilkn_elk_fec_counters_init(unit, cur_table_param, table_info));
exit:
    SHR_FUNC_EXIT;
}

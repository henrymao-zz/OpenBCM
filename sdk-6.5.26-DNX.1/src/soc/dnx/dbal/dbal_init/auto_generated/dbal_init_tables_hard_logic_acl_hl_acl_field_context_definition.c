
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 * 
 */

shr_error_e
_dbal_init_tables_hard_logic_acl_hl_acl_field_context_definition_field_context_hash_configuration_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_FIELD_CONTEXT_HASH_CONFIGURATION;
    int is_valid = TRUE;
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_HIGH;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_FIELD_CONTEXT_HASH_CONFIGURATION, is_valid, maturity_level, "FIELD_CONTEXT_HASH_CONFIGURATION", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_FIELD;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 1);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_FIELD_PMF_CTX_ID, DBAL_FIELD_TYPE_DEF_FIELD_PMF_CTX_ID, dbal_db_field));
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
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_COMPRESSION, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 1;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_SWITCH, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
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
                access_params->access_field_id = DBAL_FIELD_COMPRESSION;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_TRJ_CFGr, COMPRESSIONf));
                    access_params->data_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_SWITCH;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_TRJ_CFGr, SWITCH_ENABLEf));
                    access_params->data_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_FIELD_CONTEXT_HASH_CONFIGURATION, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_acl_hl_acl_field_context_definition_field_context_hash_configuration_with_key_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_FIELD_CONTEXT_HASH_CONFIGURATION_WITH_KEY;
    int is_valid = TRUE;
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_HIGH;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_FIELD_CONTEXT_HASH_CONFIGURATION_WITH_KEY, is_valid, maturity_level, "FIELD_CONTEXT_HASH_CONFIGURATION_WITH_KEY", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_FIELD;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 1);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_FIELD_PMF_CTX_ID, DBAL_FIELD_TYPE_DEF_FIELD_PMF_CTX_ID, dbal_db_field));
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
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 1 + dnx_data_field.context.nof_hash_keys_get(unit) + dnx_data_field.context.nof_hash_keys_get(unit));
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_HASH_FUNC, DBAL_FIELD_TYPE_DEF_CONTEXT_HASH_FUNCTION, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_HASH_ACTION, DBAL_FIELD_TYPE_DEF_HASH_ACTION, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.nof_instances = dnx_data_field.context.nof_hash_keys_get(unit);
            db_field.is_validate_nof_instances = TRUE;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_CRC_SELECT, DBAL_FIELD_TYPE_DEF_CRC_SELECT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.nof_instances = dnx_data_field.context.nof_hash_keys_get(unit);
            db_field.is_validate_nof_instances = TRUE;
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
                access_params->access_field_id = DBAL_FIELD_HASH_FUNC;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_TRAJECTORY_CONFIGURATIONm, TRJ_CRC_SELECTf));
                    access_params->entry_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_HASH_ACTION;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                access_params->inst_idx = DBAL_ENUM_FVAL_FIELD_HASH_LB_KEY_ADDITIONAL_LB;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_TRAJECTORY_CONFIGURATIONm, ADDITIONAL_LB_KEY_FUNCTION_SELECTf));
                    access_params->entry_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_HASH_ACTION;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                access_params->inst_idx = DBAL_ENUM_FVAL_FIELD_HASH_LB_KEY_ECMP0_LB;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_TRAJECTORY_CONFIGURATIONm, ECMP_LB_0_FUNCTION_SELECTf));
                    access_params->entry_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_HASH_ACTION;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                access_params->inst_idx = DBAL_ENUM_FVAL_FIELD_HASH_LB_KEY_ECMP1_LB;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_TRAJECTORY_CONFIGURATIONm, ECMP_LB_1_FUNCTION_SELECTf));
                    access_params->entry_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_HASH_ACTION;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                access_params->inst_idx = DBAL_ENUM_FVAL_FIELD_HASH_LB_KEY_ECMP2_LB;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_TRAJECTORY_CONFIGURATIONm, ECMP_LB_2_FUNCTION_SELECTf));
                    access_params->entry_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_HASH_ACTION;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                access_params->inst_idx = DBAL_ENUM_FVAL_FIELD_HASH_LB_KEY_LAG_LB;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_TRAJECTORY_CONFIGURATIONm, LAG_LB_KEY_FUNCTION_SELECTf));
                    access_params->entry_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_HASH_ACTION;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                access_params->inst_idx = DBAL_ENUM_FVAL_FIELD_HASH_LB_KEY_NWK_LB;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_TRAJECTORY_CONFIGURATIONm, NWK_LB_KEY_FUNCTION_SELECTf));
                    access_params->entry_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CRC_SELECT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                access_params->inst_idx = DBAL_ENUM_FVAL_FIELD_HASH_LB_KEY_ADDITIONAL_LB;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_TRAJECTORY_CONFIGURATIONm, ADDITIONAL_LB_KEY_CRC_SELECTf));
                    access_params->entry_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CRC_SELECT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                access_params->inst_idx = DBAL_ENUM_FVAL_FIELD_HASH_LB_KEY_ECMP0_LB;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_TRAJECTORY_CONFIGURATIONm, ECMP_LB_0_CRC_SELECTf));
                    access_params->entry_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CRC_SELECT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                access_params->inst_idx = DBAL_ENUM_FVAL_FIELD_HASH_LB_KEY_ECMP1_LB;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_TRAJECTORY_CONFIGURATIONm, ECMP_LB_1_CRC_SELECTf));
                    access_params->entry_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CRC_SELECT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                access_params->inst_idx = DBAL_ENUM_FVAL_FIELD_HASH_LB_KEY_ECMP2_LB;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_TRAJECTORY_CONFIGURATIONm, ECMP_LB_2_CRC_SELECTf));
                    access_params->entry_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CRC_SELECT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                access_params->inst_idx = DBAL_ENUM_FVAL_FIELD_HASH_LB_KEY_LAG_LB;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_TRAJECTORY_CONFIGURATIONm, LAG_LB_KEY_CRC_SELECTf));
                    access_params->entry_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_CRC_SELECT;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                access_params->inst_idx = DBAL_ENUM_FVAL_FIELD_HASH_LB_KEY_NWK_LB;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_TRAJECTORY_CONFIGURATIONm, NWK_LB_KEY_CRC_SELECTf));
                    access_params->entry_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_FIELD_CONTEXT_HASH_CONFIGURATION_WITH_KEY, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_acl_hl_acl_field_context_definition_field_ipmf1_context_general_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_FIELD_IPMF1_CONTEXT_GENERAL;
    int is_valid = TRUE;
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_HIGH;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_FIELD_IPMF1_CONTEXT_GENERAL, is_valid, maturity_level, "FIELD_IPMF1_CONTEXT_GENERAL", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_FIELD;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 1);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_FIELD_PMF_CTX_ID, DBAL_FIELD_TYPE_DEF_FIELD_PMF_CTX_ID, dbal_db_field));
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
        DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 4);
        DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_SYSTEM_HEADER_PROFILE, DBAL_FIELD_TYPE_DEF_SYSTEM_HEADER_PROFILE, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 4;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PPH_TYPE, DBAL_FIELD_TYPE_DEF_PPH_TYPE, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_FIRST_CONTEXT_PROFILE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 5;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PGM_EVENTOR_FIFO_CONTEXT_ENABLE, DBAL_FIELD_TYPE_DEF_BOOL, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
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
                access_params->access_field_id = DBAL_FIELD_SYSTEM_HEADER_PROFILE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_PMF_PROGRAM_GENERALm, SYSTEM_HEADER_PROFILEf));
                    access_params->entry_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PPH_TYPE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_PMF_PROGRAM_GENERALm, PPH_TYPEf));
                    access_params->entry_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_FIRST_CONTEXT_PROFILE;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_MAP_1ST_CONTEXT_PROFILEr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->data_offset.formula_cb = field_ipmf1_context_general_first_context_profile_dataoffset_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PGM_EVENTOR_FIFO_CONTEXT_ENABLE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_PROGRAM_KEY_GEN_VARm, EVENTOR_FIFO_CONTEXT_ENABLEf));
                    access_params->entry_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_FIELD_IPMF1_CONTEXT_GENERAL, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_acl_hl_acl_field_context_definition_field_ipmf2_context_general_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_FIELD_IPMF2_CONTEXT_GENERAL;
    int is_valid = TRUE;
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_HIGH;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_FIELD_IPMF2_CONTEXT_GENERAL, is_valid, maturity_level, "FIELD_IPMF2_CONTEXT_GENERAL", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_FIELD;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 1);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_FIELD_PMF_CTX_ID, DBAL_FIELD_TYPE_DEF_FIELD_PMF_CTX_ID, dbal_db_field));
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
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_NUM_LAYERS_TO_REMOVE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 2;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_NUM_BYTES_TO_REMOVE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 7;
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
                access_params->access_field_id = DBAL_FIELD_NUM_LAYERS_TO_REMOVE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPD_PMF_PROGRAM_GENERALm, BYTES_TO_REMOVE_HEADERf));
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_NUM_BYTES_TO_REMOVE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPD_PMF_PROGRAM_GENERALm, BYTES_TO_REMOVE_FIXf));
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_FIELD_IPMF2_CONTEXT_GENERAL, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_acl_hl_acl_field_context_definition_field_pmf_context_general_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_FIELD_PMF_CONTEXT_GENERAL;
    int is_valid = TRUE;
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_PARTIALLY_FUNCTIONAL;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_FIELD_PMF_CONTEXT_GENERAL, is_valid, maturity_level, "FIELD_PMF_CONTEXT_GENERAL", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_FIELD;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 2);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_FIELD_PMF_CTX_ID, DBAL_FIELD_TYPE_DEF_FIELD_PMF_CTX_ID, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, TRUE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_FIELD_PMF_STAGE, DBAL_FIELD_TYPE_DEF_FIELD_PMF_STAGE, dbal_db_field));
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
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_ACL_CONTEXT_PROFILE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 6;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_FWD_CONTEXT_PROFILE, DBAL_FIELD_TYPE_DEF_HEXA, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 5;
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
            field_index += dbal_db_field->nof_instances;
        }
        {
            dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PROGRAM_KEY_GEN_VAR, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 32;
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
                int condition_index = 0;
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_ACL_CONTEXT_PROFILE;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_condition(unit, &access_params->access_condition[condition_index], DBAL_CONDITION_EQUAL_TO, DBAL_FIELD_FIELD_PMF_STAGE, 0, (uint32) DBAL_ENUM_FVAL_FIELD_PMF_STAGE_IPMF1));
                condition_index++;
                access_params->nof_conditions = condition_index;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_ACL_CONTEXT_PROFILE_MAPr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->data_offset.formula_cb = field_pmf_context_general_acl_context_profile_dataoffset_0_cb;
                }
            }
            {
                int condition_index = 0;
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_ACL_CONTEXT_PROFILE;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_condition(unit, &access_params->access_condition[condition_index], DBAL_CONDITION_EQUAL_TO, DBAL_FIELD_FIELD_PMF_STAGE, 0, (uint32) DBAL_ENUM_FVAL_FIELD_PMF_STAGE_IPMF3));
                condition_index++;
                access_params->nof_conditions = condition_index;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPD_ACL_CONTEXT_PROFILE_MAPr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->data_offset.formula_cb = field_pmf_context_general_acl_context_profile_dataoffset_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                int condition_index = 0;
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_FWD_CONTEXT_PROFILE;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_condition(unit, &access_params->access_condition[condition_index], DBAL_CONDITION_EQUAL_TO, DBAL_FIELD_FIELD_PMF_STAGE, 0, (uint32) DBAL_ENUM_FVAL_FIELD_PMF_STAGE_IPMF1));
                condition_index++;
                access_params->nof_conditions = condition_index;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_FWD_CONTEXT_PROFILE_MAPr, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    access_params->data_offset.formula_cb = field_pmf_context_general_fwd_context_profile_dataoffset_0_cb;
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                int condition_index = 0;
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PROGRAM_KEY_GEN_VAR;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_condition(unit, &access_params->access_condition[condition_index], DBAL_CONDITION_EQUAL_TO, DBAL_FIELD_FIELD_PMF_STAGE, 0, (uint32) DBAL_ENUM_FVAL_FIELD_PMF_STAGE_IPMF1));
                condition_index++;
                access_params->nof_conditions = condition_index;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_PROGRAM_KEY_GEN_VARm, PROGRAM_KEY_GEN_VARf));
                    access_params->entry_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
            {
                int condition_index = 0;
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_PROGRAM_KEY_GEN_VAR;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_condition(unit, &access_params->access_condition[condition_index], DBAL_CONDITION_EQUAL_TO, DBAL_FIELD_FIELD_PMF_STAGE, 0, (uint32) DBAL_ENUM_FVAL_FIELD_PMF_STAGE_IPMF3));
                condition_index++;
                access_params->nof_conditions = condition_index;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPD_PROGRAM_KEY_GEN_VARm, PROGRAM_KEY_GEN_VARf));
                    access_params->entry_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_FIELD_PMF_CONTEXT_GENERAL, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_acl_hl_acl_field_context_definition_field_pmf_elephant_learn_cfg_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_FIELD_PMF_ELEPHANT_LEARN_CFG;
    int is_valid = TRUE;
    uint8 is_skip_table_init = FALSE;
    uint8 is_compatible_with_all_images = TRUE;
    char * custom_image = NULL;
    dbal_maturity_level_e maturity_level;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    maturity_level = DBAL_MATURITY_HIGH;
    SHR_IF_ERR_EXIT(dbal_db_init_table_general_info_and_image_handle(unit, table_entry, DBAL_TABLE_FIELD_PMF_ELEPHANT_LEARN_CFG, is_valid, maturity_level, "FIELD_PMF_ELEPHANT_LEARN_CFG", DBAL_ACCESS_METHOD_HARD_LOGIC, custom_image, is_compatible_with_all_images, &is_skip_table_init));
    if (is_skip_table_init)
    {
        SHR_EXIT();
    }
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_FIELD;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 1);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_FIELD_PMF_CTX_ID, DBAL_FIELD_TYPE_DEF_FIELD_PMF_CTX_ID, dbal_db_field));
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
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_ELEPHANT_LEARN_ENABLE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
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
                access_params->access_field_id = DBAL_FIELD_ELEPHANT_LEARN_ENABLE;
                access_params->access_type = DBAL_HL_ACCESS_REGISTER;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, IPPC_ELEPHANT_LEARNr, ELEPHANT_LEARN_ENABLEf));
                    access_params->data_offset.formula_cb = field_context_hash_configuration_compression_dataoffset_0_cb;
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_FIELD_PMF_ELEPHANT_LEARN_CFG, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dbal_init_tables_hard_logic_acl_hl_acl_field_context_definition_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_acl_hl_acl_field_context_definition_field_context_hash_configuration_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_acl_hl_acl_field_context_definition_field_context_hash_configuration_with_key_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_acl_hl_acl_field_context_definition_field_ipmf1_context_general_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_acl_hl_acl_field_context_definition_field_ipmf2_context_general_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_acl_hl_acl_field_context_definition_field_pmf_context_general_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_acl_hl_acl_field_context_definition_field_pmf_elephant_learn_cfg_init(unit, cur_table_param, table_info));
exit:
    SHR_FUNC_EXIT;
}

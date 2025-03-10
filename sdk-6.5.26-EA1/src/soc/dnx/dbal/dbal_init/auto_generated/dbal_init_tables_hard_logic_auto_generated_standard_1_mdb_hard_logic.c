
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 * 
 */

shr_error_e
_dbal_init_tables_hard_logic_auto_generated_standard_1_mdb_hard_logic_esem_default_result_table_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_ESEM_DEFAULT_RESULT_TABLE;
    int is_valid = TRUE;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    SHR_IF_ERR_EXIT(dbal_db_init_general_info_set(unit, table_entry, DBAL_TABLE_ESEM_DEFAULT_RESULT_TABLE, is_valid, "ESEM_DEFAULT_RESULT_TABLE", DBAL_ACCESS_METHOD_HARD_LOGIC));
    table_entry->maturity_level = DBAL_MATURITY_HIGH;
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_VLAN;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 1);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_ESEM_DEFAULT_RESULT_PROFILE, DBAL_FIELD_TYPE_DEF_ESEM_DEFAULT_RESULT_PROFILE, dbal_db_field));
            dbal_db_init_table_field_params_init(&db_field);
            db_field.size = 4;
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
        DBAL_DB_INIT_TABLE_NOF_RESULT_TYPES_SET(table_entry, 3);
        SHR_BITSET(table_entry->indications_bm, DBAL_TABLE_IND_HAS_RESULT_TYPE);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        result_type_counter = DBAL_RESULT_TYPE_ESEM_DEFAULT_RESULT_TABLE_ETPS_AC_STAT;
        field_index = 0;
        if (dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE___valid_get(unit) != 0)
        {
            DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 9);
            DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RESULT_TYPE, DBAL_FIELD_TYPE_DEF_RESULT_TYPE, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE_get(unit);
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_VLAN_EDIT_VID_2, DBAL_FIELD_TYPE_DEF_VLAN_ID, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 12;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_VLAN_EDIT_VID_1, DBAL_FIELD_TYPE_DEF_VLAN_ID, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 12;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_ACTION_PROFILE, DBAL_FIELD_TYPE_DEF_ACTION_PROFILE, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 2;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_VLAN_EDIT_PROFILE, DBAL_FIELD_TYPE_DEF_VLAN_EDIT_PROFILE, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 6;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_REMARK_PROFILE, DBAL_FIELD_TYPE_DEF_REMARK_PROFILE, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 5;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_ENCAP_QOS_MODEL, DBAL_FIELD_TYPE_DEF_ENCAP_QOS_MODEL, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 3;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_OUT_LIF_PROFILE, DBAL_FIELD_TYPE_DEF_OUT_LIF_PROFILE, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 6;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_EGRESS_LAST_LAYER, DBAL_FIELD_TYPE_DEF_EGRESS_LAST_LAYER, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 1;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
        }
        else
        {
            table_entry->multi_res_info[result_type_counter].is_disabled = TRUE;
            DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 0);
        }
        sal_strncpy(table_entry->multi_res_info[result_type_counter].result_type_name, "ETPS_AC_STAT", sizeof(table_entry->multi_res_info[result_type_counter].result_type_name));
        result_type_counter = DBAL_RESULT_TYPE_ESEM_DEFAULT_RESULT_TABLE_ETPS_DUAL_HOMING;
        field_index = 0;
        if (dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE___valid_get(unit) != 0)
        {
            DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 2);
            DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RESULT_TYPE, DBAL_FIELD_TYPE_DEF_RESULT_TYPE, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE_get(unit);
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_DUAL_HOMING, DBAL_FIELD_TYPE_DEF_DUAL_HOMING, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 32;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
        }
        else
        {
            table_entry->multi_res_info[result_type_counter].is_disabled = TRUE;
            DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 0);
        }
        sal_strncpy(table_entry->multi_res_info[result_type_counter].result_type_name, "ETPS_DUAL_HOMING", sizeof(table_entry->multi_res_info[result_type_counter].result_type_name));
        result_type_counter = DBAL_RESULT_TYPE_ESEM_DEFAULT_RESULT_TABLE_ETPS_NULL;
        field_index = 0;
        if (dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE___valid_get(unit) != 0)
        {
            DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 2);
            DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RESULT_TYPE, DBAL_FIELD_TYPE_DEF_RESULT_TYPE, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE_get(unit);
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_EGRESS_LAST_LAYER, DBAL_FIELD_TYPE_DEF_EGRESS_LAST_LAYER, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 1;
                dbal_db_init_table_set_field_arr_prefix(unit, &db_field, dnx_data_dnx2_arr.prefix.ETPP_ETPS_FORMATS___prefix_Always_Last_Layer_get(unit), 8);
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
        }
        else
        {
            table_entry->multi_res_info[result_type_counter].is_disabled = TRUE;
            DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 0);
        }
        sal_strncpy(table_entry->multi_res_info[result_type_counter].result_type_name, "ETPS_NULL", sizeof(table_entry->multi_res_info[result_type_counter].result_type_name));
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    {
        uint8 is_standard_1 = TRUE;
        uint8 is_compatible_with_all_images = FALSE;
        DBAL_DB_INIT_TABLE_IMAGE_SPECIFIC_TABLE_INDICATION_SET(table_entry, is_standard_1, is_compatible_with_all_images);
        SHR_IF_ERR_EXIT(dbal_db_init_table_set_table_incompatible_image_sw_state_indication(unit, DBAL_TABLE_ESEM_DEFAULT_RESULT_TABLE, is_standard_1, is_compatible_with_all_images));
    }
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    SHR_IF_ERR_EXIT(dbal_db_init_table_add_result_type_physical_values_by_reference_field(unit, &(table_entry->multi_res_info[DBAL_RESULT_TYPE_ESEM_DEFAULT_RESULT_TABLE_ETPS_AC_STAT]), DBAL_FIELD_TYPE_DEF_ETPP_ETPS_FORMATS));
    SHR_IF_ERR_EXIT(dbal_db_init_table_add_result_type_physical_values_by_reference_field(unit, &(table_entry->multi_res_info[DBAL_RESULT_TYPE_ESEM_DEFAULT_RESULT_TABLE_ETPS_DUAL_HOMING]), DBAL_FIELD_TYPE_DEF_ETPP_ETPS_FORMATS));
    SHR_IF_ERR_EXIT(dbal_db_init_table_add_result_type_physical_values_by_reference_field(unit, &(table_entry->multi_res_info[DBAL_RESULT_TYPE_ESEM_DEFAULT_RESULT_TABLE_ETPS_NULL]), DBAL_FIELD_TYPE_DEF_ETPP_ETPS_FORMATS));
    {
        int map_idx = 0;
        int access_counter;
        map_idx = DBAL_RESULT_TYPE_ESEM_DEFAULT_RESULT_TABLE_ETPS_AC_STAT;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, "ETPS_AC_STAT", sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RESULT_TYPE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPC_ESEM_DEFAULT_RESULT_TABLEm, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    {
                        uint32 result_size__result_type = 0;
                        result_size__result_type += dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE_get(unit);
                        access_params->data_offset.formula_int = 60-result_size__result_type;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_VLAN_EDIT_VID_2;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPC_ESEM_DEFAULT_RESULT_TABLEm, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    {
                        uint32 result_size__result_type = 0;
                        result_size__result_type += dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE_get(unit);
                        access_params->data_offset.formula_int = 60-result_size__result_type-12;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_VLAN_EDIT_VID_1;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPC_ESEM_DEFAULT_RESULT_TABLEm, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    {
                        uint32 result_size__result_type = 0;
                        result_size__result_type += dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE_get(unit);
                        access_params->data_offset.formula_int = 60-result_size__result_type-12-12;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_ACTION_PROFILE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPC_ESEM_DEFAULT_RESULT_TABLEm, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    {
                        uint32 result_size__result_type = 0;
                        result_size__result_type += dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE_get(unit);
                        access_params->data_offset.formula_int = 60-result_size__result_type-12-12-2;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_VLAN_EDIT_PROFILE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPC_ESEM_DEFAULT_RESULT_TABLEm, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    {
                        uint32 result_size__result_type = 0;
                        result_size__result_type += dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE_get(unit);
                        access_params->data_offset.formula_int = 60-result_size__result_type-12-12-2-6;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_REMARK_PROFILE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPC_ESEM_DEFAULT_RESULT_TABLEm, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    {
                        uint32 result_size__result_type = 0;
                        result_size__result_type += dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE_get(unit);
                        access_params->data_offset.formula_int = 60-result_size__result_type-12-12-2-6-5;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_ENCAP_QOS_MODEL;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPC_ESEM_DEFAULT_RESULT_TABLEm, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    {
                        uint32 result_size__result_type = 0;
                        result_size__result_type += dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE_get(unit);
                        access_params->data_offset.formula_int = 60-result_size__result_type-12-12-2-6-5-3;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_OUT_LIF_PROFILE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPC_ESEM_DEFAULT_RESULT_TABLEm, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    {
                        uint32 result_size__result_type = 0;
                        result_size__result_type += dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE_get(unit);
                        access_params->data_offset.formula_int = 60-result_size__result_type-12-12-2-6-5-3-6;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_EGRESS_LAST_LAYER;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPC_ESEM_DEFAULT_RESULT_TABLEm, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    {
                        uint32 result_size__result_type = 0;
                        result_size__result_type += dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_AC_STAT___RESULT_TYPE_get(unit);
                        access_params->data_offset.formula_int = 60-result_size__result_type-12-12-2-6-5-3-6-1;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
        map_idx = DBAL_RESULT_TYPE_ESEM_DEFAULT_RESULT_TABLE_ETPS_DUAL_HOMING;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, "ETPS_DUAL_HOMING", sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RESULT_TYPE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPC_ESEM_DEFAULT_RESULT_TABLEm, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    {
                        uint32 result_size__result_type = 0;
                        result_size__result_type += dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE_get(unit);
                        access_params->data_offset.formula_int = 60-result_size__result_type;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_DUAL_HOMING;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPC_ESEM_DEFAULT_RESULT_TABLEm, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    {
                        uint32 result_size__result_type = 0;
                        result_size__result_type += dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_DUAL_HOMING___RESULT_TYPE_get(unit);
                        access_params->data_offset.formula_int = 60-result_size__result_type-32;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
        map_idx = DBAL_RESULT_TYPE_ESEM_DEFAULT_RESULT_TABLE_ETPS_NULL;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, "ETPS_NULL", sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RESULT_TYPE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPC_ESEM_DEFAULT_RESULT_TABLEm, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    {
                        uint32 result_size__result_type = 0;
                        result_size__result_type += dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE_get(unit);
                        access_params->data_offset.formula_int = 60-result_size__result_type;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_EGRESS_LAST_LAYER;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPC_ESEM_DEFAULT_RESULT_TABLEm, DBAL_HL_ACCESS_HW_FIELD_INVALID));
                    {
                        uint32 result_size__result_type = 0;
                        result_size__result_type += dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___ESEM_DEFAULT_RESULT_TABLE___ETPS_NULL___RESULT_TYPE_get(unit);
                        access_params->data_offset.formula_int = 60-result_size__result_type-1;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_ESEM_DEFAULT_RESULT_TABLE, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
_dbal_init_tables_hard_logic_auto_generated_standard_1_mdb_hard_logic_jr1_mpls_push_command_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    dbal_logical_table_t * table_entry = table_info + DBAL_TABLE_JR1_MPLS_PUSH_COMMAND;
    int is_valid = TRUE;
    SHR_FUNC_INIT_VARS(unit);
    dbal_init_table_db_struct_clear(cur_table_param);
    SHR_IF_ERR_EXIT(dbal_db_init_general_info_set(unit, table_entry, DBAL_TABLE_JR1_MPLS_PUSH_COMMAND, is_valid, "JR1_MPLS_PUSH_COMMAND", DBAL_ACCESS_METHOD_HARD_LOGIC));
    table_entry->maturity_level = DBAL_MATURITY_HIGH;
    table_entry->table_type = DBAL_TABLE_TYPE_DIRECT;
    table_entry->nof_labels = 1;
    DBAL_DB_INIT_TABLE_LABELS_ALLOC(table_entry)
    table_entry->table_labels[0] = DBAL_LABEL_MPLS;
    {
        int field_index = 0;
        dbal_table_field_info_t * dbal_db_field;
        table_db_field_params_struct_t db_field;
        DBAL_DB_INIT_TABLE_INTERFACE_KEY_FIELDS_ALLOC(table_entry, 1);
        {
            dbal_db_field = &table_entry->keys_info[field_index];
            SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_PUSH_PROFILE, DBAL_FIELD_TYPE_DEF_UINT, dbal_db_field));
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
        SHR_BITSET(table_entry->indications_bm, DBAL_TABLE_IND_HAS_RESULT_TYPE);
        SHR_IF_ERR_EXIT(dbal_db_init_table_db_interface_results_alloc(unit, table_entry));
        result_type_counter = DBAL_RESULT_TYPE_JR1_MPLS_PUSH_COMMAND_ETPS_MPLS_1_STAT;
        field_index = 0;
        if (dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE___valid_get(unit) != 0)
        {
            DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 14);
            DBAL_DB_INIT_TABLE_INTERFACE_RESULT_FIELDS_ALLOC(table_entry, table_entry->multi_res_info[result_type_counter]);
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_RESULT_TYPE, DBAL_FIELD_TYPE_DEF_RESULT_TYPE, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = dnx_data_dnx2_mdb_app_db.fields.numeric_mdb_field___JR1_MPLS_PUSH_COMMAND___ETPS_MPLS_1_STAT___RESULT_TYPE_get(unit);
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_OUT_LIF_PROFILE, DBAL_FIELD_TYPE_DEF_OUT_LIF_PROFILE, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 6;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_OAM_LIF_SET, DBAL_FIELD_TYPE_DEF_OAM_LIF_SET, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 1;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_LIF_AHP_MPLS, DBAL_FIELD_TYPE_DEF_LIF_AHP_MPLS, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 3;
                dbal_db_init_table_set_field_arr_prefix(unit, &db_field, dnx_data_dnx2_arr.prefix.ETPP_ETPS_FORMATS___prefix_LIF_AHP_MPLS_Prefix_get(unit), 8);
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TTL_PIPE_PROFILE, DBAL_FIELD_TYPE_DEF_TTL_PIPE_PROFILE, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 4;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_NWK_QOS_IDX, DBAL_FIELD_TYPE_DEF_NWK_QOS_IDX, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 6;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_REMARK_PROFILE, DBAL_FIELD_TYPE_DEF_REMARK_PROFILE, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 5;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_ENCAP_QOS_MODEL, DBAL_FIELD_TYPE_DEF_ENCAP_QOS_MODEL, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 3;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_FORWARD_QOS_MODEL, DBAL_FIELD_TYPE_DEF_FORWARD_QOS_MODEL, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 1;
                dbal_db_init_table_set_field_arr_prefix(unit, &db_field, dnx_data_dnx2_arr.prefix.ETPP_ETPS_FORMATS___prefix_FORWARD_QOS_MODEL_NWK_QOS_get(unit), 8);
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TTL_DECREMENT_DISABLE, DBAL_FIELD_TYPE_DEF_TTL_DECREMENT_DISABLE, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 1;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_TTL_MODE, DBAL_FIELD_TYPE_DEF_TTL_MODE, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 1;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_MTU_PROFILE, DBAL_FIELD_TYPE_DEF_MTU_PROFILE, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 3;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_ACTION_PROFILE, DBAL_FIELD_TYPE_DEF_ACTION_PROFILE, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 2;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
            {
                dbal_db_field = &table_entry->multi_res_info[result_type_counter].results_info[field_index];
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_mandatory_values(unit, DBAL_FIELD_ESEM_COMMAND, DBAL_FIELD_TYPE_DEF_ESEM_COMMAND, dbal_db_field));
                dbal_db_init_table_field_params_init(&db_field);
                db_field.size = 3;
                SHR_IF_ERR_EXIT(dbal_db_init_table_field_set_optional_or_default_values(unit, table_entry, dbal_db_field, &db_field, FALSE));
                field_index += dbal_db_field->nof_instances;
            }
        }
        else
        {
            table_entry->multi_res_info[result_type_counter].is_disabled = TRUE;
            DBAL_DB_INIT_TABLE_NOF_RESULT_FIELDS_SET(table_entry, (table_entry->multi_res_info[result_type_counter]), 0);
        }
        sal_strncpy(table_entry->multi_res_info[result_type_counter].result_type_name, "ETPS_MPLS_1_STAT", sizeof(table_entry->multi_res_info[result_type_counter].result_type_name));
    }
    dbal_db_init_table_db_struct_access_clear(cur_table_param, table_entry);
    {
        uint8 is_standard_1 = TRUE;
        uint8 is_compatible_with_all_images = FALSE;
        DBAL_DB_INIT_TABLE_IMAGE_SPECIFIC_TABLE_INDICATION_SET(table_entry, is_standard_1, is_compatible_with_all_images);
        SHR_IF_ERR_EXIT(dbal_db_init_table_set_table_incompatible_image_sw_state_indication(unit, DBAL_TABLE_JR1_MPLS_PUSH_COMMAND, is_standard_1, is_compatible_with_all_images));
    }
    table_entry->core_mode = DBAL_CORE_MODE_SBC;
    SHR_IF_ERR_EXIT(dbal_db_init_table_add_result_type_physical_values_by_reference_field(unit, &(table_entry->multi_res_info[DBAL_RESULT_TYPE_JR1_MPLS_PUSH_COMMAND_ETPS_MPLS_1_STAT]), DBAL_FIELD_TYPE_DEF_ETPP_ETPS_FORMATS));
    {
        int map_idx = 0;
        int access_counter;
        map_idx = DBAL_RESULT_TYPE_JR1_MPLS_PUSH_COMMAND_ETPS_MPLS_1_STAT;
        access_counter = 0;
        sal_strncpy(cur_table_param->hl_access[map_idx].mapping_result_name, "ETPS_MPLS_1_STAT", sizeof(cur_table_param->hl_access[map_idx].mapping_result_name));
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_RESULT_TYPE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPA_EEI_MPLS_PUSH_2_EES_MAPm, EEI_TYPEf));
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
                access_params->access_field_id = DBAL_FIELD_OUT_LIF_PROFILE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPA_EEI_MPLS_PUSH_2_EES_MAPm, EEI_DATAf));
                    {
                        access_params->data_offset.formula_int = 88;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_OAM_LIF_SET;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPA_EEI_MPLS_PUSH_2_EES_MAPm, EEI_DATAf));
                    {
                        access_params->data_offset.formula_int = 87;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_LIF_AHP_MPLS;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPA_EEI_MPLS_PUSH_2_EES_MAPm, EEI_DATAf));
                    {
                        access_params->data_offset.formula_int = 84;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TTL_PIPE_PROFILE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPA_EEI_MPLS_PUSH_2_EES_MAPm, EEI_DATAf));
                    {
                        access_params->data_offset.formula_int = 80;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_NWK_QOS_IDX;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPA_EEI_MPLS_PUSH_2_EES_MAPm, EEI_DATAf));
                    {
                        access_params->data_offset.formula_int = 74;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_REMARK_PROFILE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPA_EEI_MPLS_PUSH_2_EES_MAPm, EEI_DATAf));
                    {
                        access_params->data_offset.formula_int = 69;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_ENCAP_QOS_MODEL;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPA_EEI_MPLS_PUSH_2_EES_MAPm, EEI_DATAf));
                    {
                        access_params->data_offset.formula_int = 66;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_FORWARD_QOS_MODEL;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPA_EEI_MPLS_PUSH_2_EES_MAPm, EEI_DATAf));
                    {
                        access_params->data_offset.formula_int = 65;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_TTL_DECREMENT_DISABLE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPA_EEI_MPLS_PUSH_2_EES_MAPm, EEI_DATAf));
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
                access_params->access_field_id = DBAL_FIELD_TTL_MODE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPA_EEI_MPLS_PUSH_2_EES_MAPm, EEI_DATAf));
                    {
                        access_params->data_offset.formula_int = 63;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_MTU_PROFILE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPA_EEI_MPLS_PUSH_2_EES_MAPm, EEI_DATAf));
                    {
                        access_params->data_offset.formula_int = 60;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_ACTION_PROFILE;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPA_EEI_MPLS_PUSH_2_EES_MAPm, EEI_DATAf));
                    {
                        access_params->data_offset.formula_int = 58;
                    }
                }
            }
        }
        {
            table_db_access_params_struct_t * access_params;
            {
                access_params = &cur_table_param->hl_access[map_idx].access[access_counter];
                dbal_db_init_table_db_struct_hl_access_params_clear(access_params);
                access_counter++;
                access_params->access_field_id = DBAL_FIELD_ESEM_COMMAND;
                access_params->access_type = DBAL_HL_ACCESS_MEMORY;
                {
                    SHR_IF_ERR_EXIT(dbal_db_init_table_set_access_register_memory(unit, access_params, ETPPA_EEI_MPLS_PUSH_2_EES_MAPm, EEI_DATAf));
                    {
                        access_params->data_offset.formula_int = 55;
                    }
                }
            }
        }
        cur_table_param->hl_access[map_idx].nof_access = access_counter;
    }
    SHR_IF_ERR_EXIT(dbal_db_init_table_add(unit, cur_table_param, DBAL_TABLE_JR1_MPLS_PUSH_COMMAND, table_info));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dbal_init_tables_hard_logic_auto_generated_standard_1_mdb_hard_logic_init(
int unit,
table_db_struct_t * cur_table_param,
dbal_logical_table_t * table_info)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_auto_generated_standard_1_mdb_hard_logic_esem_default_result_table_init(unit, cur_table_param, table_info));
    SHR_IF_ERR_EXIT(_dbal_init_tables_hard_logic_auto_generated_standard_1_mdb_hard_logic_jr1_mpls_push_command_init(unit, cur_table_param, table_info));
exit:
    SHR_FUNC_EXIT;
}

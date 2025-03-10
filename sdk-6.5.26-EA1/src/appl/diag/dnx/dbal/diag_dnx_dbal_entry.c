/** \file diag_dnx_dbal_entry.c
 *
 * Main diagnostics for dbal applications All CLI commands, that
 * are related to DBAL entry, are gathered in this file.
 *
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_SOCDNX_DIAGDBALDNX

/*************
 * INCLUDES  *
 *************/
#include <sal/appl/sal.h>
#include <shared/bslnames.h>
#include <appl/diag/diag.h>
#include <soc/dnx/dbal/dbal.h>
#include <soc/dnx/dbal/dbal_structures.h>
#include "diag_dnx_dbal_internal.h"
#include <appl/diag/shell.h>
#include <appl/diag/cmdlist.h>
#include <appl/diag/bslenable.h>
#include <appl/diag/sand/diag_sand_framework.h>
#include <shared/utilex/utilex_framework.h>
#include <soc/sand/sand_aux_access.h>
#include <bcm_int/dnx/field/field_entry.h>
#include <soc/dnx/dbal/dbal_string_mgmt.h>
#include <soc/sand/sand_signals.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_l2.h>
#include "diag_dnx_dbal.h"

/*************
 * TYPEDEFS  *
 *************/

extern shr_error_e dnx_algo_res_dbal_out_lif_is_allocated(
    int unit,
    int core_id,
    int out_lif,
    dbal_tables_e table_id,
    int *result_type,
    int is_alloc_table_any,
    uint8 *is_allocated);
extern shr_error_e dnx_algo_res_dbal_out_rif_is_allocated(
    int unit,
    int core_id,
    int out_lif,
    dbal_tables_e table_id,
    int *result_type,
    int is_alloc_table_any,
    uint8 *is_allocated);
extern shr_error_e dnx_algo_res_dbal_lif_is_allocated(
    int unit,
    int core_id,
    int in_lif,
    int sub_resource_index,
    dbal_tables_e table_id,
    int *result_type,
    int is_aloc_table_any,
    uint8 *is_allocated);

/*************
 * FUNCTIONS *
 *************/

static shr_error_e
diag_dbal_entry_print_accessId_missing(
    int unit,
    dbal_tables_e table_id)
{
    char buffer[DBAL_MAX_PRINTABLE_BUFFER_SIZE] = { 0 };

    SHR_FUNC_INIT_VARS(unit);

    sal_sprintf(buffer, "Example: dbal ENTry Get TaBLe=%s AccessId=<value>",
                dbal_logical_table_to_string(unit, table_id));
    DIAG_DBAL_HEADER_DUMP(buffer, "\0");

    SHR_FUNC_EXIT;
}

/**********************************************************************************************************************
 *  DBAL DIAGNOSTIC PACK:
 *  ENTRY SUB MENU function & infrastructure Definitions - START
 *  STURCTURE:
 *  1. cmd function definition
 *  2. cmd option and man table
 *  3. ENTRY SUB MENU cmd table
 **********************************************************************************************************************/
/**
* \brief
* Print usage example specific to requested table
* for multiple result types table the result the optional result types
* list is printed, in case the result type is present
* the full usage options for this specific result type is printed
*****************************************************/
shr_error_e
diag_dbal_entry_print_help_line(
    int unit,
    dbal_tables_e table_id,
    uint32 res_type,
    char *cmd,
    uint8 key_field_only)
{
    CONST dbal_logical_table_t *table;
    dbal_field_types_basic_info_t *field_info;
    uint8 field_index;
    uint8 enum_val_index;
    uint8 result_index = 0;
    uint8 enum_field_exist;

    PRT_INIT_VARS;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dbal_tables_table_get(unit, table_id, &table));

    DIAG_DBAL_HEADER_DUMP("USAGE EXAMPLE: ", "\0");
    if (table->nof_result_types > 1)
    {
        if ((res_type == 0xFFFFFFFF) && (!key_field_only))
        {
            LOG_CLI((BSL_META("dbal ENTry %s TaBLe=%s Result_Type=<result_type_name> \n"), cmd,
                     dbal_logical_table_to_string(unit, table_id)));
            LOG_CLI((BSL_META("Available Result Types for Table: \n")));
            for (result_index = 0; result_index < table->nof_result_types; result_index++)
            {
                LOG_CLI((BSL_META("    %s\n"), table->multi_res_info[result_index].result_type_name));
            }
            SHR_EXIT();
        }
        result_index = res_type;
    }

    enum_field_exist = FALSE;

    if (!(SHR_IS_BITSET(table->indications_bm, DBAL_TABLE_IND_HAS_RESULT_TYPE)) || (key_field_only == TRUE))
    {
        LOG_CLI((BSL_META("dbal ENTry %s TaBLe=%s "), cmd, dbal_logical_table_to_string(unit, table_id)));
    }
    else
    {
        LOG_CLI((BSL_META("For result type: %s: \n"), table->multi_res_info[result_index].result_type_name));
        LOG_CLI((BSL_META("    dbal ENTry %s TaBLe=%s "), cmd, dbal_logical_table_to_string(unit, table_id)));
    }

    if (DBAL_TABLE_IS_TCAM(table))
    {
        if (table->access_method == DBAL_ACCESS_METHOD_MDB || table->access_method == DBAL_ACCESS_METHOD_KBP)
        {
            LOG_CLI((BSL_META("Priority=<priority_uint32> ")));
        }
        else
        {
            LOG_CLI((BSL_META("AccessId=<access_id_uint32> ")));
            if (key_field_only == TRUE)
            {
                LOG_CLI((BSL_META("\n")));
                SHR_EXIT();
            }
        }
    }

    /** Print Key fields */
    for (field_index = 0; field_index < table->nof_key_fields; field_index++)
    {
        if (!SHR_BITGET(table->keys_info[field_index].field_indication_bm, DBAL_FIELD_IND_IS_CONST_VALID))
        {

            if ((key_field_only == FALSE) && (DBAL_TABLE_IS_TCAM(table) || (table->table_type == DBAL_TABLE_TYPE_LPM)))
            {
                LOG_CLI((BSL_META("%s=<val,mask> "),
                         dbal_field_to_string(unit, table->keys_info[field_index].field_id)));
            }
            else
            {
                LOG_CLI((BSL_META("%s=<val> "), dbal_field_to_string(unit, table->keys_info[field_index].field_id)));
            }
        }
    }
    if (key_field_only == FALSE)
    {
        /*
         * Print Result fields
         */
        for (field_index = 0; field_index < table->multi_res_info[result_index].nof_result_fields; field_index++)
        {
            dbal_fields_e field_id = table->multi_res_info[result_index].results_info[field_index].field_id;

            if (field_id == DBAL_FIELD_RESULT_TYPE)
            {
                LOG_CLI((BSL_META("%s=%s "),
                         dbal_field_to_string(unit, field_id), table->multi_res_info[result_index].result_type_name));
            }
            else if (!SHR_BITGET
                     (table->multi_res_info[result_index].results_info[field_index].field_indication_bm,
                      DBAL_FIELD_IND_IS_CONST_VALID))
            {
                char field_str[DBAL_MAX_STRING_LENGTH];
                uint8 inst_idx = table->multi_res_info[result_index].results_info[field_index].inst_idx;

                SHR_IF_ERR_EXIT(dbal_fields_field_types_info_get(unit, field_id, &field_info));
                if (field_info->nof_enum_values > 0)
                {
                    LOG_CLI((BSL_META("%s=<ENUM_VAL> "), dbal_field_with_inst_to_string(unit,
                                                                                        field_id,
                                                                                        inst_idx, field_str)));
                }
                else
                {
                    LOG_CLI((BSL_META("%s=<val> "), dbal_field_with_inst_to_string(unit,
                                                                                   field_id, inst_idx, field_str)));
                }
            }
        }
    }

    LOG_CLI((BSL_META("\n\n")));

    /*
     * print enum fields values if exist
     */
    PRT_TITLE_SET("ENUM Values for each enum field");
    PRT_COLUMN_ADD("Field Name");
    PRT_COLUMN_ADD("ENUM Value");

    for (field_index = 0; field_index < table->nof_key_fields; field_index++)
    {
        dbal_fields_e field_id = table->keys_info[field_index].field_id;
        SHR_IF_ERR_EXIT(dbal_fields_field_types_info_get(unit, field_id, &field_info));
        if (field_info->nof_enum_values > 0)
        {
            enum_field_exist = TRUE;
            PRT_ROW_ADD(PRT_ROW_SEP_NONE);
            PRT_CELL_SET("%s", dbal_field_to_string(unit, field_id));
            for (enum_val_index = 0; enum_val_index < field_info->nof_enum_values; enum_val_index++)
            {
                char *enum_name;

                if (enum_val_index == 32) /** not printing help line for enums values bigger than 32*/
                {
                    PRT_ROW_ADD(PRT_ROW_SEP_NONE);
                    PRT_CELL_SKIP(PRT_COLUMN_NUM - 1);
                    PRT_CELL_SET("Printing first 32 values only");
                    break;
                }
                PRT_ROW_ADD(PRT_ROW_SEP_NONE);
                PRT_CELL_SKIP(PRT_COLUMN_NUM - 1);
                enum_name = field_info->enum_val_info[enum_val_index].name;
                PRT_CELL_SET("%s", enum_name);

            }
        }
    }

    if (key_field_only == FALSE)
    {
        for (field_index = 0; field_index < table->multi_res_info[result_index].nof_result_fields; field_index++)
        {
            dbal_fields_e field_id = table->multi_res_info[result_index].results_info[field_index].field_id;

            SHR_IF_ERR_EXIT(dbal_fields_field_types_info_get(unit, field_id, &field_info));
            if (field_info->nof_enum_values > 0)
            {
                enum_field_exist = TRUE;
                PRT_ROW_ADD(PRT_ROW_SEP_NONE);
                PRT_CELL_SET("%s", dbal_field_to_string(unit, field_id));
                for (enum_val_index = 0; enum_val_index < field_info->nof_enum_values; enum_val_index++)
                {
                    char *enum_name;

                    if (enum_val_index == 32) /** not printing help line for enums values bigger than 32*/
                    {
                        PRT_ROW_ADD(PRT_ROW_SEP_NONE);
                        PRT_CELL_SKIP(PRT_COLUMN_NUM - 1);
                        PRT_CELL_SET("Printing first 32 values only");
                        break;
                    }
                    PRT_ROW_ADD(PRT_ROW_SEP_NONE);
                    PRT_CELL_SKIP(PRT_COLUMN_NUM - 1);
                    enum_name = field_info->enum_val_info[enum_val_index].name;
                    PRT_CELL_SET("%s", enum_name);
                }
            }
        }
    }
    if (enum_field_exist)
    {
        PRT_COMMIT;
    }
    else
    {
        PRT_FREE;
    }

    LOG_CLI((BSL_META("\n")));

exit:
    PRT_FREE;
    SHR_FUNC_EXIT;
}

static shr_error_e
diag_dbal_entry_cmd_field_get(
    int unit,
    char *keyword,
    sal_field_type_e * type_p,
    uint32 *id_p,
    void **ext_ptr_p)
{
    dbal_fields_e field_id;
    dbal_field_print_type_e field_type;
    uint8 inst_idx = 0;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dbal_field_string_to_inst_idx(unit, keyword, &field_id, &inst_idx));
    SHR_IF_ERR_EXIT(dbal_fields_print_type_get(unit, field_id, &field_type));

    dbal_builds_enum_sand_table(unit, field_id);

    if (type_p != NULL)
    {
        /** if result type, receive the value as string and transform it to ID */
        if (field_id == DBAL_FIELD_RESULT_TYPE)
        {
            *type_p = SAL_FIELD_TYPE_STR;
        }
        else
        {
            *type_p = dbal_field_type_to_sal_field_type[field_type];
        }
    }
    if (id_p != NULL)
    {
        DBAL_ENCODE_FIELD_ID_WITH_INSTANCE(*id_p, field_id, inst_idx);
    }
    if (ext_ptr_p != NULL)
    {   /* Fill here you pointer to sh_sand_enum_t */
        *ext_ptr_p = &dbal_test_enum_table[0];
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 * utility function for diag_dbal_entry_commit &
 * diag_dbal_entry_update.
 * commit a DBAL table entry according to the commit_flag param.
 *
 *    \param [in] unit - Relevant unit.
 *    \param [in] sand_control - received sand control.
 *    \param [in] commit_flags - DBAL_COMMIT - perform an
 *                entry commit. DBAL_COMMIT_UPDATE_ENTRY - perform an entry update.
 *    \param[in] cmd - string describing the performed action
 *
 * \return
 *    \retval Negative in case of an error
 *    \retval Zero in case of NO ERROR
 */
static shr_error_e
diag_dbal_entry_commit_flag(
    int unit,
    sh_sand_control_t * sand_control,
    dbal_entry_action_flags_e commit_flags,
    char *cmd)
{
    CONST dbal_logical_table_t *table;
    uint32 entry_handle_id;
    int key_field_index = 0;
    int value_field_index = 0;
    uint32 access_id;
    uint32 priority;
    char *table_name;
    dbal_tables_e table_id;
    sh_sand_arg_t *sand_arg;
    dbal_fields_e field_id;
    uint8 is_key, action_validated;
    uint8 is_key_const = FALSE;
    uint32 res_type = 0xFFFFFFFF;
    uint8 num_const = 0;
    int is_hw_only, is_no_payload;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    action_validated = 0;
    /*
     * Get parameters
     */
    SH_SAND_GET_STR("table", table_name);
    SH_SAND_GET_BOOL("HwOnly", is_hw_only);
    SH_SAND_GET_BOOL("NoPayload", is_no_payload);

    if (is_hw_only)
    {
        commit_flags |= DBAL_COMMIT_HW_ONLY;
    }

    if (ISEMPTY(table_name))
    {
        if (commit_flags == DBAL_COMMIT)
        {
            DIAG_DBAL_HEADER_DUMP("Example: dbal Entry CoMmit TaBLe=<table_name>", "\0");
        }
        else
        {
            DIAG_DBAL_HEADER_DUMP("Example: dbal Entry Update TaBLe=<table_name>", "\0");
        }
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(diag_dbal_table_from_string(unit, table_name, &table_id, sand_control, NULL, TRUE));
    if (table_id == dnx_data_dbal.table.nof_dynamic_and_static_tables_get(unit))
    {
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(dbal_tables_table_get(unit, table_id, &table));
    DIAG_DBAL_TABLE_STATUS_VALIDATE(table_id);

    /** Get table handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table_id, &entry_handle_id));

    if (DBAL_TABLE_IS_TCAM(table))
    {
        if (DBAL_TABLE_IS_TCAM_BY_ID(table))
        {
            SH_SAND_GET_UINT32("AccessId", access_id);
            if (access_id == 0xffffffff)
            {
                /** Access id not received or not legal */
                SHR_IF_ERR_EXIT(diag_dbal_entry_print_accessId_missing(unit, table_id));
                SHR_EXIT();
            }
            SHR_IF_ERR_EXIT(dbal_entry_handle_access_id_set(unit, entry_handle_id, access_id));

            if ((table->access_method == DBAL_ACCESS_METHOD_MDB) || (table->access_method == DBAL_ACCESS_METHOD_KBP))
            {
                SH_SAND_GET_UINT32("Priority", priority);
                SHR_IF_ERR_EXIT(dbal_entry_attribute_set(unit, entry_handle_id, DBAL_ENTRY_ATTR_PRIORITY, priority));
            }
            else
            {
                commit_flags |= DBAL_COMMIT_OVERRIDE_DEFAULT;
            }
        }
    }

    if (is_no_payload)
    {
        SHR_IF_ERR_EXIT(dbal_entry_attribute_set(unit, entry_handle_id, DBAL_ENTRY_ATTR_NO_PAYLOAD, 1));
    }

    /** get the number of const fields in the key */
    SHR_IF_ERR_EXIT(dbal_tables_field_is_key_const_val_num_get(unit, table_id, &num_const));

    SH_SAND_GET_ITERATOR(sand_arg)
    {
        uint8 inst_idx = 0;
        int mask_present = SH_SAND_HAS_MASK(sand_arg);
        field_id = SH_SAND_GET_ID(sand_arg);

        DBAL_DECODE_FIELD_ID_WITH_INSTANCE(field_id, inst_idx);

        /** Get Value fields Params */
        SHR_IF_ERR_EXIT(dbal_tables_field_is_key_get(unit, table_id, field_id, &is_key));
        if (is_key == TRUE)
        {
            SHR_IF_ERR_EXIT(dbal_tables_field_is_key_const_get(unit, table_id, field_id, &is_key_const));
            if (!is_key_const)
            {
                if (mask_present && (DBAL_TABLE_IS_TCAM(table) || (table->table_type == DBAL_TABLE_TYPE_LPM)))
                {
                    /** Get Key fields Params with mask */
                    DBAL_ENTRY_COMMIT_KEY_FIELD_WITH_MASK(unit, entry_handle_id, field_id, sand_arg);
                }
                else
                {
                    /** Get Key fields Params */
                    DBAL_ENTRY_COMMIT_KEY_FIELD(unit, entry_handle_id, field_id, sand_arg);
                }
                key_field_index++;
            }
        }
        else
        {
            DBAL_ENTRY_COMMIT_VALUE_FIELD(unit, entry_handle_id, field_id, inst_idx, res_type, 1, sand_arg);
            value_field_index++;
        }
    }

    if (DBAL_TABLE_IS_TCAM_BY_KEY(table) && (commit_flags & DBAL_COMMIT_UPDATE))
    {
        if (table->access_method == DBAL_ACCESS_METHOD_MDB)
        {
            SHR_IF_ERR_EXIT(dbal_entry_access_id_by_key_get(unit, entry_handle_id, &access_id, DBAL_COMMIT));
            SHR_IF_ERR_EXIT(dbal_entry_handle_access_id_set(unit, entry_handle_id, access_id));
        }
    }

    /** Validate that all the parameters where added according to requirements   */
    if (DBAL_TABLE_IS_TCAM(table))
    {
        if (key_field_index > 0 || value_field_index > 0)
        {
            action_validated = 1;
        }
    }
    else
    {
        if (((key_field_index + num_const) == table->nof_key_fields) && ((value_field_index > 0) || is_no_payload))
        {
            action_validated = 1;
        }
    }

    if (!action_validated)
    {
        if ((key_field_index + num_const) != table->nof_key_fields)
        {
            LOG_CLI((BSL_META("All Key fields are mandatory find available fields below:\n")));
        }
        else
        {
            LOG_CLI((BSL_META("at least one result field should be set, find available fields below:\n")));
        }

        SHR_IF_ERR_EXIT(diag_dbal_entry_print_help_line(unit, table_id, res_type, cmd, FALSE));
        SHR_EXIT();
    }
    else
    {
        int rv;
        rv = dbal_entry_commit(unit, entry_handle_id, commit_flags | DBAL_COMMIT_IGNORE_ALLOC_ERROR);
        if (rv == _SHR_E_ACCESS)
        {
            dbal_entry_handle_t *entry_handle;
            SHR_IF_ERR_EXIT(dbal_entry_handle_get_internal(unit, entry_handle_id, &entry_handle));
            SHR_ERR_EXIT(rv, "Access to unmapped combination of key fields. "
                         "The first field failing the mapping condition is: %s. Check that keys combination fits the mapping definition.\n",
                         dbal_field_to_string(unit, entry_handle->error_info.field_and_instance));
        }
        SHR_IF_ERR_EXIT(rv);

    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - commit a DBAL table entry
 */
static shr_error_e
diag_dbal_entry_commit(
    int unit,
    args_t * args,
    sh_sand_control_t * sand_control)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(diag_dbal_entry_commit_flag(unit, sand_control, DBAL_COMMIT, "CoMmit"));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Update a DBAL table entry
 */
static shr_error_e
diag_dbal_entry_update(
    int unit,
    args_t * args,
    sh_sand_control_t * sand_control)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(diag_dbal_entry_commit_flag(unit, sand_control, DBAL_COMMIT_UPDATE, "Update"));

exit:
    SHR_FUNC_EXIT;
}

/*
 * This function set the result type of an entry according to the allocated lif
 * for lif tables we need to set the result type before get and clear actions
 * in order to know the size of the entry
 */
static shr_error_e
diag_dbal_entry_lif_res_type_set(
    int unit,
    uint32 entry_handle_id,
    int lif_val)
{
    uint8 is_allocated;
    int result_type = -1;
    dbal_entry_handle_t *entry_handle;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dbal_entry_handle_get_internal(unit, entry_handle_id, &entry_handle));

    if (dbal_table_is_out_lif(entry_handle->table) && (entry_handle->table->allocator_field_id == DBAL_FIELD_OUT_LIF))
    {
        SHR_IF_ERR_EXIT(dnx_algo_res_dbal_out_lif_is_allocated
                        (unit, entry_handle->core_id, lif_val, entry_handle->table_id, &result_type, 0, &is_allocated));
    }
    else if (dbal_table_is_out_lif(entry_handle->table)
             && (entry_handle->table->allocator_field_id == DBAL_FIELD_OUT_RIF))
    {
        SHR_IF_ERR_EXIT(dnx_algo_res_dbal_out_rif_is_allocated
                        (unit, entry_handle->core_id, lif_val, entry_handle->table_id, &result_type, 0, &is_allocated));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_algo_res_dbal_lif_is_allocated
                        (unit, entry_handle->core_id, lif_val, 0, entry_handle->table_id, &result_type, 0,
                         &is_allocated));
    }

    if (!is_allocated)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "LIF %d not allocated\n", lif_val);
    }

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RESULT_TYPE, INST_SINGLE, result_type);
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
diag_dbal_result_type_set(
    int unit,
    uint32 entry_handle_id,
    dbal_tables_e table_id,
    sh_sand_arg_t * sand_arg,
    char *cmd)
{
    uint32 res_type;
    int rv;

    SHR_FUNC_INIT_VARS(unit);

    rv = dbal_result_type_string_to_id(unit, table_id, SH_SAND_ARG_STR(sand_arg), &res_type);
    if (rv)
    {
        LOG_CLI((BSL_META
                 ("result type name not valid %s, please use the string represent the result type value"),
                 SH_SAND_ARG_STR(sand_arg)));
        SHR_IF_ERR_EXIT(diag_dbal_entry_print_help_line(unit, table_id, res_type, cmd, FALSE));
        SHR_SET_CURRENT_ERR(_SHR_E_PARAM);
        SHR_EXIT();
    }
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RESULT_TYPE, INST_SINGLE, res_type);

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
diag_dbal_entry_print_entry(
    int unit,
    uint32 entry_handle_id)
{
    char buffer[DBAL_MAX_PRINTABLE_BUFFER_SIZE] = { 0 };
    char field_str[DBAL_MAX_STRING_LENGTH] = { 0 };
    dbal_field_data_t *key_fields_array = NULL;
    dbal_field_data_t *val_fields_array = NULL;
    CONST dbal_logical_table_t *table;
    dbal_entry_handle_t *entry_handle;
    int first_res_index = 0;
    int key_field_index = 0;
    int field_index = 0;
    dbal_fields_e field_id;
    dbal_tables_e table_id;
    int result_type_idx = 0;
    uint32 access_id = 0;
    uint32 hitbit_en = FALSE;
    uint8 inst_idx = 0;
    uint32 is_no_payload = 0;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dbal_entry_handle_get_internal(unit, entry_handle_id, &entry_handle));

    table = entry_handle->table;
    table_id = entry_handle->table_id;

    /** check if the requested table entry support hitbit */
    SHR_IF_ERR_EXIT(dbal_tables_indication_get(unit, table_id, DBAL_TABLE_IND_IS_HITBIT_EN, &hitbit_en));

    if (entry_handle->access_id_set)
    {
        access_id = entry_handle->phy_entry.entry_hw_id;
    }

    key_fields_array = sal_alloc(sizeof(dbal_field_data_t) * DBAL_TABLE_MAX_NUM_OF_KEY_FIELDS, "Key fields");
    if (NULL == key_fields_array)
    {
        SHR_ERR_EXIT(_SHR_E_MEMORY, "alloc failed Key fields");
    }

    val_fields_array =
        sal_alloc(sizeof(dbal_field_data_t) * DBAL_TABLE_MAX_NUM_OF_RESULT_FIELDS_PER_RES_TYPE, "Result fields");
    if (NULL == val_fields_array)
    {
        SHR_ERR_EXIT(_SHR_E_MEMORY, "alloc failed Result fields");
    }

    LOG_CLI((BSL_META("\n")));
    if (DBAL_TABLE_IS_TCAM(table) && entry_handle->access_id_set)
    {
        LOG_CLI((BSL_META("AccessId=%d \n"), access_id));
    }

    if (hitbit_en)
    {
        uint32 attr_val;

        SHR_IF_ERR_EXIT(dbal_entry_attribute_get(unit, entry_handle_id,
                                                 (DBAL_ENTRY_ATTR_HIT_PRIMARY | DBAL_ENTRY_ATTR_HIT_SECONDARY |
                                                  DBAL_ENTRY_ATTR_HIT_GET), &attr_val));
        LOG_CLI((BSL_META("HitBit=%s \n"), dbal_mdb_hitbit_to_string(unit, table->physical_db_id[0], attr_val)));
    }

    if ((table->access_method == DBAL_ACCESS_METHOD_MDB) &&
        (!dnx_data_l2.feature.feature_get(unit, dnx_data_l2_feature_age_state_not_updated)) &&
        (dbal_logical_table_is_mact(unit, table_id)))
    {
        uint32 attr_val;

        SHR_IF_ERR_EXIT(dbal_entry_attribute_get(unit, entry_handle_id, DBAL_ENTRY_ATTR_AGE, &attr_val));
        LOG_CLI((BSL_META("Age=%d \n"), attr_val));
    }

    /*
     * Print Key fields
     */
    LOG_CLI((BSL_META("\nKey:\n")));
    for (key_field_index = 0; key_field_index < table->nof_key_fields; key_field_index++)
    {
        if (DBAL_TABLE_IS_TCAM(table) && (table->access_method != DBAL_ACCESS_METHOD_MDB))
        {
            /*
             * Read all keys from handle with mask
             */
            key_fields_array[key_field_index].field_id = table->keys_info[key_field_index].field_id;
            SHR_IF_ERR_EXIT(dbal_entry_handle_key_field_arr32_masked_get
                            (unit, entry_handle_id, key_fields_array[key_field_index].field_id,
                             key_fields_array[key_field_index].field_val,
                             key_fields_array[key_field_index].field_mask));
            SHR_IF_ERR_EXIT(dbal_field_in_table_printable_string_get(unit,
                                                                     key_fields_array[key_field_index].field_id,
                                                                     0,
                                                                     table_id,
                                                                     key_fields_array[key_field_index].field_val,
                                                                     key_fields_array[key_field_index].field_mask,
                                                                     result_type_idx, TRUE, FALSE, buffer));
        }
        else
        {
            /*
             * Read all keys from handle
             */
            key_fields_array[key_field_index].field_id = table->keys_info[key_field_index].field_id;
            SHR_IF_ERR_EXIT(dbal_entry_handle_key_field_arr32_get
                            (unit, entry_handle_id, key_fields_array[key_field_index].field_id,
                             key_fields_array[key_field_index].field_val));
            SHR_IF_ERR_EXIT(dbal_field_in_table_printable_string_get(unit,
                                                                     key_fields_array[key_field_index].field_id,
                                                                     0,
                                                                     table_id,
                                                                     key_fields_array[key_field_index].field_val, NULL,
                                                                     result_type_idx, TRUE, FALSE, buffer));

        }
        LOG_CLI((BSL_META("  %-40s %s\n"), dbal_field_to_string(unit, key_fields_array[key_field_index].field_id),
                 buffer));
    }
    /*
     * Read Result fields
     */
    if (SHR_IS_BITSET(table->indications_bm, DBAL_TABLE_IND_HAS_RESULT_TYPE))
    {
        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field_arr32_get
                        (unit, entry_handle_id, DBAL_FIELD_RESULT_TYPE, INST_SINGLE, val_fields_array[0].field_val));
        val_fields_array[0].field_id = DBAL_FIELD_RESULT_TYPE;
        val_fields_array[0].inst_idx = 0;
        result_type_idx = val_fields_array[0].field_val[0];

        first_res_index = 1;
    }

    for (field_index = first_res_index; field_index < table->multi_res_info[result_type_idx].nof_result_fields;
         field_index++)
    {
        inst_idx = table->multi_res_info[result_type_idx].results_info[field_index].inst_idx;
        field_id = table->multi_res_info[result_type_idx].results_info[field_index].field_id;

        val_fields_array[field_index].field_id = field_id;
        val_fields_array[field_index].inst_idx = inst_idx;

        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field_arr32_get(unit, entry_handle_id, field_id,
                                                                inst_idx, val_fields_array[field_index].field_val));
    }

    if (SHR_IS_BITSET(table->indications_bm, DBAL_TABLE_IND_ZERO_SIZE_PAYLOAD_SUPPORT))
    {
        SHR_IF_ERR_EXIT(dbal_entry_attribute_get(unit, entry_handle_id, DBAL_ENTRY_ATTR_NO_PAYLOAD, &is_no_payload));
    }

    /** Print Result fields */
    LOG_CLI((BSL_META("\nResult:\n")));
    if (is_no_payload)
    {
        LOG_CLI((BSL_META("no payload\n")));
    }
    else
    {
        for (field_index = 0; field_index < table->multi_res_info[result_type_idx].nof_result_fields; field_index++)
        {
            SHR_IF_ERR_EXIT(dbal_field_in_table_printable_string_get
                            (unit, val_fields_array[field_index].field_id,
                             val_fields_array[field_index].inst_idx,
                             table_id,
                             val_fields_array[field_index].field_val, NULL, result_type_idx, FALSE, FALSE, buffer));
            LOG_CLI((BSL_META("  %-40s %s\n"),
                     dbal_field_with_inst_to_string(unit, val_fields_array[field_index].field_id,
                                                    val_fields_array[field_index].inst_idx, field_str), buffer));
        }
    }

    if ((table->access_method == DBAL_ACCESS_METHOD_HARD_LOGIC) && table->table_type == DBAL_TABLE_TYPE_TCAM_DIRECT)
    {
        uint32 is_invalid;

        LOG_CLI((BSL_META("Entry is valid:")));
        SHR_IF_ERR_EXIT(dbal_entry_attribute_get(unit, entry_handle_id, DBAL_ENTRY_ATTR_INVALID, &is_invalid));
        if (!is_invalid)
        {
            LOG_CLI((BSL_META(" Yes")));
        }
        else
        {
            LOG_CLI((BSL_META(" No")));
        }
    }
    LOG_CLI((BSL_META("\n")));

exit:
    if (key_fields_array != NULL)
    {
        sal_free(key_fields_array);
    }

    if (val_fields_array != NULL)
    {
        sal_free(val_fields_array);
    }
    SHR_FUNC_EXIT;
}

/**
 * \brief - get a DBAL table entry
 */
static shr_error_e
diag_dbal_entry_get(
    int unit,
    args_t * args,
    sh_sand_control_t * sand_control)
{
    int rv;
    CONST dbal_logical_table_t *table;
    uint32 entry_handle_id;
    int key_field_index = 0;
    uint32 access_id;
    int lif_val = 0, result_type_set = 0;
    uint8 num_const = 0;
    uint8 is_key_const = FALSE;
    char *table_name;
    dbal_tables_e table_id;
    char *cmd = "Get";
    sh_sand_arg_t *sand_arg;
    dbal_fields_e field_id;
    uint8 is_key;
    uint8 action_validated = 0;
    uint8 is_clear_hitbit = 0;
    uint32 clear_hitbit_flag = 0;
    int is_hw_only;
    dbal_entry_action_flags_e flags = DBAL_GET_ALL_FIELDS | DBAL_COMMIT_IGNORE_ALLOC_ERROR;
    int core_added_to_list = 0;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /*
     * Get parameters
     */
    SH_SAND_GET_STR("table", table_name);
    SH_SAND_GET_BOOL("ClearHitBit", is_clear_hitbit);
    SH_SAND_GET_BOOL("HwOnly", is_hw_only);

    if (is_hw_only)
    {
        flags |= DBAL_COMMIT_HW_ONLY;
    }

    if (ISEMPTY(table_name))
    {
        /**dbal_tables_list_dump(unit, DBAL_LABEL_NONE, sand_control);*/
        DIAG_DBAL_HEADER_DUMP("Example: dbal ENTry Get TaBLe=<table_name>", "\0");
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(diag_dbal_table_from_string(unit, table_name, &table_id, sand_control, NULL, TRUE));
    if (table_id == dnx_data_dbal.table.nof_dynamic_and_static_tables_get(unit))
    {
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(dbal_tables_table_get(unit, table_id, &table));
    DIAG_DBAL_TABLE_STATUS_VALIDATE(table_id);

    if (is_clear_hitbit)
    {
        uint32 is_hitbit_enabled;
        /** Check hitbit is supported for this table */
        SHR_IF_ERR_EXIT(dbal_tables_indication_get(unit, table_id, DBAL_TABLE_IND_IS_HITBIT_EN, &is_hitbit_enabled));
        if (!is_hitbit_enabled)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Clear Hitbit option is not supported for this table");
        }
        clear_hitbit_flag = DBAL_ENTRY_ATTR_HIT_CLEAR;
    }

    /** Get table handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table_id, &entry_handle_id));

    /** get the number of const fields in the key */
    SHR_IF_ERR_EXIT(dbal_tables_field_is_key_const_val_num_get(unit, table_id, &num_const));

    if (DBAL_TABLE_IS_TCAM_BY_ID(table))
    {
        /** Get access id */
        SH_SAND_GET_UINT32("AccessId", access_id);

        if (access_id == 0xffffffff)
        {
            /** Access id not received or not legal */
            SHR_IF_ERR_EXIT(diag_dbal_entry_print_accessId_missing(unit, table_id));
            SHR_EXIT();
        }
        else
        {
            SHR_IF_ERR_EXIT(dbal_entry_handle_access_id_set(unit, entry_handle_id, access_id));
            action_validated = 1;
        }
    }
/*
 * By default core is not considered a dynamic arg as it is a system arg,
 * we want to force add it to the dynamic args list so that it is handled by the iterator that follows
*/
    SHR_IF_ERR_EXIT(sh_sand_add_option_dyn_args(unit, sand_control, "core", diag_dbal_entry_cmd_field_get));
    core_added_to_list = 1;

    SH_SAND_GET_ITERATOR(sand_arg)
    {
        int mask_present = SH_SAND_HAS_MASK(sand_arg);
        field_id = SH_SAND_GET_ID(sand_arg);

        SHR_IF_ERR_EXIT(dbal_tables_field_is_key_get(unit, table_id, field_id, &is_key));
        if (is_key == TRUE)
        {
            SHR_IF_ERR_EXIT(dbal_tables_field_is_key_const_get(unit, table_id, field_id, &is_key_const));
            if (!is_key_const)
            {
                if (mask_present && ((DBAL_TABLE_IS_TCAM(table)) || (table->table_type == DBAL_TABLE_TYPE_LPM)))
                {
                    /** Get Key fields Params with mask */
                    DBAL_ENTRY_COMMIT_KEY_FIELD_WITH_MASK(unit, entry_handle_id, field_id, sand_arg);
                }
                else
                {
                    /** Get Key fields Params */
                    DBAL_ENTRY_COMMIT_KEY_FIELD(unit, entry_handle_id, field_id, sand_arg);
                    if (field_id == DBAL_FIELD_OUT_LIF || field_id == DBAL_FIELD_IN_LIF
                        || field_id == DBAL_FIELD_OUT_RIF)
                    {
                        lif_val = SH_SAND_ARG_ARRAY_DATA(sand_arg)[0];
                    }
                }
                key_field_index++;
            }
        }
        else if (field_id == DBAL_FIELD_RESULT_TYPE)
        {
            SHR_IF_ERR_EXIT(diag_dbal_result_type_set(unit, entry_handle_id, table_id, sand_arg, cmd));
            result_type_set = 1;
        }
    }

    if ((!((table->table_type == DBAL_TABLE_TYPE_TCAM_DIRECT) || (table->table_type == DBAL_TABLE_TYPE_TCAM_BY_ID)) &&
         ((key_field_index + num_const) != table->nof_key_fields)) ||
        (((key_field_index + num_const) == 0) && !action_validated && ((DBAL_TABLE_IS_TCAM(table)))))
    {
        LOG_CLI((BSL_META("Key fields are mandatory please find available fields below:\n")));
        SHR_IF_ERR_EXIT(diag_dbal_entry_print_help_line(unit, table_id, 0, cmd, TRUE));
        SHR_EXIT();
    }
    else
    {
        if (((DBAL_TABLE_IS_TCAM(table))) && (table->access_method == DBAL_ACCESS_METHOD_MDB) && !action_validated)
        {
            SHR_IF_ERR_EXIT(dbal_entry_access_id_by_key_get(unit, entry_handle_id, &access_id, DBAL_COMMIT));
            SHR_IF_ERR_EXIT(dbal_entry_handle_access_id_set(unit, entry_handle_id, access_id));
        }

        /** reading the result type incase of LIF tables (LIF tables require the result type when geting/clearing */
        if ((result_type_set == 0) && ((dbal_table_is_in_lif(table)) || (dbal_table_is_out_lif(table))))
        {
            SHR_IF_ERR_EXIT(diag_dbal_entry_lif_res_type_set(unit, entry_handle_id, lif_val));
        }

        if (SHR_IS_BITSET(table->indications_bm, DBAL_TABLE_IND_IS_HITBIT_EN))
        {
            SHR_IF_ERR_EXIT(dbal_entry_attribute_request(unit, entry_handle_id,
                                                         (DBAL_ENTRY_ATTR_HIT_PRIMARY | DBAL_ENTRY_ATTR_HIT_SECONDARY |
                                                          DBAL_ENTRY_ATTR_HIT_GET | clear_hitbit_flag), NULL));

            if (!dnx_data_l2.feature.feature_get(unit, dnx_data_l2_feature_age_state_not_updated))
            {
                if (dbal_logical_table_is_mact(unit, table_id))
                {
                    SHR_IF_ERR_EXIT(dbal_entry_attribute_request(unit, entry_handle_id, DBAL_ENTRY_ATTR_AGE, NULL));
                }
            }
        }

        rv = dbal_entry_get(unit, entry_handle_id, flags);
        if (rv == _SHR_E_ACCESS)
        {
            dbal_entry_handle_t *entry_handle;
            SHR_IF_ERR_EXIT(dbal_entry_handle_get_internal(unit, entry_handle_id, &entry_handle));
            SHR_ERR_EXIT(rv, "Access to unmapped combination of key fields. "
                         "The first field failing the mapping condition is: %s. Check that keys combination fits the mapping definition.\n",
                         dbal_field_to_string(unit, entry_handle->error_info.field_and_instance));
        }
        SHR_IF_ERR_EXIT(rv);
        SHR_IF_ERR_EXIT(diag_dbal_entry_print_entry(unit, entry_handle_id));
    }

exit:
    if (core_added_to_list)
    {
        /** Free allocation of core from dynamic dynamic args list*/
        sh_sand_remove_option_dyn_stats_args(unit, sand_control, "core", diag_dbal_entry_cmd_field_get, FALSE);
    }

    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - clear a DBAL table entry
 */
static shr_error_e
diag_dbal_entry_clear(
    int unit,
    args_t * args,
    sh_sand_control_t * sand_control)
{
    CONST dbal_logical_table_t *table;
    uint32 entry_handle_id;
    int key_field_index = 0;
    uint32 access_id;

    char *table_name;
    dbal_tables_e table_id;
    char *cmd = "CLear";
    sh_sand_arg_t *sand_arg;
    dbal_fields_e field_id;
    uint8 is_key, is_key_const, num_const;
    int lif_val = 0, result_type_set = 0;
    int is_hw_only;
    dbal_entry_action_flags_e flags = DBAL_COMMIT;
    int access_id_set = 0;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /*
     * Get parameters
     */
    SH_SAND_GET_STR("table", table_name);
    SH_SAND_GET_BOOL("HwOnly", is_hw_only);

    if (is_hw_only)
    {
        flags |= DBAL_COMMIT_HW_ONLY;
    }

    if (ISEMPTY(table_name))
    {
        /**dbal_tables_list_dump(unit, DBAL_LABEL_NONE, sand_control);*/
        DIAG_DBAL_HEADER_DUMP("Example: dbal ENTry CLear TaBLe=<table_name>", "\0");
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(diag_dbal_table_from_string(unit, table_name, &table_id, sand_control, NULL, TRUE));
    if (table_id == dnx_data_dbal.table.nof_dynamic_and_static_tables_get(unit))
    {
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(dbal_tables_table_get(unit, table_id, &table));
    DIAG_DBAL_TABLE_STATUS_VALIDATE(table_id);

    /** Get table handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table_id, &entry_handle_id));

    if (DBAL_TABLE_IS_TCAM_BY_ID(table))
    {
        /** Get access id */
        SH_SAND_GET_INT32("AccessId", access_id);

        if (access_id == 0xffffffff)
        {
            /** Access id not received or not legal */
            SHR_IF_ERR_EXIT(diag_dbal_entry_print_accessId_missing(unit, table_id));
            SHR_EXIT();
        }
        else
        {
            SHR_IF_ERR_EXIT(dbal_entry_handle_access_id_set(unit, entry_handle_id, access_id));
            access_id_set = 1;
        }
    }

    SH_SAND_GET_ITERATOR(sand_arg)
    {
        field_id = SH_SAND_GET_ID(sand_arg);
        SHR_IF_ERR_EXIT(dbal_tables_field_is_key_get(unit, table_id, field_id, &is_key));
        SHR_IF_ERR_EXIT(dbal_tables_field_is_key_const_get(unit, table_id, field_id, &is_key_const));
        if ((is_key == TRUE) && (is_key_const == FALSE))
        {
            /*
             * Get Key fields Params
             */
            DBAL_ENTRY_COMMIT_KEY_FIELD(unit, entry_handle_id, field_id, sand_arg);
            key_field_index++;

            if (field_id == DBAL_FIELD_OUT_LIF || field_id == DBAL_FIELD_IN_LIF || field_id == DBAL_FIELD_OUT_RIF)
            {
                lif_val = SH_SAND_ARG_ARRAY_DATA(sand_arg)[0];
            }
        }
        else if (field_id == DBAL_FIELD_RESULT_TYPE)
        {
            SHR_IF_ERR_EXIT(diag_dbal_result_type_set(unit, entry_handle_id, table_id, sand_arg, cmd));
            result_type_set = 1;
        }

    }

    /** reading the result type in case of LIF tables (LIF tables require the result type when getting/clearing */
    if ((result_type_set == 0) && ((dbal_table_is_in_lif(table)) || (dbal_table_is_out_lif(table))))
    {
        SHR_IF_ERR_EXIT(diag_dbal_entry_lif_res_type_set(unit, entry_handle_id, lif_val));
    }

    SHR_IF_ERR_EXIT(dbal_tables_field_is_key_const_val_num_get(unit, table_id, &num_const));
    if ((!(DBAL_TABLE_IS_TCAM(table)) && ((key_field_index + num_const) != table->nof_key_fields)) ||
        ((access_id_set == 0) && (key_field_index == 0) && DBAL_TABLE_IS_TCAM(table)))
    {
        LOG_CLI((BSL_META("All Key fields are mandatory please find available fields below:\n")));
        SHR_IF_ERR_EXIT(diag_dbal_entry_print_help_line(unit, table_id, 0, cmd, TRUE));
        SHR_EXIT();
    }
    else
    {
        if ((DBAL_TABLE_IS_TCAM(table)) && (table->access_method == DBAL_ACCESS_METHOD_MDB))
        {
            SHR_IF_ERR_EXIT(dbal_entry_access_id_by_key_get(unit, entry_handle_id, &access_id, DBAL_COMMIT));
            SHR_IF_ERR_EXIT(dbal_entry_handle_access_id_set(unit, entry_handle_id, access_id));
        }

        SHR_IF_ERR_EXIT(dbal_entry_clear(unit, entry_handle_id, flags));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static sh_sand_option_t diag_dbal_entry_commit_options[] = {
    {"TaBLe", SAL_FIELD_TYPE_STR, "dbal table name", "",.ac_option_cb = diag_dbal_table_autocomplete_cb},
    {"AccessId", SAL_FIELD_TYPE_UINT32, "dbal entry access id", "0xffffffff"},
    {"Priority", SAL_FIELD_TYPE_UINT32, "dbal entry priority", "0"},
    {"HwOnly", SAL_FIELD_TYPE_BOOL, "dbal commit entry to HW only without using"
     " shadow.\n" "The operation is supported for MDB EM tables only", "false"},
    {"NoPayload", SAL_FIELD_TYPE_BOOL, "Commit an entry with 0 size payload.\n"
     "Supported for tables with DBAL_TABLE_IND_ZERO_SIZE_PAYLOAD_SUPPORT set", "false"},
    {NULL}
};

static sh_sand_man_t diag_dbal_entry_commit_man = {
    .brief = "Set and commit a table entry",
    .full = NULL,
    .synopsis = "Table=<table_name>",
    .examples =
        "table=IN_AC_C_VLAN_DB Priority=1 VLAN_DOMAIN=1 C_VID=2 IN_LIF=3\n"
        "table=PRT_VIRTUAL_PORT_TCAM AccessId=1 PRT_KBR_INFO_HALF=2 CORE_ID=0\n"
        "TaBLe=fwd_mact Result_Type=FWD_MACT_RESULT_DEST_STAT MAC_STRENGTH=1 FODO=1 L2_MAC=12:12:12:12:12:12 HwOnly\n"
        "TaBLe=IPV4_RPF_FIB VRF=1 IPV4=2 NoPayload"
};

static sh_sand_option_t diag_dbal_entry_update_options[] = {
    {"TaBLe", SAL_FIELD_TYPE_STR, "dbal table name", "",.ac_option_cb = diag_dbal_table_autocomplete_cb},
    {"AccessId", SAL_FIELD_TYPE_UINT32, "dbal entry access id", "0xffffffff"},
    {"Priority", SAL_FIELD_TYPE_UINT32, "dbal entry priority", "0"},
    {"HwOnly", SAL_FIELD_TYPE_BOOL, "dbal commit entry to HW only without using"
     " shadow. The operation is supported for MDB EM tables only", "false"},
    {"NoPayload", SAL_FIELD_TYPE_BOOL, "Commit an entry with 0 size payload.\n"
     "Supported for tables with DBAL_TABLE_IND_ZERO_SIZE_PAYLOAD_SUPPORT set", "false"},
    {NULL}
};

static sh_sand_man_t diag_dbal_entry_update_man = {
    .brief = "Set and update a table entry",
    .full = NULL,
    .synopsis = "Table=<table_name>",
    .examples = "table=IN_AC_C_VLAN_DB Priority=1 VLAN_DOMAIN=1 C_VID=2 IN_LIF=3\n"
        "table=PRT_VIRTUAL_PORT_TCAM AccessId=1 PRT_KBR_INFO_HALF=2 CORE_ID=0\n"
        "TaBLe=fwd_mact Result_Type=FWD_MACT_RESULT_DEST_STAT MAC_STRENGTH=2 FODO=1 L2_MAC=12:12:12:12:12:12 hwonly\n"
        "TaBLe=IPV4_RPF_FIB VRF=1 IPV4=2 NoPayload"
};

static sh_sand_option_t diag_dbal_entry_get_options[] = {
    {"TaBLe", SAL_FIELD_TYPE_STR, "dbal table name", "",.ac_option_cb = diag_dbal_table_autocomplete_cb},
    {"AccessId", SAL_FIELD_TYPE_UINT32, "dbal entry access id", "0xffffffff"},
    {"ClearHitBit", SAL_FIELD_TYPE_BOOL, "Clear Hitbit", "false"},
    {"HwOnly", SAL_FIELD_TYPE_BOOL, "dbal get entry from HW only without using"
     " shadow. The operation is supported for MDB EM tables only", "false"},
    {NULL}
};

static sh_sand_man_t diag_dbal_entry_get_man = {
    .brief = "Get a table Entry",
    .full = NULL,
    .synopsis = "Table=<table_name>",
    .examples = "table=IN_AC_C_VLAN_DB VLAN_DOMAIN=1 C_VID=2 IN_LIF=4 ClearHitBit\n"
        "table=PRT_VIRTUAL_PORT_TCAM AccessId=1 CORE_ID=0\n" "TaBLe=fwd_mact FODO=1 L2_MAC=12:12:12:12:12:12 hwonly\n"
        "TaBLe=IPV4_RPF_FIB VRF=1 IPV4=2"
};

static sh_sand_option_t diag_dbal_entry_clear_options[] = {
    {"TaBLe", SAL_FIELD_TYPE_STR, "dbal table name", "",.ac_option_cb = diag_dbal_table_autocomplete_cb},
    {"AccessId", SAL_FIELD_TYPE_INT32, "dbal entry access id", "0xffffffff"},
    {"HwOnly", SAL_FIELD_TYPE_BOOL, "dbal clear entry to HW only, fails if "
     "the entry exists in shadow too. The operation is supported for MDB EM tables only", "false"},
    {NULL}
};

static sh_sand_man_t diag_dbal_entry_clear_man = {
    .brief = "Clear a table entry",
    .full = NULL,
    .synopsis = "Table=<table_name>",
    .examples = "table=IN_AC_C_VLAN_DB VLAN_DOMAIN=1 C_VID=2 IN_LIF=4\n"
        "table=EGRESS_ETPP_TERM_CONTEXT_PROPERTIES AccessId=1\n" "table=PRT_VIRTUAL_PORT_TCAM AccessId=1 CORE_ID=0\n"
        "TaBLe=fwd_mact Result_Type=FWD_MACT_RESULT_DEST_STAT FODO=1 L2_MAC=12:12:12:12:12:12 hwonly\n"
        "TaBLe=IPV4_RPF_FIB VRF=1 IPV4=2"
};

sh_sand_cmd_t diag_dbal_entry_cmds[] = {
   /******************************************************************************************************************
    * CMD    *     CMD_ACTION           * Next *        Options               *            MAN             * CB      *
    * NAME   *                          * Level*                              *                            *         *
    *        *                          * CMD  *                              *                            *         *
    ******************************************************************************************************************/
    {"CoMmit", diag_dbal_entry_commit, NULL, diag_dbal_entry_commit_options, &diag_dbal_entry_commit_man,
     diag_dbal_entry_cmd_field_get},
    {"Update", diag_dbal_entry_update, NULL, diag_dbal_entry_update_options, &diag_dbal_entry_update_man,
     diag_dbal_entry_cmd_field_get},
    {"Get", diag_dbal_entry_get, NULL, diag_dbal_entry_get_options, &diag_dbal_entry_get_man,
     diag_dbal_entry_cmd_field_get},
    {"CLear", diag_dbal_entry_clear, NULL, diag_dbal_entry_clear_options, &diag_dbal_entry_clear_man,
     diag_dbal_entry_cmd_field_get},
    {NULL}
};

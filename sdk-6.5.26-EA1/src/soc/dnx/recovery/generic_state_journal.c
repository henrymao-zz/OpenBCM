/*
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * INFO: This module is a generic side effect / state rollback journal,
 * saving the old values of global state or side effects that were overridden
 * by access calls since the beginning of the last transaction.
 * This journal should be used only in places where the existing DBAL or SWSTATE journal fail short.
 */

#include <assert.h>
#include <shared/bsl.h>
#include <soc/sand/shrextend/shrextend_debug.h>
#include <sal/core/sync.h>
#include <soc/dnx/dnx_err_recovery_manager_common.h>
#include <soc/dnx/recovery/rollback_journal.h>
#include <soc/dnx/recovery/rollback_journal_utils.h>
#include <soc/dnx/recovery/generic_state_journal.h>
#include <soc/dnx/dnx_er_threading.h>

#ifdef BCM_DNX_SUPPORT
#include <soc/dnx/dbal/dbal.h>
#include <soc/dnx/dbal/dbal_dynamic.h>
#endif

#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif

#define BSL_LOG_MODULE BSL_LS_SOCDNX_ERRORRECOVERY

static dnx_generic_state_journal_manager_t dnx_generic_state_journal_manager[SOC_MAX_NUM_DEVICES] = { {0} };

#define DNX_DBAL_ROLLBACK_JOURNAL_NUM 0
#define DNX_DBAL_COMPARISON_JOURNAL_NUM 1
#define DNX_GENERIC_STATE_ROLLBACK_JOURNAL_HANDLE dnx_generic_state_journal_manager[unit].journals[DNX_DBAL_ROLLBACK_JOURNAL_NUM].handle
#define DNX_GENERIC_STATE_COMPARISON_JOURNAL_HANDLE dnx_generic_state_journal_manager[unit].journals[DNX_DBAL_COMPARISON_JOURNAL_NUM].handle

int
dnx_is_generic_state_journal_is_on(
    int unit)
{
    int er_thread_id = dnx_er_threading_transaction_get(unit);

    if (er_thread_id == -1)
    {
        return FALSE;
    }

    return dnx_rollback_journal_is_on(unit, er_thread_id, DNX_GENERIC_STATE_ROLLBACK_JOURNAL_HANDLE);
}

static shr_error_e
dnx_generic_state_journal_rollback_memcpy_entry(
    int unit,
    int er_thread_id,
    uint8 *metadata,
    uint8 *payload,
    char *stamp)
{
    dnx_generic_state_journal_entry_t *entry = (dnx_generic_state_journal_entry_t *) (metadata);

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_common_is_validation_enabled(unit))
    {
        if ((NULL == entry->ptr) || (NULL == payload))
        {
            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "state journal ERROR: invalid entry data detected.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    sal_memcpy(entry->ptr, payload, entry->size);

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_generic_state_journal_entry_new(
    int unit,
    uint8 *metadata,
    uint32 metadata_size,
    uint8 *payload,
    uint32 payload_size,
    dnx_generic_state_journal_rollback_handler rollback_handler,
    uint8 is_comparison)
{
    int er_thread_id = -1;

    SHR_FUNC_INIT_VARS(unit);

    er_thread_id = dnx_er_threading_transaction_get(unit);

    assert(er_thread_id != -1);

    if (is_comparison)
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_entry_new(unit,
                                                       er_thread_id,
                                                       DNX_GENERIC_STATE_COMPARISON_JOURNAL_HANDLE,
                                                       metadata,
                                                       metadata_size,
                                                       payload,
                                                       payload_size,
                                                       DNX_ROLLBACK_JOURNAL_ENTRY_STATE_VALID,
                                                       rollback_handler, NULL, NULL));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_entry_new(unit,
                                                       er_thread_id,
                                                       DNX_GENERIC_STATE_ROLLBACK_JOURNAL_HANDLE,
                                                       metadata,
                                                       metadata_size,
                                                       payload,
                                                       payload_size,
                                                       DNX_ROLLBACK_JOURNAL_ENTRY_STATE_VALID,
                                                       rollback_handler, NULL, NULL));
    }

exit:
    SHR_FUNC_EXIT;
}

#ifdef BCM_DNX_SUPPORT

static shr_error_e
dnx_generic_state_journal_rollback_dbal_table_info_change(
    int unit,
    int er_thread_id,
    uint8 *metadata,
    uint8 *payload,
    char *stamp)
{
    dnx_generic_state_journal_dbal_table_entry_t *entry = (dnx_generic_state_journal_dbal_table_entry_t *) (metadata);

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_common_is_validation_enabled(unit))
    {
        if (NULL == metadata)
        {
            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "state journal ERROR: invalid entry data detected.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    SHR_IF_ERR_EXIT(dbal_tables_table_restore(unit, entry->table_id));

exit:
    SHR_FUNC_EXIT;
}

static inline shr_error_e
dnx_generic_state_journal_log_dbal_table_info_change_internal(
    int unit,
    int er_thread_id,
    dbal_tables_e table_id)
{
    dnx_generic_state_journal_dbal_table_entry_t entry;

    SHR_FUNC_INIT_VARS(unit);

    if (table_id < DBAL_NOF_TABLES)
    {
        DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                    "state journal ERROR: Attempted to log change to non dynamic DBAL table %d.\n%s%s",
                                                    table_id, EMPTY, EMPTY);
    }

    entry.table_id = table_id;

    SHR_IF_ERR_EXIT(dnx_generic_state_journal_entry_new(unit,
                                                        (uint8 *) (&entry),
                                                        sizeof(dnx_generic_state_journal_dbal_table_entry_t),
                                                        (uint8 *) (&entry),
                                                        sizeof(dnx_generic_state_journal_dbal_table_entry_t),
                                                        &dnx_generic_state_journal_rollback_dbal_table_info_change,
                                                        FALSE));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_generic_state_journal_log_dbal_table_info_change(
    int unit,
    dbal_tables_e table_id)
{
    int er_thread_id = dnx_er_threading_transaction_get(unit);

    SHR_FUNC_INIT_VARS(unit);

    DNX_GENERIC_STATE_JOURNAL_EXIT_IF_OFF(unit);

    SHR_IF_ERR_EXIT(dnx_generic_state_journal_log_dbal_table_info_change_internal(unit, er_thread_id, table_id));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_generic_state_journal_rollback_result_type_add(
    int unit,
    int er_thread_id,
    uint8 *metadata,
    uint8 *payload,
    char *stamp)
{
    dnx_generic_state_journal_dbal_table_entry_t *entry = (dnx_generic_state_journal_dbal_table_entry_t *) (metadata);

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_common_is_validation_enabled(unit))
    {
        if (NULL == metadata)
        {
            SHR_IF_ERR_EXIT_WITH_LOG(_SHR_E_INTERNAL, "state journal ERROR: invalid entry data detected.\n%s%s%s",
                                     EMPTY, EMPTY, EMPTY);
        }
    }

    SHR_IF_ERR_EXIT(dbal_tables_dynamic_result_type_delete(unit, entry->table_id, entry->res_type_idx));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_generic_state_journal_log_result_type_add_internal(
    int unit,
    int er_thread_id,
    dbal_tables_e table_id,
    int res_type_idx)
{
    dnx_generic_state_journal_dbal_table_entry_t entry;

    SHR_FUNC_INIT_VARS(unit);

    entry.table_id = table_id;
    entry.res_type_idx = res_type_idx;

    SHR_IF_ERR_EXIT(dnx_generic_state_journal_entry_new(unit,
                                                        (uint8 *) (&entry),
                                                        sizeof(dnx_generic_state_journal_dbal_table_entry_t),
                                                        (uint8 *) (&entry),
                                                        sizeof(dnx_generic_state_journal_dbal_table_entry_t),
                                                        &dnx_generic_state_journal_rollback_result_type_add, FALSE));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_generic_state_journal_log_result_type_add(
    int unit,
    dbal_tables_e table_id,
    int res_type_idx)
{
    int er_thread_id = dnx_er_threading_transaction_get(unit);

    SHR_FUNC_INIT_VARS(unit);

    DNX_GENERIC_STATE_JOURNAL_EXIT_IF_OFF(unit);

    SHR_IF_ERR_EXIT(dnx_generic_state_journal_log_result_type_add_internal(unit, er_thread_id, table_id, res_type_idx));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_generic_state_journal_rollback_result_type_delete(
    int unit,
    int er_thread_id,
    uint8 *metadata,
    uint8 *payload,
    char *stamp)
{
    dnx_generic_state_journal_dbal_table_entry_t *entry = (dnx_generic_state_journal_dbal_table_entry_t *) (metadata);

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_common_is_validation_enabled(unit))
    {
        if (NULL == metadata)
        {
            SHR_IF_ERR_EXIT_WITH_LOG(_SHR_E_INTERNAL, "state journal ERROR: invalid entry data detected.\n%s%s%s",
                                     EMPTY, EMPTY, EMPTY);
        }
    }

    SHR_IF_ERR_EXIT(dbal_tables_result_type_restore_rollback(unit, entry->table_id));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_generic_state_journal_log_result_type_delete_internal(
    int unit,
    int er_thread_id,
    dbal_tables_e table_id)
{
    dnx_generic_state_journal_dbal_table_entry_t entry;

    SHR_FUNC_INIT_VARS(unit);

    entry.table_id = table_id;

    SHR_IF_ERR_EXIT(dnx_generic_state_journal_entry_new(unit,
                                                        (uint8 *) (&entry),
                                                        sizeof(dnx_generic_state_journal_dbal_table_entry_t),
                                                        (uint8 *) (&entry),
                                                        sizeof(dnx_generic_state_journal_dbal_table_entry_t),
                                                        &dnx_generic_state_journal_rollback_result_type_delete, FALSE));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_generic_state_journal_log_result_type_delete(
    int unit,
    dbal_tables_e table_id)
{
    int er_thread_id = dnx_er_threading_transaction_get(unit);

    SHR_FUNC_INIT_VARS(unit);

    DNX_GENERIC_STATE_JOURNAL_EXIT_IF_OFF(unit);

    SHR_IF_ERR_EXIT(dnx_generic_state_journal_log_result_type_delete_internal(unit, er_thread_id, table_id));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_generic_state_journal_rollback_free_entry(
    int unit,
    int er_thread_id,
    uint8 *metadata,
    uint8 *payload,
    char *stamp)
{
    dnx_generic_state_journal_free_entry_t *entry = (dnx_generic_state_journal_free_entry_t *) metadata;
    uint32 data_size = entry->nof_elements * entry->element_size;

    SHR_FUNC_INIT_VARS(unit);

    SHR_ALLOC_SET_ZERO(*(entry->ptr_location), data_size, "error recovery free entry rollback", "%s%s%s\r\n", EMPTY,
                       EMPTY, EMPTY);

    sal_memcpy(*(entry->ptr_location), payload, data_size);

exit:
    SHR_FUNC_EXIT;
}

static inline shr_error_e
dnx_generic_state_journal_log_free_internal(
    int unit,
    int er_thread_id,
    uint32 nof_elements,
    uint32 element_size,
    uint8 **ptr_location)
{
    dnx_generic_state_journal_free_entry_t entry;
    uint32 data_size = 0;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_common_is_validation_enabled(unit))
    {

        if (NULL == ptr_location)
        {
            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "state journal ERROR: NULL data attempted to be inserted to journal.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    if (NULL == *ptr_location)
    {
        SHR_EXIT();
    }

    entry.nof_elements = nof_elements;
    entry.element_size = element_size;
    entry.location = *ptr_location;
    entry.ptr_location = ptr_location;

    data_size = entry.nof_elements * entry.element_size;

    SHR_IF_ERR_EXIT(dnx_generic_state_journal_entry_new(unit,
                                                        (uint8 *) (&entry),
                                                        sizeof(dnx_generic_state_journal_free_entry_t),
                                                        *ptr_location,
                                                        data_size, &dnx_generic_state_journal_rollback_free_entry,
                                                        FALSE));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_generic_state_journal_log_free(
    int unit,
    uint32 nof_elements,
    uint32 element_size,
    uint8 **ptr_location)
{
    int er_thread_id = dnx_er_threading_transaction_get(unit);

    SHR_FUNC_INIT_VARS(unit);

    DNX_GENERIC_STATE_JOURNAL_EXIT_IF_OFF(unit);

    SHR_IF_ERR_EXIT(dnx_generic_state_journal_log_free_internal
                    (unit, er_thread_id, nof_elements, element_size, ptr_location));

exit:
    SHR_FUNC_EXIT;
}

#endif

static inline shr_error_e
dnx_generic_state_journal_log_memcpy_internal(
    int unit,
    int er_thread_id,
    uint32 size,
    uint8 *ptr)
{
    dnx_generic_state_journal_entry_t entry;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_common_is_validation_enabled(unit))
    {
        if (NULL == ptr)
        {
            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "state journal ERROR: NULL data attempted to be inserted to journal.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }

        if (0 == size)
        {
            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "state journal ERROR: data with size zero attempted to be inserted to journal.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    entry.size = size;
    entry.ptr = ptr;

    SHR_IF_ERR_EXIT(dnx_generic_state_journal_entry_new(unit,
                                                        (uint8 *) (&entry),
                                                        sizeof(dnx_generic_state_journal_entry_t),
                                                        ptr, size, &dnx_generic_state_journal_rollback_memcpy_entry,
                                                        FALSE));

    SHR_EXIT();

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_generic_state_journal_log_memcpy(
    int unit,
    uint32 size,
    uint8 *ptr)
{
    int er_thread_id = dnx_er_threading_transaction_get(unit);

    SHR_FUNC_INIT_VARS(unit);

    DNX_GENERIC_STATE_JOURNAL_EXIT_IF_OFF(unit);

    SHR_IF_ERR_EXIT(dnx_generic_state_journal_log_memcpy_internal(unit, er_thread_id, size, ptr));

exit:
    SHR_FUNC_EXIT;
}

static inline shr_error_e
dnx_generic_state_journal_clear_internal(
    int unit,
    int er_thread_id,
    uint8 is_comparison)
{
    SHR_FUNC_INIT_VARS(unit);

    if (is_comparison)
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_clear(unit, er_thread_id, DNX_GENERIC_STATE_COMPARISON_JOURNAL_HANDLE));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_clear(unit, er_thread_id, DNX_GENERIC_STATE_ROLLBACK_JOURNAL_HANDLE));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_generic_state_journal_clear(
    int unit,
    int er_thread_id,
    uint8 is_comparison)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_generic_state_journal_clear_internal(unit, er_thread_id, is_comparison));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_generic_state_journal_initialize(
    int unit,
    dnx_rollback_journal_cbs_t rollback_journal_cbs,
    uint8 is_comparison)
{
    int idx = 0;
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_common_is_validation_enabled(unit))
    {
        if (NULL == rollback_journal_cbs.is_on)
        {
            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "state journal ERROR: journal is on callback must be set.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    if (is_comparison)
    {
        for (idx = 0; idx < DNX_ERR_RECOVERY_MAX_NOF_ACTIVE_TRANSACTION; idx++)
        {
            SHR_IF_ERR_EXIT(dnx_rollback_journal_new
                            (unit, idx, TRUE, DNX_ROLLBACK_JOURNAL_TYPE_COMPARISON,
                             DNX_ROLLBACK_JOURNAL_SUBTYPE_GENERIC, rollback_journal_cbs,
                             &(DNX_GENERIC_STATE_COMPARISON_JOURNAL_HANDLE)));
        }
    }
    else
    {
        for (idx = 0; idx < DNX_ERR_RECOVERY_MAX_NOF_ACTIVE_TRANSACTION; idx++)
        {
            SHR_IF_ERR_EXIT(dnx_rollback_journal_new
                            (unit, idx, FALSE, DNX_ROLLBACK_JOURNAL_TYPE_ROLLBACK, DNX_ROLLBACK_JOURNAL_SUBTYPE_GENERIC,
                             rollback_journal_cbs, &(DNX_GENERIC_STATE_ROLLBACK_JOURNAL_HANDLE)));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_generic_state_journal_destroy(
    int unit,
    uint8 is_comparison)
{
    SHR_FUNC_INIT_VARS(unit);

    if (is_comparison)
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_destroy(unit, &(DNX_GENERIC_STATE_COMPARISON_JOURNAL_HANDLE)));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_destroy(unit, &(DNX_GENERIC_STATE_ROLLBACK_JOURNAL_HANDLE)));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_generic_state_journal_get_head_seq_id(
    int unit,
    int er_thread_id,
    uint8 is_comparison,
    uint32 *seq_id)
{
    SHR_FUNC_INIT_VARS(unit);

    if (is_comparison)
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_get_head_seq_id
                        (unit, er_thread_id, seq_id, DNX_GENERIC_STATE_COMPARISON_JOURNAL_HANDLE));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_get_head_seq_id
                        (unit, er_thread_id, seq_id, DNX_GENERIC_STATE_ROLLBACK_JOURNAL_HANDLE));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_generic_state_journal_all_tmp_suppress_unsafe(
    int unit,
    int er_thread_id,
    uint8 is_disable)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_rollback_journal_disabled_counter_change
                    (unit, er_thread_id, is_disable, DNX_GENERIC_STATE_ROLLBACK_JOURNAL_HANDLE, TRUE));
    SHR_IF_ERR_EXIT(dnx_rollback_journal_disabled_counter_change
                    (unit, er_thread_id, is_disable, DNX_GENERIC_STATE_COMPARISON_JOURNAL_HANDLE, TRUE));

exit:
    SHR_FUNC_EXIT;
}

static inline shr_error_e
dnx_generic_state_journal_roll_back_internal(
    int unit,
    int er_thread_id,
    uint8 only_head_rollback,
    uint8 is_comparison)
{
    SHR_FUNC_INIT_VARS(unit);

    if (is_comparison)
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_rollback
                        (unit, er_thread_id, only_head_rollback, DNX_GENERIC_STATE_COMPARISON_JOURNAL_HANDLE));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_rollback
                        (unit, er_thread_id, only_head_rollback, DNX_GENERIC_STATE_ROLLBACK_JOURNAL_HANDLE));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_generic_state_journal_roll_back(
    int unit,
    int er_thread_id,
    uint8 only_head_rollback,
    uint8 is_comparison)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_generic_state_journal_roll_back_internal
                    (unit, er_thread_id, only_head_rollback, is_comparison));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_generic_state_journal_end_and_compare(
    int unit)
{
    uint32 seq_id = 0;
    uint8 should_clean = TRUE;
    uint8 differences_exist = FALSE;

    shr_error_e rollback_rv = _SHR_E_NONE;
    int er_thread_id = dnx_er_threading_transaction_get(unit);

    SHR_FUNC_INIT_VARS(unit);

    assert(er_thread_id != -1);

    SHR_IF_ERR_EXIT(dnx_generic_state_journal_get_head_seq_id(unit, er_thread_id, TRUE, &seq_id));
    while (0 != seq_id)
    {
        rollback_rv = dnx_generic_state_journal_roll_back(unit, er_thread_id, TRUE, TRUE);
        if (_SHR_E_NONE != rollback_rv)
        {
            differences_exist = TRUE;
        }

        SHR_IF_ERR_EXIT(dnx_generic_state_journal_get_head_seq_id(unit, er_thread_id, TRUE, &seq_id));
    }

    should_clean = FALSE;

    if (differences_exist)
    {
        SHR_IF_ERR_EXIT_NO_MSG(SOC_E_INTERNAL);
    }
exit:
    if (should_clean)
    {
        dnx_generic_state_journal_clear(unit, er_thread_id, TRUE);
    }
    SHR_FUNC_EXIT;
}

#undef _ERR_MSG_MODULE_NAME

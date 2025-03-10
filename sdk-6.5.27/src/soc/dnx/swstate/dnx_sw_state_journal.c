/*
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * INFO: This module is one of the components needed for Error Recovery,
 * it is a rollback journal, saving the old values that were overridden
 * by sw_state access calls since the beginning of the last transaction.
 */

#include <shared/bsl.h>
#include <sal/core/sync.h>
#include <sal/core/thread.h>
#include <soc/sand/shrextend/shrextend_debug.h>
#include <soc/dnxc/swstate/dnxc_sw_state.h>
#include <soc/dnxc/swstate/dnxc_sw_state_dispatcher.h>
#include <soc/dnxc/swstate/sw_state_defs.h>
#include <soc/dnx/swstate/dnx_sw_state_journal.h>
#include <soc/dnx/dnx_err_recovery_manager.h>
#include <soc/dnx/recovery/rollback_journal.h>
#include <soc/dnx/recovery/rollback_journal_diag.h>
#include <soc/dnx/recovery/rollback_journal_utils.h>
#include <soc/drv.h>
#include <soc/sand/shrextend/shrextend_debug.h>
#include <soc/dnxc/swstate/types/sw_state_hash_table.h>
#include <soc/dnxc/swstate/types/sw_state_index_hash_table.h>
#include <soc/dnxc/swstate/types/sw_state_htb.h>
#include <bcm_int/dnx/init/init_time_analyzer.h>
#include <soc/dnxc/swstate/dnxc_sw_state_wb.h>
#include <soc/dnxc/swstate/dnxc_sw_state_layout.h>

#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif

#define BSL_LOG_MODULE BSL_LS_SWSTATEDNX_GENERAL

#define DNX_SW_STATE_JOURNAL_BYTE_HEX_LEN 6

#define DNX_SW_STATE_JOURNAL_LAST_ELEMENT_REPEAT_LEN 34

#define DNX_SW_STATE_JOURNAL_UPDATE_ENTRY_ADDRESS(ptr, old_address, new_address, size) \
    do{ \
        if(((ptr) - (old_address) >= 0) && ((old_address) + (size) - (ptr) > 0)) { \
            (ptr) = (new_address) + ((ptr) - (old_address)); \
        } \
    } \
    while(0)

#define DNX_SW_STATE_JOURNAL_UPDATE_ENTRY_PTR_TO_ADDRESS(ptr, old_address, new_address, size) \
    do{ \
        if(((uint8 *)(ptr) - (uint8 *)(old_address) >= 0) \
        && ((uint8 *)(old_address) + (size) - (uint8 *)(ptr) > 0)) { \
            (ptr) = (uint8 **)((uint8 *)(new_address) + ((uint8 *)(ptr) - (uint8 *)(old_address))); \
        } \
    } \
    while(0)

#define DNX_SW_STATE_JOURNAL_UPDATE_MUTEX_ENTRY(mutex, old_mutex, new_mutex)\
    do{ \
        if(mutex == old_mutex) {\
            mutex = new_mutex;\
        }\
    } \
    while(0)

#define DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, offset)\
    dnxc_sw_state_dispatcher[unit][DNXC_SW_STATE_LAYOUT_GET_MODULE_ID(((dnx_sw_state_journal_entry_t *)(entry))->node_id)].calc_pointer(unit, ((dnx_sw_state_journal_entry_t *)(entry))->offset)

#define DNX_SWSTATE_JOURNAL_CALCULATE_DPOINTER(unit, entry, offset)\
    dnxc_sw_state_dispatcher[unit][DNXC_SW_STATE_LAYOUT_GET_MODULE_ID(((dnx_sw_state_journal_entry_t *)(entry))->node_id)].calc_dpointer(unit, ((dnx_sw_state_journal_entry_t *)(entry))->offset)

#define DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET(unit, entry, pointer)\
    dnxc_sw_state_dispatcher[unit][DNXC_SW_STATE_LAYOUT_GET_MODULE_ID(entry->node_id)].calc_offset(unit, pointer)

#define DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET_FROM_DPTR(unit, entry, pointer)\
    dnxc_sw_state_dispatcher[unit][DNXC_SW_STATE_LAYOUT_GET_MODULE_ID(entry->node_id)].calc_offset_from_dptr(unit, pointer)

#define DNX_SWSTATE_JOURNAL_ACCESS_NOTIFY(_unit, dnx_er_db)                                                                \
    do {                                                                                                                   \
        if(NULL != dnx_er_db->dnx_sw_state_manager->journals[DNX_SWSTATE_COMPARISON_JOURNAL_NUM].access_cb) {              \
            dnx_er_db->dnx_sw_state_manager->journals[DNX_SWSTATE_COMPARISON_JOURNAL_NUM].access_cb(_unit, dnx_er_db);     \
        }                                                                                                                  \
        if(NULL != dnx_er_db->dnx_sw_state_manager->journals[DNX_SWSTATE_ROLLBACK_JOURNAL_NUM].access_cb) {                \
            dnx_er_db->dnx_sw_state_manager->journals[DNX_SWSTATE_ROLLBACK_JOURNAL_NUM].access_cb(_unit, dnx_er_db);       \
        }                                                                                                                  \
    } while(0)

#ifdef DNX_ROLLBACK_JOURNAL_DIAGNOSTICS
#define DNX_SWSTATE_JOURNAL_DIAGNOSTICS_ALLOC(_unit, _jrnl_type, _jrnl_subtype, _size)\
    SHR_IF_ERR_EXIT(dnx_rollback_journal_diag_alloc(_unit, _jrnl_type, _jrnl_subtype, _size))
#else
#define DNX_SWSTATE_JOURNAL_DIAGNOSTICS_ALLOC(_unit, _jrnl_type, _jrnl_subtype, _size)
#endif

#define DNX_SWSTATE_JOURNAL_ALLOC(_unit, _ptr, _type, _size, _str, _jrnl_type, _jrnl_subtype) \
do {                                                                                          \
    (_ptr) = (_type)sal_alloc((_size), (_str));                                               \
    DNX_SWSTATE_JOURNAL_DIAGNOSTICS_ALLOC(_unit, _jrnl_type, _jrnl_subtype, _size);           \
} while(0)

#define DNX_SW_STATE_JOURNAL_MUTEX_DEFAULT_USEC sal_mutex_FOREVER
#define DNX_SW_STATE_JOURNAL_SEM_DEFAULT_USER sal_sem_FOREVER

#define DNX_SWSTATE_ROLLBACK_JOURNAL_NUM 0
#define DNX_SWSTATE_COMPARISON_JOURNAL_NUM 1

#define DNX_SW_STATE_ROLLBACK_JOURNAL_TRANSACTION dnx_er_db->dnx_sw_state_manager->journals[DNX_SWSTATE_ROLLBACK_JOURNAL_NUM].transaction
#define DNX_SW_STATE_COMPARISON_JOURNAL_TRANSACTION dnx_er_db->dnx_sw_state_manager->journals[DNX_SWSTATE_COMPARISON_JOURNAL_NUM].transaction

static shr_error_e
dnx_sw_state_journal_MEMCPY_entries_make_distinct(
    int unit,
    dnx_rollback_journal_entry_t * first_entry,
    uint8 *first_metadata,
    uint8 *first_payload,
    dnx_rollback_journal_entry_t * second_entry,
    uint8 *second_metadata,
    uint8 *second_payload)
{
    uint8 *ptr1;
    uint8 *ptr2;

    uint32 size1 =
        ((dnx_sw_state_journal_entry_t *) (first_metadata))->nof_elements *
        ((dnx_sw_state_journal_entry_t *) (first_metadata))->element_size;
    uint32 size2 =
        ((dnx_sw_state_journal_entry_t *) (second_metadata))->nof_elements *
        ((dnx_sw_state_journal_entry_t *) (second_metadata))->element_size;

    SHR_FUNC_INIT_VARS(unit);

    ptr1 = DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, first_metadata, data.memcpy_data.offset);
    ptr2 = DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, second_metadata, data.memcpy_data.offset);

    if (((ptr1 - ptr2 <= 0) && (ptr1 + size1 - (ptr2 + size2)) >= 0))
    {

        second_entry->state = DNX_ROLLBACK_JOURNAL_ENTRY_STATE_INVALID;
    }

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_HTBL_entries_make_distinct(
    int unit,
    dnx_rollback_journal_entry_t * first_entry,
    uint8 *first_metadata,
    uint8 *first_payload,
    dnx_rollback_journal_entry_t * second_entry,
    uint8 *second_metadata,
    uint8 *second_payload)
{
    uint8 *hash_table_ptr;
    SHR_FUNC_INIT_VARS(unit);

    hash_table_ptr = DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, first_metadata, data.htbl_data.hash_table_offset);

    if (DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, first_metadata, data.htbl_data.hash_table_offset) !=
        DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, second_metadata, data.htbl_data.hash_table_offset))
    {
        SHR_EXIT();
    }

    if (sal_memcmp(first_payload, second_payload, ((sw_state_htbl_t) hash_table_ptr)->key_size) != 0)
    {
        SHR_EXIT();
    }

    second_entry->state = DNX_ROLLBACK_JOURNAL_ENTRY_STATE_INVALID;

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_entries_make_distinct(
    int unit,
    dnx_rollback_journal_t * journal,
    dnx_rollback_journal_entry_t * first_entry,
    dnx_rollback_journal_entry_t * second_entry)
{

    uint8 *first_metadata, *second_metadata;
    uint8 *first_payload, *second_payload;
    uint32 should_release_first_metadata = FALSE;
    uint32 should_release_first_payload = FALSE;
    uint32 should_release_second_metadata = FALSE;
    uint32 should_release_second_payload = FALSE;
    dnx_sw_state_journal_entry_t *first;
    dnx_sw_state_journal_entry_t *second;

    SHR_FUNC_INIT_VARS(unit);

    if (second_entry == NULL)
    {
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(dnx_rollback_journal_entry_get_merged_metadata_payload_ptr(unit, journal, first_entry,
                                                                               &first_metadata, &first_payload,
                                                                               &should_release_first_metadata,
                                                                               &should_release_first_payload));
    SHR_IF_ERR_EXIT(dnx_rollback_journal_entry_get_merged_metadata_payload_ptr(unit, journal, second_entry,
                                                                               &second_metadata, &second_payload,
                                                                               &should_release_second_metadata,
                                                                               &should_release_second_payload));

    first = (dnx_sw_state_journal_entry_t *) (first_metadata);
    second = (dnx_sw_state_journal_entry_t *) (second_metadata);

    if (first->entry_type != second->entry_type)
    {
        SHR_EXIT();
    }

    if (SW_JOURNAL_ENTRY_MEMCPY == first->entry_type)
    {
        dnx_sw_state_journal_MEMCPY_entries_make_distinct(unit,
                                                          first_entry,
                                                          first_metadata,
                                                          first_payload, second_entry, second_metadata, second_payload);
    }
    else
    {
        dnx_sw_state_journal_HTBL_entries_make_distinct(unit,
                                                        first_entry,
                                                        first_metadata,
                                                        first_payload, second_entry, second_metadata, second_payload);
    }

    SHR_EXIT();
exit:
    if (should_release_first_metadata)
        SHR_FREE(first_metadata);
    if (should_release_first_payload)
        SHR_FREE(first_payload);
    if (should_release_second_metadata)
        SHR_FREE(second_metadata);
    if (should_release_second_payload)
        SHR_FREE(second_payload);

    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_comparison_journal_print_difference(
    int unit,
    int size,
    uint8 *src,
    char *start_msg)
{
    int idx = 0;
    int string_size = 0;
    int start_msg_length = 0;

    int last_element_repeat_cnt = 0;

    int print_upper_bound = size;

    char *dest = NULL;

    char str_hex_value[DNX_SW_STATE_JOURNAL_BYTE_HEX_LEN] = { 0 };
    char str_repeats[DNX_SW_STATE_JOURNAL_LAST_ELEMENT_REPEAT_LEN] = { 0 };

    SHR_FUNC_INIT_VARS(unit);

    string_size = (DNX_SW_STATE_JOURNAL_BYTE_HEX_LEN * size) + 1;

    if (NULL != start_msg)
    {
        start_msg_length = sal_strnlen(start_msg, SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH);
        string_size += start_msg_length;
    }

    string_size += DNX_SW_STATE_JOURNAL_LAST_ELEMENT_REPEAT_LEN;

    DNX_SWSTATE_JOURNAL_ALLOC(unit, dest, char *,
                              string_size,
                              "comparison journal str alloc",
                              DNX_ROLLBACK_JOURNAL_TYPE_COMPARISON,
                              DNX_ROLLBACK_JOURNAL_SUBTYPE_SWSTATE);

    if (NULL == dest)
    {

        SHR_IF_ERR_EXIT_WITH_LOG(_SHR_E_INTERNAL,
                                 "swstate journal ERROR: could not allocate memory for string.\n%s%s%s", EMPTY, EMPTY,
                                 EMPTY);
    }
    sal_memset(dest, 0x0, string_size);

    if (NULL != start_msg)
    {
        sal_strncat_s(dest, start_msg, string_size);
    }

    for (idx = size - 1; idx >= 0; idx--)
    {
        if (src[size - 1] != src[idx])
        {
            break;
        }

        last_element_repeat_cnt++;

        if (last_element_repeat_cnt > 1)
        {
            print_upper_bound = idx + 1;
        }
    }

    for (idx = 0; idx < print_upper_bound; idx++)
    {
        sal_snprintf(str_hex_value, DNX_SW_STATE_JOURNAL_BYTE_HEX_LEN, "0x%02x ", src[idx]);
        sal_strncat_s(dest, str_hex_value, string_size);
    }

    if (print_upper_bound != size)
    {
        sal_snprintf(str_repeats, DNX_SW_STATE_JOURNAL_LAST_ELEMENT_REPEAT_LEN, "<last element repeats %04d times>",
                     last_element_repeat_cnt);
        sal_strncat_s(dest, str_repeats, string_size);
    }

    LOG_INFO(BSL_LOG_MODULE, (BSL_META("%s\n"), dest));

    sal_free(dest);
    dest = NULL;

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_comparison_journal_print_differences(
    int unit,
    uint8 *key,
    uint32 key_size,
    uint8 *data_before,
    uint8 *data_after,
    uint32 data_size,
    char *stamp)
{
    SHR_FUNC_INIT_VARS(unit);

    LOG_ERROR(BSL_LOG_MODULE,
              (BSL_META("\n################################################################################\n")));
    LOG_ERROR(BSL_LOG_MODULE,
              (BSL_META("Difference found in swstate, associated stamp is: %s\n%s%s"), stamp, EMPTY, EMPTY));

    if ((NULL != key) && (0 != key_size))
    {
        SHR_IF_ERR_EXIT(dnx_sw_state_comparison_journal_print_difference(unit, key_size, key, "Key: "));
    }

    SHR_IF_ERR_EXIT(dnx_sw_state_comparison_journal_print_difference(unit, data_size, data_before, "Data before: "));

    SHR_IF_ERR_EXIT(dnx_sw_state_comparison_journal_print_difference(unit, data_size, data_after, "Data after: "));

    LOG_ERROR(BSL_LOG_MODULE,
              (BSL_META("################################################################################\n")));
    SHR_IF_ERR_EXIT_NO_MSG(_SHR_E_INTERNAL);

exit:
    SHR_FUNC_EXIT;
}

static uint32
dnx_sw_state_journal_get_stamp_size(
    char *stamp)
{
    uint32 len = sal_strnlen(stamp, SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH);

    if (len > DNX_ROLLBACK_JOURNAL_MAX_STAMP_SIZE)
    {
        return DNX_ROLLBACK_JOURNAL_MAX_STAMP_SIZE;
    }

    return len;
}

static uint8
dnx_sw_state_journal_is_stamp_excluded(
    int unit,
    dnx_er_db_t * dnx_er_db,
    char *stamp,
    uint8 is_comparison)
{
    uint32 stamp_length = 0;
    uint32 idx_length = 0;

    int ii = 0;
    int nof_tables = 0;

    char comparison_perm_excluded[50][100] = { {0} };

    char rollback_perm_excluded[5][100] = { {0} };

    sal_snprintf(comparison_perm_excluded[0], sizeof(comparison_perm_excluded[0]),
                 "example[%d]->rollback_comparison_excluded", unit);

    sal_snprintf(comparison_perm_excluded[1], sizeof(comparison_perm_excluded[1]),
                 "dnx_field_tcam_access_sw[%d]->fg_params[10].prefix_value", unit);
    sal_snprintf(comparison_perm_excluded[2], sizeof(comparison_perm_excluded[2]),
                 "algo_bfd_db[%d]->bfd_your_discr_range", unit);
    sal_snprintf(comparison_perm_excluded[3], sizeof(comparison_perm_excluded[3]), "algo_bfd_db[%d]->bfd_oama_action",
                 unit);
    sal_snprintf(comparison_perm_excluded[4], sizeof(comparison_perm_excluded[4]), "algo_bfd_db[%d]->bfd_dip", unit);
    sal_snprintf(comparison_perm_excluded[5], sizeof(comparison_perm_excluded[5]), "dnx_crps_db[%d]", unit);
    sal_snprintf(comparison_perm_excluded[6], sizeof(comparison_perm_excluded[6]),
                 "algo_oam_db[%d]->oam_mpls_pwe_exp_ttl_profile", unit);
    sal_snprintf(comparison_perm_excluded[7], sizeof(comparison_perm_excluded[7]),
                 "algo_oam_db[%d]->oamp_itmh_pph_priority_profile", unit);
    sal_snprintf(comparison_perm_excluded[8], sizeof(comparison_perm_excluded[8]),
                 "algo_bfd_db[%d]->bfd_oamp_v1_tx_rate", unit);
    sal_snprintf(comparison_perm_excluded[9], sizeof(comparison_perm_excluded[9]), "algo_oam_db[%d]->oam_mep_profile",
                 unit);
    sal_snprintf(comparison_perm_excluded[10], sizeof(comparison_perm_excluded[10]),
                 "algo_oamp_db[%d]->oamp_2b_maid_full_mep_id", unit);
    sal_snprintf(comparison_perm_excluded[11], sizeof(comparison_perm_excluded[11]),
                 "algo_oamp_db[%d]->oamp_v1_mep_db_entry", unit);
    sal_snprintf(comparison_perm_excluded[12], sizeof(comparison_perm_excluded[12]), "algo_oam_db[%d]->oam_mep_profile",
                 unit);
    sal_snprintf(comparison_perm_excluded[13], sizeof(comparison_perm_excluded[13]),
                 "algo_bfd_db[%d]->bfd_oamp_v1_tx_rate", unit);
    sal_snprintf(comparison_perm_excluded[14], sizeof(comparison_perm_excluded[14]),
                 "algo_oamp_db[%d]->oamp_2b_maid_full_mep_id", unit);
    sal_snprintf(comparison_perm_excluded[15], sizeof(comparison_perm_excluded[15]),
                 "algo_oamp_db[%d]->oamp_full_tuples_mep_id[7]", unit);
    sal_snprintf(comparison_perm_excluded[16], sizeof(comparison_perm_excluded[16]), "algo_bfd_db[%d]->bfd_oamb_action",
                 unit);
    sal_snprintf(comparison_perm_excluded[17], sizeof(comparison_perm_excluded[17]),
                 "algo_oam_db[%d]->oam_trap_tcam_index", unit);
    sal_snprintf(comparison_perm_excluded[18], sizeof(comparison_perm_excluded[18]),
                 "algo_bfd_db[%d]->bfd_oamp_v1_ipv4_src_addr", unit);

    sal_snprintf(comparison_perm_excluded[19], sizeof(comparison_perm_excluded[19]), "dnx_algo_port_db[%d]->pp[0][47]",
                 unit);

    sal_snprintf(rollback_perm_excluded[0], sizeof(rollback_perm_excluded[0]),
                 "example[%d]->rollback_comparison_excluded", unit);
    sal_snprintf(rollback_perm_excluded[0], sizeof(rollback_perm_excluded[0]),
                 "example[%d]->rollback_comparison_excluded", unit);

    if (NULL == stamp)
    {
        return FALSE;
    }

    stamp_length = dnx_sw_state_journal_get_stamp_size(stamp);

    if (!is_comparison)
    {

        for (ii = 0; ii < DNX_SW_STATE_ROLLBACK_JOURNAL_TRANSACTION.excluded_stamps_count; ii++)
        {
            idx_length =
                dnx_sw_state_journal_get_stamp_size(DNX_SW_STATE_ROLLBACK_JOURNAL_TRANSACTION.excluded_stamps[ii]);

            if ((stamp_length == idx_length)
                && (sal_strncmp(DNX_SW_STATE_ROLLBACK_JOURNAL_TRANSACTION.excluded_stamps[ii], stamp, stamp_length) ==
                    0))
            {
                return TRUE;
            }
        }

        nof_tables = sizeof(rollback_perm_excluded) / sizeof(rollback_perm_excluded[0]);

        for (ii = 0; ii < nof_tables; ii++)
        {
            idx_length = dnx_sw_state_journal_get_stamp_size(rollback_perm_excluded[ii]);

            if ((stamp_length == idx_length) && (sal_strncmp(rollback_perm_excluded[ii], stamp, stamp_length) == 0))
            {
                return TRUE;
            }
        }
    }
    else
    {

        for (ii = 0; ii < DNX_SW_STATE_COMPARISON_JOURNAL_TRANSACTION.excluded_stamps_count; ii++)
        {
            idx_length =
                dnx_sw_state_journal_get_stamp_size(DNX_SW_STATE_COMPARISON_JOURNAL_TRANSACTION.excluded_stamps[ii]);
            if ((stamp_length == idx_length)
                && (sal_strncmp(DNX_SW_STATE_COMPARISON_JOURNAL_TRANSACTION.excluded_stamps[ii], stamp, stamp_length) ==
                    0))
            {
                return TRUE;
            }
        }

        nof_tables = sizeof(comparison_perm_excluded) / sizeof(comparison_perm_excluded[0]);

        for (ii = 0; ii < nof_tables; ii++)
        {
            idx_length = dnx_sw_state_journal_get_stamp_size(comparison_perm_excluded[ii]);

            if ((stamp_length == idx_length) && (sal_strncmp(comparison_perm_excluded[ii], stamp, stamp_length) == 0))
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}

static shr_error_e
dnx_sw_state_comparison_journal_roll_back_MEMCPY_entry_cb(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 *entry_raw,
    uint8 *payload,
    char *stamp)
{
    int compare_result = 0;
    uint8 *current_value_buffer = NULL;

    dnx_sw_state_journal_entry_t *entry = (dnx_sw_state_journal_entry_t *) (entry_raw);

    uint32 payload_size = entry->nof_elements * entry->element_size;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if (NULL == DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.memcpy_data.offset) || NULL == payload)

        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state comparison journal ERROR: invalid entry data detected.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    if (dnx_sw_state_journal_is_stamp_excluded(unit, dnx_er_db, stamp, TRUE))
    {
        SHR_EXIT();
    }

    DNX_SWSTATE_JOURNAL_ALLOC(unit, current_value_buffer, uint8 *,
                              payload_size,
                              "sw state comparison cur val buf",
                              DNX_ROLLBACK_JOURNAL_TYPE_COMPARISON,
                              DNX_ROLLBACK_JOURNAL_SUBTYPE_SWSTATE);

    if (NULL == current_value_buffer)
    {

        SHR_IF_ERR_EXIT_WITH_LOG(_SHR_E_INTERNAL,
                                 "sw state comparison journal ERROR: could not allocate buffer.\n%s%s%s", EMPTY, EMPTY,
                                 EMPTY);
    }

    sal_memset(current_value_buffer, 0x0, payload_size);

    DNX_SW_STATE_MEMREAD(unit,
                         current_value_buffer,
                         DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.memcpy_data.offset),
                         0,
                         payload_size, DNXC_SW_STATE_JOURNAL_ROLLING_BACK, "sw state comparison cur val buf memread");

    DNX_SW_STATE_MEMCMP(unit,
                        current_value_buffer,
                        payload,
                        0,
                        payload_size,
                        &compare_result, DNXC_SW_STATE_JOURNAL_ROLLING_BACK, "sw state comparison cur val buf memcmp");

    if (compare_result != 0)
    {
        SHR_IF_ERR_EXIT_NO_MSG(dnx_sw_state_comparison_journal_print_differences(unit,
                                                                                 NULL,
                                                                                 0,
                                                                                 payload,
                                                                                 current_value_buffer,
                                                                                 payload_size, stamp));
    }

    sal_free(current_value_buffer);
    current_value_buffer = NULL;
exit:
    if (NULL != current_value_buffer)
    {
        sal_free(current_value_buffer);
        current_value_buffer = NULL;
    }
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_comparison_journal_roll_back_HTBL_entry_cb(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 *entry_raw,
    uint8 *payload,
    char *stamp)
{
    sw_state_htbl_t hash_table = NULL;
    dnx_sw_state_journal_entry_t *entry = NULL;

    uint8 *key_section = NULL;
    uint8 *data_section = NULL;

    uint8 *data_buffer = NULL;

    uint8 found = 0;
    uint8 compare_result = FALSE;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_sw_state_journal_is_stamp_excluded(unit, dnx_er_db, stamp, TRUE))
    {
        SHR_EXIT();
    }

    entry = (dnx_sw_state_journal_entry_t *) (entry_raw);
    hash_table = (sw_state_htbl_t) DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.htbl_data.hash_table_offset);

    key_section = payload;
    data_section = payload + hash_table->key_size;

    DNX_SWSTATE_JOURNAL_ALLOC(unit, data_buffer, uint8 *,
                              hash_table->data_size,
                              "sw state comparison cur val buf",
                              DNX_ROLLBACK_JOURNAL_TYPE_COMPARISON,
                              DNX_ROLLBACK_JOURNAL_SUBTYPE_SWSTATE);

    if (NULL == data_buffer)
    {

        SHR_IF_ERR_EXIT_WITH_LOG(_SHR_E_INTERNAL,
                                 "sw state journal ERROR: Could not allocate memory for htbl data buffer.\n%s%s%s",
                                 EMPTY, EMPTY, EMPTY);
    }

    sal_memset(data_buffer, 0x0, hash_table->data_size);

    SHR_IF_ERR_EXIT(sw_state_hash_table_entry_lookup(unit,
                                                     entry->node_id, hash_table, key_section, data_buffer, &found));

    compare_result = (sal_memcmp(data_buffer, data_section, hash_table->data_size) == 0) ? TRUE : FALSE;

    if (!compare_result)
    {

        SHR_IF_ERR_EXIT_NO_MSG(dnx_sw_state_comparison_journal_print_differences(unit,
                                                                                 key_section,
                                                                                 hash_table->key_size,
                                                                                 data_section,
                                                                                 data_buffer,
                                                                                 hash_table->data_size, stamp));
    }

    sal_free(data_buffer);
    data_buffer = NULL;
exit:
    if (NULL != data_buffer)
    {
        sal_free(data_buffer);
        data_buffer = NULL;
    }
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_comparison_journal_roll_back_idx_HTBL_entry_cb(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 *entry_raw,
    uint8 *payload,
    char *stamp)
{
    sw_state_idx_htbl_t hash_table = NULL;
    dnx_sw_state_journal_entry_t *entry = NULL;

    uint8 *key_section = NULL;
    uint8 *data_section = NULL;
    uint32 data_size = sizeof(uint32);
    uint8 *data_buffer = NULL;

    uint8 found = 0;
    uint32 data_idx = 0;
    uint8 compare_result = FALSE;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_sw_state_journal_is_stamp_excluded(unit, dnx_er_db, stamp, TRUE))
    {
        SHR_EXIT();
    }

    entry = (dnx_sw_state_journal_entry_t *) (entry_raw);
    hash_table =
        (sw_state_idx_htbl_t) DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.htbl_data.hash_table_offset);

    key_section = payload;
    data_section = payload + hash_table->key_size;

    DNX_SWSTATE_JOURNAL_ALLOC(unit, data_buffer, uint8 *,
                              data_size,
                              "sw state comparison cur val buf",
                              DNX_ROLLBACK_JOURNAL_TYPE_COMPARISON,
                              DNX_ROLLBACK_JOURNAL_SUBTYPE_SWSTATE);

    if (NULL == data_buffer)
    {

        SHR_IF_ERR_EXIT_WITH_LOG(_SHR_E_INTERNAL,
                                 "sw state journal ERROR: Could not allocate memory for htbl data buffer.\n%s%s%s",
                                 EMPTY, EMPTY, EMPTY);
    }

    sal_memset(data_buffer, 0x0, data_size);

    SHR_IF_ERR_EXIT(sw_state_index_hash_table_entry_lookup(unit,
                                                           entry->node_id,
                                                           hash_table, key_section, data_buffer, &data_idx, &found));

    compare_result = (sal_memcmp(data_buffer, data_section, data_size) == 0) ? TRUE : FALSE;

    if (!compare_result)
    {

        SHR_IF_ERR_EXIT_NO_MSG(dnx_sw_state_comparison_journal_print_differences(unit,
                                                                                 key_section,
                                                                                 hash_table->key_size,
                                                                                 data_section,
                                                                                 data_buffer, data_size, stamp));
    }

    sal_free(data_buffer);
    data_buffer = NULL;
exit:
    if (NULL != data_buffer)
    {
        sal_free(data_buffer);
        data_buffer = NULL;
    }
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_comparison_journal_roll_back_RH_HTBL_entry_cb(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 *entry_raw,
    uint8 *payload,
    char *stamp)
{
    sw_state_htb_t hash_table = NULL;
    dnx_sw_state_journal_entry_t *entry = NULL;

    uint8 *key_section = NULL;
    uint8 *data_section = NULL;

    uint8 *data_buffer = NULL;

    uint32 *offset = NULL;
    uint8 compare_result = FALSE;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_sw_state_journal_is_stamp_excluded(unit, dnx_er_db, stamp, TRUE))
    {
        SHR_EXIT();
    }

    entry = (dnx_sw_state_journal_entry_t *) (entry_raw);
    hash_table = (sw_state_htb_t) DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.htbl_data.hash_table_offset);

    key_section = payload;
    data_section = payload + hash_table->key_size;

    DNX_SWSTATE_JOURNAL_ALLOC(unit, data_buffer, uint8 *,
                              hash_table->data_size,
                              "sw state comparison cur val buf",
                              DNX_ROLLBACK_JOURNAL_TYPE_COMPARISON,
                              DNX_ROLLBACK_JOURNAL_SUBTYPE_SWSTATE);

    if (NULL == data_buffer)
    {

        SHR_IF_ERR_EXIT_WITH_LOG(_SHR_E_INTERNAL,
                                 "sw state journal ERROR: Could not allocate memory for rh htbl data buffer.\n%s%s%s",
                                 EMPTY, EMPTY, EMPTY);
    }

    sal_memset(data_buffer, 0x0, hash_table->data_size);

    SHR_IF_ERR_EXIT_ELSE_SET_EXPECT(sw_state_htb_rh_find
                                    (unit, hash_table, entry->multi_head_idx, key_section, data_buffer, offset),
                                    _SHR_E_NOT_FOUND);
    if (SHR_GET_CURRENT_ERR() == _SHR_E_NOT_FOUND)
    {
        SHR_SET_CURRENT_ERR(_SHR_E_NONE);
    }

    compare_result = (sal_memcmp(data_buffer, data_section, hash_table->data_size) == 0) ? TRUE : FALSE;

    if (!compare_result)
    {

        SHR_IF_ERR_EXIT_NO_MSG(dnx_sw_state_comparison_journal_print_differences(unit,
                                                                                 key_section,
                                                                                 hash_table->key_size,
                                                                                 data_section,
                                                                                 data_buffer,
                                                                                 hash_table->data_size, stamp));
    }

    sal_free(data_buffer);
    data_buffer = NULL;
exit:
    if (NULL != data_buffer)
    {
        sal_free(data_buffer);
        data_buffer = NULL;
    }
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_comparison_journal_roll_back_entry_update_buffers_cb(
    int unit,
    uint8 *entry_raw,
    uint8 *entry_payload_raw,
    uint8 *traversed_raw,
    uint8 *traversed_payload_raw)
{
    int addr_diff = 0;
    uint32 entry_offset = 0;
    uint32 traversed_offset = 0;
    uint32 size = 0;

    dnx_sw_state_journal_entry_t *entry = (dnx_sw_state_journal_entry_t *) (entry_raw);
    dnx_sw_state_journal_entry_t *traversed = (dnx_sw_state_journal_entry_t *) (traversed_raw);

    uint32 entry_payload_size = entry->nof_elements * entry->element_size;
    uint32 traversed_payload_size = traversed->nof_elements * traversed->element_size;

    SHR_FUNC_INIT_VARS(unit);

    if ((DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.memcpy_data.offset) -
         (DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, traversed, data.memcpy_data.offset) + traversed_payload_size) >=
         0)
        || (DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, traversed, data.memcpy_data.offset) -
            (DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.memcpy_data.offset) + entry_payload_size)) >= 0)
    {
        return _SHR_E_NONE;
    }

    addr_diff = entry->data.memcpy_data.offset - traversed->data.memcpy_data.offset;

    if (addr_diff > 0)
    {
        traversed_offset = addr_diff;

        size = traversed_payload_size - traversed_offset;
        if (size > entry_payload_size)
        {
            size = entry_payload_size;
        }
    }
    else
    {

        entry_offset = -(addr_diff);

        size = entry_payload_size - entry_offset;
    }

    sal_memcpy(traversed_payload_raw + traversed_offset, entry_payload_raw + entry_offset, size);

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_free_entry_print_cb(
    int unit,
    uint8 *metadata,
    uint8 *payload)
{
    SHR_FUNC_INIT_VARS(unit);

    if (NULL == metadata)
    {

        SHR_IF_ERR_EXIT_WITH_LOG(_SHR_E_INTERNAL, "sw state journal ERROR: Invalid data to print.\n%s%s%s", EMPTY,
                                 EMPTY, EMPTY);
    }

    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META("******************************* SW STATE Journal *******************************\n")));
    LOG_INFO(BSL_LOG_MODULE, (BSL_META("Type: FREE\n")));
    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META("********************************************************************************\n\n")));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_alloc_entry_print_cb(
    int unit,
    uint8 *metadata,
    uint8 *payload)
{
    SHR_FUNC_INIT_VARS(unit);

    if (NULL == metadata)
    {

        SHR_IF_ERR_EXIT_WITH_LOG(_SHR_E_INTERNAL, "sw state journal ERROR: Invalid data to print.\n%s%s%s", EMPTY,
                                 EMPTY, EMPTY);
    }

    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META("******************************* SW STATE Journal *******************************\n")));
    LOG_INFO(BSL_LOG_MODULE, (BSL_META("Type: ALLOC\n")));
    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META("********************************************************************************\n\n")));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_memcpy_entry_print_cb(
    int unit,
    uint8 *entry_raw,
    uint8 *payload)
{
    dnx_sw_state_journal_entry_t *entry = (dnx_sw_state_journal_entry_t *) (entry_raw);

    uint32 payload_size = entry->nof_elements * entry->element_size;

    SHR_FUNC_INIT_VARS(unit);

    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META("******************************* SW STATE Journal *******************************\n")));

    LOG_INFO(BSL_LOG_MODULE, (BSL_META("Type: MEMCPY\n")));

    if (NULL == payload)
    {
        LOG_INFO(BSL_LOG_MODULE, (BSL_META("Data: NULL\n")));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_sw_state_comparison_journal_print_difference(unit, payload_size, payload, "Data: "));
    }

    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META("********************************************************************************\n\n")));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_comparison_htbl_entry_print_cb(
    int unit,
    uint8 *entry_raw,
    uint8 *payload)
{
    SHR_FUNC_INIT_VARS(unit);

    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META("******************************* SW STATE Journal *******************************\n")));
    LOG_INFO(BSL_LOG_MODULE, (BSL_META("Type: HTBL\n")));
    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META("********************************************************************************\n\n")));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_comparison_idx_htbl_entry_print_cb(
    int unit,
    uint8 *entry_raw,
    uint8 *payload)
{
    SHR_FUNC_INIT_VARS(unit);

    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META("******************************* SW STATE Journal *******************************\n")));
    LOG_INFO(BSL_LOG_MODULE, (BSL_META("Type: HTBL\n")));
    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META("********************************************************************************\n\n")));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_comparison_rh_htbl_entry_print_cb(
    int unit,
    uint8 *entry_raw,
    uint8 *payload)
{
    SHR_FUNC_INIT_VARS(unit);

    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META("******************************* SW STATE Journal *******************************\n")));
    LOG_INFO(BSL_LOG_MODULE, (BSL_META("Type: RH HTBL\n")));
    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META("********************************************************************************\n\n")));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_comparison_mutex_entry_print_cb(
    int unit,
    uint8 *entry_raw,
    uint8 *payload)
{
    dnx_sw_state_journal_entry_t entry;
    SHR_FUNC_INIT_VARS(unit);

    entry = *(dnx_sw_state_journal_entry_t *) entry_raw;

    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META("******************************* SW STATE Journal *******************************\n")));
    LOG_INFO(BSL_LOG_MODULE, (BSL_META("Type: MUTEX\n")));
    LOG_INFO(BSL_LOG_MODULE, (BSL_META("Type of operation: %d\n"), entry.entry_type));
    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META("********************************************************************************\n\n")));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_comparison_sem_entry_print_cb(
    int unit,
    uint8 *entry_raw,
    uint8 *payload)
{
    dnx_sw_state_journal_entry_t entry;
    SHR_FUNC_INIT_VARS(unit);

    entry = *(dnx_sw_state_journal_entry_t *) entry_raw;

    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META("******************************* SW STATE Journal *******************************\n")));
    LOG_INFO(BSL_LOG_MODULE, (BSL_META("Type: SEMAPHORE\n")));
    LOG_INFO(BSL_LOG_MODULE, (BSL_META("Type of operation: %d\n"), entry.entry_type));
    LOG_INFO(BSL_LOG_MODULE,
             (BSL_META("********************************************************************************\n\n")));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_insert(
    int unit,
    dnx_er_db_t * dnx_er_db,
    dnx_sw_state_journal_entry_t entry,
    uint8 *payload,
    dnx_rollback_journal_rollback_handler rollback_handler,
    dnx_rollback_journal_rollback_traverse_handler rollback_traverse_handler,
    dnx_rollback_journal_print_handler print_handler,
    uint8 is_er,
    uint8 is_cmp)
{
    SHR_FUNC_INIT_VARS(unit);

    if (is_er && (SW_JOURNAL_ENTRY_HTBL_ENTRY != entry.entry_type))
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_entry_new(unit,
                                                       dnx_er_db,
                                                       DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_ROLLBACK,
                                                       (uint8 *) (&entry),
                                                       sizeof(dnx_sw_state_journal_entry_t),
                                                       payload,
                                                       entry.nof_elements * entry.element_size,
                                                       DNX_ROLLBACK_JOURNAL_ENTRY_STATE_VALID,
                                                       rollback_handler, rollback_traverse_handler, print_handler));
    }

    if (is_cmp)
    {
        if (SW_JOURNAL_ENTRY_MEMCPY == entry.entry_type)
        {
            SHR_IF_ERR_EXIT(dnx_rollback_journal_entry_new(unit,
                                                           dnx_er_db,
                                                           DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON,
                                                           (uint8 *) (&entry),
                                                           sizeof(dnx_sw_state_journal_entry_t),
                                                           payload,
                                                           entry.nof_elements * entry.element_size,
                                                           DNX_ROLLBACK_JOURNAL_ENTRY_STATE_VALID,
                                                           &dnx_sw_state_comparison_journal_roll_back_MEMCPY_entry_cb,
                                                           &dnx_sw_state_comparison_journal_roll_back_entry_update_buffers_cb,
                                                           print_handler));
        }
        else if (SW_JOURNAL_ENTRY_HTBL_ENTRY == entry.entry_type)
        {
            SHR_IF_ERR_EXIT(dnx_rollback_journal_entry_new(unit,
                                                           dnx_er_db,
                                                           DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON,
                                                           (uint8 *) (&entry),
                                                           sizeof(dnx_sw_state_journal_entry_t),
                                                           payload,
                                                           entry.nof_elements * entry.element_size,
                                                           DNX_ROLLBACK_JOURNAL_ENTRY_STATE_VALID,
                                                           &dnx_sw_state_comparison_journal_roll_back_HTBL_entry_cb,
                                                           NULL, print_handler));
        }
        else if (SW_JOURNAL_ENTRY_INDEX_HTBL_ENTRY == entry.entry_type)
        {
            SHR_IF_ERR_EXIT(dnx_rollback_journal_entry_new(unit,
                                                           dnx_er_db,
                                                           DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON,
                                                           (uint8 *) (&entry),
                                                           sizeof(dnx_sw_state_journal_entry_t),
                                                           payload,
                                                           entry.nof_elements * entry.element_size,
                                                           DNX_ROLLBACK_JOURNAL_ENTRY_STATE_VALID,
                                                           &dnx_sw_state_comparison_journal_roll_back_idx_HTBL_entry_cb,
                                                           NULL, print_handler));
        }
        else if (SW_JOURNAL_ENTRY_RH_HTBL_ENTRY == entry.entry_type)
        {
            SHR_IF_ERR_EXIT(dnx_rollback_journal_entry_new(unit,
                                                           dnx_er_db,
                                                           DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON,
                                                           (uint8 *) (&entry),
                                                           sizeof(dnx_sw_state_journal_entry_t),
                                                           payload,
                                                           entry.nof_elements * entry.element_size,
                                                           DNX_ROLLBACK_JOURNAL_ENTRY_STATE_VALID,
                                                           &dnx_sw_state_comparison_journal_roll_back_RH_HTBL_entry_cb,
                                                           NULL, print_handler));
        }
    }

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_roll_back_update_entry_locations_cb(
    int unit,
    uint8 *entry_raw,
    uint8 *entry_payload_raw,
    uint8 *traversed_raw,
    uint8 *traversed_payload_raw)
{
    uint32 size = 0;
    uint8 *old_location = NULL;
    uint8 *new_location = NULL;
    uint8 *calculated_pointer = NULL;
    uint8 *calculated_alloc_data_location = NULL;
    uint8 **calculated_alloc_data_new_location = NULL;
    uint8 **calculated_free_data_new_location = NULL;

    dnx_sw_state_journal_entry_t *entry_free = (dnx_sw_state_journal_entry_t *) (entry_raw);
    dnx_sw_state_journal_entry_t *traversed = (dnx_sw_state_journal_entry_t *) (traversed_raw);

    SHR_FUNC_INIT_VARS(unit);

    old_location = DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry_free, data.free_data.location_offset);
    new_location = *(DNX_SWSTATE_JOURNAL_CALCULATE_DPOINTER(unit, entry_free, data.free_data.ptr_location_offset));

    size = entry_free->element_size * entry_free->nof_elements;

    switch (traversed->entry_type)
    {
        case SW_JOURNAL_ENTRY_MEMCPY:
            calculated_pointer = DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, traversed, data.memcpy_data.offset);
            DNX_SW_STATE_JOURNAL_UPDATE_ENTRY_ADDRESS(calculated_pointer, old_location, new_location, size);
            traversed->data.memcpy_data.offset =
                DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET(unit, traversed, calculated_pointer);
            break;
        case SW_JOURNAL_ENTRY_ALLOC:
            calculated_alloc_data_location =
                DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, traversed, data.alloc_data.location_offset);
            calculated_alloc_data_new_location =
                DNX_SWSTATE_JOURNAL_CALCULATE_DPOINTER(unit, traversed, data.alloc_data.ptr_location_offset);
            DNX_SW_STATE_JOURNAL_UPDATE_ENTRY_ADDRESS(calculated_alloc_data_location, old_location, new_location, size);
            DNX_SW_STATE_JOURNAL_UPDATE_ENTRY_PTR_TO_ADDRESS(calculated_alloc_data_new_location, old_location,
                                                             new_location, size);
            traversed->data.alloc_data.location_offset =
                DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET(unit, traversed, calculated_alloc_data_location);
            traversed->data.alloc_data.ptr_location_offset =
                DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET_FROM_DPTR(unit, traversed, calculated_alloc_data_new_location);
            break;
        case SW_JOURNAL_ENTRY_FREE:
            calculated_free_data_new_location =
                DNX_SWSTATE_JOURNAL_CALCULATE_DPOINTER(unit, traversed, data.free_data.ptr_location_offset);
            DNX_SW_STATE_JOURNAL_UPDATE_ENTRY_PTR_TO_ADDRESS(calculated_free_data_new_location, old_location,
                                                             new_location, size);
            traversed->data.alloc_data.ptr_location_offset =
                DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET_FROM_DPTR(unit, traversed, calculated_free_data_new_location);
            break;
        case SW_JOURNAL_ENTRY_MUTEX_CREATE:
            break;
        case SW_JOURNAL_ENTRY_MUTEX_DESTROY:
            break;
        case SW_JOURNAL_ENTRY_MUTEX_TAKE:
            break;
        case SW_JOURNAL_ENTRY_MUTEX_GIVE:
            break;
        case SW_JOURNAL_ENTRY_SEMAPHORE_CREATE:
            break;
        case SW_JOURNAL_ENTRY_SEMAPHORE_DESTROY:
            break;
        case SW_JOURNAL_ENTRY_SEMAPHORE_TAKE:
            break;
        case SW_JOURNAL_ENTRY_SEMAPHORE_GIVE:
            break;
        default:
            SHR_IF_ERR_EXIT_WITH_LOG(_SHR_E_INTERNAL, "sw state journal ERROR: Unknown entry type detected.\n%s%s%s",
                                     EMPTY, EMPTY, EMPTY);
    }

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_roll_back_FREE_entry(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 *entry_raw,
    uint8 *payload,
    char *stamp)
{
    dnx_sw_state_journal_entry_t *entry = (dnx_sw_state_journal_entry_t *) (entry_raw);

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if ((NULL == DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.free_data.location_offset))
            || (NULL == DNX_SWSTATE_JOURNAL_CALCULATE_DPOINTER(unit, entry, data.free_data.ptr_location_offset)))
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: invalid entry data detected.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    if (dnx_sw_state_journal_is_stamp_excluded(unit, dnx_er_db, stamp, FALSE))
    {
        SHR_EXIT();
    }

    DNX_SW_STATE_ALLOC_BASIC(unit,
                             entry->node_id,
                             DNX_SWSTATE_JOURNAL_CALCULATE_DPOINTER(unit, entry, data.free_data.ptr_location_offset),
                             entry->element_size,
                             entry->nof_elements,
                             DNXC_SW_STATE_JOURNAL_ROLLING_BACK, "sw state journal roll-back free entry");

    DNX_SW_STATE_MEMCPY_BASIC(unit,
                              entry->node_id,
                              *(DNX_SWSTATE_JOURNAL_CALCULATE_DPOINTER
                                (unit, entry, data.free_data.ptr_location_offset)), payload,
                              entry->element_size * entry->nof_elements, DNXC_SW_STATE_JOURNAL_ROLLING_BACK,
                              "sw state roll back free entry");

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_roll_back_ALLOC_entry(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 *entry_raw,
    uint8 *payload,
    char *stamp)
{
    dnx_sw_state_journal_entry_t *entry = (dnx_sw_state_journal_entry_t *) (entry_raw);

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if ((NULL == DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.alloc_data.location_offset))
            || (NULL == DNX_SWSTATE_JOURNAL_CALCULATE_DPOINTER(unit, entry, data.alloc_data.ptr_location_offset)))
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: invalid entry data detected.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    if (dnx_sw_state_journal_is_stamp_excluded(unit, dnx_er_db, stamp, FALSE))
    {
        SHR_EXIT();
    }

    DNX_SW_STATE_FREE_BASIC(unit,
                            entry->node_id,
                            DNX_SWSTATE_JOURNAL_CALCULATE_DPOINTER(unit, entry, data.alloc_data.ptr_location_offset),
                            DNXC_SW_STATE_JOURNAL_ROLLING_BACK, "journal rollback alloc entry");

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_roll_back_MEMCPY_entry(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 *entry_raw,
    uint8 *payload,
    char *stamp)
{
    dnx_sw_state_journal_entry_t *entry = (dnx_sw_state_journal_entry_t *) (entry_raw);

    uint32 payload_size = entry->nof_elements * entry->element_size;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if (NULL == DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.memcpy_data.offset) || NULL == payload)
        {
            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: invalid entry data detected.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    if (dnx_sw_state_journal_is_stamp_excluded(unit, dnx_er_db, stamp, FALSE))
    {
        SHR_EXIT();
    }
    DNX_SW_STATE_MEMCPY_BASIC(unit, entry->node_id,
                              DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.memcpy_data.offset), payload,
                              payload_size, DNXC_SW_STATE_JOURNAL_ROLLING_BACK, "sw state journal roll back memcpy");

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_roll_back_MUTEX_CREATE_entry(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 *entry_raw,
    uint8 *payload,
    char *stamp)
{
    dnx_sw_state_journal_entry_t *entry = (dnx_sw_state_journal_entry_t *) (entry_raw);
    uint32 node_id = entry->node_id;
    uint8 *mtx_ptr = NULL;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if (NULL == DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.mutex_create.mtx_offset))
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: invalid entry data detected.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    if (dnx_sw_state_journal_is_stamp_excluded(unit, dnx_er_db, stamp, FALSE))
    {
        SHR_EXIT();
    }

    mtx_ptr = DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.mutex_create.mtx_offset);
    SHR_IF_ERR_EXIT(dnxc_sw_state_dispatcher[unit][DNXC_SW_STATE_LAYOUT_GET_MODULE_ID(node_id)].mutex_destroy
                    (unit, node_id, (sw_state_mutex_t *) mtx_ptr, DNXC_SW_STATE_JOURNAL_ROLLING_BACK));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_roll_back_MUTEX_DESTROY_entry(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 *entry_raw,
    uint8 *payload,
    char *stamp)
{
    dnx_sw_state_journal_entry_t *entry = (dnx_sw_state_journal_entry_t *) (entry_raw);
    uint32 node_id = entry->node_id;
    uint8 *mtx_ptr = NULL;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if (NULL == DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.mutex_destroy.mtx_offset))
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: invalid entry data detected.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    if (dnx_sw_state_journal_is_stamp_excluded(unit, dnx_er_db, stamp, FALSE))
    {
        SHR_EXIT();
    }

    mtx_ptr = DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.mutex_destroy.mtx_offset);
    SHR_IF_ERR_EXIT(dnxc_sw_state_dispatcher[unit][DNXC_SW_STATE_LAYOUT_GET_MODULE_ID(node_id)].mutex_create
                    (unit, node_id, (sw_state_mutex_t *) mtx_ptr, "roll back created mutex",
                     DNXC_SW_STATE_JOURNAL_ROLLING_BACK));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_roll_back_MUTEX_TAKE_entry(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 *entry_raw,
    uint8 *payload,
    char *stamp)
{
    dnx_sw_state_journal_entry_t *entry = (dnx_sw_state_journal_entry_t *) (entry_raw);
    uint32 node_id = entry->node_id;
    uint8 *mtx_ptr = NULL;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if (NULL == DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.mutex_take.mtx_offset))
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: invalid entry data detected.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    if (dnx_sw_state_journal_is_stamp_excluded(unit, dnx_er_db, stamp, FALSE))
    {
        SHR_EXIT();
    }

    mtx_ptr = DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.mutex_take.mtx_offset);
    SHR_IF_ERR_EXIT(dnxc_sw_state_dispatcher[unit][DNXC_SW_STATE_LAYOUT_GET_MODULE_ID(node_id)].mutex_give
                    (unit, node_id, (sw_state_mutex_t *) mtx_ptr, DNXC_SW_STATE_JOURNAL_ROLLING_BACK));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_roll_back_MUTEX_GIVE_entry(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 *entry_raw,
    uint8 *payload,
    char *stamp)
{
    uint32 usec = DNX_SW_STATE_JOURNAL_MUTEX_DEFAULT_USEC;
    dnx_sw_state_journal_entry_t *entry = (dnx_sw_state_journal_entry_t *) (entry_raw);
    uint32 node_id = entry->node_id;
    sw_state_mutex_t *mtx_ptr = NULL;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if (NULL == DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.mutex_give.mtx_offset))
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: invalid entry data detected.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    if (dnx_sw_state_journal_is_stamp_excluded(unit, dnx_er_db, stamp, FALSE))
    {
        SHR_EXIT();
    }

    mtx_ptr = (sw_state_mutex_t *) (DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.mutex_give.mtx_offset));

    SHR_IF_ERR_EXIT(dnxc_sw_state_dispatcher[unit][DNXC_SW_STATE_LAYOUT_GET_MODULE_ID(node_id)].mutex_take
                    (unit, node_id, (sw_state_mutex_t *) mtx_ptr, usec, DNXC_SW_STATE_JOURNAL_ROLLING_BACK));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_roll_back_SEM_CREATE_entry(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 *entry_raw,
    uint8 *payload,
    char *stamp)
{
    dnx_sw_state_journal_entry_t *entry = (dnx_sw_state_journal_entry_t *) (entry_raw);
    uint32 node_id = entry->node_id;
    uint8 *sem_ptr = NULL;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if (NULL == DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.sem_create.sem_offset))
        {
            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: invalid entry data detected.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    if (dnx_sw_state_journal_is_stamp_excluded(unit, dnx_er_db, stamp, FALSE))
    {
        SHR_EXIT();
    }

    sem_ptr = DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.sem_create.sem_offset);
    SHR_IF_ERR_EXIT(dnxc_sw_state_dispatcher[unit][DNXC_SW_STATE_LAYOUT_GET_MODULE_ID(node_id)].sem_destroy
                    (unit, node_id, (sw_state_sem_t *) sem_ptr, DNXC_SW_STATE_JOURNAL_ROLLING_BACK));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_roll_back_SEM_DESTROY_entry(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 *entry_raw,
    uint8 *payload,
    char *stamp)
{
    dnx_sw_state_journal_entry_t *entry = (dnx_sw_state_journal_entry_t *) (entry_raw);
    uint32 node_id = entry->node_id;
    uint8 *sem_ptr = NULL;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if (NULL == DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.sem_destroy.sem_offset))
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: invalid entry data detected.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    if (dnx_sw_state_journal_is_stamp_excluded(unit, dnx_er_db, stamp, FALSE))
    {
        SHR_EXIT();
    }
    sem_ptr = DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.sem_destroy.sem_offset);
    SHR_IF_ERR_EXIT(dnxc_sw_state_dispatcher[unit][DNXC_SW_STATE_LAYOUT_GET_MODULE_ID(node_id)].sem_create
                    (unit, node_id, (sw_state_sem_t *) sem_ptr, entry->data.sem_destroy.is_binary,
                     entry->data.sem_destroy.initial_count, "roll back created semaphore",
                     DNXC_SW_STATE_JOURNAL_ROLLING_BACK));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_roll_back_SEM_TAKE_entry(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 *entry_raw,
    uint8 *payload,
    char *stamp)
{
    dnx_sw_state_journal_entry_t *entry = (dnx_sw_state_journal_entry_t *) (entry_raw);
    uint32 node_id = entry->node_id;
    uint8 *sem_ptr = NULL;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if (NULL == DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.sem_take.sem_offset))
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: invalid entry data detected.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    if (dnx_sw_state_journal_is_stamp_excluded(unit, dnx_er_db, stamp, FALSE))
    {
        SHR_EXIT();
    }

    sem_ptr = DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.sem_take.sem_offset);
    SHR_IF_ERR_EXIT(dnxc_sw_state_dispatcher[unit][DNXC_SW_STATE_LAYOUT_GET_MODULE_ID(node_id)].sem_give
                    (unit, node_id, (sw_state_sem_t *) sem_ptr, DNXC_SW_STATE_JOURNAL_ROLLING_BACK));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_sw_state_journal_roll_back_SEM_GIVE_entry(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 *entry_raw,
    uint8 *payload,
    char *stamp)
{
    uint32 usec = DNX_SW_STATE_JOURNAL_SEM_DEFAULT_USER;
    dnx_sw_state_journal_entry_t *entry = (dnx_sw_state_journal_entry_t *) (entry_raw);
    uint32 node_id = entry->node_id;
    sw_state_sem_t *sem_ptr = NULL;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if (NULL == DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.sem_give.sem_offset))
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: invalid entry data detected.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    if (dnx_sw_state_journal_is_stamp_excluded(unit, dnx_er_db, stamp, FALSE))
    {
        SHR_EXIT();
    }

    sem_ptr = (sw_state_sem_t *) (DNX_SWSTATE_JOURNAL_CALCULATE_POINTER(unit, entry, data.sem_give.sem_offset));

    SHR_IF_ERR_EXIT(dnxc_sw_state_dispatcher[unit][DNXC_SW_STATE_LAYOUT_GET_MODULE_ID(node_id)].sem_take
                    (unit, node_id, (sw_state_sem_t *) sem_ptr, usec, DNXC_SW_STATE_JOURNAL_ROLLING_BACK));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

uint8
dnx_sw_state_journal_is_done_init(
    int unit)
{
    return dnx_rollback_journal_is_done_init(unit);
}

shr_error_e
dnx_sw_state_journal_initialize(
    int unit,
    dnx_er_db_t * dnx_er_db,
    dnx_rollback_journal_cbs_t rollback_journal_cbs,
    dnx_sw_state_journal_access_cb access_cb,
    uint8 is_comparison)
{
    SHR_FUNC_INIT_VARS(unit);

    if (is_comparison)
    {

        SHR_IF_ERR_EXIT(dnx_rollback_journal_new(unit,
                                                 dnx_er_db,
                                                 TRUE,
                                                 DNX_ROLLBACK_JOURNAL_TYPE_COMPARISON,
                                                 DNX_ROLLBACK_JOURNAL_SUBTYPE_SWSTATE,
                                                 rollback_journal_cbs, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON));
        dnx_er_db->dnx_sw_state_manager->journals[DNX_SWSTATE_COMPARISON_JOURNAL_NUM].access_cb = access_cb;
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_new(unit,
                                                 dnx_er_db,
                                                 FALSE,
                                                 DNX_ROLLBACK_JOURNAL_TYPE_ROLLBACK,
                                                 DNX_ROLLBACK_JOURNAL_SUBTYPE_SWSTATE,
                                                 rollback_journal_cbs, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_ROLLBACK));
        dnx_er_db->dnx_sw_state_manager->journals[DNX_SWSTATE_ROLLBACK_JOURNAL_NUM].access_cb = access_cb;
    }

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_destroy(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 is_comparison)
{
    SHR_FUNC_INIT_VARS(unit);

    if (is_comparison)
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_destroy(unit, dnx_er_db, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_destroy(unit, dnx_er_db, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_ROLLBACK));
    }

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static inline shr_error_e
dnx_sw_state_journal_get_if_on(
    int unit,
    dnx_er_db_t ** dnx_er_db,
    uint8 *is_er,
    uint8 *is_cmp)
{
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_er_db_get_if_initialized(unit, dnx_er_db) != _SHR_E_NONE)
    {
        SHR_IF_ERR_EXIT_NO_MSG(_SHR_E_INTERNAL);
    }

    (*is_er) = dnx_rollback_journal_is_on(unit, *dnx_er_db, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_ROLLBACK);
    (*is_cmp) = dnx_rollback_journal_is_on(unit, *dnx_er_db, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON);
    if ((!(*is_er)) && (!(*is_cmp)))
    {
        SHR_IF_ERR_EXIT_NO_MSG(_SHR_E_INTERNAL);
    }

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_roll_back(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 only_head_rollback,
    uint8 is_comparison)
{
    SHR_FUNC_INIT_VARS(unit);

    if (is_comparison)
    {

        int distinct_rv = _SHR_E_NONE;
        int rollback_rv = _SHR_E_NONE;

        distinct_rv =
            dnx_rollback_journal_distinct(unit, dnx_er_db, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON,
                                          &dnx_sw_state_journal_entries_make_distinct);
        rollback_rv =
            dnx_rollback_journal_rollback(unit, dnx_er_db, FALSE, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON);

        SHR_IF_ERR_EXIT(DNX_ROLLBACK_JOURNAL_CMP_ERROR_PARSE(distinct_rv, rollback_rv));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_rollback
                        (unit, dnx_er_db, only_head_rollback, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_ROLLBACK));
    }

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_clear(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 is_comparison)
{
    SHR_FUNC_INIT_VARS(unit);

    if (is_comparison)
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_clear(unit, dnx_er_db, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_clear(unit, dnx_er_db, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_ROLLBACK));
    }

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_log_free(
    int unit,
    uint32 node_id,
    uint32 nof_elements,
    uint32 element_size,
    uint8 **ptr_location)
{
    uint8 is_er = FALSE;
    uint8 is_cmp = FALSE;
    dnx_er_db_t *dnx_er_db = NULL;
    dnx_sw_state_journal_entry_t entry;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_sw_state_journal_get_if_on(unit, &dnx_er_db, &is_er, &is_cmp) != _SHR_E_NONE)
    {
        SHR_EXIT();
    }

    DNX_SWSTATE_JOURNAL_ACCESS_NOTIFY(unit, dnx_er_db);

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if (NULL == ptr_location || NULL == *ptr_location)
        {
            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: NULL data attempted to be inserted to journal.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    entry.entry_type = SW_JOURNAL_ENTRY_FREE;
    entry.nof_elements = nof_elements;
    entry.element_size = element_size;
    entry.node_id = node_id;
    entry.data.free_data.location_offset = DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET(unit, (&entry), *ptr_location);
    entry.data.free_data.ptr_location_offset =
        DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET_FROM_DPTR(unit, (&entry), ptr_location);

    SHR_IF_ERR_EXIT(dnx_sw_state_journal_insert(unit,
                                                dnx_er_db,
                                                entry,
                                                *ptr_location,
                                                &dnx_sw_state_journal_roll_back_FREE_entry,
                                                &dnx_sw_state_journal_roll_back_update_entry_locations_cb,
                                                &dnx_sw_state_journal_free_entry_print_cb, is_er, is_cmp));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_log_alloc(
    int unit,
    uint32 node_id,
    uint8 **ptr_location)
{
    uint8 is_er = FALSE;
    uint8 is_cmp = FALSE;
    dnx_er_db_t *dnx_er_db = NULL;
    dnx_sw_state_journal_entry_t entry;

    SHR_FUNC_INIT_VARS(unit);

    if (!(SOC_UNIT_VALID(unit)))
    {
        return _SHR_E_NONE;
    }

    if (dnx_sw_state_journal_get_if_on(unit, &dnx_er_db, &is_er, &is_cmp) != _SHR_E_NONE)
    {
        SHR_EXIT();
    }

    DNX_SWSTATE_JOURNAL_ACCESS_NOTIFY(unit, dnx_er_db);

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if ((NULL == ptr_location) || (NULL == *ptr_location))
        {
            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: NULL data attempted to be inserted to journal.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    entry.entry_type = SW_JOURNAL_ENTRY_ALLOC;
    entry.nof_elements = 0;
    entry.element_size = 0;
    entry.node_id = node_id;
    entry.data.alloc_data.location_offset = DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET(unit, (&entry), *ptr_location);
    entry.data.alloc_data.ptr_location_offset =
        DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET_FROM_DPTR(unit, (&entry), ptr_location);

    SHR_IF_ERR_EXIT(dnx_sw_state_journal_insert(unit,
                                                dnx_er_db,
                                                entry,
                                                *ptr_location,
                                                &dnx_sw_state_journal_roll_back_ALLOC_entry,
                                                NULL, dnx_sw_state_journal_alloc_entry_print_cb, is_er, is_cmp));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_log_memcpy(
    int unit,
    uint32 node_id,
    uint32 size,
    uint8 *ptr)
{
    uint8 is_er = FALSE;
    uint8 is_cmp = FALSE;
    dnx_er_db_t *dnx_er_db = NULL;
    dnx_sw_state_journal_entry_t entry;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_sw_state_journal_get_if_on(unit, &dnx_er_db, &is_er, &is_cmp) != _SHR_E_NONE)
    {
        SHR_EXIT();
    }

    DNX_SWSTATE_JOURNAL_ACCESS_NOTIFY(unit, dnx_er_db);

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if (NULL == ptr)
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: NULL data attempted to be inserted to journal.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }

        if (0 == size)
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: data with size zero attempted to be inserted to journal.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    entry.entry_type = SW_JOURNAL_ENTRY_MEMCPY;
    entry.nof_elements = 1;
    entry.element_size = size;
    entry.node_id = node_id;
    entry.data.memcpy_data.offset = DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET(unit, (&entry), ptr);

    SHR_IF_ERR_EXIT(dnx_sw_state_journal_insert(unit,
                                                dnx_er_db,
                                                entry,
                                                ptr,
                                                &dnx_sw_state_journal_roll_back_MEMCPY_entry,
                                                NULL, dnx_sw_state_journal_memcpy_entry_print_cb, is_er, is_cmp));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_log_htbl(
    int unit,
    uint32 node_id,
    sw_state_htbl_t hash_table,
    SW_STATE_HASH_TABLE_KEY * const key)
{
    dnx_er_db_t *dnx_er_db = NULL;
    dnx_sw_state_journal_entry_t entry;

    uint8 *tmp_buff = NULL;
    uint32 tmp_buff_size = 0;

    uint8 *key_section = NULL;
    uint8 *data_section = NULL;

    uint8 found = 0;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_er_db_get_if_initialized(unit, &dnx_er_db) != _SHR_E_NONE)
    {
        SHR_EXIT();
    }

    dnx_sw_state_comparison_journal_tmp_suppress(unit, FALSE);

    DNX_SWSTATE_JOURNAL_ACCESS_NOTIFY(unit, dnx_er_db);

    if (!dnx_rollback_journal_is_on(unit, dnx_er_db, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON))
    {
        SHR_EXIT();
    }

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if (NULL == hash_table)
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: Invalid hash table specified for journal entry.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);

        }

        if (NULL == key)
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: Invalid hash table key specified for journal entry.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    tmp_buff_size = hash_table->key_size + hash_table->data_size;
    DNX_SWSTATE_JOURNAL_ALLOC(unit, tmp_buff, uint8 *,
                              tmp_buff_size,
                              "tmp_buff hash table swstate journal",
                              DNX_ROLLBACK_JOURNAL_TYPE_COMPARISON,
                              DNX_ROLLBACK_JOURNAL_SUBTYPE_SWSTATE);
    if (NULL == tmp_buff)
    {
        SHR_IF_ERR_EXIT_WITH_LOG(_SHR_E_INTERNAL,
                                 "sw state journal ERROR: Could not allocate memory for htbl entry buffer.\n%s%s%s",
                                 EMPTY, EMPTY, EMPTY);
    }
    sal_memset(tmp_buff, 0x0, tmp_buff_size);

    key_section = tmp_buff;
    data_section = tmp_buff + hash_table->key_size;

    sal_memcpy(key_section, key, hash_table->key_size);
    SHR_IF_ERR_EXIT(sw_state_hash_table_entry_lookup(unit, node_id, hash_table, key, data_section, &found));

    entry.entry_type = SW_JOURNAL_ENTRY_HTBL_ENTRY;
    entry.nof_elements = 1;
    entry.element_size = tmp_buff_size;
    entry.node_id = node_id;
    entry.data.htbl_data.hash_table_offset = DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET(unit, (&entry), (uint8 *) hash_table);

    SHR_IF_ERR_EXIT(dnx_sw_state_journal_insert(unit,
                                                dnx_er_db,
                                                entry,
                                                tmp_buff,
                                                NULL,
                                                NULL,
                                                &dnx_sw_state_journal_comparison_htbl_entry_print_cb, FALSE, TRUE));

exit:
    if (NULL != tmp_buff)
    {
        sal_free(tmp_buff);
        tmp_buff = NULL;
    }

    dnx_sw_state_comparison_journal_tmp_suppress(unit, TRUE);
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_log_idx_htbl(
    int unit,
    uint32 node_id,
    sw_state_idx_htbl_t hash_table,
    SW_STATE_INDEX_HASH_TABLE_KEY * const key)
{
    dnx_er_db_t *dnx_er_db = NULL;
    dnx_sw_state_journal_entry_t entry;

    uint8 *tmp_buff = NULL;
    uint32 tmp_buff_size = 0;

    uint8 *key_section = NULL;
    uint8 *data_section = NULL;

    uint8 found = 0;
    uint32 data_idx = 0;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_er_db_get_if_initialized(unit, &dnx_er_db) != _SHR_E_NONE)
    {
        SHR_EXIT();
    }

    dnx_sw_state_comparison_journal_tmp_suppress(unit, FALSE);

    DNX_SWSTATE_JOURNAL_ACCESS_NOTIFY(unit, dnx_er_db);

    if (!dnx_rollback_journal_is_on(unit, dnx_er_db, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON))
    {
        SHR_EXIT();
    }

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if (NULL == hash_table)
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: Invalid hash table specified for journal entry.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);

        }

        if (NULL == key)
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: Invalid hash table key specified for journal entry.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    tmp_buff_size = hash_table->key_size + sizeof(uint32);
    DNX_SWSTATE_JOURNAL_ALLOC(unit, tmp_buff, uint8 *,
                              tmp_buff_size,
                              "tmp_buff hash table swstate journal",
                              DNX_ROLLBACK_JOURNAL_TYPE_COMPARISON,
                              DNX_ROLLBACK_JOURNAL_SUBTYPE_SWSTATE);
    if (NULL == tmp_buff)
    {
        SHR_IF_ERR_EXIT_WITH_LOG(_SHR_E_INTERNAL,
                                 "sw state journal ERROR: Could not allocate memory for htbl entry buffer.\n%s%s%s",
                                 EMPTY, EMPTY, EMPTY);
    }
    sal_memset(tmp_buff, 0x0, tmp_buff_size);

    key_section = tmp_buff;
    data_section = tmp_buff + hash_table->key_size;

    sal_memcpy(key_section, key, hash_table->key_size);
    SHR_IF_ERR_EXIT(sw_state_index_hash_table_entry_lookup
                    (unit, node_id, hash_table, key, data_section, &data_idx, &found));

    entry.entry_type = SW_JOURNAL_ENTRY_INDEX_HTBL_ENTRY;
    entry.nof_elements = 1;
    entry.element_size = tmp_buff_size;
    entry.node_id = node_id;
    entry.data.htbl_data.hash_table_offset = DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET(unit, (&entry), (uint8 *) hash_table);

    SHR_IF_ERR_EXIT(dnx_sw_state_journal_insert(unit,
                                                dnx_er_db,
                                                entry,
                                                tmp_buff,
                                                NULL,
                                                NULL,
                                                &dnx_sw_state_journal_comparison_idx_htbl_entry_print_cb, FALSE, TRUE));

exit:
    if (NULL != tmp_buff)
    {
        sal_free(tmp_buff);
        tmp_buff = NULL;
    }

    dnx_sw_state_comparison_journal_tmp_suppress(unit, TRUE);
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_log_rh_htbl(
    int unit,
    uint32 node_id,
    sw_state_htb_t hash_table,
    uint8 table_idx,
    void *const key)
{
    dnx_er_db_t *dnx_er_db = NULL;
    dnx_sw_state_journal_entry_t entry;

    uint8 *tmp_buff = NULL;
    uint32 tmp_buff_size = 0;

    uint8 *key_section = NULL;
    uint8 *data_section = NULL;

    uint32 *offset = NULL;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_er_db_get_if_initialized(unit, &dnx_er_db) != _SHR_E_NONE)
    {
        SHR_EXIT();
    }

    dnx_sw_state_comparison_journal_tmp_suppress(unit, FALSE);

    DNX_SWSTATE_JOURNAL_ACCESS_NOTIFY(unit, dnx_er_db);

    if (!dnx_rollback_journal_is_on(unit, dnx_er_db, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON))
    {
        SHR_EXIT();
    }

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if (NULL == hash_table)
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: Invalid hash table specified for journal entry.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);

        }

        if (NULL == key)
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: Invalid hash table key specified for journal entry.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    tmp_buff_size = hash_table->key_size + hash_table->data_size;
    DNX_SWSTATE_JOURNAL_ALLOC(unit, tmp_buff, uint8 *,
                              tmp_buff_size,
                              "tmp_buff rh hash table swstate journal",
                              DNX_ROLLBACK_JOURNAL_TYPE_COMPARISON,
                              DNX_ROLLBACK_JOURNAL_SUBTYPE_SWSTATE);
    if (NULL == tmp_buff)
    {
        SHR_IF_ERR_EXIT_WITH_LOG(_SHR_E_INTERNAL,
                                 "sw state journal ERROR: Could not allocate memory for rh htbl entry buffer.\n%s%s%s",
                                 EMPTY, EMPTY, EMPTY);
    }
    sal_memset(tmp_buff, 0x0, tmp_buff_size);

    key_section = tmp_buff;
    data_section = tmp_buff + hash_table->key_size;

    sal_memcpy(key_section, (uint8 *) key, hash_table->key_size);

    SHR_IF_ERR_EXIT_ELSE_SET_EXPECT(sw_state_htb_rh_find(unit, hash_table, table_idx, key, data_section, offset),
                                    _SHR_E_NOT_FOUND);
    if (SHR_GET_CURRENT_ERR() == _SHR_E_NOT_FOUND)
    {
        SHR_SET_CURRENT_ERR(_SHR_E_NONE);
    }

    entry.entry_type = SW_JOURNAL_ENTRY_RH_HTBL_ENTRY;
    entry.nof_elements = 1;
    entry.element_size = tmp_buff_size;
    entry.node_id = node_id;
    entry.multi_head_idx = table_idx;
    entry.data.htbl_data.hash_table_offset = DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET(unit, (&entry), (uint8 *) hash_table);

    SHR_IF_ERR_EXIT(dnx_sw_state_journal_insert(unit,
                                                dnx_er_db,
                                                entry,
                                                tmp_buff,
                                                NULL,
                                                NULL,
                                                &dnx_sw_state_journal_comparison_rh_htbl_entry_print_cb, FALSE, TRUE));

exit:
    if (NULL != tmp_buff)
    {
        sal_free(tmp_buff);
        tmp_buff = NULL;
    }

    dnx_sw_state_comparison_journal_tmp_suppress(unit, TRUE);
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_mutex_create(
    int unit,
    uint32 node_id,
    sw_state_mutex_t * ptr_mtx)
{
    uint8 is_er = FALSE;
    uint8 is_cmp = FALSE;

    dnx_er_db_t *dnx_er_db = NULL;
    dnx_sw_state_journal_entry_t entry;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_sw_state_journal_get_if_on(unit, &dnx_er_db, &is_er, &is_cmp) != _SHR_E_NONE)
    {
        SHR_EXIT();
    }

    entry.entry_type = SW_JOURNAL_ENTRY_MUTEX_CREATE;
    entry.nof_elements = 0;
    entry.element_size = 0;
    entry.node_id = node_id;
    entry.data.mutex_create.mtx_offset = DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET(unit, (&entry), (uint8 *) ptr_mtx);

    SHR_IF_ERR_EXIT(dnx_sw_state_journal_insert(unit,
                                                dnx_er_db,
                                                entry,
                                                (uint8 *) (ptr_mtx),
                                                &dnx_sw_state_journal_roll_back_MUTEX_CREATE_entry,
                                                NULL,
                                                &dnx_sw_state_journal_comparison_mutex_entry_print_cb, is_er, is_cmp));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_mutex_destroy(
    int unit,
    uint32 node_id,
    sw_state_mutex_t * ptr_mtx)
{
    uint8 is_er = FALSE;
    uint8 is_cmp = FALSE;
    dnx_er_db_t *dnx_er_db = NULL;
    dnx_sw_state_journal_entry_t entry;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_sw_state_journal_get_if_on(unit, &dnx_er_db, &is_er, &is_cmp) != _SHR_E_NONE)
    {
        SHR_EXIT();
    }

    entry.entry_type = SW_JOURNAL_ENTRY_MUTEX_DESTROY;
    entry.nof_elements = 0;
    entry.element_size = 0;
    entry.node_id = node_id;
    entry.data.mutex_destroy.mtx_offset = DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET(unit, (&entry), (uint8 *) ptr_mtx);

    SHR_IF_ERR_EXIT(dnx_sw_state_journal_insert(unit,
                                                dnx_er_db,
                                                entry,
                                                (uint8 *) (ptr_mtx),
                                                &dnx_sw_state_journal_roll_back_MUTEX_DESTROY_entry,
                                                NULL,
                                                &dnx_sw_state_journal_comparison_mutex_entry_print_cb, is_er, is_cmp));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_mutex_take(
    int unit,
    uint32 node_id,
    sw_state_mutex_t * ptr_mtx,
    uint32 usec)
{
    uint8 is_er = FALSE;
    uint8 is_cmp = FALSE;
    dnx_er_db_t *dnx_er_db = NULL;
    dnx_sw_state_journal_entry_t entry;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_sw_state_journal_get_if_on(unit, &dnx_er_db, &is_er, &is_cmp) != _SHR_E_NONE)
    {
        SHR_EXIT();
    }

    entry.entry_type = SW_JOURNAL_ENTRY_MUTEX_TAKE;
    entry.nof_elements = 0;
    entry.element_size = 0;
    entry.node_id = node_id;
    entry.data.mutex_take.mtx_offset = DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET(unit, (&entry), (uint8 *) ptr_mtx);
    entry.data.mutex_take.usec = usec;

    SHR_IF_ERR_EXIT(dnx_sw_state_journal_insert(unit,
                                                dnx_er_db,
                                                entry,
                                                (uint8 *) (ptr_mtx),
                                                &dnx_sw_state_journal_roll_back_MUTEX_TAKE_entry,
                                                NULL,
                                                &dnx_sw_state_journal_comparison_mutex_entry_print_cb, is_er, is_cmp));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_sem_create(
    int unit,
    uint32 node_id,
    sw_state_sem_t * ptr_sem)
{
    uint8 is_er = FALSE;
    uint8 is_cmp = FALSE;
    dnx_er_db_t *dnx_er_db = NULL;
    dnx_sw_state_journal_entry_t entry;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_sw_state_journal_get_if_on(unit, &dnx_er_db, &is_er, &is_cmp) != _SHR_E_NONE)
    {
        SHR_EXIT();
    }

    entry.entry_type = SW_JOURNAL_ENTRY_SEMAPHORE_CREATE;
    entry.nof_elements = 0;
    entry.element_size = 0;
    entry.node_id = node_id;
    entry.data.sem_create.sem_offset = DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET(unit, (&entry), (uint8 *) ptr_sem);

    SHR_IF_ERR_EXIT(dnx_sw_state_journal_insert(unit,
                                                dnx_er_db,
                                                entry,
                                                (uint8 *) (ptr_sem),
                                                &dnx_sw_state_journal_roll_back_SEM_CREATE_entry,
                                                NULL,
                                                &dnx_sw_state_journal_comparison_sem_entry_print_cb, is_er, is_cmp));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_sem_destroy(
    int unit,
    uint32 node_id,
    sw_state_sem_t * ptr_sem,
    int is_binary,
    int initial_count)
{
    uint8 is_er = FALSE;
    uint8 is_cmp = FALSE;
    dnx_er_db_t *dnx_er_db = NULL;
    dnx_sw_state_journal_entry_t entry;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_sw_state_journal_get_if_on(unit, &dnx_er_db, &is_er, &is_cmp) != _SHR_E_NONE)
    {
        SHR_EXIT();
    }

    entry.entry_type = SW_JOURNAL_ENTRY_SEMAPHORE_DESTROY;
    entry.nof_elements = 0;
    entry.element_size = 0;
    entry.node_id = node_id;
    entry.data.sem_destroy.sem_offset = DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET(unit, (&entry), (uint8 *) ptr_sem);
    entry.data.sem_destroy.is_binary = is_binary;
    entry.data.sem_destroy.initial_count = initial_count;

    SHR_IF_ERR_EXIT(dnx_sw_state_journal_insert(unit,
                                                dnx_er_db,
                                                entry,
                                                (uint8 *) (ptr_sem),
                                                &dnx_sw_state_journal_roll_back_SEM_DESTROY_entry,
                                                NULL,
                                                &dnx_sw_state_journal_comparison_sem_entry_print_cb, is_er, is_cmp));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_sem_take(
    int unit,
    uint32 node_id,
    sw_state_sem_t * ptr_sem,
    uint32 usec)
{
    uint8 is_er = FALSE;
    uint8 is_cmp = FALSE;
    dnx_er_db_t *dnx_er_db = NULL;
    dnx_sw_state_journal_entry_t entry;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_sw_state_journal_get_if_on(unit, &dnx_er_db, &is_er, &is_cmp) != _SHR_E_NONE)
    {
        SHR_EXIT();
    }

    entry.entry_type = SW_JOURNAL_ENTRY_SEMAPHORE_TAKE;
    entry.nof_elements = 0;
    entry.element_size = 0;
    entry.node_id = node_id;
    entry.data.sem_take.sem_offset = DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET(unit, (&entry), (uint8 *) ptr_sem);
    entry.data.sem_take.usec = usec;

    SHR_IF_ERR_EXIT(dnx_sw_state_journal_insert(unit,
                                                dnx_er_db,
                                                entry,
                                                (uint8 *) (ptr_sem),
                                                &dnx_sw_state_journal_roll_back_SEM_TAKE_entry,
                                                NULL,
                                                &dnx_sw_state_journal_comparison_sem_entry_print_cb, is_er, is_cmp));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_mutex_give(
    int unit,
    uint32 node_id,
    sw_state_mutex_t * ptr_mtx)
{
    uint8 is_er = FALSE;
    uint8 is_cmp = FALSE;
    dnx_er_db_t *dnx_er_db = NULL;
    dnx_sw_state_journal_entry_t entry;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_sw_state_journal_get_if_on(unit, &dnx_er_db, &is_er, &is_cmp) != _SHR_E_NONE)
    {
        SHR_EXIT();
    }

    entry.entry_type = SW_JOURNAL_ENTRY_MUTEX_GIVE;
    entry.nof_elements = 0;
    entry.element_size = 0;
    entry.node_id = node_id;
    entry.data.mutex_give.mtx_offset = DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET(unit, (&entry), (uint8 *) ptr_mtx);

    SHR_IF_ERR_EXIT(dnx_sw_state_journal_insert(unit,
                                                dnx_er_db,
                                                entry,
                                                (uint8 *) (ptr_mtx),
                                                &dnx_sw_state_journal_roll_back_MUTEX_GIVE_entry,
                                                NULL,
                                                &dnx_sw_state_journal_comparison_mutex_entry_print_cb, is_er, is_cmp));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_sem_give(
    int unit,
    uint32 node_id,
    sw_state_sem_t * ptr_sem)
{
    uint8 is_er = FALSE;
    uint8 is_cmp = FALSE;
    dnx_er_db_t *dnx_er_db = NULL;
    dnx_sw_state_journal_entry_t entry;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_sw_state_journal_get_if_on(unit, &dnx_er_db, &is_er, &is_cmp) != _SHR_E_NONE)
    {
        SHR_EXIT();
    }

    entry.entry_type = SW_JOURNAL_ENTRY_SEMAPHORE_GIVE;
    entry.nof_elements = 0;
    entry.element_size = 0;
    entry.node_id = node_id;
    entry.data.sem_give.sem_offset = DNX_SWSTATE_JOURNAL_CALCULATE_OFFSET(unit, (&entry), (uint8 *) ptr_sem);

    SHR_IF_ERR_EXIT(dnx_sw_state_journal_insert(unit,
                                                dnx_er_db,
                                                entry,
                                                (uint8 *) (ptr_sem),
                                                &dnx_sw_state_journal_roll_back_SEM_GIVE_entry,
                                                NULL,
                                                &dnx_sw_state_journal_comparison_sem_entry_print_cb, is_er, is_cmp));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_get_head_seq_id(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 is_comparison,
    uint32 *seq_id)
{
    SHR_FUNC_INIT_VARS(unit);

    if (is_comparison)
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_get_head_seq_id
                        (unit, dnx_er_db, seq_id, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_get_head_seq_id
                        (unit, dnx_er_db, seq_id, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_ROLLBACK));
    }

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_entries_stamp(
    int unit,
    char *format,
    va_list args)
{
    dnx_er_db_t *dnx_er_db = NULL;
    char str_to_print[DNX_ROLLBACK_JOURNAL_MAX_STAMP_SIZE + 1] = { 0 };
    int size = 0;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_er_db_get_if_initialized(unit, &dnx_er_db) != _SHR_E_NONE)
    {
        SHR_EXIT();
    }

    size = dnx_sw_state_journal_get_stamp_size(format);

    sal_vsnprintf(str_to_print, size, format, args);

    if (dnx_rollback_journal_is_on(unit, dnx_er_db, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON))
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_entries_stamp
                        (unit, dnx_er_db, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON, str_to_print));
    }

    if (dnx_rollback_journal_is_on(unit, dnx_er_db, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_ROLLBACK))
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_entries_stamp
                        (unit, dnx_er_db, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_ROLLBACK, str_to_print));
    }

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

uint8
dnx_sw_state_journal_should_stamp(
    int unit)
{
    dnx_er_db_t *dnx_er_db = NULL;

    if (dnx_er_db_get_if_initialized(unit, &dnx_er_db) != _SHR_E_NONE)
    {
        return FALSE;
    }

    return dnx_rollback_journal_is_on(unit, dnx_er_db, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON);
}

shr_error_e
dnx_sw_state_journal_all_tmp_suppress_unsafe(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 is_disable)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_rollback_journal_disabled_counter_change
                    (unit, dnx_er_db, is_disable, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_ROLLBACK, TRUE));
    SHR_IF_ERR_EXIT(dnx_rollback_journal_disabled_counter_change
                    (unit, dnx_er_db, is_disable, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON, TRUE));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_comparison_journal_tmp_suppress(
    int unit,
    uint8 is_disable)
{
    dnx_er_db_t *dnx_er_db = NULL;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_er_db_get_if_initialized(unit, &dnx_er_db) != _SHR_E_NONE)
    {
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(dnx_rollback_journal_disabled_counter_change
                    (unit, dnx_er_db, is_disable, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON, FALSE));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_exclude_by_stamp(
    int unit,
    dnx_er_db_t * dnx_er_db,
    char *stamp,
    uint8 is_comparison)
{
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_err_recovery_is_validation_enabled(unit))
    {
        if (!is_comparison)
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: rollback journal exclusion is not supported.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }

        if (!dnx_rollback_journal_is_on(unit, dnx_er_db, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON))
        {
            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: comparison journal exclusions are done only if the comparison journal is on.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
        if (DNX_SW_STATE_COMPARISON_JOURNAL_TRANSACTION.excluded_stamps_count + 1 >=
            DNX_SW_STATE_JOURNAL_EXCLUDED_STAMPS_MAX_NOF)
        {

            DNX_ROLLBACK_JOURNAL_IF_ERR_ASSERT_WITH_LOG(_SHR_E_INTERNAL,
                                                        "sw state journal ERROR: comparison journal table exclusions exceed the maximum number of allowed.\n%s%s%s",
                                                        EMPTY, EMPTY, EMPTY);
        }
    }

    sal_strncpy_s(DNX_SW_STATE_COMPARISON_JOURNAL_TRANSACTION.excluded_stamps
                  [DNX_SW_STATE_COMPARISON_JOURNAL_TRANSACTION.excluded_stamps_count], stamp,
                  DNX_SW_STATE_JOURNAL_MAX_STAMP_LENGTH);
    DNX_SW_STATE_COMPARISON_JOURNAL_TRANSACTION.excluded_stamps_count++;

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_exclude_clear(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 is_comparison)
{
    SHR_FUNC_INIT_VARS(unit);

    if (!is_comparison)
    {

        SHR_IF_ERR_EXIT_WITH_LOG(_SHR_E_INTERNAL,
                                 "sw state journal ERROR: rollback journal exclusion clear is not supported.\n%s%s%s",
                                 EMPTY, EMPTY, EMPTY);
    }

    for (int stamp_idx = 0; stamp_idx < DNX_SW_STATE_COMPARISON_JOURNAL_TRANSACTION.excluded_stamps_count; stamp_idx++)
    {
        sal_memset(DNX_SW_STATE_COMPARISON_JOURNAL_TRANSACTION.excluded_stamps[stamp_idx], 0,
                   DNX_SW_STATE_JOURNAL_MAX_STAMP_LENGTH);
    }
    DNX_SW_STATE_COMPARISON_JOURNAL_TRANSACTION.excluded_stamps_count = 0;

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_print(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 is_comparison)
{
    SHR_FUNC_INIT_VARS(unit);

    if (!is_comparison)
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_print(unit, dnx_er_db, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_ROLLBACK));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_print(unit, dnx_er_db, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON));
    }

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_sw_state_journal_logger_state_change(
    int unit,
    dnx_er_db_t * dnx_er_db,
    uint8 is_comparison)
{
    SHR_FUNC_INIT_VARS(unit);

    if (!is_comparison)
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_logger_state_change_by_type
                        (unit, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_ROLLBACK));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_rollback_journal_logger_state_change_by_type
                        (unit, DNX_ER_DB_JOURNAL_HANDLE_SW_STATE_COMPARISON));
    }

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

#undef _ERR_MSG_MODULE_NAME


/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_FLDPROCDNX

#include <soc/dnx/field/tcam/field_tcam.h>

#include <soc/sand/shrextend/shrextend_debug.h>
#include <bcm_int/dnx/cmn/dnxcmn.h>

#include <soc/dnx/field/tcam/tcam_bank_manager.h>
#include <soc/dnx/field/tcam/tcam_location_algo.h>
#include <soc/dnx/swstate/auto_generated/access/dnx_field_tcam_access_access.h>
#include <soc/dnx/swstate/auto_generated/access/dnx_field_tcam_access_mapper_access.h>
#include <soc/dnx/swstate/auto_generated/access/dnx_field_tcam_manager_access.h>
#include <soc/dnx/swstate/auto_generated/access/dnx_field_tcam_bank_access.h>
#include <soc/dnx/swstate/auto_generated/access/dnx_field_tcam_location_access.h>
#include <soc/dnx/swstate/auto_generated/access/dnx_field_tcam_access_profile_access.h>
#include <soc/dnx/swstate/auto_generated/access/dnx_field_tcam_prefix_access.h>
#include <soc/dnx/swstate/auto_generated/access/dnx_field_tcam_cache_access.h>
#include <soc/dnx/swstate/auto_generated/access/dnx_field_tcam_hit_indication_access.h>

#include <soc/dnx/swstate/auto_generated/types/dnx_field_tcam_location_types.h>

#include <soc/dnx/dnx_data/auto_generated/dnx_data_max_field.h>
#include <shared/utilex/utilex_framework.h>

static shr_error_e
dnx_field_tcam_access_mapper_sw_state_init(
    int unit)
{
    int bank_id;
    int core;
    int bank_offset;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_field_tcam_access_mapper_sw.init(unit));

    SHR_IF_ERR_EXIT(dnx_field_tcam_access_mapper_sw.key_2_location_hash.alloc(unit));

    DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core)
    {
        for (bank_id = 0; bank_id < dnx_data_field.tcam.nof_banks_get(unit); bank_id++)
        {
            SHR_IF_ERR_EXIT(dnx_field_tcam_access_mapper_sw.key_2_location_hash.
                            head.alloc(unit, core, bank_id, FIELD_TCAM_BANK_NOF_ENTRIES(bank_id)));
            SHR_IF_ERR_EXIT(dnx_field_tcam_access_mapper_sw.key_2_location_hash.
                            next.alloc(unit, core, bank_id, FIELD_TCAM_BANK_NOF_ENTRIES(bank_id)));

            for (bank_offset = 0; bank_offset < FIELD_TCAM_BANK_NOF_ENTRIES(bank_id); bank_offset++)
            {
                SHR_IF_ERR_EXIT(dnx_field_tcam_access_mapper_sw.key_2_location_hash.
                                head.set(unit, core, bank_id, bank_offset, DNX_FIELD_TCAM_ACCESS_HASH_NULL));
                SHR_IF_ERR_EXIT(dnx_field_tcam_access_mapper_sw.key_2_location_hash.
                                next.set(unit, core, bank_id, bank_offset, DNX_FIELD_TCAM_ACCESS_HASH_NULL));
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_field_tcam_access_sw_state_init(
    int unit)
{
    sw_state_htbl_init_info_t hash_init;
    int core;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_field_tcam_access_sw.init(unit));
    SHR_IF_ERR_EXIT(dnx_field_tcam_access_sw.fg_params.alloc(unit));
    SHR_IF_ERR_EXIT(dnx_field_tcam_access_sw.fg_prefix_per_core.alloc(unit));
    SHR_IF_ERR_EXIT(dnx_field_tcam_access_sw.entry_location_hash.alloc(unit));
    SHR_IF_ERR_EXIT(dnx_field_tcam_access_sw.valid_bmp.alloc(unit));
    SHR_IF_ERR_EXIT(dnx_field_tcam_access_sw.entry_in_use_bmp.alloc(unit));

    sal_memset(&hash_init, 0, sizeof(hash_init));
    hash_init.max_nof_elements = hash_init.expected_nof_elements =
        dnx_data_field.tcam.nof_big_banks_get(unit) * dnx_data_field.tcam.nof_big_bank_lines_get(unit) +
        dnx_data_field.tcam.nof_small_banks_get(unit) * dnx_data_field.tcam.nof_big_bank_lines_get(unit);

    DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core)
    {
        SHR_IF_ERR_EXIT(dnx_field_tcam_access_sw.valid_bmp.v_bit.alloc_bitmap(unit, core));
        SHR_IF_ERR_EXIT(dnx_field_tcam_access_sw.entry_in_use_bmp.v_bit.alloc_bitmap(unit, core));
        SHR_IF_ERR_EXIT(dnx_field_tcam_access_sw.entry_location_hash.create(unit, core, &hash_init));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_field_tcam_manager_sw_state_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_field_tcam_manager_sw.init(unit));
    SHR_IF_ERR_EXIT(dnx_field_tcam_manager_sw.tcam_handlers.alloc(unit));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_field_tcam_bank_sw_state_init(
    int unit)
{
    int bank_index;
    sw_state_ll_init_info_t init_info;
    int core;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&init_info, 0, sizeof(init_info));
    init_info.max_nof_elements = dnx_data_field.tcam.nof_tcam_handlers_get(unit);
    init_info.expected_nof_elements = dnx_data_field.tcam.nof_tcam_handlers_get(unit);

    SHR_IF_ERR_EXIT(dnx_field_tcam_bank_sw.init(unit));
    SHR_IF_ERR_EXIT(dnx_field_tcam_bank_sw.tcam_banks.alloc(unit));

    for (bank_index = 0; bank_index < dnx_data_field.tcam.nof_banks_get(unit); bank_index++)
    {
        SHR_IF_ERR_EXIT(dnx_field_tcam_bank_sw.tcam_banks.
                        nof_free_entries.alloc(unit, bank_index, dnx_data_device.general.nof_cores_get(unit),
                                               DNX_FIELD_TCAM_ENTRY_SIZE_COUNT));
        SHR_IF_ERR_EXIT(dnx_field_tcam_bank_sw.tcam_banks.active_handlers_id.alloc(unit, bank_index));
        SHR_IF_ERR_EXIT(dnx_field_tcam_bank_sw.tcam_banks.owner_stage.alloc(unit, bank_index));
        DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core)
        {
            uint32 max_nof_half_entries;
            uint32 max_nof_entries;
            if (bank_index < dnx_data_field.tcam.nof_big_banks_get(unit))
            {
                max_nof_half_entries = dnx_data_field.tcam.nof_big_bank_lines_get(unit);
            }
            else
            {
                max_nof_half_entries = dnx_data_field.tcam.nof_small_bank_lines_get(unit);
            }
            SHR_IF_ERR_EXIT(dnx_field_tcam_bank_sw.tcam_banks.
                            nof_free_entries.set(unit, bank_index, core, DNX_FIELD_TCAM_ENTRY_SIZE_HALF,
                                                 max_nof_half_entries));

            max_nof_entries = max_nof_half_entries / 2;
            SHR_IF_ERR_EXIT(dnx_field_tcam_bank_sw.tcam_banks.
                            nof_free_entries.set(unit, bank_index, core, DNX_FIELD_TCAM_ENTRY_SIZE_SINGLE,
                                                 max_nof_entries));

            if (bank_index % 2)
            {
                max_nof_entries = 0;
            }
            SHR_IF_ERR_EXIT(dnx_field_tcam_bank_sw.tcam_banks.
                            nof_free_entries.set(unit, bank_index, core, DNX_FIELD_TCAM_ENTRY_SIZE_DOUBLE,
                                                 max_nof_entries));

            dnx_field_tcam_bank_sw.tcam_banks.active_handlers_id.create_empty(unit, bank_index, core, &init_info);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_field_tcam_location_sw_state_handler_info_init(
    int unit,
    uint32 handler_id)
{
    int core;
    sw_state_occ_bitmap_init_info_t bmp_init_info;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_field_tcam_location_sw.tcam_handlers_info.prio_list_first_iter.alloc(unit, handler_id));
    SHR_IF_ERR_EXIT(dnx_field_tcam_location_sw.tcam_handlers_info.prio_list_last_iter.alloc(unit, handler_id));
    SHR_IF_ERR_EXIT(dnx_field_tcam_location_sw.tcam_handlers_info.entries_occupation_bitmap.alloc(unit, handler_id));

    DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core)
    {

        SHR_IF_ERR_EXIT(sw_state_occ_bm_init_info_clear(&bmp_init_info));
        bmp_init_info.size = dnx_data_field.tcam.tcam_banks_size_get(unit);

        SHR_IF_ERR_EXIT(dnx_field_tcam_location_sw.tcam_handlers_info.
                        entries_occupation_bitmap.create(unit, handler_id, core, &bmp_init_info));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_field_tcam_location_sw_state_init(
    int unit)
{
    uint32 handler_index;
    sw_state_occ_bitmap_init_info_t bmp_init_info;
    int core;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_field_tcam_location_sw.init(unit));
    SHR_IF_ERR_EXIT(dnx_field_tcam_location_sw.tcam_handlers_info.alloc(unit));

    for (handler_index = 0; handler_index < dnx_data_field.tcam.nof_tcam_handlers_get(unit); handler_index++)
    {

        SHR_IF_ERR_EXIT(dnx_field_tcam_location_sw_state_handler_info_init(unit, handler_index));
    }

    SHR_IF_ERR_EXIT(dnx_field_tcam_location_priorities_range_init(unit));

    SHR_IF_ERR_EXIT(sw_state_occ_bm_init_info_clear(&bmp_init_info));
    bmp_init_info.size = dnx_data_field.tcam.tcam_banks_size_get(unit);
    SHR_IF_ERR_EXIT(dnx_field_tcam_location_sw.tcam_banks_occupation_bitmap.alloc(unit));
    DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core)
    {
        SHR_IF_ERR_EXIT(dnx_field_tcam_location_sw.tcam_banks_occupation_bitmap.create(unit, core, &bmp_init_info));
        SHR_IF_ERR_EXIT(dnx_field_tcam_location_sw.location_priority_arr.alloc(unit, core));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_field_tcam_access_profile_sw_state_init(
    int unit)
{
    int access_profile_index;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_field_tcam_access_profile_sw.init(unit));
    SHR_IF_ERR_EXIT(dnx_field_tcam_access_profile_sw.access_profiles.alloc(unit));
    for (access_profile_index = 0; access_profile_index < dnx_data_field.tcam.nof_access_profiles_get(unit);
         access_profile_index++)
    {
        SHR_IF_ERR_EXIT(dnx_field_tcam_access_profile_sw.access_profiles.
                        bank_ids_bmp.alloc(unit, access_profile_index));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_field_tcam_prefix_sw_state_init(
    int unit)
{
    int bank_index;
    bcm_core_t core_iter;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_field_tcam_prefix_sw.init(unit));

    SHR_IF_ERR_EXIT(dnx_field_tcam_prefix_sw.banks_prefix.alloc(unit));

    for (bank_index = 0; bank_index < dnx_data_field.tcam.nof_banks_get(unit); bank_index++)
    {
        SHR_IF_ERR_EXIT(dnx_field_tcam_prefix_sw.banks_prefix.core_prefix_map.alloc(unit, bank_index));
        DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core_iter)
        {
            SHR_IF_ERR_EXIT(dnx_field_tcam_prefix_sw.banks_prefix.core_prefix_map.
                            prefix_handler_map.alloc(unit, bank_index, core_iter));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_field_tcam_shadow_sw_state_init(
    int unit)
{
    int bank_index;
    int core;
    SHR_FUNC_INIT_VARS(unit);

    if (DNX_FIELD_TCAM_SHADOW_KEEP)
    {
        SHR_IF_ERR_EXIT(dnx_field_tcam_cache_shadow.init(unit));

        SHR_IF_ERR_EXIT(dnx_field_tcam_cache_shadow.tcam_bank.alloc(unit, dnx_data_field.tcam.nof_banks_get(unit)));
        SHR_IF_ERR_EXIT(dnx_field_tcam_cache_shadow.
                        payload_table.alloc(unit, dnx_data_field.tcam.nof_payload_tables_get(unit)));

        DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core)
        {
            for (bank_index = 0; bank_index < dnx_data_field.tcam.nof_banks_get(unit); bank_index++)
            {
                SHR_IF_ERR_EXIT(dnx_field_tcam_cache_shadow.tcam_bank.
                                entry_key.alloc(unit, core, bank_index, FIELD_TCAM_BANK_NOF_ENTRIES(bank_index)));

                SHR_IF_ERR_EXIT(dnx_field_tcam_cache_shadow.payload_table.
                                entry_payload.alloc(unit, core, bank_index * 2,
                                                    (FIELD_TCAM_BANK_NOF_ENTRIES(bank_index) / 2)));
                SHR_IF_ERR_EXIT(dnx_field_tcam_cache_shadow.payload_table.
                                entry_payload.alloc(unit, core, bank_index * 2 + 1,
                                                    (FIELD_TCAM_BANK_NOF_ENTRIES(bank_index) / 2)));
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_field_tcam_hit_indication_sw_state_init(
    int unit)
{
    int sram_index;
    int nof_big_banks_sram_indexes;
    int nof_small_banks_sram_indexes;

    SHR_FUNC_INIT_VARS(unit);

    nof_big_banks_sram_indexes =
        dnx_data_field.tcam.nof_big_banks_get(unit) * dnx_data_field.tcam.action_width_selector_size_get(unit);
    nof_small_banks_sram_indexes =
        dnx_data_field.tcam.nof_small_banks_get(unit) * dnx_data_field.tcam.action_width_selector_size_get(unit);

    SHR_IF_ERR_EXIT(dnx_field_tcam_hit_indication.init(unit));
    SHR_IF_ERR_EXIT(dnx_field_tcam_hit_indication.tcam_action_hit_indication.alloc(unit));
    SHR_IF_ERR_EXIT(dnx_field_tcam_hit_indication.tcam_action_hit_indication_small.alloc(unit));

    for (sram_index = 0; sram_index < nof_big_banks_sram_indexes; sram_index++)
    {
        SHR_IF_ERR_EXIT(dnx_field_tcam_hit_indication.tcam_action_hit_indication.bank_line_id.alloc(unit, sram_index));
    }

    for (sram_index = 0; sram_index < nof_small_banks_sram_indexes; sram_index++)
    {
        SHR_IF_ERR_EXIT(dnx_field_tcam_hit_indication.tcam_action_hit_indication_small.
                        bank_line_id.alloc(unit, sram_index));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_field_tcam_sw_state_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_field_tcam_access_sw_state_init(unit));

    SHR_IF_ERR_EXIT(dnx_field_tcam_access_mapper_sw_state_init(unit));

    SHR_IF_ERR_EXIT(dnx_field_tcam_manager_sw_state_init(unit));

    SHR_IF_ERR_EXIT(dnx_field_tcam_bank_sw_state_init(unit));

    SHR_IF_ERR_EXIT(dnx_field_tcam_location_sw_state_init(unit));

    SHR_IF_ERR_EXIT(dnx_field_tcam_access_profile_sw_state_init(unit));

    SHR_IF_ERR_EXIT(dnx_field_tcam_prefix_sw_state_init(unit));

    SHR_IF_ERR_EXIT(dnx_field_tcam_shadow_sw_state_init(unit));

    if (dnx_data_field.features.hitbit_volatile_get(unit))
    {
        SHR_IF_ERR_EXIT(dnx_field_tcam_hit_indication_sw_state_init(unit));
    }

exit:
    SHR_FUNC_EXIT;
}

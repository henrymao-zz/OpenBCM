/** \file crps_engine.c
 * 
 *
 *  crps module gather all functionality that related to the counter/statisitc processor driver for DNX.
 *  crps engine.c gather the engine configuration functionality.
 *  It is internal crps file . (do not have interfaces with other modules)
 */

/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_CNT

/*
 * Include files.
 * {
 */
#include <soc/sand/shrextend/shrextend_debug.h>
#include <shared/utilex/utilex_bitstream.h>
#include <soc/dnx/dbal/dbal.h>
#include <bcm/types.h>
#include <bcm/error.h>
#include <bcm/stat.h>
#include "crps_mgmt_internal.h"
#include "crps_engine.h"
#include <soc/dnx/dnx_data/auto_generated/dnx_data_device.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_crps.h>
#include <include/shared/bitop.h>
#include <bcm_int/dnx/stat/crps/crps_mgmt.h>
#include <bcm_int/dnx/stat/crps/crps_src_interface.h>

/*
 * }
 */

/*
 * MACROs
 * {
 */

/*
 * }
 */

/** see .h file */

shr_error_e
dnx_crps_engine_base_offset_hw_set(
    int unit,
    bcm_stat_engine_t * engine_p,
    uint32 set_val)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Set only the first set */
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_CRPS_ENGINE_CFG, &entry_handle_id));
    }

    /** Setting key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_ID, engine_p->engine_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, engine_p->core_id);

    /** Setting value fields */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_ADDRESS_BASE_NORMALIZE, INST_SINGLE,
                                 set_val);

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_engine_type_hw_set(
    int unit,
    bcm_stat_engine_t * engine,
    int *valid,
    uint32 *offset)
{
    int type_id;
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    /** set CRPS_ENGINE_TYPE_CONFIG table */

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_CRPS_ENGINE_TYPE_CONFIG, &entry_handle_id));

    /** Setting key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_ID, engine->engine_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, engine->core_id);

    /** Type offset configuration depend  on the counter_set _size. It will be updated in the HW after API data_mapping_set will be called */
    for (type_id = 0; type_id < BCM_STAT_MAX_NUMBER_OF_OBJECT_TYPES; type_id++)
    {
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_STAT_IF_TYPE_ID, type_id);
        /** Setting value fields */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_TYPE_ADMISSION, INST_SINGLE,
                                     valid[type_id]);

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_TYPE_MAP_OFFSET, INST_SINGLE,
                                     ((valid[type_id] == TRUE) ? offset[type_id] : 0));

        /** Preforming the action */
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_engine_clear_hw_mem_done_get(
    int unit,
    bcm_stat_engine_t * engine,
    uint32 *clear_done)
{
    uint32 entry_handle_id;
    uint32 init_req;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_CRPS_ENGINE_ENABLE, &entry_handle_id));

    /** Setting key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_ID, engine->engine_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, engine->core_id);

    /** Setting pointers value to receive the fields */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_DONE_INDICATION, INST_SINGLE, clear_done);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_INIT_REQUEST, INST_SINGLE, &init_req);

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

    /*
     * update the clear_done according the following logic: HW detect init_req 0>1, and clear "done" bit. The basic
     * condition to check if init done, is that init started. Therfore, if init_req=0, check if done_ind=1.
     */
    if (init_req == FALSE)
    {
        *clear_done = TRUE;
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_engine_enable_hw_get(
    int unit,
    bcm_stat_engine_t * engine,
    int *enable_eviction,
    int *enable_counting)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_CRPS_ENGINE_ENABLE, &entry_handle_id));

    /** Setting key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_ID, engine->engine_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, engine->core_id);

    /** Setting pointers value to receive the fields */
    if (enable_eviction != NULL)
    {
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_SCAN_ENABLE, INST_SINGLE,
                                   (uint32 *) enable_eviction);
    }
    if (enable_counting != NULL)
    {
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_SOURCE_SELECT_ENABLE, INST_SINGLE,
                                   (uint32 *) enable_counting);
    }

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_engine_enable_hw_set(
    int unit,
    bcm_stat_engine_t * engine,
    int enable_eviction,
    int enable_counting)
{
    uint32 entry_handle_id;
    int eviction_algorithmic_disable;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** if input params do not contain one of the enablers, get it from HW */
    if (enable_eviction == -1)
    {
        SHR_IF_ERR_EXIT(dnx_crps_engine_enable_hw_get(unit, engine, &enable_eviction, NULL));
    }
    if (enable_counting == -1)
    {
        SHR_IF_ERR_EXIT(dnx_crps_engine_enable_hw_get(unit, engine, NULL, &enable_counting));
    }

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_CRPS_ENGINE_ENABLE, &entry_handle_id));

    /** Setting key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_ID, engine->engine_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, engine->core_id);

    /** Enable LFSR scan*/
    SHR_IF_ERR_EXIT(dnx_crps_db.proc.eviction.eviction_algorithmic_disable.get
                    (unit, engine->core_id, engine->engine_id, &eviction_algorithmic_disable));
    if (dnx_data_crps.eviction.feature_get(unit, dnx_data_crps_eviction_probabilistic_is_supported)
        && !eviction_algorithmic_disable)
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_SCAN_PROBABILISTIC_ENABLE,
                                     INST_SINGLE, enable_eviction);
    }
    /** enable/disable the eviction */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_SCAN_ENABLE, INST_SINGLE,
                                 enable_eviction);

    /** enable/disable the counting */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_SOURCE_SELECT_ENABLE, INST_SINGLE,
                                 enable_counting);

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;

}

/** see .h file */
shr_error_e
dnx_crps_engine_memory_access_enable(
    int unit,
    bcm_stat_engine_t * engine,
    int enable)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_CRPS_ENGINE_ENABLE, &entry_handle_id));

    /** Setting key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_ID, engine->engine_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, engine->core_id);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_PIPE_ENABLE, INST_SINGLE, enable);

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_engine_hw_counters_reset(
    int unit,
    bcm_stat_engine_t * engine_p)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_CRPS_ENGINE_ENABLE, &entry_handle_id));

    /** Setting key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_ID, engine_p->engine_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, engine_p->core_id);

    /** Setting value fields */

    /** clear the HW counter memory. this operation takes time. CRPS HW indicate it finished in another register (done) */
    /** HW detect 0>1. therfore, need to reset and set back */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_INIT_REQUEST, INST_SINGLE, FALSE);
    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_INIT_REQUEST, INST_SINGLE, TRUE);

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*   function write to data mapping hw table the values {addmission and counter_set_offset} in a given index
* \par DIRECT INPUT:
*   \param [in] unit    -  unit id
*   \param [in] engine  -  engineid and core id
*   \param [in] index   -  entry in the data mapping table
*   \param [in] value   -  strucutre of offset and addmission
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_crps_engine_data_mapping_hw_set(
    int unit,
    bcm_stat_engine_t * engine,
    uint32 index,
    bcm_stat_expansion_data_value_t value)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_CRPS_EXPANSION_DATA_MAPPING, &entry_handle_id));

    /** Setting key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_ID, engine->engine_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, engine->core_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_EXPANSION_INDEX, index);

    /** Setting pointers value to receive the fields */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_EXPANSION_DATA_ADMISSION, INST_SINGLE,
                                 value.valid);
    dbal_entry_value_field32_set
        (unit, entry_handle_id, DBAL_FIELD_CRPS_EXPANSION_DATA_OFFSET, INST_SINGLE, value.counter_set_offset);

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_engine_data_mapping_hw_get(
    int unit,
    bcm_stat_engine_t * engine,
    uint32 index,
    bcm_stat_expansion_data_value_t * value)
{
    uint32 entry_handle_id;
    uint32 data1, data2, data3 = 0;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_CRPS_EXPANSION_DATA_MAPPING, &entry_handle_id));

    /** Setting key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_ID, engine->engine_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, engine->core_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_EXPANSION_INDEX, index);

    /** Setting pointers value to receive the fields */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_CRPS_EXPANSION_DATA_ADMISSION, INST_SINGLE, &data1);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_CRPS_EXPANSION_DATA_OFFSET, INST_SINGLE, &data2);

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

    value->valid = data1;
    value->counter_set_offset = data2;
    value->set_id = data3;

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_engine_data_mapping_hw_copy(
    int unit,
    bcm_stat_engine_t * src_engine,
    bcm_stat_engine_t * dest_engine)
{
    dbal_table_field_info_t field_info;
    int index;
    bcm_stat_expansion_data_value_t value;
    SHR_FUNC_INIT_VARS(unit);

    /** get how many entries for the HW table */
    SHR_IF_ERR_EXIT(dbal_tables_field_info_get(unit, DBAL_TABLE_CRPS_EXPANSION_DATA_MAPPING,
                                               DBAL_FIELD_CRPS_EXPANSION_INDEX, TRUE, 0, 0, &field_info));

    for (index = 0; index <= field_info.max_value; index++)
    {
        SHR_IF_ERR_EXIT(dnx_crps_engine_data_mapping_hw_get(unit, src_engine, index, &value));
        SHR_IF_ERR_EXIT(dnx_crps_engine_data_mapping_hw_set(unit, dest_engine, index, value));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - return a number which represent: _bitmap & _input_val, but sqeeze the holes in the bitmap.
 *  for example: for _bitmap=0xb, _input_val=0xD, _ret_val=0x5
 * \param [in] unit -unit id
 * \param [in] bitmap -bitmap to compare with
 * \param [in] bitmap_size -number of bits of the bitmap
 * \param [in] input_val -input value
 * \param [out] ret_val -output value
 * \return
 *   see shr_error_e
 * \remark
 *   NONE
 * \see
 *   NONE
 */
static shr_error_e
dnx_crps_engine_condition_value_calc(
    int unit,
    uint32 bitmap,
    uint32 bitmap_size,
    uint32 input_val,
    uint32 *ret_val)
{
    uint32 count = 0;
    uint32 data = 0;
    int bit_idx;
    SHR_FUNC_INIT_VARS(unit);

    *ret_val = 0;

    for (bit_idx = 0; bit_idx < bitmap_size; bit_idx++)
    {
        if (SHR_BITGET(&bitmap, bit_idx))
        {
            data = 0;
            SHR_BITAND_RANGE(&bitmap, &input_val, bit_idx, 1, &data);
            if (data != 0)
            {
                SHR_BITSET(ret_val, count);
            }
            count++;
        }
    }

/**exit: */
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_engine_data_mapping(
    int unit,
    int write_value,
    bcm_stat_engine_t * engine,
    int nof_interface_keys,
    bcm_stat_counter_interface_key_t * interface_key,
    uint32 selection[BCM_STAT_MAX_NUMBER_OF_OBJECT_TYPES][2],
    bcm_stat_expansion_data_mapping_t * data_mapping)
{
    int index, key;
    uint32 expansion_valid_bits, condition_bitmap = 0;
    uint32 nof_bits, offset_in_selection, bitmap;
    int is_selected, offset_in_expansion, expansion_nof_bits, max_expansion_val = 0;
    int conditions_match = 0;
    int nof_bitmap_bits;
    uint32 condition_value;
    SHR_FUNC_INIT_VARS(unit);

    /** run over all interfaces (the diffrence between them is the type_id ) */
    /** and find the first interface that his expansion selection match to all of the key conditions */
    for (key = 0; key < nof_interface_keys; key++)
    {
        expansion_valid_bits = 0;
        condition_bitmap = 0;
        conditions_match = TRUE;
        /** run over all key conditions and generate 2 bitmaps which represent the key condiftions */
        /** 1. expansion_valid_bits = bitmap that represent the bits from the expansion (10bits) that the conditions key refer to*/
        /** 2. condition_bitmap = bitmap that represent the expansion (10bits) value according to the conditions key */
        /** Note: nof_key_conditions=0, all 1024 entries will be written, because there are no conditions :) */
        for (index = 0; index < data_mapping->nof_key_conditions; index++)
        {
            /** check if the field from the condition is part of the expansion selection */
            /** Note: since the expansion selection is per type, it is not mandatory that all condition fileds will apear in all expansion selections */
            SHR_IF_ERR_EXIT(dnx_crps_src_interface_expansion_field_is_selected
                            (unit, engine->core_id, interface_key[key].interface_source, interface_key[key].command_id,
                             data_mapping->key[index].type, selection[key], &bitmap, &is_selected));
            if (is_selected)
            {
                /** get field expansion type offset */
                SHR_IF_ERR_EXIT(dnx_crps_src_interface_expansion_type_offset_get
                                (unit, engine->core_id, interface_key[key].interface_source,
                                 interface_key[key].command_id, data_mapping->key[index].type, &offset_in_selection));
                /** find how many bits are set before this field. */
                SHR_BITCOUNT_RANGE(selection[key], offset_in_expansion, 0, offset_in_selection);

                /** get field expansion type number of bits */
                nof_bits =
                    dnx_data_crps.expansion.source_metadata_types_get(unit, interface_key[key].interface_source,
                                                                      data_mapping->key[index].type)->nof_bits;
                /** the condition value that is given in the API should be masked and align base on the bitmap. */
                /** For exapmle: for value: 0xF and bitmap=0x9, the real condition_value (as the expansion see it) is 0x3 */
                SHR_IF_ERR_EXIT(dnx_crps_engine_condition_value_calc
                                (unit, bitmap, nof_bits, (uint32) data_mapping->key[index].value, &condition_value));

                condition_bitmap |= (condition_value << offset_in_expansion);

                /** SInce it is not mandatory that all bits of the type is set (as mentioned in the bitmap),  */
                /** we have to first count the number of bits in the bitmap and only then set the relevant bits in the expansion_valid_bits, */
                /** for example if the bitmap is: b'1011, we will count 3 bits and set it */
                SHR_BITCOUNT_RANGE(&bitmap, nof_bitmap_bits, 0, nof_bits);
                nof_bits = nof_bitmap_bits;
                SHR_BITSET_RANGE(&expansion_valid_bits, offset_in_expansion, nof_bits);
            }
            else
            {
                conditions_match = FALSE;
                break;
            }
        }
        /** if all conditions are part of the interface expansion selection, find the max possible value for the expansion data and break from loop*/
        if (conditions_match == TRUE)
        {
            SHR_BITCOUNT_RANGE(selection[key], expansion_nof_bits, 0, 64);
            max_expansion_val = (1 << expansion_nof_bits) - 1;
            break;
        }
    }
    /** if we didn't find any interface that contain all of the fields condition - return an error */
    if (conditions_match == FALSE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "the given fields in the conditions do not match to the expansion selection \n");
    }
    /** set value */
    if (write_value == TRUE)
    {
        /** go over all possible table indexes and check which one match to all of the key conditions */
        for (index = 0; index <= max_expansion_val; index++)
        {
            if ((index & expansion_valid_bits) == (condition_bitmap & expansion_valid_bits))
            {
                SHR_IF_ERR_EXIT(dnx_crps_engine_data_mapping_hw_set(unit, engine, index, data_mapping->value));
            }
        }
    }
    /** get value */
    else
    {
        /** read one of the indexes that match the key conditions.  */
        SHR_IF_ERR_EXIT(dnx_crps_engine_data_mapping_hw_get
                        (unit, engine, (condition_bitmap & expansion_valid_bits), &data_mapping->value));
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_engine_data_mapping_full_spread_set(
    int unit,
    bcm_stat_engine_t * engine,
    int size,
    int valid)
{
    int index;
    bcm_stat_expansion_data_value_t value;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * go over all entries {0..(size-1)} and configure the offset according to the index and the valid field according to the input valid value
     */
    for (index = 0; index < size; index++)
    {
        value.valid = valid;
        value.counter_set_offset = (valid == TRUE) ? (index % dnx_data_crps.engine.max_counter_set_size_get(unit)) : 0;
        value.set_id = 0;
        SHR_IF_ERR_EXIT(dnx_crps_engine_data_mapping_hw_set(unit, engine, index, value));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_meter_shared_b_and_c_bank_hw_set(
    int unit,
    int core_id,
    dbal_tables_e dbal_table_id,
    int bank_id,
    dbal_enum_value_field_meter_crps_smem_src_types_e src_type)
{

    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, dbal_table_id, &entry_handle_id));

    /** calcultae bank id  */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_BANK_ID, bank_id);
    /** Setting value fields */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_METER_CRPS_SMEM_SRC_TYPES, INST_SINGLE, src_type);
    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_engine_bank_src_hw_set(
    int unit,
    int core_id,
    int engine_id,
    dnx_crps_mgmt_shmem_section_t section,
    dbal_enum_value_field_meter_crps_smem_src_types_e src_type)
{
    uint32 entry_handle_id;
    int base_bank, last_bank, bank_id;
    int single_bucket_engine = DNX_CRPS_METER_SHMEM_IS_METER_SINGLE_BUCKET_ENGINE(unit, engine_id);
    dbal_tables_e dbal_table_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** engine 0 and 1 are small engines and behave differently from big engines.
               each engine has one bank. engine 0 may be used for CRPS or ingress meter, engine 1 may be used for CRPS or egress meter */
    if (single_bucket_engine)
    {
        /** Taking a handle */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_CRPS_METER_SMALL_ENGINE_SHARED_MEM, &entry_handle_id));
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ENGINE_ID, engine_id);
        /** Setting value fields */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_SRC_METER, INST_SINGLE,
                                     (src_type != DBAL_ENUM_FVAL_METER_CRPS_SMEM_SRC_TYPES_CRPS));
        /** Preforming the action */
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    }
    else
    {
        if (IS_B_TYPE_ENGINE(unit, engine_id))
        {
        }

        else
        {
            dbal_table_id = DBAL_TABLE_CRPS_METER_BIG_ENGINE_SHARED_MEM;

            /** if section=ALL, need to updates two banks that used for the engine.*/
            if (section == dnx_crps_mgmt_shmem_section_all)
            {
                base_bank = dnx_crps_mgmt_shmem_section_low;
                last_bank = dnx_crps_mgmt_shmem_section_high;

            }

            else if (section == dnx_crps_mgmt_shmem_section_low)
            {
                base_bank = dnx_crps_mgmt_shmem_section_low;
                last_bank = dnx_crps_mgmt_shmem_section_low;
            }

            else
            {
                /** high */
                base_bank = dnx_crps_mgmt_shmem_section_high;
                last_bank = dnx_crps_mgmt_shmem_section_high;
            }

            for (; base_bank <= last_bank; base_bank++)
            {
                /** calcultae bank id  */
                SHR_IF_ERR_EXIT(dnx_crps_mgmt_meter_shmem_bank_id_get(unit, engine_id, base_bank, &bank_id));

                SHR_IF_ERR_EXIT(dnx_crps_meter_shared_b_and_c_bank_hw_set
                                (unit, core_id, dbal_table_id, bank_id, src_type));

            }
        }
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_engine_bank_src_hw_get(
    int unit,
    int core_id,
    int engine_id,
    dnx_crps_mgmt_shmem_section_t section,
    dbal_enum_value_field_meter_crps_smem_src_types_e * src_type)
{
    uint32 is_src_meter, entry_handle_id;
    int bank_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** engine 0 and 1 are small engines and behave differently from big engines.
               each engine has one bank. engine 0 may be used for CRPS or ingress meter, engine 1 may be used for CRPS or egress meter */
    if (DNX_CRPS_METER_SHMEM_IS_METER_SINGLE_BUCKET_ENGINE(unit, engine_id))
    {
        /** Taking a handle */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_CRPS_METER_SMALL_ENGINE_SHARED_MEM, &entry_handle_id));
        /** Setting key fields */
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ENGINE_ID, engine_id);
        /** Setting value fields */
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_IS_SRC_METER, INST_SINGLE, &is_src_meter);

        /** Preforming the action */
        SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

        /** if meter, update if ingress or egress meter base on the engine id.*/
        if (is_src_meter == TRUE)
        {
            *src_type = (engine_id == dnx_data_meter.mem_mgmt.ingress_single_bucket_engine_get(unit)) ?
                DBAL_ENUM_FVAL_METER_CRPS_SMEM_SRC_TYPES_METER_INGRESS :
                DBAL_ENUM_FVAL_METER_CRPS_SMEM_SRC_TYPES_METER_EGRESS;
        }
        else
        {
            *src_type = DBAL_ENUM_FVAL_METER_CRPS_SMEM_SRC_TYPES_CRPS;
        }
    }
    else
    {
        /** if section=ALL, error. function return only one bank each time */
        if (section == dnx_crps_mgmt_shmem_section_all)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "section=dnx_crps_mgmt_shmem_section_all is not allowed\n");
        }

        /** calcultae bank id */
        SHR_IF_ERR_EXIT(dnx_crps_mgmt_meter_shmem_bank_id_get(unit, engine_id, section, &bank_id));
        /** Taking a handle */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_CRPS_METER_BIG_ENGINE_SHARED_MEM, &entry_handle_id));
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_BANK_ID, bank_id);
        /** Setting value fields */
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_METER_CRPS_SMEM_SRC_TYPES, INST_SINGLE, src_type);
        SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;

}

/** see .h file */
shr_error_e
dnx_crps_engine_last_command_hw_get(
    int unit,
    bcm_stat_engine_t * engine,
    uint32 *last_address,
    uint64 *last_data)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_CRPS_LAST_COMMAND, &entry_handle_id));

    /** Setting key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_ID, engine->engine_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, engine->core_id);

    /** Setting pointers value to receive the fields */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_ENGINE_LAST_ADDRESS_ADMITTED, INST_SINGLE,
                               last_address);
    dbal_value_field64_request(unit, entry_handle_id, DBAL_FIELD_ENGINE_LAST_DATA_ADMITTED, INST_SINGLE, last_data);

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_engine_address_get(
    int unit,
    bcm_stat_counter_database_t * database,
    uint32 counter_id,
    bcm_stat_engine_t * engine,
    uint32 *engine_address)
{
    dnx_engine_interface_info_t inf;
    uint32 first_index, last_index;
    uint32 type_offset;
    int current_engine_id, base_engine_id;
    int type_id = 0;
    int entry_found = FALSE;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_crps_db.database.
                    base_engine.get(unit, database->core_id, database->database_id, &base_engine_id));

    /** get the engine configuration from db */
    SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.get(unit, database->core_id, base_engine_id, &inf));

    SHR_IF_ERR_EXIT(dnx_crps_db.database.type.
                    offset.get(unit, database->core_id, database->database_id, type_id, &type_offset));

    current_engine_id = base_engine_id;

    while (current_engine_id != DNX_CRPS_MGMT_ENGINE_INVALID)
    {
        /** get the range of the engine and verify that the logical_object_id is in the range */
        SHR_IF_ERR_EXIT(dnx_crps_db.proc.log_obj_id_range.
                        logical_object_id_first.get(unit, database->core_id, current_engine_id, &first_index));
        SHR_IF_ERR_EXIT(dnx_crps_db.proc.log_obj_id_range.
                        logical_object_id_last.get(unit, database->core_id, current_engine_id, &last_index));
        if (counter_id < first_index)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Counter ID %d is out of range.\r\n", counter_id);
        }
        else if (counter_id >= first_index && counter_id < last_index)
        {
            engine->core_id = database->core_id;
            engine->engine_id = current_engine_id;
            *engine_address = counter_id - first_index;
            entry_found = TRUE;
            break;
        }
        else
        {
            /*
             * get the next engine
             */
            SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.
                            next_engine_id.get(unit, database->core_id, current_engine_id, &current_engine_id));
        }
    }
    if (!entry_found)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Counter ID %d is out of range.\r\n", counter_id);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*   function convert the format type from API enum to DBAL enum
* \par DIRECT INPUT:
*   \param [in] unit         -
*   \param [in] format_type  -  api format type
*   \param [out] dbal_format  -  dbal format type
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_crps_engine_full_format_dbal_convert(
    int unit,
    bcm_stat_counter_format_type_t format_type,
    dbal_enum_value_field_crps_engine_counter_format_e * dbal_format)
{
    dbal_enum_value_field_crps_engine_counter_format_e format =
        DBAL_ENUM_FVAL_CRPS_ENGINE_COUNTER_FORMAT_NOT_VALID_MODE;

    SHR_FUNC_INIT_VARS(unit);
    switch (format_type)
    {
        case bcmStatCounterFormatPacketsAndBytes:
            format = DBAL_ENUM_FVAL_CRPS_ENGINE_COUNTER_FORMAT_COUNTER_PACKETS_AND_BYTES;
            break;
        case bcmStatCounterFormatPackets:
            format = DBAL_ENUM_FVAL_CRPS_ENGINE_COUNTER_FORMAT_COUNTER_PACKETS_WIDE;
            break;
        case bcmStatCounterFormatBytes:
            format = DBAL_ENUM_FVAL_CRPS_ENGINE_COUNTER_FORMAT_COUNTER_BYTES_WIDE;
            break;
        case bcmStatCounterFormatDoublePackets:
            format = DBAL_ENUM_FVAL_CRPS_ENGINE_COUNTER_FORMAT_COUNTER_PACKETS_NARROW;
            break;
        case bcmStatCounterFormatMaxSize:
            format = DBAL_ENUM_FVAL_CRPS_ENGINE_COUNTER_FORMAT_COUNTER_MAX_NARROW;
            break;
        case bcmStatCounterFormatSlimPacketsAndBytes:
            format = DBAL_ENUM_FVAL_CRPS_ENGINE_COUNTER_FORMAT_COUNTER_SLIM_PACKETS_AND_BYTES;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "invalid format type (value=%d) \n", format_type);
            break;
    }

exit:
    *dbal_format = format;
    SHR_FUNC_EXIT;
}

/**
* \brief
*   function convert the format type from API enum to DBAL enum
* \par DIRECT INPUT:
*   \param [in] unit          -
*   \param [in] format_type   - api format type
*   \param [in] counter_size  - api counter size (relevant only for state counter format)
*   \param [in] mode          - api mode (relevant only for state counter format)
*   \param [in] dbal_format - dbal format field value
*   \param [in] dbal_mode - dbal mode field value
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_crps_engine_counter_format_dbal_convert(
    int unit,
    bcm_stat_counter_format_type_t format_type,
    int counter_size,
    bcm_stat_counter_mode_t mode,
    uint32 *dbal_format,
    uint32 *dbal_mode)
{

    dbal_enum_value_field_crps_engine_counter_format_e format_type_set =
        DBAL_ENUM_FVAL_CRPS_ENGINE_COUNTER_FORMAT_NOT_VALID_MODE;

    SHR_FUNC_INIT_VARS(unit);

    if (!dnx_data_crps.engine.feature_get(unit, dnx_data_crps_engine_dynamic_counter_mode_is_supported))
    {
        SHR_IF_ERR_EXIT(dnx_crps_engine_full_format_dbal_convert(unit, format_type, &format_type_set));
    }

    *dbal_format = (uint32) format_type_set;

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_single_set_engine_cfg_set_size_hw_set(
    int unit,
    bcm_stat_engine_t * engine,
    int counter_set_size)
{

    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_CRPS_ENGINE_CFG, &entry_handle_id));

    /** Setting key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, engine->core_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_ID, engine->engine_id);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_GROUP_SIZE, INST_SINGLE,
                                 counter_set_size);

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;

}

shr_error_e
dnx_crps_engine_single_set_size_hw_config_set(
    int unit,
    bcm_stat_engine_t * engine,
    int counter_set_size)
{
    int set_idx;
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_crps.engine.feature_get(unit, dnx_data_crps_engine_multi_sets_is_supported))
    {
        /**enable only the first set, and dusable the others */
        for (set_idx = 0; set_idx < dnx_data_crps.engine.max_nof_counter_sets_get(unit); set_idx++)
        {
        }
    }

    else
    {
        SHR_IF_ERR_EXIT(dnx_crps_single_set_engine_cfg_set_size_hw_set(unit, engine, counter_set_size));
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_engine_hw_config_set(
    int unit,
    bcm_stat_engine_t * engine,
    bcm_stat_counter_interface_t * config)
{

    uint32 entry_handle_id, set_val;
    uint32 mode, format;
    const dnx_data_crps_engine_source_base_t *src_base;
    const dnx_data_crps_src_interface_command_id_t *command_data;
    int nof_counters_per_entry;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /**  set CRPS_ENGINE_CFG table */

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_CRPS_ENGINE_CFG, &entry_handle_id));

    /** Setting key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_ID, engine->engine_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, engine->core_id);

    /** Setting value fields */

    /** Counter format set*/
    SHR_IF_ERR_EXIT(dnx_crps_engine_counter_format_dbal_convert
                    (unit, config->format_type, config->counter_size, config->mode, &format, &mode));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_COUNTER_FORMAT, INST_SINGLE, format);

    /** the source_select value is unique per source and command_id.  each source has it's base value,
              which need to add the command_id in order to define the unique value */
    src_base = dnx_data_crps.engine.source_base_get(unit, config->source);
    command_data = dnx_data_crps.src_interface.command_id_get(unit, config->source);
    set_val = src_base->base_val + config->command_id - command_data->base;
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_SOURCE_SELECT, INST_SINGLE, set_val);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_ENABLE_CLEAR_ON_READ, INST_SINGLE,
                                 FALSE);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_PHY_ADDRRESS_EXCEED_MASK, INST_SINGLE,
                                 0);

    nof_counters_per_entry =
        dnx_data_crps.engine.counter_format_types_get(unit, config->format_type)->nof_counters_per_entry;

    /** Invalid admission for logical addresses which exceed the engine range->last when not working in double mode */
    /** setting the mask to 0x10, when the counter mode is not double mode (2*34bits), */
    /** will mask the MSB bits for the admission logic, and only valid counters will be admitted to the engine */
    if ((nof_counters_per_entry == dnx_data_crps.engine.counter_format_types_get(unit, bcmStatCounterFormatPackets)->nof_counters_per_entry) /** full size counter */
        && (FALSE == dnx_data_crps.engine.feature_get(unit, dnx_data_crps_engine_valid_address_admission_is_supported)))
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CRPS_ENGINE_PHY_ADDRRESS_EXCEED_MASK,
                                     INST_SINGLE, 0x10);
    }

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_CRPS_ENGINE_CFG, entry_handle_id));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

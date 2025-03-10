
/** \file crps_verify.c
 * 
 *  crps module gather all functionality that related to the counter/statisitc processor driver for DNX.
 *  crps_verify.c verifies the CRPS APIs functionality for DNX.

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
#include <soc/dnx/dnx_data/auto_generated/dnx_data_device.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_crps.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_stat.h>
#include <bcm_int/dnx/stat/crps/crps_src_interface.h>
#include <bcm_int/dnx/stat/crps/crps_mgmt.h>
#include <bcm_int/dnx/cmn/dnxcmn.h>
#include <bcm_int/dnx/algo/port/algo_port_mgmt.h>
#include "crps_engine.h"
#include "crps_eviction.h"
#include "crps_mgmt_internal.h"
#include "crps_verify.h"
#include <shared/utilex/utilex_integer_arithmetic.h>

/**
 * See crps_mgmt.h
*/
shr_error_e
dnx_crps_mgmt_counter_command_id_verify(
    int unit,
    bcm_stat_counter_interface_type_t source,
    int command_id)
{
    const dnx_data_crps_src_interface_command_id_t *values;
    SHR_FUNC_INIT_VARS(unit);
    /** get max value for command_id*/
    values = dnx_data_crps.src_interface.command_id_get(unit, source);
    /** check for correct command_id value*/
    if (command_id < values->base || command_id >= (values->base + values->size))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "  Incorrect command_id=%d, must be between %d to %d \n", command_id, values->base,
                     (values->base + values->size));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*   verification engine - engine_id in range and valid core_id
* \par DIRECT INPUT:
*   \param [in] unit    -  Unit-ID
*   \param [in] engine  -  engine configuration
*   \param [in] core_all_valid  -  TRUE - bcm_core_all allowed;
*          FALSE - unique core, bcm_core_all is not allowed
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
dnx_crps_mgmt_counter_engine_structure_verify(
    int unit,
    bcm_stat_engine_t * engine,
    int core_all_valid)
{
    SHR_FUNC_INIT_VARS(unit);
    /** verify the engine is valid */
    if (engine->engine_id >= dnx_data_crps.engine.nof_engines_get(unit) || engine->engine_id < 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect engine_id=%d, possible values 0 till 21 \n", engine->engine_id);
    }
    /** check for valid core - BCM_CORE_ALL not allowed */
    DNXCMN_CORE_VALIDATE(unit, engine->core_id, core_all_valid);

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_mgmt_database_structure_verify(
    int unit,
    bcm_stat_counter_database_t * database,
    int core_all_valid)
{
    int core_idx;
    uint8 is_allocated;
    SHR_FUNC_INIT_VARS(unit);

    /** check for valid core - BCM_CORE_ALL is allowed for set/get configuration, but not for reading counters APIs */
    DNXCMN_CORE_VALIDATE(unit, database->core_id, core_all_valid);

    DNXCMN_CORES_ITER(unit, database->core_id, core_idx)
    {
        SHR_IF_ERR_EXIT(dnx_crps_db.database_res.is_allocated(unit, core_idx, database->database_id, &is_allocated));
        /** check that database is allocated */
        if (is_allocated == FALSE)
        {
            SHR_ERR_EXIT(_SHR_E_NOT_FOUND, "database_id %d core_id %d doesn't exist\n",
                         database->database_id, core_idx);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*   verification of dnx_crps_mgmt_range_config used in API
*   bcm_dnx_stat_counter_interface_set
*   1. find the biggest counter pointer ans check if it fits in
*   the database counter range size
*   2. check for overlapping between type ranges
*   3. check for unused counters
* \par DIRECT INPUT:
*   \param [in] unit    -  Unit-ID
*   \param [in] database  - defined by database_id and core.
*   \param [in] base_engine_id    -  base engine of the database
*   \param [in] config  -  configuration structure
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
dnx_crps_mgmt_database_type_ranges_verify(
    int unit,
    bcm_stat_counter_database_t * database,
    int base_engine_id,
    bcm_stat_counter_interface_t * config)
{
    int type_id = 0;
    int curr_engine_id = base_engine_id;
    int total_range_size = 0, nof_counters_in_engine = 0;
    int max_counter_pointer = 0, counter_pointer_per_type = 0, min_counter_pointer = 0x1FFFFFFF;
    int valid_types_values[BCM_STAT_MAX_NUMBER_OF_OBJECT_TYPES][3] = { {0} };
                                                                            /** offset/ start / end */
    int nof_valid_values = 0;
    int array_row_i, array_row_j, slap, temp, offset;
    int start, end;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(database, _SHR_E_PARAM, "database");

    /** get total engine space for the database */
    while (curr_engine_id != DNX_CRPS_MGMT_ENGINE_INVALID)
    {
        SHR_IF_ERR_EXIT(dnx_crps_mgmt_nof_counters_per_engine
                        (unit, curr_engine_id, config->format_type, config->counter_size, &nof_counters_in_engine));
        total_range_size += nof_counters_in_engine;
        SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.
                        next_engine_id.get(unit, database->core_id, curr_engine_id, &curr_engine_id));
    }

    /** 1.  find the biggest counter pointer and check if it fits in
     *  the database counter range size */

    /** get the biggest counter pointer and the lowest counter pointer */
    /** save the valid values in array for part 2. */
    for (type_id = 0; type_id < BCM_STAT_MAX_NUMBER_OF_OBJECT_TYPES; type_id++)
    {
        if (config->type_config[type_id].valid)
        {
            counter_pointer_per_type =
                config->type_config[type_id].end + config->type_config[type_id].object_type_offset;
            if (counter_pointer_per_type > max_counter_pointer)
            {
                max_counter_pointer = counter_pointer_per_type;
            }
            counter_pointer_per_type =
                config->type_config[type_id].start + config->type_config[type_id].object_type_offset;
            if (counter_pointer_per_type < min_counter_pointer)
            {
                min_counter_pointer = counter_pointer_per_type;
            }

            /** save valid type values to array */
            valid_types_values[nof_valid_values][0] = config->type_config[type_id].object_type_offset;
            valid_types_values[nof_valid_values][1] = config->type_config[type_id].start;
            valid_types_values[nof_valid_values][2] = config->type_config[type_id].end;
            nof_valid_values++;
        }
    }
    if (((max_counter_pointer - min_counter_pointer + 1) * config->counter_set_size) > total_range_size)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     " Out of range values for database_id=%d (core_id=%d). total counters size for the database is %d, which can't contain the min value (%d) and the max value (%d)\n",
                     database->database_id, database->core_id, total_range_size,
                     min_counter_pointer * config->counter_set_size, max_counter_pointer * config->counter_set_size);
    }
    /** 2.  check for overlapping between type ranges   */
    /** first - sort the array ascending according to offset+start value */
    offset = 0;
    start = 1;
    end = 2;
    for (array_row_i = 0; array_row_i < nof_valid_values; array_row_i++)
    {
        for (array_row_j = array_row_i + 1; array_row_j < nof_valid_values; array_row_j++)
        {
            if ((valid_types_values[array_row_i][offset] + valid_types_values[array_row_i][start]) >
                (valid_types_values[array_row_j][offset] + valid_types_values[array_row_j][start]))
            {
                for (slap = 0; slap < 3; slap++)
                {
                    temp = valid_types_values[array_row_i][slap];
                    valid_types_values[array_row_i][slap] = valid_types_values[array_row_j][slap];
                    valid_types_values[array_row_j][slap] = temp;
                }
            }
        }
    }
    /** loop the sorted array and check for overlapping ranges or
     *  unused counters */
    for (type_id = 1; type_id < nof_valid_values; type_id++)
    {
        /** check for overlapping */
        if (((valid_types_values[type_id][offset] + valid_types_values[type_id][start]) <=
             (valid_types_values[type_id - 1][offset] + valid_types_values[type_id - 1][end])))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         " Overlapping ranges for database_id=%d (core_id=%d) between types - range: offset=%d, start=%d, end=%d",
                         database->database_id, database->core_id, valid_types_values[type_id][start],
                         valid_types_values[type_id][end], valid_types_values[type_id][offset]);
        }
        /** print warning for unused counters */
        if (((valid_types_values[type_id][offset] + valid_types_values[type_id][start]) >
             (valid_types_values[type_id - 1][offset] + valid_types_values[type_id - 1][end] + 1)))
        {
            LOG_WARN(BSL_LOG_MODULE,
                     (BSL_META_U(unit, "Warning: Unused counters: unused range: start=%d, end=%d\n"),
                      (valid_types_values[type_id - 1][offset] + valid_types_values[type_id - 1][end] + 1),
                      (valid_types_values[type_id][offset] + valid_types_values[type_id][start])));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief  
*   verification on APIs bcm_stat_counter_get and
*   bcm_stat_counter_explicit_get valid statistic array values
* \par DIRECT INPUT: 
*   \param [in] unit    -  Unit-ID
*   \param [in] stat_arr  -  the array to be checked
*   \param [in] nstat  -  size of the array
*   \param [in] counter_set_size  -  set size for check
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
dnx_crps_mgmt_counter_get_statistic_array_verify(
    int unit,
    int *stat_arr,
    int nstat,
    int counter_set_size)
{
    int stat_arr_id = 0, ctr_set_offset = 0;
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(stat_arr, _SHR_E_PARAM, "stat_counter_input_data->stat_arr");

    if (nstat > DNX_CRPS_MGMT_MAX_NSTAT)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "nstat=%d. max allowed=%d",
                     nstat, (DNX_DATA_MAX_CRPS_ENGINE_MAX_COUNTER_SET_SIZE * 2));
    }
    /** {offset,is_bytes} offset should be < counter_set_size */
    for (stat_arr_id = 0; stat_arr_id < nstat; stat_arr_id++)
    {
        ctr_set_offset = _SHR_STAT_COUNTER_STAT_OFFSET_GET(stat_arr[stat_arr_id]);
        if (ctr_set_offset > counter_set_size)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "  Incorrect stat array offset=%d for id=%d\n", ctr_set_offset, stat_arr_id);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_counter_expansion_select_structure_verify(
    int unit,
    bcm_stat_counter_interface_type_t src,
    bcm_stat_expansion_select_t * expansion_select)
{

    int nof_bits = 0, current_element_nof_bits = 0, bitmap_nof_bits_set = 0;
    int element_idx;

    SHR_FUNC_INIT_VARS(unit);

    /** check nof_elements*/
    if (expansion_select->nof_elements < 0 || expansion_select->nof_elements >= bcmStatExpansionTypeMax)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     " Incorrect nof_elements=%d, possible values from 0 till 20, where 0 means no expansion selection \n",
                     expansion_select->nof_elements);
    }

    /** check each element type */
    for (element_idx = 0; element_idx < expansion_select->nof_elements; element_idx++)
    {

        current_element_nof_bits =
            dnx_data_crps.expansion.source_metadata_types_get(unit, src,
                                                              expansion_select->expansion_elements[element_idx].
                                                              type)->nof_bits;

        /** Validate the expansion element type is valid for the given source */
        if (current_element_nof_bits < 0)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " invalid expansion element type=%d for interface source (=%d)\n",
                         expansion_select->expansion_elements[element_idx].type, src);
        }

        /** If metadata is selected, the number of bits is according to the bitmap */
        if (DNX_CRPS_EXPANSION_TYPE_BITMAP_IS_RELEVANT(expansion_select->expansion_elements[element_idx].type))
        {

            bitmap_nof_bits_set = 0;
            SHR_BITCOUNT_RANGE(&expansion_select->expansion_elements[element_idx].bitmap, bitmap_nof_bits_set, 0,
                               UTILEX_NOF_BITS_IN_UINT32);
            /** check if the set bits in the bitmap are in correct range
             *  nof_bits_per_type holds the max bits that can be set for
             *  metadata for this source */
            if (bitmap_nof_bits_set > current_element_nof_bits || bitmap_nof_bits_set <= 0)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             " invalid expansion meta data bitmap=%d for interface source (=%d)\n",
                             expansion_select->expansion_elements[element_idx].bitmap, src);
            }

            current_element_nof_bits = bitmap_nof_bits_set;
        }

        nof_bits = nof_bits + current_element_nof_bits;

    }

    /** Check the expansion value */
    if (nof_bits > dnx_data_crps.expansion.expansion_size_get(unit))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " More than 10b for expansion selected nof_bits=%d \n", nof_bits);
    }

exit:
    SHR_FUNC_EXIT;
}
/** see .h file */
shr_error_e
dnx_crps_mgmt_counter_expansion_select_set_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_interface_key_t * interface,
    bcm_stat_expansion_select_t * expansion_select)
{
    int engine_id = 0, valid_engine = 0;
    bcm_stat_counter_interface_type_t interface_source;
    int command_id, valid_type, core_idx;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(interface, _SHR_E_PARAM, "interface");
    SHR_NULL_CHECK(expansion_select, _SHR_E_PARAM, "expansion_select");

    /** check for valid flags value */
    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect flags=%d\n, no flags supported for this API - set flags to 0", flags);
    }

    /** check for valid interface source*/
    if (interface->interface_source < 0 || interface->interface_source >= bcmStatCounterInterfaceCount
        || dnx_data_crps.src_interface.command_id_get(unit, interface->interface_source)->size <= 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported interface_source=%d \n", interface->interface_source);
    }

    /** Check the expansion selection is necessary for the given source */
    if (dnx_data_crps.expansion.source_expansion_info_get(unit, interface->interface_source)->expansion_size <=
        (int) dnx_data_crps.expansion.expansion_size_get(unit))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "Incorrect interface_source=%d expansion API is not supported for this source \n",
                     interface->interface_source);
    }

    /** check for valid command id*/
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_command_id_verify(unit, interface->interface_source, interface->command_id));

    /** check for correct type_id value*/
    if (!dnx_data_crps.expansion.
        source_expansion_info_get(unit, interface->interface_source)->supports_expansion_per_type
        && interface->type_id != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "  Incorrect type_id=%d, possible value 0 \n", interface->type_id);
    }
    if (interface->type_id < 0 || interface->type_id >= BCM_STAT_MAX_NUMBER_OF_OBJECT_TYPES)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "  Incorrect type_id=%d, possible values from 0 till 3 \n", interface->type_id);
    }

    /** check for valid expansion select structure*/
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_expansion_select_structure_verify
                    (unit, interface->interface_source, expansion_select));

    /** check for valid core - BCM_CORE_ALL is also allowed */
    DNXCMN_CORE_VALIDATE(unit, interface->core_id, TRUE);

    DNXCMN_CORES_ITER(unit, interface->core_id, core_idx)
    {
        /** Check that there is no such active engine - cannot change the expansion while the engine is active*/
        for (engine_id = 0; engine_id < dnx_data_crps.engine.nof_engines_get(unit); engine_id++)
        {
            DNX_CRPS_MGMT_ENGINE_VALID_GET(unit, core_idx, engine_id, valid_engine);
            if (valid_engine)
            {
                SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.src_type.get(unit, core_idx, engine_id, &interface_source));
                SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.command_id.get(unit, core_idx, engine_id, &command_id));
                SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.
                                type_hw_valid.get(unit, core_idx, engine_id, interface->type_id, &valid_type));
                if ((interface->interface_source == interface_source) && (interface->command_id == command_id)
                    && valid_type)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM,
                                 " Active engine already exist on core_id=%d with source=%d , command_id=%d, type_id=%d \n",
                                 core_idx, interface_source, command_id, interface->type_id);
                }
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_mgmt_counter_expansion_select_get_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_interface_key_t * interface,
    bcm_stat_expansion_select_t * expansion_select)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(interface, _SHR_E_PARAM, "interface");
    SHR_NULL_CHECK(expansion_select, _SHR_E_PARAM, "expansion_select");

    /** check for valid flags value */
    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect flags=%d\n no flags are supported for this API, set flags=0", flags);
    }

    /** check for valid core - BCM_CORE_ALL not allowed */
    DNXCMN_CORE_VALIDATE(unit, interface->core_id, TRUE);

    /** check for valid interface source*/
    if (interface->interface_source < 0 || interface->interface_source >= bcmStatCounterInterfaceCount
        || dnx_data_crps.src_interface.command_id_get(unit, interface->interface_source)->size <= 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported interface_source=%d \n", interface->interface_source);
    }

    /** Check the expansion selection is necessary for the given source */
    if (dnx_data_crps.expansion.source_expansion_info_get(unit, interface->interface_source)->expansion_size <=
        (int) dnx_data_crps.expansion.expansion_size_get(unit))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "Incorrect interface_source=%d expansion API is not supported for this source \n",
                     interface->interface_source);
    }

    /** check for correct command_id value*/
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_command_id_verify(unit, interface->interface_source, interface->command_id));

    /** check for correct type_id value*/
    if (!dnx_data_crps.expansion.
        source_expansion_info_get(unit, interface->interface_source)->supports_expansion_per_type
        && interface->type_id != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "  Incorrect type_id=%d, possible value 0 \n", interface->type_id);
    }
    if (interface->type_id < 0 || interface->type_id >= BCM_STAT_MAX_NUMBER_OF_OBJECT_TYPES)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "  Incorrect type_id=%d, possible values from 0 till 3 \n", interface->type_id);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*   verification on command_id and format for ITM source - not
*   allowed MaxSize and other formats to be configured on the
*   same command id
*  \param [in] unit    -  Unit-ID
*  \param [in] database  - core id and database id
*  \param [in] command_id  -  the command id that has to be
*         checked
*  \param [in] format  -  the format that has to be checked
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_crps_mgmt_itm_format_command_id_verify(
    int unit,
    bcm_stat_counter_database_t * database,
    int command_id,
    bcm_stat_counter_format_type_t format)
{
    int core_idx;
    int database_id = 0, engine_id = 0, command_id_check = 0;
    uint8 is_allocated;
    bcm_stat_counter_interface_type_t interface_source;
    bcm_stat_counter_format_type_t format_check;
    SHR_FUNC_INIT_VARS(unit);

    DNXCMN_CORES_ITER(unit, database->core_id, core_idx)
    {
        for (database_id = 0; database_id < dnx_data_crps.engine.nof_databases_get(unit); database_id++)
        {
            SHR_IF_ERR_EXIT(dnx_crps_db.database_res.is_allocated(unit, core_idx, database_id, &is_allocated));
            /** check that database is allocated */
            if (is_allocated == TRUE && database_id != database->database_id)
            {
                SHR_IF_ERR_EXIT(dnx_crps_db.database.base_engine.get(unit, core_idx, database_id, &engine_id));
                SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.src_type.get(unit, core_idx, engine_id, &interface_source));
                if (interface_source == bcmStatCounterInterfaceIngressVoq)
                {
                    SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.
                                    command_id.get(unit, core_idx, engine_id, &command_id_check));
                    if (command_id == command_id_check)
                    {
                        SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.
                                        format.get(unit, core_idx, engine_id, &format_check));
                        if (format_check != format
                            && (format == bcmStatCounterFormatMaxSize || format_check == bcmStatCounterFormatMaxSize))
                        {
                            SHR_ERR_EXIT(_SHR_E_PARAM,
                                         " Incorrect format=%d, for IngressVoq is not supported to have two databases counting on same command id with different formats (MaxSize / PacketSize), database with format=%d already exist, database_id=%d\n",
                                         format, format_check, database_id);
                        }
                    }
                }
            }
        }
    }
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_all_c_engines_verify(
    int unit,
    bcm_stat_counter_database_t * database)
{
    int core_idx, base_engine_id, current_engine_id;
    SHR_FUNC_INIT_VARS(unit);

    DNXCMN_CORES_ITER(unit, database->core_id, core_idx)
    {
        SHR_IF_ERR_EXIT(dnx_crps_db.database.base_engine.get(unit, core_idx, database->database_id, &base_engine_id));
        current_engine_id = base_engine_id;

        while (current_engine_id != DNX_CRPS_MGMT_ENGINE_INVALID)
        {

            /*
             * Valid the engine is from type C
             */
            if (!IS_C_TYPE_ENGINE(unit, current_engine_id))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Slim format is not supported for not big_engine, engine_id=%d",
                             current_engine_id);
            }

            SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.
                            next_engine_id.get(unit, core_idx, current_engine_id, &current_engine_id));
        }
    }
exit:
    SHR_FUNC_EXIT;

}

static shr_error_e
dnx_crps_mgmt_slim_database_avilable_verify(
    int unit,
    bcm_stat_counter_database_t * database)
{
    int database_id, nof_slim_dbs, base_engine, core_idx;
    uint8 is_allocated;
    bcm_stat_counter_format_type_t format;
    SHR_FUNC_INIT_VARS(unit);

    DNXCMN_CORES_ITER(unit, database->core_id, core_idx)
    {
        nof_slim_dbs = 0;
        for (database_id = 0; database_id < dnx_data_crps.engine.nof_databases_get(unit); database_id++)
        {
            if (database_id == database->database_id)
            {
                continue;
            }

            SHR_IF_ERR_EXIT(dnx_crps_db.database_res.is_allocated(unit, core_idx, database_id, &is_allocated));

            if (!is_allocated)
            {
                continue;
            }

            SHR_IF_ERR_EXIT(dnx_crps_db.database.base_engine.get(unit, core_idx, database_id, &base_engine));
            SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.format.get(unit, core_idx, base_engine, &format));

            if (format == bcmStatCounterFormatSlimPacketsAndBytes)
            {
                nof_slim_dbs++;
            }

            if (nof_slim_dbs == dnx_data_crps.eviction.nof_crps_network_channels_get(unit))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "there is no free slip database to allocate, up to 8 are alloued");
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_counter_interface_set_slim_format_for_network_eviction_verify(
    int unit,
    bcm_stat_counter_database_t * database)
{

    SHR_FUNC_INIT_VARS(unit);

    /*
     * valid all the engines attached to the database are from type C
     */
    SHR_INVOKE_VERIFY_DNXC(dnx_crps_mgmt_all_c_engines_verify(unit, database));

    /*
     * valid there are less than 8 slim databases
     */
    SHR_INVOKE_VERIFY_DNXC(dnx_crps_mgmt_slim_database_avilable_verify(unit, database));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_counter_interface_set_conter_format_verify(
    int unit,
    bcm_stat_counter_database_t * database,
    bcm_stat_counter_format_type_t format_type,
    bcm_stat_counter_interface_type_t interface_source,
    int counter_size)
{

    SHR_FUNC_INIT_VARS(unit);

    if (format_type < bcmStatCounterFormatPacketsAndBytes || format_type >= bcmStatCounterFormatCount)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect format_type=%d\n", format_type);
    }

    if (!dnx_data_crps.engine.counter_format_types_get(unit, format_type)->valid)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect format_type=%d\n", format_type);
    }

    if (format_type == bcmStatCounterFormatSlimPacketsAndBytes &&
        dnx_data_crps.eviction.supported_eviction_destination_get(unit, bcmStatEvictionDestinationNetwork)->valid)
    {
        SHR_INVOKE_VERIFY_DNXC(dnx_crps_mgmt_counter_interface_set_slim_format_for_network_eviction_verify
                               (unit, database));
    }

    if (format_type == bcmStatCounterFormatTimestamp &&
        (interface_source != bcmStatCounterInterfaceIngressOam && interface_source != bcmStatCounterInterfaceEgressOam))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect format_type=%d for interface_source=%d\n", format_type,
                     interface_source);
    }

    /** State counters formats validation */
    if (DNX_CRPS_COUNTER_FORMAT_TYPE_IS_STATE(format_type))
    {
        if (interface_source != bcmStatCounterInterfaceIngressPMF)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect format_type=%d for interface_source=%d\n", format_type,
                         interface_source);
        }

        /** Validate the given counter-size is supported for the given state-counters-type */
        if (counter_size > dnx_data_crps.state_counters.max_wide_state_counters_size_get(unit) ||
            !dnx_data_crps.state_counters.counter_size_per_format_type_get(unit, format_type, counter_size)->valid)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect counter_size=%d for format_type=%d\n", counter_size, format_type);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_counter_interface_set_conter_mode_verify(
    int unit,
    bcm_stat_counter_mode_t mode,
    bcm_stat_counter_format_type_t format_type)
{

    SHR_FUNC_INIT_VARS(unit);

    if (format_type == bcmStatCounterFormatWideState)
    {
        if (mode < bcmStatCounterModeNone || mode >= bcmStatCounterModeCount)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect mode=%d, for format_type=%d \n", mode, format_type);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_counter_interface_counter_set_size_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_interface_t * config)
{

    int set_idx, counter_set_size, nof_counter_sets;
    SHR_FUNC_INIT_VARS(unit);

    nof_counter_sets =
        (flags & BCM_STAT_COUNTER_MULTI_SETS_DATABASE) ? dnx_data_crps.engine.max_nof_counter_sets_get(unit) : 1;

    for (set_idx = 0; set_idx < nof_counter_sets; set_idx++)
    {
        counter_set_size =
            (flags & BCM_STAT_COUNTER_MULTI_SETS_DATABASE) ? config->set_config[set_idx].
            set_size : config->counter_set_size;

        /** check valid counter set size*/
        if (counter_set_size > dnx_data_crps.engine.max_counter_set_size_get(unit) || counter_set_size < 1)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect counter_set_size=%d, possible values 1 until 32 \n",
                         counter_set_size);
        }

        /** check valid counter_set_size for OAM source */
        if (DNX_CRPS_MGMT_SOURCE_IS_OAM(unit, config->source)
            && counter_set_size != dnx_data_crps.engine.oam_counter_set_size_get(unit))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "  Incorrect counter_set_size=%d, for OAM sources is supported only counter_set_size=%d \n",
                         counter_set_size, dnx_data_crps.engine.oam_counter_set_size_get(unit));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_counter_interface_type_config_verify(
    int unit,
    bcm_stat_counter_database_t * database,
    bcm_stat_counter_interface_t * config)
{
    int type_idx, core_idx;
    int base_engine;
    bcm_stat_counter_database_t database_types_verify;
    SHR_FUNC_INIT_VARS(unit);

    /** check types - for flag BCM_STAT_COUNTER_MODIFY_RANGE_ONLY
     *  - check only the types are filled correctly */
    for (type_idx = 0; type_idx < BCM_STAT_MAX_NUMBER_OF_OBJECT_TYPES; type_idx++)
    {
        /** check valid value */
        if ((config->type_config[type_idx].valid != 0) && (config->type_config[type_idx].valid != 1))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect valid value for type_config=%d \n",
                         config->type_config[type_idx].valid);
        }

        /** make other checks if type is valid */
        if (config->type_config[type_idx].valid == FALSE)
        {
            continue;
        }

        /** the following sources has only one type supported - type=0 */
        if ((type_idx) > 0 &&
            ((config->source == bcmStatCounterInterfaceIngressVoq) ||
             (config->source == bcmStatCounterInterfaceEgressReceivePp) ||
             (config->source == bcmStatCounterInterfaceEgressReceiveQueue)))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " only type_id=0 is supported for source=%d \n", config->source);
        }

        /** check for positive start and end values */
        if (config->type_config[type_idx].start < 0 || config->type_config[type_idx].end < 0)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         " Incorrect value for start=%d or end=%d - start and end must be positive \n",
                         config->type_config[type_idx].start, config->type_config[type_idx].end);
        }

        /** check for end>=start*/
        if (config->type_config[type_idx].end < config->type_config[type_idx].start)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         " Incorrect value for start=%d or end=%d - end must be bigger (or equal) than start \n",
                         config->type_config[type_idx].start, config->type_config[type_idx].end);
        }

        if ((config->format_type == bcmStatCounterFormatDoublePackets
             || config->format_type == bcmStatCounterFormatMaxSize)
            && (config->type_config[type_idx].object_type_offset % 2) == 1)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         " Incorrect value for object_type_offset=%d - in double entry offset should be even\n",
                         config->type_config[type_idx].object_type_offset);
        }
    }

    DNXCMN_CORES_ITER(unit, database->core_id, core_idx)
    {
        SHR_IF_ERR_EXIT(dnx_crps_db.database.base_engine.get(unit, core_idx, database->database_id, &base_engine));

        database_types_verify.core_id = core_idx;
        database_types_verify.database_id = database->database_id;
        SHR_IF_ERR_EXIT(dnx_crps_mgmt_database_type_ranges_verify(unit, &database_types_verify, base_engine, config));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_nof_counters_per_database_get(
    int unit,
    int database_id,
    int core_id,
    bcm_stat_counter_format_type_t format_type,
    int counter_size,
    int *nof_countrs)
{
    int base_engine, current_engine;
    int nof_counters_per_engine = 0, total_nof_counters = 0;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_crps_db.database.base_engine.get(unit, core_id, database_id, &base_engine));

    current_engine = base_engine;

    while (current_engine != DNX_CRPS_MGMT_ENGINE_INVALID)
    {
        SHR_IF_ERR_EXIT(dnx_crps_mgmt_nof_counters_per_engine
                        (unit, current_engine, format_type, counter_size, &nof_counters_per_engine));

        total_nof_counters += nof_counters_per_engine;

        SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.next_engine_id.get(unit, core_id, current_engine, &current_engine));
    }

    *nof_countrs = total_nof_counters;

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_counter_interface_set_config_verify(
    int unit,
    bcm_stat_counter_format_type_t format_type,
    int counter_size,
    bcm_stat_counter_database_t * database,
    bcm_stat_counter_set_config_t * set_config_arr)
{
    int set_idx, core_idx;
    int nof_counters_in_database = 0, nof_counters_in_sets = 0;
    int nof_stat_ids_in_set = 0;
    SHR_FUNC_INIT_VARS(unit);

    for (set_idx = 0; set_idx < dnx_data_crps.engine.max_nof_counter_sets_get(unit); set_idx++)
    {

        /** check for end>=start*/
        if (set_config_arr[set_idx].end < set_config_arr[set_idx].start)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         " Incorrect value for start=%d or end=%d - end must be bigger (or equal) than start \n",
                         set_config_arr[set_idx].start, set_config_arr[set_idx].end);
        }
    }

    /** Verify set's counters amount */
    {
        /**calculate nof counters in bough sets*/
        for (set_idx = 0; set_idx < dnx_data_crps.engine.max_nof_counter_sets_get(unit); set_idx++)
        {
            nof_stat_ids_in_set +=
                (set_config_arr[set_idx].end - set_config_arr[set_idx].start + 1) * set_config_arr[set_idx].set_size;
        }

        DNXCMN_CORES_ITER(unit, database->core_id, core_idx)
        {
            SHR_IF_ERR_EXIT(dnx_crps_mgmt_nof_counters_per_database_get
                            (unit, database->database_id, core_idx, format_type, counter_size,
                             &nof_counters_in_database));

            if (nof_counters_in_sets > nof_counters_in_database)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Too many counters to config, database's max size is %d, got %d \n",
                             nof_counters_in_database, nof_counters_in_sets);
            }
        }

    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_counter_interface_set_interface_source_verify(
    int unit,
    bcm_stat_counter_interface_type_t interface_source)
{

    SHR_FUNC_INIT_VARS(unit);

    /** check engine source */
    if (interface_source >= bcmStatCounterInterfaceCount || interface_source < 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect interface_source=%d, possible values 0 untill %d \n",
                     interface_source, bcmStatCounterInterfaceCount);
    }

    if (dnx_data_crps.engine.source_base_get(unit, interface_source)->base_val < 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect interface_source=%d \n", interface_source);
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_counter_interface_set_flags_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_interface_t * config)
{

    SHR_FUNC_INIT_VARS(unit);

    SHR_MASK_VERIFY(flags, (BCM_STAT_COUNTER_MODIFY_RANGE_ONLY | BCM_STAT_COUNTER_END_TO_END_LATENCY |
                            BCM_STAT_COUNTER_MULTI_SETS_DATABASE), _SHR_E_PARAM, "Incorrect flags\n");

    /** etpp latency measurements can be made only on specific command_id */
    if ((_SHR_IS_FLAG_SET(flags, BCM_STAT_COUNTER_END_TO_END_LATENCY)) &&
        ((config->command_id != dnx_data_crps.latency.etpp_command_id_get(unit)) ||
         ((config->source != bcmStatCounterInterfaceEgressTransmitPp)
          && config->source != bcmStatCounterInterfaceEgressPp)))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "EGRESS_LATENCY flags is valid only for EgressTransmitPp source and command_id=%d \n",
                     dnx_data_crps.latency.etpp_command_id_get(unit));
    }

    if ((_SHR_IS_FLAG_SET(flags, BCM_STAT_COUNTER_MULTI_SETS_DATABASE)) &&
        !dnx_data_crps.engine.feature_get(unit, dnx_data_crps_engine_multi_sets_is_supported))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported flag BCM_STAT_COUNTER_MULTI_SETS_DATABASE \n");

    }

    /** State counters don't supported for multi-sets database*/
    if ((_SHR_IS_FLAG_SET(flags, BCM_STAT_COUNTER_MULTI_SETS_DATABASE)) &&
        (DNX_CRPS_COUNTER_FORMAT_TYPE_IS_STATE(config->format_type)))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "Unsupported flag BCM_STAT_COUNTER_MULTI_SETS_DATABASE with counter format_type=%d\n",
                     config->format_type);
    }

exit:
    SHR_FUNC_EXIT;

}

/** see .h file */
shr_error_e
dnx_crps_mgmt_counter_interface_set_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_database_t * database,
    bcm_stat_counter_interface_t * config)
{
    int base_engine, core_idx = 0;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(database, _SHR_E_PARAM, "database");
    /** check that database created and specific core_id */
    SHR_INVOKE_VERIFY_DNXC(dnx_crps_mgmt_database_structure_verify(unit, database, TRUE));

    SHR_NULL_CHECK(config, _SHR_E_PARAM, "config");

    SHR_INVOKE_VERIFY_DNXC(dnx_crps_mgmt_counter_interface_set_flags_verify(unit, flags, config));

    /** check that at least one engine is attached to the database, */
    DNXCMN_CORES_ITER(unit, database->core_id, core_idx)
    {
        /** otherwise, you don't have engine that holds the sw_state configuration  */
        SHR_IF_ERR_EXIT(dnx_crps_db.database.base_engine.get(unit, core_idx, database->database_id, &base_engine));
        if (base_engine == DNX_CRPS_MGMT_ENGINE_INVALID)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "No engines attached to the database. attach engines before calling this API \n");
        }

    }

    if ((flags & BCM_STAT_COUNTER_MODIFY_RANGE_ONLY) == FALSE)
    {
        /** validate that interface source is supported */
        SHR_INVOKE_VERIFY_DNXC(dnx_crps_mgmt_counter_interface_set_interface_source_verify(unit, config->source));

        /*
         * verify counter format type range
         * verify counter format's validation terms
         */
        SHR_INVOKE_VERIFY_DNXC(dnx_crps_mgmt_counter_interface_set_conter_format_verify
                               (unit, database, config->format_type, config->source, config->counter_size));

        SHR_INVOKE_VERIFY_DNXC(dnx_crps_mgmt_counter_interface_set_conter_mode_verify
                               (unit, config->mode, config->format_type));

        /** check command id*/
        {
            SHR_INVOKE_VERIFY_DNXC(dnx_crps_mgmt_counter_command_id_verify(unit, config->source, config->command_id));
            /** For ITM source - verify the command id and the format as
            *  if regular format/MaxSize was configured on the same
            *  command id - the other cannot be on the same command id */
            if (config->source == bcmStatCounterInterfaceIngressVoq)
            {
                SHR_INVOKE_VERIFY_DNXC(dnx_crps_mgmt_itm_format_command_id_verify
                                       (unit, database, config->command_id, config->format_type));
            }
        }

        /** check counter set size*/
        SHR_INVOKE_VERIFY_DNXC(dnx_crps_mgmt_counter_interface_counter_set_size_verify(unit, flags, config));
    }

    /** Stat-id range validation*/
    if (flags & BCM_STAT_COUNTER_MULTI_SETS_DATABASE)
    {

        if (!dnx_data_crps.engine.feature_get(unit, dnx_data_crps_engine_multi_sets_is_supported))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Multi sets database does not supported for this device \n");
        }

        SHR_INVOKE_VERIFY_DNXC(dnx_crps_mgmt_counter_interface_set_config_verify
                               (unit, config->format_type, config->counter_size, database, config->set_config));

    }
    else
    {
        SHR_INVOKE_VERIFY_DNXC(dnx_crps_mgmt_counter_interface_type_config_verify(unit, database, config));
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_mgmt_counter_interface_get_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_database_t * database,
    bcm_stat_counter_interface_t * config)
{
    int base_engine, core_id;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(database, _SHR_E_PARAM, "database");
    SHR_NULL_CHECK(config, _SHR_E_PARAM, "config");

    /** check for valid flags value */
    SHR_MASK_VERIFY(flags, (BCM_STAT_COUNTER_MODIFY_RANGE_ONLY | BCM_STAT_COUNTER_MULTI_SETS_DATABASE),
                    _SHR_E_PARAM, "Incorrect flags\n");

    if ((_SHR_IS_FLAG_SET(flags, BCM_STAT_COUNTER_MULTI_SETS_DATABASE)) &&
        !dnx_data_crps.engine.feature_get(unit, dnx_data_crps_engine_multi_sets_is_supported))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported flag BCM_STAT_COUNTER_MULTI_SETS_DATABASE \n");
    }

    /** verify the database is valid */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_database_structure_verify(unit, database, TRUE));
    core_id = (database->core_id == BCM_CORE_ALL) ? 0 : database->core_id;
    SHR_IF_ERR_EXIT(dnx_crps_db.database.base_engine.get(unit, core_id, database->database_id, &base_engine));
    if (base_engine == DNX_CRPS_MGMT_ENGINE_INVALID)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "No engines attached to the database. can't get the configuration \n");
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_set_size_get(
    int unit,
    int core_id,
    int database_id,
    int set_id,
    int *counter_set_size)
{
    int base_engine_id;
    SHR_FUNC_INIT_VARS(unit);

    /** Consider the database as single set database */
    if (set_id == DNX_CRPS_MGMT_SET_INVALID)
    {
        /** get the base_engine_id in database */
        SHR_IF_ERR_EXIT(dnx_crps_db.database.base_engine.get(unit, core_id, database_id, &base_engine_id));

        /** Get counter-set size*/
        SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.
                        counter_set_size.get(unit, core_id, base_engine_id, counter_set_size));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_crps_db.database.set.size.get(unit, core_id, database_id, set_id, counter_set_size));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_counter_set_mapping_full_spread_verify(
    int unit,
    uint32 flags,
    int core_id,
    int database_id,
    int nof_entries_to_map)
{
    int is_multi_sets_database, counter_set_size;
    SHR_FUNC_INIT_VARS(unit);

    if (!_SHR_IS_FLAG_SET(flags, BCM_STAT_COUNTER_MAPPING_FULL_SPREAD))
    {
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(dnx_crps_mgmt_is_multi_sets_database(unit, core_id, database_id, &is_multi_sets_database));
    if (is_multi_sets_database)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect flag BCM_STAT_COUNTER_MAPPING_FULL_SPREAD for multi-sets database");
    }

    SHR_IF_ERR_EXIT(dnx_crps_set_size_get(unit, core_id, database_id, DNX_CRPS_MGMT_SET_INVALID, &counter_set_size));
    if (counter_set_size < nof_entries_to_map)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "Incorrect flag BCM_STAT_COUNTER_MAPPING_FULL_SPREAD when counter set size is smaller then the nof_entries parameter");
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_mgmt_counter_set_mapping_set_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_database_t * database,
    bcm_stat_counter_set_map_t * counter_set_map)
{
    int base_engine_id = 0, core_idx;
    int key_id = 0, command_id = 0;
    int expansion_element_id = 0, counter_set_size = 0;
    int nof_bits_per_type = 0, max_value_per_type = 0;
    int data_mapping_set, is_multi_sets_database;
    bcm_stat_counter_interface_type_t interface_source;

    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(database, _SHR_E_PARAM, "database");
    SHR_NULL_CHECK(counter_set_map, _SHR_E_PARAM, "counter_set_map");

    /** verify flags variable */
    SHR_MASK_VERIFY(flags, (BCM_STAT_COUNTER_MAPPING_FULL_SPREAD), _SHR_E_PARAM, "Incorrect flags\n");

    /** verify database structure */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_database_structure_verify(unit, database, TRUE));

    DNXCMN_CORES_ITER(unit, database->core_id, core_idx)
    {
        /** get the base_engine_id in database */
        SHR_IF_ERR_EXIT(dnx_crps_db.database.base_engine.get(unit, core_idx, database->database_id, &base_engine_id));

        /** check that at least one engine attached to the database */
        if (base_engine_id == DNX_CRPS_MGMT_ENGINE_INVALID)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " database_id=%d, core_id=%d do not have any engine attach \n",
                         database->database_id, core_idx);
        }

        /** check that counter_set_size were already configured */
        SHR_IF_ERR_EXIT(dnx_crps_mgmt_is_multi_sets_database
                        (unit, core_idx, database->database_id, &is_multi_sets_database));
        SHR_IF_ERR_EXIT(dnx_crps_set_size_get
                        (unit, core_idx, database->database_id,
                         is_multi_sets_database ? 0 : DNX_CRPS_MGMT_SET_INVALID, &counter_set_size));

        if (counter_set_size == DNX_CRPS_MGMT_ENGINE_FIELDS_INVALID)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "counter_set_size was not configured yet. call bcm_stat_counter_interface_set API first \n");
        }

        /** Full spread flags validation terms */
        SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_set_mapping_full_spread_verify
                        (unit, flags, core_idx, database->database_id, counter_set_map->nof_entries));

        /** verify counter_set_map */
        /** verify valid nof entries */
        if (counter_set_map->nof_entries < 0
            || counter_set_map->nof_entries > dnx_data_crps.engine.data_mapping_table_size_get(unit))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect nof_entries=%d\n, should be between 0 and %d",
                         counter_set_map->nof_entries, dnx_data_crps.engine.data_mapping_table_size_get(unit));
        }
        /** verify expansion data mapping is not null */
        if (counter_set_map->nof_entries > 0)
        {
            SHR_NULL_CHECK(counter_set_map->expansion_data_mapping, _SHR_E_PARAM, "expansion_data_mapping");
        }
        for (expansion_element_id = 0; expansion_element_id < counter_set_map->nof_entries; expansion_element_id++)
        {
            /** verify correct nof key conditions */
            if (counter_set_map->expansion_data_mapping[expansion_element_id].nof_key_conditions < 0
                || counter_set_map->expansion_data_mapping[expansion_element_id].nof_key_conditions >=
                BCM_STAT_MAX_NOF_EXPANSION_KEY_ELEMENTS)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect nof_key_conditions=%d",
                             counter_set_map->expansion_data_mapping->nof_key_conditions);
            }

            /**Get the current counter set size*/
            data_mapping_set = is_multi_sets_database ?
                counter_set_map->expansion_data_mapping[expansion_element_id].value.set_id : DNX_CRPS_MGMT_SET_INVALID;

            /** verify valid value counter set offset */
            if (is_multi_sets_database)
            {
                if (counter_set_map->expansion_data_mapping[expansion_element_id].value.set_id < 0 ||
                    counter_set_map->expansion_data_mapping[expansion_element_id].value.set_id >
                    dnx_data_crps.engine.max_nof_counter_sets_get(unit))
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect set_id=%d, should be between 0 and %d", data_mapping_set,
                                 dnx_data_crps.engine.max_nof_counter_sets_get(unit));

                }
            }

            SHR_IF_ERR_EXIT(dnx_crps_set_size_get
                            (unit, core_idx, database->database_id, data_mapping_set, &counter_set_size));

            if (counter_set_map->expansion_data_mapping[expansion_element_id].value.counter_set_offset < 0
                || counter_set_map->expansion_data_mapping[expansion_element_id].value.counter_set_offset >
                counter_set_size)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect counter_set_offset=%d, should be between 0 and %d",
                             counter_set_map->expansion_data_mapping[expansion_element_id].value.counter_set_offset,
                             counter_set_size);
            }

            /** verify valid value */
            if (counter_set_map->expansion_data_mapping[expansion_element_id].value.valid != 0
                && counter_set_map->expansion_data_mapping[expansion_element_id].value.valid != 1)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             " Incorrect counter_set_map->expansion_data_mapping->value.valid=%d, should be 0 or 1",
                             counter_set_map->expansion_data_mapping[expansion_element_id].value.valid);
            }
            /** get source and command id*/
            SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.src_type.get(unit, core_idx, base_engine_id, &interface_source));
            SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.command_id.get(unit, core_idx, base_engine_id, &command_id));
            /** For OAM sources - verify that nof_entries is 1, there are
             *  no key conditions and as counter_set_size is 1 - there is
             *  one offset that is valid - offset 0  */
            if (DNX_CRPS_MGMT_SOURCE_IS_OAM(unit, interface_source))
            {
                if (counter_set_map->nof_entries != 1)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM,
                                 " Incorrect counter_set_map->nof_entries=%d, should be 1 for OAM sources",
                                 counter_set_map->nof_entries);
                }
                if (counter_set_map->expansion_data_mapping[0].nof_key_conditions != 0)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM,
                                 " Incorrect counter_set_map->expansion_data_mapping[0].nof_key_conditions=%d, should be 0 for OAM sources - no keys configuration",
                                 counter_set_map->expansion_data_mapping[0].nof_key_conditions);
                }
                /** valid=TRUE/FALSE  and offset is verified according to
                 *  counter set size for all sources */
            }
            /** verify valid keys */
            for (key_id = 0; key_id < counter_set_map->expansion_data_mapping[expansion_element_id].nof_key_conditions;
                 key_id++)
            {
                /*
                 * validate that the current key type in range 
                 */
                if ((int) (counter_set_map->expansion_data_mapping[expansion_element_id].key[key_id].type) < 0
                    || counter_set_map->expansion_data_mapping[expansion_element_id].key[key_id].type >=
                    bcmStatExpansionTypeMax)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect key.type=%d for key with id=%d",
                                 counter_set_map->expansion_data_mapping[expansion_element_id].key[key_id].type,
                                 key_id);
                }
                /*
                 * validate that the current key type is supported for the current source 
                 */
                if (dnx_data_crps.expansion.source_metadata_types_get(unit, interface_source,
                                                                      counter_set_map->expansion_data_mapping
                                                                      [expansion_element_id].key[key_id].
                                                                      type)->nof_bits <= 0)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM,
                                 " Incorrect key.type=%d for key with id=%d - not valid type for the given source=%d",
                                 counter_set_map->expansion_data_mapping[expansion_element_id].key[key_id].type, key_id,
                                 interface_source);
                }
                /** verify key value fits in the max value allowed for this type */
                nof_bits_per_type =
                    dnx_data_crps.expansion.source_metadata_types_get(unit, interface_source,
                                                                      counter_set_map->expansion_data_mapping
                                                                      [expansion_element_id].key[key_id].
                                                                      type)->nof_bits;
                max_value_per_type = (1 << nof_bits_per_type) - 1;
                if (counter_set_map->expansion_data_mapping[expansion_element_id].key[key_id].value > max_value_per_type
                    || counter_set_map->expansion_data_mapping[expansion_element_id].key[key_id].value < 0)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM,
                                 " Incorrect key.value=%d for key with id=%d - does not fit in the type allowed bits",
                                 counter_set_map->expansion_data_mapping[expansion_element_id].key[key_id].value,
                                 key_id);
                }
            }
        }
    }
    /** verify all keys are part of the expansion  - no need because it is checked during the implementation */
exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_mgmt_counter_set_mapping_get_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_database_t * database,
    bcm_stat_counter_set_map_t * counter_set_map)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(database, _SHR_E_PARAM, "database");
    SHR_NULL_CHECK(counter_set_map, _SHR_E_PARAM, "counter_set_map");
    if (counter_set_map->nof_entries != 0)
    {
        SHR_NULL_CHECK(counter_set_map->expansion_data_mapping, _SHR_E_PARAM,
                       "counter_set_map->expansion_data_mapping");
    }
    /** check for valid flags value */
    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect flags=%d\n, no flags are supported for this API", flags);
    }
    /** verify the engine is valid */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_database_structure_verify(unit, database, TRUE));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_counter_eviction_network_is_free_event_id_verify(
    int unit,
    int core_idx,
    bcm_stat_eviction_t * eviction,
    int engine_id)
{
    bcm_eviction_destination_type_t curr_eviction_type;
    int curr_engine_id, curr_database_id, curr_event_id, database_id;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.database_id.get(unit, core_idx, engine_id, &database_id));

    /*
     * Go over all C-type engines and check if some other Slim database gets the current event_id
     */
    for (curr_engine_id = FIRST_C_ENGINE_ID(unit); curr_engine_id < dnx_data_crps.engine.nof_engines_get(unit);
         curr_engine_id++)
    {

        SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.database_id.get(unit, core_idx, curr_engine_id, &curr_database_id));

        /*
         * Engines from the same database allowed to use the same event_id 
         */
        if (curr_database_id == database_id)
        {
            continue;
        }

        SHR_IF_ERR_EXIT(dnx_crps_db.proc.eviction.
                        eviction_type.get(unit, core_idx, curr_engine_id, &curr_eviction_type));
        dnx_crps_db.proc.eviction.eviction_event_id.get(unit, core_idx, curr_engine_id, &curr_event_id);

        /*
         * The event_id needs to be unique for Slim database only 
         */
        if (curr_eviction_type == bcmStatEvictionDestinationNetwork && curr_event_id == eviction->eviction_event_id)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "event_id=%d allredy allocated for database=%d\n",
                         eviction->eviction_event_id, curr_database_id);
        }

    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_counter_eviction_network_event_id_range_verify(
    int unit,
    int core_idx,
    bcm_stat_eviction_t * eviction,
    int engine_id)
{
    SHR_FUNC_INIT_VARS(unit);

    /** for C-type engine, event_id from 0 to 7 */
    if (eviction->eviction_event_id < 0 || eviction->eviction_event_id > 7)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "Iligal eviction_event_id=%d for engine=%d\n", eviction->eviction_event_id, engine_id);

    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_counter_eviction_network_engine_type_verify(
    int unit,
    int core_idx,
    int engine_id)
{
    bcm_stat_counter_format_type_t format;
    bcm_eviction_destination_type_t parallel_eviction_type;
    int parallel_engine_id;
    int nof_crps_ire_channels;
    SHR_FUNC_INIT_VARS(unit);

    /** C-type engine allowed to use network eviction with Slim format only */
    if (IS_C_TYPE_ENGINE(unit, engine_id))
    {
        SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.format.get(unit, core_idx, engine_id, &format));
        if (format != bcmStatCounterFormatSlimPacketsAndBytes)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "Network eviction is not supported for engine=%d with format=%d \n", engine_id, format);
        }

    }
    else
    {
        nof_crps_ire_channels = dnx_data_crps.eviction.nof_crps_network_channels_get(unit);

        /** A/B-type engine allowed to use network eviction if the parallel one doesn't */
        parallel_engine_id =
            (IS_A_TYPE_ENGINE(unit, engine_id)) ? engine_id + nof_crps_ire_channels : engine_id - nof_crps_ire_channels;

        SHR_IF_ERR_EXIT(dnx_crps_db.proc.eviction.
                        eviction_type.get(unit, core_idx, parallel_engine_id, &parallel_eviction_type));

        if (parallel_eviction_type == bcmStatEvictionDestinationNetwork)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "Network eviction is not supported for engine=%d, engine=%d use Network eviction\n",
                         engine_id, parallel_engine_id);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_counter_eviction_network_crps_port_verify(
    int unit,
    int core_idx)
{
    bcm_pbmp_t crps_ports;
    int nof_crps_ports;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_port_logicals_get(unit, core_idx, DNX_ALGO_PORT_LOGICALS_TYPE_CRPS, 0, &crps_ports));
    BCM_PBMP_COUNT(crps_ports, nof_crps_ports);

    if (nof_crps_ports != 1)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Cannot use network eviction, one CRPS port is required \n");
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_counter_eviction_parameters_destination_type_verify(
    int unit,
    int core_idx,
    bcm_stat_eviction_t * eviction,
    int engine_id)
{
    bcm_stat_counter_format_type_t format;
    SHR_FUNC_INIT_VARS(unit);

    /*
     *  eviction type in range
     */
    if (!dnx_data_crps.eviction.supported_eviction_destination_get(unit, eviction->type)->valid)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect eviction type=%d \n", eviction->type);
    }

    SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.format.get(unit, core_idx, engine_id, &format));

    /*
     * validate the eviction type supported for the engine's counter format
     */
    if (!dnx_crps_mgmt_eviction_destination_for_format_type_is_supported(unit, format, eviction->type))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "Cannot use eviction destination=%d with counter_format=%d\n", eviction->type, format);
    }

    if (eviction->type == bcmStatEvictionDestinationNetwork)
    {

        /*
         * verify crps port is allocated
         */
        SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_eviction_network_crps_port_verify(unit, core_idx));

        /*
         * for C-type engine, verify counter format is Slim for A/B-type engine, verify the parallel is not evict to the
         * network
         */
        SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_eviction_network_engine_type_verify(unit, core_idx, engine_id));

        SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.format.get(unit, core_idx, engine_id, &format));

        if (format == bcmStatCounterFormatSlimPacketsAndBytes)
        {
            /*
             * for Slim counters, event_id express the crps_ire_channel
             */

            /*
             * verify the current event_id is not configured for anther slim database
             */
            SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_eviction_network_is_free_event_id_verify
                            (unit, core_idx, eviction, engine_id));

            /*
             * verify 0 <= event_id < nof_crps_ire_channel
             */
            SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_eviction_network_event_id_range_verify
                            (unit, core_idx, eviction, engine_id));

            /*
             * Slim counters can be evicted with LFSR scan only
             */
            if (eviction->eviction_algorithmic_disable)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Unssuported eviction_algorithmic_disable for Slime counter format\n");
            }

        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_stat_eviction_parameter_verify(
    int unit,
    int engine_id,
    int core_idx,
    bcm_stat_eviction_t * eviction)
{
    bcm_stat_counter_format_type_t format;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_eviction_parameters_destination_type_verify
                    (unit, core_idx, eviction, engine_id));

    /** for local host the format must be physical */
    if (eviction->record_format != bcmStatEvictionRecordFormatPhysical)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     " Incorrect eviction record format=%d, when eviction type is LocalHost format must be Physical \n",
                     eviction->record_format);
    }

    /** check algorithmic eviction is correctly disabled/enabled */
    if (eviction->eviction_algorithmic_disable != 0 && eviction->eviction_algorithmic_disable != 1)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     " Incorrect eviction algorithmic disable =%d, valid values - ENABLE=1 / DISABLE=0 \n",
                     eviction->eviction_algorithmic_disable);
    }

    /** LFSR is not supported for full wide counter format */
    if (eviction->eviction_algorithmic_disable == 0 &&
        dnx_data_crps.eviction.feature_get(unit, dnx_data_crps_eviction_probabilistic_is_supported))
    {
        SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.format.get(unit, core_idx, engine_id, &format));
        if (format == bcmStatCounterFormatPackets || format == bcmStatCounterFormatBytes
            || format == bcmStatCounterFormatTimestamp)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "Cannot use algorithmic scan for engine=%d, the algorithmic scan is not supported for format=%d\n",
                         engine_id, format);
        }
    }

    /** Thus parameters are not relevant for network eviction type */
    else
    {
        /** verify dma fifo */
        if (eviction->dma_fifo_select < 0
            || eviction->dma_fifo_select >= dnx_data_crps.eviction.nof_counters_fifo_get(unit))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect dma fifo=%d \n", eviction->dma_fifo_select);
        }

    }

exit:
    SHR_FUNC_EXIT;

}

/** see .h file */
shr_error_e
dnx_crps_mgmt_counter_database_eviction_get_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_database_t * database,
    bcm_stat_eviction_t * eviction)
{
    int engine_id, core_idx;
    SHR_FUNC_INIT_VARS(unit);
    SHR_MASK_VERIFY(flags, (BCM_STAT_EVICTION_CONDITIONAL_ENABLE), _SHR_E_PARAM, "Incorrect flags\n");
    SHR_NULL_CHECK(database, _SHR_E_PARAM, "database");
    SHR_NULL_CHECK(database, _SHR_E_PARAM, "eviction");

    /** check that database is allocated and specific core_id */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_database_structure_verify(unit, database, TRUE));

    DNXCMN_CORES_ITER(unit, database->core_id, core_idx)
    {
        /** check that at least one engine is attached to the database, */
        /** otherwise, you don't have engine that holds the sw_state configuration  */
        SHR_IF_ERR_EXIT(dnx_crps_db.database.base_engine.get(unit, core_idx, database->database_id, &engine_id));
        if (engine_id == DNX_CRPS_MGMT_ENGINE_INVALID)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "No engines attached to the database. attach engines before calling this API \n");
        }
    }

exit:
    SHR_FUNC_EXIT;
}
static shr_error_e
dnx_crps_mgmt_all_engines_same_format(
    int unit,
    int engine_id,
    int core_idx,
    bcm_stat_eviction_t * eviction)
{
    int engine_database_idx = 0, database_id_get = 0, valid_engine = 0;
    int engine_idx;
    bcm_eviction_record_format_t record_format_get;

    SHR_FUNC_INIT_VARS(unit);
    /** check that all engines belonging to the same database
     *  have the same record format */
    SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.database_id.get(unit, core_idx, engine_id, &engine_database_idx));
    for (engine_idx = 0; engine_idx < dnx_data_crps.engine.nof_engines_get(unit); engine_idx++)
    {
        DNX_CRPS_MGMT_ENGINE_VALID_GET(unit, core_idx, engine_id, valid_engine);
        if (valid_engine)
        {
            SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.database_id.get(unit, core_idx, engine_idx, &database_id_get));
            /** belong to the same DB */
            if (engine_database_idx == database_id_get)
            {
                SHR_IF_ERR_EXIT(dnx_crps_db.proc.eviction.
                                record_format.get(unit, core_idx, engine_idx, &record_format_get));
                if (record_format_get != eviction->record_format)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM,
                                 " Incorrect eviction record format=%d, should be the same for all concatenated engines \n",
                                 eviction->record_format);
                }
            }
        }
    }
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_stat_engine_verify(
    int unit,
    bcm_stat_engine_t * engine,
    int core_idx,
    bcm_stat_eviction_t * eviction)
{
    int started = 0;
    int valid_engine = 0;
    int dma_fifo, eviction_event_id;
    bcm_eviction_destination_type_t eviction_type;
    bcm_eviction_record_format_t record_format;
    SHR_FUNC_INIT_VARS(unit);
    /** verify the engine is valid*/
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_engine_structure_verify(unit, engine, TRUE));
    /** part of configuration cannot be changed if engine is active */
    DNX_CRPS_MGMT_ENGINE_VALID_GET(unit, core_idx, engine->engine_id, valid_engine);
    if (valid_engine)
    {
        /** only the following fields cannot be changed */
        dnx_crps_db.proc.eviction.dma_fifo.get(unit, core_idx, engine->engine_id, &dma_fifo);
        dnx_crps_db.proc.eviction.eviction_type.get(unit, core_idx, engine->engine_id, &eviction_type);
        dnx_crps_db.proc.eviction.record_format.get(unit, core_idx, engine->engine_id, &record_format);
        dnx_crps_db.proc.eviction.eviction_event_id.get(unit, core_idx, engine->engine_id, &eviction_event_id);
        if ((dma_fifo != eviction->dma_fifo_select) || (eviction_type != eviction->type)
            || (record_format != eviction->record_format) || (eviction_event_id != eviction->eviction_event_id))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "Incorrect call of bcm_stat_counter_eviction_set - engine with engine id=%d and core=%d is already active and configuration cannot be changes",
                         engine->engine_id, core_idx);
        }
    }
    else
    {
        /** verify that attach API has already been called as it
         *  is the 1st one in the sequence */
        SHR_IF_ERR_EXIT(dnx_crps_db.proc.config_started.get(unit, core_idx, engine->engine_id, &started));
        if (!started)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         " Incorrect call of bcm_stat_counter_eviction_set - should call bcm_stat_counter_engine_attach first- for engine with engine id=%d and core=%d",
                         engine->engine_id, core_idx);
        }
    }
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_stat_eviction_conditional_verify(
    int unit,
    uint32 flags,
    int engine_id,
    int core_idx,
    bcm_stat_eviction_t * eviction)
{
    uint32 temp_action_flags[1], index;
    const dnx_data_crps_eviction_condional_action_valid_t *action_valid;
    bcm_stat_counter_format_type_t format;
    SHR_FUNC_INIT_VARS(unit);
    /** check conditional eviction */
    if (_SHR_IS_FLAG_SET(flags, BCM_STAT_EVICTION_CONDITIONAL_ENABLE))
    {
        /** check feature supported*/
        if (dnx_data_crps.eviction.feature_get(unit, dnx_data_crps_eviction_conditional_action_is_supported) == 0)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " flag BCM_STAT_EVICTION_CONDITIONAL_ENABLE not supported for this device\n");
        }
        SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.format.get(unit, core_idx, engine_id, &format));
        if (_SHR_IS_FLAG_SET(eviction->cond.action_flags, BCM_STAT_EVICTION_CONDITIONAL_ACTION_RESET_COUNTER)
            && (format != bcmStatCounterFormatDoublePackets))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "conditional action RESET_COUNTER is not supported for counter format=%d \n",
                         bcmStatCounterFormatDoublePackets);
        }
        /** verify that actions is valid for the current device */
        temp_action_flags[0] = eviction->cond.action_flags;
        index = 0;
        while (temp_action_flags[0] != 0)
        {
            if (SHR_BITGET(temp_action_flags, index))
            {
                action_valid = dnx_data_crps.eviction.condional_action_valid_get(unit, index);
                if ((action_valid->valid) == FALSE)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "action %d not supported for this device\n", (1 << index));
                }
            }
            SHR_BITCLR(temp_action_flags, index);
            index++;
        }
    }
exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_mgmt_counter_database_eviction_set_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_database_t * database,
    bcm_stat_eviction_t * eviction)
{
    bcm_stat_engine_t engine;
    int engine_id, core_idx;
    SHR_FUNC_INIT_VARS(unit);
    SHR_MASK_VERIFY(flags, (BCM_STAT_EVICTION_CONDITIONAL_ENABLE), _SHR_E_PARAM, "Incorrect flags\n");
    SHR_NULL_CHECK(database, _SHR_E_PARAM, "database");
    SHR_NULL_CHECK(database, _SHR_E_PARAM, "eviction");

    /** check that database is allocated and specific core_id */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_database_structure_verify(unit, database, TRUE));

    DNXCMN_CORES_ITER(unit, database->core_id, core_idx)
    {
        /** check that at least one engine is attached to the database, */
        /** otherwise, you don't have engine that holds the sw_state configuration  */
        SHR_IF_ERR_EXIT(dnx_crps_db.database.base_engine.get(unit, core_idx, database->database_id, &engine_id));
        if (engine_id == DNX_CRPS_MGMT_ENGINE_INVALID)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "No engines attached to the database. attach engines before calling this API \n");
        }
        engine.core_id = core_idx;
        engine.engine_id = engine_id;

        /** check all engines belong to the same database have same format*/
        SHR_IF_ERR_EXIT(dnx_crps_mgmt_all_engines_same_format(unit, engine_id, core_idx, eviction));

        /**verify eviction parameters are valid*/
        SHR_IF_ERR_EXIT(dnx_crps_mgmt_stat_eviction_parameter_verify(unit, engine_id, core_idx, eviction));

        /** check conditional eviction */
        SHR_IF_ERR_EXIT(dnx_crps_mgmt_stat_eviction_conditional_verify(unit, flags, engine_id, core_idx, eviction));

        /** check all engins are valid*/
        while (engine_id != DNX_CRPS_MGMT_ENGINE_INVALID)
        {
            engine.engine_id = engine_id;
            SHR_IF_ERR_EXIT(dnx_crps_mgmt_stat_engine_verify(unit, &engine, core_idx, eviction));

            SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.next_engine_id.get(unit, core_idx, engine_id, &engine_id));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_mgmt_counter_eviction_set_verify(
    int unit,
    uint32 flags,
    bcm_stat_engine_t * engine,
    bcm_stat_eviction_t * eviction)
{
    int core_idx;
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(engine, _SHR_E_PARAM, "engine");
    SHR_NULL_CHECK(eviction, _SHR_E_PARAM, "eviction");
    SHR_MASK_VERIFY(flags, (BCM_STAT_EVICTION_CONDITIONAL_ENABLE), _SHR_E_PARAM, "Incorrect flags\n");

    DNXCMN_CORES_ITER(unit, engine->core_id, core_idx)
    {
        /** verify the engine is valid*/
        SHR_IF_ERR_EXIT(dnx_crps_mgmt_stat_engine_verify(unit, engine, core_idx, eviction));

        /**verify eviction parameters are valid*/
        SHR_IF_ERR_EXIT(dnx_crps_mgmt_stat_eviction_parameter_verify(unit, engine->engine_id, core_idx, eviction));

        /** check conditional eviction */
        SHR_IF_ERR_EXIT(dnx_crps_mgmt_stat_eviction_conditional_verify
                        (unit, flags, engine->engine_id, core_idx, eviction));

        /** check all engines belong to the same database have same format*/
        SHR_IF_ERR_EXIT(dnx_crps_mgmt_all_engines_same_format(unit, engine->engine_id, core_idx, eviction));
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_mgmt_counter_eviction_get_verify(
    int unit,
    uint32 flags,
    bcm_stat_engine_t * engine,
    bcm_stat_eviction_t * eviction)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(engine, _SHR_E_PARAM, "engine");
    SHR_NULL_CHECK(eviction, _SHR_E_PARAM, "eviction");
    SHR_MASK_VERIFY(flags, (BCM_STAT_EVICTION_CONDITIONAL_ENABLE), _SHR_E_PARAM, "Incorrect flags\n");

    /** verify the engine is valid */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_engine_structure_verify(unit, engine, TRUE));

    /** check conditional eviction */
    if (_SHR_IS_FLAG_SET(flags, BCM_STAT_EVICTION_CONDITIONAL_ENABLE))
    {
        /** check feature supported*/
        if (dnx_data_crps.eviction.feature_get(unit, dnx_data_crps_eviction_conditional_action_is_supported) == 0)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " flag BCM_STAT_EVICTION_CONDITIONAL_ENABLE not supported for this device\n");
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static int
dnx_crps_mgmt_counter_conditional_action_no_eviction_is_supported(
    int unit)
{

    if (dnx_data_crps.eviction.feature_get(unit, dnx_data_crps_eviction_conditional_action_is_supported) && dnx_data_crps.eviction.condional_action_valid_get(unit, 4   /* index 
                                                                                                                                                                         * of 
                                                                                                                                                                         * BCM_STAT_EVICTION_CONDIONAL_ACTION_NO_EVICTION */
        )->valid)
    {
        return TRUE;
    }

    return FALSE;
}

static shr_error_e
dnx_crps_mgmt_counter_conditional_action_no_eviction_is_enable(
    int unit,
    int core_id,
    int engine_id,
    uint32 *is_enable)
{
    uint32 conditional_action_is_enable, action_no_eviction_is_enable;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_crps_mgmt_conditional_action_enable_get
                    (unit, core_id, engine_id, &conditional_action_is_enable));

    SHR_IF_ERR_EXIT(dnx_crps_mgmt_conditional_action_no_eviction_get
                    (unit, core_id, engine_id, &action_no_eviction_is_enable));

    if (conditional_action_is_enable && action_no_eviction_is_enable)
    {
        *is_enable = TRUE;
    }
    else
    {
        *is_enable = FALSE;
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_mgmt_counter_database_enable_set_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_database_t * database,
    bcm_stat_counter_enable_t * enable)
{
    int base_engine_id, core_idx;
    int rate_calculation_is_enable = FALSE;
    uint32 action_no_eviction_is_enable = FALSE;
    bcm_stat_counter_interface_type_t engine_source;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(database, _SHR_E_PARAM, "database");
    SHR_NULL_CHECK(enable, _SHR_E_PARAM, "enable");
    /** check for valid flags value */
    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect flags=%d\n", flags);
    }
    /** verify the database is valid */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_database_structure_verify(unit, database, TRUE));
    DNXCMN_CORES_ITER(unit, database->core_id, core_idx)
    {
        /** get the base_engine_id in database */
        SHR_IF_ERR_EXIT(dnx_crps_db.database.base_engine.get(unit, core_idx, database->database_id, &base_engine_id));

        /** check that at least one engine attached to the database */
        if (base_engine_id == DNX_CRPS_MGMT_ENGINE_INVALID)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " database_id=%d, core_id=%d do not have any engine attach \n",
                         database->database_id, core_idx);
        }

        /** verify enable */
        if (enable->enable_counting != TRUE && enable->enable_counting != FALSE)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect enable_counting=%d\n, possible values - 0 or 1",
                         enable->enable_counting);
        }
        if (enable->enable_eviction != TRUE && enable->enable_eviction != FALSE)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect enable_eviction=%d\n, possible values - 0 or 1",
                         enable->enable_eviction);
        }

        /** verify that eviction cannot be enabled if the source is OAM */
        /** get the source type */
        SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.src_type.get(unit, core_idx, base_engine_id, &engine_source));
        /** check for correct source - if no eviction, can't read counters E-OAM  */
        if ((engine_source == bcmStatCounterInterfaceEgressOam) && enable->enable_eviction == TRUE)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "  Incorrect enable_eviction=%d, for source=%d eviction cannot be enabled\n",
                         enable->enable_eviction, engine_source);
        }

        /** Verify that rate calculation and skip eviction don't enabled together */
        {
            /** Get whether or not rate calculation is enable*/
            if (dnx_data_crps.general.feature_get(unit, dnx_data_crps_general_crps_rate_calculation_support))
            {
                SHR_IF_ERR_EXIT(dnx_crps_db.proc.rate.rate_calculation_enable.get(unit, core_idx, base_engine_id,
                                                                                  &rate_calculation_is_enable));
            }

            /** Get whether or not skip eviction is enable*/
            if (dnx_crps_mgmt_counter_conditional_action_no_eviction_is_supported(unit))
            {
                SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_conditional_action_no_eviction_is_enable(unit, core_idx,
                                                                                               base_engine_id,
                                                                                               &action_no_eviction_is_enable));
            }

            if (enable->enable_eviction && rate_calculation_is_enable && action_no_eviction_is_enable)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Incorrect configuration, Rate calculation cann't be used with skip eviction action");

            }

        }
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_mgmt_counter_database_enable_get_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_database_t * database,
    bcm_stat_counter_enable_t * enable)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(database, _SHR_E_PARAM, "database");
    SHR_NULL_CHECK(enable, _SHR_E_PARAM, "enable");
    /** check for valid flags value */
    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect flags=%d\n", flags);
    }
    /** verify the engine is valid */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_database_structure_verify(unit, database, TRUE));

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_mgmt_counter_get_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_input_data_t * stat_counter_input_data,
    bcm_stat_counter_output_data_t * stat_counter_output_data)
{
    int engine_id = 0;
    int counter_set_size = 0;
    int is_multi_sets_database, set_id;
    bcm_stat_counter_database_t database;
    bcm_stat_counter_interface_type_t engine_source;
    dnx_type_config_t type;
    SHR_FUNC_INIT_VARS(unit);

    SHR_MASK_VERIFY(flags, BCM_STAT_COUNTER_CLEAR_ON_READ, _SHR_E_PARAM,
                    "Incorrect flags - only flag for clear on read is supported for this API\n");
    SHR_NULL_CHECK(stat_counter_input_data, _SHR_E_PARAM, "stat_counter_input_data");
    SHR_NULL_CHECK(stat_counter_output_data, _SHR_E_PARAM, "stat_counter_output_data");

    /** verify correct type_id */
    if (stat_counter_input_data->type_id < 0 || stat_counter_input_data->type_id >= BCM_STAT_MAX_NUMBER_OF_OBJECT_TYPES)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "  Incorrect type_id=%d, possible values from 0 till 3 \n",
                     stat_counter_input_data->type_id);
    }
    /** check database_id  */
    database.core_id = stat_counter_input_data->core_id;
    database.database_id = stat_counter_input_data->database_id;
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_database_structure_verify(unit, &database, FALSE));

    /** get from base_engine_id the counter set size */
    SHR_IF_ERR_EXIT(dnx_crps_db.database.base_engine.get(unit, database.core_id, database.database_id, &engine_id));
    /** get the source type */
    SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.src_type.get(unit, database.core_id, engine_id, &engine_source));
    /** check for correct source - if no eviction, can't read counters (E-OAM)  */
    if (engine_source == bcmStatCounterInterfaceEgressOam)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "  Incorrect counter_source_type=%d, counter_get API is not supported for that source \n",
                     engine_source);
    }

    SHR_IF_ERR_EXIT(dnx_crps_mgmt_is_multi_sets_database
                    (unit, database.core_id, database.database_id, &is_multi_sets_database));
    if (is_multi_sets_database)
    {
        if (stat_counter_input_data->type_id != 0)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "Incorrect type=%d for multi-sets database, must be 0\n", stat_counter_input_data->type_id);
        }

        /** get stat_id set */
        SHR_IF_ERR_EXIT(dnx_crps_mgmt_stat_object_id_set_id_get(unit, database.core_id, database.database_id,
                                                                stat_counter_input_data->counter_source_id, &set_id));

        /** verify the object stat_id is in some configured set range */
        if (set_id == DNX_CRPS_MGMT_SET_INVALID)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "Incorrect counter_source_id=%d, for type=0 the configured range is \n",
                         stat_counter_input_data->counter_source_id);
        }

        /*
         * get counter set size 
         */
        SHR_IF_ERR_EXIT(dnx_crps_db.database.set.
                        size.get(unit, database.core_id, database.database_id, set_id, &counter_set_size));
    }
    else
    {

        /** verify the object stat_id is in the type range */
        SHR_IF_ERR_EXIT(dnx_crps_db.database.
                        type.get(unit, database.core_id, database.database_id, stat_counter_input_data->type_id,
                                 &type));
        if (stat_counter_input_data->counter_source_id < type.start
            || stat_counter_input_data->counter_source_id > type.end)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "  Incorrect counter_source_id=%d, for type=%d the configured range is start=%d end=%d \n",
                         stat_counter_input_data->counter_source_id, stat_counter_input_data->type_id, type.start,
                         type.end);
        }

        /** get counter set size */
        SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.
                        counter_set_size.get(unit, stat_counter_input_data->core_id, engine_id, &counter_set_size));
    }

    /** stat array check */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_get_statistic_array_verify
                    (unit, stat_counter_input_data->stat_arr, stat_counter_input_data->nstat, counter_set_size));
exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
int
dnx_crps_mgmt_counter_explicit_get_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_explicit_input_data_t * stat_counter_input_data,
    bcm_stat_counter_output_data_t * stat_counter_output_data)
{
    bcm_stat_counter_interface_type_t engine_source;
    int valid, counter_set_size = 0;
    dnx_type_config_t type;
    int database_id;
    SHR_FUNC_INIT_VARS(unit);

    SHR_MASK_VERIFY(flags, BCM_STAT_COUNTER_CLEAR_ON_READ, _SHR_E_PARAM,
                    "Incorrect flags - only flag for clear on read is supported for this API\n");
    SHR_NULL_CHECK(stat_counter_input_data, _SHR_E_PARAM, "stat_counter_input_data");
    SHR_NULL_CHECK(stat_counter_output_data, _SHR_E_PARAM, "stat_counter_output_data");

    /** check for valid core - BCM_CORE_ALL is not allowed */
    DNXCMN_CORE_VALIDATE(unit, stat_counter_input_data->engine.core_id, FALSE);

    /** get engine interface configuration - source type */
    SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.src_type.get(unit, stat_counter_input_data->engine.core_id,
                                                            stat_counter_input_data->engine.engine_id, &engine_source));
    /** check for correct source - if no eviction, can't read counters (E-OAM)  */
    if (engine_source == bcmStatCounterInterfaceEgressOam)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "  Incorrect counter_source_type=%d, counter_explicit_get API is not supported for that source \n",
                     engine_source);
    }
    /** get if engine is valid, connected to local host and has phy record format*/
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_engine_eviction_valid_get(unit, stat_counter_input_data->engine.core_id,
                                                            stat_counter_input_data->engine.engine_id, &valid));
    if (valid == FALSE)
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL,
                     "invalid engine. core=%d,engine=%d is not valid or not connected to local host or record format!=phy",
                     stat_counter_input_data->engine.core_id, stat_counter_input_data->engine.engine_id);
    }

    /** verify the engine is valid */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_engine_structure_verify(unit, &(stat_counter_input_data->engine), FALSE));
    /** verify correct type_id */
    if (stat_counter_input_data->type_id < 0 || stat_counter_input_data->type_id >= BCM_STAT_MAX_NUMBER_OF_OBJECT_TYPES)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "  Incorrect type_id=%d, possible values from 0 till 3 \n",
                     stat_counter_input_data->type_id);
    }
    /** counter set size */
    SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.counter_set_size.get(unit, stat_counter_input_data->engine.core_id,
                                                                    stat_counter_input_data->engine.engine_id,
                                                                    &counter_set_size));
    /** stat array check */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_get_statistic_array_verify
                    (unit, stat_counter_input_data->stat_arr, stat_counter_input_data->nstat, counter_set_size));
    /** database id */
    SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.database_id.get(unit, stat_counter_input_data->engine.core_id,
                                                               stat_counter_input_data->engine.engine_id,
                                                               &database_id));
    /** verify the object stat_id is in the type range */
    SHR_IF_ERR_EXIT(dnx_crps_db.database.type.get(unit, stat_counter_input_data->engine.core_id, database_id,
                                                  stat_counter_input_data->type_id, &type));
    if (stat_counter_input_data->object_stat_id < type.start || stat_counter_input_data->object_stat_id > type.end)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "  Incorrect object_stat_id=%d, for type=%d the configured range is start=%d end=%d \n",
                     stat_counter_input_data->object_stat_id, stat_counter_input_data->type_id, type.start, type.end);
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_mgmt_counter_engine_control_set_verify(
    int unit,
    uint32 flags,
    bcm_stat_engine_t * engine,
    bcm_stat_counter_engine_control_t control,
    uint32 arg)
{
    int valid, core_idx;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(engine, _SHR_E_PARAM, "engine");
    /** verify the engine is valid */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_engine_structure_verify(unit, engine, TRUE));
    DNXCMN_CORES_ITER(unit, engine->core_id, core_idx)
    {
        DNX_CRPS_MGMT_ENGINE_VALID_GET(unit, core_idx, engine->engine_id, valid);
        if (valid == FALSE)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Engine_id=%d, core_id=%d is not active", engine->engine_id, engine->core_id);
        }

        switch (control)
        {
            case bcmStatCounterClearAll:
                /** check for valid flags value */
                if (flags != 0 && ((flags & BCM_STAT_COUNTER_CONTROL_CLEAR_SW_ONLY) == FALSE)
                    && ((flags & BCM_STAT_COUNTER_CONTROL_CLEAR_HW_ONLY) == FALSE))
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM,
                                 " Incorrect flags=%d\n, supported flag 0 ,BCM_STAT_COUNTER_CONTROL_CLEAR_HW_ONLY, BCM_STAT_COUNTER_ENGINE_CONTROL_CLEAR_HW_ONLY",
                                 flags);
                }
                break;
            case bcmStatCounterSequentialSamplingInterval:
                if (flags != 0)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM,
                                 " Incorrect flags=%d\n, if control is not bcmStatCounterClearAll - no flags allowed",
                                 flags);
                }
                break;
            case bcmStatCounterEngineEvictionEnable:
                if (flags != 0)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM,
                                 " Incorrect flags=%d\n, if control is not bcmStatCounterEngineEvictionEnable - no flags allowed",
                                 flags);
                }
                if (arg != 0 && arg != 1)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM,
                                 " Incorrect arg=%d\n, if control is bcmStatCounterEngineEvictionEnable - enable disable - only arguments 0 or 1 are allowed",
                                 flags);
                }
                break;
            default:
                SHR_ERR_EXIT(_SHR_E_PARAM, " invalid control (=%d)\n", control);
                break;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_counter_database_control_overflow_mode_support_verify(
    int unit,
    bcm_stat_counter_database_t * database)
{

    int base_engine_id, core_idx;
    bcm_stat_counter_format_type_t format_type;

    SHR_FUNC_INIT_VARS(unit);

    DNXCMN_CORES_ITER(unit, database->core_id, core_idx)
    {
        SHR_IF_ERR_EXIT(dnx_crps_db.database.base_engine.get(unit, core_idx, database->database_id, &base_engine_id));
        SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.format.get(unit, core_idx, base_engine_id, &format_type));

        /** there is no saturation for cpx counters*/
        if (dnx_crps_mgmt_eviction_destination_for_format_type_is_supported
            (unit, format_type, bcmStatEvictionDestinationCrpsXl)
            && !dnx_crps_mgmt_eviction_destination_for_format_type_is_supported(unit, format_type,
                                                                                bcmStatEvictionDestinationLocalHost))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported control=bcmStatCounterOverflowMode\n");
        }
    }
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_crps_mgmt_counter_rate_calculation_set_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_database_t * database,
    uint32 arg)
{
    int core_idx;
    bcm_stat_counter_database_t database_main;
    bcm_stat_counter_enable_t enable;
    SHR_FUNC_INIT_VARS(unit);

    if (!dnx_data_crps.general.feature_get(unit, dnx_data_crps_general_crps_rate_calculation_support))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported control=bcmStatCounterDatabaseRateCalculationEnable\n");
    }

    if (arg != 0 && arg != 1)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Incorrect arg=%d\n", arg);
    }

    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Incorrect flags=%d\n", flags);
    }

    DNXCMN_CORES_ITER(unit, database->core_id, core_idx)
    {
        database_main.core_id = core_idx;
        database_main.database_id = database->database_id;

        SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_database_enable_get(unit, 0 /* flags */ , &database_main, &enable));

        if (enable.enable_eviction)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Database eviction must be disabled, database_id=%d, core=%d",
                         database_main.database_id, database_main.core_id);
        }

    }

exit:
    SHR_FUNC_EXIT;

}

/** see .h file */
shr_error_e
dnx_crps_mgmt_counter_database_control_set_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_database_t * database,
    bcm_stat_counter_database_control_t control,
    uint32 arg)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(database, _SHR_E_PARAM, "database");
    /** verify the engine is valid */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_database_structure_verify(unit, database, TRUE));
    switch (control)
    {
        case bcmStatCounterDatabaseClearAll:
            /** check for valid flags value */
            if (flags != 0 && ((flags & BCM_STAT_COUNTER_CONTROL_CLEAR_SW_ONLY) == FALSE)
                && ((flags & BCM_STAT_COUNTER_CONTROL_CLEAR_HW_ONLY) == FALSE))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             " Incorrect flags=%d\n, supported flag 0 ,BCM_STAT_COUNTER_CONTROL_CLEAR_HW_ONLY, BCM_STAT_COUNTER_ENGINE_CONTROL_CLEAR_HW_ONLY",
                             flags);
            }
            break;

        case bcmStatCounterOverflowMode:

            SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_database_control_overflow_mode_support_verify(unit, database));

            if (flags != 0)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Incorrect flags=%d\n", flags);
            }

            if (arg != BCM_STAT_COUNTER_OVERFLOW_MODE_RESET && arg != BCM_STAT_COUNTER_OVERFLOW_MODE_WRAP_AROUND
                && arg != BCM_STAT_COUNTER_OVERFLOW_MODE_FIXED_AT_MAX)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             " Invalid arg=%d\n, if control is  bcmStatCounterOverflowMode - arg value should be BCM_STAT_COUNTER_OVERFLOW_MODE_RESET / BCM_STAT_COUNTER_OVERFLOW_MODE_WRAP_AROUND / BCM_STAT_COUNTER_OVERFLOW_MODE_FIXED_AT_MAX",
                             arg);
            }

            break;

        case bcmStatCounterDatabaseSequentialSkipZerosEnable:
            if (!dnx_data_crps.eviction.feature_get(unit, dnx_data_crps_eviction_sequential_scan_speedup_is_supported))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported control=%d\n", control);
            }
            if (arg != 0 && arg != 1)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Incorrect arg=%d\n", arg);
            }
            if (flags != 0)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Incorrect flags=%d\n", flags);
            }

            break;

        case bcmStatCounterDatabaseSequentialSamplingZeroInterval:
            if (!dnx_data_crps.eviction.feature_get(unit, dnx_data_crps_eviction_sequential_scan_speedup_is_supported))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported control=%d\n", control);
            }
            if (flags != 0)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Incorrect flags=%d\n", flags);
            }

            break;

        case bcmStatCounterDatabaseRateCalculationEnable:

            SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_rate_calculation_set_verify(unit, flags, database, arg));

            break;

        case bcmStatCounterDatabaseSequentialIterationInterval:
            if (!dnx_data_crps.
                eviction.feature_get(unit, dnx_data_crps_eviction_iteration_interval_time_config_is_supported))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported control=%d\n", control);
            }
            if (flags != 0)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Incorrect flags=%d\n", flags);
            }

            break;

        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, " invalid control (=%d)\n", control);
            break;
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_mgmt_counter_engine_control_get_verify(
    int unit,
    uint32 flags,
    bcm_stat_engine_t * engine,
    bcm_stat_counter_engine_control_t control,
    uint32 *arg)
{

    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(engine, _SHR_E_PARAM, "engine");
    /** check for valid flags value */
    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect flags=%d\n, no flags supported for this API", flags);
    }
    /** verify the engine is valid */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_engine_structure_verify(unit, engine, TRUE));

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_mgmt_counter_database_control_get_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_database_t * database,
    bcm_stat_counter_database_control_t control,
    uint32 *arg)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(database, _SHR_E_PARAM, "database");
    /** check for valid flags value */
    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect flags=%d\n, no flags supported for this API", flags);
    }

    if (control == bcmStatCounterOverflowMode)
    {
        SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_database_control_overflow_mode_support_verify(unit, database));
    }

    /** verify the engine is valid */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_database_structure_verify(unit, database, TRUE));

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_eviction_boundaries_set_verify(
    int unit,
    uint32 flags,
    bcm_stat_engine_t * engine,
    bcm_stat_eviction_boundaries_t * boundaries)
{
    int valid_engine = 0, core_idx;
    const dnx_data_crps_engine_engines_info_t *engine_size;
    int nof_counters_per_entry;
    bcm_stat_counter_format_type_t format;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(engine, _SHR_E_PARAM, "engine");
    SHR_NULL_CHECK(boundaries, _SHR_E_PARAM, "boundaries");
    /** check for valid flags value */
    if ((flags != 0) && ((flags & BCM_STAT_EVICTION_RANGE_ALL) == FALSE))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect flags=%d\n", flags);
    }
    /** verify the engine is valid */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_engine_structure_verify(unit, engine, TRUE));
    DNXCMN_CORES_ITER(unit, engine->core_id, core_idx)
    {
        /** verify that engine is already active */
        DNX_CRPS_MGMT_ENGINE_VALID_GET(unit, core_idx, engine->engine_id, valid_engine);
        if (!valid_engine)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         " Incorrect call of bcm_stat_eviction_boundaries_set - engine with engine id=%d and core=%d is not yet active and eviction boundaries cannot be changed at this stage",
                         engine->engine_id, core_idx);
        }

        /** verify that boundaries are in the correct range */
        engine_size = dnx_data_crps.engine.engines_info_get(unit, engine->engine_id);

        SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.format.get(unit, core_idx, engine->engine_id, &format));
        nof_counters_per_entry = dnx_data_crps.engine.counter_format_types_get(unit, format)->nof_counters_per_entry;
        /** valid start */
        if (boundaries->start < 0 || boundaries->start >= (engine_size->nof_entries * nof_counters_per_entry))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         " Cannot set such boundaries, possible boundaries are in range: 0 untill %d , invalid start=%d \n",
                         engine_size->nof_entries - 1, boundaries->start);
        }
        /** valid end */
        if (boundaries->end < 0 || boundaries->end >= (engine_size->nof_entries * nof_counters_per_entry))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         " Cannot set such boundaries, possible boundaries are in range: 0 untill %d, invalid end=%d \n",
                         engine_size->nof_entries - 1, boundaries->end);
        }
        /** start < end */
        if (boundaries->start > boundaries->end)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         " Cannot set such boundaries, possible boundaries are in range: 0 untill %d, invalid start=%d and end=%d \n",
                         engine_size->nof_entries - 1, boundaries->start, boundaries->end);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_eviction_boundaries_get_verify(
    int unit,
    uint32 flags,
    bcm_stat_engine_t * engine,
    bcm_stat_eviction_boundaries_t * boundaries)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(engine, _SHR_E_PARAM, "engine");
    SHR_NULL_CHECK(boundaries, _SHR_E_PARAM, "boundaries");
    /** check for valid flags value */
    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect flags=%d\n", flags);
    }
    /** verify the engine is valid */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_engine_structure_verify(unit, engine, TRUE));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
 *  verification bcm_stat_pkt_size_adjust_select_key_t
* \par DIRECT INPUT:
*   \param [in] unit    -  Unit-ID
*   \param [in] key  -  key struct to verify
*   \param [in] select_type - header adjust select type
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
dnx_crps_mgmt_pkt_size_adjust_select_key_verify(
    int unit,
    bcm_stat_counter_command_id_key_t * key,
    bcm_stat_pkt_size_adjust_select_type_t select_type)
{
    SHR_FUNC_INIT_VARS(unit);

    /** check for valid core - BCM_CORE_ALL also allowed */
    DNXCMN_CORE_VALIDATE(unit, key->core_id, TRUE);
    /** verify source */
    if (key->source != bcmStatCounterInterfaceIngressOam && key->source != bcmStatCounterInterfaceIngressReceivePp &&
        key->source != bcmStatCounterInterfaceIngressVoq)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect source=%d \n", key->source);
    }
    /** verify command_id */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_command_id_verify(unit, key->source, key->command_id));
    /** verify type */
    if (select_type != bcmStatPktSizeSelectCounterIngressHeaderTruncate)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect type=%d \n", select_type);
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_ingress_pkt_size_adjust_select_set_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_command_id_key_t * key,
    bcm_stat_pkt_size_adjust_select_type_t select_type,
    int enable)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(key, _SHR_E_PARAM, "key");
    /** check for valid flags value */
    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect flags=%d\n", flags);
    }
    /** verify enable 0/1 */
    if (enable != TRUE && enable != FALSE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect enable=%d - must be true/false \n", enable);
    }
    /** verify the key parameters are valid */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_pkt_size_adjust_select_key_verify(unit, key, select_type));

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_ingress_pkt_size_adjust_select_get_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_command_id_key_t * key,
    bcm_stat_pkt_size_adjust_select_type_t select_type,
    int *enable)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(key, _SHR_E_PARAM, "key");
    /** check for valid flags value */
    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect flags=%d\n", flags);
    }
    /** verify the key parameters are valid */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_pkt_size_adjust_select_key_verify(unit, key, select_type));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*   verification of key bcm_stat_counter_command_id_key_t and
*   filter group
* \par DIRECT INPUT:
*   \param [in] unit    -  Unit-ID
*   \param [in] key  -  key struct to verify
*   \param [in] filter - filter group
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
dnx_crps_mgmt_counter_group_filter_key_verify(
    int unit,
    bcm_stat_counter_command_id_key_t * key,
    bcm_stat_counter_group_filter_t filter)
{
    const dnx_data_stat_drop_reasons_group_drop_reason_index_t *group_index;
    SHR_FUNC_INIT_VARS(unit);

    /** check for valid core - BCM_CORE_ALL also allowed */
    DNXCMN_CORE_VALIDATE(unit, key->core_id, TRUE);
    /** verify source */
    if (key->source != bcmStatCounterInterfaceIngressOam && key->source != bcmStatCounterInterfaceIngressReceivePp &&
        key->source != bcmStatCounterInterfaceIngressVoq)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect source=%d \n", key->source);
    }
    /** verify command_id */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_command_id_verify(unit, key->source, key->command_id));
    /** verify filter group */
    group_index = dnx_data_stat.drop_reasons.group_drop_reason_index_get(unit, filter);
    if ((int) filter < 0 || filter >= bcmStatCounterGroupFilterCount || group_index->index == -1)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect filter group=%d\n", filter);
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_mgmt_filter_group_set_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_command_id_key_t * key,
    bcm_stat_counter_group_filter_t filter,
    int is_active)
{

    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(key, _SHR_E_PARAM, "key");
    /** check for valid flags value */
    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect flags=%d\n", flags);
    }
    /** verify key struct and filter */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_group_filter_key_verify(unit, key, filter));
    /** verify is_active */
    if (is_active != TRUE && is_active != FALSE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect is_active=%d\n - TRUE/FALSE", is_active);
    }
exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_mgmt_filter_group_get_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_command_id_key_t * key,
    bcm_stat_counter_group_filter_t filter,
    int *is_active)
{

    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(key, _SHR_E_PARAM, "key");
    /** check for valid flags value */
    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect flags=%d\n", flags);
    }
    /** verify key struct and filter group   */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_counter_group_filter_key_verify(unit, key, filter));

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_counter_database_create_verify(
    int unit,
    uint32 flags,
    bcm_core_t core_id,
    int *database_id)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(database_id, _SHR_E_PARAM, "database_id");
    /** check for valid flags value */
    SHR_MASK_VERIFY(flags, BCM_STAT_DATABASE_CREATE_WITH_ID, _SHR_E_PARAM, "Incorrect flags\n");
    if (core_id == BCM_CORE_ALL && ((flags & BCM_STAT_DATABASE_CREATE_WITH_ID) == FALSE))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "core_id=BCM_CORE_ALL allowed only when flag BCM_STAT_DATABASE_CREATE_WITH_ID is set\n");
    }
exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_counter_database_destroy_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_database_t * database)
{
    int next_engine_id, core_idx;
    dnx_engine_enablers_t enable;
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(database, _SHR_E_PARAM, "database");

    /** check for valid flags value */
    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect flags=%d\n", flags);
    }
    /** check that database is allocated and specific core_id */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_database_structure_verify(unit, database, TRUE));

    DNXCMN_CORES_ITER(unit, database->core_id, core_idx)
    {
        SHR_IF_ERR_EXIT(dnx_crps_db.database.base_engine.get(unit, core_idx, database->database_id, &next_engine_id));
        /** verify that all engines in the database are disabled */
        while (next_engine_id != DNX_CRPS_MGMT_ENGINE_INVALID)
        {
            /** verify that the engine is fully disabled before detach it */
            /** because destroy will detach all engines */
            SHR_IF_ERR_EXIT(dnx_crps_db.proc.enablers.get(unit, core_idx, next_engine_id, &enable));
            if (enable.counting_enable == TRUE || enable.eviction_enable == TRUE)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "engine_id=%d which belong to database_id=%d is not fully disabled, cannot destroy the database",
                             next_engine_id, database->database_id);
            }
            SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.next_engine_id.get
                            (unit, core_idx, next_engine_id, &next_engine_id));
        }
    }
exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_counter_engine_attach_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_database_t * database,
    int engine_id)
{
    uint8 is_allocated;
    int started, used_for_meter, core_idx;
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(database, _SHR_E_PARAM, "database");
    /** check for valid flags value */
    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect flags=%d\n", flags);
    }
    DNXCMN_CORES_ITER(unit, database->core_id, core_idx)
    {
        SHR_IF_ERR_EXIT(dnx_crps_db.database_res.is_allocated(unit, core_idx, database->database_id, &is_allocated));
        if (is_allocated == FALSE)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "database were not created. (core_id=%d database_id=%d)\n",
                         core_idx, database->database_id);
        }
        /** verify the engine_id is valid */
        if (engine_id >= dnx_data_crps.engine.nof_engines_get(unit) || engine_id < 0)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect engine_id=%d\n", engine_id);
        }
        /** verify the engine is not active */
        SHR_IF_ERR_EXIT(dnx_crps_db.proc.config_started.get(unit, core_idx, engine_id, &started));
        if (started)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " Engine is already active: core_id=%d, engine_id=%d \n", core_idx, engine_id);
        }
        /** check that the engine is not used for meter. some of the engines has shared memory with meter processor */
        SHR_IF_ERR_EXIT(dnx_crps_db.proc.used_for_meter.get(unit, core_idx, engine_id, &used_for_meter));
        if (used_for_meter == TRUE)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " core_id=%d, engine_id=%d is already used for meter \n", core_idx, engine_id);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_counter_engine_detach_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_database_t * database,
    int engine_id)
{
    uint8 is_allocated;
    int started;
    int database_id;
    int base_engine, core_idx;
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(database, _SHR_E_PARAM, "database");
    /** check for valid flags value */
    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect flags=%d\n", flags);
    }
    DNXCMN_CORES_ITER(unit, database->core_id, core_idx)
    {
        SHR_IF_ERR_EXIT(dnx_crps_db.database_res.is_allocated(unit, core_idx, database->database_id, &is_allocated));
        if (is_allocated == FALSE)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "database were not created. (core_id=%d database_id=%d)\n",
                         core_idx, database->database_id);
        }
        /** verify the engine_id is valid */
        if (engine_id >= dnx_data_crps.engine.nof_engines_get(unit) || engine_id < 0)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect engine_id=%d\n", engine_id);
        }
        /** verify the engine is active - which means attached already */
        SHR_IF_ERR_EXIT(dnx_crps_db.proc.config_started.get(unit, core_idx, engine_id, &started));
        if (started == FALSE)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " Engine is not active (not attached): core_id=%d, engine_id=%d \n",
                         core_idx, engine_id);
        }
        /** verify that the engine_id belong to the given database */
        SHR_IF_ERR_EXIT(dnx_crps_db.proc.interface.database_id.get(unit, core_idx, engine_id, &database_id));
        if (database_id != database->database_id)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "engine_id does not belong to the given database_id\n");
        }
        /** verify that the base engine is not remove because if removing the base_engine, */
        /** we will not have the database configuration. (scenario of detach all, attach new will fail).    */
        /** only database destroy API detach the base engine */
        SHR_IF_ERR_EXIT(dnx_crps_db.database.base_engine.get(unit, core_idx, database->database_id, &base_engine));
        if (base_engine == engine_id)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "engine_id=%d is the base engine. It is forbidden to detach the base engine of the database\n",
                         engine_id);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_database_eviction_boundaries_set_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_database_t * database,
    int type_id,
    bcm_stat_eviction_boundaries_t * boundaries)
{
    int core_idx;
    dnx_type_config_t type;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(database, _SHR_E_PARAM, "database");
    SHR_MASK_VERIFY(flags, BCM_STAT_EVICTION_RANGE_ALL, _SHR_E_PARAM,
                    "Incorrect flags - only flag BCM_STAT_EVICTION_RANGE_ALL is supported for this API\n");
    if (!_SHR_IS_FLAG_SET(flags, BCM_STAT_EVICTION_RANGE_ALL))
    {
        SHR_NULL_CHECK(boundaries, _SHR_E_PARAM, "boundaries");
    }

    /** verify the database is valid */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_database_structure_verify(unit, database, TRUE));
    /** check for correct type_id value*/
    if (type_id < 0 || type_id >= BCM_STAT_MAX_NUMBER_OF_OBJECT_TYPES)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "  Incorrect type_id=%d, possible values from 0 till %d\n", type_id,
                     BCM_STAT_MAX_NUMBER_OF_OBJECT_TYPES);
    }

    DNXCMN_CORES_ITER(unit, database->core_id, core_idx)
    {
        /** verify type id is set to valid */
        SHR_IF_ERR_EXIT(dnx_crps_db.database.type.get(unit, core_idx, database->database_id, type_id, &type));
        if (type.valid == 0)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " Cannot modify boundaries for type_id=% is set to not be valid \n", type_id);
        }
        /** valid start */
        if (boundaries->start < 0 || boundaries->start > type.end || boundaries->start < type.start)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         " Cannot set such boundaries, possible boundaries are in range: from %d untill %d , invalid start=%d \n",
                         type.start, type.end, boundaries->start);
        }
        /** valid end */
        if (boundaries->end < 0 || boundaries->end > type.end)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         " Cannot set such boundaries, possible boundaries are in range: from %d untill %d , invalid end=%d \n",
                         type.start, type.end, boundaries->end);
        }
        /** start < end */
        if (boundaries->start > boundaries->end)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         " Cannot set such boundaries, possible boundaries are in range:  from %d untill %d, invalid start=%d and end=%d \n",
                         type.start, type.end, boundaries->start, boundaries->end);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_crps_database_eviction_boundaries_get_verify(
    int unit,
    uint32 flags,
    bcm_stat_counter_database_t * database,
    int type_id,
    bcm_stat_eviction_boundaries_t * boundaries)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(database, _SHR_E_PARAM, "database");
    SHR_NULL_CHECK(boundaries, _SHR_E_PARAM, "boundaries");
    /** check for valid flags value */
    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Incorrect flags=%d\n", flags);
    }
    /** verify the database is valid */
    SHR_IF_ERR_EXIT(dnx_crps_mgmt_database_structure_verify(unit, database, TRUE));
    /** check for correct type_id value*/
    if (type_id < 0 || type_id >= BCM_STAT_MAX_NUMBER_OF_OBJECT_TYPES)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "  Incorrect type_id=%d, possible values from 0 till %d\n", type_id,
                     BCM_STAT_MAX_NUMBER_OF_OBJECT_TYPES);
    }

exit:
    SHR_FUNC_EXIT;
}

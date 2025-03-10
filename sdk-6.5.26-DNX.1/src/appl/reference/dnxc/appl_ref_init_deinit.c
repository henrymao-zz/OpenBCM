/** \file appl_ref_init_deinit.c
 * init and deinit functions to be used by the INIT_DNX command.
 */

/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_APPLDNX_INITSEQDNX

/*
* INCLUDE FILES:
* {
*/

#include <ibde.h>
#include <appl/reference/dnxc/appl_ref_init_deinit.h>
#include <appl/reference/dnxc/appl_ref_init_utils.h>
#include <appl/reference/dnxc/appl_ref_board.h>
#include <soc/sand/shrextend/shrextend_debug.h>
#include <appl/diag/sysconf.h>
#include <soc/cmext.h>
#include <soc/defs.h>
#include <soc/drv.h>
#include <soc/scache.h>
#include <bcm/init.h>
#include <appl/diag/sand/diag_sand_utils.h>
#include <soc/dnxc/drv_dnxc_utils.h>

#if defined(BCM_DNX_SUPPORT)
#include <appl/diag/dnx/diag_dnx_cmdlist.h>
#endif
#if defined(BCM_DNXF_SUPPORT)
#include <appl/diag/dnxf/diag_dnxf_cmdlist.h>
#endif

#if BCM_API_VERBOSE_LOGGING != 0
#include <src/appl/cint/cint_logger.h>
#endif

/** these externs are needed for a common step list get function - appl_dnxc_step_list_get*/
#ifdef BCM_DNX_SUPPORT
/* { */
extern shr_error_e appl_dnx_step_list_get(
    int unit,
    const appl_dnxc_init_step_t ** appl_steps);

extern shr_error_e appl_dnx_step_time_thresh_list_get(
    int unit,
    const appl_init_time_thresh_info_t ** time_thresh_list);

extern shr_error_e appl_dnx_per_dev_step_time_threshold_get(
    int unit,
    int step_id,
    sal_usecs_t * time_thresh);

extern shr_error_e appl_dnx_per_dev_full_time_threshold_get(
    int unit,
    sal_usecs_t * time_thresh);
/* } */
#endif

#ifdef BCM_DNXF_SUPPORT
extern shr_error_e appl_dnxf_step_list_get(
    int unit,
    const appl_dnxc_init_step_t ** appl_steps);

extern shr_error_e appl_dnxf_step_time_thresh_list_get(
    int unit,
    const appl_init_time_thresh_info_t ** time_thresh_list);

extern shr_error_e appl_dnxf_per_dev_step_time_threshold_get(
    int unit,
    int step_id,
    sal_usecs_t * time_thresh);

extern shr_error_e appl_dnxf_per_dev_full_time_threshold_get(
    int unit,
    sal_usecs_t * time_thresh);

#endif

/*
 * }
 */

/*
 * Typedefs.
 * {
 */

/*
 * }
 */

/*
 * Globals.
 * {
 */
static appl_dnxc_init_param_t init_param[SOC_MAX_NUM_DEVICES];

/* used when destroying and recreating a unit, to keep the device of the destroyed unit and later use it for the recreation of the unit */
static int dnxc_appl_bde_dev_used_by_destroyed_unit[SOC_MAX_NUM_DEVICES];
/* value meaning the destroyed unit was a composite unit */
#define DNXC_APPL_DESTROYED_UNIT_WAS_COMPOSITE -5

/* used when destroying and recreating a composite unit, to keep its sub units, and its composite device type */
static int dnxc_appl_sub_units_of_destroyed_unit[SOC_MAX_NUM_DEVICES * SOC_MAX_NOF_COMPOSITE_SUB_DEVS];
static uint32 dnxc_appl_composite_dev_type_of_destroyed_unit[SOC_MAX_NUM_DEVICES];

/*
 * }
 */

#if AGGRESSIVE_ALLOC_DEBUG_TESTING
/* { */
#include <src/sal/core/unix/alloc_debug.h>
#define UNFREE_ALLOCS_FILE "unfree_allocs.txt"

STATIC int
init_aggressive_alloc_debug_testing(
    int itertaion_idx)
{
    static int32 after_deinit_nof_allocs = 0;
    int32 after_deinit_init_deinit_nof_allocs;
    alloc_info *unfree_allocs;
    FILE *unfree_allocs_file;
    int rv = 0;
    uint32 allocation_idx;
    uint32 backtrace_idx;

    if (itertaion_idx == 0)
    {

        after_deinit_nof_allocs = sal_alloc_debug_nof_allocs_get();
    }

    if (itertaion_idx == 1)
    {

        after_deinit_init_deinit_nof_allocs = sal_alloc_debug_nof_allocs_get();

        if (after_deinit_init_deinit_nof_allocs > after_deinit_nof_allocs)
        {
            cli_out("ERROR: There are unfree allocations done by sal_alloc.\n");
            rv = -1;
            unfree_allocs_file = sal_fopen(UNFREE_ALLOCS_FILE, "w");
            if (!unfree_allocs_file)
            {
                cli_out("Failed to open file %s.\n", UNFREE_ALLOCS_FILE);
                return rv;
            }
            unfree_allocs = sal_alloc(sizeof(alloc_info) * (after_deinit_init_deinit_nof_allocs - after_deinit_nof_allocs + 1), "");    /* include
                                                                                                                                         * this
                                                                                                                                         * allocation 
                                                                                                                                         */
            if (!unfree_allocs)
            {
                cli_out("Memory allocation Failure.\n\r");
                return rv;
            }
            sal_alloc_debug_last_allocs_get(unfree_allocs,
                                            after_deinit_init_deinit_nof_allocs - after_deinit_nof_allocs + 1);
            for (allocation_idx = 0; allocation_idx < after_deinit_init_deinit_nof_allocs - after_deinit_nof_allocs;
                 ++allocation_idx)
            {
                sal_fprintf(unfree_allocs_file, "allocation 0x%lx %d  from ",
                            (unsigned long) unfree_allocs[allocation_idx].addr, unfree_allocs[allocation_idx].size);
                for (backtrace_idx = ALLOC_DEBUG_TESTING_NOF_BACKTRACES - 1; backtrace_idx > 0; --backtrace_idx)
                {
                    sal_fprintf(unfree_allocs_file, "%p -> ", unfree_allocs[allocation_idx].stack[backtrace_idx]);
                }
                sal_fprintf(unfree_allocs_file, "%p Description : %s\n",
                            unfree_allocs[allocation_idx].stack[0], unfree_allocs[allocation_idx].desc);
            }
            sal_free(unfree_allocs);
            sal_fclose(unfree_allocs_file);
            return rv;
        }
        else
        {
            return rv;
        }
    }

    return rv;
}
/* } */
#endif

/*
 * See .h file
 */
shr_error_e
appl_dnxc_sdk_init(
    int unit)
{

    int rv;
    uint16 device_id = 0;
    uint8 revision_id = 0;
    const ibde_dev_t *device;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Create and attach unit only if both deinit and init is required (full sequence).
     * Meaning that on cold boot the unit is created from sysconf_probe() and attached from sysconf_attach()
     * which are called from the application like from main()-diag_shell()-diag_sdk_init().
     */
    if ((init_param[unit].no_deinit == 0) && (init_param[unit].no_init == 0))
    {
        int bde_dev;

        /*
         * Override device ID and revision if needed
         */
        if (CMDEV(unit).dev.info)
        {
            SHR_EXIT_WITH_LOG(_SHR_E_UNIT, "unit %d is in use%s%s\n", unit, EMPTY, EMPTY);
        }
        bde_dev = dnxc_appl_bde_dev_used_by_destroyed_unit[unit];
        if (bde_dev == DNXC_APPL_DESTROYED_UNIT_WAS_COMPOSITE)
        {
            /** For composite units, first call appl_dnxc_sdk_init on the sub units, and then created the composite unit */
            int i, *sub_units = dnxc_appl_sub_units_of_destroyed_unit + unit * SOC_MAX_NOF_COMPOSITE_SUB_DEVS;
            uint32 composite_dev_type = dnxc_appl_composite_dev_type_of_destroyed_unit[unit];
            unsigned nof_sub_units = soc_cm_get_nof_sub_devices(composite_dev_type); /** Get the number of sub units */
            if (nof_sub_units == 0 || nof_sub_units > SOC_MAX_NOF_COMPOSITE_SUB_DEVS)
            {
                SHR_EXIT_WITH_LOG(_SHR_E_UNIT, "Bad composite device type 0x%x composite unit %d%s\n",
                                  composite_dev_type, unit, EMPTY);
            }
            /** Use information stored for the composite unit by appl_dnxc_sdk_deinit() */
            for (i = 0; i < nof_sub_units; ++i)
            {
                if (((unsigned) sub_units[i]) >= SOC_MAX_NUM_DEVICES)
                {
                    SHR_EXIT_WITH_LOG(_SHR_E_UNIT, "Found a bad sub-unit %d with index %d for composite unit %d\n",
                                      sub_units[i], i, unit);
                }
                SHR_IF_ERR_EXIT_WITH_LOG(appl_dnxc_sdk_init(sub_units[i]),
                                         "appl_dnxc_sdk_init failed for sub-unit %d of unit %d, will not create the unit%s\n",
                                         sub_units[i], unit, EMPTY);
            }
            rv = soc_cm_device_create_composite(composite_dev_type, sub_units, NULL, unit);

        }
        else
        {
            /** none-composite unit */
            if ((unsigned) bde_dev >= SOC_MAX_NUM_DEVICES)
            {
                SHR_EXIT_WITH_LOG(_SHR_E_UNIT, "Found a bad BDE device %d for previously destroyed %d%s\n", bde_dev,
                                  unit, EMPTY);
            }
            device = bde->get_dev(bde_dev);
            device_id = device->device;
            revision_id = device->rev;
            sysconf_chip_override(unit, &device_id, &revision_id);

            /*
             * Step 1 (cmext.h)
             * Verify device type is supported
             */
            rv = soc_cm_device_supported(device_id, revision_id);
            SHR_IF_ERR_EXIT_WITH_LOG(rv,
                                     "The Device is not supported, attempted to probe for Device:%u, Revision:%u\n%s",
                                     device_id, revision_id, EMPTY);
            /*
             * Step 2 (cmext.h):
             * Create unit with id
             */
            rv = soc_cm_device_create_id(device_id, revision_id, NULL, unit, bde_dev);
        }
        SHR_IF_ERR_EXIT_WITH_LOG(rv, "soc_cm_device_create() for device_id %u Failed:\n%s%s", device_id, EMPTY, EMPTY);

        /*
         * Step 3 (cmext.h)
         * Attach unit:
         * perform all needed actions to call bcm_init,
         * essentially this preliminary step need to be
         * as lean as possible, as many steps as possible
         * should be called from inside bcm_init.
         */
        if (!CM_IS_SUB_DEVICE(unit))
        {
            LOG_INFO_EX(BSL_LOG_MODULE, "   %d: Attach unit.\n%s%s%s", unit, EMPTY, EMPTY, EMPTY);
            rv = sysconf_attach(unit);
            SHR_IF_ERR_EXIT_WITH_LOG(rv, "sysconf_attach() Failed:\n%s%s%s", EMPTY, EMPTY, EMPTY);
#if defined(BCM_DNX_SUPPORT)
            if (SOC_CONTROL(unit) && soc_is(unit, DNX_DEVICE))
            {
                diag_sand_error_get(cmd_dnx_sh_init(unit));
            }
#endif
#if defined(BCM_DNXF_SUPPORT)
            if (SOC_CONTROL(unit) && soc_is(unit, DNXF_DEVICE))
            {
                diag_sand_error_get(cmd_dnxf_sh_init(unit));
            }
#endif
        }
    }

    if (CM_IS_SUB_DEVICE(unit))
    {
        SHR_EXIT(); /** do not initialize sub units */
    }

    /*
     * register the callback function to perform system reset of the device.
     * Such functionality in the code is not mandatory
     */
    if (SOC_CONTROL(unit) != NULL)
    {
        SOC_CONTROL(unit)->system_reset_cb = dnxc_perform_system_reset;
    }

    /*
     * Run the BCM initialization sequence
     */
    LOG_INFO_EX(BSL_LOG_MODULE, "   %d: BCM Init\n%s%s%s", unit, EMPTY, EMPTY, EMPTY);
    rv = bcm_init(unit);

#ifdef BCM_DNX_SUPPORT
    /*
     * After running bcm init, calibrate command tree
     */
    if (SOC_IS_DNX(unit))
    {
        SHR_IF_ERR_EXIT(cmd_dnx_sh_calibrate(unit));
    }
#endif /* BCM_DNX_SUPPORT */

#ifdef BCM_DNXF_SUPPORT
    /*
     * After running bcm init, calibrate command tree
     */
    if (SOC_IS_DNXF(unit))
    {
        SHR_IF_ERR_EXIT(cmd_dnxf_sh_calibrate(unit));
    }
#endif /* BCM_DNXF_SUPPORT */

    SHR_IF_ERR_EXIT_WITH_LOG(rv, "bcm_init() Failed:\n%s%s%s", EMPTY, EMPTY, EMPTY);
    LOG_INFO_EX(BSL_LOG_MODULE, "   %d: BCM Init Done\n%s%s%s", unit, EMPTY, EMPTY, EMPTY);

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
appl_dnxc_sdk_deinit(
    int unit)
{
    int rv;
    uint32 dev_id;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Deinit bcm:
     * bcm_detach() API is the opposite of bcm_init() API
     */
    LOG_INFO_EX(BSL_LOG_MODULE, "   %d: BCM Deinit\n%s%s%s", unit, EMPTY, EMPTY, EMPTY);
    rv = bcm_detach(unit);
    SHR_IF_ERR_EXIT_WITH_LOG(rv, "bcm_detach() for unit %u Failed:\n%s%s", unit, EMPTY, EMPTY);
    LOG_INFO_EX(BSL_LOG_MODULE, "   %d: BCM Deinit Done\n%s%s%s", unit, EMPTY, EMPTY, EMPTY);

    /*
     * Detach unit only if both deinit and init is required (full sequence).
     * Otherwise we won't be able to attach back a detached unit.
     */
    if ((init_param[unit].no_deinit == 0) && (init_param[unit].no_init == 0))
    {
#if defined(BCM_DNX_SUPPORT)
        if (soc_is(unit, DNX_DEVICE))
        {
            diag_sand_error_get(cmd_dnx_sh_deinit(unit));
        }
#endif
#if defined(BCM_DNXF_SUPPORT)
        if (soc_is(unit, DNXF_DEVICE))
        {
            diag_sand_error_get(cmd_dnxf_sh_deinit(unit));
        }
#endif

        if (!CM_IS_COMPOSITE_DEVICE(unit))
        {
            /** Override device ID and revision if needed */
            const ibde_dev_t *device = bde->get_dev(CMDEV(unit).dev.dev);
            uint16 device_id = device->device;
            uint8 revision_id = device->rev;
            sysconf_chip_override(unit, &device_id, &revision_id);
            /** soc_cm_device_destroy() will destroy the unit to bde_dev mapping, so keep the bde dev for recreating the unit by appl_dnxc_sdk_init() */
            dnxc_appl_bde_dev_used_by_destroyed_unit[unit] = soc_cm_unit_2_bde_dev(unit);
            dev_id = device_id;

        }
        else
        {        /** handle composite unit */

            const soc_cm_composite_dev_t *comp_info = soc_cm_get_composite_dev_info(unit);
            int *sub_units = dnxc_appl_sub_units_of_destroyed_unit + unit * SOC_MAX_NOF_COMPOSITE_SUB_DEVS;
            unsigned i, nof_sub_units;
            if (comp_info == NULL || comp_info->dev_type == NULL)
            {
                SHR_EXIT_WITH_LOG(_SHR_E_INTERNAL, "Bad composite device information for unit %d was not found%s%s\n",
                                  unit, EMPTY, EMPTY);
            }
            /** Get composite device information */
            dev_id = comp_info->dev_type->comp_dev_id;
            nof_sub_units = comp_info->dev_type->nof_sub_devs;
            if (nof_sub_units == 0 || nof_sub_units > SOC_MAX_NOF_COMPOSITE_SUB_DEVS)
            {
                SHR_EXIT_WITH_LOG(_SHR_E_UNIT, "Bad composite device type 0x%x composite unit %d%s\n", dev_id, unit,
                                  EMPTY);
            }
            /** Store the composite device information to later be used by appl_dnxc_sdk_init() */
            dnxc_appl_bde_dev_used_by_destroyed_unit[unit] = DNXC_APPL_DESTROYED_UNIT_WAS_COMPOSITE;
            dnxc_appl_composite_dev_type_of_destroyed_unit[unit] = dev_id;
            for (i = 0; i < nof_sub_units; ++i)
            {
                sub_units[i] = comp_info->sub_units[i];
                /** soc_cm_device_destroy() will destroy the unit to bde_dev mapping, so keep the bde dev for recreating the sub-unit by appl_dnxc_sdk_init() */
                dnxc_appl_bde_dev_used_by_destroyed_unit[sub_units[i]] = soc_cm_unit_2_bde_dev(sub_units[i]);
            }

        }

        LOG_INFO_EX(BSL_LOG_MODULE, "   %d: Detach unit\n%s%s%s", unit, EMPTY, EMPTY, EMPTY);
        rv = soc_cm_device_destroy(unit);
        SHR_IF_ERR_EXIT_WITH_LOG(rv, "soc_cm_device_destroy() for device_id %u Failed:\n%s%s", dev_id, EMPTY, EMPTY);
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
appl_dnxc_step_list_get(
    int unit,
    const appl_dnxc_init_step_t ** appl_steps)
{
    SHR_FUNC_INIT_VARS(unit);

#ifdef BCM_DNXF_SUPPORT
/* { */
    if (soc_is(unit, DNXF_DEVICE))
    {
        SHR_IF_ERR_EXIT(appl_dnxf_step_list_get(unit, appl_steps));
    }
    else
/* } */
#endif

#ifdef BCM_DNX_SUPPORT
/* { */
    if (soc_is(unit, DNX_DEVICE))
    {
        SHR_IF_ERR_EXIT(appl_dnx_step_list_get(unit, appl_steps));
    }
    else
/* } */
#endif
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Invalid Architecture\n");
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
appl_dnxc_step_time_thresh_list_get(
    int unit,
    const appl_init_time_thresh_info_t ** time_thresh_list)
{
    SHR_FUNC_INIT_VARS(unit);

#ifdef BCM_DNXF_SUPPORT
    if (soc_is(unit, DNXF_DEVICE))
    {
        SHR_IF_ERR_EXIT(appl_dnxf_step_time_thresh_list_get(unit, time_thresh_list));
    }
    else
#endif
#ifdef BCM_DNX_SUPPORT
/* { */
    if (soc_is(unit, DNX_DEVICE))
    {
        SHR_IF_ERR_EXIT(appl_dnx_step_time_thresh_list_get(unit, time_thresh_list));
    }
    else
/* } */
#endif
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Invalid Architecture\n");
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
appl_dnxc_per_dev_step_time_threshold_get(
    int unit,
    int step_id,
    sal_usecs_t * time_thresh)
{
    SHR_FUNC_INIT_VARS(unit);

#ifdef BCM_DNXF_SUPPORT
    if (soc_is(unit, DNXF_DEVICE))
    {
        SHR_IF_ERR_EXIT(appl_dnxf_per_dev_step_time_threshold_get(unit, step_id, time_thresh));
    }
    else
#endif
#ifdef BCM_DNX_SUPPORT
/* { */
    if (soc_is(unit, DNX_DEVICE))
    {
        SHR_IF_ERR_EXIT(appl_dnx_per_dev_step_time_threshold_get(unit, step_id, time_thresh));
    }
    else
/* } */
#endif
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Invalid Architecture\n");
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
appl_dnxc_per_dev_full_time_threshold_get(
    int unit,
    sal_usecs_t * time_thresh)
{
    SHR_FUNC_INIT_VARS(unit);

#ifdef BCM_DNXF_SUPPORT
    if (soc_is(unit, DNXF_DEVICE))
    {
        SHR_IF_ERR_EXIT(appl_dnxf_per_dev_full_time_threshold_get(unit, time_thresh));
    }
    else
#endif
#ifdef BCM_DNX_SUPPORT
/* { */
    if (soc_is(unit, DNX_DEVICE))
    {
        SHR_IF_ERR_EXIT(appl_dnx_per_dev_full_time_threshold_get(unit, time_thresh));
    }
    else
/* } */
#endif
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Invalid Architecture\n");
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Override init params. This function provies settin init params after cold boot.
 * This function should be used by external modules (diagnostics, testing, etc...)
 *
 * \param [in] unit - Unit ID
 * \param [Out] new_params - Pointer to init paramaters
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
appl_dnxc_init_params_set(
    int unit,
    appl_dnxc_init_param_t * new_params)
{
    SHR_FUNC_INIT_VARS(unit);

    sal_memcpy(&(init_param[unit]), new_params, sizeof(appl_dnxc_init_param_t));

    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
appl_dnxc_init_step_list_run(
    int unit,
    appl_dnxc_init_param_t * params)
{
    const appl_dnxc_init_step_t *appl_steps;

    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&init_param[unit], 0x0, sizeof(appl_dnxc_init_param_t));

    /** get the list to run */
    SHR_IF_ERR_EXIT(appl_dnxc_step_list_get(unit, &appl_steps));

    /** Get init params. */
    if (params != NULL)
    {
        SHR_IF_ERR_EXIT(appl_dnxc_init_params_set(unit, params));
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid init params\n");
    }

    /*
     * Deinit if needed
     */
    if (init_param[unit].no_deinit == 0)
    {
        LOG_INFO_EX(BSL_LOG_MODULE, "%d: APPL Deinit\n%s%s%s", unit, EMPTY, EMPTY, EMPTY);
        SHR_IF_ERR_EXIT(appl_dnxc_steps_convert_and_run(unit, appl_steps, FALSE));
        LOG_INFO_EX(BSL_LOG_MODULE, "%d: APPL Deinit Done\n%s%s%s", unit, EMPTY, EMPTY, EMPTY);
#if BCM_API_VERBOSE_LOGGING != 0
        /*
         * Integration with tr 141. If this deinit was called from tr 141 and
         * the relevant SOC property is set then reset the Logger.
         */
        if (cint_logger_tr141_get() &&
            (dnx_drv_soc_property_get(SOC_UNIT_NONE_SAL_CONFIG, spn_API_LOGGER_RESET_ON_TR141, 0) != 0))
        {

            LOG_INFO_EX(BSL_LOG_MODULE, "%d: Resetting the Logger\n%s%s%s", unit, EMPTY, EMPTY, EMPTY);
            cint_logger_reset();
        }
#endif
    }

#if AGGRESSIVE_ALLOC_DEBUG_TESTING
    if (params != NULL && params->is_resources_check)
    {
        int rv = 0;

        rv = init_aggressive_alloc_debug_testing(params->loop_id);
        if (rv < 0)
        {
            cli_out("Error: init_aggressive_alloc_debug_testing () Failed:\n");
        }
        if (params->aggressive_num_to_test == 0)
        {
            set_aggressive_num_to_test(0);
        }
        else
        {
            set_aggressive_num_to_test(params->aggressive_num_to_test);
        }
        set_aggressive_alloc_debug_testing_keep_order(params->aggressive_alloc_debug_testing_keep_order);
        set_aggressive_long_free_search(params->aggressive_long_free_search);
        if (params->loop_id == 1)
        {
#if INIT_ON_SECOND_LOOP
/* { */
            /*
             * User required to init in the second loop (for DVAPI)
             */
            init_param[unit].no_init = 0;
/* } */
#else
/* { */
            /*
             * There is no need to init in the second loop
             */
            init_param[unit].no_init = 1;
/* } */
#endif
        }
    }
#endif

    /*
     * Init if needed
     */
    if (init_param[unit].no_init == 0)
    {
#ifdef BCM_WARM_BOOT_SUPPORT
        if (init_param[unit].warmboot)
        {
            SHR_IF_ERR_EXIT(soc_scache_recover(unit));
            /*
             * turn on warmboot flag
             */
            SOC_WARM_BOOT_START(unit);
        }
#endif
        LOG_INFO_EX(BSL_LOG_MODULE, "%d: APPL Init\n%s%s%s", unit, EMPTY, EMPTY, EMPTY);
        SHR_IF_ERR_EXIT(appl_dnxc_steps_convert_and_run(unit, appl_steps, TRUE));
        LOG_INFO_EX(BSL_LOG_MODULE, "%d: APPL Init Done\n%s%s%s", unit, EMPTY, EMPTY, EMPTY);

#ifdef BCM_WARM_BOOT_SUPPORT
        /*
         * turn off warmboot flag
         */
        SOC_WARM_BOOT_DONE(unit);
#endif
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
appl_dnxc_step_list_id_run(
    int unit,
    int appl_id,
    const appl_dnxc_init_step_t * appl_steps,
    int is_forward)
{
    int is_found;
    utilex_seq_step_t *utilex_seq_list;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(appl_dnxc_init_step_list_convert(unit, appl_steps, &utilex_seq_list));

    /** run a step within a list by name */
    SHR_IF_ERR_EXIT(utilex_seq_run_step_by_id(unit, utilex_seq_list, appl_id, is_forward, &is_found));

    if (is_found == FALSE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid step id = %d\n", appl_id);
    }

exit:
     /* coverity[pass_freed_arg:FALSE]  */
    SHR_IF_ERR_EXIT(appl_dnxc_init_step_list_destory(unit, utilex_seq_list));
    SHR_FUNC_EXIT;
}

shr_error_e
appl_dnxc_step_list_name_run(
    int unit,
    char *appl_name,
    const appl_dnxc_init_step_t * appl_steps,
    int is_forward)
{
    int is_found;
    utilex_seq_step_t *utilex_seq_list;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(appl_dnxc_init_step_list_convert(unit, appl_steps, &utilex_seq_list));

    /** run a step within a list by name */
    SHR_IF_ERR_EXIT(utilex_seq_run_step_by_name(unit, utilex_seq_list, appl_name, is_forward, &is_found));

    if (is_found == FALSE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid step name = %s\n", appl_name);
    }

exit:
    /** free allocated memory */
     /* coverity[pass_freed_arg:FALSE]  */
    SHR_IF_ERR_EXIT(appl_dnxc_init_step_list_destory(unit, utilex_seq_list));
    SHR_FUNC_EXIT;
}

shr_error_e
appl_dnxc_clean_up(
    int unit)
{
#ifdef __SANITIZE_ADDRESS__
    appl_dnxc_init_param_t params;
#endif

    SHR_FUNC_INIT_VARS(unit);

    /** Disable the logging. */
    SHR_SET_SEVERITY_FOR_MODULE_SPECIFIC(BSL_LOG_MODULE, bslSeverityError);
    SHR_SET_SEVERITY_FOR_MODULE_SPECIFIC(BSL_LS_SHAREDSWDNX_UTILSDNX, bslSeverityError);
#ifdef __SANITIZE_ADDRESS__
    sal_memset(&params, 0, sizeof(params));
    params.no_init = 1;

    /** invoke common(dnx and dnxf) de-init sequence to perform clean-up */
    SHR_IF_ERR_EXIT(appl_dnxc_init_step_list_run(unit, &params));
#else /* __SANITIZE_ADDRESS__ */
    SHR_IF_ERR_EXIT(bcm_exit(unit, 0));
#endif /* __SANITIZE_ADDRESS__ */

exit:
    SHR_FUNC_EXIT;
}

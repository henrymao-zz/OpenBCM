/** \file src/bcm/dnx/cosq/flow_control/pfc_deadlock.c
 * 
 *
 * PFC Deadlock functions for DNX.\n
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 */

/*
 * $Copyright:.$
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_COSQ

#include <soc/sand/shrextend/shrextend_debug.h>
#include <shared/shr_thread_manager.h>
#include <shared/utilex/utilex_u64.h>

#include <soc/dnxc/dnxc_ha.h>
#include <soc/dnxc/swstate/dnxc_sw_state_utils.h>
#include <soc/dnx/dbal/dbal.h>
#include <soc/dnx/pll/pll.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_nif.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_fc.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_instru.h>
#include <soc/dnx/dnx_err_recovery_manager.h>
#include <soc/dnxc/dnxc_time.h>

#include <bcm/cosq.h>
#include <bcm/types.h>
#include <bcm/instru.h>

#include <bcm_int/dnx/algo/port/algo_port_mgmt.h>
#include <bcm_int/dnx/cosq/cosq.h>
#include <bcm_int/dnx/port/imb/imb.h>
#include <bcm_int/dnx/auto_generated/dnx_cosq_dispatch.h>
#include <bcm_int/dnx/auto_generated/dnx_switch_dispatch.h>
#include <bcm_int/dnx/auto_generated/dnx_port_dispatch.h>
#include <bcm_int/dnx/auto_generated/dnx_instru_dispatch.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/access/flow_control_access.h>

#include "../egress/ecgm_dbal.h"

/*
 * Global variables for PFC Deadlock breaking mechanism
 * - User configured callback function to be called during PFC Deadlock recovery
 * - Userdata to be used as input for the callback function
 */
bcm_cosq_pfc_deadlock_recovery_event_cb_t dnx_pfc_deadlock_recovery_event_cb = NULL;
void *pfc_deadlock_cb_userdata = NULL;

/**
 * \brief -  Called from the periodic event handler in order to
 * enable the PFC reception once the recovery timer has run out.
 */
static int
dnx_pfc_deadlock_recover(
    int unit,
    void *userdata)
{
    shr_error_e rv = _SHR_E_NONE;
    pfc_deadlock_recovery_userdata_t data;
    shr_thread_manager_handler_t pfc_deadlock_recovery_handler;
    SHR_FUNC_INIT_VARS(unit);

    /** Get the recovery data from SW State */
    SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.data.get(unit, &data));

    /** Call the API to end the PFC Deadlock recovery */
    SHR_IF_ERR_EXIT(bcm_dnx_cosq_pfc_deadlock_recovery_exit(unit, data.master_logical_port, -1));

    if (dnx_pfc_deadlock_recovery_event_cb != NULL)
    {
        /** Call PFC Deadlock recovery end CB for the appropriate Phy and PFC */
        dnx_pfc_deadlock_recovery_event_cb(unit, data.phy, data.pfc_num, bcmCosqPfcDeadlockRecoveryEventEnd,
                                           pfc_deadlock_cb_userdata);
    }

exit:
    /** Get the periodic event handle to stop the periodic event after one execution of the callback
     * Has to be after exit because the theread needs to be stopped even in case of error to avoid
     * infinite loop */
    rv = flow_control_db.pfc_deadlock_recovery.event_handle.get(unit, &pfc_deadlock_recovery_handler);
    if (rv != _SHR_E_NONE)
    {
        LOG_CLI((BSL_META("Fail - Getting the periodic event handle failed!")));
        SHR_SET_CURRENT_ERR(_SHR_E_FAIL);
    }
    rv = shr_thread_manager_stop(pfc_deadlock_recovery_handler, TRUE);
    if (rv != _SHR_E_NONE)
    {
        LOG_CLI((BSL_META("Fail - Stop the periodic event failed!")));
        SHR_SET_CURRENT_ERR(_SHR_E_FAIL);
    }
    SHR_FUNC_EXIT;
}

/**
 * See .h file
 */
int
dnx_interrupt_handles_corrective_action_for_pfc_deadlock(
    int unit,
    int block_instance,
    uint8 *is_cdu)
{
    int core;
    int ethu_id;
    int first_phy;
    int nof_lanes;
    int nof_phys;
    int occurances;
    int recovery_timer;
    int first_affected_phy;
    int ethu_port_num;
    shr_thread_manager_handler_t pfc_deadlock_recovery_handler;
    pfc_deadlock_recovery_userdata_t recovery_data;
    SHR_FUNC_INIT_VARS(unit);

    /** Determine the ETHU ID that is in deadlock */
    if (dnx_data_nif.eth.cdum_nof_get(unit) != 0)
    {
        int cdu_blks_in_core =
            (dnx_data_nif.eth.cdu_nof_get(unit) -
             dnx_data_nif.eth.cdum_nof_get(unit)) / dnx_data_device.general.nof_cores_get(unit);
        int cdum_blks_in_core = dnx_data_nif.eth.cdum_nof_get(unit) / dnx_data_device.general.nof_cores_get(unit);

        /** CDUM/CDU block structure */
        if (*is_cdu == FALSE)
        {
            /** CDUM */
            core = block_instance / cdum_blks_in_core;
            ethu_id = (block_instance % cdum_blks_in_core) + dnx_data_nif.eth.ethu_nof_per_core_get(unit) * core;
        }
        else
        {
            /** CDU */
            core = block_instance / cdu_blks_in_core;
            ethu_id = block_instance + cdum_blks_in_core * (core + 1);
        }
    }
    else
    {
        /** CDU/CLU block structure */
        if (*is_cdu == TRUE)
        {
            /** CDU */
            ethu_id = block_instance;
        }
        else
        {
            /** CLU */
            ethu_id = block_instance + dnx_data_nif.eth.cdu_nof_get(unit);
        }

        /** Determine the core */
        core = (ethu_id >= dnx_data_nif.eth.ethu_nof_per_core_get(unit)) ? 1 : 0;
    }

    /** Get the first Phy of the ETHU and the PFC Deadlock debug info.
     * The debug info will show which port internal for the ETHU is in deadlock.
     * Using the first Phy as offset, find the number of the Phy that is in deadlock.
     */
    SHR_IF_ERR_EXIT(dnx_algo_global_ethu_id_lane_info_get(unit, ethu_id, &first_phy, &nof_lanes));
    SHR_IF_ERR_EXIT(imb_pfc_deadlock_debug_info_get(unit, ethu_id, &ethu_port_num, &recovery_data.pfc_num));
    recovery_data.phy = first_phy + ethu_port_num;

    if (dnx_data_fc.general.feature_get(unit, dnx_data_fc_general_pfc_rec_cdu_shift))
    {
        /** The last two CDUs of each core have one bit shift left in the PFC mapping */
        SHR_IF_ERR_EXIT(dnx_algo_port_nif_phys_nof_phys_per_core_get(unit, core, &nof_phys));
        first_affected_phy = nof_phys - (2 * dnx_data_nif.eth.nof_lanes_in_cdu_get(unit));
        if ((recovery_data.phy % nof_phys) >= first_affected_phy)
        {
            recovery_data.pfc_num = (recovery_data.pfc_num == BCM_COS_MAX) ? BCM_COS_MIN : recovery_data.pfc_num + 1;
        }
    }

    /** Increment the "occurrences" counter */
    SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.
                    occurances.get(unit, recovery_data.phy, recovery_data.pfc_num, &occurances));
    occurances++;
    SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.
                    occurances.set(unit, recovery_data.phy, recovery_data.pfc_num, occurances));

    /** Determine the master logical port. This mechanism is applicable only for non-channalized ports */
    SHR_IF_ERR_EXIT(dnx_algo_port_nif_phy_to_logical_get
                    (unit, recovery_data.phy, 0, 0, &recovery_data.master_logical_port));

    /** Save the recovery data in SW State to be used in the periodic event callback */
    SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.data.set(unit, recovery_data));

    /** Call the API to start the PFC Deadlock recovery */
    SHR_IF_ERR_EXIT(bcm_dnx_cosq_pfc_deadlock_recovery_start(unit, recovery_data.master_logical_port, -1));

    if (dnx_pfc_deadlock_recovery_event_cb != NULL)
    {
        /** Call PFC Deadlock recovery begin CB for the appropriate Phy and PFC */
        dnx_pfc_deadlock_recovery_event_cb(unit, recovery_data.phy, recovery_data.pfc_num,
                                           bcmCosqPfcDeadlockRecoveryEventBegin, pfc_deadlock_cb_userdata);
    }

    /** Set the user data for the periodic event callback, then start and stop periodic event.
     * When periodic event is started it will wait a user defined interval and call a CB that will
     * restore the ability of the Phy to receive PFC and finish the recovery.
     * Get thread handle of event thread for PFC Deadlock recovery mechanism from SW-State
     */
    SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.event_handle.get(unit, &pfc_deadlock_recovery_handler));
    SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.
                    timer.get(unit, recovery_data.phy, recovery_data.pfc_num, &recovery_timer));
    SHR_IF_ERR_EXIT(shr_thread_manager_interval_set(pfc_deadlock_recovery_handler, recovery_timer));
    SHR_IF_ERR_EXIT(shr_thread_manager_start(pfc_deadlock_recovery_handler));

exit:
    SHR_FUNC_EXIT;
}

/** Define for the thread name of PFC Deadlock recovery periodic event thread */
#define PFC_DEADLOCK_RECOVERY_THREAD_NAME "PFC Deadlock recovery"

/**
 * \brief -  Initiallize the PFC deadlock recovery mechanism
 */
shr_error_e
dnx_pfc_deadlock_init(
    int unit)
{
    shr_error_e rv = _SHR_E_NONE;
    bcm_switch_event_control_t type;
    shr_thread_manager_config_t pfc_deadlock_recovery_config_info;
    shr_thread_manager_handler_t pfc_deadlock_recovery_handler;
    SHR_FUNC_INIT_VARS(unit);

    /** Allow SW state modifications during WB to be able to save the handle to the periodic event */
    SHR_IF_ERR_EXIT(dnxc_ha_tmp_allow_access_enable(unit, UTILEX_SEQ_ALLOW_SW_STATE));

    
    if (soc_is(unit, J2X_DEVICE))
    {
        SHR_EXIT();
    }

    /** Set the interrupt first and then set mask  to zero */
    type.action = bcmSwitchEventUnmaskAndClearDisable;
    type.index = BCM_CORE_ALL;
    {
        if (dnx_data_nif.eth.cdum_nof_get(unit) != 0)
        {
            type.event_id = dnx_data_fc.pfc_deadlock.cdum_intr_id_get(unit);
            SHR_IF_ERR_EXIT(bcm_dnx_switch_event_control_set(unit, BCM_SWITCH_EVENT_DEVICE_INTERRUPT, type, TRUE));
        }
        if (dnx_data_nif.eth.cdu_nof_get(unit) != 0)
        {
            type.event_id = dnx_data_fc.pfc_deadlock.cdu_intr_id_get(unit);
            SHR_IF_ERR_EXIT(bcm_dnx_switch_event_control_set(unit, BCM_SWITCH_EVENT_DEVICE_INTERRUPT, type, TRUE));
        }
        if (dnx_data_nif.eth.clu_nof_get(unit) != 0)
        {
            type.event_id = dnx_data_fc.pfc_deadlock.clu_intr_id_get(unit);
            SHR_IF_ERR_EXIT(bcm_dnx_switch_event_control_set(unit, BCM_SWITCH_EVENT_DEVICE_INTERRUPT, type, TRUE));
        }
    }

    /** Configure Thread */
    shr_thread_manager_config_t_init(&pfc_deadlock_recovery_config_info);
    pfc_deadlock_recovery_config_info.name = PFC_DEADLOCK_RECOVERY_THREAD_NAME;
    pfc_deadlock_recovery_config_info.bsl_module = BSL_LOG_MODULE;
    pfc_deadlock_recovery_config_info.type = SHR_THREAD_MANAGER_TYPE_EVENT;
    pfc_deadlock_recovery_config_info.interval = 1;
    pfc_deadlock_recovery_config_info.callback = dnx_pfc_deadlock_recover;
    pfc_deadlock_recovery_config_info.start_operation = FALSE;
    SHR_IF_ERR_EXIT(shr_thread_manager_create
                    (unit, &pfc_deadlock_recovery_config_info, &pfc_deadlock_recovery_handler));

    /** Save Thread handler to SW-State */
    SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.event_handle.set(unit, pfc_deadlock_recovery_handler));

    /** Set the default callback function to handle PFC Deadlock */
    dnx_pfc_deadlock_recovery_event_cb = NULL;
    pfc_deadlock_cb_userdata = NULL;

    {
        if (!sw_state_is_warm_boot(unit))
        {
        /** Reset the instrumentation counters */
            SHR_IF_ERR_EXIT(imb_instru_counters_reset_all(unit, TRUE));

        /** Reset the per-port counters */
            SHR_IF_ERR_EXIT(imb_instru_pfc_deadlock_counters_reset_all(unit));
        }
    }

exit:
    rv = dnxc_ha_tmp_allow_access_disable(unit, UTILEX_SEQ_ALLOW_SW_STATE);
    if (rv != _SHR_E_NONE)
    {
        LOG_CLI((BSL_META("Fail - Disabling SW State access during WB failed!")));
        SHR_SET_CURRENT_ERR(_SHR_E_FAIL);
    }
    SHR_FUNC_EXIT;
}

/**
 * \brief -  Deinitiallize the PFC deadlock recovery mechanism
 */
shr_error_e
dnx_pfc_deadlock_deinit(
    int unit)
{
    uint8 is_init = 0;
    shr_thread_manager_handler_t pfc_deadlock_recovery_handler = NULL;
    SHR_FUNC_INIT_VARS(unit);

    
    if (soc_is(unit, J2X_DEVICE))
    {
        SHR_EXIT();
    }

    /** Get thread handle of event thread for PFC Deadlock recovery mechanis from SW-State */
    SHR_IF_ERR_EXIT(flow_control_db.is_init(unit, &is_init));
    if (is_init == TRUE)
    {
        SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.event_handle.get(unit, &pfc_deadlock_recovery_handler));
    }

    /** Destroy periodic event thread for PFC Deadlock recovery mechanism */
    if (pfc_deadlock_recovery_handler != NULL)
    {
        SHR_IF_ERR_EXIT(shr_thread_manager_destroy(&pfc_deadlock_recovery_handler));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * See .h file
 */
shr_error_e
dnx_pfc_deadlock_recovery_event_cb_set(
    int unit,
    bcm_cosq_pfc_deadlock_recovery_event_cb_t callback,
    void *userdata)
{
    SHR_FUNC_INIT_VARS(unit);

    /** Set the user defined callback function to handle PFC Deadlock */
    dnx_pfc_deadlock_recovery_event_cb = callback;
    pfc_deadlock_cb_userdata = userdata;

    SHR_FUNC_EXIT;
}

 /**
  * \brief -
  * Register pfc deadlock recovery callback in PFC deadlock feature.
  *
  *   \param [in] unit - unit
  *   \param [in] callback - callback function
  *   \param [in] userdata - user data
  *   see shr_error_e
  * \remark
  *   * None
  * \see
  *   * None
  */
int
bcm_dnx_cosq_pfc_deadlock_recovery_event_register(
    int unit,
    bcm_cosq_pfc_deadlock_recovery_event_cb_t callback,
    void *userdata)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

     /** Set user defined callback function and userdata */
    SHR_IF_ERR_EXIT(dnx_pfc_deadlock_recovery_event_cb_set(unit, callback, userdata));

exit:
    SHR_FUNC_EXIT;
}

 /**
  * \brief -
  * Unregister pfc deadlock recovery callback in PFC deadlock feature.
  *
  *   \param [in] unit - unit
  *   \param [in] callback - callback function
  *   \param [in] userdata - user data
  *   see shr_error_e
  * \remark
  *   * None
  * \see
  *   * None
  */
int
bcm_dnx_cosq_pfc_deadlock_recovery_event_unregister(
    int unit,
    bcm_cosq_pfc_deadlock_recovery_event_cb_t callback,
    void *userdata)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

     /** Set user defined callback function and userdata */
    SHR_IF_ERR_EXIT(dnx_pfc_deadlock_recovery_event_cb_set(unit, NULL, NULL));

exit:
    SHR_FUNC_EXIT;
}

 /**
  * \brief -  Verify function for the input
  * parameters of bcm_dnx_cosq_pfc_deadlock_control_set/get
  */
static shr_error_e
dnx_cosq_pfc_deadlock_control_verify(
    int unit,
    bcm_port_t port,
    int pfc_priority,
    bcm_cosq_pfc_deadlock_control_t type,
    int arg,
    uint8 is_set)
{
    uint32 closest_interval_in_clocks = 0;
    uint32 interval_in_clocks;
/**    COMPILER_UINT64 time64; **/
    dnxc_time_t time_user;
    dnxc_time_t time_max;
    uint32 log2_val = 0;
    int granularity;
    bcm_instru_synced_counters_config_t config;
    SHR_FUNC_INIT_VARS(unit);

    COMPILER_64_ZERO(time_user.time);
    COMPILER_64_ZERO(time_max.time);
    COMPILER_64_ZERO(config.period);

    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, port));

    /*
     * Verify PFC priority
     */
    if ((pfc_priority < BCM_COS_MIN) || (pfc_priority > BCM_COS_MAX))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "PFC Priority is not valid. \n");
    }

    /** Verify type */
    if ((int) type < 0 || type >= bcmCosqPFCDeadlockControlTypeCount)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Type is not valid. \n");
    }

    if (is_set == TRUE)
    {
        switch (type)
        {
            case bcmCosqPFCDeadlockDetectionTimer:
                if (arg < 0)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Detection timer is not valid. \n");
                }
                /**
                 * Make sure the input value will not cause overflow when converted to clocks.
                 * The max possible value is the largest power of 2 of the user's input
                 * that can fit in a uint32.
                 */
                SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.
                                detection_timer_granularity.get(unit, &granularity));
                switch (granularity)
                {
                    case bcmCosqPFCDeadlockTimerInterval1MiliSecond:
                        granularity = 1;
                        break;
                    case bcmCosqPFCDeadlockTimerInterval10MiliSecond:
                        granularity = 10;
                        break;
                    case bcmCosqPFCDeadlockTimerInterval100MiliSecond:
                        granularity = 100;
                        break;
                    default:
                        break;
                }
                COMPILER_64_SET(time_user.time, 0, (uint32) arg);
                COMPILER_64_UMUL_32(time_user.time, (uint32) granularity);

                time_user.time_units = DNXC_TIME_UNIT_MILISEC;
                /**
                 * The value 0x7FFFFFFF is used, because the actual value writtent to HW is a power of 2 and
                 * The closest power of 2 to 0x7FFFFFFF is the biggest that can fit in 32 bits (only bit31 is set)
                 */
                SHR_IF_ERR_EXIT(dnxc_time_clock_cycles_to_time_get
                                (unit, 0x7FFFFFFF, DNXC_TIME_UNIT_MILISEC, &time_max));
                if (COMPILER_64_GT(time_user.time, time_max.time))
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Detection timer is not valid, above max value %d. \n",
                                 COMPILER_64_LO(time_max.time));
                }
                /**
                 * Value must be a power of two.
                 * Find the smallest power of two which is giving the closest result to the user's input.
                 */
                SHR_IF_ERR_EXIT(dnxc_time_time_to_clock_cycles_get(unit, &time_user, &interval_in_clocks));
                SHR_IF_ERR_EXIT(utilex_log2_round(interval_in_clocks, &log2_val));
                closest_interval_in_clocks = (1 << log2_val);

                /**
                 * The NIF instrumentation logic works based on counting intervals.
                 * After each interval the counters are reset and start over. The counters interval time must
                 * be larger than the detection time of the PFC deadlock recovery mechanism, otherwise the counters
                 * will always be reset before the detection time can be reached and a deadlock will never be detected.
                 * Counters interval is in nanoseconds.
                 */
                SHR_IF_ERR_EXIT(dnxc_time_clock_cycles_to_time_get
                                (unit, closest_interval_in_clocks, DNXC_TIME_UNIT_NSEC, &time_user));
                SHR_IF_ERR_EXIT(bcm_dnx_instru_synced_counters_config_get
                                (unit, 0, bcmInstruSyncedCountersTypeNif, &config));
                if (COMPILER_64_GT(time_user.time, config.period))
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM,
                                 "Detection timer is not valid, must be smaller than the interval period of NIF instrumentation logic. \n");
                }
                break;
            case bcmCosqPFCDeadlockDetectionAndRecoveryEnable:
                if ((arg < 0) || (arg > 1))
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Enable/disable indication is not valid. \n");
                }
                break;
            case bcmCosqPFCDeadlockRecoveryTimer:
                if (arg < 0)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Recovery timer is not valid. \n");
                }
                break;
            case bcmCosqPFCDeadlockTimerGranularity:
                if ((arg < bcmCosqPFCDeadlockTimerInterval1MiliSecond)
                    || (arg >= bcmSwitchPFCDeadlockDetectionIntervalCount))
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Detection interval is not valid. \n");
                }
                break;
            case bcmCosqPFCDeadlockRecoveryOccurrences:
                if (arg != 0)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Can not set recovery occurrences. \n");
                }
                break;
                 /* coverity[dead_error_begin:FALSE]  */
            default:
                break;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Get the event ID and block instance for PFC deadlock interrupt
 */
static shr_error_e
dnx_pfc_deadlock_block_index_event_id_get(
    int unit,
    bcm_port_t port,
    int *index,
    int *event_id)
{
    dnx_algo_port_ethu_access_info_t ethu_info;
    bcm_core_t core;
#ifdef BCM_DNX2_SUPPORT
    uint32 cdu_nof_per_core = 0;
    uint32 cdum_nof_per_core = 0;
#endif
    SHR_FUNC_INIT_VARS(unit);

    /** Get ETHU information */
    SHR_IF_ERR_EXIT(dnx_algo_port_ethu_access_info_get(unit, port, &ethu_info));
    SHR_IF_ERR_EXIT(dnx_algo_port_core_get(unit, port, &core));

    /** Determine the block index that needs to be enabled/disabled and the appropriate interrupt ID */
#ifdef BCM_DNX2_SUPPORT
    if (ethu_info.imb_type == imbDispatchTypeImb_cdu)
    {
        cdum_nof_per_core = dnx_data_nif.eth.cdum_nof_get(unit) / dnx_data_device.general.nof_cores_get(unit);
        cdu_nof_per_core = dnx_data_nif.eth.cdu_nof_get(unit) / dnx_data_device.general.nof_cores_get(unit);
        if (ethu_info.ethu_id_in_core < cdum_nof_per_core)
        {
            /** ETHU type is CDUM. IMB type index is used, because we need the CDUM block ID, which in case of CDU is the same as ETHU ID*/
            *index = ethu_info.imb_type_id - cdu_nof_per_core * core;
            *event_id = dnx_data_fc.pfc_deadlock.cdum_intr_id_get(unit);
        }
        else
        {
            /** ETHU type is CDU. The bellow calculation assumes that CDUM is always first in the core */
            *index = ethu_info.imb_type_id - (cdum_nof_per_core * (core + 1));
            *event_id = dnx_data_fc.pfc_deadlock.cdu_intr_id_get(unit);
        }
    }
    else if (ethu_info.imb_type == imbDispatchTypeImb_clu)
    {
        /** ETHU type is CLU. IMB type index is used, because we need the CLU block ID, which is different than ETHU ID */
        *index = ethu_info.imb_type_id;
        *event_id = dnx_data_fc.pfc_deadlock.clu_intr_id_get(unit);
    }
    else
#endif
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "PM type %d is not supported for port %d.", ethu_info.imb_type, port);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Clear PFC deadlock interrupt
 *
 * \param [in] unit - chip unit id
 * \param [in] port - port for which to clear interrupt
 * \return
 *   int - see _SHR_E_ *
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_pfc_deadlock_intr_clear(
    int unit,
    bcm_port_t port)
{
    bcm_switch_event_control_t control_type;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, port));

    /** Get the event ID and block instance */
    SHR_IF_ERR_EXIT(dnx_pfc_deadlock_block_index_event_id_get(unit, port, &control_type.index, &control_type.event_id));

    /** Set the interrupt mask */
    control_type.action = bcmSwitchEventClear;
    SHR_IF_ERR_EXIT(bcm_dnx_switch_event_control_set(unit, BCM_SWITCH_EVENT_DEVICE_INTERRUPT, control_type, TRUE));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Set enable/disable indication of the interrupt for PFC Deadlock recovery mechanism
 *
 * \param [in] unit - chip unit id
 * \param [in] port - port for which to enable/disable
 * \param [in] enable - enable indication
 * \return
 *   int - see _SHR_E_ *
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_pfc_deadlock_enable_set(
    int unit,
    bcm_port_t port,
    int enable)
{
    bcm_switch_event_control_t control_type;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, port));

    /** Get the event ID and block instance */
    SHR_IF_ERR_EXIT(dnx_pfc_deadlock_block_index_event_id_get(unit, port, &control_type.index, &control_type.event_id));

    /** Set the interrupt mask */
    control_type.action = bcmSwitchEventMask;
    SHR_IF_ERR_EXIT(bcm_dnx_switch_event_control_set
                    (unit, BCM_SWITCH_EVENT_DEVICE_INTERRUPT, control_type, ((enable == 0) ? TRUE : FALSE)));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Get enable/disable indication of the interrupt for PFC Deadlock recovery mechanism
 *
 * \param [in] unit - chip unit id
 * \param [in] port - port for which to enable/disable
 * \param [out] enable - enable indication
 * \return
 *   int - see _SHR_E_ *
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_pfc_deadlock_enable_get(
    int unit,
    bcm_port_t port,
    int *enable)
{
    uint32 masked;
    bcm_switch_event_control_t control_type;
    SHR_FUNC_INIT_VARS(unit);

    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, port));

    /** Get the event ID and block instance */
    SHR_IF_ERR_EXIT(dnx_pfc_deadlock_block_index_event_id_get(unit, port, &control_type.index, &control_type.event_id));

    /** Get the interrupt mask */
    control_type.action = bcmSwitchEventMask;
    SHR_IF_ERR_EXIT(bcm_dnx_switch_event_control_get(unit, BCM_SWITCH_EVENT_DEVICE_INTERRUPT, control_type, &masked));
    *enable = (masked == 0) ? TRUE : FALSE;

exit:
    SHR_FUNC_EXIT;
}

 /**
  * \brief -
  *      Set PFC Deadlock feature's config.
  * Parameters:
  *   \param [in] unit - Device unit number
  *   \param [in] port - Logical port num
  *   \param [in] pfc_priority - PFC priority
  *   \param [in] type - Type of the desired configuration.
  *   \param [in] arg  - Value
  *   see shr_error_e
  * \remark
  *   * None
  * \see
  *   * None
  */
int
bcm_dnx_cosq_pfc_deadlock_control_set(
    int unit,
    bcm_port_t port,
    int pfc_priority,
    bcm_cosq_pfc_deadlock_control_t type,
    int arg)
{
    int phy;
    int granularity;
    int ethu_id;
    dnxc_time_t time;
    dnxc_time_t time_converted;
    uint32 interval_in_clocks;
    bcm_port_t master_port;
    bcm_pbmp_t phys;
    uint32 max_duration_mask = 0;
    uint32 log2_val = 0;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_cosq_pfc_deadlock_control_verify(unit, port, pfc_priority, type, arg, TRUE));

    COMPILER_64_ZERO(time.time);
    COMPILER_64_ZERO(time_converted.time);

    SHR_IF_ERR_EXIT(dnx_algo_port_master_get(unit, port, 0, &master_port));
    SHR_IF_ERR_EXIT(dnx_algo_port_nif_phys_get(unit, master_port, 0, &phys));

    switch (type)
    {
        case bcmCosqPFCDeadlockDetectionAndRecoveryEnable:
            /**
             * Reset the instrumentation counters and clear any pre-existing interrupt
             * before enabling the PFC deadlock interrupt.
             */
            SHR_IF_ERR_EXIT(imb_port_instru_pfc_deadlock_counters_reset(unit, port));
            SHR_IF_ERR_EXIT(dnx_pfc_deadlock_intr_clear(unit, port));
            SHR_IF_ERR_EXIT(dnx_pfc_deadlock_enable_set(unit, port, arg));
            _SHR_PBMP_ITER(phys, phy)
            {
                SHR_IF_ERR_EXIT(dnx_algo_phy_to_ethu_id_get(unit, phy, &ethu_id));
                SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.enabled.set(unit, ethu_id, arg));
            }
            break;
        case bcmCosqPFCDeadlockDetectionTimer:
            /**
             * Check input
             */
            SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.detection_timer_granularity.get(unit, &granularity));
            switch (granularity)
            {
                case bcmCosqPFCDeadlockTimerInterval1MiliSecond:
                    granularity = 1;
                    break;
                case bcmCosqPFCDeadlockTimerInterval10MiliSecond:
                    granularity = 10;
                    break;
                case bcmCosqPFCDeadlockTimerInterval100MiliSecond:
                    granularity = 100;
                    break;
                default:
                    break;
            }
             /**
              * User input is in ms, but in HW the value must be set as clocks
              */
            COMPILER_64_SET(time.time, 0, (uint32) arg);
            COMPILER_64_UMUL_32(time.time, (uint32) granularity);

            time.time_units = DNXC_TIME_UNIT_MILISEC;
            SHR_IF_ERR_EXIT(dnxc_time_time_to_clock_cycles_get(unit, &time, &interval_in_clocks));

             /**
              * HW limitation - value must be a power of two.
              * Find the smallest power of two which is giving the closest result to the user's input.
              * Set the duration to HW. In HW the value is a mask, so set all bits above the allowed value.
              * The instrumentation counter perfoms a logical AND with the mask and when the result is != 0 the interrupt is triggered.
              */
            SHR_IF_ERR_EXIT(utilex_log2_round(interval_in_clocks, &log2_val));
            SHR_BITSET_RANGE(&max_duration_mask, log2_val, (SAL_UINT32_NOF_BITS - log2_val));
            _SHR_PBMP_ITER(phys, phy)
            {
                SHR_IF_ERR_EXIT(dnx_algo_phy_to_ethu_id_get(unit, phy, &ethu_id));
                SHR_IF_ERR_EXIT(imb_pfc_deadlock_max_duration_set(unit, ethu_id, max_duration_mask));
            }
            break;
        case bcmCosqPFCDeadlockRecoveryTimer:
            /**
             * User input is in miliseconds, but our mechanism works in micoseconds, so value must be converted.
             */
            COMPILER_64_ADD_32(time.time, arg);
            time.time_units = DNXC_TIME_UNIT_MILISEC;
            SHR_IF_ERR_EXIT(dnxc_time_units_convert(unit, &time, DNXC_TIME_UNIT_USEC, &time_converted));
            _SHR_PBMP_ITER(phys, phy)
            {
                SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.
                                timer.set(unit, phy, pfc_priority, COMPILER_64_LO(time_converted.time)));
            }
            break;
        case bcmCosqPFCDeadlockTimerGranularity:
            SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.detection_timer_granularity.set(unit, arg));
            break;
        case bcmCosqPFCDeadlockRecoveryOccurrences:
            _SHR_PBMP_ITER(phys, phy)
        {
            SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.occurances.set(unit, phy, pfc_priority, arg));
        }
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Switch control type is not valid for bcm_cosq_pfc_deadlock_control_set. \n");
            break;
    }

exit:
    SHR_FUNC_EXIT;
}

 /**
  * \brief -
  *      Get PFC Deadlock feature's config.
  * Parameters:
  *   \param [in] unit - Device unit number
  *   \param [in] port - Logical port num
  *   \param [in] pfc_priority - PFC priority
  *   \param [in] type - Type of the desired configuration to retrieve.
  *   \param [out] arg  - Pointer to retrieved value
  *   see shr_error_e
  * \remark
  *   * None
  * \see
  *   * None
  */
int
bcm_dnx_cosq_pfc_deadlock_control_get(
    int unit,
    bcm_port_t port,
    int pfc_priority,
    bcm_cosq_pfc_deadlock_control_t type,
    int *arg)
{
    int phy;
    int granularity;
    int ethu_id;
    int time_us;
    uint32 interval_in_clocks;
    uint32 max_duration_mask;
    bcm_port_t master_port;
    dnxc_time_t time;
    dnxc_time_t time_usec;
    int occurances;
    bcm_pbmp_t phys;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_cosq_pfc_deadlock_control_verify(unit, port, pfc_priority, type, *arg, FALSE));

    COMPILER_64_ZERO(time.time);
    COMPILER_64_ZERO(time_usec.time);

    SHR_IF_ERR_EXIT(dnx_algo_port_master_get(unit, port, 0, &master_port));
    SHR_IF_ERR_EXIT(dnx_algo_port_nif_first_phy_get(unit, master_port, 0, &phy));
    SHR_IF_ERR_EXIT(dnx_algo_phy_to_ethu_id_get(unit, phy, &ethu_id));

    switch (type)
    {
        case bcmCosqPFCDeadlockDetectionAndRecoveryEnable:
            SHR_IF_ERR_EXIT(dnx_pfc_deadlock_enable_get(unit, port, arg));
            break;
        case bcmCosqPFCDeadlockDetectionTimer:
            SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.detection_timer_granularity.get(unit, &granularity));
            switch (granularity)
            {
                case bcmCosqPFCDeadlockTimerInterval1MiliSecond:
                    granularity = 1;
                    break;
                case bcmCosqPFCDeadlockTimerInterval10MiliSecond:
                    granularity = 10;
                    break;
                case bcmCosqPFCDeadlockTimerInterval100MiliSecond:
                    granularity = 100;
                    break;
                default:
                    break;
            }
            SHR_IF_ERR_EXIT(imb_pfc_deadlock_max_duration_get(unit, ethu_id, &max_duration_mask));
            /** Coverity explanation - ARRAY_VS_SINGLETON for variables max_duration_mask
              * and interval_in_clocks. The reason is that the macro is iterating over the bits in the variables 
              * by performing pointer arithmetic */
             /* coverity[callee_ptr_arith:FALSE]  */
            SHR_BITNEGATE_RANGE(&max_duration_mask, 0, SAL_UINT32_NOF_BITS, &interval_in_clocks);
            interval_in_clocks = interval_in_clocks + 1;
             /**
              * User output must be in ms, but in HW the value is in clocks
              */
            SHR_IF_ERR_EXIT(dnxc_time_clock_cycles_to_time_get
                            (unit, interval_in_clocks, DNXC_TIME_UNIT_MILISEC, &time));
            COMPILER_64_UDIV_32(time.time, granularity);
            COMPILER_64_TO_32_LO(*arg, time.time);
            break;
        case bcmCosqPFCDeadlockRecoveryTimer:
            SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.timer.get(unit, phy, pfc_priority, &time_us));
            /**
             * User output is in miliseconds, but our mechanism works in micoseconds, so value must be converted.
             */
            COMPILER_64_SET(time_usec.time, 0, time_us);
            time_usec.time_units = DNXC_TIME_UNIT_USEC;
            SHR_IF_ERR_EXIT(dnxc_time_units_convert(unit, &time_usec, DNXC_TIME_UNIT_MILISEC, &time));
            *arg = COMPILER_64_LO(time.time);
            break;
        case bcmCosqPFCDeadlockTimerGranularity:
            SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.detection_timer_granularity.get(unit, arg));
            break;
        case bcmCosqPFCDeadlockRecoveryOccurrences:
            SHR_IF_ERR_EXIT(dnx_algo_port_nif_phys_get(unit, master_port, 0, &phys));
            *arg = 0;
            _SHR_PBMP_ITER(phys, phy)
            {
                occurances = 0;
                SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.
                                occurances.get(unit, phy, pfc_priority, &occurances));
                *arg += occurances;
            }
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Switch control type is not valid for bcm_cosq_pfc_deadlock_control_get. \n");
            break;
    }

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnx_cosq_pfc_deadlock_recovery_exit(
    int unit,
    bcm_port_t port,
    bcm_cos_t cosq)
{
    int action;
    bcm_core_t core_id;
    int base_q_pair;
    int num_priorities;
    uint32 q_pair;
    int phy;
    int ethu_id;
    int enabled;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, port));

    /** Enable the PFC reception of the port */
    SHR_IF_ERR_EXIT(bcm_dnx_port_control_set(unit, port, bcmPortControlPFCReceive, 1));

    /** Restore the chip behavior from what it was during recovery.
     * If the action is Transmit, nothing needs to be done.
     */
    SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.action.get(unit, &action));
    if (action == bcmSwitchPFCDeadlockActionDrop)
    {
        /** Get the core, base Q-pair of the port and the number of priorities and
         * re-enable all Q-pairs. This will cause the packets to that port to be transmitted.
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_core_get(unit, port, &core_id));
        SHR_IF_ERR_EXIT(dnx_algo_port_base_q_pair_get(unit, port, &base_q_pair));
        SHR_IF_ERR_EXIT(dnx_algo_port_priorities_nof_get(unit, port, &num_priorities));
        for (q_pair = base_q_pair; q_pair < (base_q_pair + num_priorities); q_pair++)
        {
            SHR_IF_ERR_EXIT(dnx_ecgm_dbal_queue_disable_set(unit, core_id, q_pair, 0));
        }
    }

    /**
     * Reset the instrumentation counters.
     */
    SHR_IF_ERR_EXIT(imb_port_instru_pfc_deadlock_counters_reset(unit, port));

    /**
     * Clear the interrupt and restore the enabler for the interrupt to it's default.
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_nif_first_phy_get(unit, port, 0, &phy));
    SHR_IF_ERR_EXIT(dnx_algo_phy_to_ethu_id_get(unit, phy, &ethu_id));
    SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.enabled.get(unit, ethu_id, &enabled));
    SHR_IF_ERR_EXIT(dnx_pfc_deadlock_intr_clear(unit, port));
    SHR_IF_ERR_EXIT(dnx_pfc_deadlock_enable_set(unit, port, enabled));

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnx_cosq_pfc_deadlock_recovery_start(
    int unit,
    bcm_port_t port,
    bcm_cos_t cosq)
{
    int action;
    bcm_core_t core_id;
    int base_q_pair;
    int num_priorities;
    uint32 q_pair;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    /** Verify logical port is valid */
    SHR_IF_ERR_EXIT(dnx_algo_port_valid_verify(unit, port));

    /** Disable the interrupt.
     * This is done in case a deadlock occurs while user has called custom recovery,
     * in order to void calling recovery functions twice.
     */
    SHR_IF_ERR_EXIT(dnx_pfc_deadlock_enable_set(unit, port, 0));

    /** Configure the chip behavior during recovery.
     * If the action is Transmit, nothing needs to be done.
     */
    SHR_IF_ERR_EXIT(flow_control_db.pfc_deadlock_recovery.action.get(unit, &action));
    if (action == bcmSwitchPFCDeadlockActionDrop)
    {
        /** Get the core, base Q-pair of the port and the number of priorities and
         * disable all Q-pairs. This will cause the packets to that port to be dropped.
         */
        SHR_IF_ERR_EXIT(dnx_algo_port_core_get(unit, port, &core_id));
        SHR_IF_ERR_EXIT(dnx_algo_port_base_q_pair_get(unit, port, &base_q_pair));
        SHR_IF_ERR_EXIT(dnx_algo_port_priorities_nof_get(unit, port, &num_priorities));
        for (q_pair = base_q_pair; q_pair < (base_q_pair + num_priorities); q_pair++)
        {
            SHR_IF_ERR_EXIT(dnx_ecgm_dbal_queue_disable_set(unit, core_id, q_pair, 1));
        }
    }

    /** Disable the PFC reception of the port */
    SHR_IF_ERR_EXIT(bcm_dnx_port_control_set(unit, port, bcmPortControlPFCReceive, 0));

exit:
    SHR_FUNC_EXIT;
}

/** \file egr_queuing_tune.c
 * Tuning of egress queuing parameters
 * 
 * NOTE: as this code is invoked from iside SDK, 
 * API invocation is done via bcm_dnx_XXX functions.
 * When this code is taken outside SDK, 
 * these calls should be replaced by bcm_XXX functions.
 */

/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_INITSEQDNX

/*
 * Include files.
 * {
 */
#include <soc/sand/shrextend/shrextend_debug.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_egr_queuing.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_egr_queuing_v1.h>
#include <bcm/cosq.h>
#include <bcm_int/dnx/auto_generated/dnx_fabric_dispatch.h>
#include <bcm_int/dnx/auto_generated/dnx_cosq_dispatch.h>
#include <bcm_int/dnx/algo/port/algo_port_mgmt.h>
#include <bcm_int/dnx/cosq/egress/rate_measurement.h>
#include <bcm_int/dnx/cosq/egress/egr_queuing.h>

/*
 * }
 * Include files.
 */

/** 24 = 12 (ipg) + 8 (preamble) + 4 (crc)*/
#define DNX_TUNE_EGR_QUEUING_PORT_RATE_COMPENSATION    24

/*
 * See .h file
 */

shr_error_e
dnx_tune_egr_ofp_rate_set(
    int unit,
    bcm_port_t port,
    int if_speed,
    int commit_changes,
    int is_remove)
{
    bcm_port_t master_port;
    bcm_cos_queue_t cosq;
    int num_priorities;
    bcm_gport_t gport, channelized;
    int nof_channels;
    int rate_measurement;
    dnx_algo_port_info_s port_info;
    bcm_pbmp_t rcy_logical_ports;
    bcm_core_t core;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_egr_queuing_v1.general.feature_get(unit, dnx_data_egr_queuing_v1_general_v1_supported))
    {
        /** Nothing to be done */
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(dnx_algo_port_priorities_nof_get(unit, port, &num_priorities));
    SHR_IF_ERR_EXIT(dnx_algo_port_master_get(unit, port, DNX_ALGO_PORT_MASTER_F_TM, &master_port));
    SHR_IF_ERR_EXIT(dnx_algo_port_is_channelized_get(unit, port, &channelized));
    SHR_IF_ERR_EXIT(dnx_algo_port_channels_nof_get(unit, port, &nof_channels));

    SHR_IF_ERR_EXIT(dnx_algo_port_info_get(unit, port, &port_info));
    if (DNX_ALGO_PORT_TYPE_IS_RCY(unit, port_info))
    {
        /** in case of RCY, need to consider ports of both RCY interfaces */
        SHR_IF_ERR_EXIT(dnx_algo_port_core_get(unit, port, &core));
        SHR_IF_ERR_EXIT(dnx_algo_port_logicals_get(unit, core, DNX_ALGO_PORT_LOGICALS_TYPE_RCY, 0, &rcy_logical_ports));

        BCM_PBMP_COUNT(rcy_logical_ports, nof_channels);
    }

    /** set speed to be 1% speedup over interface speed */
    if_speed = if_speed + (if_speed / 100) * 1;

    rate_measurement = if_speed / nof_channels;

    /*
     * set interface rate:
     * 1. For channelized interfaces only (since if non-channelized - the if shaper is set to max and port shaper is doing the shaping)
     * and
     * 2. One of the below
     *     a. When adding / changing port (!is_remove) and this is master port (port == master_port)
     *     or
     *     b. When removing port (is_remove) and this is the last port (nof_channels == 1)
     */
    if (channelized)
    {
        if (((port == master_port) && (!is_remove)) || ((nof_channels == 1) && (is_remove)))
        {
            BCM_GPORT_LOCAL_SET(gport, port);
            SHR_IF_ERR_EXIT(bcm_fabric_port_get(unit, gport, 0, &gport));
            /*
             * Use if_speed (and not egr_speed) for interface
             */
            SHR_IF_ERR_EXIT(bcm_dnx_cosq_gport_bandwidth_set(unit, gport, 0, 0, if_speed, 0));
        }
    }

    /*
     * set port rate
     * Optimization: Only the last port will perform a commit to HW, according to commit_changes argument.
     */
    BCM_GPORT_LOCAL_SET(gport, port);
    SHR_IF_ERR_EXIT(bcm_dnx_cosq_gport_bandwidth_set
                    (unit, gport, 0, 0, rate_measurement, commit_changes ? 0 : BCM_COSQ_BW_NOT_COMMIT));

    /*
     * set queue rate
     */
    for (cosq = 0; cosq < num_priorities; cosq++)
    {
        BCM_COSQ_GPORT_PORT_TC_SET(gport, port);
        SHR_IF_ERR_EXIT(bcm_dnx_cosq_gport_bandwidth_set(unit, gport, cosq, 0, rate_measurement, 0));
    }

    /*
     * configure tcg rate for supported number of priorities
     */
    if (num_priorities >= dnx_data_egr_queuing.params.tcg_min_priorities_get(unit))
    {
        BCM_COSQ_GPORT_PORT_TCG_SET(gport, port);
        SHR_IF_ERR_EXIT(bcm_dnx_cosq_gport_bandwidth_set(unit, gport, 0, 0, rate_measurement, 0));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -  egress queuing rate implementation V0 for device tuning.
 *
 * \param [in] unit -  Unit-ID
  *  *
 * \return
 *   shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */ shr_error_e
dnx_tune_egr_queuing_rate_tune_v0(
    int unit)
{
    int if_speed, if_speed_khz;
    bcm_port_t port, last_port;
    bcm_pbmp_t port_bm;
    int is_remove = 0;
    int rate_measurement_supported, interval;
    int port_has_speed;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * perform rate tuning for egress per port.
     */
    SHR_IF_ERR_EXIT(dnx_algo_port_logicals_get(unit, BCM_CORE_ALL, DNX_ALGO_PORT_LOGICALS_TYPE_TM_EGR_QUEUING,
                                               0, &port_bm));
    _SHR_PBMP_REVERSE_ITER(port_bm, last_port)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_has_speed(unit, last_port, 0, &port_has_speed));
        if (port_has_speed)
        {
            break;
        }
    }
    BCM_PBMP_ITER(port_bm, port)
    {
        SHR_IF_ERR_EXIT(dnx_algo_port_has_speed(unit, port, 0, &port_has_speed));
        if (port_has_speed)
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_interface_rate_get(unit, port, DNX_ALGO_PORT_SPEED_F_TX, &if_speed));

            if_speed_khz = if_speed * 1000;

            SHR_IF_ERR_EXIT(dnx_tune_egr_ofp_rate_set(unit, port, if_speed_khz, (port == last_port), is_remove));
        }
    }

    /*
     * set interval and weight for egress rate measure
     */
    rate_measurement_supported =
        dnx_data_egr_queuing.rate_measurement.feature_get(unit, dnx_data_egr_queuing_rate_measurement_is_supported);
    if (rate_measurement_supported)
    {
        /** default interval is 10 usec */
        interval = 10;
        SHR_IF_ERR_EXIT(dnx_rate_measurement_interval_set(unit, interval));

        SHR_IF_ERR_EXIT(dnx_rate_measurement_weight_set(unit, BCM_COSQ_RATE_WEIGHT_FULL));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_tune_egr_queuing_rate_tune(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);
    if (dnx_data_egr_queuing_v1.general.feature_get(unit, dnx_data_egr_queuing_v1_general_v1_supported))
    {
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_tune_egr_queuing_rate_tune_v0(unit));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_tune_egr_queuing_port_add(
    int unit,
    bcm_port_t port)
{
    bcm_gport_t gport;
    int port_rate_compensation = DNX_TUNE_EGR_QUEUING_PORT_RATE_COMPENSATION;
    SHR_FUNC_INIT_VARS(unit);

    /** map queue to tcg and configure tcg rate for supported number of priorities */
    if (dnx_data_egr_queuing.params.feature_get(unit, dnx_data_egr_queuing_params_tcg))
    {
        int num_priorities;
        SHR_IF_ERR_EXIT(dnx_algo_port_priorities_nof_get(unit, port, &num_priorities));
        if (num_priorities >= dnx_data_egr_queuing.params.tcg_min_priorities_get(unit))
        {
            /** check if TCG to TC mapping feature is supported */
            if (dnx_data_egr_queuing.params.feature_get(unit, dnx_data_egr_queuing_params_tcg_mapping))
            {
                /** if supported map as follows (legacy mapping) */
                for (bcm_cos_queue_t cosq = 0; cosq < num_priorities; cosq++)
                {
                    BCM_COSQ_GPORT_PORT_TC_SET(gport, port);
                    SHR_IF_ERR_EXIT(bcm_dnx_cosq_gport_sched_set(unit, gport, cosq, 0, -1));
                }
            }
            else
            {
                /** either 1 to 1 mapping between TC to TCG using internal API was done as part of port add
                 *  since BCM API is not supported for this Arch or no mapping is done at all because feature is
                 *  also not part of the HW and not supported in device Arch */
            }
        }
    }

    if (dnx_data_egr_queuing_v1.general.feature_get(unit, dnx_data_egr_queuing_v1_general_v1_supported))
    {
    }

    /** configure rate compensation */
    BCM_GPORT_LOCAL_SET(gport, port);
    SHR_IF_ERR_EXIT(bcm_dnx_cosq_control_set(unit, gport, 0, bcmCosqControlPacketLengthAdjust, port_rate_compensation));

exit:
    SHR_FUNC_EXIT;
}

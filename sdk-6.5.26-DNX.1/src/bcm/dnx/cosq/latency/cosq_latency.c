/** \file cosq_latency.c
 * 
 *
 * General cosq latency functionality \n
 * relevant for ingress and egress (end to end) latency
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
#define BSL_LOG_MODULE BSL_LS_BCMDNX_COSQ

/*
 * Include files.
 * {
 */
#include <soc/sand/shrextend/shrextend_debug.h>
#include <bcm/cosq.h>
#include <soc/dnx/dbal/dbal.h>
#include <soc/dnx/dnx_err_recovery_manager.h>
#include <bcm/types.h>
#include <bcm_int/dnx/cmn/dnxcmn.h>
#include <bcm_int/dnx/stk/stk_sys.h>
#include <bcm_int/dnx/cosq/latency/cosq_latency.h>
#include <bcm_int/dnx/cosq/aqm/cosq_aqm.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/access/cosq_latency_access.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/access/cosq_aqm_access.h>
#include <bcm_int/dnx/algo/res_mngr/resource_tag_bitmap.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_ipq.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_ingr_congestion.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_headers.h>
#include <soc/dnx/dbal/auto_generated/dbal_defines_fields.h>
#include <bcm_int/dnx/algo/algo_gpm.h>
#include <bcm_int/dnx/stat/stat_pp.h>
#include <bcm_int/dnx/init/init.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_latency.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_cosq_aqm.h>
#include <shared/utilex/utilex_u64.h>
#include <bcm_int/dnx/algo/port/algo_port_mgmt.h>
#include <bcm_int/dnx/port/port.h>
#include <bcm_int/dnx/cosq/ingress/ipq.h>
/*
 * }
 */

/*
 * Defines
 * {
 */
#define DNX_COSQ_LATENCY_QUEUE_QUARTET_RESOLUTION (4)

#define DNX_COSQ_LATENCY_END_TO_END_AQM_PKT_IS_CLASSIC_LQ (1)
#define DNX_COSQ_LATENCY_END_TO_END_AQM_PKT_IS_COUPLED_CLASSIC (2)
#define DNX_COSQ_LATENCY_END_TO_END_AQM_PKT_IS_COUPLED_LQ (4)

#define DNX_COSQ_LATENCY_DEFAULT_PROFILE (0)
/*
 * }
 */

/** See .h file */
void
dnx_cosq_latency_queue_template_print_cb(
    int unit,
    const void *data)
{
#ifdef DNX_SW_STATE_DIAGNOSTIC
    dnx_cosq_latency_queue_template_t *profile_info = (dnx_cosq_latency_queue_template_t *) data;
#endif
    SW_STATE_PRETTY_PRINT_INIT_VARIABLES();

    SW_STATE_PRETTY_PRINT_ADD_LINE(SW_STATE_PRETTY_PRINT_TYPE_STRING, NULL, "latency queue profile info:", NULL, NULL);
    SW_STATE_PRETTY_PRINT_ADD_LINE(SW_STATE_PRETTY_PRINT_TYPE_UINT32, "latency_map", profile_info->latency_map, NULL,
                                   "%d");
    SW_STATE_PRETTY_PRINT_ADD_LINE(SW_STATE_PRETTY_PRINT_TYPE_UINT32, "tc_map", profile_info->tc_map, NULL, "%d");
    SW_STATE_PRETTY_PRINT_FINISH();
    return;
}

static shr_error_e
bcm_dnx_cosq_latency_profile_nof_profiles_get(
    int unit,
    bcm_gport_t profile_gport,
    int *nof_profiles)
{
    int nof_profiles_get = 0;
    SHR_FUNC_INIT_VARS(unit);

    /** Get is_allocated per profile type*/
    if (BCM_GPORT_IS_INGRESS_LATENCY_PROFILE(profile_gport))
    {
        nof_profiles_get = dnx_data_latency.profile.ingress_nof_get(unit);
    }
    else if (BCM_GPORT_IS_END_TO_END_LATENCY_PROFILE(profile_gport))
    {
        nof_profiles_get = dnx_data_latency.profile.egress_nof_get(unit);
    }
    else if (BCM_GPORT_IS_END_TO_END_AQM_LATENCY_PROFILE(profile_gport))
    {
        nof_profiles_get = dnx_data_cosq_aqm.general.profile_nof_get(unit);
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid gport_profile %d", profile_gport);
    }

    *nof_profiles = nof_profiles_get;

exit:
    SHR_FUNC_EXIT;

}

static shr_error_e
bcm_dnx_cosq_latency_profile_id_get(
    int unit,
    bcm_gport_t profile_gport,
    int *profile_id)
{
    int profile_id_get = 0;
    SHR_FUNC_INIT_VARS(unit);

    if (BCM_GPORT_IS_INGRESS_LATENCY_PROFILE(profile_gport))
    {
        profile_id_get = BCM_GPORT_INGRESS_LATENCY_PROFILE_GET(profile_gport);
    }
    else if (BCM_GPORT_IS_END_TO_END_LATENCY_PROFILE(profile_gport))
    {
        profile_id_get = BCM_GPORT_END_TO_END_LATENCY_PROFILE_GET(profile_gport);
    }
    else if (BCM_GPORT_IS_END_TO_END_AQM_LATENCY_PROFILE(profile_gport))
    {
        profile_id_get = BCM_GPORT_LATENCY_END_TO_END_AQM_LATENCY_PROFILE_GET(profile_gport);
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid gport_profile %d", profile_gport);
    }

    *profile_id = profile_id_get;

exit:
    SHR_FUNC_EXIT;

}

static shr_error_e
bcm_dnx_cosq_latency_profile_is_allocated_verify(
    int unit,
    bcm_gport_t profile_gport,
    uint8 expected_is_allocated)
{
    uint8 is_allocated = 0;
    int profile_id = 0;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(bcm_dnx_cosq_latency_profile_id_get(unit, profile_gport, &profile_id));

    /** Get is_allocated per profile type*/
    if (BCM_GPORT_IS_INGRESS_LATENCY_PROFILE(profile_gport))
    {
        SHR_IF_ERR_EXIT(dnx_cosq_latency_db.ingress_latency_res.is_allocated(unit, profile_id, &is_allocated));
    }
    else if (BCM_GPORT_IS_END_TO_END_LATENCY_PROFILE(profile_gport))
    {
        SHR_IF_ERR_EXIT(dnx_cosq_latency_db.end_to_end_latency_res.is_allocated(unit, profile_id, &is_allocated));
    }
    else if (BCM_GPORT_IS_END_TO_END_AQM_LATENCY_PROFILE(profile_gport))
    {
        SHR_IF_ERR_EXIT(dnx_cosq_aqm_db.aqm_profile_res.is_allocated(unit, profile_id, &is_allocated));
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid gport_profile %d", profile_gport);
    }

    /** Verify is profile's is_allocated is as expected */
    if (is_allocated != expected_is_allocated)
    {
        if (expected_is_allocated)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Profile must be allocated, profile_id=%d", profile_id);
        }
        else
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Profile is already allocated, profile_id=%d", profile_id);
        }
    }

exit:
    SHR_FUNC_EXIT;

}

/**
* \brief
*  get from HW whether or not the profile in single mode (not coupled)
* \param [in] unit -unit id
* \param [in] profile_id - profile_id
* \param [out] is_typ - TRUE/FALSE
* \return
*    shr_error_e
* \remark
*   NONE
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_aqm_probability_marking_is_typ(
    int unit,
    int profile_id,
    uint32 *is_typ)
{

    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (dnx_data_latency.features.feature_get(unit, dnx_data_latency_features_coupled_mode_support))
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_DROP_CNI_PROFILE, &entry_handle_id));

        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);
        /** in order to know which profile to update need to know
         *  what type is the packet
         *  typical; LQ/Coupled Q */
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_L4_AQM_TYP_ENABLE, INST_SINGLE, is_typ);
        SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
    }

    else
    {
        /**Single mode use typical packets only */
        *is_typ = 1;
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  get from HW whether or not the ingress ECN marking enabled for the given profile
* \param [in] unit - unit id
* \param [in] profile_id -  control type
* \param [out] is_enabled - true/false
* \return
*    shr_error_e
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_ingress_ecn_marking_is_enable(
    int unit,
    int profile_id,
    uint32 *is_enabled)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_INGRESS_PROFILE, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);

    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_CNI_ENABLE, INST_SINGLE, is_enabled);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  get from HW whether or not the probabilistic ECN marking is enable for the given profile
* \param [in] unit - unit id
* \param [in] profile_id - end-to-end-aqm profile id
* \param [in] pkt_is_typ - is single or coupled mode
* \param [out] is_enable - true/false
* \return
*    shr_error_e
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_aqm_probability_ecn_marking_is_enable(
    int unit,
    int profile_id,
    int pkt_is_typ,
    uint32 *is_enable)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_DROP_CNI_PROFILE, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);

    if (dnx_data_latency.features.feature_get(unit, dnx_data_latency_features_probabilistic_legacy_mechanism_support))
    {
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_CQ_CNI_PROB_ENABLE, INST_SINGLE, is_enable);
    }

    else
    {
        dbal_value_field32_request(unit, entry_handle_id,
                                   (pkt_is_typ) ? DBAL_FIELD_CNI_PROB_ENABLE : DBAL_FIELD_LQ_CNI_PROB_ENABLE,
                                   INST_SINGLE, is_enable);
    }

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  get from HW whether or not the ECN marking is enable for the given profile
* \param [in] unit - unit id
* \param [in] profile_id - end-to-end-aqm profile id
* \param [in] pkt_is_typ - is single or coupled mode
* \param [out] is_enable - true/false
* \return
*    shr_error_e
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_aqm_ecn_marking_is_enable(
    int unit,
    int profile_id,
    int pkt_is_typ,
    uint32 *is_enable)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_DROP_CNI_PROFILE, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);

    if (dnx_data_latency.features.feature_get(unit, dnx_data_latency_features_coupled_mode_support))
    {
        dbal_value_field32_request(unit, entry_handle_id,
                                   (pkt_is_typ) ? DBAL_FIELD_CNI_MAX_ENABLE : DBAL_FIELD_LQ_CNI_MAX_ENABLE, INST_SINGLE,
                                   is_enable);
    }

    else
    {
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_CNI_MAX_ENABLE, INST_SINGLE, is_enable);
    }

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  verify type parameter for control API with ingress latency
* \param [in] unit - unit id
* \param [in] type -  control type
* \return
*    shr_error_e
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_ingress_probability_control_type_verify(
    int unit,
    bcm_cosq_control_t type)
{
    SHR_FUNC_INIT_VARS(unit);

    if (!dnx_data_latency.
        features.feature_get(unit, dnx_data_latency_features_ingress_ecn_probabilistic_mechanism_support)
        && (type == bcmCosqControlLatencyEcnProbEnable || type == bcmCosqControlLatencyEcnProbBaseThreshold))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for ingress latency profile \n", type);
    }

    if (!dnx_data_latency.features.feature_get(unit, dnx_data_latency_features_drop_probabilistic_mechanism_support) &&
        (type == bcmCosqControlLatencyDropProbEnable || type == bcmCosqControlLatencyDropProbBaseThreshold))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for ingress latency profile \n", type);

    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Initialize HW formula for legacy probabilistic ecn marking mechanism support
* \param [in] unit -unit id
* \return
*    shr_error_e
* \remark
*
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_aqm_legacy_probabilistic_mechanism_ecn_marking_formula_init(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /*
     * Turn off lines 1,2,3 and 6 in the flowing formula:
     *
     * LQ_MAX_CNI & (LQ_CNI_MAX_Enable & Packet_is_LQ & LQ_In_Profile) |
     * LQ_PROB_CNI & (LQ_CNI_PROB_Enable & Packet_is_LQ & LQ_In_Profile) |
     * CQ_PROB_AVG_CNI & (CQ_CNI_PROB_Enable & Packet_is_CQ) |
     * CQ_PROB_AVG_CNI & (CQ_CNI_PROB_Enable & (Packet_is_LQ & (~LQ_In_Profile))) |
     * TYP_MAX_CNI & (TYP_CNI_MAX_Enable & Packet_is_TYP) |
     * TYP_PROB_AVG_CNI & (TYP_CNI_PROB_Enable & Packet_is_TYP)
     */

    /*
     * Set profile configurations
     */
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_DROP_CNI_PROFILE, &entry_handle_id));

        dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, DBAL_RANGE_ALL, DBAL_RANGE_ALL);

        /** Line 1 should be off */
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LQ_CNI_MAX_ENABLE, INST_SINGLE, 0);
        }

        /** Line 2 should be off */
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LQ_CNI_PROB_ENABLE, INST_SINGLE, 0);
        }

        /** Line 4 should be on */
        {
            /*
             * set by control bcmCosqControlLatencyEcnProbEnable
             */
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CQ_CNI_PROB_ENABLE, INST_SINGLE, 0);
            /*
             * will be alwaize 1 for devices with no coupled mode
             */
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_L4_AQM_LQ_ENABLE, INST_SINGLE, 1);
        }

        /** Line 5 should be on */
        {
            /*
             * set by control bcmCosqControlLatencyEcnEnable
             */
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CNI_MAX_ENABLE, INST_SINGLE, 0);
            /*
             * will be alwaize 1 for devices with no coupled mode
             */
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_L4_AQM_TYP_ENABLE, INST_SINGLE, 1);
        }

        /** Line 6 should be off */
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CNI_PROB_ENABLE, INST_SINGLE, 0);
        }

        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

    /*
     * Set packet classification configurations
     */
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_PACKET_CLASSIFICATION, &entry_handle_id));

        dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_ECN_PROFILE, DBAL_RANGE_ALL, DBAL_RANGE_ALL);

        /** Line 3 should be off */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_CQ, INST_SINGLE, 0);

        /** Line 4 should be on */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_LQ, INST_SINGLE, 1);

        /** Line 5 should be on */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_TYP, INST_SINGLE, 1);

        /** No line, have to be enabled in order to allow latency drop */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_DE, INST_SINGLE, 1);

        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;

}

/**
* \brief
*  configure the maintenance of the average latency - whether
*  to use new average / new instantaneous latency for all the packet's types
*
*   note that change in LATENCY_EGRESS_PACKET_CLASSIFICATION
*   affects table EGRESS_MAINTAIN_AVERAGE_LATENCY as the keys
*   are connected
* \param [in] unit -unit id
* \return
*    shr_error_e
* \remark
*   None
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_aqm_legacy_probabilistic_mechanism_maintain_average_init(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_MAINTAIN_AVERAGE_LATENCY, &entry_handle_id));

    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PKT_TYPE_KEY, DBAL_RANGE_ALL, DBAL_RANGE_ALL);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_USE_NEW_AVG, INST_SINGLE, TRUE);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_USE_NEW_INST, INST_SINGLE, TRUE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
* end to end latency probability mapping HW set
*  update the mantissa/exponent dbal table
* \param [in] unit -unit id
* \param [in] mantissa - mantissa key
* \param [in] exponent - exponent key
* \param [in] mantissa_new  - the HW value of the mantissa
*        mapped to the given key
* \param [in] exponent_new  - the HW value of the mantissa
*        mapped to the given key
* \return
*    shr_error_e
* \remark
*
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_aqm_ecn_probability_map_dbal_set(
    int unit,
    int mantissa,
    int exponent,
    int mantissa_new,
    int exponent_new)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_PROBABILITY_MAPPING, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_MANTISSA, mantissa);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_EXPONENT, exponent);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_MAPPED_MANTISSA, INST_SINGLE, mantissa_new);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_MAPPED_EXPONENT, INST_SINGLE, exponent_new);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
* Set default mantissa and exponent for identity probability for all the packet's types
* \param [in] unit -unit id
* \return
*    shr_error_e
* \remark
*
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_aqm_legacy_probabilistic_mechanism_identity_types_mapping_init(
    int unit)
{

    uint32 mantissa_output = 0, exponent_output = 0;
    int table_entry_index = 0;
    uint mantissa_input = 0, exponent_input = 0;
    uint32 max_exponent, max_mantissa;
    uint32 mantissa_size;
    dbal_table_field_info_t mantissa_field_info, exponent_field_info;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dbal_tables_field_info_get
                    (unit, DBAL_TABLE_LATENCY_EGRESS_PROBABILITY_MAPPING, DBAL_FIELD_MANTISSA, TRUE, 0, 0,
                     &mantissa_field_info));

    SHR_IF_ERR_EXIT(dbal_tables_field_info_get
                    (unit, DBAL_TABLE_LATENCY_EGRESS_PROBABILITY_MAPPING, DBAL_FIELD_EXPONENT, TRUE, 0, 0,
                     &exponent_field_info));

    max_mantissa = mantissa_field_info.max_value;
    mantissa_size = mantissa_field_info.field_nof_bits;

    max_exponent = exponent_field_info.max_value;

    /** go over all hw EXPONENT - input exponent */
    for (exponent_input = 0; exponent_input <= max_exponent; exponent_input++)
    {
        for (mantissa_input = 0; mantissa_input <= max_mantissa; mantissa_input++)
        {
            exponent_output = table_entry_index / 8;
            exponent_output = (exponent_output < mantissa_size) ? 0 : exponent_output - mantissa_size;
            mantissa_output = table_entry_index % 8;
            SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_ecn_probability_map_dbal_set
                            (unit, mantissa_input, exponent_input, mantissa_output, exponent_output));

            table_entry_index++;
        }
    }

exit:
    SHR_FUNC_EXIT;

}

/**
* \brief
*  init probabilistic legacy mechanism for end-to-end-aqm latency profile
* \param [in] unit - unit id
* \return
*    shr_error_e
* \remark
*
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_aqm_legacy_probabilistic_mechanism_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Turn off HW lines 1,2,3 and 6 in the flowing formula:
     * LQ_MAX_CNI & (LQ_CNI_MAX_Enable & Packet_is_LQ & LQ_In_Profile) |
     * LQ_PROB_CNI & (LQ_CNI_PROB_Enable & Packet_is_LQ & LQ_In_Profile) |
     * CQ_PROB_AVG_CNI & (CQ_CNI_PROB_Enable & Packet_is_CQ) |
     * CQ_PROB_AVG_CNI & (CQ_CNI_PROB_Enable & (Packet_is_LQ & (~LQ_In_Profile))) |
     * TYP_MAX_CNI & (TYP_CNI_MAX_Enable & Packet_is_TYP) |
     * TYP_PROB_AVG_CNI & (TYP_CNI_PROB_Enable & Packet_is_TYP)
     */
    SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_legacy_probabilistic_mechanism_ecn_marking_formula_init(unit));

    /*
     * Set HW to use all the pacet's types
     */
    SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_legacy_probabilistic_mechanism_maintain_average_init(unit));

    /*
     * Set default mantissa and exponent for identity probability for all the packet's types
     */
    SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_legacy_probabilistic_mechanism_identity_types_mapping_init(unit));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
* verification function for latency profile create API
*/
static shr_error_e
dnx_cosq_latency_profile_create_verify(
    int unit,
    uint32 flags,
    int *gport_profile)
{
    int profile_id = 0, nof_profiles = 0;
    uint32 legal_flags =
        BCM_COSQ_LATENCY_PROFILE_WITH_ID | BCM_COSQ_LATENCY_PROFILE_ID_EXTENSION | BCM_COSQ_LATENCY_END_TO_END;
    SHR_FUNC_INIT_VARS(unit);
    legal_flags = dnx_data_latency.features.feature_get(unit, dnx_data_latency_features_valid_flow_profile_flag) ?
        (legal_flags | BCM_COSQ_LATENCY_PROFILE_BY_FLOW) : legal_flags;
    legal_flags = dnx_data_latency.features.feature_get(unit, dnx_data_latency_features_valid_end_to_end_aqm_profile) ?
        (legal_flags | BCM_COSQ_LATENCY_END_TO_END_AQM) : legal_flags;

    SHR_NULL_CHECK(gport_profile, _SHR_E_PARAM, "gport_profile");
    SHR_MASK_VERIFY(flags, legal_flags, _SHR_E_PARAM, "some of the flags are not supported.\n");

    if (_SHR_IS_FLAG_SET(flags, BCM_COSQ_LATENCY_PROFILE_WITH_ID))
    {
        /*
         * Gport type validation
         */

        if (_SHR_IS_FLAG_SET(flags, BCM_COSQ_LATENCY_END_TO_END) &&
            (BCM_GPORT_IS_INGRESS_LATENCY_PROFILE(*gport_profile)
             || BCM_GPORT_IS_END_TO_END_AQM_LATENCY_PROFILE(*gport_profile)))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "flag BCM_COSQ_LATENCY_END_TO_END, but gport (=%d) is decoded as ingress/aqm latency",
                         *gport_profile);
        }
        if (_SHR_IS_FLAG_SET(flags, BCM_COSQ_LATENCY_END_TO_END_AQM) &&
            (BCM_GPORT_IS_INGRESS_LATENCY_PROFILE(*gport_profile)
             || BCM_GPORT_IS_END_TO_END_LATENCY_PROFILE(*gport_profile)))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "flag BCM_COSQ_LATENCY_END_TO_END_AQM, but gport (=%d) is decoded as ingress/e2e latency",
                         *gport_profile);
        }

        /*
         * Profile id validation
         */

        SHR_IF_ERR_EXIT(bcm_dnx_cosq_latency_profile_id_get(unit, *gport_profile, &profile_id));

        /** Verify profile id range */
        SHR_IF_ERR_EXIT(bcm_dnx_cosq_latency_profile_nof_profiles_get(unit, *gport_profile, &nof_profiles));
        SHR_MAX_VERIFY(profile_id, nof_profiles - 1, _SHR_E_PARAM,
                       "Latency-profile %d is out of range 0-%d\n", profile_id, nof_profiles - 1);

        /** Verify profile didn't allocated */
        SHR_IF_ERR_EXIT(bcm_dnx_cosq_latency_profile_is_allocated_verify(unit, *gport_profile, FALSE    /* expect non
                                                                                                         * allocated
                                                                                                         * profile */ ));

    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  set valid the latency profile to flow id
* \param [in] unit -unit id
* \param [in] profile_gport - profile gport
* \param [in] profile_id - gport of the latency profile
* \param [in] valid - set if latency per flow id is valid or not
* \return
*    shr_error_e
* \remark
*   None
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_flow_profile_valid_set(
    int unit,
    int profile_gport,
    int profile_id,
    int valid)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if ((BCM_GPORT_IS_INGRESS_LATENCY_PROFILE(profile_gport) == TRUE)
        && (profile_id < dnx_data_latency.ingress.nof_flow_profile_get(unit)))
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_INGRESS_PROFILE_MAP_TO_FLOW, &entry_handle_id));
    }
    else if (BCM_GPORT_IS_END_TO_END_LATENCY_PROFILE(profile_gport) == TRUE)
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_PROFILE, &entry_handle_id));
    }
    else if (BCM_GPORT_IS_END_TO_END_AQM_LATENCY_PROFILE(profile_gport) == TRUE)
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_DROP_CNI_PROFILE, &entry_handle_id));
    }
    else
    {
        SHR_EXIT();
    }
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_FLOW_PROFILE_VALID, INST_SINGLE, valid);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  configura ecn profile hard coded values used for packet
*  classification - pkt is DE/ LQ / CQ / TYP
*
*  note that change in LATENCY_EGRESS_PACKET_CLASSIFICATION
*   affects table EGRESS_MAINTAIN_AVERAGE_LATENCY as the keys
*   are connected
* \param [in] unit -unit id
* \param [in] clear_hw - on latency deinit need to clear the HW
* \return
*    shr_error_e
* \remark
*   None
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_aqm_packet_configuration(
    int unit,
    int clear_hw)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_PACKET_CLASSIFICATION, &entry_handle_id));
    /** all packets are drop eligible */
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_ECN_PROFILE, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_DE, INST_SINGLE, clear_hw ? 0 : 1);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    /** by default packets are configured in typical mode */
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_ECN_PROFILE, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_TYP, INST_SINGLE, clear_hw ? 0 : 1);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    /** LQ and CQ configuration */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ECN_PROFILE, 0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_CQ, INST_SINGLE, clear_hw ? 0 : 1);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_LQ, INST_SINGLE, 0);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ECN_PROFILE, 1);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_CQ, INST_SINGLE, 0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_LQ, INST_SINGLE, clear_hw ? 0 : 1);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ECN_PROFILE, 2);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_CQ, INST_SINGLE, clear_hw ? 0 : 1);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_LQ, INST_SINGLE, 0);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ECN_PROFILE, 3);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_CQ, INST_SINGLE, 0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_LQ, INST_SINGLE, clear_hw ? 0 : 1);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

     /** configure all packets to be typical */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_LATENCY_EGRESS_DROP_CNI_PROFILE, entry_handle_id));
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_L4_AQM_TYP_ENABLE, INST_SINGLE, clear_hw ? 0 : 1);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  configure the maintainance of the average latency - whether
*  to use new average / new instantaneous latency
*
*   note that change in LATENCY_EGRESS_PACKET_CLASSIFICATION
*   affects table EGRESS_MAINTAIN_AVERAGE_LATENCY as the keys
*   are connected
* \param [in] unit -unit id
* \param [in] clear_hw - clear hw on latency deinit
* \return
*    shr_error_e
* \remark
*   None
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_aqm_cfg_maintain_average_latency(
    int unit,
    int clear_hw)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_MAINTAIN_AVERAGE_LATENCY, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PKT_TYPE_KEY,
                               DNX_COSQ_LATENCY_END_TO_END_AQM_PKT_IS_CLASSIC_LQ);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_USE_NEW_AVG, INST_SINGLE, clear_hw ? FALSE : TRUE);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_USE_NEW_INST, INST_SINGLE, clear_hw ? FALSE : TRUE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PKT_TYPE_KEY,
                               DNX_COSQ_LATENCY_END_TO_END_AQM_PKT_IS_COUPLED_CLASSIC);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_USE_NEW_AVG, INST_SINGLE, clear_hw ? FALSE : TRUE);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_USE_NEW_INST, INST_SINGLE, clear_hw ? FALSE : TRUE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PKT_TYPE_KEY,
                               DNX_COSQ_LATENCY_END_TO_END_AQM_PKT_IS_COUPLED_LQ);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_USE_NEW_AVG, INST_SINGLE, FALSE);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_USE_NEW_INST, INST_SINGLE, FALSE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    /** other key values are invalid */

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  egress latency drop probability - CQ probability
*  accoding to given mantissa/exponent - calculate the mantissa
*  and exponent that need to be set to update the CQ probability
* \param [in] unit -unit id
* \param [in] type - property type of the profile
* \param [in] arg  - the value of the property
* \return
*    shr_error_e
* \remark
*
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_aqm_ecn_probability_map_calculation(
    int unit,
    bcm_cosq_control_t type,
    int arg)
{
    uint32 mantissa_output = 0, exponent_output = 0, mantissa_input = 0, exponent_input = 0;
    uint32 max_mantissa = 0, max_exponent = 0, max_exponent_output = 0, coefficient_a = 0, exponent_b =
        0, mantissa_size = 0;
    int numerator_b = 0, denumerator_exp = 0;
    uint32 nomilize32_CQ;
    uint64 fnew_nomilize32_CQ64;
    uint32 fnew_nomilize32_CQ;
    uint32 temp_shift;
    dbal_table_field_info_t field_info;
    SHR_FUNC_INIT_VARS(unit);

    /** get givent exponent/ coefficient */
    if (type == bcmCosqControlLatencyEcnProbConvertExponent)
    {
        exponent_b = arg;
        SHR_IF_ERR_EXIT(dnx_cosq_latency_db.probability_convert.exponent_b.set(unit, exponent_b));
        SHR_IF_ERR_EXIT(dnx_cosq_latency_db.probability_convert.coefficient_a.get(unit, &coefficient_a));
    }
    else if (type == bcmCosqControlLatencyEcnProbConvertCoeff)
    {
        coefficient_a = arg;
        SHR_IF_ERR_EXIT(dnx_cosq_latency_db.probability_convert.coefficient_a.set(unit, coefficient_a));
        SHR_IF_ERR_EXIT(dnx_cosq_latency_db.probability_convert.exponent_b.get(unit, &exponent_b));
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for end to end AQM latency profile \n", type);
    }

    SHR_IF_ERR_EXIT(dbal_tables_field_info_get
                    (unit, DBAL_TABLE_LATENCY_EGRESS_PROBABILITY_MAPPING, DBAL_FIELD_MANTISSA, TRUE, 0, 0,
                     &field_info));
    max_mantissa = field_info.max_value;
    mantissa_size = field_info.field_nof_bits;
    SHR_IF_ERR_EXIT(dbal_tables_field_info_get
                    (unit, DBAL_TABLE_LATENCY_EGRESS_PROBABILITY_MAPPING, DBAL_FIELD_EXPONENT, TRUE, 0, 0,
                     &field_info));
    max_exponent = field_info.max_value;

    /** go over all possible mapping values */
    /** go over all hw MANTISSA - input mantissa */
    for (mantissa_input = 0; mantissa_input <= max_mantissa; mantissa_input++)
    {
        /** go over all hw EXPONENT - input exponent */
        for (exponent_input = 0; exponent_input <= max_exponent; exponent_input++)
        {
            temp_shift = (exponent_input > mantissa_size) ? (exponent_input - mantissa_size) : 0;
            nomilize32_CQ = ((uint32) 1 << exponent_input) | (mantissa_input << temp_shift);

            COMPILER_64_SET(fnew_nomilize32_CQ64, 0, coefficient_a);
            numerator_b = exponent_b;
            denumerator_exp = (exponent_b - 1) * 32;
            if (exponent_b > 0)
            {
                while (denumerator_exp >= 0)
                {
                    while ((COMPILER_64_HI(fnew_nomilize32_CQ64) == 0) && (numerator_b > 0))
                    {
                        COMPILER_64_UMUL_32(fnew_nomilize32_CQ64, nomilize32_CQ);
                        numerator_b--;
                    }
                    if (denumerator_exp > 0)
                    {
                        COMPILER_64_UDIV_32(fnew_nomilize32_CQ64, 2);
                    }
                    denumerator_exp--;
                }
            }
            if (COMPILER_64_HI(fnew_nomilize32_CQ64) == 0)
            {
                fnew_nomilize32_CQ = COMPILER_64_LO(fnew_nomilize32_CQ64);
            }
            else
            {
                fnew_nomilize32_CQ = 0xFFFFFFFF;
            }
             /** in order to to cross x*2^y bigger than 32 bits, we limit the exp value if necessery */
            max_exponent_output = (max_exponent + mantissa_size) < 32 ? max_exponent : (max_exponent - mantissa_size);
            SHR_IF_ERR_EXIT(utilex_break_complex_to_mnt_exp_round_down
                            (fnew_nomilize32_CQ, max_mantissa, max_exponent_output, 1,
                             utilex_power_of_2(mantissa_size), &mantissa_output, &exponent_output));

            SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_ecn_probability_map_dbal_set
                            (unit, mantissa_input, exponent_input, mantissa_output, exponent_output));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  egress latency drop probability - CQ probability
*  configure default input mantissa and exponent mapping to
*  output mantissa and exponent
* \param [in] unit -unit id
* \return
*    shr_error_e
* \remark
*
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_aqm_cq_probability_default(
    int unit)
{
    uint32 exponent_b = 0;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_cosq_latency_db.probability_convert.exponent_b.get(unit, &exponent_b));
    SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_ecn_probability_map_calculation
                    (unit, bcmCosqControlLatencyEcnProbConvertExponent, exponent_b));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  create a ingress latency profile or end to end latency profile.
* \param [in] unit -unit id
* \param [in] flags - BCM_COSQ_LATENCY_PROFILE_WITH_ID, BCM_COSQ_LATENCY_PROFILE_ID_EXTENSION
* \param [out] profile_gport - gport of the latency profile
* \return
*    shr_error_e
* \remark
*   None
* \see
*   NONE
*/
int
bcm_dnx_cosq_latency_profile_create(
    int unit,
    int flags,
    bcm_gport_t * profile_gport)
{
    uint32 res_flags = 0;
    int profile_id = 0;
    resource_tag_bitmap_utils_extra_arg_alloc_info_t alloc_info;
    int rv;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    /** Verify parameters */
    SHR_INVOKE_VERIFY_DNXC(dnx_cosq_latency_profile_create_verify(unit, flags, profile_gport));

    if (!_SHR_IS_FLAG_SET(flags, BCM_COSQ_LATENCY_END_TO_END)
        && !_SHR_IS_FLAG_SET(flags, BCM_COSQ_LATENCY_END_TO_END_AQM))
    {
        sal_memset(&alloc_info, 0x0, sizeof(resource_tag_bitmap_utils_extra_arg_alloc_info_t));
        if (_SHR_IS_FLAG_SET(flags, BCM_COSQ_LATENCY_PROFILE_WITH_ID))
        {
            profile_id = BCM_GPORT_INGRESS_LATENCY_PROFILE_GET(*profile_gport);
            res_flags |= DNX_ALGO_RES_ALLOCATE_WITH_ID;
            res_flags |= RESOURCE_TAG_BITMAP_ALLOC_IGNORE_TAG;
        }
        else
        {
            res_flags |= RESOURCE_TAG_BITMAP_ALWAYS_CHECK_TAG;
        }

        alloc_info.tags[0] = 0;

        /** First, try to allocate from extension range. if it is full, try to allocate from non-extension range */
        if (_SHR_IS_FLAG_SET(flags, BCM_COSQ_LATENCY_PROFILE_ID_EXTENSION)
            && !_SHR_IS_FLAG_SET(flags, BCM_COSQ_LATENCY_PROFILE_WITH_ID))
        {

            alloc_info.tags[0] = 1;
            rv = dnx_cosq_latency_db.ingress_latency_res.allocate_single(unit,
                                                                         res_flags | DNX_ALGO_RES_ALLOCATE_SIMULATION,
                                                                         (void *) &alloc_info, &profile_id);

            alloc_info.tags[0] = (rv != _SHR_E_RESOURCE) ? 1 : 0;
        }

        SHR_IF_ERR_EXIT(dnx_cosq_latency_db.ingress_latency_res.allocate_single
                        (unit, res_flags, (void *) &alloc_info, &profile_id));
        BCM_GPORT_INGRESS_LATENCY_PROFILE_SET((*profile_gport), profile_id);

    }
    else if (_SHR_IS_FLAG_SET(flags, BCM_COSQ_LATENCY_END_TO_END))
    {
        if (_SHR_IS_FLAG_SET(flags, BCM_COSQ_LATENCY_PROFILE_WITH_ID))
        {
            profile_id = BCM_GPORT_END_TO_END_LATENCY_PROFILE_GET(*profile_gport);
            res_flags |= DNX_ALGO_RES_ALLOCATE_WITH_ID;
        }
        SHR_IF_ERR_EXIT(dnx_cosq_latency_db.end_to_end_latency_res.allocate_single(unit, res_flags, NULL, &profile_id));
        BCM_GPORT_END_TO_END_LATENCY_PROFILE_SET((*profile_gport), profile_id);
    }
    else if (_SHR_IS_FLAG_SET(flags, BCM_COSQ_LATENCY_END_TO_END_AQM))
    {
        if (_SHR_IS_FLAG_SET(flags, BCM_COSQ_LATENCY_PROFILE_WITH_ID))
        {
            profile_id = BCM_GPORT_LATENCY_END_TO_END_AQM_LATENCY_PROFILE_GET(*profile_gport);
            res_flags |= DNX_ALGO_RES_ALLOCATE_WITH_ID;
        }
        SHR_IF_ERR_EXIT(dnx_cosq_aqm_db.aqm_profile_res.allocate_single(unit, res_flags, NULL, &profile_id));
        BCM_GPORT_LATENCY_END_TO_END_AQM_LATENCY_PROFILE_SET((*profile_gport), profile_id);
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid flags given %d", flags);
    }
    /** If latency profile by flow - set the valid bit */
    if (_SHR_IS_FLAG_SET(flags, BCM_COSQ_LATENCY_PROFILE_BY_FLOW))
    {
        SHR_IF_ERR_EXIT(dnx_cosq_latency_flow_profile_valid_set(unit, *profile_gport, profile_id, 1));
    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

static shr_error_e
bcm_dnx_cosq_latency_profile_destroy_verify(
    int unit,
    int flags,
    bcm_gport_t profile_gport)
{
    int profile_id = 0;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(bcm_dnx_cosq_latency_profile_id_get(unit, profile_gport, &profile_id));

    if (profile_id == DNX_COSQ_LATENCY_DEFAULT_PROFILE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Cannot destroy the default profile, profile_id=%d", profile_id);
    }

    SHR_IF_ERR_EXIT(bcm_dnx_cosq_latency_profile_is_allocated_verify(unit, profile_gport, TRUE  /* expect allocated
                                                                                                 * profile */ ));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  destroy a ingress latency profile or end to end latency profile.
* \param [in] unit -unit id
* \param [in] flags - NONE
* \param [in] profile_gport - gport of the latency profile
* \return
*    shr_error_e
* \remark
*   None
* \see
*   NONE
*/
int
bcm_dnx_cosq_latency_profile_destroy(
    int unit,
    int flags,
    bcm_gport_t profile_gport)
{
    int profile_id;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    SHR_IF_ERR_EXIT(bcm_dnx_cosq_latency_profile_destroy_verify(unit, flags, profile_gport));

    /** free from resource manager the profile */
    if (BCM_GPORT_IS_INGRESS_LATENCY_PROFILE(profile_gport))
    {
        profile_id = BCM_GPORT_INGRESS_LATENCY_PROFILE_GET(profile_gport);
        SHR_IF_ERR_EXIT(dnx_cosq_latency_db.ingress_latency_res.free_single(unit, profile_id, NULL));
    }
    else if (BCM_GPORT_IS_END_TO_END_LATENCY_PROFILE(profile_gport))
    {
        profile_id = BCM_GPORT_END_TO_END_LATENCY_PROFILE_GET(profile_gport);
        SHR_IF_ERR_EXIT(dnx_cosq_latency_db.end_to_end_latency_res.free_single(unit, profile_id, NULL));
    }
    else if (BCM_GPORT_IS_END_TO_END_AQM_LATENCY_PROFILE(profile_gport))
    {
        profile_id = BCM_GPORT_LATENCY_END_TO_END_AQM_LATENCY_PROFILE_GET(profile_gport);
        SHR_IF_ERR_EXIT(dnx_cosq_aqm_db.aqm_profile_res.free_single(unit, profile_id, NULL));
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid gport_profile %d", profile_gport);
    }

    /** Remove the valid bit for the latency profile per flow id if valid */
    if (dnx_data_latency.features.feature_get(unit, dnx_data_latency_features_valid_flow_profile_flag))
    {
        SHR_IF_ERR_EXIT(dnx_cosq_latency_flow_profile_valid_set(unit, profile_gport, profile_id, 0));
    }
exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *  init resource manager for latency measurements
 *
 * \par DIRECT_INPUT:
 *   \param [in] unit - Unit ID
 *
 * \par INDIRECT INPUT:
 *   * None
 * \par DIRECT OUTPUT:
 *   shr_error_e
 * \par INDIRECT OUTPUT
 *   * None
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_cosq_latency_res_init(
    int unit)
{
    dnx_algo_res_create_data_t data;
    resource_tag_bitmap_utils_extra_arg_create_info_t extra_info;
    resource_tag_bitmap_utils_tag_info_t tag_info;
    bcm_gport_t gport;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&extra_info, 0x0, sizeof(resource_tag_bitmap_utils_extra_arg_create_info_t));
    sal_memset(&tag_info, 0x0, sizeof(resource_tag_bitmap_utils_tag_info_t));

    /** create ingress latency res mngr */
    sal_memset(&data, 0, sizeof(dnx_algo_res_create_data_t));
    data.first_element = 0;
    data.nof_elements = dnx_data_latency.profile.ingress_nof_get(unit);
    data.flags = RESOURCE_TAG_BITMAP_CREATE_ALLOW_IGNORING_TAG;
    sal_strncpy(data.name, DNX_COSQ_LATENCY_INGRESS_RESOURCE, DNX_ALGO_RES_MNGR_MAX_NAME_LENGTH - 1);
    /** create tag for half of the entries. */
    /** pmf-flow-profile can be mapped just to the first half. queues can be mapped to all range. */
    extra_info.grains_size[0] = data.nof_elements / 2;
    extra_info.max_tags_value[0] = 1;
    SHR_IF_ERR_EXIT(dnx_cosq_latency_db.ingress_latency_res.create(unit, &data, (void *) &extra_info));
    tag_info.element = 0;
    tag_info.nof_elements = extra_info.grains_size[0];
    tag_info.tags[0] = 0;
    tag_info.force_tag = FALSE;
    SHR_IF_ERR_EXIT(dnx_cosq_latency_db.ingress_latency_res.advanced_algorithm_info_set(unit, (void *) &tag_info));
    tag_info.element = extra_info.grains_size[0];
    tag_info.nof_elements = extra_info.grains_size[0];
    tag_info.tags[0] = 1;
    tag_info.force_tag = FALSE;
    SHR_IF_ERR_EXIT(dnx_cosq_latency_db.ingress_latency_res.advanced_algorithm_info_set(unit, (void *) &tag_info));

     /** capture the first profile as default profile that do not perform any latency action */
    BCM_GPORT_INGRESS_LATENCY_PROFILE_SET(gport, DNX_COSQ_LATENCY_DEFAULT_PROFILE);
    SHR_IF_ERR_EXIT(bcm_dnx_cosq_latency_profile_create(unit, BCM_COSQ_LATENCY_PROFILE_WITH_ID, &gport));

    /** create end to end latency res mngr */
    sal_memset(&data, 0, sizeof(dnx_algo_res_create_data_t));
    data.first_element = 0;
    data.nof_elements = dnx_data_latency.profile.egress_nof_get(unit);
    data.flags = 0;
    sal_strncpy(data.name, DNX_COSQ_LATENCY_END_TO_END_RESOURCE, DNX_ALGO_RES_MNGR_MAX_NAME_LENGTH - 1);
    SHR_IF_ERR_EXIT(dnx_cosq_latency_db.end_to_end_latency_res.create(unit, &data, NULL));
    /** capture the first profile as default profile that do not perform any latency action */
    BCM_GPORT_END_TO_END_LATENCY_PROFILE_SET(gport, DNX_COSQ_LATENCY_DEFAULT_PROFILE);
    SHR_IF_ERR_EXIT(bcm_dnx_cosq_latency_profile_create
                    (unit, (BCM_COSQ_LATENCY_PROFILE_WITH_ID | BCM_COSQ_LATENCY_END_TO_END), &gport));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_cosq_latency_queue_tm_init(
    int unit)
{
    dnx_algo_template_create_data_t data;
    int nof_profiles;
    dbal_table_field_info_t field_info;
    dnx_cosq_latency_queue_template_t default_data = { 0 };
    SHR_FUNC_INIT_VARS(unit);

    /** get data on the profiles size etc.. from HW dbal tables */
    /** note - ingress and egress has the same hw configuration in HW. we take the data from ingress, but it belong also to egress */
    SHR_IF_ERR_EXIT(dbal_tables_field_info_get(unit, DBAL_TABLE_LATENCY_VOQ_QUARTET_PROFILE, DBAL_FIELD_PROFILE_ID,
                                               FALSE, 0, 0, &field_info));
    nof_profiles = field_info.max_value + 1;

    /** Add all entities to template init id with given data */
    sal_memset(&data, 0, sizeof(dnx_algo_template_create_data_t));
    data.flags = DNX_ALGO_TEMPLATE_CREATE_USE_DEFAULT_PROFILE | DNX_ALGO_TEMPLATE_CREATE_ALLOW_DEFAULT_PROFILE_OVERRIDE;
    data.first_profile = 0;
    data.nof_profiles = nof_profiles;
    data.max_references = dnx_data_ipq.queues.nof_queues_get(unit) / DNX_COSQ_LATENCY_QUEUE_QUARTET_RESOLUTION; /** quartet queues profile */
    data.default_profile = 0;
    data.data_size = sizeof(dnx_cosq_latency_queue_template_t);
    data.default_data = (void *) &default_data;

    /** create template manager */
    sal_strncpy(data.name, DNX_COSQ_LATENCY_QUARTET_QUEUES_TEMPLATE_NAME, DNX_ALGO_TEMPLATE_MNGR_MAX_NAME_LENGTH - 1);
    SHR_IF_ERR_EXIT(dnx_cosq_latency_db.queue_template.create(unit, &data, NULL));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  function set eco for affected devices so cgm will ignore
*  flow-profile and use only voq-profile for latency rejects
* \param [in] unit -unit id
* \return
*    shr_error_e.
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_based_admission_extended_profiles_enable(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_BASED_ADMISSION_EXTENDED_PROFILES, &entry_handle_id));
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECO_ENABLE, INST_SINGLE,
                                 dnx_data_latency.based_admission.cgm_extended_profiles_enable_value_get(unit));
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  voq latency based admission
* \return
*    shr_error_e.
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_based_admission_reject_flow_profile(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_VOQ_RJCT_SETTINGS, &entry_handle_id));
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RJCT_FLOW_PROFILE_NULL, INST_SINGLE,
                                 dnx_data_latency.based_admission.reject_flow_profile_value_get(unit));
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*
* \return
*    shr_error_e.
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_ingress_timestamp_resolution_config_jr_mode(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_INGRESS_TIMESTAMP_RESOLUTION_CONFIG, &entry_handle_id));
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_MODE_LEFT_SHIFT, INST_SINGLE,
                                 dnx_data_latency.ingress.jr_mode_latency_timestamp_left_shift_get(unit));
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** See .h file */
shr_error_e
dnx_cosq_latency_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_cosq_latency_db.init(unit));

    /** init resource manager latency */
    SHR_IF_ERR_EXIT(dnx_cosq_latency_res_init(unit));
    /** init template manager queues latency */
    SHR_IF_ERR_EXIT(dnx_cosq_latency_queue_tm_init(unit));

    if (dnx_data_latency.features.feature_get(unit, dnx_data_latency_features_valid_end_to_end_aqm_profile))
    {

        if (dnx_data_latency.
            features.feature_get(unit, dnx_data_latency_features_probabilistic_legacy_mechanism_support))
        {
            SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_legacy_probabilistic_mechanism_init(unit));
        }
        else
        {
            /** configurations for packet classification */
            SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_packet_configuration(unit, 0));
            /** set default mantissa and exponent for probability average cni */
            SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_cq_probability_default(unit));
            /** configurations for average latency maintenance */
            SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_cfg_maintain_average_latency(unit, 0));
        }

    }

    if (dnx_data_latency.features.feature_get(unit, dnx_data_latency_features_ingress_based_admission))
    {
        if (dnx_data_latency.
            based_admission.feature_get(unit, dnx_data_latency_based_admission_cgm_extended_profiles_enable))
        {
            SHR_IF_ERR_EXIT(dnx_cosq_latency_based_admission_extended_profiles_enable(unit));
        }
        else
        {
            /** set value to voq reject flow profile according to the
             *  device */
            SHR_IF_ERR_EXIT(dnx_cosq_latency_based_admission_reject_flow_profile(unit));
        }
    }

    if (dnx_data_headers.system_headers.system_headers_mode_get(unit) !=
        DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO2_MODE)
    {
        SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_timestamp_resolution_config_jr_mode(unit));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*     get a report that contain the packets with the max ingress latency.
* \param [in] unit -unit id
* \param [in] gport - indicates on the core id.
* \param [in] max_count - max entries to fill - indicates the size of array "max_latency_pkts"
* \param [out] max_latency_pkts - array of information of the max latency packets.
* \param [out] actual_count - actual size filled by the driver into max_latency_pkts.
*
* \return
*    shr_error_e
* \remark
*   None
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_ingress_max_get(
    int unit,
    bcm_gport_t gport,
    int max_count,
    bcm_cosq_max_latency_pkts_t * max_latency_pkts,
    int *actual_count)
{
    int index;
    uint32 entry_handle_id;
    dbal_table_field_info_t field_info;
    uint32 tc;
    uint32 ftmh_pp_dsp;
    uint32 modid;
    uint32 lat_val;
    uint32 flow_id;
    uint32 quartet_id;
    uint32 quartet_id_max;
    uint32 voq_quartet_profile_id;
    uint32 latency_profile_maped;
    uint32 latency_profile_id;
    uint32 is_per_flow;
    uint32 base_qid;
    uint32 sys_port_id;
    uint32 sys_gport;
    uint32 pp_dsp;
    uint32 is_tracked;
    bcm_core_t core_id;
    dnx_algo_gpm_gport_phy_info_t gport_info;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dbal_tables_field_info_get(unit, DBAL_TABLE_LATENCY_INGRESS_MAX_REPORT, DBAL_FIELD_INDEX,
                                               TRUE, 0, 0, &field_info));
    *actual_count = 0;

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_INGRESS_MAX_REPORT, &entry_handle_id));

    /** go over all max latency table, read the content and fill the structure */
    for (index = 0; index <= field_info.max_value; index++)
    {
        /** Taking a handle */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_LATENCY_INGRESS_MAX_REPORT, entry_handle_id));
        /** Setting key fields */
        core_id = _SHR_COSQ_GPORT_CORE_GET(gport);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INDEX, index);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_VALUE, INST_SINGLE, &lat_val);
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_FLOW_ID, INST_SINGLE, &flow_id);
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_TRF_CLS, INST_SINGLE, &tc);
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_PORT_ID, INST_SINGLE, &ftmh_pp_dsp);
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_MODID, INST_SINGLE, &modid);
        SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

        /** Fill the array only if latency > 0. otherwise, it is consider as empty entry */
        if (((*actual_count) < max_count) && (lat_val != 0))
        {
            /**
             * If the flow IF is VOQ, we need to get the PP DSP from it. This can only be determined if we don't have a valid bit for per PP flow
             * Assume the flow_id is a VOQ and check the profile that is mapped to it. If tracking is enabled for it, then it is per VOQ and we can
             * determine the destination port by it.
             */
            is_per_flow = TRUE;
            quartet_id = flow_id / DNX_COSQ_LATENCY_QUEUE_QUARTET_RESOLUTION;

            /** Chech if the Quartet ID will fit in the DBAL field and get the VOQ quartet profile ID */
            SHR_IF_ERR_EXIT(dbal_tables_field_max_value_get
                            (unit, DBAL_TABLE_LATENCY_VOQ_QUARTET_PROFILE, DBAL_FIELD_QUARTET_QUEUE, TRUE, 0, 0,
                             (int *) &quartet_id_max));
            if (quartet_id <= quartet_id_max)
            {
                SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_LATENCY_VOQ_QUARTET_PROFILE, entry_handle_id));
                dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_QUARTET_QUEUE, quartet_id);
                dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
                dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, INST_SINGLE,
                                           &voq_quartet_profile_id);
                SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

                /** Get the mapping of VOQ quartet profile ID to Latency Flow Profile */
                SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_LATENCY_VOQ_QUARTET_PROFILE_MAP, entry_handle_id));
                dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_QUARTET_PROFILE, voq_quartet_profile_id);
                dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_FLOW_PROFILE, INST_SINGLE,
                                           &latency_profile_maped);
                SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
                latency_profile_id = latency_profile_maped * DNX_COSQ_LATENCY_QUEUE_QUARTET_RESOLUTION;

                /** Check if tracking is enabled for the Latency Flow Profile */
                SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_LATENCY_INGRESS_PROFILE, entry_handle_id));
                dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, latency_profile_id);
                dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_TRACK_ENABLE, INST_SINGLE,
                                           &is_tracked);
                SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

                /**
                 * If the profile that way found assuming the Flow ID is a VOW is tracked,
                 * then the latency measurement is per VOQ
                 */
                is_per_flow = is_tracked ? FALSE : TRUE;
            }

            /**
             * Fill in the structure
             */
            COMPILER_64_SET(max_latency_pkts[(*actual_count)].latency, 0, lat_val);
            max_latency_pkts[(*actual_count)].latency_flow = flow_id;
            max_latency_pkts[(*actual_count)].cosq = (int) tc;
            if (is_per_flow == TRUE)
            {
                /**
                 * When the latency measurement is per PP Flow ID, the ports returned from HW
                 * should be ignored, because it is not guaranteed that they will be correct.
                 */
                max_latency_pkts[(*actual_count)].dest_gport = 0;
            }
            else
            {
                base_qid =
                    (flow_id / DNX_COSQ_LATENCY_QUEUE_QUARTET_RESOLUTION) * DNX_COSQ_LATENCY_QUEUE_QUARTET_RESOLUTION;
                SHR_IF_ERR_EXIT(dnx_ipq_queue_sysport_map_get(unit, core_id, base_qid, &sys_port_id));
                BCM_GPORT_SYSTEM_PORT_ID_SET(sys_gport, sys_port_id);
                SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get
                                (unit, sys_gport, DNX_ALGO_GPM_GPORT_TO_PHY_OP_NONE, &gport_info));
                SHR_IF_ERR_EXIT(dnx_algo_port_pp_dsp_get(unit, gport_info.local_port, &core_id, &pp_dsp));
                /** Translate Core + PP DSP to ModID + FTMH PP DSP */
                SHR_IF_ERR_EXIT(dnx_stk_sys_pp_dsp_to_modport_gport_convert(unit, core_id, pp_dsp,
                                                                            &max_latency_pkts
                                                                            [*actual_count].dest_gport));
            }
            (*actual_count)++;
        }
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*     get a report that contain the packets with the max end to end latency. the report is taken from Egress pipe.
* \param [in] unit -unit id
* \param [in] gport - indicates on the core id.
* \param [in] max_count - max entries to fill - indicates the size of array "max_latency_pkts"
* \param [out] max_latency_pkts - array of information of the max latency packets.
* \param [out] actual_count - actual size filled by the driver into max_latency_pkts.
*
* \return
*    shr_error_e
* \remark
*   None
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_egress_max_get(
    int unit,
    bcm_gport_t gport,
    int max_count,
    bcm_cosq_max_latency_pkts_t * max_latency_pkts,
    int *actual_count)
{
    uint32 index;
    uint32 entry_handle_id;
    dbal_table_field_info_t field_info;
    uint32 lat_val;
    uint32 tc;
    uint32 out_tm_port, pp_dsp;
    bcm_port_t logical_port;
    uint32 mc;
    uint32 flow_id;
    bcm_core_t core_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dbal_tables_field_info_get(unit, DBAL_TABLE_LATENCY_EGRESS_MAX_REPORT, DBAL_FIELD_INDEX,
                                               TRUE, 0, 0, &field_info));
    *actual_count = 0;

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_MAX_REPORT, &entry_handle_id));

    /** go over all max latency table, read the content and fill the structure */
    for (index = 0; index <= field_info.max_value; index++)
    {
        /**
         * Make sure we are reading the entries on the requested core
         */
        core_id = _SHR_COSQ_GPORT_CORE_GET(gport);

        /** Setting key fields */
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INDEX, index);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_VALUE, INST_SINGLE, &lat_val);
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_FLOW_ID, INST_SINGLE, &flow_id);
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_TC, INST_SINGLE, &tc);
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_OUT_TM_PORT_ID, INST_SINGLE, &out_tm_port);
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_MC, INST_SINGLE, &mc);
        SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

        /** Fill the array only if latency > 0. otherwise, it is consider as empty entry */
        if (((*actual_count) < max_count) && (lat_val != 0))
        {
            COMPILER_64_SET(max_latency_pkts[(*actual_count)].latency, 0, lat_val);
            max_latency_pkts[(*actual_count)].latency_flow = flow_id;
            max_latency_pkts[(*actual_count)].cosq = (int) tc;
            max_latency_pkts[(*actual_count)].is_mc = (int) mc;
            SHR_IF_ERR_EXIT(dnx_algo_port_out_tm_to_logical_get(unit, core_id, out_tm_port, &logical_port));
            SHR_IF_ERR_EXIT(dnx_algo_port_pp_dsp_get(unit, logical_port, &core_id, &pp_dsp));
            /** Translate Core + PP DSP to ModID + FTMH ppPP DSP */
            SHR_IF_ERR_EXIT(dnx_stk_sys_pp_dsp_to_modport_gport_convert(unit, core_id, pp_dsp,
                                                                        &max_latency_pkts[*actual_count].dest_gport));
            (*actual_count)++;
        }
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
* verification function for max latecy get API
*/
static shr_error_e
dnx_cosq_latency_max_pkts_get_verify(
    int unit,
    bcm_gport_t gport,
    uint32 flags,
    int max_count,
    bcm_cosq_max_latency_pkts_t * max_latency_pkts,
    int *actual_count)
{
    uint32 legal_flags = BCM_COSQ_LATENCY_END_TO_END;
    int core_id;
    dbal_table_field_info_t field_info;

    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(actual_count, _SHR_E_PARAM, "actual_count");
    SHR_NULL_CHECK(max_latency_pkts, _SHR_E_PARAM, "max_latency_pkts");

    SHR_MASK_VERIFY(flags, legal_flags, _SHR_E_PARAM, "some of the flags are not supported.\n");

    if (_SHR_COSQ_GPORT_IS_CORE(gport))
    {
        core_id = _SHR_COSQ_GPORT_CORE_GET(gport);
        /** not support specific core */
        DNXCMN_CORE_VALIDATE(unit, core_id, FALSE);
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid gport %d", gport);
    }

    if (_SHR_IS_FLAG_SET(flags, BCM_COSQ_LATENCY_END_TO_END))
    {
        if (!dnx_data_latency.features.feature_get(unit, dnx_data_latency_features_egress_latency_track_support))
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Not supported on this device.");
        }
        else
        {
            SHR_IF_ERR_EXIT(dbal_tables_field_info_get(unit, DBAL_TABLE_LATENCY_EGRESS_MAX_REPORT, DBAL_FIELD_INDEX,
                                                       TRUE, 0, 0, &field_info));
        }
    }
    else
    {
        SHR_IF_ERR_EXIT(dbal_tables_field_info_get(unit, DBAL_TABLE_LATENCY_INGRESS_MAX_REPORT, DBAL_FIELD_INDEX,
                                                   TRUE, 0, 0, &field_info));
    }
    if (max_count > (field_info.max_value + 1))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "max_count=%d, allow up to %d", max_count, (field_info.max_value + 1));
    }
exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*     get a report that contain the packets with the max latency.
*     user select one of the follwoing report: ingress latency, end to end latency.
* \param [in] unit -unit id
* \param [in] gport - indicates on the core id.
* \param [in] flags - iBCM_COSQ_LATENCY_END_TO_END: ndicates if the get the report from ing or egr (end to end) table
* \param [in] max_count - max entries to fill - indicates the size of array "max_latency_pkts"
* \param [out] max_latency_pkts - array of information of the max latency packets.
* \param [out] actual_count - actual size filled by the driver into max_latency_pkts.
*
* \return
*    shr_error_e
* \remark
*   None
* \see
*   NONE
*/
int
bcm_dnx_cosq_max_latency_pkts_get(
    int unit,
    bcm_gport_t gport,
    uint32 flags,
    int max_count,
    bcm_cosq_max_latency_pkts_t * max_latency_pkts,
    int *actual_count)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    /** Verify parameters */
    SHR_INVOKE_VERIFY_DNXC(dnx_cosq_latency_max_pkts_get_verify
                           (unit, gport, flags, max_count, max_latency_pkts, actual_count));
    if (_SHR_IS_FLAG_SET(flags, BCM_COSQ_LATENCY_END_TO_END))
    {
        SHR_IF_ERR_EXIT(dnx_cosq_latency_egress_max_get(unit, gport, max_count, max_latency_pkts, actual_count));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_max_get(unit, gport, max_count, max_latency_pkts, actual_count));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  function to calculate the new alpha value for the
*  probabilistic INGRESS latency based marking cni/drop
*  mechanism
*
*  when use calls API bcm_cosq_control_set with enums:
*
*      bcmCosqControlLatencyDropThreshold,
*      bcmCosqControlLatencyEcnThreshold,
*      bcmCosqControlLatencyDropProbBaseThreshold,
*      bcmCosqControlLatencyEcnProbBaseThreshold
*
*      and DropProb/EcnProb is enabled, the alpha value for the
*      probabilistic slope needs to be calculated according to
*      the new value
*
* \param [in] unit -unit id
* \param [in] profile_id - profile_id
* \param [in] is_cni - mark cni or drop
* \param [in] is_min - min threshold or max threshold is given
* \param [in] threshold_value - the threshold value that was
*        updated from user with API
* \param [out] shift_value - the new calculated shift value to
*        be set together with the new threshold value
* \return
*    shr_error_e
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_ingress_probability_marking_update_alpha_value(
    int unit,
    int profile_id,
    int is_cni,
    int is_min,
    int threshold_value,
    uint32 *shift_value)
{
    uint32 entry_handle_id, threshold_value_get = 0;
    uint64 delta_value = COMPILER_64_INIT(0, 0);
    dbal_fields_e min_max_field_id;
    dbal_tables_e table_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** read from HW the other value - if user updates min, need
     *  to get from HW the max threshold */
    if (is_min)
    {
        /** min threshold is changed, need to get the max threshold */
        min_max_field_id = is_cni ? DBAL_FIELD_LAT_CNI_THRESHOLD : DBAL_FIELD_LAT_DROP_THRESHOLD;
        table_id = DBAL_TABLE_LATENCY_INGRESS_PROFILE;
    }
    else
    {
         /** max threshold is changed, need to get the min threshold */
        min_max_field_id = is_cni ? DBAL_FIELD_MARK_CNI_MIN_THRESH : DBAL_FIELD_DROP_MIN_THRESH;
        table_id = DBAL_TABLE_LATENCY_INGRESS_PROBABILITY_MARK;
    }
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table_id, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);
    dbal_value_field32_request(unit, entry_handle_id, min_max_field_id, INST_SINGLE, &threshold_value_get);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
    /*
     * The code below is equivalent to:
     *   delta_value = (is_min) ? (threshold_value_get - threshold_value) : (threshold_value - threshold_value_get);
     */
    if (is_min)
    {
        COMPILER_64_SET(delta_value, 0, (threshold_value_get - threshold_value));
    }
    else
    {
        COMPILER_64_SET(delta_value, 0, (threshold_value - threshold_value_get));
    }
    /** calculate accordng to the formula */
    dnx_cosq_probability_marking_alpha_value_calculation(unit, delta_value, shift_value);

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  function set a single property of the ingress latency profile.
* \param [in] unit -unit id
* \param [in] profile_id - profile_id
* \param [in] cosq - offset/index  of the object.relevant just for type bin
* \param [in] type - property type of the profile
* \param [in] arg  - the value of the property
* \return
*    shr_error_e
* \remark
*   All threshold are in nano second units, same as the latency units.
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_ingress_probability_marking_set(
    int unit,
    int profile_id,
    bcm_cos_queue_t cosq,
    bcm_cosq_control_t type,
    int arg)
{
    uint32 entry_handle_id, is_enabled = 1, shift_value = 0;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** first check if the feature is supported */
    SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_probability_control_type_verify(unit, type));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_INGRESS_PROBABILITY_MARK, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);

    switch (type)
    {
        case bcmCosqControlLatencyDropThreshold:
            /** The max threshold set by same control with or without probabilistic mechanism*/
            if (dnx_data_latency.
                features.feature_get(unit, dnx_data_latency_features_drop_probabilistic_mechanism_support))
            {
                /** check if probability mechanism is enabled */
                dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_DROP_EN, INST_SINGLE, &is_enabled);
                SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
                if (is_enabled)
                {
                     /** max threshold is changed - need to update the alpha */
                    SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_probability_marking_update_alpha_value
                                    (unit, profile_id, 0, 0, arg, &shift_value));
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DROP_SHIFT, INST_SINGLE,
                                                 shift_value);
                }
            }
            break;
        case bcmCosqControlLatencyEcnThreshold:
            /** The max threshold set by same control with or without probabilistic mechanism*/
            if (dnx_data_latency.
                features.feature_get(unit, dnx_data_latency_features_ingress_ecn_probabilistic_mechanism_support))
            {
                /** check if probability mechanism is enabled */
                dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_MARK_CNI_EN, INST_SINGLE, &is_enabled);
                SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
                if (is_enabled)
                {
                     /** max threshold is changed - need to update the alpha */
                    SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_probability_marking_update_alpha_value
                                    (unit, profile_id, 1, 0, arg, &shift_value));
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_MARK_CNI_SHIFT, INST_SINGLE,
                                                 shift_value);
                }
            }
            break;
        case bcmCosqControlLatencyDropProbEnable:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DROP_EN, INST_SINGLE, arg);
            break;
        case bcmCosqControlLatencyDropProbBaseThreshold:

            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_DROP_EN, INST_SINGLE, &is_enabled);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            if (is_enabled)
            {
                dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DROP_MIN_THRESH, INST_SINGLE, arg);
                /** min threshold is changed - need to update the alpha */
                SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_probability_marking_update_alpha_value
                                (unit, profile_id, 0, 1, arg, &shift_value));
                dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DROP_SHIFT, INST_SINGLE, shift_value);
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Latency drop probability not enabled, call API first with type=bcmCosqControlLatencyDropProbEnable \n");
            }
            break;
        case bcmCosqControlLatencyEcnProbEnable:

            SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_ecn_marking_is_enable(unit, profile_id, &is_enabled));

            if (!is_enabled && arg == TRUE)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "type=%d not supported - ecn marking mechanism have to be enabled for this profile \n",
                             type);
            }

            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_MARK_CNI_EN, INST_SINGLE, arg);

            break;
        case bcmCosqControlLatencyEcnProbBaseThreshold:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_MARK_CNI_EN, INST_SINGLE, &is_enabled);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            if (is_enabled)
            {
                dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_MARK_CNI_MIN_THRESH, INST_SINGLE, arg);
                /** min threshold is changed - need to update the alpha */
                SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_probability_marking_update_alpha_value
                                (unit, profile_id, 1, 1, arg, &shift_value));
                dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_MARK_CNI_SHIFT, INST_SINGLE,
                                             shift_value);
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Latency mark ECN probability not enabled, call API first with type=bcmCosqControlLatencyEcnProbEnable \n");
            }
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for ingress latency profile \n", type);
            break;
    }

    if (is_enabled)
    {
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  function set a single property of the ingress latency profile.
* \param [in] unit -unit id
* \param [in] profile_id - profile_id
* \param [in] cosq - offset/index  of the object.relevant just for type bin
* \param [in] type - property type of the profile
* \param [in] arg  - the value of the property
* \return
*    shr_error_e
* \remark
*   All threshold are in nano second units, same as the latency units.
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_ingress_profile_set(
    int unit,
    int profile_id,
    bcm_cos_queue_t cosq,
    bcm_cosq_control_t type,
    int arg)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (type == bcmCosqControlLatencyBinThreshold)
    {
        /** Taking a handle */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_INGRESS_PROFILE_BINS, &entry_handle_id));
        /** set the table key */
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_BIN_ID, cosq);
    }
    else
    {
        /** Taking a handle */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_INGRESS_PROFILE, &entry_handle_id));
    }
    /** set the common tables key */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);

    switch (type)
    {
        case bcmCosqControlLatencyCounterEnable:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_STAT_ENABLE, INST_SINGLE, arg);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyDropEnable:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LATENCY_DROP_ENABLE, INST_SINGLE, arg);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyEcnEnable:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_CNI_ENABLE, INST_SINGLE, arg);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyDropThreshold:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_DROP_THRESHOLD, INST_SINGLE, arg);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            /** in case this is used to set max threshold for the
             *  probabilistic drop/mark mechanism also need to update the
             *  alpha value */
            if (dnx_data_latency.
                features.feature_get(unit, dnx_data_latency_features_drop_probabilistic_mechanism_support))
            {
                SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_probability_marking_set(unit, profile_id, cosq, type, arg));
            }
            break;
        case bcmCosqControlLatencyEcnThreshold:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_CNI_THRESHOLD, INST_SINGLE, arg);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            /** in case this is used to set max threshold for the
             *  probabilistic drop/mark mechanism also need to update the
             *  alpha value */
            if (dnx_data_latency.
                features.feature_get(unit, dnx_data_latency_features_ingress_ecn_probabilistic_mechanism_support))
            {
                SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_probability_marking_set(unit, profile_id, cosq, type, arg));
            }
            break;
        case bcmCosqControlLatencyTrackDropPacket:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_TRACK_DROP_ENABLE, INST_SINGLE, arg);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyTrack:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_TRACK_ENABLE, INST_SINGLE, arg);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyBinThreshold:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_BIN_THRESHOLD, INST_SINGLE, arg);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyDropProbEnable:
        case bcmCosqControlLatencyDropProbBaseThreshold:
        case bcmCosqControlLatencyEcnProbEnable:
        case bcmCosqControlLatencyEcnProbBaseThreshold:
            SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_probability_marking_set(unit, profile_id, cosq, type, arg));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for ingress latency profile \n", type);
            break;
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_cosq_latency_end_to_end_profile_set_arg_verify(
    int unit,
    bcm_cosq_control_t type,
    int arg)
{
    SHR_FUNC_INIT_VARS(unit);

    if (type == bcmCosqControlLatencyTrack)
    {
        if (arg != 0 && arg != 1)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "invalid mode %d for type %d \n", arg, type);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  function set a single property of the end to end latency profile.
* \param [in] unit -unit id
* \param [in] profile_id - profile_id
* \param [in] cosq - offset/index  of the object.relevant just for type bin
* \param [in] type - property type of the profile
* \param [in] arg  - the value of the property
* \return
*    shr_error_e
* \remark
*   All threshold are in nano second units, same as the latency units.
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_profile_set(
    int unit,
    int profile_id,
    bcm_cos_queue_t cosq,
    bcm_cosq_control_t type,
    int arg)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_cosq_latency_end_to_end_profile_set_arg_verify(unit, type, arg));

    if (type == bcmCosqControlLatencyBinThreshold)
    {
        /** Taking a handle */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_PROFILE_BINS, &entry_handle_id));
        /** set the table key */
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_BIN_ID, cosq);
    }
    else
    {
        /** Taking a handle */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_PROFILE, &entry_handle_id));
    }
    /** set the common tables key */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);

    /** if AQM profile is supported, check what type is given as
     *  some control types are not supported for E2E and should
     *  be done for AQM profile */
    if (dnx_data_latency.features.feature_get(unit, dnx_data_latency_features_valid_end_to_end_aqm_profile))
    {
        if (type == bcmCosqControlLatencyDropEnable || type == bcmCosqControlLatencyEcnEnable
            || type == bcmCosqControlLatencyDropThreshold || type == bcmCosqControlLatencyEcnThreshold)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "type=%d not supported for end to end latency profile, use end to end AQM profile \n", type);
        }
    }

    switch (type)
    {
        case bcmCosqControlLatencyCounterEnable:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_STAT_ENABLE, INST_SINGLE, arg);
            break;
        case bcmCosqControlLatencyDropEnable:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LATENCY_DROP_ENABLE, INST_SINGLE, arg);
            break;
        case bcmCosqControlLatencyEcnEnable:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_CNI_ENABLE, INST_SINGLE, arg);
            break;
        case bcmCosqControlLatencyDropThreshold:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_DROP_THRESHOLD, INST_SINGLE, arg);
            break;
        case bcmCosqControlLatencyEcnThreshold:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_CNI_THRESHOLD, INST_SINGLE, arg);
            break;
        case bcmCosqControlLatencyEgressCounterCommand:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_STAT_COMMAND, INST_SINGLE,
                                         STAT_PP_PROFILE_ID_GET(arg));
            break;
        case bcmCosqControlLatencyTrack:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_TRACK_ENABLE, INST_SINGLE, arg);
            break;
        case bcmCosqControlLatencyBinThreshold:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_BIN_THRESHOLD, INST_SINGLE, arg);
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for end to end latency profile \n", type);
            break;
    }

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  function to calculate the new alpha value for the
*  probabilistic EGRESS e2e aqm latency based marking cni/drop
*  mechanism
*
*  when use calls API bcm_cosq_control_set with enums:
*
*      bcmCosqControlLatencyDropThreshold,
*      bcmCosqControlLatencyEcnThreshold,
*      bcmCosqControlLatencyDropProbBaseThreshold,
*      bcmCosqControlLatencyEcnProbBaseThreshold
*
*      and DropProb/EcnProb is enabled, the alpha value for the
*      probabilistic slope needs to be calculated according to
*      the new value
*
* \param [in] unit -unit id
* \param [in] profile_id - profile_id
* \param [in] is_cni - mark cni or drop
* \param [in] is_min_changed - min threshold or max threshold is
*        given
* \param [in] pkt_is_typ - packet mode - typical/coupled
* \param [in] threshold_value - the threshold value that was
*        updated from user with API
* \param [out] shift_value - the new calculated shift value to
*        be set together with the new threshold value
* \return
*    shr_error_e
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_aqm_probability_marking_update_alpha_value(
    int unit,
    int profile_id,
    int is_cni,
    int is_min_changed,
    int pkt_is_typ,
    int threshold_value,
    uint32 *shift_value)
{
    uint32 entry_handle_id, threshold_value_get = 0;
    uint64 delta_value = COMPILER_64_INIT(0, 0);
    dbal_fields_e min_max_field_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** read from HW the other value - if user updates min, need
     *  to get from HW the max threshold */
    /** according to packet type */
    if (pkt_is_typ)
    {
        if (is_min_changed)
        {
            /** min threshold is changed, need to get the max threshold */
            min_max_field_id = is_cni ? DBAL_FIELD_CNI_MAX_THRESH : DBAL_FIELD_DROP_MAX_THRESH;
        }
        else
        {
            /** max threshold is changed, need to get the min threshold */
            min_max_field_id = is_cni ? DBAL_FIELD_CNI_MIN_THRESH : DBAL_FIELD_DROP_MIN_THRESH;
        }
    }
    else
    {
        if (is_min_changed)
        {
            /** min threshold is changed, need to get the max threshold */
            min_max_field_id = is_cni ? DBAL_FIELD_LQ_CNI_MAX_THRESH : DBAL_FIELD_DROP_MAX_THRESH;
        }
        else
        {
             /** max threshold is changed, need to get the min threshold */
            min_max_field_id = is_cni ? DBAL_FIELD_LQ_CNI_PROB_MIN_THRESH : DBAL_FIELD_DROP_MIN_THRESH;
        }
    }
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_DROP_CNI_PROFILE, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);
    dbal_value_field32_request(unit, entry_handle_id, min_max_field_id, INST_SINGLE, &threshold_value_get);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

    /*
     * The following clause implements:
     *   delta_value = (is_min_changed) ? (threshold_value_get - threshold_value) : (threshold_value - threshold_value_get);
     */
    if (is_min_changed)
    {
        COMPILER_64_SET(delta_value, 0, (threshold_value_get - threshold_value));
    }
    else
    {
        COMPILER_64_SET(delta_value, 0, (threshold_value - threshold_value_get));
    }
    /** calculate accordng to the formula */
    dnx_cosq_probability_marking_alpha_value_calculation(unit, delta_value, shift_value);

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  configure the drop/cni probability marking - enable,
*  thresholds etc. - depending on the packet type-
*  typ/classic/L4Q
* \param [in] unit -unit id
* \param [in] profile_id - profile_id
* \param [in] type - property type of the profile
* \param [in] arg  - the value of the property
* \return
*    shr_error_e
* \remark
*   All threshold are in nano second units, same as the latency units.
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_aqm_probability_marking_set(
    int unit,
    int profile_id,
    bcm_cosq_control_t type,
    int arg)
{
    uint32 entry_handle_id, is_enabled = 0, pkt_is_typ = 0, shift_value = 0;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** in order to know which profile to update need to know
     *  what type is the packet
     *  typical; LQ/Coupled Q */
    SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_probability_marking_is_typ(unit, profile_id, &pkt_is_typ));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_DROP_CNI_PROFILE, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);

    switch (type)
    {
        case bcmCosqControlLatencyDropEnable:
            /** configuration for TYP */
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DROP_MAX_ENABLE, INST_SINGLE, arg);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyEcnEnable:
            dbal_entry_value_field32_set(unit, entry_handle_id,
                                         (pkt_is_typ) ? DBAL_FIELD_CNI_MAX_ENABLE : DBAL_FIELD_LQ_CNI_MAX_ENABLE,
                                         INST_SINGLE, arg);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyDropThreshold:
            /** configuration for TYP */
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DROP_MAX_THRESH, INST_SINGLE, arg);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_LATENCY_EGRESS_DROP_CNI_PROFILE, entry_handle_id));
            /** check if DropProbability is enabled - if it is - must update
             *  the alpha value for the formula calculation */
            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_DROP_PROB_ENABLE, INST_SINGLE, &is_enabled);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_LATENCY_EGRESS_DROP_CNI_PROFILE, entry_handle_id));
            if (is_enabled)
            {
                SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_probability_marking_update_alpha_value
                                (unit, profile_id, 0, 0, pkt_is_typ, arg, &shift_value));
                dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);
                dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DROP_MIN_THRESH_SHIFT, INST_SINGLE,
                                             shift_value);
                SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            }
            break;
        case bcmCosqControlLatencyEcnThreshold:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CNI_MAX_THRESH, INST_SINGLE, arg);
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LQ_CNI_MAX_THRESH, INST_SINGLE, arg);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_LATENCY_EGRESS_DROP_CNI_PROFILE, entry_handle_id));

            /** check if MarkCNI Probability is enabled - if it is - must
             *  update the alpha value for the formula calculation */
            SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_probability_ecn_marking_is_enable
                            (unit, profile_id, pkt_is_typ, &is_enabled));

            if (is_enabled)
            {
                /** update both typ and LQ parameters, since even if mode is coupled, there is use of typ values */
                SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_probability_marking_update_alpha_value
                                (unit, profile_id, 1, 0, 0, arg, &shift_value));
                dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);
                dbal_entry_value_field32_set
                    (unit, entry_handle_id, DBAL_FIELD_LQ_CNI_PROB_MIN_SHIFT, INST_SINGLE, shift_value);
                SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_probability_marking_update_alpha_value
                                (unit, profile_id, 1, 0, 1, arg, &shift_value));
                dbal_entry_value_field32_set
                    (unit, entry_handle_id, DBAL_FIELD_CNI_MIN_THRESH_SHIFT, INST_SINGLE, shift_value);
                SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            }
            break;
        case bcmCosqControlLatencyEcnProbEnable:

            SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_ecn_marking_is_enable
                            (unit, profile_id, pkt_is_typ, &is_enabled));

            if (!is_enabled && arg == TRUE)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "type=%d not supported - ecn marking mechanism have to be enabled for this profile \n",
                             type);
            }

            /** Set dbal fields */
            {
                /** Legacy probabilistic mechanism */
                if (dnx_data_latency.
                    features.feature_get(unit, dnx_data_latency_features_probabilistic_legacy_mechanism_support))
                {
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CQ_CNI_PROB_ENABLE, INST_SINGLE,
                                                 arg);
                }

                /** Coupled mode is enable*/
                else if (dnx_data_latency.features.feature_get(unit, dnx_data_latency_features_coupled_mode_support)
                         && !pkt_is_typ)
                {
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LQ_CNI_PROB_ENABLE, INST_SINGLE,
                                                 arg);
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CQ_CNI_PROB_ENABLE, INST_SINGLE,
                                                 arg);
                }

                /** coupled mode not supported or not enabled*/
                else
                {
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CNI_PROB_ENABLE, INST_SINGLE, arg);
                }
            }

            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

            break;
        case bcmCosqControlLatencyEcnProbBaseThreshold:

            /** check if MarkCNI Probability is enabled */
            SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_probability_ecn_marking_is_enable
                            (unit, profile_id, pkt_is_typ, &is_enabled));
            if (!is_enabled)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "type=%d not supported - cni marking probability mechanism is not enabled for this profile \n",
                             type);
            }

            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CNI_MIN_THRESH, INST_SINGLE, arg);
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LQ_CNI_PROB_MIN_THRESH, INST_SINGLE, arg);

            if (dnx_data_latency.
                features.feature_get(unit, dnx_data_latency_features_probabilistic_legacy_mechanism_support))
            {
                dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LQ_CNI_CLASSIFICATION_THRESH,
                                             INST_SINGLE, arg);
            }

            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_LATENCY_EGRESS_DROP_CNI_PROFILE, entry_handle_id));

            /**  update the alpha value for the formula calculation
             * update both typ and LQ parameters, since even if mode is coupled, there is use of typ values */
            {
                SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_probability_marking_update_alpha_value
                                (unit, profile_id, 1, 1, 0, arg, &shift_value));
                dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);
                dbal_entry_value_field32_set(unit, entry_handle_id,
                                             DBAL_FIELD_LQ_CNI_PROB_MIN_SHIFT, INST_SINGLE, shift_value);
                SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_probability_marking_update_alpha_value
                                (unit, profile_id, 1, 1, 1, arg, &shift_value));
                dbal_entry_value_field32_set(unit, entry_handle_id,
                                             DBAL_FIELD_CNI_MIN_THRESH_SHIFT, INST_SINGLE, shift_value);
                SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            }
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for end to end AQM latency profile \n", type);
            break;
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  verify type parameter for control API with end-to-end-aqm latency
* \param [in] unit - unit id
* \param [in] type -  control type
* \return
*    shr_error_e
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_aqm_control_type_verify(
    int unit,
    bcm_cosq_control_t type)
{
    SHR_FUNC_INIT_VARS(unit);

    if (!dnx_data_latency.
        features.feature_get(unit, dnx_data_latency_features_egress_ecn_probabilistic_mechanism_support)
        && (type == bcmCosqControlLatencyEcnProbEnable || type == bcmCosqControlLatencyEcnProbBaseThreshold))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for end to end EQM latency profile \n", type);
    }

    if (!dnx_data_latency.features.feature_get(unit, dnx_data_latency_features_drop_probabilistic_mechanism_support) &&
        (type == bcmCosqControlLatencyDropProbEnable || type == bcmCosqControlLatencyDropProbBaseThreshold))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for end to end EQM latency profile \n", type);

    }

    if (!dnx_data_latency.features.feature_get(unit, dnx_data_latency_features_coupled_mode_support) &&
        (type == bcmCosqControlLatencyEgressCoupledAqmMode
         || type == bcmCosqControlLatencyEgressAqmL4sEcnClassificationThresholdMax
         || type == bcmCosqControlLatencyEcnProbConvertCoeff || type == bcmCosqControlLatencyEcnProbConvertExponent))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for end to end EQM latency profile \n", type);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  function set a single property of the end to end AQM latency
*  profile.
* \param [in] unit -unit id
* \param [in] profile_id - profile_id
* \param [in] cosq - offset/index  of the object.relevant just for type bin
* \param [in] type - property type of the profile
* \param [in] arg  - the value of the property
* \return
*    shr_error_e
* \remark
*   All threshold are in nano second units, same as the latency units.
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_aqm_profile_set(
    int unit,
    int profile_id,
    bcm_cos_queue_t cosq,
    bcm_cosq_control_t type,
    int arg)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Validation for control type */
    SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_control_type_verify(unit, type));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_DROP_CNI_PROFILE, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);
    switch (type)
    {
        case bcmCosqControlLatencyDropEnable:
        case bcmCosqControlLatencyEcnEnable:
        case bcmCosqControlLatencyDropThreshold:
        case bcmCosqControlLatencyEcnThreshold:
        case bcmCosqControlLatencyEcnProbEnable:
        case bcmCosqControlLatencyEcnProbBaseThreshold:
            SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_probability_marking_set(unit, profile_id, type, arg));
            break;
        case bcmCosqControlLatencyEcnProbConvertExponent:
        case bcmCosqControlLatencyEcnProbConvertCoeff:
            SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_ecn_probability_map_calculation(unit, type, arg));
            break;
        case bcmCosqControlLatencyEgressCoupledAqmMode:
            if (arg == TRUE)
            {
                dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_L4_AQM_LQ_ENABLE, INST_SINGLE, 1);
                dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_L4_AQM_CQ_ENABLE, INST_SINGLE, 1);
                dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_L4_AQM_TYP_ENABLE, INST_SINGLE, 0);
                SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            }
            else
            {
                dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_L4_AQM_LQ_ENABLE, INST_SINGLE, 0);
                dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_L4_AQM_CQ_ENABLE, INST_SINGLE, 0);
                dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_L4_AQM_TYP_ENABLE, INST_SINGLE, 1);
                SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            }
            break;
        case bcmCosqControlLatencyEgressAqmL4sEcnClassificationThresholdMax:
            /** relevant for coupled mode - if the packet is LQ, CNI will be
                marked by LQ classification only if latency is smaller than
                LQ_CNI_Classification_Threshold. otherwise, CNI will be
                marked by CQ
                define the max latency value in ns in which pkt will be
                defines as L4S */
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LQ_CNI_CLASSIFICATION_THRESH, INST_SINGLE,
                                         arg);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyEgressAqmAverageWeight:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_AVERAGE_WEIGHT, INST_SINGLE, arg);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for end to end AQM latency profile \n", type);
            break;
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_cosq_latency_profile_set_verify(
    int unit,
    bcm_gport_t profile_gport)
{

    int profile_nof = 0, profile_id = 0;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(bcm_dnx_cosq_latency_profile_id_get(unit, profile_gport, &profile_id));

    /** Verify profile ID within the valid range */
    SHR_IF_ERR_EXIT(bcm_dnx_cosq_latency_profile_nof_profiles_get(unit, profile_gport, &profile_nof));
    SHR_MAX_VERIFY(profile_id, profile_nof - 1, _SHR_E_PARAM,
                   "Latency-profile %d is out of range 0-%d\n", profile_id, profile_nof - 1);

    /** Latency profile must be allocated */
    SHR_IF_ERR_EXIT(bcm_dnx_cosq_latency_profile_is_allocated_verify(unit, profile_gport, TRUE  /* expect allocated
                                                                                                 * profile */ ));

    /** Canno't set properties for default profile*/
    if (profile_id == DNX_COSQ_LATENCY_DEFAULT_PROFILE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Cannot set properties for default profile, profile_id=%d \n", profile_id);
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_cosq_latency_profile_set(
    int unit,
    bcm_gport_t port,
    bcm_cos_queue_t cosq,
    bcm_cosq_control_t type,
    int arg)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_cosq_latency_profile_set_verify(unit, port));

    if (BCM_GPORT_IS_INGRESS_LATENCY_PROFILE(port))
    {
        SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_profile_set
                        (unit, BCM_GPORT_INGRESS_LATENCY_PROFILE_GET(port), cosq, type, arg));
    }
    else if (BCM_GPORT_IS_END_TO_END_LATENCY_PROFILE(port))
    {
        SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_profile_set
                        (unit, BCM_GPORT_END_TO_END_LATENCY_PROFILE_GET(port), cosq, type, arg));
    }
    else if (BCM_GPORT_IS_END_TO_END_AQM_LATENCY_PROFILE(port))
    {
        SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_profile_set
                        (unit, BCM_GPORT_LATENCY_END_TO_END_AQM_LATENCY_PROFILE_GET(port), cosq, type, arg));
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "Given gport is not latency related, configure latency profile in order to use cosq control type %d",
                     type);
    }

exit:
    SHR_FUNC_EXIT;

}

/**
* \brief
*  get a single property of the ingress latency profile serving
*  the mark CNI/drop probibalistic mechanism
* \param [in] unit -unit id
* \param [in] profile_id - profile_id
* \param [in] cosq - offset/index  of the object.relevant just for type bin
* \param [in] type - property type of the profile
* \param [out] arg  - the value of the property
* \return
*    shr_error_e
* \remark
*   All threshold are in nano second units, same as the latency units.
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_ingress_probability_marking_get(
    int unit,
    int profile_id,
    bcm_cos_queue_t cosq,
    bcm_cosq_control_t type,
    int *arg)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** first check if the feature is supported */
    SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_probability_control_type_verify(unit, type));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_INGRESS_PROBABILITY_MARK, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);

    switch (type)
    {
        case bcmCosqControlLatencyDropProbEnable:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_DROP_EN, INST_SINGLE, (uint32 *) arg);
            break;
        case bcmCosqControlLatencyDropProbBaseThreshold:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_DROP_MIN_THRESH, INST_SINGLE, (uint32 *) arg);
            break;
        case bcmCosqControlLatencyEcnProbEnable:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_MARK_CNI_EN, INST_SINGLE, (uint32 *) arg);
            break;
        case bcmCosqControlLatencyEcnProbBaseThreshold:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_MARK_CNI_MIN_THRESH, INST_SINGLE,
                                       (uint32 *) arg);
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for ingress latency profile \n", type);
            break;
    }
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  function get a single property value of the ingress latency profile.
* \param [in] unit -unit id
* \param [in] profile_id - profile_id
* \param [in] cosq - offset/index  of the object.relevant just for type bin
* \param [in] type - property type of the profile
* \param [out] arg  - the value of the property
* \return
*    shr_error_e
* \remark
*   All threshold are in nano second units, same as the latency units.
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_ingress_profile_get(
    int unit,
    int profile_id,
    bcm_cos_queue_t cosq,
    bcm_cosq_control_t type,
    int *arg)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (type == bcmCosqControlLatencyBinThreshold)
    {
        /** Taking a handle */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_INGRESS_PROFILE_BINS, &entry_handle_id));
        /** set the table key */
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_BIN_ID, cosq);
    }
    else
    {
        /** Taking a handle */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_INGRESS_PROFILE, &entry_handle_id));
    }
    /** set the common tables key */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);

    switch (type)
    {
        case bcmCosqControlLatencyCounterEnable:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_STAT_ENABLE, INST_SINGLE, (uint32 *) arg);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyDropEnable:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LATENCY_DROP_ENABLE, INST_SINGLE,
                                       (uint32 *) arg);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyEcnEnable:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_CNI_ENABLE, INST_SINGLE, (uint32 *) arg);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyDropThreshold:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_DROP_THRESHOLD, INST_SINGLE,
                                       (uint32 *) arg);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyEcnThreshold:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_CNI_THRESHOLD, INST_SINGLE,
                                       (uint32 *) arg);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyTrackDropPacket:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_TRACK_DROP_ENABLE, INST_SINGLE,
                                       (uint32 *) arg);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyTrack:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_TRACK_ENABLE, INST_SINGLE, (uint32 *) arg);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyBinThreshold:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_BIN_THRESHOLD, INST_SINGLE,
                                       (uint32 *) arg);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyDropProbEnable:
        case bcmCosqControlLatencyDropProbBaseThreshold:
        case bcmCosqControlLatencyEcnProbEnable:
        case bcmCosqControlLatencyEcnProbBaseThreshold:
            SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_probability_marking_get(unit, profile_id, cosq, type, arg));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for ingress latency profile \n", type);
            break;
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  function get a single property value of the end to end latency profile.
* \param [in] unit -unit id
* \param [in] profile_id - profile_id
* \param [in] cosq - offset/index  of the object.relevant just for type bin
* \param [in] type - property type of the profile
* \param [out] arg  - the value of the property
* \return
*    shr_error_e
* \remark
*   All threshold are in nano second units, same as the latency units.
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_profile_get(
    int unit,
    int profile_id,
    bcm_cos_queue_t cosq,
    bcm_cosq_control_t type,
    int *arg)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (type == bcmCosqControlLatencyBinThreshold)
    {
        /** Taking a handle */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_PROFILE_BINS, &entry_handle_id));
        /** set the table key */
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_BIN_ID, cosq);
    }
    else
    {
        /** Taking a handle */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_PROFILE, &entry_handle_id));
    }
    /** set the common tables key */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);

    /** if AQM profile is supported, check what type is given as
     *  some control types are not supported for E2E and should
     *  be done for AQM profile */
    if (dnx_data_latency.features.feature_get(unit, dnx_data_latency_features_valid_end_to_end_aqm_profile))
    {
        if (type == bcmCosqControlLatencyDropEnable || type == bcmCosqControlLatencyEcnEnable
            || type == bcmCosqControlLatencyDropThreshold || type == bcmCosqControlLatencyEcnThreshold)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "type=%d not supported for end to end latency profile, use end to end AQM profile \n", type);
        }
    }
    switch (type)
    {
        case bcmCosqControlLatencyCounterEnable:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_STAT_ENABLE, INST_SINGLE, (uint32 *) arg);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyDropEnable:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LATENCY_DROP_ENABLE, INST_SINGLE,
                                       (uint32 *) arg);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyEcnEnable:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_CNI_ENABLE, INST_SINGLE, (uint32 *) arg);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyDropThreshold:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_DROP_THRESHOLD, INST_SINGLE,
                                       (uint32 *) arg);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyEcnThreshold:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_CNI_THRESHOLD, INST_SINGLE,
                                       (uint32 *) arg);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyEgressCounterCommand:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_STAT_COMMAND, INST_SINGLE, (uint32 *) arg);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            STAT_PP_ENGINE_PROFILE_SET(*arg, *arg, bcmStatCounterInterfaceEgressTransmitPp);
            break;
        case bcmCosqControlLatencyTrack:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_TRACK_ENABLE, INST_SINGLE, (uint32 *) arg);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyBinThreshold:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_BIN_THRESHOLD, INST_SINGLE,
                                       (uint32 *) arg);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for end to end latency profile \n", type);
            break;
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  get the drop/cni probability marking cnfiguration - enable,
*  thresholds etc. - depending on the packet type-
*  typ/classic/L4Q
* \param [in] unit -unit id
* \param [in] profile_id - profile_id
* \param [in] type - property type of the profile
* \param [out] arg  - the value of the property
* \return
*    shr_error_e
* \remark
*   All threshold are in nano second units, same as the latency units.
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_aqm_probability_marking_get(
    int unit,
    int profile_id,
    bcm_cosq_control_t type,
    int *arg)
{
    uint32 entry_handle_id, pkt_is_typ;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** in order to know which profile to update need to know
     *  what type is the packet
     *  tyical; LQ/Coupled Q */
    SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_probability_marking_is_typ(unit, profile_id, &pkt_is_typ));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_DROP_CNI_PROFILE, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);

    switch (type)
    {
        case bcmCosqControlLatencyDropEnable:
            /** configuration for TYP */
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_DROP_MAX_ENABLE, INST_SINGLE, (uint32 *) arg);
            break;
        case bcmCosqControlLatencyEcnEnable:
            dbal_value_field32_request(unit, entry_handle_id,
                                       (pkt_is_typ) ? DBAL_FIELD_CNI_MAX_ENABLE : DBAL_FIELD_LQ_CNI_MAX_ENABLE,
                                       INST_SINGLE, (uint32 *) arg);
            break;
        case bcmCosqControlLatencyDropThreshold:
            /** configuration for TYP */
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_DROP_MAX_THRESH, INST_SINGLE, (uint32 *) arg);
            break;
        case bcmCosqControlLatencyEcnThreshold:
            dbal_value_field32_request(unit, entry_handle_id,
                                       (pkt_is_typ) ? DBAL_FIELD_CNI_MAX_THRESH : DBAL_FIELD_LQ_CNI_MAX_THRESH,
                                       INST_SINGLE, (uint32 *) arg);
            break;
        case bcmCosqControlLatencyEcnProbEnable:

            if (dnx_data_latency.
                features.feature_get(unit, dnx_data_latency_features_probabilistic_legacy_mechanism_support))
            {
                dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_CQ_CNI_PROB_ENABLE, INST_SINGLE,
                                           (uint32 *) arg);
            }
            else
            {
                dbal_value_field32_request(unit, entry_handle_id,
                                           (pkt_is_typ) ? DBAL_FIELD_CNI_PROB_ENABLE : DBAL_FIELD_LQ_CNI_PROB_ENABLE,
                                           INST_SINGLE, (uint32 *) arg);
            }

            break;
        case bcmCosqControlLatencyEcnProbBaseThreshold:
            dbal_value_field32_request(unit, entry_handle_id,
                                       (pkt_is_typ) ? DBAL_FIELD_CNI_MIN_THRESH : DBAL_FIELD_LQ_CNI_PROB_MIN_THRESH,
                                       INST_SINGLE, (uint32 *) arg);
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for end to end AQM latency profile \n", type);
            break;
    }

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  function get a single property value of the end to end latency profile.
* \param [in] unit -unit id
* \param [in] profile_id - profile_id
* \param [in] cosq - offset/index  of the object.relevant just for type bin
* \param [in] type - property type of the profile
* \param [out] arg  - the value of the property
* \return
*    shr_error_e
* \remark
*   All threshold are in nano second units, same as the latency units.
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_end_to_end_aqm_profile_get(
    int unit,
    int profile_id,
    bcm_cos_queue_t cosq,
    bcm_cosq_control_t type,
    int *arg)
{
    uint32 entry_handle_id, field_get;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_control_type_verify(unit, type));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_EGRESS_DROP_CNI_PROFILE, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, profile_id);

    switch (type)
    {
        case bcmCosqControlLatencyDropEnable:
        case bcmCosqControlLatencyEcnEnable:
        case bcmCosqControlLatencyDropThreshold:
        case bcmCosqControlLatencyEcnThreshold:
        case bcmCosqControlLatencyEcnProbEnable:
        case bcmCosqControlLatencyEcnProbBaseThreshold:
            SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_probability_marking_get(unit, profile_id, type, arg));
            break;
        case bcmCosqControlLatencyEcnProbConvertExponent:
            SHR_IF_ERR_EXIT(dnx_cosq_latency_db.probability_convert.exponent_b.get(unit, (uint32 *) arg));
            break;
        case bcmCosqControlLatencyEcnProbConvertCoeff:
            SHR_IF_ERR_EXIT(dnx_cosq_latency_db.probability_convert.coefficient_a.get(unit, (uint32 *) arg));
            break;
        case bcmCosqControlLatencyEgressCoupledAqmMode:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_L4_AQM_TYP_ENABLE, INST_SINGLE, &field_get);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            *arg = !field_get; /** if TYP is disabled the mode is coupled*/
            break;
        case bcmCosqControlLatencyEgressAqmL4sEcnClassificationThresholdMax:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LQ_CNI_CLASSIFICATION_THRESH, INST_SINGLE,
                                       (uint32 *) arg);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            break;
        case bcmCosqControlLatencyEgressAqmAverageWeight:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_AVERAGE_WEIGHT, INST_SINGLE, (uint32 *) arg);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for end to end latency profile \n", type);
            break;
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_cosq_latency_profile_get(
    int unit,
    bcm_gport_t port,
    bcm_cos_queue_t cosq,
    bcm_cosq_control_t type,
    int *arg)
{
    SHR_FUNC_INIT_VARS(unit);

    if (BCM_GPORT_IS_INGRESS_LATENCY_PROFILE(port))
    {
        SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_profile_get
                        (unit, BCM_GPORT_INGRESS_LATENCY_PROFILE_GET(port), cosq, type, arg));
    }
    else if (BCM_GPORT_IS_END_TO_END_LATENCY_PROFILE(port))
    {
        SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_profile_get
                        (unit, BCM_GPORT_END_TO_END_LATENCY_PROFILE_GET(port), cosq, type, arg));
    }
    else if (BCM_GPORT_IS_END_TO_END_AQM_LATENCY_PROFILE(port))
    {
        SHR_IF_ERR_EXIT(dnx_cosq_latency_end_to_end_aqm_profile_get
                        (unit, BCM_GPORT_LATENCY_END_TO_END_AQM_LATENCY_PROFILE_GET(port), cosq, type, arg));
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "Given gport is not latency related, configure latency profile in order to use cosq control type %d",
                     type);
    }

exit:
    SHR_FUNC_EXIT;

}

/**
* \brief
*  get from HW the quartet profile per queue
* \param [in] unit -unit id
* \param [in] core - core id
* \param [in] qid - queue id
* \param [out] profile_id - queue quartet profile id
* \return
*    shr_error_e
* \remark
*   None
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_queue_quartet_profile_id_get(
    int unit,
    int core,
    int qid,
    uint32 *profile_id)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** get the quartet profile id */
    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_VOQ_QUARTET_PROFILE, &entry_handle_id));

    /** Setting key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_QUARTET_QUEUE,
                               (qid / DNX_COSQ_LATENCY_QUEUE_QUARTET_RESOLUTION));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core);

    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, INST_SINGLE, profile_id);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_cosq_latency_ingress_queue_map_verify(
    int unit,
    int core,
    int flags,
    int lat_profile_id,
    int qid)
{
    SHR_FUNC_INIT_VARS(unit);

    /** verify that the profile_id is quartet base */
    if (lat_profile_id % DNX_COSQ_LATENCY_QUEUE_QUARTET_RESOLUTION != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid lat_profile_id (=%d)", lat_profile_id);
    }
    /** verify that the queue-id is quartet base */
    if (qid % DNX_COSQ_LATENCY_QUEUE_QUARTET_RESOLUTION != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid queue_id (=%d)", qid);
    }

    DNXCMN_CORE_VALIDATE(unit, core, TRUE);

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_cosq_latency_ingress_queue_profile_set(
    int unit,
    int profile,
    dnx_cosq_latency_queue_template_t * info)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_VOQ_QUARTET_PROFILE_MAP, &entry_handle_id));

    /** Setting key fields */

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_QUARTET_PROFILE, profile);

    /** Setting values  */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_FLOW_PROFILE, INST_SINGLE, info->latency_map);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TC_MAP, INST_SINGLE, info->tc_map);

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_cosq_latency_ingress_queue_profile_info_get(
    int unit,
    int profile,
    dnx_cosq_latency_queue_template_t * info)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_VOQ_QUARTET_PROFILE_MAP, &entry_handle_id));

    /** Setting key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_QUARTET_PROFILE, profile);

    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_FLOW_PROFILE, INST_SINGLE,
                               (uint32 *) &info->latency_map);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_TC_MAP, INST_SINGLE, (uint32 *) &info->tc_map);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_cosq_latency_ingress_queue_profile_map(
    int unit,
    int core,
    int qid,
    int profile)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_VOQ_QUARTET_PROFILE, &entry_handle_id));

    /** Setting key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_QUARTET_QUEUE,
                               (qid / DNX_COSQ_LATENCY_QUEUE_QUARTET_RESOLUTION));

    if (core == BCM_CORE_ALL)
        dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    else
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core);

    /** Setting values  */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PROFILE_ID, INST_SINGLE, profile);

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_cosq_latency_ingress_queue_map_set(
    int unit,
    int core,
    int flags,
    int qid,
    int lat_profile_id)
{
    uint32 quartet_profile_id;
    dnx_cosq_latency_queue_template_t profile_info;
    int new_profile;
    uint8 first_reference, last_reference;
    int curr_core;
    SHR_FUNC_INIT_VARS(unit);

    /** verify inputs params */
    SHR_INVOKE_VERIFY_DNXC(dnx_cosq_latency_ingress_queue_map_verify(unit, core, flags, lat_profile_id, qid));

    DNXCMN_CORES_ITER(unit, core, curr_core)
    {
        /** get the quartet_profile_id for the qid */
        SHR_IF_ERR_EXIT(dnx_cosq_latency_queue_quartet_profile_id_get(unit, curr_core, qid, &quartet_profile_id));

        /** get the old profile info*/
        SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_queue_profile_info_get(unit, quartet_profile_id, &profile_info));

        /** modify the latency_map of the profile for template manager usage */
        profile_info.latency_map = lat_profile_id / DNX_COSQ_LATENCY_QUEUE_QUARTET_RESOLUTION;

        /** exchange the profile */
        SHR_IF_ERR_EXIT(dnx_cosq_latency_db.queue_template.exchange(unit, 0, &profile_info,
                                                                    quartet_profile_id, NULL, &new_profile,
                                                                    &first_reference, &last_reference));

        /** update profile in HW */
        if (first_reference == TRUE)
        {
            SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_queue_profile_set(unit, new_profile, &profile_info));
        }

        /** map the queue quartet to the new profile */
        SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_queue_profile_map(unit, curr_core, qid, new_profile));

    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_cosq_symmetric_profile_cheack(
    int unit,
    int qid,
    int *is_symmetric_profile)
{
    uint32 quartet_profile_id;
    uint32 tmp_quartet_profile_id;
    int core;
    uint8 core_found = FALSE;
    SHR_FUNC_INIT_VARS(unit);

    *is_symmetric_profile = 1;

    DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core)
    {
        if (core_found)
        {
            SHR_IF_ERR_EXIT(dnx_cosq_latency_queue_quartet_profile_id_get(unit, core, qid, &tmp_quartet_profile_id));

            if (tmp_quartet_profile_id != quartet_profile_id)
            {
                *is_symmetric_profile = 0;
                break;
            }
        }
        else
        {
            SHR_IF_ERR_EXIT(dnx_cosq_latency_queue_quartet_profile_id_get(unit, core, qid, &quartet_profile_id));
            core_found = TRUE;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_cosq_latency_ingress_queue_map_get_verify(
    int unit,
    int core,
    int qid)
{
    int is_symmetric_profile;
    SHR_FUNC_INIT_VARS(unit);

    if (core == BCM_CORE_ALL)
    {
        dnx_cosq_symmetric_profile_cheack(unit, qid, &is_symmetric_profile);

        if (!is_symmetric_profile)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "get profile for asymetric configuration requier a specific core, got BCM_CORE_ALL");
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_cosq_latency_ingress_queue_map_get(
    int unit,
    int core,
    int flags,
    int qid,
    int *lat_profile_id)
{
    uint32 quartet_profile_id;
    dnx_cosq_latency_queue_template_t info;
    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_cosq_latency_ingress_queue_map_get_verify(unit, core, qid));

    core = (core == BCM_CORE_ALL) ? 0 : core;
    /** get the quartet_profile_id for the qid */
    SHR_IF_ERR_EXIT(dnx_cosq_latency_queue_quartet_profile_id_get(unit, core, qid, &quartet_profile_id));

    SHR_IF_ERR_EXIT(dnx_cosq_latency_ingress_queue_profile_info_get(unit, quartet_profile_id, &info));
    *lat_profile_id = info.latency_map * DNX_COSQ_LATENCY_QUEUE_QUARTET_RESOLUTION;

exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_cosq_latency_end_to_end_per_port_set(
    int unit,
    int enable)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_END_TO_END_CONFIG, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, BCM_CORE_ALL);

    /** Setting values  */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_PER_FLOW_ENABLE, INST_SINGLE, (enable == FALSE));
    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_cosq_latency_end_to_end_per_port_get(
    int unit,
    int *enable)
{
    uint32 entry_handle_id;
    uint32 flow_enable;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_END_TO_END_CONFIG, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, BCM_CORE_ALL);

    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAT_PER_FLOW_ENABLE, INST_SINGLE, &flow_enable);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
    *enable = (flow_enable == FALSE);
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_cosq_latency_end_to_end_port_map_verify(
    int unit,
    uint32 flags,
    bcm_gport_t gport_to_map,
    int profile_id)
{
    SHR_FUNC_INIT_VARS(unit);

    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid flags (=%d)", flags);
    }
exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_cosq_latency_end_to_end_port_map_set(
    int unit,
    uint32 flags,
    bcm_gport_t gport_to_map,
    int profile_id)
{
    dnx_algo_gpm_gport_phy_info_t gport_info;
    uint32 pp_port_index;
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** verify inputs params */
    SHR_INVOKE_VERIFY_DNXC(dnx_cosq_latency_end_to_end_port_map_verify(unit, flags, gport_to_map, profile_id));

    SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get
                    (unit, gport_to_map, DNX_ALGO_GPM_GPORT_TO_PHY_OP_PP_PORT_IS_MANDATORY, &gport_info));
    for (pp_port_index = 0; pp_port_index < gport_info.internal_port_pp_info.nof_pp_ports; pp_port_index++)
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_PP_PORT, &entry_handle_id));
        /** Set key fields */
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT,
                                   gport_info.internal_port_pp_info.pp_port[pp_port_index]);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID,
                                   gport_info.internal_port_pp_info.core_id[pp_port_index]);
        /** Set profile */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LATENCY_FLOW_PROFILE, INST_SINGLE, profile_id);

        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_cosq_latency_end_to_end_port_map_get(
    int unit,
    uint32 flags,
    bcm_gport_t gport_to_map,
    int *profile_id)
{
    dnx_algo_gpm_gport_phy_info_t gport_info;
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get
                    (unit, gport_to_map, DNX_ALGO_GPM_GPORT_TO_PHY_OP_PP_PORT_IS_MANDATORY, &gport_info));
    /** take the profile from the first pp port in the array */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_PP_PORT, &entry_handle_id));
    /** Set key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, gport_info.internal_port_pp_info.pp_port[0]);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, gport_info.internal_port_pp_info.core_id[0]);
    /** Get profile */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LATENCY_FLOW_PROFILE, INST_SINGLE,
                               (uint32 *) profile_id);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  function set ingress latency voq settings - bins, MC,Sniff
* \param [in] unit -unit id
* \param [in] profile_id - profile_id
* \param [in] cosq - offset/index  of the range.relevant just for type bin
* \param [in] type - property type of the profile
* \param [in] arg  - the value of the property
* \return
*    shr_error_e
* \remark
*   All threshold are in nano second units, same as the latency units.
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_voq_settings_set(
    int unit,
    int profile_id,
    bcm_cos_queue_t cosq,
    bcm_cosq_control_t type,
    int arg)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** set bin thresholds for given bin threshold id(cosq) */
    if (type == bcmCosqControlLatencyVoqRejectBinThreshold)
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_VOQ_RANGES, &entry_handle_id));
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_FLOW_PROFILE, profile_id);
    }
    /** get MC/SNIFF setting */
    else
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_VOQ_RJCT_SETTINGS, &entry_handle_id));
    }

    switch (type)
    {
        case bcmCosqControlLatencyVoqRejectBinThreshold:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RANGE_THRESHOLD, cosq, arg);
            break;
        case bcmCosqControlLatencyVoqRejectFilterMulticast:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RJCT_FILTER_MC, INST_SINGLE, arg);
            break;
        case bcmCosqControlLatencyVoqRejectFilterSniff:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RJCT_FILTER_SNIFF, INST_SINGLE, arg);
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for ingress latency profile \n", type);
            break;
    }

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  function get ingress latency voq settings - bins, MC,Sniff
* \param [in] unit -unit id
* \param [in] profile_id - profile_id
* \param [in] cosq - offset/index  of the range.relevant just for type bin
* \param [in] type - property type of the profile
* \param [out] arg  - the value of the property
* \return
*    shr_error_e
* \remark
*   All threshold are in nano second units, same as the latency units.
* \see
*   NONE
*/
static shr_error_e
dnx_cosq_latency_voq_settings_get(
    int unit,
    int profile_id,
    bcm_cos_queue_t cosq,
    bcm_cosq_control_t type,
    int *arg)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** get bin thresholds for given bin threshold id(cosq) */
    if (type == bcmCosqControlLatencyVoqRejectBinThreshold)
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_VOQ_RANGES, &entry_handle_id));
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LAT_FLOW_PROFILE, profile_id);
    }
    /** get MC/SNIFF setting */
    else
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_VOQ_RJCT_SETTINGS, &entry_handle_id));
    }
    switch (type)
    {
        case bcmCosqControlLatencyVoqRejectBinThreshold:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_RANGE_THRESHOLD, cosq, (uint32 *) arg);
            break;
        case bcmCosqControlLatencyVoqRejectFilterMulticast:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_RJCT_FILTER_MC, INST_SINGLE, (uint32 *) arg);
            break;
        case bcmCosqControlLatencyVoqRejectFilterSniff:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_RJCT_FILTER_SNIFF, INST_SINGLE,
                                       (uint32 *) arg);
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for ingress latency profile \n", type);
            break;
    }
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_cosq_latency_config_set(
    int unit,
    bcm_gport_t port,
    bcm_cos_queue_t cosq,
    bcm_cosq_control_t type,
    int arg)
{
    SHR_FUNC_INIT_VARS(unit);

    /** latency voq admission */
    if (BCM_GPORT_IS_INGRESS_LATENCY_PROFILE(port)
        && (type == bcmCosqControlLatencyVoqRejectBinThreshold
            || type == bcmCosqControlLatencyVoqRejectFilterMulticast
            || type == bcmCosqControlLatencyVoqRejectFilterSniff))
    {
        SHR_IF_ERR_EXIT(dnx_cosq_latency_voq_settings_set
                        (unit, BCM_GPORT_INGRESS_LATENCY_PROFILE_GET(port), cosq, type, arg));
    }
    /** latency profile */
    else
    {
        SHR_IF_ERR_EXIT(dnx_cosq_latency_profile_set(unit, port, cosq, type, arg));
    }
exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_cosq_latency_config_get(
    int unit,
    bcm_gport_t port,
    bcm_cos_queue_t cosq,
    bcm_cosq_control_t type,
    int *arg)
{
    SHR_FUNC_INIT_VARS(unit);

    /** latency voq admission */
    if (BCM_GPORT_IS_INGRESS_LATENCY_PROFILE(port)
        && (type == bcmCosqControlLatencyVoqRejectBinThreshold
            || type == bcmCosqControlLatencyVoqRejectFilterMulticast
            || type == bcmCosqControlLatencyVoqRejectFilterSniff))
    {
        SHR_IF_ERR_EXIT(dnx_cosq_latency_voq_settings_get
                        (unit, BCM_GPORT_INGRESS_LATENCY_PROFILE_GET(port), cosq, type, arg));
    }
    /** latency profile */
    else
    {
        SHR_IF_ERR_EXIT(dnx_cosq_latency_profile_get(unit, port, cosq, type, arg));
    }
exit:
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_cosq_latency_cosq_param_set(
    int unit,
    uint32 flags,
    bcm_gport_t gport,
    uint32 key,
    bcm_cosq_generic_control_t type,
    uint32 arg)
{
    uint32 entry_handle_id, rate_class = 0, granularity = 0;
    int bin = 0, dp = 0, reject_prob = 0;
    dbal_table_field_info_t field_info;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Determine the granularity for the internal representation
     *  encoding of the thresholds */
    granularity = dnx_data_ingr_congestion.info.bytes_threshold_granularity_get(unit);
    rate_class = BCM_GPORT_PROFILE_GET(gport);
    dp = (type ==
          bcmCosqGenericControlLatencyVoqRejectProb) ? BCM_COSQ_GENERIC_KEY_LAT_BIN_COLOR_COLOR_GET(key) :
        BCM_COSQ_GENERIC_KEY_COLOR_GET(key);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_VOQ_DISCARD_PARAMS, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_VOQ_RATE_CLASS, rate_class);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_DP, dp);

    switch (type)
    {
        case bcmCosqGenericControlLatencyVoqRejectEnable:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ENABLE, INST_SINGLE, arg);
            break;
        case bcmCosqGenericControlLatencyVoqRejectProb:
            bin = BCM_COSQ_GENERIC_KEY_LAT_BIN_COLOR_BIN_GET(key);
            /** prepare the argument in percentage units for
             *  RejectProbabilities */
            SHR_IF_ERR_EXIT(dbal_tables_field_info_get
                            (unit, DBAL_TABLE_LATENCY_VOQ_DISCARD_PARAMS, DBAL_FIELD_RJCT_PROB, FALSE, 0, bin,
                             &field_info));
            reject_prob = field_info.max_value - (arg * UTILEX_DIV_ROUND_DOWN(field_info.max_value, 100));
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RJCT_PROB, bin, reject_prob);
            break;
        case bcmCosqGenericControlLatencyVoqRejectMinThreshold:
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ADMIT_THRESHOLD, INST_SINGLE,
                                         UTILEX_DIV_ROUND_DOWN(arg, granularity));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for cosq generic latency settings \n", type);
            break;
    }
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** see .h file */
shr_error_e
dnx_cosq_latency_cosq_param_get(
    int unit,
    uint32 flags,
    bcm_gport_t gport,
    uint32 key,
    bcm_cosq_generic_control_t type,
    uint32 *arg)
{
    uint32 entry_handle_id, rate_class = 0, granularity = 0;
    int bin = 0, dp = 0;
    uint32 reject_probability_hw = 0;
    dbal_table_field_info_t field_info;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

     /** Determine the granularity for the internal representation
     *  encoding of the thresholds */
    granularity = dnx_data_ingr_congestion.info.bytes_threshold_granularity_get(unit);
    rate_class = BCM_GPORT_PROFILE_GET(gport);
    dp = (type ==
          bcmCosqGenericControlLatencyVoqRejectProb) ? BCM_COSQ_GENERIC_KEY_LAT_BIN_COLOR_COLOR_GET(key) :
        BCM_COSQ_GENERIC_KEY_COLOR_GET(key);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_LATENCY_VOQ_DISCARD_PARAMS, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_VOQ_RATE_CLASS, rate_class);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_DP, dp);

    switch (type)
    {
        case bcmCosqGenericControlLatencyVoqRejectEnable:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_ENABLE, INST_SINGLE, (uint32 *) arg);
            break;
        case bcmCosqGenericControlLatencyVoqRejectProb:
            bin = BCM_COSQ_GENERIC_KEY_LAT_BIN_COLOR_BIN_GET(key);
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_RJCT_PROB, bin, &reject_probability_hw);
            SHR_IF_ERR_EXIT(dbal_tables_field_info_get
                            (unit, DBAL_TABLE_LATENCY_VOQ_DISCARD_PARAMS, DBAL_FIELD_RJCT_PROB, FALSE, 0, bin,
                             &field_info));
            break;
        case bcmCosqGenericControlLatencyVoqRejectMinThreshold:
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_ADMIT_THRESHOLD, INST_SINGLE, (uint32 *) arg);
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "type=%d not supported for cosq generic latency settings \n", type);
            break;
    }
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

    if (type == bcmCosqGenericControlLatencyVoqRejectProb)
    {
        /** convert hw value to percentage units - granularity is max
         *  field value / 100 */
        *arg =
            UTILEX_DIV_ROUND_DOWN((field_info.max_value - reject_probability_hw),
                                  UTILEX_DIV_ROUND_DOWN(field_info.max_value, 100));
    }
    if (type == bcmCosqGenericControlLatencyVoqRejectMinThreshold)
    {
        *arg = *arg * granularity;
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

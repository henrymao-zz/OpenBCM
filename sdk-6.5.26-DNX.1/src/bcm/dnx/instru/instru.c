/** \file instru.c
 * 
 *
 * Visibility procedures for DNX in instrumentation module.
 *
 * This file contains functions for visibility configuration.
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_INSTRU
/*
 * Include
 * {
 */
#include <soc/sand/shrextend/shrextend_debug.h>
#include <soc/dnx/dnx_visibility.h>
#include <soc/dnx/dbal/dbal.h>
#include <soc/dnx/dnx_err_recovery_manager.h>
#include <soc/dnx/pll/pll.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_instru.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_headers.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_nif.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_mpls.h>

#include <soc/dnxc/dnxc_time.h>
#include <shared/utilex/utilex_u64.h>
#include <shared/utilex/utilex_tod_1588.h>

#include <bcm_int/dnx/instru/instru_ipt.h>
#include <bcm_int/dnx/instru/instru_sflow.h>
#include <bcm_int/dnx/instru/instru.h>
#include <bcm_int/dnx/algo/algo_gpm.h>
#include <bcm_int/dnx/mpls/mpls.h>
#include <bcm_int/dnx/qos/qos.h>
#include <bcm_int/dnx/cmn/dnxcmn.h>
#include <bcm/types.h>
#include <bcm/instru.h>
#include <bcm_int/dnx/lif/lif_lib.h>
#include <bcm_int/dnx/port/port.h>

#include <soc/dnx/swstate/auto_generated/types/instru_counters_types.h>
#include <soc/dnx/swstate/auto_generated/access/instru_counters_access.h>

#include <bcm_int/dnx/algo/port/algo_port_mgmt.h>
#include <bcm_int/dnx/algo/port/algo_port_utils.h>
#include <bcm_int/dnx/port/imb/imb.h>
#include <bcm_int/dnx/port/port_sit.h>
#include <bcm_int/dnx/auto_generated/dnx_instru_dispatch.h>

#include "instru_internal.h"

/*
 * }
 */

/*
 * Function Declaration.
 * {
 */

/*
 * }
 */

/*
 * Defines.
 * {
 */
#define INSTRU_IFA_OAM_LIF_SET 1

/* INT data format */
#define IFA2_0_MD_FORMAT 1
#define TAIL_EDITING_MD_FORMAT 2

/* ALU profiles */
#define ALU_IFA2_0_INTERMEDIATE_NODE 1
#define ALU_IFA2_0_TERMINATION_NODE  2

/* ALU configuration */
#define ALU_OPERATION_ADD 0
#define ALU_OPERATION_SUB 1
#define ALU_OPERAND_FFC_0 0
#define ALU_OPERAND_FFC_1 1
#define ALU_OPERAND_FROM_VALUE_0 2
#define ALU_OPERAND_FROM_VALUE_1 3

/* IPv6 Hop-by-hop Path-Tracing */
#define BCM_INSTRU_PATH_TRACING_OUT_INTF_ID_MAX 4095
#define BCM_INSTRU_PATH_TRACING_OUT_INTF_LOAD_MAX 15
#define BCM_INSTRU_PATH_TRACING_TIME_TEMPLATE_MAX 1
#define BCM_INSTRU_PATH_TRACING_TIME_LSB_OFFSET_MIN 8
#define BCM_INSTRU_PATH_TRACING_TIME_LSB_OFFSET_MAX 24
 /*
  * }
  */

 /*
  * Internal functions.
  * {
  */

 /*
  * }
  */

/**
 * \brief - verify procedure for dnx_instru_trace_probability_get()
 */
static shr_error_e
dnx_instru_trace_probability_get_verify(
    int unit,
    uint32 flags,
    bcm_gport_t gport,
    int *percentage)
{
    SHR_FUNC_INIT_VARS(unit);

    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid flags provided %d", flags);
    }

    /** null check */
    SHR_NULL_CHECK(percentage, _SHR_E_PARAM, "percentage");

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - verify procedure for dnx_instru_trace_probability_set()
 */
static shr_error_e
dnx_instru_trace_probability_set_verify(
    int unit,
    uint32 flags,
    bcm_gport_t gport,
    int percentage)
{
    SHR_FUNC_INIT_VARS(unit);

    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid flags provided %d", flags);
    }

    if (percentage < 0 || percentage > 1000)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid percentage value was provided %d", percentage);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Get port trace probability, the returned probability is given in units of one-tenth percentage.
 */
static shr_error_e
dnx_instru_trace_probability_get(
    int unit,
    uint32 flags,
    bcm_gport_t gport,
    int *percentage)
{
    uint32 entry_handle_id, field32;
    dnx_algo_gpm_gport_phy_info_t gport_info;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** verify */
    SHR_INVOKE_VERIFY_DNXC(dnx_instru_trace_probability_get_verify(unit, flags, gport, percentage));

    /** Get Port + Core */
    SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get(unit, gport, DNX_ALGO_GPM_GPORT_TO_PHY_OP_PP_PORT_IS_MANDATORY,
                                                    &gport_info));

    /** create handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_PP_PORT, &entry_handle_id));

    /** set keys - pp port and core */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, gport_info.internal_port_pp_info.pp_port[0]);

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, gport_info.internal_port_pp_info.core_id[0]);

    /** request trace probability */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_TRACE_PROBABILITY, INST_SINGLE, &field32);

    /** commit */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

    /**
     * calculate percentage in units of one-tenth from HW field.
     * The HW formula should be as following:
     *
     *         hw_field
     * -------------------------- x 1000
     *        MAX_FIELD_VAL
     */
    {
        int max_field_val;

        SHR_IF_ERR_EXIT(dbal_tables_field_max_value_get(unit, DBAL_TABLE_INGRESS_PP_PORT, DBAL_FIELD_TRACE_PROBABILITY,
                                                        FALSE, 0, 0, &max_field_val));

        *percentage = ((field32) * 1000) / max_field_val;
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Set port trace probability, the provided probability is given in units of one-tenth percentage.
 */
static shr_error_e
dnx_instru_trace_probability_set(
    int unit,
    uint32 flags,
    bcm_gport_t gport,
    int percentage)
{
    uint32 probability;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** verify */
    SHR_INVOKE_VERIFY_DNXC(dnx_instru_trace_probability_set_verify(unit, flags, gport, percentage));

    /**
     * calculate HW probability from percentage given in units of one tenth.
     * The HW formula should be as following:
     *
     *     percentage
     * -------------------- x MAX_FIELD_VAL
     *        1000
     */
    {
        int max_field_val;

        SHR_IF_ERR_EXIT(dbal_tables_field_max_value_get(unit, DBAL_TABLE_INGRESS_PP_PORT, DBAL_FIELD_TRACE_PROBABILITY,
                                                        FALSE, 0, 0, &max_field_val));

        probability = (percentage * max_field_val) / 1000;
    }

    /** Set probability to HW */
    {
        uint32 entry_handle_id;
        dnx_algo_gpm_gport_phy_info_t gport_info;
        int pp_port_index;

        /** Get Port + Core */
        SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get
                        (unit, gport, DNX_ALGO_GPM_GPORT_TO_PHY_OP_PP_PORT_IS_MANDATORY, &gport_info));

        /** create handle */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_PP_PORT, &entry_handle_id));

        /** iterate over pp port and commit to HW */
        for (pp_port_index = 0; pp_port_index < gport_info.internal_port_pp_info.nof_pp_ports; pp_port_index++)
        {
            /** set keys - pp port and core */
            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT,
                                       gport_info.internal_port_pp_info.pp_port[pp_port_index]);
            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID,
                                       gport_info.internal_port_pp_info.core_id[pp_port_index]);

            /** set value - probability */
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRACE_PROBABILITY, INST_SINGLE, probability);

            /** commit */
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
        }
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - verify procedure for dnx_instru_path_tracing_out_intf_XXX()
 */
static shr_error_e
dnx_instru_path_tracing_out_intf_verify(
    int unit,
    uint32 flags,
    bcm_gport_t gport)
{
    uint8 is_phy_port;
    int coe_enable;
    dnx_algo_port_info_s port_info;
    bcm_port_t local_port;
    dnx_algo_gpm_gport_phy_info_t gport_info;

    SHR_FUNC_INIT_VARS(unit);

    if (flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid flags provided %d", flags);
    }

    SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_is_physical(unit, gport, &is_phy_port));
    if (!is_phy_port)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Local port is needed to set interface ID\n");
    }

    /** Convert gport to logical port */
    SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get
                    (unit, gport, DNX_ALGO_GPM_GPORT_TO_PHY_OP_LOCAL_IS_MANDATORY, &gport_info));
    local_port = gport_info.local_port;

    SHR_IF_ERR_EXIT(dnx_algo_port_info_get(unit, local_port, &port_info));
    if (!DNX_ALGO_PORT_TYPE_IS_PP_DSP(unit, port_info))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Port without pp_dsp!\n");
    }

    SHR_IF_ERR_EXIT(dnx_port_sit_coe_enable_get(unit, local_port, &coe_enable));
    if (coe_enable)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Port should not be COE \n");
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Set IPv6 path tracing interface ID (12b) for port
 */
static shr_error_e
dnx_instru_path_tracing_out_intf_id_set(
    int unit,
    uint32 flags,
    bcm_gport_t gport,
    int intf_id)
{
    uint16 intf_id_16 = (uint16) intf_id;
    SHR_FUNC_INIT_VARS(unit);

    /** verify */
    SHR_INVOKE_VERIFY_DNXC(dnx_instru_path_tracing_out_intf_verify(unit, flags, gport));
    if (intf_id > BCM_INSTRU_PATH_TRACING_OUT_INTF_ID_MAX)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "intf_id (%d) is out of range. Max value is %d", intf_id,
                     BCM_INSTRU_PATH_TRACING_OUT_INTF_ID_MAX);
    }

    SHR_IF_ERR_EXIT(dnx_port_sit_egress_port_set(unit, gport, NULL, NULL, NULL, &intf_id_16));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Get IPv6 path tracing interface ID (12b) for port
 */
static shr_error_e
dnx_instru_path_tracing_out_intf_id_get(
    int unit,
    uint32 flags,
    bcm_gport_t gport,
    int *intf_id_p)
{
    uint16 intf_id_16;
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(intf_id_p, _SHR_E_PARAM, "intf_id_p");

    /** verify */
    SHR_INVOKE_VERIFY_DNXC(dnx_instru_path_tracing_out_intf_verify(unit, flags, gport));

    SHR_IF_ERR_EXIT(dnx_port_sit_egress_port_get(unit, gport, NULL, NULL, NULL, &intf_id_16));

    *intf_id_p = intf_id_16;

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Set IPv6 path tracing interface load (4b) for port
 */
static shr_error_e
dnx_instru_path_tracing_out_intf_load_set(
    int unit,
    uint32 flags,
    bcm_gport_t gport,
    int intf_load)
{
    uint8 intf_load_8;
    uint8 load_msb;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * 3 msbs set on PCP, 1 lsb set on DEI 
     */
    intf_load_8 = intf_load & 1;
    load_msb = intf_load >> 1;

    /** verify */
    SHR_INVOKE_VERIFY_DNXC(dnx_instru_path_tracing_out_intf_verify(unit, flags, gport));
    if (intf_load > BCM_INSTRU_PATH_TRACING_OUT_INTF_LOAD_MAX)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "intf_load (%d) is out of range. Max value is %d", intf_load,
                     BCM_INSTRU_PATH_TRACING_OUT_INTF_LOAD_MAX);
    }

    SHR_IF_ERR_EXIT(dnx_port_sit_egress_port_set(unit, gport, NULL, &load_msb, &intf_load_8, NULL));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Get IPv6 path tracing interface load (4b) for port
 */
static shr_error_e
dnx_instru_path_tracing_out_intf_load_get(
    int unit,
    uint32 flags,
    bcm_gport_t gport,
    int *intf_load_p)
{
    uint8 intf_load_8;
    uint8 load_msb;

    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(intf_load_p, _SHR_E_PARAM, "intf_load_p");

    /** verify */
    SHR_INVOKE_VERIFY_DNXC(dnx_instru_path_tracing_out_intf_verify(unit, flags, gport));

    SHR_IF_ERR_EXIT(dnx_port_sit_egress_port_get(unit, gport, NULL, &load_msb, &intf_load_8, NULL));

    /*
     * 3 msbs set on PCP, 1 lsb set on DEI 
     */
    intf_load_8 |= (load_msb << 1);
    *intf_load_p = intf_load_8;

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Set IPv6 path tracing time template (1b) for port
 */
static shr_error_e
dnx_instru_path_tracing_time_template_set(
    int unit,
    uint32 flags,
    bcm_gport_t gport,
    int template)
{
    uint32 entry_handle_id;
    dnx_algo_gpm_gport_phy_info_t gport_info;
    bcm_port_t local_port;
    int pp_dsp;
    bcm_core_t core;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** verify */
    SHR_INVOKE_VERIFY_DNXC(dnx_instru_path_tracing_out_intf_verify(unit, flags, gport));
    if (template > BCM_INSTRU_PATH_TRACING_TIME_TEMPLATE_MAX)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "time template (%d) is out of range. Max value is %d", template,
                     BCM_INSTRU_PATH_TRACING_TIME_TEMPLATE_MAX);
    }

    /** Get pp_dsp and core-id first. */
    SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get
                    (unit, gport, DNX_ALGO_GPM_GPORT_TO_PHY_OP_LOCAL_IS_MANDATORY, &gport_info));
    /*
     * Write default values to DBAL_TABLE_EGRESS_PP_DSP table
     */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_PP_DSP, &entry_handle_id));
    if ((gport_info.flags & DNX_ALGO_GPM_GPORT_INFO_F_IS_LOCAL_PORT) != 0)
    {
        BCM_PBMP_ITER(gport_info.local_port_bmp, local_port)
        {
            SHR_IF_ERR_EXIT(dnx_port_pp_dsp_get(unit, local_port, &pp_dsp, &core));
            dbal_entry_key_field16_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core);
            dbal_entry_key_field16_set(unit, entry_handle_id, DBAL_FIELD_PP_DSP, pp_dsp);
            dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_TTL_MODEL, INST_SINGLE, template);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
        }
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Get IPv6 path tracing time template (1b) for port
 */
static shr_error_e
dnx_instru_path_tracing_time_template_get(
    int unit,
    uint32 flags,
    bcm_gport_t gport,
    int *template)
{
    uint32 entry_handle_id;
    dnx_algo_gpm_gport_phy_info_t gport_info;
    int pp_dsp;
    bcm_core_t core;
    uint8 template_8 = 0;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** verify */
    SHR_INVOKE_VERIFY_DNXC(dnx_instru_path_tracing_out_intf_verify(unit, flags, gport));

    /** Get pp_dsp and core-id first. */
    SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get
                    (unit, gport, DNX_ALGO_GPM_GPORT_TO_PHY_OP_LOCAL_IS_MANDATORY, &gport_info));

    /** Get pp-port and core-id first. */
    SHR_IF_ERR_EXIT(dnx_port_pp_dsp_get(unit, gport_info.local_port, &pp_dsp, &core));

    /*
     * Write default values to DBAL_TABLE_EGRESS_PP_DSP table
     */
    if ((gport_info.flags & DNX_ALGO_GPM_GPORT_INFO_F_IS_LOCAL_PORT) != 0)
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_PP_DSP, &entry_handle_id));
        dbal_entry_key_field16_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core);
        dbal_entry_key_field16_set(unit, entry_handle_id, DBAL_FIELD_PP_DSP, pp_dsp);
        dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_TTL_MODEL, INST_SINGLE, &template_8);
        SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
    }

    *template = template_8;

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Set IPv6 path tracing time lsb offset for time template
 */
static shr_error_e
dnx_instru_path_tracing_time_lsb_offset_set(
    int unit,
    uint32 template,
    uint32 lsb_offset)
{
    uint32 entry_handle_id;
    uint32 msb_offset;
    dbal_fields_e dbal_field;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (template > BCM_INSTRU_PATH_TRACING_TIME_TEMPLATE_MAX)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "time template (%d) is out of range. Max value is %d", template,
                     BCM_INSTRU_PATH_TRACING_TIME_TEMPLATE_MAX);
    }
    if (lsb_offset > BCM_INSTRU_PATH_TRACING_TIME_LSB_OFFSET_MAX)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "time lsb offset (%d) is out of range. Max value is %d", lsb_offset,
                     BCM_INSTRU_PATH_TRACING_TIME_LSB_OFFSET_MAX);
    }
    if (lsb_offset < BCM_INSTRU_PATH_TRACING_TIME_LSB_OFFSET_MIN)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "time lsb offset (%d) is out of range. Min value is %d", lsb_offset,
                     BCM_INSTRU_PATH_TRACING_TIME_LSB_OFFSET_MIN);
    }

    /*
     * pemla configuration is msb offset on lower 26 bits of time stamp.
     * 26bits are: 1588 TOD [33:8]
     */
    msb_offset = 26 - lsb_offset;
    dbal_field = (template == 0) ? DBAL_FIELD_VALUE_OF_PROFILE_0 : DBAL_FIELD_VALUE_OF_PROFILE_1;
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_IPV6HBH_PT_TS_PROFILE, &entry_handle_id));
    dbal_entry_value_field32_set(unit, entry_handle_id, dbal_field, INST_SINGLE, msb_offset);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Get IPv6 path tracing time lsb offset for time template
 */
static shr_error_e
dnx_instru_path_tracing_time_lsb_offset_get(
    int unit,
    uint32 template,
    uint32 *lsb_offset)
{
    uint32 entry_handle_id;
    uint32 msb_offset;
    dbal_fields_e dbal_field;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (template > BCM_INSTRU_PATH_TRACING_TIME_TEMPLATE_MAX)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "time template (%d) is out of range. Max value is %d", template,
                     BCM_INSTRU_PATH_TRACING_TIME_TEMPLATE_MAX);
    }

    dbal_field = (template == 0) ? DBAL_FIELD_VALUE_OF_PROFILE_0 : DBAL_FIELD_VALUE_OF_PROFILE_1;
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_IPV6HBH_PT_TS_PROFILE, &entry_handle_id));
    dbal_value_field32_request(unit, entry_handle_id, dbal_field, INST_SINGLE, &msb_offset);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

    /*
     * pemla configuration is msb offset on lower 26 bits of time stamp.
     * 26bits are: 1588 TOD [33:8]
     */
    *lsb_offset = 26 - msb_offset;

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Generic API function used for configuring various general instrumentation controls
 *
 * Use cases:
 *
 * ** Use case: "IPT SWITCH ID"
 * Set Switch ID for IPT (INT/Tail-Edit) applications
 *  Parameters:
 *  - flags - 0
 *  - type - bcmInstruControlIptSwitchId
 *  - arg - switch id
 *
 * \param [in] unit -  Unit-ID
 * \param [in] flags - description per use case.
 * \param [in] type - description per use case.
 * \param [in] arg  - description per use case.
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_instru_control_set(
    int unit,
    uint32 flags,
    bcm_instru_control_t type,
    int arg)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    switch (type)
    {
        case bcmInstruControlIptSwitchId:
            SHR_IF_ERR_EXIT(dnx_instru_ipt_node_id_set(unit, arg));
            break;
        case bcmInstruControlVisMode:
        {
            /*
             * For VisMode arg is a mode and flags are not in use currently
             */
            bcm_instru_vis_mode_control_t mode = (bcm_instru_vis_mode_control_t) arg;
            SHR_IF_ERR_EXIT(dnx_visibility_mode_set(unit, mode));
            break;
        }
        case bcmInstruControlVisSampling:
            /*
             * For VisSampling flags is direction, arg is period
             */
            SHR_IF_ERR_EXIT(dnx_visibility_sampling_set(unit, flags, (uint32) arg));
            break;
        case bcmInstruControlSFlowSamplingRate:
            SHR_IF_ERR_EXIT(dnx_instru_sflow_sampling_rate_set(unit, arg));
            break;
        case bcmInstruControlSFlowAgentIPAddress:
            SHR_IF_ERR_EXIT(dnx_instru_sflow_agent_id_address_set(unit, (bcm_ip_t) arg));
            break;
        case bcmInstruControlSFlowUpTime:
            SHR_IF_ERR_EXIT(dnx_instru_sflow_uptime_set(unit, arg));
            break;
        case bcmInstruControlSFlowMyRouterASNumber:
            SHR_IF_ERR_EXIT(dnx_instru_sflow_myrouter_as_number_set(unit, arg));
            break;
        case bcmInstruControlIpFixSystemUpTime:
            SHR_IF_ERR_EXIT(dnx_instru_ipfix_system_up_time_set(unit, arg));
            break;
        case bcmInstruControlIpFixEventorId:
            SHR_IF_ERR_EXIT(dnx_instru_ipfix_eventor_id_set(unit, arg));
            break;
        case bcmInstruControlIpFixTemplateId:
            SHR_IF_ERR_EXIT(dnx_instru_ipfix_template_id_set(unit, arg));
            break;
        case bcmInstruControlIpFixTxTime:
        {
            SHR_IF_ERR_EXIT(dnx_instru_ipfix_tx_time_set(unit, arg));
        }
            break;
        case bcmInstruControlIpFixObservationDomain:
            SHR_IF_ERR_EXIT(dnx_instru_ipfix_observation_domain_set(unit, arg));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "bcm_dnx_instru_control_set - invalid type=%d\r\n", type);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Generic API function used for getting configuration of general instrumentation controls
 * For detailed description refer to \ref bcm_dnx_instru_control_set()
 *
 * \param [in] unit -  Unit-ID
 * \param [in] flags - description per use case.
 * \param [in] type - description per use case.
 * \param [out] arg  - description per use case.
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_instru_control_get(
    int unit,
    uint32 flags,
    bcm_instru_control_t type,
    int *arg)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    switch (type)
    {
        case bcmInstruControlIptSwitchId:
            SHR_IF_ERR_EXIT(dnx_instru_ipt_node_id_get(unit, arg));
            break;
        case bcmInstruControlVisMode:
        {
            /*
             * For VisMode arg is a pointer to the mode and flags are not in use currently
             */
            bcm_instru_vis_mode_control_t mode;
            SHR_IF_ERR_EXIT(dnx_visibility_mode_get(unit, &mode, TRUE));
            *arg = (int) mode;
            break;
        }
        case bcmInstruControlVisSampling:
            SHR_IF_ERR_EXIT(dnx_visibility_sampling_get(unit, flags, (uint32 *) arg));
            break;
        case bcmInstruControlSFlowSamplingRate:
            SHR_IF_ERR_EXIT(dnx_instru_sflow_sampling_rate_get(unit, arg));
            break;
        case bcmInstruControlSFlowAgentIPAddress:
            SHR_IF_ERR_EXIT(dnx_instru_sflow_agent_id_address_get(unit, (bcm_ip_t *) arg));
            break;
        case bcmInstruControlSFlowUpTime:
            SHR_IF_ERR_EXIT(dnx_instru_sflow_uptime_get(unit, arg));
            break;
        case bcmInstruControlSFlowMyRouterASNumber:
            SHR_IF_ERR_EXIT(dnx_instru_sflow_myrouter_as_number_get(unit, arg));
            break;
        case bcmInstruControlIpFixSystemUpTime:
            SHR_IF_ERR_EXIT(dnx_instru_ipfix_system_up_time_get(unit, arg));
            break;
        case bcmInstruControlIpFixEventorId:
            SHR_IF_ERR_EXIT(dnx_instru_ipfix_eventor_id_get(unit, arg));
            break;
        case bcmInstruControlIpFixTemplateId:
            SHR_IF_ERR_EXIT(dnx_instru_ipfix_template_id_get(unit, arg));
            break;
        case bcmInstruControlIpFixTxTime:
        {
            SHR_IF_ERR_EXIT(dnx_instru_ipfix_tx_time_get(unit, arg));
        }
            break;
        case bcmInstruControlIpFixObservationDomain:
            SHR_IF_ERR_EXIT(dnx_instru_ipfix_observation_domain_get(unit, arg));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "bcm_dnx_instru_control_get - invalid type=%d\r\n", type);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Generic API function used for getting configuration various of general instrumentation controls
 *
 * \param [in] unit -  Unit-ID
 * \param [in] flags - description per use case.
 * \param [in] key - description per use case.
 * \param [in] value  - description per use case.
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_instru_control_indexed_set(
    int unit,
    uint32 flags,
    bcm_instru_control_key_t key,
    bcm_instru_control_info_t value)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    switch (key.type)
    {
        case bcmInstruControlIPv6PathTracingTimeLsbOffset:
            SHR_IF_ERR_EXIT(dnx_instru_path_tracing_time_lsb_offset_set
                            (unit, (uint32) key.index, (uint32) value.value));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "bcm_dnx_instru_control_indexed_set - invalid type=%d\r\n", key.type);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Generic API function used for configuring various general instrumentation controls
 *
 * \param [in] unit -  Unit-ID
 * \param [in] flags - description per use case.
 * \param [in] key - description per use case.
 * \param [out] value  - description per use case.
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_instru_control_indexed_get(
    int unit,
    uint32 flags,
    bcm_instru_control_key_t key,
    bcm_instru_control_info_t * value)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    switch (key.type)
    {
        case bcmInstruControlIPv6PathTracingTimeLsbOffset:
            SHR_IF_ERR_EXIT(dnx_instru_path_tracing_time_lsb_offset_get
                            (unit, (uint32) key.index, (uint32 *) &value->value));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "bcm_dnx_instru_control_indexed_get - invalid type=%d\r\n", key.type);
    }

exit:
    SHR_FUNC_EXIT;
}
/**
 * \brief -
 * Generic API function used for configuring various per gport instrumentation controls
 *
 * Use cases:
 *
 * ** Use case: "Trace Probability"
 * Set trace probability
 *  Parameters:
 *  - flags - 0
 *  - gport - port to set probability for.
 *  - type - bcmInstruGportControlTraceProbability
 *  - arg - probability in units of one-tenth (for example arg=300 means 30% probability)
 *
 * \param [in] unit -  Unit-ID
 * \param [in] gport - description per use case.
 * \param [in] flags - description per use case.
 * \param [in] type - description per use case.
 * \param [in] arg  - description per use case.
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_instru_gport_control_set(
    int unit,
    bcm_gport_t gport,
    uint32 flags,
    bcm_instru_gport_control_t type,
    int arg)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    switch (type)
    {
        case bcmInstruGportControlTraceProbability:
            SHR_IF_ERR_EXIT(dnx_instru_trace_probability_set(unit, flags, gport, arg));
            break;
        case bcmInstruGportControlVisEnable:
            SHR_IF_ERR_EXIT(dnx_visibility_port_enable_set(unit, flags, gport, arg));
            break;
        case bcmInstruGportControlVisForce:
            SHR_IF_ERR_EXIT(dnx_visibility_port_force_set(unit, flags, gport, arg));
            break;
        case bcmInstruGportControlIptTrapToRcyEnable:
            SHR_IF_ERR_EXIT(dnx_instru_ipt_trap_to_rcy_set(unit, flags, gport, arg));
            break;
        case bcmInstruGportControlIfaInitiatorRcyEnable:
            SHR_IF_ERR_EXIT(dnx_instru_ifa_initiator_rcy_set(unit, flags, gport, arg));
            break;
        case bcmInstruGportControlIPv6PathTracingOutIntfID:
            SHR_IF_ERR_EXIT(dnx_instru_path_tracing_out_intf_id_set(unit, flags, gport, arg));
            break;
        case bcmInstruGportControlIPv6PathTracingOutIntfLoad:
            SHR_IF_ERR_EXIT(dnx_instru_path_tracing_out_intf_load_set(unit, flags, gport, arg));
            break;
        case bcmInstruGportControlIPv6PathTracingTimeTemplate:
            SHR_IF_ERR_EXIT(dnx_instru_path_tracing_time_template_set(unit, flags, gport, arg));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "bcm_dnx_instru_gport_control_set - invalid type=%d\r\n", type);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Generic API function used for getting configuration of per gport instrumentation controls
 * For detailed description refer to \ref bcm_dnx_instru_gport_control_set()
 *
 * \param [in] unit -  Unit-ID
 * \param [in] gport - description per use case.
 * \param [in] flags - description per use case.
 * \param [in] type - description per use case.
 * \param [out] arg  - description per use case.
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_instru_gport_control_get(
    int unit,
    bcm_gport_t gport,
    uint32 flags,
    bcm_instru_gport_control_t type,
    int *arg)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    switch (type)
    {
        case bcmInstruGportControlTraceProbability:
            SHR_IF_ERR_EXIT(dnx_instru_trace_probability_get(unit, flags, gport, arg));
            break;
        case bcmInstruGportControlVisEnable:
            SHR_IF_ERR_EXIT(dnx_visibility_port_enable_get(unit, flags, gport, arg));
            break;
        case bcmInstruGportControlVisForce:
            SHR_IF_ERR_EXIT(dnx_visibility_port_force_get(unit, flags, gport, arg));
            break;
        case bcmInstruGportControlIptTrapToRcyEnable:
            SHR_IF_ERR_EXIT(dnx_instru_ipt_trap_to_rcy_get(unit, flags, gport, arg));
            break;
        case bcmInstruGportControlIfaInitiatorRcyEnable:
            SHR_IF_ERR_EXIT(dnx_instru_ifa_initiator_rcy_get(unit, flags, gport, arg));
            break;
        case bcmInstruGportControlIPv6PathTracingOutIntfID:
            SHR_IF_ERR_EXIT(dnx_instru_path_tracing_out_intf_id_get(unit, flags, gport, arg));
            break;
        case bcmInstruGportControlIPv6PathTracingOutIntfLoad:
            SHR_IF_ERR_EXIT(dnx_instru_path_tracing_out_intf_load_get(unit, flags, gport, arg));
            break;
        case bcmInstruGportControlIPv6PathTracingTimeTemplate:
            SHR_IF_ERR_EXIT(dnx_instru_path_tracing_time_template_get(unit, flags, gport, arg));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "bcm_dnx_instru_gport_control_get - invalid type=%d\r\n", type);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - set encap lif for IFA counting
 *
 * \param [in] unit - Relevant unit
 * \param [in] local_outlif - Local sFlow encap lif
 * \param [in] counter_type - the counter_type to be stamped on metadata.
 * \param [in] dbal_result_type - the EEDB SFLOW result type.
 *
 * \return
 *   shr_error_e, negative in case of an error.
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_instru_ifa_encap_eedb_write(
    int unit,
    int local_outlif,
    uint16 counter_type,
    uint32 dbal_result_type)
{
    uint32 entry_handle_id;
    uint32 entry_data[3];

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Take DBAL handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EEDB_SFLOW, &entry_handle_id));

    /** Set KEY field */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF, local_outlif);

    /** Set RESULT_TYPE field */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RESULT_TYPE, INST_SINGLE, dbal_result_type);

    switch (dbal_result_type)
    {
        case DBAL_RESULT_TYPE_EEDB_SFLOW_ETPS_SFLOW_EXT_SECOND:
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_LIF_SET, INST_SINGLE,
                                         INSTRU_IFA_OAM_LIF_SET);

            /*
             * Set entry raw data.
             * entry_data[0] : const 0.
             * entry_data[1] : const 0.
             * entry_data[2] : counter_type (MSBs).
             */
            entry_data[0] = 0;
            entry_data[1] = 0;
            entry_data[2] = counter_type << 24;

            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_INTERNAL,
                         "Error! Unsupported result type: dbal_result_type = %d. Supported result_type is: DBAL_RESULT_TYPE_EEDB_SFLOW_ETPS_SFLOW_EXT_SECOND = %d\n",
                         dbal_result_type, DBAL_RESULT_TYPE_EEDB_SFLOW_ETPS_SFLOW_EXT_SECOND);
        }
    }

    dbal_entry_value_field_arr32_set(unit, entry_handle_id, DBAL_FIELD_RAW_DATA, INST_SINGLE, entry_data);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Parameters verification function used for
 * bcm_dnx_instru_ifa_encap_create
 *
 * \param [in] unit -  Unit-ID
 * \param [in] ifa_info - ifa configuration structure
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
dnx_instru_ifa_encap_create_verify(
    int unit,
    bcm_instru_ifa_info_t * ifa_info)
{
    SHR_FUNC_INIT_VARS(unit);

    if ((ifa_info->flags & BCM_INSTRU_IFA_ENCAP_REPLACE) == BCM_INSTRU_IFA_ENCAP_REPLACE)
    {
        if (bcm_instru_ifa_encap_get(unit, ifa_info) == _SHR_E_NOT_FOUND)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "REPLACE flag must be used on existing IFA entity.\n");
        }
    }

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Allocate out-lif and add oam entry for counting IFA packets
 *
 * \param [in] unit -  Unit-ID
 * \param [in] ifa_info - ifa configuration structure
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
dnx_instru_ifa_encap_create(
    int unit,
    bcm_instru_ifa_info_t * ifa_info)
{
    uint32 entry_handle_id;
    int local_out_lif;
    lif_mngr_local_outlif_info_t outlif_info;
    lif_mngr_global_lif_info_t global_lif_info = { 0 };
    int lif_alloc_flags = 0;
    uint32 result_type;
    int ifa_metadata_counter_type;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /*
     * Counter Type = 0
     */
    ifa_metadata_counter_type = 0;

    result_type = DBAL_RESULT_TYPE_EEDB_SFLOW_ETPS_SFLOW_EXT_SECOND;
    /*
     * Allocate LIF for IFA encap entry.
     */
    if (_SHR_IS_FLAG_SET(ifa_info->flags, BCM_INSTRU_IFA_ENCAP_WITH_ID))
    {
        /*
         * If WITH_ID flag is used - get the global out-lif from the user input and
         * add alloc_with_id flag
         */
        global_lif_info.global_lif = ifa_info->ifa_encap_id;
        lif_alloc_flags |= LIF_MNGR_GLOBAL_LIF_WITH_ID;
    }
    sal_memset(&outlif_info, 0, sizeof(lif_mngr_local_outlif_info_t));
    outlif_info.dbal_table_id = DBAL_TABLE_EEDB_SFLOW;
    outlif_info.dbal_result_type = result_type;
    outlif_info.logical_phase = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_1;
    SHR_IF_ERR_EXIT(dnx_lif_lib_allocate(unit, lif_alloc_flags, &global_lif_info, NULL, &outlif_info));
    local_out_lif = outlif_info.local_outlif;

    /*
     * Return the allocated global lif
     */
    ifa_info->ifa_encap_id = global_lif_info.global_lif;

    /*
     * ETPS Configuration
     */
    SHR_IF_ERR_EXIT(dnx_instru_ifa_encap_eedb_write(unit, local_out_lif, ifa_metadata_counter_type, result_type));

    /*
     * Add entry to glem
     */
    if ((ifa_info->flags & BCM_INSTRU_IFA_ENCAP_REPLACE) != BCM_INSTRU_IFA_ENCAP_REPLACE)
    {
        SHR_IF_ERR_EXIT(dnx_lif_lib_add_to_glem(unit, _SHR_CORE_ALL, global_lif_info.global_lif, local_out_lif, TRUE));
    }

    /*
     ******************** */
    /*
     * Add OAM_LIF_DB entry
     */
    /*
     ******************** */

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_OAM_LIF_DB, &entry_handle_id));

    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_ZERO_PADDING, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_OAM_KEY_PREFIX, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_KEY_BASE, local_out_lif);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, DBAL_RANGE_ALL, DBAL_RANGE_ALL);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_COUNTER_BASE, INST_SINGLE, ifa_info->stat_cmd);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_COUNTER_INTERFACE, INST_SINGLE,
                                 ifa_info->counter_command_id);

    if ((ifa_info->flags & BCM_INSTRU_IFA_ENCAP_REPLACE) == BCM_INSTRU_IFA_ENCAP_REPLACE)
    {
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT_UPDATE));
    }
    else
    {
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Verify ifa encap is indeed exists and it is with the correct table/result_type/phase
 *
 * \param [in] unit -  Unit-ID
 * \param [in] ifa_encap_id - global lif
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_instru_ifa_encap_id_verify(
    int unit,
    int ifa_encap_id)
{
    dnx_algo_gpm_gport_hw_resources_t hw_res;
    bcm_gport_t encap_in_tunnel;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Turn the global lif into a tunnel, then call gport to hw resources.
     */
    sal_memset(&hw_res, 0, sizeof(dnx_algo_gpm_gport_hw_resources_t));
    BCM_GPORT_TUNNEL_ID_SET(encap_in_tunnel, ifa_encap_id);

    SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_to_hw_resources(unit, encap_in_tunnel,
                                                       DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_EGRESS, &hw_res));

    if ((hw_res.outlif_dbal_table_id != DBAL_TABLE_EEDB_SFLOW)
        || (hw_res.outlif_dbal_result_type != DBAL_RESULT_TYPE_EEDB_SFLOW_ETPS_SFLOW_EXT_SECOND)
        || (hw_res.logical_phase != DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_1))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "Error! IFA encap 0x%x is not of type IFA, table_id = %d, result_type = %d, logical_phase = %d\n",
                     ifa_encap_id, hw_res.outlif_dbal_table_id, hw_res.outlif_dbal_result_type, hw_res.logical_phase);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Verify ifa entity get/delete request
 *
 * \param [in] unit -  Unit-ID
 * \param [in] ifa_info - ifa configuration structure
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_instru_ifa_encap_get_delete_verify(
    int unit,
    bcm_instru_ifa_info_t * ifa_info)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(ifa_info, _SHR_E_PARAM, "ifa_info");

    SHR_IF_ERR_EXIT(dnx_instru_ifa_encap_id_verify(unit, ifa_info->ifa_encap_id));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Given an instru global lif, returns the local lif and it's result type.
 *
 * \param [in] unit -  Unit-ID
 * \param [in] ifa_encap_id - global lif
 * \param [out] local_lif - local lif associated with the given global_lif
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_instru_ifa_encap_id_to_local_lif(
    int unit,
    int ifa_encap_id,
    int *local_lif)
{
    dnx_algo_gpm_gport_hw_resources_t hw_res;
    bcm_gport_t encap_in_tunnel;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Turn the global lif into a tunnel, then call gport to hw resources.
     */
    sal_memset(&hw_res, 0, sizeof(dnx_algo_gpm_gport_hw_resources_t));
    BCM_GPORT_TUNNEL_ID_SET(encap_in_tunnel, ifa_encap_id);

    SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_to_hw_resources(unit, encap_in_tunnel,
                                                       DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_EGRESS, &hw_res));

    *local_lif = hw_res.local_out_lif;

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Clear ifa EEDB entry
 *
 * \param [in] unit - Relevant unit
 * \param [in] ifa_local_outlif - the ifa lif id, key to the dbal table
 *
 * \return
 *   shr_error_e, negative in case of an error.
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_instru_ifa_encap_clear(
    int unit,
    int ifa_local_outlif)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Take DBAL handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EEDB_SFLOW, &entry_handle_id));

    /** Set KEY field */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF, ifa_local_outlif);
    /** Set RESULT_TYPE field */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RESULT_TYPE, INST_SINGLE,
                                 DBAL_RESULT_TYPE_EEDB_SFLOW_ETPS_SFLOW_EXT_SECOND);

    /** Clear dbal entry */
    SHR_IF_ERR_EXIT(dbal_entry_clear(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * ifa lif delete
 *
 * \param [in] unit -  Unit-ID
 * \param [in] ifa_info - holds ifa_encap_id for the ifa entity to be deleted
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_instru_ifa_lif_delete(
    int unit,
    bcm_instru_ifa_info_t * ifa_info)
{
    int local_lif;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * get local_lif
     */
    SHR_IF_ERR_EXIT(dnx_instru_ifa_encap_id_to_local_lif(unit, ifa_info->ifa_encap_id, &local_lif));

    /** Remove global lif from GLEM */
    SHR_IF_ERR_EXIT(dnx_lif_lib_remove_from_glem(unit, _SHR_CORE_ALL, ifa_info->ifa_encap_id));

    /*
     * delete ifa encap entry
     */
    SHR_IF_ERR_EXIT(dnx_instru_ifa_encap_clear(unit, local_lif));

    /*
     * Delete global and local lifs.
     */
    SHR_IF_ERR_EXIT(dnx_lif_lib_free(unit, ifa_info->ifa_encap_id, NULL, local_lif));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Generic API function used for configuration of IFA
 * instrumentation.
 * \ref bcm_dnx_instru_ifa_encap_get()
 *      bcm_dnx_instru_ifa_encap_delete()
 *      bcm_dnx_instru_ifa_encap_traverse()
 *
 * \param [in] unit -  Unit-ID
 * \param [in] ifa_info -  ifa configuration structure
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   bcm_dnx_instru_ifa_encap_get
 *   bcm_dnx_instru_ifa_encap_delete
 *   bcm_dnx_instru_ifa_encap_traverse
 */
int
bcm_dnx_instru_ifa_encap_create(
    int unit,
    bcm_instru_ifa_info_t * ifa_info)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    if (!dnx_data_instru.ifa.ifa2_is_supported_get(unit))
    {
        return _SHR_E_UNAVAIL;
    }

    SHR_IF_ERR_EXIT(dnx_instru_ifa_encap_create_verify(unit, ifa_info));

    SHR_IF_ERR_EXIT(dnx_instru_ifa_encap_create(unit, ifa_info));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * API for deleting IFA 1.0 entity
 *
 * \param [in] unit -  Unit-ID
 * \param [in] ifa_info - ifa configuration structure
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   bcm_dnx_instru_ifa_encap_create
 *   bcm_dnx_instru_ifa_encap_get
 *   bcm_dnx_instru_ifa_encap_traverse
 */
int
bcm_dnx_instru_ifa_encap_delete(
    int unit,
    bcm_instru_ifa_info_t * ifa_info)
{
    uint32 entry_handle_id;
    int local_lif;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (!dnx_data_instru.ifa.ifa2_is_supported_get(unit))
    {
        return _SHR_E_UNAVAIL;
    }

    SHR_IF_ERR_EXIT(dnx_instru_ifa_encap_id_to_local_lif(unit, ifa_info->ifa_encap_id, &local_lif));

    SHR_IF_ERR_EXIT(dnx_instru_ifa_encap_get_delete_verify(unit, ifa_info));

    SHR_IF_ERR_EXIT(dnx_instru_ifa_lif_delete(unit, ifa_info));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_OAM_LIF_DB, &entry_handle_id));

    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_OAM_KEY_PREFIX, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_KEY_BASE, local_lif);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, _SHR_CORE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_OAM_KEY_PREFIX, DBAL_RANGE_ALL, DBAL_RANGE_ALL);

    SHR_IF_ERR_EXIT(dbal_entry_clear(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * API for getting IFA 1.0 entity info
 *
 * \param [in] unit -  Unit-ID
 * \param [in,out] ifa_info - ifa_encap_id should be supplied as
 *        input. Structure will contain all information as
 *        output
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   bcm_dnx_instru_ifa_encap_create
 *   bcm_dnx_instru_ifa_encap_delete
 *   bcm_dnx_instru_ifa_encap_traverse
 */
int
bcm_dnx_instru_ifa_encap_get(
    int unit,
    bcm_instru_ifa_info_t * ifa_info)
{
    uint32 entry_handle_id;
    uint8 counter_if;
    uint32 counter_index;
    int local_lif;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (!dnx_data_instru.ifa.ifa2_is_supported_get(unit))
    {
        return _SHR_E_UNAVAIL;
    }

    SHR_IF_ERR_EXIT(dnx_instru_ifa_encap_id_to_local_lif(unit, ifa_info->ifa_encap_id, &local_lif));

    SHR_IF_ERR_EXIT(dnx_instru_ifa_encap_get_delete_verify(unit, ifa_info));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_OAM_LIF_DB, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_KEY_BASE, local_lif);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_KEY_PREFIX, 0);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, 0);

    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_OAM_COUNTER_BASE, INST_SINGLE, &counter_index);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_COUNTER_INTERFACE, INST_SINGLE, &counter_if);
    ifa_info->stat_cmd = counter_index;
    ifa_info->counter_command_id = counter_if;

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * API for traversing IFA 1.0 entity
 *
 * \param [in] unit -  Unit-ID
 * \param [in] cb - Call back function
 * \param [in] user_data - Pointer to user data structure
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   bcm_dnx_instru_ifa_encap_create
 *   bcm_dnx_instru_ifa_encap_get
 *   bcm_dnx_instru_ifa_encap_delete
 */
int
bcm_dnx_instru_ifa_encap_traverse(
    int unit,
    bcm_instru_ifa_encap_traverse_cb cb,
    void *user_data)
{
    uint32 entry_handle_id;
    int is_end = 0;
    bcm_instru_ifa_info_t ifa_info;
    uint32 field_value[3];
    uint8 counter_if;
    uint32 counter_index;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (!dnx_data_instru.ifa.ifa2_is_supported_get(unit))
    {
        return _SHR_E_UNAVAIL;
    }

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_OAM_LIF_DB, &entry_handle_id));
    SHR_IF_ERR_EXIT(dbal_iterator_init(unit, entry_handle_id, DBAL_ITER_MODE_ALL));

    SHR_IF_ERR_EXIT(dbal_iterator_get_next(unit, entry_handle_id, &is_end));
    while (!is_end)
    {
        /*
         * Receive key and value fields of the entry.
         */
        SHR_IF_ERR_EXIT(dbal_entry_handle_key_field_arr32_get(unit, entry_handle_id, DBAL_FIELD_OAM_KEY_BASE,
                                                              field_value));
        ifa_info.ifa_encap_id = field_value[0];

        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                        (unit, entry_handle_id, DBAL_FIELD_OAM_COUNTER_BASE, INST_SINGLE, &counter_index));
        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field8_get
                        (unit, entry_handle_id, DBAL_FIELD_COUNTER_INTERFACE, INST_SINGLE, &counter_if));
        ifa_info.stat_cmd = counter_index;
        ifa_info.counter_command_id = counter_if;

        /*
         * If user provided a name of the callback function, it will be invoked with sending the ifa_info structure
         * of the entry that was found.
         */
        if (cb != NULL)
        {
            /*
             * Invoke callback function
             */
            SHR_IF_ERR_EXIT((*cb) (unit, &ifa_info, user_data));
        }
        else
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Wrong callback function was provided");
        }
        /*
         * Receive next entry in table.
         */
        SHR_IF_ERR_EXIT(dbal_iterator_get_next(unit, entry_handle_id, &is_end));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 * Verify ifit parameters for BCM-API: bcm_dnx_instru_ifit_encap_create().
 * check the supported flags
 */
static shr_error_e
dnx_instru_ifit_encap_create_verify(
    int unit,
    bcm_instru_ifit_encap_info_t * ifit_encap_info)
{
    int global_out_lif;
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(ifit_encap_info, _SHR_E_PARAM, "ifit_encap_info");

    /** Verify WITH_ID and REPLACE flags */
    if (_SHR_IS_FLAG_SET(ifit_encap_info->flags, BCM_INSTRU_IFIT_ENCAP_REPLACE)
        && !_SHR_IS_FLAG_SET(ifit_encap_info->flags, BCM_INSTRU_IFIT_ENCAP_WITH_ID))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "BCM_INSTRU_IFIT_ENCAP_REPLACE can't be used without BCM_INSTRU_IFIT_ENCAP_WITH_ID");
    }

    if (_SHR_IS_FLAG_SET(ifit_encap_info->flags, BCM_INSTRU_IFIT_ENCAP_WITH_ID))
    {
        global_out_lif = BCM_L3_ITF_VAL_GET(ifit_encap_info->ifit_encap_id);
        if (global_out_lif >= dnx_data_lif.global_lif.nof_global_out_lifs_get(unit) || global_out_lif < 0)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "ifit_encap_info->ifit_encap_id(%d) is out of range with BCM_INSTRU_IFIT_ENCAP_WITH_ID!",
                         ifit_encap_info->ifit_encap_id);
        }
    }

    if (ifit_encap_info->fieh_length > BCM_INSTRU_IFIT_ENCAP_FIEH_EXT_DATA_MAX)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "FIEH length range is  0-%d\n", BCM_INSTRU_IFIT_ENCAP_FIEH_EXT_DATA_MAX);
    }

    if (!DNX_MPLS_LABEL_IN_RANGE(unit, ifit_encap_info->fih_flow_id))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Flow ID (%d) is out of range. The range should be 0 - %d",
                     ifit_encap_info->fih_flow_id, DNX_MPLS_LABEL_MAX(unit));
    }

    if (ifit_encap_info->fih_r_s_bits != 1)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "R_S_BITS (%d) must be 1.", ifit_encap_info->fih_r_s_bits);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 * Write to IFIT entry into EEDB table.
 *
 *   \param [in] unit - Relevant unit.
 *   \param [in] ifit_encap_info - A pointer to the struct that holds
 *     information for the IFIT entry
 *   \param [in] local_outlif -
 *     Local-Out-LIF whose entry should be added to out-LIF table.
 */
static shr_error_e
dnx_instru_ifit_encap_table_set(
    int unit,
    bcm_instru_ifit_encap_info_t * ifit_encap_info,
    uint32 local_outlif)
{
    uint32 entry_handle_id;
    uint32 fih_data = 0;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(ifit_encap_info, _SHR_E_PARAM, "ifit_encap_info");

    /** Take DBAL handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EEDB_MPLS_IFIT, &entry_handle_id));

    /** Set KEY field */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF, local_outlif);

    /** Set DATA fields */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RESULT_TYPE, INST_SINGLE,
                                 DBAL_RESULT_TYPE_EEDB_MPLS_IFIT_ETPS_MPLS_IFIT);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FIH_TYPE, INST_SINGLE, ifit_encap_info->fieh_length);

    /** FII header*/
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FII_TC, INST_SINGLE, ifit_encap_info->fii_exp);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FII_TTL, INST_SINGLE, ifit_encap_info->fii_ttl);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FII_BOS, INST_SINGLE, TRUE);

    /** FIH header*/
    fih_data =
        ifit_encap_info->fih_flow_id << 12 | ifit_encap_info->
        fih_r_s_bits << 8 | ifit_encap_info->fih_header_type_indicator;
    if (_SHR_IS_FLAG_SET(ifit_encap_info->flags, BCM_INSTRU_IFIT_ENCAP_ALTERNATE_MARKING_LOSS_SET))
    {
        fih_data |= 1 << 11;    /* L bit */
    }

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FLOW_ID_BASIC, INST_SINGLE, fih_data);

    /** FIEH header*/

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FLOW_ID_EXT, INST_SINGLE,
                                 ifit_encap_info->fieh_ext_data[0]);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DIP_MASK, INST_SINGLE,
                                 ifit_encap_info->fieh_ext_data[1] >> 24);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SIP_MASK, INST_SINGLE,
                                 (ifit_encap_info->fieh_ext_data[1] >> 16) & 0xFF);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FIEH_EXT_DATA, INST_SINGLE,
                                 ifit_encap_info->fieh_ext_data[2] >> 16);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_REMARK_PROFILE, INST_SINGLE,
                                 DNX_QOS_MAP_PROFILE_GET(ifit_encap_info->qos_map_id));

    /** Write to HW */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 * Reset given entry from IFIT EEDB table.
 *
 *   \param [in] unit - Relevant unit.
 *   \param [in] local_outlif -
 *     Local-Out-LIF whose entry should be reset.
 */
static shr_error_e
dnx_instru_ifit_encap_table_clear(
    int unit,
    uint32 local_outlif)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EEDB_MPLS_IFIT, &entry_handle_id));

    /** Setting key fields -- DBAL_RESULT_TYPE_EEDB_MPLS_IFIT */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF, local_outlif);

    /** Setting result type */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RESULT_TYPE, INST_SINGLE,
                                 DBAL_RESULT_TYPE_EEDB_MPLS_IFIT_ETPS_MPLS_IFIT);

    /** clearing the entry */
    SHR_IF_ERR_EXIT(dbal_entry_clear(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 * Read from IFIT entry EEDB table.
 *
 *   \param [in] unit - Relevant unit.
 *   \param [out] ifit_encap_info - A pointer to the struct that holds
 *     information for the IFIT encapsulation entry
 *   \param [in] local_outlif -
 *     Local-Out-LIF whose entry should be returned.
 */
static shr_error_e
dnx_instru_ifit_encap_table_get(
    int unit,
    bcm_instru_ifit_encap_info_t * ifit_encap_info,
    uint32 local_outlif)
{
    uint32 entry_handle_id;
    uint32 fih_data = 0;
    uint8 dip_mask = 0, sip_mask = 0;
    uint32 fieh_ext_data = 0, field_val = 0;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(ifit_encap_info, _SHR_E_PARAM, "ifit_encap_info");

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EEDB_MPLS_IFIT, &entry_handle_id));

    /** Setting key fields -- DBAL_RESULT_TYPE_EEDB_MPLS_IFIT */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF, local_outlif);

    /** Setting result type */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RESULT_TYPE, INST_SINGLE,
                                 DBAL_RESULT_TYPE_EEDB_MPLS_IFIT_ETPS_MPLS_IFIT);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));

    /**
     * Get egress encapsulation data from dbal table
     */

    /** FII header*/
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field8_get
                    (unit, entry_handle_id, DBAL_FIELD_FII_TC, INST_SINGLE, &ifit_encap_info->fii_exp));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field8_get
                    (unit, entry_handle_id, DBAL_FIELD_FII_TTL, INST_SINGLE, &ifit_encap_info->fii_ttl));

    /** FIH header*/
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                    (unit, entry_handle_id, DBAL_FIELD_FLOW_ID_BASIC, INST_SINGLE, &fih_data));

    ifit_encap_info->fih_flow_id = fih_data >> 12;
    ifit_encap_info->fih_r_s_bits = (fih_data >> 8) & 0x3;;
    ifit_encap_info->fih_header_type_indicator = fih_data & 0xFF;
    ifit_encap_info->flags |= ((fih_data >> 11) & 1) ? BCM_INSTRU_IFIT_ENCAP_ALTERNATE_MARKING_LOSS_SET : 0;

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field8_get
                    (unit, entry_handle_id, DBAL_FIELD_FIH_TYPE, INST_SINGLE, &ifit_encap_info->fieh_length));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                    (unit, entry_handle_id, DBAL_FIELD_FLOW_ID_EXT, INST_SINGLE, &ifit_encap_info->fieh_ext_data[0]));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field8_get
                    (unit, entry_handle_id, DBAL_FIELD_DIP_MASK, INST_SINGLE, &dip_mask));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field8_get
                    (unit, entry_handle_id, DBAL_FIELD_SIP_MASK, INST_SINGLE, &sip_mask));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                    (unit, entry_handle_id, DBAL_FIELD_FIEH_EXT_DATA, INST_SINGLE, &fieh_ext_data));

    ifit_encap_info->fieh_ext_data[1] |= (dip_mask << 24) | (sip_mask << 16);
    ifit_encap_info->fieh_ext_data[2] |= fieh_ext_data << 16;

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                    (unit, entry_handle_id, DBAL_FIELD_REMARK_PROFILE, INST_SINGLE, &field_val));

    ifit_encap_info->qos_map_id = field_val;
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Generic API function used for configuration of IFIT
 * instrumentation.
 * \ref bcm_dnx_instru_ifit_encap_get()
 *      bcm_dnx_instru_ifit_encap_delete()
 *      bcm_dnx_instru_ifit_encap_traverse()
 *
 * \param [in] unit -  Unit-ID
 * \param [in] ifit_encap_info -  ifit configuration structure
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   bcm_dnx_instru_ifit_encap_get
 *   bcm_dnx_instru_ifit_encap_delete
 *   bcm_dnx_instru_ifit_encap_traverse
 */
int
bcm_dnx_instru_ifit_encap_create(
    int unit,
    bcm_instru_ifit_encap_info_t * ifit_encap_info)
{
    dnx_algo_gpm_gport_hw_resources_t gport_hw_resources;
    lif_mngr_local_outlif_info_t outlif_info;
    lif_mngr_global_lif_info_t global_lif_info = { 0 };
    int lif_alloc_flags = 0;
    int lif_get_flags = 0;
    bcm_gport_t gport;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    /** Verification of input parameters */
    SHR_INVOKE_VERIFY_DNXC(dnx_instru_ifit_encap_create_verify(unit, ifit_encap_info));
    sal_memset(&gport_hw_resources, 0, sizeof(dnx_algo_gpm_gport_hw_resources_t));

    /** WITH_ID flag is used - get global out-lif ID */
    if (_SHR_IS_FLAG_SET(ifit_encap_info->flags, BCM_INSTRU_IFIT_ENCAP_WITH_ID))
    {
        /** Add alloc_with_id flag */
        global_lif_info.global_lif = BCM_L3_ITF_VAL_GET(ifit_encap_info->ifit_encap_id);
        lif_alloc_flags |= LIF_MNGR_GLOBAL_LIF_WITH_ID;
    }

    /** Allocate new egr out-LIF - REPLACE flag is not set */
    if (!_SHR_IS_FLAG_SET(ifit_encap_info->flags, BCM_INSTRU_IFIT_ENCAP_REPLACE))
    {
        /** fill the local outlif info. */
        sal_memset(&outlif_info, 0, sizeof(lif_mngr_local_outlif_info_t));
        outlif_info.dbal_table_id = DBAL_TABLE_EEDB_MPLS_IFIT;
        outlif_info.logical_phase = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_1;
        /** Allocate LIF - WITH_ID if the flag was set */
        SHR_IF_ERR_EXIT(dnx_lif_lib_allocate(unit, lif_alloc_flags, &global_lif_info, NULL, &outlif_info));
        /** update returned Encap ID's */
        BCM_L3_ITF_SET(ifit_encap_info->ifit_encap_id, BCM_L3_ITF_TYPE_LIF, global_lif_info.global_lif);
        /** Add entry to out-LIF table */
        SHR_IF_ERR_EXIT(dnx_instru_ifit_encap_table_set(unit, ifit_encap_info, outlif_info.local_outlif));
        /** Write global to local LIF mapping to GLEM. */
        SHR_IF_ERR_EXIT(dnx_lif_lib_add_to_glem
                        (unit, _SHR_CORE_ALL, global_lif_info.global_lif, outlif_info.local_outlif, TRUE));
    }

    /** Replace existing out-LIF */
    else
    {
        /** get GPort HW resources (global and local tunnel outlif) */
        lif_get_flags =
            DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_EGRESS | DNX_ALGO_GPM_GPORT_HW_RESOURCES_GLOBAL_LIF_EGRESS;

        BCM_L3_ITF_LIF_TO_GPORT_TUNNEL(gport, ifit_encap_info->ifit_encap_id);

        /** we don't have gport here, so we're using gport tunnel */
        SHR_IF_ERR_REPLACE_AND_EXIT(dnx_algo_gpm_gport_to_hw_resources(unit, gport, lif_get_flags, &gport_hw_resources),
                                    _SHR_E_NOT_FOUND, _SHR_E_PARAM);

        /** Check that eep is an index of a RCH OutLIF (in SW DB) */
        if (gport_hw_resources.outlif_dbal_table_id != DBAL_TABLE_EEDB_MPLS_IFIT)
        {
            SHR_ERR_EXIT(_SHR_E_NOT_FOUND, "Illegal to replace non IFIT OutLIF to IFIT OutLIF");
        }
        /** Add entry to out-LIF table */
        SHR_IF_ERR_EXIT(dnx_instru_ifit_encap_table_set(unit, ifit_encap_info, gport_hw_resources.local_out_lif));

    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;

}

/**
 * \brief -
 * API for deleting IFIT entity
 *
 * \param [in] unit -  Unit-ID
 * \param [in] ifit_encap_info - ifit configuration structure
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   bcm_dnx_instru_ifit_encap_create
 *   bcm_dnx_instru_ifit_encap_get
 *   bcm_dnx_instru_ifit_encap_traverse
 */
int
bcm_dnx_instru_ifit_encap_delete(
    int unit,
    bcm_instru_ifit_encap_info_t * ifit_encap_info)
{
    dnx_algo_gpm_gport_hw_resources_t gport_hw_resources;
    bcm_gport_t gport;
    uint32 flags;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    /** Get local outlif from he resources */
    BCM_L3_ITF_LIF_TO_GPORT_TUNNEL(gport, ifit_encap_info->ifit_encap_id);

    flags = DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_EGRESS | DNX_ALGO_GPM_GPORT_HW_RESOURCES_GLOBAL_LIF_EGRESS;
    SHR_IF_ERR_REPLACE_AND_EXIT(dnx_algo_gpm_gport_to_hw_resources(unit, gport, flags, &gport_hw_resources),
                                _SHR_E_NOT_FOUND, _SHR_E_PARAM);

    /** Clear --- table values */
    SHR_IF_ERR_EXIT(dnx_instru_ifit_encap_table_clear(unit, gport_hw_resources.local_out_lif));

    /** Remove global to local LIF mapping from GLEM. core-Id=0 until bcm_dnx_l2_egress_create is fixed */
    SHR_IF_ERR_EXIT(dnx_lif_lib_remove_from_glem(unit, _SHR_CORE_ALL, gport_hw_resources.global_out_lif));

    /** Free LIF */
    SHR_IF_ERR_EXIT(dnx_lif_lib_free(unit, gport_hw_resources.global_out_lif, NULL, gport_hw_resources.local_out_lif));

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * API for getting IFIT entity info
 *
 * \param [in] unit -  Unit-ID
 * \param [in,out] ifit_encap_info - ifit_encap_id should be supplied as
 *        input. Structure will contain all information as
 *        output
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   bcm_dnx_instru_ifit_encap_create
 *   bcm_dnx_instru_ifit_encap_delete
 *   bcm_dnx_instru_ifit_encap_traverse
 */
int
bcm_dnx_instru_ifit_encap_get(
    int unit,
    bcm_instru_ifit_encap_info_t * ifit_encap_info)
{
    dnx_algo_gpm_gport_hw_resources_t gport_hw_resources;
    bcm_gport_t gport;
    uint32 flags;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    /** Get local outlif from he resources */
    BCM_L3_ITF_LIF_TO_GPORT_TUNNEL(gport, ifit_encap_info->ifit_encap_id);

    flags = DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_EGRESS | DNX_ALGO_GPM_GPORT_HW_RESOURCES_GLOBAL_LIF_EGRESS;
    SHR_IF_ERR_REPLACE_AND_EXIT(dnx_algo_gpm_gport_to_hw_resources(unit, gport, flags, &gport_hw_resources),
                                _SHR_E_NOT_FOUND, _SHR_E_PARAM);

    /** Set return values in ifit_encap_info */
    SHR_IF_ERR_EXIT(dnx_instru_ifit_encap_table_get(unit, ifit_encap_info, gport_hw_resources.local_out_lif));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * API for traversing IFIT entity
 *
 * \param [in] unit -  Unit-ID
 * \param [in] cb - Call back function
 * \param [in] user_data - Pointer to user data structure
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   bcm_dnx_instru_ifit_encap_create
 *   bcm_dnx_instru_ifit_encap_get
 *   bcm_dnx_instru_ifit_encap_delete
 */
int
bcm_dnx_instru_ifit_encap_traverse(
    int unit,
    bcm_instru_ifit_encap_traverse_cb cb,
    void *user_data)
{
    uint32 entry_handle_id;
    int is_end = 0;
    uint32 local_out_lif = 0;
    bcm_gport_t tunnel_gport;
    bcm_instru_ifit_encap_info_t ifit_encap_info;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);
    DBAL_FUNC_INIT_VARS(unit);

    sal_memset(&ifit_encap_info, 0, sizeof(ifit_encap_info));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EEDB_MPLS_IFIT, &entry_handle_id));
    SHR_IF_ERR_EXIT(dbal_iterator_init(unit, entry_handle_id, DBAL_ITER_MODE_ALL));

    SHR_IF_ERR_EXIT(dbal_iterator_get_next(unit, entry_handle_id, &is_end));
    while (!is_end)
    {

        SHR_IF_ERR_EXIT(dbal_entry_handle_key_field_arr32_get
                        (unit, entry_handle_id, DBAL_FIELD_OUT_LIF, &local_out_lif));
        SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_from_lif(unit,
                                                    DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_EGRESS,
                                                    BCM_CORE_ALL, local_out_lif, &tunnel_gport));
        BCM_GPORT_TUNNEL_TO_L3_ITF_LIF(ifit_encap_info.ifit_encap_id, tunnel_gport);

        /*
         * If user provided a name of the callback function, it will be invoked with sending the ifit_encap_info structure
         * of the entry that was found.
         */

        /*
         * Get IFIT entry information.
         */
        SHR_IF_ERR_EXIT(dnx_instru_ifit_encap_table_get(unit, &ifit_encap_info, local_out_lif));

        if (cb != NULL)
        {
            /*
             * Invoke callback function
             */
            SHR_IF_ERR_EXIT((*cb) (unit, &ifit_encap_info, user_data));
        }
        else
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Wrong callback function was provided");
        }
        /*
         * Receive next entry in table.
         */
        SHR_IF_ERR_EXIT(dbal_iterator_get_next(unit, entry_handle_id, &is_end));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;

}

/**
 * \brief -
 * Verify the validity of the sync counters DNX data.
 *
 * \param [in] unit -  Unit-ID
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
static int
dnx_instru_synced_counters_time_ratio_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (dnx_data_instru.synced_counters.period_adjusted_to_ns_through_time_ratio_get(unit))
    {
        uint32 dbal_handle_id;
        uint32 nof_clocks;
        uint32 nof_ns;
        uint32 clock_freq_khz;
        int current_value_correct;
        uint64 freqkhztimestimens;
        uint64 freqtimestime_converted;
        uint64 freqtimestime_converted_back;
        uint32 unitconversion;
        int64 nof_clocks_uint64;

        current_value_correct = FALSE;

        clock_freq_khz = dnx_data_device.general.core_clock_khz_get(unit);

        if (clock_freq_khz == 0)
        {
            SHR_ERR_EXIT(_SHR_E_CONFIG, "Error, unexpected zero value for clock frequency.\n");
        }

        /** Create the unitconversion constant, 1000000000 for second to nanosecond divided by 1000 for KHz->Hz.*/
        unitconversion = 1000000000 / 1000;

        /*
         * Get the old values and check if they fit.
         */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INST_SYNCED_COUNTERS_CLK_TIME_RATIO, &dbal_handle_id));
        dbal_value_field32_request(unit, dbal_handle_id, DBAL_FIELD_NOF_CLOCK_CYCLES, INST_SINGLE, &nof_clocks);
        dbal_value_field32_request(unit, dbal_handle_id, DBAL_FIELD_NOF_NANOSECONDS, INST_SINGLE, &nof_ns);
        SHR_IF_ERR_EXIT(dbal_entry_get(unit, dbal_handle_id, DBAL_COMMIT));

        if (nof_ns != 0 && nof_clocks != 0)
        {
            /** Get freq [KHZ] times time [ns].*/
            COMPILER_64_SET(freqkhztimestimens, 0, clock_freq_khz);
            COMPILER_64_UMUL_32(freqkhztimestimens, nof_ns);

            /*
             * Reduce the conversion.
             * Note we do not have modulo/remainder in COMPILER_64,
             * so we will check divisibility using comparing after division and multiplication.
             */
            COMPILER_64_COPY(freqtimestime_converted, freqkhztimestimens);
            COMPILER_64_UDIV_32(freqtimestime_converted, unitconversion);
            COMPILER_64_COPY(freqtimestime_converted_back, freqtimestime_converted);
            COMPILER_64_UMUL_32(freqtimestime_converted_back, unitconversion);
            if (COMPILER_64_EQ(freqtimestime_converted_back, freqkhztimestimens))
            {
                COMPILER_64_SET(nof_clocks_uint64, 0, nof_clocks);
                if (COMPILER_64_EQ(nof_clocks_uint64, freqtimestime_converted))
                {
                    current_value_correct = TRUE;
                }
            }
        }

        if (current_value_correct)
        {
            LOG_DEBUG_EX(BSL_LOG_MODULE, "nof_clocks %d and nof_ns %d do match clock rate %d KHz.%s\r\n",
                         nof_clocks, nof_ns, clock_freq_khz, EMPTY);
        }
        else
        {
            /*
             * Find corrects adjustments if the current values are incorrect.
             */
            uint32 nof_clk_mask = SAL_UPTO_BIT(dnx_data_instru.synced_counters.period_adjusting_clk_bits_get(unit));
            uint32 nof_ns_max = SAL_UPTO_BIT(dnx_data_instru.synced_counters.period_adjusting_ns_bits_get(unit));
            int found = FALSE;
            LOG_DEBUG_EX(BSL_LOG_MODULE, "nof_clocks %d and nof_ns %d do not match clock rate %d KHz. "
                         "Recalculating.%s\r\n", nof_clocks, nof_ns, clock_freq_khz, EMPTY);
            for (nof_ns = 1; nof_ns <= nof_ns_max; nof_ns++)
            {
                COMPILER_64_SET(freqkhztimestimens, 0, clock_freq_khz);
                COMPILER_64_UMUL_32(freqkhztimestimens, nof_ns);
                COMPILER_64_COPY(freqtimestime_converted, freqkhztimestimens);
                COMPILER_64_UDIV_32(freqtimestime_converted, unitconversion);
                COMPILER_64_COPY(freqtimestime_converted_back, freqtimestime_converted);
                COMPILER_64_UMUL_32(freqtimestime_converted_back, unitconversion);
                if (COMPILER_64_EQ(freqtimestime_converted_back, freqkhztimestimens))
                {
                    if ((COMPILER_64_HI(freqtimestime_converted) == 0) &&
                        ((COMPILER_64_LO(freqtimestime_converted) & (!nof_clk_mask)) == 0) &&
                        (freqtimestime_converted != 0))
                    {
                        nof_clocks = COMPILER_64_LO(freqtimestime_converted);
                        found = TRUE;
                        break;
                    }
                }
            }
            if (found)
            {
                dbal_entry_value_field32_set(unit, dbal_handle_id, DBAL_FIELD_NOF_CLOCK_CYCLES, INST_SINGLE,
                                             nof_clocks);
                dbal_entry_value_field32_set(unit, dbal_handle_id, DBAL_FIELD_NOF_NANOSECONDS, INST_SINGLE, nof_ns);
                SHR_IF_ERR_EXIT(dbal_entry_commit(unit, dbal_handle_id, DBAL_COMMIT));
                LOG_DEBUG_EX(BSL_LOG_MODULE,
                             "Adjusted to nof_clocks %d and nof_ns %d to match clock rate %d KHz.%s\r\n", nof_clocks,
                             nof_ns, clock_freq_khz, EMPTY);
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG, "Could not find adjustments to satisfy clock frequency of %d KHz\n",
                             clock_freq_khz);
            }
        }
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Initialize the synchronized counters SW state
 *
 * \param [in] unit -  Unit-ID
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
static int
dnx_instru_synced_counters_init(
    int unit)
{
    int core_index;
    int ethu_index;
    int nof_ethu_per_core;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Init the SW state.
     */
    SHR_IF_ERR_EXIT(instru_sync_counters.init(unit));
    SHR_IF_ERR_EXIT(instru_sync_counters.icgm_countes.per_core_info.alloc(unit));
    
    if (!soc_is(unit, J2X_DEVICE))
    {
        SHR_IF_ERR_EXIT(instru_sync_counters.nif_countes.per_ethu_info.alloc(unit));
        DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core_index)
        {
            SHR_IF_ERR_EXIT(dnx_algo_port_nif_ethu_nof_ethus_per_core_get(unit, core_index, &nof_ethu_per_core));
            for (ethu_index = 0; ethu_index < nof_ethu_per_core; ethu_index++)
            {
                SHR_IF_ERR_EXIT(instru_sync_counters.nif_countes.per_ethu_info.
                                record_last_read_nof.alloc(unit, core_index, ethu_index));
            }
        }

        SHR_IF_ERR_EXIT(imb_instru_traffic_counters_reset_all(unit));
    }

    /*
     * Adjust the time ration by clock frequency.
     */
    SHR_IF_ERR_EXIT(dnx_instru_synced_counters_time_ratio_init(unit));

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_instru_init(
    int unit)
{
    int system_headers_mode;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_instru.ifa.ifa2_is_in_hl_get(unit))
    {
    }
    else
    {
        system_headers_mode = dnx_data_headers.system_headers.system_headers_mode_get(unit);
        if (system_headers_mode == DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO2_MODE)
        {
          /** Init IPT (INT + Tail-Edit) */
            SHR_IF_ERR_EXIT(dnx_instru_ipt_init(unit));
        }
        /** Init synchronized counters */
        SHR_IF_ERR_EXIT(dnx_instru_synced_counters_init(unit));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Function to verify the input parameters of APIs:
 * - bcm_instru_synced_counters_config_set
 * - bcm_instru_synced_counters_config_get
 *
 * \param [in] unit -  Unit-ID
 * \param [in] flags -  Flags
 * \param [in] source_type -  Type of Synchronous Counters mechanism
 * \param [in] config -  Configuration structure for Synchronous Counters mechanism
 * \param [in] is_set -  indicates if the verify function was called from the "set" API
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
int
dnx_instru_synced_counters_config_verify(
    int unit,
    uint32 flags,
    bcm_instru_synced_counters_source_type_t source_type,
    bcm_instru_synced_counters_config_t * config,
    uint8 is_set)
{
    int interval_period_nof_bits_hw;
    int interval_period_nof_bits_maximum_usable = dnx_data_instru.synced_counters.max_interval_period_size_get(unit);
    int max_interval_period_nof_bits;
    uint64 interval_period_msb;
    uint64 immediate_start;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Verify input flags */
    if (flags & ~(BCM_INSTRU_SYNCED_COUNTERS_CONFIG_SKIP_TRIGGER))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported flags for synchronized triggers configuration: 0x%x\n", flags);
    }

    /** Verify input source type */
    if ((source_type != bcmInstruSyncedCountersTypeIcgm) && (source_type != bcmInstruSyncedCountersTypeNif))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported source type %d for synchronized counters configuration!\n",
                     source_type);
    }

    if (is_set == TRUE)
    {
        /** Verify input enable */
        SHR_BOOL_VERIFY(config->enable, _SHR_E_PARAM, "Invalid enable, must be TRUE or FALSE\n");
        if (config->enable == FALSE)
        {
            /** When disabling the instrumentation all other parameters are irrelevant */
            SHR_EXIT();
        }

        /** The below parameters are relevant only for trigger configurations */
        if (!(flags & BCM_INSTRU_SYNCED_COUNTERS_CONFIG_SKIP_TRIGGER))
        {
            /** Verify input start time */
            COMPILER_64_SET(immediate_start, -1, -1);
            if (COMPILER_64_NE(config->start_time, immediate_start))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported start time currently only immediate (-1) is supported!\n");
            }

            /*
             * Verify the size of the period does not exceed the maximum number of bits,
             * either the size in HW or the maximum usable size.
             * Also verify that the period isn't zero.
             */
            if (COMPILER_64_IS_ZERO(config->period))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Period cannot be zero.\n");
            }
            SHR_IF_ERR_EXIT(dbal_tables_field_size_get
                            (unit, DBAL_TABLE_INST_SYNCED_COUNTERS_CTRL, DBAL_FIELD_INTERVAL_PERIOD, FALSE, 0, 0,
                             &interval_period_nof_bits_hw));
            max_interval_period_nof_bits = (interval_period_nof_bits_hw < interval_period_nof_bits_maximum_usable) ?
                (interval_period_nof_bits_hw) : (interval_period_nof_bits_maximum_usable);
            COMPILER_64_COPY(interval_period_msb, config->period);
            COMPILER_64_SHR(interval_period_msb, max_interval_period_nof_bits);
            if (!COMPILER_64_IS_ZERO(interval_period_msb))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Period (%u,%u)is out of range, cannot be more than %u bits.\n",
                             COMPILER_64_HI(config->period), COMPILER_64_LO(config->period),
                             max_interval_period_nof_bits);
            }
        }

        /** Verify input is_eventor_collection */
        SHR_BOOL_VERIFY(config->is_eventor_collection, _SHR_E_PARAM,
                        "Invalid is_eventor_collection, must be TRUE or FALSE\n");
        /** Verify input is_continuous */
        SHR_BOOL_VERIFY(config->is_continuous, _SHR_E_PARAM, "Invalid is_continuous, must be TRUE or FALSE\n");
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Take the Synchronous Counters in and out of reset.
 *
 * \param [in] unit -  Unit-ID
 * \param [in] source_type -  Type of Synchronous Counters to reset
 * \param [in] reset - If TRUE, take the counters into reset. Else, take them out of reset
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_instru_synced_counters_hw_reset_set(
    int unit,
    bcm_instru_synced_counters_source_type_t source_type,
    uint8 reset)
{
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    switch (source_type)
    {
        case bcmInstruSyncedCountersTypeIcgm:
        {
            uint32 entry_handle_id_setting;
            SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC
                            (unit, DBAL_TABLE_INST_SYNCED_COUNTERS_SETTING_ICGM, &entry_handle_id_setting));
            dbal_entry_value_field8_set(unit, entry_handle_id_setting, DBAL_FIELD_SYNC_COUNTERS_INIT, INST_SINGLE,
                                        reset);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id_setting, DBAL_COMMIT));
            break;
        }
        case bcmInstruSyncedCountersTypeNif:
        {
            SHR_IF_ERR_EXIT(imb_instru_counters_reset_set_all(unit, reset));
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported source_type %d.\n", source_type);
        }
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Get the the Synchronous Counters reset status.
 *
 * \param [in] unit -  Unit-ID
 * \param [in] source_type -  Type of Synchronous Counters to reset
 * \param [out] reset - If TRUE, the counters are in reset. Else, they are out of reset
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_instru_synced_counters_hw_reset_get(
    int unit,
    bcm_instru_synced_counters_source_type_t source_type,
    uint8 *reset)
{
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    switch (source_type)
    {
        case bcmInstruSyncedCountersTypeIcgm:
        {
            uint32 entry_handle_id_setting;
            SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC
                            (unit, DBAL_TABLE_INST_SYNCED_COUNTERS_SETTING_ICGM, &entry_handle_id_setting));
            dbal_value_field8_request(unit, entry_handle_id_setting, DBAL_FIELD_SYNC_COUNTERS_INIT, INST_SINGLE, reset);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id_setting, DBAL_COMMIT));
            break;
        }
        case bcmInstruSyncedCountersTypeNif:
        {
            /** All IMBs are set to the same values, so just get the value for IMB 0 */
            SHR_IF_ERR_EXIT(imb_instru_counters_reset_get(unit, 0, reset));
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported source_type %d.\n", source_type);
        }
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -  Set Synced counters configuration to HW on the side receiving the pulse from the ECI.
 */
static shr_error_e
dnx_instru_synced_counters_config_hw_set(
    int unit,
    bcm_instru_synced_counters_source_type_t source_type,
    uint16 nof_intervals,
    uint8 is_continuous)
{
    uint32 nof_intervals_hw = nof_intervals - 1;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    switch (source_type)
    {
        case bcmInstruSyncedCountersTypeIcgm:
        {
            uint32 entry_handle_id_config;

            SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC
                            (unit, DBAL_TABLE_INST_SYNCED_COUNTERS_SETTING_ICGM, &entry_handle_id_config));
            dbal_entry_value_field8_set(unit, entry_handle_id_config, DBAL_FIELD_SYNC_COUNTERS_NOF_INTERVALS,
                                        INST_SINGLE, nof_intervals_hw);
            dbal_entry_value_field8_set(unit, entry_handle_id_config, DBAL_FIELD_IS_CONTINUOUS, INST_SINGLE,
                                        is_continuous);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id_config, DBAL_COMMIT));
            break;
        }
        case bcmInstruSyncedCountersTypeNif:
        {
            SHR_IF_ERR_EXIT(imb_instru_synced_counters_config_set_all(unit, nof_intervals_hw, is_continuous));
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported source_type %d.\n", source_type);
        }
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -  Get Synced counters configuration to HW on the side receiving the pulse from the ECI.
 */
static shr_error_e
dnx_instru_synced_counters_config_hw_get(
    int unit,
    bcm_instru_synced_counters_source_type_t source_type,
    uint8 *nof_intervals,
    uint8 *is_countinious)
{
    uint8 nof_intervals_hw;
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    switch (source_type)
    {
        case bcmInstruSyncedCountersTypeIcgm:
        {
            SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INST_SYNCED_COUNTERS_SETTING_ICGM, &entry_handle_id));
            dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_SYNC_COUNTERS_NOF_INTERVALS,
                                      INST_SINGLE, &nof_intervals_hw);
            dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_IS_CONTINUOUS, INST_SINGLE, is_countinious);
            SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

            *nof_intervals = nof_intervals_hw + 1;
            break;
        }
        case bcmInstruSyncedCountersTypeNif:
        {
            /** All IMBs are set to the same values, so just get the value for IMB 0 */
            SHR_IF_ERR_EXIT(imb_instru_synced_counters_config_get(unit, 0, &nof_intervals_hw, is_countinious));
            *nof_intervals = nof_intervals_hw + 1;
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported source_type %d.\n", source_type);
        }
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -  Get time stamp for sync counters start time.
 * \param [in] unit - The unit number.
 * \param [out] timestamp_ns - Pointer to the retrieved value. Given in nanoseconds.
 * \return
 *   See \ref shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_instru_synced_counters_timestamp_ns_get(
    int unit,
    uint64 *timestamp_ns)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INST_TOD, &entry_handle_id));
    dbal_value_field64_request(unit, entry_handle_id, DBAL_FIELD_TIMESTAMP_NS, INST_SINGLE, timestamp_ns);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -  Get time current time of day (TOD)
 * \param [in] unit - The unit number.
 * \param [out] tod_1588 - Pointer to the retrieved value.
 * \return
 *   See \ref shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_instru_synced_counters_tod_1588_get(
    int unit,
    uint64 *tod_1588)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INST_TOD, &entry_handle_id));
    dbal_value_field64_request(unit, entry_handle_id, DBAL_FIELD_TOD_1588, INST_SINGLE, tod_1588);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * See instru_internal.h file
 */
shr_error_e
dnx_instru_synced_counters_sw_state_set(
    int unit,
    bcm_instru_synced_counters_source_type_t source_type,
    int is_start)
{
    uint64 tod_1588;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /*
     * Set the SW state.
     */
    if (is_start)
    {
        /** Get the time*/
        SHR_IF_ERR_EXIT(dnx_instru_synced_counters_tod_1588_get(unit, &tod_1588));

        switch (source_type)
        {
            case bcmInstruSyncedCountersTypeIcgm:
            {
                int core_index;

                SHR_IF_ERR_EXIT(instru_sync_counters.icgm_countes.sync_counters_started.set(unit, TRUE));
                SHR_IF_ERR_EXIT(instru_sync_counters.icgm_countes.tod_1588_timestamp_start.set(unit, tod_1588));
                DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core_index)
                {
                    SHR_IF_ERR_EXIT(instru_sync_counters.icgm_countes.per_core_info.
                                    record_last_read_nof.set(unit, core_index, 0));
                }
                break;
            }
            case bcmInstruSyncedCountersTypeNif:
            {
                int core_index;
                int ethu_index;
                int lane_index;
                int nof_ethu_per_core;
                int nof_lanes_per_ethu = dnx_data_nif.eth.max_nof_lanes_in_ethu_get(unit);

                SHR_IF_ERR_EXIT(instru_sync_counters.nif_countes.sync_counters_started.set(unit, TRUE));
                SHR_IF_ERR_EXIT(instru_sync_counters.nif_countes.tod_1588_timestamp_start.set(unit, tod_1588));
                DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core_index)
                {
                    SHR_IF_ERR_EXIT(dnx_algo_port_nif_ethu_nof_ethus_per_core_get
                                    (unit, core_index, &nof_ethu_per_core));
                    for (ethu_index = 0; ethu_index < nof_ethu_per_core; ethu_index++)
                    {
                        for (lane_index = 0; lane_index < nof_lanes_per_ethu; lane_index++)
                        {
                            SHR_IF_ERR_EXIT(instru_sync_counters.nif_countes.per_ethu_info.
                                            record_last_read_nof.set(unit, core_index, ethu_index, lane_index, 0));
                        }
                    }
                }
                break;
            }
            default:
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported source type %d.\n", source_type);
            }
        }

    }
    else
    {
        switch (source_type)
        {
            case bcmInstruSyncedCountersTypeIcgm:
            {
                SHR_IF_ERR_EXIT(instru_sync_counters.icgm_countes.sync_counters_started.set(unit, FALSE));
                break;
            }
            case bcmInstruSyncedCountersTypeNif:
            {
                SHR_IF_ERR_EXIT(instru_sync_counters.nif_countes.sync_counters_started.set(unit, FALSE));
                break;
            }
            /** coverity[dead_error_begin:FALSE]  */
            default:
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported source type %d.\n", source_type);
            }
        }

    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * API to configure and enable/disable synchronous instrumentation counters per type
 *
 * \param [in] unit -  Unit-ID
 * \param [in] flags -  Flags
 * \param [in] source_type -  Type of Synchronous Counters mechanism
 * \param [in] config -  Configuration structure for Synchronous Counters mechanism
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_instru_synced_counters_config_set(
    int unit,
    uint32 flags,
    bcm_instru_synced_counters_source_type_t source_type,
    bcm_instru_synced_counters_config_t * config)
{
    uint8 enable = 0;
    uint8 is_continuous = 0;
    uint64 start_time;
    uint64 interval_period;
    uint16 nof_intervals = 0;
    uint64 timestamp;
    uint64 immediate_start;
    dnxc_time_t time_src;
    dnxc_time_t time_dest;
    uint32 max_nof_intervals;
    uint32 trigger_enable = FALSE;
    bcm_instru_synced_trigger_source_type_t trigger_source = bcmInstruSyncedTriggerTypeCount;
    bcm_instru_synced_trigger_config_t trigger_config;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    COMPILER_64_ZERO(start_time);
    COMPILER_64_ZERO(interval_period);
    COMPILER_64_ZERO(timestamp);

    /** Verify input parameters */
    SHR_IF_ERR_EXIT(dnx_instru_synced_counters_config_verify(unit, flags, source_type, config, TRUE));

    enable = (config->enable == 0) ? FALSE : TRUE;

    /** Take the instrumentation counters into reset */
    SHR_IF_ERR_EXIT(dnx_instru_synced_counters_hw_reset_set(unit, source_type, TRUE));

    /** Trigger configurations */
    if (!(flags & BCM_INSTRU_SYNCED_COUNTERS_CONFIG_SKIP_TRIGGER))
    {
        /** Determine the trigger source */
        trigger_source =
            (source_type ==
             bcmInstruSyncedCountersTypeIcgm) ? bcmInstruSyncedTriggerTypeIcgm : bcmInstruSyncedTriggerTypeNif;

        /** Disable the trigger in ECI and reset the SW State */
        trigger_enable = FALSE;
        SHR_IF_ERR_EXIT(bcm_dnx_instru_synced_triggers_enable_set(unit, 0, 1, &trigger_source, &trigger_enable));
    }

    if (enable == TRUE)
    {
        /** Set number of intervals - eventor collection nof_interval=1, otherwise, nof_interval=max */
        max_nof_intervals =
            (source_type ==
             bcmInstruSyncedCountersTypeNif) ? dnx_data_instru.
            synced_counters.nif_max_nof_intervals_get(unit) : dnx_data_instru.synced_counters.
            cgm_max_nof_intervals_get(unit);
        nof_intervals = (config->is_eventor_collection == TRUE) ? 1 : max_nof_intervals;

        is_continuous = (config->is_continuous == 0) ? FALSE : TRUE;

        /** Set the Synced counters configuration to HW */
        SHR_IF_ERR_EXIT(dnx_instru_synced_counters_config_hw_set(unit, source_type, nof_intervals, is_continuous));

        /** Take the instrumentation counters out of reset */
        SHR_IF_ERR_EXIT(dnx_instru_synced_counters_hw_reset_set(unit, source_type, FALSE));

        /** Trigger configurations */
        if (!(flags & BCM_INSTRU_SYNCED_COUNTERS_CONFIG_SKIP_TRIGGER))
        {
            /** Set start time */
            COMPILER_64_SET(immediate_start, -1, -1);
            if (COMPILER_64_EQ(config->start_time, immediate_start))
            {
                SHR_IF_ERR_EXIT(dnx_instru_synced_counters_timestamp_ns_get(unit, &timestamp));
                /*
                 * Add one ms to the current timestamp to compensate the delay for setting it to HW
                 * Timestamp is in nanoseconds, so convert 1 ms to ns and add it.
                 */
                COMPILER_64_SET(time_src.time, 0, 1);
                time_src.time_units = DNXC_TIME_UNIT_MILISEC;
                SHR_IF_ERR_EXIT(dnxc_time_units_convert(unit, &time_src, DNXC_TIME_UNIT_NSEC, &time_dest));
                COMPILER_64_ADD_64(timestamp, time_dest.time);
                COMPILER_64_COPY(start_time, timestamp);
            }

            /** Set interval period */
            COMPILER_64_COPY(interval_period, config->period);

            /** Initialize the trigger configuration structure to 0 */
            sal_memset(&trigger_config, 0, sizeof(trigger_config));

            /** Configure the parameters of the trigger in ECI */
            COMPILER_64_COPY(trigger_config.start_time, start_time);
            COMPILER_64_COPY(trigger_config.trigger_period, interval_period);
            /** The input of the triggers API is not nof_intervals. It is nof_triggers, which is nof_intervals+1 */
            trigger_config.nof_triggers = (is_continuous == TRUE) ? 0 : (nof_intervals + 1);
            SHR_IF_ERR_EXIT(bcm_dnx_instru_synced_trigger_config_set
                            (unit, BCM_INSTRU_SYNCED_TRIGGER_CONFIG_START_TIME_ABSOLUTE, trigger_source,
                             &trigger_config));

            /** Enable the trigger in ECI and set the SW state */
            trigger_enable = TRUE;
            SHR_IF_ERR_EXIT(bcm_dnx_instru_synced_triggers_enable_set(unit, 0, 1, &trigger_source, &trigger_enable));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * API to get synchronous instrumentation counters configuration per type
 *
 * \param [in] unit -  Unit-ID
 * \param [in] flags -  Flags
 * \param [in] source_type -  Type of Synchronous Counters mechanism
 * \param [out] config -  Configuration structure for Synchronous Counters mechanism
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_instru_synced_counters_config_get(
    int unit,
    uint32 flags,
    bcm_instru_synced_counters_source_type_t source_type,
    bcm_instru_synced_counters_config_t * config)
{
    uint8 nof_intervals = 0;
    uint8 is_continuous = 0;
    uint8 reset = 0;
    bcm_instru_synced_trigger_source_type_t trigger_source = bcmInstruSyncedTriggerTypeCount;
    bcm_instru_synced_trigger_config_t trigger_config;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    /** Verify input parameters */
    SHR_IF_ERR_EXIT(dnx_instru_synced_counters_config_verify(unit, flags, source_type, config, FALSE));

    /** Initialize the output structure. */
    bcm_instru_synced_counters_config_t_init(config);

    /** Get trigger configurations */
    if (!(flags & BCM_INSTRU_SYNCED_COUNTERS_CONFIG_SKIP_TRIGGER))
    {
        /** Determine the trigger source */
        trigger_source =
            (source_type ==
             bcmInstruSyncedCountersTypeIcgm) ? bcmInstruSyncedTriggerTypeIcgm : bcmInstruSyncedTriggerTypeNif;

        /** Initialize the trigger configuration structure to 0 */
        sal_memset(&trigger_config, 0, sizeof(trigger_config));

        /** Get the parameters of the trigger in ECI */
        SHR_IF_ERR_EXIT(bcm_dnx_instru_synced_trigger_config_get(unit, 0, trigger_source, &trigger_config));

        /** Get start time */
        COMPILER_64_COPY(config->start_time, trigger_config.start_time);

        /** Get interval period */
        COMPILER_64_COPY(config->period, trigger_config.trigger_period);
    }

    /** Get the instrumentation counters reset status */
    SHR_IF_ERR_EXIT(dnx_instru_synced_counters_hw_reset_get(unit, source_type, &reset));

    /** Get enable status */
    config->enable = ((reset == 0) ? TRUE : FALSE);

    /** Get the Synced counters configuration from HW */
    SHR_IF_ERR_EXIT(dnx_instru_synced_counters_config_hw_get(unit, source_type, &nof_intervals, &is_continuous));

    /** Get is_eventor_collection - eventor collection nof_interval=1, otherwise, nof_interval=max */
    config->is_eventor_collection = (nof_intervals == 1) ? TRUE : FALSE;

    /** Get is_continuous */
    config->is_continuous = (is_continuous == 0) ? FALSE : TRUE;

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Get the counters from one recordfor ICGM.
 *
 * \param [in] unit           - Unit-ID
 * \param [in] core_id        - The core for which to collect the info.
 * \param [in] record_index     - The record to be read.
 * \param [in] nof_counters     - The number of counters per record to read.
                                  Number of arrays in dbal_fields and counter_values.
 * \param [in] dbal_fields      - An array (with nof_counters elements) of the DBAL fields to collect.
 * \param [out] counter_values  - An array (with nof_counters elements) of the values of the counters.
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_instru_synced_counters_per_record_icgm_get(
    int unit,
    bcm_core_t core_id,
    int record_index,
    int nof_counters,
    int dbal_fields[],
    uint64 counter_values[])
{
    uint32 entry_handle_id;
    int counter_index;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INST_SYNCED_COUNTERS_RECORDS_ICGM, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_COUNTERS_RECORD_INDEX, record_index);
    for (counter_index = 0; counter_index < nof_counters; counter_index++)
    {
        dbal_value_field64_request(unit, entry_handle_id, dbal_fields[counter_index], INST_SINGLE,
                                   &counter_values[counter_index]);
    }
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Get the counters from one record.
 *
 * \param [in] unit             - Unit-ID
 * \param [in] source_type      - Type of Synchronous Counters mechanism
 * \param [in] core_id          - The core for which to collect the info.
 *                                Only relevant if source_type is ICGM.
 * \param [in] port             - The port for which to collect the info.
 *                                Only relevant if source_type is NIF.
 * \param [in] record_index     - The record to be read.
 * \param [in] nof_counters     - The number of counters per record to read.
                                  Number of elements in dbal_fields and counter_values.
 * \param [in] dbal_fields      - An array (with nof_counters elements) of the DBAL fields to collect.
 * \param [out] counter_values  - An array (with nof_counters elements) of the values of the counters.
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_instru_synced_counters_per_record_get(
    int unit,
    bcm_instru_synced_counters_source_type_t source_type,
    bcm_core_t core_id,
    bcm_port_t port,
    int record_index,
    int nof_counters,
    int dbal_fields[],
    uint64 counter_values[])
{
    SHR_FUNC_INIT_VARS(unit);

    switch (source_type)
    {
        case bcmInstruSyncedCountersTypeIcgm:
        {
            SHR_IF_ERR_EXIT(dnx_instru_synced_counters_per_record_icgm_get(unit, core_id, record_index, nof_counters,
                                                                           dbal_fields, counter_values));
            break;
        }
        case bcmInstruSyncedCountersTypeNif:
        {
            SHR_IF_ERR_EXIT(imb_instru_synced_counters_per_record_get(unit, port, record_index, nof_counters,
                                                                      dbal_fields, counter_values));
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported source_type %d.\n", source_type);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Get the last write and nof writes for ICGM
 *
 * \param [in] unit           - Unit-ID
 * \param [in] core_id        - The core for which to collect the info.
 * \param [out] last_write_p  - Index of last record written.
 * \param [out] nof_writes_p  - Cyclical number of records written.
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_instru_synced_counters_last_write_icgm_get(
    int unit,
    bcm_core_t core_id,
    uint32 *last_write_p,
    uint32 *nof_writes_p)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INST_SYNCED_COUNTERS_LAST_COUNT_ICGN, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LAST_WRITE, INST_SINGLE, last_write_p);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_NOF_WRITES, INST_SINGLE, nof_writes_p);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Get the last write and nof writes
 *
 * \param [in] unit           - Unit-ID
 * \param [in] source_type    - Type of Synchronous Counters mechanism
 * \param [in] core_id        - The core for which to collect the info.
 *                              Only relevant if source_type is ICGM.
 * \param [in] port           - The port for which to collect the info.
 *                              Only relevant if source_type is NIF.
 * \param [out] last_write_p  - Index of last record written.
 * \param [out] nof_writes_p  - Cyclical number of records written.
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_instru_synced_counters_last_write_get(
    int unit,
    bcm_instru_synced_counters_source_type_t source_type,
    bcm_core_t core_id,
    bcm_port_t port,
    uint32 *last_write_p,
    uint32 *nof_writes_p)
{
    SHR_FUNC_INIT_VARS(unit);

    switch (source_type)
    {
        case bcmInstruSyncedCountersTypeIcgm:
        {
            SHR_IF_ERR_EXIT(dnx_instru_synced_counters_last_write_icgm_get(unit, core_id, last_write_p, nof_writes_p));
            break;
        }
        case bcmInstruSyncedCountersTypeNif:
        {
            SHR_IF_ERR_EXIT(imb_instru_synced_counters_last_write_get(unit, port, last_write_p, nof_writes_p));
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported source_type %d.\n", source_type);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Function to get the what synchronized counters records are needed to be read.
 *
 * \param [in] unit -  Unit-ID
 * \param [in] nof_written_cyc -  The number of records read in HW, cyclical by nof_intervals_counter.
 * \param [in] last_nof_record_read - The number of records written during the previous read.
 * \param [in] start_time - The time when the recording started (TOD 1588).
 * \param [in] current_time - Current time (TOD 1588).
 * \param [in] interval_period_nanoseconds - The periods in nanoseconds between writes.
 * \param [in] nof_intervals_buffer - The number or intervals written before they are overwritten cyclically.
 * \param [in] nof_intervals_counter - One above the maximum number of recorded number of intervals kept in HW,
 *                                     before wrapping around.
 * \param [in] nof_periods_to_skip - The number of periods after the last write we do not try to read,
 *                                   fearing the may be written to while we read.
 * \param [out] first_record_absolute_index -  The first record to be read, as index from the start.
 * \param [out] first_record_index -  The first record to be read, as index in the cyclical array.
 * \param [out] num_records_read -  Number of records to be read.
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
static int
dnx_instru_synced_counters_records_continuous_records_to_read(
    int unit,
    uint32 nof_written_cyc,
    uint32 last_nof_record_read,
    uint64 start_time,
    uint64 current_time,
    uint64 interval_period_nanoseconds,
    uint32 nof_intervals_buffer,
    uint32 nof_intervals_counter,
    uint32 nof_periods_to_skip,
    uint32 *first_record_absolute_index,
    uint32 *first_record_index,
    uint32 *num_records_read)
{
    int period_precision_for_tod = 2;
    uint32 nof_periods_from_start;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Find the number of writes from the beginning.
     */
    {
        uint64 time_from_start_nanoseconds;
        uint64 nof_intervals_total_uint64;
        uint32 estimated_nof_periods_from_start;
        uint32 expected_nof_writes;
        int expectation_mismatch;

        /*
         * Estimate the number of periods that passed since the beginning using TOD.
         */
        SHR_IF_ERR_EXIT(utilex_tod_1588_diff_nanoseconds(unit, start_time, current_time, &time_from_start_nanoseconds));
        COMPILER_64_COPY(nof_intervals_total_uint64, time_from_start_nanoseconds);
        COMPILER_64_UDIV_64(nof_intervals_total_uint64, interval_period_nanoseconds);
        estimated_nof_periods_from_start = COMPILER_64_LO(nof_intervals_total_uint64);
        /** Verify that we are not beyond the 32 bit boundary.*/
        if (COMPILER_64_HI(nof_intervals_total_uint64) != 0)
        {
            SHR_ERR_EXIT(_SHR_E_TIMEOUT, "More than 2^32 periods passed, not supported.\n");
        }
        COMPILER_64_ADD_32(nof_intervals_total_uint64, period_precision_for_tod);
        if (COMPILER_64_HI(nof_intervals_total_uint64) != 0)
        {
            SHR_ERR_EXIT(_SHR_E_TIMEOUT, "More than 2^32 periods may have passed, not supported.\n");
        }
        COMPILER_64_ADD_32(nof_intervals_total_uint64, nof_intervals_buffer);
        if (COMPILER_64_HI(nof_intervals_total_uint64) != 0)
        {
            SHR_ERR_EXIT(_SHR_E_TIMEOUT, "Number of periods passed too close to 2^32 period, not supported.\n");
        }

        /*
         * Verify the precision of the estimation from the start time.
         * If expected_nof_writes is within the tolerated error, align to nof_written_cyc.
         */
        expected_nof_writes = estimated_nof_periods_from_start % nof_intervals_counter;
        if (expected_nof_writes > nof_written_cyc)
        {
            expectation_mismatch = expected_nof_writes - nof_written_cyc;
        }
        else
        {
            expectation_mismatch = nof_written_cyc - expected_nof_writes;
        }
        if (expectation_mismatch > period_precision_for_tod)
        {
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Expected last write to be %u, actually %u, max tolerance is %u.\n",
                         expected_nof_writes, nof_written_cyc, period_precision_for_tod);
        }
        /** Fix the actual number of periods to be aligned to nof_written_cyc. */
        nof_periods_from_start = estimated_nof_periods_from_start + nof_written_cyc - expected_nof_writes;
    }

    if (nof_periods_from_start < last_nof_record_read)
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "Calculated %u periods from the start, but last read it was %u.\n",
                     nof_periods_from_start, last_nof_record_read);
    }

    /*
     * Get the number of records to read.
     */
    (*num_records_read) = nof_periods_from_start - last_nof_record_read;
    if ((*num_records_read) > (nof_intervals_buffer - nof_periods_to_skip))
    {
        (*num_records_read) = nof_intervals_buffer - nof_periods_to_skip;
    }
    if ((*num_records_read) > nof_periods_from_start)
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "Calculated %u periods from the start, but reading %u.\n",
                     nof_periods_from_start, (*num_records_read));
    }
    /*
     * If we read records
     */
    if ((*num_records_read) > 0)
    {
        (*first_record_absolute_index) = nof_periods_from_start - (*num_records_read);
        (*first_record_index) = (*first_record_absolute_index) % nof_intervals_buffer;
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Function to get the synchronized counters.
 *
 * \param [in] unit -  Unit-ID
 * \param [in] source_type -  Where to get the counters from.
 * \param [in] core_id_in -  The core to read from, if we do not have a gport.
 * \param [in] gport -  If record_source_type is port dependent, the port to read for.
 * \param [out] record_arr -  Array to fill the counter records.
 * \param [out] nof_records_read -  Number of elements written to in record_arr.
 * \param [out] couter_types -  Array of counter types read within record_arr.
 * \param [out] nof_counter_types -  Number of elements in couter_types.
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
static int
dnx_instru_synced_counters_records_hw_get(
    int unit,
    bcm_instru_synced_counters_source_type_t source_type,
    bcm_core_t core_id_in,
    bcm_gport_t gport,
    bcm_instru_synced_counters_record_t record_arr[BCM_INSTRU_SYNCED_COUNTERS_RECORDS_MAX],
    int *nof_records_read,
    bcm_instru_synced_counters_type_t couter_types[BCM_INSTRU_SYNCED_COUNTERS_STATS_MAX],
    int *nof_counter_types)
{
    bcm_core_t core_id = -1;
    bcm_port_t logical_port = DNX_ALGO_PORT_INVALID;
    uint64 tod_1588;
    uint64 tod_1588_after;
    uint64 sw_state_tod_1588_start;
    uint64 time_diff_nanoseconds;
    uint64 time_diff_maximum_read_time;
    uint64 interval_period_nanoseconds;
    uint8 nof_intervals_config;
    int nof_intervals_hw;
    int nof_intervals_counter = dnx_data_instru.synced_counters.cgm_write_counter_wrap_around_get(unit);
    uint8 is_continuous;
    /** Initializations to appease the compiler.*/
    uint32 first_record = 0;
    uint32 first_record_absolute_index = 0;
    uint32 num_records_read = 0xFFFFFFFF;
    uint32 sw_state_last_nof_records_read;
    uint8 sw_state_last_info_set;
    /** Tolerance numbers.*/
    int nof_periods_to_skip = 2;
    int maximum_periods_to_pass_during_read = 1;
    int record_index;
    uint32 last_record_written_in_hw;
    uint32 nof_records_written_in_hw;
    uint64
        retrieved_records[DNX_DATA_MAX_INSTRU_SYNCED_COUNTERS_CGM_MAX_NOF_INTERVALS]
        [BCM_INSTRU_SYNCED_COUNTERS_STATS_MAX];
    int nof_counters_per_record;
    int counter_index;
    uint32 bytes_in_word = dnx_data_instru.synced_counters.bytes_in_word_get(unit);
    /** Initialization to appease the compiler.*/
    int ethu_id = -1;
    int port_in_ethu = -1;
    int counters_dbal_fields[BCM_INSTRU_SYNCED_COUNTERS_STATS_MAX] = { 0 };
    bcm_instru_synced_trigger_source_type_t trigger_source = bcmInstruSyncedTriggerTypeCount;
    bcm_instru_synced_trigger_config_t trigger_config;
    uint32 trigger_enable;
    SHR_FUNC_INIT_VARS(unit);

    /** Determine the max number of intervals */
    nof_intervals_hw =
        (source_type ==
         bcmInstruSyncedCountersTypeNif) ? dnx_data_instru.
        synced_counters.nif_max_nof_intervals_get(unit) : dnx_data_instru.synced_counters.
        cgm_max_nof_intervals_get(unit);

    switch (source_type)
    {
        case bcmInstruSyncedCountersTypeIcgm:
        {
            core_id = core_id_in;
            break;
        }
        case bcmInstruSyncedCountersTypeNif:
        {
            dnx_algo_port_ethu_access_info_t ethu_info;

            /** Get the logical port from the gport. */
            if (BCM_GPORT_IS_SET(gport))
            {
                logical_port = BCM_GPORT_LOCAL_GET(gport);
            }
            else
            {
                logical_port = gport;
            }
            SHR_IF_ERR_EXIT(dnx_algo_port_ethu_access_info_get(unit, logical_port, &ethu_info));
            core_id = ethu_info.core;
            ethu_id = ethu_info.ethu_id_in_core;
            /** The counters are on the first lane of the port.*/
            port_in_ethu = ethu_info.first_lane_in_port;

            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported source_type %d.\n", source_type);
        }
    }

    /*
     * Get the last read time from SW state.
     */
    switch (source_type)
    {
        case bcmInstruSyncedCountersTypeIcgm:
        {
            SHR_IF_ERR_EXIT(instru_sync_counters.icgm_countes.sync_counters_started.get(unit, &sw_state_last_info_set));
            SHR_IF_ERR_EXIT(instru_sync_counters.icgm_countes.per_core_info.
                            record_last_read_nof.get(unit, core_id, &sw_state_last_nof_records_read));
            SHR_IF_ERR_EXIT(instru_sync_counters.icgm_countes.
                            tod_1588_timestamp_start.get(unit, &sw_state_tod_1588_start));
            break;
        }
        case bcmInstruSyncedCountersTypeNif:
        {
            SHR_IF_ERR_EXIT(instru_sync_counters.nif_countes.sync_counters_started.get(unit, &sw_state_last_info_set));
            SHR_IF_ERR_EXIT(instru_sync_counters.nif_countes.per_ethu_info.
                            record_last_read_nof.get(unit, core_id, ethu_id, port_in_ethu,
                                                     &sw_state_last_nof_records_read));
            SHR_IF_ERR_EXIT(instru_sync_counters.nif_countes.
                            tod_1588_timestamp_start.get(unit, &sw_state_tod_1588_start));
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported source_type %d.\n", source_type);
        }
    }
    if (!sw_state_last_info_set)
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "Synchronized counters not configured for source type %d.\n", source_type);
    }

    /** Get the Synced counters configuration from HW */
    SHR_IF_ERR_EXIT(dnx_instru_synced_counters_config_hw_get(unit, source_type, &nof_intervals_config, &is_continuous));

    /** Determine the trigger source */
    trigger_source =
        (source_type ==
         bcmInstruSyncedCountersTypeIcgm) ? bcmInstruSyncedTriggerTypeIcgm : bcmInstruSyncedTriggerTypeNif;

    /** Initialize the trigger configuration structure to 0 */
    sal_memset(&trigger_config, 0, sizeof(trigger_config));

    /** Get the parameters of the trigger in ECI */
    SHR_IF_ERR_EXIT(bcm_dnx_instru_synced_trigger_config_get(unit, 0, trigger_source, &trigger_config));
    COMPILER_64_COPY(interval_period_nanoseconds, trigger_config.trigger_period);
    is_continuous = (trigger_config.nof_triggers == 0) ? TRUE : FALSE;

    /** Get the enable of the trigger in ECI */
    SHR_IF_ERR_EXIT(bcm_dnx_instru_synced_triggers_enable_get(unit, 0, 1, &trigger_source, &trigger_enable));

    if (trigger_enable == FALSE)
    {
        SHR_ERR_EXIT(_SHR_E_CONFIG, "Synchronized counters collection (source_type %d ) "
                     "not configured.\n", source_type);
    }
    if (COMPILER_64_IS_ZERO(interval_period_nanoseconds))
    {
        SHR_ERR_EXIT(_SHR_E_CONFIG, "Synchronized counters (source type %d) " "collection has 0 \n", source_type);
    }
    if (nof_intervals_config == 1)
    {
        SHR_ERR_EXIT(_SHR_E_CONFIG, "Synchronized counters (source type %d) "
                     "was configured as is_eventor.\n", source_type);
    }
    if (nof_intervals_config <= 1)
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "Synchronized counters (source type %d) "
                     "has number of intervals %d, cannot process.\n", source_type, nof_intervals_config);
    }
    if (nof_intervals_config != nof_intervals_hw)
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "Synchronized counters (source type %d) "
                     "has number of intervals %d, must be %d.\n", source_type, nof_intervals_config, nof_intervals_hw);
    }

    /*
     * Count the number of counters.
     */
    for (counter_index = 0; counter_index < BCM_INSTRU_SYNCED_COUNTERS_STATS_MAX; counter_index++)
    {
        if (dnx_data_instru.synced_counters.counters_info_get(unit, counter_index, source_type)->valid == FALSE)
        {
            break;
        }
    }
    nof_counters_per_record = counter_index;

    /** Sanity check. */
    if (nof_intervals_hw <= nof_periods_to_skip)
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "nof_intervals_hw (%u) must be bigger than nof_periods_to_skip (%u).\n",
                     nof_intervals_hw, nof_periods_to_skip);
    }

    /*
     * Prepare the DBAL fields of the counters to read.
     */
    for (counter_index = 0; counter_index < nof_counters_per_record; counter_index++)
    {
        counters_dbal_fields[counter_index] =
            dnx_data_instru.synced_counters.counters_info_get(unit, counter_index, source_type)->dbal_field;
    }

    /*
     * Get the TOD and the last written record.
     */
    SHR_IF_ERR_EXIT(dnx_instru_synced_counters_tod_1588_get(unit, &tod_1588));
    SHR_IF_ERR_EXIT(dnx_instru_synced_counters_last_write_get
                    (unit, source_type, core_id, logical_port, &last_record_written_in_hw, &nof_records_written_in_hw));

    /*
     * Find the records to read.
     */
    if (is_continuous)
    {
        SHR_IF_ERR_EXIT(dnx_instru_synced_counters_records_continuous_records_to_read
                        (unit, nof_records_written_in_hw, sw_state_last_nof_records_read, sw_state_tod_1588_start,
                         tod_1588, interval_period_nanoseconds, nof_intervals_hw, nof_intervals_counter,
                         nof_periods_to_skip, &first_record_absolute_index, &first_record, &num_records_read));

    }
    else
    {
        first_record = sw_state_last_nof_records_read;
        first_record_absolute_index = first_record;
        num_records_read = nof_records_written_in_hw - sw_state_last_nof_records_read;
        if (nof_records_written_in_hw < sw_state_last_nof_records_read)
        {
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Synchronized counters not continuous, but "
                         "number of writes (%d) is smaller than the previous number of writes (%d).\n",
                         nof_records_written_in_hw, sw_state_last_nof_records_read);
        }
        if (first_record > nof_intervals_hw ||
            ((num_records_read != 0) && ((first_record + num_records_read - 1) >= nof_intervals_hw)))
        {
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Synchronized counters calculated too many records to read "
                         "(%d to %d, and there are only %d records).\n",
                         first_record, first_record + num_records_read - 1, nof_intervals_hw);
        }
    }

    /*
     * Get the records from HW.
     */
    for (record_index = first_record;
         (record_index - first_record + nof_intervals_hw) % nof_intervals_hw < num_records_read;
         record_index = (record_index + 1) % nof_intervals_hw)
    {
        SHR_IF_ERR_EXIT(dnx_instru_synced_counters_per_record_get(unit, source_type, core_id, logical_port,
                                                                  record_index, nof_counters_per_record,
                                                                  counters_dbal_fields,
                                                                  retrieved_records[record_index]));
    }

    /*
     * If is_continuous, make sure we read the records fast enough, as the are overwritten cyclically.
     */
    if (is_continuous && (num_records_read != 0))
    {
        uint32 last_record_written_in_hw_after;
        uint32 nof_records_written_in_hw_after;

        /*
         * Get the TOD and the last written record after reading and check that we read it in time.
         */
        SHR_IF_ERR_EXIT(dnx_instru_synced_counters_last_write_get
                        (unit, source_type, core_id, logical_port, &last_record_written_in_hw_after,
                         &nof_records_written_in_hw_after));
        SHR_IF_ERR_EXIT(dnx_instru_synced_counters_tod_1588_get(unit, &tod_1588_after));

        if (((nof_records_written_in_hw_after - nof_records_written_in_hw + nof_intervals_hw) % nof_intervals_hw) >
            maximum_periods_to_pass_during_read)
        {
            SHR_ERR_EXIT(_SHR_E_TIMEOUT, "Synchronized counters progressed more than %d periods during read "
                         "TOD before read (%ds,%dns), TOD after read (%ds,%dns). nof_writes before read %u, "
                         "nof_writes after read %u.\n",
                         maximum_periods_to_pass_during_read,
                         COMPILER_64_HI(tod_1588), COMPILER_64_LO(tod_1588),
                         COMPILER_64_HI(tod_1588_after), COMPILER_64_LO(tod_1588_after),
                         nof_records_written_in_hw, nof_records_written_in_hw_after);
        }
        SHR_IF_ERR_EXIT(utilex_tod_1588_diff_nanoseconds(unit, tod_1588, tod_1588_after, &time_diff_nanoseconds));
        COMPILER_64_COPY(time_diff_maximum_read_time, interval_period_nanoseconds);
        COMPILER_64_UMUL_32(time_diff_maximum_read_time, maximum_periods_to_pass_during_read);
        if (COMPILER_64_GT(time_diff_nanoseconds, time_diff_maximum_read_time))
        {
            SHR_ERR_EXIT(_SHR_E_TIMEOUT, "Synchronized counters progressed more than %d periods during read. "
                         "TOD before read (%ds,%dns), TOD after read (%ds,%dns).\n",
                         maximum_periods_to_pass_during_read,
                         COMPILER_64_HI(tod_1588), COMPILER_64_LO(tod_1588),
                         COMPILER_64_HI(tod_1588_after), COMPILER_64_LO(tod_1588_after));
        }
    }

    /*
     * If there is nothing to read, don't change any SW STATE. Otherwise, return the records.
     */
    if (num_records_read > 0)
    {
        /*
         * Write to the output array.
         */
        /** Sanity check*/
        if (((*nof_records_read) > nof_intervals_hw) ||
            (((*nof_records_read) > (nof_intervals_hw - nof_periods_to_skip)) && is_continuous))
        {
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "More intervals than existing were calculated.\n");
        }

        for (record_index = 0; record_index < num_records_read; record_index++)
        {
            uint64 time_change_nanoseconds;
            uint32 record_nof_periods;

            /*
             * Copy the counters to the output array.
             */
            sal_memcpy(record_arr[record_index].value_arr,
                       retrieved_records[(record_index + first_record) % nof_intervals_hw],
                       sizeof(retrieved_records[0]));

            /** Write the TOD of the record. */
            record_nof_periods = first_record_absolute_index + 1 + record_index;
            COMPILER_64_COPY(time_change_nanoseconds, interval_period_nanoseconds);
            COMPILER_64_UMUL_32(time_change_nanoseconds, record_nof_periods);
            SHR_IF_ERR_EXIT(utilex_tod_1588_add_nanoseconds
                            (unit, FALSE, sw_state_tod_1588_start, time_change_nanoseconds,
                             &(record_arr[record_index].estimated_time_of_day)));

            /*
             * Convert words into bytes
             */
            for (counter_index = 0; counter_index < nof_counters_per_record; counter_index++)
            {
                if (dnx_data_instru.synced_counters.
                    counters_info_get(unit, counter_index, source_type)->words_to_bytes_conv_needed)
                {
                    uint64 old_value;
                    COMPILER_64_COPY(old_value, record_arr[record_index].value_arr[counter_index]);
                    COMPILER_64_UMUL_32(record_arr[record_index].value_arr[counter_index], bytes_in_word);
                    if (COMPILER_64_GT(old_value, record_arr[record_index].value_arr[counter_index]))
                    {
                        SHR_ERR_EXIT(_SHR_E_INTERNAL, "Value or record %d (%u,%u) in words is to "
                                     "large to be converted into bytes (by multiplying by %d).\n",
                                     counter_index, COMPILER_64_HI(old_value), COMPILER_64_LO(old_value),
                                     bytes_in_word);
                    }
                }
            }
        }

        /*
         * Write to SW state the last record that was read.
         */
        switch (source_type)
        {
            case bcmInstruSyncedCountersTypeIcgm:
            {
                SHR_IF_ERR_EXIT(instru_sync_counters.icgm_countes.per_core_info.record_last_read_nof.set(unit, core_id,
                                                                                                         first_record_absolute_index
                                                                                                         +
                                                                                                         num_records_read));
                break;
            }
            case bcmInstruSyncedCountersTypeNif:
            {
                SHR_IF_ERR_EXIT(instru_sync_counters.nif_countes.per_ethu_info.
                                record_last_read_nof.set(unit, core_id, ethu_id, port_in_ethu,
                                                         first_record_absolute_index + num_records_read));
                break;
            }
            /** coverity[dead_error_begin:FALSE]  */
            default:
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported source_type %d.\n", source_type);
            }
        }
    }

    /*
     * Provide the counter types.
     */
    sal_memset(couter_types, 0x0, sizeof(couter_types[0]) * BCM_INSTRU_SYNCED_COUNTERS_STATS_MAX);
    for (counter_index = 0; counter_index < nof_counters_per_record; counter_index++)
    {
        couter_types[counter_index].counter_type =
            dnx_data_instru.synced_counters.counters_info_get(unit, counter_index, source_type)->bcm_counter_type;
        couter_types[counter_index].counter_index =
            dnx_data_instru.synced_counters.counters_info_get(unit, counter_index, source_type)->counter_index;
    }
    (*nof_counter_types) = nof_counters_per_record;

    (*nof_records_read) = num_records_read;

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Function to verify the input parameters of API bcm_instru_synced_counters_records_get.
 *
 * \param [in] unit -  Unit-ID
 * \param [in] flags -  Flags
 * \param [in] key -  Structure indicating what counters to get
 * \param [in] data -  Structure to place the the counters' value in.
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
int
dnx_instru_synced_counters_records_get_verify(
    int unit,
    uint32 flags,
    bcm_instru_synced_counters_records_key_t * key,
    bcm_instru_synced_counters_data_t * data)
{
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(key, _SHR_E_PARAM, "key");
    SHR_NULL_CHECK(data, _SHR_E_PARAM, "data");

    /** Verify input flags */
    SHR_VAL_VERIFY(flags, 0, _SHR_E_PARAM, "Unsupported flags for getting synchronized counters!\n");

    /** Verify input source type.*/
    if (key->source_type == bcmInstruSyncedCountersTypeCount)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "source_type must be set. Invalid source_type.\n");
    }
    if (key->source_type != bcmInstruSyncedCountersTypeIcgm && key->source_type != bcmInstruSyncedCountersTypeNif)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported source type %d for synchronized counters configuration!\n",
                     key->source_type);
    }

    /**Core is only relevant for ICGM, for NIF gport is used to get the core.*/
    if (key->source_type == bcmInstruSyncedCountersTypeIcgm)
    {
        /*
         * We only support collecting the data for a single core, we do not support BCM_CORE_ALL.
         */
        DNXCMN_CORE_VALIDATE(unit, key->core_id, FALSE);
        if (key->gport != BCM_GPORT_INVALID)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Source type %d does not take gport as input.\n", key->source_type);
        }
    }

    /** GPORT is only relevant for NIF.*/
    if (key->source_type == bcmInstruSyncedCountersTypeNif)
    {
        /** Verify the gport.*/
        if (key->gport == BCM_GPORT_INVALID)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Source type %d requires gport to be set. Invalid gport.\n", key->source_type);
        }
        if (BCM_GPORT_IS_SET(key->gport) && !BCM_GPORT_IS_LOCAL(key->gport))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Source type %d requires a local port, while gport is 0x%x.\n",
                         key->source_type, key->gport);
        }
        if (key->core_id != BCM_CORE_ALL)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Source type %d does not take core_id as input.\n", key->source_type);
        }
    }

    /** Verify that the source type has at least one counter.*/
    if (!(dnx_data_instru.synced_counters.counters_info_get(unit, 0, key->source_type)->valid))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported source type %d for synchronized "
                     "counters configuration on this device!\n", key->source_type);
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * API to get the counter values of sync counters mechanism (nif or icgm, depending on the source_type)
 *
 * \param [in] unit -  Unit-ID
 * \param [in] flags -  Flags
 * \param [in] key -  The synchronous counters to be collected.
 * \param [out] data -  The structure to collect the data to.
 * \return
 *   See shr_error_e
 * \remark
 *   * None
 * \see
 *   * None
 */
int
bcm_dnx_instru_synced_counters_records_get(
    int unit,
    uint32 flags,
    bcm_instru_synced_counters_records_key_t * key,
    bcm_instru_synced_counters_data_t * data)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    /** Verify input parameters */
    SHR_INVOKE_VERIFY_DNXC(dnx_instru_synced_counters_records_get_verify(unit, flags, key, data));

    /** Initialize the output*/
    bcm_instru_synced_counters_data_t_init(data);

    /*
     * Read the counters.
     */
    SHR_IF_ERR_EXIT(dnx_instru_synced_counters_records_hw_get
                    (unit, key->source_type, key->core_id, key->gport,
                     data->record_arr, &(data->nof_records), data->record_arr_counters_type, &(data->nof_counters)));

exit:
    SHR_FUNC_EXIT;
}

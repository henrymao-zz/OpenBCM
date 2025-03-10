/** \file mpls_l2vpn_egress.c General MPLS egress L2VPN functionality for DNX.
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_MPLS

/*
 * Include files.
 * {
 */
#include <soc/sand/shrextend/shrextend_debug.h>
#include <bcm_int/dnx/mpls/mpls.h>
#include <bcm_int/dnx/mpls/mpls_tunnel_encap.h>
#include <bcm_int/dnx/lif/lif_lib.h>
#include <bcm_int/dnx/algo/algo_gpm.h>
#include <bcm_int/dnx/qos/qos.h>
#include <bcm_int/dnx/algo/qos/algo_qos.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_esem.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_port_pp.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_failover.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_lif.h>
#include <bcm_int/dnx/lif/out_lif_profile.h>
#include <bcm_int/dnx/vlan/vlan.h>
#include <bcm_int/dnx/port/port_tpid.h>
#include <bcm_int/dnx/port/port_esem.h>
#include <bcm_int/dnx/algo/port_pp/algo_port_pp.h>
#include <bcm_int/dnx/failover/failover.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/access/algo_port_pp_access.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/access/algo_qos_access.h>
#include <bcm_int/dnx/lif/lif_table_mngr_lib.h>
#include <bcm_int/dnx/algo/lif_mngr/lif_mngr.h>

#include "mpls_l2vpn_egress.h"

/**
* \brief
* Verify mpls_port struct according to MPLS port addition requirements.
* Invoked from dnx_mpls_port_add_egress_only().
* \par DIRECT INPUT:
*   \param [in] unit       -  Relevant unit.
*   \param [in] l2vpn_info  -  Holds all the relevant information for the different schemes that might be defined on a VPLS LIF.
* \par DIRECT OUTPUT:
*   shr_error_e - Non-zero in case of an error.
* \remark
*   * 'l2vpn_info' is not NULL
*/
static shr_error_e
dnx_mpls_l2vpn_add_egress_only_verify(
    int unit,
    dnx_mpls_l2vpn_info_t * l2vpn_info)
{
    uint32 lif_flags;
    lif_mngr_local_outlif_info_t outlif_info;
    dnx_algo_gpm_gport_hw_resources_t gport_hw_resources;
    bcm_encap_access_t encap_access;

    SHR_FUNC_INIT_VARS(unit);

    if (_SHR_IS_FLAG_SET(l2vpn_info->mpls_port->flags, BCM_MPLS_PORT_REPLACE))
    {
        lif_flags =
            DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_EGRESS | DNX_ALGO_GPM_GPORT_HW_RESOURCES_GLOBAL_LIF_EGRESS;
        SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_to_hw_resources
                        (unit, l2vpn_info->mpls_port->mpls_port_id, lif_flags, &gport_hw_resources));

        sal_memset(&outlif_info, 0, sizeof(outlif_info));

        encap_access = l2vpn_info->mpls_port->egress_label.encap_access;
        if (encap_access == bcmEncapAccessInvalid)
        {
            encap_access = bcmEncapAccessTunnel1;
        }
        SHR_IF_ERR_EXIT(dnx_lif_lib_encap_access_to_logical_phase_convert
                        (unit, encap_access, &outlif_info.logical_phase));

        if (gport_hw_resources.logical_phase != outlif_info.logical_phase)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "replacing entry with encap_access(%d) with new value(%d) - not supported, encap_access must not change in REPLACE",
                         gport_hw_resources.logical_phase, outlif_info.logical_phase);
        }
    }

    if (_SHR_IS_FLAG_SET(l2vpn_info->mpls_port->egress_label.flags, BCM_MPLS_EGRESS_LABEL_ALTERNATE_MARKING))
    {
        if (!dnx_data_mpls.general.feature_get(unit, dnx_data_mpls_general_support_alternate_marking))
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Not supported Alternate marking\n");
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Update mpls_port struct with the relevant information
*  from out-lif-profile.
*
*   \param [in] unit -  Relevant unit.
*   \param [in] out_lif_profile -outlif profile.
*   \param [out] mpls_port - bcm struct with user info.
* \return
*   shr_error_e
*
* \remark
*   None
* \see
*   dnx_mpls_port_get_egress_only
*/
static shr_error_e
dnx_mpls_outlif_profile_to_mpls_port_info(
    int unit,
    int out_lif_profile,
    bcm_mpls_port_t * mpls_port)
{
    etpp_out_lif_profile_info_t out_lif_profile_info;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Get out_lif_porfile data:
     */
    etpp_out_lif_profile_info_t_init(unit, &out_lif_profile_info);
    SHR_IF_ERR_EXIT(dnx_etpp_out_lif_profile_get_data(unit, out_lif_profile, &out_lif_profile_info));

    /*
     * Update network_group_id:
     */
    mpls_port->network_group_id = out_lif_profile_info.out_lif_orientation;

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Update mpls_port struct with the relevant information
*  from esem command profile.
*
*   \param [in] unit -  Relevant unit.
*   \param [in] encap_info - encapsulation info.
*   \param [out] mpls_port - bcm struct with user info.
* \return
*   shr_error_e
*
* \remark
*   None
* \see
*   dnx_mpls_port_get_egress_only
*/
static shr_error_e
dnx_mpls_esem_cmd_profile_to_mpls_port_info(
    int unit,
    dnx_mpls_encap_t * encap_info,
    bcm_mpls_port_t * mpls_port)
{
    uint8 is_native_ac_lif_name_space;
    uint8 is_esi_src_lif;
    dnx_esem_cmd_data_t esem_cmd_data;

    SHR_FUNC_INIT_VARS(unit);

    /** Get esem command data: */
    SHR_IF_ERR_EXIT(dnx_port_esem_cmd_data_sw_get(unit, encap_info->esem_command_profile, &esem_cmd_data, NULL));
    if (encap_info->is_iml)
    {
        /** ESI retrieval is using IF_1 always per dnx_port_esem_cmds_basic.*/
        is_esi_src_lif =
            ((esem_cmd_data.esem[ESEM_ACCESS_IF_1].valid == TRUE) &&
             (esem_cmd_data.esem[ESEM_ACCESS_IF_1].app_db_id == DBAL_ENUM_FVAL_ESEM_APP_DB_ID_INLIF_NAMESPACE));
        mpls_port->egress_label.flags2 |= (is_esi_src_lif ? BCM_MPLS_EGRESS_LABEL_FLAGS2_ESI_INTF_NAMESPACE : 0);
    }

    /** If any of the esem lookup key is {fodo, outlif} for native AC, we think it as LIF scope.*/
    is_native_ac_lif_name_space =
        (((esem_cmd_data.esem[ESEM_ACCESS_IF_1].valid == TRUE) &&
          (esem_cmd_data.esem[ESEM_ACCESS_IF_1].app_db_id == DBAL_ENUM_FVAL_ESEM_APP_DB_ID_FODO_OUTLIF)) ||
         ((esem_cmd_data.esem[ESEM_ACCESS_IF_2].valid == TRUE) &&
          (esem_cmd_data.esem[ESEM_ACCESS_IF_2].app_db_id == DBAL_ENUM_FVAL_ESEM_APP_DB_ID_FODO_OUTLIF)));

    /** Update mpls_port */
    if (!is_native_ac_lif_name_space)
    {
        mpls_port->flags2 |= BCM_MPLS_PORT2_PLATFORM_NAMESPACE;
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get local and global lifs to be used for the tunnel.
*  If REPLACE is set lookup the lifs, otherwise allocate new ones.
*   \param [in] unit -Relevant unit.
*   \param [in] l2vpn -Holds all the relevant information for the different schemes that might be defined on a VPLS LIF.
*   \param [out] global_lif - global lif allocated
*   \param [out] local_outlif - local lif allocated
* \return
*   shr_error_e
*/
static shr_error_e
dnx_mpls_l2vpn_egress_lif_get_allocation_or_fill(
    int unit,
    dnx_mpls_l2vpn_info_t * l2vpn,
    int *global_lif,
    int *local_outlif)
{
    uint32 lif_flags;
    dnx_algo_gpm_gport_hw_resources_t gport_hw_resources;
    global_lif_alloc_info_t alloc_info = { 0 };

    SHR_FUNC_INIT_VARS(unit);

    if (l2vpn->mpls_port->flags & BCM_MPLS_PORT_REPLACE)
    {
        lif_flags =
            DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_EGRESS | DNX_ALGO_GPM_GPORT_HW_RESOURCES_GLOBAL_LIF_EGRESS;
        SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_to_hw_resources
                        (unit, l2vpn->mpls_port->mpls_port_id, lif_flags, &gport_hw_resources));

        *global_lif = gport_hw_resources.global_out_lif;
        *local_outlif = gport_hw_resources.local_out_lif;
    }
    else
    {
        /** Allocate ONLY global LIF */
        lif_flags = LIF_MNGR_L2_GPORT_GLOBAL_LIF;
        if (_SHR_IS_FLAG_SET(l2vpn->mpls_port->flags, BCM_MPLS_PORT_ENCAP_WITH_ID))
        {
            *global_lif = l2vpn->mpls_port->encap_id;
            lif_flags |= LIF_MNGR_GLOBAL_LIF_WITH_ID;
        }
        else if (l2vpn->mpls_port->flags & BCM_MPLS_PORT_WITH_ID)
        {
            *global_lif = ((l2vpn->type == MPLS_L2VPN_TYPE_EVPN) ?
                           BCM_GPORT_TUNNEL_ID_GET(l2vpn->mpls_port->mpls_port_id) :
                           BCM_GPORT_SUB_TYPE_LIF_VAL_GET(l2vpn->mpls_port->mpls_port_id));
            lif_flags |= LIF_MNGR_GLOBAL_LIF_WITH_ID;
        }
        if (l2vpn->mpls_port->flags2 & BCM_MPLS_PORT2_ALLOC_SYMMETRIC)
        {
            lif_flags |= LIF_MNGR_ONE_SIDED_SYMMETRIC_GLOBAL_LIF;
        }
        /** value -1 means that estimated_encap_size will be determine internally by sdk and not by the user */
        if (l2vpn->mpls_port->egress_label.estimated_encap_size == -1)
        {
            alloc_info.bta = dnx_data_lif.out_lif.global_mpls_outlif_bta_sop_get(unit);
        }
        else
        {
            alloc_info.bta = l2vpn->mpls_port->egress_label.estimated_encap_size;
        }

        SHR_IF_ERR_EXIT(dnx_algo_global_lif_allocation_allocate
                        (unit, lif_flags, DNX_ALGO_LIF_EGRESS, &alloc_info, global_lif));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Allocate an ESEM access command for MPLS port LIF.
*
* \param [in] unit -Relevant unit.
* \param [in] l2vpn_info - Pointer to L2VPN info, only below fields make sense here:
*             l2vpn_info->flags.
*             l2vpn_info->mpls_port->mpls_port_id.
*             l2vpn_info->mpls_port->flags.
*             l2vpn_info->mpls_port->flags2.
* \param [in] esem_cmd_size - an enum of format dnx_esem_cmd_suffix_size_t that represents
 *                            the size in bits of the esem cmd
* \param [in] old_esem_cmd - original esem access command if case of _REPLACE.
* \param [out] new_esem_cmd - newly allocated esem access command.
* \param [out] esem_cmd_data - esem access command data relative to new_esem_cmd.
* \param [out] esem_cmd_profile_first_reference - the new_esem_cmd is first used.
* \param [out] esem_cmd_profile_last_reference - the old_esem_cmd is last used.
*
* \return
*  shr_error_e
*
* \remark
*  In case of _REPLACE, and the result type is the same as before, the original
*  esem access cmd will be used rather than exchanging, no inputs from BCM API
*  would caused the changes to the cmd .
*
*/
static shr_error_e
dnx_mpls_l2vpn_egress_lif_esem_cmd_sw_alloc(
    int unit,
    dnx_mpls_l2vpn_info_t * l2vpn_info,
    dnx_esem_cmd_suffix_size_t esem_cmd_size,
    int old_esem_cmd,
    int *new_esem_cmd,
    dnx_esem_cmd_data_t * esem_cmd_data,
    uint8 *esem_cmd_profile_first_reference,
    uint8 *esem_cmd_profile_last_reference)
{
    int esem_default_result_profile;
    dnx_esem_cmd_data_t old_esem_cmd_data;
    dbal_enum_value_field_esem_app_db_id_e native_ac_esem_app_db, esi_esem_app_db;

    uint32 l2vpn_flags = l2vpn_info->flags;
    uint32 mpls_port_flags = l2vpn_info->mpls_port->flags;
    uint32 mpls_port_flags2 = l2vpn_info->mpls_port->flags2;
    uint32 mpls_port_egress_label_flags2 = l2vpn_info->mpls_port->egress_label.flags2;
    dnx_port_esem_cmd_info_t esem_cmd_info;

    SHR_FUNC_INIT_VARS(unit);

    esem_cmd_info.nof_accesses = 0;

    /** Decide the native AC in LIF scope or network scope*/
    if (_SHR_IS_FLAG_SET(mpls_port_flags2, BCM_MPLS_PORT2_PLATFORM_NAMESPACE))
    {
        native_ac_esem_app_db = DBAL_ENUM_FVAL_ESEM_APP_DB_ID_FODO_NAMESPACE_CTAG;
    }
    else
    {
        native_ac_esem_app_db = DBAL_ENUM_FVAL_ESEM_APP_DB_ID_FODO_OUTLIF;
    }

    if (!_SHR_IS_FLAG_SET(l2vpn_flags, DNX_MPLS_L2VPN_FLAG_EGRESS_IML))
    {
        /*
         * Exchanging for the proper esem access cmd for PWE tag/raw mode.
         * Note: we always need a ETPS entry for native even in raw mode(which won't use it).
         */
        esem_default_result_profile = dnx_data_esem.default_result_profile.default_native_get(unit);

        /** Use the original default result profile for PWE.*/
        if (_SHR_IS_FLAG_SET(mpls_port_flags, BCM_MPLS_PORT_REPLACE))
        {
            int esem_access_idx;

            SHR_IF_ERR_EXIT(dnx_port_esem_cmd_data_sw_get(unit, old_esem_cmd, &old_esem_cmd_data, NULL));
            for (esem_access_idx = ESEM_ACCESS_IF_1; esem_access_idx < ESEM_ACCESS_IF_COUNT; esem_access_idx++)
            {
                if (old_esem_cmd_data.esem[esem_access_idx].valid)
                {
                    esem_default_result_profile = old_esem_cmd_data.esem[esem_access_idx].default_result_profile;
                    break;
                }
            }
        }

        SHR_IF_ERR_EXIT(dnx_port_esem_cmd_access_add(unit, 0, ESEM_ACCESS_TYPE_ETH_NATIVE_AC,
                                                     native_ac_esem_app_db, esem_default_result_profile,
                                                     &esem_cmd_info));

        /** Do the exchanging.*/
        SHR_IF_ERR_EXIT(dnx_port_esem_cmd_exchange(unit, 0, esem_cmd_size, 0,
                                                   &esem_cmd_info, old_esem_cmd, new_esem_cmd,
                                                   esem_cmd_data, esem_cmd_profile_first_reference,
                                                   esem_cmd_profile_last_reference));
    }
    else
    {
        /** Decide the ESI in LIF scope or port scope*/
        if (_SHR_IS_FLAG_SET(mpls_port_egress_label_flags2, BCM_MPLS_EGRESS_LABEL_FLAGS2_ESI_INTF_NAMESPACE))
        {
            esi_esem_app_db = DBAL_ENUM_FVAL_ESEM_APP_DB_ID_INLIF_NAMESPACE;
        }
        else
        {
            esi_esem_app_db = DBAL_ENUM_FVAL_ESEM_APP_DB_ID_SSP_NAMESPACE;
        }

        /*
         * Exchanging for the proper esem access cmd for dual home.
         * Do the exchange for native tag encapsulation first.
         */
        if (_SHR_IS_FLAG_SET(mpls_port_flags, BCM_MPLS_PORT_REPLACE))
        {
            /** In case of origin is not IML, use the original default result profile for PWE.*/
            *new_esem_cmd = old_esem_cmd;
        }
        else
        {
            SHR_IF_ERR_EXIT(dnx_port_esem_cmd_access_add(unit, 0, ESEM_ACCESS_TYPE_ETH_NATIVE_AC,
                                                         native_ac_esem_app_db,
                                                         dnx_data_esem.default_result_profile.default_native_get(unit),
                                                         &esem_cmd_info));

            SHR_IF_ERR_EXIT(dnx_port_esem_cmd_exchange(unit, 0, esem_cmd_size, 0,
                                                       &esem_cmd_info, old_esem_cmd, new_esem_cmd,
                                                       esem_cmd_data, esem_cmd_profile_first_reference,
                                                       esem_cmd_profile_last_reference));
        }

        /** Update the esem access cmd for native tag encapsulation. */
        SHR_IF_ERR_EXIT(dnx_port_esem_cmd_access_add(unit, 0, ESEM_ACCESS_TYPE_DUAL_HOME,
                                                     esi_esem_app_db,
                                                     dnx_data_esem.default_result_profile.default_dual_homing_get(unit),
                                                     &esem_cmd_info));

        SHR_IF_ERR_EXIT(dnx_port_esem_cmd_exchange(unit,
                                                   DNX_PORT_ESEM_CMD_UPDATE,
                                                   esem_cmd_size, 0,
                                                   &esem_cmd_info,
                                                   *new_esem_cmd, new_esem_cmd, esem_cmd_data,
                                                   esem_cmd_profile_first_reference, esem_cmd_profile_last_reference));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief Reads the network group ID from the out lif profile.
 */
static shr_error_e
dnx_mpls_l2vpn_out_network_group_read(
    int unit,
    int out_lif_profile,
    dnx_mpls_l2vpn_info_t * l2vpn_info)
{
    etpp_out_lif_profile_info_t out_lif_profile_info;

    SHR_FUNC_INIT_VARS(unit);

    etpp_out_lif_profile_info_t_init(unit, &out_lif_profile_info);
    SHR_IF_ERR_EXIT(dnx_etpp_out_lif_profile_get_data(unit, out_lif_profile, &out_lif_profile_info));
    l2vpn_info->mpls_port->network_group_id = out_lif_profile_info.out_lif_orientation;

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_mpls_l2vpn_add_egress_only(
    int unit,
    dnx_mpls_l2vpn_info_t * l2vpn_info)
{
    int global_lif = 0, local_outlif = 0, gport_id = 0;
    dnx_mpls_encap_t encap_info, encap_info_orig;
    bcm_mpls_egress_label_t label_array[2], label_array_orig[2];
    uint8 ttl_pipe_profile_first_reference = FALSE;
    uint8 ttl_pipe_profile_last_reference = FALSE;
    uint8 qos_pipe_profile_first_reference = FALSE;
    uint8 qos_pipe_profile_last_reference = FALSE;
    uint8 esem_cmd_profile_first_reference = FALSE;
    uint8 esem_cmd_profile_last_reference = FALSE;
    uint8 out_lif_profile_last_reference = FALSE;
    uint8 is_replace;
    int old_esem_cmd;
    dnx_esem_cmd_data_t esem_cmd_data;
    dnx_esem_cmd_suffix_size_t esem_size;
    lif_table_mngr_outlif_info_t outlif_info;
    uint32 entry_handle_id, entry_handle_id_orig;
    bcm_encap_access_t encap_access;
    dnx_egress_headers_profile_mngr_info_t headers_profile_mngr_info;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_mpls_l2vpn_add_egress_only_verify(unit, l2vpn_info));

    sal_memset(&esem_cmd_data, 0, sizeof(esem_cmd_data));

    /*
     * SW allocations
     */
    /** allocate global lifs or retrieve in case of replace */
    SHR_IF_ERR_EXIT(dnx_mpls_l2vpn_egress_lif_get_allocation_or_fill(unit, l2vpn_info, &global_lif, &local_outlif));

    l2vpn_info->mpls_port->encap_id = global_lif;
    BCM_GPORT_SUB_TYPE_LIF_SET(gport_id, BCM_GPORT_SUB_TYPE_LIF_EXC_EGRESS_ONLY, global_lif);
    BCM_GPORT_MPLS_PORT_ID_SET(l2vpn_info->mpls_port->mpls_port_id, gport_id);

    /** get EEDB entry to be replaced */
    dnx_mpls_encap_t_init(unit, &encap_info_orig);
    bcm_mpls_egress_label_t_init(&label_array_orig[0]);
    bcm_mpls_egress_label_t_init(&label_array_orig[1]);

    is_replace = _SHR_IS_FLAG_SET(l2vpn_info->mpls_port->flags, BCM_MPLS_PORT_REPLACE);
    if (is_replace)
    {
        lif_table_mngr_outlif_info_t orig_lif_info;
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC
                        (unit, (l2vpn_info->type == MPLS_L2VPN_TYPE_EVPN) ? DBAL_TABLE_EEDB_EVPN : DBAL_TABLE_EEDB_PWE,
                         &entry_handle_id_orig));
        SHR_IF_ERR_EXIT(dnx_lif_table_mngr_get_outlif_info(unit, local_outlif, entry_handle_id_orig, &orig_lif_info));
        encap_info_orig.label_array = label_array_orig;

        SHR_IF_ERR_EXIT(dnx_mpls_lif_table_manager_to_encap_info
                        (unit, entry_handle_id_orig, &orig_lif_info, &encap_info_orig));
        old_esem_cmd = encap_info_orig.esem_command_profile;

        if (l2vpn_info->type == MPLS_L2VPN_TYPE_EVPN)
        {
            /*
             * Nwk-Group-ID is set through another API for EVPN. When replacing the object, need to make sure the
             * Nwk-Group-ID is not being run over.
             */
            SHR_IF_ERR_EXIT(dnx_mpls_l2vpn_out_network_group_read(unit, encap_info_orig.out_lif_profile, l2vpn_info));
        }
    }
    else
    {
        old_esem_cmd = dnx_data_esem.access_cmd.no_action_get(unit);
    }

    /** Fill encapsulation info */
    dnx_mpls_encap_t_init(unit, &encap_info);

    encap_access = l2vpn_info->mpls_port->egress_label.encap_access;
    if (encap_access == bcmEncapAccessInvalid)
    {
        encap_access = bcmEncapAccessTunnel1;
    }
    SHR_IF_ERR_EXIT(dnx_lif_lib_encap_access_to_logical_phase_convert(unit, encap_access, &encap_info.logical_phase));

    if (l2vpn_info->type == MPLS_L2VPN_TYPE_EVPN)
    {
        _SHR_GPORT_TUNNEL_ID_SET(l2vpn_info->mpls_port->mpls_port_id, global_lif);
    }
    else
    {
        BCM_GPORT_SUB_TYPE_LIF_SET(gport_id, BCM_GPORT_SUB_TYPE_LIF_EXC_EGRESS_ONLY, global_lif);
        BCM_GPORT_MPLS_PORT_ID_SET(l2vpn_info->mpls_port->mpls_port_id, gport_id);
    }
    /** add PWE label to encap db*/
    sal_memcpy(&label_array[0], &l2vpn_info->mpls_port->egress_label, sizeof(bcm_mpls_egress_label_t));
    label_array[0].l3_intf_id = l2vpn_info->mpls_port->egress_tunnel_if;

    encap_info.label_array = label_array;
    encap_info.labels_nof = 1;

    /*
     * in case of IOAM over VPLS, only one field DUAL_HOMING exists 
     */
    if (!_SHR_IS_FLAG_SET(encap_info.label_array[0].flags, BCM_MPLS_EGRESS_LABEL_ALTERNATE_MARKING))
    {
        /** Set protection details */
        if (_SHR_IS_FLAG_SET(l2vpn_info->mpls_port->flags2, BCM_MPLS_PORT2_EGRESS_PROTECTION)
            && DNX_FAILOVER_IS_PROTECTION_ENABLED(l2vpn_info->mpls_port->egress_failover_id))
        {
            encap_info.protection_path = (l2vpn_info->mpls_port->egress_failover_port_id) ? 0 : 1;
            BCM_FAILOVER_ID_GET(encap_info.protection_pointer, l2vpn_info->mpls_port->egress_failover_id);
        }

        /** Exchange for an esem access command.*/
        if (_SHR_IS_FLAG_SET(l2vpn_info->flags, DNX_MPLS_L2VPN_FLAG_EGRESS_IML))
        {
            /**ESEM_CMD Field size is 4*/
            esem_size = DNX_ALGO_ESEM_CMD_SUFFIX_SIZE_BIT_4;
        }
        else
        {
            /**ESEM_CMD Field size is 3*/
            esem_size = DNX_ALGO_ESEM_CMD_SUFFIX_SIZE_BIT_3;
        }
        if (!_SHR_IS_FLAG_SET(l2vpn_info->mpls_port->flags2, BCM_MPLS_PORT2_KEEP_TTL))
        {
            SHR_IF_ERR_EXIT(dnx_mpls_l2vpn_egress_lif_esem_cmd_sw_alloc(unit, l2vpn_info,
                                                                        esem_size,
                                                                        old_esem_cmd,
                                                                        &(encap_info.esem_command_profile),
                                                                        &esem_cmd_data,
                                                                        &esem_cmd_profile_first_reference,
                                                                        &esem_cmd_profile_last_reference));
        }

        if (l2vpn_info->mpls_port->flags & BCM_MPLS_PORT_CONTROL_WORD)
        {
            encap_info.has_cw = 1;
        }
        if (_SHR_IS_FLAG_SET(l2vpn_info->flags, DNX_MPLS_L2VPN_FLAG_EGRESS_IML))
        {
            encap_info.is_iml = 1;
        }

        /** ESEM name space is required for encapsulation retrival.*/
        if (_SHR_IS_FLAG_SET(l2vpn_info->flags, DNX_MPLS_L2VPN_FLAG_EGRESS_IML) ||
            _SHR_IS_FLAG_SET(l2vpn_info->mpls_port->flags2, BCM_MPLS_PORT2_PLATFORM_NAMESPACE))
        {
            encap_info.require_name_space = 1;
        }

        /** allocate lif, TTL and qos profiles if needed */
        SHR_IF_ERR_EXIT(dnx_mpls_egress_lif_ttl_qos_profiles_sw_allocate
                        (unit, _SHR_IS_FLAG_SET(l2vpn_info->mpls_port->flags, BCM_MPLS_PORT_REPLACE),
                         l2vpn_info->mpls_port->network_group_id, DBAL_TABLE_EEDB_PWE, &encap_info_orig, &encap_info,
                         &ttl_pipe_profile_first_reference, &ttl_pipe_profile_last_reference,
                         &qos_pipe_profile_first_reference, &qos_pipe_profile_last_reference,
                         &out_lif_profile_last_reference));
        if (l2vpn_info->mpls_port->flags2 & BCM_MPLS_PORT2_NO_TPID_CLASS)
        {
            encap_info.skip_llvp_profile = 1;
        }
        else
        {
            if (l2vpn_info->mpls_port->flags & BCM_MPLS_PORT_REPLACE)
            {
                /** Get orig Egress Native AC llvp profile ID */
                encap_info.out_lif_llvp_profile = encap_info_orig.out_lif_llvp_profile;
            }
            else
            {
                /** Get default Egress Native AC llvp profile ID */
                encap_info.out_lif_llvp_profile =
                    dnx_data_port_pp.general.default_egress_native_ac_llvp_profile_id_get(unit);
            }
        }
    }

    /** calculate lif additional_headers_profile*/
    SHR_IF_ERR_EXIT(dnx_mpls_encap_additional_header_profile_alloc
                    (unit, is_replace, &encap_info_orig, &encap_info, &headers_profile_mngr_info));

    /*
     * HW allocations
     */
    /** Write to HW if new TTL profile was allocated */
    if (ttl_pipe_profile_first_reference)
    {
        SHR_IF_ERR_EXIT(dnx_qos_egress_ttl_profile_hw_set
                        (unit, encap_info.ttl_pipe_profile, (uint32) encap_info.label_array[0].ttl));
    }

    if (qos_pipe_profile_first_reference)
    {
        /*
         * only one label
         */
        uint32 nwk_qos = encap_info.label_array[0].exp;
        SHR_IF_ERR_EXIT(dnx_qos_egress_network_qos_pipe_profile_set(unit, encap_info.nwk_qos_id, nwk_qos, nwk_qos, 0));
    }

    /** Write to HW if new esem cmd profile was allocated */
    if (esem_cmd_profile_first_reference)
    {
        SHR_IF_ERR_EXIT(dnx_port_esem_cmd_data_hw_set(unit, encap_info.esem_command_profile, &esem_cmd_data));
    }

    /*
     * Fill outlif info struct with all fields relevant info
     */
    if (l2vpn_info->type == MPLS_L2VPN_TYPE_EVPN)
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EEDB_EVPN, &entry_handle_id));
    }
    else
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EEDB_PWE, &entry_handle_id));
    }
    SHR_IF_ERR_EXIT(dnx_mpls_encap_to_lif_table_manager_info(unit, entry_handle_id, &encap_info, &outlif_info));
    outlif_info.global_lif = global_lif;

    /*
     * Find result type, allocate lif and write to HW
     */
    if (is_replace)
    {
        outlif_info.flags |= LIF_TABLE_MNGR_LIF_INFO_REPLACE;
    }
    SHR_IF_ERR_EXIT(dnx_lif_table_mngr_allocate_local_outlif_and_set_hw
                    (unit, entry_handle_id, &local_outlif, &outlif_info));
    /*
     * After new entry values are saved to HW delete redundant old values from HW
     */
    /** clear from HW the TTL profile */
    if (ttl_pipe_profile_last_reference)
    {
        SHR_IF_ERR_EXIT(dnx_qos_egress_ttl_profile_hw_clear(unit, encap_info_orig.ttl_pipe_profile));
    }

    if (qos_pipe_profile_last_reference)
    {
        SHR_IF_ERR_EXIT(dnx_qos_egress_network_qos_pipe_profile_hw_clear(unit, encap_info_orig.nwk_qos_id));
    }

    if (encap_info_orig.out_lif_profile_valid && out_lif_profile_last_reference)
    {
        /** Clear the old ETPP outlif profile in case there are no more references to it*/
        SHR_IF_ERR_EXIT(dnx_etpp_out_lif_profile_hw_clear(unit, encap_info_orig.out_lif_profile));
    }

    /** clear from HW the esem cmd profile */
    if (esem_cmd_profile_last_reference)
    {
        SHR_IF_ERR_EXIT(dnx_port_esem_cmd_data_clear(unit, encap_info_orig.esem_command_profile));
    }

    /** Clear the header profile table if needed.*/
    SHR_IF_ERR_EXIT(egress_additional_headers_profile_last_clear(unit, &headers_profile_mngr_info));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_mpls_l2vpn_get_egress_only(
    int unit,
    dnx_mpls_l2vpn_info_t * l2vpn_info)
{
    bcm_gport_t gport_id;
    dnx_algo_gpm_gport_hw_resources_t gport_hw_resources;
    uint32 lif_flags = 0;
    dnx_mpls_encap_t encap_info;
    bcm_mpls_egress_label_t label_array[2];
    lif_table_mngr_outlif_info_t outlif_info;
    uint32 entry_handle_id;
    global_lif_alloc_info_t alloc_info = { 0 };

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    bcm_mpls_egress_label_t_init(&label_array[0]);
    bcm_mpls_egress_label_t_init(&label_array[1]);

    /** get local and global out lifs */
    lif_flags |= DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_EGRESS | DNX_ALGO_GPM_GPORT_HW_RESOURCES_GLOBAL_LIF_EGRESS;
    gport_id = l2vpn_info->mpls_port->mpls_port_id;
    SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_to_hw_resources
                    (unit, l2vpn_info->mpls_port->mpls_port_id, lif_flags, &gport_hw_resources));

    /*
     * Initialize the structure
     */
    bcm_mpls_port_t_init(l2vpn_info->mpls_port);
    l2vpn_info->mpls_port->mpls_port_id = gport_id;
    BCM_ENCAP_ID_SET(l2vpn_info->mpls_port->encap_id, gport_hw_resources.global_out_lif);
    l2vpn_info->mpls_port->flags2 |= BCM_MPLS_PORT2_EGRESS_ONLY;

    /** get PWE label from encap db*/
    if (l2vpn_info->type == MPLS_L2VPN_TYPE_EVPN)
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EEDB_EVPN, &entry_handle_id));
    }
    else
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EEDB_PWE, &entry_handle_id));
    }
    SHR_IF_ERR_EXIT(dnx_lif_table_mngr_get_outlif_info
                    (unit, gport_hw_resources.local_out_lif, entry_handle_id, &outlif_info));
    dnx_mpls_encap_t_init(unit, &encap_info);
    bcm_mpls_egress_label_t_init(&label_array[0]);
    bcm_mpls_egress_label_t_init(&label_array[1]);
    encap_info.label_array = label_array;

    SHR_IF_ERR_EXIT(dnx_mpls_lif_table_manager_to_encap_info(unit, entry_handle_id, &outlif_info, &encap_info));

    if (encap_info.label_array[0].egress_failover_id != dnx_data_failover.path_select.egr_no_protection_get(unit))
    {
        BCM_FAILOVER_SET(l2vpn_info->mpls_port->egress_failover_id,
                         encap_info.label_array[0].egress_failover_id, BCM_FAILOVER_TYPE_ENCAP);
        l2vpn_info->mpls_port->egress_failover_port_id = encap_info.label_array[0].egress_failover_if_id ? 0 : 1;
        l2vpn_info->mpls_port->flags2 |= BCM_MPLS_PORT2_EGRESS_PROTECTION;
    }

    if (encap_info.has_cw)
    {
        l2vpn_info->mpls_port->flags |= BCM_MPLS_PORT_CONTROL_WORD;
    }
    if (encap_info.is_iml)
    {
        l2vpn_info->flags |= DNX_MPLS_L2VPN_FLAG_EGRESS_IML;
    }
    if (encap_info.skip_llvp_profile)
    {
        l2vpn_info->mpls_port->flags2 |= BCM_MPLS_PORT2_NO_TPID_CLASS;
    }
    if (encap_info.esem_command_profile == 0)
    {
        l2vpn_info->mpls_port->flags2 |= BCM_MPLS_PORT2_KEEP_TTL;
    }

    l2vpn_info->mpls_port->egress_tunnel_if = encap_info.label_array[0].l3_intf_id;
    encap_info.label_array[0].l3_intf_id = DNX_MPLS_CFG_LIF_NULL_VALUE;

    /*
     * Reprieve exp value from QOS table
     * nwk_pipe and nwk_pipe_mapped are 1:1 mapping (equal)
     */
    if ((encap_info.label_array[0].egress_qos_model.egress_qos == bcmQosEgressModelPipeNextNameSpace) ||
        (encap_info.label_array[0].egress_qos_model.egress_qos == bcmQosEgressModelPipeMyNameSpace))
    {
        uint8 nwk_pipe, nwk_pipe_mapped, dp_pipe_mapped;
        SHR_IF_ERR_EXIT(dnx_qos_egress_network_qos_pipe_profile_attr_get(unit, encap_info.nwk_qos_id,
                                                                         &nwk_pipe, &nwk_pipe_mapped, &dp_pipe_mapped));
        encap_info.label_array[0].exp = DNX_QOS_IDX_NWK_QOS_GET_EXP0(nwk_pipe);
        if (encap_info.labels_nof > 1)
        {
            encap_info.label_array[1].exp = DNX_QOS_IDX_NWK_QOS_GET_EXP1(nwk_pipe);
        }
    }

    SHR_IF_ERR_EXIT(dnx_algo_global_out_lif_alloc_info_get
                    (unit, gport_hw_resources.global_out_lif, DNX_ALGO_LIF_EGRESS, &alloc_info));
    label_array[0].estimated_encap_size = alloc_info.bta;

    /*
     * For VPLS egress protection, mpls_port.egress_failover_id and mpls_port.egress_failover_port_id 
     * are used for protect_pointer and protect_path. So needn't set protection parameters to mpls_port.egress_label.
     */
    sal_memcpy(&l2vpn_info->mpls_port->egress_label, &label_array[0], sizeof(bcm_mpls_egress_label_t));
    l2vpn_info->mpls_port->egress_label.egress_failover_id = 0;
    l2vpn_info->mpls_port->egress_label.egress_failover_if_id = 0;

    /** Get outlif profile info */
    SHR_IF_ERR_EXIT(dnx_mpls_outlif_profile_to_mpls_port_info(unit, encap_info.out_lif_profile, l2vpn_info->mpls_port));

    /** Get native ac info */
    SHR_IF_ERR_EXIT(dnx_mpls_esem_cmd_profile_to_mpls_port_info(unit, &encap_info, l2vpn_info->mpls_port));

    SHR_IF_ERR_EXIT(dnx_lif_lib_logical_phase_to_encap_access_convert
                    (unit, gport_hw_resources.logical_phase, &(l2vpn_info->mpls_port->egress_label.encap_access)));
    /*
     * Whenever the returned value is the same as the Invalid, the Invalid value is returned
     */
    if (l2vpn_info->mpls_port->egress_label.encap_access == bcmEncapAccessTunnel1)
    {
        l2vpn_info->mpls_port->egress_label.encap_access = bcmEncapAccessInvalid;
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_mpls_l2vpn_delete_egress_only(
    int unit,
    bcm_gport_t mpls_l2vpn_id)
{
    dnx_algo_gpm_gport_hw_resources_t gport_hw_resources;
    uint32 lif_flags = 0;
    int new_out_lif_profile;
    etpp_out_lif_profile_info_t out_lif_profile_info;
    dnx_mpls_encap_t encap_info;
    uint8 ttl_last_reference = 0;
    uint8 qos_last_reference = 0;
    uint8 esem_cmd_last_reference = 0;
    bcm_mpls_egress_label_t label_array[2];
    lif_table_mngr_outlif_info_t outlif_info;
    uint32 entry_handle_id;
    uint8 is_last = 0;
    int rv = _SHR_E_NONE;
    dbal_table_field_info_t field_info;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** get local and global out lifs */
    lif_flags |= DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_EGRESS | DNX_ALGO_GPM_GPORT_HW_RESOURCES_GLOBAL_LIF_EGRESS;
    SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_to_hw_resources(unit, mpls_l2vpn_id, lif_flags, &gport_hw_resources));

    /*
     * Get MPLS encap info
     */
    /** get PWE label from encap db*/
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, gport_hw_resources.outlif_dbal_table_id, &entry_handle_id));
    SHR_IF_ERR_EXIT(dnx_lif_table_mngr_get_outlif_info
                    (unit, gport_hw_resources.local_out_lif, entry_handle_id, &outlif_info));
    dnx_mpls_encap_t_init(unit, &encap_info);
    bcm_mpls_egress_label_t_init(&label_array[0]);
    bcm_mpls_egress_label_t_init(&label_array[1]);
    encap_info.label_array = label_array;

    SHR_IF_ERR_EXIT(dnx_mpls_lif_table_manager_to_encap_info(unit, entry_handle_id, &outlif_info, &encap_info));

    /*
     * Clear SW tables
     */
    if (encap_info.label_array[0].egress_qos_model.egress_ttl == bcmQosEgressModelPipeMyNameSpace)
    {
        SHR_IF_ERR_EXIT(algo_qos_db.qos_egress_ttl_pipe_profile.free_single
                        (unit, encap_info.ttl_pipe_profile, &ttl_last_reference));
    }

    if ((encap_info.label_array[0].egress_qos_model.egress_qos == bcmQosEgressModelPipeNextNameSpace) ||
        (encap_info.label_array[0].egress_qos_model.egress_qos == bcmQosEgressModelPipeMyNameSpace))
    {
        SHR_IF_ERR_EXIT(dnx_qos_egress_network_qos_pipe_profile_free(unit, encap_info.nwk_qos_id, &qos_last_reference));
    }

    rv = dbal_tables_field_info_get_no_err(unit, gport_hw_resources.outlif_dbal_table_id, DBAL_FIELD_OUT_LIF_PROFILE,
                                           FALSE, gport_hw_resources.outlif_dbal_result_type, INST_SINGLE, &field_info);
    if (rv == _SHR_E_NONE)
    {
        /*
         * Free outlif profile:
         * It is done by calling exchange function with default profile data:
         */
        etpp_out_lif_profile_info_t_init(unit, &out_lif_profile_info);
        SHR_IF_ERR_EXIT(dnx_etpp_out_lif_profile_exchange
                        (unit, gport_hw_resources.outlif_dbal_table_id, 0, &out_lif_profile_info,
                         encap_info.out_lif_profile, &new_out_lif_profile, &is_last));
        if (new_out_lif_profile != DNX_OUT_LIF_PROFILE_DEFAULT)
        {
            SHR_ERR_EXIT(_SHR_E_INTERNAL,
                         "Error! Something is wrong! on freeing oulif_profile, didn't get default out lif profile, default outlif profile = %d, new_out_lif_profile = %d",
                         DNX_OUT_LIF_PROFILE_DEFAULT, new_out_lif_profile);
        }
        if (is_last)
        {
            /** Clear the old ETPP outlif profile as there are no more references to it*/
            SHR_IF_ERR_EXIT(dnx_etpp_out_lif_profile_hw_clear(unit, encap_info.out_lif_profile));
        }
    }
    /*
     * Free ESEM cmd
     */
    SHR_IF_ERR_EXIT(dnx_port_esem_cmd_free(unit, encap_info.esem_command_profile, &esem_cmd_last_reference));

    /*
     * Free ETPP additional_headers_profile
     */
    SHR_IF_ERR_EXIT(dnx_mpls_encap_additional_header_profile_free(unit, &encap_info));

    /*
     * Clear HW tables
     */
    /** delete PWE label from encap db*/
    /** Free Lif table and local LIF allocation */
    lif_flags = 0;
    SHR_IF_ERR_EXIT(dnx_lif_table_mngr_outlif_info_clear(unit, gport_hw_resources.local_out_lif, lif_flags));

    /** delete global lif */
    SHR_IF_ERR_EXIT(dnx_algo_global_lif_allocation_free(unit, DNX_ALGO_LIF_EGRESS, gport_hw_resources.global_out_lif));

    /** clear from HW the TTL profile */
    if (ttl_last_reference)
    {
        SHR_IF_ERR_EXIT(dnx_qos_egress_ttl_profile_hw_clear(unit, encap_info.ttl_pipe_profile));
    }
    if (qos_last_reference)
    {
        SHR_IF_ERR_EXIT(dnx_qos_egress_network_qos_pipe_profile_hw_clear(unit, encap_info.nwk_qos_id));
    }

    /** clear ESEM cmd from hw table */
    if (esem_cmd_last_reference)
    {
        SHR_IF_ERR_EXIT(dnx_port_esem_cmd_data_clear(unit, encap_info.esem_command_profile));
    }

    /** Release out lif llvp profile*/
    /** if it is not default native ac llvp profile, need to "free" it at the template manager */
    if ((!encap_info.skip_llvp_profile) &&
        (encap_info.out_lif_llvp_profile !=
         dnx_data_port_pp.general.default_egress_native_ac_llvp_profile_id_get(unit)))
    {
        uint8 is_last;
        SHR_IF_ERR_EXIT(algo_port_pp_db.port_pp_tpid_profile_egress.free_single
                        (unit, encap_info.out_lif_llvp_profile, &is_last));

        if (is_last == TRUE)
        {
            /** Clear the HW: */
            SHR_IF_ERR_EXIT(dnx_port_tpid_class_set_egress_llvp_block_clear(unit, encap_info.out_lif_llvp_profile));
        }
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

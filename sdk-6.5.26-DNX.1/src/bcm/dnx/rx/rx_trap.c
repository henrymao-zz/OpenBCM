/** \file rx_trap.c
 * 
 *
 * RX procedures for DNX.
 *
 * Here add DESCRIPTION.
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_RX
/*
 * Include files.
 * {
 */
#include <soc/sand/shrextend/shrextend_debug.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_device.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_field.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_flow.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_headers.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_mpls.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_multicast.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_oam.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_switch.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_l2.h>
#include <include/bcm_int/dnx/algo/rx/algo_rx.h>
#include <bcm_int/dnx/cmn/dnxcmn.h>
#include <include/bcm_int/dnx/algo/algo_gpm.h>
#include <include/bcm_int/dnx/algo/port/algo_port_mgmt.h>
#include <include/bcm_int/dnx/algo/lif_mngr/lif_mngr_api.h>
#include <include/bcm_int/dnx/field/field_map.h>
#include <include/bcm_int/dnx/rx/rx_trap.h>
#include <include/bcm_int/dnx/rx/rx_trap_map.h>
#include <include/bcm_int/dnx/port/port.h>
#include <include/bcm_int/dnx/port/port_pp.h>
#include <include/bcm_int/dnx/lif/in_lif_profile.h>
#include <include/bcm_int/dnx/oam/oam_punt_and_protection.h>
#include <include/bcm_int/dnx/mirror/mirror.h>
#include <include/bcm_int/dnx/field/field_context.h>
#include <include/bcm/trunk.h>
#include <src/bcm/dnx/mirror/mirror_profile_alloc.h>
#include <src/bcm/dnx/trunk/trunk_sw_db.h>
#include <src/bcm/dnx/rx/rx_trap_map_dispatch.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/access/algo_rx_access.h>
#include <soc/dnx/dbal/dbal.h>
#include <soc/dnx/dnx_err_recovery_manager.h>
#include <soc/dnxc/dnxc_wb_test_utils.h>
#include <soc/dnxc/drv_dnxc_utils.h>
#include <soc/cmicx.h>
#include <soc/mem.h>
#include <src/bcm/dnx/rx/rx_trap_v1.h>

/*
 * }
 */

/*
 * Macros and defines for rx trap
 * {
 */

/*
 * }
 */

/*
 * Globals
 * {
 */

/*
 * } Globals
 */

/*
 * Functions
 * {
 */

/**
 * \brief
 * This function encodes a enum field. encode enum means
 * translate its SW value to HW value
 */
extern shr_error_e dbal_field_types_encode_enum(
    int unit,
    dbal_field_types_defs_e field_type,
    uint32 sw_field_val,
    uint32 *hw_field_val);

/**
* \brief
*  Init the parameters of dnx_rx_trap_erpp_config_t to default
*  values
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [out] erpp_config_p  -  Pointer type of dnx_rx_trap_erpp_config_t \n
*           \b As \b output - \n
*           This pocedure loads pointed memory by defualt value
*           of dnx_rx_trap_erpp_config_t structure
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_erpp_config_t_init(
    int unit,
    dnx_rx_trap_erpp_config_t * erpp_config_p)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(erpp_config_p, _SHR_E_PARAM, "erpp_config_p");

    /*
     * Currently all values are reset to zero.
     */
    sal_memset(erpp_config_p, 0, sizeof(dnx_rx_trap_erpp_config_t));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function sets the recycle command in HW according to recycle_cmd_config.
* \par DIRECT INPUT:
*   \param [in] unit      -  unit id
*   \param [in] core_id      -  core id
*   \param [in] recycle_cmd  - recycle command (4b)
*   \param [in] recycle_cmd_config      -  recycle command configuration: trap_id and strength
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_etpp_recycle_cmd_hw_set(
    int unit,
    uint32 core_id,
    uint8 recycle_cmd,
    dnx_rx_trap_recycle_cmd_config_t * recycle_cmd_config)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_FWD_RCY_CMD_MAP, &entry_handle_id));

    /*
     * Keys
     */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_RECYCLE_COMMAND_ID, recycle_cmd);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);

    /*
     * Values
     */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, INST_SINGLE,
                                 recycle_cmd_config->ingress_trap_id);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, INST_SINGLE,
                                recycle_cmd_config->recycle_strength);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function allocates a recycle command according to given configuration.
* \par DIRECT INPUT:
*   \param [in] unit      -  unit id
*   \param [in] old_recycle_cmd  -old recycle command configured for trap (4b)
*   \param [in] recycle_cmd_config_p      -  recycle command configuration
*   \param [in] new_recycle_cmd_p      -  new recycle command allocated
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
dnx_rx_trap_etpp_recycle_cmd_profile_set(
    int unit,
    uint8 old_recycle_cmd,
    dnx_rx_trap_recycle_cmd_config_t * recycle_cmd_config_p,
    int *new_recycle_cmd_p)
{
    uint8 is_first = 0, is_last = 0;
    dnx_rx_trap_recycle_cmd_config_t recycle_cmd_clear_config;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(algo_rx_db.trap_recycle_cmd.exchange
                    (unit, 0, recycle_cmd_config_p, old_recycle_cmd, NULL, new_recycle_cmd_p, &is_first, &is_last));

    /** If this is the first time the recycle command is allocated, set it in HW */
    if (is_first)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_recycle_cmd_hw_set
                        (unit, BCM_CORE_ALL, *new_recycle_cmd_p, recycle_cmd_config_p));
    }

    /** If this is the last trap pointing to this recycle command, clear profile from HW */
    if (is_last)
    {
        recycle_cmd_clear_config.ingress_trap_id = DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_NONE;
        recycle_cmd_clear_config.recycle_strength = 0;
        SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_recycle_cmd_hw_set
                        (unit, BCM_CORE_ALL, old_recycle_cmd, &recycle_cmd_clear_config));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function gets the recycle command from HW .
* \par DIRECT INPUT:
*   \param [in] unit      -  unit id
*   \param [in] core_id      -  core id
*   \param [in] recycle_cmd  - recycle command (4b)
*   \param [out] recycle_cmd_config      -  recycle command configuration: trap_id and strength
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
dnx_rx_trap_etpp_recycle_cmd_hw_get(
    int unit,
    uint32 core_id,
    uint8 recycle_cmd,
    dnx_rx_trap_recycle_cmd_config_t * recycle_cmd_config)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_FWD_RCY_CMD_MAP, &entry_handle_id));

    /*
     * Keys
     */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_RECYCLE_COMMAND_ID, recycle_cmd);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);

    /*
     * Values
     */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, INST_SINGLE,
                               &recycle_cmd_config->ingress_trap_id);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, INST_SINGLE,
                              &recycle_cmd_config->recycle_strength);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*   Maps a bcmRxTrapType to trap id, encoded  [trap_block | trap_class | trap_type] ,
* \par DIRECT INPUT:
*   \param [in] unit       -  Unit ID
*   \param [in] type       -  bcmRxTrapType.. some trap can have more then one id
*   \param [in] trap_id_p  - Pointer type of int. \n
*           \b As \b output - \n
*             Return the id for given trap type encoded with block and class
*               1) For ingress predefined traps the type is the index to Action table (IPPD_FWD_ACT_PROFILE)
                      Hence the block and class is 0 (DNX_RX_TRAP_BLOCK_INGRESS=0, DNX_RX_TRAP_CLASS_PREDEFINED=0)
*                    Thats also the reason why DNX_RX_TRAP_ID_SET not being called for ingress traps.
*               2) For other traps the type will be an internal enum
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * Trap id encoded [trap_block | trap_class | trap_type]
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_type_to_id(
    int unit,
    bcm_rx_trap_t type,
    int *trap_id_p)
{
    dnx_rx_trap_map_type_t trap_type_info;
    uint32 hw_value;
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(trap_id_p, _SHR_E_PARAM, "trap_id_p");

    sal_memset(&trap_type_info, 0, sizeof(dnx_rx_trap_map_type_t));
    SHR_IF_ERR_EXIT(dnx_rx_trap_type_map_info_get_dispatch(unit, type, &trap_type_info));

    if (trap_type_info.valid == FALSE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Trap Type = %d , not supported \n", type);
    }

    if (trap_type_info.trap_block != DNX_RX_TRAP_BLOCK_INGRESS)
    {
        /** Encoding only done for none Ingress, since we return SW id*/
        *trap_id_p = DNX_RX_TRAP_ID_SET(trap_type_info.trap_block, trap_type_info.trap_class, trap_type_info.trap_id);

    }
    else
    {
        /**Ingress block MUST be zero since we return HW trap_id, same as not encoding,
                * To differentiate between User and predefined the actual id is used
                */
        *trap_id_p = trap_type_info.trap_id;

        SHR_IF_ERR_EXIT(dbal_fields_enum_hw_value_get(unit, DBAL_FIELD_INGRESS_TRAP_ID, *trap_id_p, &hw_value));
        if ((hw_value == 0) && (type != bcmRxTrapLinkLayerHeaderSizeErr))
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Trap bcmRxTrap%s is not supported on the current device \n",
                         trap_type_info.trap_name);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 *  See rx_trap.h for info
 */
shr_error_e
dnx_rx_trap_map_list(
    int unit,
    dnx_rx_trap_block_e trap_block,
    dnx_rx_trap_class_e trap_class,
    char **trap_descriptions,
    dnx_rx_trap_map_type_t ** trap_map_list_p,
    int *nof_traps_p)
{
    int i_trap = 0, nof_traps = 0;
    dnx_rx_trap_map_type_t *trap_map_list = NULL;
    dnx_rx_trap_map_type_t trap_type_info;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(trap_map_list_p, _SHR_E_PARAM, "trap_map_list_p");
    SHR_NULL_CHECK(nof_traps_p, _SHR_E_PARAM, "nof_traps_p");
    SHR_ALLOC_ERR_EXIT(trap_map_list, bcmRxTrapCount * sizeof(dnx_rx_trap_map_type_t), "trap_map_list", "%s%s%s",
                       "trap_map_list", EMPTY, EMPTY);

    sal_memset(&trap_type_info, 0, sizeof(dnx_rx_trap_map_type_t));

    for (i_trap = 0; i_trap < bcmRxTrapCount; i_trap++)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_type_map_info_get_dispatch(unit, i_trap, &trap_type_info));
        if (trap_type_info.valid == TRUE)
        {
            if ((trap_block == trap_type_info.trap_block) && (trap_class == trap_type_info.trap_class))
            {
                SHR_IF_ERR_EXIT(dnx_rx_trap_type_description_map_info_get_dispatch
                                (unit, i_trap, &trap_descriptions[nof_traps]));
                trap_map_list[nof_traps] = trap_type_info;
                nof_traps++;
            }
        }
    }

    for (i_trap = 0; i_trap < nof_traps; i_trap++)
    {
        sal_memcpy(&(*trap_map_list_p)[i_trap], &trap_map_list[i_trap], sizeof(dnx_rx_trap_map_type_t));
    }

    *nof_traps_p = nof_traps;

exit:
    SHR_FREE(trap_map_list);
    SHR_FUNC_EXIT;
}

/*
 *  See rx_trap.h for info
 */
shr_error_e
dnx_rx_trap_app_map_list(
    int unit,
    dnx_rx_trap_block_e trap_block,
    char **trap_descriptions,
    dnx_rx_trap_map_type_t ** trap_map_list_p,
    int *nof_traps_p)
{
    int i_trap = 0, nof_traps = 0;
    dnx_rx_trap_map_type_t *trap_map_list = NULL;
    dnx_rx_trap_map_type_t appl_trap_info;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(trap_map_list_p, _SHR_E_PARAM, "trap_map_list_p");
    SHR_NULL_CHECK(nof_traps_p, _SHR_E_PARAM, "nof_traps_p");
    SHR_ALLOC_ERR_EXIT(trap_map_list, bcmRxTrapCount * sizeof(dnx_rx_trap_map_type_t), "trap_map_list", "%s%s%s",
                       "trap_map_list", EMPTY, EMPTY);

    sal_memset(&appl_trap_info, 0, sizeof(dnx_rx_trap_map_type_t));

    for (i_trap = 0; i_trap < bcmRxTrapCount; i_trap++)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_appl_trap_map_info_get_dispatch(unit, i_trap, &appl_trap_info));
        if (appl_trap_info.valid == TRUE && trap_block == appl_trap_info.trap_block)
        {
            SHR_IF_ERR_EXIT(dnx_rx_trap_type_description_map_info_get_dispatch
                            (unit, i_trap, &trap_descriptions[nof_traps]));
            trap_map_list[nof_traps] = appl_trap_info;
            nof_traps++;
        }
    }

    for (i_trap = 0; i_trap < nof_traps; i_trap++)
    {
        sal_memcpy(&(*trap_map_list_p)[i_trap], &trap_map_list[i_trap], sizeof(dnx_rx_trap_map_type_t));
    }

    *nof_traps_p = nof_traps;

exit:
    SHR_FREE(trap_map_list);
    SHR_FUNC_EXIT;
}

/*
 *  See rx_trap.h for info
 */
shr_error_e
dnx_rx_trap_app_type_from_id_get(
    int unit,
    dnx_rx_trap_block_e trap_block,
    uint32 trap_id,
    bcm_rx_trap_t * trap_type_p)
{
    int i_trap = 0;
    dnx_rx_trap_map_type_t appl_trap_info;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&appl_trap_info, 0, sizeof(dnx_rx_trap_map_type_t));

    SHR_NULL_CHECK(trap_type_p, _SHR_E_PARAM, "trap_type_p");

    for (i_trap = 0; i_trap < bcmRxTrapCount; i_trap++)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_appl_trap_map_info_get_dispatch(unit, i_trap, &appl_trap_info));
        if (appl_trap_info.valid == TRUE &&
            appl_trap_info.trap_block == trap_block && appl_trap_info.trap_id == trap_id)
        {
            *trap_type_p = i_trap;
            break;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 *  See rx_trap.h for info
 */
shr_error_e
dnx_rx_trap_type_list(
    int unit,
    dnx_rx_trap_block_e trap_block,
    dnx_rx_trap_class_e trap_class,
    bcm_rx_trap_t ** trap_type_list_p,
    int *trap_type_nof_p)
{
    int i_trap = 0;
    uint32 nof_traps = 0;
    uint32 *trap_type_list = NULL;
    dnx_rx_trap_map_type_t trap_type_info;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(trap_type_list_p, _SHR_E_PARAM, "trap_type_list_p");
    SHR_NULL_CHECK(trap_type_nof_p, _SHR_E_PARAM, "trap_type_nof_p");
    sal_memset(&trap_type_info, 0, sizeof(dnx_rx_trap_map_type_t));

    SHR_ALLOC_ERR_EXIT(trap_type_list, bcmRxTrapCount * sizeof(uint32), "trap_type_list", "%s%s%s", "trap_type_list",
                       EMPTY, EMPTY);

    for (i_trap = 0; i_trap < bcmRxTrapCount; i_trap++)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_type_map_info_get_dispatch(unit, i_trap, &trap_type_info));
        if (trap_type_info.valid == TRUE)
        {
            if ((trap_block == trap_type_info.trap_block) && (trap_class == trap_type_info.trap_class))
            {
                trap_type_list[nof_traps] = i_trap;
                nof_traps++;
            }
        }
    }

    *trap_type_list_p = trap_type_list;
    *trap_type_nof_p = nof_traps;

exit:
    if (SHR_FUNC_ERR())
    {
        SHR_FREE(trap_type_list);
    }
    SHR_FUNC_EXIT;
}

/*
 *  See rx_trap.h for info
 */
shr_error_e
dnx_rx_trap_type_to_name(
    int unit,
    bcm_rx_trap_t trap_type,
    char *trap_name)
{
    dnx_rx_trap_map_type_t trap_type_info;
    dnx_rx_trap_map_type_t appl_trap_info;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(trap_name, _SHR_E_PARAM, "trap_name_p");

    if (trap_type >= bcmRxTrapCount)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid trap type %d\n", trap_type);
    }
    sal_memset(&trap_type_info, 0, sizeof(dnx_rx_trap_map_type_t));
    sal_memset(&appl_trap_info, 0, sizeof(dnx_rx_trap_map_type_t));

    SHR_IF_ERR_EXIT(dnx_rx_trap_type_map_info_get_dispatch(unit, trap_type, &trap_type_info));
    SHR_IF_ERR_EXIT(dnx_rx_trap_appl_trap_map_info_get_dispatch(unit, trap_type, &appl_trap_info));

    if (trap_type_info.valid)
    {
        sal_strncpy(trap_name, trap_type_info.trap_name, DBAL_MAX_STRING_LENGTH);
    }
    else if (appl_trap_info.valid)
    {
        sal_strncpy(trap_name, appl_trap_info.trap_name, DBAL_MAX_STRING_LENGTH);
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Trap type %d Not supported\n", trap_type);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Map the Ingress User Defined HW Trap-ID to the SW(alloc) Trap-ID value
* \par DIRECT INPUT:
*   \param [in]  unit          -  Unit id
*   \param [in]  hw_trap_id    -  HW Trap-ID
*   \param [out] sw_trap_id_p  -  SW Trap-ID
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_ud_hw_to_sw(
    int unit,
    int hw_trap_id,
    int *sw_trap_id_p)
{
    dnx_rx_trap_map_ingress_ud_t ingress_ud_info;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&ingress_ud_info, 0, sizeof(dnx_rx_trap_map_ingress_ud_t));

    SHR_NULL_CHECK(sw_trap_id_p, _SHR_E_PARAM, "sw_trap_id_p");

    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_ud_map_info_get_dispatch(unit, hw_trap_id, &ingress_ud_info));
    if (ingress_ud_info.valid)
    {
        *sw_trap_id_p = ingress_ud_info.alloc_index;
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The supplied HW Trap-ID(%d) is not valid!", hw_trap_id);
    }
exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Map the Ingress User Defined SW(alloc) Trap-ID to the HW Trap-ID value
* \par DIRECT INPUT:
*   \param [in] unit     -  Unit id
*   \param [out] trap_id_p  -  SW Trap-ID to be mapped to HW Trap-ID
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_ud_sw_to_hw(
    int unit,
    int *trap_id_p)
{
    int ind = 0;
    dnx_rx_trap_map_ingress_ud_t ingress_ud_info;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&ingress_ud_info, 0, sizeof(dnx_rx_trap_map_ingress_ud_t));

    SHR_NULL_CHECK(trap_id_p, _SHR_E_PARAM, "trap_id_p");

    for (ind = 0; ind < DBAL_NOF_ENUM_INGRESS_TRAP_ID_VALUES; ind++)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_ud_map_info_get_dispatch(unit, ind, &ingress_ud_info));
        if (ingress_ud_info.valid == TRUE)
        {
            if (*trap_id_p == ingress_ud_info.alloc_index)
            {
                *trap_id_p = ind;
                break;
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Returns the ingress class (predefined, oam, user define) of trap based on trap type value
* \par DIRECT INPUT:
*   \param [in] unit       -   Unit Id
*   \param [in] trap_type    -  trap type value to check
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   dnx_rx_trap_class_e - trap class
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
dnx_rx_trap_class_e
dnx_rx_trap_ingress_class_get(
    int unit,
    int trap_type)
{
    uint8 is_user_defined = FALSE;
    bcm_error_t rv;
    dnx_rx_trap_class_e trap_class = DNX_RX_TRAP_CLASS_PREDEFINED;

    if (trap_type < 0)
    {
        rv = BCM_E_PARAM;
    }
    else
    {
        rv = (bcm_error_t) dnx_rx_trap_is_user_defined_dispatch(unit, DNX_RX_TRAP_BLOCK_INGRESS, trap_type,
                                                                &is_user_defined);
    }

    if (rv != BCM_E_NONE)
    {
        trap_class = DNX_RX_TRAP_CLASS_INVALID;
    }
    else if (is_user_defined)
    {
        trap_class = DNX_RX_TRAP_CLASS_USER_DEFINED;
    }
    else if (trap_type == DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_ETH_OAM ||
             trap_type == DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_PERFORMANCE_ETH_OAM ||
             trap_type == DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_Y1731_O_MPLSTP ||
             trap_type == DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_PERFORMANCE_Y1731_O_MPLSTP ||
             trap_type == DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_Y1731_O_PWE ||
             trap_type == DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_PERFORMANCE_Y1731_O_PWE ||
             trap_type == DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_BFD_O_IPV4 ||
             trap_type == DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_BFD_O_IPV6 ||
             trap_type == DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_BFD_O_MPLS ||
             trap_type == DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_BFD_O_PWE ||
             trap_type == DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_BFDCC_O_MPLSTP ||
             trap_type == DBAL_ENUM_FVAL_INGRESS_TRAP_ID_OAM_REFLECTOR ||
             trap_type == DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_NON_ACC_OAM_BFD ||
             trap_type == DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_OAM_CPU_SNOOP ||
             trap_type == DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_OAM_LEVEL ||
             trap_type == DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_OAM_PASSIVE)
    {
        trap_class = DNX_RX_TRAP_CLASS_OAM;
    }

    return trap_class;
}

/*
 * See rx_trap.h for more info
 */
shr_error_e
dnx_rx_trap_epmf_forward_action_profile_from_id_get(
    int unit,
    int trap_id,
    int *forward_action_profile_p)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(forward_action_profile_p, _SHR_E_PARAM, "forward_action_profile_p");

    if (dnx_data_trap.egress.feature_get(unit, dnx_data_trap_egress_egress_divided_to_erpp_and_etpp))
    {
        /** Case of divided egress, ePMF in ERPP, trap is ERPP user defined */
        *forward_action_profile_p = DNX_RX_TRAP_EGRESS_ACTION_PROFILE_GET(trap_id);
    }
    else
    {
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Check if specific ingress trap was already allocated
* \par DIRECT INPUT:
*   \param [in] unit     -  Unit id
*   \param [in] trap_type  -  ingress trap type (HW trap id value) of trap
*   \param [out] is_allocated_p  - Pointer type of int \n
*               \b As \b output - \n
*               Pointer will be filled by TRUE in case the trap was already created

* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_is_trap_id_allocated(
    int unit,
    int trap_type,
    uint8 *is_allocated_p)
{
    dnx_rx_trap_class_e trap_class = DNX_RX_TRAP_CLASS_INVALID;
    int sw_trap_id;

    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(is_allocated_p, _SHR_E_PARAM, "is_allocated_p");

    if ((trap_type < 0) || (trap_type >= DBAL_NOF_ENUM_INGRESS_TRAP_ID_VALUES))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid trap_type=%d\n", trap_type);
    }

    trap_class = DNX_RX_TRAP_ID_CLASS_GET(unit, trap_type);

    switch (trap_class)
    {
        case DNX_RX_TRAP_CLASS_PREDEFINED:
        case DNX_RX_TRAP_CLASS_OAM:
            SHR_IF_ERR_EXIT(dnx_algo_rx_trap_id_ingress_predefined_is_allocated(unit, trap_type, is_allocated_p));
            break;
        case DNX_RX_TRAP_CLASS_USER_DEFINED:
            SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_ud_hw_to_sw(unit, trap_type, &sw_trap_id));
            SHR_IF_ERR_EXIT(dnx_algo_rx_trap_id_ingress_user_define_is_allocated(unit, sw_trap_id, is_allocated_p));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Illegal trap_class=%d\n", trap_class);
            break;
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Check if specific ETPP trap was already allocated
* \par DIRECT INPUT:
*   \param [in] unit     -  Unit id
*   \param [in] trap_class  -  trap class (first or OAM) of trap to check
*   \param [in] trap_type   -  etpp trap type (SW id) of trap to check
*   \param [out] is_allocated_p  - Pointer type of int \n
*               \b As \b output - \n
*               Pointer will be filled by TRUE in case the trap was already created

* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_etpp_is_trap_id_allocated(
    int unit,
    dnx_rx_trap_class_e trap_class,
    int trap_type,
    uint8 *is_allocated_p)
{
    int oam_trap_type = 0, fwd_act_profile = 0;
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(is_allocated_p, _SHR_E_PARAM, "is_allocated_p");

    switch (trap_class)
    {
        case DNX_RX_TRAP_CLASS_USER_DEFINED:
            SHR_IF_ERR_EXIT(dnx_algo_rx_trap_id_etpp_is_allocated(unit, trap_type, is_allocated_p));
            break;
        case DNX_RX_TRAP_CLASS_OAM:
            if (dnx_data_trap.etpp.feature_get(unit, dnx_data_trap_etpp_oam_traps_predefined_support))
            {
                oam_trap_type = DNX_RX_TRAP_ETPP_OAM_TRAP_TYPE_GET(trap_type);
                SHR_IF_ERR_EXIT(dnx_algo_rx_trap_id_etpp_oam_is_allocated(unit, oam_trap_type, is_allocated_p));
            }
            else
            {
                fwd_act_profile = DNX_RX_TRAP_ETPP_OAM_ACTION_PROFILE_GET(trap_type);
                if (fwd_act_profile == 0)
                {
                    /** Zero is the init value of fwd_act_profile for OAM traps, indicating trap is not allocated */
                    *is_allocated_p = FALSE;
                }
                else
                {
                    SHR_IF_ERR_EXIT(dnx_algo_rx_trap_id_etpp_is_allocated(unit, fwd_act_profile, is_allocated_p));
                }
            }
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Illegal trap_class=%d\n", trap_class);
            break;
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Check if specific trap was already allocated
* \par DIRECT INPUT:
*   \param [in] unit            -  Unit Id
*   \param [in] trap_id         -  trap id to check
*   \param [in] is_allocated_p  - Pointer type of int \n
*               \b As \b output - \n
*               Pointer will be filled by TRUE in case the trap was already created
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
dnx_rx_trap_is_trap_id_allocated(
    int unit,
    int trap_id,
    uint8 *is_allocated_p)
{
    dnx_rx_trap_block_e trap_block = DNX_RX_TRAP_BLOCK_INVALID;
    dnx_rx_trap_class_e trap_class = DNX_RX_TRAP_CLASS_INVALID;
    int trap_type = DNX_RX_TRAP_ID_INVALID;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Verify input
     */
    SHR_NULL_CHECK(is_allocated_p, _SHR_E_PARAM, "is_allocated_p");

    trap_block = DNX_RX_TRAP_ID_BLOCK_GET(trap_id);
    trap_class = DNX_RX_TRAP_ID_CLASS_GET(unit, trap_id);
    trap_type = DNX_RX_TRAP_ID_TYPE_GET(trap_id);

    *is_allocated_p = FALSE;

    switch (trap_block)
    {
        case DNX_RX_TRAP_BLOCK_INGRESS:
            SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_is_trap_id_allocated(unit, trap_type, is_allocated_p));
            break;
        case DNX_RX_TRAP_BLOCK_ERPP:
            if (trap_id == BCM_RX_TRAP_EG_TRAP_ID_DEFAULT)
            {
                *is_allocated_p = TRUE;
            }
            else
            {
                SHR_IF_ERR_EXIT(dnx_algo_rx_trap_id_erpp_is_allocated(unit, trap_type, is_allocated_p));
            }
            break;
        case DNX_RX_TRAP_BLOCK_ETPP:
            if (trap_id == BCM_RX_TRAP_EG_TX_TRAP_ID_DEFAULT || trap_id == BCM_RX_TRAP_EG_TX_TRAP_ID_DROP)
            {
                *is_allocated_p = TRUE;
            }
            else
            {
                SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_is_trap_id_allocated(unit, trap_class, trap_type, is_allocated_p));
            }
            break;
        case DNX_RX_TRAP_BLOCK_OAMP:
            /** Allocated using OAM APIs, no need for allocation check */
            *is_allocated_p = TRUE;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Illegal trap_block=%d\n", trap_block);
            break;
    }

exit:
    SHR_FUNC_EXIT;

}

/**
* \brief
*  Verify the parameters of bcm_rx_trap_type_create API
* \par DIRECT INPUT:
*   \param [in] unit     -  Unit Id
*   \param [in] flags    -  flags of the API BCM_RX_TRAP_FLAG
*   \param [in] type     -  bcmRxTrapType to create
*   \param [in] trap_id  - trap_id of the created trap
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_type_create_verify(
    int unit,
    int flags,
    bcm_rx_trap_t type,
    int trap_id)
{
    dnx_rx_trap_block_e trap_block = DNX_RX_TRAP_ID_BLOCK_GET(trap_id);
    dnx_rx_trap_map_type_t trap_type_info;
    uint8 is_allocated = FALSE, is_oam_punt_or_protection = FALSE, is_user_defined = FALSE, is_etpp_oam_user_defined =
        FALSE;
    int system_headers_mode = DNX_RX_TRAP_SYSTEM_HEADERS_MODE_GET(unit);
    uint32 unsupported_flags;
    dnx_rx_trap_map_ud_t ud_block_info;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&trap_type_info, 0, sizeof(dnx_rx_trap_map_type_t));
    sal_memset(&ud_block_info, 0, sizeof(dnx_rx_trap_map_ud_t));

    if (type >= bcmRxTrapCount)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid trap type = %d \n", type);
    }

    if ((unsupported_flags = (flags & ~(BCM_RX_TRAP_WITH_ID))))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Flags 0x%X are not supported.\n", unsupported_flags);
    }

    SHR_IF_ERR_EXIT(dnx_rx_trap_type_map_info_get_dispatch(unit, type, &trap_type_info));

    SHR_IF_ERR_EXIT(dnx_rx_trap_user_defined_block_map_info_get_dispatch(unit, trap_block, &ud_block_info));

    SHR_IF_ERR_EXIT(dnx_oam_punt_and_protection_trap_create_verify
                    (unit, flags, type, trap_id, &is_oam_punt_or_protection));

    if (is_oam_punt_or_protection == FALSE)
    {
        is_etpp_oam_user_defined =
            (!dnx_data_trap.etpp.feature_get(unit, dnx_data_trap_etpp_oam_traps_predefined_support))
            && trap_type_info.trap_block == DNX_RX_TRAP_BLOCK_ETPP
            && trap_type_info.trap_class == DNX_RX_TRAP_CLASS_OAM;
        /** Verify non user-defined (predefined, OAM) trap create */
        if (trap_type_info.trap_class != DNX_RX_TRAP_CLASS_USER_DEFINED && !is_etpp_oam_user_defined)
        {
            if (flags & BCM_RX_TRAP_WITH_ID)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG, "Only OAMP Error traps and bcmRxTrapUserDefine traps can be created using "
                             "with_id flag\n");
            }

            SHR_IF_ERR_EXIT(dnx_rx_trap_is_trap_id_allocated(unit, trap_id, &is_allocated));
            if (is_allocated == TRUE)
            {
                SHR_ERR_EXIT(_SHR_E_EXISTS, "Trap bcmRxTrap%s was already created\n", trap_type_info.trap_name);
            }
        }

        /** Verify user-defined trap create */
        if (flags & BCM_RX_TRAP_WITH_ID)
        {
            /** In case of user-defined WITH_ID, block is not encoded, retrieve it from type */
            trap_block = trap_type_info.trap_block;

            SHR_IF_ERR_EXIT(dnx_rx_trap_is_user_defined_dispatch
                            (unit, trap_block, DNX_RX_TRAP_ID_TYPE_GET(trap_id), &is_user_defined));
            if (!is_user_defined)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG,
                             "%s user-defined traps WITH_ID need to have a designated UD trap ID \n",
                             ud_block_info.block_name);
            }

            if (trap_block == DNX_RX_TRAP_BLOCK_ERPP)
            {
                SHR_IF_ERR_EXIT(dnx_rx_trap_is_trap_id_allocated
                                (unit,
                                 DNX_RX_TRAP_ID_SET(DNX_RX_TRAP_BLOCK_ERPP, DNX_RX_TRAP_CLASS_USER_DEFINED, trap_id),
                                 &is_allocated));
            }
            else if (trap_block == DNX_RX_TRAP_BLOCK_ETPP)
            {
                SHR_IF_ERR_EXIT(dnx_rx_trap_is_trap_id_allocated
                                (unit,
                                 DNX_RX_TRAP_ID_SET(DNX_RX_TRAP_BLOCK_ETPP, DNX_RX_TRAP_CLASS_USER_DEFINED, trap_id),
                                 &is_allocated));
            }
            else
            {
                SHR_IF_ERR_EXIT(dnx_rx_trap_is_trap_id_allocated(unit, trap_id, &is_allocated));
            }
            if (is_allocated == TRUE)
            {
                SHR_ERR_EXIT(_SHR_E_EXISTS, "Trap bcmRxTrapUserDefine id=%d was already created\n", trap_id);
            }

            if (system_headers_mode == DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO_MODE)
            {
                if (trap_id >= DBAL_ENUM_FVAL_INGRESS_TRAP_ID_RESERVED_256)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Trap_ID(%d) supplied is out of Jericho mode valid range 0-256\n",
                                 trap_id);
                }
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Create and id for given ingress trap type, i.e allocate an id in relevant pool
* \par DIRECT INPUT:
*   \param [in] unit     -  Unit id
*   \param [in] flags    -  Can be BCM_RX_TRAP_FLAG_WITH_ID or 0.
*   \param [out] trap_id_p  -  Pointer type of int \n
*               \b As \b output - \n
*               Pointer will be filled by the allocated trap id
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_create(
    int unit,
    int flags,
    int *trap_id_p)
{
    int alloc_flags = 0;
    dnx_rx_trap_class_e trap_class = DNX_RX_TRAP_CLASS_INVALID;
    int sw_trap_id;
    int system_headers_mode = DNX_RX_TRAP_SYSTEM_HEADERS_MODE_GET(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(trap_id_p, _SHR_E_PARAM, "trap_id_p");

    trap_class = DNX_RX_TRAP_ID_CLASS_GET(unit, *trap_id_p);

    switch (trap_class)
    {
        case DNX_RX_TRAP_CLASS_PREDEFINED:
        case DNX_RX_TRAP_CLASS_OAM:
            SHR_IF_ERR_EXIT(dnx_algo_rx_trap_id_ingress_predefined_allocate(unit, trap_id_p));
            break;
        case DNX_RX_TRAP_CLASS_USER_DEFINED:
            if (flags & BCM_RX_TRAP_WITH_ID)
            {
                alloc_flags = DNX_ALGO_TEMPLATE_ALLOCATE_WITH_ID;
                SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_ud_hw_to_sw(unit, *trap_id_p, &sw_trap_id));
                *trap_id_p = sw_trap_id;
            }
            SHR_IF_ERR_EXIT(dnx_algo_rx_trap_id_ingress_user_define_allocate(unit, alloc_flags, trap_id_p));
            SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_ud_sw_to_hw(unit, trap_id_p));
            if ((system_headers_mode == DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO_MODE) &&
                !(flags & BCM_RX_TRAP_WITH_ID) && (*trap_id_p >= DBAL_ENUM_FVAL_INGRESS_TRAP_ID_RESERVED_256))
            {
                SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_ud_hw_to_sw(unit, *trap_id_p, trap_id_p));
                SHR_IF_ERR_EXIT(dnx_algo_rx_trap_id_ingress_user_define_deallocate(unit, *trap_id_p));
                SHR_ERR_EXIT(_SHR_E_FULL, "UserDefined traps have been exhausted in Jericho mode \n");
            }
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Illegal trap_class=%d\n", trap_class);
            break;
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Create and id for given etpp trap type, i.e allocate an id in relevant pool
* \par DIRECT INPUT:
*   \param [in] unit     -  Unit id
*   \param [in] flags       - Flags(WITH_ID)
*   \param [in] trap_class  -  trap class (first or OAM) to create
*   \param [in] type     -  bcmRxTrapTypeEgTx.. to create
*   \param [out] trap_id_p   -  etpp trap is allocated
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_etpp_create(
    int unit,
    int flags,
    dnx_rx_trap_class_e trap_class,
    bcm_rx_trap_t type,
    int *trap_id_p)
{
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_trap.egress.feature_get(unit, dnx_data_trap_egress_egress_divided_to_erpp_and_etpp))
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_v1_etpp_create(unit, flags, trap_class, type, trap_id_p));
    }
    else
    {
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Create and id for given trap type, i.e allocate an id in relevant pool
* \par DIRECT INPUT:
*   \param [in] unit     -  Unit ID
*   \param [in] flags    -  Can be WITH_ID or 0.
*   \param [in] type     -  bcmRxTrapType.. to create
*   \param [out] trap_id_p  -  the allocated trap id
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   int - Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
bcm_dnx_rx_trap_type_create(
    int unit,
    int flags,
    bcm_rx_trap_t type,
    int *trap_id_p)
{
    dnx_rx_trap_block_e trap_block = DNX_RX_TRAP_BLOCK_INVALID;
    dnx_rx_trap_class_e trap_class = DNX_RX_TRAP_CLASS_INVALID;
    int converted_trap_id = 0;
    uint8 is_punt_or_protection;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    DNX_ERR_RECOVERY_REGRESSION_RESTORE_IN_OUT_VAR_PTR(unit, sizeof(int), trap_id_p);

    SHR_NULL_CHECK(trap_id_p, _SHR_E_PARAM, "trap_id_p");

    /** Convert bcmRxTrapType to [trap_stage | trap_class | trap_type] */
    is_punt_or_protection = (((type >= bcmRxTrapOampTrapErr) && (type <= bcmRxTrapOampProtection)) ||
                             (type == bcmRxTrapOampChanTypeMissErr) || (type == bcmRxTrapOampFlexCrcMissErr) ||
                             (type == bcmRxTrapOampPuntNextGoodPacket) || (type == bcmRxTrapOampMplsLmDmErr) ||
                             (type == bcmRxTrapOampChecksumErr) || (type == bcmRxTrapOampRmepEccErr)
                             || (type == bcmRxTrapOampErrorIndicationMiss));

    if ((is_punt_or_protection == FALSE) || ((flags & BCM_RX_TRAP_WITH_ID) == 0))
    {
        if (is_punt_or_protection == TRUE)
        {
            /** For punt or protection without ID, get a user defined trap */
            SHR_IF_ERR_EXIT(dnx_rx_trap_type_to_id(unit, bcmRxTrapUserDefine, &converted_trap_id));
            converted_trap_id = DNX_RX_TRAP_ID_SET(DNX_RX_TRAP_BLOCK_OAMP, 0, converted_trap_id);
        }
        else
        {
            SHR_IF_ERR_EXIT(dnx_rx_trap_type_to_id(unit, type, &converted_trap_id));
        }

        trap_block = DNX_RX_TRAP_ID_BLOCK_GET(converted_trap_id);
        trap_class = DNX_RX_TRAP_ID_CLASS_GET(unit, converted_trap_id);
    }

    if (flags & BCM_RX_TRAP_WITH_ID)
    {
        converted_trap_id = *trap_id_p;
        if (is_punt_or_protection == TRUE)
        {
            trap_block = DNX_RX_TRAP_ID_BLOCK_GET(converted_trap_id);
            trap_class = DNX_RX_TRAP_ID_CLASS_GET(unit, converted_trap_id);
        }
    }
    else
    {
        *trap_id_p = DNX_RX_TRAP_ID_TYPE_GET(converted_trap_id);
    }

    SHR_INVOKE_VERIFY_DNXC(dnx_rx_trap_type_create_verify(unit, flags, type, converted_trap_id));

    switch (trap_block)
    {
        case DNX_RX_TRAP_BLOCK_INGRESS:
        default:
            SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_create(unit, flags, trap_id_p));
            break;
        case DNX_RX_TRAP_BLOCK_ERPP:
            SHR_IF_ERR_EXIT(dnx_algo_rx_trap_id_erpp_allocate(unit, flags, trap_id_p));
            *trap_id_p = DNX_RX_TRAP_ID_SET(DNX_RX_TRAP_BLOCK_ERPP, DNX_RX_TRAP_CLASS_USER_DEFINED, *trap_id_p);
            break;
        case DNX_RX_TRAP_BLOCK_ETPP:
            SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_create(unit, flags, trap_class, type, trap_id_p));
            break;
        case DNX_RX_TRAP_BLOCK_OAMP:
            if ((flags & BCM_RX_TRAP_WITH_ID) == 0)
            {
                /** Create the new user defined trap */
                SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_create(unit, flags, trap_id_p));
            }
            SHR_IF_ERR_EXIT(dnx_oam_error_trap_type_set(unit, type, *trap_id_p));
            *trap_id_p = DNX_RX_TRAP_ID_SET(DNX_RX_TRAP_BLOCK_OAMP, 0, *trap_id_p);
            break;
    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get the HW Trap id of the supplied trap type.
* \par DIRECT INPUT:
*   \param [in] unit     -  Unit ID
*   \param [in] flags    -  This API does not support flags.
*   \param [in] type     -  bcmRxTrapType.. to get
*   \param [out] trap_id_p  -  HW Trap ID associated with the supplied trap_type
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
bcm_dnx_rx_trap_type_get(
    int unit,
    int flags,
    bcm_rx_trap_t type,
    int *trap_id_p)
{
    uint8 is_punt_or_protection;
    dnx_rx_trap_block_e trap_block = DNX_RX_TRAP_BLOCK_INVALID;
    dnx_rx_trap_class_e trap_class = DNX_RX_TRAP_CLASS_INVALID;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    is_punt_or_protection = (((type >= bcmRxTrapOampTrapErr) && (type <= bcmRxTrapOampProtection)) ||
                             (type == bcmRxTrapOampChanTypeMissErr) || (type == bcmRxTrapOampFlexCrcMissErr) ||
                             (type == bcmRxTrapOampPuntNextGoodPacket) || (type == bcmRxTrapOampMplsLmDmErr) ||
                             (type == bcmRxTrapOampChecksumErr) || (type == bcmRxTrapOampRmepEccErr)
                             || (type == bcmRxTrapOampErrorIndicationMiss));

    if (is_punt_or_protection)
    {
        SHR_IF_ERR_EXIT(dnx_oam_get_punt_protection_trap_from_type(unit, type, trap_id_p));
        SHR_EXIT();
    }

    if (type == bcmRxTrapUserDefine)
    {
        SHR_ERR_EXIT(_SHR_E_CONFIG, "This API does not support UserDefined Traps! \n");
    }

    SHR_IF_ERR_EXIT(dnx_rx_trap_type_to_id(unit, type, trap_id_p));

    trap_block = DNX_RX_TRAP_ID_BLOCK_GET((*trap_id_p));

    switch (trap_block)
    {
        case DNX_RX_TRAP_BLOCK_INGRESS:
        {
            break;
        }
        case DNX_RX_TRAP_BLOCK_ERPP:
        {
            SHR_ERR_EXIT(_SHR_E_CONFIG, "This API does not support ERPP Traps! \n");
            break;
        }
        case DNX_RX_TRAP_BLOCK_ETPP:
        {
            trap_class = DNX_RX_TRAP_ID_CLASS_GET(unit, *trap_id_p);
            if (trap_class != DNX_RX_TRAP_CLASS_OAM)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG, "This API supports only OAM ETPP Traps! \n");
            }
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_CONFIG, "Unrecognized block! \n");
            break;
        }

    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    /** Warmboot skipped, because of a usage between pkt_send and pkt_verify.*/
    BCM_WARM_BOOT_API_TEST_MODE_SKIP_WB_SEQUENCE(unit);
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get the trap type for the supplied ingress trap id.
* \par DIRECT INPUT:
*   \param [in] unit     -  Unit ID
*   \param [in] trap_class  -  trap class
*   \param [in] trap_type   -  ingress trap type (HW id)
*   \param [out] bcm_trap_type_p     -  bcmRxTrapType.. of trap
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_type_from_id_get(
    int unit,
    dnx_rx_trap_class_e trap_class,
    int trap_type,
    bcm_rx_trap_t * bcm_trap_type_p)
{
    int i_trap = 0;
    dnx_rx_trap_map_type_t trap_type_info;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&trap_type_info, 0, sizeof(dnx_rx_trap_map_type_t));

    switch (trap_class)
    {
        case DNX_RX_TRAP_CLASS_USER_DEFINED:
            *bcm_trap_type_p = bcmRxTrapUserDefine;
            break;
        case DNX_RX_TRAP_CLASS_PREDEFINED:
        case DNX_RX_TRAP_CLASS_OAM:
            for (i_trap = 0; i_trap < bcmRxTrapCount; i_trap++)
            {
                SHR_IF_ERR_EXIT(dnx_rx_trap_type_map_info_get_dispatch(unit, i_trap, &trap_type_info));

                if (trap_type_info.valid == TRUE && trap_type_info.trap_block == DNX_RX_TRAP_BLOCK_INGRESS)
                {
                    if (trap_type == trap_type_info.trap_id)
                    {
                        *bcm_trap_type_p = i_trap;
                        break;
                    }
                }
            }

            if (i_trap == bcmRxTrapCount)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid trap_id:\"%d\"\n", trap_type);
            }
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Illegal trap_class=%d\n", trap_class);
            break;
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set the etpp trap action profile: trap stregnth and action.
*  Allocates profile using template manager.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_class  -  trap class (first or OAM) to configure
*   \param [in] trap_type   -  etpp trap type (SW id) to configure
*   \param [out] bcm_trap_type_p     -  bcmRxTrapType.. of trap
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_etpp_type_from_id_get(
    int unit,
    dnx_rx_trap_class_e trap_class,
    int trap_type,
    bcm_rx_trap_t * bcm_trap_type_p)
{
    int i_trap;
    dnx_rx_trap_map_type_t trap_type_info;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&trap_type_info, 0, sizeof(dnx_rx_trap_map_type_t));

    switch (trap_class)
    {
        case DNX_RX_TRAP_CLASS_USER_DEFINED:
            *bcm_trap_type_p = bcmRxTrapEgTxUserDefine;
            break;
        case DNX_RX_TRAP_CLASS_OAM:
            for (i_trap = 0; i_trap < bcmRxTrapCount; i_trap++)
            {
                SHR_IF_ERR_EXIT(dnx_rx_trap_type_map_info_get_dispatch(unit, i_trap, &trap_type_info));
                if (trap_type_info.valid == TRUE &&
                    trap_type_info.trap_block == DNX_RX_TRAP_BLOCK_ETPP &&
                    trap_type_info.trap_class == DNX_RX_TRAP_CLASS_OAM)
                {
                    if (trap_type == trap_type_info.trap_id)
                    {
                        *bcm_trap_type_p = i_trap;
                        break;
                    }
                }
            }

            if (i_trap == bcmRxTrapCount)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid trap_id:\"%d\"\n", trap_type);
            }
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Illegal trap_class=%d\n", trap_class);
            break;
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 *  See rx.h for info
 */
shr_error_e
bcm_dnx_rx_trap_type_from_id_get(
    int unit,
    int flags,
    int trap_id,
    bcm_rx_trap_t * bcm_trap_type_p)
{
    dnx_rx_trap_block_e trap_block = DNX_RX_TRAP_BLOCK_INVALID;
    dnx_rx_trap_class_e trap_class = DNX_RX_TRAP_CLASS_INVALID;
    int trap_type = DNX_RX_TRAP_ID_INVALID;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    SHR_NULL_CHECK(bcm_trap_type_p, _SHR_E_PARAM, "bcm_trap_type_p");

    trap_block = DNX_RX_TRAP_ID_BLOCK_GET(trap_id);
    trap_class = DNX_RX_TRAP_ID_CLASS_GET(unit, trap_id);
    trap_type = DNX_RX_TRAP_ID_TYPE_GET(trap_id);

    switch (trap_block)
    {
        case DNX_RX_TRAP_BLOCK_INGRESS:
            SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_type_from_id_get(unit, trap_class, trap_type, bcm_trap_type_p));
            break;
        case DNX_RX_TRAP_BLOCK_ERPP:
            /** ERPP traps only support user defined */
            *bcm_trap_type_p = bcmRxTrapEgUserDefine;
            break;
        case DNX_RX_TRAP_BLOCK_ETPP:
            SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_type_from_id_get(unit, trap_class, trap_type, bcm_trap_type_p));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Illegal trap_block=%d\n", trap_block);
            break;
    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/*  Check if the supplied ingress trap_type(ID) requires a trap strength to be set.
* \par DIRECT INPUT:
*   \param [in] unit              -  Unit Id
*   \param [in] trap_type         -  Ingress trap type (HW trap id value) to configure
*   \param [out] is_strengthless  -  Strengthless trap indicator.
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
dnx_rx_trap_ingress_strengthless_trap_check(
    int unit,
    int trap_type,
    int *is_strengthless)
{
    int trap_type_idx;
    dnx_rx_trap_map_type_t predefined_trap_info;
    dnx_rx_trap_map_ingress_ud_t ingress_ud_info;
    SHR_FUNC_INIT_VARS(unit);

    *is_strengthless = TRUE;
    sal_memset(&predefined_trap_info, 0, sizeof(dnx_rx_trap_map_type_t));
    sal_memset(&ingress_ud_info, 0, sizeof(dnx_rx_trap_map_ingress_ud_t));

    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_ud_map_info_get_dispatch(unit, trap_type, &ingress_ud_info));

    if (ingress_ud_info.valid == FALSE)
    {
        for (trap_type_idx = 0; trap_type_idx < bcmRxTrapCount; trap_type_idx++)
        {
            SHR_IF_ERR_EXIT(dnx_rx_trap_type_map_info_get_dispatch(unit, trap_type_idx, &predefined_trap_info));
            if (predefined_trap_info.valid && (predefined_trap_info.trap_block == DNX_RX_TRAP_BLOCK_INGRESS)
                && (predefined_trap_info.trap_id == trap_type))
            {
                *is_strengthless = predefined_trap_info.is_strengthless;
                break;
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Verify the parameters of bcm_rx_trap_set API
* \par DIRECT INPUT:
*   \param [in] unit     -  Unit Id
*   \param [in] trap_id  -  trap id to set
*   \param [in] config_p   -  configuration for given trap
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_set_verify(
    int unit,
    int trap_id,
    bcm_rx_trap_config_t * config_p)
{
    uint8 is_allocated;
    dnx_rx_trap_block_e trap_block;
    int trap_type;
    int is_strengthless = TRUE;
    SHR_FUNC_INIT_VARS(unit);

    trap_type = DNX_RX_TRAP_ID_TYPE_GET(trap_id);
    trap_block = DNX_RX_TRAP_ID_BLOCK_GET(trap_id);
    /*
     * Check NULL param
     */
    SHR_NULL_CHECK(config_p, _SHR_E_PARAM, "config_p");

    /*
     * Check if trap id was allocated
     */
    SHR_IF_ERR_EXIT(dnx_rx_trap_is_trap_id_allocated(unit, trap_id, &is_allocated));
    if (is_allocated == FALSE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "trap_id=%d was not created, call bcm_rx_trap_type_create() first \n", trap_id);
    }

    switch (trap_block)
    {
        case DNX_RX_TRAP_BLOCK_INGRESS:
        {
            if (trap_type == DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_NONE)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Default Ingress trap can't be set by user\n");
            }

            SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_strengthless_trap_check(unit, trap_type, &is_strengthless));

            /*
             * Check if the trap is strengthless and both trap and snoop strength are 0
             */
            if (is_strengthless && (config_p->trap_strength != 0 || config_p->snoop_strength != 0))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Trap and snoop strength should be 0 for user defined and OAM traps! \n");
            }

            if (!is_strengthless && config_p->snoop_strength > dnx_data_trap.strength.max_snp_strength_get(unit))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Snoop strength is too big, maximum value is %d! \n",
                             dnx_data_trap.strength.max_snp_strength_get(unit));
            }

            if ((dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_snoop_code_clear_action) == FALSE) &&
                (config_p->flags2 & BCM_RX_TRAP_FLAGS2_SNOOP_CODE_CLEAR))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Snoop code clear action does not exist on this device! \n");
            }

            if ((dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_mirror_code_clear_action) == FALSE) &&
                (config_p->flags2 & BCM_RX_TRAP_FLAGS2_MIRROR_CODE_CLEAR))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Mirror code clear action does not exist on this device! \n");
            }

            if ((dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_stat_sampling_code_clear_action) ==
                 FALSE) && (config_p->flags2 & BCM_RX_TRAP_FLAGS2_STAT_SAMPLING_CODE_CLEAR))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                             "Statistical sampling code clear action does not exist on this device! \n");
            }
            break;
        }
        case DNX_RX_TRAP_BLOCK_ERPP:
        {
            if (trap_id == BCM_RX_TRAP_EG_TRAP_ID_DEFAULT)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Default ERPP profile can't be set by user\n");
            }
            break;
        }
        case DNX_RX_TRAP_BLOCK_ETPP:
        {
            if (trap_id == BCM_RX_TRAP_EG_TX_TRAP_ID_DEFAULT)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Default ETPP profiles can't be set by user\n");
            }
            break;
        }
        case DNX_RX_TRAP_BLOCK_OAMP:
        {
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Illegal trap_block=%d\n", trap_block);
            break;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See rx_trap.h for more info
 */
void
dnx_rx_trap_ingress_action_with_flag_and_value_hw_set(
    int unit,
    uint32 entry_handle_id,
    int flags,
    int bcm_rx_trap_flag,
    dbal_fields_e overwrite_field,
    dbal_fields_e value_field,
    int value)
{
    if (flags & bcm_rx_trap_flag)
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, overwrite_field, INST_SINGLE, TRUE);
        dbal_entry_value_field32_set(unit, entry_handle_id, value_field, INST_SINGLE, value);
    }
    else
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, overwrite_field, INST_SINGLE, FALSE);
    }
}

/*
 * See rx_trap.h for more info
 */
void
dnx_rx_trap_ingress_action_with_flag_hw_set(
    int unit,
    uint32 entry_handle_id,
    int flags,
    int bcm_rx_trap_flag,
    dbal_fields_e enabler_field)
{
    if (flags & bcm_rx_trap_flag)
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, enabler_field, INST_SINGLE, TRUE);
    }
    else
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, enabler_field, INST_SINGLE, FALSE);
    }
}

/**
* \brief
*  This function returns an error for unsupported flag.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] flags      -  trap flags
*   \param [in] bcm_rx_trap_flag      -  BCM_RX_TRAP_XXX action flag
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_action_flag_not_supported(
    int unit,
    int flags,
    int bcm_rx_trap_flag)
{
    SHR_FUNC_INIT_VARS(unit);

    if (flags & bcm_rx_trap_flag)
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Flag=%d Not supported config->flags=%d BC\n", bcm_rx_trap_flag, flags);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function configure destination for trap action.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] core_id      -  core id
*   \param [in] entry_handle_id      -  entry handle alloced id
*   \param [in] config_p  - pointer to trap configuration configuration that translates to HW
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_destination_set(
    int unit,
    uint32 core_id,
    uint32 entry_handle_id,
    bcm_rx_trap_config_t * config_p)
{
    bcm_gport_t gport_dest = 0;
    uint32 dest_encoded;
    SHR_FUNC_INIT_VARS(unit);

    if ((config_p->flags & BCM_RX_TRAP_UPDATE_DEST) || (config_p->flags & BCM_RX_TRAP_DEST_MULTICAST))
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DESTINATION_OVERWRITE, INST_SINGLE, TRUE);
        /** In case of multicast the gport should be read from dest_group*/
        if (config_p->flags & BCM_RX_TRAP_DEST_MULTICAST)
        {
            if (config_p->dest_port != 0)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG, "dest_port field is configured for MULTICAST, only dest_group should be "
                             "configured for MULTICAST case\n");
            }

            BCM_GPORT_MCAST_SET(gport_dest, config_p->dest_group);
        }
        else
        {
            /** If not multicast than destination can be configured per core or not*/
            if (config_p->core_config_arr != NULL)
            {
                /** Check there is at least one core configured */
                if (config_p->core_config_arr_len < 1)
                {
                    SHR_ERR_EXIT(_SHR_E_CONFIG, "core_config_arr_len (%d) is invalid and core_config_arr is different "
                                 "from NULL\n", config_p->core_config_arr_len);
                }

                if (config_p->dest_port != 0)
                {
                    SHR_ERR_EXIT(_SHR_E_CONFIG, "Configuration is done per core (core_config_arr valid) but dest_port "
                                 "field (shared by cores) is also configured. Please configure dest_port "
                                 "per core (core_config_arr[core_num].dest_port)\n");
                }

                /** Configure desitnation per core */
                if (config_p->core_config_arr_len > core_id)
                {
                    gport_dest = config_p->core_config_arr[core_id].dest_port;
                }
            }
            else
            {
                /** Check per core configuration was not done */
                if (config_p->core_config_arr_len > 0)
                {
                    SHR_ERR_EXIT(_SHR_E_CONFIG, "core_config_arr is NULL but core_config_arr_len (%d) is non-zero\n",
                                 config_p->core_config_arr_len);
                }

                /** Case when same destination configured for both cores*/
                gport_dest = config_p->dest_port;
            }
        }

        /** In case of black hole destination, mark FWD destination as not valid*/
        if (config_p->dest_port == BCM_GPORT_BLACK_HOLE)
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FWD_DESTINATION_VALID, INST_SINGLE, FALSE);
        }
        else
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FWD_DESTINATION_VALID, INST_SINGLE, TRUE);

        }
        /** Translate the gport to DBAL destination*/
        SHR_IF_ERR_EXIT(algo_gpm_encode_destination_field_from_gport
                        (unit, ALGO_GPM_ENCODE_DESTINATION_ASYM_VOQ, gport_dest, &dest_encoded));

        /** Set the destination value*/
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DESTINATION_VALUE, INST_SINGLE, dest_encoded);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function get configuration of trap action destination.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] core_id      -  core id
*   \param [in] entry_handle_id      -  entry handle alloced id
*   \param [in] config_p  - pointer to trap configuration configuration that translates to HW
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_destination_get(
    int unit,
    uint32 core_id,
    uint32 entry_handle_id,
    bcm_rx_trap_config_t * config_p)
{
    bcm_gport_t gport_dest = 0;
    uint32 dest_ow = 0;
    uint32 fwd_dest_valid = 0;
    uint32 dest_encoded = 0;

    SHR_FUNC_INIT_VARS(unit);

    /** Get destination values */
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_DESTINATION_OVERWRITE,
                                                        INST_SINGLE, &dest_ow));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_FWD_DESTINATION_VALID,
                                                        INST_SINGLE, &fwd_dest_valid));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_DESTINATION_VALUE,
                                                        INST_SINGLE, &dest_encoded));

    if (dest_ow == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_DEST;

        /** In case fwd destination is not valid, the configuration is black hole*/
        if (fwd_dest_valid == TRUE)
        {
            SHR_IF_ERR_EXIT(algo_gpm_gport_from_encoded_destination_field
                            (unit, ALGO_GPM_ENCODE_DESTINATION_FLAGS_NONE, dest_encoded, &gport_dest));

            if (BCM_GPORT_IS_MCAST(gport_dest))
            {
                config_p->flags |= BCM_RX_TRAP_DEST_MULTICAST;
                config_p->dest_group = gport_dest;
            }
            else
            {
                /** Retrieve dest_port according to core configuration */
                if (config_p->core_config_arr == NULL)
                {
                    config_p->dest_port = gport_dest;
                }
                else if (core_id < config_p->core_config_arr_len)
                {
                    config_p->core_config_arr[core_id].dest_port = gport_dest;
                }
            }
        }
        else
        {
            config_p->dest_port |= BCM_GPORT_BLACK_HOLE;
        }
    }
    else
    {
        if (config_p->core_config_arr == NULL)
        {
            config_p->dest_port = 0;
        }
        else if (core_id < config_p->core_config_arr_len)
        {
            config_p->core_config_arr[core_id].dest_port = 0;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function configure Out-LIF for trap action.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] core_id      -  core id
*   \param [in] entry_handle_id      -  entry handle alloced id
*   \param [in] config_p  - pointer to trap configuration configuration that translates to HW
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_out_lif_set(
    int unit,
    uint32 core_id,
    uint32 entry_handle_id,
    bcm_rx_trap_config_t * config_p)
{
    int encap_id = 0, encap_id2 = 0;
    uint32 out_lif_0 = 0, out_lif_1 = 0;
    dnx_algo_gpm_gport_hw_resources_t gport_hw_resources;
    int system_headers_mode = DNX_RX_TRAP_SYSTEM_HEADERS_MODE_GET(unit);
    SHR_FUNC_INIT_VARS(unit);

    /** Set OUT_LIF for trap action */
    if (config_p->flags & BCM_RX_TRAP_UPDATE_ENCAP_ID)
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF_OVERWRITE, INST_SINGLE, TRUE);

        /** Outlif  can be configured per core or not*/
        if (config_p->core_config_arr != NULL)
        {
            /** Check there is at least one core configured */
            if (config_p->core_config_arr_len < 1)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG, "core_config_arr_len (%d) is invalid and core_config_arr is different "
                             "from NULL\n", config_p->core_config_arr_len);
            }

            if (config_p->encap_id != 0 || config_p->encap_id2 != 0)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG, "Configuration is done per core (core_config_arr valid) but encap_id/2 "
                             "field (shared by cores) is also configured. Please configure encap_id/2 "
                             "per core (core_config_arr[core_num].encap_id/2)\n");
            }

            /** Configure encap id per core */
            if (config_p->core_config_arr_len > core_id)
            {
                encap_id = config_p->core_config_arr[core_id].encap_id;
                encap_id2 = config_p->core_config_arr[core_id].encap_id2;
            }
        }
        else
        {
            /** Case when same outlif configured for both cores*/
            encap_id = config_p->encap_id;
            encap_id2 = config_p->encap_id2;
        }

        /** Translate the Gport to global outlif*/
        if (BCM_GPORT_IS_SET(encap_id))
        {
            SHR_IF_ERR_REPLACE_AND_EXIT(dnx_algo_gpm_gport_to_hw_resources(unit, encap_id,
                                                                           DNX_ALGO_GPM_GPORT_HW_RESOURCES_GLOBAL_LIF_EGRESS,
                                                                           &gport_hw_resources), _SHR_E_NOT_FOUND,
                                        _SHR_E_PARAM);

            out_lif_0 = gport_hw_resources.global_out_lif;
        }
        else
        {
            out_lif_0 = encap_id;
        }

        if (BCM_GPORT_IS_SET(encap_id2))
        {
            SHR_IF_ERR_REPLACE_AND_EXIT(dnx_algo_gpm_gport_to_hw_resources(unit, encap_id2,
                                                                           DNX_ALGO_GPM_GPORT_HW_RESOURCES_GLOBAL_LIF_EGRESS,
                                                                           &gport_hw_resources), _SHR_E_NOT_FOUND,
                                        _SHR_E_PARAM);

            out_lif_1 = gport_hw_resources.global_out_lif;
        }
        else
        {
            out_lif_1 = encap_id2;
        }

        /** Set the out lif values */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF_0_VALUE, INST_SINGLE, out_lif_0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF_1_VALUE, INST_SINGLE, out_lif_1);

        if ((encap_id2 != 0) && (system_headers_mode == DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO_MODE))
        {
            /**  EEI Extension: 0xc00000
              *  bit23 Type == 0x1 EEI carries an additional pointer to the EEDB
              *  bit22  0x1: Valid Pointer 
              *  If LBP support ROO naturally, FTMH will always carry Out-LIF1,
              *  so in order to take two outlif to egress, EEI value should set to out_lif_0
              */
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_EEI_VALUE, INST_SINGLE,
                                         (dnx_data_field.init.roo_get(unit) ? out_lif_1 : out_lif_0) | 0xc00000);
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_EEI_OVERWRITE, INST_SINGLE, 1);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function get configuration of trap action Out-LIF.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] core_id      -  core id
*   \param [in] entry_handle_id      -  entry handle alloced id
*   \param [in] config_p  - pointer to trap configuration configuration that translates to HW
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_out_lif_get(
    int unit,
    uint32 core_id,
    uint32 entry_handle_id,
    bcm_rx_trap_config_t * config_p)
{
    uint32 lif_ow = 0;
    uint32 out_lif_0 = 0, out_lif_1 = 0;
    lif_mapping_local_lif_payload_t local_lif_payload;
    bcm_gport_t gport_encap_id = 0, gport_encap_id2 = 0;
    SHR_FUNC_INIT_VARS(unit);

    /** Get LIF values */
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_OUT_LIF_OVERWRITE,
                                                        INST_SINGLE, &lif_ow));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_OUT_LIF_0_VALUE, INST_SINGLE,
                                                        &out_lif_0));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_OUT_LIF_1_VALUE, INST_SINGLE,
                                                        &out_lif_1));

    if (lif_ow == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_ENCAP_ID;

        if (out_lif_0 != 0)
        {
            SHR_IF_ERR_EXIT(dnx_algo_lif_mapping_global_to_local_get
                            (unit, DNX_ALGO_LIF_EGRESS, out_lif_0, &local_lif_payload));
            SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_from_lif(unit, DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_EGRESS,
                                                        _SHR_CORE_ALL, local_lif_payload.local_lifs_array.local_lifs[0],
                                                        &gport_encap_id));
        }

        if (out_lif_1 != 0)
        {
            SHR_IF_ERR_EXIT(dnx_algo_lif_mapping_global_to_local_get
                            (unit, DNX_ALGO_LIF_EGRESS, out_lif_1, &local_lif_payload));
            SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_from_lif(unit, DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_EGRESS,
                                                        _SHR_CORE_ALL, local_lif_payload.local_lifs_array.local_lifs[0],
                                                        &gport_encap_id2));
        }

        if (config_p->core_config_arr == NULL)
        {
            config_p->encap_id = gport_encap_id;
            config_p->encap_id2 = gport_encap_id2;
        }
        else if (core_id < config_p->core_config_arr_len)
        {
            config_p->core_config_arr[core_id].encap_id = gport_encap_id;
            config_p->core_config_arr[core_id].encap_id2 = gport_encap_id2;
        }
    }
    else
    {
        if (config_p->core_config_arr == NULL)
        {
            config_p->encap_id = 0;
            config_p->encap_id2 = 0;
        }
        else if (core_id < config_p->core_config_arr_len)
        {
            config_p->core_config_arr[core_id].encap_id = 0;
            config_p->core_config_arr[core_id].encap_id2 = 0;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function configures stat objects action attributes.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] entry_handle_id      -  entry handle alloced id
*   \param [in] config_p  - pointer to trap configuration that translates to HW
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_stat_obj_set(
    int unit,
    uint32 entry_handle_id,
    bcm_rx_trap_config_t * config_p)
{
    uint32 nof_stat_objs = dnx_data_trap.ingress.nof_stat_objs_get(unit);
    uint32 max_nof_stat_objs_to_ow = dnx_data_trap.ingress.max_nof_stat_objs_to_overwrite_get(unit);
    uint32 stat_obj_valid_clear, stat_obj_to_ow, stat_obj_mask;
    dnx_rx_trap_map_stat_obj_dbal_fields_t stat_obj_info;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&stat_obj_info, 0, sizeof(dnx_rx_trap_map_stat_obj_dbal_fields_t));

    /** Statistical objects clear configuration */
    if ((config_p->stat_clear_bitmap >> nof_stat_objs) != 0)
    {
        SHR_ERR_EXIT(_SHR_E_CONFIG, "Only %d ingress stat objects can be cleared, only %d MSB bits of bitmap should be"
                     "configured \n", nof_stat_objs, nof_stat_objs);
    }
    else
    {
        stat_obj_valid_clear = ~config_p->stat_clear_bitmap & DNX_RX_TRAP_ACTION_STAT_OBJ_CLEAR_DEFAULT;
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_STAT_OBJ_VALID_CLEAR, INST_SINGLE,
                                     stat_obj_valid_clear);
    }

    /** Statistical objects overwrite configuration */
    if (config_p->stat_obj_config_len > max_nof_stat_objs_to_ow)
    {
        SHR_ERR_EXIT(_SHR_E_CONFIG, "stat_obj_config_len > %d, only %d ingress stat objects can be overwritten",
                     max_nof_stat_objs_to_ow, max_nof_stat_objs_to_ow);
    }

    for (stat_obj_to_ow = 0; stat_obj_to_ow < config_p->stat_obj_config_len; stat_obj_to_ow++)
    {
        stat_obj_mask = 0x1 << config_p->stat_obj_config_arr[stat_obj_to_ow].counter_command_id;

        if (stat_obj_mask & config_p->stat_clear_bitmap)
        {
            SHR_ERR_EXIT(_SHR_E_CONFIG, "Statistical object %d is configured to be cleared and also overwritten, only "
                         "one of these actions should be configured",
                         config_p->stat_obj_config_arr[stat_obj_to_ow].counter_command_id);
        }
        SHR_IF_ERR_EXIT(dnx_rx_trap_stat_obj_map_info_get_dispatch(unit, stat_obj_to_ow, &stat_obj_info));

        dbal_entry_value_field32_set(unit, entry_handle_id, stat_obj_info.overwrite, INST_SINGLE, TRUE);
        dbal_entry_value_field32_set(unit, entry_handle_id, stat_obj_info.index,
                                     INST_SINGLE, config_p->stat_obj_config_arr[stat_obj_to_ow].counter_command_id);
        dbal_entry_value_field32_set(unit, entry_handle_id, stat_obj_info.value,
                                     INST_SINGLE, config_p->stat_obj_config_arr[stat_obj_to_ow].stat_id);
        dbal_entry_value_field32_set(unit, entry_handle_id, stat_obj_info.offset_by_qual,
                                     INST_SINGLE,
                                     config_p->stat_obj_config_arr[stat_obj_to_ow].is_offset_by_qual_enable);
        dbal_entry_value_field32_set(unit, entry_handle_id, stat_obj_info.type,
                                     INST_SINGLE, config_p->stat_obj_config_arr[stat_obj_to_ow].stat_object_type);
        dbal_entry_value_field32_set(unit, entry_handle_id, stat_obj_info.is_meter,
                                     INST_SINGLE, config_p->stat_obj_config_arr[stat_obj_to_ow].is_meter);
    }

    /** Statistical metadata configuration */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_STATISTIC_META_DATA, INST_SINGLE,
                                 config_p->stat_metadata_mask);

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function retrieved stat objects action attributes configuration.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] entry_handle_id      -  entry handle alloced id
*   \param [in] config_p  - pointer to trap configuration to retrieve
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_stat_obj_get(
    int unit,
    uint32 entry_handle_id,
    bcm_rx_trap_config_t * config_p)
{
    uint32 max_nof_stat_objs_to_ow = dnx_data_trap.ingress.max_nof_stat_objs_to_overwrite_get(unit);
    uint32 stat_obj_valid_clear, stat_obj_to_ow, stat_obj_ow;
    dnx_rx_trap_map_stat_obj_dbal_fields_t stat_obj_info;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&stat_obj_info, 0, sizeof(dnx_rx_trap_map_stat_obj_dbal_fields_t));

    /** Statistical objects clear configuration */
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_STAT_OBJ_VALID_CLEAR,
                                                        INST_SINGLE, &stat_obj_valid_clear));
    config_p->stat_clear_bitmap = ~stat_obj_valid_clear & DNX_RX_TRAP_ACTION_STAT_OBJ_CLEAR_DEFAULT;

    /** Statistical objects overwrite configuration */
    for (stat_obj_to_ow = 0; stat_obj_to_ow < max_nof_stat_objs_to_ow; stat_obj_to_ow++)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_stat_obj_map_info_get_dispatch(unit, stat_obj_to_ow, &stat_obj_info));
        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id,
                                                            stat_obj_info.overwrite, INST_SINGLE, &stat_obj_ow));

        if (stat_obj_ow)
        {
            config_p->stat_obj_config_len = stat_obj_to_ow + 1;
            SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id,
                                                                stat_obj_info.index,
                                                                INST_SINGLE,
                                                                (uint32 *)
                                                                &config_p->stat_obj_config_arr
                                                                [stat_obj_to_ow].counter_command_id));
            SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                            (unit, entry_handle_id, stat_obj_info.value, INST_SINGLE,
                             &config_p->stat_obj_config_arr[stat_obj_to_ow].stat_id));
            SHR_IF_ERR_EXIT(dbal_entry_handle_value_field8_get
                            (unit, entry_handle_id, stat_obj_info.offset_by_qual,
                             INST_SINGLE, &config_p->stat_obj_config_arr[stat_obj_to_ow].is_offset_by_qual_enable));
            SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                            (unit, entry_handle_id, stat_obj_info.type, INST_SINGLE,
                             (uint32 *) &config_p->stat_obj_config_arr[stat_obj_to_ow].stat_object_type));
            SHR_IF_ERR_EXIT(dbal_entry_handle_value_field8_get
                            (unit, entry_handle_id, stat_obj_info.is_meter, INST_SINGLE,
                             &config_p->stat_obj_config_arr[stat_obj_to_ow].is_meter));
        }
    }

    /** Statistical metadata configuration */
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_STATISTIC_META_DATA,
                                                        INST_SINGLE, &config_p->stat_metadata_mask));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function configure FWD HW Action of trap for specific ingress trap id.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_type   -  trap type to configure
*   \param [in] config_p  - pointer to trap configuration configuration that translates to HW
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_fwd_action_entry_hw_set(
    int unit,
    int trap_type,
    bcm_rx_trap_config_t * config_p)
{
    uint32 entry_handle_id;
    uint32 nof_cores;
    uint32 core_id;
    int system_headers_mode = DNX_RX_TRAP_SYSTEM_HEADERS_MODE_GET(unit);

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(config_p, _SHR_E_PARAM, "config_p");

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_FWD_ACTION_TABLE, &entry_handle_id));
    nof_cores = dnx_data_device.general.nof_cores_get(unit);

    if (config_p->core_config_arr_len > nof_cores)
    {
        SHR_ERR_EXIT(_SHR_E_CONFIG, "core_config_arr_len value (%d) is larger than number of device cores (%d)\n",
                     config_p->core_config_arr_len, nof_cores);
    }

    /** Configure action per core */
    DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core_id)
    {
        /** key construction*/
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, trap_type);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);

        /** Set the Values */
        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_destination_set(unit, core_id, entry_handle_id, config_p));

        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_out_lif_set(unit, core_id, entry_handle_id, config_p));

        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_stat_obj_set(unit, entry_handle_id, config_p));

        /** Set Traffic class action attribute */
        dnx_rx_trap_ingress_action_with_flag_and_value_hw_set(unit, entry_handle_id, config_p->flags,
                                                              BCM_RX_TRAP_UPDATE_PRIO,
                                                              DBAL_FIELD_TRAFFIC_CLASS_OVERWRITE,
                                                              DBAL_FIELD_TRAFFIC_CLASS_VALUE, config_p->prio);
        /** Set Drop Precedence action attribute */
        dnx_rx_trap_ingress_action_with_flag_and_value_hw_set(unit, entry_handle_id, config_p->flags,
                                                              BCM_RX_TRAP_UPDATE_COLOR,
                                                              DBAL_FIELD_DROP_PRECEDENCE_OVERWRITE,
                                                              DBAL_FIELD_DROP_PRECEDENCE_VALUE, config_p->color);

        /** Set Meter command action attribute */
        dnx_rx_trap_ingress_action_with_flag_and_value_hw_set(unit, entry_handle_id, config_p->flags,
                                                              BCM_RX_TRAP_UPDATE_METER_CMD,
                                                              DBAL_FIELD_DROP_PRECEDENCE_METER_COMMAND_OVERWRITE,
                                                              DBAL_FIELD_DROP_PRECEDENCE_METER_COMMAND_VALUE,
                                                              config_p->meter_cmd);

        /** Set Egress strength overwrite action attribute */
        dnx_rx_trap_ingress_action_with_flag_and_value_hw_set(unit, entry_handle_id, config_p->flags,
                                                              BCM_RX_TRAP_UPDATE_MAPPED_STRENGTH,
                                                              DBAL_FIELD_FWD_STRENGTH_OVERWRITE,
                                                              DBAL_FIELD_FWD_STRENGTH_VALUE,
                                                              config_p->mapped_trap_strength);

        /** Set Ethernet encapsulation action attribute */
        dnx_rx_trap_ingress_action_with_flag_and_value_hw_set(unit, entry_handle_id, config_p->flags,
                                                              BCM_RX_TRAP_UPDATE_ECN_VALUE,
                                                              DBAL_FIELD_ADMIT_PROFILE_OVERWRITE,
                                                              DBAL_FIELD_ADMIT_PROFILE_VALUE, config_p->ecn_value);

        /** Set VSQ pointer action attribute */
        dnx_rx_trap_ingress_action_with_flag_and_value_hw_set(unit, entry_handle_id, config_p->flags,
                                                              BCM_RX_TRAP_UPDATE_VSQ, DBAL_FIELD_ST_VSQ_PTR_OVERWRITE,
                                                              DBAL_FIELD_ST_VSQ_PTR, config_p->vsq);

        /** Set Visibilty action attribute */
        dnx_rx_trap_ingress_action_with_flag_and_value_hw_set(unit, entry_handle_id, config_p->flags,
                                                              BCM_RX_TRAP_UPDATE_VISIBILITY,
                                                              DBAL_FIELD_VISIBILITY_OVERWRITE,
                                                              DBAL_FIELD_VISIBILITY_VALUE, config_p->visibility_value);

        /** Set trap_trap action attribute to replace PPH fowarding code with TRAP, i.e forwarding code=trap_id. */
        dnx_rx_trap_ingress_action_with_flag_hw_set(unit, entry_handle_id, config_p->flags, BCM_RX_TRAP_TRAP,
                                                    DBAL_FIELD_TRAP);

        if (dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_bypass_filtering_action))
        {
            /** Set action attribute to bypass filters */
            dnx_rx_trap_ingress_action_with_flag_hw_set(unit, entry_handle_id, config_p->flags,
                                                        BCM_RX_TRAP_BYPASS_FILTERS, DBAL_FIELD_BYPASS_FILTERING);
        }

        /** Set action attribute to disable learning */
        dnx_rx_trap_ingress_action_with_flag_hw_set(unit, entry_handle_id, config_p->flags, BCM_RX_TRAP_LEARN_DISABLE,
                                                    DBAL_FIELD_LEARN_DISABLE);

        /** Set action attribute to add vsi to desintaion value */
        dnx_rx_trap_ingress_action_with_flag_hw_set(unit, entry_handle_id, config_p->flags, BCM_RX_TRAP_UPDATE_ADD_VLAN,
                                                    DBAL_FIELD_DESTINATION_ADD_VSI);

        /** Set action attribute to clear latency_flow_id, i.e latency_flow_id=0 */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LATENCY_FLOW_ID_OVERWRITE, INST_SINGLE,
                                     config_p->latency_flow_id_clear);

        if (dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_snoop_code_clear_action) == TRUE)
        {
            /** Set action to clear the snoop code */
            dnx_rx_trap_ingress_action_with_flag_hw_set(unit, entry_handle_id, config_p->flags2,
                                                        BCM_RX_TRAP_FLAGS2_SNOOP_CODE_CLEAR,
                                                        DBAL_FIELD_SNOOP_CODE_CLEAR);
        }

        if (dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_mirror_code_clear_action) == TRUE)
        {
            /** Set action to clear the mirror code */
            dnx_rx_trap_ingress_action_with_flag_hw_set(unit, entry_handle_id, config_p->flags2,
                                                        BCM_RX_TRAP_FLAGS2_MIRROR_CODE_CLEAR,
                                                        DBAL_FIELD_MIRROR_CODE_CLEAR);
        }

        if (dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_stat_sampling_code_clear_action) == TRUE)
        {
            /** Set action to clear the statistical sampling code */
            dnx_rx_trap_ingress_action_with_flag_hw_set(unit, entry_handle_id, config_p->flags2,
                                                        BCM_RX_TRAP_FLAGS2_STAT_SAMPLING_CODE_CLEAR,
                                                        DBAL_FIELD_STAT_SAMPLING_CODE_CLEAR);
        }

        if (config_p->flags & BCM_RX_TRAP_UPDATE_FORWARDING_HEADER)
        {
            bcm_rx_trap_forwarding_header_t actual_forwarding_header =
                config_p->forwarding_header - bcmRxTrapForwardingHeaderPacketStart;
            if (config_p->forwarding_header == bcmRxTrapForwardingHeaderOamBfdPdu)
            {
                if (system_headers_mode == DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO2_MODE)
                {
                    /*
                     * bcmRxTrapForwardingHeaderOamBfdPdu supported only in Jer1 mode
                     */
                    SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                                 "bcmRxTrapForwardingHeaderOamBfdPdu type not supported. Set egress_forwarding_index to 7 instead,"
                                 "along with BCM_RX_TRAP_UPDATE_EGRESS_FWD_INDEX flag.\n");

                }
                else
                {
                    /** In Jer1 mode bcmRxTrapForwardingHeaderOamBfdPdu should be 7 */
                    actual_forwarding_header = 7;
                }
            }

            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FWD_LAYER_INDEX_OVERWRITE, INST_SINGLE,
                                         TRUE);
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FWD_LAYER_INDEX_VALUE, INST_SINGLE,
                                         actual_forwarding_header);
            if (dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_oam_offset_actions)
                && (actual_forwarding_header == 7))
            {
                dnx_rx_trap_ingress_action_with_flag_hw_set(unit, entry_handle_id, config_p->flags,
                                                            BCM_RX_TRAP_UPDATE_FORWARDING_HEADER,
                                                            DBAL_FIELD_USE_OAM_OFFSET);
            }
        }
        else
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FWD_LAYER_INDEX_OVERWRITE, INST_SINGLE,
                                         FALSE);
        }

        /** Set Egress parsing index overwrite action attribute */
        dnx_rx_trap_ingress_action_with_flag_and_value_hw_set(unit, entry_handle_id, config_p->flags,
                                                              BCM_RX_TRAP_UPDATE_EGRESS_FWD_INDEX,
                                                              DBAL_FIELD_EGRESS_PARSING_INDEX_OVERWRITE,
                                                              DBAL_FIELD_EGRESS_PARSING_INDEX_VALUE,
                                                              config_p->egress_forwarding_index);
        if (config_p->egress_forwarding_index == 7
            && dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_oam_offset_actions))
        {
            dnx_rx_trap_ingress_action_with_flag_hw_set(unit, entry_handle_id, config_p->flags,
                                                        BCM_RX_TRAP_UPDATE_EGRESS_FWD_INDEX, DBAL_FIELD_USE_OAM_OFFSET);
        }

        /** Unsupported flags */
        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_action_flag_not_supported(unit, config_p->flags,
                                                                      BCM_RX_TRAP_UPDATE_FORWARDING_TYPE));

        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_action_flag_not_supported(unit, config_p->flags,
                                                                      BCM_RX_TRAP_UPDATE_POLICER));

        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_action_flag_not_supported(unit, config_p->flags,
                                                                      BCM_RX_TRAP_UPDATE_ETHERNET_POLICER));

        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_action_flag_not_supported(unit, config_p->flags,
                                                                      BCM_RX_TRAP_UPDATE_COUNTER));

        /** Actually was never supported and probably should have been used for replacing trap alloc */
        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_action_flag_not_supported(unit, config_p->flags, BCM_RX_TRAP_REPLACE));

        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_action_flag_not_supported(unit, config_p->flags,
                                                                      BCM_RX_TRAP_POLICER_RESULT_INGRESS));

        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_action_flag_not_supported(unit, config_p->flags,
                                                                      BCM_RX_TRAP_POLICER_RESULT_EGRESS));

        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_action_flag_not_supported(unit, config_p->flags,
                                                                      BCM_RX_TRAP_UPDATE_COUNTER_2));

        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_action_flag_not_supported(unit, config_p->flags,
                                                                      BCM_RX_TRAP_DROP_AND_LEARN));

        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_action_flag_not_supported(unit, config_p->flags,
                                                                      BCM_RX_TRAP_UPDATE_POLICER_2));

        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

        /** Clear the entry for other cores */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_TRAP_INGRESS_FWD_ACTION_TABLE, entry_handle_id));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function get configuration FWD HW Action of trap for specific ingress trap id.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_type   -  trap type to configure
*   \param [in] config_p  -  Pointer type of bcm_rx_trap_config_t \n
*               \b As \b output - \n
*               Pointer will be filled by configuration that translates to HW
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_fwd_action_entry_hw_get(
    int unit,
    int trap_type,
    bcm_rx_trap_config_t * config_p)
{
    uint32 entry_handle_id, core_id;
    uint32 tc_ow, dp_ow, trap_trap, bypass_filtering, learn_disable, add_vsi, egress_prs_index_ow;
    uint32 fwd_hdr, fwd_hdr_ow, meter_cmd_ow, mapped_strength_ow, ecn_ow, vsq_ow, visibility_ow;
    uint32 snoop_code_clear = FALSE, mirror_code_clear = FALSE, stat_sampling_code_clear = FALSE;
    uint8 bytes_to_rm_ow;
    int system_headers_mode = DNX_RX_TRAP_SYSTEM_HEADERS_MODE_GET(unit);
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(config_p, _SHR_E_PARAM, "config_p");

    /** Reset all flags*/
    config_p->flags = 0;

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_FWD_ACTION_TABLE, &entry_handle_id));

    /*
     * key construction
     */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, trap_type);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, DBAL_CORE_DEFAULT);

    /** Get fields - all results fields of the table will be read to handle buffer */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));

    /** Get the values */
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_TRAFFIC_CLASS_OVERWRITE,
                                                        INST_SINGLE, &tc_ow));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_DROP_PRECEDENCE_OVERWRITE,
                                                        INST_SINGLE, &dp_ow));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_TRAP, INST_SINGLE,
                                                        &trap_trap));

    if (dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_bypass_filtering_action))
    {
        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                        (unit, entry_handle_id, DBAL_FIELD_BYPASS_FILTERING, INST_SINGLE, &bypass_filtering));
    }

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_LEARN_DISABLE, INST_SINGLE,
                                                        &learn_disable));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_DESTINATION_ADD_VSI,
                                                        INST_SINGLE, &add_vsi));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field8_get(unit, entry_handle_id, DBAL_FIELD_BYTES_TO_REMOVE_OVERWRITE,
                                                       INST_SINGLE, &bytes_to_rm_ow));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field8_get(unit, entry_handle_id, DBAL_FIELD_LATENCY_FLOW_ID_OVERWRITE,
                                                       INST_SINGLE, &config_p->latency_flow_id_clear));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_FWD_LAYER_INDEX_OVERWRITE,
                                                        INST_SINGLE, &fwd_hdr_ow));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id,
                                                        DBAL_FIELD_DROP_PRECEDENCE_METER_COMMAND_OVERWRITE, INST_SINGLE,
                                                        &meter_cmd_ow));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_FWD_STRENGTH_OVERWRITE,
                                                        INST_SINGLE, &mapped_strength_ow));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_ADMIT_PROFILE_OVERWRITE,
                                                        INST_SINGLE, &ecn_ow));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_ST_VSQ_PTR_OVERWRITE,
                                                        INST_SINGLE, &vsq_ow));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_VISIBILITY_OVERWRITE,
                                                        INST_SINGLE, &visibility_ow));

    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id,
                                                        DBAL_FIELD_EGRESS_PARSING_INDEX_OVERWRITE, INST_SINGLE,
                                                        &egress_prs_index_ow));

    if (dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_snoop_code_clear_action) == TRUE)
    {
        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                        (unit, entry_handle_id, DBAL_FIELD_SNOOP_CODE_CLEAR, INST_SINGLE, &snoop_code_clear));
    }

    if (dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_mirror_code_clear_action) == TRUE)
    {
        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                        (unit, entry_handle_id, DBAL_FIELD_MIRROR_CODE_CLEAR, INST_SINGLE, &mirror_code_clear));
    }

    if (dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_stat_sampling_code_clear_action) == TRUE)
    {
        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                        (unit, entry_handle_id, DBAL_FIELD_STAT_SAMPLING_CODE_CLEAR, INST_SINGLE,
                         &stat_sampling_code_clear));
    }

    /*
     * The flags according the read HW
     */
    /** Check whether Egress_parsing_index was set as action*/
    if (egress_prs_index_ow == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_EGRESS_FWD_INDEX;
        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id,
                                                            DBAL_FIELD_EGRESS_PARSING_INDEX_VALUE, INST_SINGLE,
                                                            &config_p->egress_forwarding_index));
    }

    /** Check whether TC was set as action*/
    if (tc_ow == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_PRIO;
        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_TRAFFIC_CLASS_VALUE,
                                                            INST_SINGLE, (uint32 *) &config_p->prio));
    }

    /** Check whether DP was set as action*/
    if (dp_ow == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_COLOR;
        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_DROP_PRECEDENCE_VALUE,
                                                            INST_SINGLE, (uint32 *) &config_p->color));
    }

    /** Check whether trap_trap was set as action*/
    if (trap_trap == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_TRAP;
    }

    /** Check whether bypass filtering was set as action*/
    if (bypass_filtering == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_BYPASS_FILTERS;
    }

    /** Check whether learn disable was set as action*/
    if (learn_disable == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_LEARN_DISABLE;
    }

    /** Check whether distination equal vsi was set as action*/
    if (add_vsi == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_ADD_VLAN;
    }

    /** Check whether snoop code clear was set as action*/
    if (snoop_code_clear == TRUE)
    {
        config_p->flags2 |= BCM_RX_TRAP_FLAGS2_SNOOP_CODE_CLEAR;
    }

    /** Check whether mirror code clear was set as action*/
    if (mirror_code_clear == TRUE)
    {
        config_p->flags2 |= BCM_RX_TRAP_FLAGS2_MIRROR_CODE_CLEAR;
    }

    /** Check whether snoop code clear was set as action*/
    if (stat_sampling_code_clear == TRUE)
    {
        config_p->flags2 |= BCM_RX_TRAP_FLAGS2_STAT_SAMPLING_CODE_CLEAR;
    }

    /** Check whether forwarding header set as action*/
    if (fwd_hdr_ow == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_FORWARDING_HEADER;
        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_FWD_LAYER_INDEX_VALUE,
                                                            INST_SINGLE, &fwd_hdr));
        config_p->forwarding_header = bcmRxTrapForwardingHeaderPacketStart + fwd_hdr;
        if (system_headers_mode == DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO_MODE && fwd_hdr == 7)
        {
            /*
             * Value 7 in Jericho mode means "OAM/BFD-PDU
             */
            config_p->forwarding_header = bcmRxTrapForwardingHeaderOamBfdPdu;
        }
    }

    /** Check whether meter command set as action*/
    if (meter_cmd_ow == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_METER_CMD;
        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id,
                                                            DBAL_FIELD_DROP_PRECEDENCE_METER_COMMAND_VALUE, INST_SINGLE,
                                                            (uint32 *) &config_p->meter_cmd));
    }

    /** Check whether egress strength overwrite set as action*/
    if (mapped_strength_ow == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_MAPPED_STRENGTH;
        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field8_get(unit, entry_handle_id, DBAL_FIELD_FWD_STRENGTH_VALUE,
                                                           INST_SINGLE, &config_p->mapped_trap_strength));
    }

    /** Check whether ECN value set as action*/
    if (ecn_ow == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_ECN_VALUE;
        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field8_get(unit, entry_handle_id, DBAL_FIELD_ADMIT_PROFILE_VALUE,
                                                           INST_SINGLE, &config_p->ecn_value));
    }

    /** Check whether VSQ pointer set as action*/
    if (vsq_ow == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_VSQ;
        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field16_get(unit, entry_handle_id, DBAL_FIELD_ST_VSQ_PTR,
                                                            INST_SINGLE, &config_p->vsq));
    }

    /** Check whether visibility set as action*/
    if (vsq_ow == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_VISIBILITY;
        SHR_IF_ERR_EXIT(dbal_entry_handle_value_field8_get(unit, entry_handle_id, DBAL_FIELD_VISIBILITY_VALUE,
                                                           INST_SINGLE, &config_p->visibility_value));
    }

    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_stat_obj_get(unit, entry_handle_id, config_p));

    /** get per core configuration */
    DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core_id)
    {
        /** Key construction */
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, trap_type);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);

        /** Get fields - all results fields of the table will be read to handle buffer */
        SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));

        /** Get the values */
        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_destination_get(unit, core_id, entry_handle_id, config_p));
        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_out_lif_get(unit, core_id, entry_handle_id, config_p));

        /** Clear the entry for other cores */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_TRAP_INGRESS_FWD_ACTION_TABLE, entry_handle_id));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set snoop command in action table of ingress traps
* \par DIRECT INPUT:
*   \param [in] unit          -  Unit ID
*   \param [in] trap_type       -  trap type to set its snoop action
*   \param [in] snp_cmd       -  snoop cmd to configure
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
dnx_rx_trap_ingress_snp_action_entry_hw_set(
    int unit,
    int trap_type,
    int snp_cmd)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_SNOOP_ACTION_TABLE, &entry_handle_id));

    /** key construction*/
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, trap_type);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, BCM_CORE_ALL);

    /** Set the values */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SNOOP_CMD, INST_SINGLE, snp_cmd);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get snoop command in action table of ingress traps
* \par DIRECT INPUT:
*   \param [in] unit          -  Unit ID
*   \param [in] trap_type       -  trap type to set its snoop action
*   \param [in] snp_cmd_p       - Pointer type of int \n
*               \b As \b output - \n
*               Pointer will be filled by snoop cmd to configure
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
dnx_rx_trap_ingress_snp_action_entry_hw_get(
    int unit,
    int trap_type,
    int *snp_cmd_p)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_SNOOP_ACTION_TABLE, &entry_handle_id));
    /*
     * key construction
     */

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, trap_type);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, DBAL_CORE_DEFAULT);

    /*
     * Get the snoop command value
     */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_SNOOP_CMD, INST_SINGLE, (uint32 *) snp_cmd_p);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function is to set strength of given ingress trap
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_type   -trap type to configure its strength
*   \param [in] config_p  -  holds the FWD and SNP strength
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_strength_hw_set(
    int unit,
    int trap_type,
    bcm_rx_trap_config_t * config_p)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(config_p, _SHR_E_PARAM, "config_p");

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_FWD_SNP_STRENGTH, &entry_handle_id));
    /*
     * key construction
     */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, trap_type);

    /*
     * Set the values
     */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, INST_SINGLE,
                                 config_p->trap_strength);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_SNP_STRENGTH, INST_SINGLE,
                                 config_p->snoop_strength);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function is to get strength of given ingress trap
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_type   -trap type to configure its strength
*   \param [in] config_p  - Pointer type of bcm_rx_trap_config_t \n
*               \b As \b output - \n
*               Pointer will be filled bywill holds the FWD and SNP strength
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_strength_hw_get(
    int unit,
    int trap_type,
    bcm_rx_trap_config_t * config_p)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(config_p, _SHR_E_PARAM, "config_p");

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_FWD_SNP_STRENGTH, &entry_handle_id));
    /*
     * key construction
     */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, trap_type);

    /*
     * read all table values
     */
    dbal_value_field32_request(unit, entry_handle_id,
                               DBAL_FIELD_TRAP_FWD_STRENGTH, INST_SINGLE, (uint32 *) &config_p->trap_strength);
    dbal_value_field32_request(unit, entry_handle_id,
                               DBAL_FIELD_TRAP_SNP_STRENGTH, INST_SINGLE, (uint32 *) &config_p->snoop_strength);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function clears configuration of trap FWD HW Action for specific ingress trap id.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_type   -  trap type to clear
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * DBAL_TABLE_TRAP_INGRESS_FWD_ACTION_TABLE
*/
static shr_error_e
dnx_rx_trap_ingress_fwd_action_entry_hw_clear(
    int unit,
    int trap_type)
{
    uint32 entry_handle_id;
    uint32 core_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_FWD_ACTION_TABLE, &entry_handle_id));

    /*
     * Configure table per core
     */
    DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core_id)
    {
        /*
         * key construction
         */
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, trap_type);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);

        SHR_IF_ERR_EXIT(dbal_entry_clear(unit, entry_handle_id, DBAL_COMMIT));

        /** Set default values */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_STAT_OBJ_VALID_CLEAR, INST_SINGLE,
                                     DNX_RX_TRAP_ACTION_STAT_OBJ_CLEAR_DEFAULT);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FWD_DESTINATION_VALID, INST_SINGLE, TRUE);

        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function clears configuration of trap SNP HW Action for specific ingress trap id.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_type   -  trap type to clear
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * DBAL_TABLE_TRAP_INGRESS_SNOOP_ACTION_TABLE
*/
static shr_error_e
dnx_rx_trap_ingress_snp_action_entry_hw_clear(
    int unit,
    int trap_type)
{
    uint32 entry_handle_id;
    uint32 core_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_SNOOP_ACTION_TABLE, &entry_handle_id));

    /*
     * Configure table per core
     */
    DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core_id)
    {
        /*
         * key construction
         */
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, trap_type);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);

        SHR_IF_ERR_EXIT(dbal_entry_clear(unit, entry_handle_id, DBAL_COMMIT));
        /** Clear the entry for other cores */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_TRAP_INGRESS_SNOOP_ACTION_TABLE, entry_handle_id));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function is to clear strengths of given ingress trap
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_type   -trap type to configure its strength
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * DBAL_TABLE_TRAP_FWD_SNP_STRENGTH
*/
static shr_error_e
dnx_rx_trap_ingress_strength_hw_clear(
    int unit,
    int trap_type)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_FWD_SNP_STRENGTH, &entry_handle_id));
    /*
     * key construction
     */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, trap_type);

    SHR_IF_ERR_EXIT(dbal_entry_clear(unit, entry_handle_id, DBAL_COMMIT));
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
* Set configuration of bfd over IPv6 invalid UDP checksum trap
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] config_p  -  Structure, holding the information about the snoop and forward strength
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_bfd_ipv6_udp_strength_hw_set(
    int unit,
    bcm_rx_trap_config_t * config_p)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_OAM, &entry_handle_id));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_BFDV6_CHECKSUM_ERROR_FWD_ACT_STRENGTH,
                                 INST_SINGLE, config_p->trap_strength);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_BFDV6_CHECKSUM_ERROR_SNOOP_STRENGTH, INST_SINGLE,
                                 config_p->snoop_strength);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
* Set configuration of Same Interface or ICMP redirect ingress traps
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] same_interface_context_profile      -  Same interface context profile
*   \param [in] config_p  -  Structure, holding the information about the snoop and forward strength
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_same_interface_strength_hw_set(
    int unit,
    dbal_enum_value_field_fer_trap_same_interface_filter_profile_e same_interface_context_profile,
    bcm_rx_trap_config_t * config_p)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_SAME_INTERFACE_MAP, &entry_handle_id));

    /** key construction */
    dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_FER_TRAP_SAME_INTERFACE_FILTER_PROFILE,
                              same_interface_context_profile);
    dbal_entry_key_field8_range_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_SAME_INTERFACE_FILTER, DBAL_RANGE_ALL,
                                    DBAL_RANGE_ALL);
    dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_IN_PORT_SAME_INTERFACE_FILTER_PROFILE,
                              DBAL_ENUM_FVAL_IN_PORT_SAME_INTERFACE_FILTER_PROFILE_ENABLE);

    /** Set values */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, INST_SINGLE,
                                 config_p->trap_strength);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_SNP_STRENGTH, INST_SINGLE,
                                 config_p->snoop_strength);

    if (same_interface_context_profile == DBAL_ENUM_FVAL_FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_IP)
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, INST_SINGLE,
                                     DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FER_ICMP_REDIRECT);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_COMPARE_PORTS, INST_SINGLE, FALSE);
    }
    else
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, INST_SINGLE,
                                     DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FER_SAME_INTERFACE);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_COMPARE_PORTS, INST_SINGLE, TRUE);
    }

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
* Set configuration of gal with flow label trap
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] reset     -  set or reset
*   \param [in] config_p  -  Structure, holding the information about the snoop and forward strength
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_mpls_gal_with_flow_label_strength_hw_update(
    int unit,
    int reset,
    bcm_rx_trap_config_t * config_p)
{

    uint32 dummy_in_lif;
    uint32 entry_handle_id;
    uint32 trap_dest, snp_strength = 0, fwd_strength = 0, trap_id;
    uint32 destination = 0;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /*
     * Take table handle:
     */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_GAL_WITH_FLOW_LABEL_DUMMY_LIF, &entry_handle_id));
    /*
     * Set values:
     */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LIF_INDEX, INST_SINGLE, &dummy_in_lif);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
    /*
     * Take table handle:
     */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_IN_LIF_FORMAT_LIF_SPOOFING_CHECK, &entry_handle_id));
    /*
     * Set keys:
     */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF, dummy_in_lif);
    /*
     * Set values:
     */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RESULT_TYPE, INST_SINGLE,
                                 DBAL_RESULT_TYPE_IN_LIF_FORMAT_LIF_SPOOFING_CHECK_IN_LIF_P2P_COMPACT);

    trap_dest = 0;
    trap_id = DBAL_ENUM_FVAL_INGRESS_TRAP_ID_VTT_MPLS_CONTROL_WORD_TRAP;
    snp_strength = (reset == TRUE) ? 0 : config_p->snoop_strength;
    fwd_strength = (reset == TRUE) ? 0 : config_p->trap_strength;

    SHR_IF_ERR_EXIT(dbal_fields_struct_field_encode
                    (unit, DBAL_FIELD_INGRESS_TRAP_DEST, DBAL_FIELD_TRAP_SNP_STRENGTH, &snp_strength, &trap_dest));
    SHR_IF_ERR_EXIT(dbal_fields_struct_field_encode
                    (unit, DBAL_FIELD_INGRESS_TRAP_DEST, DBAL_FIELD_TRAP_FWD_STRENGTH, &fwd_strength, &trap_dest));
    SHR_IF_ERR_EXIT(dbal_fields_struct_field_encode
                    (unit, DBAL_FIELD_INGRESS_TRAP_DEST, DBAL_FIELD_INGRESS_TRAP_ID, &trap_id, &trap_dest));

    SHR_IF_ERR_EXIT(dbal_fields_parent_field32_value_set
                    (unit, DBAL_FIELD_DESTINATION, DBAL_FIELD_INGRESS_TRAP_DEST, &trap_dest, &destination));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DESTINATION, INST_SINGLE, destination);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
* Clear configuration of bfd over IPv6 invalid UDP checksum trap
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * DBAL_TABLE_TRAP_FWD_SNP_STRENGTH
*/
static shr_error_e
dnx_rx_trap_ingress_bfd_ipv6_udp_strength_hw_clear(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_OAM, &entry_handle_id));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_BFDV6_CHECKSUM_ERROR_FWD_ACT_STRENGTH,
                                 INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_BFDV6_CHECKSUM_ERROR_SNOOP_STRENGTH, INST_SINGLE,
                                 0x0);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
* Clear configuration of Same Interface or ICMP redirect ingress traps
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] same_interface_context_profile      -  Same interface context profile
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * DBAL_TABLE_TRAP_FWD_SNP_STRENGTH
*/
static shr_error_e
dnx_rx_trap_ingress_same_interface_strength_hw_clear(
    int unit,
    dbal_enum_value_field_fer_trap_same_interface_filter_profile_e same_interface_context_profile)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_SAME_INTERFACE_MAP, &entry_handle_id));

    /** key construction */
    dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_FER_TRAP_SAME_INTERFACE_FILTER_PROFILE,
                              same_interface_context_profile);
    dbal_entry_key_field8_range_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_SAME_INTERFACE_FILTER, DBAL_RANGE_ALL,
                                    DBAL_RANGE_ALL);
    dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_IN_PORT_SAME_INTERFACE_FILTER_PROFILE,
                              DBAL_ENUM_FVAL_IN_PORT_SAME_INTERFACE_FILTER_PROFILE_ENABLE);

    SHR_IF_ERR_EXIT(dbal_entry_clear(unit, entry_handle_id, DBAL_COMMIT));
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
* Get configuration of bfd over IPv6 invalid UDP checksum trap
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] config_p  - Structure, holding the information about the snoop and forward strength
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_bfd_ipv6_udp_strength_hw_get(
    int unit,
    bcm_rx_trap_config_t * config_p)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(config_p, _SHR_E_PARAM, "config_p");

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_OAM, &entry_handle_id));

    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_CFG_BFDV6_CHECKSUM_ERROR_FWD_ACT_STRENGTH,
                               INST_SINGLE, (uint32 *) &config_p->trap_strength);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_CFG_BFDV6_CHECKSUM_ERROR_SNOOP_STRENGTH,
                               INST_SINGLE, (uint32 *) &config_p->snoop_strength);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
* Get configuration of Same Interface or ICMP redirect ingress traps
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] same_interface_context_profile      -  Same interface context profile
*   \param [in] config_p  - Structure, holding the information about the snoop and forward strength
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_same_interface_strength_hw_get(
    int unit,
    dbal_enum_value_field_fer_trap_same_interface_filter_profile_e same_interface_context_profile,
    bcm_rx_trap_config_t * config_p)
{
    uint32 entry_handle_id, trap_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(config_p, _SHR_E_PARAM, "config_p");

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_SAME_INTERFACE_MAP, &entry_handle_id));

    /** key construction */
    dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_FER_TRAP_SAME_INTERFACE_FILTER_PROFILE,
                              same_interface_context_profile);
    dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_SAME_INTERFACE_FILTER, 0);
    dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_IN_PORT_SAME_INTERFACE_FILTER_PROFILE,
                              DBAL_ENUM_FVAL_IN_PORT_SAME_INTERFACE_FILTER_PROFILE_ENABLE);

    /** Get the values */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, INST_SINGLE,
                               (uint32 *) &config_p->trap_strength);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_TRAP_SNP_STRENGTH, INST_SINGLE,
                               (uint32 *) &config_p->snoop_strength);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, INST_SINGLE, &trap_id);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Clear ingress trap stregnths.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_type  -  ingress trap type (HW trap id value) to configure
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_strength_clear(
    int unit,
    int trap_type)
{
    int is_strengthless = TRUE;
    bcm_rx_trap_config_t trap_config;
    SHR_FUNC_INIT_VARS(unit);

    bcm_rx_trap_config_t_init(&trap_config);

    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_strengthless_trap_check(unit, trap_type, &is_strengthless));

    if (!is_strengthless)
    {
        /** Same interface trap have dedicated memory which needs to be handled differently than other ingress traps*/
        switch (trap_type)
        {
            case DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FER_SAME_INTERFACE:
                SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_same_interface_strength_hw_clear(unit,
                                                                                     DBAL_ENUM_FVAL_FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_DEFAULT));
                break;
            case DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FER_ICMP_REDIRECT:
                SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_same_interface_strength_hw_clear(unit,
                                                                                     DBAL_ENUM_FVAL_FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_IP));
                break;
            case DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_BFD_O_IPV6_UDP_CHECKSUM:
                SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_bfd_ipv6_udp_strength_hw_clear(unit));
                break;

                /*
                 * Another trap point for G-ACH
                 * So legacy configuration is also needed
                 */
            case DBAL_ENUM_FVAL_INGRESS_TRAP_ID_VTT_MPLS_CONTROL_WORD_TRAP:
                
                if (dnx_data_mpls.general.gach_with_flow_label_supported_get(unit))
                {
                    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_mpls_gal_with_flow_label_strength_hw_update(unit, TRUE, NULL));
                }
            default:
                SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_strength_hw_clear(unit, trap_type));
                break;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Clear extra configurations done by using ingress trap flags.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_type  -  Ingress trap type (HW trap id value)
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_flags_extra_configuration_clear(
    int unit,
    int trap_type)
{
    uint32 acl_trap_profile;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_field_context_acl_cpu_trap_code_profile_get(unit, trap_type, &acl_trap_profile));
    if (acl_trap_profile != 0)
    {
        SHR_IF_ERR_EXIT(dnx_field_context_acl_cpu_trap_code_profile_update(unit, trap_type, 0));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Clear the ingress trap action profile: trap stregnth and action.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_type  -  ingress trap type (HW trap id value) to configure
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_clear(
    int unit,
    int trap_type)
{
    SHR_FUNC_INIT_VARS(unit);

    /** Clear forward and snoop strengths */
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_strength_clear(unit, trap_type));

    /** Clear the actions of TRAP FWD and SNOOP*/
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_fwd_action_entry_hw_clear(unit, trap_type));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_snp_action_entry_hw_clear(unit, trap_type));

    /** Clear extra configurations done by trap flags. */
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_flags_extra_configuration_clear(unit, trap_type));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Clear ingress trap stregnths.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_type  -  ingress trap type (HW trap id value) to configure
*   \param [in] config_p  -  Hold the action-profile configuration to set for specific trap
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_strength_set(
    int unit,
    int trap_type,
    bcm_rx_trap_config_t * config_p)
{
    int is_strengthless = TRUE;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_strengthless_trap_check(unit, trap_type, &is_strengthless));

    if (!is_strengthless)
    {
        /** Same interface trap have dedicated memory which needs to be handled differently than other ingress traps*/
        switch (trap_type)
        {
            case DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FER_SAME_INTERFACE:
                SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_same_interface_strength_hw_set(unit,
                                                                                   DBAL_ENUM_FVAL_FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_DEFAULT,
                                                                                   config_p));
                break;
            case DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FER_ICMP_REDIRECT:
                SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_same_interface_strength_hw_set(unit,
                                                                                   DBAL_ENUM_FVAL_FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_IP,
                                                                                   config_p));
                break;
            case DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_BFD_O_IPV6_UDP_CHECKSUM:
                SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_bfd_ipv6_udp_strength_hw_set(unit, config_p));
                break;

                /*
                 * Another trap point for control word
                 * So legacy configuration is also needed
                 */
            case DBAL_ENUM_FVAL_INGRESS_TRAP_ID_VTT_MPLS_CONTROL_WORD_TRAP:
                
                if (dnx_data_mpls.general.gach_with_flow_label_supported_get(unit))
                {
                    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_mpls_gal_with_flow_label_strength_hw_update
                                    (unit, FALSE, config_p));
                }
            default:
                SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_strength_hw_set(unit, trap_type, config_p));
                break;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set the ingress trap action profile: trap stregnth and action.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_type  -  ingress trap type (HW trap id value) to configure
*   \param [in] config_p  -  Hold the action-profile configuration to set for specific trap
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_set(
    int unit,
    int trap_type,
    bcm_rx_trap_config_t * config_p)
{

    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(config_p, _SHR_E_PARAM, "config_p");

    /** clear old trap configuration */
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_clear(unit, trap_type));

    /** Set forward and snoop strengths */
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_strength_set(unit, trap_type, config_p));

    /** Set the action of TRAP FWD and SNOOP*/
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_fwd_action_entry_hw_set(unit, trap_type, config_p));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_snp_action_entry_hw_set(unit, trap_type, config_p->snoop_cmnd));

    if (config_p->flags2 & BCM_RX_TRAP_FLAGS2_UPDATE_ACL_PROFILE)
    {
        /** Update the ACL CPU trap code profile. */
        SHR_IF_ERR_EXIT(dnx_field_context_acl_cpu_trap_code_profile_update(unit, trap_type, 1));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *  Fill the ERPP trap profile fields.
 *  ERRP trap profile holds the trap forward strength, snoop
 *  strength and traps actions.
 * \param [in] unit -The unit number.
 * \param [in] config_p - the trap structure from which relevant field are taken to
 *   forwarding action profile. fields are trap actions, forward
 *   strength and snoop strength.
 * \param [out] erpp_config_p -The erpp forwarding action profile. holds trap actions,
 *   forward strength and forward snoop.
 * \par INDIRECT INPUT:
 *   * None
 * \par DIRECT OUTPUT:
 *   shr_error_e -  Error Type
 * \par INDIRECT OUTPUT:
 *   * None
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_rx_trap_erpp_config_from_config_fill(
    int unit,
    bcm_rx_trap_config_t * config_p,
    dnx_rx_trap_erpp_config_t * erpp_config_p)
{
    bcm_gport_t out_lif_gport;
    dnx_algo_gpm_gport_hw_resources_t gport_hw_resources;
    int nof_snoop_profiles, nof_mirror_profiles;
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(erpp_config_p, _SHR_E_PARAM, "erpp_config_p");
    SHR_NULL_CHECK(config_p, _SHR_E_PARAM, "config_p");

    SHR_IF_ERR_EXIT(dnx_rx_trap_erpp_config_t_init(unit, erpp_config_p));

    nof_snoop_profiles = (dnx_data_snif.egress.snoop_nof_profiles_get(unit) / 2);
    nof_mirror_profiles = (dnx_data_snif.egress.mirror_nof_profiles_get(unit) / 2);

    /*
     * Set TC
     */
    if (config_p->flags & BCM_RX_TRAP_UPDATE_PRIO)
    {
        erpp_config_p->tc = config_p->prio;
        erpp_config_p->tc_valid = TRUE;
    }

    /*
     * Set DP
     */
    if (config_p->flags & BCM_RX_TRAP_UPDATE_COLOR)
    {
        erpp_config_p->dp = config_p->color;
        erpp_config_p->dp_valid = TRUE;
    }

    /*
     * Set QOS id
     */
    if (config_p->flags & BCM_RX_TRAP_UPDATE_QOS_MAP_ID)
    {
        erpp_config_p->qos_id = config_p->qos_map_id;
        erpp_config_p->qos_id_valid = TRUE;
    }

    /*
     * Set CUD
     */
    if (config_p->flags & BCM_RX_TRAP_UPDATE_ENCAP_ID)
    {
        /** Check if input is OUTLIF */
        if (BCM_GPORT_IS_SET(config_p->encap_id))
        {
            /*
             * Get local_outlif and write that to HW
             */
            out_lif_gport = config_p->encap_id;
            SHR_IF_ERR_REPLACE_AND_EXIT(dnx_algo_gpm_gport_to_hw_resources(unit,
                                                                           out_lif_gport,
                                                                           DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_EGRESS,
                                                                           &gport_hw_resources), _SHR_E_NOT_FOUND,
                                        _SHR_E_PARAM);
            erpp_config_p->outlif_or_mcdb_ptr = gport_hw_resources.local_out_lif;
        }
        else
        {
            /*
             * Assign ACE pointer, which has no encoding
             */
            erpp_config_p->outlif_or_mcdb_ptr = config_p->encap_id;
        }
        erpp_config_p->outlif_or_mcdb_ptr_valid = TRUE;

    }

    /*
     * Set Counter_0
     */
    if (config_p->flags & BCM_RX_TRAP_UPDATE_COUNTER)
    {
        erpp_config_p->counter_profile_valid[0] = TRUE;
        erpp_config_p->counter_profile[0] = config_p->stat_obj_config_arr[0].stat_profile;

        erpp_config_p->counter_ptr_valid[0] = TRUE;
        erpp_config_p->counter_ptr[0] = config_p->stat_obj_config_arr[0].stat_id;
    }

    /*
     * Set Counter_1
     */
    if (config_p->flags & BCM_RX_TRAP_UPDATE_COUNTER_2)
    {
        erpp_config_p->counter_profile_valid[1] = TRUE;
        erpp_config_p->counter_profile[1] = config_p->stat_obj_config_arr[1].stat_profile;

        erpp_config_p->counter_ptr_valid[1] = TRUE;
        erpp_config_p->counter_ptr[1] = config_p->stat_obj_config_arr[1].stat_id;
    }

    /*
     * Set pp drop reason
     */
    if (config_p->pp_drop_reason > 0)
    {
        erpp_config_p->pp_drop_reason_valid = TRUE;
        erpp_config_p->pp_drop_reason = config_p->pp_drop_reason;
    }

    /*
     * Set Mirror Profile - without encoding
     */
    if (config_p->mirror_profile > 0)
    {
        if (config_p->mirror_profile >= nof_mirror_profiles)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Mirror profile %d is bigger than allowed for ERPP trap action."
                         "Must be between 0-3. \n", config_p->mirror_profile);
        }
        erpp_config_p->mirror_profile_valid = TRUE;
        erpp_config_p->mirror_profile = config_p->mirror_profile;
    }

    /*
     * Set Snoop Profile - without encoding
     */
    if (config_p->snoop_cmnd > 0)
    {
        if (config_p->snoop_cmnd >= nof_snoop_profiles)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Snoop profile %d is bigger than allowed for ERPP trap action."
                         "Must be between 0-3. \n", config_p->snoop_cmnd);
        }
        erpp_config_p->snoop_profile_valid = TRUE;
        erpp_config_p->snoop_profile = config_p->snoop_cmnd;
    }

    /*
     * Set destination system port
     */
    if (config_p->flags & BCM_RX_TRAP_UPDATE_DEST)
    {
        /** Verify trap destination is not trunk gport */
        if (BCM_GPORT_IS_TRUNK(config_p->dest_port))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Trunk gport cannot be configured as ERPP trap destination! \n");
        }

        if (config_p->core_config_arr != NULL)
        {
            /** Check there is at least one core configured */
            if (config_p->core_config_arr_len < 1)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG, "core_config_arr_len (%d) is invalid and core_config_arr is different "
                             "from NULL\n", config_p->core_config_arr_len);
            }

            if (config_p->dest_port != 0)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG, "Configuration is done per core (core_config_arr valid) but dest_port "
                             "field (shared by cores) is also configured. Please configure dest_port "
                             "per core (core_config_arr[core_num].dest_port)\n");
            }

            erpp_config_p->update_dest = TRUE;
            erpp_config_p->core_config_arr = config_p->core_config_arr;
            erpp_config_p->core_config_arr_len = config_p->core_config_arr_len;
        }
        else
        {
            /** Check per core configuration was not done */
            if (config_p->core_config_arr_len > 0)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG, "core_config_arr is NULL but core_config_arr_len (%d) is non-zero\n",
                             config_p->core_config_arr_len);
            }

            erpp_config_p->update_dest = TRUE;
            erpp_config_p->dest_port = config_p->dest_port;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function configure destination for ERPP trap action.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] core_id      -  core id
*   \param [in] entry_handle_id      -  entry handle alloced id
*   \param [in] erpp_config_p  - pointer to ERPP trap action configuration struct
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_erpp_destination_set(
    int unit,
    uint32 core_id,
    uint32 entry_handle_id,
    dnx_rx_trap_erpp_config_t * erpp_config_p)
{
    bcm_gport_t dest_port;
    dnx_algo_gpm_gport_phy_info_t gport_info;
    bcm_core_t algo_port_core;
    uint32 pp_dsp;
    uint8 single_core_config;
    SHR_FUNC_INIT_VARS(unit);

    if (erpp_config_p->core_config_arr != NULL)
    {
        /** In case of configuration per core */
        dest_port = erpp_config_p->core_config_arr[core_id].dest_port;
        single_core_config = FALSE;
    }
    else
    {
        /** In case of single core configuration */
        dest_port = erpp_config_p->dest_port;
        single_core_config = TRUE;
    }

    if (dest_port == BCM_GPORT_BLACK_HOLE)
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DISCARD, INST_SINGLE, TRUE);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DSP_VALID, INST_SINGLE, FALSE);
    }
    else
    {
        /** Get local port */
        SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get
                        (unit, dest_port, DNX_ALGO_GPM_GPORT_TO_PHY_OP_LOCAL_IS_MANDATORY, &gport_info));

        /** Get core_id and pp dsp */
        SHR_IF_ERR_EXIT(dnx_algo_port_pp_dsp_get(unit, gport_info.local_port, &algo_port_core, &pp_dsp));

        /** Configure PP DSP only if one of the cases applies:
         *  Single core configuration and the core id equals the dest_port core
         *  Per core configuration and the core id configuration exsits in the core_config_arr
         */
        if ((single_core_config && (core_id == algo_port_core))
            || (!single_core_config && (core_id < erpp_config_p->core_config_arr_len)))
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DSP_VALID, INST_SINGLE, TRUE);
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DSP, INST_SINGLE, pp_dsp);
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DISCARD, INST_SINGLE, FALSE);
        }
        else
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DISCARD, INST_SINGLE, FALSE);
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DSP_VALID, INST_SINGLE, FALSE);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 * This function receives ERPP forward action profile, profile
 * number and write to HW the profile actions.
 * \param [in] unit -The unit number.
 * \param [in] profile - Holds the HW profile index.
 * \param [in] erpp_config_p - The ERPP forward action profile which holds the trap actions.
 * \par INDIRECT INPUT:
 *   * None
 * \par DIRECT OUTPUT:
 *   shr_error_e -  Error Type
 * \par INDIRECT OUTPUT:
 *   * None
 * \remark
 *   * None
 * \see
 *   * DBAL_TABLE_ERPP_TRAP_FORWARD_ACTION_PROFILE_TABLE
 */
static shr_error_e
dnx_rx_trap_erpp_action_hw_set(
    int unit,
    int profile,
    dnx_rx_trap_erpp_config_t * erpp_config_p)
{

    uint32 core_id;
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(erpp_config_p, _SHR_E_PARAM, "erpp_config_p");

    DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core_id)
    {
        /** Start setting actions */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ERPP_TRAP_FORWARD_ACTION_PROFILE_TABLE, &entry_handle_id));

        /** Keys */
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_ACTION_PROFILE, (uint32) profile);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, (uint32) core_id);

        /** Values */
        /** Set DP value */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DP_VALID, INST_SINGLE, erpp_config_p->dp_valid);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DP, INST_SINGLE, erpp_config_p->dp);

        /** Set TC value */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TC_VALID, INST_SINGLE, erpp_config_p->tc_valid);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TC, INST_SINGLE, erpp_config_p->tc);

        /** Set QOS ID value */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_COS_PROFILE_VALID, INST_SINGLE,
                                     erpp_config_p->qos_id_valid);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_COS_PROFILE, INST_SINGLE, erpp_config_p->qos_id);

        /** Set destination value */
        if (erpp_config_p->update_dest == TRUE)
        {
            SHR_IF_ERR_EXIT(dnx_rx_trap_erpp_destination_set(unit, core_id, entry_handle_id, erpp_config_p));
        }

        /** Set PP drop reason */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_DROP_REASON_VALID, INST_SINGLE,
                                     erpp_config_p->pp_drop_reason_valid);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_DROP_REASON, INST_SINGLE,
                                     erpp_config_p->pp_drop_reason);

        /** Set Snoop Profile */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SNOOP_PROFILE_VALID, INST_SINGLE,
                                     erpp_config_p->snoop_profile_valid);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SNOOP_PROFILE, INST_SINGLE,
                                     erpp_config_p->snoop_profile);

        /** Set Mirror Profile */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_MIRROR_PROFILE_VALID, INST_SINGLE,
                                     erpp_config_p->mirror_profile_valid);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_MIRROR_PROFILE, INST_SINGLE,
                                     erpp_config_p->mirror_profile);

        /** Set CUD */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CUD_VALID, INST_SINGLE,
                                     erpp_config_p->outlif_or_mcdb_ptr_valid);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CUD, INST_SINGLE,
                                     erpp_config_p->outlif_or_mcdb_ptr);

        /** Set Counter 0 Profile */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PMF_COUNTER_0_PROFILE_VALID, INST_SINGLE,
                                     erpp_config_p->counter_profile_valid[0]);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PMF_COUNTER_0_PROFILE, INST_SINGLE,
                                     erpp_config_p->counter_profile[0]);

         /** Set Counter 0 Pointer */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PMF_COUNTER_0_PTR_VALID, INST_SINGLE,
                                     erpp_config_p->counter_ptr_valid[0]);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PMF_COUNTER_0_PTR, INST_SINGLE,
                                     erpp_config_p->counter_ptr[0]);

        /** Set Counter 1 Profile */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PMF_COUNTER_1_PROFILE_VALID, INST_SINGLE,
                                     erpp_config_p->counter_profile_valid[1]);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PMF_COUNTER_1_PROFILE, INST_SINGLE,
                                     erpp_config_p->counter_profile[1]);

         /** Set Counter 1 Pointer */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PMF_COUNTER_1_PTR_VALID, INST_SINGLE,
                                     erpp_config_p->counter_ptr_valid[1]);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PMF_COUNTER_1_PTR, INST_SINGLE,
                                     erpp_config_p->counter_ptr[1]);

        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Create or update an ERPP forward action profile entry based
 *   on the trap ID.
 * \param [in] unit         -The unit number.
 * \param [in] trap_type    -trap type.
 * \param [in] action_profile_p - Action profile info to be written to HW.
 * \par INDIRECT INPUT:
 *   * None
 * \par DIRECT OUTPUT:
 *   shr_error_e -  Error Type
 * \par INDIRECT OUTPUT:
 *   * None
 * \remark
 *   * None
 * \see
 *   * DBAL_TABLE_ERPP_TRAP_ACTION_PROFILE
 */

static shr_error_e
dnx_rx_trap_erpp_action_profile_hw_set(
    int unit,
    int trap_type,
    dnx_rx_trap_action_profile_t * action_profile_p)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(action_profile_p, _SHR_E_PARAM, "action_profile_p");

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ERPP_TRAP_ACTION_PROFILE, &entry_handle_id));

    /*
     * Keys
     */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ERPP_TRAP_ID, trap_type);

    /*
     * Values
     */
    /*
     * Set forward action profile
     */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_ACTION_PROFILE, INST_SINGLE,
                                 action_profile_p->profile);

    /*
     * Set forward strength
     */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, INST_SINGLE,
                                 action_profile_p->fwd_strength);

    /*
     * Set snoop strength
     */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_SNP_STRENGTH, INST_SINGLE,
                                 action_profile_p->snp_strength);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get erpp trap action profile from HW: trap stregnths and
*  profile number.
* \par DIRECT INPUT:
*   \param [in] unit        -  Unit Id
*   \param [in] trap_type   -  ERPP trap id
*   \param [out] action_profile_p  -  Hold the action profile info from HW
*          action-profile
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_erpp_action_profile_hw_get(
    int unit,
    int trap_type,
    dnx_rx_trap_action_profile_t * action_profile_p)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ERPP_TRAP_ACTION_PROFILE, &entry_handle_id));

    /*
     * key construction
     */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ERPP_TRAP_ID, trap_type);

    /*
     * Set the values
     */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_TRAP_ACTION_PROFILE, INST_SINGLE,
                               (uint32 *) &action_profile_p->profile);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, INST_SINGLE,
                               (uint32 *) &action_profile_p->fwd_strength);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_TRAP_SNP_STRENGTH, INST_SINGLE,
                               (uint32 *) &action_profile_p->snp_strength);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function sets the MTU Profile config.
* \par DIRECT INPUT:
*   \param [in] unit       - unit id
*   \param [in] mtu_key_p  - MTU key
*   \param [in] mtu_data_p - MTU data
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_mtu_profile_hw_set(
    int unit,
    bcm_rx_mtu_profile_key_t * mtu_key_p,
    bcm_rx_mtu_profile_value_t * mtu_data_p)
{
    SHR_FUNC_INIT_VARS(unit);

    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_v1_mtu_profile_hw_set(unit, mtu_key_p, mtu_data_p));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function retrieves the MTU Profile config.
* \par DIRECT INPUT:
*   \param [in] unit       - unit id
*   \param [in] mtu_key_p  - MTU key
*   \param [out] mtu_data_p - MTU data
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_mtu_profile_hw_get(
    int unit,
    bcm_rx_mtu_profile_key_t * mtu_key_p,
    bcm_rx_mtu_profile_value_t * mtu_data_p)
{
    SHR_FUNC_INIT_VARS(unit);

    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_v1_mtu_profile_hw_get(unit, mtu_key_p, mtu_data_p));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function clears the MTU Profile config.
* \par DIRECT INPUT:
*   \param [in] unit       - unit id
*   \param [in] mtu_key_p  - MTU key
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_mtu_profile_hw_clear(
    int unit,
    bcm_rx_mtu_profile_key_t * mtu_key_p)
{
    SHR_FUNC_INIT_VARS(unit);

    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_v1_mtu_profile_hw_clear(unit, mtu_key_p));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Verify function for mtu_profile_set.
* \par DIRECT INPUT:
*   \param [in] unit                    - unit id
*   \param [in] flags                   - Flags(BCM_RX_MTU_XXX)
*   \param [in] mtu_key_p               - MTU Map table key
*   \param [in] mtu_data_p             - MTU Profile config
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_mtu_profile_set_verify(
    int unit,
    uint32 flags,
    bcm_rx_mtu_profile_key_t * mtu_key_p,
    bcm_rx_mtu_profile_value_t * mtu_data_p)
{
    int fwd_action_index, trap_id, max_cmp_layer_type;
    uint8 is_allocated;
    bcm_gport_t snoop_gport;
    SHR_FUNC_INIT_VARS(unit);

    if (flags != BCM_RX_MTU_PORT && flags != BCM_RX_MTU_LIF && flags != BCM_RX_MTU_RIF)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported/Invalid flags have been set, %d flags are invalid", flags);
    }

    if (mtu_key_p->mtu_profile >= dnx_data_trap.etpp.nof_mtu_profiles_get(unit))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The MTU profile(%d) supplied is bigger than the max number of profiles(%d)",
                     mtu_key_p->mtu_profile, (dnx_data_trap.etpp.nof_mtu_profiles_get(unit) - 1));
    }

    if (mtu_data_p->mtu_val > dnx_data_trap.etpp.max_mtu_value_get(unit))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The supplied MTU value(%d) is bigger than the maximum allowed for the device: %d",
                     mtu_data_p->mtu_val, dnx_data_trap.etpp.max_mtu_value_get(unit));
    }

    if (!BCM_GPORT_IS_TRAP(mtu_data_p->trap_gport))
    {
        if (mtu_data_p->trap_gport != BCM_GPORT_INVALID)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "The Trap-Gport is not valid, should be BCM_GPORT_INVALID or valid Trap-Gport");
        }
    }
    else if (BCM_GPORT_IS_TRAP(mtu_data_p->trap_gport)
             && ((BCM_GPORT_TRAP_GET_STRENGTH(mtu_data_p->trap_gport) != 0)
                 && (BCM_GPORT_TRAP_GET_SNOOP_STRENGTH(mtu_data_p->trap_gport) != 0)))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The Trap-Gport is not valid, "
                     "Snoop and Forwarding strengths cannot be both set to non-zero values.");
    }
    else if (BCM_GPORT_IS_TRAP(mtu_data_p->trap_gport) &&
             (BCM_GPORT_TRAP_GET_ID(mtu_data_p->trap_gport) >= BCM_RX_TRAP_EG_TX_TRAP_ID_DEFAULT)
             && ((BCM_GPORT_TRAP_GET_STRENGTH(mtu_data_p->trap_gport) == 0)
                 && (BCM_GPORT_TRAP_GET_SNOOP_STRENGTH(mtu_data_p->trap_gport) == 0)))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The Trap-Gport is not valid, "
                     "Snoop and Forwarding strengths cannot be both set to zero.");
    }

    if (BCM_GPORT_IS_TRAP(mtu_data_p->trap_gport) &&
        (BCM_GPORT_TRAP_GET_ID(mtu_data_p->trap_gport) != BCM_RX_TRAP_EG_TX_TRAP_ID_DEFAULT) &&
        (BCM_GPORT_TRAP_GET_ID(mtu_data_p->trap_gport) != BCM_RX_TRAP_EG_TX_TRAP_ID_DROP))
    {
        trap_id = BCM_GPORT_TRAP_GET_ID(mtu_data_p->trap_gport);
        fwd_action_index = DNX_RX_TRAP_EGRESS_ACTION_PROFILE_GET(trap_id);
        if (fwd_action_index >= dnx_data_trap.etpp.nof_etpp_trap_profiles_get(unit))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "The Trap_ID is out of range! \n");
        }

        if (BCM_GPORT_TRAP_GET_STRENGTH(mtu_data_p->trap_gport) > 0)
        {
            SHR_IF_ERR_EXIT(dnx_algo_rx_trap_id_etpp_is_allocated(unit, fwd_action_index, &is_allocated));

            if (is_allocated == FALSE)
            {
                SHR_ERR_EXIT(_SHR_E_NOT_FOUND,
                             "The Trap_ID is not allocated, please us bcm_rx_trap_type_create() first ! \n");
            }
        }
        else if (BCM_GPORT_TRAP_GET_SNOOP_STRENGTH(mtu_data_p->trap_gport) > 0)
        {
            BCM_GPORT_MIRROR_SNOOP_SET(snoop_gport, fwd_action_index);
            SHR_IF_ERR_EXIT(dnx_mirror_profile_is_allocated(unit, snoop_gport, &is_allocated));

            if (is_allocated == FALSE)
            {
                SHR_ERR_EXIT(_SHR_E_NOT_FOUND, "The Snoop profile (%d) encoded in trap_gport is not allocated! "
                             "Use bcm_mirror_destination_create() to allocate a snoop action profile. \n",
                             fwd_action_index);
            }
        }
    }

    if (flags != BCM_RX_MTU_PORT)
    {
        if (dnx_data_trap.etpp.feature_get(unit, dnx_data_trap_etpp_mtu_layer_to_compressed_layer_mapping_support))
        {
            max_cmp_layer_type = DNX_RX_MTU_PORT_COMPRESSED_LAYER_TYPE - 1;
        }
        else
        {
            max_cmp_layer_type = bcmRxTrapMtuLayerTypeCount - 1;
        }

        if (mtu_key_p->cmp_layer_type > max_cmp_layer_type)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "Invalid compressed forward layer type, %d is too big for LIF/RIF! Maximum value is %d",
                         mtu_key_p->cmp_layer_type, max_cmp_layer_type);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 *  See rx.h for info
 */
shr_error_e
bcm_dnx_rx_mtu_profile_set(
    int unit,
    uint32 flags,
    bcm_rx_mtu_profile_key_t * mtu_key_p,
    bcm_rx_mtu_profile_value_t * mtu_data_p)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    if (flags == BCM_RX_MTU_PORT)
    {
        mtu_key_p->cmp_layer_type = DNX_RX_MTU_PORT_COMPRESSED_LAYER_TYPE;
    }

    SHR_IF_ERR_EXIT(dnx_rx_trap_mtu_profile_set_verify(unit, flags, mtu_key_p, mtu_data_p));

    if (mtu_data_p->trap_gport == BCM_GPORT_INVALID)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_mtu_profile_hw_clear(unit, mtu_key_p));
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(dnx_rx_trap_mtu_profile_hw_set(unit, mtu_key_p, mtu_data_p));

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Verify function for mtu_profile_get.
* \par DIRECT INPUT:
*   \param [in] unit                    - unit id
*   \param [in] flags                   - Flags(BCM_RX_MTU_XXX)
*   \param [in] mtu_key_p               - MTU Map table key
*   \param [out] mtu_data_p             - MTU Profile config
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_mtu_profile_get_verify(
    int unit,
    uint32 flags,
    bcm_rx_mtu_profile_key_t * mtu_key_p,
    bcm_rx_mtu_profile_value_t * mtu_data_p)
{

    SHR_FUNC_INIT_VARS(unit);

    if (flags != BCM_RX_MTU_PORT && flags != BCM_RX_MTU_LIF && flags != BCM_RX_MTU_RIF)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported/Invalid flags have been set, %d flags are invalid", flags);
    }

    if (mtu_key_p->mtu_profile >= dnx_data_trap.etpp.nof_mtu_profiles_get(unit))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The MTU profile(%d) supplied is bigger than the max number of profiles(%d)",
                     mtu_key_p->mtu_profile, (dnx_data_trap.etpp.nof_mtu_profiles_get(unit) - 1));
    }

    if (mtu_key_p->cmp_layer_type >= DNX_RX_MTU_PORT_COMPRESSED_LAYER_TYPE && (flags != BCM_RX_MTU_PORT))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "Invalid compressed forward layer type, %d is too big for LIF/RIF! Maximum value is %d",
                     mtu_key_p->cmp_layer_type, (DNX_RX_MTU_PORT_COMPRESSED_LAYER_TYPE - 1));
    }

    if ((dnx_data_trap.etpp.feature_get(unit, dnx_data_trap_etpp_mtu_layer_to_compressed_layer_mapping_support) == 0) &&
        mtu_key_p->cmp_layer_type >= bcmRxTrapMtuLayerTypeCount)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "Invalid compressed layer type, %d is too big for LIF/RIF! Maximum value is %d",
                     mtu_key_p->cmp_layer_type, (bcmRxTrapMtuLayerTypeCount - 1));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 *  See rx.h for info
 */
shr_error_e
bcm_dnx_rx_mtu_profile_get(
    int unit,
    uint32 flags,
    bcm_rx_mtu_profile_key_t * mtu_key_p,
    bcm_rx_mtu_profile_value_t * mtu_data_p)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    if (flags == BCM_RX_MTU_PORT)
    {
        mtu_key_p->cmp_layer_type = DNX_RX_MTU_PORT_COMPRESSED_LAYER_TYPE;
    }

    SHR_IF_ERR_EXIT(dnx_rx_trap_mtu_profile_get_verify(unit, flags, mtu_key_p, mtu_data_p));

    SHR_IF_ERR_EXIT(dnx_rx_trap_mtu_profile_hw_get(unit, mtu_key_p, mtu_data_p));

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set etpp trap action profile in HW: trap stregnths and profile number.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_id   -  etpp trap id (SW id) to configure
*   \param [in] action_profile_p  -  Hold the action-profile configuration to set for specific trap
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_etpp_action_profile_set(
    int unit,
    int trap_id,
    dnx_rx_trap_action_profile_t * action_profile_p)
{
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_trap.egress.feature_get(unit, dnx_data_trap_egress_egress_divided_to_erpp_and_etpp))
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_v1_etpp_action_profile_hw_set(unit, trap_id, action_profile_p));
    }
    else
    {
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get etpp trap action profile: trap stregnths and profile number.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_id   -  etpp trap id (SW id) to configure
*   \param [in] action_profile_p  -  Hold the action-profile configuration to set for specific trap
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_etpp_action_profile_get(
    int unit,
    int trap_id,
    dnx_rx_trap_action_profile_t * action_profile_p)
{
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_trap.egress.feature_get(unit, dnx_data_trap_egress_egress_divided_to_erpp_and_etpp))
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_v1_etpp_action_profile_hw_get(unit, trap_id, action_profile_p));
    }
    else
    {
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set the etpp trap action profile: trap stregnth and action.
*  Allocates profile using template manager.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_class  -  trap class to configure
*   \param [in] trap_type   -  etpp trap type (SW id) to configure
*   \param [in] config_p  -  Hold the etpp trap action profile configuration to set for specific trap
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_etpp_set(
    int unit,
    dnx_rx_trap_class_e trap_class,
    int trap_type,
    bcm_rx_trap_config_t * config_p)
{
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_trap.egress.feature_get(unit, dnx_data_trap_egress_egress_divided_to_erpp_and_etpp))
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_v1_etpp_set(unit, trap_class, trap_type, config_p));
    }
    else
    {
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set the trap action profile, forward strength and snoop
*  strength.
* \par DIRECT INPUT:
*   \param [in] unit     -  Unit id
*   \param [in] trap_id  -  trap id to configure
*   \param [in] config_p   -  trap action profile configuration
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
bcm_dnx_rx_trap_set(
    int unit,
    int trap_id,
    bcm_rx_trap_config_t * config_p)
{
    dnx_rx_trap_block_e trap_block = DNX_RX_TRAP_BLOCK_INVALID;
    dnx_rx_trap_class_e trap_class = DNX_RX_TRAP_CLASS_INVALID;
    int trap_type = DNX_RX_TRAP_ID_INVALID;
    dnx_rx_trap_erpp_config_t erpp_config;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    SHR_NULL_CHECK(config_p, _SHR_E_PARAM, "config_p");

    dnx_rx_trap_erpp_config_t_init(unit, &erpp_config);

    SHR_INVOKE_VERIFY_DNXC(dnx_rx_trap_set_verify(unit, trap_id, config_p));

    trap_block = DNX_RX_TRAP_ID_BLOCK_GET(trap_id);
    trap_class = DNX_RX_TRAP_ID_CLASS_GET(unit, trap_id);
    trap_type = DNX_RX_TRAP_ID_TYPE_GET(trap_id);

    switch (trap_block)
    {
        case DNX_RX_TRAP_BLOCK_INGRESS:
            SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_set(unit, trap_type, config_p));
            break;
        case DNX_RX_TRAP_BLOCK_ERPP:
            SHR_IF_ERR_EXIT(dnx_rx_trap_erpp_config_from_config_fill(unit, config_p, &erpp_config));
            SHR_IF_ERR_EXIT(dnx_rx_trap_erpp_action_hw_set(unit, trap_type, &erpp_config));
            break;
        case DNX_RX_TRAP_BLOCK_ETPP:
            SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_set(unit, trap_class, trap_type, config_p));
            break;
        case DNX_RX_TRAP_BLOCK_OAMP:
            SHR_IF_ERR_EXIT(dnx_oam_error_trap_set(unit, trap_type, config_p));
            SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_set(unit, trap_type, config_p));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Illegal trap_block=%d\n", trap_block);
            break;
    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Verify the parameters of bcm_rx_trap_get API
* \par DIRECT INPUT:
*   \param [in] unit     -  Unit Id
*   \param [in] trap_id  -  trap id to set
*   \param [in] config_p   -  configuration for given trap to check
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_get_verify(
    int unit,
    int trap_id,
    bcm_rx_trap_config_t * config_p)
{
    uint8 is_allocated;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Check NULL param
     */
    SHR_NULL_CHECK(config_p, _SHR_E_PARAM, "config");

    /*
     * Check if trap id was allocated
     */
    SHR_IF_ERR_EXIT(dnx_rx_trap_is_trap_id_allocated(unit, trap_id, &is_allocated));
    if (is_allocated == FALSE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "trap_id=%d was not created, call bcm_rx_trap_type_create() first \n", trap_id);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get ingress trap stregnths.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_type  -  ingress trap type (HW trap id value) to configure
*   \param [in] config_p  -  Hold the action-profile configuration to set for specific trap
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_strength_get(
    int unit,
    int trap_type,
    bcm_rx_trap_config_t * config_p)
{
    int is_strengthless = TRUE;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_strengthless_trap_check(unit, trap_type, &is_strengthless));

    if (!is_strengthless)
    {
        /** Same interface trap have dedicated memory which needs to be handled differently than other ingress traps*/
        switch (trap_type)
        {
            case DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FER_SAME_INTERFACE:
                SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_same_interface_strength_hw_get(unit,
                                                                                   DBAL_ENUM_FVAL_FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_DEFAULT,
                                                                                   config_p));
                break;
            case DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FER_ICMP_REDIRECT:
                SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_same_interface_strength_hw_get(unit,
                                                                                   DBAL_ENUM_FVAL_FER_TRAP_SAME_INTERFACE_FILTER_PROFILE_IP,
                                                                                   config_p));
                break;
            case DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_BFD_O_IPV6_UDP_CHECKSUM:
                SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_bfd_ipv6_udp_strength_hw_get(unit, config_p));
                break;
            default:
                SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_strength_hw_get(unit, trap_type, config_p));
                break;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get ingress trap flags.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_type  -  Ingress trap type (HW trap id value)
*   \param [in] config_p  -  Hold the action-profile configuration to set for specific trap
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_flags_get(
    int unit,
    int trap_type,
    bcm_rx_trap_config_t * config_p)
{
    uint32 acl_trap_profile;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_field_context_acl_cpu_trap_code_profile_get(unit, trap_type, &acl_trap_profile));
    if (acl_trap_profile != 0)
    {
        config_p->flags2 |= BCM_RX_TRAP_FLAGS2_UPDATE_ACL_PROFILE;
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get the trap action profile: trap stregnth and action for ingress traps.
* \par DIRECT INPUT:
*   \param [in] unit     -  Unit id
*   \param [in] trap_type  -  ingress trap type (HW trap id value) of trap
*   \param [in] config_p   -  Pointer type of bcm_rx_trap_config_t \n
*               \b As \b output - \n
*               Pointer will be filled by action profile configuration
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_get(
    int unit,
    int trap_type,
    bcm_rx_trap_config_t * config_p)
{
    SHR_FUNC_INIT_VARS(unit);

    /** Get forward and snoop strengths */
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_strength_get(unit, trap_type, config_p));

    /** Get the action entry information of trap */
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_fwd_action_entry_hw_get(unit, trap_type, config_p));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_snp_action_entry_hw_get(unit, trap_type, &config_p->snoop_cmnd));

    /** Get trap flags. */
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_flags_get(unit, trap_type, config_p));

exit:
    SHR_FUNC_EXIT;

}

/**
* \brief
* This function receives the HW profile index and retrieves
* the destination configured.
* \param [in] unit -The unit number.
* \param [in] profile - Holds the HW profile index.
* \param [out] erpp_config_p - The ERPP forward action profile which holds the trap actions.
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * DBAL_TABLE_ERPP_TRAP_FORWARD_ACTION_PROFILE_TABLE
*/
static shr_error_e
dnx_rx_trap_erpp_destination_get(
    int unit,
    int profile,
    dnx_rx_trap_erpp_config_t * erpp_config_p)
{
    bcm_core_t core_id;
    uint8 pp_dsp_valid, discard;
    uint32 entry_handle_id, pp_dsp;
    bcm_gport_t dest_port;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    BCM_GPORT_TRAP_SET(dest_port, 0, 0, 0);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ERPP_TRAP_FORWARD_ACTION_PROFILE_TABLE, &entry_handle_id));

    DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core_id)
    {
        /** Keys */
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_ACTION_PROFILE, (uint32) profile);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);

        dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_DISCARD, INST_SINGLE, &discard);
        dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_DSP_VALID, INST_SINGLE, &pp_dsp_valid);
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_DSP, INST_SINGLE, &pp_dsp);
        SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

        if (discard)
        {
            erpp_config_p->update_dest = TRUE;
            dest_port = BCM_GPORT_BLACK_HOLE;
        }
        else if (pp_dsp_valid)
        {
            erpp_config_p->update_dest = TRUE;
            SHR_IF_ERR_EXIT(dnx_algo_port_pp_dsp_to_logical_get(unit, core_id, pp_dsp, &dest_port));
        }

        if ((erpp_config_p->core_config_arr != NULL) && (core_id < erpp_config_p->core_config_arr_len))
        {
            /** In case of per core configuration */
            erpp_config_p->core_config_arr[core_id].dest_port = dest_port;
        }
        else
        {
            /** In case of single core configuration */
            erpp_config_p->dest_port = dest_port;
        }
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
* This function receives the HW profile index and retrieves
* from the HW the profile's actions.
* \param [in] unit -The unit number.
* \param [in] profile - Holds the HW profile index.
* \param [out] erpp_config_p - The ERPP forward action profile which holds the trap actions.
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * DBAL_TABLE_ERPP_TRAP_FORWARD_ACTION_PROFILE_TABLE
*/
static shr_error_e
dnx_rx_trap_erpp_action_hw_get(
    int unit,
    int profile,
    dnx_rx_trap_erpp_config_t * erpp_config_p)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ERPP_TRAP_FORWARD_ACTION_PROFILE_TABLE, &entry_handle_id));

    /** Keys */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_ACTION_PROFILE, (uint32) profile);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, DBAL_CORE_DEFAULT);

    /** Values */
    /** Get DP value */
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_DP_VALID, INST_SINGLE, &(erpp_config_p->dp_valid));
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_DP, INST_SINGLE, &(erpp_config_p->dp));

    /** Get TC value */
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_TC_VALID, INST_SINGLE, &(erpp_config_p->tc_valid));
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_TC, INST_SINGLE, &(erpp_config_p->tc));

    /** Get QOS ID value */
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_COS_PROFILE_VALID, INST_SINGLE,
                              &(erpp_config_p->qos_id_valid));
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_COS_PROFILE, INST_SINGLE, &(erpp_config_p->qos_id));

    /** Get PP drop reason */
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_PP_DROP_REASON_VALID, INST_SINGLE,
                              &(erpp_config_p->pp_drop_reason_valid));
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_PP_DROP_REASON, INST_SINGLE,
                               (uint32 *) &(erpp_config_p->pp_drop_reason));

    /** Get Snoop Profile */
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_SNOOP_PROFILE_VALID, INST_SINGLE,
                              &(erpp_config_p->snoop_profile_valid));
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_SNOOP_PROFILE, INST_SINGLE,
                              &(erpp_config_p->snoop_profile));

    /** Get Mirror Profile */
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_MIRROR_PROFILE_VALID, INST_SINGLE,
                              &(erpp_config_p->mirror_profile_valid));
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_MIRROR_PROFILE, INST_SINGLE,
                              &(erpp_config_p->mirror_profile));

    /** Get CUD */
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_CUD_VALID, INST_SINGLE,
                              &(erpp_config_p->outlif_or_mcdb_ptr_valid));
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_CUD, INST_SINGLE,
                               &(erpp_config_p->outlif_or_mcdb_ptr));

    /** Get Counter 0 Profile */
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_PMF_COUNTER_0_PROFILE_VALID, INST_SINGLE,
                              &(erpp_config_p->counter_profile_valid[0]));
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_PMF_COUNTER_0_PROFILE, INST_SINGLE,
                              &(erpp_config_p->counter_profile[0]));

     /** Get Counter 0 Pointer */
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_PMF_COUNTER_0_PTR_VALID, INST_SINGLE,
                              &(erpp_config_p->counter_ptr_valid[0]));
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_PMF_COUNTER_0_PTR, INST_SINGLE,
                               &(erpp_config_p->counter_ptr[0]));

    /** Get Counter 1 Profile */
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_PMF_COUNTER_1_PROFILE_VALID, INST_SINGLE,
                              &(erpp_config_p->counter_profile_valid[1]));
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_PMF_COUNTER_1_PROFILE, INST_SINGLE,
                              &(erpp_config_p->counter_profile[1]));

     /** Get Counter 1 Pointer */
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_PMF_COUNTER_1_PTR_VALID, INST_SINGLE,
                              &(erpp_config_p->counter_ptr_valid[1]));
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_PMF_COUNTER_1_PTR, INST_SINGLE,
                               &(erpp_config_p->counter_ptr[1]));

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

    SHR_IF_ERR_EXIT(dnx_rx_trap_erpp_destination_get(unit, profile, erpp_config_p));
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *  Fill bcm_rx_trap_config_t from ERPP trap configuration struct.
 * \param [in] unit -The unit number.
 * \param [in] erpp_config_p -The erpp forwarding action profile. holds trap actions,
 *   forward strength and forward snoop.
 * \param [out] config_p - Holds trap configuration.
 *   strength and snoop strength.
 * \par INDIRECT INPUT:
 *   * None
 * \par DIRECT OUTPUT:
 *   shr_error_e -  Error Type
 * \par INDIRECT OUTPUT:
 *   * None
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_rx_trap_config_from_erpp_config_fill(
    int unit,
    dnx_rx_trap_erpp_config_t * erpp_config_p,
    bcm_rx_trap_config_t * config_p)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(erpp_config_p, _SHR_E_PARAM, "erpp_config_p");

    bcm_rx_trap_config_t_init(config_p);

    if (erpp_config_p->tc_valid == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_PRIO;
        config_p->prio = erpp_config_p->tc;
    }

    if (erpp_config_p->dp_valid == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_COLOR;
        config_p->color = erpp_config_p->dp;
    }

    if (erpp_config_p->qos_id_valid == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_QOS_MAP_ID;
        config_p->qos_map_id = erpp_config_p->qos_id;
    }

    if (erpp_config_p->update_dest == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_DEST;
        config_p->dest_port = erpp_config_p->dest_port;
        config_p->core_config_arr = erpp_config_p->core_config_arr;
    }

    /** Will return HW value as we have no way of indication if we have written LIF or ACE pointer */
    if (erpp_config_p->outlif_or_mcdb_ptr_valid == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_ENCAP_ID;
        config_p->encap_id = erpp_config_p->outlif_or_mcdb_ptr;
    }

    if (erpp_config_p->pp_drop_reason_valid == TRUE)
    {
        config_p->pp_drop_reason = erpp_config_p->pp_drop_reason;
    }

    if (erpp_config_p->counter_profile_valid[0] == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_COUNTER;
        config_p->stat_obj_config_arr[0].stat_profile = erpp_config_p->counter_profile[0];
    }

    if (erpp_config_p->counter_ptr_valid[0] == TRUE)
    {
        config_p->stat_obj_config_arr[0].stat_id = erpp_config_p->counter_ptr[0];
    }

    if (erpp_config_p->counter_profile_valid[1] == TRUE)
    {
        config_p->flags |= BCM_RX_TRAP_UPDATE_COUNTER_2;
        config_p->stat_obj_config_arr[1].stat_profile = erpp_config_p->counter_profile[1];
    }

    if (erpp_config_p->counter_ptr_valid[1] == TRUE)
    {
        config_p->stat_obj_config_arr[1].stat_id = erpp_config_p->counter_ptr[1];
    }

    if (erpp_config_p->mirror_profile_valid == TRUE)
    {
        config_p->mirror_profile = erpp_config_p->mirror_profile;
    }

    if (erpp_config_p->snoop_profile_valid == TRUE)
    {
        config_p->snoop_cmnd = erpp_config_p->snoop_profile;
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get the etpp trap action profile: trap stregnth and action.
*  Allocates profile using template manager.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] trap_class  -  trap class (first or OAM) to configure
*   \param [in] trap_type   -  etpp trap type (SW id) to configure
*   \param [out] config_p  -  Hold the etpp trap action profile configuration to set for specific trap
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
dnx_rx_trap_etpp_get(
    int unit,
    dnx_rx_trap_class_e trap_class,
    int trap_type,
    bcm_rx_trap_config_t * config_p)
{
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_trap.egress.feature_get(unit, dnx_data_trap_egress_egress_divided_to_erpp_and_etpp))
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_v1_etpp_get(unit, trap_class, trap_type, config_p));
    }
    else
    {
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get the trap action profile: trap stregnth and action.
* \par DIRECT INPUT:
*   \param [in] unit     -  Unit id
*   \param [in] trap_id  -  trap id to get its info, action profile
*   \param [in] config_p   -  Pointer type of bcm_rx_trap_config_t \n
*               \b As \b output - \n
*               Pointer will be filled by action profile configuration
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
bcm_dnx_rx_trap_get(
    int unit,
    int trap_id,
    bcm_rx_trap_config_t * config_p)
{
    dnx_rx_trap_block_e trap_block = DNX_RX_TRAP_BLOCK_INVALID;
    dnx_rx_trap_class_e trap_class = DNX_RX_TRAP_CLASS_INVALID;
    int trap_type = DNX_RX_TRAP_ID_INVALID, core_config_arr_len = 0;
    dnx_rx_trap_erpp_config_t erpp_config;
    bcm_rx_trap_core_config_t *core_config_arr = NULL;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);
    SHR_INVOKE_VERIFY_DNXC(dnx_rx_trap_get_verify(unit, trap_id, config_p));

    /** initialize output structure */
    dnx_rx_trap_erpp_config_t_init(unit, &erpp_config);
    /** to retrieve per core configuration, user should supply core_config_arr*/
    core_config_arr = config_p->core_config_arr;
    core_config_arr_len = config_p->core_config_arr_len;
    bcm_rx_trap_config_t_init(config_p);

    if ((core_config_arr != NULL) && (core_config_arr_len > 0))
    {
        config_p->core_config_arr = core_config_arr;
        config_p->core_config_arr_len = core_config_arr_len;
    }

    trap_block = DNX_RX_TRAP_ID_BLOCK_GET(trap_id);
    trap_class = DNX_RX_TRAP_ID_CLASS_GET(unit, trap_id);
    trap_type = DNX_RX_TRAP_ID_TYPE_GET(trap_id);

    switch (trap_block)
    {
        case DNX_RX_TRAP_BLOCK_INGRESS:
            SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_get(unit, trap_type, config_p));
            break;
        case DNX_RX_TRAP_BLOCK_ERPP:
            erpp_config.core_config_arr = core_config_arr;
            erpp_config.core_config_arr_len = core_config_arr_len;
            SHR_IF_ERR_EXIT(dnx_rx_trap_erpp_action_hw_get(unit, trap_type, &erpp_config));
            SHR_IF_ERR_EXIT(dnx_rx_trap_config_from_erpp_config_fill(unit, &erpp_config, config_p));
            break;
        case DNX_RX_TRAP_BLOCK_ETPP:
            SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_get(unit, trap_class, trap_type, config_p));
            break;
        case DNX_RX_TRAP_BLOCK_OAMP:
            SHR_IF_ERR_EXIT(dnx_oam_error_trap_get(unit, trap_type, config_p));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Illegal trap_block=%d\n", trap_block);
            break;
    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Verify the tra_id is in legal ranges for Trap_ID
* \par DIRECT INPUT:
*   \param [in]  unit     -  Unit Id
*   \param [in]  trap_id  -  trap id to check
*   \param [out] is_legal -  Return param weather the trap_id is legal or not
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_id_is_legal(
    int unit,
    int trap_id,
    uint8 *is_legal)
{
    int trap_block = 0;
    int trap_type = 0;
    dnx_rx_trap_map_type_t trap_type_info;
    dnx_rx_trap_map_ranges_t trap_id_range_info;
    bcm_rx_trap_t oam_and_ifa_etpp_traps[DNX_RX_TRAP_ETPP_OAM_NOF_TRAPS] =
        { bcmRxTrapEgTxOamUpMEPOamp, bcmRxTrapEgTxOamUpMEPDest1, bcmRxTrapEgTxOamUpMEPDest2,
        bcmRxTrapEgTxOamLevel, bcmRxTrapEgTxOamPassive, bcmRxTrapEgTxOamReflector, bcmRxTrapEgTxIfaEgressMetadata,
        bcmRxTrapEgTxOamUpMEPOampPerformenceResponsePriority, bcmRxTrapEgTxOamUpMEPOampPerformenceResponse
    };
    SHR_FUNC_INIT_VARS(unit);
    *is_legal = FALSE;
    sal_memset(&trap_type_info, 0, sizeof(dnx_rx_trap_map_type_t));
    sal_memset(&trap_id_range_info, 0, sizeof(dnx_rx_trap_map_ranges_t));

    for (trap_type = 0; trap_type < DNX_RX_TRAP_ETPP_OAM_NOF_TRAPS; trap_type++)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_type_map_info_get_dispatch
                        (unit, oam_and_ifa_etpp_traps[trap_type], &trap_type_info));
        if (trap_type_info.valid
            && (trap_id == DNX_RX_TRAP_ID_SET(DNX_RX_TRAP_BLOCK_ETPP, DNX_RX_TRAP_CLASS_OAM, trap_type_info.trap_id)))
        {
            *is_legal = TRUE;
        }
    }
    /**
     * Trap_id can be ingress, OAMP, ERPP or ETPP, so this checks if the trap_id is in a range between them, which is illegal.
     */
    for (trap_block = DNX_RX_TRAP_BLOCK_FIRST; trap_block < DNX_RX_TRAP_BLOCK_NUM_OF; trap_block++)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_id_boundry_ranges_map_info_get_dispatch(unit, trap_block, &trap_id_range_info));
        if (trap_id >= trap_id_range_info.lower_bound_trap_id && trap_id <= trap_id_range_info.upper_bound_trap_id)
        {
            *is_legal = TRUE;
        }
    }
exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Verify the parameters of bcm_rx_trap_type_destroy
* \par DIRECT INPUT:
*   \param [in] unit     -  Unit Id
*   \param [in] trap_id  -  trap id to destroy
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_type_destroy_verify(
    int unit,
    int trap_id)
{
    uint8 is_allocated;
    uint8 is_legal = FALSE;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_id_is_legal(unit, trap_id, &is_legal));

    if (is_legal == FALSE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal trap_id(%d) value! \n", trap_id);
    }

    /*
     * Check if trap id was allocated
     */
    SHR_IF_ERR_EXIT(dnx_rx_trap_is_trap_id_allocated(unit, trap_id, &is_allocated));
    if (is_allocated == FALSE)
    {
        SHR_ERR_EXIT(_SHR_E_NOT_FOUND, "trap_id was not created, call bcm_rx_trap_type_create() first \n");
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Destroy previously created ingress trap, i.e. deallocate from relevant trap pool
* \par DIRECT INPUT:
*   \param [in] unit     -  Unit id
*   \param [in] trap_type  -  ingress trap type (HW trap id value) of trap to destroy
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_destroy(
    int unit,
    int trap_type)
{
    dnx_rx_trap_class_e trap_class = DNX_RX_TRAP_CLASS_INVALID;
    int sw_trap_id;
    SHR_FUNC_INIT_VARS(unit);

    trap_class = DNX_RX_TRAP_ID_CLASS_GET(unit, trap_type);

    switch (trap_class)
    {
        case DNX_RX_TRAP_CLASS_PREDEFINED:
        case DNX_RX_TRAP_CLASS_OAM:
            SHR_IF_ERR_EXIT(dnx_algo_rx_trap_id_ingress_predefined_deallocate(unit, trap_type));
            break;
        case DNX_RX_TRAP_CLASS_USER_DEFINED:
            /** Get the correct id in the user defined pool*/
            SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_ud_hw_to_sw(unit, trap_type, &sw_trap_id));
            SHR_IF_ERR_EXIT(dnx_algo_rx_trap_id_ingress_user_define_deallocate(unit, sw_trap_id));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Illegal trap_class=%d\n", trap_class);
            break;
    }

    /** Remove the action-profile of the trap (action and strength)*/
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_clear(unit, trap_type));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  The function checks the reference count of trap types using the same profile(trap_id).
*  Counts how many Trap types are connected to the same profile, we don't want to delete profile,
*  which has multiple trap_types connected to it.
* \par DIRECT INPUT:
*   \param [in] unit        -  Unit id
*   \param [in] profile     -  Trap ID(profile).
*   \param [out] ref_count  -  Reference count of profiles.
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_erpp_profile_ref_count_get(
    int unit,
    int profile,
    int *ref_count)
{
    dnx_rx_trap_action_profile_t action_profile;
    int trap_id;
    uint32 hw_field_val;
    int skip_invalid_value;

    SHR_FUNC_INIT_VARS(unit);

    *ref_count = 0;

    for (trap_id = DBAL_ENUM_FVAL_ERPP_TRAP_ID_RQP_DISCARD; trap_id < DBAL_NOF_ENUM_ERPP_TRAP_ID_VALUES; trap_id++)
    {
        skip_invalid_value =
            dbal_field_types_encode_enum(unit, DBAL_FIELD_TYPE_DEF_ERPP_TRAP_ID, trap_id, &hw_field_val);
        if (skip_invalid_value != _SHR_E_UNAVAIL)
        {
            SHR_IF_ERR_EXIT(dnx_rx_trap_erpp_action_profile_hw_get(unit, trap_id, &action_profile));
            if (action_profile.profile == profile)
            {
                (*ref_count)++;
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Destroy previously created ERPP trap, i.e. deallocate from relevant trap pool
* \par DIRECT INPUT:
*   \param [in] unit     -  Unit id
*   \param [in] profile  -  ERPP profile of trap to destroy
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_erpp_destroy(
    int unit,
    int profile)
{
    int ref_count;
    SHR_FUNC_INIT_VARS(unit);

    /** Check if no traps are associated with the provided ERPP profile */
    SHR_IF_ERR_EXIT(dnx_rx_trap_erpp_profile_ref_count_get(unit, profile, &ref_count));
    if (ref_count != 0)
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "There are multiple trap types set to the same Trap ID."
                     "Clear the trap types before deleting the Trap ID \n");
    }
    /** Deallocate trap type*/
    SHR_IF_ERR_EXIT(dnx_algo_rx_trap_id_erpp_deallocate(unit, profile));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Destroy previously created ETPP trap, i.e. deallocate from relevant trap pool
* \par DIRECT INPUT:
*   \param [in] unit        -  Unit id
*   \param [in] trap_class  -  trap class (predefined or OAM) of trap to destroy
*   \param [in] trap_type     -  ETPP trap type to destroy
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
dnx_rx_trap_etpp_destroy(
    int unit,
    dnx_rx_trap_class_e trap_class,
    int trap_type)
{
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_trap.egress.feature_get(unit, dnx_data_trap_egress_egress_divided_to_erpp_and_etpp))
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_v1_etpp_destroy(unit, trap_class, trap_type));
    }
    else
    {
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Destroy previously created trap, i.e. deallocate from relevant trap pool
* \par DIRECT INPUT:
*   \param [in] unit     -  Unit Id
*   \param [in] trap_id  -  trap id to destroy
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
bcm_dnx_rx_trap_type_destroy(
    int unit,
    int trap_id)
{
    dnx_rx_trap_block_e trap_block = DNX_RX_TRAP_BLOCK_INVALID;
    dnx_rx_trap_class_e trap_class = DNX_RX_TRAP_CLASS_INVALID;
    int trap_type = DNX_RX_TRAP_ID_INVALID;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_rx_trap_type_destroy_verify(unit, trap_id));

    trap_block = DNX_RX_TRAP_ID_BLOCK_GET(trap_id);
    trap_class = DNX_RX_TRAP_ID_CLASS_GET(unit, trap_id);
    trap_type = DNX_RX_TRAP_ID_TYPE_GET(trap_id);

    switch (trap_block)
    {
        case DNX_RX_TRAP_BLOCK_INGRESS:
            SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_destroy(unit, trap_type));
            break;
        case DNX_RX_TRAP_BLOCK_ERPP:
            SHR_IF_ERR_EXIT(dnx_rx_trap_erpp_destroy(unit, trap_type));
            break;
        case DNX_RX_TRAP_BLOCK_ETPP:
            SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_destroy(unit, trap_class, trap_type));
            break;
        case DNX_RX_TRAP_BLOCK_OAMP:
            SHR_IF_ERR_EXIT(dnx_oam_error_trap_destroy(unit, trap_type));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Illegal trap_block=%d\n", trap_block);
            break;
    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set mirror action profile for etpp trap (stack or latency traps).
* \par DIRECT INPUT:
*   \param [in] unit            - unit Id
*   \param [in] dbal_table    - DBAL table to configue
*   \param [in] mirror_action_profile    - mirror action profile to confiure
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_etpp_mirror_action_profile_hw_set(
    int unit,
    dbal_tables_e dbal_table,
    uint8 mirror_action_profile)
{

    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, dbal_table, &entry_handle_id));

    /** Values */
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_MRR_ACTION_PROFILE, INST_SINGLE,
                                mirror_action_profile);

    if (dbal_table == DBAL_TABLE_ETPP_LATENCY_TRAP_MIRROR_ACTION_PROFILE)
    {
        dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_MRR_ACTION_PROFILE_ENABLE, INST_SINGLE, TRUE);
    }

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;

}

/**
* \brief
*  Get mirror action profile of etpp trap (stack or latency traps).
* \par DIRECT INPUT:
*   \param [in] unit            - unit Id
*   \param [in] dbal_table   - DBAL table
*   \param [out] mirror_action_profile_p    - mirror action profile confiured
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_etpp_mirror_action_profile_hw_get(
    int unit,
    dbal_tables_e dbal_table,
    uint8 *mirror_action_profile_p)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, dbal_table, &entry_handle_id));

    /** Values */
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_MRR_ACTION_PROFILE, INST_SINGLE,
                              mirror_action_profile_p);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Verify the parameters of dnx_rx_trap_action_profile_set API
* \par DIRECT INPUT:
*   \param [in] unit            - unit Id
*   \param [in] flags            - flags (for future use)
*   \param [in] trap_type       - BCM Trap type
*   \param [in] gport   - Gport encoded as trap or mirror
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_action_profile_set_verify(
    int unit,
    uint32 flags,
    bcm_rx_trap_t trap_type,
    bcm_gport_t gport)
{
    dnx_rx_trap_action_profile_t action_profile = { 0 };
    uint8 mirror_action_profile = 0, is_allocated = TRUE;
    uint8 unknown_da_enabled = FALSE;
    uint8 glem_not_found_enabled = FALSE;
    int system_headers_mode, trap_id, snoop_strength, fwd_strength;
    int fwd_action_profile_default, fwd_action_profile_mask = 0xFF0;
    dnx_rx_trap_map_type_t appl_trap_info;
    SHR_FUNC_INIT_VARS(unit);
    sal_memset(&appl_trap_info, 0, sizeof(dnx_rx_trap_map_type_t));

    SHR_IF_ERR_EXIT(dnx_rx_trap_appl_trap_map_info_get_dispatch(unit, trap_type, &appl_trap_info));

    if (appl_trap_info.valid == FALSE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Trap type = %d , not supported \n", trap_type);
    }

    unknown_da_enabled = dnx_data_trap.erpp.feature_get(unit, dnx_data_trap_erpp_unknown_da_trap_en);
    glem_not_found_enabled = dnx_data_trap.erpp.feature_get(unit, dnx_data_trap_erpp_glem_not_found_trap);
    system_headers_mode = dnx_data_headers.system_headers.system_headers_mode_get(unit);
    if (trap_type == bcmRxTrapEgUnknownDa)
    {
        if (unknown_da_enabled == FALSE)
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcmRxTrapEgUnknownDa is not supported on this device.\n");
        }
        else if (system_headers_mode == DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO2_MODE)
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                         "bcmRxTrapEgUnknownDa is not supported on this device in Jr2 System Headers mode.\n");
        }
    }

    if ((glem_not_found_enabled == FALSE) &&
        ((trap_type == bcmRxTrapEgGlemPpTrap) || (trap_type == bcmRxTrapEgGlemNonePpTrap)))
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                     "bcmRxTrapEgGlemPpTrap and bcmRxTrapEgGlemNonePpTrap are not supported on this device.\n");
    }

    /** In case of mirror, check for relevant traps and check that trap_action_profile is not configured */
    if (BCM_GPORT_IS_MIRROR_MIRROR(gport))
    {
        if (trap_type != bcmRxTrapEgTxLatency)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "A Mirror-Action-Profile can only be configured for Latencey trap\n");
        }
        else if (!dnx_data_trap.etpp.feature_get(unit, dnx_data_trap_etpp_latency_trap_mirror_config_support))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Latency trap Mirror-Action-Profile is not supported on this device\n");
        }

        SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_action_profile_get(unit, appl_trap_info.trap_id, &action_profile));

        if ((action_profile.fwd_strength != 0) || (action_profile.snp_strength != 0))
        {
            SHR_ERR_EXIT(_SHR_E_CONFIG, "Trap-Action-Profile is configured:\n Action profile - %d\n Fwd strength - %d\n"
                         "Snp strength - %d\n Either Mirror-Action-Profile or Trap-Action-Profile can be configured\n",
                         action_profile.profile, action_profile.fwd_strength, action_profile.snp_strength);
        }
    }
    else if (BCM_GPORT_IS_TRAP(gport))
    {
        trap_id = BCM_GPORT_TRAP_GET_ID(gport);
        snoop_strength = BCM_GPORT_TRAP_GET_SNOOP_STRENGTH(gport);
        fwd_strength = BCM_GPORT_TRAP_GET_STRENGTH(gport);
        if (snoop_strength == 0 && fwd_strength != 0)
        {
            switch (appl_trap_info.trap_block)
            {
                case DNX_RX_TRAP_BLOCK_ERPP:
                {
                    if (trap_id != BCM_RX_TRAP_EG_TRAP_ID_DEFAULT)
                    {
                        SHR_IF_ERR_EXIT(dnx_algo_rx_trap_id_erpp_is_allocated
                                        (unit, DNX_RX_TRAP_EGRESS_ACTION_PROFILE_GET(trap_id), &is_allocated));
                    }
                    fwd_action_profile_default = BCM_RX_TRAP_EG_TRAP_ID_DEFAULT;
                    break;
                }
                case DNX_RX_TRAP_BLOCK_ETPP:
                {
                    if ((trap_id != BCM_RX_TRAP_EG_TX_TRAP_ID_DEFAULT) && (trap_id != BCM_RX_TRAP_EG_TX_TRAP_ID_DROP))
                    {
                        SHR_IF_ERR_EXIT(dnx_algo_rx_trap_id_etpp_is_allocated
                                        (unit, DNX_RX_TRAP_EGRESS_ACTION_PROFILE_GET(trap_id), &is_allocated));
                    }
                    fwd_action_profile_default = BCM_RX_TRAP_EG_TX_TRAP_ID_DEFAULT;
                    break;
                }
                default:
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Trap type(%d) is not valid Egress trap ID \n", trap_type);
                    break;
                }
            }

            if ((BCM_GPORT_TRAP_GET_ID(gport) & fwd_action_profile_mask) != fwd_action_profile_default)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Trap type(%d) and Trap Gport are not in the same Egress Block! \n",
                             trap_type);
            }

            if (is_allocated == FALSE)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "The Trap ID (%d) supplied is not allocated! Please call bcm_rx_trap_type_create() first. \n",
                             trap_id);
            }
        }

        /** In case of trap, check that mirror_action_profile is not configured and one of the strengths is larger than zero */
        if ((trap_type == bcmRxTrapEgTxLatency)
            && dnx_data_trap.etpp.feature_get(unit, dnx_data_trap_etpp_latency_trap_mirror_config_support))
        {
            SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_mirror_action_profile_hw_get(unit,
                                                                          DBAL_TABLE_ETPP_LATENCY_TRAP_MIRROR_ACTION_PROFILE,
                                                                          &mirror_action_profile));

            mirror_action_profile = DNX_MIRROR_EGRESS_PROFILE_GET(unit, mirror_action_profile);
            if (mirror_action_profile != 0)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG, "Mirror-Action-Profile is configured: %d\n Either Mirror-Action-Profile or"
                             "Trap-Action-Profile can be configured\n", (int) mirror_action_profile);
            }
        }

        /** Make sure we get the profile, regardless if its Snoop_ID or Trap_ID encoding */
        action_profile.profile = DNX_RX_TRAP_EGRESS_ACTION_PROFILE_GET(trap_id);
        action_profile.fwd_strength = BCM_GPORT_TRAP_GET_STRENGTH(gport);
        action_profile.snp_strength = BCM_GPORT_TRAP_GET_SNOOP_STRENGTH(gport);

        if ((action_profile.fwd_strength == 0) && (action_profile.snp_strength == 0))
        {
            SHR_ERR_EXIT(_SHR_E_CONFIG, "Both fwd and snp strengths equal to 0, one of them should be non-zero\n");
        }

        /** Action_profile is used to configure both fwd_action_profile ans snp_action profile
              * since fwd_action_profile is allocated internally and snp_action_profile is given by the user
              * only one of the configuration can be done.
              * If both strengths are non-zero, meaning both profiles are configured, this is a misconfiguration */
        if ((action_profile.fwd_strength != 0) && (action_profile.snp_strength != 0))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Both trap and snoop strengths are non-zero. Only fwd OR snp can be configured");
        }

        if (action_profile.snp_strength > dnx_data_trap.strength.max_snp_strength_get(unit))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Snoop strength(%d) is too big, cannot be higher than the maximum strength(%d)",
                         action_profile.snp_strength, dnx_data_trap.strength.max_snp_strength_get(unit));
        }

        if (action_profile.snp_strength != 0)
        {
            if ((appl_trap_info.trap_block == DNX_RX_TRAP_BLOCK_ERPP) &&
                (action_profile.profile > dnx_data_trap.erpp.nof_erpp_snif_profiles_get(unit)))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "ERPP snoop profile is limited to 2 bits value (0-3)");
            }
            else if (action_profile.profile > dnx_data_trap.etpp.nof_etpp_snif_profiles_get(unit))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "ETPP snoop profile is limited to 3 bits value (0-7)");
            }
        }
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid gport, gport given can either be encoded as mirror or trap\n");
    }

exit:
    SHR_FUNC_EXIT;

}

/*
 *  See rx.h for info
 */
shr_error_e
bcm_dnx_rx_trap_action_profile_set(
    int unit,
    uint32 flags,
    bcm_rx_trap_t trap_type,
    bcm_gport_t gport)
{
    dnx_rx_trap_action_profile_t action_profile;
    int encoded_trap_id, mirror_action_profile;
    dnx_rx_trap_map_type_t appl_trap_info;
    int skip_invalid_value;
    uint32 hw_field_val;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    sal_memset(&appl_trap_info, 0, sizeof(dnx_rx_trap_map_type_t));

    SHR_IF_ERR_EXIT(dnx_rx_trap_action_profile_set_verify(unit, flags, trap_type, gport));

    SHR_IF_ERR_EXIT(dnx_rx_trap_appl_trap_map_info_get_dispatch(unit, trap_type, &appl_trap_info));

    if (BCM_GPORT_IS_MIRROR_MIRROR(gport))
    {
        mirror_action_profile = BCM_GPORT_MIRROR_GET(gport);
        mirror_action_profile = DNX_MIRROR_EGRESS_PROFILE_GET(unit, mirror_action_profile);
        SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_mirror_action_profile_hw_set(unit,
                                                                      DBAL_TABLE_ETPP_LATENCY_TRAP_MIRROR_ACTION_PROFILE,
                                                                      mirror_action_profile));
    }

    encoded_trap_id = BCM_GPORT_TRAP_GET_ID(gport);
    /** Make sure we get the profile, regardless if its Snoop_ID or Trap_ID encoding */
    action_profile.profile = DNX_RX_TRAP_EGRESS_ACTION_PROFILE_GET(encoded_trap_id);
    action_profile.fwd_strength = BCM_GPORT_TRAP_GET_STRENGTH(gport);
    action_profile.snp_strength = BCM_GPORT_TRAP_GET_SNOOP_STRENGTH(gport);

    /** In case of snoop need to convert profile value */
    if (action_profile.snp_strength != 0)
    {
        action_profile.profile = DNX_MIRROR_EGRESS_PROFILE_GET(unit, action_profile.profile);
    }

    switch (appl_trap_info.trap_block)
    {
        case DNX_RX_TRAP_BLOCK_ERPP:
            skip_invalid_value =
                dbal_field_types_encode_enum(unit, DBAL_FIELD_TYPE_DEF_ERPP_TRAP_ID, appl_trap_info.trap_id,
                                             &hw_field_val);
            if (skip_invalid_value != _SHR_E_UNAVAIL)
            {
                SHR_IF_ERR_EXIT(dnx_rx_trap_erpp_action_profile_hw_set(unit, appl_trap_info.trap_id, &action_profile));
            }
            break;
        case DNX_RX_TRAP_BLOCK_ETPP:
            SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_action_profile_set(unit, appl_trap_info.trap_id, &action_profile));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Illegal trap_block, only ERPP and ETPP supported\n");
            break;
    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;

}

/**
* \brief
*  Verify the parameters of dnx_rx_trap_action_profile_get API
*   \param [in] unit            - unit Id
*   \param [in] trap_type       - BCM Trap type
*   \param [in] gport_p   - Gport encoded as trap or mirror
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_action_profile_get_verify(
    int unit,
    bcm_rx_trap_t trap_type,
    bcm_gport_t * gport_p)
{
    dnx_rx_trap_map_type_t appl_trap_info;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(gport_p, _SHR_E_PARAM, "gport_p");
    sal_memset(&appl_trap_info, 0, sizeof(dnx_rx_trap_map_type_t));

    SHR_IF_ERR_EXIT(dnx_rx_trap_appl_trap_map_info_get_dispatch(unit, trap_type, &appl_trap_info));
    if (appl_trap_info.valid == FALSE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Trap type = %d , not supported \n", trap_type);
    }

exit:
    SHR_FUNC_EXIT;

}

/*
 *  See rx.h for info
 */
shr_error_e
bcm_dnx_rx_trap_action_profile_get(
    int unit,
    bcm_rx_trap_t trap_type,
    bcm_gport_t * gport_p)
{
    dnx_rx_trap_action_profile_t action_profile = { 0 };
    uint8 mirror_action_profile = 0;
    int bcm_action_profile;
    dnx_rx_trap_map_type_t appl_trap_info;
    int skip_invalid_value;
    uint32 hw_field_val;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);
    sal_memset(&appl_trap_info, 0, sizeof(dnx_rx_trap_map_type_t));

    SHR_IF_ERR_EXIT(dnx_rx_trap_action_profile_get_verify(unit, trap_type, gport_p));

    SHR_IF_ERR_EXIT(dnx_rx_trap_appl_trap_map_info_get_dispatch(unit, trap_type, &appl_trap_info));
    switch (appl_trap_info.trap_block)
    {
        case DNX_RX_TRAP_BLOCK_ERPP:
            skip_invalid_value =
                dbal_field_types_encode_enum(unit, DBAL_FIELD_TYPE_DEF_ERPP_TRAP_ID, appl_trap_info.trap_id,
                                             &hw_field_val);
            if (skip_invalid_value != _SHR_E_UNAVAIL)
            {
                SHR_IF_ERR_EXIT(dnx_rx_trap_erpp_action_profile_hw_get(unit, appl_trap_info.trap_id, &action_profile));
            }
            break;
        case DNX_RX_TRAP_BLOCK_ETPP:
            SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_action_profile_get(unit, appl_trap_info.trap_id, &action_profile));

            /** In case of mirror configuration */
            if ((trap_type == bcmRxTrapEgTxLatency)
                && dnx_data_trap.etpp.feature_get(unit, dnx_data_trap_etpp_latency_trap_mirror_config_support)
                && (action_profile.fwd_strength == 0 && action_profile.snp_strength == 0))
            {
                SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_mirror_action_profile_hw_get(unit,
                                                                              DBAL_TABLE_ETPP_LATENCY_TRAP_MIRROR_ACTION_PROFILE,
                                                                              &mirror_action_profile));

                mirror_action_profile = DNX_MIRROR_EGRESS_PROFILE_GET(unit, mirror_action_profile);
                if (mirror_action_profile != 0)
                {
                    BCM_GPORT_MIRROR_MIRROR_SET(*gport_p, mirror_action_profile);
                    SHR_EXIT();
                }
            }
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Illegal trap_block, only ERPP and ETPP supported\n");
            break;
    }

    if (action_profile.snp_strength != 0)
    {
        /** In case of snoop need to convert profile value */
        bcm_action_profile = DNX_MIRROR_EGRESS_PROFILE_GET(unit, action_profile.profile);
    }
    else
    {

        /** Encode the profile to trap_id as we do in create after we allocate */
        bcm_action_profile = DNX_RX_TRAP_ID_SET(appl_trap_info.trap_block,
                                                DNX_RX_TRAP_CLASS_USER_DEFINED, action_profile.profile);
    }

    /** Encode/set the gport with the values we get from HW */
    BCM_GPORT_TRAP_SET(*gport_p, bcm_action_profile, action_profile.fwd_strength, action_profile.snp_strength);

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Clears the ETPP trap action profile.
* \par DIRECT INPUT:
*   \param [in] unit            - unit Id
*   \param [in] dbal_trap_id    - Encoded trap ID
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_etpp_action_profile_clear(
    int unit,
    int dbal_trap_id)
{
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_trap.egress.feature_get(unit, dnx_data_trap_egress_egress_divided_to_erpp_and_etpp))
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_v1_etpp_action_profile_hw_clear(unit, dbal_trap_id));
    }
    else
    {
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Clear mirror action profile of etpp trap (stack or latency traps).
* \par DIRECT INPUT:
*   \param [in] unit            - unit Id
*   \param [in] dbal_table    - DBAL table
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_etpp_mirror_action_profile_hw_clear(
    int unit,
    dbal_tables_e dbal_table)
{
    uint8 mirror_action_profile;
    SHR_FUNC_INIT_VARS(unit);

    mirror_action_profile = DNX_MIRROR_EGRESS_PROFILE_GET(unit, 0);
    SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_mirror_action_profile_hw_set(unit, dbal_table, mirror_action_profile));

exit:
    SHR_FUNC_EXIT;
}

/*
 *  See rx.h for info
 */
shr_error_e
bcm_dnx_rx_trap_action_profile_clear(
    int unit,
    bcm_rx_trap_t trap_type)
{
    dnx_rx_trap_action_profile_t action_profile = { 0 };
    dnx_rx_trap_map_type_t appl_trap_info;
    int skip_invalid_value;
    uint32 hw_field_val;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    sal_memset(&appl_trap_info, 0, sizeof(dnx_rx_trap_map_type_t));

    SHR_IF_ERR_EXIT(dnx_rx_trap_appl_trap_map_info_get_dispatch(unit, trap_type, &appl_trap_info));

    if (appl_trap_info.valid == FALSE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Trap type = %d , not supported \n", trap_type);
    }

    switch (appl_trap_info.trap_block)
    {
        case DNX_RX_TRAP_BLOCK_ERPP:
            skip_invalid_value =
                dbal_field_types_encode_enum(unit, DBAL_FIELD_TYPE_DEF_ERPP_TRAP_ID, appl_trap_info.trap_id,
                                             &hw_field_val);
            if (skip_invalid_value != _SHR_E_UNAVAIL)
            {
                SHR_IF_ERR_EXIT(dnx_rx_trap_erpp_action_profile_hw_set(unit, appl_trap_info.trap_id, &action_profile));
            }
            break;
        case DNX_RX_TRAP_BLOCK_ETPP:
            SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_action_profile_clear(unit, appl_trap_info.trap_id));

            if (trap_type == bcmRxTrapEgTxLatency
                && dnx_data_trap.etpp.feature_get(unit, dnx_data_trap_etpp_latency_trap_mirror_config_support))
            {
                SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_mirror_action_profile_hw_clear(unit,
                                                                                DBAL_TABLE_ETPP_LATENCY_TRAP_MIRROR_ACTION_PROFILE));
            }
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Illegal trap_block, only ERPP and ETPP supported\n");
            break;
    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/*
 *  See rx_trap.h for info
 */
static shr_error_e
dnx_rx_trap_ingress_err_handling_hw_set(
    int unit,
    dbal_tables_e dbal_table,
    dbal_enum_value_field_ingress_trap_id_e dbal_ingress_trap_id)
{
    uint32 entry_handle_id, dest_encoded;
    bcm_rx_trap_config_t trap_config;
    bcm_gport_t dest;
    uint8 no_black_hole_for_unknown_destination =
        dnx_data_l2.feature.feature_get(unit, dnx_data_l2_feature_no_black_hole_for_unknown_destination);
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (no_black_hole_for_unknown_destination)
    {
        /** In case the black hole can not be set directly as a destination - encode it as a trap*/
        BCM_GPORT_TRAP_SET(dest, dbal_ingress_trap_id, dnx_data_trap.strength.max_strength_get(unit), 0);
    }
    else
    {
        dest = BCM_GPORT_BLACK_HOLE;
    }

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, dbal_table, &entry_handle_id));

    /** Translate the gport to DBAL destination*/
    SHR_IF_ERR_EXIT(algo_gpm_encode_destination_field_from_gport
                    (unit, ALGO_GPM_ENCODE_DESTINATION_FLAGS_NONE, dest, &dest_encoded));

    /** Set values */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DESTINATION, INST_SINGLE, dest_encoded);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, INST_SINGLE, dbal_ingress_trap_id);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    /** Allocate trap and configure entry action to drop packet */
    SHR_IF_ERR_EXIT(dnx_algo_rx_trap_id_ingress_predefined_allocate(unit, (int *) &dbal_ingress_trap_id));
    bcm_rx_trap_config_t_init(&trap_config);
    trap_config.flags = BCM_RX_TRAP_UPDATE_DEST;
    trap_config.dest_port = BCM_GPORT_BLACK_HOLE;
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_fwd_action_entry_hw_set(unit, dbal_ingress_trap_id, &trap_config));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 *  See rx_trap.h for info
 */
shr_error_e
dnx_rx_trap_ingress_err_handling_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    /** Initialize invalid destination error handling */
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_err_handling_hw_set(unit, DBAL_TABLE_TRAP_INGRESS_INVALID_DEST,
                                                            DBAL_ENUM_FVAL_INGRESS_TRAP_ID_INVALID_DESTINATION));
    /** Initialize memory soft error handling */
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_err_handling_hw_set(unit, DBAL_TABLE_TRAP_INGRESS_MEM_SOFT_ERR,
                                                            DBAL_ENUM_FVAL_INGRESS_TRAP_ID_MEM_SOFT_ERR));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 *   Initialize SER action profile
 *
 * \param [in] unit - Unit ID
 * \param [in] trap_id - Trap id
 *
 * \return
 *   \retval  Zero if no error was detected
 *   \retval  Negative if error was detected. See \ref shr_error_e
 *
 * \remark
 *
 * \see
 *  None.
 */
shr_error_e
dnx_rx_trap_erpp_ser_handling_init(
    int unit,
    int trap_id)
{
    uint32 entry_handle_id, profile = 0;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ERPP_TRAP_SER, &entry_handle_id));

    profile = DNX_RX_TRAP_EGRESS_ACTION_PROFILE_GET(trap_id);

    /** Set values */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_ACTION_PROFILE, INST_SINGLE, profile);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SER_TRAP_ENABLE, INST_SINGLE, TRUE);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Create default trap
* \par DIRECT INPUT:
*   \param [in] unit          -  Unit ID
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
dnx_rx_trap_ingress_default_init(
    int unit)
{
    int trap_id;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(bcm_rx_trap_type_create(unit, 0, bcmRxTrapDefault, &trap_id));
    SHR_IF_ERR_EXIT(bcm_rx_trap_type_create(unit, 0, bcmRxTrapEgressTrapped2ndPass, &trap_id));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set mirror command in action table of ingress traps
* \par DIRECT INPUT:
*   \param [in] unit          -  Unit ID
*   \param [in] trap_type       -  trap type to set its mirror action
*   \param [in] mirror_cmd       -  mirror cmd to configure
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
dnx_rx_trap_ingress_mirror_action_entry_hw_set(
    int unit,
    int trap_type,
    int mirror_cmd)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_MIRROR_ACTION_TABLE, &entry_handle_id));

    /** key construction*/
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, trap_type);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, BCM_CORE_ALL);

    /** Set the values */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_MIRROR_CMD, INST_SINGLE, mirror_cmd);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set statistical sample command in action table of ingress traps
* \par DIRECT INPUT:
*   \param [in] unit          -  Unit ID
*   \param [in] trap_type       -  trap type to set its statistical sample action
*   \param [in] stat_sample_cmd       -  statistical sample cmd to configure
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
dnx_rx_trap_ingress_stat_sample_action_entry_hw_set(
    int unit,
    int trap_type,
    int stat_sample_cmd)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_STAT_SAMPLE_ACTION_TABLE, &entry_handle_id));

    /** key construction*/
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, trap_type);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, BCM_CORE_ALL);

    /** Set the values */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_STAT_SAMPLE_CMD, INST_SINGLE, stat_sample_cmd);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
* When PMF handle ITMH one of the fields is snoop command (5 bits).
* In PMF a tranlation to snoop code (9 bits) is being done which in action resolution will be used to access HW.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_pmf_itmh_prog_snif_cmd_init(
    int unit)
{
    uint32 snif_cmd, start_ind, nof_snif_cmd;
    SHR_FUNC_INIT_VARS(unit);

    start_ind = DNX_RX_TRAP_CODE_SNIF_PROFILE_START_IND(unit);
    nof_snif_cmd = dnx_data_snif.ingress.nof_profiles_get(unit);

    /*
     * initialize snif code to snif command table
     * translation of snif code to snif command in 3 tables:
     * IPPD_SNP_CODE_TO_CMD, IPPD_MIRROR_CODE_TO_CMD, IPPD_STAT_SAMPLE_CODE_TO_CMD
     */
    for (snif_cmd = 0; snif_cmd < nof_snif_cmd; snif_cmd++)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_snp_action_entry_hw_set(unit, snif_cmd + start_ind, snif_cmd));
        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_mirror_action_entry_hw_set(unit, snif_cmd + start_ind, snif_cmd));
        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_stat_sample_action_entry_hw_set(unit, snif_cmd + start_ind, snif_cmd));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
* Predefined ingress traps have a specific predefined index in tables action/snoop
* need to initialize trap code field of predefined trap to known value
* \param [in] unit  - Device ID
* \param [in] trap_dbal_enum_val  - trap dbal enum value to set
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_code_hw_set(
    int unit,
    uint32 trap_dbal_enum_val)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_CODE_SET, &entry_handle_id));

    /** DBAL key */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, trap_dbal_enum_val);

    /** DBAL value*/
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, INST_SINGLE, trap_dbal_enum_val);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
* Initialize default trap code of all ports to be TRAP_NONE
* \param [in] unit  - Device ID
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_port_default_trap_code_hw_set(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_PP_PORT, &entry_handle_id));

    /** DBAL key */
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, DBAL_RANGE_ALL, DBAL_RANGE_ALL);

    /** DBAL value*/
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, INST_SINGLE,
                                 DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_NONE);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Some predifined ingress traps have a trap code memory field
* initialize these fields to predefined values
* \param [in] unit  - Device ID
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_code_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_hw_set(unit, DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FER_UC_STRICT_RPF_FAIL));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_hw_set(unit, DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FLP_UC_LOOSE_RPF_FAIL));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_hw_set(unit, DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FER_SIP_TRANSPLANT_DETECTION));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_hw_set(unit, DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FER_MC_EXPLICIT_RPF_FAIL));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_hw_set(unit, DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FER_MC_USE_SIP_RPF_FAIL));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_hw_set(unit, DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FER_FACILITY_INVALID));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_hw_set(unit, DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FER_OUTLIF_OVERFLOW));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_hw_set(unit, DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FLP_IPV4_TTL0));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_hw_set(unit, DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FLP_IPV4_TTL1));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_hw_set(unit, DBAL_ENUM_FVAL_INGRESS_TRAP_ID_VTT_MY_MAC_AND_IP_DISABLE));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_hw_set(unit, DBAL_ENUM_FVAL_INGRESS_TRAP_ID_VTT_MY_MAC_AND_MPLS_DISABLE));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_hw_set(unit, DBAL_ENUM_FVAL_INGRESS_TRAP_ID_VTT_MY_MAC_AND_ARP));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_hw_set(unit, DBAL_ENUM_FVAL_INGRESS_TRAP_ID_VTT_MY_MAC_AND_UNKNOWN_L3));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_hw_set
                    (unit, DBAL_ENUM_FVAL_INGRESS_TRAP_ID_VTT_MPLS_PREPROCESSING_BOS_OR_TTL_TRAP));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_hw_set(unit, DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FLP_MPLS_TTL0));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_hw_set(unit, DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FLP_MPLS_TTL1));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_hw_set(unit, DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FLP_IPV6_HOP_COUNT0));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_hw_set(unit, DBAL_ENUM_FVAL_INGRESS_TRAP_ID_FLP_IPV6_HOP_COUNT1));

    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_port_default_trap_code_hw_set(unit));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
* Each layer protocol can have a different Ethernet Trap-Action-Profile
* Initialize Action-Prodile-idx for a given layer protocol
* \param [in] unit  - Device ID
* \param [in] layer_protocol  - protocol layer to configure its index
* \param [in] action_profile_idx  - Ethernet Trap-Action-Profile index
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_eth_trap_vector_hw_set(
    int unit,
    uint32 layer_protocol,
    dnx_rx_trap_eth_profiles_e action_profile_idx)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_ETHERNET_LAYER_PROTOCOL_MAP, &entry_handle_id));

    /** DBAL key - initalize both UC/MC */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LAYER_PROTOCOL, layer_protocol);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_IS_MC, DBAL_RANGE_ALL, DBAL_RANGE_ALL);

    /** DBAL value*/
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ACTION_PROFILE_IDX, INST_SINGLE, action_profile_idx);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
* Initialize Ethernet trap vector (Action-Prodile-idx for each layer protocol)
* \param [in] unit  - Device ID
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_eth_trap_vector_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_eth_trap_vector_hw_set(unit, DBAL_ENUM_FVAL_LAYER_TYPES_IPV4,
                                                               DNX_RX_TRAP_ETH_PROFILE_VTT_MY_MAC_AND_IP_DISABLE));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_eth_trap_vector_hw_set(unit, DBAL_ENUM_FVAL_LAYER_TYPES_IPV6,
                                                               DNX_RX_TRAP_ETH_PROFILE_VTT_MY_MAC_AND_IP_DISABLE));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_eth_trap_vector_hw_set(unit, DBAL_ENUM_FVAL_LAYER_TYPES_MPLS,
                                                               DNX_RX_TRAP_ETH_PROFILE_VTT_MY_MAC_AND_MPLS_DISABLE));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_eth_trap_vector_hw_set(unit, DBAL_ENUM_FVAL_LAYER_TYPES_ARP,
                                                               DNX_RX_TRAP_ETH_PROFILE_VTT_MY_MAC_AND_ARP));
    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_eth_trap_vector_hw_set(unit, DBAL_ENUM_FVAL_LAYER_TYPES_UNKNOWN,
                                                               DNX_RX_TRAP_ETH_PROFILE_VTT_MY_MAC_AND_UNKNOWN_L3));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
* Initialize forward action table to default values:
* FWD_DESTINATION_VALID = 1, used to validate the destination of packet is valid
* \param [in] unit  - Device ID
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_ingress_fwd_action_init(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_FWD_ACTION_TABLE, &entry_handle_id));

    /** Set keys - all trap_id range and all cores */
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, BCM_CORE_ALL);

    /** Set values */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FWD_DESTINATION_VALID, INST_SINGLE, TRUE);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_STAT_OBJ_VALID_CLEAR, INST_SINGLE,
                                 DNX_RX_TRAP_ACTION_STAT_OBJ_CLEAR_DEFAULT);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    /** Clear the entry for other cores and entries*/
    SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_TRAP_INGRESS_FWD_ACTION_TABLE, entry_handle_id));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
* Initialize snoop recycle traps:
* Create bcmRxTrapEgTxFieldSnoop0-15 traps and map each to snif command.
* \param [in] unit  - Device ID
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_snp_recycle_cmd_init(
    int unit)
{
    uint32 snif_cmd, nof_snoop_rcy_cmd;
    int trap_id;
    SHR_FUNC_INIT_VARS(unit);

    nof_snoop_rcy_cmd = dnx_data_snif.ingress.mirror_nof_profiles_get(unit);

    /*
     * initialize snif code to snif command table
     * translation of snif code to snif command in 3 tables:
     * IPPD_SNP_CODE_TO_CMD, IPPD_MIRROR_CODE_TO_CMD, IPPD_STAT_SAMPLE_CODE_TO_CMD
     */
    for (snif_cmd = 0; snif_cmd < nof_snoop_rcy_cmd; snif_cmd++)
    {
        SHR_IF_ERR_EXIT(bcm_rx_trap_type_create(unit, 0, bcmRxTrapEgTxFieldSnoop0 + snif_cmd, &trap_id));
        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_snp_action_entry_hw_set(unit, trap_id, snif_cmd));
        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_mirror_action_entry_hw_set(unit, trap_id, snif_cmd));
        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_stat_sample_action_entry_hw_set(unit, trap_id, snif_cmd));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
* Initialize forward recycle command table to default values:
* All profiles except default (0) should be configured to drop as default.
* \param [in] unit  - Device ID
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_fwd_recycle_cmd_init(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_FWD_RCY_CMD_MAP, &entry_handle_id));

    /** Set all recycle commands to default on all cores */
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_RECYCLE_COMMAND_ID, 0,
                                     DNX_RX_TRAP_FWD_RCY_PROFILE_DROP);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, BCM_CORE_ALL);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, INST_SINGLE,
                                 DBAL_ENUM_FVAL_INGRESS_TRAP_ID_TRAP_NONE);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, INST_SINGLE, 0);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    /** For united egress devices, following profiles are part of the configurable fwd recycle profiles pool *
     *  and do not need to be allocated separately */
    if (dnx_data_trap.egress.feature_get(unit, dnx_data_trap_egress_egress_divided_to_erpp_and_etpp))
    {
        /** Set fwd recycle command for Egress trapped packets */
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_RECYCLE_COMMAND_ID,
                                   DNX_RX_TRAP_FWD_RCY_PROFILE_EGRESS_TRAPPED);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, BCM_CORE_ALL);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, INST_SINGLE,
                                     DBAL_ENUM_FVAL_INGRESS_TRAP_ID_EGRESS_TRAPPED_2ND_PASS);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, INST_SINGLE,
                                     dnx_data_trap.strength.max_strength_get(unit) - 1);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
        SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_TRAP_FWD_RCY_CMD_MAP, entry_handle_id));
    }

    /** Set FWD_RCY_PROFILE_DROP */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_RECYCLE_COMMAND_ID, DNX_RX_TRAP_FWD_RCY_PROFILE_DROP);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, BCM_CORE_ALL);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, INST_SINGLE,
                                 DBAL_ENUM_FVAL_INGRESS_TRAP_ID_DEFAULT_DROP_TRAP);
    /** Set trap strength to max - 1, so in some cases (like outbound mirror), PMF could disable the drop of a recycled packet */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, INST_SINGLE,
                                 dnx_data_trap.strength.max_strength_get(unit) - 1);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Initialize ERPP forward strength and snoop strength.
 *   This is done due to wrong default value in HW.
 *   default values for forward strength and snoop strength
 *   should be zero.
 * \param [in] unit  - Device ID
 * \return
 *   shr_error_e - Error Type
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_rx_trap_erpp_regs_init(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ERPP_TRAP_ACTION_PROFILE, &entry_handle_id));

    /** Set keys
     *  Key is start value is (DBAL_ENUM_FVAL_ERPP_TRAP_ID_DEFAULT_TRAP + 1) because
     *  DBAL_ENUM_FVAL_ERPP_TRAP_ID_DEFAULT_TRAP is the 0 value of the ENUM and is not mapped to any register.
     *  It exists only for valid check and distinction.
     */
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_ERPP_TRAP_ID,
                                     (DBAL_ENUM_FVAL_ERPP_TRAP_ID_DEFAULT_TRAP + 1), DBAL_RANGE_ALL);

    /** Set values */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, INST_SINGLE, 0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_SNP_STRENGTH, INST_SINGLE, 0);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Initialize ETPP_CFG_FHEI_TYPE_CPU_TRAP table.
 * The function configures the default FHEI type for CPU Trap - TRAP_SNOOP.
 * \param [in] unit  - Device ID
 * \return
 *   shr_error_e - Error Type
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_rx_trap_fhei_cpu_type_init(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ETPP_CFG_FHEI_TYPE_CPU_TRAP, &entry_handle_id));
    /** Set value field */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_FHEI_TYPE_CPU_TRAP, INST_SINGLE,
                                 DBAL_ENUM_FVAL_FHEI_TYPE_TRAP_SNOOP);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Initialize for table that determine if to deny or perform meter trap.
 *   Set deny meter for all relevant types by default.
 * \param [in] unit  - Device ID
 * \return
 *   shr_error_e - Error Type
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_rx_trap_deny_meter_init(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ETPP_CFG_DENY_METER_ON_TRAP, &entry_handle_id));
    /** Set value field */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DENY_METER_ON_PROTECTION_TRAP, INST_SINGLE, TRUE);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DENY_METER_ON_STACK_TRAP, INST_SINGLE, TRUE);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DENY_METER_ON_SPLIT_HORIZON_TRAP, INST_SINGLE, TRUE);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}
/**
 * \brief
 *   Initialize for table that determine if to deny or perform count trap.
 *   Set count meter for all relevant types by default.
 * \param [in] unit  - Device ID
 * \return
 *   shr_error_e - Error Type
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_rx_trap_deny_count_init(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ETPP_CFG_DENY_COUNT_ON_TRAP, &entry_handle_id));
    /** Set value field */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DENY_COUNT_ON_PROTECTION_TRAP, INST_SINGLE, TRUE);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DENY_COUNT_ON_STACK_TRAP, INST_SINGLE, TRUE);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DENY_COUNT_ON_SPLIT_HORIZON_TRAP, INST_SINGLE, TRUE);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Initialize mapping of ingress strength (4b) to TM profile (2b) and forward strength (1b).
 *   The 3b compressed strength (TM profile + forward strength) is later mapped to 4b in Egress
 * \param [in] unit  - Device ID
 * \return
 *   shr_error_e - Error Type
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_rx_trap_ingress_strength_map_init(
    int unit)
{
    uint32 entry_handle_id;
    uint8 max_compressed_strength = dnx_data_trap.strength.max_ingress_to_egress_compressed_strength_get(unit);
    uint8 max_strength = dnx_data_trap.strength.max_strength_get(unit);
    uint8 strength = 0, tm_profile = 0, compressed_strength = 0;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_FWD_STRENGTH_MAP, &entry_handle_id));

    /** First 8 profiles are configured as one to one mapping */
    for (strength = 0; strength < max_compressed_strength; ++strength)
    {
        /** Set keys */
        dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, strength);

        tm_profile = DNX_RX_TRAP_TM_PROFILE_GET(strength);
        compressed_strength = DNX_RX_TRAP_FWD_COMPRESSED_STRENGTH_GET(strength);

        /** Set values */
        dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_TM_PROFILE, INST_SINGLE, tm_profile);
        dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_FWD_COMPRESSED_STRENGTH, INST_SINGLE,
                                    compressed_strength);

        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

    /** Last 8 profiles are configured to max compressed strength mapping */
    tm_profile = DNX_RX_TRAP_TM_PROFILE_GET(max_compressed_strength);
    compressed_strength = DNX_RX_TRAP_FWD_COMPRESSED_STRENGTH_GET(max_compressed_strength);

    /** Set keys */
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, max_compressed_strength,
                                     max_strength);

    /** Set values */
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_TM_PROFILE, INST_SINGLE, tm_profile);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_FWD_COMPRESSED_STRENGTH, INST_SINGLE,
                                compressed_strength);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function purpose is to initialize TrapInLifProfileTable
* \par DIRECT INPUT:
*   \param [in] unit      -  unit Id
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * Maps the inlif profile to another profile, used by ingress protocol traps block on J2C
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_in_lif_profile_map_init(
    int unit)
{
    uint32 entry_handle_id, in_lif_profile, msb_mask = 0x80;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PROTOCOL_TRAP_IN_LIF_PROFILE_MAPPING, &entry_handle_id));

    for (in_lif_profile = 0; (in_lif_profile & msb_mask) == 0; in_lif_profile++)
    {
        /** key construction - 7 lsb in in_lif_profile */
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_IN_LIF_PROFILE, (in_lif_profile & 0x7f));

        /** InLifProfile0 configures InLif profiles 0 to 127
          * InLifProfile1 configures InLif profiles 128 to 255
          * Each for loop configures two coresponding lines in InLifProfile0 and InLifProfile1 */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_IN_LIF_PROFILE_0, INST_SINGLE,
                                     in_lif_profile);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_IN_LIF_PROFILE_1, INST_SINGLE,
                                     (in_lif_profile | msb_mask));

        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Initialize mapping of ingress compressed strength (3b) to egress strength (4b).
 * \param [in] unit  - Device ID
 * \param [in] dbal_table  - mapping dbal table
 * \return
 *   shr_error_e - Error Type
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_rx_trap_egress_strength_map_init(
    int unit,
    dbal_tables_e dbal_table)
{
    uint32 entry_handle_id;
    uint8 max_compressed_strength = dnx_data_trap.strength.max_ingress_to_egress_compressed_strength_get(unit);
    uint8 strength = 0;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, dbal_table, &entry_handle_id));

    for (strength = 0; strength <= max_compressed_strength; ++strength)
    {
        /** Set keys */
        dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_TRAP_COMPRESSED_STRENGTH, strength);

        /** Set values */
        dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, INST_SINGLE, strength);

        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Initialize snif mapping to snoop and mirror.
 *   Sniff profile have only 2 bits which can be passed between ERPP and ETPP.
 *   Added 1 to 1 mapping of these 2 bits to snoop_action, snoop_strength and mirror_action.
 * \param [in] unit  - Device ID
 * \return
 *   shr_error_e - Error Type
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_rx_trap_etpp_snif_map_init(
    int unit)
{
    uint32 entry_handle_id;
    uint32 nof_erpp_snif_profiles = dnx_data_trap.erpp.nof_erpp_snif_profiles_get(unit);
    int erpp_snif_profile = 0, etpp_snif_profile = 0;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ETPP_TRAP_SNIF_MAP, &entry_handle_id));

    for (erpp_snif_profile = 0; erpp_snif_profile < nof_erpp_snif_profiles; ++erpp_snif_profile)
    {
        /** Set keys */
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_SNIF_ACTION_PROFILE, erpp_snif_profile);

        etpp_snif_profile = DNX_MIRROR_EGRESS_PROFILE_GET(unit, erpp_snif_profile);

        /** Set values */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SNP_ACTION_PROFILE, INST_SINGLE,
                                     etpp_snif_profile);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_MRR_ACTION_PROFILE, INST_SINGLE,
                                     etpp_snif_profile);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_SNP_STRENGTH, INST_SINGLE,
                                     erpp_snif_profile);

        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Initialize ETPP mirror action profile to default profile.
 *   ETPP mirror action profiles od traps are initialized to 0 which is not the default mirror profile
 *   Function initializes the valuses to defualt using dnx_rx_trap_etpp_mirror_action_profile_hw_clear
 * \param [in] unit  - Device ID
 * \return
 *   shr_error_e - Error Type
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_rx_trap_etpp_mirror_action_profile_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_mirror_action_profile_hw_clear(unit,
                                                                    DBAL_TABLE_ETPP_LATENCY_TRAP_MIRROR_ACTION_PROFILE));
    SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_mirror_action_profile_hw_clear(unit,
                                                                    DBAL_TABLE_ETPP_STACK_TRAP_MIRROR_ACTION_PROFILE));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Initialize trap mappings registers and memorys.
 *   The mappings are of compressed data transfered between different blocks of the device.
 * \param [in] unit  - Device ID
 * \return
 *   shr_error_e - Error Type
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_rx_trap_mappings_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_strength_map_init(unit));

    if (dnx_data_trap.egress.feature_get(unit, dnx_data_trap_egress_egress_divided_to_erpp_and_etpp))
    {
        /** Map decomppression of ingress strength (3b) to ERPP strength (4b) */
        SHR_IF_ERR_EXIT(dnx_rx_trap_egress_strength_map_init(unit, DBAL_TABLE_ERPP_TRAP_STRENGTH_MAP));

        /** Map decomppression of snif profile (2b) */
        SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_snif_map_init(unit));
    }

    /** Map decomppression of ingress strength (3b) to ETPP strength (4b) */
    SHR_IF_ERR_EXIT(dnx_rx_trap_egress_strength_map_init(unit, DBAL_TABLE_ETPP_TRAP_STRENGTH_MAP));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Initialize NDP trap ICMP_NDP_NEIGHBOR_SOLICITATION_TYPE
 * \param [in] unit  - Device ID
 * \return
 *   shr_error_e - Error Type
 * \remark
 *   * None
 * \see
 *   * IPPB_ICMP_NDP_NEIGHBOR_SOLICITATION_TYPE
 */
static shr_error_e
dnx_rx_trap_protocol_ndp_init(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PROTOCOL_TRAP_NDP, &entry_handle_id));

    /** DBAL value*/
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_NEIGHBOR_SOLICITATION_TYPE, INST_SINGLE,
                                 DNX_RX_TRAP_NEIGHBOR_SOLICITATION_TYPE);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Enabling the ICMP traps for ETH, IPv4 and IPv6 in the HW.
* \par DIRECT INPUT:
*   \param [in] unit      -  unit Id
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_icmp_enablers_init(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ICMP_TRAP_CFG, &entry_handle_id));

    /*
     * Set the values
     */
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_ICMP_TRAP_ETH, INST_SINGLE, TRUE);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_ICMP_TRAP_IPV4, INST_SINGLE, TRUE);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_ICMP_TRAP_IPV6, INST_SINGLE, TRUE);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Initalize enablers of ETPP lif profiles. 3 enablers for stack_trap1, stack_trap2, stack_mirror
* profile DNX_RX_TRAP_ETPP_LIF_PROFILE_DEFAULT - simple forwarding all disabled
* profile DNX_RX_TRAP_ETPP_LIF_PROFILE_STACK_TRAP_1 - only stack_trap1 enabled
* profile DNX_RX_TRAP_ETPP_LIF_PROFILE_STACK_TRAP_2 - only stack_trap2 enabled
* profile DNX_RX_TRAP_ETPP_LIF_PROFILE_STACK_MIRROR - only stack_mirror enabled
* \par DIRECT INPUT:
*   \param [in] unit      -  unit Id
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_etpp_lif_enablers_init(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ETPP_TRAP_LIF_ACTION_PROFILE, &entry_handle_id));

    /** Set profile DNX_RX_TRAP_ETPP_LIF_PROFILE_STACK_TRAP_1 - enable stack_trap1 */
    dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_ACTION_PROFILE,
                              DNX_RX_TRAP_ETPP_LIF_PROFILE_STACK_TRAP_1);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_STACK_TRAP_1_ENABLE, INST_SINGLE, TRUE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_ETPP_TRAP_LIF_ACTION_PROFILE, entry_handle_id));

    /** Set profile DNX_RX_TRAP_ETPP_LIF_PROFILE_STACK_TRAP_2 - enable stack_trap2 */
    dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_ACTION_PROFILE,
                              DNX_RX_TRAP_ETPP_LIF_PROFILE_STACK_TRAP_2);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_STACK_TRAP_2_ENABLE, INST_SINGLE, TRUE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_ETPP_TRAP_LIF_ACTION_PROFILE, entry_handle_id));

    /** Set profile DNX_RX_TRAP_ETPP_LIF_PROFILE_STACK_MIRROR - enable stack_mirror */
    dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_ACTION_PROFILE,
                              DNX_RX_TRAP_ETPP_LIF_PROFILE_STACK_MIRROR);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_STACK_MRR_ENABLE, INST_SINGLE, TRUE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Enable mtu port check
* \par DIRECT INPUT:
*   \param [in] unit        - unit Id
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_etpp_mtu_port_enable_init(
    int unit)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** set mtu enable */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_ETPP_GLOBAL, &entry_handle_id));
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_MTU_ENABLE, INST_SINGLE, TRUE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Initializing the Ingress trap profile selector per Port or In-LIF,
*  based on the 'protocol_traps_mode' soc property.
* \par DIRECT INPUT:
*   \param [in] unit      -  unit Id
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_protocol_mode_init(
    int unit)
{
    uint32 entry_handle_id;
    uint8 protocol_trap_mode;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_TRAP_PROFILE_SELECTOR_CFG, &entry_handle_id));
    /*
     * It is a 128 bit field, with 2'b per context, for each trap, which theoretically supports 4 modes.
     * The mode is retrieved/decided per context, which we set here.
     */
    dbal_entry_key_field8_range_set(unit, entry_handle_id, DBAL_FIELD_CONTEXT_PROFILE, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    /*
     * Set the values
     */
    protocol_trap_mode = dnx_data_trap.ingress.protocol_traps_init_mode_get(unit);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_PROFILE_MODE, INST_SINGLE,
                                protocol_trap_mode);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set the default forwarding destination for MPLS contexts to be MPLS
*  unknown label pre-defined trap.
* \par DIRECT INPUT:
*   \param [in] unit      -  unit Id
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_mpls_unknown_label_init(
    int unit)
{
    uint32 entry_handle_id;
    uint32 trap_dest;
    uint32 trap_dest_w_default_bit;
    int trap_id;
    int trap_strength = dnx_data_trap.strength.default_trap_strength_get(unit);
    bcm_gport_t trap_gport;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_type_to_id(unit, bcmRxTrapMplsUnknownLabel, &trap_id));
    BCM_GPORT_TRAP_SET(trap_gport, trap_id, trap_strength, 0);
    SHR_IF_ERR_EXIT(algo_gpm_encode_destination_field_from_gport
                    (unit, ALGO_GPM_ENCODE_DESTINATION_FLAGS_NONE, trap_gport, &trap_dest));

    trap_dest_w_default_bit = trap_dest << 1;
    /** Iterate over the result fields of FWD1/FWD2 table and set the trap ID as destination */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_ING_FWD_DEFAULT_FORWARD_RESULT, &entry_handle_id));
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DEFAULT_GROUP_MPLS, INST_SINGLE,
                                 trap_dest_w_default_bit);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Configure all trap related that is relevant for device initiation
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
dnx_rx_trap_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_default_init(unit));

    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_fwd_action_init(unit));

    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_err_handling_init(unit));

    SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_code_init(unit));

    SHR_IF_ERR_EXIT(dnx_rx_trap_pmf_itmh_prog_snif_cmd_init(unit));

    SHR_IF_ERR_EXIT(dnx_rx_trap_snp_recycle_cmd_init(unit));

    SHR_IF_ERR_EXIT(dnx_rx_trap_description_init_check_dispatch(unit));

    SHR_IF_ERR_EXIT(dnx_rx_trap_mappings_init(unit));

    SHR_IF_ERR_EXIT(dnx_rx_trap_fhei_cpu_type_init(unit));

    SHR_IF_ERR_EXIT(dnx_rx_trap_deny_meter_init(unit));

    SHR_IF_ERR_EXIT(dnx_rx_trap_deny_count_init(unit));

    SHR_IF_ERR_EXIT(dnx_rx_trap_fwd_recycle_cmd_init(unit));

    SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_lif_enablers_init(unit));

    SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_mtu_port_enable_init(unit));

    if (dnx_data_trap.egress.feature_get(unit, dnx_data_trap_egress_egress_divided_to_erpp_and_etpp))
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_erpp_regs_init(unit));

        SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_mirror_action_profile_init(unit));
    }

    /** Map in lif profile to trap in lif profile */
    if (dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_trap_in_lif_profile_mapping))
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_in_lif_profile_map_init(unit));
    }

    if (dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_ndp_trap_en) == TRUE)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_ndp_init(unit));
    }

    SHR_IF_ERR_EXIT(dnx_rx_trap_icmp_enablers_init(unit));

    SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_mode_init(unit));

    if (dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_eth_trap_vec_mapping_support))
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_eth_trap_vector_init(unit));
    }

    SHR_IF_ERR_EXIT(dnx_rx_trap_mpls_unknown_label_init(unit));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Verify the protocol trap key parameters
* \par DIRECT INPUT:
*   \param [in] unit     -  unit id
*   \param [in] key_p   -  protocol trap key parameters
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_protocol_key_verify(
    int unit,
    bcm_rx_trap_protocol_key_t * key_p)
{
    uint8 nof_protocol_trap_profiles = dnx_data_trap.ingress.nof_protocol_trap_profiles_get(unit);
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Check NULL param
     */
    SHR_NULL_CHECK(key_p, _SHR_E_PARAM, "config_p");

    if (key_p->protocol_trap_profile >= nof_protocol_trap_profiles)
    {
        SHR_ERR_EXIT(_SHR_E_CONFIG, "Invalid protocol trap profile = %d, max profile number is %d\n",
                     key_p->protocol_trap_profile, nof_protocol_trap_profiles - 1);
    }

    switch (key_p->protocol_type)
    {
        case bcmRxTrapL2cpPeer:
            if (key_p->trap_args >= DNX_RX_TRAP_NOF_L2CP_PROTOCOL_TRAP_ARGS)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG, "Invalid argument = %d (L2CP MAC LSB varies from 0 to %d)\n",
                             key_p->trap_args, DNX_RX_TRAP_NOF_L2CP_PROTOCOL_TRAP_ARGS - 1);
            }
            break;
        case bcmRxTrapIcmpRedirect:
            if (key_p->trap_args >= DNX_RX_TRAP_NOF_ICMP_PROTOCOL_TRAP_ARGS)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG, "Invalid argument = %d (ICMP types varies from 0 to %d)\n",
                             key_p->trap_args, DNX_RX_TRAP_NOF_ICMP_PROTOCOL_TRAP_ARGS - 1);
            }
            break;
        case bcmRxTrap8021xFail:
        case bcmRxTrapIgmpMembershipQuery:
        case bcmRxTrapIgmpReportLeaveMsg:
        case bcmRxTrapIgmpUndefined:
        case bcmRxTrapDhcpv4Client:
        case bcmRxTrapDhcpv4Server:
        case bcmRxTrapDhcpv6Client:
        case bcmRxTrapDhcpv6Server:
        case bcmRxTrapArp:
        case bcmRxTrapArpMyIp:
            if (key_p->trap_args != 0)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG, "Invalid argument = %d, protocol type = %d can't receive arguments\n",
                             key_p->trap_args, key_p->protocol_type);
            }
            break;
        case bcmRxTrapNdp:
        case bcmRxTrapNdpMyIp:
            if (dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_ndp_trap_en) == FALSE)
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "NDP and NDPMyIp are not support on Jericho2."
                             "Please use ACL to cover this functionality. \n");
            }
            if (key_p->trap_args != 0)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG, "Invalid argument = %d, protocol type = %d can't receive arguments\n",
                             key_p->trap_args, key_p->protocol_type);
            }
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_CONFIG, "Invalid protocol type = %d\n", key_p->protocol_type);
            break;
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function purpose is to set trap action profile in HW of given protocol trap
* \par DIRECT INPUT:
*   \param [in] unit      -  unit Id
*   \param [in] protocol_dbal_table  -  protocol type dbal table
*   \param [in] key_p   -  protocol trap key parameters
*   \param [in] config_p  -  trap configuration struct, holds the trap action profile
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_protocol_action_profile_hw_set(
    int unit,
    dbal_tables_e protocol_dbal_table,
    bcm_rx_trap_protocol_key_t * key_p,
    dnx_rx_trap_protocol_config_t * config_p)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, protocol_dbal_table, &entry_handle_id));

    /*
     * key construction
     */
    if (protocol_dbal_table != DBAL_TABLE_PROTOCOL_L2CP_TRAP_ACTION_PROFILE)
    {
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROTOCOL_TYPE, key_p->protocol_type);
    }

    if (protocol_dbal_table != DBAL_TABLE_PROTOCOL_8021X_TRAP_ACTION_PROFILE)
    {
        dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_PROTOCOL_TRAP_ARGS, key_p->trap_args);
    }

    dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_PROTOCOL_TRAP_PROFILE, key_p->protocol_trap_profile);

    /*
     * Set the values
     */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, INST_SINGLE, config_p->trap_id);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, INST_SINGLE,
                                 config_p->fwd_strength);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_SNP_STRENGTH, INST_SINGLE,
                                 config_p->snp_strength);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function purpose is to get the trap action profile fron HW of a given protocol trap
* \par DIRECT INPUT:
*   \param [in] unit      -  unit id
*   \param [in] protocol_dbal_table  -  protocol type dbal table
*   \param [in] key_p   -  protocol trap key parameters
*   \param [out] config_p  -  trap configuration struct, holds the trap action profile retrieved
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_protocol_action_profile_hw_get(
    int unit,
    dbal_tables_e protocol_dbal_table,
    bcm_rx_trap_protocol_key_t * key_p,
    dnx_rx_trap_protocol_config_t * config_p)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(config_p, _SHR_E_PARAM, "config_p");

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, protocol_dbal_table, &entry_handle_id));

    /*
     * key construction
     */
    if (protocol_dbal_table != DBAL_TABLE_PROTOCOL_L2CP_TRAP_ACTION_PROFILE)
    {
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROTOCOL_TYPE, key_p->protocol_type);
    }

    if (protocol_dbal_table != DBAL_TABLE_PROTOCOL_8021X_TRAP_ACTION_PROFILE)
    {
        dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_PROTOCOL_TRAP_ARGS, key_p->trap_args);
    }

    dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_PROTOCOL_TRAP_PROFILE, key_p->protocol_trap_profile);

    /*
     * Get the values
     */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, INST_SINGLE,
                               (uint32 *) &config_p->trap_id);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, INST_SINGLE,
                               (uint32 *) &config_p->fwd_strength);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_TRAP_SNP_STRENGTH, INST_SINGLE,
                               (uint32 *) &config_p->snp_strength);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function purpose is to clear the trap action profile hw of a given protocol trap
* \par DIRECT INPUT:
*   \param [in] unit      -  unit id
*   \param [in] protocol_dbal_table  -  protocol type dbal table
*   \param [in] key_p   -  protocol trap key parameters
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_protocol_action_profile_hw_clear(
    int unit,
    dbal_tables_e protocol_dbal_table,
    bcm_rx_trap_protocol_key_t * key_p)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, protocol_dbal_table, &entry_handle_id));

    /*
     * key construction
     */
    if (protocol_dbal_table != DBAL_TABLE_PROTOCOL_L2CP_TRAP_ACTION_PROFILE)
    {
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROTOCOL_TYPE, key_p->protocol_type);
    }

    if (protocol_dbal_table != DBAL_TABLE_PROTOCOL_8021X_TRAP_ACTION_PROFILE)
    {
        dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_PROTOCOL_TRAP_ARGS, key_p->trap_args);
    }

    dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_PROTOCOL_TRAP_PROFILE, key_p->protocol_trap_profile);

    /*
     * Clear the values
     */
    SHR_IF_ERR_EXIT(dbal_entry_clear(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Sets the Compressed ICMP type in the ICMP type compression table.
* \par DIRECT INPUT:
*   \param [in] unit                    - unit Id
*   \param [in] icmp_type               - ICMP type
*   \param [in] compressed_icmp_type    - Compressed ICMP type
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_icmp_compressed_type_hw_set(
    int unit,
    int icmp_type,
    int compressed_icmp_type)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ICMP_TYPE_COMPRESSION_TABLE, &entry_handle_id));

    /*
     * key construction
     */
    dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_ICMP_TYPE, icmp_type);
    /*
     * Set the compressed ICMP type
     */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_COMPRESSED_ICMP_TYPE, INST_SINGLE,
                                 compressed_icmp_type);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * See rx_trap.h
 */
shr_error_e
dnx_rx_trap_icmp_compressed_type_hw_get(
    int unit,
    int icmp_type,
    uint32 *compressed_icmp_type)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ICMP_TYPE_COMPRESSION_TABLE, &entry_handle_id));

    /*
     * key construction
     */
    dbal_entry_key_field8_set(unit, entry_handle_id, DBAL_FIELD_ICMP_TYPE, icmp_type);
    /*
     * Set the compressed ICMP type
     */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_COMPRESSED_ICMP_TYPE, INST_SINGLE,
                               compressed_icmp_type);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function allocates a Compressed ICMP type according to given configuration.
* \par DIRECT INPUT:
*   \param [in] unit        - unit id
*   \param [out] key_p      - protocol trap key parameters
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_icmp_type_compressed_set(
    int unit,
    bcm_rx_trap_protocol_key_t * key_p)
{
    int compressed_icmp_type;
    uint32 compressed_icmp_type_get;
    uint8 is_alloc = FALSE;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(key_p, _SHR_E_PARAM, "key_p");

    SHR_IF_ERR_EXIT(dnx_rx_trap_icmp_compressed_type_hw_get(unit, key_p->trap_args, &compressed_icmp_type_get));

    compressed_icmp_type = compressed_icmp_type_get;

    if (compressed_icmp_type != 0)
    {
        SHR_IF_ERR_EXIT(dnx_algo_rx_trap_icmp_compressed_type_is_allocated(unit, compressed_icmp_type, &is_alloc));
    }
    if (!is_alloc)
    {
        SHR_IF_ERR_EXIT(dnx_algo_rx_trap_icmp_compressed_type_allocate(unit, 0, &compressed_icmp_type));
    }

    SHR_IF_ERR_EXIT(dnx_rx_trap_icmp_compressed_type_hw_set(unit, key_p->trap_args, compressed_icmp_type));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get DBAL info, table + key, for configuring protocol in HW
* \par DIRECT INPUT:
*   \param [in] unit      -  unit id
*   \param [in] key_p   -  protocol trap key parameters
*   \param [out] protocol_dbal_table_p   - protocol_type dbal table
*   \param [out] dbal_key_p     -  protocol trap DBAL key
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_protocol_dbal_info_get(
    int unit,
    bcm_rx_trap_protocol_key_t * key_p,
    dbal_tables_e * protocol_dbal_table_p,
    bcm_rx_trap_protocol_key_t * dbal_key_p)
{

    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(protocol_dbal_table_p, _SHR_E_PARAM, "protocol_dbal_table_p");
    SHR_NULL_CHECK(dbal_key_p, _SHR_E_PARAM, "dbal_key_p");

    dbal_key_p->protocol_trap_profile = key_p->protocol_trap_profile;

    switch (key_p->protocol_type)
    {
        case bcmRxTrapL2cpPeer:
            *protocol_dbal_table_p = DBAL_TABLE_PROTOCOL_L2CP_TRAP_ACTION_PROFILE;
            dbal_key_p->protocol_type = DBAL_ENUM_FVAL_PROTOCOL_TYPE_L2CP;
            dbal_key_p->trap_args = key_p->trap_args;
            break;
        case bcmRxTrapIcmpRedirect:
            *protocol_dbal_table_p = DBAL_TABLE_PROTOCOL_ICMP_TRAP_ACTION_PROFILE;
            dbal_key_p->protocol_type = DBAL_ENUM_FVAL_PROTOCOL_TYPE_ICMP;
            SHR_IF_ERR_EXIT(dnx_rx_trap_icmp_compressed_type_hw_get(unit, key_p->trap_args, &dbal_key_p->trap_args));
            break;
        case bcmRxTrap8021xFail:
            *protocol_dbal_table_p = DBAL_TABLE_PROTOCOL_8021X_TRAP_ACTION_PROFILE;
            dbal_key_p->protocol_type = DBAL_ENUM_FVAL_PROTOCOL_TYPE_NON_AUTH_8021x;
            dbal_key_p->trap_args = 0;
            break;
        case bcmRxTrapIgmpMembershipQuery:
        case bcmRxTrapIgmpReportLeaveMsg:
        case bcmRxTrapIgmpUndefined:
            *protocol_dbal_table_p = DBAL_TABLE_PROTOCOL_IGMP_TRAP_ACTION_PROFILE;
            dbal_key_p->protocol_type = DBAL_ENUM_FVAL_PROTOCOL_TYPE_IGMP;
            dbal_key_p->trap_args = key_p->protocol_type - bcmRxTrapIgmpMembershipQuery;
            break;
        case bcmRxTrapDhcpv4Client:
            *protocol_dbal_table_p = DBAL_TABLE_PROTOCOL_DHCP_TRAP_ACTION_PROFILE;
            dbal_key_p->protocol_type = DBAL_ENUM_FVAL_PROTOCOL_TYPE_DHCP;
            dbal_key_p->trap_args = DNX_RX_TRAP_PROTOCOL_DHCP_ARGS_IPV4_CLIENT;
            break;
        case bcmRxTrapDhcpv4Server:
            *protocol_dbal_table_p = DBAL_TABLE_PROTOCOL_DHCP_TRAP_ACTION_PROFILE;
            dbal_key_p->protocol_type = DBAL_ENUM_FVAL_PROTOCOL_TYPE_DHCP;
            dbal_key_p->trap_args = DNX_RX_TRAP_PROTOCOL_DHCP_ARGS_IPV4_SERVER;
            break;
        case bcmRxTrapDhcpv6Client:
            *protocol_dbal_table_p = DBAL_TABLE_PROTOCOL_DHCP_TRAP_ACTION_PROFILE;
            dbal_key_p->protocol_type = DBAL_ENUM_FVAL_PROTOCOL_TYPE_DHCP;
            dbal_key_p->trap_args = DNX_RX_TRAP_PROTOCOL_DHCP_ARGS_IPV6_CLIENT;
            break;
        case bcmRxTrapDhcpv6Server:
            *protocol_dbal_table_p = DBAL_TABLE_PROTOCOL_DHCP_TRAP_ACTION_PROFILE;
            dbal_key_p->protocol_type = DBAL_ENUM_FVAL_PROTOCOL_TYPE_DHCP;
            dbal_key_p->trap_args = DNX_RX_TRAP_PROTOCOL_DHCP_ARGS_IPV6_SERVER;
            break;
        case bcmRxTrapArp:
            *protocol_dbal_table_p = DBAL_TABLE_PROTOCOL_ARP_NDP_TRAP_ACTION_PROFILE;
            dbal_key_p->protocol_type = DBAL_ENUM_FVAL_PROTOCOL_TYPE_ARP;
            dbal_key_p->trap_args = DNX_RX_TRAP_PROTOCOL_ARP_ARGS;
            break;
        case bcmRxTrapArpMyIp:
            *protocol_dbal_table_p = DBAL_TABLE_PROTOCOL_ARP_NDP_TRAP_ACTION_PROFILE;
            dbal_key_p->protocol_type = DBAL_ENUM_FVAL_PROTOCOL_TYPE_ARP;
            dbal_key_p->trap_args = DNX_RX_TRAP_PROTOCOL_MY_ARP_ARGS;
            break;
        case bcmRxTrapNdp:
            *protocol_dbal_table_p = DBAL_TABLE_PROTOCOL_ARP_NDP_TRAP_ACTION_PROFILE;
            dbal_key_p->protocol_type = DBAL_ENUM_FVAL_PROTOCOL_TYPE_NDP;
            dbal_key_p->trap_args = DNX_RX_TRAP_PROTOCOL_NDP_ARGS;
            break;
        case bcmRxTrapNdpMyIp:
            *protocol_dbal_table_p = DBAL_TABLE_PROTOCOL_ARP_NDP_TRAP_ACTION_PROFILE;
            dbal_key_p->protocol_type = DBAL_ENUM_FVAL_PROTOCOL_TYPE_NDP;
            dbal_key_p->trap_args = DNX_RX_TRAP_PROTOCOL_MY_NDP_ARGS;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_CONFIG, "Invalid protocol type\n");
            break;
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set the trap action profile: trap stregnth and action.
* \par DIRECT INPUT:
*   \param [in] unit     -  unit id
*   \param [in] key_p   -  protocol trap key parameters \n
*               \b As \b input - \n
*               Pointer contains protocol type, protocol arguments and trap profile
*   \param [in] trap_gport    -  gport encoding trap action profile
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
bcm_dnx_rx_trap_protocol_set(
    int unit,
    bcm_rx_trap_protocol_key_t * key_p,
    bcm_gport_t trap_gport)
{
    dnx_rx_trap_protocol_config_t config;
    dbal_tables_e protocol_dbal_table = DBAL_TABLE_EMPTY;
    bcm_rx_trap_protocol_key_t dbal_key;
    int trap_id_encoded;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    SHR_NULL_CHECK(key_p, _SHR_E_PARAM, "key_p");
    SHR_INVOKE_VERIFY_DNXC(dnx_rx_trap_protocol_key_verify(unit, key_p));

    if (key_p->protocol_type == bcmRxTrapIcmpRedirect)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_icmp_type_compressed_set(unit, key_p));
    }
    SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_dbal_info_get(unit, key_p, &protocol_dbal_table, &dbal_key));

    trap_id_encoded = BCM_GPORT_TRAP_GET_ID(trap_gport);
    config.trap_id = DNX_RX_TRAP_ID_TYPE_GET(trap_id_encoded);
    config.fwd_strength = BCM_GPORT_TRAP_GET_STRENGTH(trap_gport);
    config.snp_strength = BCM_GPORT_TRAP_GET_SNOOP_STRENGTH(trap_gport);

    SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_action_profile_hw_set(unit, protocol_dbal_table, &dbal_key, &config));

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Returns if the ICMP argument is the last one allocated or
*   there are more than 1 profile configured to it.
* \par DIRECT INPUT:
*   \param [in] unit     -  unit Id
*   \param [in] key_p   -  protocol trap key parameters \n
*               \b As \b input - \n
*               Pointer contains protocol type, protocol arguments and trap profile
*   \param [out] is_last    -  is this the last ICMP arg allocated.
*               \b As \b output - \n
*               Encoding trap action profile
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
dnx_rx_trap_protocol_icmp_is_last(
    int unit,
    bcm_rx_trap_protocol_key_t * key_p,
    uint8 *is_last)
{
    dnx_rx_trap_protocol_config_t config = { 0 };
    dbal_tables_e protocol_dbal_table = DBAL_TABLE_EMPTY;
    bcm_rx_trap_protocol_key_t dbal_key;
    int nof_references = 0, protocol_profile;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(key_p, _SHR_E_PARAM, "key_p");
    SHR_INVOKE_VERIFY_DNXC(dnx_rx_trap_protocol_key_verify(unit, key_p));

    for (protocol_profile = 0; protocol_profile < dnx_data_trap.ingress.nof_protocol_trap_profiles_get(unit);
         protocol_profile++)
    {

        SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_dbal_info_get(unit, key_p, &protocol_dbal_table, &dbal_key));
        dbal_key.protocol_trap_profile = protocol_profile;
        SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_action_profile_hw_get(unit, protocol_dbal_table, &dbal_key, &config));
        if (config.trap_id > 0)
        {
            nof_references++;
        }
    }
    if (nof_references == 1)
    {
        *is_last = TRUE;
    }
    else
    {
        *is_last = FALSE;
    }
exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get configuration of previously created protocol trap
* \par DIRECT INPUT:
*   \param [in] unit     -  unit Id
*   \param [in] key_p   -  protocol trap key parameters \n
*               \b As \b input - \n
*               Pointer contains protocol type, protocol arguments and trap profile
*   \param [out] trap_gport_p    -  trap gport
*               \b As \b output - \n
*               Encoding trap action profile
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
bcm_dnx_rx_trap_protocol_get(
    int unit,
    bcm_rx_trap_protocol_key_t * key_p,
    bcm_gport_t * trap_gport_p)
{
    dnx_rx_trap_protocol_config_t config = { 0 };
    dbal_tables_e protocol_dbal_table = DBAL_TABLE_EMPTY;
    bcm_rx_trap_protocol_key_t dbal_key;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    SHR_NULL_CHECK(key_p, _SHR_E_PARAM, "key_p");
    SHR_INVOKE_VERIFY_DNXC(dnx_rx_trap_protocol_key_verify(unit, key_p));

    SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_dbal_info_get(unit, key_p, &protocol_dbal_table, &dbal_key));

    SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_action_profile_hw_get(unit, protocol_dbal_table, &dbal_key, &config));

    BCM_GPORT_TRAP_SET(*trap_gport_p, config.trap_id, config.fwd_strength, config.snp_strength);

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Destroy previously created protocol trap, i.e. clear relevanat table entry content
* \par DIRECT INPUT:
*   \param [in] unit     -  unit Id
*   \param [in] key_p   -  protocol trap key parameters \n
*               \b As \b input - \n
*               Pointer contains protocol type, protocol arguments and trap profile
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
bcm_dnx_rx_trap_protocol_clear(
    int unit,
    bcm_rx_trap_protocol_key_t * key_p)
{
    dbal_tables_e protocol_dbal_table = DBAL_TABLE_EMPTY;
    uint8 is_last;
    bcm_rx_trap_protocol_key_t dbal_key;
    int compressed_type;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);
    SHR_NULL_CHECK(key_p, _SHR_E_PARAM, "key_p");
    SHR_INVOKE_VERIFY_DNXC(dnx_rx_trap_protocol_key_verify(unit, key_p));

    SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_icmp_is_last(unit, key_p, &is_last));

    SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_dbal_info_get(unit, key_p, &protocol_dbal_table, &dbal_key));

    if (key_p->protocol_type == bcmRxTrapIcmpRedirect && is_last)
    {
        compressed_type = dbal_key.trap_args;

        SHR_IF_ERR_EXIT(dnx_algo_rx_trap_icmp_compressed_type_deallocate(unit, compressed_type));
    }
    SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_action_profile_hw_clear(unit, protocol_dbal_table, &dbal_key));

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function purpose is to set protocol trap profiles in HW
* \par DIRECT INPUT:
*   \param [in] unit      -  unit Id
*   \param [in] port - In-PP-Port
*   \param [in] core_id - core id
*   \param [in] protocol_profiles_p  -  protocol trap profiles struct, holds the trap profiles of each protocol
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_protocol_profiles_hw_set(
    int unit,
    bcm_gport_t port,
    uint32 core_id,
    bcm_rx_trap_protocol_profiles_t * protocol_profiles_p)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(protocol_profiles_p, _SHR_E_PARAM, "protocol_profiles_p");

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PROTOCOL_TRAP_HANDLING_PROFILE, &entry_handle_id));

    /*
     * key construction - In-PP-Port & Core
     */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_PP_PORT, port);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);

    /*
     * Set trap profiles
     */
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_ICMPV6_TRAP_HANDLING_PROFILE, INST_SINGLE,
                                protocol_profiles_p->icmpv6_trap_profile);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_ICMPV4_TRAP_HANDLING_PROFILE, INST_SINGLE,
                                protocol_profiles_p->icmpv4_trap_profile);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_L_2_CP_TRAP_HANDLING_PROFILE, INST_SINGLE,
                                protocol_profiles_p->l2cp_trap_profile);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_ARP_TRAP_HANDLING_PROFILE, INST_SINGLE,
                                protocol_profiles_p->arp_trap_profile);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_IGMP_TRAP_HANDLING_PROFILE, INST_SINGLE,
                                protocol_profiles_p->igmp_trap_profile);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_DHCP_TRAP_HANDLING_PROFILE, INST_SINGLE,
                                protocol_profiles_p->dhcp_trap_profile);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_NON_AUTH_8021X_TRAP_HANDLING_PROFILE, INST_SINGLE,
                                protocol_profiles_p->non_auth_8021x_trap_profile);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function purpose is to set protocol trap profiles in HW
* \par DIRECT INPUT:
*   \param [in] unit      -  unit Id
*   \param [in] port  - In-PP-Port
*   \param [in] core_id  - Core id
*   \param [out] protocol_profiles_p  -  protocol trap profiles struct, holds the trap profiles of each protocol
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_protocol_profiles_hw_get(
    int unit,
    bcm_gport_t port,
    uint32 core_id,
    bcm_rx_trap_protocol_profiles_t * protocol_profiles_p)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(protocol_profiles_p, _SHR_E_PARAM, "protocol_profiles_p");

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PROTOCOL_TRAP_HANDLING_PROFILE, &entry_handle_id));

    /*
     * key construction - In-PP-Port & Core-id
     */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_PP_PORT, port);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);

    /*
     * Set trap profiles
     */
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_ICMPV6_TRAP_HANDLING_PROFILE, INST_SINGLE,
                              &protocol_profiles_p->icmpv6_trap_profile);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_ICMPV4_TRAP_HANDLING_PROFILE, INST_SINGLE,
                              &protocol_profiles_p->icmpv4_trap_profile);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_L_2_CP_TRAP_HANDLING_PROFILE, INST_SINGLE,
                              &protocol_profiles_p->l2cp_trap_profile);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_ARP_TRAP_HANDLING_PROFILE, INST_SINGLE,
                              &protocol_profiles_p->arp_trap_profile);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_IGMP_TRAP_HANDLING_PROFILE, INST_SINGLE,
                              &protocol_profiles_p->igmp_trap_profile);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_DHCP_TRAP_HANDLING_PROFILE, INST_SINGLE,
                              &protocol_profiles_p->dhcp_trap_profile);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_NON_AUTH_8021X_TRAP_HANDLING_PROFILE, INST_SINGLE,
                              &protocol_profiles_p->non_auth_8021x_trap_profile);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function purpose is to verify the parameters supplied to
*  dnx_rx_trap_protocol_profiles_set
* \par DIRECT INPUT:
*   \param [in] unit      -  unit Id
*   \param [in] port  - either In-PP-Port or gport for InLIF
*   \param [in] protocol_profiles_p  -  protocol trap profiles struct
*               \b As \b input - \n
*               Pointer contains the trap profiles of each protocol
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_protocol_profiles_set_verify(
    int unit,
    bcm_gport_t port,
    bcm_rx_trap_protocol_profiles_t * protocol_profiles_p)
{
    uint8 protocol_trap_profiles_nof;
    uint8 protocol_trap_mode;
    SHR_FUNC_INIT_VARS(unit);
    protocol_trap_mode = dnx_data_trap.ingress.protocol_traps_init_mode_get(unit);
    protocol_trap_profiles_nof = dnx_data_trap.ingress.nof_protocol_trap_profiles_get(unit);

    if (protocol_trap_mode == DNX_RX_TRAP_PROTOCOL_MODE_IN_LIF)
    {
        if (!BCM_GPORT_IS_SET(port))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Protocol trap mode is IN-LIF, please use a valid In-LIF. \n");
        }
    }
    else if (protocol_trap_mode == DNX_RX_TRAP_PROTOCOL_MODE_IN_PORT)
    {
        if (BCM_GPORT_IS_SET(port) && !BCM_GPORT_IS_TRUNK(port))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Protocol trap mode is IN-PORT, please use a valid In-Port. \n");
        }
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_CONFIG, "Protocol trap mode SOC property is set with an un-supported mode type. \n");
    }

    if (protocol_profiles_p->arp_trap_profile >= protocol_trap_profiles_nof ||
        protocol_profiles_p->dhcp_trap_profile >= protocol_trap_profiles_nof ||
        protocol_profiles_p->icmpv4_trap_profile >= protocol_trap_profiles_nof ||
        protocol_profiles_p->icmpv6_trap_profile >= protocol_trap_profiles_nof ||
        protocol_profiles_p->igmp_trap_profile >= protocol_trap_profiles_nof ||
        protocol_profiles_p->l2cp_trap_profile >= protocol_trap_profiles_nof ||
        protocol_profiles_p->non_auth_8021x_trap_profile >= protocol_trap_profiles_nof)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Protocol trap profile must be between 0-3 ! \n");
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function purpose is to set the protocol trap profiles for inlif
* \par DIRECT INPUT:
*   \param [in] unit      -  unit Id
*   \param [in] gport     -  gport to set
*   \param [in] intf_type -  interface type
*   \param [in] inlif_dbal_table_id - inlif dbal table to configure
*   \param [in] protocol_profiles  -  protocol trap profiles struct
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_protocol_in_lif_profile_set(
    int unit,
    bcm_port_t gport,
    in_lif_intf_type_e intf_type,
    dbal_tables_e inlif_dbal_table_id,
    bcm_rx_trap_protocol_profiles_t protocol_profiles)
{
    in_lif_profile_info_t in_lif_profile_info;
    int old_in_lif_profile, new_in_lif_profile;
    uint32 result_type;
    dnx_in_lif_profile_last_info_t last_profile;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);
    dnx_in_lif_profile_last_info_t_init(&last_profile);
    SHR_IF_ERR_EXIT(dnx_in_lif_vsi_profile_get(unit, gport, (uint32 *) &old_in_lif_profile, &result_type, intf_type));
    SHR_IF_ERR_EXIT(in_lif_profile_info_t_init(unit, &in_lif_profile_info));
    /** Set also the lif_gport for devices supporting stage based cs_in_lif_profile in ordder to recover the correct namespace */
    if (dnx_data_lif.in_lif.feature_get(unit, dnx_data_lif_in_lif_cs_in_lif_profile_based_on_stages)
        && (intf_type == LIF))
    {
        SHR_IF_ERR_EXIT(algo_gpm_gport_flow_convert(unit, gport, BCM_GPORT_TYPE_FLOW_LIF,
                                                    DNX_ALGO_GPM_CONVERSION_FLAG_FLOW_TERMINATOR,
                                                    &in_lif_profile_info.ingress_fields.lif_gport));
    }
    else if (dnx_data_lif.in_lif.feature_get(unit, dnx_data_lif_in_lif_cs_in_lif_profile_based_on_stages)
             && (intf_type == ETH_RIF))
    {
        in_lif_profile_info.ingress_fields.lif_gport = BCM_L3_ITF_VAL_GET(gport);
    }
    SHR_IF_ERR_EXIT(dnx_in_lif_profile_get_data
                    (unit, old_in_lif_profile, &in_lif_profile_info, inlif_dbal_table_id, intf_type));
    sal_memcpy(&in_lif_profile_info.ingress_fields.protocol_trap_profiles, &protocol_profiles,
               sizeof(bcm_rx_trap_protocol_profiles_t));
    SHR_IF_ERR_EXIT(dnx_in_lif_profile_exchange
                    (unit, &in_lif_profile_info, old_in_lif_profile, &new_in_lif_profile, intf_type,
                     inlif_dbal_table_id, &last_profile));
    SHR_IF_ERR_EXIT(dnx_in_lif_vsi_profile_set(unit, gport, new_in_lif_profile, result_type, intf_type));
    SHR_IF_ERR_EXIT(dnx_in_lif_profile_destroy(unit, last_profile, intf_type));

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function purpose is to set protocol trap profiles
* \par DIRECT INPUT:
*   \param [in] unit      -  unit Id
*   \param [in] port  - either In-PP-Port or gport for InLIF
*   \param [in] protocol_profiles_p  -  protocol trap profiles struct
*               \b As \b input - \n
*               Pointer contains the trap profiles of each protocol
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
bcm_dnx_rx_trap_protocol_profiles_set(
    int unit,
    bcm_gport_t port,
    bcm_rx_trap_protocol_profiles_t * protocol_profiles_p)
{
    uint8 protocol_trap_mode;
    int pp_port;
    dnx_algo_gpm_gport_phy_info_t gport_info;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);
    SHR_NULL_CHECK(protocol_profiles_p, _SHR_E_PARAM, "protocol_profiles_p");
    protocol_trap_mode = dnx_data_trap.ingress.protocol_traps_init_mode_get(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_profiles_set_verify(unit, port, protocol_profiles_p));

    if (protocol_trap_mode == DNX_RX_TRAP_PROTOCOL_MODE_IN_LIF)
    {
        bcm_gport_t resources_gport = port;
        dnx_algo_gpm_gport_hw_resources_t gport_hw_resources;

        if (dnx_data_lif.in_lif.feature_get(unit, dnx_data_lif_in_lif_cs_in_lif_profile_based_on_stages))
        {
            SHR_IF_ERR_EXIT(algo_gpm_gport_flow_convert
                            (unit, port, BCM_GPORT_TYPE_FLOW_LIF,
                             DNX_ALGO_GPM_CONVERSION_FLAG_FLOW_TERMINATOR, &resources_gport));
        }

        SHR_IF_ERR_REPLACE_AND_EXIT(dnx_algo_gpm_gport_to_hw_resources
                                    (unit, resources_gport, DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_INGRESS,
                                     &gport_hw_resources), _SHR_E_NOT_FOUND, _SHR_E_PARAM);

        SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_in_lif_profile_set
                        (unit, resources_gport, LIF, gport_hw_resources.inlif_dbal_table_id, *protocol_profiles_p));
    }
    else if (protocol_trap_mode == DNX_RX_TRAP_PROTOCOL_MODE_IN_PORT)
    {
        SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get
                        (unit, port, DNX_ALGO_GPM_GPORT_TO_PHY_OP_PP_PORT_IS_MANDATORY, &gport_info));
        for (pp_port = 0; pp_port < gport_info.internal_port_pp_info.nof_pp_ports; pp_port++)
        {
            SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_profiles_hw_set
                            (unit, gport_info.internal_port_pp_info.pp_port[pp_port],
                             gport_info.internal_port_pp_info.core_id[pp_port], protocol_profiles_p));
        }
    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function purpose is to verify the parameters supplied to
*  dnx_rx_trap_protocol_profiles_get.
* \par DIRECT INPUT:
*   \param [in] unit      -  unit Id
*   \param [in] port  - either In-PP-Port or gport for InLIF
*   \param [out] protocol_profiles_p  -  protocol trap profiles struct
*               \b As \b output - \n
*               Pointer contains the trap profiles of each protocol
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_protocol_profiles_get_verify(
    int unit,
    bcm_gport_t port,
    bcm_rx_trap_protocol_profiles_t * protocol_profiles_p)
{
    uint8 protocol_trap_mode;
    SHR_FUNC_INIT_VARS(unit);
    protocol_trap_mode = dnx_data_trap.ingress.protocol_traps_init_mode_get(unit);

    if (protocol_trap_mode == DNX_RX_TRAP_PROTOCOL_MODE_IN_LIF)
    {
        if (!BCM_GPORT_IS_SET(port))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Protocol trap mode is IN-LIF, please use a valid In-LIF. \n");
        }
    }
    else if (protocol_trap_mode == DNX_RX_TRAP_PROTOCOL_MODE_IN_PORT)
    {
        if (BCM_GPORT_IS_SET(port) && !BCM_GPORT_IS_TRUNK(port))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Protocol trap mode is IN-PORT, please use a valid In-Port. \n");
        }
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_CONFIG, "Protocol trap mode SOC property is set with an un-supported mode type. \n");
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function purpose is to get the protocol trap profiles for inlif
* \par DIRECT INPUT:
*   \param [in] unit      -  unit Id
*   \param [in] gport     -  gport to set
*   \param [in] intf_type -  interface type
*   \param [out] protocol_profiles_p  -  protocol trap profiles struct
*               \b As \b input - \n
*               Pointer contains the protocol trap profiles
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_protocol_in_lif_profile_get(
    int unit,
    bcm_port_t gport,
    in_lif_intf_type_e intf_type,
    bcm_rx_trap_protocol_profiles_t * protocol_profiles_p)
{
    in_lif_profile_info_t in_lif_profile_info;
    int in_lif_profile;
    uint32 result_type;
    bcm_gport_t resources_gport = gport;
    dbal_tables_e inlif_dbal_table_id;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    if (intf_type == ETH_RIF)
    {
        inlif_dbal_table_id = DBAL_TABLE_ING_VSI_INFO_DB;
    }
    else
    {
        dnx_algo_gpm_gport_hw_resources_t gport_hw_resources;

        if (dnx_data_lif.in_lif.feature_get(unit, dnx_data_lif_in_lif_cs_in_lif_profile_based_on_stages))
        {
            SHR_IF_ERR_EXIT(algo_gpm_gport_flow_convert
                            (unit, gport, BCM_GPORT_TYPE_FLOW_LIF,
                             DNX_ALGO_GPM_CONVERSION_FLAG_FLOW_TERMINATOR, &resources_gport));
        }

        SHR_IF_ERR_REPLACE_AND_EXIT(dnx_algo_gpm_gport_to_hw_resources
                                    (unit, resources_gport, DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_INGRESS,
                                     &gport_hw_resources), _SHR_E_NOT_FOUND, _SHR_E_PARAM);

        inlif_dbal_table_id = gport_hw_resources.inlif_dbal_table_id;
    }

    SHR_IF_ERR_EXIT(dnx_in_lif_vsi_profile_get
                    (unit, resources_gport, (uint32 *) &in_lif_profile, &result_type, intf_type));

    SHR_IF_ERR_EXIT(in_lif_profile_info_t_init(unit, &in_lif_profile_info));
    SHR_IF_ERR_EXIT(dnx_in_lif_profile_get_data
                    (unit, in_lif_profile, &in_lif_profile_info, inlif_dbal_table_id, intf_type));

    sal_memcpy(protocol_profiles_p, &in_lif_profile_info.ingress_fields.protocol_trap_profiles,
               sizeof(bcm_rx_trap_protocol_profiles_t));

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function purpose is to get protocol trap profiles configuration
* \par DIRECT INPUT:
*   \param [in] unit      -  unit Id
*   \param [in] port  - either In-PP-Port or gport for InLIF
*   \param [out] protocol_profiles_p  -  protocol trap profiles struct
*               \b As \b output - \n
*               Pointer contains the trap profiles of each protocol
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
bcm_dnx_rx_trap_protocol_profiles_get(
    int unit,
    bcm_gport_t port,
    bcm_rx_trap_protocol_profiles_t * protocol_profiles_p)
{
    uint8 protocol_trap_mode;
    dnx_algo_gpm_gport_phy_info_t gport_info;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);
    SHR_NULL_CHECK(protocol_profiles_p, _SHR_E_PARAM, "protocol_profiles_p");
    protocol_trap_mode = dnx_data_trap.ingress.protocol_traps_init_mode_get(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_profiles_get_verify(unit, port, protocol_profiles_p));

    if (protocol_trap_mode == DNX_RX_TRAP_PROTOCOL_MODE_IN_LIF)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_in_lif_profile_get(unit, port, LIF, protocol_profiles_p));
    }
    else if (protocol_trap_mode == DNX_RX_TRAP_PROTOCOL_MODE_IN_PORT)
    {
        SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get
                        (unit, port, DNX_ALGO_GPM_GPORT_TO_PHY_OP_PP_PORT_IS_MANDATORY, &gport_info));
        SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_profiles_hw_get
                        (unit, gport_info.internal_port_pp_info.pp_port[0], gport_info.internal_port_pp_info.core_id[0],
                         protocol_profiles_p));
    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
 * See rx_trap.h
 */
shr_error_e
dnx_rx_trap_protocol_my_ndp_set(
    int unit,
    int word_index,
    dnx_rx_trap_protocol_my_arp_ndp_config_t * config_p)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PROTOCOL_TRAP_MY_NDP, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_WORD_INDEX, word_index);
    /*
     * Set the values
     */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IP_1, INST_SINGLE, config_p->ip_1);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IP_2, INST_SINGLE, config_p->ip_2);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * See rx_trap.h
 */
shr_error_e
dnx_rx_trap_protocol_my_arp_set(
    int unit,
    dnx_rx_trap_protocol_my_arp_ndp_config_t * config_p)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (DNX_RX_TRAP_IS_BOOL_INDICATION(config_p->ignore_da) == FALSE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "ignore_da should be of value FALSE(0) or TRUE(1) only!");
    }

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PROTOCOL_TRAP_MY_ARP, &entry_handle_id));
    /*
     * Set the values
     */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IP_1, INST_SINGLE, config_p->ip_1);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IP_2, INST_SINGLE, config_p->ip_2);

    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_IGNORE_DA, INST_SINGLE, config_p->ignore_da);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * See rx_trap.h
 */
shr_error_e
dnx_rx_trap_protocol_my_ndp_get(
    int unit,
    int word_index,
    dnx_rx_trap_protocol_my_arp_ndp_config_t * config_p)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_ndp_trap_en) == FALSE)
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Function is not supported for the current device!");
    }

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PROTOCOL_TRAP_MY_NDP, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_WORD_INDEX, word_index);
    /*
     * Get the values
     */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_IP_1, INST_SINGLE, &config_p->ip_1);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_IP_2, INST_SINGLE, &config_p->ip_2);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * See rx_trap.h
 */
shr_error_e
dnx_rx_trap_protocol_my_arp_get(
    int unit,
    dnx_rx_trap_protocol_my_arp_ndp_config_t * config_p)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PROTOCOL_TRAP_MY_ARP, &entry_handle_id));

    /*
     * Get the values
     */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_IP_1, INST_SINGLE, &config_p->ip_1);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_IP_2, INST_SINGLE, &config_p->ip_2);

    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_IGNORE_DA, INST_SINGLE, &config_p->ignore_da);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 *  See rx_trap.h for info
 */
shr_error_e
dnx_rx_trap_protocol_icmp_ignore_da_hw_set(
    int unit,
    int enable)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (enable > TRUE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The supplied argument %d is too big, only TRUE/FALSE is allowed", enable);
    }

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ICMP_TRAP_CFG, &entry_handle_id));
    /*
     * Set the value
     */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ICMP_TRAP_IGNORE_DA, INST_SINGLE, enable);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 *  See rx_trap.h for info
 */
shr_error_e
dnx_rx_trap_protocol_icmp_ignore_da_hw_get(
    int unit,
    int *enable)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ICMP_TRAP_CFG, &entry_handle_id));

    /*
     * Gets the value
     */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_ICMP_TRAP_IGNORE_DA, INST_SINGLE, (uint32 *) enable);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Writes the Programmable trap configuration to the DBAL.
* \par DIRECT INPUT:
*   \param [in] unit            - unit Id
*   \param [in] prog_index      - Programmable Trap ID
*   \param [in] prog_config_p   - Programmable Trap configuration
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_prog_hw_set(
    int unit,
    uint8 prog_index,
    bcm_rx_trap_prog_config_t * prog_config_p)
{

    uint32 entry_handle_id;
    int ingress_trap_id, trap_id_encoded;
    int trap_strength;
    int snoop_strength;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(prog_config_p, _SHR_E_PARAM, "prog_config_p");

    trap_id_encoded = BCM_GPORT_TRAP_GET_ID(prog_config_p->trap_gport);
    ingress_trap_id = DNX_RX_TRAP_ID_TYPE_GET(trap_id_encoded);
    trap_strength = BCM_GPORT_TRAP_GET_STRENGTH(prog_config_p->trap_gport);
    snoop_strength = BCM_GPORT_TRAP_GET_SNOOP_STRENGTH(prog_config_p->trap_gport);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_PROG, &entry_handle_id));

    /*
     * key construction - In-PP-Port
     */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROG_PROFILE, prog_index);

    /*
     * Set trap profiles
     */
    dbal_entry_value_field_arr8_set(unit, entry_handle_id, DBAL_FIELD_L2_DA, INST_SINGLE, prog_config_p->dest_mac);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_DA_BITS, INST_SINGLE,
                                prog_config_p->dest_mac_nof_bits);
    dbal_entry_value_field_arr8_set(unit, entry_handle_id, DBAL_FIELD_L2_SA, INST_SINGLE, prog_config_p->src_mac);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_SA_BITS, INST_SINGLE,
                                prog_config_p->src_mac_nof_bits);
    dbal_entry_value_field16_set(unit, entry_handle_id, DBAL_FIELD_ETHER_TYPE, INST_SINGLE, prog_config_p->ether_type);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_SUB_TYPE, INST_SINGLE, prog_config_p->sub_type);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_SUB_TYPE_MASK, INST_SINGLE,
                                prog_config_p->sub_type_mask);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_IP_PROTOCOL, INST_SINGLE, prog_config_p->ip_protocol);
    dbal_entry_value_field16_set(unit, entry_handle_id, DBAL_FIELD_SRC_PORT, INST_SINGLE, prog_config_p->src_port);
    dbal_entry_value_field16_set(unit, entry_handle_id, DBAL_FIELD_SRC_PORT_MASK, INST_SINGLE,
                                 prog_config_p->src_port_mask);
    dbal_entry_value_field16_set(unit, entry_handle_id, DBAL_FIELD_DEST_PORT, INST_SINGLE, prog_config_p->dest_port);
    dbal_entry_value_field16_set(unit, entry_handle_id, DBAL_FIELD_DEST_PORT_MASK, INST_SINGLE,
                                 prog_config_p->dest_port_mask);
    dbal_entry_value_field16_set(unit, entry_handle_id, DBAL_FIELD_TCP_FLAGS, INST_SINGLE, prog_config_p->tcp_flags);
    dbal_entry_value_field16_set(unit, entry_handle_id, DBAL_FIELD_TCP_FLAGS_MASK, INST_SINGLE,
                                 prog_config_p->tcp_flags_mask);
    dbal_entry_value_field16_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, INST_SINGLE, ingress_trap_id);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_FWD_STRENGTH, INST_SINGLE, trap_strength);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_SNP_STRENGTH, INST_SINGLE, snoop_strength);
    /*
     * The mapping for the enable bits(bitmaps) is done in the DBAL logic.
     * We created and set info in the designated DBAL fields for each enable field,
     * the DBAL maps and writes to the bitmap register fields, in the appropriate places.
     */
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_SA_ENABLE, INST_SINGLE,
                                prog_config_p->src_mac_enable);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_DA_ENABLE, INST_SINGLE,
                                prog_config_p->dest_mac_enable);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_ETHER_TYPE_ENABLE, INST_SINGLE,
                                prog_config_p->ether_type_enable);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_SUB_TYPE_ENABLE, INST_SINGLE,
                                prog_config_p->sub_type_enable);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_IP_PROTOCOL_ENABLE, INST_SINGLE,
                                prog_config_p->ip_protocol_enable);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_PORTS_ENABLE, INST_SINGLE,
                                prog_config_p->l4_ports_enable);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_TCP_FLAGS_ENABLE, INST_SINGLE,
                                prog_config_p->tcp_flags_enable);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_TCP_SEQ_ENABLE, INST_SINGLE,
                                prog_config_p->tcp_seq_is_zero_enable);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;

}

/**
* \brief
*  Writes the Programmable trap configuration to the DBAL.
* \par DIRECT INPUT:
*   \param [in] unit            - unit Id
*   \param [in] prog_index      - Programmable Trap ID
*   \param [out] prog_config_p  - Programmable Trap configuration
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_prog_hw_get(
    int unit,
    uint8 prog_index,
    bcm_rx_trap_prog_config_t * prog_config_p)
{

    uint32 entry_handle_id;
    uint16 ingress_trap_id, src_port, dest_port;
    uint8 trap_strength;
    uint8 snoop_strength;
    uint8 src_mac_enable, dest_mac_enable, ether_type_enable, sub_type_enable,
        ip_protocol_enable, l4_ports_enable, tcp_flags_enable, tcp_seq_is_zero_enable;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(prog_config_p, _SHR_E_PARAM, "prog_config_p");

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_PROG, &entry_handle_id));

    /*
     * key construction - In-PP-Port
     */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PROG_PROFILE, prog_index);

    /*
     * Set trap profiles
     */
    dbal_value_field_arr8_request(unit, entry_handle_id, DBAL_FIELD_L2_DA, INST_SINGLE,
                                  (uint8 *) &(prog_config_p->dest_mac));
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_DA_BITS, INST_SINGLE,
                              (uint8 *) &(prog_config_p->dest_mac_nof_bits));
    dbal_value_field_arr8_request(unit, entry_handle_id, DBAL_FIELD_L2_SA, INST_SINGLE,
                                  (uint8 *) &(prog_config_p->src_mac));
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_SA_BITS, INST_SINGLE,
                              (uint8 *) &(prog_config_p->src_mac_nof_bits));
    dbal_value_field16_request(unit, entry_handle_id, DBAL_FIELD_ETHER_TYPE, INST_SINGLE,
                               (uint16 *) &(prog_config_p->ether_type));
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_SUB_TYPE, INST_SINGLE,
                              (uint8 *) &(prog_config_p->sub_type));
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_SUB_TYPE_MASK, INST_SINGLE,
                              (uint8 *) &(prog_config_p->sub_type_mask));
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_IP_PROTOCOL, INST_SINGLE,
                              (uint8 *) &(prog_config_p->ip_protocol));
    dbal_value_field16_request(unit, entry_handle_id, DBAL_FIELD_SRC_PORT, INST_SINGLE, (uint16 *) &src_port);
    dbal_value_field16_request(unit, entry_handle_id, DBAL_FIELD_SRC_PORT_MASK, INST_SINGLE,
                               (uint16 *) &(prog_config_p->src_port_mask));
    dbal_value_field16_request(unit, entry_handle_id, DBAL_FIELD_DEST_PORT, INST_SINGLE, (uint16 *) &dest_port);
    dbal_value_field16_request(unit, entry_handle_id, DBAL_FIELD_DEST_PORT_MASK, INST_SINGLE,
                               (uint16 *) &(prog_config_p->dest_port_mask));
    dbal_value_field16_request(unit, entry_handle_id, DBAL_FIELD_TCP_FLAGS, INST_SINGLE,
                               (uint16 *) &(prog_config_p->tcp_flags));
    dbal_value_field16_request(unit, entry_handle_id, DBAL_FIELD_TCP_FLAGS_MASK, INST_SINGLE,
                               (uint16 *) &(prog_config_p->tcp_flags_mask));
    dbal_value_field16_request(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, INST_SINGLE, &ingress_trap_id);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_FWD_STRENGTH, INST_SINGLE, &trap_strength);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_SNP_STRENGTH, INST_SINGLE, &snoop_strength);
    /*
     * The mapping for the enable bits(bitmaps) is done in the DBAL logic.
     * We created and set info in the designated DBAL fields for each enable field,
     * the DBAL maps and writes to the bitmap register fields, in the appropriate places.
     */
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_SA_ENABLE, INST_SINGLE, &src_mac_enable);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_DA_ENABLE, INST_SINGLE, &dest_mac_enable);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_ETHER_TYPE_ENABLE, INST_SINGLE, &ether_type_enable);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_SUB_TYPE_ENABLE, INST_SINGLE, &sub_type_enable);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_IP_PROTOCOL_ENABLE, INST_SINGLE, &ip_protocol_enable);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_PORTS_ENABLE, INST_SINGLE, &l4_ports_enable);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_TCP_FLAGS_ENABLE, INST_SINGLE, &tcp_flags_enable);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_TCP_SEQ_ENABLE, INST_SINGLE, &tcp_seq_is_zero_enable);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

    prog_config_p->src_mac_enable = src_mac_enable;
    prog_config_p->dest_mac_enable = dest_mac_enable;
    prog_config_p->ether_type_enable = ether_type_enable;
    prog_config_p->sub_type_enable = sub_type_enable;
    prog_config_p->ip_protocol_enable = ip_protocol_enable;
    prog_config_p->l4_ports_enable = l4_ports_enable;
    prog_config_p->tcp_flags_enable = tcp_flags_enable;
    prog_config_p->tcp_seq_is_zero_enable = tcp_seq_is_zero_enable;

    prog_config_p->src_port = src_port;
    prog_config_p->dest_port = dest_port;

    /** Encode/set the gport with the values we get from HW */
    BCM_GPORT_TRAP_SET(prog_config_p->trap_gport, ingress_trap_id, trap_strength, snoop_strength);

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;

}

/**
* \brief
*  Basic verification for the input parameters of dnx_rx_trap_prog_set/get
*
* \par DIRECT INPUT:
*   \param [in] unit              - Unit Id
*   \param [in] prog_index     - programmable trap index (0-7)
*   \param [in] prog_config_p - programmable trap configuration
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_prog_basic_verify(
    int unit,
    uint8 prog_index,
    bcm_rx_trap_prog_config_t * prog_config_p)
{
    int nof_prog_traps = dnx_data_trap.ingress.nof_programmable_traps_get(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(prog_config_p, _SHR_E_PARAM, "prog_config_p");

    if (prog_index >= nof_prog_traps)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The Programmable trap index supplied (%d) is out of range! "
                     "The valid range for prog index is 0 - %d.", prog_index, nof_prog_traps - 1);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Verification function for the input parameters of dnx_rx_trap_prog_set()
*
* \par DIRECT INPUT:
*   \param [in] unit              - Unit Id
*   \param [in] flags          - Flags
*   \param [in] prog_index     - programmable trap index (0-7)
*   \param [in] prog_config_p -  programmable trap configuration
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_prog_set_verify(
    int unit,
    int flags,
    uint8 prog_index,
    bcm_rx_trap_prog_config_t * prog_config_p)
{
    int act_profile, fwd_strength, snp_strength;
    uint8 is_allocated;
    bcm_gport_t snoop_gport;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_prog_basic_verify(unit, prog_index, prog_config_p));

    act_profile = BCM_GPORT_TRAP_GET_ID(prog_config_p->trap_gport);
    fwd_strength = BCM_GPORT_TRAP_GET_STRENGTH(prog_config_p->trap_gport);
    snp_strength = BCM_GPORT_TRAP_GET_SNOOP_STRENGTH(prog_config_p->trap_gport);

    if (fwd_strength > 0)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_ingress_is_trap_id_allocated(unit, act_profile, &is_allocated));

        if (is_allocated == FALSE)
        {
            SHR_ERR_EXIT(_SHR_E_NOT_FOUND, "The Trap id (%d) encoded in trap_gport is not allocated! "
                         "Use bcm_rx_trap_type_create() to allocate a forward action profile. \n", act_profile);
        }
    }
    else if (snp_strength > 0)
    {
        BCM_GPORT_MIRROR_SNOOP_SET(snoop_gport, act_profile);
        SHR_IF_ERR_EXIT(dnx_mirror_profile_is_allocated(unit, snoop_gport, &is_allocated));

        if (is_allocated == FALSE)
        {
            SHR_ERR_EXIT(_SHR_E_NOT_FOUND, "The Snoop profile (%d) encoded in trap_gport is not allocated! "
                         "Use bcm_mirror_destination_create() to allocate a snoop action profile. \n", act_profile);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * See rx.h for info
 */
shr_error_e
bcm_dnx_rx_trap_prog_set(
    int unit,
    int flags,
    uint8 prog_index,
    bcm_rx_trap_prog_config_t * prog_config_p)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_prog_set_verify(unit, flags, prog_index, prog_config_p));

    SHR_IF_ERR_EXIT(dnx_rx_trap_prog_hw_set(unit, prog_index, prog_config_p));

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
 * See rx.h for info
 */
shr_error_e
bcm_dnx_rx_trap_prog_get(
    int unit,
    uint8 prog_index,
    bcm_rx_trap_prog_config_t * prog_config_p)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_prog_basic_verify(unit, prog_index, prog_config_p));

    SHR_IF_ERR_EXIT(dnx_rx_trap_prog_hw_get(unit, prog_index, prog_config_p));

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/*
 * See rx_trap.h for more info
 */
shr_error_e
dnx_rx_trap_lif_mtu_profile_hw_set(
    int unit,
    dbal_tables_e dbal_table,
    dbal_fields_e dbal_key_field_type,
    uint32 outlif_dbal_result_type,
    int out_lif,
    int mtu_profile)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, dbal_table, &entry_handle_id));

    /*
     * key construction -Out Lif/Rif
     */
    dbal_entry_key_field32_set(unit, entry_handle_id, dbal_key_field_type, out_lif);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RESULT_TYPE, INST_SINGLE, outlif_dbal_result_type);
    /*
     * Set the MTU profile
     */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_MTU_PROFILE, INST_SINGLE, mtu_profile);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 * See rx_trap.h for more info
 */
shr_error_e
dnx_rx_trap_lif_mtu_profile_hw_get(
    int unit,
    dbal_tables_e dbal_table,
    dbal_fields_e dbal_key_field_type,
    uint32 outlif_dbal_result_type,
    int out_lif,
    int *mtu_profile_p)
{

    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(mtu_profile_p, _SHR_E_PARAM, "mtu_profile_p");

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, dbal_table, &entry_handle_id));

    /*
     * key construction -Out Lif/Rif
     */
    dbal_entry_key_field32_set(unit, entry_handle_id, dbal_key_field_type, out_lif);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RESULT_TYPE, INST_SINGLE, outlif_dbal_result_type);
    /*
     * Set the MTU profile
     */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_MTU_PROFILE, INST_SINGLE, (uint32 *) mtu_profile_p);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function sets the MTU Profile field in the
*  relevant DBAL table for enabling PORT MTU Configuration.
*
* \par DIRECT INPUT:
*   \param [in] unit                 - Unit Id
*   \param [in] mtu_config_p         - MTU Configuration
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_mtu_port_set(
    int unit,
    bcm_rx_mtu_config_t * mtu_config_p)
{
    uint32 entry_handle_id;
    int pp_port;
    dnx_algo_gpm_gport_phy_info_t gport_info;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get
                    (unit, mtu_config_p->gport, DNX_ALGO_GPM_GPORT_TO_PHY_OP_PP_PORT_IS_MANDATORY, &gport_info));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_PP_PORT, &entry_handle_id));
    for (pp_port = 0; pp_port < gport_info.internal_port_pp_info.nof_pp_ports; pp_port++)
    {
        /*
         * key construction - Port
         */
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT,
                                   gport_info.internal_port_pp_info.pp_port[pp_port]);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID,
                                   gport_info.internal_port_pp_info.core_id[pp_port]);

        /*
         * Set the MTU profile
         */
        dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_MTU_PROFILE, INST_SINGLE,
                                    mtu_config_p->mtu_profile);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function sets the MTU Profile field in the
*  relevant DBAL table for enabling LIF MTU Configuration.
*
* \par DIRECT INPUT:
*   \param [in] unit                 - Unit Id
*   \param [in] mtu_config_p         - MTU Configuration
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_mtu_lif_set(
    int unit,
    bcm_rx_mtu_config_t * mtu_config_p)
{
    SHR_FUNC_INIT_VARS(unit);

    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_v1_mtu_lif_set(unit, mtu_config_p));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function sets the MTU Profile field in the
*  relevant DBAL table for enabling RIF MTU Configuration.
*
* \par DIRECT INPUT:
*   \param [in] unit                 - Unit Id
*   \param [in] mtu_config_p         - MTU Configuration
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_mtu_rif_set(
    int unit,
    bcm_rx_mtu_config_t * mtu_config_p)
{
    dnx_algo_gpm_rif_hw_resources_t rif_hw_resources;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_gpm_rif_intf_to_hw_resources(unit, mtu_config_p->intf, &rif_hw_resources));

    SHR_IF_ERR_EXIT(dnx_rx_trap_lif_mtu_profile_hw_set(unit,
                                                       rif_hw_resources.outlif_dbal_table_id,
                                                       DBAL_FIELD_OUT_RIF,
                                                       rif_hw_resources.outlif_dbal_result_type,
                                                       mtu_config_p->intf, mtu_config_p->mtu_profile));
exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Verification function for the input parameters of dnx_rx_mtu_set()
*
* \par DIRECT INPUT:
*   \param [in] unit                 - Unit Id
*   \param [in] mtu_config_p         - MTU Configuration
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_mtu_set_verify(
    int unit,
    bcm_rx_mtu_config_t * mtu_config_p)
{
    int is_fec = 0, is_lif, is_rif, mtu_profile_size = 3;
    dnx_algo_gpm_rif_hw_resources_t rif_hw_resources;
    dnx_algo_gpm_gport_hw_resources_t gport_hw_resources;
    SHR_FUNC_INIT_VARS(unit);

    if (mtu_config_p->flags != BCM_RX_MTU_PORT &&
        mtu_config_p->flags != BCM_RX_MTU_LIF && mtu_config_p->flags != BCM_RX_MTU_RIF)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported/Invalid flags have been set, %d flags are invalid",
                     mtu_config_p->flags);
    }

    if (mtu_config_p->flags == BCM_RX_MTU_RIF || mtu_config_p->flags == BCM_RX_MTU_LIF)
    {
        is_fec = BCM_L3_ITF_TYPE_IS_FEC(mtu_config_p->intf);
        if (is_fec == TRUE)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "MTU Interface cannot be FEC! Must be LIF or RIF.");
        }
    }

    if (mtu_config_p->mtu_profile >= dnx_data_trap.etpp.nof_mtu_profiles_get(unit))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The MTU profile(%d) supplied is bigger than the max profile(%d)",
                     mtu_config_p->mtu_profile, (dnx_data_trap.etpp.nof_mtu_profiles_get(unit) - 1));
    }

    is_lif = BCM_L3_ITF_TYPE_IS_LIF(mtu_config_p->intf);
    is_rif = BCM_L3_ITF_TYPE_IS_RIF(mtu_config_p->intf);
    if ((mtu_config_p->flags & BCM_RX_MTU_RIF) && (is_rif == TRUE))
    {

        SHR_IF_ERR_EXIT(dnx_algo_gpm_rif_intf_to_hw_resources(unit, mtu_config_p->intf, &rif_hw_resources));

        SHR_IF_ERR_EXIT(dbal_tables_field_size_get(unit, rif_hw_resources.outlif_dbal_table_id,
                                                   DBAL_FIELD_MTU_PROFILE,
                                                   FALSE,
                                                   rif_hw_resources.outlif_dbal_result_type, 0, &mtu_profile_size));
    }
    else if (mtu_config_p->flags == BCM_RX_MTU_LIF || (((mtu_config_p->flags & BCM_RX_MTU_RIF) && (is_lif == TRUE))))
    {
        if ((mtu_config_p->flags & BCM_RX_MTU_RIF) && (is_lif == TRUE))
        {
            BCM_L3_ITF_LIF_TO_GPORT_TUNNEL(mtu_config_p->gport, mtu_config_p->intf);
        }

        SHR_IF_ERR_REPLACE_AND_EXIT(dnx_algo_gpm_gport_to_hw_resources(unit, mtu_config_p->gport,
                                                                       DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_EGRESS,
                                                                       &gport_hw_resources), _SHR_E_NOT_FOUND,
                                    _SHR_E_PARAM);

        SHR_IF_ERR_EXIT(dbal_tables_field_size_get(unit, gport_hw_resources.outlif_dbal_table_id,
                                                   DBAL_FIELD_MTU_PROFILE,
                                                   FALSE,
                                                   gport_hw_resources.outlif_dbal_result_type, 0, &mtu_profile_size));

    }

    if (mtu_config_p->mtu_profile > ((1 << mtu_profile_size) - 1))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The MTU profile(%d) supplied is too big for the LIF/RIF type supplied."
                     "The LIF/RIF MTU profile is %d bits.", mtu_config_p->mtu_profile, mtu_profile_size);
    }

exit:
    SHR_FUNC_EXIT;

}

/**
* \brief
*  Verification function for the input parameters of dnx_rx_mtu_get()
*
* \par DIRECT INPUT:
*   \param [in] unit                 - Unit Id
*   \param [in] mtu_config_p         - MTU Configuration
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_mtu_get_verify(
    int unit,
    bcm_rx_mtu_config_t * mtu_config_p)
{
    int is_fec = 0, is_lif = 0, is_rif = 0;
    SHR_FUNC_INIT_VARS(unit);

    if (mtu_config_p->flags != BCM_RX_MTU_PORT &&
        mtu_config_p->flags != BCM_RX_MTU_LIF && mtu_config_p->flags != BCM_RX_MTU_RIF)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Unsupported/Invalid flags have been set, %d flags are invalid",
                     mtu_config_p->flags);
    }

    if (mtu_config_p->flags == BCM_RX_MTU_RIF || mtu_config_p->flags == BCM_RX_MTU_LIF)
    {
        is_fec = BCM_L3_ITF_TYPE_IS_FEC(mtu_config_p->intf);
        if (is_fec == TRUE)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "MTU Interface cannot be FEC! Must be LIF or RIF.");
        }
    }

    if (mtu_config_p->flags == BCM_RX_MTU_RIF)
    {
        is_lif = BCM_L3_ITF_TYPE_IS_LIF(mtu_config_p->intf);
        is_rif = BCM_L3_ITF_TYPE_IS_RIF(mtu_config_p->intf);
        if (!is_lif && !is_rif)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "MTU Interface is invalid! Must be LIF or RIF.");
        }
    }

exit:
    SHR_FUNC_EXIT;

}

/**
 * See rx.h for info
 */
shr_error_e
bcm_dnx_rx_mtu_set(
    int unit,
    bcm_rx_mtu_config_t * mtu_config_p)
{
    int is_rif = 0, is_lif = 0;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);
    SHR_NULL_CHECK(mtu_config_p, _SHR_E_PARAM, "mtu_config_p");

    SHR_INVOKE_VERIFY_DNXC(dnx_rx_mtu_set_verify(unit, mtu_config_p));

    if (mtu_config_p->flags == BCM_RX_MTU_PORT)
    {
        SHR_IF_ERR_EXIT(dnx_rx_mtu_port_set(unit, mtu_config_p));
    }
    else
    {
        is_rif = BCM_L3_ITF_TYPE_IS_RIF(mtu_config_p->intf);
        if ((mtu_config_p->flags & BCM_RX_MTU_RIF) && (is_rif == TRUE))
        {
            SHR_IF_ERR_EXIT(dnx_rx_mtu_rif_set(unit, mtu_config_p));
        }
        else
        {
            is_lif = BCM_L3_ITF_TYPE_IS_LIF(mtu_config_p->intf);
            if ((mtu_config_p->flags & BCM_RX_MTU_RIF) && (is_lif == TRUE))
            {
                BCM_L3_ITF_LIF_TO_GPORT_TUNNEL(mtu_config_p->gport, mtu_config_p->intf);
            }
            SHR_IF_ERR_EXIT(dnx_rx_mtu_lif_set(unit, mtu_config_p));
        }
    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;

}

/**
* \brief
*  This function retrieves the MTU configuration for the supplied PORT
*
* \par DIRECT INPUT:
*   \param [in] unit                 - Unit Id
*   \param [in] mtu_config_p         - MTU Configuration retrieved
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_mtu_port_get(
    int unit,
    bcm_rx_mtu_config_t * mtu_config_p)
{
    uint32 entry_handle_id;
    dnx_algo_gpm_gport_phy_info_t gport_info;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get
                    (unit, mtu_config_p->gport, DNX_ALGO_GPM_GPORT_TO_PHY_OP_PP_PORT_IS_MANDATORY, &gport_info));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_PP_PORT, &entry_handle_id));

    /*
     * key construction - Port
     */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, gport_info.internal_port_pp_info.pp_port[0]);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, gport_info.internal_port_pp_info.core_id[0]);

    /*
     * Get the MTU profile
     */
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_MTU_PROFILE, INST_SINGLE, &mtu_config_p->mtu_profile);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function retrieves the MTU configuration for the supplied LIF
*
* \par DIRECT INPUT:
*   \param [in] unit                 - Unit Id
*   \param [in] mtu_config_p         - MTU Configuration retrieved
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_mtu_lif_get(
    int unit,
    bcm_rx_mtu_config_t * mtu_config_p)
{
    SHR_FUNC_INIT_VARS(unit);

    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_v1_mtu_lif_get(unit, mtu_config_p));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function retrieves the MTU configuration for the supplied RIF
*
* \par DIRECT INPUT:
*   \param [in] unit                 - Unit Id
*   \param [in] mtu_config_p         - MTU Configuration retrieved
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_mtu_rif_get(
    int unit,
    bcm_rx_mtu_config_t * mtu_config_p)
{
    int mtu_profile;
    dnx_algo_gpm_rif_hw_resources_t rif_hw_resources;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Read RIF result type from SW state
     */
    SHR_IF_ERR_EXIT(dnx_algo_gpm_rif_intf_to_hw_resources(unit, mtu_config_p->intf, &rif_hw_resources));

    /**
     * Get the MTU profile from the LIF/RIF DBAL Table
     */
    SHR_IF_ERR_EXIT(dnx_rx_trap_lif_mtu_profile_hw_get(unit,
                                                       rif_hw_resources.outlif_dbal_table_id,
                                                       DBAL_FIELD_OUT_RIF,
                                                       rif_hw_resources.outlif_dbal_result_type,
                                                       mtu_config_p->intf, &mtu_profile));
    mtu_config_p->mtu_profile = mtu_profile;
exit:
    SHR_FUNC_EXIT;
}

/**
 * See rx.h for info
 */
shr_error_e
bcm_dnx_rx_mtu_get(
    int unit,
    bcm_rx_mtu_config_t * mtu_config_p)
{
    int is_rif = 0, is_lif = 0;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);
    SHR_NULL_CHECK(mtu_config_p, _SHR_E_PARAM, "mtu_config_p");

    SHR_INVOKE_VERIFY_DNXC(dnx_rx_mtu_get_verify(unit, mtu_config_p));

    /**
     * Get the MTU profile from either the PORT DBAL Table or the LIF DBAL Table
     */
    if (mtu_config_p->flags & BCM_RX_MTU_PORT)
    {
        SHR_IF_ERR_EXIT(dnx_rx_mtu_port_get(unit, mtu_config_p));
    }
    else
    {
        is_rif = BCM_L3_ITF_TYPE_IS_RIF(mtu_config_p->intf);
        if ((mtu_config_p->flags & BCM_RX_MTU_RIF) && (is_rif == TRUE))
        {
            SHR_IF_ERR_EXIT(dnx_rx_mtu_rif_get(unit, mtu_config_p));
        }
        else
        {
            is_lif = BCM_L3_ITF_TYPE_IS_LIF(mtu_config_p->intf);
            if ((mtu_config_p->flags & BCM_RX_MTU_RIF) && (is_lif == TRUE))
            {
                BCM_L3_ITF_LIF_TO_GPORT_TUNNEL(mtu_config_p->gport, mtu_config_p->intf);
            }

            SHR_IF_ERR_EXIT(dnx_rx_mtu_lif_get(unit, mtu_config_p));
        }

    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;

}

/**
* \brief
*  Map LIF info to HW resources
*
* \par DIRECT INPUT:
*   \param [in] unit                 - Unit Id
*   \param [in] lif_config_p         -  LIF trap configuration
*   \param [out] lif_hw_resources_p  - HW resources of LIF
*   \param [out] lif_gport_p         - LIF gport
*   \param [out] is_ingress_lif_p    - is ingress configuration
*   \param [out] is_rif_p            - is RIF dbal configuration
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_lif_to_hw_resources(
    int unit,
    bcm_rx_trap_lif_config_t * lif_config_p,
    dnx_algo_gpm_gport_hw_resources_t * lif_hw_resources_p,
    bcm_gport_t * lif_gport_p,
    uint8 *is_ingress_lif_p,
    uint8 *is_rif_p)
{
    uint32 algo_gpm_gport_flags = DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF;
    shr_error_e rv = _SHR_E_NONE;

    SHR_FUNC_INIT_VARS(unit);

    *is_rif_p = FALSE;

    switch (lif_config_p->lif_type)
    {
        case bcmRxTrapLifTypeInLif:
            *is_ingress_lif_p = TRUE;
            *lif_gport_p = lif_config_p->lif_gport;
            algo_gpm_gport_flags = DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_INGRESS;
            break;
        case bcmRxTrapLifTypeInRif:
            *is_ingress_lif_p = TRUE;
            BCM_L3_ITF_LIF_TO_GPORT_TUNNEL(*lif_gport_p, lif_config_p->rif_intf);
            algo_gpm_gport_flags = DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_INGRESS;
            break;
        case bcmRxTrapLifTypeOutLif:
            *is_ingress_lif_p = FALSE;
            *lif_gport_p = lif_config_p->lif_gport;
            algo_gpm_gport_flags = DNX_ALGO_GPM_GPORT_HW_RESOURCES_EGRESS_LOCAL_LIF_OR_VIRTUAL;
            break;
        case bcmRxTrapLifTypeOutRif:
            *is_ingress_lif_p = FALSE;
            *is_rif_p = BCM_L3_ITF_TYPE_IS_RIF(lif_config_p->rif_intf);
            if (*is_rif_p == FALSE)
            {
                BCM_L3_ITF_LIF_TO_GPORT_TUNNEL(*lif_gport_p, lif_config_p->rif_intf);
                algo_gpm_gport_flags = DNX_ALGO_GPM_GPORT_HW_RESOURCES_LOCAL_LIF_EGRESS;
            }
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Illegal lif type=%d\n", lif_config_p->lif_type);
            break;
    }

    /** Get HW resources of LIF/RIF */
    if (*is_rif_p == FALSE
        && !dnx_data_flow.general.feature_get(unit, dnx_data_flow_general_is_flow_enabled_for_legacy_applications))
    {
        rv = dnx_algo_gpm_gport_to_hw_resources(unit, *lif_gport_p, algo_gpm_gport_flags, lif_hw_resources_p);
        SHR_IF_ERR_EXIT_WITH_LOG(rv, "The RIF/LIF indicated is not valid%s%s%s\n", EMPTY, EMPTY, EMPTY);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set LIF trap action profile in HW: trap stregnths and profile num.
* \par DIRECT INPUT:
*   \param [in] unit      -  Unit Id
*   \param [in] lif_trap_profile   -  LIF trap profile
*   \param [in] trap_action_profile_p  -  Hold the action-profile configuration to set for specific trap
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e -  Error Type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_lif_ingress_action_profile_hw_set(
    int unit,
    uint32 lif_trap_profile,
    dnx_rx_trap_action_profile_t * trap_action_profile_p)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_LIF_ACTION_PROFILE, &entry_handle_id));

    /** key construction */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ACTION_PROFILE_IDX, lif_trap_profile);

    /** Set the values */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, INST_SINGLE,
                                 trap_action_profile_p->profile);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, INST_SINGLE,
                                 trap_action_profile_p->fwd_strength);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_SNP_STRENGTH, INST_SINGLE,
                                 trap_action_profile_p->snp_strength);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 * See rx_trap.h for more info
 */
shr_error_e
dnx_rx_trap_lif_ingress_action_profile_hw_clear(
    int unit,
    uint32 lif_trap_profile)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_TRAP_INGRESS_LIF_ACTION_PROFILE, &entry_handle_id));

    /** key construction */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ACTION_PROFILE_IDX, lif_trap_profile);

    SHR_IF_ERR_EXIT(dbal_entry_clear(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 * See rx_trap.h for more info
 */
shr_error_e
dnx_rx_trap_lif_ingress_trap_profile_allocate_and_hw_update(
    int unit,
    uint32 old_lif_trap_profile,
    bcm_gport_t action_gport,
    uint32 *new_lif_trap_profile_p,
    uint8 *is_last_p)
{
    uint8 is_first = 0;
    dnx_rx_trap_action_profile_t trap_action_profile;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(new_lif_trap_profile_p, _SHR_E_PARAM, "new_lif_trap_profile_p");
    SHR_NULL_CHECK(is_last_p, _SHR_E_PARAM, "is_last_p");

    SHR_IF_ERR_EXIT(algo_rx_db.trap_lif_ingress.exchange
                    (unit, 0, &action_gport,
                     old_lif_trap_profile, NULL, (int *) new_lif_trap_profile_p, &is_first, is_last_p));

    /** If this is the first time the lif trap profile is allocated, set it in HW */
    if (is_first)
    {
        trap_action_profile.profile = BCM_GPORT_TRAP_GET_ID(action_gport);
        trap_action_profile.fwd_strength = BCM_GPORT_TRAP_GET_STRENGTH(action_gport);
        trap_action_profile.snp_strength = BCM_GPORT_TRAP_GET_SNOOP_STRENGTH(action_gport);

        SHR_IF_ERR_EXIT(dnx_rx_trap_lif_ingress_action_profile_hw_set(unit, *new_lif_trap_profile_p,
                                                                      &trap_action_profile));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Allocate and Set the ingress LIF trap Profile in the correct IN_LIF table, for the supplied IN_LIF.
* \par DIRECT INPUT:
*   \param [in] unit        - unit Id
*   \param [in] lif_gport   - LIF's gport
*   \param [in] lif_hw_resources_p  - LIF's HW resouces
*   \param [in] action_gport - action gport encoding Trap-Action-Profile
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
dnx_rx_trap_lif_ingress_profile_set(
    int unit,
    bcm_gport_t lif_gport,
    dnx_algo_gpm_gport_hw_resources_t * lif_hw_resources_p,
    bcm_gport_t action_gport)
{
    SHR_FUNC_INIT_VARS(unit);

    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_v1_lif_ingress_profile_set(unit, lif_hw_resources_p, action_gport));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_rx_trap_lif_ingress_profile_get(
    int unit,
    bcm_gport_t lif_gport,
    dnx_algo_gpm_gport_hw_resources_t * lif_hw_resources_p,
    bcm_gport_t * action_gport_p)
{
    SHR_FUNC_INIT_VARS(unit);

    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_v1_lif_ingress_profile_get(unit, lif_hw_resources_p, action_gport_p));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set the ingress LIF trap Profile in the correct OUT_LIF table, for the supplied OUT_LIF.
* \par DIRECT INPUT:
*   \param [in] unit        - unit Id
*   \param [in] rif_hw_resources_p  - RIF's HW resources
*   \param [in] rif_intf  - RIF interface
*   \param [in] lif_trap_profile - LIF trap Profile
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_lif_etpp_profile_rif_hw_set(
    int unit,
    dnx_algo_gpm_rif_hw_resources_t * rif_hw_resources_p,
    bcm_if_t rif_intf,
    uint32 lif_trap_profile)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, rif_hw_resources_p->outlif_dbal_table_id, &entry_handle_id));

    /** key construction -Out Lif */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OUT_RIF, rif_intf);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RESULT_TYPE, INST_SINGLE,
                                 rif_hw_resources_p->outlif_dbal_result_type);

    /** Set the LIF trap profile */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ACTION_PROFILE, INST_SINGLE, lif_trap_profile);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get the ingress LIF trap Profile in the correct OUT_LIF table, for the supplied OUT_LIF.
* \par DIRECT INPUT:
*   \param [in] unit        - unit Id
*   \param [in] rif_hw_resources_p  - RIF's HW resources
*   \param [in] rif_intf  - RIF interface
*   \param [out] lif_trap_profile_p - LIF trap Profile
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_lif_etpp_profile_rif_hw_get(
    int unit,
    dnx_algo_gpm_rif_hw_resources_t * rif_hw_resources_p,
    bcm_if_t rif_intf,
    uint32 *lif_trap_profile_p)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, rif_hw_resources_p->outlif_dbal_table_id, &entry_handle_id));

    /** key construction -Out Lif */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OUT_RIF, rif_intf);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RESULT_TYPE, INST_SINGLE,
                                 rif_hw_resources_p->outlif_dbal_result_type);

    /** Get the LIF trap profile */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_ACTION_PROFILE, INST_SINGLE, lif_trap_profile_p);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set the ETPP LIF action profile in HW
* \par DIRECT INPUT:
*   \param [in] unit        - unit Id
*   \param [in] lif_trap_profile  - lif trap profile
*   \param [in] action_gport - gport encoding the action
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_lif_etpp_trap_action_profile_hw_set(
    int unit,
    uint32 lif_trap_profile,
    bcm_gport_t action_gport)
{
    uint8 mirror_action_profile;
    uint32 trap_id;
    dbal_enum_value_field_etpp_trap_id_e dbal_trap_id = 0;
    dnx_rx_trap_action_profile_t trap_action_profile;
    SHR_FUNC_INIT_VARS(unit);

    if (lif_trap_profile == DNX_RX_TRAP_ETPP_LIF_PROFILE_STACK_MIRROR)
    {
        mirror_action_profile = BCM_GPORT_MIRROR_GET(action_gport);
        mirror_action_profile = DNX_MIRROR_EGRESS_PROFILE_GET(unit, mirror_action_profile);
        SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_mirror_action_profile_hw_set(unit,
                                                                      DBAL_TABLE_ETPP_STACK_TRAP_MIRROR_ACTION_PROFILE,
                                                                      mirror_action_profile));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_lif_profile_map_to_dbal_trap_id_dispatch
                        (unit, lif_trap_profile, &dbal_trap_id));
        trap_id = BCM_GPORT_TRAP_GET_ID(action_gport);
        trap_action_profile.profile = DNX_RX_TRAP_ID_TYPE_GET(trap_id);
        trap_action_profile.fwd_strength = BCM_GPORT_TRAP_GET_STRENGTH(action_gport);
        trap_action_profile.snp_strength = BCM_GPORT_TRAP_GET_SNOOP_STRENGTH(action_gport);

        SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_action_profile_set(unit, dbal_trap_id, &trap_action_profile));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See rx_trap.h for more info
 */
shr_error_e
dnx_rx_trap_lif_etpp_trap_action_profile_hw_clear(
    int unit,
    uint32 lif_trap_profile)
{
    dbal_enum_value_field_etpp_trap_id_e dbal_trap_id = 0;
    SHR_FUNC_INIT_VARS(unit);

    if (lif_trap_profile == DNX_RX_TRAP_ETPP_LIF_PROFILE_STACK_MIRROR)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_mirror_action_profile_hw_clear(unit,
                                                                        DBAL_TABLE_ETPP_STACK_TRAP_MIRROR_ACTION_PROFILE));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_lif_profile_map_to_dbal_trap_id_dispatch
                        (unit, lif_trap_profile, &dbal_trap_id));
        SHR_IF_ERR_EXIT(dnx_rx_trap_etpp_action_profile_clear(unit, dbal_trap_id));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See rx_trap.h for more info
 */
shr_error_e
dnx_rx_trap_lif_etpp_trap_profile_allocate_and_hw_update(
    int unit,
    uint32 old_lif_trap_profile,
    bcm_gport_t action_gport,
    uint32 *new_lif_trap_profile_p,
    uint8 *is_last_p)
{
    uint8 is_first = 0;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(new_lif_trap_profile_p, _SHR_E_PARAM, "new_lif_trap_profile_p");
    SHR_NULL_CHECK(is_last_p, _SHR_E_PARAM, "is_last_p");

    SHR_IF_ERR_EXIT(algo_rx_db.trap_lif_etpp.exchange
                    (unit, 0, &action_gport,
                     old_lif_trap_profile, NULL, (int *) new_lif_trap_profile_p, &is_first, is_last_p));

    /** If this is the first time the lif trap profile is allocated, set it in HW */
    if (is_first)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_lif_etpp_trap_action_profile_hw_set(unit, *new_lif_trap_profile_p, action_gport));
    }
exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Allocate and Set the ETPP LIF trap Profile (Trap or Mirror)  in the correct OUT_LIF table, for the supplied OUT_LIF.
* \par DIRECT INPUT:
*   \param [in] unit        - unit Id
*   \param [in] lif_gport - LIF gport
*   \param [in] lif_hw_resources_p  - LIF's HW resouces
*   \param [in] action_gport - action gport encoding Trap-Action-Profile
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
dnx_rx_trap_lif_etpp_profile_lif_set(
    int unit,
    bcm_gport_t lif_gport,
    dnx_algo_gpm_gport_hw_resources_t * lif_hw_resources_p,
    bcm_gport_t action_gport)
{
    SHR_FUNC_INIT_VARS(unit);

    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_v1_lif_etpp_profile_lif_set(unit, lif_gport, lif_hw_resources_p, action_gport));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get the ETPP LIF trap profile action_gport.
* \par DIRECT INPUT:
*   \param [in] unit        - unit Id
*   \param [in] lif_gport - LIF gport
*   \param [in] lif_hw_resources_p  - LIF's HW resouces
*   \param [out] action_gport_p - action gport
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
dnx_rx_trap_lif_etpp_profile_lif_get(
    int unit,
    bcm_gport_t lif_gport,
    dnx_algo_gpm_gport_hw_resources_t * lif_hw_resources_p,
    bcm_gport_t * action_gport_p)
{
    SHR_FUNC_INIT_VARS(unit);

    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_v1_lif_etpp_profile_lif_get(unit, lif_gport, lif_hw_resources_p, action_gport_p));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Allocate and Set the ETPP LIF trap Profile (Trap or Mirror) in the correct OUT_RIF table, for the supplied OUT_RIF.
* \par DIRECT INPUT:
*   \param [in] unit        - unit Id
*   \param [in] rif_hw_resources_p  - RIF's HW resources
*   \param [in] rif_intf  - RIF interface
*   \param [in] action_gport - action gport encoding Trap-Action-Profile
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_lif_etpp_profile_rif_set(
    int unit,
    dnx_algo_gpm_rif_hw_resources_t * rif_hw_resources_p,
    bcm_if_t rif_intf,
    bcm_gport_t action_gport)
{
    uint8 is_first = 0, is_last = 0;
    uint32 old_lif_trap_profile = 0, new_lif_trap_profile = 0;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_lif_etpp_profile_rif_hw_get(unit, rif_hw_resources_p, rif_intf, &old_lif_trap_profile));

    SHR_IF_ERR_EXIT(algo_rx_db.trap_lif_etpp.exchange
                    (unit, 0, &action_gport,
                     old_lif_trap_profile, NULL, (int *) &new_lif_trap_profile, &is_first, &is_last));

    /** If this is the last trap pointing to this lif trap profile, clear profile from HW */
    if (is_last)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_lif_etpp_trap_action_profile_hw_clear(unit, old_lif_trap_profile));
    }

    /** If this is the first time the lif trap profile is allocated, set it in HW */
    if (is_first)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_lif_etpp_trap_action_profile_hw_set(unit, new_lif_trap_profile, action_gport));
    }

    SHR_IF_ERR_EXIT(dnx_rx_trap_lif_etpp_profile_rif_hw_set(unit, rif_hw_resources_p, rif_intf, new_lif_trap_profile));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get the ETPP LIF trap profile action_gport.
* \par DIRECT INPUT:
*   \param [in] unit        - unit Id
*   \param [in] rif_hw_resources_p  - RIF's HW resources
*   \param [in] rif_intf  - RIF interface
*   \param [in] action_gport_p - action gport
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_lif_etpp_profile_rif_get(
    int unit,
    dnx_algo_gpm_rif_hw_resources_t * rif_hw_resources_p,
    bcm_if_t rif_intf,
    bcm_gport_t * action_gport_p)
{
    uint32 lif_trap_profile = 0;
    int ref_count;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_lif_etpp_profile_rif_hw_get(unit, rif_hw_resources_p, rif_intf, &lif_trap_profile));

    SHR_IF_ERR_EXIT(algo_rx_db.trap_lif_etpp.profile_data_get(unit, lif_trap_profile, &ref_count, action_gport_p));

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Verification function for LIF type input parameters verify
*
* \par DIRECT INPUT:
*   \param [in] unit              - Unit Id
*   \param [in] lif_config_p    -  LIF trap configuration
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_lif_type_verify(
    int unit,
    bcm_rx_trap_lif_config_t * lif_config_p)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(lif_config_p, _SHR_E_PARAM, "lif_config_p");

    if (lif_config_p->lif_type >= bcmRxTrapLifTypeCount)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The LIF type supplied (%d) is not valid", lif_config_p->lif_type);
    }

    if ((lif_config_p->lif_type == bcmRxTrapLifTypeInLif || lif_config_p->lif_type == bcmRxTrapLifTypeOutLif) &&
        !BCM_GPORT_IS_SET(lif_config_p->lif_gport))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The LIF indicated lif_gport is not valid");
    }

    if ((lif_config_p->lif_type == bcmRxTrapLifTypeInRif || lif_config_p->lif_type == bcmRxTrapLifTypeOutRif) &&
        BCM_L3_ITF_TYPE_IS_FEC(lif_config_p->rif_intf))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The RIF indicated in rif_intf is not valid");
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Verification function for the input parameters of dnx_rx_trap_lif_set()
*
* \par DIRECT INPUT:
*   \param [in] unit              - Unit Id
*   \param [in] flags             - flags
*   \param [in] lif_config_p    -  LIF trap configuration
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_lif_set_verify(
    int unit,
    uint32 flags,
    bcm_rx_trap_lif_config_t * lif_config_p)
{
    int trap_id = 0;
    uint8 is_allocated = 0;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_lif_type_verify(unit, lif_config_p));

    if (BCM_GPORT_IS_MIRROR_MIRROR(lif_config_p->action_gport))
    {
        if ((lif_config_p->lif_type != bcmRxTrapLifTypeOutLif) && (lif_config_p->lif_type != bcmRxTrapLifTypeOutRif))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Mirror configuration can only be done for ETPP lif traps");
        }

        /** Mirror valid case, no need fo adittional checks */
        SHR_EXIT();
    }

    if (!BCM_GPORT_IS_TRAP(lif_config_p->action_gport) && (lif_config_p->action_gport != BCM_GPORT_INVALID))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The Trap-Gport is not valid");
    }

    if ((lif_config_p->action_gport != BCM_GPORT_INVALID)
        && (BCM_GPORT_TRAP_GET_STRENGTH(lif_config_p->action_gport) != 0)
        && (BCM_GPORT_TRAP_GET_SNOOP_STRENGTH(lif_config_p->action_gport) != 0))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The Trap-Gport is not valid, "
                     "Snoop and Forwarding strengths cannot be both set to non-zero values.");
    }

    if (lif_config_p->action_gport != BCM_GPORT_INVALID)
    {
        dnx_rx_trap_block_e trap_block = DNX_RX_TRAP_BLOCK_INVALID;
        trap_id = BCM_GPORT_TRAP_GET_ID(lif_config_p->action_gport);
        trap_block = DNX_RX_TRAP_ID_BLOCK_GET(trap_id);

        if ((lif_config_p->lif_type == bcmRxTrapLifTypeInLif ||
             lif_config_p->lif_type == bcmRxTrapLifTypeInRif) && (trap_block != DNX_RX_TRAP_BLOCK_INGRESS))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "For lif types InLif and InRif, an IRPP trap_id must be provided! "
                         "The supplied trap_id 0x%08x is on trap_block=%d!", trap_id, trap_block);
        }

        if ((lif_config_p->lif_type == bcmRxTrapLifTypeOutLif ||
             lif_config_p->lif_type == bcmRxTrapLifTypeOutRif) && (trap_block != DNX_RX_TRAP_BLOCK_ETPP))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "For lif types OutLif and OutRif, an ETPP trap_id must be provided! "
                         "The supplied trap_id 0x%08x is on trap_block=%d!", trap_id, trap_block);
        }

        SHR_IF_ERR_EXIT(dnx_rx_trap_is_trap_id_allocated(unit, trap_id, &is_allocated));
        if (!is_allocated)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "The Trap_ID 0x%08x supplied to the action_gport is not allocated."
                         "Please use bcm_rx_trap_type_create() first,", trap_id);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * See rx.h for info
 */
shr_error_e
bcm_dnx_rx_trap_lif_set(
    int unit,
    uint32 flags,
    bcm_rx_trap_lif_config_t * lif_config_p)
{
    dnx_algo_gpm_gport_hw_resources_t lif_hw_resources;
    dnx_algo_gpm_rif_hw_resources_t rif_hw_resources;
    uint8 is_ingress_lif, is_rif;
    bcm_gport_t lif_gport;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_lif_set_verify(unit, flags, lif_config_p));

    SHR_IF_ERR_EXIT(dnx_rx_trap_lif_to_hw_resources
                    (unit, lif_config_p, &lif_hw_resources, &lif_gport, &is_ingress_lif, &is_rif));

    if (is_ingress_lif)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_lif_ingress_profile_set
                        (unit, lif_gport, &lif_hw_resources, lif_config_p->action_gport));
    }
    else if (is_rif)
    {
        SHR_IF_ERR_EXIT(dnx_algo_gpm_rif_intf_to_hw_resources(unit, lif_config_p->rif_intf, &rif_hw_resources));

        if ((rif_hw_resources.outlif_dbal_table_id == DBAL_TABLE_EEDB_RIF_BASIC
             && rif_hw_resources.outlif_dbal_result_type == 0)
            && BCM_GPORT_IS_MIRROR_MIRROR(lif_config_p->action_gport))
        {
            SHR_ERR_EXIT(_SHR_E_CONFIG, "Mirror Profile cannot be assigned to ETH RIF !");
        }

        SHR_IF_ERR_EXIT(dnx_rx_trap_lif_etpp_profile_rif_set(unit, &rif_hw_resources, lif_config_p->rif_intf,
                                                             lif_config_p->action_gport));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_lif_etpp_profile_lif_set
                        (unit, lif_gport, &lif_hw_resources, lif_config_p->action_gport));
    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
 * See rx.h for info
 */
shr_error_e
bcm_dnx_rx_trap_lif_get(
    int unit,
    bcm_rx_trap_lif_config_t * lif_config_p)
{
    dnx_algo_gpm_gport_hw_resources_t lif_hw_resources;
    dnx_algo_gpm_rif_hw_resources_t rif_hw_resources;
    uint8 is_ingress_lif, is_rif;
    bcm_gport_t lif_gport;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_lif_type_verify(unit, lif_config_p));

    SHR_IF_ERR_EXIT(dnx_rx_trap_lif_to_hw_resources
                    (unit, lif_config_p, &lif_hw_resources, &lif_gport, &is_ingress_lif, &is_rif));

    if (is_ingress_lif)
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_lif_ingress_profile_get
                        (unit, lif_gport, &lif_hw_resources, &lif_config_p->action_gport));
    }
    else if (is_rif)
    {
        SHR_IF_ERR_EXIT(dnx_algo_gpm_rif_intf_to_hw_resources(unit, lif_config_p->rif_intf, &rif_hw_resources));
        SHR_IF_ERR_EXIT(dnx_rx_trap_lif_etpp_profile_rif_get(unit, &rif_hw_resources, lif_config_p->rif_intf,
                                                             &lif_config_p->action_gport));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_lif_etpp_profile_lif_get
                        (unit, lif_gport, &lif_hw_resources, &lif_config_p->action_gport));
    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_rx_trap_svtag_common_verify(
    int unit,
    bcm_rx_trap_svtag_key_t * svtag_trap_key,
    bcm_gport_t action_gport)
{
    int nof_err_code_profiles = dnx_data_trap.ingress.nof_error_code_profiles_get(unit);
    int nof_sci_profiles = dnx_data_trap.ingress.nof_sci_profiles_get(unit);
    int svtag_trap_en;

    SHR_FUNC_INIT_VARS(unit);

    svtag_trap_en = dnx_data_trap.ingress.feature_get(unit, dnx_data_trap_ingress_svtag_trap_en);
    if (svtag_trap_en == 0)
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, "The SVTAG APIs are not supported on this device !");
    }

    if ((svtag_trap_key->flags != 0) && (svtag_trap_key->flags != BCM_RX_TRAP_SVTAG_IPSEC))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Incorrect flags, the only legal values are 0 and BCM_RX_TRAP_SVTAG_IPSEC !");
    }

    if (svtag_trap_key->error_code_profile > nof_err_code_profiles)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The Error Code profile is out of range! Maximum value is %d",
                     nof_err_code_profiles);
    }

    if (svtag_trap_key->sci_profile > nof_sci_profiles)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The SCI profile is out of range! Maximum value is %d", nof_sci_profiles);
    }

    if (svtag_trap_key->pkt_type > bcmSvtagPktTypeKayMgmt)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The Packet type is out of range! Maximum value is bcmSvtagPktTypeKayMgmt");
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Verification function for the input parameters of bcm_dnx_rx_trap_svtag_set()
*
* \par DIRECT INPUT:
*   \param [in] unit            - Unit Id
*   \param [in] svtag_trap_key  - SVTag trap key
*   \param [in] action_gport    - Trap Action Gport
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_svtag_set_verify(
    int unit,
    bcm_rx_trap_svtag_key_t * svtag_trap_key,
    bcm_gport_t action_gport)
{
    int trap_id;
    uint8 is_allocated;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_svtag_common_verify(unit, svtag_trap_key, action_gport));

    if (!BCM_GPORT_IS_TRAP(action_gport) && (action_gport != BCM_GPORT_INVALID))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The Trap-Gport is not valid");
    }

    if ((action_gport != BCM_GPORT_INVALID)
        && (BCM_GPORT_TRAP_GET_STRENGTH(action_gport) != 0) && (BCM_GPORT_TRAP_GET_SNOOP_STRENGTH(action_gport) != 0))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The Trap-Gport is not valid, "
                     "Snoop and Forwarding strengths cannot be both set to non-zero values.");
    }

    if (BCM_GPORT_IS_TRAP(action_gport)
        && (BCM_GPORT_TRAP_GET_STRENGTH(action_gport) == 0) && (BCM_GPORT_TRAP_GET_SNOOP_STRENGTH(action_gport) == 0))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "The Trap-Gport is not valid, "
                     "Snoop and Forwarding strengths cannot be both set to zero.");
    }

    if (action_gport != BCM_GPORT_INVALID)
    {
        trap_id = BCM_GPORT_TRAP_GET_ID(action_gport);
        SHR_IF_ERR_EXIT(dnx_rx_trap_is_trap_id_allocated(unit, trap_id, &is_allocated));

        if (!is_allocated)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "The Trap_ID 0x%08x supplied to the action_gport is not allocated."
                         "Please use bcm_rx_trap_type_create() first,", trap_id);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * See rx.h for info
 */
shr_error_e
bcm_dnx_rx_trap_svtag_set(
    int unit,
    bcm_rx_trap_svtag_key_t * svtag_trap_key,
    bcm_gport_t action_gport)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_svtag_set_verify(unit, svtag_trap_key, action_gport));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_SVTAG_TRAP_ATTRIBUTE, &entry_handle_id));

    /** key construction */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_SVTAG_TYPE, svtag_trap_key->flags);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PKT_TYPE, svtag_trap_key->pkt_type);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ERR_CODE_TRAP_PROFILE,
                               svtag_trap_key->error_code_profile);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_SCI_TRAP_PROFILE, svtag_trap_key->sci_profile);

    if (action_gport != BCM_GPORT_INVALID)
    {
        /** Set the Action Profile */
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, INST_SINGLE,
                                     BCM_GPORT_TRAP_GET_ID(action_gport));
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, INST_SINGLE,
                                     BCM_GPORT_TRAP_GET_STRENGTH(action_gport));
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TRAP_SNP_STRENGTH, INST_SINGLE,
                                     BCM_GPORT_TRAP_GET_SNOOP_STRENGTH(action_gport));

        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }
    else
    {
        SHR_IF_ERR_EXIT(dbal_entry_clear(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * See rx.h for info
 */
shr_error_e
bcm_dnx_rx_trap_svtag_get(
    int unit,
    bcm_rx_trap_svtag_key_t * svtag_trap_key,
    bcm_gport_t * action_gport)
{
    uint32 entry_handle_id;
    uint32 trap_id, fwd_strength, snp_strength;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    SHR_IF_ERR_EXIT(dnx_rx_trap_svtag_common_verify(unit, svtag_trap_key, *action_gport));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_SVTAG_TRAP_ATTRIBUTE, &entry_handle_id));

   /** key construction */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_SVTAG_TYPE, svtag_trap_key->flags);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PKT_TYPE, svtag_trap_key->pkt_type);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ERR_CODE_TRAP_PROFILE,
                               svtag_trap_key->error_code_profile);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_SCI_TRAP_PROFILE, svtag_trap_key->sci_profile);

    /** Get the trap profile */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_INGRESS_TRAP_ID, INST_SINGLE, &trap_id);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_TRAP_FWD_STRENGTH, INST_SINGLE, &fwd_strength);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_TRAP_SNP_STRENGTH, INST_SINGLE, &snp_strength);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

    BCM_GPORT_TRAP_SET(*action_gport, trap_id, fwd_strength, snp_strength);

exit:
    DNX_ERR_RECOVERY_END(unit);
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function purpose is to verify the parameters supplied to
*  dnx_rx_trap_protocol_interface_profiles_set
* \par DIRECT INPUT:
*   \param [in] unit      -  unit Id
*   \param [in] intf  - IN-RIF
*   \param [in] protocol_profiles_p  -  protocol trap profiles struct
*               \b As \b input - \n
*               Pointer contains the trap profiles of each protocol
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_protocol_interface_profiles_set_verify(
    int unit,
    bcm_if_t intf,
    bcm_rx_trap_protocol_profiles_t * protocol_profiles_p)
{
    uint8 protocol_trap_profiles_nof;
    uint8 protocol_trap_mode;
    SHR_FUNC_INIT_VARS(unit);
    protocol_trap_mode = dnx_data_trap.ingress.protocol_traps_init_mode_get(unit);
    protocol_trap_profiles_nof = dnx_data_trap.ingress.nof_protocol_trap_profiles_get(unit);

    if (protocol_trap_mode == DNX_RX_TRAP_PROTOCOL_MODE_IN_LIF)
    {
        if (!BCM_L3_ITF_TYPE_IS_LIF(intf) && !BCM_L3_ITF_TYPE_IS_RIF(intf))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Interface supplied is invalid! Must interface type LIF or RIF.");
        }
    }
    else if (protocol_trap_mode == DNX_RX_TRAP_PROTOCOL_MODE_IN_PORT)
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, "The API function is not available in IN_PORT mode. \n");
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_CONFIG, "Protocol trap mode SOC property is set with an un-supported mode type. \n");
    }

    if (protocol_profiles_p->arp_trap_profile >= protocol_trap_profiles_nof ||
        protocol_profiles_p->dhcp_trap_profile >= protocol_trap_profiles_nof ||
        protocol_profiles_p->icmpv4_trap_profile >= protocol_trap_profiles_nof ||
        protocol_profiles_p->icmpv6_trap_profile >= protocol_trap_profiles_nof ||
        protocol_profiles_p->igmp_trap_profile >= protocol_trap_profiles_nof ||
        protocol_profiles_p->l2cp_trap_profile >= protocol_trap_profiles_nof ||
        protocol_profiles_p->non_auth_8021x_trap_profile >= protocol_trap_profiles_nof)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Protocol trap profile must be between 0-3 ! \n");
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function purpose is to set protocol trap profiles
* \par DIRECT INPUT:
*   \param [in] unit      -  unit Id
*   \param [in] intf  - Ingress interface
*   \param [in] protocol_profiles_p  -  protocol trap profiles struct
*               \b As \b input - \n
*               Pointer contains the trap profiles of each protocol
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
bcm_dnx_rx_trap_protocol_interface_profiles_set(
    int unit,
    bcm_if_t intf,
    bcm_rx_trap_protocol_profiles_t * protocol_profiles_p)
{
    bcm_gport_t gport;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);
    SHR_NULL_CHECK(protocol_profiles_p, _SHR_E_PARAM, "protocol_profiles_p");

    SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_interface_profiles_set_verify(unit, intf, protocol_profiles_p));

    if (BCM_L3_ITF_TYPE_IS_RIF(intf) && !BCM_GPORT_IS_SET(intf))
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_in_lif_profile_set
                        (unit, BCM_L3_ITF_VAL_GET(intf), ETH_RIF, DBAL_TABLE_ING_VSI_INFO_DB, *protocol_profiles_p));
    }
    else
    {
        BCM_L3_ITF_LIF_TO_GPORT_TUNNEL(gport, intf);
        SHR_IF_ERR_EXIT(bcm_dnx_rx_trap_protocol_profiles_set(unit, gport, protocol_profiles_p));
    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
* \brief
*  This function purpose is to verify the parameters supplied to
*  dnx_rx_trap_protocol_profiles_get.
* \par DIRECT INPUT:
*   \param [in] unit      -  unit Id
*   \param [in] intf  - IN-RIF
*   \param [out] protocol_profiles_p  -  protocol trap profiles struct
*               \b As \b output - \n
*               Pointer contains the trap profiles of each protocol
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
static shr_error_e
dnx_rx_trap_protocol_interface_profiles_get_verify(
    int unit,
    bcm_if_t intf,
    bcm_rx_trap_protocol_profiles_t * protocol_profiles_p)
{
    uint8 protocol_trap_mode;
    SHR_FUNC_INIT_VARS(unit);
    protocol_trap_mode = dnx_data_trap.ingress.protocol_traps_init_mode_get(unit);

    if (protocol_trap_mode == DNX_RX_TRAP_PROTOCOL_MODE_IN_LIF)
    {
        if (!BCM_L3_ITF_TYPE_IS_LIF(intf) && !BCM_L3_ITF_TYPE_IS_RIF(intf))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Interface supplied is invalid! Must interface type LIF or RIF.");
        }
    }
    else if (protocol_trap_mode == DNX_RX_TRAP_PROTOCOL_MODE_IN_PORT)
    {
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, "The API function is not available in IN_PORT mode. \n");
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_CONFIG, "Protocol trap mode SOC property is set with an un-supported mode type. \n");
    }

exit:
    SHR_FUNC_EXIT;
}

    /**
* \brief
*  This function purpose is to set protocol trap profiles
* \par DIRECT INPUT:
*   \param [in] unit      -  unit Id
*   \param [in] intf  - Ingress interface
*   \param [in] protocol_profiles_p  -  protocol trap profiles struct
*               \b As \b input - \n
*               Pointer contains the trap profiles of each protocol
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   shr_error_e - Error type
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
shr_error_e
bcm_dnx_rx_trap_protocol_interface_profiles_get(
    int unit,
    bcm_if_t intf,
    bcm_rx_trap_protocol_profiles_t * protocol_profiles_p)
{
    bcm_gport_t gport;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);
    SHR_NULL_CHECK(protocol_profiles_p, _SHR_E_PARAM, "protocol_profiles_p");

    SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_interface_profiles_get_verify(unit, intf, protocol_profiles_p));

    if (BCM_L3_ITF_TYPE_IS_RIF(intf) && !BCM_GPORT_IS_SET(intf))
    {
        SHR_IF_ERR_EXIT(dnx_rx_trap_protocol_in_lif_profile_get
                        (unit, BCM_L3_ITF_VAL_GET(intf), ETH_RIF, protocol_profiles_p));
    }
    else
    {
        BCM_L3_ITF_LIF_TO_GPORT_TUNNEL(gport, intf);
        SHR_IF_ERR_EXIT(bcm_dnx_rx_trap_protocol_profiles_get(unit, gport, protocol_profiles_p));
    }

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

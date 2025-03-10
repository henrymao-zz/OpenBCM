/** 
 *  \file src/bcm/dnx/rx/rx_trap_map_dispatch.h
 * 
 * 
 * Internal DNX RX APIs 
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 */

#ifndef RX_TRAP_MAP_DISPATCH_H_INCLUDED
/* { */
#define RX_TRAP_MAP_DISPATCH_H_INCLUDED

#include <include/bcm_int/dnx/rx/rx_trap.h>

/**
* \brief
*  Indicate if trap indicated is a user defined trap
* \param [in] unit                  - Device ID
* \param [in] trap_block            - Block of trap
* \param [in] trap_id               - Trap ID
* \param [out] is_user_defined_p    - Indicate if trap is user defined (TRUE/FALSE)
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
shr_error_e dnx_rx_trap_is_user_defined_dispatch(
    int unit,
    dnx_rx_trap_block_e trap_block,
    int trap_id,
    uint8 *is_user_defined_p);

/**
* \brief
*  Return the map information for the requested trap type.
*  Information is taken from dnx_rx_trap_type_map array
* \param [in] unit                      - Device ID
* \param [in] trap_type                 - trap type
* \param [out] trap_type_info_p   - Predefined trap info
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
shr_error_e dnx_rx_trap_type_map_info_get_dispatch(
    int unit,
    bcm_rx_trap_t trap_type,
    dnx_rx_trap_map_type_t * trap_type_info_p);

/**
* \brief
*  Return the map information for the requested ingress User Defined trap ID.
* \param [in] unit                 - Device ID
* \param [in] trap_id              - Trap ID
* \param [out] ingress_ud_info_p   - UserDefined info
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
shr_error_e dnx_rx_trap_ingress_ud_map_info_get_dispatch(
    int unit,
    int trap_id,
    dnx_rx_trap_map_ingress_ud_t * ingress_ud_info_p);

/**
* \brief
*  Return the trap_id for the requested alloc_index.
* \param [in] unit                 - Device ID
* \param [in] alloc_index          - Alloc index
* \param [out] trap_id_p           - Trap id
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
shr_error_e dnx_rx_trap_map_ingress_ud_alloc_get_dispatch(
    int unit,
    int alloc_index,
    int *trap_id_p);

/**
* \brief
*  Return the ID range map information for the requested trap block.
* \param [in] unit                    - Device ID
* \param [in] trap_block              - Trap Block
* \param [out] trap_id_range_info_p   - Trap id range info
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
shr_error_e dnx_rx_trap_id_boundry_ranges_map_info_get_dispatch(
    int unit,
    dnx_rx_trap_block_e trap_block,
    dnx_rx_trap_map_ranges_t * trap_id_range_info_p);

/**
* \brief
*  Return the DBAL trap id for the given lif trap profile.
* \param [in] unit                    - Device ID
* \param [in] lif_trap_profile        - LIF trap profile
* \param [out] dbal_trap_id_p         - DBAL trap id
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
shr_error_e dnx_rx_trap_etpp_lif_profile_map_to_dbal_trap_id_dispatch(
    int unit,
    dnx_rx_trap_etpp_lif_profiles_e lif_trap_profile,
    dbal_enum_value_field_etpp_trap_id_e * dbal_trap_id_p);

/**
* \brief
*  Return the OAM trap type for the given forward action profile.
* \param [in] unit                    - Device ID
* \param [in] oam_sub_type            - OAM sub type
* \param [in] fwd_act_profile         - Forward action profile
* \param [out] oam_trap_type_p        - OAM trap type
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
shr_error_e dnx_rx_trap_etpp_fwd_act_profile_map_to_oam_trap_type_dispatch(
    int unit,
    dbal_enum_value_field_oam_sub_type_e oam_sub_type,
    int fwd_act_profile,
    dnx_rx_trap_etpp_oam_types_e * oam_trap_type_p);

/**
* \brief
*  Return the map information for the requested trap type.
* \param [in] unit                    - Device ID
* \param [in] trap_type               - Trap Type
* \param [out] appl_trap_info_p       - Trap type info
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
shr_error_e dnx_rx_trap_appl_trap_map_info_get_dispatch(
    int unit,
    bcm_rx_trap_t trap_type,
    dnx_rx_trap_map_type_t * appl_trap_info_p);

/**
* \brief
*  Return the UserDefined trap information for the requested trap block.
* \param [in] unit                    - Device ID
* \param [in] trap_block              - Trap Block
* \param [out] ud_block_info_p        - UserDefined traps info
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
shr_error_e dnx_rx_trap_user_defined_block_map_info_get_dispatch(
    int unit,
    dnx_rx_trap_block_e trap_block,
    dnx_rx_trap_map_ud_t * ud_block_info_p);

/**
* \brief
*  Return the Statistical object info for the requested profile.
* \param [in] unit                - Device ID
* \param [in] stat_obj_profile    - Stat Object profile
* \param [out] stat_obj_info_p    - Stat Object profile info
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
shr_error_e dnx_rx_trap_stat_obj_map_info_get_dispatch(
    int unit,
    uint32 stat_obj_profile,
    dnx_rx_trap_map_stat_obj_dbal_fields_t * stat_obj_info_p);

/**
* \brief
*  Return the description of a bcmRxTrap...
* \param [in] unit               - Device ID
* \param [in] trap_type          - Trap Type
* \param [out] description       - Trap type info
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
shr_error_e dnx_rx_trap_type_description_map_info_get_dispatch(
    int unit,
    bcm_rx_trap_t trap_type,
    char **description);

/**
* \brief
*  Return an error of trap is valid and no description is found.
* \param [in] unit               - Device ID
* \return
*   shr_error_e - Error Type
* \remark
*   * None
* \see
*   * None
*/
shr_error_e dnx_rx_trap_description_init_check_dispatch(
    int unit);

#endif /* RX_TRAP_MAP_DISPATCH_H_INCLUDED */

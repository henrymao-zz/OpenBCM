/** \file src/bcm/dnx/trunk/trunk_verify.c
 * 
 *  Internal DNX TRUNK verify APIs to be used in trunk module 
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
#define BSL_LOG_MODULE BSL_LS_BCMDNX_TRUNK

/*
 * Include files.
 * {
 */

#include <soc/sand/shrextend/shrextend_debug.h>
#include <shared/trunk.h>
#include <bcm/trunk.h>
#include <bcm/switch.h>
#include <bcm_int/dnx/auto_generated/dnx_switch_dispatch.h>
#include <bcm_int/dnx/auto_generated/dnx_stk_dispatch.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_trunk.h>
#include <bcm_int/dnx/algo/port/algo_port_mgmt.h>
#include <bcm_int/dnx/algo/algo_gpm.h>
#include <bcm_int/dnx/algo/trunk/algo_trunk.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_max_port.h>
#include <soc/dnx/dbal/auto_generated/dbal_defines_fields.h>
#include "trunk_utils.h"
#include "trunk_sw_db.h"
#include "trunk_temp_structs_to_skip_papi.h"
#include "trunk_verify.h"
#include "trunk_chm.h"

/*
 * }
 */

/*
 * DEFINEs
 * {
 */

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

/**
 * \brief - verify id_info is within valid range as defined by 
 *        user in soc properties.
 * 
 * \param [in] unit - unit number
 * \param [in] id_info - id info structure
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
dnx_trunk_id_info_t_verify(
    int unit,
    bcm_trunk_id_info_t * id_info)
{
    uint32 pool_index;
    uint32 group_index;
    uint32 nof_pools;
    uint32 nof_groups;

    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(id_info, _SHR_E_PARAM, "id_info");

    /** check pool is not larger than max pool */
    pool_index = id_info->pool_index;
    nof_pools = dnx_data_trunk.parameters.nof_pools_get(unit);
    if (pool_index >= nof_pools)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "provided pool index is too big, received %d when max possible value is %d\n",
                     pool_index, nof_pools - 1);
    }

    /** check group is not larger than max group */
    group_index = id_info->group_index;
    nof_groups = dnx_data_trunk.parameters.pool_info_get(unit, pool_index)->max_nof_groups_in_pool;
    if (group_index >= nof_groups)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "provided group index is too big, received %d when max possible value is %d\n",
                     group_index, nof_groups - 1);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * see header file
 */
shr_error_e
dnx_trunk_t_verify(
    int unit,
    bcm_trunk_t trunk_id)
{
    bcm_trunk_id_info_t id_info;
    SHR_FUNC_INIT_VARS(unit);
    if (!_SHR_TRUNK_ID_IS_VALID(trunk_id))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid trunk ID, need to use BCM_TRUNK_ID_SET to create trunk IDs");
    }

    SHR_IF_ERR_EXIT(dnx_trunk_utils_trunk_id_to_id_info_convert(unit, trunk_id, &id_info));
    SHR_IF_ERR_EXIT(dnx_trunk_id_info_t_verify(unit, &id_info));

exit:
    SHR_FUNC_EXIT;
}

/**
 * see header file
 */
shr_error_e
dnx_trunk_was_created_verify(
    int unit,
    bcm_trunk_id_info_t * id_info)
{
    int in_use;
    bcm_trunk_t trunk_id;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_trunk_sw_db_group_is_used_get(unit, id_info->pool_index, id_info->group_index, &in_use));
    if (in_use == 0)
    {
        SHR_IF_ERR_EXIT(dnx_trunk_utils_id_info_to_trunk_id_convert(unit, &trunk_id, id_info));
        SHR_ERR_EXIT(_SHR_E_PARAM, "given trunk ID 0x%x was never created\n"
                     "use bcm_trunk_create to create this trunk ID\n", trunk_id);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * see header file
 */
shr_error_e
dnx_trunk_can_fit_new_amount_of_members_verify(
    int unit,
    bcm_trunk_id_info_t * id_info,
    int new_nof_members)
{
    int max_group_size;

    SHR_FUNC_INIT_VARS(unit);

    max_group_size = dnx_data_trunk.parameters.pool_info_get(unit, id_info->pool_index)->max_nof_members_in_group;
    if (new_nof_members > max_group_size)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "given nof members %d is too big for pool %d\n",
                     new_nof_members, id_info->pool_index);
    }
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - verify function to check if a the psc_info is valid for c-lag psc
 *
 * \param [in] unit - unit number
 * \param [in] psc_info - psc_info
 * \param [in] id_info - id info
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
dnx_trunk_c_lag_psc_info_verify(
    int unit,
    bcm_trunk_psc_profile_info_t * psc_info,
    bcm_trunk_id_info_t * id_info)
{
    shr_error_e rv;
    int max_nof_members_in_profile;
    int max_group_is_support;
    int profile_type;
    int max_group_size;
    SHR_FUNC_INIT_VARS(unit);

    max_group_is_support = dnx_data_trunk.psc.feature_get(unit, dnx_data_trunk_psc_consistant_hashing_max_group);
    /** Devices which support "max_group_is_support" writes to dbal max_nof_members_in_profile-1.
     *  Other devices writes to dbal max_nof_members_in_profile. To use the same function for both
     *  needs to add one for none-support devices. */
    max_nof_members_in_profile =
        (max_group_is_support ==
         TRUE) ? psc_info->max_nof_members_in_profile : psc_info->max_nof_members_in_profile + 1;

    /** verify that max_nof_members_in_profile is valid */
    rv = dnx_trunk_c_lag_profile_type_get(unit, max_nof_members_in_profile, &profile_type);
    if (rv != _SHR_E_NONE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "unsupported number of member (%d) for existing profiles",
                     psc_info->max_nof_members_in_profile);
    }

    max_group_size = dnx_data_trunk.parameters.pool_info_get(unit, id_info->pool_index)->max_nof_members_in_group;
    if (psc_info->max_nof_members_in_profile > max_group_size)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "given psc_info->max_nof_members_in_profile %d is too big for pool %d\n",
                     psc_info->max_nof_members_in_profile, id_info->pool_index);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - verify function to check if a the psc_info is valid for user profile psc
 *
 * \param [in] unit - unit number
 * \param [in] psc_info - psc_info
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
dnx_trunk_user_profile_psc_info_verify(
    int unit,
    bcm_trunk_psc_profile_info_t * psc_info)
{
    uint8 is_allocated;
    SHR_FUNC_INIT_VARS(unit);

    /** check that psc_flag with ID is set */
    if (!_SHR_IS_FLAG_SET(psc_info->psc_flags, BCM_TRUNK_PSC_WITH_ID))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "USer Profile PSC requires to be set with ID\n");
    }

    /** verify profile ID is valid */
    SHR_IF_ERR_EXIT(dnx_algo_trunk_user_profile_is_allocated(unit, psc_info->profile_id, &is_allocated));
    if (!is_allocated)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "user profile ID %d is not allocated\n", psc_info->profile_id);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * see header file
 */
shr_error_e
dnx_trunk_psc_verify(
    int unit,
    int psc,
    bcm_trunk_psc_profile_info_t * psc_info,
    bcm_trunk_id_info_t * id_info)
{
    int psc_supported;
    char *str_ptr;
    SHR_FUNC_INIT_VARS(unit);

    switch (psc)
    {
        case BCM_TRUNK_PSC_PORTFLOW:
        {
            psc_supported = dnx_data_trunk.psc.feature_get(unit, dnx_data_trunk_psc_multiply_and_divide);
            str_ptr = "Multiply and Divide";
            break;
        }
        case BCM_TRUNK_PSC_SMOOTH_DIVISION:
        {
            psc_supported = dnx_data_trunk.psc.feature_get(unit, dnx_data_trunk_psc_smooth_division);
            str_ptr = "Smooth Division";
            break;
        }
        case BCM_TRUNK_PSC_C_LAG:
        {
            psc_supported = dnx_data_trunk.psc.feature_get(unit, dnx_data_trunk_psc_consistant_hashing);
            str_ptr = "C-lag (Consistent Hashing)";
            SHR_IF_ERR_EXIT(dnx_trunk_c_lag_psc_info_verify(unit, psc_info, id_info));
            break;
        }
        case BCM_TRUNK_PSC_USER_PROFILE:
        {
            /** User profile PSC uses C-Lag infra, so the blocking feature is  psc_consistant_hashing */
            psc_supported = dnx_data_trunk.psc.feature_get(unit, dnx_data_trunk_psc_consistant_hashing);
            str_ptr = "User Profile";
            SHR_IF_ERR_EXIT(dnx_trunk_user_profile_psc_info_verify(unit, psc_info));
            break;
        }
        default:
        {
            psc_supported = FALSE;
            str_ptr = "Unknown PSC";
            break;
        }
    }

    if (!psc_supported)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Given PSC %s (%d) is not supported for this unit(%d)\n", str_ptr, psc, unit);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * see header file
 */
shr_error_e
dnx_trunk_member_flags_verify(
    int unit,
    uint32 *flags)
{
    SHR_FUNC_INIT_VARS(unit);

    if (*flags &
        ~(BCM_TRUNK_MEMBER_INGRESS_DISABLE | BCM_TRUNK_MEMBER_EGRESS_DISABLE | BCM_TRUNK_MEMBER_SPA_WITH_ID |
          BCM_TRUNK_MEMBER_WITH_ID))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "API was used with invalid falgs\n");
    }

    if (*flags & (BCM_TRUNK_MEMBER_INGRESS_DISABLE))
    {
        LOG_WARN(BSL_LOG_MODULE,
                 (BSL_META_U(unit, "attampt to use legacy flag - BCM_TRUNK_MEMBER_INGRESS_DISABLE\n"
                             "changing them to relevant flag instead - BCM_TRUNK_MEMBER_EGRESS_DISABLE\n")));

        *flags &= ~BCM_TRUNK_MEMBER_INGRESS_DISABLE;
        *flags |= BCM_TRUNK_MEMBER_EGRESS_DISABLE;
    }

exit:
    SHR_FUNC_EXIT;
}

/** see header file */
shr_error_e
dnx_trunk_new_member_has_matching_header_type_verify(
    int unit,
    bcm_trunk_id_info_t * id_info,
    bcm_gport_t gport)
{
    uint32 trunk_in_header_type;
    uint32 trunk_out_header_type;
    dnx_algo_gpm_gport_phy_info_t gport_info;
    bcm_switch_control_key_t key;
    bcm_switch_control_info_t in_header_type;
    bcm_switch_control_info_t out_header_type;
    uint32 trunk_flags;
    SHR_FUNC_INIT_VARS(unit);

    /** if new member is not local to this FAP or lag is virtual, don't check header type */
    SHR_IF_ERR_EXIT(dnx_trunk_sw_db_group_flags_get(unit, id_info->pool_index, id_info->group_index, &trunk_flags));
    if (trunk_flags & BCM_TRUNK_FLAG_VP)
    {
        SHR_EXIT();
    }
    SHR_IF_ERR_EXIT(dnx_algo_gpm_gport_phy_info_get(unit, gport, DNX_ALGO_GPM_GPORT_TO_PHY_OP_NONE, &gport_info));
    if (0 == (gport_info.flags & DNX_ALGO_GPM_GPORT_INFO_F_IS_LOCAL_PORT))
    {
        SHR_EXIT();
    }

    /** get trunk header type from trunk_sw_db */
    SHR_IF_ERR_EXIT(dnx_trunk_sw_db_header_types_get
                    (unit, id_info->pool_index, id_info->group_index, &trunk_in_header_type, &trunk_out_header_type));

    /** get added member header types */
    key.type = bcmSwitchPortHeaderType;
    /** in direction*/
    key.index = 1;
    SHR_IF_ERR_EXIT(bcm_dnx_switch_control_indexed_port_get(unit, gport, key, &in_header_type));
    /** out direction*/
    key.index = 2;
    SHR_IF_ERR_EXIT(bcm_dnx_switch_control_indexed_port_get(unit, gport, key, &out_header_type));

    /** if either in or out header types of new member and trunk are different, fail */
    if ((in_header_type.value != trunk_in_header_type) || (out_header_type.value != trunk_out_header_type))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "new member header type is different from trunk header type\n"
                     "trunk header types      : IN 0x%x, OUT 0x%x\n"
                     "new_member header types : IN 0x%x, OUT 0x%x\n"
                     "change either the member or the trunk header type and try again\n",
                     trunk_in_header_type, trunk_out_header_type, in_header_type.value, out_header_type.value);
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * See .h file
 */
shr_error_e
dnx_trunk_modport_membership_verify(
    int unit,
    bcm_gport_t sysport,
    int member_count,
    bcm_trunk_member_t * member_array)
{
    int member_i;
    bcm_gport_t modport, modport_i;

    SHR_FUNC_INIT_VARS(unit);

    /** get modport from the given sysport */
    SHR_IF_ERR_EXIT(bcm_dnx_stk_sysport_gport_get(unit, sysport, &modport));

    /** iterate over members and find a match in physical mapping */
    for (member_i = 0; member_i < member_count; member_i++)
    {
        SHR_IF_ERR_EXIT(bcm_dnx_stk_sysport_gport_get(unit, member_array[member_i].gport, &modport_i));
        if (modport == modport_i)
        {
            SHR_EXIT();
        }
    }

    /** if we reached this point then it means that modport match wasn't found */
    SHR_ERR_EXIT(_SHR_E_PARAM, "given modport 0x%x is nod part of the member list", modport);

exit:
    SHR_FUNC_EXIT;
}

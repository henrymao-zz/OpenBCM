/** \file src/bcm/dnx/trunk/trunk_sw_db.c
 *
 *  This file contains the implementation of sw db functions of
 *  the trunk module.
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
#include "trunk_sw_db.h"
#include "trunk_chm.h"
#include "trunk_utils.h"
#include <soc/dnx/dnx_data/auto_generated/dnx_data_trunk.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_device.h>
#include <soc/dnx/swstate/auto_generated/types/trunk_types.h>
#include <soc/dnx/swstate/auto_generated/access/trunk_access.h>
#include <bcm_int/dnx/cmn/dnxcmn.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/access/algo_trunk_access.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_max_port.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_port.h>
#include <shared/shr_resmgr.h>
#include <bcm/switch.h>
#include <bcm/trunk.h>
#include <bcm/types.h>

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
 * \brief - initiate group in pool (part of swstate mechanism)
 *
 * \param [in] unit - unit number
 * \param [in] pool_index - pool index
 * \param [in] group_id - group index
 * \param [in] max_nof_members_per_group - max number of members
 *        in group
 * \return
 *      shr_error_e
 * \remark
 *   * additional fields in group structure are initiated to 0.
 * \see
 *   * None
 */
static shr_error_e
dnx_trunk_sw_db_group_init(
    int unit,
    int pool_index,
    int group_id,
    int max_nof_members_per_group)
{
    int nof_cores;
    dnx_algo_res_create_data_t data = { 0 };
    int ref_counter = 0;
    resource_tag_bitmap_utils_extra_arg_create_info_t extra_arg_create_info = {.data_per_entry_size =
            sizeof(ref_counter)
    };
    SHR_FUNC_INIT_VARS(unit);

    /** allocate members array */
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.alloc(unit, pool_index, group_id, max_nof_members_per_group));

    /** allocate pp ports array - each group can have upto one pp port per core. */
    nof_cores = dnx_data_device.general.nof_cores_get(unit);
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.pp_ports.alloc(unit, pool_index, group_id, nof_cores));

    /** create SPA member id resource manager */
    /** create resource manager for spa IDs in group if group is used */
    data.first_element = 0;
    data.nof_elements = dnx_data_trunk.parameters.pool_info_get(unit, pool_index)->max_nof_members_in_group;
    data.flags = RESOURCE_TAG_BITMAP_CREATE_DATA_PER_ENTRY;
    data.advanced_algorithm = DNX_ALGO_RESOURCE_ADVANCED_ALGORITHM_BASIC;
    sal_snprintf(data.name, DNX_ALGO_RES_MNGR_MAX_NAME_LENGTH, "spa_member_id_manager_pool_%d_group_%d", pool_index,
                 group_id);
    SHR_IF_ERR_EXIT(algo_trunk_db.pools.groups.
                    spa_id_manager.create(unit, pool_index, group_id, &data, &extra_arg_create_info));

    /** create tm_index resource manager according to max_nof_members provided */
    /** this is not the best way to do it.
     * i am forced to set nof elements here to max possible in group and not actual max.
     * the reason is that sw-state doesn't allow currently to destroy instances after the were created.
     * an alternative approach should those kind of things were allowed is to create when i know the actual
     * max size. and destroy whenever i reset the group to be created again when setting the group. */
    sal_memset(&data, 0, sizeof(data));
    data.first_element = 0;
    data.nof_elements = dnx_data_trunk.parameters.pool_info_get(unit, pool_index)->max_nof_members_in_group;
    data.flags = 0;
    data.advanced_algorithm = DNX_ALGO_RESOURCE_ADVANCED_ALGORITHM_BASIC;
    sal_snprintf(data.name, DNX_ALGO_RES_MNGR_MAX_NAME_LENGTH, "tm_index_manager_pool_%d_group_%d", pool_index,
                 group_id);
    SHR_IF_ERR_EXIT(algo_trunk_db.pools.groups.tm_index_manager.create(unit, pool_index, group_id, &data, NULL));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - initiate pool in trunk software database (part of
 *        swstate mechanism)
 *
 * \param [in] unit - unit number
 * \param [in] pool_index - pool index
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
dnx_trunk_sw_db_pool_init(
    int unit,
    int pool_index)
{
    const dnx_data_trunk_parameters_pool_info_t *pool_info;
    int groups_in_pool;
    int group_index;
    int members_in_group;

    SHR_FUNC_INIT_VARS(unit);

    /** get pool_info from DNX_DATA, relevant info is members per group and groups per pool. */
    pool_info = dnx_data_trunk.parameters.pool_info_get(unit, pool_index);
    groups_in_pool = pool_info->max_nof_groups_in_pool;
    members_in_group = pool_info->max_nof_members_in_group;

    /** allocate groups, loop over groups and initiate each group */
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.alloc(unit, pool_index, groups_in_pool));
    SHR_IF_ERR_EXIT(algo_trunk_db.pools.groups.alloc(unit, pool_index,
                                                     dnx_data_trunk.parameters.pool_info_get(unit,
                                                                                             pool_index)->
                                                     max_nof_groups_in_pool));
    for (group_index = 0; group_index < groups_in_pool; ++group_index)
    {
        SHR_IF_ERR_EXIT(dnx_trunk_sw_db_group_init(unit, pool_index, group_index, members_in_group));
    }

exit:
    SHR_FUNC_EXIT;
}

static void
trunk_system_port_entry_t_init(
    trunk_system_port_entry_t * entry)
{
    entry->flags = 0;
    entry->trunk_id = TRUNK_SW_DB_INVALID_TRUNK_ID;
}

/**
 * \brief - init trunk system port db in swstate
 *
 * \param [in] unit - unit number
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
dnx_trunk_sw_db_trunk_system_port_db_init(
    int unit)
{
    int max_nof_system_ports;
    trunk_system_port_entry_t invalid_entry;
    SHR_FUNC_INIT_VARS(unit);

    /** allocate system ports array and init them to Invalid values */
    max_nof_system_ports = dnx_data_device.general.max_nof_system_ports_get(unit);
    SHR_IF_ERR_EXIT(trunk_db.trunk_system_port_db.trunk_system_port_entries.alloc(unit));
    trunk_system_port_entry_t_init(&invalid_entry);
    SHR_IF_ERR_EXIT(trunk_db.trunk_system_port_db.trunk_system_port_entries.
                    range_fill(unit, 0, max_nof_system_ports, invalid_entry));
exit:
    SHR_FUNC_EXIT;
}

static void
profile_info_t_init(
    profile_info_t * entry)
{
    entry->psc_profile_type = TRUNK_INVALID_PROFILE;
    entry->max_nof_members = -1;
}

static void
user_profile_info_t_init(
    user_profile_info_t * entry)
{
    entry->assigned_psc_profile = -1;
    entry->ref_counter = 0;
}

/**
 * \brief - init trunk psc profiles info db in swstate
 *
 * \param [in] unit - unit number
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
dnx_trunk_sw_db_profile_info_db_init(
    int unit)
{
    int max_nof_profiles;
    profile_info_t profile_invalid_entry;
    user_profile_info_t user_profile_invalid_entry;
    SHR_FUNC_INIT_VARS(unit);

    /** allocate profile and user profile info arrays and init them to invalid values */
    SHR_IF_ERR_EXIT(trunk_db.psc_general_info.profile_info.alloc(unit));
    SHR_IF_ERR_EXIT(trunk_db.psc_general_info.user_profile_info.alloc(unit));
    max_nof_profiles = dnx_data_trunk.psc.consistant_hashing_nof_resources_get(unit);
    profile_info_t_init(&profile_invalid_entry);
    SHR_IF_ERR_EXIT(trunk_db.psc_general_info.
                    profile_info.range_fill(unit, 0, max_nof_profiles, profile_invalid_entry));
    user_profile_info_t_init(&user_profile_invalid_entry);
    SHR_IF_ERR_EXIT(trunk_db.psc_general_info.
                    user_profile_info.range_fill(unit, 0, max_nof_profiles, user_profile_invalid_entry));

exit:
    SHR_FUNC_EXIT;
}
#if (0)
/* { UNUSED */
/**
 * \brief - deinit trunk_db (free memory)
 *
 * \param [in] unit - unit number
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
dnx_trunk_sw_db_deinit(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    /*
     * sw state module deinit is done automatically at device deinit
     */

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}
/* } */
#endif
/**
 * \brief - initiate trunk software database (part of swstate
 *        mechanism)
 *
 * \param [in] unit - unit number
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
dnx_trunk_sw_db_init(
    int unit)
{
    uint8 trunk_sw_db_is_init;
    int nof_pools;
    int pool_index;

    SHR_FUNC_INIT_VARS(unit);

    /** Initiate swstate (sw_db) if it was not initiated yet. */
    SHR_IF_ERR_EXIT(trunk_db.is_init(unit, &trunk_sw_db_is_init));
    if (trunk_sw_db_is_init)
    {
        SHR_ERR_EXIT(_SHR_E_CONFIG, "trunk_db is already initiated \n");
    }
    SHR_IF_ERR_EXIT(trunk_db.init(unit));

    /** get nof_pools from DNX_DATA, allocate pools, loop over nof_pools and initiate each pool */
    nof_pools = dnx_data_trunk.parameters.nof_pools_get(unit);
    SHR_IF_ERR_EXIT(trunk_db.pools.alloc(unit, nof_pools));
    SHR_IF_ERR_EXIT(algo_trunk_db.pools.alloc(unit, nof_pools));
    for (pool_index = 0; pool_index < nof_pools; ++pool_index)
    {
        SHR_IF_ERR_EXIT(dnx_trunk_sw_db_pool_init(unit, pool_index));
    }

    /** init trunk_system_port_db */
    SHR_IF_ERR_EXIT(dnx_trunk_sw_db_trunk_system_port_db_init(unit));

    /** init profile info db*/
    SHR_IF_ERR_EXIT(dnx_trunk_sw_db_profile_info_db_init(unit));

exit:
    SHR_FUNC_EXIT;
}

void
dnx_trunk_sw_db_member_init(
    int unit,
    trunk_group_member_info_t * member)
{
    /** no flags  */
    member->flags = 0;
    /** invalid index */
    member->index = INVALID_TM_INDEX;
    /** invalid system port */
    member->system_port = dnx_data_device.general.invalid_system_port_get(unit);
    /** invalid spa member id */
    member->spa_member_id = INVALID_SPA_MEMBER_ID;
    /** invalid system port */
    member->protecting_system_port = dnx_data_device.general.invalid_system_port_get(unit);
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_group_reset(
    int unit,
    int pool_index,
    int group_index,
    int is_currently_created)
{
    trunk_group_member_info_t member_info;
    int nof_members_in_group;
    int nof_cores;

    SHR_FUNC_INIT_VARS(unit);

    /** init all group members to invalid */
    dnx_trunk_sw_db_member_init(unit, &member_info);
    nof_members_in_group = dnx_data_trunk.parameters.pool_info_get(unit, pool_index)->max_nof_members_in_group;
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.range_fill(unit, pool_index, group_index,
                                                             0, nof_members_in_group, member_info));

    if (is_currently_created)
    {
        /** init all pp ports to invalid */
        nof_cores = dnx_data_device.general.nof_cores_get(unit);
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.pp_ports.range_fill(unit, pool_index, group_index, 0, nof_cores,
                                                                  dnx_data_port.general.nof_pp_ports_get(unit)));
        /** set header type to invalid value */
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.
                        in_header_type.set(unit, pool_index, group_index, BCM_SWITCH_PORT_HEADER_TYPE_NONE));
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.
                        out_header_type.set(unit, pool_index, group_index, BCM_SWITCH_PORT_HEADER_TYPE_NONE));

        /** set flags to 0 */
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.flags.set(unit, pool_index, group_index, 0));

        /** set master trunk id to 0 */
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.
                        master_trunk_id.set(unit, pool_index, group_index, TRUNK_SW_DB_INVALID_TRUNK_ID));
    }

    /** init the other group global attributes */
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.last_member_added_index.set(unit, pool_index, group_index, -1));
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.psc.set(unit, pool_index, group_index, -1));
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.psc_profile_id.set(unit, pool_index, group_index, -1));
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.nof_members.set(unit, pool_index, group_index, 0));

    /** free all spa IDs */
    SHR_IF_ERR_EXIT(algo_trunk_db.pools.groups.spa_id_manager.clear(unit, pool_index, group_index));

    /** free all tm indexes */
    SHR_IF_ERR_EXIT(algo_trunk_db.pools.groups.tm_index_manager.clear(unit, pool_index, group_index));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_trunk_sw_db_group_res_manager_size_limit(
    int unit,
    int pool,
    int group,
    int max_nof_members)
{
    int nof_elements_to_alloc;
    SHR_FUNC_INIT_VARS(unit);

    /** fill the last members in the resource manager so that only max_nof_memebers remain free */
    /** this is done because dynamically destroying and creating again the resource manager is not allowed in current infra implementation */
    nof_elements_to_alloc =
        dnx_data_trunk.parameters.pool_info_get(unit, pool)->max_nof_members_in_group - max_nof_members;
    if (nof_elements_to_alloc > 0)
    {
        SHR_IF_ERR_EXIT(algo_trunk_db.pools.groups.
                        tm_index_manager.allocate_several(unit, pool, group, SHR_RES_ALLOC_WITH_ID,
                                                          nof_elements_to_alloc, NULL, &max_nof_members));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_trunk_system_port_db_set(
    int unit,
    uint32 system_port,
    bcm_trunk_t trunk_id,
    uint32 flags)
{
    trunk_system_port_entry_t entry;
    SHR_FUNC_INIT_VARS(unit);

    /** update entry to sw db */
    entry.trunk_id = trunk_id;
    entry.flags = flags;
    SHR_IF_ERR_EXIT(trunk_db.trunk_system_port_db.trunk_system_port_entries.set(unit, system_port, &entry));

exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_trunk_system_port_db_get(
    int unit,
    uint32 system_port,
    bcm_trunk_t * trunk_id,
    uint32 *flags)
{
    trunk_system_port_entry_t entry;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(trunk_db.trunk_system_port_db.trunk_system_port_entries.get(unit, system_port, &entry));
    *trunk_id = entry.trunk_id;
    *flags = entry.flags;

exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_group_pp_port_core_bitmap_get(
    int unit,
    int pool,
    int group,
    uint32 *current_core_bitmap)
{
    int core;
    uint32 pp_port;
    uint32 core_bit;

    SHR_FUNC_INIT_VARS(unit);

    *current_core_bitmap = 0;
    core_bit = 1;
    DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core)
    {
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.pp_ports.get(unit, pool, group, core, &pp_port));
        if (pp_port != dnx_data_port.general.nof_pp_ports_get(unit))
        {
            *current_core_bitmap |= core_bit;
        }
        core_bit <<= 1;
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_group_pp_port_set(
    int unit,
    int pool_index,
    int group_index,
    int core,
    uint32 pp_port)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.pp_ports.set(unit, pool_index, group_index, core, pp_port));
exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_group_pp_port_get(
    int unit,
    int pool_index,
    int group_index,
    int core,
    uint32 *pp_port)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.pp_ports.get(unit, pool_index, group_index, core, pp_port));
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - find next free member in group, if group is full -
 *        fail
 *
 * \param [in] unit - uint number
 * \param [in] pool - pool index
 * \param [in] group - group index
 * \param [in] free_member - returned free member index
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
dnx_trunk_sw_db_next_free_member_find(
    int unit,
    int pool,
    int group,
    int *free_member)
{
    int max_nof_members_in_group;
    int remaining_members_to_check;
    int last_added;
    uint32 system_port;
    int invalid_system_port;
    int member;
    SHR_FUNC_INIT_VARS(unit);

    max_nof_members_in_group = remaining_members_to_check =
        dnx_data_trunk.parameters.pool_info_get(unit, pool)->max_nof_members_in_group;
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.last_member_added_index.get(unit, pool, group, &last_added));
    invalid_system_port = dnx_data_device.general.invalid_system_port_get(unit);
    /*
     * the members in the trunk sw db are not necessarily consequential, therefore we need to iterate over all the
     * members. as an optimization it is suffice to do so until we iterated over the remaining members
     */
    for (member = last_added + 1; remaining_members_to_check > 0; ++member, --remaining_members_to_check)
    {
        member %= max_nof_members_in_group;
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.system_port.get(unit, pool, group, member, &system_port));
        if (system_port == invalid_system_port)
        {
            *free_member = member;
            SHR_EXIT();
        }
    }
    SHR_ERR_EXIT(_SHR_E_NOT_FOUND, "trunk group %d in pool %d is full\n", group, pool);
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_trunk_sw_db_spa_ref_increment(
    int unit,
    int pool,
    int group,
    int spa_id)
{
    int spa_id_ref_counter;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(algo_trunk_db.pools.groups.
                    spa_id_manager.data_per_entry_get(unit, pool, group, spa_id, &spa_id_ref_counter));
    ++spa_id_ref_counter;
    SHR_IF_ERR_EXIT(algo_trunk_db.pools.groups.
                    spa_id_manager.data_per_entry_set(unit, pool, group, spa_id, &spa_id_ref_counter));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_trunk_sw_db_spa_ref_decrement(
    int unit,
    int pool,
    int group,
    int spa_id)
{
    int spa_id_ref_counter;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(algo_trunk_db.pools.groups.
                    spa_id_manager.data_per_entry_get(unit, pool, group, spa_id, &spa_id_ref_counter));
    --spa_id_ref_counter;
    SHR_IF_ERR_EXIT(algo_trunk_db.pools.groups.
                    spa_id_manager.data_per_entry_set(unit, pool, group, spa_id, &spa_id_ref_counter));

exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_member_add(
    int unit,
    int pool,
    int group,
    trunk_group_member_info_t * member_info,
    int *member_index)
{
    bcm_trunk_t trunk_id;
    uint32 current_flags;
    uint32 sys_port;
    int added_member_is_protecting;
    int existing_member_is_enabled = 0;
    int enabling_a_disabled_member = 0;
    int first;
    int last;
    int count;
    int free_member = 0;
    int nof_members;
    int spa_id_ref_counter;
    uint32 current_member_flags = 0;
    uint32 masked_flags = BCM_TRUNK_MEMBER_WITH_PROTECTION;
    uint32 flags_that_should_not_change;
    uint32 flags_that_should_change;
    uint32 updated_flags;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_trunk_sw_db_member_in_group_find(unit, pool, group, member_info, &first, &last, &count));
    sys_port = BCM_GPORT_SYSTEM_PORT_ID_GET(member_info->system_port);
    SHR_IF_ERR_EXIT(dnx_trunk_sw_db_trunk_system_port_db_get(unit, sys_port, &trunk_id, &current_flags));

    /** resolve spa member id */
    if (count != 0)
    {
        /** if this is not the first instance of this member, get first member info and copy spa_id to current member */
        trunk_group_member_info_t first_instance_info;
        SHR_IF_ERR_EXIT(dnx_trunk_sw_db_member_get(unit, pool, group, first, &first_instance_info));
        member_info->spa_member_id = first_instance_info.spa_member_id;
        existing_member_is_enabled = (first_instance_info.index >= 0);
    }
    else
    {
        uint32 flags = RESOURCE_TAG_BITMAP_ALLOC_DATA_PER_ENTRY;
        resource_tag_bitmap_utils_extra_arg_alloc_info_t alloc_info = { 0 };
        spa_id_ref_counter = 0;
        alloc_info.data = &spa_id_ref_counter;
        /** alloc a member in resource manager and assign it to this member */
        if (member_info->flags & BCM_TRUNK_MEMBER_SPA_WITH_ID)
        {
            /** user requested spa_id */
            flags |= DNX_ALGO_RES_ALLOCATE_WITH_ID;
        }
        SHR_IF_ERR_EXIT(algo_trunk_db.pools.groups.spa_id_manager.allocate_single(unit, pool, group, flags, &alloc_info,
                                                                                  &member_info->spa_member_id));
    }

    /** identify case of enabling an existing member */
    enabling_a_disabled_member = ((count == 1) &&
                                  (current_flags & BCM_TRUNK_MEMBER_EGRESS_DISABLE) &&
                                  ((member_info->index == INVALID_TM_INDEX_BUT_NEED_ALLOCATE_ONE)
                                   || (member_info->index >= 0)));
    if (enabling_a_disabled_member)
    {
        /** update current member flag with relevant info */
        trunk_group_member_info_t first_instance_info;
        SHR_IF_ERR_EXIT(dnx_trunk_sw_db_member_get(unit, pool, group, first, &first_instance_info));
        current_member_flags = first_instance_info.flags;
        member_info->protecting_system_port = first_instance_info.protecting_system_port;
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_trunk_sw_db_spa_ref_increment(unit, pool, group, member_info->spa_member_id));
    }
    /** update member flags to sw_db, some flags should be ignored by this update */
    /** MEMBER_WITH_PROTECTION flag should be ignored, it is updated from external context */
    flags_that_should_not_change = current_member_flags & masked_flags;
    flags_that_should_change = member_info->flags & (~masked_flags);
    updated_flags = flags_that_should_not_change | flags_that_should_change;
    member_info->flags = updated_flags;

    /** resolve TM-index if required */
    if ((member_info->index == INVALID_TM_INDEX_TO_INDICATE_DISABLED_MEMBER)
        || (member_info->index == INVALID_TM_INDEX_TO_INDICATE_MEMBER_IS_ONLY_PROTECTING))
    {
        /** Invalid tm index, nothing to do */
        LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "Invalid TM index. no need to allocate a TM index in DB\n")));
    }
    else if (member_info->index == INVALID_TM_INDEX_BUT_NEED_ALLOCATE_ONE)
    {
        /** Need to allocate on your own and return allocated TM index */
        int allocated_tm_index = -1;
        SHR_IF_ERR_EXIT(algo_trunk_db.pools.groups.
                        tm_index_manager.allocate_single(unit, pool, group, 0, NULL, &allocated_tm_index));
        member_info->index = allocated_tm_index;
    }
    else
    {
        /** Need to allocate with ID received TM index */
        SHR_IF_ERR_EXIT(algo_trunk_db.pools.groups.
                        tm_index_manager.allocate_single(unit, pool, group, SHR_RES_ALLOC_WITH_ID, NULL,
                                                         &member_info->index));
    }

    /**  this table described the logic of adding a new member to the sw_db
     *   skip - means no action is required from this db perspective
     *   N/A  - means scenario is not valid and verification should prevent from reaching this state
     *
     *                                       new member
     *                               +-------------------------+
     *                               |                         |
     *           +------------+------+------+------------+-----+------+
     *           |            | protecting  |  disabled  |  regular   |
     *           +------------+-------------+------------+------------+
     *         +-+empty       |  Full add   |  Full add  |  Full add  |
     *         | +------------+-------------+------------+------------+
     * exiting | |protecting  |  Skip       |  Update    |  Update    |
     * member  | +------------+-------------+------------+------------+
     *         | |disabled    |  Skip       |  N/A       |  Update    |
     *         | +------------+-------------+------------+------------+
     *         +-+regular     |  Skip       |  N/A       |  Full add  |
     *           +------------+-------------+------------+------------+
     */
    added_member_is_protecting = (member_info->index == INVALID_TM_INDEX_TO_INDICATE_MEMBER_IS_ONLY_PROTECTING);

    if (count == 0)
    {
        /** add to member to sw_db */
        SHR_IF_ERR_EXIT(dnx_trunk_sw_db_next_free_member_find(unit, pool, group, &free_member));
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.set(unit, pool, group, free_member, member_info));
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.nof_members.get(unit, pool, group, &nof_members));
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.nof_members.set(unit, pool, group, nof_members + 1));
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.last_member_added_index.set(unit, pool, group, free_member));

        /** add system port to sys_port_db */
        BCM_TRUNK_ID_SET(trunk_id, pool, group);
        SHR_IF_ERR_EXIT(dnx_trunk_sw_db_trunk_system_port_db_set(unit, sys_port, trunk_id, member_info->flags));

        /** return added index */
        *member_index = free_member;
    }
    else if (added_member_is_protecting)
    {
        *member_index = first;
    }
    else
    {
        if (existing_member_is_enabled)
        {
            /** add to member to sw_db */
            SHR_IF_ERR_EXIT(dnx_trunk_sw_db_next_free_member_find(unit, pool, group, &free_member));
            SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.set(unit, pool, group, free_member, member_info));
            SHR_IF_ERR_EXIT(trunk_db.pools.groups.nof_members.get(unit, pool, group, &nof_members));
            SHR_IF_ERR_EXIT(trunk_db.pools.groups.nof_members.set(unit, pool, group, nof_members + 1));
            SHR_IF_ERR_EXIT(trunk_db.pools.groups.last_member_added_index.set(unit, pool, group, free_member));

            /** return added index */
            *member_index = free_member;
        }
        else
        {
            /** update member to sw_db */
            SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.set(unit, pool, group, first, member_info));

            /** update flags in sys_port_db */
            SHR_IF_ERR_EXIT(trunk_db.trunk_system_port_db.trunk_system_port_entries.
                            flags.set(unit, sys_port, member_info->flags));
            /** The existing members index should be used */
            *member_index = first;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_member_get(
    int unit,
    int pool,
    int group,
    int member,
    trunk_group_member_info_t * member_info)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.get(unit, pool, group, member, member_info));
exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_member_set(
    int unit,
    int pool,
    int group,
    int member,
    trunk_group_member_info_t * member_info)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.set(unit, pool, group, member, member_info));
exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_is_last_spa_ref(
    int unit,
    int pool,
    int group,
    int member,
    int *is_last_ref)
{
    int spa_id = -1;
    int spa_id_ref_counter;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.spa_member_id.get(unit, pool, group, member, &spa_id));
    SHR_IF_ERR_EXIT(algo_trunk_db.pools.groups.spa_id_manager.data_per_entry_get(unit, pool, group, spa_id,
                                                                                 &spa_id_ref_counter));
    *is_last_ref = (spa_id_ref_counter == 1);
exit:
    SHR_FUNC_EXIT;
}

/**
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_entry_remove(
    int unit,
    int pool,
    int group,
    int member,
    int is_last_replication,
    int remove_protection)
{
    trunk_group_member_info_t empty_member_info;
    trunk_group_member_info_t removed_member_info;
    uint32 gport_sys_port;
    int nof_members;
    int spa_id_ref_counter;
    SHR_FUNC_INIT_VARS(unit);

    /** get gport_system_port to access the trunk sys port db */
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.system_port.get(unit, pool, group, member, &gport_sys_port));

    /** get removed entry info */
    SHR_IF_ERR_EXIT(dnx_trunk_sw_db_member_get(unit, pool, group, member, &removed_member_info));

    /** clear tm-index from resource manager */
    /** if its invalid, it was already removed, all negative values are invalid */
    /** when just removing protection this should be skipped */

    if ((!remove_protection) && (removed_member_info.index >= 0))
    {
        SHR_IF_ERR_EXIT(algo_trunk_db.pools.groups.
                        tm_index_manager.free_single(unit, pool, group, removed_member_info.index, NULL));
    }

    SHR_IF_ERR_EXIT(dnx_trunk_sw_db_spa_ref_decrement(unit, pool, group, removed_member_info.spa_member_id));
    SHR_IF_ERR_EXIT(algo_trunk_db.pools.groups.
                    spa_id_manager.data_per_entry_get(unit, pool, group, removed_member_info.spa_member_id,
                                                      &spa_id_ref_counter));

    if (!is_last_replication && !remove_protection)
    {
        /** overrun entry in member sw db with an empty one */
        dnx_trunk_sw_db_member_init(unit, &empty_member_info);
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.set(unit, pool, group, member, &empty_member_info));

        /** update nof members */
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.nof_members.get(unit, pool, group, &nof_members));
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.nof_members.set(unit, pool, group, nof_members - 1));
    }
    else
    {
        if (spa_id_ref_counter == 0)
        {
            trunk_system_port_entry_t entry;
            uint32 sys_port;

            /** overrun entry in member sw db with an empty one */
            dnx_trunk_sw_db_member_init(unit, &empty_member_info);
            SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.set(unit, pool, group, member, &empty_member_info));

            /** update nof members */
            SHR_IF_ERR_EXIT(trunk_db.pools.groups.nof_members.get(unit, pool, group, &nof_members));
            SHR_IF_ERR_EXIT(trunk_db.pools.groups.nof_members.set(unit, pool, group, nof_members - 1));

            /** when the last replication of the member was removed, need to clear it from the system port db */
            trunk_system_port_entry_t_init(&entry);
            sys_port = BCM_GPORT_SYSTEM_PORT_ID_GET(gport_sys_port);
            SHR_IF_ERR_EXIT(trunk_db.trunk_system_port_db.trunk_system_port_entries.set(unit, sys_port, &entry));

            /** and clear its spa member id from DB */
            SHR_IF_ERR_EXIT(algo_trunk_db.pools.groups.
                            spa_id_manager.free_single(unit, pool, group, removed_member_info.spa_member_id, NULL));
        }
        else if (!remove_protection)
        {
            uint32 sys_port;
            /** update entry to protecting entry */
            /** change its index to reserved index for protecting members */
            SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.index.set(unit, pool, group, member,
                                                                    INVALID_TM_INDEX_TO_INDICATE_MEMBER_IS_ONLY_PROTECTING));
            /** clear member flags */
            SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.flags.set(unit, pool, group, member, 0));
            /** clear member flag in sys_port_db */
            sys_port = BCM_GPORT_SYSTEM_PORT_ID_GET(removed_member_info.system_port);
            SHR_IF_ERR_EXIT(trunk_db.trunk_system_port_db.trunk_system_port_entries.flags.set(unit, sys_port, 0));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - search a trunk group for the member with the largest
 *        TM index
 *
 * \param [in] unit - unit number
 * \param [in] pool - pool index
 * \param [in] group - group index
 * \param [in] member_with_greatest_tm_index - returned index of
 *        member with greatest TM index
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
dnx_trunk_sw_db_member_with_greatest_tm_index_find(
    int unit,
    int pool,
    int group,
    int *member_with_greatest_tm_index)
{
    int max_nof_members;
    int member;
    int max_tm_index = INVALID_TM_INDEX;
    int tm_index;
    SHR_FUNC_INIT_VARS(unit);
    *member_with_greatest_tm_index = -1;
    max_nof_members = dnx_data_trunk.parameters.pool_info_get(unit, pool)->max_nof_members_in_group;
    for (member = 0; member < max_nof_members; ++member)
    {
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.index.get(unit, pool, group, member, &tm_index));
        if (tm_index > max_tm_index)
        {
            max_tm_index = tm_index;
            *member_with_greatest_tm_index = member;
        }
    }
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - swap TM indexes of the member with the largest one
 *        and the member that you want to delete when required (based on PSC).
 *
 * \param [in] unit - unit number
 * \param [in] pool - pool index
 * \param [in] group - group index
 * \param [in] member - index of the member you want to delete
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
dnx_trunk_tm_indexes_to_allow_deleting_align(
    int unit,
    int pool,
    int group,
    int member)
{
    int member_to_swap = -1;
    int index;
    int max_index;
    int psc;
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.psc.get(unit, pool, group, &psc));

    if ((psc == BCM_TRUNK_PSC_C_LAG) || (psc == BCM_TRUNK_PSC_USER_PROFILE))
    {
        /** if PSC is C-Lag or User Profile it is forbidden to change TM index of used member. */
        /** also the whole process of aligning members before deletion is not required */
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.index.get(unit, pool, group, member, &index));
    if (index < 0)
    {
        /** if member has tm_index < 0 it means that a member will not be actually deleted, so no need to align anything */
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(dnx_trunk_sw_db_member_with_greatest_tm_index_find(unit, pool, group, &member_to_swap));
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.index.get(unit, pool, group, member_to_swap, &max_index));
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.index.get(unit, pool, group, member, &index));

    SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.index.set(unit, pool, group, member_to_swap, index));
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.index.set(unit, pool, group, member, max_index));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - disable given member in both sw db and system port
 *        db
 *
 * \param [in] unit - unit number
 * \param [in] pool - pool index
 * \param [in] group - group index
 * \param [in] member - index of the member to disable
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
dnx_trunk_member_disable(
    int unit,
    int pool,
    int group,
    int member)
{
    uint32 gport_sys_port;
    uint32 sys_port;
    int disabled_member_tm_index;
    uint32 member_flags;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.index.get(unit, pool, group, member, &disabled_member_tm_index));
    if (disabled_member_tm_index < 0)
    {
        /** if member has tm_index < 0 it means that the member is not really active (either disabled or only protecting).
         *  in other words - this is a sanity check, if we got here, something is wrong, the verify functions should've kicked us out before hand
         */
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "invalid TM index indicated, cannot disable a non active member\n");
    }
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.system_port.get(unit, pool, group, member, &gport_sys_port));
    sys_port = BCM_GPORT_SYSTEM_PORT_ID_GET(gport_sys_port);
    /** get modify set member flags */
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.flags.get(unit, pool, group, member, &member_flags));
    member_flags |= BCM_TRUNK_MEMBER_EGRESS_DISABLE;
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.flags.set(unit, pool, group, member, member_flags));
    /** set index to disabled member */
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.
                    index.set(unit, pool, group, member, INVALID_TM_INDEX_TO_INDICATE_DISABLED_MEMBER));
    /** get modify set member flags */
    SHR_IF_ERR_EXIT(trunk_db.trunk_system_port_db.trunk_system_port_entries.flags.get(unit, sys_port, &member_flags));
    member_flags |= BCM_TRUNK_MEMBER_EGRESS_DISABLE;
    SHR_IF_ERR_EXIT(trunk_db.trunk_system_port_db.trunk_system_port_entries.
                    flags.set(unit, sys_port, BCM_TRUNK_MEMBER_EGRESS_DISABLE));
    /** free tm index */
    SHR_IF_ERR_EXIT(algo_trunk_db.pools.groups.
                    tm_index_manager.free_single(unit, pool, group, disabled_member_tm_index, NULL));
exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_protecting_member_delete(
    int unit,
    int pool,
    int group,
    int member)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_trunk_sw_db_entry_remove(unit, pool, group, member, DONT_CARE, TRUE));
exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_member_delete(
    int unit,
    int pool,
    int group,
    int member,
    int nof_replications,
    int need_disable_instead_of_deleting)
{
    uint32 curr_flags;
    int disabled_member;
    int deleting_a_regular_member;
    int deleting_a_disabled_member;
    int disabling_a_regular_member;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.flags.get(unit, pool, group, member, &curr_flags));
    disabled_member = (curr_flags & BCM_TRUNK_MEMBER_EGRESS_DISABLE);
    deleting_a_regular_member = !need_disable_instead_of_deleting && !disabled_member;
    deleting_a_disabled_member = !need_disable_instead_of_deleting && disabled_member;
    disabling_a_regular_member = need_disable_instead_of_deleting && !disabled_member;

    /*
     * there are 3 valid scenarios at this point. deleting a disabled member, deleting a regular member and disabling
     * a regular member. every attempt to perform other actions should have already been blocked from above and so we
     * don't check for it now. additional assumptions are that in case of disabling a regular member we can have only
     * a single replication from it - this is also verified in calling functions. prior to deleting a member from the
     * sw db, we must align it in such a way that we're deleting the member with greatest TM index - meaning that we
     * are actually required in certain cases to swap between member's TM index.
     */
    if (deleting_a_disabled_member)
    {
        SHR_IF_ERR_EXIT(dnx_trunk_sw_db_entry_remove(unit, pool, group, member, TRUE, FALSE));
    }
    else if (deleting_a_regular_member)
    {
        int is_last_replication = (nof_replications == 1) ? TRUE : FALSE;
        SHR_IF_ERR_EXIT(dnx_trunk_tm_indexes_to_allow_deleting_align(unit, pool, group, member));
        SHR_IF_ERR_EXIT(dnx_trunk_sw_db_entry_remove(unit, pool, group, member, is_last_replication, FALSE));
    }
    else if (disabling_a_regular_member)
    {
        SHR_IF_ERR_EXIT(dnx_trunk_tm_indexes_to_allow_deleting_align(unit, pool, group, member));
        SHR_IF_ERR_EXIT(dnx_trunk_member_disable(unit, pool, group, member));
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_CONFIG, "input doesn't fit any valid configuration\n");
    }
exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_group_last_member_added_set(
    int unit,
    int pool,
    int group,
    int last_member_added)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.last_member_added_index.set(unit, pool, group, last_member_added));
exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_member_in_group_find(
    int unit,
    int pool,
    int group,
    trunk_group_member_info_t * member_info,
    int *first_replication_index,
    int *last_replication_index,
    int *count)
{
    trunk_group_member_info_t curr_member_info;
    int max_nof_members;
    int member;
    int first_rep_tm_index;
    int last_rep_tm_index;

    SHR_FUNC_INIT_VARS(unit);
    max_nof_members = dnx_data_trunk.parameters.pool_info_get(unit, pool)->max_nof_members_in_group;
    *first_replication_index = *last_replication_index = max_nof_members;
    first_rep_tm_index = max_nof_members;
    last_rep_tm_index = INVALID_TM_INDEX;
    *count = 0;
    for (member = 0; member < max_nof_members; ++member)
    {
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.get(unit, pool, group, member, &curr_member_info));
        if (curr_member_info.system_port == member_info->system_port)
        {
            ++(*count);
            if (curr_member_info.index > last_rep_tm_index)
            {
                last_rep_tm_index = curr_member_info.index;
                *last_replication_index = member;
            }
            if (curr_member_info.index < first_rep_tm_index)
            {
                first_rep_tm_index = curr_member_info.index;
                *first_replication_index = member;
            }
        }
    }
exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_member_in_group_per_criteria_find(
    int unit,
    int pool,
    int group,
    trunk_group_member_info_t * member_info,
    uint32 member_flags_mask,
    int arr_size,
    int *found_index_arr,
    int *count)
{
    int system_port_criterion_is_valid = 0;
    int protection_criterion_is_valid = 0;
    int index_criterion_is_valid = 0;
    int spa_member_id_criterion_is_valid = 0;
    int member_flags_criterion_is_valid = 0;
    int invalid_system_port;
    int max_nof_members;
    trunk_group_member_info_t curr_member_info;
    SHR_FUNC_INIT_VARS(unit);

    /** setup match criteria */
    invalid_system_port = dnx_data_device.general.invalid_system_port_get(unit);
    if (member_info->system_port != invalid_system_port)
    {
        system_port_criterion_is_valid = TRUE;
    }
    if (member_info->index != INVALID_TM_INDEX)
    {
        index_criterion_is_valid = TRUE;
    }
    if (member_info->spa_member_id != INVALID_SPA_MEMBER_ID)
    {
        spa_member_id_criterion_is_valid = TRUE;
    }
    if (member_info->protecting_system_port != invalid_system_port)
    {
        protection_criterion_is_valid = TRUE;
    }
    if (member_flags_mask != 0)
    {
        /** flag bits that are not set in the mask are ignored in the comparison, thus if the mask is 0 all flags are ignored in the comparison */
        member_flags_criterion_is_valid = TRUE;
    }

    max_nof_members = dnx_data_trunk.parameters.pool_info_get(unit, pool)->max_nof_members_in_group;
    *count = 0;
    for (int member = 0; member < max_nof_members; ++member)
    {
        /** Check match criteria, continue to next member on first failure to match */
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.get(unit, pool, group, member, &curr_member_info));
        /** Skip empty entries */
        if (curr_member_info.system_port == invalid_system_port)
        {
            continue;
        }
        if ((system_port_criterion_is_valid) && (curr_member_info.system_port != member_info->system_port))
        {
            continue;
        }
        if ((index_criterion_is_valid) && (curr_member_info.index != member_info->index))
        {
            continue;
        }
        if ((spa_member_id_criterion_is_valid) && (curr_member_info.spa_member_id != member_info->spa_member_id))
        {
            continue;
        }
        if ((protection_criterion_is_valid)
            && (curr_member_info.protecting_system_port != member_info->protecting_system_port))
        {
            continue;
        }
        if (member_flags_criterion_is_valid)
        {
            if ((curr_member_info.flags & member_flags_mask) != (member_info->flags & member_flags_mask))
            {
                continue;
            }
        }

        /** add member's sw db index to found_index_arr if there's available place */
        if (*count < arr_size)
        {
            found_index_arr[*count] = member;
        }
        /** increase count */
        *count += 1;
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_spa_member_id_in_group_find(
    int unit,
    int pool,
    int group,
    trunk_group_member_info_t * member_info)
{
    trunk_group_member_info_t curr_member_info;
    int max_nof_members;
    int member;
    int match_found = 0;

    SHR_FUNC_INIT_VARS(unit);

    max_nof_members = dnx_data_trunk.parameters.pool_info_get(unit, pool)->max_nof_members_in_group;
    for (member = 0; member < max_nof_members; ++member)
    {
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.get(unit, pool, group, member, &curr_member_info));
        if (curr_member_info.spa_member_id == member_info->spa_member_id)
        {
            *member_info = curr_member_info;
            match_found = 1;
            break;
        }
    }

    if (!match_found)
    {
        /** if not found set member info to invalid values and return NOT FOUND */
        dnx_trunk_sw_db_member_init(unit, member_info);
        SHR_ERR_EXIT(_SHR_E_NOT_FOUND, "member with provided spa member id was not found");
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_nof_members_in_group_get(
    int unit,
    int pool,
    int group,
    int *count)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.nof_members.get(unit, pool, group, count));
exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_group_is_used_get(
    int unit,
    int pool,
    int group,
    int *is_used)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.in_use.get(unit, pool, group, is_used));
exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_group_is_used_set(
    int unit,
    int pool,
    int group,
    int is_used)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.in_use.set(unit, pool, group, is_used));

exit:
    SHR_FUNC_EXIT;
}

/** see header file */
shr_error_e
dnx_trunk_sw_db_header_types_set(
    int unit,
    int pool,
    int group,
    uint32 in_header_type,
    uint32 out_header_type)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.in_header_type.set(unit, pool, group, in_header_type));
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.out_header_type.set(unit, pool, group, out_header_type));
exit:
    SHR_FUNC_EXIT;
}

/** see header file */
shr_error_e
dnx_trunk_sw_db_header_types_get(
    int unit,
    int pool,
    int group,
    uint32 *in_header_type,
    uint32 *out_header_type)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.in_header_type.get(unit, pool, group, in_header_type));
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.out_header_type.get(unit, pool, group, out_header_type));
exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_group_psc_get(
    int unit,
    int pool,
    int group,
    int *psc,
    int *psc_profile_id)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.psc.get(unit, pool, group, psc));
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.psc_profile_id.get(unit, pool, group, psc_profile_id));

exit:
    SHR_FUNC_EXIT;
}

/** expectations are that this will update the sw db with the
 *  bcm encoded PSC, the psc_profile_id is relevant for all
 *  PSC, including SMD and M&D, in those cases the profile
 *  will actually represent (number_of_enabled_members - 1) */
/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_group_psc_set(
    int unit,
    int pool,
    int group,
    int psc,
    int psc_profile_id)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.psc.set(unit, pool, group, psc));
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.psc_profile_id.set(unit, pool, group, psc_profile_id));

exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_enabled_members_get(
    int unit,
    int pool,
    int group,
    int arr_size,
    int *nof_enabled_members,
    int *member_index_arr)
{
    trunk_group_member_info_t member_info;
    int member;
    int max_nof_members;
    int invalid_system_port;
    SHR_FUNC_INIT_VARS(unit);
    *nof_enabled_members = 0;
    max_nof_members = dnx_data_trunk.parameters.pool_info_get(unit, pool)->max_nof_members_in_group;
    invalid_system_port = dnx_data_device.general.invalid_system_port_get(unit);
    for (member = 0; member < max_nof_members; ++member)
    {
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.get(unit, pool, group, member, &member_info));
        if ((member_info.system_port == invalid_system_port || member_info.index < 0))
        {
            continue;
        }

        /** if member is enabled, count it */
        if ((member_info.flags & BCM_TRUNK_MEMBER_EGRESS_DISABLE) == 0)
        {
            if (*nof_enabled_members < arr_size)
            {
                member_index_arr[*nof_enabled_members] = member;
            }
            ++(*nof_enabled_members);
        }

    }
exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_nof_enabled_members_get(
    int unit,
    int pool,
    int group,
    int *nof_enabled_members)
{
    trunk_group_member_info_t member_info;
    int member;
    int max_nof_members;
    int invalid_system_port;
    SHR_FUNC_INIT_VARS(unit);
    *nof_enabled_members = 0;
    max_nof_members = dnx_data_trunk.parameters.pool_info_get(unit, pool)->max_nof_members_in_group;
    invalid_system_port = dnx_data_device.general.invalid_system_port_get(unit);
    for (member = 0; member < max_nof_members; ++member)
    {
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.get(unit, pool, group, member, &member_info));
        if ((member_info.system_port == invalid_system_port || member_info.index < 0))
        {
            continue;
        }

        /** if member is enabled, count it */
        if ((member_info.flags & BCM_TRUNK_MEMBER_EGRESS_DISABLE) == 0)
        {
            ++(*nof_enabled_members);
        }

    }
exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_nof_replication_get(
    int unit,
    int pool,
    int group,
    uint32 system_port_gport,
    int *nof_replications)
{
    int first;
    int last;
    trunk_group_member_info_t member_info;

    SHR_FUNC_INIT_VARS(unit);
    member_info.system_port = system_port_gport;
    SHR_IF_ERR_EXIT(dnx_trunk_sw_db_member_in_group_find(unit, pool, group, &member_info,
                                                         &first, &last, nof_replications));
exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_unique_members_info_get(
    int unit,
    int pool,
    int group,
    dnx_trunk_unique_member_t * unique_members_arr,
    int arr_size,
    int *nof_unique_members)
{
    uint32 system_port;
    int max_nof_members;
    int nof_members_in_group;
    uint32 invalid_system_port;
    int member;
    int unique_member;
    int tm_index;

    SHR_FUNC_INIT_VARS(unit);
    max_nof_members = dnx_data_trunk.parameters.pool_info_get(unit, pool)->max_nof_members_in_group;
    SHR_IF_ERR_EXIT(trunk_db.pools.groups.nof_members.get(unit, pool, group, &nof_members_in_group));
    invalid_system_port = dnx_data_device.general.invalid_system_port_get(unit);
    *nof_unique_members = 0;
    sal_memset(unique_members_arr, 0, sizeof(unique_members_arr[0]) * arr_size);

    /** sanity check, if the given array is smaller than the number of members in the group return error */
    /** this is over defensive, we actually need only to check that there sufficient size for unique members */
    if (arr_size < nof_members_in_group)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "input array size(%d) is smaller than number of members in group(%d)",
                     arr_size, nof_members_in_group);
    }

    /** iterate members in group */
    for (member = 0; member < max_nof_members; ++member)
    {
        /** skip invalid members */
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.system_port.get(unit, pool, group, member, &system_port));
        if (system_port == invalid_system_port)
        {
            continue;
        }

        /** if member exists already as unique member increase number of replications */
        for (unique_member = 0; unique_member < *nof_unique_members; ++unique_member)
        {
            if (system_port == unique_members_arr[unique_member].system_port)
            {
                ++unique_members_arr[unique_member].nof_replications;
                break;
            }
        }

        /** if not first replication continue */
        if (unique_member < *nof_unique_members)
        {
            continue;
        }

        /** for first replication of a unique member, add it to the array */
        unique_members_arr[unique_member].system_port = system_port;
        unique_members_arr[unique_member].nof_replications = 1;
        SHR_IF_ERR_EXIT(trunk_db.pools.groups.members.index.get(unit, pool, group, member, &tm_index));
        unique_members_arr[unique_member].is_enabled = (tm_index >= 0);
        ++(*nof_unique_members);
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_group_flags_get(
    int unit,
    int pool,
    int group,
    uint32 *flags)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(trunk_db.pools.groups.flags.get(unit, pool, group, flags));

exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_group_flags_set(
    int unit,
    int pool,
    int group,
    uint32 flags)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(trunk_db.pools.groups.flags.set(unit, pool, group, flags));

exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_group_master_trunk_id_get(
    int unit,
    int pool,
    int group,
    bcm_trunk_t * tid)
{
    uint32 trunk_flags;

    SHR_FUNC_INIT_VARS(unit);

    /** master trunk is only relevant for virtual trunks */
    SHR_IF_ERR_EXIT(dnx_trunk_sw_db_group_flags_get(unit, pool, group, &trunk_flags));
    if ((trunk_flags & BCM_TRUNK_FLAG_VP) == 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "master trunk is only supported for virtual trunks");
    }

    SHR_IF_ERR_EXIT(trunk_db.pools.groups.master_trunk_id.get(unit, pool, group, tid));

exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_group_master_trunk_id_set(
    int unit,
    int pool,
    int group,
    bcm_trunk_t tid)
{
    uint32 trunk_flags;

    SHR_FUNC_INIT_VARS(unit);

    /** master trunk is only relevant for virtual trunks */
    SHR_IF_ERR_EXIT(dnx_trunk_sw_db_group_flags_get(unit, pool, group, &trunk_flags));
    if ((trunk_flags & BCM_TRUNK_FLAG_VP) == 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "master trunk is only supported for virtual trunks");
    }

    SHR_IF_ERR_EXIT(trunk_db.pools.groups.master_trunk_id.set(unit, pool, group, tid));

exit:
    SHR_FUNC_EXIT;
}

/*
 * see header file
 */
shr_error_e
dnx_trunk_sw_db_group_gport_is_virtual_trunk(
    int unit,
    bcm_gport_t gport,
    uint8 *is_virtual_trunk,
    bcm_trunk_t * master_tid)
{
    bcm_trunk_id_info_t id_info;
    uint32 trunk_flags;

    SHR_FUNC_INIT_VARS(unit);

    *is_virtual_trunk = FALSE;

    if (BCM_GPORT_IS_TRUNK(gport))
    {
        SHR_IF_ERR_EXIT(dnx_trunk_utils_trunk_id_to_id_info_convert(unit, BCM_GPORT_TRUNK_GET(gport), &id_info));
        SHR_IF_ERR_EXIT(dnx_trunk_sw_db_group_flags_get(unit, id_info.pool_index, id_info.group_index, &trunk_flags));
        if (trunk_flags & BCM_TRUNK_FLAG_VP)
        {
            *is_virtual_trunk = TRUE;
            SHR_IF_ERR_EXIT(dnx_trunk_sw_db_group_master_trunk_id_get
                            (unit, id_info.pool_index, id_info.group_index, master_tid));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/** see header file */
shr_error_e
dnx_trunk_sw_db_chm_handle_get(
    int unit,
    uint32 *chm_handle)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(trunk_db.psc_general_info.chm_handle.get(unit, chm_handle));

exit:
    SHR_FUNC_EXIT;
}

/** see header file */
shr_error_e
dnx_trunk_sw_db_chm_handle_set(
    int unit,
    uint32 chm_handle)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(trunk_db.psc_general_info.chm_handle.set(unit, chm_handle));

exit:
    SHR_FUNC_EXIT;
}

/** see header file */
shr_error_e
dnx_trunk_sw_db_profile_info_get(
    int unit,
    int psc_profile,
    int *profile_type,
    int *max_nof_members)
{
    profile_info_t profile_info;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(trunk_db.psc_general_info.profile_info.get(unit, psc_profile, &profile_info));
    *profile_type = profile_info.psc_profile_type;
    *max_nof_members = profile_info.max_nof_members;

exit:
    SHR_FUNC_EXIT;
}

/** see header file */
shr_error_e
dnx_trunk_sw_db_profile_info_set(
    int unit,
    int psc_profile,
    int profile_type,
    int max_nof_members)
{
    profile_info_t profile_info;
    SHR_FUNC_INIT_VARS(unit);

    profile_info.psc_profile_type = profile_type;
    profile_info.max_nof_members = max_nof_members;
    SHR_IF_ERR_EXIT(trunk_db.psc_general_info.profile_info.set(unit, psc_profile, &profile_info));

exit:
    SHR_FUNC_EXIT;
}

/** see header file */
shr_error_e
dnx_trunk_sw_db_user_profile_info_psc_profile_get(
    int unit,
    int user_profile,
    int *psc_profile)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(trunk_db.psc_general_info.user_profile_info.
                    assigned_psc_profile.get(unit, user_profile, psc_profile));

exit:
    SHR_FUNC_EXIT;
}

/** see header file */
shr_error_e
dnx_trunk_sw_db_user_profile_info_psc_profile_set(
    int unit,
    int user_profile,
    int psc_profile)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(trunk_db.psc_general_info.user_profile_info.
                    assigned_psc_profile.set(unit, user_profile, psc_profile));

exit:
    SHR_FUNC_EXIT;
}

/** see header file */
shr_error_e
dnx_trunk_sw_db_user_profile_info_clear(
    int unit,
    int user_profile)
{
    user_profile_info_t user_profile_info;
    SHR_FUNC_INIT_VARS(unit);

    user_profile_info_t_init(&user_profile_info);
    SHR_IF_ERR_EXIT(trunk_db.psc_general_info.user_profile_info.set(unit, user_profile, &user_profile_info));

exit:
    SHR_FUNC_EXIT;
}

/** see header file */
shr_error_e
dnx_trunk_sw_db_user_profile_info_ref_count_increment(
    int unit,
    int user_profile)
{
    int ref_counter;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(trunk_db.psc_general_info.user_profile_info.ref_counter.get(unit, user_profile, &ref_counter));
    ++ref_counter;
    SHR_IF_ERR_EXIT(trunk_db.psc_general_info.user_profile_info.ref_counter.set(unit, user_profile, ref_counter));

exit:
    SHR_FUNC_EXIT;
}

/** see header file */
shr_error_e
dnx_trunk_sw_db_user_profile_info_ref_count_decrement(
    int unit,
    int user_profile)
{
    int ref_counter;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(trunk_db.psc_general_info.user_profile_info.ref_counter.get(unit, user_profile, &ref_counter));
    --ref_counter;
    if (ref_counter < 0)
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "ref_countner < 0, something went wrong\n");
    }
    SHR_IF_ERR_EXIT(trunk_db.psc_general_info.user_profile_info.ref_counter.set(unit, user_profile, ref_counter));

exit:
    SHR_FUNC_EXIT;
}

/** see header file */
shr_error_e
dnx_trunk_sw_db_user_profile_info_ref_count_get(
    int unit,
    int user_profile,
    int *ref_counter)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(trunk_db.psc_general_info.user_profile_info.ref_counter.get(unit, user_profile, ref_counter));

exit:
    SHR_FUNC_EXIT;
}

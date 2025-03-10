/*
 * 
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * DNXF FABRIC
 */

#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif

#define BSL_LOG_MODULE BSL_LS_BCMDNX_FABRIC
#include <shared/bsl.h>
#include <bcm/types.h>
#include <bcm/module.h>
#include <bcm/error.h>
#include <bcm_int/common/debug.h>
#include <bcm_int/dnxf/auto_generated/dnxf_fabric_dispatch.h>
#include <bcm_int/dnxf/auto_generated/dnxf_stk_dispatch.h>
#include <bcm/debug.h>
#include <bcm/fabric.h>

#include <bcm_int/dnxf/fabric.h>
#include <bcm_int/dnxf/dnxf_modid_group_map.h>
#include <bcm_int/dnxf/dnxf_modid_local_map.h>
#include <bcm_int/dnxf/dnxf_multicast_id_map.h>

#include <soc/defs.h>
#include <soc/drv.h>

#include <soc/dnxf/cmn/dnxf_drv.h>
#include <soc/dnxf/cmn/dnxf_defs.h>
#include <soc/dnxf/cmn/dnxf_fabric.h>
#include <soc/dnxf/cmn/dnxf_multicast.h>
#include <soc/dnxf/cmn/dnxf_port.h>
#include <soc/dnxf/swstate/auto_generated/access/dnxf_access.h>
#include <soc/dnxf/cmn/dnxf_fabric_source_routed_cell.h>
#include <soc/dnxf/cmn/dnxf_fabric_cell.h>
#include <soc/dnxf/cmn/dnxf_fabric_flow_control.h>
#include <soc/dnxf/cmn/mbcm.h>

#include <soc/dnxc/dnxc_verify.h>
#include <soc/dnxc/dnxc_cells_buffer.h>
#include <soc/dnxc/dnxc_captured_buffer.h>
#include <soc/dnxc/dnxc_crc.h>

#include <soc/dnxf/dnxf_data/auto_generated/dnxf_data_fabric.h>
#include <soc/dnxf/dnxf_data/auto_generated/dnxf_data_device.h>
#include <soc/dnxf/dnxf_data/auto_generated/dnxf_data_port.h>
#include <soc/dnxf/dnxf_data/auto_generated/dnxf_data_max_port.h>
#include <soc/dnxf/dnxf_data/auto_generated/dnxf_data_max_fabric.h>
#include <soc/dnxf/swstate/auto_generated/access/dnxf_access.h>

#ifdef ADAPTER_SERVER_MODE
#include <soc/dnxc/dnxc_adapter_reg_access.h>
#endif

STATIC int
_bcm_dnxf_fabric_link_control_set_llfc_control_source(
    int unit,
    bcm_port_t link,
    soc_dnxc_fabric_pipe_t arg)
{
    int nof_pipes;
    uint32 mask = 0;
    SHR_FUNC_INIT_VARS(unit);

    nof_pipes = dnxf_data_fabric.pipes.nof_pipes_get(unit);
    SOC_DNXC_FABRIC_PIPE_ALL_PIPES_SET(&mask, nof_pipes);

    if ((!(SOC_DNXC_FABRIC_PIPE_ALL_PIPES_IS_CLEAR(arg))) && (!(SOC_DNXC_FABRIC_PIPE_ALL_PIPES_IS_SET(arg, mask))))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "LLFC must be for all pipes");
    }

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_links_llf_control_source_set, (unit, link, arg)));

exit:
    SHR_FUNC_EXIT;
}

STATIC int
_bcm_dnxf_fabric_multicast_low_prio_drop_select(
    int unit,
    int arg)
{
    SHR_FUNC_INIT_VARS(unit);

    if (!DNXF_IS_PRIORITY_VALID(arg))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal priority %d", arg);
    }

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_multicast_low_prio_drop_select_priority_set,
                                          (unit, (soc_dnxf_fabric_priority_t) arg)));

exit:
    SHR_FUNC_EXIT;
}

STATIC int
_bcm_dnxf_fabric_control_set_low_prio_threshold(
    int unit,
    bcm_fabric_control_t type,
    int arg)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL
                    (unit, mbcm_dnxf_fabric_multicast_low_prio_threshold_validate, (unit, type, arg)));

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_multicast_low_prio_threshold_set, (unit, type, arg)));

exit:
    SHR_FUNC_EXIT;
}

STATIC int
_bcm_dnxf_fabric_control_set_priority_range(
    int unit,
    bcm_fabric_control_t type,
    int arg)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_multicast_priority_range_validate, (unit, type, arg)));

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_multicast_priority_range_set, (unit, type, arg)));

exit:
    SHR_FUNC_EXIT;
}

int
dnxf_fabric_link_retimer_connect_set(
    int unit,
    soc_port_t link_a,
    soc_port_t link_b)
{
    SHR_FUNC_INIT_VARS(unit);

    DNXF_LINK_INPUT_CHECK(unit, link_a);

    if (link_b != -1)
    {
        DNXF_LINK_INPUT_CHECK(unit, link_b);
    }

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_link_retimer_connect_set, (unit, link_a, link_b)));

exit:
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_link_retimer_connect_get(
    int unit,
    bcm_port_t link_a,
    bcm_port_t * link_b)
{

    SHR_FUNC_INIT_VARS(unit);

    DNXF_LINK_INPUT_CHECK(unit, link_a);

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_link_retimer_connect_get, (unit, link_a, link_b)));

exit:
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_link_topology_destination_validation(
    int unit,
    bcm_module_t destination)
{
    int is_valid = 0;
    bcm_module_t local_id = -1;
    SHR_FUNC_INIT_VARS(unit);

    if (dnxf_data_fabric.general.device_mode_get(unit) == soc_dnxf_fabric_device_mode_multi_stage_fe2)
    {
        if (!BCM_FABRIC_MODID_IS_GROUP(destination))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "In FE2 multistage destination must be a group");
        }
        local_id = BCM_FABRIC_GROUP_MODID_UNSET(destination);
        if (!DNXF_MODID_GROUP_IS_LEGAL(unit, local_id))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Group %d is out of range", destination);
        }
    }
    else
    {
        if (BCM_FABRIC_MODID_IS_GROUP(destination))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Only in FE2 multistage destination can be a group");
        }
        if (BCM_FABRIC_MODID_IS_LOCAL(destination))
        {
            local_id = BCM_FABRIC_LOCAL_MODID_UNSET(destination);
            SHR_IF_ERR_EXIT(dnxf_modid_local_map_is_valid(unit, local_id, &is_valid));
            if (!is_valid)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Local id %d wasn't allocated", destination);
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_link_topology_destination_to_local_get(
    int unit,
    bcm_module_t destination,
    bcm_module_t * local_id)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnxf_fabric_link_topology_destination_validation(unit, destination));

    if (BCM_FABRIC_MODID_IS_GROUP(destination))
    {
        *local_id = BCM_FABRIC_GROUP_MODID_UNSET(destination);
    }
    else if (BCM_FABRIC_MODID_IS_LOCAL(destination))
    {
        *local_id = BCM_FABRIC_LOCAL_MODID_UNSET(destination);
    }
    else
    {

        SHR_IF_ERR_EXIT(dnxf_modid_local_map_modid_to_local(unit, destination, local_id));
    }

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_ERR_EXIT(_SHR_E_UNAVAIL, "API" " not supported!");

exit:
    SHR_FUNC_EXIT;
}

STATIC int
dnxf_fabric_init_verify(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    if (SOC_DNXF_IS_FE2(unit) && dnxf_data_fabric.general.local_routing_enable_uc_get(unit))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "UC Local routing can be enabled only if device is in FE13 mode!");
    }

    if (SOC_DNXF_IS_FE2(unit) && dnxf_data_fabric.general.local_routing_enable_mc_get(unit))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "MC Local routing can be enabled only if device is in FE13 mode!");
    }

exit:
    SHR_FUNC_EXIT;
}

int
dnxf_fabric_init(
    int unit)
{
    bcm_port_t link;
    uint32 mc_table_size;
    DNXF_UNIT_LOCK_INIT(unit);

    SHR_FUNC_INIT_VARS(unit);

    DNXF_UNIT_LOCK_TAKE(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_init_verify(unit));

    if (!SOC_WARM_BOOT(unit))
    {
        SHR_IF_ERR_EXIT(dnxf_modid_group_map_clear(unit));
        SHR_IF_ERR_EXIT(dnxf_modid_local_map_clear(unit));
    }

    if (!SOC_WARM_BOOT(unit))
    {
        if (dnxf_data_port.general.feature_get(unit, dnxf_data_port_general_is_connection_to_repeater_supported))
        {
            PBMP_SFI_ITER(unit, link)
            {
                if (dnxf_data_port.static_add.port_info_get(unit, link)->connected_to_repeater)
                {
                    SHR_IF_ERR_EXIT(bcm_dnxf_fabric_link_control_set(unit, link, bcmFabricLinkRepeaterEnable, 1));
                }
            }
        }
    }

    if (!SOC_WARM_BOOT(unit))
    {

        if (!dnxf_data_fabric.cell.feature_get(unit, dnxf_data_fabric_cell_format_always_with_pcp))
        {
            PBMP_SFI_ITER(unit, link)
            {
                SHR_IF_ERR_EXIT(bcm_dnxf_fabric_link_control_set(unit, link, bcmFabricLinkPcpEnable, 0x1));
            }
        }
    }

    if (!SOC_WARM_BOOT(unit))
    {
        SHR_IF_ERR_EXIT(soc_dnxf_cell_filter_init(unit));
    }

    if (!SOC_WARM_BOOT(unit))
    {
        if (SOC_DNXF_IS_FE2(unit))
        {
            SHR_IF_ERR_EXIT(soc_dnxf_control_cell_filter_clear(unit));
            SHR_IF_ERR_EXIT(soc_dnxf_control_cell_filter_set
                            (unit, SOC_CELL_FILTER_FLAG_DONT_FORWARD | SOC_CELL_FILTER_FLAG_DONT_TRAP,
                             soc_dnxc_fe2_filtered_cell, 0, NULL, NULL));
        }
    }

    if (!SOC_WARM_BOOT(unit))
    {
        if (dnxf_data_fabric.multicast.priority_map_enable_get(unit) == 1)
        {
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_multicast_table_size_get, (unit, &mc_table_size)));
            SHR_IF_ERR_EXIT(bcm_dnxf_fabric_control_set(unit, bcmFabricMcLowPrioMin, 0));
            SHR_IF_ERR_EXIT(bcm_dnxf_fabric_control_set(unit, bcmFabricMcLowPrioMax, mc_table_size - 1));
        }
    }

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
dnxf_fabric_deinit(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_control_set(
    int unit,
    bcm_fabric_control_t type,
    int arg)
{
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    DNXF_UNIT_LOCK_TAKE(unit);

    switch (type)
    {
        case bcmFabricMcLowPrioMin:
        case bcmFabricMcLowPrioMax:
        case bcmFabricMcMidPrioMin:
        case bcmFabricMcMidPrioMax:
            if (!(dnxf_data_fabric.multicast.priority_map_enable_get(unit) == 1))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Unsupported controls when mc priority is determined by the cell");
            }
            SHR_IF_ERR_EXIT(_bcm_dnxf_fabric_control_set_priority_range(unit, type, arg));
            break;
        case bcmFabricEnableMcLowPrioDrop:
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL
                            (unit, mbcm_dnxf_fabric_multicast_low_priority_drop_enable_set, (unit, arg)));
            break;
        case bcmFabricMcLowPrioDropThUp:
        case bcmFabricMcLowPrioDropThDown:
            SHR_IF_ERR_EXIT(_bcm_dnxf_fabric_control_set_low_prio_threshold(unit, type, arg));
            break;
        case bcmFabricMcLowPrioDropSelect:
            SHR_IF_ERR_EXIT(_bcm_dnxf_fabric_multicast_low_prio_drop_select(unit, arg));
            break;
        case bcmFabricIsolate:
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_topology_isolate_set,
                                                  (unit,
                                                   arg ? soc_dnxc_isolation_status_isolated :
                                                   soc_dnxc_isolation_status_active)));
            break;
        case bcmFabricShutdown:
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcmFabricShutdown is not supported. Use bcmFabricIsolate instead.");
            break;
        case bcmFabricRCIControlSource:
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcmFabricRCIControlSource is not supported");
            break;
        case bcmFabricGCIControlSource:
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcmFabricGCIControlSource is not supported");
            break;
        case bcmFabricControlDirectMcModidOffset:
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_multicast_direct_offset_set, (unit, arg)));
            break;
        case bcmFabricLocalRouteControlCellsEnable:
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_topology_local_route_control_cells_enable_set,
                                                  (unit, arg)));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Unsupported Type %d", type);
    }

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_control_get(
    int unit,
    bcm_fabric_control_t type,
    int *arg)
{
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(arg, _SHR_E_PARAM, "arg");

    DNXF_UNIT_LOCK_TAKE(unit);

    switch (type)
    {
        case bcmFabricMcLowPrioMin:
        case bcmFabricMcLowPrioMax:
        case bcmFabricMcMidPrioMin:
        case bcmFabricMcMidPrioMax:

            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL
                            (unit, mbcm_dnxf_fabric_multicast_priority_range_get, (unit, type, arg)));
            break;
        case bcmFabricEnableMcLowPrioDrop:
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL
                            (unit, mbcm_dnxf_fabric_multicast_low_priority_drop_enable_get, (unit, arg)));
            break;
        case bcmFabricMcLowPrioDropThUp:
        case bcmFabricMcLowPrioDropThDown:
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL
                            (unit, mbcm_dnxf_fabric_multicast_low_prio_threshold_get, (unit, type, arg)));
            break;
        case bcmFabricMcLowPrioDropSelect:
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_multicast_low_prio_drop_select_priority_get,
                                                  (unit, (soc_dnxf_fabric_priority_t *) arg)));
            break;
        case bcmFabricIsolate:
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_topology_isolate_get,
                                                  (unit, (soc_dnxc_isolation_status_t *) arg)));
            break;
        case bcmFabricRCIControlSource:
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcmFabricRCIControlSource is not supported");
            break;
        case bcmFabricGCIControlSource:
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcmFabricGCIControlSource is not supported");
            break;
        case bcmFabricShutdown:
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcmFabricShutdown is not supported. Use bcmFabricIsolate instead.");
            break;
        case bcmFabricControlDirectMcModidOffset:
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_multicast_direct_offset_get, (unit, arg)));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Unsupported Type %d", type);
    }

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_modid_group_set_verify(
    int unit,
    bcm_module_t group,
    int modid_count,
    bcm_module_t * modid_array)
{
    int i, is_valid;
    bcm_module_t module, grp;

    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(modid_array, _SHR_E_PARAM, "modid_array");

    if (dnxf_data_fabric.general.device_mode_get(unit) != soc_dnxf_fabric_device_mode_multi_stage_fe2)
    {
        SHR_ERR_EXIT(_SHR_E_CONFIG, "This function can be called only in multi-stage FE2 mode.");
    }

    if (!BCM_FABRIC_MODID_IS_GROUP(group))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "%d is not a group", group);
    }

    grp = BCM_FABRIC_GROUP_MODID_UNSET(group);
    if (!DNXF_MODID_GROUP_IS_LEGAL(unit, grp))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Group %d is out of range", group);
    }

    for (i = 0; i < modid_count; i++)
    {
        if (BCM_FABRIC_MODID_IS_LOCAL(modid_array[i]))
        {
            module = BCM_FABRIC_LOCAL_MODID_UNSET(modid_array[i]);
            SHR_IF_ERR_EXIT(dnxf_modid_local_map_is_valid(unit, module, &is_valid));
            if (!is_valid)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "module %d index %d is invalid local modid", modid_array[i], i);
            }
        }
        else
        {
            if (modid_array[i] >= dnxf_data_fabric.topology.nof_system_modid_get(unit))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "module %d index %d is out of rang", modid_array[i], i);
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_modid_group_set(
    int unit,
    bcm_module_t group,
    int modid_count,
    bcm_module_t * modid_array)
{
    int modid_idx;
    bcm_module_t module, grp;
    DNXF_UNIT_LOCK_INIT(unit);

    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_modid_group_set_verify(unit, group, modid_count, modid_array));

    grp = BCM_FABRIC_GROUP_MODID_UNSET(group);
    SHR_IF_ERR_EXIT(dnxf_modid_group_map_clear_group(unit, grp));

    for (modid_idx = 0; modid_idx < modid_count; modid_idx++)
    {
        if (BCM_FABRIC_MODID_IS_LOCAL(modid_array[modid_idx]))
        {
            SHR_IF_ERR_EXIT(dnxf_modid_local_map_get
                            (unit, BCM_FABRIC_LOCAL_MODID_UNSET(modid_array[modid_idx]), &module));
        }
        else
        {
            module = modid_array[modid_idx];
        }

        SHR_IF_ERR_EXIT(dnxf_modid_group_map_add(unit, grp, module));

        SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL
                        (unit, mbcm_dnxf_fabric_topology_modid_group_map_set, (unit, module, grp)));
    }

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_modid_group_get_verify(
    int unit,
    bcm_module_t group,
    int modid_max_count,
    bcm_module_t * modid_array,
    int *modid_count)
{
    bcm_module_t grp;

    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(modid_array, _SHR_E_PARAM, "modid_array");
    SHR_NULL_CHECK(modid_count, _SHR_E_PARAM, "modid_count");

    if (!BCM_FABRIC_MODID_IS_GROUP(group))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "%d is not a group", group);
    }

    grp = BCM_FABRIC_GROUP_MODID_UNSET(group);
    if (!DNXF_MODID_GROUP_IS_LEGAL(unit, grp))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Group %d is out of range", group);
    }

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_modid_group_get(
    int unit,
    bcm_module_t group,
    int modid_max_count,
    bcm_module_t * modid_array,
    int *modid_count)
{
    bcm_module_t grp;
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_modid_group_get_verify(unit, group, modid_max_count, modid_array, modid_count));

    DNXF_UNIT_LOCK_TAKE(unit);

    grp = BCM_FABRIC_GROUP_MODID_UNSET(group);

    SHR_IF_ERR_EXIT(dnxf_modid_group_map_get_list(unit, grp, modid_max_count, modid_array, modid_count));

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_modid_group_find_verify(
    int unit,
    bcm_module_t modid,
    bcm_module_t * group)
{
    int is_valid;

    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(group, _SHR_E_PARAM, "group");

    if (BCM_FABRIC_MODID_IS_LOCAL(modid))
    {
        SHR_IF_ERR_EXIT(dnxf_modid_local_map_is_valid(unit, BCM_FABRIC_LOCAL_MODID_UNSET(modid), &is_valid));
        if (!is_valid)
        {
            SHR_ERR_EXIT(_SHR_E_NOT_FOUND, "module %d is invalid local modid", modid);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_modid_group_find(
    int unit,
    bcm_module_t modid,
    bcm_module_t * group)
{
    int m;
    DNXF_UNIT_LOCK_INIT(unit);

    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_modid_group_find_verify(unit, modid, group));

    DNXF_UNIT_LOCK_TAKE(unit);

    if (BCM_FABRIC_MODID_IS_LOCAL(modid))
    {
        SHR_IF_ERR_EXIT(dnxf_modid_local_map_get(unit, BCM_FABRIC_LOCAL_MODID_UNSET(modid), &m));
    }
    else
    {
        m = modid;
    }

    SHR_IF_ERR_EXIT(dnxf_modid_group_map_get_group(unit, m, group));

    if (DNXF_MODID_GROUP_INVALID == *group)
    {
        SHR_ERR_EXIT(_SHR_E_NOT_FOUND, "module %d not found", modid);
    }

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_modid_local_mapping_set_verify(
    int unit,
    bcm_module_t local_modid,
    bcm_module_t modid)
{
    bcm_module_t local;

    SHR_FUNC_INIT_VARS(unit);

    if (!BCM_FABRIC_MODID_IS_LOCAL(local_modid))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "%d is not a local module id", local_modid);
    }

    local = BCM_FABRIC_LOCAL_MODID_UNSET(local_modid);

    if (!DNXF_MODID_LOCAL_MAP_ROW_VALIDATE(unit, local))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "local module id %d is out of range", local_modid);
    }

    if (!SOC_DNXF_CHECK_MODULE_ID(modid))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "module id %d is out of range", modid);
    }

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_modid_local_mapping_set(
    int unit,
    bcm_module_t local_modid,
    bcm_module_t modid)
{
    bcm_module_t local;
    DNXF_UNIT_LOCK_INIT(unit);

    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_modid_local_mapping_set_verify(unit, local_modid, modid));

    DNXF_UNIT_LOCK_TAKE(unit);

    local = BCM_FABRIC_LOCAL_MODID_UNSET(local_modid);

    SHR_IF_ERR_EXIT(dnxf_modid_local_map_add(unit, local, modid, 1));

    if ((dnxf_data_fabric.general.device_mode_get(unit) != soc_dnxf_fabric_device_mode_multi_stage_fe2) &&
        (dnxf_data_fabric.multicast.mode_get(unit) != soc_dnxf_multicast_mode_direct))
    {

        SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL
                        (unit, mbcm_dnxf_fabric_topology_modid_group_map_set, (unit, modid, local)));
    }

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_modid_local_mapping_get_verify(
    int unit,
    bcm_module_t local_modid,
    bcm_module_t * modid)
{
    bcm_module_t local;

    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(modid, _SHR_E_PARAM, "modid");

    if (!BCM_FABRIC_MODID_IS_LOCAL(local_modid))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "%d is not a local module id", local_modid);
    }

    local = BCM_FABRIC_LOCAL_MODID_UNSET(local_modid);

    if (!DNXF_MODID_LOCAL_MAP_ROW_VALIDATE(unit, local))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "local module id %d is out of range", local_modid);
    }

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_modid_local_mapping_get(
    int unit,
    bcm_module_t local_modid,
    bcm_module_t * modid)
{
    int is_valid;
    bcm_module_t local;
    DNXF_UNIT_LOCK_INIT(unit);

    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_modid_local_mapping_get_verify(unit, local_modid, modid));

    DNXF_UNIT_LOCK_TAKE(unit);

    local = BCM_FABRIC_LOCAL_MODID_UNSET(local_modid);

    SHR_IF_ERR_EXIT(dnxf_modid_local_map_is_valid(unit, local, &is_valid));
    if (!is_valid)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "local module id %d is invalid", local_modid);
    }

    SHR_IF_ERR_EXIT(dnxf_modid_local_map_get(unit, local, modid));

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_module_control_set(
    int unit,
    uint32 flags,
    bcm_module_t modid,
    bcm_fabric_module_control_t control,
    int value)
{
    int rv;
    int local_modid = -1;
    DNXF_UNIT_LOCK_INIT(unit);

    SHR_FUNC_INIT_VARS(unit);

    DNXF_UNIT_LOCK_TAKE(unit);

    switch (control)
    {
        case bcmFabricModuleControlMcTopologySwControlEnable:
        {
            SHR_IF_ERR_EXIT(dnxf_fabric_link_topology_destination_to_local_get(unit, modid, &local_modid));

            rv = MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_topology_mc_sw_control_set,
                                       (unit, local_modid, (value) ? (1) : (0)));
            SHR_IF_ERR_EXIT(rv);
            break;
        }
        default:
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Unsupported control %d", control);
    }

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_module_control_get(
    int unit,
    uint32 flags,
    bcm_module_t modid,
    bcm_fabric_module_control_t control,
    int *value)
{
    int rv;
    int local_modid = -1;
    DNXF_UNIT_LOCK_INIT(unit);

    SHR_FUNC_INIT_VARS(unit);

    DNXF_UNIT_LOCK_TAKE(unit);

    switch (control)
    {
        case bcmFabricModuleControlMcTopologySwControlEnable:
        {
            SHR_IF_ERR_EXIT(dnxf_fabric_link_topology_destination_to_local_get(unit, modid, &local_modid));

            rv = MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_topology_mc_sw_control_get, (unit, local_modid, value));
            SHR_IF_ERR_EXIT(rv);
            break;
        }
        default:
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Unsupported control %d", control);
    }

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_link_topology_config_set_verify(
    int unit,
    uint32 flags,
    bcm_module_t destination,
    bcm_fabric_topology_type_t type,
    int links_count,
    bcm_port_t * links_array)
{
    int i_link = 0;
    bcm_module_t local_id = -1;
    int enable = 0;

    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(links_array, _SHR_E_PARAM, "links_array");

    if (links_count < 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "illegal links_count");
    }

    if (links_count > dnxf_data_port.general.nof_links_get(unit))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Links count not whitin the valid range!");
    }

    for (i_link = 0; i_link < links_count; i_link++)
    {

        if (links_array[i_link] != _SHR_PORT_INVALID)
        {
            DNXF_LINK_INPUT_CHECK(unit, links_array[i_link]);
        }
    }

    SHR_IF_ERR_EXIT(dnxf_fabric_link_topology_destination_to_local_get(unit, destination, &local_id));

    switch (type)
    {
        case bcmFabricTopologyLB:
        case bcmFabricTopologyAll:
        {

            break;
        }
        case bcmFabricTopologyMC:
        {
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL
                            (unit, mbcm_dnxf_fabric_topology_mc_sw_control_get, (unit, local_id, &enable)));
            if (!enable)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "SW group link configuration is disabled for group %d", local_id);
            }

            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Unsupported Type %d", type);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_topology_config_set(
    int unit,
    uint32 flags,
    bcm_module_t destination,
    bcm_fabric_topology_type_t type,
    int links_count,
    bcm_port_t * links_array)
{
    int enable = 0;
    bcm_module_t local_id = -1;
    DNXF_UNIT_LOCK_INIT(unit);

    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_link_topology_config_set_verify
                           (unit, flags, destination, type, links_count, links_array));

    SHR_IF_ERR_EXIT(dnxf_fabric_link_topology_destination_to_local_get(unit, destination, &local_id));

    DNXF_UNIT_LOCK_TAKE(unit);

    switch (type)
    {
        case bcmFabricTopologyLB:
        {
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_topology_lb_set,
                                                  (unit, local_id, links_count, links_array)));
            break;
        }
        case bcmFabricTopologyMC:
        {
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_topology_mc_set,
                                                  (unit, local_id, links_count, links_array)));
            break;
        }
        case bcmFabricTopologyAll:
        {
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_topology_lb_set,
                                                  (unit, local_id, links_count, links_array)));

            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL
                            (unit, mbcm_dnxf_fabric_topology_mc_sw_control_get, (unit, local_id, &enable)));
            if (enable)
            {
                SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_topology_mc_set,
                                                      (unit, local_id, links_count, links_array)));
            }
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Unsupported Type %d", type);
        }
    }

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_topology_set(
    int unit,
    bcm_module_t destination,
    int links_count,
    bcm_port_t * links_array)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(bcm_dnxf_fabric_link_topology_config_set
                    (unit, 0, destination, bcmFabricTopologyAll, links_count, links_array));

exit:
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_link_topology_config_get_verify(
    int unit,
    uint32 flags,
    bcm_module_t destination,
    bcm_fabric_topology_type_t type,
    int links_count_max,
    int *links_count,
    bcm_port_t * links_array)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(links_count, _SHR_E_PARAM, "links_count");
    SHR_NULL_CHECK(links_array, _SHR_E_PARAM, "links_array");

    if (links_count_max <= 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "links_array size must be positive");
    }

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_topology_config_get(
    int unit,
    uint32 flags,
    bcm_module_t destination,
    bcm_fabric_topology_type_t type,
    int links_count_max,
    int *links_count,
    bcm_port_t * links_array)
{
    bcm_module_t local_id = -1;
    int enable = 0;
    DNXF_UNIT_LOCK_INIT(unit);

    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_link_topology_config_get_verify
                           (unit, flags, destination, type, links_count_max, links_count, links_array));

    SHR_IF_ERR_EXIT(dnxf_fabric_link_topology_destination_to_local_get(unit, destination, &local_id));

    DNXF_UNIT_LOCK_TAKE(unit);

    switch (type)
    {
        case bcmFabricTopologyLB:
        {
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_topology_lb_get,
                                                  (unit, local_id, links_count_max, links_count, links_array)));
            break;
        }
        case bcmFabricTopologyMC:
        {
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL
                            (unit, mbcm_dnxf_fabric_topology_mc_sw_control_get, (unit, local_id, &enable)));
            if (!enable)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "SW group link configuration is disabled for group %d", local_id);
            }

            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_topology_mc_get,
                                                  (unit, local_id, links_count_max, links_count, links_array)));
            break;
        }
        case bcmFabricTopologyAll:
        {
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_topology_lb_get,
                                                  (unit, local_id, links_count_max, links_count, links_array)));
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Unsupported Type %d", type);
        }
    }

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_topology_get(
    int unit,
    bcm_module_t destination,
    int links_count_max,
    int *links_count,
    bcm_port_t * links_array)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(bcm_dnxf_fabric_link_topology_config_get
                    (unit, 0, destination, bcmFabricTopologyAll, links_count_max, links_count, links_array));

exit:
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_multicast_set_verify(
    int unit,
    bcm_multicast_t group,
    uint32 flags,
    uint32 destid_count,
    bcm_module_t * destid_array)
{
    bcm_gport_t mudule_id;
    int i, is_legal, is_free, is_valid;
    uint32 mc_table_entry_size;
    bcm_module_t local_module_id;

    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(destid_array, _SHR_E_PARAM, "destid_array");

    if (destid_count > dnxf_data_fabric.topology.nof_system_modid_get(unit))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "too many destinations");
    }

    SHR_IF_ERR_EXIT(dnxf_multicst_id_map_is_legal_id(unit, group, &is_legal));
    if (!is_legal)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "group %d is illegal", group);
    }

    SHR_IF_ERR_EXIT(dnxf_multicst_id_map_is_free_id(unit, group, &is_free));
    if (is_free)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "group %d wasn't created", group);
    }

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL
                    (unit, mbcm_dnxf_multicast_table_entry_size_get, (unit, &mc_table_entry_size)));

    for (i = 0; i < destid_count; i++)
    {

        if (soc_dnxf_fabric_device_mode_multi_stage_fe2 == dnxf_data_fabric.general.device_mode_get(unit))
        {

            if (BCM_FABRIC_MODID_IS_GROUP(destid_array[i]))
            {
                if ((BCM_FABRIC_GROUP_MODID_UNSET(destid_array[i])) >= mc_table_entry_size)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Destination id  %d is larger than multicast table entry size %d",
                                 BCM_FABRIC_GROUP_MODID_UNSET(destid_array[i]), mc_table_entry_size);
                }
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "In FE2 multi stage destid must be a FAPs group, failed on index %d", i);
            }
        }
        else
        {

            if (BCM_FABRIC_MODID_IS_GROUP(destid_array[i]))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "If not FE2 multi stage destid must not be a FAPs group, failed on index %d",
                             i);
            }
            else
            {
                if (BCM_FABRIC_MODID_IS_LOCAL(destid_array[i]))
                {
                    local_module_id = BCM_FABRIC_LOCAL_MODID_UNSET(destid_array[i]);
                    if (local_module_id >= mc_table_entry_size)
                    {
                        SHR_ERR_EXIT(_SHR_E_PARAM, "Destination id  %d is larger than multicast table entry size %d",
                                     local_module_id, mc_table_entry_size);
                    }
                    SHR_IF_ERR_EXIT(dnxf_modid_local_map_is_valid(unit, local_module_id, &is_valid));
                    if (!is_valid)
                    {
                        SHR_ERR_EXIT(_SHR_E_PARAM, "Local id %d isn't mapped, failed on index %d", local_module_id, i);
                    }

                    if (soc_dnxf_multicast_mode_direct == dnxf_data_fabric.multicast.mode_get(unit))
                    {

                        SHR_IF_ERR_EXIT(dnxf_modid_local_map_get(unit, local_module_id, &mudule_id));
                        if (mudule_id >= mc_table_entry_size)
                        {
                            SHR_ERR_EXIT(_SHR_E_PARAM,
                                         "Destination id %d was not correctly mapped to modid. Modid %d is larger than multicast table entry size %d",
                                         local_module_id, mudule_id, mc_table_entry_size);
                        }
                    }
                    else
                    {

                    }
                }
                else
                {
                    if (soc_dnxf_multicast_mode_direct == dnxf_data_fabric.multicast.mode_get(unit))
                    {
                        if (destid_array[i] >= mc_table_entry_size)
                        {
                            SHR_ERR_EXIT(_SHR_E_PARAM,
                                         "Destination id  %d is larger than multicast table entry size %d",
                                         destid_array[i], mc_table_entry_size);
                        }
                    }
                    else
                    {

                    }
                }
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static int
dnx_fabric_multicat_local_modid_get(
    int unit,
    bcm_module_t destid,
    bcm_gport_t * local_modid)
{
    SHR_FUNC_INIT_VARS(unit);

    if (soc_dnxf_fabric_device_mode_multi_stage_fe2 == dnxf_data_fabric.general.device_mode_get(unit))
    {

        if (BCM_FABRIC_MODID_IS_GROUP(destid))
        {
            *local_modid = BCM_FABRIC_GROUP_MODID_UNSET(destid);
        }
        else
        {

        }
    }
    else
    {

        if (BCM_FABRIC_MODID_IS_GROUP(destid))
        {

        }
        else
        {
            if (BCM_FABRIC_MODID_IS_LOCAL(destid))
            {
                bcm_module_t local_module_id = BCM_FABRIC_LOCAL_MODID_UNSET(destid);

                if (soc_dnxf_multicast_mode_direct == dnxf_data_fabric.multicast.mode_get(unit))
                {

                    SHR_IF_ERR_EXIT(dnxf_modid_local_map_get(unit, local_module_id, local_modid));
                }
                else
                {
                    *local_modid = local_module_id;
                }
            }
            else
            {
                if (soc_dnxf_multicast_mode_direct == dnxf_data_fabric.multicast.mode_get(unit))
                {
                    *local_modid = destid;
                }
                else
                {

                    SHR_IF_ERR_EXIT(dnxf_modid_local_map_modid_to_local(unit, destid, local_modid));
                }
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_multicast_set(
    int unit,
    bcm_multicast_t group,
    uint32 flags,
    uint32 destid_count,
    bcm_module_t * destid_array)
{
    bcm_gport_t *local_modis_array = NULL;
    int destid_idx;
    uint32 mc_table_entry_size;

    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_multicast_set_verify(unit, group, flags, destid_count, destid_array));

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL
                    (unit, mbcm_dnxf_multicast_table_entry_size_get, (unit, &mc_table_entry_size)));

    SHR_ALLOC(local_modis_array, sizeof(bcm_gport_t) * destid_count, "modid array", "%s%s%s\r\n", EMPTY, EMPTY, EMPTY);
    if (NULL == local_modis_array)
    {
        SHR_ERR_EXIT(_SHR_E_MEMORY, "Failed to allocate port_array");
    }

    DNXF_UNIT_LOCK_TAKE(unit);

    for (destid_idx = 0; destid_idx < destid_count; destid_idx++)
    {
        SHR_IF_ERR_EXIT(dnx_fabric_multicat_local_modid_get
                        (unit, destid_array[destid_idx], &local_modis_array[destid_idx]));
    }

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_multicast_egress_set,
                                          (unit, group, destid_count, (soc_gport_t *) local_modis_array)));

exit:
    SHR_FREE(local_modis_array);
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_multicast_get_verify(
    int unit,
    bcm_multicast_t group,
    uint32 flags,
    int destid_count_max,
    int *destid_count,
    bcm_module_t * destid_array)
{
    int is_legal, is_free;

    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(destid_count, _SHR_E_PARAM, "destid_count");
    SHR_NULL_CHECK(destid_array, _SHR_E_PARAM, "destid_array");

    if (destid_count_max > dnxf_data_fabric.topology.nof_system_modid_get(unit) || destid_count_max < 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "illegal destid_count_max");
    }

    SHR_IF_ERR_EXIT(dnxf_multicst_id_map_is_legal_id(unit, group, &is_legal));
    if (!is_legal)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "group %d is illegal", group);
    }

    SHR_IF_ERR_EXIT(dnxf_multicst_id_map_is_free_id(unit, group, &is_free));
    if (is_free)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "group %d wasn't created", group);
    }

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_multicast_get(
    int unit,
    bcm_multicast_t group,
    uint32 flags,
    int destid_count_max,
    int *destid_count,
    bcm_module_t * destid_array)
{
    bcm_gport_t *port_array = NULL;
    int i;

    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_multicast_get_verify
                           (unit, group, flags, destid_count_max, destid_count, destid_array));

    SHR_ALLOC(port_array, sizeof(bcm_gport_t) * destid_count_max, "port array", "%s%s%s\r\n", EMPTY, EMPTY, EMPTY);
    if (NULL == port_array)
    {
        SHR_ERR_EXIT(_SHR_E_MEMORY, "Failed to allocate port_array");
    }

    DNXF_UNIT_LOCK_TAKE(unit);

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_multicast_egress_get,
                                          (unit, group, destid_count_max, (soc_gport_t *) port_array, destid_count)));

    for (i = 0; i < *destid_count; i++)
    {
        if (soc_dnxf_fabric_device_mode_multi_stage_fe2 == dnxf_data_fabric.general.device_mode_get(unit))
        {

            destid_array[i] = BCM_FABRIC_GROUP_MODID_SET(port_array[i]);
        }
        else
        {
            if (soc_dnxf_multicast_mode_direct == dnxf_data_fabric.multicast.mode_get(unit))
            {
                destid_array[i] = port_array[i];
            }
            else
            {

                SHR_IF_ERR_EXIT(dnxf_modid_local_map_get(unit, port_array[i], &(destid_array[i])));
            }
        }
    }

exit:
    SHR_FREE(port_array);
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_multicast_multi_config_get_verify(
    int unit,
    uint32 flags,
    uint32 nof_groups,
    bcm_multicast_t * groups,
    bcm_fabric_module_vector_t * dest_array,
    int *local_route_array)
{
    bcm_multicast_t group;
    int i, is_legal, is_free;
    uint32 mc_table_size = 0;

    SHR_FUNC_INIT_VARS(unit);

    if (local_route_array != NULL)
    {
        if (!SOC_DNXF_IS_FE13(unit))
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Multicast local route can be configured only on FE13 devices");
        }

        if (dnxf_data_fabric.general.local_routing_enable_mc_get(unit) == 0)
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Multicast local route can be configured only if the feature was enabled");
        }
    }

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_multicast_table_size_get, (unit, &mc_table_size)));
    if (nof_groups > mc_table_size)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "too many groups");
    }

    if (nof_groups == 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid number of groups");
    }

    for (i = 0; i < nof_groups; i++)
    {
        group = groups[i];
        SHR_IF_ERR_EXIT(dnxf_multicst_id_map_is_legal_id(unit, group, &is_legal));
        if (!is_legal)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "group %d is illegal", group);
        }

        SHR_IF_ERR_EXIT(dnxf_multicst_id_map_is_free_id(unit, group, &is_free));
        if (is_free)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "group %d wasn't created", group);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_multicast_multi_get_verify(
    int unit,
    uint32 flags,
    uint32 ngroups,
    bcm_multicast_t * groups,
    bcm_fabric_module_vector_t * dest_array)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(groups, _SHR_E_PARAM, "groups");
    SHR_NULL_CHECK(dest_array, _SHR_E_PARAM, "dest_array");

exit:
    SHR_FUNC_EXIT;

}

static int
dnxf_fabric_multicast_multi_config_get(
    int unit,
    uint32 flags,
    uint32 nof_groups,
    bcm_multicast_t * groups,
    bcm_fabric_module_vector_t * dest_array,
    int *local_route_array)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnxf_fabric_multicast_multi_config_get_verify
                    (unit, flags, nof_groups, groups, dest_array, local_route_array));

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_multicast_multi_get,
                                          (unit, flags, nof_groups, groups, dest_array, local_route_array)));

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_multicast_multi_get(
    int unit,
    uint32 flags,
    uint32 ngroups,
    bcm_multicast_t * groups,
    bcm_fabric_module_vector_t * dest_array)
{
    DNXF_UNIT_LOCK_INIT(unit);

    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_multicast_multi_get_verify(unit, flags, ngroups, groups, dest_array));

    DNXF_UNIT_LOCK_TAKE(unit);

    SHR_IF_ERR_EXIT(dnxf_fabric_multicast_multi_config_get(unit, flags, ngroups, groups, dest_array, NULL));

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;

}

static int
dnxf_fabric_multicast_multi_config_set_verify(
    int unit,
    uint32 flags,
    uint32 nof_groups,
    bcm_multicast_t * groups,
    bcm_fabric_module_vector_t * dest_array,
    int *local_route_array)
{
    bcm_multicast_t group;
    int i, is_legal, is_free;
    uint32 mc_table_size = 0;

    SHR_FUNC_INIT_VARS(unit);

    if (local_route_array != NULL)
    {
        if (!SOC_DNXF_IS_FE13(unit))
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Multicast local route can be configured only on FE13 devices");
        }

        if (dnxf_data_fabric.general.local_routing_enable_mc_get(unit) == 0)
        {
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Multicast local route can be configured only if the feature was enabled");
        }
    }

    if (!flags || (flags & _SHR_FABRIC_MULTICAST_SET_ONLY))
    {
        SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_multicast_table_size_get, (unit, &mc_table_size)));
        if (nof_groups > mc_table_size)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "too many groups");
        }

        if (nof_groups == 0)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid number of groups");
        }

        for (i = 0; i < nof_groups; i++)
        {
            group = groups[i];
            SHR_IF_ERR_EXIT(dnxf_multicst_id_map_is_legal_id(unit, group, &is_legal));
            if (!is_legal)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "group %d is illegal", group);
            }

            SHR_IF_ERR_EXIT(dnxf_multicst_id_map_is_free_id(unit, group, &is_free));
            if (is_free)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "group %d wasn't created", group);
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_multicast_multi_config_set(
    int unit,
    uint32 flags,
    uint32 nof_groups,
    bcm_multicast_t * groups,
    bcm_fabric_module_vector_t * dest_array,
    int *local_route_array)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_multicast_multi_config_set_verify
                           (unit, flags, nof_groups, groups, dest_array, local_route_array));

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_multicast_multi_set,
                                          (unit, flags, nof_groups, groups, dest_array, local_route_array)));

exit:
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_multicast_multi_set_verify(
    int unit,
    uint32 flags,
    uint32 ngroups,
    bcm_multicast_t * groups,
    bcm_fabric_module_vector_t * dest_array)
{
    SHR_FUNC_INIT_VARS(unit);

    if (!flags || (flags & _SHR_FABRIC_MULTICAST_SET_ONLY))
    {

        SHR_NULL_CHECK(groups, _SHR_E_PARAM, "groups");
        SHR_NULL_CHECK(dest_array, _SHR_E_PARAM, "dest_array");
    }

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_multicast_multi_set(
    int unit,
    uint32 flags,
    uint32 ngroups,
    bcm_multicast_t * groups,
    bcm_fabric_module_vector_t * dest_array)
{
    DNXF_UNIT_LOCK_INIT(unit);

    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_multicast_multi_set_verify(unit, flags, ngroups, groups, dest_array));

    DNXF_UNIT_LOCK_TAKE(unit);

    SHR_IF_ERR_EXIT(dnxf_fabric_multicast_multi_config_set(unit, flags, ngroups, groups, dest_array, NULL));

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_multicast_local_route_set_verify(
    int unit,
    uint32 flags,
    uint32 nof_groups,
    bcm_multicast_t * groups,
    int *enable)
{
    SHR_FUNC_INIT_VARS(unit);

    if (!flags || (flags & _SHR_FABRIC_MULTICAST_SET_ONLY))
    {
        SHR_NULL_CHECK(groups, _SHR_E_PARAM, "groups");
        SHR_NULL_CHECK(enable, _SHR_E_PARAM, "enable");
    }

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_multicast_local_route_set(
    int unit,
    uint32 flags,
    uint32 nof_groups,
    bcm_multicast_t * groups,
    int *enable)
{
    DNXF_UNIT_LOCK_INIT(unit);

    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_multicast_local_route_set_verify(unit, flags, nof_groups, groups, enable));

    DNXF_UNIT_LOCK_TAKE(unit);

    SHR_IF_ERR_EXIT(dnxf_fabric_multicast_multi_config_set(unit, flags, nof_groups, groups, NULL, enable));

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_multicast_local_route_get_verify(
    int unit,
    uint32 flags,
    uint32 nof_groups,
    bcm_multicast_t * groups,
    int *enable)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(groups, _SHR_E_PARAM, "groups");
    SHR_NULL_CHECK(enable, _SHR_E_PARAM, "enable");

exit:
    SHR_FUNC_EXIT;

}

int
bcm_dnxf_fabric_multicast_local_route_get(
    int unit,
    uint32 flags,
    uint32 nof_groups,
    bcm_multicast_t * groups,
    int *enable)
{
    DNXF_UNIT_LOCK_INIT(unit);

    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_multicast_local_route_get_verify(unit, flags, nof_groups, groups, enable));

    DNXF_UNIT_LOCK_TAKE(unit);

    SHR_IF_ERR_EXIT(dnxf_fabric_multicast_multi_config_get(unit, flags, nof_groups, groups, NULL, enable));

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;

}

static int
dnxf_fabric_link_control_link_verify(
    int unit,
    bcm_port_t link,
    bcm_fabric_link_control_t type)
{
    int is_link_out_of_range = 0;
    SHR_FUNC_INIT_VARS(unit);

    if (link > 0 && (link >= dnxf_data_port.general.nof_links_get(unit) || !IS_SFI_PORT(unit, link)))
    {
        is_link_out_of_range = 1;
    }

    if ((type == bcmFabricLinkCableSwapMasterMode) || (type == bcmFabricLinkCableSwapEnable))
    {
        if (link < -1)
        {
            is_link_out_of_range = 1;
        }
    }
    else
    {
        if (link < 0)
        {
            is_link_out_of_range = 1;
        }
    }

    if (is_link_out_of_range)
    {
        SHR_ERR_EXIT(_SHR_E_PORT, "link %d is out of range", link);
    }

exit:
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_link_control_set_verify(
    int unit,
    bcm_port_t link,
    bcm_fabric_link_control_t type,
    int arg)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnxf_fabric_link_control_link_verify(unit, link, type));

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_control_set(
    int unit,
    bcm_port_t link,
    bcm_fabric_link_control_t type,
    int arg)
{
    bcm_port_t retimer_link_partner;

    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_link_control_set_verify(unit, link, type, arg));

    DNXF_UNIT_LOCK_TAKE(unit);

    switch (type)
    {
        case bcmFabricLinkCellFormat:
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_link_cell_format_set, (unit, link, arg, 0)));
            break;
        case bcmFabricLinkCellInterleavingEnable:
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcmFabricLinkCellInterleavingEnable is not supported");
            break;
        case bcmFabricLLFControlSource:
            if (dnxf_data_fabric.congestion.feature_get(unit, dnxf_data_fabric_congestion_credit_based_llfc_supported))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                             "bcmFabricLLFControlSource not supported for this device. To enable LLFC please use bcmFabricLLFControlType");
            }
            else
            {
                SHR_IF_ERR_EXIT(_bcm_dnxf_fabric_link_control_set_llfc_control_source(unit, link, arg));
            }
            break;
        case bcmFabricLLFControlType:
            if (dnxf_data_fabric.congestion.feature_get(unit, dnxf_data_fabric_congestion_credit_based_llfc_supported))
            {
                SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_links_llfc_type_set, (unit, link, arg)));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                             "bcmFabricLLFControlType not supported for this device. To enable LLFC please use bcmFabricLLFControlSource");
            }
            break;
        case bcmFabricLinkRepeaterDestinationLink:
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcmFabricLinkRepeaterDestinationLink is not supported");
            break;
        case bcmFabricLinkIsolate:
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_links_isolate_set,
                                                  (unit, link,
                                                   arg ? soc_dnxc_isolation_status_isolated :
                                                   soc_dnxc_isolation_status_active)));
            break;
        case bcmFabricLinkPcpEnable:
            if (!dnxf_data_fabric.cell.feature_get(unit, dnxf_data_fabric_cell_format_always_with_pcp))
            {
                SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_links_pcp_enable_set, (unit, link, arg)));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "PCP is always enabled for device %s Type\n", soc_dev_name(unit));
            }
            break;
        case bcmFabricLinkRepeaterEnable:
            if (dnxf_data_port.general.feature_get(unit, dnxf_data_port_general_is_connection_to_repeater_supported))
            {
                SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL
                                (unit, mbcm_dnxf_fabric_link_repeater_enable_set, (unit, link, arg ? 1 : 0)));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Connectiion to repeater device is not supported for device %s Type\n",
                             soc_dev_name(unit));
            }
            break;
        case bcmFabricLinkRetimerConnect:
            if (!dnxf_data_port.retimer.feature_get(unit, dnxf_data_port_retimer_is_supported))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Retimer is not supported for device %s Type\n", soc_dev_name(unit));
            }
            else
            {
                SHR_IF_ERR_EXIT(dnxf_fabric_link_retimer_connect_set(unit, link, arg));
            }
            break;
        case bcmFabricLinkRetimerFecEnable:
            if (!dnxf_data_port.retimer.feature_get(unit, dnxf_data_port_retimer_is_supported))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Retimer is not supported for device %s Type\n", soc_dev_name(unit));
            }
            SHR_IF_ERR_EXIT(dnxf_fabric_link_retimer_connect_get(unit, link, &retimer_link_partner));
            if (retimer_link_partner != -1)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG,
                             "Link %d: Retimer is enabled. Setting retimer FEC can be done only BEFORE enabling retimer.\n",
                             link);
            }
            SHR_IF_ERR_EXIT(portmod_port_pass_through_fec_enable_set(unit, link, arg));
            break;
        case bcmFabricLinkCableSwapEnable:
        case bcmFabricLinkCableSwapMasterMode:
            if (!dnxf_data_port.general.feature_get(unit, dnxf_data_port_general_is_cable_swap_supported))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Cable swap is not supported for device %s Type\n", soc_dev_name(unit));
            }
            SHR_IF_ERR_EXIT(soc_dnxc_port_cable_swap_set(unit, link, type, arg));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Unsupported Type %d", type);
    }

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;

}

static int
dnxf_fabric_link_control_get_verify(
    int unit,
    bcm_port_t link,
    bcm_fabric_link_control_t type,
    int *arg)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(arg, _SHR_E_PARAM, "arg");

    SHR_IF_ERR_EXIT(dnxf_fabric_link_control_link_verify(unit, link, type));

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_control_get(
    int unit,
    bcm_port_t link,
    bcm_fabric_link_control_t type,
    int *arg)
{
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_link_control_get_verify(unit, link, type, arg));

    DNXF_UNIT_LOCK_TAKE(unit);

    switch (type)
    {
        case bcmFabricLinkCellFormat:
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_link_cell_format_get,
                                                  (unit, link, (uint32 *) arg)));
            break;
        case bcmFabricLinkCellInterleavingEnable:
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcmFabricLinkCellInterleavingEnable is not supported");
            break;
        case bcmFabricLLFControlSource:
            if (dnxf_data_fabric.congestion.feature_get(unit, dnxf_data_fabric_congestion_credit_based_llfc_supported))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                             "bcmFabricLLFControlSource not supported for this device. To enable LLFC please use bcmFabricLLFControlType");
            }
            else
            {
                SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_links_llf_control_source_get,
                                                      (unit, link, (soc_dnxc_fabric_pipe_t *) arg)));
            }
            break;
        case bcmFabricLLFControlType:
            if (dnxf_data_fabric.congestion.feature_get(unit, dnxf_data_fabric_congestion_credit_based_llfc_supported))
            {
                SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_links_llfc_type_get, (unit, link, arg)));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                             "bcmFabricLLFControlType not supported for this device. To enable LLFC please use bcmFabricLLFControlSource");
            }
            break;
        case bcmFabricLinkRepeaterDestinationLink:
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcmFabricLinkRepeaterDestinationLink is not supported");
            break;
        case bcmFabricLinkIsolate:
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_links_isolate_get,
                                                  (unit, link, (soc_dnxc_isolation_status_t *) arg)));
            break;
        case bcmFabricLinkPcpEnable:
            if (!dnxf_data_fabric.cell.feature_get(unit, dnxf_data_fabric_cell_format_always_with_pcp))
            {
                SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_links_pcp_enable_get, (unit, link, arg)));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "PCP is always enabled for device %s Type\n", soc_dev_name(unit));
            }
            break;
        case bcmFabricLinkRepeaterEnable:
            if (dnxf_data_port.general.feature_get(unit, dnxf_data_port_general_is_connection_to_repeater_supported))
            {
                SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL
                                (unit, mbcm_dnxf_fabric_link_repeater_enable_get, (unit, link, arg)));

            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Connectiion to repeater device is not supported for device %s Type\n",
                             soc_dev_name(unit));
            }
            break;
        case bcmFabricLinkRetimerConnect:
            if (!dnxf_data_port.retimer.feature_get(unit, dnxf_data_port_retimer_is_supported))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Retimer is not supported for device %s Type\n", soc_dev_name(unit));
            }
            else
            {
                SHR_IF_ERR_EXIT(dnxf_fabric_link_retimer_connect_get(unit, link, arg));
            }
            break;
        case bcmFabricLinkRetimerFecEnable:
            if (!dnxf_data_port.retimer.feature_get(unit, dnxf_data_port_retimer_is_supported))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Retimer is not supported for device %s Type\n", soc_dev_name(unit));
            }
            SHR_IF_ERR_EXIT(portmod_port_pass_through_fec_enable_get(unit, link, arg));
            break;
        case bcmFabricLinkCableSwapEnable:
        case bcmFabricLinkCableSwapMasterMode:
            if (!dnxf_data_port.general.feature_get(unit, dnxf_data_port_general_is_cable_swap_supported))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Cable swap is not supported for device %s Type\n", soc_dev_name(unit));
            }
            SHR_IF_ERR_EXIT(soc_dnxc_port_cable_swap_get(unit, link, type, arg));
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Unsupported Type %d", type);
    }

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_threshold_add(
    int unit,
    uint32 flags,
    int *fifo_type)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcm_fabric_link_threshold_add is not supported for this device");

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_threshold_delete(
    int unit,
    int fifo_type)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_ERR_EXIT(_SHR_E_UNAVAIL, "bcm_fabric_link_threshold_delete is not supported for this device");

exit:
    SHR_FUNC_EXIT;

}

int
bcm_dnxf_fabric_link_thresholds_set(
    int unit,
    int fifo_type,
    uint32 count,
    bcm_fabric_link_threshold_type_t * type,
    int *value)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                 "bcm_fabric_link_thresholds_set is not supported for this device. Use bcm_fabric_profile_threshold_set instead.");

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_thresholds_get(
    int unit,
    int fifo_type,
    uint32 count,
    bcm_fabric_link_threshold_type_t * type,
    int *value)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                 "bcm_fabric_link_thresholds_get is not supported for this device. Use bcm_fabric_profile_threshold_get instead.");

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_thresholds_pipe_set(
    int unit,
    int fifo_type,
    bcm_fabric_pipe_t pipe,
    uint32 flags,
    uint32 count,
    bcm_fabric_link_threshold_type_t * type,
    int *value)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                 "bcm_fabric_link_thresholds_pipe_set is not supported for this device. Use bcm_fabric_profile_threshold_set instead.");

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_thresholds_pipe_get(
    int unit,
    int fifo_type,
    bcm_fabric_pipe_t pipe,
    uint32 flags,
    uint32 count,
    bcm_fabric_link_threshold_type_t * type,
    int *value)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                 "bcm_fabric_link_thresholds_pipe_get is not supported for this device. Use bcm_fabric_profile_threshold_get instead.");

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_thresholds_attach(
    int unit,
    int fifo_type,
    uint32 links_count,
    bcm_port_t * links)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                 "bcm_fabric_link_thresholds_attach is not supported for this device. Use bcm_fabric_profile_threshold_set instead.");

exit:
    SHR_FUNC_EXIT;

}

int
bcm_dnxf_fabric_link_thresholds_retrieve(
    int unit,
    int fifo_type,
    uint32 links_count_max,
    bcm_port_t * links,
    uint32 *links_count)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_ERR_EXIT(_SHR_E_UNAVAIL,
                 "bcm_fabric_link_thresholds_retrieve is not supported for this device. Use bcm_fabric_profile_threshold_get instead.");

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_status_get(
    int unit,
    bcm_port_t link_id,
    uint32 *link_status,
    uint32 *errored_token_count)
{
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(link_status, _SHR_E_PARAM, "link_status");
    SHR_NULL_CHECK(errored_token_count, _SHR_E_PARAM, "errored_token_count");

    DNXF_LINK_INPUT_CHECK(unit, link_id);

    DNXF_UNIT_LOCK_TAKE(unit);

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_link_status_get,
                                          (unit, link_id, link_status, errored_token_count)));

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_connectivity_status_get(
    int unit,
    int link_partner_max,
    bcm_fabric_link_connectivity_t * link_partner_array,
    int *link_partner_count)
{
    bcm_port_t link_id = 0;
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(link_partner_array, _SHR_E_PARAM, "link_partner_array");
    SHR_NULL_CHECK(link_partner_count, _SHR_E_PARAM, "link_partner_count");

    DNXF_UNIT_LOCK_TAKE(unit);

    *link_partner_count = 0;

    BCM_PBMP_ITER(PBMP_SFI_ALL(unit), link_id)
    {
        if (*link_partner_count >= link_partner_max)
        {
            *link_partner_count = 0;
            SHR_ERR_EXIT(_SHR_E_FULL, "link_partner_array is too small");
        }

        link_partner_array[*link_partner_count].local_link_id = link_id;

        SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_link_connectivity_status_get,
                                              (unit, link_id, &(link_partner_array[*link_partner_count]))));

        (*link_partner_count)++;
    }

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_connectivity_status_single_get(
    int unit,
    bcm_port_t link_id,
    bcm_fabric_link_connectivity_t * link_partner_info)
{
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(link_partner_info, _SHR_E_PARAM, "link_partner_info");
    DNXF_LINK_INPUT_CHECK(unit, link_id);

    DNXF_UNIT_LOCK_TAKE(unit);

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL
                    (unit, mbcm_dnxf_fabric_link_connectivity_status_get, (unit, link_id, link_partner_info)));

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_reachability_status_get(
    int unit,
    int moduleid,
    int links_max,
    uint32 *links_array,
    int *links_count)
{
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(links_array, _SHR_E_PARAM, "links_array");
    SHR_NULL_CHECK(links_count, _SHR_E_PARAM, "links_count");

    if (!SOC_DNXF_CHECK_MODULE_ID(moduleid))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal moduleid %d", moduleid);
    }

    DNXF_UNIT_LOCK_TAKE(unit);
    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_reachability_status_get,
                                          (unit, moduleid, links_max, links_array, links_count)));

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_route_rx(
    int unit,
    uint32 flags,
    uint32 data_out_max_size,
    uint32 *data_out,
    uint32 *data_out_size)
{
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(data_out, _SHR_E_PARAM, "data_out");
    SHR_NULL_CHECK(data_out_size, _SHR_E_PARAM, "data_out_size");
    if (data_out_max_size == 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "buffer is too small");
    }

    DNXF_UNIT_LOCK_TAKE(unit);

    SHR_IF_ERR_EXIT(soc_dnxf_sr_cell_payload_receive(unit, flags, data_out_max_size, data_out_size, data_out));

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_route_tx(
    int unit,
    uint32 flags,
    bcm_fabric_route_t * route,
    uint32 data_in_size,
    uint32 *data_in)
{

    DNXF_UNIT_LOCK_INIT(unit);

    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(route, _SHR_E_PARAM, "route");
    SHR_NULL_CHECK(route->hop_ids, _SHR_E_PARAM, "route->hop_ids");
    SHR_NULL_CHECK(data_in, _SHR_E_PARAM, "data_in");
    if (data_in_size == 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "no data to send");
    }

    DNXF_UNIT_LOCK_TAKE(unit);

#ifdef ADAPTER_SERVER_MODE
    {

        int i, nof_signals = 0, src_port = 0;
        char packet_data[WORDS2BYTES(DNXC_VSC256_SR_DATA_CELL_PAYLOAD_MAX_LENGTH_U32)];
        adapter_ms_id_e ms_id = ADAPTER_MS_ID_FIRST_MS;

        sal_memset(packet_data, 0x0, sizeof(uint32) * DNXC_VSC256_SR_DATA_CELL_PAYLOAD_MAX_LENGTH_U32);

        for (i = 0; i < data_in_size; i++)
        {
            sal_snprintf(packet_data + (i * sizeof(uint32)), sizeof(uint32) + 1, "%x", data_in[i]);
        }

        SHR_IF_ERR_EXIT(adapter_send_buffer
                        (unit, (uint32) ms_id, src_port, WORDS2BYTES(data_in_size), (unsigned char *) packet_data,
                         nof_signals));
    }
#else
    {
        soc_dnxc_fabric_route_t soc_route;
        soc_route.pipe_id = route->pipe_id;
        soc_route.number_of_hops = route->number_of_hops;
        soc_route.hop_ids = route->hop_ids;
        soc_route.dest_device_type = (_shr_fabric_device_type_t) (route->dest_device_type);

        SHR_IF_ERR_EXIT(soc_dnxf_sr_cell_send(unit, flags, &soc_route, data_in_size, data_in));
    }
#endif

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
_bcm_dnxf_fabric_link_flow_status_cell_format_set(
    int unit,
    bcm_port_t port,
    int cell_format)
{
    int rv;
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    rv = MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_links_flow_status_control_cell_format_set,
                               (unit, port, (soc_dnxf_fabric_link_cell_size_t) cell_format));
    SHR_IF_ERR_EXIT(rv);

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
_bcm_dnxf_fabric_link_flow_status_cell_format_get(
    int unit,
    bcm_port_t port,
    int *cell_format)
{
    int rv;
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    rv = MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_links_flow_status_control_cell_format_get,
                               (unit, port, (soc_dnxf_fabric_link_cell_size_t *) cell_format));
    SHR_IF_ERR_EXIT(rv);

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_link_remote_pipe_mapping_get_verify(
    int unit,
    bcm_port_t port,
    bcm_fabric_link_remote_pipe_mapping_t * mapping_config)
{
    soc_dnxf_fabric_link_remote_pipe_mapping_t soc_mapping_config;
    SHR_FUNC_INIT_VARS(unit);

    DNXF_LINK_INPUT_CHECK(unit, port);

    sal_memset(&soc_mapping_config, 0, sizeof(soc_dnxf_fabric_link_remote_pipe_mapping_t));

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL
                    (unit, mbcm_dnxf_fabric_links_pipe_map_get, (unit, port, &soc_mapping_config)));

    if (soc_mapping_config.num_of_remote_pipes > mapping_config->remote_pipe_mapping_max_size)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Size of buffer should be bigger than the number of remote pipes");
    }

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_remote_pipe_mapping_get(
    int unit,
    bcm_port_t port,
    bcm_fabric_link_remote_pipe_mapping_t * mapping_config)
{
    int i;
    soc_dnxf_fabric_link_remote_pipe_mapping_t soc_mapping_config;
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_link_remote_pipe_mapping_get_verify(unit, port, mapping_config));

    DNXF_UNIT_LOCK_TAKE(unit);

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL
                    (unit, mbcm_dnxf_fabric_links_pipe_map_get, (unit, port, &soc_mapping_config)));

    mapping_config->num_of_remote_pipes = soc_mapping_config.num_of_remote_pipes;
    for (i = 0; i < mapping_config->num_of_remote_pipes; i++)
    {
        mapping_config->remote_pipe_mapping[i] = soc_mapping_config.remote_pipe_mapping[i] + bcmFabricPipe0;
    }

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_link_remote_pipe_mapping_set_verify(
    int unit,
    bcm_port_t port,
    bcm_fabric_link_remote_pipe_mapping_t * mapping_config)
{
    int i;

    SHR_FUNC_INIT_VARS(unit);

    if (mapping_config->num_of_remote_pipes > DNXF_DATA_MAX_FABRIC_PIPES_MAX_NOF_PIPES)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Number of remote pipes (%d), is not supported, link %d.\n",
                     mapping_config->num_of_remote_pipes, port);
    }

    if (mapping_config->num_of_remote_pipes > mapping_config->remote_pipe_mapping_max_size)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Buffer max size is too small relative to number of remote pipes (%d), link %d.\n",
                     mapping_config->num_of_remote_pipes, port);
    }

    for (i = 0; i < mapping_config->num_of_remote_pipes; i++)
    {
        if ((mapping_config->remote_pipe_mapping[i] - bcmFabricPipe0) < 0 ||
            (mapping_config->remote_pipe_mapping[i] - bcmFabricPipe0) >= dnxf_data_fabric.pipes.nof_pipes_get(unit))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "invalid local pipe (%d), link %d",
                         (mapping_config->remote_pipe_mapping[i] - bcmFabricPipe0), port);
        }
    }

    DNXF_LINK_INPUT_CHECK(unit, port);

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_remote_pipe_mapping_set(
    int unit,
    bcm_port_t port,
    bcm_fabric_link_remote_pipe_mapping_t * mapping_config)
{
    soc_dnxf_fabric_link_remote_pipe_mapping_t soc_mapping_config;
    int i;
    int orig_enabled;
    DNXF_UNIT_LOCK_INIT(unit);

    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_link_remote_pipe_mapping_set_verify(unit, port, mapping_config));

    sal_memset(&soc_mapping_config, 0, sizeof(soc_dnxf_fabric_link_remote_pipe_mapping_t));

    soc_mapping_config.num_of_remote_pipes = mapping_config->num_of_remote_pipes;
    for (i = 0; i < mapping_config->num_of_remote_pipes; i++)
    {
        soc_mapping_config.remote_pipe_mapping[i] = mapping_config->remote_pipe_mapping[i] - bcmFabricPipe0;
    }

    DNXF_UNIT_LOCK_TAKE(unit);

    SHR_IF_ERR_EXIT(soc_dnxf_port_disable_and_save_enable_state(unit, port, 0, &orig_enabled));

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_links_pipe_map_set, (unit, port, soc_mapping_config)));

    SHR_IF_ERR_EXIT(soc_dnxf_port_restore_enable_state(unit, port, 0, orig_enabled));

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

static int
dnxf_fabric_profile_threshold_validate(
    int unit,
    int profile_id,
    bcm_fabric_threshold_id_t threshold_id,
    bcm_fabric_threshold_type_t threshold_type,
    uint32 flags,
    int value,
    int set_get)
{
    int pipe_idx, level_idx, link, cast_idx, prio_idx;

    uint32 th_validity_bmp, supported_flags_mask, supported_flags;

    SHR_FUNC_INIT_VARS(unit);

    if ((int) threshold_type < 0
        || threshold_type >= dnxf_data_fabric.congestion.thresholds_info_info_get(unit)->key_size[0])
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid threshold provided %d !", threshold_type);
    }

    supported_flags = dnxf_data_fabric.congestion.thresholds_info_get(unit, threshold_type)->supported_flags;
    supported_flags_mask = ~(supported_flags);

    if ((supported_flags_mask & flags) != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Threshold type %d does not support such flags %d !", threshold_type, flags);
    }

    if (SOC_DNXF_IS_FE2(unit) && flags != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "None of the flags is supported for FE2!");
    }

    switch (dnxf_data_fabric.congestion.thresholds_info_get(unit, threshold_type)->index_type)
    {
        case _shr_dnxf_cgm_index_type_pipe:
            if (threshold_id != _SHR_FABRIC_PIPE_ALL)
            {
                if (threshold_id >= dnxf_data_fabric.pipes.nof_pipes_get(unit))
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Pipe index %d is not within the valid range!", threshold_id);
                }
            }
            break;
        case _shr_dnxf_cgm_index_type_priority:
            if (threshold_id != -1)
            {
                if (threshold_id >= dnxf_data_fabric.congestion.nof_threshold_priorities_get(unit))
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Priority index %d is not within the valid range!", threshold_id);
                }
            }
            break;
        case _shr_dnxf_cgm_index_type_pipe_level:
            soc_dnxf_cgm_pipe_level_type_decode(unit, threshold_id, &level_idx, &pipe_idx);
            if (pipe_idx != _SHR_FABRIC_PIPE_ALL)
            {
                if (pipe_idx < 0 || pipe_idx >= dnxf_data_fabric.pipes.nof_pipes_get(unit))
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Pipe index %d is not within the valid range!", pipe_idx);
                }
            }
            if (level_idx != -1)
            {
                if (level_idx < 0 || level_idx >= dnxf_data_fabric.congestion.nof_threshold_levels_get(unit))
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Level index %d is not within the valid range!", level_idx);
                }
            }
            break;
        case _shr_dnxf_cgm_index_type_pipe_link:
            soc_dnxf_cgm_pipe_link_type_decode(unit, threshold_id, &link, &pipe_idx);
            if (pipe_idx != _SHR_FABRIC_PIPE_ALL)
            {
                if (pipe_idx < 0 || pipe_idx >= dnxf_data_fabric.pipes.nof_pipes_get(unit))
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Pipe index %d is not within the valid range!", pipe_idx);
                }
            }
            if (link != -1)
            {
                if (link < 0 || link >= dnxf_data_port.general.nof_links_get(unit))
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Link %d is not within the valid range!", link);
                }
            }
            break;
        case _shr_dnxf_cgm_index_type_cast_prio:
            soc_dnxf_cgm_cast_prio_type_decode(unit, threshold_id, &cast_idx, &prio_idx);
            if (cast_idx != -1)
            {
                if (cast_idx != 0 && cast_idx != 1)
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Cast index %d is not within the valid range!", cast_idx);
                }
            }
            if (prio_idx != -1)
            {
                if (prio_idx < 0 || prio_idx >= dnxf_data_fabric.congestion.nof_threshold_priorities_get(unit))
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM, "Priority index %d is not within the valid range!", prio_idx);
                }
            }
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Unknown threshold index received from DNXF DATA!");
    }

    if ((flags & _SHR_FABRIC_TH_FLAG_LR) && (flags & _SHR_FABRIC_TH_FLAG_NLR))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Configuring NLR and LR together is not supported!");
    }

    if ((flags & _SHR_FABRIC_TH_FLAG_FE1_ONLY) && (flags & _SHR_FABRIC_TH_FLAG_FE3_ONLY))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Configuring FE1_ONLY and FE3_ONLY together is not supported!");
    }

    if (profile_id != 1 && profile_id != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Profile ID can be either 0  or 1!");
    }

    th_validity_bmp = dnxf_data_fabric.congestion.thresholds_info_get(unit, threshold_type)->th_validity_bmp;

    if ((th_validity_bmp & _SHR_FABRIC_CGM_VALIDITY_NOT_PROFILE_DEPENDENT) && profile_id != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, " Threshold type is not profile dependant!");
    }

    if (th_validity_bmp & _SHR_FABRIC_CGM_VALIDITY_ONLY_TWO_PIPES)
    {
        if (dnxf_data_fabric.congestion.thresholds_info_get(unit, threshold_type)->index_type ==
            _shr_dnxf_cgm_index_type_pipe)
        {
            pipe_idx = threshold_id;
        }
        else if (dnxf_data_fabric.congestion.thresholds_info_get(unit, threshold_type)->index_type ==
                 _shr_dnxf_cgm_index_type_pipe_level)
        {
            soc_dnxf_cgm_pipe_level_type_decode(unit, threshold_id, &level_idx, &pipe_idx);
        }
        else if (dnxf_data_fabric.congestion.thresholds_info_get(unit, threshold_type)->index_type ==
                 _shr_dnxf_cgm_index_type_pipe_link)
        {
            soc_dnxf_cgm_pipe_link_type_decode(unit, threshold_id, &link, &pipe_idx);
        }
        else
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Not a pipe type threhold index.");
        }

        if ((pipe_idx == 2) || (pipe_idx == -1))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, " The value for this threshold cannot be set for pipe 2 or pipe ALL!");
        }
    }

    if (set_get == _SHR_FABRIC_FLAG_SET)
    {
        if (th_validity_bmp & _SHR_FABRIC_CGM_VALIDITY_MODULO_4)
        {
            if ((value % 4) != 0)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             " Threshold value should be a number which divisible by 4 without a remainder!");
            }
        }

        if (th_validity_bmp & _SHR_FABRIC_CGM_DISABLE_NOT_SUPPORTED)
        {
            if (value == -1)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "SIZE Type thresholds cannot be disabled and receive value -1");
            }
        }
    }
exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_profile_threshold_set(
    int unit,
    int profile_id,
    bcm_fabric_threshold_id_t threshold_id,
    bcm_fabric_threshold_type_t threshold_type,
    uint32 flags,
    int value)
{
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_profile_threshold_validate
                           (unit, profile_id, threshold_id, threshold_type, flags, value, _SHR_FABRIC_FLAG_SET));

    DNXF_UNIT_LOCK_TAKE(unit);

    SHR_IF_ERR_EXIT(soc_dnxf_cgm_profile_threshold_set(unit, profile_id, threshold_id,
                                                       (_shr_dnxf_threshold_type_t) threshold_type, flags, value));

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_profile_threshold_get(
    int unit,
    int profile_id,
    bcm_fabric_threshold_id_t threshold_id,
    bcm_fabric_threshold_type_t threshold_type,
    uint32 flags,
    int *value)
{
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnxf_fabric_profile_threshold_validate
                           (unit, profile_id, threshold_id, threshold_type, flags, *value, _SHR_FABRIC_FLAG_GET));

    DNXF_UNIT_LOCK_TAKE(unit);

    SHR_IF_ERR_EXIT(soc_dnxf_cgm_profile_threshold_get(unit, profile_id, threshold_id,
                                                       (_shr_dnxf_threshold_type_t) threshold_type, flags, value));

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_profile_set(
    int unit,
    int profile_id,
    uint32 flags,
    uint32 links_count,
    bcm_port_t * links)
{
    int rv, ii;
    bcm_port_t link;

    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    DNXF_UNIT_LOCK_TAKE(unit);

    SHR_NULL_CHECK(links, _SHR_E_PARAM, "links");

    if (links_count > dnxf_data_port.general.nof_links_get(unit))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Links count not whitin the valid range!");
    }

    if (profile_id != 0 && profile_id != 1)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Profile ID can be either 0 or 1!");
    }

    for (ii = 0; ii < links_count; ii++)
    {
        link = links[ii];

        if (link < 0 || link > dnxf_data_port.general.nof_links_get(unit) - 1)
        {
            SHR_ERR_EXIT(_SHR_E_PORT, "Port %d is not in the valid range or is uninitialized! \n", link);
        }

        if (!PBMP_MEMBER(PBMP_SFI_ALL(unit), link))
        {
            SHR_ERR_EXIT(_SHR_E_PORT, "Port %d is not a valid link! \n", link);
        }

    }

    rv = MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_link_profile_set, (unit, profile_id, flags, links_count, links));
    SHR_IF_ERR_EXIT(rv);

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_link_profile_get(
    int unit,
    int profile_id,
    uint32 flags,
    uint32 links_count_max,
    uint32 *links_count,
    bcm_port_t * links)
{
    int rv;

    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(links, _SHR_E_PARAM, "links_count");
    SHR_NULL_CHECK(links, _SHR_E_PARAM, "links");

    if (profile_id != 0 && profile_id != 1)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Profile ID can be either 0 or 1!");
    }

    rv = MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_link_profile_get,
                               (unit, profile_id, flags, links_count_max, links_count, links));
    SHR_IF_ERR_EXIT(rv);

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_rci_resolution_set(
    int unit,
    uint32 flags,
    bcm_fabric_rci_resolution_key_t * key,
    bcm_fabric_rci_resolution_config_t * config)
{
    int rv;

    soc_dnxf_fabric_rci_resolution_key_t dnxf_key;
    soc_dnxf_fabric_rci_resolution_config_t dnxf_config;
    uint32 nof_rci_bits, nof_rci_levels;
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(key, _SHR_E_PARAM, "key");
    SHR_NULL_CHECK(config, _SHR_E_PARAM, "config");

    nof_rci_bits = dnxf_data_fabric.congestion.nof_rci_bits_get(unit);
    nof_rci_levels = (1 << nof_rci_bits);

    if ((key->pipe != _SHR_FABRIC_PIPE_ALL)
        && ((key->pipe >= dnxf_data_fabric.pipes.nof_pipes_get(unit)) || (key->pipe < 0)))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "invalid pipe %d", key->pipe);
    }

    if (key->shared_rci >= nof_rci_levels)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "invalid shared RCI value %d", key->shared_rci);
    }

    if (key->guaranteed_rci >= nof_rci_levels)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "invalid guaranteed RCI value %d", key->guaranteed_rci);
    }

    if (config->resolved_rci >= nof_rci_levels)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "invalid resolved RCI value %d", config->resolved_rci);
    }

    dnxf_key.pipe = key->pipe;
    dnxf_key.shared_rci = key->shared_rci;
    dnxf_key.guaranteed_rci = key->guaranteed_rci;
    dnxf_config.resolved_rci = config->resolved_rci;

    rv = MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_rci_resolution_set, (unit, &dnxf_key, &dnxf_config));
    SHR_IF_ERR_EXIT(rv);

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_rci_resolution_get(
    int unit,
    uint32 flags,
    bcm_fabric_rci_resolution_key_t * key,
    bcm_fabric_rci_resolution_config_t * config)
{
    int rv;
    soc_dnxf_fabric_rci_resolution_key_t dnxf_key;
    soc_dnxf_fabric_rci_resolution_config_t dnxf_config;
    uint32 nof_rci_bits, nof_rci_levels;
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(key, _SHR_E_PARAM, "key");
    SHR_NULL_CHECK(config, _SHR_E_PARAM, "config");

    nof_rci_bits = dnxf_data_fabric.congestion.nof_rci_bits_get(unit);
    nof_rci_levels = (1 << nof_rci_bits);

    if ((key->pipe != _SHR_FABRIC_PIPE_ALL)
        && ((key->pipe >= dnxf_data_fabric.pipes.nof_pipes_get(unit)) || (key->pipe < 0)))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "invalid pipe %d", key->pipe);
    }

    if (key->shared_rci >= nof_rci_levels)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "invalid shared RCI value %d", key->shared_rci);
    }

    if (key->guaranteed_rci >= nof_rci_levels)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "invalid guaranteed RCI value %d", key->guaranteed_rci);
    }

    dnxf_key.pipe = key->pipe;
    dnxf_key.shared_rci = key->shared_rci;
    dnxf_key.guaranteed_rci = key->guaranteed_rci;

    rv = MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_rci_resolution_get, (unit, &dnxf_key, &dnxf_config));
    SHR_IF_ERR_EXIT(rv);

    config->resolved_rci = dnxf_config.resolved_rci;

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_stat_get(
    int unit,
    uint32 flags,
    bcm_fabric_stat_index_t index,
    bcm_fabric_stat_t stat,
    uint64 *value)
{
    int rv;

    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    DNXF_UNIT_LOCK_TAKE(unit);

    SHR_NULL_CHECK(value, _SHR_E_PARAM, "value");

    rv = MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_fabric_stat_get, (unit, index, stat, value));
    SHR_IF_ERR_EXIT(rv);

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_tx(
    int unit,
    bcm_pkt_t * tx_pkt,
    void *cookie)
{
    int rv = _SHR_E_NONE;
    int cell_data_size = 0, offset = 0;
    dnxc_dest_routed_cell_t cell;
    uint8 ftmh_header_buf[DNXC_FTMH_BASE_HEADER_SIZE_BYTES];
    uint16 crc;
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&cell, 0, sizeof(dnxc_dest_routed_cell_t));
    sal_memset(ftmh_header_buf, 0, DNXC_FTMH_BASE_HEADER_SIZE_BYTES);

    SHR_IF_ERR_EXIT(bcm_dnxf_stk_modid_get(unit, (int *) &(cell.header.source_modid)));
    cell.header.dest_modid = tx_pkt->dest_mod;

    if (tx_pkt->pkt_data->len >
        (dnxf_data_fabric.cell.max_vsc_format_size_get(unit) - DNXC_FTMH_HEADER_OFFSET_BYTES -
         DNXC_FTMH_CRC_SIZE_BYTES))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Payload size may be up to %d bytes! Provided value is %d ",
                     (dnxf_data_fabric.cell.max_vsc_format_size_get(unit) - DNXC_FTMH_HEADER_OFFSET_BYTES -
                      DNXC_FTMH_CRC_SIZE_BYTES), tx_pkt->pkt_data->len);
    }

    cell_data_size = DNXC_FTMH_HEADER_OFFSET_BYTES + tx_pkt->pkt_data->len + DNXC_FTMH_CRC_SIZE_BYTES;

    SHR_IF_ERR_EXIT(soc_dnxc_ftmh_base_build_header
                    (unit, tx_pkt->dest_port, cell_data_size, DNXC_FTMH_BASE_HEADER_SIZE_BYTES, ftmh_header_buf));

    offset = 0;
    sal_memcpy(&(cell.payload[offset]), ftmh_header_buf, DNXC_FTMH_BASE_HEADER_SIZE_BYTES);
    offset += DNXC_FTMH_BASE_HEADER_SIZE_BYTES;

    sal_memset(&(cell.payload[offset]), 0, DNXC_FTMH_BASE_HEADER_LB_EXT_MIN_SIZE_BYTES);

    offset += DNXC_FTMH_BASE_HEADER_LB_EXT_MIN_SIZE_BYTES;
    sal_memcpy(&(cell.payload[offset]), tx_pkt->pkt_data->data, tx_pkt->pkt_data->len);

    SHR_IF_ERR_EXIT(soc_dnxc_crc_calc(unit, cell.payload, cell_data_size, &crc));
    _shr_uint16_write(&(cell.payload[cell_data_size - DNXC_FTMH_CRC_SIZE_BYTES]), crc);

    cell.payload_size = cell_data_size;

    rv = MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_cpu_cell_send, (unit, &cell));
    SHR_IF_ERR_EXIT(rv);

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

static shr_error_e
dnxf_fabric_system_upgrade_phase1_verify(
    int unit,
    int flags,
    int *master_id,
    bcm_fabric_system_upgrade_target_t * target,
    int is_set)
{
    uint32 target_value = 0;
    uint32 state_0, state_1, state_2;
    uint32 max_master_id;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(master_id, _SHR_E_PARAM, "master_id");
    SHR_NULL_CHECK(target, _SHR_E_PARAM, "target");

    if (is_set)
    {
        max_master_id = dnxf_data_fabric.system_upgrade.max_master_id_get(unit);

        if (*master_id > max_master_id)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "master_id=%d should be less than %d.\n", *master_id, max_master_id + 1);
        }
        SHR_IF_ERR_EXIT(dnxf_state.system_upgrade.state_0.get(unit, &state_0));
        SHR_IF_ERR_EXIT(dnxf_state.system_upgrade.state_1.get(unit, &state_1));
        SHR_IF_ERR_EXIT(dnxf_state.system_upgrade.state_2.get(unit, &state_2));

        if (BCM_FABRIC_SYSTEM_UPGRADE_FIRST_ITERATION == flags)
        {

            SHR_MAX_VERIFY(*target, bcmFabricSystemUpgradeTargetCount - 1, _SHR_E_PARAM,
                           "target=%d should be less than %d.\n", *target, bcmFabricSystemUpgradeTargetCount);
            target_value = dnxf_data_fabric.system_upgrade.target_get(unit, *target)->value;
            if (state_0 == target_value)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Target has been achieved, no need to upgrade.\n");
            }
        }
        else if (BCM_FABRIC_SYSTEM_UPGRADE_REPEAT_ITERATION == flags)
        {
            if (state_0 >= state_1)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "No error happened during system upgrade, don't need to repeat the iter.\n");
            }
        }
        else if (0 == flags)
        {
            if (state_0 != state_1)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Please make sure BCM_FABRIC_SYSTEM_UPGRADE_FIRST_ITERATION is called and each system upgrade iter has completed.\n");
            }
            if (state_0 == state_2)
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Target has been achieved, no need to upgrade.\n");
            }
        }
        else
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Flags is invalid, should be 0 or BCM_FABRIC_SYSTEM_UPGRADE_xxx.\n");
        }
    }

exit:
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_system_upgrade_phase1_set(
    int unit,
    int flags,
    int master_id,
    bcm_fabric_system_upgrade_target_t target)
{
    int in_progress;
    uint32 current_target;
    uint32 state_1;
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnxf_fabric_system_upgrade_phase1_verify(unit, flags, &master_id, &target, 1));

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_system_upgrade_in_progress_get, (unit, &in_progress)));
    if (in_progress)
    {
        SHR_ERR_EXIT(_SHR_E_CONFIG,
                     "The system upgrade is in progress, please call bcm_fabric_system_upgrade_phase3_get() to check the status.\n");
    }

    if (BCM_FABRIC_SYSTEM_UPGRADE_FIRST_ITERATION == flags)
    {
        SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_system_upgrade_phase1_init, (unit, master_id)));

        SHR_IF_ERR_EXIT(dnxf_state.system_upgrade.state_0.get(unit, &current_target));
        current_target += dnxf_data_fabric.system_upgrade.param_5_get(unit);
        SHR_IF_ERR_EXIT(dnxf_state.system_upgrade.state_1.set(unit, current_target));
        SHR_IF_ERR_EXIT(dnxf_state.system_upgrade.state_2.set(unit,
                                                              dnxf_data_fabric.system_upgrade.target_get(unit,
                                                                                                         target)->value));
        SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_system_upgrade_target_set, (unit, current_target)));

    }
    else if (0 == flags)
    {
        SHR_IF_ERR_EXIT(dnxf_state.system_upgrade.state_1.get(unit, &state_1));
        state_1 += dnxf_data_fabric.system_upgrade.param_5_get(unit);
        SHR_IF_ERR_EXIT(dnxf_state.system_upgrade.state_1.set(unit, state_1));
        SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_system_upgrade_target_set, (unit, state_1)));

    }

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_system_upgrade_enable_set, (unit, 1)));

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_system_upgrade_phase1_get(
    int unit,
    int flags,
    int *master_id,
    bcm_fabric_system_upgrade_target_t * target)
{
    int i;
    uint32 state_2;
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnxf_fabric_system_upgrade_phase1_verify(unit, flags, master_id, target, 0));

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_system_upgrade_master_id_get, (unit, master_id)));

    SHR_IF_ERR_EXIT(dnxf_state.system_upgrade.state_2.get(unit, &state_2));
    if (0 == state_2)
    {
        *target = bcmFabricSystemUpgradeTargetInvalid;
    }
    else
    {
        for (i = 0; i < dnxf_data_fabric.system_upgrade.target_info_get(unit)->key_size[0]; ++i)
        {
            if (dnxf_data_fabric.system_upgrade.target_get(unit, i)->value == state_2)
            {
                *target = (bcm_fabric_system_upgrade_target_t) i;
                break;
            }
        }

        if (bcmFabricSystemUpgradeTargetCount == i)
        {
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Target values mismatch.\n");
        }
    }

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_system_upgrade_phase2_trig(
    int unit,
    int flags)
{
    int enable;
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_system_upgrade_enable_get, (unit, &enable)));

    if (!enable)
    {
        SHR_ERR_EXIT(_SHR_E_CONFIG,
                     "System upgrade is not enabled. Please call bcm_fabric_system_upgrade_phase1_set() first.\n");
    }
    else
    {
        SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_system_upgrade_trig, (unit)));
    }

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

int
bcm_dnxf_fabric_system_upgrade_phase3_get(
    int unit,
    int flags,
    bcm_fabric_system_upgrade_status_t * status)
{
    int in_progress = 0;
    int done = 0;
    int ok = 0;
    int is_triggered;
    uint32 state_0, state_1, state_2;
    DNXF_UNIT_LOCK_INIT(unit);
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(status, _SHR_E_PARAM, "status");

    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_system_upgrade_in_progress_get, (unit, &in_progress)));
    SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_system_upgrade_done_get, (unit, &done)));

    if (in_progress)
    {
        *status = bcmFabricSystemUpgradeStatusInProgress;
    }
    else if (done)
    {
        SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_system_upgrade_ok_get, (unit, &ok)));
        if (ok)
        {
            SHR_IF_ERR_EXIT(dnxf_state.system_upgrade.state_1.get(unit, &state_1));
            SHR_IF_ERR_EXIT(dnxf_state.system_upgrade.state_2.get(unit, &state_2));
            if (state_1 == state_2)
            {
                *status = bcmFabricSystemUpgradeStatusComplete;
            }
            else
            {
                *status = bcmFabricSystemUpgradeStatusOk;
            }
            SHR_IF_ERR_EXIT(dnxf_state.system_upgrade.state_0.set(unit, state_1));
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_system_upgrade_apply, (unit)));
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_system_upgrade_enable_set, (unit, 0)));
        }
        else
        {
            *status = bcmFabricSystemUpgradeStatusError;
        }
    }
    else
    {
        SHR_IF_ERR_EXIT(dnxf_state.system_upgrade.state_0.get(unit, &state_0));
        SHR_IF_ERR_EXIT(dnxf_state.system_upgrade.state_1.get(unit, &state_1));
        SHR_IF_ERR_EXIT(dnxf_state.system_upgrade.state_2.get(unit, &state_2));
        if (state_0 == state_1)
        {
            if (state_0 == state_2)
            {
                *status = bcmFabricSystemUpgradeStatusComplete;
            }
            else
            {
                *status = bcmFabricSystemUpgradeStatusOk;
            }
        }
        else
        {
            SHR_IF_ERR_EXIT(MBCM_DNXF_DRIVER_CALL(unit, mbcm_dnxf_system_upgrade_trig_get, (unit, &is_triggered)));

            if (!is_triggered)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG,
                             "System upgrade is not triggered. Please call bcm_fabric_system_upgrade_phase2_trig() first.\n");
            }
        }
    }

exit:
    DNXF_UNIT_LOCK_RELEASE(unit);
    SHR_FUNC_EXIT;
}

#undef BSL_LOG_MODULE

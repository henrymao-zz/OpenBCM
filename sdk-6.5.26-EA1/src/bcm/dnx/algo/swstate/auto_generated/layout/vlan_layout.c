/** \file algo/swstate/auto_generated/layout/vlan_layout.c
 *
 * sw state layout structure
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
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
#define BSL_LOG_MODULE BSL_LS_SWSTATEDNX_GENERAL

#include <bcm_int/dnx/algo/swstate/auto_generated/types/vlan_types.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/layout/vlan_layout.h>

dnxc_sw_state_layout_t layout_array_vlan[DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_VLAN_DB_NOF_PARAMS)];

shr_error_e
vlan_init_layout_structure(int unit)
{

    int idx;

    DNXC_SW_STATE_INIT_FUNC_DEFS;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_VLAN_DB);
    layout_array_vlan[idx].name = "vlan_db";
    layout_array_vlan[idx].type = "vlan_unit_state_t";
    layout_array_vlan[idx].total_size = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].size_of = sizeof(vlan_unit_state_t);
    layout_array_vlan[idx].parent  = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].first_child_index = 1;
    layout_array_vlan[idx].last_child_index = 10;
    layout_array_vlan[idx].next_node_index = 1;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_VLAN_DB__VLAN_INFO);
    layout_array_vlan[idx].name = "vlan_db__vlan_info";
    layout_array_vlan[idx].type = "vlan_info_t";
    layout_array_vlan[idx].total_size = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].size_of = sizeof(vlan_info_t);
    layout_array_vlan[idx].parent  = 0;
    layout_array_vlan[idx].first_child_index = 11;
    layout_array_vlan[idx].last_child_index = 11;
    layout_array_vlan[idx].next_node_index = 2;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_VLAN_DB__VSI);
    layout_array_vlan[idx].name = "vlan_db__vsi";
    layout_array_vlan[idx].type = "dnx_algo_res_t";
    layout_array_vlan[idx].doc = "VSI";
    layout_array_vlan[idx].total_size = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].size_of = sizeof(dnx_algo_res_t);
    layout_array_vlan[idx].parent  = 0;
    layout_array_vlan[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].next_node_index = 3;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_VLAN_DB__ACTION_ID_INGRESS);
    layout_array_vlan[idx].name = "vlan_db__action_id_ingress";
    layout_array_vlan[idx].type = "dnx_algo_res_t";
    layout_array_vlan[idx].doc = "ACTION_ID_INGRESS";
    layout_array_vlan[idx].total_size = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].size_of = sizeof(dnx_algo_res_t);
    layout_array_vlan[idx].parent  = 0;
    layout_array_vlan[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].next_node_index = 4;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_VLAN_DB__ACTION_ID_EGRESS);
    layout_array_vlan[idx].name = "vlan_db__action_id_egress";
    layout_array_vlan[idx].type = "dnx_algo_res_t";
    layout_array_vlan[idx].doc = "ACTION_ID_EGRESS";
    layout_array_vlan[idx].total_size = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].size_of = sizeof(dnx_algo_res_t);
    layout_array_vlan[idx].parent  = 0;
    layout_array_vlan[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].next_node_index = 5;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_VLAN_DB__VLAN_PORT_INGRESS_VIRTUAL_GPORT_ID);
    layout_array_vlan[idx].name = "vlan_db__vlan_port_ingress_virtual_gport_id";
    layout_array_vlan[idx].type = "dnx_algo_res_t";
    layout_array_vlan[idx].doc = "VLAN-PORT INGRESS VIRTUAL GPORT ID";
    layout_array_vlan[idx].total_size = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].size_of = sizeof(dnx_algo_res_t);
    layout_array_vlan[idx].parent  = 0;
    layout_array_vlan[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].next_node_index = 6;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_VLAN_DB__VLAN_PORT_EGRESS_VIRTUAL_GPORT_ID);
    layout_array_vlan[idx].name = "vlan_db__vlan_port_egress_virtual_gport_id";
    layout_array_vlan[idx].type = "dnx_algo_res_t";
    layout_array_vlan[idx].doc = "VLAN-PORT EGRESS VIRTUAL GPORT ID";
    layout_array_vlan[idx].total_size = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].size_of = sizeof(dnx_algo_res_t);
    layout_array_vlan[idx].parent  = 0;
    layout_array_vlan[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].next_node_index = 7;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_VLAN_DB__VLAN_RANGE_OUTER_PROFILE);
    layout_array_vlan[idx].name = "vlan_db__vlan_range_outer_profile";
    layout_array_vlan[idx].type = "dnx_algo_template_t";
    layout_array_vlan[idx].doc = "Outer vlan range profile template";
    layout_array_vlan[idx].total_size = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].size_of = sizeof(dnx_algo_template_t);
    layout_array_vlan[idx].parent  = 0;
    layout_array_vlan[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].next_node_index = 8;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_VLAN_DB__VLAN_RANGE_INNER_PROFILE);
    layout_array_vlan[idx].name = "vlan_db__vlan_range_inner_profile";
    layout_array_vlan[idx].type = "dnx_algo_template_t";
    layout_array_vlan[idx].doc = "Inner vlan range profile template";
    layout_array_vlan[idx].total_size = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].size_of = sizeof(dnx_algo_template_t);
    layout_array_vlan[idx].parent  = 0;
    layout_array_vlan[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].next_node_index = 9;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_VLAN_DB__VLAN_INFO__DEFAULT_VID);
    layout_array_vlan[idx].name = "vlan_db__vlan_info__default_vid";
    layout_array_vlan[idx].type = "bcm_vlan_t";
    layout_array_vlan[idx].total_size = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].size_of = sizeof(bcm_vlan_t);
    layout_array_vlan[idx].parent  = 1;
    layout_array_vlan[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_vlan[idx].next_node_index = DNXC_SW_STATE_LAYOUT_INVALID;


    dnxc_sw_state_layout_init_structure(unit, DNX_SW_STATE_VLAN_DB, layout_array_vlan, sw_state_layout_array[unit][VLAN_MODULE_ID], DNX_SW_STATE_VLAN_DB_NOF_PARAMS);

    DNXC_SW_STATE_FUNC_RETURN;
}

#undef BSL_LOG_MODULE

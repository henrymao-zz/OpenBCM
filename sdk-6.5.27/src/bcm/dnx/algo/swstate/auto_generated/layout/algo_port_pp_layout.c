/** \file algo/swstate/auto_generated/layout/algo_port_pp_layout.c
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

#include <bcm_int/dnx/algo/swstate/auto_generated/types/algo_port_pp_types.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/layout/algo_port_pp_layout.h>

dnxc_sw_state_layout_t layout_array_algo_port_pp[DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB_NOF_PARAMS)];

shr_error_e
algo_port_pp_init_layout_structure(int unit)
{

    int idx;

    DNXC_SW_STATE_INIT_FUNC_DEFS;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB);
    layout_array_algo_port_pp[idx].name = "algo_port_pp_db";
    layout_array_algo_port_pp[idx].type = "algo_port_pp_sw_state_t";
    layout_array_algo_port_pp[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].size_of = sizeof(algo_port_pp_sw_state_t);
    layout_array_algo_port_pp[idx].parent  = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].first_child_index = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__FIRST);
    layout_array_algo_port_pp[idx].last_child_index = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__LAST)-1;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__ESEM_DEFAULT_RESULT_PROFILE);
    layout_array_algo_port_pp[idx].name = "algo_port_pp_db__esem_default_result_profile";
    layout_array_algo_port_pp[idx].type = "dnx_algo_res_t";
    layout_array_algo_port_pp[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].size_of = sizeof(dnx_algo_res_t);
    layout_array_algo_port_pp[idx].parent  = 0;
    layout_array_algo_port_pp[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__PORT_PP_TPID_PROFILE_INGRESS);
    layout_array_algo_port_pp[idx].name = "algo_port_pp_db__port_pp_tpid_profile_ingress";
    layout_array_algo_port_pp[idx].type = "dnx_algo_template_t";
    layout_array_algo_port_pp[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].size_of = sizeof(dnx_algo_template_t);
    layout_array_algo_port_pp[idx].parent  = 0;
    layout_array_algo_port_pp[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].print_cb = &dnx_algo_port_tpid_print_ingress_cb;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__IPVX_O_MPLS_PARSING_ENABLE_PROFILE);
    layout_array_algo_port_pp[idx].name = "algo_port_pp_db__ipvx_o_mpls_parsing_enable_profile";
    layout_array_algo_port_pp[idx].type = "dnx_algo_template_t";
    layout_array_algo_port_pp[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].size_of = sizeof(dnx_algo_template_t);
    layout_array_algo_port_pp[idx].parent  = 0;
    layout_array_algo_port_pp[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].print_cb = &dnx_algo_port_ipvx_o_mpls_parsing_print_cb;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__PORT_PP_TPID_PROFILE_EGRESS);
    layout_array_algo_port_pp[idx].name = "algo_port_pp_db__port_pp_tpid_profile_egress";
    layout_array_algo_port_pp[idx].type = "dnx_algo_template_t";
    layout_array_algo_port_pp[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].size_of = sizeof(dnx_algo_template_t);
    layout_array_algo_port_pp[idx].parent  = 0;
    layout_array_algo_port_pp[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].print_cb = &dnx_algo_port_tpid_print_egress_cb;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__EGRESS_ACCEPTABLE_FRAME_TYPE_PROFILE);
    layout_array_algo_port_pp[idx].name = "algo_port_pp_db__egress_acceptable_frame_type_profile";
    layout_array_algo_port_pp[idx].type = "dnx_algo_template_t";
    layout_array_algo_port_pp[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].size_of = sizeof(dnx_algo_template_t);
    layout_array_algo_port_pp[idx].parent  = 0;
    layout_array_algo_port_pp[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].print_cb = &dnx_algo_egress_acceptable_frame_type_profile_template_print_cb;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__EGRESS_PP_PORT_SIT_PROFILE);
    layout_array_algo_port_pp[idx].name = "algo_port_pp_db__egress_pp_port_sit_profile";
    layout_array_algo_port_pp[idx].type = "dnx_algo_template_t";
    layout_array_algo_port_pp[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].size_of = sizeof(dnx_algo_template_t);
    layout_array_algo_port_pp[idx].parent  = 0;
    layout_array_algo_port_pp[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].print_cb = &dnx_algo_egress_sit_profile_template_print_cb;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__PP_PORT_LB_PROFILE);
    layout_array_algo_port_pp[idx].name = "algo_port_pp_db__pp_port_lb_profile";
    layout_array_algo_port_pp[idx].type = "dnx_algo_template_t";
    layout_array_algo_port_pp[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].size_of = sizeof(dnx_algo_template_t);
    layout_array_algo_port_pp[idx].parent  = 0;
    layout_array_algo_port_pp[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].print_cb = &dnx_algo_pp_port_lb_profile_print_entry_cb;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__FORCE_FORWARD);
    layout_array_algo_port_pp[idx].name = "algo_port_pp_db__force_forward";
    layout_array_algo_port_pp[idx].type = "dnx_algo_port_db_force_forward_t";
    layout_array_algo_port_pp[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].size_of = sizeof(dnx_algo_port_db_force_forward_t);
    layout_array_algo_port_pp[idx].parent  = 0;
    layout_array_algo_port_pp[idx].first_child_index = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__FORCE_FORWARD__FIRST);
    layout_array_algo_port_pp[idx].last_child_index = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__FORCE_FORWARD__LAST)-1;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__ESEM);
    layout_array_algo_port_pp[idx].name = "algo_port_pp_db__esem";
    layout_array_algo_port_pp[idx].type = "algo_port_esem_t";
    layout_array_algo_port_pp[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].size_of = sizeof(algo_port_esem_t);
    layout_array_algo_port_pp[idx].parent  = 0;
    layout_array_algo_port_pp[idx].first_child_index = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__ESEM__FIRST);
    layout_array_algo_port_pp[idx].last_child_index = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__ESEM__LAST)-1;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__RECYCLE_APP);
    layout_array_algo_port_pp[idx].name = "algo_port_pp_db__recycle_app";
    layout_array_algo_port_pp[idx].type = "dnx_algo_recycle_app_info_t";
    layout_array_algo_port_pp[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].size_of = sizeof(dnx_algo_recycle_app_info_t);
    layout_array_algo_port_pp[idx].array_indexes[0].num_elements = DNX_DATA_MAX_DEVICE_GENERAL_NOF_CORES;
    layout_array_algo_port_pp[idx].array_indexes[0].index_type = DNXC_SWSTATE_ARRAY_INDEX_STATIC;
    layout_array_algo_port_pp[idx].array_indexes[1].num_elements = dnx_data_port.general.nof_pp_ports_get(unit);
    layout_array_algo_port_pp[idx].array_indexes[1].index_type = DNXC_SWSTATE_ARRAY_INDEX_DYNAMIC_DNX_DATA;
    layout_array_algo_port_pp[idx].parent  = 0;
    layout_array_algo_port_pp[idx].first_child_index = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__RECYCLE_APP__FIRST);
    layout_array_algo_port_pp[idx].last_child_index = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__RECYCLE_APP__LAST)-1;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__FORCE_FORWARD__MNGR);
    layout_array_algo_port_pp[idx].name = "algo_port_pp_db__force_forward__mngr";
    layout_array_algo_port_pp[idx].type = "dnx_algo_template_t";
    layout_array_algo_port_pp[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].size_of = sizeof(dnx_algo_template_t);
    layout_array_algo_port_pp[idx].array_indexes[0].num_elements = dnx_data_device.general.nof_cores_get(unit);
    layout_array_algo_port_pp[idx].array_indexes[0].index_type = DNXC_SWSTATE_ARRAY_INDEX_DYNAMIC_DNX_DATA;
    layout_array_algo_port_pp[idx].parent  = 8;
    layout_array_algo_port_pp[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].print_cb = &dnx_algo_port_pp_force_forward_template_cb;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__FORCE_FORWARD__TRAP_ID);
    layout_array_algo_port_pp[idx].name = "algo_port_pp_db__force_forward__trap_id";
    layout_array_algo_port_pp[idx].type = "uint32";
    layout_array_algo_port_pp[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].size_of = sizeof(uint32);
    layout_array_algo_port_pp[idx].array_indexes[0].num_elements = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].array_indexes[0].index_type = DNXC_SWSTATE_ARRAY_INDEX_DYNAMIC;
    layout_array_algo_port_pp[idx].array_indexes[1].num_elements = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].array_indexes[1].index_type = DNXC_SWSTATE_ARRAY_INDEX_DYNAMIC;
    layout_array_algo_port_pp[idx].parent  = 8;
    layout_array_algo_port_pp[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__ESEM__ACCESS_CMD);
    layout_array_algo_port_pp[idx].name = "algo_port_pp_db__esem__access_cmd";
    layout_array_algo_port_pp[idx].type = "dnx_algo_template_t";
    layout_array_algo_port_pp[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].size_of = sizeof(dnx_algo_template_t);
    layout_array_algo_port_pp[idx].parent  = 9;
    layout_array_algo_port_pp[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].print_cb = &dnx_algo_port_esem_access_cmd_template_print_cb;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__ESEM__PREDEFINE_ESEM_CMDS);
    layout_array_algo_port_pp[idx].name = "algo_port_pp_db__esem__predefine_esem_cmds";
    layout_array_algo_port_pp[idx].type = "uint8";
    layout_array_algo_port_pp[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].size_of = sizeof(uint8);
    layout_array_algo_port_pp[idx].array_indexes[0].num_elements = DNX_DATA_MAX_ESEM_ACCESS_CMD_NOF_CMDS;
    layout_array_algo_port_pp[idx].array_indexes[0].index_type = DNXC_SWSTATE_ARRAY_INDEX_STATIC;
    layout_array_algo_port_pp[idx].parent  = 9;
    layout_array_algo_port_pp[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_PORT_PP_DB__RECYCLE_APP__TYPE);
    layout_array_algo_port_pp[idx].name = "algo_port_pp_db__recycle_app__type";
    layout_array_algo_port_pp[idx].type = "uint32";
    layout_array_algo_port_pp[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].size_of = sizeof(uint32);
    layout_array_algo_port_pp[idx].parent  = 10;
    layout_array_algo_port_pp[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_port_pp[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;


    dnxc_sw_state_layout_init_structure(unit, DNX_SW_STATE_ALGO_PORT_PP_DB, layout_array_algo_port_pp, sw_state_layout_array[unit][ALGO_PORT_PP_MODULE_ID], DNX_SW_STATE_ALGO_PORT_PP_DB_NOF_PARAMS);

    DNXC_SW_STATE_FUNC_RETURN;
}

#undef BSL_LOG_MODULE

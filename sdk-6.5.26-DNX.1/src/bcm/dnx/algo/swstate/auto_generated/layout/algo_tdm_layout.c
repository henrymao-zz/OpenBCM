/** \file algo/swstate/auto_generated/layout/algo_tdm_layout.c
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

#include <bcm_int/dnx/algo/swstate/auto_generated/types/algo_tdm_types.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/layout/algo_tdm_layout.h>

dnxc_sw_state_layout_t layout_array_algo_tdm[DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_TDM_DB_NOF_PARAMS)];

shr_error_e
algo_tdm_init_layout_structure(int unit)
{

    int idx;

    DNXC_SW_STATE_INIT_FUNC_DEFS;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_TDM_DB);
    layout_array_algo_tdm[idx].name = "algo_tdm_db";
    layout_array_algo_tdm[idx].type = "algo_tdm_sw_state_t";
    layout_array_algo_tdm[idx].doc = "TDM related sw state";
    layout_array_algo_tdm[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_tdm[idx].size_of = sizeof(algo_tdm_sw_state_t);
    layout_array_algo_tdm[idx].parent  = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_tdm[idx].first_child_index = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_TDM_DB__FIRST);
    layout_array_algo_tdm[idx].last_child_index = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_TDM_DB__LAST)-1;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_TDM_DB__INGRESS_CONTEXT);
    layout_array_algo_tdm[idx].name = "algo_tdm_db__ingress_context";
    layout_array_algo_tdm[idx].type = "dnx_algo_res_t";
    layout_array_algo_tdm[idx].doc = "TDM Ingress Context ID";
    layout_array_algo_tdm[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_tdm[idx].size_of = sizeof(dnx_algo_res_t);
    layout_array_algo_tdm[idx].parent  = 0;
    layout_array_algo_tdm[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_tdm[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_ALGO_TDM_DB__LINK_MASK);
    layout_array_algo_tdm[idx].name = "algo_tdm_db__link_mask";
    layout_array_algo_tdm[idx].type = "dnx_algo_template_t";
    layout_array_algo_tdm[idx].doc = "TDM Link Mask for direct routing";
    layout_array_algo_tdm[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_tdm[idx].size_of = sizeof(dnx_algo_template_t);
    layout_array_algo_tdm[idx].parent  = 0;
    layout_array_algo_tdm[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_algo_tdm[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;


    dnxc_sw_state_layout_init_structure(unit, DNX_SW_STATE_ALGO_TDM_DB, layout_array_algo_tdm, sw_state_layout_array[unit][ALGO_TDM_MODULE_ID], DNX_SW_STATE_ALGO_TDM_DB_NOF_PARAMS);

    DNXC_SW_STATE_FUNC_RETURN;
}

#undef BSL_LOG_MODULE

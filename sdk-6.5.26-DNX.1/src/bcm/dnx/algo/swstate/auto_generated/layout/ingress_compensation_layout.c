/** \file algo/swstate/auto_generated/layout/ingress_compensation_layout.c
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

#include <bcm_int/dnx/algo/swstate/auto_generated/types/ingress_compensation_types.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/layout/ingress_compensation_layout.h>

dnxc_sw_state_layout_t layout_array_ingress_compensation[DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_DNX_INGRESS_COMPENSATION_DB_NOF_PARAMS)];

shr_error_e
ingress_compensation_init_layout_structure(int unit)
{

    int idx;

    DNXC_SW_STATE_INIT_FUNC_DEFS;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_DNX_INGRESS_COMPENSATION_DB);
    layout_array_ingress_compensation[idx].name = "dnx_ingress_compensation_db";
    layout_array_ingress_compensation[idx].type = "dnx_ingress_compensation_db_t";
    layout_array_ingress_compensation[idx].doc = "DB for ingress compensation";
    layout_array_ingress_compensation[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_ingress_compensation[idx].size_of = sizeof(dnx_ingress_compensation_db_t);
    layout_array_ingress_compensation[idx].parent  = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_ingress_compensation[idx].first_child_index = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_DNX_INGRESS_COMPENSATION_DB__FIRST);
    layout_array_ingress_compensation[idx].last_child_index = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_DNX_INGRESS_COMPENSATION_DB__LAST)-1;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_DNX_INGRESS_COMPENSATION_DB__COMPENSATION);
    layout_array_ingress_compensation[idx].name = "dnx_ingress_compensation_db__compensation";
    layout_array_ingress_compensation[idx].type = "dnx_algo_template_t*";
    layout_array_ingress_compensation[idx].doc = "VOQ compensation template manager";
    layout_array_ingress_compensation[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_ingress_compensation[idx].size_of = sizeof(dnx_algo_template_t*);
    layout_array_ingress_compensation[idx].array_indexes[0].num_elements = dnx_data_device.general.nof_cores_get(unit);
    layout_array_ingress_compensation[idx].array_indexes[0].index_type = DNXC_SWSTATE_ARRAY_INDEX_DYNAMIC_DNX_DATA;
    layout_array_ingress_compensation[idx].parent  = 0;
    layout_array_ingress_compensation[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_ingress_compensation[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;


    dnxc_sw_state_layout_init_structure(unit, DNX_SW_STATE_DNX_INGRESS_COMPENSATION_DB, layout_array_ingress_compensation, sw_state_layout_array[unit][INGRESS_COMPENSATION_MODULE_ID], DNX_SW_STATE_DNX_INGRESS_COMPENSATION_DB_NOF_PARAMS);

    DNXC_SW_STATE_FUNC_RETURN;
}

#undef BSL_LOG_MODULE

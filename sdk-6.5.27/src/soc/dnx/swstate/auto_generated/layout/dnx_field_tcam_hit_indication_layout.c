
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_SWSTATEDNX_GENERAL

#include <soc/dnx/swstate/auto_generated/types/dnx_field_tcam_hit_indication_types.h>
#include <soc/dnx/swstate/auto_generated/layout/dnx_field_tcam_hit_indication_layout.h>

dnxc_sw_state_layout_t layout_array_dnx_field_tcam_hit_indication[DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_DNX_FIELD_TCAM_HIT_INDICATION_NOF_PARAMS)];

shr_error_e
dnx_field_tcam_hit_indication_init_layout_structure(int unit)
{

    int idx;

    DNXC_SW_STATE_INIT_FUNC_DEFS;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_DNX_FIELD_TCAM_HIT_INDICATION);
    layout_array_dnx_field_tcam_hit_indication[idx].name = "dnx_field_tcam_hit_indication";
    layout_array_dnx_field_tcam_hit_indication[idx].type = "dnx_field_tcam_hit_indication_t";
    layout_array_dnx_field_tcam_hit_indication[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_dnx_field_tcam_hit_indication[idx].size_of = sizeof(dnx_field_tcam_hit_indication_t);
    layout_array_dnx_field_tcam_hit_indication[idx].parent  = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_dnx_field_tcam_hit_indication[idx].first_child_index = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_DNX_FIELD_TCAM_HIT_INDICATION__FIRST);
    layout_array_dnx_field_tcam_hit_indication[idx].last_child_index = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_DNX_FIELD_TCAM_HIT_INDICATION__LAST)-1;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_DNX_FIELD_TCAM_HIT_INDICATION__TCAM_ACTION_HIT_INDICATION);
    layout_array_dnx_field_tcam_hit_indication[idx].name = "dnx_field_tcam_hit_indication__tcam_action_hit_indication";
    layout_array_dnx_field_tcam_hit_indication[idx].type = "dnx_field_tcam_hit_indication_hitbit_unit_info_t";
    layout_array_dnx_field_tcam_hit_indication[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_dnx_field_tcam_hit_indication[idx].size_of = sizeof(dnx_field_tcam_hit_indication_hitbit_unit_info_t);
    layout_array_dnx_field_tcam_hit_indication[idx].array_indexes[0].num_elements = dnx_data_device.general.nof_cores_get(unit);
    layout_array_dnx_field_tcam_hit_indication[idx].array_indexes[0].index_type = DNXC_SWSTATE_ARRAY_INDEX_DYNAMIC_DNX_DATA;
    layout_array_dnx_field_tcam_hit_indication[idx].array_indexes[1].num_elements = dnx_data_field.tcam.nof_banks_hitbit_units_get(unit);
    layout_array_dnx_field_tcam_hit_indication[idx].array_indexes[1].index_type = DNXC_SWSTATE_ARRAY_INDEX_DYNAMIC_DNX_DATA;
    layout_array_dnx_field_tcam_hit_indication[idx].parent  = 0;
    layout_array_dnx_field_tcam_hit_indication[idx].first_child_index = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_DNX_FIELD_TCAM_HIT_INDICATION__TCAM_ACTION_HIT_INDICATION__FIRST);
    layout_array_dnx_field_tcam_hit_indication[idx].last_child_index = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_DNX_FIELD_TCAM_HIT_INDICATION__TCAM_ACTION_HIT_INDICATION__LAST)-1;

    idx = DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX(DNX_SW_STATE_DNX_FIELD_TCAM_HIT_INDICATION__TCAM_ACTION_HIT_INDICATION__BMP);
    layout_array_dnx_field_tcam_hit_indication[idx].name = "dnx_field_tcam_hit_indication__tcam_action_hit_indication__bmp";
    layout_array_dnx_field_tcam_hit_indication[idx].type = "SHR_BITDCL";
    layout_array_dnx_field_tcam_hit_indication[idx].sum_of_allocation = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_dnx_field_tcam_hit_indication[idx].size_of = sizeof(SHR_BITDCL);
    layout_array_dnx_field_tcam_hit_indication[idx].array_indexes[0].num_elements = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_dnx_field_tcam_hit_indication[idx].array_indexes[0].index_type = DNXC_SWSTATE_ARRAY_INDEX_DYNAMIC_BITMAP;
    layout_array_dnx_field_tcam_hit_indication[idx].parent  = 1;
    layout_array_dnx_field_tcam_hit_indication[idx].first_child_index = DNXC_SW_STATE_LAYOUT_INVALID;
    layout_array_dnx_field_tcam_hit_indication[idx].last_child_index = DNXC_SW_STATE_LAYOUT_INVALID;


    dnxc_sw_state_layout_init_structure(unit, DNX_SW_STATE_DNX_FIELD_TCAM_HIT_INDICATION, layout_array_dnx_field_tcam_hit_indication, sw_state_layout_array[unit][DNX_FIELD_TCAM_HIT_INDICATION_MODULE_ID], DNX_SW_STATE_DNX_FIELD_TCAM_HIT_INDICATION_NOF_PARAMS);

    DNXC_SW_STATE_FUNC_RETURN;
}

#undef BSL_LOG_MODULE

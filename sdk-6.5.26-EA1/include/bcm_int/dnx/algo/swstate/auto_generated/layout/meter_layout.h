/** \file algo/swstate/auto_generated/layout/meter_layout.h
 *
 * sw state layout enum
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

#ifndef __METER_LAYOUT_H__
#define __METER_LAYOUT_H__

#include <include/soc/dnxc/swstate/types/dnxc_sw_state_layout.h>
#include <include/soc/dnxc/swstate/auto_generated/types/dnxc_module_ids_types.h>


int meter_init_layout_structure(int unit);

typedef enum
{
    DNX_SW_STATE_DNX_METER_DB = DNXC_SW_STATE_LAYOUT_NODE_ID_GET(METER_MODULE_ID, 0),
    DNX_SW_STATE_DNX_METER_DB__PROFILE_LIMITS_INFO,
    DNX_SW_STATE_DNX_METER_DB__GLOBAL_METER_ENABLED,
    DNX_SW_STATE_DNX_METER_DB__GENERIC_METER_INFO,
    DNX_SW_STATE_DNX_METER_DB__POLICER_TEMPLATES,
    DNX_SW_STATE_DNX_METER_DB__PROFILE_LIMITS_INFO__MAX_RATE,
    DNX_SW_STATE_DNX_METER_DB__PROFILE_LIMITS_INFO__MAX_BURST_NORMAL_MODE,
    DNX_SW_STATE_DNX_METER_DB__PROFILE_LIMITS_INFO__MAX_BURST_LARGE_MODE,
    DNX_SW_STATE_DNX_METER_DB__PROFILE_LIMITS_INFO__MIN_RATE,
    DNX_SW_STATE_DNX_METER_DB__PROFILE_LIMITS_INFO__MIN_BURST,
    DNX_SW_STATE_DNX_METER_DB__PROFILE_LIMITS_INFO__MAX_CBS_MANT,
    DNX_SW_STATE_DNX_METER_DB__PROFILE_LIMITS_INFO__MAX_CBS_EXP,
    DNX_SW_STATE_DNX_METER_DB__PROFILE_LIMITS_INFO__MAX_IR_MANT,
    DNX_SW_STATE_DNX_METER_DB__PROFILE_LIMITS_INFO__MAX_IR_EXP,
    DNX_SW_STATE_DNX_METER_DB__GENERIC_METER_INFO__DB_INFO,
    DNX_SW_STATE_DNX_METER_DB__GENERIC_METER_INFO__DB_INFO__ENABLE,
    DNX_SW_STATE_DNX_METER_DB__GENERIC_METER_INFO__DB_INFO__CREATED,
    DNX_SW_STATE_DNX_METER_DB__GENERIC_METER_INFO__DB_INFO__EXPANSION_ENABLE,
    DNX_SW_STATE_DNX_METER_DB__GENERIC_METER_INFO__DB_INFO__EXPANSION_IS_PER_TC,
    DNX_SW_STATE_DNX_METER_DB__GENERIC_METER_INFO__DB_INFO__IS_SINGLE_BUCKET,
    DNX_SW_STATE_DNX_METER_DB__GENERIC_METER_INFO__DB_INFO__USE_SINGLE_BUCKET_BANK,
    DNX_SW_STATE_DNX_METER_DB__GENERIC_METER_INFO__DB_INFO__NOF_GENERIC_BANKS,
    DNX_SW_STATE_DNX_METER_DB__GENERIC_METER_INFO__DB_INFO__BANKS_ARR,
    DNX_SW_STATE_DNX_METER_DB__GENERIC_METER_INFO__DB_INFO__BANKS_ARR__BANK_ID,
    DNX_SW_STATE_DNX_METER_DB__GENERIC_METER_INFO__DB_INFO__BANKS_ARR__BASE_METER_INDEX,
    DNX_SW_STATE_DNX_METER_DB__POLICER_TEMPLATES__POLICER_INGRESS_DB0,
    DNX_SW_STATE_DNX_METER_DB__POLICER_TEMPLATES__POLICER_INGRESS_DB1,
    DNX_SW_STATE_DNX_METER_DB__POLICER_TEMPLATES__POLICER_INGRESS_DB2,
    DNX_SW_STATE_DNX_METER_DB__POLICER_TEMPLATES__POLICER_EGRESS_DB0,
    DNX_SW_STATE_DNX_METER_DB__POLICER_TEMPLATES__POLICER_EGRESS_DB1,
    /*
     * Use DNXC_SW_STATE_LAYOUT_GET_PARAM_IDX macro to get the number of parameters
     */
    DNX_SW_STATE_DNX_METER_DB_NOF_PARAMS,
} dnxc_sw_state_layout_meter_node_id_e;

#endif /* __METER_LAYOUT_H__ */

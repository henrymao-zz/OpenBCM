
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifndef __DNX_ALGO_LANE_MAP_LAYOUT_H__
#define __DNX_ALGO_LANE_MAP_LAYOUT_H__

#include <include/soc/dnxc/swstate/types/dnxc_sw_state_layout.h>
#include <include/soc/dnxc/swstate/auto_generated/types/dnxc_module_ids_types.h>


int dnx_algo_lane_map_init_layout_structure(int unit);

typedef enum
{
    DNX_SW_STATE_DNX_ALGO_LANE_MAP_DB = DNXC_SW_STATE_LAYOUT_NODE_ID_GET(DNX_ALGO_LANE_MAP_MODULE_ID, 0),
    DNX_SW_STATE_DNX_ALGO_LANE_MAP_DB__LANE_MAP,
    DNX_SW_STATE_DNX_ALGO_LANE_MAP_DB__OTN,
    DNX_SW_STATE_DNX_ALGO_LANE_MAP_DB__LANE_MAP__MAP_SIZE,
    DNX_SW_STATE_DNX_ALGO_LANE_MAP_DB__LANE_MAP__LANE2SERDES,
    DNX_SW_STATE_DNX_ALGO_LANE_MAP_DB__LANE_MAP__SERDES2LANE,
    DNX_SW_STATE_DNX_ALGO_LANE_MAP_DB__LANE_MAP__LANE2SERDES__RX_ID,
    DNX_SW_STATE_DNX_ALGO_LANE_MAP_DB__LANE_MAP__LANE2SERDES__TX_ID,
    DNX_SW_STATE_DNX_ALGO_LANE_MAP_DB__LANE_MAP__SERDES2LANE__RX_ID,
    DNX_SW_STATE_DNX_ALGO_LANE_MAP_DB__LANE_MAP__SERDES2LANE__TX_ID,
    DNX_SW_STATE_DNX_ALGO_LANE_MAP_DB__OTN__LOGICAL_LANES,
    DNX_SW_STATE_DNX_ALGO_LANE_MAP_DB__OTN__LOGICAL_LANE_MAP,
    DNX_SW_STATE_DNX_ALGO_LANE_MAP_DB__OTN__LOGICAL_LANE_MAP__LOGICAL_OTN_LANE,
    DNX_SW_STATE_DNX_ALGO_LANE_MAP_DB__OTN__LOGICAL_LANE_MAP__NOF_LANES,
    
    DNX_SW_STATE_DNX_ALGO_LANE_MAP_DB_NOF_PARAMS,
} dnxc_sw_state_layout_dnx_algo_lane_map_node_id_e;

#endif 

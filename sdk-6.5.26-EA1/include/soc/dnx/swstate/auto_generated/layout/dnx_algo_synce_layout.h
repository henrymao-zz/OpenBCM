
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifndef __DNX_ALGO_SYNCE_LAYOUT_H__
#define __DNX_ALGO_SYNCE_LAYOUT_H__

#include <include/soc/dnxc/swstate/types/dnxc_sw_state_layout.h>
#include <include/soc/dnxc/swstate/auto_generated/types/dnxc_module_ids_types.h>


int dnx_algo_synce_init_layout_structure(int unit);

typedef enum
{
    DNX_SW_STATE_DNX_ALGO_SYNCE_DB = DNXC_SW_STATE_LAYOUT_NODE_ID_GET(DNX_ALGO_SYNCE_MODULE_ID, 0),
    DNX_SW_STATE_DNX_ALGO_SYNCE_DB__FABRIC_SYNCE_STATUS,
    DNX_SW_STATE_DNX_ALGO_SYNCE_DB__FABRIC_SYNCE_STATUS__MASTER_SYNCE_ENABLED,
    DNX_SW_STATE_DNX_ALGO_SYNCE_DB__FABRIC_SYNCE_STATUS__SLAVE_SYNCE_ENABLED,
    DNX_SW_STATE_DNX_ALGO_SYNCE_DB__FABRIC_SYNCE_STATUS__MASTER_SET1_SYNCE_ENABLED,
    DNX_SW_STATE_DNX_ALGO_SYNCE_DB__FABRIC_SYNCE_STATUS__SLAVE_SET1_SYNCE_ENABLED,
    
    DNX_SW_STATE_DNX_ALGO_SYNCE_DB_NOF_PARAMS,
} dnxc_sw_state_layout_dnx_algo_synce_node_id_e;

#endif 


/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifndef __DNX_ECGM_LAYOUT_H__
#define __DNX_ECGM_LAYOUT_H__

#include <include/soc/dnxc/swstate/types/dnxc_sw_state_layout.h>
#include <include/soc/dnxc/swstate/auto_generated/types/dnxc_module_ids_types.h>


int dnx_ecgm_init_layout_structure(int unit);

typedef enum
{
    DNX_SW_STATE_DNX_ECGM_DB = DNXC_SW_STATE_LAYOUT_NODE_ID_GET(DNX_ECGM_MODULE_ID, 0),
    DNX_SW_STATE_DNX_ECGM_DB__PORT_INFO,
    DNX_SW_STATE_DNX_ECGM_DB__INTERFACE_CACHING,
    DNX_SW_STATE_DNX_ECGM_DB__PORT_CACHING,
    DNX_SW_STATE_DNX_ECGM_DB__INTERFACE_CACHING__PORT,
    DNX_SW_STATE_DNX_ECGM_DB__INTERFACE_CACHING__INFO,
    DNX_SW_STATE_DNX_ECGM_DB__INTERFACE_CACHING__PROFILE_ID,
    DNX_SW_STATE_DNX_ECGM_DB__INTERFACE_CACHING__VALID,
    DNX_SW_STATE_DNX_ECGM_DB__PORT_CACHING__PORT,
    DNX_SW_STATE_DNX_ECGM_DB__PORT_CACHING__INFO,
    DNX_SW_STATE_DNX_ECGM_DB__PORT_CACHING__PROFILE_ID,
    DNX_SW_STATE_DNX_ECGM_DB__PORT_CACHING__VALID,
    
    DNX_SW_STATE_DNX_ECGM_DB_NOF_PARAMS,
} dnxc_sw_state_layout_dnx_ecgm_node_id_e;

#endif 

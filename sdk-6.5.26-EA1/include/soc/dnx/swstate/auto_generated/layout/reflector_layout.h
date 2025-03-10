
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifndef __REFLECTOR_LAYOUT_H__
#define __REFLECTOR_LAYOUT_H__

#include <include/soc/dnxc/swstate/types/dnxc_sw_state_layout.h>
#include <include/soc/dnxc/swstate/auto_generated/types/dnxc_module_ids_types.h>


int reflector_init_layout_structure(int unit);

typedef enum
{
    DNX_SW_STATE_REFLECTOR_SW_DB_INFO = DNXC_SW_STATE_LAYOUT_NODE_ID_GET(REFLECTOR_MODULE_ID, 0),
    DNX_SW_STATE_REFLECTOR_SW_DB_INFO__UC,
    DNX_SW_STATE_REFLECTOR_SW_DB_INFO__UC_L2_INT,
    DNX_SW_STATE_REFLECTOR_SW_DB_INFO__UC_L2_INT_ONEPASS,
    DNX_SW_STATE_REFLECTOR_SW_DB_INFO__SBFD_REFLECTOR_CNT,
    DNX_SW_STATE_REFLECTOR_SW_DB_INFO__UC__ENCAP_ID,
    DNX_SW_STATE_REFLECTOR_SW_DB_INFO__UC__IS_ALLOCATED,
    DNX_SW_STATE_REFLECTOR_SW_DB_INFO__UC_L2_INT__ENCAP_ID,
    DNX_SW_STATE_REFLECTOR_SW_DB_INFO__UC_L2_INT__IS_ALLOCATED,
    DNX_SW_STATE_REFLECTOR_SW_DB_INFO__UC_L2_INT_ONEPASS__ENCAP_ID,
    DNX_SW_STATE_REFLECTOR_SW_DB_INFO__UC_L2_INT_ONEPASS__IS_ALLOCATED,
    
    DNX_SW_STATE_REFLECTOR_SW_DB_INFO_NOF_PARAMS,
} dnxc_sw_state_layout_reflector_node_id_e;

#endif 


/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifndef __DNX_IPQ_LAYOUT_H__
#define __DNX_IPQ_LAYOUT_H__

#include <include/soc/dnxc/swstate/types/dnxc_sw_state_layout.h>
#include <include/soc/dnxc/swstate/auto_generated/types/dnxc_module_ids_types.h>


int dnx_ipq_init_layout_structure(int unit);

typedef enum
{
    DNX_SW_STATE_DNX_IPQ_DB = DNXC_SW_STATE_LAYOUT_NODE_ID_GET(DNX_IPQ_MODULE_ID, 0),
    DNX_SW_STATE_DNX_IPQ_DB__BASE_QUEUES,
    DNX_SW_STATE_DNX_IPQ_DB__BASE_QUEUE_IS_ASYMM,
    DNX_SW_STATE_DNX_IPQ_DB__BASE_QUEUES__NUM_COS,
    DNX_SW_STATE_DNX_IPQ_DB__BASE_QUEUES__SYS_PORT_REF_COUNTER,
    
    DNX_SW_STATE_DNX_IPQ_DB_NOF_PARAMS,
} dnxc_sw_state_layout_dnx_ipq_node_id_e;

#endif 

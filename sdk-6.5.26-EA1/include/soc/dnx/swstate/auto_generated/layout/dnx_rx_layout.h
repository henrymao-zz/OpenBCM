
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifndef __DNX_RX_LAYOUT_H__
#define __DNX_RX_LAYOUT_H__

#include <include/soc/dnxc/swstate/types/dnxc_sw_state_layout.h>
#include <include/soc/dnxc/swstate/auto_generated/types/dnxc_module_ids_types.h>


int dnx_rx_init_layout_structure(int unit);

typedef enum
{
    DNX_SW_STATE_DNX_RX_PARSER_INFO = DNXC_SW_STATE_LAYOUT_NODE_ID_GET(DNX_RX_MODULE_ID, 0),
    DNX_SW_STATE_DNX_RX_PARSER_INFO__FTMH_LB_KEY_SIZE,
    DNX_SW_STATE_DNX_RX_PARSER_INFO__FTMH_STACKING_EXT_SIZE,
    DNX_SW_STATE_DNX_RX_PARSER_INFO__USER_HEADER_ENABLE,
    DNX_SW_STATE_DNX_RX_PARSER_INFO__PPH_BASE_SIZE,
    DNX_SW_STATE_DNX_RX_PARSER_INFO__OUT_LIF_X_1_EXT_SIZE,
    DNX_SW_STATE_DNX_RX_PARSER_INFO__OUT_LIF_X_2_EXT_SIZE,
    DNX_SW_STATE_DNX_RX_PARSER_INFO__OUT_LIF_X_3_EXT_SIZE,
    DNX_SW_STATE_DNX_RX_PARSER_INFO__IN_LIF_EXT_SIZE,
    DNX_SW_STATE_DNX_RX_PARSER_INFO__OAMP_SYSTEM_PORT_0,
    DNX_SW_STATE_DNX_RX_PARSER_INFO__OAMP_SYSTEM_PORT_1,
    DNX_SW_STATE_DNX_RX_PARSER_INFO__DMA_CHANNEL_TO_CPU_PORT,
    DNX_SW_STATE_DNX_RX_PARSER_INFO__CPU_PORT_TO_DMA_CHANNEL,
    DNX_SW_STATE_DNX_RX_PARSER_INFO__FTMH_PP_DSP_TO_CPU_PORT,
    DNX_SW_STATE_DNX_RX_PARSER_INFO__ETPP_OAM_UP_MEP_DEST_TRAP_ID1,
    DNX_SW_STATE_DNX_RX_PARSER_INFO__ETPP_OAM_UP_MEP_DEST_TRAP_ID2,
    
    DNX_SW_STATE_DNX_RX_PARSER_INFO_NOF_PARAMS,
} dnxc_sw_state_layout_dnx_rx_node_id_e;

#endif 

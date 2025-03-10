
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifndef __MDB_KAPS_LAYOUT_H__
#define __MDB_KAPS_LAYOUT_H__

#include <include/soc/dnxc/swstate/types/dnxc_sw_state_layout.h>
#include <include/soc/dnxc/swstate/auto_generated/types/dnxc_module_ids_types.h>


int mdb_kaps_init_layout_structure(int unit);

typedef enum
{
    DNX_SW_STATE_MDB_KAPS_DB = DNXC_SW_STATE_LAYOUT_NODE_ID_GET(MDB_KAPS_MODULE_ID, 0),
    DNX_SW_STATE_MDB_KAPS_DB__DB_INFO,
    DNX_SW_STATE_MDB_KAPS_DB__SEARCH_INSTRUCTION_INFO,
    DNX_SW_STATE_MDB_KAPS_DB__BIG_KAPS_LARGE_BB_MODE,
    DNX_SW_STATE_MDB_KAPS_DB__DB_INFO__DB_P,
    DNX_SW_STATE_MDB_KAPS_DB__DB_INFO__HB_DB_P,
    DNX_SW_STATE_MDB_KAPS_DB__DB_INFO__AD_DB_P_ARR,
    DNX_SW_STATE_MDB_KAPS_DB__DB_INFO__AD_DB_SIZE_ARR,
    DNX_SW_STATE_MDB_KAPS_DB__DB_INFO__IS_VALID,
    DNX_SW_STATE_MDB_KAPS_DB__SEARCH_INSTRUCTION_INFO__INST_P,
    
    DNX_SW_STATE_MDB_KAPS_DB_NOF_PARAMS,
} dnxc_sw_state_layout_mdb_kaps_node_id_e;

#endif 

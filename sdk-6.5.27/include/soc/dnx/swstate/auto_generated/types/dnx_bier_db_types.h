
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifndef __DNX_BIER_DB_TYPES_H__
#define __DNX_BIER_DB_TYPES_H__

#include <soc/dnxc/swstate/dnxc_sw_state_h_includes.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_max_multicast.h>


typedef struct {
    uint32 active[DNX_DATA_MAX_MULTICAST_PARAMS_NOF_MCDB_ENTRIES];
} bier_db_status_t;

typedef struct {
    int set_size[DNX_DATA_MAX_MULTICAST_PARAMS_NOF_MCDB_ENTRIES];
    bier_db_status_t ingress;
    bier_db_status_t egress;
} dnx_bier_db_t;


#endif 


/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifndef _DNX_DATA_STG_H_

#define _DNX_DATA_STG_H_

#include <sal/limits.h>
#include <soc/property.h>
#include <soc/sand/shrextend/shrextend_debug.h>
#include <shared/utilex/utilex_framework.h>
#include <soc/dnxc/dnxc_data/dnxc_data_utils.h>
#include <soc/dnxc/dnxc_data/dnxc_data_mgmt.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_max_stg.h>



#ifndef BCM_DNX_SUPPORT
#error "This file is for use by DNX (JR2) family only!"
#endif



shr_error_e dnx_data_if_stg_init(
    int unit);







typedef enum
{

    
    _dnx_data_stg_stg_feature_nof
} dnx_data_stg_stg_feature_e;



typedef int(
    *dnx_data_stg_stg_feature_get_f) (
    int unit,
    dnx_data_stg_stg_feature_e feature);


typedef uint32(
    *dnx_data_stg_stg_nof_topology_ids_get_f) (
    int unit);



typedef struct
{
    
    dnx_data_stg_stg_feature_get_f feature_get;
    
    dnx_data_stg_stg_nof_topology_ids_get_f nof_topology_ids_get;
} dnx_data_if_stg_stg_t;





typedef struct
{
    
    dnx_data_if_stg_stg_t stg;
} dnx_data_if_stg_t;




extern dnx_data_if_stg_t dnx_data_stg;


#endif 


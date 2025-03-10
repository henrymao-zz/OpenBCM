 

/*
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */



#include <assert.h>
#include <soc/drv.h>
#include <soc/dnxc/dnxc_ha.h>
#include <soc/dnxc/drv_dnxc_utils.h>
#include <soc/dnxc/swstate/sw_state_defs.h>
#include <soc/dnxc/swstate/dnxc_sw_state.h>
#include <soc/dnxc/swstate/dnxc_sw_state_plain.h>
#include <soc/dnxc/swstate/dnxc_sw_state_wb.h>
#include <soc/dnxc/swstate/dnxc_sw_state_verifications.h>
#include <soc/dnxc/swstate/dnx_sw_state_logging.h>
#include <soc/dnxc/swstate/sw_state_diagnostics.h>
#ifdef BCM_DNX_SUPPORT
#include <soc/dnx/dnx_data/auto_generated/dnx_data_dev_init.h>
#endif
#include <soc/sand/shrextend/shrextend_debug.h>
#include <soc/dnxc/swstate/auto_generated/access/wb_engine_access.h>
#include <soc/dnxc/swstate/auto_generated/access/sw_state_external_access.h>



#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif

#define BSL_LOG_MODULE BSL_LS_SWSTATEDNX_GENERAL







int dnxc_sw_state_diagnostic_is_on[SOC_MAX_NUM_DEVICES] = {0};


int dnxc_sw_state_diag_init(int unit) {

    DNXC_SW_STATE_INIT_FUNC_DEFS;

    
    if (soc_is(unit, DNXF_DEVICE))
    {
        dnxc_sw_state_diagnostic_is_on[unit] = 1;
    }
    else
    {
        dnxc_sw_state_diagnostic_is_on[unit] = 0;
    }

#ifdef BCM_DNX_SUPPORT
#ifdef DNX_SW_STATE_DIAGNOSTIC
    if (soc_is(unit, DNX_DEVICE) && dnx_data_dev_init.ha.feature_get(unit, dnx_data_dev_init_ha_sw_state_diagnostics)) {
        dnxc_sw_state_diagnostic_is_on[unit] = 1;
    }
#endif
#endif

    DNXC_SW_STATE_FUNC_RETURN;
}


int dnxc_sw_state_diag_is_on(int unit) {
    return dnxc_sw_state_diagnostic_is_on[unit];
}



int dnxc_sw_state_init(int unit, uint32 warmboot, uint32 sw_state_max_size)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    
    if (SOC_WARM_BOOT(unit) && !warmboot) {
        SHR_IF_ERR_EXIT_WITH_LOG(SOC_E_PARAM,
                                 "device is loading in Warm Boot although Warmboot is disabled by SoC property or compilation flag\n%s%s%s",
                                 EMPTY, EMPTY, EMPTY);
    }

    
#ifndef BCM_WARM_BOOT_SUPPORT
    if (warmboot) {
        SHR_IF_ERR_EXIT_WITH_LOG(SOC_E_PARAM,
                                 "driver compiled without BCM_WARM_BOOT_SUPPORT but trying to enable warmboot (by soc property warmboot_support)\n%s%s%s",
                                 EMPTY, EMPTY, EMPTY);
    }
#endif

    
    SHR_IF_ERR_EXIT(dnxc_ha_init(unit));

#ifdef DNX_SW_STATE_VERIFICATIONS
    
    SHR_IF_ERR_EXIT(dnxc_sw_state_verifications_init(unit));
#endif

    
#ifdef DNX_SW_STATE_LOGGING
    dnx_sw_state_log_init(unit);
#endif 

    
    SHR_IF_ERR_EXIT(dnxc_sw_state_diag_init(unit));


    
    SHR_IF_ERR_EXIT(dnxc_sw_state_init_plain(unit, 0));

    
#ifdef BCM_WARM_BOOT_SUPPORT
    if (warmboot) {
        SHR_IF_ERR_EXIT(dnxc_sw_state_init_wb(unit, 0, sw_state_max_size));
    }
#endif

    if (!SOC_WARM_BOOT(unit)) {
        
        SHR_IF_ERR_EXIT(sw_state_wb_engine.init(unit));
        
        SHR_IF_ERR_EXIT(sw_state_external.init(unit));
    }

    DNXC_SW_STATE_FUNC_RETURN;
}


int dnxc_sw_state_deinit(int unit)
{
    DNXC_SW_STATE_INIT_FUNC_DEFS;

    
#ifdef BCM_WARM_BOOT_SUPPORT
        SHR_IF_ERR_EXIT(dnxc_sw_state_deinit_wb(unit, 0));
#endif

    
    SHR_IF_ERR_EXIT(dnxc_sw_state_deinit_plain(unit, 0));

    
    DNXC_SW_STATE_VERIFICATIONS_ONLY(dnxc_sw_state_verifications_deinit(unit));

#ifdef DNX_SW_STATE_LOGGING
    dnx_sw_state_log_deinit(unit);
#endif 

    
    SHR_IF_ERR_EXIT(dnxc_ha_deinit(unit));

    
#ifdef BCM_WARM_BOOT_SUPPORT
    SHR_IF_ERR_EXIT(soc_scache_detach(unit));
#endif

    DNXC_SW_STATE_FUNC_RETURN;
}

#undef _ERR_MSG_MODULE_NAME

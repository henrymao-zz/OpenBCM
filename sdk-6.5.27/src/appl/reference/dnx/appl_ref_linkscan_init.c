/** \file appl_ref_linkscan_init.c
 * 
 *
 * Linkscan application procedures for DNX.
 *
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_LINKSCANDNX

 /*
  * Include files.
  * {
  */
#include <shared/bsl.h>
#include <shared/bslenum.h>
#include <soc/sand/shrextend/shrextend_debug.h>
#include <sal/types.h>
#include <sal/core/libc.h>
#include <shared/shr_thread_manager.h>
#include <soc/defs.h>
#include <bcm/types.h>
#include <bcm/error.h>
#include <bcm/port.h>
#include <bcm/link.h>
#include <bcm_int/dnx/algo/port/algo_port_mgmt.h>
#include <bcm_int/dnx/link/link.h>
#include <soc/dnxc/drv_dnxc_utils.h>
#include <soc/sand/sand_aux_access.h>
#include <soc/dnxc/dnxc_wb_test_utils.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_nif.h>
/*
 * }
 */

/*
 * DEFINEs
 * {
 */
/*
 * }
 */

/*
 * MACROs
 * {
 */
/*
 * }
 */

 /*
  * Global and Static
  */
/*
 * }
 */

/**
 * \brief - Initialize linkscan, application stage
 *
 * \param [in] unit - unit ID
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
appl_dnx_linkscan_init(
    int unit)
{
    int rv = BCM_E_NONE;
    bcm_pbmp_t pbmp;
    bcm_pbmp_t flexe_phy_pbmp, otn_phy_pbmp;
    uint32 linkscan_interval = BCM_LINKSCAN_INTERVAL_DEFAULT;
    bcm_port_config_t pcfg;
    bcm_port_t port;
    uint32 flags;
    bcm_port_interface_info_t interface_info;
    bcm_port_mapping_info_t mapping_info;
    SHR_FUNC_INIT_VARS(unit);

    if (soc_sand_is_emulation_system(unit))
    {
        SHR_EXIT_WITH_LOG(_SHR_E_NONE, "Not initializing Linkscan application in emulation%s%s%s\n", EMPTY, EMPTY,
                          EMPTY);
    }

    /*
     * Turn linkscan on
     */
    rv = bcm_linkscan_enable_set(unit, linkscan_interval);
    SHR_IF_ERR_EXIT_WITH_LOG(rv, "bcm_linkscan_enable_set() Failed:\n%s%s%s", EMPTY, EMPTY, EMPTY);

    rv = bcm_port_config_get(unit, &pcfg);
    SHR_IF_ERR_EXIT_WITH_LOG(rv, "bcm ports not initialized\n%s%s%s", EMPTY, EMPTY, EMPTY);

    /*
     * Adding nif ports to linkscan, flexe_phy are default in sw mode
     * il are default in none mode, the other nif ports are default in
     * hw mode.
     */
    BCM_PBMP_ASSIGN(pbmp, pcfg.nif);
    BCM_PBMP_REMOVE(pbmp, pcfg.il);

    BCM_PBMP_CLEAR(flexe_phy_pbmp);
    BCM_PBMP_CLEAR(otn_phy_pbmp);

    if (!dnx_data_nif.global.feature_get(unit, dnx_data_nif_global_framer_phy_hw_linkscan_supported))
    {
        BCM_PBMP_ITER(pbmp, port)
        {
            rv = bcm_port_get(unit, port, &flags, &interface_info, &mapping_info);
            SHR_IF_ERR_EXIT_WITH_LOG(rv, "bcm_port_get() Failed:\n%s%s%s", EMPTY, EMPTY, EMPTY);
            if (flags & BCM_PORT_ADD_FLEXE_PHY)
            {
                BCM_PBMP_PORT_ADD(flexe_phy_pbmp, port);
            }
            if (interface_info.interface == BCM_PORT_IF_OTN)
            {
                BCM_PBMP_PORT_ADD(otn_phy_pbmp, port);
            }
        }
        BCM_PBMP_REMOVE(pbmp, flexe_phy_pbmp);
        BCM_PBMP_REMOVE(pbmp, otn_phy_pbmp);

        rv = bcm_linkscan_mode_set_pbm(unit, flexe_phy_pbmp, BCM_LINKSCAN_MODE_SW);
        rv |= bcm_linkscan_mode_set_pbm(unit, otn_phy_pbmp, BCM_LINKSCAN_MODE_SW);
    }

    rv |= bcm_linkscan_mode_set_pbm(unit, pbmp, BCM_LINKSCAN_MODE_HW);
    SHR_IF_ERR_EXIT_WITH_LOG(rv, "bcm_linkscan_mode_set_pbm() Failed:\n%s%s%s", EMPTY, EMPTY, EMPTY);

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Deinitialize linkscan, application stage
 *
 * \param [in] unit - unit ID
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
appl_dnx_linkscan_deinit(
    int unit)
{
    int rv = BCM_E_NONE;
    SHR_FUNC_INIT_VARS(unit);

    rv = bcm_linkscan_enable_set(unit, 0);

    SHR_IF_ERR_EXIT_WITH_LOG(rv, "bcm_linkscan_enable_set() Failed:\n%s%s%s", EMPTY, EMPTY, EMPTY);

exit:
    SHR_FUNC_EXIT;
}

/***********************************************************************************
 *                                                                                 *
 * Copyright: (c) 2021 Broadcom.                                                   *
 * Broadcom Proprietary and Confidential. All rights reserved.                     *
 *                                                                                 *
 ***********************************************************************************/

/**************************************************************************************
 **************************************************************************************
 *  File Name     :  osprey7_v2l8p1_pwr_mgt.c                                             *
 *  Created On    :  04 Nov 2015                                                      *
 *  Created By    :  Brent Roberts                                                    *
 *  Description   :  Power management APIs for Serdes IPs                             *
 *  Revision      :     *
 *                                                                                    *
 **************************************************************************************
 **************************************************************************************/

#include "osprey7_v2l8p1_pwr_mgt.h"
#include "osprey7_v2l8p1_common.h"
#include "osprey7_v2l8p1_functions.h"
#include "osprey7_v2l8p1_internal.h"
#include "osprey7_v2l8p1_internal_error.h"
#include "osprey7_v2l8p1_select_defns.h"
#include "osprey7_v2l8p1_config.h"

#ifndef SMALL_FOOTPRINT

/*! @file
 *
 */

/***************************/
/*  Configure Serdes IDDQ  */
/***************************/

err_code_t osprey7_v2l8p1_core_config_for_iddq(srds_access_t *sa__) {
    UNUSED(sa__);
    return (ERR_CODE_NONE);
}


err_code_t osprey7_v2l8p1_lane_config_for_iddq(srds_access_t *sa__) {
    INIT_SRDS_ERR_CODE

    /* Use frc/frc_val to force all RX and TX clk_vld signals to 0 */
    EFUN(wr_pmd_rx_clk_vld_frc_val(0x0));
    EFUN(wr_pmd_rx_clk_vld_frc(0x1));
    EFUN(wr_pmd_tx_clk_vld_frc_val(0x0));
    EFUN(wr_pmd_tx_clk_vld_frc(0x1));

    /* Use frc/frc_val to force all pmd_rx_lock signals to 0 */
    EFUN(wr_rx_dsc_lock_frc_val(0x0));
    EFUN(wr_rx_dsc_lock_frc(0x1));

    /* Switch all the lane clocks to comclk by writing to RX/TX comclk_sel registers */
    EFUN(wr_ln_rx_s_comclk_sel(0x1));
    EFUN(wr_ln_tx_s_comclk_sel(0x1));

    /* Assert all the AFE pwrdn/reset pins using frc/frc_val to make sure AFE is in lowest possible power mode */
    EFUN(wr_afe_tx_pwrdn_frc_val(0x1));
    EFUN(wr_afe_tx_pwrdn_frc(0x1));
    EFUN(wr_afe_rx_pwrdn_frc_val(0x1));
    EFUN(wr_afe_rx_pwrdn_frc(0x1));
    EFUN(wr_afe_tx_reset_frc_val(0x1));
    EFUN(wr_afe_tx_reset_frc(0x1));
    EFUN(wr_afe_rx_reset_frc_val(0x1));
    EFUN(wr_afe_rx_reset_frc(0x1));

    /* Set pmd_iddq pin to enable IDDQ */
    return (ERR_CODE_NONE);
}
/****************************************************/
/*  Serdes Powerdown, ClockGate and Deep_Powerdown  */
/****************************************************/

#endif /* !SMALL_FOOTPRINT */
#if !defined(SMALL_FOOTPRINT)
err_code_t osprey7_v2l8p1_core_pwrdn(srds_access_t *sa__, enum srds_core_pwrdn_mode_enum mode) {
    INIT_SRDS_ERR_CODE

    switch(mode) {
    case PWR_ON:
        EFUN(osprey7_v2l8p1_INTERNAL_core_clkgate(sa__, 0));
        EFUN(wrc_ams_pll_pwrdn(0x0));
        EFUN(wrc_afe_s_pll_pwrdn(0x0));
        EFUN(USR_DELAY_NS(500)); /* wait >50 comclk cycles  */
        break;
    case PWRDN:
        EFUN(osprey7_v2l8p1_core_dp_reset(sa__, 1));
        EFUN(USR_DELAY_NS(500)); /* wait >50 comclk cycles  */
        EFUN(wrc_afe_s_pll_pwrdn(0x1));
        EFUN(USR_DELAY_NS(500)); /* wait >50 comclk cycles  */
        EFUN(wrc_ams_pll_pwrdn(0x1));
        break;
    case PWROFF_DEEP: /* PWROFF_DEEP is identical to PWRDN_DEEP for core pwrdn. FALL THROUGH */
    case PWRDN_DEEP:
        EFUN(osprey7_v2l8p1_core_pwrdn(sa__, PWRDN));
        break;
    default:
        return(osprey7_v2l8p1_error(sa__, ERR_CODE_BAD_PTR_OR_INVALID_INPUT));
    }
    return ERR_CODE_NONE;
}
#endif /* !SMALL_FOOTPRINT || BLACKHAWK7 */
#ifndef SMALL_FOOTPRINT

err_code_t osprey7_v2l8p1_lane_pwrdn(srds_access_t *sa__, enum srds_core_pwrdn_mode_enum mode) {
    INIT_SRDS_ERR_CODE

    switch(mode) {
    case PWR_ON:
        EFUN(osprey7_v2l8p1_INTERNAL_lane_clkgate(sa__, 0));
        EFUN(osprey7_v2l8p1_lane_pwrdn(sa__, PWR_ON_RX));
        EFUN(osprey7_v2l8p1_lane_pwrdn(sa__, PWR_ON_TX));
        break;
    case PWR_ON_TX:
        EFUN(wr_ln_tx_s_pwrdn(0x0));
        break;
    case PWR_ON_RX:
        EFUN(wr_ln_rx_s_pwrdn(0x0));
        break;
    case PWRDN:
        EFUN(osprey7_v2l8p1_lane_pwrdn(sa__, PWRDN_TX));
        EFUN(osprey7_v2l8p1_lane_pwrdn(sa__, PWRDN_RX));
        break;
    case PWROFF_DEEP: /* PWROFF_DEEP is identical to PWRDN_DEEP for lane pwrdn. FALL THROUGH */
    case PWRDN_DEEP:
        EFUN(osprey7_v2l8p1_lane_pwrdn(sa__, PWRDN_TX_DEEP));
        EFUN(osprey7_v2l8p1_lane_pwrdn(sa__, PWRDN_RX_DEEP));
        EFUN(osprey7_v2l8p1_INTERNAL_lane_clkgate(sa__, 1));
        break;
    case PWRDN_TX:
        EFUN(wr_tx_ln_dp_s_rstb(0x0));
        EFUN(wr_ln_tx_s_pwrdn(0x1));
        break;
    case PWRDN_RX:
        EFUN(wr_rx_ln_dp_s_rstb(0x0));
        EFUN(wr_ln_rx_s_pwrdn(0x1));
        break;
    case PWRDN_TX_DEEP:
        EFUN(wr_tx_ln_dp_s_rstb(0x0));
        EFUN(wr_ln_tx_s_pwrdn(0x1));
        break;
    case PWRDN_RX_DEEP:
        EFUN(wr_rx_ln_dp_s_rstb(0x0));
        EFUN(wr_ln_rx_s_pwrdn(0x1));
        break;
    default:
        return(osprey7_v2l8p1_error(sa__, ERR_CODE_BAD_PTR_OR_INVALID_INPUT));
    }
  return (ERR_CODE_NONE);
}
err_code_t osprey7_v2l8p1_pwrdn_all(srds_access_t *sa__, enum srds_core_pwrdn_mode_enum mode) {
    INIT_SRDS_ERR_CODE
    uint8_t lane_orig = osprey7_v2l8p1_acc_get_lane(sa__);
    uint8_t lane;
    uint8_t lanes_per_core;

    if(mode != PWRDN_DEEP && mode != PWRDN && mode != PWROFF_DEEP) {
        return(osprey7_v2l8p1_error(sa__, ERR_CODE_BAD_PTR_OR_INVALID_INPUT));
    }

    ESTM(lanes_per_core = rdc_revid_multiplicity());
    for (lane = 0; lane < lanes_per_core; ++lane) {
        EFUN(osprey7_v2l8p1_acc_set_lane(sa__,   lane));
        EFUN(osprey7_v2l8p1_lane_pwrdn(sa__, mode));
    }
    EFUN(osprey7_v2l8p1_acc_set_lane(sa__, lane_orig));
    {
      uint8_t pll_orig = osprey7_v2l8p1_acc_get_pll_idx(sa__);
      uint8_t pll;
      for (pll = 0; pll < NUM_PLLS; ++pll) {
        EFUN(osprey7_v2l8p1_acc_set_pll_idx(sa__, pll));
        EFUN(osprey7_v2l8p1_core_pwrdn(sa__, mode));
      }
      EFUN(osprey7_v2l8p1_acc_set_pll_idx(sa__, pll_orig));
    }
    return ERR_CODE_NONE;
}

#endif /* !SMALL_FOOTPRINT */

/***********************************************************************************
 *                                                                                 *
 * Copyright: (c) 2021 Broadcom.                                                   *
 * Broadcom Proprietary and Confidential. All rights reserved.                     *
 *                                                                                 *
 ***********************************************************************************/

/***********************************************************************************
 ***********************************************************************************
 *                                                                                 *
 *  Revision    :    *
 *                                                                                 *
 *  Description :  Power management functions provided to IP User                  *
 *                                                                                 *
 ***********************************************************************************
 ***********************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OSPREY7_V2L8P1_API_PWR_MGT_H
#define OSPREY7_V2L8P1_API_PWR_MGT_H

#include "osprey7_v2l8p1_ipconfig.h"
#include "common/srds_api_enum.h"
#include "common/srds_api_err_code.h"
#include "osprey7_v2l8p1_dependencies.h"
/*! @file
 *  @brief Power management functions provided to IP User
 */

/*! @addtogroup APITag
 * @{
 */

/*! @defgroup SerdesAPIPwrMgtTag Power Management APIs
 * Serdes API functions for powering on and off the Serdes.
 * Contains APIs for both powering down core(s) and lane(s).
 */

/*! @addtogroup SerdesAPIPwrMgtTag
 * @{
 */

/** Serdes Core Powerdown.
 * To complete a osprey7_v2l8p1_core_pwrdn(), all of the lane(s) belonging to the core being powered down.
 * should also be issued a lane power down using osprey7_v2l8p1_lane_pwrdn().
 * Note: To wake up from any powerdown mode, first call PWR_ON and then de-assert core_dp_reset [osprey7_v2l8p1_core_dp_reset(sa__, 0)].
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] mode based on enum #srds_core_pwrdn_mode_enum select from PWR_ON, PWRDN, PWRDN_DEEP power down modes.
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_core_pwrdn(srds_access_t *sa__, enum srds_core_pwrdn_mode_enum mode);

#ifndef SMALL_FOOTPRINT

/*-----------------------*/
/*  IDDQ / Clkgate APIs  */
/*-----------------------*/
/** Core configuration for IDDQ.
 * Note: User also needs to configure all lanes through osprey7_v2l8p1_lane_config_for_iddq()
 * before enabling IDDQ by asserting IDDQ pin.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_core_config_for_iddq(srds_access_t *sa__);
/**************************************************/
/* LANE Based APIs - Required to be used per Lane */
/**************************************************/

/*--------------------------------------------------------------*/
/*  IDDQ / Powerdown / Deep Powerdown / Isolate Pins  */
/*--------------------------------------------------------------*/
/** Lane configurations for IDDQ.
 * Note: User needs to configure all lanes through osprey7_v2l8p1_lane_config_for_iddq() and also call osprey7_v2l8p1_core_config_for_iddq()
 * before enabling IDDQ by asserting IDDQ pin.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_lane_config_for_iddq(srds_access_t *sa__);

/** Serdes Lane Powerdown.
 * Powers down option available - TX only, RX only, TX only DEEP, RX only DEEP,
 * complete LANE, complete lane DEEP, complete lane DEEP OFF, PWR_ON, PWR_ON TX only, PWR_ON RX only.
 * Note: To wake up from any lane powerdown mode, first call PWR_ON and then de-assert lane dp reset.
 *       De-assert with osprey7_v2l8p1_tx_dp_reset(..) when waking up from a TX only PWRDN, osprey7_v2l8p1_rx_dp_reset(..)
 *       for a RX only PWRDN, and osprey7_v2l8p1_ln_dp_reset(..) for both RX and TX.
 * Note: PWRDN_TX_DEEP, PWRDN_RX_DEEP, and PWRDN_DEEP may require lane reconfiguration upon a PWR_ON.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] mode Enable/Disable lane powerdown based on #srds_core_pwrdn_mode_enum.
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_lane_pwrdn(srds_access_t *sa__, enum srds_core_pwrdn_mode_enum mode);

/** Serdes All Powerdown.
 * Powers down the core along with all PLLs and all lanes within the core.
 * Note: PWRDN_DEEP may require lane reconfiguration upon a PWR_ON.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] mode based on enum #srds_core_pwrdn_mode_enum select from PWRDN, or PWRDN_DEEP, or PWROFF_DEEP power down modes.
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_pwrdn_all(srds_access_t *sa__, enum srds_core_pwrdn_mode_enum mode);

#endif /* !SMALL_FOOTPRINT */
/*! @} SerdesAPIPwrMgtTag */
/*! @} APITag */
#endif /* SERDES_API_PWR_MGT_H */
#ifdef __cplusplus
}
#endif

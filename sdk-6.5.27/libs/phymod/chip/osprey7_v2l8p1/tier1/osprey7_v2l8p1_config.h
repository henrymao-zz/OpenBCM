/***********************************************************************************
 *                                                                                 *
 * Copyright: (c) 2021 Broadcom.                                                   *
 * Broadcom Proprietary and Confidential. All rights reserved.                     *
 *                                                                                 *
 ***********************************************************************************/

/***********************************************************************************
 ***********************************************************************************
 *                                                                                 *
 *  Revision    :      *
 *                                                                                 *
 *  Description :  Config functions targeted to IP user                            *
 *                                                                                 *
 ***********************************************************************************
 ***********************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OSPREY7_V2L8P1_API_CONFIG_H
#define OSPREY7_V2L8P1_API_CONFIG_H

#include <phymod/phymod_system.h>
#include "osprey7_v2l8p1_ipconfig.h"
#include "common/srds_api_enum.h"
#include "common/srds_api_err_code.h"
#include "common/srds_api_types.h"
#include "osprey7_v2l8p1_enum.h"
#include "osprey7_v2l8p1_types.h"
#include "osprey7_v2l8p1_select_defns.h"
#include "osprey7_v2l8p1_access.h"

/*! @file
 *  @brief Configuration functions provided to IP User
 */

/*! @addtogroup APITag
 * @{
 */

/*! @defgroup SerdesAPIConfigTag Configuration APIs
 * Serdes API functions which can be used to get and/or set
 * Serdes configuration settings, as well as enable/disable modes.
 * Also includes APIs for loading and verifying uCode.
 */

/*! @addtogroup SerdesAPIConfigTag
 * @{
 */

#define GRACEFUL_STOP_TIME 2000

#define IF_API_ID_CODES_DONT_MATCH_CORE_ID_CODES      \
uint16_t revid, revid2, ipversion;                    \
ESTM(revid     = rdc_revid_model());                  \
ESTM(revid2    = rdc_revid2());                       \
ESTM(ipversion = rd_ams_tx_version_id());             \
if ((OSPREY7_V2L8P1_REVID_MODEL_DEFAULT != revid || OSPREY7_V2L8P1_REVID2_DEFAULT != revid2) || \
    (OSPREY7_V2L8P1_AFE_IPVERSION_ID_DEFAULT_A0 != ipversion  && OSPREY7_V2L8P1_AFE_IPVERSION_ID_DEFAULT_A1 != ipversion &&  OSPREY7_V2L8P1_AFE_IPVERSION_ID_DEFAULT_C0 != ipversion && OSPREY7_V2L8P1_AFE_IPVERSION_ID_DEFAULT_C1 != ipversion)) { \
    EFUN_PRINTF(("ERROR: IP Hardware ID Mismatch. Expected: 0x%08X (A0), 0x%08X (A1), 0x%08X (C0), or 0x%08X (C1). Actual: 0x%08X.\n",               \
                (uint32_t)((OSPREY7_V2L8P1_REVID_MODEL_DEFAULT << 16) | (OSPREY7_V2L8P1_REVID2_DEFAULT << 8) | (OSPREY7_V2L8P1_AFE_IPVERSION_ID_DEFAULT_A0)),        \
                (uint32_t)((OSPREY7_V2L8P1_REVID_MODEL_DEFAULT << 16) | (OSPREY7_V2L8P1_REVID2_DEFAULT << 8) | (OSPREY7_V2L8P1_AFE_IPVERSION_ID_DEFAULT_A1)),        \
                (uint32_t)((OSPREY7_V2L8P1_REVID_MODEL_DEFAULT << 16) | (OSPREY7_V2L8P1_REVID2_DEFAULT << 8) | (OSPREY7_V2L8P1_AFE_IPVERSION_ID_DEFAULT_C0)),        \
                (uint32_t)((OSPREY7_V2L8P1_REVID_MODEL_DEFAULT << 16) | (OSPREY7_V2L8P1_REVID2_DEFAULT << 8) | (OSPREY7_V2L8P1_AFE_IPVERSION_ID_DEFAULT_C1)),        \
                (uint32_t)((revid << 16) | (revid2 << 8) | (ipversion))));



#define RELEASE_LOCK_AND_RETURN(__x__) \
    USR_RELEASE_LOCK; \
    return (__x__);

/****************************************************/
/*  CORE Based APIs - Required to be used per Core  */
/****************************************************/
#ifndef SMALL_FOOTPRINT
/* Returns API Version Number */
/** API Version Number.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] api_version API Version Number returned by the API
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_version(srds_access_t *sa__, uint32_t *api_version);
#endif /* SMALL_FOOTPRINT */

/*------------------------------------------------*/
/*  APIs to Read Core Config variables in uC RAM  */
/*------------------------------------------------*/
/** Read value of core_config uC RAM variable.
 *  Note that various API configuration functions can modify core config.
 *  Since the value returned by this can become stale, re-read after modifying core configuration.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] struct_val core_config RAM variable values read by the API
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_get_uc_core_config(srds_access_t *sa__, struct osprey7_v2l8p1_uc_core_config_st *struct_val);
/*------------------------------------------------*/
/*  APIs to get physical Tx addr for given lane   */
/*------------------------------------------------*/
/** Read value of physical Tx address for a mapped lane.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] lane Logical lane address for the lane
 * @param[out] physical_tx_lane get the physical address of the tx logical lane
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_get_physical_tx_addr(srds_access_t *sa__, uint8_t lane, uint8_t *physical_tx_lane);

/*------------------------------------------------*/
/*  APIs to get physical Rx addr for given lane   */
/*------------------------------------------------*/
/** Read value of physical Rx address for a mapped lane.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] lane Logical lane address for the lane
 * @param[out] physical_rx_lane get the physical address of the rx logical lane
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_get_physical_rx_addr(srds_access_t *sa__, uint8_t lane, uint8_t *physical_rx_lane);


/*------------------------------------------------*/
/*  APIs to get number of uc cores  */
/*------------------------------------------------*/
/** Get the number of uc cores.
 *  Note that various API configuration functions can modify core config.
 *  Since the value returned by this can become stale, re-read after modifying core configuration.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] num_micros Value containing the number of uc cores returned by the API.
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_get_micro_num_uc_cores(srds_access_t *sa__, uint8_t *num_micros);

/*-----------------------------------*/
/*  Microcode Load/Verify Functions  */
/*-----------------------------------*/
/** Performs the initial register writes which are required before loading microcode.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] pram indicates if the microcode is loaded through the PRAM interface (1 = yes; 0 = no )
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_ucode_load_init(srds_access_t *sa__, uint8_t pram);

/** Writes all or part of the microcode image into Micro.
 * Note: If microcode is being loaded with multiple writes, then ucode_len must be divisble by 4 (32 bit aligned)
 * for all writes, except for the final write, which does not need to be 32 bit aligned.
 * Note: osprey7_v2l8p1_ucode_load_init() must be called before the first call to osprey7_v2l8p1_ucode_load_write(),
 * and osprey7_v2l8p1_ucode_load_close() must be called after the last call to osprey7_v2l8p1_ucode_load_write().
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] ucode_image pointer to the Microcode image organized in bytes.
 * @param[in] ucode_len Length of Microcode Image (number of bytes).
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_ucode_load_write(srds_access_t *sa__, uint8_t *ucode_image, uint32_t ucode_len);

/** Ends Microcode loading state. Call after the last osprey7_v2l8p1_ucode_load_write().
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] pram indicates if the microcode is loaded through the PRAM interface (1 = yes; 0 = no )
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_ucode_load_close(srds_access_t *sa__, uint8_t pram);

/** Load Microcode into current one core through Register (MDIO) Interface.
 * Once the microcode is loaded, de-assert reset to micro to start executing microcode "wrc_micro_core_rstb(0x1)".
 * Note: Micro should be loaded only after issuing a osprey7_v2l8p1_uc_reset(1) followed by asserting and de-asserting
 * core_s_reset. Information table should be intialized with osprey7_v2l8p1_init_osprey7_v2l8p1_info after microcode load.
 * See relevant Programmers guide for more details.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] ucode_image pointer to the Microcode image organized in bytes.
 * @param[in] ucode_len Length of Microcode Image (number of bytes).
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_ucode_load(srds_access_t *sa__, uint8_t *ucode_image, uint32_t ucode_len);


#ifndef SMALL_FOOTPRINT
/** To verify the Microcode image loaded in the Micro.
 * Read back the microcode from Micro and check against expected microcode image.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] ucode_image pointer to the expected Microcode image organized in bytes.
 * @param[in] ucode_len Length of Microcode Image (number of bytes).
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_ucode_load_verify(srds_access_t *sa__, uint8_t *ucode_image, uint32_t ucode_len);

/** To verify the CRC of the microcode loaded in the Micro.
 * Instruct uC to read image and calculate CRC and check against expected CRC.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] ucode_len Length of Microcode Image (number of bytes)
 * @param[in] expected_crc_value Expected CRC value of the microcode
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_ucode_crc_verify(srds_access_t *sa__, uint32_t ucode_len, uint16_t expected_crc_value);

#endif /* SMALL_FOOTPRINT */

/** Load the Micro through the PRAM bus.
 * NOTE: Information table should be intialized with osprey7_v2l8p1_init_osprey7_v2l8p1_info after microcode load.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] ucode_image Microcode Image to be written.
 * @param[in] ucode_len Length of Microcode Image (number of bytes).
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_ucode_pram_load(srds_access_t *sa__, char const * ucode_image, uint32_t ucode_len);

/** Enable or Disable the uC reset.
 * Dummy function to maintain compatibility with BHK7 APIs [calls osprey7_v2l8p1_uc_reset(..) internally].
 * Note: Micro should be reset using the API everytime before reloading the microcode.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] enable Enable/Disable uC reset (1 = Enable; 0 = Disable).
 * @param[in] ucode_info struct has information regarding stack size.
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_uc_reset_with_info(srds_access_t *sa__, uint8_t enable, ucode_info_t ucode_info);

/** Enable or Disable the uC reset.
 * Note: Micro should be reset using the API everytime before reloading the microcode.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] enable Enable/Disable uC reset (1 = Enable; 0 = Disable).
 * @param[in] ucode_info struct has information regarding stack size.
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_uc_reset(srds_access_t *sa__, uint8_t enable, ucode_info_t ucode_info);

/** API to assert Serdes core reset.
 * Issues osprey7_v2l8p1_uc_reset followed by osprey7_v2l8p1 core reset (core_s_rstb) after selecting com_clk as micro_clk.
 * NOTE: This API should be used to issue a core reset instead of directly using the core_s_rstb register.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] ucode_info struct has information regarding stack size.
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_core_reset(srds_access_t *sa__, ucode_info_t ucode_info);

/** Wait for the uC to become active.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @return Error Code generated if uC does not become active (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_wait_uc_active(srds_access_t *sa__);

#define INFO_TABLE_END INFO_TABLE_END_LEGACY

/** Initialize the osprey7_v2l8p1_info for the uC.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @return Error Code generated if uC does not become active (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_init_osprey7_v2l8p1_info(srds_access_t *sa__);

#ifndef SMALL_FOOTPRINT

/** Set the core_cfg_from_pcs flag in the core configuration.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] core_cfg_from_pcs The value to set.
 * @return Error Code generated if uC does not become active (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_set_core_config_from_pcs(srds_access_t *sa__, uint8_t core_cfg_from_pcs);

/** Set the osr_5_en flag in the core configuration.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] osr_5_en The value to set.
 * @return Error Code generated if uC does not become active (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_set_osr_5_en(srds_access_t *sa__, uint8_t osr_5_en);

/** Configure the lane address mapping.
 *  Note: Micro and core data path must be in reset when this function is called.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] num_lanes The number of entries in tx_lane_map and rx_lane_map.
 *                  This must match the number of lanes associated with the core.
 * @param[in] tx_lane_map A num_lanes-sized array of lane indexes to map to the TX lanes.
 *                     Each entry must be from 0 to num_lanes-1, and each entry must be unique.
 * @param[in] rx_lane_map A num_lanes-sized array of lane indexes to map to the RX lanes.
 *                     Each entry must be from 0 to num_lanes-1, and each entry must be unique.
 *                     If independent TX / RX lane mapping is not enabled for a core, then this must match tx_lane_map.
 *
 * @b Example (2 lane core)
 * @code

    uint8_t const tx_lane_map[2] = {1,0};
    uint8_t const rx_lane_map[2] = {1,0};
    EFUN(wrc_micro_core_rstb(0));
    EFUN(osprey7_v2l8p1_core_dp_reset(sa__, 1));
    EFUN(osprey7_v2l8p1_map_lanes(sa__, 2, tx_lane_map, rx_lane_map));
 * @endcode
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_map_lanes(srds_access_t *sa__, const uint8_t num_lanes, uint8_t const *tx_lane_map, uint8_t const *rx_lane_map);
#endif /* SMALL_FOOTPRINT */

/*-----------------*/
/*  Configure PLL  */
/*-----------------*/

/** The pll can be configured by providing all four parameters:  refclk frequency, divider value, VCO output frequency and the PLL options.
 *  This is the only option in SMALL_FOOTPRINT
 */
#define osprey7_v2l8p1_configure_pll_refclk_div_vco osprey7_v2l8p1_INTERNAL_configure_pll

#ifndef SMALL_FOOTPRINT
/** PLL Powerdown.
 *
 * Powers down the selected PLL. To power up the PLL, reconfigure the PLL by using
 * one of the "osprey7_v2l8p1_configure_pll_" APIs.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_configure_pll_powerdown(srds_access_t *sa__);

/** Configure PLL.
 *
 * Use core_dp_s_rstb to re-initialize the PLL to its default configuration before calling this function.
 * For single PLL SerDes, use core_s_rstb instead of core_dp_s_rstb to also re-initialize all registers to default.
 *
 * Configures PLL registers to obtain the required configuration.
 * PLL configuration for this function is based on refclk frequency and divider value.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] refclk Reference clock frequency (enumerated).
 * @param[in] srds_div Divider value (enumerated).
 *
 * @b Example (refclk = 156.25 MHz, Divider = 170, VCO output frequency = 26.5625 GHz)
 * @code
    EFUN(osprey7_v2l8p1_core_dp_reset(sa__, 1));
    EFUN(osprey7_v2l8p1_configure_pll_refclk_div(sa__, OSPREY7_V2L8P1_PLL_REFCLK_156P25MHZ, OSPREY7_V2L8P1_PLL_DIV_170));
    EFUN(osprey7_v2l8p1_core_dp_reset(sa__, 0));
 * @endcode
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_configure_pll_refclk_div(srds_access_t *sa__,
                                           enum osprey7_v2l8p1_pll_refclk_enum refclk,
                                           enum osprey7_v2l8p1_pll_div_enum srds_div);

/** Configure PLL.
 *
 * Use core_dp_s_rstb to re-initialize the PLL to its default configuration before calling this function.
 * For single PLL SerDes, use core_s_rstb instead of core_dp_s_rstb to also re-initialize all registers to default.
 *
 * Configures PLL registers to obtain the required configuration.
 * PLL configuration for this function is based on refclk frequency and VCO output frequency.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] refclk Reference clock frequency (enumerated).
 * @param[in] vco_freq_khz VCO output frequency, in kHz.
 *
 * @b Example (VCO output frequency = 25 GHz, refclk = 156.25 MHz, Divider = 160)
 * @code
    EFUN(osprey7_v2l8p1_core_dp_reset(sa__, 1));
    EFUN(osprey7_v2l8p1_configure_pll_refclk_vco(sa__, OSPREY7_V2L8P1_PLL_REFCLK_156P25MHZ, 25000000));
    EFUN(osprey7_v2l8p1_core_dp_reset(sa__, 0));
 * @endcode
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_configure_pll_refclk_vco(srds_access_t *sa__,
                                           enum osprey7_v2l8p1_pll_refclk_enum refclk,
                                           uint32_t vco_freq_khz);

/** Configure PLL.
 *
 * Use core_dp_s_rstb to re-initialize the PLL to its default configuration before calling this function.
 * For single PLL SerDes, use core_s_rstb instead of core_dp_s_rstb to also re-initialize all registers to default.
 *
 * Configures PLL registers to obtain the required configuration.
 * PLL configuration for this function is based on divider value and VCO output frequency.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] srds_div Divider value (enumerated).
 * @param[in] vco_freq_khz VCO output frequency, in kHz.
 *
 * @b Example (VCO output frequency = 25 GHz, Divider = 170, refclk = 147.05 MHz)
 * @code
    EFUN(osprey7_v2l8p1_core_dp_reset(sa__, 1));
    EFUN(osprey7_v2l8p1_configure_pll_refclk_vco(sa__, OSPREY7_V2L8P1_PLL_DIV_170, 25000000));
    EFUN(osprey7_v2l8p1_core_dp_reset(sa__, 0));
 * @endcode
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_configure_pll_div_vco(srds_access_t *sa__,
                                        enum osprey7_v2l8p1_pll_div_enum srds_div,
                                        uint32_t vco_freq_khz);

/** Special Configure PLL to 53.125 GHz.
 *
 * Note: This function is only needed for afe A0 silicon, but is forward
 *       compatible with future afe silicon versions.
 * PLL configuration for this function is based on refclk value.
 * This function operates on the currently selected PLL index, configures PLL registers
 * to obtain the required configuration, and calls osprey7_v2l8p1_core_dp_reset() as needed.
 * For afe A0 silicon, this function first attempts to configure using LBVCO.
 * If configuration is unsuccessful, attempts to use HBVCO.
 * For afe B0 silicon, this function only attempts to configure using HBVCO.
 * For afe C0 silicon and beyond, this function only attempts to configure using LBVCO.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] refclk Reference clock frequency (enumerated).
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_configure_53P125G_pll_refclk(srds_access_t *sa__,
                                        enum osprey7_v2l8p1_pll_refclk_enum refclk);

/** Special Configure PLL to 53.125 GHz.
 *
 * Note: This function is only needed for afe A0 silicon, but is forward
 *       compatible with future afe silicon versions.
 * PLL configuration for this function is based on divider value.
 * This function operates on the currently selected PLL index, configures PLL registers
 * to obtain the required configuration, and calls osprey7_v2l8p1_core_dp_reset() as needed.
 * For afe A0 silicon, this function first attempts to configure using LBVCO.
 * If configuration is unsuccessful, attempts to use HBVCO.
 * For afe B0 silicon, this function only attempts to configure using HBVCO.
 * For afe C0 silicon and beyond, this function only attempts to configure using LBVCO.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] srds_div Divider value (enumerated).
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_configure_53P125G_pll_div(srds_access_t *sa__,
                                        enum osprey7_v2l8p1_pll_div_enum srds_div);

/** Special Configure PLL to 53.125 GHz using LB VCO.
 *
 * Note: This function is only needed for afe A0 silicon, but is forward
 *       compatible with future afe silicon versions.
 * PLL configuration for this function is based on refclk value.
 * This function operates on the currently selected PLL index, configures PLL registers
 * to obtain the required configuration, and calls osprey7_v2l8p1_core_dp_reset() as needed.
 * For afe A0 silicon, this function attempts to configure using LBVCO.
 * If configuration is unsuccessful, osprey7_v2l8p1_configure_53P125G_hb_pll() will need to be called.
 * For afe B0 silicon, this function only attempts to configure using HBVCO.
 * For afe C0 silicon and beyond, this function only attempts to configure using LBVCO.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] refclk Reference clock frequency (enumerated).
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_configure_53P125G_lb_pll_refclk(srds_access_t *sa__,
                                        enum osprey7_v2l8p1_pll_refclk_enum refclk);
/** Special Configure PLL to 53.125 GHz using LB VCO.
 *
 * Note: This function is only needed for afe A0 silicon, but is forward
 *       compatible with future afe silicon versions.
 * PLL configuration for this function is based on refclk value.
 * This function operates on the currently selected PLL index, configures PLL registers
 * to obtain the required configuration, and calls osprey7_v2l8p1_core_dp_reset() as needed.
 * For afe A0 silicon, this function attempts to configure using LBVCO.
 * If configuration is unsuccessful, osprey7_v2l8p1_configure_53P125G_hb_pll() will need to be called.
 * For afe B0 silicon, this function only attempts to configure using HBVCO.
 * For afe C0 silicon and beyond, this function only attempts to configure using LBVCO.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] srds_div Divider value (enumerated).
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_configure_53P125G_lb_pll_div(srds_access_t *sa__,
                                        enum osprey7_v2l8p1_pll_div_enum srds_div);

/** Special Configure PLL to 53.125 GHz using HB VCO.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] srds_div Divider value (enumerated).
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_configure_53P125G_hb_pll_div(srds_access_t *sa__,
                                        enum osprey7_v2l8p1_pll_div_enum srds_div);

/** Special  LB VCO out of range check for 53.125 GHz.
 *
 * Note: This function is only needed for afe A0 silicon.
 * This function checks to make sure that the pll_range register field value is within the allowed LB VCO range.
 * This function should be called after osprey7_v2l8p1_configure_53P125G_lb_pll_div() or osprey7_v2l8p1_configure_53P125G_lb_pll_refclk().
 * If pll_out_range == 1, then osprey7_v2l8p1_configure_53P125G_hb_pll() should be called to configure HB VCO.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] pll_out_range Pointer which will be set to 1 if the PLL is out of range, otherwise will be set to 0.
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_pll_lb_range_check(srds_access_t *sa__, uint8_t *pll_out_range);

/** Special  HB VCO out of range check for 53.125 GHz.
 *
 * Note: This function is only needed for afe A0 silicon.
 * This function checks to make sure that the pll_range register field value is within the allowed HB VCO range.
 * This function should be called after osprey7_v2l8p1_configure_53P125G_hb_pll.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] pll_out_range Pointer which will be set to 1 if the PLL is out of range, otherwise will be set to 0.
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_pll_hb_range_check(srds_access_t *sa__, uint8_t *pll_out_range);

/** Configure PLL.
 *
 * Use core_dp_s_rstb to re-initialize the PLL to its default configuration before calling this function.
 * For single PLL SerDes, use core_s_rstb instead of core_dp_s_rstb to also re-initialize all registers to default.
 *
 * Configures PLL registers to obtain the required configuration.
 * PLL configuration for this fucntion is based on input refclk frequency and divider value.
 * but first divides the input refclk by 2 and adjusts parameters accordingly.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] refclk Input Reference clock frequency before refclk divide by 2  (enumerated).
 * @param[in] srds_div Divider value based on input reference clock frequency (enumerated).
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_configure_pll_refclk_div_div2refclk(srds_access_t *sa__,
                                           enum osprey7_v2l8p1_pll_refclk_enum refclk,
                                           enum osprey7_v2l8p1_pll_div_enum srds_div);

/** Configure PLL.
 *
 * Use core_dp_s_rstb to re-initialize the PLL to its default configuration before calling this function.
 * For single PLL SerDes, use core_s_rstb instead of core_dp_s_rstb to also re-initialize all registers to default.
 *
 * Configures PLL registers to obtain the required configuration.
 * PLL configuration for this function is based on input refclk frequency and VCO output frequency.
 * but first divides the input refclk by 2 and adjusts parameters accordingly.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] refclk Input Reference clock frequency before refclk divide by 2 (enumerated).
 * @param[in] vco_freq_khz VCO output frequency, in kHz.
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_configure_pll_refclk_vco_div2refclk(srds_access_t *sa__,
                                           enum osprey7_v2l8p1_pll_refclk_enum refclk,
                                           uint32_t vco_freq_khz);

/** Configure PLL.
 *
 * Use core_dp_s_rstb to re-initialize the PLL to its default configuration before calling this function.
 * For single PLL SerDes, use core_s_rstb instead of core_dp_s_rstb to also re-initialize all registers to default.
 *
 * Configures PLL registers to obtain the required configuration.
 * PLL configuration for this function is based on divider value and VCO output frequency.
 * but first divides the input refclk by 2 and adjusts parameters accordingly.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] srds_div Divider value based on input refclk frequency before refclk divide by 2 (enumerated).
 * @param[in] vco_freq_khz VCO output frequency, in kHz.
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_configure_pll_div_vco_div2refclk(srds_access_t *sa__,
                                        enum osprey7_v2l8p1_pll_div_enum srds_div,
                                        uint32_t vco_freq_khz);
/** Configure PLL.
 *
 * Use core_dp_s_rstb to re-initialize the PLL to its default configuration before calling this function.
 * For single PLL SerDes, use core_s_rstb instead of core_dp_s_rstb to also re-initialize all registers to default.
 *
 * Configures PLL registers to obtain the required configuration.
 * PLL configuration for this fucntion is based on input refclk frequency and divider value.
 * but first divides the input refclk by 4 and adjusts parameters accordingly.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] refclk Input Reference clock frequency before refclk divide by 4  (enumerated).
 * @param[in] srds_div Divider value based on input reference clock frequency (enumerated).
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_configure_pll_refclk_div_div4refclk(srds_access_t *sa__,
                                           enum osprey7_v2l8p1_pll_refclk_enum refclk,
                                           enum osprey7_v2l8p1_pll_div_enum srds_div);

/** Configure PLL.
 *
 * Use core_dp_s_rstb to re-initialize the PLL to its default configuration before calling this function.
 * For single PLL SerDes, use core_s_rstb instead of core_dp_s_rstb to also re-initialize all registers to default.
 *
 * Configures PLL registers to obtain the required configuration.
 * PLL configuration for this function is based on input refclk frequency and VCO output frequency.
 * but first divides the input refclk by 4 and adjusts parameters accordingly.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] refclk Input Reference clock frequency before refclk divide by 4 (enumerated).
 * @param[in] vco_freq_khz VCO output frequency, in kHz.
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_configure_pll_refclk_vco_div4refclk(srds_access_t *sa__,
                                           enum osprey7_v2l8p1_pll_refclk_enum refclk,
                                           uint32_t vco_freq_khz);

/** Configure PLL.
 *
 * Use core_dp_s_rstb to re-initialize the PLL to its default configuration before calling this function.
 * For single PLL SerDes, use core_s_rstb instead of core_dp_s_rstb to also re-initialize all registers to default.
 *
 * Configures PLL registers to obtain the required configuration.
 * PLL configuration for this function is based on divider value and VCO output frequency.
 * but first divides the input refclk by 4 and adjusts parameters accordingly.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] srds_div Divider value based on input refclk frequency before refclk divide by 4 (enumerated).
 * @param[in] vco_freq_khz VCO output frequency, in kHz.
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_configure_pll_div_vco_div4refclk(srds_access_t *sa__,
                                        enum osprey7_v2l8p1_pll_div_enum srds_div,
                                        uint32_t vco_freq_khz);

/** Configure PLL.
 *
 * Use core_dp_s_rstb to re-initialize the PLL to its default configuration before calling this function.
 * For single PLL SerDes, use core_s_rstb instead of core_dp_s_rstb to also re-initialize all registers to default.
 *
 * Configures PLL registers to obtain the required configuration.
 * PLL configuration for this fucntion is based on refclk frequency and divider value.
 * Enables refclk doubler.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] refclk Reference clock frequency (enumerated).
 * @param[in] srds_div Divider value (enumerated).
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_configure_pll_refclk_div_refclk_2x(srds_access_t *sa__,
                                           enum osprey7_v2l8p1_pll_refclk_enum refclk,
                                           enum osprey7_v2l8p1_pll_div_enum srds_div);

/** Configure PLL.
 *
 * Use core_dp_s_rstb to re-initialize the PLL to its default configuration before calling this function.
 * For single PLL SerDes, use core_s_rstb instead of core_dp_s_rstb to also re-initialize all registers to default.
 *
 * Configures PLL registers to obtain the required configuration.
 * PLL configuration for this function is based on refclk frequency and VCO output frequency.
 * Enables refclk doubler.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] refclk Reference clock frequency (enumerated).
 * @param[in] vco_freq_khz VCO output frequency, in kHz.
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_configure_pll_refclk_vco_refclk_2x(srds_access_t *sa__,
                                           enum osprey7_v2l8p1_pll_refclk_enum refclk,
                                           uint32_t vco_freq_khz);

/** Configure PLL.
 *
 * Use core_dp_s_rstb to re-initialize the PLL to its default configuration before calling this function.
 * For single PLL SerDes, use core_s_rstb instead of core_dp_s_rstb to also re-initialize all registers to default.
 *
 * Configures PLL registers to obtain the required configuration.
 * PLL configuration for this function is based on divider value and VCO output frequency.
 * Enables refclk doubler.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] srds_div Divider value (enumerated).
 * @param[in] vco_freq_khz VCO output frequency, in kHz.
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_configure_pll_div_vco_refclk_2x(srds_access_t *sa__,
                                        enum osprey7_v2l8p1_pll_div_enum srds_div,
                                        uint32_t vco_freq_khz);

/** Get the VCO frequency in kHz, based on the reference clock frequency and divider value.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] refclk_freq_hz Reference clock frequency, in Hz.
 * @param[in] srds_div Divider value, in the same encoding as enum #osprey7_v2l8p1_pll_div_enum.
 * @param[out] vco_freq_khz VCO output frequency, in kHz, obtained based on reference clock frequency and dic value.
 * @param[in] pll_option Select PLL configuration option from enum #osprey7_v2l8p1_pll_option_enum.
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_get_vco_from_refclk_div(srds_access_t *sa__, uint32_t refclk_freq_hz, enum osprey7_v2l8p1_pll_div_enum srds_div, uint32_t *vco_freq_khz, enum osprey7_v2l8p1_pll_option_enum pll_option);
#endif /* SMALL_FOOTPRINT */

/**************************************************/
/* LANE Based APIs - Required to be used per Lane */
/**************************************************/

/*------------------------------------------------------------*/
/*  APIs to Write Lane Config and User variables into uC RAM  */
/*------------------------------------------------------------*/
/** Write to lane_config uC RAM variable.
 * Note: This API should be used only during configuration under dp_reset (osprey7_v2l8p1_ln_dp_reset()).
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] struct_val Value to be written into lane_config RAM variable.
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_set_uc_lane_cfg(srds_access_t *sa__, struct osprey7_v2l8p1_uc_lane_config_st struct_val);

/** Get force OS/BR/ER CDR mode
 * Note: ER-CDR Mode does not apply to 7nm Serdes cores
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] mode An enable/disable option from the enum osprey7_v2l8p1_force_cdr_mode_enum.
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_get_force_lane_cdr_mode(srds_access_t *sa__, enum osprey7_v2l8p1_force_cdr_mode_enum *mode);

/** Enable or disable force OS/BR/ER CDR mode
 * Note: This API should be used only during configuration under dp reset (osprey7_v2l8p1_ln_dp_reset()).
 *       When enabling one mode, this API will disable the other mode.
 * Note: ER-CDR Mode does not apply to 7nm Serdes cores
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] mode An enable/disable option from the enum osprey7_v2l8p1_force_cdr_mode_enum.
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_force_lane_cdr_mode(srds_access_t *sa__, enum osprey7_v2l8p1_force_cdr_mode_enum mode);

#ifndef SMALL_FOOTPRINT
/*-----------------------------------------------------------*/
/*  APIs to Read Lane Config and User variables from uC RAM  */
/*-----------------------------------------------------------*/
/** Read value of lane_config uC RAM variable.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] struct_val Value read from lane_config RAM variable.
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_get_uc_lane_cfg(srds_access_t *sa__, struct osprey7_v2l8p1_uc_lane_config_st *struct_val);
#endif /* SMALL_FOOTPRINT */

/*--------------------------------------------*/
/*  APIs to Reset Lane to Default             */
/*--------------------------------------------*/

/** Resets TX Lane to Default Configuration.
 * Toggles TX ln_s_rstb and leaves the lane TX in datapath reset.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_reset_tx_lane_to_default(srds_access_t *sa__);

/** Resets RX Lane to Default Configuration.
 * Toggles RX ln_s_rstb and leaves the lane RX in datapath reset.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_reset_rx_lane_to_default(srds_access_t *sa__);

/** Resets Lane to Default Configuration.
 * Toggles ln_s_rstb and leaves the lane in datapath reset.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_reset_lane_to_default(srds_access_t *sa__);

/*--------------------------------------------*/
/*  APIs to Enable or Disable datapath reset  */
/*--------------------------------------------*/

/** Enable or Disable TX datapath reset.
 * Asserts handshake signals upon disable.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] enable Enable/Disable TX datapath reset (1 = Enable; 0 = Disable).
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_tx_dp_reset(srds_access_t *sa__, uint8_t enable);

/** Enable or Disable RX datapath reset.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] enable Enable/Disable RX datapath reset (1 = Enable; 0 = Disable).
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_rx_dp_reset(srds_access_t *sa__, uint8_t enable);

/** Enable or Disable Core datapath reset.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] enable Enable/Disable Core datapath reset (1 = Enable; 0 = Disable).
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_core_dp_reset(srds_access_t *sa__, uint8_t enable);

/** Enable or Disable Lane datapath reset.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] enable Enable/Disable Lane datapath reset (1 = Enable; 0 = Disable).
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_ln_dp_reset(srds_access_t *sa__, uint8_t enable);

/*-----------------------------------------*/
/*  APIs for setting and getting OSR mode  */
/*-----------------------------------------*/

/** Configure if the TX and RX osr mode pins should only be used to configure the TX and RX osr modes.
 * Note: Calling this API will overwrite any OSR mode value previously programmed through osprey7_v2l8p1_set_osr_mode(),
 *       osprey7_v2l8p1_set_tx_osr_mode(), or osprey7_v2l8p1_set_rx_osr_mode().
 * Note: This API requires accessing microcode RAM variables.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] use_pins_only Allow the use of TX and RX osr mode pins (1 = Yes; 0 = No).
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_set_use_osr_mode_pins_only(srds_access_t *sa__, uint8_t use_pins_only);

/** Get the TX and RX osr mode pins only status.
 * Note: This API requires accessing microcode RAM variables.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] tx_use_pins_only Returns whether the TX OSR mode pins only should be used (1 = Yes; 0 = No).
 * @param[out] rx_use_pins_only Returns whether the RX OSR mode pins only should be used (1 = Yes; 0 = No).
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_get_use_osr_mode_pins_only(srds_access_t *sa__, uint8_t *tx_use_pins_only, uint8_t *rx_use_pins_only);

/** Configure if the RX osr mode pins should only be used to configure the RX osr mode.
 * Note: Calling this API will overwrite any OSR mode value previously programmed through osprey7_v2l8p1_set_osr_mode()
 *        or osprey7_v2l8p1_set_rx_osr_mode().
 * Note: This API requires accessing microcode RAM variables.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] rx_use_pins_only Allow the use of RX osr mode pins (1 = Yes; 0 = No).
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_set_use_rx_osr_mode_pins_only(srds_access_t *sa__, uint8_t rx_use_pins_only);

/** Get the RX osr mode pins only status.
 * Note: This API requires accessing microcode RAM variables.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] rx_use_pins_only Returns whether the RX OSR mode pins only should be used (1 = Yes; 0 = No).
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_get_use_rx_osr_mode_pins_only(srds_access_t *sa__, uint8_t *rx_use_pins_only);

/** Configure if the RX osr mode pins should only be used to configure the TX osr mode.
 * Note: Calling this API will overwrite any OSR mode value previously programmed through osprey7_v2l8p1_set_osr_mode()
 *        or osprey7_v2l8p1_set_tx_osr_mode().
 * Note: This API requires accessing microcode RAM variables.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] tx_use_pins_only Allow the use of TX osr mode pins (1 = Yes; 0 = No).
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_set_use_tx_osr_mode_pins_only(srds_access_t *sa__, uint8_t tx_use_pins_only);

/** Get the TX osr mode pins only status.
 * Note: This API requires accessing microcode RAM variables.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] tx_use_pins_only Returns whether the TX OSR mode pins only should be used (1 = Yes; 0 = No).
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_get_use_tx_osr_mode_pins_only(srds_access_t *sa__, uint8_t *tx_use_pins_only);

/** Set both the TX and RX osr mode.
 * Note: Calling this API will overwrite the osprey7_v2l8p1_set_use_osr_mode_pins_only() setting if it was previously set.
 * Note: This API should be used for configuring TX and RX osr modes when pins aren't being used. Do not write directly to the following
 *       register fields: rx_osr_mode_frc, rx_osr_mode_frc_val, tx_osr_mode_frc, tx_osr_mode_frc_val, osr_mode_frc, and osr_mode_frc_val.
 * Note: This API requires accessing microcode RAM variables.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] osr_mode The desired osr mode value that will be programmed.
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_set_osr_mode(srds_access_t *sa__, enum osprey7_v2l8p1_osr_mode_enum osr_mode);

/** Get both the TX and RX osr mode.
 * Note: A return value of 0x3f is uninitialized.
 * Note: This API returns the control status, not the actual hardware status. Use osprey7_v2l8p1_INTERNAL_get_osr_mode()
 *       if the actual hardware status is needed.
 * Note: This API requires accessing microcode RAM variables. If using pin only mode, then the osr_mode_pin
 *       status register can be directly read from rd_osr_mode_pin() instead of using this API.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] tx_osr_mode The returned TX osr mode.
 * @param[out] rx_osr_mode The returned RX osr mode.
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_get_osr_mode(srds_access_t *sa__, enum osprey7_v2l8p1_osr_mode_enum *tx_osr_mode, enum osprey7_v2l8p1_osr_mode_enum *rx_osr_mode);

/** Set the RX osr mode.
 * Note: Calling this API will overwrite the osprey7_v2l8p1_set_use_rx_osr_mode_pins_only() setting if it was previously set.
 * Note: This API should be used for configuring TX and RX osr modes when pins aren't being used. Do not write directly to the following
 *       register fields: rx_osr_mode_frc, rx_osr_mode_frc_val, tx_osr_mode_frc, tx_osr_mode_frc_val, osr_mode_frc, and osr_mode_frc_val.
 * Note: This API requires accessing microcode RAM variables.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] rx_osr_mode The desired RX osr mode value that will be programmed.
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_set_rx_osr_mode(srds_access_t *sa__, enum osprey7_v2l8p1_osr_mode_enum rx_osr_mode);

/** Get the RX osr mode.
 * Note: A return value of 0x3f is uninitialized.
 * Note: This API returns the control status, not the actual hardware status. Use osprey7_v2l8p1_INTERNAL_get_osr_mode()
 *       if the actual hardware status is needed.
 * Note: This API requires accessing microcode RAM variables. If using pin only mode, then the osr_mode_pin
 *       status register can be directly read from rd_rx_osr_mode_pin() instead of using this API.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] rx_osr_mode The returned RX osr mode.
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_get_rx_osr_mode(srds_access_t *sa__, enum osprey7_v2l8p1_osr_mode_enum *rx_osr_mode);

/** Set the TX osr mode.
 * Note: Calling this API will overwrite the osprey7_v2l8p1_set_use_tx_osr_mode_pins_only() setting if it was previously set.
 * Note: This API should be used for configuring TX and RX osr modes when pins aren't being used. Do not write directly to the following
 *       register fields: rx_osr_mode_frc, rx_osr_mode_frc_val, tx_osr_mode_frc, tx_osr_mode_frc_val, osr_mode_frc, and osr_mode_frc_val.
 * Note: This API requires accessing microcode RAM variables.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] tx_osr_mode The desired TX osr mode value that will be programmed.
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_set_tx_osr_mode(srds_access_t *sa__, enum osprey7_v2l8p1_osr_mode_enum tx_osr_mode);

/** Get the TX osr mode.
 * Note: A return value of 0x3f is uninitialized.
 * Note: This API returns the control status, not the actual hardware status. Use osprey7_v2l8p1_INTERNAL_get_osr_mode()
 *       if the actual hardware status is needed.
 * Note: This API requires accessing microcode RAM variables. If using pin only mode, then the osr_mode_pin
 *       status register can be directly read from rd_tx_osr_mode_pin() instead of using this API.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] tx_osr_mode The returned TX osr mode.
 * @return Error Code generated by invalid access (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_get_tx_osr_mode(srds_access_t *sa__, enum osprey7_v2l8p1_osr_mode_enum *tx_osr_mode);


/*---------------------------*/
/* TX Analog APIs            */
/*---------------------------*/
#ifndef SMALL_FOOTPRINT
/** Write TX AFE parameters.
 * NOTE: This API should be used only after lane_dp_reset is released.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] param selects the parameter to write based on #osprey7_v2l8p1_tx_afe_settings_enum.
 * @param[in] val is the signed input value to the parameter.
 * @return Error Code generated by invalid tap settings (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_write_tx_afe(srds_access_t *sa__, enum osprey7_v2l8p1_tx_afe_settings_enum param, int16_t val);
#endif /* SMALL_FOOTPRINT */

/** Read TX AFE parameters.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] param selects the parameter to read based on #osprey7_v2l8p1_tx_afe_settings_enum.
 * @param[out] val is the returned signed value of the parameter.
 * @return Error Code generated by invalid tap settings (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_read_tx_afe(srds_access_t *sa__, enum osprey7_v2l8p1_tx_afe_settings_enum param, int16_t *val);

/** Validates Osprey TXFIR tap settings.
 * Returns failcodes if TXFIR settings are invalid.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] enable_taps Enable TXFIR TAPs based on #osprey7_v2l8p1_txfir_tap_enable_enum.
 * @param[in] pre3    TXFIR pre3  tap value (-8 to 0 when in PAM4 mode, otherwise -127 to 127).
 * @param[in] pre2    TXFIR pre2  tap value.
 * @param[in] pre1    TXFIR pre1  tap value.
 * @param[in] main    TXFIR main  tap value (-168 to +168 when in PAM4 mode, otherwise -127 to 127).
 * @param[in] post1   TXFIR post  tap value.
 * @param[in] post2   TXFIR post2 tap value.
 * @return Error Code generated by invalid tap settings (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_validate_txfir_cfg(srds_access_t *sa__, enum osprey7_v2l8p1_txfir_tap_enable_enum enable_taps, int16_t pre3, int16_t pre2, int16_t pre1, int16_t main, int16_t post1, int16_t post2);

/** Writes Serdes TXFIR tap settings.
 * Returns failcodes if TXFIR settings are invalid.
 * NOTE: Dynamically switching between enable_6tap and !enable_6tap will cause a 1UI slip in TX.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] enable_taps Enable TXFIR TAPs based on #osprey7_v2l8p1_txfir_tap_enable_enum.
 * @param[in] pre3    TXFIR pre3  tap value (-8 to 0 when in PAM4 mode, otherwise -127 to 127).
 * @param[in] pre2    TXFIR pre2  tap value.
 * @param[in] pre1    TXFIR pre1  tap value.
 * @param[in] main    TXFIR main  tap value (-168 to +168 when in PAM4 mode, otherwise -127 to 127).
 * @param[in] post1   TXFIR post  tap value.
 * @param[in] post2   TXFIR post2 tap value.
 * @return Error Code generated by invalid tap settings (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_apply_txfir_cfg(srds_access_t *sa__, enum osprey7_v2l8p1_txfir_tap_enable_enum enable_taps, int16_t pre3, int16_t pre2, int16_t pre1, int16_t main, int16_t post1, int16_t post2);



/*----------------*/
/*   PMD_RX_LOCK  */
/*----------------*/

/** PMD rx lock status of current lane.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] *pmd_rx_lock PMD_RX_LOCK status of current lane returned by API.
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_pmd_lock_status(srds_access_t *sa__, uint8_t *pmd_rx_lock);

/*--------------------------------*/
/*  Serdes TX disable/RX Restart  */
/*--------------------------------*/
/** TX Disable.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] enable Enable/Disable TX disable (1 = TX Disable asserted; 0 = TX Disable removed).
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_tx_disable(srds_access_t *sa__, uint8_t enable);

/** Enable/disable Restart RX and hold.
 * (Reset DSC state machine into RESTART State and hold it till disabled)
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] enable Enable/Disable Restart RX and hold (1 = RX restart and hold; 0 = Release hold in restart state)
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_rx_restart(srds_access_t *sa__, uint8_t enable);


/*----------------------*/
/*  Fast Link Recovery  */
/*----------------------*/

/** Configure Fast Link Recovery (FLR) for the lane.
 * This may only be performed while the lane is in reset.
 * Note: Enabling this API will disable slicer vertical offset tuning and DFE tap 1 adaptation in steady state.
 *       Disabling this API will enable slicer vertical offset tuning and DFE tap 1 adaptation in steady state.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] enable Enables the FLR feature.
 * @param[in] enable_timeout Enables timeout.
 * @param[in] timeout_time The timeout time, if enable_timeout is set.
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_configure_fast_link_recovery(srds_access_t *sa__, uint8_t enable, uint8_t enable_timeout, enum osprey7_v2l8p1_flr_timeout_enum timeout_time);

/** Get Fast Link Recovery (FLR) Configuration for the lane.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] enable Returns if FLR is enabled (1 = Enabled; 0 = Disabled).
 * @param[out] enable_timeout  Returns if timeouts are enabled (1 = Enabled; 0 = Disabled).
 * @param[out] timeout_time Returns the value of the timeout time, if enable_timeout is set.
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_get_configure_fast_link_recovery(srds_access_t *sa__, uint8_t *enable, uint8_t *enable_timeout, enum osprey7_v2l8p1_flr_timeout_enum *timeout_time);


#ifndef SMALL_FOOTPRINT
/*-----------------------------*/
/*  Stop/Resume RX Adaptation  */
/*-----------------------------*/
/** Stop RX Adaptation on a Lane. Control is returned only after attempting to stop adaptation.
 * RX Adaptation needs to be stopped before modifying any of the VGA, PF or DFE taps.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] enable Enable RX Adaptation stop (1 = Stop RX Adaptation on lane; 0 = Resume RX Adaptation on lane)
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_stop_rx_adaptation(srds_access_t *sa__, uint8_t enable);

/** Request to stop RX Adaptation on a Lane.
 * Control will be returned immediately before adaptaion is completely stopped.
 * RX Adaptation needs to be stopped before modifying any of the VGA, PF or DFE taps.
 * To resume RX adaptation, use the osprey7_v2l8p1_stop_rx_adaptation() API.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_request_stop_rx_adaptation(srds_access_t *sa__);
#endif /* SMALL_FOOTPRINT */

#if !defined(SMALL_FOOTPRINT) 
/*------------------------------------*/
/*  Read/Write all RX AFE parameters  */
/*------------------------------------*/

/** Write to RX AFE settings.
 * Note: RX Adaptation needs to be stopped before modifying any of the VGA, PF or DFE taps.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] param Enum (#srds_rx_afe_settings_enum) to select the required RX AFE setting to be modified
 * @param[in] val Value to be written to the selected AFE setting
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_write_rx_afe(srds_access_t *sa__, enum srds_rx_afe_settings_enum param, int8_t val);
#endif /* !SMALL_FOOTPRINT */

#ifndef SMALL_FOOTPRINT
/** Read from RX AFE settings.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] param Enum (#srds_rx_afe_settings_enum) to select the required RX AFE setting to be read.
 * @param[out] val RX AFE value returned from API.
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_read_rx_afe(srds_access_t *sa__, enum srds_rx_afe_settings_enum param, int8_t *val);
#endif /* SMALL_FOOTPRINT */

/*-----------------------------*/
/*  TX_PI Fixed Frequency Mode */
/*-----------------------------*/

/** TX_PI Fixed Frequency Mode.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] enable Enable/Disable TX_PI (1 = Enable; 0 = Disable)
 * @param[in] freq_override_val Fixed Frequency Override value (freq_override_val = desired_ppm*8192/781.25; Range: -8192 to + 8192);
 * @return Error Code generated by invalid TX_PI settings (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_tx_pi_freq_override(srds_access_t *sa__, uint8_t enable, int16_t freq_override_val);

#ifndef SMALL_FOOTPRINT
/** This function allows user to align TX clocks in selected lanes.
 * The current lane is expected to be the master lane.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] enable - 0: enable tx_clock_align for selected lanes with current lane as master;
 *                 1: disable tx_clock_align for selected lanes including master lane.
 * @param[in] lane_mask: bit mask for selecting lanes (0x00001111 - lane 0-3 are selected).
 * NOTE: The current lane should be selected as part of the lane_mask; else API errors out.
 * @return Error Code, if generated (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_tx_clock_align_enable(srds_access_t *sa__, uint8_t enable, uint8_t lane_mask);
#endif /* SMALL_FOOTPRINT */

/*--------------------------------------------*/
/*  Loopback and Ultra-Low Latency Functions  */
/*--------------------------------------------*/

/** Locks TX_PI to Loop timing.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] enable Enable TX_PI lock to loop timing (1 = Enable Lock; 0 = Disable Lock)
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_loop_timing(srds_access_t *sa__, uint8_t enable);

/** Enable/Disable Remote Loopback.
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[in] enable Enable Remote Loopback (1 = Enable rmt_lpbk; 0 = Disable rmt_lpbk)
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors)
 */
err_code_t osprey7_v2l8p1_rmt_lpbk(srds_access_t *sa__, uint8_t enable);

/*! @} SerdesAPIConfigTag */
/*! @} APITag */
#endif
#ifdef __cplusplus
}
#endif

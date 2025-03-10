/*
 *         
 * 
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *     
 * DO NOT EDIT THIS FILE!
 *
 */

#include <phymod/phymod.h>
#include <phymod/phymod_system.h>
#include <phymod/phymod_diagnostics.h>
#include <phymod/phymod_diagnostics_dispatch.h>

#ifdef PHYMOD_TSCBH_SUPPORT

#include <phymod/chip/tscbh_diagnostics.h>

#include <phymod/chip/blackhawk_diagnostics.h>

__phymod_diagnostics__dispatch__t__ phymod_diagnostics_tscbh_diagnostics_driver = {

    tscbh_phy_rx_slicer_position_set,
    tscbh_phy_rx_slicer_position_get,
    tscbh_phy_rx_slicer_position_max_get,
    blackhawk_phy_prbs_config_set,
    blackhawk_phy_prbs_config_get,
    blackhawk_phy_prbs_enable_set,
    blackhawk_phy_prbs_enable_get,
    blackhawk_phy_prbs_status_get,
    blackhawk_phy_pattern_config_set,
    blackhawk_phy_pattern_config_get,
    blackhawk_phy_pattern_enable_set,
    blackhawk_phy_pattern_enable_get,
    tscbh_core_diagnostics_get,
    tscbh_phy_diagnostics_get,
    blackhawk_phy_pmd_info_dump,
    NULL, /* phymod_phy_pcs_info_dump */
    tscbh_phy_eyescan_run,
    NULL, /* phymod_phy_link_mon_enable_set */
    NULL, /* phymod_phy_link_mon_enable_get */
    NULL, /* phymod_phy_link_mon_status_get */
    tscbh_phy_fec_correctable_counter_get,
    tscbh_phy_fec_uncorrectable_counter_get,
    tscbh_phy_stat_get,
    tscbh_phy_fec_cl91_correctable_counter_get,
    tscbh_phy_fec_cl91_uncorrectable_counter_get,
    blackhawk_phy_PAM4_tx_pattern_enable_set,
    blackhawk_phy_PAM4_tx_pattern_enable_get,
    blackhawk_phy_tx_pattern_set,
    blackhawk_phy_tx_pattern_get,
    blackhawk_phy_ber_proj,
    blackhawk_phy_fast_ber_proj_get,
    tscbh_phy_rsfec_symbol_error_counter_get,
    blackhawk_phy_linkcat,
    blackhawk_phy_pmd_lane_diag_debug_level_set,
    blackhawk_phy_pmd_lane_diag_debug_level_get,
    blackhawk_phy_pmd_usr_misc_ctrl_set,
    blackhawk_phy_pmd_usr_misc_ctrl_get,
    tscbh_phy_fec_error_inject_set,
    tscbh_phy_fec_error_inject_get,
    tscbh_phy_fec_error_bits_counter_get,
    NULL, /* phymod_phy_fec_error_inject_config_set */
    NULL, /* phymod_phy_fec_error_inject_config_get */
    NULL, /* phymod_phy_fec_error_inject_enable_set */
    NULL, /* phymod_phy_fec_error_inject_enable_get */
};

#endif /* PHYMOD_TSCBH_SUPPORT */


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

#include <bcm/port.h>
#include <bcm_int/dnx/port/imb/imb_common.h>
#include <bcm_int/dnx/port/imb/imb_internal.h>
#include <soc/portmod/portmod.h>
#include <soc/dnx/swstate/auto_generated/access/dnx_port_imb_access.h>
#include <soc/dnx/swstate/auto_generated/types/dnx_port_imb_types.h>
#include <soc/sand/shrextend/shrextend_debug.h>
#include <bcm_int/dnx/port/imb/imb.h>
#include <bcm_int/dnx/port/imb/imb_dispatch.h>

#include <bcm_int/dnx/port/imb/imb_ilu.h>

#include <bcm_int/dnx/port/imb/imb_ile.h>

const __imb__dispatch__t__ imb_imb_ilu_driver = {

    imb_ilu_init,
    imb_ilu_deinit,
    imb_ilu_port_pad_size_set,
    imb_ilu_port_pad_size_get,
    NULL,       /* imb_port_link_recovery_enable_set */
    NULL,       /* imb_port_link_recovery_enable_get */
    imb_ilu_port_attach,
    imb_ilu_port_detach,
    imb_ilu_port_enable_set,
    imb_ilu_port_enable_get,
    imb_ile_port_rx_data_enable_set,
    imb_ile_port_loopback_set,
    imb_ile_port_loopback_get,
    NULL,       /* imb_port_phy_loopback_adapter_set */
    imb_ile_port_link_state_get,
    NULL,       /* imb_port_eee_enable_set */
    NULL,       /* imb_port_eee_enable_get */
    NULL,       /* imb_port_link_up_mac_update */
    NULL,       /* imb_port_link_up_mac_update_post */
    NULL,       /* imb_port_priority_config_set */
    NULL,       /* imb_port_priority_config_get */
    imb_ile_port_phy_measure_get,
    imb_common_port_over_sampling_get,
    portmod_port_autoneg_set,
    portmod_port_autoneg_get,
    portmod_port_link_get,
    NULL,       /* imb_port_max_packet_size_set */
    NULL,       /* imb_port_max_packet_size_get */
    NULL,       /* imb_port_tx_average_ipg_set */
    NULL,       /* imb_port_tx_average_ipg_get */
    NULL,       /* imb_port_duplex_set */
    NULL,       /* imb_port_duplex_get */
    NULL,       /* imb_port_cntmaxsize_set */
    NULL,       /* imb_port_cntmaxsize_get */
    NULL,       /* imb_port_local_fault_status_get */
    NULL,       /* imb_port_local_fault_status_clear */
    NULL,       /* imb_port_remote_fault_status_get */
    NULL,       /* imb_port_remote_fault_status_clear */
    NULL,       /* imb_port_local_fault_enable_set */
    NULL,       /* imb_port_local_fault_enable_get */
    NULL,       /* imb_port_remote_fault_enable_set */
    NULL,       /* imb_port_remote_fault_enable_get */
    NULL,       /* imb_port_faults_status_get */
    NULL,       /* imb_port_eee_set */
    NULL,       /* imb_port_eee_get */
    imb_ilu_bandwidth_get,
    imb_ilu_port_tx_start_thr_set,
    imb_ilu_port_tx_start_thr_get,
    imb_ilu_prd_enable_set,
    imb_ilu_prd_enable_get,
    imb_ilu_prd_properties_set,
    imb_ilu_prd_properties_get,
    NULL,       /* imb_prd_port_profile_map_set */
    NULL,       /* imb_prd_port_profile_map_get */
    imb_ilu_prd_map_set,
    imb_ilu_prd_map_get,
    imb_ilu_prd_threshold_set,
    imb_ilu_prd_threshold_get,
    imb_ilu_prd_threshold_max_get,
    imb_ilu_prd_tpid_set,
    imb_ilu_prd_tpid_get,
    imb_ilu_prd_drop_count_get,
    imb_ilu_prd_custom_ether_type_set,
    imb_ilu_prd_custom_ether_type_get,
    imb_ilu_prd_flex_key_entry_set,
    imb_ilu_prd_flex_key_entry_get,
    imb_ilu_prd_ether_type_size_set,
    imb_ilu_prd_ether_type_size_get,
    imb_ilu_prd_tcam_entry_key_offset_base_set,
    imb_ilu_prd_tcam_entry_key_offset_base_get,
    imb_ilu_prd_tcam_entry_key_offset_set,
    imb_ilu_prd_tcam_entry_key_offset_get,
    imb_ilu_prd_control_frame_set,
    imb_ilu_prd_control_frame_get,
    imb_ilu_prd_mpls_special_label_set,
    imb_ilu_prd_mpls_special_label_get,
    NULL,       /* imb_prd_port_last_packet_priority_get */
    imb_ile_port_logical_lane_order_set,
    imb_ile_port_logical_lane_order_get,
    imb_common_port_prbs_polynomial_set,
    imb_common_port_prbs_polynomial_get,
    imb_common_port_prbs_invert_data_set,
    imb_common_port_prbs_invert_data_get,
    imb_ile_port_prbs_enable_set,
    imb_common_port_prbs_enable_get,
    imb_common_port_prbs_rx_status_get,
    NULL,       /* imb_port_rx_rmc_priority_config_set */
    imb_ilu_port_rx_fifo_status_get,
    imb_ilu_port_tx_fifo_status_get,
    NULL,       /* imb_port_low_latency_llfc_enable_set */
    NULL,       /* imb_port_low_latency_llfc_enable_get */
    NULL,       /* imb_port_fec_error_detect_enable_set */
    NULL,       /* imb_port_fec_error_detect_enable_get */
    NULL,       /* imb_port_llfc_after_fec_enable_set */
    NULL,       /* imb_port_llfc_after_fec_enable_get */
    NULL,       /* imb_port_extract_congestion_indication_from_llfc_enable_set */
    NULL,       /* imb_port_extract_congestion_indication_from_llfc_enable_get */
    NULL,       /* imb_port_control_cells_fec_bypass_enable_set */
    NULL,       /* imb_port_control_cells_fec_bypass_enable_get */
    imb_ilu_port_speed_config_set,
    imb_ile_port_mib_counter_get,
    NULL,       /* imb_port_mib_counter_set */
    imb_ile_port_mib_counter_clear,
    NULL,       /* imb_port_autoneg_ability_advert_set */
    NULL,       /* imb_port_autoneg_ability_advert_get */
    NULL,       /* imb_port_speed_ability_local_get */
    NULL,       /* imb_port_autoneg_ability_remote_get */
    imb_ilu_port_scheduler_config_set,
    imb_ilu_port_scheduler_priority_update,
    imb_ile_port_resource_default_get,
    NULL,       /* imb_port_to_stif_instance_map_set */
    NULL,       /* imb_port_gen_pfc_from_rmc_enable_set */
    NULL,       /* imb_port_gen_pfc_from_rmc_enable_get */
    NULL,       /* imb_port_gen_llfc_from_rmc_enable_set */
    imb_ilu_port_stop_pm_from_cfc_llfc_enable_set,
    NULL,       /* imb_port_stop_pm_from_pfc_enable_set */
    NULL,       /* imb_port_stop_pm_from_pfc_enable_get */
    NULL,       /* imb_port_pfc_force_enable_set */
    NULL,       /* imb_port_gen_pfc_from_llfc_thresh_enable_set */
    NULL,       /* imb_port_gen_pfc_from_llfc_thresh_enable_get */
    NULL,       /* imb_port_fc_rx_qmlf_threshold_set */
    NULL,       /* imb_port_fc_rx_qmlf_threshold_get */
    imb_ilu_fc_reset_set,
    NULL,       /* imb_llfc_from_glb_rsc_enable_set */
    NULL,       /* imb_pfc_rec_priority_map */
    NULL,       /* imb_pfc_rec_priority_unmap */
    NULL,       /* imb_pfc_mask_on_link_fail_enable_set */
    imb_ile_port_fec_speed_validate,
    imb_ilu_inband_ilkn_fc_init,
    NULL,       /* imb_calendar_set */
    NULL,       /* imb_port_fifo_resource_set */
    NULL,       /* imb_post_init */
    NULL,       /* imb_instru_synced_counters_config_set */
    NULL,       /* imb_instru_synced_counters_config_get */
    NULL,       /* imb_instru_synced_counters_last_write_get */
    NULL,       /* imb_instru_synced_counters_per_record_get */
    NULL,       /* imb_instru_counters_reset_set */
    NULL,       /* imb_instru_counters_reset_get */
    NULL,       /* imb_instru_traffic_counters_reset */
    NULL,       /* imb_port_instru_traffic_counters_reset */
    NULL,       /* imb_instru_pfc_deadlock_counters_reset */
    NULL,       /* imb_port_instru_pfc_deadlock_counters_reset */
    NULL,       /* imb_pfc_deadlock_debug_info_get */
    NULL,       /* imb_pfc_deadlock_max_duration_set */
    NULL,       /* imb_pfc_deadlock_max_duration_get */
    imb_ile_port_phy_control_validate,
    NULL,       /* imb_port_pre_add_validate */
    NULL,       /* imb_port_autoneg_ability_verify */
    NULL,       /* imb_port_pcs_lane_map_set */
    imb_ilu_port_link_status_change_event,
    imb_ile_port_pm_lock_status_change_event,
    imb_ilu_port_rx_buffers_restart,
    NULL,       /* imb_port_l1_mismatch_rate_rx_config_set */
    NULL,       /* imb_port_post_ber_proj_get */
    NULL,       /* imb_flexe_core_port_config_set */
    imb_ile_portmod_add_info_config,
    NULL,       /* imb_portmod_soft_reset_lock */
    NULL,       /* imb_portmod_soft_reset_unlock */
    NULL,       /* imb_port_link_fault_force_set */
    NULL,       /* imb_port_link_fault_force_get */
    NULL,       /* imb_fec_global_enable_set */
    NULL,       /* imb_port_timesync_tx_info_get */
    portmod_port_add,
    NULL,       /* imb_port_txpi_sdm_override_set */
    NULL,       /* imb_port_txpi_sdm_override_get */
    NULL,       /* imb_port_txpi_sdm_status_get */
    NULL,       /* imb_port_lane_map_set */
    NULL,       /* imb_port_lane_map_get */
    NULL,       /* imb_preemption_control_set */
    NULL,       /* imb_preemption_control_get */
    NULL,       /* imb_preemption_verify_status_get */
    NULL,       /* imb_preemption_tx_status_get */
    NULL,       /* imb_port_flr_link_config_set */
    NULL,       /* imb_port_mac_tx_threshold_set */
    NULL,       /* imb_port_ghao_speed_config_set */
    NULL,       /* imb_port_l1_eth_1588_enable_set */
    NULL,       /* imb_port_l1_eth_1588_enable_get */
    NULL,       /* imb_port_txpi_sdm_divider_set */
    NULL,       /* imb_pm_reset_get */
};


/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifndef _DNX_DATA_INTERNAL_FC_H_

#define _DNX_DATA_INTERNAL_FC_H_

#include <soc/dnx/dnx_data/auto_generated/dnx_data_internal.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_fc.h>



#ifndef BCM_DNX_SUPPORT
#error "This file is for use by DNX family only!"
#endif



typedef enum
{
    dnx_data_fc_submodule_general,
    dnx_data_fc_submodule_calendar_common,
    dnx_data_fc_submodule_coe,
    dnx_data_fc_submodule_oob,
    dnx_data_fc_submodule_inband,
    dnx_data_fc_submodule_pfc_deadlock,

    
    _dnx_data_fc_submodule_nof
} dnx_data_fc_submodule_e;








int dnx_data_fc_general_feature_get(
    int unit,
    dnx_data_fc_general_feature_e feature);



typedef enum
{
    dnx_data_fc_general_define_nof_glb_rsc,
    dnx_data_fc_general_define_nof_gen_bmps,
    dnx_data_fc_general_define_gen_bmp_first_id,
    dnx_data_fc_general_define_nof_af_nif_indications,
    dnx_data_fc_general_define_nof_cal_llfcs,
    dnx_data_fc_general_define_nof_entries_qmlf,
    dnx_data_fc_general_define_nof_bits_in_pfc_status_select,
    dnx_data_fc_general_define_nof_rmc_thresholds_profiles,
    dnx_data_fc_general_define_rmc_pfc_set_threshold_default,
    dnx_data_fc_general_define_rmc_pfc_clear_threshold_default,
    dnx_data_fc_general_define_rmc_llfc_set_threshold_default,
    dnx_data_fc_general_define_rmc_llfc_clear_threshold_default,
    dnx_data_fc_general_define_nof_bits_in_nif_eth_rmc_id,
    dnx_data_fc_general_define_bcm_cos_count,

    
    _dnx_data_fc_general_define_nof
} dnx_data_fc_general_define_e;



uint32 dnx_data_fc_general_nof_glb_rsc_get(
    int unit);


uint32 dnx_data_fc_general_nof_gen_bmps_get(
    int unit);


uint32 dnx_data_fc_general_gen_bmp_first_id_get(
    int unit);


uint32 dnx_data_fc_general_nof_af_nif_indications_get(
    int unit);


uint32 dnx_data_fc_general_nof_cal_llfcs_get(
    int unit);


uint32 dnx_data_fc_general_nof_entries_qmlf_get(
    int unit);


uint32 dnx_data_fc_general_nof_bits_in_pfc_status_select_get(
    int unit);


uint32 dnx_data_fc_general_nof_rmc_thresholds_profiles_get(
    int unit);


uint32 dnx_data_fc_general_rmc_pfc_set_threshold_default_get(
    int unit);


uint32 dnx_data_fc_general_rmc_pfc_clear_threshold_default_get(
    int unit);


uint32 dnx_data_fc_general_rmc_llfc_set_threshold_default_get(
    int unit);


uint32 dnx_data_fc_general_rmc_llfc_clear_threshold_default_get(
    int unit);


uint32 dnx_data_fc_general_nof_bits_in_nif_eth_rmc_id_get(
    int unit);


uint32 dnx_data_fc_general_bcm_cos_count_get(
    int unit);



typedef enum
{

    
    _dnx_data_fc_general_table_nof
} dnx_data_fc_general_table_e;









int dnx_data_fc_calendar_common_feature_get(
    int unit,
    dnx_data_fc_calendar_common_feature_e feature);



typedef enum
{
    dnx_data_fc_calendar_common_define_rx_dest_pfc,
    dnx_data_fc_calendar_common_define_rx_dest_nif_llfc,
    dnx_data_fc_calendar_common_define_rx_dest_port_2_prio,
    dnx_data_fc_calendar_common_define_rx_dest_port_4_prio,
    dnx_data_fc_calendar_common_define_rx_dest_port_8_prio,
    dnx_data_fc_calendar_common_define_rx_dest_pfc_generic_bmp,
    dnx_data_fc_calendar_common_define_rx_dest_empty,
    dnx_data_fc_calendar_common_define_tx_src_vsq_a_b_c,
    dnx_data_fc_calendar_common_define_tx_src_vsq_d,
    dnx_data_fc_calendar_common_define_tx_src_llfc_vsq,
    dnx_data_fc_calendar_common_define_tx_src_pfc_vsq,
    dnx_data_fc_calendar_common_define_tx_src_glb_rsc,
    dnx_data_fc_calendar_common_define_tx_src_nif_llfc,
    dnx_data_fc_calendar_common_define_tx_src_empty,

    
    _dnx_data_fc_calendar_common_define_nof
} dnx_data_fc_calendar_common_define_e;



uint32 dnx_data_fc_calendar_common_rx_dest_pfc_get(
    int unit);


uint32 dnx_data_fc_calendar_common_rx_dest_nif_llfc_get(
    int unit);


uint32 dnx_data_fc_calendar_common_rx_dest_port_2_prio_get(
    int unit);


uint32 dnx_data_fc_calendar_common_rx_dest_port_4_prio_get(
    int unit);


uint32 dnx_data_fc_calendar_common_rx_dest_port_8_prio_get(
    int unit);


uint32 dnx_data_fc_calendar_common_rx_dest_pfc_generic_bmp_get(
    int unit);


uint32 dnx_data_fc_calendar_common_rx_dest_empty_get(
    int unit);


uint32 dnx_data_fc_calendar_common_tx_src_vsq_a_b_c_get(
    int unit);


uint32 dnx_data_fc_calendar_common_tx_src_vsq_d_get(
    int unit);


uint32 dnx_data_fc_calendar_common_tx_src_llfc_vsq_get(
    int unit);


uint32 dnx_data_fc_calendar_common_tx_src_pfc_vsq_get(
    int unit);


uint32 dnx_data_fc_calendar_common_tx_src_glb_rsc_get(
    int unit);


uint32 dnx_data_fc_calendar_common_tx_src_nif_llfc_get(
    int unit);


uint32 dnx_data_fc_calendar_common_tx_src_empty_get(
    int unit);



typedef enum
{

    
    _dnx_data_fc_calendar_common_table_nof
} dnx_data_fc_calendar_common_table_e;









int dnx_data_fc_coe_feature_get(
    int unit,
    dnx_data_fc_coe_feature_e feature);



typedef enum
{
    dnx_data_fc_coe_define_nof_coe_cal_instances,
    dnx_data_fc_coe_define_nof_supported_chan_ids,
    dnx_data_fc_coe_define_nof_coe_vid_mask_width,
    dnx_data_fc_coe_define_nof_coe_vid_right_shift_width,
    dnx_data_fc_coe_define_nof_coe_ptc_mask_width,
    dnx_data_fc_coe_define_nof_coe_ptc_left_shift_width,
    dnx_data_fc_coe_define_max_coe_ticks,
    dnx_data_fc_coe_define_fc_support,
    dnx_data_fc_coe_define_map_value_size_in_bits,
    dnx_data_fc_coe_define_calendar_pause_resolution,
    dnx_data_fc_coe_define_data_offset,
    dnx_data_fc_coe_define_ethertype,
    dnx_data_fc_coe_define_control_opcode,
    dnx_data_fc_coe_define_coe_vid_offset,
    dnx_data_fc_coe_define_coe_vid_mask,
    dnx_data_fc_coe_define_coe_vid_right_shift,
    dnx_data_fc_coe_define_coe_ptc_mask,
    dnx_data_fc_coe_define_coe_ptc_left_shift,

    
    _dnx_data_fc_coe_define_nof
} dnx_data_fc_coe_define_e;



uint32 dnx_data_fc_coe_nof_coe_cal_instances_get(
    int unit);


uint32 dnx_data_fc_coe_nof_supported_chan_ids_get(
    int unit);


uint32 dnx_data_fc_coe_nof_coe_vid_mask_width_get(
    int unit);


uint32 dnx_data_fc_coe_nof_coe_vid_right_shift_width_get(
    int unit);


uint32 dnx_data_fc_coe_nof_coe_ptc_mask_width_get(
    int unit);


uint32 dnx_data_fc_coe_nof_coe_ptc_left_shift_width_get(
    int unit);


uint32 dnx_data_fc_coe_max_coe_ticks_get(
    int unit);


uint32 dnx_data_fc_coe_fc_support_get(
    int unit);


uint32 dnx_data_fc_coe_map_value_size_in_bits_get(
    int unit);


uint32 dnx_data_fc_coe_calendar_pause_resolution_get(
    int unit);


uint32 dnx_data_fc_coe_data_offset_get(
    int unit);


uint32 dnx_data_fc_coe_ethertype_get(
    int unit);


uint32 dnx_data_fc_coe_control_opcode_get(
    int unit);


uint32 dnx_data_fc_coe_coe_vid_offset_get(
    int unit);


uint32 dnx_data_fc_coe_coe_vid_mask_get(
    int unit);


uint32 dnx_data_fc_coe_coe_vid_right_shift_get(
    int unit);


uint32 dnx_data_fc_coe_coe_ptc_mask_get(
    int unit);


uint32 dnx_data_fc_coe_coe_ptc_left_shift_get(
    int unit);



typedef enum
{
    dnx_data_fc_coe_table_calendar_mode,
    dnx_data_fc_coe_table_mac_address,
    dnx_data_fc_coe_table_calender_length,

    
    _dnx_data_fc_coe_table_nof
} dnx_data_fc_coe_table_e;



const dnx_data_fc_coe_calendar_mode_t * dnx_data_fc_coe_calendar_mode_get(
    int unit);


const dnx_data_fc_coe_mac_address_t * dnx_data_fc_coe_mac_address_get(
    int unit);


const dnx_data_fc_coe_calender_length_t * dnx_data_fc_coe_calender_length_get(
    int unit,
    int cal_id);



shr_error_e dnx_data_fc_coe_calendar_mode_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index);


shr_error_e dnx_data_fc_coe_mac_address_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index);


shr_error_e dnx_data_fc_coe_calender_length_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index);



const dnxc_data_table_info_t * dnx_data_fc_coe_calendar_mode_info_get(
    int unit);


const dnxc_data_table_info_t * dnx_data_fc_coe_mac_address_info_get(
    int unit);


const dnxc_data_table_info_t * dnx_data_fc_coe_calender_length_info_get(
    int unit);






int dnx_data_fc_oob_feature_get(
    int unit,
    dnx_data_fc_oob_feature_e feature);



typedef enum
{
    dnx_data_fc_oob_define_nof_oob_ids,

    
    _dnx_data_fc_oob_define_nof
} dnx_data_fc_oob_define_e;



uint32 dnx_data_fc_oob_nof_oob_ids_get(
    int unit);



typedef enum
{
    dnx_data_fc_oob_table_calender_length,
    dnx_data_fc_oob_table_calender_rep_count,
    dnx_data_fc_oob_table_tx_freq,
    dnx_data_fc_oob_table_port,
    dnx_data_fc_oob_table_indication_invert,

    
    _dnx_data_fc_oob_table_nof
} dnx_data_fc_oob_table_e;



const dnx_data_fc_oob_calender_length_t * dnx_data_fc_oob_calender_length_get(
    int unit,
    int oob_id);


const dnx_data_fc_oob_calender_rep_count_t * dnx_data_fc_oob_calender_rep_count_get(
    int unit,
    int oob_id);


const dnx_data_fc_oob_tx_freq_t * dnx_data_fc_oob_tx_freq_get(
    int unit,
    int oob_id);


const dnx_data_fc_oob_port_t * dnx_data_fc_oob_port_get(
    int unit,
    int oob_id);


const dnx_data_fc_oob_indication_invert_t * dnx_data_fc_oob_indication_invert_get(
    int unit,
    int oob_id);



shr_error_e dnx_data_fc_oob_calender_length_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index);


shr_error_e dnx_data_fc_oob_calender_rep_count_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index);


shr_error_e dnx_data_fc_oob_tx_freq_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index);


shr_error_e dnx_data_fc_oob_port_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index);


shr_error_e dnx_data_fc_oob_indication_invert_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index);



const dnxc_data_table_info_t * dnx_data_fc_oob_calender_length_info_get(
    int unit);


const dnxc_data_table_info_t * dnx_data_fc_oob_calender_rep_count_info_get(
    int unit);


const dnxc_data_table_info_t * dnx_data_fc_oob_tx_freq_info_get(
    int unit);


const dnxc_data_table_info_t * dnx_data_fc_oob_port_info_get(
    int unit);


const dnxc_data_table_info_t * dnx_data_fc_oob_indication_invert_info_get(
    int unit);






int dnx_data_fc_inband_feature_get(
    int unit,
    dnx_data_fc_inband_feature_e feature);



typedef enum
{
    dnx_data_fc_inband_define_nof_inband_intlkn_cal_instances,

    
    _dnx_data_fc_inband_define_nof
} dnx_data_fc_inband_define_e;



uint32 dnx_data_fc_inband_nof_inband_intlkn_cal_instances_get(
    int unit);



typedef enum
{
    dnx_data_fc_inband_table_calender_length,
    dnx_data_fc_inband_table_port,

    
    _dnx_data_fc_inband_table_nof
} dnx_data_fc_inband_table_e;



const dnx_data_fc_inband_calender_length_t * dnx_data_fc_inband_calender_length_get(
    int unit,
    int ilkn_id);


const dnx_data_fc_inband_port_t * dnx_data_fc_inband_port_get(
    int unit,
    int ilkn_id);



shr_error_e dnx_data_fc_inband_calender_length_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index);


shr_error_e dnx_data_fc_inband_port_entry_str_get(
    int unit,
    char *buffer,
    int key0,
    int key1,
    int value_index);



const dnxc_data_table_info_t * dnx_data_fc_inband_calender_length_info_get(
    int unit);


const dnxc_data_table_info_t * dnx_data_fc_inband_port_info_get(
    int unit);






int dnx_data_fc_pfc_deadlock_feature_get(
    int unit,
    dnx_data_fc_pfc_deadlock_feature_e feature);



typedef enum
{
    dnx_data_fc_pfc_deadlock_define_cdum_intr_id,
    dnx_data_fc_pfc_deadlock_define_cdu_intr_id,
    dnx_data_fc_pfc_deadlock_define_clu_intr_id,
    dnx_data_fc_pfc_deadlock_define_nbu_intr_id,
    dnx_data_fc_pfc_deadlock_define_nof_bits_in_port_num,

    
    _dnx_data_fc_pfc_deadlock_define_nof
} dnx_data_fc_pfc_deadlock_define_e;



uint32 dnx_data_fc_pfc_deadlock_cdum_intr_id_get(
    int unit);


uint32 dnx_data_fc_pfc_deadlock_cdu_intr_id_get(
    int unit);


uint32 dnx_data_fc_pfc_deadlock_clu_intr_id_get(
    int unit);


uint32 dnx_data_fc_pfc_deadlock_nbu_intr_id_get(
    int unit);


uint32 dnx_data_fc_pfc_deadlock_nof_bits_in_port_num_get(
    int unit);



typedef enum
{

    
    _dnx_data_fc_pfc_deadlock_table_nof
} dnx_data_fc_pfc_deadlock_table_e;






shr_error_e dnx_data_fc_init(
    int unit,
    dnxc_data_module_t *module_data);



#endif 


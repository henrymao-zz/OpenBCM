
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifndef _DNX_DATA_SWITCH_H_

#define _DNX_DATA_SWITCH_H_

#include <sal/limits.h>
#include <shared/utilex/utilex_framework.h>
#include <soc/property.h>
#include <soc/sand/shrextend/shrextend_debug.h>
#include <soc/dnxc/dnxc_data/dnxc_data_utils.h>
#include <soc/dnxc/dnxc_data/dnxc_data_mgmt.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_max_switch.h>



#ifndef BCM_DNX_SUPPORT
#error "This file is for use by DNX family only!"
#endif



shr_error_e dnx_data_if_switch_init(
    int unit);






typedef struct
{
    int client_logical_id;
} dnx_data_switch_load_balancing_lb_clients_t;


typedef struct
{
    int crc_hash_func;
} dnx_data_switch_load_balancing_lb_client_crc_t;


typedef struct
{
    uint32 field_enablers_mask;
} dnx_data_switch_load_balancing_lb_field_enablers_t;



typedef enum
{
    dnx_data_switch_load_balancing_fwd_hashing_method,
    dnx_data_switch_load_balancing_layer_record_mode_selection,
    dnx_data_switch_load_balancing_seed_config_per_pp_port,
    dnx_data_switch_load_balancing_paser_seed_update_supported,
    dnx_data_switch_load_balancing_ipv6_reparse_supported,
    dnx_data_switch_load_balancing_ipv6_unsymmetrical_hashing_supported,
    dnx_data_switch_load_balancing_cw_exclude_from_hash,

    
    _dnx_data_switch_load_balancing_feature_nof
} dnx_data_switch_load_balancing_feature_e;



typedef int(
    *dnx_data_switch_load_balancing_feature_get_f) (
    int unit,
    dnx_data_switch_load_balancing_feature_e feature);


typedef uint32(
    *dnx_data_switch_load_balancing_nof_lb_clients_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_nof_lb_crc_sel_tcam_entries_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_nof_crc_functions_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_initial_reserved_label_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_initial_reserved_label_force_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_initial_reserved_next_label_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_initial_reserved_next_label_valid_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_reserved_next_label_valid_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_num_valid_mpls_protocols_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_nof_layer_records_from_parser_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_nof_seeds_per_crc_function_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_hashing_selection_per_layer_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_mpls_split_stack_config_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_mpls_cam_next_label_valid_field_exists_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_padded_layers_crc_buffer_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_wide_hash_buffer_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_nof_lb_mpls_stack_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_nof_bits_mpls_protocol_identifier_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_seed_configuration_per_pp_port_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_swig_base_offline_simulation_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_load_balancing_pmf_simulation_support_get_f) (
    int unit);


typedef const dnx_data_switch_load_balancing_lb_clients_t *(
    *dnx_data_switch_load_balancing_lb_clients_get_f) (
    int unit,
    int client_hw_id);


typedef const dnx_data_switch_load_balancing_lb_client_crc_t *(
    *dnx_data_switch_load_balancing_lb_client_crc_get_f) (
    int unit,
    int client_hw_id);


typedef const dnx_data_switch_load_balancing_lb_field_enablers_t *(
    *dnx_data_switch_load_balancing_lb_field_enablers_get_f) (
    int unit,
    int header_id);



typedef struct
{
    
    dnx_data_switch_load_balancing_feature_get_f feature_get;
    
    dnx_data_switch_load_balancing_nof_lb_clients_get_f nof_lb_clients_get;
    
    dnx_data_switch_load_balancing_nof_lb_crc_sel_tcam_entries_get_f nof_lb_crc_sel_tcam_entries_get;
    
    dnx_data_switch_load_balancing_nof_crc_functions_get_f nof_crc_functions_get;
    
    dnx_data_switch_load_balancing_initial_reserved_label_get_f initial_reserved_label_get;
    
    dnx_data_switch_load_balancing_initial_reserved_label_force_get_f initial_reserved_label_force_get;
    
    dnx_data_switch_load_balancing_initial_reserved_next_label_get_f initial_reserved_next_label_get;
    
    dnx_data_switch_load_balancing_initial_reserved_next_label_valid_get_f initial_reserved_next_label_valid_get;
    
    dnx_data_switch_load_balancing_reserved_next_label_valid_get_f reserved_next_label_valid_get;
    
    dnx_data_switch_load_balancing_num_valid_mpls_protocols_get_f num_valid_mpls_protocols_get;
    
    dnx_data_switch_load_balancing_nof_layer_records_from_parser_get_f nof_layer_records_from_parser_get;
    
    dnx_data_switch_load_balancing_nof_seeds_per_crc_function_get_f nof_seeds_per_crc_function_get;
    
    dnx_data_switch_load_balancing_hashing_selection_per_layer_get_f hashing_selection_per_layer_get;
    
    dnx_data_switch_load_balancing_mpls_split_stack_config_get_f mpls_split_stack_config_get;
    
    dnx_data_switch_load_balancing_mpls_cam_next_label_valid_field_exists_get_f mpls_cam_next_label_valid_field_exists_get;
    
    dnx_data_switch_load_balancing_padded_layers_crc_buffer_get_f padded_layers_crc_buffer_get;
    
    dnx_data_switch_load_balancing_wide_hash_buffer_get_f wide_hash_buffer_get;
    
    dnx_data_switch_load_balancing_nof_lb_mpls_stack_get_f nof_lb_mpls_stack_get;
    
    dnx_data_switch_load_balancing_nof_bits_mpls_protocol_identifier_get_f nof_bits_mpls_protocol_identifier_get;
    
    dnx_data_switch_load_balancing_seed_configuration_per_pp_port_get_f seed_configuration_per_pp_port_get;
    
    dnx_data_switch_load_balancing_swig_base_offline_simulation_get_f swig_base_offline_simulation_get;
    
    dnx_data_switch_load_balancing_pmf_simulation_support_get_f pmf_simulation_support_get;
    
    dnx_data_switch_load_balancing_lb_clients_get_f lb_clients_get;
    
    dnxc_data_table_info_get_f lb_clients_info_get;
    
    dnx_data_switch_load_balancing_lb_client_crc_get_f lb_client_crc_get;
    
    dnxc_data_table_info_get_f lb_client_crc_info_get;
    
    dnx_data_switch_load_balancing_lb_field_enablers_get_f lb_field_enablers_get;
    
    dnxc_data_table_info_get_f lb_field_enablers_info_get;
} dnx_data_if_switch_load_balancing_t;







typedef enum
{

    
    _dnx_data_switch_load_balancing_sim_feature_nof
} dnx_data_switch_load_balancing_sim_feature_e;



typedef int(
    *dnx_data_switch_load_balancing_sim_feature_get_f) (
    int unit,
    dnx_data_switch_load_balancing_sim_feature_e feature);


typedef uint32(
    *dnx_data_switch_load_balancing_sim_device_enum_get_f) (
    int unit);



typedef struct
{
    
    dnx_data_switch_load_balancing_sim_feature_get_f feature_get;
    
    dnx_data_switch_load_balancing_sim_device_enum_get_f device_enum_get;
} dnx_data_if_switch_load_balancing_sim_t;







typedef enum
{
    dnx_data_switch_svtag_egress_svtag_enable_by_context,
    dnx_data_switch_svtag_egress_svtag_legacy_api_support,
    dnx_data_switch_svtag_enable_by_defualt,

    
    _dnx_data_switch_svtag_feature_nof
} dnx_data_switch_svtag_feature_e;



typedef int(
    *dnx_data_switch_svtag_feature_get_f) (
    int unit,
    dnx_data_switch_svtag_feature_e feature);


typedef uint32(
    *dnx_data_switch_svtag_supported_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_svtag_svtag_label_size_bits_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_svtag_egress_svtag_offset_addr_size_bits_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_svtag_egress_svtag_offset_addr_position_bits_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_svtag_egress_svtag_signature_size_bits_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_svtag_egress_svtag_signature_position_bits_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_svtag_egress_svtag_sci_size_bits_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_svtag_egress_svtag_sci_position_bits_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_svtag_egress_svtag_pkt_type_size_bits_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_svtag_egress_svtag_pkt_type_position_bits_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_svtag_egress_svtag_ipv6_indication_position_bits_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_svtag_egress_svtag_hw_field_position_bits_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_svtag_egress_svtag_accumulation_indication_hw_field_position_bits_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_svtag_UDP_dedicated_port_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_svtag_ingress_svtag_position_bytes_get_f) (
    int unit);


typedef uint32(
    *dnx_data_switch_svtag_svtag_physical_db_get_f) (
    int unit);



typedef struct
{
    
    dnx_data_switch_svtag_feature_get_f feature_get;
    
    dnx_data_switch_svtag_supported_get_f supported_get;
    
    dnx_data_switch_svtag_svtag_label_size_bits_get_f svtag_label_size_bits_get;
    
    dnx_data_switch_svtag_egress_svtag_offset_addr_size_bits_get_f egress_svtag_offset_addr_size_bits_get;
    
    dnx_data_switch_svtag_egress_svtag_offset_addr_position_bits_get_f egress_svtag_offset_addr_position_bits_get;
    
    dnx_data_switch_svtag_egress_svtag_signature_size_bits_get_f egress_svtag_signature_size_bits_get;
    
    dnx_data_switch_svtag_egress_svtag_signature_position_bits_get_f egress_svtag_signature_position_bits_get;
    
    dnx_data_switch_svtag_egress_svtag_sci_size_bits_get_f egress_svtag_sci_size_bits_get;
    
    dnx_data_switch_svtag_egress_svtag_sci_position_bits_get_f egress_svtag_sci_position_bits_get;
    
    dnx_data_switch_svtag_egress_svtag_pkt_type_size_bits_get_f egress_svtag_pkt_type_size_bits_get;
    
    dnx_data_switch_svtag_egress_svtag_pkt_type_position_bits_get_f egress_svtag_pkt_type_position_bits_get;
    
    dnx_data_switch_svtag_egress_svtag_ipv6_indication_position_bits_get_f egress_svtag_ipv6_indication_position_bits_get;
    
    dnx_data_switch_svtag_egress_svtag_hw_field_position_bits_get_f egress_svtag_hw_field_position_bits_get;
    
    dnx_data_switch_svtag_egress_svtag_accumulation_indication_hw_field_position_bits_get_f egress_svtag_accumulation_indication_hw_field_position_bits_get;
    
    dnx_data_switch_svtag_UDP_dedicated_port_get_f UDP_dedicated_port_get;
    
    dnx_data_switch_svtag_ingress_svtag_position_bytes_get_f ingress_svtag_position_bytes_get;
    
    dnx_data_switch_svtag_svtag_physical_db_get_f svtag_physical_db_get;
} dnx_data_if_switch_svtag_t;







typedef enum
{
    dnx_data_switch_feature_mpls_labels_included_in_hash,
    dnx_data_switch_feature_excluded_header_bits_from_hash,
    dnx_data_switch_feature_silent_dummy_lif_lookup,
    dnx_data_switch_feature_fwd1_default_result_support,

    
    _dnx_data_switch_feature_feature_nof
} dnx_data_switch_feature_feature_e;



typedef int(
    *dnx_data_switch_feature_feature_get_f) (
    int unit,
    dnx_data_switch_feature_feature_e feature);



typedef struct
{
    
    dnx_data_switch_feature_feature_get_f feature_get;
} dnx_data_if_switch_feature_t;







typedef enum
{
    dnx_data_switch_wide_data_ext_key_by_global_ac_lif,
    dnx_data_switch_wide_data_ext_key_by_global_eth_rif,
    dnx_data_switch_wide_data_ext_key_by_data,

    
    _dnx_data_switch_wide_data_feature_nof
} dnx_data_switch_wide_data_feature_e;



typedef int(
    *dnx_data_switch_wide_data_feature_get_f) (
    int unit,
    dnx_data_switch_wide_data_feature_e feature);



typedef struct
{
    
    dnx_data_switch_wide_data_feature_get_f feature_get;
} dnx_data_if_switch_wide_data_t;





typedef struct
{
    
    dnx_data_if_switch_load_balancing_t load_balancing;
    
    dnx_data_if_switch_load_balancing_sim_t load_balancing_sim;
    
    dnx_data_if_switch_svtag_t svtag;
    
    dnx_data_if_switch_feature_t feature;
    
    dnx_data_if_switch_wide_data_t wide_data;
} dnx_data_if_switch_t;




extern dnx_data_if_switch_t dnx_data_switch;


#endif 


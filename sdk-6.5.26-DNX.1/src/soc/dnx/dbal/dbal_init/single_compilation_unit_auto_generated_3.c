
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 * 
 */
#ifdef BSL_LOG_MODULE
#  error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_SOCDNX_DBALDNX

#include <src/soc/dnx/dbal/dbal_internal.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data.h>

#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_cb_tables_hard_logic_tm_hl_tm_tsn_definition.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_cb_tables_sw_state_pp_l3_sw_pp_l3_vrrp.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_cb_tables_sw_state_pp_lif_in_lif_profile.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_cb_tables_sw_state_pp_oam_sw_pp_oam.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_cb_tables_sw_state_pp_sw_pp_algo_gpm.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_cb_tables_sw_state_pp_tunnel_tunnel.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_cb_tables_sw_state_pp_vlan_sw_pp_vlan_port.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_auto_generated.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_auto_generated_profile_field_types.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_auto_generated_standard_1.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_auto_generated_standard_1_standard_1_arr_field_types.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_auto_generated_standard_1_standard_1_arr_formats_enum_encoding.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_auto_generated_standard_1_standard_1_egress_ctx_id_field_types_definition.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_auto_generated_standard_1_standard_1_fec_field_types_definition.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_auto_generated_standard_1_standard_1_ingress_ctx_id_field_types_definition.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_auto_generated_standard_1_standard_1_kbp_field_types_definition.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_auto_generated_standard_1_standard_1_profile_field_types.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_auto_generated_standard_1_standard_1_virtual_tcam_field_types.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_cosq_field_types_definition.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_example_field_types.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_fabric_field_types_definition.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_field_types_definition.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_field_types_encoding.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_kbp_field_types_definition.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_kleap_field_types_definition.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_oam_bfd_field_types_definition.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_oamp_field_types_definition.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_pmf_field_types_definition.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_pmf_qualifiers_and_actions.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_field_types_qos_fields_types_definition.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_hw_entity_groups.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_hw_entity_groups_hw_entity_groups.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_shared_field_types.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_shared_field_types_basic_field_types_definition.c>
#include <src/soc/dnx/dbal/dbal_init/auto_generated/dbal_init_shared_field_types_packet_field_types.c>


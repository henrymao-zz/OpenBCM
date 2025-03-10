
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_INITSEQDNX

#include <soc/sand/shrextend/shrextend_debug.h>
#include <sal/compiler.h>
#include <soc/types.h>
#include <soc/memory.h>
#include <soc/feature.h>
#include <soc/register.h>
#include <soc/dnx/mdb.h>
#include <bcm/switch.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_mdb.h>
#include <soc/dnx/dbal/dbal.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_headers.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_tdm.h>
#include <bcm_int/dnx/tdm/tdm.h>
#include "bcm_int/dnx/init/init_pp.h"
#include <src/bcm/dnx/init/init_pp_common.h>
#include <soc/dnx/dbal/auto_generated/dbal_defines_fields.h>
#include <bcm/types.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_dev_init.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_device.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_switch.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_port.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_port_pp.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_elk.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_srv6.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_ingress_cs.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_l3.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_lif.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_pp.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_mpls.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_nif.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_fabric.h>
#include <bcm_int/dnx/vlan/vlan.h>
#include <bcm_int/dnx/field/field_context.h>
#include <bcm_int/dnx/init/init.h>
#include <bcm_int/dnx/rx/rx_trap.h>
#include <bcm_int/dnx/vsi/vsi.h>
#include <soc/sand/sand_aux_access.h>
#include <src/bcm/dnx/init/auto_generated/init_pp_dnx2_aod_tables.h>

#include <soc/dnx/swstate/auto_generated/access/dnx_ire_packet_generator_access.h>
#include <soc/dnx/utils/dnx_pp_programmability_utils.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_vlan.h>
#include <soc/dnx/swstate/auto_generated/access/mdb_access.h>
#include <src/bcm/dnx/multicast/multicast_pp.h>
#include <sal/core/boot.h>
#include <bcm_int/dnx/cmn/dnxcmn.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_graphical.h>
#include <bcm_int/dnx/switch/switch_em_false_hit.h>
#include <bcm_int/dnx/field/field_init.h>
#include <bcm_int/dnx/lif/out_lif_headers_profile.h>
#include <bcm_int/dnx/port/port.h>
#include <bcm_int/dnx/fabric/fabric.h>

#define LAYER_QUALIFIER_SRV6_SEGMENT_LEFT_IS_ZERO_OFFSET (0)
#define LAYER_QUALIFIER_SRV6_SEGMENT_LEFT_IS_ONE_OFFSET (1)
#define LAYER_QUALIFIER_SRV6_SINGLE_PASS_TERMINATION_OFFSET (2)

#define LAYER_QUALIFIER_SRV6_SEGMENT_LEFT_IS_ZERO_SET(qualifier_p, segment_left_is_zero) (utilex_bitstream_set(qualifier_p, LAYER_QUALIFIER_SRV6_SEGMENT_LEFT_IS_ZERO_OFFSET, segment_left_is_zero))
#define LAYER_QUALIFIER_SRV6_SEGMENT_LEFT_IS_ONE_SET(qualifier_p, segment_left_is_one) (utilex_bitstream_set(qualifier_p, LAYER_QUALIFIER_SRV6_SEGMENT_LEFT_IS_ONE_OFFSET, segment_left_is_one))
#define LAYER_QUALIFIER_SRV6_SINGLE_PASS_TERMINATION_SET(qualifier_p, single_pass_termination) (utilex_bitstream_set(qualifier_p, LAYER_QUALIFIER_SRV6_SINGLE_PASS_TERMINATION_OFFSET, single_pass_termination))

#define LAYER_QUALIFIER_IPV6_1ST_ADD_HEADER_EXISTS_OFFSET (1)
#define LAYER_QUALIFIER_IPV6_1ST_ADD_HEADER_EXISTS_SIZE (1)
#define LAYER_QUALIFIER_IPV6_1ST_ADD_HEADER_OFFSET (2)
#define LAYER_QUALIFIER_IPV6_1ST_ADD_HEADER_SIZE (5)
#define LAYER_QUALIFIER_IPV6_2ND_ADD_HEADER_SRV6_SINGLE_PASS_TERM_OFFSET (7)
#define LAYER_QUALIFIER_IPV6_2ND_ADD_HEADER_SRV6_SINGLE_PASS_TERM_SIZE (1)

#define LAYER_QUALIFIER_IPV6_1ST_ADD_HEADER_EXISTS_SET(qualifier_p, _first_add_header_exists_) \
    SHR_IF_ERR_EXIT(utilex_bitstream_set_field(qualifier_p, \
                                LAYER_QUALIFIER_IPV6_1ST_ADD_HEADER_EXISTS_OFFSET, \
                                LAYER_QUALIFIER_IPV6_1ST_ADD_HEADER_EXISTS_SIZE, \
                                _first_add_header_exists_))

#define LAYER_QUALIFIER_IPV6_1ST_ADD_HEADER_SET(qualifier_p, _first_add_header_) \
        SHR_IF_ERR_EXIT(utilex_bitstream_set_field(qualifier_p, \
                                LAYER_QUALIFIER_IPV6_1ST_ADD_HEADER_OFFSET, \
                                LAYER_QUALIFIER_IPV6_1ST_ADD_HEADER_SIZE, \
                                _first_add_header_))

#define LAYER_QUALIFIER_IPV6_2ND_ADD_HEADER_SRV6_SINGLE_PASS_TERM_SET(qualifier_p, _srv6_sl0_single_pass_) \
        SHR_IF_ERR_EXIT(utilex_bitstream_set_field(qualifier_p, \
                                LAYER_QUALIFIER_IPV6_2ND_ADD_HEADER_SRV6_SINGLE_PASS_TERM_OFFSET, \
                                LAYER_QUALIFIER_IPV6_2ND_ADD_HEADER_SRV6_SINGLE_PASS_TERM_SIZE, \
                                _srv6_sl0_single_pass_))

#define LIF_EXTENSION_TYPE_NONE                 DBAL_ENUM_FVAL_LIF_EXTENSION_TYPE_NONE

#define LIF_EXTENSION_TYPE_1XOUT_LIF            DBAL_ENUM_FVAL_LIF_EXTENSION_TYPE_1xOUT_LIF

#define LIF_EXTENSION_TYPE_2XOUT_LIF            DBAL_ENUM_FVAL_LIF_EXTENSION_TYPE_2xOUT_LIF

#define LIF_EXTENSION_TYPE_3XOUT_LIF            DBAL_ENUM_FVAL_LIF_EXTENSION_TYPE_3xOUT_LIF

#define LIF_EXTENSION_TYPE_INLIF_PROFILE        DBAL_ENUM_FVAL_LIF_EXTENSION_TYPE_IN_LIF_PLUS_IN_LIF_PROFILE

#define LIF_EXTENSION_SIZE_1XOUT_LIF            3

#define LIF_EXTENSION_SIZE_IN_LIF_PROFILE       4

#define FWD_PLUS_1_REMARK_INGRESS_DISABLE       DBAL_ENUM_FVAL_QOS_FORWARD_P1_REMARK_PROFILE_INGRESS_REMARK_PROFILE_0

#define FWD_PLUS_1_REMARK_INGRESS_ENABLE        DBAL_ENUM_FVAL_QOS_FORWARD_P1_REMARK_PROFILE_INGRESS_REMARK_PROFILE_1

#define J2_PP_GENERAL                           DBAL_ENUM_FVAL_SYS_HDR_GENERATION_PROFILE_GENERAL

#define J2_OAM                                  DBAL_ENUM_FVAL_SYS_HDR_GENERATION_PROFILE_JR2_OAM

#define J2_TM                                   DBAL_ENUM_FVAL_SYS_HDR_GENERATION_PROFILE_JR2_TM

#define J_OAM                                   DBAL_ENUM_FVAL_SYS_HDR_GENERATION_PROFILE_J_OAM

#define J_TM                                    DBAL_ENUM_FVAL_SYS_HDR_GENERATION_PROFILE_J_TM

#define TDM                                     DBAL_ENUM_FVAL_SYS_HDR_GENERATION_PROFILE_TDM

#define OTMH                                    DBAL_ENUM_FVAL_SYS_HDR_GENERATION_PROFILE_OTMH

#define UDH                                     DBAL_ENUM_FVAL_SYS_HDR_GENERATION_PROFILE_UDH

#define INLIF_DESCISION_0_FODO                  DBAL_ENUM_FVAL_INLIF_DECISION_0_FORWARDING_DOMAIN

#define INLIF_DESCISION_0_INLIF                 DBAL_ENUM_FVAL_INLIF_DECISION_0_INLIF

#define INLIF_DESCISION_1_INLIF                 DBAL_ENUM_FVAL_INLIF_DECISION_1_INLIF

#define INLIF_DESCISION_1_INLIF_EXTENSION       DBAL_ENUM_FVAL_INLIF_DECISION_1_INLIF_EXTENSION

#define SYSTEM_HEADERS_MODE_JERICHO_MODE        DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO_MODE

#define SYSTEM_HEADERS_MODE_JERICHO2_MODE       DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO2_MODE

#define ERPP_FILTER_PER_FWD_CONTEXT_SIZE        11

#define FTMH_LB_KEY_EXT_SIZE 3

#define STACKING_EXT_SIZE 2

#define SYSTEM_SCOPE_LIF_PROFILE_JR_MODE_2B_BOTH_ENABLED 2
#define SYSTEM_SCOPE_LIF_PROFILE_JR_MODE_2B_ENABLED 3
#define SYSTEM_SCOPE_LIF_PROFILE_JR_MODE_1B_ENABLED 1
#define SYSTEM_SCOPE_ENABLED_AND_ORIENTATION_ENABLED 3
#define DEVICE_SCOPE_ENABLED_AND_ORIENTATION_ENABLED 2

#define ERPP_COMPENSATE_CRC_SIZE 2

#define FORCE_BUBBLE_SYNC_COUNTER(unit) dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_ippe_sync_counter)

typedef struct
{

    int index;

    int outlif_0_decision;
    int outlif_1_decision;
    int outlif_2_decision;
    int outlif_3_decision;
} outlif_decision_t;

typedef struct
{

    dbal_enum_value_field_lif_extension_type_e lif_extension_type;

    int outlif_extension_1;
    int outlif_extension_2;
    int outlif_extension_3;
    int inlif_extension_1;
    int inlif_extension_1_profile;
} outlif_extension_config_t;

typedef struct
{

    dbal_enum_value_field_system_headers_mode_e system_headers_mode;
    int is_mc_forward_code;

    dbal_enum_value_field_inlif_decision_0_e inlif_decision_0;
    dbal_enum_value_field_inlif_decision_1_e inlif_decision_1;
} inlif_decision_config_t;

typedef struct
{

    int system_header_profile;

    int bytes_to_add;
} system_header_profile_t;

typedef struct
{

    dbal_enum_value_field_layer_types_e layer_type;

    dbal_enum_value_field_egress_1st_parser_parser_context_e parser_context;
} layer_type_to_mpls_upper_layer_protocol_t;

typedef struct
{
    dbal_enum_value_field_irpp_2nd_parser_parser_context_e parser_ctx;
    dbal_enum_value_field_layer_types_e layer_type_speculation;
    dbal_enum_value_field_layer_types_e layer_type_force_incorrect;
} per_2nd_stage_parsing_ctx_t;

typedef struct
{

    uint32 forwarding_additional_info;

    uint8 ipvx_fallback_to_bridge_enable;
    uint8 bum_traffic_enable;
    uint8 fwd_plus_1_remark_ingress_profile;
} forwarding_additional_info_config_t;

typedef struct
{

    dbal_enum_value_field_layer_types_e fwd_layer_type;
    int fwd_layer_qual_lsb;

    dbal_enum_value_field_jr_fwd_code_e jr_fwd_code;
} jr_mode_fwd_code_mapping_config_t;

typedef struct
{

    dbal_enum_value_field_jr_fwd_code_e jr_fwd_code;
    int is_mc;
    int outlif_is_rif;

    dbal_enum_value_field_jr_vsi_src_e jr_vsi_src;
} jr_mode_vsi_src_mapping_config_t;

typedef struct
{

    dbal_enum_value_field_jr_fwd_code_e jr_fwd_code;
    int inlif_eq_zero;
    int fwd_layer_idx;

    dbal_enum_value_field_fhei_size_e fhei_size;
} jr_mode_fhei_size_mapping_config_t;

typedef struct
{

    dbal_enum_value_field_current_protocol_type_e current_protocol_type;
    dbal_enum_value_field_etpp_next_protocol_namespace_e current_protocol_namespace;

    int current_next_protocol;
} current_next_protocol_config_table_t;

static const outlif_decision_t outlif_decision_map_jr2_mode[] = {

    {0, 1, 2, 2, 2},
    {1, 1, 3, 2, 2},
    {2, 0, 0, 0, 0},
    {3, 1, 3, 3, 2},
    {4, 0, 0, 0, 0},
    {5, 0, 0, 0, 0},
    {6, 0, 0, 0, 0},
    {7, 1, 3, 3, 3}
};

static const outlif_decision_t outlif_decision_map_jer_mode[] = {

    {0, 1, 3, 3, 3},
    {1, 1, 1, 1, 1},
    {4, 1, 3, 3, 3},
    {5, 1, 1, 1, 1},
    {6, 0, 0, 1, 1},
    {7, 0, 0, 0, 0}
};

static const outlif_extension_config_t outlif_extension_map[] = {

    {LIF_EXTENSION_TYPE_NONE, 0, 0, 0, 0, 0},
    {LIF_EXTENSION_TYPE_1XOUT_LIF, 1622, 0, 0, 0, 0},
    {LIF_EXTENSION_TYPE_2XOUT_LIF, 918, 1622, 0, 0, 0},
    {LIF_EXTENSION_TYPE_3XOUT_LIF, 214, 918, 1622, 0, 0},
    {LIF_EXTENSION_TYPE_INLIF_PROFILE, 0, 0, 0, 1366, 1064}
};

static const inlif_decision_config_t inlif_decision_config_map_jer_mode[] = {

    {SYSTEM_HEADERS_MODE_JERICHO_MODE, 1, INLIF_DESCISION_0_FODO, INLIF_DESCISION_1_INLIF},
    {SYSTEM_HEADERS_MODE_JERICHO_MODE, 0, INLIF_DESCISION_0_INLIF, INLIF_DESCISION_1_INLIF_EXTENSION}
};

static const inlif_decision_config_t inlif_decision_config_map_jr2_mode[] = {

    {SYSTEM_HEADERS_MODE_JERICHO2_MODE, 1, INLIF_DESCISION_0_INLIF, INLIF_DESCISION_1_INLIF_EXTENSION},
    {SYSTEM_HEADERS_MODE_JERICHO2_MODE, 0, INLIF_DESCISION_0_INLIF, INLIF_DESCISION_1_INLIF_EXTENSION}
};

static const current_next_protocol_config_table_t current_next_protocol_config_map[] = {

    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV4_UC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_ETHERTYPE,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV4_OVER_ETHERNET},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV4_MC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_ETHERTYPE,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV4_OVER_ETHERNET},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV6_UC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_ETHERTYPE,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV6_OVER_ETHERNET},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV6_MC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_ETHERTYPE,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV6_OVER_ETHERNET},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_SRV6_ENDPOINT, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_ETHERTYPE,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV6_OVER_ETHERNET},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_MPLS, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_ETHERTYPE,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_MPLS_OVER_ETHERNET},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_FCOE, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_ETHERTYPE,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_FCOE_OVER_ETHERNET},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_PPPOE_SESSION, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_ETHERTYPE,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_PPPOE_OVER_ETHERNET},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_ERSPANV2, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_ETHERTYPE,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_ERSPAN_OVER_GRE},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_ERSPANV3, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_ETHERTYPE,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_ERSPANV3_OVER_GRE},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_ETHERNET, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_ETHERTYPE,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_ETHERNET_OVER_ETHERNET},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV4_UC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_IP_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV4},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV4_MC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_IP_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV4},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV6_UC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_IP_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV6_OVER_IP},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV6_MC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_IP_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV6_OVER_IP},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_ETHERNET, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_IP_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_ETHERNET_OVER_IP},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_MPLS, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_IP_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_MPLS_OVER_IP},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_UDP, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_IP_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_UDP},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_GRE, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_IP_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_GRE_OVER_IP},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_ETHERNET, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_MPLS_BOS,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_MPLS},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV4_UC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_MPLS_BOS,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_MPLS},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV4_MC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_MPLS_BOS,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_MPLS},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV6_UC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_MPLS_BOS,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_MPLS},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_SRV6_ENDPOINT, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_MPLS_BOS,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_MPLS},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV6_MC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_MPLS_BOS,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_MPLS},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_MPLS, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_MPLS_BOS,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_MPLS_BOS},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_BIER_NON_MPLS, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_MPLS_BOS,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_MPLS},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_TDM_BS, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_MPLS_BOS,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_MPLS},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_VXLAN_GPE, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_MPLS_BOS,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_MPLS},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_MPLS, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_UDP_DESTINATION_PORT,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_MPLS_OVER_UDP},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV4_UC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_UDP_DESTINATION_PORT,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV4_OVER_UDP},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV4_MC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_UDP_DESTINATION_PORT,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV4_OVER_UDP},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV6_UC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_UDP_DESTINATION_PORT,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV6_OVER_UDP},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV6_MC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_UDP_DESTINATION_PORT,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV6_OVER_UDP},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_SRV6_ENDPOINT,
     DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_UDP_DESTINATION_PORT,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV6_OVER_UDP},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_VXLAN, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_UDP_DESTINATION_PORT,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_VXLAN_OVER_UDP},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_VXLAN_GPE, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_UDP_DESTINATION_PORT,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_VXLAN_GPE_OVER_UDP},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_GENEVE, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_UDP_DESTINATION_PORT,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_GENEVE_OVER_UDP},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_GRE, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_UDP_DESTINATION_PORT,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_GRE_OVER_UDP},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_SRV6_ENDPOINT, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_IP_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV6_OVER_IP},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_SRV6_SRH_ONLY, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_IP_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_SRV6_OVER_IPV6},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_ETHERNET, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_VXLAN_GPE_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_ETHERNET},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV4_UC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_VXLAN_GPE_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_MPLS},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV4_MC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_VXLAN_GPE_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_MPLS},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV6_UC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_VXLAN_GPE_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV6},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV6_MC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_VXLAN_GPE_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV6},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_SRV6_ENDPOINT,
     DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_VXLAN_GPE_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV6},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_MPLS, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_VXLAN_GPE_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_MPLS_OVER_VXLAN},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV4_UC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_PPP_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV4_OVER_PPPOE},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV4_MC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_PPP_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV4_OVER_PPPOE},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV6_UC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_PPP_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV6_OVER_PPPOE},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV6_MC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_PPP_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV6_OVER_PPPOE},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_SRV6_ENDPOINT, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_PPP_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_IPV6_OVER_PPPOE},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_GTP, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_UDP_DESTINATION_PORT,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_GTPU_OVER_UDP},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_PTP, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_ETHERTYPE,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_PTP_OVER_ETHERNET},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_BIER_NON_MPLS, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_ETHERTYPE,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_SET_2_BIER_NON_MPLS_OVER_ETHERNET},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_BIER_MPLS, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_ETHERTYPE,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_SET_2_BIER_MPLS_OVER_RCH},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_MPLS, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_BIER_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_SET_2_MPLS_OVER_BIER},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV4_UC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_BIER_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_SET_2_IPV4_OVER_BIER},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV4_MC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_BIER_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_SET_2_IPV4_OVER_BIER},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV6_UC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_BIER_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_SET_2_IPV6_OVER_BIER},
    {DBAL_ENUM_FVAL_CURRENT_PROTOCOL_TYPE_IPV6_MC, DBAL_ENUM_FVAL_ETPP_NEXT_PROTOCOL_NAMESPACE_BIER_NEXT_PROTOCOL,
     DBAL_DEFINE_CURRENT_NEXT_PROTOCOL_SET_2_IPV6_OVER_BIER}
};

static const system_header_profile_t system_header_profile_map[] = {

    {J2_PP_GENERAL, 40},
    {J2_OAM, 35},
    {J2_TM, 20},
    {J_OAM, 30},
    {J_TM, 25},
    {TDM, 18},
    {OTMH, 17},
    {UDH, 0}
};

static const per_2nd_stage_parsing_ctx_t per_2nd_stage_parsing_ctx[] = {

    {DBAL_ENUM_FVAL_IRPP_2ND_PARSER_PARSER_CONTEXT_NONE, DBAL_ENUM_FVAL_LAYER_TYPES_INITIALIZATION,
     DBAL_ENUM_FVAL_LAYER_TYPES_INITIALIZATION},
    {DBAL_ENUM_FVAL_IRPP_2ND_PARSER_PARSER_CONTEXT_ETH_B1, DBAL_ENUM_FVAL_LAYER_TYPES_ETHERNET,
     DBAL_ENUM_FVAL_LAYER_TYPES_ETHERNET},
    {DBAL_ENUM_FVAL_IRPP_2ND_PARSER_PARSER_CONTEXT_IPVX_DEMUX_B1, DBAL_ENUM_FVAL_LAYER_TYPES_IPV4,
     DBAL_ENUM_FVAL_LAYER_TYPES_INITIALIZATION},
    {DBAL_ENUM_FVAL_IRPP_2ND_PARSER_PARSER_CONTEXT_MPLS_SPECULATIVEOAMB1, DBAL_ENUM_FVAL_LAYER_TYPES_MPLS,
     DBAL_ENUM_FVAL_LAYER_TYPES_MPLS},
    {DBAL_ENUM_FVAL_IRPP_2ND_PARSER_PARSER_CONTEXT_IPV4_NOETHB2, DBAL_ENUM_FVAL_LAYER_TYPES_IPV4,
     DBAL_ENUM_FVAL_LAYER_TYPES_INITIALIZATION},
    {DBAL_ENUM_FVAL_IRPP_2ND_PARSER_PARSER_CONTEXT_IPV6_NOETHB2, DBAL_ENUM_FVAL_LAYER_TYPES_IPV6,
     DBAL_ENUM_FVAL_LAYER_TYPES_INITIALIZATION},
    {DBAL_ENUM_FVAL_IRPP_2ND_PARSER_PARSER_CONTEXT_BIER, DBAL_ENUM_FVAL_LAYER_TYPES_IN_BIER_BASE_EG_BIER_MPLS,
     DBAL_ENUM_FVAL_LAYER_TYPES_IN_BIER_BASE_EG_BIER_MPLS},
    {DBAL_ENUM_FVAL_IRPP_2ND_PARSER_PARSER_CONTEXT_BIER_NON_MPLS, DBAL_ENUM_FVAL_LAYER_TYPES_BIER_NON_MPLS,
     DBAL_ENUM_FVAL_LAYER_TYPES_BIER_NON_MPLS},
    {DBAL_ENUM_FVAL_IRPP_2ND_PARSER_PARSER_CONTEXT_TCP_B1, DBAL_ENUM_FVAL_LAYER_TYPES_TCP,
     DBAL_ENUM_FVAL_LAYER_TYPES_TCP},
    {DBAL_ENUM_FVAL_IRPP_2ND_PARSER_PARSER_CONTEXT_UDP_B1, DBAL_ENUM_FVAL_LAYER_TYPES_UDP,
     DBAL_ENUM_FVAL_LAYER_TYPES_UDP},
    {DBAL_ENUM_FVAL_IRPP_2ND_PARSER_PARSER_CONTEXT_NOP, DBAL_ENUM_FVAL_LAYER_TYPES_INITIALIZATION,
     DBAL_ENUM_FVAL_LAYER_TYPES_INITIALIZATION}
};

static const layer_type_to_mpls_upper_layer_protocol_t layer_type_to_mpls_upper_layer_protocol[] = {

    {DBAL_ENUM_FVAL_LAYER_TYPES_INITIALIZATION, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_MPLS_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_ETHERNET, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_ETH_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_IPV4, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_IPV4_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_IPV6, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_IPV6_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_MPLS, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_MPLS_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_ARP, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_MPLS_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_FCOE, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_MPLS_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_TCP, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_MPLS_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_UDP, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_MPLS_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_BFD_SINGLE_HOP, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_MPLS_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_BFD_MULTI_HOP, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_MPLS_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_PTP, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_MPLS_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_Y_1731, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_MPLS_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_ICMP, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_MPLS_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_BIER_NON_MPLS, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_BIER_NON_MPLS_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_IN_BIER_BASE_EG_BIER_MPLS,
     DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_BIER_MPLS_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_RCH, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_MPLS_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_PPPOE, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_MPLS_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_SRV6_ENDPOINT, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_MPLS_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_IGMP, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_MPLS_A1},
    {DBAL_ENUM_FVAL_LAYER_TYPES_ITMH, DBAL_ENUM_FVAL_EGRESS_1ST_PARSER_PARSER_CONTEXT_MPLS_A1}
};

static const forwarding_additional_info_config_t forwarding_additional_info_config_map[] = {

    {0, 0, 0, FWD_PLUS_1_REMARK_INGRESS_DISABLE},
    {1, 0, 1, FWD_PLUS_1_REMARK_INGRESS_DISABLE},
    {2, 1, 0, FWD_PLUS_1_REMARK_INGRESS_ENABLE},
    {3, 1, 1, FWD_PLUS_1_REMARK_INGRESS_ENABLE},
    {4, 0, 0, FWD_PLUS_1_REMARK_INGRESS_DISABLE},
    {5, 0, 1, FWD_PLUS_1_REMARK_INGRESS_DISABLE},
    {6, 1, 0, FWD_PLUS_1_REMARK_INGRESS_ENABLE},
    {7, 1, 1, FWD_PLUS_1_REMARK_INGRESS_ENABLE},
    {8, 0, 0, FWD_PLUS_1_REMARK_INGRESS_DISABLE},
    {9, 0, 1, FWD_PLUS_1_REMARK_INGRESS_DISABLE},
    {10, 1, 0, FWD_PLUS_1_REMARK_INGRESS_ENABLE},
    {11, 1, 1, FWD_PLUS_1_REMARK_INGRESS_ENABLE},
    {12, 0, 0, FWD_PLUS_1_REMARK_INGRESS_DISABLE},
    {13, 0, 1, FWD_PLUS_1_REMARK_INGRESS_DISABLE},
    {14, 1, 0, FWD_PLUS_1_REMARK_INGRESS_ENABLE},
    {15, 1, 1, FWD_PLUS_1_REMARK_INGRESS_ENABLE}
};

static const jr_mode_fwd_code_mapping_config_t jr_mode_fwd_code_map[] = {

    {DBAL_ENUM_FVAL_LAYER_TYPES_ETHERNET, 0, DBAL_ENUM_FVAL_JR_FWD_CODE_BRIDGE},

    {DBAL_ENUM_FVAL_LAYER_TYPES_ETHERNET, 1, DBAL_ENUM_FVAL_JR_FWD_CODE_BRIDGE},

    {DBAL_ENUM_FVAL_LAYER_TYPES_IPV4, 0, DBAL_ENUM_FVAL_JR_FWD_CODE_IPV4_UC},

    {DBAL_ENUM_FVAL_LAYER_TYPES_IPV4, 1, DBAL_ENUM_FVAL_JR_FWD_CODE_IPV4_MC},

    {DBAL_ENUM_FVAL_LAYER_TYPES_IPV6, 0, DBAL_ENUM_FVAL_JR_FWD_CODE_IPV6_UC},

    {DBAL_ENUM_FVAL_LAYER_TYPES_IPV6, 1, DBAL_ENUM_FVAL_JR_FWD_CODE_IPV6_MC},

    {DBAL_ENUM_FVAL_LAYER_TYPES_MPLS_UNTERM, 0, DBAL_ENUM_FVAL_JR_FWD_CODE_MPLS},

    {DBAL_ENUM_FVAL_LAYER_TYPES_MPLS_UNTERM, 1, DBAL_ENUM_FVAL_JR_FWD_CODE_MPLS},

    {DBAL_ENUM_FVAL_LAYER_TYPES_ITMH, 0, DBAL_ENUM_FVAL_JR_FWD_CODE_TM},

    {DBAL_ENUM_FVAL_LAYER_TYPES_ITMH, 1, DBAL_ENUM_FVAL_JR_FWD_CODE_TM}

};

static const jr_mode_vsi_src_mapping_config_t jr_mode_vsi_src_map[] = {

    {DBAL_ENUM_FVAL_JR_FWD_CODE_IPV4_UC, 0, 1, DBAL_ENUM_FVAL_JR_VSI_SRC_OUT_LIF},

    {DBAL_ENUM_FVAL_JR_FWD_CODE_IPV6_UC, 0, 1, DBAL_ENUM_FVAL_JR_VSI_SRC_OUT_LIF},

    {DBAL_ENUM_FVAL_JR_FWD_CODE_IPV4_UC, 0, 0, DBAL_ENUM_FVAL_JR_VSI_SRC_VRF},

    {DBAL_ENUM_FVAL_JR_FWD_CODE_IPV6_UC, 0, 0, DBAL_ENUM_FVAL_JR_VSI_SRC_VRF},

    {DBAL_ENUM_FVAL_JR_FWD_CODE_IPV4_MC, 1, 1, DBAL_ENUM_FVAL_JR_VSI_SRC_VRF},

    {DBAL_ENUM_FVAL_JR_FWD_CODE_IPV6_MC, 1, 1, DBAL_ENUM_FVAL_JR_VSI_SRC_VRF},

    {DBAL_ENUM_FVAL_JR_FWD_CODE_IPV4_MC, 1, 0, DBAL_ENUM_FVAL_JR_VSI_SRC_VRF},

    {DBAL_ENUM_FVAL_JR_FWD_CODE_IPV6_MC, 1, 0, DBAL_ENUM_FVAL_JR_VSI_SRC_VRF}

};

static shr_error_e
egress_prp_general_configuration_init(
    int unit)
{

    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_ETPP_GLOBAL, &entry_handle_id));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ETPP_ENABLE, INST_SINGLE, TRUE);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SOURCE_IDX_MSB, INST_SINGLE, FALSE);

    if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_etppa_bypass_stamp_ftmh_enable))
    {

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_BYPASS_STAMP_FTMH_ENABLE, INST_SINGLE, TRUE);
    }
    else
    {

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_BYPASS_STAMP_FTMH_ENABLE, INST_SINGLE, FALSE);
    }
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ETPP_FIXED_LATENCY_EN, INST_SINGLE, FALSE);
    if (!dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_remove_crc_bytes))
    {
        if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_etpp_compensate_crc_size))
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_GENERAL_PACKET_SIZE_COMPENSATION,
                                         INST_SINGLE, 2);
        }
        else
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_NETWORK_OFFSET, INST_SINGLE, 2);
        }
    }
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PRP_PEMA_CONTEXT_ENABLE, INST_SINGLE, TRUE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
egress_parser_general_configuration_init(
    int unit)
{

    uint32 entry_handle_id, is_tdm_mode_packet;
    int system_headers_mode;

    uint32 udh_size = 0, crc_size = 0;
    uint32 lb_key_ext_size_bytes = 0, stacking_ext_size_bytes = 0;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    system_headers_mode = dnx_data_headers.system_headers.system_headers_mode_get(unit);
    if ((system_headers_mode == SYSTEM_HEADERS_MODE_JERICHO_MODE)
        && (dnx_data_headers.general.feature_get(unit, dnx_data_headers_general_jericho_mode_sys_header_is_supported) ==
            0))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Jericho mode system header is not supported");
    }
    crc_size = dnx_data_headers.system_headers.crc_size_counted_in_pkt_len_get(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_TDM, &entry_handle_id));
    is_tdm_mode_packet = (dnx_data_tdm.params.mode_get(unit) == TDM_MODE_PACKET);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TDM_MODE_IS_TDM_PACKET, INST_SINGLE,
                                 is_tdm_mode_packet);

    if (dnx_data_tdm.params.feature_get(unit, dnx_data_tdm_params_is_supported))
    {
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

    SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_EGRESS_PARSER_GLOBAL, entry_handle_id));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_BLOCK_IS_ETPP, INST_SINGLE, 0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_BLOCK_IS_ETPP_INV, INST_SINGLE, 0);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_JERICHO_FORWARD_CODE_FOR_MPLS, INST_SINGLE, 5);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_JERICHO_FHEI_SIZE_FOR_MPLS_POP, INST_SINGLE, 3);
    if (system_headers_mode == SYSTEM_HEADERS_MODE_JERICHO2_MODE)
    {

        uint64 work_reg_64;

        stacking_ext_size_bytes =
            dnx_data_headers.system_headers.jr2_mode_ftmh_stacking_ext_mode_get(unit) ? STACKING_EXT_SIZE : 0;

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SYSTEM_HEADERS_MODE, INST_SINGLE,
                                     DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO2_MODE);

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_BASE_CG_1_LAYER_IDX, INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_BASE_CG_1_HEADER_IDX, INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_BASE_CG_1_OFFSET, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_BASE_CG_1_SIZE, INST_SINGLE, 12);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LB_KEY_EXT_CG_1_LAYER_IDX, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LB_KEY_EXT_CG_1_HEADER_IDX, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LB_KEY_EXT_CG_1_OFFSET, INST_SINGLE,
                                     10 + FTMH_LB_KEY_EXT_SIZE);

        COMPILER_64_SET(work_reg_64, 0x18, 0xC6318C63);
        dbal_entry_value_field64_set(unit, entry_handle_id, DBAL_FIELD_LB_KEY_EXT_CG_1_MAPPED_SIZE, INST_SINGLE,
                                     work_reg_64);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_STACKING_EXT_CG_1_LAYER_IDX, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_STACKING_EXT_CG_1_HEADER_IDX, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_STACKING_EXT_CG_1_OFFSET, INST_SINGLE,
                                     10 + FTMH_LB_KEY_EXT_SIZE + stacking_ext_size_bytes);

        if (stacking_ext_size_bytes == STACKING_EXT_SIZE)
        {
            COMPILER_64_SET(work_reg_64, 0x10, 0x84210842);
        }
        else
        {
            COMPILER_64_SET(work_reg_64, 0x0, 0x0);
        }
        dbal_entry_value_field64_set(unit, entry_handle_id, DBAL_FIELD_STACKING_EXT_CG_1_MAPPED_SIZE, INST_SINGLE,
                                     work_reg_64);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_BIER_EXT_CG_1_LAYER_IDX, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_BIER_EXT_CG_1_HEADER_IDX, INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_BIER_EXT_CG_1_OFFSET, INST_SINGLE,
                                     10 + FTMH_LB_KEY_EXT_SIZE + stacking_ext_size_bytes);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_BIER_EXT_CG_1_SIZE, INST_SINGLE, 2);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_APPLICATION_SPECIFIC_EXT_CG_1_LAYER_IDX,
                                     INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_APPLICATION_SPECIFIC_EXT_CG_1_HEADER_IDX,
                                     INST_SINGLE, 3);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_APPLICATION_SPECIFIC_EXT_CG_1_OFFSET,
                                     INST_SINGLE, 10 + FTMH_LB_KEY_EXT_SIZE + stacking_ext_size_bytes);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_APPLICATION_SPECIFIC_EXT_CG_1_SIZE, INST_SINGLE,
                                     6);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TM_EXT_CG_1_LAYER_IDX, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TM_EXT_CG_1_HEADER_IDX, INST_SINGLE, 2);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TM_EXT_CG_1_OFFSET, INST_SINGLE,
                                     10 + FTMH_LB_KEY_EXT_SIZE + stacking_ext_size_bytes);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TM_EXT_CG_1_SIZE, INST_SINGLE, 3);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TSH_CG_1_LAYER_IDX, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TSH_CG_1_HEADER_IDX, INST_SINGLE, 4);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TSH_CG_1_OFFSET, INST_SINGLE,
                                     10 + FTMH_LB_KEY_EXT_SIZE + stacking_ext_size_bytes);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TSH_CG_1_SIZE, INST_SINGLE, 7);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FHEI_EXT_CG_1_LAYER_IDX, INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FHEI_EXT_CG_1_HEADER_IDX, INST_SINGLE, 2);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FHEI_EXT_CG_1_OFFSET, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FHEI_EXT_CG_1_SIZE, INST_SINGLE, 8);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LIF_EXT_CG_1_LAYER_IDX, INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LIF_EXT_CG_1_HEADER_IDX, INST_SINGLE, 3);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LIF_EXT_CG_1_OFFSET, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LIF_EXT_CG_1_SIZE, INST_SINGLE, 9);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LEARN_EXT_CG_1_LAYER_IDX, INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LEARN_EXT_CG_1_HEADER_IDX, INST_SINGLE, 4);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LEARN_EXT_CG_1_OFFSET, INST_SINGLE, 0x12);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LEARN_EXT_CG_1_SIZE, INST_SINGLE, 19);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_UDH_BASE_CG_1_LAYER_IDX, INST_SINGLE, 2);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_UDH_BASE_CG_1_HEADER_IDX, INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_UDH_BASE_CG_1_OFFSET, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_UDH_BASE_CG_1_SIZE, INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_UDH_DATA_CG_1_LAYER_IDX, INST_SINGLE, 2);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_UDH_DATA_CG_1_HEADER_IDX, INST_SINGLE, 2);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_UDH_DATA_CG_1_OFFSET, INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_UDH_DATA_CG_1_SIZE, INST_SINGLE, 16);

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_LEARN_EXT_PRESENT_CG_2_INNER_OFFSET,
                                     INST_SINGLE, 18);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_LEARN_EXT_PRESENT_CG_2_WIDTH, INST_SINGLE,
                                     1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FHEI_SIZE_CG_2_INNER_OFFSET, INST_SINGLE,
                                     16);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FHEI_SIZE_CG_2_WIDTH, INST_SINGLE, 2);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_LIF_EXT_TYPE_CG_2_INNER_OFFSET, INST_SINGLE,
                                     13);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_LIF_EXT_TYPE_CG_2_WIDTH, INST_SINGLE, 3);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_PARSING_START_OFFSET_CG_2_INNER_OFFSET,
                                     INST_SINGLE, 6);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_PARSING_START_OFFSET_CG_2_WIDTH, INST_SINGLE,
                                     7);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_PARSING_START_TYPE_CG_2_INNER_OFFSET,
                                     INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_PARSING_START_TYPE_CG_2_WIDTH, INST_SINGLE,
                                     5);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FWD_LAYER_INDEX_CG_2_INNER_OFFSET,
                                     INST_SINGLE, 90);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FWD_LAYER_INDEX_CG_2_WIDTH, INST_SINGLE, 3);
        dbal_entry_value_field32_set(unit, entry_handle_id,
                                     DBAL_FIELD_PPH_FWD_LAYER_ADD_INFO_CG_2_INNER_OFFSET, INST_SINGLE, 86);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FORWARDING_LAYER_ADD_INFO_CG_2_WIDTH,
                                     INST_SINGLE, 4);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FORWARDING_STRENGTH_CG_2_INNER_OFFSET,
                                     INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FORWARDING_STRENGTH_CG_2_WIDTH, INST_SINGLE,
                                     1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_IN_LIF_PROFILE_CG_2_INNER_OFFSET,
                                     INST_SINGLE, 75);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_IN_LIF_PROFILE_CG_2_WIDTH, INST_SINGLE, 8);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FORWARD_DOMAIN_CG_2_INNER_OFFSET,
                                     INST_SINGLE, 57);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FORWARD_DOMAIN_CG_2_WIDTH, INST_SINGLE, 18);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_IN_LIF_CG_2_INNER_OFFSET, INST_SINGLE, 35);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_IN_LIF_CG_2_WIDTH, INST_SINGLE, 22);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_NWK_QOS_CG_2_INNER_OFFSET, INST_SINGLE, 27);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_NWK_QOS_CG_2_WIDTH, INST_SINGLE, 8);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_TTL_CG_2_INNER_OFFSET, INST_SINGLE, 19);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_TTL_CG_2_WIDTH, INST_SINGLE, 8);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_END_OF_PACKET_EDITING_CG_2_INNER_OFFSET,
                                     INST_SINGLE, 83);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_END_OF_PACKET_EDITING_CG_2_WIDTH,
                                     INST_SINGLE, 3);

    }

    else
    {
        uint64 work_reg_64;

        lb_key_ext_size_bytes = dnx_data_headers.system_headers.jr_mode_ftmh_lb_key_ext_mode_get(unit) ? 1 : 0;
        stacking_ext_size_bytes =
            dnx_data_headers.system_headers.jr_mode_ftmh_stacking_ext_mode_get(unit) ? STACKING_EXT_SIZE : 0;

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SYSTEM_HEADERS_MODE, INST_SINGLE,
                                     DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO_MODE);

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_BASE_CG_1_LAYER_IDX, INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_BASE_CG_1_HEADER_IDX, INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_BASE_CG_1_OFFSET, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_BASE_CG_1_SIZE, INST_SINGLE, 7);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LB_KEY_EXT_CG_1_LAYER_IDX, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LB_KEY_EXT_CG_1_HEADER_IDX, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LB_KEY_EXT_CG_1_OFFSET, INST_SINGLE,
                                     9 + lb_key_ext_size_bytes);

        COMPILER_64_SET(work_reg_64, 0, 0x20);
        dbal_entry_value_field64_set(unit, entry_handle_id, DBAL_FIELD_LB_KEY_EXT_CG_1_MAPPED_SIZE, INST_SINGLE,
                                     work_reg_64);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TM_EXT_CG_1_LAYER_IDX, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TM_EXT_CG_1_HEADER_IDX, INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TM_EXT_CG_1_OFFSET, INST_SINGLE,
                                     9 + lb_key_ext_size_bytes);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TM_EXT_CG_1_SIZE, INST_SINGLE, 2);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_STACKING_EXT_CG_1_LAYER_IDX, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_STACKING_EXT_CG_1_HEADER_IDX, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_STACKING_EXT_CG_1_OFFSET,
                                     INST_SINGLE, 9 + lb_key_ext_size_bytes + stacking_ext_size_bytes);

        COMPILER_64_SET(work_reg_64, 0, 0x800);
        dbal_entry_value_field64_set(unit, entry_handle_id, DBAL_FIELD_STACKING_EXT_CG_1_MAPPED_SIZE, INST_SINGLE,
                                     work_reg_64);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_BIER_EXT_CG_1_LAYER_IDX, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_BIER_EXT_CG_1_HEADER_IDX, INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_BIER_EXT_CG_1_OFFSET, INST_SINGLE, 10);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_BIER_EXT_CG_1_SIZE, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_APPLICATION_SPECIFIC_EXT_CG_1_LAYER_IDX,
                                     INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_APPLICATION_SPECIFIC_EXT_CG_1_HEADER_IDX,
                                     INST_SINGLE, 3);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_APPLICATION_SPECIFIC_EXT_CG_1_OFFSET,
                                     INST_SINGLE, 9 + lb_key_ext_size_bytes + stacking_ext_size_bytes);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_APPLICATION_SPECIFIC_EXT_CG_1_SIZE, INST_SINGLE,
                                     6);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TSH_CG_1_LAYER_IDX, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TSH_CG_1_HEADER_IDX, INST_SINGLE, 3);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TSH_CG_1_OFFSET, INST_SINGLE,
                                     9 + lb_key_ext_size_bytes + stacking_ext_size_bytes);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TSH_CG_1_SIZE, INST_SINGLE, 6);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FHEI_EXT_CG_1_LAYER_IDX, INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FHEI_EXT_CG_1_HEADER_IDX, INST_SINGLE, 2);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FHEI_EXT_CG_1_OFFSET, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FHEI_EXT_CG_1_SIZE, INST_SINGLE, 8);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LIF_EXT_CG_1_LAYER_IDX, INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LIF_EXT_CG_1_HEADER_IDX, INST_SINGLE, 3);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LIF_EXT_CG_1_OFFSET, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LIF_EXT_CG_1_SIZE, INST_SINGLE, 9);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LEARN_EXT_CG_1_LAYER_IDX, INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LEARN_EXT_CG_1_HEADER_IDX, INST_SINGLE, 4);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LEARN_EXT_CG_1_OFFSET, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LEARN_EXT_CG_1_SIZE, INST_SINGLE, 5);

        udh_size += BITS2BYTES(dnx_data_field.udh.field_class_id_size_0_get(unit));
        udh_size += BITS2BYTES(dnx_data_field.udh.field_class_id_size_1_get(unit));
        udh_size += BITS2BYTES(dnx_data_field.udh.field_class_id_size_2_get(unit));
        udh_size += BITS2BYTES(dnx_data_field.udh.field_class_id_size_3_get(unit));

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_UDH_BASE_CG_1_SIZE, INST_SINGLE, 0);

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_UDH_DATA_CG_1_LAYER_IDX, INST_SINGLE, 2);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_UDH_DATA_CG_1_HEADER_IDX, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_UDH_DATA_CG_1_OFFSET, INST_SINGLE, udh_size);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_UDH_DATA_CG_1_SIZE, INST_SINGLE, udh_size);

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_LEARN_EXT_PRESENT_CG_2_INNER_OFFSET,
                                     INST_SINGLE, 54);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_LEARN_EXT_PRESENT_CG_2_WIDTH, INST_SINGLE,
                                     1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FHEI_SIZE_CG_2_INNER_OFFSET, INST_SINGLE,
                                     52);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FHEI_SIZE_CG_2_WIDTH, INST_SINGLE, 2);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_LIF_EXT_TYPE_CG_2_INNER_OFFSET, INST_SINGLE,
                                     55);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_LIF_EXT_TYPE_CG_2_WIDTH, INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_PARSING_START_OFFSET_CG_2_INNER_OFFSET,
                                     INST_SINGLE, 41);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_PARSING_START_OFFSET_CG_2_WIDTH, INST_SINGLE,
                                     7);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_PARSING_START_TYPE_CG_2_INNER_OFFSET,
                                     INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_PARSING_START_TYPE_CG_2_WIDTH, INST_SINGLE,
                                     0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FWD_LAYER_INDEX_CG_2_INNER_OFFSET,
                                     INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FWD_LAYER_INDEX_CG_2_WIDTH, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id,
                                     DBAL_FIELD_PPH_FWD_LAYER_ADD_INFO_CG_2_INNER_OFFSET, INST_SINGLE, 48);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FORWARDING_LAYER_ADD_INFO_CG_2_WIDTH,
                                     INST_SINGLE, 4);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FORWARDING_STRENGTH_CG_2_INNER_OFFSET,
                                     INST_SINGLE, 40);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FORWARDING_STRENGTH_CG_2_WIDTH, INST_SINGLE,
                                     1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_IN_LIF_PROFILE_CG_2_INNER_OFFSET,
                                     INST_SINGLE, 36);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_IN_LIF_PROFILE_CG_2_WIDTH, INST_SINGLE, 2);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FORWARD_DOMAIN_CG_2_INNER_OFFSET,
                                     INST_SINGLE, 18);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FORWARD_DOMAIN_CG_2_WIDTH, INST_SINGLE, 16);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_IN_LIF_CG_2_INNER_OFFSET, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_IN_LIF_CG_2_WIDTH, INST_SINGLE, 18);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_NWK_QOS_CG_2_INNER_OFFSET, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_NWK_QOS_CG_2_WIDTH, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_TTL_CG_2_INNER_OFFSET, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_TTL_CG_2_WIDTH, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_VALUE_1_CG_2_INNER_OFFSET, INST_SINGLE, 38);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_VALUE_1_CG_2_WIDTH, INST_SINGLE, 2);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_VALUE_2_CG_2_INNER_OFFSET, INST_SINGLE, 34);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_VALUE_2_CG_2_WIDTH, INST_SINGLE, 2);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_END_OF_PACKET_EDITING_CG_2_INNER_OFFSET,
                                     INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_END_OF_PACKET_EDITING_CG_2_WIDTH,
                                     INST_SINGLE, 0);
    }

    if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_remove_crc_bytes))
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FTMH_PACKET_SIZE_REMOVE_CRC, INST_SINGLE, 2);
    }
    else if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_remove_crc_bytes_capability))
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FTMH_PACKET_SIZE_REMOVE_CRC, INST_SINGLE, 0);
    }
    if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_erpp_compensate_crc_size))
    {

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FTMH_CRC_COMPENSATION, INST_SINGLE,
                                     ERPP_COMPENSATE_CRC_SIZE);
    }

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_NO_GLEM_ACCESS_USE_GLOBAL_OUTLIF, INST_SINGLE, 0);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    if (system_headers_mode == SYSTEM_HEADERS_MODE_JERICHO_MODE)
    {

        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_PARSERJR1SYSHDRS, &entry_handle_id));
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_JR1_FTMH_LB_KEY_PLUS_FTMH_STACKING_SIZE_IN_BYTES,
                                     INST_SINGLE, lb_key_ext_size_bytes + stacking_ext_size_bytes);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_JR1_UDH1_PLUS_UDH2_SIZE_IN_BYTES, INST_SINGLE,
                                     udh_size);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_SYSTEM_HEADER_GLOBAL_CFG, &entry_handle_id));
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_NETWORK_OFFSET, INST_SINGLE, udh_size);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

        if (dnx_data_dev_init.
            general.feature_get(unit, dnx_data_dev_init_general_network_offset_for_system_headers_valid))
        {
            SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_SYSTEM_HEADER_GLOBAL_CFG, &entry_handle_id));
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_NETWORK_OFFSET_FOR_SYSTEM_HEADERS,
                                         INST_SINGLE, udh_size);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
        }

        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_ETPP_GLOBAL, &entry_handle_id));
        if (!dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_etpp_compensate_crc_size))
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_NETWORK_OFFSET, INST_SINGLE,
                                         udh_size + crc_size);
        }
        else
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_NETWORK_OFFSET, INST_SINGLE, udh_size);
        }
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

    else
    {

        if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_remove_crc_bytes))
        {
            if (!dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_etpp_compensate_crc_size))
            {
                SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_ETPP_GLOBAL, &entry_handle_id));
                dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_NETWORK_OFFSET, INST_SINGLE, crc_size);
                SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            }
        }

        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_PARSERJR2SYSHDRS, &entry_handle_id));
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_JR2_FTMH_STACKING_EXT_SIZE_IN_BYTES,
                                     INST_SINGLE, stacking_ext_size_bytes);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_SYSTEM_HEADER_GLOBAL_CFG, &entry_handle_id));
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_NETWORK_OFFSET, INST_SINGLE, 0);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

        if (dnx_data_dev_init.
            general.feature_get(unit, dnx_data_dev_init_general_network_offset_for_system_headers_valid))
        {
            SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_SYSTEM_HEADER_GLOBAL_CFG, &entry_handle_id));
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_NETWORK_OFFSET_FOR_SYSTEM_HEADERS,
                                         INST_SINGLE, 0);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
        }

    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
egress_selected_outlif_table_configure(
    int unit,
    int index,
    int outlif_0_decision,
    int outlif_1_decision,
    int outlif_2_decision,
    int outlif_3_decision)
{

    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_SELECTED_GLOBAL_OUTLIFS, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INDEX, index);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OUTLIF_0_DECISION, INST_SINGLE, outlif_0_decision);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OUTLIF_1_DECISION, INST_SINGLE, outlif_1_decision);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OUTLIF_2_DECISION, INST_SINGLE, outlif_2_decision);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OUTLIF_3_DECISION, INST_SINGLE, outlif_3_decision);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

shr_error_e static
egress_selected_outlif_table_init(
    int unit)
{

    int nof_outlif_decision_entries;
    int entry;
    int system_headers_mode;
    outlif_decision_t *decision = NULL;

    SHR_FUNC_INIT_VARS(unit);

    system_headers_mode = dnx_data_headers.system_headers.system_headers_mode_get(unit);

    if (system_headers_mode == SYSTEM_HEADERS_MODE_JERICHO2_MODE)
    {
        decision = (outlif_decision_t *) outlif_decision_map_jr2_mode;
        nof_outlif_decision_entries = sizeof(outlif_decision_map_jr2_mode) / sizeof(outlif_decision_t);
    }
    else
    {
        decision = (outlif_decision_t *) outlif_decision_map_jer_mode;
        nof_outlif_decision_entries = sizeof(outlif_decision_map_jer_mode) / sizeof(outlif_decision_t);
    }

    for (entry = 0; entry < nof_outlif_decision_entries; entry++)
    {

        SHR_IF_ERR_EXIT(egress_selected_outlif_table_configure
                        (unit, decision[entry].index,
                         decision[entry].outlif_0_decision,
                         decision[entry].outlif_1_decision,
                         decision[entry].outlif_2_decision, decision[entry].outlif_3_decision));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
egress_system_headers_lif_extension_configuration(
    int unit,
    int lif_extension_type,
    int outlif_extension_1,
    int outlif_extension_2,
    int outlif_extension_3,
    int inlif_extension_1,
    int inlif_extension_1_profile)
{

    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_SYSTEM_HEADERS_LIF_EXTENSION, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LIF_EXTENSION_TYPE, lif_extension_type);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OUTLIF_EXTENSION_1_CONFIG, INST_SINGLE,
                                 outlif_extension_1);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OUTLIF_EXTENSION_2_CONFIG, INST_SINGLE,
                                 outlif_extension_2);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OUTLIF_EXTENSION_3_CONFIG, INST_SINGLE,
                                 outlif_extension_3);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_INLIF_EXTENSION_1_CONFIG, INST_SINGLE,
                                 inlif_extension_1);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_INLIF_EXTENSION_1_PROFILE_CONFIG, INST_SINGLE,
                                 inlif_extension_1_profile);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

shr_error_e static
egress_system_headers_lif_extension_configuration_init(
    int unit)
{

    int nof_lif_extension_entries;
    int entry;

    SHR_FUNC_INIT_VARS(unit);

    nof_lif_extension_entries = sizeof(outlif_extension_map) / sizeof(outlif_extension_config_t);

    for (entry = 0; entry < nof_lif_extension_entries; entry++)
    {

        SHR_IF_ERR_EXIT(egress_system_headers_lif_extension_configuration
                        (unit, outlif_extension_map[entry].lif_extension_type,
                         outlif_extension_map[entry].outlif_extension_1,
                         outlif_extension_map[entry].outlif_extension_2,
                         outlif_extension_map[entry].outlif_extension_3, outlif_extension_map[entry].inlif_extension_1,
                         outlif_extension_map[entry].inlif_extension_1_profile));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
ingress_lbp_general_configuration_init(
    int unit)
{

    uint32 entry_handle_id;
    int system_headers_mode;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    system_headers_mode = dnx_data_headers.system_headers.system_headers_mode_get(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_LBP_GLOBAL, &entry_handle_id));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_RESERVED_BITS_SIZE, INST_SINGLE, 3);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_OUT_LIF_SIZE, INST_SINGLE, 22);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_IN_LIF_SIZE, INST_SINGLE, 22);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_IN_LIF_PROFILE_SIZE, INST_SINGLE, 8);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FWD_LAYER_IDX_SIZE, INST_SINGLE, 3);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FWD_LAYER_ADDITIONAL_INFO_SIZE, INST_SINGLE, 4);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_FWD_DOMAIN_SIZE, INST_SINGLE, 18);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PPH_END_OF_PACKET_EDITING_SIZE, INST_SINGLE, 3);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FTMH_TM_DESTINATION_EXT_PRESENT, INST_SINGLE,
                                 dnx_data_headers.ftmh.add_dsp_ext_get(unit));
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SLB_LEARN_PAYLOAD_START_BIT, INST_SINGLE, 0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ELEPHANT_TRAP_LEARN_PAYLOAD_START_BIT, INST_SINGLE,
                                 0);
    if (system_headers_mode != SYSTEM_HEADERS_MODE_JERICHO2_MODE)
    {
        int field_size = 0, field_value = 0;

        dbal_tables_field_size_get(unit, DBAL_TABLE_INGRESS_LBP_GLOBAL, DBAL_FIELD_OUT_RIF_SIZE,
                                   FALSE, 0, 0, &field_size);
        if (dnx_data_l3.rif.nof_rifs_get(unit) == (1 << field_size))
        {
            field_value = SAL_UPTO_BIT(field_size);
        }
        else
        {
            field_value = dnx_data_l3.rif.nof_rifs_get(unit);
        }
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OUT_RIF_SIZE, INST_SINGLE, field_value);

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_MODE_ADD_UDH_BASE, INST_ALL, FALSE);

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_MODE_UDH_SIZE_COMPENSATION_ENABLE, INST_ALL,
                                     TRUE);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ENABLE_FHEI_WITH_IN_LIF_PROFILE, INST_SINGLE,
                                     TRUE);

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_MODE_TIMESTAMP_RIGHT_SHIFT, INST_SINGLE,
                                     dnx_data_headers.system_headers.jr_mode_ftmh_oam_ts_right_shift_get(unit));
    }
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    if (system_headers_mode != SYSTEM_HEADERS_MODE_JERICHO2_MODE)
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_OAM, &entry_handle_id));

        dbal_entry_value_field32_set(unit, entry_handle_id,
                                     DBAL_FIELD_CFG_UP_MEP_STACKING_EXTENSION_PRESENT_INDICATION, INST_SINGLE,
                                     dnx_data_headers.system_headers.jr_mode_ftmh_stacking_ext_mode_get(unit));

        dbal_entry_value_field32_set(unit, entry_handle_id,
                                     DBAL_FIELD_CFG_UP_MEP_LOAD_BALANCING_EXTENSION_PRESENT_INDICATION, INST_SINGLE,
                                     dnx_data_headers.system_headers.jr_mode_ftmh_lb_key_ext_mode_get(unit));

        dbal_entry_value_field32_set(unit, entry_handle_id,
                                     DBAL_FIELD_CFG_UP_MEP_PPH_LEARN_EXTENSION_DISABLE_INDICATION, INST_SINGLE,
                                     dnx_data_headers.system_headers.jr_mode_pph_learn_extension_disable_get(unit));

        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

    if (dnx_data_headers.system_headers.jr2_mode_ftmh_stacking_ext_mode_get(unit))
    {

        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_OAM, &entry_handle_id));
        dbal_entry_value_field32_set(unit, entry_handle_id,
                                     DBAL_FIELD_CFG_UP_MEP_STACKING_EXTENSION_PRESENT_INDICATION, INST_SINGLE, 1);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

    if (dnx_data_headers.ftmh.add_dsp_ext_get(unit))
    {

        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_OAM, &entry_handle_id));
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CFG_UP_MEP_DSP_EXTENSION_PRESENT_INDICATION,
                                     INST_SINGLE, 1);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
ingress_lbp_jr_fwd_code_map_table_configure(
    int unit,
    dbal_enum_value_field_layer_types_e layer_type,
    int fwd_layer_qual_lsb,
    dbal_enum_value_field_jr_fwd_code_e fwd_code)
{

    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_JR_FWD_CODE_MAPPING_TABLE, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_FORWARD_LAYER_TYPE, layer_type);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_FWD_LAYER_QUAL_LSB, fwd_layer_qual_lsb);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_FWD_CODE, INST_SINGLE, fwd_code);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
ingress_lbp_jr_vsi_src_map_table_configure(
    int unit,
    dbal_enum_value_field_jr_fwd_code_e fwd_code,
    int is_mc,
    int outlif_is_rif,
    dbal_enum_value_field_jr_vsi_src_e vsi_src)
{

    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_JR_VSI_SRC_MAPPING_TABLE, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_FWD_CODE, fwd_code);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_MC, is_mc);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OUTLIF_IS_RIF, outlif_is_rif);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_VSI_SRC, INST_SINGLE, vsi_src);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
ingress_lbp_jr_vsi_src_in_lif_map_table_configure(
    int unit,
    dbal_enum_value_field_jr_fwd_code_e fwd_code,
    int is_mc,
    int outlif_is_rif,
    uint8 in_lif_selection,
    dbal_enum_value_field_jr_vsi_src_e vsi_src)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_JR_VSI_SRC_MAPPING_TABLE, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_FWD_CODE, fwd_code);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_MC, is_mc);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OUTLIF_IS_RIF, outlif_is_rif);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_VSI_SRC, INST_SINGLE, vsi_src);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_IN_LIF_SRC, INST_SINGLE,
                                 (uint32) in_lif_selection);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
ingress_lbp_jr_fhei_size_map_table_configure(
    int unit)
{

    uint32 entry_handle_id;
    dbal_enum_value_field_jr_fwd_code_e fwd_code_index;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_JR_FHEI_SIZE_MAPPING, &entry_handle_id));

    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_JR_FWD_CODE, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_INLIF_EQ_ZERO, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_FWD_LAYER_IDX, DBAL_RANGE_ALL, DBAL_RANGE_ALL);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FHEI_SIZE, INST_SINGLE, DBAL_ENUM_FVAL_FHEI_SIZE_3B);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    for (fwd_code_index = DBAL_ENUM_FVAL_JR_FWD_CODE_BRIDGE; fwd_code_index < DBAL_NOF_ENUM_JR_FWD_CODE_VALUES;
         fwd_code_index++)
    {
        if ((fwd_code_index != DBAL_ENUM_FVAL_JR_FWD_CODE_BRIDGE)
            && (fwd_code_index != DBAL_ENUM_FVAL_JR_FWD_CODE_IPV4_UC)
            && (fwd_code_index != DBAL_ENUM_FVAL_JR_FWD_CODE_IPV4_MC)
            && (fwd_code_index != DBAL_ENUM_FVAL_JR_FWD_CODE_IPV6_UC)
            && (fwd_code_index != DBAL_ENUM_FVAL_JR_FWD_CODE_IPV6_MC)
            && (fwd_code_index != DBAL_ENUM_FVAL_JR_FWD_CODE_TRILL)
            && (fwd_code_index != DBAL_ENUM_FVAL_JR_FWD_CODE_CPU_TRAP1)
            && (fwd_code_index != DBAL_ENUM_FVAL_JR_FWD_CODE_RESERVED0))
        {

            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_FWD_CODE, fwd_code_index);
            dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_INLIF_EQ_ZERO, DBAL_RANGE_ALL,
                                             DBAL_RANGE_ALL);
            dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_FWD_LAYER_IDX, DBAL_RANGE_ALL,
                                             DBAL_RANGE_ALL);

            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FHEI_SIZE, INST_SINGLE,
                                         DBAL_ENUM_FVAL_FHEI_SIZE_0B);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

        }
    }

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_FWD_CODE, DBAL_ENUM_FVAL_JR_FWD_CODE_IPV4_MC);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_INLIF_EQ_ZERO, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_FWD_LAYER_IDX, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FHEI_SIZE, INST_SINGLE, DBAL_ENUM_FVAL_FHEI_SIZE_8B);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_FWD_CODE, DBAL_ENUM_FVAL_JR_FWD_CODE_IPV6_MC);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_INLIF_EQ_ZERO, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_FWD_LAYER_IDX, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FHEI_SIZE, INST_SINGLE, DBAL_ENUM_FVAL_FHEI_SIZE_8B);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_FWD_CODE, DBAL_ENUM_FVAL_JR_FWD_CODE_MPLS);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INLIF_EQ_ZERO, FALSE);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_FWD_LAYER_IDX, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FHEI_SIZE, INST_SINGLE, DBAL_ENUM_FVAL_FHEI_SIZE_5B);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_JR_FWD_CODE, DBAL_ENUM_FVAL_JR_FWD_CODE_MPLS);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INLIF_EQ_ZERO, TRUE);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_FWD_LAYER_IDX, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FHEI_SIZE, INST_SINGLE, DBAL_ENUM_FVAL_FHEI_SIZE_3B);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
ingress_lbp_jer_mode_configuration_init(
    int unit)
{
    int nof_entries;
    int entry;
    int roo_enable = 0;

    SHR_FUNC_INIT_VARS(unit);

    nof_entries = sizeof(jr_mode_fwd_code_map) / sizeof(jr_mode_fwd_code_mapping_config_t);

    for (entry = 0; entry < nof_entries; entry++)
    {

        SHR_IF_ERR_EXIT(ingress_lbp_jr_fwd_code_map_table_configure
                        (unit, jr_mode_fwd_code_map[entry].fwd_layer_type,
                         jr_mode_fwd_code_map[entry].fwd_layer_qual_lsb, jr_mode_fwd_code_map[entry].jr_fwd_code));
    }

    nof_entries = sizeof(jr_mode_vsi_src_map) / sizeof(jr_mode_vsi_src_mapping_config_t);

    if (dnx_data_field.init.jr1_ipmc_inlif_get(unit) == 1)
    {
        for (entry = 0; entry < nof_entries; entry++)
        {

            SHR_IF_ERR_EXIT(ingress_lbp_jr_vsi_src_map_table_configure
                            (unit, jr_mode_vsi_src_map[entry].jr_fwd_code,
                             jr_mode_vsi_src_map[entry].is_mc,
                             jr_mode_vsi_src_map[entry].outlif_is_rif, jr_mode_vsi_src_map[entry].jr_vsi_src));
        }
    }
    else
    {
        SHR_IF_ERR_EXIT(ingress_lbp_jr_vsi_src_in_lif_map_table_configure
                        (unit, DBAL_ENUM_FVAL_JR_FWD_CODE_IPV4_UC, 0, 1, 0, DBAL_ENUM_FVAL_JR_VSI_SRC_OUT_LIF));
        SHR_IF_ERR_EXIT(ingress_lbp_jr_vsi_src_in_lif_map_table_configure
                        (unit, DBAL_ENUM_FVAL_JR_FWD_CODE_IPV6_UC, 0, 1, 0, DBAL_ENUM_FVAL_JR_VSI_SRC_OUT_LIF));
        SHR_IF_ERR_EXIT(ingress_lbp_jr_vsi_src_in_lif_map_table_configure
                        (unit, DBAL_ENUM_FVAL_JR_FWD_CODE_IPV4_MC, 1, 0, 1, DBAL_ENUM_FVAL_JR_VSI_SRC_IN_RIF));
        SHR_IF_ERR_EXIT(ingress_lbp_jr_vsi_src_in_lif_map_table_configure
                        (unit, DBAL_ENUM_FVAL_JR_FWD_CODE_IPV6_MC, 1, 0, 1, DBAL_ENUM_FVAL_JR_VSI_SRC_IN_RIF));

    }

    roo_enable = dnx_data_field.init.roo_get(unit);
    if (!roo_enable)
    {

        SHR_IF_ERR_EXIT(ingress_lbp_jr_vsi_src_map_table_configure
                        (unit, DBAL_ENUM_FVAL_JR_FWD_CODE_IPV4_UC, 0, 0, DBAL_ENUM_FVAL_JR_VSI_SRC_INVALID));

        SHR_IF_ERR_EXIT(ingress_lbp_jr_vsi_src_map_table_configure
                        (unit, DBAL_ENUM_FVAL_JR_FWD_CODE_IPV6_UC, 0, 0, DBAL_ENUM_FVAL_JR_VSI_SRC_INVALID));

    }

    SHR_IF_ERR_EXIT(ingress_lbp_jr_fhei_size_map_table_configure(unit));

exit:
    SHR_FUNC_EXIT;

}

static shr_error_e
ingress_vtt_global_configuration_init(
    int unit)
{

    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_VTT_GLOBAL, &entry_handle_id));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SEXEM_INTERFACE_0_SEL, INST_SINGLE, 0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SEXEM_INTERFACE_2_SEL, INST_SINGLE, 1);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_EXTEND_VCP_EN, INST_SINGLE,
                                 dnx_data_vlan.llvp.ext_vcp_en_get(unit));
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
ingress_itpp_general_configuration_init(
    int unit)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_ITPP_GENERAL_CFG, &entry_handle_id));
    if (dnx_data_device.general.feature_get(unit, dnx_data_device_general_itpp_cud_valid_check))
    {

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PD_CUD_INVALID_VALUE, INST_SINGLE,
                                     DBAL_DEFINE_PD_CUD_INVALID_VALUE_DEFAULT);
    }
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ENABLE_TERMINATION, INST_SINGLE, 1);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_SYSTEM_HEADER_GLOBAL_CFG, entry_handle_id));
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF_EXT_SIZE, 0, LIF_EXTENSION_SIZE_1XOUT_LIF);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF_EXT_SIZE, 1,
                                 2 * LIF_EXTENSION_SIZE_1XOUT_LIF);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF_EXT_SIZE, 2,
                                 3 * LIF_EXTENSION_SIZE_1XOUT_LIF);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_EXT_SIZE, INST_SINGLE,
                                 LIF_EXTENSION_SIZE_IN_LIF_PROFILE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    SHR_IF_ERR_EXIT(ingress_itpp_general_network_header_termination_init(unit));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
egress_system_header_generation_table_configure(
    int unit,
    int system_header_profile,
    int bytes_to_add)
{

    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_SYSTEM_HEADER_GENERATION_TABLE, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_SYS_HDR_GENERATION_PROFILE, system_header_profile);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_BYTES_TO_ADD, INST_SINGLE, bytes_to_add);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_init_pp_egress_current_next_protocol_config_table_get(
    int unit,
    int current_protocol_type,
    int current_protocol_namespace,
    int *current_next_protocol)
{

    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_CURRENT_NEXT_PROTOCOL_MAP_TABLE, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CURRENT_PROTOCOL_TYPE, current_protocol_type);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_NEXT_PROTOCOL_NAMESPACE, current_protocol_namespace);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_CURRENT_NEXT_PROTOCOL, INST_SINGLE,
                               (uint32 *) current_next_protocol);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
egress_global_inlif_resolution_table_configure(
    int unit,
    int system_headers_mode,
    int is_mc_forward_code,
    int inlif_decision_0,
    int inlif_decision_1)
{

    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_GLOBAL_INLIF_RESOLUTION, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_SYSTEM_HEADERS_MODE, system_headers_mode);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_FORWARD_CODE_IPVX_MC, is_mc_forward_code);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_INLIF_DECISION_0, INST_SINGLE, inlif_decision_0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_INLIF_DECISION_1, INST_SINGLE, inlif_decision_1);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
egress_glem_dummy_entry_configure(
    int unit)
{

    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_GLOBAL_RIF_EM, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_GLOB_OUT_RIF, 0);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, DBAL_CORE_ALL);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ERPP_OUT_LIF_PROFILE, 0, 0);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
egress_global_inlif_resolution_table_init(
    int unit)
{

    int nof_global_inlif_config_entries;
    int entry;
    int system_headers_mode;

    SHR_FUNC_INIT_VARS(unit);

    system_headers_mode = dnx_data_headers.system_headers.system_headers_mode_get(unit);

    if (system_headers_mode == SYSTEM_HEADERS_MODE_JERICHO2_MODE)
    {
        nof_global_inlif_config_entries = sizeof(inlif_decision_config_map_jr2_mode) / sizeof(inlif_decision_config_t);
    }
    else
    {
        nof_global_inlif_config_entries = sizeof(inlif_decision_config_map_jer_mode) / sizeof(inlif_decision_config_t);
    }

    for (entry = 0; entry < nof_global_inlif_config_entries; entry++)
    {

        if (system_headers_mode == SYSTEM_HEADERS_MODE_JERICHO2_MODE)
        {
            SHR_IF_ERR_EXIT(egress_global_inlif_resolution_table_configure
                            (unit, inlif_decision_config_map_jr2_mode[entry].system_headers_mode,
                             inlif_decision_config_map_jr2_mode[entry].is_mc_forward_code,
                             inlif_decision_config_map_jr2_mode[entry].inlif_decision_0,
                             inlif_decision_config_map_jr2_mode[entry].inlif_decision_1));
        }
        else
        {
            SHR_IF_ERR_EXIT(egress_global_inlif_resolution_table_configure
                            (unit, inlif_decision_config_map_jer_mode[entry].system_headers_mode,
                             inlif_decision_config_map_jer_mode[entry].is_mc_forward_code,
                             inlif_decision_config_map_jer_mode[entry].inlif_decision_0,
                             inlif_decision_config_map_jer_mode[entry].inlif_decision_1));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
egress_system_header_generation_table_init(
    int unit)
{

    int nof_system_header_generation_profile_entries;
    int entry;

    SHR_FUNC_INIT_VARS(unit);

    nof_system_header_generation_profile_entries = sizeof(system_header_profile_map) / sizeof(system_header_profile_t);

    for (entry = 0; entry < nof_system_header_generation_profile_entries; entry++)
    {

        SHR_IF_ERR_EXIT(egress_system_header_generation_table_configure
                        (unit, system_header_profile_map[entry].system_header_profile,
                         system_header_profile_map[entry].bytes_to_add));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
egress_fhei_mpls_upper_layer_protocol_to_pes_mapping_configure(
    int unit,
    dbal_enum_value_field_layer_types_e layer_type,
    dbal_enum_value_field_egress_1st_parser_parser_context_e parser_context)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_PER_LAYER_PROTOCOL, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPES, layer_type);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_EGRESS_PARSING_CONTEXT, INST_SINGLE, parser_context);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
ingress_map_parsing_ctx_layer_potocol(
    int unit)
{
    int ii = 0;
    uint32 entry_handle_id;
    int nof_ctx_to_config;
    int mpls_second_stage_parser_handling;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    mpls_second_stage_parser_handling = dnx_data_mpls.general.mpls_second_stage_parser_handling_get(unit);

    nof_ctx_to_config = sizeof(per_2nd_stage_parsing_ctx) / sizeof(per_2nd_stage_parsing_ctx_t);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_MAP_PARSING_CTX_LAYER_PROTOCOL, &entry_handle_id));
    for (ii = 0; ii < nof_ctx_to_config; ii++)
    {
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IRPP_2ND_PARSER_PARSER_CONTEXT,
                                   per_2nd_stage_parsing_ctx[ii].parser_ctx);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPES_SPECULATION, INST_SINGLE,
                                     per_2nd_stage_parsing_ctx[ii].layer_type_speculation);
        if (!mpls_second_stage_parser_handling)
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPES_FORCE_INCORRECT, INST_SINGLE,
                                         per_2nd_stage_parsing_ctx[ii].layer_type_force_incorrect);
        }
        else
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPES_FORCE_INCORRECT, INST_SINGLE,
                                         per_2nd_stage_parsing_ctx[ii].layer_type_speculation);
        }
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
egress_fhei_mpls_upper_layer_protocol_to_pes_mapping_init(
    int unit)
{

    int entry;
    int nof_layres_to_config;

    SHR_FUNC_INIT_VARS(unit);

    nof_layres_to_config =
        sizeof(layer_type_to_mpls_upper_layer_protocol) / sizeof(layer_type_to_mpls_upper_layer_protocol_t);

    for (entry = 0; entry < nof_layres_to_config; entry++)
    {

        SHR_IF_ERR_EXIT(egress_fhei_mpls_upper_layer_protocol_to_pes_mapping_configure
                        (unit, layer_type_to_mpls_upper_layer_protocol[entry].layer_type,
                         layer_type_to_mpls_upper_layer_protocol[entry].parser_context));
    }
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
egress_global_eedb_configuration_init(
    int unit)
{
    uint32 entry_handle_id;
    int nof_rifs;
    int local_outlif_width;
    int outlif_profile_width, system_headers_mode, iop_mode_outlif_selection;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    nof_rifs = dnx_data_l3.rif.nof_rifs_get(unit);

    local_outlif_width = dnx_data_lif.out_lif.local_outlif_width_get(unit);
    outlif_profile_width = dnx_data_lif.out_lif.outlif_profile_width_get(unit);
    system_headers_mode = dnx_data_headers.system_headers.system_headers_mode_get(unit);
    iop_mode_outlif_selection = dnx_data_lif.feature.feature_get(unit, dnx_data_lif_feature_iop_mode_outlif_selection);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_EEDB_GLOBAL, &entry_handle_id));

    if ((system_headers_mode == DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO2_MODE) ||
        (iop_mode_outlif_selection == FALSE))
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_NOF_RIFS, INST_SINGLE, nof_rifs);
    }
    else
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_NOF_RIFS, INST_SINGLE, 0);
    }
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LOCAL_OUTLIF_SIZE_IN_BITS, INST_SINGLE,
                                 local_outlif_width);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OUTLIF_PROFILE_SIZE_IN_BITS, INST_SINGLE,
                                 outlif_profile_width);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
ingress_egw_full_threshold_set(
    int unit)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_EGW_FULL_THRESHOLD, &entry_handle_id));
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FLP_FULL_THRESHOLD, INST_SINGLE,
                                 dnx_data_elk.general.flp_full_treshold_get(unit));
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
ingress_ippe_traffic_enable(
    int unit)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_GLOBAL_CONFIGURATION, &entry_handle_id));
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DATA_PATH_ENABLE, INST_SINGLE, TRUE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
egress_fwd_plus_1_remark_ingress_profile_configuration(
    int unit,
    uint32 fwd_additional_info,
    uint8 fwd_plus_1_remark_ingress_profile)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_FORWARDING_ADDITIONAL_INFO, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_FORWARDING_ADDITIONAL_INFO, fwd_additional_info);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_FWD_PLUS_1_REMARK_INGRESS_PROFILE, INST_SINGLE,
                                fwd_plus_1_remark_ingress_profile);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
ingress_forwarding_additional_info_to_bum_traffic_configuration(
    int unit,
    uint32 fwd_additional_info,
    uint8 bum_traffic_enable)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_FORWARDING_ADDITIONAL_INFO, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_FORWARDING_ADDITIONAL_INFO, fwd_additional_info);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_BUM_TRAFFIC_ENABLE, INST_SINGLE, bum_traffic_enable);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
ingress_egress_forwarding_additional_info_configuration_init(
    int unit)
{
    uint32 nof_map_tables_entries;
    uint32 entry;

    SHR_FUNC_INIT_VARS(unit);

    nof_map_tables_entries =
        sizeof(forwarding_additional_info_config_map) / sizeof(forwarding_additional_info_config_t);

    for (entry = 0; entry < nof_map_tables_entries; entry++)
    {
        SHR_IF_ERR_EXIT(egress_fallback_to_bridge_configuration(unit,
                                                                forwarding_additional_info_config_map
                                                                [entry].forwarding_additional_info,
                                                                forwarding_additional_info_config_map
                                                                [entry].ipvx_fallback_to_bridge_enable));

        SHR_IF_ERR_EXIT(ingress_forwarding_additional_info_to_bum_traffic_configuration(unit,
                                                                                        forwarding_additional_info_config_map
                                                                                        [entry].forwarding_additional_info,
                                                                                        forwarding_additional_info_config_map
                                                                                        [entry].bum_traffic_enable));
        SHR_IF_ERR_EXIT(egress_fwd_plus_1_remark_ingress_profile_configuration
                        (unit, forwarding_additional_info_config_map[entry].forwarding_additional_info,
                         forwarding_additional_info_config_map[entry].fwd_plus_1_remark_ingress_profile));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
egress_same_interface_filter_configure_init(
    int unit)
{
    uint32 entry_handle_id;
    int system_headers_mode, same_interface_bits, orientation;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    same_interface_bits = dnx_data_lif.in_lif.in_lif_profile_allocate_same_interface_mode_get(unit);
    system_headers_mode = dnx_data_headers.system_headers.system_headers_mode_get(unit);
    orientation = dnx_data_lif.in_lif.in_lif_profile_allocate_orientation_get(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_SAME_INTERFACE_FILTER, &entry_handle_id));

    if (system_headers_mode == DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO2_MODE)
    {

        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_SYS_PORT_EQUAL, TRUE);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INLIF_IS_PORT, FALSE);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OUTLIF_IS_PORT, FALSE);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_FWD_CONTEXT_SAME_INTERFACE_FILTER, TRUE);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SAME_INTERFACE_FILTER_ENABLE, INST_SINGLE, TRUE);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LIFS_EQUAL, TRUE);
        dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF_SAME_INTERFACE_FILTER,
                                         DBAL_RANGE_ALL, DBAL_RANGE_ALL);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_SAME_INTERFACE_FILTER,
                                   DEVICE_SCOPE_LIF_PROFILE);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

    else
    {
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_SYS_PORT_EQUAL, TRUE);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INLIF_IS_PORT, FALSE);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OUTLIF_IS_PORT, FALSE);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_FWD_CONTEXT_SAME_INTERFACE_FILTER, TRUE);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SAME_INTERFACE_FILTER_ENABLE, INST_SINGLE, TRUE);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LIFS_EQUAL, TRUE);
        dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF_SAME_INTERFACE_FILTER,
                                         DBAL_RANGE_ALL, DBAL_RANGE_ALL);

        if (same_interface_bits == JR_COMP_MODE_BOTH_DEV_AND_SYS_SCOPE_ENABLED_BY_SOC_PROPERTIES)
        {

            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_SAME_INTERFACE_FILTER,
                                       DEVICE_SCOPE_LIF_PROFILE);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_SAME_INTERFACE_FILTER,
                                       SYSTEM_SCOPE_LIF_PROFILE_JR_MODE_2B_BOTH_ENABLED);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
        }

        else if (same_interface_bits == JR_COMP_MODE_ONLY_SYS_SCOPE_ENABLED_BY_SOC_PROPERTIES)
        {

            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_SAME_INTERFACE_FILTER,
                                       DEVICE_SCOPE_LIF_PROFILE);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_SAME_INTERFACE_FILTER,
                                       SYSTEM_SCOPE_LIF_PROFILE_JR_MODE_1B_ENABLED);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
        }
        else if ((same_interface_bits == JR_COMP_MODE_ONLY_DEV_SCOPE_ENABLED_BY_SOC_PROPERTIES) && (orientation > 0))
        {

            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_SAME_INTERFACE_FILTER,
                                       DEVICE_SCOPE_LIF_PROFILE);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_SAME_INTERFACE_FILTER,
                                       DEVICE_SCOPE_ENABLED_AND_ORIENTATION_ENABLED);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
        }
        else
        {

            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_SAME_INTERFACE_FILTER,
                                       DEVICE_SCOPE_LIF_PROFILE);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
        }
    }

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_SYS_PORT_EQUAL, TRUE);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INLIF_IS_PORT, TRUE);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OUTLIF_IS_PORT, TRUE);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LIFS_EQUAL, TRUE);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_FWD_CONTEXT_SAME_INTERFACE_FILTER, TRUE);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF_SAME_INTERFACE_FILTER, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_SAME_INTERFACE_FILTER,
                               DEVICE_SCOPE_LIF_PROFILE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    if (system_headers_mode == DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO2_MODE)
    {
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_SYS_PORT_EQUAL, FALSE);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INLIF_IS_PORT, FALSE);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OUTLIF_IS_PORT, FALSE);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_FWD_CONTEXT_SAME_INTERFACE_FILTER, TRUE);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SAME_INTERFACE_FILTER_ENABLE, INST_SINGLE, TRUE);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LIFS_EQUAL, TRUE);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_SAME_INTERFACE_FILTER,
                                   SYSTEM_SCOPE_LIF_PROFILE);
        dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF_SAME_INTERFACE_FILTER,
                                         DBAL_RANGE_ALL, DBAL_RANGE_ALL);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_SYS_PORT_EQUAL, TRUE);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

    else
    {
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_SYS_PORT_EQUAL, FALSE);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INLIF_IS_PORT, FALSE);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OUTLIF_IS_PORT, FALSE);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_FWD_CONTEXT_SAME_INTERFACE_FILTER, TRUE);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SAME_INTERFACE_FILTER_ENABLE, INST_SINGLE, TRUE);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LIFS_EQUAL, TRUE);
        dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_OUT_LIF_SAME_INTERFACE_FILTER,
                                         DBAL_RANGE_ALL, DBAL_RANGE_ALL);

        if (same_interface_bits == JR_COMP_MODE_BOTH_DEV_AND_SYS_SCOPE_ENABLED_BY_SOC_PROPERTIES)
        {

            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_SAME_INTERFACE_FILTER,
                                       SYSTEM_SCOPE_LIF_PROFILE_JR_MODE_2B_ENABLED);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_SAME_INTERFACE_FILTER,
                                       SYSTEM_SCOPE_LIF_PROFILE_JR_MODE_2B_BOTH_ENABLED);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
        }

        else if (same_interface_bits == JR_COMP_MODE_ONLY_SYS_SCOPE_ENABLED_BY_SOC_PROPERTIES)
        {

            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_SAME_INTERFACE_FILTER,
                                       SYSTEM_SCOPE_LIF_PROFILE_JR_MODE_1B_ENABLED);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            if (orientation > 0)
            {

                dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_SAME_INTERFACE_FILTER,
                                           SYSTEM_SCOPE_ENABLED_AND_ORIENTATION_ENABLED);
                SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            }
        }
    }
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
ingress_eth_termination_mapping_table_init(
    int unit)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_ETHERNET_TERMINATION_ACTION, &entry_handle_id));

    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_IS_CONTEXT_L3_LIF, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PTC_CS_PROFILE_VTT2, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PTC_ROUTING_ENABLE_PROFILE_VTT1, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_ROUTING_ENABLE, TRUE);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PACKET_IS_COMPATIBLE_MC, FALSE);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_MY_MAC, TRUE);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_LAYER_TERMINATION, INST_SINGLE, TRUE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_IS_CONTEXT_L3_LIF, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PTC_CS_PROFILE_VTT2, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PTC_ROUTING_ENABLE_PROFILE_VTT1, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_ROUTING_ENABLE, TRUE);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PACKET_IS_COMPATIBLE_MC, TRUE);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_MY_MAC, FALSE);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_LAYER_TERMINATION, INST_SINGLE, TRUE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_IS_CONTEXT_L3_LIF, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PTC_CS_PROFILE_VTT2, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PTC_ROUTING_ENABLE_PROFILE_VTT1, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_ROUTING_ENABLE, TRUE);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PACKET_IS_COMPATIBLE_MC, TRUE);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_MY_MAC, TRUE);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_LAYER_TERMINATION, INST_SINGLE, TRUE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_CONTEXT_L3_LIF, TRUE);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PTC_CS_PROFILE_VTT2, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PTC_ROUTING_ENABLE_PROFILE_VTT1, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_ROUTING_ENABLE, TRUE);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PACKET_IS_COMPATIBLE_MC, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_MY_MAC, FALSE);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_LAYER_TERMINATION, INST_SINGLE, TRUE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_IS_CONTEXT_L3_LIF, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PTC_CS_PROFILE_VTT2, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PTC_ROUTING_ENABLE_PROFILE_VTT1, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PACKET_IS_COMPATIBLE_MC, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_ROUTING_ENABLE, FALSE);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_MY_MAC, TRUE);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_LAYER_TERMINATION, INST_SINGLE, FALSE);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_INGRESS_TERMINATION_TRAP_ENABLE, INST_SINGLE,
                                 TRUE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_IS_CONTEXT_L3_LIF, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PTC_ROUTING_ENABLE_PROFILE_VTT1,
                               DBAL_ENUM_FVAL_PTC_ROUTING_ENABLE_PROFILE_VTT1_ALWAYSTERMINATE);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PTC_CS_PROFILE_VTT2, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);

    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_IS_ROUTING_ENABLE, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PACKET_IS_COMPATIBLE_MC, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_IS_MY_MAC, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_LAYER_TERMINATION, INST_SINGLE, TRUE);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_INGRESS_TERMINATION_TRAP_ENABLE, INST_SINGLE,
                                 FALSE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_IS_CONTEXT_L3_LIF, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PTC_ROUTING_ENABLE_PROFILE_VTT1, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_IS_ROUTING_ENABLE, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PACKET_IS_COMPATIBLE_MC, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_IS_MY_MAC, DBAL_RANGE_ALL, DBAL_RANGE_ALL);
    dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_PTC_CS_PROFILE_VTT2, DBAL_RANGE_ALL,
                                     DBAL_RANGE_ALL);
    {
        uint32 ptc_profile_never_terminate;
        SHR_IF_ERR_EXIT(dbal_fields_enum_hw_value_get
                        (unit, DBAL_FIELD_PTC_ROUTING_ENABLE_PROFILE_VTT1,
                         DBAL_ENUM_FVAL_PTC_ROUTING_ENABLE_PROFILE_VTT1_NEVERTERMINATE, &ptc_profile_never_terminate));
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PTC_ROUTING_ENABLE_PROFILE_VTT1,
                                   ptc_profile_never_terminate);
    }
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_LAYER_TERMINATION, INST_SINGLE, FALSE);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IS_INGRESS_TERMINATION_TRAP_ENABLE, INST_SINGLE,
                                 FALSE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
egress_erpp_filter_per_fwd_context_map_init(
    int unit)
{

    int system_headers_mode;
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    system_headers_mode = dnx_data_headers.system_headers.system_headers_mode_get(unit);
    if (system_headers_mode == DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO_MODE)
    {

        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ERPP_FWD_CONTEXT_FILTER, &entry_handle_id));
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_EGRESS_FWD_CODE,
                                   DBAL_ENUM_FVAL_EGRESS_FWD_CODE_ETHERNET);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TTL_EQ_0, INST_SINGLE, FALSE);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
egress_global_system_header_configuration_init(
    int unit)
{
    uint32 entry_handle_id;
    int system_headers_mode;
    uint32 max_vsi_value;
    uint32 jr_lb_key_ext_size_bytes = 0;
    uint32 stacking_ext_size_bytes = 0;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    system_headers_mode = dnx_data_headers.system_headers.system_headers_mode_get(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_SYSTEM_HEADER_GLOBAL_CFG, &entry_handle_id));

    SHR_IF_ERR_EXIT(dnx_vsi_count_get(unit, (int *) &max_vsi_value));
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_MAC_IN_MAC_VSI, INST_SINGLE, max_vsi_value + 1);

    if (system_headers_mode == SYSTEM_HEADERS_MODE_JERICHO2_MODE)
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FTMH_LB_KEY_EXT_SIZE, INST_SINGLE,
                                     FTMH_LB_KEY_EXT_SIZE);

        stacking_ext_size_bytes =
            dnx_data_headers.system_headers.jr2_mode_ftmh_stacking_ext_mode_get(unit) ? STACKING_EXT_SIZE : 0;
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FTMH_STACKING_EXT_SIZE, INST_SINGLE,
                                     stacking_ext_size_bytes);
    }
    else
    {

        jr_lb_key_ext_size_bytes = dnx_data_headers.system_headers.jr_mode_ftmh_lb_key_ext_mode_get(unit) ? 1 : 0;
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FTMH_LB_KEY_EXT_SIZE, INST_SINGLE,
                                     jr_lb_key_ext_size_bytes);

        stacking_ext_size_bytes =
            dnx_data_headers.system_headers.jr_mode_ftmh_stacking_ext_mode_get(unit) ? STACKING_EXT_SIZE : 0;
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FTMH_STACKING_EXT_SIZE, INST_SINGLE,
                                     stacking_ext_size_bytes);
    }

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_egress_otmh_global_configuration_init(
    int unit)
{

    uint32 entry_handle_id;
    uint32 outlif_ext_mode = 0, src_ext_enable = 0;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (dnx_data_headers.otmh.feature_get(unit, dnx_data_headers_otmh_otmh_enable))
    {
        outlif_ext_mode = dnx_data_headers.otmh.otmh_outlif_ext_mode_get(unit);
        src_ext_enable = dnx_data_headers.otmh.otmh_src_ext_enable_get(unit);

        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_TMOTMHFORMATS, &entry_handle_id));

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OUTLIF_EXT_MODE, INST_SINGLE, outlif_ext_mode);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SRC_PORT_EXT, INST_SINGLE, src_ext_enable);

        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_egress_bypass_fifo_almost_full_threshold_init(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (dnx_data_device.general.feature_get(unit, dnx_data_device_general_ignore_mdb_sample_diff))
    {

        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ETPP_BYPASS_FIFO_ALMOST_FULL_THRESHOLD, &entry_handle_id));

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_BYPASS_FIFO_ALMOST_FULL_THRESHOLD, INST_SINGLE,
                                     2);

        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_force_bubble_cfg_init(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_SYSTEM_FORCE_BUBBLE_CFG, &entry_handle_id));

    if (dnx_data_mdb.feature.feature_get(unit, dnx_data_mdb_feature_bubble_pulse_width_too_short))
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FORCE_BUBBLES_INGRESS, INST_SINGLE, 1);
    }
    else
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FORCE_BUBBLE_IGNORE_PULSE_WIDTH, INST_SINGLE, 1);
    }
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_SYNC_COUNTER, INST_SINGLE,
                                 FORCE_BUBBLE_SYNC_COUNTER(unit));
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ALMOST_FULL_ENABLE, INST_SINGLE, 0);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;

}

static shr_error_e
dnx_egress_estimated_bta_btr_cfg_init(
    int unit)
{
    uint32 entry_handle_id;
    int system_headers_mode;
    uint32 udh_type_len[DNX_DATA_MAX_FIELD_UDH_TYPE_COUNT];
    int btr_sop_delta = 0;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_egress_estimated_bta_btr_hw_config))
    {
        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ERPP_ESTIMATED_BTR_HEADERS_PROFILE, &entry_handle_id));
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_TERMINATE_BY_PORT, TRUE);
        dbal_entry_key_field32_range_set(unit, entry_handle_id, DBAL_FIELD_TERMINATE_BY_CTX, DBAL_RANGE_ALL,
                                         DBAL_RANGE_ALL);

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TERMINATE_SYSTEM_HEADERS, INST_SINGLE, TRUE);

        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TERMINATE_NETWORK_HEADERS, INST_SINGLE, TRUE);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

        system_headers_mode = dnx_data_headers.system_headers.system_headers_mode_get(unit);
        if (system_headers_mode == dnx_data_headers.system_headers.system_headers_mode_jericho_get(unit))
        {
            SHR_IF_ERR_EXIT(dnx_field_udh_len_jericho_mode_get(unit, DNX_DATA_MAX_FIELD_UDH_TYPE_COUNT, udh_type_len));
            for (int i = 0; i < DNX_DATA_MAX_FIELD_UDH_TYPE_COUNT; i++)
            {
                btr_sop_delta += udh_type_len[i];
            }
        }

        SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_ESTIMATED_BTA_BTR_CONFIG, &entry_handle_id));
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_BTR_SOP_DELTA, INST_SINGLE, btr_sop_delta);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_erpp_fifo_threshold_config_init(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ERPP_FIFO_ALMOST_FULL_THRESHOLD_CONFIG, &entry_handle_id));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PRP_WAIT_FOR_GLEM_FIFO, INST_SINGLE, 4);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PRP_SAVE_NETWORK_HEADER_FIFO, INST_SINGLE, 4);
    if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_erpp_threshold_prp_per_port_info))
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PRP_PER_PORT_INFO_FIFO, INST_SINGLE, 4);
    }
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;

}

static shr_error_e
dnx_pp_init_bridge_lookup_db_verify(
    int unit)
{
#ifndef ADAPTER_SERVER_MODE
    int capacity;
#endif
    SHR_FUNC_INIT_VARS(unit);

#ifndef ADAPTER_SERVER_MODE
    if (dnx_data_pp.application.vtt1_lookup_by_exem1_get(unit))
    {

        SHR_IF_ERR_EXIT(mdb_get_capacity(unit, DBAL_PHYSICAL_TABLE_SEXEM_1, &capacity));
        if (capacity == 0)
        {
            SHR_ERR_EXIT(BCM_E_PARAM, "vtt1_lookup_by_exem1=1, but EXEM_1 size=0");
        }
        SHR_IF_ERR_EXIT(mdb_get_capacity(unit, DBAL_PHYSICAL_TABLE_ISEM_1, &capacity));
        if (capacity != 0)
        {
            SHR_ERR_EXIT(BCM_E_PARAM, "vtt1_lookup_by_exem1=1, but ISEM1 size > 0");
        }
    }
exit:
#endif
    SHR_FUNC_EXIT;
}

static shr_error_e
egress_current_next_protocol_config_table_init(
    int unit)
{

    int nof_current_next_protocol_entries;
    int entry;

    SHR_FUNC_INIT_VARS(unit);

    nof_current_next_protocol_entries =
        sizeof(current_next_protocol_config_map) / sizeof(current_next_protocol_config_table_t);

    for (entry = 0; entry < nof_current_next_protocol_entries; entry++)
    {

        SHR_IF_ERR_EXIT(dnx_init_pp_egress_current_next_protocol_config_table_configure
                        (unit, current_next_protocol_config_map[entry].current_protocol_type,
                         current_next_protocol_config_map[entry].current_protocol_namespace,
                         current_next_protocol_config_map[entry].current_next_protocol));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
ingress_prt_recycle_command_configuration_init(
    int unit)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_PP_RECYCLE_COMMAND, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_RECYCLE_CMD,
                               DBAL_ENUM_FVAL_RECYCLE_CMD_PRT_PROFILE_NONE);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, DBAL_CORE_ALL);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RECYCLE_CMD_PRT_PROFILE, INST_SINGLE,
                                 DBAL_ENUM_FVAL_RECYCLE_CMD_PRT_PROFILE_NONE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_RECYCLE_CMD, 2);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, DBAL_CORE_ALL);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RECYCLE_CMD_PRT_PROFILE, INST_SINGLE,
                                 DBAL_ENUM_FVAL_RECYCLE_CMD_PRT_PROFILE_PTCH2);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_RECYCLE_CMD,
                               DBAL_ENUM_FVAL_RECYCLE_CMD_PRT_PROFILE_ETH_APPEND64);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, DBAL_CORE_ALL);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RECYCLE_CMD_PRT_PROFILE, INST_SINGLE,
                                 DBAL_ENUM_FVAL_RECYCLE_CMD_PRT_PROFILE_ETH_APPEND64);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IRPP_1ST_PARSER_PARSER_CONTEXT, INST_SINGLE,
                                 DBAL_ENUM_FVAL_IRPP_1ST_PARSER_PARSER_CONTEXT_ETH_A1);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_RECYCLE_CMD,
                               DBAL_ENUM_FVAL_RECYCLE_CMD_PRT_PROFILE_802_1BR_TYPE1);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, DBAL_CORE_ALL);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RECYCLE_CMD_PRT_PROFILE, INST_SINGLE,
                                 DBAL_ENUM_FVAL_RECYCLE_CMD_PRT_PROFILE_802_1BR_TYPE1);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_RECYCLE_CMD,
                               DBAL_ENUM_FVAL_RECYCLE_CMD_PRT_PROFILE_802_1BR_TYPE2);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, DBAL_CORE_ALL);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RECYCLE_CMD_PRT_PROFILE, INST_SINGLE,
                                 DBAL_ENUM_FVAL_RECYCLE_CMD_PRT_PROFILE_802_1BR_TYPE2);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_RECYCLE_CMD,
                               DBAL_ENUM_FVAL_RECYCLE_CMD_PRT_PROFILE_COE);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, DBAL_CORE_ALL);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RECYCLE_CMD_PRT_PROFILE, INST_SINGLE,
                                 DBAL_ENUM_FVAL_RECYCLE_CMD_PRT_PROFILE_COE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
ingress_prt_configuration_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(ingress_prt_recycle_command_configuration_init(unit));

exit:
    SHR_FUNC_EXIT;
}

static const per_layer_protocol_t per_layer_protocol[] = {

    {DBAL_ENUM_FVAL_LAYER_TYPES_INITIALIZATION, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE,
     FALSE, FALSE, FALSE, FALSE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_ETHERNET, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE,
     FALSE, FALSE, FALSE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_IPV4, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE,
     FALSE, FALSE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_IPV6, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE,
     FALSE, FALSE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_MPLS, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE,
     FALSE, FALSE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_ARP, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE,
     FALSE, FALSE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_FCOE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE,
     FALSE, FALSE, FALSE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_TCP, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, FALSE,
     FALSE,
     FALSE, FALSE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_UDP, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE,
     FALSE,
     FALSE, FALSE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_BFD_SINGLE_HOP, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, FALSE,
     FALSE,
     FALSE, FALSE, FALSE, FALSE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_BFD_MULTI_HOP, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,
     FALSE,
     FALSE, FALSE, FALSE, FALSE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_PTP, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, FALSE, FALSE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_Y_1731, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE,
     FALSE,
     FALSE, FALSE, FALSE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_ICMP, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,
     TRUE,
     FALSE, FALSE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_BIER_NON_MPLS, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE,
     FALSE,
     FALSE, FALSE, FALSE, TRUE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_IN_BIER_BASE_EG_BIER_MPLS, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, FALSE, FALSE,
     FALSE,
     FALSE, FALSE, FALSE, TRUE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_RCH, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE,
     FALSE, FALSE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_PPPOE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, FALSE, FALSE, FALSE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_SRV6_ENDPOINT, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, FALSE, FALSE, FALSE,
     FALSE, FALSE, FALSE, FALSE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_IGMP, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE,
     FALSE, FALSE, TRUE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_ITMH, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE,
     FALSE, FALSE, FALSE, FALSE},
    {DBAL_ENUM_FVAL_LAYER_TYPES_MPLS_UNTERM, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE}
};

static shr_error_e
dnx2_ingress_egress_per_layer_protocol_configuration_init(
    int unit)
{
    int entry;
    int nof_layres_to_config;
    uint32 ingress_layer_check[DBAL_NOF_ENUM_LAYER_TYPES_VALUES] = { 0 };

    SHR_FUNC_INIT_VARS(unit);

    nof_layres_to_config = sizeof(per_layer_protocol) / sizeof(per_layer_protocol_t);

    for (entry = 0; entry < nof_layres_to_config; entry++)
    {

        SHR_IF_ERR_EXIT(ingress_per_layer_protocol_configuration(unit, per_layer_protocol[entry].layer_type_enum_val,
                                                                 per_layer_protocol[entry].is_ethernet,
                                                                 per_layer_protocol[entry].is_arp,
                                                                 per_layer_protocol[entry].is_ipv4,
                                                                 per_layer_protocol[entry].is_ipv6,
                                                                 per_layer_protocol[entry].is_mpls_term,
                                                                 per_layer_protocol[entry].is_mpls_fwd,
                                                                 per_layer_protocol[entry].is_udp,
                                                                 per_layer_protocol[entry].is_bfd_single_hop,
                                                                 per_layer_protocol[entry].is_bfd_multi_hop,
                                                                 per_layer_protocol[entry].is_icmpv6,
                                                                 per_layer_protocol[entry].is_igmp,
                                                                 per_layer_protocol[entry].is_8021_x_2,
                                                                 per_layer_protocol[entry].is_icmp,
                                                                 per_layer_protocol[entry].is_bier_mpls,
                                                                 per_layer_protocol[entry].is_bier_ti));
        ingress_layer_check[per_layer_protocol[entry].layer_type_enum_val] = 1;
    }

    if (!dnx_data_mpls.general.mpls_speculative_learning_handling_get(unit))
    {
        for (entry = 0; entry < DBAL_NOF_ENUM_LAYER_TYPES_VALUES; entry++)
        {
            if (ingress_layer_check[entry] == 0)
            {
                SHR_IF_ERR_EXIT(ingress_layer_protocol_allow_speculative_learning(unit, entry, 1));
            }
        }
    }

    for (entry = 0; entry < nof_layres_to_config; entry++)
    {

        SHR_IF_ERR_EXIT(egress_per_layer_protocol_configuration(unit, per_layer_protocol[entry].layer_type_enum_val,
                                                                per_layer_protocol[entry].is_ipv4,
                                                                per_layer_protocol[entry].is_ipv6,
                                                                per_layer_protocol[entry].is_mpls_term,
                                                                per_layer_protocol[entry].is_oam,
                                                                per_layer_protocol[entry].is_tcp,
                                                                per_layer_protocol[entry].is_udp));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
ingress_ecologic_srv6_segment_endpoint_init(
    int unit)
{
    uint32 access_id;
    uint32 entry_handle_id;
    uint32 layer_qualifier;
    uint32 layer_qualifier_mask;
    ecol_ffc_t ecol_ffc;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    sal_memset(&ecol_ffc, 0, sizeof(ecol_ffc_t));

    SHR_IF_ERR_EXIT(dbal_fields_enum_hw_value_get
                    (unit, DBAL_FIELD_ECOL_CONTEXT_ID, DBAL_ENUM_FVAL_ECOL_CONTEXT_ID_SRV6_SEGMENT_ENDPOINT,
                     &access_id));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ECOL_IDENTIFICATION_CAM, &entry_handle_id));

    SHR_IF_ERR_EXIT(dbal_entry_handle_access_id_set(unit, entry_handle_id, access_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPE_PREVIOUS_LAYER,
                               DBAL_ENUM_FVAL_LAYER_TYPES_SRV6_ENDPOINT);
    layer_qualifier_mask = 0;
    LAYER_QUALIFIER_SRV6_SEGMENT_LEFT_IS_ZERO_SET(&layer_qualifier_mask, TRUE);
    LAYER_QUALIFIER_SRV6_SEGMENT_LEFT_IS_ONE_SET(&layer_qualifier_mask, TRUE);

    layer_qualifier = 0;
    LAYER_QUALIFIER_SRV6_SEGMENT_LEFT_IS_ZERO_SET(&layer_qualifier, FALSE);
    LAYER_QUALIFIER_SRV6_SEGMENT_LEFT_IS_ONE_SET(&layer_qualifier, FALSE);

    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_LAYER_QUALIFIER_PREVIOUSLAYER, layer_qualifier,
                                      layer_qualifier_mask);

    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPE_CURRENT_LAYER,
                                      DBAL_ENUM_FVAL_LAYER_TYPES_INITIALIZATION, 0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_LAYER_QUALIFIER_CURRENT_LAYER, 0, 0);

    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_ECOL_RCY_FWD_PROFILE, 0, 0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_ECOL_RCY_SNP_PROFILE, 0, 0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_ECOL_RCY_MRR_PROFILE, 0, 0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_ECOL_PP_PORT_PROFILE, 0, 0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_ECOL_PTC_PROFILE,
                                      DBAL_ENUM_FVAL_ECOL_PTC_PROFILE_ENABLE, 0x3);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_VALID, INST_SINGLE, TRUE);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_ECOL_CONTEXT_ATTRIBUTES, entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_CONTEXT_ID,
                               DBAL_ENUM_FVAL_ECOL_CONTEXT_ID_SRV6_SEGMENT_ENDPOINT);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_VALID, INST_SINGLE, TRUE);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_FFC_INSTRUCTION_0, INST_SINGLE, 0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_FFC_INSTRUCTION_1, INST_SINGLE, 0);

    ecol_ffc.opcode = 0;
    ecol_ffc.index = 7;
    ecol_ffc.field_offset = (144 * 8 - 3 * 8 - 8);
    ecol_ffc.field_size = 7;
    ecol_ffc.key_offset = 0;

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_FFC_INSTRUCTION_2, INST_SINGLE,
                                 BUILD_ECOL_FFC_INSTRUCTION_16(ecol_ffc));

    sal_memset(&ecol_ffc, 0, sizeof(ecol_ffc_t));
    ecol_ffc.opcode = 0;
    ecol_ffc.index = 7;
    ecol_ffc.field_offset = (144 * 8 - 3 * 8 - 8 + 7);
    ecol_ffc.field_size = 0;
    ecol_ffc.key_offset = 0;
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_FFC_INSTRUCTION_0, INST_SINGLE,
                                 BUILD_ECOL_FFC_INSTRUCTION_16(ecol_ffc));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_FFC_INSTRUCTION_1, INST_SINGLE,
                                 BUILD_ECOL_FFC_INSTRUCTION_16(ecol_ffc));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_BTC_OFFSET_BASE_IDX, INST_SINGLE,
                                 DBAL_ENUM_FVAL_ECOL_OFFSET_BASE_IDX_PARSING_LAYER_MINUS_ONE_OFFSET);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_BTC_OFFSET_SHIFT_IN_BYTES, INST_SINGLE, 0x08);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_HEADER_SIZE_MODE, INST_SINGLE,
                                 DBAL_ENUM_FVAL_ECOL_HEADER_SIZE_MODE_USE_CAM_TABLE);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_HEADER_SIZE_INDEX, INST_SINGLE,
                                 DBAL_ENUM_FVAL_ECOL_HEADER_SIZE_INDEX_SRV6_SEGMENT_ENDPOINT);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_NOF_HEADERS_OP_B_SRC, INST_SINGLE,
                                 DBAL_ENUM_FVAL_ECOL_NOF_HEADERS_OP_B_SRC_USE_CFG);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_NOF_HEADERS_OP_B_CFG, INST_SINGLE, 0x1);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_NOF_HEADERS_CALCULATION_MODE, INST_SINGLE,
                                 DBAL_ENUM_FVAL_ECOL_NOF_HEADERS_CALCULATION_MODE_OP_A_MINUS_OP_B);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_BTC_OFFSET_ADD_MODE, INST_SINGLE,
                                 DBAL_ENUM_FVAL_ECOL_BTC_OFFSET_ADD_MODE_SHIFT);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_BTK_OFFSET_BASE_IDX, INST_SINGLE,
                                 DBAL_ENUM_FVAL_ECOL_OFFSET_BASE_IDX_PARSING_LAYER_MINUS_ONE_OFFSET);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_BTK_OFFSET_SHIFT_IN_BYTES, INST_SINGLE, 0x8);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_ECOL_HEADER_SIZE_CAM, entry_handle_id));

    SHR_IF_ERR_EXIT(dbal_fields_enum_hw_value_get
                    (unit, DBAL_FIELD_ECOL_HEADER_SIZE_INDEX,
                     DBAL_ENUM_FVAL_ECOL_HEADER_SIZE_INDEX_SRV6_SEGMENT_ENDPOINT, &access_id));

    SHR_IF_ERR_EXIT(dbal_entry_handle_access_id_set(unit, entry_handle_id, access_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_HEADER_SIZE_INDEX,
                               DBAL_ENUM_FVAL_ECOL_HEADER_SIZE_INDEX_SRV6_SEGMENT_ENDPOINT);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_VARIABLE_0, 0, 0);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_VALID, INST_SINGLE, TRUE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_ECOL_HEADER_SIZE, entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_HEADER_SIZE_INDEX,
                               DBAL_ENUM_FVAL_ECOL_HEADER_SIZE_INDEX_SRV6_SEGMENT_ENDPOINT);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_HEADER_SIZE, INST_SINGLE, 4);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
ingress_ecologic_srv6_egress_tunnel_1_pass_init(
    int unit)
{
    uint32 access_id;
    uint32 entry_handle_id;
    uint32 layer_qualifier;
    uint32 layer_qualifier_mask;
    uint32 srv6_sl_0_additionl_header_hw_val;
    ecol_ffc_t ecol_ffc;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dbal_fields_enum_hw_value_get
                    (unit, DBAL_FIELD_ECOL_CONTEXT_ID, DBAL_ENUM_FVAL_ECOL_CONTEXT_ID_SRV6_EGRESS_NODE_1_PASS,
                     &access_id));
    SHR_IF_ERR_EXIT(dbal_fields_enum_hw_value_get
                    (unit, DBAL_FIELD_IPV6_QUALIFIER_ADDITIONAL_HEADER_1ST,
                     DBAL_ENUM_FVAL_IPV6_ADDITIONAL_HEADER_IPV6_SRV6_SL_0, &srv6_sl_0_additionl_header_hw_val));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ECOL_IDENTIFICATION_CAM, &entry_handle_id));

    SHR_IF_ERR_EXIT(dbal_entry_handle_access_id_set(unit, entry_handle_id, access_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPE_PREVIOUS_LAYER,
                               DBAL_ENUM_FVAL_LAYER_TYPES_IPV6);
    layer_qualifier_mask = 0;
    LAYER_QUALIFIER_IPV6_1ST_ADD_HEADER_EXISTS_SET(&layer_qualifier_mask, 1);
    LAYER_QUALIFIER_IPV6_1ST_ADD_HEADER_SET(&layer_qualifier_mask, 0x1F);
    LAYER_QUALIFIER_IPV6_2ND_ADD_HEADER_SRV6_SINGLE_PASS_TERM_SET(&layer_qualifier_mask, 1);

    layer_qualifier = 0;
    LAYER_QUALIFIER_IPV6_1ST_ADD_HEADER_EXISTS_SET(&layer_qualifier, 1);
    LAYER_QUALIFIER_IPV6_1ST_ADD_HEADER_SET(&layer_qualifier, srv6_sl_0_additionl_header_hw_val);
    LAYER_QUALIFIER_IPV6_2ND_ADD_HEADER_SRV6_SINGLE_PASS_TERM_SET(&layer_qualifier, 1);

    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_LAYER_QUALIFIER_PREVIOUSLAYER, layer_qualifier,
                                      layer_qualifier_mask);

    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPE_CURRENT_LAYER,
                                      DBAL_ENUM_FVAL_LAYER_TYPES_INITIALIZATION, 0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_LAYER_QUALIFIER_CURRENT_LAYER, 0, 0);

    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_ECOL_RCY_FWD_PROFILE, 0, 0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_ECOL_RCY_SNP_PROFILE, 0, 0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_ECOL_RCY_MRR_PROFILE, 0, 0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_ECOL_PP_PORT_PROFILE, 0, 0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_ECOL_PTC_PROFILE,
                                      DBAL_ENUM_FVAL_ECOL_PTC_PROFILE_ENABLE, 0x3);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_VALID, INST_SINGLE, TRUE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_ECOL_CONTEXT_ATTRIBUTES, entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_CONTEXT_ID,
                               DBAL_ENUM_FVAL_ECOL_CONTEXT_ID_SRV6_EGRESS_NODE_1_PASS);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_VALID, INST_SINGLE, TRUE);

    ecol_ffc.opcode = 0;
    ecol_ffc.index = 0;
    ecol_ffc.field_offset = (128 + 64 - 16);
    ecol_ffc.field_size = 6;
    ecol_ffc.key_offset = 3;
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_FFC_INSTRUCTION_2, INST_SINGLE,
                                 BUILD_ECOL_FFC_INSTRUCTION_16(ecol_ffc));

    sal_memset(&ecol_ffc, 0, sizeof(ecol_ffc_t));
    ecol_ffc.opcode = 0;
    ecol_ffc.index = 0;
    ecol_ffc.field_offset = (128 + 64 - 32);
    ecol_ffc.field_size = 0;
    ecol_ffc.key_offset = 0;
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_FFC_INSTRUCTION_0, INST_SINGLE,
                                 BUILD_ECOL_FFC_INSTRUCTION_16(ecol_ffc));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_FFC_INSTRUCTION_1, INST_SINGLE,
                                 BUILD_ECOL_FFC_INSTRUCTION_16(ecol_ffc));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_BTC_OFFSET_BASE_IDX, INST_SINGLE,
                                 DBAL_ENUM_FVAL_ECOL_OFFSET_BASE_IDX_PARSING_LAYER_OFFSET);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_BTC_OFFSET_SHIFT_IN_BYTES, INST_SINGLE, 0);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_HEADER_SIZE_MODE, INST_SINGLE,
                                 DBAL_ENUM_FVAL_ECOL_HEADER_SIZE_MODE_USE_CAM_TABLE);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_HEADER_SIZE_INDEX, INST_SINGLE,
                                 DBAL_ENUM_FVAL_ECOL_HEADER_SIZE_INDEX_SRV6_EGRESS_NODE);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_NOF_HEADERS_OP_B_SRC, INST_SINGLE,
                                 DBAL_ENUM_FVAL_ECOL_NOF_HEADERS_OP_B_SRC_USE_CFG);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_NOF_HEADERS_OP_B_CFG, INST_SINGLE, 16);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_NOF_HEADERS_CALCULATION_MODE, INST_SINGLE,
                                 DBAL_ENUM_FVAL_ECOL_NOF_HEADERS_CALCULATION_MODE_OP_A_MINUS_OP_B);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_BTC_OFFSET_ADD_MODE, INST_SINGLE,
                                 DBAL_ENUM_FVAL_ECOL_BTC_OFFSET_ADD_MODE_SHIFT);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_BTK_OFFSET_BASE_IDX, INST_SINGLE,
                                 DBAL_ENUM_FVAL_ECOL_OFFSET_BASE_IDX_PARSING_LAYER_OFFSET);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_BTK_OFFSET_SHIFT_IN_BYTES, INST_SINGLE, 0);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_ECOL_HEADER_SIZE_CAM, entry_handle_id));

    SHR_IF_ERR_EXIT(dbal_fields_enum_hw_value_get
                    (unit, DBAL_FIELD_ECOL_HEADER_SIZE_INDEX, DBAL_ENUM_FVAL_ECOL_HEADER_SIZE_INDEX_SRV6_EGRESS_NODE,
                     &access_id));

    SHR_IF_ERR_EXIT(dbal_entry_handle_access_id_set(unit, entry_handle_id, access_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_HEADER_SIZE_INDEX,
                               DBAL_ENUM_FVAL_ECOL_HEADER_SIZE_INDEX_SRV6_EGRESS_NODE);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_VARIABLE_0, 0, 0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_VALID, INST_SINGLE, TRUE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_ECOL_HEADER_SIZE, entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_HEADER_SIZE_INDEX,
                               DBAL_ENUM_FVAL_ECOL_HEADER_SIZE_INDEX_SRV6_EGRESS_NODE);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_HEADER_SIZE, INST_SINGLE, 0);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
ingress_ecologic_srv6_egress_tunnel_2_pass_init(
    int unit)
{
    uint32 access_id;
    uint32 entry_handle_id;
    uint32 layer_qualifier;
    uint32 layer_qualifier_mask;
    uint32 srv6_sl_0_additionl_header_hw_val;
    uint32 btc_offset;
    ecol_ffc_t ecol_ffc;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dbal_fields_enum_hw_value_get
                    (unit, DBAL_FIELD_ECOL_CONTEXT_ID, DBAL_ENUM_FVAL_ECOL_CONTEXT_ID_SRV6_EGRESS_NODE_2_PASS,
                     &access_id));
    SHR_IF_ERR_EXIT(dbal_fields_enum_hw_value_get
                    (unit, DBAL_FIELD_IPV6_QUALIFIER_ADDITIONAL_HEADER_1ST,
                     DBAL_ENUM_FVAL_IPV6_ADDITIONAL_HEADER_IPV6_SRV6_SL_0, &srv6_sl_0_additionl_header_hw_val));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_ECOL_IDENTIFICATION_CAM, &entry_handle_id));

    SHR_IF_ERR_EXIT(dbal_entry_handle_access_id_set(unit, entry_handle_id, access_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPE_PREVIOUS_LAYER,
                               DBAL_ENUM_FVAL_LAYER_TYPES_IPV6);
    layer_qualifier_mask = 0;
    LAYER_QUALIFIER_IPV6_1ST_ADD_HEADER_EXISTS_SET(&layer_qualifier_mask, 1);
    LAYER_QUALIFIER_IPV6_1ST_ADD_HEADER_SET(&layer_qualifier_mask, 0x1F);
    LAYER_QUALIFIER_IPV6_2ND_ADD_HEADER_SRV6_SINGLE_PASS_TERM_SET(&layer_qualifier_mask, 1);

    layer_qualifier = 0;
    LAYER_QUALIFIER_IPV6_1ST_ADD_HEADER_EXISTS_SET(&layer_qualifier, 1);
    LAYER_QUALIFIER_IPV6_1ST_ADD_HEADER_SET(&layer_qualifier, srv6_sl_0_additionl_header_hw_val);
    LAYER_QUALIFIER_IPV6_2ND_ADD_HEADER_SRV6_SINGLE_PASS_TERM_SET(&layer_qualifier, 0);

    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_LAYER_QUALIFIER_PREVIOUSLAYER, layer_qualifier,
                                      layer_qualifier_mask);

    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPE_CURRENT_LAYER,
                                      DBAL_ENUM_FVAL_LAYER_TYPES_INITIALIZATION, 0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_LAYER_QUALIFIER_CURRENT_LAYER, 0, 0);

    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_ECOL_RCY_FWD_PROFILE, 0, 0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_ECOL_RCY_SNP_PROFILE, 0, 0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_ECOL_RCY_MRR_PROFILE, 0, 0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_ECOL_PP_PORT_PROFILE, 0, 0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_ECOL_PTC_PROFILE,
                                      DBAL_ENUM_FVAL_ECOL_PTC_PROFILE_ENABLE, 0x3);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_VALID, INST_SINGLE, TRUE);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, DBAL_TABLE_ECOL_CONTEXT_ATTRIBUTES, entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_CONTEXT_ID,
                               DBAL_ENUM_FVAL_ECOL_CONTEXT_ID_SRV6_EGRESS_NODE_2_PASS);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_VALID, INST_SINGLE, TRUE);

    sal_memset(&ecol_ffc, 0, sizeof(ecol_ffc_t));
    ecol_ffc.opcode = 0;
    ecol_ffc.index = 0;
    ecol_ffc.field_offset = (128 + 64 - 32);
    ecol_ffc.field_size = 0;
    ecol_ffc.key_offset = 0;
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_FFC_INSTRUCTION_0, INST_SINGLE,
                                 BUILD_ECOL_FFC_INSTRUCTION_16(ecol_ffc));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_FFC_INSTRUCTION_1, INST_SINGLE,
                                 BUILD_ECOL_FFC_INSTRUCTION_16(ecol_ffc));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_FFC_INSTRUCTION_2, INST_SINGLE,
                                 BUILD_ECOL_FFC_INSTRUCTION_16(ecol_ffc));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_BTK_OFFSET_BASE_IDX, INST_SINGLE,
                                 DBAL_ENUM_FVAL_ECOL_OFFSET_BASE_IDX_PARSING_LAYER_OFFSET);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_BTK_OFFSET_SHIFT_IN_BYTES, INST_SINGLE, 0);

    btc_offset = (16 * (dnx_data_srv6.termination.max_nof_terminated_sids_usp_1pass_get(unit)));
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_BTC_OFFSET_BASE_IDX, INST_SINGLE,
                                 DBAL_ENUM_FVAL_ECOL_OFFSET_BASE_IDX_PARSING_LAYER_OFFSET);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ECOL_BTC_OFFSET_SHIFT_IN_BYTES, INST_SINGLE,
                                 btc_offset);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

shr_error_e static
ingress_ecologic_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(ingress_ecologic_srv6_segment_endpoint_init(unit));
    SHR_IF_ERR_EXIT(ingress_ecologic_srv6_egress_tunnel_1_pass_init(unit));
    SHR_IF_ERR_EXIT(ingress_ecologic_srv6_egress_tunnel_2_pass_init(unit));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_general_pp_ingress_power_down_set(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_INGRESS_POWER_DOWN, &entry_handle_id));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_POWER_DOWN, INST_SINGLE, 1);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_general_pp_egress_power_down_set(
    int unit)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_EGRESS_POWER_DOWN, &entry_handle_id));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_POWER_DOWN, INST_SINGLE, 1);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_general_pp_pem_power_down_set(
    int unit,
    int pem_block_id)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEM_POWER_DOWN, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PEM_BLOCK_ID, pem_block_id);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_POWER_DOWN, INST_SINGLE, 1);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_general_pp_power_down_set(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_ingress_power_down_supported))
    {
        SHR_IF_ERR_EXIT(dnx_general_pp_ingress_power_down_set(unit));
    }

    if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_egress_power_down_supported))
    {
        if (dnx_data_nif.global.l1_only_mode_get(unit) == DNX_PORT_NIF_L1_ONLY_MODE_WITHOUT_ILKN)
        {
            if (dnx_data_fabric.general.connect_mode_get(unit) == DNX_FABRIC_CONNECT_MODE_SINGLE_FAP
                || dnx_data_tdm.params.feature_get(unit, dnx_data_tdm_params_egress_bypass_enable))
            {
                SHR_IF_ERR_EXIT(dnx_general_pp_egress_power_down_set(unit));
                if (dnx_data_pp.PEM.feature_get(unit, dnx_data_pp_PEM_clock_power_down))
                {
                    int pem_block_id, pem_block_cnt;
                    pem_block_cnt = 1 << dnx_data_pp.PEM.nof_pem_bits_get(unit);
                    for (pem_block_id = 0; pem_block_id < pem_block_cnt; pem_block_id++)
                    {
                        SHR_IF_ERR_EXIT(dnx_general_pp_pem_power_down_set(unit, pem_block_id));
                    }
                }
            }
        }
    }
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_general_pp_init(
    int unit)
{
    uint8 is_image_standard_1 = FALSE;
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_is_pp_used))
    {
#ifndef ADAPTER_SERVER_MODE
        if (dnx_data_mdb.feature.feature_get(unit, dnx_data_mdb_feature_em_compare_init) && (!SAL_BOOT_PLISIM))
        {
            soc_reg_above_64_val_t data;
            bcm_core_t core;

            soc_reg_t reg = dnx_data_graphical.diag.counters_get(unit, dnx_graphical_spb, 0)->regs[0];

            SHR_IF_ERR_EXIT(dnx_switch_control_mdb_exact_match_false_hit_set(unit, 0));

            SHR_IF_ERR_EXIT(dnx_drv_soc_dnx_soft_init_no_fabric(unit));

            DNXCMN_CORES_ITER(unit, BCM_CORE_ALL, core)
            {
                SHR_IF_ERR_EXIT(soc_reg_above_64_get(unit, reg, core, 0, data));
            }
        }
#endif
        SHR_IF_ERR_EXIT(mdb_db_infos.mdb_em_init_done.set(unit, TRUE));

        if (dnx_data_headers.system_headers.system_headers_mode_get(unit) ==
            DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO_MODE)
        {
            SHR_IF_ERR_EXIT(dnx_multicast_pp_jr1_same_interface_init(unit));
        }
        SHR_IF_ERR_EXIT(dnx_pp_init_bridge_lookup_db_verify(unit));

        SHR_IF_ERR_EXIT(dnx_pp_prgm_default_image_check(unit, &is_image_standard_1));
        if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_application_v1))
        {
            SHR_IF_ERR_EXIT(dnx2_pp_automatic_tables_init(unit));
        }
        SHR_IF_ERR_EXIT(egress_eedb_type_buster_enable_init(unit));
        SHR_IF_ERR_EXIT(egress_eedb_forwarding_domain_vsd_enable_init(unit));
        SHR_IF_ERR_EXIT(egress_eedb_svtag_indication_enable_init(unit));
        SHR_IF_ERR_EXIT(ingress_prt_configuration_init(unit));
        if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_ecologic_support))
        {
            SHR_IF_ERR_EXIT(ingress_ecologic_init(unit));
        }
        SHR_IF_ERR_EXIT(ingress_forwarding_domain_assignment_mode_init(unit));
        SHR_IF_ERR_EXIT(ingress_lbp_general_configuration_init(unit));
        SHR_IF_ERR_EXIT(ingress_eth_termination_mapping_table_init(unit));
        SHR_IF_ERR_EXIT(ingress_lbp_vlan_editing_configuration_init(unit));
        if (dnx_data_headers.system_headers.system_headers_mode_get(unit) ==
            DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO_MODE)
        {
            SHR_IF_ERR_EXIT(ingress_lbp_jer_mode_configuration_init(unit));
        }
        if (dnx_data_lif.in_lif.feature_get(unit, dnx_data_lif_in_lif_separate_ipv4_ipv6_urpf_mode_config))
        {
            SHR_IF_ERR_EXIT(ingress_is_ipv6_header_configuration_init(unit));
        }

        if (dnx_data_elk.general.device_type_get(unit))
        {
            SHR_ERR_EXIT(_SHR_E_CONFIG, "KBP is not supported on this device and/or compilation\n");
        }
        SHR_IF_ERR_EXIT(ingress_egw_full_threshold_set(unit));
        if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_data_path_hw))
        {
            SHR_IF_ERR_EXIT(ingress_ippe_traffic_enable(unit));
        }
        if (dnx_data_ingress_cs.parser.feature_get(unit, dnx_data_ingress_cs_parser_parsing_context_map_enable))
        {
            SHR_IF_ERR_EXIT(ingress_ippe_parser_context_mapping(unit));
        }
        if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_l4_protocol_fields_config_enable))
        {
            SHR_IF_ERR_EXIT(ingress_ippb_l4_protocols_config(unit));
        }
        SHR_IF_ERR_EXIT(ingress_vtt_global_configuration_init(unit));
        SHR_IF_ERR_EXIT(ingress_port_general_configuration_init(unit));
        SHR_IF_ERR_EXIT(ingress_itpp_general_configuration_init(unit));
        if (dnx_data_dev_init.general.feature_get(unit, dnx_data_dev_init_general_da_type_map_enable))
        {
            SHR_IF_ERR_EXIT(ingress_da_type_map_init(unit));
        }
        SHR_IF_ERR_EXIT(ingress_egress_parser_configuration_init(unit));
        SHR_IF_ERR_EXIT(ingress_egress_forwarding_additional_info_configuration_init(unit));
        SHR_IF_ERR_EXIT(ingress_stat_fec_ecmp_mapping_init(unit));
        SHR_IF_ERR_EXIT(egress_prp_general_configuration_init(unit));
        SHR_IF_ERR_EXIT(egress_parser_general_configuration_init(unit));
        SHR_IF_ERR_EXIT(egress_selected_outlif_table_init(unit));
        SHR_IF_ERR_EXIT(egress_system_headers_lif_extension_configuration_init(unit));
        SHR_IF_ERR_EXIT(egress_system_header_generation_table_init(unit));
        SHR_IF_ERR_EXIT(egress_global_system_header_configuration_init(unit));

        if (dnx_data_port_pp.
            general.feature_get(unit, dnx_data_port_pp_general_split_horizon_per_port_outlif_profile_support))
        {
            SHR_IF_ERR_EXIT(egress_port_outlif_profile_configuration_init(unit));
        }

        SHR_IF_ERR_EXIT(egress_global_inlif_resolution_table_init(unit));
        SHR_IF_ERR_EXIT(egress_global_eedb_configuration_init(unit));
        SHR_IF_ERR_EXIT(egress_exclude_source_filter_configure_init(unit));
        SHR_IF_ERR_EXIT(egress_same_interface_filter_configure_init(unit));
        SHR_IF_ERR_EXIT(egress_mapping_forward_context_configure_init(unit));
        SHR_IF_ERR_EXIT(egress_ingress_trapped_by_fhei_configure_init(unit));
        SHR_IF_ERR_EXIT(ire_packet_generator_init(unit));

        if (is_image_standard_1)
        {
            SHR_IF_ERR_EXIT(dnx2_ingress_egress_per_layer_protocol_configuration_init(unit));
            SHR_IF_ERR_EXIT(ingress_gre_next_protocol_eth_init(unit));
            SHR_IF_ERR_EXIT(ingress_udp_next_protocol_enable_init(unit));
            SHR_IF_ERR_EXIT(dnx_parser_geneve_init(unit));
            SHR_IF_ERR_EXIT(egress_current_next_protocol_config_table_init(unit));
            SHR_IF_ERR_EXIT(egress_additional_headers_profile_init(unit));
            SHR_IF_ERR_EXIT(ingress_map_parsing_ctx_layer_potocol(unit));
            SHR_IF_ERR_EXIT(egress_fhei_mpls_upper_layer_protocol_to_pes_mapping_init(unit));
            SHR_IF_ERR_EXIT(egress_erpp_filter_per_fwd_context_map_init(unit));
        }

        SHR_IF_ERR_EXIT(dnx_field_context_ifwd2_external_tcam_acl_init(unit));
        SHR_IF_ERR_EXIT(dnx_pph_base_size_init(unit));

        if (!is_image_standard_1)
        {
            SHR_IF_ERR_EXIT(bare_metal_configuration_init(unit));
        }

        if (dnx_data_lif.global_lif.null_lif_get(unit) &&
            dnx_data_lif.global_lif.feature_get(unit, dnx_data_lif_global_lif_outlif_profile_in_glem))
        {
            SHR_IF_ERR_EXIT(egress_glem_dummy_entry_configure(unit));
        }

        SHR_IF_ERR_EXIT(egress_cfg_in_lif_null_value_init(unit));
        SHR_IF_ERR_EXIT(dnx_force_bubble_cfg_init(unit));
        SHR_IF_ERR_EXIT(dnx_egress_estimated_bta_btr_cfg_init(unit));
        SHR_IF_ERR_EXIT(dnx_erpp_fifo_threshold_config_init(unit));
        SHR_IF_ERR_EXIT(dnx_egress_otmh_global_configuration_init(unit));
        SHR_IF_ERR_EXIT(dnx_egress_bypass_fifo_almost_full_threshold_init(unit));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_general_pp_power_down_set(unit));
    }

exit:
    SHR_FUNC_EXIT;
}

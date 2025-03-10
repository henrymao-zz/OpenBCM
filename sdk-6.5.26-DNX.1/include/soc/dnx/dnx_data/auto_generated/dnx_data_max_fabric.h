
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifndef _DNX_DATA_MAX_FABRIC_H_

#define _DNX_DATA_MAX_FABRIC_H_




#ifndef BCM_DNX_SUPPORT
#error "This file is for use by DNX family only!"
#endif


#define DNX_DATA_MAX_FABRIC_GENERAL_NOF_LCPLLS (1)

#undef DNX_DATA_MAX_FABRIC_GENERAL_NOF_LCPLLS
#define DNX_DATA_MAX_FABRIC_GENERAL_NOF_LCPLLS (2)


#define DNX_DATA_MAX_FABRIC_GENERAL_FMAC_CLOCK_KHZ (1)

#undef DNX_DATA_MAX_FABRIC_GENERAL_FMAC_CLOCK_KHZ
#define DNX_DATA_MAX_FABRIC_GENERAL_FMAC_CLOCK_KHZ (906250)


#define DNX_DATA_MAX_FABRIC_GENERAL_FMAC_TX_PADDING_MIN_PORT_SPEED (1)

#define DNX_DATA_MAX_FABRIC_GENERAL_NOF_BER_PROJ_ERROR_ANALYZER_COUNTERS (1)

#undef DNX_DATA_MAX_FABRIC_GENERAL_NOF_BER_PROJ_ERROR_ANALYZER_COUNTERS
#define DNX_DATA_MAX_FABRIC_GENERAL_NOF_BER_PROJ_ERROR_ANALYZER_COUNTERS (16)


#define DNX_DATA_MAX_FABRIC_LINKS_NOF_LINKS (1)

#undef DNX_DATA_MAX_FABRIC_LINKS_NOF_LINKS
#define DNX_DATA_MAX_FABRIC_LINKS_NOF_LINKS (192)


#define DNX_DATA_MAX_FABRIC_LINKS_NOF_LINKS_PER_CORE (1)

#undef DNX_DATA_MAX_FABRIC_LINKS_NOF_LINKS_PER_CORE
#define DNX_DATA_MAX_FABRIC_LINKS_NOF_LINKS_PER_CORE (96)


#define DNX_DATA_MAX_FABRIC_LINKS_MAX_LINK_ID (1)

#undef DNX_DATA_MAX_FABRIC_LINKS_MAX_LINK_ID
#define DNX_DATA_MAX_FABRIC_LINKS_MAX_LINK_ID (191)


#define DNX_DATA_MAX_FABRIC_LINKS_USEC_BETWEEN_LOAD_BALANCING_EVENTS (1)

#undef DNX_DATA_MAX_FABRIC_LINKS_USEC_BETWEEN_LOAD_BALANCING_EVENTS
#define DNX_DATA_MAX_FABRIC_LINKS_USEC_BETWEEN_LOAD_BALANCING_EVENTS (1000000)


#define DNX_DATA_MAX_FABRIC_LINKS_KR_FEC_SUPPORTED (1)

#undef DNX_DATA_MAX_FABRIC_LINKS_KR_FEC_SUPPORTED
#define DNX_DATA_MAX_FABRIC_LINKS_KR_FEC_SUPPORTED (1)


#define DNX_DATA_MAX_FABRIC_LINKS_WFD_MAX_HW_WEIGHT (1)

#undef DNX_DATA_MAX_FABRIC_LINKS_WFD_MAX_HW_WEIGHT
#define DNX_DATA_MAX_FABRIC_LINKS_WFD_MAX_HW_WEIGHT (127)


#define DNX_DATA_MAX_FABRIC_LINKS_LOAD_BALANCING_PROFILE_ID_MIN (1)

#undef DNX_DATA_MAX_FABRIC_LINKS_LOAD_BALANCING_PROFILE_ID_MIN
#define DNX_DATA_MAX_FABRIC_LINKS_LOAD_BALANCING_PROFILE_ID_MIN (1)


#define DNX_DATA_MAX_FABRIC_LINKS_LOAD_BALANCING_PROFILE_ID_MAX (1)

#undef DNX_DATA_MAX_FABRIC_LINKS_LOAD_BALANCING_PROFILE_ID_MAX
#define DNX_DATA_MAX_FABRIC_LINKS_LOAD_BALANCING_PROFILE_ID_MAX (15)


#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_INSTANCES_FMAC (1)

#undef DNX_DATA_MAX_FABRIC_BLOCKS_NOF_INSTANCES_FMAC
#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_INSTANCES_FMAC (48)


#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_LINKS_IN_FMAC (1)

#undef DNX_DATA_MAX_FABRIC_BLOCKS_NOF_LINKS_IN_FMAC
#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_LINKS_IN_FMAC (4)


#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_INSTANCES_FSRD (1)

#undef DNX_DATA_MAX_FABRIC_BLOCKS_NOF_INSTANCES_FSRD
#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_INSTANCES_FSRD (24)


#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_LINKS_IN_FSRD (1)

#undef DNX_DATA_MAX_FABRIC_BLOCKS_NOF_LINKS_IN_FSRD
#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_LINKS_IN_FSRD (8)


#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_FMACS_IN_FSRD (1)

#undef DNX_DATA_MAX_FABRIC_BLOCKS_NOF_FMACS_IN_FSRD
#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_FMACS_IN_FSRD (2)


#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_PMS (1)

#undef DNX_DATA_MAX_FABRIC_BLOCKS_NOF_PMS
#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_PMS (24)


#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_LINKS_IN_PM (1)

#undef DNX_DATA_MAX_FABRIC_BLOCKS_NOF_LINKS_IN_PM
#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_LINKS_IN_PM (8)


#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_FMACS_IN_PM (1)

#undef DNX_DATA_MAX_FABRIC_BLOCKS_NOF_FMACS_IN_PM
#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_FMACS_IN_PM (2)


#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_INSTANCES_FDTL (1)

#undef DNX_DATA_MAX_FABRIC_BLOCKS_NOF_INSTANCES_FDTL
#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_INSTANCES_FDTL (2)


#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_LINKS_IN_FDTL (1)

#undef DNX_DATA_MAX_FABRIC_BLOCKS_NOF_LINKS_IN_FDTL
#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_LINKS_IN_FDTL (112)


#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_SBUS_CHAINS (1)

#undef DNX_DATA_MAX_FABRIC_BLOCKS_NOF_SBUS_CHAINS
#define DNX_DATA_MAX_FABRIC_BLOCKS_NOF_SBUS_CHAINS (2)


#define DNX_DATA_MAX_FABRIC_REACHABILITY_RESOLUTION (1)

#undef DNX_DATA_MAX_FABRIC_REACHABILITY_RESOLUTION
#define DNX_DATA_MAX_FABRIC_REACHABILITY_RESOLUTION (32)


#define DNX_DATA_MAX_FABRIC_REACHABILITY_GEN_PERIOD (1)

#undef DNX_DATA_MAX_FABRIC_REACHABILITY_GEN_PERIOD
#define DNX_DATA_MAX_FABRIC_REACHABILITY_GEN_PERIOD (6)


#define DNX_DATA_MAX_FABRIC_REACHABILITY_FULL_CYCLE_PERIOD_NSEC (1)

#undef DNX_DATA_MAX_FABRIC_REACHABILITY_FULL_CYCLE_PERIOD_NSEC
#define DNX_DATA_MAX_FABRIC_REACHABILITY_FULL_CYCLE_PERIOD_NSEC (44800)


#define DNX_DATA_MAX_FABRIC_REACHABILITY_WATCHDOG_RESOLUTION (1)

#undef DNX_DATA_MAX_FABRIC_REACHABILITY_WATCHDOG_RESOLUTION
#define DNX_DATA_MAX_FABRIC_REACHABILITY_WATCHDOG_RESOLUTION (4096)


#define DNX_DATA_MAX_FABRIC_REACHABILITY_WATCHDOG_PERIOD_USEC (1)

#undef DNX_DATA_MAX_FABRIC_REACHABILITY_WATCHDOG_PERIOD_USEC
#define DNX_DATA_MAX_FABRIC_REACHABILITY_WATCHDOG_PERIOD_USEC (100)


#define DNX_DATA_MAX_FABRIC_MESH_MAX_MC_ID (1)

#undef DNX_DATA_MAX_FABRIC_MESH_MAX_MC_ID
#define DNX_DATA_MAX_FABRIC_MESH_MAX_MC_ID (131071)


#define DNX_DATA_MAX_FABRIC_MESH_MAX_NOF_DEST (1)

#undef DNX_DATA_MAX_FABRIC_MESH_MAX_NOF_DEST
#define DNX_DATA_MAX_FABRIC_MESH_MAX_NOF_DEST (3)


#define DNX_DATA_MAX_FABRIC_CELL_NOF_PRIORITIES (1)

#undef DNX_DATA_MAX_FABRIC_CELL_NOF_PRIORITIES
#define DNX_DATA_MAX_FABRIC_CELL_NOF_PRIORITIES (4)


#define DNX_DATA_MAX_FABRIC_CELL_VSC256_MAX_SIZE (1)

#undef DNX_DATA_MAX_FABRIC_CELL_VSC256_MAX_SIZE
#define DNX_DATA_MAX_FABRIC_CELL_VSC256_MAX_SIZE (272)


#define DNX_DATA_MAX_FABRIC_CELL_MAX_VSC_FORMAT_SIZE (1)

#undef DNX_DATA_MAX_FABRIC_CELL_MAX_VSC_FORMAT_SIZE
#define DNX_DATA_MAX_FABRIC_CELL_MAX_VSC_FORMAT_SIZE (256)


#define DNX_DATA_MAX_FABRIC_CELL_SR_CELL_HEADER_OFFSET (1)

#undef DNX_DATA_MAX_FABRIC_CELL_SR_CELL_HEADER_OFFSET
#define DNX_DATA_MAX_FABRIC_CELL_SR_CELL_HEADER_OFFSET (32)


#define DNX_DATA_MAX_FABRIC_CELL_SR_CELL_NOF_INSTANCES (1)

#undef DNX_DATA_MAX_FABRIC_CELL_SR_CELL_NOF_INSTANCES
#define DNX_DATA_MAX_FABRIC_CELL_SR_CELL_NOF_INSTANCES (12)


#define DNX_DATA_MAX_FABRIC_CELL_CTRL_CELLS_INIT_FIFO_EMPTY_ITERATIONS (1)

#undef DNX_DATA_MAX_FABRIC_CELL_CTRL_CELLS_INIT_FIFO_EMPTY_ITERATIONS
#define DNX_DATA_MAX_FABRIC_CELL_CTRL_CELLS_INIT_FIFO_EMPTY_ITERATIONS (36)


#define DNX_DATA_MAX_FABRIC_PIPES_MAX_NOF_PIPES (1)

#undef DNX_DATA_MAX_FABRIC_PIPES_MAX_NOF_PIPES
#define DNX_DATA_MAX_FABRIC_PIPES_MAX_NOF_PIPES (3)


#define DNX_DATA_MAX_FABRIC_PIPES_MAX_NOF_CONTEXTS (1)

#undef DNX_DATA_MAX_FABRIC_PIPES_MAX_NOF_CONTEXTS
#define DNX_DATA_MAX_FABRIC_PIPES_MAX_NOF_CONTEXTS (3)


#define DNX_DATA_MAX_FABRIC_PIPES_MAX_NOF_SUBCONTEXTS (1)

#undef DNX_DATA_MAX_FABRIC_PIPES_MAX_NOF_SUBCONTEXTS
#define DNX_DATA_MAX_FABRIC_PIPES_MAX_NOF_SUBCONTEXTS (6)


#define DNX_DATA_MAX_FABRIC_MESH_TOPOLOGY_MESH_INIT (1)

#undef DNX_DATA_MAX_FABRIC_MESH_TOPOLOGY_MESH_INIT
#define DNX_DATA_MAX_FABRIC_MESH_TOPOLOGY_MESH_INIT (13)


#define DNX_DATA_MAX_FABRIC_MESH_TOPOLOGY_MESH_CONFIG_1 (1)

#undef DNX_DATA_MAX_FABRIC_MESH_TOPOLOGY_MESH_CONFIG_1
#define DNX_DATA_MAX_FABRIC_MESH_TOPOLOGY_MESH_CONFIG_1 (2)


#define DNX_DATA_MAX_FABRIC_CGM_NOF_RCI_LEVELS (1)

#undef DNX_DATA_MAX_FABRIC_CGM_NOF_RCI_LEVELS
#define DNX_DATA_MAX_FABRIC_CGM_NOF_RCI_LEVELS (8)


#define DNX_DATA_MAX_FABRIC_CGM_NOF_RCI_THRESHOLD_LEVELS (1)

#undef DNX_DATA_MAX_FABRIC_CGM_NOF_RCI_THRESHOLD_LEVELS
#define DNX_DATA_MAX_FABRIC_CGM_NOF_RCI_THRESHOLD_LEVELS (3)


#define DNX_DATA_MAX_FABRIC_CGM_EGRESS_DROP_TH_CLOCKS_RESOLUTION (1)

#undef DNX_DATA_MAX_FABRIC_CGM_EGRESS_DROP_TH_CLOCKS_RESOLUTION
#define DNX_DATA_MAX_FABRIC_CGM_EGRESS_DROP_TH_CLOCKS_RESOLUTION (16)


#define DNX_DATA_MAX_FABRIC_CGM_EGRESS_FIFO_FC_THRESHOLD (1)

#undef DNX_DATA_MAX_FABRIC_CGM_EGRESS_FIFO_FC_THRESHOLD
#define DNX_DATA_MAX_FABRIC_CGM_EGRESS_FIFO_FC_THRESHOLD (32)


#define DNX_DATA_MAX_FABRIC_CGM_STATIC_SHAPER_CREDIT_RESOLUTION_BYTES (1)

#undef DNX_DATA_MAX_FABRIC_CGM_STATIC_SHAPER_CREDIT_RESOLUTION_BYTES
#define DNX_DATA_MAX_FABRIC_CGM_STATIC_SHAPER_CREDIT_RESOLUTION_BYTES (31)


#define DNX_DATA_MAX_FABRIC_CGM_CGM_ADAPTIVE_TFL_SHAPER_ZONE_NOF (1)

#undef DNX_DATA_MAX_FABRIC_CGM_CGM_ADAPTIVE_TFL_SHAPER_ZONE_NOF
#define DNX_DATA_MAX_FABRIC_CGM_CGM_ADAPTIVE_TFL_SHAPER_ZONE_NOF (8)


#define DNX_DATA_MAX_FABRIC_CGM_CGM_GLOBAL_CELL_SHAPER_MAX_RATE (1)

#undef DNX_DATA_MAX_FABRIC_CGM_CGM_GLOBAL_CELL_SHAPER_MAX_RATE
#define DNX_DATA_MAX_FABRIC_CGM_CGM_GLOBAL_CELL_SHAPER_MAX_RATE (100000)


#define DNX_DATA_MAX_FABRIC_CGM_RCI_LINK_LEVEL_FACTOR_MAX_VALUE (1)

#undef DNX_DATA_MAX_FABRIC_CGM_RCI_LINK_LEVEL_FACTOR_MAX_VALUE
#define DNX_DATA_MAX_FABRIC_CGM_RCI_LINK_LEVEL_FACTOR_MAX_VALUE (7)


#define DNX_DATA_MAX_FABRIC_CGM_LOCAL_UNICAST_DYNAMIC_WFQ_MAX_THRESHOLD_VALUE (1)

#undef DNX_DATA_MAX_FABRIC_CGM_LOCAL_UNICAST_DYNAMIC_WFQ_MAX_THRESHOLD_VALUE
#define DNX_DATA_MAX_FABRIC_CGM_LOCAL_UNICAST_DYNAMIC_WFQ_MAX_THRESHOLD_VALUE (160)


#define DNX_DATA_MAX_FABRIC_CGM_LOCAL_UNICAST_DYNAMIC_WFQ_HIGH_THRESHOLD (1)

#undef DNX_DATA_MAX_FABRIC_CGM_LOCAL_UNICAST_DYNAMIC_WFQ_HIGH_THRESHOLD
#define DNX_DATA_MAX_FABRIC_CGM_LOCAL_UNICAST_DYNAMIC_WFQ_HIGH_THRESHOLD (120)


#define DNX_DATA_MAX_FABRIC_CGM_LOCAL_UNICAST_DYNAMIC_WFQ_LOW_THRESHOLD (1)

#undef DNX_DATA_MAX_FABRIC_CGM_LOCAL_UNICAST_DYNAMIC_WFQ_LOW_THRESHOLD
#define DNX_DATA_MAX_FABRIC_CGM_LOCAL_UNICAST_DYNAMIC_WFQ_LOW_THRESHOLD (40)


#define DNX_DATA_MAX_FABRIC_CGM_LOCAL_UNICAST_DYNAMIC_WFQ_HIGH_WEIGHT (1)

#undef DNX_DATA_MAX_FABRIC_CGM_LOCAL_UNICAST_DYNAMIC_WFQ_HIGH_WEIGHT
#define DNX_DATA_MAX_FABRIC_CGM_LOCAL_UNICAST_DYNAMIC_WFQ_HIGH_WEIGHT (70)


#define DNX_DATA_MAX_FABRIC_CGM_LOCAL_UNICAST_DYNAMIC_WFQ_LOW_WEIGHT (1)

#undef DNX_DATA_MAX_FABRIC_CGM_LOCAL_UNICAST_DYNAMIC_WFQ_LOW_WEIGHT
#define DNX_DATA_MAX_FABRIC_CGM_LOCAL_UNICAST_DYNAMIC_WFQ_LOW_WEIGHT (30)


#define DNX_DATA_MAX_FABRIC_DTQS_MAX_NOF_SUBDTQS (1)

#undef DNX_DATA_MAX_FABRIC_DTQS_MAX_NOF_SUBDTQS
#define DNX_DATA_MAX_FABRIC_DTQS_MAX_NOF_SUBDTQS (6)


#define DNX_DATA_MAX_FABRIC_DTQS_MAX_NOF_DTQS (1)

#undef DNX_DATA_MAX_FABRIC_DTQS_MAX_NOF_DTQS
#define DNX_DATA_MAX_FABRIC_DTQS_MAX_NOF_DTQS (3)


#define DNX_DATA_MAX_FABRIC_DTQS_MAX_SIZE (1)

#undef DNX_DATA_MAX_FABRIC_DTQS_MAX_SIZE
#define DNX_DATA_MAX_FABRIC_DTQS_MAX_SIZE (2048)


#define DNX_DATA_MAX_FABRIC_DTQS_OCB_ONLY_SIZE (1)

#undef DNX_DATA_MAX_FABRIC_DTQS_OCB_ONLY_SIZE
#define DNX_DATA_MAX_FABRIC_DTQS_OCB_ONLY_SIZE (128)


#define DNX_DATA_MAX_FABRIC_DBAL_LINK_RCI_THRESHOLD_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_LINK_RCI_THRESHOLD_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_LINK_RCI_THRESHOLD_BITS_NOF (11)


#define DNX_DATA_MAX_FABRIC_DBAL_CGM_LLFC_THRESHOLD_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_CGM_LLFC_THRESHOLD_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_CGM_LLFC_THRESHOLD_BITS_NOF (11)


#define DNX_DATA_MAX_FABRIC_DBAL_CGM_LLFC_THRESHOLD_MAX_VALUE (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_CGM_LLFC_THRESHOLD_MAX_VALUE
#define DNX_DATA_MAX_FABRIC_DBAL_CGM_LLFC_THRESHOLD_MAX_VALUE (1024)


#define DNX_DATA_MAX_FABRIC_DBAL_CGM_LLFC_INGRESS_IPT_CTX_MAPPING_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_CGM_LLFC_INGRESS_IPT_CTX_MAPPING_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_CGM_LLFC_INGRESS_IPT_CTX_MAPPING_BITS_NOF (3)


#define DNX_DATA_MAX_FABRIC_DBAL_EGRESS_FIFO_DROP_THRESHOLD_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_EGRESS_FIFO_DROP_THRESHOLD_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_EGRESS_FIFO_DROP_THRESHOLD_BITS_NOF (12)


#define DNX_DATA_MAX_FABRIC_DBAL_EGRESS_FIFO_DROP_THRESHOLD_MAX_VALUE (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_EGRESS_FIFO_DROP_THRESHOLD_MAX_VALUE
#define DNX_DATA_MAX_FABRIC_DBAL_EGRESS_FIFO_DROP_THRESHOLD_MAX_VALUE (2048)


#define DNX_DATA_MAX_FABRIC_DBAL_CGM_LINK_FIFO_BASE_ADDRESS_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_CGM_LINK_FIFO_BASE_ADDRESS_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_CGM_LINK_FIFO_BASE_ADDRESS_BITS_NOF (11)


#define DNX_DATA_MAX_FABRIC_DBAL_CGM_LINK_FIFO_BASE_ADDRESS_MAX_VALUE (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_CGM_LINK_FIFO_BASE_ADDRESS_MAX_VALUE
#define DNX_DATA_MAX_FABRIC_DBAL_CGM_LINK_FIFO_BASE_ADDRESS_MAX_VALUE (768)


#define DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_BASE_ADDRESS_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_BASE_ADDRESS_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_BASE_ADDRESS_BITS_NOF (12)


#define DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_BASE_ADDRESS_MAX_VALUE (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_BASE_ADDRESS_MAX_VALUE
#define DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_BASE_ADDRESS_MAX_VALUE (2048)


#define DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_FC_THRESHOLD_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_FC_THRESHOLD_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_FC_THRESHOLD_BITS_NOF (12)


#define DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_FC_THRESHOLD_MAX_VALUE (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_FC_THRESHOLD_MAX_VALUE
#define DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_FC_THRESHOLD_MAX_VALUE (2048)


#define DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_FC_FULL_LEVEL_MIN_VALUE (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_FC_FULL_LEVEL_MIN_VALUE
#define DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_FC_FULL_LEVEL_MIN_VALUE (8)


#define DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_FC_FULL_LEVEL_MAX_VALUE (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_FC_FULL_LEVEL_MAX_VALUE
#define DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_FC_FULL_LEVEL_MAX_VALUE (2047)


#define DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_FC_FULL_LEVEL_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_FC_FULL_LEVEL_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_FIFO_FC_FULL_LEVEL_BITS_NOF (12)


#define DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_DROP_MC_LOW_PRIO_TH_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_DROP_MC_LOW_PRIO_TH_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_DROP_MC_LOW_PRIO_TH_BITS_NOF (11)


#define DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_DYNAMIC_WFQ_TH_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_DYNAMIC_WFQ_TH_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_CGM_EGRESS_DYNAMIC_WFQ_TH_BITS_NOF (8)


#define DNX_DATA_MAX_FABRIC_DBAL_CGM_INGRESS_FC_THRESHOLD_MAX_VALUE (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_CGM_INGRESS_FC_THRESHOLD_MAX_VALUE
#define DNX_DATA_MAX_FABRIC_DBAL_CGM_INGRESS_FC_THRESHOLD_MAX_VALUE (12)


#define DNX_DATA_MAX_FABRIC_DBAL_CGM_STATIC_SHAPER_CALENDAR_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_CGM_STATIC_SHAPER_CALENDAR_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_CGM_STATIC_SHAPER_CALENDAR_BITS_NOF (8)


#define DNX_DATA_MAX_FABRIC_DBAL_FABRIC_TRANSMIT_WFQ_INDEX_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_FABRIC_TRANSMIT_WFQ_INDEX_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_FABRIC_TRANSMIT_WFQ_INDEX_BITS_NOF (4)


#define DNX_DATA_MAX_FABRIC_DBAL_FABRIC_TRANSMIT_WFQ_INDEX_MAX_VALUE (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_FABRIC_TRANSMIT_WFQ_INDEX_MAX_VALUE
#define DNX_DATA_MAX_FABRIC_DBAL_FABRIC_TRANSMIT_WFQ_INDEX_MAX_VALUE (9)


#define DNX_DATA_MAX_FABRIC_DBAL_MESH_TOPOLOGY_INIT_CONFIG_2_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_MESH_TOPOLOGY_INIT_CONFIG_2_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_MESH_TOPOLOGY_INIT_CONFIG_2_BITS_NOF (5)


#define DNX_DATA_MAX_FABRIC_DBAL_FABRIC_TRANSMIT_DTQ_FC_THRESHOLDS_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_FABRIC_TRANSMIT_DTQ_FC_THRESHOLDS_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_FABRIC_TRANSMIT_DTQ_FC_THRESHOLDS_BITS_NOF (12)


#define DNX_DATA_MAX_FABRIC_DBAL_FABRIC_TRANSMIT_PDQ_SIZE_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_FABRIC_TRANSMIT_PDQ_SIZE_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_FABRIC_TRANSMIT_PDQ_SIZE_BITS_NOF (15)


#define DNX_DATA_MAX_FABRIC_DBAL_ADAPTIVE_SHAPER_THRESHOLD_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_ADAPTIVE_SHAPER_THRESHOLD_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_ADAPTIVE_SHAPER_THRESHOLD_BITS_NOF (10)


#define DNX_DATA_MAX_FABRIC_DBAL_ADAPTIVE_SHAPER_FACTOR_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_ADAPTIVE_SHAPER_FACTOR_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_ADAPTIVE_SHAPER_FACTOR_BITS_NOF (11)


#define DNX_DATA_MAX_FABRIC_DBAL_ADAPTIVE_SHAPER_MNOL_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_ADAPTIVE_SHAPER_MNOL_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_ADAPTIVE_SHAPER_MNOL_BITS_NOF (8)


#define DNX_DATA_MAX_FABRIC_DBAL_GLOBAL_CELL_SHAPER_ALLOWED_CELLS_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_GLOBAL_CELL_SHAPER_ALLOWED_CELLS_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_GLOBAL_CELL_SHAPER_ALLOWED_CELLS_BITS_NOF (16)


#define DNX_DATA_MAX_FABRIC_DBAL_GLOBAL_CELL_SHAPER_ALLOWED_CELLS_GRANULARITY (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_GLOBAL_CELL_SHAPER_ALLOWED_CELLS_GRANULARITY
#define DNX_DATA_MAX_FABRIC_DBAL_GLOBAL_CELL_SHAPER_ALLOWED_CELLS_GRANULARITY (32)


#define DNX_DATA_MAX_FABRIC_DBAL_GLOBAL_CELL_SHAPER_ALLOWED_CELLS_MAX_VALUE (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_GLOBAL_CELL_SHAPER_ALLOWED_CELLS_MAX_VALUE
#define DNX_DATA_MAX_FABRIC_DBAL_GLOBAL_CELL_SHAPER_ALLOWED_CELLS_MAX_VALUE (65535)


#define DNX_DATA_MAX_FABRIC_DBAL_GLOBAL_CELL_SHAPER_TIME_FRAME_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_GLOBAL_CELL_SHAPER_TIME_FRAME_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_GLOBAL_CELL_SHAPER_TIME_FRAME_BITS_NOF (11)


#define DNX_DATA_MAX_FABRIC_DBAL_GLOBAL_CELL_SHAPER_TIME_FRAME_MAX_VALUE (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_GLOBAL_CELL_SHAPER_TIME_FRAME_MAX_VALUE
#define DNX_DATA_MAX_FABRIC_DBAL_GLOBAL_CELL_SHAPER_TIME_FRAME_MAX_VALUE (2047)


#define DNX_DATA_MAX_FABRIC_DBAL_GLOBAL_CELL_SHAPER_CNT_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_GLOBAL_CELL_SHAPER_CNT_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_GLOBAL_CELL_SHAPER_CNT_BITS_NOF (16)


#define DNX_DATA_MAX_FABRIC_DBAL_FDR_LINKS_OFFSET (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_FDR_LINKS_OFFSET
#define DNX_DATA_MAX_FABRIC_DBAL_FDR_LINKS_OFFSET (8)


#define DNX_DATA_MAX_FABRIC_DBAL_FABRIC_CGM_RCI_HIGH_SEVERITY_MIN_NOF_LINKS_BITS_NOF (1)

#undef DNX_DATA_MAX_FABRIC_DBAL_FABRIC_CGM_RCI_HIGH_SEVERITY_MIN_NOF_LINKS_BITS_NOF
#define DNX_DATA_MAX_FABRIC_DBAL_FABRIC_CGM_RCI_HIGH_SEVERITY_MIN_NOF_LINKS_BITS_NOF (8)


#define DNX_DATA_MAX_FABRIC_MESH_MC_NOF_REPLICATION (1)

#undef DNX_DATA_MAX_FABRIC_MESH_MC_NOF_REPLICATION
#define DNX_DATA_MAX_FABRIC_MESH_MC_NOF_REPLICATION (5)


#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQS_TOTAL_SIZE (1)

#undef DNX_DATA_MAX_FABRIC_TRANSMIT_PDQS_TOTAL_SIZE
#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQS_TOTAL_SIZE (26624)


#define DNX_DATA_MAX_FABRIC_TRANSMIT_NOF_PDQS (1)

#undef DNX_DATA_MAX_FABRIC_TRANSMIT_NOF_PDQS
#define DNX_DATA_MAX_FABRIC_TRANSMIT_NOF_PDQS (26)


#define DNX_DATA_MAX_FABRIC_TRANSMIT_S2D_PDQ_SIZE (1)

#undef DNX_DATA_MAX_FABRIC_TRANSMIT_S2D_PDQ_SIZE
#define DNX_DATA_MAX_FABRIC_TRANSMIT_S2D_PDQ_SIZE (1023)


#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_SRAM_FC_TH (1)

#undef DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_SRAM_FC_TH
#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_SRAM_FC_TH (700)


#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_MIXS_FC_TH (1)

#undef DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_MIXS_FC_TH
#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_MIXS_FC_TH (700)


#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_MIXD_FC_TH (1)

#undef DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_MIXD_FC_TH
#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_MIXD_FC_TH (700)


#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_MIX_MIXS_FC_TH (1)

#undef DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_MIX_MIXS_FC_TH
#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_MIX_MIXS_FC_TH (600)


#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_MIX_MIXD_FC_TH (1)

#undef DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_MIX_MIXD_FC_TH
#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_MIX_MIXD_FC_TH (600)


#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_OCB_FC_TH (1)

#undef DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_OCB_FC_TH
#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_OCB_FC_TH (700)


#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_DRAM_DELETE_FC_TH (1)

#undef DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_DRAM_DELETE_FC_TH
#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_DRAM_DELETE_FC_TH (900)


#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_SRAM_DELETE_FC_TH (1)

#undef DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_SRAM_DELETE_FC_TH
#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_SRAM_DELETE_FC_TH (200)


#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_S2D_FC_TH (1)

#undef DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_S2D_FC_TH
#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_S2D_FC_TH (873)


#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_SRAM_EIR_FC_TH (1)

#undef DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_SRAM_EIR_FC_TH
#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_SRAM_EIR_FC_TH (800)


#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_MIXS_EIR_FC_TH (1)

#undef DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_MIXS_EIR_FC_TH
#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_MIXS_EIR_FC_TH (800)


#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_MIXD_EIR_FC_TH (1)

#undef DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_MIXD_EIR_FC_TH
#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_MIXD_EIR_FC_TH (800)


#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_OCB_EIR_FC_TH (1)

#undef DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_OCB_EIR_FC_TH
#define DNX_DATA_MAX_FABRIC_TRANSMIT_PDQ_OCB_EIR_FC_TH (700)


#define DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_MAX_MASTER_ID (1)

#undef DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_MAX_MASTER_ID
#define DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_MAX_MASTER_ID (2047)


#define DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_0 (1)

#undef DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_0
#define DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_0 (10)


#define DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_1 (1)

#undef DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_1
#define DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_1 (8388607)


#define DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_2 (1)

#undef DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_2
#define DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_2 (10000)


#define DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_3 (1)

#undef DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_3
#define DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_3 (300000)


#define DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_4 (1)

#undef DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_4
#define DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_4 (1000)


#define DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_5 (1)

#undef DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_5
#define DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_5 (100000)


#define DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_7 (1)

#undef DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_7
#define DNX_DATA_MAX_FABRIC_SYSTEM_UPGRADE_PARAM_7 (100)


#define DNX_DATA_MAX_FABRIC_REGRESSION_MINIMUM_SYSTEM_REF_CLK (1)

#undef DNX_DATA_MAX_FABRIC_REGRESSION_MINIMUM_SYSTEM_REF_CLK
#define DNX_DATA_MAX_FABRIC_REGRESSION_MINIMUM_SYSTEM_REF_CLK (1600000)


#define DNX_DATA_MAX_FABRIC_REGRESSION_SOFT_RESET_WITH_FABRIC_MAX_EXEC_TIME (1)

#undef DNX_DATA_MAX_FABRIC_REGRESSION_SOFT_RESET_WITH_FABRIC_MAX_EXEC_TIME
#define DNX_DATA_MAX_FABRIC_REGRESSION_SOFT_RESET_WITH_FABRIC_MAX_EXEC_TIME (900000)


#define DNX_DATA_MAX_FABRIC_REGRESSION_SOFT_RESET_WITH_FABRIC_AVG_EXEC_TIME (1)

#undef DNX_DATA_MAX_FABRIC_REGRESSION_SOFT_RESET_WITH_FABRIC_AVG_EXEC_TIME
#define DNX_DATA_MAX_FABRIC_REGRESSION_SOFT_RESET_WITH_FABRIC_AVG_EXEC_TIME (310000)





#endif 


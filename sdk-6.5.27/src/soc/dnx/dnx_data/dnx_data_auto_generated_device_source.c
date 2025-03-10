
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#define DNX_DATA_INTERNAL



#include <soc/dnx/dnx_data/auto_generated/dnx_data_property.h>

#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_access.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_adapter.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_bfd.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_bier.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_consistent_hashing.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_cosq_aqm.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_crps.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_dbal.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_debug.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_dev_init.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_device.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/dnx2/jr2_a0_data_dnx2_pemla_soc.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_dram.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_ecgm.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_egr_queuing.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_egr_queuing_v1.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_elk.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_esb.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_esem.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_fabric.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_failover.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_fc.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_field.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_field_map.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_fifodma.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_flow.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_graphical.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_gtimer.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_gtp.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_headers.c>
#ifdef INCLUDE_CTEST
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_infra_tests.c>
#endif  
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_ingr_congestion.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_ingr_reassembly.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_ingress_cs.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_instru.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_intr.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_ipq.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_iqs.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_kaps.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_kleap_stage_info.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_l2.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_l3.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_lane_map.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_latency.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_led.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_lif.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_linkscan.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_macsec.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_mdb.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_meter.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_mib.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_module_testing.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_mpls.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_multicast.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_nif.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_oam.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_parser.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_pll.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_port.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_port_pp.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_pp.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_ppmc.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_ptp.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_pvt.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_qos.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_regression.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_sat.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_sbusdma_desc.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_sch.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_snif.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_spb.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_srv6.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_stack.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_stat.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_stg.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_stif.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_switch.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_synce.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_system_red.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_tdm.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_techsupport.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_time.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_trap.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_trunk.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_tune.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_tunnel.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0/jr2_a0_data_vlan.c>


#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0_standard_1/dnx2/jr2_a0_standard_1_data_dnx2_aod.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0_standard_1/dnx2/jr2_a0_standard_1_data_dnx2_aod_sizes.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0_standard_1/dnx2/jr2_a0_standard_1_data_dnx2_arr.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_a0_standard_1/dnx2/jr2_a0_standard_1_data_dnx2_mdb_app_db.c>


#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_adapter.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_bfd.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_bier.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_crps.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_dbal.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_debug.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_dev_init.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_device.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/dnx2/jr2_b0_data_dnx2_pemla_soc.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_dram.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_egr_queuing.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_esem.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_field.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_field_map.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_graphical.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_headers.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_ingr_congestion.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_instru.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_intr.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_l2.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_l3.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_latency.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_mdb.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_meter.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_mpls.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_nif.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_oam.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_qos.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_sat.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_srv6.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_stat.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_stif.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_switch.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_system_red.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_techsupport.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0/jr2_b0_data_trap.c>


#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0_standard_1/dnx2/jr2_b0_standard_1_data_dnx2_aod.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0_standard_1/dnx2/jr2_b0_standard_1_data_dnx2_aod_sizes.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0_standard_1/dnx2/jr2_b0_standard_1_data_dnx2_arr.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b0_standard_1/dnx2/jr2_b0_standard_1_data_dnx2_mdb_app_db.c>


#include <src/soc/dnx/dnx_data/auto_generated/jr2_b1/jr2_b1_data_device.c>
#include <src/soc/dnx/dnx_data/auto_generated/jr2_b1/jr2_b1_data_mdb.c>




#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_adapter.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_bfd.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_bier.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_cosq_aqm.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_crps.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_dbal.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_debug.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_dev_init.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_device.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/dnx2/j2c_a0_data_dnx2_pemla_soc.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_dram.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_ecgm.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_egr_queuing.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_elk.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_esb.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_esem.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_fabric.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_fc.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_field.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_field_map.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_graphical.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_gtimer.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_headers.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_ingr_congestion.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_ingr_reassembly.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_ingress_cs.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_instru.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_intr.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_ipq.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_iqs.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_l2.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_l3.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_latency.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_led.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_lif.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_mdb.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_meter.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_module_testing.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_mpls.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_nif.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_oam.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_onesync.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_pll.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_port.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_port_pp.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_pp.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_ptp.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_pvt.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_qos.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_regression.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_sat.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_sch.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_snif.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_srv6.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_stack.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_stat.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_stif.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_switch.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_synce.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_system_red.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_tdm.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_techsupport.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_trap.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_trunk.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_tune.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0/j2c_a0_data_vlan.c>


#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0_standard_1/dnx2/j2c_a0_standard_1_data_dnx2_aod.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0_standard_1/dnx2/j2c_a0_standard_1_data_dnx2_aod_sizes.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0_standard_1/dnx2/j2c_a0_standard_1_data_dnx2_arr.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a0_standard_1/dnx2/j2c_a0_standard_1_data_dnx2_mdb_app_db.c>


#include <src/soc/dnx/dnx_data/auto_generated/j2c_a1/j2c_a1_data_device.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a1/j2c_a1_data_ingr_congestion.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a1/j2c_a1_data_instru.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a1/j2c_a1_data_l2.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a1/j2c_a1_data_mdb.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a1/j2c_a1_data_nif.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2c_a1/j2c_a1_data_port_pp.c>




#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_adapter.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_bfd.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_bier.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_cosq_aqm.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_crps.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_dbal.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_debug.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_dev_init.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_device.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/dnx2/q2a_a0_data_dnx2_pemla_soc.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_dram.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_ecgm.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_egr_queuing.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_elk.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_esb.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_esem.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_fabric.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_fc.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_field.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_field_map.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_graphical.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_gtimer.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_headers.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_ingr_congestion.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_ingr_reassembly.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_ingress_cs.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_instru.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_intr.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_ipq.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_iqs.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_l2.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_l3.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_latency.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_led.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_lif.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_mdb.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_meter.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_mib.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_module_testing.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_mpls.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_multicast.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_nif.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_oam.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_onesync.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_pll.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_port.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_port_pp.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_pp.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_ptp.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_pvt.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_qos.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_regression.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_sat.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_sch.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_snif.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_spb.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_srv6.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_stack.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_stat.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_stif.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_switch.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_synce.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_system_red.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_tdm.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_techsupport.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_trap.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_trunk.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_tune.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0/q2a_a0_data_vlan.c>


#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0_standard_1/dnx2/q2a_a0_standard_1_data_dnx2_aod.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0_standard_1/dnx2/q2a_a0_standard_1_data_dnx2_aod_sizes.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0_standard_1/dnx2/q2a_a0_standard_1_data_dnx2_arr.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_a0_standard_1/dnx2/q2a_a0_standard_1_data_dnx2_mdb_app_db.c>


#include <src/soc/dnx/dnx_data/auto_generated/q2a_b0/q2a_b0_data_adapter.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b0/q2a_b0_data_dev_init.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b0/q2a_b0_data_device.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b0/dnx2/q2a_b0_data_dnx2_pemla_soc.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b0/q2a_b0_data_dram.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b0/q2a_b0_data_l2.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b0/q2a_b0_data_led.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b0/q2a_b0_data_mpls.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b0/q2a_b0_data_nif.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b0/q2a_b0_data_srv6.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b0/q2a_b0_data_stif.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b0/q2a_b0_data_switch.c>


#include <src/soc/dnx/dnx_data/auto_generated/q2a_b0_standard_1/dnx2/q2a_b0_standard_1_data_dnx2_aod.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b0_standard_1/dnx2/q2a_b0_standard_1_data_dnx2_aod_sizes.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b0_standard_1/dnx2/q2a_b0_standard_1_data_dnx2_arr.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b0_standard_1/dnx2/q2a_b0_standard_1_data_dnx2_mdb_app_db.c>


#include <src/soc/dnx/dnx_data/auto_generated/q2a_b1/q2a_b1_data_device.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b1/q2a_b1_data_dram.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b1/q2a_b1_data_egr_queuing.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b1/q2a_b1_data_l2.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b1/q2a_b1_data_latency.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b1/q2a_b1_data_mdb.c>
#include <src/soc/dnx/dnx_data/auto_generated/q2a_b1/q2a_b1_data_nif.c>




#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_access.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_adapter.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_bfd.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_bier.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_cosq_aqm.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_crps.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_dbal.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_debug.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_dev_init.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_device.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/dnx2/j2p_a0_data_dnx2_pemla_soc.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_dram.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_ecgm.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_egr_queuing.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_elk.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_esb.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_esem.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_fabric.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_fc.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_field.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_field_map.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_flow.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_graphical.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_gtimer.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_headers.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_ingr_congestion.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_ingr_reassembly.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_ingress_cs.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_instru.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_intr.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_ipq.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_iqs.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_l2.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_l3.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_latency.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_led.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_lif.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_macsec.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_mdb.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_meter.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_mib.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_module_testing.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_mpls.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_nif.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_oam.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_pll.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_port.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_port_pp.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_pp.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_ptp.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_pvt.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_qos.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_regression.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_sat.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_sch.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_snif.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_spb.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_srv6.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_stack.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_stat.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_stif.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_switch.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_synce.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_system_red.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_techsupport.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_trap.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_trunk.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_tune.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0/j2p_a0_data_vlan.c>


#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0_standard_1/dnx2/j2p_a0_standard_1_data_dnx2_aod.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0_standard_1/dnx2/j2p_a0_standard_1_data_dnx2_aod_sizes.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0_standard_1/dnx2/j2p_a0_standard_1_data_dnx2_arr.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a0_standard_1/dnx2/j2p_a0_standard_1_data_dnx2_mdb_app_db.c>


#include <src/soc/dnx/dnx_data/auto_generated/j2p_a1/j2p_a1_data_crps.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a1/j2p_a1_data_device.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a1/j2p_a1_data_dram.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a1/j2p_a1_data_fabric.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a1/j2p_a1_data_lif.c>




#include <src/soc/dnx/dnx_data/auto_generated/j2p_a2/j2p_a2_data_device.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a2/j2p_a2_data_egr_queuing.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a2/j2p_a2_data_macsec.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2p_a2/j2p_a2_data_snif.c>




#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_access.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_adapter.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_bfd.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_bier.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_cosq_aqm.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_crps.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_dbal.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_debug.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_dev_init.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_device.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/dnx2/j2x_a0_data_dnx2_pemla_soc.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_dram.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_ecgm.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_egr_queuing.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_elk.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_esb.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_esem.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_fabric.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_fc.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_field.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_field_map.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_graphical.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_gtimer.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_headers.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_ingr_congestion.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_ingr_reassembly.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_ingress_cs.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_instru.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_intr.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_ipq.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_iqs.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_l2.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_l3.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_lane_map.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_latency.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_led.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_lif.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_macsec.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_mdb.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_meter.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_mib.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_module_testing.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_mpls.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_multicast.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_nif.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_oam.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_pll.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_port.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_port_pp.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_pp.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_ptp.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_pvt.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_qos.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_regression.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_sat.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_sch.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_snif.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_spb.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_srv6.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_stack.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_stat.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_stif.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_switch.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_synce.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_tdm.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_trap.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_trunk.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_tsn.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_tune.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0/j2x_a0_data_vlan.c>


#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0_standard_1/dnx2/j2x_a0_standard_1_data_dnx2_aod.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0_standard_1/dnx2/j2x_a0_standard_1_data_dnx2_aod_sizes.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0_standard_1/dnx2/j2x_a0_standard_1_data_dnx2_arr.c>
#include <src/soc/dnx/dnx_data/auto_generated/j2x_a0_standard_1/dnx2/j2x_a0_standard_1_data_dnx2_mdb_app_db.c>



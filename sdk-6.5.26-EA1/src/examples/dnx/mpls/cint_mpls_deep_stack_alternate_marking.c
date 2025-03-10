/*
 * 
 This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 
 Copyright 2007-2022 Broadcom Inc. All rights reserved. File: cint_mpls_deep_stack.c Purpose: utility for MPLS deep encapsulation stack..
 */

/*
 * This cint is an example of Alternate Marking configuration (RFC321) of Ingress Node.
 * It contains IPv4 forwarding into deep MPLS tunnel stack with Alternate Marking encapsulation.
 * This cint uses mpls and counter cint utilities and cint_field_alternate_marking.c that contains the
 * field configuration for alternate marking.
 *
 * Test Scenario (ingress node)
 *
 * ./bcm.user
 * cd ../../../../regress/bcm
 * cint ../../src/./examples/sand/utility/cint_sand_utils_global.c
 * cint ../../src/./examples/dnx/utility/cint_dnx_utils_l3.c
 * cint ../../src/./examples/dnx/utility/cint_dnx_utility_mpls.c
 * cint ../../src/./examples/dnx/mpls/cint_mpls_deep_stack_alternate_marking.c
 * cint ../../src/./examples/dnx/stat_pp/cint_stat_pp_config.c
 * cint ../../src/./examples/dnx/crps/cint_crps_db_utils.c
 * cint ../../src/./examples/dnx/crps/cint_crps_irpp_config.c
 * cint ../../src/./examples/dnx/field/cint_field_alternate_marking.c
 * cint ../../src/./examples/dnx/crps/cint_crps_oam_config.c
 * cint
 * mpls_deep_stack_alternate_marking_encapsulation_example(0,200,203,5);
 * exit;

 *
 * cint
 *  cint_field_alternate_marking_period_change(0,0,0);
 * exit;
 *
 **** alternate marking, L=0, second packet = 0
 * tx 1 psrc=200 data=0x000c00020001000c0002000081000000080045000049000000008006b626a0a1a1a2a0a1a1a31f40232800000000000000000010001000000000000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 *
 *  Should recieve 2 packets: forward copy + snoop copy. ToD timestamp in the snooped copy.
 * Next packet, counter should be >0, there will be no snoop copy.
 *
 ****** Switch to L=1
 * cint
 * cint_field_alternate_marking_period_change(0,0,1);
 * exit;
 *
 **** alternate marking, L=1, second packet = 0 *
 * tx 1 psrc=200 data=0x000c00020001000c0002000081000000080045000049000000008006b626a0a1a1a2a0a1a1a31f40232800000000000000000010001000000000000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * Once again, should recieve 2 packets.
 *
 * Read L=0 counter:
 * read_counter_and_handle_eviction(unit,1,&counter)
 */

 /*
 * Test Scenario  - termaination and intermediate node
 * Note that this cint doesn't provide termination/MPLS forwarding cints.
 * In this example we use mpls_termination_basic_main
 *
 * ./bcm.user
 * cd ../../../../regress/bcm
 * cint ../../src/./examples/sand/utility/cint_sand_utils_global.c
 * cint ../../src/./examples/sand/utility/cint_sand_utils_global.c
 * cint ../../src/./examples/dnx/field/cint_field_utils.c
 * cint ../../src/./examples/sand/cint_ip_route_basic.c
 * cint ../../src/./examples/sand/cint_mpls_encapsulation_basic.c
 * cint ../../src/./examples/sand/cint_mpls_termination_basic.c
 * cint
 * mpls_encapsulation_basic_main(0,200,201,0);
 * fec_id_deviation=10;
 * mpls_termination_basic_main(0,200,201);
 * exit;
 *
 * cint ../../src/./examples/sand/utility/cint_sand_utils_global.c
 * cint ../../src/./examples/sand/utility/cint_dnx_utils_l3.c
 * cint ../../src/./examples/dnx/utility/cint_dnx_utility_mpls.c
 * cint ../../src/./examples/dnx/mpls/cint_mpls_deep_stack_alternate_marking.c
 * cint ../../src/./examples/dnx/stat_pp/cint_stat_pp_config.c
 * cint ../../src/./examples/dnx/crps/cint_crps_db_utils.c
 * cint ../../src/./examples/dnx/crps/cint_crps_irpp_config.c
 * cint ../../src/./examples/dnx/field/cint_field_alternate_marking.c
 * cint ../../src/./examples/dnx/crps/cint_crps_oam_config.c
 * cint ../../src/./examples/dnx/field/cint_field_ip_snoop.c
 * cint
 * mpls_alternate_marking_termination(0,200,201,0xabc,0);
 * exit;
 *
 *   4 types of packets, the difference being the L and D bits.
 *   Use packetor.com to analyze packets
 *
 *   First Packet: L bit 0, D bit 0.
 *  MPLS over ethernet packet
 * tx 1 psrc=200 data=0x000c000200000011000001128100000088470177004001e610400000a04000abc140450000350000000080005874a0000011a0a1a1a2000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * Received packets on unit 0 should be (packet was forwarded):
 *  Data: 0x00000000cd1d000c00020f558100002a884700d0503f0000a04000abc140450000350000000080005874a0000011a0a1a1a2000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 *
 *  Second packet: L bit 1, D bit 0
 *  MPLS over ethernet packet
 * tx 1 psrc=200 data=0x000c000200000011000001128100000088470177004001e610400000a04000abc140450000350000000080005874a0000011a0a1a1a2000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 *  Received packets on unit 0 should be (packet was forwarded):
 *  Data: 0x00000000cd1d000c00020f558100002a884700d0503f0000a04000abc940450000350000000080005874a0000011a0a1a1a2000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 *
 *  Third packet: L bit 0 D bit 1
 *  MPLS over ethernet packet
 * tx 1 psrc=200 data=0x000c000200000011000001128100000088470177004001e610400000a04000abc540450000350000000080005874a0000011a0a1a1a2000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * Two packets recieved: forwarded copy:
 * Data: 0x00000000cd1d000c00020f558100002a884700d0503f0000a04000abc540450000350000000080005874a0000011a0a1a1a2000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * And snooped copy, including system headers and timestamp information
 *  Data: 0x01f800000008000002601c35e7e5b553d0000800000000000007fa00020000000195008017000c000200000011000001128100000088470177004001e610400000a04000abc540450000350000000080005874a0000011a0a1a1a2000102030405060708090a0b0c0d0e0f10111213141516171819
 *
 *  Fourth packet: L bit 1 D bit 1
 *  MPLS over ethernet packet
 * tx 1 psrc=200 data=0x000c000200000011000001128100000088470177004001e610400000a04000abcd40450000350000000080005874a0000011a0a1a1a2000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * Two packets recieved: forwarded copy:
 * Data: 0x00000000cd1d000c00020f558100002a884700d0503f0000a04000abcd40450000350000000080005874a0000011a0a1a1a2000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * And snooped copy, including system headers and timestamp information
 * Data: 0x01f800000008000002601c35e7917e5510000800000000000007fa00020000000195008017000c000200000011000001128100000088470177004001e610400000a04000abcd40450000350000000080005874a0000011a0a1a1a2000102030405060708090a0b0c0d0e0f10111213141516171819
 *
 * Read each counter with mpls_deep_stack_alternate_marking_get_counter
 *
 */

/*
 *Additional example of intermediate PE node when IP is terminated (intermediate PE node)
 *
 * Packet in Pipeline
 *   1. Rx packet with format IPvXoFLoFLIoMPLSxMPLSyoEth
 *   2. Tunnel-termination for the MPLSx and IP forwarding (IPvX lookup on IPvX.DIP) which
 *      encapsulates the packet with a new MPLS header (MPLSm and MPLSn)
 *   3. Tx packet with format IPvXoFLoFLIoMPLSmoMPLSnoEth
 *
 * Test Scenario (intermediate PE node)
 *
 * ./bcm.user
 * cd ../../../../regress/bcm
 * cint ../../src/./examples/sand/utility/cint_sand_utils_global.c
 * cint ../../src/./examples/dnx/field/cint_field_utils.c
 * cint ../../src/./examples/sand/cint_ip_route_basic.c
 * cint ../../src/./examples/sand/cint_mpls_encapsulation_basic.c
 * cint ../../src/./examples/sand/cint_mpls_termination_basic.c
 * cint
 * mpls_encapsulation_basic_main(0,200,202,0);
 * cint_termination_mpls_basic_info.termination_stack[2]=10;
 * cint_termination_mpls_basic_info.termination_stack[3]=0xabc;
 * fec_id_deviation=10;
 * mpls_termination_basic_main(0,200,202);
 * exit;
 *
 * cint ../../src/./examples/sand/utility/cint_sand_utils_global.c
 * cint ../../src/./examples/sand/utility/cint_dnx_utils_l3.c
 * cint ../../src/./examples/sand/utility/cint_sand_utils_mpls.c
 * cint ../../src/./examples/dnx/utility/cint_dnx_utility_mpls.c
 * cint ../../src/./examples/dnx/field/cint_field_presel_fwd_layer.c
 * cint ../../src/./examples/dnx/field/cint_field_udh_cascading.c
 * cint ../../src/./examples/dnx/mpls/cint_mpls_deep_stack_alternate_marking.c
 * cint ../../src/./examples/dnx/stat_pp/cint_stat_pp_config.c
 * cint ../../src/./examples/dnx/crps/cint_crps_db_utils.c
 * cint ../../src/./examples/dnx/crps/cint_crps_irpp_config.c
 * cint ../../src/./examples/dnx/field/cint_field_alternate_marking.c
 * cint ../../src/./examples/dnx/crps/cint_crps_oam_config.c
 * cint ../../src/./examples/dnx/field/cint_field_ip_snoop.c
 * cint
 * mpls_am_inter_pe_route_into_tunnel(0,200,202);
 * mpls_alternate_marking_termination(0,200,202,0xabc,1);
 * exit;
 *
 * First Packet: L bit 0, D bit 0.
 * tx 1 psrc=200 data=0x000c0002000000110000011281000000884701770040017710400000a03c00abc114450000350000000080001bb4a00000117fffff04000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * Received packets on unit 0 should be (packet was forwarded):
 * Data: 0x00000000cd1d000c0002000181000032884701f41028003200140000a03c00abc11445000035000000007f001cb4a00000117fffff04000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 *
 * Second packet: L bit 0, D bit 1
 * tx 1 psrc=200 data=0x000c0002000000110000011281000000884701770040017710400000a03c00abc514450000350000000080001bb4a00000117fffff04000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * Received two packets on unit 0 should be:
 * Forward copy:
 * Data: 0x00000000cd1d000c0002000181000032884701f41028003200140000a03c00abc51445000035000000007f001cb4a00000117fffff04000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * Snoop copy, including system headers and timestamp information:
 * Data: 0x01f80000000800000260bb7926868c873e000800000000000007fa0002000000019500801e000c0002000000110000011281000000884701770040017710400000a03c00abc514450000350000000080001bb4a00000117fffff04000102030405060708090a0b0c0d0e0f10111213141516171819
 *
 * Third Packet: L bit 1, D bit 0.
 * tx 1 psrc=200 data=0x000c0002000000110000011281000000884701770040017710400000a03c00abc914450000350000000080001bb4a00000117fffff04000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * Received packets on unit 0 should be (packet was forwarded):
 * Data: 0x00000000cd1d000c0002000181000032884701f41028003200140000a03c00abc91445000035000000007f001cb4a00000117fffff04000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 *
 * Forth packet: L bit 1 D bit 1.
 * tx 1 psrc=200 data=0x000c0002000000110000011281000000884701770040017710400000a03c00abcd14450000350000000080001bb4a00000117fffff04000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * Received two packets on unit 0 should be:
 * Forward copy:
 * Data: 0x00000000cd1d000c0002000181000032884701f41028003200140000a03c00abcd1445000035000000007f001cb4a00000117fffff04000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * Snoop copy, including system headers and timestamp information:
 * Data: 0x01f80000000800000260bb7926a594dd78000800000000000007fa0002000000019500801e000c0002000000110000011281000000884701770040017710400000a03c00abcd14450000350000000080001bb4a00000117fffff04000102030405060708090a0b0c0d0e0f10111213141516171819
 *
 * Time-of-Day in case D bit is on can come in one of 2 ways:
 * 1. Tail edit appended to the end of the packet which includes time of day
 *    On Jer2-B0 using this method only egress-TOD may be used.
 * 2.  64B of  mirror information appended to snooped packets.
 *      In this case the last 12 bytes will ingress-ToD (6B), egress-ToD (12B)
 *      Format of snooped packets in this case will be {FTMH+system+headers, 52B reserved, 6B ingress-ToD, 6B egress-TOD, network-headers}
 *              52B reserved includes original system headers. Existince of this stack is indicated by the FHEI of the first set of system headers (Usually trap code will be EgTxFieldSnoop1)
 *  Global variable tod_append_mode determines this.
 *  This applies to ingress node only.
 *  When set to 1, cint_field_IFA_datapath.c, cint_ifa.c cints must be loaded.
 */

/**
 * Set to 1 (tail edit) or 2 (mirror additional information)
 */
int tod_append_mode =1;
/**
 * Setting tod_append_mode to 2 requires port configuration when
 * the in_port is a NIF port.
 *
 */
int in_port_is_nif =0;


/**
 * Using iFIT for altermate marking
 *
 */
int ifit_enable =0;

/**
 * Set to 0 (only stat pkts) or 1 (stat both pkts and bytes)
 */
int stat_mode_pkt_and_byte = 0;

/*
 * IPT main function for alternate marking.
 * Calls:
 *
 */

/**
 * \brief IPT profile IDs
 */
int CINT_INSTRU_IPT_TAIL_EDIT_PROFILE              = 1;

/*
 * Default values used for setting back defaults
 */
bcm_instru_ipt_t default_tail_edit_config;
int default_switch_id;

int
cint_instru_ipt_main(
   int unit,
   int switch_id,
   int shim_type)
{
    int rv;
    uint32 ipt_profile;
    bcm_instru_ipt_t config;
    uint32 supported_flags_per_device = 0;

    /* Following flags shared between all devices:*/
    supported_flags_per_device = BCM_INSTRU_IPT_METADATA_FLAG_INGRESS_TOD | BCM_INSTRU_IPT_METADATA_FLAG_INGRESS_SYS_PORT |
            BCM_INSTRU_IPT_METADATA_FLAG_EGRESS_TOD | BCM_INSTRU_IPT_METADATA_FLAG_EGRESS_SYS_PORT |
            BCM_INSTRU_IPT_METADATA_FLAG_SWITCH_ID | BCM_INSTRU_IPT_METADATA_FLAG_QUEUE_INFO;

    if (*dnxc_data_get (unit,"instru","ipt","advanced_ipt",NULL))
    {
        /* Advanced IPT flags*/
        supported_flags_per_device |= BCM_INSTRU_IPT_METADATA_FLAG_QUEUE_SIZE_FG | BCM_INSTRU_IPT_METADATA_FLAG_LATENCY| BCM_INSTRU_IPT_METADATA_FLAG_PORT_RATE
            | BCM_INSTRU_IPT_METADATA_FLAG_QUEUE_SIZE_CG;

    } else {
        /* Basic IPT flags*/
        supported_flags_per_device |= BCM_INSTRU_IPT_METADATA_FLAG_INGRESS_DEV_ID |
                BCM_INSTRU_IPT_METADATA_FLAG_EGRESS_RESERVED |  BCM_INSTRU_IPT_METADATA_FLAG_EGRESS_DEV_ID;
    }


    /** set tail-edit profile */
    {
        ipt_profile = CINT_INSTRU_IPT_TAIL_EDIT_PROFILE;

        /** get default */
        rv  = bcm_instru_ipt_profile_get(unit, 0, ipt_profile, &default_tail_edit_config);
        if (rv != BCM_E_NONE)
        {
            printf("bcm_instru_ipt_profile_get failed for Tail Edit\n");
            return rv;
        }

        bcm_instru_ipt_t_init(&config);

        config.node_type = bcmInstruIptNodeTypeTail;
        config.metadata_flags = supported_flags_per_device;

        rv  = bcm_instru_ipt_profile_set(unit, 0, ipt_profile, &config);
        if (rv != BCM_E_NONE)
        {
            printf("bcm_instru_ipt_profile_set failed for Tail Edit\n");
            return rv;
        }
    }

    if (0==*dnxc_data_get (unit,"instru","ipt","advanced_ipt",NULL))
    {
        /* Following configurations also use "ingress resereved" flags (Jer2 devices only)*/
        supported_flags_per_device |= BCM_INSTRU_IPT_METADATA_FLAG_INGRESS_RESERVED;
    }



    /** get default switch id */
    rv = bcm_instru_control_get(unit, 0, bcmInstruControlIptSwitchId, &default_switch_id);
    if (rv != BCM_E_NONE)
    {
        printf("bcm_instru_control_get failed for setting switch id\n");
        return rv;
    }

    /** set switch ID */
    rv = bcm_instru_control_set(unit, 0, bcmInstruControlIptSwitchId, switch_id);
    if (rv != BCM_E_NONE)
    {
        printf("bcm_instru_control_set failed for setting switch id\n");
        return rv;
    }

    return rv;
}


int
cint_instru_ipt_clear(
   int unit)
{
    int rv;
    int ipt_profile;

    /** set tail-edit profile */
    {
        ipt_profile = CINT_INSTRU_IPT_TAIL_EDIT_PROFILE;

        rv  = bcm_instru_ipt_profile_set(unit, 0, ipt_profile, default_tail_edit_config);
        if (rv != BCM_E_NONE)
        {
            printf("bcm_instru_ipt_profile_set failed for default Tail Edit\n");
            return rv;
        }
    }

    /** set switch ID */
    rv = bcm_instru_control_set(unit, 0, bcmInstruControlIptSwitchId, default_switch_id);
    if (rv != BCM_E_NONE)
    {
        printf("bcm_instru_control_set failed for setting default switch id\n");
        return rv;
    }

    return rv;
}



struct cint_mpls_deep_stack_am_params_s{
    bcm_if_t alternate_marking_if_loss;
    bcm_if_t alternate_marking_if_no_loss;
    int stat_id;
    int loss_KeyGenVar_period;
    int no_loss_KeyGenVar_period;
    int crps_database_id;
    int core_id;
    int byte_crps_database_id;
};

cint_mpls_deep_stack_am_params_s cint_mpls_deep_stack_alternate_marking_params = {
     /*
      * alternate_marking_if_loss, alternate_marking_if_no_loss
      */
     0,                              0,
     /*
      * stat_id
      */
     1,
     /*
      * loss_KeyGenVar_period,   no_loss_KeyGenVar_period
      */
     1,                            0, /** In this example using the first bit of KeyGenVar, i.e. profile 1, so using values 0 and 1 */
    0,0,1 /* Database-id, core ID to be filled by mpls_deep_stack_alternate_marking_crps()*/
};

/** Used for coordinating between setting the counter
 *  processor and getting the counters. */
struct cint_mpls_deep_stack_am_crps_params_s{
    uint32 total_nof_counters;
    int core;
    int engine;
    uint32 total_nof_byte_counters;
    int byte_engine;
};


cint_mpls_deep_stack_am_crps_params_s cint_mpls_deep_stack_alternate_marking_crps_params = {
    0, /* filled after creating the counters*/
    0,
    3, /* use engine 3*/
    0,
    4, /* use engine 4*/
};

enum test_type_on_encap_t {
    mpls_2plus2_on_vpn_label = 0,  /* test encap Flow Label, IN-Band Special Label and two mpls labels in encap 1 stage */
    mpls_2plus1_on_vpn_label = 1,  /* test encap Flow Label, IN-Band Special Label and one mpls label in encap 1 stage */
    mpls_2_on_vpn_label      = 2,  /* test encap Flow Label and IN-Band Special Label in encap 1 stage */
    test_type_on_encap_count = 3
};

test_type_on_encap_t test_type_on_encap = mpls_2plus2_on_vpn_label;

bcm_field_entry_t entry_handle_L_bit_1;
bcm_field_entry_t entry_handle_L_bit_0;

/*
 * Add ingress node PMF configuration per 5-tuple defining flow ID.
 * 6 Parameters per ingress entry, the sixth representing the L bit      .
 *                                                                .
 * Per flow (5-tuple), adding 2 PMF entries with two different action,                                                                                                     .
 * each action assigns a different counter.
 */
int
mpls_deep_stack_alternate_marking_ingress_field(
        int unit)
{
   int rv = BCM_E_NONE;
   bcm_field_entry_t entry_handle;

   /*
    * Configure cint params. First the entry for L bit =1.
    */
   g_cint_field_am_ing_ent.SrcIp = 0xA0A1A1A2;
   g_cint_field_am_ing_ent.DstIp = 0xA0A1A1A3;
   g_cint_field_am_ing_ent.ProtocolType = 6; /*TCP*/
   g_cint_field_am_ing_ent.L4Dst = 9000;
   g_cint_field_am_ing_ent.L4Src = 8000;
   g_cint_field_am_ing_ent.KeyGenVar_period = cint_mpls_deep_stack_alternate_marking_params.loss_KeyGenVar_period;

   g_cint_field_am_ing_ent.statId0 = 1; /* Counter 1*/
   g_cint_field_am_ing_ent.byteStatId1 = 1; /* Counter 1*/


   g_cint_field_am_ing_ent.out_lif_0_raw = BCM_L3_ITF_VAL_GET(cint_mpls_deep_stack_alternate_marking_params.alternate_marking_if_loss);
   printf("g_cint_field_am_ing_ent.out_lif_0_raw: %d", g_cint_field_am_ing_ent.out_lif_0_raw);

   rv = cint_field_alternate_marking_ingress_node_iPMF1(unit);
   if (rv != BCM_E_NONE)
   {
      printf("Error (%d), in cint_field_alternate_marking_ingress_node_iPMF1 \n", rv);
      return rv;
   }

   rv = cint_field_alternate_marking_ingress_node_entry_add(unit,&entry_handle_L_bit_1);
   if (rv != BCM_E_NONE)
   {
      printf("Error (%d), in cint_field_alternate_marking_ingress_node_entry_add \n", rv);
      return rv;
   }
    /* Alternate between the two counters per flow - Now configure the entry with L bit =0.*/
   /*For eviction purposes in the CRPS, its best to take counters as far away from each other.
     In this example we assume
           L=1 range: 1- total_nof_counters/2
           L=0 range: total_nof_counters/2 + 1 - total_nof_counters */
   g_cint_field_am_ing_ent.statId0  = cint_mpls_deep_stack_alternate_marking_crps_params.total_nof_counters /2 + 1;
   g_cint_field_am_ing_ent.byteStatId1  = cint_mpls_deep_stack_alternate_marking_crps_params.total_nof_byte_counters /2 + 1;
   g_cint_field_am_ing_ent.KeyGenVar_period = cint_mpls_deep_stack_alternate_marking_params.no_loss_KeyGenVar_period;
   g_cint_field_am_ing_ent.out_lif_0_raw = BCM_L3_ITF_VAL_GET(cint_mpls_deep_stack_alternate_marking_params.alternate_marking_if_no_loss);

   rv = cint_field_alternate_marking_ingress_node_entry_add(unit,&entry_handle_L_bit_0);
   if (rv != BCM_E_NONE)
   {
      printf("Error (%d), in cint_field_alternate_marking_ingress_node_entry_add \n", rv);
      return rv;
   }

   printf("Ingress node iPMF1 configuration Done! \n");

   rv = cint_field_alternate_marking_ingress_node_ePMF(unit);
   if (rv != BCM_E_NONE)
   {
      printf("Error (%d), in cint_field_alternate_marking_ingress_node_ePMF \n", rv);
      return rv;
   }
   printf("Ingress node ePMF configuration Done! \n");

   return rv;
}

/**
* \brief
*   Configure CRPS with IngressReceivePp source for alternate marking byte counting
*
*   Create database on the given core with the given engines,
*   OAM source, command id, database_id
* \par DIRECT INPUT:
*   \param [in] unit            -  UNIT_ID
*   \param [in] core            -  CORE_ID, BCM_CORE_ALL
*          supported
*   \param [in] source          -  OAM source typede
*   \param [in] command_id      -  command_id
*   \param [in] nof_engines     -  number of engines to configure
*   \param [in] engine_id_array -  array with engine ids to configure
*   \param [in] counter_base    -  the start of the counter range
*   \param [in] database_id     -  database_id (0-21)
*   \param [out] actual_nof_counters - actual num of counters in
*          the database
* \par INDIRECT INPUT:
*   * None
* \par DIRECT OUTPUT:
*   int -
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
int
mpls_deep_stack_alternate_marking_byte_counter_database_set(
    int unit,
    int core_id,
    bcm_stat_counter_interface_type_t source,
    int command_id,
    int nof_engines,
    int *engine_id_array,
    int counter_base,
    int database_id,
    uint32 *actual_nof_counters)
{
    int rv, flags = 0, i = 0;
    bcm_stat_counter_database_t database;
    bcm_stat_engine_t engine;
    bcm_stat_counter_enable_t enable_config;
    bcm_stat_counter_interface_t interface;
    bcm_stat_counter_set_map_t ctr_set_map;
    bcm_stat_counter_interface_key_t interface_key;
    bcm_stat_expansion_select_t expansion_select;
    bcm_stat_counter_engine_control_t control = bcmStatCounterClearAll;
    bcm_stat_expansion_data_mapping_t data_mapping_array[1];
    bcm_stat_counter_format_type_t format_type = bcmStatCounterFormatBytes;
    int counter_set_size = 1; /** For OAM sources counter_set_size should be always 1 */
    int type_id = 0; /** Configure only one type */
    uint32 engine_size;
    uint32 total_nof_counters = 0; /** Calculate the size of the database*/
    bcm_stat_eviction_t eviction;
    uint32 eviction_flags = 0;
    uint32 feature_conditional_eviction_support =
        *dnxc_data_get(unit, "crps", "eviction", "conditional_action_is_supported", NULL);
    uint32 *conditional_no_eviction_support;
    int temp = 0, action_idx = -1;


    /** calc no eviction flag bit index */
    while ((BCM_STAT_EVICTION_CONDITIONAL_ACTION_NO_EVICTION & temp) == 0)
    {
        action_idx++;
        temp = 1 << action_idx;
    }
    conditional_no_eviction_support =
            dnxc_data_1d_get(unit, "crps", "eviction", "condional_action_valid", "valid", action_idx);


    bcm_stat_eviction_t_init(&eviction);
    bcm_stat_counter_database_t_init(&database);
    bcm_stat_engine_t_init(&engine);
    bcm_stat_counter_set_map_t_init(&ctr_set_map);
    bcm_stat_expansion_data_mapping_t_init(&data_mapping_array);
    bcm_stat_counter_interface_key_t_init(&interface_key);
    bcm_stat_expansion_select_t_init(&expansion_select);
    bcm_stat_counter_interface_t_init(&interface);
    bcm_stat_counter_enable_t_init(&enable_config);
    ctr_set_map.expansion_data_mapping = data_mapping_array;
    /** check if the given source are indeed OAM sources
    * command id will be verified inside the API */

    if (source != bcmStatCounterInterfaceIngressReceivePp)
    {
         printf("Error in crps_oam_source_engines_set - call the function with source %d\n", source);
         return BCM_E_PARAM;
    }
    /** configure expansion */
    expansion_select.nof_elements = 0;
    interface_key.command_id = command_id;
    interface_key.core_id = core_id;
    interface_key.interface_source = source;
    interface_key.type_id = type_id;
    rv = bcm_stat_counter_expansion_select_set(unit, flags, &interface_key, &expansion_select);
    if (rv != BCM_E_NONE)
    {
        printf("Error in bcm_stat_counter_expansion_select_set\n");
        return rv;
    }

    /** create database */
    rv = bcm_stat_counter_database_create(unit, BCM_STAT_DATABASE_CREATE_WITH_ID, core_id, database_id);
    if (rv != BCM_E_NONE)
    {
        printf("Error in bcm_stat_counter_database_create\n");
        return rv;
    }
    database.database_id = database_id;
    database.core_id = core_id;

    eviction.dma_fifo_select = 0;
    eviction.record_format = bcmStatEvictionRecordFormatPhysical;
    eviction.eviction_event_id = database_id;
    eviction.type = bcmStatEvictionDestinationLocalHost;
    /** optimization - do not evict a counter which its value is zero */
    /** HW compare 34 bits of the counter */
    if ((*conditional_no_eviction_support == TRUE) && (feature_conditional_eviction_support == TRUE))
    {
        eviction_flags |= BCM_STAT_EVICTION_CONDITIONAL_ENABLE;
        eviction.cond.action_flags = BCM_STAT_EVICTION_CONDITIONAL_ACTION_NO_EVICTION;
        eviction.cond.condition_source_select = bcmStatEvictionConditionalSourceUserData;
        COMPILER_64_SET(eviction.cond.condition_user_data, 0x0, 0x0);
        eviction.cond.qualifier = bcmStatEvictionConditionalQualOrEqualZero;
    }

    eviction.eviction_algorithmic_disable = 1;

     /** calling the APIs per engine - attach engines to the
      *  database  */
    for (i = 0; i < nof_engines; i++)
    {
        engine.core_id = core_id;
        engine.engine_id = engine_id_array[i];
        /** attach the engines to the database */
        rv = bcm_stat_counter_engine_attach(unit, flags, &database, engine_id_array[i]);
        if (rv != BCM_E_NONE)
        {
            printf("Error in bcm_stat_counter_engine_attach\n");
            return rv;
        }
        rv = bcm_stat_counter_eviction_set(unit, eviction_flags, &engine, &eviction);
        if (rv != BCM_E_NONE)
        {
            printf("Error in bcm_stat_counter_eviction_set\n");
            return rv;
        }
        /** add engine size to the total number of counters in the
         *  database to get the database size */
        engine_size = (*dnxc_data_1d_get(unit, "crps", "engine", "engines_info", "nof_entries", engine_id_array[i])) *
                (*dnxc_data_1d_get(unit, "crps", "engine", "counter_format_types", "nof_counters_per_entry", format_type));
        total_nof_counters = total_nof_counters + engine_size;
    }
    /** the mode is double entry */
    *actual_nof_counters = total_nof_counters;

    /** configure the counter interface for the OAM crps database */
    interface.source = source;
    interface.command_id = command_id;
    interface.format_type = format_type;
    interface.counter_set_size = counter_set_size;
    interface.type_config[type_id].valid = TRUE;
    interface.type_config[type_id].object_type_offset = 0; /** counter_set_size is 1 => there is one offset - offset 0*/
    interface.type_config[type_id].start = counter_base; /** user selected what the counter base is*/
    interface.type_config[type_id].end = counter_base + *actual_nof_counters - 1; /** untill the end of the database size*/
    rv = bcm_stat_counter_interface_set(unit, flags, &database, &interface);
    if (rv != BCM_E_NONE)
    {
        printf("Error in bcm_stat_counter_interface_set\n");
        return rv;
    }

    /** configure the counter set mapping for the database */
    ctr_set_map.nof_entries = 1;
    ctr_set_map.expansion_data_mapping[0].nof_key_conditions = 0;
    ctr_set_map.expansion_data_mapping[0].value.counter_set_offset = 0;
    ctr_set_map.expansion_data_mapping[0].value.valid = TRUE;
    rv = bcm_stat_counter_set_mapping_set(unit, flags, &database, &ctr_set_map);
    if (rv != BCM_E_NONE)
    {
        printf("Error in bcm_stat_counter_set_mapping_set\n");
        return rv;
    }

     /** enable the database */
    enable_config.enable_counting = TRUE;
    enable_config.enable_eviction = FALSE;
    if (crps_oam_config_enable_eviction)    {
        enable_config.enable_eviction = TRUE; /** enable eviction for OAMP/IngressOAM source */
    }
    rv = bcm_stat_counter_database_enable_set(unit, flags, &database, &enable_config);
    if (rv != BCM_E_NONE)
    {
        printf("Error in bcm_stat_counter_database_enable_set\n");
        return rv;
    }

    return BCM_E_NONE;
}

/* Add CRPS configuration */
int
mpls_deep_stack_alternate_marking_crps(int unit,  int in_port)
{
    int rv = BCM_E_NONE;
    bcm_stat_pp_profile_info_t pp_profile;
    int core_id,  tm_port;
    int counter_base = 0;
    int pkt_counter_database_id = 0;
    int byte_counter_database_id2 = 1;
    int byte_counter_command_id = 8;
    bcm_stat_engine_t engine;

    rv = get_core_and_tm_port_from_port(unit, in_port, &core_id, &tm_port);
    if (rv != BCM_E_NONE) {
       printf("Error, in get_core_and_tm_port_from_port\n");
       return rv;
    }
    cint_mpls_deep_stack_alternate_marking_crps_params.core = core_id;

    rv = crps_oam_database_set(unit, core_id, bcmStatCounterInterfaceIngressOam, g_cint_field_am_ing_ent.command_id , 1,
                               &(cint_mpls_deep_stack_alternate_marking_crps_params.engine), counter_base, pkt_counter_database_id,
                               &cint_mpls_deep_stack_alternate_marking_crps_params.total_nof_counters);
    if (rv != BCM_E_NONE)
    {
        printf("Error, crps_oam_database_set \n");
        return rv;
    }

    /* For testing purposes, use stat-id 8*/
    cint_mpls_deep_stack_alternate_marking_params.stat_id = 8;
    cint_mpls_deep_stack_alternate_marking_params.core_id = core_id;
    cint_mpls_deep_stack_alternate_marking_params.crps_database_id = pkt_counter_database_id;

    bcm_stat_engine_t_init(&engine);
    /* Set the eviction rate to 0.25 milliseconds per counter.
       8K counters in this engine, so this comes out to ~2 seconds to evict the whole engine. */
    engine.engine_id = cint_mpls_deep_stack_alternate_marking_crps_params.engine;
    engine.core_id = core_id;
    rv = bcm_stat_counter_engine_control_set(unit,0,engine,bcmStatCounterSequentialSamplingInterval,250);
    if (rv != BCM_E_NONE)
    {
        printf("Error, bcm_stat_counter_engine_control_set \n");
        return rv;
    }

    if (stat_mode_pkt_and_byte == 1) {
        /* configure counter database for byte counting */
        rv = mpls_deep_stack_alternate_marking_byte_counter_database_set(unit, core_id, bcmStatCounterInterfaceIngressReceivePp, g_cint_field_am_ing_ent.byte_command_id1 , 1,
                                   &(cint_mpls_deep_stack_alternate_marking_crps_params.byte_engine), counter_base, byte_counter_database_id2,
                                   &cint_mpls_deep_stack_alternate_marking_crps_params.total_nof_byte_counters);
        if (rv != BCM_E_NONE)
        {
            printf("Error, crps_oam_am_byte_counter_database_set \n");
            return rv;
        }

        cint_mpls_deep_stack_alternate_marking_params.byte_crps_database_id = byte_counter_database_id2;

        bcm_stat_engine_t_init(&engine);
        /* Set the eviction rate to 0.25 milliseconds per counter.
         8K counters in this engine, so this comes out to ~2 seconds to evict the whole engine. */
        engine.engine_id = cint_mpls_deep_stack_alternate_marking_crps_params.byte_engine;
        engine.core_id = core_id;
        rv = bcm_stat_counter_engine_control_set(unit,0,engine,bcmStatCounterSequentialSamplingInterval,250);
        if (rv != BCM_E_NONE)
        {
            printf("Error, bcm_stat_counter_engine_control_set \n");
            return rv;
        }

        /* Disable header truncate for byte counter */
        bcm_stat_counter_command_id_key_t key;
        int enable = 0;
        key.core_id = BCM_CORE_ALL;
        key.command_id = byte_counter_command_id;
        key.source = bcmStatCounterInterfaceIngressReceivePp;
        rv = bcm_stat_pkt_size_adjust_select_get(unit, 0, &key, bcmStatPktSizeSelectCounterIngressHeaderTruncate, &enable);
        if (rv != BCM_E_NONE)
        {
            printf("Error, bcm_stat_pkt_size_adjust_select_get \n");
            return rv;
        }
        enable = 0;
        rv = bcm_stat_pkt_size_adjust_select_set(unit, 0, &key, bcmStatPktSizeSelectCounterIngressHeaderTruncate, enable);
        if (rv != BCM_E_NONE)
        {
            printf("Error, bcm_stat_pkt_size_adjust_select_set \n");
            return rv;
        }
    }

    return rv;
}

int
mpls_deep_stack_alternate_marking_encapsulation_example(
    int unit,
    int in_port,
    int out_port,
    int nof_tunnel)
{
    int rv = BCM_E_NONE;
    int encap_access_array[7] = {
                                        bcmEncapAccessNativeArp,
                                        bcmEncapAccessTunnel1,
                                        bcmEncapAccessTunnel2,
                                        bcmEncapAccessTunnel3,
                                        bcmEncapAccessTunnel4,
                                        bcmEncapAccessArp,
                                        bcmEncapAccessInvalid
                                    };
    int encap_access_idx = 0;
    int mpls_tunnel_id = 0;
    bcm_mpls_label_t stage_enc_label_1 = 0x3331;
    bcm_mpls_label_t stage_enc_label_2 = 0x4441;

    MPLS_UTIL_MAX_NOF_ENTITIES = 2;

    init_default_mpls_params(unit, in_port, out_port);

    mpls_tunnel_initiator_create_s_init(mpls_util_entity[0].mpls_encap_tunnel, MPLS_UTIL_MAX_NOF_TUNNELS);

    /* encapsulation entries, not including alternate marking entries */
    for (mpls_tunnel_id = 0; mpls_tunnel_id < nof_tunnel; mpls_tunnel_id++, encap_access_idx++, stage_enc_label_1++, stage_enc_label_2++)
    {
        mpls_util_entity[0].mpls_encap_tunnel[mpls_tunnel_id].label[0] = stage_enc_label_1;
        mpls_util_entity[0].mpls_encap_tunnel[mpls_tunnel_id].label[1] = stage_enc_label_2;
        mpls_util_entity[0].mpls_encap_tunnel[mpls_tunnel_id].num_labels = 2;
        mpls_util_entity[0].mpls_encap_tunnel[mpls_tunnel_id].flags |= BCM_MPLS_EGRESS_LABEL_TTL_DECREMENT | BCM_MPLS_EGRESS_LABEL_TANDEM;
        mpls_util_entity[0].mpls_encap_tunnel[mpls_tunnel_id].l3_intf_id = &mpls_util_entity[0].mpls_encap_tunnel[mpls_tunnel_id+1].tunnel_id;
        mpls_util_entity[0].mpls_encap_tunnel[mpls_tunnel_id].encap_access = encap_access_array[encap_access_idx];
        mpls_util_entity[0].mpls_encap_tunnel[mpls_tunnel_id].egress_qos_model.egress_qos = bcmQosEgressModelPipeMyNameSpace;
        mpls_util_entity[0].mpls_encap_tunnel[mpls_tunnel_id].exp0 = 1;
        mpls_util_entity[0].mpls_encap_tunnel[mpls_tunnel_id].exp1 = 1;
    }
    if (mpls_2plus1_on_vpn_label == test_type_on_encap)
    {
        mpls_util_entity[0].mpls_encap_tunnel[0].num_labels = 1;
    }
    else if (mpls_2_on_vpn_label == test_type_on_encap)
    {
        mpls_util_entity[0].mpls_encap_tunnel[0].flags &= ~BCM_MPLS_EGRESS_LABEL_TANDEM;
    }

    mpls_util_entity[0].mpls_encap_tunnel[mpls_tunnel_id-1].l3_intf_id = &mpls_util_entity[1].arps[0].arp;

    /* configure ARP+AC in single ETPS entry */
    mpls_util_entity[1].arps[0].flags2 |= BCM_L3_FLAGS2_VLAN_TRANSLATION;

    rv = mpls_util_main(unit,in_port,out_port);
    if (rv) {
        printf("Error, create_mpls_tunnel\n");
        return rv;
    }

    /* Set Alternate Marking special label switch control */
    int speacial_label_value = 10;
    if (verbose >= 1)
    {
        printf("Set alternate marking encapsulation special label switch control\n");
    }
    rv = bcm_switch_control_set(unit, bcmSwitchMplsAlternateMarkingSpecialLabel, speacial_label_value);
    if (rv) {
        printf("Error, bcm_switch_control_set bcmSwitchMplsAlternateMarkingSpecialLabel\n");
        return rv;
    }

    /*
     * Add Alternate Marking encapsulation: LOSS bit off
     */
    mpls_util_mpls_tunnel_initiator_create_s mpls_encap_tunnel[1];
    mpls_encap_tunnel[0].label[0] = 0x1234;
    mpls_encap_tunnel[0].label[1] = BCM_MPLS_LABEL_INVALID;
    mpls_encap_tunnel[0].num_labels = 2;
    mpls_encap_tunnel[0].flags |= BCM_MPLS_EGRESS_LABEL_TTL_DECREMENT | BCM_MPLS_EGRESS_LABEL_ALTERNATE_MARKING;
    mpls_encap_tunnel[0].encap_access = bcmEncapAccessRif;
    mpls_encap_tunnel[0].qos_map_id = 0;
    mpls_encap_tunnel[0].egress_qos_model.egress_qos = bcmQosEgressModelPipeMyNameSpace;
    mpls_encap_tunnel[0].exp0 = 0;
    mpls_encap_tunnel[0].exp1 = 1;

    if (verbose >= 1)
    {
        printf("Configure alternate marking encapsulation entries\n");
    }
    rv = mpls_create_initiator_tunnels(unit, mpls_encap_tunnel, 1);
    if (rv != BCM_E_NONE)
    {
        printf("Error, in mpls_create_initiator_tunnels\n");
        return rv;
    }
    cint_mpls_deep_stack_alternate_marking_params.alternate_marking_if_no_loss = mpls_encap_tunnel[0].tunnel_id;

    /*
     * Add alternate marking encapsulation: LOSS bit on
     */
    mpls_encap_tunnel[0].flags |= BCM_MPLS_EGRESS_LABEL_TTL_DECREMENT | BCM_MPLS_EGRESS_LABEL_ALTERNATE_MARKING | BCM_MPLS_EGRESS_LABEL_ALTERNATE_MARKING_LOSS_SET;

    rv = mpls_create_initiator_tunnels(unit, mpls_encap_tunnel, 1);
    if (rv != BCM_E_NONE)
    {
        printf("Error, in mpls_create_initiator_tunnels\n");
        return rv;
    }
    cint_mpls_deep_stack_alternate_marking_params.alternate_marking_if_loss = mpls_encap_tunnel[0].tunnel_id;
    printf("cint_mpls_deep_stack_alternate_marking_params.alternate_marking_if_loss:%d\n/n", cint_mpls_deep_stack_alternate_marking_params.alternate_marking_if_loss);

    /*
     * Add CRPS configuration
     */
    rv = mpls_deep_stack_alternate_marking_crps(unit, in_port);
    if (rv != BCM_E_NONE)
    {
        printf("Error in mpls_deep_stack_alternate_marking_crps\n");
        return rv;
    }

    /*
     * Configure PMF rules
     */
    rv = mpls_deep_stack_alternate_marking_ingress_field(unit);
    if (rv != BCM_E_NONE)
    {
        printf("Error in mpls_deep_stack_alternate_marking_ingress_field\n");
        return rv;
    }

    rv = mpls_deep_stack_alternate_marking_snoop(unit, cint_field_am_egress_snoop_id);
    if (rv != BCM_E_NONE)
    {
        printf("Error in mpls_deep_stack_alternate_marking_field\n");
        return rv;
    }


    if (tod_append_mode ==2)
    {
        /*
         * Time of day gotten through mirror additional info.
         * This requires initializing through a cint from cint_ifa.c
         * Only when the in_port is a NIF port.
         */
        if (in_port_is_nif)
        {
            BCM_IF_ERROR_RETURN( cint_instru_config_nif_rx_timestamp(unit,in_port,0));
        }
    }
    else if (tod_append_mode ==1)
    {
        /*
        * Timestamp information when D bit is set is gotten through tail-edit meta data.
        * Switch id parameter is the node ID field.
        */
        BCM_IF_ERROR_RETURN(cint_instru_ipt_main(unit, 0xab, 0));
    }
    else
    {
        print "ERROR: tod_append_mode must be either 1 (use tail-edit) or 2 (use mirror-additional-info)";
        return  123;
    }

    return rv;
}


/**
 * Snooping configuration for alternate marking ingress node:
 * 1. Set snoop destination
 * 2. Set tail edit profile which appends the tail edit header
 *
 * @param unit
 * @param snoop_cmnd
 *
 * @return int
 */
int mpls_deep_stack_alternate_marking_snoop(int unit, int snoop_cmnd) {
    bcm_mirror_header_info_t mirror_header_info;
    bcm_mirror_destination_t mirror_dest;
    bcm_port_config_t port_config;
    int cpu_port;
    bcm_instru_ipt_t config;


    /** First, get the CPU port */
    bcm_mirror_destination_t_init(&mirror_dest);
    BCM_IF_ERROR_RETURN(bcm_port_config_get(unit, &port_config));
    BCM_PBMP_ITER(port_config.cpu, cpu_port)
    {
        mirror_dest.gport = cpu_port;
        break;
    }

    mirror_dest.flags = BCM_MIRROR_DEST_IS_SNOOP| BCM_MIRROR_DEST_WITH_ID |BCM_MIRROR_DEST_REPLACE  ;
    if (tod_append_mode==2)
    {
        /* Add additional 64B of original system-headers, including ingress, egress TOD */
        mirror_dest.flags |= BCM_MIRROR_DEST_EGRESS_ADD_ORIG_SYSTEM_HEADER;
    }
    mirror_dest.packet_control_updates.valid = BCM_MIRROR_PKT_HEADER_UPDATE_FABRIC_HEADER_EDITING;
    BCM_GPORT_MIRROR_SET(mirror_dest.mirror_dest_id, snoop_cmnd);
    BCM_IF_ERROR_RETURN(bcm_mirror_destination_create(unit, &mirror_dest));

    /**
    *  Call mirror-header-set.
    *  When tod_append_mode = 1 this is required for adding
    *  tail-edit information.
    *  When tod_append_mode = 2 this is required to add FHEI on the
    *  first set of system headers. trap-code on FHEI can be used to
    *  signify the existence of another set of system headers.
    *  The value will be 90 + snoop_cmnd (i.e. EgTxFieldSnoop1 when
    *  snoop_cmnd is 1).
    *
    */
        bcm_mirror_header_info_t_init(&mirror_header_info);
        if (tod_append_mode == 1)
        {
            mirror_header_info.pp.tail_edit_profile = CINT_INSTRU_IPT_TAIL_EDIT_PROFILE;
            mirror_header_info.tm.ase_ext.ase_type = bcmPktDnxAseTypeInt;
            mirror_header_info.tm.ase_ext.valid = 1;
        }
        BCM_IF_ERROR_RETURN(bcm_mirror_header_info_set(unit, BCM_MIRROR_DEST_IS_SNOOP, mirror_dest.mirror_dest_id, &mirror_header_info));

    return 0;
}


/**
 * Get the counter value for the session configured in this
 * cint.
 * Two separate counters may be gotten - with the L bit set and
 * without.
 * Note that getting the counter while traffic is running will
 * result in inconsistent behavior in the counter processor!
 * When L bit is set through
 * cint_field_alternate_marking_period_change(), call this API
 * with L bit 0 and the other way around.
 *
 * @param unit
 * @param l_bit_set
 * @param counter
 * @param ingress_node
 *
 * @return int
 */
int mpls_deep_stack_alternate_marking_get_counter(int unit, int l_bit_set, int * counter) {
    bcm_stat_counter_input_data_t input_data;
    bcm_stat_counter_output_data_t output_data;
    int stat_array[64];
    const uint32 *max_counter_set_size = dnxc_data_get(unit, "crps", "engine", "max_counter_set_size", NULL);
    bcm_stat_counter_value_t counter_value[(*max_counter_set_size) * 2];
    int source_id;
    uint64 counter_value_64b;

    bcm_stat_counter_input_data_t_init(&input_data);
    bcm_stat_counter_output_data_t_init(&output_data);

    /* Counters used for the entry set in this cint: 1 with L bit set, total_nof_counters/2 without*/
    source_id = l_bit_set ? 1 :cint_mpls_deep_stack_alternate_marking_crps_params.total_nof_counters /2 + 1 ;

    stat_array[0] = BCM_STAT_COUNTER_STAT_SET(0,0);
    input_data.core_id = cint_mpls_deep_stack_alternate_marking_crps_params.core;
    input_data.database_id = 0;
    input_data.type_id = 0;
    input_data.counter_source_id = source_id;
    input_data.nstat = 1;
    input_data.stat_arr = stat_array;

    output_data.value_arr = counter_value;

    BCM_IF_ERROR_RETURN(bcm_stat_counter_get(unit, BCM_STAT_COUNTER_CLEAR_ON_READ, &input_data, &output_data));

    counter_value_64b = output_data.value_arr[0].value;

    COMPILER_64_TO_32_LO(*counter,counter_value_64b);

    return 0;

}


/**
 * Function should be called immediatly after
 * cint_field_alternate_marking_period_change(), before reading
 * the counter.
 *
 * This enables reading the inactive counter i.e. if
 * transmitting with the L bit set enable reading the counters
 * with L bit unset.
 *
 * Counters should be read after a sufficient period of time has
 * passed after this function was called to allow eviction.
 *
 * @param unit
 * @param new_L_bit - set to 1 when switching from packets with
 *                  L=0 to L=1. Set to 0 when going the other
 *                  way.
 *
 * @return int
 */
int switch_counter_procedure_before_reading(int unit, int active_L_bit){
    bcm_stat_counter_database_t database;
    bcm_stat_eviction_boundaries_t boundaries;
    bcm_stat_counter_enable_t enable_config;
    int nof_counter_type = 1;
    int i = 0;
    int nof_counters = 0;

    nof_counter_type = (stat_mode_pkt_and_byte == 1) ? 2 : 1;
    for (i = 0; i < nof_counter_type; i++) {
        nof_counters = (i == 0) ? cint_mpls_deep_stack_alternate_marking_crps_params.total_nof_counters :
            cint_mpls_deep_stack_alternate_marking_crps_params.total_nof_byte_counters;

        bcm_stat_eviction_boundaries_t_init(&boundaries);
        bcm_stat_counter_database_t_init(&database);
        bcm_stat_counter_enable_t_init(&enable_config);

        database.database_id = (i == 0) ? cint_mpls_deep_stack_alternate_marking_params.crps_database_id :
            cint_mpls_deep_stack_alternate_marking_params.byte_crps_database_id;
        database.core_id = cint_mpls_deep_stack_alternate_marking_params.core_id;

        /* Step 1: Set the eviction boundry on the active counter. */
        if (active_L_bit)
        {
            /* Going from L=0 to L=1.
               Need to enable eviction on the L=0 range, disable on L=1 range.
               This means evict on the range
               total_nof_counters /2  to total_nof_counters.
               */
            boundaries.start = nof_counters / 2;
            boundaries.end = nof_counters - 1;
        } else {
            /* Other way around.
               0 to total_nof_counters/2*/
            boundaries.start = 0;
            boundaries.end = nof_counters / 2 - 1;
        }
        BCM_IF_ERROR_RETURN(bcm_stat_database_eviction_boundaries_set(unit,0,&database,0,&boundaries)); /* tpye ID is 0 for OAM counters*/

        /* Step 2: Enable eviction on the engine.
           Becasue of step 1, eviction will only take place in the inactive range.*/

        enable_config.enable_counting = TRUE; /* Set to true in any case*/
        enable_config.enable_eviction = TRUE;
        BCM_IF_ERROR_RETURN(bcm_stat_counter_database_enable_set(unit, 0, &database, &enable_config));

    }

    return 0;
}


/**
 * Procedure for reading the inactive counter. 3 steps:
 * 1. Set eviction boundaries to disable eviction on active
 * counter range.
 *
 * 2. Enable eviction on the engine. Due to step 1 eviction will
 * only be enabled on the inactive range
 *
 * 3. Wait. This is required for eviction to occur (SW counters
 * get the HW counters)
 *
 * 4. Read the inactive counter
 *
 * 5. Disable eviction globally
 *
 * @param unit
 * @param active_L_bit - Read the opposite counter
 * @param counter
 *
 * @return int
 */
int read_counter_and_handle_eviction(int unit, int active_L_bit, int * counter) {
    bcm_stat_counter_enable_t enable_config;
    bcm_stat_counter_database_t database;
    bcm_stat_counter_database_t_init(&database);
    bcm_stat_counter_enable_t_init(&enable_config);

    BCM_IF_ERROR_RETURN(switch_counter_procedure_before_reading(unit, active_L_bit));

    print "Succesfully set eviction boundaries and enabled eviction. Going to sleep to allow reading the counters.";
    sal_sleep(2); /* Wait for eviction to take place*/

    BCM_IF_ERROR_RETURN(mpls_deep_stack_alternate_marking_get_counter(unit,!active_L_bit,counter));
    printf("Read the counter, value is %d. Now disabling eviction back\n",*counter);


    /* Now disable eviction back on all the range.
       Otherwise, when we switch back the L bit counters will not be stamped on ASE and packet flow will be incorrect.*/
    database.database_id = cint_mpls_deep_stack_alternate_marking_params.crps_database_id;
    database.core_id = cint_mpls_deep_stack_alternate_marking_params.core_id;
    enable_config.enable_counting = TRUE; /* Set to true in any case*/
    enable_config.enable_eviction = FALSE;
    BCM_IF_ERROR_RETURN(bcm_stat_counter_database_enable_set(unit, 0, &database, &enable_config));

    return 0;
}

/**
 * Get the counter value for the session configured in this
 * cint.
 * Two separate counters may be gotten - with the L bit set and
 * without.
 * Note that getting the counter while traffic is running will
 * result in inconsistent behavior in the counter processor!
 * When L bit is set through
 * cint_field_alternate_marking_period_change(), call this API
 * with L bit 0 and the other way around.
 *
 * @param unit
 * @param l_bit_set
 * @param pkt_counter
 * @param byte_counter
 * @param ingress_node
 *
 * @return int
 */
int mpls_deep_stack_alternate_marking_get_counter2(int unit, int l_bit_set, int* pkt_counter, int* byte_counter) {
    bcm_stat_counter_input_data_t input_data;
    bcm_stat_counter_output_data_t output_data;
    int stat_array[64];
    const uint32 *max_counter_set_size = dnxc_data_get(unit, "crps", "engine", "max_counter_set_size", NULL);
    bcm_stat_counter_value_t counter_value[(*max_counter_set_size) * 2];
    int source_id;
    uint64 counter_value_64b;
    int NOF_COUNTER_TYPE = 2;
    int i = 0;
    int nof_counters = 0;

    if (stat_mode_pkt_and_byte != 1) {
        printf("Error in mpls_deep_stack_alternate_marking_get_counter2 - valid only when stat_mode_pkt_and_byte is 1\n");
        return BCM_E_PARAM;
    }

    for (i = 0; i < NOF_COUNTER_TYPE; i++) {
        nof_counters = (i == 0) ? cint_mpls_deep_stack_alternate_marking_crps_params.total_nof_counters :
            cint_mpls_deep_stack_alternate_marking_crps_params.total_nof_byte_counters;
        bcm_stat_counter_input_data_t_init(&input_data);
        bcm_stat_counter_output_data_t_init(&output_data);

        /* Counters used for the entry set in this cint: 1 with L bit set, total_nof_counters/2 without*/
        source_id = l_bit_set ? 1 : nof_counters /2 + 1 ;

        stat_array[0] = BCM_STAT_COUNTER_STAT_SET(0,0);
        input_data.core_id = cint_mpls_deep_stack_alternate_marking_crps_params.core;
        input_data.database_id = (i == 0) ? cint_mpls_deep_stack_alternate_marking_params.crps_database_id :
            cint_mpls_deep_stack_alternate_marking_params.byte_crps_database_id;
        input_data.type_id = 0;
        input_data.counter_source_id = source_id;
        input_data.nstat = 1;
        input_data.stat_arr = stat_array;

        output_data.value_arr = counter_value;

        BCM_IF_ERROR_RETURN(bcm_stat_counter_get(unit, BCM_STAT_COUNTER_CLEAR_ON_READ, &input_data, &output_data));

        counter_value_64b = output_data.value_arr[0].value;
        if (i == 0) {
            COMPILER_64_TO_32_LO(*pkt_counter,counter_value_64b);
        } else {
            COMPILER_64_TO_32_LO(*byte_counter,counter_value_64b);
        }
    }

    return 0;

}

/**
 * Procedure for reading the inactive counter. 3 steps:
 * 1. Set eviction boundaries to disable eviction on active
 * counter range.
 *
 * 2. Enable eviction on the engine. Due to step 1 eviction will
 * only be enabled on the inactive range
 *
 * 3. Wait. This is required for eviction to occur (SW counters
 * get the HW counters)
 *
 * 4. Read the inactive counter
 *
 * 5. Disable eviction globally
 *
 * @param unit
 * @param active_L_bit - Read the opposite counter
 * @param pkt_counter
 * @param byte_counter
 *
 * @return int
 */
int read_counter2_and_handle_eviction(int unit, int active_L_bit, int* pkt_counter, int* byte_counter) {
    bcm_stat_counter_enable_t enable_config;
    bcm_stat_counter_database_t database;
    int NOF_COUNTER_TYPE = 2;
    int i = 0;

    if (stat_mode_pkt_and_byte != 1) {
        printf("Error in mpls_deep_stack_alternate_marking_get_counter2 - valid only when stat_mode_pkt_and_byte is 1\n");
        return BCM_E_PARAM;
    }

    bcm_stat_counter_database_t_init(&database);
    bcm_stat_counter_enable_t_init(&enable_config);

    BCM_IF_ERROR_RETURN(switch_counter_procedure_before_reading(unit, active_L_bit));

    print "Succesfully set eviction boundaries and enabled eviction. Going to sleep to allow reading the counters.";
    sal_sleep(2); /* Wait for eviction to take place*/

    BCM_IF_ERROR_RETURN(mpls_deep_stack_alternate_marking_get_counter2(unit,!active_L_bit,pkt_counter,byte_counter));
    printf("Read the pkt counter, value is %d. Now disabling eviction back\n",*pkt_counter);
    printf("Read the byte counter, value is %d. Now disabling eviction back\n",*byte_counter);


    for (i = 0; i < NOF_COUNTER_TYPE; i++) {
        /* Now disable eviction back on all the range.
           Otherwise, when we switch back the L bit counters will not be stamped on ASE and packet flow will be incorrect.*/
        database.database_id = (i == 0) ? cint_mpls_deep_stack_alternate_marking_params.crps_database_id :
            cint_mpls_deep_stack_alternate_marking_params.byte_crps_database_id;
        database.core_id = cint_mpls_deep_stack_alternate_marking_params.core_id;
        enable_config.enable_counting = TRUE; /* Set to true in any case*/
        enable_config.enable_eviction = FALSE;
       BCM_IF_ERROR_RETURN(bcm_stat_counter_database_enable_set(unit, 0, &database, &enable_config));
    }

    return 0;
}


/**************************/
/** Intermediate/termination node*/

/**
 * PMF Configuration for intermidiate or egress node.
 *
 * @param unit
 * @param is_inter_pe 1 is for intermediate PE node;
 *
 * @return int
 */
int mpls_alternate_marking_intermediate_field(int unit, int is_inter_pe) {
    bcm_field_entry_t entry_handle;
    int rv = BCM_E_NONE;

    printf("=================================== \n");
    printf("intermidiate or egress node Start \n");
    printf("=================================== \n");

    rv = cint_field_alternate_marking_inter_or_egress_node_iPMF1(unit, is_inter_pe);
    if (rv != BCM_E_NONE)
    {
       printf("Error (%d), in cint_field_alternate_marking_inter_or_egress_node_iPMF1 \n", rv);
       return rv;
    }

    printf("I o E Node iPMF1 configuration Done! \n");
    rv = cint_field_alternate_marking_inter_or_egress_node_iPMF2_fg_add(unit);
    if (rv != BCM_E_NONE)
    {
       printf("Error (%d), in cint_field_alternate_marking_inter_or_egress_iPMF2_fg_add \n", rv);
       return rv;
    }

    printf("I o E Node iPMF2 FG_ADD Done! \n");

    rv = cint_field_alternate_marking_inter_or_egress_iPMF2_attach(unit);
    if (rv != BCM_E_NONE)
    {
       printf("Error (%d), in cint_field_alternate_marking_inter_or_egress_iPMF2_attach \n", rv);
       return rv;
    }
    printf("I o E Node iPMF2 Attach Done! \n");

    rv = cint_field_alternate_marking_inter_or_egress_node_iPMF1_entry_add(unit,&entry_handle);
    if (rv != BCM_E_NONE)
    {
       printf("Error (%d), in cint_field_alternate_marking_inter_or_egress_node_iPMF1_entry_add \n", rv);
       return rv;
    }

    /** Add 2 entries - one with L bit set and counter 1, another
     *  with L bit cleared and a higher counter in the range. */
    g_cint_field_am_i_o_e_ipmf2_flow_ent.L_bit = 1;
    g_cint_field_am_i_o_e_ipmf2_flow_ent.statId0 = 1;
    rv = cint_field_alternate_marking_inter_or_egress_node_iPMF2_flow_entry_add(unit,&entry_handle);
    if (rv != BCM_E_NONE)
    {
       printf("Error (%d), in cint_field_alternate_marking_inter_or_egress_node_iPMF2_flow_entry_add \n", rv);
       return rv;
    }

    g_cint_field_am_i_o_e_ipmf2_flow_ent.L_bit = 0;
    g_cint_field_am_i_o_e_ipmf2_flow_ent.statId0 += cint_mpls_deep_stack_alternate_marking_crps_params.total_nof_counters /2;
    rv = cint_field_alternate_marking_inter_or_egress_node_iPMF2_flow_entry_add(unit,&entry_handle);
    if (rv != BCM_E_NONE)
    {
       printf("Error (%d), in cint_field_alternate_marking_inter_or_egress_node_iPMF2_flow_entry_add \n", rv);
       return rv;
    }


    rv = cint_field_alternate_marking_inter_or_egress_node_iPMF2_D_entry_add(unit,&entry_handle);
    if (rv != BCM_E_NONE)
    {
       printf("Error (%d), in cint_field_alternate_marking_inter_or_egress_node_iPMF2_D_entry_add \n", rv);
       return rv;
    }

    if (is_inter_pe)
    {
        /* In iPMF2, Load the Flow label(32 bits) on UDH1_Data and Flow label indication(32bits) on UDH2_Data. */
        rv = cint_field_alternate_marking_inter_pe_ipmf2_udh(unit);
        if (rv != BCM_E_NONE)
        {
            printf("Error (%d), in cint_field_alternate_marking_inter_pe_ipmf2_udh \n", rv);
            return rv;
        }
        printf("Intermediate PE Node iPMF2 Done! \n");

        /* In ePMF, Identify the packet carries the FLoFLI and apply AceContextValue action. */
        rv = cint_field_alternate_marking_inter_pe_epmf_udh(unit);
        if (rv != BCM_E_NONE)
        {
            printf("Error (%d), in cint_field_alternate_marking_inter_pe_epmf_udh \n", rv);
            return rv;
        }
        printf("Intermediate PE Node ePMF Done! \n");
    }

    return 0;

}


/**
 * Termination/intermediate node alternate marking.
 * Cint should be called on top of standard MPLS termination
 * cints.
 *  1. Set up snoop for D flag, along with tail edit profile on
 *  snooped packet
 *  2. Install CRPS
 *  3. Call field APIs for snooping and assigning counters to
 *  packets.
 *
 * @param unit
 * @param in_port
 * @param out_port
 * @param flow_id  Flow-ID on AM label.
 * @parm  is_inter_pe 1 is intermediate PE node.
 *
 * @return int
 */
int mpls_alternate_marking_termination(int unit, int in_port, int out_port, int flow_id, int is_inter_pe) {
    int cpu_port;
    bcm_port_config_t port_config;
    bcm_gport_t snoop_trap_gport_id;
    bcm_mirror_header_info_t mirror_header_info;
    int snoop_code;

    BCM_IF_ERROR_RETURN(bcm_port_config_get(unit, &port_config));
    BCM_PBMP_ITER(port_config.cpu, cpu_port)
    {
        mirror_dest.gport = cpu_port;
        break;
    }

    if (ifit_enable)
    {
        BCM_IF_ERROR_RETURN(bcm_switch_control_set(unit,bcmSwitchMplsFlowInstructionIndicatorSpecialLabel, 12));
    }


    /* Set up snoop + snoop header*/
    BCM_IF_ERROR_RETURN(cint_field_ip_snoop_set(unit,cpu_port,1,0,0,snoop_trap_gport_id,&snoop_code));
    /* Snoop raw is composed {strength(3b), snoop-code(b9) }. Use strength 7.*/
    g_cint_field_am_i_o_e_ipmf2_D_ent.SnoopRaw = ( 7<<9 | BCM_GPORT_TRAP_GET_ID(snoop_trap_gport_id));

        /** Now set tail-edit-profile on the system headers */
    bcm_mirror_header_info_t_init(&mirror_header_info);
    mirror_header_info.pp.tail_edit_profile = CINT_INSTRU_IPT_TAIL_EDIT_PROFILE;
    mirror_header_info.tm.flow_id_ext.valid= 1;
    BCM_IF_ERROR_RETURN(bcm_mirror_header_info_set(unit,BCM_MIRROR_DEST_IS_SNOOP ,snoop_code,&mirror_header_info));


    /*
     * Add CRPS configuration
     */
    crps_oam_config_enable_eviction = 1; /* Eviction must be enabled on the transit node*/
    BCM_IF_ERROR_RETURN(mpls_deep_stack_alternate_marking_crps(unit, in_port));
    crps_oam_config_enable_eviction = 0; /* Set it back to default value*/
    /*
     * Field
     */
    g_cint_field_am_i_o_e_ipmf2_flow_ent.flow_label = flow_id;
    BCM_IF_ERROR_RETURN(mpls_alternate_marking_intermediate_field(unit, is_inter_pe));


    /*
    * Timestamp information when D bit is set is gotten through meta data.
    * Switch id parameter is the node ID field.
    */
    BCM_IF_ERROR_RETURN(cint_instru_ipt_main(unit,0xab,0));

    return 0;
}

/*
 * Intermediate pe node
 *   Added an ip host entry and mpls tunnel.
 *   Packet hit the ip host entry will enter the mpls tunnel
 */
int mpls_am_inter_pe_route_into_tunnel (int unit, int in_port, int out_port)
{
    int rv;
    bcm_ip_t dip_routing_into_tunnel = 0x7FFFFF04; /* 127.255.255.4 */
    int vrf = 100;
    dnx_utils_l3_fec_s fec_structure;
    int common_tunnel_fec_id;

    int common_mpls_tunnel_id;
    int common_mpls_tunnel_label[2] = {800,8001};
    int label_index;
    bcm_mpls_egress_label_t label_array[2];
    int tunnel_ttl[2] = {20,40};

    for (label_index = 0; label_index < 2; label_index++)
    {
        bcm_mpls_egress_label_t_init(&label_array[label_index]);
        label_array[label_index].label = common_mpls_tunnel_label[label_index];
        label_array[label_index].flags = BCM_MPLS_EGRESS_LABEL_TTL_DECREMENT;
        label_array[label_index].egress_qos_model.egress_qos = bcmQosEgressModelUniform;
        label_array[label_index].egress_qos_model.egress_ttl = bcmQosEgressModelPipeMyNameSpace;
        label_array[label_index].action = BCM_MPLS_EGRESS_ACTION_PUSH;
        label_array[label_index].ttl = tunnel_ttl[label_index];
        /*Only outermost entry carry arp*/
        if (label_index == 1) {
            label_array[label_index].l3_intf_id = cint_termination_mpls_basic_info.arp_id;
        }
    }

    /** Create the mpls tunnel with one call.*/
    rv = sand_mpls_tunnel_initiator_create(unit, 0, 2, label_array);
    if (rv != BCM_E_NONE)
    {
        printf("Error, in bcm_mpls_tunnel_initiator_create\n");
        return rv;
    }
    common_mpls_tunnel_id = label_array[0].tunnel_id;

    /** Create fec.*/
    dnx_utils_l3_fec_s_init(unit, 0x0, &fec_structure);
    BCM_GPORT_LOCAL_SET(fec_structure.destination, out_port);
    fec_structure.tunnel_gport = common_mpls_tunnel_id;
    rv = dnx_utils_l3_fec_create(unit, &fec_structure);
    if (rv != BCM_E_NONE)
    {
        printf("Error, create egress object FEC only\n");
        return rv;
    }
    common_tunnel_fec_id = fec_structure.l3eg_fec_id;

    /** Create ipv4 host.*/
    rv = add_host_ipv4(unit, dip_routing_into_tunnel, vrf, common_tunnel_fec_id, 0, 0);
    if (rv != BCM_E_NONE)
    {
        printf("Error (%d), in add_host_ipv4\n", rv);
        return rv;
    }

    return rv;
}

/*
 * 
 This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 
 Copyright 2007-2022 Broadcom Inc. All rights reserved. File: cint_mpls_operations_without_eedb.c
 */

/*
 * 
 * Configuration:
 * 
 * Test Scenario - start
 * cint;                                                                  
 * cint_reset();                                                          
 * exit; 
  cint ../../../../src/examples/sand/utility/cint_sand_utils_global.c  
  cint ../../../../src/examples/sand/utility/cint_sand_utils_l3.c   
  cint ../../../../src/examples/dnx/utility/cint_dnx_utility_mpls.c                                       
  cint ../../../../src/examples/dnx/mpls/cint_mpls_operations_without_eedb.c                                       
  cint                                                                   
  int unit = 0; 
  int rv = 0; 
  int port1 = 200; 
  int port2 = 201;
  int mode = 0;
  rv = mpls_operations_without_eedb_main(unit,port1,port2, mode);
  print rv; 
 * Test Scenario - end
 * 
 * This cint uses cint_dnx_utility_mpls.c to configure MPLS setup with required modifications.
 *
 * Main function for basic mpls php from fhei: Do php from fhei, ilm results in fhei and fec pointer for arp. 
 * Fhei is then resolved into ees and then to etps, as with the common php (php from eedb)
 *
 *  Scenarios configured in this cint:
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~
 *  1) Basic MPLS forwarding (SWAP)
 *  ~~~~~~~~~~~~~~~~~~~~~~~~
 *  Covered modes:
 *  1.1) MPLS_NO_EEDB_FEC_MODE_SWAP - 
 *      ILM entry points to cascaded FEC entries where one entry holds the swap information (action and label) and the following FEC entry holds the arp.
 *  1.2) MPLS_NO_EEDB_ILM_MODE_SWAP - 
 *      ILM entry holds the swap information (action and label)
 *
 *  Traffic:
 * 
 *  Send the following traffic:
 *
 *  ##############################################################################################
 *  Sending packet from port == port1 :   ----------->
 *   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *   |    +-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-
 *   |    |      DA         | SA              ||   MPLS   ||  SIP          ||  DIP          ||
 *   |    |00:0C:00:02:00:01|00:0C:00:02:00:00||Label:7777||160.161.161.162||160.161.161.163||
 *   |    +-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-
 *   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 *  Receiving packet on port == port2:   <------------
 *   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *   |    +-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-
 *   |    |      DA         | SA              ||   MPLS   ||  SIP          ||  DIP          ||
 *   |    |00:11:00:00:01:12|00:00:00:00:CD:1D||Label:3333||160.161.161.162||160.161.161.163||
 *   |    +-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-
 *   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ###############################################################################################
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~
 *   2) Basic MPLS Termination (PHP)
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Covered modes:
 *  2.1) MPLS_NO_EEDB_FEC_MODE_PHP -
 *      ILM entry points to cascaded FEC entries where one entry holds the php information (action) and the following FEC entry holds the arp.
 *  2.2) MPLS_NO_EEDB_ILM_MODE_PHP - 
 *      Do php from ILM entry.
 *
 *  Traffic:
 * 
 *  Send the following traffic:
 *
 *  ##############################################################################################
 *  Sending packet from port == port1 :   ----------->
 *   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *   |    +-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-
 *   |    |      DA         | SA              ||   MPLS   ||  SIP          ||  DIP          ||
 *   |    |00:0C:00:02:00:01|00:0C:00:02:00:00||Label:3377||160.161.161.163||160.161.161.162||
 *   |    +-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-
 *   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 *  Receiving packet on port == port1:   <------------
 *   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *   |    +-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-
 *   |    |      DA         | SA              ||  SIP          ||  DIP          ||  
 *   |    |00:11:00:00:01:12|00:00:00:00:CD:1D||160.161.161.163||160.161.161.162||
 *   |    +-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-
 *   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ###############################################################################################
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~
 *  3) Basic MPLS encapsulation (PUSH)
 *  ~~~~~~~~~~~~~~~~~~~~~~~~
 *  Covered modes:
 *  MPLS_NO_EEDB_FEC_MODE_PUSH - 
 *      IP entry points to cascaded FEC entries where one entry holds the swap information (action and label) and the following FEC entry holds the arp.
 *
 *  Traffic:
 * 
 *  Send the following traffic:
 *
 *  ##############################################################################################
 *  Sending packet from port == port1 :   ----------->
 *   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *   |    +-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-
 *   |    |      DA         | SA              ||   MPLS   ||  SIP          ||  DIP          ||
 *   |    |00:0C:00:02:00:01|00:0C:00:02:00:00||Label:7777||160.161.161.162||160.161.161.163||
 *   |    +-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-
 *   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 *  Receiving packet on port == port2:   <------------
 *   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *   |    +-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-
 *   |    |      DA         | SA              ||   MPLS   ||  SIP          ||  DIP          ||
 *   |    |00:11:00:00:01:12|00:00:00:00:CD:1D||Label:3333||160.161.161.162||160.161.161.163||
 *   |    +-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-
 *   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ###############################################################################################
 */

/** all MODE explanation can be found in the cint description above */
int MPLS_NO_EEDB_FEC_MODE_PHP = 0;
int MPLS_NO_EEDB_FEC_MODE_SWAP = 1;
int MPLS_NO_EEDB_ILM_MODE_PHP = 2;
int MPLS_NO_EEDB_ILM_MODE_SWAP = 3;
int MPLS_NO_EEDB_FEC_MODE_PUSH = 4;
int MPLS_NO_EEDB_FEC_MODE_PHP_AND_PUSH = 5;

/* override global configuration */
MPLS_UTIL_MAX_NOF_ENTITIES = 2;


int
mpls_operations_without_eedb_main(
    int unit,
    int port1,
    int port2,
    int mode)
{

    init_default_mpls_params(unit, port1, port2);

    /* disable tunnels configured by default */
    mpls_tunnel_switch_create_s_init(mpls_util_entity[0].mpls_switch_tunnel, MPLS_UTIL_MAX_NOF_TUNNELS);
    mpls_tunnel_switch_create_s_init(mpls_util_entity[1].mpls_switch_tunnel, MPLS_UTIL_MAX_NOF_TUNNELS);
    mpls_tunnel_initiator_create_s_init(mpls_util_entity[0].mpls_encap_tunnel, MPLS_UTIL_MAX_NOF_TUNNELS);
    mpls_tunnel_initiator_create_s_init(mpls_util_entity[1].mpls_encap_tunnel, MPLS_UTIL_MAX_NOF_TUNNELS);

    /* configure requested setup */
    switch (mode)
    {
        case MPLS_NO_EEDB_FEC_MODE_PHP:
            mpls_util_entity[0].fecs[0].flags |= BCM_L3_CASCADED;
            mpls_util_entity[0].fecs[0].tunnel_gport = &mpls_util_entity[1].arps[0].arp;

            mpls_util_entity[0].fecs[1].fec_id = 0;
            mpls_util_entity[0].fecs[1].fec = &mpls_util_entity[0].fecs[0].fec_id;
            /** PHP fec format is determined by egress object mpls action */
            mpls_util_entity[0].fecs[1].mpls_action = BCM_MPLS_EGRESS_ACTION_PHP;

            mpls_util_entity[0].mpls_switch_tunnel[0].action = BCM_MPLS_SWITCH_ACTION_NOP;
            mpls_util_entity[0].mpls_switch_tunnel[0].egress_if = &mpls_util_entity[0].fecs[1].fec_id;
            mpls_util_entity[0].mpls_switch_tunnel[0].flags = BCM_MPLS_SWITCH_TTL_DECREMENT;
            mpls_util_entity[0].mpls_switch_tunnel[0].label = 3377;
            break;
        case MPLS_NO_EEDB_FEC_MODE_SWAP:
            mpls_util_entity[0].fecs[0].flags |= BCM_L3_CASCADED;
            mpls_util_entity[0].fecs[0].tunnel_gport = &mpls_util_entity[1].arps[0].arp;

            mpls_util_entity[0].fecs[1].fec_id = 0;
            mpls_util_entity[0].fecs[1].fec = &mpls_util_entity[0].fecs[0].fec_id;
            mpls_util_entity[0].fecs[1].mpls_action = (!dnx_utils_is_jr2_system_header_mode(unit))?
                                               BCM_MPLS_EGRESS_ACTION_SWAP:BCM_MPLS_EGRESS_ACTION_SWAP_OR_PUSH;
            mpls_util_entity[0].fecs[1].mpls_label = 3333;

            mpls_util_entity[0].mpls_switch_tunnel[0].action = BCM_MPLS_SWITCH_ACTION_NOP;
            mpls_util_entity[0].mpls_switch_tunnel[0].egress_if = &mpls_util_entity[0].fecs[1].fec_id;
            mpls_util_entity[0].mpls_switch_tunnel[0].flags = BCM_MPLS_SWITCH_TTL_DECREMENT;
            mpls_util_entity[0].mpls_switch_tunnel[0].label = 7777;
            break;
        case MPLS_NO_EEDB_ILM_MODE_PHP:
            mpls_util_entity[0].fecs[0].tunnel_gport = &mpls_util_entity[1].arps[0].arp;

            mpls_util_entity[0].mpls_switch_tunnel[0].flags = BCM_MPLS_SWITCH_TTL_DECREMENT;
            mpls_util_entity[0].mpls_switch_tunnel[0].label = 3377;
            mpls_util_entity[0].mpls_switch_tunnel[0].port = &mpls_util_entity[0].fecs[0].fec_id;
            mpls_util_entity[0].mpls_switch_tunnel[0].action = BCM_MPLS_SWITCH_ACTION_PHP;
            break;
        case MPLS_NO_EEDB_ILM_MODE_SWAP:
            mpls_util_entity[0].fecs[0].tunnel_gport = &mpls_util_entity[1].arps[0].arp;

            mpls_util_entity[0].mpls_switch_tunnel[0].flags = BCM_MPLS_SWITCH_TTL_DECREMENT;
            mpls_util_entity[0].mpls_switch_tunnel[0].label = 7777;
            mpls_util_entity[0].mpls_switch_tunnel[0].port = &mpls_util_entity[0].fecs[0].fec_id;
            mpls_util_entity[0].mpls_switch_tunnel[0].action = BCM_MPLS_SWITCH_ACTION_SWAP;
            mpls_util_entity[0].mpls_switch_tunnel[0].egress_label = 3333;
            break;
        case MPLS_NO_EEDB_FEC_MODE_PUSH:
            /*
            * Configure MPLS term -> MPLS FHEI encap -> IP
            */
            /* termination entry */
            mpls_util_entity[0].mpls_switch_tunnel[0].action = BCM_MPLS_SWITCH_ACTION_POP;
            mpls_util_entity[0].mpls_switch_tunnel[0].label = 7777;
            mpls_util_entity[0].mpls_switch_tunnel[0].vrf = 100;

            mpls_util_entity[0].fecs[0].flags |= BCM_L3_CASCADED;
            mpls_util_entity[0].fecs[0].tunnel_gport = &mpls_util_entity[1].arps[0].arp;

            mpls_util_entity[0].fecs[1].fec_id = 0;
            mpls_util_entity[0].fecs[1].fec = &mpls_util_entity[0].fecs[0].fec_id;
            mpls_util_entity[0].fecs[1].mpls_action = (!dnx_utils_is_jr2_system_header_mode(unit))?
                                                     BCM_MPLS_EGRESS_ACTION_PUSH:BCM_MPLS_EGRESS_ACTION_SWAP_OR_PUSH;
            mpls_util_entity[0].fecs[1].mpls_label = 3333;

            mpls_util_entity[0].hosts_ipvx[0].ipv4 = 0xA0A1A1A3; /* 160.161.161.163 */
            mpls_util_entity[0].hosts_ipvx[0].fec_id = &mpls_util_entity[0].fecs[1].fec_id;
            mpls_util_entity[0].hosts_ipvx[0].vrf = 100;

            /*
            * Configure MPLS term -> MPLS FHEI encap -> MPLS encap -> IP
            */
            /* termination entry */
            mpls_util_entity[1].mpls_switch_tunnel[0].action = BCM_MPLS_SWITCH_ACTION_POP;
            mpls_util_entity[1].mpls_switch_tunnel[0].label = 8888;
            mpls_util_entity[1].mpls_switch_tunnel[0].vrf = 100;

            mpls_util_fec_s_init(mpls_util_entity[1].fecs, MPLS_UTIL_MAX_NOF_FECS);
            mpls_util_entity[1].fecs[0].fec_id = 0;
            mpls_util_entity[1].fecs[0].flags |= BCM_L3_3RD_HIERARCHY;
            mpls_util_entity[1].fecs[0].port = &mpls_util_entity[0].ports[0].port;

            mpls_util_entity[1].fecs[1].fec_id = 0;
            mpls_util_entity[1].fecs[1].flags |= BCM_L3_2ND_HIERARCHY;
            mpls_util_entity[1].fecs[1].fec = &mpls_util_entity[1].fecs[0].fec_id;
            mpls_util_entity[1].fecs[1].tunnel_gport = &mpls_util_entity[1].mpls_encap_tunnel[0].tunnel_id;

            mpls_util_entity[1].fecs[2].fec_id = 0;
            mpls_util_entity[1].fecs[2].fec = &mpls_util_entity[1].fecs[1].fec_id;
            mpls_util_entity[1].fecs[2].mpls_action = (!dnx_utils_is_jr2_system_header_mode(unit))?
                                                     BCM_MPLS_EGRESS_ACTION_PUSH:BCM_MPLS_EGRESS_ACTION_SWAP_OR_PUSH;
            mpls_util_entity[1].fecs[2].mpls_label = 3333;

            mpls_util_entity[1].hosts_ipvx[0].ipv4 = 0xA0A1A1A2; /* 160.161.161.162 */
            mpls_util_entity[1].hosts_ipvx[0].fec_id = &mpls_util_entity[1].fecs[2].fec_id;
            mpls_util_entity[1].hosts_ipvx[0].vrf = 100;

            /* encapsulation entry */    
            mpls_util_entity[1].mpls_encap_tunnel[0].label[0] = 3334;
            mpls_util_entity[1].mpls_encap_tunnel[0].num_labels = 1;
            mpls_util_entity[1].mpls_encap_tunnel[0].flags |= BCM_MPLS_EGRESS_LABEL_TTL_DECREMENT | BCM_MPLS_EGRESS_LABEL_ENTROPY_ENABLE | BCM_MPLS_EGRESS_LABEL_ENTROPY_INDICATION_ENABLE;
            mpls_util_entity[1].mpls_encap_tunnel[0].l3_intf_id = &mpls_util_entity[0].arps[0].arp;
            mpls_util_entity[1].mpls_encap_tunnel[0].encap_access = bcmEncapAccessTunnel3;


            break;
        case MPLS_NO_EEDB_FEC_MODE_PHP_AND_PUSH:
            /*Egress MPLS tunnel */
            mpls_util_entity[0].mpls_encap_tunnel[0].label[0] = 3333;
            mpls_util_entity[0].mpls_encap_tunnel[0].num_labels = 1;
            mpls_util_entity[0].mpls_encap_tunnel[0].flags |= BCM_MPLS_EGRESS_LABEL_TTL_DECREMENT;
            mpls_util_entity[0].mpls_encap_tunnel[0].egress_qos_model.egress_ttl = bcmQosEgressModelPipeMyNameSpace;
            mpls_util_entity[0].mpls_encap_tunnel[0].l3_intf_id = &mpls_util_entity[1].arps[0].arp;

            mpls_util_entity[0].mpls_switch_tunnel[0].flags = BCM_MPLS_SWITCH_TTL_DECREMENT;
            mpls_util_entity[0].mpls_switch_tunnel[0].label = 3377;
            mpls_util_entity[0].mpls_switch_tunnel[0].port = &mpls_util_entity[0].fecs[0].fec_id;
            mpls_util_entity[0].mpls_switch_tunnel[0].action = BCM_MPLS_SWITCH_ACTION_PHP;

            break;
        default:
            printf("Error(%d), invalid test mode(%d) - valid range is %d-%d \n", rv, mode, MPLS_NO_EEDB_FEC_MODE_PHP,
                   MPLS_NO_EEDB_FEC_MODE_PUSH);
            return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN_MSG(mpls_util_main(unit, port1, port2), "");

    return BCM_E_NONE;
}


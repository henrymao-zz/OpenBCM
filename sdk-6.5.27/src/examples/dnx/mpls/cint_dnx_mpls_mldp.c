/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MPLS mLDP~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * File: cint_dnx_mpls_mldp.c
 * Purpose: Demo mpls mLDP(BUD LSR PE node)
 *
 *  LSR BUD node could do 2 times replication:
 *   1. Replication based on the mLDP label;
 *   2. Replication based on the payload inside the mLDP label(MPLS label or IP);
 * This cint demo the traffic test for BUD node.
 *  1. IPv4omLDPoMPLSoEth packet received, the 1st Label terminated;
 *  2. In 1st Pass,packet is replicated based on the mLDP label, 2 copies generated(to core side);
 *  3. One copy sent to recycle port;
 *  4. In 2nd PASS, mLDP label is terminated, and packet is replicated based on the IP,
 *     1 copy generated(to access side);

 * Example:
 * Test Scenario 
 *
 * Test Scenario - start
  cint ../../../../src/examples/sand/utility/cint_sand_utils_global.c
  cint ../../../../src/examples/dnx/field/cint_field_utils.c
  cint ../../../../src/examples/sand/utility/cint_sand_utils_global.c
  cint ../../../../src/examples/sand/utility/cint_dnx_utils_l3.c
  cint ../../../../src/examples/sand/utility/cint_sand_utils_mpls.c
  cint ../../../../src/examples/dnx/utility/cint_dnx_util_rch.c
  cint ../../../../src/examples/sand/cint_ip_route_basic.c
  cint ../../../../src/examples/sand/cint_ipmc_route_basic.c
  cint ../../../../src/examples/dnx/mpls/cint_dnx_mpls_mldp.c
  cint
  mpls_mldp_example(0,200,201,202);
  exit;
 *
 *  MLDP traffic test. 
  tx 1 psrc=200 data=0x000000000011000000000000810070648847003e8040007d01404500004c00000000403d84650a0a0a02e0020202000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f303132333435363738393a3b00000000
 *
 *  Received packets on unit 0 should be: 
 *  Source port: 200, Destination port: 201 
 *  Data: 0x000000000022000000000011810000c88847008ae13f4500004c00000000403d84650a0a0a02e0020202000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f303132333435363738393a3b00000000 
 *  Source port: 200, Destination port: 202 
 *  Data: 0x000000000033000000000011810000c908004500004c000000003f3d85650a0a0a02e0020202000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f303132333435363738393a3b00000000 
 *  Source port: 200, Destination port: 201 
 *  Data: 0x000000000022000000000011810000c888470045713f4500004c00000000403d84650a0a0a02e0020202000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f303132333435363738393a3b00000000 
 * Test Scenario - end
*/


 struct cint_mpls_mldp_info_s 
{
    int in_rif;                             /* access RIF */
    int core_side_out_rif;                  /* out RIF */
    int access_side_out_rif;                  /* out RIF */

    int vrf;                                /*  VRF */
    bcm_mac_t my_mac;                       /* mac for Incoming L3 intf */
    bcm_mac_t core_side_next_hop_mac;       /* next hop mac for outgoing station */
    bcm_mac_t access_side_next_hop_mac;     /* next hop mac for access side */

    bcm_ip_t dip;                           /* dip */
    bcm_ip_t sip;                           /* sip */


    int mpls_tunnel_term_label;         /*Incoming tunnel label*/
    int mldp_label;                         /*Incoming mldp label*/

    int mpls_tunnel_outgoing_label[2];         /*Incoming tunnel label*/

    int mldp_mc_id;                         /*MC ID for 1st pass*/   
    int ipmc_id;                            /*MC ID for 2nd pass*/

    int recycle_port_id;                    /*recycle port ID*/

    bcm_qos_ingress_model_t ingress_qos_model;   /*ingress qos model*/

    int core_side_arp_encap_id;             /*Next hop intf ID*/ 
    int access_side_arp_encap_id;           /*Next hop intf ID*/ 
    int mpls_tunnel_id[2];                  /*mpls tunnel id*/ 
    int recycle_entry_encap_id;             /*recycle header entr ID*/
    int mldp_tunnel_intf;                   /*tunnel intf for MLDP entry*/
};
 
 
 cint_mpls_mldp_info_s cint_mpls_mldp_info=
{
    /*
    * In-RIF,
    */
    100,
    /*
    * core-side-Out-RIF,
    */
    200,

    /*
    * access-side-Out-RIF,
    */
    201,

    /*
    * vrf,
    */
    1,
    /*
    * my_mac | next_hop_mac 
    */
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x11},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x22},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x33},

    /*
    * dip
    */
    0xE0020202 /** 224.2.2.2 */ ,


    /*
    * sip
    */
    0x0A0A0A02 /** 10.10.10.2 */ ,


    /*
    * mpls_tunnel_term_label
    */
    1000, 

    /*
    * mldp_label
    */
    2000, 

    /*
    * mpls_tunnel_outgoing_label
    */
    {1111,2222},    

    /*
    * mldp_mc_id
    */
    6000,

    /*
    * ipmc_id
    */
    6001,

    /*
    * recycle_port_id
    */
    50,

    /*
     * ingress qos model
     */
    {bcmQosIngressModelUniform, bcmQosIngressModelUniform, bcmQosIngressModelUniform, bcmQosIngressEcnModelInvalid}
};

/**
 * port init
 * INPUT:
 *   in_port    - traffic incoming port 
*/
 int
 mpls_mldp_ingress_port_configuration(
    int unit,
    int in_port,
    int in_rif)
{

    BCM_IF_ERROR_RETURN_MSG(in_port_intf_set(unit, in_port, in_rif), "");
    return BCM_E_NONE;

}

/**
 * port egress init
 * INPUt:
 * core_side_port   -out port to core side
 * access_side_port   -out port to access side
*/
 int
 mpls_mldp_egress_port_configuration(
    int unit,
    int core_side_port,
    int access_side_port)
{
    char error_msg[200]={0,};

    /*
     * 1. Set Out-Port default properties, in case of ARP+AC no need
     */
    snprintf(error_msg, sizeof(error_msg), "intf_out out_port %d", core_side_port);
    BCM_IF_ERROR_RETURN_MSG(out_port_set(unit, core_side_port), error_msg);

    /*
     * 2. Set Out-Port default properties, in case of ARP+AC no need
     */
    snprintf(error_msg, sizeof(error_msg), "intf_out out_port %d", access_side_port);
    BCM_IF_ERROR_RETURN_MSG(out_port_set(unit, access_side_port), error_msg);


    return BCM_E_NONE;

}

 
/**
 * L3 intf init
 * INPUT:
 *   unit    - traffic incoming unit 
*/
 int
 mpls_mldp_l3_intf_configuration(
    int unit)
{
    int rv;
    bcm_l3_intf_t l3_intf;
    dnx_utils_l3_eth_rif_s eth_rif_structure;

    bcm_l3_intf_t_init(&l3_intf);
    l3_intf.l3a_intf_id = cint_mpls_mldp_info.in_rif;
    rv = bcm_l3_intf_get(unit,&l3_intf);
    if (rv != BCM_E_NONE) {
        dnx_utils_l3_eth_rif_s_common_init(unit, 0, &eth_rif_structure, cint_mpls_mldp_info.in_rif, 0, 0, cint_mpls_mldp_info.my_mac, cint_mpls_mldp_info.vrf);
        BCM_IF_ERROR_RETURN_MSG(dnx_utils_l3_eth_rif_create(unit, &eth_rif_structure), "core_side_in_rif");
    }

    bcm_l3_intf_t_init(&l3_intf);
    l3_intf.l3a_intf_id = cint_mpls_mldp_info.core_side_out_rif;
    rv = bcm_l3_intf_get(unit,&l3_intf);
    if (rv != BCM_E_NONE) {
        dnx_utils_l3_eth_rif_s_common_init(unit, 0, &eth_rif_structure, cint_mpls_mldp_info.core_side_out_rif, 0, 0, cint_mpls_mldp_info.my_mac, cint_mpls_mldp_info.vrf);
        BCM_IF_ERROR_RETURN_MSG(dnx_utils_l3_eth_rif_create(unit, &eth_rif_structure), "core_side_out_rif");

    }    


    bcm_l3_intf_t_init(&l3_intf);
    l3_intf.l3a_intf_id = cint_mpls_mldp_info.access_side_out_rif;
    rv = bcm_l3_intf_get(unit,&l3_intf);
    if (rv != BCM_E_NONE) {
        dnx_utils_l3_eth_rif_s_common_init(unit, 0, &eth_rif_structure, cint_mpls_mldp_info.access_side_out_rif, 0, 0, cint_mpls_mldp_info.my_mac, cint_mpls_mldp_info.vrf);
        BCM_IF_ERROR_RETURN_MSG(dnx_utils_l3_eth_rif_create(unit, &eth_rif_structure), "access_side_out_rif");

    }    


    return BCM_E_NONE;
}


/**
 * mpls tunnel termination entry adding
 * INPUT:
 *   unit    - traffic incoming unit 
*/
 int
mpls_mldp_tunnel_termination_configuration(
    int unit)
{
    bcm_mpls_tunnel_switch_t entry;
    int i;

    /*
     * step 1: Create MPLS tunnel to be terminated 
     */
    bcm_mpls_tunnel_switch_t_init(&entry);

    entry.action = BCM_MPLS_SWITCH_ACTION_POP;
    entry.label = cint_mpls_mldp_info.mpls_tunnel_term_label;
    entry.vpn = cint_mpls_mldp_info.vrf;

    BCM_IF_ERROR_RETURN_MSG(bcm_mpls_tunnel_switch_create(unit, &entry), "");

    /*
     * step 2: Create mpls label for mLDP label 
     */
    bcm_mpls_tunnel_switch_t_init(&entry);

    entry.action = BCM_MPLS_SWITCH_ACTION_POP;
    entry.label = cint_mpls_mldp_info.mldp_label;
    entry.flags2 = BCM_MPLS_SWITCH2_TERM_BUD; 
    entry.vpn = cint_mpls_mldp_info.vrf;

    BCM_IF_ERROR_RETURN_MSG(bcm_mpls_tunnel_switch_create(unit, &entry), "");

    BCM_GPORT_TUNNEL_TO_L3_ITF_LIF(cint_mpls_mldp_info.mldp_tunnel_intf,entry.tunnel_id);
    return BCM_E_NONE;
}

/**
 * update ingress mpls tunnel qos model
 * INPUT:
 *   unit    - traffic incoming unit 
*/
 int
mpls_mldp_tunnel_termination_qos_update(
    int unit)
{
    bcm_mpls_tunnel_switch_t entry;
    int i;

    /*
     * step 1: update MPLS tunnel 
     */
    bcm_mpls_tunnel_switch_t_init(&entry);

    entry.label = cint_mpls_mldp_info.mpls_tunnel_term_label;
    entry.action = BCM_MPLS_SWITCH_ACTION_POP;
    BCM_IF_ERROR_RETURN_MSG(bcm_mpls_tunnel_switch_get(unit, &entry), "");
    sal_memcpy(&(entry.ingress_qos_model), &(cint_mpls_mldp_info.ingress_qos_model), sizeof(entry.ingress_qos_model));
    entry.flags |= (BCM_MPLS_SWITCH_REPLACE |BCM_MPLS_SWITCH_WITH_ID);
    BCM_IF_ERROR_RETURN_MSG(bcm_mpls_tunnel_switch_create(unit, &entry), "");

    /*
     * step 2: update mldp 
     */
    bcm_mpls_tunnel_switch_t_init(&entry);

    entry.label = cint_mpls_mldp_info.mldp_label;
    entry.action = BCM_MPLS_SWITCH_ACTION_POP;
    entry.flags2 = BCM_MPLS_SWITCH2_TERM_BUD;
    BCM_IF_ERROR_RETURN_MSG(bcm_mpls_tunnel_switch_get(unit, &entry), "");
    sal_memcpy(&(entry.ingress_qos_model), &(cint_mpls_mldp_info.ingress_qos_model), sizeof(entry.ingress_qos_model));
    entry.flags |= (BCM_MPLS_SWITCH_REPLACE |BCM_MPLS_SWITCH_WITH_ID);
    BCM_IF_ERROR_RETURN_MSG(bcm_mpls_tunnel_switch_create(unit, &entry), "");

    return BCM_E_NONE;
}


int
mpls_mldp_tunnel_encapsulation_configuration(
    int unit)
{
    int i = 0;
    bcm_mpls_egress_label_t label_array[4];

    for (i = 0;i<2; i++) 
    {
        bcm_mpls_egress_label_t_init(&label_array[0]);
        
        label_array[0].label = cint_mpls_mldp_info.mpls_tunnel_outgoing_label[i];
        label_array[0].flags = BCM_MPLS_EGRESS_LABEL_TTL_DECREMENT;  
        label_array[0].action = BCM_MPLS_EGRESS_ACTION_PUSH;
        label_array[0].l3_intf_id = cint_mpls_mldp_info.core_side_arp_encap_id;
        
        /** Create the mpls tunnel with one call.*/
        BCM_IF_ERROR_RETURN_MSG(sand_mpls_tunnel_initiator_create(unit, 0, 1, label_array), "");
        
        cint_mpls_mldp_info.mpls_tunnel_id[i] = label_array[0].tunnel_id;

    }
    return BCM_E_NONE;
}


/**
 * ARP adding
 * INPUT:
 *   unit    - traffic outgoing unit 
*/
 int
 mpls_mldp_arp_configuration(
    int unit)
{

    dnx_utils_l3_arp_s arp_structure;

    /*
     * Configure access side ARP entry      */
    dnx_utils_l3_arp_s_common_init(unit, 0, &arp_structure, cint_mpls_mldp_info.access_side_arp_encap_id, 0, BCM_L3_FLAGS2_VLAN_TRANSLATION , cint_mpls_mldp_info.access_side_next_hop_mac, cint_mpls_mldp_info.access_side_out_rif);
    BCM_IF_ERROR_RETURN_MSG(dnx_utils_l3_arp_create(unit, &arp_structure), "create AC egress object ARP only");
    cint_mpls_mldp_info.access_side_arp_encap_id = arp_structure.l3eg_arp_id;

    /*
     * Configure core side ARP entry      */
    dnx_utils_l3_arp_s_common_init(unit, 0, &arp_structure, cint_mpls_mldp_info.core_side_arp_encap_id, 0, BCM_L3_FLAGS2_VLAN_TRANSLATION , cint_mpls_mldp_info.core_side_next_hop_mac, cint_mpls_mldp_info.core_side_out_rif);
    BCM_IF_ERROR_RETURN_MSG(dnx_utils_l3_arp_create(unit, &arp_structure), "create AC egress object ARP only");

    cint_mpls_mldp_info.core_side_arp_encap_id = arp_structure.l3eg_arp_id;


    return BCM_E_NONE;
}

 /*
  * Create a Recycle Entry.
  * unit - relevant unit
  * recycle_entry_encap_id - returned encap id.
  */
 int 
 mpls_mldp_create_recycle_entry(
     int unit)
 {
     bcm_switch_control_key_t key;
     bcm_switch_control_info_t get_info;
     uint32 ibch1_supported = *dnxc_data_get(unit, "headers", "system_headers", "system_headers_ibch1_supported", NULL);

     BCM_IF_ERROR_RETURN_MSG(create_recycle_entry_with_defaults(unit, &cint_mpls_mldp_info.recycle_entry_encap_id), "");

    /** configure port as recycle port, Part of context selection at
     *  2nd pass VTT1.
      */
     /** Index 1 means direction IN */
     key.index = 1;
     key.type = bcmSwitchPortHeaderType;
     /** Retrieve default out port configuration */
     BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_indexed_port_get(unit, cint_mpls_mldp_info.recycle_port_id, key, &get_info), "");
     /** header_type IBCH1_MODE, allow to run various applications on the same recycle port */
     if (!ibch1_supported)
     {
         BCM_IF_ERROR_RETURN_MSG(bcm_port_control_set(unit, cint_mpls_mldp_info.recycle_port_id, bcmPortControlOverlayRecycle,
                ((get_info.value == BCM_SWITCH_PORT_HEADER_TYPE_IBCH1_MODE) ? 0 : 1)), "");
     }
     return BCM_E_NONE;
 }



 int
 mpls_mldp_multicast_group_configuration(
    int unit,
    int core_out_port,
    int access_out_port)
{
    int pp_db_replication_list[2];

    bcm_multicast_replication_t replications[3];
    int rep_count = 3;
    uint32 mc_flags=0;

    /*
     * 1st PASS MC, for mLDP label
     */
     
    /* 1st copy: to core-side tunnel1*/
    bcm_multicast_replication_t_init(&replications[0]);
    replications[0].encap1 = BCM_L3_ITF_VAL_GET(cint_mpls_mldp_info.mpls_tunnel_id[0]);
    replications[0].port = core_out_port;

    /* 2nd copy: to core side tunnel2*/
    bcm_multicast_replication_t_init(&replications[1]);
    replications[1].encap1 = BCM_L3_ITF_VAL_GET(cint_mpls_mldp_info.mpls_tunnel_id[1]);
    replications[1].port = core_out_port;

    /* 3rd copy: to recycle port*/
    bcm_multicast_replication_t_init(&replications[2]);
    replications[2].encap1 = BCM_L3_ITF_VAL_GET(cint_mpls_mldp_info.recycle_entry_encap_id);
    replications[2].port = cint_mpls_mldp_info.recycle_port_id;

    if (*dnxc_data_get(unit, "multicast", "params", "mcdb_formats_v2", NULL)) {
        mc_flags = BCM_MULTICAST_INGRESS_GROUP | BCM_MULTICAST_ELEMENT_STATIC;
    } else {
        mc_flags = BCM_MULTICAST_INGRESS_GROUP;
    }
    BCM_IF_ERROR_RETURN_MSG(bcm_multicast_create(unit, BCM_MULTICAST_WITH_ID|mc_flags, &cint_mpls_mldp_info.mldp_mc_id), "");

    /*MCDB setting*/
    BCM_IF_ERROR_RETURN_MSG(bcm_multicast_set(unit, cint_mpls_mldp_info.mldp_mc_id, mc_flags, 3, replications), "");

    /*
     * 2nd PASS MC, for IP payload
     */

    /* 1st copy: to access-side intr*/
    bcm_multicast_replication_t_init(&replications[0]);
    replications[0].encap1 = BCM_L3_ITF_VAL_GET(cint_mpls_mldp_info.access_side_arp_encap_id);
    replications[0].port = access_out_port;

    BCM_IF_ERROR_RETURN_MSG(bcm_multicast_create(unit, BCM_MULTICAST_WITH_ID|mc_flags, &cint_mpls_mldp_info.ipmc_id), "");

    /*MCDB setting*/
    BCM_IF_ERROR_RETURN_MSG(bcm_multicast_set(unit, cint_mpls_mldp_info.ipmc_id, mc_flags, 1, replications), "");


    return BCM_E_NONE;
}


/**
 * forward entry adding(ILM, IPv4 Route)
 * INPUT:
 *   unit    - traffic incoming unit 
*/
 int
 mpls_mldp_forward_entry_configuration(
    int unit)
{
    int l3_mc_id;
    bcm_mpls_tunnel_switch_t entry;

    bcm_mpls_tunnel_switch_t_init(&entry);

    /*
     * 1. Add P2MP entry
     */

    /** mLDP label */
    entry.label = cint_mpls_mldp_info.mldp_label;
    entry.mc_group = cint_mpls_mldp_info.mldp_mc_id;
    entry.flags = BCM_MPLS_SWITCH_TTL_DECREMENT | BCM_MPLS_SWITCH_P2MP;
    entry.action = BCM_MPLS_SWITCH_ACTION_NOP;
    BCM_IF_ERROR_RETURN_MSG(bcm_mpls_tunnel_switch_create(unit, &entry), "");


    /*
     * 2. Add IPv4 IPMC entry
     */
    BCM_IF_ERROR_RETURN_MSG(add_ipv4_ipmc(unit, cint_mpls_mldp_info.dip, 0xFFFFFFFF, cint_mpls_mldp_info.sip, 0xFFFFFFFF,
        cint_mpls_mldp_info.mldp_tunnel_intf, cint_mpls_mldp_info.vrf, cint_mpls_mldp_info.ipmc_id, 0,0), "to LEM table");
    

    return BCM_E_NONE;
}



/**
 * Main entrance for IPv4 UC on multi-device
 * INPUT:
 *   in_sys_port	- traffic incoming port 
 *   out_sys_port - traffic outgoing port
*/
 int
 mpls_mldp_example(
    int unit,
    int core_in_port,
    int core_out_port,
    int access_out_port)
{



    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_ingress_port_configuration(unit,core_in_port,cint_mpls_mldp_info.in_rif), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_egress_port_configuration(unit,core_out_port,access_out_port), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_l3_intf_configuration(unit), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_tunnel_termination_configuration(unit), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_arp_configuration(unit), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_tunnel_encapsulation_configuration(unit), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_create_recycle_entry(unit), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_multicast_group_configuration(unit,core_out_port,access_out_port), "");
    
    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_forward_entry_configuration(unit), "");
    
    return BCM_E_NONE;
}



/**
 * Example for MLDP and 2nd pass is PWE
*/
 int
 mpls_mldp_2nd_pass_pwe(
    int unit,
    int core_in_port,
    int core_out_port,
    int access_out_port)
{
    char error_msg[200]={0,};
    int flags;
    int mcid;

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_ingress_port_configuration(unit,core_in_port,cint_mpls_mldp_info.in_rif), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_egress_port_configuration(unit,core_out_port,access_out_port), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_l3_intf_configuration(unit), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_tunnel_termination_configuration(unit), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_arp_configuration(unit), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_tunnel_encapsulation_configuration(unit), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_create_recycle_entry(unit), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_multicast_group_configuration(unit,core_out_port,access_out_port), "");
    
    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_forward_entry_configuration(unit), "");

    /*
     * create VSI for 2nd pass
     */
    snprintf(error_msg, sizeof(error_msg), "Failed to create VLAN %d", cint_vpls_pwe_tagged_mode_basic_info.service_vsi);
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_create(unit, cint_vpls_pwe_tagged_mode_basic_info.service_vsi), error_msg);

    /*
     * configure PWE tunnel termination for 2nd pass
     */
    BCM_IF_ERROR_RETURN_MSG(vpls_pwe_tagged_mode_basic_mpls_port_add_termination(unit,
                                                              &(cint_vpls_pwe_tagged_mode_basic_info.mpls_port_id_ing),
                                                              cint_vpls_pwe_tagged_mode_basic_info.service_pwe_label,
                                                              &(cint_vpls_pwe_tagged_mode_basic_info.pwe_encap_id),
                                                              cint_vpls_pwe_tagged_mode_basic_info.mpls_fec_id,
                                                              cint_vpls_pwe_tagged_mode_basic_info.service_vsi), "");

    /*
     * Add ingress indexed native AC
     */
    BCM_IF_ERROR_RETURN_MSG(vpls_pwe_tagged_mode_add_network_native_ac(unit, cint_vpls_pwe_tagged_mode_basic_info.service_vsi,
                                                    cint_vpls_pwe_tagged_mode_basic_info.service_mac_1,
                                                    &
                                                    (cint_vpls_pwe_tagged_mode_basic_info.ingress_native_ac_vlan_port_id),
                                                    &
                                                    (cint_vpls_pwe_tagged_mode_basic_info.access_egress_vlan_port_id),
                                                    cint_vpls_pwe_tagged_mode_basic_info.mpls_port_id_ing,
                                                    cint_vpls_pwe_tagged_mode_basic_info.ingress_canonical_outer_vlan,
                                                    cint_vpls_pwe_tagged_mode_basic_info.ingress_canonical_inner_vlan,
                                                    cint_vpls_pwe_tagged_mode_basic_info.access_port, 0, FALSE, FALSE, 0), "");

    /*
     * Configure IVE for core to access traffic: delete two service tags 
     */
    snprintf(error_msg, sizeof(error_msg), "port=0x%08x", cint_vpls_pwe_tagged_mode_basic_info.ingress_native_ac_vlan_port_id);
    BCM_IF_ERROR_RETURN_MSG(vlan_translate_ive_eve_translation_set(unit,
                                                cint_vpls_pwe_tagged_mode_basic_info.ingress_native_ac_vlan_port_id,
                                                0,
                                                0,
                                                bcmVlanActionDelete,
                                                bcmVlanActionDelete,
                                                0,
                                                0,
                                                cint_vpls_pwe_tagged_mode_basic_info.ingress_vlan_edit_profile,
                                                cint_vpls_pwe_tagged_mode_basic_info.tag_format_double_tagged, 1), error_msg);

    /*
     * Create multicast groups and add access port as member
     */
    if (*dnxc_data_get(unit, "multicast", "params", "mcdb_formats_v2", NULL)) {
        flags = BCM_MULTICAST_INGRESS_GROUP | BCM_MULTICAST_ELEMENT_STATIC;
    } else {
        flags = BCM_MULTICAST_INGRESS_GROUP;
    }
    mcid = cint_vpls_pwe_tagged_mode_basic_info.service_vsi;

    BCM_IF_ERROR_RETURN_MSG(bcm_multicast_create(unit, (BCM_MULTICAST_WITH_ID | flags), &mcid), "");

    bcm_multicast_replication_t rep_array;
    bcm_multicast_replication_t_init(&rep_array);
    rep_array.port =  access_out_port;
    snprintf(error_msg, sizeof(error_msg), "in Port= %d", access_out_port);
    BCM_IF_ERROR_RETURN_MSG(bcm_multicast_add(unit, mcid, flags, 1, &rep_array), error_msg);

    return BCM_E_NONE;
}

/**
 * Example for MLDP and 2nd pass is EVPN IML
*/
 int
 mpls_mldp_2nd_pass_evpn(
    int unit,
    int core_in_port,
    int core_out_port,
    int access_out_port)
{
    char error_msg[200]={0,};
    int flags;
    int mcid;

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_ingress_port_configuration(unit,core_in_port,cint_mpls_mldp_info.in_rif), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_egress_port_configuration(unit,core_out_port,access_out_port), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_l3_intf_configuration(unit), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_tunnel_termination_configuration(unit), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_arp_configuration(unit), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_tunnel_encapsulation_configuration(unit), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_create_recycle_entry(unit), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_multicast_group_configuration(unit,core_out_port,access_out_port), "");

    BCM_IF_ERROR_RETURN_MSG(mpls_mldp_forward_entry_configuration(unit), "");

    /*
     * create VSI for 2nd pass
     */
    snprintf(error_msg, sizeof(error_msg), "Failed to create VLAN %d", cint_evpn_info.vsi);
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_create(unit, cint_evpn_info.vsi), error_msg);

    /*
     * configure EVPN tunnels termination for 2nd pass
     */
    BCM_IF_ERROR_RETURN_MSG(evpn_profiles_set(unit), "");
    BCM_IF_ERROR_RETURN_MSG(evpn_service_ingress_config(unit, cint_evpn_info.vsi), "");

    /* Add AC for inner ETH IVE */
    bcm_vlan_port_t vlan_port;
    bcm_vlan_port_t_init(&vlan_port);
    vlan_port.flags = BCM_VLAN_PORT_NATIVE | BCM_VLAN_PORT_CREATE_INGRESS_ONLY;
    vlan_port.flags |= BCM_VLAN_PORT_VLAN_TRANSLATION;
    vlan_port.vsi = cint_evpn_info.vsi;
    vlan_port.criteria = BCM_VLAN_PORT_MATCH_NONE;
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_create(unit, &vlan_port), "");

    /* Add Match for inner ETH*/
    /*
     * currently EVPN IML doesn't support PWE tagged mode
     * It always works in LIF scope currently.
     * will update test once it's supported
     */
    bcm_port_match_info_t match_info;
    bcm_port_match_info_t_init(&match_info);
    match_info.flags = BCM_PORT_MATCH_INGRESS_ONLY | BCM_PORT_MATCH_NATIVE;
    match_info.match = BCM_PORT_MATCH_PORT;
    match_info.port = evpn_global_info.pe1_pe2_iml_tunnel_switch_esi.tunnel_id;
    snprintf(error_msg, sizeof(error_msg), "for match_port 0x%08X", match_info.port);
    BCM_IF_ERROR_RETURN_MSG(bcm_port_match_add(unit, vlan_port.vlan_port_id, &match_info), error_msg);

    if (!(*dnxc_data_get(unit, "mpls", "general", "mpls_term_till_bos", NULL))) {
        bcm_port_match_info_t_init(&match_info);
        match_info.flags = BCM_PORT_MATCH_INGRESS_ONLY | BCM_PORT_MATCH_NATIVE;
        match_info.match = BCM_PORT_MATCH_PORT;
        match_info.port = evpn_global_info.pe1_pe2_iml_tunnel_switch_no_esi.tunnel_id;
        snprintf(error_msg, sizeof(error_msg), "for match_port 0x%08X", match_info.port);
        BCM_IF_ERROR_RETURN_MSG(bcm_port_match_add(unit, vlan_port.vlan_port_id, &match_info), error_msg);
    }

    /*
     * Configure IVE for core to access traffic: delete two service tags 
     */
    snprintf(error_msg, sizeof(error_msg), "for match_port 0x%08X", vlan_port.vlan_port_id);
    BCM_IF_ERROR_RETURN_MSG(vlan_translate_ive_eve_translation_set(unit,
                                                vlan_port.vlan_port_id,
                                                0,
                                                0,
                                                bcmVlanActionDelete,
                                                bcmVlanActionDelete,
                                                0,
                                                0,
                                                2,
                                                16, 1), error_msg);

    /*
     * Create multicast groups and add access port as member
     */
    if (*dnxc_data_get(unit, "multicast", "params", "mcdb_formats_v2", NULL)) {
        flags = BCM_MULTICAST_INGRESS_GROUP | BCM_MULTICAST_ELEMENT_STATIC;
    } else {
        flags = BCM_MULTICAST_INGRESS_GROUP;
    }
    mcid = cint_evpn_info.vsi;

    BCM_IF_ERROR_RETURN_MSG(bcm_multicast_create(unit, (BCM_MULTICAST_WITH_ID | flags), &mcid), "");

    bcm_multicast_replication_t rep_array;
    bcm_multicast_replication_t_init(&rep_array);
    rep_array.port =  access_out_port;
    snprintf(error_msg, sizeof(error_msg), "in Port= %d", access_out_port);
    BCM_IF_ERROR_RETURN_MSG(bcm_multicast_add(unit, mcid, flags, 1, &rep_array), error_msg);

    return BCM_E_NONE;
}

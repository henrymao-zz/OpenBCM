
/*
 * Examples of Jericho2-only tunnel termination
 *
 * Description:
 * -The Cint is full Demo of traversing an IPv4oETH packet through an SRv6 u-SDID Tunnel/Overlay.
 * -The Demo includes the following scenarios:
 * -------------------------------------
 * 1.IPv4oETH packet traverses through an SRv6 Ingress Node to add SRv6 and IPv6 Encapsulation,
 *   and output IPv4oSRv6_1oIPv6oETH packet (SRv6_1 means with SRH header with x1 128b SID, which includes x2 u-SIDs)
 *   -IPv6 DIP includes
 *       - a prefix of 32bits: 0xAABBCCDD
 *       - and x2 u-SIDs of 16bits: 0xEE00 and 0xEE01
 *       - rest of DIP is all zeros
 *
 * 2.Packet from scenario (1) IPv4oSRv6_1oIPv6oETH through an SRv6 Endpoint Node that performs:
 *    -Lookup on VRF and next u-SIDs in IPv6 DIP to get Destination and Outlif
 *    -Edits IPv6 DIP so that
 *        - the prefix is reserved
 *        - next u-SID is shifted left by 16b
 *        - lsb DIP bits are set to 0
 *
 * 3.Packet from scenario (2) IPv4oSRv6_1oIPv6oETH through an SRv6 Egress USP Node that performs:
 *    on 1st Pass - Termination of SRv6 and IPv6 Header
 *    on 2nd Pass - IPv4 Forwarding
 *    and outputs an IPv4oETH packet
 *
 *********************************
 *       Device  Demo Run        *
 *********************************
 *
 * Add/modify following SOC Properties to "config-jr2.bcm":
 * -----------------------------
 * tm_port_header_type_in_0=ETH
 * tm_port_header_type_in_200=ETH
 * tm_port_header_type_in_201=ETH
 * tm_port_header_type_in_202=ETH
 * tm_port_header_type_in_203=ETH
 * tm_port_header_type_in_40=RCH_0 (or IBCH1_MODE, if supported)
 * tm_port_header_type_out_40=ETH
 * ucode_port_40=RCY.0:core_1.40
 * appl_param_srv6_reduce_enable=0
 * appl_param_srv6_psp_enable=0
 *
 * Shell Commands:
 * ---------------
 * Test Scenario - start
  config add tm_port_header_type_in_0=ETH
  config add tm_port_header_type_in_200=ETH
  config add tm_port_header_type_in_201=ETH
  config add tm_port_header_type_in_202=ETH
  config add tm_port_header_type_in_203=ETH
  config add tm_port_header_type_in_40=RCH_0
 * or IBCH1_MODE, if supported
  config add tm_port_header_type_out_40=ETH
  config add ucode_port_40=RCY.0:core_1.40
  config add appl_param_srv6_reduce_enable=0
  config add appl_param_srv6_psp_enable=0
  tr 141
 * cint;
 * cint_reset();
 * exit;
  cint ../../../../src/examples/sand/utility/cint_sand_utils_global.c
  cint ../../../../src/examples/dnx/field/cint_field_utils.c
  cint ../../../../src/examples/dnx/l3/cint_dnx_ip_route_basic.c
  cint ../../../../src/examples/sand/utility/cint_sand_utils_vlan_translate.c
  cint ../../../../src/examples/dnx/tunnel/cint_dnx_srv6_usid_full_flow_example.c
  cint ../../../../src/examples/dnx/utility/cint_dnx_util_srv6.c
 *
  cint;
  int rv;
  rv = srv6_basic_usid_example(0,200,202,202,202,201,40,203,srh_present,is_default);
  print rv;
  exit;
 *
 * Note if using SRH, set above srh_present = 1, else srh_present = 0
 * Note if is_default = 1 then USID with cascaded lookup is performed
 *
 **********************************************************************************************************
 * Following is example of full flow using Egress USP and encapsulation Normal mode, of expected packets: *
 **********************************************************************************************************
 * NOTE - Send Only Packets Without PTCH for SRv6 ! *
 ****************************************************
 *
 * Srv6 Ingress Node:
 *
  PacKeT TX raw port=200 DATA=000c000200000000070001000800450000350000000040003a46c08001017fffff02000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * Received packets on unit 0 should be:
 *
 * data = 00000000cd1d00123456789a8100006586dd
 *        60038ea3004d2b80 123456789abceeffffeecba987654321 aabbccddee00ee010000000000000000
 *        0402000000000000 aabbccddee00ee010000000000000000
 *        45000035000000003f003b46c08001017fffff02000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 *
 * Srv6 End-Point-1 Node:
 *
  PacKeT TX raw port=202 DATA=00000000cd1d00123456789a8100006586dd60000000004d2b80123456789abceeffffeecba987654321aabbccddee00ee0100000000000000000402000000000000aabbccddee00ee01000000000000000045000035000000003f003b46c08001017fffff02000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * Received packets on unit 0 should be:
 *
 * data = 00000001cd1d00213456789a8100006486dd
 *        60000000004d2b7f 123456789abceeffffeecba987654321 aabbccddee0100000000000000000000
 *        0402000000000000 aabbccddee00ee010000000000000000
 *        45000035000000003f003b46c08001017fffff02000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 *
 * data = 00000001CD1D00213456789A8100006686DD
 *        60006DCB00952B7F 123456789ABCEEFFFFEECBA987654321 AAAABBBBCCCCDDDDEEEEFFFF11112222
 *        0406000102000000 ABCDDBCA123443211010989845679ABC AAAABBBBCCCCDDDDEEEEFFFF11112222 11112222333344445555666677778888
 *        45000035000000007F00FB45C08001017FFFFF02000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F20
 *
 * Srv6 Egress Node:
 *
  PacKeT TX raw port=201 DATA=00000002cd1d00223456789a8100006486dd60000000004d2b7e123456789abceeffffeecba987654321aabbccddee01000000000000000000000402000000000000aabbccddee00ee01000000000000000045000035000000003f003b46c08001017fffff02000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * Received packets on unit 0 should be:
 *
 * data = 00000003cd1d00303456789a810000680800
 *        45000035000000007d00fd45c08001017fffff02000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * Test Scenario - end
 *
 */


/** \brief List of SRv6 used instances */
enum srv6_instances_e
{
    INGRESS,
    END_POINT_1,
    EGRESS,
    RCH,
    NO_DEFAULT
};

 int NOF_INSTANCES = RCH+1;

/** \brief List of SRv6 used FEC ids */
enum srv6_fec_id_e
{
    INGRESS_IPV6_TUNNEL_FEC_ID,
    INGRESS_IPV6_TUNNEL_FEC_ID_2ND_HIER,
    END_POINT_1_FEC_ID,
    EGRESS_FEC_ID,
    EGRESS_FEC_ID_2ND_HIER,
    T_INSERT_FEC_ID
};

int NOF_FEC_ID = T_INSERT_FEC_ID+1;

/** \brief List of SRv6 used VIDs */
enum srv6_vid_e
{
    END_POINT_1_VID,
    EGRESS_VID,
    EGRESS_OUT_VID
};

int NOF_VID = EGRESS_OUT_VID+1;

/** \brief List of SRv6 used Global LIFs */
enum srv6_global_lifs_e
{
    INGRESS_IPV6_TUNNEL_GLOBAL_LIF
};

int NOF_GLOBAL_LIFS=INGRESS_IPV6_TUNNEL_GLOBAL_LIF+1;

/** \brief List of SRv6 used Terminated DIPs */
enum srv6_terminated_dips_e
{
    END_POINT_1_DIP,
    END_POINT_2_DIP,
    END_POINT_3_DIP,
    END_POINT_4_DIP,
    END_POINT_5_DIP,
    END_POINT_CLASSIC,
    EGRESS_DIP,
    END_POINT_TO_T_INSERT,
    END_POINT_TO_T_INSERT_FWD,
    END_POINT_1_DIP_48B_PREFIX,
    END_POINT_2_DIP_48B_PREFIX,
    END_POINT_3_DIP_48B_PREFIX,
    END_POINT_4_DIP_48B_PREFIX,
    END_POINT_1_DIP_48B_PREFIX_NO_DEF,
    END_POINT_2_DIP_48B_PREFIX_NO_DEF,
    END_POINT_3_DIP_48B_PREFIX_NO_DEF
};

int NOF_DIPS = END_POINT_3_DIP_48B_PREFIX_NO_DEF+1;
int NOF_DIPS_END_TO_INSERT = 2;
int NOF_DIPS_IN_TRANSPORT = 3;
int srv6_tunnel_term_id = 0;

struct cint_srv6_tunnel_info_s
{
    int eth_rif_intf_in[NOF_INSTANCES];                 /* in RIF */
    int eth_rif_intf_out[NOF_INSTANCES-1];              /* out RIF */
    bcm_mac_t intf_in_mac_address[NOF_INSTANCES];       /* mac for in RIF */
    bcm_mac_t intf_out_mac_address[NOF_INSTANCES];      /* mac for in RIF */
    bcm_mac_t arp_next_hop_mac[NOF_INSTANCES];          /* mac for next hop */
    bcm_mac_t dmac_fwd;                                 /* mac for forwarding */
    bcm_vlan_t vlan_fwd;
    int vrf_in[NOF_INSTANCES+1];                        /* VRF, resolved as Tunnel-InLif property*/
    int tunnel_arp_id[NOF_INSTANCES-1];                 /* Id for ARP entry */
    int t_insert_global_id;
    int tunnel_fec_id[NOF_FEC_ID];                      /* FEC id */
    int tunnel_global_lif[NOF_GLOBAL_LIFS];             /* Global LIFs */
    int tunnel_vid[NOF_VID];                            /* VID */
    bcm_ip_t route_ipv4_dip;                            /* IPv4 Route DIP as next layer above SRv6 */
    bcm_ip6_t route_ipv6_dip;                            /* IPv6 Route DIP as next layer above SRv6 */
    bcm_ip6_t tunnel_ip6_dip[NOF_DIPS];                 /* IPv6 Terminated DIPs */
    bcm_ip6_t sid_encap_in_tunnel[NOF_DIPS_IN_TRANSPORT];    /* SID in Tunnel (transport) */
    bcm_ip6_t tunnel_ip6_sip;                           /* IPv6 Tunnel SIP */
    int srh_next_protocol_ipv4;                         /* IPv4 as next protocol above SRv6, per IANA RFC */
    int srh_next_protocol_ipv6;                         /* IPv6 as next protocol above SRv6, per IANA RFC */
    int is_l2_fwd;                                      /* enable l2 fwd after Srv6 */
    int l2_termination_vsi;                             /* when the fwd is ETH, the fwd domain is VSI*/
};


cint_srv6_tunnel_info_s cint_srv6_tunnel_info =
{
        /*
         * eth_rif_intf_in
         */
         {15, 16, 18, 19},
        /*
         * eth_rif_intf_out --> we don't include eth-rif-out for Ingress node, we use instead VSI with MAC and VID of End-Point-1
         */
         {0, 110, 103},
        /*
         * intf_in_mac_address
         */
         {{ 0x00, 0x0c, 0x00, 0x02, 0x00, 0x00 },  { 0x00, 0x00, 0x00, 0x00, 0xcd, 0x1d },
          { 0x00, 0x00, 0x00, 0x02, 0xcd, 0x1d },  { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0x11 }},
        /*
         * intf_out_mac_address
         */
         {{ 0x00, 0x12, 0x34, 0x56, 0x78, 0x9a }, { 0x00, 0x21, 0x34, 0x56, 0x78, 0x9a },
          { 0x00, 0x30, 0x34, 0x56, 0x78, 0x9a }, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }},
        /*
         * arp_next_hop_mac
         */
         {{ 0x00, 0x00, 0x00, 0x00, 0xcd, 0x1d }, { 0x00, 0x00, 0x00, 0x02, 0xcd, 0x1d },
          { 0x00, 0x00, 0x00, 0x03, 0xcd, 0x1d }, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
        /*
         * dmac_fwd | vlan_fwd
         */
          { 0x00, 0x00, 0x00, 0xca, 0xcd, 0x1d }, 17,
        /*
         * In VRF
         */
         {1, 11, 14, 14, 5},
         /*
          * tunnel_arp_id
          */
         {0x4384, 0x4385, 0x4387},
         /*
          * t_insert_global_id
          */
         0x6890,
         /*
         * tunnel_fec_id
         */
         {0xA711, 0xD711, 0xA002, 0xA003, 0xA004},
         /*
          * tunnel_global_lifs - IPv6 Tunnel, 1st SID respectively
          */
         {0x2230, 0x4231},
         /*
          * tunnel_vid - VID of End-Point-1 is used to create VSI for Ingress node to have MAC and VID instead of in ETH-RIF-OUT which is not present
          */
         {101, 100, 104},
        /*
         * route_ipv4_dip when IPv4 is above SRv6
         */
        0x7fffff02 /* 127.255.255.02 */,
        /*
         * route_ipv6_dip when IPv6 is above SRv6
         */
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x34, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x13 },
        /*
         * terminated_ip6_dips
         */
        {{ 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0x00, 0xEE, 0x01, 0xEE, 0x02, 0xEE, 0x03, 0xEE, 0x04, 0xEE, 0x05 },
         { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0x01, 0xEE, 0x02, 0xEE, 0x03, 0xEE, 0x04, 0xEE, 0x05, 0x00, 0x00 },
         { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0x02, 0xEE, 0x03, 0xEE, 0x04, 0xEE, 0x05, 0x00, 0x00, 0x00, 0x00 },
         { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0x03, 0xEE, 0x04, 0xEE, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
         { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0x04, 0xEE, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
         { 0xAA, 0xAA, 0xBB, 0xBB, 0xCC, 0xCC, 0xDD, 0xDD, 0xEE, 0xEE, 0xFF, 0xFF, 0x11, 0x11, 0x22, 0x22 },
         { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
         { 0xDD, 0xCC, 0xBB, 0xAA, 0xEE, 0x05, 0xEE, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
         { 0xDD, 0xCC, 0xBB, 0xAA, 0xEE, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
         { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0x00, 0xEE, 0x02, 0xEE, 0x03, 0xEE, 0x04, 0xEE, 0x05, 0x00, 0x00 },
         { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0x01, 0xEE, 0x03, 0xEE, 0x04, 0xEE, 0x05, 0x00, 0x00, 0x00, 0x00 },
         { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0x02, 0xEE, 0x04, 0xEE, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
         { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0x03, 0xEE, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
         { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0x00, 0xEE, 0x03, 0xEE, 0x04, 0xEE, 0x05, 0x00, 0x00, 0x00, 0x00 },
         { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0x01, 0xEE, 0x04, 0xEE, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
         { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0x02, 0xEE, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }},
         /*
          * sid_encap_in_tunnel
          */
         {{ 0x12, 0x12, 0x34, 0x34, 0x56, 0x56, 0x78, 0x78, 0x9a, 0x9a, 0xbc, 0xbc, 0x00, 0x00, 0x00, 0x01 },
          { 0x01, 0x01, 0x23, 0x23, 0x45, 0x45, 0x67, 0x67, 0x89, 0x89, 0xab, 0xab, 0x00, 0x00, 0x00, 0x02 },
          { 0x1c, 0x1c, 0x2b, 0x2b, 0x3a, 0x3a, 0x49, 0x49, 0x58, 0x58, 0x67, 0x67, 0x00, 0x00, 0x00, 0x03 }},
         /*
          * tunnel_ip6_sip
          */
        { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xee, 0xff, 0xff, 0xee, 0xcb, 0xa9, 0x87, 0x65, 0x43, 0x21 },
       /*
        * next protocol above SRv6 which is IPv4
        */
        4,
        /*
         * next protocol above SRv6 which is IPv6 | is_l2_fwd | l2_termination_vsi
         */
         41, 0, 15

};

/*
 * Set In-Port default ETH-RIF:
 * - in_port: Incoming port ID
 * - in_port: Incoming VLAN ID
 * - eth_rif: ETH-RIF
 */
int
in_port_vid_intf_set(
    int unit,
    int in_port,
    int in_vid,
    int eth_rif)
{
    bcm_vlan_port_t vlan_port;
    char *proc_name;

    proc_name = "in_port_vid_intf_set";
    bcm_vlan_port_t_init(&vlan_port);
    vlan_port.port = in_port;
    vlan_port.match_vlan = in_vid;
    vlan_port.criteria = BCM_VLAN_PORT_MATCH_PORT_CVLAN;
    vlan_port.vsi = eth_rif;
    vlan_port.flags = BCM_VLAN_PORT_CREATE_INGRESS_ONLY;

    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_create(unit, vlan_port), "");

    printf("%s(): port = %d, in_lif = 0x%08X\n", proc_name, vlan_port.port, vlan_port.vlan_port_id);
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_gport_add(unit, in_vid, in_port, 0), "");

    return BCM_E_NONE;
}

/*
 * Configures MyDip of an IPv6 address in an SRv6 tunnel
 */
int
srv6_tunnel_termination(
                    int unit,
                    int end_point_id,
                    int is_egress_tunnel,
                    int srh_present,
                    int vrf,
                    bcm_tunnel_type_t tunnel_type, /** for uSID end-point bcmTunnelTypeIpAnyIn6 */
                    int is_default)
{

    bcm_ip6_t ip6_mask = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    bcm_ip6_t ip6_usid_prefix_mask = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    bcm_ip6_t ip6_mask_func = {0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    bcm_ip6_t ip6_usid_48b_prefix_mask = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    bcm_ip6_t ip6_mask_48b_prefix_func = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00};

    bcm_ip6_t ip6_dip  = {0};
    bcm_ip6_t ip6_sip  = {0};

    print(cint_srv6_tunnel_info);

    sal_memcpy(ip6_sip, cint_srv6_tunnel_info.tunnel_ip6_sip, 16);
    sal_memcpy(ip6_dip, cint_srv6_tunnel_info.tunnel_ip6_dip[end_point_id], 16);

    bcm_tunnel_terminator_t tunnel_term_set;
    l3_ingress_intf ingress_rif;
    int flags = (is_default) ? BCM_TUNNEL_TERM_CASCADED_MISS_DISABLE_TERM : 0;
    int is_prefix_48b_enabled = *dnxc_data_get(unit, "srv6", "general", "srv6_usid_prefix_48b_enable", NULL);

    bcm_tunnel_terminator_t_init(&tunnel_term_set);
    tunnel_term_set.type = tunnel_type;
    if (tunnel_type != bcmTunnelTypeEthIn6)
    {
        tunnel_term_set.flags = BCM_TUNNEL_TERM_MICRO_SEGMENT_ID | flags;
    }
    sal_memcpy(tunnel_term_set.dip6, ip6_dip, 16);
    sal_memcpy(tunnel_term_set.sip6, ip6_sip, 16);
    sal_memcpy(tunnel_term_set.dip6_mask, (is_prefix_48b_enabled ? ip6_usid_48b_prefix_mask : ip6_usid_prefix_mask), 16);
    sal_memcpy(tunnel_term_set.sip6_mask, ip6_mask, 16);
    tunnel_term_set.vrf = vrf;

    if (tunnel_type == bcmTunnelTypeEthIn6)
    {
        tunnel_term_set.vlan = cint_srv6_tunnel_info.l2_termination_vsi;
    }
    /* Following is for configuring for the IPv6 LIF, to increase the strength of its TTL
     * so that terminated IPv6 header's TTL would get to sysh, from which the IPv6 TTL decrease
     * would decrease from
     */
    tunnel_term_set.ingress_qos_model.ingress_ttl = bcmQosIngressModelPipe;

    /** only in Egress node + when SRH is present, Extended Termination is performed */
    if(is_egress_tunnel && srh_present)
    {
        tunnel_term_set.flags = tunnel_term_set.flags | BCM_TUNNEL_TERM_EXTENDED_TERMINATION;
        /* If it's ESR USP, shortpipe and uniform are supported
         * Uniform: take QoS info from SRv6 tunnel
         * Shortpipe: take QoS info from fwd layer
         */
        tunnel_term_set.ingress_qos_model.ingress_ttl = bcmQosIngressModelUniform;
        tunnel_term_set.ingress_qos_model.ingress_phb = bcmQosIngressModelUniform;
        tunnel_term_set.ingress_qos_model.ingress_remark = bcmQosIngressModelUniform;
    }

    BCM_IF_ERROR_RETURN_MSG(bcm_tunnel_terminator_create(unit, &tunnel_term_set), "");
    srv6_tunnel_term_id = tunnel_term_set.tunnel_id;

    if (is_default)
    {

       /*
        * Create function lif lookup
        */
       bcm_tunnel_terminator_t_init(&tunnel_term_set);
       tunnel_term_set.type = bcmTunnelTypeCascadedFunct;
       tunnel_term_set.flags = is_egress_tunnel ? BCM_TUNNEL_TERM_EXTENDED_TERMINATION : 0;
       tunnel_term_set.default_tunnel_id = srv6_tunnel_term_id;
       sal_memcpy(tunnel_term_set.dip6, ip6_dip, 16);
       sal_memcpy(tunnel_term_set.sip6, ip6_sip, 16);
       sal_memcpy(tunnel_term_set.dip6_mask, (is_prefix_48b_enabled ? ip6_mask_48b_prefix_func : ip6_mask_func), 16);
       sal_memcpy(tunnel_term_set.sip6_mask, ip6_mask, 16);
       tunnel_term_set.vrf = vrf;
       tunnel_term_set.ingress_qos_model.ingress_ttl = bcmQosIngressModelPipe;
       tunnel_term_set.ingress_qos_model.ingress_phb = bcmQosIngressModelPipe;
       tunnel_term_set.ingress_qos_model.ingress_remark = bcmQosIngressModelPipe;

       BCM_IF_ERROR_RETURN_MSG(bcm_tunnel_terminator_create(unit, &tunnel_term_set), "");
       srv6_tunnel_term_id = tunnel_term_set.tunnel_id;
       vrf = cint_srv6_tunnel_info.vrf_in[NO_DEFAULT];
    }
    if (!cint_srv6_tunnel_info.is_l2_fwd)
    {
        l3_ingress_intf_init(&ingress_rif);
        ingress_rif.vrf = vrf;
        BCM_GPORT_TUNNEL_TO_L3_ITF_LIF(ingress_rif.intf_id, tunnel_term_set.tunnel_id);
        BCM_IF_ERROR_RETURN_MSG(intf_ingress_rif_set(unit, &ingress_rif), "");
    }

    return BCM_E_NONE;
}

/*
 * Create a Recycle Entry.
 * unit - relevant unit
 * eth_type - ether type, per what's layer is passed for RCH ETH dummy packet encapsulation
 * recycle_entry_encap_id - returned encap id.
 */
int
create_recycle_entry(
    int unit,
    uint32 eth_type,
    int *recycle_entry_encap_id)
{

    bcm_l2_egress_t recycle_entry;
    bcm_l2_egress_t_init(&recycle_entry);
    recycle_entry.ethertype = eth_type;
    recycle_entry.flags = BCM_L2_EGRESS_RECYCLE_HEADER;

    BCM_IF_ERROR_RETURN_MSG(bcm_l2_egress_create(unit, &recycle_entry), "");
    *recycle_entry_encap_id = recycle_entry.encap_id;

    return BCM_E_NONE;
}

/*
 * Returns type field in ETH from SRH next type
 */
int
srh_nxt_hdr_to_eth_type(
    int srh_next_header_idx)
{
    int map_array[256] = { 0 };

    /** IPV4 */
    map_array[4] = 0x0800;

    /** IPV6 */
    map_array[41] = 0x86DD;

    return map_array[srh_next_header_idx];
}

int
dnx_srv6_update_fecs_id(
        int unit)
{
    int first_fec;
    BCM_IF_ERROR_RETURN_MSG(get_first_fec_in_range_which_not_in_ecmp_range(unit, 0, 0, &first_fec), "");
    cint_srv6_tunnel_info.tunnel_fec_id[INGRESS_IPV6_TUNNEL_FEC_ID] = first_fec++;
    cint_srv6_tunnel_info.tunnel_fec_id[EGRESS_FEC_ID] = first_fec++;
    cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID] = first_fec++;
    cint_srv6_tunnel_info.tunnel_fec_id[T_INSERT_FEC_ID] = first_fec++;

    /*Update 2nd hierarchy fec ids*/
    BCM_IF_ERROR_RETURN_MSG(get_first_fec_in_range_which_not_in_ecmp_range(unit, 1, 0, &first_fec), "");
    cint_srv6_tunnel_info.tunnel_fec_id[INGRESS_IPV6_TUNNEL_FEC_ID_2ND_HIER] = first_fec++;
    cint_srv6_tunnel_info.tunnel_fec_id[EGRESS_FEC_ID_2ND_HIER] = first_fec++;
    return BCM_E_NONE;
}

int
srv6_basic_usid_example(
                    int unit,
                    int in_port,             /** Incoming port of SRV6 Ingress Tunnel */
                    int out_port,            /** Outgoing port of SRV6 Ingress Tunnel */
                    int in_port_end1,        /** Incoming port of SRV6 End Point 1 */
                    int out_port_end1,       /** Outgoing port of SRV6 End Point 1 */
                    int in_port_egress,      /** Incoming port of SRV6 Egress */
                    int rch_port,            /** Rycling port number for 1st Pass USP in Egress */
                    int out_port_egress,     /** Outgoing port of SRV6 Egress */
                    int srh_present,         /** If set, SRH header is present in uSID packet */
                    int is_default)          /** If set, USIDwith cascaded lookup is performed */
{

    char error_msg[200]={0,};
    char *proc_name = "srv6_basic_usid_example";
    bcm_tunnel_type_t tunnel_type_endpoint;
    bcm_tunnel_type_t egress_tunnel_type;
    bcm_tunnel_type_t ingress_tunnel_type;
    int is_prefix_48b_enabled = *dnxc_data_get(unit, "srv6", "general", "srv6_usid_prefix_48b_enable", NULL);

    if (cint_srv6_tunnel_info.is_l2_fwd)
    {
        egress_tunnel_type = bcmTunnelTypeEthIn6;
        tunnel_type_endpoint = bcmTunnelTypeIpAnyIn6;
        ingress_tunnel_type = bcmTunnelTypeEthIn6;
    }
    else
    {
        egress_tunnel_type = bcmTunnelTypeIpAnyIn6;
        tunnel_type_endpoint = bcmTunnelTypeIpAnyIn6;
        ingress_tunnel_type = bcmTunnelTypeIpAnyIn6;
    }

    /*
     * 0. Set legal FEC IDs
     */
    BCM_IF_ERROR_RETURN_MSG(dnx_srv6_update_fecs_id(unit), "");

    /*
     * 1. Set In-Port to In ETh-RIF
     */

    /** SRV6 Ingress Tunnel Eth RIF based on Port only */
    BCM_IF_ERROR_RETURN_MSG(in_port_intf_set(unit, in_port, cint_srv6_tunnel_info.eth_rif_intf_in[INGRESS]), "intf_in");
    if (cint_srv6_tunnel_info.is_l2_fwd)
    {
        BCM_IF_ERROR_RETURN_MSG(in_port_intf_set(unit, in_port, cint_srv6_tunnel_info.vlan_fwd), "intf_in");
    }

    /** End-Point-1 Eth RIF based on Port + VLAN ID so that we can re-use same port */
    BCM_IF_ERROR_RETURN_MSG(in_port_vid_intf_set(unit, in_port_end1, cint_srv6_tunnel_info.tunnel_vid[END_POINT_1_VID], cint_srv6_tunnel_info.eth_rif_intf_in[END_POINT_1]), "in_port_end1");

    /** Egress Eth RIF based on Port + VLAN ID so that we can re-use same port */
    snprintf(error_msg, sizeof(error_msg), "in_port = %d, intf_in = %d",
        in_port_egress, cint_srv6_tunnel_info.eth_rif_intf_in[EGRESS]);
    BCM_IF_ERROR_RETURN_MSG(in_port_vid_intf_set(unit, in_port_egress, cint_srv6_tunnel_info.tunnel_vid[EGRESS_VID], cint_srv6_tunnel_info.eth_rif_intf_in[EGRESS]), error_msg);

    /*
     * 2. Set Out-Port default properties, in case of ARP+AC no need
     */

    /** In SRV6 Ingress and End-Point-1 use the same out_port, (End-Point-1 and End-Point-2 receive from same Port, with different VLAN) */
    snprintf(error_msg, sizeof(error_msg), "intf_out out_port of SRV6 Ingress Tunnel %d", out_port);
    BCM_IF_ERROR_RETURN_MSG(out_port_set(unit, out_port), error_msg);

    /** Egress out_port */
    snprintf(error_msg, sizeof(error_msg), "out_port = %d", out_port_egress);
    BCM_IF_ERROR_RETURN_MSG(out_port_set(unit, out_port_egress), error_msg);

    /*
     * 3. Create ETH-RIF and set its properties
     */

    /** SRV6 Ingress Tunnel My-MAC */
    snprintf(error_msg, sizeof(error_msg), "intf_in %d", cint_srv6_tunnel_info.eth_rif_intf_in[INGRESS]);
    BCM_IF_ERROR_RETURN_MSG(intf_eth_rif_create(unit, cint_srv6_tunnel_info.eth_rif_intf_in[INGRESS], cint_srv6_tunnel_info.intf_in_mac_address[INGRESS]), error_msg);

    /** SRV6 Ingress Tunnel out-port SA - Here creating not Out-RIF, we don't need it SRv6 Tunnel, but VSI (with SA MAC) and its VID of END-Point1, to tie it to ARP+AC  */
    BCM_IF_ERROR_RETURN_MSG(intf_eth_rif_create(unit, cint_srv6_tunnel_info.tunnel_vid[END_POINT_1_VID], cint_srv6_tunnel_info.intf_out_mac_address[INGRESS]), "intf_out");

    /** SRV6 Ingress Tunnel out-port SA - Here creating not Out-RIF, we don't need it SRv6 Tunnel, but VSI (with SA MAC) and its VID of END-Point1, to tie it to ARP+AC  */
    BCM_IF_ERROR_RETURN_MSG(intf_eth_rif_create(unit, cint_srv6_tunnel_info.tunnel_vid[EGRESS_VID], cint_srv6_tunnel_info.intf_out_mac_address[INGRESS]), "intf_out");

    /** End-Point-1 My-MAC - set to SRV6 Ingress Tunnel next hop MAC */
    snprintf(error_msg, sizeof(error_msg), "intf_in %d", cint_srv6_tunnel_info.eth_rif_intf_in[END_POINT_1]);
    BCM_IF_ERROR_RETURN_MSG(intf_eth_rif_create(unit, cint_srv6_tunnel_info.eth_rif_intf_in[END_POINT_1], cint_srv6_tunnel_info.intf_in_mac_address[END_POINT_1]), error_msg);

    /** End-Point-1 out-port SA  */
    BCM_IF_ERROR_RETURN_MSG(intf_eth_rif_create(unit, cint_srv6_tunnel_info.eth_rif_intf_out[END_POINT_1], cint_srv6_tunnel_info.intf_out_mac_address[END_POINT_1]), "intf_out");


    /** Egress My-MAC - set to End-Point-2 next hop MAC */
    snprintf(error_msg, sizeof(error_msg), "intf_in %d", cint_srv6_tunnel_info.eth_rif_intf_in[EGRESS]);
    BCM_IF_ERROR_RETURN_MSG(intf_eth_rif_create(unit, cint_srv6_tunnel_info.eth_rif_intf_in[EGRESS], cint_srv6_tunnel_info.intf_in_mac_address[EGRESS]), error_msg);

    /** RCH Eth_Rif My MAC  */
    snprintf(error_msg, sizeof(error_msg), "intf_in %d", cint_srv6_tunnel_info.eth_rif_intf_in[RCH]);
    BCM_IF_ERROR_RETURN_MSG(intf_eth_rif_create(unit, cint_srv6_tunnel_info.eth_rif_intf_in[RCH], cint_srv6_tunnel_info.intf_in_mac_address[RCH]), error_msg);

    /** Egress out-port SA  */
    snprintf(error_msg, sizeof(error_msg), "intf_out = %d", cint_srv6_tunnel_info.eth_rif_intf_out[EGRESS]);
    BCM_IF_ERROR_RETURN_MSG(intf_eth_rif_create(unit, cint_srv6_tunnel_info.eth_rif_intf_out[EGRESS], cint_srv6_tunnel_info.intf_out_mac_address[EGRESS]), error_msg);

    /*
     * 4. Set Incoming ETH-RIF properties
     */

    l3_ingress_intf ingress_rif;

    /** SRV6 Ingress Tunnel VRF */
    l3_ingress_intf_init(&ingress_rif);
    ingress_rif.vrf = cint_srv6_tunnel_info.vrf_in[INGRESS];
    ingress_rif.intf_id = cint_srv6_tunnel_info.eth_rif_intf_in[INGRESS];
    BCM_IF_ERROR_RETURN_MSG(intf_ingress_rif_set(unit, &ingress_rif), "SRV6 Ingress Tunnel");

    /** End-Point-1 VRF */
    l3_ingress_intf_init(&ingress_rif);
    ingress_rif.vrf = cint_srv6_tunnel_info.vrf_in[END_POINT_1];
    ingress_rif.intf_id = cint_srv6_tunnel_info.eth_rif_intf_in[END_POINT_1];
    BCM_IF_ERROR_RETURN_MSG(intf_ingress_rif_set(unit, &ingress_rif), "End-Point-1");


    /** Egress Tunnel - 1st pass VRF */
    l3_ingress_intf_init(&ingress_rif);
    ingress_rif.vrf = cint_srv6_tunnel_info.vrf_in[EGRESS];
    ingress_rif.intf_id = cint_srv6_tunnel_info.eth_rif_intf_in[EGRESS];
    snprintf(error_msg, sizeof(error_msg), "intf_in = %d, vrf = %d",
        cint_srv6_tunnel_info.eth_rif_intf_in[EGRESS], cint_srv6_tunnel_info.vrf_in[EGRESS]);
    BCM_IF_ERROR_RETURN_MSG(intf_ingress_rif_set(unit, &ingress_rif), error_msg);

    /** Egress Tunnel - RCH - 2nd pass VRF */
    l3_ingress_intf_init(&ingress_rif);
    ingress_rif.vrf = cint_srv6_tunnel_info.vrf_in[RCH];
    ingress_rif.intf_id = cint_srv6_tunnel_info.eth_rif_intf_in[RCH];
    BCM_IF_ERROR_RETURN_MSG(intf_ingress_rif_set(unit, &ingress_rif), "intf_out");

    /*
     * 5. Create ARP and set its properties - ARP is Assumed be + AC. Create VLAN ID editing for each case.
     *    We use same port out for the End-Points, therefore the VLAN ID is what separates these cases.
     */

    uint32 flags2 = 0;

    flags2 |= BCM_L3_FLAGS2_VLAN_TRANSLATION;

    /*
     * SRV6 Ingress Tunnel ARP create, with VLAN ID of expected in End-Point-1 - adding to ARP+AC the VSI (created of tunne_vid of end-point-1) which includes the SA MAC,
     * cause in Ingress node, ETH-RIF out is not present, and VSI will come from ARP+AC
     * -using no VLAN
     */
    BCM_IF_ERROR_RETURN_MSG(l3__egress_only_encap__create_inner(unit, 0, &cint_srv6_tunnel_info.tunnel_arp_id[INGRESS], cint_srv6_tunnel_info.arp_next_hop_mac[INGRESS], cint_srv6_tunnel_info.tunnel_vid[END_POINT_1_VID], 0, flags2),
        "create egress object ARP only, in SRV6 Ingress Tunnel");

    BCM_IF_ERROR_RETURN_MSG(l3__egress_only_encap__create_inner(unit, 0, &cint_srv6_tunnel_info.tunnel_arp_id[END_POINT_1], cint_srv6_tunnel_info.arp_next_hop_mac[END_POINT_1], cint_srv6_tunnel_info.tunnel_vid[EGRESS_VID], 0, flags2),
        "create egress object ARP only, in End-Point-1");
    /** Egress ARP create, with VLAN ID of Egress Tunnel, however there we will look on only the Port */
    snprintf(error_msg, sizeof(error_msg), "create egress object ARP only: encap_id = %d, vsi = %d",
        cint_srv6_tunnel_info.tunnel_arp_id[EGRESS], cint_srv6_tunnel_info.tunnel_vid[EGRESS_OUT_VID]);
    BCM_IF_ERROR_RETURN_MSG(l3__egress_only_encap__create_inner(unit, 0, &cint_srv6_tunnel_info.tunnel_arp_id[EGRESS], cint_srv6_tunnel_info.arp_next_hop_mac[EGRESS], cint_srv6_tunnel_info.tunnel_vid[EGRESS_OUT_VID], 0,flags2), error_msg);

    /*
     * Create T_Insert tunnel chain, including 3 SIDs and ARP
     */
    {
        bcm_if_t arp_as_ift;
        bcm_gport_t next_sid_tunnel_id;
        int sid_idx;
        bcm_srv6_sid_initiator_info_t  sid_info;
        bcm_srv6_sid_initiator_info_t_init(&sid_info);

        BCM_L3_ITF_SET(arp_as_ift, BCM_L3_ITF_TYPE_LIF, cint_srv6_tunnel_info.tunnel_arp_id[END_POINT_1]);
        BCM_L3_ITF_LIF_TO_GPORT_TUNNEL(next_sid_tunnel_id, arp_as_ift);

        printf("Creating a transport tunnel with 3 SIDs\n");
        for (sid_idx = 0; sid_idx < NOF_DIPS_IN_TRANSPORT; sid_idx++)
        {
            bcm_srv6_sid_initiator_info_t_init(&sid_info);

            /** set SID address to be last SID0 */
            sal_memcpy(sid_info.sid, cint_srv6_tunnel_info.sid_encap_in_tunnel[sid_idx], 16);
            /** set to EEDB entry of SID0 */
            sid_info.encap_access = bcmEncapAccessTunnel4 - sid_idx;

            /** next_encap_id set to l3 interface - convert it from GPORT to l3_int */
            BCM_GPORT_TUNNEL_TO_L3_ITF_LIF(sid_info.next_encap_id, next_sid_tunnel_id);

            /** call the sid_initiator API to create the SID EEDB Entry and return its GPORT Tunnel-id */
            snprintf(error_msg, sizeof(error_msg), "for SID%d", sid_idx);
            BCM_IF_ERROR_RETURN_MSG(bcm_srv6_sid_initiator_create(unit, &sid_info), error_msg);
            next_sid_tunnel_id = sid_info.tunnel_id;
        }

        /** define the SRH Base structure which holds nof_sids, QOS, and SRH Base GPORT */
        bcm_srv6_srh_base_initiator_info_t srh_base_info;
        bcm_srv6_srh_base_initiator_info_t_init(&srh_base_info);

        /** we will pass the global-out-LIF id*/
        srh_base_info.flags = BCM_SRV6_SRH_BASE_INITIATOR_WITH_ID;

        /** convert SRH global-LIF id to GPORT */
        BCM_GPORT_TUNNEL_ID_SET(srh_base_info.tunnel_id, cint_srv6_tunnel_info.t_insert_global_id);

        /** set number of SIDs*/
        srh_base_info.nof_sids = NOF_DIPS_IN_TRANSPORT;
        BCM_GPORT_TUNNEL_TO_L3_ITF_LIF(srh_base_info.next_encap_id, next_sid_tunnel_id);

        /** set TTL and QOS modes */
        srh_base_info.egress_qos_model.egress_ttl = bcmQosEgressModelUniform;
        srh_base_info.egress_qos_model.egress_qos = bcmQosEgressModelUniform;
        srh_base_info.egress_qos_model.egress_ecn = bcmQosEgressEcnModelInvalid;
        srh_base_info.ttl = 0x0; /** needs to be 0 cause we don't use Pipe mode */

        int reduced_mode = 0;
        uint32 estimate_encap_size_required =
            *dnxc_data_get(unit, "lif", "out_lif", "global_lif_allocation_estimated_encap_size_enable", NULL);

        BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_get(unit, bcmSwitchSRV6ReducedModeEnable, &reduced_mode),
            "bcmSwitchSRV6ReducedModeEnable");

        if(estimate_encap_size_required)
        {
            /*
             * This is the last pass, it's always T.insert
             */
            srh_base_info.estimated_encap_size = NOF_DIPS_IN_TRANSPORT*16 + 8 - 16*reduced_mode;
        }

        /** call the srh_base_initiator API to create the SRH EEDB Entry and local-out-LIF for it */
        BCM_IF_ERROR_RETURN_MSG(bcm_srv6_srh_base_initiator_create(unit, &srh_base_info), "3rd pass");

        next_sid_tunnel_id = 0;
    }

    /*
     * 6. SRV6 FEC Entries
     */

    bcm_gport_t gport;

    int srv6_basic_lif_encode;
    uint32 fec_flags2 = 0;
    if(*dnxc_data_get(unit, "l3", "feature", "separate_fwd_rpf_dbs", NULL))
    {
        fec_flags2 |= BCM_L3_FLAGS2_FWD_ONLY;
    }

    if(*dnxc_data_get(unit, "l3", "fwd", "host_entry_support", NULL))
    {
        /** Egress 2nd Pass FEC Entry - due to Forwarding on IPv4 Layer above SRv6  */
        int encoded_fec;
        BCM_L3_ITF_SET(srv6_basic_lif_encode, BCM_L3_ITF_TYPE_LIF, cint_srv6_tunnel_info.tunnel_global_lif[INGRESS_IPV6_TUNNEL_GLOBAL_LIF]);
        BCM_GPORT_LOCAL_SET(gport, out_port);

        BCM_IF_ERROR_RETURN_MSG(l3__egress_only_fec__create_inner(unit, cint_srv6_tunnel_info.tunnel_fec_id[INGRESS_IPV6_TUNNEL_FEC_ID], 0 , srv6_basic_lif_encode, gport, 0, fec_flags2,
                                               0, 0,&encoded_fec), "create egress object FEC only");
    }
    else
    {
        int encoded_fec;
        /**Create FEC in second hierarchy and set its properties*/
        BCM_L3_ITF_SET(srv6_basic_lif_encode, BCM_L3_ITF_TYPE_LIF, cint_srv6_tunnel_info.tunnel_global_lif[INGRESS_IPV6_TUNNEL_GLOBAL_LIF]);
        BCM_GPORT_LOCAL_SET(gport, out_port);
        BCM_IF_ERROR_RETURN_MSG(l3__egress_only_fec__create_inner(unit, cint_srv6_tunnel_info.tunnel_fec_id[INGRESS_IPV6_TUNNEL_FEC_ID_2ND_HIER], srv6_basic_lif_encode, 0, gport, BCM_L3_2ND_HIERARCHY, fec_flags2,
                                               0, 0,&encoded_fec), "create egress object FEC_1 only");


        /** Create FEC in first hierarchy and set its properties*/
        BCM_GPORT_FORWARD_PORT_SET(gport, encoded_fec);
        BCM_IF_ERROR_RETURN_MSG(l3__egress_only_fec__create_inner(unit, cint_srv6_tunnel_info.tunnel_fec_id[INGRESS_IPV6_TUNNEL_FEC_ID], 0, cint_srv6_tunnel_info.tunnel_arp_id[INGRESS], gport, 0, fec_flags2, 0, 0, NULL),
            "create egress object FEC only, fec");
    }

    /** End-Point-1 FEC Entry - tying end-point-1 OUT-RIF with its OUT_Port, (ARP - DA and VLAN ID) */
    BCM_GPORT_LOCAL_SET(gport, out_port_end1);
    snprintf(error_msg, sizeof(error_msg), "create egress object FEC only for End-Point-1: fec = %d, intf_out = %d, encap_id = %d, out_port = %d",
        cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID], cint_srv6_tunnel_info.eth_rif_intf_out[END_POINT_1], cint_srv6_tunnel_info.tunnel_arp_id[END_POINT_1], out_port_end1);
    BCM_IF_ERROR_RETURN_MSG(l3__egress_only_fec__create(unit, cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID], cint_srv6_tunnel_info.eth_rif_intf_out[END_POINT_1], cint_srv6_tunnel_info.tunnel_arp_id[END_POINT_1], gport, 0, fec_flags2), error_msg);

    /** T_insert FEC Entry - tying end-point-1 OUT-RIF with its OUT_Port, (ARP - DA and VLAN ID) */
    BCM_GPORT_LOCAL_SET(gport, out_port_end1);
    BCM_L3_ITF_SET(srv6_basic_lif_encode, BCM_L3_ITF_TYPE_LIF, cint_srv6_tunnel_info.t_insert_global_id);
    snprintf(error_msg, sizeof(error_msg), "create egress object FEC only for End-Point with t insert fec = %d, intf_out = %d, encap_id = %d, out_port = %d",
        cint_srv6_tunnel_info.tunnel_fec_id[T_INSERT_FEC_ID], cint_srv6_tunnel_info.eth_rif_intf_out[END_POINT_1], cint_srv6_tunnel_info.t_insert_global_id, out_port_end1);
    BCM_IF_ERROR_RETURN_MSG(l3__egress_only_fec__create(unit, cint_srv6_tunnel_info.tunnel_fec_id[T_INSERT_FEC_ID], srv6_basic_lif_encode, 0, gport, 0, fec_flags2), error_msg);

    /*
     * On 1st Pass Egress, no FEC entry  because no more SIDs left to enter FWD on and then FEC,
     * in VTT5 there's LIF P2P which gives the destination right away
     */

    if(*dnxc_data_get(unit, "l3", "fwd", "host_entry_support", NULL))
    {
        /** Egress 2nd Pass FEC Entry - due to Forwarding on IPv4 Layer above SRv6  */
        int encoded_fec;
        BCM_GPORT_LOCAL_SET(gport, out_port_egress);
        BCM_IF_ERROR_RETURN_MSG(l3__egress_only_fec__create_inner(unit, cint_srv6_tunnel_info.tunnel_fec_id[EGRESS_FEC_ID], 0 , cint_srv6_tunnel_info.tunnel_arp_id[EGRESS], gport, 0, fec_flags2, 0, 0,&encoded_fec),
            "create egress object FEC only");
    }
    else
    {
        int encoded_fec;

        /** Create FEC in second hierarchy and set its properties*/
        int egress_encoded_fec2;
        BCM_GPORT_LOCAL_SET(gport, out_port_egress);
        BCM_IF_ERROR_RETURN_MSG(l3__egress_only_fec__create_inner(unit, cint_srv6_tunnel_info.tunnel_fec_id[EGRESS_FEC_ID_2ND_HIER], 0 , cint_srv6_tunnel_info.tunnel_arp_id[EGRESS], gport, BCM_L3_2ND_HIERARCHY, fec_flags2, 0, 0,&encoded_fec),
            "create egress object FEC only");


        /** Create FEC in first hierarchy and set its properties*/
        BCM_GPORT_FORWARD_PORT_SET(gport, encoded_fec);
        BCM_IF_ERROR_RETURN_MSG(l3__egress_only_fec__create_inner(unit, cint_srv6_tunnel_info.tunnel_fec_id[EGRESS_FEC_ID], 0 , cint_srv6_tunnel_info.eth_rif_intf_out[EGRESS], gport, 0, fec_flags2, 0, 0, NULL),
            "create egress object FEC only");
    }


    /*
     * 7. Add route entry - we work with specific DIP addresses, so we don't need to add best match route entries.
     */

    /*
     * 8. Add host entry
     */
    if (*dnxc_data_get(unit, "l3", "fwd", "host_entry_support", NULL))
    {
        /** SRV6 Tunnel Ingress Forwarding for IPv4 as next header over SRv6 to FEC Hierarchy to bring out IPV6, SRH, SIDs - not including OUT-ETH-RIF entry */
        BCM_GPORT_FORWARD_PORT_SET(gport, cint_srv6_tunnel_info.tunnel_fec_id[INGRESS_IPV6_TUNNEL_FEC_ID]);
        BCM_IF_ERROR_RETURN_MSG(add_host_ipv4(unit, cint_srv6_tunnel_info.route_ipv4_dip, cint_srv6_tunnel_info.vrf_in[INGRESS], 0, cint_srv6_tunnel_info.tunnel_arp_id[INGRESS], gport),
            "for SRV6 Ingress Tunnel");



        /** SRV6 Tunnel Ingress Forwarding for IPv6 as next header over SRv6 to FEC Hierarchy to bring out IPV6, SRH, SIDs - not including OUT-ETH-RIF entry */
        BCM_IF_ERROR_RETURN_MSG(add_host_ipv6_encap_dest(unit, cint_srv6_tunnel_info.route_ipv6_dip, cint_srv6_tunnel_info.vrf_in[INGRESS], 0, cint_srv6_tunnel_info.tunnel_arp_id[INGRESS], gport),
            "for SRV6 Ingress Tunnel");
        int _l3_itf;
        BCM_L3_ITF_SET(&_l3_itf, BCM_L3_ITF_TYPE_FEC, cint_srv6_tunnel_info.tunnel_fec_id[EGRESS_FEC_ID]);

        if(is_default)
        {
            /** add End-Point-2's next IP (u-SID) as host to do forwarding on to FEC (same VRF lookup as End-Point-1) */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-3: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_host_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[(is_prefix_48b_enabled ? END_POINT_1_DIP_48B_PREFIX_NO_DEF : END_POINT_3_DIP)], cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);

            /** add End-Point-3's next IP (u-SID) as host to do forwarding on to FEC (same VRF lookup as End-Point-1) */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-4: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_host_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[(is_prefix_48b_enabled ? END_POINT_2_DIP_48B_PREFIX_NO_DEF : END_POINT_4_DIP)], cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);

            /** add End-Point-4's next IP (u-SID) as host to do forwarding on to FEC (same VRF lookup as End-Point-1) */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-5: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_host_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[(is_prefix_48b_enabled ? END_POINT_3_DIP_48B_PREFIX_NO_DEF : END_POINT_5_DIP)], cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);

            /** add End-Point-4's (u-SID) as host to do forwarding on to FEC (same VRF lookup as End-Point-1) */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-1: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_host_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[EGRESS_DIP], cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);
            /** add End-Point-Classic case as host to do forwarding on to FEC - using the uSID Egress VRF (cause classic SID happens when SL > 0 and uSID Egress) */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-Classic: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_host_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[END_POINT_CLASSIC], cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);
            /** Egress tunnel destination*/
            BCM_IF_ERROR_RETURN_MSG(add_host_ipv4(unit, cint_srv6_tunnel_info.route_ipv4_dip, cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], _l3_itf, cint_srv6_tunnel_info.eth_rif_intf_out[EGRESS], 0),
                "for SRV6 Ingress Tunnel");

            /** add Egress 2nd-Pass, IPv6 Packet DIP as host to do forwarding on to FEC when IPv6 is next header over SRv6 */
            BCM_IF_ERROR_RETURN_MSG(add_host_ipv6_encap_dest(unit, cint_srv6_tunnel_info.route_ipv6_dip, cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], _l3_itf, cint_srv6_tunnel_info.eth_rif_intf_out[EGRESS], 0), "");
            /**Add last dip destination, when the packet is egress node, but the layer above is TCP, so no TT will occur */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-Classic: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_host_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[END_POINT_5_DIP], cint_srv6_tunnel_info.vrf_in[EGRESS], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);
            /** In case 48b prefix is enabled the penultimate EP DIP is the egress one*/
            if (is_prefix_48b_enabled)
            {
               /**Add last dip destination, when the packet is egress node, but the layer above is TCP, so no TT will occur */
                snprintf(error_msg, sizeof(error_msg), "for End-Point-Classic: vrf = %d, fec = %d",
                    cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
                BCM_IF_ERROR_RETURN_MSG(add_host_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[END_POINT_4_DIP], cint_srv6_tunnel_info.vrf_in[EGRESS], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);
           }
        }
        else
        {
            /** add End-Point-1's next IP (u-SID) as host to do forwarding on to FEC */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-2: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_host_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[(is_prefix_48b_enabled ? END_POINT_1_DIP_48B_PREFIX : END_POINT_2_DIP)], cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);

            /** add End-Point-2's next IP (u-SID) as host to do forwarding on to FEC (same VRF lookup as End-Point-1) */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-3: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_host_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[(is_prefix_48b_enabled ? END_POINT_2_DIP_48B_PREFIX : END_POINT_3_DIP)], cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);

            /** add End-Point-3's next IP (u-SID) as host to do forwarding on to FEC (same VRF lookup as End-Point-1) */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-4: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_host_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[(is_prefix_48b_enabled ? END_POINT_3_DIP_48B_PREFIX : END_POINT_4_DIP)], cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);

            /** add End-Point-4's next IP (u-SID) as host to do forwarding on to FEC (same VRF lookup as End-Point-1) */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-5: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_host_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[(is_prefix_48b_enabled ? END_POINT_4_DIP_48B_PREFIX : END_POINT_5_DIP)], cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);

            /** add End-Point-Classic case as host to do forwarding on to FEC - using the uSID Egress VRF (cause classic SID happens when SL > 0 and uSID Egress) */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-Classic: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_host_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[END_POINT_CLASSIC], cint_srv6_tunnel_info.vrf_in[EGRESS], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);

            /** add End-Point-5's (u-SID) as host to do forwarding on to FEC (same VRF lookup as End-Point-1) */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-1: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_host_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[EGRESS_DIP], cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);
            /** add Egress 2nd-Pass, IPv6 Packet DIP as host to do forwarding on to FEC when IPv6 is next header over SRv6 */
            BCM_IF_ERROR_RETURN_MSG(add_host_ipv6_encap_dest(unit, cint_srv6_tunnel_info.route_ipv6_dip, cint_srv6_tunnel_info.vrf_in[RCH], _l3_itf, cint_srv6_tunnel_info.eth_rif_intf_out[EGRESS], 0), "");
            /** In case 48b prefix is enabled the penultimate EP DIP is the egress one*/
            if (is_prefix_48b_enabled)
            {
                /**Add last dip destination, when the packet is egress node, but the layer above is TCP, so no TT will occur */
                snprintf(error_msg, sizeof(error_msg), "for End-Point-Classic: vrf = %d, fec = %d",
                    cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
                BCM_IF_ERROR_RETURN_MSG(add_host_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[END_POINT_5_DIP], cint_srv6_tunnel_info.vrf_in[EGRESS], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);
            }
            else
            {
                /**Add last dip destination, when the packet is egress node, but the layer above is TCP, so no TT will occur */
                snprintf(error_msg, sizeof(error_msg), "for End-Point-Classic: vrf = %d, fec = %d",
                    cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
                BCM_IF_ERROR_RETURN_MSG(add_host_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[EGRESS_DIP], cint_srv6_tunnel_info.vrf_in[EGRESS], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);
           }
        }

        /**Add dip destination for usid into T_insert flow */
        snprintf(error_msg, sizeof(error_msg), "for End-Point-Classic: vrf = %d, fec = %d",
            cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
        BCM_IF_ERROR_RETURN_MSG(add_host_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[END_POINT_TO_T_INSERT_FWD], cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[T_INSERT_FEC_ID]), error_msg);

        /** add Egress 2nd-Pass, IPv4 Packet DIP as host to do forwarding on to FEC when IPv4 is next header over SRv6*/
        BCM_IF_ERROR_RETURN_MSG(add_host_ipv4(unit, cint_srv6_tunnel_info.route_ipv4_dip, cint_srv6_tunnel_info.vrf_in[RCH], _l3_itf, cint_srv6_tunnel_info.eth_rif_intf_out[EGRESS], 0), "");

    }
    else
    {
        int vrf = 1;
        bcm_ip6_t ip6_mask = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
        bcm_ip_t ip4_mask =  0xFFFFFFFF;
        int _l3_itf;
        BCM_L3_ITF_SET(&_l3_itf, BCM_L3_ITF_TYPE_FEC, cint_srv6_tunnel_info.tunnel_fec_id[EGRESS_FEC_ID]);

        if (is_default)
        {
            /** add End-Point-2's next IP (u-SID) as host to do forwarding on to FEC (same VRF lookup as End-Point-1) */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-3: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_route_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[(is_prefix_48b_enabled ? END_POINT_1_DIP_48B_PREFIX_NO_DEF : END_POINT_3_DIP)], ip6_mask, cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);
            /** add End-Point-3's next IP (u-SID) as host to do forwarding on to FEC (same VRF lookup as End-Point-1) */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-4: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_route_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[(is_prefix_48b_enabled ? END_POINT_2_DIP_48B_PREFIX_NO_DEF : END_POINT_4_DIP)], ip6_mask, cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);
            /** add End-Point-4's next IP (u-SID) as host to do forwarding on to FEC (same VRF lookup as End-Point-1) */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-5: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_route_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[(is_prefix_48b_enabled ? END_POINT_3_DIP_48B_PREFIX_NO_DEF : END_POINT_5_DIP)], ip6_mask, cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);
            /**Add last dip destination, when the packet is egress node, but the layer above is TCP, so no TT will occur */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-Classic: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_route_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[EGRESS_DIP], ip6_mask, cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);

            /** add Egress 2nd-Pass, IPv4 Packet DIP as host to do forwarding on to FEC when IPv4 is next header over SRv6*/
            BCM_IF_ERROR_RETURN_MSG(add_route_ipv4(unit, cint_srv6_tunnel_info.route_ipv4_dip, ip4_mask, cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], _l3_itf), "");
            /** add End-Point-Classic case as host to do forwarding on to FEC - using the uSID Egress VRF (cause classic SID happens when SL > 0 and uSID Egress) */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-Classic: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_route_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[END_POINT_CLASSIC], ip6_mask, cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);
            /** add Egress 2nd-Pass, IPv6 Packet DIP as host to do forwarding on to FEC when IPv6 is next header over SRv6 */
            BCM_IF_ERROR_RETURN_MSG(add_route_ipv6(unit, cint_srv6_tunnel_info.route_ipv6_dip, ip6_mask, cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], _l3_itf), "");
            /** In case 48b prefix is enabled the penultimate EP DIP is the egress one*/
            if (is_prefix_48b_enabled)
            {
                /**Add last dip destination, when the packet is egress node, but the layer above is TCP, so no TT will occur */
                snprintf(error_msg, sizeof(error_msg), "for End-Point-Classic: vrf = %d, fec = %d",
                    cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
                BCM_IF_ERROR_RETURN_MSG(add_route_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[END_POINT_4_DIP], ip6_mask, cint_srv6_tunnel_info.vrf_in[NO_DEFAULT], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);
            }
        }
        else
        {
            /** add End-Point-1's next IP (u-SID) as host to do forwarding on to FEC */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-2: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_route_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[(is_prefix_48b_enabled ? END_POINT_1_DIP_48B_PREFIX : END_POINT_2_DIP)], ip6_mask, cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);
            /** add End-Point-2's next IP (u-SID) as host to do forwarding on to FEC (same VRF lookup as End-Point-1) */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-3: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_route_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[(is_prefix_48b_enabled ? END_POINT_2_DIP_48B_PREFIX : END_POINT_3_DIP)], ip6_mask, cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);
            /** add End-Point-3's next IP (u-SID) as host to do forwarding on to FEC (same VRF lookup as End-Point-1) */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-4: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_route_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[(is_prefix_48b_enabled ? END_POINT_3_DIP_48B_PREFIX : END_POINT_4_DIP)], ip6_mask, cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);
            /** add End-Point-4's next IP (u-SID) as host to do forwarding on to FEC (same VRF lookup as End-Point-1) */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-5: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_route_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[(is_prefix_48b_enabled ? END_POINT_4_DIP_48B_PREFIX : END_POINT_5_DIP)], ip6_mask, cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);
            /**Add last dip destination, when the packet is egress node, but the layer above is TCP, so no TT will occur */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-Classic: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_route_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[(is_prefix_48b_enabled ? END_POINT_5_DIP : EGRESS_DIP)], ip6_mask, cint_srv6_tunnel_info.vrf_in[EGRESS], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);

            /** add End-Point-Classic case as host to do forwarding on to FEC - using the uSID Egress VRF (cause classic SID happens when SL > 0 and uSID Egress) */
            snprintf(error_msg, sizeof(error_msg), "for End-Point-Classic: vrf = %d, fec = %d",
                cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
            BCM_IF_ERROR_RETURN_MSG(add_route_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[END_POINT_CLASSIC], ip6_mask, cint_srv6_tunnel_info.vrf_in[EGRESS], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);
            /** add Egress 2nd-Pass, IPv4 Packet DIP as host to do forwarding on to FEC when IPv4 is next header over SRv6*/
            BCM_IF_ERROR_RETURN_MSG(add_route_ipv4(unit, cint_srv6_tunnel_info.route_ipv4_dip, ip4_mask, cint_srv6_tunnel_info.vrf_in[RCH], _l3_itf), "");
            /** add Egress 2nd-Pass, IPv6 Packet DIP as host to do forwarding on to FEC when IPv6 is next header over SRv6 */
            BCM_IF_ERROR_RETURN_MSG(add_route_ipv6(unit, cint_srv6_tunnel_info.route_ipv6_dip, ip6_mask, cint_srv6_tunnel_info.vrf_in[RCH], _l3_itf), "");
        }

        /** SRV6 Tunnel Ingress Forwarding for IPv4 as next header over SRv6 to FEC Hierarchy to bring out IPV6, SRH, SIDs - not including OUT-ETH-RIF entry */
        BCM_IF_ERROR_RETURN_MSG(add_route_ipv4(unit, cint_srv6_tunnel_info.route_ipv4_dip, ip4_mask, cint_srv6_tunnel_info.vrf_in[INGRESS], cint_srv6_tunnel_info.tunnel_fec_id[INGRESS_IPV6_TUNNEL_FEC_ID]),
            "for SRV6 Ingress Tunnel");

        /** SRV6 Tunnel Ingress Forwarding for IPv6 as next header over SRv6 to FEC Hierarchy to bring out IPV6, SRH, SIDs - not including OUT-ETH-RIF entry */
        BCM_IF_ERROR_RETURN_MSG(add_route_ipv6(unit, cint_srv6_tunnel_info.route_ipv6_dip, ip6_mask, cint_srv6_tunnel_info.vrf_in[INGRESS], cint_srv6_tunnel_info.tunnel_fec_id[INGRESS_IPV6_TUNNEL_FEC_ID]),
            "for SRV6 Ingress Tunnel");
        /** add End-Point-5's (u-SID) as host to do forwarding on to FEC (same VRF lookup as End-Point-1) */
        snprintf(error_msg, sizeof(error_msg), "for End-Point-1: vrf = %d, fec = %d",
            cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
        BCM_IF_ERROR_RETURN_MSG(add_route_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[EGRESS_DIP], ip6_mask, cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);

        /**Add last dip no_default destination, when the packet is egress node, but the layer above is TCP, so no TT will occur */
        snprintf(error_msg, sizeof(error_msg), "for End-Point-Classic: vrf = %d, fec = %d",
            cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
        BCM_IF_ERROR_RETURN_MSG(add_route_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[END_POINT_5_DIP], ip6_mask, cint_srv6_tunnel_info.vrf_in[EGRESS], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]), error_msg);

        /**Add dip destination for usid into T_insert flow */
        snprintf(error_msg, sizeof(error_msg), "for End-Point-Classic: vrf = %d, fec = %d",
            cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[END_POINT_1_FEC_ID]);
        BCM_IF_ERROR_RETURN_MSG(add_route_ipv6(unit, cint_srv6_tunnel_info.tunnel_ip6_dip[END_POINT_TO_T_INSERT_FWD], ip6_mask, cint_srv6_tunnel_info.vrf_in[END_POINT_1], cint_srv6_tunnel_info.tunnel_fec_id[T_INSERT_FEC_ID]), error_msg);

    }

    if (cint_srv6_tunnel_info.is_l2_fwd)
    {
        /** SRV6 Tunnel Ingress Forwarding for ETH as next header over SRv6*/
        bcm_l2_addr_t l2addr2;
        bcm_l2_addr_t_init(&l2addr2, cint_srv6_tunnel_info.dmac_fwd, cint_srv6_tunnel_info.vlan_fwd);
        l2addr2.port  = gport;
        l2addr2.vid   = cint_srv6_tunnel_info.vlan_fwd;
        l2addr2.flags = BCM_L2_STATIC;

        BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_add(unit, &l2addr2), "");
    }

    /*
     * 9. Configuring ISR SRv6 Tunnel
     */
    {

        /*
         * create IPv6 Tunnel of SRv6 Type
         */
        bcm_tunnel_initiator_t tunnel_init_set;
        bcm_l3_intf_t intf;


        bcm_tunnel_initiator_t_init(&tunnel_init_set);
        bcm_l3_intf_t_init(&intf);
        tunnel_init_set.type = ingress_tunnel_type; /** when no SRH is present, creating a regular IPv6 tunnel type */
        sal_memcpy(tunnel_init_set.sip6, cint_srv6_tunnel_info.tunnel_ip6_sip, 16);
        sal_memcpy(tunnel_init_set.dip6, cint_srv6_tunnel_info.tunnel_ip6_dip[END_POINT_1_DIP], 16);

        /** only in case that no SRH is present and IPv6 tunnel is regular, use encap_access */
        if (!srh_present)
        {
            tunnel_init_set.encap_access    = bcmEncapAccessTunnel2;
        }

        tunnel_init_set.ttl = 128;
        tunnel_init_set.egress_qos_model.egress_ttl = bcmQosEgressModelPipeMyNameSpace;
        /** using our own Global-LIF for the IPv6 encap entry */
        tunnel_init_set.flags = BCM_TUNNEL_WITH_ID;
        BCM_GPORT_TUNNEL_ID_SET(tunnel_init_set.tunnel_id, cint_srv6_tunnel_info.tunnel_global_lif[INGRESS_IPV6_TUNNEL_GLOBAL_LIF]);
        if (cint_srv6_tunnel_info.is_l2_fwd)
        {
            tunnel_init_set.l3_intf_id = cint_srv6_tunnel_info.tunnel_arp_id[INGRESS];
        }
        BCM_IF_ERROR_RETURN_MSG(bcm_tunnel_initiator_create(unit, &intf, &tunnel_init_set), "for IPv6 Tunnel");


    }

    /*
     * 10. Configure the SRv6 ESR USP 1st Pass P2P IN_LIF into RCH Port and Ethernet Encapsulation
     */
    {

        /** Set Out-Port default properties for the recycled packets*/
        BCM_IF_ERROR_RETURN_MSG(out_port_set(unit, rch_port), "recycle_port");
        uint32 ibch1_supported = *dnxc_data_get(unit, "headers", "system_headers", "system_headers_ibch1_supported", NULL);
        if (!ibch1_supported)
        {
            /** Configure RCH port of Extended Termination type */
            snprintf(error_msg, sizeof(error_msg), "for rch_port %d", rch_port);
            BCM_IF_ERROR_RETURN_MSG(bcm_port_control_set(unit, rch_port, bcmPortControlRecycleApp, bcmPortControlRecycleAppExtendedTerm), error_msg);
        }
        /** Set port class in order for PMF to crop RCH ad IRPP */
        BCM_IF_ERROR_RETURN_MSG(bcm_port_class_set(unit,rch_port,bcmPortClassFieldIngressPMF3TrafficManagementPortCs,4), "");

        /** define the structure which holds the mapping between nof_sids to RCH port and encap_id */
        /** Create termination for next protocol nof_sids to RCH port and encap_id */
        int max_nof_terminated_usp_sids = *(dnxc_data_get (unit, "srv6", "termination", "max_nof_terminated_sids_usp", NULL));
        int max_nof_terminated_usp_sids_1pass = *(dnxc_data_get (unit, "srv6", "termination", "max_nof_terminated_sids_usd_1pass", NULL));
        int nof_2pass_recycle_entries = max_nof_terminated_usp_sids - max_nof_terminated_usp_sids_1pass;
        BCM_IF_ERROR_RETURN_MSG(srv6_create_extended_termination_create_all_sids_rcy_entries_and_extensions(
                unit, nof_2pass_recycle_entries, max_nof_terminated_usp_sids_1pass, rch_port),"");
    }

    /*
     * 11. End-Point configurations
     */
    {
        /** End-Point-1: Add MyDIP of current End-Point, getting same VRF for all End-Points */
        BCM_IF_ERROR_RETURN_MSG(srv6_tunnel_termination(unit, END_POINT_1_DIP, 0, srh_present, cint_srv6_tunnel_info.vrf_in[END_POINT_1], tunnel_type_endpoint, is_default), "");

        /** End-Point-2: Add MyDIP of current End-Point, getting same VRF for all End-Points */
        BCM_IF_ERROR_RETURN_MSG(srv6_tunnel_termination(unit, END_POINT_2_DIP, 0, srh_present, cint_srv6_tunnel_info.vrf_in[END_POINT_1], tunnel_type_endpoint, is_default), "");

        /** End-Point-3: Add MyDIP of current End-Point, getting same VRF for all End-Points */
        BCM_IF_ERROR_RETURN_MSG(srv6_tunnel_termination(unit, END_POINT_3_DIP, 0, srh_present, cint_srv6_tunnel_info.vrf_in[END_POINT_1], tunnel_type_endpoint, is_default), "");

        /** End-Point-4: Add MyDIP of current End-Point, getting same VRF for all End-Points */
        BCM_IF_ERROR_RETURN_MSG(srv6_tunnel_termination(unit, END_POINT_4_DIP, 0, srh_present, cint_srv6_tunnel_info.vrf_in[END_POINT_1], tunnel_type_endpoint, is_default), "");

        /** End-Point-5: Add MyDIP of current End-Point, getting same VRF for all End-Points */
        BCM_IF_ERROR_RETURN_MSG(srv6_tunnel_termination(unit, END_POINT_5_DIP, 0, srh_present, cint_srv6_tunnel_info.vrf_in[END_POINT_1], tunnel_type_endpoint, is_default), "");

        /** End-Point-5: Add MyDIP of current End-Point, getting same VRF for all End-Points */
        BCM_IF_ERROR_RETURN_MSG(srv6_tunnel_termination(unit, END_POINT_TO_T_INSERT, 0, srh_present, cint_srv6_tunnel_info.vrf_in[END_POINT_1], tunnel_type_endpoint, is_default), "");

        /** Egress: Add MyDIP according to the SIDs, because we need to terminate the IPV6 header with the current SID */
        if (is_prefix_48b_enabled)
        {
            /** handle the no_default and general egress tunnel */
            BCM_IF_ERROR_RETURN_MSG(srv6_tunnel_termination(unit, (is_default ? END_POINT_4_DIP : END_POINT_5_DIP), 1, srh_present, cint_srv6_tunnel_info.vrf_in[EGRESS], tunnel_type_endpoint, is_default), "");
        }
        else
        {
            /** handle the no_default and general egress tunnel */
            BCM_IF_ERROR_RETURN_MSG(srv6_tunnel_termination(unit, (is_default ? END_POINT_5_DIP : EGRESS_DIP), 1, srh_present, cint_srv6_tunnel_info.vrf_in[EGRESS], egress_tunnel_type, is_default), "");
        }
    }

    printf("%s(): Exit\r\n",proc_name);
    return BCM_E_NONE;
}


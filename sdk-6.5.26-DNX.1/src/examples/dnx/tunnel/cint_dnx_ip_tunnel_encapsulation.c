/*
 * 
 This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 
 Copyright 2007-2022 Broadcom Inc. All rights reserved.File: cint_dnx_ip_tunnel_encapsulation.c Purpose: Various examples for IPTunnels in J2        .
 *                                                                                                                     .
 * Test Scenario: ipv4-gre tunnel encapsulation with MPLS fwd.
 *
 * ./bcm.user
 * cd ../../../../regress/bcm
 * cint ../../src/./examples/sand/utility/cint_sand_utils_global.c
 * cint ../../src/./examples/dnx/l3/cint_dnx_ip_route_basic.c
 * cint ../../src/./examples/dnx/tunnel/cint_dnx_ip_tunnel_encapsulation.c
 * cint
 * ip_tunnel_encap_gre4_mpls_fwd(0,202,203);
 * exit;
 *
 * Traffic:
 * MPLS over ethernet packet
 * Send Ipv4oMPLSoETH packet, with dmac matching my_mac configured and a label to be swapped.
 * Label should be matched in ILM (MPLS forwarding table).
 * the packet should be encapsulated in IP-GRE4 tunnel.
 * tx 1 psrc=202 data=0x000c000200560050000012348847005b0140000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 *
 * Received packets on unit 0 should be:
 * Data: 0x00020000cd1d000c000200568100a0640800450a004800000000382f415ba0000011a100001100008847005b013f000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f200000000000000000000000
 *
 */

enum ipv4_encap_forward_type_e
{
    IPv4EncapsulationForwardTypeIPv4 = 0,
    IPv4EncapsulationForwardTypeIPv6 = 1,
    IPv4EncapsulationForwardTypeMPLS = 2
};

enum ipv4_encap_gre_type_e
{
    IPv4EncapsulationGRE4 = 0,
    IPv4EncapsulationGRE8 = 1,
    IPv4EncapsulationMPLSoGRE = 2
};

struct cint_ip_tunnel_basic_info_s
{
    int eth_rif_intf_provider;          /* out RIF */
    int eth_rif_intf_access;            /* in RIF */
    bcm_mac_t intf_access_mac_address;  /* mac for in RIF */
    bcm_mac_t tunnel_next_hop_mac;      /* mac for next hop */
    int access_vrf;                     /* VRF, resolved as Tunnel-InLif property */
    int access_vrf_to_vni;              /* VRF, used for VRF, network_domain -> VNI. Used for checking VRF->VNI miss. */
    int tunnel_fec_id;                  /* FEC id */
    int tunnel_arp_id;                  /* Id for ARP entry */
    bcm_ip_t tunnel_dip;                /* tunnel DIP */
    bcm_ip_t tunnel_sip;                /* tunnel SIP */
    bcm_tunnel_type_t tunnel_type;      /* tunnel type */
    int provider_vlan;                  /* VID assigned to the outgoing packet */
    int mpls_fwd_label;                 /* MPLS label used for forwarding */
    int gre_lb_key_enable;              /* Enable LB-Key on GRE4-IP tunnel */
    int tunnel_ttl;                     /* Ip tunnel header TTL */
    int tunnel_dscp;                    /* Ip tunnel header differentiated services code point */
    int tunnel_intf;                    /* Tunnel Interface */
    int tunnel_id;                      /* Tunnel ID */
    bcm_ip_t route_ipv4_dip;            /* Route dip */
    bcm_ip_t ipv4_mask;                 /* IPv4 Mask */
    int ecmp_id;                        /* ECMP ID */
    int ecmp_group_members_num;         /* ECMP group members number */
    bcm_ip6_t ipv6_dip;                 /* DIP for IPv6 forwarding */
    bcm_ip6_t ipv6_mask;                /* Mask for IPv6 routing */
    int gre_tunnel_outlif;              /* OUTLIF to be used by ip_tunnel_encapsulation_gre */
    int udp_dst_port;                   /* udp dest port for UDP header in UDPoIPv4 tunnel */
    int svtag_lookup;                   /* Perform an SVTAG lookup */
    int egress_qos_model;               /* use the Egress QoS configuration in cint_ip_tunnel_basic_egress_qos_s */
    int encap_label;                    /* encap label of MPLSoGRE */
};

cint_ip_tunnel_basic_info_s cint_ip_tunnel_basic_info = {
    /*
     * eth_rif_intf_provider | eth_rif_intf_access
     */
    100, 15,
    /*
     * intf_access_mac_address           | tunnel_next_hop_mac
     */
    {0x00, 0x0c, 0x00, 0x02, 0x00, 0x56}, {0x00, 0x02, 0x00, 0x00, 0xcd, 0x1d},
    /*
     * access_vrf
     */
    1,
    /*
     * access_vrf_to_vni
     */
    1,

    /*
     * tunnel_fec_id
     */
    40961,
    /*
     * tunnel_arp_id
     */
    5050,
    /*
     * tunnel_dip
     */
    0xA1000011, /* 161.0.0.17 */
    /*
     * tunnel_sip
     */
    0xA0000011, /* 160.0.0.17 */
    /*
     * tunnel_type
     */
    bcmTunnelTypeGreAnyIn4,
    /*
     * provider_vlan
     */
    100,
    /*
     * mpls_fwd_label
     */
    1456,
    /*
     * gre_lb_key_enable
     */
    0,
    /*
     * tunnel_ttl
     */
    56,
    /*
     * tunnel_dscp
     */
    10,
    /*
     * tunnel_intf
     */
    0,
    /*
     * tunnel_id
     */
    0,
    /*
     * route dip ipv4
     */
    0x7fffff03, /* 127.255.255.03 */
    /*
     * ipv4 mask
     */
    0xffffff00, /* 255.255.255.00 */
    /*
     * ecmp_id
     */
    50,
    /*
     * ecmp_group_members_num
     */
    1,
    /*
     * ipv6_dip
     */
    {
     0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8,
     0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, 0xec},
    /*
     * ipv6_mask
     */
    {
     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    /*
     * gre_tunnel_outlif
     */
     0x45346,
     /*
     * udp_dst_port
     */
    0,
    /*
     * svtag_lookup
     */
    0,
    /*
     * egress_qos_model
     */
    0,
    /*
     * encap_label (MPLSoGRE)
     */
    200
};

struct cint_ip_tunnel_basic_egress_qos_s
{
    bcm_qos_egress_model_type_t egress_qos;        /* pipe or uniform */
    bcm_qos_egress_model_type_t egress_ttl;        /* pipe or uniform */
    bcm_qos_egress_ecn_model_type_t egress_ecn;    /* eligible or invalid */
};

cint_ip_tunnel_basic_egress_qos_s cint_ip_tunnel_basic_egress_qos = {
    /*
     * egress_qos
     */
    bcmQosEgressModelPipeNextNameSpace,
    /*
     * egress_ttl
     */
    bcmQosEgressModelPipeMyNameSpace,
    /*
     * egress_ecn
     */
    bcmQosEgressEcnModelInvalid
};


/*
 * Ports and LIFs Initialization
 * The function ip_tunnel_encapsulation_open_route_interfaces serves as a configuration template to
 * more advanced tests
 * Inputs: unit - relevant unit;
 *         access_port - incoming port;
 *         provider_port - outgoing port;
 *         *proc_name - main function name;
 */
int
ip_tunnel_encapsulation_open_route_interfaces(
    int unit,
    int access_port,
    int provider_port,
    char *proc_name)
{
    int rv = BCM_E_NONE;

    /*
     * Configure ingress interfaces
     */
    rv = ip_tunnel_encapsulation_open_route_interfaces_access(unit, access_port, proc_name);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, ip_tunnel_encapsulation_open_route_interfaces_access\n", proc_name);
        return rv;
    }

    /*
     * Configure egress interfaces
     */
    rv = ip_tunnel_encapsulation_open_route_interfaces_provider(unit, provider_port, proc_name);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, ip_tunnel_encapsulation_open_route_interfaces_provider\n", proc_name);
        return rv;
    }

    /*
     * Create ARP entry and set its properties.
     */
    rv = l3__egress_only_encap__create(unit, 0, &(cint_ip_tunnel_basic_info.tunnel_arp_id),
                                       cint_ip_tunnel_basic_info.tunnel_next_hop_mac,
                                       cint_ip_tunnel_basic_info.provider_vlan);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, l3__egress_only_encap__create\n", proc_name);
        return rv;
    }

    return rv;
}

/*
 * Configure Ingress interfaces
 * Inputs: access_port - incomming port;
 *         *proc_name - main function name;
 */
int
ip_tunnel_encapsulation_open_route_interfaces_access(
    int unit,
    int access_port,
    char *proc_name)
{
    int rv = BCM_E_NONE;

    l3_ingress_intf ingr_intf;
    l3_ingress_intf_init(&ingr_intf);
    /*
     * Set In-Port to In ETh-RIF
     */
    rv = in_port_intf_set(unit, access_port, cint_ip_tunnel_basic_info.eth_rif_intf_access);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, in_port_intf_set\n", proc_name);
        return rv;
    }

    /*
     * Create routing interface for the routing's IP.
     * We use it as ingress ETH-RIF to perform ETH termination (my-mac procedure),
     * to enable IPv4 routing for this ETH-RIF and to set the VRF.
     */
    rv = intf_eth_rif_create(unit, cint_ip_tunnel_basic_info.eth_rif_intf_access,
                             cint_ip_tunnel_basic_info.intf_access_mac_address);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, intf_eth_rif_create eth_rif_intf_access\n", proc_name);
        return rv;
    }

    /*
     * Set Incoming ETH-RIF properties, VRF is updated for the rif.
     */
    ingr_intf.vrf = cint_ip_tunnel_basic_info.access_vrf;
    ingr_intf.intf_id = cint_ip_tunnel_basic_info.eth_rif_intf_access;
    rv = intf_ingress_rif_set(unit, &ingr_intf);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, intf_ingress_rif_set eth_rif_intf_access\n", proc_name);
    }

    return rv;
}

/*
 * Configure Egress interfaces
 * Inputs: access_port - outgoing port;
 *         *proc_name - main function name;
 */
int
ip_tunnel_encapsulation_open_route_interfaces_provider(
    int unit,
    int provider_port,
    char *proc_name)
{
    int rv = BCM_E_NONE;

    /*
     * Set Out-Port default properties
     */
    rv = out_port_set(unit, provider_port);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, out_port_set provider_port\n", proc_name);
        return rv;
    }

    /*
     * Create egress routing interface used for routing after the tunnel encapsulation.
     * We are using it as egress ETH-RIF, providing the link layer SA.
     */
    rv = intf_eth_rif_create(unit, cint_ip_tunnel_basic_info.eth_rif_intf_provider,
                             cint_ip_tunnel_basic_info.intf_access_mac_address);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, intf_eth_rif_create eth_rif_intf_provider\n", proc_name);
    }

    return rv;
}
/*
 * Main function for ip tunnel encapsulation with IPvX/MPLS forwarding on Jericho 2 only
 * The function implements various IP tunnel encapsulation of IPvXoETH/MPLSoETH packet
 * Inputs: unit - relevant unit;
 *         access_port      - incoming port;
 *         provider_port    - outgoing port;
 *         forward_type     - IPv4 FWD/IPv6 FWD/MPLS FWD;
 *         gre_type         - IPv4EncapsulationGRE4/IPv4EncapsulationGRE8/IPv4EncapsulationMPLSoGRE;
 */
int
ip_tunnel_encap_with_various_fwd(
    int unit,
    int access_port,
    int provider_port,
    int forward_type,
    int gre_type)
{
    int rv = BCM_E_NONE;
    char *proc_name;
    proc_name = "ip_tunnel_encap_with_various_fwd";

    if (gre_type == IPv4EncapsulationGRE8)
    {
        cint_ip_tunnel_basic_info.gre_lb_key_enable = 1;
    }

    rv = get_first_fec_in_range_which_not_in_ecmp_range(unit, 0, 0, &cint_ip_tunnel_basic_info.tunnel_fec_id);
    if (rv != BCM_E_NONE)
    {
        printf("Error, get_first_fec_in_range_which_not_in_ecmp_range\n");
        return rv;
    }
    /*
     * Initialize ports, LIFs, Eth-RIFs etc
     */
    rv = ip_tunnel_encapsulation_open_route_interfaces(unit, access_port, provider_port, *proc_name);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, ip_tunnel_encapsulation_open_route_interfaces\n", proc_name);
        return rv;
    }

    /*
     * Create GRE IP tunnel
     */
    rv = tunnel_initiator_create(unit, cint_ip_tunnel_basic_info.tunnel_arp_id, &cint_ip_tunnel_basic_info.tunnel_intf,
                                 cint_ip_tunnel_basic_info.gre_lb_key_enable);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, tunnel_initiator_create\n", proc_name);
        return rv;
    }

    if (gre_type == IPv4EncapsulationMPLSoGRE )
    {
        /** Create MPLS tunnel initiator **/
        bcm_if_t mpls_intf_id;
        rv = mpls_swap_tunnel_create(unit, cint_ip_tunnel_basic_info.encap_label, cint_ip_tunnel_basic_info.tunnel_intf, &mpls_intf_id);
        if (rv != BCM_E_NONE)
        {
            printf("%s(): Error, mpls_swap_tunnel_create\n", proc_name);
            return rv;
        }
        cint_ip_tunnel_basic_info.tunnel_intf = mpls_intf_id;
    }

    if (forward_type == IPv4EncapsulationForwardTypeMPLS)
    {
        /*
         * Add MPLS route to IP-Tunnel.
         */
        bcm_if_t mpls_intf_id;
        rv = mpls_swap_tunnel_create(unit, cint_ip_tunnel_basic_info.mpls_fwd_label, cint_ip_tunnel_basic_info.tunnel_intf, &mpls_intf_id);
        if (rv != BCM_E_NONE)
        {
            printf("%s(): Error, mpls_swap_tunnel_create\n", proc_name);
            return rv;
        }
        cint_ip_tunnel_basic_info.tunnel_intf = mpls_intf_id;
    }

    int fec_id;
    BCM_L3_ITF_SET(&fec_id, BCM_L3_ITF_TYPE_FEC, cint_ip_tunnel_basic_info.tunnel_fec_id);
    /*
     * Create FEC and configure its: Outlif, Destination port, Global Out-EthRIF
     */
    int fwd_flag = (*dnxc_data_get(unit, "l3", "feature", "separate_fwd_rpf_dbs", NULL)) ? BCM_L3_FLAGS2_FWD_ONLY : 0;
    rv = l3__egress_only_fec__create(unit, cint_ip_tunnel_basic_info.tunnel_fec_id, cint_ip_tunnel_basic_info.tunnel_intf, 0, provider_port, 0, fwd_flag);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, l3__egress_only_fec__create failed to execute! \n", proc_name);
        return rv;
    }

    if (forward_type == IPv4EncapsulationForwardTypeMPLS)
    {
        /*
         * Create mpls LSF for port pointed by FEC
         */
        rv = mpls_switch_tunnel_create(unit, cint_ip_tunnel_basic_info.mpls_fwd_label,
                                      fec_id);
        if (rv != BCM_E_NONE)
        {
            printf("%s(): Error, mpls_switch_tunnel_create\n", proc_name);
            return rv;
        }
    }
    else if (forward_type == IPv4EncapsulationForwardTypeIPv4)
    {
        /*
         * Add Host entry
         */
        rv = add_host_ipv4(unit, cint_ip_tunnel_basic_info.route_ipv4_dip, cint_ip_tunnel_basic_info.access_vrf, fec_id, 0, 0);
        if (rv != BCM_E_NONE)
        {
            printf("%s(): Error, add_host_ipv4 failed to execute! \n", proc_name);
            return rv;
        }
    }
    else
    {
        rv = add_host_ipv6(unit, cint_ip_tunnel_basic_info.ipv6_dip, cint_ip_tunnel_basic_info.access_vrf, fec_id);
        if (rv != BCM_E_NONE)
        {
            printf("%s(): Error, add_host_ipv6 failed to execute! \n", proc_name);
            return rv;
        }
    }

    return rv;
}


/*
 * Main function for UDP ip tunnel encapsulation with IPv4 forwarding on Jericho 2 only
 * The function implements UDP IP tunnel encapsulation of IPv4oETH packet
 * Inputs: unit             - relevant unit;
 *         access_port      - incoming port;
 *         provider_port    - outgoing port;
 */
int
ip_tunnel_encap_udp_ipvx_fwd(
    int unit,
    int access_port,
    int provider_port,
    int udp_dst_port)
{
    int rv;
    char *proc_name;
    proc_name = "ip_tunnel_encap_udp_ipvx_fwd";

    cint_ip_tunnel_basic_info.tunnel_type = bcmTunnelTypeUdp;
    cint_ip_tunnel_basic_info.udp_dst_port = udp_dst_port;

    rv = ip_tunnel_encap_with_various_fwd(unit, access_port, provider_port, IPv4EncapsulationForwardTypeIPv4, IPv4EncapsulationGRE4);
    if (rv != BCM_E_NONE)
    {
        printf("Error, ip_tunnel_encap_with_various_fwd\n");
        return rv;
    }
    /* add host entry for ipv6 forwarding */
    int fec_id;
    BCM_L3_ITF_SET(&fec_id, BCM_L3_ITF_TYPE_FEC, cint_ip_tunnel_basic_info.tunnel_fec_id);
    rv = add_host_ipv6(unit, cint_ip_tunnel_basic_info.ipv6_dip, cint_ip_tunnel_basic_info.access_vrf, fec_id);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, add_host_ipv6 failed to execute! \n", proc_name);
        return rv;
    }

    return rv;
}

/*
 * Main function for GRE ip tunnel encapsulation with MPLS forwarding on Jericho 2 only
 * The function implements GRE IP tunnel encapsulation of MPLSoETH0 packet
 * Inputs: unit             - relevant unit;
 *         access_port      - incoming port;
 *         provider_port    - outgoing port;
 */
int
ip_tunnel_encap_gre4_mpls_fwd(
    int unit,
    int access_port,
    int provider_port)
{
    int rv = BCM_E_NONE;
    rv = ip_tunnel_encap_with_various_fwd(unit, access_port, provider_port, IPv4EncapsulationForwardTypeMPLS, IPv4EncapsulationGRE4);
    if (rv != BCM_E_NONE)
    {
        printf("Error, ip_tunnel_encap_with_various_fwd\n");
        return rv;
    }

    return rv;
}

/*
 * Main function for VXLAN-GPE IP tunnel encapsulation with MPLS forwarding on Jericho 2
 * The function implements VXLANoUDPoIPv4 tunnel encapsulation of MPLSoETH packet
 * Inputs: unit          - relevant unit;
 *         access_port   - incoming port;
 *         provider_port - outgoing port;
 */
int
ip_tunnel_encap_vxlan_gpe_mpls_fwd(
    int unit,
    int access_port,
    int provider_port,
    int vsi)
{
    int rv = BCM_E_NONE;
    char *proc_name;
    bcm_if_t mpls_intf_id;
    bcm_l3_egress_ecmp_t ecmp;
    cint_ip_tunnel_basic_info.eth_rif_intf_access = vsi;
    cint_ip_tunnel_basic_info.gre_lb_key_enable = 0;
    cint_ip_tunnel_basic_info.tunnel_type = bcmTunnelTypeVxlanGpe;

    proc_name = "ip_tunnel_encap_vxlan_gpe_mpls_fwd";

    rv = get_first_fec_in_range_which_not_in_ecmp_range(unit, 0, 0, &cint_ip_tunnel_basic_info.tunnel_fec_id);
    if (rv != BCM_E_NONE)
    {
        printf("Error, get_first_fec_in_range_which_not_in_ecmp_range\n");
        return rv;
    }
    /** Initialize ports, LIFs, Eth-RIFs etc */
    rv = ip_tunnel_encapsulation_open_route_interfaces(unit, access_port, provider_port, *proc_name);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, ip_tunnel_encapsulation_open_route_interfaces\n", proc_name);
        return rv;
    }

    /** Create VXLAN-GPE IP tunnel */
    rv = tunnel_initiator_create(unit, cint_ip_tunnel_basic_info.tunnel_arp_id, &cint_ip_tunnel_basic_info.tunnel_intf,
                                 cint_ip_tunnel_basic_info.gre_lb_key_enable);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, tunnel_initiator_create\n", proc_name);
        return rv;
    }

    /** Add MPLS route to IP-Tunnel.*/
    rv = mpls_swap_tunnel_create(unit, cint_ip_tunnel_basic_info.mpls_fwd_label, cint_ip_tunnel_basic_info.tunnel_intf, &mpls_intf_id);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, mpls_swap_tunnel_create\n", proc_name);
        return rv;
    }

    /** Create FEC and configure its: Outlif, Destination port, Global Out-EthRIF */
    int fwd_flag = (*dnxc_data_get(unit, "l3", "feature", "separate_fwd_rpf_dbs", NULL)) ? BCM_L3_FLAGS2_FWD_ONLY : 0;
    rv = l3__egress_only_fec__create(unit, cint_ip_tunnel_basic_info.tunnel_fec_id, mpls_intf_id,
                                     0, provider_port, 0, fwd_flag);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, l3__egress_only_fec__create\n", proc_name);
        return rv;
    }

    /** Create an ECMP group */
    rv = l3__ecmp_create(unit, cint_ip_tunnel_basic_info.ecmp_id,
                         cint_ip_tunnel_basic_info.ecmp_group_members_num,
                         cint_ip_tunnel_basic_info.tunnel_fec_id, BCM_L3_WITH_ID,
                         BCM_L3_ECMP_DYNAMIC_MODE_DISABLED, &ecmp, 0);
    if (rv != BCM_E_NONE)
    {
        printf("Error, l3__ecmp_create\n");
        return rv;
    }

    /** Create mpls LSF for port pointed by FEC, pointed by ECMP group id */
    rv = mpls_switch_tunnel_create(unit, cint_ip_tunnel_basic_info.mpls_fwd_label, cint_ip_tunnel_basic_info.ecmp_id);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, mpls_switch_tunnel_create\n", proc_name);
        return rv;
    }

    rv = vxlan_network_domain_management_l3_egress(unit);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, vxlan_network_domain_management_l3_egress\n", proc_name);
        return rv;
    }
    return rv;
}

int
ip_tunnel_encap_vxlan_gpe_vrf_to_vni_miss() {
    cint_ip_tunnel_basic_info.access_vrf_to_vni++;
    return 0;
}

/*
 * Main function for VXLAN-GPE IP tunnel encapsulation with IPv6 forwarding on Jericho 2
 * The function implements VXLANoUDPoIPv4 tunnel encapsulation of IPv6oETH packet
 * Inputs: unit          - relevant unit;
 *         access_port   - incoming port;
 *         provider_port - outgoing port;
 */
int
ip_tunnel_encap_vxlan_gpe_ipv6_fwd(
    int unit,
    int access_port,
    int provider_port,
    int vsi)
{
    int rv = BCM_E_NONE;
    char *proc_name;
    bcm_l3_egress_ecmp_t ecmp;
    cint_ip_tunnel_basic_info.eth_rif_intf_access = vsi;
    cint_ip_tunnel_basic_info.gre_lb_key_enable = 0;
    cint_ip_tunnel_basic_info.tunnel_type = bcmTunnelTypeVxlanGpe;

    rv = get_first_fec_in_range_which_not_in_ecmp_range(unit, 0, 0, &cint_ip_tunnel_basic_info.tunnel_fec_id);
    if (rv != BCM_E_NONE)
    {
        printf("Error, get_first_fec_in_range_which_not_in_ecmp_range\n");
        return rv;
    }
    proc_name = "ip_tunnel_encap_vxlan_gpe_ipv6_fwd";

    /** Initialize ports, LIFs, Eth-RIFs etc */
    rv = ip_tunnel_encapsulation_open_route_interfaces(unit, access_port, provider_port, *proc_name);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, ip_tunnel_encapsulation_open_route_interfaces\n", proc_name);
        return rv;
    }

    /** Create VXLAN-GPE IP tunnel */
    rv = tunnel_initiator_create(unit, cint_ip_tunnel_basic_info.tunnel_arp_id, &cint_ip_tunnel_basic_info.tunnel_intf,
                                 cint_ip_tunnel_basic_info.gre_lb_key_enable);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, tunnel_initiator_create\n", proc_name);
        return rv;
    }

    /** Create FEC and configure its: Outlif, Destination port, Global Out-EthRIF */
    int fwd_flag = (*dnxc_data_get(unit, "l3", "feature", "separate_fwd_rpf_dbs", NULL)) ? BCM_L3_FLAGS2_FWD_ONLY : 0;
    rv = l3__egress_only_fec__create(unit, cint_ip_tunnel_basic_info.tunnel_fec_id, cint_ip_tunnel_basic_info.tunnel_intf,
                                     0, provider_port, 0, fwd_flag);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, l3__egress_only_fec__create\n", proc_name);
        return rv;
    }

    /** Create an ECMP group */
    rv = l3__ecmp_create(unit, cint_ip_tunnel_basic_info.ecmp_id,
                         cint_ip_tunnel_basic_info.ecmp_group_members_num,
                         cint_ip_tunnel_basic_info.tunnel_fec_id, BCM_L3_WITH_ID,
                         BCM_L3_ECMP_DYNAMIC_MODE_DISABLED, &ecmp, 0);
    if (rv != BCM_E_NONE)
    {
        printf("Error, l3__ecmp_create\n");
        return rv;
    }

    /** IPv6 forwarding, FEC pointed by ECMP group id*/
    rv = add_host_ipv6(unit, cint_ip_tunnel_basic_info.ipv6_dip,
                       cint_ip_tunnel_basic_info.access_vrf, cint_ip_tunnel_basic_info.ecmp_id);
    if (rv != BCM_E_NONE)
    {
        printf("Error, add_host_ipv6 \n");
        return rv;
    }

    vxlan_network_domain_management_l3_egress(unit);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, vxlan_network_domain_management_l3_egress\n", proc_name);
        return rv;
    }
    return rv;
}


/* Create IP tunnel
 * Parameters: arp_itf - tunnel ARP interface Id
 *             *tunnel_intf - tunnel interface
 *             gre_protocol_type - configure global GRE.protocol (when not IPvX or Eth)
 *             gre_lb_key_enable - boolean indicating GRE8 with lb key
 */
int
tunnel_initiator_create(
    int unit,
    bcm_if_t arp_itf,
    bcm_if_t * tunnel_intf,
    int gre_lb_key_enable)
{
    int rv;
    bcm_tunnel_initiator_t tunnel_info;
    bcm_l3_intf_t l3_intf;

    /*
     * Create IP tunnel initiator for encapsulating GRE4oIPv4 tunnel header
     */
    bcm_tunnel_initiator_t_init(&tunnel_info);
    tunnel_info.dip = cint_ip_tunnel_basic_info.tunnel_dip;
    tunnel_info.sip = cint_ip_tunnel_basic_info.tunnel_sip;

    if (gre_lb_key_enable)
    {
        tunnel_info.flags |= BCM_TUNNEL_INIT_GRE_KEY_USE_LB;
    }

    tunnel_info.dscp = cint_ip_tunnel_basic_info.tunnel_dscp;
    tunnel_info.egress_qos_model.egress_qos = bcmQosEgressModelPipeNextNameSpace;
    if (cint_ip_tunnel_basic_info.egress_qos_model) {
        tunnel_info.egress_qos_model.egress_qos = cint_ip_tunnel_basic_egress_qos.egress_qos;
        tunnel_info.egress_qos_model.egress_ttl = cint_ip_tunnel_basic_egress_qos.egress_ttl;
        tunnel_info.egress_qos_model.egress_ecn = cint_ip_tunnel_basic_egress_qos.egress_ecn;
    }
    tunnel_info.type = cint_ip_tunnel_basic_info.tunnel_type;
    tunnel_info.ttl = cint_ip_tunnel_basic_info.tunnel_ttl;
    tunnel_info.l3_intf_id = arp_itf;
    tunnel_info.encap_access = bcmEncapAccessTunnel4;
    if (cint_ip_tunnel_basic_info.svtag_lookup) {
        tunnel_info.flags  |= BCM_TUNNEL_INIT_SVTAG_ENABLE;
    }
    if (*tunnel_intf > 0)
    {
        BCM_GPORT_TUNNEL_ID_SET(tunnel_info.tunnel_id, *tunnel_intf);
        tunnel_info.flags |= BCM_TUNNEL_WITH_ID;
    }

    tunnel_info.outlif_counting_profile = BCM_STAT_LIF_COUNTING_PROFILE_NONE;
    tunnel_info.udp_dst_port = cint_ip_tunnel_basic_info.udp_dst_port;
    bcm_l3_intf_t_init(&l3_intf);

    rv = bcm_tunnel_initiator_create(unit, &l3_intf, tunnel_info);
    if (rv != BCM_E_NONE)
    {
        printf("Error, bcm_tunnel_initiator_create \n");
    }

    *tunnel_intf = l3_intf.l3a_intf_id;
    cint_ip_tunnel_basic_info.tunnel_id = tunnel_info.tunnel_id;
    return rv;
}

/*
 * Add MPLS route to IP-Tunnel.
 */
int
mpls_swap_tunnel_create(
    int unit,
    int mpls_fwd_label,
    bcm_if_t tunnel_intf,
    bcm_if_t * mpls_intf_id)
{
    int rv = BCM_E_NONE;
    bcm_mpls_egress_label_t label_array[1];
    int num_labels = 1;

    bcm_mpls_egress_label_t_init(&label_array[0]);

    /*
     * Pushed or Swapping label.
     * The label will be pushed for IP forwarding context and swapped for
     * MPLS forwarding context.
     */
    label_array[0].label = mpls_fwd_label;
    /*
     * Set the next pointer of this entry to be the IP tunnel. This configuration is new compared to
     * Jericho, where the arp pointer used to be connected to the EEDB entry via
     * bcm_l3_egress_create (with egress flag indication).
     */
    label_array[0].l3_intf_id = tunnel_intf;

    label_array[0].flags |= BCM_MPLS_EGRESS_LABEL_TTL_DECREMENT;

    rv = bcm_mpls_tunnel_initiator_create(unit, 0, num_labels, label_array);
    if (rv != BCM_E_NONE)
    {
        printf("Error, in bcm_mpls_tunnel_initiator_create\n");
        return rv;
    }

    *mpls_intf_id = label_array[0].tunnel_id;

    return rv;
}

/*
 * Create mpls LSF for port pointed by FEC
 */
int
mpls_switch_tunnel_create(
    int unit,
    bcm_mpls_label_t label,
    int fec_id)
{

    int rv;
    bcm_mpls_tunnel_switch_t entry;

    /*
     * No flag is needed to indicate the action, since the information for the swap/php action is
     * included in the EEDB, pointed from the ILM.
     */

    bcm_mpls_tunnel_switch_t_init(&entry);

    /** incoming label */
    entry.label = label;
    entry.action = BCM_MPLS_SWITCH_ACTION_NOP;
    entry.flags = BCM_MPLS_SWITCH_TTL_DECREMENT;

    /** FEC entry pointing to port */
    BCM_GPORT_FORWARD_PORT_SET(entry.port, fec_id);

    rv = bcm_mpls_tunnel_switch_create(unit, &entry);
    if (rv != BCM_E_NONE)
    {
        printf("Error, in bcm_mpls_tunnel_switch_create\n");
        return rv;
    }

    return rv;
}


int
vxlan_network_domain_management_l3_egress(
    int unit)
{
    int rv;
    bcm_vxlan_network_domain_config_t config;
    bcm_vxlan_network_domain_config_t_init(&config);
    /*
     * configure VRF->VNI
     */
    config.flags            = BCM_VXLAN_NETWORK_DOMAIN_CONFIG_EGRESS_ONLY | BCM_VXLAN_NETWORK_DOMAIN_CONFIG_L3_MAPPING;
    config.vrf              = cint_ip_tunnel_basic_info.access_vrf_to_vni;
    config.vni              = 5000;
    config.network_domain   = 0;

    rv = bcm_vxlan_network_domain_config_add(unit, &config);
    if (rv != BCM_E_NONE)
    {
        printf("Error, bcm_vxlan_network_domain_config_add \n");
        return rv;
    }
    return rv;
}

/**update l3 fodo entry qos profile for IP forward header remark*/
int
vxlan_network_domain_management_l3_egress_replace(int unit, int qos_map_id)
{
    int rv;
    bcm_vxlan_network_domain_config_t config;
    bcm_vxlan_network_domain_config_t_init(&config);
    /*
     * Update network domain for the created VNI->VRF
     */
    config.flags            = BCM_VXLAN_NETWORK_DOMAIN_CONFIG_EGRESS_ONLY | BCM_VXLAN_NETWORK_DOMAIN_CONFIG_L3_MAPPING;
    config.vrf              = cint_ip_tunnel_basic_info.access_vrf;
    config.network_domain   = 0;

    rv = bcm_vxlan_network_domain_config_get (unit, &config);
    if (rv != BCM_E_NONE)
    {
        printf("Error, bcm_vxlan_network_domain_config_add \n");
        return rv;
    }
    /**replace qos map id*/
    config.flags            |= BCM_VXLAN_NETWORK_DOMAIN_CONFIG_REPLACE;
    config.qos_map_id = qos_map_id;
    rv = bcm_vxlan_network_domain_config_add(unit, &config);
    if (rv != BCM_E_NONE)
    {
        printf("Error, bcm_vxlan_network_domain_config_add \n");
        return rv;
    }
    return rv;
}

/*
 * Main function for GRE ip tunnel encapsulation with IPv4 forwarding on Jericho 2 only
 * The function implements GRE4 IP tunnel encapsulation of IPv4oETH0 packet
 * Inputs: unit             - relevant unit;
 *         access_port      - incoming port;
 *         provider_port    - outgoing port;
 */
int
ip_tunnel_encap_gre4_ipv4_fwd(
    int unit,
    int access_port,
    int provider_port)
{
    int rv = BCM_E_NONE;

    rv = ip_tunnel_encap_with_various_fwd(unit, access_port, provider_port, IPv4EncapsulationForwardTypeIPv4, IPv4EncapsulationGRE4);
    if (rv != BCM_E_NONE)
    {
        printf("Error, ip_tunnel_encap_with_various_fwd\n");
        return rv;
    }

    return rv;
}

/*
 * Main function for GRE ip tunnel encapsulation with IPv6 forwarding on Jericho 2 only
 * The function implements GRE IP tunnel encapsulation of IPv6oETH0 packet
 * Inputs: unit             - relevant unit;
 *         access_port      - incoming port;
 *         provider_port    - outgoing port;
 */
int
ip_tunnel_encap_gre4_ipv6_fwd(
    int unit,
    int access_port,
    int provider_port)
{
    int rv = BCM_E_NONE;

    rv = ip_tunnel_encap_with_various_fwd(unit, access_port, provider_port, IPv4EncapsulationForwardTypeIPv6, IPv4EncapsulationGRE4);
    if (rv != BCM_E_NONE)
    {
        printf("Error, ip_tunnel_encap_with_various_fwd\n");
        return rv;
    }

    return rv;
}

/*
 * Main function for IpAnyIn4 tunnel encapsulation with IPv4 forwarding on Jericho 2 only
 * The function implements IpAnyIn4 tunnel encapsulation of IPv4oETH packet
 * Inputs: unit             - relevant unit;
 *         access_port      - incoming port;
 *         provider_port    - outgoing port;
 */
int
ip_tunnel_encap_ipany_ipvx_fwd(
    int unit,
    int access_port,
    int provider_port)
{
    int rv = BCM_E_NONE;
    char *proc_name;
    proc_name = "ip_tunnel_encap_ipany_ipvx_fwd";

    cint_ip_tunnel_basic_info.tunnel_type       = bcmTunnelTypeIpAnyIn4;
    rv = ip_tunnel_encap_with_various_fwd(unit, access_port, provider_port, IPv4EncapsulationForwardTypeIPv4, IPv4EncapsulationGRE4);
    if (rv != BCM_E_NONE)
    {
        printf("Error, ip_tunnel_encap_with_various_fwd\n");
        return rv;
    }
    /* add host entry for ipv6 forwarding */
    int fec_id;
    BCM_L3_ITF_SET(&fec_id, BCM_L3_ITF_TYPE_FEC, cint_ip_tunnel_basic_info.tunnel_fec_id);
    rv = add_host_ipv6(unit, cint_ip_tunnel_basic_info.ipv6_dip, cint_ip_tunnel_basic_info.access_vrf, fec_id);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, add_host_ipv6 failed to execute! \n", proc_name);
        return rv;
    }

    return rv;
}


/*
 * Main function for MPLSoGRE ip tunnel encapsulation with IPv4 forwarding on Jericho 2 only
 * The function implements MPLS over GRE IP tunnel encapsulation of IPv4oETH packet
 * Inputs: unit             - relevant unit;
 *         access_port      - incoming port;
 *         provider_port    - outgoing port;
 */
int
ip_tunnel_encap_mpls_o_gre_ipvx_fwd(
    int unit,
    int access_port,
    int provider_port)
{
    int rv = BCM_E_NONE;
    char *proc_name;
    proc_name = "ip_tunnel_encap_mpls_o_gre_ipvx_fwd";

    cint_ip_tunnel_basic_info.tunnel_ttl = 64;
    rv = ip_tunnel_encap_with_various_fwd(unit, access_port, provider_port, IPv4EncapsulationForwardTypeIPv4, IPv4EncapsulationMPLSoGRE);
    if (rv != BCM_E_NONE)
    {
        printf("Error, ip_tunnel_encap_with_various_fwd\n");
        return rv;
    }
    /* add host entry for ipv6 forwarding */
    int fec_id;
    BCM_L3_ITF_SET(&fec_id, BCM_L3_ITF_TYPE_FEC, cint_ip_tunnel_basic_info.tunnel_fec_id);
    rv = add_host_ipv6(unit, cint_ip_tunnel_basic_info.ipv6_dip, cint_ip_tunnel_basic_info.access_vrf, fec_id);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, add_host_ipv6 failed to execute! \n", proc_name);
        return rv;
    }

    return rv;
}

/*
 * Main function for UDP ip tunnel encapsulation with MPLS forwarding on Jericho 2 only
 * The function implements UDP IP tunnel encapsulation of IPv4oMPLSoETH packet
 * Inputs: unit             - relevant unit;
 *         access_port      - incoming port;
 *         provider_port    - outgoing port;
 */
int
ip_tunnel_encap_udp_mpls_fwd(
    int unit,
    int access_port,
    int provider_port)
{
    int rv;
    cint_ip_tunnel_basic_info.tunnel_type = bcmTunnelTypeUdp;
    rv = ip_tunnel_encap_with_various_fwd(unit, access_port, provider_port, IPv4EncapsulationForwardTypeMPLS, IPv4EncapsulationGRE4);
    if (rv != BCM_E_NONE)
    {
        printf("Error, ip_tunnel_encap_with_various_fwd\n");
        return rv;
    }
    return rv;
}

/*
 * Main function for GRE8 ip tunnel encapsulation with IPv4 forwarding on Jericho 2 only
 * The function implements GRE8 IP tunnel encapsulation of IPv4oETH packet
 * Inputs: unit             - relevant unit;
 *         access_port      - incoming port;
 *         provider_port    - outgoing port;
 */
int
ip_tunnel_encap_gre8_ipvx_fwd(
    int unit,
    int access_port,
    int provider_port)
{
    int rv = BCM_E_NONE;
    char *proc_name;
    proc_name = "ip_tunnel_encap_gre8_ipvx_fwd";

    cint_ip_tunnel_basic_info.tunnel_intf = cint_ip_tunnel_basic_info.gre_tunnel_outlif;

    rv = ip_tunnel_encap_with_various_fwd(unit, access_port, provider_port, IPv4EncapsulationForwardTypeIPv4, IPv4EncapsulationGRE8);
    if (rv != BCM_E_NONE)
    {
        printf("Error, ip_tunnel_encap_with_various_fwd\n");
        return rv;
    }
    /* add host entry for ipv6 forwarding */
    int fec_id;
    BCM_L3_ITF_SET(&fec_id, BCM_L3_ITF_TYPE_FEC, cint_ip_tunnel_basic_info.tunnel_fec_id);
    rv = add_host_ipv6(unit, cint_ip_tunnel_basic_info.ipv6_dip, cint_ip_tunnel_basic_info.access_vrf, fec_id);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, add_host_ipv6 failed to execute! \n", proc_name);
        return rv;
    }

    return rv;
}

/*
 * Main function for GRE8 ip tunnel encapsulation with MPLS forwarding on Jericho 2 only
 * The function implements GRE8 IP tunnel encapsulation of MPLSoETH packet
 * Inputs: unit             - relevant unit;
 *         access_port      - incoming port;
 *         provider_port    - outgoing port;
 */
int
ip_tunnel_encap_gre8_mpls_fwd(
    int unit,
    int access_port,
    int provider_port)
{
    int rv = BCM_E_NONE;
    rv = ip_tunnel_encap_with_various_fwd(unit, access_port, provider_port, IPv4EncapsulationForwardTypeMPLS, IPv4EncapsulationGRE8);
    if (rv != BCM_E_NONE)
    {
        printf("Error, ip_tunnel_encap_with_various_fwd\n");
        return rv;
    }
    return rv;
}

int
ip_tunnel_encap_vxlan_gpe_ipv4_fwd(
    int unit,
    int access_port,
    int provider_port)
{
    int rv = BCM_E_NONE;

    cint_ip_tunnel_basic_info.tunnel_type = bcmTunnelTypeVxlanGpe;

    rv = ip_tunnel_encap_with_various_fwd(unit, access_port, provider_port, IPv4EncapsulationForwardTypeIPv4, IPv4EncapsulationGRE4);
    if (rv != BCM_E_NONE)
    {
        printf("Error, ip_tunnel_encap_with_various_fwd\n");
        return rv;
    }

    rv = vxlan_network_domain_management_l3_egress(unit);
    if (rv != BCM_E_NONE)
    {
        printf("Error, bcm_vxlan_network_domain_config_add \n");
        return rv;
    }

    return rv;
}

int
ip_tunnel_encap_geneve_ipv4_fwd(
    int unit,
    int access_port,
    int provider_port)
{
    int rv = BCM_E_NONE;

    cint_ip_tunnel_basic_info.tunnel_type = bcmTunnelTypeGeneve;

    rv = ip_tunnel_encap_with_various_fwd(unit, access_port, provider_port, IPv4EncapsulationForwardTypeIPv4, IPv4EncapsulationGRE4);
    if (rv != BCM_E_NONE)
    {
        printf("Error, ip_tunnel_encap_with_various_fwd\n");
        return rv;
    }

    rv = vxlan_network_domain_management_l3_egress(unit);
    if (rv != BCM_E_NONE)
    {
        printf("Error, bcm_vxlan_network_domain_config_add \n");
        return rv;
    }

    return rv;
}


/*
 * Main function for Geneve IP tunnel encapsulation with IPv4/IPv6/MPLS forwarding on Jericho 2
 * The function implements GENEVEoUDPoIPv4 tunnel encapsulation of IPvXoETH packet or MPLSoETH
 * Inputs: unit          - relevant unit;
 *         access_port   - incoming port;
 *         provider_port - outgoing port;
 */
int
ip_tunnel_geneve_encap_with_various_fwd(
    int unit,
    int access_port,
    int provider_port,
    int forward_type)
{
    int rv = BCM_E_NONE;

    cint_ip_tunnel_basic_info.tunnel_type = bcmTunnelTypeGeneve;

    rv = ip_tunnel_encap_with_various_fwd(unit, access_port, provider_port, forward_type, 0);
    if (rv != BCM_E_NONE)
    {
        printf("Error, ip_tunnel_encap_with_various_fwd\n");
        return rv;
    }

    rv = vxlan_network_domain_management_l3_egress(unit);
    if (rv != BCM_E_NONE)
    {
        printf("Error, bcm_vxlan_network_domain_config_add \n");
        return rv;
    }

    return rv;
}


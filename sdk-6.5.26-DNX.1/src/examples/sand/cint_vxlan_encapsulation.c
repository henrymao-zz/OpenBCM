/*
 * 
 This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 
 Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
/*
 * The cint tested with Device JR2/Q2A using SDK 6.5.25
 * Feature label : FL-Vxlan
 * SOC properties : Use default BRCM SOC properties 
 *
 * This cint example will do the following :
 * 
 * Tunnel encapsulation of VXLANoUDPoIPv4oETH0 tunnel headers.
 * 1. VTT1 lookup covered - {In-PP-Port.Default-Lif}.
 * 2. FWD lookup - {VSI, MAC DA}.
 * The result
 * 1: Expect VSI to be resolved from AC-Lif.forwarding-domain (VSI) after VTT1.
 * 2: Expect the FWD lookup to succeed and the result to be a FEC.
 * 3: Expect the FEC to be resolved as Tunnel OutLif, Destination port.
 * 4: Expect the outgoing packet of the egress pipeline to be ETHoVXLANoUDPoIPv4oETH.
 *
 * How to execute the cint :
 * from the BCM shell ($SDK/systems/linux/user/slk_be) use the following steps :
 * cint ../../../../src/examples/sand/utility/cint_sand_utils_global.c
 * cint ../../../../src/examples/sand/cint_sand_advanced_vlan_translation_mode.c
 * cint ../../../../src/examples/dpp/cint_advanced_vlan_translation_mode.c
 * cint ../../../../src/examples/sand/cint_ip_route_basic.c
 * cint ../../../../src/examples/sand/utility/cint_sand_utils_multicast.c
 * cint ../../../../src/examples/sand/utility/cint_sand_utils_vxlan.c
 * cint ../../../../src/examples/sand/cint_vxlan_encapsulation.c
 * cint
 * int unit = 0;
 * int core_port = 200;
 * int virtual_machine_port = 201;
 * print vxlan_eth_encapsulation(unit,core_port,virtual_machine_port);
 *
 * Packet to send:ETH1
 * Tx = PORT:201
 *    =>   ETH DATA <= 
 *   dst_mac => 00:00:00:00:00:F1
 *   src_mac => 00:00:12:34:56:78
 *   tpid    => 0x8100
 *   prio    => 0
 *   cfi     => 0
 *   vid     => 15
 *   ether type   => 0xffff (ethII)
 *   L2 PayLoad   =>  
 *     0000:: 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07   0x08 0x09 0x0a 0x0b 0x0c 0x0d 0x0e 0x0f 
 *     0016:: 0x10 0x11 0x12 0x13 0x14 0x15 0x16 0x17   0x18 0x19 0x1a 0x1b 0x1c 0x1d 0x1e 0x1f 
 *     0032:: 0x20 
 *
 *  Use the following command from shell to send the packet :
 *  tx 1 PSRC=201 DATA=0x0000000000f10000123456788100000fffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 *  
 *   Packet received :  ETH1oVXLANoUDPoIPV4oETH1
 *   Rx = 1 PORT:200
 *    ETH1             DA=0x00000000CD1D SA=0x000C00020000 TPID=0x8100 PCP=0x5 DEI=0x0 VID=0x064 ETHERTYPE=0x0800 
 *    IPV4             VERSION=0x4 IHL=0x5 DSCP=0x02 ECN=0x2 LENGTH=0x0062 ID=0x0000 RESERVED1=0x0 DF=0x0 MF=0x0 
 *                     FO=0x0000 TTL=0x40 PROTOCOL=0x11 CHECKSUM=0x2F6F SIP=0xA0000001 DIP=0xAB000011 
 *    UDP              SRC_PORT=0xAE4B DST_PORT=0x12B5 LENGTH=0x004E CHECKSUM=0x0000 
 *    VXLAN            RESERVED1=0x0 VERSION=0x0 VNI_FLAG=0x1 NEXT_PROTOCOL_FLAG=0x0 BUM_FLAG=0x0 OAM_FLAG=0x0 
 *                     RESERVED2=0x0000 NEXT_PROTOCOL=0x00 VNI=0x001388 RESERVED3=0x00 
 *    ETH1             DA=0x0000000000F1 SA=0x000012345678 TPID=0x8100 PCP=0x0 DEI=0x0 VID=0x00F ETHERTYPE=0xFFFF 
 *
 *  Debug commands to use :
 * 
 *  BCM.0> diag pp fdt
 * 
 *  BCM.0> pp vis ekleap
 * 
 *  BCM.0> pp info fec
 * 
 *  For JR Devices :
 *
 *  SOC properties :
 *  bcm886xx_ip4_tunnel_termination_mode=0
 *  bcm886xx_vxlan_enable=1
 *  The same sequence above .
 *
 *  Debug commands to use :
 *
 *  BCM.0> diag pp fdt
 *
 *  BCM.0> diag pp last
 *
 *  BCM.0> diag pp encap
 *
 * For Jericho2 only: example ETPP stat pp per VNI 
 *
 * cint ../../../../src/examples/sand/utility/cint_sand_utils_global.c
 * cint ../../../../src/examples/sand/cint_sand_advanced_vlan_translation_mode.c
 * cint ../../../../src/examples/sand/cint_ip_route_basic.c
 * cint ../../../../src/examples/sand/utility/cint_sand_utils_vxlan.c
 * cint ../../../../src/examples/sand/utility/cint_sand_utils_multicast.c
 * cint ../../../../src/examples/sand/cint_vxlan_encapsulation.c
 * cint ../../../../src/examples/dnx/stat_pp/cint_stat_pp_config.c
 * cint ../../../../src/examples/dnx/stat_pp/cint_stat_pp_ip_tunnel.c
 * cint ../../../../src/examples/dnx/crps/cint_crps_wrapper.c
 * cint ../../../../src/examples/dnx/crps/cint_crps_db_utils.c
 * cint ../../../../src/examples/dnx/crps/cint_crps_etpp_config.c
 * cint
 * cint_vxlan_basic_info.vpn_vni_is_mapped=0;
 * int unit = 0; 
 * print vxlan_eth_encapsulation(unit,201,202);
 * // Configure ETPP CRPS database/engine,create pp profile
 * print cint_stat_pp_config_main(unit,ipv4_tunnel_outlif_statistics_properties,bcmStatCounterInterfaceEgressTransmitPp,0,BCM_CORE_ALL,0);
 * // copy stat pp info to cint global var
 * cint_vxlan_basic_info.stat_pp_per_vni.stat_id = ipv4_tunnel_outlif_statistics_properties.stat_id;
 * cint_vxlan_basic_info.stat_pp_per_vni.stat_pp_profile = ipv4_tunnel_outlif_statistics_properties.pp_profile;
 * // configure ETPP stat pp per VNI
 * print vxlan_encapsulation_vpn_to_vni_configuration(unit); 
 * exit;
 * 
 * //ETH1 packet into VXLAN tunnel 
 * tx 1 psrc=202 data=0x0000000000f10000123456788100000fffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * 
 * print crps_stats_array_set(0,0,0,0,1);
 * print crps_database_stat_counter_get(0,0,0,1,0,1,1);
 * verify that the function _get return no ERROR.
 * 
 * print crps_database_enable_wrapper(0,0,1,BCM_CORE_ALL,0,0);
 * print crps_database_destroy_wrapper(0,BCM_CORE_ALL,1);
 * ipv4_tunnel_outlif_statistics_properties.expansion_flag=EXPANSION_TYPE_META_DATA_FULL_4_BITS;
 * print cint_stat_pp_config_crps(0, ipv4_tunnel_outlif_statistics_properties, bcmStatCounterInterfaceEgressTransmitPp, BCM_CORE_ALL);
 * bcm_stat_pp_metadata_info_t metadata_info;
 * metadata_info.flags = BCM_STAT_PP_METADATA_EGRESS | BCM_STAT_PP_METADATA_TUNNEL;
 * metadata_info.header_type = bcmStatPpMetadataHeaderTypeEth;
 * metadata_info.metadata = 5;
 * print bcm_stat_pp_metadata_set(0,&metadata_info);
 *
 * //Send the pkt again, verify crps - 1 packet on IPv4 vxlan tunnel outlif with metadata
 * //ETH1 packet into VXLAN tunnel 
 * tx 1 psrc=202 data=0x0000000000f10000123456788100000fffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * 
 * print crps_stats_array_set(0,0,0,5,1);
 * print crps_database_stat_counter_get(0,0,0,1,0,1,1);
 * verify that the function _get return no ERROR.
 */


struct cint_vxlan_stat_pp_info_s {
    uint32 stat_id; /* Object statistic ID */
    int stat_pp_profile; /* Statistics profile */
};

/*
 * VXLAN global structure
 */
struct cint_vxlan_basic_info_s {
    int vpn_id;                     /* VPN ID */
    int vni;                        /* VNID of the VXLAN */
    int vxlan_network_group_id;     /* ingress and egress orientation for VXLAN */
    int virtual_vlan;               /* Virtual machine VID */
    int core_vlan;                  /* Outer ETH header VID */
    bcm_mac_t dmac_in;              /* DA of in ETH packet*/
    int eth_rif_intf_core;          /* Core RIF */
    int eth_rif_core_vrf;           /* VRF - a router instance for the tunnels's DIP */
    int eth_rif_vm_vrf;             /* VRF after termination,resolved as Tunnel-InLif property */
    bcm_mac_t intf_core_mac_addr;   /* mac for next hop */
    bcm_mac_t tunnel_next_hop_mac;  /* tunnel next hop MAC DA */
    bcm_ip_t tunnel_dip;            /* tunnel DIP */
    bcm_ip_t tunnel_dip_mask;       /* tunnel DIP mask */
    bcm_ip_t tunnel_sip;            /* tunnel SIP */
    bcm_ip_t tunnel_sip_mask;       /* tunnel SIP mask*/
    int tunnel_arp_id;              /* Id for ARP entry */
    int tunnel_fec_id;              /* FEC id */
    bcm_gport_t tunnel_id;          /* Tunnel ID */
    bcm_ip_t route_dip;             /* Route DIP */
    uint32 route_dip_mask;          /* mask for route DIP */
    int is_native_vlan_editing;     /* indicate if we want to perform native vlan editing for vxlan encapsulation */
    bcm_gport_t vxlan_port_id;      /* vxlan gport */
    int svtag_enable;               /* enable an SVTAG lookup */
    int l3_intf;                    /* l3 interface */
    int vpn_vni_is_mapped;        /* indicate if the vpn <-> vni is to be configured in bcm_vxlan_vpn_create, if false need to be configured separately */
    cint_vxlan_stat_pp_info_s stat_pp_per_vni; /* JER2 only: stat pp information per VNI */
    int double_udp;
};

cint_vxlan_basic_info_s cint_vxlan_basic_info = 
{
    /*
     * vpn_id | vni
     */
       15,      5000,
    /*
     * vxlan_network_group_id
     */
       1,
    /*
     * virtual_vlan | core_vlan
     */
       510,      100,
    /*
     * dmac_in
     */
       {0x00, 0x00, 0x00, 0x00, 0x00, 0xf1},
    /* 
     * eth_rif_intf_core
     */
       15,
    /*
     * eth_rif_core_vrf | eth_rif_vm_vrf
     */
       1,                 5,
    /*
     * intf_core_mac_addr
     */
       {0x00, 0x0c, 0x00, 0x02, 0x00, 0x00},
    /*
     * tunnel_next_hop_mac
     */
       {0x00, 0x00, 0x00, 0x00, 0xcd, 0x1d},
    /*
     * tunnel_dip = 171.0.0.17 | tunnel_dip_mask
     */
       0xAB000011,               0xffffffff,
    /*
     * tunnel_sip = 160.0.0.1 | tunnel_sip_mask
     */
       0xA0000001,              0xffffffff,
    /*
     * tunnel_arp_id | tunnel_fec_id | tunnel_id
     */
       9000,           5000,          0,
    /*
     * route_dip
     */
       0x7fffff03, /* 127.255.255.03 */
    /*
     * route_dip_mask
     */
       0xfffffff0, 
    /* 
     * is_native_vlan_editing
     */
       0, 
    /*
     * vxlan port id
     */
       0,
    /*
     * svtag_enable
     */
       0,
     /*
     * l3 interface
     */
       0,
     /*
      * vpn_vni_is_mapped
      */
       1,
     /* stat pp per vni */
     /* Object statistic ID , Statistics profile */
       {0,                      0},
     /*
      * double_udp
      */
       0
};

/*
 * Copy parameter structure into local one
 */
void vxlan_struct_get(cint_vxlan_basic_info_s *param)
{
    sal_memcpy(param, &cint_vxlan_basic_info, sizeof(cint_vxlan_basic_info));
}

int set_is_native_vlan_editing(int is_native_vlan_editing) {
    cint_vxlan_basic_info.is_native_vlan_editing = is_native_vlan_editing; 
    return 0; 
}

/*
 * The basic VXLAN example with parameters:
 *     Unit - relevant unit
 *     core_port - port where core routers and aggregation switches are connected.
 *     vm_port - port where virtual machines are connected.
 */
int vxlan_eth_encapsulation(
    int unit,
    int core_port,
    int vm_port)
{
    char *proc_name;
    int rv = BCM_E_NONE;
    int device_is_jericho2;
    int device_is_qux;
    bcm_if_t tunnel_out_rif_intf;
    bcm_gport_t tunnel_id;
    bcm_if_t l3egid;
    bcm_l2_addr_t l2addr2;

    proc_name = "vxlan_eth_encapsulation";

    rv = is_device_jericho2(unit, &device_is_jericho2);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, is_device_jericho2\n", proc_name);
        return rv;
    }

    rv = is_qux_only(unit, &device_is_qux);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, is_qux_only\n", proc_name);
        return rv;
    }

    /** Init L2 VXLAN module for JER1 */
    if(!device_is_jericho2)
    {
        rv = bcm_vxlan_init(unit);
        if (rv != BCM_E_NONE)
        {
            printf("%s(): Error, bcm_switch_control_set\n", proc_name);
            return rv;
        }
        cint_vxlan_basic_info.tunnel_fec_id = 40961;
        if (device_is_qux)
        {
            /* FEC range on QUX is 24K */
            cint_vxlan_basic_info.tunnel_fec_id = 20481;
        }
    }
    else
    {
        rv = get_first_fec_in_range_which_not_in_ecmp_range(unit, 0, &cint_vxlan_basic_info.tunnel_fec_id);
        if (rv != BCM_E_NONE)
        {
            printf("Error, get_first_fec_in_range_which_not_in_ecmp_range\n");
            return rv;
        }
    }

    /** Build L2 VPN */
    rv = vxlan_open_vpn(unit, cint_vxlan_basic_info.vpn_id, cint_vxlan_basic_info.vni);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, vxlan_open_vpn, vpn=%d, \n", proc_name, cint_vxlan_basic_info.vpn_id);
        return rv;
    }


    /** j2 only: configure entry: VNI+AC */
    if (device_is_jericho2 && cint_vxlan_basic_info.is_native_vlan_editing) {
        /* At ESEM for vsi, netork_domain -> VNI, AC information
           create a virtual AC which represent the AC information in ESEM entry.
           The virtual AC save the key to access the ESEM entry. 
           In this case: vsi, network domain
           */
        bcm_vlan_port_t vlan_port; 
        bcm_vlan_port_t_init(&vlan_port); 
        vlan_port.vsi = cint_vxlan_basic_info.vpn_id; /* vsi, part of the key in ESEM lookup */
        vlan_port.match_class_id = 0; /* network domain, part of the key in ESEM lookup */
        vlan_port.criteria = BCM_VLAN_PORT_MATCH_NAMESPACE_VSI; 
        vlan_port.flags = BCM_VLAN_PORT_CREATE_EGRESS_ONLY | BCM_VLAN_PORT_VLAN_TRANSLATION; 
        vlan_port.egress_network_group_id = 1; 
        printf("right before vni + ac bcm_dnx_vlan_port_create \n"); 
        rv = bcm_vlan_port_create(unit, vlan_port); 
        if (rv != BCM_E_NONE)
        {
            printf("%s(): Error, bcm_vlan_port_create \n", proc_name);
            return rv;
        }

        /* 
           vlan port translation set
           */
        int vlan_edit_profile = 3; 
        bcm_vlan_port_translation_t vlan_port_translation; 
        bcm_vlan_port_translation_t_init(&vlan_port_translation); 
        vlan_port_translation.flags = BCM_VLAN_ACTION_SET_EGRESS; 
        vlan_port_translation.gport = vlan_port.vlan_port_id; 
        vlan_port_translation.new_outer_vlan = 12; 
        vlan_port_translation.new_inner_vlan = 0; 
        vlan_port_translation.vlan_edit_class_id = vlan_edit_profile; 
        rv = bcm_vlan_port_translation_set(unit, &vlan_port_translation); 
        if (rv != BCM_E_NONE)
        {
            printf("%s(): Error, bcm_vlan_port_translation_set \n", proc_name);
            return rv;
        }
        /*
         * Create action ID
         */
        int action_id; 
        rv = bcm_vlan_translate_action_id_create(unit, BCM_VLAN_ACTION_SET_EGRESS, &action_id);
        if (rv != BCM_E_NONE)
        {
            printf("Error, bcm_vlan_translate_action_id_create\n");
            return rv;
        }
        /*
         * Set translation action
         */
        bcm_vlan_action_set_t action;
        bcm_vlan_action_set_t_init(&action);
        action.outer_tpid = 0x8100;
        action.inner_tpid = 0x8100;
        action.dt_outer = bcmVlanActionNone;
        action.dt_inner = bcmVlanActionNone;
        rv = bcm_vlan_translate_action_id_set(unit,
                                              BCM_VLAN_ACTION_SET_EGRESS,
                                              action_id, &action);
        if (rv != BCM_E_NONE)
        {
            printf("Error, bcm_vlan_translate_action_id_set\n");
            return rv;
        }
        /*
         * Set translation action class (map edit_profile & tag_format to action_id)
         */
        int tag_format_ctag = 8;
        bcm_vlan_translate_action_class_t action_class;
        bcm_vlan_translate_action_class_t_init(&action_class);
        action_class.vlan_edit_class_id = vlan_edit_profile;
        action_class.tag_format_class_id = tag_format_ctag;
        action_class.vlan_translation_action_id = action_id;
        action_class.flags = BCM_VLAN_ACTION_SET_EGRESS;
        rv = bcm_vlan_translate_action_class_set(unit, &action_class);
        if (rv != BCM_E_NONE)
        {
            printf("Error, bcm_vlan_translate_action_class_set\n");
            return rv;
        }
    }


    /** Initialize ports, LIFs, Eth-RIFs etc */
    rv = vxlan_encapsulation_open_route_interfaces(unit, core_port, vm_port, proc_name);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, vxlan_encapsulation_open_route_interfaces\n", proc_name);
        return rv;
    }

    /** Build tunnel terminations and router interfaces*/
    rv = tunnel_terminator_create(unit, &tunnel_id);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, tunnel_terminator_create\n", proc_name);
        return rv;
    }

    /** Create the tunnel initiator */
    rv = tunnel_initiator_create(unit, cint_vxlan_basic_info.tunnel_arp_id, &tunnel_out_rif_intf);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, tunnel_initiator_configure\n", proc_name);
        return rv;
    }

    /** Create FEC and configure its: Outlif, Destination port, Global Out-EthRIF */
    rv = l3__egress_only_fec__create(unit, cint_vxlan_basic_info.tunnel_fec_id, tunnel_out_rif_intf,
                                     0, core_port, 0);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, l3__egress_only_fec__create fec_id=0x%x\n", proc_name,
               cint_vxlan_basic_info.tunnel_fec_id);
        return rv;
    }
    printf("vxlan tunnel fec_id: 0x%x\n", cint_vxlan_basic_info.tunnel_fec_id);

    /* update tunnel init orientation.
     * It's not done by vxlan_port_add since we configure it with tunnel term lif and FEC */
    rv = bcm_port_class_set(unit, cint_vxlan_basic_info.tunnel_id, bcmPortClassForwardEgress, cint_vxlan_basic_info.vxlan_network_group_id);
    {
        printf("%s(): Error, create in update orientation for tunnel outlif \n", proc_name);
    }
    /** Initialize ports: VXLAN/VLAN/VSWITCH/TPID */
    rv = vxlan_ports_add(unit, core_port, vm_port, tunnel_id, &cint_vxlan_basic_info.vxlan_port_id, proc_name);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, vxlan_ports_add\n", proc_name);
        return rv;
    }

    /** Create an MACT entry for VXLAN tunnel, mapped to the VPN */
    rv = vxlan_l2_addr_add(unit, cint_vxlan_basic_info.vxlan_port_id);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, vxlan_l2_addr_add\n", proc_name);
        return rv;
    }

    return rv;
}

/*
 * LIFs Initialization
 * The function ip_tunnel_encapsulation_open_route_interfaces serves as a configuration template to
 * more advanced tests
 * Inputs: unit - relevant unit;
 *         access_port - incoming port;
 *         provider_port - outgoing port;
 *         *proc_name - main function name;
 */
int
vxlan_encapsulation_open_route_interfaces(
    int  unit,
    int  access_port,
    int  provider_port,
    char *proc_name)
{
    int rv = BCM_E_NONE;
    int device_is_jericho2;

    rv = is_device_jericho2(unit, &device_is_jericho2);

    if(device_is_jericho2)
    {
        cint_vxlan_basic_info.tunnel_arp_id = 5050;
        rv = get_first_fec_in_range_which_not_in_ecmp_range(unit, 0, &cint_vxlan_basic_info.tunnel_fec_id);
        if (rv != BCM_E_NONE)
        {
            printf("Error, get_first_fec_in_range_which_not_in_ecmp_range\n");
            return rv;
        }
    }

    /** Configure ingress interfaces */
    rv = vxlan_encapsulation_open_route_interfaces_access(unit, access_port, proc_name);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, vxlan_encapsulation_open_route_interfaces_access\n", proc_name);
        return rv;
    }

    /** Configure egress interfaces */
    rv = vxlan_encapsulation_open_route_interfaces_provider(unit, provider_port, proc_name);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, vxlan_encapsulation_open_route_interfaces_provider\n", proc_name);
        return rv;
    }

    /** Create ARP entry for VXLAN tunnel and set ARP properties. */
    rv = l3__egress_only_encap__create(unit, BCM_L3_EGRESS_ONLY,
                                       &(cint_vxlan_basic_info.tunnel_arp_id),
                                       cint_vxlan_basic_info.tunnel_next_hop_mac,
                                       cint_vxlan_basic_info.core_vlan);
    if(rv != BCM_E_NONE)
    {
        printf("%s(): Error, l3_egress_only_encap__create\n", proc_name);
        return rv;
    }

    return rv;
}

/*
 * Configure Ingress interfaces
 * Inputs: core_port - incomming port;
 *         *proc_name - main function name;
 */
int vxlan_encapsulation_open_route_interfaces_access(
    int  unit,
    int  core_port,
    char *proc_name)
{
    int rv = BCM_E_NONE;
    int device_is_jericho2;
    l3_ingress_intf ingr_itf;

    rv = is_device_jericho2(unit, &device_is_jericho2);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, is_device_jericho2\n", proc_name);
        return rv;
    }

    /** Set In-Port to In ETh-RIF - for incoming port, we configure default VSI. */
    if (device_is_jericho2)
    {
        rv = in_port_intf_set(unit, core_port, cint_vxlan_basic_info.eth_rif_intf_core);
        if (rv != BCM_E_NONE)
        {
            printf("%s(): Error, in_port_intf_set intf_in\n", proc_name);
            return rv;
        }
    }

    /*
     * Create Routing interface for the tunnel's DIP. 
     * We use it as ingress ETH-RIF to perform LL termination (my-mac procedure),
     * to enable the IPv4 routing for this ETH-RIF and to set the VRF.
     */
    rv = intf_eth_rif_create(unit, cint_vxlan_basic_info.eth_rif_intf_core,
                             cint_vxlan_basic_info.intf_core_mac_addr);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, intf_eth_rif_create eth_rif_intf_core \n", proc_name);
        return rv;
    }

    /** Needed only for JER1 */
    if(!device_is_jericho2)
    {
        int tunnel_if = 20; /* The RIF property of the InLif used only for JR1 */
        
        /** Create ingress Tunnel interface. */
        rv = intf_eth_rif_create(unit,tunnel_if, cint_vxlan_basic_info.intf_core_mac_addr);
        if (rv != BCM_E_NONE)
        {
            printf("%s(): Error, intf_eth_rif_create tunnel_if 2 \n", proc_name);
            return rv;
        }
    }

    return rv;
}

/*
 * Configure Egress interfaces
 * Inputs: vm_port - outgoing port;
 *         *proc_name - main function name;
 */
int
vxlan_encapsulation_open_route_interfaces_provider(
    int  unit,
    int  vm_port,
    char *proc_name)
{
    int rv = BCM_E_NONE;

    /** Set Out-Port default properties */
    rv = out_port_set(unit, vm_port);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, out_port_set vm_port \n", proc_name);
        return rv;
    }

    /** Set In-Port to In ETh-RIF - for incoming port, we configure default VSI. */
    if (is_device_or_above(unit, JERICHO2))
    {
        rv = in_port_intf_set(unit, vm_port, cint_vxlan_basic_info.eth_rif_intf_core);
        if (rv != BCM_E_NONE)
        {
            printf("%s(): Error, in_port_intf_set intf_in\n", proc_name);
            return rv;
        }
    }

    /* configure SA for ETH-RIF configured in tunnel's arp */
    rv = intf_eth_rif_create(unit, cint_vxlan_basic_info.core_vlan,
                             cint_vxlan_basic_info.intf_core_mac_addr);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, intf_eth_rif_create eth_rif_intf_core \n", proc_name);
        return rv;
    }

    return rv;
}

/*
 * Create and configure a VXLAN VPN
 */
int vxlan_open_vpn(
    int unit,
    int vpn,
    int vni)
{
    int rv = BCM_E_NONE;
    int device_is_jericho2;
    char *proc_name;
    int flags;

    proc_name = "vxlan_open_vpn";
    rv = is_device_jericho2(unit, &device_is_jericho2);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, is_device_jericho2 \n", proc_name);
        return rv;
    }

    if(!device_is_jericho2)
    {
        rv = multicast__open_mc_group(unit, &vpn, BCM_MULTICAST_TYPE_L2);
        if (rv != BCM_E_NONE)
        {
            printf("%s(): Error, multicast__open_mc_group\n", proc_name);
            return rv;
        }
    }

    bcm_vxlan_vpn_config_t vpn_config;
    bcm_vxlan_vpn_config_t_init(&vpn_config);
    vpn_config.flags = BCM_VXLAN_VPN_WITH_ID|BCM_VXLAN_VPN_WITH_VPNID;
    vpn_config.vpn = vpn;
    vpn_config.broadcast_group = vpn;
    vpn_config.unknown_unicast_group = vpn;
    vpn_config.unknown_multicast_group = vpn;
    if (cint_vxlan_basic_info.vpn_vni_is_mapped) {
        vpn_config.vnid = vni;
    }
    else {
        vpn_config.vnid = BCM_VXLAN_VNI_INVALID;
    }
    rv = bcm_vxlan_vpn_create(unit,&vpn_config);
    if(rv != BCM_E_NONE)
    {
        printf("%s(): error in bcm_vxlan_vpn_create \n", proc_name);
        return rv;
    }

    return rv;
}


/* precondition:
 * vxlan_open_vpn has been called with BCM_VXLAN_VNI_INVALID
 * */
int vxlan_encapsulation_vpn_to_vni_configuration(int unit)
{
    int rv = BCM_E_NONE;
    bcm_vxlan_network_domain_config_t config;
    config.stat_id = cint_vxlan_basic_info.stat_pp_per_vni.stat_id; /* Object statistic ID */
    config.stat_pp_profile = cint_vxlan_basic_info.stat_pp_per_vni.stat_pp_profile; /* Statistics profile */
    config.vsi = cint_vxlan_basic_info.vpn_id;
    config.vni = cint_vxlan_basic_info.vni;
    config.network_domain = 0;
    config.flags = BCM_VXLAN_NETWORK_DOMAIN_CONFIG_EGRESS_ONLY | BCM_VXLAN_NETWORK_DOMAIN_CONFIG_L2_MAPPING;
    rv = bcm_vxlan_network_domain_config_add(unit, &config);
    if(rv != BCM_E_NONE)
    {
        printf("Error in bcm_dnx_vxlan_network_domain_config_add \n");
        return rv;
    }
    return rv;
}

/*
 * Create and configure VXLAN tunnel termination
 */
int tunnel_terminator_create(
    int unit,
    bcm_gport_t *tunnel_id)
{
    int rv = BCM_E_NONE;
    int device_is_jericho2;
    bcm_tunnel_terminator_t tunnel_term;

    rv = is_device_jericho2(unit, &device_is_jericho2);
    if (rv != BCM_E_NONE)
    {
        printf("Error, is_device_jericho2 device_is_jericho2 \n");
        return rv;
    }

    /** Create the tunnel termination lookup and the tunnel termination In-Lif */
    bcm_tunnel_terminator_t_init(&tunnel_term);
    tunnel_term.dip      = cint_vxlan_basic_info.tunnel_dip;       /* default: 171.0.0.17 */
    tunnel_term.dip_mask = cint_vxlan_basic_info.tunnel_dip_mask;  /* default: 255.255.255.255 */
    tunnel_term.sip      = cint_vxlan_basic_info.tunnel_sip;       /* default: 160.0.0.1 */
    tunnel_term.sip_mask = cint_vxlan_basic_info.tunnel_sip_mask;  /* default: 255.255.255.255 */
    tunnel_term.vrf      = cint_vxlan_basic_info.eth_rif_core_vrf; /* default: 1 */
    tunnel_term.type     = bcmTunnelTypeVxlan;

    /** We configure tunnel_id only for JR1 and older devices - JR2 doesn't support "WITH_ID" flag*/
    if(!device_is_jericho2)
    {
        tunnel_term.tunnel_id = 0xf;
    }

    rv = bcm_tunnel_terminator_create(unit, &tunnel_term);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, bcm_tunnel_terminator_create, \n", proc_name);
        return rv;
    }

    *tunnel_id = tunnel_term.tunnel_id;

    printf("tunnel term tunnel id: 0x%x\n", tunnel_term.tunnel_id);

    return rv;
}

/*
 * Create and configure VXLAN tunnel encapsulation
 */
int tunnel_initiator_create(
    int unit,
    bcm_if_t arp_itf,
    bcm_if_t *itf)
{
    int rv;
    int device_is_jericho2;
    bcm_tunnel_initiator_t tunnel_init;
    bcm_l3_intf_t l3_intf;

    rv = is_device_jericho2(unit, &device_is_jericho2);
    if (rv != BCM_E_NONE)
    {
        printf("Error, is_device_jericho2 device_is_jericho2 \n");
        return rv;
    }

    bcm_l3_intf_t_init(&l3_intf);

    /* Create IP tunnel initiator for encapsulating GRE4oIPv4 tunnel header*/
    bcm_tunnel_initiator_t_init(&tunnel_init);
    tunnel_init.dip = cint_vxlan_basic_info.tunnel_dip; /* default: 171.0.0.17 */
    tunnel_init.sip = cint_vxlan_basic_info.tunnel_sip; /* default: 160.0.0.1 */
    tunnel_init.flags = 0;
    tunnel_init.dscp = 10; /* default: 10 */
    tunnel_init.type = bcmTunnelTypeVxlan;
    tunnel_init.l3_intf_id = arp_itf;

    if (device_is_jericho2)
    {
        tunnel_init.flags |= BCM_TUNNEL_INIT_STAT_ENABLE;
        if(cint_vxlan_basic_info.svtag_enable)
        {
            tunnel_init.flags |= BCM_TUNNEL_INIT_SVTAG_ENABLE;
            if (cint_vxlan_basic_info.double_udp)
            {
                tunnel_init.flags |= BCM_TUNNEL_INIT_FIXED_UDP_SRC_PORT;
            }
        }
        tunnel_init.egress_qos_model.egress_qos = bcmQosEgressModelPipeNextNameSpace;
    }
    else
    {
        tunnel_init.dscp_sel = bcmTunnelDscpAssign;
        tunnel_init.vlan = cint_vxlan_basic_info.core_vlan; /* For JR2 the vlan is set at LL*/
    }
    tunnel_init.ttl = 64; /* default: 64 */
    tunnel_init.outlif_counting_profile = BCM_STAT_LIF_COUNTING_PROFILE_NONE; /* default: -1 */
    rv = bcm_tunnel_initiator_create(unit, &l3_intf, tunnel_init);

    if (rv != BCM_E_NONE)
    {
        printf("Error, bcm_tunnel_initiator_create \n");
        return rv;
    }

    *itf = l3_intf.l3a_intf_id;
    cint_vxlan_basic_info.l3_intf = l3_intf.l3a_intf_id;
    cint_vxlan_basic_info.tunnel_id = tunnel_init.tunnel_id;

    printf("tunnel encap tunnel id: 0x%x \n", cint_vxlan_basic_info.tunnel_id);
    printf("tunnel encap l3 itf: 0x%x \n", *itf);

    return rv;
}

/*
 * Ports Initialization
 * The function vxlan_ports_add configures VXLAN, VLAN and VSWITCH ports with the Out-Lif
 * Inputs: unit - relevant unit;
 *         core_port - physical port;
 *         vm_port - virtual machine port;
 *         tunnel_id - VXLAN tunnel id;
 *         *vxlan_port_id - VXLAN port id;
 *         *proc_name - main function name;
 */
int vxlan_ports_add(
    int unit,
    int core_port,
    int vm_port,
    bcm_gport_t tunnel_id,
    bcm_gport_t *vxlan_port_id,
    char* proc_name)
{
    int rv = BCM_E_NONE;
    int vxlan_port_flags = 0;
    int device_is_jericho2;
    vxlan_port_add_s vxlan_port_add;
    bcm_gport_t vlan_port_id;

    rv = is_device_jericho2(unit, &device_is_jericho2);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, is_device_jericho2\n", proc_name);
        return rv;
    }

    /* Add VXLAN port properties and configure tunnel terminator In-Lif and initiatior Out-Lif*/
    vxlan_port_s_clear(&vxlan_port_add);
    vxlan_port_add.vpn              = cint_vxlan_basic_info.vpn_id;
    vxlan_port_add.in_port          = core_port;
    vxlan_port_add.in_tunnel        = tunnel_id;
    vxlan_port_add.flags            = vxlan_port_flags;
    vxlan_port_add.network_group_id = cint_vxlan_basic_info.vxlan_network_group_id;
    vxlan_port_add.add_to_mc_group = 0;
    BCM_L3_ITF_SET(vxlan_port_add.egress_if, BCM_L3_ITF_TYPE_FEC, cint_vxlan_basic_info.tunnel_fec_id);

    printf("Before vxlan port add: update vxlan outlif\n");
    print vxlan_port_add;
    rv = vxlan__vxlan_port_add(unit, vxlan_port_add);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, vxlan__vxlan_port_add, in_gport=0x%08x\n", proc_name, tunnel_id);
        return rv;
    }

    *vxlan_port_id = vxlan_port_add.vxlan_port_id;

    if (!device_is_jericho2) {
        /** Configure the Outgoing port TPID properties. */
        port_tpid_init(vm_port, 1, 1);
        rv = port_tpid_set(unit);
        if (rv != BCM_E_NONE)
        {
            printf("%s(): Error, port_tpid_set \n", proc_name);
            return rv;
        }

        /* Configure the Incomming port TPID properties. */
        port_tpid_init(core_port, 1, 1);
        rv = port_tpid_set(unit);
        if (rv != BCM_E_NONE)
        {
            printf("%s(): Error, port_tpid_set \n", proc_name);
            return rv;
        }
    }

    rv = vlan_port_add(unit, vm_port, &vlan_port_id);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, vswitch_metro_add_port_1 2, in_intf=0x%08x\n", proc_name, vlan_port_id);
        return rv;
    }

    rv = bcm_vswitch_port_add(unit, cint_vxlan_basic_info.vpn_id, vlan_port_id);
    if (rv != BCM_E_NONE)
    {
        printf("%s(): Error, bcm_vswitch_port_add\n", proc_name);
        return rv;
    }

    return rv;
}

/*
 * Create and configure VLAN port
 */
int vlan_port_add(
    int unit,
    bcm_gport_t in_port,
    bcm_gport_t *port_id)
{
    int rv = BCM_E_NONE;
    bcm_vlan_port_t vlan_port;
    bcm_vlan_port_t_init(&vlan_port);

    /* the match criteria is port:1, out-vlan:510   */
    if (!is_device_or_above(unit, JERICHO2))
    {
        /* JR1 - criteria is PORT * VLAN */
        vlan_port.criteria = BCM_VLAN_PORT_MATCH_PORT_VLAN;
    }
    else
    {
        /* JR2 - criteria is PORT * C_VLAN */
        vlan_port.criteria = BCM_VLAN_PORT_MATCH_PORT_CVLAN;
    }
    vlan_port.port = in_port;
    vlan_port.match_vlan = cint_vxlan_basic_info.virtual_vlan;
    vlan_port.flags = 0;
    vlan_port.vsi = 0;

    rv = bcm_vlan_port_create(unit,&vlan_port);
    if (rv != BCM_E_NONE)
    {
        printf("Error, bcm_vlan_port_create\n");
        return rv;
    }

    /* handle of the created gport */
    *port_id = vlan_port.vlan_port_id;


    if (!is_device_or_above(unit, JERICHO2)) {  
        bcm_vlan_action_set_t action;
        /* In advanced vlan translation mode, the default ingress/ egress actions and mapping
               are not configured. This is here to compensate. */
        rv = vlan_translation_default_mode_init(unit);
        if (rv != BCM_E_NONE) {
            printf("Error, vlan_translation_default_mode_init\n");
            return rv;
        }

        if (advanced_vlan_translation_mode) { 
            int ing_tag_format = 2;
            int ing_vlan_action_id;
            int ing_vlan_edit_class_id = 4;
            bcm_vlan_port_translation_t port_trans;
            bcm_vlan_translate_action_class_t action_class;
        
            /* Map LIF -> vlan_edit_class_id */
            bcm_vlan_port_translation_t_init(&port_trans);
            port_trans.gport = vlan_port.vlan_port_id;
            port_trans.vlan_edit_class_id = ing_vlan_edit_class_id;
            port_trans.flags = BCM_VLAN_ACTION_SET_INGRESS;
            rv = bcm_vlan_port_translation_set(unit, &port_trans);
            if (rv != BCM_E_NONE) {
                printf("Error, bcm_vlan_port_translation_set ing $rv\n");
                return rv;
            }
            /* Create ingress vlan action id: ing_vlan_action_id */
            rv = bcm_vlan_translate_action_id_create(unit, BCM_VLAN_ACTION_SET_INGRESS, &ing_vlan_action_id);
            if (rv != BCM_E_NONE) {
                printf("Error, bcm_vlan_translate_action_id_create ing $rv\n");
                return rv;
            }
            /* Map <vlan_edit_class_id,  tag_format_class_id> -> ing_vlan_action_id */
            bcm_vlan_translate_action_class_t_init(&action_class);
            action_class.vlan_edit_class_id = ing_vlan_edit_class_id;
            action_class.tag_format_class_id = ing_tag_format;
            action_class.vlan_translation_action_id = ing_vlan_action_id;
            action_class.flags = BCM_VLAN_ACTION_SET_INGRESS;
            rv = bcm_vlan_translate_action_class_set( unit,  &action_class);
            if (rv != BCM_E_NONE) {
                printf("Error, bcm_vlan_translate_action_class_set ing $rv\n");
                return rv;
            }
            /* Map ing_vlan_action_id to action */
            bcm_vlan_action_set_t_init(&action);
            action.dt_outer = bcmVlanActionNone;
            action.dt_inner = bcmVlanActionNone;
            action.outer_tpid = 0x8100;
            action.inner_tpid = 0x8100;
            rv = bcm_vlan_translate_action_id_set(unit, BCM_VLAN_ACTION_SET_INGRESS, ing_vlan_action_id, &action);
            if (rv != BCM_E_NONE) {
                printf("Error, bcm_vlan_translate_action_id_set ing $rv\n");
                return rv;
            }        
        } else {
            bcm_vlan_action_set_t_init(&action);
            action.ot_outer = bcmVlanActionNone;
            action.ot_inner = bcmVlanActionNone;
            rv = bcm_vlan_translate_action_create(unit, vlan_port.vlan_port_id, bcmVlanTranslateKeyPortOuter, BCM_VLAN_INVALID, BCM_VLAN_NONE, &action);
            if (rv != BCM_E_NONE) {
                printf("Error, in bcm_vlan_translate_action_create $rv\n");
                return rv;
            }
        }
    }

    return rv;
}


/*
 * Create an MACT entry for VXLAN tunnel, mapped to the VPN 
 */
int
vxlan_l2_addr_add (
    int unit,
    bcm_gport_t vxlan_port_id)
{
    int rv = BCM_E_NONE;
    bcm_l2_addr_t l2addr2;

    bcm_l2_addr_t_init(&l2addr2, cint_vxlan_basic_info.dmac_in, cint_vxlan_basic_info.vpn_id);
    l2addr2.port  = vxlan_port_id;
    l2addr2.vid   = cint_vxlan_basic_info.vpn_id;
    l2addr2.flags = BCM_L2_STATIC;

    rv = bcm_l2_addr_add(unit, &l2addr2);
    if (rv != BCM_E_NONE) {
        printf("%s(): Error, bcm_l2_addr_add\n", proc_name);
        return rv;
    }

    return rv;
}

/*vxlan tunnel qos update main function*/
int vxlan_tunnel_encap_qos_update(int unit, int qos_map_id, int qos_model, int dscp)
{
    int rv = BCM_E_NONE;
    int flags;
    bcm_l3_egress_t l3eg;
    bcm_if_t l3egid_null;       /* not intersting */
    bcm_l3_intf_t l3_intf;
    bcm_tunnel_initiator_t tunnel_init;

    if (!is_device_or_above(unit, JERICHO2))
    {
        printf("This function is only supported on JR2\n");
        return BCM_E_UNAVAIL;
    }

    bcm_tunnel_initiator_t_init(&tunnel_init);
    bcm_l3_intf_t_init(&l3_intf);
    l3_intf.l3a_intf_id = cint_vxlan_basic_info.l3_intf;
    rv= bcm_tunnel_initiator_get(unit, &l3_intf, &tunnel_init);
    if (rv) {
        printf("error bcm_tunnel_initiator_get()\n");
        return rv;
    }
    if(dscp != -1)
    {
      tunnel_init.dscp = dscp;  
    }
    tunnel_init.egress_qos_model.egress_qos = qos_model;
    tunnel_init.flags |= (BCM_TUNNEL_WITH_ID |  BCM_TUNNEL_REPLACE);
    rv = bcm_tunnel_initiator_create(unit,&l3_intf, tunnel_init);
    if (rv != BCM_E_NONE)
    {
        printf("Error, bcm_tunnel_initiator_create \n");
    }
    /*update ARP qos map id in order to remark IP tunnle TOS*/
    if (qos_map_id != -1)
    {
        bcm_l3_egress_t_init(&l3eg);
        l3eg.encap_id = cint_vxlan_basic_info.tunnel_arp_id;
        rv = bcm_l3_egress_get(unit,cint_vxlan_basic_info.tunnel_arp_id,&l3eg);
        if (rv) {
            printf("error bcm_l3_egress_get()\n");
            return rv;
        }
        l3eg.qos_map_id = qos_map_id;
        flags = BCM_L3_REPLACE | BCM_L3_WITH_ID | BCM_L3_EGRESS_ONLY;
        rv = bcm_l3_egress_create(unit, flags, &l3eg, &l3egid_null);
        if (rv) {
            printf("error bcm_l3_egress_create()\n");
            return rv;
        }
    }

    return rv;
}


int vxlan_vpn_destroy(int unit) {
    int rv = BCM_E_NONE;
    rv = bcm_vxlan_vpn_destroy(unit, cint_vxlan_basic_info.vpn_id);
    if (rv) {
        printf("error in bcm_vxlan_vpn_destroy\n");
    }
    return rv; 
}
 

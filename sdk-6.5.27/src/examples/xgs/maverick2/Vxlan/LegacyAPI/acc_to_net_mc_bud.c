/*
 * Feature  : VxLAN known multicast BUD mode
 *
 * Usage    : BCM.0> cint acc_to_net_mc_bud.c
 *
 * config   : config.56770.vxlan
 *
 * Log file : acc_to_net_mc_bud_log.txt
 *
 * Test Topology :
 *
 *                  +------------------------------+
 *                  |                              |
 *                  |                              |  network port 1<<<< Incoming VxLAN encapsulated IPMC
 *                  |                              +-----------------+
 * acees_port_1     |                              |
 * +----------------+          SWITCH              |
 *                  |                              |
 *                  |                              |
 *                  |                              | network port 2(to VTEP 2)
 *                  |                              +-----------------+
 *                  |                              |
 *                  +------------------------------+
 * Summary:
 * ========
 *   This Cint example to show configuration of acc to net multicast of vxlan
 *   
 *
 * Detailed steps done in the CINT script:
 * =======================================
 *    1) Step1 - Test Setup (Done in test_setup()):
 *    =============================================
 *      a) Select three ports as 3 access_port 
 *
 *      b) Configure access_port_1 as ingress port and all others as egress ports.
 *
 *      c) All ports are configured in loopback mode and IFP rules are installed
 *         on all ports to copy all packets ingressing these ports to CPU.
 *
 *      d) On egress ports an additional action is installed to drop the packets
 *         to avoid loopback.
 *
 *      e) Start packet watcher.
 *

 *    2) Step2 - Configuration (Done in vxlan_access_to_network_bud())
 *    =============================================================================

 *       
 *
 *   3) Step3 - Verification ():
 *   ===========================================
 *       In the BUD mode, when the incoming VxLAN encapsulated IPMC traffic comes in to network port1,
 *       the VxLAN pacekt is terminated and sent to access port, in the mean time,
 *       the VxLAN encapsulated packet is routed out on network port2(port 3).
 *       
 *       Test 1) Multicast initiation
 *        
 *       Ingress on access_Port_1  with the following multicast packet(the script will send the pkt automatically):
 *       
 *       01005E0101010000000011BB81000015
 *       08004500002E0000000040FF84C40A0A
 *       0A01E001010100010203040506070809
 *       0A0B0C0D0E0F10111213141516171819
 *       
 *       Expected Result
 *       The multicast packet is encapsulated in the multicast VxLAN tunnel on network port 1:
 *       
 *       0100 5e01 0114 0000 0000 2222 8100 0016
 *       0800 4501 0060 0000 0000 1011 b56c 0a0a 
 *       0a01 e001 0114 ffff 2118 004c 0000 0800 
 *       0000 0123 4500 0100 5e01 0101 0000 0000 
 *       11bb 0800 4500 002e 0000 0000 40ff 84c4 
 *       0a0a 0a01 e001 0101 0001 0203 0405 0607 
 *       0809 0a0b 0c0d 0e0f 1011 1213 1415 1617 
 *       1819 f77b e408
 *       
 *       Test 2) Multicast termination (BUD mode)
 *       
 *       Ingress on Network Port 1(the script will send the pkt automatically):
 *       
 *       01005E01011400000000000281000016
 *       080045000060000000004011D7CEC0A8
 *       0101E0010114FFFF2118004C00000800
 *       00000123450001005E01010100000000
 *       11CC080045000031000100004000D820
 *       C0A80101E00101010001020304050607
 *       08090A0B0C0D0E0F1011121314151617
 *       1819
 *       
 *       Expected Result
 *       The VxlAN tunnel is terminated, and multicast packet sent to access port 1:
 *       
 *       0100 5e01 0101 0000 0000 11cc 8100 0015
 *       0800 4500 0031 0001 0000 4000 d820 c0a8 
 *       0101 e001 0101 0001 0203 0405 0607 0809 
 *       0a0b 0c0d 0e0f 1011 1213 1415 1617 1819 
 *       d696 d1d9
 *       
 *       Network port 2 out (IPMC routed):
 *       
 *       0100 5e01 0114 0000 0000 3333 8100 0017
 *       0800 4500 0060 0000 0000 3f11 d8ce c0a8 
 *       0101 e001 0114 ffff 2118 004c 0000 0800 
 *       0000 0123 4500 0100 5e01 0101 0000 0000 
 *       11cc 0800 4500 0031 0001 0000 4000 d820 
 *       c0a8 0101 e001 0101 0001 0203 0405 0607 
 *       0809 0a0b 0c0d 0e0f 1011 1213 1415 1617 
 *       1819 88af 81c0

 *
 */


cint_reset();


/**************************   1 basic function begin*************************************/
/* Create vlan and add port to vlan */

int
vlan_create_add_port(int unit, int vid, int port)
{
    bcm_pbmp_t pbmp, upbmp;
    bcm_error_t rv = BCM_E_NONE;

    rv = bcm_vlan_create(unit, vid);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_vlan_create failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}
    BCM_PBMP_CLEAR(pbmp);
    BCM_PBMP_CLEAR(upbmp);
    BCM_PBMP_PORT_ADD(pbmp, port);
    rv = bcm_vlan_port_add(unit, vid, pbmp, upbmp);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_vlan_port_add failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}	
	
	printf("vlan_create_add_port SUCCESS \n");
	return rv;	
}

int
vlan_create_add_ports(int unit, int vid, int count, bcm_port_t *ports)
{
    bcm_pbmp_t pbmp, upbmp;
    int i;
    bcm_error_t rv = BCM_E_NONE;
    rv  = bcm_vlan_create(unit, vid);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_vlan_create failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}
    BCM_PBMP_CLEAR(pbmp);
    BCM_PBMP_CLEAR(upbmp);

    for (i = 0; i < count; i++) {
        BCM_PBMP_PORT_ADD(pbmp, ports[i]);
    }

     rv = bcm_vlan_port_add(unit, vid, pbmp, upbmp);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_vlan_port_add failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("vlan_create_add_ports SUCCESS! \n");
	return rv;	
}

/* Create L3 interface */
int
create_l3_interface(int unit, int flags, bcm_mac_t local_mac, int vid, int vrf, bcm_if_t *intf_id)
{
    bcm_l3_intf_t l3_intf; 
    bcm_error_t rv = BCM_E_NONE;

    /* L3 interface and egress object for access */
    bcm_l3_intf_t_init(&l3_intf);
    l3_intf.l3a_flags |= flags;
    sal_memcpy(l3_intf.l3a_mac_addr, local_mac, sizeof(local_mac));
    l3_intf.l3a_vid = vid;
    l3_intf.l3a_vrf = vrf;
    rv = bcm_l3_intf_create(unit, &l3_intf);
    *intf_id = l3_intf.l3a_intf_id;
	
	if (BCM_E_NONE != rv)
	{
			printf("bcm_l3_intf_create failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("create_l3_interface SUCCESS! \n");
    return rv;
}

int 
create_l3_if_id(int unit, int flags, int intf_id, bcm_mac_t local_mac, int vid, int vrf)
{
    bcm_l3_intf_t l3_intf;
    bcm_error_t rv = BCM_E_NONE;

    /* L3 interface and egress object for access */
    bcm_l3_intf_t_init(&l3_intf);
    l3_intf.l3a_flags = BCM_L3_WITH_ID | flags;
    l3_intf.l3a_intf_id = intf_id;
    sal_memcpy(l3_intf.l3a_mac_addr, local_mac, sizeof(local_mac));
    l3_intf.l3a_vid = vid;
    l3_intf.l3a_vrf = vrf;

    rv = bcm_l3_intf_create(unit, &l3_intf);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_l3_intf_create failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("create_l3_if_id SUCCESS! \n");
    return rv;
	
}

/* Create L3 egress object */
int
l3_create_egr_obj(int unit, int flags, int l3_if, bcm_mac_t nh_mac, bcm_gport_t gport,
                   bcm_if_t *egr_obj_id)
{
    bcm_l3_egress_t l3_egress;
    bcm_error_t rv = BCM_E_NONE;

    bcm_l3_egress_t_init(&l3_egress);
    l3_egress.flags  |= flags;
    sal_memcpy(l3_egress.mac_addr,  nh_mac, sizeof(nh_mac));
    l3_egress.intf  = l3_if;
    l3_egress.port = gport;
    rv = bcm_l3_egress_create(unit, 0, &l3_egress, egr_obj_id);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_l3_egress_create failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("l3_create_egr_obj SUCCESS! \n");
    return rv;	
}

int
vxlan_create_egr_obj(int unit, uint32 flag, int l3_if, bcm_mac_t nh_mac, bcm_gport_t gport,
              int vid, bcm_if_t *egr_obj_id)
{
    bcm_l3_egress_t l3_egress;
    bcm_error_t rv = BCM_E_NONE;

    bcm_l3_egress_t_init(&l3_egress);
    l3_egress.flags = BCM_L3_VXLAN_ONLY | flag;
    l3_egress.intf  = l3_if;
    sal_memcpy(l3_egress.mac_addr,  nh_mac, sizeof(nh_mac));
    l3_egress.vlan = vid;
    l3_egress.port = gport;
    rv = bcm_l3_egress_create(unit, flag, &l3_egress, egr_obj_id);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_l3_egress_create failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("vxlan_create_egr_obj SUCCESS! \n");
    return rv;		
}

int
add_to_l2_station(int unit, bcm_mac_t mac, bcm_vlan_t vid, int flags)
{
    bcm_l2_station_t l2_station;
    int station_id;
    bcm_error_t rv = BCM_E_NONE;

    bcm_l2_station_t_init(&l2_station);
    sal_memcpy(l2_station.dst_mac, mac, sizeof(mac));
    l2_station.flags   = flags;
    l2_station.dst_mac_mask = "ff:ff:ff:ff:ff:ff";
    l2_station.vlan         = vid;
    l2_station.vlan_mask    = 0xfff;
    rv = bcm_l2_station_add(unit, &station_id, &l2_station);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_l2_station_add failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("add_to_l2_station SUCCESS! \n");	
    return rv;
}

int
add_to_l2_table(int unit, bcm_mac_t mac, bcm_vpn_t vpn_id, int port, int stat)
{
    bcm_l2_addr_t l2_addr;
    bcm_error_t rv = BCM_E_NONE;

    bcm_l2_addr_t_init(&l2_addr, mac, vpn_id);
    if (stat) {
        l2_addr.flags = BCM_L2_STATIC;
    }
    l2_addr.port = port;
    rv = bcm_l2_addr_add(unit, &l2_addr);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_l2_addr_add failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("add_to_l2_table SUCCESS! \n");	
    return rv;	
}

int do_vxlan_global_setting(int unit)
{
    bcm_error_t rv = BCM_E_NONE;

    /* Enable L3 Egress Mode */
    rv = bcm_switch_control_set(unit, bcmSwitchL3EgressMode, TRUE);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_switch_control_set failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("bcm_switch_control_set SUCCESS! \n");		

    /* Set UDP port for VXLAN */
    rv = bcm_switch_control_set(unit, bcmSwitchVxlanUdpDestPortSet, udp_dp);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_switch_control_set bcmSwitchVxlanUdpDestPortSet failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("bcm_switch_control_set bcmSwitchVxlanUdpDestPortSet SUCCESS! \n");			

    /* Enable/Disable VXLAN Entropy */
    rv = bcm_switch_control_set(unit, bcmSwitchVxlanEntropyEnable, FALSE);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_switch_control_set bcmSwitchVxlanEntropyEnablefailed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("bcm_switch_control_set bcmSwitchVxlanEntropyEnable SUCCESS! \n");			

    /* Enable/Disable VXLAN Tunnel lookup failure settings */
    rv = bcm_switch_control_set(unit, bcmSwitchVxlanTunnelMissToCpu, TRUE);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_switch_control_set  bcmSwitchVxlanTunnelMissToCpu failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("bcm_switch_control_set bcmSwitchVxlanTunnelMissToCpu SUCCESS! \n");			

    /* Enable/Disable VXLAN VN_ID lookup failure settings */
    rv = bcm_switch_control_set(unit, bcmSwitchVxlanVnIdMissToCpu, TRUE);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_switch_control_set  bcmSwitchVxlanVnIdMissToCpu failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("bcm_switch_control_set bcmSwitchVxlanVnIdMissToCpu SUCCESS! \n");			

    return BCM_E_NONE;
}

int
do_vxlan_access_port_settings(int unit, bcm_port_t a_port)
{
    bcm_error_t rv = BCM_E_NONE;

	/* Enable VLAN translation on access port */
    rv = bcm_vlan_control_port_set(unit, a_port, bcmVlanTranslateIngressEnable, TRUE);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_vlan_control_port_set  bcmVlanTranslateIngressEnable failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("bcm_vlan_control_port_set bcmVlanTranslateIngressEnable SUCCESS! \n");			

    /* Should disable Vxlan Processing on access port */
    rv = bcm_port_control_set(unit, a_port, bcmPortControlVxlanEnable, FALSE);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_vlan_control_port_set  bcmPortControlVxlanEnable failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("bcm_vlan_control_port_set bcmPortControlVxlanEnable SUCCESS! \n");				

    /* Should disable Tunnel Based Vxlan-VnId lookup */
    rv = bcm_port_control_set(unit, a_port, bcmPortControlVxlanTunnelbasedVnId, FALSE);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_vlan_control_port_set  bcmPortControlVxlanTunnelbasedVnId failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("bcm_vlan_control_port_set bcmPortControlVxlanTunnelbasedVnId SUCCESS! \n");				

    return BCM_E_NONE;
}

int
do_vxlan_net_port_settings(int unit, bcm_port_t n_port)
{
    bcm_error_t rv = BCM_E_NONE;

    /* Enable VXLAN Processing on network port */
    rv =  bcm_port_control_set(unit, n_port, bcmPortControlVxlanEnable, TRUE);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_port_control_set  bcmPortControlVxlanEnable failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("bcm_port_control_set bcmPortControlVxlanEnable SUCCESS! \n");				
	

    /* Allow tunnel based VXLAN-VNID lookup */
    rv =  bcm_port_control_set(unit, n_port, bcmPortControlVxlanTunnelbasedVnId, FALSE);
                              /* Only BCM_VXLAN_PORT_MATCH_VN_ID at network port */
	if (BCM_E_NONE != rv)
	{
			printf("bcm_port_control_set  bcmPortControlVxlanTunnelbasedVnId failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("bcm_port_control_set bcmPortControlVxlanTunnelbasedVnId SUCCESS! \n");				
								  

    return BCM_E_NONE;
}

int
tunnel_initiator_setup(int unit, bcm_ip_t lip, bcm_ip_t rip, int dp, int sp, int ttl, int *tid)
{
    bcm_tunnel_initiator_t tnl_init;
    bcm_error_t rv = BCM_E_NONE;

    bcm_tunnel_initiator_t_init(&tnl_init);
    tnl_init.type  = bcmTunnelTypeVxlan;
    tnl_init.ttl = ttl;
    tnl_init.sip = lip;
    tnl_init.dip = rip;
    tnl_init.udp_dst_port = dp;
    tnl_init.udp_src_port = sp;
    rv = bcm_vxlan_tunnel_initiator_create(unit, &tnl_init);
    *tid = tnl_init.tunnel_id;
	if (BCM_E_NONE != rv)
	{
			printf("bcm_vxlan_tunnel_initiator_create failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("tunnel_initiator_setup SUCCESS! \n");			
	
    return rv;
}

int
tunnel_terminator_setup(int unit, bcm_ip_t rip, bcm_ip_t lip, bcm_vlan_t net_vid,
                        int tunnel_init_id, int *term_id)
{
    bcm_tunnel_terminator_t tnl_term;
    bcm_error_t rv = BCM_E_NONE;

    bcm_tunnel_terminator_t_init(&tnl_term);
    tnl_term.type = bcmTunnelTypeVxlan;
    tnl_term.sip = rip;    /* For MC tunnel, Don't care */
    tnl_term.dip = lip;
    tnl_term.tunnel_id = tunnel_init_id;
    tnl_term.flags = BCM_TUNNEL_TERM_TUNNEL_WITH_ID;
    if (net_vid != -1) {
        tnl_term.vlan = net_vid;  /* MC tunnel only - for Bud check */
    }
    rv = bcm_vxlan_tunnel_terminator_create(unit, &tnl_term);
    *term_id = tnl_term.tunnel_id;
	if (BCM_E_NONE != rv)
	{
			printf("bcm_vxlan_tunnel_terminator_create failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("tunnel_terminator_setup SUCCESS! \n");			

    return rv;
}

int
create_vxlan_vpn(int unit, int vpn_id, int vnid, bcm_multicast_t bc,
                 bcm_multicast_t mc, bcm_multicast_t uuc)
{
    bcm_vxlan_vpn_config_t vpn_info;
    bcm_error_t rv = BCM_E_NONE;

    bcm_vxlan_vpn_config_t_init(&vpn_info);
    vpn_info.flags = BCM_VXLAN_VPN_ELAN | BCM_VXLAN_VPN_WITH_ID | BCM_VXLAN_VPN_WITH_VPNID;
    vpn_info.vpn  = vpn_id;
    vpn_info.vnid = vnid;
    vpn_info.broadcast_group         = bc;
    vpn_info.unknown_multicast_group = mc;
    vpn_info.unknown_unicast_group   = uuc;
    rv = bcm_vxlan_vpn_create(unit, &vpn_info);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_vxlan_vpn_create failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("create_vxlan_vpn SUCCESS! \n");			

    return rv;
}

int
sdtag_create_vxlan_vpn(int unit, int vpn_id, int vnid, bcm_multicast_t bc,
              bcm_multicast_t mc, bcm_multicast_t uuc)
{
    bcm_vxlan_vpn_config_t vpn_info;
    bcm_error_t rv = BCM_E_NONE;

    bcm_vxlan_vpn_config_t_init(&vpn_info);
    /* Service tag will be removed going into UDP tunnel */
    vpn_info.flags = BCM_VXLAN_VPN_ELAN | BCM_VXLAN_VPN_WITH_ID | BCM_VXLAN_VPN_WITH_VPNID |
                     BCM_VXLAN_VPN_SERVICE_TAGGED | BCM_VXLAN_VPN_SERVICE_VLAN_DELETE;
    vpn_info.vpn  = vpn_id;
    vpn_info.vnid = vnid;
    vpn_info.broadcast_group         = bc;
    vpn_info.unknown_multicast_group = mc;
    vpn_info.unknown_unicast_group   = uuc;
    vpn_info.egress_service_tpid     = 0x8100;
    rv = bcm_vxlan_vpn_create(unit, &vpn_info);
	if (BCM_E_NONE != rv)
	{
			printf("bcm_vxlan_vpn_create failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("sdtag_create_vxlan_vpn SUCCESS! \n");		
    return rv;
}

int
create_vxlan_acc_vp(int unit, bcm_vpn_t vpn, uint32 flags, bcm_gport_t port,
                    bcm_vxlan_port_match_t criteria,
                    bcm_if_t egr_obj, bcm_vlan_t vid, bcm_gport_t *vp)
{
    bcm_vxlan_port_t vxlan_port;
    bcm_error_t rv = BCM_E_NONE;

    bcm_vxlan_port_t_init(&vxlan_port);
    vxlan_port.flags = BCM_VXLAN_PORT_SERVICE_TAGGED | flags;
    vxlan_port.match_port =        port;
    vxlan_port.criteria =          criteria;
    vxlan_port.egress_if =         egr_obj;
    vxlan_port.match_vlan =        vid;
    rv = bcm_vxlan_port_add(unit, vpn, &vxlan_port);
    *vp = vxlan_port.vxlan_port_id;
	if (BCM_E_NONE != rv)
	{
			printf("bcm_vxlan_port_add failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("create_vxlan_acc_vp SUCCESS! \n");			

    return rv;
}

int
sdtag_create_vxlan_acc_vp(int unit, bcm_vpn_t vpn, uint32 flags, bcm_gport_t port,
                    bcm_vxlan_port_match_t criteria, bcm_if_t egr_obj,
                    bcm_vlan_t vid, bcm_vlan_t sdtag, bcm_gport_t *vp)
{
    bcm_vxlan_port_t vxlan_port;
    bcm_error_t rv = BCM_E_NONE;

    bcm_vxlan_port_t_init(&vxlan_port);
    vxlan_port.flags = BCM_VXLAN_PORT_SERVICE_TAGGED | flags;
    vxlan_port.criteria =          criteria;
    vxlan_port.match_port =        port;
    vxlan_port.egress_if =         egr_obj;
    vxlan_port.match_vlan =        vid;
    vxlan_port.egress_service_tpid = 0x8100;
    vxlan_port.egress_service_vlan = sdtag;
    rv = bcm_vxlan_port_add(unit, vpn, &vxlan_port);
    *vp = vxlan_port.vxlan_port_id;
	if (BCM_E_NONE != rv)
	{
			printf("bcm_vxlan_port_add failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("sdtag_create_vxlan_acc_vp SUCCESS! \n");			
	
    return rv;
}

int
create_vxlan_net_vp(int unit, bcm_vpn_t vpn, uint32 flags, bcm_gport_t port,
                    bcm_vxlan_port_match_t criteria, bcm_if_t egr_obj,
                    bcm_gport_t tun_init, bcm_gport_t tun_term, bcm_gport_t *vp)
{
    bcm_vxlan_port_t vxlan_port;
    bcm_error_t rv = BCM_E_NONE;

    bcm_vxlan_port_t_init(&vxlan_port);
    vxlan_port.flags = BCM_VXLAN_PORT_NETWORK | BCM_VXLAN_PORT_EGRESS_TUNNEL |
                       BCM_VXLAN_PORT_SERVICE_TAGGED | flags;
    vxlan_port.match_port =        port;
    vxlan_port.criteria =          criteria;
    vxlan_port.egress_if =         egr_obj;
    vxlan_port.egress_tunnel_id =  tun_init;
    vxlan_port.match_tunnel_id =   tun_term;
    /* vpn_id parameter is not care for net VP */
    rv = bcm_vxlan_port_add(unit, vpn, &vxlan_port);
    *vp = vxlan_port.vxlan_port_id;
	if (BCM_E_NONE != rv)
	{
			printf("bcm_vxlan_port_add failed %s\n", bcm_errmsg(rv));		
			return rv;	
	}

     printf("create_vxlan_net_vp SUCCESS! \n");			

    return rv;
}



        
bcm_error_t
create_ifp_group (int unit, bcm_field_group_config_t *group_config)
{
    bcm_error_t rv = BCM_E_NONE;

    /* FP group configuration and creation */
    bcm_field_group_config_t_init(group_config);

    BCM_FIELD_QSET_INIT(group_config->qset);
    BCM_FIELD_QSET_ADD(group_config->qset, bcmFieldQualifyStageIngress);
    BCM_FIELD_QSET_ADD(group_config->qset, bcmFieldQualifyInPort);

    group_config->mode = bcmFieldGroupModeAuto;

    rv = bcm_field_group_config_create(unit, group_config);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_group_config_create() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    return rv;
}


bcm_error_t
create_ifp_to_cpu_rule (int unit, bcm_field_group_t gid, bcm_field_entry_t *eid, bcm_port_t port)
{
    bcm_error_t rv = BCM_E_NONE;
    bcm_port_t port_mask = 0xffffffff;
    
    /* FP entry configuration and creation */
    rv = bcm_field_entry_create(unit, gid, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_create() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_qualify_InPort(unit, *eid, port, port_mask);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_InPort() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* FP entry actions configuration */
    rv = bcm_field_action_add(unit, *eid, bcmFieldActionDrop, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_field_action_add(unit, *eid, bcmFieldActionCopyToCpu, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* Installing FP entry to FP TCAM */
    rv = bcm_field_entry_install(unit, *eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_install() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    return rv;
}


bcm_error_t
destroy_ifp_to_cpu_rule (int unit, bcm_field_entry_t eid)
{
    bcm_error_t rv = BCM_E_NONE;
    
    /* Destroying FP entry */
    rv = bcm_field_entry_destroy(unit, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_destroy() : %s\n", bcm_errmsg(rv));
        return rv;
    }

    return rv;
}



/**************************1 basic function end*************************************/

/**************************2 global variable defination begin***********************/

bcm_error_t rv = BCM_E_NONE;
uint16 udp_dp = 8472;   /* UDP dst port used for OTV */

bcm_port_t access_port_1  = BCM_PORT_INVALID;
bcm_port_t network_port_1 = BCM_PORT_INVALID;
bcm_port_t network_port_2 = BCM_PORT_INVALID;


bcm_gport_t access_gport_1  = BCM_GPORT_INVALID;
bcm_gport_t network_gport_1 = BCM_GPORT_INVALID;
bcm_gport_t network_gport_2 = BCM_GPORT_INVALID;

/* FP Group/Rule Creation/Destruction*/
bcm_field_group_config_t group_config;
bcm_field_entry_t access_port_1_eid = BCM_FIELD_ENTRY_INVALID;
bcm_field_entry_t network_port_1_eid = BCM_FIELD_ENTRY_INVALID;
bcm_field_entry_t network_port_2_eid = BCM_FIELD_ENTRY_INVALID;

/**************************2 global variable defination end ***********************/

/**************************3 test setup functions begin***********************/

bcm_error_t
create_ifp_group (int unit, bcm_field_group_config_t *group_config)
{
    bcm_error_t rv = BCM_E_NONE;
    /* FP group configuration and creation */
    bcm_field_group_config_t_init(group_config);
    BCM_FIELD_QSET_INIT(group_config->qset);
    BCM_FIELD_QSET_ADD(group_config->qset, bcmFieldQualifyStageIngress);
    BCM_FIELD_QSET_ADD(group_config->qset, bcmFieldQualifyInPort);
    group_config->mode = bcmFieldGroupModeAuto;
    rv = bcm_field_group_config_create(unit, group_config);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_group_config_create() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    return rv;
}

bcm_error_t
create_ifp_to_cpu_rule (int unit, bcm_field_group_t gid, bcm_field_entry_t *eid, bcm_port_t port, int drop)
{
    bcm_error_t rv = BCM_E_NONE;
    bcm_port_t port_mask = 0xffffffff;
    /* FP entry configuration and creation */
    rv = bcm_field_entry_create(unit, gid, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_create() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    rv = bcm_field_qualify_InPort(unit, *eid, port, port_mask);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_qualify_InPort() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    /* FP entry actions configuration */
    if (1 == drop) {
        rv = bcm_field_action_add(unit, *eid, bcmFieldActionDrop, 0, 0);
        if(BCM_FAILURE(rv)) {
            printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
            return rv;
        }
    }
    rv = bcm_field_action_add(unit, *eid, bcmFieldActionCopyToCpu, 0, 0);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_action_add() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    /* Installing FP entry to FP TCAM */
    rv = bcm_field_entry_install(unit, *eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_install() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    return rv;
}

bcm_error_t
destroy_ifp_to_cpu_rule (int unit, bcm_field_entry_t eid)
{
    bcm_error_t rv = BCM_E_NONE;

    /* Destroying FP entry */
    rv = bcm_field_entry_destroy(unit, eid);
    if(BCM_FAILURE(rv)) {
        printf("\nError in bcm_field_entry_destroy() : %s\n", bcm_errmsg(rv));
        return rv;
    }
    return rv;
}


/* This function is written so that hardcoding of port
   numbers in Cint scripts is removed. This function gives
   required number of ports
*/
bcm_error_t portNumbersGet(int unit, int *port_list, int num_ports)
{

  int i=0,port=0,rv=0;
  bcm_port_config_t configP;
  bcm_pbmp_t ports_pbmp;

  rv = bcm_port_config_get(unit,&configP);
  if(BCM_FAILURE(rv)) {
    printf("\nError in retrieving port configuration: %s.\n",bcm_errmsg(rv));
    return rv;
  }

  ports_pbmp = configP.e;
  for (i= 1; i < BCM_PBMP_PORT_MAX; i++) {
    if (BCM_PBMP_MEMBER(&ports_pbmp,i)&& (port < num_ports)) {
      port_list[port]=i;
      port++;
    }
  }

  if (( port == 0 ) || ( port != num_ports )) {
      printf("portNumbersGet() failed \n");
      return -1;
  }

  return BCM_E_NONE;

}

/*
 * Configures the port in loopback mode and discard setting to BCM_PORT_DISCARD_NONE.
 * Also add a rule to copy packets ingressing on the port to CPU.
 */
bcm_error_t ingress_port_setup(int unit, bcm_port_t port, bcm_field_entry_t *entry)
{
  int drop;
  bcm_error_t rv;
  BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, port, BCM_PORT_LOOPBACK_MAC));
  BCM_IF_ERROR_RETURN(bcm_port_discard_set(unit, port, BCM_PORT_DISCARD_NONE));
  if (BCM_FIELD_ENTRY_INVALID != *entry)
  {
    rv = destroy_ifp_to_cpu_rule(unit, *entry);
    if(BCM_FAILURE(rv))
    {
        printf("\nError executing destroy_ifp_to_cpu_rule%s.\n",bcm_errmsg(rv));
        return rv;
    }
  }
  rv = create_ifp_to_cpu_rule(unit, group_config.group, entry, port, (drop = 0));
  if(BCM_FAILURE(rv))
  {
      printf("\nError executing create_ifp_to_cpu_rule(): %s.\n",bcm_errmsg(rv));
      return rv;
  }

  return BCM_E_NONE;
}

/*
 * Configures the port in loopback mode and discard setting to BCM_PORT_DISCARD_ALL.
 * Also add a rule to copy packets ingressing on the port to CPU and drop them
 * to avoid loopback.
 */

bcm_error_t egress_port_setup(int unit, bcm_port_t port, bcm_field_entry_t *entry)
{
  int drop;
  bcm_error_t rv;
  BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, port, BCM_PORT_LOOPBACK_MAC));
  BCM_IF_ERROR_RETURN(bcm_port_discard_set(unit, port, BCM_PORT_DISCARD_ALL));
  if (BCM_FIELD_ENTRY_INVALID != *entry)
  {
    rv = destroy_ifp_to_cpu_rule(unit, *entry);
    if(BCM_FAILURE(rv))
    {
        printf("\nError executing destroy_ifp_to_cpu_rule%s.\n",bcm_errmsg(rv));
        return rv;
    }
  }
  rv = create_ifp_to_cpu_rule(unit, group_config.group, entry, port, (drop = 1));
  if(BCM_FAILURE(rv))
  {
      printf("\nError executing create_ifp_to_cpu_rule(): %s.\n",bcm_errmsg(rv));
      return rv;
  }

  return BCM_E_NONE;
}



/*   Select 3 ports and does ingess and egress port setting on respective ports.
 *   */
bcm_error_t test_setup(int unit)
{
  int port_list[3], i;
  bcm_field_entry_t entry[3] = {BCM_FIELD_ENTRY_INVALID, BCM_FIELD_ENTRY_INVALID, BCM_FIELD_ENTRY_INVALID};  
  if (BCM_E_NONE != portNumbersGet(unit, port_list, 3)) {
    printf("portNumbersGet() failed\n");
    return -1;
  }

  access_port_1 = port_list[0];
  network_port_1 = port_list[1];
  network_port_2 = port_list[2];

  BCM_IF_ERROR_RETURN(create_ifp_group(unit, &group_config));
  printf("Using port number:%d as access_port_1\n", access_port_1);
  if (BCM_E_NONE != ingress_port_setup(unit, access_port_1, &entry[0])) {
    printf("ingress_port_setup() failed for port %d\n", access_port_1);
    return -1;
  }
  access_port_1_eid = entry[0];
  
  for (i = 1; i <= 2; i++) {
    printf("Using port number:%d as network_port_%d\n", port_list[i], (i ));
    if (BCM_E_NONE != egress_port_setup(unit, port_list[i], &entry[i])) {
      printf("egress_port_setup() failed for port %d\n", port_list[i]);
      return -1;
    }
  }
  network_port_1_eid = entry[1];
  network_port_2_eid = entry[2];


  bshell(unit, "pw start report +raw +decode");
  return BCM_E_NONE;
}

/**************************3 test setup functions end ***********************/

/**************************4 main functions begin ***********************/

/********************************************************************
*********************************************************************
*************** main script *********************
*********************************************************************
**********************************************************************/


bcm_error_t
tunnel_terminator_bud_update(int unit, int term_id)
{
    bcm_tunnel_terminator_t tnl_term;
    bcm_error_t rv = BCM_E_NONE;

    bcm_tunnel_terminator_t_init(&tnl_term);
    tnl_term.flags |= BCM_TUNNEL_TERM_TUNNEL_WITH_ID;
    tnl_term.multicast_flag = BCM_VXLAN_MULTICAST_TUNNEL_STATE_BUD_ENABLE;
    tnl_term.tunnel_id = term_id;
    rv = bcm_vxlan_tunnel_terminator_update(unit, &tnl_term);
    if (BCM_E_NONE != rv)
    {
      printf("bcm_vxlan_tunnel_terminator_update failed %s\n", bcm_errmsg(rv));		
      return rv;	
    }

     printf("tunnel_terminator_bud_update SUCCESS! \n");			

    return rv;
}

bcm_error_t vxlan_access_to_network_bud(int unit)
{
  /* VPN */
  bcm_vpn_t vpn_id = 0x7010;
  uint32 vnid = 0x12345;
  bcm_multicast_t dlf_group = 0;

  /* Used to create a dummy VPN that is used to create network VP */
  int rsvd_network_vpn = 0x7001;
  int rsvd_network_vpn_vnid = 0xeeee;

  /*
   * Access side
   */
  /* Access side MAC addresses are not really used */
  bcm_mac_t acc_dummy_mac = "00:00:01:00:00:01";

  bcm_vlan_t acc_vid = 21;
  bcm_if_t acc_intf_id = 1;
  bcm_if_t acc_egr_obj;
  int acc_vxlan_port;
  bcm_if_t acc_encap_id;

  /*
   * Network side
   */

  /* Tunnel */
  uint8 ttl = 16;

  uint16 udp_sp = 0xffff;
  int vrf = 0;

  /* Network 1 */
  bcm_vlan_t net_vid_1 = 22;
  bcm_if_t net_intf_id_1 = 2;
  bcm_if_t net_egr_obj_1;
  int net_vxlan_port_1;
  bcm_mac_t net_local_mac_1 = "00:00:00:00:22:22";
  bcm_mac_t net_remote_mac_1 = "00:00:00:00:00:02";
  bcm_ip_t tnl_local_ip_1  = 0x0a0a0a01;    /* 10.10.10.1 */
  bcm_ip_t tnl_remote_ip_1 = 0xC0A80101;    /* 192.168.1.1 */
  int tnl_uc_init_id_1, tnl_uc_term_id_1;

  /* Network 2 */
  bcm_vlan_t net_vid_2 = 23;
  bcm_if_t net_intf_id_2 = 3;
  bcm_if_t net_egr_obj_2;
  int net_vxlan_port_2;
  bcm_mac_t net_local_mac_2 = "00:00:00:00:33:33";
  bcm_mac_t net_remote_mac_2 = "00:00:00:00:00:03";
  bcm_ip_t tnl_local_ip_2  = 0x0a0a1402;    /* 10.10.20.2 */
  bcm_ip_t tnl_remote_ip_2 = 0xC0A80202;    /* 192.168.2.2 */
  int tnl_uc_init_id_2, tnl_uc_term_id_2;

  /*
   * DLF/BC tunnel and virtual port
   */
  bcm_mac_t dlf_mac = "01:00:5e:00:00:0A"; /* 224.0.0.10 */
  bcm_ip_t tnl_dlf_dip = 0xe000000A;       /* 224.0.0.10 */

  /* Assume the DLF/BC only forwards to network port 1 */
  bcm_if_t egr_obj_dlf;
  int vxlan_port_dlf;
  bcm_if_t encap_id_dlf;

  /* Still need to create two DLF tunnels, because the incoming DLF may arrive at any network ports */
  int tnl_dlf_init_id_1, tnl_dlf_term_id_1;
  int tnl_dlf_init_id_2, tnl_dlf_term_id_2;

  /* Unicast payment MAC */
  bcm_mac_t payload_da_1 = "00:00:00:00:11:aa";
  bcm_mac_t payload_sa   = "00:00:00:00:11:bb";
  bcm_mac_t payload_da_2 = "00:00:00:00:11:cc";


  /* Global settings */
  BCM_IF_ERROR_RETURN(do_vxlan_global_setting(unit));

  /* Access port settings */
  BCM_IF_ERROR_RETURN(do_vxlan_access_port_settings(unit, access_port_1));

  /* Network port settings */
  BCM_IF_ERROR_RETURN(do_vxlan_net_port_settings(unit, network_port_1));
  BCM_IF_ERROR_RETURN(do_vxlan_net_port_settings(unit, network_port_2));

  BCM_IF_ERROR_RETURN(bcm_port_gport_get(unit, access_port_1, &access_gport_1)); 
  BCM_IF_ERROR_RETURN(bcm_port_gport_get(unit, network_port_1, &network_gport_1)); 
  BCM_IF_ERROR_RETURN(bcm_port_gport_get(unit, network_port_2, &network_gport_2)); 

  /* VLAN settings */
  BCM_IF_ERROR_RETURN(vlan_create_add_port(unit, acc_vid, access_port_1));
  BCM_IF_ERROR_RETURN(vlan_create_add_port(unit, net_vid_1, network_port_1));
  BCM_IF_ERROR_RETURN(vlan_create_add_port(unit, net_vid_2, network_port_2));

  /* Multicast group for the segment MC/BC */
  BCM_IF_ERROR_RETURN(bcm_multicast_create(unit, BCM_MULTICAST_TYPE_VXLAN, &dlf_group));
  print dlf_group;

  /* Create VXLAN VPN */
  BCM_IF_ERROR_RETURN(sdtag_create_vxlan_vpn(unit, vpn_id, vnid, dlf_group, dlf_group, dlf_group));

  /* Create VXLAN VPN for assigning Network-VP */
  BCM_IF_ERROR_RETURN(sdtag_create_vxlan_vpn(unit, rsvd_network_vpn, rsvd_network_vpn_vnid, dlf_group, dlf_group, dlf_group));

  /* L3 interface and egress object for access - note use a dummy MAC address */
  BCM_IF_ERROR_RETURN(create_l3_interface(unit, 0, acc_dummy_mac, acc_vid, vrf, &acc_intf_id));
  BCM_IF_ERROR_RETURN(vxlan_create_egr_obj(unit, 0, acc_intf_id, acc_dummy_mac, access_gport_1, acc_vid, &acc_egr_obj));

  /* Create VXLAN VP for access port */
  BCM_IF_ERROR_RETURN(sdtag_create_vxlan_acc_vp(unit, vpn_id, BCM_VXLAN_PORT_SERVICE_VLAN_ADD,
                      access_gport_1, BCM_VXLAN_PORT_MATCH_PORT_VLAN,
                      acc_egr_obj, acc_vid, acc_vid, &acc_vxlan_port));
  print acc_vxlan_port;

  /*
   * Network port 1
   */
  /* Tunnel Setup (UC Initiator & Terminator) */
  BCM_IF_ERROR_RETURN(tunnel_initiator_setup(unit, tnl_local_ip_1, tnl_remote_ip_1, udp_dp, udp_sp, ttl, &tnl_uc_init_id_1));
  BCM_IF_ERROR_RETURN(tunnel_terminator_setup(unit, tnl_remote_ip_1, tnl_local_ip_1, -1, tnl_uc_init_id_1, &tnl_uc_term_id_1));

  /* L3 interface and egress object */
  BCM_IF_ERROR_RETURN(create_l3_interface(unit, 0, net_local_mac_1, net_vid_1, vrf, &net_intf_id_1));
  BCM_IF_ERROR_RETURN(vxlan_create_egr_obj(unit, 0, net_intf_id_1, net_remote_mac_1, network_gport_1,
                 net_vid_1, &net_egr_obj_1));

  /* Create VXLAN VP */
  BCM_IF_ERROR_RETURN(create_vxlan_net_vp(unit, rsvd_network_vpn, 0, network_gport_1, BCM_VXLAN_PORT_MATCH_VN_ID,
                      net_egr_obj_1, tnl_uc_init_id_1, tnl_uc_term_id_1, &net_vxlan_port_1));
  print net_vxlan_port_1;

  /* Tunnel Setup (DLF/BC Initiator & Terminator) */
  BCM_IF_ERROR_RETURN(tunnel_initiator_setup(unit, tnl_local_ip_1, tnl_dlf_dip, udp_dp, udp_sp, ttl, &tnl_dlf_init_id_1));
  BCM_IF_ERROR_RETURN(tunnel_terminator_setup(unit, tnl_remote_ip_1, tnl_dlf_dip, net_vid_1,
                          tnl_dlf_init_id_1, &tnl_dlf_term_id_1));
  /*
   * Network port 2
   */
  /* Tunnel Setup (UC Initiator & Terminator) */
  BCM_IF_ERROR_RETURN(tunnel_initiator_setup(unit, tnl_local_ip_2, tnl_remote_ip_2, udp_dp, udp_sp, ttl, &tnl_uc_init_id_2));
  BCM_IF_ERROR_RETURN(tunnel_terminator_setup(unit, tnl_remote_ip_2, tnl_local_ip_2, -1, tnl_uc_init_id_2, &tnl_uc_term_id_2));

  /* L3 interface and egress object */
  BCM_IF_ERROR_RETURN(create_l3_interface(unit, 0, net_local_mac_2, net_vid_2, vrf, &net_intf_id_2));
  BCM_IF_ERROR_RETURN(vxlan_create_egr_obj(unit, 0, net_intf_id_2, net_remote_mac_2, network_gport_2, net_vid_2, &net_egr_obj_2));

  /* Create VXLAN VP */
  BCM_IF_ERROR_RETURN(create_vxlan_net_vp(unit, rsvd_network_vpn, 0, network_gport_2, BCM_VXLAN_PORT_MATCH_VN_ID,
                net_egr_obj_2, tnl_uc_init_id_2, tnl_uc_term_id_2, &net_vxlan_port_2));
  print net_vxlan_port_2;

  /* Tunnel Setup (DLF/BC Initiator & Terminator) */
  BCM_IF_ERROR_RETURN(tunnel_initiator_setup(unit, tnl_local_ip_2, tnl_dlf_dip, udp_dp, udp_sp, ttl, &tnl_dlf_init_id_2));
  BCM_IF_ERROR_RETURN(tunnel_terminator_setup(unit, tnl_remote_ip_2, tnl_dlf_dip, net_vid_2,
                          tnl_dlf_init_id_2, &tnl_dlf_term_id_2));

  /*
   * Egress object for DLF/BC VXLAN VP - uses same interface as UC VXLAN network 1
   */
  BCM_IF_ERROR_RETURN(vxlan_create_egr_obj(unit, BCM_L3_IPMC, net_intf_id_1, dlf_mac, network_gport_1, net_vid_1, &egr_obj_dlf));

  /* Create DLF/BC VXLAN VP at network port 1 */
  BCM_IF_ERROR_RETURN(create_vxlan_net_vp(unit, rsvd_network_vpn, BCM_VXLAN_PORT_MULTICAST, network_gport_1,
                      BCM_VXLAN_PORT_MATCH_NONE, egr_obj_dlf,
                      tnl_dlf_init_id_1, tnl_dlf_term_id_1, &vxlan_port_dlf));
  print vxlan_port_dlf;

  /* Station MAC set up */
  BCM_IF_ERROR_RETURN(add_to_l2_station(unit, net_local_mac_1, net_vid_1, BCM_L2_STATION_IPV4));
  BCM_IF_ERROR_RETURN(add_to_l2_station(unit, net_local_mac_2, net_vid_2, BCM_L2_STATION_IPV4));

  /* DLF MC group set up - should contain all Access ports and Network DLF port */
  BCM_IF_ERROR_RETURN(bcm_multicast_vxlan_encap_get(unit, dlf_group, access_gport_1, acc_vxlan_port, &acc_encap_id));
  BCM_IF_ERROR_RETURN(bcm_multicast_egress_add(unit, dlf_group, acc_vxlan_port, acc_encap_id));

  BCM_IF_ERROR_RETURN(bcm_multicast_vxlan_encap_get(unit, dlf_group, network_gport_1, vxlan_port_dlf, &encap_id_dlf));
  BCM_IF_ERROR_RETURN(bcm_multicast_egress_add(unit, dlf_group, vxlan_port_dlf, encap_id_dlf));

  /*
   * Add unicast Payload L2 address to L2 table to avoid DLF flooding
  add_to_l2_table(unit, payload_sa, vpn_id, acc_vxlan_port, 0);
  add_to_l2_table(unit, payload_da_1, vpn_id, net_vxlan_port_1, 0);
  add_to_l2_table(unit, payload_da_2, vpn_id, net_vxlan_port_2, 0);
   */


  /*=====================================
   *
   * Known MC setup : using network port 1
   *
   *====================================*/

  bcm_multicast_t known_mc_group;
  bcm_mac_t known_mc_mac = "01:00:5e:01:01:01";
  bcm_mac_t known_mc_tnl_mac = "01:00:5e:01:01:14";
  bcm_ip_t known_mc_tnl_dip = 0xe0010114;       /* 224.1.1.20 */
  bcm_if_t known_mc_egr_obj;
  int known_mc_vxlan_port;
  bcm_if_t known_mc_encap;
  int known_mc_tnl_init_id, known_mc_tnl_term_id;

  /* Multicast group for the known MC group */
  BCM_IF_ERROR_RETURN(bcm_multicast_create(unit, BCM_MULTICAST_TYPE_VXLAN, &known_mc_group));
  print known_mc_group;

  /* Tunnel Setup (Known MC Initiator & Terminator) */
  BCM_IF_ERROR_RETURN(tunnel_initiator_setup(unit, tnl_local_ip_1, known_mc_tnl_dip, udp_dp, udp_sp, ttl,
                         &known_mc_tnl_init_id));
  BCM_IF_ERROR_RETURN(tunnel_terminator_setup(unit, tnl_remote_ip_1, known_mc_tnl_dip, -1, /* net_vid_1, */
                          known_mc_tnl_init_id, &known_mc_tnl_term_id));

  /* Egress object for known MC VP - uses same interface as UC VXLAN network 1 */
  BCM_IF_ERROR_RETURN(vxlan_create_egr_obj(unit, BCM_L3_IPMC, net_intf_id_1, known_mc_tnl_mac, network_gport_1,
                 net_vid_1, &known_mc_egr_obj));

  /* Create known MC VP */
  BCM_IF_ERROR_RETURN(create_vxlan_net_vp(unit, rsvd_network_vpn, BCM_VXLAN_PORT_MULTICAST, network_gport_1,
                      BCM_VXLAN_PORT_MATCH_VN_ID, known_mc_egr_obj,
                      known_mc_tnl_init_id, known_mc_tnl_term_id, &known_mc_vxlan_port));
  print known_mc_vxlan_port;

  BCM_IF_ERROR_RETURN(add_to_l2_station(unit, known_mc_tnl_mac, net_vid_2, BCM_L2_STATION_IPV4));

  /* Known MC group replication - contain all access VPs & MC VP included in the MC group */
  BCM_IF_ERROR_RETURN(bcm_multicast_vxlan_encap_get(unit, known_mc_group, network_gport_1, known_mc_vxlan_port, &known_mc_encap));
  BCM_IF_ERROR_RETURN(bcm_multicast_egress_add(unit, known_mc_group, known_mc_vxlan_port, known_mc_encap));

  BCM_IF_ERROR_RETURN(bcm_multicast_vxlan_encap_get(unit, known_mc_group, access_gport_1, acc_vxlan_port, &acc_encap_id));
  BCM_IF_ERROR_RETURN(bcm_multicast_egress_add(unit, known_mc_group, acc_vxlan_port, acc_encap_id));

  /* Add MC group address to L2 table */
  bcm_l2_addr_t mc_addr;
  bcm_l2_addr_t_init(&mc_addr, known_mc_mac, vpn_id);
  mc_addr.flags = BCM_L2_STATIC | BCM_L2_MCAST;
  mc_addr.l2mc_group = known_mc_group;
  BCM_IF_ERROR_RETURN(bcm_l2_addr_add (unit, &mc_addr));


  /*=====================================
   *
   * BUD mode IPMC setup
   *
   *====================================*/




  bcm_multicast_t bud_ipmc_group;
  bcm_ipmc_addr_t bud_ipmc_data;
  bcm_if_t bud_ipmc_encap_id;

  /* IPMC packet from Network 1 should go out on Network 2 */
  BCM_IF_ERROR_RETURN(bcm_multicast_create(unit, BCM_MULTICAST_TYPE_L3, &bud_ipmc_group));
  BCM_IF_ERROR_RETURN(bcm_multicast_l3_encap_get(unit, bud_ipmc_group, network_gport_2, net_intf_id_2, &bud_ipmc_encap_id));
  BCM_IF_ERROR_RETURN(bcm_multicast_egress_add(unit, bud_ipmc_group, network_gport_2, bud_ipmc_encap_id));

  bcm_ipmc_addr_t_init(&bud_ipmc_data);
  bud_ipmc_data.s_ip_addr = tnl_remote_ip_1;
  bud_ipmc_data.mc_ip_addr = known_mc_tnl_dip;
  bud_ipmc_data.vid = net_vid_1;
  bud_ipmc_data.ts = 0;
  bud_ipmc_data.port_tgid = network_gport_1;
  bud_ipmc_data.v = 1;
  bud_ipmc_data.group = bud_ipmc_group;
  BCM_IF_ERROR_RETURN(bcm_ipmc_add(unit, &bud_ipmc_data));

  BCM_IF_ERROR_RETURN(tunnel_terminator_bud_update(unit, known_mc_tnl_term_id));


  printf("acc_to_net_mc_bud SUCCESS \n");		

  return BCM_E_NONE;

}

 
 /**************************4 main functions end ***********************/
 
 
 /**************************5 verify functions begin ***********************/
 
 /*
  * send the pkt to verify the script
  * 
  * 
  * 
  */
 void verify(int unit)
 {
	char	  str[512];
	bshell(unit, "hm ieee");
	printf(" \n***************************\n\n\n\n\n");  

	/************************************************************************************************************/  
	printf(" \n **************TEST 1  Multicast initiation access port 1 to network port1 **************\n");	  
	bshell(0, "l2 show ");
	/*
	* 	  01005E0101010000000011BB81000015
	* 	  08004500002E0000000040FF84C40A0A
	* 	  0A01E001010100010203040506070809
	* 	  0A0B0C0D0E0F10111213141516171819		 
	*/

	if (BCM_E_NONE != ingress_port_setup(unit, access_port_1, &access_port_1_eid)) {
	printf("ingress_port_setup() failed for port %d\n", access_port_1);
	return ;
	}

	if (BCM_E_NONE != egress_port_setup(unit, network_port_1, &network_port_1_eid)) {
	printf("egress_port_setup() failed for port %d\n", network_port_1);
	return ;
	} 	  


	/* sent DLF packet */
	snprintf(str, 512,"tx 1 pbm=%d DATA=0x01005E0101010000000011BB8100001508004500002E0000000040FF84C40A0A0A01E0010101000102030405060708090A0B0C0D0E0F10111213141516171819", access_port_1);
	bshell(unit, str);					 
	bshell(0, "sleep 1"); 
	bshell(0, "l2 show ");
	bshell(0, "sleep 1"); 
	bshell(0, " show c");

	/************************************************************************************************************/
	printf(" \n **************TEST 2  Multicast termination(BUD mode) network port1 to  access port 1 and network port2**************\n");	  
	bshell(0, "l2 show ");

	/* 	 
	*		 01005E01011400000000000281000016
	*		 080045000060000000004011D7CEC0A8
	*		 0101E0010114FFFF2118004C00000800
	*		 00000123450001005E01010100000000
	*		 11CC080045000031000100004000D820
	*		 C0A80101E00101010001020304050607
	*		 08090A0B0C0D0E0F1011121314151617
	*		 1819
	*/
	if (BCM_E_NONE != ingress_port_setup(unit, network_port_1, &network_port_1_eid)) {
	printf("ingress_port_setup() failed for port %d\n", network_port_1);
	return ;
	}

	if (BCM_E_NONE != egress_port_setup(unit, access_port_1, &access_port_1_eid)) {
	printf("egress_port_setup() failed for port %d\n", access_port_1);
	return ;
	} 	  

	if (BCM_E_NONE != egress_port_setup(unit, network_port_2, &network_port_2_eid)) {
	printf("egress_port_setup() failed for port %d\n", network_port_2);
	return ;
	} 	    
	/* sent DLF packet */
	snprintf(str, 512,"tx 1 pbm=%d DATA=0x01005E01011400000000000281000016080045000060000000004011D7CEC0A80101E0010114FFFF2118004C0000080000000123450001005E0101010000000011CC080045000031000100004000D820C0A80101E0010101000102030405060708090A0B0C0D0E0F10111213141516171819", network_port_1);
	bshell(unit, str); 					
	bshell(0, "sleep 1"); 
	bshell(0, "l2 show ");
	bshell(0, "sleep 1"); 
	bshell(0, " show c");

	printf(" \n **************destroy the ifp rules************** \n"); 
	destroy_ifp_to_cpu_rule(unit,access_port_1_eid);
	destroy_ifp_to_cpu_rule(unit,network_port_1_eid);
	destroy_ifp_to_cpu_rule(unit,network_port_2_eid);	  

	return ;

 }
 
 /**************************5 verify functions end ***********************/
 
 
 
 ////////////////////////////////////////////////////////////////////////////////////////
 /*
  * This function does the following
  * a)test setup
  * b)actual configuration (Done in config_vxlan_access_to_network_multicast())
  * c)demonstrates the functionality(done in verify()).
  */
 
 bcm_error_t execute()
 {
   bcm_error_t rv;
   int unit =0;
 
   
   printf("**************************** basic information begin****************************\n", bcm_errmsg(rv));	   
   bshell(unit, "config show; a ; version; cancun stat");
   
   printf("**************************** basic information end****************************\n\n", bcm_errmsg(rv));	   
   printf("**************************** test setup begin****************************\n", bcm_errmsg(rv));	   
 
   if (BCM_FAILURE((rv = test_setup(unit)))) {
	 printf("test_setup() failed.\n");
	 return -1;
   }
   printf("**************************** test setup end****************************\n\n", bcm_errmsg(rv));	   
   printf("****************************run main script begin****************************\n", bcm_errmsg(rv));	   
 
   if (BCM_FAILURE((rv = vxlan_access_to_network_bud(unit)))) {
	 printf("vxlan_access_to_access_multicast() Failed\n");
	 return -1;
   }
   printf("****************************run main script end****************************\n\n", bcm_errmsg(rv));	   
   printf("****************************Verify begin****************************\n", bcm_errmsg(rv));	   
 
   verify(unit);
   
   printf("****************************Verify end****************************\n", bcm_errmsg(rv));	   
   return BCM_E_NONE;
 }
 
 const char *auto_execute = (ARGC == 1) ? ARGV[0] : "YES";
 if (!sal_strcmp(auto_execute, "YES")) {
   print execute();
 }


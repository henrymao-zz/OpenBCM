/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

/*
 * Feature  : Vxlan Riot bud mode operation,IPv4 multicast traffic
 *
 * Usage    : BCM.0> cint ipv4_riot_mc_bud.c
 *
 * config   : config_fb6_flex_riot.bcm
 *
 * Log file : ipv4_riot_mc_bud_log.txt
 *
 * Test Topology :
 *
 *                                  +----------------------+
 *                                  |                      |   VLAN-11        Underlay-NextHop
 *                                  |                      | ingress_port       +---+
 *   SMAC 00::01:01                 |                      +--------------------+   |
 *            +---+          VLAN-10|                      |00::bb:bb           +---+
 *  Host1(acc)|   +-----------------+     Firebolt-6       |
 *            +---+  (L3)egress_port|                      |
 *                                  |                      |   VLAN-13        Underlay-NextHop
 *            +---+          VLAN-12|                      | egress_port        +---+
 *  Host2(acc)|   +-----------------+                      +--------------------+   |
 *            +---+  (L2)egress_port|                      |00::04:01           +---+
 *   SMAC 00::02:02                 |                      |
 *                                  |                      |
 *                                  +----------------------+
 *
 * Summary:
 * ========
 * Cint example to demonstrate VxLAN Riot configuration for multicast bud mode operation-
 *
 * Detailed steps done in the CINT script:
 * =======================================
 *   1) Step1 - Test Setup (Done in test_setup()):
 *   =============================================
 *     a) Selects ports for network side and for access side
 *        and configure them in Loopback mode.
 *
 *     b) Install an IFP rule to copy ingress & egress packets to CPU and start
 *        packet watcher.
 *
 *     Note: IFP rule is meant for a verification purpose and is not part of the feature configuration.
 *
 *   2) Step2 - Configuration (Done in config_vxlan_ipv4_vtep()):
 *   =========================================================
 *     a) Configure a VxLAN Riot configuration with SDTAG operations.
 *        Setup network port for routing into vxlan tunnel.
 *        This does the necessary configurations of vxlan global settings, vlan,
 *        access and network port setting, tunnel setup, interface and next hop.
 *
 *   3) Step3 - Verification (Done in verify()):
 *   ===========================================
 *     a) Check the configurations by 'vlan show', 'l2 show',traversing the vpn and vp's
 *
 *     b) Transmit the multicast packet. The contents of the packet
 *        are printed on screen.
 *
 *     c) Expected Result:
 *     ===================
 *       We can see the tunnel terminated packets and ipmc routed packets on the
 *       egress ports respectively
 *       and 'show c' to check the Tx/Rx packet stats/counters.
 */

/*
Packet:

NETWORK multicast:-
packet received on network port

Ingress Packet:
======

Header Info
  ###[ Ethernet ]###
    dst= 01:00:5e:00:01:0a
    src= 00:00:00:00:03:01
    type= 0x8100
  ###[ 802.1Q ]###
     vlan= 11
     type= 0x8000
  ###[ IP ]###
     version= 4
     proto= udp
     dst= 224.0.0.10
     src= 10.10.10.1
  ###[ UDP ]###
     sport= 65535
     dport= 8472
  ###[ VXLAN ]###
     flags= Instance
     reserved1= 0
     vni= 0x12345
     reserved2= 0x0
  ###[ Ethernet ]###
                 src= 00:00:00:00:02:02
                 dst= 01:00:5e:00:10:01
                 type= 0x8100
  ###[ 802.1Q ]###
     vlan= 12
     type= 0x8000
  ###[ IP ]###
        version= 4
        proto= udp
        dst= 224.0.10.1
        src= 30.30.30.1
  ###[ UDP ]###

Ingress Hex Packet:
tx port=1 data=0x01005e00010a0000000003018100000b08004500006400000000401186740a0a0a01e000000affff211800000000080000000123450001005e0010010000000002028100000c080045000032000000004011549b1e1e1e01e0000a0100000000000000000000000000000000000000000000000000000

Egress Packet:
======
IPMC routed copy
{01005e00010a} {000000000401} 8100 000d
0800 4500 0064 0000 0000 3f11 8774 0a0a
0a01 e000 000a ffff 2118 0000 0000 0800
0000 0123 4500 0100 5e00 1001 0000 0000
0202 8100 000c 0800 4500 0032 0000 0000
4011 549b 1e1e 1e01 e000 0a01 0000 0000
0000 0000 0000 0000 0000 0000 0000 0000
0000 0000 0000 4f83 5c24

Access packet L3 copy
{01005e001001} {000000000101} 8100 000a
0800 4500 0032 0000 0000 3f11 559b 1e1e
1e01 e000 0a01 0000 0000 0000 0000 0000
0000 0000 0000 0000 0000 0000 0000 0000
21be 4d26

Access packet L2 copy
{01005e001001} {000000000202} 8100 000c
0800 4500 0032 0000 0000 4011 549b 1e1e
1e01 e000 0a01 0000 0000 0000 0000 0000
0000 0000 0000 0000 0000 0000 0000 0000
7e7d 4fb8
*
*/

/* Reset C interpreter*/
cint_reset();

bcm_port_t ingress_port;
bcm_port_t egress_port[3];
bcm_gport_t ingress_phy_gport;
bcm_gport_t egress_phy_gport[3];

/* struct for Access Port Params for creating access VP*/
struct vxlan_acc_cfg_t {
    bcm_port_t    acc_port;     /*access physical port*/
    bcm_gport_t   phy_Gport;    /*Input : gport of the port/trunk*/
    bcm_vlan_t    acc_vlan;     /*access vlan*/
    bcm_mac_t     acc_ol_mac;   /*payload dst mac*/
    bcm_mac_t     acc_ol_nh_mac;/*payload src mac*/
    bcm_vpn_t     acc_vpn;      /*access vpn*/
    uint32        acc_vpn_vnid; /* dummy for Access side VPN */
    bcm_ip_t      acc_src_ip;   /*payload sip*/
    bcm_ip_t      acc_dest_ip;  /*payload dip*/
    bcm_multicast_t mcast_acc;  /*mcast group*/
    bcm_gport_t   acc_gport;    /* Output:Access VP gport */
};

/* struct for Network Port params for creating network VP*/
struct vxlan_net_cfg_t {
    bcm_port_t    net_port;     /*network physical port*/
    bcm_port_t    phy_Gport;    /*Input : gport of the port/trunk*/
    bcm_vlan_t    net_ol_vlan;  /*overlay payload vlan*/
    bcm_mac_t     net_ol_mac;   /*overlay payload src mac*/
    bcm_mac_t     net_ol_nh_mac; /*overlay payload dst mac*/
    bcm_vlan_t    net_ul_vlan;    /*tunnel vid*/
    bcm_mac_t     net_ul_mac;     /*tunnel src mac*/
    bcm_mac_t     net_ul_nh_mac;  /*tunnel remote mac*/
    bcm_vpn_t     net_vpn;       /*network vpn*/
    uint32        net_vpn_vnid;  /*network tunnel vnid*/
    bcm_ip_t      net_src_ip;  /*tunnel local ip*/
    bcm_ip_t      net_dest_ip; /*tunnel remote ip*/
    bcm_multicast_t mcast_net;  /*mcast group*/
    bcm_gport_t   net_gport;   /*Output:Nw VP gport */
};

/*struct for vxlan setup*/
struct vxlan_cfg_t {
    uint16 udp_src_port;
    uint16 udp_dest_port;
    bcm_vrf_t vrf;  /*routing vrf id*/
    bcm_vpn_t vxlan_vpn;
    uint32    vxlan_vnid;   /*use vnid for vp sharing*/
    bcm_multicast_t mc_group;
};

/*
 * This function is written so that hardcoding of port
 * numbers in cint scripts is removed. This function gives
 * required number of ports
 */
bcm_error_t
portNumbersGet(int unit, int *port_list, int num_ports)
{
    int i = 0, port = 0, rv = BCM_E_NONE;
    bcm_port_config_t configP;
    bcm_pbmp_t ports_pbmp;

    rv = bcm_port_config_get(unit, &configP);
    if (BCM_FAILURE(rv)) {
        printf("\nError in retrieving port configuration: %s\n",bcm_errmsg(rv));
        return rv;
    }

    ports_pbmp = configP.e;
    for (i= 1; i < BCM_PBMP_PORT_MAX; i++) {
        if (BCM_PBMP_MEMBER(&ports_pbmp, i) && (port < num_ports)) {
            port_list[port] = i;
            port++;
        }
    }

    if ((0 == port) || (port != num_ports)) {
        printf("portNumbersGet() failed \n");
        return -1;
    }

    return BCM_E_NONE;
}

/*
 * Configures the port in loopback mode and installs
 * an IFP rule. This IFP rule copies the packets ingressing
 * on the specified port to CPU.
 */
bcm_error_t
ingress_port_multi_setup(int unit, bcm_pbmp_t pbm)
{
    bcm_field_qset_t qset;
    bcm_field_group_t group;
    bcm_field_entry_t entry;
    bcm_port_t     port;

    BCM_FIELD_QSET_INIT(qset);
    BCM_FIELD_QSET_ADD(qset, bcmFieldQualifyInPort);

    BCM_IF_ERROR_RETURN(bcm_field_group_create(unit, qset,
                                            BCM_FIELD_GROUP_PRIO_ANY, &group));

    BCM_PBMP_ITER(pbm, port) {
        printf("ingress_port_multi_setup port: %d\n", port);
        BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, port,
                                                  BCM_PORT_LOOPBACK_MAC));
        BCM_IF_ERROR_RETURN(bcm_port_discard_set(unit, port,
                                                 BCM_PORT_DISCARD_NONE));

        BCM_IF_ERROR_RETURN(bcm_field_entry_create(unit, group, &entry));

        BCM_IF_ERROR_RETURN(bcm_field_qualify_InPort(unit, entry, port,
                                                   BCM_FIELD_EXACT_MATCH_MASK));
        BCM_IF_ERROR_RETURN(bcm_field_action_add(unit, entry,
                                                bcmFieldActionCopyToCpu, 0, 0));

        BCM_IF_ERROR_RETURN(bcm_field_entry_install(unit, entry));
    }
    return BCM_E_NONE;
}

/*
 * Configures the port in loopback mode and installs
 * an IFP rule. This IFP rule copies the packets ingressing
 * on the specified port to CPU. Port is also configured
 * to discard all packets. This is to avoid continuous
 * loopback of the packet.
 */
bcm_error_t
egress_port_multi_setup(int unit, bcm_pbmp_t pbm)
{
    bcm_field_qset_t qset;
    bcm_field_group_t group;
    bcm_field_entry_t entry;
    bcm_port_t     port;

    BCM_FIELD_QSET_INIT(qset);
    BCM_FIELD_QSET_ADD(qset, bcmFieldQualifyInPort);

    BCM_IF_ERROR_RETURN(bcm_field_group_create(unit, qset,
                                        BCM_FIELD_GROUP_PRIO_ANY, &group));

    BCM_PBMP_ITER(pbm, port) {
        printf("egress_port_multi_setup port: %d\n", port);
        BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit,port,
                                                  BCM_PORT_LOOPBACK_MAC));
        BCM_IF_ERROR_RETURN(bcm_port_discard_set(unit, port,
                                                 BCM_PORT_DISCARD_ALL));

        BCM_IF_ERROR_RETURN(bcm_field_entry_create(unit, group, &entry));

        BCM_IF_ERROR_RETURN(bcm_field_qualify_InPort(unit, entry, port,
                                                BCM_FIELD_EXACT_MATCH_MASK));
        BCM_IF_ERROR_RETURN(bcm_field_action_add(unit, entry,
                                                bcmFieldActionCopyToCpu, 0, 0));
        BCM_IF_ERROR_RETURN(bcm_field_action_add(unit,entry,bcmFieldActionDrop,
                                                    0, 0));

        BCM_IF_ERROR_RETURN(bcm_field_entry_install(unit, entry));
    }
    return BCM_E_NONE;
}

/*
 * Test Setup:
 * This functions gets the port numbers and sets up ingress and
 * egress ports. Check ingress_port_multi_setup() and egress_port_multi_setup().
 */
bcm_error_t
test_setup(int unit)
{
    uint32 num_ports = 4;
    int port_list[num_ports];
    bcm_pbmp_t     pbmp;
    int iter = 0;

    if (BCM_E_NONE != portNumbersGet(unit, port_list, num_ports)) {
        printf("portNumbersGet() failed\n");
        return -1;
    }

    egress_port[0] = port_list[1];
    egress_port[1] = port_list[2];
    egress_port[2] = port_list[3];
    ingress_port = port_list[0];

    if (BCM_E_NONE != bcm_port_gport_get(unit, ingress_port,
                                        &(ingress_phy_gport))){
        printf("bcm_port_gport_get() failed to get gport for port %d\n",
                                                            ingress_port);
        return -1;
    }

    for(iter=0;iter<3;iter++){
        if (BCM_E_NONE !=bcm_port_gport_get(unit,egress_port[iter],
            &(egress_phy_gport[iter]))){
            printf("bcm_port_gport_get() failed to get gport for port %d\n",
                    egress_port);
            return -1;
        }
    }

    BCM_PBMP_CLEAR(pbmp);
    BCM_PBMP_PORT_ADD(pbmp, ingress_port);
    if (BCM_E_NONE != ingress_port_multi_setup(unit, pbmp)) {
        printf("ingress_port_multi_setup() failed for port %d\n", ingress_port);
        return -1;
    }

    BCM_PBMP_CLEAR(pbmp);
    for(iter=0;iter<3;iter++){
        BCM_PBMP_PORT_ADD(pbmp, egress_port[iter]);
    }
    if (BCM_E_NONE != egress_port_multi_setup(unit, pbmp)) {
        printf("egress_port_multi_setup() failed for port %d\n", egress_port);
        return -1;
    }

    bshell(unit, "pw start report +raw +decode");

    return BCM_E_NONE;
}

/* verifying the VPN configuration */
bcm_error_t
show_vxlan_vtep_config(int unit)
{
    bcm_flow_vpn_traverse(unit,vpn_traverse,NULL);
    return BCM_E_NONE;
}

/*Verify function call*/
void
verify(int unit)
{
    char str[512];

    bshell(unit, "hm ieee");
    bshell(unit, "vlan show");
    bshell(unit, "l2 show");
    bshell(unit, "l3 defip show");
    bshell(unit, "l3 egress show");
    bshell(unit, "l3 intf show");
    bshell(unit, "clear c");
    printf("\nSending multicast packet to ingress network side:%d\n",
                                                                ingress_port);
    snprintf(str, 512, "tx 1 pbm=%d data=0x01005e00010a0000000003018100000b08004500006400000000401186740a0a0a01e000000affff211800000000080000000123450001005e0010010000000002028100000c080045000032000000004011549b1e1e1e01e0000a0100000000000000000000000000000000000000000000000000000; sleep quiet 1", ingress_port);
    bshell(unit, str);
    bshell(unit, "show c");

    printf("\nverify l2 learning:\n");
    bshell(unit, "l2 show");
    printf("\nverify l3 route hit\n");
    bshell(unit, "ipmc table show");

    /* Dump the Configured VPN & VP's*/
    show_vxlan_vtep_config(unit);

    return;
}

/* Create vlan and add port to vlan */
bcm_error_t
vlan_create_add_port(int unit, int vid, int port)
{
    bcm_pbmp_t pbmp, upbmp;
    bcm_error_t rv = BCM_E_NONE;

    BCM_IF_ERROR_RETURN(bcm_vlan_create(unit, vid));
    BCM_PBMP_CLEAR(pbmp);
    BCM_PBMP_CLEAR(upbmp);
    BCM_PBMP_PORT_ADD(pbmp, port);
    rv = bcm_vlan_port_add(unit, vid, pbmp, upbmp);
    if (BCM_FAILURE(rv)) {
        printf("Error in bcm_vlan_port_add: %s\n", bcm_errmsg(rv));
        return rv;
    }
    return rv;
}

/* vxlan system configuration */
bcm_error_t
vxlan_system_config(int unit, vxlan_cfg_t *vxlan_cfg)
{
    printf("Configure Vxlan global configuration\n");
    BCM_IF_ERROR_RETURN(bcm_switch_control_set(unit, bcmSwitchL3EgressMode, 1));
    BCM_IF_ERROR_RETURN(bcm_switch_control_set(unit, bcmSwitchL3IngressMode,1));
    BCM_IF_ERROR_RETURN(bcm_switch_control_set(unit,
                                         bcmSwitchL3IngressInterfaceMapSet, 1));
    /* L4 Port for VxLAN */
    BCM_IF_ERROR_RETURN(bcm_switch_control_set(unit,
                                               bcmSwitchVxlanUdpDestPortSet,
                                               vxlan_cfg->udp_dest_port));
    BCM_IF_ERROR_RETURN(bcm_switch_control_set(unit,
                                            bcmSwitchVxlanTunnelMissToCpu, 1));
    return BCM_E_NONE;
}

/* vxlan configuration specific to access physical port */
bcm_error_t
vxlan_access_port_config(int unit, bcm_gport_t gport_acc)
{
    printf("Configure Vxlan access port configuration\n");
    BCM_IF_ERROR_RETURN(bcm_vlan_control_port_set(unit, gport_acc,
                                            bcmVlanTranslateIngressEnable, 1));
    BCM_IF_ERROR_RETURN(bcm_port_control_set(unit, gport_acc,
                          bcmPortControlVxlanEnable, 0));
    BCM_IF_ERROR_RETURN(bcm_port_control_set(unit, gport_acc,
                             bcmPortControlVxlanTunnelbasedVnId, 0));
    return BCM_E_NONE;
}

/* vxlan configuration specific to network physical port */
bcm_error_t
vxlan_network_port_config(int unit, bcm_gport_t gport_net)
{
    printf("Configure Vxlan network port configuration\n");
    BCM_IF_ERROR_RETURN(bcm_port_control_set(unit, gport_net,
                            bcmPortControlVxlanEnable, 1));
    BCM_IF_ERROR_RETURN(bcm_port_control_set(unit, gport_net,
                             bcmPortControlVxlanTunnelbasedVnId, 0));
    return BCM_E_NONE;
}

/* Create L3 interface */
bcm_error_t
create_l3_interface(int unit, uint32 flags, bcm_mac_t local_mac, int vid,
                     bcm_if_t *intf_id)
{
    bcm_l3_intf_t l3_intf;
    bcm_error_t rv = BCM_E_NONE;

    /* L3 interface and egress object for access */
    bcm_l3_intf_t_init(&l3_intf);
    l3_intf.l3a_flags |= flags;
    sal_memcpy(l3_intf.l3a_mac_addr, local_mac, sizeof(local_mac));
    l3_intf.l3a_vid = vid;
    rv = bcm_l3_intf_create(unit, &l3_intf);
    *intf_id = l3_intf.l3a_intf_id;
    return rv;
}

bcm_error_t
vxlan_create_egr_obj(int unit, uint32 flag, int l3_if, bcm_mac_t nh_mac,
                     bcm_gport_t gport,
        int vid, bcm_if_t *egr_obj_id)
{
    bcm_l3_egress_t l3_egress;

    bcm_l3_egress_t_init(&l3_egress);
    l3_egress.flags2 |= flag;
    l3_egress.intf  = l3_if;
    sal_memcpy(l3_egress.mac_addr,  nh_mac, sizeof(nh_mac));
    l3_egress.port = gport;
    return bcm_l3_egress_create(unit, 0, &l3_egress, egr_obj_id);
}

bcm_error_t
vxlan_create_mc_egr_obj(int unit, uint32 flag, int l3_if, bcm_mac_t nh_mac,
                        bcm_gport_t gport, bcm_gport_t vxlan_gport,
                        int vid, bcm_if_t *egr_obj_id)
{
    bcm_l3_egress_t l3_egress;
    bcm_if_t vp;
    vp = BCM_GPORT_FLOW_PORT_ID_GET(vxlan_gport);

    bcm_l3_egress_t_init(&l3_egress);
    l3_egress.encap_id = vp;
    l3_egress.flags = BCM_L3_IPMC;
    l3_egress.flags2 |= flag;
    l3_egress.intf  = l3_if;
    sal_memcpy(l3_egress.mac_addr,  nh_mac, sizeof(nh_mac));
    l3_egress.vlan = vid;
    l3_egress.port = gport;
    return bcm_l3_egress_create(unit, 0, &l3_egress, egr_obj_id);
}

bcm_error_t
vxlan_create_l3_ingress(int unit,uint32 flag,bcm_vrf_t vrf,
                        bcm_if_t ol_intf_id,bcm_if_t *ing_obj_id)
{
    bcm_l3_ingress_t l3_ingress;

    bcm_l3_ingress_t_init(&l3_ingress);
    l3_ingress.flags = flag;
    l3_ingress.vrf = vrf;
    *ing_obj_id = ol_intf_id;

    return bcm_l3_ingress_create(unit, &l3_ingress, ing_obj_id);
}

bcm_error_t
vxlan_create_l3_mc_ingress(int unit,uint32 flag,bcm_vrf_t vrf,
                        bcm_if_t ol_intf_id,bcm_if_t *ing_obj_id)
{
    bcm_l3_ingress_t l3_ingress;

    bcm_l3_ingress_t_init(&l3_ingress);
    l3_ingress.flags = flag;
    l3_ingress.vrf = vrf;
    l3_ingress.ipmc_intf_id = ol_intf_id;
    *ing_obj_id = ol_intf_id;

    return bcm_l3_ingress_create(unit, &l3_ingress, ing_obj_id);
}

/*
 * Routine to update vlan profile
 */
bcm_error_t
vlan_vfi_profile_update(int unit, bcm_vlan_t vlan, bcm_vrf_t vrf, bcm_if_t intf)
{
    int rv = BCM_E_NONE;

    /* get vlan control structure */
    bcm_vlan_control_vlan_t vlan_profile;
    bcm_vlan_control_vlan_t_init(&vlan_profile);
    rv = bcm_vlan_control_vlan_get(unit, vlan, &vlan_profile);
    if (BCM_FAILURE(rv)) {
        printf("Error in bcm_vlan_control_vlan_get: %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* modify the profile */
    if (vrf != -1) {
        vlan_profile.vrf = vrf;
    }
    if (intf != BCM_IF_INVALID) {
        vlan_profile.ingress_if = intf;
    }
    /* update profile */
    rv = bcm_vlan_control_vlan_set(unit, vlan, vlan_profile);
    if (BCM_FAILURE(rv)) {
        printf("Error in bcm_vlan_control_vlan_set: %s\n", bcm_errmsg(rv));
        return rv;
    }
    return BCM_E_NONE;
}

/* Create the VPN for vxlan */
bcm_error_t
create_vxlan_vpn(int unit,bcm_multicast_t *vxlan_mc_group,bcm_vpn_t *vxlan_vpn)
{
    bcm_error_t rv = BCM_E_NONE;
    bcm_multicast_t mc_group=0;
    bcm_vpn_t vpn=0;

    printf("create multicast group for UUC/MC/BC\n");
    rv = bcm_multicast_create(unit, BCM_MULTICAST_TYPE_FLOW, &mc_group);
    if (BCM_FAILURE(rv)) {
        printf("\nError in bcm_multicast_create: %s\n", bcm_errmsg(rv));
        return rv;
    }

    bcm_flow_vpn_config_t vpn_info;
    bcm_flow_vpn_config_t_init (&vpn_info);
    vpn_info.flags = BCM_FLOW_VPN_ELAN;
    vpn_info.broadcast_group         = mc_group;
    vpn_info.unknown_unicast_group   = mc_group;
    vpn_info.unknown_multicast_group = mc_group;
    BCM_IF_ERROR_RETURN(bcm_flow_vpn_create(unit, &vpn, &vpn_info));

    *vxlan_mc_group = mc_group;
    *vxlan_vpn = vpn;

    return BCM_E_NONE;
}

/* Common code for Access/Network VP's */
bcm_error_t
create_vxlan_vp(int unit, bcm_vpn_t vpn, uint32 flags, bcm_gport_t *vp)
{
    bcm_error_t rv = BCM_E_NONE;
    bcm_flow_port_t  flow_port;
    bcm_flow_port_t_init(&flow_port);
    flow_port.flags = BCM_FLOW_PORT_SERVICE_TAGGED | flags;
    flow_port.egress_service_tpid = 0x8100;
    rv = bcm_flow_port_create(unit, vpn, &flow_port);
    if (BCM_FAILURE(rv)) {
        printf("Error in bcm_flow_port_create: %s\n", bcm_errmsg(rv));
        return rv;
    }
    *vp = flow_port.flow_port_id;
    return BCM_E_NONE;
}

/* Match criteria configuration */
bcm_error_t
vxlan_flow_match_add(int unit, bcm_flow_match_config_t match_info)
{
    bcm_error_t rv = BCM_E_NONE;
    rv = bcm_flow_match_add(unit, &match_info, 0, NULL);
    if (BCM_FAILURE(rv)) {
        printf("Error in bcm_flow_match_add: %s\n", bcm_errmsg(rv));
        return rv;
    }
    return rv;
}

/* Encap configuration */
bcm_error_t
vxlan_flow_port_encap_set(int unit, bcm_flow_port_encap_t peinfo)
{
    bcm_error_t rv = BCM_E_NONE;
    rv =  bcm_flow_port_encap_set(unit, &peinfo, 0, NULL);
    if (BCM_FAILURE(rv)) {
        printf("Error in bcm_flow_port_encap_set: %s\n", bcm_errmsg(rv));
        return rv;
    }
    return rv;
}

/*
 * Wrapper for L3 Route Creation
 */
bcm_error_t
l3_route_add(int unit, bcm_ip_t ip_addr, bcm_ip_t ip_mask,
                         bcm_vrf_t vrf, bcm_if_t egr_obj)
{
    int rv = BCM_E_NONE;

    bcm_l3_route_t route_t;
    bcm_l3_route_t_init(&route_t);

    route_t.l3a_subnet = ip_addr;
    route_t.l3a_ip_mask = ip_mask;
    route_t.l3a_intf = egr_obj;
    route_t.l3a_vrf = vrf;

    rv = bcm_l3_route_add(unit, &route_t);
    if (BCM_FAILURE(rv)) {
        printf("Error in bcm_l3_route_add: %s\n", bcm_errmsg(rv));
    }
    return rv;
}

/* Create ipmc entry*/
bcm_error_t
create_ipmc_entry(int unit,vxlan_cfg_t *vxlan_cfg,vxlan_net_cfg_t *vxlan_net,
                    bcm_multicast_t mcast_net,bcm_if_t ing_obj)
{
    int rv;
    bcm_ipmc_addr_t ip_mcast;
    bcm_ipmc_addr_t_init(ip_mcast);
    ip_mcast.vid = vxlan_net->net_ul_vlan;
    ip_mcast.port_tgid = vxlan_net->net_port;
    ip_mcast.vrf = vxlan_cfg->vrf;
    ip_mcast.ing_intf = ing_obj;
    ip_mcast.s_ip_addr = vxlan_net->net_src_ip;
    ip_mcast.mc_ip_addr = vxlan_net->net_dest_ip;
    ip_mcast.group = mcast_net;
    ip_mcast.v = 1;

    rv = bcm_ipmc_add(unit, &ip_mcast);
    if (BCM_FAILURE(rv)) {
        printf("\nError in bcm_ipmc_add\n");
        return rv;
    }
    return rv;
}

/*
* VXLAN VP membership
*/
bcm_error_t
vxlan_vp_membership(int unit, bcm_gport_t vxlan_vp, bcm_vpn_t vxlan_vpn)
{
    bcm_error_t rv = BCM_E_NONE;
    rv = bcm_port_vlan_member_set(unit, vxlan_vp, BCM_PORT_VLAN_MEMBER_INGRESS);
    if (BCM_FAILURE(rv)) {
        printf("Error in bcm_port_vlan_member_set: %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_vlan_gport_add(unit, vxlan_vpn, vxlan_vp, 0);
    if (BCM_FAILURE(rv)) {
        printf("Error in bcm_vlan_gport_add: %s\n", bcm_errmsg(rv));
        return rv;
    }
    return rv;
}

/* Create ipmc group */
bcm_error_t
create_l3_ipmc_group(int unit,int flag,bcm_gport_t gport,bcm_if_t intf_id,
                     bcm_multicast_t *mcast)
{
    bcm_multicast_t mcast_group=0;
    bcm_if_t encap_id;
    int flags = flag;

    printf("Create multicast group for 1st pass: IPMC Routing.\n");
    BCM_IF_ERROR_RETURN(bcm_multicast_create(unit, flags, &mcast_group));
    BCM_IF_ERROR_RETURN(bcm_multicast_l3_encap_get(unit,mcast_group,gport,
                                                   intf_id, &encap_id));
    printf("create_l3_ipmc_group l3 encap_id=0x%x\n",encap_id);
    BCM_IF_ERROR_RETURN(bcm_multicast_egress_add(unit,mcast_group,gport,
                                                 encap_id));

    *mcast = mcast_group;

    return BCM_E_NONE;
}

/*
 * Update termination tunnel
 */
bcm_error_t
vxlan_tunnel_term_update(int unit, bcm_gport_t tnl_id, uint32 mflags)
{
    int rv = 0;
    bcm_tunnel_terminator_t tnl_info;
    bcm_tunnel_terminator_t_init(&tnl_info);
    tnl_info.tunnel_id = tnl_id;
    print bcm_vxlan_tunnel_terminator_get(unit, &tnl_info);

    tnl_info.multicast_flag = mflags;
    tnl_info.flags |= BCM_TUNNEL_TERM_TUNNEL_WITH_ID;

    rv = bcm_vxlan_tunnel_terminator_update(unit, &tnl_info);
    return rv;
}

/* Static L2 entry for forwarding */
bcm_error_t
add_to_l2_table(int unit,uint32 flag,bcm_mac_t mac,bcm_vpn_t vpn_id,int port)
{
    bcm_l2_addr_t l2_addr;
    bcm_l2_addr_t_init(&l2_addr, mac, vpn_id);
    l2_addr.flags = flag;
    l2_addr.port = port;
    return bcm_l2_addr_add(unit, &l2_addr);
}

/*
 * Routine to create L2 Station Entry
 */
bcm_error_t
l2_station_add(int unit,bcm_mac_t mac_addr,bcm_vlan_t vlan,bcm_vlan_t vlan_mask,
               int flags,int *station_id)
{
    int rv = BCM_E_NONE;

    bcm_l2_station_t l2_station;
    bcm_l2_station_t_init(&l2_station);

    l2_station.dst_mac = mac_addr;
    l2_station.vlan = vlan;
    l2_station.vlan_mask = vlan_mask;
    l2_station.dst_mac_mask = "FF:FF:FF:FF:FF:FF";
    l2_station.flags = flags;

    return bcm_l2_station_add(unit, *station_id, &l2_station);
}

/* Access Vxlan VP creation */
bcm_error_t
config_vxlan_access(int unit,vxlan_cfg_t *vxlan_cfg,vxlan_acc_cfg_t *vxlan_acc,
                 int l3,bcm_multicast_t acc_mc_group,bcm_gport_t *acc_flow_port)
{
    /* Access Configuartion variables */
    bcm_error_t rv = BCM_E_NONE;
    bcm_if_t      acc_intf_ol;
    bcm_if_t      acc_egr_obj_ul;
    bcm_if_t      acc_egr_obj_ol;
    bcm_if_t      acc_ing_obj = -1;
    int l2_station_acc_ol;
    bcm_mac_t dummy_mac_addr    = "00:00:00:00:00:00";
    bcm_ip_t mask               = 0xFFFFFF00; /*255.255.255.0*/
    bcm_flow_port_encap_t        peinfo;
    bcm_flow_match_config_t      match_info;
    bcm_if_t encap_id;

    rv = vlan_create_add_port(unit, vxlan_acc->acc_vlan, vxlan_acc->acc_port);
    if (BCM_FAILURE(rv)) {
        printf("Error in vlan_create_add_port: %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = vxlan_access_port_config(unit, vxlan_acc->phy_Gport);
    if (BCM_FAILURE(rv)) {
        printf("\nError in vxlan_access_port_config: %s\n", bcm_errmsg(rv));
        return rv;
    }

    if(l3){
        printf("Access: create VPN\n");
        rv = create_vxlan_vpn(unit,vxlan_acc->mcast_acc,vxlan_acc->acc_vpn);
        if (BCM_FAILURE(rv)) {
            printf("\nError in create_vxlan_vpn: %s\n", bcm_errmsg(rv));
            return rv;
        }
    }

    printf("Access: create flow port vp\n");
    rv = create_vxlan_vp(unit, vxlan_acc->acc_vpn, 0, acc_flow_port);
    if (BCM_FAILURE(rv)) {
        printf("\nError in create_vxlan_vp: %s\n", bcm_errmsg(rv));
        return rv;
    }

    vxlan_acc->acc_gport=(*acc_flow_port);
    printf("Access: flow port=0x%x\n",vxlan_acc->acc_gport);

    printf("Access: create UL L3 interface\n");
    rv = vxlan_create_egr_obj(unit,BCM_L3_FLOW_ONLY,BCM_IF_INVALID,
                        dummy_mac_addr,vxlan_acc->phy_Gport,vxlan_acc->acc_vlan,
                              &acc_egr_obj_ul);
    if (BCM_FAILURE(rv)) {
        printf("\nError in vxlan_create_egr_obj: %s\n", bcm_errmsg(rv));
        return rv;
    }

    printf("Access: set encapsulation. VP=>egress-obj{Device,Port}\n");
    bcm_flow_port_encap_t_init(&peinfo);
    peinfo.flow_port = *acc_flow_port;
    peinfo.egress_if = acc_egr_obj_ul;
    peinfo.valid_elements = BCM_FLOW_PORT_ENCAP_PORT_VALID |
        BCM_FLOW_PORT_ENCAP_EGRESS_IF_VALID;
    /*sdtag*/
    peinfo.valid_elements |= (BCM_FLOW_PORT_ENCAP_FLAGS_VALID |
            BCM_FLOW_PORT_ENCAP_TPID_VALID |
            BCM_FLOW_PORT_ENCAP_VLAN_VALID);
    peinfo.vlan = vxlan_acc->acc_vlan;
    peinfo.tpid = 0x8100;
    peinfo.flags = BCM_FLOW_ENCAP_FLAG_SERVICE_TAGGED |
                   BCM_FLOW_ENCAP_FLAG_SERVICE_VLAN_ADD;
    /*end:sdtag*/
    rv = vxlan_flow_port_encap_set(unit, peinfo);
    if (BCM_FAILURE(rv)) {
        printf("Error in vxlan_flow_port_encap_set: %s\n", bcm_errmsg(rv));
        return rv;
    }

    /*
     * Enable L3 routing
     */
    rv = bcm_port_control_set(unit, *acc_flow_port, bcmPortControlIP4, TRUE);
    if (BCM_FAILURE(rv)) {
        printf("Error in bcm_port_control_set: %s\n", bcm_errmsg(rv));
        return rv;
    }

    printf("Access: add flow match (match: port,vlan criteria)\n");
    bcm_flow_match_config_t_init(&match_info);
    match_info.criteria  = BCM_FLOW_MATCH_CRITERIA_PORT_VLAN;
    match_info.port      = vxlan_acc->phy_Gport;
    match_info.vlan      = vxlan_acc->acc_vlan;
    match_info.flow_port = *acc_flow_port;
    match_info.valid_elements = (BCM_FLOW_MATCH_PORT_VALID |
                                 BCM_FLOW_MATCH_VLAN_VALID |
                                 BCM_FLOW_MATCH_FLOW_PORT_VALID);
    rv = vxlan_flow_match_add(unit, match_info);
    if (BCM_FAILURE(rv)) {
        printf("\nError in vxlan_flow_match_add: %s\n", bcm_errmsg(rv));
        return rv;
    }

    if(l3){
        printf("Access: create OL L3 interface\n");
        rv = create_l3_interface(unit,0,vxlan_acc->acc_ol_mac,
                                vxlan_acc->acc_vlan,&acc_intf_ol);
        if (BCM_FAILURE(rv)) {
            printf("\nError in create_l3_interface: %s\n", bcm_errmsg(rv));
            return rv;
        }

        printf("Access: create OL L3 egress object\n");
        rv =vxlan_create_mc_egr_obj(unit,0,acc_intf_ol,vxlan_acc->acc_ol_nh_mac,
                                     vxlan_acc->phy_Gport,vxlan_acc->acc_gport,
                                     vxlan_acc->acc_vlan,&acc_egr_obj_ol);
        if (BCM_FAILURE(rv)) {
            printf("\nError in vxlan_create_mc_egr_obj: %s\n", bcm_errmsg(rv));
            return rv;
        }

        printf("Access: create L3 ingress interface\n");
        rv = vxlan_create_l3_ingress(unit,BCM_L3_INGRESS_REPLACE,vxlan_cfg->vrf,
                                     acc_intf_ol,&acc_ing_obj);
        if (BCM_FAILURE(rv)) {
            printf("\nError in vxlan_create_l3_ingress: %s\n", bcm_errmsg(rv));
            return rv;
        }

        printf("Access: update the vrf field in VFI table\n");
        rv = vlan_vfi_profile_update(unit,vxlan_acc->acc_vpn,vxlan_cfg->vrf,
                                     acc_ing_obj);
        if (BCM_FAILURE(rv)) {
            printf("\nError in vlan_vfi_profile_update: %s\n",bcm_errmsg(rv));
            return rv;
        }

        rv = bcm_multicast_l3_encap_get(unit,acc_mc_group,vxlan_acc->acc_gport,
                                        acc_egr_obj_ol,&encap_id);
        if (BCM_FAILURE(rv)) {
            printf("\nError in bcm_multicast_l3_encap_get: %s\n",
                    bcm_errmsg(rv));
            return rv;
        }
        printf("Access: l3 encap_id=0x%x\n",encap_id);

        rv = bcm_multicast_egress_add(unit,acc_mc_group,vxlan_acc->acc_gport,
                                      encap_id);
        if (BCM_FAILURE(rv)) {
            printf("\nError in bcm_multicast_egress_add: %s\n", bcm_errmsg(rv));
            return rv;
        }

    } else {
        rv = bcm_multicast_l2_encap_get(unit,acc_mc_group,vxlan_acc->phy_Gport,
                                        vxlan_acc->acc_vlan,&encap_id);
        if (BCM_FAILURE(rv)) {
            printf("\nError in bcm_multicast_l2_encap_get: %s\n",
                    bcm_errmsg(rv));
            return rv;
        }
        printf("Access: l2 encap_id=0x%x\n",encap_id);

        rv = bcm_multicast_egress_add(unit,acc_mc_group,vxlan_acc->phy_Gport,
                                      encap_id);
        if (BCM_FAILURE(rv)) {
            printf("\nError in bcm_multicast_egress_add: %s\n", bcm_errmsg(rv));
            return rv;
        }
    }

    return BCM_E_NONE;
}

/* Tunnel creation and associating it with Nw VP */
bcm_error_t
config_vxlan_tunnel(int unit,vxlan_cfg_t *vxlan_cfg, vxlan_net_cfg_t *vxlan_net,
                    bcm_gport_t net_flow_port, bcm_flow_handle_t flow_handle)
{
    /* Tunnel Configuration variables */
    bcm_error_t rv = BCM_E_NONE;
    bcm_flow_tunnel_initiator_t  tiinfo;
    bcm_flow_tunnel_terminator_t ttinfo;

    printf("Tunnel_init: create flow tunnel initiator\n");
    bcm_flow_tunnel_initiator_t_init(&tiinfo);
    tiinfo.flow_handle = flow_handle;
    tiinfo.valid_elements = BCM_FLOW_TUNNEL_INIT_DIP_VALID |
        BCM_FLOW_TUNNEL_INIT_SIP_VALID |
        BCM_FLOW_TUNNEL_INIT_UDP_DPORT_VALID |
        BCM_FLOW_TUNNEL_INIT_UDP_SPORT_VALID |
        BCM_FLOW_TUNNEL_INIT_DSCP_VALID |
        BCM_FLOW_TUNNEL_INIT_TTL_VALID;
    tiinfo.flow_port = net_flow_port;
    tiinfo.type = bcmTunnelTypeVxlan;
    tiinfo.udp_src_port = vxlan_cfg->udp_src_port;
    tiinfo.udp_dst_port = vxlan_cfg->udp_dest_port;
    tiinfo.sip = vxlan_net->net_src_ip;
    tiinfo.dip = vxlan_net->net_dest_ip;
    tiinfo.ttl = 0x3f;
    rv = bcm_flow_tunnel_initiator_create(0,&tiinfo,0,NULL);
    if (BCM_FAILURE(rv)) {
        printf("\nError in bcm_flow_tunnel_initiator_create: %s\n",
                                                             bcm_errmsg(rv));
        return rv;
    }

    printf("Tunnel_term: create flow tunnel terminator\n");
    bcm_flow_tunnel_terminator_t_init(&ttinfo);
    ttinfo.flow_handle = flow_handle;
    ttinfo.multicast_flag = BCM_FLOW_MULTICAST_TUNNEL_STATE_BUD_ENABLE;
    ttinfo.valid_elements = BCM_FLOW_TUNNEL_TERM_DIP_VALID;
    ttinfo.dip = vxlan_net->net_dest_ip;
    ttinfo.type = bcmTunnelTypeVxlan;
    rv = bcm_flow_tunnel_terminator_create(0,&ttinfo,0,NULL);
    if (BCM_FAILURE(rv)) {
        printf("\nError in bcm_flow_tunnel_terminator_create: %s\n",
                                                                bcm_errmsg(rv));
        return rv;
    }
    return BCM_E_NONE;
}

/* vxlan network VP creation . tunnel is not created */
bcm_error_t
config_vxlan_network(int unit,vxlan_cfg_t *vxlan_cfg,vxlan_acc_cfg_t *vxlan_acc,
                     vxlan_net_cfg_t *vxlan_net,bcm_gport_t *net_flow_port,
                     int bud_mode,bcm_multicast_t *ul_mcast_net,
                     bcm_flow_handle_t flow_handle)
{
    /* Network Configuartion variables */
    bcm_error_t rv = BCM_E_NONE;
    bcm_if_t      net_intf_ul;
    bcm_if_t      net_intf_ol;
    bcm_if_t      net_egr_obj_ul;
    bcm_if_t      net_egr_obj_ol;
    bcm_if_t net_ol_ing_obj     = -1;
    bcm_if_t net_ul_ing_obj     = -1;
    int l2_station_net_ul;
    int l2_station_net_ol;
    bcm_ip_t mask  = 0xFFFFFF00; /*255.255.255.0*/
    bcm_flow_port_encap_t        peinfo;
    bcm_flow_match_config_t      match_info;
    bcm_flow_encap_config_t      einfo;

    rv = vlan_create_add_port(unit,vxlan_net->net_ul_vlan,vxlan_net->net_port);
    if (BCM_FAILURE(rv)) {
        printf("\nError in vlan_create_add_port: %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = vxlan_network_port_config(unit, vxlan_net->phy_Gport);
    if (BCM_FAILURE(rv)) {
        printf("\nError in vxlan_network_port_config: %s\n", bcm_errmsg(rv));
        return rv;
    }

    printf("Network: create VPN\n");
    rv = create_vxlan_vpn(unit,vxlan_net->mcast_net,vxlan_net->net_vpn);
    if (BCM_FAILURE(rv)) {
        printf("\nError in create_vxlan_vpn: %s\n", bcm_errmsg(rv));
        return rv;
    }

    printf("Network: create UL L3 interface\n");
    rv = create_l3_interface(unit,0,vxlan_net->net_ul_mac,
                             vxlan_net->net_ul_vlan,&net_intf_ul);
    if (BCM_FAILURE(rv)) {
        printf("\nError in create_l3_interface: %s\n", bcm_errmsg(rv));
        return rv;
    }

    printf("Network: create UL L3 egress object\n");
    rv = vxlan_create_egr_obj(unit,BCM_L3_FLOW_ONLY,net_intf_ul,
                              vxlan_net->net_ul_nh_mac,vxlan_net->phy_Gport,
                              vxlan_net->net_ul_vlan,&net_egr_obj_ul);
    if (BCM_FAILURE(rv)) {
        printf("\nError in vxlan_create_egr_obj: %s\n", bcm_errmsg(rv));
        return rv;
    }

    printf("Network: create UL L3 ingress interface for bud ipmc routing\n");
    rv = vxlan_create_l3_mc_ingress(unit,BCM_L3_INGRESS_REPLACE,vxlan_cfg->vrf,
                                 net_intf_ul,&net_ul_ing_obj);
    if (BCM_FAILURE(rv)) {
        printf("\nError in vxlan_create_l3_mc_ingress: %s\n", bcm_errmsg(rv));
        return rv;
    }

    printf("Network: update the vrf field in VFI table\n");
    rv = vlan_vfi_profile_update(unit,vxlan_net->net_ul_vlan,vxlan_cfg->vrf,
                                 net_ul_ing_obj);
    if (BCM_FAILURE(rv)) {
        printf("\nError in vlan_vfi_profile_update: %s\n", bcm_errmsg(rv));
        return rv;
    }

    printf("Network: create flow port vp\n");
    rv = create_vxlan_vp(unit,vxlan_net->net_vpn,BCM_FLOW_PORT_NETWORK,
                         net_flow_port);
    if (BCM_FAILURE(rv)) {
        printf("\nError in create_vxlan_vp: %s\n", bcm_errmsg(rv));
        return rv;
    }
    vxlan_net->net_gport=*net_flow_port;
    printf("Network: flow port=0x%x\n",vxlan_net->net_gport);

    /*
     * Enable IPMC L3 routing
     */
    rv = bcm_port_control_set(unit,*net_flow_port,bcmPortControlIP4Mcast,TRUE);
    if (BCM_FAILURE(rv)) {
        printf("Error in bcm_port_control_set: %s\n", bcm_errmsg(rv));
        return rv;
    }

    if (bud_mode) {
        printf("Network: encap add, VFI-->VNID\n");
        bcm_flow_encap_config_t_init(&einfo);
        einfo.flow_handle = flow_handle;
        einfo.criteria = BCM_FLOW_ENCAP_CRITERIA_VFI;
        einfo.vnid = vxlan_net->net_vpn_vnid;
        einfo.vpn  = vxlan_net->net_vpn;
        einfo.valid_elements = BCM_FLOW_ENCAP_VNID_VALID |
                               BCM_FLOW_ENCAP_VPN_VALID;
        /*sdtag*/
        einfo.tpid = 0x8100;
        einfo.vlan = vxlan_net->net_ol_vlan;
        einfo.valid_elements |= ( BCM_FLOW_ENCAP_FLAGS_VALID|
                                  BCM_FLOW_ENCAP_TPID_VALID |
                                  BCM_FLOW_ENCAP_VLAN_VALID);
        einfo.flags = BCM_FLOW_ENCAP_FLAG_SERVICE_TAGGED |
                      BCM_FLOW_ENCAP_FLAG_SERVICE_VLAN_ADD;
        /*end:sdtag*/
        rv = bcm_flow_encap_add(unit, &einfo, 0, NULL);
        if (BCM_FAILURE(rv)) {
            printf("\nError in bcm_flow_encap_add: %s\n", bcm_errmsg(rv));
            return rv;
        }

        printf("Network: set encapsulation. VP=>egress-obj{Device,Port}\n");
        bcm_flow_port_encap_t_init(&peinfo);
        peinfo.flow_handle = flow_handle;
        peinfo.flow_port = *net_flow_port;
        peinfo.egress_if = net_egr_obj_ul;
        peinfo.valid_elements = BCM_FLOW_PORT_ENCAP_PORT_VALID |
                                BCM_FLOW_PORT_ENCAP_EGRESS_IF_VALID;
        rv = vxlan_flow_port_encap_set(unit, peinfo);
        if (BCM_FAILURE(rv)) {
            printf("\nError in vxlan_flow_port_encap_set: %s\n",bcm_errmsg(rv));
            return rv;
        }

        printf("Network: create OL L3 interface\n");
        rv = create_l3_interface(unit,0,vxlan_net->net_ol_mac,
                                 vxlan_net->net_ol_vlan,&net_intf_ol);
        if (BCM_FAILURE(rv)) {
            printf("\nError in create_l3_interface: %s\n", bcm_errmsg(rv));
            return rv;
        }

        printf("Network: create OL L3 egress object\n");
        rv=vxlan_create_mc_egr_obj(unit,0,net_intf_ol,vxlan_net->net_ul_nh_mac,
                                     vxlan_net->phy_Gport,vxlan_net->net_gport,
                                     vxlan_net->net_ol_vlan,&net_egr_obj_ol);
        if (BCM_FAILURE(rv)) {
            printf("\nError in vxlan_create_mc_egr_obj: %s\n", bcm_errmsg(rv));
            return rv;
        }

        printf("Network: create L3 ingress interface\n");
        rv = vxlan_create_l3_ingress(unit,BCM_L3_INGRESS_REPLACE,vxlan_cfg->vrf,
                                     net_intf_ol,&net_ol_ing_obj);
        if (BCM_FAILURE(rv)) {
            printf("\nError in vxlan_create_l3_ingress: %s\n", bcm_errmsg(rv));
            return rv;
        }

        printf("Network: update the vrf field in VFI table\n");
        rv = vlan_vfi_profile_update(unit,vxlan_net->net_vpn,vxlan_cfg->vrf,
                                     net_ol_ing_obj);
        if (BCM_FAILURE(rv)) {
            printf("\nError in vlan_vfi_profile_update: %s\n", bcm_errmsg(rv));
            return rv;
        }

        printf("Network: configure match condition to derive VPN (Match:{VN_ID},Derive: VFI (VPN))\n");
        bcm_flow_match_config_t_init(&match_info);
        match_info.flow_handle    = flow_handle;
        match_info.criteria       = BCM_FLOW_MATCH_CRITERIA_VN_ID;
        match_info.vpn            = vxlan_net->net_vpn;
        match_info.vnid           = vxlan_net->net_vpn_vnid;
        match_info.valid_elements = BCM_FLOW_MATCH_VPN_VALID |
                                    BCM_FLOW_MATCH_VNID_VALID;
        rv = vxlan_flow_match_add(unit, match_info);
        if (BCM_FAILURE(rv)) {
            printf("\nError in vxlan_flow_match_add: %s\n", bcm_errmsg(rv));
            return rv;
        }

        printf("Network: add flow match (match: SIP => network SVP)\n");
        bcm_flow_match_config_t_init(&match_info);
        match_info.flow_handle = flow_handle;
        match_info.criteria = BCM_FLOW_MATCH_CRITERIA_SIP;
        match_info.sip = vxlan_net->net_src_ip;
        match_info.flow_port = *net_flow_port;
        match_info.valid_elements = BCM_FLOW_MATCH_SIP_VALID |
                                    BCM_FLOW_MATCH_FLOW_PORT_VALID;
        rv = vxlan_flow_match_add(unit, match_info);
        if (BCM_FAILURE(rv)) {
            printf("\nError in vxlan_flow_match_add: %s\n", bcm_errmsg(rv));
            return rv;
        }

        printf("Network: set egress vlan_xlate key_type for network VP\n");
        BCM_IF_ERROR_RETURN(bcm_vlan_control_port_set(unit, *net_flow_port,
                   bcmVlanPortTranslateEgressKey,bcmVlanTranslateEgressKeyVpn));

        printf("Network: set ipmc entry\n");
        rv = create_ipmc_entry(unit,vxlan_cfg,vxlan_net,*ul_mcast_net,
                               net_ul_ing_obj);
        if (BCM_FAILURE(rv)) {
            printf("\nError in create_ipmc_entry: %s.\n", bcm_errmsg(rv));
            return rv;
        }
    } else {
        rv = create_l3_ipmc_group(unit,BCM_MULTICAST_TYPE_L3,
                                 vxlan_net->phy_Gport,net_intf_ul,ul_mcast_net);
        if (BCM_FAILURE(rv)) {
            printf("\nError in create_l3_ipmc_group: %s.\n", bcm_errmsg(rv));
            return rv;
        }
    }

    return BCM_E_NONE;
}

/* vxlan Configuration function */
bcm_error_t
config_vxlan_ipv4_vtep(int unit)
{
    bcm_error_t rv = BCM_E_NONE;

    /* VPN Configuration variables */
    vxlan_cfg_t vxlan_cfg = {
        0xFFFF, /*udp_src_port*/
        0x2118, /*udp_dest_port*/
        1,      /*vrf*/
        0,      /*vxlan_vpn*/
        0,      /*vxlan_vnid*/
        0       /*mc_group*/
    };

    /*Access port 2nd pass l3 copy*/
    vxlan_acc_cfg_t vxlan_acc_1 = {
        egress_port[1],            /*access physical port*/
        egress_phy_gport[1],       /*gport of the port/trunk*/
        10,                      /*access vlan*/
        "00:00:00:00:01:01",     /*payload dst mac*/
        "01:00:5e:00:10:01",     /*payload src mac*/
        0,                       /*access vpn*/
        0,                       /* dummy for Access side VPN */
        0x1E1E1E01,              /*payload sip*/
        0xE0000a01,              /*payload dip*/
        0,                       /*mcast group*/
        0                        /* Output:Access VP gport */
    };

    /*Access port 2nd pass l2 copy*/
    vxlan_acc_cfg_t vxlan_acc_2 = {
        egress_port[2],            /*access physical port*/
        egress_phy_gport[2],       /*gport of the port/trunk*/
        12,                      /*access vlan*/
        "00:00:00:00:02:02",     /*payload dst mac*/
        "01:00:5e:00:10:01",     /*payload src mac*/
        0,                       /*access vpn*/
        0,                       /* dummy for Access side VPN */
        0x1E1E1E01,              /*payload sip*/
        0xE0000a01,              /*payload dip*/
        0,                       /*mcast group*/
        0                        /* Output:Access VP gport */
    };

    /*Network port ingressing ipmc  traffic*/
    vxlan_net_cfg_t vxlan_net_1 = {
        ingress_port,             /*network physical port*/
        ingress_phy_gport,        /*gport of the port/trunk*/
        12,                      /*overlay payload vlan*/
        "00:00:00:00:02:01",     /*overlay payload src mac*/
        "00:00:00:00:02:02",     /*overlay payload dst mac*/
        11,                      /*tunnel vid*/
        "00:00:00:00:03:01",     /*tunnel src mac*/
        "01:00:5e:00:01:0A",     /*tunnel remote mac*/
        0,                       /*network vpn*/
        0x12345,                 /*network tunnel vnid*/
        0x0a0a0a01,              /*tunnel local ip*/
        0xe000000a,              /*tunnel remote ip*/
        0,                       /*mcast group*/
        0                        /*Output:Nw VP gport */
    };

    /*Network port first pass ipmc routed in underlay domain*/
    vxlan_net_cfg_t vxlan_net_2 = {
        egress_port[0],             /*network physical port*/
        egress_phy_gport[0],        /*gport of the port/trunk*/
        12,                      /*overlay payload vlan*/
        "00:00:00:00:02:01",     /*overlay payload src mac*/
        "00:00:00:00:02:02",     /*overlay payload dst mac*/
        13,                      /*tunnel vid*/
        "00:00:00:00:04:01",     /*tunnel src mac*/
        "01:00:5e:00:01:0A",     /*tunnel remote mac*/
        0,                       /*network vpn*/
        0x12345,                 /*network tunnel vnid*/
        0x14141401,              /*tunnel local ip*/
        0xe000000a,              /*tunnel remote ip*/
        0,                       /*mcast group*/
        0                        /*Output:Nw VP gport */
    };

    /* flow API */
    bcm_flow_handle_t  flow_handle;
    bcm_gport_t   acc_flow_port_1;
    bcm_gport_t   acc_flow_port_2;
    bcm_gport_t   net_flow_port_in;
    bcm_gport_t   net_flow_port_out;

    rv = vxlan_system_config(unit, &vxlan_cfg);
    if (BCM_FAILURE(rv)) {
        printf("\nError in vxlan_system_config: %s\n", bcm_errmsg(rv));
        return rv;
    }

    printf("Enable ipmc in the system\n");
    rv = bcm_ipmc_enable(unit, 1);
    if (BCM_FAILURE(rv)) {
        printf("\nError in bcm_ipmc_enable: %s\n", bcm_errmsg(rv));
        return rv;
    }

    printf("Get flow handler for CLASSIC_VXLAN\n");
    rv = bcm_flow_handle_get(unit, "CLASSIC_VXLAN", &flow_handle);
    if (BCM_FAILURE(rv)) {
        printf("\nError in bcm_flow_handle_get: %s\n", bcm_errmsg(rv));
        return rv;
    }

    printf("Access: create multicast group for 2nd pass=");
    bcm_multicast_t acc_mc_group;
    rv = bcm_multicast_create(unit,BCM_MULTICAST_TYPE_L3,&acc_mc_group);
    if (BCM_FAILURE(rv)) {
        printf("\nError in bcm_multicast_create: %s\n", bcm_errmsg(rv));
        return rv;
    }
    printf("0x%x\n",acc_mc_group);

    printf("\nSetup access VP(L3) on port %d\n", vxlan_acc_1.acc_port);
    rv = config_vxlan_access(unit, &vxlan_cfg, &vxlan_acc_1,1,acc_mc_group,
                             &acc_flow_port_1);
    if (BCM_FAILURE(rv)) {
        printf("\nError in config_vxlan_access: %s\n", bcm_errmsg(rv));
        return rv;
    }

    printf("\nSetup access VP(L2) on port %d\n", vxlan_acc_2.acc_port);
    vxlan_acc_2.mcast_acc = vxlan_acc_1.mcast_acc;
    vxlan_acc_2.acc_vpn = vxlan_acc_1.acc_vpn;
    rv = config_vxlan_access(unit, &vxlan_cfg, &vxlan_acc_2,0,acc_mc_group,
                             &acc_flow_port_2);
    if (BCM_FAILURE(rv)) {
        printf("\nError in config_vxlan_access: %s\n", bcm_errmsg(rv));
        return rv;
    }

    printf("\nAccess: 2nd pass ipmc route add\n");
    /*2nd pass ipmc route add*/
    bcm_ipmc_addr_t ip_mcast;
    bcm_ipmc_addr_t_init(ip_mcast);
    ip_mcast.flags = BCM_IPMC_SOURCE_PORT_NOCHECK;
    ip_mcast.vrf = vxlan_cfg.vrf;
    ip_mcast.s_ip_addr = vxlan_acc_1.acc_src_ip;
    ip_mcast.mc_ip_addr = vxlan_acc_1.acc_dest_ip;
    ip_mcast.group = acc_mc_group;
    ip_mcast.v = 1;

    rv = bcm_ipmc_add(unit, &ip_mcast);
    if (BCM_FAILURE(rv)) {
        printf("\nError in access bcm_ipmc_add\n");
        return rv;
    }

    bcm_multicast_t ul_mcast_net = 0;
    /*create egress network flow port*/
    printf("\nSetup network VP on port %d\n", vxlan_net_2.net_port);
    rv = config_vxlan_network(unit,&vxlan_cfg,&vxlan_acc_1,&vxlan_net_2,
                              &net_flow_port_out,0,&ul_mcast_net,flow_handle);
    if (BCM_FAILURE(rv)) {
        printf("\nError in config_vxlan_network: %s\n", bcm_errmsg(rv));
        return rv;
    }

    /*create ingress network flow port with vnid 0x12345*/
    printf("\nSetup network VP on port %d\n", vxlan_net_1.net_port);
    rv = config_vxlan_network(unit,&vxlan_cfg,&vxlan_acc_1,&vxlan_net_1,
                              &net_flow_port_in,1,&ul_mcast_net,flow_handle);
    if (BCM_FAILURE(rv)) {
        printf("\nError in config_vxlan_network: %s\n", bcm_errmsg(rv));
        return rv;
    }

    /*create vxlan tunnel with network flow port*/
    rv = config_vxlan_tunnel(unit,&vxlan_cfg,&vxlan_net_1,net_flow_port_in,
                             flow_handle);
    if (BCM_FAILURE(rv)) {
        printf("\nError in config_vxlan_tunnel: %s\n", bcm_errmsg(rv));
        return rv;
    }
    return BCM_E_NONE;
}

/* verifying the VPN VP configuration using traverse*/
bcm_error_t
vpn_traverse(int unit,bcm_vpn_t vpn, bcm_flow_vpn_config_t *info, void *data)
{
    int maxArr=20;
    int count=0,iter=0;
    bcm_flow_port_t flow_portArr[maxArr];

    printf("\n Vpn :%d \n",vpn);
    printf("\n VpnInfo : \n");
    print *info;
    BCM_IF_ERROR_RETURN(bcm_flow_port_get_all(unit,vpn,maxArr,
                                                flow_portArr,&count));

    printf("\n Flow Ports %d\n",count);
    for(iter=0;(iter<count) && (iter < maxArr);++iter)
    {
        print flow_portArr[iter];
    }
    return BCM_E_NONE;
}

/*
 * execute:
 *  This function does the following
 *  a) test setup
 *  b) actual configuration (Done in config_vxlan_ipv4_vtep())
 *  c) demonstrates the functionality(done in verify())
 */
bcm_error_t
execute(void)
{
    bcm_error_t rv;
    int unit = 0;
    print "config show; attach; version";
    bshell(unit, "config show; a ; version");

    print "~~~ #1) test_setup(): ** start **";
    if (BCM_FAILURE((rv = test_setup(unit)))) {
        printf("test_setup() failed.\n");
        return -1;
    }
    print "~~~ #1) test_setup(): ** end **";

    print "~~~ #2) config_vxlan_ipv4_vtep(): ** start **";
    if (BCM_FAILURE((rv = config_vxlan_ipv4_vtep(unit)))) {
        printf("config_vxlan_ipv4_vtep() failed.\n");
        return -1;
    }
    print "~~~ #2) config_vxlan_ipv4_vtep(): ** end **";

    print "~~~ #3) verify(): ** start **";
    verify(unit);
    print "~~~ #3) verify(): ** end **";

    return BCM_E_NONE;
}

const char *auto_execute = (ARGC == 1) ? ARGV[0] : "YES";
if (!sal_strcmp(auto_execute, "YES")) {
    print "execute(): Start";
    print execute();
    print "execute(): End";
}

/* 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
* 
* File: cint_dnx_qos_ingress_policer.c
* Purpose: An example of the QoS ingress policer remark out PCP-DEI. 
*
*          Wherever the IVE PCP-DEI is configured to use a mapping of the TM state TC(Traffic Class)-DP (Drop Precedence), 
*          a better mapping will take into account the meter color of the packet as the more current Drop Precedence value. 
*          The following CINT provides a calling sequence example to map TC-DP to PCP-DEI in two mode: simple mode and advance mode. 
*          In simple mode, bcm_port_control_set API can directly set DP profile ID which will be used with the port for both outer tag PCP-DEI and 
*          inner tag PCP-DEI. A new SOC property is needed in simple mode.
*          In advance mode, bcm_port_control_set API  set  DP proifle ID which will be used with the port for out tag PCP-DEI or inner tag PCP-DEI.
*          It should be noted that policer map will share the port class with other feature in advance mode. if port class changed and policer map is working 
*          in advance mode, then the QOS map ID should be set again. 
*          DP profile map Ingress-DP and selected PCP-DEI by IVE to new PCP-DEI
* Calling sequence:
*
* Initialization:
*          set the mode which policer map work, default is simple mode
*
* Set up sequence:
*  1. Create QOS LIF
*        - Call bcm_vlan_port_create() with criterias BCM_VLAN_PORT_MATCH_PORT_VLAN  and following flags:
*                BCM_VLAN_PORT_OUTER_VLAN_PRESERVE | BCM_VLAN_PORT_INNER_VLAN_PRESERVE
*  2. Set QOS LIF ingress VLAN editor.
*        - Call bcm_vlan_translate_action_create()
*  3. Cross connect the 2 LIFs
*        - Call bcm_vswitch_cross_connect_add()
*  4. Create QOS ingress remark DP map and add to INLIF (remark ingress DP) 
*  5. Create QOS DP map mapping PCP-DEI and set to INLIF (simple or advance mode)
*        - Call bcm_port_control_set ()
*
* Clean up sequence:
*  1. Delete the cross connected LIFs.
*        - Call bcm_vswitch_cross_connect_delete()
*  2. Delete QOS LIFs.
*        - Call bcm_vlan_port_destroy()
*  3. Distroy QOS map profile.
*        - Call bcm_qos_map_destroy()
*
* Service Model:
* Ingress QOS remark profile
*      remark IP packet DP to bcmColorGreen
* DP profile 1:
*     bcmColorGreen ----------------------PCP-DEI 12 (PCP = 6, DEI =0)
* Mapping 
*     outer/inner  tag -----DP profile 1

* Traffic:
*  1.  VLAN tag: 
          TPID 0x8100, VID 10, priority 2
          TPID 0x9100, VID 10, priority 3
*  2.  output packet : 
*           outer/inner tag pcp=6, dei = 0
*           TPID 0x8100, VID 11, priority 2
*           TPID 0x9100, VID 12, priority 3
*
* To Activate Above Settings Run:
 * Test Scenario - start
       cint examples/sand/utility/cint_sand_utils_global.c
       cint examples/dnx/qos/cint_dnx_qos_ingress_policer.c
       cint
       qos_color_mapping_pcp_init($unit, $mode);
       policer_remark_pcp_example($unit, $inPort, $outPort);
       qos_policer_clean($unit);
 * Test Scenario - end
*/

/********** 
  Globals/Aux Variables
 ********** */

struct qos_mapping_pcp_info_s {
    /* The cross connection will be between port pin with vlan vid and port pout and vlan vid+1. */
    int vid; 
    /*ingress phb map id*/
    int ingress_map_id;
    /*the new_pcp_dei will be set to this value for the expected traffic.*/
    int new_pcp_dei;
    /* The id to use for bcm_qos_map_create. If -1, no id is used. */
    int qos_policer_map_id;
    /*in lif*/
    bcm_port_t gport_in;
    /*out lif*/
    bcm_port_t gport_out;
};

qos_mapping_pcp_info_s default_qos_pcp_mapping_info = {
    10, /*vid*/
    -1,  /*ingress mapp id*/
    12,  /*new_pcp_dei*/
    1,  /*qos_policer_map_id*/
    0, /*in lif*/
    0   /*out lif*/
};

/* debug prints */
verbose = 3;

/********** 
  functions
 ********** */
/*  Map: Incoming-EXP (exp) -> TC (int_pri), DP (color)*/
int
dnx_qos_policer_ingress_remark_profile(int unit)
{
    bcm_qos_map_t l3_ing_map;
    int dscp;
    int flags = 0;
    int opcode_id;
    int map_id;

    /*allocate opcode*/
    flags =  BCM_QOS_MAP_INGRESS | BCM_QOS_MAP_PHB | BCM_QOS_MAP_OPCODE;
    BCM_IF_ERROR_RETURN_MSG(bcm_qos_map_create(unit, flags, &opcode_id), "");
    /*allocate profile*/
    flags = BCM_QOS_MAP_INGRESS | BCM_QOS_MAP_PHB | BCM_QOS_MAP_REMARK;
    BCM_IF_ERROR_RETURN_MSG(bcm_qos_map_create(unit, flags, &map_id), "");

    bcm_qos_map_t_init(&l3_ing_map);
    flags = BCM_QOS_MAP_PHB | BCM_QOS_MAP_OPCODE | BCM_QOS_MAP_L3 | BCM_QOS_MAP_IPV4;
    l3_ing_map.opcode = opcode_id;
    BCM_IF_ERROR_RETURN_MSG(bcm_qos_map_add(unit, flags, &l3_ing_map, map_id), "");
    /* 
     * Ingress DSCP profile Maps:
     * Incoming-DSCP -> TC (int_pri), DP (color)
     */
    flags = BCM_QOS_MAP_L3 | BCM_QOS_MAP_IPV4 | BCM_QOS_MAP_PHB;
    for(dscp = 0; dscp < 256; dscp++)
    {
        bcm_qos_map_t_init(&l3_ing_map);
        l3_ing_map.dscp             = dscp;
        l3_ing_map.int_pri      = 4;
        l3_ing_map.color            = bcmColorGreen;
        l3_ing_map.remark_int_pri   = dscp;
        l3_ing_map.opcode   = 0;
        BCM_IF_ERROR_RETURN_MSG(bcm_qos_map_add(unit, flags, &l3_ing_map, opcode_id), "");
    }

    default_qos_pcp_mapping_info.ingress_map_id = map_id;
    return BCM_E_NONE;
}

int dnx_qos_policer_map_create(int unit, int qos_profile_id, int new_pcp_dei){
    char error_msg[200]={0,};
    int dp_idx, sel_pcp_dei;
    int qos_create_flags;
    bcm_qos_map_t map;
    int new_pcp, new_dei;

    qos_create_flags = BCM_QOS_MAP_INGRESS | BCM_QOS_MAP_POLICER;
    if (qos_profile_id != -1) {
        qos_create_flags |= BCM_QOS_MAP_WITH_ID;
    }

    BCM_IF_ERROR_RETURN_MSG(bcm_qos_map_create(unit, qos_create_flags, &qos_profile_id),
        "for flags BCM_QOS_MAP_INGRESS and BCM_QOS_MAP_POLICER.");

    if (verbose >= 2) {
        printf("created Qos mapid (0x%x) for new pcp_dei (%d)\n", qos_profile_id, new_pcp_dei);
    }

    bcm_qos_map_t_init(&map);
    new_pcp = new_pcp_dei >> 1;
    new_dei = new_pcp_dei & 0x1;
    
    for (dp_idx = 0; dp_idx < 4; dp_idx++) {
        for (sel_pcp_dei = 0; sel_pcp_dei < 16; ++sel_pcp_dei){
            map.color = dp_idx; /*DP */
            map.remark_int_pri = sel_pcp_dei; /* IVE selected PCP-DEI */
            map.pkt_pri= new_pcp; /* PCP */
            map.pkt_cfi= new_dei; /* DEI */
            snprintf(error_msg, sizeof(error_msg), "(0,BCM_QOS_MAP_POLICER, map=<dp=%d,sel_pcp_dei=%d,pcp=%d,dei=%d>,map_id=%d).",
                dp_idx, sel_pcp_dei, new_pcp, new_dei, qos_profile_id);
            BCM_IF_ERROR_RETURN_MSG(bcm_qos_map_add(unit, BCM_QOS_MAP_POLICER, &map, qos_profile_id), error_msg);
        }
    }

    default_qos_pcp_mapping_info.qos_policer_map_id = qos_profile_id;

    return BCM_E_NONE;
}

int dnx_qos_cross_connect(int unit, int port_in, int port_out, int vid)
{
    bcm_vlan_port_t vp;
    int i;
    int tag_format_s_c =16;
    int s_tpid = 0x9100;
    int c_tpid = 0x8100;
    int ports[2];
    int gport[2];
    bcm_vlan_port_t in_vlan_port, out_vlan_port;
    int action_id = 1;
    bcm_vlan_action_set_t action;
    bcm_vlan_translate_action_class_t action_class;
    bcm_vlan_port_translation_t port_trans;
    bcm_vswitch_cross_connect_t gports_conn;
    bcm_vlan_t vsi;
    
    BCM_IF_ERROR_RETURN_MSG(tpid__tpids_clear_all(unit), "");

    BCM_IF_ERROR_RETURN_MSG(tpid__tpid_add(unit, c_tpid), "");

    BCM_IF_ERROR_RETURN_MSG(tpid__tpid_add(unit, s_tpid), "");
    /** Incoming-packet recognize s_c_format */
    BCM_IF_ERROR_RETURN_MSG(port_tpid_class_add(unit, port_in, s_tpid, c_tpid, tag_format_s_c), "");
    
    /** After IVE recognize s_c_format */
    BCM_IF_ERROR_RETURN_MSG(port_tpid_class_add(unit, port_out, s_tpid, c_tpid, tag_format_s_c), "");

    ports[0] = port_in;
    ports[1] = port_out;    
    
    for (i = 0; i < sizeof(ports) / sizeof(ports[0]); i++) {
        bcm_vlan_port_t_init(&vp);
        vp.criteria = BCM_VLAN_PORT_MATCH_PORT_VLAN_STACKED;
        vp.port = ports[i];
        /* +i - This is instead of setting different port domains for the ports. */
        /* Otherwise, both port domains and vlans will be equal and thus we will have equal lifs. */
        vp.match_vlan = vid+i;
        vp.match_inner_vlan = vid+1+i; 
        vp.vsi = 0; /* will be populated when the gport is added to service, using vswitch_port_add */

        if (verbose >= 2) {
            printf("Adding port %d to vlan %d...\n", ports[i], vid+i);
        }
        
        BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_create(unit, &vp), "");

        printf("The gport for port %d, vlan %d is 0x%x.\n", vp.port, vp.match_vlan, vp.vlan_port_id);
        gport[i] = vp.vlan_port_id;

        BCM_IF_ERROR_RETURN_MSG(bcm_vlan_gport_add(unit, vid, ports[0], 0), "");
    }

    default_qos_pcp_mapping_info.gport_in = gport[0];
    default_qos_pcp_mapping_info.gport_out = gport[1];

    bcm_vswitch_cross_connect_t_init(&gports_conn);
    gports_conn.port1 = gport[0];
    gports_conn.port2 = gport[1];

    /*create action id*/
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_translate_action_id_create(unit, BCM_VLAN_ACTION_SET_INGRESS, &action_id), "ing");
    print action_id;

    bcm_vlan_action_set_t_init(&action);
    action.flags = BCM_VLAN_ACTION_SET_INGRESS;
    action.dt_outer = bcmVlanActionReplace;
    action.dt_inner = bcmVlanActionReplace;
    action.new_outer_vlan = vid+1;
    action.new_inner_vlan = vid+2;
    action.dt_outer_pkt_prio = bcmVlanActionReplace;
    action.dt_inner_pkt_prio = bcmVlanActionReplace;
    action.outer_tpid = 0x9100;
    action.inner_tpid = 0x8100;
    action.outer_tpid_action = bcmVlanTpidActionNone;
    action.inner_tpid_action = bcmVlanTpidActionNone;
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_translate_action_id_set( unit, BCM_VLAN_ACTION_SET_INGRESS, action_id, &action), "");

    /* Set translation action class for s_tag packets */
    bcm_vlan_translate_action_class_t_init(&action_class);
    action_class.vlan_edit_class_id = 1;
    action_class.tag_format_class_id = 16;
    action_class.vlan_translation_action_id = action_id;
    action_class.flags = BCM_VLAN_ACTION_SET_INGRESS;
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_translate_action_class_set(unit,  &action_class), "egr");

    bcm_vlan_port_translation_t_init(&port_trans);
	port_trans.new_outer_vlan = vid+2;
    port_trans.new_inner_vlan = vid+2;
    port_trans.gport = gport[0];
    port_trans.vlan_edit_class_id = 1;
    port_trans.flags = BCM_VLAN_ACTION_SET_INGRESS;
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_translation_set(unit, &port_trans), "");

    if (verbose >= 2) {
        printf("Cross connecting the ports...\n");
    }
    
    /* cross connect two lifs for tagged service */
    BCM_IF_ERROR_RETURN_MSG(bcm_vswitch_cross_connect_add(unit, &gports_conn), "");

    return BCM_E_NONE;
}

  
/* 
 * Example of: 
 * IVE PCP-DEI. 
 *  
 * packet will be routed from in_port to out-port 
 * 
 * packet to send: 
 *  - in port = in_port
 *  - vlan 10.
 *  - DA = {0x00, 0x0c, 0x00, 0x02, 0x00, 0x00}
 *  - DIP = 0x7fffff03 (127.255.255.3)
 *  
 * expected: 
 *  - out port = out_port
 *  - vlan 11.
 *  - DA = {0x00, 0x00, 0x00, 0x00, 0xcd, 0x1d}
 *  - SA = {0x00, 0x0c, 0x00, 0x02, 0x00, 0x00}
 *  TTL decremented
 *  vlan PCP-DEI according to mapping
 */
int policer_remark_pcp_example(int unit, int in_port, int out_port){

    char error_msg[200]={0,};
    int map_id;
    int in_vlan;
    int out_vlan;
    int gport_in;
    int gport_out;
    int simple;
    uint32 inlif_profile;
    int dp_profile;
    
    in_vlan = default_qos_pcp_mapping_info.vid;
    out_vlan = in_vlan+1; /* The value is based on the cross_connect function. */

    /* Cross connect in_port,vlan 10 to out_port,vlan 11 */
    if (verbose >= 2) {
        printf("Doing port setup (cross connect port %d vlan %d to port %d vlan %d)...\n", in_port, in_vlan, out_port, out_vlan);
    }

    BCM_IF_ERROR_RETURN_MSG(dnx_qos_cross_connect(unit, in_port, out_port, in_vlan), "doing port setup.");

    gport_in = default_qos_pcp_mapping_info.gport_in;
    gport_out = default_qos_pcp_mapping_info.gport_out;
    
    if (verbose >= 2) {
        printf("gport_in is 0x%x, gport_out is 0x%x.\n", gport_in, gport_out);
    }

    /*remark ingress DP*/
    BCM_IF_ERROR_RETURN_MSG(dnx_qos_policer_ingress_remark_profile(unit), "");
    
    BCM_IF_ERROR_RETURN_MSG(bcm_qos_port_map_set(unit,gport_in, default_qos_pcp_mapping_info.ingress_map_id, -1), "");
    
    /*create qos map for tag*/
    map_id = default_qos_pcp_mapping_info.qos_policer_map_id;
    if (verbose >= 2) {
        printf("to create qos profile %d for outer vlan tag.\n", map_id);
    }
    BCM_IF_ERROR_RETURN_MSG(dnx_qos_policer_map_create(unit, map_id, default_qos_pcp_mapping_info.new_pcp_dei), "");

    /*set profile for outer tag*/
    map_id = default_qos_pcp_mapping_info.qos_policer_map_id;

    if (verbose >= 2) {
        printf("Setting the qos profile for outer vlan tag to %d.\n", map_id);
    }
    snprintf(error_msg, sizeof(error_msg), "(%d,0x%x,bcmPortControlOuterPolicerRemark,%d)", unit, gport_in, map_id);
    BCM_IF_ERROR_RETURN_MSG(bcm_port_control_set(unit, gport_in, bcmPortControlOuterPolicerRemark, map_id), error_msg);
    snprintf(error_msg, sizeof(error_msg), "(%d,0x%x,bcmPortClassFieldIngress,%d)", unit, gport_in, map_id);
    BCM_IF_ERROR_RETURN_MSG(bcm_port_control_get(unit, gport_in, bcmPortControlOuterPolicerRemark, &map_id), "");

    /*set profile for  inner tag*/
    if (verbose >= 2) {
        printf("Setted the qos profile for inner vlan tag to %d.\n", map_id);
    }
    snprintf(error_msg, sizeof(error_msg), "(%d,0x%x,bcmPortControlInnerPolicerRemark,%d)", unit, gport_in, map_id);
    BCM_IF_ERROR_RETURN_MSG(bcm_port_control_set(unit, gport_in, bcmPortControlInnerPolicerRemark, map_id), error_msg);
    snprintf(error_msg, sizeof(error_msg), "(%d,0x%x,bcmPortControlInnerPolicerRemark,%d)", unit, gport_in, map_id);
    BCM_IF_ERROR_RETURN_MSG(bcm_port_control_get(unit, gport_in, bcmPortControlInnerPolicerRemark, &map_id), error_msg);

    return BCM_E_NONE;
}

int qos_policer_clean(int unit)
{
    char error_msg[200]={0,};
    int map_id;

    bcm_vswitch_cross_connect_t gports;
    qos_mapping_pcp_info_s info = default_qos_pcp_mapping_info;

    map_id = info.qos_policer_map_id;
    snprintf(error_msg, sizeof(error_msg), "%d", map_id);
    BCM_IF_ERROR_RETURN_MSG(bcm_qos_map_destroy(unit, map_id), error_msg);

    if (verbose >= 2) {
        printf("qos_policer_clean outer map..\n");
    }
    
    map_id = info.ingress_map_id;
    snprintf(error_msg, sizeof(error_msg), "%d", map_id);
    BCM_IF_ERROR_RETURN_MSG(bcm_qos_map_destroy(unit, map_id), error_msg);

    if (verbose >= 2) {
        printf("qos_policer_clean ingress ..\n");
    }

    /* Delete the cross connected LIFs */
    gports.port1 = info.gport_in;
    gports.port2 = info.gport_out;
    BCM_IF_ERROR_RETURN_MSG(bcm_vswitch_cross_connect_delete(unit, &gports), "");

    /* Delete IN LIF */
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_destroy(unit, info.gport_in), "");

    /* Delete OUT LIF */
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_destroy(unit, info.gport_out), "");
    return BCM_E_NONE;
}


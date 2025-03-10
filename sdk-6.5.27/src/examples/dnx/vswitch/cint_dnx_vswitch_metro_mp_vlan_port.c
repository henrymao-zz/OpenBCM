/*
 * 
 This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 
 Copyright 2007-2022 Broadcom Inc. All rights reserved. 
 */
/*
 * An example of L2VPN Metro Multi-point UC traffic scenario
 * VLAN-Port sending to other VLAN-Port through MACT
 * 
 * Test Scenario 
 * Test Scenario - start
  cint ../../../../src/examples/dnx/utility/cint_dnx_utils_global.c
  cint ../../../../src/examples/dnx/utility/cint_dnx_utils_tpid.c
  cint ../../../../src/examples/dnx/cint_dnx_vswitch_metro_mp_vlan_port.c
  cint
  basic_example(0,200,201);
  exit;
 *
 * VSWITCH MP packet 
  tx 1 psrc = 200 data = 0x000000000001000000000100910000648100012cffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 * 
 * Received Data:
 * 0x0000000000010000000001009100025881000320ffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f2000000000000000 
 * Test Scenario - end
 */

/*
 * Utilities APIs
 */
/*
 * add L2 entry points to the given gport
 */
int
vswitch_add_l2_addr_to_gport(
    int unit,
    int gport_id,
    bcm_mac_t mac,
    int vsi)
{
    bcm_gport_t g1;
    bcm_l2_addr_t l2_addr1;

    /*
     * local: MACT, add entry points to local-port 
     */
    bcm_l2_addr_t_init(&l2_addr1, mac, vsi);
    l2_addr1.flags = BCM_L2_STATIC;     /* static entry */
    g1 = gport_id;
    l2_addr1.port = g1;
    BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_add(unit, &l2_addr1), "");

    return BCM_E_NONE;
}

int
port_tpid_class_add(
    int unit,
    int port,
    int tpid1,
    int tpid2,
    int tag_format)
{
    bcm_port_tpid_class_t port_tpid_class;

    bcm_port_tpid_class_t_init(&port_tpid_class);
    port_tpid_class.port = port;
    port_tpid_class.tpid1 = tpid1;
    port_tpid_class.tpid2 = tpid2;
    port_tpid_class.tag_format_class_id = tag_format;

    BCM_IF_ERROR_RETURN_MSG(bcm_port_tpid_class_set(unit, &port_tpid_class), "");

    return BCM_E_NONE;
}

int
vlan_translation_create_and_set(
    int unit,
    int is_ingress,
    int action_id,
    bcm_vlan_action_t outer_vid_source,
    bcm_vlan_action_t inner_vid_source,
    uint16 outer_tpid,
    uint16 inner_tpid)
{
    int flags;
    bcm_vlan_action_set_t action;

    bcm_vlan_action_set_t_init(&action);

    /*
     * Create new Action IDs 
     */
    flags = (is_ingress) ? BCM_VLAN_ACTION_SET_INGRESS : BCM_VLAN_ACTION_SET_EGRESS;
    flags |= BCM_VLAN_ACTION_SET_WITH_ID;
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_translate_action_id_create(unit, flags, &action_id), "");

    /*
     * Fill Action 
     */
    action.dt_outer = outer_vid_source;
    action.dt_inner = inner_vid_source;
    action.outer_tpid = outer_tpid;
    action.inner_tpid = inner_tpid;
    action.dt_outer_pkt_prio = bcmVlanActionAdd;
    action.dt_inner_pkt_prio = bcmVlanActionAdd;
    flags = (is_ingress) ? BCM_VLAN_ACTION_SET_INGRESS : BCM_VLAN_ACTION_SET_EGRESS;

    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_translate_action_id_set(unit, flags, action_id, &action), "");

    return BCM_E_NONE;
}

int
vlan_translate_action_map_set(
    int unit,
    int is_ingress,
    int action_id,
    int tag_format,
    int vlan_port_edit_prfoile)
{
    bcm_vlan_translate_action_class_t action_class;
    bcm_vlan_translate_action_class_t_init(&action_class);

    action_class.vlan_edit_class_id = vlan_port_edit_prfoile;
    action_class.tag_format_class_id = tag_format;
    action_class.vlan_translation_action_id = action_id;
    action_class.flags = (is_ingress) ? BCM_VLAN_ACTION_SET_INGRESS : BCM_VLAN_ACTION_SET_EGRESS;;
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_translate_action_class_set(unit, &action_class), "");

    return BCM_E_NONE;
}

/*
 * For now use VLAN create
 */
int
vswitch_create(
    int unit,
    int vsi_id)
{

    BCM_IF_ERROR_RETURN_MSG(bcm_vswitch_create_with_id(unit, vsi_id), "");
    return BCM_E_NONE;
}

int
vswitch_vlan_port_create(
    int unit,
    int vlan_port_id,
    int port,
    int vsi,
    uint32 flags,
    /*
     * Ingress information 
     */
    int match_outer_vid,
    int match_inner_vid,
    int criteria,
    int ingress_vlan_edit_profile,
    /*
     * Egress information 
     */
    int egress_outer_vid,
    int egress_inner_vid,
    int egress_vlan_edit_profile,
    int is_p2p)
{
    bcm_vlan_port_t vp;
    bcm_vlan_port_translation_t port_trans;

    bcm_vlan_port_t_init(&vp);
    bcm_vlan_port_translation_t_init(&port_trans);

    /*
     * create vlan-port 
     */
    vp.criteria = criteria;
    vp.port = port;
    vp.match_vlan = match_outer_vid;
    vp.match_inner_vlan = match_inner_vid;
    vp.flags = BCM_VLAN_PORT_WITH_ID | flags;
    vp.vlan_port_id = vlan_port_id;
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_create(unit, &vp), "");

    if (!(vp.flags & BCM_VLAN_PORT_CREATE_EGRESS_ONLY))
    {
        port_trans.new_outer_vlan = 1000;
        port_trans.new_inner_vlan = 2000;
        port_trans.gport = vlan_port_id;
        port_trans.vlan_edit_class_id = ingress_vlan_edit_profile;
        port_trans.flags = BCM_VLAN_ACTION_SET_INGRESS;
        BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_translation_set(unit, &port_trans), "");
    }

    if (!(vp.flags & BCM_VLAN_PORT_CREATE_INGRESS_ONLY))
    {
        port_trans.new_outer_vlan = egress_outer_vid;
        port_trans.new_inner_vlan = egress_inner_vid;
        port_trans.gport = vlan_port_id;
        port_trans.vlan_edit_class_id = egress_vlan_edit_profile;
        port_trans.flags = BCM_VLAN_ACTION_SET_EGRESS;
        BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_translation_set(unit, &port_trans), "");
    }

    /*
     * add to vswitch for p2mp case
     */
    if (is_p2p == 0)
    {
        BCM_IF_ERROR_RETURN_MSG(bcm_vswitch_port_add(unit, vsi, vlan_port_id), "");
    }
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_gport_add(unit, match_outer_vid, port, 0), "");

    return BCM_E_NONE;
}

/*
int unit = 0;
int in_port = 200;
int out_port = 201;
 */
int
vswitch_metro_vlan_port_config(
    int unit,
    int in_port,
    int out_port,
    int is_p2p)
{
    char error_msg[200]={0,};
    int s_tpid = 0x9100;
    int c_tpid = 0x8100;
   /*
   * In JR2 - D-tag must be in the range [16:23] 
   */
    int tag_format_s_c = 16;
    int tag_format_untag = 0;
    int ingress_action_id = 5;
    int egress_action_id = 6;
    int in_vlan_port_edit_prfoile = 2;
    int out_vlan_port_edit_prfoile = 3;
    int vsi_id = 10;
    int in_vlan_port_id = 10000;
    int out_vlan_port_id = 10010;
    int match_outer_vid1 = 100;
    int match_outer_vid2 = 200;
    int match_inner_vid1 = 300;
    int match_inner_vid2 = 400;
    int egress_outer_vid1 = 500;
    int egress_outer_vid2 = 600;
    int egress_inner_vid1 = 700;
    int egress_inner_vid2 = 800;
    bcm_mac_t da = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };      /* DA */

    BCM_GPORT_SUB_TYPE_LIF_SET(in_vlan_port_id, 0, in_vlan_port_id);
    BCM_GPORT_VLAN_PORT_ID_SET(in_vlan_port_id, in_vlan_port_id);
    BCM_GPORT_SUB_TYPE_LIF_SET(out_vlan_port_id, 0, out_vlan_port_id);
    BCM_GPORT_VLAN_PORT_ID_SET(out_vlan_port_id, out_vlan_port_id);

    /*
     * 1. Set global TPIDs 
     */
    BCM_IF_ERROR_RETURN_MSG(tpid__tpids_clear_all(unit), "");

    BCM_IF_ERROR_RETURN_MSG(tpid__tpid_add(unit, c_tpid), "");

    BCM_IF_ERROR_RETURN_MSG(tpid__tpid_add(unit, s_tpid), "");

    /*
     * 2. Set LLVP configuration 
     */
    /*
     * Incoming-packet recognize s_c_format 
     */
    BCM_IF_ERROR_RETURN_MSG(port_tpid_class_add(unit, in_port, s_tpid, c_tpid, tag_format_s_c), "");
    /*
     * After IVE recognize untag_format 
     */
    BCM_IF_ERROR_RETURN_MSG(port_tpid_class_add(unit, out_port,
                             BCM_PORT_TPID_CLASS_TPID_INVALID, BCM_PORT_TPID_CLASS_TPID_INVALID, tag_format_untag), "");

    /*
     * 3. IVE action settings - Delete VLANs 
     */
    BCM_IF_ERROR_RETURN_MSG(vlan_translation_create_and_set(unit, 1 /* Ingress */ , ingress_action_id,
                                         bcmVlanActionDelete, bcmVlanActionDelete, 0x9100, 0x8100), "");

    /*
     * 4. EVE action settings - Add VLANs 
     */
    BCM_IF_ERROR_RETURN_MSG(vlan_translation_create_and_set(unit, 0 /* Egress */ , egress_action_id,
                                         bcmVlanActionAdd, bcmVlanActionAdd, 0x9100, 0x8100), "");

    /*
     * 5. Map LLVP and VLAN Port profile to Action 
     */
    BCM_IF_ERROR_RETURN_MSG(vlan_translate_action_map_set(unit, 1 /* Ingress */ , ingress_action_id,
                                       tag_format_s_c, in_vlan_port_edit_prfoile), "");
    BCM_IF_ERROR_RETURN_MSG(vlan_translate_action_map_set(unit, 0 /* Egress */ , egress_action_id,
                                       tag_format_untag, out_vlan_port_edit_prfoile), "");

    /*
     * 6. VPN create 
     */
    BCM_IF_ERROR_RETURN_MSG(vswitch_create(unit, vsi_id), "");

    /*
     * 7. Create VLAN-Ports 
     */
    BCM_IF_ERROR_RETURN_MSG(vswitch_vlan_port_create(unit, in_vlan_port_id, in_port, vsi_id, 0,
                                  match_outer_vid1, match_inner_vid1, BCM_VLAN_PORT_MATCH_PORT_VLAN_STACKED,
                                  in_vlan_port_edit_prfoile, egress_outer_vid1, egress_inner_vid1,
                                  out_vlan_port_edit_prfoile, is_p2p), "");
    BCM_IF_ERROR_RETURN_MSG(vswitch_vlan_port_create(unit, out_vlan_port_id, out_port, vsi_id, 0,
                                  match_outer_vid2, match_inner_vid2, BCM_VLAN_PORT_MATCH_PORT_VLAN_STACKED,
                                  in_vlan_port_edit_prfoile, egress_outer_vid2, egress_inner_vid2,
                                  out_vlan_port_edit_prfoile, is_p2p), "");

    /*
     * 8. Add MACT entry 
     */
    if (is_p2p)
    {
        bcm_vswitch_cross_connect_t gports;
        bcm_vswitch_cross_connect_t_init(&gports);
        gports.port1 = in_vlan_port_id;
        gports.port2 = out_vlan_port_id;
        snprintf(error_msg, sizeof(error_msg), "in cross connect port1(0x%08X) <--> port2(0x%08X)", gports.port1, gports.port2);
        BCM_IF_ERROR_RETURN_MSG(bcm_vswitch_cross_connect_add(unit, &gports), error_msg);
    }
    else
    {
        BCM_IF_ERROR_RETURN_MSG(vswitch_add_l2_addr_to_gport(unit, out_vlan_port_id, da, vsi_id), "");
    }

    return BCM_E_NONE;
}

int
vswitch_metro_vlan_port_mp_main(
    int unit,
    int in_port,
    int out_port)
{
    return vswitch_metro_vlan_port_config(unit, in_port, out_port, 0);
}

int
vswitch_metro_vlan_port_p2p_main(
    int unit,
    int in_port,
    int out_port)
{
    return vswitch_metro_vlan_port_config(unit, in_port, out_port, 1);
}

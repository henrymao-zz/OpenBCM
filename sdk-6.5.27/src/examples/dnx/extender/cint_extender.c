/* 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
*/

/*
 * Purpose: The CINT demonstrates a Controlling bridge configuration as part of a Port Extender (802.BR) application.
 *
 * 1. The basic example handles UC traffic with no protection.
 *    Packets can be sent from/to a cascaded port or an End station.
 * 2. A new match can be added to an existing extender port using port_extender_cb_uc_match_add.
 * 3. The previously created new match can be removed using port_extender_cb_uc_match_delete
 *
 *                                                                         Network
 *                                                                       | Port
 *                                                                       |
 *                                                    ___________________|__________________
 *                 __________                        |                                      |                           __________
 *        LIF 1 __|          |                       |         Controlling Bridge           |                          |          |__  LIF 3
 *        LIF 2 __|   Port   | --------------------->|------------------------------------> |------------------------->|  Port    |__
 *              __|          |      In-Cascaded-Port |                    |    /\           | Out-Cascaded-Port        |          |__
 *              __| Extender | <---------------------|<-------------------|    |            |                          | Extender |__
 *                |__________|                       |                    |    |            |                          |__________|
 *                                                   |                    |    |            |
 *                             _____________         |                    |    |            |
 *                            |             |<------ |<-------------------     |            |
 *                  LIF4(AC)  | End Station |        |                         |            |
 *                            |_____________|------->|-------------------------             |
 *                                                   |                                      |
 *                                                   |______________________________________|
 *
 * Test Scenario
 *  1. UC service test 
 * Test Scenario - start
  cint ../../../../src/examples/sand/utility/cint_sand_utils_global.c
  cint ../../../../src/examples/sand/utility/cint_sand_utils_l2.c
  cint ../../../../src/examples/dnx/extender/cint_extender.c
  cint ../../../../src/examples/sand/cint_l2_basic_bridge_with_vlan_editing.c
  cint ../../../../src/examples/sand/utility/cint_sand_utils_vlan_translate.c
  cint ../../../../src/examples/sand/utility/cint_sand_utils_global.c
  cint
  port_extender_cb_uc_run_with_customized_para(0,200,201,202,10);
  exit;
 *
 *  Received packets on unit 0 should be: 
 *  Source port: 200, Destination port: 201 
 *  Data: 0x00aabbcc000000000001893ff00000cb000081000067ffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f200000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 
 *
 *  Sending ETH packet 
  tx 1 psrc=202 data=0x000000aabbcc00000000000181000064ffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 *
 *  Received packets on unit 0 should be: 
 *  Source port: 202, Destination port: 201 
 *  Data: 0x00aabbcc000000000001893ff00000cb000081000067ffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f200000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 
 *
 *  Received packets on unit 0 should be: 
 *  Source port: 201, Destination port: 202 
 *  Data: 0x00445566000000aabbcc81000064ffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f2000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 
 * Test Scenario - end
 *
 * 2. MC service test
 * Test Scenario
 *
 * Test Scenario - start
  cint ../../../../src/examples/sand/utility/cint_sand_utils_global.c
  cint ../../../../src/examples/sand/utility/cint_sand_utils_l2.c
  cint ../../../../src/examples/dnx/extender/cint_extender.c
  cint ../../../../src/examples/sand/cint_l2_basic_bridge_with_vlan_editing.c
  cint ../../../../src/examples/sand/utility/cint_sand_utils_vlan_translate.c
  cint ../../../../src/examples/sand/utility/cint_sand_utils_global.c
  cint
  port_extender_cb_uc_run_with_customized_para(0,200,201,202,10);
  exit;
 *
 *  Received packets on unit 0 should be: 
 *  Source port: 200, Destination port: 201 
 *  Data: 0x00aabbcd000000000001893f000010c900008100006508004500003500000000800026c40a0000050a000001000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 
 *  Source port: 200, Destination port: 201 
 *  Data: 0x00aabbcd0000000000018100006408004500003500000000800026c40a0000050a000001000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f200000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 
 *  Source port: 200, Destination port: 202 
 *  Data: 0x00aabbcd000000000001893ff00010cb00008100006708004500003500000000800026c40a0000050a000001000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 
 *  Source port: 200, Destination port: 10 
 *  Data: 0x00aabbcd000000000001893f000010ca00008100006608004500003500000000800026c40a0000050a000001000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 
 * Test Scenario - end
 *
*/

/* **************************************************************************************************
  --------------          Global Variables Definition and Initialization  START     -----------------
 **************************************************************************************************** */
int NOF_EXTENDER_PORTS = 4;
int EXTENDER_IN_LIF_WIDE_DATA_ENABLE = 0;

struct port_extender_cascaded_port_s
{
    bcm_gport_t port;
};

struct port_extender_end_station_s
{
    bcm_gport_t port;
    bcm_vlan_port_match_t match_criteria;
    bcm_vlan_t vid;
    bcm_vlan_t inner_vid;
    bcm_gport_t vlan_port_id;   /* The LIF ID */
};

struct extender_port_extender_port_s
{
    bcm_gport_t port;
    bcm_vlan_t tag_vid;         /* Outer C-VID */
    uint16 extender_vid;        /* Extended-Port E-CID */
    bcm_gport_t extender_gport_id;      /* The LIF ID */
};

/*  Main Struct  */
struct port_extender_cb_uc_s
{
    port_extender_cascaded_port_s cascaded_port[NOF_EXTENDER_PORTS];
    extender_port_extender_port_s extender_port[NOF_EXTENDER_PORTS];
    port_extender_end_station_s end_station;
    bcm_vlan_t vsi;
};

/* Initialization of global struct*/
port_extender_cb_uc_s g_port_extender_cb_uc = { /* Cascaded Ports configuration Phy Port Tag Format */
    {{13},      /* In-Cascaded-Port */
     {13},      /* In-Cascaded-Port (Out) */
     {14},      /* Out-Cascaded-Port */
     {14}},     /* Out-Cascaded-Port */

    /*
     * Extender Ports configuration Phy Port Tag VID Extender VID Extender gport ID 
     */
    {{13, 101, 201, 0}, /* LIF 1 */
     {13, 102, 202, 0}, /* LIF 2 */
     {14, 103, 203, 0}, /* LIF 3 */
     {14, 103,   204, 0}  /* LIF 4, un-tag */
     },

    /*
     * End Station configuration Phy Port match criteria Tag VID Tag format vlan_port_id
     */
    {15, BCM_VLAN_PORT_MATCH_PORT_VLAN, 100, 4, 0},

    /*
     * Additional parameters 
     */
    12, /* VSI */
};

/* **************************************************************************************************
  --------------          Global  Variables Definitions and Initialization  END       ---------------
 **************************************************************************************************** */

/**
 * Configuration of cascaded port
 * Enable the 802.1BR tag encapsulation on the port
 * Enable the 802.1BR tag identify and tag swap on the port.
 *
 * INPUT:
 *   cascaded port id.
 */
int
extender_cascaded_port_configure(
    int unit,
    int port)
{
    char error_msg[200]={0,};
    int value = 0;

    /*
     * Enable prepend operation for the port 
     */
    snprintf(error_msg, sizeof(error_msg), "for bcmSwitchPrependTagEnable, port - %d", port);
    BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_port_set(unit, port, bcmSwitchPrependTagEnable, 1), error_msg);

    /*
     * Configure the Port Extender Port-type to be a Cascaded Port 
     */
    snprintf(error_msg, sizeof(error_msg), "for bcmPortControlExtenderType to SWITCH, port - %d", port);
    BCM_IF_ERROR_RETURN_MSG(bcm_port_control_set(unit, port, bcmPortControlExtenderType, BCM_PORT_EXTENDER_TYPE_SWITCH), error_msg);

    snprintf(error_msg, sizeof(error_msg), "for bcmPortControlExtenderType to SWITCH, port - %d", port);
    BCM_IF_ERROR_RETURN_MSG(bcm_port_control_get(unit, port, bcmPortControlExtenderType, &value), error_msg);
    if (value != BCM_PORT_EXTENDER_TYPE_SWITCH)
    {
        printf("Error, value != BCM_PORT_EXTENDER_TYPE_SWITCH, port - %d\n", port);
        return BCM_E_FAIL;
    }

    /*
     * Configure the Port vlan domain 
     */
    snprintf(error_msg, sizeof(error_msg), "for bcmPortClassId  , port - %d", port);
    BCM_IF_ERROR_RETURN_MSG(bcm_port_class_set(unit, port, bcmPortClassId, port), error_msg);

    return BCM_E_NONE;
}

/**
 * Configuration default vlan edit action for LIF
 * IVE default action: remove one tag
 * EVE default action: add one tag.
 *
 * INPUT:
 *   gport   - gport ID
 *   is_ive  - ive/eve
 *   eve_new_vid vlan to be added by eve.
 */
int
extender_lif_vlan_edit_default_action_config(
    int unit,
    bcm_gport_t gport,
    int is_ive,
    int eve_new_vid)
{
    char error_msg[200]={0,};
    if (is_ive)
    {
        snprintf(error_msg, sizeof(error_msg), "(setting gport 0x%x EVE action)", gport);
        BCM_IF_ERROR_RETURN_MSG(vlan_translate_ive_eve_translation_set_with_pri_action(unit, gport,        /* outlif */
                                                                    0x8100,     /* outer_tpid */
                                                                    0,  /* inner_tpid */
                                                                    bcmVlanTpidActionNone,      /* Outer tpid action
                                                                                                 * modify */
                                                                    bcmVlanTpidActionNone,      /* Inner tpid action
                                                                                                 * modify */
                                                                    bcmVlanActionDelete,        /* outer_action */
                                                                    bcmVlanActionNone,  /* inner_action */
                                                                    bcmVlanActionNone,        /* outer_pri_action */
                                                                    bcmVlanActionNone,  /* inner_pri_action */
                                                                    0,  /* new_outer_vid */
                                                                    0,  /* new_inner_vid */
                                                                    0,  /* vlan_edit_profile */
                                                                    4,  /* tag_format: stag */
                                                                    TRUE        /* is_ive */
            ), error_msg);

    }
    else
    {
        snprintf(error_msg, sizeof(error_msg), "(setting gport 0x%x EVE action)", gport);
        BCM_IF_ERROR_RETURN_MSG(vlan_translate_ive_eve_translation_set_with_pri_action(unit, gport,        /* outlif */
                                                                    0x8100,     /* outer_tpid */
                                                                    0,  /* inner_tpid */
                                                                    bcmVlanTpidActionNone,      /* Outer tpid action
                                                                                                 * modify */
                                                                    bcmVlanTpidActionNone,      /* Inner tpid action
                                                                                                 * modify */
                                                                    bcmVlanActionAdd,   /* outer_action */
                                                                    bcmVlanActionNone,  /* inner_action */
                                                                    bcmVlanActionAdd,   /* outer_pri_action */
                                                                    bcmVlanActionNone,  /* inner_pri_action */
                                                                    eve_new_vid,        /* new_outer_vid */
                                                                    0,  /* new_inner_vid */
                                                                    0,  /* vlan_edit_profile */
                                                                    0,  /* tag_format: untag */
                                                                    FALSE       /* is_ive */
            ), error_msg);

    }

    return BCM_E_NONE;
}

/**
 * Add one entry into bud group
 * INPUT:
 *   port - destination port
 *   encap  - lif ID
 */
int
extender_add_entry_into_flood_group(
    int unit,
    int port,
    int encap,
    int mcid)
{

    char error_msg[200]={0,};
    int flags;
    bcm_multicast_replication_t rep_array;

    flags = BCM_MULTICAST_INGRESS_GROUP;
    bcm_multicast_replication_t_init(&rep_array);

    rep_array.port = port;
    rep_array.encap1 = encap;
    snprintf(error_msg, sizeof(error_msg), "in Port= %d,encap = 0x%x", port, encap);
    BCM_IF_ERROR_RETURN_MSG(bcm_multicast_add(unit, mcid, flags, 1, &rep_array), error_msg);
    return BCM_E_NONE;
}

/**
 * Create a externder port
 * INPUT:
 *   extender_port_info   - extender port infomation
 *   is_mc  is multicast extender port(egress only)
 */
int
extender_port_configure(
    int unit,
    extender_port_extender_port_s * extender_port_info,
    int is_mc,
    int is_untag)
{

    char error_msg[200]={0,};
    bcm_extender_port_t extender_port;
    bcm_extender_forward_t fwd_entry;

    /*
     * Format the supplied LIF info to the Port-Extender struct 
     */
    bcm_extender_port_t_init(&extender_port);
    extender_port.port = extender_port_info->port;
    extender_port.flags = is_mc ? BCM_EXTENDER_PORT_MULTICAST : 0;
    
    if (EXTENDER_IN_LIF_WIDE_DATA_ENABLE == TRUE)
    {
        extender_port.flags |= BCM_EXTENDER_PORT_INGRESS_WIDE;
    }
    extender_port.match_vlan = extender_port_info->tag_vid;
    extender_port.extended_port_vid = extender_port_info->extender_vid;
    if (!is_untag)
    {
        extender_port.criteria = BCM_EXTENDER_PORT_MATCH_PORT_EXTENDED_PORT_VLAN;
    }
    else
    {
        extender_port.criteria = BCM_EXTENDER_PORT_MATCH_PORT_EXTENDED_UNTAGGED;
    }
    extender_port.pcp_de_select = BCM_EXTENDER_PCP_DE_SELECT_OUTER_TAG;

    /*
     * Call the API to create the Port Extender object 
     */
    snprintf(error_msg, sizeof(error_msg), "port - %d, vlan - %d, E-TAG - %d", extender_port.port,
        extender_port.match_vlan, extender_port.extended_port_vid);
    BCM_IF_ERROR_RETURN_MSG(bcm_extender_port_add(unit, &extender_port), error_msg);

    printf("Extender port params. port: %d, VLAN: %d ECID: %d\n", extender_port_info->port, extender_port_info->tag_vid,
           extender_port_info->extender_vid);

    extender_port_info->extender_gport_id = extender_port.extender_port_id;

    /*
     * IVE: remove vlan
     */
    if (!is_mc)
    {
        BCM_IF_ERROR_RETURN_MSG(extender_lif_vlan_edit_default_action_config(unit, extender_port.extender_port_id, 1, 0), "");
    }

    /*
     * EVE: add match vlan
     */
    BCM_IF_ERROR_RETURN_MSG(extender_lif_vlan_edit_default_action_config(unit, extender_port.extender_port_id, 0, extender_port.match_vlan), "");

    return BCM_E_NONE;
}

/* Configuration of a Port Extender single Extender LIF
 * Create the object(LIF), associate it with a VSI and define an EVE operation.
 *
 * INPUT:
 *   extender_port_info: Configuration info for a single Extender LIF.
 */
int
port_extender_cb_uc_set_extender_lif(
    int unit,
    extender_port_extender_port_s * extender_port_info)
{

    char error_msg[200]={0,};

    /*
     * Attach the Extender-Port to a specific VSI 
     */
    snprintf(error_msg, sizeof(error_msg), "vsi - %d, extender_port_id - %d", g_port_extender_cb_uc.vsi,
        extender_port_info->extender_gport_id);
    BCM_IF_ERROR_RETURN_MSG(bcm_vswitch_port_add(unit, g_port_extender_cb_uc.vsi, extender_port_info->extender_gport_id), error_msg);
    printf("Allocated extender_port_id - %x\n", extender_port_info->extender_gport_id);

    /**
      * Add into the bud group
      */
    BCM_IF_ERROR_RETURN_MSG(extender_add_entry_into_flood_group(unit, extender_port_info->port,
                                             BCM_GPORT_SUB_TYPE_LIF_VAL_GET(extender_port_info->extender_gport_id),
                                             g_port_extender_cb_uc.vsi), "");
    return BCM_E_NONE;
}

/* Configuration of a Port Extender End station
 * Handles the port's TPIDs - The profile and the tag format classification,
 * creates the AC LIF and associates it with a VSI.
 * No EVE is defined as the C-VID in this example is the same across all the
 * interfaces.
 *
 * INPUT:
 *   end_station_info: Configuration info for a single End station
 */
int
port_extender_cb_uc_set_end_station(
    int unit,
    port_extender_end_station_s * end_station_info)
{

    char error_msg[200]={0,};
    bcm_vlan_port_t vlan_port;
    bcm_vlan_port_translation_t vp_translation;

    /*
     * Create an AC LIF 
     */
    bcm_vlan_port_t_init(&vlan_port);

    vlan_port.criteria = end_station_info->match_criteria;
    vlan_port.port = end_station_info->port;
    vlan_port.match_vlan = end_station_info->vid;
    vlan_port.match_inner_vlan = end_station_info->inner_vid;

    snprintf(error_msg, sizeof(error_msg), "for port - %d, vlan - %d", end_station_info->port, end_station_info->vid);
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_create(unit, &vlan_port), error_msg);
    end_station_info->vlan_port_id = vlan_port.vlan_port_id;

    /*
     * Attach the AC LIF to the Controller Bridge VSI 
     */
    snprintf(error_msg, sizeof(error_msg), "vsi - %d, vlan_port_id - %d", g_port_extender_cb_uc.vsi, vlan_port.vlan_port_id);
    BCM_IF_ERROR_RETURN_MSG(bcm_vswitch_port_add(unit, g_port_extender_cb_uc.vsi, vlan_port.vlan_port_id), error_msg);

    /*
     * IVE:remove the tag
     */
    BCM_IF_ERROR_RETURN_MSG(extender_lif_vlan_edit_default_action_config(unit, vlan_port.vlan_port_id, 1, 0), "");

    /*
     * EVE: add match vlan
     */
    BCM_IF_ERROR_RETURN_MSG(extender_lif_vlan_edit_default_action_config(unit, vlan_port.vlan_port_id, 0, vlan_port.match_vlan), "");

    /**
      * Add into the bud group
      */
    BCM_IF_ERROR_RETURN_MSG(extender_add_entry_into_flood_group(unit, vlan_port.port,
                                             BCM_GPORT_SUB_TYPE_LIF_VAL_GET(vlan_port.vlan_port_id),
                                             g_port_extender_cb_uc.vsi), "");

    return BCM_E_NONE;
}

/*
 * Main function to run the Port Extender Control Bridge UC example
 *
 * Main steps of configuration:
 *    1. Set Cascaded Ports
 *    2. Set Port-Extender LIFs
 *    3. Set an End Station
 *
 * INPUT: unit  - unit
 *        param - NULL for default params, or new values.
 */
int
port_extender_cb_uc_run(
    int unit)
{
    char error_msg[200]={0,};
    int rv, idx;
    bcm_extender_forward_t fwd_entry;
    bcm_pbmp_t p, u;
    int flags = 0;
    bcm_mac_t mac1 = {0x00, 0x00, 0x00, 0x44, 0x55, 0x66};
    bcm_mac_t mac2 = {0x00, 0x00, 0x00, 0xaa, 0xbb, 0xcc};
    bcm_mac_t mac3 = {0x00, 0x00, 0x00, 0x11, 0x22, 0x33};
    int ac_vlan = 100;
    int extender1_pay_vlan = 101;
    int extender2_pay_vlan = 103;
    int mc_id = g_port_extender_cb_uc.vsi;
    bcm_vlan_control_vlan_t vlan_control;

    /*
     * Create the vlan first
     */
    rv = bcm_vlan_control_vlan_get(unit, g_port_extender_cb_uc.vsi, &vlan_control);
    if (rv == BCM_E_NONE) {
        BCM_IF_ERROR_RETURN_MSG(bcm_vlan_destroy(unit, g_port_extender_cb_uc.vsi), "");
    }
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_create(unit, g_port_extender_cb_uc.vsi), "");
    BCM_PBMP_PORT_SET(p, g_port_extender_cb_uc.extender_port[0].port);
    BCM_PBMP_PORT_SET(p, g_port_extender_cb_uc.extender_port[2].port);
    BCM_PBMP_PORT_SET(p, g_port_extender_cb_uc.end_station.port);

    BCM_PBMP_ASSIGN(u, p);
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_add(unit, g_port_extender_cb_uc.vsi, p, u), "");
    snprintf(error_msg, sizeof(error_msg), "for vlan vsi %d", g_port_extender_cb_uc.vsi);
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_gport_add(unit, extender1_pay_vlan, g_port_extender_cb_uc.cascaded_port[0].port, 0), error_msg);
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_gport_add(unit, ac_vlan, g_port_extender_cb_uc.end_station.port, 0), error_msg);
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_gport_add(unit, extender2_pay_vlan, g_port_extender_cb_uc.extender_port[2].port, 0), error_msg);

    /**
      * Configure the bud group
      */
    flags = (BCM_MULTICAST_WITH_ID | BCM_MULTICAST_INGRESS_GROUP);
    BCM_IF_ERROR_RETURN_MSG(bcm_multicast_create(unit, flags, &mc_id), "");

    for (idx = 0; idx < NOF_EXTENDER_PORTS; idx++)
    {
        /*
         * Configure the cascased port property
         */
        snprintf(error_msg, sizeof(error_msg), "for port #%d", idx);
        BCM_IF_ERROR_RETURN_MSG(extender_cascaded_port_configure(unit, g_port_extender_cb_uc.cascaded_port[idx].port), error_msg);

        /*
         * Configure Port-Extender LIFs 
         */

        snprintf(error_msg, sizeof(error_msg), "for LIF #%d", idx);
        BCM_IF_ERROR_RETURN_MSG(extender_port_configure(unit, &g_port_extender_cb_uc.extender_port[idx], 0, (idx==(NOF_EXTENDER_PORTS-1))?1:0), error_msg);

        BCM_IF_ERROR_RETURN_MSG(port_extender_cb_uc_set_extender_lif(unit, &g_port_extender_cb_uc.extender_port[idx]), error_msg);
    }

    /*
     * Configure an End Station 
     */
    BCM_IF_ERROR_RETURN_MSG(port_extender_cb_uc_set_end_station(unit, &g_port_extender_cb_uc.end_station), "");

    /*
     * Configure a mac address for the endpoint. 
     */
    BCM_IF_ERROR_RETURN_MSG(l2__mact_entry_create(unit, mac1, g_port_extender_cb_uc.vsi, g_port_extender_cb_uc.end_station.vlan_port_id), "");

    /*
     * Configure a mac address for the out cascade port. 
     */
    BCM_IF_ERROR_RETURN_MSG(l2__mact_entry_create(unit, mac2, g_port_extender_cb_uc.vsi, g_port_extender_cb_uc.extender_port[2].extender_gport_id), "");

    /*
     * Configure a mac address for the in cascade port. 
     */
    BCM_IF_ERROR_RETURN_MSG(l2__mact_entry_create(unit, mac3, g_port_extender_cb_uc.vsi, g_port_extender_cb_uc.extender_port[1].extender_gport_id), "");

    printf("Done configuring\n");

    return BCM_E_NONE;
}

/*
 * You can use this function to change the ports the cint is using from the defaults (13, 14 and 15).
 *
 * INPUT: unit              - unit
 *        in_cascaded_port  - cascaded port holding lifs 1 and 2
 *        out_cascaded_port - cascaded port holding lif 3
 *        end_station_port  - ethernet port holding lif 4
 */
int
port_extender_cb_uc_run_with_customized_para(
    int unit,
    int in_cascaded_port,
    int out_cascaded_port,
    int end_station_port,
    bcm_vlan_t vsi)
{

    g_port_extender_cb_uc.cascaded_port[0].port = in_cascaded_port;
    g_port_extender_cb_uc.cascaded_port[1].port = in_cascaded_port;
    g_port_extender_cb_uc.cascaded_port[2].port = out_cascaded_port;
    g_port_extender_cb_uc.cascaded_port[3].port = in_cascaded_port;

    g_port_extender_cb_uc.end_station.port = end_station_port;

    g_port_extender_cb_uc.extender_port[0].port = in_cascaded_port;
    g_port_extender_cb_uc.extender_port[1].port = in_cascaded_port;
    g_port_extender_cb_uc.extender_port[2].port = out_cascaded_port;
    g_port_extender_cb_uc.extender_port[3].port = in_cascaded_port;

    g_port_extender_cb_uc.vsi = vsi;

    return port_extender_cb_uc_run(unit);
}

/* P2P(vlan_port <==>extender port) structure */
struct port_extender_p2p_s {
    bcm_port_t ac_port;
    bcm_vlan_t vlan_port_match_vlan;              /* Outer VLAN ID to match. */
    bcm_gport_t vlan_port_id;
    bcm_port_t extender_port;
    uint16     extended_port_vid;       /* Extender port VID. */
    bcm_vlan_t extender_port_match_vlan;              /* Outer VLAN ID to match. */
    bcm_gport_t extender_port_id;
};

/* Initialization of global struct*/
port_extender_p2p_s g_port_extender_p2p = {
    13, /* vlan port */
    10, /* match vlan at vlan port */
    0,
    14, /* extender port */
    100, /* Extender port VID. */
    200, /* match vlan at extender port */
    0,
};

/**
 * P2P service(vlan_port <==>extender port) configuration init
 * INPUT:
 *   ac_port   - ucode port of vlan port
 *   extender_port -  extender port
 */
int
extender_port_p2p_service_init(
    int unit,
    int ac_port,
    int extender_port)
{
    char error_msg[200]={0,};
 
    snprintf(error_msg, sizeof(error_msg), "ac_port %d, vlan_domain %d", ac_port, ac_port);
    BCM_IF_ERROR_RETURN_MSG(bcm_port_class_set(unit, ac_port, bcmPortClassId, ac_port), error_msg);

    snprintf(error_msg, sizeof(error_msg), "extender_port %d, vlan_domain %d", extender_port, extender_port);
    BCM_IF_ERROR_RETURN_MSG(bcm_port_class_set(unit, extender_port, bcmPortClassId, extender_port), error_msg);

    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_gport_add(unit, g_port_extender_p2p.vlan_port_match_vlan, ac_port, 0), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_gport_add(unit, g_port_extender_p2p.extender_port_match_vlan, extender_port, 0), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_port_set(unit, extender_port, bcmSwitchPrependTagEnable, 1), "");

    /*
     * Configure the Port Extender Port-type 
     */
    snprintf(error_msg, sizeof(error_msg), "for bcmPortControlExtenderType to SWITCH, port - %d", extender_port);
    BCM_IF_ERROR_RETURN_MSG(bcm_port_control_set(unit, extender_port, bcmPortControlExtenderType, BCM_PORT_EXTENDER_TYPE_SWITCH), error_msg);

    g_port_extender_p2p.ac_port = ac_port;
    g_port_extender_p2p.extender_port = extender_port;

    return BCM_E_NONE;
}

/**
 * Create P2P service between vlan_port and extender port
 * INPUT:
 *   port1 -  vlan port
 *   port2 -  extender port
 *
 * Steps
 * Test Scenario - start
    cint ../../../../src/examples/sand/utility/cint_sand_utils_global.c
    cint ../../../../src/examples/sand/utility/cint_sand_utils_l2.c
    cint ../../../../src/examples/dnx/extender/cint_extender.c
    cint
    extender_port_p2p_basic_service_run(0,201,203);
    exit;
 *
 *  ac -> extender 
  tx 1 psrc=201 data=0x0000000000020000000000018100000affff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 *
 * Received packets on unit 0 should be:
 * Data: 0x000000000002000000000001893f0000006400008100000affff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f200000000000000000000000
 *
 * extender -> ac 
  tx 1 psrc=203 data=0x00000002000000000001893f000000640000810000c8ffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 *
 *  Received packets on unit 0 should be: 
 * Data: 0x000000000002000000000001810000c8ffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f200000000000 
 *
  cint
  extender_port_p2p_basic_service_clean(0);
  exit;
 * Test Scenario - end
 *
 */
int
extender_port_p2p_basic_service_run(
    int unit,
    int port1,
    int port2)

{
    bcm_extender_port_t extender_port;
    bcm_vlan_port_t vlan_port;
    bcm_vswitch_cross_connect_t cross_connect;

    /* init */
    BCM_IF_ERROR_RETURN_MSG(extender_port_p2p_service_init(unit, port1, port2), "");

    /* vlan port */
    bcm_vlan_port_t_init(&vlan_port);
    vlan_port.criteria = BCM_VLAN_PORT_MATCH_PORT_CVLAN;
    vlan_port.port = g_port_extender_p2p.ac_port;
    vlan_port.match_vlan = g_port_extender_p2p.vlan_port_match_vlan;
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_create(unit, &vlan_port), "");
    g_port_extender_p2p.vlan_port_id = vlan_port.vlan_port_id;

    /* extender port */
    bcm_extender_port_t_init(&extender_port);
    extender_port.port = g_port_extender_p2p.extender_port;
    extender_port.match_vlan = g_port_extender_p2p.extender_port_match_vlan;
    extender_port.extended_port_vid = g_port_extender_p2p.extended_port_vid;
    extender_port.criteria = BCM_EXTENDER_PORT_MATCH_PORT_EXTENDED_PORT_CVLAN;
    BCM_IF_ERROR_RETURN_MSG(bcm_extender_port_add(unit, &extender_port), "");
    g_port_extender_p2p.extender_port_id = extender_port.extender_port_id;

    /* add cross_connect: vlan_port <==> extender_port  */
    bcm_vswitch_cross_connect_t_init(&cross_connect);
    cross_connect.port1 = g_port_extender_p2p.vlan_port_id;
    cross_connect.port2 = g_port_extender_p2p.extender_port_id;
    BCM_IF_ERROR_RETURN_MSG(bcm_vswitch_cross_connect_add(unit, &cross_connect), "");

    return BCM_E_NONE;

}


/**
 * Clean P2P service configuration
 */
int
extender_port_p2p_basic_service_clean(
    int unit)

{
    bcm_vswitch_cross_connect_t cross_connect;

    /* add cross_connect: vlan_port <==> extender_port  */
    bcm_vswitch_cross_connect_t_init(&cross_connect);
    cross_connect.port1 = g_port_extender_p2p.vlan_port_id;
    cross_connect.port2 = g_port_extender_p2p.extender_port_id;
    BCM_IF_ERROR_RETURN_MSG(bcm_vswitch_cross_connect_delete(unit, &cross_connect), "");

    /* vlan port */
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_destroy(unit, g_port_extender_p2p.vlan_port_id), "");

    /* extender port */
    BCM_IF_ERROR_RETURN_MSG(bcm_extender_port_delete(unit, g_port_extender_p2p.extender_port_id), "");

    return BCM_E_NONE;

}


/**
 * Update qos_variable mapping for profile
 */
int extender_qos_egress_remark(int unit, int profile, int is_default)
{
    int map_opcode;
    uint32 flags;
    uint32 color;
    int var;
    bcm_qos_map_t egress_remark_map;
    int max_dp = *dnxc_data_get(unit, "qos", "qos", "packet_max_dp", NULL);
    int max_var = *dnxc_data_get(unit, "qos", "qos", "max_egress_var", NULL);

    /** profile is allocated in qos moudle init */
    flags = BCM_QOS_MAP_EGRESS | BCM_QOS_MAP_REMARK|BCM_QOS_MAP_OPCODE;
    BCM_IF_ERROR_RETURN_MSG(bcm_qos_map_id_get_by_profile(unit, flags, profile, &map_opcode), "for map_opcode");

    /** init outer pcp/dei map  */
    flags = BCM_QOS_MAP_L2 | BCM_QOS_MAP_REMARK | BCM_QOS_MAP_L2_TWO_TAGS;
    for (color = 0; color <= max_dp; color++)
    {
        for (var = 0; var <= max_var; var++)
        {
            bcm_qos_map_t_init(&egress_remark_map);
            egress_remark_map.int_pri = var;
            egress_remark_map.color = color;            

            /** qos 1:1 mapping */
            if (!is_default)
            {
                egress_remark_map.pkt_pri = (var >> 2) & 7;
                egress_remark_map.pkt_cfi = (var >> 1) & 1;
                egress_remark_map.inner_pkt_pri = (var >> 0) & 7;
                egress_remark_map.inner_pkt_cfi = (var >> 0) & 1;
            }
            else
            {
                egress_remark_map.pkt_pri = (var >> 1) & 7;
                egress_remark_map.pkt_cfi = var & 1;
                egress_remark_map.inner_pkt_pri = (var >> 1) & 7;
                egress_remark_map.inner_pkt_cfi = var & 1;
            }

            BCM_IF_ERROR_RETURN_MSG(bcm_qos_map_add(unit, flags, &egress_remark_map, map_opcode), "");
        }
    }

    return BCM_E_NONE;
}



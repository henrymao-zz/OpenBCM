int user_defined_trap;

int add_mact_entry(
    int unit,
    int mac_id,
    uint16 vid,
    int phy_port)
{
    bcm_l2_addr_t l2addr;
    bcm_gport_t port;

    bcm_mac_t my_mac = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    my_mac[5] = mac_id % 256;

    BCM_GPORT_SYSTEM_PORT_ID_SET(port, phy_port);

    bcm_l2_addr_t_init(&l2addr, my_mac, vid);

    l2addr.port = port;
    l2addr.vid = vid;
    l2addr.flags = BCM_L2_STATIC;
    l2addr.tgid = 2;

    BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_add(unit, &l2addr), "");

    return BCM_E_NONE;
}

int disable_same_if_filter_all(
    int unit,
    int port)
{
    int rv = BCM_E_NONE;
    int flags = 0;
    int trap_id;
    bcm_rx_trap_config_t config;
    bcm_rx_trap_t trap = bcmRxTrapSameInterface;

    BCM_IF_ERROR_RETURN_MSG(bcm_port_control_set(unit, port, bcmPortControlBridge, 0), "");

    bcm_rx_trap_config_t_init(&config);

    config.flags = BCM_RX_TRAP_UPDATE_DEST;
    config.trap_strength = 0;

    rv = bcm_rx_trap_type_get(unit, flags, trap, &trap_id);
    if (rv == BCM_E_CONFIG) {
        rv = BCM_E_NONE;
    }
    BCM_IF_ERROR_RETURN_MSG(rv, "");

    BCM_IF_ERROR_RETURN_MSG(bcm_rx_trap_set(unit, trap_id, &config), "");

    return BCM_E_NONE;
}

int port_set_raw_header(
    int unit,
    int port)
{
    bcm_switch_control_key_t key;
    bcm_switch_control_info_t value;

    key.index = 2;
    key.type = bcmSwitchPortHeaderType;
    value.value = BCM_SWITCH_PORT_HEADER_TYPE_RAW;

    BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_indexed_port_set(unit, port, key, value), "");

    return BCM_E_NONE;
}


int pfc_port_control_set(
    int unit,
    int port)
{
    return bcm_port_control_set(unit, port, bcmPortControlPFCReceive, 1);
}

/**
* \brief - in order to have RX time-stamp of the packet, user must enable the timestamp in the port.
*          should be made while port is disabled.
*          assuming linkScan is enabled.
*/
int rx_time_stamp_enable(
    int unit,
    int in_port)    
{
    bcm_port_phy_timesync_config_t timesync_phy_config;

    bcm_port_phy_timesync_config_t_init(&timesync_phy_config);
    /** flag BCM_PORT_PHY_TIMESYNC_ONE_STEP_ENABLE is relevant only for 1588 feature. */
    /** If you don't use flag BCM_PORT_PHY_TIMESYNC_ONE_STEP_ENABLE, two step timestamping is enabled in the port. */
    /** If you only care about the Rx TS, you can only use flag BCM_PORT_PHY_TIMESYNC_ENABLE. */
    timesync_phy_config.flags = (BCM_PORT_PHY_TIMESYNC_ENABLE | BCM_PORT_PHY_TIMESYNC_ONE_STEP_ENABLE);
    BCM_IF_ERROR_RETURN_MSG(bcm_port_enable_set(unit, in_port, 0), "");
    BCM_IF_ERROR_RETURN_MSG(bcm_port_phy_timesync_config_set(unit, in_port, &timesync_phy_config), "");
    BCM_IF_ERROR_RETURN_MSG(bcm_port_enable_set(unit, in_port, 1), "");    
    /** wait after port enable, that port will sync back */
    sal_sleep(6);
    return BCM_E_NONE;
}

/**
* \brief - Configure snoop and add PMF entry for it.
*          Create and attach TCAM group in iPMF1. Attach field group to context and add field entry.
*
*/
int
cpu_snoop_by_src_port_pmf_config_set(
    int unit,
    bcm_port_t src_port,
    bcm_port_t out_port)
{
    bcm_mirror_destination_t mirror_dest;
    bcm_field_group_info_t fg_info;
    bcm_field_group_attach_info_t attach_info;
    bcm_field_entry_info_t ent_info;
    void *dest_char;
    bcm_field_group_t cint_in_port_qaul_fg_id = 0;
    bcm_field_entry_t ent1_id;
    int is_snoop;
    int snoop_cmnd;
    int flags = 0;
    int trap_strength = 0;
    int snoop_strength = 3;
    int trap_code;
    bcm_rx_trap_config_t trap_config_snoop;
    bcm_gport_t snoop_trap_gport_id;

    /*
     * Create a new snoop command associated with the new trap
     */
    bcm_mirror_destination_t_init(&mirror_dest);
    mirror_dest.gport = out_port;
    mirror_dest.flags = BCM_MIRROR_DEST_IS_SNOOP;
    /* Add trap FHEI preserve */
    mirror_dest.packet_control_updates.valid = BCM_MIRROR_PKT_HEADER_UPDATE_FABRIC_HEADER_EDITING;

    BCM_IF_ERROR_RETURN_MSG(bcm_mirror_destination_create(unit, &mirror_dest), "");

    bcm_mirror_header_info_t mirror_header_info;
    bcm_mirror_header_info_t_init(&mirror_header_info);
    mirror_header_info.tm.src_sysport = src_port;
    BCM_IF_ERROR_RETURN_MSG(bcm_mirror_header_info_set(unit, BCM_MIRROR_DEST_IS_SNOOP, mirror_dest.mirror_dest_id, &mirror_header_info), "");

    /*
     * Check if snoop was created
     */
    is_snoop = BCM_GPORT_IS_MIRROR_SNOOP(mirror_dest.mirror_dest_id);
    if (!is_snoop)
    {
        printf("Error. Could not create snoop.\n");
        return -1;
    }

    /*
     * Get the snoop command
     */
    snoop_cmnd = BCM_GPORT_MIRROR_GET(mirror_dest.mirror_dest_id);

    /*
     * Create a new trap
     */
    BCM_IF_ERROR_RETURN_MSG(bcm_rx_trap_type_create(unit, flags, bcmRxTrapUserDefine, &trap_code), "");

    user_defined_trap = trap_code;

    /*
     * Setup the new trap
     */
    bcm_rx_trap_config_t_init(&trap_config_snoop);
    trap_config_snoop.trap_strength = 0;
    trap_config_snoop.snoop_cmnd = snoop_cmnd;

    BCM_IF_ERROR_RETURN_MSG(bcm_rx_trap_set(unit, trap_code, trap_config_snoop), "");

    /*
     * Encode trap, trap strength and snoop strength as a gport
     */
    BCM_GPORT_TRAP_SET(snoop_trap_gport_id, trap_code, trap_strength, snoop_strength);

    /*
     * Create and attach TCAM group in iPMF1
     */
    bcm_field_group_info_t_init(&fg_info);
    fg_info.fg_type = bcmFieldGroupTypeTcam;
    fg_info.stage = bcmFieldStageIngressPMF1;
    fg_info.nof_quals = 1;
    fg_info.qual_types[0] = bcmFieldQualifyInPort;
    fg_info.nof_actions = 1;
    fg_info.action_types[0] = bcmFieldActionSnoop;

    printf("Creating first group\n");
    dest_char = &(fg_info.name[0]);
    sal_strncpy_s(dest_char, "In_port_qual", sizeof(fg_info.name));
    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_add(unit, 0, &fg_info, &cint_in_port_qaul_fg_id), "");

    /*
     * Attach the FG to context
     */
    bcm_field_group_attach_info_t_init(&attach_info);

    attach_info.key_info.nof_quals = 1;
    attach_info.key_info.qual_types[0] = bcmFieldQualifyInPort;
    attach_info.payload_info.nof_actions = 1;
    attach_info.payload_info.action_types[0] = bcmFieldActionSnoop;
    attach_info.key_info.qual_info[0].input_type = bcmFieldInputTypeMetaData;
    attach_info.key_info.qual_info[0].input_arg = 0;
    attach_info.key_info.qual_info[0].offset = 0;

    printf("Attaching field group\n");
    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_context_attach(unit, 0, cint_in_port_qaul_fg_id, 0 , &attach_info), "");

    bcm_field_entry_info_t_init(&ent_info);
    ent_info.priority = 1;
    ent_info.nof_entry_quals = 1;
    ent_info.entry_qual[0].type = bcmFieldQualifyInPort;
    ent_info.entry_qual[0].value[0] = src_port;
    ent_info.entry_qual[0].mask[0] = 0x1ff;

    ent_info.nof_entry_actions = 1;
    ent_info.entry_action[0].type = bcmFieldActionSnoop;
    ent_info.entry_action[0].value[0] = snoop_trap_gport_id;

    printf("Adding Entry\n");
    BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_add(unit, 0, cint_in_port_qaul_fg_id, &ent_info, &ent1_id), "");

    return BCM_E_NONE;
}


/*
 * 
 This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 
 Copyright 2007-2022 Broadcom Inc. All rights reserved. File: cint_stat_pp_egress_metadata.c Purpose: Statistics examples for SDK egress statistics and metadata APIs using an L2 application.
 */

/*
 * File: cint_stat_pp_egress_metadata.c
 * Purpose: Example of multiple egress PP statistics
 *
 * Count packets on specific metadata offset inside the counted object counter set (in relevant offset)
 *
 * Usage:
 * ------
 *
 * Test Scenario:
 *--------------
 * Test Scenario - start
  cint ../../../../src/examples/dnx/field/cint_field_utils.c
  cint ../../../../src/examples/sand/utility/cint_sand_utils_l3.c
  cint ../../../../src/examples/sand/cint_ip_route_basic.c
  cint ../../../../src/examples/sand/utility/cint_sand_utils_global.c
  cint ../../../../src/examples/dnx/l3/cint_ip_route_encap_src_mac.c
  cint ../../../../src/examples/dnx/stat_pp/cint_stat_pp_config.c
  cint ../../../../src/examples/dnx/crps/cint_crps_db_utils.c
  cint ../../../../src/examples/dnx/crps/cint_crps_etpp_config.c
  cint ../../../../src/examples/dnx/stat_pp/cint_stat_pp_egress_metadata.c
  cint
  basic_example_egress_metadata_fwd_stat_pp(0,1);
  exit;
 * Test Scenario - end
 * Test Scenario - start
  cint ../../../../src/examples/dnx/field/cint_field_utils.c
  cint ../../../../src/examples/sand/utility/cint_sand_utils_l3.c
  cint ../../../../src/examples/sand/cint_ip_route_basic.c
  cint ../../../../src/examples/sand/utility/cint_sand_utils_global.c
  cint ../../../../src/examples/dnx/l3/cint_ip_route_encap_src_mac.c
  cint ../../../../src/examples/dnx/stat_pp/cint_stat_pp_config.c
  cint ../../../../src/examples/dnx/crps/cint_crps_db_utils.c
  cint ../../../../src/examples/dnx/crps/cint_crps_etpp_config.c
  cint ../../../../src/examples/dnx/stat_pp/cint_stat_pp_egress_metadata.c
  cint
  basic_example_egress_metadata_enc_stat_pp(0,1,2,3);
  exit;
 * Test Scenario - end
 * Test Scenario - start
  cint ../../../../src/examples/dnx/field/cint_field_utils.c
  cint ../../../../src/examples/sand/utility/cint_sand_utils_l3.c
  cint ../../../../src/examples/sand/cint_ip_route_basic.c
  cint ../../../../src/examples/sand/utility/cint_sand_utils_global.c
  cint ../../../../src/examples/dnx/l3/cint_ip_route_encap_src_mac.c
  cint ../../../../src/examples/dnx/stat_pp/cint_stat_pp_config.c
  cint ../../../../src/examples/dnx/crps/cint_crps_db_utils.c
  cint ../../../../src/examples/dnx/crps/cint_crps_etpp_config.c
  cint ../../../../src/examples/dnx/stat_pp/cint_stat_pp_egress_metadata.c
  cint
  basic_example_egress_metadata_fwd_plus_one_stat_pp(0,1);
  exit;
 * Test Scenario - end
 */

struct cint_stat_pp_egress_metadata_config_info_s
{
    bcm_stat_pp_metadata_header_type_t header_type;
    uint32 egress_metadata_val;
};

/* egress metadata enc */
cint_stat_pp_egress_metadata_config_info_s cint_stat_pp_egress_metadata_enc_info_ipv4 =
{
        bcmStatPpMetadataHeaderTypeIpv4,
        1,
};

cint_stat_pp_egress_metadata_config_info_s cint_stat_pp_egress_metadata_enc_info_ipv6 =
{
        bcmStatPpMetadataHeaderTypeIpv6,
        2,
};

cint_stat_pp_egress_metadata_config_info_s cint_stat_pp_egress_metadata_enc_info_mpls =
{
        bcmStatPpMetadataHeaderTypeMpls,
        3,
};

cint_stat_pp_egress_metadata_config_info_s cint_stat_pp_egress_metadata_enc_info_ipv4_mc =
{
        bcmStatPpMetadataHeaderTypeIpv4,
        4,
};

cint_stat_pp_egress_metadata_config_info_s cint_stat_pp_egress_metadata_enc_info_ipv6_mc =
{
        bcmStatPpMetadataHeaderTypeIpv6,
        5,
};

/* egress metadata fwd */
cint_stat_pp_egress_metadata_config_info_s cint_stat_pp_egress_metadata_fwd_info_eth =
{
        bcmStatPpMetadataHeaderTypeEth,
        1,
};

/* egress metadata fwd plus one */
cint_stat_pp_egress_metadata_config_info_s cint_stat_pp_egress_metadata_fwd_plus_one_info_ipv4 =
{
        bcmStatPpMetadataHeaderTypeIpv4,
        1,
};

cint_stat_pp_egress_metadata_config_info_s cint_stat_pp_egress_metadata_fwd_plus_one_info_ipv4_mc =
{
        bcmStatPpMetadataHeaderTypeIpv4,
        2,
};

cint_stat_pp_egress_metadata_config_info_s cint_stat_pp_egress_metadata_fwd_plus_one_info_ipv6 =
{
        bcmStatPpMetadataHeaderTypeIpv6,
        3,
};

cint_stat_pp_egress_metadata_config_info_s cint_stat_pp_egress_metadata_fwd_plus_one_info_ipv6_mc =
{
        bcmStatPpMetadataHeaderTypeIpv6,
        4,
};

cint_stat_pp_egress_metadata_config_info_s cint_stat_pp_egress_metadata_fwd_plus_one_info_mpls =
{
        bcmStatPpMetadataHeaderTypeMpls,
        5,
};

cint_stat_pp_egress_metadata_config_info_s cint_stat_pp_egress_metadata_fwd_plus_one_info_other =
{
        bcmStatPpMetadataHeaderTypeArp,
        6,
};

cint_stat_pp_config_info_s egress_metadata_statistics_config =
{
        /**database_id */
        1,
        /**crps_engine_id */
        1,
        /**pp_profile */
        1,
        /**counter_command */
        1,
        /**crps_start */
        0,
        /**crps_end */
        100,
        /**type_id*/
        0,
        /**stat_id*/
        1,
        /**expansion_flag*/
        EXPANSION_TYPE_META_DATA_FULL_4_BITS
};

/**Example for etpp enc metadata - mpls lif statistics
 * Counting is on mpls lif with next layer == ipv4*/
int
basic_example_egress_metadata_enc_stat_pp(
    int unit,
    int port1,
    int port2,
    int mpls_label)
{
    char error_msg[200]={0,};
    bcm_gport_t gport;
    bcm_stat_pp_info_t stat_info;
    bcm_stat_pp_profile_info_t pp_profile;
    bcm_stat_pp_metadata_info_t metadata_info;
    bcm_ip_t ipv4_mc_addr = 0xE0020202; /* 224.2.2.2 */
    bcm_ip_t ipv4_full_mask = 0xFFFFFFFF;
    bcm_ip6_t ipv6_mc_addr = {0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x11, 0x11};
    bcm_ip6_t ipv6_full_mask =
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    int pp_profile_id;
    uint32 entry_handle_id;
    int out_label = 4000;
    int mc_id = 5000;
    bcm_stat_counter_interface_type_t interface_type = *(dnxc_data_get(unit, "stat", "stat_pp", "supported_egress_interface_counter_enum", NULL));

    init_default_mpls_params(unit, port1, port2);

    /** fec pointer is following the mpls first encap tunnel, which will be created later */
    mpls_util_entity[0].fecs[0].tunnel_gport = &mpls_util_entity[0].mpls_encap_tunnel[0].tunnel_id;

    /** Configure mpls tunnel */
    mpls_util_entity[0].mpls_encap_tunnel[0].label[0] = mpls_label;
    mpls_util_entity[0].mpls_encap_tunnel[0].encap_access = bcmEncapAccessTunnel1;
    mpls_util_entity[0].mpls_encap_tunnel[0].l3_intf_id = &mpls_util_entity[1].arps[0].arp;
    mpls_util_entity[0].mpls_encap_tunnel[0].num_labels = 1;
    mpls_util_entity[0].mpls_encap_tunnel[0].flags |= (BCM_MPLS_EGRESS_LABEL_TTL_DECREMENT | BCM_MPLS_EGRESS_LABEL_STAT_ENABLE);
    mpls_util_entity[0].mpls_encap_tunnel[0].egress_qos_model.egress_qos = bcmQosEgressModelUniform;
    mpls_util_entity[0].mpls_encap_tunnel[0].egress_qos_model.egress_ttl = bcmQosEgressModelUniform;
    /** MPLS LSR into tunnel */
    mpls_util_entity[0].mpls_switch_tunnel[0].action = BCM_MPLS_SWITCH_ACTION_SWAP;
    mpls_util_entity[0].mpls_switch_tunnel[0].egress_label = out_label;

    mpls_util_entity[0].hosts_ipvx[1] = mpls_util_entity[0].hosts_ipvx[0];
    mpls_util_entity[0].hosts_ipvx[1].ipv4 = ipv4_mc_addr;
    mpls_util_entity[0].hosts_ipvx[1].valid_ipv6 = 1;
    mpls_util_entity[0].hosts_ipvx[1].ipv6 = ipv6_mc_addr;

    /** Create the mpls tunnels */
    BCM_IF_ERROR_RETURN_MSG(mpls_util_main(unit, port1, port2), "");

    /** Configure statistics for the mpls lif */
    BCM_L3_ITF_LIF_TO_GPORT_TUNNEL(gport, mpls_util_entity[0].mpls_encap_tunnel[0].tunnel_id);
    BCM_IF_ERROR_RETURN_MSG(cint_stat_pp_config_main(unit, egress_metadata_statistics_config, interface_type, gport, BCM_CORE_ALL, TRUE),
        "for etps_1_statistics_config");

    /* For IPMC to work properly in compatible mode, forwarding decision needs to be multicast */
    if (!dnx_utils_is_jr2_system_header_mode(unit))
    {
        /**
         * 1. Search IPvX multicast address in routing table, returns FEC ID;
         * 2. Get destination port + encap ID from FEC entry;
         * 3. Create ingress multicast group, add port + encap ID as multicast member
         * 4. Update IPvX multicast entry in routing table to point to the created MC group
         */
        bcm_ipmc_addr_t ipmc_addr;
        bcm_ipmc_addr_t_init(&ipmc_addr);

        ipmc_addr.mc_ip_addr = ipv4_mc_addr;
        ipmc_addr.mc_ip_mask = ipv4_full_mask;

        ipmc_addr.vrf = mpls_util_entity[0].hosts_ipvx[1].vrf;
        snprintf(error_msg, sizeof(error_msg), "Failed to find IPv4 MC entry (%08X) in routing table", ipv4_mc_addr);
        BCM_IF_ERROR_RETURN_MSG(bcm_ipmc_find(unit, &ipmc_addr), error_msg);

        bcm_l3_egress_t egr;
        snprintf(error_msg, sizeof(error_msg), "Failed to find FEC entry %d", ipmc_addr.l3a_intf);
        BCM_IF_ERROR_RETURN_MSG(bcm_l3_egress_get(unit, ipmc_addr.l3a_intf, &egr), error_msg);

        bcm_multicast_replication_t replications;

        snprintf(error_msg, sizeof(error_msg), "Failed to create multicast group %d", mc_id);
        BCM_IF_ERROR_RETURN_MSG(bcm_multicast_create(unit, BCM_MULTICAST_WITH_ID | BCM_MULTICAST_INGRESS_GROUP, mc_id), error_msg);

        bcm_multicast_replication_t_init(&replications);
        replications.port = egr.port;
        replications.encap1 = BCM_ENCAP_ID_GET(egr.intf);

        snprintf(error_msg, sizeof(error_msg), "Failed to add replications to multicast group %d", mc_id);
        BCM_IF_ERROR_RETURN_MSG(bcm_multicast_add(unit, mc_id, BCM_MULTICAST_INGRESS_GROUP, 1, &replications), error_msg);

        bcm_ipmc_addr_t_init(&ipmc_addr);
        ipmc_addr.flags = BCM_IPMC_REPLACE;
        ipmc_addr.mc_ip_addr = ipv4_mc_addr;
        ipmc_addr.mc_ip_mask = ipv4_full_mask;
        ipmc_addr.vrf = mpls_util_entity[0].hosts_ipvx[1].vrf;
        ipmc_addr.group = mc_id;
        snprintf(error_msg, sizeof(error_msg), "Failed to replace existing IPMC entry 0x%08X", ipv4_mc_addr);
        BCM_IF_ERROR_RETURN_MSG(bcm_ipmc_add(unit, &ipmc_addr), error_msg);

        bcm_ipmc_addr_t_init(&ipmc_addr);
        ipmc_addr.flags = BCM_IPMC_IP6 | BCM_IPMC_REPLACE;
        ipmc_addr.mc_ip6_addr = ipv6_mc_addr;
        ipmc_addr.mc_ip6_mask = ipv6_full_mask;
        ipmc_addr.vrf = mpls_util_entity[0].hosts_ipvx[1].vrf;
        ipmc_addr.group = mc_id;
        BCM_IF_ERROR_RETURN_MSG(bcm_ipmc_add(unit, &ipmc_addr), "Failed to replace existing IPv6 multicast entry");
    }

    /* Layertype: IPv4, UC */
    metadata_info.flags = BCM_STAT_PP_METADATA_EGRESS;
    metadata_info.flags |= BCM_STAT_PP_METADATA_TUNNEL;
    metadata_info.header_type = cint_stat_pp_egress_metadata_enc_info_ipv4.header_type;
    metadata_info.address_type_flags = BCM_STAT_PP_METADATA_ADDRESS_TYPE_UCAST;
    metadata_info.metadata = cint_stat_pp_egress_metadata_enc_info_ipv4.egress_metadata_val;

    /**Configure metadata mapping*/
    BCM_IF_ERROR_RETURN_MSG(bcm_stat_pp_metadata_set(unit, &metadata_info), "");

    /* Layertype: IPv4, MC */
    metadata_info.flags = BCM_STAT_PP_METADATA_EGRESS;
    metadata_info.flags |= BCM_STAT_PP_METADATA_TUNNEL;
    metadata_info.header_type = cint_stat_pp_egress_metadata_enc_info_ipv4_mc.header_type;
    metadata_info.address_type_flags = BCM_STAT_PP_METADATA_ADDRESS_TYPE_MCAST;
    metadata_info.metadata = cint_stat_pp_egress_metadata_enc_info_ipv4_mc.egress_metadata_val;

    /**Configure metadata mapping*/
    BCM_IF_ERROR_RETURN_MSG(bcm_stat_pp_metadata_set(unit, &metadata_info), "");

    /* Layertype: IPv6, UC */
    metadata_info.flags = BCM_STAT_PP_METADATA_EGRESS;
    metadata_info.flags |= BCM_STAT_PP_METADATA_TUNNEL;
    metadata_info.header_type = cint_stat_pp_egress_metadata_enc_info_ipv6.header_type;
    metadata_info.address_type_flags = BCM_STAT_PP_METADATA_ADDRESS_TYPE_UCAST;
    metadata_info.metadata = cint_stat_pp_egress_metadata_enc_info_ipv6.egress_metadata_val;

    /**Configure metadata mapping*/
    BCM_IF_ERROR_RETURN_MSG(bcm_stat_pp_metadata_set(unit, &metadata_info), "");

    /* Layertype: IPv6, MC */
    metadata_info.flags = BCM_STAT_PP_METADATA_EGRESS;
    metadata_info.flags |= BCM_STAT_PP_METADATA_TUNNEL;
    metadata_info.header_type = cint_stat_pp_egress_metadata_enc_info_ipv6_mc.header_type;
    metadata_info.address_type_flags = BCM_STAT_PP_METADATA_ADDRESS_TYPE_MCAST;
    metadata_info.metadata = cint_stat_pp_egress_metadata_enc_info_ipv6_mc.egress_metadata_val;

    /**Configure metadata mapping*/
    BCM_IF_ERROR_RETURN_MSG(bcm_stat_pp_metadata_set(unit, &metadata_info), "");

    /* Layertype: MPLS */
    metadata_info.flags = BCM_STAT_PP_METADATA_EGRESS;
    metadata_info.flags |= BCM_STAT_PP_METADATA_TUNNEL;
    metadata_info.header_type = cint_stat_pp_egress_metadata_enc_info_mpls.header_type;
    metadata_info.metadata = cint_stat_pp_egress_metadata_enc_info_mpls.egress_metadata_val;

    /**Configure metadata mapping*/
    BCM_IF_ERROR_RETURN_MSG(bcm_stat_pp_metadata_set(unit, &metadata_info), "");

    return BCM_E_NONE;
}

/**Example for etpp fwd metadata - vlan statistics
 * Counting is on egress vsi with eth forwarding*/
int
basic_example_egress_metadata_fwd_stat_pp(
    int unit,
    int vid)
{
    bcm_vlan_t vlan;
    bcm_vlan_control_vlan_t vsi_control;
    bcm_stat_pp_metadata_info_t metadata_info;
    uint32 entry_handle_id;	
    bcm_stat_counter_interface_type_t interface_type = *(dnxc_data_get(unit, "stat", "stat_pp", "supported_egress_interface_counter_enum", NULL));

    /** Configure statistics for the egress vsi*/
    egress_metadata_statistics_config.stat_id = vid;
    /**Configure crps and reserve metadata buffer space*/
    BCM_IF_ERROR_RETURN_MSG(cint_stat_pp_config_main(unit, egress_metadata_statistics_config, interface_type, 0, BCM_CORE_ALL, FALSE),
        "failed for etps_1_statistics_config");

    /**Create vlan with statistics*/
    vlan = vid;
    vsi_control.forwarding_vlan = vid;

    vsi_control.egress_stat_pp_profile = egress_metadata_statistics_config.pp_profile;
    vsi_control.egress_stat_id = egress_metadata_statistics_config.stat_id;
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_control_vlan_set(unit, vlan, vsi_control), "");

    metadata_info.flags = BCM_STAT_PP_METADATA_EGRESS;
    metadata_info.flags |= BCM_STAT_PP_METADATA_FORWARD;
    metadata_info.address_type_flags = BCM_STAT_PP_METADATA_ADDRESS_TYPE_UCAST;
    metadata_info.header_type = cint_stat_pp_egress_metadata_fwd_info_eth.header_type;
    metadata_info.metadata = cint_stat_pp_egress_metadata_fwd_info_eth.egress_metadata_val;

    /**Configure metadata mapping*/
    BCM_IF_ERROR_RETURN_MSG(bcm_stat_pp_metadata_set(unit, &metadata_info), "");

    return BCM_E_NONE;
}

/**Example for etpp fwd plus one metadata - vlan statistics
 * Counting is on egress vsi with eth forwarding*/
int
basic_example_egress_metadata_fwd_plus_one_stat_pp(
    int unit,
    int vid)
{
    bcm_vlan_t vlan;
    bcm_vlan_control_vlan_t vsi_control;
    bcm_stat_pp_metadata_info_t metadata_info;
    uint32 entry_handle_id;

    /** Configure statistics for the egress vsi*/
    egress_metadata_statistics_config.stat_id = vid;
    /**Configure crps and reserve metadata buffer space*/
    BCM_IF_ERROR_RETURN_MSG(cint_stat_pp_config_main(unit, egress_metadata_statistics_config, bcmStatCounterInterfaceEgressTransmitPp, 0, BCM_CORE_ALL, FALSE),
        "failed for etps_1_statistics_config");

    /**Create vlan with statistics*/
    vlan = vid;
    vsi_control.forwarding_vlan = vid;

    vsi_control.egress_stat_pp_profile = egress_metadata_statistics_config.pp_profile;
    vsi_control.egress_stat_id = egress_metadata_statistics_config.stat_id;
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_control_vlan_set(unit, vlan, vsi_control), "");

    /* IPv4 UC */
    metadata_info.flags = BCM_STAT_PP_METADATA_EGRESS;
    metadata_info.flags |= BCM_STAT_PP_METADATA_FORWARD_PLUS_ONE;
    metadata_info.address_type_flags = BCM_STAT_PP_METADATA_ADDRESS_TYPE_UCAST;
    metadata_info.header_type = cint_stat_pp_egress_metadata_fwd_plus_one_info_ipv4.header_type;
    metadata_info.metadata = cint_stat_pp_egress_metadata_fwd_plus_one_info_ipv4.egress_metadata_val;

    /**Configure metadata mapping*/
    BCM_IF_ERROR_RETURN_MSG(bcm_stat_pp_metadata_set(unit, &metadata_info), "IPv4 UC");

    /* IPv4 MC */
    metadata_info.address_type_flags = BCM_STAT_PP_METADATA_ADDRESS_TYPE_MCAST;
    metadata_info.header_type = cint_stat_pp_egress_metadata_fwd_plus_one_info_ipv4_mc.header_type;
    metadata_info.metadata = cint_stat_pp_egress_metadata_fwd_plus_one_info_ipv4_mc.egress_metadata_val;

    /**Configure metadata mapping*/
    BCM_IF_ERROR_RETURN_MSG(bcm_stat_pp_metadata_set(unit, &metadata_info), "IPv4 MC");

    /* IPv6 UC */
    metadata_info.address_type_flags = BCM_STAT_PP_METADATA_ADDRESS_TYPE_UCAST;
    metadata_info.header_type = cint_stat_pp_egress_metadata_fwd_plus_one_info_ipv6.header_type;
    metadata_info.metadata = cint_stat_pp_egress_metadata_fwd_plus_one_info_ipv6.egress_metadata_val;

    /**Configure metadata mapping*/
    BCM_IF_ERROR_RETURN_MSG(bcm_stat_pp_metadata_set(unit, &metadata_info), "IPv6 UC");

    /* IPv6 MC */
    metadata_info.address_type_flags = BCM_STAT_PP_METADATA_ADDRESS_TYPE_MCAST;
    metadata_info.header_type = cint_stat_pp_egress_metadata_fwd_plus_one_info_ipv6_mc.header_type;
    metadata_info.metadata = cint_stat_pp_egress_metadata_fwd_plus_one_info_ipv6_mc.egress_metadata_val;

    /**Configure metadata mapping*/
    BCM_IF_ERROR_RETURN_MSG(bcm_stat_pp_metadata_set(unit, &metadata_info), "IPv6 MC");

    /* MPLS */
    metadata_info.address_type_flags = BCM_STAT_PP_METADATA_ADDRESS_TYPE_UCAST;
    metadata_info.header_type = cint_stat_pp_egress_metadata_fwd_plus_one_info_mpls.header_type;
    metadata_info.metadata = cint_stat_pp_egress_metadata_fwd_plus_one_info_mpls.egress_metadata_val;

    /**Configure metadata mapping*/
    BCM_IF_ERROR_RETURN_MSG(bcm_stat_pp_metadata_set(unit, &metadata_info), "IPv4 UC");

    /* Other */
    metadata_info.address_type_flags = BCM_STAT_PP_METADATA_ADDRESS_TYPE_UCAST;
    metadata_info.header_type = cint_stat_pp_egress_metadata_fwd_plus_one_info_other.header_type;
    metadata_info.metadata = cint_stat_pp_egress_metadata_fwd_plus_one_info_other.egress_metadata_val;

    /**Configure metadata mapping*/
    BCM_IF_ERROR_RETURN_MSG(bcm_stat_pp_metadata_set(unit, &metadata_info), "IPv4 UC");

    return BCM_E_NONE;
}



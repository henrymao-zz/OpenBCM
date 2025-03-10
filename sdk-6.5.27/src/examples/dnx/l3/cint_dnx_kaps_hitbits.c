/*
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * KAPS Hitbits Example script
 *
 */

/*
 * This cint demonstrates KAPS hitbit functionality.
 * To enable/disable hitbits in KAPS for a specific table,
 * use bcm_switch_control_indexed_set with bcmSwitchL3LpmHitbitEnable as the key type
 * and bcm_switch_l3_lpm_hitbit_tables_t as the key index.
 * Value can be either 1 (enable) or 0 (disable).
 * Calling with the same value as the currently set value will return an error.
 *
 * Enabling hitbits must be done on empty tables, if they are not empty they will be cleared.
 *
 * For bcm_l3_route_get and bcm_l3_route_traverse, BCM_L3_HIT flag set on retrieved route indicates it was hit.
 * Use BCM_L3_HIT_CLEAR with bcm_l3_route_get or bcm_l3_route_traverse to clear hitbits in UC routes.
 *
 * For bcm_ipmc_find and bcm_ipmc_traverse, BCM_IPMC_HIT flag set on retrieved route indicates it was hit.
 * Use BCM_IPMC_HIT_CLEAR with bcm_ipmc_find or bcm_ipmc_traverse to clear hitbits in MC routes.
 */


/*
 * This cint is only used for testing hitbits and therefore the payload is of no interest,
 * For simplicity all routes with ip = mask are entered for various prefix lengths.
 * IPv4 UC prefix length 4-32 (including) are added + default private/public.
 * IPv4 MC prefix length 8-32 (including) are added.
 * IPv6 UC prefix length 8-128 (including) are added + default private/public.
 * IPv6 MC prefix length 8-128 (including) are added.
 * Alternate between public and private DBs using the following formula: prefix_length % 2 ? vlan : 0.
 * UC packets are sent with vlan 5(hits private+public) and 6(hits public) and forwarded with vlan 5.
 * The vrf=5 in_rif has mymac equal to mac_l3_ingress_add, the vrf=6 in_rif has mymac equal to mac_l3_ingress_public_add.
 * MC packets are sent with vlan 5(hits private+public) and 6(hits public) and forwarded with vlan 7 (to avoid fallback to bridge).
 * The DA MAC is derived from the destination IP for IPMC.
 *
 * Example IPv4 UC sequence:
 * (For IPv6 UC change the second parameter of kaps_hitbits_uc_verify_entries to 0)
 * (For IPv4/6 MC use kaps_hitbits_mc_verify_entries)
 *
 * Test Scenario - start
  cint ../../../../src/examples/dnx/l3/cint_dnx_ip_route_basic.c
  cint ../../../../src/examples/dnx/utility/cint_dnx_utils_l3.c
  cint ../../../../src/examples/dnx/l3/cint_dnx_kaps_hitbits.c
  cint
  kaps_hitbits_ipv_4_6_uc_mc_fill_entries(0,200,201);
  exit;
 *
 * Iteration 0: Send an IPv4 UC packet to hit a prefix length of 32.
  tx 1 psrc=200 data=0x0000000055110000d6de479c8100000608004500003500000000800016b70a0a0a0a0fffffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 *
 *  Received packets on unit 0 should be:
 *  Source port: 0, Destination port: 0
 *  Data: 0x00000000660100000000550181000005080045000035000000007f0017b70a0a0a0a0fffffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 *
  cint
  kaps_hitbits_uc_verify_entries(0,1,0);
  exit;
 * Test Scenario - end
 */
int kaps_hitbits_ipv_4_6_uc_mc_fill_entries(int unit, int in_port, int out_port) {
    int i;
    bcm_l3_intf_t l3if;
    bcm_l3_intf_t l3if_public;
    bcm_l3_intf_t l3if_mc;
    bcm_l3_egress_t l3eg;
    bcm_if_t l3egid;
    int egress_intf = 20000;
    int encap_id = 8193;
    int min_mc_prefix = 8;
    bcm_mac_t mac_l3_ingress_add = {0x00, 0x00, 0x00, 0x00, 0x55, 0x01};
    bcm_mac_t mac_l3_ingress_public_add = {0x00, 0x00, 0x00, 0x00, 0x55, 0x11};
    bcm_mac_t mac_l3_egress_add = {0x00, 0x00, 0x00, 0x00, 0x66, 0x01};
    char error_msg[200]={0,};
    int vlan = 5;
    uint32 mc_flags = BCM_MULTICAST_INGRESS_GROUP | BCM_MULTICAST_WITH_ID;
    bcm_multicast_t ipmc_group = 1 + vlan;

    bcm_switch_l3_lpm_hitbit_tables_t kaps_hitbit_tables[4];
    int num_of_tables = 4, table_index = 0;


    /*Enable hitbits*/
    kaps_hitbit_tables[table_index++] = bcmL3LpmHitbitTableIPv4MC;
    kaps_hitbit_tables[table_index++] = bcmL3LpmHitbitTableIPv6MC;
    kaps_hitbit_tables[table_index++] = bcmL3LpmHitbitTableIPv4UC;
    kaps_hitbit_tables[table_index++] = bcmL3LpmHitbitTableIPv6UC;

    for (i = 0; i < num_of_tables; i++) {
        /*Get, set and get again to verify correct bcm_switch_control functionality*/
        bcm_switch_control_key_t key;
        bcm_switch_control_info_t info;
        key.type = bcmSwitchL3LpmHitbitEnable;
        key.index = kaps_hitbit_tables[i];
        snprintf(error_msg, sizeof(error_msg), "bcmSwitchL3LpmHitbitEnable failed with table index = %d.", i);
        BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_indexed_get(unit, key, &info), error_msg);

        if (info.value != 0) {
            printf("bcm_switch_control_indexed_get returned value = 1, before the value was set.\n");
            return -1;
        }

        info.value = 1;
        snprintf(error_msg, sizeof(error_msg), "bcmSwitchL3LpmHitbitEnable failed with table index = %d.", i);
        BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_indexed_set(unit, key, info), error_msg);

        snprintf(error_msg, sizeof(error_msg), "bcmSwitchL3LpmHitbitEnable failed with table index = %d.", i);
        BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_indexed_get(unit, key, &info), error_msg);

        if (info.value != 1) {
            printf("bcm_switch_control_indexed_get returned value != 1, after the value was set.\n");
            return -1;
        }
    }

    encap_id = 0x1234;
    min_mc_prefix = 16;
    bcm_vlan_port_t vlan_port;
    bcm_vlan_port_t_init(&vlan_port);
    vlan_port.port = in_port;
    vlan_port.criteria = BCM_VLAN_PORT_MATCH_PORT_VLAN;
    vlan_port.vsi = vlan;
    vlan_port.match_vlan = vlan;
    vlan_port.flags = BCM_VLAN_PORT_CREATE_INGRESS_ONLY;
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_create(unit, vlan_port), "");
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_gport_add(unit, vlan, in_port, 0), "");
    bcm_vlan_port_t_init(&vlan_port);
    vlan_port.port = in_port;
    vlan_port.criteria = BCM_VLAN_PORT_MATCH_PORT_VLAN;
    vlan_port.vsi = vlan + 1;
    vlan_port.match_vlan = vlan + 1;
    vlan_port.flags = BCM_VLAN_PORT_CREATE_INGRESS_ONLY;
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_create(unit, vlan_port), "");
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_gport_add(unit, vlan + 1, in_port, 0), "");

    snprintf(error_msg, sizeof(error_msg), "intf_out out_port %d", out_port);
    BCM_IF_ERROR_RETURN_MSG(out_port_set(unit, out_port), error_msg);
    BCM_IF_ERROR_RETURN_MSG(get_first_fec_in_range_which_not_in_ecmp_range(unit, 0, 0, &egress_intf), error_msg);

    /*Create L3 interface*/
    bcm_l3_intf_t_init(l3if);
    sal_memcpy(l3if.l3a_mac_addr, mac_l3_ingress_add, 6);
    l3if.l3a_vid = vlan;
    l3if.l3a_vrf = vlan;
    BCM_IF_ERROR_RETURN_MSG(bcm_l3_intf_create(unit, &l3if), "");

    /*Create L3 interface for the public entries to hit*/
    bcm_l3_intf_t_init(l3if_public);
    sal_memcpy(l3if_public.l3a_mac_addr, mac_l3_ingress_public_add, 6);
    l3if_public.l3a_vid = vlan + 1;
    l3if_public.l3a_vrf = vlan + 1;
    BCM_IF_ERROR_RETURN_MSG(bcm_l3_intf_create(unit, &l3if_public), "");

    bcm_l3_ingress_t l3_ing_if;
    bcm_l3_ingress_t_init(&l3_ing_if);

    l3_ing_if.flags = BCM_L3_INGRESS_WITH_ID; /* must, as we update exist RIF */
    l3_ing_if.vrf = l3if_public.l3a_vrf;
    l3_ing_if.flags |= BCM_L3_INGRESS_GLOBAL_ROUTE;

    BCM_IF_ERROR_RETURN_MSG(bcm_l3_ingress_create(unit, l3_ing_if, l3if_public.l3a_intf_id), "");

    BCM_IF_ERROR_RETURN_MSG(l3__egress_only_encap__create_inner(unit, 0, &encap_id, mac_l3_egress_add, vlan, 0, 0),
        "create egress object ARP only");
    BCM_IF_ERROR_RETURN_MSG(l3__egress_only_fec__create_inner(unit, egress_intf, l3if.l3a_intf_id, encap_id, out_port,0, 0, 0, 0,&l3egid),
        "create egress object FEC only");
    egress_intf = l3egid;

    /*Create L3 interface for ipmc, vlan + 2 to avoid fallback to bridge */
    bcm_l3_intf_t_init(l3if_mc);
    sal_memcpy(l3if_mc.l3a_mac_addr, mac_l3_ingress_add, 6);
    l3if_mc.l3a_vid = vlan + 2;
    l3if_mc.l3a_vrf = vlan + 2;
    BCM_IF_ERROR_RETURN_MSG(bcm_l3_intf_create(unit, &l3if_mc), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_multicast_create(unit, mc_flags, &ipmc_group), "");

    bcm_multicast_replication_t replication;
    bcm_multicast_replication_t_init(replication);
    replication.encap1 = vlan + 2;
    replication.port = out_port;
    BCM_IF_ERROR_RETURN_MSG(bcm_multicast_add(unit, ipmc_group, BCM_MULTICAST_INGRESS_GROUP, 1, replication), "");

    bcm_l3_route_t route;
    bcm_ip6_t ip6;
    bcm_ip6_t ip6_mask;

    int prefix_length;

    for (prefix_length = 128; prefix_length >= 8; prefix_length-=1) {
        bcm_l3_route_t_init(&route);
        ipv6_create_mask(route.l3a_ip6_mask, prefix_length);
        ipv6_create_mask(route.l3a_ip6_net, prefix_length);
        /*Set the first byte to 0 so it would not be a valid MC address*/
        route.l3a_ip6_net[0] = 0x0;
        route.l3a_flags = BCM_L3_IP6;
        route.l3a_vrf = prefix_length % 2 ? vlan : 0;
        route.l3a_intf = egress_intf; /* fec */
        snprintf(error_msg, sizeof(error_msg), "IPv6: prefix_length = %d.", prefix_length);
        BCM_IF_ERROR_RETURN_MSG(bcm_l3_route_add(unit, &route), error_msg);
    }

    /*Add private default IPv6 route*/
    bcm_l3_route_t_init(&route);
    ipv6_create_mask(route.l3a_ip6_mask, 0);
    ipv6_create_mask(route.l3a_ip6_net, 0);
    route.l3a_flags = BCM_L3_IP6;
    route.l3a_vrf = vlan;
    route.l3a_intf = egress_intf; /* fec */
    snprintf(error_msg, sizeof(error_msg), "IPv4: prefix_length = %d.", prefix_length);
    BCM_IF_ERROR_RETURN_MSG(bcm_l3_route_add(unit, &route), error_msg);

    /*Add public default IPv6 route*/
    bcm_l3_route_t_init(&route);
    ipv6_create_mask(route.l3a_ip6_mask, 0);
    ipv6_create_mask(route.l3a_ip6_net, 0);
    route.l3a_flags = BCM_L3_IP6;
    route.l3a_vrf = 0;
    route.l3a_intf = egress_intf; /* fec */
    snprintf(error_msg, sizeof(error_msg), "IPv4: prefix_length = %d.", prefix_length);
    BCM_IF_ERROR_RETURN_MSG(bcm_l3_route_add(unit, &route), error_msg);

    for (prefix_length = 32; prefix_length >= 5; prefix_length-=1) {
        bcm_l3_route_t_init(&route);
        route.l3a_ip_mask = bcm_ip_mask_create(prefix_length);
        /*Set the first nibble to 0 so it would not be a valid MC address*/
        route.l3a_subnet = (0x00000000 | (bcm_ip_mask_create(prefix_length) & 0x0FFFFFFF));
        route.l3a_subnet = route.l3a_subnet & route.l3a_ip_mask;
        route.l3a_vrf = prefix_length % 2 ? vlan : 0;
        route.l3a_intf = egress_intf; /* fec */
        snprintf(error_msg, sizeof(error_msg), "IPv4: prefix_length = %d.", prefix_length);
        BCM_IF_ERROR_RETURN_MSG(bcm_l3_route_add(unit, &route), error_msg);
    }

    /*Add private default IPv4 route*/
    bcm_l3_route_t_init(&route);
    route.l3a_ip_mask = 0x0;
    route.l3a_subnet = 0x0;
    route.l3a_subnet = route.l3a_subnet & route.l3a_ip_mask;
    route.l3a_vrf = vlan;
    route.l3a_intf = egress_intf; /* fec */
    snprintf(error_msg, sizeof(error_msg), "IPv4: prefix_length = %d.", prefix_length);
    BCM_IF_ERROR_RETURN_MSG(bcm_l3_route_add(unit, &route), error_msg);

    /*Add public default IPv4 route*/
    bcm_l3_route_t_init(&route);
    route.l3a_ip_mask = 0x0;
    route.l3a_subnet = 0x0;
    route.l3a_subnet = route.l3a_subnet & route.l3a_ip_mask;
    route.l3a_vrf = 0;
    route.l3a_intf = egress_intf; /* fec */
    snprintf(error_msg, sizeof(error_msg), "IPv4: prefix_length = %d.", prefix_length);
    BCM_IF_ERROR_RETURN_MSG(bcm_l3_route_add(unit, &route), error_msg);

    bcm_ipmc_addr_t ipmc_addr;

    for (prefix_length = 128; prefix_length >= min_mc_prefix; prefix_length-=1) {
        bcm_ipmc_addr_t_init(&ipmc_addr);
        ipv6_create_mask(ipmc_addr.mc_ip6_mask, prefix_length);
        ipv6_create_mask(ipmc_addr.mc_ip6_addr, prefix_length);
        ipmc_addr.vrf = prefix_length % 2 ? vlan : vlan + 1;
        ipmc_addr.group = ipmc_group;
        ipmc_addr.flags = BCM_IPMC_IP6;
        snprintf(error_msg, sizeof(error_msg), "IPv6: prefix_length = %d.", prefix_length);
        BCM_IF_ERROR_RETURN_MSG(bcm_ipmc_add(unit, ipmc_addr), error_msg);
    }

    for (prefix_length = 32; prefix_length >= 8; prefix_length-=1) {
        bcm_ipmc_addr_t_init(&ipmc_addr);
        ipmc_addr.mc_ip_addr = (0xE0000000 | (bcm_ip_mask_create(prefix_length) & 0x00FFFFFF));
        ipmc_addr.mc_ip_mask = bcm_ip_mask_create(prefix_length);
        ipmc_addr.vrf = prefix_length % 2 ? vlan : 0;
        ipmc_addr.group = ipmc_group;
        snprintf(error_msg, sizeof(error_msg), "IPv4: prefix_length = %d.", prefix_length);
        BCM_IF_ERROR_RETURN_MSG(bcm_ipmc_add(unit, ipmc_addr), error_msg);
    }

    return BCM_E_NONE;
}

/*global variables used for the traverse function*/
/*
 * Counts the number of correctly traversed routes.
 * A route is only counted if its hitbit is according to the pattern.
 */
int kaps_hitbits_entry_counter;
/*
 * First round is without BCM_L3_HIT_CLEAR, expect hitbits set
 * Second round is with BCM_L3_HIT_CLEAR, expect hitbits set
 * Third round expect hitbits to be clear
 */
int kaps_hitbits_round;

/*For UC the hitbit pattern in this example is that (prefix_length % 3 != 0) and default routes are set*/
int kaps_hitbits_uc_verify_entries_traverse(int unit, int index, bcm_l3_route_t *info, void *user_data)
{
    int round = kaps_hitbits_round;
    int prefix_length;
    int ipv4 = 0;

    if ((info->l3a_flags & BCM_L3_IP6) == 0) {
        prefix_length = bcm_ip_mask_length(info->l3a_ip_mask);
        ipv4 = 1;
    } else {
        prefix_length = bcm_ip6_mask_length(info->l3a_ip6_mask);
    }

    /*Verify the hitbit pattern*/
    if (((prefix_length % 3 != 0) || (prefix_length == 0)) && (round != 2)) {
        if ((info->l3a_flags & BCM_L3_HIT) == 0) {
            printf ("IPv%d UC: HITBIT expected to be set, but it is not set. prefix_length = %d. round = %d.\n", ipv4?4:6, prefix_length, round);
            print *info;
            return -1;
        } else {
            printf ("IPv%d UC: HITBIT correctly set. prefix_length = %d. round = %d.\n", ipv4?4:6, prefix_length, round);
        }
    } else {
        if ((info->l3a_flags & BCM_L3_HIT) != 0) {
            printf ("IPv%d UC: HITBIT expected not to be set, but it is set. prefix_length = %d. round = %d.\n", ipv4?4:6, prefix_length, round);
            print *info;
            printf ("False positives are possible due to certain prefixes containing shorter prefixes.\n");
            /*False-positive are expected due to certain prefixes containing shorter prefixes*/
            /*return -1;*/
        } else {
            printf ("IPv%d UC: HITBIT correctly not set. prefix_length = %d. round = %d.\n", ipv4?4:6, prefix_length, round);
        }
    }

    kaps_hitbits_entry_counter++;

    printf ("Route traverse index: %d verified\n", index);
    return 0;
}

int kaps_hitbits_uc_verify_entries(int unit, int ipv4, int iteration) {
    char error_msg[200]={0,};
    int vlan = 5;
    bcm_l3_route_t route;
    int prefix_length;
    int public_private_i;
    int round;
    int max_prefix_length, min_prefix_length;

    if (ipv4) {
        max_prefix_length = 32;
        min_prefix_length = 5;
    } else {
        max_prefix_length = 128;
        min_prefix_length = 8;
    }

    /*
     * First round is without BCM_L3_HIT_CLEAR, expect hitbits set
     * Second round is with BCM_L3_HIT_CLEAR, expect hitbits set
     * Third round expect hitbits to be clear
     */
    for (round = 0; round < 3; round++) {
        if (iteration == 0) {
            /*Check get functionality*/
            for (prefix_length = max_prefix_length; prefix_length >= min_prefix_length; prefix_length-=1) {
                bcm_l3_route_t_init(&route);
                if (ipv4) {
                    route.l3a_ip_mask = bcm_ip_mask_create(prefix_length);
                    /*Set the first nibble to 0 so it would not be a valid MC address*/
                    route.l3a_subnet = (0x00000000 | (bcm_ip_mask_create(prefix_length) & 0x0FFFFFFF));
                    route.l3a_subnet = route.l3a_subnet & route.l3a_ip_mask;
                } else {
                    ipv6_create_mask(route.l3a_ip6_mask, prefix_length);
                    ipv6_create_mask(route.l3a_ip6_net, prefix_length);
                    /*Set the first byte to 0 so it would not be a valid MC address*/
                    route.l3a_ip6_net[0] = 0x0;
                    route.l3a_flags |= BCM_L3_IP6;

                    if ((prefix_length < 48) && (prefix_length > 44)) {
                        /*
                         * The scale feature in this example runs with long prefix of 48 and short prefix of 44.
                         * Skip the prefixes in between.
                         */
                        continue;
                    }
                }
                route.l3a_vrf = prefix_length % 2 ? vlan : 0;
                if (round == 1) {
                    route.l3a_flags |= BCM_L3_HIT_CLEAR;
                }
                snprintf(error_msg, sizeof(error_msg), "IPv%d: prefix_length = %d.", ipv4?4:6, prefix_length);
                BCM_IF_ERROR_RETURN_MSG(bcm_l3_route_get(unit, &route), error_msg);

                /*Verify the hitbit pattern*/
                if ((prefix_length % 3 != 0) && (round != 2)) {
                    if ((route.l3a_flags & BCM_L3_HIT) == 0) {
                        printf ("IPv%d UC: HITBIT expected to be set, but it is not set. prefix_length = %d. round = %d.\n", ipv4?4:6, prefix_length, round);
                        print route;
                        return -1;
                    } else {
                        printf ("IPv%d UC: HITBIT correctly set. prefix_length = %d. round = %d.\n", ipv4?4:6, prefix_length, round);
                    }
                } else {
                    if ((route.l3a_flags & BCM_L3_HIT) != 0) {
                        printf ("IPv%d UC: HITBIT expected not to be set, but it is set. prefix_length = %d. round = %d.\n", ipv4?4:6, prefix_length, round);
                        print route;
                        printf ("False positives are possible due to certain prefixes containing shorter prefixes.\n");
                        /*False-positive are expected due to certain prefixes containing shorter prefixes*/
                        /*return -1;*/
                    } else {
                        printf ("IPv%d UC: HITBIT correctly not set. prefix_length = %d. round = %d.\n", ipv4?4:6, prefix_length, round);
                    }
                }
            }

            /*Verify private and public default routes*/
            for (public_private_i = 0; public_private_i < 2; public_private_i++) {
                bcm_l3_route_t_init(&route);
                if (ipv4) {
                    route.l3a_ip_mask = 0x00000000;
                    route.l3a_subnet = 0x00000000;
                } else {
                    ipv6_create_mask(route.l3a_ip6_mask, 0);
                    ipv6_create_mask(route.l3a_ip6_net, 0);
                    route.l3a_flags |= BCM_L3_IP6;
                }
                route.l3a_vrf = public_private_i % 2 ? vlan : 0;
                if (round == 1) {
                    route.l3a_flags |= BCM_L3_HIT_CLEAR;
                }
                snprintf(error_msg, sizeof(error_msg), "IPv%d: prefix_length = %d.", ipv4?4:6, 0);
                BCM_IF_ERROR_RETURN_MSG(bcm_l3_route_get(unit, &route), error_msg);

                /*Verify the hitbit pattern, default routes are both hit (public+private)*/
                if (round != 2) {
                    if ((route.l3a_flags & BCM_L3_HIT) == 0) {
                        printf ("IPv%d UC DEFAULT: HITBIT expected to be set, but it is not set. iteration = %d. round = %d.\n", ipv4?4:6, public_private_i, round);
                        print route;
                        return -1;
                    }
                } else {
                    if ((route.l3a_flags & BCM_L3_HIT) != 0) {
                        printf ("IPv%d UC DEFAULT: HITBIT expected not to be set, but it is set. iteration = %d. round = %d.\n", ipv4?4:6, prefix_length, round);
                        print route;
                        printf ("False positives are possible due to certain prefixes containing shorter prefixes.\n");
                        /*False-positive are expected due to certain prefixes containing shorter prefixes*/
                        /*return -1;*/
                    }
                }
            }
        } else {
            /*Check iterator functionality*/
            int flags = 0;

            int expected_entry_counter;

            if (ipv4) {
                /*We're expecting a total of 30 routes, 32-5+1 and 2 default routes*/
                expected_entry_counter = 30;
            } else {
                flags |= BCM_L3_IP6;
                /*We're expecting a total of 123 routes, 128-8+1 and 2 default routes*/
                expected_entry_counter = 123;
            }

            if (round == 1) {
                flags |= BCM_L3_HIT_CLEAR;
            }

            kaps_hitbits_round = round;
            kaps_hitbits_entry_counter = 0;
            snprintf(error_msg, sizeof(error_msg), "IPv%d: round = %d.", ipv4?4:6, round);
            BCM_IF_ERROR_RETURN_MSG(bcm_l3_route_traverse(unit, flags, 0, 0, kaps_hitbits_uc_verify_entries_traverse, NULL), error_msg);

            if (kaps_hitbits_entry_counter != expected_entry_counter) {
                printf ("IPv%d: bcm_l3_route_traverse failed, expected_entry_counter: %d, kaps_hitbits_entry_counter : %d.\n", ipv4?4:6, expected_entry_counter, kaps_hitbits_entry_counter);
                return -1;
            }
        }

        /*Prevent race conditions of clearing hitbits and sending packets*/
        snprintf(error_msg, sizeof(error_msg), "IPv%d: bcmSwitchDescCommit round = %d.", ipv4?4:6, round);
        BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_set(unit, bcmSwitchDescCommit, 1), error_msg);
    }

    return BCM_E_NONE;
}

/*Entries with prefix higher than high and lower than low are expected to be hit*/
int kaps_mc_prefix_length_hit_high, kaps_mc_prefix_length_hit_low;

/*For MC the hitbit pattern in this example is that kaps_mc_prefix_length_hit_low < prefix_length < kaps_mc_prefix_length_hit_high is not set */
int kaps_hitbits_mc_verify_entries_traverse(int unit, bcm_ipmc_addr_t *info, void *user_data)
{
    int round = kaps_hitbits_round;
    int prefix_length;

    if ((info->flags & BCM_IPMC_IP6) == 0) {
        prefix_length = bcm_ip_mask_length(info->mc_ip_mask);
    } else {
        prefix_length = bcm_ip6_mask_length(info->mc_ip6_mask);
    }

    /*Verify the hitbit pattern*/
    if ((((prefix_length <= kaps_mc_prefix_length_hit_low) || (prefix_length >= kaps_mc_prefix_length_hit_high)) || (prefix_length == 0)) && (round != 2)) {
        if ((info->flags & BCM_IPMC_HIT) == 0) {
            printf ("IPv4 MC %d: HITBIT expected to be set, but it is not set. prefix_length = %d. round = %d.\n", kaps_hitbits_entry_counter, prefix_length, round);
            print *info;
            return -1;
        } else {
            printf ("IPv4 MC %d: HITBIT correctly set. prefix_length = %d. round = %d.\n", kaps_hitbits_entry_counter, prefix_length, round);
        }
    } else {
        if ((info->flags & BCM_IPMC_HIT) != 0) {
            printf ("IPv4 MC %d: HITBIT expected not to be set, but it is set. prefix_length = %d. round = %d.\n", kaps_hitbits_entry_counter, prefix_length, round);
            print *info;
            printf ("False positives are possible due to certain prefixes containing shorter prefixes.\n");
            /*False-positive are expected due to certain prefixes containing shorter prefixes*/
            /*return -1;*/
        } else {
            printf ("IPv4 MC %d: HITBIT correctly not set. prefix_length = %d. round = %d.\n", kaps_hitbits_entry_counter, prefix_length, round);
        }
    }

    kaps_hitbits_entry_counter++;

    printf ("Route traverse prefix_length: %d verified\n", prefix_length);
    return 0;
}

/*First iteration checks bcm_ipmc_find functionality, Second iteration checks bcm_ipmc_traverse functionality*/
int kaps_hitbits_mc_verify_entries(int unit, int ipv4, int iteration) {
    char error_msg[200]={0,};
    int vlan = 5;
    bcm_ipmc_addr_t ipmc_addr;
    int prefix_length;
    int public_private_i;
    int round;
    int max_prefix_length, min_prefix_length;

    if (ipv4) {
        max_prefix_length = 32;
        min_prefix_length = 8;
        kaps_mc_prefix_length_hit_high = 18;
        kaps_mc_prefix_length_hit_low = 12;
    } else {
        max_prefix_length = 128;
        min_prefix_length = 16;
        kaps_mc_prefix_length_hit_high = 80;
        kaps_mc_prefix_length_hit_low = 60;
    }

    /*
     * First round is without BCM_IPMC_HIT_CLEAR, expect hitbits set
     * Second round is with BCM_IPMC_HIT_CLEAR, expect hitbits set
     * Third round expect hitbits to be clear
     */
    for (round = 0; round < 3; round++) {
        if (iteration == 0) {
            /*Check get functionality*/
            for (prefix_length = max_prefix_length; prefix_length >= min_prefix_length; prefix_length-=1) {
                bcm_ipmc_addr_t_init(&ipmc_addr);
                if (ipv4) {
                    ipmc_addr.mc_ip_addr = (0xE0000000 | (bcm_ip_mask_create(prefix_length) & 0x00FFFFFF));
                    ipmc_addr.mc_ip_mask = bcm_ip_mask_create(prefix_length);
                } else {
                    ipv6_create_mask(ipmc_addr.mc_ip6_mask, prefix_length);
                    ipv6_create_mask(ipmc_addr.mc_ip6_addr, prefix_length);
                    ipmc_addr.flags = BCM_IPMC_IP6;
                }
                if (!ipv4)
                {
                    ipmc_addr.vrf = prefix_length % 2 ? vlan : vlan + 1;
                }
                else
                {
                    ipmc_addr.vrf = prefix_length % 2 ? vlan : 0;
                }
                if (round == 1) {
                    ipmc_addr.flags |= BCM_IPMC_HIT_CLEAR;
                }
                snprintf(error_msg, sizeof(error_msg), "IPv%d: prefix_length = %d.", ipv4?4:6, prefix_length);
                BCM_IF_ERROR_RETURN_MSG(bcm_ipmc_find(unit, &ipmc_addr), error_msg);

                /*Verify the hitbit pattern*/
                if (((prefix_length <= kaps_mc_prefix_length_hit_low) || (prefix_length >= kaps_mc_prefix_length_hit_high)) && (round != 2)) {
                    if ((ipmc_addr.flags & BCM_IPMC_HIT) == 0) {
                        printf ("IPv%d MC: HITBIT expected to be set, but it is not set. prefix_length = %d. round = %d.\n", ipv4?4:6, prefix_length, round);
                        print ipmc_addr;
                        return -1;
                    } else {
                        printf ("IPv%d MC: HITBIT correctly set. prefix_length = %d. round = %d.\n", ipv4?4:6, prefix_length, round);
                    }
                } else {
                    if ((ipmc_addr.flags & BCM_IPMC_HIT) != 0) {
                        printf ("IPv%d MC: HITBIT expected not to be set, but it is set. prefix_length = %d. round = %d.\n", ipv4?4:6, prefix_length, round);
                        print ipmc_addr;
                        printf ("False positives are possible due to certain prefixes containing shorter prefixes.\n");
                        /*False-positive are expected due to certain prefixes containing shorter prefixes*/
                        /*return -1;*/
                    } else {
                        printf ("IPv%d MC: HITBIT correctly not set. prefix_length = %d. round = %d.\n", ipv4?4:6, prefix_length, round);
                    }
                }
            }

        } else {
            /*Check iterator functionality*/
            int flags = 0;

            int expected_entry_counter;

            if (ipv4) {
                /*We're expecting a total of 25 routes, 32-8+1 */
                expected_entry_counter = 25;
            } else {
                flags |= BCM_IPMC_IP6;
                /*We're expecting a total of 121 routes, 128-8+1*/
                expected_entry_counter = 113;
            }

            if (round == 1) {
                flags |= BCM_IPMC_HIT_CLEAR;
            }

            kaps_hitbits_round = round;
            kaps_hitbits_entry_counter = 0;
            snprintf(error_msg, sizeof(error_msg), "IPv%d: round = %d.", ipv4?4:6, round);
            BCM_IF_ERROR_RETURN_MSG(bcm_ipmc_traverse(unit, flags, kaps_hitbits_mc_verify_entries_traverse, NULL), error_msg);

            if (kaps_hitbits_entry_counter != expected_entry_counter) {
                printf ("IPv%d: bcm_ipmc_traverse failed, expected_entry_counter: %d, kaps_hitbits_entry_counter : %d.\n", ipv4?4:6, expected_entry_counter, kaps_hitbits_entry_counter);
                return -1;
            }
        }

        /*Prevent race conditions of clearing hitbits and sending packets*/
        snprintf(error_msg, sizeof(error_msg), "IPv%d: bcmSwitchDescCommit round = %d.", ipv4?4:6, round);
        BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_set(unit, bcmSwitchDescCommit, 1), error_msg);
    }

    return BCM_E_NONE;
}



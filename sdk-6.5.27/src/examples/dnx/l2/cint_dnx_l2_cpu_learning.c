/*
 File: cint_dnx_l2_cpu_learning.c
 Purpose: Example of how to set l2 cpu learning with up to two devices.
           Example of how to enable cpu learn and handle learn and aged event.
 
 Notes:
    cint_dnx_l2_cpu_learning.c is built up on the top of cint_l2_cpu_learning.c
 
 Test Scenario - start 
 
 cint ../../../../src/examples/sand/utility/cint_sand_utils_global.c
 cint ../../../../src/examples/dnx/utility/cint_dnx_utils_global.c
 cint ../../../../src/examples/dnx/utility/cint_dnx_utils_vlan.c
 cint ../../../../src/examples/dnx/l2/cint_dnx_l2_cpu_learning.c
 cint
 l2_cpu_learning_run(0,200);
 exit;
 
 // run packet 1:
 //     ethernet header with DA 33 and any SA
 //     vlan tag with vlan tag id 33
 //     from any port
 tx 1 psrc=201 data=0x00000000003300000000000181000021ffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 
 // Received packets on unit 0 should be:
 // Source port: 0, Destination port: 0 
 // Data: 0x00000000003300000000000181000021ffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f200000000000000000000000 
 // Source port: 0, Destination port: 0 
 // Data: 0x000000004488000000001255ab00040000281060064810000000000000084000000000005c0000000000000000000000000000000000000000 
 
 // run packet 2:
 //    ethernet header with DA 44 and any SA
 //    vlan tag with vlan tag id 44
 //    from any port
 tx 1 psrc=201 data=0x0000000000440000000000028100002cffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
 
 // Received packets on unit 0 should be: 
 // Source port: 0, Destination port: 0 
 // Data: 0x0000000000440000000000028100002cffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f200000000000000000000000 
 // Source port: 0, Destination port: 0 
 // Data: 0x000000004488000000001255ab000400002810600648100000000000000b0000000000009c0000000000000000000000000000000000000000 
 
 //both packets will be sent to CPU
 
 Test Scenario - end
 
 
 Test Scenario - start
 cint ../../../../src/examples/dnx/utility/cint_dnx_utils_global.c
 cint ../../../../src/examples/dnx/utility/cint_dnx_utils_multicast.c
 cint ../../../../src/examples/dnx/l2/cint_dnx_l2_traverse.c
 cint ../../../../src/examples/dnx/l2/cint_dnx_l2_cpu_learning.c
 cint
 l2_entry_control_set(0,1|32);
 exit;
 
 cint
 l2_entry_event_handle_register(0);
 exit;
 
 Test Scenario - end
 */
 /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MACT Cpu Learning:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* SA and DA in learning msgs */
uint8 _src_mac_address[6] = {0x00, 0x00, 0x00, 0x00, 0x12, 0x55};
uint8 _dest_mac_address[6] = {0x00, 0x00, 0x00, 0x00, 0x44, 0x88};

/* DA in incoming packets */
uint8 _dest_mac_1[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x33};
uint8 _dest_mac_2[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x44};

struct l2_learning_info_s {
    bcm_gport_t cpu_port; /* cpu */
    bcm_vlan_t vlan_1;
    bcm_vlan_t vlan_2;
    int out_port;
};

int l2_entry_event_handler_called = 0;
l2_learning_info_s l2_learning_info;
int cpu_and_hw_learning = 0;
int refresh_test = 0;

int l2_learning_info_init(int unit, int port) {
    int count;
    bcm_port_config_t port_config;
    bcm_gport_t cpu;
    bcm_switch_control_key_t key;
    bcm_switch_control_info_t value_in;
    bcm_switch_control_info_t value_out;
    bcm_gport_t logical_port;

    /* get the cpu port */
    BCM_IF_ERROR_RETURN_MSG(bcm_port_config_get(unit, &port_config), "");

    /* get the first cpu port with out header type = ETH and in header type = INJECTED_2_PP */
    BCM_PBMP_ITER(port_config.cpu, cpu) {
        BCM_GPORT_LOCAL_SET(l2_learning_info.cpu_port, cpu);

        key.index = 2;      /* 1 is in, 2 is out */
        key.type = bcmSwitchPortHeaderType;
        BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_indexed_port_get(unit, l2_learning_info.cpu_port, key, &value_out),
            "out header type");

        key.index = 1;      /* 1 is in, 2 is out */
        BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_indexed_port_get(unit, l2_learning_info.cpu_port, key, &value_in),
            "in header type");

        if (value_out.value == BCM_SWITCH_PORT_HEADER_TYPE_ETH && value_in.value == BCM_SWITCH_PORT_HEADER_TYPE_INJECTED_2_PP)
        {
            break;
        }
    }

    printf("cpu_port = 0x%x\n", l2_learning_info.cpu_port);

    l2_learning_info.vlan_1 = 33;
    l2_learning_info.vlan_2 = 44;
    l2_learning_info.out_port = port;

    return BCM_E_NONE;
}

/* set learning mode to ingress_distributed (if distributed == 1) or ingress_centralized (otherwise) */
int learning_mode_set(int unit, int distributed) {
    int mode;

    if (distributed) {
        /* change learning mode to ingress distributed */
        mode = BCM_L2_INGRESS_DIST;
    } else {
        /* change learning mode to ingress centralized */
        mode = BCM_L2_INGRESS_CENT;
    }

    BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_set(unit, bcmSwitchL2LearnMode, mode), "");

    return BCM_E_NONE;
}

/* Configure the DSP messages with vlan in the ethernet header */
int l2_cpu_learning_with_vlan(int unit, int port) {
    char error_msg[200]={0,};
    bcm_l2_learn_msgs_config_t learn_msgs;
    bcm_l2_addr_distribute_t distribution;
    int age_seconds;
    bcm_l2_addr_t l2addr_1, l2addr_2;
    int aging_profiles_bug = 0;

    aging_profiles_bug = *(dnxc_data_get(unit, "l2", "feature", "age_out_and_refresh_profile_selection", NULL));
    l2_learning_info_init(unit, port);

    /* create vlan 33 */
    snprintf(error_msg, sizeof(error_msg), "with vlan#1 %d", l2_learning_info.vlan_1);
    BCM_IF_ERROR_RETURN_MSG(vlan__init_vlan(unit, l2_learning_info.vlan_1), error_msg);

    /* enter the DA of the arriving packet and send it to port 4 */
    bcm_l2_addr_t_init(&l2addr_1,_dest_mac_1,l2_learning_info.vlan_1);
    l2addr_1.port = l2_learning_info.out_port;
    l2addr_1.flags = BCM_L2_STATIC;
    BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_add(unit, l2addr_1), "");

    /* set learning through cpu with vlan in the DSP (shadow) */
    /* set format of learning messages */
    bcm_l2_learn_msgs_config_t_init(&learn_msgs);
    learn_msgs.flags = BCM_L2_LEARN_MSG_SHADOW;
    /* follow attributes set the destination port/group shadow messages are distributed to */
    /*learn_msgs.flags |= BCM_L2_LEARN_MSG_DEST_MULTICAST; - not needed as dest is port*/
    learn_msgs.dest_port = l2_learning_info.cpu_port;

    /* follow attributes set the encapsulation of the learning messages */
    /* learning message encapsulated with ethernet header */
    learn_msgs.flags |= BCM_L2_LEARN_MSG_ETH_ENCAP;
    learn_msgs.ether_type = 0xab00;
    learn_msgs.tpid = 0x8100;
    learn_msgs.vlan = l2_learning_info.vlan_1;
    sal_memcpy(learn_msgs.src_mac_addr, _src_mac_address, 6);
    sal_memcpy(learn_msgs.dst_mac_addr, _dest_mac_address, 6);
    /* default value of learn_msgs.vlan indicates packet is not tagged */
    /*learn_msgs.vlan/tpid/vlan_prio: not relevant as packet is not tagged*/
    BCM_IF_ERROR_RETURN_MSG(bcm_l2_learn_msgs_config_set(unit, &learn_msgs), "");

    /* set learning mode to ingress centralized */
    BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_set(unit, bcmSwitchL2LearnMode, BCM_L2_INGRESS_CENT), "");

    distribution.vid = l2_learning_info.vlan_1;
    distribution.flags = BCM_L2_ADDR_DIST_LEARN_EVENT | BCM_L2_ADDR_DIST_STATION_MOVE_EVENT | BCM_L2_ADDR_DIST_AGED_OUT_EVENT | BCM_L2_ADDR_DIST_SET_SHADOW_DISTRIBUTER;
    if (aging_profiles_bug)
    {
        distribution.flags = BCM_L2_ADDR_DIST_LEARN_EVENT | BCM_L2_ADDR_DIST_STATION_MOVE_EVENT | BCM_L2_ADDR_DIST_SET_SHADOW_DISTRIBUTER;
        BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_msg_distribute_set(unit, &distribution), "");

        distribution.vid = -1;
        distribution.flags = BCM_L2_ADDR_DIST_AGED_OUT_EVENT | BCM_L2_ADDR_DIST_SET_SHADOW_DISTRIBUTER;
    }

    BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_msg_distribute_set(unit, &distribution), "");

    return BCM_E_NONE;
}

int l2_cpu_learning_run_olp_to_queue(int unit, int olpDestPort, int outPort) {
    char error_msg[200]={0,};
    bcm_l2_learn_msgs_config_t learn_msgs;
    bcm_l2_addr_distribute_t distribution;
    int age_seconds, meta_cycle;
    bcm_l2_addr_t l2addr_1, l2addr_2;
    bcm_gport_t olpDestQueue;
    int aging_profiles_bug = 0;

    l2_learning_info_init(unit, outPort);

    aging_profiles_bug = *(dnxc_data_get(unit, "l2", "feature", "age_out_and_refresh_profile_selection", NULL));
    /* convert port to tm queue */
    BCM_GPORT_UNICAST_QUEUE_GROUP_SET(olpDestQueue, (olpDestPort*8) + 24);
    printf("cpu_port = 0x%x, queue = 0x%x\n", olpDestPort, olpDestQueue);

    /* create vlan - 33 */
    snprintf(error_msg, sizeof(error_msg), "with vlan#1 %d", l2_learning_info.vlan_1);
    BCM_IF_ERROR_RETURN_MSG(vlan__init_vlan(unit, l2_learning_info.vlan_1), error_msg);

    /* enter the DA's of the arriving packets and send them to port 4 */
    bcm_l2_addr_t_init(&l2addr_1,_dest_mac_1,l2_learning_info.vlan_1);
    l2addr_1.port = l2_learning_info.out_port;
    l2addr_1.flags = BCM_L2_STATIC;
    BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_add(unit, l2addr_1), "");

    /* set learning through cpu (shadow) */
    /* set format of learning messages */
    bcm_l2_learn_msgs_config_t_init(&learn_msgs);
    learn_msgs.flags = BCM_L2_LEARN_MSG_SHADOW;
    /* set the destination tm queue to shadow messages */
    learn_msgs.dest_port = olpDestQueue;

    /* follow attributes set the encapsulation of the learning messages */
    /* learning message encapsulated with ethernet header */
    learn_msgs.flags |= BCM_L2_LEARN_MSG_ETH_ENCAP;
    learn_msgs.ether_type = 0xab00;
    sal_memcpy(learn_msgs.src_mac_addr, _src_mac_address, 6);
    sal_memcpy(learn_msgs.dst_mac_addr, _dest_mac_address, 6);
    BCM_IF_ERROR_RETURN_MSG(bcm_l2_learn_msgs_config_set(unit, &learn_msgs), "");

    /* set learning mode to ingress centralized */
    BCM_IF_ERROR_RETURN_MSG(learning_mode_set(unit, 0), "");

    bcm_l2_addr_distribute_t_init(&distribution);
    /* set learning */
    distribution.vid = l2_learning_info.vlan_1;
    distribution.flags = BCM_L2_ADDR_DIST_LEARN_EVENT | BCM_L2_ADDR_DIST_STATION_MOVE_EVENT | BCM_L2_ADDR_DIST_AGED_OUT_EVENT |BCM_L2_ADDR_DIST_SET_SHADOW_DISTRIBUTER;

    if (aging_profiles_bug)
    {
        distribution.flags = BCM_L2_ADDR_DIST_LEARN_EVENT | BCM_L2_ADDR_DIST_STATION_MOVE_EVENT | BCM_L2_ADDR_DIST_SET_SHADOW_DISTRIBUTER;
        BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_msg_distribute_set(unit, &distribution), "");

        distribution.vid = -1;
        distribution.flags = BCM_L2_ADDR_DIST_AGED_OUT_EVENT | BCM_L2_ADDR_DIST_SET_SHADOW_DISTRIBUTER;
    }

    BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_msg_distribute_set(unit, &distribution), "");

    /* set aging, so there'll be refresh */
    meta_cycle = 1;
    BCM_IF_ERROR_RETURN_MSG(bcm_l2_age_timer_meta_cycle_set(unit, meta_cycle), "");

    return BCM_E_NONE;
}

int l2_cpu_learning_run(int unit, int port) {

    char error_msg[200]={0,};
    bcm_l2_learn_msgs_config_t learn_msgs;
    bcm_l2_addr_distribute_t distribution;
    int age_seconds, meta_cycle;
    bcm_l2_addr_t l2addr_1, l2addr_2;
    int aging_profiles_bug = 0;
    int static_age_out_bug = 0;

    l2_learning_info_init(unit, port);
    /* create 2 vlans - 33, 44 */
    snprintf(error_msg, sizeof(error_msg), "with vlan#1 %d", l2_learning_info.vlan_1);
    BCM_IF_ERROR_RETURN_MSG(vlan__init_vlan(unit, l2_learning_info.vlan_1), error_msg);

    snprintf(error_msg, sizeof(error_msg), "with vlan#2 %d", l2_learning_info.vlan_2);
    BCM_IF_ERROR_RETURN_MSG(vlan__init_vlan(unit, l2_learning_info.vlan_2), error_msg);

    /* enter the DA's of the arriving packets and send them to port 4 */
    bcm_l2_addr_t_init(&l2addr_1,_dest_mac_1,l2_learning_info.vlan_1);
    l2addr_1.port = l2_learning_info.out_port;
    l2addr_1.flags = BCM_L2_STATIC;
    BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_add(unit, l2addr_1), "");

    bcm_l2_addr_t_init(&l2addr_1,_dest_mac_2,l2_learning_info.vlan_2);
    l2addr_1.port = l2_learning_info.out_port;
    l2addr_1.flags = BCM_L2_STATIC;
    BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_add(unit, l2addr_1), "");

    /* set learning through cpu (shadow) */
    /* set format of learning messages */
    bcm_l2_learn_msgs_config_t_init(&learn_msgs);
    learn_msgs.flags = BCM_L2_LEARN_MSG_SHADOW;
    /* follow attributes set the destination port/group shadow messages are distributed to */
    /*learn_msgs.flags |= BCM_L2_LEARN_MSG_DEST_MULTICAST; - not needed as dest is port*/
    learn_msgs.dest_port = l2_learning_info.cpu_port;

    /* follow attributes set the encapsulation of the learning messages */
    /* learning message encapsulated with ethernet header */
    learn_msgs.flags |= BCM_L2_LEARN_MSG_ETH_ENCAP;
    learn_msgs.ether_type = 0xab00;
    sal_memcpy(learn_msgs.src_mac_addr, _src_mac_address, 6);
    sal_memcpy(learn_msgs.dst_mac_addr, _dest_mac_address, 6);
    /* default value of learn_msgs.vlan indicates packet is not tagged */
    /*learn_msgs.vlan/tpid/vlan_prio: not relevant as packet is not tagged*/
    BCM_IF_ERROR_RETURN_MSG(bcm_l2_learn_msgs_config_set(unit, &learn_msgs), "");

    /* set learning mode to ingress centralized */
    BCM_IF_ERROR_RETURN_MSG(learning_mode_set(unit, 0), "");

    bcm_l2_addr_distribute_t_init(&distribution);
    aging_profiles_bug = *(dnxc_data_get(unit, "l2", "feature", "age_out_and_refresh_profile_selection", NULL));
    static_age_out_bug = *(dnxc_data_get(unit, "l2", "feature", "static_mac_age_out", NULL));
    /* set learning */
    distribution.flags = BCM_L2_ADDR_DIST_LEARN_EVENT | BCM_L2_ADDR_DIST_STATION_MOVE_EVENT | BCM_L2_ADDR_DIST_AGED_OUT_EVENT |BCM_L2_ADDR_DIST_SET_SHADOW_DISTRIBUTER;
    if (aging_profiles_bug)
    {
        distribution.flags = BCM_L2_ADDR_DIST_AGED_OUT_EVENT | BCM_L2_ADDR_DIST_SET_SHADOW_DISTRIBUTER;
        distribution.vid = -1;
        BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_msg_distribute_set(unit, &distribution), "");
        distribution.flags = BCM_L2_ADDR_DIST_LEARN_EVENT | BCM_L2_ADDR_DIST_STATION_MOVE_EVENT | BCM_L2_ADDR_DIST_SET_SHADOW_DISTRIBUTER;
    }

    distribution.vid = l2_learning_info.vlan_1;
    BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_msg_distribute_set(unit, &distribution), "");

    distribution.vid = l2_learning_info.vlan_2;
    BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_msg_distribute_set(unit, &distribution), "");

    /* set aging, so there'll be refresh */
    if (!static_age_out_bug) {
        meta_cycle = 1;
        BCM_IF_ERROR_RETURN_MSG(bcm_l2_age_timer_meta_cycle_set(unit, meta_cycle), "");
    }

    return BCM_E_NONE;
}

void l2_entry_event_handle(int unit,
         bcm_l2_addr_t *l2addr,
         int operation,
         void *userdata)
{
    int rv = BCM_E_NONE;

    l2_entry_event_handler_called = 1;
    /* In case of CPU + HW learning, we suppose HW learning always is faster than CPU learning  */
    if (operation == BCM_L2_CALLBACK_LEARN_EVENT) {
        printf("BCM_L2_CALLBACK_LEARN_EVENT handle\n");
        l2_addr_print_entry(l2addr);
        if (cpu_and_hw_learning){
            BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_get(unit, l2addr->mac, l2addr->vid, l2addr), "");
        } else {
            BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_add(unit, l2addr), "");
        }
    } if (operation == BCM_L2_CALLBACK_MOVE_EVENT) {
        printf("BCM_L2_CALLBACK_MOVE_EVENT handle\n");
        l2_addr_print_entry(l2addr);
        l2addr->flags |= BCM_L2_STATIC;  /* This event handler is used by AT_Cint_l2_cpu_learning_move_static and should enter static entries */
        if (cpu_and_hw_learning){
            BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_get(unit, l2addr->mac, l2addr->vid, l2addr), "");
        } else {
            BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_add(unit, l2addr), "");
        }
    } else if (operation == BCM_L2_CALLBACK_AGE_EVENT) {
        printf("BCM_L2_CALLBACK_AGE_EVENT handle\n");
        l2_addr_print_entry(l2addr);
        if (refresh_test)
        {
            printf("For age event proccess when refresh_test=1, don't delete SA\n");
        }
        else
        {
            rv = bcm_l2_addr_delete(unit, l2addr->mac, l2addr->vid);
            if (cpu_and_hw_learning) {
                if (rv != BCM_E_NOT_FOUND) {
                    printf("Error for age event process\n");
                    return BCM_E_FAIL;
                }
            } else {
                BCM_IF_ERROR_RETURN_MSG(rv, "Error for age event process");
            }
        }
    } else if (operation == BCM_L2_CALLBACK_REFRESH_EVENT) {
        printf("BCM_L2_CALLBACK_REFRESH_EVENT handle\n");
        l2_addr_print_entry(l2addr);
        if (refresh_test)
        {
            printf("For refresh event proccess when refresh_test=1, delete SA\n");
            BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_delete(unit, l2addr->mac, l2addr->vid), "Error for refresh event process");
        }
    }

}

int l2_entry_control_set(int unit, int flags) {
    int age_seconds, meta_cycle;
    bcm_switch_event_control_t event_control;

    BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_set(unit, bcmSwitchL2LearnMode, flags), "");

    /* Enabling aging to 60 sec or 10 cycles */
    meta_cycle = 10;
    BCM_IF_ERROR_RETURN_MSG(bcm_l2_age_timer_meta_cycle_set(unit, meta_cycle), "");

    return BCM_E_NONE;

}

int l2_entry_event_handle_register(int unit) {
    bcm_l2_addr_t l2_addr;

    BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_register(unit,l2_entry_event_handle, NULL), "");

    return BCM_E_NONE;
}
int l2_entry_event_handle_unregister(int unit) {
    bcm_l2_addr_t l2_addr;

    BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_unregister(unit,l2_entry_event_handle, NULL), "");

    return BCM_E_NONE;
}

int cpu_learning_set(int unit) {
    BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_set(unit, bcmSwitchL2LearnMode, BCM_L2_INGRESS_CENT
                                | BCM_L2_LEARN_CPU), "");
    printf ("L2 learn mode set to CPU learning \n");

    BCM_IF_ERROR_RETURN_MSG(l2_entry_event_handle_register(unit), "");
    printf ("L2 callbacks registered. \n");
    return BCM_E_NONE;
}

int l2_event_distribute_set_per_lif(int unit, int vlan_port_id, int dist_flags) {
    bcm_l2_addr_distribute_t distribution;

    bcm_l2_addr_distribute_t_init(&distribution);
    distribution.gport = vlan_port_id;
    distribution.flags = dist_flags | BCM_L2_ADDR_DIST_GPORT;
    BCM_IF_ERROR_RETURN_MSG(bcm_l2_addr_msg_distribute_set(unit, &distribution), "");

    return BCM_E_NONE;
}

int l2_aging_set_per_lif(int unit, int vlan_port_id, int aging_profile, int aging_cycles) {
    bcm_l2_gport_control_info_t ctrl_info;

    bcm_l2_gport_control_info_t_init(&ctrl_info);
    ctrl_info.gport = vlan_port_id;
    ctrl_info.aging_cycles = aging_cycles;
    BCM_IF_ERROR_RETURN_MSG(bcm_l2_gport_control_info_set(unit, &ctrl_info), "");

    return BCM_E_NONE;
}

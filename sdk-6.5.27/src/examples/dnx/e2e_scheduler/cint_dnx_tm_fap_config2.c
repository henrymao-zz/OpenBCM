/*~~~~~~~~~~~~~~~~~~~~~~~~~~Cosq: E2E Scheduling~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
 * 
 *
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * File: cint_tm_fap_config2.c
 * Purpose: Example of SP Validation
 *
 * Environment
 *    -    Default Egress queue mapping in play.
 *    -    Default Egress Port Scheduler hierarchy in play.
 *    -    Default Ingress Scheduling Discipline (delay tolerance), queues sizes
 *    - Packet Size 1500
 *
 * - Port Scheduler
 *   - CL Scheduler (SP mode)
 *     - 4 FQ Schedulers
 *       - 1 Queue Group / Connector Group (4 elements in bundle) connected to
 *         corresponding FQ schedulers
 *       - 2nd Queue Group / Connector Group (4 elements in bundle) connected to
 *         corresponding FQ schedulers - Created by specifying BCM_COSQ_GPORT_TM_FLOW_ID flag.
 *
 * - test run 1
 *   - Destination port: System port. See SYS_PORT variable inside main. If
 *     destination port is not on modid 0, ingress configuration is done on unit 0
 *     and egress is done on unitid=sys_port_mod_id.
 *
 *   - Input
 *     - Queue Group 1 - Cos 0
 *       Input 500 Mbps
 *     - Queue Group 1 - Cos 1
 *       Input 500 Mbps
 *
 *   - Expected Output
 *     - Queue Group 1 - Cos 0
 *       Expected Output 500 Mbps
 *       Observed 500 Mbps
 *     - Queue Group 1 - Cos 1
 *       Expected Output 000 Mbps
 *       Observed 000 Mbps
 *
 * - test run 2
 *   - Input
 *     - Queue Group 1 - Cos 0
 *       Input 200 Mbps
 *     - Queue Group 1 - Cos 1
 *       Input 500 Mbps
 *
 *   - Expected Output
 *     - Queue Group 1 - Cos 0
 *       Expected Output 200 Mbps
 *       Observed 197 Mbps
 *     - Queue Group 1 - Cos 1
 *       Expected Output 300 Mbps
 *       Observed 328 Mbps
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  |                                                                                 |
 *  |                                        |                                        |
 *  |                                       SPR (500 Mbps)                            |
 *  |                                        |                                        |
 *  |                                       \/                                        |
 *  |                                      +----+                                     |
 *  |                                     /      \                                    |
 *  |                                    /   HR   \                                   |
 *  |                                   /          \                                  |
 *  |                                  +------------+                                 |
 *  |                                        |                                        |
 *  |                                       SPR (500 Mbps)                            |
 *  |                                        |                                        |
 *  |                                       \/                                        |
 *  |                                +----------------+                               |
 *  |                               / CL (4 SP levels) \                              |
 *  |                              /                    \                             |
 *  |                             / SP0   SP1  SP2   SP3 \                            |
 *  |                            +------------------------+                           |
 *  |                              /      |      |     \                              |
 *  |                             /       |      |      \                             |
 *  |                           SPR     SPR     SPR    SPR                            |
 *  |                    (500 Mbps)(500 Mbps)(500 Mbps)(500 Mbps)                     |
 *  |                         /           |      |         \                          |
 *  |                        /            |      |          \                         |
 *  |                       |/           \/     \/          \/                        |
 *  |                   +------+   +------+   +------+   +------+                     |
 *  |                  /   FQ   \ /   FQ   \ /   FQ   \ /   FQ   \                    |
 *  |                 +----------+----------+----------+----------+                   |
 *  |                     \            |          |          /                        |
 *  |                      \           |          |         /                         |
 *  |                     SPR         SPR        SPR       SPR                        |
 *  |                  (500 Mbps) (500 Mbps) (500 Mbps) (500 Mbps)                    |
 *  |                        \         |          |      /                            |
 *  |                        \/       \/         \/     \/                            |
 *  |                     |     |  |     |   |     |  |     |                         |
 *  | +----------------+  |     | +----------------+  |     |                         |
 *  | |Input2: 200 Mbps|  |     | |Input2: 500 Mbps|  |     |                         |
 *  | +----------------+  |     | +----------------+  |     |                         |
 *  |                     |     |  |     |   |     |  |     |                         |
 *  |                     +-----+  +-----+   +-----+  +-----+     +----------------+  |
 *  |                     Input1:500 Mbps                         |      KEY       |  |
 *  |                                                             +----------------+  |
 *  |                                                             |SPR- Rate Shaper|  |
 *  |                                                             |                |  |
 *  |                                                             +----------------+  |
 *  |                              +~~~~~~~~~~~~~~~~~~+                               |
 *  |                              |   Figure 5: SP   |                               |
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Warmboot test sequence:
 * coldboot
 *   export SOC_BOOT_FLAGS=0x000000
 * Test Scenario - start
    cint cint_warmboot_utilities.c
    cint cint_dnx_tm_fap_config2.c
 *
    cint
    tm_config2_setup(0, 0 *C2_FRONT_PANEL_PORT_TYPE*, 1 *C2_RESOURCE_TYPE_FIXED*);
    quit;
 *
    cint
    wb_sync_initiate(0);
    quit;
 * Test Scenario - end
 *
 * warmboot
 *   export SOC_BOOT_FLAGS=0x200000
 * Test Scenario - start
    cint cint_dnx_tm_fap_config2.c
 *
    cint
    tm_config2_verify(0, 0 *C2_FRONT_PANEL_PORT_TYPE*, 1 *C2_RESOURCE_TYPE_FIXED*);
    quit;
 * Test Scenario - end
 */

/*
 * General Definitions
 */
int C2_NUM_COS = 4;

int C2_E2E_INTERFACE_KBITS_SEC_MAX = 1000000; /* 1gbps */
int C2_E2E_INTERFACE_KBITS_SEC_MAX_MARGIN = 500; /* 500 kbps */

int C2_E2E_PORT_KBITS_SEC_MAX = 500000; /* 500mbps */
int C2_E2E_PORT_KBITS_SEC_MAX_MARGIN = 10; /* 10 kbits */

int C2_DEFAULT_E2E_SCHED_TYPE = bcmCosqSchedulerGportTypeHrEnhanced;
int C2_SCHED_CL_TYPE = bcmCosqSchedulerGportTypeClass4Sp;
int C2_SCHED_MODE = BCM_COSQ_SP1;
int C2_SCHED_KBITS_SEC_MAX = 500000; /* 500 Mbps */
int C2_SCHED_KBITS_SEC_MAX_MARGIN = 10; /* 10 Kbps */

int C2_SCHED_FQ_TYPE = bcmCosqSchedulerGportTypeFq;
int C2_SCHED_FQ_KBITS_SEC_MAX = 500000; /* 500 Mbps */
int C2_SCHED_FQ_KBITS_SEC_MAX_MARGIN = 10; /* 10 Kbps */

int C2_CONN_FLAGS = (BCM_COSQ_GPORT_VOQ_CONNECTOR);
int C2_CONN_KBITS_SEC_MAX = 500000; /* 500 Mbps */
int C2_CONN_KBITS_SEC_MAX_MARGIN = 10; /* 10 Kbps */

int C2_QUEUE_FLAGS = (BCM_COSQ_GPORT_UCAST_QUEUE_GROUP);

int C2_ISQ_ROOT_KBITS_SEC_MAX = 500000; /* 500000 Mbps */
int C2_ISQ_ROOT_KBITS_SEC_MAX_MARGIN = 500; /* 500 kbps */

/* handles */
int c2_ingr_unit = 0;
int c2_egr_unit = 0;
int c2_ingr_modid = 0;
int c2_egr_modid = 0;
bcm_gport_t c2_gport_ucast_voq_connector_group0[32];
bcm_gport_t c2_gport_ucast_voq_connector_group1[32];
bcm_gport_t c2_gport_ucast_queue_group0[32];
bcm_gport_t c2_gport_ucast_queue_group1[32];
bcm_gport_t c2_gport_ucast_scheduler[32];
bcm_gport_t c2_gport_ucast_scheduler_fq0[32];
bcm_gport_t c2_gport_ucast_scheduler_fq1[32];
bcm_gport_t c2_gport_ucast_scheduler_fq2[32];
bcm_gport_t c2_gport_ucast_scheduler_fq3[32];
bcm_gport_t c2_e2e_parent_gport[32];
bcm_gport_t c2_e2e_gport[32];
bcm_gport_t c2_sys_gport[32];


int credit_worth = *(dnxc_data_get(c2_ingr_unit, "iqs", "credit", "worth", NULL));
int multiplier = credit_worth / 1024;

int C2_SCHED_MAX_BURST = 3000 * multiplier;
int C2_SCHED_MAX_BURST_MARGIN = 75 * multiplier;
int C2_SCHED_FQ_MAX_BURST = 3000 * multiplier;
int C2_SCHED_FQ_MAX_BURST_MARGIN = 75 * multiplier;
int C2_CONN_MAX_BURST = 3000 * multiplier;
int C2_CONN_MAX_BURST_MARGIN = 75 * multiplier;


int C2_NBR_QUEUE_GROUPS = 2;
int C2_NBR_FQ_SCHEDULERS = 4;

int c2_use_same_handles = 0;

/* for port type variable */
int C2_FRONT_PANEL_PORT_TYPE = 0;

/* resource type variable */
int C2_RESOURCE_TYPE_LEGACY = 0;
int C2_RESOURCE_TYPE_FIXED = 1;


int c2_base_sched = 32768;
int c2_base_fq_sched = 32773;
int c2_base_voq_connector = 32;
int c2_base_voq = 4;


bcm_gport_t tm_config2_get_flow_handle(int port_id)
{
    int idx = port_id;
    return c2_gport_ucast_queue_group1[idx];
}
bcm_gport_t tm_config2_get_ucast_handle(int port_id)
{
    int idx = port_id;
    return c2_gport_ucast_queue_group0[idx];
}
bcm_gport_t tm_config2_get_sysport_handle(int port_id)
{
    int idx = port_id;
    return c2_sys_gport[idx];
}
void tm_config2_display_handles(int port_id)
{
    int idx = port_id;

    printf("  e2eGport(0x%x) schedGport(0x%x)\n",
            c2_e2e_gport[idx], c2_gport_ucast_scheduler[idx]);
    printf("    l3_fq0(0x%x) l3_fq1(0x%x) l3_fq2(0x%x) l3_fq3(0x%x)\n",
            c2_gport_ucast_scheduler_fq0[idx], c2_gport_ucast_scheduler_fq1[idx],
            c2_gport_ucast_scheduler_fq2[idx], c2_gport_ucast_scheduler_fq3[idx]);
    printf("    connGrp0Gport(0x%x) connGrp1Gport(0x%x)\n",
            c2_gport_ucast_voq_connector_group0[idx], c2_gport_ucast_voq_connector_group1[idx]);
    printf("    ucastGrp0Gport(0x%x) ucastGrp1Gport(0x%x)\n",
            c2_gport_ucast_queue_group0[idx], c2_gport_ucast_queue_group1[idx]);
}

int tm_config2_form_handles(int port_id, int port_type)
{
    int idx = port_id;
    int port, system_port;
    bcm_gport_t dest_gport[32];
    char error_msg[200]={0,};

    if (port_type == C2_FRONT_PANEL_PORT_TYPE) {
        port = idx + 1;
        system_port = idx + 1;

        BCM_GPORT_SYSTEM_PORT_ID_SET(c2_sys_gport[idx], system_port);

        snprintf(error_msg, sizeof(error_msg), "unit=%d, sysport=0x%x, destport=0x%x", c2_ingr_unit, c2_sys_gport[idx], dest_gport[idx]);
        BCM_IF_ERROR_RETURN_MSG(bcm_stk_sysport_gport_get(c2_ingr_unit, c2_sys_gport[idx], dest_gport[idx]), error_msg);

        port = BCM_GPORT_MODPORT_PORT_GET(dest_gport[idx]);
        BCM_COSQ_GPORT_E2E_PORT_SET(c2_e2e_gport[idx], port);

        BCM_IF_ERROR_RETURN_MSG(bcm_fabric_port_get(c2_egr_unit,
                c2_e2e_gport[idx],
                0,
                &c2_e2e_parent_gport[idx]), "");

        printf("c2_e2e_parent_gport: 0x%x\n", c2_e2e_parent_gport[idx]);
    }
    else {
        return(BCM_E_PARAM);
    }

    BCM_GPORT_SCHEDULER_CORE_SET( c2_gport_ucast_scheduler[idx], (c2_base_sched + (port_id * 4)), 0 );

    BCM_GPORT_SCHEDULER_CORE_SET( c2_gport_ucast_scheduler_fq0[idx], (c2_base_fq_sched + (port_id * 16)), 0 );
    BCM_GPORT_SCHEDULER_CORE_SET( c2_gport_ucast_scheduler_fq1[idx], (c2_base_fq_sched + (port_id * 16) + 4), 0 );
    BCM_GPORT_SCHEDULER_CORE_SET( c2_gport_ucast_scheduler_fq2[idx], (c2_base_fq_sched + (port_id * 16) + 8), 0 );
    BCM_GPORT_SCHEDULER_CORE_SET( c2_gport_ucast_scheduler_fq3[idx], (c2_base_fq_sched + (port_id * 16) + 12), 0 );

    BCM_COSQ_GPORT_VOQ_CONNECTOR_CORE_SET( c2_gport_ucast_voq_connector_group0[idx], (c2_base_voq_connector + (port_id * 8)), 0 );
    BCM_COSQ_GPORT_VOQ_CONNECTOR_CORE_SET( c2_gport_ucast_voq_connector_group1[idx], (c2_base_voq_connector + (port_id * 8) + 4), 0 );

    BCM_GPORT_UNICAST_QUEUE_GROUP_CORE_SET( c2_gport_ucast_queue_group0[idx], (c2_base_voq + (port_id * 8)), 0 );
    BCM_GPORT_UNICAST_QUEUE_GROUP_CORE_SET( c2_gport_ucast_queue_group1[idx], (c2_base_voq + (port_id * 8) + 4), 0 );

    return BCM_E_NONE;
}

/*
 * Set queue ranges - must be done before any queues are allocated
 */
int tm_config2_set_queue_range(int unit, int bottom_queue, int top_queue, int port_type)
{
    bcm_fabric_control_t control_type;

    control_type = bcmFabricQueueMin;
    BCM_IF_ERROR_RETURN_MSG(bcm_fabric_control_set(unit, control_type, bottom_queue), "");
    control_type = bcmFabricQueueMax;
    BCM_IF_ERROR_RETURN_MSG(bcm_fabric_control_set(unit, control_type, top_queue), "");

    return BCM_E_NONE;
}
int tm_config2_configure_isq_root(int unit, int kbits_sec_max)
{
    bcm_gport_t isq_root;

    BCM_COSQ_GPORT_ISQ_ROOT_CORE_SET(isq_root, 0);

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_bandwidth_set(unit,
            isq_root,
            0,
            0,
            kbits_sec_max,
            0), "failed for ISQ root");

    return BCM_E_NONE;
}

int tm_config2_setup(int port_id, int port_type, int res_type)
{
    int idx, port, system_port;
    bcm_gport_t dest_gport[32];
    int num_cos = 4;
    int flags = 0, default_flags = 0, default_voq_flags = 0, default_connector_flags = 0;
    int voq;
    bcm_cosq_gport_connection_t connection;
    int kbits_sec_max;
    int max_burst;
    int cosq = 0;
    bcm_cosq_voq_connector_gport_t config;
    uint32 dummy_flags ;
    bcm_port_interface_info_t interface_info;
    bcm_port_mapping_info_t mapping_info;
    int core = 0;
    int voq_id;
    bcm_cosq_ingress_queue_bundle_gport_config_t conf;
    bcm_port_resource_t resource;
    int delay_tolerance_level, rate_class;
    bcm_cosq_scheduler_gport_params_t params;
    char error_msg[200]={0,};

    printf("\nSetup\n");

    idx = port_id;

    if ( (res_type != C2_RESOURCE_TYPE_LEGACY) && (res_type != C2_RESOURCE_TYPE_FIXED) ) {
        printf("invaid res_type(%d)\n", res_type);
        return(BCM_E_PARAM);
    }

    if ( (res_type == C2_RESOURCE_TYPE_FIXED) && (port_type != C2_FRONT_PANEL_PORT_TYPE) ) {
        printf("For fixed resource type Port type has to be Front Panel, invalid port type (%d)\n", port_type);
        return(BCM_E_PARAM);
    }

    if (c2_use_same_handles == 1) {
        default_flags = BCM_COSQ_SCHEDULER_GPORT_WITH_ID;
        default_voq_flags = BCM_COSQ_GPORT_WITH_ID;
        default_connector_flags = BCM_COSQ_VOQ_CONNECTOR_GPORT_F_WITH_ID;
        tm_config2_display_handles(idx);
    }

    if (port_type == C2_FRONT_PANEL_PORT_TYPE) {
        port = idx + 1;
        system_port = idx + 1;

        BCM_IF_ERROR_RETURN_MSG(bcm_port_get(c2_egr_unit, port, &dummy_flags, &interface_info, &mapping_info), "");
        printf("\n core(%d)\n",  mapping_info.core);
        core =  mapping_info.core;

        BCM_GPORT_SYSTEM_PORT_ID_SET(c2_sys_gport[idx], system_port);
        BCM_GPORT_MODPORT_SET(dest_gport[idx], c2_egr_modid + core, port);

        snprintf(error_msg, sizeof(error_msg), "unit=%d, sysport=0x%x, destport=0x%x", c2_ingr_unit, c2_sys_gport[idx], dest_gport[idx]);
        BCM_IF_ERROR_RETURN_MSG(bcm_stk_sysport_gport_get(c2_ingr_unit, c2_sys_gport[idx], dest_gport[idx]), error_msg);
    } else {
        printf("Invalid port type(%d) \n", port_type);
        return BCM_E_PARAM;
    }


    port = BCM_GPORT_MODPORT_PORT_GET(dest_gport[idx]);
    printf("idx(%d) dest_gport(%d) port(%d) modid(%d)\n",  idx, dest_gport[idx], port, c2_egr_modid + core);

    if (res_type == C2_RESOURCE_TYPE_FIXED) {
        BCM_IF_ERROR_RETURN_MSG(tm_config2_form_handles(idx, port_type), "");
    }

    /* create scheduler */

    params.type = bcmCosqSchedulerGportTypeClass4Sp;
    params.mode = bcmCosqSchedulerGportModeSimple;
    params.cl_wfq_mode = bcmCosqSchedulerGportClWfqModeNone;
    params.core = mapping_info.core;
    params.shared_order = bcmCosqSchedulerGportSharedOrderNone;
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_scheduler_gport_add(c2_egr_unit, default_flags, params, &c2_gport_ucast_scheduler[idx]), "");

    /* COS 0 */
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_sched_set(c2_egr_unit,
            c2_gport_ucast_scheduler[idx],
            0,
            C2_SCHED_MODE,
            0), "");

    BCM_COSQ_GPORT_E2E_PORT_SET(c2_e2e_gport[idx], port);

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_attach(c2_egr_unit, c2_e2e_gport[idx],
            c2_gport_ucast_scheduler[idx], 0), "");

    /* create scheduler */

    params.type = bcmCosqSchedulerGportTypeFq;
    params.mode = bcmCosqSchedulerGportModeSimple;
    params.cl_wfq_mode = bcmCosqSchedulerGportClWfqModeNone;
    params.core = mapping_info.core;
    params.shared_order = bcmCosqSchedulerGportSharedOrderNone;
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_scheduler_gport_add(c2_egr_unit, default_flags, params, &c2_gport_ucast_scheduler_fq0[idx]), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_sched_set(c2_egr_unit,
            c2_gport_ucast_scheduler_fq0[idx],
            0,
            BCM_COSQ_SP0,
            0), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_attach(c2_egr_unit, c2_gport_ucast_scheduler[idx],
            c2_gport_ucast_scheduler_fq0[idx], 0), "");


    /* create scheduler */

    params.type = bcmCosqSchedulerGportTypeFq;
    params.mode = bcmCosqSchedulerGportModeSimple;
    params.cl_wfq_mode = bcmCosqSchedulerGportClWfqModeNone;
    params.core = mapping_info.core;
    params.shared_order = bcmCosqSchedulerGportSharedOrderNone;
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_scheduler_gport_add(c2_egr_unit, default_flags, params, &c2_gport_ucast_scheduler_fq1[idx]), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_sched_set(c2_egr_unit,
            c2_gport_ucast_scheduler_fq1[idx],
            0,
            BCM_COSQ_SP1,
            0), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_attach(c2_egr_unit, c2_gport_ucast_scheduler[idx],
            c2_gport_ucast_scheduler_fq1[idx], 0), "");


    /* create scheduler */

    params.type = bcmCosqSchedulerGportTypeFq;
    params.mode = bcmCosqSchedulerGportModeSimple;
    params.cl_wfq_mode = bcmCosqSchedulerGportClWfqModeNone;
    params.core = mapping_info.core;
    params.shared_order = bcmCosqSchedulerGportSharedOrderNone;
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_scheduler_gport_add(c2_egr_unit, default_flags, params, &c2_gport_ucast_scheduler_fq2[idx]), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_sched_set(c2_egr_unit,
            c2_gport_ucast_scheduler_fq2[idx],
            0,
            BCM_COSQ_SP2,
            0), "");


    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_attach(c2_egr_unit, c2_gport_ucast_scheduler[idx],
            c2_gport_ucast_scheduler_fq2[idx], 0), "");

    /* create scheduler */

    params.type = bcmCosqSchedulerGportTypeFq;
    params.mode = bcmCosqSchedulerGportModeSimple;
    params.cl_wfq_mode = bcmCosqSchedulerGportClWfqModeNone;
    params.core = mapping_info.core;
    params.shared_order = bcmCosqSchedulerGportSharedOrderNone;
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_scheduler_gport_add(c2_egr_unit, default_flags, params, &c2_gport_ucast_scheduler_fq3[idx]), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_sched_set(c2_egr_unit,
            c2_gport_ucast_scheduler_fq3[idx],
            0,
            BCM_COSQ_SP3,
            0), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_attach(c2_egr_unit, c2_gport_ucast_scheduler[idx],
            c2_gport_ucast_scheduler_fq3[idx], 0), "");

    /* create voq connector */
    BCM_GPORT_MODPORT_SET(config.port, c2_egr_modid + core, port);

    config.flags = C2_CONN_FLAGS | default_connector_flags;
    config.numq = num_cos;
    config.remote_modid = c2_ingr_modid + core;
    config.nof_remote_cores = 1;
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_voq_connector_gport_add(c2_egr_unit, &config, &c2_gport_ucast_voq_connector_group0[idx]), "");

    /* COS 0 */
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_sched_set(c2_egr_unit,
            c2_gport_ucast_voq_connector_group0[idx],
            0,
            BCM_COSQ_SP0,
            0), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_attach(c2_egr_unit, c2_gport_ucast_scheduler_fq0[idx],
            c2_gport_ucast_voq_connector_group0[idx], 0), "");


    /* COS 1 */
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_sched_set(c2_egr_unit,
            c2_gport_ucast_voq_connector_group0[idx],
            1,
            BCM_COSQ_SP0,
            0), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_attach(c2_egr_unit, c2_gport_ucast_scheduler_fq1[idx],
            c2_gport_ucast_voq_connector_group0[idx], 1), "");

    /* COS 2 */
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_sched_set(c2_egr_unit,
            c2_gport_ucast_voq_connector_group0[idx],
            2,
            BCM_COSQ_SP0,
            0), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_attach(c2_egr_unit, c2_gport_ucast_scheduler_fq2[idx],
            c2_gport_ucast_voq_connector_group0[idx], 2), "");

    /* COS 3 */
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_sched_set(c2_egr_unit,
            c2_gport_ucast_voq_connector_group0[idx],
            3,
            BCM_COSQ_SP0,
            0), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_attach(c2_egr_unit, c2_gport_ucast_scheduler_fq3[idx],
            c2_gport_ucast_voq_connector_group0[idx], 3), "");

    /* Create VOQ */
    flags = C2_QUEUE_FLAGS | default_voq_flags;

    BCM_IF_ERROR_RETURN_MSG(bcm_port_resource_get(c2_ingr_unit, port, &resource), "");
    BCM_IF_ERROR_RETURN_MSG(appl_dnx_e2e_voq_profiles_get(c2_ingr_unit, resource.speed, &delay_tolerance_level, &rate_class), "");
    conf.flags = flags;
    conf.port = c2_sys_gport[idx];
    conf.numq = num_cos;
    conf.local_core_id = BCM_CORE_ALL;
    for (cosq = 0; cosq < num_cos; cosq++) {
        conf.queue_atrributes[cosq].delay_tolerance_level = delay_tolerance_level;
        conf.queue_atrributes[cosq].rate_class = rate_class;
    }
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_ingress_queue_bundle_gport_add(c2_ingr_unit, &conf, &c2_gport_ucast_queue_group0[idx]), "");
    /*bcm_cosq_ingress_queue_bundle_gport_add will a voq gport with core - BCM_CORE_ALL.
          In order to be consistent with the asymmetric scheme to be created
          the core is overwrited.*/
    voq_id = BCM_GPORT_UNICAST_QUEUE_GROUP_QID_GET(c2_gport_ucast_queue_group0[idx]);
    BCM_GPORT_UNICAST_QUEUE_GROUP_CORE_QUEUE_SET(c2_gport_ucast_queue_group0[idx], core, voq_id);


    printf("ucast gport(0x%08x)\n", c2_gport_ucast_queue_group0[idx]);
    /* connect voq to flow */
    connection.flags = BCM_COSQ_GPORT_CONNECTION_INGRESS;
    connection.remote_modid = c2_egr_modid + core;
    connection.voq = c2_gport_ucast_queue_group0[idx];
    connection.voq_connector = c2_gport_ucast_voq_connector_group0[idx];

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_connection_set(c2_ingr_unit, &connection), "");


    /* connect flow to voq */
    connection.flags = BCM_COSQ_GPORT_CONNECTION_EGRESS;
    connection.remote_modid = c2_ingr_modid + core;
    connection.voq = c2_gport_ucast_queue_group0[idx];
    connection.voq_connector = c2_gport_ucast_voq_connector_group0[idx];

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_connection_set(c2_egr_unit, &connection), "");


    /* configuration for another queue group */
    /* create voq connector */
    BCM_GPORT_MODPORT_SET(config.port, c2_egr_modid + core, port);

    config.flags = C2_CONN_FLAGS | default_connector_flags;
    config.numq = num_cos;
    config.remote_modid = c2_ingr_modid + core;
    config.nof_remote_cores = 1;

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_voq_connector_gport_add(c2_egr_unit, &config, &c2_gport_ucast_voq_connector_group1[idx]), "");

    /* COS 0 */
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_sched_set(c2_egr_unit,
            c2_gport_ucast_voq_connector_group1[idx],
            0,
            BCM_COSQ_SP0,
            0), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_attach(c2_egr_unit, c2_gport_ucast_scheduler_fq0[idx],
            c2_gport_ucast_voq_connector_group1[idx], 0), "");

    /* COS 1 */
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_sched_set(c2_egr_unit,
            c2_gport_ucast_voq_connector_group1[idx],
            1,
            BCM_COSQ_SP0,
            0), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_attach(c2_egr_unit, c2_gport_ucast_scheduler_fq1[idx],
            c2_gport_ucast_voq_connector_group1[idx], 1), "");

    /* COS 2 */
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_sched_set(c2_egr_unit,
            c2_gport_ucast_voq_connector_group1[idx],
            2,
            BCM_COSQ_SP0,
            0), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_attach(c2_egr_unit, c2_gport_ucast_scheduler_fq2[idx],
            c2_gport_ucast_voq_connector_group1[idx], 2), "");

    /* COS 3 */
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_sched_set(c2_egr_unit,
            c2_gport_ucast_voq_connector_group1[idx],
            3,
            BCM_COSQ_SP0,
            0), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_attach(c2_egr_unit, c2_gport_ucast_scheduler_fq3[idx],
            c2_gport_ucast_voq_connector_group1[idx], 3), "");

    flags = C2_QUEUE_FLAGS |  BCM_COSQ_GPORT_TM_FLOW_ID | default_voq_flags;

    BCM_IF_ERROR_RETURN_MSG(bcm_port_resource_get(c2_egr_unit, port, &resource), "");
    BCM_IF_ERROR_RETURN_MSG(appl_dnx_e2e_voq_profiles_get(c2_egr_unit, resource.speed, &delay_tolerance_level, &rate_class), "");
    conf.flags = flags;
    conf.port = c2_sys_gport[idx];
    conf.numq = num_cos;
    conf.local_core_id = BCM_CORE_ALL;
    for (cosq = 0; cosq < num_cos; cosq++) {
        conf.queue_atrributes[cosq].delay_tolerance_level = delay_tolerance_level;
        conf.queue_atrributes[cosq].rate_class = rate_class;
    }
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_ingress_queue_bundle_gport_add(c2_egr_unit, &conf, &c2_gport_ucast_queue_group1[idx]), "");
    printf("ucast gport(0x%08x)\n", c2_gport_ucast_queue_group1[idx]);

    /*bcm_cosq_ingress_queue_bundle_gport_add will a voq gport with core - BCM_CORE_ALL.
          In order to be consistent with the asymmetric scheme to be created
          the core is overwrited.*/
    voq_id = BCM_GPORT_UNICAST_QUEUE_GROUP_QID_GET(c2_gport_ucast_queue_group1[idx]);
    BCM_GPORT_UNICAST_QUEUE_GROUP_CORE_QUEUE_SET(c2_gport_ucast_queue_group1[idx], core, voq_id);

    /* connect voq to flow */
    connection.flags = BCM_COSQ_GPORT_CONNECTION_INGRESS;
    connection.remote_modid = c2_egr_modid + core;
    connection.voq = c2_gport_ucast_queue_group1[idx];
    connection.voq_connector = c2_gport_ucast_voq_connector_group1[idx];

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_connection_set(c2_ingr_unit, &connection), "");

    /* connect voq to flow */
    connection.flags = BCM_COSQ_GPORT_CONNECTION_EGRESS;
    connection.remote_modid = c2_ingr_modid + core;
    connection.voq = c2_gport_ucast_queue_group1[idx];
    connection.voq_connector = c2_gport_ucast_voq_connector_group1[idx];

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_connection_set(c2_egr_unit, &connection), "");
    /*
     * Set rate on the E2E Interface
     */

    BCM_COSQ_GPORT_E2E_PORT_SET(c2_e2e_gport[idx], port);
    kbits_sec_max = C2_E2E_INTERFACE_KBITS_SEC_MAX; /* 1Gbps */

    BCM_IF_ERROR_RETURN_MSG(bcm_fabric_port_get(c2_egr_unit,
            c2_e2e_gport[idx],
            0,
            &c2_e2e_parent_gport[idx]), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_bandwidth_set(c2_egr_unit,
            c2_e2e_parent_gport[idx],
            0,
            0,
            kbits_sec_max,
            0), "");

    /*
     * Set rate on the E2E port
     */
    kbits_sec_max = C2_E2E_PORT_KBITS_SEC_MAX; /* 500Mbps */
    BCM_COSQ_GPORT_E2E_PORT_SET(c2_e2e_gport[idx], port);
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_bandwidth_set(c2_egr_unit,
            c2_e2e_gport[idx],
            0,
            0,
            kbits_sec_max,
            0), "");

    /*
     * Set rate on the Scheduler (CL)
     */
    kbits_sec_max = C2_SCHED_KBITS_SEC_MAX;
    max_burst = C2_SCHED_MAX_BURST;
    /* Scheduler */
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_bandwidth_set(c2_egr_unit,
            c2_gport_ucast_scheduler[idx],
            0,
            0,
            kbits_sec_max,
            0), "");

    /* Set max burst on the Scheduler */
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_control_set(c2_egr_unit,
            c2_gport_ucast_scheduler[idx],
            0,
            bcmCosqControlBandwidthBurstMax,
            max_burst), "");

    /*
     * FQ scheduler (instance 0)
     */
    kbits_sec_max = C2_SCHED_FQ_KBITS_SEC_MAX;
    max_burst = C2_SCHED_FQ_MAX_BURST;
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_bandwidth_set(c2_egr_unit,
            c2_gport_ucast_scheduler_fq0[idx],
            0,
            0,
            kbits_sec_max,
            0), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_control_set(c2_egr_unit,
            c2_gport_ucast_scheduler_fq0[idx],
            0,
            bcmCosqControlBandwidthBurstMax,
            max_burst), "");

    /*
     * FQ scheduler (instance 1)
     */
    kbits_sec_max = C2_SCHED_FQ_KBITS_SEC_MAX;
    max_burst = C2_SCHED_FQ_MAX_BURST;
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_bandwidth_set(c2_egr_unit,
            c2_gport_ucast_scheduler_fq1[idx],
            0,
            0,
            kbits_sec_max,
            0), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_control_set(c2_egr_unit,
            c2_gport_ucast_scheduler_fq1[idx],
            0,
            bcmCosqControlBandwidthBurstMax,
            max_burst), "");

    /*
     * FQ scheduler (instance 2)
     */
    kbits_sec_max = C2_SCHED_FQ_KBITS_SEC_MAX;
    max_burst = C2_SCHED_FQ_MAX_BURST;
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_bandwidth_set(c2_egr_unit,
            c2_gport_ucast_scheduler_fq2[idx],
            0,
            0,
            kbits_sec_max,
            0), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_control_set(c2_egr_unit,
            c2_gport_ucast_scheduler_fq2[idx],
            0,
            bcmCosqControlBandwidthBurstMax,
            max_burst), "");

    /*
     * FQ scheduler (instance 3)
     */
    kbits_sec_max = C2_SCHED_FQ_KBITS_SEC_MAX;
    max_burst = C2_SCHED_FQ_MAX_BURST;
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_bandwidth_set(c2_egr_unit,
            c2_gport_ucast_scheduler_fq3[idx],
            0,
            0,
            kbits_sec_max,
            0), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_control_set(c2_egr_unit,
            c2_gport_ucast_scheduler_fq3[idx],
            0,
            bcmCosqControlBandwidthBurstMax,
            max_burst), "");


    /*
     * Connector Group 0
     */
    kbits_sec_max = C2_CONN_KBITS_SEC_MAX;
    max_burst = C2_CONN_MAX_BURST;

    for (cosq = 0; cosq < 4; cosq++) {
        /* Set rate on the Connector flow */
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_bandwidth_set(c2_egr_unit,
                c2_gport_ucast_voq_connector_group0[idx],
                cosq,
                0,
                kbits_sec_max,
                0), "");

        /* Set maxburst on the Connector flow */
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_control_set(c2_egr_unit,
                c2_gport_ucast_voq_connector_group0[idx],
                cosq,
                bcmCosqControlBandwidthBurstMax,
                max_burst), "");

    }

    /*
     * Connector Group 1
     */
    kbits_sec_max = C2_CONN_KBITS_SEC_MAX;
    max_burst = C2_CONN_MAX_BURST;
    for (cosq=0; cosq<4; cosq++) {
        /* Set rate on the Connector flow */
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_bandwidth_set(c2_egr_unit,
                c2_gport_ucast_voq_connector_group1[idx],
                cosq,
                0,
                kbits_sec_max,
                0), "");

        /* Set maxburst on the Connector flow */
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_control_set(c2_egr_unit,
                c2_gport_ucast_voq_connector_group1[idx],
                cosq,
                bcmCosqControlBandwidthBurstMax,
                max_burst), "");

    }

    tm_config2_display_handles(idx);

    printf("port(%d) sysport(%d) ucast gport(0x%08x)\n", port, system_port, c2_gport_ucast_queue_group0[idx]);
    printf("cint_dnx_tm_fap_config2.c completed with status (%s)\n", bcm_errmsg(BCM_E_NONE));
    return BCM_E_NONE;
}


int tm_config2_teardown(int port_id, int port_type)
{
    int                           idx = 0;
    bcm_gport_t                   gport_ucast_voq_connector_group;
    bcm_gport_t                   gport_ucast_queue_group;
    bcm_gport_t                   gport_scheduler_fq;
    int                           nbr_queue_groups, nbr_fq_sched;
    bcm_cosq_gport_connection_t   connection;
    int                           cosq = 0;
    char                          error_msg[200]={0,};

    printf("\nTeardown\n");

    idx = port_id;

    tm_config2_display_handles(idx);

    /* detach scheduler sub-tree from E2E hierarchy */
    snprintf(error_msg, sizeof(error_msg), "detach for SE(0x%x) failed", c2_gport_ucast_scheduler[idx]);
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_detach(c2_egr_unit, c2_e2e_gport[idx], c2_gport_ucast_scheduler[idx], 0), error_msg);
    printf("  detached schedGport(0x%x)\n", c2_gport_ucast_scheduler[idx]);

    /* dis-associate queue from connectors */
    for (nbr_queue_groups = 0; nbr_queue_groups < C2_NBR_QUEUE_GROUPS; nbr_queue_groups++) {
        switch (nbr_queue_groups) {
        case 0: gport_ucast_queue_group = c2_gport_ucast_queue_group0[idx];
        gport_ucast_voq_connector_group = c2_gport_ucast_voq_connector_group0[idx]; break;
        default: gport_ucast_queue_group = c2_gport_ucast_queue_group1[idx];
        gport_ucast_voq_connector_group = c2_gport_ucast_voq_connector_group1[idx]; break;
        }

        connection.flags = BCM_COSQ_GPORT_CONNECTION_INGRESS | BCM_COSQ_GPORT_CONNECTION_INVALID;
        connection.remote_modid = c2_egr_modid;
        connection.voq = gport_ucast_queue_group;
        connection.voq_connector = gport_ucast_voq_connector_group;

        snprintf(error_msg, sizeof(error_msg), "resetting queue2connector association failed, queue(0x%x)", gport_ucast_queue_group);
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_connection_set(c2_ingr_unit, &connection), error_msg);
        printf("  disconnected (Ingress) ucastGport(0x%x) from connGport(0x%x)\n", gport_ucast_queue_group, gport_ucast_voq_connector_group);
    }

    /* dis-associate connectors from queues */
    for (nbr_queue_groups = 0; nbr_queue_groups < C2_NBR_QUEUE_GROUPS; nbr_queue_groups++) {
        switch (nbr_queue_groups) {
        case 0: gport_ucast_queue_group = c2_gport_ucast_queue_group0[idx];
        gport_ucast_voq_connector_group = c2_gport_ucast_voq_connector_group0[idx]; break;
        default: gport_ucast_queue_group = c2_gport_ucast_queue_group1[idx];
        gport_ucast_voq_connector_group = c2_gport_ucast_voq_connector_group1[idx]; break;
        }

        connection.flags = BCM_COSQ_GPORT_CONNECTION_EGRESS | BCM_COSQ_GPORT_CONNECTION_INVALID;
        connection.remote_modid = c2_ingr_modid;
        connection.voq = gport_ucast_queue_group;
        connection.voq_connector = gport_ucast_voq_connector_group;

        snprintf(error_msg, sizeof(error_msg), "resetting connector2queue association failed, Connector(0x%x)", gport_ucast_voq_connector_group);
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_connection_set(c2_egr_unit, &connection), error_msg);
        printf("  disconnected (Engress) connGport(0x%x) from ucastGport(0x%x)\n", gport_ucast_voq_connector_group, gport_ucast_queue_group);
    }

    /* delete queues */
    for (nbr_queue_groups = 0; nbr_queue_groups < C2_NBR_QUEUE_GROUPS; nbr_queue_groups++) {
        switch (nbr_queue_groups) {
        case 0: gport_ucast_queue_group = c2_gport_ucast_queue_group0[idx]; break;
        default: gport_ucast_queue_group = c2_gport_ucast_queue_group1[idx]; break;
        }

        snprintf(error_msg, sizeof(error_msg), "delete for QueueGroup(0x%x) failed", gport_ucast_queue_group);
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_delete(c2_ingr_unit, gport_ucast_queue_group), error_msg);
        printf("  deleted ucastGport(0x%x)\n", gport_ucast_queue_group);
    }

    /* detach connectors */
    for (nbr_queue_groups = 0; nbr_queue_groups < C2_NBR_QUEUE_GROUPS; nbr_queue_groups++) {
        switch (nbr_queue_groups) {
        case 0: gport_ucast_voq_connector_group = c2_gport_ucast_voq_connector_group0[idx]; break;
        default: gport_ucast_voq_connector_group = c2_gport_ucast_voq_connector_group1[idx]; break;
        }

        for (cosq = 0; cosq < 4; cosq++) {
            switch (cosq) {
            case 0: gport_scheduler_fq = c2_gport_ucast_scheduler_fq0[idx]; break;
            case 1: gport_scheduler_fq = c2_gport_ucast_scheduler_fq1[idx]; break;
            case 2: gport_scheduler_fq = c2_gport_ucast_scheduler_fq2[idx]; break;
            default: gport_scheduler_fq = c2_gport_ucast_scheduler_fq3[idx]; break;
            }

            snprintf(error_msg, sizeof(error_msg), "detach for Connector:cosq(0x%x:%d) from Sched(0x%x) failed", gport_ucast_voq_connector_group, cosq, gport_scheduler_fq);
            BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_detach(c2_egr_unit, gport_scheduler_fq, gport_ucast_voq_connector_group, cosq), error_msg);
            printf("  detached connGport(0x%x) from schedGport(0x%x)\n", gport_ucast_voq_connector_group, gport_scheduler_fq);
        }
    }

    /* delete connectors */
    for (nbr_queue_groups = 0; nbr_queue_groups < C2_NBR_QUEUE_GROUPS; nbr_queue_groups++) {
        switch (nbr_queue_groups) {
        case 0: gport_ucast_voq_connector_group = c2_gport_ucast_voq_connector_group0[idx]; break;
        default: gport_ucast_voq_connector_group = c2_gport_ucast_voq_connector_group1[idx]; break;
        }

        /* delete connectors */
        snprintf(error_msg, sizeof(error_msg), "delete for ConnectorGroup(0x%x) failed", gport_ucast_voq_connector_group);
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_delete(c2_egr_unit, gport_ucast_voq_connector_group), error_msg);
        printf("  delete connGport(0x%x)\n", gport_ucast_voq_connector_group);
    }

    /* detach intermediate Scheduler elements (SE) */
    for (nbr_fq_sched = 0; nbr_fq_sched < C2_NBR_FQ_SCHEDULERS; nbr_fq_sched++) {
        switch (nbr_fq_sched) {
        case 0: gport_scheduler_fq = c2_gport_ucast_scheduler_fq0[idx]; break;
        case 1: gport_scheduler_fq = c2_gport_ucast_scheduler_fq1[idx]; break;
        case 2: gport_scheduler_fq = c2_gport_ucast_scheduler_fq2[idx]; break;
        default: gport_scheduler_fq = c2_gport_ucast_scheduler_fq3[idx]; break;
        }

        snprintf(error_msg, sizeof(error_msg), "detach for SE(0x%x) failed", gport_scheduler_fq);
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_detach(c2_egr_unit, c2_gport_ucast_scheduler[idx], gport_scheduler_fq, 0), error_msg);
        printf("  detached schedGport(0x%x)\n", gport_scheduler_fq);
    }

    /* delete intermediate Scheduler elements (SE) */
    for (nbr_fq_sched = 0; nbr_fq_sched < C2_NBR_FQ_SCHEDULERS; nbr_fq_sched++) {
        switch (nbr_fq_sched) {
        case 0: gport_scheduler_fq = c2_gport_ucast_scheduler_fq0[idx]; break;
        case 1: gport_scheduler_fq = c2_gport_ucast_scheduler_fq1[idx]; break;
        case 2: gport_scheduler_fq = c2_gport_ucast_scheduler_fq2[idx]; break;
        default: gport_scheduler_fq = c2_gport_ucast_scheduler_fq3[idx]; break;
        }

        snprintf(error_msg, sizeof(error_msg), "delete for SE(0x%x) failed", gport_scheduler_fq);
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_delete(c2_egr_unit, gport_scheduler_fq), error_msg);
        printf("  delete schedGport(0x%x)\n", gport_scheduler_fq);
    }

    /* delete scheduler  element at top of sub-tree */
    snprintf(error_msg, sizeof(error_msg), "delete for SE(0x%x) failed", c2_gport_ucast_scheduler[idx]);
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_delete(c2_egr_unit, c2_gport_ucast_scheduler[idx]), error_msg);
    printf("  delete schedGport(0x%x)\n", c2_gport_ucast_scheduler[idx]);

    printf("cint_dnx_tm_fap_config2.c (teardown) completed with status (%s)\n", bcm_errmsg(BCM_E_NONE));

    c2_use_same_handles = 1;

    return BCM_E_NONE;
}

int
tm_config2_verify(int port_id, int port_type, int res_type)
{
    int                           idx = 0;
    bcm_gport_t                   physical_port;
    int                           num_cos_levels;
    uint32                        flags;
    int                           mode, weight, exp_mode;
    int                           cosq, kbits_sec_max, max_burst, slow_rate;
    bcm_gport_t                   gport_scheduler_fq;
    bcm_gport_t                   gport_ucast_voq_connector_group;
    bcm_gport_t                   gport_ucast_queue_group;
    int                           nbr_queue_groups, nbr_fq_sched;
    bcm_cosq_gport_connection_t   connection;
    bcm_cosq_scheduler_gport_params_t params_get;
    bcm_cosq_voq_connector_gport_t config_get;
    char error_msg[200]={0,};

    printf("\nVerify Setup\n");

    idx = port_id;

    if ( (res_type != C2_RESOURCE_TYPE_LEGACY) && (res_type != C2_RESOURCE_TYPE_FIXED) ) {
        printf("invaid res_type(%d)\n", res_type);
        return(BCM_E_PARAM);
    }

    if ( (res_type == C2_RESOURCE_TYPE_FIXED) && (port_type != C2_FRONT_PANEL_PORT_TYPE) ) {
        printf("For fixed resource type Port type has to be Front Panel, invalid port type (%d)\n", port_type);
        return(BCM_E_PARAM);
    }

    if (res_type == C2_RESOURCE_TYPE_FIXED) {
        BCM_IF_ERROR_RETURN_MSG(tm_config2_form_handles(idx, port_type), "");
        tm_config2_display_handles(idx);
    }

    /* Get rate of the E2E Interface */
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_bandwidth_get(c2_egr_unit,c2_e2e_parent_gport[idx], 0,0,&kbits_sec_max,0), "");
    /* actual hardware value set returned */
    if ((kbits_sec_max > C2_E2E_INTERFACE_KBITS_SEC_MAX + C2_E2E_INTERFACE_KBITS_SEC_MAX_MARGIN) ||
            (kbits_sec_max < C2_E2E_INTERFACE_KBITS_SEC_MAX - C2_E2E_INTERFACE_KBITS_SEC_MAX_MARGIN)) {
        printf("E2E interface(0x%08x) bandwidth_get rate(%d) expected rate(1000000)\n", c2_e2e_parent_gport[idx], kbits_sec_max);
    }

    /* Get rate on the E2E port */
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_bandwidth_get(c2_egr_unit,c2_e2e_gport[idx],0, 0,kbits_sec_max, 0), "");
    if ((kbits_sec_max > C2_E2E_PORT_KBITS_SEC_MAX + C2_E2E_PORT_KBITS_SEC_MAX_MARGIN) ||
            (kbits_sec_max < C2_E2E_PORT_KBITS_SEC_MAX - C2_E2E_PORT_KBITS_SEC_MAX_MARGIN)) {
        printf("E2E interface(0x%08x) bandwidth_get rate(%d) expected rate(1000000)\n", c2_e2e_parent_gport[idx], kbits_sec_max);
    }

    if (kbits_sec_max != C2_E2E_PORT_KBITS_SEC_MAX) {
        printf("E2E interface(0x%08x) bandwidth_get rate(%d) expected rate(500000)\n", c2_e2e_gport[idx], kbits_sec_max);
    }

    /* retrieve e2e port scheduling element */
    snprintf(error_msg, sizeof(error_msg), "failed on e2e Sched (0x%x)", c2_e2e_gport[idx]);
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_scheduler_gport_get(c2_egr_unit, 0, c2_e2e_gport[idx], &params_get), error_msg);
    if (params_get.type != C2_DEFAULT_E2E_SCHED_TYPE) {
        printf("gport get mismatch on E2E Sched (0x%x) expected type(%d) retreived type (%d)\n", c2_e2e_gport[idx], C2_DEFAULT_E2E_SCHED_TYPE, params_get.type);
    }

    /* retreive type of scheduling element */
    snprintf(error_msg, sizeof(error_msg), "failed on Sched (0x%x)", c2_gport_ucast_scheduler[idx]);
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_scheduler_gport_get(c2_egr_unit, 0, c2_gport_ucast_scheduler[idx], &params_get), error_msg);
    if (params_get.type != C2_SCHED_CL_TYPE) {
        printf("gport get mismatch on Sched (0x%x) expected type(%d) retreived type (%d)\n", c2_gport_ucast_scheduler[idx], C2_SCHED_CL_TYPE, params_get.type);
    }

    /* retreive SE scheduling discipline */
    snprintf(error_msg, sizeof(error_msg), "failed on Sched (0x%x)", c2_gport_ucast_scheduler[idx]);
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_sched_get(c2_egr_unit, c2_gport_ucast_scheduler[idx], 0, &mode, &weight), error_msg);
    if (mode != C2_SCHED_MODE) {
        printf("sched mode mismatch on Sched (0x%x) expected(BCM_COSQ_SP%d) retreived (BCM_COSQ_SP%d)\n", c2_gport_ucast_scheduler[idx], (C2_SCHED_MODE - BCM_COSQ_SP0), (mode - BCM_COSQ_SP0));
    }
    if (weight != 0) {
        printf("sched weight mismatch on Sched (0x%x) expected(%d) retreived (%d)\n", c2_gport_ucast_scheduler[idx], 0, weight);
    }

    /* retreive rate of Scheduler */
    snprintf(error_msg, sizeof(error_msg), "failed on Sched (0x%x)", c2_gport_ucast_scheduler[idx]);
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_bandwidth_get(c2_egr_unit, c2_gport_ucast_scheduler[idx], 0,
            NULL, &kbits_sec_max, NULL), "");
    if ( (kbits_sec_max < (C2_SCHED_KBITS_SEC_MAX - C2_SCHED_KBITS_SEC_MAX_MARGIN)) ||
            (kbits_sec_max > (C2_SCHED_KBITS_SEC_MAX + C2_SCHED_KBITS_SEC_MAX_MARGIN)) ) {
        printf("bandwidth_get mismatch on Sched (0x%x) expected(%d) retreived (%d)\n", c2_gport_ucast_scheduler[idx], C2_SCHED_KBITS_SEC_MAX, kbits_sec_max);
    }

    /* retreive scheduler burst size */
    snprintf(error_msg, sizeof(error_msg), "BandwidthBurstMax on Sched (0x%x) failed", c2_gport_ucast_scheduler[idx]);
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_control_get(c2_egr_unit, c2_gport_ucast_scheduler[idx], 0,
            bcmCosqControlBandwidthBurstMax, &max_burst), error_msg);
    if ( (max_burst < (C2_SCHED_MAX_BURST - C2_SCHED_MAX_BURST_MARGIN)) ||
            (max_burst > (C2_SCHED_MAX_BURST + C2_SCHED_MAX_BURST_MARGIN)) ) {
        printf("control_get-BandwidthBurstMax mismatch on Sched (0x%x) expected(%d) retreived (%d)\n", c2_gport_ucast_scheduler[idx], C2_SCHED_MAX_BURST, max_burst);
    }


    /* retreive intermediate Scheduler elements (SE) */
    for (nbr_fq_sched = 0; nbr_fq_sched < C2_NBR_FQ_SCHEDULERS; nbr_fq_sched++) {
        switch (nbr_fq_sched) {
        case 0: gport_scheduler_fq = c2_gport_ucast_scheduler_fq0[idx];
        exp_mode = BCM_COSQ_SP0; break;
        case 1: gport_scheduler_fq = c2_gport_ucast_scheduler_fq1[idx];
        exp_mode = BCM_COSQ_SP1; break;
        case 2: gport_scheduler_fq = c2_gport_ucast_scheduler_fq2[idx];
        exp_mode = BCM_COSQ_SP2; break;
        default: gport_scheduler_fq = c2_gport_ucast_scheduler_fq3[idx];
        exp_mode = BCM_COSQ_SP3; break;
        }

        /* retreive type of scheduling element */
        snprintf(error_msg, sizeof(error_msg), "failed on Sched (0x%x)", gport_scheduler_fq);
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_scheduler_gport_get(c2_egr_unit, 0, gport_scheduler_fq, &params_get), error_msg);
        if (params_get.type != C2_SCHED_FQ_TYPE) {
            printf("gport get mismatch on Sched (0x%x) expected type(%d) retreived type (%d)\n", gport_scheduler_fq, C2_SCHED_FQ_TYPE, params_get.type);
        }

        /* retreive SE scheduling discipline */
        snprintf(error_msg, sizeof(error_msg), "failed on Sched (0x%x)", gport_scheduler_fq);
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_sched_get(c2_egr_unit, gport_scheduler_fq, 0, &mode, &weight), error_msg);
        if (mode != exp_mode) {
            printf("sched mode mismatch on Sched (0x%x) expected(BCM_COSQ_SP%d) retreived (BCM_COSQ_SP%d)\n", gport_scheduler_fq, (exp_mode - BCM_COSQ_SP0), (mode - BCM_COSQ_SP0));
        }
        if (weight != 0) {
            printf("sched weight mismatch on Sched (0x%x) expected(%d) retreived (%d)\n", gport_scheduler_fq, 0, weight);
        }

        /* retreive rate of Scheduler */
        snprintf(error_msg, sizeof(error_msg), "failed on Sched (0x%x)", gport_scheduler_fq);
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_bandwidth_get(c2_egr_unit, gport_scheduler_fq, 0,
                NULL, &kbits_sec_max, NULL), error_msg);
        if ( (kbits_sec_max < (C2_SCHED_FQ_KBITS_SEC_MAX - C2_SCHED_FQ_KBITS_SEC_MAX_MARGIN)) ||
                (kbits_sec_max > (C2_SCHED_FQ_KBITS_SEC_MAX + C2_SCHED_FQ_KBITS_SEC_MAX_MARGIN)) ) {
            printf("bandwidth_get mismatch on Sched (0x%x) expected(%d) retreived (%d)\n", gport_scheduler_fq, C2_SCHED_FQ_KBITS_SEC_MAX, kbits_sec_max);
        }

        /* retreive scheduler burst size */
        snprintf(error_msg, sizeof(error_msg), "BandwidthBurstMax on Sched (0x%x) failed", gport_scheduler_fq);
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_control_get(c2_egr_unit, gport_scheduler_fq, 0,
                bcmCosqControlBandwidthBurstMax, &max_burst), error_msg);
        if ( (max_burst < (C2_SCHED_FQ_MAX_BURST - C2_SCHED_FQ_MAX_BURST_MARGIN)) ||
                (max_burst > (C2_SCHED_FQ_MAX_BURST + C2_SCHED_FQ_MAX_BURST_MARGIN)) ) {
            printf("control_get-BandwidthBurstMax mismatch on Sched (0x%x) expected(%d) retreived (%d)\n", gport_scheduler_fq, C2_SCHED_FQ_MAX_BURST, max_burst);
        }
    }

    /* retreive connectors and queue groups */
    for (nbr_queue_groups = 0; nbr_queue_groups < C2_NBR_QUEUE_GROUPS; nbr_queue_groups++) {
        switch (nbr_queue_groups) {
        case 0: gport_ucast_voq_connector_group = c2_gport_ucast_voq_connector_group0[idx];
        gport_ucast_queue_group = c2_gport_ucast_queue_group0[idx]; break;
        default: gport_ucast_voq_connector_group = c2_gport_ucast_voq_connector_group1[idx];
        gport_ucast_queue_group = c2_gport_ucast_queue_group1[idx]; break;
        }

        snprintf(error_msg, sizeof(error_msg), "failed on ucast queue group(0x%x)", gport_ucast_queue_group);
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_get(c2_egr_unit, gport_ucast_queue_group,
                &physical_port, &num_cos_levels, &flags), error_msg);

        if (gport_ucast_queue_group == c2_gport_ucast_queue_group0[idx]) {
            if (flags != C2_QUEUE_FLAGS) {
                printf("gport get mismatch on ucast queue (0x%x) failed expected flags(0x%x) retrieved flags(0x%x)\n",
                        gport_ucast_queue_group, C2_QUEUE_FLAGS, flags);
            }
        } else {
            if (flags != (C2_QUEUE_FLAGS | BCM_COSQ_GPORT_TM_FLOW_ID)) {
                printf("gport get mismatch on ucast queue (0x%x) failed expected flags(0x%x) retrieved flags(0x%x)\n",
                        gport_ucast_queue_group, C2_QUEUE_FLAGS, flags);
            }
        }
        if (num_cos_levels != C2_NUM_COS) {
            printf("gport get mismatch on ucast queue (0x%x) expected numCos(%d) retreived numCos(%d)\n",
                    gport_ucast_queue_group, C2_NUM_COS, num_cos_levels);
        }

        /* retreive type of connectors */
        snprintf(error_msg, sizeof(error_msg), "failed on Connector (0x%x)", gport_ucast_voq_connector_group);
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_voq_connector_gport_get(c2_egr_unit, gport_ucast_voq_connector_group, &config_get), error_msg);
        if (config_get.flags != C2_CONN_FLAGS) {
            printf("gport get mismatch on Connector (0x%x) expected flags(0x%x) retreived flags (0x%x\n", gport_ucast_voq_connector_group, C2_CONN_FLAGS, config_get.flags);
        }
        if (config_get.numq != C2_NUM_COS) {
            printf("gport get mismatch on Connector (0x%x) expected numCos(%d) retreived numCos(%d)\n", gport_ucast_voq_connector_group, C2_NUM_COS, config_get.numq);
        }

        /* retreive rate of Connectors and corresponding burst size */
        for (cosq = 0; cosq < 4; cosq++) {
            /* retreive SE scheduling discipline */
            snprintf(error_msg, sizeof(error_msg), "failed on connector:cos (0x%x:%d)", gport_ucast_voq_connector_group, cosq);
            BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_sched_get(c2_egr_unit, gport_ucast_voq_connector_group, cosq, &mode, &weight), error_msg);
            if (mode != BCM_COSQ_SP0) {
                printf("connector mode mismatch on connector:cos (0x%x:%d) expected(BCM_COSQ_SP%d) retreived (BCM_COSQ_SP%d)\n", gport_ucast_voq_connector_group, cosq, (BCM_COSQ_SP0 - BCM_COSQ_SP0), (mode - BCM_COSQ_SP0));
            }
            if (weight != 0) {
                printf("connector weight mismatch on connector:cos (0x%x:%d) expected(%d) retreived (%d)\n", gport_ucast_voq_connector_group, cosq, 0, weight);
            }

            /* retreive rate on the VOQ Connector */
            snprintf(error_msg, sizeof(error_msg), "failed on connector:cosq (0x%x:%d)", gport_ucast_voq_connector_group, cosq);
            BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_bandwidth_get(c2_egr_unit, gport_ucast_voq_connector_group, cosq,
                    NULL, &kbits_sec_max, NULL), error_msg);

            if ( (kbits_sec_max < (C2_CONN_KBITS_SEC_MAX - C2_CONN_KBITS_SEC_MAX_MARGIN)) ||
                    (kbits_sec_max > (C2_CONN_KBITS_SEC_MAX + C2_CONN_KBITS_SEC_MAX_MARGIN)) ) {
                printf("bandwidth_get mismatch on connector:cosq (0x%x:%d) expected(%d) retreived (%d)\n", gport_ucast_voq_connector_group, cosq, C2_CONN_KBITS_SEC_MAX, kbits_sec_max);
            }

            snprintf(error_msg, sizeof(error_msg), "BandwidthBurstMax on Connector:cosq (0x%x:%d) failed", gport_ucast_voq_connector_group, cosq);
            BCM_IF_ERROR_RETURN_MSG(bcm_cosq_control_get(c2_egr_unit, gport_ucast_voq_connector_group, cosq,
                    bcmCosqControlBandwidthBurstMax, &max_burst), error_msg);
            if ( (max_burst < (C2_CONN_MAX_BURST - C2_CONN_MAX_BURST_MARGIN)) ||
                    (max_burst > (C2_CONN_MAX_BURST + C2_CONN_MAX_BURST_MARGIN)) ) {
                printf("control_get-BandwidthBurstMax mismatch on Connector:cosq(0x%x:%d) expected(%d) retreived (%d)\n", gport_ucast_voq_connector_group, cosq, C2_SCHED_MAX_BURST, max_burst);

            }

            /* retreive VOQ Connector slow state */
            snprintf(error_msg, sizeof(error_msg), "FlowSlowRate on Connector:cosq (0x%x:%d) failed", gport_ucast_voq_connector_group, cosq);
            BCM_IF_ERROR_RETURN_MSG(bcm_cosq_control_get(c2_egr_unit, gport_ucast_voq_connector_group, cosq,
                    bcmCosqControlFlowSlowRate, &slow_rate), error_msg);
            if (slow_rate != 0) {
                printf("control_get-FlowSlowRate mismatch on Connector:cosq(0x%x:%d) expected(%d) retreived (%d)\n", gport_ucast_voq_connector_group, cosq, 0, slow_rate);
            }
        }

        /* retreive egress connection set information */
        connection.flags = BCM_COSQ_GPORT_CONNECTION_EGRESS;
        connection.voq_connector = gport_ucast_voq_connector_group;
        snprintf(error_msg, sizeof(error_msg), "failed on Egress, Connector (0x%x)", gport_ucast_voq_connector_group);
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_connection_get(c2_egr_unit, &connection), error_msg);
        if (connection.voq != gport_ucast_queue_group) {
            printf("gport_connection_get on Egress, Connector (0x%x) VoQ association mismatch, Expected (0x%x), retreived (0x%x)\n", gport_ucast_voq_connector_group, gport_ucast_queue_group, connection.voq);
        }

        /* retreive ingress connection set information */
        connection.flags = BCM_COSQ_GPORT_CONNECTION_INGRESS;
        connection.voq = gport_ucast_queue_group;
        snprintf(error_msg, sizeof(error_msg), "failed on Ingress, VoQ (0x%x)", gport_ucast_queue_group);
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_connection_get(c2_ingr_unit, &connection), error_msg);
        if (connection.voq_connector != gport_ucast_voq_connector_group) {
            printf("gport_connection_get on Ingress, VoQ (0x%x) connector association mismatch, Expected (0x%x), retreived (0x%x)\n", gport_ucast_queue_group, gport_ucast_voq_connector_group, connection.voq_connector);
        }
    }

    printf("cint_dnx_tm_fap_config2.c (verify) completed with status (%s)\n", bcm_errmsg(BCM_E_NONE));

    return BCM_E_NONE;
}


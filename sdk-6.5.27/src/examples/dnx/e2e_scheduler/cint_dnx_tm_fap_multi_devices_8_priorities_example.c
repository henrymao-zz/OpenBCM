/* 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
/*
 *  This CINT is meant to provide an example of building a FAP scheduling scheme in 8 priorities mode.
 *  that is connect VOQ connectors to the appropriate HR according to the HRs TC.
 *
 * Creating Schedling Scheme done by the following steps:
 * 1. Egress: Create for each local port: following FQs, VOQ connectors.
 * 2. Ingress: Create VOQs for each system port.
 * 3. Connect Ingress VOQs <=> Egress VOQ connectors.
 * Pay attention the scheduling scheme assumes static IDs for VOQ connectors,VOQs.
 * This is depended by the local and system ports in the system.
 * Conversion is done static using utils functions.
 *
 * For this example to run you must bring up the FAP device with the following SOC properties:
 * diag_cosq_disable=1
 */
cint_reset();

int MAX_COS = 8;
int MAX_NUM_PORTS = 256;
int MAX_NUM_DEVICE = 8;
int MAX_MODIDS_PER_DEVICE = 2;
int MAX_NUM_REMOTE_MODIDS = 2;
struct info_t {
    int         my_modid;
    /* Number of devices in the system */
    int         nof_devices;
    /* Number of physical ports per device */
    int         num_ports;
    /* Number of internal ports (OLP,ERP) per device */
    int         num_internal_ports;
    /* Number of cos levels (COSQ) */
    int         num_cos;
    /* CPU system port */
    int         cpu_sys_port;
    int         internal_ports[MAX_NUM_DEVICE*MAX_NUM_PORTS];
    int         offset_start_of_internal_ports;
    /* Offset given for a system port on each device */
    int         offset_start_of_sys_port;
    /* Offset given for a voq */
    int         offset_start_of_voq;
    /* Offset given for a voq connector */
    int         offset_start_of_voq_connector;
    /* Present local ports on each device */
    bcm_gport_t dest_local_gport[MAX_NUM_PORTS];
    /*
     * Present all VOQ connectors on egress device
     * For each dest local port create 2 voq connectors, for each device
     */
    bcm_gport_t gport_ucast_voq_connector_group[MAX_NUM_DEVICE*MAX_NUM_PORTS];
    /*
     * Present all VOQ on ingress device,
     * For each system port create VOQ
     */
    bcm_gport_t gport_ucast_queue_group[MAX_NUM_DEVICE*MAX_NUM_PORTS];
    /* Present all FQ scheduling on egress device, one for each local port */
    bcm_gport_t gport_ucast_scheduler[MAX_NUM_PORTS*MAX_COS];

    /* If true, a single CPU control two units, and no need to allocate resources with ID.
       Otherwise, this script runs on two CPUs, and we allocate with-ID in order to know how
       to bind ingress to egress resources. */
    int central_cpu;

};
info_t g_info; /* global info */

/*
 * Utils function: Converting between IDs
 */
/* return the index for the internal port stored in the internal_ports[] array */
int
port_internal_id_get(int modid_idx, int port)
{
    int port_i;
    for (port_i=0; port_i<g_info.num_internal_ports; port_i++) {
        if (g_info.internal_ports[modid_idx*MAX_NUM_PORTS+port_i] == port) {
            return port_i;
        }
    }
    return -1;
}

/*
 * Utils function: Converting bewtween IDs
 */
/* Convert (module id,port) id to sysport id */
int
convert_modport_to_sysport_id(int modid_idx,int port)
{
    /* ITMH cannot be sent to system port 0, so we're using system port
               100 instead (for CPU) */
    int internal_port_idx;
    if (port == 0) {
        port = g_info.cpu_sys_port;
    }
    internal_port_idx = port_internal_id_get(modid_idx, port);
    if (internal_port_idx != -1) {
        return (g_info.offset_start_of_sys_port * modid_idx + internal_port_idx
                + g_info.offset_start_of_internal_ports);
    }
    return g_info.offset_start_of_sys_port * modid_idx + port;
}

/*
 * Convert sysport to base VOQ id
 * The conversation includes:
 * VOQ ID = offset + (sysport-1)*num_cos.
 * offset specify the start of the VOQ range (right after the FMQ range) by default 4.
 */
int
convert_sysport_id_to_base_voq_id(int sysport)
{
    /* Assume, no system port 0 */
    if (sysport == 0) {
        return -1;
    }
    return g_info.offset_start_of_voq + (sysport-1)*g_info.num_cos;
}

/*
 * Convert (local port,ingress_modid) to VOQ connector base
 * VOQ connector ID  = offset + egress_local_port * nof_devices * max_cos + ingress_modid*max_cos
 * specify offset start of the VOQ connector ID, by default 32.
 * max_cos is 8
 */

int
convert_modport_to_base_voq_connector(int local_port,int ingress_modid)
{
    /* In case of internal ports (higher than 255) have a port of max + (local_port - 255) */
    if (local_port > 255) {
        local_port = 256 + (local_port % 256);
    }
    return g_info.offset_start_of_voq_connector + local_port*g_info.nof_devices*MAX_MODIDS_PER_DEVICE*MAX_COS
            + ingress_modid*MAX_COS;
}

/*
 * Purpose: Initializes Looks at current configuration and populates
 *          g_info based on that
 */
int
global_info_init (int unit, int nof_devices)
{
    int         port_i = 0;
    int         modid_idx = 0;
    int         idx=0;

    bcm_port_config_t port_config;
    bcm_pbmp_t pbmp;

    g_info.num_cos = MAX_COS;
    g_info.nof_devices = nof_devices;

    /*set num_ports in stk_init*/
    BCM_PBMP_CLEAR(pbmp);

    int max_nof_fap_ids_per_device = *(dnxc_data_get(unit, "device", "general", "max_nof_fap_ids_per_device", NULL));
    MAX_MODIDS_PER_DEVICE = max_nof_fap_ids_per_device > 2 ? max_nof_fap_ids_per_device : 2;
    BCM_IF_ERROR_RETURN_MSG(appl_dnx_sys_device_ports_get(unit, &pbmp), "");

    BCM_PBMP_COUNT(pbmp, g_info.num_ports);

    BCM_PBMP_ITER(pbmp, port_i) {
        BCM_GPORT_LOCAL_SET(g_info.dest_local_gport[idx],port_i);
        idx++;
    }
    g_info.cpu_sys_port = 255;
    /* Offset sysport per device */
    g_info.offset_start_of_sys_port = 256;
    /* Offset VOQ */
    g_info.offset_start_of_voq = 32;
    /* Offset VOQ connector */
    g_info.offset_start_of_voq_connector = 32;

    /* on local device internal ports will start at 240 */
    g_info.offset_start_of_internal_ports = 240;
    g_info.num_internal_ports = 0;

    for (modid_idx=0; modid_idx < nof_devices; modid_idx++) {
        for (port_i=0; port_i<MAX_NUM_PORTS; port_i++) {
            g_info.internal_ports[modid_idx*MAX_NUM_PORTS+port_i] = -1;
        }
    }
    g_info.central_cpu = 1;

    return BCM_E_NONE;
}

/* This function create the scheduling scheme */
int
cosq_init_ing_egr_alloc(int unit) {
    int                         idx, cos, port, core_idx;
    uint32                      flags, dummy_flags;
    int queue_range = 0, sysport;
    int modid_idx, sysport_id, voq_base_id, voq_connector_id;
    bcm_gport_t sysport_gport,modport_gport, e2e_gport;
    int int_flags, tm_port;
    int local_erp_port[2] = {-1};
    int num_erp_ports = 0;
    bcm_port_interface_info_t interface_info;
    bcm_port_mapping_info_t   mapping_info;
    bcm_cosq_voq_connector_gport_t config;
    bcm_cosq_ingress_queue_bundle_gport_config_t conf;
    bcm_port_resource_t resource;
    int delay_tolerance_level, rate_class;
    bcm_cosq_scheduler_gport_params_t params;
    bcm_cosq_gport_info_t gport_info;
    char error_msg[200]={0,};

    /*
     * Before creating VOQs, User must specify the range of the FMQs in
     * the device.
     * In most cases, where fabric multicast is only defined by packet tc,
     * range should set between 0-3.
     * Set range that is different than 0-3, need to change fabric scheduler
     * mode.
     * Please see more details in the UM, Cint example:
     * cint_enhance_application.c
     * and API:
     * bcm_fabric_control_set type: bcmFabricMulticastSchedulerMode.
     */
    queue_range = 0;

    queue_range = 3;
    snprintf(error_msg, sizeof(error_msg), "queue_id :%d", queue_range);
    BCM_IF_ERROR_RETURN_MSG(bcm_fabric_control_set(unit,bcmFabricMulticastQueueMax,queue_range), error_msg);
    /* Get ERP port */
    int_flags =
            BCM_PORT_INTERNAL_EGRESS_REPLICATION;
    BCM_IF_ERROR_RETURN_MSG(bcm_port_internal_get(unit, int_flags, MAX_NUM_PORTS,
            local_erp_port, &num_erp_ports), "");

    /*
     * Creating Schedling Scheme
     * This is done by the following steps:
     * 1. Egress: Create for each local port: following FQs, VOQ connectors.
     * 2. Ingress: Create VOQs for each system port.
     * 3. Connect Ingress VOQs <=> Egress VOQ connectors.
     * Pay attention the scheduling scheme assumes static IDs for VOQ connectors,VOQs.
     * This is depended by the local and system ports in the system.
     * Conversion is done static using utils functions.
     */
    /* Stage I: Egress Create FQs */
    for (idx = 0; idx < g_info.num_ports + g_info.num_internal_ports; idx++) {
        /* Create FQ per traffic class i, attach it to HR SPi */
        for (cos = 0; cos < g_info.num_cos; cos++)
        {
            port = BCM_GPORT_LOCAL_GET(g_info.dest_local_gport[idx]);

            snprintf(error_msg, sizeof(error_msg), "port %d", port);
            BCM_IF_ERROR_RETURN_MSG(bcm_port_get(unit, port, &dummy_flags, &interface_info, &mapping_info), error_msg);
            /* Replace HR mode to enhance */
            /* e2e gport */
            BCM_COSQ_GPORT_E2E_PORT_SET(e2e_gport, BCM_GPORT_LOCAL_GET(g_info.dest_local_gport[idx]));
            gport_info.in_gport = e2e_gport;
            gport_info.cosq = 0;
            BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_handle_get(unit, bcmCosqGportTypeSched, &gport_info), "");
            e2e_gport = gport_info.out_gport;

            params.type = bcmCosqSchedulerGportTypeHrEnhanced;
            params.mode = bcmCosqSchedulerGportModeSimple;
            params.cl_wfq_mode = bcmCosqSchedulerGportClWfqModeNone;
            params.core = mapping_info.core;
            params.shared_order = bcmCosqSchedulerGportSharedOrderNone;
            snprintf(error_msg, sizeof(error_msg), "replace hr scheduler idx:%d failed", idx);
            BCM_IF_ERROR_RETURN_MSG(bcm_cosq_scheduler_gport_add(unit, BCM_COSQ_SCHEDULER_GPORT_REPLACE, params, &e2e_gport), error_msg);

            params.type = bcmCosqSchedulerGportTypeFq;
            params.mode = bcmCosqSchedulerGportModeSimple;
            params.cl_wfq_mode = bcmCosqSchedulerGportClWfqModeNone;
            params.core = mapping_info.core;
            params.shared_order = bcmCosqSchedulerGportSharedOrderNone;
            snprintf(error_msg, sizeof(error_msg), "fq scheduler idx:%d cos: %d failed", idx, cos);
            BCM_IF_ERROR_RETURN_MSG(bcm_cosq_scheduler_gport_add(unit, 0, params, &g_info.gport_ucast_scheduler[idx*MAX_COS+cos]), error_msg);

            snprintf(error_msg, sizeof(error_msg), "hr scheduler-fq idx:%d cos:%d failed", idx, cos);
            BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_sched_set(unit,
                    g_info.gport_ucast_scheduler[idx*MAX_COS+cos], 0,
                    BCM_COSQ_SP0 + cos,0), error_msg);


            /* attach hr scheduler to fq */
            snprintf(error_msg, sizeof(error_msg), "hr scheduler-fq idx:%d cos:%d failed", idx, cos);
            BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_attach(unit, e2e_gport,
                    g_info.gport_ucast_scheduler[idx*MAX_COS+cos], 0), error_msg);

        }
    }

    /* Stage I: Egress Create VOQ connectors */
    for (modid_idx = 0; modid_idx < g_info.nof_devices; modid_idx++) {
        for (idx = 0; idx < g_info.num_ports + g_info.num_internal_ports; idx++) {
            /* create voq connector - with ID */
            flags = BCM_COSQ_GPORT_VOQ_CONNECTOR;

            port = BCM_GPORT_LOCAL_GET(g_info.dest_local_gport[idx]);

            /* Skip ERP port if not far end on ingress */
            for(core_idx = 0 ; core_idx < num_erp_ports ; core_idx++) {
                if ((local_erp_port[core_idx] == port) && (modid_idx == g_info.my_modid)) {
                    continue;
                }
            }

            snprintf(error_msg, sizeof(error_msg), "port %d", port);
            BCM_IF_ERROR_RETURN_MSG(bcm_port_get(unit, port, &dummy_flags, &interface_info, &mapping_info), error_msg);

            /* If both devices are control by a central CPU, no need to allocate with ID,
               since we use the ID allocated by the BCM */
            if (!g_info.central_cpu) {
                flags |= BCM_COSQ_VOQ_CONNECTOR_GPORT_F_WITH_ID;
                voq_connector_id  = convert_modport_to_base_voq_connector(port,modid_idx*MAX_MODIDS_PER_DEVICE);
                BCM_COSQ_GPORT_VOQ_CONNECTOR_CORE_SET(g_info.gport_ucast_voq_connector_group[modid_idx*MAX_NUM_PORTS+idx],voq_connector_id, mapping_info.core);
            }

            config.flags = flags;
            config.nof_remote_cores = MAX_NUM_REMOTE_MODIDS;
            config.numq = g_info.num_cos;
            config.remote_modid = modid_idx * MAX_MODIDS_PER_DEVICE;
            BCM_COSQ_GPORT_E2E_PORT_SET(config.port, port);
            snprintf(error_msg, sizeof(error_msg), "connector idx:%d failed", idx);
            BCM_IF_ERROR_RETURN_MSG(bcm_cosq_voq_connector_gport_add(unit, &config, &g_info.gport_ucast_voq_connector_group[modid_idx*MAX_NUM_PORTS+idx]), error_msg);

            for (cos = 0; cos < g_info.num_cos; cos++) {
                /* Each VOQ connector attach suitable FQ traffic class */
                snprintf(error_msg, sizeof(error_msg), "connector idx:%d cos:%d failed", idx, cos);
                BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_sched_set(unit,
                        g_info.gport_ucast_voq_connector_group[modid_idx*MAX_NUM_PORTS+idx], cos,
                        BCM_COSQ_SP0,0), error_msg);
                /* attach fq scheduler to connecter */
                snprintf(error_msg, sizeof(error_msg), "fq scheduler-connector idx:%d cos:%d failed", idx, cos);
                BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_attach(unit, g_info.gport_ucast_scheduler[idx*MAX_COS+cos],
                        g_info.gport_ucast_voq_connector_group[modid_idx*MAX_NUM_PORTS+idx], cos), error_msg);
            }
        }
    }

    /* Stage 2: Ingress: Create VOQs for each system port. */
    for (modid_idx = 0; modid_idx < g_info.nof_devices; modid_idx++) {
        for (idx = 0; idx < g_info.num_ports + g_info.num_internal_ports; idx++) {
            flags = BCM_COSQ_GPORT_UCAST_QUEUE_GROUP;
            port = BCM_GPORT_LOCAL_GET(g_info.dest_local_gport[idx]);
            /* Skip ERP port if not far end on ingress */
            if ((local_erp_port[0] == port) && (modid_idx == g_info.my_modid)) {
                continue;
            }


            snprintf(error_msg, sizeof(error_msg), "port %d", port);
            BCM_IF_ERROR_RETURN_MSG(bcm_port_get(unit, port, &dummy_flags, &interface_info, &mapping_info), error_msg);
            tm_port = (mapping_info.tm_port != -1 ? mapping_info.tm_port : mapping_info.pp_dsp);
            BCM_GPORT_MODPORT_SET(modport_gport, modid_idx * MAX_MODIDS_PER_DEVICE + mapping_info.core, tm_port);



            if (!g_info.central_cpu) {
                flags |= BCM_COSQ_GPORT_WITH_ID;

                BCM_IF_ERROR_RETURN_MSG(bcm_stk_gport_sysport_get(unit,modport_gport,&sysport_gport), "");

                sysport_id = BCM_GPORT_SYSTEM_PORT_ID_GET(sysport_gport);
                voq_base_id = convert_sysport_id_to_base_voq_id(sysport_id);

                BCM_GPORT_UNICAST_QUEUE_GROUP_SET(g_info.gport_ucast_queue_group[modid_idx*MAX_NUM_PORTS+idx],voq_base_id);
            }

            BCM_IF_ERROR_RETURN_MSG(appl_dnx_logical_port_to_sysport_get(unit, modid_idx * MAX_MODIDS_PER_DEVICE, tm_port, &sysport), "");

            /** Creating VOQs only with system port gport is mandatory for JR2 (JR1 also supports it) */
            BCM_GPORT_SYSTEM_PORT_ID_SET(sysport_gport, sysport);

            BCM_IF_ERROR_RETURN_MSG(bcm_port_resource_get(unit, port, &resource), "");
            BCM_IF_ERROR_RETURN_MSG(appl_dnx_e2e_voq_profiles_get(unit, resource.speed, &delay_tolerance_level, &rate_class), "");
            conf.flags = flags;
            conf.port = sysport_gport;
            conf.numq = g_info.num_cos;
            conf.local_core_id = BCM_CORE_ALL;
            for (cos = 0; cos < g_info.num_cos; cos++) {
                conf.queue_atrributes[cos].delay_tolerance_level = delay_tolerance_level;
                conf.queue_atrributes[cos].rate_class = rate_class;
            }
            BCM_IF_ERROR_RETURN_MSG(bcm_cosq_ingress_queue_bundle_gport_add(unit, &conf, &g_info.gport_ucast_queue_group[modid_idx*MAX_NUM_PORTS+idx]), "");
        }
    }

    return BCM_E_NONE;
}

int
cosq_init_ing_egr_connect(int unit, int mymodid_idx) {
    int                         idx, port, core_idx;
    bcm_cosq_gport_connection_t connection;
    int modid_idx, sysport_id, voq_base_id, voq_connector_id;
    bcm_gport_t voq_connector_gport,sysport_gport,modport_gport, voq_base_gport;
    int local_erp_port[2] = {-1},num_erp_ports;
    int int_flags;
    int cos;
    char error_msg[200]={0,};

    /* Get ERP port */
    int_flags =
            BCM_PORT_INTERNAL_EGRESS_REPLICATION;
    BCM_IF_ERROR_RETURN_MSG(bcm_port_internal_get(unit, int_flags, MAX_NUM_PORTS,
            local_erp_port, &num_erp_ports), "");

    /* Stage 3: Connect Ingress VOQs <=> Egress VOQ connectors. */
    /* Ingress: connect voqs to voq connectors */
    for (modid_idx = 0; modid_idx < g_info.nof_devices; modid_idx++) {
        for (idx = 0; idx < g_info.num_ports + g_info.num_internal_ports; idx++) {
            connection.flags = BCM_COSQ_GPORT_CONNECTION_INGRESS;
            connection.remote_modid = modid_idx * MAX_MODIDS_PER_DEVICE;
            connection.voq = g_info.gport_ucast_queue_group[modid_idx*MAX_NUM_PORTS+idx];
            port = BCM_GPORT_LOCAL_GET(g_info.dest_local_gport[idx]);

            /* Skip ERP port if not far end on ingress */
            for(core_idx = 0 ; core_idx < num_erp_ports ; core_idx++) {
                if ((local_erp_port[core_idx] == port) && (modid_idx == g_info.my_modid)) {
                    continue;
                }
            }
            connection.voq_connector = g_info.gport_ucast_voq_connector_group[mymodid_idx*MAX_NUM_PORTS+idx];

            snprintf(error_msg, sizeof(error_msg), "ingress modid: %d, idx:%d failed", modid_idx, idx);
            BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_connection_set(unit, &connection), error_msg);
        }
    }

    /* Egress: connect voq connectors to voqs */
    for (modid_idx = 0; modid_idx < g_info.nof_devices; modid_idx++) {
        for (idx = 0; idx < g_info.num_ports + g_info.num_internal_ports; idx++) {
            connection.flags = BCM_COSQ_GPORT_CONNECTION_EGRESS;
            connection.remote_modid = modid_idx * MAX_MODIDS_PER_DEVICE;
            connection.voq_connector = g_info.gport_ucast_voq_connector_group[modid_idx*MAX_NUM_PORTS+idx];
            connection.voq = g_info.gport_ucast_queue_group[mymodid_idx*MAX_NUM_PORTS+idx];


            port = BCM_GPORT_LOCAL_GET(g_info.dest_local_gport[idx]);
            /* Skip ERP port if not far end on ingress */
            if ((local_erp_port[0] == port) && (modid_idx == g_info.my_modid)) {
                continue;
            }

            snprintf(error_msg, sizeof(error_msg), "egress modid: %d, idx:%d failed", modid_idx, idx);
            BCM_IF_ERROR_RETURN_MSG(bcm_cosq_gport_connection_set(unit, &connection), error_msg);
        }
    }

    return BCM_E_NONE;
}

/*
 * Purpose: Initialize basic components of a Fap decive.
 * Note:    This is intended to configure only using BCM API.
 * This is the main function of this cint example. The following steps are being done:
 * 1. Setup the diag init structure. (global_info_init)
 * 2. Run the Cosq Application (Scheduling scheme) (cosq_init)
 * Parameters:
 *  - unit:
 *  - modid_idx: Module id index.
 *  - nof_units: Number of devices in the system. cannot be above 8
 *  - unit_arr: An array with unit ids of the rest of units controlled by this CPU.
 *  - modid_idx_arr: An array with mod id indexes of the rest of units controlled by this CPU.
 */
int
bcm_tm_fap_cosq(int unit, int modid_idx, int nof_units, int* unit_arr, int* modid_idx_arr)
{
    int cfg_2nd_unit;
    int unit_idx;
    char error_msg[200]={0,};
    if ((nof_units > MAX_NUM_DEVICE)) {
        printf("Number of units (%d) is more than %d, is negative ", nof_units,MAX_NUM_DEVICE);
        return BCM_E_PARAM;
    }

    /* misc init should be called first */
    BCM_IF_ERROR_RETURN_MSG(global_info_init(unit, nof_units), "");


    cfg_2nd_unit = (g_info.central_cpu && (nof_units > 1));

    /*
     * COSQ Init
     */

    BCM_IF_ERROR_RETURN_MSG(cosq_init_ing_egr_alloc(unit), "");
    if (cfg_2nd_unit) {
        for (unit_idx=0;unit_idx<nof_units-1;unit_idx++) {
            snprintf(error_msg, sizeof(error_msg), "unit: %d", unit_arr[unit_idx]);
            BCM_IF_ERROR_RETURN_MSG(cosq_init_ing_egr_alloc(unit_arr[unit_idx]), error_msg);
        }
    }

    BCM_IF_ERROR_RETURN_MSG(cosq_init_ing_egr_connect(unit, modid_idx), "");
    if (cfg_2nd_unit) {
        for (unit_idx=0;unit_idx<nof_units-1;unit_idx++) {
            snprintf(error_msg, sizeof(error_msg), "unit: %d", unit_arr[unit_idx]);
            BCM_IF_ERROR_RETURN_MSG(cosq_init_ing_egr_connect(unit_arr[unit_idx], modid_idx_arr[unit_idx]), error_msg);
        }
    }
    return BCM_E_NONE;
}

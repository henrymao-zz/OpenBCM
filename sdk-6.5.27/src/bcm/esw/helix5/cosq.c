
/*
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * COS Queue Management
 * Purpose: API to set different cosq, priorities, and scheduler registers.
 */

#include <shared/bsl.h>

#include <soc/defs.h>
#include <sal/core/libc.h>

#if defined(BCM_TRIDENT3_SUPPORT)
#include <soc/drv.h>
#include <soc/scache.h>
#include <soc/profile_mem.h>
#include <soc/debug.h>
#include <soc/helix5.h>

#include <bcm/debug.h>
#include <bcm/error.h>
#include <bcm/cosq.h>
#include <bcm_int/esw/mbcm.h>
#include <bcm_int/esw/stack.h>
#include <bcm_int/esw/cosq.h>
#include <bcm_int/esw/virtual.h>
#include <bcm_int/esw/helix5.h>
#include <bcm_int/esw/trident.h>
#include <bcm_int/esw_dispatch.h>
#include <bcm_int/esw/ecn.h>
#include <bcm_int/bst.h>
#include <bcm_int/esw/pfc_deadlock.h>

#if defined(INCLUDE_PSTATS)
#include <bcm_int/esw/pstats.h>
#endif /* INCLUDE_PSTATS */


#if defined (INCLUDE_TCB) && defined (BCM_TCB_SUPPORT)
#include <bcm_int/esw/tcb.h>
#endif

#if defined(BCM_TOMAHAWK2_SUPPORT)
#include <bcm_int/esw/tomahawk2.h>
#include <soc/tomahawk2.h>
#endif
#include <bcm_int/esw/switch.h>

/* COS default value for HX5 is assumed to be 8 */
#define _BCM_HX5_COS_DEFAULT           8
#define _HX5_NUM_COS_MAP_ENTRY         16
#define _HX5_WIRELESS_COS_MAP_BASE     64
/* Number of Class of Service Supported */
#define _BCM_HX5_NUM_COS(unit) NUM_COS(unit)

#define HX5_WRED_CELL_FIELD_MAX       0x3ffff
#define HX5_WRED_PROFILE_NUM          9

#define _BCM_HX5_OBM_PRIORITY_MAX    3
/* Number of logical Ports */
#define _BCM_HX5_NUM_PORTS 72
/* Number of HG/stacking/uplink  Ports */
#define _BCM_HX5_NUM_ST_PORTS 16

/* HX5 supports 8 PFC priorities */
#define _BCM_HX5_NUM_PFC_CLASS  8

/* Base l3 queue number for down link port */
#define _HX5_BASE_L3QUEUE      416
/* Base l2 queue number for down link port */
#define _HX5_BASE_L2QUEUE      416
/* Base l1 queue number for down link port */
#define _HX5_BASE_L1QUEUE      64
/* Base l0 queue number for down link port */
#define _HX5_BASE_L0QUEUE      48

#define _HX5_ST_NUML0_NODES       3
#define _HX5_ST_NUML1_NODES       4
#define _HX5_ST_NUML2_NODES       26

#define _HX5_NUML0_NODES          1
#define _HX5_NUML1_NODES          2
#define _HX5_NUML2_NODES          16

#define _HX5_CPU_LO_NODE_BASE     103
#define _HX5_CPU_L1_NODE_BASE     173
#define _HX5_CPU_L2_NODE_BASE     1290

#define _HX5_CPU_NUML0_NODES      1
#define _HX5_CPU_NUML1_NODES      1
#define _HX5_CPU_NUML2_NODES      10

#define _BCM_HX5_NUM_SAFC_CLASS  16

/* Number of COSQs configured for this unit */
#define BCM_HX5_NUM_COS(unit) NUM_COS(unit)

#define _HX5_IS_ST_PORT(unit, mmu_port) \
    ((mmu_port < 16) ? 1 : 0)



#define _HX5_PORT_INDEX_GET(unit, mmu_port, index)          \
    do {                                                    \
        if (_HX5_IS_ST_PORT(unit, mmu_port)) {              \
                index = mmu_port;                           \
        } else {                                            \
                index = mmu_port - _BCM_HX5_NUM_ST_PORTS;   \
        }                                                   \
    } while (0)



#define _HX5_PORT_NUM_COS(unit, port) \
    ((IS_CPU_PORT(unit, port)) ? NUM_CPU_COSQ(unit) : \
    (IS_LB_PORT(unit, port)) ? 10 : BCM_HX5_NUM_COS(unit))

#define _BCM_HX5_NUM_TIME_DOMAIN    4

/* Here cosq is < SOC_HX5_NUM_SCHEDULER_PER_ST_PORT */
#define HX5_ST_SCHED_LEVEL_GET(unit, cosq) \
        ((cosq < 3) ? SOC_HX5_NODE_LVL_L0 : (cosq >= 3 && cosq < 7) ? SOC_HX5_NODE_LVL_L1 : SOC_HX5_NODE_LVL_L2)

/* Here cosq is < SOC_HX5_NUM_SCHEDULER_PER_PORT */
#define HX5_SCHED_LEVEL_GET(unit, cosq) \
        ((cosq < 1) ? SOC_HX5_NODE_LVL_L0 : (cosq >= 1 && cosq < 3) ? SOC_HX5_NODE_LVL_L1 : SOC_HX5_NODE_LVL_L2)

#define HX5_CPU_SCHED_LEVEL_GET(unit, cosq) \
        ((cosq < 1) ? SOC_HX5_NODE_LVL_L0 : (cosq == 1) ? SOC_HX5_NODE_LVL_L1 : SOC_HX5_NODE_LVL_L2)

#define _BCM_HX5_NUM_TIME_DOMAIN    4

extern int _bcm_td3_ecn_init(int unit);

typedef struct _bcm_hx5_cosq_time_info_s {
    uint32 ref_count;
} _bcm_hx5_cosq_time_info_t;

STATIC _bcm_hx5_cosq_time_info_t hx5_time_domain_info[BCM_MAX_NUM_UNITS][_BCM_HX5_NUM_TIME_DOMAIN];
/* WRED resolution table */
#define _BCM_HX5_NUM_WRED_RESOLUTION_TABLE   4
STATIC uint32 _bcm_hx5_wred_resolution_tbl[_BCM_HX5_NUM_WRED_RESOLUTION_TABLE] = {
    1,
    0,
    0,
    0,
};


typedef struct _bcm_hx5_cosq_cpu_cosq_config_s {
    /* All MC queues have DB[idx 0] and MCQE[idx 1] space */
    int q_min_limit[2];
    int q_shared_limit[2];
    uint8 q_limit_dynamic[2];
    uint8 q_limit_enable[2];
    uint8 q_color_limit_enable[2];
    uint8 enable;
} _bcm_hx5_cosq_cpu_cosq_config_t;

typedef struct _bcm_hx5_cosq_node_s {
    bcm_gport_t gport;
    int numq;
    int level;
    int hw_index;
    int in_use;
    bcm_gport_t parent_gport;
} _bcm_hx5_cosq_node_t;


typedef struct _bcm_hx5_cosq_st_port_info_s {
    _bcm_hx5_cosq_node_t ucast[SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT];
    _bcm_hx5_cosq_node_t mcast[SOC_HX5_NUM_MCAST_QUEUE_PER_ST_PORT];
    _bcm_hx5_cosq_node_t sched[SOC_HX5_NUM_SCHEDULER_PER_ST_PORT];
} _bcm_hx5_cosq_st_port_info_t;

typedef struct _bcm_hx5_cosq_port_info_s {
    _bcm_hx5_cosq_node_t ucast[SOC_HX5_NUM_UCAST_QUEUE_PER_PORT];
    _bcm_hx5_cosq_node_t mcast[SOC_HX5_NUM_MCAST_QUEUE_PER_PORT];
    _bcm_hx5_cosq_node_t sched[SOC_HX5_NUM_SCHEDULER_PER_PORT];
} _bcm_hx5_cosq_port_info_t;

typedef struct _bcm_hx5_cosq_cpu_port_info_s {
    _bcm_hx5_cosq_node_t sched[SOC_HX5_NUM_SCHEDULER_PER_CPU_PORT];
    _bcm_hx5_cosq_node_t mcast[SOC_HX5_NUM_CPU_QUEUES];
} _bcm_hx5_cosq_cpu_port_info_t;

typedef struct _bcm_hx5_mmu_info_s {
    _bcm_hx5_cosq_port_info_t *_bcm_hx5_port_info;
    _bcm_hx5_cosq_cpu_port_info_t *_bcm_hx5_cpu_port_info;
    _bcm_hx5_cosq_st_port_info_t *_bcm_hx5_st_port_info;
    int gport_tree_created; /* FALSE: No GPORT tree exists */
    /* Mapping from Egress Service Pool ID to Ingress Service Pool:
           Index: Egress service pool ID;
           Bit [3..0] - ingress pool [3..0] */
    int pool_map[SOC_MMU_CFG_SERVICE_POOL_MAX];
} _bcm_hx5_mmu_info_t;

STATIC _bcm_hx5_mmu_info_t *_bcm_hx5_mmu_info[BCM_MAX_NUM_UNITS]; /* MMU info */
STATIC _bcm_hx5_cosq_port_info_t *_bcm_hx5_cosq_port_info[BCM_MAX_NUM_UNITS];
STATIC _bcm_hx5_cosq_st_port_info_t *_bcm_hx5_cosq_st_port_info[BCM_MAX_NUM_UNITS];
STATIC _bcm_hx5_cosq_cpu_port_info_t *_bcm_hx5_cosq_cpu_port_info[BCM_MAX_NUM_UNITS];
STATIC _bcm_hx5_cosq_cpu_cosq_config_t
    *_bcm_hx5_cosq_cpu_cosq_config[BCM_MAX_NUM_UNITS][SOC_HX5_NUM_CPU_QUEUES];

STATIC soc_profile_mem_t *_bcm_hx5_ifp_cos_map_profile[BCM_MAX_NUM_UNITS];

typedef enum {
    _BCM_HX5_COSQ_TYPE_UCAST,
    _BCM_HX5_COSQ_TYPE_MCAST
} _bcm_hx5_cosq_type_t;

/* Memory Profiles */
STATIC soc_profile_mem_t *_bcm_hx5_cos_map_profile[BCM_MAX_NUM_UNITS];
STATIC soc_profile_mem_t *_bcm_hx5_wred_profile[BCM_MAX_NUM_UNITS];
STATIC soc_profile_reg_t *_bcm_hx5_prio2cos_profile[BCM_MAX_NUM_UNITS];

#define _BCM_HX5_MMU_INFO(unit) _bcm_hx5_mmu_info[(unit)]

#define _BCM_HX5_CPU_COS_MAPS_RSVD   9
#define _BCM_HX5_INT_PRI_8_15_MASK   0x8
#define _BCM_HX5_INT_PRI_0_7_MASK    0xf

STATIC int
_bcm_hx5_cosq_ing_pool_pg_pipe_get(int unit, bcm_gport_t gport,
                                   bcm_cos_t prio, int *pipe,
                                   int *sp, int *pg, int *hdrm_pool);
STATIC int
_bcm_hx5_cosq_qgroup_limit_enables_get(int unit, bcm_gport_t gport,
                                       bcm_cos_queue_t cosq,
                                       bcm_cosq_control_t type,
                                       int *arg);

STATIC int
_bcm_hx5_cosq_pool_thresh_adjust(int unit,
                                 bcm_port_t local_port,
                                 int egr_pool,
                                 int delta,
                                 int share_update_flag,
                                 uint8 check_use_count);
STATIC int
_bcm_hx5_cosq_egr_pool_thresh_adjust(int unit, int egr_pool,
                                     int delta, uint8 increase);
STATIC int
_bcm_hx5_cosq_egr_pool_thresh_validate(int unit, int egr_pool,
                                       int delta);
STATIC int
_bcm_hx5_cosq_ing_res_limit_get(int unit, bcm_gport_t gport, bcm_cos_t cosq,
                                bcm_cosq_control_t type, int *arg);

STATIC int
_bcm_hx5_cosq_ing_res_limit_set(int unit, bcm_gport_t gport, bcm_cos_t cosq,
                                bcm_cosq_control_t type, int arg);

STATIC int
_bcm_hx5_cosq_qgroup_limit_get(int unit, bcm_gport_t gport, bcm_cos_t cosq,
                               bcm_cosq_control_t type, int *arg);

/*
 * index: degree, value: contangent(degree) * 100
 * max value is 0xffff (16-bit) at 0 degree
 * Same as TD2.
 */
STATIC int
_bcm_hx5_cotangent_lookup_table[] =
{
    /*  0.. 5 */  65535, 5728, 2863, 1908, 1430, 1143,
    /*  6..11 */    951,  814,  711,  631,  567,  514,
    /* 12..17 */    470,  433,  401,  373,  348,  327,
    /* 18..23 */    307,  290,  274,  260,  247,  235,
    /* 24..29 */    224,  214,  205,  196,  188,  180,
    /* 30..35 */    173,  166,  160,  153,  148,  142,
    /* 36..41 */    137,  132,  127,  123,  119,  115,
    /* 42..47 */    111,  107,  103,  100,   96,   93,
    /* 48..53 */     90,   86,   83,   80,   78,   75,
    /* 54..59 */     72,   70,   67,   64,   62,   60,
    /* 60..65 */     57,   55,   53,   50,   48,   46,
    /* 66..71 */     44,   42,   40,   38,   36,   34,
    /* 72..77 */     32,   30,   28,   26,   24,   23,
    /* 78..83 */     21,   19,   17,   15,   14,   12,
    /* 84..89 */     10,    8,    6,    5,    3,    1,
    /* 90     */      0
};

/*
 * Given a slope (angle in degrees) from 0 to 90, return the number of cells
 * in the range from 0% drop probability to 100% drop probability.
 * Same as TD2.
 */
STATIC int
_bcm_hx5_angle_to_cells(int angle)
{
    return (_bcm_hx5_cotangent_lookup_table[angle]);
}

/*
 * Given a number of packets in the range from 0% drop probability
 * to 100% drop probability, return the slope (angle in degrees).
 * Same as TD2.
 */
STATIC int
_bcm_hx5_cells_to_angle(int packets)
{
    int angle;

    for (angle = 90; angle >= 0 ; angle--) {
        if (packets <= _bcm_hx5_cotangent_lookup_table[angle]) {
            break;
        }
    }
    return angle;
}


/*
 *  Convert HW drop probability to percent value
 *  Same as TD2.
 */
STATIC int
_bcm_hx5_hw_drop_prob_to_percent[] = {
    0,     /* 0  */
    1,     /* 1  */
    2,     /* 2  */
    3,     /* 3  */
    4,     /* 4  */
    5,     /* 5  */
    6,     /* 6  */
    7,     /* 7  */
    8,     /* 8  */
    9,     /* 9  */
    10,    /* 10 */
    25,    /* 11 */
    50,    /* 12 */
    75,    /* 13 */
    100,   /* 14 */
    -1     /* 15 */
};

STATIC int
_bcm_hx5_percent_to_drop_prob(int percent)
{
   int i;

   for (i = 14; i > 0 ; i--) {
      if (percent >= _bcm_hx5_hw_drop_prob_to_percent[i]) {
          break;
      }
   }
   return i;
}

STATIC int
_bcm_hx5_drop_prob_to_percent(int drop_prob) {
   return (_bcm_hx5_hw_drop_prob_to_percent[drop_prob]);
}


STATIC int
_bcm_hx5_cosq_bucket_set(int unit, bcm_gport_t gport, bcm_cos_queue_t cosq,
                         uint32 min_quantum, uint32 max_quantum,
                         uint32 kbits_burst_min, uint32 kbits_burst_max,
                         uint32 flags);
STATIC int
_bcm_hx5_cosq_bucket_get(int unit, bcm_port_t gport, bcm_cos_queue_t cosq,
                        uint32 *min_quantum, uint32 *max_quantum,
                        uint32 *kbits_burst_min, uint32 *kbits_burst_max,
                        uint32 *flags);


/*
 * Function:
 *     _bcm_hx5_cosq_node_get
 * Purpose:
 *     Get internal information of queue group or scheduler type GPORT
 * Parameters:
 *     unit       - (IN) unit number
 *     gport      - (IN) queue group/scheduler GPORT identifier
 *     modid      - (OUT) module identifier
 *     port       - (OUT) port number
 *     id         - (OUT) queue group or scheduler identifier
 *     node       - (OUT) node structure for the specified GPORT
 * Returns:
 *     BCM_E_XXX
 */
int
_bcm_hx5_cosq_node_get(int unit, bcm_gport_t gport, bcm_module_t *modid,
                       bcm_port_t *port, int *id, _bcm_hx5_cosq_node_t **node)
{
    _bcm_hx5_cosq_port_info_t *port_info = NULL;
    _bcm_hx5_cosq_st_port_info_t *stport_info = NULL;
    _bcm_hx5_cosq_cpu_port_info_t *cpu_port_info = NULL;
    _bcm_hx5_cosq_node_t *node_base = NULL;
    bcm_module_t modid_out;
    bcm_port_t port_out;
    int index, port_index;
    int num_sched_port = 0;
    int phy_port, mmu_port;
    soc_info_t *si = &SOC_INFO(unit);

    if (_bcm_hx5_cosq_port_info[unit] == NULL) {
        return BCM_E_INIT;
    }

    if (_bcm_hx5_cosq_st_port_info[unit] == NULL) {
        return BCM_E_INIT;
    }

    if (_bcm_hx5_cosq_cpu_port_info[unit] == NULL) {
        return BCM_E_INIT;
    }

    BCM_IF_ERROR_RETURN(bcm_esw_stk_my_modid_get(unit, &modid_out));
    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
        port_out = BCM_GPORT_UCAST_QUEUE_GROUP_SYSPORTID_GET(gport);
    } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        port_out = BCM_GPORT_MCAST_QUEUE_GROUP_SYSPORTID_GET(gport);
    } else if (BCM_GPORT_IS_SCHEDULER(gport)) {
        port_out = BCM_GPORT_SCHEDULER_GET(gport) & 0xff;
    } else {
        return BCM_E_PORT;
    }

    if (!SOC_PORT_VALID(unit, port_out) || IS_LB_PORT(unit, port_out) ) {
        return BCM_E_PORT;
    }

    phy_port = si->port_l2p_mapping[port_out];
    mmu_port = si->port_p2m_mapping[phy_port];
    _HX5_PORT_INDEX_GET(unit, mmu_port, port_index);

    if (IS_CPU_PORT(unit, port_out)) {
        cpu_port_info = _bcm_hx5_cosq_cpu_port_info[unit];
        num_sched_port = SOC_HX5_NUM_SCHEDULER_PER_CPU_PORT;
    } else if(_HX5_IS_ST_PORT(unit, mmu_port)){
        stport_info = &_bcm_hx5_cosq_st_port_info[unit][port_index];
        num_sched_port = SOC_HX5_NUM_SCHEDULER_PER_ST_PORT;
    } else {
        port_info = &_bcm_hx5_cosq_port_info[unit][port_index];
        num_sched_port = SOC_HX5_NUM_SCHEDULER_PER_PORT;
    }

    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
        index = BCM_GPORT_UCAST_QUEUE_GROUP_QID_GET(gport);
        node_base = (_HX5_IS_ST_PORT(unit, mmu_port)) ? stport_info->ucast : port_info->ucast;
    } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        index = BCM_GPORT_MCAST_QUEUE_GROUP_QID_GET(gport);
        if (IS_CPU_PORT(unit, port_out)) {
            node_base = cpu_port_info->mcast;
        } else {
            node_base = (_HX5_IS_ST_PORT(unit, mmu_port)) ? stport_info->mcast : port_info->mcast;
        }
    } else {
        index = (BCM_GPORT_SCHEDULER_GET(gport) >> 16) & 0x3ff;
        if (index >= num_sched_port) {
            return BCM_E_PORT;
        }
        if (IS_CPU_PORT(unit, port_out)) {
            node_base = cpu_port_info->sched;
        } else {
            node_base = (_HX5_IS_ST_PORT(unit, mmu_port)) ? stport_info->sched : port_info->sched;
        }
    }

    if ((node_base == NULL) ||
        (node_base[index].numq == 0) ||
        (node_base[index].in_use == 0)) {
        return BCM_E_NOT_FOUND;
    }

    if (modid != NULL) {
        *modid = modid_out;
    }
    if (port != NULL) {
        *port = port_out;
    }
    if (id != NULL) {
        *id = index;
    }
    if (node != NULL) {
        *node = &node_base[index];
    }

    return BCM_E_NONE;

}


/*
 * Function:
 *     _bcm_hx5_cosq_port_resolve
 * Purpose:
 *     Resolve following COS queue related GPORT
 *         BCM_GPORT_TYPE_UCAST_QUEUE_GROUP
 *         BCM_GPORT_TYPE_MCAST_QUEUE_GROUP
 *         BCM_GPORT_TYPE SCHEDULER
 * Parameters:
 *     unit       - (IN) unit number
 *     gport      - (IN) GPORT identifier
 *     modid      - (OUT) module identifier
 *     port       - (OUT) port number
 *     trunk_id   - (OUT) trunk identifier
 *     id         - (OUT) queue group or scheduler identifier
 *     qnum       - (OUT) hw_index for given queue gport
 * Returns:
 *     BCM_E_XXX
 */
int
_bcm_hx5_cosq_port_resolve(int unit, bcm_gport_t gport, bcm_module_t *modid,
                           bcm_port_t *port, bcm_trunk_t *trunk_id, int *id,
                           int *qnum)
{
    _bcm_hx5_cosq_node_t *node;

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_node_get(unit, gport, modid, port, id, &node));
    *trunk_id = -1;

    if (qnum) {
        if (node->hw_index == -1) {
            return BCM_E_PARAM;
        }
        *qnum = node->hw_index;
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *     _bcm_hx5_cosq_localport_resolve
 * Purpose:
 *     Resolve GPORT if it is a local port
 * Parameters:
 *     unit       - (IN) unit number
 *     gport      - (IN) GPORT identifier
 *     local_port - (OUT) local port number
 * Returns:
 *     BCM_E_XXX
 */
STATIC int
_bcm_hx5_cosq_localport_resolve(int unit, bcm_gport_t gport,
                                bcm_port_t *local_port)
{
    bcm_module_t module;
    bcm_port_t port;
    bcm_trunk_t trunk;
    int id, result, rv;

    if (!BCM_GPORT_IS_SET(gport)) {
        if (!SOC_PORT_VALID(unit, gport)) {
            return BCM_E_PORT;
        }
        *local_port = gport;
        return BCM_E_NONE;
    }

    rv = _bcm_esw_gport_resolve(unit, gport, &module, &port, &trunk, &id);
    if (rv == BCM_E_PORT) {
        /* returning E_PARAM when invalid gport is given as param */
        return BCM_E_PARAM;
    } else if (BCM_FAILURE(rv)) {
        return rv;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_esw_modid_is_local(unit, module, &result));
    if (result == FALSE) {
        return BCM_E_PARAM;
    }

    *local_port = port;

    return BCM_E_NONE;
}


/*
 * Function:
 *     _bcm_hx5_cosq_cleanup
 * Purpose:
 *     Clean resource in case of error during Cosq Init
 * Parameters:
 *     unit - (IN) unit number
 * Returns:
 *     No return value
 */
STATIC void
_bcm_hx5_cosq_cleanup(int unit)
{
    if (_bcm_hx5_cosq_port_info[unit] != NULL) {
        sal_free(_bcm_hx5_cosq_port_info[unit]);
        _bcm_hx5_cosq_port_info[unit] = NULL;
    }

    if (_bcm_hx5_cosq_st_port_info[unit] != NULL) {
        sal_free(_bcm_hx5_cosq_st_port_info[unit]);
        _bcm_hx5_cosq_st_port_info[unit] = NULL;
    }

    if (_bcm_hx5_cosq_cpu_port_info[unit] != NULL) {
        sal_free(_bcm_hx5_cosq_cpu_port_info[unit]);
        _bcm_hx5_cosq_cpu_port_info[unit] = NULL;
    }

    if (_bcm_hx5_mmu_info[unit] != NULL) {
        sal_free(_bcm_hx5_mmu_info[unit]);
        _bcm_hx5_mmu_info[unit] = NULL;
    }

    if (_bcm_hx5_wred_profile[unit] != NULL) {
        (void)soc_profile_mem_destroy(unit, _bcm_hx5_wred_profile[unit]);
        sal_free(_bcm_hx5_wred_profile[unit]);
        _bcm_hx5_wred_profile[unit] = NULL;
    }

    /* Cleanup profile for PRIO2COS_PROFILE register */
    if (_bcm_hx5_prio2cos_profile[unit] != NULL) {
        (void)soc_profile_reg_destroy(unit, _bcm_hx5_prio2cos_profile[unit]);
        sal_free(_bcm_hx5_prio2cos_profile[unit]);
        _bcm_hx5_prio2cos_profile[unit] = NULL;
    }

    if (_bcm_hx5_ifp_cos_map_profile[unit] != NULL) {
        (void)soc_profile_mem_destroy(unit, _bcm_hx5_ifp_cos_map_profile[unit]);
        sal_free(_bcm_hx5_ifp_cos_map_profile[unit]);
        _bcm_hx5_ifp_cos_map_profile[unit] = NULL;
    }
#if defined (INCLUDE_TCB) && defined (BCM_TCB_SUPPORT)
    if (soc_feature(unit, soc_feature_tcb)) {
        _bcm_hx5_cosq_tcb_deinit(unit);
    }
#endif /* INCLUDE_TCB && BCM_TCB_SUPPORT */

    if (soc_feature(unit, soc_feature_pfc_deadlock)) {
        (void)_bcm_hx5_pfc_deadlock_deinit(unit);
    }

}

/*
 * Function:
 *     _bcm_hx5_cosq_node_hw_index_get
 * Purpose:
 *     Get cosq node hardware index
 * Parameters:
 *     unit        - (IN) unit number
 *     gport       - (IN) GPORT identifier
 *     cosq        - (OUT) COS queue number
 * Returns:
 *     BCM_E_XXX
 */
STATIC int
_bcm_hx5_cosq_node_hw_index_get(int unit, bcm_gport_t gport,
        bcm_cos_queue_t *cosq)
{
    _bcm_hx5_cosq_node_t *node = NULL;
    int local_port = -1;
    int phy_port, mmu_port;
    int num_uc, num_mc;

    soc_info_t *si = &SOC_INFO(unit);

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_node_get(unit, gport, NULL, &local_port, NULL,
                                &node));

    phy_port = si->port_l2p_mapping[local_port];
    mmu_port = si->port_p2m_mapping[phy_port];

    if(IS_CPU_PORT(unit, local_port)){
        num_uc = 0;
        num_mc = SOC_HX5_NUM_CPU_QUEUES;
    }else {
        if(_HX5_IS_ST_PORT(unit, mmu_port)) {
            num_uc = SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT;
            num_mc = SOC_HX5_NUM_MCAST_QUEUE_PER_ST_PORT;
        }else {
            num_uc = SOC_HX5_NUM_UCAST_QUEUE_PER_PORT;
            num_mc = SOC_HX5_NUM_MCAST_QUEUE_PER_PORT;
        }
    }

    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
        if(_HX5_IS_ST_PORT(unit, mmu_port)){
            *cosq = node->hw_index - (mmu_port * num_uc);
        } else {
            *cosq = node->hw_index - (_HX5_BASE_L3QUEUE +
                    ((mmu_port - _BCM_HX5_NUM_ST_PORTS) * num_uc));
        }
    } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        if(IS_CPU_PORT(unit, local_port)){
            *cosq = node->hw_index - _HX5_CPU_L2_NODE_BASE;
        } else if(_HX5_IS_ST_PORT(unit, mmu_port)){
            *cosq = node->hw_index - (mmu_port * num_mc);
        } else {
            *cosq = node->hw_index - (_HX5_BASE_L3QUEUE +
                    ((mmu_port - _BCM_HX5_NUM_ST_PORTS) * num_mc));
        }
    } else {
         switch(node->level) {
             case SOC_HX5_NODE_LVL_L0:
                 if(IS_CPU_PORT(unit, local_port)){
                     *cosq = node->hw_index - _HX5_CPU_LO_NODE_BASE;
                 } else if(_HX5_IS_ST_PORT(unit, mmu_port)){
                     *cosq = node->hw_index - (mmu_port * _HX5_ST_NUML0_NODES);
                 } else {
                     *cosq = node->hw_index - (_HX5_BASE_L0QUEUE +
                             ((mmu_port  - _BCM_HX5_NUM_ST_PORTS) * _HX5_NUML0_NODES));
                 }
                 break;
             case SOC_HX5_NODE_LVL_L1:
                 if(IS_CPU_PORT(unit, local_port)){
                     *cosq = node->hw_index - _HX5_CPU_L1_NODE_BASE;
                 } else if(_HX5_IS_ST_PORT(unit, mmu_port)){
                     *cosq = node->hw_index - (mmu_port * _HX5_ST_NUML1_NODES);
                 } else {
                     *cosq = node->hw_index - (_HX5_BASE_L1QUEUE +
                             ((mmu_port - _BCM_HX5_NUM_ST_PORTS) * _HX5_NUML1_NODES));
                 }
                 break;
             case SOC_HX5_NODE_LVL_L2:
                 if(IS_CPU_PORT(unit, local_port)){
                     *cosq = node->hw_index - _HX5_CPU_L2_NODE_BASE;
                 } else if(_HX5_IS_ST_PORT(unit, mmu_port)){
                     *cosq = node->hw_index - (mmu_port * _HX5_ST_NUML2_NODES);
                 } else {
                     *cosq = node->hw_index - (_HX5_BASE_L2QUEUE +
                             ((mmu_port - _BCM_HX5_NUM_ST_PORTS) * _HX5_NUML2_NODES));
                 }
                 break;
             default:
                 return BCM_E_PARAM;
         }

    }

    return BCM_E_NONE;
}


/*
 * Function:
 *     bcm_hx5_cosq_gport_get
 * Purpose:
 *     Get a cosq gport structure
 * Parameters:
 *     unit       - (IN) unit number
 *     gport      - (IN) GPORT identifier
 *     port       - (OUT) port number
 *     numq       - (OUT) number of COS queues
 *     flags      - (OUT) flags (BCM_COSQ_GPORT_XXX)
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_gport_get(int unit, bcm_gport_t gport, bcm_gport_t *port,
                       int *numq, uint32 *flags)
{
    _bcm_hx5_cosq_node_t *node;
    bcm_port_t local_port;
    bcm_module_t modid;
    _bcm_gport_dest_t dest;
    int phy_port, mmu_port;
    soc_info_t *si = &SOC_INFO(unit);

    if (port == NULL || numq == NULL || flags == NULL) {
        return BCM_E_PARAM;
    }

    LOG_INFO(BSL_LS_BCM_COSQ,
             (BSL_META_U(unit,
              "bcm_hx5_cosq_gport_get: unit=%d gport=0x%x\n"),
              unit, gport));

    if ((BCM_GPORT_IS_SCHEDULER(gport)) ||
        BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
        BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport) ||
        BCM_GPORT_IS_UCAST_SUBSCRIBER_QUEUE_GROUP(gport)) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_node_get(unit, gport, NULL, &local_port, NULL,
                                    &node));

        *numq = node->numq;

        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            *flags = BCM_COSQ_GPORT_UCAST_QUEUE_GROUP;
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            *flags = BCM_COSQ_GPORT_MCAST_QUEUE_GROUP;
        } else if (BCM_GPORT_IS_SCHEDULER(gport)) {
            *flags = BCM_COSQ_GPORT_SCHEDULER;
        } else {
            *flags = 0;
        }
    } else {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
        *flags = 0;
        phy_port = si->port_l2p_mapping[local_port];
        mmu_port = si->port_p2m_mapping[phy_port];
        *numq = (_HX5_IS_ST_PORT(unit, mmu_port)) ? SOC_HX5_NUM_SCHEDULER_PER_ST_PORT :
                                                   SOC_HX5_NUM_SCHEDULER_PER_PORT;
    }

    if (SOC_USE_GPORT(unit)) {
        BCM_IF_ERROR_RETURN(bcm_esw_stk_my_modid_get(unit, &modid));
        dest.gport_type = _SHR_GPORT_TYPE_MODPORT;
        dest.modid = modid;
        dest.port = local_port;
        BCM_IF_ERROR_RETURN(_bcm_esw_gport_construct(unit, &dest, port));
    } else {
        *port = local_port;
    }

    LOG_INFO(BSL_LS_BCM_COSQ,
             (BSL_META_U(unit,
              "                       port=0x%x numq=%d flags=0x%x\n"),
              *port, *numq, *flags));

    return BCM_E_NONE;
}

/*
 * Function:
 *     _bcm_hx5_cosq_gport_add
 * Purpose:
 *     Create a cosq gport structure
 * Parameters:
 *     unit  - (IN) unit number
 *     port  - (IN) port number
 *     numq  - (IN) number of COS queues
 *     flags - (IN) flags (BCM_COSQ_GPORT_XXX)
 *     gport - (OUT) GPORT identifier
 * Returns:
 *     BCM_E_XXX
 */
STATIC int
_bcm_hx5_cosq_gport_add(int unit, bcm_gport_t port, int numq, uint32 flags,
                       bcm_gport_t *gport)
{
    _bcm_hx5_cosq_port_info_t *port_info = NULL;
    _bcm_hx5_cosq_st_port_info_t *stport_info = NULL;
    _bcm_hx5_cosq_cpu_port_info_t *cpu_port_info = NULL;
    _bcm_hx5_cosq_node_t *node = NULL;
    int phy_port, mmu_port;
    bcm_port_t local_port;
    uint32 sched_encap;
    int id;
    int num_uc, num_mc, num_sc, index;

    soc_info_t *si = &SOC_INFO(unit);

    LOG_INFO(BSL_LS_BCM_COSQ,
        (BSL_META_U(unit,
                    "_bcm_hx5_cosq_gport_add: unit=%d port=0x%x "
                    "numq=%d flags=0x%x\n"), unit, port, numq, flags));

    if (gport == NULL) {
        return BCM_E_PARAM;
    }

    if (_bcm_hx5_cosq_port_info[unit] == NULL) {
        return BCM_E_INIT;
    }

    if (_bcm_hx5_cosq_st_port_info[unit] == NULL) {
        return BCM_E_INIT;
    }

    if (_bcm_hx5_cosq_cpu_port_info[unit] == NULL) {
        return BCM_E_INIT;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));

    if (local_port < 0 || IS_LB_PORT(unit, local_port)) {
        return BCM_E_PORT;
    }

    phy_port = si->port_l2p_mapping[local_port];
    mmu_port = si->port_p2m_mapping[phy_port];
    _HX5_PORT_INDEX_GET(unit, mmu_port, index);
    if (IS_CPU_PORT(unit, local_port)) {
        cpu_port_info = _bcm_hx5_cosq_cpu_port_info[unit];
        num_uc = 0;
        num_mc = SOC_HX5_NUM_CPU_QUEUES;
        num_sc = SOC_HX5_NUM_SCHEDULER_PER_CPU_PORT;
    } else if(_HX5_IS_ST_PORT(unit, mmu_port)) {
        stport_info = &_bcm_hx5_cosq_st_port_info[unit][index];
        num_uc = SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT;
        num_mc = SOC_HX5_NUM_MCAST_QUEUE_PER_ST_PORT;
        num_sc = SOC_HX5_NUM_SCHEDULER_PER_ST_PORT;
    } else {
        port_info = &_bcm_hx5_cosq_port_info[unit][index];
        num_uc = SOC_HX5_NUM_UCAST_QUEUE_PER_PORT;
        num_mc = SOC_HX5_NUM_UCAST_QUEUE_PER_PORT;
        num_sc = SOC_HX5_NUM_SCHEDULER_PER_PORT;
    }

    switch (flags) {
        case BCM_COSQ_GPORT_UCAST_QUEUE_GROUP:
            if (IS_CPU_PORT(unit, local_port)) {
                return BCM_E_PARAM;
            }
            if (numq != 1) {
                return BCM_E_PARAM;
            }
            for (id = 0; id < num_uc; id++) {
                if(_HX5_IS_ST_PORT(unit, mmu_port)) {
                    if ((stport_info->ucast[id].numq == 0) ||
                        (stport_info->ucast[id].in_use == 0)) {
                         break;
                    }
                } else {
                    if ((port_info->ucast[id].numq == 0) ||
                        (port_info->ucast[id].in_use == 0)) {
                         break;
                    }
                }
            }
            if (id == num_uc) {
                return BCM_E_RESOURCE;
            }
            BCM_GPORT_UCAST_QUEUE_GROUP_SYSQID_SET(*gport, local_port, id);
            if (_HX5_IS_ST_PORT(unit, mmu_port)){
               node = &stport_info->ucast[id];
            } else {
               node = &port_info->ucast[id];
            }
            node->level = SOC_HX5_NODE_LVL_L3;
            break;
        case BCM_COSQ_GPORT_MCAST_QUEUE_GROUP:
            if (numq != 1) {
                return BCM_E_PARAM;
            }
            if (IS_CPU_PORT(unit, local_port)) {
                for (id = 0; id < SOC_HX5_NUM_CPU_QUEUES; id++) {
                    if ((cpu_port_info->mcast[id].numq == 0) ||
                        (cpu_port_info->mcast[id].in_use == 0)) {
                        break;
                    }
                }
                if (id == SOC_HX5_NUM_CPU_QUEUES) {
                    return BCM_E_RESOURCE;
                }
            } else {
                for (id = 0; id < num_mc; id++) {
                    if(_HX5_IS_ST_PORT(unit, mmu_port)) {
                        if ((stport_info->mcast[id].numq == 0) ||
                            (stport_info->mcast[id].in_use == 0)) {
                             break;
                        }
                     } else {
                        if ((port_info->mcast[id].numq == 0) ||
                            (port_info->mcast[id].in_use == 0)) {
                            break;
                        }
                    }
                }
                if (id == num_mc) {
                    return BCM_E_RESOURCE;
                }
            }
            BCM_GPORT_MCAST_QUEUE_GROUP_SYSQID_SET(*gport, local_port, id);
            if (IS_CPU_PORT(unit, local_port)) {
                node = &cpu_port_info->mcast[id];
            } else if ( _HX5_IS_ST_PORT(unit, mmu_port)){
                node = &stport_info->mcast[id];
            } else {
                node = &port_info->mcast[id];
            }
            node->level = SOC_HX5_NODE_LVL_L3;
            break;
        case BCM_COSQ_GPORT_SCHEDULER:
        case 0:
            if (numq <= 0) {
                return BCM_E_PARAM;
            }
            if (IS_CPU_PORT(unit, local_port)) {
                for (id = 0; id < SOC_HX5_NUM_SCHEDULER_PER_CPU_PORT; id++) {
                    if (cpu_port_info->sched[id].numq == 0) {
                        break;
                    }
                    if (id == num_sc) {
                        return BCM_E_RESOURCE;
                    }
                }
                if (id == SOC_HX5_NUM_SCHEDULER_PER_CPU_PORT) {
                    return BCM_E_RESOURCE;
                }

                sched_encap = (id << 16) | local_port;
                BCM_GPORT_SCHEDULER_SET(*gport, sched_encap);
                node = &cpu_port_info->sched[id];
                node->level = SOC_HX5_NODE_LVL_L0;
            }

            if (_HX5_IS_ST_PORT(unit, mmu_port) && !IS_CPU_PORT(unit, local_port)){
                for (id = 0; id < SOC_HX5_NUM_SCHEDULER_PER_ST_PORT; id++) {
                    if (stport_info->sched[id].numq == 0) {
                        break;
                    }
                }
                if (id == SOC_HX5_NUM_SCHEDULER_PER_ST_PORT) {
                    return BCM_E_RESOURCE;
                }
                sched_encap = (id << 16) | local_port;
                BCM_GPORT_SCHEDULER_SET(*gport, sched_encap);
                node = &stport_info->sched[id];
                node->level = SOC_HX5_NODE_LVL_L0;
            } 

            if (!_HX5_IS_ST_PORT(unit, mmu_port) && !IS_CPU_PORT(unit, local_port)){
                for (id = 0; id < SOC_HX5_NUM_SCHEDULER_PER_PORT; id++) {
                    if (port_info->sched[id].numq == 0) {
                        break;
                    }
                }
                if (id == SOC_HX5_NUM_SCHEDULER_PER_PORT) {
                    return BCM_E_RESOURCE;
               }
                sched_encap = (id << 16) | local_port;
                BCM_GPORT_SCHEDULER_SET(*gport, sched_encap);
                node = &port_info->sched[id];
                node->level = SOC_HX5_NODE_LVL_L0;
             }
            break;
        default:
            return BCM_E_PARAM;
    }

    node->gport = *gport;
    node->numq = numq;
    node->in_use = 1;

    LOG_INFO(BSL_LS_BCM_COSQ,
            (BSL_META_U(unit,"gport=0x%x\n"), *gport));

    return BCM_E_NONE;
}

/*
 * This function does two things:
 * 1. Tests whether the corresponding COS_BMP bit is set or not.
 * 2. Tests whether the queue corresponding to given cos is
 *     mapped to correct L2 or not.
 *
 * L2.0 is associated with CMC0 CH1(Rx) (pci)
 * L2.1 is associated with CMC0 CH2(Rx) (pci)
 * L2.2 is associated with CMC0 CH3(Rx) (pci)
 * L2.3 is associated with CMC0 CH4(Rx) (pci)
 * L2.4 is associated with CMC0 CH5(Rx) (pci)
 * L2.5 is associated with CMC0 CH6(Rx) (pci)
 * L2.6 is associated with CMC0 CH7(Rx) (pci)
 * L2.7 is associated with CMC1 CHx(Rx) (uc0)
 * L2.8 is associated with CMC1 CHx(Rx) (uC1)
 * L2.9 is reserved
 */
int
bcm_hx5_rx_queue_channel_set_test(int unit, bcm_cos_queue_t queue_id,
                                          bcm_rx_chan_t chan_id)
{
#if defined(BCM_CMICX_SUPPORT)
    if (soc_feature(unit, soc_feature_cmicx)) {
        int pci_cmc = SOC_PCI_CMC(unit);
        uint32 reg_val;
        uint32 bit;
        uint32 max_rx_channels = 0;
        int index;
        _bcm_hx5_cosq_cpu_port_info_t *cpu_port_info = NULL;
        bcm_gport_t cpu_l2_gport = -1;
        bcm_gport_t parent_gport = -1;

        soc_dma_max_rx_channels_get(unit, &max_rx_channels);

        if ((chan_id <= 0) || (chan_id >= max_rx_channels)) {
            return BCM_E_PARAM;
        }

        if (_bcm_hx5_cosq_cpu_port_info[unit] == NULL) {
            return BCM_E_INIT;
        }

        cpu_port_info = _bcm_hx5_cosq_cpu_port_info[unit];

        if ((chan_id > 0) && (chan_id < 8 ))  {
            index = chan_id + 2;
            cpu_l2_gport = cpu_port_info->sched[index - 1].gport;
        }

        if (queue_id < 0) { /* All COS Queues */
            for (queue_id = 0; queue_id < NUM_CPU_COSQ(unit); queue_id++) {
                soc_dma_cos_ctrl_queue_get(unit, pci_cmc, chan_id, queue_id,
                        &reg_val);

                bit = 1 << (queue_id % 32);
                if (reg_val & bit) {
                    /* find the parent gport of this queue if parent gport is
                     * not equal to l0 gport for this channel return error */
                    parent_gport = cpu_port_info->mcast[queue_id].parent_gport;
                    if (parent_gport != cpu_l2_gport) {
                        return BCM_E_PARAM;
                    }
                }
            }
        } else {
            soc_dma_cos_ctrl_queue_get(unit, pci_cmc, chan_id, queue_id,
                    &reg_val);
            bit = 1 << (queue_id % 32);
            if (reg_val & bit) {
                /* find the parent gport of this queue if parent gport is not
                 * equal to l0 gport for this channel return error */
                parent_gport = cpu_port_info->mcast[queue_id].parent_gport;
                if (parent_gport != cpu_l2_gport) {
                    return BCM_E_PARAM;
                }
            } else {
                return BCM_E_PARAM;
            }
        }
    }
#endif /* BCM_CMICX_SUPPORT */

    return BCM_E_NONE;
}

/*
 * Function:
 *      _bcm_hx5_cpu_cosq_mapping_default_set
 * Purpose:
 *      Map 16 internal priorities to CPU COS queues using CPU_COS_MAPm
 *      Default cpu_cos_maps should have lower priorities than user created
 *      maps
 * Parameters:
 *      unit - (IN) Unit number.
 *      numq - (IN) number of COS queues (0-7).
 * Returns:
 *      BCM_E_XXX
 */
STATIC int
_bcm_hx5_cpu_cosq_mapping_default_set(int unit, int numq)
{
    int cos = 0, prio = 0, index = 0, i = 0;
    cpu_cos_map_entry_t cpu_cos_map_entry;

    /* Nothing to do on devices with no CPU_COS_MAP memory */
    if (!SOC_MEM_IS_VALID(unit, CPU_COS_MAPm)) {
        return BCM_E_NONE;
    }

    /* Map internal priorities 0 ~ 7 to appropriate CPU CoS queue */
    sal_memset(&cpu_cos_map_entry, 0, sizeof(cpu_cos_map_entry_t));
    soc_mem_field32_set(unit, CPU_COS_MAPm, &cpu_cos_map_entry, VALIDf, 3);
    soc_mem_field32_set(unit, CPU_COS_MAPm, &cpu_cos_map_entry,
                        INT_PRI_MASKf, _BCM_HX5_INT_PRI_0_7_MASK);

   index = (soc_mem_index_count(unit, CPU_COS_MAPm) - _BCM_HX5_CPU_COS_MAPS_RSVD);
    for (cos = 0; cos < numq; cos++) {
        for (i = 8 / numq + (cos < 8 % numq ? 1 : 0); i > 0; i--) {
            soc_mem_field32_set(unit, CPU_COS_MAPm, &cpu_cos_map_entry,
                                INT_PRI_KEYf, prio);
            soc_mem_field32_set(unit, CPU_COS_MAPm, &cpu_cos_map_entry, COSf, cos);
            SOC_IF_ERROR_RETURN(WRITE_CPU_COS_MAPm(unit, MEM_BLOCK_ALL, index,
                                                   &cpu_cos_map_entry));
            prio++;
            index++;
        }
    }

    /* Map internal priorities 8 ~ 15 to (numq - 1) CPU CoS queue */
    soc_mem_field32_set(unit, CPU_COS_MAPm, &cpu_cos_map_entry,
                        INT_PRI_KEYf, 0x8);
    soc_mem_field32_set(unit, CPU_COS_MAPm, &cpu_cos_map_entry,
                        INT_PRI_MASKf, _BCM_HX5_INT_PRI_8_15_MASK);
    soc_mem_field32_set(unit, CPU_COS_MAPm, &cpu_cos_map_entry, COSf, numq - 1);
    SOC_IF_ERROR_RETURN(WRITE_CPU_COS_MAPm(unit, MEM_BLOCK_ALL, index,
                                           &cpu_cos_map_entry));

    return BCM_E_NONE;
}

/*
 * Function:
 *    bcm_hx5_wireless_cos_map_update
 * Purpose:
 *     Set the number of classes of service supported
 * Parameters:
 *     unit - (IN) unit number
 *     index - (IN) index of newly added profile 
 * Returns:
 *     BCM_E_XXX
 */
int bcm_hx5_wireless_cos_map_update(int unit, int numq) 
{
    uint32 *cos_map_entries;
    soc_mem_t mem;
    int rv = SOC_E_NONE, cos, prio = 0, index = 0;
    uint32 uc_cos = 0, mc_cos = 0, hg_cos = 0;

    mem = PORT_COS_MAPm;
    cos_map_entries = soc_cm_salloc(unit, (sizeof(port_cos_map_entry_t) * 16),
                                    "HX5 Cos map update");
    for (index = 0; index < 4; index++) {
        prio = 0;
        sal_memset(cos_map_entries, 0, (sizeof(port_cos_map_entry_t) * 16));
        rv = soc_mem_read_range(unit, mem, MEM_BLOCK_ANY, index * _HX5_NUM_COS_MAP_ENTRY,
                (index * _HX5_NUM_COS_MAP_ENTRY) + (_HX5_NUM_COS_MAP_ENTRY - 1),
                (void *)cos_map_entries);
        if (BCM_FAILURE(rv)) {
            soc_cm_sfree(unit, cos_map_entries);
            return rv;
        }
        for (cos = 0; cos < numq; cos++) {
            uc_cos = mc_cos = hg_cos = 0;
            uc_cos = soc_mem_field32_get(unit, mem, &cos_map_entries[prio], UC_COS1f);
            mc_cos = soc_mem_field32_get(unit, mem, &cos_map_entries[prio], MC_COS1f);
            hg_cos = soc_mem_field32_get(unit, mem, &cos_map_entries[prio], HG_COSf);
            soc_mem_field32_set(unit, mem, &cos_map_entries[prio],  UC_COS1f, uc_cos + _BCM_HX5_COS_DEFAULT);
            soc_mem_field32_set(unit, mem, &cos_map_entries[prio],  MC_COS1f, mc_cos + _BCM_HX5_COS_DEFAULT);
            if(!hg_cos || (hg_cos < _BCM_HX5_COS_DEFAULT)) {
               soc_mem_field32_set(unit, mem, &cos_map_entries[prio], HG_COSf, hg_cos + _HX5_NUM_COS_MAP_ENTRY);
            }
            prio++;
        }

        for (prio = 8; prio < 16; prio++) {
            soc_mem_field32_set(unit, mem, &cos_map_entries[prio], UC_COS1f,
                    uc_cos + _BCM_HX5_COS_DEFAULT); 
            soc_mem_field32_set(unit, mem, &cos_map_entries[prio], MC_COS1f,
                    mc_cos + _BCM_HX5_COS_DEFAULT); 
            if(!hg_cos || (hg_cos < _BCM_HX5_COS_DEFAULT)) {
                soc_mem_field32_set(unit, mem, &cos_map_entries[prio], HG_COSf,
                        hg_cos + _HX5_NUM_COS_MAP_ENTRY); 
            }
        }

        rv = soc_mem_write_range(unit, mem, MEM_BLOCK_ANY, (index * _HX5_NUM_COS_MAP_ENTRY) +
                _HX5_WIRELESS_COS_MAP_BASE, (index * _HX5_NUM_COS_MAP_ENTRY) +
                (_HX5_WIRELESS_COS_MAP_BASE + _HX5_NUM_COS_MAP_ENTRY - 1),
                (void *)cos_map_entries);

    }
    soc_cm_sfree(unit, cos_map_entries);
    return rv;

}

/*
 * Function:
 *     bcm_hx5_cosq_config_set
 * Purpose:
 *     Set the number of classes of service supported
 * Parameters:
 *     unit - (IN) unit number
 *     numq - (IN) number of classes of service
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_config_set(int unit, int numq)
{
    port_cos_map_entry_t cos_map_entries[16];
    void *entries[1];
    uint32 index;
    int count = 0;
    bcm_port_t port;
    int cos, prio = 0, ref_count = -1;
    uint32 i;
    soc_mem_t mem = PORT_COS_MAPm;

    if (numq < 1 || numq > _BCM_HX5_COS_DEFAULT) {
        return BCM_E_PARAM;
    }

    index = 0;
    while (index < (soc_mem_index_count(unit, mem) / 2)) {
        BCM_IF_ERROR_RETURN(soc_profile_mem_ref_count_get(unit,
                                      _bcm_hx5_cos_map_profile[unit],
                                      index, &ref_count));
        if (ref_count > 0) {
            while (ref_count) {
                if (!soc_profile_mem_delete(unit,
                            _bcm_hx5_cos_map_profile[unit], index)) {
                    ref_count -= 1;
                }
            }
        }
        index += 16;
    }

    /*
     * Distribute first 8 internal priority levels into the specified number
     * of cosq, map remaining internal priority levels to highest priority
     * cosq
     */
    sal_memset(cos_map_entries, 0, sizeof(cos_map_entries));
    entries[0] = &cos_map_entries;

    for (cos = 0; cos < numq; cos++) {
        for (i = 8 / numq + (cos < 8 % numq ? 1 : 0); i > 0; i--) {
            soc_mem_field32_set(unit, mem, &cos_map_entries[prio],
                                UC_COS1f, cos);
            soc_mem_field32_set(unit, mem, &cos_map_entries[prio],
                                MC_COS1f, cos);
            soc_mem_field32_set(unit, mem, &cos_map_entries[prio],
                                HG_COSf, _HX5_NUM_COS_MAP_ENTRY + cos);
            prio++;
        }
    }
    for (prio = 8; prio < 16; prio++) {
         soc_mem_field32_set(unit, mem, &cos_map_entries[prio], UC_COS1f,
                                numq - 1);
         soc_mem_field32_set(unit, mem, &cos_map_entries[prio], MC_COS1f,
                                numq - 1);
         soc_mem_field32_set(unit, mem, &cos_map_entries[prio], HG_COSf,
                                _HX5_NUM_COS_MAP_ENTRY + (numq - 1));
    }

    /* Map internal priority levels to CPU CoS queues */
    BCM_IF_ERROR_RETURN(_bcm_hx5_cpu_cosq_mapping_default_set(unit, numq));

    SOC_IF_ERROR_RETURN
        (soc_profile_mem_add(unit, _bcm_hx5_cos_map_profile[unit], entries, 16,
                             &index));
    BCM_IF_ERROR_RETURN(bcm_hx5_wireless_cos_map_update(unit, numq));
    PBMP_ALL_ITER(unit, port) {
        SOC_IF_ERROR_RETURN
            (soc_mem_field32_modify(unit, COS_MAP_SELm, port, SELECTf,
                                    index / 16));
        count++;
    }
    if (SOC_INFO(unit).cpu_hg_index != -1) {
        SOC_IF_ERROR_RETURN
            (soc_mem_field32_modify(unit, COS_MAP_SELm,
                                    SOC_INFO(unit).cpu_hg_index, SELECTf,
                                    index / 16));
        count++;
    }
    for (i = 1; i < count; i++) {
        soc_profile_mem_reference(unit, _bcm_hx5_cos_map_profile[unit], index, 0);
    }

    _BCM_HX5_NUM_COS(unit) = numq;

    return BCM_E_NONE;
}

int bcm_hx5_hgcos_mode_get(int unit, bcm_port_t port, int *mode)
{
    uint32 regval = 0;
    SOC_IF_ERROR_RETURN(READ_UC_HG_QUEUE_MODEr(unit, port, &regval));
    *mode = soc_reg_field_get(unit, UC_HG_QUEUE_MODEr, regval, QUEUE_MODEf);

   return BCM_E_NONE;
}


/*
 * Function:
 *     bcm_hx5_cosq_config_get
 * Purpose:
 *     Get the number of Classes of Service
 * Parameters:
 *     unit - (IN) unit number
 *     numq - (OUT) Number of Classes of Service
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_config_get(int unit, int *numq)
{
    if (numq != NULL) {
        *numq = _BCM_HX5_NUM_COS(unit);
    }

    return BCM_E_NONE;

}


/*
 * CMIC CMC Channel to Queue mapping.
 */
    STATIC int
_bcm_hx5_cosq_rx_queue_channel_set(int unit, bcm_cos_queue_t parent_cos,
        bcm_cos_queue_t queue_id, int enable)
{
#if defined(BCM_CMICX_SUPPORT)
    if soc_feature(unit, soc_feature_cmicx) {
        int pci_cmc = SOC_PCI_CMC(unit);
        int chan_id = -1;
        int start_chan_id = 0;
        uint32 chan_off;
        uint32 reg_addr, reg_val;
        uint32 ix;
        uint32 max_rx_channels = 0;

        if ((parent_cos >= 0) && (parent_cos <= 6)) {
            chan_id = parent_cos + 1;
        } else {
            return BCM_E_PARAM;
        }

        if (!SHR_BITGET(CPU_ARM_QUEUE_BITMAP(unit, pci_cmc), queue_id)) {
            return BCM_E_PARAM;
        }

        soc_dma_max_rx_channels_get(unit, &max_rx_channels);

        for (ix = start_chan_id; ix < (start_chan_id + max_rx_channels); ix++) {
            chan_off = ix % max_rx_channels;
            soc_dma_cos_ctrl_reg_addr_get(unit, pci_cmc, chan_off, queue_id,
                    &reg_addr);
            reg_val = soc_pci_read(unit, reg_addr);

            if (enable == 1) {
                if (ix == (uint32)chan_id) {
                    reg_val |= ((uint32)1 << (queue_id % 32));
                } else {
                    /* Clear all other channels */
                    reg_val &= ~((uint32)1 << (queue_id % 32));
                }
            } else {
                if (ix == (uint32)chan_id) {
                    reg_val &= ~((uint32)1 << (queue_id % 32));
                }
            }
            /* Incoporate the reserved queues (if any on this device)
             * into the CMIC programming,  */
            reg_val |=
                CPU_ARM_RSVD_QUEUE_BITMAP(unit, pci_cmc)[queue_id / 32];
            soc_pci_write(unit, reg_addr, reg_val);
        }
    }
#endif /* BCM_CMICX_SUPPORT */

    return BCM_E_NONE;
}

int
bcm_hx5_cosq_detach(int unit, int software_state_only)
{
    _bcm_hx5_cosq_cleanup(unit);
    return BCM_E_NONE;
}




/*
 * Function:
 *     _bcm_hx5_cosq_cpu_parent_set
 * Purpose:
 *     Set Parent(L2) for a given L3 queue of the CPU port.
 *     Only child @ L3 level is supported. Because only L3 level queues can be
 *     attached to different parent (L2.0-L2.9) of the CPU port.
 * Parameters:
 *     unit         - (IN) unit number
 *     child_index  - (IN) Child node index
 *     child_level  - (IN) Child node level
 *     parent_index - (IN) Parent node index
 * Returns:
 *     BCM_E_XXX
 */
    STATIC int
_bcm_hx5_cosq_cpu_parent_set(int unit, int child_index, int child_level,
        int parent_index)
{
    soc_reg_t reg =  Q_SCHED_CPU_L3_MC_QUEUE_L2_MAPPINGr;
    uint32 rval = 0;

    if (child_level != SOC_HX5_NODE_LVL_L3) {
        return BCM_E_PARAM;
    }

    /* Set the L3 queue's parent to the given L2 node */
    SOC_IF_ERROR_RETURN
        (soc_reg32_get(unit, reg, 0, child_index, &rval));
    soc_reg_field_set(unit, reg, &rval, SELECTf, parent_index);
    SOC_IF_ERROR_RETURN
        (soc_reg32_set(unit, reg, 0, child_index, rval));

    return BCM_E_NONE;
}


/*
 * Function:
 *     _bcm_hx5_cosq_cpu_parent_get
 * Purpose:
 *     Get Parent(L2) for a given L3 queue of the CPU port.
 *     Only child @ L3 level is supported. Because only L3 level queues can be
 *     attached to different parent (L2.0-L2.9) of the CPU port.
 * Parameters:
 *     unit         - (IN)  unit number
 *     child_index  - (IN)  Child node index
 *     child_level  - (IN)  Child node level
 *     parent_index - (OUT) Parent node index
 * Returns:
 *     BCM_E_XXX
 */
    STATIC int
_bcm_hx5_cosq_cpu_parent_get(int unit, int child_index, int child_level,
        int *parent_index)
{
    soc_reg_t reg = Q_SCHED_CPU_L3_MC_QUEUE_L2_MAPPINGr;
    uint32 rval = 0;

    if (child_level != SOC_HX5_NODE_LVL_L3) {
        return BCM_E_PARAM;
    }

    /* Set the L3 queue's parent to the given L2 node */
    SOC_IF_ERROR_RETURN
        (soc_reg32_get(unit, reg, 0, child_index, &rval));
    *parent_index = soc_reg_field_get(unit, reg, rval, SELECTf);

    return BCM_E_NONE;
}


/*
 * Function:
 *     _bcm_hx5_cosq_cpu_gport_attach
 * Purpose:
 *     Attach any of the L3 MC Queue to one of the L2 nodes
 * Parameters:
 *     unit         - (IN) unit number
 *     input_gport  - (IN) GPORT id, that will attach to parent gport
 *     parent_gport - (IN) Parent Gport to which current gport will be attached
 *     cosq         - (IN) COS queue to attach to (-1 for first available cosq)
 * Returns:
 *     BCM_E_XXX
 */
STATIC int
_bcm_hx5_cosq_cpu_gport_attach(int unit, bcm_gport_t input_gport,
        bcm_gport_t parent_gport, bcm_cos_queue_t cosq)
{

    _bcm_hx5_cosq_node_t *input_node = NULL;
    _bcm_hx5_cosq_node_t *parent_node = NULL;
    bcm_port_t input_port, parent_port;
    int parent_cos = 0;

    LOG_INFO(BSL_LS_BCM_COSQ,
            (BSL_META_U(unit,
                        "bcm_hx5_cosq_gport_attach: unit=%d parent_gport=0x%x "
                        "input_gport=0x%x cosq=%d\n"), unit, parent_gport,
             input_gport, cosq));

    if (_BCM_HX5_MMU_INFO(unit)->gport_tree_created == FALSE) {
        if (((BCM_GPORT_IS_MCAST_QUEUE_GROUP(input_gport)) &&
                    (!BCM_GPORT_IS_SCHEDULER(parent_gport))) ||
                (!(BCM_GPORT_IS_MCAST_QUEUE_GROUP(input_gport)) &&
                 (!BCM_GPORT_IS_SCHEDULER(input_gport)))) {
            return BCM_E_PARAM;
        }
    } else if ((!BCM_GPORT_IS_SCHEDULER(parent_gport)) ||
            (!BCM_GPORT_IS_MCAST_QUEUE_GROUP(input_gport))) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_node_get(unit, input_gport, NULL, &input_port, NULL,
                                &input_node));

    if (!input_node) {
        return BCM_E_PARAM;
    }
    if (input_port < 0) {
        return BCM_E_PORT;
    }

    if (BCM_GPORT_IS_SCHEDULER(parent_gport)) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_node_get(unit, parent_gport, NULL, &parent_port, NULL,
                                    &parent_node));
    } else {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, parent_gport, &parent_port));
        parent_node = NULL;
    }

    if (!IS_CPU_PORT(unit, parent_port)) {
        return BCM_E_PARAM;
    }

    /* Return BCM_E_EXISTS when queue to be attached is
     * already attached to the given gport
     */
    if ((_BCM_HX5_MMU_INFO(unit)->gport_tree_created == TRUE) &&
            (input_node->parent_gport == parent_gport)) {
        return BCM_E_EXISTS;
    }


    if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(input_gport)) {
        input_node->hw_index = SOC_HX5_CPU_MCQ_BASE + cosq;
    } else {
        input_node->level = HX5_CPU_SCHED_LEVEL_GET(unit, cosq);
        switch(input_node->level) {
            case SOC_HX5_NODE_LVL_L0:
                input_node->hw_index = _HX5_CPU_LO_NODE_BASE;
                break;
            case SOC_HX5_NODE_LVL_L1:
                input_node->hw_index = _HX5_CPU_L1_NODE_BASE;
                break;
            case SOC_HX5_NODE_LVL_L2:
                input_node->hw_index = _HX5_CPU_L2_NODE_BASE + (cosq - (_HX5_CPU_NUML0_NODES + _HX5_CPU_NUML1_NODES));
                break;
            default:
                return BCM_E_PARAM;
        }
    }

    if (BCM_GPORT_IS_SCHEDULER(parent_gport)) {
        if(parent_node->level == SOC_HX5_NODE_LVL_L2) {
            parent_cos = parent_node->hw_index - _HX5_CPU_L2_NODE_BASE;
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_cpu_parent_set(unit, cosq, SOC_HX5_NODE_LVL_L3,
                                              parent_cos));
            /*
             * L2.0 is associated with CMC0 CH1(Rx)
             * L2.1 is associated with CMC0 CH2(Rx)
             * L2.2 is associated with CMC0 CH3(Rx)
             * L2.3 is associated with CMC0 CH4(Rx)
             * L2.4 is associated with CMC0 CH5(Rx)
             * L2.5 is associated with CMC0 CH6(Rx)
             * L2.6 is associated with CMC0 CH7(Rx)
             */
            if ((parent_cos >= 0) && (parent_cos < 7)) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_rx_queue_channel_set(unit, parent_cos, cosq, 1));
            }
        }
    }

    if (BCM_GPORT_IS_SCHEDULER(input_gport)) {
        if(input_node->level == SOC_HX5_NODE_LVL_L0) {
            BCM_IF_ERROR_RETURN
                (bcm_esw_port_gport_get(unit, input_port,
                                        &(input_node->parent_gport)));
        } else {
            input_node->parent_gport = parent_gport;
        }
    }else if(BCM_GPORT_IS_MCAST_QUEUE_GROUP(input_gport)){
        input_node->parent_gport = parent_gport;
    }


    return BCM_E_NONE;
}



/*
 * Function:
 *     _bcm_hx5_cosq_port_cos_resolve
 * Purpose:
 *     Find UC/MC queue gport for a given logical port
 *     and cos value.
 * Parameters:
 *     unit      - (IN) unit number
 *     port      - (IN) logical port
 *     cos       - (IN) cos value
 *     style     - (IN) index style
 *                 (_BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE or
 *                  _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE)
 *     gport     - (OUT) Queue gport
 * Returns:
 *     BCM_E_XXX
 */
int
_bcm_hx5_cosq_port_cos_resolve(int unit, bcm_port_t port, bcm_cos_t cos,
                              _bcm_hx5_cosq_index_style_t style,
                              bcm_gport_t *gport)
{
    _bcm_hx5_cosq_port_info_t *port_info = NULL;
    _bcm_hx5_cosq_st_port_info_t *stport_info = NULL;
    _bcm_hx5_cosq_cpu_port_info_t *cpu_port_info = NULL;
    int phy_port, mmu_port, port_index;

    soc_info_t *si = &SOC_INFO(unit);

    if (gport == NULL) {
        return BCM_E_PARAM;
    }

    if (_bcm_hx5_cosq_port_info[unit] == NULL) {
        return BCM_E_INIT;
    }

    if (_bcm_hx5_cosq_st_port_info[unit] == NULL) {
        return BCM_E_INIT;
    }
    if (_bcm_hx5_cosq_cpu_port_info[unit] == NULL) {
        return BCM_E_INIT;
    }

    if ((IS_CPU_PORT(unit, port)) &&
        (style == _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE)) {
        return BCM_E_PARAM;
    }

    if (cos < 0) {
        return BCM_E_PARAM;
    }

    if (!SOC_PORT_VALID(unit, port)) {
        return BCM_E_PORT;
    }

    if (_BCM_HX5_MMU_INFO(unit)->gport_tree_created != TRUE) {
        return BCM_E_INTERNAL;
    }

     phy_port = si->port_l2p_mapping[port];
     mmu_port = si->port_p2m_mapping[phy_port];
     _HX5_PORT_INDEX_GET(unit, mmu_port, port_index);


     if (IS_CPU_PORT(unit, port)) {
         cpu_port_info = _bcm_hx5_cosq_cpu_port_info[unit];
         if (style == _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE) {
             if (cos >= SOC_HX5_NUM_CPU_QUEUES) {
                 return BCM_E_PARAM;
             }
             *gport = cpu_port_info->mcast[cos].gport;
         } else {
             return BCM_E_INTERNAL;
         }
     } else if(_HX5_IS_ST_PORT(unit, mmu_port)){
         stport_info = &_bcm_hx5_cosq_st_port_info[unit][port_index];
         if (style == _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE) {
             if (cos >= SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT) {
                 return BCM_E_PARAM;
             }
             *gport = stport_info->ucast[cos].gport;
         } else if (style == _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE) {
             if (cos >= SOC_HX5_NUM_MCAST_QUEUE_PER_ST_PORT) {
                 return BCM_E_PARAM;
             }
             *gport = stport_info->mcast[cos].gport;
         } else {
             return BCM_E_INTERNAL;
         }
     } else {
         port_info = &_bcm_hx5_cosq_port_info[unit][port_index];
         if (style == _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE) {
             if (cos >= SOC_HX5_NUM_UCAST_QUEUE_PER_PORT) {
                 return BCM_E_PARAM;
             }
             *gport = port_info->ucast[cos].gport;
         } else if (style == _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE) {
             if (cos >= SOC_HX5_NUM_MCAST_QUEUE_PER_PORT) {
                 return BCM_E_PARAM;
             }
             *gport = port_info->mcast[cos].gport;
         } else {
             return BCM_E_INTERNAL;
         }
     }

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_gport_attach
 * Purpose:
 *     Attach sched_port to the specified index (cosq) of input_port
 * Parameters:
 *     unit          - (IN) unit number
 *     input_port    - (IN) GPORT id, that will attach to parent gport
 *     parent_gport  - (IN) Parent Gport to which current gport will be attached
 *     cosq          - (IN) COS queue to attach to (-1 for first available cosq)
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_gport_attach(int unit, bcm_gport_t input_gport,
                          bcm_gport_t parent_gport, bcm_cos_queue_t cosq)
{
    _bcm_hx5_cosq_node_t *input_node = NULL;
    _bcm_hx5_cosq_node_t *parent_node = NULL;
    bcm_port_t input_port, parent_port;
    int phy_port, mmu_port;
    soc_info_t *si = &SOC_INFO(unit);

    LOG_INFO(BSL_LS_BCM_COSQ,
        (BSL_META_U(unit,
                    "bcm_hx5_cosq_gport_attach: unit=%d parent_gport=0x%x "
                    "input_gport=0x%x cosq=%d\n"), unit, parent_gport,
                    input_gport, cosq));

    if (!(BCM_GPORT_IS_SCHEDULER(input_gport) ||
        BCM_GPORT_IS_UCAST_QUEUE_GROUP(input_gport) ||
        BCM_GPORT_IS_MCAST_QUEUE_GROUP(input_gport))) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_node_get(unit, input_gport, NULL, &input_port, NULL,
                               &input_node));

    if (!input_node) {
        return BCM_E_PARAM;
    }
    if (input_port < 0) {
        return BCM_E_PORT;
    }

    if (IS_CPU_PORT(unit, input_port)) {
        return _bcm_hx5_cosq_cpu_gport_attach(unit, input_gport, parent_gport,
                cosq);
    } else if (_BCM_HX5_MMU_INFO(unit)->gport_tree_created == TRUE) {
        return BCM_E_PARAM;
    }

    phy_port = si->port_l2p_mapping[input_port];
    mmu_port = si->port_p2m_mapping[phy_port];

    if (BCM_GPORT_IS_SCHEDULER(parent_gport)) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_node_get(unit, parent_gport, NULL, &parent_port, NULL,
                                   &parent_node));
    } else {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, parent_gport, &parent_port));
            parent_node = NULL;
    }

    if (input_port != parent_port) {
        return BCM_E_PARAM;
    }

    phy_port = si->port_l2p_mapping[parent_port];
    mmu_port = si->port_p2m_mapping[phy_port];

    if(_HX5_IS_ST_PORT(unit, mmu_port)) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(input_gport)) {
            input_node->hw_index = (mmu_port * SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT) + cosq;
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(input_gport)) {
            input_node->hw_index = (mmu_port * SOC_HX5_NUM_MCAST_QUEUE_PER_ST_PORT) +  cosq;
        } else {
            input_node->level = HX5_ST_SCHED_LEVEL_GET(unit, cosq);
            switch(input_node->level) {
                case SOC_HX5_NODE_LVL_L0:
                     input_node->hw_index = (mmu_port * _HX5_ST_NUML0_NODES) + cosq;
                     break;
                case SOC_HX5_NODE_LVL_L1:
                     input_node->hw_index = (mmu_port * _HX5_ST_NUML1_NODES) + (cosq - _HX5_ST_NUML0_NODES);
                     break;
                case SOC_HX5_NODE_LVL_L2:
                     input_node->hw_index = (mmu_port * _HX5_ST_NUML2_NODES) +
                                             (cosq - (_HX5_ST_NUML1_NODES + _HX5_ST_NUML0_NODES));
                     break;
                default:
                     return BCM_E_PARAM;
            }
        }
    }else {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(input_gport)) {
            input_node->hw_index = _HX5_BASE_L3QUEUE + ((mmu_port - _BCM_HX5_NUM_ST_PORTS)  *
                                                       SOC_HX5_NUM_UCAST_QUEUE_PER_PORT) + cosq;
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(input_gport)) {
            input_node->hw_index = _HX5_BASE_L3QUEUE + ((mmu_port - _BCM_HX5_NUM_ST_PORTS)  *
                                                       SOC_HX5_NUM_MCAST_QUEUE_PER_PORT) +  cosq;
        } else {
            input_node->level = HX5_SCHED_LEVEL_GET(unit, cosq);
            switch(input_node->level) {
                case SOC_HX5_NODE_LVL_L0:
                     input_node->hw_index = _HX5_BASE_L0QUEUE + ((mmu_port - _BCM_HX5_NUM_ST_PORTS)  *
                                                                 _HX5_NUML0_NODES) + cosq;
                     break;
                case SOC_HX5_NODE_LVL_L1:
                     input_node->hw_index = _HX5_BASE_L1QUEUE + ((mmu_port - _BCM_HX5_NUM_ST_PORTS) *
                                             _HX5_NUML1_NODES) + (cosq - _HX5_NUML0_NODES);
                     break;
                case SOC_HX5_NODE_LVL_L2:
                     input_node->hw_index = _HX5_BASE_L2QUEUE + ((mmu_port - _BCM_HX5_NUM_ST_PORTS)  *
                                            _HX5_NUML2_NODES) + (cosq - (_HX5_NUML1_NODES + _HX5_NUML0_NODES));
                     break;
                default:
                     return BCM_E_PARAM;
            }
        }
    }

    if (BCM_GPORT_IS_SCHEDULER(input_gport)) {
        if(input_node->level == SOC_HX5_NODE_LVL_L0) {
            BCM_IF_ERROR_RETURN
                (bcm_esw_port_gport_get(unit, input_port,
                                        &(input_node->parent_gport)));
        } else {
            input_node->parent_gport = parent_gport;
        }
    } else if ((BCM_GPORT_IS_UCAST_QUEUE_GROUP(input_gport)) ||
                (BCM_GPORT_IS_MCAST_QUEUE_GROUP(input_gport))) {
        input_node->parent_gport = parent_gport;
    }

    return BCM_E_NONE;
}


/*
 * Function:
 *     _bcm_hx5_cosq_cpu_gport_detach
 * Purpose:
 *     Detach any of the L3 MC Queue from its parent L2 nodes.
 *     Post detach, L3 MC queue is attached to Parent L2.9 node
 * Parameters:
 *     unit        - (IN) unit number
 *     input_port  - (IN) scheduler GPORT identifier
 *     parent_port - (IN) GPORT to detach from
 *     cosq        - (IN) COS queue to detach from
 * Returns:
 *     BCM_E_XXX
 */
    STATIC int
_bcm_hx5_cosq_cpu_gport_detach(int unit, bcm_gport_t input_gport,
        bcm_gport_t parent_gport, bcm_cos_queue_t cosq)
{
    bcm_port_t parent_port, input_port;
    _bcm_hx5_cosq_node_t *input_node = NULL, *parent_node = NULL;
    int input_cos = 0, parent_cos = 0, config_cos = 0;
    int index = 0;

    /* Post Default tree created, expected Input
     * Gport is of MC Gport
     * and expected Parent Gport is new L0
     * Parent
     */
    if ((!BCM_GPORT_IS_SCHEDULER(parent_gport)) ||
            (!BCM_GPORT_IS_MCAST_QUEUE_GROUP(input_gport))) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_node_get(unit, input_gport, NULL, &input_port, NULL,
                                &input_node));
    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_node_get(unit, parent_gport, NULL, &parent_port, NULL,
                                &parent_node));

    if (!IS_CPU_PORT(unit, parent_port)) {
        return BCM_E_PARAM;
    }

    /* Return BCM_E_PARAM when queue to be detached is
       not attached to the given gport */
    if (input_node->parent_gport != parent_gport) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_SCHEDULER(parent_gport)) {
        switch(parent_node->level) {
            case SOC_HX5_NODE_LVL_L0:
                parent_cos =  parent_node->hw_index -  _HX5_CPU_LO_NODE_BASE;
                break;
            case SOC_HX5_NODE_LVL_L1:
                parent_cos =  parent_node->hw_index -  _HX5_CPU_L1_NODE_BASE;
                break;
            case SOC_HX5_NODE_LVL_L2:
                parent_cos =  parent_node->hw_index -  _HX5_CPU_L2_NODE_BASE;
                break;
            default:
                return BCM_E_PARAM;
        }
    }

    input_cos = cosq % SOC_HX5_NUM_CPU_QUEUES;

    if(parent_node->level == SOC_HX5_NODE_LVL_L2) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_cpu_parent_get(unit, input_cos, SOC_HX5_NODE_LVL_L3,
                                          &config_cos));
        if (config_cos != parent_cos) {
            /* Error when detaching from wrong Parent (L0 level) */
            return BCM_E_PARAM;
        }

        /*
         * L2.0 is associated with CMC0 CH1(Rx)
         * L2.1 is associated with CMC0 CH2(Rx)
         * L2.2 is associated with CMC0 CH3(Rx)
         * L2.3 is associated with CMC0 CH4(Rx)
         * L2.4 is associated with CMC0 CH5(Rx)
         * L2.5 is associated with CMC0 CH6(Rx)
         * L2.6 is associated with CMC0 CH7(Rx)
         */
        if ((parent_cos >= 0) && (parent_cos < 7)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_rx_queue_channel_set(unit, parent_cos, input_cos,
                                                    0));
        }

        /* Reset parent to L0.9 */
        index = _HX5_CPU_NUML2_NODES;
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_cpu_parent_set(unit, input_cos, SOC_HX5_NODE_LVL_L3, index - 1));
        index += 2;
        input_node->parent_gport = _BCM_HX5_MMU_INFO(unit)->_bcm_hx5_cpu_port_info->
            sched[index - 1].gport;
    }
    return BCM_E_NONE;
}





/*
 * Function:
 *     bcm_hx5_cosq_gport_detach
 * Purpose:
 *     Detach sched_port from the specified index (cosq) of input_port
 * Parameters:
 *     unit        - (IN) unit number
 *     input_port  - (IN) scheduler GPORT identifier
 *     parent_port - (IN) GPORT to detach from
 *     cosq        - (IN) COS queue to detach from
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_gport_detach(int unit, bcm_gport_t input_gport,
                          bcm_gport_t parent_gport, bcm_cos_queue_t cosq)
{
    _bcm_hx5_cosq_node_t *input_node = NULL, *parent_node = NULL;
    bcm_port_t input_port, parent_port;
    int input_hw_index = -1, parent_hw_index = -1;
    int num_uc, num_mc, num_sc;
    int phy_port, mmu_port;

    soc_info_t *si = &SOC_INFO(unit);
    LOG_INFO(BSL_LS_BCM_COSQ,
        (BSL_META_U(unit,
                    "bcm_hx5_cosq_gport_detach: unit=%d input_gport=0x%x "
                    "parent_gport=0x%x cosq=%d\n"),
                    unit, input_gport, parent_gport, cosq));

    if (!(BCM_GPORT_IS_SCHEDULER(input_gport) ||
        BCM_GPORT_IS_UCAST_QUEUE_GROUP(input_gport) ||
        BCM_GPORT_IS_MCAST_QUEUE_GROUP(input_gport))) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_node_get(unit, input_gport, NULL, &input_port, NULL,
                                &input_node));

    if (!input_node) {
        return BCM_E_PARAM;
    }

    if (_BCM_HX5_MMU_INFO(unit)->gport_tree_created == TRUE) {
        if (IS_CPU_PORT(unit, input_port)) {
            return _bcm_hx5_cosq_cpu_gport_detach(unit, input_gport, parent_gport, cosq);
        } else {
            return BCM_E_PARAM;
        }
    }

    phy_port = si->port_l2p_mapping[input_port];
    mmu_port = si->port_p2m_mapping[phy_port];

    if(_HX5_IS_ST_PORT(unit, mmu_port)) {
        num_uc = SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT;
        num_mc = SOC_HX5_NUM_MCAST_QUEUE_PER_ST_PORT;
        num_sc = SOC_HX5_NUM_SCHEDULER_PER_ST_PORT;
    }else {
        num_uc = SOC_HX5_NUM_UCAST_QUEUE_PER_PORT;
        num_mc = SOC_HX5_NUM_MCAST_QUEUE_PER_PORT;
        num_sc = SOC_HX5_NUM_SCHEDULER_PER_PORT;
    }

    if (BCM_GPORT_IS_SCHEDULER(parent_gport)) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_node_get(unit, parent_gport, NULL, &parent_port, NULL,
                                    &parent_node));
    } else {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, parent_gport, &parent_port));
            parent_node = NULL;
    }

    if (input_port != parent_port) {
        return BCM_E_PARAM;
    }

    /* HX5 scheduler heirarchy is fixed. Hence check for wrong config. */
    if (parent_node) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(input_gport)) {
            input_hw_index = input_node->hw_index % num_uc;
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(input_gport)) {
            input_hw_index = input_node->hw_index % num_mc;
        } else {
            input_hw_index = input_node->hw_index % num_sc;
        }

        if (parent_node->level == SOC_HX5_NODE_LVL_L2) {
            parent_hw_index = parent_node->hw_index % num_sc;

            if (input_hw_index != parent_hw_index) {
                return BCM_E_PARAM;
            }
        }
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_gport_attach_get
 * Purpose:
 *     Get attached status of a scheduler port
 * Parameters:
 *     unit       - (IN) unit number
 *     sched_port - (IN) scheduler GPORT identifier
 *     input_port - (OUT) GPORT to attach to
 *     cosq       - (OUT) COS queue to attached to
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_gport_attach_get(int unit, bcm_gport_t sched_gport,
        bcm_gport_t *input_gport, bcm_cos_queue_t *cosq)
{
    _bcm_hx5_cosq_node_t *node = NULL;
    bcm_port_t local_port = -1;
    int phy_port, mmu_port;
    int num_uc, num_mc;

    soc_info_t *si = &SOC_INFO(unit);

    if (!(BCM_GPORT_IS_SET(sched_gport) ||
                BCM_GPORT_IS_SCHEDULER(sched_gport) ||
                BCM_GPORT_IS_UCAST_QUEUE_GROUP(sched_gport) ||
                BCM_GPORT_IS_MCAST_QUEUE_GROUP(sched_gport))) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_node_get(unit, sched_gport, NULL, &local_port, NULL,
                                &node));

    if (node == NULL) {
        return BCM_E_PARAM;
    }

    if (local_port < 0) {
        return BCM_E_PARAM;
    }

    phy_port = si->port_l2p_mapping[local_port];
    mmu_port = si->port_p2m_mapping[phy_port];

    if(IS_CPU_PORT(unit, local_port)){
        num_uc = 0;
        num_mc = SOC_HX5_NUM_CPU_QUEUES;
    }else {
        if(_HX5_IS_ST_PORT(unit, mmu_port)) {
            num_uc = SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT;
            num_mc = SOC_HX5_NUM_MCAST_QUEUE_PER_ST_PORT;
        }else {
            num_uc = SOC_HX5_NUM_UCAST_QUEUE_PER_PORT;
            num_mc = SOC_HX5_NUM_MCAST_QUEUE_PER_PORT;
        }
    }


    if (BCM_GPORT_IS_SCHEDULER(sched_gport)) {
        switch(node->level) {
            case SOC_HX5_NODE_LVL_L0:
                if(IS_CPU_PORT(unit, local_port)){
                    *cosq = node->hw_index - _HX5_CPU_LO_NODE_BASE;
                } else if(_HX5_IS_ST_PORT(unit, mmu_port)){
                    *cosq = node->hw_index - (mmu_port * _HX5_ST_NUML0_NODES);
                } else {
                    *cosq = node->hw_index - (_HX5_BASE_L0QUEUE + ((mmu_port - _BCM_HX5_NUM_ST_PORTS)  * _HX5_NUML0_NODES));
                }
                break;
            case SOC_HX5_NODE_LVL_L1:
                if(IS_CPU_PORT(unit, local_port)){
                    *cosq = node->hw_index - _HX5_CPU_L1_NODE_BASE;
                } else if(_HX5_IS_ST_PORT(unit, mmu_port)){
                    *cosq = node->hw_index - (mmu_port * _HX5_ST_NUML1_NODES);
                } else {
                    *cosq = node->hw_index - (_HX5_BASE_L1QUEUE + ((mmu_port - _BCM_HX5_NUM_ST_PORTS) * _HX5_NUML1_NODES));
                }
                break;
            case SOC_HX5_NODE_LVL_L2:
                if(IS_CPU_PORT(unit, local_port)){
                    *cosq = node->hw_index - _HX5_CPU_L2_NODE_BASE;
                } else if(_HX5_IS_ST_PORT(unit, mmu_port)){
                    *cosq = node->hw_index - (mmu_port * _HX5_ST_NUML2_NODES);
                } else {
                    *cosq = node->hw_index - (_HX5_BASE_L2QUEUE + ((mmu_port - _BCM_HX5_NUM_ST_PORTS) * _HX5_NUML2_NODES));
                }
                break;
            default:
                return BCM_E_PARAM;
        }
    } else if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(sched_gport)) {
        if(_HX5_IS_ST_PORT(unit, mmu_port)){
            *cosq = node->hw_index - (mmu_port * num_uc);
        } else {
            *cosq = node->hw_index - (_HX5_BASE_L3QUEUE + ((mmu_port - _BCM_HX5_NUM_ST_PORTS)* num_uc));
        }
    } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(sched_gport)) {
        if(IS_CPU_PORT(unit, local_port)){
            *cosq = node->hw_index - _HX5_CPU_L2_NODE_BASE;
        } else if(_HX5_IS_ST_PORT(unit, mmu_port)){
            *cosq = node->hw_index - (mmu_port * num_mc);
        } else {
            *cosq = node->hw_index - (_HX5_BASE_L3QUEUE + ((mmu_port - _BCM_HX5_NUM_ST_PORTS) * num_mc));
        }
    } else {
        return BCM_E_PARAM;
    }

    *input_gport = node->parent_gport;
    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_gport_traverse
 * Purpose:
 *     Walks through the valid COSQ GPORTs and calls
 *     the user supplied callback function for each entry.
 * Parameters:
 *     unit       - (IN) unit number
 *     trav_fn    - (IN) Callback function.
 *     user_data  - (IN) User data to be passed to callback function
 * Returns:
 *     BCM_E_NONE - Success.
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_gport_traverse(int unit, bcm_cosq_gport_traverse_cb cb,
        void *user_data)
{
    _bcm_hx5_cosq_port_info_t *port_info = NULL;
    _bcm_hx5_cosq_st_port_info_t *stport_info = NULL;
    _bcm_hx5_cosq_cpu_port_info_t *cpu_port_info = NULL;
    bcm_module_t my_modid, modid_out;
    bcm_port_t port, port_out, local_port;
    bcm_gport_t gport;
    int id, rv = SOC_E_NONE;
    int phy_port, mmu_port, index;

    soc_info_t *si = &SOC_INFO(unit);

    if (_bcm_hx5_cosq_port_info[unit] == NULL) {
        return BCM_E_INIT;
    }
    if (_bcm_hx5_cosq_st_port_info[unit] == NULL) {
        return BCM_E_INIT;
    }
    if (_bcm_hx5_cosq_cpu_port_info[unit] == NULL) {
        return BCM_E_INIT;
    }

    BCM_IF_ERROR_RETURN(bcm_esw_stk_my_modid_get(unit, &my_modid));
    PBMP_ALL_ITER(unit, port) {
        BCM_IF_ERROR_RETURN
            (_bcm_esw_stk_modmap_map(unit, BCM_STK_MODMAP_GET, my_modid,  port,
                                     &modid_out, &port_out));
        BCM_GPORT_MODPORT_SET(gport, modid_out, port_out);

        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));

        phy_port = si->port_l2p_mapping[local_port];
        mmu_port = si->port_p2m_mapping[phy_port];
        _HX5_PORT_INDEX_GET(unit, mmu_port, index);
        if (IS_CPU_PORT(unit, local_port)) {
            cpu_port_info = _bcm_hx5_cosq_cpu_port_info[unit];
        } else {
            if(_HX5_IS_ST_PORT(unit, mmu_port)) {
                stport_info = &_bcm_hx5_cosq_st_port_info[unit][index];
            }else {
                port_info = &_bcm_hx5_cosq_port_info[unit][index];
            }
        }

        if (!IS_CPU_PORT(unit, local_port) && !_HX5_IS_ST_PORT(unit, mmu_port)) {
            for (id = 0; id < SOC_HX5_NUM_UCAST_QUEUE_PER_PORT; id++) {
                if (port_info->ucast[id].numq == 0) {
                    continue;
                }
                rv = cb(unit, gport, port_info->ucast[id].numq,
                        BCM_COSQ_GPORT_UCAST_QUEUE_GROUP,
                        port_info->ucast[id].gport, user_data);
            }
#ifdef BCM_CB_ABORT_ON_ERR
            if (BCM_FAILURE(rv) && SOC_CB_ABORT_ON_ERR(unit)) {
                return rv;
            }
#else
            rv = BCM_E_NONE;
#endif
        }

        if (!IS_CPU_PORT(unit, local_port) && _HX5_IS_ST_PORT(unit, mmu_port)) {
            for (id = 0; id < SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT; id++) {
                if (stport_info->ucast[id].numq == 0) {
                    continue;
                }
                rv = cb(unit, gport, stport_info->ucast[id].numq,
                        BCM_COSQ_GPORT_UCAST_QUEUE_GROUP,
                        stport_info->ucast[id].gport, user_data);
            }
#ifdef BCM_CB_ABORT_ON_ERR
            if (BCM_FAILURE(rv) && SOC_CB_ABORT_ON_ERR(unit)) {
                return rv;
            }
#else
            rv = BCM_E_NONE;
#endif
        }

        if (IS_CPU_PORT(unit, local_port)) {
            for (id = 0; id < SOC_HX5_NUM_CPU_QUEUES; id++) {
                if (cpu_port_info->mcast[id].numq == 0) {
                    continue;
                }
                rv = cb(unit, gport, cpu_port_info->mcast[id].numq,
                        BCM_COSQ_GPORT_MCAST_QUEUE_GROUP,
                        cpu_port_info->mcast[id].gport, user_data);
#ifdef BCM_CB_ABORT_ON_ERR
                if (BCM_FAILURE(rv) && SOC_CB_ABORT_ON_ERR(unit)) {
                    return rv;
                }
#else
                rv = BCM_E_NONE;
#endif
            }
        } 

        if (!IS_CPU_PORT(unit, local_port) && !_HX5_IS_ST_PORT(unit, mmu_port)) {
            for (id = 0; id < SOC_HX5_NUM_MCAST_QUEUE_PER_PORT; id++) {
                if (port_info->mcast[id].numq == 0) {
                    continue;
                }
                rv = cb(unit, gport, port_info->mcast[id].numq,
                        BCM_COSQ_GPORT_MCAST_QUEUE_GROUP,
                        port_info->mcast[id].gport, user_data);
            }
#ifdef BCM_CB_ABORT_ON_ERR
            if (BCM_FAILURE(rv) && SOC_CB_ABORT_ON_ERR(unit)) {
                return rv;
            }
#else
            rv = BCM_E_NONE;
#endif
        }


        if (!IS_CPU_PORT(unit, local_port) && _HX5_IS_ST_PORT(unit, mmu_port)) {
            for (id = 0; id < SOC_HX5_NUM_MCAST_QUEUE_PER_ST_PORT; id++) {
                if (stport_info->mcast[id].numq == 0) {
                    continue;
                }
                rv = cb(unit, gport, stport_info->mcast[id].numq,
                        BCM_COSQ_GPORT_MCAST_QUEUE_GROUP,
                        stport_info->mcast[id].gport, user_data);
            }
#ifdef BCM_CB_ABORT_ON_ERR
            if (BCM_FAILURE(rv) && SOC_CB_ABORT_ON_ERR(unit)) {
                return rv;
            }
#else
            rv = BCM_E_NONE;
#endif
        }


        if (IS_CPU_PORT(unit, local_port)) {
            for (id = 0; id < SOC_HX5_NUM_SCHEDULER_PER_CPU_PORT; id++) {
                if (cpu_port_info->sched[id].numq == 0) {
                    continue;
                }
                rv = cb(unit, gport, cpu_port_info->sched[id].numq,
                        BCM_COSQ_GPORT_SCHEDULER,
                        cpu_port_info->sched[id].gport, user_data);
#ifdef BCM_CB_ABORT_ON_ERR
                if (BCM_FAILURE(rv) && SOC_CB_ABORT_ON_ERR(unit)) {
                    return rv;
                }
#else
                rv = BCM_E_NONE;
#endif
            }
        }

        if (!IS_CPU_PORT(unit, local_port) && !_HX5_IS_ST_PORT(unit, mmu_port)) {
            for (id = 0; id < SOC_HX5_NUM_SCHEDULER_PER_PORT; id++) {
                if (port_info->sched[id].numq == 0) {
                    continue;
                }
                rv = cb(unit, gport, port_info->sched[id].numq,
                        BCM_COSQ_GPORT_SCHEDULER,
                        port_info->sched[id].gport, user_data);
            }
#ifdef BCM_CB_ABORT_ON_ERR
            if (BCM_FAILURE(rv) && SOC_CB_ABORT_ON_ERR(unit)) {
                return rv;
            }
#else
            rv = BCM_E_NONE;
#endif
        }


        if (!IS_CPU_PORT(unit, local_port) && _HX5_IS_ST_PORT(unit, mmu_port)) {
            for (id = 0; id < SOC_HX5_NUM_SCHEDULER_PER_ST_PORT; id++) {
                if (stport_info->sched[id].numq == 0) {
                    continue;
                }
                rv = cb(unit, gport, stport_info->sched[id].numq,
                        BCM_COSQ_GPORT_SCHEDULER,
                        stport_info->sched[id].gport, user_data);
            }
#ifdef BCM_CB_ABORT_ON_ERR
            if (BCM_FAILURE(rv) && SOC_CB_ABORT_ON_ERR(unit)) {
                return rv;
            }
#else
            rv = BCM_E_NONE;
#endif
        }

   }
    return rv;
}

STATIC void 
_bcm_hx5_gport_numq_get(int unit, int id, int *numq)
{
    switch(id) {
    case 1:
    case 2:
        *numq = 1;
        break;
    case 3:
    case 4:
    case 5:
        *numq = 8;
        break;
    default:
    case 6:
        *numq = 2;
        break;
    }
}
/*
 * Function:
 *      _bcm_hx5_cosq_st_gport_tree_create
 * Purpose:
 *      During cosq init create the default cosq gport tree.
 *      Schedualar (L0) nodes are created and attach to physical ports.
 *      UC and MC queues are added and attached to each L0 nodes.
 * Parameters:
 *      unit - (IN) unit number.
 *      port - (IN) port number
 * Returns:
 *     BCM_E_XXX
 */
STATIC int
_bcm_hx5_cosq_st_gport_tree_create(int unit, bcm_port_t port)
{
    int id, sc_id;
    bcm_gport_t sched_gport[SOC_HX5_NUM_SCHEDULER_PER_ST_PORT];
    bcm_gport_t uc_gport[SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT];
    bcm_gport_t mc_gport[SOC_HX5_NUM_MCAST_QUEUE_PER_ST_PORT];
    int numq = 1;

    /*Creating all L0,L1 and L2 scheduler nodes */
    for (id = 0; id < SOC_HX5_NUM_SCHEDULER_PER_ST_PORT; id++) {
        _bcm_hx5_gport_numq_get(unit, id, &numq);        
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_gport_add(unit, port, numq, BCM_COSQ_GPORT_SCHEDULER,
                                     &sched_gport[id]));
    }

    /* Attaching L0 schedular node to front panel port */
    for (sc_id = 0; sc_id < 3; sc_id++) {
        BCM_IF_ERROR_RETURN
            (bcm_hx5_cosq_gport_attach(unit, sched_gport[sc_id], port, sc_id));
    }
    /* Attaching L1 schedular nodes to l0 Schedular nodes */
    for (sc_id = 3; sc_id < 7; sc_id++) {
        if (sc_id == 3) {
            BCM_IF_ERROR_RETURN
                (bcm_hx5_cosq_gport_attach(unit, sched_gport[sc_id],
                                           sched_gport[0], sc_id));
        } else if (sc_id > 3 && sc_id < 6) {
            BCM_IF_ERROR_RETURN
                (bcm_hx5_cosq_gport_attach(unit, sched_gport[sc_id],
                                           sched_gport[1], sc_id));
        } else {
            BCM_IF_ERROR_RETURN
                (bcm_hx5_cosq_gport_attach(unit, sched_gport[sc_id],
                                           sched_gport[2], sc_id));
        }
    }

    /* Aattaching L2 schedular nodes to  l1 Schedular nodes */
   for (sc_id = 7; sc_id < SOC_HX5_NUM_SCHEDULER_PER_ST_PORT; sc_id++) {
        if (sc_id < 15) {
            BCM_IF_ERROR_RETURN
                (bcm_hx5_cosq_gport_attach(unit, sched_gport[sc_id],
                                           sched_gport[3], sc_id));
        } else if((sc_id >= 15) && (sc_id < 23)) {
            BCM_IF_ERROR_RETURN
                (bcm_hx5_cosq_gport_attach(unit, sched_gport[sc_id],
                                           sched_gport[4], sc_id));
        } else if((sc_id >= 23 ) && (sc_id < 31)) {
            BCM_IF_ERROR_RETURN
                (bcm_hx5_cosq_gport_attach(unit, sched_gport[sc_id],
                                           sched_gport[5], sc_id));
        } else {
            BCM_IF_ERROR_RETURN
                (bcm_hx5_cosq_gport_attach(unit, sched_gport[sc_id],
                                           sched_gport[6], sc_id));
        }
    }
    numq = 1;
   /* Creating and attaching l3 uc and l2 mc queues to  l2 Schedular nodes */
   for (id = 0, sc_id = 7; id < SOC_HX5_NUM_MCAST_QUEUE_PER_ST_PORT &&
           sc_id < SOC_HX5_NUM_SCHEDULER_PER_ST_PORT; id++, sc_id++) {
       BCM_IF_ERROR_RETURN
           (_bcm_hx5_cosq_gport_add(unit, port, numq,
                                    BCM_COSQ_GPORT_UCAST_QUEUE_GROUP,
                                    &uc_gport[id]));
       BCM_IF_ERROR_RETURN
           (bcm_hx5_cosq_gport_attach(unit, uc_gport[id],
                                      sched_gport[sc_id], id));

       BCM_IF_ERROR_RETURN
           (_bcm_hx5_cosq_gport_add(unit, port, numq,
                                    BCM_COSQ_GPORT_MCAST_QUEUE_GROUP,
                                    &mc_gport[id]));
       BCM_IF_ERROR_RETURN
           (bcm_hx5_cosq_gport_attach(unit, mc_gport[id],
                                      sched_gport[sc_id], id));
   }
   return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_sched_weight_max_get
 * Purpose:
 *     Retrieve maximum weights for given COS policy
 * Parameters:
 *     unit       - (IN) unit number
 *     mode       - (IN) Scheduling mode (BCM_COSQ_xxx)
 *     weight_max - (OUT) Maximum weight for COS queue.
 * Returns:
 *     BCM_E_XXX
 */
    int
bcm_hx5_cosq_sched_weight_max_get(int unit, int mode, int *weight_max)
{
    switch (mode) {
        case BCM_COSQ_STRICT:
            *weight_max = BCM_COSQ_WEIGHT_STRICT;
            break;
        case BCM_COSQ_ROUND_ROBIN:
        case BCM_COSQ_WEIGHTED_ROUND_ROBIN:
        case BCM_COSQ_DEFICIT_ROUND_ROBIN:
            /* In hx5, weights can be [1, 127] */
            *weight_max =
                (1 << soc_mem_field_length(unit, Q_SCHED_L0_WEIGHT_MEMm,
                                           WEIGHTf)) - 1;
            break;
        default:
            return BCM_E_PARAM;
    }

    return BCM_E_NONE;
}


/*
 * Function:
 *     _bcm_hx5_sched_weight_setget
 * Purpose:
 *     Get/Set weights for given COS policy
 * Parameters:
 *     unit     - (IN)  unit number
 *     port     - (IN)  port number
 *     level    - (IN)  node level
 *     index    - (IN)  COS queue number
 *     weights  - (OUT) Weights for COS queue.
 *     mc       - (IN)  Multicast queue group
 *     setget   - (IN)  Set/get flag
 * Returns:
 *     BCM_E_XXX
 */
STATIC int
_bcm_hx5_sched_weight_setget(int unit, int port, int level, int index,
        int *weight, int mc, int setget)
{
    soc_info_t *si;
    soc_mem_t mem = INVALIDm;
    uint32 entry[SOC_MAX_MEM_WORDS];
    int pipe = 0;
    int phy_port, mmu_port;

    si = &SOC_INFO(unit);
    phy_port = si->port_l2p_mapping[port];
    mmu_port = si->port_p2m_mapping[phy_port];

    switch(level) {
        case SOC_HX5_NODE_LVL_L0:
            mem = Q_SCHED_L0_WEIGHT_MEMm;
            if(IS_CPU_PORT(unit, port)) {
                index = _HX5_CPU_LO_NODE_BASE;
            } else if(_HX5_IS_ST_PORT(unit, mmu_port)){
               index += (mmu_port * _HX5_ST_NUML0_NODES);
            } else {
               index +=  _HX5_BASE_L0QUEUE +  ((mmu_port - _BCM_HX5_NUM_ST_PORTS)  * _HX5_NUML0_NODES);
            }
            break;

        case SOC_HX5_NODE_LVL_L1:
            mem = Q_SCHED_L1_WEIGHT_MEMm;
            if(IS_CPU_PORT(unit, port)) {
                index = _HX5_CPU_L1_NODE_BASE;
            } else if(_HX5_IS_ST_PORT(unit, mmu_port)){
               index += (mmu_port * _HX5_ST_NUML1_NODES);
            } else {
               index += _HX5_BASE_L1QUEUE + ((mmu_port - _BCM_HX5_NUM_ST_PORTS) * _HX5_NUML1_NODES);
            }
            break;

        case SOC_HX5_NODE_LVL_L2:
            mem = Q_SCHED_L2_WEIGHT_MEMm;
            if(IS_CPU_PORT(unit, port)) {
                index += _HX5_CPU_L2_NODE_BASE;
            } else if(_HX5_IS_ST_PORT(unit, mmu_port)){
               index += (mmu_port * _HX5_ST_NUML2_NODES);
            } else {
               index += _HX5_BASE_L2QUEUE + ((mmu_port - _BCM_HX5_NUM_ST_PORTS) * _HX5_NUML2_NODES);
            }
            break;

        case SOC_HX5_NODE_LVL_L3:
            mem = Q_SCHED_L3_WEIGHT_MEMm;
            if(IS_CPU_PORT(unit, port)) {
                index += _HX5_CPU_L2_NODE_BASE;
            } else if(_HX5_IS_ST_PORT(unit, mmu_port)){
                index +=  (mmu_port * SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT);
            } else {
                index +=  SOC_HX5_DOWNLINK_PORTQ_BASE + ((mmu_port - _BCM_HX5_NUM_ST_PORTS) * SOC_HX5_NUM_UCAST_QUEUE_PER_PORT);
            }
            if(mc == 1) {
                index += SOC_HX5_NUM_UC_QUEUES_PER_PIPE;
            }
            break;
        default:
        return BCM_E_PARAM;
    }

    mem = SOC_MEM_UNIQUE_ACC(unit, mem)[pipe];
    SOC_IF_ERROR_RETURN
        (soc_mem_read(unit, mem, MEM_BLOCK_ALL, index, &entry));

    if (setget == 1) {
        soc_mem_field32_set(unit, mem, &entry, WEIGHTf, *weight);
        SOC_IF_ERROR_RETURN
            (soc_mem_write(unit, mem, MEM_BLOCK_ALL, index, &entry));
    } else {
        *weight = soc_mem_field32_get(unit, mem, &entry, WEIGHTf);
    }

    return BCM_E_NONE;
}




/*
 * Function:
 *     _bcm_hx5_cosq_sched_mode_setget
 * Purpose:
 *     Get/Set scheduling mode
 * Parameters:
 *     unit     - (IN)  Unit number
 *     port     - (IN)  Port number
 *     level    - (IN)  Node level
 *     index    - (IN)  COS queue number
 *     mode     - (IN/OUT) Scheduling mode (BCM_COSQ_xxx)
 *     weights  - (IN/OUT) Weights for COS queue.
 *     mc       - (IN)  Multicast queue group
 *     setget   - (IN)  Set/get flag
 * Returns:
 *     BCM_E_XXX
 */
STATIC int
_bcm_hx5_cosq_sched_mode_setget(int unit, bcm_port_t port, int level, int index,
        soc_hx5_sched_mode_e *mode, int *weight, int mc,
        int setget)
{
    soc_reg_t reg, reg2 = INVALIDr;
    uint32 fval = 0, rval, wrr_mask, sp_mask;
    uint64 rval64;
    int parent_index = 0;
    int mmu_port, phy_port;
    int child_idx = 0;

    soc_info_t *si = &SOC_INFO(unit);
    phy_port = si->port_l2p_mapping[port];
    mmu_port = si->port_p2m_mapping[phy_port];


    if (index < 0) {
        return BCM_E_PARAM;
    }
    child_idx = index;

    if (setget == 1) {
        LOG_INFO(BSL_LS_SOC_COSQ,
                (BSL_META_U(unit,
                            "Port:%d L%s%d config : index=%d MODE=%d WT=%d\n"),
                 port, (level == 0) ? "r" : "", level - 1, index, *mode,
                 *weight));
    }



    /* Selection between SP and WxRR is based on weight property. */
    BCM_IF_ERROR_RETURN
        (_bcm_hx5_sched_weight_setget(unit, port, level, index, weight, mc,
                                      setget));

    if ((level == SOC_HX5_NODE_LVL_L1 || level == SOC_HX5_NODE_LVL_L2) && (IS_CPU_PORT(unit, port))) {
            return BCM_E_NONE;
    }

    switch(level) {
        case SOC_HX5_NODE_LVL_L0:
            reg = IS_CPU_PORT(unit, port) ? Q_SCHED_CPU_PORT_CONFIGr : Q_SCHED_PORT_CONFIGr;
            index = 0;
            reg2 = _HX5_IS_ST_PORT(unit, mmu_port) ? Q_SCHED_L0_NODE_CONFIG_HIQr : Q_SCHED_L0_NODE_CONFIGr;
            break;

        case SOC_HX5_NODE_LVL_L1:
            if(_HX5_IS_ST_PORT(unit, mmu_port)) {
                reg = Q_SCHED_L0_NODE_CONFIG_HIQr;
                index = (index == 0) ? 0 : (index > 0 && index < 3) ? 1 : 2;
            } else {
                reg = Q_SCHED_L0_NODE_CONFIGr;
                index = 0;
            }
            reg2 = _HX5_IS_ST_PORT(unit, mmu_port) ? Q_SCHED_L1_NODE_CONFIG_HIQr : Q_SCHED_L1_NODE_CONFIGr;
            break;

        case SOC_HX5_NODE_LVL_L2:
            if(_HX5_IS_ST_PORT(unit, mmu_port)) {
                reg = Q_SCHED_L1_NODE_CONFIG_HIQr;
                if( index >= 0 && index < 8 ) {
                    index = 0;
                } else if (index >= 8 && index < 16 ){
                    index = 1;
                } else if (index >= 16 && index < 24 ){
                    index = 2;
                } else {
                    index = 3;
                }
            } else {
                reg = Q_SCHED_L1_NODE_CONFIGr;
                index = (index >= 0 && index < 8) ? 0 : 1;
            }
            reg2 = _HX5_IS_ST_PORT(unit, mmu_port) ? Q_SCHED_L2_NODE_CONFIG_HIQ_SPLIT0r : Q_SCHED_L2_NODE_CONFIG_NORMQr;
            break;

        case SOC_HX5_NODE_LVL_L3:
            if (IS_CPU_PORT(unit, port)) {
                reg = Q_SCHED_CPU_L2_NODE_CONFIGr;
                SOC_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_cpu_parent_get(unit, index, SOC_HX5_NODE_LVL_L3,
                                                  &parent_index));
                index = parent_index;
            } else if(_HX5_IS_ST_PORT(unit, mmu_port)) {
                reg = Q_SCHED_L2_NODE_CONFIG_HIQ_SPLIT0r;
                reg2 = (mc) ? Q_SCHED_L3_MC_NODE_CONFIG_HIQr : Q_SCHED_L3_UC_NODE_CONFIG_HIQr;
            } else {
                reg = Q_SCHED_L2_NODE_CONFIG_NORMQr;
                reg2 = (mc) ? Q_SCHED_L3_MC_NODE_CONFIG_NORMQr : Q_SCHED_L3_UC_NODE_CONFIG_NORMQr;
            }
            break;
        default:
            return BCM_E_PARAM;

    }

    if (SOC_REG_IS_64(unit, reg)) {
        SOC_IF_ERROR_RETURN(soc_reg_get(unit, reg, port, 0, &rval64));
        wrr_mask = soc_reg64_field32_get(unit, reg, rval64, ENABLE_WRRf);
    } else {
        SOC_IF_ERROR_RETURN(soc_reg32_get(unit, reg, port, 0, &rval));
        wrr_mask = soc_reg_field_get(unit, reg, rval, ENABLE_WRRf);
    }

    if (setget == 1) {
        if (*mode == SOC_HX5_SCHED_MODE_WRR) {
            fval = 1;
        } else if (*mode == SOC_HX5_SCHED_MODE_WERR) {
            fval = 0;
        }

        if (*mode != SOC_HX5_SCHED_MODE_STRICT) {
            wrr_mask &= ~(1 << index);
            wrr_mask |= (fval << index);
            if (SOC_REG_IS_64(unit, reg)) {
                soc_reg64_field32_set(unit, reg, &rval64, ENABLE_WRRf, wrr_mask);
                SOC_IF_ERROR_RETURN(soc_reg_set(unit, reg, port, 0, rval64));
            }else {
                soc_reg_field_set(unit, reg, &rval, ENABLE_WRRf, wrr_mask);
                SOC_IF_ERROR_RETURN(soc_reg32_set(unit, reg, port, 0, rval));
            }
        }
        if (!IS_CPU_PORT(unit, port)) {
            if (SOC_REG_IS_64(unit, reg2)) {
                SOC_IF_ERROR_RETURN(soc_reg_get(unit, reg2, port, 0, &rval64));
                sp_mask = soc_reg64_field32_get(unit, reg2, rval64, ENABLE_SP_IN_MINf);
            } else {
                SOC_IF_ERROR_RETURN(soc_reg32_get(unit, reg2, port, 0, &rval));
                sp_mask = soc_reg_field_get(unit, reg2, rval, ENABLE_SP_IN_MINf);
            }
            if (*mode == SOC_HX5_SCHED_MODE_STRICT) {
                sp_mask |= (1 << child_idx);
            } else {
                sp_mask &= ~(1 << child_idx);
            }
            if (SOC_REG_IS_64(unit, reg2)) {
                soc_reg64_field32_set(unit, reg2, &rval64, ENABLE_SP_IN_MINf, sp_mask);
                SOC_IF_ERROR_RETURN(soc_reg_set(unit, reg2, port, 0, rval64));
            }else {
                soc_reg_field_set(unit, reg2, &rval, ENABLE_SP_IN_MINf, sp_mask);
                SOC_IF_ERROR_RETURN(soc_reg32_set(unit, reg2, port, 0, rval));
            }
        }

    } else {
        if (*weight == 0) {
            *mode = SOC_HX5_SCHED_MODE_STRICT;
        } else if (wrr_mask & (1 << index)) {
            *mode = SOC_HX5_SCHED_MODE_WRR;
        } else {
            *mode = SOC_HX5_SCHED_MODE_WERR;
        }
    }

    return BCM_E_NONE;
}


/*
 * Function:
 *     _bcm_hx5_cosq_sched_get
 * Purpose:
 *     Get scheduling mode setting
 * Parameters:
 *     unit     - (IN) unit number
 *     gport    - (IN) GPORT identifier
 *     cosq     - (IN) COS queue number
 *     mode     - (OUT) Scheduling mode (BCM_COSQ_xxx)
 *     weights  - (OUT) Weights for COS queue.
 * Returns:
 *     BCM_E_XXX
 */
    STATIC int
_bcm_hx5_cosq_sched_get(int unit, bcm_gport_t gport, bcm_cos_queue_t cosq,
        int *mode, int *weight)
{
    soc_hx5_sched_mode_e sched_mode;
    bcm_port_t local_port;
    _bcm_hx5_cosq_node_t *node = NULL;
    int lvl = SOC_HX5_NODE_LVL_L2, mc = 0;


    if (BCM_GPORT_IS_SET(gport)) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_node_get(unit, gport, NULL, &local_port, NULL,
                                    &node));
        lvl = node->level;
    }else {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));

    }

    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
            BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        mc = BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport) ? 1 : 0;
    } else if (IS_CPU_PORT(unit, local_port)) {
        mc = 1;
        lvl = SOC_HX5_NODE_LVL_L3;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_sched_mode_setget(unit, local_port, lvl, cosq,
                                         &sched_mode, weight, mc, 0));

    switch(sched_mode) {
        case SOC_HX5_SCHED_MODE_STRICT:
            *mode = BCM_COSQ_STRICT;
            break;

        case SOC_HX5_SCHED_MODE_WRR:
            *mode = BCM_COSQ_WEIGHTED_ROUND_ROBIN;
            break;

        case SOC_HX5_SCHED_MODE_WERR:
            *mode = BCM_COSQ_DEFICIT_ROUND_ROBIN;
            break;

        default:
            return BCM_E_INTERNAL;
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_gport_sched_get
 * Purpose:
 *     Get COS queue schedular setting
 * Parameters:
 *     unit     - (IN) unit number
 *     gport    - (IN) GPORT identifier
 *     cosq     - (IN) COS queue to get, -1 for any queue
 *     mode     - (OUT) Scheduling mode (BCM_COSQ_xxx)
 *     weights  - (OUT) Weights for COS queue.
 * Returns:
 *     BCM_E_XXX
 */
    int
bcm_hx5_cosq_gport_sched_get(int unit, bcm_gport_t gport, bcm_cos_queue_t cosq,
        int *mode, int *weight)
{
    int local_port = -1;
    soc_info_t *si = &SOC_INFO(unit);

    if (BCM_GPORT_IS_SET(gport)) {
        if ((BCM_GPORT_IS_SCHEDULER(gport)) ||
                BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
                BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {

            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_node_hw_index_get(unit, gport, &cosq));

            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_sched_get(unit, gport, cosq, mode, weight));
            return BCM_E_NONE;
        } else {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));

            if ((cosq < 0) || (cosq >= si->port_num_cosq[local_port])) {
                return BCM_E_PARAM;
            }

            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_sched_get(unit, local_port, cosq, mode, weight));
            return BCM_E_NONE;
        }
    } else {
        return BCM_E_PORT;
    }

    return BCM_E_NOT_FOUND;
}


/*
 * Function:
 *     bcm_hx5_cosq_port_sched_get
 * Purpose:
 *     Retrieve class-of-service policy and corresponding weights and delay
 * Parameters:
 *     unit     - (IN) unit number
 *     pbm      - (IN) port bitmap
 *     mode     - (OUT) Scheduling mode (BCM_COSQ_xxx)
 *     weights  - (OUT) Weights for each COS queue.
 *     delay    - This parameter is not used
 * Returns:
 *     BCM_E_XXX
 */
    int
bcm_hx5_cosq_port_sched_get(int unit, bcm_pbmp_t pbm, int *mode, int *weights,
        int *delay)
{
    bcm_port_t port;
    int num_weights, i;

    BCM_PBMP_ITER(pbm, port) {
        if (IS_CPU_PORT(unit, port) && SOC_PBMP_NEQ(pbm, PBMP_CMIC(unit))) {
            continue;
        }
        num_weights = _BCM_HX5_NUM_COS(unit); 
        for (i = 0; i < num_weights; i++) {
            BCM_IF_ERROR_RETURN(
                    _bcm_hx5_cosq_sched_get(unit, port, i, mode, &weights[i]));
        }
    }

    return BCM_E_NONE;
}




/*
 * Function:
 *     _bcm_hx5_cosq_sched_set
 * Purpose:
 *     Set scheduling mode
 * Parameters:
 *     unit     - (IN) unit number
 *     gport    - (IN) GPORT identifier
 *     cosq     - (IN) COS queue number
 *     mode     - (IN) Scheduling mode (BCM_COSQ_xxx)
 *     weights  - (IN) Weight for COS queue.
 * Returns:
 *     BCM_E_XXX
 */
STATIC int
_bcm_hx5_cosq_sched_set(int unit, bcm_gport_t gport, bcm_cos_queue_t cosq,
        int mode, int weight)
{
    soc_hx5_sched_mode_e sched_mode;
    _bcm_hx5_cosq_node_t *node = NULL;
    bcm_port_t local_port;
    int lwts = 1, child_index=0, lvl = SOC_HX5_NODE_LVL_L2, mc = 0;

    if (cosq < 0) {
        if (cosq == -1) {
            /* caller needs to resolve the wild card value (-1) */
            return BCM_E_INTERNAL;
        } else {
            return BCM_E_PARAM;
        }
    }

    if ((weight < 0) || (weight > 127)) {
        return BCM_E_PARAM;
    }

    switch(mode) {
        case BCM_COSQ_STRICT:
            sched_mode = SOC_HX5_SCHED_MODE_STRICT;
            lwts = 0;
            break;
        case BCM_COSQ_ROUND_ROBIN:
            sched_mode = SOC_HX5_SCHED_MODE_WRR;
            lwts = 1;
            break;
        case BCM_COSQ_WEIGHTED_ROUND_ROBIN:
            sched_mode = SOC_HX5_SCHED_MODE_WRR;
            lwts = weight;
            break;
        case BCM_COSQ_DEFICIT_ROUND_ROBIN:
            sched_mode = SOC_HX5_SCHED_MODE_WERR;
            lwts = weight;
            break;
        default:
            return BCM_E_PARAM;
    }

    /* Weight = 0 corresponds to Strict Mode */
    if (lwts == 0) {
        sched_mode = SOC_HX5_SCHED_MODE_STRICT;
    }

    if(BCM_GPORT_IS_SET(gport)) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_node_get(unit, gport, NULL, &local_port, NULL,
                                    &node));
        lvl = node->level;
    } else {
        BCM_IF_ERROR_RETURN(_bcm_hx5_cosq_localport_resolve(unit, gport,
                    &local_port));

    }

    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
            BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        mc = BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport) ? 1 : 0;
    } else if (IS_CPU_PORT(unit, local_port)) {
        if(BCM_GPORT_IS_SET(gport)) {
            if(lvl == SOC_HX5_NODE_LVL_L3) {
                mc = 1;
            }
        } else {
            lvl = SOC_HX5_NODE_LVL_L3;
            mc = 1;
        }
    }

    child_index = cosq;
    BCM_IF_ERROR_RETURN(_bcm_hx5_cosq_sched_mode_setget(unit, local_port, lvl,
                child_index, &sched_mode, &lwts, mc, 1));

    return BCM_E_NONE;
}





/*
 * Function:
 *     bcm_hx5_cosq_gport_sched_set
 * Purpose:
 *     Set up class-of-service policy and corresponding weights
 * Parameters:
 *     unit     - (IN) unit number
 *     gport    - (IN) GPORT identifier
 *     cosq     - (IN) COS queue to get
 *     mode     - (IN) Scheduling mode (BCM_COSQ_xxx)
 *     weight   - (IN) Weight for COS queue.
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_gport_sched_set(int unit, bcm_gport_t gport, bcm_cos_queue_t cosq,
        int mode, int weight)
{
    soc_info_t *si = &SOC_INFO(unit);
    int local_port = -1;

    if (BCM_GPORT_IS_SET(gport)) {
        if (BCM_GPORT_IS_SCHEDULER(gport) ||
                BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
                BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {

            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_node_hw_index_get(unit, gport, &cosq));

            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_sched_set(unit, gport, cosq, mode, weight));
            return BCM_E_NONE;

        } else {
            BCM_IF_ERROR_RETURN(_bcm_hx5_cosq_localport_resolve(unit, gport,
                        &local_port));

            if ((cosq < 0) || (cosq >= si->port_num_cosq[local_port])) {
                return BCM_E_PARAM;
            }

            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_sched_set(unit, local_port, cosq, mode, weight));
            return BCM_E_NONE;
        }
    } else {
        return BCM_E_PORT;
    }

    return BCM_E_NOT_FOUND;
}

/*
 * Function:
 *     bcm_hx5_cosq_port_sched_set
 * Purpose:
 *     Set up class-of-service policy and corresponding weights and delay
 * Parameters:
 *     unit     - (IN) unit number
 *     pbm      - (IN) port bitmap
 *     mode     - (IN) Scheduling mode (BCM_COSQ_xxx)
 *     weight   - (IN) Weight for each COS queue.
 *     delay    - This parameter is not used
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_port_sched_set(int unit, bcm_pbmp_t pbm, int mode, const int
        *weights, int delay)
{
    bcm_port_t port; 
    int num_weights, i = 0;
    int phy_port, mmu_port;

    soc_info_t *si = &SOC_INFO(unit);

    BCM_PBMP_ITER(pbm, port) {
        num_weights = _BCM_HX5_NUM_COS(unit); 
        phy_port = si->port_l2p_mapping[port];
        mmu_port = si->port_p2m_mapping[phy_port];
        for (i = 0; i < num_weights; i++) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_sched_set(unit, port, i, mode, weights[i]));

            if(!IS_CPU_PORT(unit, port)) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_sched_set(unit, port, i + 8, mode, weights[i]));

                if (_HX5_IS_ST_PORT(unit, mmu_port)) {
                    BCM_IF_ERROR_RETURN
                        (_bcm_hx5_cosq_sched_set(unit, port, i + 16, mode, weights[i]));
                }
            }
        }
    }

    return BCM_E_NONE;
}
                       

/*
 * Function:
 *      _bcm_hx5_cosq_sched_config_port
 * Purpose:
 *      Set scheduler Configuration for the specified port
 * Parameters:
 *      unit        - (IN) unit number.
 *      port        - (IN) port number.
 * Returns:
 *     BCM_E_XXX
 */
STATIC int
_bcm_hx5_cosq_sched_config_port(int unit, int port, int mode, int weight)
{
    _bcm_hx5_cosq_port_info_t *port_info = NULL;
    _bcm_hx5_cosq_st_port_info_t *stport_info = NULL;
    int phy_port, mmu_port, i, index;

    soc_info_t *si = &SOC_INFO(unit);
    phy_port = si->port_l2p_mapping[port];
    mmu_port = si->port_p2m_mapping[phy_port];
    _HX5_PORT_INDEX_GET(unit, mmu_port, index);

    if (_HX5_IS_ST_PORT(unit, mmu_port)) {
        stport_info = &_bcm_hx5_cosq_st_port_info[unit][index];

        for (i = 0; i < SOC_HX5_NUM_SCHEDULER_PER_ST_PORT; i++) {
            BCM_IF_ERROR_RETURN
                (bcm_hx5_cosq_gport_sched_set(unit, stport_info->sched[i].gport,
                                              -1, mode, weight));
        }
        for (i = 0; i < SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT; i++) {
            BCM_IF_ERROR_RETURN
                (bcm_hx5_cosq_gport_sched_set(unit, stport_info->ucast[i].gport,
                                              -1, mode, weight));
        }
        for (i = 0; i < SOC_HX5_NUM_MCAST_QUEUE_PER_ST_PORT; i++) {
            BCM_IF_ERROR_RETURN
                (bcm_hx5_cosq_gport_sched_set(unit, stport_info->mcast[i].gport,
                                              -1, mode, weight));
        }
    } else {
        port_info = &_bcm_hx5_cosq_port_info[unit][index];

        for (i = 0; i < SOC_HX5_NUM_SCHEDULER_PER_PORT; i++) {
            BCM_IF_ERROR_RETURN
                (bcm_hx5_cosq_gport_sched_set(unit, port_info->sched[i].gport,
                                              -1, mode, weight));
        }
        for (i = 0; i < SOC_HX5_NUM_UCAST_QUEUE_PER_PORT; i++) {
            BCM_IF_ERROR_RETURN
                (bcm_hx5_cosq_gport_sched_set(unit, port_info->ucast[i].gport,
                                              -1, mode, weight));
        }
        for (i = 0; i < SOC_HX5_NUM_MCAST_QUEUE_PER_PORT; i++) {
            BCM_IF_ERROR_RETURN
                (bcm_hx5_cosq_gport_sched_set(unit, port_info->mcast[i].gport,
                                              -1, mode, weight));
        }
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *      _bcm_hx5_cosq_sched_default_config
 * Purpose:
 *      Set Default Scheduler Configuration for all the ports
 * Parameters:
 *      unit        - (IN) unit number.
 * Returns:
 *     BCM_E_XXX
 */
STATIC int
_bcm_hx5_cosq_sched_default_config(int unit)
{
    _bcm_hx5_cosq_cpu_port_info_t *cpu_port_info = NULL;
    bcm_port_t port;
    int default_mode = BCM_COSQ_WEIGHTED_ROUND_ROBIN, default_weight = 1;
    int i;

    port = 0;
    cpu_port_info = &_bcm_hx5_cosq_cpu_port_info[unit][port];
    for (i = 0; i < SOC_HX5_NUM_SCHEDULER_PER_CPU_PORT; i++) {
        BCM_IF_ERROR_RETURN
            (bcm_hx5_cosq_gport_sched_set(unit, cpu_port_info->sched[i].gport,
                                          -1, default_mode, default_weight));
    }
    for (i = 0; i < SOC_HX5_NUM_CPU_QUEUES; i++) {
        BCM_IF_ERROR_RETURN
            (bcm_hx5_cosq_gport_sched_set(unit, cpu_port_info->mcast[i].gport,
                                          -1, default_mode, default_weight));
    }

    PBMP_ALL_ITER(unit, port) {
        if (IS_CPU_PORT(unit, port) || IS_LB_PORT(unit, port) || IS_FAE_PORT(unit, port)) {
            continue;
        }
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_sched_config_port(unit, port, default_mode,
                                             default_weight));
    }

    return BCM_E_NONE;
}





STATIC int
_bcm_hx5_cosq_gport_default_config(int unit)
{
    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_sched_default_config(unit));

    return BCM_E_NONE;
}


/****************
 * BST Support
 ****************/


STATIC int
_bcm_hx5_cosq_egress_sp_get(int unit, bcm_gport_t gport, bcm_cos_queue_t cosq, 
        int *p_pool_start, int *p_pool_end)
{
    int local_port;
    int pool; 

    if (cosq == BCM_COS_INVALID) {
        if (p_pool_start && p_pool_end) {
            *p_pool_start = 0;
            *p_pool_end = 3;
            return BCM_E_NONE;
        } else {
            return BCM_E_PARAM;
        }
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_index_resolve(unit, gport, cosq, 
                                     _BCM_HX5_COSQ_INDEX_STYLE_EGR_POOL,
                                     &local_port, &pool, NULL));

    if (p_pool_start) {
        *p_pool_start = pool; 
    }
    if (p_pool_end) {
        *p_pool_end = pool; 
    }
    return BCM_E_NONE;
}
/*
 * Function:
 *     _bcm_hx5_cosq_index_resolve
 * Purpose:
 *     Find hardware index for the given port/cosq
 * Parameters:
 *     unit       - (IN) unit number
 *     port       - (IN) port number or GPORT identifier
 *     cosq       - (IN) COS queue number
 *     style      - (IN) index style (_BCM_KA_COSQ_INDEX_STYLE_XXX)
 *     local_port - (OUT) local port number
 *     index      - (OUT) result index
 *     count      - (OUT) number of index
 * Returns:
 *     BCM_E_XXX
 */
int
_bcm_hx5_cosq_index_resolve(int unit, bcm_port_t port, bcm_cos_queue_t cosq,
                           _bcm_hx5_cosq_index_style_t style,
                           bcm_port_t *local_port, int *index, int *count)
{
    bcm_port_t resolved_port;
    soc_info_t *si;
    int resolved_index = -1;
    int id, startq, numq = 0;
    int pipe = 0;
    int uc_base = 0, mc_base = 0, cpu_mc_base; /* Q base number */
    int mmu_port, phy_port;

    _bcm_hx5_cosq_node_t *node;
    uint32 entry0[SOC_MAX_MEM_WORDS];
    soc_mem_t mem;

    si = &SOC_INFO(unit);

    if (cosq < -1) {
        return BCM_E_PARAM;
    } else if (cosq == -1) {
        startq = 0;
        numq = NUM_COS(unit);
    } else {
        startq = cosq;
        numq = 1;
    }


    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
        BCM_GPORT_IS_MCAST_QUEUE_GROUP(port) ||
        BCM_GPORT_IS_SCHEDULER(port)) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_node_get(unit, port, NULL, &resolved_port, &id,
                                   &node));
        if (resolved_port < 0) {
            return BCM_E_PORT;
        }
    } else {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, port, &resolved_port));
        if (resolved_port < 0) {
            return BCM_E_PORT;
        }
        node = NULL;
        numq = (IS_CPU_PORT(unit, resolved_port)) ? NUM_CPU_COSQ(unit) : NUM_COS(unit);
    }
    phy_port = si->port_l2p_mapping[resolved_port];
    mmu_port = si->port_p2m_mapping[phy_port];
    mc_base = si->port_cosq_base[resolved_port];
    uc_base = si->port_uc_cosq_base[resolved_port];

    switch (style) {
        case _BCM_HX5_COSQ_INDEX_STYLE_WRED_DEVICE:
            if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                return BCM_E_PARAM;
            }
            if ((port == -1) || (cosq == -1)) {
                numq = _HX5_MMU_NUM_POOL; /* 4 Global Service Pools */
                resolved_index = _HX5_WRED_PER_PIPE_GLOBAL_SP_BASE;
            } else {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_egress_sp_get(unit, port, cosq,
                                                &resolved_index,
                                                NULL));
                numq = 1;
                resolved_index += _HX5_WRED_PER_PIPE_GLOBAL_SP_BASE;
            }
            break;

        case _BCM_HX5_COSQ_INDEX_STYLE_WRED_PORT:
            if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                return BCM_E_PARAM;
            }
            resolved_index = 0;
            if (cosq != -1) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_egress_sp_get(unit, port, cosq,
                                                &resolved_index,
                                                NULL));
            }
            resolved_index += _HX5_WRED_PER_PIPE_PORT_SP_BASE +
                              (mmu_port * 4);
            numq = (cosq == -1) ? 4: 1;
            break;

        case _BCM_HX5_COSQ_INDEX_STYLE_WRED_QUEUE:
            if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                return BCM_E_PARAM;
            }
            if (node) {
                if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port)) {
                     resolved_index = node->hw_index;
                } else {
                    return BCM_E_PARAM;
                }
            } else {
                resolved_index = uc_base;
                if (cosq != -1) {
                    numq = si->port_num_cosq[resolved_port];
                    if (cosq >= numq) {
                        return BCM_E_PARAM;
                    }
                    resolved_index += cosq;
                }
                numq = (cosq == -1) ? NUM_COS(unit): 1;
            }
            break;

        case _BCM_HX5_COSQ_INDEX_STYLE_EGR_POOL:
            if ((node != NULL) && (!BCM_GPORT_IS_MODPORT(port))) {
                if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port)) {
                    /* regular unicast queue */
                    resolved_index = node->hw_index ;
                    mem = MMU_THDU_Q_TO_QGRP_MAPm;
                } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                    resolved_index = node->hw_index ;
                    mem = MMU_THDM_MCQE_QUEUE_CONFIGm;
                } else { /* scheduler */
                    return BCM_E_PARAM;
                }
            } else { /* node == NULL */
                /* PGA check this else  part for uc index based on port type 
                   icaluclation */
                numq = si->port_num_cosq[resolved_port];
                if (startq >= numq) {
                    return BCM_E_PARAM;
                }
                resolved_index = uc_base + startq;
                mem = MMU_THDU_Q_TO_QGRP_MAPm;
            }
            mem = SOC_MEM_UNIQUE_ACC(unit, mem)[pipe];

            SOC_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, resolved_index,
                                entry0));
            resolved_index = soc_mem_field32_get(unit, mem, entry0, Q_SPIDf);
            break;

        case _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE:
            /* Return hw_index for given unicast queue gport */
            if (node) {
                if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port)) {
                     resolved_index = node->hw_index; 
                } else {
                    return BCM_E_PARAM;
                }
            } else {
                numq = si->port_num_cosq[resolved_port];
                if ((startq >= numq) || (IS_LB_PORT(unit, resolved_port))) {
                    return BCM_E_PARAM;
                }
                resolved_index = uc_base + startq;
            }
            break;
        case _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE:
            /* Return hw_index for given multicast queue gport */
            if (node) {
                if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                         resolved_index = node->hw_index; 
                } else {
                    return BCM_E_PARAM;
                }
            } else {
                numq = si->port_num_cosq[resolved_port];
                if (startq >= numq) {
                    return BCM_E_PARAM;
                }
                resolved_index = mc_base + startq;
            }
            break;
        case _BCM_HX5_COSQ_INDEX_STYLE_COS:
            if (node) {
                if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port)) {
                    resolved_index = node->hw_index;
                } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                    if (IS_CPU_PORT(unit, resolved_port)) {
                        cpu_mc_base = si->port_cosq_base[CMIC_PORT(unit)];
                        resolved_index = (node->hw_index - cpu_mc_base) %
                            NUM_CPU_COSQ(unit);
                    } else {
                        resolved_index = node->hw_index;
                    }
                } else {
                    resolved_index = node->hw_index;
                }
            } else {
                resolved_index = startq;
            }
            break;
        default:
            return BCM_E_PARAM;
    }

    if (index) {
        *index = resolved_index;
    }
    if (local_port) {
        *local_port = resolved_port;
    }
    if (count) {
        *count = (cosq == -1) ? numq : 1;
    }

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_bst_map_resource_to_gport_cos(int unit,
        bcm_bst_stat_id_t bid, int port, int index, bcm_gport_t *gport,
        bcm_cos_t *cosq)
{
    soc_info_t *si = &SOC_INFO(unit);
    _bcm_bst_resource_info_t *pres = NULL;
    int phy_port = 0;
    int mmu_port = 0;
    int stats_per_inst = 1;
    int stats_per_pipe = 1;

    if (bid >= bcmBstStatIdMaxCount) {
        LOG_INFO(BSL_LS_BCM_COSQ,
                (BSL_META_U(unit,
                            "_bcm_th_cosq_bst_map_resource_to_gport_cos: unit=%d bid=0x%x\n"),
                 unit, bid));
        return BCM_E_NONE;
    }

    pres = _BCM_BST_RESOURCE(unit, bid);
    stats_per_inst = (pres->num_stat_pp) / (pres->num_instance);
    index %= stats_per_inst;
    if (pres->flags & _BCM_BST_CMN_RES_F_PIPED) {
        stats_per_pipe = stats_per_inst / NUM_PIPE(unit);
        index %= stats_per_pipe;
    }

    switch (bid) {
        case bcmBstStatIdDevice:
            *gport = -1;
            *cosq = BCM_COS_INVALID;
            break;

        case bcmBstStatIdIngPool:
        case bcmBstStatIdEgrPool:
        case bcmBstStatIdEgrMCastPool:
        case bcmBstStatIdRQEPool:
            *gport = -1;
            *cosq = index % _HX5_MMU_NUM_POOL;
            break;

        case bcmBstStatIdRQEQueue:
            *gport = -1;
            *cosq = index % _HX5_MMU_NUM_RQE_QUEUES;
            break;

        case bcmBstStatIdUCQueueGroup:
            mmu_port = index;
            phy_port = si->port_m2p_mapping[mmu_port];
            *gport = si->port_p2l_mapping[phy_port];
            *cosq =  -1;
            break;

        case bcmBstStatIdPortPool:
            mmu_port= index/_HX5_MMU_NUM_POOL;
            phy_port = si->port_m2p_mapping[mmu_port];
            *gport = si->port_p2l_mapping[phy_port];
            *cosq = index % _HX5_MMU_NUM_POOL;
            break;

        case bcmBstStatIdPriGroupHeadroom:
        case bcmBstStatIdPriGroupShared:
            mmu_port = index/_HX5_MMU_NUM_PG;
            phy_port = si->port_m2p_mapping[mmu_port];
            *gport = si->port_p2l_mapping[phy_port];
            *cosq = index % _HX5_MMU_NUM_PG;
            break;

        case bcmBstStatIdUcast:
        case bcmBstStatIdMcast:
            if (index <  SOC_HX5_DOWNLINK_PORTQ_BASE) {
               mmu_port = index / 26;
            } else {
               mmu_port = ((index - SOC_HX5_DOWNLINK_PORTQ_BASE) / 16) + 16;
            }
            if ((bid == bcmBstStatIdMcast) &&
                    (index >= si->port_cosq_base[CMIC_PORT(unit)])) {
                *gport = CMIC_PORT(unit);
                *cosq = index - si->port_cosq_base[CMIC_PORT(unit)];
            } else {
                phy_port = si->port_m2p_mapping[mmu_port];
                *gport = si->port_p2l_mapping[phy_port];
                *cosq = index - si->port_uc_cosq_base[*gport];
            }
            break;
        case bcmBstStatIdEgrPortPoolSharedUcast:
        case bcmBstStatIdEgrPortPoolSharedMcast:
            mmu_port = index/_HX5_MMU_NUM_POOL;
            phy_port = si->port_m2p_mapping[mmu_port];
            *gport = si->port_p2l_mapping[phy_port];
            *cosq = index % _HX5_MMU_NUM_POOL;
            break;
        default:
            break;
    }

    return BCM_E_NONE;
}


int
_bcm_hx5_cosq_pfc_class_resolve(bcm_switch_control_t sctype, int *type,
                               int *class)
{
    switch (sctype) {
        case bcmSwitchPFCClass7Queue:
        case bcmSwitchPFCClass6Queue:
        case bcmSwitchPFCClass5Queue:
        case bcmSwitchPFCClass4Queue:
        case bcmSwitchPFCClass3Queue:
        case bcmSwitchPFCClass2Queue:
        case bcmSwitchPFCClass1Queue:
        case bcmSwitchPFCClass0Queue:
            *type = _BCM_HX5_COSQ_TYPE_UCAST;
            break;
        case bcmSwitchPFCClass7McastQueue:
        case bcmSwitchPFCClass6McastQueue:
        case bcmSwitchPFCClass5McastQueue:
        case bcmSwitchPFCClass4McastQueue:
        case bcmSwitchPFCClass3McastQueue:
        case bcmSwitchPFCClass2McastQueue:
        case bcmSwitchPFCClass1McastQueue:
        case bcmSwitchPFCClass0McastQueue:
            *type = _BCM_HX5_COSQ_TYPE_MCAST;
            break;
        default:
            /* Unsupported Switch Control types should return E_UNAVAIL */
            return BCM_E_UNAVAIL;
    }

    switch (sctype) {
        case bcmSwitchPFCClass7Queue:
        case bcmSwitchPFCClass7McastQueue:
            *class = 7;
            break;
        case bcmSwitchPFCClass6Queue:
        case bcmSwitchPFCClass6McastQueue:
            *class = 6;
            break;
        case bcmSwitchPFCClass5Queue:
        case bcmSwitchPFCClass5McastQueue:
            *class = 5;
            break;
        case bcmSwitchPFCClass4Queue:
        case bcmSwitchPFCClass4McastQueue:
            *class = 4;
            break;
        case bcmSwitchPFCClass3Queue:
        case bcmSwitchPFCClass3McastQueue:
            *class = 3;
            break;
        case bcmSwitchPFCClass2Queue:
        case bcmSwitchPFCClass2McastQueue:
            *class = 2;
            break;
        case bcmSwitchPFCClass1Queue:
        case bcmSwitchPFCClass1McastQueue:
            *class = 1;
            break;
        case bcmSwitchPFCClass0Queue:
        case bcmSwitchPFCClass0McastQueue:
            *class = 0;
            break;
        /*
         * COVERITY
         *
         * This default is unreachable but needed for some compiler.
         */
        /* coverity[dead_error_begin] */
        default:
            return BCM_E_INTERNAL;
    }
    return BCM_E_NONE;
}



STATIC int
_bcm_hx5_cosq_ingress_pg_get(int unit, bcm_gport_t gport, bcm_cos_queue_t pri,
                            int *p_pg_start, int *p_pg_end)
{
    bcm_port_t local_port;
    uint32  rval,pool;
    soc_reg_t reg = INVALIDr;
    static const soc_reg_t prigroup_reg[] = {
        THDI_PORT_PRI_GRP0r, THDI_PORT_PRI_GRP1r
    };
    static const soc_field_t prigroup_field[] = {
        PRI0_GRPf, PRI1_GRPf, PRI2_GRPf, PRI3_GRPf,
        PRI4_GRPf, PRI5_GRPf, PRI6_GRPf, PRI7_GRPf,
        PRI8_GRPf, PRI9_GRPf, PRI10_GRPf, PRI11_GRPf,
        PRI12_GRPf, PRI13_GRPf, PRI14_GRPf, PRI15_GRPf
    };

    if (pri == BCM_COS_INVALID) {
        *p_pg_start = 0;
        *p_pg_end = 7;
        return BCM_E_NONE;
    }

    BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));

    if (!SOC_PORT_VALID(unit, local_port)) {
        return BCM_E_PORT;
    }

    if (pri >= _HX5_MMU_NUM_INT_PRI) {
        return BCM_E_PARAM;
    }
       /* get PG for port using Port+Cos */
    if (pri < (_HX5_MMU_NUM_INT_PRI / 2)) {
        reg = prigroup_reg[0];
    } else {
        reg = prigroup_reg[1];
    }

    SOC_IF_ERROR_RETURN
        (soc_reg32_get(unit, reg, local_port, 0, &rval));
        pool = soc_reg_field_get(unit, reg, rval, prigroup_field[pri]);

    if (p_pg_start) {
        *p_pg_start = pool;
    }

    if (p_pg_end) {
        *p_pg_end = pool;
    }

    return BCM_E_NONE;
}


/*
 * This function is used to get shared pool
 * for given Ingress [Port, Priority]
 */
STATIC int
_bcm_hx5_cosq_ingress_sp_get(int unit, bcm_gport_t gport, bcm_cos_t pri,
                            int *p_pool_start, int *p_pool_end)
{
    int local_port;
    uint32 rval, pool;
    int pri_grp;
    static const soc_field_t prigroup_spid_field[] = {
        PG0_SPIDf, PG1_SPIDf, PG2_SPIDf, PG3_SPIDf,
        PG4_SPIDf, PG5_SPIDf, PG6_SPIDf, PG7_SPIDf
    };

    if (pri == BCM_COS_INVALID) {
        if (p_pool_start && p_pool_end) {
            *p_pool_start = 0;
            *p_pool_end = 3;
            return BCM_E_NONE;
        } else {
            return BCM_E_PARAM;
        }
    }

    if ((pri < 0) || (pri >= _HX5_MMU_NUM_INT_PRI)) {
        /* Error. Input pri > Max Pri_Grp */
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_ingress_pg_get(unit, gport, pri, &pri_grp, &pri_grp));

    BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));

    if (!SOC_PORT_VALID(unit, local_port)) {
        return BCM_E_PORT;
    }

    if (pri_grp >= _HX5_MMU_NUM_PG) {
        return BCM_E_PARAM;
    }

    SOC_IF_ERROR_RETURN(READ_THDI_PORT_PG_SPIDr(unit, local_port, &rval));
    pool = soc_reg_field_get(unit, THDI_PORT_PG_SPIDr, rval,
                             prigroup_spid_field[pri_grp]);

    if (p_pool_start) {
        *p_pool_start = pool;
    }
    if (p_pool_end) {
        *p_pool_end = pool;
    }
    return BCM_E_NONE;
}

/*
 * This function is used to get shared pool
 * for given Ingress [Port, Priority_group]
 */
STATIC int
_bcm_hx5_cosq_ingress_sp_get_by_pg(int unit, bcm_gport_t gport, bcm_cos_queue_t pri_grp,
                            int *p_pool_start, int *p_pool_end)
{
    int local_port;
    uint32 rval, pool;
    static const soc_field_t prigroup_spid_field[] = {
        PG0_SPIDf, PG1_SPIDf, PG2_SPIDf, PG3_SPIDf,
        PG4_SPIDf, PG5_SPIDf, PG6_SPIDf, PG7_SPIDf
    };

    if (pri_grp == BCM_COS_INVALID) {
        if (p_pool_start && p_pool_end) {
            *p_pool_start = 0;
            *p_pool_end = 3;
            return BCM_E_NONE;
        } else {
            return BCM_E_PARAM;
        }
    }

    BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));

    if (!SOC_PORT_VALID(unit, local_port)) {
        return BCM_E_PORT;
    }

    if (pri_grp >= _HX5_MMU_NUM_PG) {
        return BCM_E_PARAM;
    }

    SOC_IF_ERROR_RETURN(READ_THDI_PORT_PG_SPIDr(unit, local_port, &rval));
    pool = soc_reg_field_get(unit, THDI_PORT_PG_SPIDr, rval,
                             prigroup_spid_field[pri_grp]);

    if (p_pool_start) {
        *p_pool_start = pool;
    }
    if (p_pool_end) {
        *p_pool_end = pool;
    }
    return BCM_E_NONE;
}

/*
 * This function is used to get headroom pool
 * for given Ingress [Port, Priority]
 */
STATIC int
_bcm_hx5_cosq_ingress_hdrm_pool_get(int unit, bcm_gport_t gport,
                                   bcm_cos_t pri,
                                   int *p_hdrm_pool_start,
                                   int *p_hdrm_pool_end)
{
    int local_port;
    uint32 rval, hdrm_pool;
    int pri_grp;
    static const soc_field_t prigroup_hpid_field[] = {
        PG0_HPIDf, PG1_HPIDf, PG2_HPIDf, PG3_HPIDf,
        PG4_HPIDf, PG5_HPIDf, PG6_HPIDf, PG7_HPIDf
    };

    if (pri == BCM_COS_INVALID) {
        if (p_hdrm_pool_start && p_hdrm_pool_end) {
            *p_hdrm_pool_start = 0;
            *p_hdrm_pool_end = 3;
            return BCM_E_NONE;
        } else {
            return BCM_E_PARAM;
        }
    }

    if ((pri < 0) || (pri >= _HX5_MMU_NUM_INT_PRI)) {
        /* Error. Input pri > Max Pri_Grp */
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_ingress_pg_get(unit, gport, pri, &pri_grp, &pri_grp));

    BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));

    if (!SOC_PORT_VALID(unit, local_port)) {
        return BCM_E_PORT;
    }

    if (pri_grp >= _HX5_MMU_NUM_PG) {
        return BCM_E_PARAM;
    }

    SOC_IF_ERROR_RETURN(READ_THDI_HDRM_PORT_PG_HPIDr(unit, local_port, &rval));
    hdrm_pool = soc_reg_field_get(unit, THDI_HDRM_PORT_PG_HPIDr, rval,
                                  prigroup_hpid_field[pri_grp]);

    if (p_hdrm_pool_start) {
        *p_hdrm_pool_start = hdrm_pool;
    }
    if (p_hdrm_pool_end) {
        *p_hdrm_pool_end = hdrm_pool;
    }

    return BCM_E_NONE;
}


/*
 * This function is used to set headroom pool
 * or shared pool for given Ingress [Port, Priority]
 */
STATIC int
_bcm_hx5_cosq_ing_pool_set(int unit, bcm_gport_t gport, bcm_cos_t pri,
                          bcm_cosq_control_t type, int arg)
{
    int local_port;
    uint32 rval;
    int pri_grp;
    static const soc_field_t prigroup_spid_field[] = {
        PG0_SPIDf, PG1_SPIDf, PG2_SPIDf, PG3_SPIDf,
        PG4_SPIDf, PG5_SPIDf, PG6_SPIDf, PG7_SPIDf
    };
    static const soc_field_t prigroup_hpid_field[] = {
        PG0_HPIDf, PG1_HPIDf, PG2_HPIDf, PG3_HPIDf,
        PG4_HPIDf, PG5_HPIDf, PG6_HPIDf, PG7_HPIDf
    };
    pri = pri % 8;

    if((arg < 0) || (arg >= _HX5_MMU_NUM_POOL)) {
            return BCM_E_PARAM;
    }

    if ((pri < 0) || (pri >= _HX5_MMU_NUM_INT_PRI)) {
        /* Error. Input pri > Max Pri_Grp */
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
        BCM_GPORT_IS_SCHEDULER(gport) ||
        BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));

    if (!SOC_PORT_VALID(unit, local_port)) {
        return BCM_E_PORT;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_ingress_pg_get(unit, gport, pri, &pri_grp, &pri_grp));

    /* coverity fix : pri_grp can take value from 0 to 7 */
    if ((pri_grp < 0) || (pri_grp >= _HX5_MMU_NUM_PG)) {
        return BCM_E_PARAM;
    }

    if (type == bcmCosqControlIngressPool) {
        SOC_IF_ERROR_RETURN(READ_THDI_PORT_PG_SPIDr(unit, local_port, &rval));
        soc_reg_field_set(unit, THDI_PORT_PG_SPIDr, &rval,
                          prigroup_spid_field[pri_grp],arg);
        BCM_IF_ERROR_RETURN(WRITE_THDI_PORT_PG_SPIDr(unit, local_port, rval));
    } else if (type == bcmCosqControlIngressHeadroomPool) {
        SOC_IF_ERROR_RETURN(READ_THDI_HDRM_PORT_PG_HPIDr(unit, local_port, &rval));
        soc_reg_field_set(unit, THDI_HDRM_PORT_PG_HPIDr, &rval,
                          prigroup_hpid_field[pri_grp], arg);
        BCM_IF_ERROR_RETURN(WRITE_THDI_HDRM_PORT_PG_HPIDr(unit, local_port, rval));
    } else {
        return BCM_E_PARAM;
    }
    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_ing_pool_get(int unit, bcm_gport_t gport,
                          bcm_cos_t pri,
                          bcm_cosq_control_t type, int *arg)
{
    int pool_start_idx = 0, pool_end_idx = 0;
    pri = pri % 8;

    if (arg == NULL) {
        return BCM_E_PARAM;
    }

    if ((pri < 0) || (pri >= _HX5_MMU_NUM_INT_PRI)) {
        /* Error. Input pri > Max Pri_Grp */
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
        BCM_GPORT_IS_SCHEDULER(gport) ||
        BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        return BCM_E_PARAM;
    }

    if (type == bcmCosqControlIngressPool) {
        BCM_IF_ERROR_RETURN(
            _bcm_hx5_cosq_ingress_sp_get(unit, gport, pri,
                                        &pool_start_idx,
                                        &pool_end_idx));
    } else if (type == bcmCosqControlIngressHeadroomPool) {
        BCM_IF_ERROR_RETURN(
            _bcm_hx5_cosq_ingress_hdrm_pool_get(unit, gport, pri,
                                               &pool_start_idx,
                                               &pool_end_idx));
    } else {
        return BCM_E_PARAM;
    }
    *arg = pool_start_idx;
    return BCM_E_NONE;
}


STATIC _bcm_bst_cb_ret_t
_bcm_hx5_bst_index_resolve(int unit, bcm_gport_t gport, bcm_cos_queue_t cosq,
                          bcm_bst_stat_id_t bid, int *pipe, int *start_hw_index,
                          int *end_hw_index, int *rcb_data, void **cb_data, int *bcm_rv)
{
    int phy_port, mmu_port, local_port;
    int mmu_port_base = 0;
    int pool_idx = 0;
    uint32 rval = 0;
    _bcm_hx5_cosq_node_t *node = NULL;
    soc_info_t *si;

    *bcm_rv = _bcm_hx5_cosq_localport_resolve(unit, gport, &local_port);

    if (BCM_E_NONE != (*bcm_rv)) {
        goto error;
    }

    si = &SOC_INFO(unit);
    phy_port = si->port_l2p_mapping[local_port];
    mmu_port = si->port_p2m_mapping[phy_port];

    *pipe = mmu_port / SOC_HX5_MMU_PORT_STRIDE;

    if (bid == bcmBstStatIdDevice) {
        *start_hw_index = *end_hw_index = 0;
        *bcm_rv = BCM_E_NONE;
        return _BCM_BST_RV_OK;
    }

    if ((bid == bcmBstStatIdEgrPool) || (bid == bcmBstStatIdEgrMCastPool)) {
        if(_bcm_hx5_cosq_egress_sp_get(unit, gport, cosq, start_hw_index,
                    end_hw_index)) {
            goto error;
        }
        return _BCM_BST_RV_OK;
    } else if (bid == bcmBstStatIdHeadroomPool) {
        cosq = cosq % 8;
        /* ingress headroom pool */
        if (_bcm_hx5_cosq_ingress_hdrm_pool_get(unit, gport, cosq,
                    start_hw_index, end_hw_index)) {
            goto error;
        }
        return _BCM_BST_RV_OK;
    } else if (bid == bcmBstStatIdIngPool) {
        cosq = cosq % 8;
        /* ingress pool */
        if (_bcm_hx5_cosq_ingress_sp_get(unit, gport, cosq,
                    start_hw_index, end_hw_index)) {
            goto error;
        }
        return _BCM_BST_RV_OK;
    } else if (bid == bcmBstStatIdRQEPool) {
        /* RQE pool */
        if (cosq == BCM_COS_INVALID) {
            *start_hw_index = 0;
            *end_hw_index = _HX5_MMU_NUM_POOL - 1;
        } else if ((cosq < 0) || (cosq >= _HX5_MMU_NUM_POOL)) {
            return BCM_E_PARAM;
        } else {
            SOC_IF_ERROR_RETURN
                (READ_MMU_THDR_DB_CONFIG1_PRIQr(unit, cosq, &rval));

            pool_idx = soc_reg_field_get(unit, MMU_THDR_DB_CONFIG1_PRIQr, rval,
                    SPIDf);
            *start_hw_index = *end_hw_index = pool_idx;
        }
        return _BCM_BST_RV_OK;
    } else if (bid == bcmBstStatIdRQEQueue) {
        /* RQE queue */
        if (cosq == BCM_COS_INVALID) {
            *start_hw_index = 0;
            *end_hw_index = _HX5_MMU_NUM_RQE_QUEUES - 1;
        } else if ((cosq < 0) || (cosq >= _HX5_MMU_NUM_RQE_QUEUES)) {
            return BCM_E_PARAM;
        } else {
            *start_hw_index = *end_hw_index = cosq;
        }
        return _BCM_BST_RV_OK;
    } else if (bid == bcmBstStatIdUCQueueGroup) {
        /* unicast queue group */
        mmu_port_base = SOC_HX5_MMU_PORT_STRIDE * (*pipe);
        *start_hw_index = *end_hw_index = mmu_port - mmu_port_base;
        return _BCM_BST_RV_OK;
    }


    if (bid == bcmBstStatIdPortPool) {
        cosq = cosq % 8;
        /* ingress pool */
        if (_bcm_hx5_cosq_ingress_sp_get(unit, gport, cosq,
                                        start_hw_index, end_hw_index)) {
            goto error;
        }
        *start_hw_index = ((mmu_port & SOC_HX5_MMU_PORT_STRIDE) * 4) +
                          *start_hw_index;
        *end_hw_index = ((mmu_port & SOC_HX5_MMU_PORT_STRIDE) * 4) +
                        *end_hw_index;
    } else if ((bid == bcmBstStatIdPriGroupShared) ||
               (bid == bcmBstStatIdPriGroupHeadroom)) {
        cosq = cosq % 8;
        /* ingress PG */
        if (_bcm_hx5_cosq_ingress_pg_get(unit, gport, cosq,
                                        start_hw_index, end_hw_index)) {
            goto error;
        }
        *start_hw_index = ((mmu_port & SOC_HX5_MMU_PORT_STRIDE) * 8) +
                          *start_hw_index;
        *end_hw_index = ((mmu_port & SOC_HX5_MMU_PORT_STRIDE) * 8) +
                        *end_hw_index;
    } else if (bid == bcmBstStatIdEgrPortPoolSharedUcast ||
               bid == bcmBstStatIdEgrPortPoolSharedMcast) {
        /* egress pool */
        if (_bcm_hx5_cosq_egress_sp_get(unit, gport, cosq,
                                       start_hw_index, end_hw_index)) {
            goto error;
        }
        *start_hw_index = ((mmu_port & SOC_HX5_MMU_PORT_STRIDE) * 4) +
                          *start_hw_index;
        *end_hw_index = ((mmu_port & SOC_HX5_MMU_PORT_STRIDE) * 4) +
                        *end_hw_index;
    } else {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            if (bid != bcmBstStatIdUcast) {
                goto error;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_node_get(unit, gport, NULL,
                                       &local_port, NULL, &node));
            if (!node) {
                goto error;
            }
            *start_hw_index =  node->hw_index; 
            *end_hw_index = *start_hw_index;
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            if (bid != bcmBstStatIdMcast) {
                goto error;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_node_get(unit, gport, NULL,
                                       &local_port, NULL, &node));
            if (!node) {
                goto error;
            }
            if (IS_CPU_PORT(unit, local_port)) {
                *start_hw_index = si->port_cosq_base[CMIC_PORT(unit)] + cosq;
            } else {
                *start_hw_index =  node->hw_index;
            }
            *end_hw_index = *start_hw_index;
        } else {
            if (cosq < 0) {
                if (bid == bcmBstStatIdUcast) {
                    if (IS_LB_PORT(unit, local_port)) {
                        goto error;
                    }
                    *start_hw_index = si->port_uc_cosq_base[local_port];
                    *end_hw_index = *start_hw_index +
                                    si->port_num_uc_cosq[local_port] - 1;
                } else {
                    if (IS_CPU_PORT(unit, local_port)) {
                        *start_hw_index = si->port_cosq_base[CMIC_PORT(unit)];
                        *end_hw_index = *start_hw_index +
                                         SOC_HX5_NUM_CPU_QUEUES - 1;
                    } else {
                        *start_hw_index =  si->port_cosq_base[local_port];
                        *end_hw_index = *start_hw_index +
                            si->port_num_cosq[local_port] - 1;
                    }
                }
            } else {
                if (bid == bcmBstStatIdUcast) {
                    if (IS_LB_PORT(unit, local_port)) {
                        goto error;
                    }
                    *start_hw_index = si->port_uc_cosq_base[local_port] + cosq;
                    *end_hw_index = *start_hw_index;
                } else {
                    if (IS_CPU_PORT(unit, local_port)) {
                        *start_hw_index = si->port_cosq_base[CMIC_PORT(unit)] + cosq;
                    } else {
                        *start_hw_index = si->port_cosq_base[local_port] + cosq;
                    }
                    *end_hw_index = *start_hw_index;
                }
            }
        }
    }

    *bcm_rv = BCM_E_NONE;
    return _BCM_BST_RV_OK;

error:
    *bcm_rv = BCM_E_PARAM;
    return _BCM_BST_RV_ERROR;
}

/*
 * Function:
 *     _bcm_hx5_cosq_bucket_get
 * Purpose:
 *     Get COS queue bandwidth control bucket setting
 * Parameters:
 *     unit          - (IN) unit number
 *     gport         - (IN) port number or GPORT identifier
 *     cosq          - (IN) COS queue number
 *     min_quantum   - (OUT) kbps or packet/second
 *     max_quantum   - (OUT) kbps or packet/second
 *     burst_quantum - (OUT) kbps or packet/second
 *     flags         - (IN) BCM_COSQ_BW_XXX
 * Returns:
 *     BCM_E_XXX
 * Notes:
 *     If port is any form of local port, cosq is the hardware queue index.
 */
STATIC int
_bcm_hx5_cosq_bucket_get(int unit, bcm_port_t gport, bcm_cos_queue_t cosq,
                        uint32 *min_quantum, uint32 *max_quantum,
                        uint32 *kbits_burst_min, uint32 *kbits_burst_max,
                        uint32 *flags)
{
    _bcm_hx5_cosq_node_t *node = NULL;
    bcm_port_t local_port;
    uint32 rval;
    uint32 refresh_rate, bucketsize, granularity, meter_flags;
    int pipe = 0, phy_port, mmu_port, index = 0;

    soc_mem_t config_mem = INVALIDm;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_info_t *si;

    if (cosq < 0) {
        if (cosq == -1) {
            /* caller needs to resolve the wild card value (-1) */
            return BCM_E_INTERNAL;
        } else { /* reject all other negative value */
            return BCM_E_PARAM;
        }
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));

    si = &SOC_INFO(unit);
    phy_port = si->port_l2p_mapping[local_port];
    mmu_port = si->port_p2m_mapping[phy_port];

    if (BCM_GPORT_IS_SET(gport) &&
        ((BCM_GPORT_IS_SCHEDULER(gport)) ||
          BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
          BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport))) { 

        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_node_get(unit, gport, NULL, NULL, NULL, &node));
    }

    if (node) {
        if (BCM_GPORT_IS_SCHEDULER(gport)) {
            if (node->level == SOC_HX5_NODE_LVL_L0) {
                config_mem = SOC_MEM_UNIQUE_ACC(unit, MMU_MTRO_L0_MEMm)[pipe];
                index = node->hw_index;
            } else if(node->level == SOC_HX5_NODE_LVL_L1) {
                config_mem = SOC_MEM_UNIQUE_ACC(unit, MMU_MTRO_L1_MEMm)[pipe];
                index = node->hw_index;
            } else if(node->level == SOC_HX5_NODE_LVL_L2) {
                config_mem = SOC_MEM_UNIQUE_ACC(unit, MMU_MTRO_L2_MEMm)[pipe];
                index = node->hw_index;
            } else {
                return BCM_E_PARAM;
            }
        } else if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
                   BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            config_mem = SOC_MEM_UNIQUE_ACC(unit, MMU_MTRO_L3_MEMm)[pipe];

            if (IS_CPU_PORT(unit, local_port)) {
                cosq = node->hw_index -  SOC_HX5_CPU_MCQ_BASE;
                /* For CPU port's MC queue starting index: 2570 */
                index =  _BCM_HX5_MMU_L3_MC_CPU_QBASE + cosq;
            } else if (IS_LB_PORT(unit, local_port)) {
                cosq = node->hw_index - SOC_HX5_LB_MCQ_BASE;
                index = _BCM_HX5_MMU_L3_MC_LB_QBASE + cosq;
            } else {
                index = node->hw_index;
                if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
                     index =  node->hw_index + SOC_HX5_NUM_UC_QUEUES_PER_PIPE;
                }
            }
        } else {
            return BCM_E_PARAM;
        }
    } else {
        if ((cosq < 0) || (cosq >= si->port_num_cosq[local_port])) {
            return BCM_E_PARAM;
        }
        if (IS_CPU_PORT(unit, local_port)) {
            /* For CPU port, refer L3 memory (logical queue, starting index 2570)
             * directly */
            config_mem = SOC_MEM_UNIQUE_ACC(unit, MMU_MTRO_L3_MEMm)[pipe];
            index = _BCM_HX5_MMU_L3_MC_CPU_QBASE + cosq;
        } else if (IS_LB_PORT(unit, local_port)) {
            config_mem = SOC_MEM_UNIQUE_ACC(unit, MMU_MTRO_L3_MEMm)[pipe];
            index = _BCM_HX5_MMU_L3_MC_LB_QBASE + cosq;
        } else {
            if (_HX5_IS_ST_PORT(unit, mmu_port)) {
                index = (mmu_port * SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT) + cosq;
            } else {
                index = SOC_HX5_DOWNLINK_PORTQ_BASE + ((mmu_port - 16) * SOC_HX5_NUM_UCAST_QUEUE_PER_PORT) + cosq;
            }
            config_mem = SOC_MEM_UNIQUE_ACC(unit, MMU_MTRO_L2_MEMm)[pipe];
        }
    }

    /*
     * COVERITY
     *
     * This checker will not be True.
     * It is kept intentionally as a defensive case for future development.
     */
    /* coverity[dead_error_line] */
    if (config_mem == INVALIDm) {
        return BCM_E_PARAM;
    }

    if (min_quantum == NULL || max_quantum == NULL ||
        kbits_burst_max == NULL || kbits_burst_min == NULL) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (soc_mem_read(unit, config_mem, MEM_BLOCK_ALL, index, &entry));

    meter_flags = 0;
    *flags = 0;
    BCM_IF_ERROR_RETURN(READ_MMU_SEDCFG_MISCCONFIGr(unit, &rval));
    if (soc_reg_field_get(unit, MMU_SEDCFG_MISCCONFIGr, rval, ITU_MODE_SELf)) {
        meter_flags |= _BCM_TD_METER_FLAG_NON_LINEAR;
    }
    if (soc_mem_field32_get(unit, config_mem, &entry, SHAPER_CONTROLf)) {
        meter_flags |= _BCM_TD_METER_FLAG_PACKET_MODE;
        *flags |= BCM_COSQ_BW_PACKET_MODE;
    }
    if (soc_mem_field32_get(unit, config_mem, &entry, EAV_ENABLEf)) {
        *flags |= BCM_COSQ_BW_EAV_MODE;
    }

    granularity = soc_mem_field32_get(unit, config_mem, &entry, MAX_METER_GRANf);
    refresh_rate = soc_mem_field32_get(unit, config_mem, &entry, MAX_REFRESHf);
    bucketsize = soc_mem_field32_get(unit, config_mem, &entry, MAX_THD_SELf);
    BCM_IF_ERROR_RETURN
        (_bcm_td_bucket_encoding_to_rate(unit, refresh_rate, bucketsize,
                                           granularity, meter_flags,
                                           max_quantum, kbits_burst_max));

    granularity = soc_mem_field32_get(unit, config_mem, &entry, MIN_METER_GRANf);
    refresh_rate = soc_mem_field32_get(unit, config_mem, &entry, MIN_REFRESHf);
    bucketsize = soc_mem_field32_get(unit, config_mem, &entry, MIN_THD_SELf);
    BCM_IF_ERROR_RETURN
        (_bcm_td_bucket_encoding_to_rate(unit, refresh_rate, bucketsize,
                                           granularity, meter_flags,
                                           min_quantum, kbits_burst_min));
    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_egr_pool_mcshrd_limit_val(int unit, int pool, int new_limit)
{
    int total_avail_mcq = _HX5_MMU_TOTAL_MCQ_ENTRY(unit);
    uint32 total_qmin_limit = 0;
    int total_shrd_limit = 0;
    int total_mcq = 0;
    uint32 cpu_cnt = 1, lb_cnt = 2, mgmt_cnt = 1, num_ports = 0;
    int port, pm, pipe, startq;
    soc_info_t *si = &SOC_INFO(unit);
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm;
    bcm_pbmp_t pbmp;
    int spid, i;
    int active_sp[_HX5_MMU_NUM_POOL] = {FALSE};
    uint32 rval;
    int granularity = 4;
    soc_reg_t reg;

    /* Calculate total available MCQE */
    if (si->flex_eligible) {
        for (pm = 0; pm < _HX5_PBLKS_PER_DEV(unit); pm++) {
            num_ports += soc_hx5_ports_per_pm_get(unit, pm);
        }
        total_mcq += (num_ports * SOC_HX5_NUM_MCAST_QUEUE_PER_PORT);
    } else {
        PBMP_ALL_ITER(unit, port) {
            if (IS_CPU_PORT(unit, port) ||
                IS_LB_PORT(unit, port) ||
                IS_FAE_PORT(unit, port) ||
                IS_MANAGEMENT_PORT(unit, port)) {
                continue;
            }
            total_mcq += si->port_num_cosq[port];
        }
    }
    total_mcq += ((cpu_cnt * SOC_HX5_NUM_CPU_QUEUES) +
                  (lb_cnt + mgmt_cnt) * SOC_HX5_NUM_MCAST_QUEUE_PER_PORT);
    total_avail_mcq -= ((total_mcq * _HX5_MCQE_RSVD_PER_MCQ) +
                         _HX5_TDM_MCQE_RSVD_OVERSHOOT);

    BCM_PBMP_ASSIGN(pbmp, PBMP_PORT_ALL(unit));
    BCM_PBMP_ITER(pbmp, port) {
        SOC_IF_ERROR_RETURN(soc_port_pipe_get(unit, port, &pipe));
        mem = SOC_MEM_UNIQUE_ACC(unit, MMU_THDM_MCQE_QUEUE_CONFIGm)[pipe];
        for (i = 0; i < NUM_COS(unit); i++) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, port, i,
                                             _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                             NULL, &startq, NULL));
            BCM_IF_ERROR_RETURN
                (soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));

            /* Calculate total MIN of MC QEntries */
            total_qmin_limit += soc_mem_field32_get(unit, mem, entry,
                                                    Q_MIN_LIMITf);

            /* Get active egress MCQE service pools */
            spid = soc_mem_field32_get(unit, mem, entry, Q_SPIDf);
            active_sp[spid] = TRUE;
        }
    }

    /* Total service pool size */
    reg = MMU_THDM_MCQE_POOL_SHARED_LIMITr;
    for (i = 0; i < _HX5_MMU_NUM_POOL; i++) {
        if ((i != pool) && (active_sp[i] == TRUE)) {
            BCM_IF_ERROR_RETURN(soc_reg32_get(unit, reg, REG_PORT_ANY, i, &rval));
            total_shrd_limit += soc_reg_field_get(unit, reg, rval, SHARED_LIMITf);
        }
    }
    total_shrd_limit *= granularity;
    total_shrd_limit += new_limit;

    if ((total_qmin_limit + total_shrd_limit) > total_avail_mcq) {
        return BCM_E_PARAM;
    }

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_egr_pool_mcshrd_thresh_adjust(int unit, int pool, int new_limit,
                                            bcm_port_t port)
{
    soc_reg_t reg = MMU_THDM_MCQE_POOL_SHARED_LIMITr;
    int granularity = 4;
    int cur_val;
    uint32 rval;
    soc_reg_t ctr_reg;
    soc_ctr_control_info_t ctrl_info;
    uint8 allowed = FALSE;
    uint8 increase = TRUE;
    int new_resume_limit;
    int delta;

    BCM_IF_ERROR_RETURN(soc_reg32_get(unit, reg, REG_PORT_ANY, pool, &rval));
    cur_val = soc_reg_field_get(unit, reg, rval, SHARED_LIMITf);

    /* Do occupancy check if new_limit less than current_limit */
    if (sal_ceil_func(new_limit, granularity) < cur_val) {
        delta = cur_val * granularity - new_limit;
        increase = FALSE;
        ctrl_info.instance_type = SOC_CTR_INSTANCE_TYPE_XPE;
        ctrl_info.instance = port;
        ctr_reg = SOC_COUNTER_NON_DMA_EGRESS_MCQE_POOL_CURRENT;
        BCM_IF_ERROR_RETURN
            (soc_hx5_cosq_threshold_dynamic_change_check(unit, new_limit,
                                                         ctr_reg, ctrl_info, pool,
                                                         TRUE, &allowed));
    } else {
        delta = new_limit - cur_val * granularity;
    }

    soc_reg_field_set(unit, reg, &rval, SHARED_LIMITf,
                      sal_ceil_func(new_limit, granularity));
    BCM_IF_ERROR_RETURN(soc_reg32_set(unit, reg, REG_PORT_ANY, pool, rval));

    /* Adjust egress MCQE pool resume limit */
    reg = MMU_THDM_MCQE_POOL_RESUME_LIMITr;
    rval = 0;
    granularity = 8;
    BCM_IF_ERROR_RETURN(soc_reg32_get(unit, reg, REG_PORT_ANY, pool, &rval));
    cur_val = soc_reg_field_get(unit, reg, rval, RESUME_LIMITf);
    if (increase == TRUE) {
        new_resume_limit = cur_val * granularity + delta;
    } else {
        new_resume_limit = cur_val * granularity - delta;
    }
    soc_reg_field_set(unit, reg, &rval, RESUME_LIMITf,
                      sal_ceil_func(new_resume_limit, granularity));
    BCM_IF_ERROR_RETURN(soc_reg32_set(unit, reg, REG_PORT_ANY, pool, rval));

    return BCM_E_NONE;
}
/*
 * Function:
 *     _bcm_hx5_cosq_bucket_set
 * Purpose:
 *     Configure COS queue bandwidth control bucket
 * Parameters:
 *     unit          - (IN) unit number
 *     gport         - (IN) port number or GPORT identifier
 *     cosq          - (IN) COS queue number
 *     min_quantum   - (IN) kbps or packet/second
 *     max_quantum   - (IN) kbps or packet/second
 *     burst_quantum - (IN) kbps or packet/second
 *     flags         - (IN) BCM_COSQ_BW_XXX
 * Returns:
 *     BCM_E_XXX
 * Notes:
 *     If port is any form of local port, cosq is the hardware queue index.
 */
STATIC int
_bcm_hx5_cosq_bucket_set(int unit, bcm_gport_t gport, bcm_cos_queue_t cosq,
                        uint32 min_quantum, uint32 max_quantum,
                        uint32 kbits_burst_min, uint32 kbits_burst_max,
                        uint32 flags)
{
    _bcm_hx5_cosq_node_t *node = NULL;
    bcm_port_t local_port;
    uint32 rval, meter_flags;
    uint32 bucketsize_max, bucketsize_min;
    uint32 granularity_max, granularity_min;
    uint32 refresh_rate_max, refresh_rate_min;
    int refresh_bitsize = 0, bucket_bitsize = 0;
    int pipe = 0, phy_port, mmu_port, index = 0;
    soc_mem_t config_mem = INVALIDm;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_info_t *si;

    /* caller should resolve the cosq. */
    if (cosq < 0) {
        if (cosq == -1) {
            /* caller needs to resolve the wild card value (-1) */
            return BCM_E_INTERNAL;
        } else { /* reject all other negative value */
            return BCM_E_PARAM;
        }
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));

    si = &SOC_INFO(unit);
    phy_port = si->port_l2p_mapping[local_port];
    mmu_port = si->port_p2m_mapping[phy_port];

    if (BCM_GPORT_IS_SET(gport) &&
        ((BCM_GPORT_IS_SCHEDULER(gport)) ||
          BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
          BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport))) { 

        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_node_get(unit, gport, NULL, NULL, NULL, &node));
    }

    if (node) {
        if (BCM_GPORT_IS_SCHEDULER(gport)) {
            if (node->level == SOC_HX5_NODE_LVL_L0) {
                config_mem = SOC_MEM_UNIQUE_ACC(unit, MMU_MTRO_L0_MEMm)[pipe];
                index = node->hw_index;
            } else if(node->level == SOC_HX5_NODE_LVL_L1) {
                config_mem = SOC_MEM_UNIQUE_ACC(unit, MMU_MTRO_L1_MEMm)[pipe];
                index = node->hw_index;
            } else if(node->level == SOC_HX5_NODE_LVL_L2) {
                config_mem = SOC_MEM_UNIQUE_ACC(unit, MMU_MTRO_L2_MEMm)[pipe];
                index = node->hw_index;
            } else {
                return BCM_E_PARAM;
            }
        } else if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
                   BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            config_mem = SOC_MEM_UNIQUE_ACC(unit, MMU_MTRO_L3_MEMm)[pipe];
            if (IS_CPU_PORT(unit, local_port)) {
                /* For CPU port, refer L3 memory (logical queue, starting index 2570)
                 * directly */
                index = _BCM_HX5_MMU_L3_MC_CPU_QBASE + (cosq - SOC_HX5_CPU_MCQ_BASE);
            } else if (IS_LB_PORT(unit, local_port)) {
                index = _BCM_HX5_MMU_L3_MC_LB_QBASE + cosq;
            } else {
                index = node->hw_index;
                if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
                     index =  node->hw_index + SOC_HX5_NUM_UC_QUEUES_PER_PIPE;
                }
            }
       } else {
            return BCM_E_PARAM;
       }
    } else {
        if ((cosq < 0) || (cosq >= si->port_num_cosq[local_port])) {
            return BCM_E_PARAM;
        }
        if (IS_CPU_PORT(unit, local_port)) {
            /* For CPU port, refer L1 memory (logical queue, starting index 1300)
             * directly */
            config_mem = SOC_MEM_UNIQUE_ACC(unit, MMU_MTRO_L3_MEMm)[pipe];
            index = _BCM_HX5_MMU_L3_MC_CPU_QBASE + cosq;
        } else if (IS_LB_PORT(unit, local_port)) {
            config_mem = SOC_MEM_UNIQUE_ACC(unit, MMU_MTRO_L3_MEMm)[pipe];
            index = _BCM_HX5_MMU_L3_MC_LB_QBASE + cosq;
        } else {
            if (_HX5_IS_ST_PORT(unit, mmu_port)) {
                index = (mmu_port * SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT) + cosq;
            } else {
                index = SOC_HX5_DOWNLINK_PORTQ_BASE + ((mmu_port - 16) * SOC_HX5_NUM_UCAST_QUEUE_PER_PORT) + cosq;
            }
            config_mem = SOC_MEM_UNIQUE_ACC(unit, MMU_MTRO_L2_MEMm)[pipe];
        }
    }

    /*
     * COVERITY
     *
     * This checker will not be True.
     * It is kept intentionally as a defensive check for future development.
     */
    /* coverity[dead_error_line] */
    if (config_mem == INVALIDm) {
        return BCM_E_PARAM;
    }

    meter_flags = flags & BCM_COSQ_BW_PACKET_MODE ?
                            _BCM_TD_METER_FLAG_PACKET_MODE : 0;
    BCM_IF_ERROR_RETURN(READ_MMU_SEDCFG_MISCCONFIGr(unit, &rval));

    if (soc_reg_field_get(unit, MMU_SEDCFG_MISCCONFIGr, rval, ITU_MODE_SELf)) {
        meter_flags |= _BCM_TD_METER_FLAG_NON_LINEAR;
    }

    refresh_bitsize = soc_mem_field_length(unit, config_mem, MAX_REFRESHf);
    bucket_bitsize = soc_mem_field_length(unit, config_mem, MAX_THD_SELf);

    BCM_IF_ERROR_RETURN
        (_bcm_td_rate_to_bucket_encoding(unit, max_quantum, kbits_burst_max,
                                           meter_flags, refresh_bitsize,
                                           bucket_bitsize, &refresh_rate_max,
                                           &bucketsize_max, &granularity_max));

    BCM_IF_ERROR_RETURN
        (_bcm_td_rate_to_bucket_encoding(unit, min_quantum, kbits_burst_min,
                                           meter_flags, refresh_bitsize,
                                           bucket_bitsize, &refresh_rate_min,
                                           &bucketsize_min, &granularity_min));

    sal_memset(entry, 0, sizeof(uint32)*SOC_MAX_MEM_WORDS);

    soc_mem_field32_set(unit, config_mem, &entry, MAX_METER_GRANf, granularity_max);
    soc_mem_field32_set(unit, config_mem, &entry, MAX_REFRESHf, refresh_rate_max);
    soc_mem_field32_set(unit, config_mem, &entry, MAX_THD_SELf, bucketsize_max);

    soc_mem_field32_set(unit, config_mem, &entry, MIN_METER_GRANf, granularity_min);
    soc_mem_field32_set(unit, config_mem, &entry, MIN_REFRESHf, refresh_rate_min);
    soc_mem_field32_set(unit, config_mem, &entry, MIN_THD_SELf, bucketsize_min);

    soc_mem_field32_set(unit, config_mem, &entry, SHAPER_CONTROLf,
                        (flags & BCM_COSQ_BW_PACKET_MODE) ? 1 : 0);
    soc_mem_field32_set(unit, config_mem, &entry, EAV_ENABLEf,
                        (flags & BCM_COSQ_BW_EAV_MODE) ? 1 : 0);

    BCM_IF_ERROR_RETURN
        (soc_mem_write(unit, config_mem, MEM_BLOCK_ALL, index, &entry));

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_gport_bandwidth_burst_set
 * Purpose:
 *     Configure COS queue bandwidth burst setting
 * Parameters:
 *      unit        - (IN) unit number
 *      gport       - (IN) GPORT identifier
 *      cosq        - (IN) COS queue to configure, -1 for all COS queues
 *      kbits_burst - (IN) maximum burst, kbits
 * Returns:
 *      BCM_E_XXX
 */
int
bcm_hx5_cosq_gport_bandwidth_burst_set(int unit, 
                                      bcm_gport_t gport,
                                      bcm_cos_queue_t cosq,
                                      uint32 kbits_burst_min,
                                      uint32 kbits_burst_max)
{
    int i, start_cos=0, end_cos=0;
    uint32 kbits_sec_min, kbits_sec_max, kbits_sec_burst, flags;
    bcm_port_t local_port;
    _bcm_hx5_cosq_node_t *node = NULL;
    int phy_port, mmu_port;


    soc_info_t *si = &SOC_INFO(unit);

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));

    phy_port = si->port_l2p_mapping[local_port];
    mmu_port = si->port_p2m_mapping[phy_port];
    start_cos = end_cos = cosq;

    if (cosq == BCM_COS_INVALID) {
        start_cos = 0;
        if (IS_CPU_PORT(unit, local_port)) {
           end_cos =  NUM_CPU_COSQ(unit); 
        } else if(_HX5_IS_ST_PORT(unit, mmu_port)) {
           end_cos = SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT; 
        } else {
           end_cos = SOC_HX5_NUM_UCAST_QUEUE_PER_PORT; 
        }
    }

    if (BCM_GPORT_IS_SET(gport)) {
        if ((BCM_GPORT_IS_SCHEDULER(gport)) ||
             BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
             BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_node_get(unit, gport, NULL, NULL, NULL, &node));
                start_cos = end_cos = node->hw_index;
        }
    }

    for (i = start_cos; i <= end_cos; i++) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_bucket_get(unit, gport, i, &kbits_sec_min,
                                     &kbits_sec_max, &kbits_sec_burst,
                                     &kbits_sec_burst, &flags));
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_bucket_set(unit, gport, i, kbits_sec_min,
                                     kbits_sec_max, kbits_burst_min,
                                     kbits_burst_max, flags));
    }
    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_gport_bandwidth_burst_get
 * Purpose:
 *     Get COS queue bandwidth burst setting
 * Parameters:
 *     unit        - (IN) unit number
 *     gport       - (IN) GPORT identifier
 *     cosq        - (IN) COS queue to get, -1 for Queue 0
 *     kbits_burst - (OUT) maximum burst, kbits
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_gport_bandwidth_burst_get(int unit, 
                                      bcm_gport_t gport,
                                      bcm_cos_queue_t cosq,
                                      uint32 *kbits_burst_min,
                                      uint32 *kbits_burst_max)
{
    uint32 kbits_sec_min, kbits_sec_max, flags;

    if (cosq < -1) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_bucket_get(unit, gport, cosq == -1 ? 0 : cosq,
                                 &kbits_sec_min, &kbits_sec_max, kbits_burst_min,
                                 kbits_burst_max, &flags));

    return BCM_E_NONE;
}

/*
 *   Function:
 *        _bcm_hx5_cosq_mapping_set
 *   Purpose:
 *       Set COS queue for the specified priority of an ingress port
 *   Parameters:
 *        unit     - (IN) unit number
 *        ing_port - (IN) ingress port
 *        priority - (IN) priority value to map
 *        flags    - (IN) BCM_COSQ_GPORT_XXX_QUEUE_GROUP
 *        gport    - (IN) queue group GPORT identifier
 *        cosq     - (IN) COS queue number
 *   Returns:
 *         BCM_E_XXX
 */
STATIC int
_bcm_hx5_cosq_mapping_set(int unit, bcm_port_t ing_port, bcm_cos_t priority,
        uint32 flags, bcm_gport_t gport, bcm_cos_queue_t cosq)
{
    bcm_port_t local_port, out_port;
    bcm_cos_queue_t hw_cosq;
    int rv, idx, numq;
    int port;
    soc_field_t field[3] = {INVALIDf, INVALIDf, INVALIDf}; /* [0]:UC, [1]:MC cos */
    int value[3] = {0, 0, 0};
    void *entries[1];
    cos_map_sel_entry_t cos_map_sel_entry;
    port_cos_map_entry_t cos_map_entries[_HX5_MMU_NUM_INT_PRI];
    uint32 old_index, new_index;
    soc_info_t *si;

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, ing_port, &local_port));

     si = &SOC_INFO(unit);

    if (gport != -1) {
        BCM_IF_ERROR_RETURN(_bcm_hx5_cosq_localport_resolve(unit, gport,
                    &out_port));
    }

    switch(flags) {
        case BCM_COSQ_GPORT_UCAST_QUEUE_GROUP:
            if (gport == -1) {
                hw_cosq = cosq;
            } else {
                if (!BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
                    return BCM_E_PARAM;
                }
                BCM_IF_ERROR_RETURN
                        (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                                     _BCM_HX5_COSQ_INDEX_STYLE_COS, &port, &hw_cosq, NULL));
                if (!IS_CPU_PORT(unit, port)) {
                    hw_cosq = hw_cosq - si->port_uc_cosq_base[port];
                }
            }
            hw_cosq = hw_cosq % 8;
            field[0] = UC_COS1f;
            field[1] = HG_COSf;
            value[0] = hw_cosq;
            value[1] = hw_cosq + 8;
            break;
        case BCM_COSQ_GPORT_MCAST_QUEUE_GROUP:
            if (gport == -1) {
                hw_cosq = cosq;
            } else {
                if (!BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
                    return BCM_E_PARAM;
                }
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                                 _BCM_HX5_COSQ_INDEX_STYLE_COS, &port, &hw_cosq, NULL));
                if (!IS_CPU_PORT(unit, port)) {
                    hw_cosq = hw_cosq - si->port_cosq_base[port];
                }
            }
            hw_cosq = hw_cosq % 8;
            field[0] = MC_COS1f;
            field[1] = HG_COSf;
            value[0] = hw_cosq;
            value[1] = hw_cosq + 8;
            break;
            case (BCM_COSQ_GPORT_UCAST_QUEUE_GROUP |
                    BCM_COSQ_GPORT_MCAST_QUEUE_GROUP):
                if (gport == -1) {
                    hw_cosq = cosq;
                } else {
                    return BCM_E_PARAM;
                }
                hw_cosq = hw_cosq % 8;
                field[0] = UC_COS1f;
                field[1] = MC_COS1f;
                field[2] = HG_COSf;
                value[0] = hw_cosq;
                value[1] = hw_cosq; 
                value[2] = hw_cosq + 8;
            break;
        default:
            return BCM_E_PARAM;
    }

    numq = _BCM_HX5_NUM_COS(unit);
    entries[0] = &cos_map_entries;
    BCM_IF_ERROR_RETURN
        (READ_COS_MAP_SELm(unit, MEM_BLOCK_ANY, local_port,
                           &cos_map_sel_entry));
    old_index = soc_mem_field32_get(unit, COS_MAP_SELm, &cos_map_sel_entry,
            SELECTf);
    old_index *= _HX5_MMU_NUM_INT_PRI;

    BCM_IF_ERROR_RETURN
        (soc_profile_mem_get(unit, _bcm_hx5_cos_map_profile[unit], old_index,
                             _HX5_MMU_NUM_INT_PRI, entries));

    for (idx = 0; idx < 3; idx++) {
        if (field[idx] != INVALIDf) {
            soc_mem_field32_set(unit, PORT_COS_MAPm, &cos_map_entries[priority],
                    field[idx], value[idx]);
        }
    }

    soc_mem_lock(unit, PORT_COS_MAPm);
    rv = soc_profile_mem_delete(unit, _bcm_hx5_cos_map_profile[unit],
            old_index);
    if (BCM_FAILURE(rv)) {
        soc_mem_unlock(unit, PORT_COS_MAPm);
        return rv;
    }

    rv = soc_profile_mem_add(unit, _bcm_hx5_cos_map_profile[unit], entries,
            _HX5_MMU_NUM_INT_PRI, &new_index);

    soc_mem_unlock(unit, PORT_COS_MAPm);
    if (BCM_FAILURE(rv)) {
        return rv;
    }

    soc_mem_field32_set(unit, COS_MAP_SELm, &cos_map_sel_entry, SELECTf,
            new_index / _HX5_MMU_NUM_INT_PRI);
    BCM_IF_ERROR_RETURN
        (WRITE_COS_MAP_SELm(unit, MEM_BLOCK_ANY, local_port,
                            &cos_map_sel_entry));

#ifndef BCM_COSQ_HIGIG_MAP_DISABLE
    if (IS_CPU_PORT(unit, local_port)) {
        BCM_IF_ERROR_RETURN
            (soc_mem_field32_modify(unit, COS_MAP_SELm,
                                    SOC_INFO(unit).cpu_hg_index, SELECTf,
                                    new_index / _HX5_MMU_NUM_INT_PRI));
    }
#endif /* BCM_COSQ_HIGIG_MAP_DISABLE */

   /* update the wireless part of the cos_map table */
    rv = bcm_hx5_wireless_cos_map_update(unit, numq);

    if (rv < 0) {
        return rv;
    }
    return BCM_E_NONE;
}

/*
 *   Function:
 *       _bcm_hx5_cosq_mapping_get
 *   Purpose:
 *      Determine which COS queue a given priority currently maps to.
 *   Parameters:
 *        unit     - (IN) unit number
 *        ing_port - (IN) ingress port
 *        priority - (IN) priority value to map
 *        flags    - (IN) BCM_COSQ_GPORT_XXX_QUEUE_GROUP
 *        gport    - (IN) queue group GPORT identifier
 *        cosq     - (OUT) COS queue number
 *    Returns:
 *       BCM_E_XXX
 **/
STATIC int
_bcm_hx5_cosq_mapping_get(int unit, bcm_port_t ing_port, bcm_cos_t priority,
        uint32 flags, bcm_gport_t *gport,
        bcm_cos_queue_t *cosq)
{
    bcm_port_t local_port;
    cos_map_sel_entry_t cos_map_sel_entry;
    _bcm_hx5_cosq_port_info_t *port_info = NULL;
    _bcm_hx5_cosq_st_port_info_t *stport_info = NULL;
    _bcm_hx5_cosq_cpu_port_info_t *cpu_port_info = NULL;
    _bcm_hx5_cosq_node_t *node;
    int ii, index;
    void *entry_p;
    bcm_cos_queue_t hw_cosq = BCM_COS_INVALID, node_cosq = BCM_COS_INVALID;
    int numq = -1;
    int phy_port, mmu_port, port_index;


    soc_info_t *si = &SOC_INFO(unit);

    if ((flags != BCM_COSQ_GPORT_UCAST_QUEUE_GROUP) &&
            (flags != BCM_COSQ_GPORT_MCAST_QUEUE_GROUP)) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, ing_port, &local_port));

    phy_port = si->port_l2p_mapping[local_port];
    mmu_port = si->port_p2m_mapping[phy_port];

    if (gport) {
        *gport = BCM_GPORT_INVALID;
    }

    *cosq = BCM_COS_INVALID;

    BCM_IF_ERROR_RETURN
        (READ_COS_MAP_SELm(unit, MEM_BLOCK_ANY, local_port,
                           &cos_map_sel_entry));
    index = soc_mem_field32_get(unit, COS_MAP_SELm, &cos_map_sel_entry,
            SELECTf);
    index *= _HX5_MMU_NUM_INT_PRI;

    entry_p = SOC_PROFILE_MEM_ENTRY(unit, _bcm_hx5_cos_map_profile[unit],
            port_cos_map_entry_t *, index + priority);

    if (IS_CPU_PORT(unit, local_port)) {
        cpu_port_info = &_bcm_hx5_cosq_cpu_port_info[unit][local_port];
        numq = SOC_HX5_NUM_CPU_QUEUES;
    } else {
        _HX5_PORT_INDEX_GET(unit, mmu_port, port_index);
        if (_HX5_IS_ST_PORT(unit, mmu_port)) {
            stport_info = &_bcm_hx5_cosq_st_port_info[unit][port_index];
            numq = SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT;
        } else {
            port_info = &_bcm_hx5_cosq_port_info[unit][port_index];
            numq = SOC_HX5_NUM_UCAST_QUEUE_PER_PORT;
        }
    }

    switch (flags) {
        case BCM_COSQ_GPORT_UCAST_QUEUE_GROUP:
            hw_cosq = soc_mem_field32_get(unit, PORT_COS_MAPm, entry_p,
                    UC_COS1f);
            if ((IS_CPU_PORT(unit, local_port) == FALSE) && (gport)) {
                for (ii = 0; ii < numq; ii++) {
                    if (_HX5_IS_ST_PORT(unit, mmu_port)) {
                        node = &stport_info->ucast[ii];
                    } else {
                        node = &port_info->ucast[ii];
                    }
                    if (node == NULL) {
                        return BCM_E_NOT_FOUND;
                    }
                    node_cosq = node->hw_index - si->port_uc_cosq_base[local_port];
                    if (node && (node_cosq == hw_cosq)) {
                        *gport = node->gport;
                        *cosq = hw_cosq % 8;
                        break;
                    }
                }
            } else {
                *cosq = hw_cosq;
            }
            break;
        case BCM_COSQ_GPORT_MCAST_QUEUE_GROUP:
            hw_cosq = soc_mem_field32_get(unit, PORT_COS_MAPm, entry_p,
                    MC_COS1f);
            if (gport) {
                for (ii = 0; ii < numq; ii++) {
                    if (IS_CPU_PORT(unit, local_port)) {
                        node = &cpu_port_info->mcast[ii];
                    } else {
                        if (_HX5_IS_ST_PORT(unit, mmu_port)) {
                            node = &stport_info->mcast[ii];
                        } else {
                            node = &port_info->mcast[ii];
                        }
                    }
                    if (!node) {
                        return BCM_E_NOT_FOUND;
                    }
                    if (IS_CPU_PORT(unit, local_port)) {
                        node_cosq = node->hw_index - _HX5_CPU_L2_NODE_BASE;
                    } else {
                        node_cosq = node->hw_index - si->port_cosq_base[local_port]; 
                    }
                    if (node_cosq == hw_cosq) {
                        *gport = node->gport;
                        *cosq = hw_cosq % 8;
                        break;
                    }
                }
            } else {
                *cosq = hw_cosq;
            }
            break;
            /*
             * COVERITY
             *
             *This default is unreachable. It is kept intentionally
             *as a defensive default for future development.
             */
            /* coverity[dead_error_begin] */
        default:
            return BCM_E_PARAM;
    }

    if (((gport &&
                    (*gport == BCM_GPORT_INVALID) && (*cosq == BCM_COS_INVALID))) ||
            (*cosq == BCM_COS_INVALID)) {
        return BCM_E_NOT_FOUND;
    }

    return BCM_E_NONE;
}

/*
 *   Function:
 *       bcm_hx5_cosq_mapping_set
 *   Purpose:
 *        Set which cosq a given priority should fall into
 *   Parameters:
 *        unit     - (IN) unit number
 *        gport    - (IN) queue group GPORT identifier
 *        priority - (IN) priority value to map
 *        cosq     - (INT) COS queue number
 *   Returns:
 *        BCM_E_XXX
 */
int
bcm_hx5_cosq_mapping_set(int unit, bcm_port_t port, bcm_cos_t priority,
        bcm_cos_queue_t cosq)
{
    bcm_pbmp_t pbmp;
    bcm_port_t local_port;
    int rv = BCM_E_NONE, numq;

    BCM_PBMP_CLEAR(pbmp);

    if ((priority < 0) || (priority >= _HX5_MMU_NUM_INT_PRI)) {
        return BCM_E_PARAM;
    }

    if (cosq < 0) {
        return BCM_E_PARAM;
    }

    if (port == -1) {
        /* port value of -1 will cause the cosq mapping set for
         *          * all types of local ports except Loopback ports.
         *                   * So we do the sanity check of cos value with Default Number
         *                            * of COS
         *                                     */
        if (cosq >= _BCM_HX5_NUM_COS(unit)) {
            return BCM_E_PARAM;
        }
        BCM_PBMP_ASSIGN(pbmp, PBMP_ALL(unit));
    } else {
        if (BCM_GPORT_IS_SET(port)) {
            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
                    BCM_GPORT_IS_MCAST_QUEUE_GROUP(port) ||
                    BCM_GPORT_IS_SCHEDULER(port)) {
                return BCM_E_PARAM;
            } else if (BCM_GPORT_IS_LOCAL(port)) {
                local_port = BCM_GPORT_LOCAL_GET(port);
            } else if (BCM_GPORT_IS_MODPORT(port)) {
                BCM_IF_ERROR_RETURN
                    (bcm_esw_port_local_get(unit, port, &local_port));
            } else {
                return BCM_E_PARAM;
            }
        } else {
            local_port = port;
        }

        if (!SOC_PORT_VALID(unit, local_port)) {
            return BCM_E_PORT;
        }

        BCM_PBMP_PORT_ADD(pbmp, local_port);
        if (cosq >= _HX5_PORT_NUM_COS(unit, local_port)) {
            return BCM_E_PARAM;
        }
    }

    numq = _BCM_HX5_NUM_COS(unit);
    PBMP_ITER(pbmp, local_port) {
        if (IS_LB_PORT(unit, local_port)) {
            continue;
        }

        /* If no ETS/gport, map the int prio symmetrically for ucast and
         *          * mcast */
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_mapping_set(unit, local_port, priority,
                                       BCM_COSQ_GPORT_UCAST_QUEUE_GROUP |
                                       BCM_COSQ_GPORT_MCAST_QUEUE_GROUP,
                                       -1, cosq));
    }

    rv = bcm_hx5_wireless_cos_map_update(unit, numq);

    if (rv < 0) {
        return rv;
    }

    return BCM_E_NONE;
}

/*
 *   Function:
 *       bcm_hx5_cosq_gport_mapping_set
 *   Purpose:
 *        Set COS queue for the specified priority of an ingress port
 *   Parameters:
 *        unit     - (IN) unit number
 *        ing_port - (IN) ingress port
 *        int_pri  - (IN) priority value to map
 *        flags    - (IN) BCM_COSQ_GPORT_XXX_QUEUE_GROUP
 *        gport    - (IN) queue group GPORT identifier
 *        cosq     - (IN) COS queue number
 *    Returns:
 *        BCM_E_XXX
 */
int
bcm_hx5_cosq_gport_mapping_set(int unit, bcm_port_t ing_port, bcm_cos_t int_pri,
        uint32 flags, bcm_gport_t gport,
        bcm_cos_queue_t cosq)
{
    bcm_port_t local_port;

    if ((int_pri < 0) || (int_pri >= _HX5_MMU_NUM_INT_PRI)) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN(_bcm_hx5_cosq_localport_resolve(unit, ing_port,
                &local_port));

    if ((cosq < 0) || (cosq >= _HX5_PORT_NUM_COS(unit, local_port))) {
        return BCM_E_PARAM;
    }

    return _bcm_hx5_cosq_mapping_set(unit, ing_port, int_pri, flags, gport,
            cosq);
}

/*
 *   Function:
 *       bcm_hx5_cosq_mapping_get
 *   Purpose:
 *       Determine which COS queue a given priority currently maps to.
 *   Parameters:
 *       unit     - (IN) unit number
 *       gport    - (IN) queue group GPORT identifier
 *       priority - (IN) priority value to map
 *       cosq     - (OUT) COS queue number
 *   Returns:
 *       BCM_E_XXX
 */
int
bcm_hx5_cosq_mapping_get(int unit, bcm_port_t port, bcm_cos_t priority,
        bcm_cos_queue_t *cosq)
{
    bcm_port_t local_port;
    bcm_pbmp_t pbmp;

    BCM_PBMP_CLEAR(pbmp);

    if ((priority < 0) || (priority >= _HX5_MMU_NUM_INT_PRI)) {
        return BCM_E_PARAM;
    }

    if (port == -1) {
        BCM_PBMP_ASSIGN(pbmp, PBMP_ALL(unit));
    } else {
        if (BCM_GPORT_IS_SET(port)) {
            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
                    BCM_GPORT_IS_MCAST_QUEUE_GROUP(port) ||
                    BCM_GPORT_IS_SCHEDULER(port)) {
                return BCM_E_PARAM;
            } else if (BCM_GPORT_IS_LOCAL(port)) {
                local_port = BCM_GPORT_LOCAL_GET(port);
            } else if (BCM_GPORT_IS_MODPORT(port)) {
                BCM_IF_ERROR_RETURN
                    (bcm_esw_port_local_get(unit, port, &local_port));
            } else {
                return BCM_E_PARAM;
            }
        } else {
            local_port = port;
        }

        if (!SOC_PORT_VALID(unit, local_port)) {
            return BCM_E_PORT;
        }

        BCM_PBMP_PORT_ADD(pbmp, local_port);
    }

    PBMP_ITER(pbmp, local_port) {
        if (IS_LB_PORT(unit, local_port)) {
            continue;
        }

        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_mapping_get(unit, local_port, priority,
                                       BCM_COSQ_GPORT_UCAST_QUEUE_GROUP, NULL,
                                       cosq));
        break;
    }

    return BCM_E_NONE;

}

/*
 *   Function:
 *      _bcm_hx5_cosq_gport_mapping_get
 *   Purpose:
 *       Determine which COS queue a given priority currently maps to.
 *   Parameters:
 *       unit     - (IN) unit number
 *       ing_port - (IN) ingress port
 *       int_pri  - (IN) priority value to map
 *       flags    - (IN) BCM_COSQ_GPORT_XXX_QUEUE_GROUP
 *       gport    - (IN) queue group GPORT identifier
 *        cosq     - (OUT) COS queue number
 *  Returns:
 *       BCM_E_XXX
 */
int
bcm_hx5_cosq_gport_mapping_get(int unit, bcm_port_t ing_port, bcm_cos_t int_pri,
        uint32 flags, bcm_gport_t *gport,
        bcm_cos_queue_t *cosq)
{
    if (gport == NULL || cosq == NULL) {
        return BCM_E_PARAM;
    }

    if ((int_pri < 0) || (int_pri >= _HX5_MMU_NUM_INT_PRI)) {
        return BCM_E_PARAM;
    }

    return _bcm_hx5_cosq_mapping_get(unit, ing_port, int_pri, flags, gport,
            cosq);
}


STATIC int
_bcm_hx5_cosq_egr_pool_set(int unit, bcm_gport_t gport, 
                          bcm_cos_queue_t cosq, bcm_cosq_control_t type, int arg)
{
    bcm_port_t local_port;
    int startq, pool, midx;
    uint32 max_val;
    uint32 entry[SOC_MAX_MEM_WORDS];
    uint32 entry2[SOC_MAX_MEM_WORDS];
    soc_mem_t base_mem = INVALIDm, base_mem2 = INVALIDm;
    soc_mem_t mem = INVALIDm, mem2 = INVALIDm;
    soc_field_t fld_limit = INVALIDf;
    int granularity = 1, pipe = 0;

    if (arg < 0) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                     _BCM_HX5_COSQ_INDEX_STYLE_EGR_POOL,
                                     &local_port, &pool, NULL));

    base_mem = MMU_THDM_DB_PORTSP_CONFIGm;
    mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];

    if (type == bcmCosqControlEgressPoolLimitEnable) {
        midx = SOC_TD3_MMU_PIPED_MEM_INDEX(unit, local_port, base_mem, pool);
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL,
                            midx, entry));

        soc_mem_field32_set(unit, mem, entry, SHARED_LIMIT_ENABLEf, !!arg);

        return soc_mem_write(unit, mem, MEM_BLOCK_ALL, midx, entry);
    }
    if (type == bcmCosqControlEgressPool || type == bcmCosqControlUCEgressPool ||
        type == bcmCosqControlMCEgressPool) {
        if((arg < 0) || (arg >= _HX5_MMU_NUM_POOL)) {
            return BCM_E_PARAM;
        }
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            if (type != bcmCosqControlEgressPool) {
                return BCM_E_PARAM;
            }
            /* regular unicast queue */
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                     _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                     &local_port, &startq, NULL));
            base_mem = MMU_THDU_Q_TO_QGRP_MAPm;
            mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            if (type != bcmCosqControlEgressPool) {
                return BCM_E_PARAM;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                     _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                     &local_port, &startq, NULL));
            base_mem = MMU_THDM_MCQE_QUEUE_CONFIGm;
            mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
            base_mem2 = MMU_THDM_DB_QUEUE_CONFIGm;
            mem2 = SOC_MEM_UNIQUE_ACC(unit, base_mem2)[pipe];
        } else  { /* local port */
            if (type == bcmCosqControlUCEgressPool) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                         _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                         &local_port, &startq, NULL));
                base_mem = MMU_THDU_Q_TO_QGRP_MAPm;
                mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
            } else {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                             _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                             &local_port, &startq, NULL));
                base_mem = MMU_THDM_MCQE_QUEUE_CONFIGm;
                mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
                base_mem2 = MMU_THDM_DB_QUEUE_CONFIGm;
                mem2 = SOC_MEM_UNIQUE_ACC(unit, base_mem2)[pipe];
            }
        }

        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        soc_mem_field32_set(unit, mem, entry, Q_SPIDf, arg);

        BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, startq, entry));
        if (mem2 != INVALIDm) {
            BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem2, MEM_BLOCK_ALL, startq, entry2));
            soc_mem_field32_set(unit, mem2, entry2, Q_SPIDf, arg);
            BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem2, MEM_BLOCK_ALL, startq, entry2));
        }
        return BCM_E_NONE;
    }

    if (type == bcmCosqControlEgressPoolMCSharedEntryLimit) {
        soc_reg_t reg = MMU_THDM_MCQE_POOL_SHARED_LIMITr;
        granularity = 4;

        /* Check for min/max values */
        max_val = (1 << soc_reg_field_length(unit, reg, SHARED_LIMITf)) - 1;
        if ((arg < 0) || (sal_ceil_func(arg, granularity) > max_val)) {
            return BCM_E_PARAM;
        }

        /* Validate whether new shared limit causes over allocation
         * of the egress multicast queue entries.
         */
        BCM_IF_ERROR_RETURN(
                _bcm_hx5_cosq_egr_pool_mcshrd_limit_val(unit, pool, arg));

        /* Set the egress MCQE pool size to the new SHARED_LIMIT */
        BCM_IF_ERROR_RETURN(
                _bcm_hx5_cosq_egr_pool_mcshrd_thresh_adjust(unit, pool, arg,
                    local_port));

        return BCM_E_NONE;
    }

    arg = (arg + _HX5_MMU_BYTES_PER_CELL - 1) / _HX5_MMU_BYTES_PER_CELL;

    /* per service pool settings */
    if (type == bcmCosqControlEgressPoolSharedLimitBytes ||
        type == bcmCosqControlEgressPoolResumeLimitBytes ||
        type == bcmCosqControlEgressPoolYellowSharedLimitBytes ||
        type == bcmCosqControlEgressPoolYellowResumeLimitBytes ||
        type == bcmCosqControlEgressPoolRedSharedLimitBytes ||
        type == bcmCosqControlEgressPoolRedResumeLimitBytes) {
                uint32 rval;
        soc_reg_t reg;
        switch (type) {
        case bcmCosqControlEgressPoolSharedLimitBytes:
            reg = MMU_THDM_DB_POOL_SHARED_LIMITr;
            fld_limit = SHARED_LIMITf;
            granularity = 1;
            break;
        case bcmCosqControlEgressPoolResumeLimitBytes:
            reg = MMU_THDM_DB_POOL_RESUME_LIMITr;
            fld_limit = RESUME_LIMITf;
            granularity = 8;
            break;
        case bcmCosqControlEgressPoolYellowSharedLimitBytes:
            reg = MMU_THDM_DB_POOL_YELLOW_SHARED_LIMITr;
            fld_limit = YELLOW_SHARED_LIMITf;
            granularity = 8;
            break;
        case bcmCosqControlEgressPoolYellowResumeLimitBytes:
            reg = MMU_THDM_DB_POOL_YELLOW_RESUME_LIMITr;
            fld_limit = YELLOW_RESUME_LIMITf;
            granularity = 8;
            break;
        case bcmCosqControlEgressPoolRedSharedLimitBytes:
            reg = MMU_THDM_DB_POOL_RED_SHARED_LIMITr;
            fld_limit = RED_SHARED_LIMITf;
            granularity = 8;
            break;
        case bcmCosqControlEgressPoolRedResumeLimitBytes:
            reg = MMU_THDM_DB_POOL_RED_RESUME_LIMITr;
            fld_limit = RED_RESUME_LIMITf;
            granularity = 8;
            break;
        /* coverity[dead_error_begin] */
        default:
            return BCM_E_UNAVAIL;
        }

        BCM_IF_ERROR_RETURN(soc_reg32_get(unit, reg, REG_PORT_ANY, pool, &rval));

        /* Check for min/max values */
        max_val = (1 << soc_reg_field_length(unit, reg, fld_limit)) - 1;
        if ((arg < 0) || ((arg/granularity) > max_val)) {
            return BCM_E_PARAM;
        } else {
            soc_reg_field_set(unit, reg, &rval, fld_limit, (arg/granularity));
        }

        BCM_IF_ERROR_RETURN(soc_reg32_set(unit, reg, REG_PORT_ANY, pool, rval));

        return BCM_E_NONE;
    }

    if (type == bcmCosqControlEgressPoolHighCongestionLimitBytes ||
            type == bcmCosqControlEgressPoolLowCongestionLimitBytes) {
        uint64 rval64;
        soc_reg_t reg64;
        soc_reg_t wred_cng_lmt[4] = {
            WRED_POOL_INST_CONG_LIMIT_0r,
            WRED_POOL_INST_CONG_LIMIT_1r,
            WRED_POOL_INST_CONG_LIMIT_2r,
            WRED_POOL_INST_CONG_LIMIT_3r,
        };

        switch (type) {
            case bcmCosqControlEgressPoolHighCongestionLimitBytes:
                reg64 = wred_cng_lmt[pool];
                fld_limit = POOL_HI_CONG_LIMITf;
                pool = -1;
                granularity = 1;
                break;
            case bcmCosqControlEgressPoolLowCongestionLimitBytes:
                reg64 = wred_cng_lmt[pool];
                fld_limit = POOL_LOW_CONG_LIMITf;
                pool = -1;
                granularity = 1;
                break;
                /* coverity[dead_error_begin] */
            default:
                return BCM_E_UNAVAIL;
        }

        BCM_IF_ERROR_RETURN(soc_reg64_get(unit, reg64, REG_PORT_ANY, pool, &rval64));

        /* Check for min/max values */
        max_val = (1 << soc_reg_field_length(unit, reg64, fld_limit)) - 1;
        if ((arg < 0) || ((arg/granularity) > max_val)) {
            return BCM_E_PARAM;
        } else {
            soc_reg64_field32_set(unit, reg64, &rval64, fld_limit, (arg/granularity));
        }

        BCM_IF_ERROR_RETURN(soc_reg64_set(unit, reg64, REG_PORT_ANY, pool, rval64));

        return BCM_E_NONE;
    }

    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                         _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                         &local_port, &startq, NULL));
        base_mem = MMU_THDU_CONFIG_QUEUEm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        base_mem2 = MMU_THDU_Q_TO_QGRP_MAPm;
        mem2 = SOC_MEM_UNIQUE_ACC(unit, base_mem2)[pipe];
    } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                         _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                         &local_port, &startq, NULL));
        base_mem = MMU_THDM_DB_QUEUE_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
    } else {
        if (soc_property_get(unit, spn_PORT_UC_MC_ACCOUNTING_COMBINE, 0) == 0) {
            /* Need to have the UC_MC_Combine config enabled */
            return BCM_E_PARAM;
        }
        base_mem = MMU_THDM_DB_PORTSP_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        startq = SOC_TD3_MMU_PIPED_MEM_INDEX(unit, local_port, base_mem, pool);
    }

    BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));

    if (mem2 != INVALIDm) {
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem2, MEM_BLOCK_ALL, startq, entry2));
    }

    switch (type) {
        case bcmCosqControlEgressPoolLimitBytes:
            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
                fld_limit = Q_SHARED_LIMIT_CELLf;

                if (mem2 != INVALIDm) {
                    soc_mem_field32_set(unit, mem2, entry2, Q_LIMIT_ENABLEf, 1);
                }
            } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
                fld_limit = Q_SHARED_LIMITf;
                soc_mem_field32_set(unit, mem, entry, Q_LIMIT_ENABLEf, 1);
            } else {
                fld_limit = SHARED_LIMITf;
                soc_mem_field32_set(unit, mem, entry, SHARED_LIMIT_ENABLEf, 1);
            }
            granularity = 1;
            break;
        case bcmCosqControlEgressPoolYellowLimitBytes:
            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
                fld_limit = LIMIT_YELLOW_CELLf;
            } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
                fld_limit = YELLOW_SHARED_LIMITf;
            } else {
                fld_limit = YELLOW_SHARED_LIMITf;
            }
            granularity = 8;
            break;
        case bcmCosqControlEgressPoolRedLimitBytes:
            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
                fld_limit = LIMIT_RED_CELLf;
            } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
                fld_limit = RED_SHARED_LIMITf;
            } else {
                fld_limit = RED_SHARED_LIMITf;
            }
            granularity = 8;
            break;
        default:
            return BCM_E_UNAVAIL;
    }

    /* Check for min/max values */
    max_val = (1 << soc_mem_field_length(unit, mem, fld_limit)) - 1;
    if ((arg < 0) || ((arg/granularity) > max_val)) {
        return BCM_E_PARAM;
    } else {
        soc_mem_field32_set(unit, mem, entry, fld_limit, (arg/granularity));
    }
    BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, startq, entry));

    if (mem2 != INVALIDm) {
        BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem2, MEM_BLOCK_ALL, startq, entry2));
    }
    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_egr_pool_get(int unit, bcm_gport_t gport, bcm_cos_queue_t cosq,
                          bcm_cosq_control_t type, int *arg)
{
    bcm_port_t local_port;
    int startq, pool, midx, pipe = 0;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_mem_t mem, base_mem;
    int granularity = 1;

    if (!arg) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                     _BCM_HX5_COSQ_INDEX_STYLE_EGR_POOL,
                                     &local_port, &pool, NULL));

    if (type == bcmCosqControlEgressPool || type == bcmCosqControlUCEgressPool ||
        type == bcmCosqControlMCEgressPool) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            if (type != bcmCosqControlEgressPool) {
                return BCM_E_PARAM;
            }
            /* regular unicast queue */
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                     _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                     &local_port, &startq, NULL));
            base_mem = MMU_THDU_Q_TO_QGRP_MAPm;
            mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            if (type != bcmCosqControlEgressPool) {
                return BCM_E_PARAM;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                     _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                     &local_port, &startq, NULL));
            base_mem = MMU_THDM_MCQE_QUEUE_CONFIGm;
            mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        } else  { /* local port */
            if (type == bcmCosqControlUCEgressPool) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                         _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                         &local_port, &startq, NULL));
                base_mem = MMU_THDU_Q_TO_QGRP_MAPm;
                mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
            } else {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                             _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                             &local_port, &startq, NULL));
                base_mem = MMU_THDM_MCQE_QUEUE_CONFIGm;
                mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
            }
        }

        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        *arg = soc_mem_field32_get(unit, mem, entry, Q_SPIDf);
        return BCM_E_NONE;
    }

    /* per service pool settings */
    if (type == bcmCosqControlEgressPoolSharedLimitBytes ||
        type == bcmCosqControlEgressPoolResumeLimitBytes ||
        type == bcmCosqControlEgressPoolYellowSharedLimitBytes ||
        type == bcmCosqControlEgressPoolYellowResumeLimitBytes ||
        type == bcmCosqControlEgressPoolRedSharedLimitBytes ||
        type == bcmCosqControlEgressPoolRedResumeLimitBytes) {
        uint32 rval;
        soc_reg_t reg;
        soc_field_t fld_limit = INVALIDf;
        switch (type) {
        case bcmCosqControlEgressPoolSharedLimitBytes:
            reg = MMU_THDM_DB_POOL_SHARED_LIMITr;
            fld_limit = SHARED_LIMITf;
            granularity = 1;
            break;
        case bcmCosqControlEgressPoolResumeLimitBytes:
            reg = MMU_THDM_DB_POOL_RESUME_LIMITr;
            fld_limit = RESUME_LIMITf;
            granularity = 8;
            break;
        case bcmCosqControlEgressPoolYellowSharedLimitBytes:
            reg = MMU_THDM_DB_POOL_YELLOW_SHARED_LIMITr;
            fld_limit = YELLOW_SHARED_LIMITf;
            granularity = 8;
            break;
        case bcmCosqControlEgressPoolYellowResumeLimitBytes:
            reg = MMU_THDM_DB_POOL_YELLOW_RESUME_LIMITr;
            fld_limit = YELLOW_RESUME_LIMITf;
            granularity = 8;
            break;
        case bcmCosqControlEgressPoolRedSharedLimitBytes:
            reg = MMU_THDM_DB_POOL_RED_SHARED_LIMITr;
            fld_limit = RED_SHARED_LIMITf;
            granularity = 8;
            break;
        case bcmCosqControlEgressPoolRedResumeLimitBytes:
            reg = MMU_THDM_DB_POOL_RED_RESUME_LIMITr;
            fld_limit = RED_RESUME_LIMITf;
            granularity = 8;
            break;
        /* coverity[dead_error_begin] */
        default:
            return BCM_E_UNAVAIL;
        }

        BCM_IF_ERROR_RETURN(soc_reg32_get(unit, reg, REG_PORT_ANY, pool, &rval));

        *arg = soc_reg_field_get(unit, reg, rval, fld_limit);
        *arg = (*arg) * granularity * _HX5_MMU_BYTES_PER_CELL;

        return BCM_E_NONE;
    }

    if (type == bcmCosqControlEgressPoolHighCongestionLimitBytes ||
        type == bcmCosqControlEgressPoolLowCongestionLimitBytes) {
        uint64 rval64;
        soc_reg_t reg64;
        soc_reg_t wred_cng_lmt[4] = {
            WRED_POOL_INST_CONG_LIMIT_0r,
            WRED_POOL_INST_CONG_LIMIT_1r,
            WRED_POOL_INST_CONG_LIMIT_2r,
            WRED_POOL_INST_CONG_LIMIT_3r,
        };
        soc_field_t fld_limit = INVALIDf;

        switch (type) {
        case bcmCosqControlEgressPoolHighCongestionLimitBytes:
            reg64 = wred_cng_lmt[pool];
            fld_limit = POOL_HI_CONG_LIMITf;
            pool = -1;
            granularity = 1;
            break;
        case bcmCosqControlEgressPoolLowCongestionLimitBytes:
            reg64 = wred_cng_lmt[pool];
            fld_limit = POOL_LOW_CONG_LIMITf;
            pool = -1;
            granularity = 1;
            break;
        /* coverity[dead_error_begin] */
        default:
            return BCM_E_UNAVAIL;
        }

        BCM_IF_ERROR_RETURN(soc_reg64_get(unit, reg64, REG_PORT_ANY, pool, &rval64));

        *arg = soc_reg64_field32_get(unit, reg64, rval64, fld_limit);
        *arg = (*arg) * granularity * _HX5_MMU_BYTES_PER_CELL;

        return BCM_E_NONE;
    }

    if (type == bcmCosqControlEgressPoolMCSharedEntryLimit) {
        uint32 rval;
        soc_reg_t reg = MMU_THDM_MCQE_POOL_SHARED_LIMITr;
        granularity = 4;

        BCM_IF_ERROR_RETURN(soc_reg32_get(unit, reg, REG_PORT_ANY, pool, &rval));
        *arg = soc_reg_field_get(unit, reg, rval, SHARED_LIMITf);
        *arg = (*arg) * granularity;
        return BCM_E_NONE;
    }

    base_mem = MMU_THDM_DB_PORTSP_CONFIGm;
    mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];

    if (type == bcmCosqControlEgressPoolLimitEnable) {
        midx = SOC_TD3_MMU_PIPED_MEM_INDEX(unit, local_port, base_mem, pool);
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL,
                                 midx, entry));

        *arg = soc_mem_field32_get(unit, mem, entry, SHARED_LIMIT_ENABLEf);
        return BCM_E_NONE;
    }

    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                        _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                        &local_port, &startq, NULL));
        base_mem = MMU_THDU_CONFIG_QUEUEm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
    } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                        _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                        &local_port, &startq, NULL));

        base_mem = MMU_THDM_DB_QUEUE_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
    } else {
        if (soc_property_get(unit, spn_PORT_UC_MC_ACCOUNTING_COMBINE, 0) == 0) {
            /* Need to have the UC_MC_Combine config enabled */
            return BCM_E_PARAM;
        }
        base_mem = MMU_THDM_DB_PORTSP_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        startq = SOC_TD3_MMU_PIPED_MEM_INDEX(unit, local_port, base_mem, pool);
    }
    BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL,
                             startq, entry));

    switch (type) {
        case bcmCosqControlEgressPoolLimitBytes:
            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
                *arg = soc_mem_field32_get(unit, mem, entry, Q_SHARED_LIMIT_CELLf);
            } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
                *arg = soc_mem_field32_get(unit, mem, entry, Q_SHARED_LIMITf);
            } else {
                *arg = soc_mem_field32_get(unit, mem, entry, SHARED_LIMITf);
            }
            granularity = 1;
            break;
        case bcmCosqControlEgressPoolYellowLimitBytes:
            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
                *arg = soc_mem_field32_get(unit, mem, entry, LIMIT_YELLOW_CELLf);
            } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
                *arg = soc_mem_field32_get(unit, mem, entry, YELLOW_SHARED_LIMITf);
            } else {
                *arg = soc_mem_field32_get(unit, mem, entry, YELLOW_SHARED_LIMITf);
            }
            granularity = 8;
            break;
        case bcmCosqControlEgressPoolRedLimitBytes:
            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
                *arg = soc_mem_field32_get(unit, mem, entry, LIMIT_RED_CELLf);
            } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
                *arg = soc_mem_field32_get(unit, mem, entry, RED_SHARED_LIMITf);
            } else {
                *arg = soc_mem_field32_get(unit, mem, entry, RED_SHARED_LIMITf);
            }
            granularity = 8;
            break;
        default:
            return BCM_E_UNAVAIL;
    }
    *arg = (*arg) * granularity * _HX5_MMU_BYTES_PER_CELL;
    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_egr_queue_set(int unit, bcm_gport_t gport, bcm_cos_queue_t cosq,
                            bcm_cosq_control_t type, int arg)
{
    bcm_port_t local_port;
    int pipe = 0, startq;
    uint32 max_val;
    uint32 max_val2;
    uint32 entry[SOC_MAX_MEM_WORDS];
    uint32 entry2[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm, mem2 = INVALIDm;
    soc_field_t fld_limit = INVALIDf;
    int granularity = 1;
    int from_cos, to_cos, ci;
    int cur_val;
    int limit;
    int disable_queuing = 0;
    int uc_qlimit_enable = 0, mc_qlimit_enable = 0;
    int delta = 0;
    soc_reg_t ctr_reg;
    soc_ctr_control_info_t ctrl_info;
    int ar_idx;
    uint8 sync_mode = TRUE;
    uint8 allowed = FALSE;
    int share_update_flag = 0;
    int egr_pool;
    int use_qgroup_min;
    uint8 check_use_count = FALSE;
    soc_info_t * si = &SOC_INFO(unit);

    if (arg < 0) {
        return BCM_E_PARAM;
    }

    arg = sal_ceil_func(arg, _HX5_MMU_BYTES_PER_CELL);

    if ((type == bcmCosqControlEgressUCQueueMinLimitBytes) ||
        (type == bcmCosqControlEgressUCQueueSharedLimitBytes)) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                             _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                             &local_port, &startq, NULL));
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        }
        else {
            if (cosq == BCM_COS_INVALID) {
                from_cos = to_cos = 0;
            } else {
                from_cos = to_cos = cosq;
            }

            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            for (ci = from_cos; ci <= to_cos; ci++) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_index_resolve
                     (unit, local_port, ci, _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                      NULL, &startq, NULL));
            }
        }
        mem = SOC_MEM_UNIQUE_ACC(unit, MMU_THDU_CONFIG_QUEUEm)[pipe];
        mem2 = SOC_MEM_UNIQUE_ACC(unit, MMU_THDU_Q_TO_QGRP_MAPm)[pipe];
    } else if ((type == bcmCosqControlEgressMCQueueMinLimitBytes) ||
               (type == bcmCosqControlEgressMCQueueSharedLimitBytes)) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                             _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                             &local_port, &startq, NULL));
        }
        else {
            if (cosq == BCM_COS_INVALID) {
                from_cos = to_cos = 0;
            } else {
                from_cos = to_cos = cosq;
            }

            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            for (ci = from_cos; ci <= to_cos; ci++) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_index_resolve
                     (unit, local_port, ci, _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                      NULL, &startq, NULL));
            }
        }
        mem = SOC_MEM_UNIQUE_ACC(unit, MMU_THDM_DB_QUEUE_CONFIGm)[pipe];
        mem2 = SOC_MEM_UNIQUE_ACC(unit, MMU_THDM_MCQE_QUEUE_CONFIGm)[pipe];
    } else {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
    BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem2, MEM_BLOCK_ALL, startq, entry2));
    if (mem2 != INVALIDm) {
        BCM_IF_ERROR_RETURN
            (soc_mem_read(unit, mem2, MEM_BLOCK_ALL, startq, entry2));
    }

    switch (type) {
        case bcmCosqControlEgressUCQueueSharedLimitBytes:
            fld_limit = Q_SHARED_LIMIT_CELLf;
            uc_qlimit_enable = 1;

            /* Set MMU_THDU_XPIPE_Q_TO_QGRP_MAP.DISABLE_QUEUING to 1 when both MIN
             * and SHARED LIMIT are 0. Set it to 0 when either MIN or SHARED LIMIT
             * is non-zero.
             */
            limit = soc_mem_field32_get(unit, mem, entry, Q_MIN_LIMIT_CELLf);
            if (arg == 0 && limit == 0) {
                disable_queuing = 1;
            } else if (arg != 0 || limit != 0) {
                disable_queuing = 0;
            }
            granularity = 1;
            break;
        case bcmCosqControlEgressMCQueueSharedLimitBytes:
            fld_limit = Q_SHARED_LIMITf;
            mc_qlimit_enable = 1;
            granularity = 1;
            break;
        case bcmCosqControlEgressUCQueueMinLimitBytes:
            fld_limit = Q_MIN_LIMIT_CELLf;

            /* Set MMU_THDU_Q_TO_QGRP_MAP.DISABLE_QUEUING to 1 when both MIN
             * and SHARED LIMIT are 0. Set it to 0 when either MIN or
             * SHARED LIMIT is non-zero
             */
            limit = soc_mem_field32_get(unit, mem, entry, Q_SHARED_LIMIT_CELLf);
            if (arg == 0 && limit == 0) {
                disable_queuing = 1;
            } else if (arg != 0 || limit != 0) {
                disable_queuing = 0;
            }

            granularity = 1;
            break;
        case bcmCosqControlEgressMCQueueMinLimitBytes:
            fld_limit = Q_MIN_LIMITf;
            granularity = 1;
            break;
        default:
            return BCM_E_UNAVAIL;
    }

    /* Check for min/max values */
    max_val = (1 << soc_mem_field_length(unit, mem, fld_limit)) - 1;
    if ((arg < 0) || (sal_ceil_func(arg, granularity) > max_val)) {
        return BCM_E_PARAM;
    }
   /* guarantee limits need adjust shared limits */
    if ((type == bcmCosqControlEgressUCQueueMinLimitBytes) ||
         (type == bcmCosqControlEgressMCQueueMinLimitBytes)) {
        cur_val = soc_mem_field32_get(unit, mem, entry, fld_limit);
        if (sal_ceil_func(arg, granularity) == cur_val) {
            /* New_Q_MIN equals to Current_Q_MIN, return directly without doing anything */
            return BCM_E_NONE;
        }

        if (type == bcmCosqControlEgressUCQueueMinLimitBytes) {
            BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_qgroup_limit_enables_get(unit, gport, cosq,
                                                   bcmCosqControlEgressUCQueueGroupMinEnable,
                                                   &use_qgroup_min));

            /* If use queue group MIN, set new Q_MIN and skip share limit adjust */
            if (use_qgroup_min) {
                BCM_IF_ERROR_RETURN
                    (soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
                soc_mem_field32_set(unit, mem, entry, fld_limit,
                                    sal_ceil_func(arg, granularity));
                /* coverity[negative_returns] */
                BCM_IF_ERROR_RETURN
                    (soc_mem_write(unit, mem, MEM_BLOCK_ALL, startq, entry));
                goto limit_enable;
            }
        }

        /* Retrieve the egress pool ID */
        if ((BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport))
            || (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport))) {
            BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_egr_pool_get(unit, gport, cosq,
                                       bcmCosqControlEgressPool, &egr_pool));
        } else {
            if (type == bcmCosqControlEgressUCQueueMinLimitBytes) {
                BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_egr_pool_get(unit, gport, cosq,
                                           bcmCosqControlUCEgressPool, &egr_pool));
            } else {
                BCM_IF_ERROR_RETURN
                 (_bcm_hx5_cosq_egr_pool_get(unit, gport, cosq,
                                           bcmCosqControlMCEgressPool, &egr_pool));
            }
        }

        if (sal_ceil_func(arg, granularity) < cur_val) {
            /* Decrease Q_MIN threshold */
            share_update_flag |= _BCM_COSQ_INCREASE_SHARE_LIMIT;
            delta = cur_val * granularity - arg;

            /* Check Q_MIN Use Count less than new Q_MIN threshold */
            ctrl_info.instance_type = SOC_CTR_INSTANCE_TYPE_XPE;
            ctrl_info.instance = local_port;
            if (type == bcmCosqControlEgressUCQueueMinLimitBytes) {
                ctr_reg = SOC_COUNTER_NON_DMA_UC_QUEUE_CURRENT;
                ar_idx = startq - si->port_uc_cosq_base[local_port];
            } else {
                ctr_reg = SOC_COUNTER_NON_DMA_QUEUE_CURRENT;
                ar_idx = startq - si->port_cosq_base[local_port];
            }
            BCM_IF_ERROR_RETURN
                (soc_hx5_cosq_threshold_dynamic_change_check(unit, arg,
                                                            ctr_reg, ctrl_info,
                                                            ar_idx, sync_mode,
                                                            &allowed));
        } else {
            /* Increase Q_MIN threshold */
            share_update_flag |= _BCM_COSQ_DECREASE_SHARE_LIMIT;
            delta = arg - cur_val * granularity;
            check_use_count = TRUE;
            /* Validate and decrease pool related threshold */
            BCM_IF_ERROR_RETURN(
                _bcm_hx5_cosq_pool_thresh_adjust(unit, local_port, egr_pool,
                                                delta, share_update_flag,
                                            check_use_count));
        }

        /* Set new Q_MIN threshold*/
        BCM_IF_ERROR_RETURN
            (soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        soc_mem_field32_set(unit, mem, entry, fld_limit,
                            sal_ceil_func(arg, granularity));
        /* coverity[negative_returns] */
        BCM_IF_ERROR_RETURN
            (soc_mem_write(unit, mem, MEM_BLOCK_ALL, startq, entry));

        /* Q_MIN decrease case */
        if (share_update_flag & _BCM_COSQ_INCREASE_SHARE_LIMIT) {
            check_use_count = FALSE;
            /* Increase pool related threshold */
            BCM_IF_ERROR_RETURN(
                _bcm_hx5_cosq_pool_thresh_adjust(unit, local_port, egr_pool,
                                                delta, share_update_flag,
                                                check_use_count));
        }
    } else {
        if (type == bcmCosqControlEgressMCQueueSharedLimitBytes) {
            uint32 value = sal_ceil_func(arg, granularity);
            max_val2 = (1 << soc_mem_field_length(unit, mem2, fld_limit)) - 1;
            if (value > max_val2) {
                value = max_val2;
            }
            soc_mem_field32_set(unit, mem2, entry2, fld_limit, value);
            BCM_IF_ERROR_RETURN
                (soc_mem_write(unit, mem2, MEM_BLOCK_ALL, startq, entry2));
        }
        soc_mem_field32_set(unit, mem, entry, fld_limit,
                            sal_ceil_func(arg, granularity));
        BCM_IF_ERROR_RETURN
            (soc_mem_write(unit, mem, MEM_BLOCK_ALL, startq, entry));
    }

limit_enable:
    /* limit enable */
    BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
    BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem2, MEM_BLOCK_ALL, startq, entry2));

    if ((type == bcmCosqControlEgressUCQueueMinLimitBytes) ||
        (type == bcmCosqControlEgressUCQueueSharedLimitBytes)) {
        soc_mem_field32_set(unit, mem2, entry2, DISABLE_QUEUINGf,
                            disable_queuing);
    }

    if (mc_qlimit_enable) {
        soc_mem_field32_set(unit, mem, entry, Q_LIMIT_ENABLEf, 1);
        soc_mem_field32_set(unit, mem2, entry2, Q_LIMIT_ENABLEf, 1);
    }

    if (uc_qlimit_enable) {
        soc_mem_field32_set(unit, mem2, entry2, Q_LIMIT_ENABLEf, 1);
    }

    BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, startq, entry));
    BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem2, MEM_BLOCK_ALL, startq,
                                      entry2));

    return BCM_E_NONE;
}


STATIC int
_bcm_hx5_cosq_egr_queue_get(int unit, bcm_gport_t gport, bcm_cos_queue_t cosq,
                            bcm_cosq_control_t type, int *arg)
{
    bcm_port_t local_port;
    int pipe = 0, startq;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm;
    soc_field_t fld_limit = INVALIDf;
    int granularity = 1;
    int from_cos, to_cos, ci;

    if (!arg) {
        return BCM_E_PARAM;
    }

    if ((type == bcmCosqControlEgressUCQueueMinLimitBytes) ||
        (type == bcmCosqControlEgressUCQueueSharedLimitBytes)) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                             _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                             &local_port, &startq, NULL));
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        }
        else {
            if (cosq == BCM_COS_INVALID) {
                from_cos = to_cos = 0;
            } else {
                from_cos = to_cos = cosq;
            }

            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            for (ci = from_cos; ci <= to_cos; ci++) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_index_resolve
                     (unit, local_port, ci, _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                      NULL, &startq, NULL));
            }
        }
        mem = SOC_MEM_UNIQUE_ACC(unit, MMU_THDU_CONFIG_QUEUEm)[pipe];
    } else if ((type == bcmCosqControlEgressMCQueueMinLimitBytes) ||
               (type == bcmCosqControlEgressMCQueueSharedLimitBytes)) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                             _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                             &local_port, &startq, NULL));
        }
        else {
            if (cosq == BCM_COS_INVALID) {
                from_cos = to_cos = 0;
            } else {
                from_cos = to_cos = cosq;
            }

            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            for (ci = from_cos; ci <= to_cos; ci++) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_index_resolve
                     (unit, local_port, ci, _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                      NULL, &startq, NULL));
            }
        }
        mem = SOC_MEM_UNIQUE_ACC(unit, MMU_THDM_DB_QUEUE_CONFIGm)[pipe];
    } else {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL,
                             startq, entry));

    switch (type) {
        case bcmCosqControlEgressUCQueueSharedLimitBytes:
            fld_limit = Q_SHARED_LIMIT_CELLf;
            granularity = 1;
            break;
        case bcmCosqControlEgressMCQueueSharedLimitBytes:
            fld_limit = Q_SHARED_LIMITf;
            granularity = 1;
            break;
        case bcmCosqControlEgressUCQueueMinLimitBytes:
            fld_limit = Q_MIN_LIMIT_CELLf;
            granularity = 1;
            break;
        case bcmCosqControlEgressMCQueueMinLimitBytes:
            fld_limit = Q_MIN_LIMITf;
            granularity = 1;
            break;
        default:
            return BCM_E_UNAVAIL;
    }
    *arg = soc_mem_field32_get(unit, mem, entry, fld_limit);
    *arg = (*arg) * granularity * _HX5_MMU_BYTES_PER_CELL;
    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_ing_pool_thresh_validate(int unit, int ing_pool, int delta)
{
    uint32 rval = 0;
    int cur_limit;

    /* Validate ingress service pool threshold */

    SOC_IF_ERROR_RETURN
        (READ_THDI_BUFFER_CELL_LIMIT_SPr(unit, ing_pool, &rval));
    cur_limit = soc_reg_field_get(unit, THDI_BUFFER_CELL_LIMIT_SPr,
                                         rval, LIMITf);

    if ((cur_limit - delta) < 0) {
        /* Delta greater than current pool limit */
        LOG_ERROR(BSL_LS_BCM_COSQ,
            (BSL_META_U(unit, "Error: Delta(%d) used to adjust(subtract) \n"
             "ingress service pool limit is greater than current "
             "pool limit(%d)!\n"),
             delta, cur_limit));
        return BCM_E_INTERNAL;
    }
    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_max_thresh_ingress_pool_find(int unit,
                                          int lossless_pool_map,
                                          int *max_thresh,
                                          int *max_thresh_id)
{
    int idx;
    int pool_thresh;
    uint32 rval = 0;

    for (idx = 0; idx < SOC_MMU_CFG_SERVICE_POOL_MAX; idx++) {
        if (lossless_pool_map & (1 << idx)) {
            /* Get ingress service pool threshold */

            SOC_IF_ERROR_RETURN
                (READ_THDI_BUFFER_CELL_LIMIT_SPr(unit, idx, &rval));
            pool_thresh = soc_reg_field_get(unit, THDI_BUFFER_CELL_LIMIT_SPr,
                                             rval, LIMITf);
            if (pool_thresh > *max_thresh) {
                *max_thresh = pool_thresh;
                *max_thresh_id = idx;
            } else if ((pool_thresh == *max_thresh)
                        && (idx < *max_thresh_id)) {
                /* Select ingress service pool with smaller ID if threshold equal */
                 *max_thresh_id = idx;
            }
        }
    }

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_ingress_pool_list_find(int unit, int egr_pool,
                                     int *lossless_pool_map,
                                     uint8 *lossless_pool_find)
{
    int pri;
    int ing_pool;
    bcm_port_t port;
    int pause_enable;
    uint32 rval, pri_bmp;

    /* Retrieve lossless ingress pool IDs mapped to the egress pool */
    PBMP_ALL_ITER(unit, port) {
        SOC_IF_ERROR_RETURN(READ_THDI_INPUT_PORT_XON_ENABLESr(unit, port,
                                                              &rval));
        pause_enable = soc_reg_field_get(unit, THDI_INPUT_PORT_XON_ENABLESr,
                                         rval, PORT_PAUSE_ENABLEf);

        pri_bmp = soc_reg_field_get(unit, THDI_INPUT_PORT_XON_ENABLESr, rval,
                                    PORT_PRI_XON_ENABLEf);

        SOC_IF_ERROR_RETURN(READ_THDI_PORT_PG_SPIDr(unit, port, &rval));
        ing_pool = soc_reg_field_get(unit, THDI_PORT_PG_SPIDr, rval,
                                     PG7_SPIDf);

        if (pause_enable &&
            ((1 << ing_pool) & _BCM_HX5_MMU_INFO(unit)->pool_map[egr_pool])) {
            *lossless_pool_map |= (1 << ing_pool);
            *lossless_pool_find = TRUE;
        }

        for (pri = 0; pri < _HX5_MMU_NUM_INT_PRI; pri++) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_ing_pool_pg_pipe_get(unit, port, pri,
                                                   NULL, &ing_pool, NULL,
                                                   NULL));
            if (((1 << pri) & pri_bmp) &&
                ((1 << ing_pool) & _BCM_HX5_MMU_INFO(unit)->pool_map[egr_pool])) {
                *lossless_pool_map |= (1 << ing_pool);
                *lossless_pool_find = TRUE;
            }
        }
    }

    return BCM_E_NONE;
}

/*
 * This function is used to get ingress pipe, shared pool id
 * priority group and headroom pool id for a given [Port, Prio]
 */
STATIC int
_bcm_hx5_cosq_ing_pool_pg_pipe_get(int unit, bcm_gport_t gport,
                                  bcm_cos_t prio, int *pipe,
                                  int *sp, int *pg, int *hdrm_pool)
{
    bcm_port_t local_port;

    if (pipe) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
        if (local_port < 0) {
            return BCM_E_PORT;
        }
        SOC_IF_ERROR_RETURN(soc_port_pipe_get(unit, local_port, pipe));
    }

    if (pg) {
         BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_ingress_pg_get(unit, gport, prio, pg,
                                         NULL ));

        if ((*pg < 0) || (*pg >= _HX5_MMU_NUM_PG)) {
            return BCM_E_PARAM;
        }
    }
    if (sp) {
        BCM_IF_ERROR_RETURN(
            _bcm_hx5_cosq_ingress_sp_get(unit, gport, prio, sp,
                                        NULL));

        if ((*sp < 0) || (*sp >= _HX5_MMU_NUM_POOL)) {
            return BCM_E_PARAM;
        }
    }

    if (hdrm_pool) {
        BCM_IF_ERROR_RETURN(
            _bcm_hx5_cosq_ingress_hdrm_pool_get(unit, gport,
                                               prio, hdrm_pool,
                                               NULL));

        if ((*hdrm_pool < 0) || (*hdrm_pool >= _HX5_MMU_NUM_POOL)) {
            return BCM_E_PARAM;
        }
    }

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_pool_thresh_adjust(int unit,
                                bcm_port_t local_port,
                                int egr_pool,
                                int delta,
                                int share_update_flag,
                                uint8 check_use_count)
{
    uint8 sync_mode = TRUE;
    uint32 rval = 0;
    soc_reg_t egr_sp_reg = INVALIDr;
    int new_ing_pool_limit, new_egr_pool_limit;
    soc_reg_t ctr_reg;
    soc_ctr_control_info_t ctrl_info;
    int ar_idx;
    uint8 allowed = FALSE;
    int ing_pool_thresh, egr_pool_thresh;
    int lossless_pool_map;
    uint8 lossless_pool_find;
    int ing_max_thresh;
    int ing_max_thresh_id;
    uint8 increase = FALSE;

    egr_sp_reg = MMU_THDM_DB_POOL_SHARED_LIMITr;

    if (share_update_flag & _BCM_COSQ_DECREASE_SHARE_LIMIT) {
        increase = FALSE;
    } else {
            increase = TRUE;
    }

    /* Retrieve lossless ingress pool IDs mapped to the egress pool */
    lossless_pool_map = 0;
    lossless_pool_find = FALSE;
    SOC_IF_ERROR_RETURN(
        _bcm_hx5_cosq_ingress_pool_list_find(unit, egr_pool,
                                            &lossless_pool_map,
                                            &lossless_pool_find));

    ing_max_thresh = 0;
    ing_max_thresh_id = -1;

    /* Find the ingress service pool ID with the max threshold */
    if (lossless_pool_find == TRUE) {
        SOC_IF_ERROR_RETURN(
            _bcm_hx5_cosq_max_thresh_ingress_pool_find(unit,
                                                      lossless_pool_map,
                                                      &ing_max_thresh,
                                                      &ing_max_thresh_id));
    }

    if (!increase) {
        /* Validate current threshold of egress service/RQE pool greater than delta */
        BCM_IF_ERROR_RETURN(
            _bcm_hx5_cosq_egr_pool_thresh_validate(unit, egr_pool, delta));
        if (lossless_pool_find == TRUE) {
            /* Validate current threshold of ingress service pool greater than delta */
            BCM_IF_ERROR_RETURN(
                _bcm_hx5_cosq_ing_pool_thresh_validate(unit, ing_max_thresh_id,
                                                      delta));
        }
    }

    if (lossless_pool_find == TRUE) {
        if (check_use_count == TRUE) {
            new_ing_pool_limit = ing_max_thresh - delta;
            ar_idx = ing_max_thresh_id;
            ctrl_info.instance_type = SOC_CTR_INSTANCE_TYPE_XPE;
            /* Check threshold againist use count on all the XPEs */
            ctrl_info.instance = BCM_PORT_INVALID;
            ctr_reg = SOC_COUNTER_NON_DMA_POOL_CURRENT;
            BCM_IF_ERROR_RETURN
                (soc_hx5_cosq_threshold_dynamic_change_check(unit, new_ing_pool_limit,
                                                            ctr_reg, ctrl_info,
                                                            ar_idx, sync_mode,
                                                            &allowed));
        }

        /* Adjust ingress service pool threshold */
        SOC_IF_ERROR_RETURN
            (READ_THDI_BUFFER_CELL_LIMIT_SPr(unit, ing_max_thresh_id, &rval));
        ing_pool_thresh = soc_reg_field_get(unit, THDI_BUFFER_CELL_LIMIT_SPr,
                                         rval, LIMITf);

        if (increase == TRUE) {
             new_ing_pool_limit = ing_pool_thresh + delta;
        } else {
            new_ing_pool_limit = ing_pool_thresh - delta;
        }
        soc_reg_field_set(unit, THDI_BUFFER_CELL_LIMIT_SPr, &rval, LIMITf,
                          new_ing_pool_limit);
        SOC_IF_ERROR_RETURN(
                    soc_trident3_xpe_reg32_set(unit, THDI_BUFFER_CELL_LIMIT_SPr,
                                               -1, 0, ing_max_thresh_id, rval));

    }

    if (check_use_count == TRUE) {
        /* Get current egress service pool limit */

        SOC_IF_ERROR_RETURN(
            soc_trident3_xpe_reg32_get(unit, MMU_THDM_DB_POOL_SHARED_LIMITr,
                                      -1, 0, egr_pool, &rval));


        egr_pool_thresh = soc_reg_field_get(unit, egr_sp_reg, rval,
                                            SHARED_LIMITf);

        /* Check egress service pool Use Count of both XPEs less than new pool limit */
        new_egr_pool_limit = egr_pool_thresh - delta;
        ar_idx = egr_pool;
        ctrl_info.instance_type = SOC_CTR_INSTANCE_TYPE_XPE;
        /* Check threshold againist use count on the 2 related XPEs */
        ctrl_info.instance = local_port;
        ctr_reg = SOC_COUNTER_NON_DMA_EGRESS_POOL_CURRENT;
        BCM_IF_ERROR_RETURN
            (soc_hx5_cosq_threshold_dynamic_change_check(unit, new_egr_pool_limit,
                                                        ctr_reg, ctrl_info,
                                                        ar_idx, sync_mode,
                                                        &allowed));
    }

    BCM_IF_ERROR_RETURN(
        _bcm_hx5_cosq_egr_pool_thresh_adjust(unit, egr_pool, delta,
                                            increase));
    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_egr_pool_thresh_adjust(int unit, int egr_pool,
                                     int delta, uint8 increase)
{
    uint32 rval = 0;
    int granularity = 1;
    int cur_limit, new_limit;
    soc_reg_t reg = INVALIDr;
    soc_field_t field = INVALIDf;

    /* Adjust egress service pool threshold */
    rval = 0;
    reg = MMU_THDM_DB_POOL_SHARED_LIMITr;
    field = SHARED_LIMITf;
    granularity = 1;

    SOC_IF_ERROR_RETURN(
        soc_trident3_xpe_reg32_get(unit, reg,
                                   -1, 0, egr_pool, &rval));
    cur_limit = soc_reg_field_get(unit, reg, rval, field);

    if (increase == TRUE) {
         new_limit = cur_limit * granularity + delta;
    } else {
        new_limit = cur_limit * granularity - delta;
    }
    soc_reg_field_set(unit, reg, &rval, field, sal_ceil_func(new_limit, granularity));

    SOC_IF_ERROR_RETURN(
        soc_trident3_xpe_reg32_set(unit, reg, -1, 0, egr_pool, rval));


    /* Adjust RQE pool threshold, set to same limit as egress SP threshold */
    reg = MMU_THDR_DB_CONFIG_SPr;
    field = SHARED_LIMITf;
    granularity = 1;
    SOC_IF_ERROR_RETURN(soc_trident3_xpe_reg32_get(unit, reg, -1, 0,
                                                   egr_pool, &rval));
    soc_reg_field_set(unit, reg, &rval, field,
                      sal_ceil_func(new_limit, granularity));
    SOC_IF_ERROR_RETURN(soc_trident3_xpe_reg32_set(unit, reg, -1, 0,
                                                   egr_pool, rval));

    /* Adjust egress service pool resume limit */
    rval = 0;
    reg = MMU_THDM_DB_POOL_RESUME_LIMITr;
    field = RESUME_LIMITf;
    granularity = 8;
    SOC_IF_ERROR_RETURN(soc_trident3_xpe_reg32_get(unit, reg, -1, 0,
                                                   egr_pool, &rval));
    cur_limit = soc_reg_field_get(unit, reg, rval, field);

    if (increase == TRUE) {
        new_limit = cur_limit * granularity + delta;
    } else {
        new_limit = cur_limit * granularity - delta;
    }

    soc_reg_field_set(unit, reg, &rval, field,
                      sal_ceil_func(new_limit, granularity));
    SOC_IF_ERROR_RETURN(soc_trident3_xpe_reg32_set(unit, reg, -1, 0,
                                                   egr_pool, rval));

    /* Adjust RQE pool resume limit, set to same limit as egress SP resume threshold */
    rval = 0;
    reg = MMU_THDR_DB_CONFIG_SPr;
    field = RESUME_LIMITf;
    granularity = 8;
    SOC_IF_ERROR_RETURN(soc_trident3_xpe_reg32_get(unit, reg, -1, 0,
                                                   egr_pool, &rval));
    soc_reg_field_set(unit, reg, &rval, field,
                      sal_ceil_func(new_limit, granularity));
    SOC_IF_ERROR_RETURN(soc_trident3_xpe_reg32_set(unit, reg, -1, 0,
                                                   egr_pool, rval));

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_egr_pool_thresh_validate(int unit, int egr_pool,
                                      int delta)
{
    uint32 rval;
    soc_reg_t reg = INVALIDr;
    soc_field_t field = INVALIDf;
    int granularity = 1;
    int cur_limit;

    /* Validate egress service pool threshold */
    rval = 0;
    reg = MMU_THDM_DB_POOL_SHARED_LIMITr;
    field = SHARED_LIMITf;
    granularity = 1;
    SOC_IF_ERROR_RETURN(soc_trident3_xpe_reg32_get(unit, reg, -1, 0,
                                                   egr_pool, &rval));
    cur_limit = soc_reg_field_get(unit, reg, rval, field);
    if ((cur_limit * granularity - delta) < 0) {
        /* Delta greater than current limit */
        LOG_ERROR(BSL_LS_BCM_COSQ,
            (BSL_META_U(unit, "Error: Delta(%d) used to adjust(subtract)\n"
            "egress service pool limit is greater than current limit(%d)!\n"),
             delta, cur_limit));
        return BCM_E_INTERNAL;
    }

    /* Validate egress service pool resume limit */
    rval = 0;
    reg = MMU_THDM_DB_POOL_RESUME_LIMITr;
    field = RESUME_LIMITf;
    granularity = 8;
    SOC_IF_ERROR_RETURN(soc_trident3_xpe_reg32_get(unit, reg, -1, 0,
                                                   egr_pool, &rval));
    cur_limit = soc_reg_field_get(unit, reg, rval, field);
    if ((cur_limit * granularity - delta) < 0) {
        /* Delta greater than current limit */
        LOG_ERROR(BSL_LS_BCM_COSQ,
            (BSL_META_U(unit, "Error: Delta(%d) used to adjust(subtract)\n"
            "egress service resume pool limit is greater than current limit(%d)!\n"),
             delta, cur_limit));
        return BCM_E_INTERNAL;
    }

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_egr_queue_limit_enable_set(int unit, bcm_gport_t gport,
                                        bcm_cos_queue_t cosq,
                                        bcm_cosq_control_t type,
                                        int arg)
{
    bcm_port_t local_port;
    int startq, pipe = 0;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm, base_mem = INVALIDm;
    soc_field_t field_name = INVALIDf;
    int enable;

    if (arg < 0) {
        return BCM_E_PARAM;
    }

    arg = arg ? 1 : 0;

    if ((type == bcmCosqControlEgressUCQueueLimitEnable) ||
        (type == bcmCosqControlEgressUCQueueColorLimitEnable)) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                            &local_port, &startq, NULL));
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        } else {
            if (cosq < 0) {
                return BCM_E_PARAM;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve
                 (unit, local_port, cosq, _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                  NULL, &startq, NULL));
        }

        base_mem = MMU_THDU_Q_TO_QGRP_MAPm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        if (type == bcmCosqControlEgressUCQueueLimitEnable) {
            field_name = Q_LIMIT_ENABLEf;
        } else if (type == bcmCosqControlEgressUCQueueColorLimitEnable) {
            field_name = Q_COLOR_ENABLE_CELLf;
        }
        enable = soc_mem_field32_get(unit, mem, entry, field_name);
        if (enable != arg) {
            soc_mem_field32_set(unit, mem, entry, field_name, arg);
            BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, startq, entry));
        }
    } else if ((type == bcmCosqControlEgressMCQueueLimitEnable) ||
        (type == bcmCosqControlEgressMCQueueColorLimitEnable)) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                            &local_port, &startq, NULL));
        } else {
            if (cosq < 0) {
                return BCM_E_PARAM;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, local_port, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                            NULL, &startq, NULL));
        }

        base_mem = MMU_THDM_MCQE_QUEUE_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        if (type == bcmCosqControlEgressMCQueueLimitEnable) {
            field_name = Q_LIMIT_ENABLEf;
        } else if (type == bcmCosqControlEgressMCQueueColorLimitEnable) {
            field_name = Q_COLOR_LIMIT_ENABLEf;
        }
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        enable = soc_mem_field32_get(unit, mem, entry, field_name);
        if (enable != arg) {
            soc_mem_field32_set(unit, mem, entry, field_name, arg);
            BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, startq, entry));
        }

        base_mem = MMU_THDM_DB_QUEUE_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        if (type == bcmCosqControlEgressMCQueueLimitEnable) {
            field_name = Q_LIMIT_ENABLEf;
        } else if (type == bcmCosqControlEgressMCQueueColorLimitEnable) {
            field_name = Q_COLOR_LIMIT_ENABLEf;
        }
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        enable = soc_mem_field32_get(unit, mem, entry, field_name);
        if (enable != arg) {
            soc_mem_field32_set(unit, mem, entry, field_name, arg);
            BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, startq, entry));
        }
    } else {
        return BCM_E_PARAM;
    }

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_egr_queue_limit_enable_get(int unit, bcm_gport_t gport,
                                         bcm_cos_queue_t cosq,
                                         bcm_cosq_control_t type,
                                         int *arg)
{
    bcm_port_t local_port;
    int startq, pipe = 0;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm, base_mem = INVALIDm;
    soc_field_t field_name = INVALIDf;

    if ((type == bcmCosqControlEgressUCQueueLimitEnable) ||
        (type == bcmCosqControlEgressUCQueueColorLimitEnable)) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                          _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                          &local_port, &startq, NULL));
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        } else {
            if (cosq < 0) {
                return BCM_E_PARAM;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve
                    (unit, local_port, cosq, _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                     NULL, &startq, NULL));
        }

        base_mem = MMU_THDU_Q_TO_QGRP_MAPm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        if (type == bcmCosqControlEgressUCQueueLimitEnable) {
            field_name = Q_LIMIT_ENABLEf;
        } else if (type == bcmCosqControlEgressUCQueueColorLimitEnable) {
            field_name = Q_COLOR_ENABLE_CELLf;
        }
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        *arg = soc_mem_field32_get(unit, mem, entry, field_name);
    } else if ((type == bcmCosqControlEgressMCQueueLimitEnable) ||
               (type == bcmCosqControlEgressMCQueueColorLimitEnable)) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                     _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                     &local_port, &startq, NULL));
        } else {
            if (cosq < 0) {
                return BCM_E_PARAM;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, local_port, cosq,
                                    _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                     NULL, &startq, NULL));
        }
        base_mem = MMU_THDM_MCQE_QUEUE_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        if (type == bcmCosqControlEgressMCQueueLimitEnable) {
           field_name = Q_LIMIT_ENABLEf;
        } else if (type == bcmCosqControlEgressMCQueueColorLimitEnable) {
           field_name = Q_COLOR_LIMIT_ENABLEf;
        }

        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        *arg = soc_mem_field32_get(unit, mem, entry, field_name);
    } else {
        return BCM_E_PARAM;
    }
    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_egr_port_pool_set(int unit, bcm_gport_t gport,
                               bcm_cos_queue_t cosq,
                               bcm_cosq_control_t type, int arg)
{
    bcm_port_t local_port;
    uint32 max_val;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm, base_mem = INVALIDm;
    soc_field_t fld_limit = INVALIDf;
    int granularity = 1;
    int pool, midx, pipe = 0;

    if (arg < 0) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                     _BCM_HX5_COSQ_INDEX_STYLE_EGR_POOL,
                                     &local_port, &pool, NULL));

    if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport) || IS_CPU_PORT(unit, local_port)) {
        base_mem = MMU_THDM_DB_PORTSP_CONFIGm;
    } else {
        base_mem = MMU_THDU_CONFIG_PORTm;
    }

    mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
    midx = SOC_TD3_MMU_PIPED_MEM_INDEX(unit, local_port, base_mem, pool);
    BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, midx, entry));

    switch (type) {
        case bcmCosqControlEgressPortPoolYellowLimitBytes:
            if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport) || IS_CPU_PORT(unit, local_port)) {
                fld_limit = YELLOW_SHARED_LIMITf;
            } else {
                fld_limit = YELLOW_LIMITf;
            }
            granularity = 8;
            break;
        case bcmCosqControlEgressPortPoolRedLimitBytes:
            if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport) || IS_CPU_PORT(unit, local_port)) {
                fld_limit = RED_SHARED_LIMITf;
            } else {
                fld_limit = RED_LIMITf;
            }
            granularity = 8;
            break;
        default:
            return BCM_E_UNAVAIL;
    }

    arg = (arg + _HX5_MMU_BYTES_PER_CELL - 1) / _HX5_MMU_BYTES_PER_CELL;

    /* Check for min/max values */
    max_val = (1 << soc_mem_field_length(unit, mem, fld_limit)) - 1;
    if ((arg < 0) || ((arg/granularity) > max_val)) {
        return BCM_E_PARAM;
    } else {
        soc_mem_field32_set(unit, mem, entry, fld_limit, (arg/granularity));
    }
    BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, midx, entry));

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_egr_port_pool_get(int unit, bcm_gport_t gport,
                               bcm_cos_queue_t cosq,
                               bcm_cosq_control_t type, int *arg)
{
    bcm_port_t local_port;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm, base_mem = INVALIDm;
    int granularity = 1;
    int pool, midx, pipe = 0;

    if (!arg) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                     _BCM_HX5_COSQ_INDEX_STYLE_EGR_POOL,
                                     &local_port, &pool, NULL));

    if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport) || IS_CPU_PORT(unit, local_port)) {
        base_mem = MMU_THDM_DB_PORTSP_CONFIGm;
    } else {
        base_mem = MMU_THDU_CONFIG_PORTm;
    }

    
    mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
    midx = SOC_TD3_MMU_PIPED_MEM_INDEX(unit, local_port, base_mem, pool);
    BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, midx, entry));

    switch (type) {
        case bcmCosqControlEgressPortPoolYellowLimitBytes:
            if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport) || IS_CPU_PORT(unit, local_port)) {
                *arg = soc_mem_field32_get(unit, mem, entry,
                                           YELLOW_SHARED_LIMITf);
            } else {
                *arg = soc_mem_field32_get(unit, mem, entry, YELLOW_LIMITf);
            }
            granularity = 8;
            break;
        case bcmCosqControlEgressPortPoolRedLimitBytes:
            if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport) || IS_CPU_PORT(unit, local_port)) {
                *arg = soc_mem_field32_get(unit, mem, entry, RED_SHARED_LIMITf);
            } else {
                *arg = soc_mem_field32_get(unit, mem, entry, RED_LIMITf);
            }
            granularity = 8;
            break;
        default:
            return BCM_E_UNAVAIL;
    }

    *arg = (*arg) * granularity * _HX5_MMU_BYTES_PER_CELL;
    return BCM_E_NONE;
}

/*
 * This function is used to get the
 * Min and Max value of ingress PG or SP
 */
STATIC int
_bcm_hx5_cosq_ing_res_get(int unit, bcm_gport_t gport, bcm_cos_queue_t cosq,
                          bcm_cosq_control_t type, int *arg)
{
    bcm_port_t local_port;
    int midx;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm, base_mem = INVALIDm;
    soc_field_t fld_limit = INVALIDf;
    int pipe = 0, port_pg;
    int pool, granularity = 1;

    if ((cosq < 0) || (cosq >= _HX5_MMU_NUM_INT_PRI)) {
        /* Error. Input pri > Max Pri_Grp */
        return BCM_E_PARAM;
    }

    if (arg == NULL) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
        BCM_GPORT_IS_SCHEDULER(gport) ||
        BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
    if (local_port < 0) {
        return BCM_E_PORT;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_ingress_pg_get(unit, gport, cosq, &port_pg, NULL));
    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_ingress_sp_get(unit, gport, cosq, &pool, NULL));

    if ((type == bcmCosqControlIngressPortPGSharedLimitBytes) ||
        (type == bcmCosqControlIngressPortPGMinLimitBytes) ||
        (type == bcmCosqControlIngressPortPGHeadroomLimitBytes) ||
        (type == bcmCosqControlIngressPortPGResetOffsetBytes) ||
        (type == bcmCosqControlIngressPortPGResetFloorBytes)) {
        base_mem = THDI_PORT_PG_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        /* get index for Port-PG */
        midx = SOC_TD3_MMU_PIPED_MEM_INDEX(unit, local_port, base_mem, port_pg);
    } else if ((type == bcmCosqControlIngressPortPoolMaxLimitBytes) ||
               (type == bcmCosqControlIngressPortPoolMinLimitBytes)) {
        base_mem = THDI_PORT_SP_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        /* get index for Port-SP */
        midx = SOC_TD3_MMU_PIPED_MEM_INDEX(unit, local_port, base_mem, pool);
    } else {
        return BCM_E_UNAVAIL;
    }

    if (midx < 0) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, midx, entry));

    switch (type) {
        case bcmCosqControlIngressPortPGSharedLimitBytes:
            fld_limit = PG_SHARED_LIMITf;
            granularity = 1;
            break;
        case bcmCosqControlIngressPortPoolMaxLimitBytes:
            fld_limit = PORT_SP_MAX_LIMITf;
            granularity = 1;
            break;
        case bcmCosqControlIngressPortPGMinLimitBytes:
            fld_limit = PG_MIN_LIMITf;
            granularity = 1;
            break;
        case bcmCosqControlIngressPortPoolMinLimitBytes:
            fld_limit = PORT_SP_MIN_LIMITf;
            granularity = 1;
            break;
        case bcmCosqControlIngressPortPGHeadroomLimitBytes:
            fld_limit = PG_HDRM_LIMITf;
            granularity = 1;
            break;
        case bcmCosqControlIngressPortPGResetFloorBytes:
            fld_limit = PG_RESET_FLOORf;
            granularity = 1;
            break;
        case bcmCosqControlIngressPortPGResetOffsetBytes:
            fld_limit = PG_RESET_OFFSETf;
            granularity = 1;
            break;
        /* coverity[dead_error_begin] */
        default:
            return BCM_E_UNAVAIL;
    }

    *arg = soc_mem_field32_get(unit, mem, entry, fld_limit);
    *arg = (*arg) * granularity * _HX5_MMU_BYTES_PER_CELL;

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_ing_res_set(int unit, bcm_gport_t gport, bcm_cos_queue_t cosq,
                          bcm_cosq_control_t type, int arg)
{
    bcm_port_t local_port;
    int midx;
    uint32 max_val;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm, base_mem = INVALIDm;
    soc_field_t fld_limit = INVALIDf;
    int pipe = 0, port_pg;
    int pool, granularity = 1;
    int  ing_shd_size, cur_val;

    if ((cosq < 0) || (cosq >= _HX5_MMU_NUM_INT_PRI)) {
        /* Error. Input pri > Max Pri_Grp */
        return BCM_E_PARAM;
    }

    if (arg < 0) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
        BCM_GPORT_IS_SCHEDULER(gport) ||
        BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        return BCM_E_PARAM;
    }

    arg = (arg + _HX5_MMU_BYTES_PER_CELL - 1) / _HX5_MMU_BYTES_PER_CELL;
    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
    if (local_port < 0) {
        return BCM_E_PORT;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_ingress_pg_get(unit, gport, cosq, &port_pg, NULL));
    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_ingress_sp_get(unit, gport, cosq, &pool, NULL));

    if ((type == bcmCosqControlIngressPortPGSharedLimitBytes) ||
        (type == bcmCosqControlIngressPortPGMinLimitBytes) ||
        (type == bcmCosqControlIngressPortPGHeadroomLimitBytes) ||
        (type == bcmCosqControlIngressPortPGResetOffsetBytes) ||
        (type == bcmCosqControlIngressPortPGResetFloorBytes)) {
        base_mem = THDI_PORT_PG_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        /* get index for Port-PG */
        midx = SOC_TD3_MMU_PIPED_MEM_INDEX(unit, local_port, base_mem, port_pg);
    } else if ((type == bcmCosqControlIngressPortPoolMaxLimitBytes) ||
               (type == bcmCosqControlIngressPortPoolMinLimitBytes)) {
        base_mem = THDI_PORT_SP_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        /* get index for Port-SP */
        midx = SOC_TD3_MMU_PIPED_MEM_INDEX(unit, local_port, base_mem, pool);
    } else {
        return BCM_E_UNAVAIL;
    }

    if (midx < 0) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, midx, entry));

    switch (type) {
        case bcmCosqControlIngressPortPGSharedLimitBytes:
            fld_limit = PG_SHARED_LIMITf;
            granularity = 1;
            break;
        case bcmCosqControlIngressPortPoolMaxLimitBytes:
            fld_limit = PORT_SP_MAX_LIMITf;
            granularity = 1;
            break;
        case bcmCosqControlIngressPortPGMinLimitBytes:
            fld_limit = PG_MIN_LIMITf;
            granularity = 1;
            break;
        case bcmCosqControlIngressPortPoolMinLimitBytes:
            fld_limit = PORT_SP_MIN_LIMITf;
            granularity = 1;
            break;
        case bcmCosqControlIngressPortPGHeadroomLimitBytes:
            fld_limit = PG_HDRM_LIMITf;
            granularity = 1;
            break;
        case bcmCosqControlIngressPortPGResetFloorBytes:
            fld_limit = PG_RESET_FLOORf;
            granularity = 1;
            break;
        case bcmCosqControlIngressPortPGResetOffsetBytes:
            fld_limit = PG_RESET_OFFSETf;
            granularity = 1;
            break;
        /* coverity[dead_error_begin] */
        default:
            return BCM_E_UNAVAIL;
    }

    /* Recalculate Shared Values if Min Changed */
    cur_val = soc_mem_field32_get(unit, mem, entry, fld_limit);

    if((arg / granularity) == cur_val) {
        return BCM_E_NONE;
    }

    if (type == bcmCosqControlIngressPortPGMinLimitBytes) {
        int delta = 0; /* In Cells */
        uint32 rval = 0;
        /* Read THDI shared size from Service pool 0 */
        SOC_IF_ERROR_RETURN
            (READ_THDI_BUFFER_CELL_LIMIT_SPr(unit, 0, &rval));
        ing_shd_size = soc_reg_field_get(unit, THDI_BUFFER_CELL_LIMIT_SPr,
                                         rval, LIMITf);
        if ((arg / granularity) > cur_val) {
           /* New Min Val > Cur Min Val
            * So reduce the Shared values first and then
            * Increase the Min Value for given resource */             
            delta = ((arg / granularity) - cur_val) * granularity;	
            if (delta > ing_shd_size) {
                return BCM_E_PARAM;
            }

            SOC_IF_ERROR_RETURN(
                soc_hx5_mmu_config_shared_buf_recalc(unit, 1 /* ing */,
                                                     ing_shd_size - delta,
                                                     -1, -1, 1));

            /* the value may be changed by soc_hx5_mmu_config_res_limits_update
             * so read the register again in order to keep consistent  */
            BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, midx, entry));
        }

        /* Check for min/max values */
        max_val = (1 << soc_mem_field_length(unit, mem, fld_limit)) - 1;
        if ((arg < 0) || ((arg/granularity) > max_val)) {
            return BCM_E_PARAM;
        }

        soc_mem_field32_set(unit, mem, entry, fld_limit, (arg/granularity));
        BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, midx, entry));

        if ((arg / granularity) < cur_val) {
           /* New Min Val < Cur Min Val
            * So reduce the Min values first and then
            * Increase Shared values everywhere */
            delta = (cur_val - (arg / granularity)) * granularity;
            if (delta > ing_shd_size) {
                return BCM_E_PARAM;
            }
            SOC_IF_ERROR_RETURN(
                soc_hx5_mmu_config_shared_buf_recalc(unit, 1 /* ing */,
                                                     ing_shd_size + delta,
                                                     -1, -1,  0));
        }
    } else {
        /* Check for min/max values */
        max_val = (1 << soc_mem_field_length(unit, mem, fld_limit)) - 1;
        if ((arg < 0) || ((arg/granularity) > max_val)) {
            return BCM_E_PARAM;
        }
        soc_mem_field32_set(unit, mem, entry, fld_limit, (arg/granularity));
        BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, midx, entry));
    }

	return BCM_E_NONE;
}

/*
 * This function is used to get ingress pool
 * limit given Ingress [Port, Priority]
 */
STATIC int
_bcm_hx5_cosq_ing_res_limit_get(int unit, bcm_gport_t gport, bcm_cos_t cosq,
                               bcm_cosq_control_t type, int *arg)
{
    uint32 rval = 0x0;
    int pool;
    int local_port;
    soc_reg_t reg = INVALIDr;

    if (arg == NULL) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
        BCM_GPORT_IS_SCHEDULER(gport) ||
        BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));

    if (!SOC_PORT_VALID(unit, local_port)) {
        return BCM_E_PORT;
    }

    if (type == bcmCosqControlIngressPoolLimitBytes) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_ing_pool_get(unit, gport, cosq,
                                       bcmCosqControlIngressPool,
                                       &pool));
        reg = THDI_BUFFER_CELL_LIMIT_SPr;
    } else if (type == bcmCosqControlIngressHeadroomPoolLimitBytes) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_ing_pool_get(unit, gport, cosq,
                                        bcmCosqControlIngressHeadroomPool,
                                        &pool));
        reg = THDI_HDRM_BUFFER_CELL_LIMIT_HPr;
    } else {
        return BCM_E_PARAM;
    }

    SOC_IF_ERROR_RETURN(
        soc_trident3_xpe_reg32_get(unit,reg,
                                   -1, 0, pool, &rval));
    *arg = soc_reg_field_get(unit, reg, rval, LIMITf);

    *arg *= _HX5_MMU_BYTES_PER_CELL;

    return BCM_E_NONE;
}

/*
 * This function is used to set ingress pool
 * limit given Ingress [Port, Priority]
 */
STATIC int
_bcm_hx5_cosq_ing_res_limit_set(int unit, bcm_gport_t gport, bcm_cos_t cosq,
                               bcm_cosq_control_t type, int arg)
{
    uint32 rval = 0x0;
    int pool;
    int local_port;
    soc_reg_t reg = INVALIDr;

    if (arg < 0) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
        BCM_GPORT_IS_SCHEDULER(gport) ||
        BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        return BCM_E_PARAM;
    }
    BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));

    if (!SOC_PORT_VALID(unit, local_port)) {
        return BCM_E_PORT;
    }

    arg = (arg + _HX5_MMU_BYTES_PER_CELL - 1) / _HX5_MMU_BYTES_PER_CELL;

    if (type == bcmCosqControlIngressPoolLimitBytes) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_ing_pool_get(unit, gport, cosq,
                                       bcmCosqControlIngressPool,
                                       &pool));
        reg = THDI_BUFFER_CELL_LIMIT_SPr;
    } else if (type == bcmCosqControlIngressHeadroomPoolLimitBytes) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_ing_pool_get(unit, gport, cosq,
                                       bcmCosqControlIngressHeadroomPool,
                                       &pool));
        reg = THDI_HDRM_BUFFER_CELL_LIMIT_HPr;
    } else {
        return BCM_E_PARAM;
    }

    soc_reg_field_set(unit, reg, &rval, LIMITf, arg);
    SOC_IF_ERROR_RETURN(
        soc_trident3_xpe_reg32_set(unit, reg,
                                   -1, 0, pool, rval));

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_ing_res_enable_get(int unit, bcm_gport_t gport,
        bcm_cos_queue_t cosq, bcm_cosq_control_t type,
        int *arg)
{
    bcm_port_t local_port;
    int midx;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm, base_mem = INVALIDm;
    soc_field_t fld_en = INVALIDf;
    int port_pg;

    if ((cosq < 0) || (cosq >= _HX5_MMU_NUM_INT_PRI)) {
        /* Error. Input pri > Max Pri_Grp */
        return BCM_E_PARAM;
    }

    if (arg == NULL) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
            BCM_GPORT_IS_SCHEDULER(gport) ||
            BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
    if (!SOC_PORT_VALID(unit, local_port)) {
        return BCM_E_PORT;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_ingress_pg_get(unit, gport, cosq, &port_pg, NULL));


    if (type == bcmCosqControlIngressPortPGGlobalHeadroomEnable) {
        base_mem = THDI_PORT_PG_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[0];
        /* get index for Port-PG */
        midx = SOC_TD3_MMU_PIPED_MEM_INDEX(unit, local_port, base_mem, port_pg);
    } else {
        return BCM_E_UNAVAIL;
    }

    if (midx < 0) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, midx, entry));

    switch (type) {
        case bcmCosqControlIngressPortPGGlobalHeadroomEnable:
            fld_en = PG_GBL_HDRM_ENf;
            break;
            /* coverity[dead_error_begin] */
        default:
            return BCM_E_UNAVAIL;
    }

    *arg = soc_mem_field32_get(unit, mem, entry, fld_en);

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_ing_res_enable_set(int unit, bcm_gport_t gport,
        bcm_cos_queue_t cosq, bcm_cosq_control_t type,
        int arg)
{
    bcm_port_t local_port;
    int midx;
    uint32 max_val;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm, base_mem = INVALIDm;
    soc_field_t fld_en = INVALIDf;
    int port_pg;

    if ((cosq < 0) || (cosq >= _HX5_MMU_NUM_INT_PRI)) {
        /* Error. Input pri > Max Pri_Grp */
        return BCM_E_PARAM;
    }

    if (arg < 0) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
            BCM_GPORT_IS_SCHEDULER(gport) ||
            BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
    if (!SOC_PORT_VALID(unit, local_port)) {
        return BCM_E_PORT;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_ingress_pg_get(unit, gport, cosq, &port_pg, NULL));

    if (type == bcmCosqControlIngressPortPGGlobalHeadroomEnable) {
        base_mem = THDI_PORT_PG_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[0];
        /* get index for Port-PG */
        midx = SOC_TD3_MMU_PIPED_MEM_INDEX(unit, local_port, base_mem, port_pg);
    } else {
        return BCM_E_UNAVAIL;
    }

    if (midx < 0) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, midx, entry));

    switch (type) {
        case bcmCosqControlIngressPortPGGlobalHeadroomEnable:
            fld_en = PG_GBL_HDRM_ENf;
            break;
            /* coverity[dead_error_begin] */
        default:
            return BCM_E_UNAVAIL;
    }

    /* Check for min/max values */
    max_val = (1 << soc_mem_field_length(unit, mem, fld_en)) - 1;
    if ((arg < 0) || (arg > max_val)) {
        return BCM_E_PARAM;
    }

    if (type == bcmCosqControlIngressPortPGGlobalHeadroomEnable) {
        soc_mem_field32_set(unit, mem, entry, fld_en, arg ? 1 : 0);
        /* coverity[negative_returns] */
        BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, midx, entry));
    }

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_dynamic_thresh_enable_set(int unit,
                        bcm_gport_t gport, bcm_cos_queue_t cosq,
                        bcm_cosq_control_t type, int arg)
{
    bcm_port_t local_port;
    int startq, pipe = 0;
    int from_cos, to_cos, ci;
    int midx;
    uint32 rval;
    uint32 entry[SOC_MAX_MEM_WORDS];
    uint32 entry2[SOC_MAX_MEM_WORDS];
    soc_mem_t base_mem = INVALIDm, base_mem2 = INVALIDm;
    soc_mem_t mem = INVALIDm, mem2 = INVALIDm;
    soc_reg_t reg = INVALIDr;
    int port_pg;
    static const soc_reg_t prigroup_reg[] = {
        THDI_PORT_PRI_GRP0r, THDI_PORT_PRI_GRP1r
    };
    static const soc_field_t prigroup_field[] = {
        PRI0_GRPf, PRI1_GRPf, PRI2_GRPf, PRI3_GRPf,
        PRI4_GRPf, PRI5_GRPf, PRI6_GRPf, PRI7_GRPf,
        PRI8_GRPf, PRI9_GRPf, PRI10_GRPf, PRI11_GRPf,
        PRI12_GRPf, PRI13_GRPf, PRI14_GRPf, PRI15_GRPf
    };

    if (type == bcmCosqControlIngressPortPGSharedDynamicEnable) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
            BCM_GPORT_IS_SCHEDULER(gport) ||
            BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        }
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
        if (local_port < 0) {
            return BCM_E_PORT;
        }

        if ((cosq < 0) || (cosq >= _HX5_MMU_NUM_INT_PRI)) {
            /* Error. Input pri > Max Pri_Grp */
            return BCM_E_PARAM;
        }

        /* get PG for port using Port+Cos */
        if (cosq < _HX5_MMU_NUM_PG) {
            reg = prigroup_reg[0];
        } else {
            reg = prigroup_reg[1];
        }

        SOC_IF_ERROR_RETURN
            (soc_reg32_get(unit, reg, local_port, 0, &rval));
        port_pg = soc_reg_field_get(unit, reg, rval, prigroup_field[cosq]);
        base_mem = THDI_PORT_PG_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        /* get index for Port-PG */
        midx = SOC_TD3_MMU_PIPED_MEM_INDEX(unit, local_port, base_mem, port_pg);
        BCM_IF_ERROR_RETURN
            (soc_mem_read(unit, mem, MEM_BLOCK_ALL, midx, entry));
        soc_mem_field32_set(unit, mem, entry,
                            PG_SHARED_DYNAMICf, arg ? 1 : 0);
        /* Set default alpha value*/
        if (arg) {
            soc_mem_field32_set(unit, mem, entry, PG_SHARED_LIMITf,
                                SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_128);
        }
        SOC_IF_ERROR_RETURN
            (soc_mem_write(unit, mem, MEM_BLOCK_ALL, midx, entry));
    } else if (type == bcmCosqControlEgressUCSharedDynamicEnable) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                           _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                           &local_port, &startq, NULL));
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        } else {
            if (cosq == BCM_COS_INVALID) {
                from_cos = to_cos = 0;
            } else {
                from_cos = to_cos = cosq;
            }

            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            for (ci = from_cos; ci <= to_cos; ci++) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_index_resolve(unit, local_port, ci,
                                         _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                         NULL, &startq, NULL));

            }
        }
        base_mem = MMU_THDU_CONFIG_QUEUEm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];

        BCM_IF_ERROR_RETURN
            (soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        soc_mem_field32_set(unit, mem, entry,
                            Q_LIMIT_DYNAMIC_CELLf, arg ? 1 : 0);
        /* Set default alpha value*/
        if (arg) {
            soc_mem_field32_set(unit, mem, entry, Q_SHARED_ALPHA_CELLf,
                                SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_128);
        }
        SOC_IF_ERROR_RETURN
            (soc_mem_write(unit, mem, MEM_BLOCK_ALL, startq, entry));
    } else if (type == bcmCosqControlEgressMCSharedDynamicEnable) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                      _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                      &local_port, &startq, NULL));
        }
        else {
            if (cosq == BCM_COS_INVALID) {
                from_cos = to_cos = 0;
            } else {
                from_cos = to_cos = cosq;
            }

            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            for (ci = from_cos; ci <= to_cos; ci++) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_index_resolve(unit, local_port, ci,
                                         _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                         NULL, &startq, NULL));

            }
        }

        base_mem = MMU_THDM_DB_QUEUE_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];

        base_mem2 = MMU_THDM_MCQE_QUEUE_CONFIGm;
        mem2 = SOC_MEM_UNIQUE_ACC(unit, base_mem2)[pipe];

        BCM_IF_ERROR_RETURN
            (soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        soc_mem_field32_set(unit, mem, entry, Q_LIMIT_DYNAMICf, arg ? 1 : 0);
        /* Set default alpha value*/
        if (arg) {
            soc_mem_field32_set(unit, mem, entry, Q_SHARED_ALPHAf,
                                SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_128);
        }
        SOC_IF_ERROR_RETURN
            (soc_mem_write(unit, mem, MEM_BLOCK_ALL, startq, entry));

        BCM_IF_ERROR_RETURN
            (soc_mem_read(unit, mem2, MEM_BLOCK_ALL, startq, entry2));
        soc_mem_field32_set(unit, mem2, entry2, Q_LIMIT_DYNAMICf, arg ? 1 : 0);
        /* Set default alpha value*/
        if (arg) {
            soc_mem_field32_set(unit, mem2, entry2, Q_SHARED_ALPHAf,
                                SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_128);
        }
        SOC_IF_ERROR_RETURN
            (soc_mem_write(unit, mem2, MEM_BLOCK_ALL, startq, entry2));

    } else {
        return BCM_E_PARAM;
    }

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_dynamic_thresh_enable_get(int unit,
                        bcm_gport_t gport, bcm_cos_queue_t cosq,
                        bcm_cosq_control_t type, int *arg)
{
    bcm_port_t local_port;
    int startq, pipe = 0, from_cos, to_cos, ci, midx, port_pg;
    uint32 rval;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm, base_mem = INVALIDm;
    soc_reg_t reg = INVALIDr;
    static const soc_reg_t prigroup_reg[] = {
        THDI_PORT_PRI_GRP0r, THDI_PORT_PRI_GRP1r
    };
    static const soc_field_t prigroup_field[] = {
        PRI0_GRPf, PRI1_GRPf, PRI2_GRPf, PRI3_GRPf,
        PRI4_GRPf, PRI5_GRPf, PRI6_GRPf, PRI7_GRPf,
        PRI8_GRPf, PRI9_GRPf, PRI10_GRPf, PRI11_GRPf,
        PRI12_GRPf, PRI13_GRPf, PRI14_GRPf, PRI15_GRPf
    };

    if (!arg) {
        return BCM_E_PARAM;
    }

    if (type == bcmCosqControlIngressPortPGSharedDynamicEnable) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
            BCM_GPORT_IS_SCHEDULER(gport) ||
            BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        }
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
        if (local_port < 0) {
            return BCM_E_PORT;
        }

        if ((cosq < 0) || (cosq >= _HX5_MMU_NUM_INT_PRI)) {
            /* Error. Input pri > Max Pri_Grp */
            return BCM_E_PARAM;
        }
        /* get PG for port using Port+Cos */
        if (cosq < _HX5_MMU_NUM_PG) {
            reg = prigroup_reg[0];
        } else {
            reg = prigroup_reg[1];
        }

        SOC_IF_ERROR_RETURN
            (soc_reg32_get(unit, reg, local_port, 0, &rval));
        port_pg = soc_reg_field_get(unit, reg, rval, prigroup_field[cosq]);
        base_mem = THDI_PORT_PG_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        /* get index for Port-PG */
        midx = SOC_TD3_MMU_PIPED_MEM_INDEX(unit, local_port, base_mem, port_pg);

        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL,
                                 midx, entry));
        *arg = soc_mem_field32_get(unit, mem, entry, PG_SHARED_DYNAMICf);

    } else if (type == bcmCosqControlEgressUCSharedDynamicEnable) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                         _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                         &local_port, &startq, NULL));
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        } else {
            if (cosq == BCM_COS_INVALID) {
                from_cos = to_cos = 0;
            } else {
                from_cos = to_cos = cosq;
            }

            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            for (ci = from_cos; ci <= to_cos; ci++) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_index_resolve(unit, local_port, ci,
                          _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                          NULL, &startq, NULL));
            }
        }
        base_mem = MMU_THDU_CONFIG_QUEUEm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];

        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL,
                                 startq, entry));
        *arg = soc_mem_field32_get(unit, mem, entry, Q_LIMIT_DYNAMIC_CELLf);
    } else if (type == bcmCosqControlEgressMCSharedDynamicEnable) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                         _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                         &local_port, &startq, NULL));
        }
        else {
            if (cosq == BCM_COS_INVALID) {
                from_cos = to_cos = 0;
            } else {
                from_cos = to_cos = cosq;
            }

            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            for (ci = from_cos; ci <= to_cos; ci++) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_index_resolve(unit, local_port, ci,
                                         _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                         NULL, &startq, NULL));
            }
        }
        base_mem = MMU_THDM_DB_QUEUE_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];

        BCM_IF_ERROR_RETURN
            (soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        *arg = soc_mem_field32_get(unit, mem, entry, Q_LIMIT_DYNAMICf);
    } else {
        return BCM_E_PARAM;
    }

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_alpha_set(int unit,
        bcm_gport_t gport, bcm_cos_queue_t cosq,
        bcm_cosq_control_t type,
        bcm_cosq_control_drop_limit_alpha_value_t arg)
{
    bcm_port_t local_port;
    int startq, midx, pipe = 0;
    uint32 rval;
    uint32 entry[SOC_MAX_MEM_WORDS];
    uint32 entry2[SOC_MAX_MEM_WORDS];
    soc_mem_t base_mem = INVALIDm, base_mem2 = INVALIDm;
    soc_mem_t mem = INVALIDm, mem2 = INVALIDm;
    int alpha, dynamic_thresh_mode, port_pg;
    soc_reg_t reg = INVALIDr;
    int type_uc = 0, type_mc = 0;
    static const soc_reg_t prigroup_reg[] = {
        THDI_PORT_PRI_GRP0r, THDI_PORT_PRI_GRP1r
    };
    static const soc_field_t prigroup_field[] = {
        PRI0_GRPf, PRI1_GRPf, PRI2_GRPf, PRI3_GRPf,
        PRI4_GRPf, PRI5_GRPf, PRI6_GRPf, PRI7_GRPf,
        PRI8_GRPf, PRI9_GRPf, PRI10_GRPf, PRI11_GRPf,
        PRI12_GRPf, PRI13_GRPf, PRI14_GRPf, PRI15_GRPf
    };

    if (type == bcmCosqControlDropLimitAlpha) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            type_uc = 1;
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            type_mc = 1;
        }
    } else if (type == bcmCosqControlUCDropLimitAlpha) {
        if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        }
        type_uc = 1;
    } else if (type == bcmCosqControlMCDropLimitAlpha) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        }
        type_mc = 1;
    }

    switch(arg) {
        case bcmCosqControlDropLimitAlpha_1_128:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_128;
            break;
        case bcmCosqControlDropLimitAlpha_1_64:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_64;
            break;
        case bcmCosqControlDropLimitAlpha_1_32:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_32;
            break;
        case bcmCosqControlDropLimitAlpha_1_16:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_16;
            break;
        case bcmCosqControlDropLimitAlpha_1_8:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_8;
            break;
        case bcmCosqControlDropLimitAlpha_1_4:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_4;
            break;
        case bcmCosqControlDropLimitAlpha_1_2:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_2;
            break;
        case bcmCosqControlDropLimitAlpha_1:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1;
            break;
        case bcmCosqControlDropLimitAlpha_2:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_2;
            break;
        case bcmCosqControlDropLimitAlpha_4:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_4;
            break;
        case bcmCosqControlDropLimitAlpha_8:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_8;
            break;
        default:
            return BCM_E_PARAM;
    }

    if (type_uc == 1) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_dynamic_thresh_enable_get(unit, gport, cosq,
                                                     bcmCosqControlEgressUCSharedDynamicEnable,
                                                     &dynamic_thresh_mode));
        if (!dynamic_thresh_mode){
            return BCM_E_CONFIG;
        }

        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                         _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                         &local_port, &startq, NULL));

        base_mem = MMU_THDU_CONFIG_QUEUEm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];

        BCM_IF_ERROR_RETURN
            (soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        soc_mem_field32_set(unit, mem, entry,
                Q_SHARED_ALPHA_CELLf, alpha);
        SOC_IF_ERROR_RETURN
            (soc_mem_write(unit, mem, MEM_BLOCK_ALL, startq, entry));
    } else if (type_mc == 1) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_dynamic_thresh_enable_get(unit, gport, cosq,
                                                     bcmCosqControlEgressMCSharedDynamicEnable,
                                                     &dynamic_thresh_mode));
        if (!dynamic_thresh_mode){
            return BCM_E_CONFIG;
        }
        if (cosq < 0) {
            return BCM_E_PARAM;
        }
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                         _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                         &local_port, &startq, NULL));
        base_mem = MMU_THDM_DB_QUEUE_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];

        base_mem2 = MMU_THDM_MCQE_QUEUE_CONFIGm;
        mem2 = SOC_MEM_UNIQUE_ACC(unit, base_mem2)[pipe];

        BCM_IF_ERROR_RETURN
            (soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        soc_mem_field32_set(unit, mem, entry, Q_SHARED_ALPHAf, alpha);
        SOC_IF_ERROR_RETURN
            (soc_mem_write(unit, mem, MEM_BLOCK_ALL, startq, entry));

        BCM_IF_ERROR_RETURN
            (soc_mem_read(unit, mem2, MEM_BLOCK_ALL, startq, entry2));
        soc_mem_field32_set(unit, mem2, entry2, Q_SHARED_ALPHAf, alpha);
        SOC_IF_ERROR_RETURN
            (soc_mem_write(unit, mem2, MEM_BLOCK_ALL, startq, entry2));
    } else  {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_dynamic_thresh_enable_get(unit, gport, cosq,
                                                     bcmCosqControlIngressPortPGSharedDynamicEnable,
                                                     &dynamic_thresh_mode));
        if (!dynamic_thresh_mode){
            return BCM_E_CONFIG;
        }
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
        if (local_port < 0) {
            return BCM_E_PORT;
        }

        if ((cosq < 0) || (cosq >= _HX5_MMU_NUM_INT_PRI)) {
            /* Error. Input pri > Max Pri_Grp */
            return BCM_E_PARAM;
        }
        /* get PG for port using Port+Cos */
        if (cosq < _HX5_MMU_NUM_PG) {
            reg = prigroup_reg[0];
        } else {
            reg = prigroup_reg[1];
        }

        SOC_IF_ERROR_RETURN
            (soc_reg32_get(unit, reg, local_port, 0, &rval));
        port_pg = soc_reg_field_get(unit, reg, rval, prigroup_field[cosq]);
        base_mem = THDI_PORT_PG_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        /* get index for Port-PG */
        midx = SOC_TD3_MMU_PIPED_MEM_INDEX(unit, local_port, base_mem, port_pg);
        BCM_IF_ERROR_RETURN
            (soc_mem_read(unit, mem, MEM_BLOCK_ALL, midx, entry));
        soc_mem_field32_set(unit, mem, entry, PG_SHARED_LIMITf, alpha);
        SOC_IF_ERROR_RETURN
            (soc_mem_write(unit, mem, MEM_BLOCK_ALL, midx, entry));
    }

    return BCM_E_NONE;
}


STATIC int
_bcm_hx5_cosq_alpha_get(int unit,
        bcm_gport_t gport, bcm_cos_queue_t cosq,
        bcm_cosq_control_t type,
        bcm_cosq_control_drop_limit_alpha_value_t *arg)
{
    bcm_port_t local_port;
    int startq, midx, pipe = 0;
    uint32 rval;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm, base_mem = INVALIDm;
    int alpha = 0, dynamic_thresh_mode, port_pg;
    soc_reg_t reg = INVALIDr;
    int type_uc = 0, type_mc = 0;
    static const soc_reg_t prigroup_reg[] = {
        THDI_PORT_PRI_GRP0r, THDI_PORT_PRI_GRP1r
    };
    static const soc_field_t prigroup_field[] = {
        PRI0_GRPf, PRI1_GRPf, PRI2_GRPf, PRI3_GRPf,
        PRI4_GRPf, PRI5_GRPf, PRI6_GRPf, PRI7_GRPf,
        PRI8_GRPf, PRI9_GRPf, PRI10_GRPf, PRI11_GRPf,
        PRI12_GRPf, PRI13_GRPf, PRI14_GRPf, PRI15_GRPf
    };

    if (!arg) {
        return BCM_E_PARAM;
    }

    if (type == bcmCosqControlDropLimitAlpha) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            type_uc = 1;
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            type_mc = 1;
        }
    } else if (type == bcmCosqControlUCDropLimitAlpha) {
        if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        }
        type_uc = 1;
    } else if (type == bcmCosqControlMCDropLimitAlpha) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        }
        type_mc = 1;
    }

    if (type_uc == 1) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_dynamic_thresh_enable_get(unit, gport, cosq,
                                                     bcmCosqControlEgressUCSharedDynamicEnable,
                                                     &dynamic_thresh_mode));
        if (!dynamic_thresh_mode){
            return BCM_E_CONFIG;
        }

        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                         _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                         &local_port, &startq, NULL));
        base_mem = MMU_THDU_CONFIG_QUEUEm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];

        BCM_IF_ERROR_RETURN
            (soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        alpha = soc_mem_field32_get(unit, mem, entry, Q_SHARED_ALPHA_CELLf);
    } else if (type_mc == 1) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_dynamic_thresh_enable_get(unit, gport, cosq,
                                                     bcmCosqControlEgressMCSharedDynamicEnable,
                                                     &dynamic_thresh_mode));
        if (!dynamic_thresh_mode){
            return BCM_E_CONFIG;
        }
        if (cosq < 0) {
            return BCM_E_PARAM;
        }
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                         _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                         &local_port, &startq, NULL));
        base_mem = MMU_THDM_DB_QUEUE_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        BCM_IF_ERROR_RETURN
            (soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        alpha = soc_mem_field32_get(unit, mem, entry, Q_SHARED_ALPHAf);
    } else if (type == bcmCosqControlDropLimitAlpha) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_dynamic_thresh_enable_get(unit, gport, cosq,
                                                     bcmCosqControlIngressPortPGSharedDynamicEnable,
                                                     &dynamic_thresh_mode));
        if (!dynamic_thresh_mode){
            return BCM_E_CONFIG;
        }
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
        if (local_port < 0) {
            return BCM_E_PORT;
        }

        if ((cosq < 0) || (cosq >= _HX5_MMU_NUM_INT_PRI)) {
            /* Error. Input pri > Max Pri_Grp */
            return BCM_E_PARAM;
        }
        /* get PG for port using Port+Cos */
        if (cosq < _HX5_MMU_NUM_PG) {
            reg = prigroup_reg[0];
        } else {
            reg = prigroup_reg[1];
        }

        SOC_IF_ERROR_RETURN
            (soc_reg32_get(unit, reg, local_port, 0, &rval));
        port_pg = soc_reg_field_get(unit, reg, rval, prigroup_field[cosq]);
        base_mem = THDI_PORT_PG_CONFIGm;
        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
        /* get index for Port-PG */
        midx = SOC_TD3_MMU_PIPED_MEM_INDEX(unit, local_port, base_mem, port_pg);
        BCM_IF_ERROR_RETURN
            (soc_mem_read(unit, mem, MEM_BLOCK_ALL, midx, entry));
        alpha = soc_mem_field32_get(unit, mem, entry, PG_SHARED_LIMITf);
    }

    switch(alpha) {
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_128:
            *arg = bcmCosqControlDropLimitAlpha_1_128;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_64:
            *arg = bcmCosqControlDropLimitAlpha_1_64;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_32:
            *arg = bcmCosqControlDropLimitAlpha_1_32;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_16:
            *arg = bcmCosqControlDropLimitAlpha_1_16;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_8:
            *arg = bcmCosqControlDropLimitAlpha_1_8;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_4:
            *arg = bcmCosqControlDropLimitAlpha_1_4;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_2:
            *arg = bcmCosqControlDropLimitAlpha_1_2;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1:
            *arg = bcmCosqControlDropLimitAlpha_1;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_2:
            *arg = bcmCosqControlDropLimitAlpha_2;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_4:
            *arg = bcmCosqControlDropLimitAlpha_4;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_8:
            *arg = bcmCosqControlDropLimitAlpha_8;
            break;
        default:
            return BCM_E_PARAM;
    }

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_time_domain_get(int unit, int time_id, int *time_value)
{
    uint32 time_domain_val;
    soc_reg_t time_domain_reg = TIME_DOMAINr;

    if (time_id < 0 || time_id > _BCM_HX5_NUM_TIME_DOMAIN - 1) {
        return SOC_E_PARAM;
    }

    if (time_value == NULL) {
        return SOC_E_PARAM;
    }

    BCM_IF_ERROR_RETURN(
        soc_reg32_get(unit, time_domain_reg, REG_PORT_ANY, time_id, &time_domain_val));
    *time_value = soc_reg_field_get(unit, time_domain_reg,
                                   time_domain_val, TIME_DOMAIN_FIELDf);
    return SOC_E_NONE;
}

STATIC int
_bcm_hx5_cosq_time_domain_set(int unit, int time_value, int *time_id)
{
    int id;
    uint32 time_domain_val;
    soc_reg_t time_domain_reg = TIME_DOMAINr;

    if (time_value < 0 || time_value > 63) {
        return SOC_E_PARAM;
    }

    for (id = 0; id < _BCM_HX5_NUM_TIME_DOMAIN; id++) {
        BCM_IF_ERROR_RETURN(
            soc_reg32_get(unit, time_domain_reg, REG_PORT_ANY, id, &time_domain_val));
        if (!hx5_time_domain_info[unit][id].ref_count) {
            soc_reg_field_set(unit, time_domain_reg, &time_domain_val,
                              TIME_DOMAIN_FIELDf, time_value);
            hx5_time_domain_info[unit][id].ref_count++;
            break;
        }
    }

    if (id == _BCM_HX5_NUM_TIME_DOMAIN) {
        return BCM_E_RESOURCE;
    }

    if (time_id) {
        *time_id = id;
    }
    SOC_IF_ERROR_RETURN(
        soc_reg32_set(unit, time_domain_reg, REG_PORT_ANY, id, time_domain_val));
    return SOC_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_wred_resolution_entry_create
 * Purpose:
 *     Assign a unused entry. Default drop rules are WRED drop.
 * Parameters:
 *     unit                - (IN) unit number
 *     index               - (OUT) entry index
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_wred_resolution_entry_create(int unit, int *index)
{
    uint32 i, rval = 0;
    soc_reg_t reg = WRED_CONG_NOTIFICATION_RESOLUTION_TABLEr;

    for (i = 0; i < _BCM_HX5_NUM_WRED_RESOLUTION_TABLE; i++) {
        if (_bcm_hx5_wred_resolution_tbl[i] == 0) {
            /* hw reset value */
            soc_reg_field_set(unit, reg, &rval, MMU_CONGESTION_EXPERIENCEf, 0xAAA);
            BCM_IF_ERROR_RETURN(soc_reg32_set(unit, reg, REG_PORT_ANY, i, rval));
            _bcm_hx5_wred_resolution_tbl[i]++;
            *index = i;
            return BCM_E_NONE;
        }
    }

    return BCM_E_RESOURCE;
}

/*
 * Function:
 *     bcm_hx5_cosq_wred_resolution_entry_destroy
 * Purpose:
 *     Callback an entry and set its drop rules to WRED drop.
 * Parameters:
 *     unit                - (IN) unit number
 *     index               - (IN) entry index
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_wred_resolution_entry_destroy(int unit, int index)
{
    uint32 rval = 0;
    soc_reg_t reg = WRED_CONG_NOTIFICATION_RESOLUTION_TABLEr;

    if ((index < 0) || (index >= _BCM_HX5_NUM_WRED_RESOLUTION_TABLE)) {
        return BCM_E_PARAM;
    }

    if (_bcm_hx5_wred_resolution_tbl[index] == 0) {
        return BCM_E_NOT_FOUND;
    }

    /* hw reset value */
    soc_reg_field_set(unit, reg, &rval, MMU_CONGESTION_EXPERIENCEf, 0xAAA);
    BCM_IF_ERROR_RETURN(soc_reg32_set(unit, reg, REG_PORT_ANY, index, rval));
    _bcm_hx5_wred_resolution_tbl[index] = 0;

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_wred_resolution_set
 * Purpose:
 *     Set one rule of a resolution table entry
 * Parameters:
 *     unit                - (IN) unit number
 *     index               - (IN) entry index
 *     rule                - (IN) drop rule
 * Returns:
 *     BCM_E_XXX
 * Notes:
 *     One entry has 12 bits, equals to 6 rules
 */
int
bcm_hx5_cosq_wred_resolution_set(int unit, int index, bcm_cosq_discard_rule_t *rule)
{
    uint32 offset, sp, qmin;
    uint32 rval, fval, drop;
    soc_reg_t reg = WRED_CONG_NOTIFICATION_RESOLUTION_TABLEr;

    if ((index < 0) || (index >= _BCM_HX5_NUM_WRED_RESOLUTION_TABLE)) {
        return BCM_E_PARAM;
    }

    if (_bcm_hx5_wred_resolution_tbl[index] == 0) {
        return BCM_E_NOT_FOUND;
    }

    switch (rule->egress_pool_congestion_state) {
        case BCM_COSQ_DISCARD_CONGESTION_LOW:
            sp = 0;
            break;
        case BCM_COSQ_DISCARD_CONGESTION_MEDIUM:
            sp = 1;
            break;
        case BCM_COSQ_DISCARD_CONGESTION_HIGH:
            sp = 2;
            break;
        default:
            return BCM_E_PARAM;
    }

    switch (rule->queue_min_congestion_state) {
        case BCM_COSQ_DISCARD_CONGESTION_LOW:
            qmin = 0;
            break;
        case BCM_COSQ_DISCARD_CONGESTION_HIGH:
            qmin = 1;
            break;
        default:
            return BCM_E_PARAM;
    }

    switch (rule->action) {
        case BCM_COSQ_DISCARD_ACTION_WRED_DROP:
            drop = 0x2;
            break;
        case BCM_COSQ_DISCARD_ACTION_FORCE_DROP:
            drop = 0x3;
            break;
        case BCM_COSQ_DISCARD_ACTION_FORCE_NO_DROP:
            drop = 0x0;
            break;
        default:
            return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN(soc_reg32_get(unit, reg, REG_PORT_ANY, index, &rval));
    fval = soc_reg_field_get(unit, reg, rval, MMU_CONGESTION_EXPERIENCEf);

    offset = (sp * 2 + qmin) * 2;       /* 2 bits per rule */
    fval = (fval & (~(0x3 << offset))) | (drop << offset);

    soc_reg_field_set(unit, reg, &rval, MMU_CONGESTION_EXPERIENCEf, fval);
    BCM_IF_ERROR_RETURN(soc_reg32_set(unit, reg, REG_PORT_ANY, index, rval));

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_wred_resolution_get
 * Purpose:
 *     Get all rules of a resolution table entry
 * Parameters:
 *     unit                - (IN) unit number
 *     index               - (IN) entry index
 *     max                 - (IN) rule array size
 *     rule                - (OUT) rule array
 *     count               - (OUT) actual rules count
 * Returns:
 *     BCM_E_XXX
 * Notes:
 *     One entry has 12 bits, equals to 6 rules
 */
int
bcm_hx5_cosq_wred_resolution_get(int unit, int index, int max,
                                 bcm_cosq_discard_rule_t *rule, int *count)
{
    uint32 offset, sp, qmin, i = 0;
    uint32 rval, fval, action;
    soc_reg_t reg = WRED_CONG_NOTIFICATION_RESOLUTION_TABLEr;
    uint32 sp_map[3] = {
        BCM_COSQ_DISCARD_CONGESTION_LOW,
        BCM_COSQ_DISCARD_CONGESTION_MEDIUM,
        BCM_COSQ_DISCARD_CONGESTION_HIGH,
    };
    uint32 qmin_map[2] = {
        BCM_COSQ_DISCARD_CONGESTION_LOW,
        BCM_COSQ_DISCARD_CONGESTION_HIGH,
    };
    uint32 action_map[4] = {
        BCM_COSQ_DISCARD_ACTION_FORCE_NO_DROP,
        -1,
        BCM_COSQ_DISCARD_ACTION_WRED_DROP,
        BCM_COSQ_DISCARD_ACTION_FORCE_DROP,
    };

    if ((!count) ||
        (index < 0) || (index >= _BCM_HX5_NUM_WRED_RESOLUTION_TABLE)) {
        return BCM_E_PARAM;
    }

    *count = 3 * 2;

    if (!rule) {
        return BCM_E_NONE;
    }

    BCM_IF_ERROR_RETURN(soc_reg32_get(unit, reg, REG_PORT_ANY, index, &rval));
    fval = soc_reg_field_get(unit, reg, rval, MMU_CONGESTION_EXPERIENCEf);

    for (sp = 0; sp < 3; sp ++) {
        for (qmin = 0; qmin < 2; qmin++) {
            offset = (sp * 2 + qmin) * 2;       /* 2 bits per rule */
            action = (fval >> offset) & 0x3;
            if (i < max) {
                rule[i].egress_pool_congestion_state = sp_map[sp];
                rule[i].queue_min_congestion_state = qmin_map[qmin];
                rule[i].action = action_map[action];
                i++;
            }
        }
    }

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_wred_set(int unit, bcm_port_t port, bcm_cos_queue_t cosq,
                      uint32 flags, uint32 min_thresh, uint32 max_thresh,
                      int drop_probability, int gain, int ignore_enable_flags,
                      uint32 lflags,  int refresh_time, uint32 resolution_id,
                      uint32 use_queue_group)
{
    /* Local Variables */
    soc_mem_t wred_config_mem = INVALIDm;
    bcm_port_t local_port = -1;
    int index, i, start_index, end_index, count = 0;
    int end_offset, need_profile = 0, pipe = 0;
    uint32 profile_index, old_profile_index;
    uint32 wred_flags = 0;
    void *entries[9];
    soc_mem_t mems[9];
    static soc_mem_t wred_mems[9] = {
        MMU_WRED_DROP_CURVE_PROFILE_0m, MMU_WRED_DROP_CURVE_PROFILE_1m,
        MMU_WRED_DROP_CURVE_PROFILE_2m, MMU_WRED_DROP_CURVE_PROFILE_3m,
        MMU_WRED_DROP_CURVE_PROFILE_4m, MMU_WRED_DROP_CURVE_PROFILE_5m,
        MMU_WRED_DROP_CURVE_PROFILE_6m, MMU_WRED_DROP_CURVE_PROFILE_7m,
        MMU_WRED_DROP_CURVE_PROFILE_8m
    };
    mmu_wred_drop_curve_profile_0_entry_t entry_tcp_green;
    mmu_wred_drop_curve_profile_1_entry_t entry_tcp_yellow;
    mmu_wred_drop_curve_profile_2_entry_t entry_tcp_red;
    mmu_wred_drop_curve_profile_3_entry_t entry_nontcp_green;
    mmu_wred_drop_curve_profile_4_entry_t entry_nontcp_yellow;
    mmu_wred_drop_curve_profile_5_entry_t entry_nontcp_red;
    mmu_wred_drop_curve_profile_6_entry_t entry_ecn_green;
    mmu_wred_drop_curve_profile_7_entry_t entry_ecn_yellow;
    mmu_wred_drop_curve_profile_8_entry_t entry_ecn_red;
    mmu_wred_config_entry_t entry;
    int rate = 0;
    int from_pipe, to_pipe;
    int time_id,time,old_time,current_time_sel;
    int rv = SOC_E_NONE, exists = 0;

    wred_flags = flags | lflags;
    end_offset = 0;

    /* Check Flags for WRED res level - Device-SP/Port-SP/Queues */
    if ((wred_flags & BCM_COSQ_DISCARD_DEVICE) && (port == BCM_GPORT_INVALID)) {
        /* (Port == -1) For all Global SPs */
        index = _HX5_WRED_PER_PIPE_GLOBAL_SP_BASE;
        count = _HX5_MMU_NUM_POOL;
        /*For all pipe*/
        from_pipe = 0;
        to_pipe = NUM_PIPE(unit) - 1;

    } else {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));
        from_pipe = to_pipe = pipe;

        if (wred_flags & BCM_COSQ_DISCARD_DEVICE) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, port, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_WRED_DEVICE,
                                            NULL, &index, &count));
            /* (cosq == -1) For all Global SPs */
        } else if (wred_flags & BCM_COSQ_DISCARD_PORT) {
            /* Port SP - Given or all SPs of the port */
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, port, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_WRED_PORT,
                                            NULL, &index, &count));
            /* (cosq == -1) For all SPs of the given port */
        } else {
            /* Per Queue WRED settings */
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, port, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_WRED_QUEUE,
                                            NULL, &index, &count));
            /* (cosq == -1) For all Queues of the given port */
        }
    }


    end_offset = (count > 0) ? (count - 1) : 0;

    if (index < 0) {
        return BCM_E_PARAM;
    }

    if (refresh_time < 1) {
        return BCM_E_PARAM;
    }

    start_index = index;
    end_index = start_index + end_offset;

    rate = _bcm_hx5_percent_to_drop_prob(drop_probability);

    for (pipe = from_pipe; pipe <= to_pipe; pipe++ ) {
        /* Config MMU_WRED_CONFIGm for the respective resource */
        wred_config_mem = MMU_WRED_CONFIGm;
        wred_config_mem = SOC_MEM_UNIQUE_ACC(unit, wred_config_mem)[pipe];
        if (wred_config_mem == INVALIDm) {
            return BCM_E_PARAM;
        }

        for (i=0; i < 9; i++) {
            mems[i] = INVALIDm;
        }

        if (wred_flags & (BCM_COSQ_DISCARD_COLOR_ALL |
                          BCM_COSQ_DISCARD_TCP |
                          BCM_COSQ_DISCARD_NONTCP |
                          BCM_COSQ_DISCARD_ECT_MARKED |
                          BCM_COSQ_DISCARD_RESPONSIVE_DROP |
                          BCM_COSQ_DISCARD_NON_RESPONSIVE_DROP)) {
            need_profile = 1;

            if (!(flags & (BCM_COSQ_DISCARD_COLOR_GREEN |
                           BCM_COSQ_DISCARD_COLOR_YELLOW |
                           BCM_COSQ_DISCARD_COLOR_RED))) {
                flags |= BCM_COSQ_DISCARD_COLOR_ALL;
            }

            if (!(wred_flags & (BCM_COSQ_DISCARD_NONTCP |
                                BCM_COSQ_DISCARD_NON_RESPONSIVE_DROP |
                                BCM_COSQ_DISCARD_ECT_MARKED)) ||
                 ((wred_flags & BCM_COSQ_DISCARD_TCP) ||
                 (wred_flags & BCM_COSQ_DISCARD_RESPONSIVE_DROP))) {
                if (flags & BCM_COSQ_DISCARD_COLOR_GREEN) {
                    mems[0] = wred_mems[0];
                }
                if (flags & BCM_COSQ_DISCARD_COLOR_YELLOW) {
                    mems[1] = wred_mems[1];
                }
                if (flags & BCM_COSQ_DISCARD_COLOR_RED) {
                    mems[2] = wred_mems[2];
                }
            }
            if ((wred_flags & BCM_COSQ_DISCARD_NONTCP) ||
                (wred_flags & BCM_COSQ_DISCARD_NON_RESPONSIVE_DROP)){
                if (flags & BCM_COSQ_DISCARD_COLOR_GREEN) {
                    mems[3] = wred_mems[3];
                }
                if (flags & BCM_COSQ_DISCARD_COLOR_YELLOW) {
                    mems[4] = wred_mems[4];
                }
                if (flags & BCM_COSQ_DISCARD_COLOR_RED) {
                    mems[5] = wred_mems[5];
                }
            }
            if (wred_flags & BCM_COSQ_DISCARD_ECT_MARKED) {
                if (flags & BCM_COSQ_DISCARD_COLOR_GREEN) {
                    mems[6] = wred_mems[6];
                }
                if (flags & BCM_COSQ_DISCARD_COLOR_YELLOW) {
                    mems[7] = wred_mems[7];
                }
                if (flags & BCM_COSQ_DISCARD_COLOR_RED) {
                    mems[8] = wred_mems[8];
                }
            }
        }

        entries[0] = &entry_tcp_green;
        entries[1] = &entry_tcp_yellow;
        entries[2] = &entry_tcp_red;
        entries[3] = &entry_nontcp_green;
        entries[4] = &entry_nontcp_yellow;
        entries[5] = &entry_nontcp_red;
        entries[6] = &entry_ecn_green;
        entries[7] = &entry_ecn_yellow;
        entries[8] = &entry_ecn_red;

        for (index = start_index; index <= end_index; index++) {
            old_profile_index = 0xffffffff;
            BCM_IF_ERROR_RETURN
                (soc_mem_read(unit, wred_config_mem, MEM_BLOCK_ALL, index, &entry));

            if (need_profile) {
                old_profile_index = soc_mem_field32_get(unit, wred_config_mem,
                                                        &entry, PROFILE_INDEXf);

                BCM_IF_ERROR_RETURN
                    (soc_profile_mem_get(unit, _bcm_hx5_wred_profile[unit],
                                         old_profile_index, 1, entries));

                for (i = 0; i < HX5_WRED_PROFILE_NUM; i++) {
                    if (mems[i] == INVALIDm) {
                        continue;
                    }
                    soc_mem_field32_set(unit, wred_mems[i], entries[i],
                                        MIN_THDf, min_thresh);
                    soc_mem_field32_set(unit, wred_mems[i], entries[i],
                                        MAX_THDf, max_thresh);
                    soc_mem_field32_set(unit, wred_mems[i], entries[i],
                                        MAX_DROP_RATEf, rate);
                }
                BCM_IF_ERROR_RETURN
                    (soc_profile_mem_add(unit, _bcm_hx5_wred_profile[unit],
                                         entries, 1, &profile_index));
                soc_mem_field32_set(unit, wred_config_mem, &entry, PROFILE_INDEXf, profile_index);
            }
                soc_mem_field32_set(unit, wred_config_mem, &entry, WEIGHTf, gain);

            /* Some APIs only modify profiles */
            if (!ignore_enable_flags) {
                soc_mem_field32_set(unit, wred_config_mem, &entry, CAP_AVERAGEf,
                                    flags & BCM_COSQ_DISCARD_CAP_AVERAGE ? 1 : 0);
                soc_mem_field32_set(unit, wred_config_mem, &entry, WRED_ENf,
                                    flags & BCM_COSQ_DISCARD_ENABLE ? 1 : 0);
                soc_mem_field32_set(unit, wred_config_mem, &entry, ECN_MARKING_ENf,
                                    flags & BCM_COSQ_DISCARD_MARK_CONGESTION ?  1 : 0);
            }

            current_time_sel = soc_mem_field32_get(unit, wred_config_mem,
                                                   &entry, TIME_DOMAIN_SELf);
            time = refresh_time - 1;
            exists = 0;
            /* If the time value exist, update reference count only */
            for (time_id = 0; time_id < _BCM_HX5_NUM_TIME_DOMAIN; time_id++) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_time_domain_get(unit, time_id, &old_time));
                if (time == old_time) {
                    /* Only set exist flag if this entry reference count already update,
                                  otherwise update reference count */
                    if(time_id != current_time_sel){
                        soc_mem_field32_set(unit, wred_config_mem, &entry,
                                            TIME_DOMAIN_SELf, time_id);
                        hx5_time_domain_info[unit][time_id].ref_count++;
                        hx5_time_domain_info[unit][current_time_sel].ref_count--;
                    }
                    exists = 1;
                    break;
                }
            }

            if(!exists){
                rv = _bcm_hx5_cosq_time_domain_set(unit, time, &time_id);
                if(rv == SOC_E_NONE){
                    soc_mem_field32_set(unit, wred_config_mem, &entry,
                                        TIME_DOMAIN_SELf, time_id);
                    hx5_time_domain_info[unit][current_time_sel].ref_count--;
                } else {
                    return rv;
                }
            }

            soc_mem_field32_set(unit, wred_config_mem, &entry, QG_ENf,
                                use_queue_group ? 1 : 0);
            if (flags & BCM_COSQ_DISCARD_MARK_CONGESTION) {
                soc_mem_field32_set(unit, wred_config_mem, &entry,
                    WRED_CONG_NOTIFICATION_RESOLUTION_TABLE_MARKING_INDEXf,
                    resolution_id);
            } else {
                soc_mem_field32_set(unit, wred_config_mem, &entry,
                    WRED_CONG_NOTIFICATION_RESOLUTION_TABLE_DROPPING_INDEXf,
                    resolution_id);
            }


            BCM_IF_ERROR_RETURN(
                    soc_mem_write(unit, wred_config_mem, MEM_BLOCK_ALL, index, &entry));

            if (old_profile_index != 0xffffffff) {
                SOC_IF_ERROR_RETURN
                    (soc_profile_mem_delete(unit, _bcm_hx5_wred_profile[unit],
                                            old_profile_index));
            }

        }

    }

    /* Check Flags for WRED profile based on Color */
    return BCM_E_NONE;
}

/*
 * Function:
 *     _bcm_hx5_cosq_wred_get
 * Purpose:
 *     Configure unicast queue WRED setting
 * Parameters:
 *     unit                - (IN) unit number
 *     port                - (IN) port number or GPORT identifier
 *     cosq                - (IN) COS queue number
 *     flags               - (IN/OUT) BCM_COSQ_DISCARD_XXX
 *     min_thresh          - (OUT) Min Threshold
 *     max_thresh          - (OUT) Max Threshold
 *     drop_probablity     - (OUT) Probabilistic drop rate
 *     gain                - (OUT)
 *     lflags              - (IN) Config flags
 *     refresh_time        - (OUT) Time Domain
 *     resolution_id       - (OUT) Resolution index
 *     use_queue_group     - (OUT) Queue group status is used
 * Returns:
 *     BCM_E_XXX
 * Notes:
 *     If port is any form of local port, cosq is the hardware queue index.
 */
STATIC int
_bcm_hx5_cosq_wred_get(int unit, bcm_port_t port, bcm_cos_queue_t cosq,
                      uint32 *flags, uint32 *min_thresh, uint32 *max_thresh,
                      int *drop_probability, int *gain, uint32 lflags,
                      int *refresh_time, uint32 *resolution_id,
                      uint32 *use_queue_group)
{
    soc_mem_t wred_config_mem = INVALIDm, mem = INVALIDm;
    bcm_port_t local_port = -1;
    mmu_wred_drop_curve_profile_0_entry_t entry_tcp_green;
    mmu_wred_drop_curve_profile_1_entry_t entry_tcp_yellow;
    mmu_wred_drop_curve_profile_2_entry_t entry_tcp_red;
    mmu_wred_drop_curve_profile_3_entry_t entry_nontcp_green;
    mmu_wred_drop_curve_profile_4_entry_t entry_nontcp_yellow;
    mmu_wred_drop_curve_profile_5_entry_t entry_nontcp_red;
    mmu_wred_drop_curve_profile_6_entry_t entry_ecn_green;
    mmu_wred_drop_curve_profile_7_entry_t entry_ecn_yellow;
    mmu_wred_drop_curve_profile_8_entry_t entry_ecn_red;
    void *entries[9];
    void *entry_p;
    int index, profile_index;
    mmu_wred_config_entry_t entry;
    uint32 wred_flags = 0;
    int rate = 0, pipe = 0;
    int time_id, time;

    if (flags) {
        wred_flags = *flags | lflags;
    } else {
        wred_flags = lflags;
    }

    if ((wred_flags & BCM_COSQ_DISCARD_DEVICE) && (port == BCM_GPORT_INVALID)) {
        /* (Port == -1) For all Global SPs */
        index = _HX5_WRED_PER_PIPE_GLOBAL_SP_BASE;
        pipe = 0;

    } else {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));

        /* Check Flags for WRED res level - Device-SP/Port-SP/Queues */
        if(wred_flags & BCM_COSQ_DISCARD_DEVICE) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, port, cosq,
                                        _BCM_HX5_COSQ_INDEX_STYLE_WRED_DEVICE,
                                        NULL, &index, NULL));
        } else if (wred_flags & BCM_COSQ_DISCARD_PORT) {
            /* Port SP - Given or all SPs of the port */
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, port, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_WRED_PORT,
                                            NULL, &index, NULL));
        } else {
            /* Per Queue WRED settings */
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, port, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_WRED_QUEUE,
                                            NULL, &index, NULL));
        }
    }

    if ((index < 0) || (pipe == -1)) {
        return BCM_E_PARAM;
    }

    wred_config_mem = MMU_WRED_CONFIGm;
    wred_config_mem = SOC_MEM_UNIQUE_ACC(unit, wred_config_mem)[pipe];
    if (wred_config_mem == INVALIDm) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (soc_mem_read(unit, wred_config_mem, MEM_BLOCK_ALL, index, &entry));
    profile_index = soc_mem_field32_get(unit, wred_config_mem,
                                        &entry, PROFILE_INDEXf);

    if (!(wred_flags & (BCM_COSQ_DISCARD_NONTCP |
                        BCM_COSQ_DISCARD_NON_RESPONSIVE_DROP |
                        BCM_COSQ_DISCARD_ECT_MARKED))) {
        /* By default we will assume
           BCM_COSQ_DISCARD_TCP */
        if (wred_flags & BCM_COSQ_DISCARD_COLOR_YELLOW) {
            mem = MMU_WRED_DROP_CURVE_PROFILE_1m;
            entry_p = &entry_tcp_yellow;
        } else if (wred_flags & BCM_COSQ_DISCARD_COLOR_RED) {
            mem = MMU_WRED_DROP_CURVE_PROFILE_2m;
            entry_p = &entry_tcp_red;
        } else {
            /* By default we will assume
               BCM_COSQ_DISCARD_COLOR_GREEN */
            mem = MMU_WRED_DROP_CURVE_PROFILE_0m;
            entry_p = &entry_tcp_green;
        }
    } else if ((wred_flags & BCM_COSQ_DISCARD_NONTCP) ||
               (wred_flags & BCM_COSQ_DISCARD_NON_RESPONSIVE_DROP)) {
        if (wred_flags & BCM_COSQ_DISCARD_COLOR_YELLOW) {
            mem = MMU_WRED_DROP_CURVE_PROFILE_4m;
            entry_p = &entry_nontcp_yellow;
        } else if (wred_flags & BCM_COSQ_DISCARD_COLOR_RED) {
            mem = MMU_WRED_DROP_CURVE_PROFILE_5m;
            entry_p = &entry_nontcp_red;
        } else {
            /* By default we will assume
               BCM_COSQ_DISCARD_COLOR_GREEN */
            mem = MMU_WRED_DROP_CURVE_PROFILE_3m;
            entry_p = &entry_nontcp_green;
        }
    } else {
        if (wred_flags & BCM_COSQ_DISCARD_COLOR_YELLOW) {
            mem = MMU_WRED_DROP_CURVE_PROFILE_7m;
            entry_p = &entry_ecn_yellow;
        } else if (wred_flags & BCM_COSQ_DISCARD_COLOR_RED) {
            mem = MMU_WRED_DROP_CURVE_PROFILE_8m;
            entry_p = &entry_ecn_red;
        } else {
            /* By default we will assume
               BCM_COSQ_DISCARD_COLOR_GREEN */
            mem = MMU_WRED_DROP_CURVE_PROFILE_6m;
            entry_p = &entry_ecn_green;
        }
    }

    entries[0] = &entry_tcp_green;
    entries[1] = &entry_tcp_yellow;
    entries[2] = &entry_tcp_red;
    entries[3] = &entry_nontcp_green;
    entries[4] = &entry_nontcp_yellow;
    entries[5] = &entry_nontcp_red;
    entries[6] = &entry_ecn_green;
    entries[7] = &entry_ecn_yellow;
    entries[8] = &entry_ecn_red;

    BCM_IF_ERROR_RETURN
        (soc_profile_mem_get(unit, _bcm_hx5_wred_profile[unit],
                             profile_index, 1, entries));
    if (min_thresh != NULL) {
        *min_thresh = soc_mem_field32_get(unit, mem, entry_p, MIN_THDf);
    }
    if (max_thresh != NULL) {
        *max_thresh = soc_mem_field32_get(unit, mem, entry_p, MAX_THDf);
    }
    if (drop_probability != NULL) {
        rate = soc_mem_field32_get(unit, mem, entry_p, MAX_DROP_RATEf);
        *drop_probability = _bcm_hx5_drop_prob_to_percent(rate);
    }
    if (gain) {
        *gain = soc_mem_field32_get(unit, wred_config_mem, &entry, WEIGHTf);
    }

    if (refresh_time) {
            time_id = soc_mem_field32_get(unit, wred_config_mem, &entry,
                                          TIME_DOMAIN_SELf);
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_time_domain_get(unit,time_id,&time));
            *refresh_time = time + 1;
    }

    /* Get flags */
    if (flags) {
        if (soc_mem_field32_get(unit, wred_config_mem, &entry, CAP_AVERAGEf)) {
            *flags |= BCM_COSQ_DISCARD_CAP_AVERAGE;
        }
        if (soc_mem_field32_get(unit, wred_config_mem, &entry, WRED_ENf)) {
            *flags |= BCM_COSQ_DISCARD_ENABLE;
        }
        if (soc_mem_field32_get(unit, wred_config_mem, &entry, ECN_MARKING_ENf)) {
            *flags |= BCM_COSQ_DISCARD_MARK_CONGESTION;
        }
    }

    /* Get resolution table index */
    if (resolution_id) {
        if (soc_mem_field32_get(unit, wred_config_mem, &entry, ECN_MARKING_ENf)) {
            *resolution_id = soc_mem_field32_get(unit, wred_config_mem, &entry,
                WRED_CONG_NOTIFICATION_RESOLUTION_TABLE_MARKING_INDEXf);
        } else {
            *resolution_id = soc_mem_field32_get(unit, wred_config_mem, &entry,
                WRED_CONG_NOTIFICATION_RESOLUTION_TABLE_DROPPING_INDEXf);
        }
    }

    /* Get use_queue_group */
    if (use_queue_group) {
        *use_queue_group =
            soc_mem_field32_get(unit, wred_config_mem, &entry, QG_ENf);
    }

    return BCM_E_NONE;
}


int
bcm_hx5_cosq_discard_set(int unit, uint32 flags)
{
    bcm_port_t port;

    if (_bcm_hx5_cosq_port_info[unit] == NULL) {
        return BCM_E_INIT;
    }

    if (flags & ~(BCM_COSQ_DISCARD_DEVICE |
                  BCM_COSQ_DISCARD_NONTCP |
                  BCM_COSQ_DISCARD_COLOR_ALL |
                  BCM_COSQ_DISCARD_PORT |
                  BCM_COSQ_DISCARD_TCP |
                  BCM_COSQ_DISCARD_COLOR_GREEN |
                  BCM_COSQ_DISCARD_COLOR_YELLOW |
                  BCM_COSQ_DISCARD_COLOR_RED |
                  BCM_COSQ_DISCARD_CAP_AVERAGE |
                  BCM_COSQ_DISCARD_ENABLE |
                  BCM_COSQ_DISCARD_MARK_CONGESTION)) {
        return BCM_E_PARAM;
    }

    flags &= ~(BCM_COSQ_DISCARD_NONTCP | BCM_COSQ_DISCARD_COLOR_ALL);

    PBMP_PORT_ITER(unit, port) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_wred_set(unit, port, 0, flags, 0, 0, 0, 0,
                                   FALSE, BCM_COSQ_DISCARD_PORT, 0x1, 0, 0));
    }

    return BCM_E_NONE;
}

int
bcm_hx5_cosq_discard_get(int unit, uint32 *flags)
{
    bcm_port_t port;

    PBMP_PORT_ITER(unit, port) {
        *flags = 0;
        /* use setting from hardware cosq index 0 of the first port */
        return _bcm_hx5_cosq_wred_get(unit, port, 0, flags, NULL, NULL, NULL,
                                     NULL, BCM_COSQ_DISCARD_PORT, NULL, NULL,
                                     NULL);
    }

    return BCM_E_NOT_FOUND;
}

/*
 * Function:
 *     bcm_hx5_cosq_discard_port_set
 * Purpose:
 *     Configure port WRED setting
 * Parameters:
 *     unit          - (IN) unit number
 *     port          - (IN) port number or GPORT identifier
 *     cosq          - (IN) COS queue number
 *     color         - (IN)
 *     drop_start    - (IN)
 *     drop_slot     - (IN)
 *     average_time  - (IN)
 * Returns:
 *     BCM_E_XXX
 * Notes:
 *     If port is any form of local port, cosq is the hardware queue index.
 *     Same as TD2 except for Reg changes.
 */
int
bcm_hx5_cosq_discard_port_set(int unit, bcm_port_t port, bcm_cos_queue_t cosq,
                             uint32 color, int drop_start, int drop_slope,
                             int average_time)
{
    bcm_port_t local_port;
    bcm_pbmp_t pbmp;
    int gain;
    uint32 min_thresh, max_thresh, shared_limit;
    uint32 rval, bits, flags = 0;
    int numq, i;

    if (drop_start < 0 || drop_start > 100 ||
        drop_slope < 0 || drop_slope > 90) {
        return BCM_E_PARAM;
    }

    /*
     * average queue size is reculated every 8us, the formula is
     * avg_qsize(t + 1) =
     *     avg_qsize(t) + (cur_qsize - avg_qsize(t)) / (2 ** gain)
     * gain = log2(average_time / 8)
     */
    bits = (average_time / 8) & 0xffff;
    if (bits != 0) {
        bits |= bits >> 1;
        bits |= bits >> 2;
        bits |= bits >> 4;
        bits |= bits >> 8;
        gain = _shr_popcount(bits) - 1;
    } else {
        gain = 0;
    }

    /*
     * per-port cell limit may be disabled.
     * per-port per-cos cell limit may be set to use dynamic method.
     * therefore drop_start percentage is based on per-device total shared
     * cells.
     */
    BCM_IF_ERROR_RETURN(READ_MMU_THDM_DB_POOL_SHARED_LIMITr(unit, 0, &rval));
    shared_limit = soc_reg_field_get(unit, MMU_THDM_DB_POOL_SHARED_LIMITr,
                                     rval, SHARED_LIMITf);
    min_thresh = ((drop_start * shared_limit) + (100 - 1)) / 100;

    /* Calculate the max threshold. For a given slope (angle in
     * degrees), determine how many packets are in the range from
     * 0% drop probability to 100% drop probability. Add that
     * number to the min_treshold to the the max_threshold.
     */
    max_thresh = min_thresh + _bcm_hx5_angle_to_cells(drop_slope);
    if (max_thresh > HX5_WRED_CELL_FIELD_MAX) {
        max_thresh = HX5_WRED_CELL_FIELD_MAX;
    }

    if (BCM_GPORT_IS_SET(port)) {
        numq = 1;
        for (i = 0; i < numq; i++) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_wred_set(unit, port, cosq + i, color,
                                        min_thresh, max_thresh, 100, gain,
                                        TRUE, flags, 0x1, 0, 0));
        }
    } else {
        if (port == -1) {
            BCM_PBMP_ASSIGN(pbmp, PBMP_PORT_ALL(unit));
        } else if (!SOC_PORT_VALID(unit, port)) {
            return BCM_E_PORT;
        } else {
            BCM_PBMP_PORT_SET(pbmp, port);
        }

        BCM_PBMP_ITER(pbmp, local_port) {
            numq = 1;
            for (i = 0; i < numq; i++) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_wred_set(unit, local_port, cosq + i,
                                            color, min_thresh, max_thresh, 100,
                                            gain, TRUE, 0, 0x1, 0, 0));
            }
        }
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_discard_port_get
 * Purpose:
 *     Get port WRED setting
 * Parameters:
 *     unit          - (IN) unit number
 *     port          - (IN) port number or GPORT identifier
 *     cosq          - (IN) COS queue number
 *     color         - (OUT)
 *     drop_start    - (OUT)
 *     drop_slot     - (OUT)
 *     average_time  - (OUT)
 * Returns:
 *     BCM_E_XXX
 * Notes:
 *     If port is any form of local port, cosq is the hardware queue index.
 *     Same as TD2 except for Reg changes.
 */
int
bcm_hx5_cosq_discard_port_get(int unit, bcm_port_t port, bcm_cos_queue_t cosq,
                             uint32 color, int *drop_start, int *drop_slope,
                             int *average_time)
{
    bcm_port_t local_port;
    bcm_pbmp_t pbmp;
    int gain, drop_prob;
    uint32 min_thresh, max_thresh, shared_limit;
    uint32 rval;

    if (drop_start == NULL || drop_slope == NULL || average_time == NULL) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_SET(port)) {
        local_port = port;
    } else {
        if (port == -1) {
            BCM_PBMP_ASSIGN(pbmp, PBMP_PORT_ALL(unit));
        } else if (!SOC_PORT_VALID(unit, port)) {
            return BCM_E_PORT;
        } else {
            BCM_PBMP_PORT_SET(pbmp, port);
        }
        BCM_PBMP_ITER(pbmp, local_port) {
            break;
        }
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_wred_get(unit, local_port, cosq == -1 ? 0 : cosq,
                                &color, &min_thresh, &max_thresh, &drop_prob,
                                &gain, 0, NULL, NULL, NULL));

    /*
     * average queue size is reculated every 8us, the formula is
     * avg_qsize(t + 1) =
     *     avg_qsize(t) + (cur_qsize - avg_qsize(t)) / (2 ** gain)
     */
    *average_time = (1 << gain) * 8;

    BCM_IF_ERROR_RETURN(READ_MMU_THDM_DB_POOL_SHARED_LIMITr(unit, 0, &rval));
    shared_limit = soc_reg_field_get(unit, MMU_THDM_DB_POOL_SHARED_LIMITr,
                                     rval, SHARED_LIMITf);
    if (min_thresh > shared_limit) {
        min_thresh = shared_limit;
    }

    if (max_thresh > shared_limit) {
        max_thresh = shared_limit;
    }

    *drop_start = min_thresh * 100 / shared_limit;

    /* Calculate the slope using the min and max threshold.
     * The angle is calculated knowing drop probability at min
     * threshold is 0% and drop probability at max threshold is 100%.
     */
    *drop_slope = _bcm_hx5_cells_to_angle(max_thresh - min_thresh);

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_gport_discard_set
 * Purpose:
 *     Configure port WRED setting
 * Parameters:
 *     unit    - (IN) unit number
 *     port    - (IN) GPORT identifier
 *     cosq    - (IN) COS queue to configure, -1 for all COS queues
 *     discard - (IN) discard settings
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_gport_discard_set(int unit, bcm_gport_t gport,
                               bcm_cos_queue_t cosq,
                               bcm_cosq_gport_discard_t *discard)
{
    int numq, i;
    uint32 min_thresh, max_thresh, flags = 0;
    int cell_size, cell_field_max;
    bcm_port_t local_port = -1;

    /* the reasonable range of refresh_time  is from 1 to 64 */
    if (discard == NULL ||
        discard->gain < 0 || discard->gain > 15 ||
        discard->drop_probability < 0 || discard->drop_probability > 100 ||
        discard->refresh_time <= 0 || discard->refresh_time > 64 || 
        discard->profile_id > 3) {
        return BCM_E_PARAM;
    }

    if (discard == NULL ||
        discard->gain < 0 || discard->gain > 15 ||
        discard->drop_probability < 0 || discard->drop_probability > 100) {
        return BCM_E_PARAM;
    }

    cell_size = _HX5_MMU_BYTES_PER_CELL;
    cell_field_max = HX5_WRED_CELL_FIELD_MAX;

    min_thresh = discard->min_thresh;
    max_thresh = discard->max_thresh;
    if (discard->flags & BCM_COSQ_DISCARD_BYTES) {
        /* Convert bytes to cells */
        min_thresh += (cell_size - 1);
        min_thresh /= cell_size;

        max_thresh += (cell_size - 1);
        max_thresh /= cell_size;

        if ((min_thresh > cell_field_max) ||
            (max_thresh > cell_field_max)) {
            return BCM_E_PARAM;
        }
    } else if (discard->flags & BCM_COSQ_DISCARD_PACKETS) {
        /* Packet mode not supported */
        return BCM_E_PARAM;
    } else {
        /* Lower layer function will update thresh when these flags are
         * configured, this interface only allow such opration when
         * BCM_COSQ_DISCARD_BYTES is also configured.
         */
        if (discard->flags & (BCM_COSQ_DISCARD_COLOR_ALL |
            BCM_COSQ_DISCARD_TCP |
            BCM_COSQ_DISCARD_NONTCP |
            BCM_COSQ_DISCARD_ECT_MARKED |
            BCM_COSQ_DISCARD_RESPONSIVE_DROP |
            BCM_COSQ_DISCARD_NON_RESPONSIVE_DROP)) {
            return BCM_E_PARAM;
        }
    }

    if (gport != BCM_GPORT_INVALID) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
        if (IS_CPU_PORT(unit,local_port) || IS_LB_PORT(unit,local_port)) {
            return BCM_E_PORT;
        }
        if ((cosq < -1) || (cosq >= SOC_PORT_NUM_COSQ(unit, local_port))) {
            return BCM_E_PARAM;
        }
    }

    numq = 1;

    for (i = 0; i < numq; i++) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_wred_set(unit, gport, cosq + i, discard->flags,
                                   min_thresh, max_thresh,
                                   discard->drop_probability, discard->gain,
                                   FALSE, flags, discard->refresh_time,
                                   discard->profile_id, discard->use_queue_group));
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_gport_discard_get
 * Purpose:
 *     Get port WRED setting
 * Parameters:
 *     unit    - (IN) unit number
 *     port    - (IN) GPORT identifier
 *     cosq    - (IN) COS queue to get, -1 for any queue
 *     discard - (OUT) discard settings
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_gport_discard_get(int unit, bcm_gport_t gport,
                              bcm_cos_queue_t cosq,
                              bcm_cosq_gport_discard_t *discard)
{
    uint32 min_thresh, max_thresh;
    bcm_port_t local_port = -1;

    if (discard == NULL) {
        return BCM_E_PARAM;
    }

    if (gport != BCM_GPORT_INVALID) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
        if (IS_CPU_PORT(unit,local_port) || IS_LB_PORT(unit,local_port)) {
            return BCM_E_PORT;
        }
        if ((cosq < -1) || (cosq >= SOC_PORT_NUM_COSQ(unit, local_port))) {
            return BCM_E_PARAM;
        }
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_wred_get(unit, gport, cosq == -1 ? 0 : cosq,
                                &discard->flags, &min_thresh, &max_thresh,
                                &discard->drop_probability, &discard->gain,
                                0, &discard->refresh_time,
                                &discard->profile_id, &discard->use_queue_group));

    /* Convert number of cells to number of bytes */
    discard->min_thresh = min_thresh * _HX5_MMU_BYTES_PER_CELL;
    discard->max_thresh = max_thresh * _HX5_MMU_BYTES_PER_CELL;

    return BCM_E_NONE;
}


/*
 * Function:
 *      _bcm_hx5_cosq_qgroup_limit_enables_set
 * Purpose:
 *      set enables for Qgroup Min and Shared Limits
 * Parameters:
 *      unit - (IN) Unit number.
 *      port - (IN) GPORT ID.
 *      cosq - (IN) COS queue.
 *      type - (IN) feature
 *      arg  - (IN) feature value
 * Returns:
 *      BCM_E_XXX
 * Notes:
 */
STATIC int
_bcm_hx5_cosq_qgroup_limit_enables_set(int unit, bcm_gport_t gport,
        bcm_cos_t cosq,
        bcm_cosq_control_t type,
        int arg)
{
    bcm_port_t local_port = 0;
    int startq = 0, pipe = 0, count = 1, lc = 0, to_cos = 0;
    uint32 entry[SOC_MAX_MEM_WORDS];
    uint32 entry2[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm;
    soc_mem_t base_mem = INVALIDm;
    int enable = 0;
    int valid = 0;
    soc_field_t field = INVALIDf;
    soc_field_t field2 = INVALIDf;

    if (arg < 0) {
        return BCM_E_PARAM;
    }
    arg = arg ? 1 : 0;

    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
        BCM_IF_ERROR_RETURN(_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                    _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE, &local_port, &startq, NULL));
    } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        return BCM_E_PARAM;
    } else {
        if (cosq < -1) {
            return BCM_E_PARAM;
        }
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
        if (local_port < 0) {
            return BCM_E_PORT;
        }
        BCM_IF_ERROR_RETURN(_bcm_hx5_cosq_index_resolve(unit, local_port, cosq,
                    _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE, NULL, &startq, &count));
    }

    base_mem = MMU_THDU_Q_TO_QGRP_MAPm;
    mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
    if (type == bcmCosqControlEgressUCQueueGroupSharedLimitEnable) {
        field = QGROUP_LIMIT_ENABLEf;
        field2 = QGROUP_VALIDf;
    } else if (type == bcmCosqControlEgressUCQueueGroupMinEnable) {
        field = USE_QGROUP_MINf;
        field2 = QGROUP_VALIDf;
    } else {
        return BCM_E_PARAM;
    }

    to_cos = startq + count;
    for (lc = startq; lc < to_cos; lc++) {
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, lc, entry));
        enable = soc_mem_field32_get(unit, mem, entry, field);
        if (enable != arg) {
            soc_mem_field32_set(unit, mem, entry, field, arg);
            BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, lc, entry));
        }
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, lc, entry2));
        valid = soc_mem_field32_get(unit, mem, entry2, field2);
        if (valid != 1) {
            soc_mem_field32_set(unit, mem, entry2, field2, 1);
            BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, lc, entry2));
        }
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *       _bcm_hx5_cosq_qgroup_limit_enables_get
 * Purpose:
 *       get enables for Qgroup Min and Shared Limits
 * Parameters:
 *      unit - (IN) Unit number.
 *      port - (IN) GPORT ID.
 *      cosq - (IN) COS queue.
 *      type - (IN) feature
 *      arg  - (OUT) feature value
 *  Returns:
 *       BCM_E_XXX
 *  Notes:
 * */

STATIC int
_bcm_hx5_cosq_qgroup_limit_enables_get(int unit, bcm_gport_t gport,
        bcm_cos_queue_t cosq,
        bcm_cosq_control_t type,
        int *arg)
{
    int startq, pipe = 0;
    bcm_port_t local_port;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm;
    soc_mem_t base_mem = INVALIDm;
    soc_field_t field = INVALIDf;

    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
        BCM_IF_ERROR_RETURN(_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                    _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE, &local_port, &startq, NULL));
    } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        return BCM_E_PARAM;
    } else {
        if (cosq < 0) {
            return BCM_E_PARAM;
        }
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
        if (local_port < 0) {
            return BCM_E_PORT;
        }
        BCM_IF_ERROR_RETURN(_bcm_hx5_cosq_index_resolve(unit, local_port, cosq,
                    _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE, NULL, &startq, NULL));
    }

    base_mem = MMU_THDU_Q_TO_QGRP_MAPm;
    mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
    BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));

    if (type == bcmCosqControlEgressUCQueueGroupSharedLimitEnable) {
        field = QGROUP_LIMIT_ENABLEf;
    } else if (type == bcmCosqControlEgressUCQueueGroupMinEnable) {
        field = USE_QGROUP_MINf;
    } else {
        return BCM_E_PARAM;
    }

    *arg = soc_mem_field32_get(unit, mem, entry, field);
    return BCM_E_NONE;
}

/*
 *Function:
 *      _bcm_hx5_cosq_qgroup_limit_set
 *Purpose:
 *      set limits for Qgroup Min and Shared Limits
 *Parameters:
 *      unit - (IN) Unit number.
 *      port - (IN) GPORT ID.
 *      cosq - (IN) COS queue.
 *      type - (IN) feature
 *      arg  - (IN) feature value
 * Returns:
 *      BCM_E_XXX
 * Notes:
 **/

STATIC int
_bcm_hx5_cosq_qgroup_limit_set(int unit, bcm_gport_t gport, bcm_cos_t cosq,
        bcm_cosq_control_t type, int arg)
{
    int pipe = 0;
    int phy_port;
    int mmu_port;
    bcm_port_t local_port;
    soc_mem_t mem = INVALIDm;
    soc_mem_t base_mem = INVALIDm;
    soc_field_t field = INVALIDf;
    int granularity;
    int egr_db_shd_size;
    int egr_qe_shd_size;
    int cur_val;
    int max_val;
    int delta;
    uint32 rval;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_info_t *si = &SOC_INFO(unit);

    if (cosq < 0) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        return BCM_E_PARAM;
    }
    BCM_IF_ERROR_RETURN(
            _bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
    if (local_port < 0) {
        return BCM_E_PORT;
    }

    if (type == bcmCosqControlEgressUCQueueGroupMinLimitBytes ||
            type == bcmCosqControlEgressUCQueueGroupSharedLimitBytes) {
        arg = (arg + _HX5_MMU_BYTES_PER_CELL - 1) / _HX5_MMU_BYTES_PER_CELL;
    }

    phy_port = si->port_l2p_mapping[local_port];
    mmu_port = si->port_p2m_mapping[phy_port];
    base_mem = MMU_THDU_CONFIG_QGROUPm;
    mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
    BCM_IF_ERROR_RETURN(soc_mem_read(
                unit, mem, MEM_BLOCK_ALL, mmu_port, entry));

    if (type == bcmCosqControlEgressUCQueueGroupMinLimitBytes) {
        field = Q_MIN_LIMIT_CELLf;
        granularity = 1;

        rval = 0;
        SOC_IF_ERROR_RETURN(
                READ_MMU_THDM_DB_POOL_SHARED_LIMITr(unit, 0, &rval));
        egr_db_shd_size = soc_reg_field_get(
                unit, MMU_THDM_DB_POOL_SHARED_LIMITr, rval, SHARED_LIMITf);

        rval = 0;
        SOC_IF_ERROR_RETURN(
                READ_MMU_THDM_MCQE_POOL_SHARED_LIMITr(unit, 0, &rval));
        egr_qe_shd_size = soc_reg_field_get(
                unit, MMU_THDM_MCQE_POOL_SHARED_LIMITr, rval, SHARED_LIMITf);

        cur_val = soc_mem_field32_get(unit, mem, entry, field);
        delta = ((arg / granularity) - cur_val) * granularity;
        if (delta > egr_db_shd_size) {
            return BCM_E_PARAM;
        }

        SOC_IF_ERROR_RETURN(soc_hx5_mmu_config_shared_buf_recalc(
                    unit, 2, -1, egr_db_shd_size - delta, egr_qe_shd_size, 1));
    } else if (type == bcmCosqControlEgressUCQueueGroupSharedLimitBytes) {
        field = Q_SHARED_LIMIT_CELLf;
        granularity = 1;
    } else if (type == bcmCosqControlEgressUCQueueGroupSharedDynamicEnable) {
        field = Q_LIMIT_DYNAMIC_CELLf;
        granularity = 1;
    } else {
        return BCM_E_PARAM;
    }

    max_val = (1 << soc_mem_field_length(unit, mem, field)) - 1;
    if ((arg < 0) || ((arg / granularity) > max_val)) {
        return BCM_E_PARAM;
    }

    soc_mem_field32_set(unit, mem, entry, field, (arg / granularity));
    BCM_IF_ERROR_RETURN(soc_mem_write(
                unit, mem, MEM_BLOCK_ALL, mmu_port, entry));
    return BCM_E_NONE;
}


/*
 * Function:
 *      _bcm_hx5_cosq_qgroup_limit_get
 * Purpose:
 *      get limits for Qgroup Min and Shared Limits
 * Parameters:
 *      unit - (IN) Unit number.
 *      port - (IN) GPORT ID.
 *      cosq - (IN) COS queue.
 *      type - (IN) feature
 *      arg  - (OUT) feature value
 * Returns:
 *       BCM_E_XXX
 *  Notes:
 * */

STATIC int
_bcm_hx5_cosq_qgroup_limit_get(int unit, bcm_gport_t gport, bcm_cos_t cosq,
                               bcm_cosq_control_t type, int *arg)
{
    int pipe = 0;
    int phy_port;
    int mmu_port;
    bcm_port_t local_port;
    soc_mem_t mem = INVALIDm;
    soc_mem_t base_mem = INVALIDm;
    soc_field_t field = INVALIDf;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_info_t *si = &SOC_INFO(unit);

    if (cosq < 0) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        return BCM_E_PARAM;
    }
    BCM_IF_ERROR_RETURN(
            _bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
    if (local_port < 0) {
        return BCM_E_PORT;
    }

    phy_port = si->port_l2p_mapping[local_port];
    mmu_port = si->port_p2m_mapping[phy_port];
    base_mem = MMU_THDU_CONFIG_QGROUPm;
    mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
    BCM_IF_ERROR_RETURN(
            soc_mem_read(unit, mem, MEM_BLOCK_ALL, mmu_port, entry));

    if (type == bcmCosqControlEgressUCQueueGroupMinLimitBytes) {
        field = Q_MIN_LIMIT_CELLf;
    } else if (type == bcmCosqControlEgressUCQueueGroupSharedLimitBytes) {
        field = Q_SHARED_LIMIT_CELLf;
    } else if (type == bcmCosqControlEgressUCQueueGroupSharedDynamicEnable) {
        field = Q_LIMIT_DYNAMIC_CELLf;
    } else {
        return BCM_E_PARAM;
    }

    *arg = soc_mem_field32_get(unit, mem, entry, field);
    if (type == bcmCosqControlEgressUCQueueGroupMinLimitBytes ||
            type == bcmCosqControlEgressUCQueueGroupSharedLimitBytes) {
        *arg = (*arg) * _HX5_MMU_BYTES_PER_CELL;
    }
    return BCM_E_NONE;
}

/*
 *Function:
 *      _bcm_hx5_cosq_qgroup_alpha_set
 * Purpose:
 *      set alpha for qgroup
 * Parameters:
 *      unit - (IN) Unit number.
 *      port - (IN) GPORT ID.
 *      cosq - (IN) COS queue.
 *      arg  - (IN) feature value
 * Returns:
 *      BCM_E_XXX
 * Notes:
 **/ 
STATIC int
_bcm_hx5_cosq_qgroup_alpha_set(int unit, bcm_gport_t gport,
                               bcm_cos_queue_t cosq,
                               bcm_cosq_control_drop_limit_alpha_value_t arg)
{   
    int alpha;
    int pipe = 0;
    int phy_port;
    int mmu_port;
    bcm_port_t local_port;
    soc_mem_t mem = INVALIDm;
    soc_mem_t base_mem = INVALIDm;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_info_t *si = &SOC_INFO(unit);

    if (cosq < 0) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN(
            _bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
    if (local_port < 0) {
        return BCM_E_PORT;
    }

    switch(arg) {
        case bcmCosqControlDropLimitAlpha_1_128:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_128;
            break;
        case bcmCosqControlDropLimitAlpha_1_64:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_64;
            break;
        case bcmCosqControlDropLimitAlpha_1_32:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_32;
            break;
        case bcmCosqControlDropLimitAlpha_1_16:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_16;
            break;
        case bcmCosqControlDropLimitAlpha_1_8:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_8;
            break;
        case bcmCosqControlDropLimitAlpha_1_4:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_4;
            break;
        case bcmCosqControlDropLimitAlpha_1_2:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_2;
            break;
        case bcmCosqControlDropLimitAlpha_1:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1;
            break;
        case bcmCosqControlDropLimitAlpha_2:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_2;
            break;
        case bcmCosqControlDropLimitAlpha_4:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_4;
            break;
        case bcmCosqControlDropLimitAlpha_8:
            alpha = SOC_HX5_COSQ_DROP_LIMIT_ALPHA_8;
            break;
        default:
            return BCM_E_PARAM;
    }

    phy_port = si->port_l2p_mapping[local_port];
    mmu_port = si->port_p2m_mapping[phy_port];
    base_mem = MMU_THDU_CONFIG_QGROUPm;
    mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
    BCM_IF_ERROR_RETURN(soc_mem_read(
                unit, mem, MEM_BLOCK_ALL, mmu_port, entry));

    soc_mem_field32_set(unit, mem, entry, Q_SHARED_ALPHA_CELLf, alpha);
    BCM_IF_ERROR_RETURN(soc_mem_write(
                unit, mem, MEM_BLOCK_ALL, mmu_port, entry));
    return BCM_E_NONE;
}

/*
 * Function:
 *       _bcm_hx5_cosq_qgroup_alpha_get
 * Purpose:
 *      get alpha for qgroup
 * Parameters:
 *      unit - (IN) Unit number.
 *      port - (IN) GPORT ID.
 *      cosq - (IN) COS queue.
 *      arg  - (OUT) feature value
 * Returns:
 *      BCM_E_XXX
 * Notes:
 **/

STATIC int
_bcm_hx5_cosq_qgroup_alpha_get(int unit, bcm_gport_t gport,
        bcm_cos_queue_t cosq,
        bcm_cosq_control_drop_limit_alpha_value_t *arg)
{
    int alpha;
    int pipe = 0;
    int phy_port;
    int mmu_port;
    bcm_port_t local_port;
    soc_mem_t mem = INVALIDm;
    soc_mem_t base_mem = INVALIDm;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_info_t *si = &SOC_INFO(unit);

    if (cosq < 0) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN(
            _bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
    if (local_port < 0) {
        return BCM_E_PORT;
    }

    phy_port = si->port_l2p_mapping[local_port];
    mmu_port = si->port_p2m_mapping[phy_port];
    base_mem = MMU_THDU_CONFIG_QGROUPm;
    mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[pipe];
    BCM_IF_ERROR_RETURN(soc_mem_read(
                unit, mem, MEM_BLOCK_ALL, mmu_port, entry));
    alpha = soc_mem_field32_get(unit, mem, entry, Q_SHARED_ALPHA_CELLf);

    switch(alpha) {
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_128:
            *arg = bcmCosqControlDropLimitAlpha_1_128;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_64:
            *arg = bcmCosqControlDropLimitAlpha_1_64;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_32:
            *arg = bcmCosqControlDropLimitAlpha_1_32;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_16:
            *arg = bcmCosqControlDropLimitAlpha_1_16;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_8:
            *arg = bcmCosqControlDropLimitAlpha_1_8;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_4:
            *arg = bcmCosqControlDropLimitAlpha_1_4;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1_2:
            *arg = bcmCosqControlDropLimitAlpha_1_2;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_1:
            *arg = bcmCosqControlDropLimitAlpha_1;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_2:
            *arg = bcmCosqControlDropLimitAlpha_2;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_4:
            *arg = bcmCosqControlDropLimitAlpha_4;
            break;
        case SOC_HX5_COSQ_DROP_LIMIT_ALPHA_8:
            *arg = bcmCosqControlDropLimitAlpha_8;
            break;
        default:
            return BCM_E_PARAM;
    }

    return BCM_E_NONE;
}

/*
 * Function: _bcm_hx5_cosq_egr_queue_color_limit_mode_set
 * Purpose: Set color limit mode per queue to static (0) or
 *          dynamic (1)
*/

STATIC int
_bcm_hx5_cosq_egr_queue_color_limit_mode_set(int unit, bcm_gport_t gport,
                                             bcm_cos_queue_t cosq,
                                             bcm_cosq_control_t type,
                                             int arg)
{
    bcm_port_t local_port;
    int startq, pipe;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm;
    int enable;

    if (arg < 0) {
        return BCM_E_PARAM;
    }

    arg = arg ? 1 : 0;

    if (type == bcmCosqControlEgressUCQueueColorLimitDynamicEnable) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                            &local_port, &startq, NULL));
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        } else {
            if (cosq < 0) {
                return BCM_E_PARAM;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve
                 (unit, local_port, cosq, _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                  NULL, &startq, NULL));
        }
        BCM_IF_ERROR_RETURN(soc_port_pipe_get(unit, local_port, &pipe));
        mem = SOC_MEM_UNIQUE_ACC(unit, MMU_THDU_CONFIG_QUEUEm)[pipe];
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        enable = soc_mem_field32_get(unit, mem, entry, Q_COLOR_LIMIT_DYNAMIC_CELLf);
        if (enable != arg) {
            soc_mem_field32_set(unit, mem, entry, Q_COLOR_LIMIT_DYNAMIC_CELLf, arg);
            /* Reset the Red and Yellow limits when color limit mode is changed */
            soc_mem_field32_set(unit, mem, entry, LIMIT_RED_CELLf, 0);
            soc_mem_field32_set(unit, mem, entry, LIMIT_YELLOW_CELLf, 0);
            BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, startq, entry));
        }
    } else if (type == bcmCosqControlEgressMCQueueColorLimitDynamicEnable) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                            &local_port, &startq, NULL));
        } else {
            if (cosq < 0) {
                return BCM_E_PARAM;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, local_port, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                            NULL, &startq, NULL));
        }
        BCM_IF_ERROR_RETURN(soc_port_pipe_get(unit, local_port, &pipe));
        mem = SOC_MEM_UNIQUE_ACC(unit, MMU_THDM_DB_QUEUE_CONFIGm)[pipe];
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        enable = soc_mem_field32_get(unit, mem, entry, Q_COLOR_LIMIT_DYNAMICf);
        if (enable != arg) {
            soc_mem_field32_set(unit, mem, entry, Q_COLOR_LIMIT_DYNAMICf, arg);
            /* Reset the Red and Yellow limits when color limit mode is changed */
            soc_mem_field32_set(unit, mem, entry, RED_SHARED_LIMITf, 0);
            soc_mem_field32_set(unit, mem, entry, YELLOW_SHARED_LIMITf, 0);
            BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, startq, entry));
        }

        mem = SOC_MEM_UNIQUE_ACC(unit, MMU_THDM_MCQE_QUEUE_CONFIGm)[pipe];
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        enable = soc_mem_field32_get(unit, mem, entry, Q_COLOR_LIMIT_DYNAMICf);
        if (enable != arg) {
            soc_mem_field32_set(unit, mem, entry, Q_COLOR_LIMIT_DYNAMICf, arg);
            /* Reset the Red and Yellow limits when color limit mode is changed */
            soc_mem_field32_set(unit, mem, entry, RED_SHARED_LIMITf, 0);
            soc_mem_field32_set(unit, mem, entry, YELLOW_SHARED_LIMITf, 0);
            BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, startq, entry));
        }

    } else {
        return BCM_E_PARAM;
    }

    return BCM_E_NONE;
}

/*
 * Function: _bcm_hx5_cosq_egr_queue_color_limit_mode_get
 * Purpose: Get color limit mode per queue.
 * Returns: 0 (static) or 1 (dynamic)
*/
STATIC int
_bcm_hx5_cosq_egr_queue_color_limit_mode_get(int unit, bcm_gport_t gport,
                                             bcm_cos_queue_t cosq,
                                             bcm_cosq_control_t type,
                                             int* arg)
{
    bcm_port_t local_port;
    int startq, pipe;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm;

    if (arg == NULL) {
        return BCM_E_PARAM;
    }

    if (type == bcmCosqControlEgressUCQueueColorLimitDynamicEnable) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                            &local_port, &startq, NULL));
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        } else {
            if (cosq < 0) {
                return BCM_E_PARAM;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve
                 (unit, local_port, cosq, _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                  NULL, &startq, NULL));
        }
        BCM_IF_ERROR_RETURN(soc_port_pipe_get(unit, local_port, &pipe));
        mem = SOC_MEM_UNIQUE_ACC(unit, MMU_THDU_CONFIG_QUEUEm)[pipe];
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        *arg = soc_mem_field32_get(unit, mem, entry, Q_COLOR_LIMIT_DYNAMIC_CELLf);
    } else if (type == bcmCosqControlEgressMCQueueColorLimitDynamicEnable) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                            &local_port, &startq, NULL));
        } else {
            if (cosq < 0) {
                return BCM_E_PARAM;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, local_port, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                            NULL, &startq, NULL));
        }
        BCM_IF_ERROR_RETURN(soc_port_pipe_get(unit, local_port, &pipe));
        mem = SOC_MEM_UNIQUE_ACC(unit, MMU_THDM_DB_QUEUE_CONFIGm)[pipe];
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        *arg = soc_mem_field32_get(unit, mem, entry, Q_COLOR_LIMIT_DYNAMICf);
    } else {
        return BCM_E_PARAM;
    }

    return BCM_E_NONE;

}
/*
 * Function: _bcm_hx5_cosq_egr_queue_color_limit_set
 * Purpose: Set Red and Yellow color limit per queue
 *          IF color mode dynamic: limit should be between 0-7
 *                                 0: 100% of green threshold
 *                                 1: 12.5% of green threshold
 *                                 2: 25% of green threshold
 *                                 3: 37.5% of green threshold
 *                                 4: 50% of green threshold
 *                                 5: 67.5% of green threshold
 *                                 6: 75% of green threshold
 *                                 7: 87.5% of green threshold
 *          If color mode static: Limit is number of bytes
*/

STATIC int
_bcm_hx5_cosq_egr_queue_color_limit_set(int unit, bcm_gport_t gport,
                                        bcm_cos_queue_t cosq,
                                        bcm_cosq_control_t type,
                                        int arg)
{
    bcm_port_t local_port;
    int startq, pipe;
    uint32 entry[SOC_MAX_MEM_WORDS];
    uint32 entry1[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm;
    soc_mem_t mem1 = INVALIDm;
    soc_field_t fld_limit = INVALIDf;
    int color_mode, granularity, max_val;

    if (arg < 0) {
        return BCM_E_PARAM;
    }
    granularity = 8;

    if ((type == bcmCosqControlEgressUCQueueRedLimit) ||
        (type == bcmCosqControlEgressUCQueueYellowLimit)) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                            &local_port, &startq, NULL));
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        } else {
            if (cosq < 0) {
                return BCM_E_PARAM;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve
                 (unit, local_port, cosq, _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                  NULL, &startq, NULL));
        }
        if (type == bcmCosqControlEgressUCQueueRedLimit) {
            fld_limit = LIMIT_RED_CELLf;
        } else {
            fld_limit = LIMIT_YELLOW_CELLf;
        }
        BCM_IF_ERROR_RETURN(soc_port_pipe_get(unit, local_port, &pipe));
        mem = SOC_MEM_UNIQUE_ACC(unit, MMU_THDU_CONFIG_QUEUEm)[pipe];
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        color_mode = soc_mem_field32_get(unit, mem, entry, Q_COLOR_LIMIT_DYNAMIC_CELLf);

        if (color_mode == 1) { /* Dynamic color limit */
            if (arg > 7) { /* Legal values are 0 - 7 */
                return BCM_E_PARAM;
            } else {
                soc_mem_field32_set(unit, mem, entry, fld_limit, arg);
            }
        } else { /* Static color limit */
            arg = (arg + _HX5_MMU_BYTES_PER_CELL - 1) / _HX5_MMU_BYTES_PER_CELL;

            /* Check for min/max values */
            max_val = (1 << soc_mem_field_length(unit, mem, fld_limit)) - 1;
            if ((arg/granularity) > max_val) {
                return BCM_E_PARAM;
            } else {
                soc_mem_field32_set(unit, mem, entry, fld_limit, (arg/granularity));
            }
        }
        BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, startq, entry));
    } else if ((type == bcmCosqControlEgressMCQueueRedLimit) ||
               (type == bcmCosqControlEgressMCQueueYellowLimit)) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                            &local_port, &startq, NULL));
        } else {
            if (cosq < 0) {
                return BCM_E_PARAM;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, local_port, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                            NULL, &startq, NULL));
        }

        if (type == bcmCosqControlEgressMCQueueRedLimit) {
            fld_limit = RED_SHARED_LIMITf;
        } else {
            fld_limit = YELLOW_SHARED_LIMITf;
        }
        BCM_IF_ERROR_RETURN(soc_port_pipe_get(unit, local_port, &pipe));
        mem = SOC_MEM_UNIQUE_ACC(unit, MMU_THDM_DB_QUEUE_CONFIGm)[pipe];
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        mem1 = SOC_MEM_UNIQUE_ACC(unit, MMU_THDM_MCQE_QUEUE_CONFIGm)[pipe];
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem1, MEM_BLOCK_ALL, startq, entry1));
        color_mode = soc_mem_field32_get(unit, mem, entry, Q_COLOR_LIMIT_DYNAMICf);

        if (color_mode == 1) { /* Dynamic color limit */
            if (arg > 7) { /* Legal values are 0 - 7 */
                return BCM_E_PARAM;
            } else {
                soc_mem_field32_set(unit, mem, entry, fld_limit, arg);
                soc_mem_field32_set(unit, mem1, entry1, fld_limit, arg);
            }
        } else { /* Static color limit */
            arg = (arg + _HX5_MMU_BYTES_PER_CELL - 1) / _HX5_MMU_BYTES_PER_CELL;

            /* Check for min/max values */
            max_val = (1 << soc_mem_field_length(unit, mem, fld_limit)) - 1;
            if ((arg/granularity) > max_val) {
                return BCM_E_PARAM;
            } else {
                soc_mem_field32_set(unit, mem, entry, fld_limit, (arg/granularity));
                soc_mem_field32_set(unit, mem1, entry1, fld_limit, (arg/granularity));
            }
        }
        BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, startq, entry));
        BCM_IF_ERROR_RETURN(soc_mem_write(unit, mem1, MEM_BLOCK_ALL, startq, entry1));

    } else {
        return BCM_E_PARAM;
    }

    return BCM_E_NONE;
}


/*
 * Function: _bcm_hx5_cosq_egr_queue_color_limit_get
 * Purpose: Get Red and Yellow color limit per queue
 * Return value: IF color mode dynamic: limit should be between 0-7
 *                                 0: 100% of green threshold
 *                                 1: 12.5% of green threshold
 *                                 2: 25% of green threshold
 *                                 3: 37.5% of green threshold
 *                                 4: 50% of green threshold
 *                                 5: 67.5% of green threshold
 *                                 6: 75% of green threshold
 *                                 7: 87.5% of green threshold
 *          If color mode static: Limit is number of bytes
*/

STATIC int
_bcm_hx5_cosq_egr_queue_color_limit_get(int unit, bcm_gport_t gport,
                                        bcm_cos_queue_t cosq,
                                        bcm_cosq_control_t type,
                                        int* arg)
{
    bcm_port_t local_port;
    int startq, pipe;
    uint32 entry[SOC_MAX_MEM_WORDS];
    soc_mem_t mem = INVALIDm;
    soc_field_t fld_limit = INVALIDf;
    int color_mode, granularity;

    if (arg == NULL) {
        return BCM_E_PARAM;
    }

    granularity = 8;

    if ((type == bcmCosqControlEgressUCQueueRedLimit) ||
        (type == bcmCosqControlEgressUCQueueYellowLimit)) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                            &local_port, &startq, NULL));
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        } else {
            if (cosq < 0) {
                return BCM_E_PARAM;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve
                 (unit, local_port, cosq, _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                  NULL, &startq, NULL));
        }

        if (type == bcmCosqControlEgressUCQueueRedLimit) {
            fld_limit = LIMIT_RED_CELLf;
        } else {
            fld_limit = LIMIT_YELLOW_CELLf;
        }
        BCM_IF_ERROR_RETURN(soc_port_pipe_get(unit, local_port, &pipe));
        mem = SOC_MEM_UNIQUE_ACC(unit, MMU_THDU_CONFIG_QUEUEm)[pipe];
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        color_mode = soc_mem_field32_get(unit, mem, entry, Q_COLOR_LIMIT_DYNAMIC_CELLf);

        if (color_mode == 1) { /* Dynamic color limit */
            *arg = soc_mem_field32_get(unit, mem, entry, fld_limit);
        } else { /* Static color limit */
            *arg = soc_mem_field32_get(unit, mem, entry, fld_limit);
            *arg = (*arg) * granularity * _HX5_MMU_BYTES_PER_CELL;
        }
    } else if ((type == bcmCosqControlEgressMCQueueRedLimit) ||
               (type == bcmCosqControlEgressMCQueueYellowLimit)) {
        if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
            return BCM_E_PARAM;
        } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                            &local_port, &startq, NULL));
        } else {
            if (cosq < 0) {
                return BCM_E_PARAM;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
            if (local_port < 0) {
                return BCM_E_PORT;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, local_port, cosq,
                                            _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                            NULL, &startq, NULL));
        }

        if (type == bcmCosqControlEgressMCQueueRedLimit) {
            fld_limit = RED_SHARED_LIMITf;
        } else {
            fld_limit = YELLOW_SHARED_LIMITf;
        }
        BCM_IF_ERROR_RETURN(soc_port_pipe_get(unit, local_port, &pipe));
        mem = SOC_MEM_UNIQUE_ACC(unit, MMU_THDM_DB_QUEUE_CONFIGm)[pipe];
        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
        color_mode = soc_mem_field32_get(unit, mem, entry, Q_COLOR_LIMIT_DYNAMICf);

        if (color_mode == 1) { /* Dynamic color limit */
            *arg = soc_mem_field32_get(unit, mem, entry, fld_limit);
        } else { /* Static color limit */
            *arg = soc_mem_field32_get(unit, mem, entry, fld_limit);
            *arg = (*arg) * granularity * _HX5_MMU_BYTES_PER_CELL;
        }

    } else {
        return BCM_E_PARAM;
    }

    return BCM_E_NONE;
}


/*
 * Function:
 *      bcm_hx5_cosq_control_set
 * Purpose:
 *      Set specified feature configuration
 *
 * Parameters:
 *      unit - (IN) Unit number.
 *      port - (IN) GPORT ID.
 *      cosq - (IN) COS queue.
 *      type - (IN) feature
 *      arg  - (IN) feature value
 * Returns:
 *      BCM_E_XXX
 * Notes:
 */
int
bcm_hx5_cosq_control_set(int unit, bcm_gport_t gport, bcm_cos_queue_t cosq,
                        bcm_cosq_control_t type, int arg)
{
    uint32 kbits_burst_min, kbits_burst_max;
    uint32 kbits_burst;

    kbits_burst_min = 0;
    kbits_burst_max = 0;

    COMPILER_REFERENCE(kbits_burst_min);
    COMPILER_REFERENCE(kbits_burst_max);

    switch (type) {
        case bcmCosqControlBandwidthBurstMax:
            kbits_burst = arg & 0x7fffffff; /* Convert to uint32  */
            BCM_IF_ERROR_RETURN
                (bcm_hx5_cosq_gport_bandwidth_burst_get(unit, gport, cosq,
                                                        &kbits_burst_min,
                                                        &kbits_burst_max));
            return bcm_hx5_cosq_gport_bandwidth_burst_set(unit, gport, cosq,
                                                             kbits_burst_min,
                                                             kbits_burst);
        case bcmCosqControlBandwidthBurstMin:
            kbits_burst = arg & 0x7fffffff; /* Convert to uint32  */
            BCM_IF_ERROR_RETURN
                (bcm_hx5_cosq_gport_bandwidth_burst_get(unit, gport, cosq,
                                                       &kbits_burst_min,
                                                       &kbits_burst_max));
            return bcm_hx5_cosq_gport_bandwidth_burst_set(unit, gport, cosq,
                                                         kbits_burst,
                                                         kbits_burst_max);
        case bcmCosqControlEgressPool:
        case bcmCosqControlEgressPoolLimitBytes:
        case bcmCosqControlEgressPoolYellowLimitBytes:
        case bcmCosqControlEgressPoolRedLimitBytes:
        case bcmCosqControlEgressPoolLimitEnable:
        case bcmCosqControlUCEgressPool:
        case bcmCosqControlMCEgressPool:
        case bcmCosqControlEgressPoolSharedLimitBytes:
        case bcmCosqControlEgressPoolResumeLimitBytes:
        case bcmCosqControlEgressPoolYellowSharedLimitBytes:
        case bcmCosqControlEgressPoolYellowResumeLimitBytes:
        case bcmCosqControlEgressPoolRedSharedLimitBytes:
        case bcmCosqControlEgressPoolRedResumeLimitBytes:
        case bcmCosqControlEgressPoolHighCongestionLimitBytes:
        case bcmCosqControlEgressPoolLowCongestionLimitBytes:
        case bcmCosqControlEgressPoolMCSharedEntryLimit:
            return _bcm_hx5_cosq_egr_pool_set(unit, gport, cosq, type, arg);
        case bcmCosqControlEgressUCQueueSharedLimitBytes:
        case bcmCosqControlEgressMCQueueSharedLimitBytes:
        case bcmCosqControlEgressUCQueueMinLimitBytes:
        case bcmCosqControlEgressMCQueueMinLimitBytes:
            return _bcm_hx5_cosq_egr_queue_set(unit, gport, cosq, type, arg);
        case bcmCosqControlIngressPortPGSharedLimitBytes:
        case bcmCosqControlIngressPortPGMinLimitBytes:
        case bcmCosqControlIngressPortPoolMaxLimitBytes:
        case bcmCosqControlIngressPortPoolMinLimitBytes:
        case bcmCosqControlIngressPortPGHeadroomLimitBytes:
        case bcmCosqControlIngressPortPGResetFloorBytes:
        case bcmCosqControlIngressPortPGResetOffsetBytes:
            return _bcm_hx5_cosq_ing_res_set(unit, gport, cosq, type, arg);
        case bcmCosqControlIngressPool:
        case bcmCosqControlIngressHeadroomPool:
            return _bcm_hx5_cosq_ing_pool_set(unit, gport, cosq, type, arg);
        case bcmCosqControlDropLimitAlpha:
        case bcmCosqControlUCDropLimitAlpha:
        case bcmCosqControlMCDropLimitAlpha:
            return _bcm_hx5_cosq_alpha_set(unit, gport, cosq, type,
                                (bcm_cosq_control_drop_limit_alpha_value_t)arg);
        case bcmCosqControlIngressPortPGSharedDynamicEnable:
        case bcmCosqControlEgressUCSharedDynamicEnable:
        case bcmCosqControlEgressMCSharedDynamicEnable:
            return _bcm_hx5_cosq_dynamic_thresh_enable_set(unit, gport, cosq,
                    type, arg);
        case bcmCosqControlEgressPortPoolYellowLimitBytes:
        case bcmCosqControlEgressPortPoolRedLimitBytes:
            return _bcm_hx5_cosq_egr_port_pool_set(unit, gport, cosq, type, arg);
        case bcmCosqControlEgressUCQueueLimitEnable:
        case bcmCosqControlEgressMCQueueLimitEnable:
        case bcmCosqControlEgressMCQueueColorLimitEnable:
        case bcmCosqControlEgressUCQueueColorLimitEnable:
            return _bcm_hx5_cosq_egr_queue_limit_enable_set(unit, gport, cosq,
                    type, arg);
        case bcmCosqControlIngressPoolLimitBytes:
        case bcmCosqControlIngressHeadroomPoolLimitBytes:
            return _bcm_hx5_cosq_ing_res_limit_set(unit, gport, cosq, type, arg);
        case bcmCosqControlIngressPortPGGlobalHeadroomEnable:
            return _bcm_hx5_cosq_ing_res_enable_set(unit, gport, cosq, type, arg);
        case bcmCosqControlEgressUCQueueGroupMinEnable:
        case bcmCosqControlEgressUCQueueGroupSharedLimitEnable:
            return _bcm_hx5_cosq_qgroup_limit_enables_set(
                    unit, gport, cosq, type, arg); 
        case bcmCosqControlEgressUCQueueGroupMinLimitBytes:
        case bcmCosqControlEgressUCQueueGroupSharedLimitBytes:
        case bcmCosqControlEgressUCQueueGroupSharedDynamicEnable:
            return _bcm_hx5_cosq_qgroup_limit_set(unit, gport, cosq, type, arg); 
        case bcmCosqControlEgressUCQueueGroupDropLimitAlpha:
            return _bcm_hx5_cosq_qgroup_alpha_set(unit, gport, cosq, 
                    (bcm_cosq_control_drop_limit_alpha_value_t)arg);

        case bcmCosqControlEgressUCQueueColorLimitDynamicEnable:
        case bcmCosqControlEgressMCQueueColorLimitDynamicEnable:
            return _bcm_hx5_cosq_egr_queue_color_limit_mode_set(unit, gport, cosq,
                    type, arg);
        case bcmCosqControlEgressUCQueueRedLimit:
        case bcmCosqControlEgressUCQueueYellowLimit:
        case bcmCosqControlEgressMCQueueRedLimit:
        case bcmCosqControlEgressMCQueueYellowLimit:
            return _bcm_hx5_cosq_egr_queue_color_limit_set(unit, gport, cosq,
                    type, arg);
        default:
            break;
    }
    return BCM_E_UNAVAIL;
}

/*
 * Function:
 *      bcm_hx5_cosq_control_get
 * Purpose:
 *      Get specified feature configuration
 *
 * Parameters:
 *      unit - (IN) Unit number.
 *      port - (IN) GPORT ID.
 *      cosq - (IN) COS queue.
 *      type - (IN) feature
 *      arg  - (OUT) feature value
 * Returns:
 *      BCM_E_XXX
 * Notes:
 */
int
bcm_hx5_cosq_control_get(int unit, bcm_gport_t gport, bcm_cos_queue_t cosq,
                        bcm_cosq_control_t type, int *arg)
{
    uint32 kburst_tmp, kbits_burst;

    switch (type) {
        case bcmCosqControlBandwidthBurstMax:
            BCM_IF_ERROR_RETURN
                (bcm_hx5_cosq_gport_bandwidth_burst_get(unit, gport, cosq,
                                                       &kburst_tmp,
                                                       &kbits_burst));
            *arg = kbits_burst & 0x7fffffff; /* Convert to int  */
            return BCM_E_NONE;

        case bcmCosqControlBandwidthBurstMin:
            return bcm_hx5_cosq_gport_bandwidth_burst_get(unit, gport, cosq,
                                                         (uint32*)arg,
                                                         &kburst_tmp);
        case bcmCosqControlEgressPool:
        case bcmCosqControlEgressPoolLimitBytes:
        case bcmCosqControlEgressPoolYellowLimitBytes:
        case bcmCosqControlEgressPoolRedLimitBytes:
        case bcmCosqControlEgressPoolLimitEnable:
        case bcmCosqControlUCEgressPool:
        case bcmCosqControlMCEgressPool:
        case bcmCosqControlEgressPoolSharedLimitBytes:
        case bcmCosqControlEgressPoolResumeLimitBytes:
        case bcmCosqControlEgressPoolYellowSharedLimitBytes:
        case bcmCosqControlEgressPoolYellowResumeLimitBytes:
        case bcmCosqControlEgressPoolRedSharedLimitBytes:
        case bcmCosqControlEgressPoolRedResumeLimitBytes:
        case bcmCosqControlEgressPoolHighCongestionLimitBytes:
        case bcmCosqControlEgressPoolLowCongestionLimitBytes:
        case bcmCosqControlEgressPoolMCSharedEntryLimit:
            return _bcm_hx5_cosq_egr_pool_get(unit, gport, cosq, type, arg);
        case bcmCosqControlEgressUCQueueSharedLimitBytes:
        case bcmCosqControlEgressMCQueueSharedLimitBytes:
        case bcmCosqControlEgressUCQueueMinLimitBytes:
        case bcmCosqControlEgressMCQueueMinLimitBytes:
            return _bcm_hx5_cosq_egr_queue_get(unit, gport, cosq, type, arg);
        case bcmCosqControlIngressPortPGSharedLimitBytes:
        case bcmCosqControlIngressPortPGMinLimitBytes:
        case bcmCosqControlIngressPortPoolMaxLimitBytes:
        case bcmCosqControlIngressPortPoolMinLimitBytes:
        case bcmCosqControlIngressPortPGHeadroomLimitBytes:
        case bcmCosqControlIngressPortPGResetFloorBytes:
        case bcmCosqControlIngressPortPGResetOffsetBytes:
            return _bcm_hx5_cosq_ing_res_get(unit, gport, cosq, type, arg);
        case bcmCosqControlIngressPool:
        case bcmCosqControlIngressHeadroomPool:
            return _bcm_hx5_cosq_ing_pool_get(unit, gport, cosq, type, arg);
        case bcmCosqControlDropLimitAlpha:
        case bcmCosqControlUCDropLimitAlpha:
        case bcmCosqControlMCDropLimitAlpha:
            return _bcm_hx5_cosq_alpha_get(unit, gport, cosq, type,
                            (bcm_cosq_control_drop_limit_alpha_value_t *)arg);
        case bcmCosqControlIngressPortPGSharedDynamicEnable:
        case bcmCosqControlEgressUCSharedDynamicEnable:
        case bcmCosqControlEgressMCSharedDynamicEnable:
            return _bcm_hx5_cosq_dynamic_thresh_enable_get(unit, gport, cosq,
                                                          type, arg);
        case bcmCosqControlEgressPortPoolYellowLimitBytes:
        case bcmCosqControlEgressPortPoolRedLimitBytes:
            return _bcm_hx5_cosq_egr_port_pool_get(unit, gport, cosq, type, arg);
        case bcmCosqControlEgressUCQueueLimitEnable:
        case bcmCosqControlEgressMCQueueLimitEnable:
        case bcmCosqControlEgressMCQueueColorLimitEnable:
        case bcmCosqControlEgressUCQueueColorLimitEnable:
            return _bcm_hx5_cosq_egr_queue_limit_enable_get(unit, gport, cosq,
                    type, arg);
        case bcmCosqControlIngressPoolLimitBytes:
        case bcmCosqControlIngressHeadroomPoolLimitBytes:
            return _bcm_hx5_cosq_ing_res_limit_get(unit, gport, cosq, type, arg);
        case bcmCosqControlIngressPortPGGlobalHeadroomEnable:
            return _bcm_hx5_cosq_ing_res_enable_get(unit, gport, cosq, type, arg);
        case bcmCosqControlEgressUCQueueGroupMinEnable:
        case bcmCosqControlEgressUCQueueGroupSharedLimitEnable:
            return _bcm_hx5_cosq_qgroup_limit_enables_get(
                    unit, gport, cosq, type, arg);
        case bcmCosqControlEgressUCQueueGroupMinLimitBytes:
        case bcmCosqControlEgressUCQueueGroupSharedLimitBytes:
        case bcmCosqControlEgressUCQueueGroupSharedDynamicEnable:
            return _bcm_hx5_cosq_qgroup_limit_get(unit, gport, cosq, type, arg);
        case bcmCosqControlEgressUCQueueGroupDropLimitAlpha:
            return _bcm_hx5_cosq_qgroup_alpha_get(unit, gport, cosq,
                    (bcm_cosq_control_drop_limit_alpha_value_t*)arg);

        case bcmCosqControlEgressUCQueueColorLimitDynamicEnable:
        case bcmCosqControlEgressMCQueueColorLimitDynamicEnable:
            return _bcm_hx5_cosq_egr_queue_color_limit_mode_get(unit, gport, cosq,
                    type, arg);

        case bcmCosqControlEgressUCQueueRedLimit:
        case bcmCosqControlEgressUCQueueYellowLimit:
        case bcmCosqControlEgressMCQueueRedLimit:
        case bcmCosqControlEgressMCQueueYellowLimit:
            return _bcm_hx5_cosq_egr_queue_color_limit_get(unit, gport, cosq, type,
                    arg);
        default:
            break;
    }
    return BCM_E_UNAVAIL;
}
/*
 * Function:
 *     bcm_hx5_cosq_gport_bandwidth_get
 * Purpose:
 *     Get COS queue bandwidth control configuration
 * Parameters:
 *     unit   - (IN) unit number
 *     gport  - (IN) GPORT identifier
 *     cosq   - (IN) COS queue number
 *     kbits_sec_min - (OUT) minimum bandwidth, kbits/sec
 *     kbits_sec_max - (OUT) maximum bandwidth, kbits/sec
 *     flags  - (OUT) BCM_COSQ_BW_XXX
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_gport_bandwidth_get(int unit, bcm_gport_t gport,
                                 bcm_cos_queue_t cosq, uint32 *kbits_sec_min,
                                 uint32 *kbits_sec_max, uint32 *flags)
{
    uint32 kbits_sec_burst;

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_bucket_get(unit, gport, cosq, kbits_sec_min,
                                  kbits_sec_max, &kbits_sec_burst,
                                  &kbits_sec_burst, flags));

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_gport_bandwidth_set
 * Purpose:
 *     Configure COS queue bandwidth control
 * Parameters:
 *     unit   - (IN) unit number
 *     gport  - (IN) GPORT identifier
 *     cosq   - (IN) COS queue number
 *     kbits_sec_min - (IN) minimum bandwidth, kbits/sec
 *     kbits_sec_max - (IN) maximum bandwidth, kbits/sec
 *     flags  - (IN) BCM_COSQ_BW_XXX
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_gport_bandwidth_set(int unit, bcm_gport_t gport,
                                 bcm_cos_queue_t cosq, uint32 kbits_sec_min,
                                 uint32 kbits_sec_max, uint32 flags)
{
    int i = 0, local_port;
    _bcm_hx5_cosq_node_t *node = NULL;
    uint32 burst_min, burst_max;

    BCM_IF_ERROR_RETURN(_bcm_hx5_cosq_localport_resolve(unit, gport,
                                                        &local_port));

    if (BCM_GPORT_IS_SET(gport)) {
        if ((BCM_GPORT_IS_SCHEDULER(gport)) ||
            BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) ||
            BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_node_get(unit, gport, NULL, NULL, NULL, &node));

            if (node != NULL) {
                 i = node->hw_index;
            } else {
                cosq = 0;
            }
        } else {
            if (cosq < 0) {
                return BCM_E_PARAM;
            }
            i  = cosq;
        }
    } else {
        if (cosq < 0) {
            return BCM_E_PARAM;
        }
        i = cosq;
    }

    burst_min = (kbits_sec_min > 0) ?
        _bcm_td_default_burst_size(unit, local_port, kbits_sec_min) : 0;

    burst_max = (kbits_sec_max > 0) ?
        _bcm_td_default_burst_size(unit, local_port, kbits_sec_max) : 0;

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_bucket_set(unit, gport, i, kbits_sec_min,
                                      kbits_sec_max, burst_min, burst_max,
                                      flags));

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_port_bandwidth_set
 * Purpose:
 *     Configure COS queue bandwidth control
 * Parameters:
 *     unit   - (IN) unit number
 *     port   - (IN) port number
 *     cosq   - (IN) COS queue number
 *     min_quantum   - (IN) minimum bandwidth, kbits/sec
 *     max_quantum   - (IN) maximum bandwidth, kbits/sec
 *     burst_quantum - (IN) burst size, kbits/sec
 *     flags  - (IN) BCM_COSQ_BW_XXX
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_port_bandwidth_set(int unit, bcm_port_t port,
                                bcm_cos_queue_t cosq, uint32 min_quantum,
                                uint32 max_quantum, uint32 burst_quantum,
                                uint32 flags)
{
    uint32 burst_min, burst_max;

    if (cosq < 0) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_SET(port)) {
        if ((BCM_GPORT_IS_SCHEDULER(port)) ||
            BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
            BCM_GPORT_IS_MCAST_QUEUE_GROUP(port) ||
            BCM_GPORT_IS_UCAST_SUBSCRIBER_QUEUE_GROUP(port)) {
            return BCM_E_UNAVAIL;
        }
    }

    burst_min = (min_quantum > 0) ?
        _bcm_td_default_burst_size(unit, port, min_quantum) : 0;

    burst_max = (max_quantum > 0) ?
        _bcm_td_default_burst_size(unit, port, max_quantum) : 0;

        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_bucket_set(unit, port, cosq, min_quantum,
                                      max_quantum, burst_min, burst_max,
                                      flags));

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_port_bandwidth_get
 * Purpose:
 *     Get COS queue bandwidth control configuration
 * Parameters:
 *     unit   - (IN) unit number
 *     port   - (IN) port number
 *     cosq   - (IN) COS queue number
 *     min_quantum   - (OUT) minimum bandwidth, kbits/sec
 *     max_quantum   - (OUT) maximum bandwidth, kbits/sec
 *     burst_quantum - (OUT) burst size, kbits/sec
 *     flags  - (OUT) BCM_COSQ_BW_XXX
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_port_bandwidth_get(int unit, bcm_port_t port,
                                 bcm_cos_queue_t cosq, uint32 *min_quantum,
                                 uint32 *max_quantum, uint32 *burst_quantum,
                                 uint32 *flags)
{
    uint32 kbits_burst_min;

    if (cosq < -1) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_SET(port) &&
        ((BCM_GPORT_IS_SCHEDULER(port)) ||
        BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
        BCM_GPORT_IS_MCAST_QUEUE_GROUP(port) ||
        BCM_GPORT_IS_UCAST_SUBSCRIBER_QUEUE_GROUP(port))) {
        return BCM_E_UNAVAIL;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_bucket_get(unit, port, cosq, min_quantum,
                                  max_quantum, &kbits_burst_min,
                                  burst_quantum, flags));

    return BCM_E_NONE;
}


/*
 * Function:
 *     bcm_hx5_cosq_port_pps_set
 * Purpose:
 *     Set the RX per-Cos rate limiting value
 * Parameters:
 *     unit     - (IN) unit number
 *     port     - (IN) queue group GPORT identifier
 *     cosq     - (IN) CoS to configure
 *     pps      - (IN) Rate in packets/second
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_port_pps_set(int unit, bcm_port_t port, bcm_cos_queue_t cosq,
        int pps)
{
    uint32 min, max, burst, burst_min, flags;
    bcm_port_t  local_port =  port;

    if (!IS_CPU_PORT(unit, port)) {
        return BCM_E_PORT;
    } else if (cosq < 0 || cosq >= NUM_CPU_COSQ(unit)) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_SET(port) &&
            ((BCM_GPORT_IS_SCHEDULER(port)) ||
             BCM_GPORT_IS_MCAST_QUEUE_GROUP(port))) { 
        return BCM_E_UNAVAIL;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_bucket_get(unit, port, cosq, &min, &max, &burst_min,
                                  &burst, &flags));

    min = pps;
    burst_min = (min > 0) ?
        _bcm_td_default_burst_size(unit, local_port, min) : 0;
    burst = burst_min;

    return _bcm_hx5_cosq_bucket_set(unit, port, cosq, min, pps, burst_min,
            burst, flags | BCM_COSQ_BW_PACKET_MODE);
}

/*
 * Function:
 *     bcm_hx5_cosq_port_pps_get
 * Purpose:
 *     Get the RX per-Cos rate limiting value
 * Parameters:
 *     unit     - (IN) unit number
 *     port     - (IN) queue group GPORT identifier
 *     cosq     - (IN) COS queue number
 *     pps      - (OUT) Rate in packets/second
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_port_pps_get(int unit, bcm_port_t port, bcm_cos_queue_t cosq,
        int *pps)
{
    uint32 min, max, burst, flags;

    if (!IS_CPU_PORT(unit, port)) {
        return BCM_E_PORT;
    } else if (cosq < 0 || cosq >= NUM_CPU_COSQ(unit)) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_SET(port) &&
            ((BCM_GPORT_IS_SCHEDULER(port)) ||
             BCM_GPORT_IS_MCAST_QUEUE_GROUP(port))) {
        return BCM_E_UNAVAIL;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_bucket_get(unit, port, cosq, &min, &max, &burst, &burst,
                                  &flags));

    *pps = max;

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_port_burst_set
 * Purpose:
 *     Set the per-Cos burst setting
 * Parameters:
 *     unit     - (IN) unit number
 *     port     - (IN) queue group GPORT identifier
 *     cosq     - (IN) CoS to configure
 *     burst    - (IN) Burst rate for the system in packets
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_port_burst_set(int unit, bcm_port_t port, bcm_cos_queue_t cosq,
        int burst)
{
    uint32 min, max, cur_burst, flags;

    if (!IS_CPU_PORT(unit, port)) {
        return BCM_E_PORT;
    } else if (cosq < 0 || cosq >= NUM_CPU_COSQ(unit)) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_SET(port) &&
            ((BCM_GPORT_IS_SCHEDULER(port)) ||
             BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
             BCM_GPORT_IS_MCAST_QUEUE_GROUP(port) ||
             BCM_GPORT_IS_UCAST_SUBSCRIBER_QUEUE_GROUP(port))) {
        return BCM_E_UNAVAIL;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_bucket_get(unit, port, cosq, &min, &max, &cur_burst,
                                  &cur_burst, &flags));

    /* Replace the current BURST setting, keep PPS the same */
    return _bcm_hx5_cosq_bucket_set(unit, port, cosq, min, max, burst, burst,
            flags | BCM_COSQ_BW_PACKET_MODE);
}

/*
 * Function:
 *     bcm_hx5_cosq_port_burst_set
 * Purpose:
 *     Get the per-Cos burst setting
 * Parameters:
 *     unit     - (IN) unit number
 *     port     - (IN) queue group GPORT identifier
 *     cosq     - (IN) CoS queue number
 *     burst    - (OUT) Burst rate for the system in packets
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_port_burst_get(int unit, bcm_port_t port, bcm_cos_queue_t cosq,
        int *burst)
{
    uint32 min, max, cur_burst, cur_burst_min, flags;

    if (!IS_CPU_PORT(unit, port)) {
        return BCM_E_PORT;
    } else if (cosq < 0 || cosq >= NUM_CPU_COSQ(unit)) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_SET(port) &&
            ((BCM_GPORT_IS_SCHEDULER(port)) ||
             BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
             BCM_GPORT_IS_MCAST_QUEUE_GROUP(port) ||
             BCM_GPORT_IS_UCAST_SUBSCRIBER_QUEUE_GROUP(port))) {
        return BCM_E_UNAVAIL;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_bucket_get(unit, port, cosq, &min, &max,
                                  &cur_burst_min, &cur_burst, &flags));

    *burst = cur_burst;

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_obmhighwatermark_set(int unit, bcm_port_t port, uint64 value)
{
    int pipe = 0, obm_id, lane;
    soc_reg_t reg;
    uint64 rval64;
    soc_reg_t obm_high_watermark_reg[] = {
        /* PM4x10Q */
        IDB_OBM0_Q_MAX_USAGEr, IDB_OBM1_Q_MAX_USAGEr, IDB_OBM2_Q_MAX_USAGEr,
        /* PM4x10 */
        IDB_OBM0_MAX_USAGEr, IDB_OBM1_MAX_USAGEr, IDB_OBM2_MAX_USAGEr, IDB_OBM3_MAX_USAGEr,
        /* PM4x25 */
        IDB_OBM0_48_MAX_USAGEr, IDB_OBM1_48_MAX_USAGEr, IDB_OBM2_48_MAX_USAGEr,
    };


    soc_field_t obm_high_watermark_fields[] = {
        PORT0_MAX_USAGEf, PORT1_MAX_USAGEf,
        PORT2_MAX_USAGEf, PORT3_MAX_USAGEf
    };

    SOC_IF_ERROR_RETURN
        (soc_helix5_port_obm_info_get(unit, port, &obm_id, &lane));
    if (obm_id >= _HX5_OBMS_PER_PIPE ||
        (lane < 0 || lane >= _HX5_PORTS_PER_PBLK)) {
        return BCM_E_PARAM;
    }
    if(!COMPILER_64_IS_ZERO(value)) {
        return BCM_E_PARAM;
    }

    reg = SOC_REG_UNIQUE_ACC(unit, obm_high_watermark_reg[obm_id])[pipe];
    COMPILER_64_ZERO(rval64);
    BCM_IF_ERROR_RETURN
            (soc_reg64_get(unit, reg, REG_PORT_ANY, 0, &rval64));

    soc_reg64_field32_set(unit, reg, &rval64, obm_high_watermark_fields[lane], 0);
    BCM_IF_ERROR_RETURN
            (soc_reg64_set(unit, reg, REG_PORT_ANY, 0, rval64));
    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_obmhighwatermark_get(int unit, bcm_port_t port, uint64 *value)
{
    int pipe = 0, obm_id, lane;
    soc_reg_t reg;
    uint64 rval64;
    soc_reg_t obm_high_watermark_reg[] = {
        /* PM4x10Q */
        IDB_OBM0_Q_MAX_USAGEr, IDB_OBM1_Q_MAX_USAGEr, IDB_OBM2_Q_MAX_USAGEr,
        /* PM4x10 */
        IDB_OBM0_MAX_USAGEr, IDB_OBM1_MAX_USAGEr, IDB_OBM2_MAX_USAGEr, IDB_OBM3_MAX_USAGEr,
        /* PM4x25 */
        IDB_OBM0_48_MAX_USAGEr, IDB_OBM1_48_MAX_USAGEr, IDB_OBM2_48_MAX_USAGEr,
    };

    soc_field_t obm_high_watermark_fields[] = {
        PORT0_MAX_USAGEf, PORT1_MAX_USAGEf,
        PORT2_MAX_USAGEf, PORT3_MAX_USAGEf
    };

    SOC_IF_ERROR_RETURN
        (soc_helix5_port_obm_info_get(unit, port, &obm_id, &lane));
    if (obm_id >= _HX5_OBMS_PER_PIPE ||
        (lane < 0 || lane >= _HX5_PORTS_PER_PBLK)) {
        return BCM_E_PARAM;
    }

    reg = SOC_REG_UNIQUE_ACC(unit, obm_high_watermark_reg[obm_id])[pipe];
    COMPILER_64_ZERO(rval64);
    BCM_IF_ERROR_RETURN
            (soc_reg64_get(unit, reg, REG_PORT_ANY, 0, &rval64));

    *value = soc_reg64_field_get(unit, reg, rval64, obm_high_watermark_fields[lane]);
    COMPILER_64_UMUL_32(*value, 16);    /* 16B cell granularity. */

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_obm_buf_use_cnt_set(int unit, bcm_port_t port, uint64 value)
{
    int pipe = 0, obm_id, lane;
    soc_reg_t reg;
    soc_field_t fld;
    uint64 rval64;
    soc_info_t *si;
    soc_reg_t obm_usage_reg[] = {
        /* PM4x10Q */
        IDB_OBM0_Q_USAGEr, IDB_OBM1_Q_USAGEr, IDB_OBM2_Q_USAGEr,
        /* PM4x10 */
        IDB_OBM0_USAGEr, IDB_OBM1_USAGEr, IDB_OBM2_USAGEr, IDB_OBM3_USAGEr,
        /* PM4x25 */
        IDB_OBM0_48_USAGEr, IDB_OBM1_48_USAGEr, IDB_OBM2_48_USAGEr,
    };

    SOC_IF_ERROR_RETURN
            (soc_helix5_port_obm_info_get(unit, port, &obm_id, &lane));
    if (obm_id >= _HX5_OBMS_PER_PIPE || (lane < 0 || lane >= _HX5_PORTS_PER_PBLK)) {
        return BCM_E_PARAM;
    }
    if(!COMPILER_64_IS_ZERO(value)) {
        return BCM_E_PARAM;
    }
    si = &SOC_INFO(unit);

    reg = SOC_REG_UNIQUE_ACC(unit, obm_usage_reg[obm_id])[pipe];
    fld = si->mmu_lossless ? LOSSLESS0_COUNTf : LOSSY_COUNTf;
    COMPILER_64_ZERO(rval64);
    BCM_IF_ERROR_RETURN
            (soc_reg64_get(unit, reg, REG_PORT_ANY, lane, &rval64));

    soc_reg64_field_set(unit, reg, &rval64, fld, value);
    BCM_IF_ERROR_RETURN
            (soc_reg64_set(unit, reg, REG_PORT_ANY, lane, rval64));
    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_obm_buf_use_cnt_get(int unit, bcm_port_t port, uint64 *value)
{
    int pipe = 0, obm_id, lane;
    soc_reg_t reg;
    soc_field_t fld;
    uint64 rval64;
    soc_info_t *si;
    soc_reg_t obm_usage_reg[] = {
        /* PM4x10Q */
        IDB_OBM0_Q_USAGEr, IDB_OBM1_Q_USAGEr, IDB_OBM2_Q_USAGEr,
        /* PM4x10 */
        IDB_OBM0_USAGEr, IDB_OBM1_USAGEr, IDB_OBM2_USAGEr, IDB_OBM3_USAGEr,
        /* PM4x25 */
        IDB_OBM0_48_USAGEr, IDB_OBM1_48_USAGEr, IDB_OBM2_48_USAGEr,
    };

    SOC_IF_ERROR_RETURN
            (soc_helix5_port_obm_info_get(unit, port, &obm_id, &lane));
    if (obm_id >= _HX5_OBMS_PER_PIPE || (lane < 0 || lane >= _HX5_PORTS_PER_PBLK)) {
        return BCM_E_PARAM;
    }
    si = &SOC_INFO(unit);

    reg = SOC_REG_UNIQUE_ACC(unit, obm_usage_reg[obm_id])[pipe];
    fld = si->mmu_lossless ? LOSSLESS0_COUNTf : LOSSY_COUNTf;
    COMPILER_64_ZERO(rval64);
    BCM_IF_ERROR_RETURN
            (soc_reg64_get(unit, reg, REG_PORT_ANY, lane, &rval64));

    *value = soc_reg64_field_get(unit, reg, rval64, fld);
    COMPILER_64_UMUL_32(*value, 16);    /* 16B cell granularity. */

    return BCM_E_NONE;
}

/*
 * Function:
 *      bcm_hx5_cosq_stat_set
 * Purpose:
 *      Set MMU statistics on a per port per cosq basis.
 * Parameters:
 *      unit  - (IN) Unit number.
 *      port  - (IN) GPORT ID
 *      cosq  - (IN) COS queue.
 *      stat  - (IN) Statistic to be set.
 *      value - (IN) Statistic value to be set.
 * Returns:
 *      BCM_E_xxx
 * Notes:
 */
int
bcm_hx5_cosq_stat_set(int unit, bcm_gport_t port, bcm_cos_queue_t cosq,
                     bcm_cosq_stat_t stat, uint64 value)
{
    soc_ctr_control_info_t ctrl_info;
    soc_reg_t ctr_reg, ctr_reg_uc, ctr_reg_mc;
    _bcm_hx5_cosq_index_style_t style = _BCM_HX5_COSQ_INDEX_STYLE_COUNT;
    int startq = 0, ci, from_cos, to_cos;
    int cpu_mc_base = 0;
    bcm_port_t local_port = -1;
    soc_info_t *si = &SOC_INFO(unit);
    cpu_mc_base = si->port_cosq_base[CMIC_PORT(unit)];
    ctrl_info.instance = -1;
    ctrl_info.instance_type = SOC_CTR_INSTANCE_TYPE_XPE;

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));
    if ((cosq < -1) || (cosq >= si->port_num_cosq[local_port])) {
        return BCM_E_PARAM;
    }

    switch (stat) {
        case bcmCosqStatDroppedPackets:
        case bcmCosqStatDroppedBytes:
        case bcmCosqStatOutPackets:
        case bcmCosqStatOutBytes:
            style = _BCM_HX5_COSQ_INDEX_STYLE_COS;
            if (stat == bcmCosqStatDroppedBytes) {
                ctr_reg_uc = SOC_COUNTER_NON_DMA_COSQ_DROP_BYTE_UC;
                ctr_reg_mc = SOC_COUNTER_NON_DMA_COSQ_DROP_BYTE;
            } else if (stat == bcmCosqStatDroppedPackets) {
                ctr_reg_uc = SOC_COUNTER_NON_DMA_COSQ_DROP_PKT_UC;
                ctr_reg_mc = SOC_COUNTER_NON_DMA_COSQ_DROP_PKT;
            } else if (stat == bcmCosqStatOutBytes) {
                ctr_reg_uc = SOC_COUNTER_NON_DMA_EGR_PERQ_XMT_BYTE_UC;
                ctr_reg_mc = SOC_COUNTER_NON_DMA_EGR_PERQ_XMT_BYTE;
                ctrl_info.instance_type = SOC_CTR_INSTANCE_TYPE_PORT;
            } else { /* (stat == bcmCosqStatOutPackets) */
                ctr_reg_uc = SOC_COUNTER_NON_DMA_EGR_PERQ_XMT_PKT_UC;
                ctr_reg_mc = SOC_COUNTER_NON_DMA_EGR_PERQ_XMT_PKT;
                ctrl_info.instance_type = SOC_CTR_INSTANCE_TYPE_PORT;
            }
            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port)) {
                if (ctr_reg_uc != INVALIDr) {
                    BCM_IF_ERROR_RETURN
                        (_bcm_hx5_cosq_index_resolve
                         (unit, port, cosq, style, &local_port, &startq, NULL));

                    ctrl_info.instance = local_port;
                    startq = startq - si->port_uc_cosq_base[local_port];
                    BCM_IF_ERROR_RETURN
                        (soc_counter_generic_set(unit, ctr_reg_uc, ctrl_info, 0,
                                                 startq, value));
                }
            } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                if (ctr_reg_mc != INVALIDr) {
                    BCM_IF_ERROR_RETURN
                        (_bcm_hx5_cosq_index_resolve
                         (unit, port, cosq, style, &local_port, &startq, NULL));

                    ctrl_info.instance = local_port;
                    if(IS_CPU_PORT(unit, local_port)) {
                        startq = (cpu_mc_base + startq) - si->port_cosq_base[local_port];
                    } else {
                        startq = startq - si->port_cosq_base[local_port];
                    }
                    BCM_IF_ERROR_RETURN
                        (soc_counter_generic_set(unit, ctr_reg_mc, ctrl_info, 0,
                                                 startq, value));
                }
            } else {
                if (BCM_GPORT_IS_SCHEDULER(port)) {
                    BCM_IF_ERROR_RETURN
                        (_bcm_hx5_cosq_index_resolve
                         (unit, port, cosq, style, &local_port, &startq, NULL));
                    from_cos = to_cos = startq;
                } else {
                    BCM_IF_ERROR_RETURN
                        (_bcm_hx5_cosq_localport_resolve(unit, port,
                                                        &local_port));

                    if (cosq == BCM_COS_INVALID) {
                        /* if (cosq == -1) set value for the first cosq */
                        cosq = 0;
                    }
                    from_cos = to_cos = cosq;
                }
                ctrl_info.instance = local_port;
                for (ci = from_cos; ci <= to_cos; ci++) {
                    if (!IS_CPU_PORT(unit, local_port)) {
                        if (ctr_reg_uc != INVALIDr) {
                            /* Set UC values if NOT CPU port */
                            BCM_IF_ERROR_RETURN
                                (soc_counter_generic_set(unit, ctr_reg_uc,
                                                         ctrl_info, 0,
                                                         ci, value));
                        }
                    }

                    if (ctr_reg_mc != INVALIDr) {
                        BCM_IF_ERROR_RETURN
                            (soc_counter_generic_set(unit, ctr_reg_mc,
                                                     ctrl_info, 0, ci, value));
                    }
                }
            }
            break;
        case bcmCosqStatYellowCongestionDroppedPackets:
        case bcmCosqStatRedCongestionDroppedPackets:
        case bcmCosqStatGreenDiscardDroppedPackets:
        case bcmCosqStatYellowDiscardDroppedPackets:
        case bcmCosqStatRedDiscardDroppedPackets:
            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
                BCM_GPORT_IS_SCHEDULER(port) ||
                BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                return BCM_E_PARAM;
            }
            if (cosq != BCM_COS_INVALID) {
                return BCM_E_UNAVAIL;
            }
            if (stat == bcmCosqStatYellowCongestionDroppedPackets) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_PKT_YELLOW;
            } else if (stat == bcmCosqStatRedCongestionDroppedPackets) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_PKT_RED;
            } else if (stat == bcmCosqStatYellowDiscardDroppedPackets) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_WRED_PKT_YELLOW;
            } else if (stat == bcmCosqStatRedDiscardDroppedPackets) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_WRED_PKT_RED;
            } else {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_WRED_PKT_GREEN;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));

            ctrl_info.instance = local_port;
            BCM_IF_ERROR_RETURN
                (soc_counter_generic_set(unit, ctr_reg, ctrl_info, 0,
                                         startq, value));
            break;
        case bcmCosqStatHighPriDroppedPackets:
        case bcmCosqStatOBMLossyHighPriDroppedPackets:
        case bcmCosqStatLowPriDroppedPackets:
        case bcmCosqStatOBMLossyLowPriDroppedPackets:
        case bcmCosqStatHighPriDroppedBytes:
        case bcmCosqStatOBMLossyHighPriDroppedBytes:
        case bcmCosqStatLowPriDroppedBytes:
        case bcmCosqStatOBMLossyLowPriDroppedBytes:
        case bcmCosqStatOBMLossless0DroppedPackets:
        case bcmCosqStatOBMLossless1DroppedPackets:
        case bcmCosqStatOBMLossless0DroppedBytes:
        case bcmCosqStatOBMLossless1DroppedBytes:
        case bcmCosqStatOBMFlowControlEvents:
            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
                BCM_GPORT_IS_SCHEDULER(port) ||
                BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                return BCM_E_PARAM;
            }
            if ((stat == bcmCosqStatHighPriDroppedPackets) ||
                (stat == bcmCosqStatOBMLossyHighPriDroppedPackets)) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_PKT_OBM_LOSSY_HI;
            } else if ((stat == bcmCosqStatLowPriDroppedPackets) ||
                       (stat == bcmCosqStatOBMLossyLowPriDroppedPackets)) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_PKT_OBM_LOSSY_LO;
            } else if ((stat == bcmCosqStatHighPriDroppedBytes) ||
                       (stat == bcmCosqStatOBMLossyHighPriDroppedBytes)) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_BYTE_OBM_LOSSY_HI;
            } else if ((stat == bcmCosqStatLowPriDroppedBytes) ||
                       (stat == bcmCosqStatOBMLossyLowPriDroppedBytes)) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_BYTE_OBM_LOSSY_LO;
            } else if (stat == bcmCosqStatOBMLossless0DroppedPackets) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_PKT_OBM_LOSSLESS0;
            } else if (stat == bcmCosqStatOBMLossless1DroppedPackets) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_PKT_OBM_LOSSLESS1;
            } else if (stat == bcmCosqStatOBMLossless0DroppedBytes) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_BYTE_OBM_LOSSLESS0;
            } else if (stat == bcmCosqStatOBMLossless1DroppedBytes) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_BYTE_OBM_LOSSLESS1;
            } else { /* (stat == bcmCosqStatOBMFlowControlEvents) */
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_OBM_FC_EVENTS;
            }
            ctrl_info.instance_type = SOC_CTR_INSTANCE_TYPE_PORT;
            ctrl_info.instance = local_port;
            BCM_IF_ERROR_RETURN
                (soc_counter_generic_set(unit, ctr_reg, ctrl_info, 0,
                                         0, value));
            break;
        case bcmCosqStatOBMHighWatermark:
        case bcmCosqStatOBMBufferBytes:
            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
                BCM_GPORT_IS_SCHEDULER(port) ||
                BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                return BCM_E_PARAM;
            }
            if (stat == bcmCosqStatOBMHighWatermark) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_obmhighwatermark_set(unit, local_port, value));
            } else { /* stat == bcmCosqStatOBMBufferBytes */
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_obm_buf_use_cnt_set(unit, local_port, value));
            }
            break;
        default:
            return BCM_E_PARAM;
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *      bcm_hx5_cosq_stat_get
 * Purpose:
 *      Get MMU statistics on a per port per cosq basis.
 * Parameters:
 *      unit      - (IN) Unit number.
 *      port      - (IN) GPORT ID.
 *      cosq      - (IN) COS queue.
 *      stat      - (IN) Statistic to be retrieved.
 *      sync_mode - (IN) whether to sync before read.
 *      value     - (OUT) Returned statistic value.
 * Returns:
 *      BCM_E_xxx
 * Notes:
 */
int
bcm_hx5_cosq_stat_get(int unit, bcm_gport_t port, bcm_cos_queue_t cosq,
                      bcm_cosq_stat_t stat, int sync_mode, uint64 *value)
{
    soc_ctr_control_info_t ctrl_info;
    soc_reg_t ctr_reg, ctr_reg_uc, ctr_reg_mc;
    soc_mem_t base_mem = INVALIDm, mem = INVALIDm;
    soc_field_t field = INVALIDf;
    uint32 entry[SOC_MAX_MEM_WORDS] = {0};
    uint32 rval, value32 = 0;
    _bcm_hx5_cosq_index_style_t style = _BCM_HX5_COSQ_INDEX_STYLE_COUNT;
    uint64 sum, value64;
    int startq = 0, ci, from_cos, to_cos, i, start_hw_index, end_hw_index;
    int cpu_mc_base = 0, pool, mem_idx;
    bcm_port_t local_port = -1;
    int sync = sync_mode ? SOC_COUNTER_SYNC_ENABLE : 0;
    soc_info_t *si = &SOC_INFO(unit);
    cpu_mc_base = si->port_cosq_base[CMIC_PORT(unit)];

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));
    ctrl_info.instance = -1;
    ctrl_info.instance_type = SOC_CTR_INSTANCE_TYPE_XPE;

    switch (stat) {
        case bcmCosqStatDroppedPackets:
        case bcmCosqStatDroppedBytes:
        case bcmCosqStatOutPackets:
        case bcmCosqStatOutBytes:
        case bcmCosqStatEgressMCQueueBytesPeak:
        case bcmCosqStatEgressMCQueueBytesCurrent:
        case bcmCosqStatEgressMCQueueMinBytesCurrent:
        case bcmCosqStatEgressUCQueueBytesPeak:
        case bcmCosqStatEgressUCQueueBytesCurrent:
        case bcmCosqStatEgressUCQueueMinBytesCurrent:
            if ((cosq < -1) || (cosq >=  si->port_num_cosq[local_port])) {
                return BCM_E_PARAM;
            }
            style = _BCM_HX5_COSQ_INDEX_STYLE_COS;
            if (stat == bcmCosqStatEgressMCQueueBytesPeak) {
                if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
                    BCM_GPORT_IS_SCHEDULER(port)) {
                    return BCM_E_PARAM;
                }
                ctr_reg_uc = INVALIDr;
                ctr_reg_mc = SOC_COUNTER_NON_DMA_QUEUE_PEAK;
            } else if (stat == bcmCosqStatEgressMCQueueBytesCurrent) {
                if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
                    BCM_GPORT_IS_SCHEDULER(port)) {
                    return BCM_E_PARAM;
                }
                ctr_reg_uc = INVALIDr;
                ctr_reg_mc = SOC_COUNTER_NON_DMA_QUEUE_CURRENT;
            } else if (stat == bcmCosqStatEgressMCQueueMinBytesCurrent) {
                if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
                    BCM_GPORT_IS_SCHEDULER(port)) {
                    return BCM_E_PARAM;
                }
                if (!BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                    BCM_IF_ERROR_RETURN
                        (_bcm_hx5_cosq_index_resolve(unit, port, cosq, style,
                                                     &local_port, &startq, NULL));
                    if (IS_CPU_PORT(unit, local_port)) {
                        startq = (cpu_mc_base + startq) - si->port_cosq_base[local_port];
                    } else {
                        startq = startq - si->port_cosq_base[local_port];
                    }
                }
                ctr_reg_uc = INVALIDr;
                ctr_reg_mc = INVALIDr;
                base_mem = MMU_THDM_DB_QUEUE_COUNTm;
                field = MIN_COUNTf;
            } else if (stat == bcmCosqStatEgressUCQueueBytesPeak) {
                if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(port) ||
                    BCM_GPORT_IS_SCHEDULER(port)) {
                    return BCM_E_PARAM;
                }
                if (!BCM_GPORT_IS_UCAST_QUEUE_GROUP(port)) {
                    BCM_IF_ERROR_RETURN
                        (_bcm_hx5_cosq_localport_resolve(unit, port,
                                                         &local_port));
                    if (IS_CPU_PORT(unit, local_port))
                    {
                        return BCM_E_PARAM;
                    }
                }
                ctr_reg_uc = SOC_COUNTER_NON_DMA_UC_QUEUE_PEAK;
                ctr_reg_mc = INVALIDr;
            } else if (stat == bcmCosqStatEgressUCQueueBytesCurrent) {
                if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(port) ||
                    BCM_GPORT_IS_SCHEDULER(port)) {
                    return BCM_E_PARAM;
                }
                if (!BCM_GPORT_IS_UCAST_QUEUE_GROUP(port)) {
                    BCM_IF_ERROR_RETURN
                        (_bcm_hx5_cosq_localport_resolve(unit, port,
                                                         &local_port));
                    if (IS_CPU_PORT(unit, local_port))
                    {
                        return BCM_E_PARAM;
                    }
                }
                ctr_reg_uc = SOC_COUNTER_NON_DMA_UC_QUEUE_CURRENT;
                ctr_reg_mc = INVALIDr;
            } else if (stat == bcmCosqStatEgressUCQueueMinBytesCurrent) {
                if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(port) ||
                    BCM_GPORT_IS_SCHEDULER(port)) {
                    return BCM_E_PARAM;
                }
                if (!BCM_GPORT_IS_UCAST_QUEUE_GROUP(port)) {
                    BCM_IF_ERROR_RETURN
                        (_bcm_hx5_cosq_localport_resolve(unit, port,
                                                         &local_port));
                    if (IS_CPU_PORT(unit, local_port))
                    {
                        return BCM_E_PARAM;
                    }
                    BCM_IF_ERROR_RETURN
                        (_bcm_hx5_cosq_index_resolve(unit, port, cosq, style,
                                                     &local_port, &startq, NULL));

                    startq = startq - si->port_uc_cosq_base[local_port];
                }
                ctr_reg_uc = INVALIDr;
                ctr_reg_mc = INVALIDr;
                base_mem = MMU_THDU_COUNTER_QUEUEm;
                field = MIN_COUNTf;
            } else if (stat == bcmCosqStatDroppedBytes) {
                ctr_reg_uc = SOC_COUNTER_NON_DMA_COSQ_DROP_BYTE_UC;
                ctr_reg_mc = SOC_COUNTER_NON_DMA_COSQ_DROP_BYTE;
            } else if (stat == bcmCosqStatDroppedPackets) {
                ctr_reg_uc = SOC_COUNTER_NON_DMA_COSQ_DROP_PKT_UC;
                ctr_reg_mc = SOC_COUNTER_NON_DMA_COSQ_DROP_PKT;
            } else if (stat == bcmCosqStatOutBytes) {
                ctr_reg_uc = SOC_COUNTER_NON_DMA_EGR_PERQ_XMT_BYTE_UC;
                ctr_reg_mc = SOC_COUNTER_NON_DMA_EGR_PERQ_XMT_BYTE;
                ctrl_info.instance_type = SOC_CTR_INSTANCE_TYPE_PORT;
            } else { /* (stat == bcmCosqStatOutPackets) */
                ctr_reg_uc = SOC_COUNTER_NON_DMA_EGR_PERQ_XMT_PKT_UC;
                ctr_reg_mc = SOC_COUNTER_NON_DMA_EGR_PERQ_XMT_PKT;
                ctrl_info.instance_type = SOC_CTR_INSTANCE_TYPE_PORT;
            }
            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port)) {
                if ((ctr_reg_uc != INVALIDr) || (base_mem != INVALIDm)) {
                    BCM_IF_ERROR_RETURN
                        (_bcm_hx5_cosq_index_resolve(unit, port, cosq, style,
                                                     &local_port, &startq, NULL));

                    startq = startq - si->port_uc_cosq_base[local_port];
                    ctrl_info.instance = local_port;
                    if (ctr_reg_uc != INVALIDr) {
                        BCM_IF_ERROR_RETURN
                            (soc_counter_generic_get(unit, ctr_reg_uc, ctrl_info,
                                                    sync, startq, value));
                    } else {
                        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[0];
                        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL,
                                            startq, entry));
                        value32 = soc_mem_field32_get(unit, mem, entry, field);
                        COMPILER_64_ADD_32(*value, value32);
                        COMPILER_64_UMUL_32(*value, _HX5_MMU_BYTES_PER_CELL);
                    }
                }
            } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                if ((ctr_reg_mc != INVALIDr) || (base_mem != INVALIDm)) {
                    BCM_IF_ERROR_RETURN
                        (_bcm_hx5_cosq_index_resolve(unit, port, cosq, style,
                                                     &local_port, &startq, NULL));
                    if (IS_CPU_PORT(unit, local_port)) {
                        startq = (cpu_mc_base + startq) - si->port_cosq_base[local_port];
                    } else {
                        startq = startq - si->port_cosq_base[local_port];
                    }
                    if (ctr_reg_mc != INVALIDr) {
                        ctrl_info.instance = local_port;
                        BCM_IF_ERROR_RETURN
                            (soc_counter_generic_get(unit, ctr_reg_mc, ctrl_info,
                                                     sync, startq, value));
                    } else {
                        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[0];
                        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL,
                                            startq, entry));
                        value32 = soc_mem_field32_get(unit, mem, entry, field);
                        COMPILER_64_ADD_32(*value, value32);
                        COMPILER_64_UMUL_32(*value, _HX5_MMU_BYTES_PER_CELL);
                    }
                }
            } else {
                if (BCM_GPORT_IS_SCHEDULER(port)) {
                    BCM_IF_ERROR_RETURN
                        (_bcm_hx5_cosq_index_resolve(unit, port, cosq, style,
                                                     &local_port, &startq, NULL));
                    from_cos = to_cos = startq;
                } else {
                    BCM_IF_ERROR_RETURN
                        (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));

                    if (cosq == BCM_COS_INVALID) {
                        from_cos = 0;
                        to_cos = (IS_CPU_PORT(unit, local_port)) ? \
                            NUM_CPU_COSQ(unit) - 1 : _BCM_HX5_NUM_COS(unit) - 1;
                    } else {
                        from_cos = to_cos = cosq;
                    }
                }
                COMPILER_64_ZERO(sum);
                ctrl_info.instance = local_port;
                for (ci = from_cos; ci <= to_cos; ci++) {

                    if (!IS_CPU_PORT(unit, local_port)) {
                        /* Get UC values if NOT CPU port */
                        if (ctr_reg_uc != INVALIDr) {
                            BCM_IF_ERROR_RETURN
                                (soc_counter_generic_get(unit, ctr_reg_uc,
                                                         ctrl_info,
                                                         sync, ci, &value64));
                            COMPILER_64_ADD_64(sum, value64);
                        }
                    }

                    if (ctr_reg_mc != INVALIDr) {
                        BCM_IF_ERROR_RETURN
                            (soc_counter_generic_get(unit, ctr_reg_mc,
                                                     ctrl_info,
                                                     sync, ci, &value64));
                        COMPILER_64_ADD_64(sum, value64);
                    }
                    if (base_mem != INVALIDm) {
                        mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[0];
                        BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL,
                                            startq + ci, entry));
                        value32 = soc_mem_field32_get(unit, mem, entry, field) *
                                  _HX5_MMU_BYTES_PER_CELL;
                        COMPILER_64_ADD_32(sum, value32);
                    }
                }
                *value = sum;
            }
            break;
        case bcmCosqStatYellowCongestionDroppedPackets:
        case bcmCosqStatRedCongestionDroppedPackets:
        case bcmCosqStatGreenDiscardDroppedPackets:
        case bcmCosqStatYellowDiscardDroppedPackets:
        case bcmCosqStatRedDiscardDroppedPackets:
            if ((cosq < -1) || (cosq >=  si->port_num_cosq[local_port])) {
                return BCM_E_PARAM;
            }

            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
                BCM_GPORT_IS_SCHEDULER(port) ||
                BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                return BCM_E_PARAM;
            }
            if (cosq != BCM_COS_INVALID) {
                return BCM_E_UNAVAIL;
            }
            if (stat == bcmCosqStatYellowCongestionDroppedPackets) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_PKT_YELLOW;
            } else if (stat == bcmCosqStatRedCongestionDroppedPackets) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_PKT_RED;
            } else if (stat == bcmCosqStatYellowDiscardDroppedPackets) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_WRED_PKT_YELLOW;
            } else if (stat == bcmCosqStatRedDiscardDroppedPackets) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_WRED_PKT_RED;
            } else { /* (stat == bcmCosqStatGreenDiscardDroppedPackets) */
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_WRED_PKT_GREEN;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));

            ctrl_info.instance = local_port;
            BCM_IF_ERROR_RETURN
                (soc_counter_generic_get(unit, ctr_reg, ctrl_info,
                                         sync, startq, value));
            break;
        case bcmCosqStatIngressPortPGMinBytesPeak:
        case bcmCosqStatIngressPortPGMinBytesCurrent:
        case bcmCosqStatIngressPortPGSharedBytesPeak:
        case bcmCosqStatIngressPortPGSharedBytesCurrent:
        case bcmCosqStatIngressPortPGHeadroomBytesPeak:
        case bcmCosqStatIngressPortPGHeadroomBytesCurrent:
            if (cosq < -1) {
                return BCM_E_PARAM;
            }

            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
                BCM_GPORT_IS_SCHEDULER(port) ||
                BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                return BCM_E_PARAM;
            }
            if (stat == bcmCosqStatIngressPortPGMinBytesPeak) {
                ctr_reg = SOC_COUNTER_NON_DMA_PG_MIN_PEAK;
            } else if (stat == bcmCosqStatIngressPortPGMinBytesCurrent) {
                ctr_reg = SOC_COUNTER_NON_DMA_PG_MIN_CURRENT;
            } else if (stat == bcmCosqStatIngressPortPGSharedBytesPeak) {
                ctr_reg = SOC_COUNTER_NON_DMA_PG_SHARED_PEAK;
            } else if (stat == bcmCosqStatIngressPortPGSharedBytesCurrent) {
                ctr_reg = SOC_COUNTER_NON_DMA_PG_SHARED_CURRENT;
            } else if (stat == bcmCosqStatIngressPortPGHeadroomBytesPeak) {
                ctr_reg = SOC_COUNTER_NON_DMA_PG_HDRM_PEAK;
            } else {
                /* (stat == bcmCosqStatIngressPortPGHeadroomBytesCurrent) */
                ctr_reg = SOC_COUNTER_NON_DMA_PG_HDRM_CURRENT;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_ingress_pg_get(unit, port, cosq,
                                             &start_hw_index, &end_hw_index));

            COMPILER_64_ZERO(sum);
            for (i = start_hw_index; i <= end_hw_index; i++) {
                ctrl_info.instance = local_port;
                BCM_IF_ERROR_RETURN
                    (soc_counter_generic_get(unit, ctr_reg, ctrl_info,
                                             sync, i, &value64));
                COMPILER_64_ADD_64(sum, value64);
            }

            COMPILER_64_UMUL_32(sum, _HX5_MMU_BYTES_PER_CELL);
            *value = sum;
            break;
        case bcmCosqStatIngressPortPoolSharedBytesPeak:
            if (cosq < -1) {
                return BCM_E_PARAM;
            }

            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
                BCM_GPORT_IS_SCHEDULER(port) ||
                BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                return BCM_E_PARAM;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_ingress_sp_get_by_pg(unit, port, cosq,
                                             &start_hw_index, &end_hw_index));

            BCM_IF_ERROR_RETURN(
                _bcm_hx5_cosq_localport_resolve(unit, port, &local_port));

            ctrl_info.instance_type = SOC_CTR_INSTANCE_TYPE_XPE;
            ctrl_info.instance = local_port;
            ctr_reg = SOC_COUNTER_NON_DMA_POOL_PEAK;

            COMPILER_64_ZERO(sum);
            for (i = start_hw_index; i <= end_hw_index; i++) {
                BCM_IF_ERROR_RETURN
                    (soc_counter_generic_get(unit, ctr_reg, ctrl_info,
                                             sync, i, &value64));
                COMPILER_64_ADD_64(sum, value64);
            }

            COMPILER_64_UMUL_32(sum, _HX5_MMU_BYTES_PER_CELL);
            *value = sum;
            break;
        case bcmCosqStatIngressPortPoolSharedBytesCurrent:
            if (cosq < -1) {
                return BCM_E_PARAM;
            }

            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
                BCM_GPORT_IS_SCHEDULER(port) ||
                BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                return BCM_E_PARAM;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_ingress_sp_get_by_pg(unit, port, cosq,
                                             &start_hw_index, &end_hw_index));
            BCM_IF_ERROR_RETURN(
                _bcm_hx5_cosq_localport_resolve(unit, port, &local_port));

            ctrl_info.instance_type = SOC_CTR_INSTANCE_TYPE_XPE;
            ctrl_info.instance = local_port;
            ctr_reg = SOC_COUNTER_NON_DMA_POOL_CURRENT;

            COMPILER_64_ZERO(sum);
            for (i = start_hw_index; i <= end_hw_index; i++) {
                BCM_IF_ERROR_RETURN
                    (soc_counter_generic_get(unit, ctr_reg, ctrl_info,
                                             sync, i, &value64));
               COMPILER_64_ADD_64(sum, value64);
            }

            COMPILER_64_UMUL_32(sum, _HX5_MMU_BYTES_PER_CELL);
            *value = sum;
            break;
        case bcmCosqStatHighPriDroppedPackets:
        case bcmCosqStatOBMLossyHighPriDroppedPackets:
        case bcmCosqStatLowPriDroppedPackets:
        case bcmCosqStatOBMLossyLowPriDroppedPackets:
        case bcmCosqStatHighPriDroppedBytes:
        case bcmCosqStatOBMLossyHighPriDroppedBytes:
        case bcmCosqStatLowPriDroppedBytes:
        case bcmCosqStatOBMLossyLowPriDroppedBytes:
        case bcmCosqStatOBMLossless0DroppedPackets:
        case bcmCosqStatOBMLossless1DroppedPackets:
        case bcmCosqStatOBMLossless0DroppedBytes:
        case bcmCosqStatOBMLossless1DroppedBytes:
        case bcmCosqStatOBMFlowControlEvents:
            if ((cosq < -1) || (cosq >=  si->port_num_cosq[local_port])) {
                return BCM_E_PARAM;
            }

            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
                BCM_GPORT_IS_SCHEDULER(port) ||
                BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                return BCM_E_PARAM;
            }
            if ((stat == bcmCosqStatHighPriDroppedPackets) ||
                (stat == bcmCosqStatOBMLossyHighPriDroppedPackets)) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_PKT_OBM_LOSSY_HI;
            } else if ((stat == bcmCosqStatLowPriDroppedPackets) ||
                       (stat == bcmCosqStatOBMLossyLowPriDroppedPackets)) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_PKT_OBM_LOSSY_LO;
            } else if ((stat == bcmCosqStatHighPriDroppedBytes) ||
                       (stat == bcmCosqStatOBMLossyHighPriDroppedBytes)) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_BYTE_OBM_LOSSY_HI;
            } else if ((stat == bcmCosqStatLowPriDroppedBytes) ||
                       (stat == bcmCosqStatOBMLossyLowPriDroppedBytes)) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_BYTE_OBM_LOSSY_LO;
            } else if (stat == bcmCosqStatOBMLossless0DroppedPackets) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_PKT_OBM_LOSSLESS0;
            } else if (stat == bcmCosqStatOBMLossless1DroppedPackets) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_PKT_OBM_LOSSLESS1;
            } else if (stat == bcmCosqStatOBMLossless0DroppedBytes) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_BYTE_OBM_LOSSLESS0;
            } else if (stat == bcmCosqStatOBMLossless1DroppedBytes) {
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_BYTE_OBM_LOSSLESS1;
            } else { /* (stat == bcmCosqStatOBMFlowControlEvents) */
                ctr_reg = SOC_COUNTER_NON_DMA_PORT_OBM_FC_EVENTS;
            }
            ctrl_info.instance_type = SOC_CTR_INSTANCE_TYPE_PORT;
            ctrl_info.instance = local_port;
            BCM_IF_ERROR_RETURN
                (soc_counter_generic_get(unit, ctr_reg, ctrl_info, 0,
                                         0, value));
            break;
        case bcmCosqStatOBMHighWatermark:
        case bcmCosqStatOBMBufferBytes:
            if ((cosq < -1) || (cosq >=  si->port_num_cosq[local_port])) {
                return BCM_E_PARAM;
            }

            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
                BCM_GPORT_IS_SCHEDULER(port) ||
                BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                return BCM_E_PARAM;
            }
            if (stat == bcmCosqStatOBMHighWatermark) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_obmhighwatermark_get(unit, local_port, value));
            } else { /* stat == bcmCosqStatOBMBufferBytes */
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_obm_buf_use_cnt_get(unit, local_port, value));
            }
            break;
        case bcmCosqStatEgressUCQueuePortBytesCurrent:
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, port, cosq,
                                             _BCM_HX5_COSQ_INDEX_STYLE_EGR_POOL,
                                             &local_port, &pool, NULL));
            base_mem = MMU_THDU_COUNTER_PORTm;
            mem = SOC_MEM_UNIQUE_ACC_XPE_PIPE(unit, base_mem, 0, 0);
            mem_idx = SOC_TD3_MMU_PIPED_MEM_INDEX(unit, local_port, base_mem, pool);
            BCM_IF_ERROR_RETURN
                (soc_mem_read(unit, mem, MEM_BLOCK_ALL, mem_idx, entry));
            value32 = soc_mem_field32_get(unit, mem, entry, SHARED_COUNTf);

            COMPILER_64_ADD_32(*value, value32);
            COMPILER_64_UMUL_32(*value, _HX5_MMU_BYTES_PER_CELL);
            break;
        case bcmCosqStatEgressPortPoolTotalBytesCurrent:
            if (cosq != BCM_COS_INVALID) {
                return BCM_E_UNAVAIL;
            }
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));
            BCM_IF_ERROR_RETURN
                (soc_reg32_get(unit, MMU_THDM_DB_PORT_TOTAL_COUNTr,
                               local_port, 0, &rval));
            value32 = soc_reg_field_get(unit, MMU_THDM_DB_PORT_TOTAL_COUNTr,
                                        rval, COUNTf);
            COMPILER_64_ADD_32(*value, value32);
            COMPILER_64_UMUL_32(*value, _HX5_MMU_BYTES_PER_CELL);
            break;
        case bcmCosqStatEgressPortPoolSharedBytesCurrent:
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, port, cosq,
                                             _BCM_HX5_COSQ_INDEX_STYLE_EGR_POOL,
                                             &local_port, &pool, NULL));
            BCM_IF_ERROR_RETURN
                (soc_reg32_get(unit, MMU_THDM_DB_PORTSP_SHARED_COUNTr,
                               local_port, pool, &rval));
            value32 = soc_reg_field_get(unit, MMU_THDM_DB_PORTSP_SHARED_COUNTr,
                                        rval, COUNTf);
            COMPILER_64_ADD_32(*value, value32);
            COMPILER_64_UMUL_32(*value, _HX5_MMU_BYTES_PER_CELL);
            break;
        case bcmCosqStatEgressPoolSharedBytesCurrent:
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_index_resolve(unit, port, cosq,
                                             _BCM_HX5_COSQ_INDEX_STYLE_EGR_POOL,
                                             &local_port, &pool, NULL));
            BCM_IF_ERROR_RETURN
                (soc_reg32_get(unit, MMU_THDM_DB_POOL_SHARED_COUNTr,
                               REG_PORT_ANY, pool, &rval));
            value32 = soc_reg_field_get(unit, MMU_THDM_DB_PORTSP_SHARED_COUNTr,
                                        rval, COUNTf);
            COMPILER_64_ADD_32(*value, value32);
            COMPILER_64_UMUL_32(*value, _HX5_MMU_BYTES_PER_CELL);
            break;
        case bcmCosqStatEgressQgroupMinBytesCurrent:
        case bcmCosqStatEgressQgroupBytesCurrent:
            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port)) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_index_resolve(unit, port, cosq,
                                                 _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                                 &local_port, &startq, NULL));
            } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                return BCM_E_PARAM;
            } else {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));
                if (local_port < 0) {
                    return BCM_E_PORT;
                }
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_cosq_index_resolve(unit, local_port, cosq,
                                                 _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                                 NULL, &startq, NULL));
            }
            base_mem = MMU_THDU_Q_TO_QGRP_MAPm;
            mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[0];
            BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, startq, entry));
            if (!soc_mem_field32_get(unit, mem, entry, QGROUP_VALIDf)) {
                LOG_INFO(BSL_LS_BCM_COSQ,
                         (BSL_META_U(unit,
                         "UCQ doesn't associate with a queue group!\n")));
                return BCM_E_UNAVAIL;
            }

            base_mem = MMU_THDU_COUNTER_QGROUPm;
            mem = SOC_MEM_UNIQUE_ACC(unit, base_mem)[0];
            if (stat == bcmCosqStatEgressQgroupMinBytesCurrent) {
                field = MIN_COUNTf;
            } else if (stat == bcmCosqStatEgressQgroupBytesCurrent) {
                field = SHARED_COUNTf;
            }
            mem_idx = _soc_td3_mmu_port(unit, local_port) &  SOC_HX5_MMU_PORT_STRIDE;
            BCM_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, mem_idx, entry));
            value32 = soc_mem_field32_get(unit, mem, entry, field);

            COMPILER_64_ADD_32(*value, value32);
            COMPILER_64_UMUL_32(*value, _HX5_MMU_BYTES_PER_CELL);
            break;
        case bcmCosqStatSourcePortDroppedPackets:
            if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(port) ||
                BCM_GPORT_IS_SCHEDULER(port) ||
                BCM_GPORT_IS_MCAST_QUEUE_GROUP(port)) {
                return BCM_E_PARAM;
            }

            if (cosq != BCM_COS_INVALID) {
                return BCM_E_UNAVAIL;
            }

            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));

            ctrl_info.instance_type = SOC_CTR_INSTANCE_TYPE_XPE;
            ctrl_info.instance = local_port;
            ctr_reg = SOC_COUNTER_NON_DMA_PORT_DROP_PKT_ING;
            BCM_IF_ERROR_RETURN
                (soc_counter_generic_get(unit, ctr_reg, ctrl_info,
                                         sync, startq, value));
            break;
        default:
            return BCM_E_PARAM;
    }

    return BCM_E_NONE;
}


STATIC int
_bcm_hx5_cosq_cpu_tree_create(int unit, bcm_port_t port)
{
    int id, sc_id;
    bcm_gport_t sched_gport[SOC_HX5_NUM_SCHEDULER_PER_CPU_PORT];
    bcm_gport_t cpu_mc_gport[SOC_HX5_NUM_CPU_QUEUES];
    int numq = 1;

    /*Creating all L0,L1 and L2 scheduler nodes for cpu port  */
    for (id = 0; id < SOC_HX5_NUM_SCHEDULER_PER_CPU_PORT; id++) {
        if (id == 1) {
            numq = 10;
        } else if (id >= 2 && id <= 11) {
            numq = 48;
        }

        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_gport_add(unit, port, numq,
                                     BCM_COSQ_GPORT_SCHEDULER,
                                     &sched_gport[id]));
    }

    /* Attaching L0 schedular node to front panel port */
    BCM_IF_ERROR_RETURN
        (bcm_hx5_cosq_gport_attach(unit, sched_gport[0], port, 0));

    /* Attaching L1 schedular node to L0 schedular node  */
    BCM_IF_ERROR_RETURN
        (bcm_hx5_cosq_gport_attach(unit, sched_gport[1],  sched_gport[0], 1));

    /* Attaching L2 schedular node to L1 schedular node  */
    for (sc_id = 2; sc_id < SOC_HX5_NUM_SCHEDULER_PER_CPU_PORT; sc_id++) {
        BCM_IF_ERROR_RETURN
            (bcm_hx5_cosq_gport_attach(unit, sched_gport[sc_id],  sched_gport[1], sc_id));
    }

    numq = 1;
    for (id = 0; id < SOC_HX5_NUM_CPU_QUEUES; id++) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_gport_add(unit, port, numq,
                                     BCM_COSQ_GPORT_MCAST_QUEUE_GROUP,
                                     &cpu_mc_gport[id]));
        /* Attach all the 48 CPU MC queues to L2.0 node */
        BCM_IF_ERROR_RETURN
            (bcm_hx5_cosq_gport_attach(unit, cpu_mc_gport[id],
                                       sched_gport[2], id));
    }

    return BCM_E_NONE;


}

/*
 *  Function:
 *      bcm_hx5_cosq_gport_child_get
 *  Purpose:
 *      Get the child node GPORT atatched to N-th index (cosq)
 *      of the scheduler GPORT.
 *  Parameters:
 *      unit       - (IN)  Unit number.
 *      in_gport   - (IN)  Scheduler GPORT ID.
 *      cosq       - (IN)  COS queue attached to.
 *      out_gport  - (OUT) Child GPORT ID.
 *  Returns:
 *       BCM_E_XXX
 * */

int
bcm_hx5_cosq_gport_child_get(int unit, bcm_gport_t in_gport,
        bcm_cos_queue_t cosq, bcm_gport_t *out_gport)
{
    _bcm_hx5_cosq_node_t *tmp_node = NULL;
    bcm_port_t local_port = -1;
    _bcm_hx5_cosq_cpu_port_info_t *port_info = NULL;
    int index = -1, cpu_mc_base = 0;
    soc_info_t *si = &SOC_INFO(unit);

    if (out_gport == NULL) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, in_gport, &local_port));

    if (!SOC_PORT_VALID(unit, local_port)) {
        return BCM_E_PORT;
    }

    /* This API is only supported for CPU ports because
     *        for all other ports we have fixed hierarchy */
    if (!IS_CPU_PORT(unit, local_port)) {
        return BCM_E_PARAM;
    }
    
    if ((cosq < 0) || (cosq >= NUM_CPU_COSQ(unit))) {
        return BCM_E_PARAM;
    }

    if (_bcm_hx5_cosq_cpu_port_info[unit] == NULL) {
        return BCM_E_INIT;
    }

    port_info = _bcm_hx5_cosq_cpu_port_info[unit];
    cpu_mc_base = si->port_cosq_base[CMIC_PORT(unit)];

    if (BCM_GPORT_IS_SCHEDULER(in_gport)) {
        for (index = 0; index < SOC_HX5_NUM_CPU_QUEUES; index++) {
            if (port_info->mcast[index].parent_gport == in_gport) {
                if (cosq == ((port_info->mcast[index].hw_index - cpu_mc_base) %
                            SOC_HX5_NUM_CPU_QUEUES)) {
                    tmp_node = &port_info->mcast[index];
                    break;
                }
            }
        }
    } else {
        return BCM_E_PARAM;
    }

    if (tmp_node == NULL) {
        return BCM_E_NOT_FOUND;
    }

    *out_gport = tmp_node->gport;

    return BCM_E_NONE;
}

/*
 * Function:
 *      _bcm_hx5_cosq_gport_tree_create
 * Purpose:
 *      During cosq init create the default cosq gport tree.
 *      Schedualar (L0) nodes are created and attach to physical ports.
 *      UC and MC queues are added and attached to each L0 nodes.
 * Parameters:
 *      unit - (IN) unit number.
 *      port - (IN) port number
 * Returns:
 *     BCM_E_XXX
 */
STATIC int
_bcm_hx5_cosq_gport_tree_create(int unit, bcm_port_t port)
{
    int id, sc_id;
    bcm_gport_t sched_gport[SOC_HX5_NUM_SCHEDULER_PER_PORT];
    bcm_gport_t uc_gport[SOC_HX5_NUM_UCAST_QUEUE_PER_PORT];
    bcm_gport_t mc_gport[SOC_HX5_NUM_MCAST_QUEUE_PER_PORT];
    int numq = 1;

    /*Creating all L0,L1 and L2 scheduler nodes */
    for (id = 0; id < SOC_HX5_NUM_SCHEDULER_PER_PORT; id++) {
        if (id == 0 || id >= 3) {
           numq = 2;
        } else if(id > 0 && id < 3) {
           numq = 8;
        }
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_gport_add(unit, port, numq,
                                     BCM_COSQ_GPORT_SCHEDULER,
                                     &sched_gport[id]));
    }

    /* Attaching L0 schedular node to front panel port */
    BCM_IF_ERROR_RETURN
        (bcm_hx5_cosq_gport_attach(unit, sched_gport[0], port, 0));

    /* Attaching L1 schedular nodes to L0 schedular node */
    for(sc_id = 1; sc_id < 3; sc_id++){
        BCM_IF_ERROR_RETURN
            (bcm_hx5_cosq_gport_attach(unit, sched_gport[sc_id], sched_gport[0], sc_id));
    }
    /* Attaching L2 schedular nodes to L1 schedular node */
    for(sc_id = 3; sc_id < SOC_HX5_NUM_SCHEDULER_PER_PORT; sc_id++){
        BCM_IF_ERROR_RETURN
            (bcm_hx5_cosq_gport_attach(unit, sched_gport[sc_id], (sc_id < 11) ? sched_gport[1] : sched_gport[2], sc_id));
    }
    numq = 1;
    /* Creating and attaching l3 uc and l2 mc queues to  l2 Schedular nodes */
    for (id = 0, sc_id = 3; id < SOC_HX5_NUM_UCAST_QUEUE_PER_PORT &&
            sc_id < SOC_HX5_NUM_SCHEDULER_PER_PORT; id++, sc_id++) {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_gport_add(unit, port, numq,
                                     BCM_COSQ_GPORT_UCAST_QUEUE_GROUP,
                                     &uc_gport[id]));
        BCM_IF_ERROR_RETURN
            (bcm_hx5_cosq_gport_attach(unit, uc_gport[id],
                                       sched_gport[sc_id], id));
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_gport_add(unit, port, numq,
                                     BCM_COSQ_GPORT_MCAST_QUEUE_GROUP,
                                     &mc_gport[id]));
        BCM_IF_ERROR_RETURN
            (bcm_hx5_cosq_gport_attach(unit, mc_gport[id],
                                       sched_gport[sc_id], id));
    }
    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_port_pfc_op
 * Purpose:
 *     Set PFC Prio 2 Cos Map and set the profile index for the Port
 * Parameters:
 *     unit     - (IN) unit number
 *     port     - (IN) GPORT identifier
 *     sctype   - (IN) Input Class
 *     op       - (IN) Operation to be performed (ADD|SET|CLEAR)
 *     gport    - (IN) Gport/Cos array
 *     gport_ct - (IN) Count of values in the array
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_port_pfc_op(int unit, bcm_port_t port,
                         bcm_switch_control_t sctype, _bcm_cosq_op_t op,
                         bcm_gport_t *gport, int gport_count)
{
    bcm_port_t local_port;
    int type = -1, class = -1, index, hw_cosq;
    uint32 profile_index, old_profile_index;
    uint32 rval, fval, cos_bmp;
    uint64 rval64[16], *rval64s[1];
    _bcm_hx5_cosq_node_t *node;
    static const soc_reg_t port_fc_reg = PORT_LLFC_CFGr;
    soc_field_t field = INVALIDf;
    soc_info_t *si = &SOC_INFO(unit);
    int rv = SOC_E_NONE;

    if (gport_count < 0) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));
    if (IS_CPU_PORT(unit, local_port)) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN(_bcm_hx5_cosq_pfc_class_resolve(sctype, &type, &class));

    cos_bmp = 0;

    if (type == _BCM_HX5_COSQ_TYPE_MCAST) {
        field = MC_COS_BMPf;
    } else {
        field = UC_COS_BMPf;
    }

    for (index = 0; index < gport_count; index++) {
        hw_cosq = -1;
        if (BCM_GPORT_IS_SET(gport[index]) &&
            ((BCM_GPORT_IS_SCHEDULER(gport[index])) ||
              BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport[index]) ||
              BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport[index]))) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_node_get(unit, gport[index], NULL,
                                        NULL, NULL, &node));
            if (BCM_GPORT_IS_SCHEDULER(gport[index])) {
                hw_cosq = node->hw_index % SOC_HX5_NUM_SCHEDULER_PER_PORT;
            } else if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport[index])) {
                if (type != _BCM_HX5_COSQ_TYPE_UCAST) {
                    return BCM_E_PARAM;
                }
                hw_cosq = node->hw_index - si->port_uc_cosq_base[local_port];

            } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport[index])) {
                if (type != _BCM_HX5_COSQ_TYPE_MCAST) {
                    return BCM_E_PARAM;
                }
                hw_cosq = node->hw_index - si->port_cosq_base[local_port];;
            }
        } else {
            /* Find hardware index for given local_port, cosq */
            hw_cosq = gport[index] % si->port_num_cosq[local_port];
        }
        cos_bmp |= (1 << hw_cosq);
    }

    rval64s[0] = rval64;
    BCM_IF_ERROR_RETURN(soc_reg32_get(unit, port_fc_reg, local_port, 0, &rval));

    if (op == _BCM_COSQ_OP_CLEAR || cos_bmp != 0) {
        old_profile_index = 16 * soc_reg_field_get(unit, port_fc_reg, rval,
                                                   PROFILE_INDEXf);

        BCM_IF_ERROR_RETURN
            (soc_profile_reg_get(unit, _bcm_hx5_prio2cos_profile[unit],
                                 old_profile_index, 16, rval64s));
        if (op == _BCM_COSQ_OP_SET) {
            soc_reg64_field32_set(unit, PRIO2COS_PROFILE_64r, &rval64[class],
                                  field, cos_bmp);
        } else if (op == _BCM_COSQ_OP_CLEAR || cos_bmp != 0) {
            fval = soc_reg64_field32_get(unit, PRIO2COS_PROFILE_64r, rval64[class],
                                         field);
            if (op == _BCM_COSQ_OP_ADD) {
                fval |= cos_bmp;
            } else { /* _BCM_COSQ_OP_CLEAR */
                fval = 0;
            }
            soc_reg64_field32_set(unit, PRIO2COS_PROFILE_64r, &rval64[class],
                                  field, fval);
        }
        BCM_IF_ERROR_RETURN
            (soc_profile_reg_delete(unit, _bcm_hx5_prio2cos_profile[unit],
                                    old_profile_index));
        rv = soc_profile_reg_add(unit, _bcm_hx5_prio2cos_profile[unit], rval64s,
                                 16, &profile_index);
        if (rv != BCM_E_NONE) {
            SOC_IF_ERROR_RETURN
                (soc_profile_reg_reference(unit, _bcm_hx5_prio2cos_profile[unit],
                                           old_profile_index, 16));
            return rv;
        }
        soc_reg_field_set(unit, port_fc_reg, &rval, PROFILE_INDEXf,
                          profile_index / 16);
    }
    BCM_IF_ERROR_RETURN(soc_reg32_set(unit, port_fc_reg, local_port, 0, rval));
    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_port_pfc_get
 * Purpose:
 *     Get PFC Prio2Cos Map for a given Traffic Class
 * Parameters:
 *     unit     - (IN) unit number
 *     port     - (IN) GPORT identifier
 *     sctype   - (IN) Input Traffic Class
 *     gport    - (OUT) Gport/Cos array
 *     gport_ct - (IN) Input Count of gport required
 *     actual_gport_ct - (OUT) Actual Count of gport/cos in the array
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_port_pfc_get(int unit, bcm_port_t port,
                          bcm_switch_control_t sctype,
                          bcm_gport_t *gport, int gport_count,
                          int *actual_gport_count)
{
    bcm_port_t local_port;
    int type = 0, class = -1, hw_cosq, count = 0;
    int port_index;
    uint32 profile_index;
    uint32 rval, cos_bmp;
    uint64 rval64[16], *rval64s[1];
    static const soc_reg_t port_fc_reg = PORT_LLFC_CFGr;
    soc_field_t field = INVALIDf;
    _bcm_hx5_cosq_node_t *port_node = NULL;
    int phy_port, mmu_port;
    soc_info_t *si = &SOC_INFO(unit);

    if (gport == NULL || gport_count <= 0 || actual_gport_count == NULL) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));
    if (IS_CPU_PORT(unit, local_port)) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN(_bcm_hx5_cosq_pfc_class_resolve(sctype, &type, &class));

    phy_port = si->port_l2p_mapping[local_port];
    mmu_port = si->port_p2m_mapping[phy_port];
    _HX5_PORT_INDEX_GET(unit, mmu_port, port_index);

    rval64s[0] = rval64;
    BCM_IF_ERROR_RETURN(soc_reg32_get(unit, port_fc_reg, local_port, 0, &rval));
    profile_index = 16 * soc_reg_field_get(unit, port_fc_reg, rval,
                                           PROFILE_INDEXf);

    if (type == _BCM_HX5_COSQ_TYPE_MCAST) {
        field = MC_COS_BMPf;
        port_node = _HX5_IS_ST_PORT(unit, mmu_port) ?
                    _bcm_hx5_cosq_st_port_info[unit][port_index].mcast :
                    _bcm_hx5_cosq_port_info[unit][port_index].mcast;
    } else {
        field = UC_COS_BMPf;
        port_node = _HX5_IS_ST_PORT(unit, mmu_port) ?
                    _bcm_hx5_cosq_st_port_info[unit][port_index].ucast :
                    _bcm_hx5_cosq_port_info[unit][port_index].ucast;
    }

    BCM_IF_ERROR_RETURN
        (soc_profile_reg_get(unit, _bcm_hx5_prio2cos_profile[unit],
                             profile_index, 16, rval64s));

    cos_bmp = soc_reg64_field32_get(unit, PRIO2COS_PROFILE_64r, rval64[class],
                                    field);
    for (hw_cosq = 0; hw_cosq < si->port_num_cosq[local_port]; hw_cosq++) {
        if (!(cos_bmp & (1 << hw_cosq))) {
            continue;
        }
        gport[count++] = port_node[hw_cosq].gport;

        if (count == gport_count) {
            break;
        }
    }
    if (count == 0) {
        return BCM_E_NOT_FOUND;
    }
    *actual_gport_count = count;

    return BCM_E_NONE;
}

/*
 * Function:
 *     _bcm_hx5_cosq_port_fc_get
 * Purpose:
 *     Get the UC|MC gport values associated with
 *     the given PFC/SAFC class.
 * Parameters:
 *     unit             - (IN) unit number
 *     port             - (IN) port number
 *     fc_class         - (IN) PFC/SAFC internal priority class
 *     gport_list       - (OUT) UC|MC gport list
 *     gport_count      - (OUT) gport count
 * Returns:
 *     BCM_E_XXX
 */
STATIC int
_bcm_hx5_cosq_port_fc_get(int unit, bcm_gport_t local_port,
                         int fc_class, bcm_gport_t *gport_list,
                         int *gport_count)
{
    int hw_cosq, count = 0;
    uint32 profile_index;
    uint32 rval, uc_cos_bmp, mc_cos_bmp;
    uint64 rval64[16], *rval64s[1];
    static const soc_reg_t port_fc_reg = PORT_LLFC_CFGr;
    soc_info_t *si = &SOC_INFO(unit);

    if ((gport_list == NULL) || (gport_count == NULL)) {
        return BCM_E_PARAM;
    }

    rval64s[0] = rval64;
    BCM_IF_ERROR_RETURN
        (soc_reg32_get(unit, port_fc_reg, local_port, 0, &rval));
    profile_index = 16 * soc_reg_field_get(unit, port_fc_reg, rval,
                                           PROFILE_INDEXf);

    BCM_IF_ERROR_RETURN
        (soc_profile_reg_get(unit, _bcm_hx5_prio2cos_profile[unit],
                             profile_index, 16, rval64s));

    uc_cos_bmp = soc_reg64_field32_get(unit, PRIO2COS_PROFILE_64r, rval64[fc_class],
                                       UC_COS_BMPf);
    mc_cos_bmp = soc_reg64_field32_get(unit, PRIO2COS_PROFILE_64r, rval64[fc_class],
                                       MC_COS_BMPf);

    for (hw_cosq = 0; hw_cosq < si->port_num_uc_cosq[local_port]; hw_cosq++) {
        if (!(uc_cos_bmp & (1 << hw_cosq))) {
            continue;
        }
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_port_cos_resolve(unit, local_port, hw_cosq,
                                           _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE,
                                           &gport_list[count++]));
    }

    for (hw_cosq = 0; hw_cosq < si->port_num_cosq[local_port]; hw_cosq++) {
        if (!(mc_cos_bmp & (1 << hw_cosq))) {
            continue;
        }
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_port_cos_resolve(unit, local_port, hw_cosq,
                                           _BCM_HX5_COSQ_INDEX_STYLE_MCAST_QUEUE,
                                           &gport_list[count++]));
    }

    if (count == 0) {
        return BCM_E_NOT_FOUND;
    }
    *gport_count = count;

    return BCM_E_NONE;
}

/*
 * Function:
 *    _bcm_hx5_cosq_port_fc_profile_set
 * Purpose:
 *     Set PFC/SAFC Prio 2 Cos Map and set the profile index for the Port
 * Parameters:
 *     unit       - (IN) unit number
 *     port       - (IN) GPORT identifier
 *     fc_class   - (IN) Input Class
 *     uc_cos_bmp - (IN) UC Cos bitmap array
 *     mc_cos_bmp - (IN) MC Cos bitmap array
 *     num_class  - (IN) Number of input class
 * Returns:
 *     BCM_E_XXX
 */
STATIC int
_bcm_hx5_cosq_port_fc_profile_set(int unit, bcm_port_t local_port,
                int *fc_class, uint32 *uc_cos_bmp, uint32 *mc_cos_bmp,
                int num_class)
{
    uint32 profile_index, old_profile_index;
    uint32 rval;
    uint64 rval64[16], *rval64s[1];
    static const soc_reg_t port_fc_reg = PORT_LLFC_CFGr;
    int entry, cur_class;
    uint32 cur_uc_bmp, cur_mc_bmp;

    if ((fc_class == NULL) ||
        (uc_cos_bmp == NULL) ||
        (mc_cos_bmp == NULL)) {
        return BCM_E_PARAM;
    }

    rval64s[0] = rval64;
    BCM_IF_ERROR_RETURN
        (soc_reg32_get(unit, port_fc_reg, local_port, 0, &rval));

    old_profile_index = 16 * soc_reg_field_get(unit, port_fc_reg, rval,
                                               PROFILE_INDEXf);

    BCM_IF_ERROR_RETURN
        (soc_profile_reg_get(unit, _bcm_hx5_prio2cos_profile[unit],
                             old_profile_index, 16, rval64s));

    for (entry = 0; entry < num_class; entry++) {
        cur_class = fc_class[entry];
        cur_uc_bmp = uc_cos_bmp[entry];
        cur_mc_bmp = mc_cos_bmp[entry];
        soc_reg64_field32_set(unit, PRIO2COS_PROFILE_64r, &rval64[cur_class],
                              UC_COS_BMPf, cur_uc_bmp);
        soc_reg64_field32_set(unit, PRIO2COS_PROFILE_64r, &rval64[cur_class],
                              MC_COS_BMPf, cur_mc_bmp);

    }

    BCM_IF_ERROR_RETURN
        (soc_profile_reg_add(unit, _bcm_hx5_prio2cos_profile[unit], rval64s,
                             16, &profile_index));

    soc_reg_field_set(unit, port_fc_reg, &rval, PROFILE_INDEXf,
                      profile_index / 16);

    BCM_IF_ERROR_RETURN
        (soc_profile_reg_delete(unit, _bcm_hx5_prio2cos_profile[unit],
                                old_profile_index));

    BCM_IF_ERROR_RETURN
        (soc_reg32_set(unit, port_fc_reg, local_port, 0, rval));

    return BCM_E_NONE;
}

/*
 * Function:
 *      _bcm_hx5_fc_status_map_gport
 * Purpose:
 *      Set mapping in PFC/SAFC for gport, and update
 *      uc_cos_bmp/mc_cos_bmp with gport cosq.
 * Parameters:
 *      unit        - (IN) unit number
 *      port        - (IN) port number
 *      gport       - (IN) gport to be mapped
 *      uc_cos_map  - (OUT) unicast hw_cosq of gport
 *      mc_cos_map  - (OUT) multicast hw_cosq of gport
 * Returns:
 *      BCM_E_XXX
 */
STATIC int
_bcm_hx5_fc_status_map_gport(int unit, bcm_port_t port,
                bcm_gport_t gport, uint32 *uc_cos_bmp, uint32 *mc_cos_bmp)
{
    _bcm_hx5_cosq_node_t *node = NULL;
    bcm_port_t local_port = -1;
    bcm_cos_queue_t cosq = -1;
    soc_info_t *si = &SOC_INFO(unit);

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_node_get(unit, gport, NULL, &local_port, NULL, &node));

    if (node == NULL) {
        return BCM_E_PARAM;
    }
    if (local_port < 0) {
        return BCM_E_PARAM;
    }
    if (local_port != port) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
        cosq = node->hw_index - si->port_uc_cosq_base[local_port];
        *uc_cos_bmp |= 1 << cosq;
    } else if (BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        cosq = node->hw_index - si->port_cosq_base[local_port]; 
        *mc_cos_bmp |= 1 << cosq;
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *     _bcm_hx5_pfc_class_mapping_check
 * Purpose:
 *     Validate param of bcm_cosq_pfc_class_mapping_t.
 * Parameters:
 *     unit             - (IN) unit number
 *     port             - (IN) port number
 *     array_count      - (IN) count of mapping array
 *     mapping_array    - (IN) mapping array list
 * Returns:
 *     BCM_E_XXX
 */
STATIC int
_bcm_hx5_pfc_class_mapping_check(int unit,
    bcm_gport_t port,
    int array_count,
    bcm_cosq_pfc_class_mapping_t *mapping_array)
{
    int count, index, cur_class;
    bcm_port_t local_port = -1, resolved_port;
    bcm_gport_t cur_gport = 0;

    if (mapping_array == NULL) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));
    if (local_port < 0) {
        return BCM_E_PORT;
    }
    if (IS_CPU_PORT(unit, local_port)) {
        return BCM_E_PARAM;
    }

    for (count = 0; count < array_count; count++) {
        cur_class = mapping_array[count].class_id;
        if ((cur_class < 0) || (cur_class >= _BCM_HX5_NUM_PFC_CLASS)) {
            return BCM_E_PARAM;
        }

        for (index = 0; index < BCM_COSQ_PFC_GPORT_COUNT; index++) {
            cur_gport = mapping_array[count].gport_list[index];
            if (cur_gport == BCM_GPORT_INVALID) {
                break;
            }
            if (BCM_GPORT_IS_SET(cur_gport)) {
                if (!((BCM_GPORT_IS_UCAST_QUEUE_GROUP(cur_gport)) ||
                      (BCM_GPORT_IS_MCAST_QUEUE_GROUP(cur_gport)))) {
                    return BCM_E_PARAM;
                }
                BCM_IF_ERROR_RETURN(_bcm_hx5_cosq_node_get(unit, cur_gport,
                                        NULL, &resolved_port, NULL, NULL));
                if (resolved_port != local_port) {
                    return BCM_E_PARAM;
                }
            } else {
                return BCM_E_PARAM;
            }
        }
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_pfc_class_mapping_set
 * Purpose:
 *     Set PFC mapping for port.
 *     PFC class is mapped to cosq or scheduler node gports.
 * Parameters:
 *     unit             - (IN) unit number
 *     port             - (IN) port number
 *     array_count      - (IN) count of mapping
 *     mapping_array    - (IN) mappings
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_pfc_class_mapping_set(int unit, bcm_gport_t port,
                                   int array_count,
                                   bcm_cosq_pfc_class_mapping_t *mapping_array)
{
    int index, count;
    int cur_class = 0;
    int pfc_class[_BCM_HX5_NUM_PFC_CLASS];
    bcm_gport_t cur_gport = 0;
    uint32 uc_cos_bmp[_BCM_HX5_NUM_PFC_CLASS] = {0};
    uint32 mc_cos_bmp[_BCM_HX5_NUM_PFC_CLASS] = {0};
    bcm_port_t local_port = -1;

    if ((array_count < 0) || (array_count > _BCM_HX5_NUM_PFC_CLASS)) {
        return BCM_E_PARAM;
    }
    if (mapping_array == NULL) {
        return BCM_E_PARAM;
    }
    BCM_IF_ERROR_RETURN
        (_bcm_hx5_pfc_class_mapping_check(unit, port,
                                          array_count, mapping_array));

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));

    for (count = 0; count < array_count; count++) {
        cur_class = mapping_array[count].class_id;
        uc_cos_bmp[cur_class] = 0;
        mc_cos_bmp[cur_class] = 0;

        for (index = 0; index < BCM_COSQ_PFC_GPORT_COUNT; index++) {
            cur_gport = mapping_array[count].gport_list[index];
            if (cur_gport == BCM_GPORT_INVALID) {
                break;
            }

            BCM_IF_ERROR_RETURN
                (_bcm_hx5_fc_status_map_gport(unit, local_port, cur_gport,
                                              &uc_cos_bmp[cur_class],
                                              &mc_cos_bmp[cur_class]));
        }
    }

    for (index = 0; index < _BCM_HX5_NUM_PFC_CLASS; index++) {
        pfc_class[index] = index;
    }
    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_port_fc_profile_set(unit, local_port, pfc_class,
                                           uc_cos_bmp, mc_cos_bmp,
                                           _BCM_HX5_NUM_PFC_CLASS));

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_pfc_class_mapping_get
 * Purpose:
 *     Get PFC mapping for port.
 *     Retrieves cosq or scheduler node gports
 *     associated to PFC classes.
 * Parameters:
 *     unit             - (IN) unit number
 *     port             - (IN) port number
 *     array_max        - (IN) max retrieve count
 *     mapping_array    - (OUT) mappings
 *     array_count      - (OUT) retrieved mapping count
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_pfc_class_mapping_get(int unit, bcm_gport_t port,
                                   int array_max,
                                   bcm_cosq_pfc_class_mapping_t *mapping_array,
                                   int *array_count)
{
    int rv = 0;
    int cur_class = 0;
    int actual_gport_count, class_count = 0;
    bcm_port_t local_port = -1;

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));

    if (local_port < 0) {
        return BCM_E_PORT;
    }
    if (IS_CPU_PORT(unit, local_port)) {
        return BCM_E_PARAM;
    }
    if (((mapping_array == NULL) && (array_max > 0)) ||
        ((mapping_array != NULL) && (array_max <= 0)) ||
        (array_count == NULL)) {
        return BCM_E_PARAM;
    }
    if (array_max <= 0) {
        *array_count = _BCM_HX5_NUM_PFC_CLASS;
        return BCM_E_NONE;
    }

    for (cur_class = 0; cur_class < _BCM_HX5_NUM_PFC_CLASS; cur_class++) {
        actual_gport_count = 0;
        rv = _bcm_hx5_cosq_port_fc_get(unit, local_port, cur_class,
                                       mapping_array[class_count].gport_list,
                                       &actual_gport_count);

        if (rv == BCM_E_NONE) {
            mapping_array[class_count].class_id = cur_class;
            if (actual_gport_count < BCM_COSQ_PFC_GPORT_COUNT) {
                mapping_array[class_count].gport_list[actual_gport_count] =
                                                        BCM_GPORT_INVALID;
            }
            class_count++;
        } else if (rv != BCM_E_NOT_FOUND) {
            return rv;
        }

        if ((class_count == array_max) && (array_max > 0)) {
            break;
        }
    }

    *array_count = class_count;
    if (class_count == 0) {
        return BCM_E_NOT_FOUND;
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_safc_class_mapping_set
 * Purpose:
 *     Set SAFC mapping for port.
 *     SAFC class is mapped to cosq or scheduler node gports.
 * Parameters:
 *     unit             - (IN) unit number
 *     port             - (IN) port number
 *     array_count      - (IN) count of mapping
 *     mapping_array    - (IN) mappings
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_safc_class_mapping_set(int unit, bcm_gport_t port, int array_count,
                                bcm_cosq_safc_class_mapping_t *mapping_array)
{
    int index, count;
    int cur_class = 0;
    int safc_class[_BCM_HX5_NUM_SAFC_CLASS];
    bcm_gport_t cur_gport = 0;
    uint32 uc_cos_bmp[_BCM_HX5_NUM_SAFC_CLASS] = {0};
    uint32 mc_cos_bmp[_BCM_HX5_NUM_SAFC_CLASS] = {0};
    bcm_port_t local_port = -1;

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));

    if (local_port < 0) {
        return BCM_E_PORT;
    }

    if (IS_CPU_PORT(unit, local_port)) {
        return BCM_E_PARAM;
    }

    if ((array_count < 0) || (array_count > _BCM_HX5_NUM_SAFC_CLASS)) {
        return BCM_E_PARAM;
    }

    if (mapping_array == NULL) {
        return BCM_E_PARAM;
    }

    for (count = 0; count < array_count; count++) {
        cur_class = mapping_array[count].class_id;
        if ((cur_class < 0) || (cur_class >= _BCM_HX5_NUM_SAFC_CLASS)) {
            return BCM_E_PARAM;
        } else {
            uc_cos_bmp[cur_class] = 0;
            mc_cos_bmp[cur_class] = 0;
        }

        for (index = 0; index < BCM_COSQ_SAFC_GPORT_COUNT; index++) {
            cur_gport = mapping_array[count].gport_list[index];
            if (cur_gport == BCM_GPORT_INVALID) {
                break;
            }

            if ((BCM_GPORT_IS_UCAST_QUEUE_GROUP(cur_gport)) ||
                (BCM_GPORT_IS_MCAST_QUEUE_GROUP(cur_gport))) {
                BCM_IF_ERROR_RETURN
                    (_bcm_hx5_fc_status_map_gport(unit, local_port, cur_gport,
                                                  &uc_cos_bmp[cur_class],
                                                  &mc_cos_bmp[cur_class]));
            } else {
                return BCM_E_PARAM;
            }
        }
    }

    for (index = 0; index < _BCM_HX5_NUM_SAFC_CLASS; index++) {
        safc_class[index] = index;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_port_fc_profile_set(unit, local_port, safc_class,
                                           uc_cos_bmp, mc_cos_bmp,
                                           _BCM_HX5_NUM_SAFC_CLASS));

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_safc_class_mapping_get
 * Purpose:
 *     Get SAFC mapping for port.
 *     Retrieves cosq or scheduler node gports associated to SAFC classes.
 * Parameters:
 *     unit             - (IN) unit number
 *     port             - (IN) port number
 *     array_max        - (IN) max retrieve count
 *     mapping_array    - (OUT) mappings
 *     array_count      - (OUT) retrieved mapping count
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_safc_class_mapping_get(int unit, bcm_gport_t port, int array_max,
                                bcm_cosq_safc_class_mapping_t *mapping_array,
                                int *array_count)
{
    int rv = 0;
    int cur_class = 0;
    int actual_gport_count, class_count = 0;
    bcm_port_t local_port = -1;

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));

    if (local_port < 0) {
        return BCM_E_PORT;
    }

    if (IS_CPU_PORT(unit, local_port)) {
        return BCM_E_PARAM;
    }

    if (((mapping_array == NULL) && (array_max > 0)) ||
        ((mapping_array != NULL) && (array_max <= 0)) ||
        (array_count == NULL)) {
        return BCM_E_PARAM;
    }

    if (array_max <= 0) {
        *array_count = _BCM_HX5_NUM_SAFC_CLASS;
        return BCM_E_NONE;
    }

    for (cur_class = 0; cur_class < _BCM_HX5_NUM_SAFC_CLASS; cur_class++) {
        actual_gport_count = 0;
        rv = _bcm_hx5_cosq_port_fc_get(unit, local_port, cur_class,
                                       mapping_array[class_count].gport_list,
                                       &actual_gport_count);

        if (rv == BCM_E_NONE) {
            mapping_array[class_count].class_id = cur_class;
            if (actual_gport_count < BCM_COSQ_SAFC_GPORT_COUNT) {
                mapping_array[class_count].gport_list[actual_gport_count] =
                                                BCM_GPORT_INVALID;
            }
            class_count++;
        } else if (rv != BCM_E_NOT_FOUND) {
            return rv;
        }

        if (class_count == array_max) {
            break;
        }
    }

    *array_count = class_count;
    if (class_count == 0) {
        return BCM_E_NOT_FOUND;
    }

    return BCM_E_NONE;
}
/*
 *   Function:
 *        bcm_hx5_cosq_buffer_id_multi_get
 *   Purpose:
 *        Get mutliple buffer ids associated with a specified port.
 *   Parameters:
 *        unit - (IN) BCM device number.
 *        gport - (IN) Port
 *        cosq - (IN) Reserved field
 *        direction - (IN) Specify ingress or egress direction
 *        array_max - (IN) number of entries to be retrieved
 *        buf_id_array - (OUT) Buffer id array
 *        array_count - (OUT) Actural buffer id count in buf_id_array
 *   Returns:
 *       BCM_E_XXX
 * */
int
bcm_hx5_cosq_buffer_id_multi_get(int unit, bcm_gport_t gport,
        bcm_cos_queue_t cosq, bcm_cosq_dir_t direction,
        int array_max, bcm_cosq_buffer_id_t *buf_id_array,
        int *array_count)
{
    bcm_port_t local_port;
    int i;

    if ((direction < bcmCosqIngress) ||
            (direction >= bcmCosqDirectionMaxCount)) {
        return BCM_E_PARAM;
    }

    if (!BCM_GPORT_IS_SET(gport)) {
        local_port = gport;
    } else if (BCM_GPORT_IS_LOCAL(gport)) {
        local_port = BCM_GPORT_LOCAL_GET(gport);
    } else if (BCM_GPORT_IS_MODPORT(gport)) {
        BCM_IF_ERROR_RETURN(bcm_esw_port_local_get(unit, gport, &local_port));
    } else if (BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) {
        int idx;
        BCM_IF_ERROR_RETURN(_bcm_hx5_cosq_index_resolve(unit, gport, cosq,
                    _BCM_HX5_COSQ_INDEX_STYLE_UCAST_QUEUE, &local_port, &idx, NULL));
    } else {
        return BCM_E_PARAM;
    }

    if (!SOC_PORT_VALID(unit, local_port)) {
        return BCM_E_PORT;
    }

    if (array_max >= 1) {
        *array_count = 1;
    } else if (array_max == 0){
        *array_count = array_max;
    } else {
        return BCM_E_PARAM;
    }

    for (i = 0; i < *array_count; i++) {
        buf_id_array[i] = 0;
    }

    for (i = *array_count; i < array_max; i++) {
        buf_id_array[i] = BCM_COSQ_INVALID_BUF_ID;
    }

    return BCM_E_NONE;
}

#ifdef BCM_WARM_BOOT_SUPPORT
#define BCM_WB_VERSION_1_0                SOC_SCACHE_VERSION(1,0)
#define BCM_WB_VERSION_2_0                SOC_SCACHE_VERSION(2,0)
#define BCM_WB_DEFAULT_VERSION            BCM_WB_VERSION_2_0
STATIC int
_bcm_hx5_cosq_wb_alloc(int unit)
{
    soc_scache_handle_t scache_handle;
    uint8 *scache_ptr = NULL;
    int rv, alloc_size = 0, max_size = (4096 * 7);
    _bcm_hx5_cosq_cpu_port_info_t *cpu_port_info = NULL;

    /*
     * Sync _bcm_hx5_cosq_cpu_port_info structure
     */
    cpu_port_info = _bcm_hx5_cosq_cpu_port_info[unit];
    if (cpu_port_info == NULL) {
        return BCM_E_INIT;
    }
    alloc_size += sizeof(_bcm_hx5_cosq_cpu_port_info_t);

    /*
     * Sync the ref_count of IFP_COS_MAPm/COS_MAPm
     */
    alloc_size += (SOC_MEM_SIZE(unit, IFP_COS_MAPm) / _HX5_MMU_NUM_INT_PRI) *
                   sizeof(uint16);

    /*
     * Sync _bcm_hx5_cosq_cpu_cosq_config_t structure for all CPU queues
     */
    alloc_size += (SOC_HX5_NUM_CPU_QUEUES *
                   sizeof(_bcm_hx5_cosq_cpu_cosq_config_t));

    /*
     * Sync num_cos value
     */
    alloc_size += sizeof(int);

    /*    
     * Sync _soc_td3_mmu_traffic_ctrl_t
     */
    BCM_IF_ERROR_RETURN(soc_td3_mmu_traffic_ctrl_size(unit, &alloc_size));

    /*
     * Sync _bcm_pfc_deadlock_control_t structure
     */
    if (soc_feature(unit, soc_feature_pfc_deadlock)) {
        alloc_size += sizeof(_bcm_hx5_pfc_deadlock_control_t);
    }

    /*
     * Sync _bcm_hx5_cosq_cpu_cosq_config_t structure for all CPU queues
     */
    alloc_size += (_BCM_HX5_NUM_WRED_RESOLUTION_TABLE *
                   sizeof(uint32));

    if (soc_feature(unit, soc_feature_mpls_ecn)) {
        uint32 scache_size = 0;
        BCM_IF_ERROR_RETURN(
            bcmi_xgs5_ecn_scache_size_get(unit, &scache_size));
        alloc_size += scache_size;
    }

#if defined (BCM_TCB_SUPPORT) && defined (INCLUDE_TCB)
    if (soc_feature(unit, soc_feature_tcb)) {
        alloc_size += sizeof(uint16);
    }
#else
    alloc_size += sizeof(uint16);
#endif

    /* Reserving some space scache for future usecase (max_size) */
    if (alloc_size < max_size) {
        alloc_size = max_size;
    } else {
        /* Required size more than max size allocated for Cosq */
        return BCM_E_INIT;
    }

    SOC_SCACHE_HANDLE_SET(scache_handle, unit, BCM_MODULE_COSQ, 0);

    rv = _bcm_esw_scache_ptr_get(unit, scache_handle, TRUE, alloc_size,
                                 &scache_ptr, BCM_WB_DEFAULT_VERSION, NULL);

    if (rv == BCM_E_NOT_FOUND) {
        rv = BCM_E_NONE;
    }

    return rv;
}

int
bcm_hx5_cosq_reinit(int unit)
{
    soc_scache_handle_t scache_handle;
    uint8 *scache_ptr = NULL;
    int *int_scache_ptr = NULL;
    uint16 *u16_scache_ptr = NULL;
    uint32 *u32_scache_ptr = NULL;
    _bcm_hx5_cosq_cpu_port_info_t *cpu_port_info = NULL;
    int alloc_size = 0, pipe = -1, i, j;
    soc_profile_mem_t *profile_mem;
    soc_mem_t wred_config_mem = INVALIDm;
    int index, profile_index, resolution_index;
    int stable_size, rv, set_index, num;
    mmu_wred_config_entry_t qentry;
    uint32 entry[SOC_MAX_MEM_WORDS];
    int phy_port, mmu_port;
    bcm_port_t port;
    static const soc_reg_t port_fc_reg = PORT_LLFC_CFGr;
    uint32 rval;
    _bcm_bst_device_handlers_t bst_callbks;
    _bcm_hx5_cosq_cpu_cosq_config_t *cpu_cosq_config_p;
    uint16 recovered_ver = 0;
    int index_min, index_max;
    _bcm_hx5_pfc_deadlock_control_t *pfc_deadlock_control = NULL;
    soc_info_t *si = &SOC_INFO(unit); 


    SOC_IF_ERROR_RETURN(soc_stable_size_get(unit, &stable_size));
    if ((stable_size == 0) || (SOC_WARM_BOOT_SCACHE_IS_LIMITED(unit))) {
        /* COSQ warmboot requires extended scache support i.e. level2 warmboot*/
        return BCM_E_NONE;
    }

    SOC_SCACHE_HANDLE_SET(scache_handle, unit, BCM_MODULE_COSQ, 0);
    rv = _bcm_esw_scache_ptr_get(unit, scache_handle, FALSE, 0, &scache_ptr,
                                 BCM_WB_DEFAULT_VERSION, &recovered_ver);
    if (BCM_FAILURE(rv)) {
        return rv;
    }

    /* Restore _bcm_hx5_cosq_cpu_port_info structure */
    cpu_port_info = _bcm_hx5_cosq_cpu_port_info[unit];
    if (cpu_port_info == NULL) {
        return BCM_E_INIT;
    }
    alloc_size = sizeof(_bcm_hx5_cosq_cpu_port_info_t);
    sal_memcpy(cpu_port_info, scache_ptr, alloc_size);
    scache_ptr += alloc_size;

    /* Update IFP_COS_MAP memory profile reference counter */
    profile_mem = _bcm_hx5_ifp_cos_map_profile[unit];
    num = SOC_MEM_SIZE(unit, IFP_COS_MAPm) / _HX5_MMU_NUM_INT_PRI;
    u16_scache_ptr = (uint16 *)scache_ptr;
    for (i = 0; i < num; i++) {
        for (j = 0; j < *u16_scache_ptr; j++) {
            SOC_IF_ERROR_RETURN(
                soc_profile_mem_reference(unit, profile_mem,
                                          i * _HX5_MMU_NUM_INT_PRI,
                                          _HX5_MMU_NUM_INT_PRI));
        }
        u16_scache_ptr++;
    }
    scache_ptr = (uint8*)u16_scache_ptr;

    /* Recover CPU queue config information from scache */
    cpu_cosq_config_p = _bcm_hx5_cosq_cpu_cosq_config[unit][0];
    if (cpu_cosq_config_p == NULL) {
        return BCM_E_INIT;
    }
    alloc_size = (SOC_HX5_NUM_CPU_QUEUES *
                  sizeof(_bcm_hx5_cosq_cpu_cosq_config_t));
    sal_memcpy(cpu_cosq_config_p, scache_ptr, alloc_size);
    scache_ptr += alloc_size;

    /* Retriving num_cos value */
    int_scache_ptr = (int *) scache_ptr;
    _BCM_HX5_NUM_COS(unit) = *int_scache_ptr++;
    scache_ptr = (uint8*) int_scache_ptr;

    /* Update PRIO2COS_PROFILE register profile reference counter */
    PBMP_PORT_ITER(unit, port) {
        BCM_IF_ERROR_RETURN
            (soc_reg32_get(unit, port_fc_reg, port, 0, &rval));
        profile_index = 16 * soc_reg_field_get(unit, port_fc_reg, rval,
                                               PROFILE_INDEXf);
        SOC_IF_ERROR_RETURN
            (soc_profile_reg_reference(unit, _bcm_hx5_prio2cos_profile[unit],
                                       profile_index, 16));
    }

    /* Update PORT_COS_MAP memory profile reference counter */
    profile_mem = _bcm_hx5_cos_map_profile[unit];
    PBMP_ALL_ITER(unit, port) {
        SOC_IF_ERROR_RETURN
            (soc_mem_read(unit, COS_MAP_SELm, MEM_BLOCK_ALL, port, &entry));
        set_index = soc_mem_field32_get(unit, COS_MAP_SELm, &entry, SELECTf);
        SOC_IF_ERROR_RETURN
            (soc_profile_mem_reference(unit, profile_mem, set_index * 16, 16));
    }
    if (SOC_INFO(unit).cpu_hg_index != -1) {
        SOC_IF_ERROR_RETURN(soc_mem_read(unit, COS_MAP_SELm, MEM_BLOCK_ALL,
                                         SOC_INFO(unit).cpu_hg_index, &entry));
        set_index = soc_mem_field32_get(unit, COS_MAP_SELm, &entry, SELECTf);
        SOC_IF_ERROR_RETURN
            (soc_profile_mem_reference(unit, profile_mem, set_index * 16, 16));
    }

    /* Update MMU_WRED_DROP_CURVE_PROFILE memory profile reference counter */
    for (pipe = 0; pipe < NUM_PIPE(unit); pipe++) {
        wred_config_mem = SOC_MEM_UNIQUE_ACC(unit, MMU_WRED_CONFIGm)[pipe];
        if (wred_config_mem == INVALIDm) {
            return BCM_E_PARAM;
        }
        index_min = soc_mem_index_min(unit, wred_config_mem);
        index_max = soc_mem_index_max(unit, wred_config_mem);
        for (index = index_min; index < index_max; index++) {
            BCM_IF_ERROR_RETURN
                (soc_mem_read(unit, wred_config_mem,
                              MEM_BLOCK_ALL, index, &qentry));
            profile_index = soc_mem_field32_get(unit, wred_config_mem,
                                                &qentry, PROFILE_INDEXf);
            BCM_IF_ERROR_RETURN
                (soc_profile_mem_reference(unit, _bcm_hx5_wred_profile[unit],
                                           profile_index, 1));

            if (soc_mem_field32_get(unit, wred_config_mem, &qentry,
                ECN_MARKING_ENf)) {
                resolution_index = soc_mem_field32_get(
                    unit, wred_config_mem, &qentry,
                    WRED_CONG_NOTIFICATION_RESOLUTION_TABLE_MARKING_INDEXf);
            } else {
                resolution_index = soc_mem_field32_get(
                    unit, wred_config_mem, &qentry,
                    WRED_CONG_NOTIFICATION_RESOLUTION_TABLE_DROPPING_INDEXf);
            }
            _bcm_hx5_wred_resolution_tbl[resolution_index] = 1;
        }
    }

    /* Create gport tree */
    _BCM_HX5_MMU_INFO(unit)->gport_tree_created = FALSE;
    PBMP_ALL_ITER(unit, port) {
        phy_port = si->port_l2p_mapping[port];
        mmu_port = si->port_p2m_mapping[phy_port];
        if (IS_LB_PORT(unit, port) || IS_CPU_PORT(unit, port)
            || IS_FAE_PORT(unit, port)) {
            continue;
        }
        if (_HX5_IS_ST_PORT(unit, mmu_port)) {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_st_gport_tree_create(unit, port));
        } else {
            BCM_IF_ERROR_RETURN
                (_bcm_hx5_cosq_gport_tree_create(unit, port));
        }
    }
    _BCM_HX5_MMU_INFO(unit)->gport_tree_created = TRUE;

    /* BST reinit */
    sal_memset(&bst_callbks, 0, sizeof(_bcm_bst_device_handlers_t));
    bst_callbks.resolve_index = &_bcm_hx5_bst_index_resolve;
    bst_callbks.reverse_resolve_index = NULL;
    BCM_IF_ERROR_RETURN(_bcm_bst_attach(unit, &bst_callbks));

    /* Recover _soc_td3_mmu_traffic_ctrl_t */
    BCM_IF_ERROR_RETURN(soc_td3_mmu_traffic_ctrl_wb_restore(unit, &scache_ptr));


    /* PFC Deadlock recovery should be initialized
       irrespective of scache version to handle
       upgrades */
    if (soc_feature(unit, soc_feature_pfc_deadlock)) {
        BCM_IF_ERROR_RETURN(_bcm_pfc_deadlock_init(unit));
    }

    /* Recover PFC Deadlock recovery information from scache */
    if (soc_feature(unit, soc_feature_pfc_deadlock)) {
        pfc_deadlock_control = _BCM_HX5_UNIT_PFC_DEADLOCK_CONTROL(unit);
        if (pfc_deadlock_control == NULL) {
            return BCM_E_INIT;
        }
        alloc_size = sizeof(_bcm_hx5_pfc_deadlock_control_t);
        sal_memcpy(pfc_deadlock_control, scache_ptr, alloc_size);
        scache_ptr += alloc_size;
        /* Re-set the Hardware Registers/Memory info */
        BCM_IF_ERROR_RETURN(_bcm_hx5_pfc_deadlock_hw_res_init(unit));
        BCM_IF_ERROR_RETURN(_bcm_hx5_pfc_deadlock_reinit(unit));
        BCM_IF_ERROR_RETURN(_bcm_hx5_pfc_deadlock_recovery_reset(unit));
        pfc_deadlock_control->cosq_inv_mapping_get = _bcm_hx5_cosq_inv_mapping_get;
    }

    if (soc_feature(unit, soc_feature_ecn_wred)) {
        if (recovered_ver >= BCM_WB_VERSION_2_0) {
            BCM_IF_ERROR_RETURN(bcmi_xgs5_ecn_reinit(unit, &scache_ptr));
        }
    }

#if defined (BCM_TCB_SUPPORT) && defined (INCLUDE_TCB)
    if (soc_feature(unit, soc_feature_tcb)){
        _bcm_cosq_tcb_unit_ctrl_t *tcb_unit_info;
        BCM_IF_ERROR_RETURN(bcm_hx5_cosq_tcb_reinit(unit));

        tcb_unit_info = TCB_UNIT_CONTROL(unit);
        TCB_INIT(unit);

        alloc_size = sizeof(uint16);
        sal_memcpy(&tcb_unit_info->tcb_config_init_bmp, scache_ptr, alloc_size);
        scache_ptr += alloc_size;
    }
#else
    scache_ptr += sizeof(uint16);
#endif

    /* Retriving _bcm_hx5_wred_resolution_tbl value */
    u32_scache_ptr = (uint32 *) scache_ptr;
    for (i = 0; i < _BCM_HX5_NUM_WRED_RESOLUTION_TABLE; i++) {
        _bcm_hx5_wred_resolution_tbl[i] = *u32_scache_ptr++;
    }

    return BCM_E_NONE;
}

int
bcm_hx5_cosq_sync(int unit)
{
    soc_scache_handle_t scache_handle;
    uint8 *scache_ptr;
    int *int_scache_ptr;
    _bcm_hx5_cosq_cpu_port_info_t *cpu_port_info = NULL;
    int size = 0;
    _bcm_hx5_cosq_cpu_cosq_config_t **cpu_cosq_config_p;
    int ii;
    int rv = BCM_E_NONE, ref_count;
    uint16 *u16_scache_ptr;
    uint32 *u32_scache_ptr;
    _bcm_hx5_pfc_deadlock_control_t *pfc_deadlock_control = NULL;

    cpu_port_info = _bcm_hx5_cosq_cpu_port_info[unit];
    if (cpu_port_info == NULL) {
        return BCM_E_INIT;
    }

    SOC_SCACHE_HANDLE_SET(scache_handle, unit, BCM_MODULE_COSQ, 0);
    BCM_IF_ERROR_RETURN
        (_bcm_esw_scache_ptr_get(unit, scache_handle, FALSE, 0,
                                 &scache_ptr, BCM_WB_DEFAULT_VERSION, NULL));

    /* Cache _bcm_hx5_cosq_cpu_port_info_t structure */
    size = sizeof(_bcm_hx5_cosq_cpu_port_info_t);
    sal_memcpy(scache_ptr, cpu_port_info, size);
    scache_ptr += size/sizeof(uint8);

    /* Cache _bcm_hx5_ifp_cos_map_profile reference count */
    u16_scache_ptr = (uint16 *)scache_ptr;
    for (ii = 0;
         ii < (SOC_MEM_SIZE(unit, IFP_COS_MAPm) / _HX5_MMU_NUM_INT_PRI);
         ii++) {
        rv = soc_profile_mem_ref_count_get(unit,
                                           _bcm_hx5_ifp_cos_map_profile[unit],
                                           ii * _HX5_MMU_NUM_INT_PRI,
                                           &ref_count);
        if (!(rv == SOC_E_NOT_FOUND || rv == SOC_E_NONE)) {
            return rv;
        }
        *u16_scache_ptr++ = (uint16)(ref_count & 0xffff);
    }
    scache_ptr = (uint8*) u16_scache_ptr;

    /* Sync CPU Queue info */
    cpu_cosq_config_p = _bcm_hx5_cosq_cpu_cosq_config[unit];
    size = (SOC_HX5_NUM_CPU_QUEUES * sizeof(_bcm_hx5_cosq_cpu_cosq_config_t));
    sal_memcpy(scache_ptr, *cpu_cosq_config_p, size);
    scache_ptr += (size / sizeof(uint8));

    /* Sync num_cos value */
    int_scache_ptr = (int*) scache_ptr;
    *int_scache_ptr++ = _BCM_HX5_NUM_COS(unit);
    scache_ptr = (uint8 *)int_scache_ptr;

    /* Sync _soc_td3_mmu_traffic_ctrl_t */
    BCM_IF_ERROR_RETURN(soc_td3_mmu_traffic_ctrl_wb_sync(unit, &scache_ptr));

   
    /* Sync PFC Deadlock Control info */
    if (soc_feature(unit, soc_feature_pfc_deadlock)) {
        pfc_deadlock_control = _BCM_HX5_UNIT_PFC_DEADLOCK_CONTROL(unit);
        if (pfc_deadlock_control == NULL) {
            return BCM_E_INIT;
        }
        size = sizeof(_bcm_hx5_pfc_deadlock_control_t);
        sal_memcpy(scache_ptr, pfc_deadlock_control, size);
        scache_ptr += (size / sizeof(uint8));
    }

    if (soc_feature(unit, soc_feature_ecn_wred)) {
        BCM_IF_ERROR_RETURN(bcmi_xgs5_ecn_sync(unit, &scache_ptr));
    }

#if defined (BCM_TCB_SUPPORT) && defined (INCLUDE_TCB)
    if (soc_feature(unit, soc_feature_tcb)){
        _bcm_cosq_tcb_unit_ctrl_t *tcb_unit_info;
        tcb_unit_info = TCB_UNIT_CONTROL(unit);
        TCB_INIT(unit);

        u16_scache_ptr = (uint16*) scache_ptr;
        size = sizeof(uint16);
        sal_memcpy(u16_scache_ptr, &tcb_unit_info->tcb_config_init_bmp, size);
        u16_scache_ptr ++;
    }
#else
    u16_scache_ptr = (uint16*) scache_ptr;
    u16_scache_ptr ++;
#endif
    u32_scache_ptr = (uint32*) u16_scache_ptr;

    for (ii = 0; ii < _BCM_HX5_NUM_WRED_RESOLUTION_TABLE; ii++) {
        *u32_scache_ptr++ = _bcm_hx5_wred_resolution_tbl[ii];
    }

    scache_ptr = (uint8 *)u32_scache_ptr;

    return BCM_E_NONE;
}
#endif


/*
 * Function:
 *     bcm_hx5_cosq_init
 * Purpose:
 *     Initialize (clear) all COS schedule/mapping state.
 * Parameters:
 *     unit - (IN) unit number
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_init(int unit)
{
    int i, alloc_size = 0, numq = 0, pipe = -1;
    int rv = BCM_E_NONE;
    soc_mem_t mem = INVALIDm;
    soc_reg_t reg = INVALIDr;
    int entry_words[9];
    int phy_port, mmu_port;
    int min_index, max_index;
    bcm_port_t port;
    uint64 rval64s[16], *prval64s[1];
    _bcm_hx5_cosq_cpu_cosq_config_t *cpu_cosq_config_p = NULL;
    soc_mem_t wred_config_mem = INVALIDm;
    _bcm_bst_device_handlers_t bst_callbks;
    soc_info_t *si = &SOC_INFO(unit);

    static soc_mem_t wred_mems[9] = {
        MMU_WRED_DROP_CURVE_PROFILE_0m, MMU_WRED_DROP_CURVE_PROFILE_1m,
        MMU_WRED_DROP_CURVE_PROFILE_2m, MMU_WRED_DROP_CURVE_PROFILE_3m,
        MMU_WRED_DROP_CURVE_PROFILE_4m, MMU_WRED_DROP_CURVE_PROFILE_5m,
        MMU_WRED_DROP_CURVE_PROFILE_6m, MMU_WRED_DROP_CURVE_PROFILE_7m,
        MMU_WRED_DROP_CURVE_PROFILE_8m
    };
    
    mmu_wred_drop_curve_profile_0_entry_t entry_tcp_green;
    mmu_wred_drop_curve_profile_1_entry_t entry_tcp_yellow;
    mmu_wred_drop_curve_profile_2_entry_t entry_tcp_red;
    mmu_wred_drop_curve_profile_3_entry_t entry_nontcp_green;
    mmu_wred_drop_curve_profile_4_entry_t entry_nontcp_yellow;
    mmu_wred_drop_curve_profile_5_entry_t entry_nontcp_red;
    mmu_wred_drop_curve_profile_6_entry_t entry_ecn_green;
    mmu_wred_drop_curve_profile_7_entry_t entry_ecn_yellow;
    mmu_wred_drop_curve_profile_8_entry_t entry_ecn_red;
    void *entries[9];
    uint32 profile_index;
    int ii, wred_prof_count;

    numq = soc_property_get(unit, spn_BCM_NUM_COS, _BCM_HX5_COS_DEFAULT);
    if (numq < 1) {
        numq = 1;
    } else if (numq > _BCM_HX5_COS_DEFAULT) {
        numq = _BCM_HX5_COS_DEFAULT;
    }

    /* Create Port Information structure */
    alloc_size = sizeof(_bcm_hx5_cosq_port_info_t) * (_BCM_HX5_NUM_PORTS);
    if (_bcm_hx5_cosq_port_info[unit] == NULL) {
        _bcm_hx5_cosq_port_info[unit] =
            sal_alloc(alloc_size, "_bcm_hx5_cosq_port_info");
            if (_bcm_hx5_cosq_port_info[unit] == NULL) {
                return BCM_E_MEMORY;
            }
    }
    sal_memset(_bcm_hx5_cosq_port_info[unit], 0, alloc_size);

    /* Create HG Port Information structure */
    alloc_size = sizeof(_bcm_hx5_cosq_st_port_info_t) * (_BCM_HX5_NUM_ST_PORTS);
    if (_bcm_hx5_cosq_st_port_info[unit] == NULL) {
        _bcm_hx5_cosq_st_port_info[unit] =
            sal_alloc(alloc_size, "_bcm_hx5_cosq_st_port_info");
            if (_bcm_hx5_cosq_st_port_info[unit] == NULL) {
                return BCM_E_MEMORY;
            }
    }
    sal_memset(_bcm_hx5_cosq_st_port_info[unit], 0, alloc_size);

    /* Create CPU Port Information structure */
    alloc_size = sizeof(_bcm_hx5_cosq_cpu_port_info_t);
    if (_bcm_hx5_cosq_cpu_port_info[unit] == NULL) {
        _bcm_hx5_cosq_cpu_port_info[unit] =
            sal_alloc(alloc_size, "_bcm_hx5_cosq_cpu_port_info");
        if (_bcm_hx5_cosq_cpu_port_info[unit] == NULL) {
            _bcm_hx5_cosq_cleanup(unit);
            return BCM_E_MEMORY;
        }
    }
    sal_memset(_bcm_hx5_cosq_cpu_port_info[unit], 0, alloc_size);

    /* Create MMU Port Information structure */
    alloc_size = sizeof(_bcm_hx5_mmu_info_t);
    if (_bcm_hx5_mmu_info[unit] == NULL) {
        _bcm_hx5_mmu_info[unit] =
            sal_alloc(alloc_size, "_bcm_hx5_mmu_info");
        if (_bcm_hx5_mmu_info[unit] == NULL) {
            _bcm_hx5_cosq_cleanup(unit);
            return BCM_E_MEMORY;
        }
    }
    sal_memset(_bcm_hx5_mmu_info[unit], 0, alloc_size);
    _BCM_HX5_MMU_INFO(unit)->_bcm_hx5_port_info =
            _bcm_hx5_cosq_port_info[unit];
    _BCM_HX5_MMU_INFO(unit)->_bcm_hx5_cpu_port_info =
            _bcm_hx5_cosq_cpu_port_info[unit];
    _BCM_HX5_MMU_INFO(unit)->_bcm_hx5_st_port_info =
            _bcm_hx5_cosq_st_port_info[unit];

    /* Create profile for PORT_COS_MAP table */
    if (_bcm_hx5_cos_map_profile[unit] == NULL) {
        _bcm_hx5_cos_map_profile[unit] = sal_alloc(sizeof(soc_profile_mem_t),
                                                  "COS_MAP Profile Mem");
        if (_bcm_hx5_cos_map_profile[unit] == NULL) {
            _bcm_hx5_cosq_cleanup(unit);
            return BCM_E_MEMORY;
        }
        soc_profile_mem_t_init(_bcm_hx5_cos_map_profile[unit]);
    }
    mem = PORT_COS_MAPm;
    min_index = soc_mem_index_min(unit, PORT_COS_MAPm);
    max_index = soc_mem_index_max(unit, PORT_COS_MAPm) / 2;
    entry_words[0] = sizeof(port_cos_map_entry_t) / sizeof(uint32);

    /* create an cos_map profile with max index of 64,
     * because cos_map_sel being an 2 bit we can able to 
     * maintain up to 4 profiles.
     */
    rv = soc_profile_mem_index_create(unit, &mem, entry_words,
                                 &min_index, &max_index, NULL, 1,
                                _bcm_hx5_cos_map_profile[unit]);
    if (rv != SOC_E_NONE) {
        _bcm_hx5_cosq_cleanup(unit);
        return rv;
    }

    /* Create profile for IFP_COS_MAP table */
    if (_bcm_hx5_ifp_cos_map_profile[unit] == NULL) {
        _bcm_hx5_ifp_cos_map_profile[unit]
            = sal_alloc(sizeof(soc_profile_mem_t), "IFP_COS_MAP Profile Mem");
        if (_bcm_hx5_ifp_cos_map_profile[unit] == NULL) {
            _bcm_hx5_cosq_cleanup(unit);
            return BCM_E_MEMORY;
        }
        soc_profile_mem_t_init(_bcm_hx5_ifp_cos_map_profile[unit]);
    }
    mem = IFP_COS_MAPm;
    entry_words[0] = sizeof(ifp_cos_map_entry_t) / sizeof(uint32);

    rv = soc_profile_mem_create(unit, &mem, entry_words, 1,
            _bcm_hx5_ifp_cos_map_profile[unit]);
    if (rv != SOC_E_NONE) {
        _bcm_hx5_cosq_cleanup(unit);
        return rv;
    }

    /* Create profile for MMU_WRED_DROP_CURVE_PROFILE_x tables */
    if (_bcm_hx5_wred_profile[unit] == NULL) {
        _bcm_hx5_wred_profile[unit] =
            sal_alloc(sizeof(soc_profile_mem_t), "WRED Profile Mem");
        if (_bcm_hx5_wred_profile[unit] == NULL) {
            _bcm_hx5_cosq_cleanup(unit);
            return BCM_E_MEMORY;
        }
        soc_profile_mem_t_init(_bcm_hx5_wred_profile[unit]);
    }

    entry_words[0] =
        sizeof(mmu_wred_drop_curve_profile_0_entry_t) / sizeof(uint32);
    entry_words[1] =
        sizeof(mmu_wred_drop_curve_profile_1_entry_t) / sizeof(uint32);
    entry_words[2] =
        sizeof(mmu_wred_drop_curve_profile_2_entry_t) / sizeof(uint32);
    entry_words[3] =
        sizeof(mmu_wred_drop_curve_profile_3_entry_t) / sizeof(uint32);
    entry_words[4] =
        sizeof(mmu_wred_drop_curve_profile_4_entry_t) / sizeof(uint32);
    entry_words[5] =
        sizeof(mmu_wred_drop_curve_profile_5_entry_t) / sizeof(uint32);
    entry_words[6] =
        sizeof(mmu_wred_drop_curve_profile_6_entry_t) / sizeof(uint32);
    entry_words[7] =
        sizeof(mmu_wred_drop_curve_profile_7_entry_t) / sizeof(uint32);
    entry_words[8] =
        sizeof(mmu_wred_drop_curve_profile_8_entry_t) / sizeof(uint32);

    rv = soc_profile_mem_create(unit, wred_mems, entry_words, 9,
                                _bcm_hx5_wred_profile[unit]);
    if (rv != SOC_E_NONE) {
        _bcm_hx5_cosq_cleanup(unit);
        return rv;
    }

    /* Create profile for PRIO2COS_PROFILE register */
    if (_bcm_hx5_prio2cos_profile[unit] == NULL) {
        _bcm_hx5_prio2cos_profile[unit] =
            sal_alloc(sizeof(soc_profile_reg_t), "PRIO2COS_PROFILE Profile Reg");
        if (_bcm_hx5_prio2cos_profile[unit] == NULL) {
            _bcm_hx5_cosq_cleanup(unit);
            return BCM_E_MEMORY;
        }
        soc_profile_reg_t_init(_bcm_hx5_prio2cos_profile[unit]);
    }
    reg = PRIO2COS_PROFILE_64r;
    rv = soc_profile_reg_create(unit, &reg, 1, _bcm_hx5_prio2cos_profile[unit]);
    if (rv != SOC_E_NONE) {
        _bcm_hx5_cosq_cleanup(unit);
        return rv;
    }

    if (_bcm_hx5_cosq_cpu_cosq_config[unit][0] == NULL) {
        cpu_cosq_config_p = sal_alloc(SOC_HX5_NUM_CPU_QUEUES *
                sizeof(_bcm_hx5_cosq_cpu_cosq_config_t), "CPU Cosq Config");
        if (cpu_cosq_config_p == NULL) {
            _bcm_hx5_cosq_cleanup(unit);
            return BCM_E_MEMORY;
        }
        if (NUM_CPU_COSQ(unit) > SOC_HX5_NUM_CPU_QUEUES) {
            /* Invalid CPU Queues */
            if (cpu_cosq_config_p != NULL) {
                sal_free(cpu_cosq_config_p);
                cpu_cosq_config_p = NULL;
            }
            _bcm_hx5_cosq_cleanup(unit);
            return BCM_E_INIT;
        }
        for (i = 0; i < NUM_CPU_COSQ(unit); i++) {
            _bcm_hx5_cosq_cpu_cosq_config[unit][i] = cpu_cosq_config_p + i;
        }
    }

    if (soc_feature(unit, soc_feature_helix5_ecn)) {
        rv = _bcm_td3_ecn_init(unit);
        if (rv != BCM_E_NONE) {
            if (cpu_cosq_config_p != NULL) {
                sal_free(cpu_cosq_config_p);
                cpu_cosq_config_p = NULL;
            }
            _bcm_hx5_cosq_cleanup(unit);
            return rv;
        }
    }

#if defined(INCLUDE_PSTATS)
    if (soc_feature(unit, soc_feature_pstats)) {
        rv = _bcm_pstats_init(unit);
        if (rv != BCM_E_NONE) {
            if (cpu_cosq_config_p != NULL) {
                sal_free(cpu_cosq_config_p);
                cpu_cosq_config_p = NULL;
            }
            _bcm_hx5_cosq_cleanup(unit);
            return rv;
        }
    }
#endif /* INCLUDE_PSTATS */

#if defined (INCLUDE_TCB) && defined (BCM_TCB_SUPPORT)
    if (soc_feature(unit, soc_feature_tcb)) {
        rv = bcm_hx5_cosq_tcb_init(unit);
    }
    if (rv != SOC_E_NONE) {
        if (cpu_cosq_config_p != NULL) {
            sal_free(cpu_cosq_config_p);
            cpu_cosq_config_p = NULL;
        }
        _bcm_hx5_cosq_cleanup(unit);
        return rv;
    }
#endif

#ifdef BCM_WARM_BOOT_SUPPORT
    if (SOC_WARM_BOOT(unit)) {
        rv = bcm_hx5_cosq_reinit(unit);
        if (rv != BCM_E_NONE) {
            if (cpu_cosq_config_p != NULL) {
                sal_free(cpu_cosq_config_p);
                cpu_cosq_config_p = NULL;
            }
            _bcm_hx5_cosq_cleanup(unit);
        }
    /*
     * COVERITY
     *
     * This checker will not be True.
     * cpu_cosq_config_p pointer is assigned to
     * _bcm_hx5_cosq_cpu_cosq_config global data
     * structure.
     */
    /* coverity[leaked_storage : FALSE] */
    /* coverity[resource_leak:FALSE] */
        return rv;
    } else {
        rv = _bcm_hx5_cosq_wb_alloc(unit);
        if (rv != BCM_E_NONE) {
            if (cpu_cosq_config_p != NULL) {
                sal_free(cpu_cosq_config_p);
                cpu_cosq_config_p = NULL;
            }
            _bcm_hx5_cosq_cleanup(unit);
            return rv;
        }
    }
#endif /* BCM_WARM_BOOT_SUPPORT */

    /* Assign default init values for CPU info */
    for (i = 0; i < NUM_CPU_COSQ(unit); i++) {
        if (_bcm_hx5_cosq_cpu_cosq_config[unit][i] == NULL) {
            if (cpu_cosq_config_p != NULL) {
                sal_free(cpu_cosq_config_p);
                cpu_cosq_config_p = NULL;
            }
            _bcm_hx5_cosq_cleanup(unit);
            return BCM_E_MEMORY;
        }
        sal_memset(_bcm_hx5_cosq_cpu_cosq_config[unit][i], 0,
                   sizeof(_bcm_hx5_cosq_cpu_cosq_config_t));
        _bcm_hx5_cosq_cpu_cosq_config[unit][i]->enable = 1;
    }

    /* Add default entries for PORT_COS_MAP memory profile */
    rv = bcm_hx5_cosq_config_set(unit, numq);
    if (rv != BCM_E_NONE) {
        if (cpu_cosq_config_p != NULL) {
            sal_free(cpu_cosq_config_p);
            cpu_cosq_config_p = NULL;
        }
        _bcm_hx5_cosq_cleanup(unit);
        return rv;
    }

    for (pipe = 0; pipe < NUM_PIPE(unit); pipe++) {
        /* Clear the WRED memories pointing to WRED profiles */
        mem = SOC_MEM_UNIQUE_ACC(unit, MMU_WRED_CONFIGm)[pipe];
        rv = soc_mem_clear(unit, mem, COPYNO_ALL, 1);
        if (rv != SOC_E_NONE) {
            if (cpu_cosq_config_p != NULL) {
                sal_free(cpu_cosq_config_p);
                cpu_cosq_config_p = NULL;
            }
            _bcm_hx5_cosq_cleanup(unit);
            return rv;
        }
    }
	
    /* Add default entries for MMU_WRED_DROP_CURVE_PROFILE_x memory profile */
    sal_memset(&entry_tcp_green, 0, sizeof(entry_tcp_green));
    sal_memset(&entry_tcp_yellow,0, sizeof(entry_tcp_yellow));
    sal_memset(&entry_tcp_red, 0, sizeof(entry_tcp_red));
    sal_memset(&entry_nontcp_green, 0, sizeof(entry_nontcp_green));
    sal_memset(&entry_nontcp_yellow, 0, sizeof(entry_nontcp_yellow));
    sal_memset(&entry_nontcp_red, 0, sizeof(entry_nontcp_red));
    sal_memset(&entry_ecn_green, 0, sizeof(entry_ecn_green));
    sal_memset(&entry_ecn_yellow,0, sizeof(entry_ecn_yellow));
    sal_memset(&entry_ecn_red, 0, sizeof(entry_ecn_red));
    entries[0] = &entry_tcp_green;
    entries[1] = &entry_tcp_yellow;
    entries[2] = &entry_tcp_red;
    entries[3] = &entry_nontcp_green;
    entries[4] = &entry_nontcp_yellow;
    entries[5] = &entry_nontcp_red;
    entries[6] = &entry_ecn_green;
    entries[7] = &entry_ecn_yellow;
    entries[8] = &entry_ecn_red;

    for (ii = 0; ii < HX5_WRED_PROFILE_NUM; ii++) {
        soc_mem_field32_set(unit, wred_mems[ii], entries[ii],
                            MIN_THDf, 0xffff);
        soc_mem_field32_set(unit, wred_mems[ii], entries[ii],
                            MAX_THDf, 0xffff);
    }
    profile_index = 0xffffffff;
    wred_config_mem = SOC_MEM_UNIQUE_ACC(unit, MMU_WRED_CONFIGm)[0];
    wred_prof_count = soc_mem_index_count(unit, wred_config_mem);

    /* In HX5 Profile table duplicate across all pipes.
        * Ref count needs to be updated too */
    wred_prof_count *= NUM_PIPE(unit);
    while(wred_prof_count) {
        if (profile_index == 0xffffffff) {
            rv = soc_profile_mem_add(unit, _bcm_hx5_wred_profile[unit],
                                     entries, 1, &profile_index);
        } else {
            rv = soc_profile_mem_reference(unit, _bcm_hx5_wred_profile[unit],
                                           profile_index, 0);
        }
        if (rv != SOC_E_NONE) {
            if (cpu_cosq_config_p != NULL) {
                sal_free(cpu_cosq_config_p);
                cpu_cosq_config_p = NULL;
            }
            _bcm_hx5_cosq_cleanup(unit);
            return rv;
        }
        wred_prof_count -= 1;
    }

    /* Add default entries for PRIO2COS_PROFILE register profile */
    sal_memset(rval64s, 0, sizeof(rval64s));
    prval64s[0] = rval64s;
    profile_index = 0xffffffff;
    PBMP_ALL_ITER(unit, port) {
        if (IS_CPU_PORT(unit, port) || IS_FAE_PORT(unit, port)) {
            continue;
        }
        if (profile_index == 0xffffffff) {
            rv = soc_profile_reg_add(unit, _bcm_hx5_prio2cos_profile[unit],
                                     prval64s, 16, &profile_index);
        } else {
            rv = soc_profile_reg_reference(unit, _bcm_hx5_prio2cos_profile[unit],
                                           profile_index, 0);
        }
        if (rv != SOC_E_NONE) {
            if (cpu_cosq_config_p != NULL) {
                sal_free(cpu_cosq_config_p);
                cpu_cosq_config_p = NULL;
            }
            _bcm_hx5_cosq_cleanup(unit);
            return rv;
        }
    }

    /* Create default gport tree */
    _BCM_HX5_MMU_INFO(unit)->gport_tree_created = FALSE;
    PBMP_ALL_ITER(unit, port) {
        phy_port = si->port_l2p_mapping[port];
        mmu_port = si->port_p2m_mapping[phy_port];
        if (IS_LB_PORT(unit, port) || 
                 IS_FAE_PORT(unit, port) ) {
            continue;
        }
        if(IS_CPU_PORT(unit, port)){
            rv = _bcm_hx5_cosq_cpu_tree_create(unit, port);
            if (rv != BCM_E_NONE) {
                if (cpu_cosq_config_p != NULL) {
                    sal_free(cpu_cosq_config_p);
                    cpu_cosq_config_p = NULL;
                }
                _bcm_hx5_cosq_cleanup(unit);
                return rv;
            }
        }else if (_HX5_IS_ST_PORT(unit, mmu_port)) {
            rv = _bcm_hx5_cosq_st_gport_tree_create(unit, port);
            if (rv != BCM_E_NONE) {
                if (cpu_cosq_config_p != NULL) {
                    sal_free(cpu_cosq_config_p);
                    cpu_cosq_config_p = NULL;
                }
                _bcm_hx5_cosq_cleanup(unit);
                return rv;
            }
        } else {
            rv = _bcm_hx5_cosq_gport_tree_create(unit, port);
            if (rv != BCM_E_NONE) {
                if (cpu_cosq_config_p != NULL) {
                    sal_free(cpu_cosq_config_p);
                    cpu_cosq_config_p = NULL;
                }
                _bcm_hx5_cosq_cleanup(unit);
                return rv;
            }
        }
    }
    _BCM_HX5_MMU_INFO(unit)->gport_tree_created = TRUE;

    rv = _bcm_hx5_cosq_gport_default_config(unit);
    if (rv != BCM_E_NONE) {
        if (cpu_cosq_config_p != NULL) {
            sal_free(cpu_cosq_config_p);
            cpu_cosq_config_p = NULL;
        }
        _bcm_hx5_cosq_cleanup(unit);
        return rv;
    }

    /* BST INIT */
    sal_memset(&bst_callbks, 0, sizeof(_bcm_bst_device_handlers_t));
    bst_callbks.resolve_index = &_bcm_hx5_bst_index_resolve;
    bst_callbks.reverse_resolve_index = &_bcm_hx5_cosq_bst_map_resource_to_gport_cos;
    rv = _bcm_bst_attach(unit, &bst_callbks);
    if (rv != BCM_E_NONE) {
        if (cpu_cosq_config_p != NULL) {
            sal_free(cpu_cosq_config_p);
            cpu_cosq_config_p = NULL;
        }
        _bcm_hx5_cosq_cleanup(unit);
        return rv;
    }

    if (soc_feature(unit, soc_feature_pfc_deadlock)) {
        rv = _bcm_pfc_deadlock_init(unit);
        if (rv != BCM_E_NONE) {
            if (cpu_cosq_config_p != NULL) {
                sal_free(cpu_cosq_config_p);
                cpu_cosq_config_p = NULL;
            }
            _bcm_hx5_cosq_cleanup(unit);
            return rv;
        }
    }
    sal_memset(hx5_time_domain_info, 0x0, sizeof(hx5_time_domain_info));
    for (pipe = 0; pipe < NUM_PIPE(unit); pipe++) {
        mmu_wred_config_entry_t entry;
        uint32 time_id = 0;
        uint32 wred_mem_count = 0;

        wred_config_mem = SOC_MEM_UNIQUE_ACC(unit, MMU_WRED_CONFIGm)[pipe];
        wred_mem_count = soc_mem_index_count(unit, wred_config_mem);
        if (INVALIDm != wred_config_mem) {
            for (i = 0; i< wred_mem_count; i++){ 
                BCM_IF_ERROR_RETURN
                    (soc_mem_read(unit, wred_config_mem, MEM_BLOCK_ALL, i,
                                  &entry));
                time_id = soc_mem_field32_get(unit, wred_config_mem, &entry,
                        TIME_DOMAIN_SELf);
                if(time_id < _BCM_HX5_NUM_TIME_DOMAIN) {
                    hx5_time_domain_info[unit][time_id].ref_count ++;
                }
            }
        }
    }

    for (i = 0; i < _BCM_HX5_NUM_WRED_RESOLUTION_TABLE; i++) {
        if (i == 0) {
            _bcm_hx5_wred_resolution_tbl[i] = 1;
        } else {
            _bcm_hx5_wred_resolution_tbl[i] = 0;
        }
    }




    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_port_attach
 * Purpose:
 *     Initialize Cosq for newly added port
 * Parameters:
 *     unit    - (IN) unit number
 *     port    - (IN) Logical port.
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_port_attach(int unit, bcm_port_t port)
{
    int default_mode = BCM_COSQ_WEIGHTED_ROUND_ROBIN, default_weight = 1;
    uint64 rval64s[16], *prval64s[1];
    uint32 profile_index;
    int phy_port, mmu_port;
    soc_info_t *si = &SOC_INFO(unit);


    if (IS_CPU_PORT(unit, port) || IS_LB_PORT(unit, port) ||
        IS_MANAGEMENT_PORT(unit, port)) {
        return BCM_E_PARAM;
    }

    phy_port = si->port_l2p_mapping[port];
    mmu_port = si->port_p2m_mapping[phy_port];
    /* Increase the reference of default PRIO2COS_PROFILE */
    sal_memset(rval64s, 0, sizeof(rval64s));
    prval64s[0] = rval64s;
    BCM_IF_ERROR_RETURN
        (soc_profile_reg_add(unit, _bcm_hx5_prio2cos_profile[unit],
                              prval64s, 16, &profile_index));

    /* Create gport tree */
    _BCM_HX5_MMU_INFO(unit)->gport_tree_created = FALSE;
    if (_HX5_IS_ST_PORT(unit, mmu_port)) {
        BCM_IF_ERROR_RETURN(_bcm_hx5_cosq_st_gport_tree_create(unit, port));
    } else {
        BCM_IF_ERROR_RETURN(_bcm_hx5_cosq_gport_tree_create(unit, port));
    }
    _BCM_HX5_MMU_INFO(unit)->gport_tree_created = TRUE;

    /* Set Default Scheduler Configuration on the ports */
    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_sched_config_port(unit, port, default_mode,
                                         default_weight));

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_port_detach
 * Purpose:
 *     Clear cosq configuration of port
 * Parameters:
 *     unit    - (IN) unit number
 *     port    - (IN) Logical port.
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_port_detach(int unit, bcm_port_t port)
{
    _bcm_hx5_cosq_port_info_t *port_info = NULL;
    _bcm_hx5_cosq_st_port_info_t *stport_info = NULL;
    int phy_port, mmu_port, index;
    uint32 rval, profile_index;

    soc_info_t *si = &SOC_INFO(unit);

    if (IS_CPU_PORT(unit, port) || IS_LB_PORT(unit, port) ||
        IS_MANAGEMENT_PORT(unit, port)) {
        return BCM_E_PARAM;
    }

    phy_port = si->port_l2p_mapping[port];
    mmu_port = si->port_p2m_mapping[phy_port];
    _HX5_PORT_INDEX_GET(unit, mmu_port, index); 

    /* Destroy cosq gport tree on port */
    if (_HX5_IS_ST_PORT(unit, mmu_port)) {
        stport_info = &_bcm_hx5_cosq_st_port_info[unit][index]; 
        sal_memset(stport_info, 0, sizeof(_bcm_hx5_cosq_st_port_info_t));
    } else {
        port_info = &_bcm_hx5_cosq_port_info[unit][index];
        sal_memset(port_info, 0, sizeof(_bcm_hx5_cosq_port_info_t));
    }

    /* Decrease the reference of defalt PRIO2COS_PROFILE */
    BCM_IF_ERROR_RETURN(soc_reg32_get(unit, PORT_LLFC_CFGr, port, 0, &rval));
    profile_index = soc_reg_field_get(unit, PORT_LLFC_CFGr, rval,
                                      PROFILE_INDEXf) * 16;
    BCM_IF_ERROR_RETURN
        (soc_profile_reg_delete(unit, _bcm_hx5_prio2cos_profile[unit],
                                profile_index));

    /* Clear cosq */
    si->port_num_cosq[port] = 0;
    si->port_cosq_base[port] = 0;
    si->port_num_uc_cosq[port] = 0;
    si->port_uc_cosq_base[port] = 0;
    si->port_num_ext_cosq[port] = 0;

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_cpu_cosq_enable_get
 * Purpose:
 *     To get enable/disable status on Rx of packets on the specified CPU cosq.
 * Parameters:
 *     unit    - (IN) unit number
 *     cosq    - (IN) CPU Cosq ID
 *     enable  - (IN) Enable/Disable
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_cpu_cosq_enable_get(int unit, bcm_cos_queue_t cosq, int *enable)
{
    uint32 entry[SOC_MAX_MEM_WORDS];
    int index, hw_enable;
    _bcm_hx5_cosq_cpu_cosq_config_t *cpu_cosq;
    soc_info_t *si;
    soc_mem_t thdm_mem = MMU_THDM_DB_QUEUE_CONFIG_PIPE0m;
    soc_field_t min_limit, shared_limit, limit_enable, dynamic_enable;

    si = &SOC_INFO(unit);

    if ((cosq < 0) || (cosq >= NUM_CPU_COSQ(unit))) {
        return BCM_E_PARAM;
    }

    cpu_cosq = _bcm_hx5_cosq_cpu_cosq_config[unit][cosq];

    if (!cpu_cosq) {
        return BCM_E_INTERNAL;
    }

    /* CPU Port (0) - MC cosq's range from 1290 - 1337. */
    index = si->port_cosq_base[CMIC_PORT(unit)] + cosq;
    hw_enable = 1;

    /* Sync up software record with hardware status. */
    BCM_IF_ERROR_RETURN(soc_mem_read(unit, thdm_mem, MEM_BLOCK_ALL, index,
                                     &entry));
    min_limit = soc_mem_field32_get(unit, thdm_mem, &entry, Q_MIN_LIMITf);
    shared_limit = soc_mem_field32_get(unit, thdm_mem, &entry, Q_SHARED_LIMITf);
    limit_enable = soc_mem_field32_get(unit, thdm_mem, &entry, Q_LIMIT_ENABLEf);
    dynamic_enable = soc_mem_field32_get(unit, thdm_mem, &entry, Q_LIMIT_DYNAMICf);

    if ((limit_enable != 0) && (dynamic_enable == 0) &&
        (min_limit == 0) && (shared_limit == 0)) {
        hw_enable = 0;
    }
    cpu_cosq->enable = hw_enable;

    *enable = cpu_cosq->enable;
    return BCM_E_NONE;

    return BCM_E_NONE;
}
/*
 * Function:
 *     bcm_hx5_cosq_cpu_cosq_enable_set
 * Purpose:
 *     To enable/disable Rx of packets on the specified CPU cosq.
 * Parameters:
 *     unit    - (IN) unit number
 *     cosq    - (IN) CPU Cosq ID
 *     enable  - (IN) Enable/Disable
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_cpu_cosq_enable_set(int unit, bcm_cos_queue_t cosq, int enable)
{
    uint32 entry[SOC_MAX_MEM_WORDS];
    int i, index, enable_status;
    _bcm_hx5_cosq_cpu_cosq_config_t *cpu_cosq_config;
    soc_info_t *si;
    soc_mem_t thdm_mem[] = {
        MMU_THDM_DB_QUEUE_CONFIG_PIPE0m,
        MMU_THDM_MCQE_QUEUE_CONFIG_PIPE0m
    };

    si = &SOC_INFO(unit);

    if ((cosq < 0) || (cosq >= NUM_CPU_COSQ(unit))) {
        return BCM_E_PARAM;
    }

    cpu_cosq_config = _bcm_hx5_cosq_cpu_cosq_config[unit][cosq];

    if (!cpu_cosq_config) {
        return BCM_E_INTERNAL;
    }

    BCM_IF_ERROR_RETURN(bcm_hx5_cosq_cpu_cosq_enable_get(unit, cosq,
                        &enable_status));
    if (enable == enable_status) {
        return BCM_E_NONE;
    }

    /* CPU Port (0) - MC cosq's range from 1290 - 1337. */
    index = si->port_cosq_base[CMIC_PORT(unit)] + cosq;

    /* To set DB and QE entries */
    for (i = 0; i < 2; i++) {
        BCM_IF_ERROR_RETURN
            (soc_mem_read(unit, thdm_mem[i], MEM_BLOCK_ALL, index, &entry));

        /* When enabled, restore the Min and Shared from the cached value */
        if (!enable) {
            cpu_cosq_config->q_min_limit[i] = soc_mem_field32_get(unit,
                                                thdm_mem[i], &entry,
                                                Q_MIN_LIMITf);
            cpu_cosq_config->q_shared_limit[i] = soc_mem_field32_get(unit,
                                                    thdm_mem[i], &entry,
                                                    Q_SHARED_LIMITf);
            cpu_cosq_config->q_limit_dynamic[i] = soc_mem_field32_get(unit,
                                                    thdm_mem[i], &entry,
                                                    Q_LIMIT_DYNAMICf);
            cpu_cosq_config->q_limit_enable[i] = soc_mem_field32_get(unit,
                                                    thdm_mem[i], &entry,
                                                    Q_LIMIT_ENABLEf);
            cpu_cosq_config->q_color_limit_enable[i] = soc_mem_field32_get(unit,
                                                        thdm_mem[i], &entry,
                                                        Q_COLOR_LIMIT_ENABLEf);
        }
        soc_mem_field32_set(unit, thdm_mem[i], &entry, Q_LIMIT_DYNAMICf,
                            enable ? cpu_cosq_config->q_limit_dynamic[i] : 0);
        soc_mem_field32_set(unit, thdm_mem[i], &entry, Q_LIMIT_ENABLEf,
                            enable ? cpu_cosq_config->q_limit_enable[i] : 1);
        soc_mem_field32_set(unit, thdm_mem[i], &entry, Q_COLOR_LIMIT_ENABLEf,
                            enable ? cpu_cosq_config->q_color_limit_enable[i] :1);
        soc_mem_field32_set(unit, thdm_mem[i], &entry, Q_MIN_LIMITf,
                            enable ? cpu_cosq_config->q_min_limit[i] : 0);
        soc_mem_field32_set(unit, thdm_mem[i], &entry, Q_SHARED_LIMITf,
                            enable ? cpu_cosq_config->q_shared_limit[i] : 0);
        cpu_cosq_config->enable = enable;
        BCM_IF_ERROR_RETURN
            (soc_mem_write(unit, thdm_mem[i], MEM_BLOCK_ALL, index, &entry));
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_field_classifier_get
 * Purpose:
 *     Get classifier type information.
 * Parameters:
 *     unit          - (IN) unit number
 *     classifier_id - (IN) Classifier ID
 *     classifier    - (OUT) Classifier info
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_field_classifier_get(int unit, int classifier_id,
                                  bcm_cosq_classifier_t *classifier)
{
    if (classifier == NULL) {
        return BCM_E_PARAM;
    }
    sal_memset(classifier, 0, sizeof(bcm_cosq_classifier_t));

    if (_BCM_COSQ_CLASSIFIER_IS_FIELD(classifier_id)) {
        classifier->flags |= BCM_COSQ_CLASSIFIER_FIELD;
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_field_classifier_id_create
 * Purpose:
 *     Create a cosq classifier.
 * Parameters:
 *     unit          - (IN) unit number
 *     classifier    - (IN) Classifier attributes
 *     classifier_id - (OUT) Classifier ID
 * Returns:
 *     BCM_E_XXX
 */
int
bcm_hx5_cosq_field_classifier_id_create(int unit, bcm_cosq_classifier_t
                                        *classifier, int *classifier_id)
{
    int rv;
    int ref_count = 0;
    int ent_per_set = _HX5_MMU_NUM_INT_PRI;
    int i;

    if (NULL == classifier || NULL == classifier_id) {
        return BCM_E_PARAM;
    }

    for (i = 0; i < SOC_MEM_SIZE(unit, IFP_COS_MAPm); i += ent_per_set) {
        rv = soc_profile_mem_ref_count_get(
                unit, _bcm_hx5_ifp_cos_map_profile[unit], i, &ref_count);
        if (SOC_FAILURE(rv)) {
            return rv;
        }
        if (0 == ref_count) {
            break;
        }
    }

    if (i >= SOC_MEM_SIZE(unit, IFP_COS_MAPm) && ref_count != 0) {
        *classifier_id = 0;
        return BCM_E_RESOURCE;
    }

    _BCM_COSQ_CLASSIFIER_FIELD_SET(*classifier_id, (i / ent_per_set));

    return BCM_E_NONE;
}

/*
 * Function:
 *      bcm_hx5_cosq_field_classifier_id_destroy
 * Purpose:
 *      Free resource associated with this field classifier id.
 * Parameters:
 *      unit          - (IN) Unit number.
 *      classifier_id - (IN) Classifier ID
 * Returns:
 *      BCM_E_xxx
 */
int
bcm_hx5_cosq_field_classifier_id_destroy(int unit, int classifier_id)
{
    return BCM_E_NONE;
}

/*
 * Function:
 *     bcm_hx5_cosq_field_classifier_map_set
 * Purpose:
 *     Set internal priority to ingress field processor CoS queue override
 *     mapping.
 * Parameters:
 *     unit           - (IN) unit number
 *     classifier_id  - (OUT) Classifier ID
 *     count          - (IN) Number of elements in priority_array and cosq_array
 *     priority_array - (IN) Array of internal priorities
 *     cosq_array     - (IN) Array of COS queues
 * Returns:
 *     BCM_E_XXX
 * Notes:
 *      Supported count value is [0-16] and 48
 *      When count = [0-16]
 *          Array Index [15-0] : Maps Prio[15-0] to UC, MC, HG and RQE cos[15-0]
 *      When count = 48
 *      Prio Array Index Map
 *          Array Index [15-0] : Maps Prio[15-0] to UC and HG cos[15-0] 
 *          Array Index [31-16] : Maps Prio[15-0] to MC and HG  cos[15-0]
 *          Array Index [47-32] : Maps Prio[15-0] to RQE cos[15-0]
 */
int
bcm_hx5_cosq_field_classifier_map_set(int unit, int classifier_id, int count,
                        bcm_cos_t *priority_array, bcm_cos_queue_t *cosq_array)
{
    int rv;
    int i;
    int max_entries = _HX5_MMU_NUM_INT_PRI;
    uint32 index, new_index;
    void *entries[1];
    ifp_cos_map_entry_t ent_buf[_HX5_MMU_NUM_INT_PRI];
    soc_field_t field = -1;
    soc_field_t field1 = -1;

    /* Input parameter check. */
    if (!_BCM_COSQ_CLASSIFIER_IS_FIELD(classifier_id)) {
        return BCM_E_PARAM;
    }

    if (NULL == priority_array || NULL == cosq_array) {
        return BCM_E_PARAM;
    }

    if ((count > max_entries) && (count != (max_entries * 3))) {
        return BCM_E_PARAM;
    }

    sal_memset(ent_buf, 0, sizeof(ifp_cos_map_entry_t) * max_entries);
    entries[0] = ent_buf;

    if (count != (max_entries * 3)) {
        for (i = 0; i < count; i++) {
            if (priority_array[i] < max_entries) {
                /* When count != max_entries * 3
                   We program the same mapping for all three
                   fields UC/MC/RQE/HG queues.
                   Hence cos_array[i] cannot have value more than
                   equal to 26 */
                if ((cosq_array[i] < 0) ||
                    (cosq_array[i] >= SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT)) {
                    return BCM_E_PARAM;
                }
                soc_mem_field32_set(unit, IFP_COS_MAPm, &ent_buf[priority_array[i]],
                                    IFP_MC_COSf, cosq_array[i]);
                soc_mem_field32_set(unit, IFP_COS_MAPm, &ent_buf[priority_array[i]],
                                    IFP_UC_COSf, cosq_array[i]);
                soc_mem_field32_set(unit, IFP_COS_MAPm, &ent_buf[priority_array[i]],
                                    IFP_HG_COSf, cosq_array[i]);
                soc_mem_field32_set(unit, IFP_COS_MAPm, &ent_buf[priority_array[i]],
                                    IFP_RQE_Q_NUMf, 
                                    (cosq_array[i] > _HX5_MMU_NUM_RQE_QUEUES) ? _HX5_MMU_NUM_RQE_QUEUES : cosq_array[i]);
            }
        }
    } else {
        for (i = 0; i < count; i++) {
            field = field1 = -1;
            if (priority_array[i] < max_entries) {
                if (i < max_entries) {
                    /* Number of UCAST queue per port = 26 */
                    if ((cosq_array[i] < 0) ||
                        (cosq_array[i] >= SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT)) {
                        return BCM_E_PARAM;
                    }
                    field = IFP_UC_COSf;
                    field1 = IFP_HG_COSf;
                } else if (i < (max_entries * 2)) {
                    /* Number of MCAST queue per port = 26 */
                    if ((cosq_array[i] < 0) ||
                        (cosq_array[i] >= SOC_HX5_NUM_MCAST_QUEUE_PER_ST_PORT)) {
                        return BCM_E_PARAM;
                    }
                    field = IFP_MC_COSf;
                    field1 = IFP_HG_COSf;
                } else {
                    if ((cosq_array[i] < 0) ||
                        (cosq_array[i] >= SOC_HX5_NUM_MCAST_QUEUE_PER_ST_PORT)) {
                        return BCM_E_PARAM;
                    }
                    /* Number of RQE queue per unit = 11 */
                    if (cosq_array[i] > _HX5_MMU_NUM_RQE_QUEUES) {
                       cosq_array[i] = _HX5_MMU_NUM_RQE_QUEUES;
                    }
                    field = IFP_RQE_Q_NUMf;
                }
                soc_mem_field32_set(unit, IFP_COS_MAPm, &ent_buf[priority_array[i]],
                        field, cosq_array[i]);
                if (field1 != -1) {
                    soc_mem_field32_set(unit, IFP_COS_MAPm, &ent_buf[priority_array[i]],
                            field1, cosq_array[i]);
                }
            }
        }
    }

    index = _BCM_COSQ_CLASSIFIER_FIELD_GET(classifier_id);

    rv = soc_profile_mem_delete(unit, _bcm_hx5_ifp_cos_map_profile[unit],
                                index * max_entries);

    /* If rv = SOC_E_NONE means that there exists a
     * mapping for given classifier_id which is now
     * successfully deleted and we can overwrite.
     * rv = SOC_E_NOT_FOUND means there was no mapping
     * for given classifier_id and we can create a new mapping
     * Otherwise there is something else wrong and we return
     * the error value returned by soc_profile_mem_delete()
     */
    if ((rv != SOC_E_NONE) && (rv != SOC_E_NOT_FOUND)) {
        return rv;
    }

    SOC_IF_ERROR_RETURN
        (soc_profile_mem_add(unit, _bcm_hx5_ifp_cos_map_profile[unit],
                             entries, max_entries, &new_index));

    /* If we get (index == new_index / max_entries) means we have
     * a successful mapping operation.
     * But if they are not equal which means there already exists
     * a similar mapping associated with other classifier_id hence
     * we return BCM_E_EXISTS.
     */

    if (index != (new_index / max_entries)) {
        SOC_IF_ERROR_RETURN
            (soc_profile_mem_delete(unit, _bcm_hx5_ifp_cos_map_profile[unit],
                                    new_index));
        return BCM_E_EXISTS;
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *      bcm_hx5_cosq_field_classifier_map_get
 * Purpose:
 *      Get internal priority to ingress field processor CoS queue
 *      override mapping information.
 * Parameters:
 *      unit           - (IN) Unit number.
 *      classifier_id  - (IN) Classifier ID
 *      array_max      - (IN) Size of priority_array and cosq_array
 *      priority_array - (IN) Array of internal priorities
 *      cosq_array     - (OUT) Array of COS queues
 *      array_count    - (OUT) Size of cosq_array
 * Returns:
 *      BCM_E_xxx
 * Notes:
 *      Supported array_max = [0-16] and 48
 *      When array_max = [0-16]
 *          Array Index [15-0] : Maps Prio[15-0] to UC cos[15-0]
 *      When array_max = 48
 *      Prio Array Index Map
 *          Array Index [15-0] : Maps Prio[15-0] to UC cos[15-0]
 *          Array Index [31-16] : Maps Prio[15-0] to MC cos[15-0]
 *          Array Index [47-32] : Maps Prio[15-0] to RQE cos[15-0]
 */
int
bcm_hx5_cosq_field_classifier_map_get(int unit, int classifier_id, int array_max,
    bcm_cos_t *priority_array, bcm_cos_queue_t *cosq_array, int *array_count)
{
    int rv;
    int i;
    int ent_per_set = _HX5_MMU_NUM_INT_PRI;
    uint32 index;
    void *entries[1];
    ifp_cos_map_entry_t ent_buf[_HX5_MMU_NUM_INT_PRI];
    soc_field_t field = -1;

    /* Input parameter check. */
    if (NULL == priority_array || NULL == cosq_array || NULL == array_count) {
        return BCM_E_PARAM;
    }

    sal_memset(ent_buf, 0, sizeof(ifp_cos_map_entry_t) * ent_per_set);
    entries[0] = ent_buf;

    /* Get profile table entry set base index. */
    index = _BCM_COSQ_CLASSIFIER_FIELD_GET(classifier_id);

    /* Read out entries from profile table into allocated buffer. */
    rv = soc_profile_mem_get(unit, _bcm_hx5_ifp_cos_map_profile[unit],
                             index * ent_per_set, ent_per_set, entries);
    if (SOC_FAILURE(rv)) {
        return rv;
    }

    if (array_max <= ent_per_set) {
        *array_count = array_max;
    } else if ((array_max > ent_per_set) && (array_max < (ent_per_set * 3))) {
        return BCM_E_PARAM;
    } else {
        *array_count = ent_per_set * 3;
    }
        /* Copy values into API OUT parameters. */
    for (i = 0; i < *array_count; i++) {
        if (priority_array[i % 16] >= _HX5_MMU_NUM_INT_PRI) {
            return BCM_E_PARAM;
        }
        if (i < ent_per_set) {
            field = IFP_UC_COSf;
        } else if (i < (ent_per_set * 2)) {
            field = IFP_MC_COSf;
        } else {
            field = IFP_RQE_Q_NUMf;
        }
        cosq_array[i] = soc_mem_field32_get(unit, IFP_COS_MAPm,
                                            &ent_buf[priority_array[i]],
                                            field);
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *      bcm_hx5_cosq_field_classifier_map_clear
 * Purpose:
 *      Delete an internal priority to ingress field processor CoS queue
 *      override mapping profile set.
 * Parameters:
 *      unit          - (IN) Unit number.
 *      classifier_id - (IN) Classifier ID
 * Returns:
 *      BCM_E_xxx
 */
int
bcm_hx5_cosq_field_classifier_map_clear(int unit, int classifier_id)
{
    int ent_per_set = _HX5_MMU_NUM_INT_PRI;
    uint32 index;

    /* Get profile table entry set base index. */
    index = _BCM_COSQ_CLASSIFIER_FIELD_GET(classifier_id);

    /* Delete the profile entries set. */
    SOC_IF_ERROR_RETURN
        (soc_profile_mem_delete(unit,
                                _bcm_hx5_ifp_cos_map_profile[unit],
                                index * ent_per_set));
    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_cpu_port_info_dump(int unit)
{
    _bcm_hx5_cosq_cpu_port_info_t *port_info;
     bcm_port_t port = 0; /* CPU Port */
    _bcm_hx5_cosq_node_t *node;
    int index, new_index;
    soc_hx5_sched_mode_e sched_mode = 0;
    int weight = 0;

    char *sched_modes[] = {"X", "SP", "WRR", "WERR"};

    if (!SOC_PORT_VALID(unit, port)) {
        return BCM_E_PORT;
    }
    port_info = _bcm_hx5_cosq_cpu_port_info[unit];
    if (port_info == NULL) {
        return BCM_E_INIT;
    }

    LOG_CLI((BSL_META_U(unit,
                        "=== CPU PORT ===\n")));

    LOG_CLI((BSL_META_U(unit,
                        "Nodes\n")));
    for (index = 0; index < SOC_HX5_NUM_SCHEDULER_PER_CPU_PORT; index++) {
        /* Node */
        node = &port_info->sched[index];
        new_index = (index >= 2) ? index - 2 : index;
        BCM_IF_ERROR_RETURN(
                _bcm_hx5_cosq_sched_mode_setget(unit, port, node->level, new_index,
                    &sched_mode, &weight, 0, 0));
        LOG_CLI((BSL_META_U(unit,
                        "L%d.%d: GPORT=0x%x HW_INDEX=%d MODE=%s WT=%d\n"),
                    node->level - 1, new_index, node->gport, node->hw_index,
                    sched_modes[sched_mode], weight));
    }

    LOG_CLI((BSL_META_U(unit,
                        "\nMC Queues\n")));
    for (index = 0; index < SOC_HX5_NUM_CPU_QUEUES; index++) {
        int parent_id = 0;
        /* MC Queue */
        node = &port_info->mcast[index];
        BCM_IF_ERROR_RETURN(
                _bcm_hx5_cosq_sched_mode_setget(unit, port, node->level, index,
                                                &sched_mode, &weight, 1, 0));
        BCM_IF_ERROR_RETURN(
            _bcm_hx5_cosq_node_get(unit, node->parent_gport, NULL, NULL,
                                   &parent_id, NULL));
        LOG_CLI((BSL_META_U(unit,
                            "    MC.%d: GPORT=0x%x HW_INDEX=%d MODE=%s WT=%d"
                            " PARENT=%d\n"),
                             index, node->gport, node->hw_index,
                             sched_modes[sched_mode], weight,
                             parent_id));
    }
    LOG_CLI((BSL_META_U(unit,
                        "=========== \n")));

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_st_port_info_dump(int unit, bcm_port_t port)
{
    _bcm_hx5_cosq_st_port_info_t *port_info;
    _bcm_hx5_cosq_node_t *node;
    int index, empty, port_index;
    int l1index = 0, l2index = 0, l3index = 0;
    int l1_max = 0, l2_max = 0, l3_max = 0;
    soc_hx5_sched_mode_e sched_mode = 0;
    int weight = 0;
    char *sched_modes[] = {"X", "SP", "WRR", "WERR"};
    int phy_port, mmu_port;
    soc_info_t *si = &SOC_INFO(unit);


    phy_port = si->port_l2p_mapping[port];
    mmu_port = si->port_p2m_mapping[phy_port];
    _HX5_PORT_INDEX_GET(unit, mmu_port, port_index);

    if (!SOC_PORT_VALID(unit, port)) {
        return BCM_E_PORT;
    }
    port_info = &_bcm_hx5_cosq_st_port_info[unit][port_index];

    empty = TRUE;
    for (index = 0; index < SOC_HX5_NUM_SCHEDULER_PER_ST_PORT; index++) {
        if (port_info->sched[index].numq > 0) {
            empty = FALSE;
            break;
        }
    }
    if (empty) {
        for (index = 0; index < SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT; index++) {
            if (port_info->ucast[index].numq > 0) {
                empty = FALSE;
                break;
            }
        }
    }
    if (empty) {
        for (index = 0; index < SOC_HX5_NUM_MCAST_QUEUE_PER_ST_PORT; index++) {
            if (port_info->mcast[index].numq > 0) {
                empty = FALSE;
                break;
            }
        }
    }

    if (empty == TRUE) {
        return BCM_E_NOT_FOUND;
    }

    LOG_CLI((BSL_META_U(unit,
                        "=== PORT %d\n"), port));

    for (index = 0; index < 3; index++) {
        /* Node */
        node = &port_info->sched[index];

        BCM_IF_ERROR_RETURN(
                _bcm_hx5_cosq_sched_mode_setget(unit, port, node->level, index,
                    &sched_mode, &weight, 0, 0));
        LOG_CLI((BSL_META_U(unit,
                        "L0.%d: GPORT=0x%x HW_INDEX=%d MODE=%s WT=%d\n"),
                    index, node->gport, node->hw_index,
                    sched_modes[sched_mode], weight));

        if (index == 0) {
            l1index = 3;
            l1_max = 4;
        } else if(index == 1) {
            l1index = 5;
            l1_max = 5;
        } else {
            l1index = 6;
            l1_max = 6;
        }
        for(; l1index <= l1_max; l1index++) {
            node = &port_info->sched[l1index];
            BCM_IF_ERROR_RETURN(
                    _bcm_hx5_cosq_sched_mode_setget(unit, port, node->level, l1index - 3,
                        &sched_mode, &weight, 0, 0));
            LOG_CLI((BSL_META_U(unit,
                            "    L1.%d: GPORT=0x%x HW_INDEX=%d MODE=%s WT=%d\n"),
                        l1index - 3, node->gport, node->hw_index,
                        sched_modes[sched_mode], weight));

            if (index == 0) {
                if (l1index == 3) {
                    l2index = 7;
                    l2_max = l2index + 8;
                    l3index = 0;
                    l3_max = l3index + 8;
                } else  if(l1index == 4) {
                    l2index = 15;
                    l2_max = l2index + 8;
                    l3index = 8;
                    l3_max = l3index + 8;
                }
            } else if (index == 1) {
                l2index = 23;
                l2_max = l2index + 8;
                l3index = 16;
                l3_max = l3index + 8;
            } else {
                l2index = 31;
                l2_max = l2index + 2;
                l3index = 24;
                l3_max = l3index + 2;
            }


            for (; l2index < l2_max && l3index < l3_max; l2index++, l3index++) {
                node = &port_info->sched[l2index];
                BCM_IF_ERROR_RETURN(
                        _bcm_hx5_cosq_sched_mode_setget(unit, port, node->level, l2index - 7,
                            &sched_mode, &weight, 0, 0));
                LOG_CLI((BSL_META_U(unit,
                                "       L2.%d: GPORT=0x%x HW_INDEX=%d MODE=%s WT=%d\n"),
                            l2index - 7, node->gport, node->hw_index,
                            sched_modes[sched_mode], weight));

                /* UC Queue */
                node = &port_info->ucast[l3index];
                BCM_IF_ERROR_RETURN(
                        _bcm_hx5_cosq_sched_mode_setget(unit, port, node->level, l3index,
                            &sched_mode, &weight, 0, 0));
                LOG_CLI((BSL_META_U(unit,
                                "           UC.%d: GPORT=0x%x HW_INDEX=%d MODE=%s WT=%d\n"),
                            l3index, node->gport, node->hw_index,
                            sched_modes[sched_mode], weight));

                /* MC Queue */
                node = &port_info->mcast[l3index];
                BCM_IF_ERROR_RETURN(
                        _bcm_hx5_cosq_sched_mode_setget(unit, port, node->level, l3index,
                            &sched_mode, &weight, 1, 0));
                LOG_CLI((BSL_META_U(unit,
                                "           MC.%d: GPORT=0x%x HW_INDEX=%d MODE=%s WT=%d\n"),
                            l3index, node->gport, node->hw_index,
                            sched_modes[sched_mode], weight));
            }
        }
    }
    LOG_CLI((BSL_META_U(unit,
                        "=========== \n")));

    return BCM_E_NONE;
}

STATIC int
_bcm_hx5_cosq_port_info_dump(int unit, bcm_port_t port)
{
    _bcm_hx5_cosq_port_info_t *port_info;
    _bcm_hx5_cosq_node_t *node;
    int index = 0, empty;
    int l1index, l2index, l3index;
    soc_hx5_sched_mode_e sched_mode = 0;
    int weight = 0, port_index;
    char *sched_modes[] = {"X", "SP", "WRR", "WERR"};
    int phy_port, mmu_port;
    soc_info_t *si = &SOC_INFO(unit);


    phy_port = si->port_l2p_mapping[port];
    mmu_port = si->port_p2m_mapping[phy_port];
    _HX5_PORT_INDEX_GET(unit, mmu_port, port_index);

    if (!SOC_PORT_VALID(unit, port)) {
        return BCM_E_PORT;
    }
    port_info = &_bcm_hx5_cosq_port_info[unit][port_index];

    empty = TRUE;
    for (index = 0; index < SOC_HX5_NUM_SCHEDULER_PER_PORT; index++) {
        if (port_info->sched[index].numq > 0) {
            empty = FALSE;
            break;
        }
    }
    if (empty) {
        for (index = 0; index < SOC_HX5_NUM_UCAST_QUEUE_PER_PORT; index++) {
            if (port_info->ucast[index].numq > 0) {
                empty = FALSE;
                break;
            }
        }
    }
    if (empty) {
        for (index = 0; index < SOC_HX5_NUM_MCAST_QUEUE_PER_PORT; index++) {
            if (port_info->mcast[index].numq > 0) {
                empty = FALSE;
                break;
            }
        }
    }

    if (empty == TRUE) {
        return BCM_E_NOT_FOUND;
    }

    LOG_CLI((BSL_META_U(unit,
                        "=== PORT %d\n"), port));

    node = &port_info->sched[index];

    BCM_IF_ERROR_RETURN(
            _bcm_hx5_cosq_sched_mode_setget(unit, port, node->level, index,
                &sched_mode, &weight, 0, 0));
    LOG_CLI((BSL_META_U(unit,
                    "L0.%d: GPORT=0x%x HW_INDEX=%d MODE=%s WT=%d\n"),
                index, node->gport, node->hw_index,
                sched_modes[sched_mode], weight));

    for (l1index = 1; l1index < 3; l1index++) {
        /* Node */
        node = &port_info->sched[l1index];

        BCM_IF_ERROR_RETURN(
                _bcm_hx5_cosq_sched_mode_setget(unit, port, node->level, l1index - 1,
                    &sched_mode, &weight, 0, 0));
        LOG_CLI((BSL_META_U(unit,
                        "    L1.%d: GPORT=0x%x HW_INDEX=%d MODE=%s WT=%d\n"),
                    l1index - 1, node->gport, node->hw_index,
                    sched_modes[sched_mode], weight));

        l2index = ((l1index - 1) * 8) + 3;
        l3index = ((l1index - 1) * 8);

        for (; l2index < ((l1index - 1) * 8) + 11 && l3index < ((l1index - 1) * 8) + 8; l2index++, l3index++) {
            node = &port_info->sched[l2index];

            BCM_IF_ERROR_RETURN(
                    _bcm_hx5_cosq_sched_mode_setget(unit, port, node->level, l2index - 3,
                        &sched_mode, &weight, 0, 0));
            LOG_CLI((BSL_META_U(unit,
                            "       L2.%d: GPORT=0x%x HW_INDEX=%d MODE=%s WT=%d\n"),
                        l2index - 3, node->gport, node->hw_index,
                        sched_modes[sched_mode], weight));

                /* UC Queue */
                node = &port_info->ucast[l3index];
                BCM_IF_ERROR_RETURN(
                        _bcm_hx5_cosq_sched_mode_setget(unit, port, node->level, l3index,
                            &sched_mode, &weight, 0, 0));
                LOG_CLI((BSL_META_U(unit,
                                "          UC.%d: GPORT=0x%x HW_INDEX=%d MODE=%s WT=%d\n"),
                            l3index, node->gport, node->hw_index,
                            sched_modes[sched_mode], weight));

                /* MC Queue */
                node = &port_info->mcast[l3index];
                BCM_IF_ERROR_RETURN(
                        _bcm_hx5_cosq_sched_mode_setget(unit, port, node->level, l3index,
                            &sched_mode, &weight, 1, 0));
                LOG_CLI((BSL_META_U(unit,
                                "          MC.%d: GPORT=0x%x HW_INDEX=%d MODE=%s WT=%d\n"),
                            l3index, node->gport, node->hw_index,
                            sched_modes[sched_mode], weight));
        }
    }
    LOG_CLI((BSL_META_U(unit,
                        "=========== \n")));

    return BCM_E_NONE;
}

int
bcm_hx5_dump_port_hsp(int unit, int port)
{
    int phy_port, mmu_port;
    soc_info_t *si = &SOC_INFO(unit);
    LOG_CLI((BSL_META_U(unit,
                    "\nSW Information COSQ - Unit %d\n"), unit));
    if (!IS_FAE_PORT(unit, port) && !IS_LB_PORT(unit, port)) {
        phy_port = si->port_l2p_mapping[port];
        mmu_port = si->port_p2m_mapping[phy_port];
        if (IS_CPU_PORT(unit, port)) {
            (void)_bcm_hx5_cosq_cpu_port_info_dump(unit);
        }
        if(_HX5_IS_ST_PORT(unit, mmu_port)) {
            (void)_bcm_hx5_cosq_st_port_info_dump(unit, port);
        } else {
            (void)_bcm_hx5_cosq_port_info_dump(unit, port);
        }
    }
    return BCM_E_NONE;
}
/*
 * Function:
 *     bcm_hx5_cosq_sw_dump
 * Purpose:
 *     Displays COS Queue information maintained by software.
 * Parameters:
 *     unit - Device unit number
 * Returns:
 *     None
 */
void
bcm_hx5_cosq_sw_dump(int unit)
{
    bcm_port_t port;
    int phy_port, mmu_port;
    soc_info_t *si = &SOC_INFO(unit);
    LOG_CLI((BSL_META_U(unit,
                        "\nSW Information COSQ - Unit %d\n"), unit));

    PBMP_ALL_ITER(unit, port) {
        phy_port = si->port_l2p_mapping[port];
        mmu_port = si->port_p2m_mapping[phy_port];
        if (IS_CPU_PORT(unit, port)) {
            (void)_bcm_hx5_cosq_cpu_port_info_dump(unit);
        }
        if(_HX5_IS_ST_PORT(unit, mmu_port)) {
            (void)_bcm_hx5_cosq_st_port_info_dump(unit, port);
        } else {
            (void)_bcm_hx5_cosq_port_info_dump(unit, port);
        }
    }
    return;
}

int
bcm_hx5_hgcos_select_port_control_set(int unit,  bcm_port_t port,
                                      bcm_port_control_t type, int value)
{
    soc_info_t *si;
    int phy_port, mmu_port;
    uint64 rval64, rval64_tmp, rval64_reset_tmp;
    uint32 rval;
    soc_reg_t reg = UC_HG_QUEUE_MODEr;
    soc_field_t field = QUEUE_MODEf;
    soc_reg_t reg1 = COS_MODE_SPLIT0r;
    si = &SOC_INFO(unit);
    phy_port = si->port_l2p_mapping[port];
    mmu_port = si->port_p2m_mapping[phy_port];

    if ((value < 0) || (value > 1)) {
        return BCM_E_PARAM;
    }
    COMPILER_64_ZERO(rval64);
    COMPILER_64_ZERO(rval64_tmp);
    COMPILER_64_ZERO(rval64_reset_tmp);

    if (IS_CPU_PORT(unit, port) || IS_LB_PORT(unit, port) ||
        IS_FAE_PORT(unit, port) || !_HX5_IS_ST_PORT(unit, mmu_port)) {
        return BCM_E_PARAM;
    }
    BCM_IF_ERROR_RETURN
        (soc_reg32_get(unit, reg, port, 0, &rval));

    soc_reg_field_set(unit, reg, &rval, field, value);

    BCM_IF_ERROR_RETURN
        (soc_reg32_set(unit, reg, port, 0, rval));

    SOC_IF_ERROR_RETURN
        (soc_trident3_xpe_reg_get(unit, reg1, -1, 0, 0, &rval64));
    COMPILER_64_SET(rval64_tmp, 0, (2 << (mmu_port * 2)));
    COMPILER_64_SET(rval64_reset_tmp, 0, (3 << (mmu_port * 2)));

    if (value) {
        COMPILER_64_OR(rval64, rval64_tmp);
    } else {
        COMPILER_64_NOT(rval64_reset_tmp);
        COMPILER_64_AND(rval64, rval64_reset_tmp);

    }
    SOC_IF_ERROR_RETURN
        (soc_trident3_xpe_reg_set(unit, reg1, -1, 0, 0, rval64));
   return BCM_E_NONE;
}

int 
bcm_hx5_hgcos_select_port_control_get(int unit,  bcm_port_t port,
                                      bcm_port_control_t type, int *value)
{
    soc_info_t *si;
    int phy_port, mmu_port;
    uint32 rval;
    soc_reg_t reg = UC_HG_QUEUE_MODEr;
    soc_field_t field = QUEUE_MODEf;
    si = &SOC_INFO(unit);
    phy_port = si->port_l2p_mapping[port];
    mmu_port = si->port_p2m_mapping[phy_port];

    if (IS_CPU_PORT(unit, port) || IS_LB_PORT(unit, port) ||
        IS_FAE_PORT(unit, port) || !_HX5_IS_ST_PORT(unit, mmu_port)) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (soc_reg32_get(unit, reg, port, 0, &rval));

   *value =  soc_reg_field_get(unit, reg, rval, field);

   return BCM_E_NONE;
}

int
bcm_hx5_cosq_gport_info_get(int unit, bcm_gport_t gport,
                                    bcm_cosq_gport_level_info_t *info)
{

    int phy_port, mmu_port, local_port;
    _bcm_hx5_cosq_node_t *node = NULL;
    soc_info_t *si;

    if( NULL == info ) {
        return BCM_E_PARAM;
    }

    if (!BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport) &&
            !BCM_GPORT_IS_SCHEDULER(gport) &&
            !BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport)) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_node_get(unit, gport, NULL,
                                &local_port, NULL, &node));

    si = &SOC_INFO(unit);
    phy_port = si->port_l2p_mapping[local_port];
    mmu_port = si->port_p2m_mapping[phy_port];

    info->parent_port_type = (mmu_port < 16) ? BCM_COSQ_UPLINK_GPORT : BCM_COSQ_DOWNLINK_GPORT;
    info->level = node->level;

    return BCM_E_NONE;
}
/* Routine to perform Inverse mapping for given Queue port back to Port/Priority
 * which was defined by default or through cosq_mapping_set functions
 */
int
_bcm_hx5_cosq_inv_mapping_get(int unit, bcm_gport_t gport,
                             bcm_cos_queue_t cosq,
                             uint32 flags, bcm_port_t *ing_port,
                             bcm_cos_t *priority)
{
    bcm_port_t local_port;
    cos_map_sel_entry_t cos_map_sel_entry;
    void *entries[1];
    int index, ii;
    bcm_cos_queue_t in_cosq = BCM_COS_INVALID, pri_cosq = BCM_COS_INVALID;
    bcm_module_t    modid;
    soc_field_t cos_field = INVALIDf;
    port_cos_map_entry_t cos_map_entries[_HX5_MMU_NUM_INT_PRI];

    if ((flags != BCM_COSQ_GPORT_UCAST_QUEUE_GROUP) &&
       (flags != BCM_COSQ_GPORT_MCAST_QUEUE_GROUP)) {
        return BCM_E_PARAM;
    }

    if ((ing_port == NULL) || (priority == NULL)) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_SET(gport)) {
        if (!(BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) &&
            !(BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport))) {
            return BCM_E_PARAM;
        }
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_node_get(unit, gport, &modid, &local_port,
                                   &in_cosq, NULL));
    } else {
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_localport_resolve(unit, gport, &local_port));
        in_cosq = cosq;
    }

    if ((cosq < -1) || (cosq >= _HX5_PORT_NUM_COS(unit, local_port))) {
        return BCM_E_PARAM;
    }

    if ((IS_CPU_PORT(unit, local_port)) || (IS_LB_PORT(unit, local_port))) {
        return BCM_E_PARAM;
    }

    *ing_port = local_port;

    if (flags == BCM_COSQ_GPORT_MCAST_QUEUE_GROUP) {
        cos_field = MC_COS1f;
    } else {
        cos_field = UC_COS1f;
    }

    if (in_cosq == BCM_COS_INVALID) {
        return BCM_E_PARAM;
    } else {
        in_cosq %= _BCM_HX5_NUM_PFC_CLASS;
    }

    entries[0] = &cos_map_entries;
    BCM_IF_ERROR_RETURN
        (READ_COS_MAP_SELm(unit, MEM_BLOCK_ANY, local_port,
                           &cos_map_sel_entry));
    index = soc_mem_field32_get(unit, COS_MAP_SELm, &cos_map_sel_entry,
                                SELECTf);
    index *= _HX5_MMU_NUM_INT_PRI;

    BCM_IF_ERROR_RETURN
        (soc_profile_mem_get(unit, _bcm_hx5_cos_map_profile[unit],
                             index, _HX5_MMU_NUM_INT_PRI, entries));

    for (ii = 0; ii < _HX5_MMU_NUM_INT_PRI; ii++) {
        pri_cosq = soc_mem_field32_get(unit, PORT_COS_MAPm,
                                       &cos_map_entries[ii], cos_field);
        if (pri_cosq == in_cosq) {
            /* Required Cosq found. Break as the index is the priority */
            *priority = ii;
            break;
        }
    }

    if (ii == _HX5_MMU_NUM_INT_PRI) {
        /* Mapping cannot be found */
        return BCM_E_NOT_FOUND;
    }

    return BCM_E_NONE;
}

int
bcm_hx5_pfc_deadlock_queue_info_get(int unit, bcm_gport_t gport,
                                    bcm_port_t *mmu_port, bcm_port_t *local_port, int *type, int *split)
{
    soc_info_t *si;
    int pport = 0, mport = 0, lport = 0, in_cosq = 0;
    bcm_module_t    modid;
    si = &SOC_INFO(unit);

    if ((mmu_port == NULL) || (split == NULL) || (local_port == NULL) || (type == NULL)) {
        return BCM_E_PARAM;
    }

    if (BCM_GPORT_IS_SET(gport)) {
        if (!(BCM_GPORT_IS_UCAST_QUEUE_GROUP(gport)) &&
            !(BCM_GPORT_IS_MCAST_QUEUE_GROUP(gport))) {
            return BCM_E_PARAM;
        }
        BCM_IF_ERROR_RETURN
            (_bcm_hx5_cosq_node_get(unit, gport, &modid, &lport,
                                   &in_cosq, NULL));
   }
   pport = si->port_l2p_mapping[lport];
   mport = si->port_p2m_mapping[pport];

   *split = (mport > 15) ? 0 : 1;
   *mmu_port = mport;
   *local_port = lport;
   *type = (in_cosq < 8) ? 0 : (in_cosq >= 8 && in_cosq < 16) ? 1 : 2;

   return BCM_E_NONE;
}

int
bcm_hx5_pfc_deadlock_ignore_pfc_xoff_gen(int unit, int priority,
                                        bcm_port_t port, uint32 *rval32)
{
    uint32 profile_index, fc_class;
    uint32 rval, uc_cos_bmp;
    uint64 rval64[16], *rval64s[1];
    static const soc_reg_t port_fc_reg = PORT_LLFC_CFGr;

    rval64s[0] = rval64;
    BCM_IF_ERROR_RETURN
        (soc_reg32_get(unit, port_fc_reg, port, 0, &rval));
    profile_index = soc_reg_field_get(unit, port_fc_reg, rval, PROFILE_INDEXf) * 16;

    BCM_IF_ERROR_RETURN
        (soc_profile_reg_get(unit, _bcm_hx5_prio2cos_profile[unit],
                             profile_index, 16, rval64s));

    for (fc_class = 0; fc_class < _BCM_HX5_NUM_PFC_CLASS; ++fc_class ) {

        uc_cos_bmp = soc_reg64_field32_get(unit, PRIO2COS_PROFILE_64r, rval64[fc_class],
                                           UC_COS_BMPf);
        if (uc_cos_bmp & (1 << priority)) {
            *rval32 = uc_cos_bmp;
            return BCM_E_NONE;
        }
    }

    return BCM_E_NOT_FOUND;
}

/*
 *  Function:
 *      bcm_hx5_pfc_deadlock_recovery_start
 *  Purpose:
 *      Begin recovery when a Port is deaclared to be in Deadlock by Hardware
 *  Parameters:
 *      unit - unit number
 *      port - port number
 *      priority - priority
 *  Returns:
 *      BCM_E_XXX
 * */
int
bcm_hx5_pfc_deadlock_recovery_start(int unit, bcm_port_t port, int priority)
{
    int pipe, split, pos, cos = 0, index;
    uint32 rval = 0, uc_cos_bmp = 0;
    uint64 rval64, temp_mask64, temp_en64;
    _bcm_hx5_pfc_hw_resorces_t *hw_res = NULL; 
    _bcm_hx5_pfc_deadlock_control_t *pfc_deadlock_control = NULL; 

    if ((priority < 0) || (priority >= HX5_PFC_DEADLOCK_MAX_COS)) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN(
            _bcm_hx5_cosq_localport_resolve(unit, port, &port));
    if (port >= MAX_PORT(unit)) {
        return BCM_E_PARAM;
    }

    pfc_deadlock_control = _BCM_HX5_UNIT_PFC_DEADLOCK_CONTROL(unit);
    hw_res = &pfc_deadlock_control->hw_regs_fields;
    SOC_IF_ERROR_RETURN(
            soc_td3_mmu_bmp_reg_pos_get(unit, port, &pipe, &split, &pos));

    BCM_IF_ERROR_RETURN(
            _bcm_hx5_pfc_reg_index_get(unit, port, NULL, &index));

    COMPILER_64_ZERO(temp_en64);
    COMPILER_64_ZERO(temp_mask64);

    if (pos < 32) {
       COMPILER_64_SET(temp_mask64, 0, (1 << pos));
    } else {
        COMPILER_64_SET(temp_mask64, (1 << (pos - 32)), 0);
    }

    COMPILER_64_OR(temp_en64, temp_mask64);

    BCM_IF_ERROR_RETURN(
            _bcm_hx5_pfc_deadlock_hw_cos_index_get(unit, priority, &cos));

    /* Mask the Intr DD_TIMER_MASK by setting 1 (pbmp) */
    COMPILER_64_ZERO(rval64);
    SOC_IF_ERROR_RETURN(
            soc_trident3_xpe_reg_get(unit, hw_res->timer_mask[split], -1, pipe,
                cos, &rval64));
    COMPILER_64_OR(rval64, temp_mask64);
    SOC_IF_ERROR_RETURN(
            soc_trident3_xpe_reg_set(unit, hw_res->timer_mask[split], -1, pipe,
                cos, rval64));

    SOC_IF_ERROR_RETURN(
            soc_reg32_get(unit, hw_res->port_config[index], port, 0, &rval));
    priority = pfc_deadlock_control->pfc_cos2pri[cos];

    rval = _bcm_pfc_deadlock_ignore_pfc_xoff_gen(unit, priority, port,
            &uc_cos_bmp);
    if (rval != BCM_E_NONE) {
        rval = 0;
        rval |= (1 << priority);
    } else {
        rval = 0;
        rval |= uc_cos_bmp;
    }

    SOC_IF_ERROR_RETURN(
            soc_reg32_set(unit, hw_res->port_config[index], port, 0, rval));

    return BCM_E_NONE;
}

/*
 * Function:
 *    bcm_hx5_pfc_deadlock_recovery_exit
 * Purpose:
 *      Reset recovery state of a port and config port back in original state
 * Parameters:
 *      unit - unit number
 *      port - port number
 *      priority - priority
 * Returns:
 *      BCM_E_XXX
 * */
    int
bcm_hx5_pfc_deadlock_recovery_exit(int unit, bcm_port_t port, int priority)
{
    int pipe, split, pos, cos = 0, index;
    uint32 rval = 0, uc_cos_bmp = 0;
    uint64 rval64, temp_mask64, temp_en64;
    _bcm_hx5_pfc_hw_resorces_t *hw_res = NULL;
    _bcm_hx5_pfc_deadlock_control_t *pfc_deadlock_control = NULL;

    if ((priority < 0) || (priority >= HX5_PFC_DEADLOCK_MAX_COS)) {
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN(
            _bcm_hx5_cosq_localport_resolve(unit, port, &port));
    if (port >= MAX_PORT(unit)) {
        return BCM_E_PARAM;
    }

    pfc_deadlock_control = _BCM_HX5_UNIT_PFC_DEADLOCK_CONTROL(unit);
    hw_res = &pfc_deadlock_control->hw_regs_fields;
    SOC_IF_ERROR_RETURN(
            soc_td3_mmu_bmp_reg_pos_get(unit, port, &pipe, &split, &pos));

    COMPILER_64_ZERO(temp_en64);
    COMPILER_64_ZERO(temp_mask64);

    if (pos < 32) {
        COMPILER_64_SET(temp_mask64, 0, (1 << pos));
    } else {
        COMPILER_64_SET(temp_mask64, (1 << (pos - 32)), 0);
    }

    COMPILER_64_OR(temp_en64, temp_mask64);

    BCM_IF_ERROR_RETURN(
            _bcm_hx5_pfc_deadlock_hw_cos_index_get(unit, priority, &cos));

    BCM_IF_ERROR_RETURN(
            _bcm_hx5_pfc_reg_index_get(unit, port, NULL, &index));
    /* For that port, set ignore_pfc_xoff = 0 (per port reg) */
    SOC_IF_ERROR_RETURN(
            soc_reg32_get(unit, hw_res->port_config[index], port, 0, &rval));

    rval = _bcm_pfc_deadlock_ignore_pfc_xoff_gen(unit, priority, port,
            &uc_cos_bmp);
    if (rval != BCM_E_NONE) {
        rval = 0;
        rval &= ~(1 << priority);
    } else {
        rval = 0;
        rval &= ~uc_cos_bmp;
    }

    SOC_IF_ERROR_RETURN(
            soc_reg32_set(unit, hw_res->port_config[index], port, 0, rval));

    /* Mask the Intr DD_TIMER_MASK by setting 0 (pbmp) */
    COMPILER_64_ZERO(rval64);
    SOC_IF_ERROR_RETURN(
            soc_trident3_xpe_reg_get(unit, hw_res->timer_mask[split], -1, pipe,
                cos, &rval64));
    COMPILER_64_NOT(temp_mask64);
    COMPILER_64_AND(rval64, temp_mask64);
    SOC_IF_ERROR_RETURN(
            soc_trident3_xpe_reg_set(unit, hw_res->timer_mask[split], -1, pipe,
                cos, rval64));

    /* Turn timer on DD_TIMER_ENABLE  by setting 1 (pbmp) */
    COMPILER_64_ZERO(rval64);
    SOC_IF_ERROR_RETURN(
            soc_trident3_xpe_reg_get(unit, hw_res->timer_en[split], -1, pipe,
                cos, &rval64));
    COMPILER_64_OR(rval64, temp_en64);
    SOC_IF_ERROR_RETURN(
            soc_trident3_xpe_reg_set(unit, hw_res->timer_en[split], -1, pipe,
                cos, rval64));

    return BCM_E_NONE;
}



/* Function:
 *      bcmi_hx5_port_cosmap_update
 *  Purpose:
 *     called during flexport during port attach/detach
 *     to update the cos_map profile for the port
 *  Parameters:
 *      unit   - unit number
 *      port   - port number
 *      enable - add/delete
 *  Returns:
 *      BCM_E_XXX
 */

int
bcmi_hx5_port_cosmap_update(int unit, pbmp_t pbm, int enable)
{
    port_cos_map_entry_t cos_map_entries[16];
    cos_map_sel_entry_t cos_map_sel_entry;
    void *entries[1];
    uint32 index, old_index;
    bcm_port_t port;
    int cos, prio, numq, rv;
    soc_mem_t mem = PORT_COS_MAPm;
    uint32 i;

    numq = _BCM_HX5_NUM_COS(unit);

    SOC_PBMP_ITER(pbm, port) {
        prio = 0;
        sal_memset(cos_map_entries, 0, sizeof(cos_map_entries));
        entries[0] = &cos_map_entries;

        if (enable) {
            /*
             * Distribute first 8 internal priority levels into the specified number
             * of cosq, map remaining internal priority levels to highest priority
             * cosq
             * */
            sal_memset(cos_map_entries, 0, sizeof(cos_map_entries));
            entries[0] = &cos_map_entries;

            for (cos = 0; cos < numq; cos++) {
                for (i = 8 / numq + (cos < 8 % numq ? 1 : 0); i > 0; i--) {
                    soc_mem_field32_set(unit, mem, &cos_map_entries[prio],
                            UC_COS1f, cos);
                    soc_mem_field32_set(unit, mem, &cos_map_entries[prio],
                            MC_COS1f, cos);
                    soc_mem_field32_set(unit, mem, &cos_map_entries[prio],
                            HG_COSf, _HX5_NUM_COS_MAP_ENTRY + cos);
                    prio++;
                }
            }
            for (prio = 8; prio < 16; prio++) {
                soc_mem_field32_set(unit, mem, &cos_map_entries[prio], UC_COS1f,
                        numq - 1);
                soc_mem_field32_set(unit, mem, &cos_map_entries[prio], MC_COS1f,
                        numq - 1);
                soc_mem_field32_set(unit, mem, &cos_map_entries[prio], HG_COSf,
                        _HX5_NUM_COS_MAP_ENTRY + (numq - 1));
            }

            SOC_IF_ERROR_RETURN
                (soc_profile_mem_add(unit, _bcm_hx5_cos_map_profile[unit], entries, 16,
                                     &index));
            BCM_IF_ERROR_RETURN(bcm_hx5_wireless_cos_map_update(unit, numq));
            BCM_IF_ERROR_RETURN
                (soc_mem_field32_modify(unit, COS_MAP_SELm, port, SELECTf,
                                        index / 16));

        } else {
            BCM_IF_ERROR_RETURN
                (READ_COS_MAP_SELm(unit, MEM_BLOCK_ANY, port, &cos_map_sel_entry));
            old_index = soc_mem_field32_get(unit, COS_MAP_SELm, &cos_map_sel_entry,
                    SELECTf);
            old_index *= 16;

            rv = soc_profile_mem_delete(unit, _bcm_hx5_cos_map_profile[unit],
                    old_index);

            if (BCM_FAILURE(rv)) {
                return rv;
            }
        }
    }
    return BCM_E_NONE;
}

/*
 * Function:
 *    bcm_cosq_gport_traverse_by_port
 * Purpose:
 *     Walks through the valid COSQ GPORTs belong to a port and calls
 *     the user supplied callback function for each entry.
 * Parameters:
 *     unit       - (IN) unit number
 *     port       - (IN) port number or GPORT identifier
 *     trav_fn    - (IN) Callback function.
 *     user_data  - (IN) User data to be passed to callback function
 * Returns:
 *     BCM_E_NONE - Success.
 *     BCM_E_XXX
 * */

int
bcm_hx5_cosq_gport_traverse_by_port(int unit, bcm_gport_t port,
                            bcm_cosq_gport_traverse_cb cb,
                            void *user_data)
{
    _bcm_hx5_cosq_port_info_t *port_info = NULL;
    _bcm_hx5_cosq_st_port_info_t *stport_info = NULL;
    _bcm_hx5_cosq_cpu_port_info_t *cpu_port_info = NULL;
    bcm_module_t my_modid, modid_out;
    bcm_port_t port_out, local_port;
    bcm_gport_t gport;
    int id, rv = SOC_E_NONE;
    int phy_port, mmu_port, index;

    soc_info_t *si = &SOC_INFO(unit);

    if (_bcm_hx5_cosq_port_info[unit] == NULL) {
        return BCM_E_INIT;
    }
    if (_bcm_hx5_cosq_st_port_info[unit] == NULL) {
        return BCM_E_INIT;
    }
    if (_bcm_hx5_cosq_cpu_port_info[unit] == NULL) {
        return BCM_E_INIT;
    }

    if (BCM_GPORT_IS_SET(port) &&
            (!BCM_GPORT_IS_LOCAL(port) &&
             !BCM_GPORT_IS_DEVPORT(port) &&
             !BCM_GPORT_IS_MODPORT(port))) {
        LOG_ERROR(BSL_LS_BCM_COSQ, (BSL_META_U(unit,
                        "Invalid gport type\n")));
        return BCM_E_PARAM;
    }

    BCM_IF_ERROR_RETURN
        (_bcm_hx5_cosq_localport_resolve(unit, port, &local_port));


    BCM_IF_ERROR_RETURN(bcm_esw_stk_my_modid_get(unit, &my_modid));
    BCM_IF_ERROR_RETURN
        (_bcm_esw_stk_modmap_map(unit, BCM_STK_MODMAP_GET, my_modid,  port,
                                 &modid_out, &port_out));
    BCM_GPORT_MODPORT_SET(gport, modid_out, port_out);

    phy_port = si->port_l2p_mapping[local_port];
    mmu_port = si->port_p2m_mapping[phy_port];
    _HX5_PORT_INDEX_GET(unit, mmu_port, index);
    if (IS_CPU_PORT(unit, local_port)) {
        cpu_port_info = _bcm_hx5_cosq_cpu_port_info[unit];
    } else {
        if(_HX5_IS_ST_PORT(unit, mmu_port)) {
            stport_info = &_bcm_hx5_cosq_st_port_info[unit][index];
        }else {
            port_info = &_bcm_hx5_cosq_port_info[unit][index];
        }
    }

    if (!IS_CPU_PORT(unit, local_port) && !_HX5_IS_ST_PORT(unit, mmu_port)) {
        for (id = 0; id < SOC_HX5_NUM_UCAST_QUEUE_PER_PORT; id++) {
            if (port_info->ucast[id].numq == 0) {
                continue;
            }
            rv = cb(unit, gport, port_info->ucast[id].numq,
                    BCM_COSQ_GPORT_UCAST_QUEUE_GROUP,
                    port_info->ucast[id].gport, user_data);
        }
#ifdef BCM_CB_ABORT_ON_ERR
        if (BCM_FAILURE(rv) && SOC_CB_ABORT_ON_ERR(unit)) {
            return rv;
        }
#else
        rv = BCM_E_NONE;
#endif
    }

    if (!IS_CPU_PORT(unit, local_port) && _HX5_IS_ST_PORT(unit, mmu_port)) {
        for (id = 0; id < SOC_HX5_NUM_UCAST_QUEUE_PER_ST_PORT; id++) {
            if (stport_info->ucast[id].numq == 0) {
                continue;
            }
            rv = cb(unit, gport, stport_info->ucast[id].numq,
                    BCM_COSQ_GPORT_UCAST_QUEUE_GROUP,
                    stport_info->ucast[id].gport, user_data);
        }
#ifdef BCM_CB_ABORT_ON_ERR
        if (BCM_FAILURE(rv) && SOC_CB_ABORT_ON_ERR(unit)) {
            return rv;
        }
#else
        rv = BCM_E_NONE;
#endif
    }

    if (IS_CPU_PORT(unit, local_port)) {
        for (id = 0; id < SOC_HX5_NUM_CPU_QUEUES; id++) {
            if (cpu_port_info->mcast[id].numq == 0) {
                continue;
            }
            rv = cb(unit, gport, cpu_port_info->mcast[id].numq,
                    BCM_COSQ_GPORT_MCAST_QUEUE_GROUP,
                    cpu_port_info->mcast[id].gport, user_data);
#ifdef BCM_CB_ABORT_ON_ERR
            if (BCM_FAILURE(rv) && SOC_CB_ABORT_ON_ERR(unit)) {
                return rv;
            }
#else
            rv = BCM_E_NONE;
#endif
        }
    }

    if (!IS_CPU_PORT(unit, local_port) && !_HX5_IS_ST_PORT(unit, mmu_port)) {
        for (id = 0; id < SOC_HX5_NUM_MCAST_QUEUE_PER_PORT; id++) {
            if (port_info->mcast[id].numq == 0) {
                continue;
            }
            rv = cb(unit, gport, port_info->mcast[id].numq,
                    BCM_COSQ_GPORT_MCAST_QUEUE_GROUP,
                    port_info->mcast[id].gport, user_data);
        }
#ifdef BCM_CB_ABORT_ON_ERR
        if (BCM_FAILURE(rv) && SOC_CB_ABORT_ON_ERR(unit)) {
            return rv;
        }
#else
        rv = BCM_E_NONE;
#endif
    }


    if (!IS_CPU_PORT(unit, local_port) && _HX5_IS_ST_PORT(unit, mmu_port)) {
        for (id = 0; id < SOC_HX5_NUM_MCAST_QUEUE_PER_ST_PORT; id++) {
            if (stport_info->mcast[id].numq == 0) {
                continue;
            }
            rv = cb(unit, gport, stport_info->mcast[id].numq,
                    BCM_COSQ_GPORT_MCAST_QUEUE_GROUP,
                    stport_info->mcast[id].gport, user_data);
        }
#ifdef BCM_CB_ABORT_ON_ERR
        if (BCM_FAILURE(rv) && SOC_CB_ABORT_ON_ERR(unit)) {
            return rv;
        }
#else
        rv = BCM_E_NONE;
#endif
    }


    if (IS_CPU_PORT(unit, local_port)) {
        for (id = 0; id < SOC_HX5_NUM_SCHEDULER_PER_CPU_PORT; id++) {
            if (cpu_port_info->sched[id].numq == 0) {
                continue;
            }
            rv = cb(unit, gport, cpu_port_info->sched[id].numq,
                    BCM_COSQ_GPORT_SCHEDULER,
                    cpu_port_info->sched[id].gport, user_data);
#ifdef BCM_CB_ABORT_ON_ERR
            if (BCM_FAILURE(rv) && SOC_CB_ABORT_ON_ERR(unit)) {
                return rv;
            }
#else
            rv = BCM_E_NONE;
#endif
        }
    }

    if (!IS_CPU_PORT(unit, local_port) && !_HX5_IS_ST_PORT(unit, mmu_port)) {
        for (id = 0; id < SOC_HX5_NUM_SCHEDULER_PER_PORT; id++) {
            if (port_info->sched[id].numq == 0) {
                continue;
            }
            rv = cb(unit, gport, port_info->sched[id].numq,
                    BCM_COSQ_GPORT_SCHEDULER,
                    port_info->sched[id].gport, user_data);
        }
#ifdef BCM_CB_ABORT_ON_ERR
        if (BCM_FAILURE(rv) && SOC_CB_ABORT_ON_ERR(unit)) {
            return rv;
        }
#else
        rv = BCM_E_NONE;
#endif
    }


    if (!IS_CPU_PORT(unit, local_port) && _HX5_IS_ST_PORT(unit, mmu_port)) {
        for (id = 0; id < SOC_HX5_NUM_SCHEDULER_PER_ST_PORT; id++) {
            if (stport_info->sched[id].numq == 0) {
                continue;
            }
            rv = cb(unit, gport, stport_info->sched[id].numq,
                    BCM_COSQ_GPORT_SCHEDULER,
                    stport_info->sched[id].gport, user_data);
        }
#ifdef BCM_CB_ABORT_ON_ERR
        if (BCM_FAILURE(rv) && SOC_CB_ABORT_ON_ERR(unit)) {
            return rv;
        }
#else
        rv = BCM_E_NONE;
#endif
    }

    return rv;

}
STATIC int
bcm_hx5_obm_dscp_classifier_mapping_multi_set(int unit, int obm,
        int lane, int pipe, int array_count,
        bcm_switch_obm_classifier_t *switch_obm_classifier)
{
    int                             i, code_point, ob_priority;
    int                             entry_index[4];
    idb_obm0_dscp_map_port0_entry_t entry[4];
    bcm_switch_obm_classifier_t     *classifier_ptr = NULL;
    soc_mem_t                       mem;

    static const soc_mem_t obm_dscp_map_port_mem[][4] = {
        /* PM4x10Q*/
        {IDB_OBM0_Q_DSCP_MAP_PORT0m, IDB_OBM0_Q_DSCP_MAP_PORT1m,
        IDB_OBM0_Q_DSCP_MAP_PORT2m, IDB_OBM0_Q_DSCP_MAP_PORT3m
        },
        {IDB_OBM1_Q_DSCP_MAP_PORT0m, IDB_OBM1_Q_DSCP_MAP_PORT1m,
        IDB_OBM1_Q_DSCP_MAP_PORT2m, IDB_OBM1_Q_DSCP_MAP_PORT3m
        },
        {IDB_OBM2_Q_DSCP_MAP_PORT0m, IDB_OBM2_Q_DSCP_MAP_PORT1m,
        IDB_OBM2_Q_DSCP_MAP_PORT2m, IDB_OBM2_Q_DSCP_MAP_PORT3m
        },
        /* PM4x10 */
        {IDB_OBM0_DSCP_MAP_PORT0m, IDB_OBM0_DSCP_MAP_PORT1m,
        IDB_OBM0_DSCP_MAP_PORT2m, IDB_OBM0_DSCP_MAP_PORT3m
        },
        {IDB_OBM1_DSCP_MAP_PORT0m, IDB_OBM1_DSCP_MAP_PORT1m,
        IDB_OBM1_DSCP_MAP_PORT2m, IDB_OBM1_DSCP_MAP_PORT3m
        },
        {IDB_OBM2_DSCP_MAP_PORT0m, IDB_OBM2_DSCP_MAP_PORT1m,
        IDB_OBM2_DSCP_MAP_PORT2m, IDB_OBM2_DSCP_MAP_PORT3m
        },
        {IDB_OBM3_DSCP_MAP_PORT0m, IDB_OBM3_DSCP_MAP_PORT1m,
        IDB_OBM3_DSCP_MAP_PORT2m, IDB_OBM3_DSCP_MAP_PORT3m
        },
        /* PM4x25 */
        {IDB_OBM0_48_DSCP_MAP_PORT0m, IDB_OBM0_48_DSCP_MAP_PORT1m,
        IDB_OBM0_48_DSCP_MAP_PORT2m, IDB_OBM0_48_DSCP_MAP_PORT3m
        },
        {IDB_OBM1_48_DSCP_MAP_PORT0m, IDB_OBM1_48_DSCP_MAP_PORT1m,
        IDB_OBM1_48_DSCP_MAP_PORT2m, IDB_OBM1_48_DSCP_MAP_PORT3m
        },
        {IDB_OBM2_48_DSCP_MAP_PORT0m, IDB_OBM2_48_DSCP_MAP_PORT1m,
        IDB_OBM2_48_DSCP_MAP_PORT2m, IDB_OBM2_48_DSCP_MAP_PORT3m
        }
    };

    static const soc_field_t offset_ob_prio[] = {
        OFFSET0_OB_PRIORITYf, OFFSET1_OB_PRIORITYf, OFFSET2_OB_PRIORITYf,
        OFFSET3_OB_PRIORITYf, OFFSET4_OB_PRIORITYf, OFFSET5_OB_PRIORITYf,
        OFFSET6_OB_PRIORITYf, OFFSET7_OB_PRIORITYf, OFFSET8_OB_PRIORITYf,
        OFFSET9_OB_PRIORITYf, OFFSET10_OB_PRIORITYf, OFFSET11_OB_PRIORITYf,
        OFFSET12_OB_PRIORITYf, OFFSET13_OB_PRIORITYf, OFFSET14_OB_PRIORITYf,
        OFFSET15_OB_PRIORITYf
    };

    mem = SOC_MEM_UNIQUE_ACC(unit, obm_dscp_map_port_mem[obm][lane])[pipe];
    for (i = 0; i < 4; i++) {
         entry_index[i] = 0;
         sal_memset(&entry[i], 0, sizeof(entry[i]));
         SOC_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, i,
                                          &entry[i]));
    }

    for (i = 0; i < array_count; i++) {
         classifier_ptr = switch_obm_classifier + i;
         code_point = classifier_ptr->obm_code_point;
         ob_priority = classifier_ptr->obm_priority;
         if (code_point < BCM_OBM_DSCP_CHUNK_SIZE) {
             soc_mem_field32_set(unit, mem, &entry[0],
                                 offset_ob_prio[code_point], ob_priority);
             entry_index[0] = 1;
         } else if (code_point < 2 * BCM_OBM_DSCP_CHUNK_SIZE ) {
             soc_mem_field32_set(unit, mem, &entry[1],
                                 offset_ob_prio[code_point % BCM_OBM_DSCP_CHUNK_SIZE],
                                 ob_priority);
            entry_index[1] = 1;
         } else if (code_point < 3 * BCM_OBM_DSCP_CHUNK_SIZE) {
             soc_mem_field32_set(unit, mem, &entry[2],
                                 offset_ob_prio[code_point % BCM_OBM_DSCP_CHUNK_SIZE],
                                 ob_priority);
             entry_index[2] = 1;
         } else {
             soc_mem_field32_set(unit, mem, &entry[3],
                                 offset_ob_prio[code_point % BCM_OBM_DSCP_CHUNK_SIZE],
                                 ob_priority);
             entry_index[3] = 1;
         }
    }

    for (i = 0; i < 4; i++) {
         if (entry_index[i]) {
             SOC_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL,
                                               i, &entry[i]));
         }
    }

    return BCM_E_NONE;
}

STATIC int
bcm_hx5_obm_dscp_classifier_mapping_multi_get(int unit, int obm,
        int lane, int pipe, int array_max,
        bcm_switch_obm_classifier_t *switch_obm_classifier, int *array_count)
{
    int                             i, code_point, ob_priority;
    idb_obm0_dscp_map_port0_entry_t entry[4];
    bcm_switch_obm_classifier_t     *classifier_ptr = NULL;
    soc_mem_t                       mem;

    static const soc_mem_t obm_dscp_map_port_mem[][4] = {
        /* PM4x10Q*/
        {IDB_OBM0_Q_DSCP_MAP_PORT0m, IDB_OBM0_Q_DSCP_MAP_PORT1m,
        IDB_OBM0_Q_DSCP_MAP_PORT2m, IDB_OBM0_Q_DSCP_MAP_PORT3m
        },
        {IDB_OBM1_Q_DSCP_MAP_PORT0m, IDB_OBM1_Q_DSCP_MAP_PORT1m,
        IDB_OBM1_Q_DSCP_MAP_PORT2m, IDB_OBM1_Q_DSCP_MAP_PORT3m
        },
        {IDB_OBM2_Q_DSCP_MAP_PORT0m, IDB_OBM2_Q_DSCP_MAP_PORT1m,
        IDB_OBM2_Q_DSCP_MAP_PORT2m, IDB_OBM2_Q_DSCP_MAP_PORT3m
        },
        /* PM4x10 */
        {IDB_OBM0_DSCP_MAP_PORT0m, IDB_OBM0_DSCP_MAP_PORT1m,
        IDB_OBM0_DSCP_MAP_PORT2m, IDB_OBM0_DSCP_MAP_PORT3m
        },
        {IDB_OBM1_DSCP_MAP_PORT0m, IDB_OBM1_DSCP_MAP_PORT1m,
        IDB_OBM1_DSCP_MAP_PORT2m, IDB_OBM1_DSCP_MAP_PORT3m
        },
        {IDB_OBM2_DSCP_MAP_PORT0m, IDB_OBM2_DSCP_MAP_PORT1m,
        IDB_OBM2_DSCP_MAP_PORT2m, IDB_OBM2_DSCP_MAP_PORT3m
        },
        {IDB_OBM3_DSCP_MAP_PORT0m, IDB_OBM3_DSCP_MAP_PORT1m,
        IDB_OBM3_DSCP_MAP_PORT2m, IDB_OBM3_DSCP_MAP_PORT3m
        },
        /* PM4x25 */
        {IDB_OBM0_48_DSCP_MAP_PORT0m, IDB_OBM0_48_DSCP_MAP_PORT1m,
        IDB_OBM0_48_DSCP_MAP_PORT2m, IDB_OBM0_48_DSCP_MAP_PORT3m
        },
        {IDB_OBM1_48_DSCP_MAP_PORT0m, IDB_OBM1_48_DSCP_MAP_PORT1m,
        IDB_OBM1_48_DSCP_MAP_PORT2m, IDB_OBM1_48_DSCP_MAP_PORT3m
        },
        {IDB_OBM2_48_DSCP_MAP_PORT0m, IDB_OBM2_48_DSCP_MAP_PORT1m,
        IDB_OBM2_48_DSCP_MAP_PORT2m, IDB_OBM2_48_DSCP_MAP_PORT3m
        }
    };
    static const soc_field_t offset_ob_prio[] = {
        OFFSET0_OB_PRIORITYf, OFFSET1_OB_PRIORITYf, OFFSET2_OB_PRIORITYf,
        OFFSET3_OB_PRIORITYf, OFFSET4_OB_PRIORITYf, OFFSET5_OB_PRIORITYf,
        OFFSET6_OB_PRIORITYf, OFFSET7_OB_PRIORITYf, OFFSET8_OB_PRIORITYf,
        OFFSET9_OB_PRIORITYf, OFFSET10_OB_PRIORITYf, OFFSET11_OB_PRIORITYf,
        OFFSET12_OB_PRIORITYf, OFFSET13_OB_PRIORITYf, OFFSET14_OB_PRIORITYf,
        OFFSET15_OB_PRIORITYf
    };

    mem = SOC_MEM_UNIQUE_ACC(unit, obm_dscp_map_port_mem[obm][lane])[pipe];
    for (i = 0; i < 4; i++) {
         sal_memset(&entry[i], 0, sizeof(entry[i]));
         SOC_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, i,
                                          &entry[i]));
    }

    for (i = 0; i < *array_count; i++) {
         classifier_ptr = switch_obm_classifier + i;
         code_point = classifier_ptr->obm_code_point;
         if (code_point < BCM_OBM_DSCP_CHUNK_SIZE) {
             ob_priority = soc_mem_field32_get(unit, mem, &entry[0],
                                               offset_ob_prio[code_point]);
         } else if (code_point < 2 * BCM_OBM_DSCP_CHUNK_SIZE) {
             ob_priority = soc_mem_field32_get(unit, mem, &entry[1],
                          offset_ob_prio[code_point % BCM_OBM_DSCP_CHUNK_SIZE]);
         } else if (code_point < 3 * BCM_OBM_DSCP_CHUNK_SIZE) {
             ob_priority = soc_mem_field32_get(unit, mem, &entry[2],
                          offset_ob_prio[code_point % BCM_OBM_DSCP_CHUNK_SIZE]);
         } else {
             ob_priority = soc_mem_field32_get(unit, mem, &entry[3],
                          offset_ob_prio[code_point % BCM_OBM_DSCP_CHUNK_SIZE]);
        }

        classifier_ptr->obm_priority = ob_priority;
   }

   return BCM_E_NONE;
}

STATIC int
bcm_hx5_obm_etag_classifier_mapping_multi_set(int unit, int obm,
        int lane, int pipe, int array_count,
        bcm_switch_obm_classifier_t *switch_obm_classifier)
{
    int                             i, code_point, ob_priority;
    idb_obm0_etag_map_port0_entry_t entry;
    bcm_switch_obm_classifier_t     *classifier_ptr = NULL;
    soc_mem_t                       mem;

    static const soc_mem_t obm_etag_map_port_mem[][4] = {
        /* PM4x10Q*/
        {IDB_OBM0_Q_ETAG_MAP_PORT0m, IDB_OBM0_Q_ETAG_MAP_PORT1m,
        IDB_OBM0_Q_ETAG_MAP_PORT2m, IDB_OBM0_Q_ETAG_MAP_PORT3m
        },
        {IDB_OBM1_Q_ETAG_MAP_PORT0m, IDB_OBM1_Q_ETAG_MAP_PORT1m,
        IDB_OBM1_Q_ETAG_MAP_PORT2m, IDB_OBM1_Q_ETAG_MAP_PORT3m
        },
        {IDB_OBM2_Q_ETAG_MAP_PORT0m, IDB_OBM2_Q_ETAG_MAP_PORT1m,
        IDB_OBM2_Q_ETAG_MAP_PORT2m, IDB_OBM2_Q_ETAG_MAP_PORT3m
        },
        /* PM4x10 */
        {IDB_OBM0_ETAG_MAP_PORT0m, IDB_OBM0_ETAG_MAP_PORT1m,
        IDB_OBM0_ETAG_MAP_PORT2m, IDB_OBM0_ETAG_MAP_PORT3m
        },
        {IDB_OBM1_ETAG_MAP_PORT0m, IDB_OBM1_ETAG_MAP_PORT1m,
        IDB_OBM1_ETAG_MAP_PORT2m, IDB_OBM1_ETAG_MAP_PORT3m
        },
        {IDB_OBM2_ETAG_MAP_PORT0m, IDB_OBM2_ETAG_MAP_PORT1m,
        IDB_OBM2_ETAG_MAP_PORT2m, IDB_OBM2_ETAG_MAP_PORT3m
        },
        {IDB_OBM3_ETAG_MAP_PORT0m, IDB_OBM3_ETAG_MAP_PORT1m,
        IDB_OBM3_ETAG_MAP_PORT2m, IDB_OBM3_ETAG_MAP_PORT3m
        },
        /* PM4x25 */
        {IDB_OBM0_48_ETAG_MAP_PORT0m, IDB_OBM0_48_ETAG_MAP_PORT1m,
        IDB_OBM0_48_ETAG_MAP_PORT2m, IDB_OBM0_48_ETAG_MAP_PORT3m
        },
        {IDB_OBM1_48_ETAG_MAP_PORT0m, IDB_OBM1_48_ETAG_MAP_PORT1m,
        IDB_OBM1_48_ETAG_MAP_PORT2m, IDB_OBM1_48_ETAG_MAP_PORT3m
        },
        {IDB_OBM2_48_ETAG_MAP_PORT0m, IDB_OBM2_48_ETAG_MAP_PORT1m,
        IDB_OBM2_48_ETAG_MAP_PORT2m, IDB_OBM2_48_ETAG_MAP_PORT3m
        }
    };

    static const soc_field_t offset_ob_prio[] = {
        OFFSET0_OB_PRIORITYf, OFFSET1_OB_PRIORITYf,
        OFFSET2_OB_PRIORITYf, OFFSET3_OB_PRIORITYf,
        OFFSET4_OB_PRIORITYf, OFFSET5_OB_PRIORITYf,
        OFFSET6_OB_PRIORITYf, OFFSET7_OB_PRIORITYf
    };

    mem = SOC_MEM_UNIQUE_ACC(unit, obm_etag_map_port_mem[obm][lane])[pipe];
    sal_memset(&entry, 0, sizeof(entry));
    SOC_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, 0, &entry));

    for (i = 0; i < array_count; i++) {
         classifier_ptr = switch_obm_classifier + i;
         code_point = classifier_ptr->obm_code_point;
         ob_priority = classifier_ptr->obm_priority;
         soc_mem_field32_set(unit, mem, &entry,
                             offset_ob_prio[code_point], ob_priority);
    }
    SOC_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, 0, &entry));

    return BCM_E_NONE;
}

STATIC int
bcm_hx5_obm_etag_classifier_mapping_multi_get(
        int unit, int obm, int lane, int pipe, int array_max,
        bcm_switch_obm_classifier_t *switch_obm_classifier,
        int *array_count)
{
    int                             i, code_point, ob_priority;
    idb_obm0_etag_map_port0_entry_t entry;
    bcm_switch_obm_classifier_t     *classifier_ptr = NULL;
    soc_mem_t                       mem;

    static const soc_mem_t obm_etag_map_port_mem[][4] = {
        /* PM4x10Q*/
        {IDB_OBM0_Q_ETAG_MAP_PORT0m, IDB_OBM0_Q_ETAG_MAP_PORT1m,
        IDB_OBM0_Q_ETAG_MAP_PORT2m, IDB_OBM0_Q_ETAG_MAP_PORT3m
        },
        {IDB_OBM1_Q_ETAG_MAP_PORT0m, IDB_OBM1_Q_ETAG_MAP_PORT1m,
        IDB_OBM1_Q_ETAG_MAP_PORT2m, IDB_OBM1_Q_ETAG_MAP_PORT3m
        },
        {IDB_OBM2_Q_ETAG_MAP_PORT0m, IDB_OBM2_Q_ETAG_MAP_PORT1m,
        IDB_OBM2_Q_ETAG_MAP_PORT2m, IDB_OBM2_Q_ETAG_MAP_PORT3m
        },
        /* PM4x10 */
        {IDB_OBM0_ETAG_MAP_PORT0m, IDB_OBM0_ETAG_MAP_PORT1m,
        IDB_OBM0_ETAG_MAP_PORT2m, IDB_OBM0_ETAG_MAP_PORT3m
        },
        {IDB_OBM1_ETAG_MAP_PORT0m, IDB_OBM1_ETAG_MAP_PORT1m,
        IDB_OBM1_ETAG_MAP_PORT2m, IDB_OBM1_ETAG_MAP_PORT3m
        },
        {IDB_OBM2_ETAG_MAP_PORT0m, IDB_OBM2_ETAG_MAP_PORT1m,
        IDB_OBM2_ETAG_MAP_PORT2m, IDB_OBM2_ETAG_MAP_PORT3m
        },
        {IDB_OBM3_ETAG_MAP_PORT0m, IDB_OBM3_ETAG_MAP_PORT1m,
        IDB_OBM3_ETAG_MAP_PORT2m, IDB_OBM3_ETAG_MAP_PORT3m
        },
        /* PM4x25 */
        {IDB_OBM0_48_ETAG_MAP_PORT0m, IDB_OBM0_48_ETAG_MAP_PORT1m,
        IDB_OBM0_48_ETAG_MAP_PORT2m, IDB_OBM0_48_ETAG_MAP_PORT3m
        },
        {IDB_OBM1_48_ETAG_MAP_PORT0m, IDB_OBM1_48_ETAG_MAP_PORT1m,
        IDB_OBM1_48_ETAG_MAP_PORT2m, IDB_OBM1_48_ETAG_MAP_PORT3m
        },
        {IDB_OBM2_48_ETAG_MAP_PORT0m, IDB_OBM2_48_ETAG_MAP_PORT1m,
        IDB_OBM2_48_ETAG_MAP_PORT2m, IDB_OBM2_48_ETAG_MAP_PORT3m
        }
    };

    static const soc_field_t offset_ob_prio[] = {
        OFFSET0_OB_PRIORITYf, OFFSET1_OB_PRIORITYf,
        OFFSET2_OB_PRIORITYf, OFFSET3_OB_PRIORITYf,
        OFFSET4_OB_PRIORITYf, OFFSET5_OB_PRIORITYf,
        OFFSET6_OB_PRIORITYf, OFFSET7_OB_PRIORITYf
    };

    mem = SOC_MEM_UNIQUE_ACC(unit, obm_etag_map_port_mem[obm][lane])[pipe];
    sal_memset(&entry, 0, sizeof(entry));
    SOC_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, 0, &entry));

    for (i = 0; i < *array_count; i++) {
         classifier_ptr = switch_obm_classifier + i;
         code_point = classifier_ptr->obm_code_point;
         ob_priority = soc_mem_field32_get(unit, mem, &entry,
                                           offset_ob_prio[code_point]);
         classifier_ptr->obm_priority = ob_priority;
    }

    return BCM_E_NONE;
}

STATIC int
bcm_hx5_obm_vlan_classifier_mapping_multi_set(
        int unit, int obm, int lane, int pipe, int array_count,
        bcm_switch_obm_classifier_t *switch_obm_classifier)
{
    int                            i, code_point, ob_priority;
    idb_obm0_pri_map_port0_entry_t entry;
    bcm_switch_obm_classifier_t    *classifier_ptr = NULL;
    soc_mem_t                      mem;

    static const soc_mem_t obm_pri_map_port_mem[][4] = {
        /* PM4x10Q*/
        {IDB_OBM0_Q_PRI_MAP_PORT0m, IDB_OBM0_Q_PRI_MAP_PORT1m,
        IDB_OBM0_Q_PRI_MAP_PORT2m, IDB_OBM0_Q_PRI_MAP_PORT3m
        },
        {IDB_OBM1_Q_PRI_MAP_PORT0m, IDB_OBM1_Q_PRI_MAP_PORT1m,
        IDB_OBM1_Q_PRI_MAP_PORT2m, IDB_OBM1_Q_PRI_MAP_PORT3m
        },
        {IDB_OBM2_Q_PRI_MAP_PORT0m, IDB_OBM2_Q_PRI_MAP_PORT1m,
        IDB_OBM2_Q_PRI_MAP_PORT2m, IDB_OBM2_Q_PRI_MAP_PORT3m
        },
        /* PM4x10 */
        {IDB_OBM0_PRI_MAP_PORT0m, IDB_OBM0_PRI_MAP_PORT1m,
        IDB_OBM0_PRI_MAP_PORT2m, IDB_OBM0_PRI_MAP_PORT3m
        },
        {IDB_OBM1_PRI_MAP_PORT0m, IDB_OBM1_PRI_MAP_PORT1m,
        IDB_OBM1_PRI_MAP_PORT2m, IDB_OBM1_PRI_MAP_PORT3m
        },
        {IDB_OBM2_PRI_MAP_PORT0m, IDB_OBM2_PRI_MAP_PORT1m,
        IDB_OBM2_PRI_MAP_PORT2m, IDB_OBM2_PRI_MAP_PORT3m
        },
        {IDB_OBM3_PRI_MAP_PORT0m, IDB_OBM3_PRI_MAP_PORT1m,
        IDB_OBM3_PRI_MAP_PORT2m, IDB_OBM3_PRI_MAP_PORT3m
        },
        /* PM4x25 */
        {IDB_OBM0_48_PRI_MAP_PORT0m, IDB_OBM0_48_PRI_MAP_PORT1m,
        IDB_OBM0_48_PRI_MAP_PORT2m, IDB_OBM0_48_PRI_MAP_PORT3m
        },
        {IDB_OBM1_48_PRI_MAP_PORT0m, IDB_OBM1_48_PRI_MAP_PORT1m,
        IDB_OBM1_48_PRI_MAP_PORT2m, IDB_OBM1_48_PRI_MAP_PORT3m
        },
        {IDB_OBM2_48_PRI_MAP_PORT0m, IDB_OBM2_48_PRI_MAP_PORT1m,
        IDB_OBM2_48_PRI_MAP_PORT2m, IDB_OBM2_48_PRI_MAP_PORT3m
        }
    };

    static const soc_field_t offset_ob_prio[] = {
        OFFSET0_OB_PRIORITYf, OFFSET1_OB_PRIORITYf,
        OFFSET2_OB_PRIORITYf, OFFSET3_OB_PRIORITYf,
        OFFSET4_OB_PRIORITYf, OFFSET5_OB_PRIORITYf,
        OFFSET6_OB_PRIORITYf, OFFSET7_OB_PRIORITYf,
    };

    mem = SOC_MEM_UNIQUE_ACC(unit, obm_pri_map_port_mem[obm][lane])[pipe];
    sal_memset(&entry, 0, sizeof(entry));
    SOC_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, 0, &entry));

    for (i = 0; i < array_count; i++) {
         classifier_ptr = switch_obm_classifier + i;
         code_point = classifier_ptr->obm_code_point;
         ob_priority = classifier_ptr->obm_priority;
         soc_mem_field32_set(unit, mem, &entry,
                             offset_ob_prio[code_point], ob_priority);
    }
    SOC_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, 0, &entry));

    return BCM_E_NONE;
}

STATIC int
bcm_hx5_obm_vlan_classifier_mapping_multi_get(
        int unit, int obm, int lane, int pipe, int array_max,
        bcm_switch_obm_classifier_t *switch_obm_classifier,
        int *array_count)
{
    int                            i, code_point, ob_priority;
    idb_obm0_pri_map_port0_entry_t entry;
    bcm_switch_obm_classifier_t    *classifier_ptr = NULL;
    soc_mem_t                      mem;

    static const soc_mem_t obm_pri_map_port_mem[][4] = {
        /* PM4x10Q*/
        {IDB_OBM0_Q_PRI_MAP_PORT0m, IDB_OBM0_Q_PRI_MAP_PORT1m,
        IDB_OBM0_Q_PRI_MAP_PORT2m, IDB_OBM0_Q_PRI_MAP_PORT3m
        },
        {IDB_OBM1_Q_PRI_MAP_PORT0m, IDB_OBM1_Q_PRI_MAP_PORT1m,
        IDB_OBM1_Q_PRI_MAP_PORT2m, IDB_OBM1_Q_PRI_MAP_PORT3m
        },
        {IDB_OBM2_Q_PRI_MAP_PORT0m, IDB_OBM2_Q_PRI_MAP_PORT1m,
        IDB_OBM2_Q_PRI_MAP_PORT2m, IDB_OBM2_Q_PRI_MAP_PORT3m
        },
        /* PM4x10 */
        {IDB_OBM0_PRI_MAP_PORT0m, IDB_OBM0_PRI_MAP_PORT1m,
        IDB_OBM0_PRI_MAP_PORT2m, IDB_OBM0_PRI_MAP_PORT3m
        },
        {IDB_OBM1_PRI_MAP_PORT0m, IDB_OBM1_PRI_MAP_PORT1m,
        IDB_OBM1_PRI_MAP_PORT2m, IDB_OBM1_PRI_MAP_PORT3m
        },
        {IDB_OBM2_PRI_MAP_PORT0m, IDB_OBM2_PRI_MAP_PORT1m,
        IDB_OBM2_PRI_MAP_PORT2m, IDB_OBM2_PRI_MAP_PORT3m
        },
        {IDB_OBM3_PRI_MAP_PORT0m, IDB_OBM3_PRI_MAP_PORT1m,
        IDB_OBM3_PRI_MAP_PORT2m, IDB_OBM3_PRI_MAP_PORT3m
        },
        /* PM4x25 */
        {IDB_OBM0_48_PRI_MAP_PORT0m, IDB_OBM0_48_PRI_MAP_PORT1m,
        IDB_OBM0_48_PRI_MAP_PORT2m, IDB_OBM0_48_PRI_MAP_PORT3m
        },
        {IDB_OBM1_48_PRI_MAP_PORT0m, IDB_OBM1_48_PRI_MAP_PORT1m,
        IDB_OBM1_48_PRI_MAP_PORT2m, IDB_OBM1_48_PRI_MAP_PORT3m
        },
        {IDB_OBM2_48_PRI_MAP_PORT0m, IDB_OBM2_48_PRI_MAP_PORT1m,
        IDB_OBM2_48_PRI_MAP_PORT2m, IDB_OBM2_48_PRI_MAP_PORT3m
        }
    };

    static const soc_field_t offset_ob_prio[] = {
        OFFSET0_OB_PRIORITYf, OFFSET1_OB_PRIORITYf,
        OFFSET2_OB_PRIORITYf, OFFSET3_OB_PRIORITYf,
        OFFSET4_OB_PRIORITYf, OFFSET5_OB_PRIORITYf,
        OFFSET6_OB_PRIORITYf, OFFSET7_OB_PRIORITYf
    };

    mem = SOC_MEM_UNIQUE_ACC(unit, obm_pri_map_port_mem[obm][lane])[pipe];
    sal_memset(&entry, 0, sizeof(entry));
    SOC_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, 0, &entry));

    for (i = 0; i < *array_count; i++) {
         classifier_ptr = switch_obm_classifier + i;
         code_point = classifier_ptr->obm_code_point;
         ob_priority = soc_mem_field32_get(unit, mem, &entry,
                                           offset_ob_prio[code_point]);
         classifier_ptr->obm_priority = ob_priority;
    }

    return BCM_E_NONE;
}

STATIC int
bcm_hx5_obm_higig2_classifier_mapping_multi_set(
        int unit, int obm, int lane, int pipe, int array_count,
        bcm_switch_obm_classifier_t *switch_obm_classifier)
{
    int                            i, code_point, ob_priority;
    idb_obm0_pri_map_port0_entry_t entry;
    bcm_switch_obm_classifier_t    *classifier_ptr = NULL;
    soc_mem_t                      mem;

    static const soc_mem_t obm_pri_map_port_mem[][4] = {
        /* PM4x10Q*/
        {IDB_OBM0_Q_PRI_MAP_PORT0m, IDB_OBM0_Q_PRI_MAP_PORT1m,
        IDB_OBM0_Q_PRI_MAP_PORT2m, IDB_OBM0_Q_PRI_MAP_PORT3m
        },
        {IDB_OBM1_Q_PRI_MAP_PORT0m, IDB_OBM1_Q_PRI_MAP_PORT1m,
        IDB_OBM1_Q_PRI_MAP_PORT2m, IDB_OBM1_Q_PRI_MAP_PORT3m
        },
        {IDB_OBM2_Q_PRI_MAP_PORT0m, IDB_OBM2_Q_PRI_MAP_PORT1m,
        IDB_OBM2_Q_PRI_MAP_PORT2m, IDB_OBM2_Q_PRI_MAP_PORT3m
        },
        /* PM4x10 */
        {IDB_OBM0_PRI_MAP_PORT0m, IDB_OBM0_PRI_MAP_PORT1m,
        IDB_OBM0_PRI_MAP_PORT2m, IDB_OBM0_PRI_MAP_PORT3m
        },
        {IDB_OBM1_PRI_MAP_PORT0m, IDB_OBM1_PRI_MAP_PORT1m,
        IDB_OBM1_PRI_MAP_PORT2m, IDB_OBM1_PRI_MAP_PORT3m
        },
        {IDB_OBM2_PRI_MAP_PORT0m, IDB_OBM2_PRI_MAP_PORT1m,
        IDB_OBM2_PRI_MAP_PORT2m, IDB_OBM2_PRI_MAP_PORT3m
        },
        {IDB_OBM3_PRI_MAP_PORT0m, IDB_OBM3_PRI_MAP_PORT1m,
        IDB_OBM3_PRI_MAP_PORT2m, IDB_OBM3_PRI_MAP_PORT3m
        },
        /* PM4x25 */
        {IDB_OBM0_48_PRI_MAP_PORT0m, IDB_OBM0_48_PRI_MAP_PORT1m,
        IDB_OBM0_48_PRI_MAP_PORT2m, IDB_OBM0_48_PRI_MAP_PORT3m
        },
        {IDB_OBM1_48_PRI_MAP_PORT0m, IDB_OBM1_48_PRI_MAP_PORT1m,
        IDB_OBM1_48_PRI_MAP_PORT2m, IDB_OBM1_48_PRI_MAP_PORT3m
        },
        {IDB_OBM2_48_PRI_MAP_PORT0m, IDB_OBM2_48_PRI_MAP_PORT1m,
        IDB_OBM2_48_PRI_MAP_PORT2m, IDB_OBM2_48_PRI_MAP_PORT3m
        }
    };

    static const soc_field_t offset_ob_prio[] = {
        OFFSET0_OB_PRIORITYf, OFFSET1_OB_PRIORITYf, OFFSET2_OB_PRIORITYf,
        OFFSET3_OB_PRIORITYf, OFFSET4_OB_PRIORITYf, OFFSET5_OB_PRIORITYf,
        OFFSET6_OB_PRIORITYf, OFFSET7_OB_PRIORITYf, OFFSET8_OB_PRIORITYf,
        OFFSET9_OB_PRIORITYf, OFFSET10_OB_PRIORITYf, OFFSET11_OB_PRIORITYf,
        OFFSET12_OB_PRIORITYf, OFFSET13_OB_PRIORITYf, OFFSET14_OB_PRIORITYf,
        OFFSET15_OB_PRIORITYf
    };

    mem = SOC_MEM_UNIQUE_ACC(unit, obm_pri_map_port_mem[obm][lane])[pipe];
    sal_memset(&entry, 0, sizeof(entry));
    SOC_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, 0, &entry));

    for (i = 0; i < array_count; i++) {
         classifier_ptr = switch_obm_classifier + i;
         code_point = classifier_ptr->obm_code_point;
         ob_priority = classifier_ptr->obm_priority;
         soc_mem_field32_set(unit, mem, &entry,
                             offset_ob_prio[code_point], ob_priority);
    }
    SOC_IF_ERROR_RETURN(soc_mem_write(unit, mem, MEM_BLOCK_ALL, 0, &entry));

    return BCM_E_NONE;
}

STATIC int
bcm_hx5_obm_higig2_classifier_mapping_multi_get(
        int unit, int obm, int lane, int pipe, int array_max,
        bcm_switch_obm_classifier_t *switch_obm_classifier,
        int *array_count)
{
    int                            i, code_point, ob_priority;
    idb_obm0_pri_map_port0_entry_t entry;
    bcm_switch_obm_classifier_t    *classifier_ptr = NULL;
    soc_mem_t                      mem;

    static const soc_mem_t obm_pri_map_port_mem[][4] = {
        /* PM4x10Q*/
        {IDB_OBM0_Q_PRI_MAP_PORT0m, IDB_OBM0_Q_PRI_MAP_PORT1m,
        IDB_OBM0_Q_PRI_MAP_PORT2m, IDB_OBM0_Q_PRI_MAP_PORT3m
        },
        {IDB_OBM1_Q_PRI_MAP_PORT0m, IDB_OBM1_Q_PRI_MAP_PORT1m,
        IDB_OBM1_Q_PRI_MAP_PORT2m, IDB_OBM1_Q_PRI_MAP_PORT3m
        },
        {IDB_OBM2_Q_PRI_MAP_PORT0m, IDB_OBM2_Q_PRI_MAP_PORT1m,
        IDB_OBM2_Q_PRI_MAP_PORT2m, IDB_OBM2_Q_PRI_MAP_PORT3m
        },
        /* PM4x10 */
        {IDB_OBM0_PRI_MAP_PORT0m, IDB_OBM0_PRI_MAP_PORT1m,
        IDB_OBM0_PRI_MAP_PORT2m, IDB_OBM0_PRI_MAP_PORT3m
        },
        {IDB_OBM1_PRI_MAP_PORT0m, IDB_OBM1_PRI_MAP_PORT1m,
        IDB_OBM1_PRI_MAP_PORT2m, IDB_OBM1_PRI_MAP_PORT3m
        },
        {IDB_OBM2_PRI_MAP_PORT0m, IDB_OBM2_PRI_MAP_PORT1m,
        IDB_OBM2_PRI_MAP_PORT2m, IDB_OBM2_PRI_MAP_PORT3m
        },
        {IDB_OBM3_PRI_MAP_PORT0m, IDB_OBM3_PRI_MAP_PORT1m,
        IDB_OBM3_PRI_MAP_PORT2m, IDB_OBM3_PRI_MAP_PORT3m
        },
        /* PM4x25 */
        {IDB_OBM0_48_PRI_MAP_PORT0m, IDB_OBM0_48_PRI_MAP_PORT1m,
        IDB_OBM0_48_PRI_MAP_PORT2m, IDB_OBM0_48_PRI_MAP_PORT3m
        },
        {IDB_OBM1_48_PRI_MAP_PORT0m, IDB_OBM1_48_PRI_MAP_PORT1m,
        IDB_OBM1_48_PRI_MAP_PORT2m, IDB_OBM1_48_PRI_MAP_PORT3m
        },
        {IDB_OBM2_48_PRI_MAP_PORT0m, IDB_OBM2_48_PRI_MAP_PORT1m,
        IDB_OBM2_48_PRI_MAP_PORT2m, IDB_OBM2_48_PRI_MAP_PORT3m
        }
    };

    static const soc_field_t offset_ob_prio[] = {
        OFFSET0_OB_PRIORITYf, OFFSET1_OB_PRIORITYf, OFFSET2_OB_PRIORITYf,
        OFFSET3_OB_PRIORITYf, OFFSET4_OB_PRIORITYf, OFFSET5_OB_PRIORITYf,
        OFFSET6_OB_PRIORITYf, OFFSET7_OB_PRIORITYf, OFFSET8_OB_PRIORITYf,
        OFFSET9_OB_PRIORITYf, OFFSET10_OB_PRIORITYf, OFFSET11_OB_PRIORITYf,
        OFFSET12_OB_PRIORITYf, OFFSET13_OB_PRIORITYf, OFFSET14_OB_PRIORITYf,
        OFFSET15_OB_PRIORITYf
    };

    mem = SOC_MEM_UNIQUE_ACC(unit, obm_pri_map_port_mem[obm][lane])[pipe];
    sal_memset(&entry, 0, sizeof(entry));
    SOC_IF_ERROR_RETURN(soc_mem_read(unit, mem, MEM_BLOCK_ALL, 0, &entry));

    for (i = 0; i < *array_count; i++) {
         classifier_ptr = switch_obm_classifier + i;
         code_point = classifier_ptr->obm_code_point;
         ob_priority = soc_mem_field32_get(unit, mem, &entry,
                                           offset_ob_prio[code_point]);
         classifier_ptr->obm_priority = ob_priority;
    }

    return BCM_E_NONE;
}

STATIC int
bcm_hx5_obm_field_classifier_mapping_multi_set(
        int unit, int obm, int lane, int pipe, int array_count,
        bcm_switch_obm_classifier_t *switch_obm_classifier)
{
    uint64                       rval64;
    uint32                       rval_hi, rval_lo;
    bcm_switch_obm_classifier_t  *classifier_ptr = NULL;
    soc_reg_t                    reg;
    int                          i;

    static const soc_reg_t obm_proto_control0_regs[] = {
        /* PM4x10Q */
        IDB_OBM0_Q_PROTOCOL_CONTROL_0r, IDB_OBM1_Q_PROTOCOL_CONTROL_0r, IDB_OBM2_Q_PROTOCOL_CONTROL_0r,
        /* PM4x10 */
        IDB_OBM0_PROTOCOL_CONTROL_0r, IDB_OBM1_PROTOCOL_CONTROL_0r, IDB_OBM2_PROTOCOL_CONTROL_0r, IDB_OBM3_PROTOCOL_CONTROL_0r,
        /* PM4x25 */
        IDB_OBM0_48_PROTOCOL_CONTROL_0r, IDB_OBM1_48_PROTOCOL_CONTROL_0r, IDB_OBM2_48_PROTOCOL_CONTROL_0r
    };

    static const soc_reg_t obm_proto_control1_regs[] = {
        /* PM4x10Q */
        IDB_OBM0_Q_PROTOCOL_CONTROL_1r, IDB_OBM1_Q_PROTOCOL_CONTROL_1r, IDB_OBM2_Q_PROTOCOL_CONTROL_1r,
        /* PM4x10 */
        IDB_OBM0_PROTOCOL_CONTROL_1r, IDB_OBM1_PROTOCOL_CONTROL_1r, IDB_OBM2_PROTOCOL_CONTROL_1r, IDB_OBM3_PROTOCOL_CONTROL_0r,
        /* PM4x25 */
        IDB_OBM0_48_PROTOCOL_CONTROL_1r, IDB_OBM1_48_PROTOCOL_CONTROL_1r, IDB_OBM2_48_PROTOCOL_CONTROL_1r

    };
    static const soc_reg_t obm_proto_control2_regs[] = {
        /* PM4x10Q */
        IDB_OBM0_Q_PROTOCOL_CONTROL_2r, IDB_OBM1_Q_PROTOCOL_CONTROL_2r, IDB_OBM2_Q_PROTOCOL_CONTROL_2r,
        /* PM4x10 */
        IDB_OBM0_PROTOCOL_CONTROL_2r, IDB_OBM1_PROTOCOL_CONTROL_2r, IDB_OBM2_PROTOCOL_CONTROL_2r, IDB_OBM3_PROTOCOL_CONTROL_2r,
        /* PM4x25 */
        IDB_OBM0_48_PROTOCOL_CONTROL_2r, IDB_OBM1_48_PROTOCOL_CONTROL_2r, IDB_OBM2_48_PROTOCOL_CONTROL_2r
    };

    for (i = 0; i < array_count; i++) {
        classifier_ptr = switch_obm_classifier + i;

        reg = SOC_REG_UNIQUE_ACC(unit, obm_proto_control0_regs[obm])[pipe];
        COMPILER_64_ZERO(rval64);
        COMPILER_64_TO_32_HI(rval_hi, rval64);
        COMPILER_64_TO_32_LO(rval_lo, rval64);
        rval_hi |= ((classifier_ptr->obm_destination_mac[5] & 0xff) << 8);
        rval_hi |= (classifier_ptr->obm_destination_mac[4] & 0xff);
        rval_lo |= ((classifier_ptr->obm_destination_mac[3] & 0xff) << 24);
        rval_lo |= ((classifier_ptr->obm_destination_mac[2] & 0xff) << 16);
        rval_lo |= ((classifier_ptr->obm_destination_mac[1] & 0xff) << 8);
        rval_lo |= (classifier_ptr->obm_destination_mac[0] & 0xff);
        COMPILER_64_SET(rval64, rval_hi, rval_lo);
        SOC_IF_ERROR_RETURN
            (soc_reg_set(unit, reg, REG_PORT_ANY, lane, rval64));

        reg = SOC_REG_UNIQUE_ACC(unit, obm_proto_control1_regs[obm])[pipe];
        COMPILER_64_ZERO(rval64);
        COMPILER_64_TO_32_HI(rval_hi, rval64);
        COMPILER_64_TO_32_LO(rval_lo, rval64);
        rval_hi |= ((classifier_ptr->obm_destination_mac_mask[5] & 0xff) << 8);
        rval_hi |= (classifier_ptr->obm_destination_mac_mask[4] & 0xff);
        rval_lo |= ((classifier_ptr->obm_destination_mac_mask[3] & 0xff) << 24);
        rval_lo |= ((classifier_ptr->obm_destination_mac_mask[2] & 0xff) << 16);
        rval_lo |= ((classifier_ptr->obm_destination_mac_mask[1] & 0xff) << 8);
        rval_lo |= (classifier_ptr->obm_destination_mac_mask[0] & 0xff);
        COMPILER_64_SET(rval64, rval_hi, rval_lo);
        SOC_IF_ERROR_RETURN
            (soc_reg_set(unit, reg, REG_PORT_ANY, lane, rval64));

        reg = SOC_REG_UNIQUE_ACC(unit, obm_proto_control2_regs[obm])[pipe];
        COMPILER_64_ZERO(rval64);
        COMPILER_64_TO_32_HI(rval_hi, rval64);
        COMPILER_64_TO_32_LO(rval_lo, rval64);
        rval_lo |= (classifier_ptr->obm_ethertype & 0xffff);
        rval_lo |= ((classifier_ptr->obm_ethertype_mask & 0xffff) << 16);
        rval_hi |= (classifier_ptr->obm_priority & 0x7);
        rval_hi |= (0x1 << 3);
        COMPILER_64_SET(rval64, rval_hi, rval_lo);
        SOC_IF_ERROR_RETURN
            (soc_reg_set(unit, reg, REG_PORT_ANY, lane, rval64));
   }

   return BCM_E_NONE;
}

STATIC int
bcm_hx5_obm_field_classifier_mapping_multi_get(
        int unit, int obm, int lane, int pipe, int array_max,
        bcm_switch_obm_classifier_t *switch_obm_classifier,
        int *array_count)
{
    uint64                       rval64;
    uint32                       rval_hi, rval_lo;
    bcm_switch_obm_classifier_t  *classifier_ptr = NULL;
    soc_reg_t                    reg;
    int                          i;

    static const soc_reg_t obm_proto_control0_regs[] = {
        /* PM4x10Q */
        IDB_OBM0_Q_PROTOCOL_CONTROL_0r, IDB_OBM1_Q_PROTOCOL_CONTROL_0r, IDB_OBM2_Q_PROTOCOL_CONTROL_0r,
        /* PM4x10 */
        IDB_OBM0_PROTOCOL_CONTROL_0r, IDB_OBM1_PROTOCOL_CONTROL_0r, IDB_OBM2_PROTOCOL_CONTROL_0r, IDB_OBM3_PROTOCOL_CONTROL_0r,
        /* PM4x25 */
        IDB_OBM0_48_PROTOCOL_CONTROL_0r, IDB_OBM1_48_PROTOCOL_CONTROL_0r, IDB_OBM2_48_PROTOCOL_CONTROL_0r
    };

    static const soc_reg_t obm_proto_control1_regs[] = {
        /* PM4x10Q */
        IDB_OBM0_Q_PROTOCOL_CONTROL_1r, IDB_OBM1_Q_PROTOCOL_CONTROL_1r, IDB_OBM2_Q_PROTOCOL_CONTROL_1r,
        /* PM4x10 */
        IDB_OBM0_PROTOCOL_CONTROL_1r, IDB_OBM1_PROTOCOL_CONTROL_1r, IDB_OBM2_PROTOCOL_CONTROL_1r, IDB_OBM3_PROTOCOL_CONTROL_0r,
        /* PM4x25 */
        IDB_OBM0_48_PROTOCOL_CONTROL_1r, IDB_OBM1_48_PROTOCOL_CONTROL_1r, IDB_OBM2_48_PROTOCOL_CONTROL_1r

    };
    static const soc_reg_t obm_proto_control2_regs[] = {
        /* PM4x10Q */
        IDB_OBM0_Q_PROTOCOL_CONTROL_2r, IDB_OBM1_Q_PROTOCOL_CONTROL_2r, IDB_OBM2_Q_PROTOCOL_CONTROL_2r,
        /* PM4x10 */
        IDB_OBM0_PROTOCOL_CONTROL_2r, IDB_OBM1_PROTOCOL_CONTROL_2r, IDB_OBM2_PROTOCOL_CONTROL_2r, IDB_OBM3_PROTOCOL_CONTROL_2r,
        /* PM4x25 */
        IDB_OBM0_48_PROTOCOL_CONTROL_2r, IDB_OBM1_48_PROTOCOL_CONTROL_2r, IDB_OBM2_48_PROTOCOL_CONTROL_2r
    };


    /* Do validation of params */
    if (array_max > BCM_OBM_CLASSIFIER_NUM_ENTRY_FIELD) {
        *array_count = BCM_OBM_CLASSIFIER_NUM_ENTRY_FIELD;
    } else {
        *array_count = array_max;
    }

    for (i = 0; i < *array_count; i++) {
        classifier_ptr = switch_obm_classifier + i;

        reg = SOC_REG_UNIQUE_ACC(unit, obm_proto_control0_regs[obm])[pipe];
        COMPILER_64_ZERO(rval64);
        SOC_IF_ERROR_RETURN
            (soc_reg_get(unit, reg, REG_PORT_ANY, lane, &rval64));
        COMPILER_64_TO_32_HI(rval_hi, rval64);
        COMPILER_64_TO_32_LO(rval_lo, rval64);
        classifier_ptr->obm_destination_mac[5] = (rval_hi >> 8) & 0xff;
        classifier_ptr->obm_destination_mac[4] = rval_hi & 0xff;
        classifier_ptr->obm_destination_mac[3] = (rval_lo >> 24) & 0xff;
        classifier_ptr->obm_destination_mac[2] = (rval_lo >> 16) & 0xff;
        classifier_ptr->obm_destination_mac[1] = (rval_lo >> 8) & 0xff;
        classifier_ptr->obm_destination_mac[0] = rval_lo & 0xff;

        reg = SOC_REG_UNIQUE_ACC(unit, obm_proto_control1_regs[obm])[pipe];
        COMPILER_64_ZERO(rval64);
        SOC_IF_ERROR_RETURN
            (soc_reg_get(unit, reg, REG_PORT_ANY, lane, &rval64));
        COMPILER_64_TO_32_HI(rval_hi, rval64);
        COMPILER_64_TO_32_LO(rval_lo, rval64);
        classifier_ptr->obm_destination_mac_mask[5] = (rval_hi >> 8) & 0xff;
        classifier_ptr->obm_destination_mac_mask[4] = rval_hi & 0xff;
        classifier_ptr->obm_destination_mac_mask[3] = (rval_lo >> 24) & 0xff;
        classifier_ptr->obm_destination_mac_mask[2] = (rval_lo >> 16) & 0xff;
        classifier_ptr->obm_destination_mac_mask[1] = (rval_lo >> 8) & 0xff;
        classifier_ptr->obm_destination_mac_mask[0] = rval_lo & 0xff;

        reg = SOC_REG_UNIQUE_ACC(unit, obm_proto_control2_regs[obm])[pipe];
        COMPILER_64_ZERO(rval64);
        SOC_IF_ERROR_RETURN
            (soc_reg_get(unit, reg, REG_PORT_ANY, lane, &rval64));
        COMPILER_64_TO_32_HI(rval_hi, rval64);
        COMPILER_64_TO_32_LO(rval_lo, rval64);
        classifier_ptr->obm_ethertype = rval_lo & 0xffff;
        classifier_ptr->obm_ethertype_mask = (rval_lo >>16) & 0xffff;
        classifier_ptr->obm_priority = rval_hi & 0x7;
   }

   return BCM_E_NONE;
}

/*
 * Function:
 *      bcm_hx5_obm_classifier_validate
 * Purpose:
 *      Internal function for validation of config params.
 * Parameters:
 *      unit                      - (IN) Unit number.
 *      port                      - (IN) phyical port.
 *      switch_obm_classifier_type- (IN) type of switch_obm_classifier.
 *      array_count               - (IN) Number of elements in switch_obm_classifier.
 *      switch_obm_classifier     - (IN) Array of bcm_switch_obm_classifier_t.
 * Returns:
 *      BCM_E_xxx
 */
STATIC int
bcm_hx5_obm_classifier_validate(int unit, bcm_port_t port,
        bcm_switch_obm_classifier_type_t switch_obm_classifier_type,
        int *array_count,
        bcm_switch_obm_classifier_t *switch_obm_classifier, int set)
{
    int                          i, max_count;
    bcm_switch_obm_classifier_t  *classifier_ptr = NULL;

    if ((port <= 0) || (port > _BCM_HX5_NUM_PORTS)) {
        LOG_ERROR(BSL_LS_BCM_COMMON,
                 (BSL_META_U(unit,
                 "ERROR: Invalid port %d\n"), port));
        return BCM_E_PORT;
    }

    if (IS_HG_PORT(unit, port)) {
        if (switch_obm_classifier_type == bcmSwitchObmClassifierVlan) {
            LOG_ERROR(BSL_LS_BCM_COMMON,
                     (BSL_META_U(unit,
                     "ERROR: OBM Vlan classifier not allowed on Higig"
                     " port %d\n"), port));
            return BCM_E_PARAM;
        }
    } else {
        if (switch_obm_classifier_type == bcmSwitchObmClassifierHigig2) {
            LOG_ERROR(BSL_LS_BCM_COMMON,
                     (BSL_META_U(unit,
                     "ERROR: OBM Higig2 classifier not allowed on non Higig"
                     " port %d\n"), port));
            return BCM_E_PARAM;
        }
    }
    switch (switch_obm_classifier_type) {
        case bcmSwitchObmClassifierDscp:
            max_count = BCM_OBM_CLASSIFIER_NUM_ENTRY_DSCP;
            break;
        case bcmSwitchObmClassifierEtag:
            max_count = BCM_OBM_CLASSIFIER_NUM_ENTRY_ETAG;
            break;
        case bcmSwitchObmClassifierVlan:
            max_count = BCM_OBM_CLASSIFIER_NUM_ENTRY_VLAN;
            break;
        case bcmSwitchObmClassifierHigig2:
            max_count = BCM_OBM_CLASSIFIER_NUM_ENTRY_HIGIG2;
            break;
        case bcmSwitchObmClassifierField:
            max_count = BCM_OBM_CLASSIFIER_NUM_ENTRY_FIELD;
            break;
        default:
            LOG_ERROR(BSL_LS_BCM_COMMON,
                     (BSL_META_U(unit,
                     "ERROR: switch_obm_classifier_type is not correct on"
                     " port %d\n"), port));
            return BCM_E_PARAM;
    }
    /* For get API array count may be more than max_count */
    if (*array_count > max_count) {
        if (set) {
            return BCM_E_PARAM;
        } else {
            *array_count = max_count;
        }
    }
    for (i = 0; i < *array_count; i++) {
         classifier_ptr = switch_obm_classifier + i;
         if (switch_obm_classifier_type != bcmSwitchObmClassifierField) {
             if (classifier_ptr->obm_code_point >= max_count) {
                 LOG_ERROR(BSL_LS_BCM_COMMON,
                          (BSL_META_U(unit,
                          "ERROR: Invalid obm_code_point configured on"
                          " port %d\n"), port));
                 return BCM_E_PARAM;
             }
         }
         if (set) {
             if (classifier_ptr->obm_priority > _BCM_HX5_OBM_PRIORITY_MAX) {
                 LOG_ERROR(BSL_LS_BCM_COMMON,
                          (BSL_META_U(unit,
                          "ERROR: Invalid obm_priority configured on"
                          " port %d\n"), port));
                 return BCM_E_PARAM;
             }
        }
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *      bcm_hx5_switch_obm_classifier_mapping_multi_set
 * Purpose:
 *      Set the mapping of bcm_obm_code_point to bcm_obm_priority
 *      for multiple entries of same type of classifier.  Maximum
 *      number of entries to be programmed are different depending
 *      type of classifier. For type bcmSwitchObmClassifierField
 *      bcm_obm_code_point will not be used and mapping will happen
 *      based on destination_mac/mask and ethertype/mask.
 * Parameters:
 *      unit                       - (IN) Unit number.
 *      gport                      - (IN) gport for a given port.
 *      switch_obm_classifier_type - (IN) type of switch_obm_classifier.
 *      array_count                - (IN) Number of elements in switch_obm_classifier.
 *      switch_obm_classifier      - (IN) Array of bcm_switch_obm_classifier_t.
 * Returns:
 *      BCM_E_xxx
 */
int
bcm_hx5_switch_obm_classifier_mapping_multi_set(
        int unit, bcm_gport_t gport,
        bcm_switch_obm_classifier_type_t switch_obm_classifier_type,
        int array_count,
        bcm_switch_obm_classifier_t *switch_obm_classifier)
{
    soc_info_t *si;
    bcm_port_t port;
    int obm_id, lane, pipe;

    BCM_IF_ERROR_RETURN(bcm_esw_port_local_get(unit, gport, &port));
    SOC_IF_ERROR_RETURN
        (soc_helix5_port_obm_info_get(unit, port, &obm_id, &lane));
    if (obm_id >= _HX5_OBMS_PER_PIPE ||
            (lane < 0 || lane >= _HX5_PORTS_PER_PBLK)) {
        return BCM_E_PARAM;
    }
    si = &SOC_INFO(unit);
    pipe = si->port_pipe[port];

    /* Validate port and classifier compatibility */
    BCM_IF_ERROR_RETURN(
       bcm_hx5_obm_classifier_validate(unit, port, switch_obm_classifier_type,
                                       &array_count, switch_obm_classifier, 1));

    switch (switch_obm_classifier_type) {
        case bcmSwitchObmClassifierDscp:
            BCM_IF_ERROR_RETURN(
            bcm_hx5_obm_dscp_classifier_mapping_multi_set(unit, obm_id, lane,
                                             pipe, array_count,
                                             switch_obm_classifier));
            break;
        case bcmSwitchObmClassifierEtag:
            BCM_IF_ERROR_RETURN(
            bcm_hx5_obm_etag_classifier_mapping_multi_set(unit, obm_id, lane,
                                             pipe, array_count,
                                             switch_obm_classifier));
            break;
        case bcmSwitchObmClassifierVlan:
            BCM_IF_ERROR_RETURN(
            bcm_hx5_obm_vlan_classifier_mapping_multi_set(unit, obm_id, lane,
                                             pipe, array_count,
                                             switch_obm_classifier));
            break;
        case bcmSwitchObmClassifierHigig2:
            BCM_IF_ERROR_RETURN(
            bcm_hx5_obm_higig2_classifier_mapping_multi_set(unit, obm_id, lane,
                                              pipe, array_count,
                                              switch_obm_classifier));
            break;
        case bcmSwitchObmClassifierField:
            BCM_IF_ERROR_RETURN(
            bcm_hx5_obm_field_classifier_mapping_multi_set(unit, obm_id, lane,
                                              pipe, array_count,
                                              switch_obm_classifier));
            break;

        default:
            return BCM_E_UNAVAIL;
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *      bcm_hx5_switch_obm_classifier_mapping_multi_get
 * Purpose:
 *      Get the mapping of bcm_obm_code_point to bcm_obm_priority
 *      for multiple entries of same type of classifier.  Maximum
 *      number of entries to be programmed are different depending
 *      type of classifier. For type bcmSwitchObmClassifierField
 *      bcm_obm_code_point will not be used and mapping will happen
 *      based on destination_mac/mask and ethertype/mask.
 * Parameters:
 *      unit                       - (IN) Unit number.
 *      gport                      - (IN) gport for a given port.
 *      switch_obm_classifier_type - (IN) type of switch_obm_classifier.
 *      array_max                  - (IN) Maximum number of elements in switch_obm_classifier.
 *      switch_obm_classifier      - (IN/OUT) Array of bcm_switch_obm_classifier_t.
 *      array_count                - (OUT) Number of elements in switch_obm_classifier.
 * Returns:
 *      BCM_E_xxx
 */
int
bcm_hx5_switch_obm_classifier_mapping_multi_get(
        int unit, bcm_gport_t gport,
        bcm_switch_obm_classifier_type_t switch_obm_classifier_type,
        int array_max,
        bcm_switch_obm_classifier_t *switch_obm_classifier,
        int *array_count)
{
    soc_info_t *si;
    bcm_port_t port;
    int obm_id, lane, pipe;

    BCM_IF_ERROR_RETURN(bcm_esw_port_local_get(unit, gport, &port));
    SOC_IF_ERROR_RETURN
        (soc_helix5_port_obm_info_get(unit, port, &obm_id, &lane));
    if (obm_id >= _HX5_OBMS_PER_PIPE ||
            (lane < 0 || lane >= _HX5_PORTS_PER_PBLK)) {
        return BCM_E_PARAM;
    }
    si = &SOC_INFO(unit);
    pipe = si->port_pipe[port];

    /* Validate port and classifier compatibility */
    BCM_IF_ERROR_RETURN(
       bcm_hx5_obm_classifier_validate(unit, port, switch_obm_classifier_type,
                                       array_count, switch_obm_classifier, 0));
    switch (switch_obm_classifier_type) {
        case bcmSwitchObmClassifierDscp:
            BCM_IF_ERROR_RETURN(
            bcm_hx5_obm_dscp_classifier_mapping_multi_get(unit, obm_id, lane,
                                             pipe, array_max,
                                             switch_obm_classifier,
                                             array_count));
            break;
        case bcmSwitchObmClassifierEtag:
            BCM_IF_ERROR_RETURN(
            bcm_hx5_obm_etag_classifier_mapping_multi_get(unit, obm_id, lane,
                                             pipe, array_max,
                                             switch_obm_classifier,
                                             array_count));
            break;
        case bcmSwitchObmClassifierVlan:
            BCM_IF_ERROR_RETURN(
            bcm_hx5_obm_vlan_classifier_mapping_multi_get(unit, obm_id, lane,
                                             pipe, array_max,
                                             switch_obm_classifier,
                                             array_count));
            break;
        case bcmSwitchObmClassifierHigig2:
            BCM_IF_ERROR_RETURN(
            bcm_hx5_obm_higig2_classifier_mapping_multi_get(unit, obm_id, lane,
                                               pipe, array_max,
                                               switch_obm_classifier,
                                               array_count));
            break;
        case bcmSwitchObmClassifierField:
            BCM_IF_ERROR_RETURN(
            bcm_hx5_obm_field_classifier_mapping_multi_get(unit, obm_id, lane,
                                              pipe, array_max,
                                              switch_obm_classifier,
                                              array_count));
            break;

        default:
            return BCM_E_UNAVAIL;
    }

    return BCM_E_NONE;
}

int
bcm_hx5_obm_classifier_port_control_set(int unit, bcm_port_t port,
        bcm_port_control_t type, int value)
{
    soc_info_t *si;
    soc_reg_t  reg;
    soc_field_t field;
    int vntag = 0, port_control = 0, val;
    uint32 rval32;
    int pipe, obm, lane;

    static const soc_reg_t obm_port_config_regs[] = {
        /* PM4x10Q */
        IDB_OBM0_Q_PORT_CONFIGr, IDB_OBM1_Q_PORT_CONFIGr, IDB_OBM2_Q_PORT_CONFIGr,
        /* PM4x10 */
        IDB_OBM0_PORT_CONFIGr, IDB_OBM1_PORT_CONFIGr, IDB_OBM2_PORT_CONFIGr, IDB_OBM3_PORT_CONFIGr,
        /* PM4x25 */
        IDB_OBM0_48_PORT_CONFIGr, IDB_OBM1_48_PORT_CONFIGr, IDB_OBM2_48_PORT_CONFIGr
    };

    static const soc_reg_t obm_niv_ethertype_config_regs[] = {
        /* PM4x10Q */
        IDB_OBM0_Q_NIV_ETHERTYPEr, IDB_OBM1_Q_NIV_ETHERTYPEr, IDB_OBM2_Q_NIV_ETHERTYPEr,
        /* PM4x10 */
        IDB_OBM0_NIV_ETHERTYPEr, IDB_OBM1_NIV_ETHERTYPEr, IDB_OBM2_NIV_ETHERTYPEr, IDB_OBM3_NIV_ETHERTYPEr,
        /* PM4x25 */
        IDB_OBM0_48_NIV_ETHERTYPEr, IDB_OBM1_48_NIV_ETHERTYPEr, IDB_OBM2_48_NIV_ETHERTYPEr
    };

    static const soc_reg_t obm_pe_ethertype_config_regs[] = {
        /* PM4x10Q */
        IDB_OBM0_Q_PE_ETHERTYPEr, IDB_OBM1_Q_PE_ETHERTYPEr, IDB_OBM2_Q_PE_ETHERTYPEr,
        /* PM4x10 */
        IDB_OBM0_PE_ETHERTYPEr, IDB_OBM1_PE_ETHERTYPEr, IDB_OBM2_PE_ETHERTYPEr, IDB_OBM3_PE_ETHERTYPEr,
        /* PM4x25 */
        IDB_OBM0_48_PE_ETHERTYPEr, IDB_OBM1_48_PE_ETHERTYPEr, IDB_OBM2_48_PE_ETHERTYPEr
    };

    /* Add check on ports */
    if (IS_CPU_PORT(unit, port) || IS_LB_PORT(unit, port) ||
        IS_MACSEC_PORT(unit, port)) {
        /*  Do not allow programming on non-idb ports */
        return BCM_E_PARAM;
    }

    SOC_IF_ERROR_RETURN
        (soc_helix5_port_obm_info_get(unit, port, &obm, &lane));
    if (obm >= _HX5_OBMS_PER_PIPE ||
            (lane < 0 || lane >= _HX5_PORTS_PER_PBLK)) {
        return BCM_E_PARAM;
    }
    si = &SOC_INFO(unit);
    pipe = si->port_pipe[port];

    switch (type) {
        case bcmPortControlObmClassifierPriority:
            port_control = 1;
            field = PORT_PRIf;
            val = value & 0x7;
            break;
        case bcmPortControlObmClassifierEnableDscp:
            port_control = 1;
            field = TRUST_DSCPf;
            val = value & 0x1;
            break;
        case bcmPortControlObmClassifierEnableEtag:
            port_control = 1;
            field = PHB_FROM_ETAGf;
            val = value & 0x1;
            break;
        case bcmPortControlObmClassifierEtagEthertype:
            field = ETHERTYPEf;
            val = value & 0xffff;
            break;
        case bcmPortControlObmClassifierVntagEthertype:
            vntag = 1;
            field = ETHERTYPEf;
            val = value & 0xffff;
            break;
        default:
            return BCM_E_UNAVAIL;
    }

    if (port_control == 1) {
        reg = SOC_REG_UNIQUE_ACC(unit, obm_port_config_regs[obm])[pipe];
        SOC_IF_ERROR_RETURN(soc_reg32_get(unit, reg, REG_PORT_ANY, lane, &rval32));
        soc_reg_field_set(unit, reg, &rval32, field, val);
        SOC_IF_ERROR_RETURN(soc_reg32_set(unit, reg, REG_PORT_ANY, lane, rval32));
    } else if (vntag == 1) {
        reg = SOC_REG_UNIQUE_ACC(unit, obm_niv_ethertype_config_regs[obm])[pipe];
        SOC_IF_ERROR_RETURN(soc_reg32_get(unit, reg, REG_PORT_ANY, 0, &rval32));
        soc_reg_field_set(unit, reg, &rval32, field, val);
        soc_reg_field_set(unit, reg, &rval32, ENABLEf, val ? 1 : 0);
        SOC_IF_ERROR_RETURN(soc_reg32_set(unit, reg, REG_PORT_ANY, 0, rval32));
    } else {
        reg = SOC_REG_UNIQUE_ACC(unit, obm_pe_ethertype_config_regs[obm])[pipe];
        SOC_IF_ERROR_RETURN(soc_reg32_get(unit, reg, REG_PORT_ANY, 0, &rval32));
        soc_reg_field_set(unit, reg, &rval32, field, val);
        soc_reg_field_set(unit, reg, &rval32, ENABLEf, val ? 1 : 0);
        SOC_IF_ERROR_RETURN(soc_reg32_set(unit, reg, REG_PORT_ANY, 0, rval32));
    }

    return BCM_E_NONE;
}

int
bcm_hx5_obm_classifier_port_control_get(int unit, bcm_port_t port,
        bcm_port_control_t type, int *value)
{
    soc_info_t *si;
    soc_reg_t  reg;
    soc_field_t field;
    int vntag = 0, port_control = 0, val;
    uint32 rval32;
    int pipe, obm, lane;

    static const soc_reg_t obm_port_config_regs[] = {
        /* PM4x10Q */
        IDB_OBM0_Q_PORT_CONFIGr, IDB_OBM1_Q_PORT_CONFIGr, IDB_OBM2_Q_PORT_CONFIGr,
        /* PM4x10 */
        IDB_OBM0_PORT_CONFIGr, IDB_OBM1_PORT_CONFIGr, IDB_OBM2_PORT_CONFIGr, IDB_OBM3_PORT_CONFIGr,
        /* PM4x25 */
        IDB_OBM0_48_PORT_CONFIGr, IDB_OBM1_48_PORT_CONFIGr, IDB_OBM2_48_PORT_CONFIGr
    };

    static const soc_reg_t obm_niv_ethertype_config_regs[] = {
        /* PM4x10Q */
        IDB_OBM0_Q_NIV_ETHERTYPEr, IDB_OBM1_Q_NIV_ETHERTYPEr, IDB_OBM2_Q_NIV_ETHERTYPEr,
        /* PM4x10 */
        IDB_OBM0_NIV_ETHERTYPEr, IDB_OBM1_NIV_ETHERTYPEr, IDB_OBM2_NIV_ETHERTYPEr, IDB_OBM3_NIV_ETHERTYPEr,
        /* PM4x25 */
        IDB_OBM0_48_NIV_ETHERTYPEr, IDB_OBM1_48_NIV_ETHERTYPEr, IDB_OBM2_48_NIV_ETHERTYPEr
    };

    static const soc_reg_t obm_pe_ethertype_config_regs[] = {
        /* PM4x10Q */
        IDB_OBM0_Q_PE_ETHERTYPEr, IDB_OBM1_Q_PE_ETHERTYPEr, IDB_OBM2_Q_PE_ETHERTYPEr,
        /* PM4x10 */
        IDB_OBM0_PE_ETHERTYPEr, IDB_OBM1_PE_ETHERTYPEr, IDB_OBM2_PE_ETHERTYPEr, IDB_OBM3_PE_ETHERTYPEr,
        /* PM4x25 */
        IDB_OBM0_48_PE_ETHERTYPEr, IDB_OBM1_48_PE_ETHERTYPEr, IDB_OBM2_48_PE_ETHERTYPEr
    };

    /* Add check on ports */
    if (IS_CPU_PORT(unit, port) || IS_LB_PORT(unit, port) ||
        IS_MACSEC_PORT(unit, port)) {
        /*  Do not allow programming on non-idb ports */
        return BCM_E_PARAM;
    }

    SOC_IF_ERROR_RETURN
        (soc_helix5_port_obm_info_get(unit, port, &obm, &lane));
    if (obm >= _HX5_OBMS_PER_PIPE ||
            (lane < 0 || lane >= _HX5_PORTS_PER_PBLK)) {
        return BCM_E_PARAM;
    }
    si = &SOC_INFO(unit);
    pipe = si->port_pipe[port];

    switch (type) {
        case bcmPortControlObmClassifierPriority:
            port_control = 1;
            field = PORT_PRIf;
            break;
        case bcmPortControlObmClassifierEnableDscp:
            port_control = 1;
            field = TRUST_DSCPf;
            break;
        case bcmPortControlObmClassifierEnableEtag:
            port_control = 1;
            field = PHB_FROM_ETAGf;
            break;
        case bcmPortControlObmClassifierEtagEthertype:
            field = ETHERTYPEf;
            break;
        case bcmPortControlObmClassifierVntagEthertype:
            vntag = 1;
            field = ETHERTYPEf;
            break;
        default:
            return BCM_E_UNAVAIL;
    }

    if (port_control == 1) {
        reg = SOC_REG_UNIQUE_ACC(unit, obm_port_config_regs[obm])[pipe];
        SOC_IF_ERROR_RETURN(soc_reg32_get(unit, reg, REG_PORT_ANY, lane, &rval32));
        val = soc_reg_field_get(unit, reg, rval32, field);
        SOC_IF_ERROR_RETURN(soc_reg32_set(unit, reg, REG_PORT_ANY, lane, rval32));
    } else if (vntag == 1) {
        reg = SOC_REG_UNIQUE_ACC(unit, obm_niv_ethertype_config_regs[obm])[pipe];
        SOC_IF_ERROR_RETURN(soc_reg32_get(unit, reg, REG_PORT_ANY, 0, &rval32));
        val = soc_reg_field_get(unit, reg, rval32, field);
        SOC_IF_ERROR_RETURN(soc_reg32_set(unit, reg, REG_PORT_ANY, 0, rval32));
    } else {
        reg = SOC_REG_UNIQUE_ACC(unit, obm_pe_ethertype_config_regs[obm])[pipe];
        SOC_IF_ERROR_RETURN(soc_reg32_get(unit, reg, REG_PORT_ANY, 0, &rval32));
        val = soc_reg_field_get(unit, reg, rval32, field);
        SOC_IF_ERROR_RETURN(soc_reg32_set(unit, reg, REG_PORT_ANY, 0, rval32));
    }

    *value = val;
    return BCM_E_NONE;
}
#endif /* BCM_HELIX5_SUPPORT */

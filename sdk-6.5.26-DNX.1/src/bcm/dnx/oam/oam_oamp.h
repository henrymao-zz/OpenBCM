/** \file oam_oamp.h
 * OAMP support - contains internal functions and definitions
 * for support of the OAM/BFD accelerator oam functionality
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifndef OAM_OAMP_H_INCLUDED
/*
 * {
 */
#define OAM_OAMP_H_INCLUDED

#ifndef BCM_DNX_SUPPORT
#error "This file is for use by DNX family only!"
#endif

#include "include/bcm/oam.h"
#include <bcm/types.h>
#include <soc/dnx/dbal/dbal.h>
#include <bcm_int/dnx/algo/oam/algo_oam.h>
#include <src/bcm/dnx/oam/oam_internal.h>
#include <include/soc/dnx/dnx_data/auto_generated/dnx_data_oam.h>

#define NOF_BITS_IN_BYTE 8

/**
 *  Convert from hardware entry index (15 bits) to OAM-ID (17
 *  bits)
 */
#define MEP_DB_ENTRY_TO_OAM_ID(x) ((x)<<2)

/**
 *  Convert from OAM-ID (17 bits) to hardware entry index (15
 *  bits)
 */
#define OAM_ID_TO_MEP_DB_ENTRY(x) ((x)>>2)

/**
 *  For self contained OAM endpoints, the LM/DM data is
 *  contained in these types of entries.
 *  The RFC 6374 is not part of the LM/DM data, but it is part of the
 *  additional entries of flex pointer, and need to be take into account.
 */
#define IS_LM_DM_TYPE(x) ((x == DBAL_ENUM_FVAL_OAMP_MEP_TYPE_LM_DB) ||\
                          (x == DBAL_ENUM_FVAL_OAMP_MEP_TYPE_LM_STAT) ||\
                          (x == DBAL_ENUM_FVAL_OAMP_MEP_TYPE_DM_STAT) ||\
                          (x == DBAL_ENUM_FVAL_OAMP_MEP_TYPE_RFC_6374) ||\
                          (x == DBAL_ENUM_FVAL_OAMP_MEP_TYPE_DM_STAT_ONE_WAY))

/** Interval in microseconds between to OAMP MEP DB scans */
#define OAMP_SCAN_INTERVAL_uS(unit) (dnx_data_oam.oamp.oamp_scan_sycles_in_us_get(unit))
/** Interval in miliseconds for endpoint period */
#define OAMP_PERIOD_INTERVAL_mS(unit) (dnx_data_oam.oamp.oamp_scan_sycles_in_ms_get(unit))

/** Flags relevant for accelerated OAM CCM endpoints   */

/** Update flag - always necessary because of allocation  */
#define DNX_OAMP_OAM_CCM_MEP_UPDATE             SAL_BIT(0)

#define MPLS_LABEL_GAL_TTL 64
#define MPLS_LABEL_GAL_EXP 0
#define MPLS_LABEL_GAL_BOS 1

/**
 *  When set, this endpoint will be written to the OAMP MEP DB
 *  in offloaded mode: two MDB entries will also be added
 */
#define DNX_OAMP_OAM_CCM_MEP_LM_DM_OFFLOADED    SAL_BIT(1)

/** Indicates 1/4 entry mode   */
#define DNX_OAMP_OAM_CCM_MEP_Q_ENTRY            SAL_BIT(2)

/** 0 = down-MEP; 1 = up-MEP   */
#define DNX_OAMP_OAM_CCM_MEP_IS_UPMEP           SAL_BIT(3)

/** MAID that is copied from extra data header */
#define DNX_OAMP_OAM_CCM_MEP_48B_MAID           SAL_BIT(4)

/** Read only: remote detect indicator produced by scanner   */
#define DNX_OAMP_OAM_CCM_MEP_RDI_FROM_SCANNER   SAL_BIT(5)

/**
 *  Read only: remote detect indicator read for received
 *  packet
 */
#define DNX_OAMP_OAM_CCM_MEP_RDI_FROM_PACKET    SAL_BIT(6)

/** Enable port status TLV injection   */
#define DNX_OAMP_OAM_CCM_MEP_PORT_TLV_EN        SAL_BIT(7)

/** Value of port status TLV   */
#define DNX_OAMP_OAM_CCM_MEP_PORT_TLV_VAL       SAL_BIT(8)

/** 1 = multicast; 0 = unicast   */
#define DNX_OAMP_OAM_CCM_MEP_MC_UC_SEL          SAL_BIT(9)

/** Do not send packets for this MEP ID.   */
#define DNX_OAMP_OAM_CCM_MEP_TXM_DSBL_TX        SAL_BIT(10)

/** Use FEC ID or global out-LIF?   */
#define DNX_OAMP_OAM_CCM_MEP_DESTINATION_IS_FEC SAL_BIT(11)

/** Use for Egress Down-MEP Injection   */
#define DNX_OAMP_OAM_CCM_MEP_DOWN_MEP_EGRESS_INJECTION   SAL_BIT(12)

/**
 *  When set, LM is enabled on this endpoint
 */
#define DNX_OAMP_OAM_CCM_MEP_OFFLOADED_LM_ENABLE        SAL_BIT(13)

/**
 *  When set, DM is enabled on this endpoint
 */
#define DNX_OAMP_OAM_CCM_MEP_OFFLOADED_DM_ENABLE        SAL_BIT(14)

/**
 *  When set, LM/DM flexible DMAC is enabled on this endpoint
 */
#define DNX_OAMP_OAM_CCM_MEP_LMDM_FLEXIBLE_DA    SAL_BIT(15)

/**
 *  When set, Endpoint support Signal Degradation feature(MPLS Section node only
 */
#define DNX_OAMP_OAM_CCM_MEP_SIGNAL_DEGRADATION_ENABLE    SAL_BIT(16)
/**
 *  When set, Add GAL label to RFC6374 PDU
 */
#define DNX_OAMP_OAM_RF6374_GAL    SAL_BIT(19)
/**
 *  When set, Add ACH label to RFC6374 PDU
 */
#define DNX_OAMP_OAM_RF6374_ACH    SAL_BIT(20)
/**
 * When set, indicate that the MEP is of type RFC6374
 */
#define DNX_OAMP_OAM_MEP_IS_RF6374   SAL_BIT(21)
/**
 * When set, indicate that additional GAL label is used on the MEP
 */
#define DNX_OAMP_OAM_MEP_ADDITIONAL_GAL_LABEL   SAL_BIT(22)

/**
 *  Bit in the "FEC-ID or Global out-LIF" field that determines
 *  whether the field is FEC-ID (1) or global out-LIF (0)
 */
#define FIELD_IS_FEC_ID_FLAG 22

/**
 *  Number of bytes of extra data in a single EXTRA_DATA_HDR
 *  or EXTRA_DATA_PLD entry
 */
#define DATA_SEG_LEN 20

/**
 *  Number of bytes needed for a two-way delay field
 *  (LAST_DELAY, MAX_DELAY, etc.)
 */
#define TWO_WAY_DELAY_SIZE 6

/**
 *  Number of bytes needed for a one-way delay field
 *  (LAST_DELAY_DMR, MAX_DELAY_DMR, etc.)
 */
#define ONE_WAY_DELAY_SIZE 5

/** In order to avoid pointing to a valid entry, this value can be used in fields that point to other MEP DB entries  */
#define INVALID_ENTRY 0xFFFF

/** OAM group create indication   */
#define DNX_OAMP_OAM_GROUP_CREATE SAL_BIT(0)

/** OAM group destroy indication   */
#define DNX_OAMP_OAM_GROUP_DESTROY 0

/** OAM group MD format short/ICC   */
#define DNX_OAMP_OAM_GROUP_MD_FORMAT SAL_BIT(0)

/** OAM group MA NAME format short   */
#define DNX_OAMP_OAM_GROUP_MA_NAME_FORMAT_SHORT 3

/** OAM group MA NAME format ICC   */
#define DNX_OAMP_OAM_GROUP_MA_NAME_FORMAT_ICC 32

/** MAID offset in OAM packet (in bits)*/
#define DNX_OAMP_OAM_GROUP_MAID_OFFSET 80

/** OAM group MA NAME ICC data length in bytes */
#define DNX_OAMP_OAM_GROUP_ICC_DATA_LENGTH 6

/** OAM group MA NAME ICC data offset in MAID name */
#define DNX_OAMP_OAM_GROUP_ICC_DATA_OFFSET 3

/** OAM LONG group MA NAME length in MAID name */
#define DNX_OAMP_OAM_GROUP_LONG_MA_NAME_DATA_LENGTH 2

/** OAM LONG group MA NAME offset in MAID name */
#define DNX_OAMP_OAM_GROUP_LONG_MA_NAME_DATA_OFFSET (DNX_OAMP_OAM_GROUP_ICC_DATA_OFFSET + DNX_OAMP_OAM_GROUP_ICC_DATA_LENGTH)

/** OAM group MA NAME UMC data length in bytes */
#define DNX_OAMP_OAM_GROUP_UMC_DATA_LENGTH 5

/** OAM group MA NAME UMC data offset in MAID name */
#define DNX_OAMP_OAM_GROUP_UMC_DATA_OFFSET (DNX_OAMP_OAM_GROUP_LONG_MA_NAME_DATA_OFFSET + DNX_OAMP_OAM_GROUP_LONG_MA_NAME_DATA_LENGTH)

/** In the "local port" field, offset of core ID bit */
#define PORT_CORE_BIT_INDEX 8

#define DNX_OAM_MEP_DB_NOF_BITS_IN_HEADER_ENTRY  160
#define DNX_OAM_MEP_DB_NOF_BITS_IN_PAYLOAD_ENTRY 160

/** To facilitate OAM-PE coding, DMAC occupies 8 bytes in extra data */
#define DNX_LMDM_FLEXIBLE_DA_LENGTH 8
#define DNX_LMDM_FLEXIBLE_DA_BITS (DNX_LMDM_FLEXIBLE_DA_LENGTH * NOF_BITS_IN_BYTE)

#define DNX_OAM_OAMP_NOF_MAID_BITS (BCM_OAM_GROUP_NAME_LENGTH * NOF_BITS_IN_BYTE)

/** Maximum extra data size 80 bytes */
#define DNX_OAM_OAMP_EXTRA_DATA_MAX_SIZE 80

#define DNX_OAM_MDB_EXTRA_DATA_HDR_SEG_LEN 63
#define DNX_OAM_MDB_EXTRA_DATA_PLD_SEG_LEN 109

/** MAC LSB field */
#define DNX_OAM_ETH_SA_MAC_LSB_SIZE_IN_BITS     (15)
#define DNX_OAM_ETH_SA_MAC_SECOND_BYTE_MASK UTILEX_BITS_MASK(DNX_OAM_ETH_SA_MAC_LSB_SIZE_IN_BITS - SAL_UINT8_NOF_BITS - 1,0)

#define DNX_OAM_CCM_ENDPOINT_EXTRA_DATA_LENGHT_CALC(is_maid20, is_maid48) \
    ((is_maid20) ? 2 : ((is_maid48) ? 3 : 1))

/** Conversion from milliseconds to microseconds */
#define MS_TO_uS(x) (x * 1000)

/**
* Conversion of Period (API structure) two number of scans (hardware table) 
* In Jer2 value 0 means 1.667 ms, value 1 means 3.33 ms etc.
* In Jer3 value 0 means 0, value 1 means 3.33ms, value 2 means 6.66 ms, etc.
*/
#define BCM_OAMP_SW_ENTRY_INFO_PERIOD_TO_MEP_DB_SCAN_RATE(unit,period) \
    (UTILEX_DIV_ROUND(MS_TO_uS(period), OAMP_SCAN_INTERVAL_uS(unit)) - (dnx_data_oam.oamp.feature_get(unit, dnx_data_oam_oamp_oamp_v2) ? 0 : 1))

/** Conversion of number of scans (hardware table) to period (API structure) */
#define BCM_OAMP_MEP_DB_SCAN_RATE_TO_SW_ENTRY_PERIOD(unit,scan_rate) \
    UTILEX_DIV_ROUND(((scan_rate + 1) * OAMP_PERIOD_INTERVAL_mS(unit)), 100)

/** Criterion for OAM server endpoint */
#define IS_OAM_SERVER(x) (x->remote_gport != BCM_GPORT_INVALID)

/*
 * Integer division x/y with integer round to nearest.
 * NOTE!!!!!! if y=0  .... ERROR
 */
#define SOC_SAND_DIV_ROUND(x,y) ( ((x) + ((y)/2) ) / (y) )

/**
 * Structure for extra data attached in CCM endpoint entry
 * Possible format is,
 * 1. Flexible DMAC (6 bytes)
 * 2. Flexible DMAC (6 bytes) + MAID48 (48 bytes)
 * 3. Signal Degradation
 * 4. Signal Degradation + MAID48
 * related to HW write/clear
 */
typedef struct dnx_oamp_ccm_endpoint_extra_data_s
{
    /** Index for extra data entry */
    uint16 index;

    /** Number for extra data entries */
    uint8 length;

    /** Bitmap defining opcodes to be prepended*/
    uint16 opcodes_to_prepend;

    /** Flag for extra data */
    uint16 flags;

    /** Expected Signal Degradation value */
    uint8 signal_degradation_rx;

    /** 6 bytes flexible DMAC */
    bcm_mac_t dmac;

    /** 48 bytes MAID */
    uint8 maid48[BCM_OAM_GROUP_NAME_LENGTH];
} dnx_oamp_ccm_endpoint_extra_data_t;

/** Indicate setting flexible DMAC in extra data   */
#define DNX_OAMP_CCM_ENDPOINT_EXTRA_DATA_UPDATE SAL_BIT(0)
/** Indicate setting flexible DMAC in extra data   */
#define DNX_OAMP_CCM_ENDPOINT_EXTRA_DATA_DMAC SAL_BIT(1)
/** Indicate setting 48 bytes MAID in extra data   */
#define DNX_OAMP_CCM_ENDPOINT_EXTRA_DATA_MAID48 SAL_BIT(2)
/** Indicate setting Signal Degradation in extra data   */
#define DNX_OAMP_CCM_ENDPOINT_EXTRA_DATA_SD SAL_BIT(3)
/** Indicate setting 20 bytes MAID in extra data   */
#define DNX_OAMP_CCM_ENDPOINT_EXTRA_DATA_MAID20 SAL_BIT(4)
/** Indicate setting 40 bytes MAID in extra data   */
#define DNX_OAMP_CCM_ENDPOINT_EXTRA_DATA_MAID40 SAL_BIT(5)

/** Indicate extra data is prepended on CCM PDU   */
#define DNX_OAMP_EXTRA_DATA_TO_PREPEND_CCM SAL_BIT(0)
/** Indicate extra data is prepended on LMM PDU   */
#define DNX_OAMP_EXTRA_DATA_TO_PREPEND_LMM SAL_BIT(1)
/** Indicate extra data is prepended on DMM PDU   */
#define DNX_OAMP_EXTRA_DATA_TO_PREPEND_DMM SAL_BIT(2)

/**
 * PP port: the data needed for up-MEPs
 * Is a port index and a core ID
 */
typedef struct
{
    uint16 pp_port;
    int8 port_core;
} upmep_port_t;

/**
 * This union covers all possibilities:
 * - For up-MEP, the above structure
 * - Otherwise, just a profile index
 */
typedef union
{
    upmep_port_t ccm_eth_up_mep_port;
    uint16 port_profile;
} u_port_access;

/** Structure for accelerated OAM CCM endpoints   */
typedef struct
{
    /**
     *  MEP type.  Values for OAM:
     *  Ethernet OAM:
     *  DBAL_ENUM_FVAL_OAMP_MEP_TYPE_ETH_OAM = 0
     *  Y1731 OAM over MPLS-TP:
     *  DBAL_ENUM_FVAL_OAMP_MEP_TYPE_Y1731_MPLSTP = 1
     *  Y1731 OAM over PWE:
     *  DBAL_ENUM_FVAL_OAMP_MEP_TYPE_Y1731_PWE = 2
     */
    dbal_enum_value_field_oamp_mep_type_e mep_type;

    /** See flag mask definitions named DNX_OAMP_OAM_CCM_MEP_XXX  */
    uint32 flags;

    /** Only one of these values can be used.  See flag above   */
    union
    {
        /** FEC ID   */
        uint32 fec_id;

        /** Global out-LIF   */
        uint32 glob_out_lif;
    } fec_id_or_glob_out_lif;

    /** MPLS/PWE label (for MPLS/PWE only)   */
    uint32 label;

    /** Counter pointer for TxFCf stamping by SLM   */
    uint32 counter_ptr;

    /** VSI used for Egress Down-MEP injection */
    uint32 vsi;

    /** Destination trap for OAMP server */
    uint32 server_destination;

    /**
     *  Endpoint identification number used in transmitted CCM
     *  packets
     */
    uint16 mep_id;

    /** MPLS-TP/PWE only: system port   */
    uint16 dest_sys_port_agr;

    /**
     *  Pointer to extra data header entry (48b MAID params) - self
     *  contained entries only.  For offloaded entries, extra data
     *  entries are automatically created in the MDB.
     */
    uint16 extra_data_header;

    /**
     *  Pointer to LM/DM entry for self-contained endpoints or
     *  Part 2 entry for offloaded endpoints.
     */
    uint16 flex_lm_dm_entry;

    /**
     *  2 byte MAID - relevant only if 48b MAID flag is clear
     */
    uint16 maid;

    /** VID of the inner VLAN   */
    uint16 inner_vid;

    /** VID of the outer VLAN   */
    uint16 outer_vid;

    /** 15 least significant bits of the source MAC address   */
    uint16 sa_gen_lsb;

    /**
     *  Interval between sending CCM packets for this endpoint.
     */
    dbal_enum_value_field_ccm_interval_e ccm_interval;

    /**
     *  choice between two possible values for the 33 most
     *  significant bits of the source MAC address
     */
    uint8 sa_gen_msb_profile;

    /** ICC pointer for ICC based MAID   */
    uint8 icc_index;

    /** MD Level   */
    uint8 mdl;

    /** Number VLAN tags (0, 1 or 2)   */
    uint8 nof_vlan_tags;

    /** Pointer to TPID value of inner VLAN   */
    uint8 inner_tpid_index;

    /** PCP DEI of the inner VLAN   */
    uint8 inner_pcp_dei;

    /** Pointer to TPID value of outer VLAN   */
    uint8 outer_tpid_index;

    /** PCP DEI of the outer VLAN   */
    uint8 outer_pcp_dei;

    /**
     *  Code for interface status TLV;
     *  0 - no interface status TLV
     */
    uint8 interface_status_tlv_code;

    /** Packet priority - mapped ITMH TC/DP   */
    uint8 itmh_tc_dp_profile;

    /**
     *  Points to an entry that contains more endpoint
     *  parameters, mostly LM/DM
     */
    uint8 mep_profile;

    /**
     *  Points to an entry that contains parameters that dictate
     *  programmable editor modification of packets generated by
     *  this endpoint
     */
    uint8 mep_pe_profile;

    /** PP port - mapping according to MEP type */
    u_port_access unified_port_access;

    /**
     *  MPLS/PWE only: points to a profile that contains TTL and
     *  QoS values
     */
    uint8 push_profile;

    /** Counter for this endpoint is accessed by this interface   */
    uint8 counter_interface;

    /** Number of the core performing the counter processing */
    uint8 crps_core_select;

    /** Signal Degradation TX indication */
    uint8 signal_degradation_tx;

    /** Extra data attached to CCM endpoint */
    dnx_oamp_ccm_endpoint_extra_data_t extra_data;

    /** Extra data attached to CCM endpoint */
    uint32 session_id;

    /** Extra data attached to CCM endpoint */
    uint32 timestamp_format;

    /** Extra data attached to CCM endpoint */
    uint32 ach_sel;

    /** Extra data attached to CCM endpoint */
    uint8 dm_t_flag;

    /** Extra data attached to CCM endpoint */
    uint8 dm_priority;

    /**
     *  Indicate the different address in OAMP generic memory
     *  which is used to store ingress VLAN edit command ID to
     *  delete 0/1/2 VLAN tag(s) for Down MEP Egress inject
     */
    uint8 ivec_address_factor;

} dnx_oam_oamp_ccm_endpoint_t;

/** Flags used in LM APIs   */

/** Update flag - always necessary because of allocation  */
#define DNX_OAMP_OAM_LM_MEP_UPDATE                      SAL_BIT(0)

/**
 *  For self-contained mode: use a second entry (the same offset
 *  in the next entry bank) for LM_STAT
 *  For LM/DM offloaded mode: add the optional second MEP DB
 *  entry
 */
#define DNX_OAMP_OAM_LM_MEP_ADD_STAT_ENTRY              SAL_BIT(1)

/** Measure the next received SLR  */
#define DNX_OAMP_OAM_LM_MEP_MEASURE_NEXT_RECEIVED_SLR   SAL_BIT(2)

/** Indicates if LM_STAT entry exists */
#define DNX_OAMP_OAM_LM_MEP_LM_STAT_EXISTS              SAL_BIT(3)

/** Indicates if DM_STAT entry exists */
#define DNX_OAMP_OAM_LM_MEP_DM_STAT_EXISTS              SAL_BIT(4)

/** For MDB entries, an access key is necessary   */

/**
 *  Access key for the first of two mandatory MDB entries for
 *  LM/DM offloaded endpoints
 */
#define MDB_PART_1_ACCESS 0
/**
 *  Access key for the second of two mandatory MDB entries for
 *  LM/DM offloaded endpoints
 */
#define MDB_PART_2_ACCESS 1

/** Access key for the mandatory MDB entry for 1/4 endpoints  */
#define MDB_Q_ENTRY_ACCESS 0

/** Access keys for the MDB entries for 48B MAID */
#define MDB_EXTRA_DATA_HDR_ACCESS  2
#define MDB_EXTRA_DATA_PLD1_ACCESS 3
#define MDB_EXTRA_DATA_PLD2_ACCESS 4
#define MDB_EXTRA_DATA_PLD3_ACCESS 5
#define MDB_EXTRA_DATA_PLD4_ACCESS 6
#define MDB_EXTRA_DATA_PLD5_ACCESS 7

/** maximum size of MEP_DB or MDB extra data header + extra data payload entries */
#define OAM_OAMP_EXTRA_DATA_MAX_SIZE 80

/** MEP PE PROFILE and TCAM constants */
#define DNX_OAM_OAMP_OPCODE_CCM_CCM_LM SAL_BIT(0)

#define DNX_OAM_OAMP_GACH_SELECT   0
#define DNX_OAM_OAMP_OPCODE_SELECT 1

/** LM_DM find and add flags */
#define LM_DM_FIND_AND_ADD 0
#define LM_DM_FIND_ONLY 1

typedef struct
{
    /** See flag mask definitions named OAM_LM_MEP_XXX  */
    uint32 flags;

    /** Local LM count for transmitted packets - read only */
    uint32 lm_my_tx;

    /** Local LM count for received packets - read only */
    uint32 lm_my_rx;

    /** Remote LM count for transmitted packets - read only */
    uint32 lm_peer_tx;

    /** Remote LM count for received packets - read only */
    uint32 lm_peer_rx;

    /** Accumulated far endpoint packet losses - read only */
    uint32 acc_lm_far;

    /** Accumulated near endpoint packet losses - read only */
    uint32 acc_lm_near;

    /**
     *  Entry to use for LM_DB entry for self-contained endpoints or
     *  second "dynamic" MEP DB entry for LM/DM offloaded endpoints.
     */
    uint32 flex_lm_entry;

    /** Last loss measurement value from far endpoint - read only */
    uint16 last_lm_far;

    /**
     *  Last loss measurement value from near endpoint - read
     *  only
     */
    uint16 last_lm_near;

    /**
     *  Highest number packet losses from a single far endpoint -
     *  read only
     */
    uint16 max_lm_far;

    /**
     *  Highest number packet losses from a single near endpoint -
     *  read only
     */
    uint16 max_lm_near;

    /**
     *  Profile - select the least 3 significant bytes of the MAC
     *  destination address in LMM injection
     */
    uint8 lmm_dmm_da_profile;

    /*
     * LM DB entry ID - Entry ID of the LM_DB entry in case of self
     * contained endpoints. If it is non zero, indicates LM is enabled
     * as well on the endpoint.  - Read only
     */
    uint32 lm_db_entry_idx;
    /*
     * LM STAT entry ID - Entry ID of the LM_STAT entry in case of self
     * contained endpoints. If it is non zero, indicates LM STAT is enabled
     * as well on the endpoint.  - Read only
     */
    uint32 lm_stat_entry_idx;

    /*
     * OAMP Mep profile
     */
    uint8 mep_profile;

    /*
     * The OAMP MEP DB counter_pointer and core_id required for SLM counting
     */
    uint32 slm_counter_pointer;
    uint32 slm_core_id;
} dnx_oam_oamp_endpoint_lm_params_t;

/** Flags used in DM APIs   */

/** Add a one-way DM statistics entry   */
#define DNX_OAMP_OAM_DM_MEP_MEASURE_ONE_WAY  SAL_BIT(0)

/** Add a two-way DM statistics entry   */
#define DNX_OAMP_OAM_DM_MEP_MEASURE_TWO_WAY  SAL_BIT(1)

/** Delay update flag */
#define DNX_OAMP_OAM_DM_MEP_UPDATE           SAL_BIT(2)

typedef struct
{
    /** See flag mask definitions named DNX_OAM_DM_MEP_XXX  */
    uint32 flags;

    /**
     *  Entry to use for DM_STAT_ONE_WAY entry or DM_STAT_TWO_WAY_ENTRY.
     *  Relevant on for self contained mode where LM has not been
     *  added, or for offloaded entries.
     */
    uint32 flex_dm_entry;

    /** Last value of two-way delay measurement - read only */
    uint8 last_delay[TWO_WAY_DELAY_SIZE];

    /** Highest two-way delay measurement - read only */
    uint8 max_delay[TWO_WAY_DELAY_SIZE];

    /** Lowest two-way delay measurement - read only */
    uint8 min_delay[TWO_WAY_DELAY_SIZE];

    /** Highest one-way delay measurement (including 1DM) - read only */
    uint8 max_delay_one_way[ONE_WAY_DELAY_SIZE];

    /** Lowest one-way delay measurement (including 1DM) - read only */
    uint8 min_delay_one_way[ONE_WAY_DELAY_SIZE];

    /** Last value of one-way delay measurement (including 1DM) - read only */
    uint8 last_delay_one_way[ONE_WAY_DELAY_SIZE];

    /** Highest one-way delay measurement - read only */
    uint8 max_delay_one_way_near_end[ONE_WAY_DELAY_SIZE];

    /** Lowest one-way delay measurement - read only */
    uint8 min_delay_one_way_near_end[ONE_WAY_DELAY_SIZE];

    /** Last value of one-way delay measurement - read only */
    uint8 last_delay_one_way_near_end[ONE_WAY_DELAY_SIZE];
    /**
     *  Profile - select the least 3 significant bytes of the MAC
     *  destination address in LMM/DMM injection
     */
    uint8 lmm_dmm_da_profile;

    /*
     * DM STAT entry ID - Entry ID of the DM_STAT entry in case of self
     * contained endpoints. If it is non zero, indicates DM is enabled
     * as well on the endpoint.  - Read only
     */
    uint32 dm_stat_entry_idx;

    /*
     * OAMP Mep profile
     */
    uint8 mep_profile;

    /*
     * OAMP MEP PE profile
     */
    uint8 mep_pe_profile;
} dnx_oam_oamp_endpoint_dm_params_t;

typedef struct
{
    /** Interface status*/
    uint8 interface_status;

    /** Port status*/
    uint8 port_status;

} dnx_oam_oamp_oam_state_t;

typedef struct
{
    /** BFD state*/
    uint8 state;

    /** Diag profile */
    uint8 diag_profile;

    /** Detect multiplier*/
    uint16 detect_multiplier;

    /** Flags profile used for Jericho2 */
    uint8 flags;

} dnx_oam_oamp_bfd_state_t;

typedef struct
{
    /** oam id*/
    uint16 oam_id;

    /** Interval used for Loss of continuity in microseconds*/
    uint32 period;

    /** A number indicates the maximal time that can pass with no CCM from this MEP. After this time the OAMP issues LoC interrupt.*/
    uint32 lifetime;

    /** Determine the resolution of the lifetime and last-CCM-lifetime fields*/
    uint32 lifetime_units;

    /** Threshold for loss of continuity mechanism */
    uint8 loc_clear_threshold;

    /** punt profile */
    uint8 punt_profile;

    /** punt good packets profile */
    uint8 punt_good_profile;

    /** Punt next received good packet indication */
    uint8 punt_next_good_packet;

    /** rmep status for oam and bfd*/
    union
    {
        dnx_oam_oamp_oam_state_t eth_state;

        dnx_oam_oamp_bfd_state_t bfd_state;
    } rmep_state;

    /** Indication that last CCM message had the RDI bit(read only)*/
    uint8 rdi_received;

    /** Indication Loss of continuity happen(read only) */
    uint8 loc;

    /** Indication of timeout state (timeout/timein) */
    uint8 last_ccm_lifetime_valid_on_create;

} dnx_oam_oamp_rmep_db_entry_t;

/**
 *  This enumerator lists the 1 bit fields in the OAMP MEP DB
 *  table - to be used for masking when reading from/writing
 *  to 32-bit "flags" variables.  Note that when both the
 *  OAMP_LM_DM_OFFLOADED flag and the OAMP_MEP_Q_ENTRY flag
 *  are set, the entry is a type 2 LM/DM offloaded entry.
 */
typedef enum
{
    OAMP_MEP_UPDATE,
    OAMP_MEP_LM_DM_OFFLOADED,
    OAMP_MEP_Q_ENTRY,
    OAMP_MEP_IS_UPMEP,
    OAMP_MEP_RDI_FROM_SCANNER,
    OAMP_MEP_RDI_FROM_PACKET,
    OAMP_MEP_PORT_TLV_EN,
    OAMP_MEP_PORT_TLV_VAL,
    /**
     * This flag is always set to multicast,
     * because unicast is not supported.
     */
    OAMP_MEP_MC_UC_SEL,
    OAMP_MEP_BFD_TUNNEL_MPLS_ENABLE,
    OAMP_MEP_MICRO_BFD,
    OAMP_MEP_BFD_ECHO,
    OAMP_MEP_EGRESS_INJECTION,
    OAMP_MEP_ACH,
    OAMP_MEP_GAL,
    OAMP_MEP_ROUTER_ALERT,
    OAMP_MEP_LAST_ENTRY,
    OAMP_MEP_SET_DISCR_MSB,
    OAMP_MEP_SEAMLESS_BFD,
    OAMP_MEP_LM_CNTRS_VALID,
    OAMP_MEP_MEASURE_NEXT_RECEIVED_SLR,
    OAMP_MEP_LM_ENABLE,
    OAMP_MEP_DM_ENABLE,
    OAMP_MEP_LM_STAT_ENABLE,
    OAMP_MEP_DM_STAT_ENABLE,
    OAMP_MEP_RESET_LM_STATISTICS,
    OAMP_MEP_RESET_DM_STATISTICS,
    OAMP_MEP_COPY_LM_STATISTICS,
    OAMP_MEP_COPY_DM_STATISTICS,
    OAMP_MEP_UP_MEP_SERVER,
    OAMP_MEP_RFC_6374_ENABLE
} dnx_oam_oamp_mep_db_flags_e;

/**
 *  This structure is used to pass arguments to the OAMP MEP DB
 *  tables
 */
typedef struct
{
    union
    {
        struct
        {
            uint32 bfd_your_disc;
            uint32 bfd_ipv4_dip;
            uint8 bfd_tx_rate;
            uint8 bfd_src_ip_profile;
            uint8 bfd_detect_mult;
            uint8 bfd_min_tx_interval_profile;
            uint8 bfd_min_rx_interval_profile;
            uint8 bfd_diag_profile;
            uint8 bfd_flags_profile;
            uint8 bfd_ip_ttl_tos_profile;
            uint8 bfd_sta;
            uint8 bfd_ach_sel;
            uint32 local_discr_lsb;
        } bfd_only;
        struct
        {
            uint32 vsi;
            uint32 server_destination;
            uint16 oam_maid;
            uint16 oam_inner_vid;
            uint16 oam_outer_vid;
            uint16 oam_mep_id;
            uint16 oam_sa_mac_lsb;
            uint8 oam_sa_mac_msb_profile;
            uint8 oam_ccm_interval;
            uint8 oam_mdl;
            uint8 oam_inner_tpid_index;
            uint8 oam_inner_dei_pcp;
            uint8 oam_outer_tpid_index;
            uint8 oam_outer_dei_pcp;
            uint8 oam_icc_index;
            uint8 oam_nof_vlan_tags;
            uint8 oam_prt_qualifier_profile;
            uint8 oam_interface_status_tlv_code;
            uint8 oam_lmm_da_profile;
            uint8 tx_signal;
            uint8 ivec_address_factor;
        } oam_only;
        struct
        {
            uint16 crc_val1;
            uint16 crc_val2;
            uint16 opcode_bmp;
            uint8 data_segment[DATA_SEG_LEN];
            uint8 extra_data_len;
        } extra_data;
        struct
        {
            uint32 lm_my_tx;
            uint32 lm_my_rx;
            uint32 lm_peer_tx;
            uint32 lm_peer_rx;
            uint32 acc_lm_far;
            uint32 acc_lm_near;
            uint16 last_lm_far;
            uint16 last_lm_near;
            uint16 max_lm_far;
            uint16 max_lm_near;
            uint8 max_delay[TWO_WAY_DELAY_SIZE];
            uint8 min_delay[TWO_WAY_DELAY_SIZE];
            uint8 last_delay[TWO_WAY_DELAY_SIZE];
            uint8 last_delay_one_way[ONE_WAY_DELAY_SIZE];
            uint8 max_delay_one_way[ONE_WAY_DELAY_SIZE];
            uint8 min_delay_one_way[ONE_WAY_DELAY_SIZE];
            uint8 last_delay_one_way_near_end[ONE_WAY_DELAY_SIZE];
            uint8 max_delay_one_way_near_end[ONE_WAY_DELAY_SIZE];
            uint8 min_delay_one_way_near_end[ONE_WAY_DELAY_SIZE];
        } lm_dm;
        struct
        {
            uint32 session_id;
            uint8 lm_cw_choose;
            uint32 timestamp_format;
            uint8 dm_t_flag;
            uint8 dm_ds;
        } rfc_6374_only;
    } exclusive;
    struct
    {
        uint32 label;
        uint8 push_profile;
    } mpls_pwe;
    uint32 flags;
    uint32 fec_id_or_glob_out_lif;
    uint32 counter_ptr;
    uint16 dest_sys_port_agr;
    uint32 extra_data_ptr;
    uint16 flex_lm_dm_ptr;
    dbal_enum_value_field_oamp_mep_type_e mep_type;
    uint8 itmh_tc_dp_profile;
    uint8 ip_ttl_tos_probile;
    uint8 mep_profile;
    uint8 mep_pe_profile;
    u_port_access unified_port_access;
    uint8 ip_subnet_len;
    uint8 counter_interface;
    uint8 crps_core_select;
} dnx_oam_oamp_mep_db_args_t;

typedef enum
{
    DNX_OAMP_OAM_MA_NAME_TYPE_ICC = 0,
    DNX_OAMP_OAM_MA_NAME_TYPE_SHORT,
    DNX_OAMP_OAM_MA_NAME_TYPE_NOF
} dnx_oam_ma_name_type_e;

/*
 *Get the group name (string) and returns a dnx_oam_ma_name_type_e enum.
 * Macro assumes group is one of the two supported formats:
 * Short: {1,3,2,{two byte name},0,0,...,0}
 * ICC based: {1,32,13,{13 byte name},0,0,...,0}
 */
#define BCM_DNX_OAM_GROUP_NAME_TO_NAME_TYPE(name) \
            ( (name[1]==DNX_OAMP_OAM_GROUP_MA_NAME_FORMAT_ICC) ?\
            DNX_OAMP_OAM_MA_NAME_TYPE_ICC : \
             (name[1]==DNX_OAMP_OAM_GROUP_MA_NAME_FORMAT_SHORT)?\
            DNX_OAMP_OAM_MA_NAME_TYPE_SHORT : DNX_OAMP_OAM_MA_NAME_TYPE_NOF)

/* oam_group_umc_data_t  used to store OAM group UMC data*/
typedef uint8 oam_group_umc_data_t[5];

/** Maximum value for sampling_ratio field */
#define MAX_SAMPLING_RATIO 8

/** Maximum value for bfd_period_cluster field */
#define MAX_BFD_PERIOD_CLUSTER 8

typedef struct
{
    /*
     * Rate of sampling packets to CPU. values ranges from 0 to 7 representing
     * the number of packets (with events) required to be received before
     * sampling a packet to CPU.
     */
    uint8 punt_rate;
    /*
     * '0' disables punt of packet in case of state/RDI change or validity check fail;
     * '1' enables the punt according to Punt Rate
     */
    uint8 punt_enable;
    /*
     * '00' Do not update state and RDI according to received packet; generate event.
     * '01' Update state and RDI according to received packet; don't generate event.
     * '10' Update state and RDI only if event FIFO is not full; generate event.
     * '11' Update state and RDI  regardless of event FIFO; generate event.
     */
    dbal_enum_value_field_profile_rx_state_update_en_e rx_state_update_en;
    /*
     * '00' Do not update rmep_db state on scan; generate event.
     * '01' Update rmep_db state on scan; don't generate event.
     * '10' Update rmep_db state only if event FIFO is not full; generate event.
     * '11' Update rmep_db state regardless of event FIFO; generate event.
     */
    dbal_enum_value_field_profile_scan_state_update_en_e profile_scan_state_update_en;

    /*
     * Enable the scanner machine to update MEP DB RDI indication in case LoC (timeout) event detected
     */
    uint8 mep_rdi_update_loc_en;

    /*
     * Enable the scanner machine to update MEP DB RDI indication in case LoC clear (time-in) event detected
     */
    uint8 mep_rdi_update_loc_clear_en;

    /*
     * Enables the RX machine to update the MEP DB RDI indication by copy the RDI indication from the received valid
     * CCM packet
     */
    uint8 mep_rdi_update_rx_en;
} dnx_oam_oamp_punt_event_profile_t;

/*
 * Structure with punt good profile HW information
 * to be passed from SW related functions to functions
 * related to HW write/clear
 */
typedef struct dnx_oam_oamp_punt_good_profile_temp_data_s
{
    /** The new profile id */
    uint8 new_punt_good_profile;

    /** The new profile data */
    uint16 new_punt_good_profile_data;

    /** Whether HW needs to be written with this new profile */
    uint8 write_new_punt_good_profile;

    /** Old punt good profile, in case of update to new profile */
    uint8 old_punt_good_profile;

    /*
     * Whether to delete old profile or not.
     * This is true only in case of update
     */
    uint8 delete_old_punt_good_profile;
} dnx_oam_oamp_punt_good_profile_temp_data_t;

typedef enum
{
    OAMP_MEP_TX_OPCODE_CCM_BFD = 0,
    OAMP_MEP_TX_OPCODE_LMM = 1,
    OAMP_MEP_TX_OPCODE_DMM = 2,
    OAMP_MEP_TX_OPCODE_OP0 = 3,
    OAMP_MEP_TX_OPCODE_OP1 = 4,
    OAMP_MEP_TX_OPCODE_MAX_SUPPORTED = 5
} dnx_oam_oamp_tx_opcode;

/**
 *  Structure used as a parameter for
 *  dnx_oamp_mep_db_find_or_add_lm_dm_entry, the function that
 *  searches the LM/DM entries associated with an OAM endpoint
 *  for a certain type of entry
 */
typedef struct
{
    /**
     *  Entry ("OAM_ID" format) to which the CCM entry's flex LM/DM field is
     *  currently pointing
     */
    uint32 first_entry;

    /**
     *  Entry ("OAM_ID" format) specified by the user to which the flex LM/DM field
     *  should point. If the first entry field points to a legitimate
     *  LM/DM entry, this field is ignored.
     */
    uint32 param_entry;

     /**
      *  Entry number ("OAM_ID" format) where entry data should be
      *  written
      */
    uint32 resulting_entry;

     /**
      * boolean that indicates whether an existing entry was found,
      * or not.
      */
    uint8 update_entry;

     /**
      *  boolean that indicates whether this MEP already had an
      *  entry marked "last entry," which should now be unmarked.
      */
    uint8 clear_last_entry;

     /**
      *  Type of entry that is being sought (one of four possible
      *  types.)
      */
    dbal_enum_value_field_oamp_mep_type_e search_type;

} dnx_oam_oamp_lm_dm_search_t;

/*
 * Structure with punt profile HW information
 * to be passed from SW related functions to functions
 * related to HW write/clear
 */
typedef struct dnx_oam_rmep_punt_profile_temp_data_s
{
    /** The new profile id */
    int new_punt_profile;

    /** The new punt profile data */
    dnx_oam_oamp_punt_event_profile_t new_punt_profile_data;

    /** Whether HW needs to be written with this new profile */
    uint8 write_new_punt_profile;

    /** Old punt profile, in case of update to new profile */
    int old_punt_profile;

    /*
     * Whether delete old profile or not.
     * This is true only in case of update
     */
    uint8 delete_old_punt_profile;
} dnx_oam_rmep_punt_profile_temp_data_t;

/**
 * \brief - This function copies a bit sequence.
 *
 * \param [out] dst_buffer - Pointer to destination.
 * \param [in] dst_offset - Offset from dst_buffer to
 *        start writing, in bits.  For 0, starts from LSB
 *        of the byte to which dst_buffer is pointing.
 * \param [in] src_buffer - Pointer to source.
 *        this MEP type.
 * \param [in] src_offset - Offset from src_buffer to
 *        start reading, in bits.  For 0, starts from LSB
 *        of the byte to which src_buffer is pointing.
 * \param [in] nof_bits_to_copy - Number of bits to copy
 * \param [in] read_from_hw - TRUE for hardware source
 *        format and software destination format, FALSE
 *        otherwise.
 *
 * \return
 *   None
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
void dnx_oamp_copy_bit_array(
    uint8 *dst_buffer,
    uint32 dst_offset,
    const uint8 *src_buffer,
    uint32 src_offset,
    uint32 nof_bits_to_copy,
    uint8 read_from_hw);

/**
 * \brief - This function creates or modifies the dbal entries
 *        needed for an accelerated OAM CCM endpoint
 *
 * \param [in] unit - Number of hardware unit used
 * \param [in] oam_id - Index of OAM endpoint.  For full
 *        entry this must be a multiple or 4.
 * \param [in] entry_values - Structure containing all the
 *        endpoint parameters
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oamp_mep_db_ccm_endpoint_set(
    int unit,
    uint16 oam_id,
    dnx_oam_oamp_ccm_endpoint_t * entry_values);

/**
 * \brief - This function deletes the entries used for
 *        accelerating an OAM CCM endpoint from dbal (clearing
 *        them from the hardware tables as well)
 *
 * \param [in] unit - Number of hardware unit used
 * \param [in] oam_id - Index of OAM endpoint.  For full
 *        entry this must be a multiple or 4.
 * \param [in] extra_data_length - extra data length in bits
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oamp_mep_db_ccm_endpoint_clear(
    int unit,
    uint16 oam_id,
    uint32 extra_data_length);

/**
 * \brief - This function return the Index of Remote MEP according OAM-ID and MEP-ID.
 *
 * \param [in] unit - Number of hardware unit used
 * \param [in] oam_id - Index of OAM endpoint.
 * \param [in] mep_id - Index of Maintenance End Point
 * \param [out] rmep_id - Remote MEP DB(RMEP_INDEX) id.
 *
 * \return
 *   shr_error_e
 *   \retval _SHR_E_NONE - no error
 *   \retval _SHR_E_NOT_FOUND - entry not exist
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_rmep_index_db_get(
    int unit,
    uint16 oam_id,
    uint16 mep_id,
    uint32 *rmep_id);

/**
 * \brief - This function choose whenever the RMEP to be updated.
 *          In case of different value between old and new fields in RMEP DB the DB will be updated.
 *
 * \param [in] unit - Number of hardware unit used
 * \param [in] is_oam - Indication if RMEP is oam('1) of BFD('0')
 * \param [in] old_entry_values - Remote MEP parameters in the DB.
 * \param [in] new_entry_values - Remote MEP parameters set for update.
 *
 * \return
 *   \retval TRUE - there is a difference, the DB need to be updated.
 *   \retval FALSE - there isn't a difference, the DB shouldn't be updated.
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
int dnx_oam_oamp_rmep_compare(
    int unit,
    int is_oam,
    dnx_oam_oamp_rmep_db_entry_t * old_entry_values,
    dnx_oam_oamp_rmep_db_entry_t * new_entry_values);

/**
 * \brief - This function add Remote MEP to OAMP_RMEP_DB table.
 *          In case the entry is offloaded function add static part of Remote MEP to OAMP_RMEP_STATIC_DATA_DB table
 *
 * \param [in] unit - Number of hardware unit used
 * \param [in] rmep_id - Remote MEP ID
 * \param [in] is_oam - Indication if RMEP is oam('1) of BFD('0')
 * \param [in] is_update - Indication if rmep is new or update
 * \param [in] rmep_entry - Remote MEP parameters
 *
 * \return
 *   shr_error_e
 *   \retval _SHR_E_NONE - no error
 *   \retval _SHR_E_NOT_FOUND - entry not exist(in case is_update is '1')
 *   \retval _SHR_E_EXIST - entry already exist(in case is_update is '0'

 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_rmep_add(
    int unit,
    uint32 rmep_id,
    uint32 is_oam,
    uint32 is_update,
    dnx_oam_oamp_rmep_db_entry_t * rmep_entry);

/**
 * \brief - This function return Remote MEP parameters according Remote MEP ID.
 *          Parameters are taken from OAMP_RMEP_DB table and in case of offloaded entry from  OAMP_RMEP_STATIC_DATA_DB table
 *
 * \param [in] unit - Number of hardware unit used
 * \param [in] rmep_id - Remote MEP ID
 * \param [in] is_oam - Indication if RMEP is oam('1) of BFD('0')
 * \param [out] rmep_entry - Remote MEP parameters
 *
 * \return
 *   shr_error_e
 *   \retval _SHR_E_NONE - no error
 *   \retval _SHR_E_NOT_FOUND
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_rmep_get(
    int unit,
    uint32 rmep_id,
    uint32 is_oam,
    dnx_oam_oamp_rmep_db_entry_t * rmep_entry);

/**
 * \brief - This function remove Remote MEP entry from OAMP_RMEP_DB.
 *          In case the entry is offloaded remove static part of Remote MEP from OAMP_RMEP_STATIC_DATA_DB table
 *
 * \param [in] unit - Number of hardware unit used
 * \param [in] rmep_id - Remote MEP ID
 * \param [in] is_oam - Indication if RMEP is oam('1) of BFD('0')
 *
 * \return
 *   shr_error_e
 *   \retval _SHR_E_NONE - no error
 *   \retval _SHR_E_NOT_FOUND - entry not exist
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_rmep_remove(
    int unit,
    uint32 rmep_id,
    uint32 is_oam);

/**
 * \brief - This function gets OAMP punt profile from HW.
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] profile_id - Punt profile index.
 * \param [out] punt_profile_data - Punt profile data read from HW
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   This function get the memory under PUNT_PROFILE_TBL DBAL table.
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_punt_profile_tbl_get(
    int unit,
    int profile_id,
    dnx_oam_oamp_punt_event_profile_t * punt_profile_data);

/**
 * \brief - This function writes OAMP punt profile into HW.
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] profile_id - Punt profile index.
 * \param [in] punt_profile_data - Punt profile data to write to HW
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   This function set the memory under PUNT_PROFILE_TBL DBAL table.
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_punt_profile_tbl_set(
    int unit,
    int profile_id,
    const dnx_oam_oamp_punt_event_profile_t * punt_profile_data);

/**
 * \brief - Conversion of period in milliseconds to RMEP number of scans
 *
 * \param [in] unit - Number of hardware unit used
 * \param [in] period - Period in milliseconds
 * \param [out] nof_hw_scans - Number of RMEP DB scans
 *
 * \return
 *   shr_error_e
 *
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_period_to_rmep_db_nof_scans(
    int unit,
    int period,
    uint16 *nof_hw_scans);

/**
 * \brief - Conversion of RMEP number of scans to period in milliseconds
 *
 * \param [in] unit - Number of hardware unit used
 * \param [in] nof_hw_scans - Number of RMEP DB scans
 * \param [out] period - Period in milliseconds
 *
 * \return
 *   shr_error_e
 *
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_rmep_db_nof_scans_to_period(
    int unit,
    uint16 nof_hw_scans,
    int *period);

/**
 * \brief - OAM/BFD punt good profile allocate function
 *          based on MEP endpoint info.
 *
 * \param [in] unit - Number of hardware unit used
 * \param [in] is_update - Indication if MEP is new or is updated
 * \param [in] punt_good_packet_period - Period in milliseconds
 * \param [in] old_profile_id - If update - the ID of the old profile
 * \param [out] hw_write_data - Punt good profile HW info for the requested MEP
 *
 * \return
 *   shr_error_e
 *
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_punt_good_profile_alloc(
    int unit,
    uint8 is_update,
    int punt_good_packet_period,
    int old_profile_id,
    dnx_oam_oamp_punt_good_profile_temp_data_t * hw_write_data);

/**
 * \brief - Utility function for OAM/BFD MEP Punt good profile HW configuration.
 *          This function does HW writes/clear based on information in
 *          the structure.
 *
 * \param [in] unit - Number of hardware unit used
 * \param [in] hw_write_data - The HW write/clear information
 *
 * \return
 *   shr_error_e
 *
 * \see
 *   * None
 */
shr_error_e dnx_oam_remote_endpoint_punt_good_profile_hw_configure(
    int unit,
    const dnx_oam_oamp_punt_good_profile_temp_data_t * hw_write_data);

/**
 * \brief - Get OAM/BFD MEP punt good profile
 *          and store it in endpoint_info.
 *
 * \param [in] unit - Number of hardware unit used
 * \param [in] punt_good_profile - Punt good profile of the requested MEP
 * \param [out] punt_good_packet_period - Period in milliseconds to be set
 *              in endpoint_info
 *
 * \return
 *   shr_error_e
 *
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_punt_good_profile_get(
    int unit,
    uint8 punt_good_profile,
    int *punt_good_packet_period);

/**
 * \brief - OAM/BFD punt good profile free function
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] punt_good_profile - Punt good profile for the requested
 *             MEP.
 * \param [out] hw_write_data - Profile deletion info for HW.
 *
 * \return
 *   shr_error_e
 *
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_punt_good_profile_free(
    int unit,
    int punt_good_profile,
    dnx_oam_oamp_punt_good_profile_temp_data_t * hw_write_data);

/**
 * \brief -
 * Initialize OAMP module.
 * This function calls initialazation functions for OAMP registers/memories
 *
 * Called from oam init
 *
 * \param [in] unit - Number of hardware unit used
 *
 * \return
 *   \retval Non-zero (!= _SHR_E_NONE) in case of an error
 *   \retval Zero (= _SHR_E_NONE) in case of NO ERROR
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_init(
    int unit);

/**
 * \brief -
 * De-initialize OAMP module.
 *
 * \param [in] unit - Number of hardware unit used
 *
 * \return
 *   \retval Non-zero (!= _SHR_E_NONE) in case of an error
 *   \retval Zero (= _SHR_E_NONE) in case of NO ERROR
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_deinit(
    int unit);

/**
 * \brief - This function add priority(tc/dp) profile that is used in ITMH header
 *
 * \param [in] unit - Number of hardware unit used.
* \param [in] profile - Priority profile(maximum 8 profiles)
 * \param [in] tc - traffic class
 * \param [in] dp - drop precedence
 * \param [in] qos - pph qos
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_itmh_priority_profile_set(
    int unit,
    uint8 profile,
    uint8 tc,
    uint8 dp,
    uint8 qos);

/**
 * \brief - This function provide priority(tc/dp) according profile.
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] profile - Priority profile(maximum 8 profiles)
 * \param [out] tc - traffic class
 * \param [out] dp - drop precedence
 * \param [out] qos - pph qos
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_itmh_priority_profile_get(
    int unit,
    uint8 profile,
    uint8 *tc,
    uint8 *dp,
    uint8 *qos);

/**
 * \brief - This function provide mapping of local port to system port
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] pp_port_profile - key to table entry
 * \param [out] system_port - system_port
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_local_port_to_system_port_get(
    int unit,
    uint16 pp_port_profile,
    uint32 *system_port);

/**
 * \brief - This function set Source MAC profile(33 MSB bits)
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] profile - mac profile(maximum 2 profiles)
 * \param [in] sa_mac_addr_msb - Source mac address(only 33 msb bits are relevant
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_sa_mac_msb_profile_set(
    int unit,
    uint8 profile,
    bcm_mac_t sa_mac_addr_msb);

/**
 * \brief - This function provide Source MAC address(33 MSB bits) according profile
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] profile - mac profile(maximum 2 profiles)
 * \param [out] sa_mac_addr_msb - Source mac address(only 33 msb bits are relevant
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_sa_mac_msb_profile_get(
    int unit,
    uint8 profile,
    bcm_mac_t sa_mac_addr_msb);

/**
 * \brief - Function set/update/remove profiles that were changed during endpoint create/modify/destroy
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] mep_hw_profiles_write_data - parameters of profiles
 *
 * \return
 *   shr_error_e
 *
 * \see
 *   * oam_oamp_profile_hw_data_t
 */
shr_error_e dnx_oam_oamp_profile_hw_set(
    int unit,
    oam_oamp_profile_hw_data_t * mep_hw_profiles_write_data);

/**
 * \brief - map bcm endpoint type to oamp mep db type
 *
 * \param [in] unit - Relevant unit.
 * \param [in] bcm_mep_type - MEP BCM Type
 * \param [out] mep_db_mep_type - MEP type used in MEP_DB
 *
 * \retval Error indication.
 *
 */
shr_error_e dnx_oam_oamp_endpoint_bcm_mep_type_to_mep_db_mep_type(
    int unit,
    const bcm_oam_endpoint_type_t bcm_mep_type,
    dbal_enum_value_field_oamp_mep_type_e * mep_db_mep_type);

/**
 * \brief
 * This function calculate internal ccm interval value according requested period.
 */
shr_error_e dnx_oam_oamp_ccm_period_to_ccm_interval(
    int unit,
    int ccm_period,
    dbal_enum_value_field_ccm_interval_e * ccm_interval);

/**
 * \brief - Initialize mep db parameters that relevant to Eth OAM only
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] endpoint_info - info structure of the requested MEP
 * \param [out] mep_db_entry - return filled oam eth fields of mep_db entry according endpoint_info
 *  Updated fields are:
 *               outer_tpid,inner_tpid
 *               outer_tpid_index,inner_tpid_index
 *               outer_vid,inner_vid
 *               outer_pcp_dei,inner_pcp_dei
 *               nof_vlan_tags
 *               sa_gen_lsb
 *               sa_gen_msb_profile
 * \param [out] mep_hw_profiles_write_data - return new profile for outer_tpid,inner_tpid and sa mac msb if allocated
 * \return
 *   shr_error_e
 *
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_ccm_endpoint_eth_oam_init(
    int unit,
    const bcm_oam_endpoint_info_t * endpoint_info,
    dnx_oam_oamp_ccm_endpoint_t * mep_db_entry,
    oam_oamp_profile_hw_data_t * mep_hw_profiles_write_data);

/**
 * \brief - This function will update ICC index and MA ID
 *          details of endpoint structure based on OAM group info.
 * \param [in] unit - Number of hardware unit used.
 * \param [in] group_name - pointer to  group name.
 * \param [out] mep_db_entry -
 *  Pointer to OAM endpoint structure that need to be updated with group info.
 *  Updated fields are:
 *               icc_index
 *               maid

 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_update_accelarated_endpoint_info_with_group_config(
    int unit,
    const uint8 *group_name,
    dnx_oam_oamp_ccm_endpoint_t * mep_db_entry);

/**
 * \brief - This function gets the OAMP RMEP DB entry lifetime and lifetime_unit
 *          value from RMEP structure CCM period paramter
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] period_us - RMEP CCM period value in microseconds
 * \param [out] lifetime - lifetime value in RMEP DB entry
 * \param [out] lifetime_units - lifetime_unit value in RMEP DB entry
 *
 * \return
 *   void
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
void dnx_oam_oamp_period_to_lifetime(
    int unit,
    uint32 period_us,
    uint32 *lifetime,
    uint32 *lifetime_units);

/**
 * \brief
 * This function calculate period(ccm/bfd interval) according lifetime and lifetime units.
 * Period will be in microseconds.
 * \param [in] unit - Number of hardware unit used.
 * \param [in] lifetime - lifetime value in RMEP DB entry
 * \param [in] lifetime_units - lifetime_unit value in RMEP DB entry
 * \param [out] period_us - RMEP CCM period value in microseconds
 *
 * \return
 *   void
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
void dnx_oam_oamp_lifetime_to_period(
    int unit,
    uint32 lifetime,
    uint32 lifetime_units,
    uint32 *period_us);

/**
 * \brief - This function checks that the specified OAMP_MEP_DB
 *          short entry either has sub-index 0, or that the short
 *          entry with sub-index 0 has the requested entry type.
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] oam_id - number of entry being added.
 * \param [in] req_mep_type - type for comparison.
 * \param [out] sub_index - Calculated sub-index
 * \param [out] is_leader_alloc - TRUE if entry with sub-index
 *        0 is allocated, FALSE otherwise.
 * \param [out] is_leader_type_match - TRUE if entry type is a
 *        match, FALSE otherwise
 *
 * \return
 *   void
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_short_entry_type_check_mep_db(
    int unit,
    uint16 oam_id,
    dbal_enum_value_field_oamp_mep_type_e req_mep_type,
    int *sub_index,
    uint8 *is_leader_alloc,
    uint8 *is_leader_type_match);

/**
 * \brief
 * This function calculate period ccm period value according requested interval.
 * \param [in] unit - number of hardware unit used
 * \param [in] ccm_interval - ENUM value for the ccm period.
 * \param [in,out] ccm_period - CCM period in milliseconds.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_ccm_interval_to_ccm_period(
    int unit,
    dbal_enum_value_field_ccm_interval_e ccm_interval,
    int *ccm_period);

/**
 * \brief
 * This function update the diag field local and remote when there is a request for no 1 to 1 mapping.
 * \param [in] diag - field
 *
 * \return
 *   the value of the mapping
 *
 * \remark
 *   * None
 * \see
 *   * None
 */

int dnx_bfd_endpoint_map_diag(
    int diag);

/**
* \brief
*  This function calculate mep_id_shift and RX/TX statistics enable per profile.
* \par DIRECT INPUT:
*   \param [in] unit  -
*   Relevant unit.
*   \param [in] flags  -
*   Endpoint flags2 parameter, used to enable RX/TX statistics and per opcode count.
*   \param [out] mep_profile_data  -
*   hold information for mep_profile.
* \par INDIRECT INPUT:
*   * none
* \par DIRECT OUTPUT:
*   shr_error_param - Return relevant error.
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * None
*/
void dnx_oam_oamp_statistics_enable(
    int unit,
    uint32 flags,
    dnx_oam_mep_profile_t * mep_profile_data);

/**
 * \brief
 * This function initializes the event DMA interrupts of OAMP
 * \param [in] unit - number of hardware unit used
 *
 * \return
 *   * None
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_event_dma_init(
    int unit);

/**
 * \brief
 * This function de-initializes the event DMA interrupts of OAMP
 * \param [in] unit - number of hardware unit used
 *
 * \return
 *   * None
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_event_dma_deinit(
    int unit);

/**
 * \brief
 * This function initializes the report DMA interrupts of OAMP statistics
 * \param [in] unit - number of hardware unit used
 *
 * \return
 *   * None
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_stat_dma_init(
    int unit);

/**
 * \brief
 * This function de-initializes the repo;prt DMA interrupts of OAMP Statistics
 * \param [in] unit - number of hardware unit used
 *
 * \return
 *   * None
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_stat_dma_deinit(
    int unit);

/**
 * \brief - This is the call back function used in sal_dpc call version1.
 *
 * \param [in] unit - number of hardware unit used
 * \param [in] entry - pointer to host entry being processed
 * \param [in] entry_size - size of host entry being processed
 * \param [in] entry_number - entry number
 * \param [in] total_amount_of_entries - total number of entries
 * \param [in] user_data - user data
 *
 * \return
 *   void
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
void dnx_oam_oamp_v1_dma_event_handler(
    int unit,
    void *entry,
    int entry_size,
    int entry_number,
    int total_amount_of_entries,
    void **user_data);

/**
 * \brief - This is the call back function used in sal_dpc call version2 for ccm.
 *
 * \param [in] unit - number of hardware unit used
 * \param [in] entry - pointer to host entry being processed
 * \param [in] entry_size - size of host entry being processed
 * \param [in] entry_number - entry number
 * \param [in] total_amount_of_entries - total number of entries
 * \param [in] user_data - user data
 *
 * \return
 *   void
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
void dnx_oam_oamp_v2_dma_ccm_event_handler(
    int unit,
    void *entry,
    int entry_size,
    int entry_number,
    int total_amount_of_entries,
    void **user_data);

/**
 * \brief - This is the call back function used in sal_dpc call version2 for bfd.
 *
 * \param [in] unit - number of hardware unit used
 * \param [in] entry - pointer to host entry being processed
 * \param [in] entry_size - size of host entry being processed
 * \param [in] entry_number - entry number
 * \param [in] total_amount_of_entries - total number of entries
 * \param [in] user_data - user data
 *
 * \return
 *   void
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
void dnx_oam_oamp_v2_dma_bfd_event_handler(
    int unit,
    void *entry,
    int entry_size,
    int entry_number,
    int total_amount_of_entries,
    void **user_data);
/**
 * \brief - This is the call back function used in sal_dpc call.
 *
 * \param [in] unit - number of hardware unit used
 * \param [in] entry - pointer to host entry being processed
 * \param [in] entry_size - size of host entry being processed
 * \param [in] entry_number - entry number
 * \param [in] total_amount_of_entries - total number of entries
 * \param [in] user_data - user data
 *
 * \return
 *   void
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
void dnx_oam_oamp_stat_dma_event_handler(
    int unit,
    void *entry,
    int entry_size,
    int entry_number,
    int total_amount_of_entries,
    void **user_data);

/**
 * \brief - This function sets a single OAM or BFD
 *          trap.
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] mep_type - Type of OAM/BFD MEP which
 *        the received packet is targeting.
 * \param [in] trap_code - Trap code to associate with
 *        this MEP type.
 * \param [in] index - index associated with the entry
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_rx_trap_codes_set(
    int unit,
    dbal_enum_value_field_oamp_mep_type_e mep_type,
    uint32 trap_code,
    uint32 index);

/**
 * \brief - Gets enable dynamic memory access for oamp block
 *
 * \param [in] unit - unit number
 * \param [in] enable - enable/disable 1/0
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oamp_dbal_dynamic_memory_access_get(
    int unit,
    uint32 *enable);

/**
 * \brief -
 * This is the function assigned to the oam event report thread.
 *
 * \param [in]  unit - unit id
 * \param [in]  info - pointer to the relevant thread data
 *
 * \return
 *   _shr_error_t
 *
 * \remark
 *   None
 *
 * \see
 *   None
 */
shr_error_e dnx_oam_oamp_event_fifodma_thread(
    int unit,
    void *info);

/**
 * \brief -
 * remove oam event report thread:dnx_oam_oamp_event_fifodma_thread
 *
 * \param [in]  unit - unit id
 *
 * \return
 *   _shr_error_t
 *
 * \remark
 *   None
 *
 * \see
 *   None
 */
shr_error_e dnx_oam_oamp_event_fifodma_deinit(
    int unit);

/**
 * \brief -
 * create oam event report thread:dnx_oam_oamp_event_fifodma_thread
 *
 * \param [in]  unit - unit id
 *
 * \return
 *   _shr_error_t
 *
 * \remark
 *   None
 *
 * \see
 *   None
 */
shr_error_e dnx_oam_oamp_event_fifodma_init(
    int unit);

/**
 * \brief - This function sets network QoS in PPH
 *          for OAMP injected packets.
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] network_qos - Network QoS in PPH.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_tx_pph_network_qos_set(
    int unit,
    uint32 network_qos);

/**
 * \brief - This function gets network QoS in PPH
 *          for OAMP injected packets.
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] network_qos - Network QoS in PPH.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e dnx_oam_oamp_tx_pph_network_qos_get(
    int unit,
    uint32 *network_qos);

/*
 * }
 */
#endif /* OAM_OAMP_H_INCLUDED */

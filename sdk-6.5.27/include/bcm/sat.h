/*
 * 
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 */

#ifndef __BCM_SAT_H__
#define __BCM_SAT_H__

#include <bcm/types.h>
#include <bcm/pkt.h>

/* SAT endpoint flags */
#define BCM_SAT_ENDPOINT_WITH_ID            0x01       /* Use the specified
                                                          endpoint ID */
#define BCM_SAT_ENDPOINT_REPLACE            0x02       /* Replace an existing
                                                          SAT endpoint */
#define BCM_SAT_ENDPOINT_UPMEP              0x04       /* Endpoint associated
                                                          with SAT UP-MEP */
#define BCM_SAT_ENDPOINT_DOWNMEP            0x08       /* Endpoint associated
                                                          with SAT DOWN-MEP */
#define BCM_SAT_ENDPOINT_MATCH_INNER_VLAN   0x10       /* Selection of SAT MEP
                                                          based on C VLAN */
#define BCM_SAT_ENDPOINT_MATCH_OUTER_VLAN   0x20       /* Selection of SAT MEP
                                                          based on C VLAN */

/* SAT action flags */
#define BCM_SAT_ACTION_FWD_ACTION_DROP      0x01       /* Forward action for the
                                                          SAT packet is to drop */
#define BCM_SAT_ACTION_FWD_ACTION_REDIRECT  0x02       /* Forward action for the
                                                          SAT packet is redirect
                                                          to DGLP port */
#define BCM_SAT_ACTION_FWD_ACTION_LLF       0x04       /* Forward action for the
                                                          SAT packet is perform
                                                          latching loop back
                                                          function (LLF) and
                                                          redirect packet to
                                                          SGLP port */
#define BCM_SAT_ACTION_COPY_TO_CPU          0x08       /* Copy SAT packet to CPU */
#define BCM_SAT_ACTION_SAMPLE_TIMESTAMP     0x10       /* Sample time stamp into
                                                          the OLP header */

/* SAT Timestamp Formats */
typedef enum bcm_sat_timestamp_format_e {
    bcmSATTimestampFormatIEEE1588v1 = 0x00, /* Low-order 64 bits of the IEEE
                                           1588-2008 (1588v2) Precision Time
                                           Protocol timestamp format [IEEE1588] */
    bcmSATTimestampFormatNTP = 0x01     /* Network Time Protocol version 4
                                           64-bit timestamp format [RFC5905] */
} bcm_sat_timestamp_format_t;

/* SAT endpoint ID type */
typedef int bcm_sat_endpoint_t;

/* SAT endpoint object. */
typedef struct bcm_sat_endpoint_info_s {
    bcm_sat_endpoint_t ep_id;           /* The ID associated with this endpoint */
    uint32 flags;                       /* The flags associated with this
                                           endpoint */
    bcm_gport_t src_gport;              /* The source gport associated with this
                                           endpoint */
    bcm_vlan_t outer_vlan;              /* Outer-most VLAN tag (vlanID+ 3bits
                                           dot1p +CFI) associated with this
                                           endpoint */
    bcm_vlan_t inner_vlan;              /* Configure with CVLAN tag (vlanID+
                                           3bits dot1p +CFI) for two-tag
                                           operation or set to 0 for one-tag */
    bcm_mac_t dst_mac_address;          /* The destination MAC address
                                           associated with this endpoint */
    bcm_mac_t src_mac_address;          /* The source MAC address associated
                                           with this endpoint */
    uint16 ether_type;                  /* Ether type of the packet */
    uint32 action_flags;                /* SAT action flags */
    uint8 pkt_pri;                      /* Egress priority marking for packet
                                           redirected to DGPP */
    bcm_gport_t dest_gport;             /* Local endpoint SAT PDUs are forwarded
                                           to this OLP destination port for
                                           processing */
    bcm_sat_timestamp_format_t timestamp_format; /* SAT timestamp format */
    uint16 session_id;                  /* SAT session ID to identify the test
                                           among the MEPs */
} bcm_sat_endpoint_info_t;

/* Callback function type for SAT endpoint traversal */
typedef int (*bcm_sat_endpoint_traverse_cb)(
    int unit, 
    bcm_sat_endpoint_info_t *endpoint_info, 
    void *user_data);

#ifndef BCM_HIDE_DISPATCHABLE

/* Create or replace a SAT endpoint object. */
extern int bcm_sat_endpoint_create(
    int unit, 
    bcm_sat_endpoint_info_t *endpoint_info);

/* Get a SAT endpoint object. */
extern int bcm_sat_endpoint_get(
    int unit, 
    bcm_sat_endpoint_t endpoint, 
    uint32 flags, 
    bcm_sat_endpoint_info_t *endpoint_info);

/* Destroy a SAT endpoint object. */
extern int bcm_sat_endpoint_destroy(
    int unit, 
    bcm_sat_endpoint_t endpoint, 
    uint32 flags);

/* Destroy all SAT endpoint objects. */
extern int bcm_sat_endpoint_destroy_all(
    int unit, 
    uint32 flags);

/* Traverse the set of SAT endpoints. */
extern int bcm_sat_endpoint_traverse(
    int unit, 
    uint32 flags, 
    bcm_sat_endpoint_traverse_cb cb, 
    void *user_data);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Miscellaneous SAT defines */
#define BCM_SAT_GTF_NUM_OF_PRIORITIES       2          /* Number of element in
                                                          gtf */
#define BCM_SAT_PAYLOAD_MAX_PATTERN_SIZE    8          /* SAT payload pattern
                                                          max size */
#define BCM_SAT_GTF_PACKET_LENGTH_NUM_OF_PATTERNS 8          /* Number of pattern of
                                                          GTF packet length */
#define BCM_SAT_GTF_PACKET_MAX_PATTERN_LENGTH 32         /* SAT packet max pattern
                                                          length */
#define BCM_SAT_GTF_MAX_STAMPS              3          /* Max stamps of SAT GTF */
#define BCM_SAT_CTF_IDENTIFIER_ANY          0xFFFFFFFF /* SAT ctf idenifier */
#define BCM_SAT_CTF_STAT_MAX_NUM_OF_BINS    10         /* SAT ctf bins number */

/* SAT config flags */
#define BCM_SAT_CONFIG_CRC_REVERSED_DATA    0x01       /* During CRC calculation
                                                          the packet data bits
                                                          are reversed */
#define BCM_SAT_CONFIG_CRC_INVERT           0x02       /* During CRC calculation
                                                          the result is inverted
                                                          and reversed before
                                                          stamping */
#define BCM_SAT_CONFIG_CRC_HIGH_RESET       0x04       /* During CRC
                                                          calculations, reset
                                                          CRC value is taken to
                                                          be 32'hffffffff */
#define BCM_SAT_CONFIG_PRBS_USE_NXOR        0x08       /* During PRBS
                                                          calculations the next
                                                          bit is created using
                                                          NXOR (and not XOR) */
#define BCM_SAT_CONFIG_TWAMP_MODE           0x10       /* Mapped to two ctf
                                                          flows with consecutive
                                                          IDs when twamp_mode
                                                          set. */
#define BCM_SAT_CONFIG_CRC_REVERSE          0x20       /* During CRC calculation
                                                          the result is reversed
                                                          before stamping. */
#define BCM_SAT_CONFIG_CRC_INVERT_BITMAP    0x40       /* During CRC calculation
                                                          the result is inverted
                                                          according
                                                          crc_result_invert_bitmap
                                                          before stamping. */

/* SAT GTF create flags */
#define BCM_SAT_GTF_WITH_ID     0x01       /* Use the specified gtf ID */
#define BCM_SAT_GTF_ALLOC_PAIR  0x02       /* Allocate GTF in pair */

/* SAT GTF packet config flags */
#define BCM_SAT_GTF_PACKET_EDIT_ADD_END_TLV 0x01       /* If set, add an END TLV
                                                          at the end of the
                                                          packet */
#define BCM_SAT_GTF_PACKET_EDIT_ADD_CRC     0x02       /* If set, add CRC */

/* SAT GTF rate pattern flags */
#define BCM_SAT_GTF_RATE_PATTERN_STOP_INTERVAL_EQ_BURST 0x01       /* If set, INTERVAL state
                                                          limit is set to the
                                                          configuration,
                                                          otherwise to the
                                                          number of packets sent
                                                          in BURST state */

/* SAT GTF rate flags */
#define BCM_SAT_GTF_RATE_IN_BYTES           0x0        /* If set, gtf rate is
                                                          configured in bytes
                                                          per second */
#define BCM_SAT_GTF_RATE_IN_PACKETS         0x01       /* If set, gtf rate is
                                                          configured in packets
                                                          per second */
#define BCM_SAT_GTF_RATE_WITH_GRANULARITY   0x02       /* If set, the
                                                          granularity can be
                                                          changed; if not,
                                                          granularity will be 1 */

/* SAT CTF create flags */
#define BCM_SAT_CTF_WITH_ID     0x01       /* Use the specified ctf ID */

/* SAT CTF packet config flags */
#define BCM_SAT_CTF_PACKET_INFO_ADD_END_TLV 0x01       /* If set, add end tlv,
                                                          otherwise not add end
                                                          tlv */
#define BCM_SAT_CTF_PACKET_INFO_ADD_CRC     0x02       /* If set, add crc,
                                                          otherwise not add crc */

/* SAT CTF Stat Get flags */
#define BCM_SAT_CTF_STAT_DO_NOT_CLR_ON_READ 0x01       /* If set, do not clear
                                                          counter when reading,
                                                          otherwise clear
                                                          counter */
#define BCM_SAT_CTF_STAT_READ_TRANSITION_SLOTS 0x02       /* If set, read counters
                                                          when CTF is in
                                                          transition state, this
                                                          is for debug purpose */

/* SAT CTF Report Config flags */
#define BCM_SAT_CTF_REPORT_ADD_SEQ_NUM  0x01       /* If set, add sequence
                                                      number to reports */
#define BCM_SAT_CTF_REPORT_ADD_DELAY    0x02       /* If set, add delay to
                                                      reports */

/* SAT gtf ID type */
typedef int bcm_sat_gtf_t;

/* SAT ctf ID type */
typedef int bcm_sat_ctf_t;

/* SAT GTF Priority */
typedef enum bcm_sat_gtf_pri_e {
    bcmSatGtfPriAll = -1,   /* Relevant to both  CIR generator and EIR generator */
    bcmSatGtfPriCir = 0,    /* Only relevant to CIR generator */
    bcmSatGtfPriEir = 1     /* Only relevant to EIR generator */
} bcm_sat_gtf_pri_t;

/* SAT Header Type */
typedef enum bcm_sat_header_type_e {
    bcmSatHeaderUserDefined = 0,    /* User defined SAT header */
    bcmSatHeaderY1731 = 1,          /* SAT Header defined by Y1731 */
    bcmSatHeaderMEF = 2,            /* SAT Header defined by MEF */
    bcmSatHeadersCount = 3          /* Always Last. Not a usable value. */
} bcm_sat_header_type_t;

/* SAT Payload Type */
typedef enum bcm_sat_payload_type_e {
    bcmSatPayloadConstant8Bytes = 0,    /* 8 byte repeatable pattern */
    bcmSatPayloadConstant4Bytes = 1,    /* 4 byte repeatable pattern */
    bcmSatPayloadPRBS = 2,              /* PRBS-31 */
    bcmSatPayloadsCount = 3             /* Always Last. Not a usable value. */
} bcm_sat_payload_type_t;

/* SAT Stamp Type */
typedef enum bcm_sat_stamp_type_e {
    bcmSatStampInvalid = 0,         /* Invalid stamp type */
    bcmSatStampConstant2Bit = 1,    /* 2 bit stamp - constant value to stamp
                                       into the packet */
    bcmSatStampCounter8Bit = 2,     /* 8 bit counter */
    bcmSatStampCounter16Bit = 3,    /* 16 bit counter */
    bcmSatStampConstant16Bit = 4,   /* 16 bit stamp - constant value to stamp
                                       into the packet */
    bcmSatStampCount = 5            /* Always Last. Not a usable value. */
} bcm_sat_stamp_type_t;

/* SAT Stamp Field */
typedef enum bcm_sat_stamp_field_e {
    bcmSatStampFieldUserDefined = 0,    /* Stamp user defined field */
    bcmSatStampFieldTc = 1,             /* Stamp Tc */
    bcmSatStampFieldDp = 2,             /* Stamp Dp */
    bcmSatStampFieldSrcMac = 3,         /* Stamp Src Mac */
    bcmSatStampFieldDestMac = 4,        /* Stamp Dest Mac */
    bcmSatStampFieldInnerVlan = 5,      /* Stamp Inner Vlan */
    bcmSatStampFieldOuterVlan = 6,      /* Stamp Outer Vlan */
    bcmSatStampFieldsCount = 7          /* Always Last. Not a usable value. */
} bcm_sat_stamp_field_t;

/* SAT gtf rate pattern mode */
typedef enum bcm_sat_gtf_rate_pattern_mode_e {
    bcmSatGtfRatePatternContinues = 0,  /* Plain */
    bcmSatGtfRatePatternSimpleBurst = 1, /* Burst only */
    bcmSatGtfRatePatternCombined = 2,   /* Combined mode */
    bcmSatGtfRatePatternInterval = 3,   /* Interval mode */
    bcmSatGtfRatePatternsCount = 4      /* Always Last. Not a usable value. */
} bcm_sat_gtf_rate_pattern_mode_t;

/* SAT gtf counter types */
typedef enum bcm_sat_gtf_stat_counter_e {
    bcmSatGtfStatPacketCount = 0,   /* Count number of packets transmitted */
    bcmSatGtfStatCount = 1          /* Always Last. Not a usable value. */
} bcm_sat_gtf_stat_counter_t;

/* SAT event types */
typedef enum bcm_sat_event_type_e {
    bcmSATEventReport = 0, 
    bcmSATEventCount = 1    /* Always Last. Not a usable value. */
} bcm_sat_event_type_t;

/* Sat common configuration Object */
typedef struct bcm_sat_config_s {
    bcm_sat_timestamp_format_t timestamp_format; /* SAT timestamp format */
    uint32 config_flags; 
    uint32 seq_number_wrap_around;      /* SEQ number wrap-around */
    uint32 crc_result_invert_bitmap;    /* bitwise invert for CRC result */
} bcm_sat_config_t;

/* 
 * Offsets of payload, timestamp and sequence number in user defined
 * header
 */
typedef struct bcm_sat_header_user_define_offsets_s {
    int payload_offset;             /* Payload offset */
    int timestamp_offset;           /* Timestamp offset */
    int seq_number_offset;          /* Sequence number offset */
    int crc_byte_offset;            /* offset of CRC covered byte */
    int packet_length_compensation; /* Adjust the GTF bandwidth */
} bcm_sat_header_user_define_offsets_t;

/* Configure sat payload */
typedef struct bcm_sat_payload_s {
    bcm_sat_payload_type_t payload_type; /* Payload type */
    uint8 payload_pattern[BCM_SAT_PAYLOAD_MAX_PATTERN_SIZE]; /* Payload pattern */
} bcm_sat_payload_t;

/* Configure sat stamp */
typedef struct bcm_sat_stamp_s {
    bcm_sat_stamp_type_t stamp_type;    /* Stamp type */
    bcm_sat_stamp_field_t field_type;   /* Stamp field type */
    uint32 inc_step;                    /* Increment step - by what value the
                                           counter should be incremented */
    uint32 inc_period_packets;          /* Increment period - counter may be
                                           incremented every 1/2/4/8 packets */
    uint32 value;                       /* Stamp value */
    uint32 offset;                      /* Stamp offset in bits - where to stamp
                                           the counter, beginning from start of
                                           packet */
} bcm_sat_stamp_t;

/* Configure sat packet of gtf */
typedef struct bcm_sat_gtf_packet_edit_s {
    uint32 packet_length[BCM_SAT_GTF_PACKET_LENGTH_NUM_OF_PATTERNS]; /* Packet length */
    uint32 packet_length_pattern[BCM_SAT_GTF_PACKET_MAX_PATTERN_LENGTH]; /* Packet length pattern */
    uint32 pattern_length;              /* Pattern length */
    bcm_sat_stamp_t stamps[BCM_SAT_GTF_MAX_STAMPS]; /* Configurae stamp */
    uint32 number_of_stamps;            /* Number of stamps valid in stamps */
    uint32 number_of_ctfs;              /* Number of CTFs which collect
                                           information from the current gtf */
    uint32 flags; 
} bcm_sat_gtf_packet_edit_t;

/* 
 * If the most significant bit of packet_context_id is set, the least
 * significant bits of packet_context_id in bcm_sat_gtf_packet_config_t
 * are treated as core ID bitmap
 */
#define BCM_SAT_GTF_CONTEXT_ID_IN_BITMAP    0x80000000 /* packet_context_id
                                                          contains core bitmap */

/* Sat gtf packet config */
typedef struct bcm_sat_gtf_packet_config_s {
    bcm_sat_header_type_t sat_header_type; /* Sat header type */
    bcm_pkt_t header_info;              /* Sat header info */
    bcm_sat_payload_t payload;          /* Sat payload */
    bcm_sat_gtf_packet_edit_t packet_edit[BCM_SAT_GTF_NUM_OF_PRIORITIES]; /* Packet edit for each element of the
                                           gtf */
    uint32 packet_context_id;           /* Core ID, or core bitmap if
                                           BCM_SAT_GTF_CONTEXT_ID_IN_BITMAP is
                                           set */
    bcm_sat_header_user_define_offsets_t offsets; /* Offsets of payload, timestamp and
                                           sequence number in user defined
                                           header */
} bcm_sat_gtf_packet_config_t;

/* Configure sat gtf bandwidth */
typedef struct bcm_sat_gtf_bandwidth_s {
    uint32 flags; 
    uint32 rate;        /* traffic rate. Units: kbps */
    uint32 max_burst;   /* traffic burst. Units: kbit */
    uint32 granularity; /* packet per second */
} bcm_sat_gtf_bandwidth_t;

/* Configure sat gtf rate pattern */
typedef struct bcm_sat_gtf_rate_pattern_s {
    bcm_sat_gtf_rate_pattern_mode_t rate_pattern_mode; /* rate pattern mode */
    uint32 high_threshold;              /* High threshold */
    uint32 low_threshold;               /* Lower threshold */
    uint32 stop_iter_count;             /* Stop Iterations */
    uint32 stop_burst_count;            /* Stop Burst count - Burst state is
                                           left when number of packets
                                           transmitted in this state is
                                           greater-equal than this value */
    uint32 stop_interval_count;         /* Stop interval count */
    uint32 burst_packet_weight;         /* Burst Pkt Weight - on each packet
                                           transmitted in Burst state packet
                                           counter increased by this value */
    uint32 interval_packet_weight;      /* Inteval Packet weight - on each
                                           packet transmitted in Interval state
                                           packet counter increased by this
                                           value */
    uint32 flags; 
} bcm_sat_gtf_rate_pattern_t;

/* Sat ctf packet config */
typedef struct bcm_sat_ctf_packet_info_s {
    bcm_sat_header_type_t sat_header_type; /* Sat header type */
    bcm_sat_payload_t payload;          /* Sat payload */
    uint32 flags; 
    bcm_sat_header_user_define_offsets_t offsets; /* Offsets of payload, timestamp and
                                           sequence number in user defined
                                           header */
} bcm_sat_ctf_packet_info_t;

/* Sat ctf is recognized by this parameters */
typedef struct bcm_sat_ctf_identifier_s {
    uint32 tc;          /* Class of service */
    uint32 color;       /* Color */
    uint32 trap_id;     /* Trap ID */
    uint32 session_id;  /* SAT session ID */
} bcm_sat_ctf_identifier_t;

/* Sat ctf bin limit */
typedef struct bcm_sat_ctf_bin_limit_s {
    uint32 bin_select;  /* bin select */
    uint32 bin_limit;   /* bin limit */
} bcm_sat_ctf_bin_limit_t;

/* Sat ctf stat object for configuration */
typedef struct bcm_sat_ctf_stat_config_s {
    uint32 use_global_bin_config;       /* Use global bin config */
    uint32 bin_min_delay;               /* Bin min delay, for linear bins */
    uint32 bin_step;                    /* Bin step, for linear bins */
    uint32 update_counters_in_unvavail_state; /* Update counters in unavail state */
    uint32 count_packet_delay_delta;    /* When set, FDV bins count the packet
                                           delay delta between current packet
                                           and the previous packet of the same
                                           flow */
} bcm_sat_ctf_stat_config_t;

/* Sat ctf stat */
typedef struct bcm_sat_ctf_stat_s {
    uint64 received_packet_cnt;         /* Counter packet counter */
    uint64 out_of_order_packet_cnt;     /* Counter for out of order packet */
    uint64 err_packet_cnt;              /* Counter for error packet */
    uint64 received_octet_cnt;          /* Counter for received octet */
    uint64 out_of_order_octet_cnt;      /* Counter for out of order octet */
    uint64 err_octet_cnt;               /* Counter for error octet */
    uint64 last_packet_delay;           /* counter for last packet delay */
    uint64 bin_delay_counters[BCM_SAT_CTF_STAT_MAX_NUM_OF_BINS]; /* Counters for bin delay */
    uint64 accumulated_delay_count;     /* Counter for accumulated delay */
    uint64 max_packet_delay;            /* max packet delay */
    uint64 min_packet_delay;            /* min packet delay */
    uint64 time_of_day_stamp;           /* Time of day stamp */
    uint64 sec_in_avail_state_counter;  /* Counter for sec in avail state */
    uint64 last_packet_seq_number;      /* Last received packet sequence number */
    uint64 lost_packet_cnt;             /* Counter for lost packets */
} bcm_sat_ctf_stat_t;

/* Sat gtf stat */
typedef struct bcm_sat_gtf_stat_multi_s {
    uint64 transmitted_packet_cnt;  /* Counter transmitted packet */
    uint64 transmitted_byte_cnt;    /* Counter transmitted byte */
} bcm_sat_gtf_stat_multi_t;

/* Sat ctf state for configuration */
typedef struct bcm_sat_ctf_availability_config_s {
    uint32 switch_state_num_of_slots;   /* Number of slot */
    uint32 switch_state_threshold_per_slot; /* Threshold per slot */
} bcm_sat_ctf_availability_config_t;

/* Sat ctf report object */
typedef struct bcm_sat_ctf_report_config_s {
    uint32 report_sampling_percent; /* Report sampling percent */
    uint32 flags; 
} bcm_sat_ctf_report_config_t;

/* Sat ctf report event data */
typedef struct bcm_sat_report_event_data_s {
    int sequence_number;        /* Sequence number */
    int sequence_number_valid;  /* Sequence number valid */
    int delay;                  /* Delay */
    int delay_valid;            /* Delay valid */
    bcm_sat_ctf_t ctf_id;       /* SAT CTF id */
} bcm_sat_report_event_data_t;

/* Initialize a bcm_sat_header_user_define_offsets_t structure. */
extern void bcm_sat_header_user_define_offsets_t_init(
    bcm_sat_header_user_define_offsets_t *offsets);

/* Initialize a bcm_sat_payload_t structure. */
extern void bcm_sat_payload_t_init(
    bcm_sat_payload_t *payload);

/* Initialize a bcm_sat_config_t structure. */
extern void bcm_sat_config_t_init(
    bcm_sat_config_t *conf);

/* Initialize a bcm_sat_stamp_t structure. */
extern void bcm_sat_stamp_t_init(
    bcm_sat_stamp_t *stamp);

/* Initialize a bcm_sat_gtf_packet_edit_t structure. */
extern void bcm_sat_gtf_packet_edit_t_init(
    bcm_sat_gtf_packet_edit_t *packet_edit);

/* Initialize a bcm_sat_gtf_packet_config_t structure. */
extern void bcm_sat_gtf_packet_config_t_init(
    bcm_sat_gtf_packet_config_t *pkt_cfg);

/* Initialize a bcm_sat_gtf_bandwidth_t structure. */
extern void bcm_sat_gtf_bandwidth_t_init(
    bcm_sat_gtf_bandwidth_t *bw);

/* Initialize a bcm_sat_gtf_rate_pattern_t structure. */
extern void bcm_sat_gtf_rate_pattern_t_init(
    bcm_sat_gtf_rate_pattern_t *rate_pattern);

/* Initialize a bcm_sat_endpoint_info_t structure. */
extern void bcm_sat_endpoint_info_t_init(
    bcm_sat_endpoint_info_t *endpoint_info);

#ifndef BCM_HIDE_DISPATCHABLE

/* Set common configuration. */
extern int bcm_sat_config_set(
    int unit, 
    bcm_sat_config_t *conf);

/* Get common configuration. */
extern int bcm_sat_config_get(
    int unit, 
    bcm_sat_config_t *conf);

/* Create SAT GTF object. */
extern int bcm_sat_gtf_create(
    int unit, 
    uint32 flags, 
    bcm_sat_gtf_t *gtf_id);

/* Destroy a SAT GTF object. */
extern int bcm_sat_gtf_destroy(
    int unit, 
    bcm_sat_gtf_t gtf_id);

/* Destroy all SAT GTF objects. */
extern int bcm_sat_gtf_destroy_all(
    int unit);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Gtf callback function prototype. */
typedef int (*bcm_sat_gtf_traverse_cb)(
    int unit, 
    bcm_sat_gtf_t gtf_id, 
    void *user_data);

#ifndef BCM_HIDE_DISPATCHABLE

/* Traverse all the gtfs. */
extern int bcm_sat_gtf_traverse(
    int unit, 
    bcm_sat_gtf_traverse_cb cb, 
    void *user_data);

/* Set gtf packet format. */
extern int bcm_sat_gtf_packet_config(
    int unit, 
    bcm_sat_gtf_t gtf_id, 
    bcm_sat_gtf_packet_config_t *config);

/* Set gtf packet format. */
extern int bcm_sat_gtf_packet_config_set(
    int unit, 
    bcm_sat_gtf_t gtf_id, 
    bcm_sat_gtf_packet_config_t *config);

/* Set gtf packet format. */
extern int bcm_sat_gtf_packet_config_get(
    int unit, 
    bcm_sat_gtf_t gtf_id, 
    bcm_sat_gtf_packet_config_t *config);

/* Set gtf bandwidth. */
extern int bcm_sat_gtf_bandwidth_set(
    int unit, 
    bcm_sat_gtf_t gtf_id, 
    int priority, 
    bcm_sat_gtf_bandwidth_t *bw);

/* Get gtf bandwidth. */
extern int bcm_sat_gtf_bandwidth_get(
    int unit, 
    bcm_sat_gtf_t gtf_id, 
    int priority, 
    bcm_sat_gtf_bandwidth_t *bw);

/* Set gtf rate pattern. */
extern int bcm_sat_gtf_rate_pattern_set(
    int unit, 
    bcm_sat_gtf_t gtf_id, 
    int priority, 
    bcm_sat_gtf_rate_pattern_t *config);

/* Get gtf rate pattern. */
extern int bcm_sat_gtf_rate_pattern_get(
    int unit, 
    bcm_sat_gtf_t gtf_id, 
    int priority, 
    bcm_sat_gtf_rate_pattern_t *config);

/* Start gtf packet generation. */
extern int bcm_sat_gtf_packet_start(
    int unit, 
    bcm_sat_gtf_t gtf_id, 
    bcm_sat_gtf_pri_t priority);

/* Stop gtf packet generation. */
extern int bcm_sat_gtf_packet_stop(
    int unit, 
    bcm_sat_gtf_t gtf_id, 
    bcm_sat_gtf_pri_t priority);

/* Get gtf Statistics. */
extern int bcm_sat_gtf_stat_get(
    int unit, 
    bcm_sat_gtf_t gtf_id, 
    int priority, 
    uint32 flags, 
    bcm_sat_gtf_stat_counter_t type, 
    uint64 *value);

/* Get gtf multi Statistics. */
extern int bcm_sat_gtf_stat_multi_get(
    int unit, 
    bcm_sat_gtf_t gtf_id, 
    bcm_sat_gtf_stat_multi_t *stat);

/* Create SAT CTF object. */
extern int bcm_sat_ctf_create(
    int unit, 
    uint32 flags, 
    bcm_sat_ctf_t *ctf_id);

/* Destroy a SAT CTF object. */
extern int bcm_sat_ctf_destroy(
    int unit, 
    bcm_sat_ctf_t ctf_id);

/* Destroy all SAT CTF objects. */
extern int bcm_sat_ctf_destroy_all(
    int unit);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Ctf callback function prototype. */
typedef int (*bcm_sat_ctf_traverse_cb)(
    int unit, 
    bcm_sat_ctf_t ctf_id, 
    void *user_data);

#ifndef BCM_HIDE_DISPATCHABLE

/* Traverse all the ctfs. */
extern int bcm_sat_ctf_traverse(
    int unit, 
    bcm_sat_ctf_traverse_cb cb, 
    void *user_data);

/* Set ctf packet format. */
extern int bcm_sat_ctf_packet_config(
    int unit, 
    bcm_sat_ctf_t ctf_id, 
    bcm_sat_ctf_packet_info_t *packet_info);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Initialize a bcm_sat_ctf_packet_info_t structure. */
extern void bcm_sat_ctf_packet_info_t_init(
    bcm_sat_ctf_packet_info_t *packet_info);

/* Initialize a bcm_sat_ctf_identifier_t structure. */
extern void bcm_sat_ctf_identifier_t_init(
    bcm_sat_ctf_identifier_t *identifier);

/* Initialize a bcm_sat_ctf_bin_limit_t structure. */
extern void bcm_sat_ctf_bin_limit_t_init(
    bcm_sat_ctf_bin_limit_t *bins);

/* Initialize a bcm_sat_ctf_stat_config_t structure. */
extern void bcm_sat_ctf_stat_config_t_init(
    bcm_sat_ctf_stat_config_t *stat_cfg);

/* Initialize a bcm_sat_ctf_stat_t structure. */
extern void bcm_sat_ctf_stat_t_init(
    bcm_sat_ctf_stat_t *stat);

/* Initialize a bcm_sat_ctf_availability_config_t structure. */
extern void bcm_sat_ctf_availability_config_t_init(
    bcm_sat_ctf_availability_config_t *config);

/* Initialize a bcm_sat_ctf_report_config_t structure. */
extern void bcm_sat_ctf_report_config_t_init(
    bcm_sat_ctf_report_config_t *reports);

#ifndef BCM_HIDE_DISPATCHABLE

/* Map identifier to ctf. */
extern int bcm_sat_ctf_identifier_map(
    int unit, 
    bcm_sat_ctf_identifier_t *identifier, 
    bcm_sat_ctf_t ctf_id);

/* Unmap identifier to ctf. */
extern int bcm_sat_ctf_identifier_unmap(
    int unit, 
    bcm_sat_ctf_identifier_t *identifier);

/* Add specific trap ID. */
extern int bcm_sat_ctf_trap_add(
    int unit, 
    uint32 trap_id);

/* Remove specific trap ID. */
extern int bcm_sat_ctf_trap_remove(
    int unit, 
    uint32 trap_id);

/* Destroy all Trap objects. */
extern int bcm_sat_ctf_trap_remove_all(
    int unit);

/* Set ctf bin limit configuration. */
extern int bcm_sat_ctf_bin_limit_set(
    int unit, 
    int bins_count, 
    bcm_sat_ctf_bin_limit_t *bins);

/* Get ctf bin limit configuration. */
extern int bcm_sat_ctf_bin_limit_get(
    int unit, 
    int max_bins_count, 
    bcm_sat_ctf_bin_limit_t *bins, 
    int *bins_count);

/* Configure ctf stat. */
extern int bcm_sat_ctf_stat_config_set(
    int unit, 
    bcm_sat_ctf_t ctf_id, 
    bcm_sat_ctf_stat_config_t *stat);

/* Get ctf stat values. */
extern int bcm_sat_ctf_stat_get(
    int unit, 
    bcm_sat_ctf_t ctf_id, 
    uint32 flags, 
    bcm_sat_ctf_stat_t *stat);

/* Set ctf availability. */
extern int bcm_sat_ctf_availability_config_set(
    int unit, 
    bcm_sat_ctf_t ctf_id, 
    bcm_sat_ctf_availability_config_t *config);

/* Map trap data to session ID. */
extern int bcm_sat_ctf_trap_data_to_session_map(
    int unit, 
    uint32 trap_data, 
    uint32 trap_data_mask, 
    uint32 session_id);

/* Unmap trap data to session ID. */
extern int bcm_sat_ctf_trap_data_to_session_unmap(
    int unit, 
    uint32 trap_data, 
    uint32 trap_data_mask);

/* Set ctf report configuration. */
extern int bcm_sat_ctf_reports_config_set(
    int unit, 
    bcm_sat_ctf_t ctf_id, 
    bcm_sat_ctf_report_config_t *reports);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Callback function type for SAT event handling */
typedef int (*bcm_sat_event_cb)(
    int unit, 
    bcm_sat_event_type_t event_type, 
    void *user_provided_struct, 
    void *user_data);

#ifndef BCM_HIDE_DISPATCHABLE

/* Register a handler for SAT events. */
extern int bcm_sat_event_register(
    int unit, 
    bcm_sat_event_type_t event_type, 
    bcm_sat_event_cb cb, 
    void *user_data);

/* Unregister a handler for SAT events. */
extern int bcm_sat_event_unregister(
    int unit, 
    bcm_sat_event_type_t event_type, 
    bcm_sat_event_cb cb);

#endif /* BCM_HIDE_DISPATCHABLE */

#endif /* __BCM_SAT_H__ */

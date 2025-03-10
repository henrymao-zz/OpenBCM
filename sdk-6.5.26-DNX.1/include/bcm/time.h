/*
 * 
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 */

#ifndef __BCM_TIME_H__
#define __BCM_TIME_H__

#include <bcm/types.h>

/* Time Interface Identifier. */
typedef int bcm_time_if_t;

#define BCM_TIME_ENABLE                     0x00000001 /* Enable Time
                                                          Synchronization
                                                          Interface */
#define BCM_TIME_WITH_ID                    0x00000002 /* Create/Update
                                                          interface with valid
                                                          identifier in the
                                                          structure */
#define BCM_TIME_REPLACE                    0x00000004 /* Replace current
                                                          interface settings
                                                          according to flags
                                                          provided */
#define BCM_TIME_INPUT                      0x00000008 /* Current interface will
                                                          recieve a time sync
                                                          messages (Act as
                                                          slave) */
#define BCM_TIME_DRIFT                      0x00000020 /* To set/get the drift
                                                          parameter for
                                                          Interface */
#define BCM_TIME_OFFSET                     0x00000040 /* To set/get the offset
                                                          parameter for
                                                          Interface */
#define BCM_TIME_ACCURACY                   0x00000080 /* To set/get the
                                                          accuracy parameter for
                                                          Interface */
#define BCM_TIME_HEARTBEAT                  0x00000100 /* To set the heartbeat
                                                          frequency for
                                                          Interface */
#define BCM_TIME_LOCKED                     0x00000200 /* To indicate that
                                                          interface is locked on
                                                          a grand master's clock */
#define BCM_TIME_REF_CLOCK                  0x00000400 /* Enable Reference clock */
#define BCM_TIME_SYNC_STAMPER               0x00000800 /* Enable BroadSync
                                                          timestamper sync
                                                          support */
#define BCM_TIME_NTP_OFFSET                 0x000001000 /* To set/get the ntp
                                                          offset parameter for
                                                          Interface */
#define BCM_TIME_BS_TIME                    0x000002000 /* set UTC time or system
                                                          time for BroadSync
                                                          Master */
#define BCM_TIME_BS_NTP_TOD_UPDATE_DISABLE  0x00004000 /* Flag to disable NTP
                                                          ToD updates */
#define BCM_TIME_BS_PTP_TOD_UPDATE_DISABLE  0x00008000 /* Flag to disable PTP
                                                          ToD updates */
#define BCM_TIME_PTP_OFFSET                 0x00010000 /* To set/get the ptp
                                                          offset parameter for
                                                          Interface */

/* BroadSync Time Source Status. */
typedef enum bcm_bs_time_source_e {
    bcmBsTimeSourceNotLocked = 0,       /* No time-code received, Holdover mode
                                           or Not Locked */
    bcmBsTimeSourceAcquiring = 1,       /* Acquiring state */
    bcmBsTimeSourceExcessiveJitter = 2, /* Acquiring state but locked with
                                           excessive jitter */
    bcmBsTimeSourceLocked = 3           /* Locked State */
} bcm_bs_time_source_t;

/* Base time structure. */
typedef struct bcm_time_interface_s {
    uint32 flags;                   /* Flags BCM_TIME_* */
    bcm_time_if_t id;               /* Time Interface Identifier */
    bcm_time_spec_t drift;          /* Drift amount per 1 Sec */
    bcm_time_spec_t offset;         /* Offset */
    bcm_time_spec_t accuracy;       /* Accuracy */
    int heartbeat_hz;               /* HeartBeat Rate */
    int clk_resolution;             /* Reference clock resolution in nsecs */
    int bitclock_hz;                /* BitClock frequency */
    bcm_bs_time_source_t status;    /* BroadSync Time Source Status */
    bcm_time_spec_t ntp_offset;     /* NTP Offset */
    bcm_time_spec_t bs_time;        /* UTC time or system time for BroadSync
                                       Master */
    bcm_time_spec_t ptp_offset;     /* PTP Offset */
} bcm_time_interface_t;

#define BCM_TIME_CAPTURE_LOCKED             0x00000001 /* Captured Time is
                                                          synchronized with
                                                          Grand Master */
#define BCM_TIME_CAPTURE_GPIO_0             0x00000002 /* Capture Time at rising
                                                          edge of GPIO 0 */
#define BCM_TIME_CAPTURE_GPIO_1             0x00000004 /* Capture Time at rising
                                                          edge of GPIO 1 */
#define BCM_TIME_CAPTURE_GPIO_2             0x00000008 /* Capture Time at rising
                                                          edge of GPIO 2 */
#define BCM_TIME_CAPTURE_GPIO_3             0x00000010 /* Capture Time at rising
                                                          edge of GPIO 3 */
#define BCM_TIME_CAPTURE_GPIO_4             0x00000020 /* Capture Time at rising
                                                          edge of GPIO 4 */
#define BCM_TIME_CAPTURE_GPIO_5             0x00000040 /* Capture Time at rising
                                                          edge of GPIO 5 */
#define BCM_TIME_CAPTURE_L1_CLOCK_PRIMARY   0x00000080 /* Capture Time at rising
                                                          edge of primary L1 */
#define BCM_TIME_CAPTURE_L1_CLOCK_SECONDARY 0x00000100 /* Capture Time at rising
                                                          edge of primary L2 */
#define BCM_TIME_CAPTURE_LCPLL              0x00000200 /* Capture Time at rising
                                                          edge of LCPLL */
#define BCM_TIME_CAPTURE_IP_DM_0            0x00000400 /* Capture Time at rising
                                                          edge of DM0 */
#define BCM_TIME_CAPTURE_IP_DM_1            0x00000800 /* Capture Time at rising
                                                          edge of DM1 */
#define BCM_TIME_CAPTURE_IMMEDIATE          0x00001000 /* Capture Immediate */
#define BCM_TIME_CAPTURE_ALL                0x00002000 /* Capture Immediate */
#define BCM_TIME_CAPTURE_BS0HB              0x00004000 /* Capture Time at rising
                                                          edge of BroadSync 0 */
#define BCM_TIME_CAPTURE_BS1HB              0x00008000 /* Capture Time at rising
                                                          edge of BroadSync 1 */
#define BCM_TIME_CAPTURE_TS1TS              0x00010000 /* Capture Time of TS1
                                                          event */
#define BCM_TIME_CAPTURE_BS0PLL             0x00020000 /* Capture Time of rising
                                                          edge of BroadSync0 PL */
#define BCM_TIME_CAPTURE_BS1PLL             0x00040000 /* Capture Time of rising
                                                          edge of  BroadSync1 PL */
#define BCM_TIME_CAPTURE_RSVD1IF            0x00080000 /* Capture Time of rising
                                                          edge of  RSVD1
                                                          interfac */
#define BCM_TIME_CAPTURE_RSVD1RF            0x00100000 /* Capture Time of rising
                                                          edge of  RSVD2 counte */
#define BCM_TIME_CAPTURE_BS0CONVTC          0x00200000 /* Capture Time of
                                                          BroadSync0 converted
                                                          timecode */
#define BCM_TIME_CAPTURE_BS1CONVTC          0x00400000 /* Capture Time of
                                                          BroadSync1 converted
                                                          timecod */
#define BCM_TIME_CAPTURE_LCPLL1             0x00800000 /* Capture Time at rising
                                                          edge of LCPLL1 */
#define BCM_TIME_CAPTURE_LCPLL2             0x01000000 /* Capture Time at rising
                                                          edge of LCPLL2 */
#define BCM_TIME_CAPTURE_LCPLL3             0x02000000 /* Capture Time at rising
                                                          edge of LCPLL3 */
#define BCM_TIME_CAPTURE_PORT               0x04000000 /* Capture Time at port */

/* Time port events */
typedef enum bcm_time_port_event_e {
    bcmTimePortEventRXSOF = 0,  /* CPRI port recieve SOF input event */
    bcmTimePortEventTXSOF = 1,  /* CPRI port transmit SOF input event */
    bcmTimePortEventROE = 2,    /* CPRI ROE timestamp event */
    bcmTimePortEventRXCDR = 3,  /* Port recieve CDR event */
    bcmTimePortEventTXPI = 4    /* Port TXPI event */
} bcm_time_port_event_t;

/* Base time capture structure. */
typedef struct bcm_time_capture_s {
    uint32 flags;                       /*  Flags BCM_TIME_CAPTURE_* */
    bcm_time_spec_t free;               /* Free running clock */
    bcm_time_spec_t syntonous;          /* Syntonous clock */
    bcm_time_spec_t synchronous;        /* Synchronous clock */
    bcm_time_spec_t received;           /* Received clock */
    bcm_time_spec_t received_accuracy;  /* Received clock accuracy */
    bcm_port_t port;                    /* Port number */
    bcm_time_port_event_t port_event_type; /* Port related event type */
    uint32 event_divisor;               /* Divisor value for a ts event */
    int ts_counter;                     /* Sample on TS0(0), TS1(1) */
} bcm_time_capture_t;

/* SyncE Clock Source Type. */
typedef enum bcm_time_synce_clock_src_type_e {
    bcmTimeSynceClockSourcePrimary = 0, /* Primary Clock Source */
    bcmTimeSynceClockSourceSecondary = 1 /* Secondary Clock Source */
} bcm_time_synce_clock_src_type_t;

/* SyncE Input Source Type. */
typedef enum bcm_time_synce_input_src_type_e {
    bcmTimeSynceInputSourceTypePort = 0, /* Input Source Port */
    bcmTimeSynceInputSourceTypePLL = 1, /* Input Source PLL */
    bcmTimeSynceInputSourceTypeExtPhy = 2 /* Input Source ExtPHY */
} bcm_time_synce_input_src_type_t;

/* SyncE Stage0 Mode. */
typedef enum bcm_time_synce_stage0_mode_e {
    bcmTimeSynceModeBypass = 0,     /* Stage0 Mode Bypass */
    bcmTimeSynceModeGap45 = 1,      /* Stage0 Mode GAP 4/5 */
    bcmTimeSynceModeSDMFracDiv = 2  /* Stage0 Mode SDM Frac Div */
} bcm_time_synce_stage0_mode_t;

/* bcm_time_synce_stage1_div_e */
typedef enum bcm_time_synce_stage1_div_e {
    bcmTimeSynceStage1Div1 = 0,     /* Stage1 Div1 */
    bcmTimeSynceStage1Div7 = 1,     /* Stage1 Div7 */
    bcmTimeSynceStage1Div11 = 2,    /* Stage1 Div11 */
    bcmTimeSynceStage1Div8 = 3      /* Stage1 Div8 */
} bcm_time_synce_stage1_div_t;

/* Time Synce Divisor setting structure. */
typedef struct bcm_time_synce_divisor_setting_s {
    bcm_time_synce_input_src_type_t input_src; /* Input source type */
    uint32 index;                       /* Logical port number or PLL index */
    bcm_time_synce_stage0_mode_t stage0_mode; /* Stage0 Mode bcmTimeSynceMode* */
    uint32 stage0_sdm_whole;            /* Stage0 SDM whole value */
    uint32 stage0_sdm_frac;             /* Stage0 SDM frac value */
    bcm_time_synce_stage1_div_t stage1_div; /* Stage1 Div bcmTimeSynceStage1Div* */
} bcm_time_synce_divisor_setting_t;

/* BS log configuration structure. */
typedef struct bcm_time_bs_log_cfg_s {
    uint32 debug_mask;      /* mask indicating log level */
    uint64 udp_log_mask;    /* mask indicating UDP log level */
    bcm_mac_t src_mac;      /* Source MAC address */
    bcm_mac_t dest_mac;     /* Destination MAC address */
    uint16 tpid;            /* TPID */
    uint16 vid;             /* VLAN ID */
    uint8 ttl;              /* Time to live */
    bcm_ip_t src_addr;      /* Source IP address */
    bcm_ip_t dest_addr;     /* Destination IP address */
    uint16 udp_port;        /* UDP port number */
} bcm_time_bs_log_cfg_t;

#define BCM_BS_LOG_NONE         0x00000000 /* BS log level None */
#define BCM_BS_LOG_SYS_INFO     0x00000001 /* BS log level info */
#define BCM_BS_LOG_SYS_WARN     0x00000002 /* BS log level warning */
#define BCM_BS_LOG_SYS_ERR      0x00000004 /* BS log level error */
#define BCM_BS_LOG_SYS_CRIT     0x00000008 /* BS log level critical */
#define BCM_BS_LOG_SYS_ALL      0x000000FF /* BS log level all */

#ifndef BCM_HIDE_DISPATCHABLE

/* Configures the BroadSync logging */
extern int bcm_time_bs_log_configure_set(
    int unit, 
    bcm_time_bs_log_cfg_t bs_log_cfg);

/* Get the BroadSync logging configuration */
extern int bcm_time_bs_log_configure_get(
    int unit, 
    bcm_time_bs_log_cfg_t *bs_log_cfg);

/* Initialize time module. */
extern int bcm_time_init(
    int unit);

/* Uninitialize time module. */
extern int bcm_time_deinit(
    int unit);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Initialize bcm_time_spec_t structure. */
extern void bcm_time_spec_t_init(
    bcm_time_spec_t *spec);

/* Initialize bcm_time_interface_t structure */
extern void bcm_time_interface_t_init(
    bcm_time_interface_t *intf);

/* Initialize bcm_time_capture_t structure. */
extern void bcm_time_capture_t_init(
    bcm_time_capture_t *capture);

/* Initialize bcm_time_synce_divisor_setting_t structure. */
extern void bcm_time_synce_divisor_setting_t_init(
    bcm_time_synce_divisor_setting_t *divisor);

#ifndef BCM_HIDE_DISPATCHABLE

/* Creates a Time Synchronization Interface */
extern int bcm_time_interface_add(
    int unit, 
    bcm_time_interface_t *intf);

/* Retrieve the Time Synchronization Interface. */
extern int bcm_time_interface_get(
    int unit, 
    bcm_time_interface_t *intf);

/* Deletes a Time Synchronization Interface. */
extern int bcm_time_interface_delete(
    int unit, 
    bcm_time_if_t intf_id);

/* Removes all interfaces on a given device. */
extern int bcm_time_interface_delete_all(
    int unit);

#endif /* BCM_HIDE_DISPATCHABLE */

/* bcm_time_interface_traverse_cb */
typedef int (*bcm_time_interface_traverse_cb)(
    int unit, 
    bcm_time_interface_t *intf, 
    void *user_data);

#ifndef BCM_HIDE_DISPATCHABLE

/* Iterates over all Time Synchronization Interfaces. */
extern int bcm_time_interface_traverse(
    int unit, 
    bcm_time_interface_traverse_cb cb, 
    void *user_data);

/* Retrieves time capture from the device. */
extern int bcm_time_capture_get(
    int unit, 
    bcm_time_if_t intf_id, 
    bcm_time_capture_t *time);

#endif /* BCM_HIDE_DISPATCHABLE */

/* bcm_time_heartbeat_cb */
typedef int (*bcm_time_heartbeat_cb)(
    int unit, 
    bcm_time_if_t id, 
    bcm_time_capture_t *time, 
    void *user_data);

#ifndef BCM_HIDE_DISPATCHABLE

/* Register a callback function to be called on each heartbeat. */
extern int bcm_time_heartbeat_register(
    int unit, 
    bcm_time_if_t id, 
    bcm_time_heartbeat_cb f, 
    void *user_data);

/* Unregister a callback function . */
extern int bcm_time_heartbeat_unregister(
    int unit, 
    bcm_time_if_t id);

/* 
 * Enables/Disables interrupt handling for each heartbeat provided by a
 * clock.
 */
extern int bcm_time_heartbeat_enable_set(
    int unit, 
    bcm_time_if_t id, 
    int enable);

/* 
 * Retrieves the status of interrupt handling for each heartbeat provided
 * by a clock.
 */
extern int bcm_time_heartbeat_enable_get(
    int unit, 
    bcm_time_if_t id, 
    int *enable);

/* Set External time capture modes */
extern int bcm_time_trigger_enable_set(
    int unit, 
    bcm_time_if_t id, 
    uint32 mode_flags);

/* Get External time capture modes */
extern int bcm_time_trigger_enable_get(
    int unit, 
    bcm_time_if_t id, 
    uint32 *mode_flags);

/* Get current syncE input divisor settings */
extern int bcm_time_synce_clock_get(
    int unit, 
    bcm_time_synce_clock_src_type_t clk_src, 
    bcm_time_synce_divisor_setting_t *divisor_setting);

/* Set syncE clock output frequency beased on the input divisor settings. */
extern int bcm_time_synce_clock_set(
    int unit, 
    bcm_time_synce_clock_src_type_t clk_src, 
    bcm_time_synce_divisor_setting_t *divisor_setting);

#endif /* BCM_HIDE_DISPATCHABLE */

/* synce clock source config */
typedef struct bcm_time_synce_clock_source_config_s {
    bcm_time_synce_clock_src_type_t clk_src; /* SyncE Clock Source Primary or
                                           Secondary */
    bcm_time_synce_input_src_type_t input_src; /* Input source type Port or PLL */
    uint32 pll_index;                   /* PLL index */
    bcm_port_t port;                    /* Logical port number */
} bcm_time_synce_clock_source_config_t;

/* bcm_time_synce_clock_source_control */
typedef enum bcm_time_synce_clock_source_control_e {
    bcmTimeSynceClockSourceControlSquelch = 0, /* Squelch of SyncE source */
    bcmTimeSynceClockSourceControlFrequency = 1 /* Frequency of SyncE source */
} bcm_time_synce_clock_source_control_t;

/* SyncE Frequency */
typedef enum bcm_time_synce_frequency_e {
    bcmTimeSyncE23MHz = 1,  /* TSCF - 23.4375 MHz */
    bcmTimeSyncE25MHz = 2,  /* SDM - 25MHz */
    bcmTimeSyncE28MHz = 3,  /* General - 28.4 MHz */
    bcmTimeSyncE46MHz = 4,  /* General - 46.875 MHz */
    bcmTimeSyncE125MHz = 5, /* General - 125MHz */
    bcmTimeSyncE515MHz = 6, /* General - 515.625MHz */
    bcmTimeSyncE7MHz = 7,   /* SDM - 7.8125 MHz */
    bcmTimeSyncE12MHz = 8,  /* SDM - 12.5 MHz */
    bcmTimeSyncE31MHz = 9,  /* SDM - 31.25 MHz */
    bcmTimeSyncE37MHz = 10, /* SDM - 37.5 MHz */
    bcmTimeSyncE156MHz = 11 /* General - 156.25 MHz */
} bcm_time_synce_frequency_t;

#ifndef BCM_HIDE_DISPATCHABLE

/* Configure Primary or Secondary SyncE Recovered clock. */
extern int bcm_time_synce_clock_source_control_set(
    int unit, 
    bcm_time_synce_clock_source_config_t *clk_src_config, 
    bcm_time_synce_clock_source_control_t control, 
    int value);

/* Configure Primary or Secondary SyncE Recovered clock. */
extern int bcm_time_synce_clock_source_control_get(
    int unit, 
    bcm_time_synce_clock_source_config_t *clk_src_config, 
    bcm_time_synce_clock_source_control_t control, 
    int *value);

/* Retrieves broadsync time from device */
extern int bcm_time_bs_time_get(
    int unit, 
    bcm_time_spec_t *bs_time);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Time formats */
typedef enum bcm_time_format_e {
    bcmTimeFormatPTP = 0,   /* The time format is PTP. */
    bcmTimeFormatNTP = 1    /* The time format is NTP. */
} bcm_time_format_t;

/* values to set initial counter in ts clock. */
typedef struct bcm_time_ts_counter_s {
    bcm_time_format_t time_format;  /* Time format for counter */
    int enable;                     /* Enable/disable control for counter. */
    int ts_counter;                 /* TS0/TS1 counter. */
    uint64 ts_counter_ns;           /* nanosecond value of counter. */
} bcm_time_ts_counter_t;

/* Initialize counter structure for timestamping. */
extern void bcm_time_ts_counter_t_init(
    bcm_time_ts_counter_t *counter);

#ifndef BCM_HIDE_DISPATCHABLE

/* Set counter values for timestamping. */
extern int bcm_time_ts_counter_set(
    int unit, 
    bcm_time_ts_counter_t *counter);

/* Set counter values for timestamping. */
extern int bcm_time_ts_counter_get(
    int unit, 
    bcm_time_ts_counter_t *counter);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Time stamping stages. */
#define BCM_TIME_STAGE_INGRESS_FLOWTRACKER  (1U << 0)  /* Ingress Flowtracker
                                                          stage for time
                                                          stamping. */
#define BCM_TIME_STAGE_EGRESS               (1U << 1)  /* Egress stage for time
                                                          stamping. */
#define BCM_TIME_STAGE_LIVE_WIRE_PTP        (1U << 2)  /* Live wire timestamping
                                                          in PTP format. */
#define BCM_TIME_STAGE_LIVE_WIRE_NTP        (1U << 3)  /* Live wire timestamping
                                                          in NTP format. */
#define BCM_TIME_STAGE_MMU                  (1U << 4)  /* MMU stage for time
                                                          stamping. */
#define BCM_TIME_STAGE_BTE                  (1U << 5)  /* BTE stage for time
                                                          stamping. */
#define BCM_TIME_STAGE_ALL                  (1U << 31) /* Timestamping will be
                                                          applied to all the
                                                          stages. */

/* Structure for Time of the day values. */
typedef struct bcm_time_tod_s {
    int auto_update;                    /* Enable ToD automatic update. */
    bcm_time_format_t time_format;      /* Time format for counter. */
    bcm_time_spec_t ts;                 /* time of the day values. */
    uint64 ts_adjustment_counter_ns;    /* tod value adjustment in nanoseconds. */
} bcm_time_tod_t;

/* Initialize tod structure for timestamping. */
extern void bcm_time_tod_t_init(
    bcm_time_tod_t *tod);

#ifndef BCM_HIDE_DISPATCHABLE

/* Set time of the day values at various stages in ASIC. */
extern int bcm_time_tod_set(
    int unit, 
    uint32 stages, 
    bcm_time_tod_t *tod);

/* Get time of the day values at various stages in ASIC. */
extern int bcm_time_tod_get(
    int unit, 
    uint32 stages, 
    bcm_time_tod_t *tod);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Time capture callback types */
typedef enum bcm_time_capture_cb_type_e {
    bcmTimeCaptureOverflow = 0,         /* Cb will be called only on overflow */
    bcmTimeCapturetFill = 1,            /* Cb will be called only for ts events */
    bcmTimeCaptureAll = 2,              /* Cb will be called for both overflow
                                           and ts events */
    bcmTimeCaptureTS0CntOffsetUpdated = 3, /* Cb will be called when TS0 phase
                                           offset gets applied */
    bcmTimeCaptureTS1CntOffsetUpdated = 4 /* Cb will be called when TS1 phase
                                           offset gets applied */
} bcm_time_capture_cb_type_t;

#ifndef BCM_HIDE_DISPATCHABLE

/* Enable/Disable FIFO timestamp capture for a particular event */
extern int bcm_time_capture_enable_set(
    int unit, 
    bcm_time_if_t id, 
    bcm_time_capture_t *time_capture, 
    int enable, 
    int *capture_handle);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Generic callback for time capture events */
typedef int (*bcm_time_capture_cb)(
    int unit, 
    void *user_data, 
    uint32 *cb_data, 
    bcm_time_capture_cb_type_t cb_status);

#ifndef BCM_HIDE_DISPATCHABLE

/* Register callback function for a given type */
extern int bcm_time_capture_cb_register(
    int unit, 
    bcm_time_if_t id, 
    bcm_time_capture_cb_type_t cb_type, 
    bcm_time_capture_cb cb, 
    void *user_data);

/* Un-register callback function for a given time event type */
extern int bcm_time_capture_cb_unregister(
    int unit, 
    bcm_time_if_t id, 
    bcm_time_capture_cb_type_t cb_type);

#endif /* BCM_HIDE_DISPATCHABLE */

/* Time of the day offset type. */
typedef enum bcm_time_tod_offset_type_e {
    bcmTimeTodNTPEpochOffset = 0,   /* Epoch offset for PTP to NTP conversion. */
    bcmTimeTodPTPPhaseOffset = 1    /* Offset to shift the time forwards or
                                       backwards. */
} bcm_time_tod_offset_type_t;

#ifndef BCM_HIDE_DISPATCHABLE

/* Set offset for Time of the day values. */
extern int bcm_time_tod_offset_set(
    int unit, 
    bcm_time_tod_offset_type_t type, 
    bcm_time_spec_t *offset);

/* Get offset for Time of the day values. */
extern int bcm_time_tod_offset_get(
    int unit, 
    bcm_time_tod_offset_type_t type, 
    bcm_time_spec_t *offset);

/* Set counter values for timestamping. */
extern int bcm_time_ts_offset_set(
    int unit, 
    int64 ts_offset, 
    uint64 ts_update_intv, 
    int ts_counter);

/* Function to reset and enable time counter and timestamp pair */
extern int bcm_time_ts_counter_time_init(
    int unit);

/* Function to periodically to update the 80bit/48bit timestamp pair */
extern int bcm_time_ts_time_update(
    int unit);

/* Function to convert 32bit timestamp to 80bit tod */
extern int bcm_time_ts_time_convert(
    int unit, 
    uint32 ts_val, 
    bcm_time_spec_t *time);

#endif /* BCM_HIDE_DISPATCHABLE */

#define BCM_TIME_TIMESYNC_ONE_STEP_TIMESTAMP_DISABLE (1U << 0)  /* Disable one step
                                                          timestamp for IEEE
                                                          1588 packets. */
#define BCM_TIME_TIMESYNC_PTP_DO_NOT_MODIFY (1U << 1)  /* Enable to not modify
                                                          IEEE 1588 packets. */
#define BCM_TIME_TIMESYNC_PTP_ING_UPDATE_DONE (1U << 2)  /* Enable to specify that
                                                          IEEE 1588 ingress
                                                          update has been done. */

/* Timesync config profile structure. */
typedef struct bcm_time_timesync_config_profile_s {
    uint32 flags;   /* See BCM_TIME_TIMESYNC_xxx flag definitions. */
} bcm_time_timesync_config_profile_t;

/* Initialize bcm_time_timesync_config_profile_t struct */
extern void bcm_time_timesync_config_profile_t_init(
    bcm_time_timesync_config_profile_t *profile);

#ifndef BCM_HIDE_DISPATCHABLE

/* Create the timesync profile. */
extern int bcm_time_timesync_config_profile_create(
    int unit, 
    bcm_time_timesync_config_profile_t *profile, 
    int *profile_id);

/* Destroy the timesync profile. */
extern int bcm_time_timesync_config_profile_destroy(
    int unit, 
    int profile_id);

/* Get the timesync profile entry with a given profile id. */
extern int bcm_time_timesync_config_profile_get(
    int unit, 
    int profile_id, 
    bcm_time_timesync_config_profile_t *profile);

#endif /* BCM_HIDE_DISPATCHABLE */

#endif /* __BCM_TIME_H__ */

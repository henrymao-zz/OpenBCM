/***********************************************************************************
 *                                                                                 *
 * Copyright: (c) 2021 Broadcom.                                                   *
 * Broadcom Proprietary and Confidential. All rights reserved.                     *
 *                                                                                 *
 ***********************************************************************************/

/*****************************************************************************************
 *****************************************************************************************
 *                                                                                       *
 *  Revision      :   *
 *                                                                                       *
 *  Description   :  Common types used by Serdes API functions                           *
 *                                                                                       *
 *****************************************************************************************
 *****************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BLACKHAWK7_V1L8P1_API_TYPES_H
#define BLACKHAWK7_V1L8P1_API_TYPES_H

#include "blackhawk7_v1l8p1_ipconfig.h"
#include "blackhawk7_v1l8p1_common.h"
#include "blackhawk7_v1l8p1_select_defns.h"

/*! @file
 *  @brief Common types used by Serdes API functions
 */

/*! @addtogroup APITag
 * @{
 */

/*! @defgroup SerdesAPITypesTag Common Core Types
 * Contains structs and typedefs which are used throughout
 * Serdes APIs.
 */

/*! @addtogroup SerdesAPITypesTag
 * @{
 */

/*! Used for error reporting APIs
 *
 */
typedef struct blackhawk7_v1l8p1_triage_info_st {
   uint32_t     api_ver;
   uint32_t     ucode_ver;
   uint8_t      core;
   uint8_t      lane;

   err_code_t   error;
   uint16_t     line;

   uint16_t     stop_status;
   uint16_t     sw_exception;
   uint16_t     hw_exception;
   uint16_t     stack_overflow;
   uint16_t     overflow_lane_id;
   uint16_t     cmd_info;

   uint8_t      pmd_lock;
   uint8_t      pmd_lock_chg;
   uint8_t      sig_det;
   uint8_t      sig_det_chg;
   uint16_t     dsc_one_hot[2];
} blackhawk7_v1l8p1_triage_info;



#define SIZE_OF_DBGFB_STATS_STRUCT 296  /* Change the size if blackhawk7_v1l8p1_dbgfb_stats_st size changes */
/*! Used for maintaining correctness of SIZE_OF_DBGFB_STATS_STRUCT
 *
 */
typedef struct { 
    uint8_t dbgfb_tmp[sizeof(blackhawk7_v1l8p1_dbgfb_stats_st)==SIZE_OF_DBGFB_STATS_STRUCT ? 1: -1]; 
} blackhawk7_v1l8p1_dbgfb_stats_st_size_check;

/*! Used for debug feedback APIs
 *
 */
typedef struct blackhawk7_v1l8p1_dbgfb_cfg_s {
    uint8_t y;
    uint8_t x;
    uint32_t time_in_us;
    int32_t data1;
    int32_t data2;
    int32_t data3;
} blackhawk7_v1l8p1_dbgfb_cfg_st;

#define DBGFB_CFG_ST_INIT {0,0,0,0,0,0}

/*----------------------------------------*/
/*  Lane/Core structs (without bitfields) */
/*----------------------------------------*/

/*! Lane Config Variable Structure in Microcode
 *
 */
struct blackhawk7_v1l8p1_uc_lane_config_field_st {
  uint8_t  lane_cfg_from_pcs ;
  uint8_t  an_enabled        ;
  uint8_t  dfe_on            ;
  uint8_t  dfe_lp_mode       ;
  uint8_t  force_brdfe_on    ;
  uint8_t  media_type        ;
  uint8_t  unreliable_los    ;
  uint8_t  scrambling_dis    ;
  uint8_t  cl72_auto_polarity_en ;
  uint8_t  cl72_restart_timeout_en;
  uint8_t  force_er          ;
  uint8_t  force_nr          ;
  uint8_t  lp_has_prec_en    ;
  uint8_t  force_pam4_mode   ; /*!< Used to override the pam4mode pin */
  uint8_t  force_nrz_mode    ; /*!< Used to override the pam4mode pin */
};
#define UC_LANE_CONFIG_FIELD_INIT {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

/*! Core Config Variable Structure in Microcode
 *
 */
struct blackhawk7_v1l8p1_uc_core_config_field_st {
  uint8_t  vco_rate          ;
  uint8_t  core_cfg_from_pcs ;
  uint8_t  osr_2p5_en        ;
  uint8_t  reserved          ;
};
#define UC_CORE_CONFIG_FIELD_INIT {0,0,0,0}

/*! Lane Config Struct
 *
 */
struct  blackhawk7_v1l8p1_uc_lane_config_st {
  struct blackhawk7_v1l8p1_uc_lane_config_field_st field;
  uint16_t word;
};
#define UC_LANE_CONFIG_INIT {UC_LANE_CONFIG_FIELD_INIT, 0}

/*! Core Config Struct
 *
 */
struct  blackhawk7_v1l8p1_uc_core_config_st {
  struct blackhawk7_v1l8p1_uc_core_config_field_st field;
  uint16_t word;
  int32_t vco_rate_in_Mhz; /*!< if > 0 then will get converted and replace field.vco_rate when update is called */
};
#define UC_CORE_CONFIG_INIT {UC_CORE_CONFIG_FIELD_INIT, 0, 0}

/*! Lane User Control Function Structure in Microcode
 *
 */
struct blackhawk7_v1l8p1_usr_ctrl_func_st {
  uint16_t pf_adaptation           ; /*!< Main Peaking Filter Adaptation */
  uint16_t pf2_adaptation          ; /*!< Low Frequency Peaking Filter adaptation */
  uint16_t pf3_adaptation          ; /*!< Low Frequency Peaking Filter adaptation */
  uint16_t dc_adaptation           ; /*!< DC Offset Adaptation */
  uint16_t vga_adaptation          ; /*!< Variable Gain Amplifier adaptation */
  uint16_t slicer_voffset_tuning   ; /*!< Slicer Vertical Offset tuning */
  uint16_t slicer_hoffset_tuning   ; /*!< Slicer Horizontal Offset tuning */
  uint16_t phase_offset_adaptation ; /*!< Phase Offset adaptation */
  uint16_t eye_margin_estimation   ; /*!< Eye margin estimation */
  uint16_t all_adaptation          ; /*!< All adaptation */
  uint16_t afe_bw_adaptation       ; /*!< AFE b/w adaptation */
  uint16_t pam_eye_margin_estimation; /*!< PAM eye margin */
  uint16_t reserved2               ;
  uint16_t reserved                ;
  uint16_t ss_pam4es_dfe_data_cdr  ; /*!< Steady state PAM4ES DFE data CDR */
  uint16_t ss_open_loop_debug      ; /*!< Steady State Open Loop debug */
};

/*! Lane User DFE Control Function Structure in Microcode
 *
 */
struct blackhawk7_v1l8p1_usr_ctrl_dfe_func_st {
  uint8_t dfe_tap1_adaptation      ; /*!< DFE tap 1 adaptation */
  uint8_t dfe_fx_taps_adaptation   ; /*!< DFE Fixed taps adaptation */
  uint8_t dfe_fl_taps_adaptation   ; /*!< DFE Floating taps adaptation */
  uint8_t dfe_dcd_adaptation       ; /*!< DFE tap Duty Cycle Distortion */
};

/*! Lane User Control Disable Function Struct
 *
 */
struct blackhawk7_v1l8p1_usr_ctrl_disable_functions_st {
  struct blackhawk7_v1l8p1_usr_ctrl_func_st field;
  uint16_t word;
};

/*! Lane User Control Disable DFE Function Struct
 *
 */
struct blackhawk7_v1l8p1_usr_ctrl_disable_dfe_functions_st {
  struct blackhawk7_v1l8p1_usr_ctrl_dfe_func_st field;
  uint8_t  byte;
};

/*! Used in BER APIs
 *
 */
struct blackhawk7_v1l8p1_ber_data_st {
    uint64_t num_errs;
    uint64_t num_bits;
    uint8_t lcklost;
    uint8_t prbs_chk_en;
    uint8_t cdrlcklost;
    uint8_t prbs_lck_state;
};


/*! Used for checking platform-specific padding
 *
 */
struct blackhawk7_v1l8p1_check_platform_info_st {
    char c;
    uint32_t d;
};

#define BER_DATA_ST_INIT {0, 0, 0, 0, 0, 0}

/*! @def NUM_ILV
 * The number of interleaves per lane 
 */
#define NUM_ILV 2

#define DATA_ARR_SIZE (6)
#define PHASE_ARR_SIZE (3)

#define DFE_ARR_SIZE (26)


/*! Blackhawk Lane status Struct
 *  Please ensure that decreasing order of size is maintained while adding new elements to this structure
 */
struct blackhawk7_v1l8p1_detailed_lane_status_st {
    /* =========== 32-bit variables start =========== */
    /** PRBS Error Count */
    uint32_t prbs_chk_errcnt;
    blackhawk7_v1l8p1_dbgfb_stats_st dbgfb_stats;
    /* =========== 32-bit variables end ============= */
    /* =========== 16-bit variables start =========== */
    /** One Hot DSC State */
    uint16_t dsc_sm[2];
    /** Horizontal left eye margin @ 1e-5 as seen by internal diagnostic slicer in mUI and mV */
    uint16_t heye_left;
    /** Horizontal right eye margin @ 1e-5 as seen by internal diagnostic slicer in mUI and mV */
    uint16_t heye_right;
    /** Vertical upper eye margin @ 1e-5 as seen by internal diagnostic slicer in mUI and mV */
    uint16_t veye_upper;
    /** Vertical lower eye margin @ 1e-5 as seen by internal diagnostic slicer in mUI and mV */
    uint16_t veye_lower;
    /** Link time in milliseconds */
    uint16_t link_time;
    /** LMS Slicer Threshold */
    int16_t  lms_thresh;
    /** blw gain */
    int16_t blw_gain;
    /** Frequency offset of local reference clock with respect to RX data in ppm */
    int16_t ppm;
    /** Estimate for Main tap */
    int16_t main_tap_est;
    /* TX equalization FIR tap weights */
    blackhawk7_v1l8p1_txfir_st txfir;
    /** Dummy 14 */
    int16_t dummy14;
    /** Dummy 16 */
    int16_t dummy16;
    /** Dummy 19 */
    int16_t dummy19;
    /** Dummy 20 */
    int16_t dummy20[2];
    /** Dummy 21 */
    int16_t dummy21[2];
    /** Dummy 8 */
    int16_t dummy8[DATA_ARR_SIZE][NUM_ILV];
    int16_t lvl_ss;
    int16_t lvl_90;

    /** RX PI counter value (Phase Error) for data slicer */
    uint16_t rx_pi_cnt_perr;
    /* =========== 16-bit variables end ============ */
    /* =========== 8-bit variables start =========== */
    /** RX PAM Mode */
    uint8_t rx_pam_mode;
    /** Order of PRBS Checker */
    uint8_t prbs_chk_order;
    /** Temperature Index */
    uint8_t  temp_idx;
    /** TX driver to disable high voltage control */
    uint8_t  ams_tx_drv_hv_disable;
    /** Analog Resistor Calibration value */
    uint8_t  ams_tx_ana_rescal;
    /** TX PAM Mode */
    uint8_t tx_pam_mode;
    /** TX Precoder Enable */
    uint8_t tx_prec_en;
    /* Are the TXFIR taps using the PAM4 range */
    uint8_t txfir_use_pam4_range;
    /* No of TXFIR Taps Enabled */
    uint8_t num_txfir_taps;
    /** Signal Detect */
    uint8_t  sigdet;
    /** Signal Detect Change */
    uint8_t  sigdet_chg;
    /** PMD RX Lock */
    uint8_t  pmd_lock;
    /** PMD RX Lock Change */
    uint8_t  pmd_lock_chg;
    /** TX PLL Select */
    uint8_t  pmd_tx_pll_select;
    /** RX PLL Select */
    uint8_t  pmd_rx_pll_select;
    /** Restart Count */
    uint8_t restart_count;
    /** Reset Count */
    uint8_t reset_count;
    /**  PMD Lock Count */
    uint8_t pmd_lock_count;
    /** Variable Gain Amplifier settings */
    uint8_t  vga;
    /** Main Peaking Filter setting */
    uint8_t  pf;
    /** Low Frequency Peaking Filter settings */
    uint8_t  pf2;
    /** High Frequency Peaking Filter settings */
    uint8_t  pf3;
    /** Main Frequency Peaking Filter reg settings */
    uint8_t  pf_reg[3];
    /** High Frequency Peaking Filter reg settings */
    uint8_t  pf3_reg[3];
    /** Extra AFE settings for Osprey7 */
    uint8_t refgen_range;
    /** Extra AFE settings for Osprey7 */
    uint8_t dfesum_bw;
    /** Extra AFE settings for Osprey7 */
    uint8_t fga_bw_cl;
    /** Extra AFE settings for Osprey7 */
    uint8_t pga_bw_cl;
    /** Extra AFE settings for Osprey7 */
    uint8_t pfhi_range;
    /** Extra AFE settings for Osprey7 */
    uint8_t pfmid_range;
    /** Extra AFE settings for Osprey7 */
    uint8_t pflow_range;
    /** Extra AFE settings for Osprey7 */
    uint8_t pfmid_10g;
    /** Extra AFE settings for Osprey7 */
    uint8_t ffe_enable;
    /** Extra AFE settings for Osprey7 */
    uint8_t ffesum_bw;
    /** Extra AFE settings for Osprey7 */
    uint8_t ffe_gain;
    /** Extra AFE settings for Osprey7 */
    int8_t ffe[2][NUM_ILV];
    /** Data23 Slicer Threshold */
    int8_t   data23_thresh;
    /** Data14 Slicer Threshold */
    int8_t   data14_thresh;
    /** Data05 Slicer Threshold */
    int8_t   data05_thresh;
    /** Phase1 Slicer Threshold */
    int8_t   phase1_thresh;
    /** Phase02 Slicer Threshold */
    int8_t   phase02_thresh;
    /** Delay of zero crossing slicer, m1, wrt to data in PI codes */
    int8_t clk90;
    /** Horizontal offset between data and phase */
    int8_t  dp_hoffset;
    /** Horizontal offset between data and lms */
    int8_t  dl_hoffset;
    int8_t  lms_dac4ck;
    int8_t  phase_dac4ck;
    int8_t  data_dac4ck;
    int8_t  lms_dac4ck_q;
    int8_t  phase_dac4ck_q;
    int8_t  data_dac4ck_q;
    /** DFE tap values */
    int8_t  dfe[DFE_ARR_SIZE][NUM_ILV];
    /** DC offset DAC control value */
    int8_t   dc_offset;
    /** Slicer calibration control codes (data0) */
    int8_t   thctrl_d[DATA_ARR_SIZE][NUM_ILV];
    /** Slicer calibration control codes (phase0) */
    int8_t   thctrl_p[PHASE_ARR_SIZE][NUM_ILV];
    /** Slicer calibration control codes (lms) */
    int8_t   thctrl_l[NUM_ILV];
    /** PRBS Checker Enable */
    uint8_t  prbs_chk_en;
    /** PRBS Checker Invert */
    uint8_t  prbs_chk_inv;
    /** PRBS Checker Lock */
    uint8_t  prbs_chk_lock;
    /** PRBS Checker Lock Lost */
    uint8_t  prbs_chk_lock_lost;
    /** lane_reset_state **/
    uint8_t reset_state;
    /** uC stopped state **/
    uint8_t stop_state;
    /** BER Error Rate string **/
    char ber_string[10];
    /** signal detect offset calibration pos */
    uint8_t ams_rx_sd_cal_pos;
    /** signal detect offset calibration neg */
    uint8_t ams_rx_sd_cal_neg;
    /** channel loss usr var */
    uint8_t pam4_chn_loss;
    /** vga1 bw control capacitor */
    uint8_t ams_rx_vga1_bwr;
    /** vga bw control inductor */
    uint8_t ams_rx_vga_dis_ind;
    /** vga3 inductor*/
    uint8_t ams_rx_vga2_cm;
    /** pf3 max bw */
    uint8_t ams_rx_eq2_hibw;
    /** vga0 rescal mux */
    uint8_t ams_rx_vga0_rescal_mux;
    /** vga1 rescal mux */
    uint8_t ams_rx_vga1_rescal_mux;
    /** vga2 rescal mux */
    uint8_t ams_rx_vga2_rescal_mux;
    uint8_t EQ1_bwr;
    uint8_t EQ2_bwr;
    uint8_t VGA1_bwr;
    uint8_t VGA2_bwr;
    uint8_t vga_dis_ind;
    /** lms calibration error */
    int8_t  lms_cal_err;
    /** phase calibration error */
    int8_t  phase_cal_err;
    /** data calibration error */
    int8_t data_cal_err;
    /** max data calibration error */
    int8_t max_data_cal_err;
    /* horizontal calibration residual error */
    int8_t res_dac4ck_err[4][2];
    /* horizontal calibration sign change count */
    uint8_t sgn_chn_cnt[4][2];
    /** dac4ck calibration failure */
    uint8_t dac4ck_cal_fail;
    /** eye margin failure */
    uint8_t eye_margin_fail;
    /** dac4ck monotonicity fail */
    uint8_t dac4ck_monotonicity_fail;
    /** hoffset rail out */
    uint8_t hoffset_rail_out;
    /** calibrated dac4ck reset */
    uint8_t reset_calibrated_dac4ck;
    /** Per interleave DCO controls */
    int8_t dc_adjust_a;
    /** Per interleave DCO controls */
    int8_t dc_adjust_b;
    /** Dummy 4 */
    int8_t dummy4;
    /** Dummy 5 */
    int8_t dummy5;
    /** Dummy 6 */
    uint8_t dummy6;
    /** Dummy 7 */
    int8_t dummy7[DATA_ARR_SIZE][NUM_ILV];
    /** Dummy 9 */
    uint8_t dummy9[2 + 6 + NUM_ILV];
    /** Dummy 10 */
    uint8_t dummy10[DATA_ARR_SIZE][NUM_ILV];
    /** Dummy 11 */
    int8_t dummy11[DATA_ARR_SIZE][NUM_ILV];
    /** Dummy 12 */
    int8_t dummy12[DATA_ARR_SIZE][NUM_ILV];
    /** Dummy 13 */
    int8_t dummy13;
    /** Dummy 15 */
    uint8_t dummy15[2];
    /** Dummy 17 */
    uint8_t dummy17[2];
    /** Dummy 18 */
    int8_t dummy18[3];
    /** Dummy 23 */
    uint8_t dummy23;
    /** Big endian */
    uint8_t big_endian;
    /** Padding to complete 4-byte boundary **/
    uint8_t padding_byte[2];
    /* =========== 8-bit variables end ============== */
}; /* struct blackhawk7_v1l8p1_detailed_lane_status_st  for BLACKHAWK7 */
/* Change the size if blackhawk7_v1l8p1_detailed_lane_status_st size changes */
#define SIZE_OF_EXTENDED_LANE_STATE (638 + 2)



#ifndef SMALL_FOOTPRINT
/*! Used for maintaining correctness of SIZE_OF_EXTENDED_LANE_STATE
 *
 */
typedef struct {
    uint8_t extended_lane_st_tmp[sizeof(struct blackhawk7_v1l8p1_detailed_lane_status_st)==SIZE_OF_EXTENDED_LANE_STATE ? 1: -1];
} blackhawk7_v1l8p1_detailed_lane_status_st_size_check;
#endif /* !SMALL_FOOTPRINT */

/****************************************************************************
 * @name Diagnostic Sampling
 *
 ****************************************************************************/
/***/

#ifdef STANDALONE_EVENT
#define DIAG_MAX_SAMPLES (64)
#else
/**
 * Diagnostic sample set size, BLACKHAWK7 variant.
 * Applies to collections of BER measurements, eye margins, etc.
 */
#define DIAG_MAX_SAMPLES (64)
#endif


/*! @} SerdesAPITypesTag */
/*! @} APITag */
#endif
#ifdef __cplusplus
}
#endif


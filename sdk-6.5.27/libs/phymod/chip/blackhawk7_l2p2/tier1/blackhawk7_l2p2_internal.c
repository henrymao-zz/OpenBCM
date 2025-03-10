/***********************************************************************************
 *                                                                                 *
 * Copyright: (c) 2021 Broadcom.                                                   *
 * Broadcom Proprietary and Confidential. All rights reserved.                     *
 *                                                                                 *
 ***********************************************************************************/

/***********************************************************************************
 ***********************************************************************************
 *  File Name     :  blackhawk7_l2p2_internal.c                                         *
 *  Created On    :  13/02/2014                                                    *
 *  Created By    :  Justin Gaither                                                *
 *  Description   :  Internal APIs for Serdes IPs                                  *
 *                                                                                 *
 ***********************************************************************************
 ***********************************************************************************/

#ifdef NON_SDK
#include <stdio.h>
#include <math.h>
#endif

#include <phymod/phymod_system.h>
#include "blackhawk7_l2p2_internal.h"
#include "blackhawk7_l2p2_internal_error.h"
#include "blackhawk7_l2p2_access.h"
#include "blackhawk7_l2p2_common.h"
#include "blackhawk7_l2p2_config.h"
#include "blackhawk7_l2p2_functions.h"
#include "blackhawk7_l2p2_select_defns.h"
#include "blackhawk7_l2p2_debug_functions.h"
#include "blackhawk7_l2p2_decode_print.h"
#include "blackhawk7_l2p2_diag.h"


/*! @file
 *
 */



#ifndef SMALL_FOOTPRINT
#ifndef UINT16_MAX
#define UINT16_MAX 0xFFFF
#endif
uint32_t blackhawk7_l2p2_INTERNAL_mult_with_overflow_check(uint32_t a, uint32_t b, uint8_t *of) {
    uint16_t c,d;
    uint32_t r,s;
    if (a > b) return blackhawk7_l2p2_INTERNAL_mult_with_overflow_check(b, a, of);
    *of = 0;
    c = (uint16_t)(b >> 16);
    d = UINT16_MAX & b;
    r = a * c;
    s = a * d;
    if (r > UINT16_MAX) *of = 1;
    r <<= 16;
    return (s + r);
}
#endif /* SMALL_FOOTPRINT */

#if !defined(SERDES_EXTERNAL_INFO_TABLE_EN)
static srds_info_t blackhawk7_l2p2_info;
#endif


srds_info_t *blackhawk7_l2p2_INTERNAL_get_blackhawk7_l2p2_info_ptr(srds_access_t *sa__) {
#if defined(SERDES_EXTERNAL_INFO_TABLE_EN)
    return blackhawk7_l2p2_acc_get_info_table_address(sa__);
#else
    UNUSED(sa__);
    return &blackhawk7_l2p2_info;
#endif
}

srds_info_t *blackhawk7_l2p2_INTERNAL_get_blackhawk7_l2p2_info_ptr_with_check(srds_access_t *sa__) {
    err_code_t err_code = ERR_CODE_NONE;
    srds_info_t * const blackhawk7_l2p2_info_ptr = blackhawk7_l2p2_INTERNAL_get_blackhawk7_l2p2_info_ptr(sa__);
    if (blackhawk7_l2p2_info_ptr->signature != SRDS_INFO_SIGNATURE) {
        err_code = blackhawk7_l2p2_init_blackhawk7_l2p2_info(sa__);
    }
    if (err_code != ERR_CODE_NONE) {
        EFUN_PRINTF(("ERROR: Serdes Info pointer not initialized correctly\n"));
        return (srds_info_t *)NULL;
    }
    return blackhawk7_l2p2_info_ptr;
}

err_code_t blackhawk7_l2p2_INTERNAL_match_ucode_from_info(srds_access_t *sa__, srds_info_t const *blackhawk7_l2p2_info_ptr) {
    INIT_SRDS_ERR_CODE
    uint16_t ucode_version_major;
    uint8_t ucode_version_minor;
    uint32_t ucode_version;

    if (blackhawk7_l2p2_info_ptr == NULL) {
        return(ERR_CODE_BAD_PTR_OR_INVALID_INPUT);
    }
    ESTM(ucode_version_major = rdcv_common_ucode_version());
    ESTM(ucode_version_minor = rdcv_common_ucode_minor_version());
    ucode_version = (uint32_t)((ucode_version_major << 8) | ucode_version_minor);

    if (ucode_version == blackhawk7_l2p2_info_ptr->ucode_version) {
        return(ERR_CODE_NONE);
    } else {
        EFUN_PRINTF(("ERROR:  ucode version of the current thread not matching with stored blackhawk7_l2p2_info->ucode_version, Expected 0x%08X, but received 0x%08X.\n",
                    blackhawk7_l2p2_info_ptr->ucode_version, ucode_version));
        return(ERR_CODE_UCODE_VERIFY_FAIL);
    }
}

/* This function is getting deprecated.
   Please use blackhawk7_l2p2_INTERNAL_get_blackhawk7_l2p2_info_ptr_with_check and blackhawk7_l2p2_INTERNAL_match_ucode_from_info instead */
err_code_t blackhawk7_l2p2_INTERNAL_verify_blackhawk7_l2p2_info(srds_access_t *sa__, srds_info_t const *blackhawk7_l2p2_info_ptr) {
    err_code_t err_code = ERR_CODE_NONE;

    if (blackhawk7_l2p2_info_ptr == NULL) {
        return(ERR_CODE_BAD_PTR_OR_INVALID_INPUT);
    }
    if (blackhawk7_l2p2_info_ptr->signature != SRDS_INFO_SIGNATURE) {
        EFUN_PRINTF(("ERROR:  Mismatch in blackhawk7_l2p2_info signature.  Expected 0x%08X, but received 0x%08X.\n",
                    SRDS_INFO_SIGNATURE, blackhawk7_l2p2_info_ptr->signature));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_INFO_TABLE_ERROR));
    }
    err_code = blackhawk7_l2p2_INTERNAL_match_ucode_from_info(sa__, blackhawk7_l2p2_info_ptr);

    if (err_code != ERR_CODE_NONE) {
        /* ucode version mismatch */
        return(ERR_CODE_MICRO_INIT_NOT_DONE);
    }
    return (ERR_CODE_NONE);
}

#ifndef SMALL_FOOTPRINT

/* Timestamp check to see if heartbeat timer is programmed correctly for the COMCLK frequency it is running at */
err_code_t blackhawk7_l2p2_INTERNAL_test_uc_timestamp_with_print_options(srds_access_t *sa__, uint8_t console_print_options) {
#ifdef SERDES_API_FLOATING_POINT
    INIT_SRDS_ERR_CODE
    uint16_t time = 0;
    uint16_t time1 = 0;
    uint16_t time2 = 0;
    USR_DOUBLE resolution;
    const uint16_t test_delay=400;

    const USR_DOUBLE max_resolution=11.0;
    const USR_DOUBLE min_resolution=9.0;

    EFUN(blackhawk7_l2p2_pmd_uc_cmd(sa__, CMD_UC_DBG, CMD_UC_DBG_TIMESTAMP, 100));
    ESTM(time1=rd_uc_dsc_data());
    EFUN(USR_DELAY_MS(test_delay));
    EFUN(blackhawk7_l2p2_pmd_uc_cmd(sa__, CMD_UC_DBG, CMD_UC_DBG_TIMESTAMP, 100));
    ESTM(time2=rd_uc_dsc_data());
    time=(uint16_t)(time2-time1);
    if(time == 0) {
        EFUN_PRINTF(("%s ERROR : Diag  timestamp fail, start = 0x%04x, end = 0x%04x\n", API_FUNCTION_NAME, time1, time2));
        return (ERR_CODE_DIAG_TIMESTAMP_FAIL);
    }
    resolution=test_delay*1000.0/(double)time;
    if((resolution<min_resolution)||(resolution>max_resolution)){
        if (console_print_options) {
            EFUN_PRINTF(("\nERROR : Lane %i:\tuC timestamp: %i\t\tResolution: %.1fus/count. Passing resolution limits:\tMax: %.1fus/count\tMin: %.1fus/count\n",blackhawk7_l2p2_acc_get_lane(sa__),time,resolution,max_resolution,min_resolution));
        }
        return(ERR_CODE_DIAG_TIMESTAMP_FAIL);
    }
    else {
        if (console_print_options) {
            EFUN_PRINTF(("\nPassed timestamp check : Lane %i:\tuC timestamp: %i\t\tResolution: %.1fus/count. Passing resolution limits:\tMax: %.1fus/count\tMin: %.1fus/count\n",blackhawk7_l2p2_acc_get_lane(sa__),time,resolution,max_resolution,min_resolution));
        }
   }
#else
    USR_PRINTF(("%s : This function needs SERDES_API_FLOATING_POINT define to operate \n", API_FUNCTION_NAME));
#endif
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_num_bits_per_ms(srds_access_t *sa__, uint8_t select_rx, uint32_t *num_bits_per_ms) {
    INIT_SRDS_ERR_CODE
    uint8_t osr_mode = 0;
    uint8_t pam4_mode = 0;
    uint8_t pll_select = 0, prev_pll = 0;
    uint64_t temp_value;

    struct blackhawk7_l2p2_uc_core_config_st core_config = UC_CORE_CONFIG_INIT;
    blackhawk7_l2p2_osr_mode_st osr_mode_st;
    ENULL_MEMSET(&osr_mode_st, 0, sizeof(blackhawk7_l2p2_osr_mode_st));

    {
        EFUN(blackhawk7_l2p2_INTERNAL_get_osr_mode(sa__, &osr_mode_st));
        if (select_rx) {
            osr_mode = osr_mode_st.rx;
        } else {
            osr_mode = osr_mode_st.tx;
        }
    }

    if (select_rx) {
        ESTM(pam4_mode = rd_rx_pam4_mode());
    } else {
        ESTM(pam4_mode = rd_tx_pam4_mode());
    }

    ESTM(prev_pll = blackhawk7_l2p2_acc_get_pll_idx(sa__));
    if (select_rx) {
        ESTM(pll_select = rd_rx_pll_select());
    } else {
        ESTM(pll_select = rd_tx_pll_select());
    }
    EFUN(blackhawk7_l2p2_acc_set_pll_idx(sa__,pll_select));

    EFUN(blackhawk7_l2p2_get_uc_core_config(sa__, &core_config));
    /* *num_bits_per_ms = (uint32_t)((((uint64_t)core_config.vco_rate_in_Mhz * 100000UL) / blackhawk7_l2p2_osr_mode_enum_to_int_x1000(osr_mode))*10);
     */
    COMPILER_64_SET(temp_value, 0, core_config.vco_rate_in_Mhz);
    COMPILER_64_UMUL_32(temp_value, 100000UL);
    COMPILER_64_UDIV_32(temp_value, blackhawk7_l2p2_osr_mode_enum_to_int_x1000(osr_mode));
    COMPILER_64_UMUL_32(temp_value, 10);
    *num_bits_per_ms = COMPILER_64_LO(temp_value);

    if(pam4_mode > 0) *num_bits_per_ms <<= 1;
    EFUN(blackhawk7_l2p2_acc_set_pll_idx(sa__,prev_pll));
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_display_BER(srds_access_t *sa__, uint16_t time_ms) {
    INIT_SRDS_ERR_CODE
    char string[SRDS_MAX_BER_STR_LEN];
      EFUN(blackhawk7_l2p2_INTERNAL_get_BER_string(sa__,time_ms,string, sizeof(string)));
      USR_PRINTF(("%s",string));
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_BER_string(srds_access_t *sa__, uint16_t time_ms, char *string, uint8_t string_size) {
    INIT_SRDS_ERR_CODE
    char string2[4];
    char string_extra[3] = "";
    uint8_t chk_en = 0;
    /* struct blackhawk7_l2p2_ber_data_st ber_data_local = BER_DATA_ST_INIT; */
    struct blackhawk7_l2p2_ber_data_st ber_data_local;
    err_code_t err = ERR_CODE_NONE;

    ENULL_MEMSET(&ber_data_local, 0, sizeof(ber_data_local));
    if(string == NULL) {
        return(ERR_CODE_BAD_PTR_OR_INVALID_INPUT);
    }
    ESTM(chk_en = rd_prbs_chk_en());
    if(chk_en == 0) {
        USR_SNPRINTF(string, (size_t)(string_size), " !chk_en ");
        return(ERR_CODE_NONE);
    }
    {
        enum blackhawk7_l2p2_prbs_chk_timer_selection_enum timer_sel = USE_HW_TIMERS;

        err = blackhawk7_l2p2_INTERNAL_get_BER_data(sa__, time_ms, &ber_data_local, timer_sel);
    }

    if(err == ERR_CODE_RX_CLKGATE_FRC_ON) {
        USR_SNPRINTF(string, (size_t)(string_size), "clk_gated");
        return(ERR_CODE_NONE);
    }
    else if(err == ERR_CODE_NO_PMD_RX_LOCK) {
        USR_SNPRINTF(string, (size_t)(string_size), "!pmd_lock");
        return(ERR_CODE_NONE);
    }
    else if(err != ERR_CODE_NONE) {
        return blackhawk7_l2p2_error(sa__, err);
    }

    /*if((ber_data_local.num_errs < 3) && (ber_data_local.lcklost == 0)) {*/   /* lcklost = 0 */
    if((COMPILER_64_LO(ber_data_local.num_errs) < 3) && (ber_data_local.lcklost == 0)) {   /* lcklost = 0 */
        USR_SNPRINTF(string2, sizeof(string2), " <");
        /*ber_data_local.num_errs = 3;*/
        COMPILER_64_SET(ber_data_local.num_errs, 0, 3);
    } else {
        USR_SNPRINTF(string2, sizeof(string2), "  ");
    }
    if(ber_data_local.cdrlcklost) {
        USR_SNPRINTF(string_extra, sizeof(string_extra), "*");
    }
    if(ber_data_local.lcklost == 1) {    /* lcklost = 1 */
        if(ber_data_local.prbs_lck_state == PRBS_CHECKER_NOT_ENABLED) {
            USR_SNPRINTF(string, (size_t)(string_size), "         ");
        }
        else if(ber_data_local.prbs_lck_state == PRBS_CHECKER_LOCK_LOST_AFTER_LOCK) {
            USR_SNPRINTF(string, (size_t)(string_size), " Lck lost");
        }
        else
        {
            USR_SNPRINTF(string, (size_t)(string_size), "  !Lock  ");
        }
    }
    else {                    /* lcklost = 0 */
        uint16_t x=0,y=0,z=0,srds_div;

        /*if(ber_data_local.num_errs < ber_data_local.num_bits) {*/
        if(COMPILER_64_GE(ber_data_local.num_errs, ber_data_local.num_bits)) {
        } else {
            uint64_t temp_dividend;
            uint64_t temp_divisor;
            while(1) {
                /*srds_div = (uint16_t)(((ber_data_local.num_errs<<1) + ber_data_local.num_bits)/(ber_data_local.num_bits<<1));*/
                COMPILER_64_COPY(temp_dividend, ber_data_local.num_errs);
                COMPILER_64_SHL(temp_dividend, 1);
                COMPILER_64_ADD_64(temp_dividend, ber_data_local.num_bits);

                COMPILER_64_COPY(temp_divisor, ber_data_local.num_bits);
                COMPILER_64_SHL(temp_divisor, 1);

                COMPILER_64_UDIV_64(temp_dividend, temp_divisor);

                srds_div = (uint16_t) COMPILER_64_LO( temp_dividend );

                if(srds_div>=10) break;
                /*ber_data_local.num_errs = ber_data_local.num_errs*10;*/
                COMPILER_64_UMUL_32(ber_data_local.num_errs, 10);
                z++;
            }
            if(srds_div>=100) {
                srds_div = srds_div/10;
                /* coverity[overflow_const] */
                z--;
            }
            x=srds_div/10;
            y = (uint16_t)(srds_div - 10*x);
            /* coverity[overflow_const] */
            z--;
            USR_SNPRINTF(string, (size_t)(string_size), "%s%d.%1de-%02d%s",string2,x,y,z,string_extra);
        }

    }
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_BER_data(srds_access_t *sa__, uint16_t time_ms, struct blackhawk7_l2p2_ber_data_st *ber_data, enum blackhawk7_l2p2_prbs_chk_timer_selection_enum timer_sel) {
    INIT_SRDS_ERR_CODE
    uint8_t  lcklost = 0;
    uint32_t err_cnt= 0;

    /* Configure, Start, and Poll for end */
    if (timer_sel == USE_HW_TIMERS) {
        /* Create PRBS HW timer ctrl struct */
        struct blackhawk7_l2p2_prbs_chk_hw_timer_ctrl_st prbs_chk_hw_timer_ctrl;

        /* Call functionality step by step */
        EFUN(blackhawk7_l2p2_BER_setup_measurement(sa__, time_ms, ber_data, &prbs_chk_hw_timer_ctrl));
        EFUN(blackhawk7_l2p2_BER_poll_measurement(sa__, ber_data, &prbs_chk_hw_timer_ctrl));
        EFUN(blackhawk7_l2p2_BER_get_measurement(sa__, ber_data, &prbs_chk_hw_timer_ctrl));
    }
    /* Else HW timers not available, use SW TIMERS method */
    else
    {
        uint8_t clk_gate = 0;
        UNUSED(timer_sel);
        ESTM(ber_data->prbs_chk_en = rd_prbs_chk_en());
        ESTM(ber_data->prbs_lck_state = rd_prbs_chk_lock_state());
        ESTM(clk_gate = rd_ln_rx_s_clkgate_frc_on());
        if(ber_data->prbs_chk_en == 0) {
            return(ERR_CODE_PRBS_CHK_DISABLED);
        }
        else if (clk_gate == 1) {
            return(ERR_CODE_RX_CLKGATE_FRC_ON);
        }
        EFUN(blackhawk7_l2p2_prbs_err_count_state(sa__, &err_cnt, &lcklost)); /* clear error counters */
        EFUN(USR_DELAY_MS(time_ms));
        EFUN(blackhawk7_l2p2_prbs_err_count_state(sa__, &err_cnt, &lcklost));
        ber_data->lcklost = lcklost;
        if(ber_data->lcklost == 0) {
            uint32_t num_bits_per_ms=0;
            EFUN(blackhawk7_l2p2_INTERNAL_get_num_bits_per_ms(sa__, 1, &num_bits_per_ms));
/*
            ber_data->num_bits = (uint64_t)num_bits_per_ms*(uint64_t)time_ms;
            ber_data->num_errs = err_cnt;
*/
            COMPILER_64_SET(ber_data->num_bits, 0, num_bits_per_ms);
            COMPILER_64_UMUL_32(ber_data->num_bits, time_ms);
            COMPILER_64_SET(ber_data->num_errs, 0, err_cnt);
            ESTM(lcklost = rd_prbs_chk_lock_lost_lh()); /* Clear sticky bit */
            UNUSED(lcklost);
        }

    }

    return(ERR_CODE_NONE);
}

/* Check CDR lost lock */
err_code_t blackhawk7_l2p2_INTERNAL_prbs_chk_cdr_lock_lost(srds_access_t *sa__, uint8_t *cdrlcklost) {
    INIT_SRDS_ERR_CODE
    uint32_t err_cnt, num_bits_per_ms = 0, num_bits;
    uint8_t lcklost;
    uint8_t time_ms = 1;
    if(!cdrlcklost) {
        return (ERR_CODE_BAD_PTR_OR_INVALID_INPUT);
    }
    EFUN(blackhawk7_l2p2_prbs_err_count_state(sa__, &err_cnt,&lcklost)); /* clear error counters */
    EFUN(USR_DELAY_MS(time_ms));
    EFUN(blackhawk7_l2p2_prbs_err_count_state(sa__, &err_cnt,&lcklost));
    EFUN(blackhawk7_l2p2_INTERNAL_get_num_bits_per_ms(sa__, 1, &num_bits_per_ms));
    num_bits = num_bits_per_ms*time_ms;

    /* check for BER>0.25 */
    *cdrlcklost = lcklost || (err_cnt>(num_bits>>2));

    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_get_prbs_timeout_count_from_time(uint16_t time_ms, uint16_t * time_ms_adjusted, struct blackhawk7_l2p2_prbs_chk_hw_timer_ctrl_st * const prbs_chk_hw_timer_ctrl) {
    uint16_t timeout_value=0;
    uint8_t timer_unit_sel;

    if(!time_ms_adjusted || !prbs_chk_hw_timer_ctrl) {
        return (ERR_CODE_BAD_PTR_OR_INVALID_INPUT);
    }

    *time_ms_adjusted = time_ms;

    /* Select unit of time for PRBS HW TIMER */
    if (time_ms < 100) {
        timer_unit_sel = PRBS_CHK_EN_TIMER_UNIT_SEL_1MS;
        timeout_value = (uint32_t)time_ms;
    }
    else if (time_ms < 1000) {
        timer_unit_sel = PRBS_CHK_EN_TIMER_UNIT_SEL_10MS;
        timeout_value = (uint32_t)time_ms/10;
    }
    else {
        timer_unit_sel = PRBS_CHK_EN_TIMER_UNIT_SEL_100MS;
        timeout_value = (uint32_t)time_ms/100;
    }

    prbs_chk_hw_timer_ctrl->prbs_chk_en_timer_unit_timeout = timeout_value;
    prbs_chk_hw_timer_ctrl->prbs_chk_en_timer_unit_sel = timer_unit_sel;

    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_hw_timer_sync_delay(srds_access_t *sa__) {
    INIT_SRDS_ERR_CODE
    uint8_t i, timer_unit_sel;
    uint8_t ms_delay = 0;
    uint16_t delay_count = 1;
    UNUSED(sa__);
    ESTM(timer_unit_sel = rd_prbs_chk_en_timer_unit_sel());

    /* prbs_chk_en_timer_unit_sel register should have a valid value when calling this function */
    if((timer_unit_sel == PRBS_CHK_EN_TIMER_UNIT_SEL_DISABLED) || (timer_unit_sel == PRBS_CHK_EN_TIMER_UNIT_SEL_RESERVED)) {
        return ERR_CODE_INVALID_VALUE;
    }

    /* Determine the delay to wait for synchronization based on the prbs_chk_en_timer_unit_sel */
    for(i=PRBS_CHK_EN_TIMER_UNIT_SEL_1US; i<=PRBS_CHK_EN_TIMER_UNIT_SEL_100MS; i++) {
        if(i == PRBS_CHK_EN_TIMER_UNIT_SEL_1MS) {
            ms_delay = 1;
            delay_count /= 1000;
        }
        if(i < timer_unit_sel) {
            delay_count = (uint16_t)(delay_count * 10);
        } else {
            break;
        }
    }
    /* Add the appropriate delay */
    if(ms_delay){
        EFUN(USR_DELAY_MS(delay_count));
    } else {
        if(delay_count!=1) EFUN(USR_DELAY_US(delay_count));
    }
    return ERR_CODE_NONE;
}



err_code_t blackhawk7_l2p2_INTERNAL_ladder_setting_to_mV(srds_access_t *sa__, int16_t ctrl, uint8_t range_250, afe_override_slicer_sel_t slicer_sel, int16_t *nlmv_val) {
    uint16_t absv;                                    /* Absolute value of ctrl */
    int16_t nlmv=0;                                     /* Non-linear value */
    UNUSED(sa__);
    UNUSED(slicer_sel);
    if (nlmv_val == NULL) {
        return(ERR_CODE_BAD_PTR_OR_INVALID_INPUT);
    }

    /* Get absolute value */
    absv = (uint16_t)(SRDS_ABS(ctrl));

    {
       UNUSED(range_250);

       nlmv = (int16_t)((absv*225+127/2)/127);
    }
    /* Add sign and return */
    *nlmv_val=(int16_t)((ctrl>=0) ? nlmv : -nlmv);

    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_pam4_to_bin(srds_access_t *sa__, char var, char bin[], size_t bin_size) {
    if(!bin) {
        return(blackhawk7_l2p2_error(sa__, ERR_CODE_BAD_PTR_OR_INVALID_INPUT));
    }

  switch (var) {
    case '0': USR_SNPRINTF(bin, bin_size, "00");
              break;
    case '1': USR_SNPRINTF(bin, bin_size, "01");
              break;
    case '2': USR_SNPRINTF(bin, bin_size, "11");  /* To account for PAM4 Gray coding */
              break;
    case '3': USR_SNPRINTF(bin, bin_size, "10");  /* To account for PAM4 Gray coding */
              break;
    case '_': bin[0] = '\0';
              break;
    default : bin[0] = '\0';
              EFUN_PRINTF(("ERROR: Invalid PAM4 format Pattern\n"));
              return (blackhawk7_l2p2_error(sa__, ERR_CODE_CFG_PATT_INVALID_PAM4));
  }
  return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_compute_bin(srds_access_t *sa__, char var, char bin[], size_t bin_size) {
    if(!bin) {
        return(blackhawk7_l2p2_error(sa__, ERR_CODE_BAD_PTR_OR_INVALID_INPUT));
    }

  switch (var) {
    case '0':  USR_SNPRINTF(bin, bin_size, "0000");
               break;
    case '1':  USR_SNPRINTF(bin, bin_size, "0001");
               break;
    case '2':  USR_SNPRINTF(bin, bin_size, "0010");
               break;
    case '3':  USR_SNPRINTF(bin, bin_size, "0011");
               break;
    case '4':  USR_SNPRINTF(bin, bin_size, "0100");
               break;
    case '5':  USR_SNPRINTF(bin, bin_size, "0101");
               break;
    case '6':  USR_SNPRINTF(bin, bin_size, "0110");
               break;
    case '7':  USR_SNPRINTF(bin, bin_size, "0111");
               break;
    case '8':  USR_SNPRINTF(bin, bin_size, "1000");
               break;
    case '9':  USR_SNPRINTF(bin, bin_size, "1001");
               break;
    case 'a':
    case 'A':  USR_SNPRINTF(bin,bin_size,"1010");
               break;
    case 'b':
    case 'B':  USR_SNPRINTF(bin,bin_size,"1011");
               break;
    case 'c':
    case 'C':  USR_SNPRINTF(bin,bin_size,"1100");
               break;
    case 'd':
    case 'D':  USR_SNPRINTF(bin,bin_size,"1101");
               break;
    case 'e':
    case 'E':  USR_SNPRINTF(bin,bin_size,"1110");
               break;
    case 'f':
    case 'F':  USR_SNPRINTF(bin,bin_size,"1111");
               break;
    case '_': bin[0] = '\0';
              break;
    default : bin[0] = '\0';
               USR_PRINTF(("ERROR: Invalid Hexadecimal Pattern\n"));
               return (blackhawk7_l2p2_error(sa__, ERR_CODE_CFG_PATT_INVALID_HEX));
  }
  return (ERR_CODE_NONE);
}


err_code_t blackhawk7_l2p2_INTERNAL_compute_hex(srds_access_t *sa__, char bin[],uint8_t *hex) {
  if(!hex || !bin) {
    return(blackhawk7_l2p2_error(sa__, ERR_CODE_BAD_PTR_OR_INVALID_INPUT));
  }

  if (!USR_STRCMP(bin,"0000")) {
    *hex = 0x0;
  }
  else if (!USR_STRCMP(bin,"0001")) {
    *hex = 0x1;
  }
  else if (!USR_STRCMP(bin,"0010")) {
    *hex = 0x2;
  }
  else if (!USR_STRCMP(bin,"0011")) {
    *hex = 0x3;
  }
  else if (!USR_STRCMP(bin,"0100")) {
    *hex = 0x4;
  }
  else if (!USR_STRCMP(bin,"0101")) {
    *hex = 0x5;
  }
  else if (!USR_STRCMP(bin,"0110")) {
    *hex = 0x6;
  }
  else if (!USR_STRCMP(bin,"0111")) {
    *hex = 0x7;
  }
  else if (!USR_STRCMP(bin,"1000")) {
    *hex = 0x8;
  }
  else if (!USR_STRCMP(bin,"1001")) {
    *hex = 0x9;
  }
  else if (!USR_STRCMP(bin,"1010")) {
    *hex = 0xA;
  }
  else if (!USR_STRCMP(bin,"1011")) {
    *hex = 0xB;
  }
  else if (!USR_STRCMP(bin,"1100")) {
    *hex = 0xC;
  }
  else if (!USR_STRCMP(bin,"1101")) {
    *hex = 0xD;
  }
  else if (!USR_STRCMP(bin,"1110")) {
    *hex = 0xE;
  }
  else if (!USR_STRCMP(bin,"1111")) {
    *hex = 0xF;
  }
  else {
    EFUN_PRINTF(("ERROR: Invalid Binary to Hex Conversion\n"));
    *hex = 0x0;
    return (blackhawk7_l2p2_error(sa__, ERR_CODE_CFG_PATT_INVALID_BIN2HEX));
  }
  return (ERR_CODE_NONE);
}

#define MICRO_STOP_BITS  (0x7F)


uint8_t blackhawk7_l2p2_INTERNAL_stop_micro(srds_access_t *sa__, uint8_t graceful, err_code_t *err_code_p) {
   INIT_SRDS_ERR_CODE
   uint8_t stop_state = 0;

   if(!err_code_p) {
       return(0xFF);
   }

   /* Log current micro stop status */
   EPSTM2((stop_state = rdv_usr_sts_micro_stopped()),0xFF);

   /* Stop micro only if micro is not stopped currently */
   if (!(stop_state & MICRO_STOP_BITS)) {
       if (graceful) {
           EPFUN2((blackhawk7_l2p2_stop_rx_adaptation(sa__, 1)),0xFF);
       }
       else {
           EPFUN2((blackhawk7_l2p2_pmd_uc_control(sa__, CMD_UC_CTRL_STOP_IMMEDIATE,GRACEFUL_STOP_TIME)),0xFF);
       }
   }

   /* Return the previous micro stop status */
   return(stop_state);
}




/********************************************************/
/*  Global RAM access through Micro Register Interface  */
/********************************************************/
/* Micro Global RAM Byte Read */
uint8_t blackhawk7_l2p2_INTERNAL_rdb_uc_var(srds_access_t *sa__, err_code_t *err_code_p, uint32_t addr) {
    INIT_SRDS_ERR_CODE
    uint8_t rddata;

    if(!err_code_p) {
        return(0);
    }
    EPSTM(rddata = blackhawk7_l2p2_rdb_uc_ram(sa__, err_code_p, addr)); /* Use Micro register interface for reading RAM */
    return (rddata);
}

/* Micro Global RAM Word Read */
uint16_t blackhawk7_l2p2_INTERNAL_rdw_uc_var(srds_access_t *sa__, err_code_t *err_code_p, uint32_t addr) {
  uint16_t rddata;
  INIT_SRDS_ERR_CODE

  if(!err_code_p) {
      return(0);
  }
  if (addr%2 != 0) {                                         /* Validate even address */
      *err_code_p = ERR_CODE_INVALID_RAM_ADDR;
      USR_PRINTF(("Error incorrect addr x%04x\n",addr));
      return (0);
  }
  EPSTM(rddata = blackhawk7_l2p2_rdw_uc_ram(sa__, err_code_p, addr)); /* Use Micro register interface for reading RAM */
  return (rddata);
}

/* Micro Global RAM Byte Write  */
err_code_t blackhawk7_l2p2_INTERNAL_wrb_uc_var(srds_access_t *sa__, uint32_t addr, uint8_t wr_val) {

    return (blackhawk7_l2p2_wrb_uc_ram(sa__, addr, wr_val));          /* Use Micro register interface for writing RAM */
}

/* Micro Global RAM Word Write  */
err_code_t blackhawk7_l2p2_INTERNAL_wrw_uc_var(srds_access_t *sa__, uint32_t addr, uint16_t wr_val) {
    if (addr%2 != 0) {                                       /* Validate even address */
      USR_PRINTF(("Error incorrect addr x%04x\n",addr));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_INVALID_RAM_ADDR));
    }
    return (blackhawk7_l2p2_wrw_uc_ram(sa__, addr, wr_val));          /* Use Micro register interface for writing RAM */
}


/***********************/
/*  Event Log Display  */
/***********************/
err_code_t blackhawk7_l2p2_INTERNAL_event_log_dump_callback(srds_access_t *sa__, void *arg, uint8_t byte_count, uint16_t data) {
    blackhawk7_l2p2_INTERNAL_event_log_dump_state_t * const state_ptr = (blackhawk7_l2p2_INTERNAL_event_log_dump_state_t *)arg;
    const uint8_t bytes_per_row=16;

    /* when detecting more than 256 bytes of consequtive 0 in data,
     * terminate the printing to the log
     */
    if (state_ptr->zero_cnt == 0xffff) {
        return (ERR_CODE_NONE);
    }
    if (data == 0) {
        state_ptr->zero_cnt++;
    }
    else {
        state_ptr->zero_cnt = 0;
    }
    if (byte_count == 0) {
        if (state_ptr->line_start_index != state_ptr->index) {
            EFUN_PRINTF(("%*s    %d\n", 4*(bytes_per_row - state_ptr->index + state_ptr->line_start_index), "", state_ptr->line_start_index));
        }
        return (ERR_CODE_NONE);
    }
    if (byte_count == 1) {
        /* There is a trailing byte in the event log.
         * The simplest way to handle it is to print out a whole word, but mask
         * the invalid upper byte.
         */
        data &= 0xFF;
    }
    EFUN_PRINTF(("  0x%04x", ((data & 0xFF) << 8) | (data >> 8)));
    state_ptr->index = (uint16_t)(state_ptr->index + 2);
    if (state_ptr->index % bytes_per_row == 0) {
        EFUN_PRINTF(("    %d\n", state_ptr->line_start_index));
        state_ptr->line_start_index = state_ptr->index;
        /* 128 words/256 bytes is the largest event data section.
         * 0xffff is used as a flag to terminate the printing to the logfile
         */
        if (state_ptr->zero_cnt > 128) {
            state_ptr->zero_cnt = 0xffff;
        }
    }

    return(ERR_CODE_NONE);
}



err_code_t blackhawk7_l2p2_INTERNAL_read_event_log_with_callback(srds_access_t *sa__,
                                                        uint8_t micro_num,
                                                        uint8_t bypass_micro,
                                                        void *arg,
                                                        err_code_t (*callback)(srds_access_t *, void *, uint8_t, uint16_t)) {
    INIT_SRDS_ERR_CODE

    srds_info_t const * const blackhawk7_l2p2_info_ptr = blackhawk7_l2p2_INTERNAL_get_blackhawk7_l2p2_info_ptr_with_check(sa__);
    uint16_t rd_idx;
    uint8_t current_lane;


    EFUN(blackhawk7_l2p2_INTERNAL_match_ucode_from_info(sa__, blackhawk7_l2p2_info_ptr));

    if (micro_num >= blackhawk7_l2p2_info_ptr->micro_count) {
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_BAD_PTR_OR_INVALID_INPUT));
    }
    /* Read Current lane so that it can be restored at the end of function */
    current_lane = blackhawk7_l2p2_acc_get_lane(sa__);
    /* 2 lanes per micro; Set lane appropriate for the desired micro */
    EFUN(blackhawk7_l2p2_acc_set_physical_lane(sa__,(uint8_t)(micro_num<<1)));
    EFUN_PRINTF(("\n\n********************************************\n"));
    EFUN_PRINTF((    "**** SERDES UC TRACE MEMORY DUMP ***********\n"));
    EFUN_PRINTF((    "********************************************\n"));

    if (bypass_micro) {
        ESTM(rd_idx = rducv_trace_mem_wr_idx());
        if (blackhawk7_l2p2_info_ptr->trace_memory_descending_writes) {
            ++rd_idx;
            if (rd_idx >= blackhawk7_l2p2_info_ptr->trace_mem_ram_size) {
                rd_idx = 0;
            }
        } else {
            if (rd_idx == 0) {
                rd_idx = (uint16_t)blackhawk7_l2p2_info_ptr->trace_mem_ram_size;
            }
            --rd_idx;
        }
    } else {
        uint16_t reset_state;
        uint8_t lanes_per_micro = blackhawk7_l2p2_info_ptr->lane_count;
        uint8_t i = 0;
        for(i = 1; i < lanes_per_micro; i++) {
            ESTM(reset_state = rd_lane_dp_reset_state());
            if (reset_state & 0x0007) {
                EFUN(blackhawk7_l2p2_acc_set_physical_lane(sa__,(uint8_t)((micro_num<<1) + i)));
            }
            else {
                break;
            }
        }
        /* Start Read to stop uC logging and read the word at last event written by uC */
        EFUN(blackhawk7_l2p2_pmd_uc_cmd(sa__, CMD_EVENT_LOG_READ, CMD_EVENT_LOG_READ_START, GRACEFUL_STOP_TIME));
        ESTM(rd_idx = rducv_trace_mem_rd_idx());
    }

    EFUN_PRINTF(( "\n  DEBUG INFO: trace memory read index = 0x%04x\n", rd_idx));

    EFUN_PRINTF(("  DEBUG INFO: trace memory size = 0x%04x\n\n", blackhawk7_l2p2_info_ptr->trace_mem_ram_size));

    if (blackhawk7_l2p2_info_ptr->trace_memory_descending_writes) {
        /* Micro writes trace memory using descending addresses.
         * So read using ascending addresses using block read
         */

        EFUN(blackhawk7_l2p2_INTERNAL_rdblk_uc_generic_ram(sa__,
                                                  blackhawk7_l2p2_info_ptr->trace_mem_ram_base + (uint32_t)(blackhawk7_l2p2_info_ptr->grp_ram_size*micro_num),
                                                  (uint16_t)blackhawk7_l2p2_info_ptr->trace_mem_ram_size,
                                                  rd_idx,
                                                  (uint16_t)blackhawk7_l2p2_info_ptr->trace_mem_ram_size,
                                                  arg,
                                                  callback));
    } else {
        /* Micro writes trace memory using descending addresses.
         * So read using ascending addresses using block read
         */
        EFUN(blackhawk7_l2p2_INTERNAL_rdblk_uc_generic_ram_descending(sa__,
                                                             blackhawk7_l2p2_info_ptr->trace_mem_ram_base + (uint32_t)(blackhawk7_l2p2_info_ptr->grp_ram_size*micro_num),
                                                             (uint16_t)blackhawk7_l2p2_info_ptr->trace_mem_ram_size,
                                                             rd_idx,
                                                             (uint16_t)blackhawk7_l2p2_info_ptr->trace_mem_ram_size,
                                                             arg,
                                                             callback));
    }


    if (!bypass_micro) {
        /* Read Done to resume logging  */
        EFUN(blackhawk7_l2p2_pmd_uc_cmd(sa__, CMD_EVENT_LOG_READ, CMD_EVENT_LOG_READ_DONE, 50));
    }
    EFUN(blackhawk7_l2p2_acc_set_lane(sa__,current_lane));
    return(ERR_CODE_NONE);
}  /* blackhawk7_l2p2_INTERNAL_read_event_log_with_callback() */


#ifdef TO_FLOATS
/* convert uint32_t to float8 */
float8_t blackhawk7_l2p2_INTERNAL_int32_to_float8(uint32_t input) {
    int8_t cnt;
    uint8_t output;

    if(input == 0) {
      return(0);
    } else if(input == 1) {
      return(0xe0);
    } else {
      cnt = 0;
      input = input & 0x7FFFFFFF; /* get rid of MSB which may be lock indicator */
      do {
        input = input << 1;
        cnt++;
      } while ((input & 0x80000000) == 0);

      output = (uint8_t)((input & 0x70000000)>>23)+(31 - cnt%32);
      return(output);
    }
}
#endif

/* convert float8 to uint32_t */
uint32_t blackhawk7_l2p2_INTERNAL_float8_to_uint32(float8_t input) {
    uint32_t x;
    if(input == 0) return(0);
    x = (uint32_t)((((uint8_t)(input))>>5) + 8);
    if((input & 0x1F) < 3) {
      return(x>>(3-(input & 0x1f)));
    } else if((input & 0x1F) > 3) {
        x=(x<<1)|1;
        return((x<<((input & 0x1F)-3-1)));
    }else {
        return(x<<((input & 0x1F)-3));
    }
}

/* Convert uint8 to 8-bit gray code */
uint8_t blackhawk7_l2p2_INTERNAL_uint8_to_gray(uint8_t input) {
    return input ^ (input >> 1);
}

/* Convert 8-bit gray code to uint8 */
uint8_t blackhawk7_l2p2_INTERNAL_gray_to_uint8(uint8_t input) {
    input = input ^ (input >> 4);
    input = input ^ (input >> 2);
    input = input ^ (input >> 1);
    return input;
}

/* Convert seconds to hr:min:sec */
uint8_t blackhawk7_l2p2_INTERNAL_seconds_to_displayformat(uint32_t seconds, uint8_t *hrs, uint8_t *mins, uint8_t *secs) {
    if(!hrs || !mins || !secs) {
        return (ERR_CODE_BAD_PTR_OR_INVALID_INPUT);
    }
    *hrs    = (uint8_t)(seconds / 3600);
    seconds = (seconds % 3600);
    *mins   = (uint8_t)(seconds / 60);
    *secs   = (uint8_t)(seconds % 60);
    return(ERR_CODE_NONE);
}

/* convert float12 to uint32 */
uint32_t blackhawk7_l2p2_INTERNAL_float12_to_uint32(uint8_t input, uint8_t multi) {

    return(((uint32_t)input)<<multi);
}

#endif /* !SMALL_FOOTPRINT */

#if !defined(SMALL_FOOTPRINT) 
err_code_t blackhawk7_l2p2_INTERNAL_set_rx_pf_main(srds_access_t *sa__, uint8_t val) {
    INIT_SRDS_ERR_CODE
    uint8_t pf_max;
    BLACKHAWK7_L2P2_UAPI_INIT_AMS_B0         /* if BLACKHAWK7_V2LXP2 || BLACKHAWK7_V3LXP2 */
    pf_max = PF_MAX_VALUE_B0;
    BLACKHAWK7_L2P2_UAPI_ELSE_AMS_A0   /* else if BLACKHAWK7_V1LXP2 */
    pf_max = PF_MAX_VALUE;
    BLACKHAWK7_L2P2_UAPI_ELSE_ERR
    if (val > pf_max) {
       return (blackhawk7_l2p2_error(sa__, ERR_CODE_PF_INVALID));
    }
    EFUN(WR_RX_PF_CTRL(val));
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_set_rx_pf2(srds_access_t *sa__, uint8_t val) {
    INIT_SRDS_ERR_CODE
    if (val > 15) {
      return (blackhawk7_l2p2_error(sa__, ERR_CODE_PF_INVALID));
    }

    EFUN(wr_sync_master_afe_signals(1));
    if (val < 8) {
      EFUN(WR_RX_PF2_CTRL(val));
      EFUN(wr_ams_rx_pflo_ctrl_msb(0));
    }
    else {
      EFUN(WR_RX_PF2_CTRL((uint8_t)(15-val)));
      EFUN(wr_ams_rx_pflo_ctrl_msb(1));
    }
    EFUN(wr_ana_timer_t2(1));
    EFUN(wr_sync_master_afe_signals(0));
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_set_rx_pf3(srds_access_t *sa__, uint8_t val) {
    INIT_SRDS_ERR_CODE
    uint8_t pf3_max;
    BLACKHAWK7_L2P2_UAPI_INIT_AMS_B0         /* if BLACKHAWK7_V2LXP2 || BLACKHAWK7_V3LXP2 */
    pf3_max = PF3_MAX_VALUE_B0;
    BLACKHAWK7_L2P2_UAPI_ELSE_AMS_A0   /* else if BLACKHAWK7_V1LXP2 */
    pf3_max = PF3_MAX_VALUE;
    BLACKHAWK7_L2P2_UAPI_ELSE_ERR
    if(val > pf3_max) {
      return (blackhawk7_l2p2_error(sa__, ERR_CODE_PF_INVALID));
    }

    BLACKHAWK7_L2P2_UAPI_INIT_AMS_B0         /* if BLACKHAWK7_V2LXP2 || BLACKHAWK7_V3LXP2 */
    if (val > PF3_MAX_VALUE) {
        EFUN(wr_ams_rx_eq2_ctrl4(1));
        EFUN(WR_RX_PF3_CTRL((uint8_t)(PF3_MAX_VALUE_B0 - val)));  /* To account for MSB not gray coded */
    }
    else {
        EFUN(wr_ams_rx_eq2_ctrl4(0));
        EFUN(WR_RX_PF3_CTRL(val));
    }
    BLACKHAWK7_L2P2_UAPI_ELSE_AMS_A0   /* else if BLACKHAWK7_V1LXP2 */
    EFUN(WR_RX_PF3_CTRL(val));
    BLACKHAWK7_L2P2_UAPI_ELSE_ERR
    return(ERR_CODE_NONE);
}
#endif /* !SMALL_FOOTPRINT */

#ifndef SMALL_FOOTPRINT
err_code_t blackhawk7_l2p2_INTERNAL_get_rx_pf_main(srds_access_t *sa__, uint8_t *val) {
    INIT_SRDS_ERR_CODE
    ESTM(*val = RD_RX_PF_CTRL());
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_rx_pf2(srds_access_t *sa__, uint8_t *val) {
    INIT_SRDS_ERR_CODE
    ESTM(*val = RD_RX_PF2_CTRL());
    {
      uint8_t rddata;
      ESTM(rddata = rd_ams_rx_pflo_ctrl_msb());
      if (rddata==1) {
        *val = (uint8_t)(15 - *val);
      }
    }
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_rx_pf3(srds_access_t *sa__, uint8_t *val) {
    INIT_SRDS_ERR_CODE
    ESTM(*val = RD_RX_PF3_CTRL());
    BLACKHAWK7_L2P2_UAPI_INIT_AMS_B0         /* if !BLACKHAWK7_V1LXP2 */
    {
        uint8_t pf3_msb;
        ESTM(pf3_msb = rd_ams_rx_eq2_ctrl4());
        if (pf3_msb) {
            *val = (uint8_t)(PF3_MAX_VALUE_B0 - *val);  /* To account for MSB not gray coded */
        }
    }
    BLACKHAWK7_L2P2_UAPI_NOT_AMS_A0_ERR  /* if not BLACKHAWK7_V1LXP2, print error */
    return (ERR_CODE_NONE);
}

#endif /* !SMALL_FOOTPRINT */

#if !defined(SMALL_FOOTPRINT) 
err_code_t blackhawk7_l2p2_INTERNAL_set_rx_vga(srds_access_t *sa__, uint8_t val) {
    INIT_SRDS_ERR_CODE

    EFUN(blackhawk7_l2p2_INTERNAL_check_uc_lane_stopped(sa__));  /* make sure uC is stopped to avoid race conditions */

    if (val > RX_VGA_CTRL_VAL_MAX) {
      return (blackhawk7_l2p2_error(sa__, ERR_CODE_VGA_INVALID));
    }
#if defined(RX_VGA_CTRL_VAL_MIN) && (RX_VGA_CTRL_VAL_MIN > 0)
    if (val < RX_VGA_CTRL_VAL_MIN) {
      return (blackhawk7_l2p2_error(sa__, ERR_CODE_VGA_INVALID));
    }
#endif

    EFUN(wr_rx_vga_val(val));
    return(ERR_CODE_NONE);
}



#endif /* !SMALL_FOOTPRINT */

#ifndef SMALL_FOOTPRINT
err_code_t blackhawk7_l2p2_INTERNAL_get_rx_vga(srds_access_t *sa__, uint8_t *val) {
    INIT_SRDS_ERR_CODE
    ESTM(*val = rd_rx_vga_status());
    return (ERR_CODE_NONE);
}

#endif /* !SMALL_FOOTPRINT */

#if !defined(SMALL_FOOTPRINT) 
err_code_t blackhawk7_l2p2_INTERNAL_set_rx_dfe1(srds_access_t *sa__, int8_t val) {
    INIT_SRDS_ERR_CODE
    enum blackhawk7_l2p2_rx_pam_mode_enum pam_mode = NRZ;
    EFUN(blackhawk7_l2p2_INTERNAL_get_rx_pam_mode(sa__, &pam_mode));

    if(pam_mode != NRZ) {
        EFUN_PRINTF(("ERROR: RX DFE1 is only available in NRZ mode\n"));
        return(ERR_CODE_INVALID_RX_PAM_MODE);
    }
    EFUN(blackhawk7_l2p2_INTERNAL_check_uc_lane_stopped(sa__));  /* make sure uC is stopped to avoid race conditions */

    EFUN(wr_rx_afe_override_sel(1));                     /* Select data23 slicer */
    EFUN(wr_rx_afe_override_val((uint8_t)val));
    EFUN(wr_rx_afe_override_write(1));
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_set_rx_dfe2(srds_access_t *sa__, int8_t val) {
    INIT_SRDS_ERR_CODE
    if ((val > 31) || (val < -31)) {
        USR_PRINTF(("Exceeded range of DFE tap limit = 31, request %d\n",val));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_DFE_TAP));
    }
    EFUN(wr_rxa_dfe_tap2_val((uint8_t)val));
    EFUN(wr_rxa_dfe_tap2_write(1));
    EFUN(wr_rxb_dfe_tap2_val((uint8_t)val));
    EFUN(wr_rxb_dfe_tap2_write(1));
    EFUN(wr_rxa_dfe_tap2_h_val((uint8_t)val));
    EFUN(wr_rxa_dfe_tap2_h_write(1));
    EFUN(wr_rxb_dfe_tap2_h_val((uint8_t)val));
    EFUN(wr_rxb_dfe_tap2_h_write(1));
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_set_rx_dfe3(srds_access_t *sa__, int8_t val) {
    INIT_SRDS_ERR_CODE
    if ((val > 15) || (val < -15)) {
        USR_PRINTF(("Exceeded range of DFE tap limit = 15, request %d\n",val));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_DFE_TAP));
    }
    EFUN(wr_rxa_dfe_tap3_val((uint8_t)val));
    EFUN(wr_rxa_dfe_tap3_write(1));
    EFUN(wr_rxb_dfe_tap3_val((uint8_t)val));
    EFUN(wr_rxb_dfe_tap3_write(1));
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_set_rx_dfe4(srds_access_t *sa__, int8_t val) {
    INIT_SRDS_ERR_CODE
    if ((val > 15) || (val < -15)) {
        USR_PRINTF(("Exceeded range of DFE tap limit = 15, request %d\n",val));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_DFE_TAP));
    }
    EFUN(wr_rxa_dfe_tap4_val((uint8_t)val));
    EFUN(wr_rxa_dfe_tap4_write(1));
    EFUN(wr_rxb_dfe_tap4_val((uint8_t)val));
    EFUN(wr_rxb_dfe_tap4_write(1));
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_set_rx_dfe5(srds_access_t *sa__, int8_t val) {
    INIT_SRDS_ERR_CODE
    if ((val > 7) || (val < -7)) {
        USR_PRINTF(("Exceeded range of DFE tap limit = 7, request %d\n",val));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_DFE_TAP));
    }
    val = blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(val);
    EFUN(wr_rxa_dfe_tap5((uint8_t)val));
    EFUN(wr_rxb_dfe_tap5((uint8_t)val));
    return(ERR_CODE_NONE);
}


err_code_t blackhawk7_l2p2_INTERNAL_set_rx_dfe6(srds_access_t *sa__, int8_t val) {
    INIT_SRDS_ERR_CODE
    if ((val > 7) || (val < -7)) {
        USR_PRINTF(("Exceeded range of DFE tap limit = 7, request %d\n",val));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_DFE_TAP));
    }
    val = blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(val);
    EFUN(wr_rxa_dfe_tap6((uint8_t)val));
    EFUN(wr_rxb_dfe_tap6((uint8_t)val));
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_set_rx_dfe7(srds_access_t *sa__, int8_t val) {
    INIT_SRDS_ERR_CODE
    if ((val > 7) || (val < -7)) {
        USR_PRINTF(("Exceeded range of DFE tap limit = 7, request %d\n",val));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_DFE_TAP));
    }
    val = blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(val);
    EFUN(wr_rxa_dfe_tap7((uint8_t)val));
    EFUN(wr_rxb_dfe_tap7((uint8_t)val));
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_set_rx_dfe8(srds_access_t *sa__, int8_t val) {
    INIT_SRDS_ERR_CODE
    if ((val > 7) || (val < -7)) {
        USR_PRINTF(("Exceeded range of DFE tap limit = 7, request %d\n",val));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_DFE_TAP));
    }
    val = blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(val);
    EFUN(wr_rxa_dfe_tap8((uint8_t)val));
    EFUN(wr_rxb_dfe_tap8((uint8_t)val));
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_set_rx_dfe9(srds_access_t *sa__, int8_t val) {
    INIT_SRDS_ERR_CODE
    if ((val > 7) || (val < -7)) {
        USR_PRINTF(("Exceeded range of DFE tap limit = 7, request %d\n",val));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_DFE_TAP));
    }
    val = blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(val);
    EFUN(wr_rxa_dfe_tap9((uint8_t)val));
    EFUN(wr_rxb_dfe_tap9((uint8_t)val));
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_set_rx_dfe10(srds_access_t *sa__, int8_t val) {
    INIT_SRDS_ERR_CODE
    if ((val > 7) || (val < -7)) {
        USR_PRINTF(("Exceeded range of DFE tap limit = 7, request %d\n",val));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_DFE_TAP));
    }
    val = blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(val);
    EFUN(wr_rxa_dfe_tap10((uint8_t)val));
    EFUN(wr_rxb_dfe_tap10((uint8_t)val));
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_set_rx_dfe11(srds_access_t *sa__, int8_t val) {
    INIT_SRDS_ERR_CODE
    if ((val > 7) || (val < -7)) {
        USR_PRINTF(("Exceeded range of DFE tap limit = 7, request %d\n",val));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_DFE_TAP));
    }
    val = blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(val);
    EFUN(wr_rxa_dfe_tap11((uint8_t)val));
    EFUN(wr_rxb_dfe_tap11((uint8_t)val));
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_set_rx_dfe12(srds_access_t *sa__, int8_t val) {
    INIT_SRDS_ERR_CODE
    if ((val > 7) || (val < -7)) {
        USR_PRINTF(("Exceeded range of DFE tap limit = 7, request %d\n",val));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_DFE_TAP));
    }
    val = blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(val);
    EFUN(wr_rxa_dfe_tap12((uint8_t)val));
    EFUN(wr_rxb_dfe_tap12((uint8_t)val));
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_set_rx_dfe13(srds_access_t *sa__, int8_t val) {
    INIT_SRDS_ERR_CODE
    if ((val > 7) || (val < -7)) {
        USR_PRINTF(("Exceeded range of DFE tap limit = 7, request %d\n",val));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_DFE_TAP));
    }
    val = blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(val);
    EFUN(wr_rxa_dfe_tap13((uint8_t)val));
    EFUN(wr_rxb_dfe_tap13((uint8_t)val));
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_set_rx_dfe14(srds_access_t *sa__, int8_t val) {
    INIT_SRDS_ERR_CODE
    if ((val > 7) || (val < -7)) {
        USR_PRINTF(("Exceeded range of DFE tap limit = 7, request %d\n",val));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_DFE_TAP));
    }
    val = blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(val);
    EFUN(wr_rxa_dfe_tap14((uint8_t)val));
    EFUN(wr_rxb_dfe_tap14((uint8_t)val));
    return(ERR_CODE_NONE);
}

#endif /* !SMALL_FOOTPRINT */

#ifndef SMALL_FOOTPRINT
err_code_t blackhawk7_l2p2_INTERNAL_get_rx_dfe1(srds_access_t *sa__, int8_t *val) {
    INIT_SRDS_ERR_CODE
    {
        enum blackhawk7_l2p2_rx_pam_mode_enum pam_mode = NRZ;
        EFUN(blackhawk7_l2p2_INTERNAL_get_rx_pam_mode(sa__, &pam_mode));

        if(pam_mode != NRZ) {
            EFUN_PRINTF(("ERROR: RX DFE1 is only available in NRZ mode (core %d lane %d)\n",blackhawk7_l2p2_acc_get_core(sa__),blackhawk7_l2p2_acc_get_lane(sa__)));
            return(ERR_CODE_INVALID_RX_PAM_MODE);
        }
    }
    ESTM(*val = (int8_t)rd_rx_data23_status());
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_rx_dfe2(srds_access_t *sa__, int8_t *val) {
    INIT_SRDS_ERR_CODE
    int8_t temp = 0;
    ESTM(temp = (int8_t)(temp + rd_rxa_dfe_tap2_status()));
    ESTM(temp = (int8_t)(temp + rd_rxb_dfe_tap2_status()));
    *val = (int8_t)(temp >> 1);
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_rx_dfe3(srds_access_t *sa__, int8_t *val) {
    INIT_SRDS_ERR_CODE
    int8_t temp = 0;
    ESTM(temp = (int8_t)(temp + rd_rxa_dfe_tap3_status()));
    ESTM(temp = (int8_t)(temp + rd_rxb_dfe_tap3_status()));
    *val = (int8_t)(temp >> 1);
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_rx_dfe4(srds_access_t *sa__, int8_t *val) {
    INIT_SRDS_ERR_CODE
    int8_t temp = 0;
    ESTM(temp = (int8_t)(temp + rd_rxa_dfe_tap4_status()));
    ESTM(temp = (int8_t)(temp + rd_rxb_dfe_tap4_status()));
    *val = (int8_t)(temp >> 1);
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_rx_dfe5(srds_access_t *sa__, int8_t *val) {
    INIT_SRDS_ERR_CODE
    int8_t temp = 0;
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxa_dfe_tap5())));
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxb_dfe_tap5())));
    *val = (int8_t)(temp >> 1);
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_rx_dfe6(srds_access_t *sa__, int8_t *val) {
    INIT_SRDS_ERR_CODE
    int8_t temp = 0;
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxa_dfe_tap6())));
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxb_dfe_tap6())));
    *val = (int8_t)(temp >> 1);
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_rx_dfe7(srds_access_t *sa__, int8_t *val) {
    INIT_SRDS_ERR_CODE
    int8_t temp = 0;
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxa_dfe_tap7())));
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxb_dfe_tap7())));
    *val = (int8_t)(temp >> 1);
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_rx_dfe8(srds_access_t *sa__, int8_t *val) {
    INIT_SRDS_ERR_CODE
    int8_t temp = 0;
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxa_dfe_tap8())));
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxb_dfe_tap8())));
    *val = (int8_t)(temp >> 1);
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_rx_dfe9(srds_access_t *sa__, int8_t *val) {
    INIT_SRDS_ERR_CODE
    int8_t temp = 0;
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxa_dfe_tap9())));
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxb_dfe_tap9())));
    *val = (int8_t)(temp >> 1);
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_rx_dfe10(srds_access_t *sa__, int8_t *val) {
    INIT_SRDS_ERR_CODE
    int8_t temp = 0;
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxa_dfe_tap10())));
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxb_dfe_tap10())));
    *val = (int8_t)(temp >> 1);
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_rx_dfe11(srds_access_t *sa__, int8_t *val) {
    INIT_SRDS_ERR_CODE
    int8_t temp = 0;
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxa_dfe_tap11())));
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxb_dfe_tap11())));
    *val = (int8_t)(temp >> 1);
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_rx_dfe12(srds_access_t *sa__, int8_t *val) {
    INIT_SRDS_ERR_CODE
    int8_t temp = 0;
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxa_dfe_tap12())));
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxb_dfe_tap12())));
    *val = (int8_t)(temp >> 1);
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_rx_dfe13(srds_access_t *sa__, int8_t *val) {
    INIT_SRDS_ERR_CODE
    int8_t temp = 0;
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxa_dfe_tap13())));
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxb_dfe_tap13())));
    *val = (int8_t)(temp >> 1);
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_rx_dfe14(srds_access_t *sa__, int8_t *val) {
    INIT_SRDS_ERR_CODE
    int8_t temp = 0;
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxa_dfe_tap14())));
    ESTM(temp = (int8_t)(temp + blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(rd_rxb_dfe_tap14())));
    *val = (int8_t)(temp >> 1);
    return (ERR_CODE_NONE);
}


err_code_t blackhawk7_l2p2_INTERNAL_get_bwr(srds_access_t *sa__, uint8_t *vga1_bwr, uint8_t *vga2_bwr, uint8_t *eq1_bwr, uint8_t *eq2_bwr) {
    INIT_SRDS_ERR_CODE
  uint8_t reg1 = 0, reg2 = 0;
  ESTM(reg1 = rd_ams_rx_eq2_deq2());
  ESTM(reg2 = rd_ams_rx_eq1_deq());
  *eq1_bwr = (uint8_t)((reg1 << 2) | reg2);
  ESTM(reg1 = rd_ams_rx_eq1_deq2());
  ESTM(reg2 = rd_ams_rx_eq2_deq());
  *eq2_bwr = (uint8_t)((reg1 << 2) | reg2);
  ESTM(*vga1_bwr = rd_ams_rx_vga1_deq());
  ESTM(*vga2_bwr = rd_ams_rx_vga2_deq());
  ESTM(reg1 = rd_ams_rx_eq1_deq3());
  ESTM(reg2 = rd_ams_rx_eq2_deq3());
  *eq1_bwr = (uint8_t)((reg1 << 3) | *eq1_bwr);           /* EQ1={eq1_deq3,eq1_deq<2:0>} */
  *eq2_bwr = (uint8_t)((reg2 << 3) | *eq2_bwr);           /* EQ2={eq2_deq3,eq2_deq<2:0>} */
  ESTM(reg1 = rd_ams_rx_vga_dis_ind());
  *vga1_bwr = (uint8_t)(((reg1 & 0x1) << 2) | *vga1_bwr); /* VGA1={vga_dis_ind<0>,vga1_deq<1:0>} */
  *vga2_bwr = (uint8_t)(((reg1 & 0x2) << 1) | *vga2_bwr); /* VGA2={vga_dis_ind<1>,vga2_deq<1:0>} */
  *eq1_bwr  = blackhawk7_l2p2_INTERNAL_gray_to_uint8(*eq1_bwr);
  *eq2_bwr  = blackhawk7_l2p2_INTERNAL_gray_to_uint8(*eq2_bwr);
  *vga1_bwr = blackhawk7_l2p2_INTERNAL_gray_to_uint8(*vga1_bwr);
  *vga2_bwr = blackhawk7_l2p2_INTERNAL_gray_to_uint8(*vga2_bwr);
  return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_set_bwr(srds_access_t *sa__, uint8_t vga1_bwr, uint8_t vga2_bwr, uint8_t eq1_bwr, uint8_t eq2_bwr, uint8_t vga_dis_ind) {
  INIT_SRDS_ERR_CODE
  eq1_bwr  = blackhawk7_l2p2_INTERNAL_uint8_to_gray(eq1_bwr);
  eq2_bwr  = blackhawk7_l2p2_INTERNAL_uint8_to_gray(eq2_bwr);
  vga1_bwr = blackhawk7_l2p2_INTERNAL_uint8_to_gray(vga1_bwr);
  vga2_bwr = blackhawk7_l2p2_INTERNAL_uint8_to_gray(vga2_bwr);

  EFUN(wr_sync_master_afe_signals(1));
  UNUSED(vga_dis_ind);
  EFUN(wr_ams_rx_vga1_deq(vga1_bwr & 0x03));
  EFUN(wr_ams_rx_vga2_deq(vga2_bwr & 0x03));
  {
    uint8_t ams_rx_vga_dis_ind = 0;
    ESTM(ams_rx_vga_dis_ind = rd_ams_rx_vga_dis_ind());
    EFUN(wr_ams_rx_vga_dis_ind((uint8_t)((ams_rx_vga_dis_ind & 0xFC) | ((vga1_bwr&0x04)>>2) | ((vga2_bwr&0x04)>>1))));
  }
  EFUN(wr_ams_rx_eq2_deq3 ((uint8_t)((eq2_bwr & 0x08) >> 3)));
  EFUN(wr_ams_rx_eq1_deq2 ((uint8_t)((eq2_bwr & 0x04) >> 2)));
  EFUN(wr_ams_rx_eq2_deq  (        eq2_bwr & 0x3));
  EFUN(wr_ams_rx_eq1_deq3 ((uint8_t)((eq1_bwr & 0x08) >> 3)));
  EFUN(wr_ams_rx_eq2_deq2((uint8_t)((eq1_bwr & 0x04) >> 2)));
  EFUN(wr_ams_rx_eq1_deq  (       eq1_bwr & 0x03));

  EFUN(wr_ana_timer_t2(1));
  EFUN(wr_sync_master_afe_signals(0));

  return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_eye_scan_setup(srds_access_t *sa__, uint8_t intr_pass_b, int16_t *y_max, int16_t *y_step, uint16_t *usr_diag_status) {
    INIT_SRDS_ERR_CODE
    enum blackhawk7_l2p2_rx_pam_mode_enum pam_mode = NRZ;
    uint8_t dig_lpbk_en;
    int16_t val_max,val_step;

    /* init value */
    *usr_diag_status = 0;

    ESTM(dig_lpbk_en = rd_dig_lpbk_en());
    if(dig_lpbk_en) {
        EFUN_PRINTF(("Eye scan is not supported while digital loopback is enabled.\n"));
        return (ERR_CODE_INVALID_DIG_LPBK_STATE);
    }
    val_max  = EYE_SCAN_NRZ_VERTICAL_IDX_MAX;
    val_step = EYE_SCAN_NRZ_VERTICAL_STEP;
    EFUN(blackhawk7_l2p2_INTERNAL_get_rx_pam_mode(sa__, &pam_mode));
    if((pam_mode == PAM4_NR)||(pam_mode == PAM4_ER)) {
        val_max  = EYE_SCAN_PAM_VERTICAL_IDX_MAX;
        val_step = EYE_SCAN_PAM_VERTICAL_STEP;
    }
    EFUN_PRINTF(("\n\n****  SERDES %sEYE SCAN CORE %d LANE %d   ****\n", intr_pass_b?"INTRUSIVE ":"",blackhawk7_l2p2_acc_get_core(sa__),blackhawk7_l2p2_acc_get_lane(sa__)));

    /* start horizontal acquisition */
    {
        uint8_t direction = EYE_SCAN_HORIZ;
        err_code_t err_code;

        if(intr_pass_b) {
            EFUN_PRINTF(("ERROR: Intrusive eye scan mode is not supported in this IP\n"));
            return ERR_CODE_BAD_PTR_OR_INVALID_INPUT;
        }

        err_code = blackhawk7_l2p2_meas_eye_scan_start(sa__, direction);

        if (err_code) {
            if (err_code == ERR_CODE_DIAG_SCAN_NO_PMD_LOCK) {
                return err_code;
            }
            else {
                EFUN(blackhawk7_l2p2_meas_eye_scan_done(sa__));
            }
        }
    }

    {
        uint8_t rx_tuning_done=0;
        EFUN(blackhawk7_l2p2_get_rx_tuning_status(sa__, &rx_tuning_done));
        if((pam_mode != NRZ) && (!rx_tuning_done)) {
            EFUN_PRINTF(("2-D eye scan is not ready yet, wait for RX tuning status to be set\n"));
            EFUN(blackhawk7_l2p2_meas_eye_scan_done(sa__));
            return ERR_CODE_RX_TUNING_NOT_DONE;
        }
    }

    ESTM(*usr_diag_status = rdv_usr_diag_status());
    if((pam_mode != NRZ) && ((*usr_diag_status & DIAG_EYE_SCAN_V_RANGE_MASK) == DIAG_EYE_SCAN_V_HALF)) {
        val_max  = EYE_SCAN_PAM_VERTICAL_IDX_MAX>>1;
        val_step = EYE_SCAN_PAM_VERTICAL_STEP>>1;
    }


    *y_max = val_max;
    *y_step = val_step;

    return ERR_CODE_NONE;
}
#endif /* SMALL_FOOTPRINT */

err_code_t blackhawk7_l2p2_INTERNAL_load_txfir_taps(srds_access_t *sa__){
    INIT_SRDS_ERR_CODE
  EFUN(wr_txfir_tap_load(1));  /* Load the tap coefficients into TXFIR. */
  return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_set_tx_tap(srds_access_t *sa__, uint8_t tap_num, int16_t val) {
    INIT_SRDS_ERR_CODE

    switch (tap_num) {
    case  0: EFUN(wr_txfir_tap0_coeff ((uint16_t)val)); break;
    case  1: EFUN(wr_txfir_tap1_coeff ((uint16_t)val)); break;
    case  2: EFUN(wr_txfir_tap2_coeff ((uint16_t)val)); break;
    case  3: EFUN(wr_txfir_tap3_coeff ((uint16_t)val)); break;
    case  4: EFUN(wr_txfir_tap4_coeff ((uint16_t)val)); break;
    case  5: EFUN(wr_txfir_tap5_coeff ((uint16_t)val)); break;
    default:
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_BAD_PTR_OR_INVALID_INPUT));
    }

    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_tx_tap(srds_access_t *sa__, uint8_t tap_num, int16_t *val) {
    INIT_SRDS_ERR_CODE

    switch (tap_num) {
    case  0: ESTM(*val = rd_txfir_tap0_coeff ()); break;
    case  1: ESTM(*val = rd_txfir_tap1_coeff ()); break;
    case  2: ESTM(*val = rd_txfir_tap2_coeff ()); break;
    case  3: ESTM(*val = rd_txfir_tap3_coeff ()); break;
    case  4: ESTM(*val = rd_txfir_tap4_coeff ()); break;
    case  5: ESTM(*val = rd_txfir_tap5_coeff ()); break;
    default:
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_BAD_PTR_OR_INVALID_INPUT));
    }

    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_validate_full_txfir_cfg(srds_access_t *sa__, enum blackhawk7_l2p2_txfir_tap_enable_enum enable_taps, blackhawk7_l2p2_txfir_st *txfir) {
    uint8_t tap_num;
    err_code_t err_code = ERR_CODE_NONE;
    uint16_t abs_total = 0;
    uint8_t  in_nrz_range;
    UNUSED(sa__);

    if (txfir == NULL) {
        return (ERR_CODE_BAD_PTR_OR_INVALID_INPUT);
    }

    in_nrz_range = ((enable_taps == BLACKHAWK7_L2P2_NRZ_LP_3TAP) || (enable_taps == BLACKHAWK7_L2P2_NRZ_6TAP)) ? 1 : 0;
    if ((enable_taps == BLACKHAWK7_L2P2_NRZ_6TAP) || (enable_taps == BLACKHAWK7_L2P2_PAM4_6TAP)) {
        tap_num=TXFIR_ST_NUM_TAPS;
    }
    else {
        tap_num=3;
    }
    for (; tap_num< TXFIR_ST_NUM_TAPS; tap_num++) {
        if (txfir->tap[tap_num]) {
            /* txfir should be memset to zero and so this check catches bad accesses */
            EFUN_PRINTF(("ERROR: unused taps cannot be non zero values\n"));
            return(blackhawk7_l2p2_error(sa__, ERR_CODE_BAD_PTR_OR_INVALID_INPUT));
        }
    }
    for (tap_num=0; tap_num<TXFIR_ST_NUM_TAPS; tap_num++) {
        if (((!in_nrz_range) && ((txfir->tap[tap_num] < TXFIR_PAM4_SW_TAP_MIN) || (txfir->tap[tap_num] > TXFIR_PAM4_SW_TAP_MAX))) ||
            ((in_nrz_range)  && ((txfir->tap[tap_num] <     TXFIR_NRZ_TAP_MIN) || (txfir->tap[tap_num] >     TXFIR_NRZ_TAP_MAX)))) {
            EFUN_PRINTF(("ERROR: TXFIR main tap invalid\n"));
            err_code |= ERR_CODE_TXFIR_MAIN_INVALID;
        }
        abs_total = (uint16_t)(abs_total + SRDS_ABS(txfir->tap[tap_num]));
    }
    if (abs_total > (in_nrz_range ? TXFIR_NRZ_SUM_LIMIT: TXFIR_PAM4_SW_SUM_LIMIT)) {
        EFUN_PRINTF(("ERROR: TXFIR sum limit failed %d\n",abs_total));
        err_code |= ERR_CODE_TXFIR_SUM_LIMIT;
    }
    return (blackhawk7_l2p2_error(sa__, err_code));
}

err_code_t blackhawk7_l2p2_INTERNAL_apply_full_txfir_cfg(srds_access_t *sa__, enum blackhawk7_l2p2_txfir_tap_enable_enum enable_taps, blackhawk7_l2p2_txfir_st *txfir) {
    INIT_SRDS_ERR_CODE
    uint8_t tap_num;

    if (txfir == NULL) {
        return (ERR_CODE_BAD_PTR_OR_INVALID_INPUT);
    }

    EFUN(wr_txfir_nrz_tap_range_sel(((enable_taps == BLACKHAWK7_L2P2_NRZ_LP_3TAP) || (enable_taps == BLACKHAWK7_L2P2_NRZ_6TAP)) ? 1 : 0));
    for (tap_num=0; tap_num<TXFIR_ST_NUM_TAPS; tap_num++) {
        EFUN(blackhawk7_l2p2_INTERNAL_set_tx_tap(sa__, tap_num, txfir->tap[tap_num]));
    }
    if ((enable_taps == BLACKHAWK7_L2P2_NRZ_6TAP) || (enable_taps == BLACKHAWK7_L2P2_PAM4_6TAP)) {
        EFUN(wr_txfir_tap_en(1));
    }
    else {
        EFUN(wr_txfir_tap_en(0));
    }
    EFUN(blackhawk7_l2p2_INTERNAL_load_txfir_taps(sa__));
    return (ERR_CODE_NONE);
}




err_code_t blackhawk7_l2p2_INTERNAL_core_clkgate(srds_access_t *sa__, uint8_t enable) {
    UNUSED(sa__);
    UNUSED(enable);
    return (ERR_CODE_NONE);
}
#ifndef SMALL_FOOTPRINT
err_code_t blackhawk7_l2p2_INTERNAL_lane_clkgate(srds_access_t *sa__, uint8_t enable) {
    INIT_SRDS_ERR_CODE

  if (enable) {
    /* Use frc/frc_val to force all RX and TX clk_vld signals to 0 */
        EFUN(wr_pmd_rx_clk_vld_frc_val(0x0));
        EFUN(wr_pmd_rx_clk_vld_frc(0x1));
        EFUN(wr_pmd_tx_clk_vld_frc_val(0x0));
        EFUN(wr_pmd_tx_clk_vld_frc(0x1));

    /* Use frc_on to force clkgate */
        EFUN(wr_ln_rx_s_clkgate_frc_on(0x1));

        EFUN(wr_ln_tx_s_clkgate_frc_on(0x1));

  }
  else {
        EFUN(wr_pmd_rx_clk_vld_frc_val(0x0));
        EFUN(wr_pmd_rx_clk_vld_frc(0x0));
        EFUN(wr_pmd_tx_clk_vld_frc_val(0x0));
        EFUN(wr_pmd_tx_clk_vld_frc(0x0));

        EFUN(wr_ln_rx_s_clkgate_frc_on(0x0));

        EFUN(wr_ln_tx_s_clkgate_frc_on(0x0));
  }
  return (ERR_CODE_NONE);
}

/*-----------------------------------------------*/
/*  Get dynamic eye margin estimation values     */
/*-----------------------------------------------*/
err_code_t blackhawk7_l2p2_INTERNAL_get_eye_margin_est(srds_access_t *sa__, uint16_t *left_eye_mUI, uint16_t *right_eye_mUI, uint16_t  *upper_eye_mV, uint16_t *lower_eye_mV) {
  INIT_SRDS_ERR_CODE
  uint8_t ladder_range = 0;
  uint8_t eye_val = 0;
  ESTM(eye_val = rdv_usr_sts_heye_left());
  ESTM(*left_eye_mUI  = blackhawk7_l2p2_INTERNAL_eye_to_mUI(sa__, eye_val));
  ESTM(eye_val = rdv_usr_sts_heye_right());
  ESTM(*right_eye_mUI = blackhawk7_l2p2_INTERNAL_eye_to_mUI(sa__, eye_val));
  ESTM(eye_val = rdv_usr_sts_veye_upper());
  ESTM(*upper_eye_mV = blackhawk7_l2p2_INTERNAL_eye_to_mV(sa__, eye_val, ladder_range));
  ESTM(eye_val = rdv_usr_sts_veye_lower());
  ESTM(*lower_eye_mV = blackhawk7_l2p2_INTERNAL_eye_to_mV(sa__, eye_val, ladder_range));

  return (ERR_CODE_NONE);
}

uint16_t blackhawk7_l2p2_INTERNAL_eye_to_mUI(srds_access_t *sa__, uint8_t var) {
    UNUSED(sa__);
    /* var is in units of 1/512 th UI, so need to multiply by 1000/512 */
    return (uint16_t)(((uint16_t)var)*125/64);
}

uint16_t blackhawk7_l2p2_INTERNAL_eye_to_mV(srds_access_t *sa__, uint8_t var, uint8_t ladder_range) {
    INIT_SRDS_ERR_CODE
    int16_t nlmv_val = 0;
    uint16_t vl = 0;
    afe_override_slicer_sel_t slicer = INVALID_SLICER;
    /* find nearest two vertical levels */
    EFUN(blackhawk7_l2p2_INTERNAL_ladder_setting_to_mV(sa__, (int16_t)var, ladder_range, slicer, &nlmv_val));
    vl = (uint16_t)nlmv_val;
    return (vl);
}


/*----------------------------------------------------*/
/*  Get dynamic eye margin estimation values (PAM)    */
/*----------------------------------------------------*/
err_code_t blackhawk7_l2p2_INTERNAL_get_pam_eye_margin_est(srds_access_t *sa__, blackhawk7_l2p2_eye_margin_t *eye_margin) {
    INIT_SRDS_ERR_CODE
  uint8_t ladder_range = 0;
  uint8_t pam_eye_val = 0;
  uint8_t i;
  for(i=0; i<NUM_PAM_EYES; i++) {
      ESTM(pam_eye_val = rdv_usr_sts_pam_heye_left(i));
      ESTM(eye_margin->left_eye_mUI [i] = blackhawk7_l2p2_INTERNAL_eye_to_mUI(sa__, pam_eye_val));
      ESTM(pam_eye_val = rdv_usr_sts_pam_heye_right(i));
      ESTM(eye_margin->right_eye_mUI[i] = blackhawk7_l2p2_INTERNAL_eye_to_mUI(sa__, pam_eye_val));
      ESTM(pam_eye_val = rdv_usr_sts_pam_veye_upper(i));
      ESTM(eye_margin->upper_eye_mV [i] = blackhawk7_l2p2_INTERNAL_eye_to_mV (sa__, pam_eye_val, ladder_range));
      ESTM(pam_eye_val = rdv_usr_sts_pam_veye_lower(i));
      ESTM(eye_margin->lower_eye_mV [i] = blackhawk7_l2p2_INTERNAL_eye_to_mV (sa__, pam_eye_val, ladder_range));
  }
  return (ERR_CODE_NONE);
}

/*------------------------------------------------------*/
/*  Print dynamic eye margin estimation values (PAM)    */
/*------------------------------------------------------*/
err_code_t blackhawk7_l2p2_display_pam_eye_margin_est(srds_access_t *sa__) {
    INIT_SRDS_ERR_CODE
    uint8_t i;
    blackhawk7_l2p2_eye_margin_t eye_margin = {{0},{0},{0},{0}};
    enum blackhawk7_l2p2_rx_pam_mode_enum pam_mode = NRZ;
    struct blackhawk7_l2p2_usr_ctrl_disable_functions_st dsu, dss;
    uint8_t disable_display=0;

    EFUN(blackhawk7_l2p2_INTERNAL_get_rx_pam_mode(sa__, &pam_mode));
    EFUN(blackhawk7_l2p2_get_usr_ctrl_disable_startup(sa__, &dsu));
    EFUN(blackhawk7_l2p2_get_usr_ctrl_disable_steady_state(sa__, &dss));
    EFUN(blackhawk7_l2p2_INTERNAL_get_pam_eye_margin_est(sa__, &eye_margin));
    disable_display = (pam_mode == NRZ) || (dsu.field.pam_eye_margin_estimation) || (dss.field.pam_eye_margin_estimation);

    EFUN_PRINTF(("Eye margin: L(mUI),R(mUI),U(mV),D(mV)\n"));
    for(i=NUM_PAM_EYES; i>0; i--) {
        EFUN_PRINTF(("%s eye: ", (i-1)==2?"Upper ":(i-1)==1?"Middle":"Lower "));
        if (disable_display) {
            EFUN_PRINTF(("  x   ,  x   ,  x  ,  x  \n"));
        }
        else {
            EFUN_PRINTF(("%6d,%6d,%5d,%5d\n", eye_margin.left_eye_mUI[i-1], eye_margin.right_eye_mUI[i-1], eye_margin.upper_eye_mV[i-1], eye_margin.lower_eye_mV[i-1]));
        }
    }
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_osr_mode(srds_access_t *sa__, blackhawk7_l2p2_osr_mode_st *imode) {
    INIT_SRDS_ERR_CODE
    blackhawk7_l2p2_osr_mode_st mode;

    ENULL_MEMSET(&mode, 0, sizeof(blackhawk7_l2p2_osr_mode_st));

    if(!imode) {
        return(blackhawk7_l2p2_error(sa__, ERR_CODE_BAD_PTR_OR_INVALID_INPUT));
    }

    ESTM(mode.tx = rd_tx_osr_mode());
    ESTM(mode.rx = rd_rx_osr_mode());
    mode.tx_rx = 255;
    *imode = mode;
    return (ERR_CODE_NONE);
}


/** A simple decoding structure
 *
 */
struct simpleDecoder
{
    int32_t  name;
    uint32_t val;
};

uint32_t blackhawk7_l2p2_osr_mode_enum_to_int_x1000(uint8_t osr_mode) {
    int32_t c;
    struct simpleDecoder dec[] = INIT_OSR_ASSOC_TABLE;

    for(c = 0; c < (int32_t)(sizeof(dec)/sizeof(struct simpleDecoder)); c++)
    {
        if(osr_mode == dec[c].name)
        {
            return(dec[c].val);
        }
    }
    return(1000);

}
const char* blackhawk7_l2p2_INTERNAL_get_osr_str(uint8_t osr_val, uint8_t osr_str_length) {
    const char* e2s_long_osr_mode_enum[14] = {
      "x1   ",
      "x2   ",
      "x4   ",
      "x2.5 ",
      "x21.2",
      "x8   ",
      "ERR  ",
      "ERR  ",
      "x16.5",
      "x16  ",
      "ERR  ",
      "ERR  ",
      "x20.6",
      "x32  "
    };

    const char* e2s_short_osr_mode_enum[14] = {
      "x1",
      "x2",
      "x4",
      "xT",
      "xL",
      "x8",
      "ER",
      "ER",
      "xH",
      "xG",
      "ER",
      "ER",
      "xK",
      "xW"
    };
    switch(osr_str_length) {
        case (GET_OSR_STR_LONG):
            return e2s_long_osr_mode_enum[osr_val];
        case (GET_OSR_STR_SHORT):
            return e2s_short_osr_mode_enum[osr_val];
        default:
            return "ER";
    }
}
#endif /* SMALL_FOOTPRINT */

err_code_t blackhawk7_l2p2_INTERNAL_get_rx_pam_mode(srds_access_t *sa__, enum blackhawk7_l2p2_rx_pam_mode_enum *pmode) {
    INIT_SRDS_ERR_CODE
    uint8_t rx_pam4_mode;
    uint8_t rx_pam4_er_mode;

    ESTM(rx_pam4_mode    = rd_rx_pam4_mode());
    ESTM(rx_pam4_er_mode = rd_rx_pam4_er_mode());

    if (rx_pam4_mode == 0) {
        *pmode = NRZ;
    }
    else if (rx_pam4_mode == 1) {
        *pmode = (rx_pam4_er_mode) ? PAM4_ER : PAM4_NR;
    }
    else {
        return(blackhawk7_l2p2_error(sa__, ERR_CODE_INVALID_RX_PAM_MODE));
    }

  return (ERR_CODE_NONE);
}

#ifndef SMALL_FOOTPRINT

err_code_t blackhawk7_l2p2_INTERNAL_decode_br_os_mode(srds_access_t *sa__, uint8_t *br_pd_en) {
    INIT_SRDS_ERR_CODE

    enum blackhawk7_l2p2_rx_pam_mode_enum pam_mode = NRZ;
    EFUN(blackhawk7_l2p2_INTERNAL_get_rx_pam_mode(sa__, &pam_mode));
    if(pam_mode == NRZ) {
        ESTM(*br_pd_en = rd_br_pd_en());
    } else {
        uint8_t os_pattern_enhanced=0, os_all_edges=0;
        ESTM(os_pattern_enhanced = rd_os_pattern_enhanced());
        ESTM(os_all_edges = rd_os_all_edges());
        *br_pd_en = (uint8_t)(!((!os_pattern_enhanced) & os_all_edges));
    }
    return (ERR_CODE_NONE);
}

#endif /* SMALL_FOOTPRINT */

err_code_t blackhawk7_l2p2_INTERNAL_sigdet_status(srds_access_t *sa__, uint8_t *sig_det, uint8_t *sig_det_chg) {
    INIT_SRDS_ERR_CODE
    uint16_t rddata;

    ESTM(rddata = reg_rd_SIGDET_SDSTATUS_0());
    *sig_det = ex_SIGDET_SDSTATUS_0__signal_detect(rddata);
    *sig_det_chg = (uint8_t)(ex_SIGDET_SDSTATUS_0__signal_detect_change(rddata));
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_pll_lock_status(srds_access_t *sa__, uint8_t *pll_lock, uint8_t *pll_lock_chg) {
    INIT_SRDS_ERR_CODE
    uint16_t rddata;
    uint8_t pll_fail;
    ESTM(rddata = reg_rdc_PLL_CAL_COM_STS_0());
    *pll_lock = (uint8_t)(exc_PLL_CAL_COM_STS_0__pll_lock(rddata));
    pll_fail = (uint8_t)(exc_PLL_CAL_COM_STS_0__pll_fail_stky(rddata));
    *pll_lock_chg = (uint8_t)((*pll_lock ^ !exc_PLL_CAL_COM_STS_0__pll_lock_bar_stky(rddata)) | (*pll_lock ^ !pll_fail));
    return(ERR_CODE_NONE);
}

#ifndef SMALL_FOOTPRINT
err_code_t blackhawk7_l2p2_INTERNAL_pmd_lock_status(srds_access_t *sa__, uint8_t *pmd_lock, uint8_t *pmd_lock_chg) {
    INIT_SRDS_ERR_CODE
    uint16_t rddata;
    ESTM(rddata = reg_rd_TLB_RX_DBG_PMD_RX_LOCK_STATUS());
    *pmd_lock = ex_TLB_RX_DBG_PMD_RX_LOCK_STATUS__dbg_pmd_rx_lock(rddata);
    *pmd_lock_chg = (uint8_t)(ex_TLB_RX_DBG_PMD_RX_LOCK_STATUS__dbg_pmd_rx_lock_change(rddata));
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_tx_ppm(srds_access_t *sa__, int16_t *tx_ppm) {
    INIT_SRDS_ERR_CODE
    /* tx_ppm = register/10.486                     */
    /* 3125/32768 = 1/10.486                        */
    /* tx_ppm = register*3125/32768                 */
    /* Suppose you want x/N, but with rounding then */
    /* tx_ppm rounded = (x+N/2)/N;                  */

    ESTM(*tx_ppm = (int16_t)(((rd_tx_pi_integ2_reg() * 3125) + (32768 / 2)) / 32768));
    return ERR_CODE_NONE;
}


err_code_t blackhawk7_l2p2_INTERNAL_read_lane_state(srds_access_t *sa__, blackhawk7_l2p2_lane_state_st_t *istate) {
   INIT_SRDS_ERR_CODE

    if(!istate) {
      return(blackhawk7_l2p2_error(sa__, ERR_CODE_BAD_PTR_OR_INVALID_INPUT));
    }

    EFUN(blackhawk7_l2p2_INTERNAL_pmd_lock_status(sa__,&istate->pmd_lock, &istate->pmd_lock_chg));
    EFUN(blackhawk7_l2p2_INTERNAL_get_stop_state_lane_state(sa__, istate)); /* Dependency on istate->pmd_lock. Updates istate->stop_state AND stop micro as well */
    istate->laneid = blackhawk7_l2p2_acc_get_lane(sa__);
    EFUN(blackhawk7_l2p2_get_rx_tuning_status(sa__, &istate->rx_tuning_done));

    EFUN(blackhawk7_l2p2_INTERNAL_get_osr_mode(sa__, &istate->osr_mode));
    EFUN(blackhawk7_l2p2_INTERNAL_get_osr_str_lane_state(sa__, istate)); /* Dependency on istate->osr_mode */
    EFUN(blackhawk7_l2p2_INTERNAL_get_uc_cfg_lane_state(sa__, istate));
    ESTM(istate->UC_STS = rdv_status_byte());
    ESTM(istate->UC_STS_EXT = rdv_ext_status_word());
    EFUN(blackhawk7_l2p2_INTERNAL_get_rx_pam_mode_lane_state(sa__, istate));
    ESTM(istate->tx_pam_mode = rd_tx_pam4_mode());

    ESTM(istate->rx_rst    = rd_rx_lane_dp_reset_state());
    ESTM(istate->tx_rst    = rd_tx_lane_dp_reset_state());
    ESTM(istate->tx_pll_select = rd_tx_pll_select());
    ESTM(istate->rx_pll_select = rd_rx_pll_select());
    EFUN(blackhawk7_l2p2_INTERNAL_sigdet_status(sa__,&istate->sig_det, &istate->sig_det_chg));
    ESTM(istate->ppm = rd_cdr_integ_reg()/84);
    EFUN(blackhawk7_l2p2_INTERNAL_get_clk_lane_state(sa__, istate));
    EFUN(blackhawk7_l2p2_INTERNAL_decode_br_os_mode(sa__, &istate->CDR));
    EFUN(blackhawk7_l2p2_INTERNAL_get_pf_lane_state(sa__, istate));
    ESTM(istate->bwr_ctrl = rdv_afe_bw_adjust());
    EFUN(blackhawk7_l2p2_read_rx_afe(sa__, RX_AFE_VGA, &istate->VGA));

    ESTM(istate->DCO = rd_dc_offset_bin());

    EFUN(blackhawk7_l2p2_INTERNAL_get_TP0_lane_state(sa__, istate)); /* Dependency on istate->rx_pam_mode */
    ESTM(istate->P1mV = rdv_usr_main_tap_est()/32);
    EFUN(blackhawk7_l2p2_INTERNAL_ladder_setting_to_mV(sa__, istate->P1mV, 0, INVALID_SLICER, &istate->P1mV));

    EFUN(blackhawk7_l2p2_INTERNAL_get_eq_debug1_lane_state(sa__, istate)); /* Dependency on istate->rx_pam_mode */
    EFUN(blackhawk7_l2p2_INTERNAL_get_afe_bw_lane_state(sa__, istate)); /* Dependency on istate->rx_pam_mode */

    ESTM(istate->TP1 = rdv_usr_status_eq_debug3());
    ESTM(istate->blind_ctle_trnsum =  rdv_usr_status_eq_debug14()); /* do this logic that includes logic inside specific uCode for each architecture */
    EFUN(blackhawk7_l2p2_INTERNAL_get_afe_bw_metric_lane_state(sa__, istate)); /* Dependency on istate->TP1 and istate->blind_ctle_trnsum */
    ESTM(istate->tp_metric_prec1 = rdv_usr_status_tp_metric_1());
    EFUN(blackhawk7_l2p2_INTERNAL_get_dfe_lane_state(sa__, istate)); /* Dependency on istate->rx_pam_mode */

    EFUN(blackhawk7_l2p2_INTERNAL_get_tx_ppm(sa__, &istate->tx_ppm));

    ESTM(istate->tx_disable_status = rd_tx_disable_status());
    ESTM(istate->tx_prec_en = rd_pam4_precoder_en());
    ESTM(istate->linktrn_en = rd_linktrn_ieee_training_enable());

    EFUN(blackhawk7_l2p2_INTERNAL_get_txfir_lane_state(sa__, istate));
    EFUN(blackhawk7_l2p2_INTERNAL_get_eye_margin_est(sa__, &istate->heye_left, &istate->heye_right, &istate->veye_upper, &istate->veye_lower));
    EFUN(blackhawk7_l2p2_INTERNAL_get_disable_eye_lane_state(sa__, istate));
    EFUN(blackhawk7_l2p2_INTERNAL_get_link_time(sa__, &istate->link_time));
    EFUN(blackhawk7_l2p2_INTERNAL_get_pmd_lock_chg_lane_state(sa__, istate));  /* Depedency on istate->pmd_lock */
    ESTM(istate->tx_pmd_dp_invert = rd_tx_pmd_dp_invert());
    ESTM(istate->rx_pmd_dp_invert = rd_rx_pmd_dp_invert());
    ESTM(istate->rmt_lpbk_en = rd_rmt_lpbk_en());
    ESTM(istate->dig_lpbk_en = rd_dig_lpbk_en());
    ESTM(istate->ilb_en = rd_ilb_en());
    ESTM(istate->tx_pi_en = rd_tx_pi_en());

    EFUN(blackhawk7_l2p2_INTERNAL_resume_micro_lane_state(sa__, istate)); /* Dependency on istate->stop_state */

    EFUN(blackhawk7_l2p2_INTERNAL_get_BER_string(sa__, 100, istate->BER, sizeof(istate->BER)));
    EFUN(blackhawk7_l2p2_INTERNAL_get_uc_sts_decoded_lane_state(sa__, istate)); /* Dependency on istate->UC_STS and istate->UC_STS_EXT */

    return (ERR_CODE_NONE);
}

/*------------------------------------*/
/*  Read Lane state Helper Functions  */
/*------------------------------------*/
err_code_t blackhawk7_l2p2_INTERNAL_resume_micro_lane_state(srds_access_t *sa__, blackhawk7_l2p2_lane_state_st_t *st) {
    if (!st->stop_state || (st->stop_state == 0xFF)) {
        /* manually check error code instead of EFUN*/
        err_code_t resume_status = ERR_CODE_NONE;
        resume_status = blackhawk7_l2p2_stop_rx_adaptation(sa__, 0);
        if (resume_status) {
            USR_PRINTF(("WARNING: Resuming micro after lane state capture failed \n"));
        }
    }
    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_get_stop_state_lane_state(srds_access_t *sa__, blackhawk7_l2p2_lane_state_st_t *st) {
    err_code_t err_code = 0;
    st->stop_state = blackhawk7_l2p2_INTERNAL_stop_micro(sa__,st->pmd_lock,&err_code);

    if(err_code) USR_PRINTF(("WARNING: Unable to stop microcontroller,  following data is suspect\n"));
    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_get_pmd_lock_chg_lane_state(srds_access_t *sa__, blackhawk7_l2p2_lane_state_st_t *st) {
    INIT_SRDS_ERR_CODE
    uint8_t rx_lock_at_end=0, rx_lock_chg_at_end=0;

    /* read lock status at end and combine them to handle transient cases */
    EFUN(blackhawk7_l2p2_INTERNAL_pmd_lock_status(sa__, &rx_lock_at_end, &rx_lock_chg_at_end));
    if (st->pmd_lock != rx_lock_at_end) {
        USR_PRINTF(("WARNING: Lane %d rx_lock status changed while reading lane state (rx_lock_start=%d, rx_lock_chg_start=%d, rx_lock_at_end=%d, rx_lock_chg_at_end=%d) \n",
                    blackhawk7_l2p2_acc_get_lane(sa__), st->pmd_lock, st->pmd_lock_chg, rx_lock_at_end, rx_lock_chg_at_end));
    }
    st->pmd_lock &= rx_lock_at_end;
    st->pmd_lock_chg |= rx_lock_chg_at_end;
    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_get_afe_bw_lane_state(srds_access_t *sa__, blackhawk7_l2p2_lane_state_st_t *st) {
    INIT_SRDS_ERR_CODE
    if (st->rx_pam_mode == NRZ) {
        st->afe_bw = 0;
    }
    else {
        ESTM(st->afe_bw = rdv_usr_status_afe_bw_dbg_0());
    }
    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_get_eq_debug1_lane_state(srds_access_t *sa__, blackhawk7_l2p2_lane_state_st_t *st) {
    INIT_SRDS_ERR_CODE
    if (st->rx_pam_mode == NRZ) {
        st->usr_status_eq_debug1 = 0;
    }
    else {
        ESTM(st->usr_status_eq_debug1 = rdv_usr_status_eq_debug1());
    }
    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_get_osr_str_lane_state(srds_access_t *sa__, blackhawk7_l2p2_lane_state_st_t *st) {
    const char *tx;
    UNUSED(sa__);

    if(st->osr_mode.tx_rx != 255) {
        tx = blackhawk7_l2p2_INTERNAL_get_osr_str(st->osr_mode.tx_rx, GET_OSR_STR_LONG);
        USR_SNPRINTF(st->tx_osr_mode_str, sizeof(st->tx_osr_mode_str), "%s", tx);
    }
    else {
        const char *rx;
        tx = blackhawk7_l2p2_INTERNAL_get_osr_str(st->osr_mode.tx, GET_OSR_STR_SHORT);
        rx = blackhawk7_l2p2_INTERNAL_get_osr_str(st->osr_mode.rx, GET_OSR_STR_SHORT);
        USR_SNPRINTF(st->tx_osr_mode_str, sizeof(st->tx_osr_mode_str), "%s", tx);
        USR_SNPRINTF(st->rx_osr_mode_str, sizeof(st->rx_osr_mode_str), "%s", rx);
    }
    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_get_uc_cfg_lane_state(srds_access_t *sa__, blackhawk7_l2p2_lane_state_st_t *st) {
    INIT_SRDS_ERR_CODE
    struct blackhawk7_l2p2_uc_lane_config_st lane_cfg;

    EFUN(blackhawk7_l2p2_get_uc_lane_cfg(sa__, &lane_cfg));
    st->UC_CFG = lane_cfg.word;

    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_get_uc_sts_decoded_lane_state(srds_access_t *sa__, blackhawk7_l2p2_lane_state_st_t *st) {
    INIT_SRDS_ERR_CODE
    const char * const prepend = "    ";
    if(st->UC_STS != 0) {
        EFUN(blackhawk7_l2p2_decode_uc_sts(sa__, st->UC_STS, st->uc_sts_decoded, sizeof(st->uc_sts_decoded), prepend));
    }
    if(st->UC_STS_EXT != 0) {
        EFUN(blackhawk7_l2p2_decode_uc_sts_ext(sa__, st->UC_STS_EXT, st->uc_sts_ext_decoded, sizeof(st->uc_sts_ext_decoded), prepend));
    }
    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_get_rx_pam_mode_lane_state(srds_access_t *sa__, blackhawk7_l2p2_lane_state_st_t *st) {
    INIT_SRDS_ERR_CODE
    enum blackhawk7_l2p2_rx_pam_mode_enum pam_mode = NRZ;

    EFUN(blackhawk7_l2p2_INTERNAL_get_rx_pam_mode(sa__, &pam_mode));
    st->rx_pam_mode = (uint8_t)pam_mode;

    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_get_disable_eye_lane_state(srds_access_t *sa__, blackhawk7_l2p2_lane_state_st_t *st) {
    INIT_SRDS_ERR_CODE
    struct blackhawk7_l2p2_usr_ctrl_disable_functions_st dsu, dss;
    uint8_t nrz_mode_en=0, pam4_mode_en=0;
    EFUN(blackhawk7_l2p2_get_usr_ctrl_disable_startup(sa__, &dsu));
    EFUN(blackhawk7_l2p2_get_usr_ctrl_disable_steady_state(sa__, &dss));
    nrz_mode_en = (st->rx_pam_mode == NRZ) && ((dsu.field.eye_margin_estimation) || (dss.field.eye_margin_estimation));
    pam4_mode_en = (st->rx_pam_mode != NRZ) && ((dsu.field.pam_eye_margin_estimation) || (dss.field.pam_eye_margin_estimation));
    st->disable_eye_display = nrz_mode_en || pam4_mode_en;
    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_get_TP0_lane_state(srds_access_t *sa__, blackhawk7_l2p2_lane_state_st_t *st) {
    INIT_SRDS_ERR_CODE
    if (st->rx_pam_mode == NRZ) {
        ESTM(st->TP0  = rd_rx_phase02_status());
        EFUN(blackhawk7_l2p2_INTERNAL_ladder_setting_to_mV(sa__, (int8_t)st->TP0, 0, INVALID_SLICER, &st->TP0));
    }
    else {
        ESTM(st->TP0 = rdv_usr_ctrl_pam4_chn_loss());
    }
    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_get_pf_lane_state(srds_access_t *sa__, blackhawk7_l2p2_lane_state_st_t *st) {
    INIT_SRDS_ERR_CODE
    EFUN(blackhawk7_l2p2_read_rx_afe(sa__, RX_AFE_PF2, &st->pf2_ctrl));
    EFUN(blackhawk7_l2p2_read_rx_afe(sa__, RX_AFE_PF3, &st->pf3_ctrl));
    EFUN(blackhawk7_l2p2_read_rx_afe(sa__, RX_AFE_PF, &st->pf_main));
    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_get_clk_lane_state(srds_access_t *sa__, blackhawk7_l2p2_lane_state_st_t *st) {
    INIT_SRDS_ERR_CODE
    ESTM(st->clk90 = rdv_usr_sts_phase_hoffset());
    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_get_dfe_lane_state(srds_access_t *sa__, blackhawk7_l2p2_lane_state_st_t *st) {
    INIT_SRDS_ERR_CODE
    if (st->rx_pam_mode == NRZ) {
        EFUN(blackhawk7_l2p2_INTERNAL_get_rx_dfe1(sa__, &st->DFE1));
    }
    EFUN(blackhawk7_l2p2_INTERNAL_get_rx_dfe2(sa__, &st->DFE2));
    EFUN(blackhawk7_l2p2_INTERNAL_get_rx_dfe3(sa__, &st->DFE3));
    EFUN(blackhawk7_l2p2_INTERNAL_get_rx_dfe4(sa__, &st->DFE4));
    EFUN(blackhawk7_l2p2_INTERNAL_get_rx_dfe5(sa__, &st->DFE5));
    EFUN(blackhawk7_l2p2_INTERNAL_get_rx_dfe6(sa__, &st->dfe6));
    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_get_txfir_lane_state(srds_access_t *sa__, blackhawk7_l2p2_lane_state_st_t *st) {
    INIT_SRDS_ERR_CODE
    uint8_t tap_num;
    ESTM(st->txfir_use_pam4_range = rd_txfir_nrz_tap_range_sel() ? 0 : 1);

    for (tap_num=0; tap_num<TXFIR_ST_NUM_TAPS; ++tap_num) {
        EFUN(blackhawk7_l2p2_INTERNAL_get_tx_tap(sa__, tap_num, &st->txfir.tap[tap_num]));
    }

    ESTM(st->enable_6taps = rd_txfir_tap_en());

    if (st->enable_6taps) {
        st->TXEQ_n2  = st->txfir.tap[0];
        st->TXEQ_n1  = st->txfir.tap[1];
        st->TXEQ_m   = st->txfir.tap[2];
        st->TXEQ_p1  = st->txfir.tap[3];
        st->TXEQ_p2  = st->txfir.tap[4];
        st->TXEQ_p3  = st->txfir.tap[5];
    }
    else {
        st->TXEQ_n1 = st->txfir.tap[0];
        st->TXEQ_m  = st->txfir.tap[1];
        st->TXEQ_p1 = st->txfir.tap[2];
    }
    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_get_afe_bw_metric_lane_state(srds_access_t *sa__, blackhawk7_l2p2_lane_state_st_t *st) {
    UNUSED(sa__);
    if ((st->TP1 == 0) && (st->blind_ctle_trnsum < 0)) {
        st->afe_bw_metric = st->blind_ctle_trnsum;
    }
    else {
        st->afe_bw_metric = st->TP1;
    }
    return ERR_CODE_NONE;
}



err_code_t blackhawk7_l2p2_INTERNAL_get_link_time(srds_access_t *sa__, uint32_t *link_time) {
    INIT_SRDS_ERR_CODE
    uint32_t usr_sts_link_time = 0;
    if(link_time == NULL) {
        return(ERR_CODE_BAD_PTR_OR_INVALID_INPUT);
    }
    ESTM(usr_sts_link_time = rdv_usr_sts_link_time());
    *link_time = (usr_sts_link_time<<BLACKHAWK7_L2P2_LANE_TIMER_SHIFT)/10;
    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_display_lane_state_no_newline(srds_access_t *sa__) {
  INIT_SRDS_ERR_CODE
  err_code_t Exit_Status = ERR_CODE_NONE;
  blackhawk7_l2p2_lane_state_st_t *state;


  state = (blackhawk7_l2p2_lane_state_st_t *)USR_CALLOC(1, sizeof(blackhawk7_l2p2_lane_state_st_t));
  if(!state) {
      return (ERR_CODE_MEM_ALLOC_FAIL);
  }
  CFUN(blackhawk7_l2p2_INTERNAL_read_lane_state(sa__, state));

  EFUN_PRINTF(("%2d ", state->laneid));


  if(state->osr_mode.tx_rx != 255) {
      EFUN_PRINTF(("(%s%s%2s%s, 0x%04x, 0x%02x ,", (state->tx_pmd_dp_invert ? "-" : "+"), (state->rx_pmd_dp_invert ? "-" : "+"),

                                                    ((state->CDR) ? "BR" : "OS"),

                                                    state->tx_osr_mode_str, state->UC_CFG,state->UC_STS));
  } else {
      EFUN_PRINTF(("(%s%s%3s%s,%2s%s:%s, 0x%04x, 0x%02x_%04x,", (state->tx_pmd_dp_invert ? "-" : "+"), (state->rx_pmd_dp_invert ? "-" : "+"),
                    ((state->rx_pam_mode == NRZ) ? "NRZ" : ((state->rx_pam_mode == PAM4_NR) ? "P4N": "P4E")), ((state->tx_pam_mode == (state->rx_pam_mode > 0)) ? " ": "~"),

                    ((state->CDR) ? "BR" : "OS"),

                    state->tx_osr_mode_str, state->rx_osr_mode_str, state->UC_CFG, state->UC_STS, state->UC_STS_EXT));
  }
  EFUN_PRINTF((" %01x,%01x, %02x, %1d,%1d)",state->tx_rst,state->rx_rst,state->stop_state,state->tx_pll_select,state->rx_pll_select));
  EFUN_PRINTF((" %1d%s", state->sig_det, state->sig_det_chg ? "*" : " "));

  EFUN_PRINTF((" %1d%s", state->pmd_lock, state->pmd_lock_chg ? "*" : " "));
  EFUN_PRINTF(("%s", state->pmd_lock ? (state->rx_tuning_done ? " " : "+") : " "));
  EFUN_PRINTF(("%4d ", state->ppm));

  EFUN_PRINTF(("  %3d ", state->clk90));
  EFUN_PRINTF(("(%2d,%1d,%2d,%2d) ", state->pf_main, state->pf2_ctrl, state->pf3_ctrl, state->bwr_ctrl));

  EFUN_PRINTF(("%2d ", state->VGA));

  EFUN_PRINTF(("%4d ", state->DCO));
  EFUN_PRINTF(("%4d ", state->P1mV));

  EFUN_PRINTF(("(%4d,%+5d,",
              state->TP0, /* pam4 _chn_loss */
              state->afe_bw_metric /* hidden logic buried deeper and within uCode */
             ));
  EFUN_PRINTF(("%2d,%3d,%3d)",
              state->afe_bw,
              state->usr_status_eq_debug1,
              state->tp_metric_prec1));
  if (state->rx_pam_mode == NRZ) {
      EFUN_PRINTF((" (%3d,%3d,%3d,%3d,%3d,%3d)", state->DFE1, state->DFE2, state->DFE3, state->DFE4, state->DFE5, state->dfe6));
  }
  else {
      EFUN_PRINTF((" ( x ,%3d,%3d,%3d,%3d,%3d)", state->DFE2, state->DFE3, state->DFE4, state->DFE5, state->dfe6));
  }
  EFUN_PRINTF((" %4d%c ", state->tx_ppm, state->tx_pi_en ? '*' : ' '));

  if(state->tx_disable_status){
      EFUN_PRINTF((" D"));
  }else{
      EFUN_PRINTF(("  "));
  }

  if(state->tx_prec_en){
      EFUN_PRINTF(("P"));
  }else{
      EFUN_PRINTF((" "));
  }

  if(state->rmt_lpbk_en){
      EFUN_PRINTF(("R"));
  }else if(state->dig_lpbk_en){
      EFUN_PRINTF(("L"));
  }else if(state->ilb_en){
      EFUN_PRINTF(("I"));
  }else if(state->linktrn_en){
      EFUN_PRINTF(("T"));
  }else{
      EFUN_PRINTF((" "));
  }

  if (!state->enable_6taps) {
      EFUN_PRINTF(("( x ,%3d,%3d,%3d, x , x )", state->txfir.tap[0], state->txfir.tap[1], state->txfir.tap[2]));
  }
  else {
      EFUN_PRINTF(("(%3d,%3d,%3d,%3d,%3d,%3d) ",
                   state->txfir.tap[0], state->txfir.tap[1], state->txfir.tap[2],
                   state->txfir.tap[3], state->txfir.tap[4], state->txfir.tap[5]));
  }
  if (state->disable_eye_display) {
      EFUN_PRINTF((" ( x , x , x , x ) "));
  }
  else {
      EFUN_PRINTF((" (%3d,%3d,%3d,%3d) ", state->heye_left, state->heye_right, state->veye_upper, state->veye_lower));
  }
  /* Check to see if link_time is max value after 80us to 0.1msec unit conversion */
  if (state->link_time == ((0xFFFFL<<BLACKHAWK7_L2P2_LANE_TIMER_SHIFT)/10)) {
      EFUN_PRINTF((" >%4d.%01d", state->link_time/10, state->link_time%10));
      EFUN_PRINTF(("  "));
  } else {
      EFUN_PRINTF((" %4d.%01d", state->link_time/10, state->link_time%10));
      EFUN_PRINTF(("   "));
  }

  EFUN_PRINTF(("%s",state->BER));


  if(state->UC_STS != 0) {
      EFUN_PRINTF(("\n"));
      EFUN_PRINTF(("%s", state->uc_sts_decoded));
  }

  if(state->UC_STS_EXT != 0) {
      EFUN_PRINTF(("%s", state->uc_sts_ext_decoded));
  }

Exit:
  USR_FREE(state);
  if(Exit_Status != ERR_CODE_NONE) {
      return blackhawk7_l2p2_error_report(sa__, Exit_Status);
  }

  return (ERR_CODE_NONE);
}  /* blackhawk7_l2p2_INTERNAL_display_lane_state_no_newline(srds_access_t *sa__) */



err_code_t blackhawk7_l2p2_INTERNAL_read_core_state(srds_access_t *sa__, blackhawk7_l2p2_core_state_st *istate) {
  INIT_SRDS_ERR_CODE
  blackhawk7_l2p2_core_state_st state;
  struct blackhawk7_l2p2_uc_core_config_st core_cfg = UC_CORE_CONFIG_INIT;

  ENULL_MEMSET(&state, 0, sizeof(blackhawk7_l2p2_core_state_st));

  if(!istate)
    return(blackhawk7_l2p2_error(sa__, ERR_CODE_BAD_PTR_OR_INVALID_INPUT));

  EFUN(blackhawk7_l2p2_get_uc_core_config(sa__, &core_cfg));

  /* BHK7 has independent rescals (all same value); reading out rescal_bg */
  ESTM(state.rescal = rdc_rescal_bg_mux());

  ESTM(state.core_reset           = rdc_core_dp_reset_state());
  ESTM(state.uc_active            = rdc_uc_active());
  ESTM(state.comclk_mhz           = rdc_heartbeat_count_1us());
  ESTM(state.pll_pwrdn            = rdc_pll_pwrdn_or());
  ESTM(state.ucode_version        = rdcv_common_ucode_version());
  ESTM(state.ucode_minor_version  = rdcv_common_ucode_minor_version());
  EFUN(blackhawk7_l2p2_version(sa__, &state.api_version));
  ESTM(state.afe_hardware_version = rdcv_afe_hardware_version());
  ESTM(state.temp_idx             = rdcv_temp_idx());
  EFUN(blackhawk7_l2p2_read_die_temperature(sa__, &state.die_temp));
  ESTM(state.avg_tmon             = (int16_t)(_bin_to_degC(rdcv_avg_tmon_reg13bit()>>3)));
  state.vco_rate_mhz              = (uint16_t)core_cfg.vco_rate_in_Mhz;
  EFUN(blackhawk7_l2p2_INTERNAL_read_pll_div(sa__, &state.pll_div));
  EFUN(blackhawk7_l2p2_INTERNAL_pll_lock_status(sa__, &state.pll_lock, &state.pll_lock_chg));
  ESTM(state.analog_vco_range     = rdc_pll_range());
  ESTM(state.core_status          = rdcv_status_byte());
  ESTM(state.refclk_doubler       = rdc_ams_pll_refclk_freq2x_en());
  *istate = state;
  return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_display_core_state_no_newline(srds_access_t *sa__) {
    INIT_SRDS_ERR_CODE
  blackhawk7_l2p2_core_state_st state;
    blackhawk7_l2p2_core_state_st state_pll1;
    char decode_buf[512];
    ENULL_MEMSET(&state_pll1, 0, sizeof(state_pll1));
    ENULL_MEMSET(&state     , 0, sizeof(state     ));
    {
        uint8_t pll_orig;
        ESTM(pll_orig = blackhawk7_l2p2_acc_get_pll_idx(sa__));
        EFUN(blackhawk7_l2p2_acc_set_pll_idx(sa__, 0));
        EFUN(blackhawk7_l2p2_INTERNAL_read_core_state(sa__, &state));
        EFUN(blackhawk7_l2p2_acc_set_pll_idx(sa__, 1));
        EFUN(blackhawk7_l2p2_INTERNAL_read_core_state(sa__, &state_pll1));
        EFUN(blackhawk7_l2p2_acc_set_pll_idx(sa__, pll_orig));
    }

    if ((state.avg_tmon<-50)||(state.avg_tmon>135)) {
      EFUN_PRINTF(("\n*** WARNING: Core die temperature (LIVE_TEMP) out of bounds -50C to 130C\n"));
    }
    if ((state.rescal < RESCAL_MIN) || (state.rescal > RESCAL_MAX)) {
      EFUN_PRINTF(("\n*** WARNING: RESCAL value is out of bounds %d to %d\n",RESCAL_MIN, RESCAL_MAX));
    }
    if ((state_pll1.rescal < RESCAL_MIN) || (state_pll1.rescal > RESCAL_MAX)) {
      EFUN_PRINTF(("\n*** WARNING: RESCAL PLL1 value is out of bounds %d to %d\n",RESCAL_MIN, RESCAL_MAX));
    }

    EFUN_PRINTF((" %02d "              ,  blackhawk7_l2p2_acc_get_core(sa__)));
    EFUN_PRINTF((" %x,%x,%02x "        ,  state.core_reset, state_pll1.core_reset, state.core_status));
    EFUN_PRINTF(("   %1d,%1d    "      ,  state.pll_pwrdn,state_pll1.pll_pwrdn));
    EFUN_PRINTF(("   %1d    "          ,  state.uc_active));
    EFUN_PRINTF((" %3d.%02dMHz"        , (state.comclk_mhz/4),((state.comclk_mhz%4)*25)));    /* comclk in Mhz = heartbeat_count_1us / 4 */
    EFUN_PRINTF(("   %4X_%02X "        ,  state.ucode_version, state.ucode_minor_version));
    EFUN_PRINTF(("  %06X "             ,  state.api_version));
    EFUN_PRINTF(("    0x%02X   "       ,  state.afe_hardware_version));
    EFUN_PRINTF(("   %3dC   "          ,  state.die_temp));
    EFUN_PRINTF(("   (%02d)%3dC "      ,  state.temp_idx, state.avg_tmon));
    EFUN_PRINTF((" 0x%02x,%02x "       ,  state.rescal, state_pll1.rescal));
    EFUN_PRINTF((" %2d.%03d,%2d.%03dGHz ", (state     .vco_rate_mhz / 1000),
                                           (state     .vco_rate_mhz % 1000),
                                           (state_pll1.vco_rate_mhz / 1000),
                                           (state_pll1.vco_rate_mhz % 1000)));
    EFUN_PRINTF(("  %03d,%03d     "    ,  state     .analog_vco_range,
                                          state_pll1.analog_vco_range));
    EFUN(blackhawk7_l2p2_INTERNAL_display_pll_to_divider(sa__, state .pll_div));
    EFUN_PRINTF((","));
    EFUN(blackhawk7_l2p2_INTERNAL_display_pll_to_divider(sa__, state_pll1.pll_div));
    EFUN_PRINTF(("  %01d%s,"           ,  state.pll_lock, state.pll_lock_chg ? "*" : " "));
    EFUN_PRINTF((" %01d%s"             ,  state_pll1.pll_lock, state_pll1.pll_lock_chg ? "*" : " "));
    if(state.core_status != 0) {
        EFUN_PRINTF(("\n"));
        EFUN(blackhawk7_l2p2_decode_core_sts(sa__, state.core_status, decode_buf, sizeof(decode_buf), ""));
        EFUN_PRINTF(("%s", decode_buf));
    }
    return (ERR_CODE_NONE);
  }
#endif /* SMALL_FOOTPRINT */


/* returns 000111 (7 = 8-1), for n = 3  */
#define BFMASK(n) ((1<<((n)))-1)

err_code_t blackhawk7_l2p2_INTERNAL_update_uc_lane_config_st(struct  blackhawk7_l2p2_uc_lane_config_st *st) {
  uint16_t in = st->word;
  st->field.lane_cfg_from_pcs = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.an_enabled = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.dfe_on = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.dfe_lp_mode = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.force_brdfe_on = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.media_type = in & BFMASK(2); in = (uint16_t)(in >> 2);
  st->field.unreliable_los = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.scrambling_dis = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.cl72_auto_polarity_en = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.cl72_restart_timeout_en = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.force_er = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.force_nr = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.lp_has_prec_en = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.force_pam4_mode = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.force_nrz_mode = in & BFMASK(1);
  return(ERR_CODE_NONE);
}
#ifndef SMALL_FOOTPRINT
err_code_t blackhawk7_l2p2_INTERNAL_update_usr_ctrl_disable_functions_st(struct blackhawk7_l2p2_usr_ctrl_disable_functions_st *st) {
  uint16_t in = st->word;
  st->field.pf_adaptation = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.pf2_adaptation = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.pf3_adaptation = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.dc_adaptation = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.vga_adaptation = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.slicer_voffset_tuning = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.slicer_hoffset_tuning = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.phase_offset_adaptation = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.eye_margin_estimation = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.all_adaptation = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.afe_bw_adaptation = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.pam_eye_margin_estimation = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.reserved2  = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.reserved = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.ss_pam4es_dfe_data_cdr = in & BFMASK(1); in = (uint16_t)(in >> 1);
  st->field.ss_open_loop_debug = in & BFMASK(1);
  return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_update_usr_ctrl_disable_dfe_functions_st(struct blackhawk7_l2p2_usr_ctrl_disable_dfe_functions_st *st) {
  uint8_t in = st->byte;
  st->field.dfe_tap1_adaptation = in & BFMASK(1); in = (uint8_t)(in >> 1);
  st->field.dfe_fx_taps_adaptation = in & BFMASK(1); in = (uint8_t)(in >> 1);
  st->field.dfe_fl_taps_adaptation = in & BFMASK(1); in = (uint8_t)(in >> 1);
  st->field.dfe_dcd_adaptation = in & BFMASK(1);
  return ERR_CODE_NONE;
}
#endif /* SMALL_FOOTPRINT */
/* word to fields, for display */
err_code_t blackhawk7_l2p2_INTERNAL_update_uc_core_config_st(struct blackhawk7_l2p2_uc_core_config_st *st) {
  uint16_t in = st->word;
  st->field.vco_rate = (uint8_t)(in & BFMASK(8)); in = (uint16_t)(in >> 8);
  st->field.core_cfg_from_pcs = (uint8_t)(in & BFMASK(1)); in = (uint16_t)(in >> 1);
  st->field.osr_2p5_en = (uint8_t)(in & BFMASK(1)); in = (uint16_t)(in >> 1);
  st->field.reserved = in & BFMASK(6);
  st->vco_rate_in_Mhz = VCO_RATE_TO_MHZ(st->field.vco_rate);
  return ERR_CODE_NONE;
}

/* fields to word, to write into uC RAM */
err_code_t blackhawk7_l2p2_INTERNAL_update_uc_core_config_word(struct blackhawk7_l2p2_uc_core_config_st *st) {
  uint16_t in = 0;
  in = (uint16_t)(in << 6); in |= 0/*st->field.reserved*/ & BFMASK(6);
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.osr_2p5_en & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.core_cfg_from_pcs & BFMASK(1)));
  in = (uint16_t)(in << 8); in = (uint16_t)(in | (st->field.vco_rate & BFMASK(8)));
  st->word = in;
  return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_update_uc_lane_config_word(struct blackhawk7_l2p2_uc_lane_config_st *st) {
  uint16_t in = 0;
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.force_nrz_mode & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.force_pam4_mode & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.lp_has_prec_en & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.force_nr & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.force_er & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.cl72_restart_timeout_en & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | ( st->field.cl72_auto_polarity_en & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | ( st->field.scrambling_dis & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | ( st->field.unreliable_los & BFMASK(1)));
  in = (uint16_t)(in << 2); in = (uint16_t)(in | ( st->field.media_type & BFMASK(2)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | ( st->field.force_brdfe_on & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.dfe_lp_mode & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.dfe_on & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.an_enabled & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.lane_cfg_from_pcs & BFMASK(1)));
  st->word = in;
  return ERR_CODE_NONE;
}


#ifndef SMALL_FOOTPRINT
err_code_t blackhawk7_l2p2_INTERNAL_update_usr_ctrl_disable_functions_byte(struct blackhawk7_l2p2_usr_ctrl_disable_functions_st *st) {
  uint16_t in = 0;
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.ss_open_loop_debug & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.ss_pam4es_dfe_data_cdr & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.reserved & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.reserved2 & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.pam_eye_margin_estimation & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.afe_bw_adaptation & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.all_adaptation & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.eye_margin_estimation & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.phase_offset_adaptation & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.slicer_hoffset_tuning & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.slicer_voffset_tuning & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.vga_adaptation & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.dc_adaptation & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.pf3_adaptation & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.pf2_adaptation & BFMASK(1)));
  in = (uint16_t)(in << 1); in = (uint16_t)(in | (st->field.pf_adaptation & BFMASK(1)));
  st->word = in;
  return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_update_usr_ctrl_disable_dfe_functions_byte(struct  blackhawk7_l2p2_usr_ctrl_disable_dfe_functions_st *st) {
  uint8_t in = 0;
  in = (uint8_t)(in << 1); in = (uint8_t)(in | (st->field.dfe_dcd_adaptation & BFMASK(1)));
  in = (uint8_t)(in << 1); in = (uint8_t)(in | (st->field.dfe_fl_taps_adaptation & BFMASK(1)));
  in = (uint8_t)(in << 1); in = (uint8_t)(in | (st->field.dfe_fx_taps_adaptation & BFMASK(1)));
  in = (uint8_t)(in << 1); in = (uint8_t)(in | (st->field.dfe_tap1_adaptation & BFMASK(1)));
  st->byte = in;
  return ERR_CODE_NONE;
}
#endif /*SMALL_FOOTPRINT */

#undef BFMASK

err_code_t blackhawk7_l2p2_INTERNAL_check_uc_lane_stopped(srds_access_t *sa__) {
    INIT_SRDS_ERR_CODE

  uint8_t is_micro_stopped;
  ESTM(is_micro_stopped = rdv_usr_sts_micro_stopped() || (rd_rx_lane_dp_reset_state() > 0));
  if (!is_micro_stopped) {
      return(blackhawk7_l2p2_error(sa__, ERR_CODE_UC_NOT_STOPPED));
  } else {
      return(ERR_CODE_NONE);
  }
}
#ifndef SMALL_FOOTPRINT

err_code_t blackhawk7_l2p2_INTERNAL_calc_patt_gen_mode_sel(srds_access_t *sa__, uint8_t *mode_sel, uint8_t *zero_pad_len, uint8_t patt_length) {

  if(!mode_sel || !zero_pad_len || !patt_length) {
    return(blackhawk7_l2p2_error(sa__, ERR_CODE_BAD_PTR_OR_INVALID_INPUT));
  }

  /* Select the correct Pattern generator Mode depending on Pattern length */
  if (!(140 % patt_length)) {
    *mode_sel = 6;
    *zero_pad_len = 100;
  }
  else if (!(160 % patt_length)) {
    *mode_sel = 5;
    *zero_pad_len = 80;
  }
  else if (!(180 % patt_length)) {
    *mode_sel = 4;
    *zero_pad_len = 60;
  }
  else if (!(200 % patt_length)) {
    *mode_sel = 3;
    *zero_pad_len = 40;
  }
  else if (!(220 % patt_length)) {
    *mode_sel = 2;
    *zero_pad_len = 20;
  }
  else if (!(240 % patt_length)) {
    *mode_sel = 1;
    *zero_pad_len = 0;
  } else {
    EFUN_PRINTF(("ERROR: Unsupported Pattern Length\n"));
    return (blackhawk7_l2p2_error(sa__, ERR_CODE_CFG_PATT_INVALID_PATT_LENGTH));
  }
  return(ERR_CODE_NONE);
}
#endif /*SMALL_FOOTPRINT */

/*-----------------------------------------*/
/*  Write Core Config variables to uC RAM  */
/*-----------------------------------------*/

err_code_t blackhawk7_l2p2_INTERNAL_set_uc_core_config(srds_access_t *sa__, struct blackhawk7_l2p2_uc_core_config_st struct_val) {
    INIT_SRDS_ERR_CODE
    {   uint8_t reset_state;
        ESTM(reset_state = rdc_core_dp_reset_state());
        if(reset_state < 7) {
            EFUN_PRINTF(("ERROR: blackhawk7_l2p2_INTERNAL_set_uc_core_config(..) called without core_dp_s_rstb=0\n"));
            return (blackhawk7_l2p2_error(sa__, ERR_CODE_CORE_DP_NOT_RESET));
        }
    }
    if(struct_val.vco_rate_in_Mhz > 0) {
        struct_val.field.vco_rate = MHZ_TO_VCO_RATE(struct_val.vco_rate_in_Mhz);
    }
    EFUN(blackhawk7_l2p2_INTERNAL_update_uc_core_config_word(&struct_val));
    switch (blackhawk7_l2p2_acc_get_pll_idx(sa__)) {
    case 0:
        EFUN(reg_wrc_CORE_PLL_COM_PLL_UC_CORE_CONFIG(struct_val.word));
        break;
    case 1:
        EFUN(reg_wrc_CORE_PLL_COM_PLL_UC_CORE_CONFIG(struct_val.word));
        break;
    default:
        return(blackhawk7_l2p2_error(sa__, ERR_CODE_BAD_PTR_OR_INVALID_INPUT));
    }
    return (ERR_CODE_NONE);
}

/*---------------------*/
/*  PLL Configuration  */
/*---------------------*/
/** Extract the refclk frequency in Hz, based on a blackhawk7_l2p2_pll_refclk_enum value. */
err_code_t blackhawk7_l2p2_INTERNAL_get_refclk_in_hz(srds_access_t *sa__, enum blackhawk7_l2p2_pll_refclk_enum refclk, uint32_t *refclk_in_hz) {
    switch (refclk) {
        case BLACKHAWK7_L2P2_PLL_REFCLK_145P947802MHZ:  *refclk_in_hz = 145947802; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_166P7974882MHZ: *refclk_in_hz = 166797488; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_167P4107143MHZ: *refclk_in_hz = 167410714; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_245P76MHZ:      *refclk_in_hz = 245760000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_250MHZ:         *refclk_in_hz = 250000000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_425MHZ:         *refclk_in_hz = 425000000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_534MHZ:         *refclk_in_hz = 534000000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_705MHZ:         *refclk_in_hz = 705000000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_175MHZ:         *refclk_in_hz = 175000000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_400MHZ:         *refclk_in_hz = 400000000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_266P67MHZ:      *refclk_in_hz = 266670000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_100MHZ:         *refclk_in_hz = 100000000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_106P25MHZ:      *refclk_in_hz = 106250000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_122P88MHZ:      *refclk_in_hz = 122880000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_125MHZ:         *refclk_in_hz = 125000000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_155P52MHZ:      *refclk_in_hz = 155520000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_156P25MHZ:      *refclk_in_hz = 156250000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_159P375MHZ:     *refclk_in_hz = 159375000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_161P1328125MHZ: *refclk_in_hz = 161132813; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_166P67MHZ:      *refclk_in_hz = 166670000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_166P015625MHZ:  *refclk_in_hz = 166015625; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_167P38MHZ:      *refclk_in_hz = 167380000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_174P703125MHZ:  *refclk_in_hz = 174703125; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_212P5MHZ:       *refclk_in_hz = 212500000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_311P04MHZ:      *refclk_in_hz = 311040000; break;
        case BLACKHAWK7_L2P2_PLL_REFCLK_312P5MHZ:       *refclk_in_hz = 312500000; break;
        default:
            EFUN_PRINTF(("ERROR: Unknown refclk frequency:  0x%08X\n", (uint32_t)refclk));
            *refclk_in_hz = 0xFFFFFFFF;
            return (blackhawk7_l2p2_error(sa__, ERR_CODE_REFCLK_FREQUENCY_INVALID));
    }
    return (ERR_CODE_NONE);
}

/** Identify the ratio:
 *
 *     (numerator / denominator) = (1000 / divisor)
 *
 * such that this has as little rounding error as possible:
 *
 *     refclk_freq_hz = numerator * round(vco_freq_khz / denominator)
 *
 * This will yield the most accurate refclk_freq_hz.
 * Common values of vco_freq_khz are considered in this.
 */
static uint32_t _steins_gcd(uint32_t u, uint32_t v) {
    /* simple cases (termination) */
    if (u == v)
        return u;

    if (u == 0)
        return v;

    if (v == 0)
        return u;

    /* look for factors of 2 */
    if (~u & 1) {                                       /* u is even */
        if (v & 1)                                      /* v is odd */
            return _steins_gcd(u >> 1, v);
        else                                            /* both u and v are even */
            return _steins_gcd(u >> 1, v >> 1) << 1;
    }

    if (~v & 1)                                         /* u is odd, v is even */
        return _steins_gcd(u, v >> 1);

    /* reduce larger argument */
    if (u > v)
        return _steins_gcd((u - v) >> 1, v);

    return _steins_gcd((v - u) >> 1, u);
}

static err_code_t _blackhawk7_l2p2_minimize_divisor_ratio(uint32_t md, uint32_t *simple_numerator, uint32_t *simple_denominator) {
    /* continued fraction coefficients */
    uint32_t a, h[3] = { 0, 1, 0 }, k[3] = { 1, 0, 0 };
    uint32_t x, d, n;
    uint8_t i;

    n = *simple_numerator;
    d = *simple_denominator;

    /* continued fraction and check denominator each step */
    for (i = 0; i < 64; i++) {

        a = (n ? d / n : 0);
        if (i && !a) break;

        /* coverity[divide_by_zero] */
        x = d; d = n; n = x % n;

        x = a;
        if (k[1] * a + k[0] >= md) {
            x = (md - k[0]) / k[1];
            if (x * 2 >= a || k[1] >= md)
                i = 65;
            else
                break;
        }

        h[2] = x * h[1] + h[0]; h[0] = h[1]; h[1] = h[2];
        k[2] = x * k[1] + k[0]; k[0] = k[1]; k[1] = k[2];
    }
    *simple_denominator = k[1];
    *simple_numerator   = h[1];
    return (ERR_CODE_NONE);
}

static err_code_t _blackhawk7_l2p2_get_divisor_ratio(srds_access_t *sa__, enum blackhawk7_l2p2_pll_div_enum srds_div, uint16_t *simple_numerator, uint16_t *simple_denominator){
    /*
       From the documentation above:
       (numerator / denominator) = (1000 / divisor)
       divisor = div_int + div_decimal where div_decimal = (UPPER_FIVE_HEX_DIGITS_OF_ENUM)/(0x100000).
       This is the same as: (numerator / denominator) =  (1000)(0x100000) / ((div_int)*(0x100000) + UPPER_FIVE_HEX_DIGITS_OF_ENUM)
       numerator = 1000(0x100000) and denominator= div_int*0x100000 + UPPER_FIVE_HEX_DIGITS_OF_ENUM
       If we simplify this fraction, we should end up with the same values as the table above
    */

    uint32_t lowest_numerator, lowest_denominator, gcd;

    if (srds_div == BLACKHAWK7_L2P2_PLL_DIV_UNKNOWN){
        EFUN_PRINTF(("ERROR: Unknown divider value:  0x%08X\n", (uint32_t)srds_div));
        *simple_numerator = 0;
        *simple_denominator = 0;
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_PLL_DIV_INVALID));
    }

    lowest_numerator = (1000)*(0x100000);
    lowest_denominator = ((uint32_t)srds_div & 0xFFF)*0x100000 + (((uint32_t)srds_div & 0xFFFFC000)>>12);
    gcd = _steins_gcd(lowest_numerator, lowest_denominator);

    lowest_numerator    = lowest_numerator / gcd;
    lowest_denominator  = lowest_denominator / gcd;

    if (lowest_numerator >= 0x10000){
        _blackhawk7_l2p2_minimize_divisor_ratio(0x10000,&lowest_numerator, &lowest_denominator);
        *simple_numerator   = (uint16_t)lowest_denominator;
        *simple_denominator = (uint16_t)lowest_numerator;
        return (ERR_CODE_NONE);
    }
    *simple_numerator   = (uint16_t)lowest_numerator;
    *simple_denominator = (uint16_t)lowest_denominator;

    return (ERR_CODE_NONE);
}


#ifndef SMALL_FOOTPRINT
/** Get the Refclk frequency in Hz, based on the blackhawk7_l2p2_pll_div_enum value and VCO frequency. */
static err_code_t _blackhawk7_l2p2_get_refclk_from_div_vco(srds_access_t *sa__, uint32_t *refclk_freq_hz, enum blackhawk7_l2p2_pll_div_enum srds_div, uint32_t vco_freq_khz, enum blackhawk7_l2p2_pll_option_enum pll_option) {
    INIT_SRDS_ERR_CODE
    uint16_t numerator, denominator;
    EFUN(_blackhawk7_l2p2_get_divisor_ratio(sa__, srds_div, &numerator, &denominator));
    if (denominator == 0){
        EFUN_PRINTF(("ERROR: Divider returned denominator 0:  0x%08X\n", (uint32_t)srds_div));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_PLL_DIV_INVALID));
    }
    *refclk_freq_hz = ((vco_freq_khz+(denominator>>1)) / denominator) * numerator;
    if (pll_option == BLACKHAWK7_L2P2_PLL_OPTION_REFCLK_DOUBLER_EN) *refclk_freq_hz /= 2;
    if (pll_option == BLACKHAWK7_L2P2_PLL_OPTION_REFCLK_DIV2_EN)    *refclk_freq_hz *= 2;
    if (pll_option == BLACKHAWK7_L2P2_PLL_OPTION_REFCLK_DIV4_EN)    *refclk_freq_hz *= 4;
    return (ERR_CODE_NONE);
}
#endif /*SMALL_FOOTPRINT */

/** Get the VCO frequency in kHz, based on the reference clock frequency and blackhawk7_l2p2_pll_div_enum value. */
err_code_t blackhawk7_l2p2_INTERNAL_get_vco_from_refclk_div(srds_access_t *sa__, uint32_t refclk_freq_hz, enum blackhawk7_l2p2_pll_div_enum srds_div, uint32_t *vco_freq_khz, enum blackhawk7_l2p2_pll_option_enum pll_option) {
    INIT_SRDS_ERR_CODE
    uint16_t numerator, denominator;
    uint64_t temp_dividend;
    EFUN(_blackhawk7_l2p2_get_divisor_ratio(sa__, srds_div, &numerator, &denominator));
    if (pll_option == BLACKHAWK7_L2P2_PLL_OPTION_REFCLK_DOUBLER_EN) refclk_freq_hz *= 2;
    if (pll_option == BLACKHAWK7_L2P2_PLL_OPTION_REFCLK_DIV2_EN)    refclk_freq_hz /= 2;
    if (pll_option == BLACKHAWK7_L2P2_PLL_OPTION_REFCLK_DIV4_EN)    refclk_freq_hz /= 4;
    if (numerator == 0){
        EFUN_PRINTF(("ERROR: Divider returned numerator 0:  0x%08X\n", (uint32_t)srds_div));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_PLL_DIV_INVALID));
    }
    /* *vco_freq_khz =(uint32_t) (((uint64_t)refclk_freq_hz * denominator + (numerator >> 1)) / numerator); */

    COMPILER_64_ZERO(temp_dividend);
    COMPILER_64_ADD_32(temp_dividend, refclk_freq_hz);
    COMPILER_64_UMUL_32(temp_dividend, denominator); /* refclk_freq_hz * denominator */
    COMPILER_64_ADD_32(temp_dividend, (numerator >> 1)); /* ((uint64_t)refclk_freq_hz * denominator + (numerator >> 1)) */
    COMPILER_64_UDIV_32(temp_dividend, numerator); /* (((uint64_t)refclk_freq_hz * denominator + (numerator >> 1)) / numerator) */
    *vco_freq_khz = COMPILER_64_LO(temp_dividend);

    return (ERR_CODE_NONE);
}

/* Boundaries for allowed VCO frequency */
#    define SERDES_VCO_FREQ_KHZ_MIN (15000000)
#    define SERDES_VCO_FREQ_KHZ_MAX (30000000)

/* Allowed tolerance in resultant VCO frequency when auto-determining divider value */
#    define SERDES_VCO_FREQ_KHZ_TOLERANCE (2000)

#ifndef SMALL_FOOTPRINT
/* The allowed PLL divider values */
static const enum blackhawk7_l2p2_pll_div_enum _blackhawk7_l2p2_div_candidates[] = {
    BLACKHAWK7_L2P2_PLL_DIV_82P50128477,
    BLACKHAWK7_L2P2_PLL_DIV_85P67380253,
    BLACKHAWK7_L2P2_PLL_DIV_88P39285714,
    BLACKHAWK7_L2P2_PLL_DIV_88P76582278,
    BLACKHAWK7_L2P2_PLL_DIV_89P44777920,
    BLACKHAWK7_L2P2_PLL_DIV_89P84376637,
    BLACKHAWK7_L2P2_PLL_DIV_179P6875327,
    BLACKHAWK7_L2P2_PLL_DIV_66,
    BLACKHAWK7_L2P2_PLL_DIV_67,
    BLACKHAWK7_L2P2_PLL_DIV_70,
    BLACKHAWK7_L2P2_PLL_DIV_72,
    BLACKHAWK7_L2P2_PLL_DIV_74P25,
    BLACKHAWK7_L2P2_PLL_DIV_76,
    BLACKHAWK7_L2P2_PLL_DIV_73P6,
    BLACKHAWK7_L2P2_PLL_DIV_79P2,
    BLACKHAWK7_L2P2_PLL_DIV_80,
    BLACKHAWK7_L2P2_PLL_DIV_82P5,
    BLACKHAWK7_L2P2_PLL_DIV_84,
    BLACKHAWK7_L2P2_PLL_DIV_85,
    BLACKHAWK7_L2P2_PLL_DIV_87P5,
    BLACKHAWK7_L2P2_PLL_DIV_89P6,
    BLACKHAWK7_L2P2_PLL_DIV_90,
    BLACKHAWK7_L2P2_PLL_DIV_90P75,
    BLACKHAWK7_L2P2_PLL_DIV_96,
    BLACKHAWK7_L2P2_PLL_DIV_100,
    BLACKHAWK7_L2P2_PLL_DIV_120,
    BLACKHAWK7_L2P2_PLL_DIV_127P401984,
    BLACKHAWK7_L2P2_PLL_DIV_128,
    BLACKHAWK7_L2P2_PLL_DIV_136,
    BLACKHAWK7_L2P2_PLL_DIV_137P721519,
    BLACKHAWK7_L2P2_PLL_DIV_140,
    BLACKHAWK7_L2P2_PLL_DIV_142P0253165,
    BLACKHAWK7_L2P2_PLL_DIV_144,
    BLACKHAWK7_L2P2_PLL_DIV_152,
    BLACKHAWK7_L2P2_PLL_DIV_165P7770801,
    BLACKHAWK7_L2P2_PLL_DIV_170P800628,
    BLACKHAWK7_L2P2_PLL_DIV_141P4285714,
    BLACKHAWK7_L2P2_PLL_DIV_171P347605,
    BLACKHAWK7_L2P2_PLL_DIV_176P7857143,
    BLACKHAWK7_L2P2_PLL_DIV_177P5316456,
    BLACKHAWK7_L2P2_PLL_DIV_178P8955584,
    BLACKHAWK7_L2P2_PLL_DIV_179P7348805,
    BLACKHAWK7_L2P2_PLL_DIV_179P7356828,
    BLACKHAWK7_L2P2_PLL_DIV_180P5309734,
    BLACKHAWK7_L2P2_PLL_DIV_184,
    BLACKHAWK7_L2P2_PLL_DIV_192,
    BLACKHAWK7_L2P2_PLL_DIV_198,
    BLACKHAWK7_L2P2_PLL_DIV_200,
    BLACKHAWK7_L2P2_PLL_DIV_224,
    BLACKHAWK7_L2P2_PLL_DIV_240,
    BLACKHAWK7_L2P2_PLL_DIV_54,
    BLACKHAWK7_L2P2_PLL_DIV_108,
    BLACKHAWK7_L2P2_PLL_DIV_132,
    BLACKHAWK7_L2P2_PLL_DIV_147P2,
    BLACKHAWK7_L2P2_PLL_DIV_158P4,
    BLACKHAWK7_L2P2_PLL_DIV_160,
    BLACKHAWK7_L2P2_PLL_DIV_165,
    BLACKHAWK7_L2P2_PLL_DIV_168,
    BLACKHAWK7_L2P2_PLL_DIV_170,
    BLACKHAWK7_L2P2_PLL_DIV_175,
    BLACKHAWK7_L2P2_PLL_DIV_180,
    BLACKHAWK7_L2P2_PLL_DIV_264,
    BLACKHAWK7_L2P2_PLL_DIV_280,
    BLACKHAWK7_L2P2_PLL_DIV_330,
    BLACKHAWK7_L2P2_PLL_DIV_350
};

static const uint8_t _blackhawk7_l2p2_div_candidates_count = sizeof(_blackhawk7_l2p2_div_candidates) / sizeof(_blackhawk7_l2p2_div_candidates[0]);

static err_code_t _blackhawk7_l2p2_check_div(srds_access_t *sa__, enum blackhawk7_l2p2_pll_div_enum srds_div) {
    uint8_t i, found = 0;
    for (i=0; i<_blackhawk7_l2p2_div_candidates_count; i++) {
        found = (uint8_t)(found | (srds_div == _blackhawk7_l2p2_div_candidates[i]));
    }
    if (!found) {
        EFUN_PRINTF(("ERROR: Invalid divider value:  0x%08X\n", (uint32_t)srds_div));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_PLL_DIV_INVALID));
    }
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_check_vco_freq_khz(srds_access_t *sa__, uint32_t vco_freq_khz) {
    uint32_t min_vco_freq = SERDES_VCO_FREQ_KHZ_MIN;
    if (vco_freq_khz < min_vco_freq - SERDES_VCO_FREQ_KHZ_TOLERANCE) {
        EFUN_PRINTF(("ERROR: VCO frequency too low:  %d kHz is lower than minimum (%d kHz)\n", vco_freq_khz, min_vco_freq));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_VCO_FREQUENCY_INVALID));
    }
    if (vco_freq_khz > SERDES_VCO_FREQ_KHZ_MAX + SERDES_VCO_FREQ_KHZ_TOLERANCE) {
        EFUN_PRINTF(("ERROR: VCO frequency too high:  %d kHz is higher than maximum (%d kHz)\n", vco_freq_khz, SERDES_VCO_FREQ_KHZ_MAX));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_VCO_FREQUENCY_INVALID));
    }
    return (ERR_CODE_NONE);
}

/** Find the entry out of _blackhawk7_l2p2_div_candidates that is closest to matching refclk_freq_hz and vco_freq_khz. */
static err_code_t _blackhawk7_l2p2_get_div(srds_access_t *sa__, uint32_t refclk_freq_hz, uint32_t vco_freq_khz, enum blackhawk7_l2p2_pll_div_enum *srds_div, enum blackhawk7_l2p2_pll_option_enum pll_option) {
    INIT_SRDS_ERR_CODE
    int32_t vco_freq_khz_min_error = 0x7FFFFFFF;
    uint8_t i;
    for (i=0; i<_blackhawk7_l2p2_div_candidates_count; i++) {
        uint32_t actual_vco_freq_khz = 0;
        int32_t  vco_freq_khz_error;
        EFUN(blackhawk7_l2p2_INTERNAL_get_vco_from_refclk_div(sa__, refclk_freq_hz, _blackhawk7_l2p2_div_candidates[i], &actual_vco_freq_khz, pll_option));
        vco_freq_khz_error = (int32_t)(vco_freq_khz - actual_vco_freq_khz);
        vco_freq_khz_error = SRDS_ABS(vco_freq_khz_error);
        if (vco_freq_khz_min_error > vco_freq_khz_error) {
            vco_freq_khz_min_error = vco_freq_khz_error;
            *srds_div = _blackhawk7_l2p2_div_candidates[i];
        }
    }
    if (vco_freq_khz_min_error == (int32_t)0xFFFFFFFF) {
      return (blackhawk7_l2p2_error(sa__, ERR_CODE_CONFLICTING_PARAMETERS));
    }
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_resolve_pll_parameters(srds_access_t *sa__,
                                                  enum blackhawk7_l2p2_pll_refclk_enum refclk,
                                                  uint32_t *refclk_freq_hz,
                                                  enum blackhawk7_l2p2_pll_div_enum *srds_div,
                                                  uint32_t *vco_freq_khz,
                                                  enum blackhawk7_l2p2_pll_option_enum pll_option) {
    INIT_SRDS_ERR_CODE

    /* Parameter value and consistency checks */
    const uint8_t given_param_count = (uint8_t)(((refclk == BLACKHAWK7_L2P2_PLL_REFCLK_UNKNOWN) ? 0 : 1)
                                       + ((*srds_div == BLACKHAWK7_L2P2_PLL_DIV_UNKNOWN) ? 0 : 1)
                                       + ((*vco_freq_khz == 0) ? 0 : 1));
    const uint32_t original_vco_freq_khz = *vco_freq_khz;
    enum blackhawk7_l2p2_pll_div_enum auto_div = BLACKHAWK7_L2P2_PLL_DIV_UNKNOWN;
    const char*pll_option_e2s[] = {"no", "refclk_x2", "refclk_div2", "refclk_div4"};

    COMPILER_REFERENCE(pll_option_e2s);

    /* Verify that at least two of the three parameters is given. */
    if (given_param_count < 2) {
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_INSUFFICIENT_PARAMETERS));
    }

    /* Skip verification if option is selected. Error if all parameters not given. */
    if ((pll_option & BLACKHAWK7_L2P2_PLL_OPTION_DISABLE_VERIFY) == BLACKHAWK7_L2P2_PLL_OPTION_DISABLE_VERIFY) {
        if (given_param_count < 3) {
            return (blackhawk7_l2p2_error(sa__, ERR_CODE_INSUFFICIENT_PARAMETERS));
        } else {
            /* Calculate "refclk_freq_hz" from the input "refclk" enum (0xNNNMMMMM = Frequency is MMMMM / NNN MHz) */
            /**refclk_freq_hz = (uint32_t)((((uint64_t)(refclk & 0xFFFFF)) * 1000000) / ((((uint32_t)refclk) & 0xFFF00000) >> 20)); */

            uint64_t refclk_temp;
            uint32_t refclk_mhz;
            COMPILER_64_SET(refclk_temp, 0, (refclk & 0xFFFFF));
            COMPILER_64_UMUL_32(refclk_temp, 1000000);
            refclk_mhz = ((uint32_t)(refclk & 0xFFF00000) >> 20);
            COMPILER_64_UDIV_32(refclk_temp, refclk_mhz);
            *refclk_freq_hz = COMPILER_64_LO(refclk_temp);

            return(ERR_CODE_NONE);
        }
    }
    pll_option = (enum blackhawk7_l2p2_pll_option_enum)(pll_option & BLACKHAWK7_L2P2_PLL_OPTION_REFCLK_MASK);

    /* The refclk value is checked in various functions below. */

    /* Verify that the requested div value is allowed. */
    if (*srds_div != BLACKHAWK7_L2P2_PLL_DIV_UNKNOWN) {
        EFUN(_blackhawk7_l2p2_check_div(sa__, *srds_div));
    }

    /* Verify that the requested VCO frequency is allowed. */
    if (*vco_freq_khz != 0) {
        EFUN(blackhawk7_l2p2_INTERNAL_check_vco_freq_khz(sa__,*vco_freq_khz));
    }

    if (refclk == BLACKHAWK7_L2P2_PLL_REFCLK_UNKNOWN) {
        /* Determine refclk from vco frequency and div */
        EFUN(_blackhawk7_l2p2_get_refclk_from_div_vco(sa__, refclk_freq_hz, *srds_div, *vco_freq_khz, pll_option));
    } else {
        EFUN(blackhawk7_l2p2_INTERNAL_get_refclk_in_hz(sa__, refclk, refclk_freq_hz));
    }

    if (*vco_freq_khz == 0) {
        /* Determine VCO frequency from refclk and divider */
        EFUN(blackhawk7_l2p2_INTERNAL_get_vco_from_refclk_div(sa__, *refclk_freq_hz, *srds_div, vco_freq_khz, pll_option));
    }

    /* Determine divider from vco frequency and refclk.
     * This is done even if the div was provided, because if it is,
     * we still want to check whether the parameters are conflicting.
     */
    EFUN(_blackhawk7_l2p2_get_div(sa__, *refclk_freq_hz, *vco_freq_khz, &auto_div, pll_option));
    if (*srds_div == BLACKHAWK7_L2P2_PLL_DIV_UNKNOWN) {
        /* Use the auto-determined divider value, since the divider was not supplied. */
        *srds_div = auto_div;

        /* Determine resultant VCO frequency from refclk and divider */
        EFUN(blackhawk7_l2p2_INTERNAL_get_vco_from_refclk_div(sa__, *refclk_freq_hz, *srds_div, vco_freq_khz, pll_option));
    }

    /* Verify the resultant VCO frequency */
    EFUN(blackhawk7_l2p2_INTERNAL_check_vco_freq_khz(sa__, *vco_freq_khz));

    /* Verify that the requested VCO frequency is delivered. */
    if ((original_vco_freq_khz != 0)
        && ((*vco_freq_khz < original_vco_freq_khz - SERDES_VCO_FREQ_KHZ_TOLERANCE)
            || (*vco_freq_khz > original_vco_freq_khz + SERDES_VCO_FREQ_KHZ_TOLERANCE))) {
        EFUN_PRINTF(("ERROR: Could not achieve requested VCO frequency of %d kHz.\n       Refclk is %d Hz, %s option enabled, and auto-determined divider is 0x%08X, yielding a VCO frequency of %d kHz.\n",
                     original_vco_freq_khz, *refclk_freq_hz, pll_option_e2s[pll_option], *srds_div, *vco_freq_khz));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_VCO_FREQUENCY_INVALID));
    }

    /* Verify the auto-determined divider value. */
    if (auto_div != *srds_div) {
        EFUN_PRINTF(("ERROR: Conflicting PLL parameters:  refclk is %d Hz, %s option enabled, divider is 0x%08X, and VCO frequency is %d kHz.\n       Expected divider is 0x%08X\n",
                     *refclk_freq_hz, pll_option_e2s[pll_option], *srds_div, *vco_freq_khz, auto_div));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_CONFLICTING_PARAMETERS));
    }

    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_display_pll_to_divider(srds_access_t *sa__, uint32_t srds_div) {
    /* Adjust these to increase or decrease the number of digits to the right
     * of the decimal point.
     */
    const uint8_t decimal_digits = 4;
    const uint32_t ten_to_the_decimal_digits = 10000; /* 10**decimal_digits */

    /* Not a const, because of carry logic below. */
    uint16_t div_integer = SRDS_INTERNAL_GET_PLL_DIV_INTEGER(srds_div);

    if (SRDS_INTERNAL_IS_PLL_DIV_FRACTIONAL(srds_div)) {
        /* fraction_num will have this many bits (ending at bit 0). */
        const uint8_t  fraction_num_width = 28;
        const uint32_t fraction_num =(uint32_t)(SRDS_INTERNAL_GET_PLL_DIV_FRACTION_NUM(srds_div, fraction_num_width));

        /* Identify the number that, when printed with left-padded zeros,
         * becomes the digits to the right of the decimal point.
         *
         * This value can be obtained by dividing fraction_num by:
         *
         *     (2^fraction_num_width)/(10^decimal_digits)
         */
        const uint32_t divisor = (((1U << fraction_num_width) + (ten_to_the_decimal_digits>>1))
                                  / ten_to_the_decimal_digits);
        uint32_t fraction_as_int = (fraction_num + (divisor>>1)) / divisor;

        /* In case the rounding above caused the fractional portion to overflow
         * (e.g. 4.9999999999 becomes 5.0000), implement the carry into the
         * integer portion.
         */
        if (fraction_as_int >= ten_to_the_decimal_digits) {
            fraction_as_int -= ten_to_the_decimal_digits;
            ++div_integer;
        }

        EFUN_PRINTF(("%3d.%0*d", div_integer, decimal_digits, fraction_as_int));
    } else {
        const uint8_t left_spaces = (decimal_digits + 1) >> 1;
        COMPILER_REFERENCE(left_spaces);
        EFUN_PRINTF(("%*s%3d%*s", left_spaces, "", div_integer, decimal_digits - left_spaces + 1, ""));
    }
    return(ERR_CODE_NONE);
}
#endif /* SMALL_FOOTPRINT */
err_code_t blackhawk7_l2p2_INTERNAL_print_uc_dsc_error(srds_access_t *sa__, enum srds_pmd_uc_cmd_enum cmd) {
    INIT_SRDS_ERR_CODE
    uint32_t supp_info;

    ESTM(supp_info = (rd_uc_dsc_supp_info()) & 0xFF);
    switch (SUPP_INFO_TO_ERROR_CODE(supp_info)) {
      case UC_CMD_ERROR_INVALID_COMMAND:
        ESTM_PRINTF(("ERROR : UC reported invalid command %d.  (other_info = 0x%X)\n",
                     cmd, SUPP_INFO_TO_OTHER_INFO(supp_info)));
        break;
      case UC_CMD_ERROR_BUSY:
        ESTM_PRINTF(("ERROR : UC reported busy for command %d.  (other_info = 0x%X)\n",
                     cmd, SUPP_INFO_TO_OTHER_INFO(supp_info)));
        break;
      case UC_CMD_ERROR_GET_EYE_SAMPLE_ERROR:
        ESTM_PRINTF(("ERROR : UC reported error in getting eye sample.  (command %d, other_info = 0x%X)\n",
                     cmd, SUPP_INFO_TO_OTHER_INFO(supp_info)));
        break;
      case UC_CMD_ERROR_PRBS_NOT_LOCKED:
        ESTM_PRINTF(("ERROR : UC reported PRBS not locked.  (command %d, other_info = 0x%X)\n",
                     cmd, SUPP_INFO_TO_OTHER_INFO(supp_info)));
        break;
      case UC_CMD_ERROR_COMMAND_IN_PROGRESS:
        ESTM_PRINTF(("ERROR : UC reported command already in progress.  (command %d, other_info = 0x%X)\n",
                     cmd, SUPP_INFO_TO_OTHER_INFO(supp_info)));
        break;
      case UC_CMD_ERROR_INVALID_MODE:
        ESTM_PRINTF(("ERROR : UC reported invalid mode for command %d.  (other_info = 0x%X)\n",
                     cmd, SUPP_INFO_TO_OTHER_INFO(supp_info)));
        break;
      default:
        ESTM_PRINTF(("ERROR : UC reported unknown error 0x%X for command %d.  (other_info = 0x%X)\n",
                     SUPP_INFO_TO_ERROR_CODE(supp_info), cmd, SUPP_INFO_TO_OTHER_INFO(supp_info)));
    }
    /* Cleanup cmd register */
    EFUN(reg_wr_DSC_A_DSC_UC_CTRL(0x80));
    EFUN(wr_uc_dsc_data(0));

    return(ERR_CODE_NONE);
}
/******************************************/
/*  Serdes Register field Poll functions  */
/******************************************/

#ifndef CUSTOM_REG_POLLING
#ifndef SMALL_FOOTPRINT
/* poll for microcontroller to populate the dsc_data register */
err_code_t blackhawk7_l2p2_INTERNAL_poll_diag_done(srds_access_t *sa__, uint16_t *status, uint32_t timeout_ms) {
    INIT_SRDS_ERR_CODE
    uint8_t loop;

    if(!status) {
        return(blackhawk7_l2p2_error(sa__, ERR_CODE_BAD_PTR_OR_INVALID_INPUT));
    }

    for(loop=0;loop < 100; loop++) {
        ESTM(*status=rdv_usr_diag_status());

        if((*status & 0x8000) > 0) {
            return(ERR_CODE_NONE);
        }
        if(loop>10) {
            EFUN(USR_DELAY_US(10*timeout_ms));
        }
    }
 return(blackhawk7_l2p2_error(sa__, ERR_CODE_DIAG_TIMEOUT));
}
#endif /*SMALL_FOOTPRINT */


/** Poll for field "uc_dsc_ready_for_cmd" = 1 [Return Val => Error_code (0 = Polling Pass)] */
err_code_t blackhawk7_l2p2_INTERNAL_poll_uc_dsc_ready_for_cmd_equals_1(srds_access_t *sa__, uint32_t timeout_ms, enum srds_pmd_uc_cmd_enum cmd)
{
    INIT_SRDS_ERR_CODE
    /* read quickly for 10 tries */
    uint16_t loop = 0;
    uint16_t reset_state;

    for (loop = 0; loop < 100; loop++)
    {
        uint16_t rddata;
        ESTM(rddata = reg_rd_DSC_A_DSC_UC_CTRL());
        if (rddata & 0x0080) {    /* bit 7 is uc_dsc_ready_for_cmd */
            if (rddata & 0x0040) {  /* bit 6 is uc_dsc_error_found   */
                EFUN(blackhawk7_l2p2_INTERNAL_print_uc_dsc_error(sa__, cmd));
                return(blackhawk7_l2p2_error(sa__, ERR_CODE_UC_CMD_RETURN_ERROR));
            }
            return (ERR_CODE_NONE);
        }
        if(loop>10) {
            EFUN(USR_DELAY_US(10*timeout_ms));
        }
    }
    /* Check if ln_s_rstb is asserted by looking at the reset state, then give a warning and display the commands */
    ESTM(reset_state = rd_lane_dp_reset_state());
    if (reset_state & 0x0007) {
        EFUN_PRINTF(("DSC ready for command is not working; SerDes lane is probably reset!\n"));
        EFUN(reg_wr_DSC_A_DSC_UC_CTRL(0x80)); /* Cleanup after failure */
        return (ERR_CODE_NONE);
    }
    {
        EFUN_PRINTF(("%s ERROR : DSC ready for command is not working, applying workaround and getting debug info !\n", API_FUNCTION_NAME));
        /* print the triage info and reset the cmd interface */
        blackhawk7_l2p2_INTERNAL_print_triage_info(sa__, ERR_CODE_UC_CMD_POLLING_TIMEOUT, 1, 1, (uint16_t)__LINE__);
        /* artifically terminate the command to re-enable the command interface */
        EFUN(wr_uc_dsc_ready_for_cmd(0x1));
    }
    return (ERR_CODE_UC_CMD_POLLING_TIMEOUT);
}


#ifndef SMALL_FOOTPRINT
/* Poll for field "dsc_state" = DSC_STATE_UC_TUNE [Return Val => Error_code (0 = Polling Pass)] */
err_code_t blackhawk7_l2p2_INTERNAL_poll_dsc_state_equals_uc_tune(srds_access_t *sa__, uint32_t timeout_ms) {
    INIT_SRDS_ERR_CODE
    uint16_t loop;
    uint16_t dsc_state;
    /* poll 10 times to avoid longer delays later */
    for (loop = 0; loop < 100; loop++) {
        ESTM(dsc_state = rd_dsc_state());
        if (dsc_state == DSC_STATE_UC_TUNE) {
            return (ERR_CODE_NONE);
        }
        if(loop>10) {
            EFUN(USR_DELAY_US(10*timeout_ms));
        }
    }
    ESTM_PRINTF(("DSC_STATE = %d\n", rd_dsc_state()));
    return (blackhawk7_l2p2_error(sa__, ERR_CODE_POLLING_TIMEOUT));          /* Error Code for polling timeout */
}

#endif /*SMALL_FOOTPRINT */

/* Poll for field "micro_ra_initdone" = 1 [Return Val => Error_code (0 = Polling Pass)] */
err_code_t blackhawk7_l2p2_INTERNAL_poll_micro_ra_initdone(srds_access_t *sa__, uint32_t timeout_ms) {
    INIT_SRDS_ERR_CODE
    uint16_t loop, max_count;
    uint8_t result;

    max_count = 333;
    for (loop = 0; loop <= max_count; loop++) {
        ESTM(result = rdc_micro_ra_initdone());
        if (result) {
            return (ERR_CODE_NONE);
        }
        EFUN(USR_DELAY_US(3*timeout_ms));
    }
    return (blackhawk7_l2p2_error(sa__, ERR_CODE_POLLING_TIMEOUT));          /* Error Code for polling timeout */
}

#endif /* CUSTOM_REG_POLLING */

uint8_t blackhawk7_l2p2_INTERNAL_is_big_endian(void) {
    uint32_t one_u32 = 0x01000000;
    char * ptr = (char *)(&one_u32);
    const uint8_t big_endian = (ptr[0] == 1);
    return big_endian;
}

err_code_t blackhawk7_l2p2_INTERNAL_rdblk_callback(srds_access_t *sa__, void *arg, uint8_t byte_count, uint16_t data) {
    /* Never call blackhawk7_l2p2_INTERNAL_get_blackhawk7_l2p2_info_ptr_with_check() here */

    blackhawk7_l2p2_INTERNAL_rdblk_callback_arg_t * const cast_arg = (blackhawk7_l2p2_INTERNAL_rdblk_callback_arg_t *)arg;
    UNUSED(sa__);
    *(cast_arg->mem_ptr + get_endian_offset(cast_arg->mem_ptr)) = (uint8_t)(data & 0xFF);
    cast_arg->mem_ptr++;
    if (byte_count == 2) {
        *(cast_arg->mem_ptr + get_endian_offset(cast_arg->mem_ptr)) = (uint8_t)(data >> 8);
        cast_arg->mem_ptr++;
    }
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_ram_dump_callback(srds_access_t *sa__, void *arg, uint8_t byte_count, uint16_t data) {
    blackhawk7_l2p2_INTERNAL_ram_dump_state_t * const state_ptr = (blackhawk7_l2p2_INTERNAL_ram_dump_state_t *)arg;
    const uint8_t bytes_per_row=26;

    if (byte_count == 0) {
        if (state_ptr->line_start_index != state_ptr->index) {
            EFUN_PRINTF(("%*s    %d\n", 4*(bytes_per_row - state_ptr->index + state_ptr->line_start_index), "", state_ptr->line_start_index));
        }
        return (ERR_CODE_NONE);
    }
    if (byte_count == 1) {
#if defined(SMALL_FOOTPRINT)
        /* coverity[assigned_value] */
#endif
        data &= 0xFF;
    }

    if (state_ptr->index % bytes_per_row == 0) {
        state_ptr->line_start_index = state_ptr->index;
        EFUN_PRINTF(("\n%04x ", state_ptr->line_start_index));

    }
    EFUN_PRINTF(("%02x ", (uint8_t)(data & 0xFF)));
    EFUN_PRINTF(("%02x ", (data >> 8)));
    state_ptr->index = (uint16_t)(state_ptr->index + 2);

    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_rdblk_ram_callback(srds_access_t *sa__, void *arg, uint8_t byte_count, uint16_t data) {
    INIT_SRDS_ERR_CODE
    srds_info_t const * const blackhawk7_l2p2_info_ptr = blackhawk7_l2p2_INTERNAL_get_blackhawk7_l2p2_info_ptr_with_check(sa__); /* Needed for get_endian_offset_info_ptr() */
    blackhawk7_l2p2_INTERNAL_rdblk_ram_arg_t *  cast_arg = (blackhawk7_l2p2_INTERNAL_rdblk_ram_arg_t *)arg;
    blackhawk7_l2p2_INTERNAL_ram_dump_state_t * const state_ptr = (blackhawk7_l2p2_INTERNAL_ram_dump_state_t *)(cast_arg->dump_state_ptr);
    const int bytes_per_row = 26;
    SRDS_INFO_PTR_NULL_CHECK;

    if(cast_arg->ram_buff != NULL) {
        if (state_ptr->index % bytes_per_row == 0) {
            state_ptr->line_start_index = (state_ptr->index);
            if (state_ptr->index != 0){
                state_ptr->ram_idx++;
                state_ptr->count = 0;
            }

            state_ptr->count += USR_SNPRINTF((cast_arg->ram_buff + get_endian_offset_info_ptr(cast_arg->ram_buff)+(state_ptr->ram_idx * SRDS_DUMP_BUF_SIZE )+ state_ptr->count), (size_t)(SRDS_DUMP_BUF_SIZE - state_ptr->count - 1), "%04x ",(state_ptr->line_start_index) );

        }
        state_ptr->count += USR_SNPRINTF((cast_arg->ram_buff + get_endian_offset_info_ptr(cast_arg->ram_buff)+(state_ptr->ram_idx * SRDS_DUMP_BUF_SIZE )+ state_ptr->count), (size_t)(SRDS_DUMP_BUF_SIZE - state_ptr->count - 1), "%02x ", (uint8_t)(data&0xFF));

        state_ptr->index++;
        if (byte_count == 2) {
            state_ptr->count += USR_SNPRINTF((cast_arg->ram_buff + get_endian_offset_info_ptr(cast_arg->ram_buff)+(state_ptr->ram_idx * SRDS_DUMP_BUF_SIZE)+ state_ptr->count), (size_t)(SRDS_DUMP_BUF_SIZE - state_ptr->count - 1), "%02x ",(uint8_t)(data>>8));
            state_ptr->index++;
        }

        if(state_ptr->index == cast_arg->ram_size){
            state_ptr->count = 0;
            state_ptr->ram_idx++;
            *(cast_arg->ram_buff + get_endian_offset_info_ptr(cast_arg->ram_buff)+(state_ptr->ram_idx * SRDS_DUMP_BUF_SIZE) + state_ptr->count) = 0xA;
            state_ptr->ram_idx++;
            *(cast_arg->ram_buff + get_endian_offset_info_ptr(cast_arg->ram_buff)+(state_ptr->ram_idx * SRDS_DUMP_BUF_SIZE) + state_ptr->count) = 0x0;

        }

    }

    if (cast_arg->ram_buff == NULL) {
        EFUN(blackhawk7_l2p2_INTERNAL_ram_dump_callback(sa__, cast_arg->dump_state_ptr, byte_count,data));
    }


    return (ERR_CODE_NONE);
}

/************************************************************/
/*      Serdes IP RAM access - Lane RAM Variables           */
/*----------------------------------------------------------*/
/*   - through Micro Register Interface for PMD IPs         */
/*   - through Serdes FW DSC Command Interface for Gallardo */
/************************************************************/

/* This function returns the absolute address of lane RAM variables given the offset address and lane */
uint32_t _blackhawk7_l2p2_INTERNAL_get_addr_from_lane(srds_access_t *sa__, uint16_t addr, uint8_t lane) {
    uint32_t lane_var_ram_base=0, lane_var_ram_size=0;
    uint32_t lane_addr_offset = 0;
    uint16_t grp_ram_size=0,lane_count=0;
    srds_info_t const * const blackhawk7_l2p2_info_ptr = blackhawk7_l2p2_INTERNAL_get_blackhawk7_l2p2_info_ptr_with_check(sa__);

    if (blackhawk7_l2p2_info_ptr != NULL) {
        lane_var_ram_base = blackhawk7_l2p2_info_ptr->lane_var_ram_base;
        lane_var_ram_size = blackhawk7_l2p2_info_ptr->lane_var_ram_size;
        grp_ram_size = blackhawk7_l2p2_info_ptr->grp_ram_size;
        lane_count = blackhawk7_l2p2_info_ptr->lane_count;
        if(!lane_count) {
            return lane_addr_offset; /* To avoid a modulo by 0 exception */
        }
        lane_addr_offset = (uint32_t)(lane_var_ram_base+addr+ ((uint32_t)(lane%lane_count)*lane_var_ram_size) + (uint32_t)(grp_ram_size*blackhawk7_l2p2_INTERNAL_grp_idx_from_lane(lane)));
    }
    return(lane_addr_offset);
}

 /************************************************************/
 /*      Serdes IP RAM access - Micro RAM Variables           */
 /*----------------------------------------------------------*/
 /*   - through Micro Register Interface for PMD IPs         */
 /************************************************************/

 /* This function returns the absolute address of uc RAM variables given the offset address and lane */
 uint32_t _blackhawk7_l2p2_INTERNAL_get_uc_addr_from_lane(srds_access_t *sa__, uint16_t addr, uint8_t lane) {
     uint32_t micro_var_ram_base = 0;
     uint16_t grp_ram_size = 0;
     uint32_t uc_addr_offset = 0;
     srds_info_t const * const blackhawk7_l2p2_info_ptr = blackhawk7_l2p2_INTERNAL_get_blackhawk7_l2p2_info_ptr_with_check(sa__);

     if (blackhawk7_l2p2_info_ptr != NULL) {
         micro_var_ram_base = blackhawk7_l2p2_info_ptr->micro_var_ram_base;
         grp_ram_size = blackhawk7_l2p2_info_ptr->grp_ram_size;
         uc_addr_offset = (uint32_t)(micro_var_ram_base + addr + (uint32_t)(grp_ram_size*blackhawk7_l2p2_INTERNAL_grp_idx_from_lane(lane)));
     }
     return(uc_addr_offset);
 }

 /************************************************************/
 /*      Serdes IP RAM access - Core RAM Variables           */
 /*----------------------------------------------------------*/
 /*   - through Micro Register Interface for PMD IPs         */
 /*   - through Serdes FW DSC Command Interface for Gallardo */
 /************************************************************/

 /* This function returns the absolute address of core RAM variables given the offset address and lane */
 uint32_t _blackhawk7_l2p2_INTERNAL_get_addr_from_core(srds_access_t *sa__, uint16_t addr) {
     uint32_t core_var_ram_base=0;
     uint32_t core_addr_offset = 0;
     srds_info_t const * const blackhawk7_l2p2_info_ptr = blackhawk7_l2p2_INTERNAL_get_blackhawk7_l2p2_info_ptr_with_check(sa__);

     if (blackhawk7_l2p2_info_ptr != NULL) {
         core_var_ram_base = blackhawk7_l2p2_info_ptr->core_var_ram_base;
         core_addr_offset = core_var_ram_base + addr;
     }
     return(core_addr_offset);
}


err_code_t blackhawk7_l2p2_INTERNAL_rdblk_ram_read_callback(srds_access_t * sa__,void *arg,uint8_t byte_count,uint16_t data) {
    INIT_SRDS_ERR_CODE
    srds_info_t const * const blackhawk7_l2p2_info_ptr = blackhawk7_l2p2_INTERNAL_get_blackhawk7_l2p2_info_ptr_with_check(sa__); /* Needed for get_endian_offset_info_ptr() */
    blackhawk7_l2p2_INTERNAL_rdblk_ram_arg_t * const cast_arg = (blackhawk7_l2p2_INTERNAL_rdblk_ram_arg_t *)arg;
    SRDS_INFO_PTR_NULL_CHECK;
    if(cast_arg->mem_ptr != NULL) {
        *(cast_arg->mem_ptr + get_endian_offset_info_ptr(cast_arg->mem_ptr)) = (uint8_t)(data & 0xFF);
        cast_arg->mem_ptr++;
        if (byte_count == 2) {
            *(cast_arg->mem_ptr + get_endian_offset_info_ptr(cast_arg->mem_ptr)) = (uint8_t)(data >> 8);
            cast_arg->mem_ptr++;
        }
    }
    if (cast_arg->mem_ptr == NULL) {
        EFUN(blackhawk7_l2p2_INTERNAL_ram_dump_callback(sa__, cast_arg->dump_state_ptr, byte_count,data));
    }
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_rdblk_uc_generic_ram(srds_access_t *sa__,
                                                uint32_t block_addr,
                                                uint32_t block_size,
                                                uint32_t start_offset,
                                                uint32_t cnt,
                                                void *arg,
                                                err_code_t (*callback)(srds_access_t *, void *, uint8_t, uint16_t)) {
    /* Never call blackhawk7_l2p2_INTERNAL_get_blackhawk7_l2p2_info_ptr_with_check() here */

    INIT_SRDS_ERR_CODE
    err_code_t Exit_Status = ERR_CODE_NONE;
    uint32_t read_val = 0;
    uint8_t defecit = 0;
    uint32_t addr = block_addr + start_offset;
    if (cnt == 0) {
        return (ERR_CODE_NONE);
    }

    /* Check for bad start offset and block size. */
    if (start_offset >= block_size) {
        return (ERR_CODE_BAD_PTR_OR_INVALID_INPUT);
    }


    while (cnt > 0) {
        /* Determine how many bytes to read before wrapping back to start of block. */
        uint32_t block_cnt = (uint32_t)(SRDS_MIN(cnt, block_addr + block_size - addr));
        cnt = cnt - block_cnt;

            /* Set up the word reads. */
            CFUN(wrc_micro_autoinc_rdaddr_en(1));
            CFUN(wrc_micro_ra_rddatasize(0x1));                     /* Select 16bit read datasize */
            CFUN(wrc_micro_ra_rdaddr_msw((uint16_t)(addr >> 16)));              /* Upper 16bits of RAM address to be read */
            CFUN(wrc_micro_ra_rdaddr_lsw(addr & 0xFFFE));           /* Lower 16bits of RAM address to be read */

            /* Read the leading byte, if starting at an odd address. */
            if ((addr & 1) == 1) {
                CSTM(read_val |= (uint32_t)((rdc_micro_ra_rddata_lsw() >> 8) << defecit));
                if (defecit == 8) {
                    CFUN(callback(sa__, arg, 2, (uint16_t)read_val));
                    read_val = 0;
                }
                /* We just read a byte.  This toggles the defecit from 0 to 8 or from 8 to 0. */
                defecit ^= 8;
                --block_cnt;
            }

            /* Read the whole words, and call the callback with two bytes at a time. */
            while (block_cnt >= 2) {
                CSTM(read_val |= (uint32_t)(rdc_micro_ra_rddata_lsw() << defecit));
                CFUN(callback(sa__, arg, 2, (uint16_t)read_val));
                read_val >>= 16;
                /* We just read two bytes.  This preserves whatever defecit (8 or 0) is there. */
                block_cnt -= 2;
            }

            /* Read the trailing byte, if leftover after reading whole words. */
            if (block_cnt > 0) {
                CSTM(read_val |= (uint32_t)((rdc_micro_ra_rddata_lsw() & 0xFF) << defecit));
                if (defecit == 8) {
                    CFUN(callback(sa__, arg, 2, (uint16_t)read_val));
                    read_val = 0;
                }
                /* We just read a byte.  This toggles the defecit from 0 to 8 or from 8 to 0. */
                defecit ^= 8;
            }
        addr = block_addr;
    }

    /* If a final byte is left behind, then call the callback with it. */
    if (defecit > 0) {
        CFUN(callback(sa__, arg, 1, (uint16_t)read_val));
    }

Exit:
    return(Exit_Status);
}


#ifndef SMALL_FOOTPRINT
err_code_t blackhawk7_l2p2_INTERNAL_rdblk_uc_generic_ram_descending(srds_access_t *sa__,
                                                           uint32_t block_addr,
                                                           uint32_t block_size,
                                                           uint32_t start_offset,
                                                           uint32_t cnt,
                                                           void *arg,
                                                           err_code_t (*callback)(srds_access_t *, void *, uint8_t, uint16_t)) {
    INIT_SRDS_ERR_CODE
    uint32_t read_val = 0;
    uint8_t defecit = 0;
    uint32_t addr = block_addr + start_offset;
    uint16_t configured_addr_msw = (uint16_t)((addr >> 16) + 1);

    if (cnt == 0) {
        return (ERR_CODE_NONE);
    }

    /* Check for bad start offset and block size. */
    if (start_offset >= block_size) {
        return (ERR_CODE_BAD_PTR_OR_INVALID_INPUT);
    }

    EFUN(wrc_micro_autoinc_rdaddr_en(0));
    EFUN(wrc_micro_ra_rddatasize(0x1));                         /* Select 16bit read datasize */

    while (cnt > 0) {
        /* Determine how many bytes to read before wrapping back to end of block. */
        uint32_t block_cnt = (uint32_t)(SRDS_MIN(cnt, start_offset+1));
        cnt = cnt - block_cnt;

        while (block_cnt > 0) {
            const uint16_t addr_msw = (uint16_t)(addr >> 16);
            uint16_t read_val2;
            if (addr_msw != configured_addr_msw) {
                EFUN(wrc_micro_ra_rdaddr_msw(addr_msw));        /* Upper 16bits of RAM address to be read */
                configured_addr_msw = addr_msw;
            }

            EFUN(wrc_micro_ra_rdaddr_lsw(addr & 0xFFFE));       /* Lower 16bits of RAM address to be read */
            ESTM(read_val2 = rdc_micro_ra_rddata_lsw());

            if (((addr & 1) == 1) && (block_cnt >= 2)) {
                /* Reading two bytes.  Since we're reading in descending address order, they
                 * will be reversed before they are sent out. */
                read_val = read_val | (uint32_t)((((read_val2 & 0xFF) << 8) | (read_val2 >> 8)) << defecit);
                EFUN(callback(sa__, arg, 2, (uint16_t)read_val));
                read_val >>= 16;
                /* We just read two bytes.  This preserves whatever defecit (8 or 0) is there. */
                block_cnt -= 2;
                addr -= 2;
            }
            else {
                if ((addr & 1) == 1) {
                    /* Reading upper byte of word. */
                    read_val = read_val | (uint32_t)((read_val2 >> 8) << defecit);
                } else {
                    /* Reading lower byte of word. */
                    read_val = read_val | (uint32_t)((read_val2 & 0xFF) << defecit);
                }
                if (defecit == 8) {
                    EFUN(callback(sa__, arg, 2, (uint16_t)read_val));
                    read_val = 0;
                }
                /* We just read a byte.  This toggles the defecit from 0 to 8 or from 8 to 0. */
                defecit ^= 8;
                --block_cnt;
                --addr;
            }
        }

        addr = block_addr + block_size - 1;
        start_offset = block_size - 1;
    }

    /* If a final byte is left behind, then call the callback with it. */
    if (defecit > 0) {
        EFUN(callback(sa__, arg, 1, (uint16_t)read_val));
    }

    return(ERR_CODE_NONE);
}
#endif /*SMALL_FOOTPRINT */

uint8_t blackhawk7_l2p2_INTERNAL_grp_idx_from_lane(uint8_t lane) {
    UNUSED(lane);
    return(0);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_lms_thresh_bin(srds_access_t *sa__, int8_t *lms_thresh_bin) {
    INIT_SRDS_ERR_CODE
    ESTM(*lms_thresh_bin = (int8_t)rd_afe_lms_thresh_bin());
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_read_cal_error(srds_access_t *sa__, int8_t *lms_err, int8_t *phase_err, int8_t *data_err, int8_t *max_data_err) {
    INIT_SRDS_ERR_CODE
     ESTM(*lms_err   = rdv_usr_sts_lms_cal_error());
     ESTM(*phase_err = rdv_usr_sts_phase_cal_error());
     ESTM(*data_err  = rdv_usr_sts_data_cal_error());
     ESTM(*max_data_err  = rdv_usr_sts_max_data_cal_error());
    return(ERR_CODE_NONE);
}

#ifndef SMALL_FOOTPRINT
err_code_t blackhawk7_l2p2_INTERNAL_clk4sync_div2_sequence(srds_access_t *sa__, uint8_t enable) {
    INIT_SRDS_ERR_CODE
    uint8_t pll_selected = 0;
    uint8_t pll_orig = 0;
    uint8_t pll_lock = 0;
    uint8_t pll_lock_chg = 0;
    if (enable) {
        /* Check if selected pll is locked */
        ESTM(pll_orig = blackhawk7_l2p2_acc_get_pll_idx(sa__));
        ESTM(pll_selected = rd_rx_pll_select());
        EFUN(blackhawk7_l2p2_acc_set_pll_idx(sa__,pll_selected));
        EFUN(blackhawk7_l2p2_INTERNAL_pll_lock_status(sa__, &pll_lock, &pll_lock_chg));

        if (pll_lock) {
            EFUN(wrc_clk4sync_div2_s_comclk_sel(0x1)); /* Reset clk4sync_div2 clock domain to use comclk (slow clock) */
            EFUN(wrc_clk4sync_div2_vco_select(pll_selected));
            EFUN(wrc_clk4sync_div2_en(0x1)); /* 1: div2 enabled */
            EFUN(wrc_clk4sync_div2_s_comclk_sel(0x0)); /* Switch clk4sync_div2 clock domain to use VCO divided clk (fast clock) */
            EFUN(blackhawk7_l2p2_acc_set_pll_idx(sa__, pll_orig));
        }
        else {
            EFUN_PRINTF(("Selected PLL not locked for PRBS error analyzer!\n"));
            EFUN(blackhawk7_l2p2_acc_set_pll_idx(sa__, pll_orig));
            return (ERR_CODE_INVALID_PRBS_ERR_ANALYZER_NO_PLL_LOCK);
        }
    }
    else {
        EFUN(wrc_clk4sync_div2_s_comclk_sel(0x1)); /* Switch clk4sync_div2 clock domain to use comclk (slow clock) */
        EFUN(wrc_clk4sync_div2_en(0x0)); /* 0: disable to save power */
    }

    return (ERR_CODE_NONE);
}
#endif /* SMALL_FOOTPRINT */


err_code_t blackhawk7_l2p2_INTERNAL_read_res_error(srds_access_t *sa__, int8_t res_dac4ck_err[][RES_ERROR_NUM_ILV], uint8_t sgn_chn_cnt[][RES_ERROR_NUM_ILV]) {
    INIT_SRDS_ERR_CODE
    int8_t hoff_res;
    uint8_t i,j;

    for(i = 0; i < RES_ERROR_NUM_SLICER; i++) {
        for(j = 0; j < RES_ERROR_NUM_ILV; j++) {
            ESTM(hoff_res = rdv_usr_status_hoff_res(i,j));
            res_dac4ck_err[i][j] = hoff_res >> 4;
            sgn_chn_cnt[i][j]   = hoff_res & 0x0F;
        }
    }

    return (ERR_CODE_NONE);
}

#ifndef SMALL_FOOTPRINT
err_code_t blackhawk7_l2p2_INTERNAL_poll_dbgfb_idx_lock(srds_access_t *sa__, uint8_t timeout_ms) {
  INIT_SRDS_ERR_CODE
  uint32_t loop, max_loop = 10;
  uint8_t idx_lock = 0;

  /* poll for first 10 times and then wait for timeout_ms before polling */
  for (loop = 0; loop < max_loop; loop++) {
      ESTM(idx_lock = rd_dbg_fdbk_idx_lock());
      if (idx_lock) {
          return (ERR_CODE_NONE);
      }
  }
  /* polled for 10 times, wait for timeout_ms right here before polling the register */
  EFUN(USR_DELAY_US((uint32_t)(timeout_ms * 1000)));
  ESTM(idx_lock = rd_dbg_fdbk_idx_lock());
  if (idx_lock) {
      return (ERR_CODE_NONE);
  } else {
      ESTM_PRINTF(("!!!!ERROR!!!! polling for dbgfb idx lock timedout after %d ms \n", timeout_ms));
      /* Error Code for polling timeout */
      return (blackhawk7_l2p2_error(sa__, ERR_CODE_POLLING_TIMEOUT));
  }
}

err_code_t blackhawk7_l2p2_get_dbgfb_summary(srds_access_t *sa__, blackhawk7_l2p2_dbgfb_cfg_st *dbgfb_cfg) {
    INIT_SRDS_ERR_CODE
    uint32_t d_0_n1, d_0_0, d_0_p1, d_1_n1, d_1_0, d_1_p1;
    int32_t pdet, ndet, tdet;
    enum blackhawk7_l2p2_rx_pam_mode_enum pam_mode = NRZ;

    EFUN(blackhawk7_l2p2_INTERNAL_get_rx_pam_mode(sa__, &pam_mode));
    if (pam_mode == NRZ) {
        EFUN_PRINTF(("!!!!ERROR!!!! rx_pam_mode is set to NRZ , blackhawk7_l2p2_get_dbgfb_summary cannot continue\n"));
        return(ERR_CODE_INVALID_RX_PAM_MODE);
    }
    EFUN(wr_dbg_fdbk_en(1));
    EFUN(wr_fdbk_counting_mode(0));
    EFUN(wr_dbg_fdbk_data_threshold(dbgfb_cfg->y));
    EFUN(wr_dbg_fdbk_data_sel(1));
    if (dbgfb_cfg->x) {
        EFUN(wr_inlv_idx(228));
        EFUN(wr_dbg_fdbk_idx((uint8_t)(dbgfb_cfg->x -1)));
        EFUN(wr_frc_index_diffprec(1));
        EFUN(blackhawk7_l2p2_INTERNAL_poll_dbgfb_idx_lock(sa__, 100));
        EFUN(wr_frc_index_diffprec(0));
        EFUN(wr_dbg_fdbk_idx_monitor_en(0));
        EFUN(wr_dbg_fdbk_idx_monitor_en(1));
    } else {
        EFUN(wr_dbg_fdbk_idx(1));
        EFUN(wr_dbg_fdbk_idx(0));
        EFUN(wr_dbg_fdbk_idx_monitor_en(0));
    }
    
    EFUN(USR_DELAY_US(dbgfb_cfg->time_in_us));

    EFUN(wr_dbg_fdbk_en(0));
    ESTM(d_1_n1 = rd_dbg_fdbk_counter_0());

    ESTM(d_1_0  = rd_dbg_fdbk_counter_1());
    ESTM(d_1_p1 = rd_dbg_fdbk_counter_2());
    ESTM(d_0_n1 = rd_dbg_fdbk_counter_3());
    ESTM(d_0_0  = rd_dbg_fdbk_counter_4());
    ESTM(d_0_p1 = rd_dbg_fdbk_counter_5());

    tdet  = (int32_t)(d_1_n1 + d_0_p1-d_0_n1 - d_1_p1);
    pdet  = (int32_t)(d_1_n1 + d_1_0 + d_1_p1);
    ndet  = (int32_t)(d_0_n1 + d_0_0 + d_0_p1);
    dbgfb_cfg->data2 = pdet;
    dbgfb_cfg->data3 = ndet;
    dbgfb_cfg->data1 = tdet;
    return ERR_CODE_NONE;
}



err_code_t blackhawk7_l2p2_dbgfb_collect_stats(srds_access_t *sa__, uint32_t time_in_us, blackhawk7_l2p2_dbgfb_stats_st *dbgfb_stats) {
    INIT_SRDS_ERR_CODE
    EFUN(blackhawk7_l2p2_dbgfb_collect_stats_api_method(sa__, time_in_us, dbgfb_stats));
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_dbgfb_collect_stats_api_method(srds_access_t *sa__, uint32_t time_in_us, blackhawk7_l2p2_dbgfb_stats_st *dbgfb_stats) {
    INIT_SRDS_ERR_CODE
    uint8_t y, x;
    uint8_t max_y ,max_x;
    enum blackhawk7_l2p2_rx_pam_mode_enum pam_mode = NRZ;
    uint8_t pam4es_en = 0;
    blackhawk7_l2p2_dbgfb_cfg_st dbgfb_cfg = DBGFB_CFG_ST_INIT;

    EFUN(blackhawk7_l2p2_INTERNAL_get_rx_pam_mode(sa__, &pam_mode));
    if (pam_mode == NRZ) {
        EFUN_PRINTF(("ERROR: %s rx_pam_mode is set to NRZ, cannot continue\n", API_FUNCTION_NAME));
        return(ERR_CODE_INVALID_RX_PAM_MODE);
    }
    pam4es_en = (pam_mode==PAM4_ER);
    max_y = pam4es_en ? 6 : 3;

    {
        max_x = srds_X_width;
    }
    /* backup the measure time and pam4es_en info */
    dbgfb_stats->time_in_us = time_in_us;
    dbgfb_stats->pam4es_en  = pam4es_en;

    for (y=0; y < max_y; y++){
        for (x = 0; x < max_x; x++){
            dbgfb_cfg.y = y;
            dbgfb_cfg.x = x;
            dbgfb_cfg.time_in_us = time_in_us;
            dbgfb_cfg.data1 = 0;
            dbgfb_cfg.data2 = 0;
            dbgfb_cfg.data3 = 0;
            EFUN(blackhawk7_l2p2_get_dbgfb_summary(sa__, &dbgfb_cfg));
            dbgfb_stats->time_in_us = time_in_us;
            dbgfb_stats->data.data1[x][y] = dbgfb_cfg.data1;
            dbgfb_stats->data.data2[x][y] = dbgfb_cfg.data2;
            dbgfb_stats->data.data3[x][y] = dbgfb_cfg.data3;
            dbgfb_stats->data.data4[x][y] = (int32_t)(dbgfb_stats->data.data2[x][y] - dbgfb_stats->data.data3[x][y]);

        }
    }

    return ERR_CODE_NONE;
}
#endif /* SMALL_FOOTPRINT */

err_code_t blackhawk7_l2p2_INTERNAL_display_info_table (srds_access_t *sa__) {
    INIT_SRDS_ERR_CODE
    srds_info_t const * const blackhawk7_l2p2_info_ptr = blackhawk7_l2p2_INTERNAL_get_blackhawk7_l2p2_info_ptr_with_check(sa__);
    EFUN(blackhawk7_l2p2_INTERNAL_match_ucode_from_info(sa__, blackhawk7_l2p2_info_ptr));

    EFUN_PRINTF(("\n********** SERDES INFO TABLE DUMP **********\n"));
    EFUN_PRINTF(("signature                 = 0x%X\n", blackhawk7_l2p2_info_ptr->signature));
    EFUN_PRINTF(("diag_mem_ram_base         = 0x%X\n", blackhawk7_l2p2_info_ptr->diag_mem_ram_base));
    EFUN_PRINTF(("diag_mem_ram_size         = 0x%X\n", blackhawk7_l2p2_info_ptr->diag_mem_ram_size));
    EFUN_PRINTF(("core_var_ram_base         = 0x%X\n", blackhawk7_l2p2_info_ptr->core_var_ram_base));
    EFUN_PRINTF(("core_var_ram_size         = 0x%X\n", blackhawk7_l2p2_info_ptr->core_var_ram_size));
    EFUN_PRINTF(("lane_var_ram_base         = 0x%X\n", blackhawk7_l2p2_info_ptr->lane_var_ram_base));
    EFUN_PRINTF(("lane_var_ram_size         = 0x%X\n", blackhawk7_l2p2_info_ptr->lane_var_ram_size));
    EFUN_PRINTF(("trace_mem_ram_base        = 0x%X\n", blackhawk7_l2p2_info_ptr->trace_mem_ram_base));
    EFUN_PRINTF(("trace_mem_ram_size        = 0x%X\n", blackhawk7_l2p2_info_ptr->trace_mem_ram_size));
    EFUN_PRINTF(("micro_var_ram_base        = 0x%X\n", blackhawk7_l2p2_info_ptr->micro_var_ram_base));
    EFUN_PRINTF(("lane_count                = 0x%X\n", blackhawk7_l2p2_info_ptr->lane_count));
    EFUN_PRINTF(("trace_memory_descending_writes = 0x%X\n", blackhawk7_l2p2_info_ptr->trace_memory_descending_writes));
    EFUN_PRINTF(("micro_count               = 0x%X\n", blackhawk7_l2p2_info_ptr->micro_count));
    EFUN_PRINTF(("micro_var_ram_size        = 0x%X\n", blackhawk7_l2p2_info_ptr->micro_var_ram_size));
    EFUN_PRINTF(("grp_ram_size              = 0x%X\n", blackhawk7_l2p2_info_ptr->grp_ram_size));
    EFUN_PRINTF(("ucode_version             = 0x%X\n", blackhawk7_l2p2_info_ptr->ucode_version));
    EFUN_PRINTF(("info_table_version        = 0x%X\n", blackhawk7_l2p2_info_ptr->info_table_version));
    EFUN_PRINTF(("silicon_version           = 0x%X\n", blackhawk7_l2p2_info_ptr->silicon_version));
    EFUN_PRINTF(("is_big_endian             = 0x%X\n", blackhawk7_l2p2_info_ptr->is_big_endian));

    return (ERR_CODE_NONE);
}
err_code_t blackhawk7_l2p2_INTERNAL_get_logical_tx_lane_addr(srds_access_t *sa__, uint8_t physical_tx_lane, uint8_t *logical_tx_lane) {
    INIT_SRDS_ERR_CODE
    if(logical_tx_lane == NULL) return (ERR_CODE_BAD_PTR_OR_INVALID_INPUT);
    switch(physical_tx_lane) {
        case 0:
            ESTM(*logical_tx_lane = rdc_tx_lane_addr_0());
            break;
        case 1:
            ESTM(*logical_tx_lane = rdc_tx_lane_addr_1());
            break;
        default:
            return (ERR_CODE_BAD_PTR_OR_INVALID_INPUT);
    }
    return (ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_get_logical_rx_lane_addr(srds_access_t *sa__, uint8_t physical_rx_lane, uint8_t *logical_rx_lane) {
    INIT_SRDS_ERR_CODE
    if(logical_rx_lane == NULL) return (ERR_CODE_BAD_PTR_OR_INVALID_INPUT);
    switch(physical_rx_lane) {
        case 0:
            ESTM(*logical_rx_lane = rdc_rx_lane_addr_0());
            break;
        case 1:
            ESTM(*logical_rx_lane = rdc_rx_lane_addr_1());
            break;
        default:
            return (ERR_CODE_BAD_PTR_OR_INVALID_INPUT);
    }
    return (ERR_CODE_NONE);
}

#ifndef SMALL_FOOTPRINT
/****************/
/*  DBstop API  */
/****************/
static err_code_t _print_breakpoint_warning(srds_access_t *sa__) {
    EFUN_PRINTF(("*******************************************************************************\n"));
    EFUN_PRINTF(("* WARNING: SRDS_BREAKPOINT functionality is being used.                       *\n"));
    EFUN_PRINTF(("*                                                                             *\n"));
    EFUN_PRINTF(("*          Use of this feature may affect SERDES performance!                 *\n"));
    EFUN_PRINTF(("*******************************************************************************\n"));
    return (ERR_CODE_NONE);
}
err_code_t blackhawk7_l2p2_INTERNAL_en_breakpoint(srds_access_t *sa__, uint8_t breakpoint) {
    INIT_SRDS_ERR_CODE
    EFUN(_print_breakpoint_warning(sa__));
    EFUN(wrv_usr_dbstop_enable(breakpoint));
    return (ERR_CODE_NONE);
}
err_code_t blackhawk7_l2p2_INTERNAL_goto_breakpoint(srds_access_t *sa__, uint8_t breakpoint) {
    INIT_SRDS_ERR_CODE
    uint8_t already_stopped;

    ESTM(already_stopped = rdv_usr_dbstopped());      /* find out if breakpoint is already reached */
    EFUN(wrv_usr_dbstop_enable(breakpoint));
    if (already_stopped) {WRV_USR_DBSTOPPED_TO_0;}    /* if already stopped, let it continue */
    return (ERR_CODE_NONE);
}
err_code_t blackhawk7_l2p2_INTERNAL_rd_breakpoint(srds_access_t *sa__) {
    INIT_SRDS_ERR_CODE
    uint8_t val;
    uint8_t core;
    uint8_t lane;
#ifdef SMALL_FOOTPRINT
    UNUSED(core);
    UNUSED(lane);
#endif
    ESTM(core = blackhawk7_l2p2_acc_get_core(sa__));
    ESTM(lane = blackhawk7_l2p2_acc_get_lane(sa__));
    ESTM(val = rdv_usr_dbstopped());
    if(val > 0) {
        EFUN_PRINTF(("Stopped at Breakpoint %d on Core=%d, Lane=%d\n", val, core, lane));
    }
    else {
        EFUN_PRINTF(("Not currently stopped at a breakpoint.\n"));
    }
    return (ERR_CODE_NONE);
}
err_code_t blackhawk7_l2p2_INTERNAL_dis_breakpoint(srds_access_t *sa__) {
    INIT_SRDS_ERR_CODE
    EFUN(wrv_usr_dbstop_enable(0));
    WRV_USR_DBSTOPPED_TO_0;
    return (ERR_CODE_NONE);
}

#endif /* SMALL_FOOTPRINT */


int8_t blackhawk7_l2p2_INTERNAL_dfe_tap_sgb2sg(int8_t sgb){
    int16_t local_sgb = 0;
    
    local_sgb = (int16_t)sgb;
    switch (local_sgb){
    /*switch (sgb){*/
    case 2: return 3;
    case 3: return 2;
    case 6: return 7;
    case 7: return 6;
    case -2: return -3;
    case -3: return -2;
    case -6: return -7;
    case -7: return -6;
    default: return sgb;
    }
}

err_code_t blackhawk7_l2p2_INTERNAL_fit_second_order(srds_access_t *sa__, uint8_t n, USR_DOUBLE *x, USR_DOUBLE *y, USR_DOUBLE *a) {
#ifdef SERDES_API_FLOATING_POINT
    uint8_t    i, j, k;
    USR_DOUBLE Ex[5]     = { 0.0 }; /* elements of normal matrix */
    USR_DOUBLE Eb[3][4]  = { {0.0} }; /* augmented matrix */
    USR_DOUBLE Ey[3]     = { 0.0 };
    UNUSED(sa__);

    if ( x == NULL || y == NULL || a == NULL ) {
        return (ERR_CODE_BAD_PTR_OR_INVALID_INPUT);
    }
    if ( n < 2 ) {
        EFUN_PRINTF(("Not enough samples.\n"));
        return (ERR_CODE_BAD_PTR_OR_INVALID_INPUT);
    }

    for (i=0; i<=4; i++) {
        Ex[i] = 0;
        for (j=0; j<n; j++) {
            Ex[i] = Ex[i] + pow(x[j], i);
        }
    }

    for (i=0; i<=2; i++) {
        Ey[i] = 0;
        for (j=0; j<n; j++) {
            Ey[i] = Ey[i] + pow(x[j], i) * y[j];
        }
    }

    for (i=0; i<=2; i++) {
        for (j=0; j<=2; j++) {
            Eb[i][j] = Ex[i+j];
        }
        Eb[i][3] = Ey[i];
    }

    /* apply gauss elimination to get the coefficents */
    for (i=0; i<2; i++) {
        /* partial pivoting */
        for (k=(uint8_t)(i+1); k<3; k++) {
            /* swap if diagonal element(absolute) is smaller than any terms below it */
             if (fabs(Eb[i][j]) < fabs(Eb[k][i])) {
                 for (j=0; j<4; j++) {
                     USR_DOUBLE temp;
                     temp = Eb[i][j];
                     Eb[i][j] = Eb[k][j];
                     Eb[k][j] = temp;
                 }
            }
        }
        /* gauss elimination */
        for (k=(uint8_t)(i+1); k<3; k++) {
            USR_DOUBLE term = Eb[k][i]/Eb[i][i];
            for (j=0; j<4; j++) {
                Eb[k][j] = Eb[k][j] - term * Eb[i][j];
            }
        }
    }

    /* back substitution */
    for (i=3; i>0; i--) {
        a[i-1] = Eb[i-1][3];
        for (j=i; j<3; j++) {
            a[i-1] = a[i-1] - Eb[i-1][j] * a[j];
        }
        a[i-1] = a[i-1]/Eb[i-1][i-1];
    }

    return (ERR_CODE_NONE);
#else
    UNUSED(n);
    UNUSED(x);
    UNUSED(y);
    UNUSED(a);
    USR_PRINTF(("%s : This function needs SERDES_API_FLOATING_POINT define to operate \n", API_FUNCTION_NAME));
    return(blackhawk7_l2p2_error(sa__, ERR_CODE_BAD_PTR_OR_INVALID_INPUT));
#endif /* SERDES_API_FLOATING_POINT */
}

err_code_t blackhawk7_l2p2_INTERNAL_is_flr_supported(srds_access_t *sa__, uint8_t *flr_support) {
    INIT_SRDS_ERR_CODE
    srds_info_t * const blackhawk7_l2p2_info_ptr = blackhawk7_l2p2_INTERNAL_get_blackhawk7_l2p2_info_ptr_with_check(sa__);
    EFUN(blackhawk7_l2p2_INTERNAL_match_ucode_from_info(sa__, blackhawk7_l2p2_info_ptr));

    *flr_support = (blackhawk7_l2p2_info_ptr->lane_var_ram_size >= 0x950);
    return ERR_CODE_NONE;
}



#if !defined(SMALL_FOOTPRINT)
err_code_t blackhawk7_l2p2_INTERNAL_poll_diag_data(srds_access_t *sa__, const srds_info_t *blackhawk7_l2p2_info_ptr, uint16_t *status,
                                          uint8_t * diag_rd_ptr, uint8_t byte_count, uint32_t timeout_ms)
{
    INIT_SRDS_ERR_CODE
    const uint32_t lane_diag_size = blackhawk7_l2p2_info_ptr->diag_mem_ram_size;
    uint16_t loop;

    if(!status || !diag_rd_ptr) {
        return(blackhawk7_l2p2_error(sa__, ERR_CODE_BAD_PTR_OR_INVALID_INPUT));
    }

    *diag_rd_ptr = 0;

    /** If the byte_count is too high, then there might be problems not updating
     *  the read pointer fast enough.
     */
    if (byte_count > (lane_diag_size / 2)) {
        EFUN_PRINTF(("\nERROR : blackhawk7_l2p2_INTERNAL_poll_diag_data() has excessive byte count of %d.\n", byte_count));
        return (blackhawk7_l2p2_error(sa__, ERR_CODE_DIAG_TIMEOUT));
    }

    ESTM(*diag_rd_ptr = rdv_usr_diag_rd_ptr());

    /* Wait until byte_count bytes are available to be read in the diagnostic memory. */
    loop = 0;
    while (1) {
        uint8_t diag_wr_ptr, full_count;

        ESTM(diag_wr_ptr = rdv_usr_diag_wr_ptr());
        if (diag_wr_ptr >= *diag_rd_ptr) {
            full_count = (uint8_t)(diag_wr_ptr - *diag_rd_ptr);
        } else {
            full_count = (uint8_t)((uint16_t)diag_wr_ptr + lane_diag_size - *diag_rd_ptr);
        }
        if (full_count >= byte_count) {
            break;
        }

        ++loop;
        if (loop > 10) {
            EFUN(USR_DELAY_US(10*timeout_ms));
        }
        if (loop > 1000) {
            return(blackhawk7_l2p2_error(sa__, ERR_CODE_DIAG_TIMEOUT));
        }
    }
    ESTM(*status = rdv_usr_diag_status() & 0xFF);
    return(ERR_CODE_NONE);
}

err_code_t blackhawk7_l2p2_INTERNAL_eye_margin_proj_start(srds_access_t *sa__, uint8_t ber_scan_mode, uint8_t timer_control, uint8_t max_error_control, int16_t *offset_start) {
    INIT_SRDS_ERR_CODE
    uint8_t lane = blackhawk7_l2p2_acc_get_lane(sa__);
    enum blackhawk7_l2p2_rx_pam_mode_enum pam_mode = NRZ;
    EFUN(blackhawk7_l2p2_INTERNAL_get_rx_pam_mode(sa__, &pam_mode));

    if(pam_mode != NRZ) {
        EFUN_PRINTF(("Lane %d ERROR: NRZ eye margin projection is only available in NRZ mode\n", lane));
        return(ERR_CODE_INVALID_RX_PAM_MODE);
    }
    /* Below 'DIAG_VERBOSE' level is intended to be modified only within a debug */
    /* session immediately after a breakpoint, and to retain its state only */
    /* through function exit:  therefore it must be 'volatile' to prevent a */
    /* compiler from eliding code conditioned on it, but NOT 'static'.      */

    if(DIAG_VERBOSE > 2) EFUN_PRINTF(("lane %d: start begin\n", lane));
    EFUN(blackhawk7_l2p2_start_ber_scan_test(sa__, ber_scan_mode, timer_control, max_error_control));
    ESTM(*offset_start = (int16_t)rd_uc_dsc_data());
    {
        int16_t nlmv_val = 0;
        afe_override_slicer_sel_t slicer = INVALID_SLICER;
        EFUN(blackhawk7_l2p2_INTERNAL_ladder_setting_to_mV(sa__, *offset_start, 0, slicer, &nlmv_val));
        if(DIAG_VERBOSE > 2) EFUN_PRINTF(("lane %d: offset_start = %d:%dmV\n",lane, *offset_start, nlmv_val));
    }
    if(DIAG_VERBOSE > 2) EFUN_PRINTF(("lane %d: start done\n", lane));
    return ERR_CODE_NONE;
}

err_code_t blackhawk7_l2p2_INTERNAL_eye_margin_proj_end(srds_access_t *sa__, USR_DOUBLE rate, uint8_t ber_scan_mode, uint8_t timer_control, int16_t offset_start) {
    INIT_SRDS_ERR_CODE
    uint32_t errs[DIAG_MAX_SAMPLES];
    uint32_t time[DIAG_MAX_SAMPLES];
    uint8_t i,cnt=0;
    uint16_t sts;
    uint8_t lane = blackhawk7_l2p2_acc_get_lane(sa__);

    /* Below 'DIAG_VERBOSE' level is intended to be modified only within a debug */
    /* session immediately after a breakpoint, and to retain its state only */
    /* through function exit:  therefore it must be 'volatile' to prevent a */
    /* compiler from eliding code conditioned on it, but NOT 'static'.      */

    for(i=0;i<DIAG_MAX_SAMPLES;i++) {
        errs[i]=0;
        time[i]=0;
    }

    EFUN(blackhawk7_l2p2_INTERNAL_poll_diag_done(sa__, &sts,(uint32_t)(timer_control*2000)));

    if(DIAG_VERBOSE > 2) EFUN_PRINTF(("lane %d: delay done\n", lane));

    EFUN(blackhawk7_l2p2_read_ber_scan_data(sa__, &errs[0], &time[0], &cnt, 2000));

    if(DIAG_VERBOSE > 2) EFUN_PRINTF(("lane %d: read done cnt=%d\n",lane, cnt));

    EFUN(blackhawk7_l2p2_pmd_uc_cmd(sa__, CMD_CAPTURE_BER_END,0x00,200));

    if(DIAG_VERBOSE > 2) EFUN_PRINTF(("lane %d: end function done\n", lane));
 /* if(cnt == 1) {                                                     */
 /*     EFUN_PRINTF(("Not enough points found to extrapolate BER\n")); */
 /*     return(ERR_CODE_NONE);                                         */
 /* }                                                                  */

    EFUN(blackhawk7_l2p2_display_ber_scan_data(sa__, rate, ber_scan_mode, &errs[0], &time[0],(uint8_t)SRDS_ABS(offset_start)));


    if(DIAG_VERBOSE > 2) EFUN_PRINTF(("lane %d: display done\n", lane));

    return ERR_CODE_NONE;
}

#endif /* !defined(SMALL_FOOTPRINT) */

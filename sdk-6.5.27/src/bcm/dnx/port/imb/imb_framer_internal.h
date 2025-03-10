/** \file imb_framer_internal.h
 *
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifndef IMB_FRAMER_INTERNAL_H_INCLUDED
/*
 * {
 */
#define IMB_FRAMER_INTERNAL_H_INCLUDED

#ifndef BCM_DNX_SUPPORT
#error "This file is for use by DNX family only!"
#endif

/*
 * INCLUDE FILES:
 * {
 */

#include <bcm/port.h>
#include <bcm_int/dnx/algo/flexe_general/algo_flexe_general.h>
#include <bcm_int/dnx/algo/cal/algo_cal.h>
#include <soc/dnx/dbal/dbal.h>
/*
 * }
 */

/*
 * MACROs
 * {
 */

/*
 * }
 */

/*
 * Structs
 * {
 */

typedef enum
{
    IMB_FRAMER_NB_RX_CALENDAR = 0,
    IMB_FRAMER_NB_TX_CALENDAR,
    IMB_FRAMER_SB_RX_CALENDAR,
    IMB_FRAMER_SB_TX_CALENDAR,
    IMB_FEU_RMC_CALENDAR,
    IMB_FEU_HI_OR_ESB_RMC_CALENDAR,
    IMB_FEU_TMC_CALENDAR
} imb_framer_calendar_type_e;
/*
 * Transcode configurations.
 */
typedef struct imb_framer_xcode_config_s
{
    int xcode_en;
    int xcode_shift_en;
    int xcode_cl82_en;
    int trans_am_en;
    int am_comp_en;
} imb_framer_xcode_config_t;
/*
 * }
 */

/**
 * \brief - Set FlexE core in/out of reset
 *
 * \param [in] unit - chip unit id.
 * \param [in] in_reset - In or out of reset
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_flexe_core_reset(
    int unit,
    int in_reset);

/**
 * \brief - Set FlexE Tiny MAC in/out of reset
 *
 * \param [in] unit - chip unit id.
 * \param [in] in_reset - In or out of reset
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_tiny_mac_reset(
    int unit,
    int in_reset);

/**
 * \brief - Define the TX delay in Northbound interface.
 *
 * \param [in] unit - chip unit id.
 * \param [in] tx_delay - Delay value
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_nb_tx_delay_set(
    int unit,
    int tx_delay);
/**
 * \brief - Define the TX delay in Northbound interface for each PM.
 *
 * \param [in] unit - chip unit id.
 * \param [in] pm_id - PM ID.
 * \param [in] tx_delay - Delay value
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_nb_tx_delay_per_pm_set(
    int unit,
    int pm_id,
    int tx_delay);

/**
 * \brief - Define the TX fifo threshold for first read.
 *
 * \param [in] unit - chip unit id.
 * \param [in] tx_threshold - threshold value
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_nb_tx_fifo_threshold_set(
    int unit,
    int tx_threshold);

/**
 * \brief - Enable or disable the clock from TSC
 *
 * \param [in] unit - chip unit id.
 * \param [in] enable - Enable or disable
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_clock_enable_set(
    int unit,
    int enable);

/**
 * \brief - Select the clock source from TSC
 *
 * \param [in] unit - chip unit id.
 * \param [in] clock_source - clock source
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_clock_source_set(
    int unit,
    int clock_source);

/**
 * \brief - Configure FlexE core to PCS port mapping.
 *
 * \param [in] unit - chip unit id.
 * \param [in] flexe_core_port - FlexE core port
 * \param [in] pm_id - PortMacro ID.
 * \param [in] pcs_port - PCS port
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_flexe_core_to_pcs_port_map_set(
    int unit,
    int flexe_core_port,
    int pm_id,
    int pcs_port);

/**
 * \brief - Enable or disable PCS port per PM.
 *
 * \param [in] unit - chip unit id.
 * \param [in] pm_id - PortMacro ID.
 * \param [in] pcs_port - PCS port.
 * \param [in] enable - enable or disable.
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_pcs_port_enable_set(
    int unit,
    int pm_id,
    int pcs_port,
    int enable);

/**
 * \brief - Enable or disable the FlexE core port.
 *
 * \param [in] unit - chip unit id.
 * \param [in] flexe_core_port - FlexE core port
 * \param [in] enable - Enable or disable
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_flexe_core_port_enable_set(
    int unit,
    int flexe_core_port,
    int enable);

/**
 * \brief - Enable / disable Tx data to the PM
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - FlexE client channel
 * \param [in] enable - enable indication
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_tx_data_to_pm_enable_set(
    int unit,
    int client_channel,
    int enable);

/**
 * \brief - Set the logical FIFO threshold after overflow.
 * after the fifo reaches overflow, it will not resume writing
 * until fifo level will get below this value.
 *
 * \param [in] unit - chip unit id
 * \param [in] rmc_id - logical fifo id
 * \param [in] thr_after_ovf - value to set as threshold after
 *        overflow
 *
 * \return
 *   int - see _SHR_E*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_rmc_thr_after_ovf_set(
    int unit,
    int rmc_id,
    int thr_after_ovf);

/**
 * \brief - set TX start threshold. this threshold represent the
 *        number of 64B words to be accumulated in the MLF
 *        before transmitting towards the PM. This is to prevent
 *        TX MAC starvation and is important for systems with
 *        oversubscription.
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - FlexE client channel
 * \param [in] start_thr - threshold value
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_tx_start_thr_set(
    int unit,
    int client_channel,
    int start_thr);
/**
 * \brief - Get tx mlf start tx threshold.
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - FlexE client channel
 * \param [out] start_thr - threshold value
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_tx_start_thr_get(
    int unit,
    int client_channel,
    int *start_thr);
/**
 * \brief - Common function for configuring FlexE
 *    shadow calendar, including:
 *        Northbound Rx calendar
 *        Southbound Rx/Tx calendar
 *        RMC/TMC calendar
 *
 */
shr_error_e imb_framer_internal_shadow_calendar_config(
    int unit,
    imb_framer_calendar_type_e cal_type,
    int cal_len,
    uint32 *calendar,
    int *cal_to_config);

/**
 * \brief - Common function for activating FlexE
 *    calendar, including:
 *        Northbound Rx calendar
 *        Southbound Rx/Tx calendar
 *        RMC/TMC calendar
 *
 */
shr_error_e imb_framer_internal_calendar_switch(
    int unit,
    imb_framer_calendar_type_e cal_type,
    int cal_to_switch);

/**
 * \brief - Get the original number of slots for give FlexE
 *    core port in NB RX calendar
 *
 */
shr_error_e imb_framer_internal_nb_cal_original_tdm_slots_nof_get(
    int unit,
    int flexe_core_port,
    int *nof_slots);

/**
 * \brief - Enable SB Tx credit counter table
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - FlexE client channel
 * \param [in] enable - enable or disable
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
shr_error_e imb_framer_internal_tx_credit_counter_enable_set(
    int unit,
    int client_channel,
    int enable);

/**
 * \brief - get the RMC current FIFO level
 *
 * \param [in] unit - chip unit id
 * \param [in] rmc_id - rmc id to check fifo level
 * \param [out] fifo_level - RMC FIFO fullnes level
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_rmc_level_get(
    int unit,
    uint32 rmc_id,
    uint32 *fifo_level);

/**
 * \brief - Reset the RMC in FEU
 *
 * \param [in] unit - chip unit id
 * \param [in] port - logical port id
 * \param [in] rmc_id - rmc id to reset
 * \param [in] in_reset - 1: in reset 0: out of reset
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_port_rx_reset_set(
    int unit,
    bcm_port_t port,
    int rmc_id,
    int in_reset);
/**
 * \brief - Configure RMC to client mapping
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - FlexE client channel
 * \param [in] rmc - rmc info
 * \param [in] rmc_id_is_changed - indicate if RMC ID is changed
 * \param [in] enable - enable or disable the mapping
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_rmc_to_client_map_set(
    int unit,
    int client_channel,
    dnx_algo_port_rmc_info_t * rmc,
    int rmc_id_is_changed,
    int enable);

/**
 * \brief - Configure client to RMC mapping
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - FlexE client channel
 * \param [in] rmc - rmc info
 * \param [in] enable - enable or disable the mapping
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_client_to_rmc_map(
    int unit,
    int client_channel,
    dnx_algo_port_rmc_info_t * rmc,
    int enable);

/**
 * \brief - get number of ports from a FEU with the specified
 *        scheduler
 *
 * \param [in] unit - chip unit id
 * \param [in] sch_prio - Scheduler. see
 *        bcm_port_nif_scheduler_t
 * \param [out] nof_ports - how many ports from the FEU use this
 *        scheduler.
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_scheduler_nof_ports_get(
    int unit,
    bcm_port_nif_scheduler_t sch_prio,
    int *nof_ports);

/**
 * \brief - Enable / disable egress flush. Egress flush means
 *        continously geanting credits to the port in order to
 *        free occupied resources.
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - flexE client channel
 * \param [in] flush_enable - enable or disable flush
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_tx_egress_flush_set(
    int unit,
    int client_channel,
    int flush_enable);
/**
 * \brief - Get egress flush status.
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - flexE client channel
 * \param [out] flush_enable - enable or disable flush
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_tx_egress_flush_get(
    int unit,
    int client_channel,
    uint32 *flush_enable);

/**
 * \brief - Reset TMC fifo in NMG
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - flexE client channel
 * \param [in] in_reset - 1: in reset 0: out of reset
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_tx_nmg_reset_hw_set(
    int unit,
    int client_channel,
    int in_reset);

/**
 * \brief - Reset TMC fifo in FEU
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - flexE client channel
 * \param [in] in_reset - 1: in reset 0: out of reset
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_tx_reset_set(
    int unit,
    int client_channel,
    int in_reset);

/**
 * \brief - Configure the indirect access control for
 *    Tiny MAC
 *
 * \param [in] unit - chip unit id
 * \param [in] port - logical port
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_mac_access_control_set(
    int unit,
    bcm_port_t port);

/**
 * \brief - Error Recovery journal for indirect access control of
 *    Tiny MAC
 *
 * \param [in] unit - chip unit id
 * \param [in] port - logical port
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_mac_access_control_set_er_journal_insert(
    int unit,
    bcm_port_t port);

/**
 * \brief - Configure Tiny MAC according to the
 *    table and field info
 *
 * \param [in] unit - chip unit id
 * \param [in] table_id - Tiny MAC dbal table id
 * \param [in] field_id - Tiny MAC dbal field id
 * \param [in] val - configuration value
 * \param [in] nof_fields - nof fields to be configured
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_mac_set(
    int unit,
    dbal_tables_e table_id,
    dbal_fields_e * field_id,
    uint32 *val,
    int nof_fields);
/**
 * \brief - Polling the required TinyMAC field
 *
 * \param [in] unit - chip unit id
 * \param [in] table_id - Tiny MAC dbal table id
 * \param [in] field_id - Tiny MAC dbal field id
 * \param [in] expected_val - the expected value
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_mac_polling(
    int unit,
    dbal_tables_e table_id,
    dbal_fields_e field_id,
    uint32 expected_val);
/**
 * \brief - Get Tiny MAC value according to the
 *    table and field info
 *
 * \param [in] unit - chip unit id
 * \param [in] table_id - Tiny MAC dbal table id
 * \param [in] field_id - Tiny MAC dbal field id
 * \param [out] val - return value
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_mac_get(
    int unit,
    dbal_tables_e table_id,
    dbal_fields_e field_id,
    uint32 *val);
/**
 * \brief - Configure credit value from TMC to EGQ.
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - FlexE client channel
 * \param [in] credit_val - Credit value
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_port_tx_credit_val_set(
    int unit,
    int client_channel,
    int credit_val);

/**
 * \brief - stop credit from TMC to EGQ.
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - FlexE client channel
 * \param [in] enable or disable
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_stop_credit_to_egq_enable_set(
    int unit,
    int client_channel,
    int enable);

/**
 * \brief - Configure the TX reset credit value.
 *
 * \param [in] unit - chip unit id
 * \param [in] value - reset credit value
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_tx_reset_credit_value_set(
    int unit,
    uint32 value);

/**
 * \brief - Reset the TX credit.
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - Flexe client channel
 * \param [in] reset - reset credit
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_tx_credit_reset(
    int unit,
    int client_channel,
    int reset);

/**
 * \brief - Set FLEXEWP/FSAR/FASIC/FSCL blocks in/out of reset
 *
 * \param [in] unit - chip unit id
 * \param [in] in_reset - in or out of reset
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
shr_error_e imb_framer_internal_flexe_blocks_soft_reset(
    int unit,
    int in_reset);

/**
 * \brief - Set FLEXEWP/FSAR/FSCL/FASIC SBUS in/out of reset
 *
 * \param [in] unit - chip unit id
 * \param [in] in_reset - in or out of reset
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
shr_error_e imb_framer_internal_flexe_blocks_sbus_reset(
    int unit,
    int in_reset);

/**
 * \brief - Set FLEXEWP/FSAR/FSCL/FASIC in/out of soft init
 *
 * \param [in] unit - chip unit id
 * \param [in] enable - in or out of reset
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
shr_error_e imb_framer_internal_flexe_blocks_soft_init_enable(
    int unit,
    int enable);

/**
 * \brief - Take target TMC credit in/out of reset
 *
 * \param [in] unit - chip unit id
 * \param [in] first_phy - first phy of ethernet port
 * \param [in] in_reset - in or out of reset
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
shr_error_e imb_feu_internal_target_tmc_credit_reset(
    int unit,
    int first_phy,
    int in_reset);

/**
 * \brief - set ITMH TC + DP offsets for the PRD.
 *
 * \param [in] unit - chip unit id
 * \param [in] tc_offset - TC offset on ITMH header
 * \param [in] dp_offset - DP offset in ITMH header
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_itmh_offsets_hw_set(
    int unit,
    uint32 tc_offset,
    uint32 dp_offset);

/**
 * \brief - set FTMH  TC + DP offsets for the PRD
 *
 * \param [in] unit - chip unit id
 * \param [in] tc_offset - TC offset in FTMH header
 * \param [in] dp_offset - DP offset in FTMH header
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_ftmh_offsets_hw_set(
    int unit,
    uint32 tc_offset,
    uint32 dp_offset);

/*
 * \brief - Enable or disable PRD bypass logic in FEU
 *
 * \param [in] unit - chip unit id
 * \param [in] is_bypass - If bypass the PRD logic
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_prd_bypass_set(
    int unit,
    uint32 is_bypass);

/*
 * \brief - Configure weight for each NIF scheduler
 *
 * \param [in] unit - chip unit id
 * \param [in] sch_prio - scheduler priority
 * \param [in] sch_weight - weight
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_scheduler_config_set(
    int unit,
    uint32 sch_prio,
    uint32 sch_weight);

/*
 * \brief - Get weight for each NIF scheduler
 *
 * \param [in] unit - chip unit id
 * \param [in] sch_prio - scheduler priority
 * \param [out] sch_weight - weight
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_scheduler_config_get(
    int unit,
    uint32 sch_prio,
    uint32 *sch_weight);

/*
 * \brief - Enable or disable drop data in RMC
 *
 * \param [in] unit - chip unit id
 * \param [in] rmc_id - RMC id
 * \param [in] enable - enable or disable
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_rmc_drop_data_set(
    int unit,
    int rmc_id,
    int enable);

/*
 * \brief - Enable or disable flush context in NMG for each scheduler
 *
 * \param [in] unit - chip unit id
 * \param [in] sch_priority - NIF scheduler
 * \param [in] enable - enable or disable
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_rx_nmg_flush_context_enable_set(
    int unit,
    uint32 sch_priority,
    int enable);

/*
 * \brief - Enable or disable RMC flush mode
 *
 * \param [in] unit - chip unit id
 * \param [in] rmc_id - RMC ID
 * \param [in] enable - enable or disable
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_rmc_flush_mode_enable_set(
    int unit,
    int rmc_id,
    int enable);

/*
 * \brief - Enable or disable RX flush in FEU
 *
 * \param [in] unit - chip unit id
 * \param [in] enable - enable or disable
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_rx_flush_enable_set(
    int unit,
    int enable);

/*
 * \brief - Polling RMC counter in given period and check if it is "0"
 *
 * \param [in] unit - chip unit id
 * \param [in] rmc_id - RMC ID
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_rx_rmc_counter_polling(
    int unit,
    int rmc_id);

/*
 * \brief - Mask the credit from FEU to EGQ in NMG
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - client channel
 * \param [in] enable - enable or disable the mask
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_nmg_credit_mask_set(
    int unit,
    int client_channel,
    int enable);

/*
 * \brief - Reset the NIF scheduler in NMG
 *
 * \param [in] unit - chip unit id
 * \param [in] sch_priority - NIF scheduler
 * \param [in] in_reset - in or out of reset
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_rx_nmg_per_sch_prio_reset(
    int unit,
    uint32 sch_priority,
    int in_reset);

/*
 * \brief - Mask the credit from NIF to FEU
 *
 * \param [in] unit - chip unit id
 * \param [in] tmc - NIF tmc index
 * \param [in] enable - enable or disable the mask
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_feu_credit_mask_set(
    int unit,
    int tmc,
    int enable);

/*
 * \brief - Enable per pcs port msbus mode
 *
 * \param [in] unit - chip unit id
 * \param [in] pm_id - PM ID
 * \param [in] pcs_port - pcs port
 * \param [in] l1_eth_en - enable or disable L1 eth mode
 * \param [in] flexe_en - enable or disable flexe mode
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_pcs_msbus_mode_enable_set(
    int unit,
    int pm_id,
    int pcs_port,
    int l1_eth_en,
    int flexe_en);

/*
 * \brief - Reset client in Flexewp RX
 *
 * \param [in] unit - chip unit id
 * \param [in] client-channel - FlexE client channel
 * \param [in] in_reset - in or out of reset
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_sb_client_rx_reset_set(
    int unit,
    int client_channel,
    int in_reset);
/**
 * \brief - Reset the client in FlexEWP SB tx.
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - client channel
 * \param [in] in_reset - 1: in reset 0: out of reset
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_sb_client_tx_reset_set(
    int unit,
    int client_channel,
    int in_reset);
/**
 * \brief - Reset the tinymac encap in FlexEWP SB tx.
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - client channel
 * \param [in] in_reset - 1: in reset 0: out of reset
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_sb_client_enc_reset_set(
    int unit,
    int client_channel,
    int in_reset);
/**
 * \brief - Reset the tinymac decap in FlexEWP SB rx.
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - client channel
 * \param [in] in_reset - 1: in reset 0: out of reset
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_sb_client_dec_reset_set(
    int unit,
    int client_channel,
    int in_reset);
/**
 * \brief - Enable 66b control blocks in encap, including LF/RF/LI/LPI
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - client channel
 * \param [in] enable - enable or disable
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_enc_control_blocks_enable_set(
    int unit,
    int client_channel,
    int enable);
/**
 * \brief - Enable 66b control blocks in decap, including LF/RF/LI/LPI
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - client channel
 * \param [in] enable - enable or disable
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_dec_control_blocks_enable_set(
    int unit,
    int client_channel,
    int enable);
/**
 * \brief - Enable cl82 in encap
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - client channel
 * \param [in] enable - enable or disable
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_enc_cl82_enable_set(
    int unit,
    int client_channel,
    int enable);
/**
 * \brief - Enable cl82 in decap
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - client channel
 * \param [in] enable - enable or disable
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_dec_cl82_enable_set(
    int unit,
    int client_channel,
    int enable);
/**
 * \brief - Reset the decap data path.
 *
 * \param [in] unit - chip unit id
 * \param [in] in_reset - 1: in reset 0: out of reset
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_dec_datapath_reset_set(
    int unit,
    int in_reset);
/**
 * \brief - Reset the encap data path.
 *
 * \param [in] unit - chip unit id
 * \param [in] in_reset - 1: in reset 0: out of reset
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_enc_datapath_reset_set(
    int unit,
    int in_reset);
/**
 * \brief - Configure if decoder is ready to decode.
 *
 * \param [in] unit - chip unit id
 * \param [in] is_ready - if it is ready
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_dec_ready_set(
    int unit,
    int is_ready);

int imb_feu_rx_prd_port_profile_map_hw_set(
    int unit,
    int client_channel,
    int prd_profile);

/*
 * \brief - Reset port RX in Flexewp NB
 *
 * \param [in] unit - chip unit id
 * \param [in] flexe_core_port - FlexE core port
 * \param [in] in_reset - in or out of reset
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_nb_port_rx_reset_set(
    int unit,
    int flexe_core_port,
    int in_reset);

/**
 * \brief - enable PRD hard stage per RMC. this effectively
 *        enable the PRD feature.
 *
 */
int imb_feu_prd_hard_stage_enable_hw_set(
    int unit,
    uint32 rmc,
    uint32 enable);

/**
 * \brief - get enable indication for the PRD hard stage per RMC
 *
 */
int imb_feu_prd_hard_stage_enable_hw_get(
    int unit,
    uint32 rmc,
    uint32 *enable);
/**
 * \brief - set PRD Parser whether to ignore indication of IP
 *        dscp even if packet is identified as IP.
 *
 * \param [in] unit - chip unit id
 * \param [in] prd_profile - prd port profile.
 * \param [in] ignore_ip_dscp - ignore IP DSCP indication
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_ignore_ip_dscp_hw_set(
    int unit,
    int prd_profile,
    uint32 ignore_ip_dscp);

/**
 * \brief - get from PRD parser indication whether it ignores IP
 *        DSCP
 *
 * \param [in] unit - chip unit id
 * \param [in] prd_profile - prd port profile.
 * \param [out] ignore_ip_dscp - ignore IP DSCP indication
 *
 * \return
 *   int - see _SHR_E*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_ignore_ip_dscp_hw_get(
    int unit,
    int prd_profile,
    uint32 *ignore_ip_dscp);

/**
 * \brief - set PRD parser to ignore MPLS EXP even if packet is
 *        identified as MPLS
 *
 * \param [in] unit - chip unit id
 * \param [in] prd_profile - prd port profile.
 * \param [in] ignore_mpls_exp - ignore MPLS EXP indication
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_ignore_mpls_exp_hw_set(
    int unit,
    int prd_profile,
    uint32 ignore_mpls_exp);

/**
 * \brief - get from PRD parser indication whether it ignores
 *        MPLS EXP
 *
 * \param [in] unit - chip unit id
 * \param [in] prd_profile - prd port profile.
 * \param [out] ignore_mpls_exp - ignore MPLS EXP indication
 *
 * \return
 *   int - see _SHR_E*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_ignore_mpls_exp_hw_get(
    int unit,
    int prd_profile,
    uint32 *ignore_mpls_exp);

/**
 * \brief - set PRD Parser whether to ignore inner tag PCP DEI
 *        indication even if packet is identified as double
 *        tagged
 *
 * \param [in] unit - chip unit id
 * \param [in] prd_profile - prd port profile.
 * \param [in] ignore_inner_tag - ignore inner VLAN tag
 *        indication
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_ignore_inner_tag_hw_set(
    int unit,
    int prd_profile,
    uint32 ignore_inner_tag);

/**
 * \brief - get from PRD parser indication whether it ignores
 *        inner VLAN tag
 *
 * \param [in] unit - chip unit id
 * \param [in] prd_profile - prd port profile.
 * \param [out] ignore_inner_tag - ignore inner VLAN tag
 *        indication
 *
 * \return
 *   int -see _SHR_E*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_ignore_inner_tag_hw_get(
    int unit,
    int prd_profile,
    uint32 *ignore_inner_tag);

/**
 * \brief - set PRD Parser whether to ignore outer tag PCP DEI
 *        indication even if packet is identified as VLAN tagged
 *
 * \param [in] unit - chip unit id
 * \param [in] prd_profile - prd port profile.
 * \param [in] ignore_outer_tag - ignore outer VLAN tag
 *        indication
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_ignore_outer_tag_hw_set(
    int unit,
    int prd_profile,
    uint32 ignore_outer_tag);

/**
 * \brief - get from PRD parser indication whether it ignores
 *        outer VLAN tag
 *
 * \param [in] unit - chip unit id
 * \param [in] prd_profile - prd port profile.
 * \param [out] ignore_outer_tag - ignore outer VLAN tag
 *        indication
 *
 * \return
 *   int - see _SHR_E*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_ignore_outer_tag_hw_get(
    int unit,
    int prd_profile,
    uint32 *ignore_outer_tag);

/**
 * \brief - set default priority for the PRD hard stage parser.
 *        if the packet is not identified as IP/MPLS/double
 *        tagged/single tagged or if the relevant indications
 *        are set to ignore, the default priority will be given
 *        to the packet. (the priority from the hard stage can
 *        be later overridden by the priority from the soft
 *        stage.
 *
 * \param [in] unit - chip unit id
 * \param [in] prd_profile - prd port profile.
 * \param [in] default_priority - default priority
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_default_priority_hw_set(
    int unit,
    int prd_profile,
    uint32 default_priority);

/**
 * \brief - get default priority given in the PRD hard stage
 *        parser.
 *
 * \param [in] unit - chip unit id
 * \param [in] prd_profile - prd port profile.
 * \param [out] default_priority - default priority
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_default_priority_hw_get(
    int unit,
    int prd_profile,
    uint32 *default_priority);

/**
 * \brief - enable PRD soft stage per port. PRD soft stage is a
 *        TCAM for which the user configures both the table and
 *        the key. if there is a hit in the TCAM, the priority
 *        from the TCAM entry will override the priority from
 *        the hard stage
 *
 * \param [in] unit - chip unit id
 * \param [in] prd_profile - prd port profile.
 * \param [in] enable_eth - enable soft stage for eth port
 *        (should only be set for eth ports)
 * \param [in] enable_tm - enable soft stage for TM ports
 *        (should only be set for ports with TM headers -
 *        ITMH/FTMH)
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_soft_stage_enable_hw_set(
    int unit,
    int prd_profile,
    uint32 enable_eth,
    uint32 enable_tm);

/**
 * \brief - get enable indication for PRD soft stage
 *
 * \param [in] unit - chip unit id
 * \param [in] prd_profile - prd port profile.
 * \param [out] enable_eth - soft stage enabled for eth port
 * \param [out] enable_tm - soft stage enabled for TM port
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_soft_stage_enable_hw_get(
    int unit,
    int prd_profile,
    uint32 *enable_eth,
    uint32 *enable_tm);

/**
 * \brief - set outer tag size for the port. if port is port
 *        Extender, the outer tag size should be set to 8B,
 *        otherwise 4B
 *
 * \param [in] unit - chip unit id
 * \param [in] prd_profile - prd port profile.
 * \param [in] outer_tag_size - outer tag size, compatible to
 *        DBAL enum field. see VLAN_OUTER_TAG_SIZE.
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_outer_tag_size_hw_set(
    int unit,
    int prd_profile,
    uint32 outer_tag_size);

/**
 * \brief - set PRD port type, according to the header type of
 *        the port
 *
 * \param [in] unit - chip unit id
 * \param [in] prd_profile - prd port profile.
 * \param [in] prd_port_type - PRD port type. should match DBAL
 *        enum type. see NIF_PRD_PORT_TYPE.
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_port_type_hw_set(
    int unit,
    int prd_profile,
    uint32 prd_port_type);

/**
 * \brief - fill the TM priority map (PRD hard stage). add the
 *        the map priority value to be returned per TC + DP
 *        values
 *
 * \param [in] unit - chip unit ID
 * \param [in] port - logical port
 * \param [in] tc - TC value (Traffic Class)
 * \param [in] dp - DP value (Drop Precedence)
 * \param [in] priority - priority to set for TC+DP
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_map_tm_tc_dp_hw_set(
    int unit,
    bcm_port_t port,
    uint32 tc,
    uint32 dp,
    uint32 priority);

/**
 * \brief - get information from TM priority map (PRD hard
 *        stage). get the priority given for a combination of
 *        TC+DP.
 *
 * \param [in] unit - chip unit id
 * \param [in] port - logical port
 * \param [in] tc - TC value (Traffic Class)
 * \param [in] dp - DP value (Drop Precedence)
 * \param [out] priority - priority for the TC+DP
 *
 * \return
 *   int - see _SHR_E*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_map_tm_tc_dp_hw_get(
    int unit,
    bcm_port_t port,
    uint32 tc,
    uint32 dp,
    uint32 *priority);
/**
 * \brief - fill the IP priority table (PRD hard stage). set
 *        priority value for a specific DSCP.
 *
 * \param [in] unit - chip unit id
 * \param [in] port - logical port
 * \param [in] dscp - DSCP field value
 * \param [in] priority - priority for the DSCP
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_map_ip_dscp_hw_set(
    int unit,
    bcm_port_t port,
    uint32 dscp,
    uint32 priority);

/**
 * \brief - get information from IP priority table (PRD hard
 *        stage). get the priority returned for a specific DSCP
 *
 * \param [in] unit - chip unit id
 * \param [in] port - logical port
 * \param [in] dscp - DSCP field value
 * \param [out] priority - returned priority
 *
 * \return
 *   int - see _SHR_E*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_map_ip_dscp_hw_get(
    int unit,
    bcm_port_t port,
    uint32 dscp,
    uint32 *priority);
/**
 * \brief - fill the ETH (VLAN) Priority table (PRD hard
 *        stage). set a priority value to match a specific
 *        PCP+DEI combination
 *
 * \param [in] unit - chip unit id
 * \param [in] port - logical port
 * \param [in] pcp - PCP value
 * \param [in] dei - DEI value
 * \param [in] priority - priority for the PCP+DEI
 *
 * \return
 *   int - see _SHR_E*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_map_eth_pcp_dei_hw_set(
    int unit,
    bcm_port_t port,
    uint32 pcp,
    uint32 dei,
    uint32 priority);

/**
 * \brief - get information from the ETH (VLAN) priority table
 *        (PRD hard stage). get the priority returned for a
 *        specific combination of PCP+DEI
 *
 * \param [in] unit - chip unit id
 * \param [in] port - logical port
 * \param [in] pcp - PCP value
 * \param [in] dei - DEI value
 * \param [out] priority - priority for the PCP+DEI
 *
 * \return
 *   int - see _SHR_E*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_map_eth_pcp_dei_hw_get(
    int unit,
    bcm_port_t port,
    uint32 pcp,
    uint32 dei,
    uint32 *priority);

/**
 * \brief - fill the MPLS priority table (PRD hard stage). set
 *        priority value for a specific EXP value.
 *
 * \param [in] unit - chip unit id
 * \param [in] port - logical port
 * \param [in] exp - EXP field value
 * \param [in] priority - priority for the EXP
 *
 * \return
 *   int - see .h file
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_map_mpls_exp_hw_set(
    int unit,
    bcm_port_t port,
    uint32 exp,
    uint32 priority);

/**
 * \brief - get information from the MPLS priority table. get
 *        the priority returned for a specific EXP value
 *
 * \param [in] unit - chip unit id
 * \param [in] port - logical port
 * \param [in] exp - EXP field value
 * \param [out] priority - priority for the EXP
 *
 * \return
 *   int - see _SHR_E*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_prd_map_mpls_exp_hw_get(
    int unit,
    bcm_port_t port,
    uint32 exp,
    uint32 *priority);
/**
 * \brief - set one of the TPID values per port profile to be recognized
 *        by the PRD parser. if a packet TPID is not recognized,
 *        the packet will get the default priority. each port
 *        can have four TPID values.
 *
 */
int imb_feu_prd_tpid_hw_set(
    int unit,
    uint32 prd_profile,
    uint32 tpid_index,
    uint32 tpid_value);

/**
 * \brief - get the TPID value per port profile to be recognized
 *        by the PRD parser. if a packet TPID is not recognized,
 *        the packet will get the default priority. each port
 *        can have four TPID values.
 *
 */
int imb_feu_prd_tpid_hw_get(
    int unit,
    uint32 prd_profile,
    uint32 tpid_index,
    uint32 *tpid_value);

/**
 * \brief - set PRD thresholds per priority. based on the
 *        priority given from the parser, the packet is sent to
 *        the correct RMC. in each RMC there is a thresholds per
 *        priority which is mapped to it.
 *
 */
int imb_feu_prd_threshold_hw_set(
    int unit,
    uint32 rmc,
    uint32 priority,
    uint32 threshold);

/**
 * \brief - get the current threshold for a specific priority in
 *        a specific RMC.
 *
 */
int imb_feu_prd_threshold_hw_get(
    int unit,
    uint32 rmc,
    uint32 priority,
    uint32 *threshold);
/**
 * \brief - get PRD drop counter value, per RMC
 *
 */
int imb_feu_prd_drop_count_hw_get(
    int unit,
    uint32 rmc,
    uint64 *count);
/**
 * \brief - set configurable ether type to a ether type code.
 *        the ether type codes are meaningful in the PRD soft
 *        stage (TCAM).
 *
 */
int imb_feu_prd_custom_ether_type_hw_set(
    int unit,
    uint32 ether_type_code,
    uint32 ether_type_val);

/**
 * \brief - get the ether type value mapped to a specific ether
 *        type code, out of the configurable ether types (codes
 *        1-6).
 *
 */
int imb_feu_prd_custom_ether_type_hw_get(
    int unit,
    uint32 ether_type_code,
    uint32 *ether_type_val);

/**
 * \brief - set the offset base for the TCAM key. it means the
 *        offsets that compose the key will start from this
 *        offset base. the offset base have 3 options:
 * 0=>start of packet
 * 1=>end of eth header
 * 2=>end of header after eth header.
 *
 */
int imb_feu_prd_tcam_entry_key_offset_base_hw_set(
    int unit,
    uint32 ether_type_code,
    uint32 offset_base);

/**
 * \brief - get the current offset base for the given ether
 *        code.
 *
 */
int imb_feu_prd_tcam_entry_key_offset_base_hw_get(
    int unit,
    uint32 ether_type_code,
    uint32 *offset_base);

/**
 * \brief - set ether type size (in bytes) for the given ether
 *        type code. the ether type size is only used if the
 *        offset base for the key is "end of header after eth
 *        header"
 *
 */
int imb_feu_prd_ether_type_size_hw_set(
    int unit,
    uint32 ether_type_code,
    uint32 ether_type_size);

/**
 * \brief - get the ether type currently set for a specific
 *        ether type code
 *
 */
int imb_feu_prd_ether_type_size_hw_get(
    int unit,
    uint32 ether_type_code,
    uint32 *ether_type_size);
/**
 * \brief - set the PRD soft stage (TCAM) key. there is a key
 *        per ether type (total of 16 keys). the key is build of
 *        4 offsets given in the packet header. from each
 *        offset, 8 bits are taken to create a total of 32 bit.
 *        when comparing to the TCAM entries, the ether type
 *        code joins the key to create 36bit key:
 *        |ether type code|offset 4|offset 3|offset 2|offset 1|
 *        -----------------------------------------------------
 *        35              31       23       15       7        0
 *
 * see .h file
 */
int imb_feu_prd_tcam_entry_key_offset_hw_set(
    int unit,
    uint32 ether_type_code,
    uint32 offset_index,
    uint32 offset_value);

/**
 * \brief - get information about the TCAM key for a specific
 *        ether type.
 *
 * see .h file
 */
int imb_feu_prd_tcam_entry_key_offset_hw_get(
    int unit,
    uint32 ether_type_code,
    uint32 offset_index,
    uint32 *offset_value);

/**
 * \brief - fill the PRD soft stage TCAM table. there are 32
 *        entries in the table. if there is a hit, the priority
 *        for the packet will be taken from the TCAM entry
 *        information
 *
 */

int imb_feu_prd_tcam_entry_hw_set(
    int unit,
    uint32 entry_index,
    const dnx_cosq_prd_tcam_entry_info_t * entry_info);

/**
 * \brief - get information from the PRD soft stage (TCAM)
 *        table. get specific entry information
 *
 */
int imb_feu_prd_tcam_entry_hw_get(
    int unit,
    uint32 entry_index,
    dnx_cosq_prd_tcam_entry_info_t * entry_info);
/**
 * \brief - set Control Frame properties to be recognized by the
 *        PRD parser. if a control frame is identified, it
 *        automatically gets the highest priority (3). each
 *        packet is compared against all control frame
 *        properties of the ETHU
 *
 */
int imb_feu_prd_control_frame_hw_set(
    int unit,
    uint32 control_frame_index,
    const bcm_cosq_ingress_drop_control_frame_config_t * control_frame_config);

/**
 * \brief - get Control Frame properties recognized by the
 *        parser.
 *
 */
int imb_feu_prd_control_frame_hw_get(
    int unit,
    uint32 control_frame_index,
    bcm_cosq_ingress_drop_control_frame_config_t * control_frame_config);

/**
 * \brief - set MPLS special label properties. if one of the
 *        MPLS labels is identified as special label and its
 *        value match one of the special label values, priority
 *        for the packet is taken from the special label
 *        properties.
 *
 */
int imb_feu_prd_mpls_special_label_hw_set(
    int unit,
    uint32 special_label_index,
    const bcm_cosq_ingress_port_drop_mpls_special_label_config_t * label_config);

/**
 * \brief - get current configuration of MPLS special label
 *
 */
int imb_feu_prd_mpls_special_label_hw_get(
    int unit,
    uint32 special_label_index,
    bcm_cosq_ingress_port_drop_mpls_special_label_config_t * label_config);

/*
 * \brief - Clear SB RX client FIFO overflow interrupt in wrapper
 *
 * \param [in] unit - chip unit id
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_sb_port_rx_overflow_clear(
    int unit);

/*
 * \brief - Get SB RX client FIFO overflow interrupt in wrapper
 *
 * \param [in] unit - chip unit id
 * \param [out] is_overflow - fifo overflow status
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_sb_port_rx_overflow_get(
    int unit,
    uint32 *is_overflow);

/**
 * \brief - Configure the calendar slots
 *
 * \param [in] unit - chip unit id
 * \param [in] cal_type - calendar type
 * \param [in] cal_id - calendar ID to configure
 * \param [in] cal_len - calendar length
 * \param [in] calendar - calendar slots info
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
shr_error_e imb_framer_internal_calendar_slots_config(
    int unit,
    imb_framer_calendar_type_e cal_type,
    int cal_id,
    int cal_len,
    uint32 *calendar);

/**
 * \brief - Get default pm_id_and pcs port for FLEXEWP_FLEXE_PORT_SOURCE
 *
 * \param [in] unit - chip unit id
 * \param [in] pm_id - default PM ID
 * \param [in] pcs_port - default PCS port
 */
shr_error_e imb_framer_internal_default_pm_id_and_pcs_port_get(
    int unit,
    int *pm_id,
    int *pcs_port);

/**
 * \brief - Reset the port Tx in FlexEWP NB.
 *
 * \param [in] unit - chip unit id
 * \param [in] pm_index - PM Index
 * \param [in] pcs_port - PCS port
 * \param [in] in_reset - In or Out of rest
 *
 * \return
 *   int - see _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 * see .h file
 */
shr_error_e imb_framer_internal_nb_port_tx_reset_set(
    int unit,
    int pm_index,
    int pcs_port,
    int in_reset);

/**
 * \brief - Get tiny mac counter according to field id
 *
 * \param [in] unit - chip unit id
 * \param [in] field_id - Tiny MAC counter dbal field id
 * \param [out] val - counter value
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
shr_error_e imb_framer_internal_mac_counter_get(
    int unit,
    dbal_fields_e field_id,
    uint64 *val);

/**
 * \brief - Set tiny mac counter according to field id
 *
 * \param [in] unit - chip unit id
 * \param [in] field_id - Tiny MAC counter dbal field id
 * \param [in] val - counter value
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
shr_error_e imb_framer_internal_mac_counter_set(
    int unit,
    dbal_fields_e field_id,
    const uint64 *val);

/**
 * \brief - Configure alter Flexe core ports for give flexe core port
 *
 * \param [in] unit - chip unit id
 * \param [in] flexe_core_port - flexe core port
 * \param [in] alter_flexe_core_ports - Alternative flexe core port
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */

int imb_framer_internal_alternative_port_set(
    int unit,
    int flexe_core_port,
    uint32 alter_flexe_core_ports);

/**
 * \brief - Enable Tx credit for Rx valid in case of
 *    local fault.
 *
 * \param [in] unit - chip unit id
 * \param [in] enable - Enable or disable
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_tx_credit_for_rx_valid_enable_set(
    int unit,
    int enable);

/**
 * \brief - Enable led functional in flexe wrapper
 *
 * \param [in] unit - chip unit id
 * \param [in] enable - Enable or disable
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_led_enable_set(
    int unit,
    int enable);

/**
 * \brief - Program loopback tdm table for tinymac
 *
 * \param [in] unit - chip unit id
 * \param [in] client_channel - client channel
 * \param [in] valid - valid or not
 * \param [in] tdm_slot_start - slot start in the range of 1700
 * \param [in] nof_slot - number of slot from tdm_slot_start
 *
 * \return
 *   int - see _SHR_E*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_mac_loopback_tdm_table_hw_set(
    int unit,
    int client_channel,
    int valid,
    int tdm_slot_start,
    int nof_slot);

/**
 * \brief - Configure start TX for FEU RMC
 *
 * \param [in] unit - chip unit id
 * \param [in] rmc_id - RMC ID
 * \param [in] start_tx - Start Tx value
 * \param [in] enable - Enable or disable start tx
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_internal_port_rx_start_tx_thr_set(
    int unit,
    int rmc_id,
    uint32 start_tx,
    int enable);
/**
 * \brief - Enable/Disable TDM indication masking.
 *
 * \param [in] unit - Unit ID
 * \param [in] value - 1: enable TDM mask, 0: disable TDM mask
 *
 * \return
 *   int
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_feu_tdm_mask_hw_set(
    int unit,
    uint32 value);
/**
 * \brief - Enable/disable LF/RF/LI for L1 switching in ENC
 *
 * \param [in] unit - Unit ID
 * \param [in] enable - enable or disable
 *
 * \return
 *   int
 *
 * \remarks
 *   * None
 * \see
 *   * None
 */
int imb_framer_internal_lf_rf_li_encap_enable_set(
    int unit,
    int enable);
/**
 * \brief - Get the latest packet PRD priority and TDM indication of a port
 *
 * \param [in] unit - chip unit id
 * \param [out] priority - prd priority of latest packet
 * \param [out] tdm - TDM indication of latest packet
 * \param [out] valid - indicates if the priority and TDM is valid
 *
 * \return
 *   int - seee _SHR_E_*
 *
 * \remarks
 *   * None
 * \see
 *   * None
*/
int imb_feu_prd_port_last_packet_priority_tdm_hw_get(
    int unit,
    uint32 *priority,
    uint32 *tdm,
    uint32 *valid);
/**
 * \brief - Set BusB client link list G.hao configuration
 *
 */
int imb_framer_internal_port_fifo_link_list_ghao_config_set(
    int unit,
    int client_channel,
    dnx_algo_flexe_link_list_fifo_type_e fifo_type,
    int delta_val,
    uint32 flags);
/**
 * \brief - Set BusB client link list force configuration
 *
 */
int imb_framer_internal_port_fifo_link_list_force_config_set(
    int unit,
    int client_channel,
    int rmc_id,
    int speed,
    dnx_algo_flexe_link_list_fifo_type_e fifo_type,
    int enable);
/**
 * \brief - get all master logical ports on Framer
 */
int imb_framer_master_ports_get(
    int unit,
    bcm_pbmp_t * framer_ports);
/**
 * \brief - Configure PCS port to flexe core port mapping.
 *
 */
int imb_framer_internal_pcs_to_flexe_core_port_map_set(
    int unit,
    int pm_id,
    int pcs_port,
    int flexe_core_port);
/**
 * \brief - Configure PCS port fifo size.
 *    for speed <= 50G, the fifo size is 0
 *    for speed = 100G, the fifo size is 1
 *    for speed = 200G, the fifo size is 2
 *    for speed = 400G, the fifo size is 3
 */
int imb_framer_internal_pcs_port_fifo_size_set(
    int unit,
    int pm_id,
    int pcs_port,
    int fifo_size);
/**
 * \brief - Configure SAR to EGQ port mapping for credit transmission.
 */
int imb_framer_internal_sar_to_egq_mapping_set(
    int unit,
    int sar_channel,
    int enable);
/**
 * \brief - Configure EGQ to SAR port mapping for data transmission.
 */
int imb_framer_internal_egq_to_sar_mapping_set(
    int unit,
    int sar_channel,
    int enable);
/**
 * \brief - Configure the transcode configurations.
 */
int imb_framer_internal_port_transcode_set(
    int unit,
    int pm_index,
    int pcs_port,
    int is_rx,
    imb_framer_xcode_config_t * xcode_cfg);
/**
 * \brief - Configure init credit for SB Tx fifo into HW
 */
int imb_framer_internal_sb_tx_fifo_init_credit_set(
    int unit,
    int client_channel,
    int init_credit);

/**
 * \brief - Read the shared arch calendar slots
 */
shr_error_e imb_framer_internal_active_shared_arch_calendar_get(
    int unit,
    imb_framer_calendar_type_e calendar_type,
    uint32 calendar_length,
    uint32 *nof_slots_per_client,
    uint32 *calendar);
#endif/*_IMB_FRAMER_INTERNAL_H_INCLUDED_*/

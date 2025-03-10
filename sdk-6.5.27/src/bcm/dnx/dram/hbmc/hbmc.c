
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_DRAM

#include <soc/sand/shrextend/shrextend_debug.h>
#include <soc/memory.h>
#include <soc/feature.h>
#include <soc/types.h>
#include <soc/register.h>
#include <soc/dnxc/drv_dnxc_utils.h>
#include <soc/dnxc/drv.h>

#include <sal/core/boot.h>
#include <soc/mem.h>
#include <sal/appl/sal.h>
#include <bcm_int/dnx/dram/hbmc/hbmc.h>
#include <bcm_int/dnx/dram/hbmc/hbmc_cb.h>
#include <bcm_int/dnx/dram/hbmc/hbmc_firmware.h>
#include <soc/dnx/shmoo_hbm16.h>
#include "hbmc_dbal_access.h"
#include "hbmc_monitor.h"
#include "hbmc_otp.h"
#include <bcm_int/dnx/dram/dram.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_dram.h>
#include <soc/sand/sand_aux_access.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/access/dnx_ingress_congestion_access.h>
#include <soc/dnx/swstate/auto_generated/access/dnx_dram_access.h>
#include <soc/dnxc/dnxc_ha.h>
#include <soc/dnxc/swstate/dnxc_sw_state_verifications.h>
#include <soc/dnxc/swstate/dnxc_sw_state_utils.h>

#define GET_BIT_MASK(bits, offset)                  ((((1 << ((bits) + (offset))) - 1) >> (offset)) << (offset))

#define PHY_ADDRESS_MODULE_BITS                     (1)
#define PHY_ADDRESS_MODULE_OFFSET                   (0)
#define PHY_ADDRESS_MODULE_MASK                     (GET_BIT_MASK(PHY_ADDRESS_MODULE_BITS, PHY_ADDRESS_MODULE_OFFSET))

#define PHY_ADDRESS_GET_MODULE(address, core)       (((address & PHY_ADDRESS_MODULE_MASK) >> PHY_ADDRESS_MODULE_OFFSET) ^ (core))

#define PHY_ADDRESS_CHANNEL_BITS                    (3)
#define PHY_ADDRESS_CHANNEL_OFFSET                  (PHY_ADDRESS_MODULE_OFFSET + PHY_ADDRESS_MODULE_BITS)
#define PHY_ADDRESS_CHANNEL_MASK                    (GET_BIT_MASK(PHY_ADDRESS_CHANNEL_BITS, PHY_ADDRESS_CHANNEL_OFFSET))
#define PHY_ADDRESS_GET_CHANNEL(address)            ((address & PHY_ADDRESS_CHANNEL_MASK) >> PHY_ADDRESS_CHANNEL_OFFSET)

#define PHY_ADDRESS_BANK_BITS                       (5)
#define PHY_ADDRESS_BANK_OFFSET                     (PHY_ADDRESS_CHANNEL_OFFSET + PHY_ADDRESS_CHANNEL_BITS)
#define PHY_ADDRESS_BANK_MASK                       (GET_BIT_MASK(PHY_ADDRESS_BANK_BITS, PHY_ADDRESS_BANK_OFFSET))
#define PHY_ADDRESS_GET_BANK(address)               ((address & PHY_ADDRESS_BANK_MASK) >> PHY_ADDRESS_BANK_OFFSET)

#define PHY_ADDRESS_ROW_BITS                        (15)
#define PHY_ADDRESS_ROW_OFFSET                      (PHY_ADDRESS_BANK_OFFSET + PHY_ADDRESS_BANK_BITS)
#define PHY_ADDRESS_ROW_MASK                        (GET_BIT_MASK(PHY_ADDRESS_ROW_BITS, PHY_ADDRESS_ROW_OFFSET))
#define PHY_ADDRESS_GET_ROW(address)                ((address & PHY_ADDRESS_ROW_MASK) >> PHY_ADDRESS_ROW_OFFSET)

#define PHY_ADDRESS_COLUMN_BITS                     (6)
#define PHY_ADDRESS_COLUMN_OFFSET                   (PHY_ADDRESS_ROW_OFFSET + PHY_ADDRESS_ROW_BITS)
#define PHY_ADDRESS_COLUMN_MASK                     (GET_BIT_MASK(PHY_ADDRESS_COLUMN_BITS, PHY_ADDRESS_COLUMN_OFFSET))

#define PHY_ADDRESS_GET_COLUMN(address)             (((address & PHY_ADDRESS_COLUMN_MASK) >> PHY_ADDRESS_COLUMN_OFFSET) >> 1)

#define PHY_ADDRESS_JUMBLED_RELEVANT_COLUMN_BITS    (2)
#define PHY_ADDRESS_JUMBLED_RELEVANT_COLUMN_OFFSET  (PHY_ADDRESS_ROW_OFFSET + PHY_ADDRESS_ROW_BITS)
#define PHY_ADDRESS_JUMBLED_RELEVANT_COLUMN_MASK    (GET_BIT_MASK(PHY_ADDRESS_JUMBLED_RELEVANT_COLUMN_BITS, \
                                                                  PHY_ADDRESS_JUMBLED_RELEVANT_COLUMN_OFFSET))

#define PHY_ADDRESS_CORRECT_RELEVANT_COLUMN_OFFSET  (28)
#define PHY_ADDRESS_SEQUENTIAL_COLUMN_OFFSET        (25)

#define HBMC_LOGICAL_ADDRESSES_DATA_SOURCE_ID_OFFSET (24)

#define HBMC_LOGICAL_ADDRESSES_BITS_PER_BUFFER      (4)

#define HBMC_TRANSACTION_BITS_IN_LOGICAL_ADDRESS    (3)
#define HBMC_PHYSICAL_ADDRESS_TRANSACTION_SIZE_WORDS    (8)
#define BYTES_IN_WORD (4)

#define DNX_HBMC_INIT_BIST_WRITE_WEIGHT          (0x800)
#define DNX_HBMC_INIT_BIST_READ_WEIGHT           (0x800)
#define DNX_HBMC_INIT_BIST_NUM_ACTIONS           (0x1000000)
#define DNX_HBMC_INIT_BIST_SAME_ROW_COMMANDS     (dnx_data_dram.hbm.bist_get(unit)->same_row_commands)

#define DNX_HBMC_SAVE_RESTORE_LEVELS (HBMC_SHMOO_LEVEL_2 | HBMC_SHMOO_LEVEL_1 | HBMC_SHMOO_LEVEL_0)

#define HBM_TEMPERATURE_MONITOR_THREAD_NAME "HBM temperature monitor"
#define HBM_TEMPERATURE_LOG_THREAD_NAME "HBM temperature log"

static shr_error_e dnx_hbmc_hbm_refresh_enable_set(
    int unit,
    int hbm_index,
    uint32 refresh_enable);

static shr_error_e
dnx_hbmc_call_backs_register(
    int unit)
{
    hbmc_shmoo_cbi_t shmoo_cbi;

    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&shmoo_cbi, 0, sizeof(shmoo_cbi));

    shmoo_cbi.hbmc_phy_reg_read = dnx_hbmc_phy_reg_read_cb;

    shmoo_cbi.hbmc_phy_reg_write = dnx_hbmc_phy_reg_write_cb;

    shmoo_cbi.hbmc_phy_reg_modify = dnx_hbmc_phy_reg_modify_cb;

    shmoo_cbi.hbmc_shmoo_bist_conf_set = dnx_hbmc_bist_conf_set_cb;

    shmoo_cbi.hbmc_shmoo_bist_err_cnt = dnx_hbmc_bist_err_cnt_cb;
    shmoo_cbi.hbmc_shmoo_custom_bist_run = NULL;

    shmoo_cbi.hbmc_shmoo_dram_init = dnx_hbmc_dram_init_cb;

    shmoo_cbi.hbmc_shmoo_pll_set = dnx_hbmc_pll_set_cb;

    shmoo_cbi.hbmc_shmoo_modify_mrs = dnx_hbmc_modify_mrs_cb;

    shmoo_cbi.hbmc_shmoo_enable_wr_parity = dnx_hbmc_enable_wr_parity_cb;

    shmoo_cbi.hbmc_shmoo_enable_rd_parity = dnx_hbmc_enable_rd_parity_cb;

    shmoo_cbi.hbmc_shmoo_enable_addr_parity = dnx_hbmc_enable_addr_parity_cb;

    shmoo_cbi.hbmc_shmoo_dram_info_access = dnx_hbmc_dram_info_access_cb;

    shmoo_cbi.hbmc_shmoo_soft_reset_controller_without_dram = dnx_hbmc_soft_reset_controller_without_dram_cb;

    shmoo_cbi.hbmc_shmoo_enable_refresh = dnx_hbmc_enable_refresh_cb;

    shmoo_cbi.hbmc_shmoo_enable_rd_dbi = dnx_hbmc_enable_rd_dbi_cb;

    shmoo_cbi.hbmc_shmoo_enable_wr_dbi = dnx_hbmc_enable_wr_dbi_cb;

    shmoo_cbi.hbmc_shmoo_bist_status_get = dnx_hbmc_bist_status_get_cb;

    shmoo_cbi.hbmc_shmoo_model_part_get = dnx_hbmc_model_part_get_cb;

    shmoo_cbi.hbmc_shmoo_phy_channel_dwords_alignment_check = dnx_hbmc_phy_channel_dwords_alignment_check_cb;
    SHR_IF_ERR_EXIT(soc_hbm16_shmoo_interface_cb_register(unit, shmoo_cbi));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_index_verify(
    int unit,
    int hbm_index)
{

    uint32 nof_hbms;
    SHR_FUNC_INIT_VARS(unit);

    nof_hbms = dnx_data_dram.general_info.max_nof_drams_get(unit);
    if (hbm_index >= nof_hbms)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "bad param hbm_index=%d\n", hbm_index);
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_dram_and_channel_indexes_verify(
    int unit,
    int hbmc_ndx,
    int channel)
{
    uint32 nof_hbms;
    uint32 nof_channels_per_hbm;
    SHR_FUNC_INIT_VARS(unit);

    nof_hbms = dnx_data_dram.general_info.max_nof_drams_get(unit);
    nof_channels_per_hbm = dnx_data_dram.general_info.nof_channels_get(unit);
    if ((hbmc_ndx >= nof_hbms) || (channel >= nof_channels_per_hbm))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "bad param hbm_index=%d, channel=%d \n", hbmc_ndx, channel);
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_steps_before_out_of_soft_reset(
    int unit,
    int hbm_index)
{
    SHR_FUNC_INIT_VARS(unit);

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): register CBs\n"), FUNCTION_NAME()));
    SHR_IF_ERR_EXIT(dnx_hbmc_call_backs_register(unit));

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): configure PLLs\n"), FUNCTION_NAME()));
    SHR_IF_ERR_EXIT(soc_hbm16_shmoo_phy_cfg_pll(unit, hbm_index));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_configure_plls(
    int unit,
    int hbm_index,
    const hbmc_shmoo_pll_t * pll_info)
{
    SHR_FUNC_INIT_VARS(unit);

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): sanity checks\n"), FUNCTION_NAME()));
    SHR_NULL_CHECK(pll_info, _SHR_E_PARAM, "pll_info");
    SHR_INVOKE_VERIFY_DNXC(dnx_hbmc_index_verify(unit, hbm_index));

    LOG_VERBOSE(BSL_LOG_MODULE,
                (BSL_META_U
                 (unit,
                  "%s(): (enter) drc_ndx=%d, pll_info->enableb_aux_post=%d, pll_info->enableb_ch_bitmap=%d, "
                  "pll_info->fref_eff_info=%d, pll_info->mdiv_aux_post=%d,"
                  "pll_info->mdiv_ch[0]=%d, pll_info->mdiv_ch[1]=%d, pll_info->mdiv_ch[2]=%d, "
                  "pll_info->mdiv_ch[3]=%d, pll_info->mdiv_ch[4]=%d, pll_info->mdiv_ch[5]=%d,"
                  "pll_info->ndiv_frac_mode_sel=%d, pll_info->ndiv_int=%d, pll_info->ndiv_p=%d, pll_info->ndiv_q=%d,"
                  " pll_info->pdiv=%d, pll_info->ssc_limit=%d, pll_info->ssc_mode=%d,"
                  "pll_info->ssc_step=%d, pll_info->vco_fb_div2=%d\n"), FUNCTION_NAME(), hbm_index,
                 pll_info->enableb_aux_post, pll_info->enableb_ch_bitmap, pll_info->fref_eff_info,
                 pll_info->mdiv_aux_post, pll_info->mdiv_ch[0], pll_info->mdiv_ch[1], pll_info->mdiv_ch[2],
                 pll_info->mdiv_ch[3], pll_info->mdiv_ch[4], pll_info->mdiv_ch[5], pll_info->ndiv_frac_mode_sel,
                 pll_info->ndiv_int, pll_info->ndiv_p, pll_info->ndiv_q, pll_info->pdiv, pll_info->ssc_limit,
                 pll_info->ssc_mode, pll_info->ssc_step, pll_info->vco_fb_div2));

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): put pll into reset\n"), FUNCTION_NAME()));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_pll_control_set(unit, hbm_index, 0, 0));

    LOG_VERBOSE(BSL_LOG_MODULE,
                (BSL_META_U(unit, "%s(): make changes according to pll_info fields\n"), FUNCTION_NAME()));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_pll_config_set(unit, hbm_index, pll_info));

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_pll_control_set(unit, hbm_index, 1, 0));

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): poll for pll_lock field\n"), FUNCTION_NAME()));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_pll_status_locked_poll(unit, hbm_index));

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_pll_control_set(unit, hbm_index, 1, 1));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_pll_configuration_for_apd_phy(
    int unit,
    int hbm_index)
{
    SHR_FUNC_INIT_VARS(unit);

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(hbm%d): put pll into reset\n"), FUNCTION_NAME(), hbm_index));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_pll_control_set(unit, hbm_index, 0, 0));

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(hbm%d): configure pll\n"), FUNCTION_NAME(), hbm_index));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_pll_configuration_for_apd_phy(unit, hbm_index));

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(hbm%d): take pll out of reset\n"), FUNCTION_NAME(), hbm_index));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_pll_control_set(unit, hbm_index, 1, 0));

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(hbm%d): poll for pll_lock field\n"), FUNCTION_NAME(), hbm_index));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_pll_status_locked_poll(unit, hbm_index));

    LOG_VERBOSE(BSL_LOG_MODULE,
                (BSL_META_U(unit, "%s(hbm%d): take pll out of post reset\n"), FUNCTION_NAME(), hbm_index));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_pll_control_set(unit, hbm_index, 1, 1));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_phy_out_of_reset(
    int unit,
    int hbm_index)
{
    SHR_FUNC_INIT_VARS(unit);

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): allow access to phy registers\n"), FUNCTION_NAME()));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_dynamic_memory_access_set(unit, hbm_index, 1));

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): take phy control out of reset\n"), FUNCTION_NAME()));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_phy_control_out_of_reset_config(unit, hbm_index));

    LOG_VERBOSE(BSL_LOG_MODULE,
                (BSL_META_U(unit, "%s(): phy channel(7:0) & midstack out of reset\n"), FUNCTION_NAME()));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_phy_channel_out_of_reset_config(unit, hbm_index));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_access_init(
    int unit)
{
    int nof_hbms;
    uint32 dram_bitmap[1];
    int hbm_index;
    SHR_FUNC_INIT_VARS(unit);

    dram_bitmap[0] = dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap;
    nof_hbms = dnx_data_dram.general_info.max_nof_drams_get(unit);
    SHR_BIT_ITER(dram_bitmap, nof_hbms, hbm_index)
    {

        SHR_IF_ERR_EXIT(dnx_hbmc_channels_soft_reset_set(unit, hbm_index, 1));

        SHR_IF_ERR_EXIT(dnx_hbmc_channels_soft_init_set(unit, hbm_index, 1));

        SHR_IF_ERR_EXIT(dnx_hbmc_steps_before_out_of_soft_reset(unit, hbm_index));

        SHR_IF_ERR_EXIT(dnx_hbmc_channels_soft_reset_set(unit, hbm_index, 0));

        SHR_IF_ERR_EXIT(dnx_hbmc_channels_soft_init_set(unit, hbm_index, 0));

        SHR_IF_ERR_EXIT(dnx_hbmc_phy_out_of_reset(unit, hbm_index));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_apd_phy_pll_init(
    int unit)
{
    uint32 nof_hbms = dnx_data_dram.general_info.max_nof_drams_get(unit);
    uint32 dram_bitmap[1] = { dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap };
    int hbm_index;
    SHR_FUNC_INIT_VARS(unit);

    SHR_BIT_ITER(dram_bitmap, nof_hbms, hbm_index)
    {

        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit, "%s(hbmc%d): Put all EMI blocks into soft reset\n"), FUNCTION_NAME(), hbm_index));
        SHR_IF_ERR_EXIT(dnx_hbmc_tdu_soft_reset_set(unit, hbm_index, TRUE));
        SHR_IF_ERR_EXIT(dnx_hbmc_hbmc_soft_reset_set(unit, hbm_index, TRUE));
        SHR_IF_ERR_EXIT(dnx_hbmc_hrc_soft_reset_set(unit, hbm_index, TRUE));
        SHR_IF_ERR_EXIT(dnx_hbmc_channels_soft_reset_set(unit, hbm_index, TRUE));

        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit, "%s(hbmc%d): Put all EMI blocks into soft init\n"), FUNCTION_NAME(), hbm_index));
        SHR_IF_ERR_EXIT(dnx_hbmc_tdu_soft_init_set(unit, hbm_index, TRUE));
        SHR_IF_ERR_EXIT(dnx_hbmc_hbmc_soft_init_set(unit, hbm_index, TRUE));
        SHR_IF_ERR_EXIT(dnx_hbmc_hrc_soft_init_set(unit, hbm_index, TRUE));
        SHR_IF_ERR_EXIT(dnx_hbmc_channels_soft_init_set(unit, hbm_index, TRUE));

        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit, "%s(hbmc%d): Take all TDU blocks out of soft reset\n"), FUNCTION_NAME(),
                     hbm_index));
        SHR_IF_ERR_EXIT(dnx_hbmc_tdu_soft_reset_set(unit, hbm_index, FALSE));

        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit, "%s(hbmc%d): Take HBMC block out of soft reset\n"), FUNCTION_NAME(), hbm_index));
        SHR_IF_ERR_EXIT(dnx_hbmc_hbmc_soft_reset_set(unit, hbm_index, FALSE));

        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit, "%s(hbmc%d): Take all TDU blocks out of soft init\n"), FUNCTION_NAME(),
                     hbm_index));
        SHR_IF_ERR_EXIT(dnx_hbmc_tdu_soft_init_set(unit, hbm_index, FALSE));

        LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(hbmc%d): Configure the PLL\n"), FUNCTION_NAME(), hbm_index));
        SHR_IF_ERR_EXIT(dnx_hbmc_pll_configuration_for_apd_phy(unit, hbm_index));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_apd_phy_init(
    int unit)
{
    uint32 nof_hbms = dnx_data_dram.general_info.max_nof_drams_get(unit);
    uint32 dram_bitmap[1] = { dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap };
    int hbm_index;
    int global_hbm_index;
    SHR_FUNC_INIT_VARS(unit);

    SHR_BIT_ITER(dram_bitmap, nof_hbms, hbm_index)
    {

        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit, "%s(hbmc%d): allow dynamic memory access to HBMC tables\n"), FUNCTION_NAME(),
                     hbm_index));
        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hbmc_dynamic_memory_access_set(unit, hbm_index, TRUE));

        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit, "%s(hbmc%d): Take HBMC block out of soft init\n"), FUNCTION_NAME(), hbm_index));
        SHR_IF_ERR_EXIT(dnx_hbmc_hbmc_soft_init_set(unit, hbm_index, FALSE));

        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit, "%s(hbmc%d): Init the PHY through firmware\n"), FUNCTION_NAME(), hbm_index));
        SHR_IF_ERR_EXIT(dnx_hbmc_firmware_phy_init(unit, hbm_index));

        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit, "%s(hbmc%d): Take HBM channels out of soft reset\n"), FUNCTION_NAME(),
                     hbm_index));
        SHR_IF_ERR_EXIT(dnx_hbmc_channels_soft_reset_set(unit, hbm_index, FALSE));

        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit, "%s(hbmc%d): allow dynamic memory access to HCC tables\n"), FUNCTION_NAME(),
                     hbm_index));
        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hcc_dynamic_memory_access_set(unit, hbm_index, TRUE));
    }

    for (global_hbm_index = 0; global_hbm_index < nof_hbms; ++global_hbm_index)
    {

        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit, "%s(hbmc%d): Take HRC block out of soft reset\n"), FUNCTION_NAME(),
                     global_hbm_index));
        SHR_IF_ERR_EXIT(dnx_hbmc_hrc_soft_reset_set(unit, global_hbm_index, FALSE));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_pll_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_dram.hbm.feature_get(unit, dnx_data_dram_hbm_apd_phy))
    {
        SHR_IF_ERR_EXIT(dnx_hbmc_apd_phy_pll_init(unit));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_hbmc_access_init(unit));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_phy_init(
    int unit)
{
    int nof_hbms;
    int nof_channels_in_hbm;
    uint32 dram_bitmap[1];
    int hbm_index;
    SHR_FUNC_INIT_VARS(unit);

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): no data into phy\n"), FUNCTION_NAME()));
    nof_hbms = dnx_data_dram.general_info.max_nof_drams_get(unit);

    dram_bitmap[0] = dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap;

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): init phy through phy registers\n"), FUNCTION_NAME()));
    nof_channels_in_hbm = dnx_data_dram.general_info.nof_channels_get(unit);
    SHR_BIT_ITER(dram_bitmap, nof_hbms, hbm_index)
    {
        for (int channel = 0; channel < nof_channels_in_hbm; ++channel)
        {
            SHR_IF_ERR_EXIT(soc_hbm16_shmoo_phy_init(unit, hbm_index, channel));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_configure(
    int unit)
{

    uint32 dram_bitmap[1] = { dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap };
    uint32 nof_hbms = dnx_data_dram.general_info.max_nof_drams_get(unit);
    int hbm_index;
    SHR_FUNC_INIT_VARS(unit);

    SHR_BIT_ITER(dram_bitmap, nof_hbms, hbm_index)
    {
        LOG_VERBOSE(BSL_LOG_MODULE,
                    (BSL_META_U(unit, "%s(): configure channels for HBM%d\n"), FUNCTION_NAME(), hbm_index));
        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hcc_hbm_config(unit, hbm_index));
        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hcc_tsm_config(unit, hbm_index));
        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hcc_data_source_config(unit, hbm_index));
    }

exit:
    SHR_FUNC_EXIT;
}

void
dnx_hbmc_mode_registers_default_values_get(
    int unit,
    int is_hbm2e,
    dnx_hbmc_mode_registers_t * mrs)
{

    uint32 command_address_parity = dnx_data_dram.general_info.command_address_parity_get(unit);
    uint32 dq_write_parity = dnx_data_dram.general_info.dq_write_parity_get(unit);
    uint32 dq_read_parity = dnx_data_dram.general_info.dq_read_parity_get(unit);
    uint32 dbi_write = dnx_data_dram.general_info.dbi_write_get(unit);
    uint32 dbi_read = dnx_data_dram.general_info.dbi_read_get(unit);
    uint32 write_parity_enable = dq_write_parity;

    uint32 read_parity_enable = (dq_read_parity == 0 && dq_write_parity == 0) ? 0 : 1;

    uint32 write_recovery = dnx_data_dram.general_info.timing_params_get(unit)->twr;

    uint32 driver_strength = (dnx_data_dram.hbm.driver_strength_get(unit) - 6) / 3;

    uint32 read_latency = is_hbm2e ?
        dnx_data_dram.general_info.read_latency_hbm2e_get(unit) : dnx_data_dram.general_info.read_latency_get(unit);

    uint32 read_latency_hw_val = read_latency - 2;

    uint32 write_latency = is_hbm2e ?
        dnx_data_dram.general_info.write_latency_hbm2e_get(unit) : dnx_data_dram.general_info.write_latency_get(unit);

    uint32 write_latency_hw_val = write_latency - 1;

    uint32 tras =
        is_hbm2e ? dnx_data_dram.general_info.timing_params_get(unit)->tras_hbm2e : dnx_data_dram.
        general_info.timing_params_get(unit)->tras;
    uint32 bank_group_enabled = 1;

    uint32 burst_length_hw_val = (dnx_data_dram.hbm.burst_length_get(unit) == 4) ? 1 : 0;

    uint32 ecc_enabled = 1;
    uint32 write_data_mask_disabled = 1;
    uint32 parity_latency = dnx_data_dram.general_info.parity_latency_get(unit);

    uint32 trp_hw_val = dnx_data_dram.general_info.timing_params_get(unit)->trp - 2;

    uint32 internal_vref_hw_val = 1;

    sal_memset(mrs, 0, sizeof(dnx_hbmc_mode_registers_t));

    SHR_BITCOPY_RANGE(&mrs->mr_val[0], 0, &dbi_read, 0, 1);
    SHR_BITCOPY_RANGE(&mrs->mr_val[0], 1, &dbi_write, 0, 1);
    SHR_BITCOPY_RANGE(&mrs->mr_val[0], 4, &read_parity_enable, 0, 1);
    SHR_BITCOPY_RANGE(&mrs->mr_val[0], 5, &write_parity_enable, 0, 1);
    SHR_BITCOPY_RANGE(&mrs->mr_val[0], 6, &command_address_parity, 0, 1);

    SHR_BITCOPY_RANGE(&mrs->mr_val[1], 0, &write_recovery, 0, 5);
    SHR_BITCOPY_RANGE(&mrs->mr_val[1], 5, &driver_strength, 0, 3);

    SHR_BITCOPY_RANGE(&mrs->mr_val[2], 0, &write_latency_hw_val, 0, 3);
    SHR_BITCOPY_RANGE(&mrs->mr_val[2], 3, &read_latency_hw_val, 0, 5);

    SHR_BITCOPY_RANGE(&mrs->mr_val[3], 0, &tras, 0, 6);
    SHR_BITCOPY_RANGE(&mrs->mr_val[3], 6, &bank_group_enabled, 0, 1);
    SHR_BITCOPY_RANGE(&mrs->mr_val[3], 7, &burst_length_hw_val, 0, 1);

    SHR_BITCOPY_RANGE(&mrs->mr_val[4], 0, &ecc_enabled, 0, 1);
    SHR_BITCOPY_RANGE(&mrs->mr_val[4], 1, &write_data_mask_disabled, 0, 1);

    if (read_parity_enable == 0)
    {
        parity_latency = 0;
    }
    SHR_BITCOPY_RANGE(&mrs->mr_val[4], 2, &parity_latency, 0, 2);

    SHR_BITCOPY_RANGE(&mrs->mr_val[6], 3, &trp_hw_val, 0, 5);

    SHR_BITCOPY_RANGE(&mrs->mr_val[15], 0, &internal_vref_hw_val, 0, 3);
}

static shr_error_e
dnx_hbmc_mode_registers_configure(
    int unit,
    int hbm_index)
{
    uint32 channel_index = 0;
    uint32 nof_channels_in_hbm = dnx_data_dram.general_info.nof_channels_get(unit);
    uint32 mr_index = 0;
    uint32 nof_mrs = dnx_data_dram.general_info.nof_mrs_get(unit);
    dnx_hbmc_mode_registers_t mrs;
    SHR_FUNC_INIT_VARS(unit);

    dnx_hbmc_mode_registers_default_values_get(unit, FALSE, &mrs);

    for (channel_index = 0; channel_index < nof_channels_in_hbm; ++channel_index)
    {
        for (mr_index = 0; mr_index < nof_mrs; ++mr_index)
        {
            SHR_IF_ERR_EXIT(dnx_hbmc_mode_register_set(unit, hbm_index, channel_index, mr_index, mrs.mr_val[mr_index]));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hcc_configure(
    int unit,
    int hbm_index)
{
    SHR_FUNC_INIT_VARS(unit);

    LOG_VERBOSE(BSL_LOG_MODULE,
                (BSL_META_U(unit, "%s(hbm%d): Configure channels before out of soft init\n"), FUNCTION_NAME(),
                 hbm_index));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hcc_hbm_config(unit, hbm_index));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hcc_data_source_config(unit, hbm_index));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_cke_set(unit, hbm_index, 1));

    LOG_VERBOSE(BSL_LOG_MODULE,
                (BSL_META_U(unit, "%s(hbm%d): Take HBM channels out of soft init\n"), FUNCTION_NAME(), hbm_index));
    SHR_IF_ERR_EXIT(dnx_hbmc_channels_soft_init_set(unit, hbm_index, FALSE));

    SHR_IF_ERR_EXIT(dnx_hbmc_mode_registers_configure(unit, hbm_index));

    LOG_VERBOSE(BSL_LOG_MODULE,
                (BSL_META_U(unit, "%s(hbm%d): Configure channels after out of soft init\n"), FUNCTION_NAME(),
                 hbm_index));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hcc_tsm_config(unit, hbm_index));
    SHR_IF_ERR_EXIT(dnx_hbmc_hbm_refresh_enable_set(unit, hbm_index, TRUE));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hcc_data_path_enable_set(unit, hbm_index, TRUE));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hcc_request_path_enable_set(unit, hbm_index, TRUE));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_hrc_configure(
    int unit)
{
    uint32 max_nof_drams = dnx_data_dram.general_info.max_nof_drams_get(unit);
    uint32 global_hbm_index;
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_dram.hbm.feature_get(unit, dnx_data_dram_hbm_is_hrc_supported))
    {
        for (global_hbm_index = 0; global_hbm_index < max_nof_drams; ++global_hbm_index)
        {
            LOG_VERBOSE(BSL_LOG_MODULE,
                        (BSL_META_U(unit, "%s(HBM%d): configure HRC\n"), FUNCTION_NAME(), global_hbm_index));
            SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hrc_enable_set(unit, global_hbm_index, TRUE));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_hbm_refresh_enable_bitmap_get(
    int unit,
    int hbm_index,
    uint32 *refresh_enable_per_channel_bitmap)
{
    int nof_channels = dnx_data_dram.general_info.nof_channels_get(unit);
    SHR_FUNC_INIT_VARS(unit);

    *refresh_enable_per_channel_bitmap = 0;

    for (int channel = 0; channel < nof_channels; ++channel)
    {

        uint32 channel_enable_refresh;
        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_enable_refresh_get(unit, hbm_index, channel, &channel_enable_refresh));
        if (channel_enable_refresh)
        {
            *refresh_enable_per_channel_bitmap |= (1 << channel);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_hbm_refresh_enable_bitmap_set(
    int unit,
    int hbm_index,
    uint32 refresh_enable_per_channel_bitmap)
{
    int nof_channels = dnx_data_dram.general_info.nof_channels_get(unit);
    SHR_FUNC_INIT_VARS(unit);

    for (int channel = 0; channel < nof_channels; ++channel)
    {
        uint32 channel_enable_refresh;
        channel_enable_refresh = ! !(refresh_enable_per_channel_bitmap & (1 << channel));
        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_enable_refresh_set(unit, hbm_index, channel, channel_enable_refresh));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_hbm_refresh_enable_set(
    int unit,
    int hbm_index,
    uint32 refresh_enable)
{
    int nof_channels = dnx_data_dram.general_info.nof_channels_get(unit);
    SHR_FUNC_INIT_VARS(unit);

    for (int channel = 0; channel < nof_channels; ++channel)
    {
        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_enable_refresh_set(unit, hbm_index, channel, refresh_enable));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_hbm_init(
    int unit,
    int hbm_index)
{
    uint32 refresh_enable_per_channel_bitmap;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_hbmc_hbm_refresh_enable_bitmap_get(unit, hbm_index, &refresh_enable_per_channel_bitmap));

    SHR_IF_ERR_EXIT(dnx_hbmc_hbm_refresh_enable_bitmap_set(unit, hbm_index, 0));

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): taking hbm into reset\n"), FUNCTION_NAME()));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_reset_control_set(unit, hbm_index, 0));

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_cke_set(unit, hbm_index, 0));

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): set clocks output enable\n"), FUNCTION_NAME()));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_clocks_output_enable_set(unit, hbm_index, 0, 0));

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): set output enable (C,R,CKE,Arfu)\n"), FUNCTION_NAME()));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_output_enable_set(unit, hbm_index, 1));

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_clocks_set(unit, hbm_index, 0, 0));

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): JEDEC requires 200 us waiting time\n"), FUNCTION_NAME()));
    sal_usleep(200);

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): taking hbm out of reset\n"), FUNCTION_NAME()));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_reset_control_set(unit, hbm_index, 1));

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): set clocks\n"), FUNCTION_NAME()));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_clocks_set(unit, hbm_index, 0, 1));

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): JEDEC requires 500 us waiting time\n"), FUNCTION_NAME()));
    sal_usleep(500);

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_cke_set(unit, hbm_index, 1));

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): configure MRs\n"), FUNCTION_NAME()));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_mr_init_set(unit, hbm_index));

    SHR_IF_ERR_EXIT(dnx_hbmc_hbm_refresh_enable_bitmap_set(unit, hbm_index, refresh_enable_per_channel_bitmap));

exit:
    SHR_FUNC_EXIT;
}

static soc_error_t
dnx_hbmc_tune_param_name_string_set(
    int unit,
    int hbm_ndx,
    int channel_ndx,
    const char *name,
    char *name_str)
{
    int len;
    SHR_FUNC_INIT_VARS(unit);
    if (channel_ndx == SHMOO_HBM16_MIDSTACK_CHANNEL)
    {
        len = sal_snprintf(name_str, dnx_drv_soc_property_name_max(), "%s_%s_%d.%d", spn_HBM_TUNE, name, hbm_ndx, unit);
    }
    else
    {
        len =
            sal_snprintf(name_str, dnx_drv_soc_property_name_max(), "%s_%s_%d_%d.%d", spn_HBM_TUNE, name, hbm_ndx,
                         channel_ndx, unit);
    }
    if (len >= dnx_drv_soc_property_name_max())
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "long string for field=%s\n", name);
    }

exit:
    SHR_FUNC_EXIT;

}

static soc_error_t
dnx_hbmc_shmoo_hbm16_entry_set(
    int unit,
    int hbm_ndx,
    int channel_ndx,
    const char *name,
    uint32 value)
{
    char *name_str = NULL;
    char val_str[DNX_HBMC_STR_VAL_SIZE];
    int len;

    SHR_FUNC_INIT_VARS(unit);
    SHR_ALLOC_SET_ZERO(name_str, dnx_drv_soc_property_name_max(), "hbmc_shmoo_hbm16_entry_set", "%s%s%s\r\n", EMPTY,
                       EMPTY, EMPTY);
    SHR_IF_ERR_EXIT(dnx_hbmc_tune_param_name_string_set(unit, hbm_ndx, channel_ndx, name, name_str));

    len = sal_snprintf(val_str, DNX_HBMC_STR_VAL_SIZE, "0x%08X", value);
    if (len >= DNX_HBMC_STR_VAL_SIZE)
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "long string value= 0x%08x, for field=%s\n", value, name);
    }
    if (soc_mem_config_set(name_str, val_str) < 0)
    {
        SHR_ERR_EXIT(_SHR_E_MEMORY, "Failed to save hbm16 shmoo configuration");
    }

exit:
    SHR_FREE(name_str);
    SHR_FUNC_EXIT;
}

static soc_error_t
dnx_hbmc_shmoo_hbm16_entry_get(
    int unit,
    int hbm_ndx,
    int channel_ndx,
    const char *name,
    int *valid,
    uint32 *value)
{
    char *name_str = NULL;
    char *ss;
    SHR_FUNC_INIT_VARS(unit);

    SHR_ALLOC_SET_ZERO(name_str, dnx_drv_soc_property_name_max(), "hbmc_shmoo_hbm16_entry_get", "%s%s%s\r\n", EMPTY,
                       EMPTY, EMPTY);
    SHR_IF_ERR_EXIT(dnx_hbmc_tune_param_name_string_set(unit, hbm_ndx, channel_ndx, name, name_str));
    if ((ss = dnx_drv_soc_property_get_str(unit, name_str)) != NULL)
    {
        *valid = TRUE;
        *value = _shr_ctoi(ss);
    }
    else
    {
        *valid = FALSE;
    }

exit:
    SHR_FREE(name_str);
    SHR_FUNC_EXIT;
}

static soc_error_t
dnx_hbmc_shmoo_hbm16_save(
    int unit,
    int hbm_ndx,
    hbmc_shmoo_config_param_t * shmoo_config_param)
{
    int metadata_ndx;
    const hbmc_shmoo_channel_config_param_t *channel_metadata = soc_hbm16_shmoo_channel_config_param_metadata_get();
    const hbmc_shmoo_midstack_config_param_t *midstack_metadata = soc_hbm16_shmoo_midstack_config_param_metadata_get();

    SHR_FUNC_INIT_VARS(unit);

    for (int channel_ndx = 0; channel_ndx < dnx_data_dram.general_info.nof_channels_get(unit); channel_ndx++)
    {
        for (metadata_ndx = 0; metadata_ndx < HBMC_SHMOO_CHANNEL_METADATA_SIZE; metadata_ndx++)
        {

            if ((shmoo_config_param->channel_data[channel_ndx][metadata_ndx].valid) &&
                ((channel_metadata[metadata_ndx].level & DNX_HBMC_SAVE_RESTORE_LEVELS) != 0))
            {
                SHR_IF_ERR_EXIT(dnx_hbmc_shmoo_hbm16_entry_set
                                (unit, hbm_ndx, channel_ndx, channel_metadata[metadata_ndx].name,
                                 shmoo_config_param->channel_data[channel_ndx][metadata_ndx].value));
            }
        }
    }

    for (metadata_ndx = 0; metadata_ndx < HBMC_SHMOO_MIDSTACK_METADATA_SIZE; metadata_ndx++)
    {

        if ((shmoo_config_param->midstack_data[metadata_ndx].valid) &&
            ((channel_metadata[metadata_ndx].level & DNX_HBMC_SAVE_RESTORE_LEVELS) != 0))
        {
            SHR_IF_ERR_EXIT(dnx_hbmc_shmoo_hbm16_entry_set(unit, hbm_ndx, SHMOO_HBM16_MIDSTACK_CHANNEL,
                                                           midstack_metadata[metadata_ndx].name,
                                                           shmoo_config_param->midstack_data[metadata_ndx].value));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_shmoo_hbm16_restore_from_file(
    int unit,
    int hbm_ndx,
    int is_quiet,
    hbmc_shmoo_config_param_t * shmoo_config_param)
{
    const hbmc_shmoo_channel_config_param_t *channel_metadata = soc_hbm16_shmoo_channel_config_param_metadata_get();
    const hbmc_shmoo_midstack_config_param_t *midstack_metadata = soc_hbm16_shmoo_midstack_config_param_metadata_get();

    SHR_FUNC_INIT_VARS(unit);

    for (int channel_ndx = 0; channel_ndx < dnx_data_dram.general_info.nof_channels_get(unit); channel_ndx++)
    {
        for (int metadata_ndx = 0; metadata_ndx < HBMC_SHMOO_CHANNEL_METADATA_SIZE; metadata_ndx++)
        {

            if ((channel_metadata[metadata_ndx].level & DNX_HBMC_SAVE_RESTORE_LEVELS) == 0)
            {
                shmoo_config_param->channel_data[channel_ndx][metadata_ndx].valid = FALSE;
                continue;
            }
            SHR_IF_ERR_EXIT(dnx_hbmc_shmoo_hbm16_entry_get
                            (unit, hbm_ndx, channel_ndx, channel_metadata[metadata_ndx].name,
                             &shmoo_config_param->channel_data[channel_ndx][metadata_ndx].valid,
                             &shmoo_config_param->channel_data[channel_ndx][metadata_ndx].value));

            if ((channel_metadata[metadata_ndx].level & HBMC_SHMOO_LEVEL_0) &&
                shmoo_config_param->channel_data[channel_ndx][metadata_ndx].valid == FALSE)
            {
                if (is_quiet)
                {
                    SHR_IF_ERR_EXIT_NO_MSG(_SHR_E_PARAM);
                }
                else
                {
                    SHR_ERR_EXIT(_SHR_E_PARAM,
                                 "ch=%d field %s is not valid - unable to restore phy tune parameters, try running full tune instead and save tune parameters again\n",
                                 channel_ndx, channel_metadata[metadata_ndx].name);
                }

            }
        }
    }

    for (int metadata_ndx = 0; metadata_ndx < HBMC_SHMOO_MIDSTACK_METADATA_SIZE; metadata_ndx++)
    {

        if ((midstack_metadata[metadata_ndx].level & DNX_HBMC_SAVE_RESTORE_LEVELS) == 0)
        {
            shmoo_config_param->midstack_data[metadata_ndx].valid = FALSE;
            continue;
        }
        SHR_IF_ERR_EXIT(dnx_hbmc_shmoo_hbm16_entry_get(unit, hbm_ndx, SHMOO_HBM16_MIDSTACK_CHANNEL,
                                                       midstack_metadata[metadata_ndx].name,
                                                       &shmoo_config_param->midstack_data[metadata_ndx].valid,
                                                       &shmoo_config_param->midstack_data[metadata_ndx].value));

        if ((midstack_metadata[metadata_ndx].level & HBMC_SHMOO_LEVEL_0) &&
            (shmoo_config_param->midstack_data[metadata_ndx].valid == FALSE))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "field %s is not valid - unable to restore phy tune parameters, try running full tune instead and save tune parameters again\n",
                         midstack_metadata[metadata_ndx].name);
        }
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_cattrip_indication_mask_set(
    int unit,
    int hbm_index,
    uint32 mask_cattrip_indication)
{
    SHR_FUNC_INIT_VARS(unit);
    if (mask_cattrip_indication)
    {

        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_cattrip_indication_mask_set(unit, hbm_index, 1));
    }
    else
    {

        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_cattrip_interrupt_clear(unit, hbm_index));
        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_cattrip_indication_mask_set(unit, hbm_index, 0));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_cattrip_indication_disable(
    int unit,
    uint32 dram_start,
    uint32 dram_end,
    int *should_reenable_cattrip)
{
    int is_valid;
    uint32 dram_index;
    SHR_FUNC_INIT_VARS(unit);

    for (dram_index = dram_start; dram_index <= dram_end; ++dram_index)
    {
        SHR_IF_ERR_EXIT(dnx_dram_index_is_valid(unit, dram_index, &is_valid));
        if (is_valid)
        {
            SHR_IF_ERR_EXIT(dnx_hbmc_cattrip_indication_mask_set(unit, dram_index, 1));
            should_reenable_cattrip[dram_index] = TRUE;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_cattrip_indication_restore(
    int unit,
    uint32 dram_start,
    uint32 dram_end,
    const int *should_reenable_cattrip)
{
    uint32 dram_index;
    SHR_FUNC_INIT_VARS(unit);

    for (dram_index = dram_start; dram_index <= dram_end; ++dram_index)
    {
        if (should_reenable_cattrip[dram_index])
        {
            SHR_IF_ERR_EXIT(dnx_hbmc_cattrip_indication_mask_set(unit, dram_index, 0));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_action_to_derived_action(
    int unit,
    int hbm_index,
    dnx_hbmc_phy_tune_action_e action,
    dnx_hbmc_phy_tune_action_e * derived_action,
    hbmc_shmoo_config_param_t * config_params_p,
    int *shmoo_action_p)
{
    int nof_hbms;
    SHR_FUNC_INIT_VARS(unit);
    nof_hbms = dnx_data_dram.general_info.max_nof_drams_get(unit);
    if (hbm_index >= nof_hbms)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal param 'hbm_index'=%d. Must be smaller that %d\r\n", hbm_index, nof_hbms);
    }
    sal_memset(config_params_p, 0x0, sizeof(*config_params_p));
    switch (action)
    {
        case DNX_HBMC_RESTORE_TUNE_PARAMETERS_FROM_OTP:
        {
            SHR_IF_ERR_EXIT(dnx_hbmc_otp_shmoo_hbm16_restore_from_otp(unit, hbm_index, FALSE, config_params_p));
            *derived_action = DNX_HBMC_RESTORE_TUNE_PARAMETERS_FROM_OTP;
            *shmoo_action_p = SHMOO_HBM16_ACTION_RESTORE;
            break;
        }
        case DNX_HBMC_RESTORE_TUNE_PARAMETERS_FROM_SOC_PROPERTIES:
        {
            SHR_IF_ERR_EXIT(dnx_hbmc_shmoo_hbm16_restore_from_file(unit, hbm_index, FALSE, config_params_p));
            *derived_action = DNX_HBMC_RESTORE_TUNE_PARAMETERS_FROM_SOC_PROPERTIES;
            *shmoo_action_p = SHMOO_HBM16_ACTION_RESTORE;
            break;
        }
        case DNX_HBMC_RESTORE_TUNE_PARAMS_FROM_SOC_PROPS_OR_OTP_OR_TUNE:
        {

            if (SHR_SUCCESS(dnx_hbmc_shmoo_hbm16_restore_from_file(unit, hbm_index, TRUE, config_params_p)))
            {
                *derived_action = DNX_HBMC_RESTORE_TUNE_PARAMETERS_FROM_SOC_PROPERTIES;
                *shmoo_action_p = SHMOO_HBM16_ACTION_RESTORE;
            }
            else if (SHR_SUCCESS(dnx_hbmc_otp_shmoo_hbm16_restore_from_otp(unit, hbm_index, TRUE, config_params_p)))
            {
                *derived_action = DNX_HBMC_RESTORE_TUNE_PARAMETERS_FROM_OTP;
                *shmoo_action_p = SHMOO_HBM16_ACTION_RESTORE;
            }
            else
            {
                *derived_action = DNX_HBMC_RUN_TUNE;

                *shmoo_action_p = SHMOO_HBM16_ACTION_RUN_AND_SAVE;
            }
            break;
        }
        case DNX_HBMC_RESTORE_TUNE_PARAMS_FROM_OTP_OR_TUNE:
        {

            if (SHR_SUCCESS(dnx_hbmc_otp_shmoo_hbm16_restore_from_otp(unit, hbm_index, TRUE, config_params_p)))
            {
                *derived_action = DNX_HBMC_RESTORE_TUNE_PARAMETERS_FROM_OTP;
                *shmoo_action_p = SHMOO_HBM16_ACTION_RESTORE;
            }
            else
            {
                *derived_action = DNX_HBMC_RUN_TUNE;

                *shmoo_action_p = SHMOO_HBM16_ACTION_RUN_AND_SAVE;
            }
            break;
        }
        case DNX_HBMC_RUN_TUNE:
        {

            *shmoo_action_p = SHMOO_HBM16_ACTION_RUN_AND_SAVE;
            *derived_action = DNX_HBMC_RUN_TUNE;
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal param 'action'=%d\n", action);
            break;
        }
    }
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_run_phy_tune(
    int unit,
    int hbm_index,
    int channel,
    int shmoo_type,
    uint32 flags,
    dnx_hbmc_phy_tune_action_e action)
{
    int shmoo_action;
    int hbm_iter;
    uint32 nof_hbms = dnx_data_dram.general_info.max_nof_drams_get(unit);

    uint32 dram_bitmap[1] = { 0 };
    uint32 nof_channels_in_hbm;
    int temp_monitoring_is_active;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_hbmc_temp_monitor_is_active(unit, &temp_monitoring_is_active));
    if (temp_monitoring_is_active)
    {
        SHR_IF_ERR_EXIT(dnx_hbmc_temp_monitor_pause(unit));
    }
    if (action == DNX_HBMC_SKIP_TUNE)
    {

        LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): shmoo is skipped\n"), FUNCTION_NAME()));
        SHR_EXIT();
    }

    if (hbm_index != DNX_HBMC_ITER_ALL)
    {
        SHR_BITSET(dram_bitmap, hbm_index);
        nof_channels_in_hbm = channel + 1;
    }
    else
    {
        dram_bitmap[0] = dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap;
        nof_channels_in_hbm = dnx_data_dram.general_info.nof_channels_get(unit);
        channel = 0;
    }

    SHR_BIT_ITER(dram_bitmap, nof_hbms, hbm_iter)
    {

        dnx_hbmc_phy_tune_action_e derived_action;
        hbmc_shmoo_config_param_t config_params;

        SHR_IF_ERR_EXIT(dnx_hbmc_cattrip_indication_mask_set(unit, hbm_iter, 1));
        SHR_IF_ERR_EXIT(dnx_hbmc_action_to_derived_action
                        (unit, hbm_iter, action, &derived_action, &config_params, &shmoo_action));

        for (; channel < nof_channels_in_hbm; ++channel)
        {

            SHR_IF_ERR_EXIT(dnx_hbmc_enable_refresh_cb(unit, hbm_iter, channel, 0));

            SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_ecc_enable(unit, hbm_iter, channel, 0));

            SHR_IF_ERR_EXIT(soc_hbm16_shmoo_ctl
                            (unit, hbm_iter, channel, shmoo_type, flags, shmoo_action, &config_params));

            if ((derived_action == DNX_HBMC_RESTORE_TUNE_PARAMETERS_FROM_SOC_PROPERTIES) ||
                (derived_action == DNX_HBMC_RESTORE_TUNE_PARAMETERS_FROM_OTP))
            {

                SHR_IF_ERR_EXIT(_hbm16_phy_channel_reset(unit, 0, hbm_iter, channel));
            }

            SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_ecc_enable(unit, hbm_iter, channel, 1));

            SHR_IF_ERR_EXIT(dnx_hbmc_enable_refresh_cb(unit, hbm_iter, channel, 1));
        }

        channel = 0;

        SHR_IF_ERR_EXIT(dnx_hbmc_cattrip_indication_mask_set(unit, hbm_iter, 0));

        if (derived_action == DNX_HBMC_RUN_TUNE || derived_action == DNX_HBMC_RESTORE_TUNE_PARAMETERS_FROM_OTP)
        {

            SHR_IF_ERR_EXIT(dnx_hbmc_shmoo_hbm16_save(unit, hbm_iter, &config_params));
        }
    }

    if (temp_monitoring_is_active)
    {

        sal_usleep(200000);
        SHR_IF_ERR_EXIT(dnx_hbmc_temp_monitor_resume(unit));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_tdu_atm_get(
    int unit,
    const uint32 **atm)
{
    uint32 max_nof_hbms = dnx_data_dram.general_info.max_nof_drams_get(unit);
    uint32 dram_bitmap = dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap;
    int nof_hbms;

    SHR_FUNC_INIT_VARS(unit);

    shr_bitop_range_count(&dram_bitmap, 0, max_nof_hbms, &nof_hbms);

    *atm = &(dnx_data_dram.address_translation.matrix_configuration_get(unit, nof_hbms - 1)->logical_to_physical[0]);

    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_tdu_atm_configure(
    int unit)
{
    const uint32 *atm;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_hbmc_tdu_atm_get(unit, &atm));

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_tdu_atm_configure(unit, atm));
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_tdu_configure(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_tdu_configure(unit));

    SHR_IF_ERR_EXIT(dnx_dram_block_configure(unit));

    SHR_IF_ERR_EXIT(dnx_hbmc_tdu_atm_configure(unit));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_bist_run(
    int unit,
    int flags,
    int hbmc_ndx,
    int channel,
    int is_blocking,
    const hbmc_shmoo_bist_info_t * info,
    int *is_polling_required)
{
    int override_bist_configuration = 0;
    uint32 temp_ecc;
    uint32 temp_dbi_read;
    uint32 temp_dbi_write;
    uint8 should_restore_temp_info = 0;
    uint8 in_loopback_mode = 0;
    uint32 mr_orig_value = 0;
    hbmc_shmoo_bist_info_t temp_info = { 0 };
    hbmc_shmoo_bist_info_t loopback_default_info = { 0 };
    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_hbmc_dram_and_channel_indexes_verify(unit, hbmc_ndx, channel));

    *is_polling_required = TRUE;

    if (flags & (HBMC_SHMOO_CFG_FLAG_LOOPBACK_MODE_WRITE_LFSR | HBMC_SHMOO_CFG_FLAG_LOOPBACK_MODE_READ_LFSR))
    {

        in_loopback_mode = TRUE;
        is_blocking = TRUE;
        *is_polling_required = FALSE;

        if (flags & HBMC_SHMOO_CFG_FLAG_LOOPBACK_MODE_READ_LFSR)
        {

            loopback_default_info.write_weight = 0x0;
            loopback_default_info.read_weight = 0x1000;
        }
        else
        {

            loopback_default_info.write_weight = 0x1000;
            loopback_default_info.read_weight = 0x0;
        }

        loopback_default_info.bist_timer_us = 0;
        loopback_default_info.bist_num_actions[0] = 0x1000000;
        loopback_default_info.bist_num_actions[1] = 0;
        loopback_default_info.bank_start_index = 0x00000000;
        loopback_default_info.bank_end_index = 0x0000001F;
        loopback_default_info.column_start_index = 0x00000000;
        loopback_default_info.column_end_index = 0x0000001F;
        loopback_default_info.row_start_index = 0x00000000;
        loopback_default_info.row_end_index = 0x00003FFF;
        loopback_default_info.bist_refresh_enable = 0;
        loopback_default_info.bist_ignore_address = 1;
        loopback_default_info.same_row_commands = 8;
        loopback_default_info.data_mode = DBAL_ENUM_FVAL_DRAM_BIST_MODE_PRBS;
        for (int i = 0; i < HBMC_SHMOO_BIST_NOF_PRBS_DATA_SEEDS; i++)
        {
            loopback_default_info.prbs_seeds[i] = 0xAAAAA;
        }
        info = &loopback_default_info;
    }

    SHR_IF_ERR_EXIT(dnx_dram_db.override_bist_configurations_during_tuning.get(unit, &override_bist_configuration));
    if (override_bist_configuration)
    {

        SHR_IF_ERR_EXIT(dnx_hbmc_bist_configuration_set(unit, hbmc_ndx, channel, info));
    }
    else if (flags & HBMC_SHMOO_CFG_FLAG_FORCE_BIST_CONFIGURATION)
    {

        SHR_IF_ERR_EXIT(dnx_hbmc_bist_configuration_get(unit, hbmc_ndx, channel, &temp_info));
        SHR_IF_ERR_EXIT(dnx_hbmc_bist_configuration_set(unit, hbmc_ndx, channel, info));
        should_restore_temp_info = 1;
    }

    if (in_loopback_mode)
    {

        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hcc_configuration_ecc_dbi_get
                        (unit, hbmc_ndx, channel, &temp_ecc, &temp_dbi_read, &temp_dbi_write));
        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hcc_configuration_ecc_dbi_set(unit, hbmc_ndx, channel, 0, 0, 0));

        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_mr_get(unit, hbmc_ndx, channel, 7, &mr_orig_value));

        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_mr_set(unit, hbmc_ndx, channel, 7, 0x1));

        if (flags & HBMC_SHMOO_CFG_FLAG_LOOPBACK_MODE_READ_LFSR)
        {

            SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_mr_set(unit, hbmc_ndx, channel, 7, 0xb));
        }
        else
        {

            SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_mr_set(unit, hbmc_ndx, channel, 7, 0x21));

        }
    }

    if (!SAL_BOOT_PLISIM)
    {

        SHR_IF_ERR_EXIT(dnx_hbmc_bist_start(unit, hbmc_ndx, channel));

        if (is_blocking && info->bist_timer_us)
        {

            sal_usleep(info->bist_timer_us);

            SHR_IF_ERR_EXIT(dnx_hbmc_bist_stop(unit, hbmc_ndx, channel));
        }
        else
        {
            COMPILER_UINT64 orig_nof_bist_actions_for_arethmetics;

            COMPILER_64_SET(orig_nof_bist_actions_for_arethmetics, info->bist_num_actions[1],
                            info->bist_num_actions[0]);
            if (COMPILER_64_IS_ZERO(orig_nof_bist_actions_for_arethmetics))
            {

                *is_polling_required = FALSE;
                SHR_EXIT();
            }

            if (is_blocking)
            {

                SHR_IF_ERR_EXIT(dnx_hbmc_bist_run_done_poll(unit, hbmc_ndx, channel));
            }
        }
    }

    if (in_loopback_mode)
    {
        if (flags & HBMC_SHMOO_CFG_FLAG_LOOPBACK_MODE_WRITE_LFSR)
        {

            loopback_default_info.bist_num_actions[0] = 0x1;
            loopback_default_info.bist_num_actions[1] = 0;
            loopback_default_info.write_weight = 0x0;
            loopback_default_info.read_weight = 0x1;
            info = &loopback_default_info;
            SHR_IF_ERR_EXIT(dnx_hbmc_bist_configuration_set(unit, hbmc_ndx, channel, info));

            SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_mr_set(unit, hbmc_ndx, channel, 7, 0x17));

            if (!SAL_BOOT_PLISIM)
            {

                SHR_IF_ERR_EXIT(dnx_hbmc_bist_start(unit, hbmc_ndx, channel));
                SHR_IF_ERR_EXIT(dnx_hbmc_bist_run_done_poll(unit, hbmc_ndx, channel));
            }
        }

        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hcc_configuration_ecc_dbi_set
                        (unit, hbmc_ndx, channel, temp_ecc, temp_dbi_read, temp_dbi_write));

        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_mr_set(unit, hbmc_ndx, channel, 7, mr_orig_value));
    }

    if (should_restore_temp_info)
    {
        SHR_IF_ERR_EXIT(dnx_hbmc_bist_configuration_set(unit, hbmc_ndx, channel, &temp_info));
    }

exit:
    SHR_FUNC_EXIT;
}

static void
dnx_hbmc_bist_err_bitmap_log(
    int unit,
    char *bitmap_title,
    uint32 *err_bitmap,
    uint32 bitmap_size)
{
    uint32 i;
    int is_any_bit_set = FALSE;

    LOG_ERROR(BSL_LOG_MODULE, (BSL_META_U(unit, "Bits set in %s: "), bitmap_title));
    SHR_BIT_ITER(err_bitmap, bitmap_size, i)
    {
        LOG_ERROR(BSL_LOG_MODULE, ("%d ", i));
        is_any_bit_set = TRUE;
    }

    if (!is_any_bit_set)
    {
        LOG_ERROR(BSL_LOG_MODULE, ("None"));
    }

    LOG_ERROR(BSL_LOG_MODULE, ("\n"));
}

static void
dnx_hbmc_bist_result_report(
    int unit,
    int hbmc_index,
    int hbmc_channel,
    hbmc_shmoo_bist_status_cnt_t * sts_counters,
    hbmc_shmoo_bist_err_cnt_t * bist_err_cnt,
    hbmc_ecc_err_cnt_t * ecc_err_cnt)
{
    if (bist_err_cnt->bist_data_err_cnt > 0)
    {
        LOG_ERROR(BSL_LOG_MODULE, (BSL_META_U(unit,
                                              "HBMC BIST FAILED for hbmc_index=%d, hbmc_channel=%d:\n"),
                                   hbmc_index, hbmc_channel));
        LOG_ERROR(BSL_LOG_MODULE, (BSL_META_U(unit,
                                              "write_cmd_counter=0x%x%x, read_cmd_counter=0x%x%x, read_data_counter=0x%x%x\n"),
                                   sts_counters->write_cmd_counter[1], sts_counters->write_cmd_counter[0],
                                   sts_counters->read_cmd_counter[1], sts_counters->read_cmd_counter[0],
                                   sts_counters->read_data_counter[1], sts_counters->read_cmd_counter[0]));
        LOG_ERROR(BSL_LOG_MODULE, (BSL_META_U(unit,
                                              "global_err_cnt=%d\n -data_err_cnt=%d\n"),
                                   bist_err_cnt->bist_global_err_cnt, bist_err_cnt->bist_data_err_cnt));
        dnx_hbmc_bist_err_bitmap_log(unit, "data_err_bits", bist_err_cnt->bist_data_err_bits,
                                     HBMC_SHMOO_BIST_DATA_ERR_BITS);
        LOG_ERROR(BSL_LOG_MODULE, ("\n"));

    }

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit,
                                            "corrected_err_cnt_lower_channel=0x%x%x, corrected_err_cnt_upper_channel=0x%x%x\n"),
                                 ecc_err_cnt->corrected_err_cnt_lower_channel[1],
                                 ecc_err_cnt->corrected_err_cnt_lower_channel[0],
                                 ecc_err_cnt->corrected_err_cnt_upper_channel[1],
                                 ecc_err_cnt->corrected_err_cnt_upper_channel[0]));
    LOG_VERBOSE(BSL_LOG_MODULE,
                (BSL_META_U(unit, "detected_err_cnt_lower_channel=0x%x%x, detected_err_cnt_upper_channel=0x%x%x\n"),
                 ecc_err_cnt->detected_err_cnt_lower_channel[1], ecc_err_cnt->detected_err_cnt_lower_channel[0],
                 ecc_err_cnt->detected_err_cnt_upper_channel[1], ecc_err_cnt->detected_err_cnt_upper_channel[0]));
    LOG_VERBOSE(BSL_LOG_MODULE, ("\n"));
}

shr_error_e
dnx_hbmc_ecc_err_counters_clear(
    int unit)
{
    int hbmc_index = 0, hbmc_channel = 0;
    hbmc_ecc_err_cnt_t ecc_err_cnt;
    int dram_bitmap_size = dnx_data_dram.general_info.max_nof_drams_get(unit);
    uint32 dram_bitmap[1] = { dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap };
    SHR_FUNC_INIT_VARS(unit);

    SHR_BIT_ITER(dram_bitmap, dram_bitmap_size, hbmc_index)
    {

        for (hbmc_channel = 0; hbmc_channel < dnx_data_dram.general_info.nof_channels_get(unit); hbmc_channel++)
        {

            SHR_IF_ERR_EXIT(dnx_hbmc_ecc_errors_get(unit, hbmc_index, hbmc_channel, &ecc_err_cnt));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_bist_handle(
    int unit)
{
    hbmc_shmoo_bist_info_t info = { 0 };
    hbmc_shmoo_bist_err_cnt_t bist_err_cnt = { 0 };
    int hbmc_index = 0, hbmc_channel = 0;
    int fail_indication = FALSE;
    int is_polling_required[DNX_DATA_MAX_DRAM_GENERAL_INFO_MAX_NOF_DRAMS][DNX_DATA_MAX_DRAM_GENERAL_INFO_NOF_CHANNELS] =
        { {0} };
    int dram_bitmap_size = dnx_data_dram.general_info.max_nof_drams_get(unit);
    uint32 dram_bitmap[1] = { dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap };
    hbmc_ecc_err_cnt_t ecc_err_cnt;
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_dram.general_info.tune_mode_on_init_get(unit) != DNX_HBMC_SKIP_TUNE &&
        dnx_data_dram.hbm.enable_dram_bist_on_init_get(unit))
    {
        LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): Run HBM BIST\n"), FUNCTION_NAME()));

        info.write_weight = DNX_HBMC_INIT_BIST_WRITE_WEIGHT;
        info.read_weight = DNX_HBMC_INIT_BIST_READ_WEIGHT;
        info.bist_num_actions[0] = DNX_HBMC_INIT_BIST_NUM_ACTIONS;
        info.bist_num_actions[1] = 0;
        info.row_start_index = 0;
        info.column_start_index = 0;
        info.bank_start_index = 0;
        info.row_end_index = dnx_data_dram.general_info.dram_info_get(unit)->nof_rows - 1;
        info.column_end_index = dnx_data_dram.general_info.dram_info_get(unit)->nof_columns - 1;
        info.bank_end_index = dnx_data_dram.general_info.dram_info_get(unit)->nof_banks - 1;
        info.same_row_commands = DNX_HBMC_INIT_BIST_SAME_ROW_COMMANDS;
        info.data_mode = DBAL_ENUM_FVAL_DRAM_BIST_MODE_PRBS;
        sal_memcpy(info.prbs_seeds, &dnx_data_dram.hbm.bist_get(unit)->prbs_seeds[0], sizeof(info.prbs_seeds));

        SHR_IF_ERR_EXIT(dnx_hbmc_ecc_err_counters_clear(unit));
        SHR_BIT_ITER(dram_bitmap, dram_bitmap_size, hbmc_index)
        {

            for (hbmc_channel = 0; hbmc_channel < dnx_data_dram.general_info.nof_channels_get(unit); hbmc_channel++)
            {

                SHR_IF_ERR_EXIT(dnx_hbmc_bist_run(unit, 0, hbmc_index, hbmc_channel, FALSE, &info,
                                                  &is_polling_required[hbmc_index][hbmc_channel]));

            }
        }

        SHR_BIT_ITER(dram_bitmap, dram_bitmap_size, hbmc_index)
        {

            for (hbmc_channel = 0; hbmc_channel < dnx_data_dram.general_info.nof_channels_get(unit); hbmc_channel++)
            {
                if (is_polling_required[hbmc_index][hbmc_channel])
                {
                    hbmc_shmoo_bist_status_cnt_t sts_counters;
                    sal_memset(&sts_counters, 0, sizeof(hbmc_shmoo_bist_status_cnt_t));
                    SHR_IF_ERR_EXIT(dnx_hbmc_bist_run_done_poll(unit, hbmc_index, hbmc_channel));

                    SHR_IF_ERR_EXIT(dnx_hbmc_bist_err_cnt_cb(unit, 0, hbmc_index, hbmc_channel, &bist_err_cnt));

                    SHR_IF_ERR_EXIT(dnx_hbmc_bist_status_get(unit, hbmc_index, hbmc_channel,
                                                             sts_counters.write_cmd_counter,
                                                             sts_counters.read_cmd_counter,
                                                             sts_counters.read_data_counter));

                    SHR_IF_ERR_EXIT(dnx_hbmc_ecc_errors_get(unit, hbmc_index, hbmc_channel, &ecc_err_cnt));

                    if (bist_err_cnt.bist_data_err_cnt > 0)
                    {
                        fail_indication = TRUE;
                    }

                    dnx_hbmc_bist_result_report(unit, hbmc_index, hbmc_channel, &sts_counters, &bist_err_cnt,
                                                &ecc_err_cnt);
                }
            }
        }

        if (fail_indication == TRUE)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "HBMC BIST FAILED. see previous error messages\n");
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_single_channel_coherence_enforcement_enable(
    int unit,
    int hbm_index,
    int channel)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_HCC_HBM_COHERENCY_ENFORCER_CONTROL, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_HBMC_INDEX, hbm_index);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CHANNEL_INDEX, channel);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_HBM_COHERENCY_ENFORCER_ENABLE, INST_SINGLE, 1);

    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_coherence_enforcement_enable(
    int unit)
{
    const uint32 dram_bitmap[1] = { dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap };
    const int nof_hbms = dnx_data_dram.general_info.max_nof_drams_get(unit);
    const int nof_channels_in_hbm = dnx_data_dram.general_info.nof_channels_get(unit);

    int channel;
    int hbm_index;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_BIT_ITER(dram_bitmap, nof_hbms, hbm_index)
    {
        for (channel = 0; channel < nof_channels_in_hbm; channel++)
        {
            SHR_IF_ERR_EXIT(dnx_hbmc_single_channel_coherence_enforcement_enable(unit, hbm_index, channel));
        }
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_hbm_init_all(
    int unit)
{
    int nof_hbms;
    int hbm_index;
    uint32 dram_bitmap[1];
    SHR_FUNC_INIT_VARS(unit);

    nof_hbms = dnx_data_dram.general_info.max_nof_drams_get(unit);

    dram_bitmap[0] = dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap;
    SHR_BIT_ITER(dram_bitmap, nof_hbms, hbm_index)
    {
        SHR_IF_ERR_EXIT(dnx_hbmc_hbm_init(unit, hbm_index));

        SHR_IF_ERR_EXIT(dnx_hbmc_cattrip_indication_mask_set(unit, hbm_index, 0));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_hbc_blocks_enable_set(
    int unit)
{
    uint32 dram_bitmap[1];
    int nof_hbms;
    int nof_channels_in_hbm;

    SHR_FUNC_INIT_VARS(unit);

    dram_bitmap[0] = dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap;
    nof_hbms = dnx_data_dram.general_info.max_nof_drams_get(unit);

    nof_channels_in_hbm = dnx_data_dram.general_info.nof_channels_get(unit);

    for (int hbm_index = 0; hbm_index < nof_hbms; ++hbm_index)
    {
        int is_enabled;
        if (SHR_BITGET(dram_bitmap, hbm_index))
        {

            is_enabled = 1;
        }
        else
        {

            is_enabled = 0;
        }
        for (int channel = 0; channel < nof_channels_in_hbm; ++channel)
        {
            int block;
            int *hbc_block_p;
            uint8 *block_valid_p;

            SHR_IF_ERR_EXIT(soc_info_int_address_get(unit, HBC_BLOCK_INT, &hbc_block_p));
            SHR_IF_ERR_EXIT(soc_info_uint8_address_get(unit, BLOCK_VALID, &block_valid_p));
            block = hbc_block_p[dnx_hbmc_get_sequential_channel(unit, hbm_index, channel)];
            block_valid_p[block] = is_enabled;
        }
    }
    if (dram_bitmap[0] == 0)
    {
        int *brdc_hbc_block_p;
        uint8 *block_valid_p;

        SHR_IF_ERR_EXIT(soc_info_int_address_get(unit, BRDC_HBC_BLOCK_INT, &brdc_hbc_block_p));
        SHR_IF_ERR_EXIT(soc_info_uint8_address_get(unit, BLOCK_VALID, &block_valid_p));
        block_valid_p[*brdc_hbc_block_p] = 0;
    }
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_vendor_info_to_sw_state_update(
    int unit)
{
    int nof_hbms;
    int hbm_index;
    uint32 dram_bitmap[1];
    SHR_FUNC_INIT_VARS(unit);

    if (!dnx_data_dram.hbm.feature_get(unit, dnx_data_dram_hbm_cpu2tap_access))
    {

        SHR_EXIT();
    }

    if (dnx_data_dram.hbm.feature_get(unit, dnx_data_dram_hbm_vendor_info_disable))
    {

        SHR_EXIT();
    }

    nof_hbms = dnx_data_dram.general_info.max_nof_drams_get(unit);

    dram_bitmap[0] = dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap;
    SHR_BIT_ITER(dram_bitmap, nof_hbms, hbm_index)
    {
        dnx_dram_vendor_info_t vendor_info;
        SHR_IF_ERR_EXIT(dnx_dram_vendor_info_get(unit, hbm_index, &vendor_info));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_default_model_part_to_sw_state_compare(
    int unit,
    int *model_part_is_matching)
{
    int nof_hbms;
    uint32 dram_bitmap[1];
    int hbm_index;
    uint32 model_part_number = 0;
    SHR_FUNC_INIT_VARS(unit);

    nof_hbms = dnx_data_dram.general_info.max_nof_drams_get(unit);
    dram_bitmap[0] = dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap;
    SHR_BIT_ITER(dram_bitmap, nof_hbms, hbm_index)
    {

        SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.model_part_number.get(unit, hbm_index, &model_part_number));
        break;
    }

    *model_part_is_matching = (model_part_number == dnx_data_dram.hbm.default_model_part_num_get(unit));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_sw_state_init(
    int unit)
{
    int nof_hbms;
    uint32 dram_bitmap[1];
    int hbm_index;
    uint8 is_dram_db_inited;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_dram_db.is_init(unit, &is_dram_db_inited));
    if (is_dram_db_inited)
    {
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(dnx_dram_db.init(unit));

    SHR_IF_ERR_EXIT(dnx_dram_db.override_bist_configurations_during_tuning.set(unit, 1));
    SHR_IF_ERR_EXIT(dnx_dram_db.channel_soft_init_after_bist.set(unit, 0));

    nof_hbms = dnx_data_dram.general_info.max_nof_drams_get(unit);
    dram_bitmap[0] = dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap;
    SHR_BIT_ITER(dram_bitmap, nof_hbms, hbm_index)
    {
        SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.
                        model_part_number.set(unit, hbm_index, dnx_data_dram.hbm.default_model_part_num_get(unit)));
    }

    SHR_IF_ERR_EXIT(dnx_dram_db.power_down_callback.power_on.set(unit, 0));

    if (dnx_data_dram.hbm.feature_get(unit, dnx_data_dram_hbm_apd_phy))
    {

        SHR_IF_ERR_EXIT(dnx_dram_db.sync_manager.firmware_mutex.create(unit));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_init(
    int unit)
{
    int model_part_is_matching = 0;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_hbmc_hbc_blocks_enable_set(unit));

    if (dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap == 0)
    {
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(dnx_dram_db.power_down_callback.power_on.set(unit, 1));

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): hbmc_phy init\n"), FUNCTION_NAME()));
    SHR_IF_ERR_EXIT(dnx_hbmc_phy_init(unit));

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): configure hbmc side\n"), FUNCTION_NAME()));
    SHR_IF_ERR_EXIT(dnx_hbmc_configure(unit));

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): hbm init (CPU + MRs)\n"), FUNCTION_NAME()));
    SHR_IF_ERR_EXIT(dnx_hbmc_hbm_init_all(unit));

    SHR_IF_ERR_EXIT(dnx_hbmc_vendor_info_to_sw_state_update(unit));

    SHR_IF_ERR_EXIT(dnx_hbmc_default_model_part_to_sw_state_compare(unit, &model_part_is_matching));
    if (!model_part_is_matching)
    {

        SHR_IF_ERR_EXIT(dnx_hbmc_phy_init(unit));
        SHR_IF_ERR_EXIT(dnx_hbmc_configure(unit));
        SHR_IF_ERR_EXIT(dnx_hbmc_hbm_init_all(unit));
    }

    if (!SAL_BOOT_PLISIM)
    {
        LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): run shmoo\n"), FUNCTION_NAME()));
        SHR_IF_ERR_EXIT(dnx_hbmc_run_phy_tune(unit, DNX_HBMC_ITER_ALL, DNX_HBMC_ITER_ALL, SHMOO_HBM16_SHMOO_RSVP,
                                              SHMOO_HBM16_CTL_FLAGS_DWORDS_ALL,
                                              dnx_data_dram.general_info.tune_mode_on_init_get(unit)));
    }

    SHR_IF_ERR_EXIT(dnx_hbmc_bist_handle(unit));

    SHR_IF_ERR_EXIT(dnx_hbmc_tdu_configure(unit));

    SHR_IF_ERR_EXIT(dnx_dram_db.is_initialized.set(unit, 1));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_init_with_apd_phy(
    int unit)
{
    int max_nof_drams = dnx_data_dram.general_info.max_nof_drams_get(unit);
    int global_hbm_index;
    int is_valid;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_hbmc_hbc_blocks_enable_set(unit));

    if (dnx_data_dram.general_info.dram_blocks_in_power_down_get(unit))
    {
        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_power_down_enable_set(unit, 1));
    }
    else
    {

        if (dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap == 0)
        {
            SHR_EXIT();
        }

        SHR_IF_ERR_EXIT(dnx_dram_db.power_down_callback.power_on.set(unit, 1));

        for (global_hbm_index = 0; global_hbm_index < max_nof_drams; ++global_hbm_index)
        {
            SHR_IF_ERR_EXIT(dnx_dram_index_is_valid(unit, global_hbm_index, &is_valid));

            if (is_valid)
            {

                LOG_VERBOSE(BSL_LOG_MODULE,
                            (BSL_META_U(unit, "%s(hbmc%d): Unmask CATTRIP indication\n"), FUNCTION_NAME(),
                             global_hbm_index));
                SHR_IF_ERR_EXIT(dnx_hbmc_cattrip_indication_mask_set(unit, global_hbm_index, FALSE));
            }

            LOG_VERBOSE(BSL_LOG_MODULE,
                        (BSL_META_U(unit, "%s(hbmc%d): Take HRC block out of soft init\n"), FUNCTION_NAME(),
                         global_hbm_index));
            SHR_IF_ERR_EXIT(dnx_hbmc_hrc_soft_init_set(unit, global_hbm_index, FALSE));

            if (is_valid)
            {

                LOG_VERBOSE(BSL_LOG_MODULE,
                            (BSL_META_U(unit, "%s(hbmc%d): Configure channels\n"), FUNCTION_NAME(), global_hbm_index));
                SHR_IF_ERR_EXIT(dnx_hcc_configure(unit, global_hbm_index));
            }
        }

        LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): Configure TDU\n"), FUNCTION_NAME()));
        SHR_IF_ERR_EXIT(dnx_hbmc_tdu_configure(unit));

        LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): Configure HRC\n"), FUNCTION_NAME()));
        SHR_IF_ERR_EXIT(dnx_hbmc_hrc_configure(unit));

        SHR_IF_ERR_EXIT(dnx_hbmc_bist_handle(unit));

        if (dnx_data_dram.hbm.feature_get(unit, dnx_data_dram_hbm_is_coherency_enforcer_supported))
        {
            LOG_VERBOSE(BSL_LOG_MODULE,
                        (BSL_META_U(unit, "%s(): Enable HBM coherence enforcer BIST\n"), FUNCTION_NAME()));
            SHR_IF_ERR_EXIT(dnx_hbmc_coherence_enforcement_enable(unit));
        }

        SHR_IF_ERR_EXIT(dnx_dram_db.is_initialized.set(unit, TRUE));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbm_phy_bist(
    int unit)
{
    int max_nof_drams = dnx_data_dram.general_info.max_nof_drams_get(unit);
    int global_hbm_index;
    int is_valid;
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap == 0)
    {
        SHR_EXIT();
    }

    if (!dnx_data_dram.hbm.feature_get(unit, dnx_data_dram_hbm_apd_phy))
    {
        SHR_EXIT();
    }

    for (global_hbm_index = 0; global_hbm_index < max_nof_drams; ++global_hbm_index)
    {
        SHR_IF_ERR_EXIT(dnx_dram_index_is_valid(unit, global_hbm_index, &is_valid));

        if (is_valid)
        {

            LOG_VERBOSE(BSL_LOG_MODULE,
                        (BSL_META_U(unit, "%s(hbmc%d): Launch firmware operation RUN_MMT\n"), FUNCTION_NAME(),
                         global_hbm_index));
            SHR_IF_ERR_EXIT(dnx_hbmc_firmware_launch_operation
                            (unit, global_hbm_index, DNX_HBMC_FIRMWARE_ALL_CHANNELS,
                             DNX_HBMC_FIRMWARE_OPERATION_RUN_MMT));

            LOG_VERBOSE(BSL_LOG_MODULE,
                        (BSL_META_U(unit, "%s(hbmc%d): Launch firmware operation RESET_PHY_AND_HBM\n"), FUNCTION_NAME(),
                         global_hbm_index));
            SHR_IF_ERR_EXIT(dnx_hbmc_firmware_launch_operation
                            (unit, global_hbm_index, DNX_HBMC_FIRMWARE_ALL_CHANNELS,
                             DNX_HBMC_FIRMWARE_OPERATION_RESET_PHY_AND_HBM));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_temp_monitor_is_active(
    int unit,
    int *is_active)
{
    shr_thread_manager_handler_t temp_monitor_handler;
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(is_active, _SHR_E_PARAM, "is_active");

    *is_active = FALSE;

    if ((dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap != 0) &&
        dnx_data_dram.hbm.dram_temp_monitor_enable_get(unit))
    {

        SHR_IF_ERR_EXIT(dnx_dram_db.temperature_monitoring_thread_handler.get(unit, &temp_monitor_handler));

        if (temp_monitor_handler != NULL)
        {

            SHR_IF_ERR_EXIT(shr_thread_manager_is_active_get(temp_monitor_handler, is_active));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_temp_monitor_resume(
    int unit)
{
    shr_thread_manager_handler_t temp_monitor_handler;
    int is_active;
    SHR_FUNC_INIT_VARS(unit);

    if (TRUE == dnx_data_dram.hbm.dram_temp_monitor_enable_get(unit))
    {

        SHR_IF_ERR_EXIT(dnx_dram_db.temperature_monitoring_thread_handler.get(unit, &temp_monitor_handler));

        SHR_IF_ERR_EXIT(dnx_hbmc_temp_monitor_is_active(unit, &is_active));

        if (!is_active)
        {

            SHR_IF_ERR_EXIT(shr_thread_manager_start(temp_monitor_handler));
        }
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_temp_monitor_pause(
    int unit)
{
    shr_thread_manager_handler_t temp_monitor_handler;
    SHR_FUNC_INIT_VARS(unit);

    if (TRUE == dnx_data_dram.hbm.dram_temp_monitor_enable_get(unit))
    {

        SHR_IF_ERR_EXIT(dnx_dram_db.temperature_monitoring_thread_handler.get(unit, &temp_monitor_handler));

        SHR_IF_ERR_EXIT(shr_thread_manager_stop(temp_monitor_handler, 0));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_temp_monitor_thread_create(
    int unit)
{
    shr_thread_manager_config_t temp_monitor_config_info;
    shr_thread_manager_handler_t temp_monitor_handler;
    SHR_FUNC_INIT_VARS(unit);

    shr_thread_manager_config_t_init(&temp_monitor_config_info);
    temp_monitor_config_info.name = HBM_TEMPERATURE_MONITOR_THREAD_NAME;
    temp_monitor_config_info.bsl_module = BSL_LOG_MODULE;
    temp_monitor_config_info.type = SHR_THREAD_MANAGER_TYPE_EVENT;
    temp_monitor_config_info.interval = dnx_data_dram.hbm.usec_between_temp_samples_get(unit);
    temp_monitor_config_info.callback = dnx_hbmc_temp_monitor;
    temp_monitor_config_info.start_operation = (dnx_data_dram.hbm.start_disabled_get(unit) ? 0 : 1);
    SHR_IF_ERR_EXIT(shr_thread_manager_create(unit, &temp_monitor_config_info, &temp_monitor_handler));

    SHR_IF_ERR_EXIT(dnx_dram_db.temperature_monitoring_thread_handler.set(unit, temp_monitor_handler));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_temp_log_thread_create(
    int unit)
{
    shr_thread_manager_config_t temp_monitor_config_info;
    shr_thread_manager_handler_t temp_monitor_handler;
    SHR_FUNC_INIT_VARS(unit);

    shr_thread_manager_config_t_init(&temp_monitor_config_info);
    temp_monitor_config_info.name = HBM_TEMPERATURE_LOG_THREAD_NAME;
    temp_monitor_config_info.bsl_module = BSL_LOG_MODULE;
    temp_monitor_config_info.type = SHR_THREAD_MANAGER_TYPE_EVENT;
    temp_monitor_config_info.interval = dnx_data_dram.hbm.usec_between_temp_samples_get(unit);
    temp_monitor_config_info.callback = dnx_hbmc_temp_log;
    SHR_IF_ERR_EXIT(shr_thread_manager_create(unit, &temp_monitor_config_info, &temp_monitor_handler));

    SHR_IF_ERR_EXIT(dnx_dram_db.temperature_monitoring_thread_handler.set(unit, temp_monitor_handler));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_temp_monitor_thread_destroy(
    int unit)
{

    shr_thread_manager_handler_t temp_monitor_handler;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_dram_db.temperature_monitoring_thread_handler.get(unit, &temp_monitor_handler));

    if (temp_monitor_handler != NULL)
    {
        SHR_IF_ERR_EXIT(shr_thread_manager_destroy(&temp_monitor_handler));
    }

    SHR_IF_ERR_EXIT(dnx_dram_db.temperature_monitoring_thread_handler.set(unit, NULL));

exit:
    SHR_FUNC_EXIT;
}

static int
dnx_hbmc_temp_monitor_check(
    int unit)
{

    return
        ((dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap != 0) &&
         dnx_data_dram.hbm.feature_get(unit, dnx_data_dram_hbm_is_supported) &&
         dnx_data_dram.general_info.feature_get(unit, dnx_data_dram_general_info_is_temperature_reading_supported));

}

shr_error_e
dnx_hbmc_temp_monitor_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    if (!dnx_hbmc_temp_monitor_check(unit))
    {
        SHR_EXIT();
    }

    if (TRUE == dnx_data_dram.hbm.dram_temp_monitor_enable_get(unit))
    {

        SHR_IF_ERR_EXIT(dnx_hbmc_temp_monitor_thread_create(unit));
    }
    else
    {

        SHR_IF_ERR_EXIT(dnx_hbmc_temp_log_thread_create(unit));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_temp_monitor_deinit(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap == 0)
    {
        SHR_EXIT();
    }

    if (!dnx_data_dram.hbm.feature_get(unit, dnx_data_dram_hbm_is_supported))
    {
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(dnx_hbmc_temp_monitor_thread_destroy(unit));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_deinit(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_mode_register_get(
    int unit,
    int hbm_index,
    int channel,
    int mr_index,
    uint32 *value)
{

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_mr_get(unit, hbm_index, channel, mr_index, value));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_mode_register_set(
    int unit,
    int hbm_index,
    int channel,
    int mr_index,
    uint32 value)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_mr_set(unit, hbm_index, channel, mr_index, value));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_bist_configuration_set_verify(
    int unit,
    int hbm_index,
    int channel,
    const hbmc_shmoo_bist_info_t * info)
{
    COMPILER_UINT64 nof_bist_actions_for_arethmetics;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(info, _SHR_E_PARAM, "info");

    COMPILER_64_SET(nof_bist_actions_for_arethmetics, info->bist_num_actions[1], info->bist_num_actions[0]);
    if (info->bist_timer_us != 0 && !COMPILER_64_IS_ZERO(nof_bist_actions_for_arethmetics))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "both number of actions and timer are set together, can use either not both\n");
    }

    if (info->column_end_index >= dnx_data_dram.general_info.dram_info_get(unit)->nof_columns)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "number of columns is not compatible to init configurations\n");
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_bist_configuration_get(
    int unit,
    int hbm_index,
    int channel,
    hbmc_shmoo_bist_info_t * info)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(info, _SHR_E_PARAM, "info");

    sal_memset(info, 0, sizeof(*info));

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_bist_configuration_get(unit, hbm_index, channel, info));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_bist_configuration_set(
    int unit,
    int hbm_index,
    int channel,
    const hbmc_shmoo_bist_info_t * info)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_hbmc_bist_configuration_set_verify(unit, hbm_index, channel, info));

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_bist_configuration_set(unit, hbm_index, channel, info));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_bist_start(
    int unit,
    int hbm_index,
    int channel)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_bist_run(unit, hbm_index, channel, 1));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_bist_stop(
    int unit,
    int hbm_index,
    int channel)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_bist_run(unit, hbm_index, channel, 0));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_bist_run_done_poll(
    int unit,
    int hbm_index,
    int channel)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_bist_run_done_poll(unit, hbm_index, channel));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_channel_soft_init(
    int unit,
    int hbm_ndx,
    int channel)
{
    uint32 nof_mrs = dnx_data_dram.general_info.nof_mrs_get(unit);
    uint32 *mr_vals_p = NULL;

    SHR_FUNC_INIT_VARS(unit);
    SHR_ALLOC_SET_ZERO(mr_vals_p, sizeof(*mr_vals_p) * nof_mrs, "mr_vals_p", "%s%s%s", EMPTY, EMPTY, EMPTY);

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_update_hbm_on_mode_register_change(unit, hbm_ndx, channel, 0));

    for (int mr_index = 0; mr_index < nof_mrs; ++mr_index)
    {
        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_mr_get(unit, hbm_ndx, channel, mr_index, &mr_vals_p[mr_index]));
    }

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_channel_soft_init_set(unit, hbm_ndx, channel, 1));

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_channel_soft_init_set(unit, hbm_ndx, channel, 0));

    for (int mr_index = 0; mr_index < nof_mrs; ++mr_index)
    {
        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_mr_set(unit, hbm_ndx, channel, mr_index, mr_vals_p[mr_index]));
    }

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_update_hbm_on_mode_register_change(unit, hbm_ndx, channel, 1));

exit:
    SHR_FREE(mr_vals_p);
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_channels_soft_init_set(
    int unit,
    int hbm_index,
    int in_soft_init)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_channels_soft_init_set(unit, hbm_index, in_soft_init));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_channels_soft_reset_set(
    int unit,
    int hbm_index,
    int in_soft_reset)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_channels_soft_reset_set(unit, hbm_index, in_soft_reset));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_hbmc_soft_init_set(
    int unit,
    int hbm_index,
    int in_soft_init)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hbmc_soft_init_set(unit, hbm_index, in_soft_init));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_hbmc_soft_reset_set(
    int unit,
    int hbm_index,
    int in_soft_reset)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hbmc_soft_reset_set(unit, hbm_index, in_soft_reset));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_hrc_soft_init_set(
    int unit,
    int hbm_index,
    int in_soft_init)
{
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_dram.hbm.feature_get(unit, dnx_data_dram_hbm_is_hrc_supported))
    {

        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hrc_soft_init_set(unit, hbm_index, in_soft_init));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_hrc_soft_reset_set(
    int unit,
    int hbm_index,
    int in_soft_reset)
{
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_dram.hbm.feature_get(unit, dnx_data_dram_hbm_is_hrc_supported))
    {

        SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hrc_soft_reset_set(unit, hbm_index, in_soft_reset));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_tdu_soft_init_set(
    int unit,
    int hbm_index,
    int in_soft_init)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_tdu_soft_init_set(unit, hbm_index, in_soft_init));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_tdu_soft_reset_set(
    int unit,
    int hbm_index,
    int in_soft_reset)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_tdu_soft_reset_set(unit, hbm_index, in_soft_reset));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_soft_init_mrs_save(
    int unit,
    dnx_hbmc_mrs_values_t * mr_values_p)
{
    uint32 dram_bitmap[1];
    uint8 is_dram_db_inited = 0;
    SHR_FUNC_INIT_VARS(unit);

    if (!dnx_data_dram.hbm.feature_get(unit, dnx_data_dram_hbm_is_supported))
    {
        SHR_EXIT();
    }

    if (dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap == 0)
    {
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(dnx_dram_db.is_init(unit, &is_dram_db_inited));
    if (!is_dram_db_inited)
    {
        SHR_EXIT();
    }

    dram_bitmap[0] = dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap;

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_mr_get_all(unit, dram_bitmap, mr_values_p));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_soft_init_mrs_restore(
    int unit,
    dnx_hbmc_mrs_values_t * mr_values_p)
{
    uint32 dram_bitmap[1];
    uint8 is_dram_db_inited = 0;
    SHR_FUNC_INIT_VARS(unit);

    if (!dnx_data_dram.hbm.feature_get(unit, dnx_data_dram_hbm_is_supported))
    {
        SHR_EXIT();
    }

    if (dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap == 0)
    {
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(dnx_dram_db.is_init(unit, &is_dram_db_inited));
    if (!is_dram_db_inited)
    {
        SHR_EXIT();
    }

    dram_bitmap[0] = dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap;

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_update_hbm_on_mode_register_change
                    (unit, DNX_HBMC_ITER_ALL, DNX_HBMC_ITER_ALL, 0));

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_mr_set_all(unit, dram_bitmap, mr_values_p));

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_update_hbm_on_mode_register_change
                    (unit, DNX_HBMC_ITER_ALL, DNX_HBMC_ITER_ALL, 1));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_ind_access_physical_address_read(
    int unit,
    uint32 hbm_index,
    uint32 channel,
    uint32 bank,
    uint32 row,
    uint32 column,
    uint32 *data)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_dram_cpu_access_get(unit, hbm_index, channel, bank, row, column, data));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_ind_access_physical_address_write(
    int unit,
    uint32 hbm_index,
    uint32 channel,
    uint32 bank,
    uint32 row,
    uint32 column,
    uint32 *pattern)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_dram_cpu_access_set(unit, hbm_index, channel, bank, row, column, pattern));

exit:
    SHR_FUNC_EXIT;
}

static uint32
dnx_hbmc_xor_bits(
    uint32 val)
{
    val ^= val >> 16;
    val ^= val >> 8;
    val ^= val >> 4;
    val ^= val >> 2;
    val ^= val >> 1;
    return val & 1;
}

static shr_error_e
dnx_hbmc_ind_access_logical_to_physical_address_translate(
    int unit,
    int core,
    int buffer,
    int index,
    uint32 *address)
{
    const uint32 *atm;
    uint32 data_source_id;
    uint32 logical_address;
    uint32 jumbled_physical_address = 0;
    uint32 base_physical_address;
    uint32 base_physical_address_unchanged_part;
    uint32 base_physical_address_shifted_column_part;
    uint32 bits_in_physical_address = dnx_data_dram.address_translation.matrix_column_size_get(unit);
    uint32 index_in_offset_bits = HBMC_TRANSACTION_BITS_IN_LOGICAL_ADDRESS;
    uint32 offsets_for_buffer_bits = HBMC_LOGICAL_ADDRESSES_BITS_PER_BUFFER;
    uint32 data_source_id_offset = HBMC_LOGICAL_ADDRESSES_DATA_SOURCE_ID_OFFSET;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_hbmc_tdu_atm_get(unit, &atm));

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_data_source_id_get(unit, core, &data_source_id));
    logical_address =
        (buffer << offsets_for_buffer_bits) | (index >> index_in_offset_bits) | (data_source_id <<
                                                                                 data_source_id_offset);
    LOG_VERBOSE(BSL_LOG_MODULE,
                (BSL_META_U(unit, "%s(): logical buffer=%d, index=%d, logical_address=0x%x\n"), FUNCTION_NAME(), buffer,
                 index, logical_address));

    for (int bit = 0; bit < bits_in_physical_address; ++bit)
    {
        jumbled_physical_address |= dnx_hbmc_xor_bits(logical_address & atm[bit]) << bit;
        LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit,
                                                "%s(): logical_address=0x%x, atm[%d]=0x%x, jumbled_physical_address_bit_%d=%d\n"),
                                     FUNCTION_NAME(), logical_address, bit, atm[bit], bit,
                                     jumbled_physical_address >> bit));
    }

    base_physical_address_unchanged_part = (jumbled_physical_address &
                                            (PHY_ADDRESS_MODULE_MASK | PHY_ADDRESS_CHANNEL_MASK | PHY_ADDRESS_BANK_MASK
                                             | PHY_ADDRESS_ROW_MASK));
    base_physical_address_shifted_column_part =
        (((jumbled_physical_address & PHY_ADDRESS_JUMBLED_RELEVANT_COLUMN_MASK) >>
          PHY_ADDRESS_JUMBLED_RELEVANT_COLUMN_OFFSET) << PHY_ADDRESS_CORRECT_RELEVANT_COLUMN_OFFSET);
    base_physical_address = base_physical_address_unchanged_part | base_physical_address_shifted_column_part;
    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit,
                                            "%s(): jumbled_physical_address=0x%x, base_physical_address=0x%x\n"),
                                 FUNCTION_NAME(), jumbled_physical_address, base_physical_address));

    *address = base_physical_address | ((index & GET_BIT_MASK(index_in_offset_bits, 0)) <<
                                        PHY_ADDRESS_SEQUENTIAL_COLUMN_OFFSET);

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "%s(): logical buffer=%d, index=%d, physical address=0x%x\n"),
                                 FUNCTION_NAME(), buffer, index, *address));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_ind_access_logical_buffer_read(
    int unit,
    int core,
    int buffer,
    int index,
    uint32 *data)
{
    int stop_index;
    int start_index;
    int nof_indexes;
    int transaction_size_in_words;

    SHR_FUNC_INIT_VARS(unit);
    if (index == -1)
    {

        nof_indexes = dnx_data_dram.general_info.buffer_size_get(unit) /
            dnx_data_dram.address_translation.physical_address_transaction_size_get(unit);
        start_index = 0;
        stop_index = nof_indexes - 1;
    }
    else
    {
        start_index = index;
        stop_index = index;
    }

    transaction_size_in_words =
        dnx_data_dram.address_translation.physical_address_transaction_size_get(unit) / BYTES_IN_WORD;
    for (int current_index = start_index; current_index <= stop_index; ++current_index)
    {
        uint32 address;

        SHR_IF_ERR_EXIT(dnx_hbmc_ind_access_logical_to_physical_address_translate
                        (unit, core, buffer, current_index, &address));

        SHR_IF_ERR_EXIT(dnx_hbmc_ind_access_physical_address_read(unit, PHY_ADDRESS_GET_MODULE(address, core),
                                                                  PHY_ADDRESS_GET_CHANNEL(address),
                                                                  PHY_ADDRESS_GET_BANK(address),
                                                                  PHY_ADDRESS_GET_ROW(address),
                                                                  PHY_ADDRESS_GET_COLUMN(address),
                                                                  data + (current_index -
                                                                          start_index) * transaction_size_in_words));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_ind_access_logical_buffer_write(
    int unit,
    int core,
    int buffer,
    int index,
    uint32 *pattern)
{
    int stop_index;
    int start_index;
    int nof_indexes;

    SHR_FUNC_INIT_VARS(unit);
    if (index == -1)
    {

        nof_indexes = dnx_data_dram.general_info.buffer_size_get(unit) /
            dnx_data_dram.address_translation.physical_address_transaction_size_get(unit);
        start_index = 0;
        stop_index = nof_indexes - 1;
    }
    else
    {
        start_index = index;
        stop_index = index;
    }

    for (int current_index = start_index; current_index <= stop_index; ++current_index)
    {
        uint32 address;

        SHR_IF_ERR_EXIT(dnx_hbmc_ind_access_logical_to_physical_address_translate
                        (unit, core, buffer, current_index, &address));

        SHR_IF_ERR_EXIT(dnx_hbmc_ind_access_physical_address_write(unit, PHY_ADDRESS_GET_MODULE(address, core),
                                                                   PHY_ADDRESS_GET_CHANNEL(address),
                                                                   PHY_ADDRESS_GET_BANK(address),
                                                                   PHY_ADDRESS_GET_ROW(address),
                                                                   PHY_ADDRESS_GET_COLUMN(address), pattern));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_redirect_traffic_to_ocb(
    int unit,
    uint32 enable,
    uint8 *hbm_is_empty)
{
    static const uint8 emptying_delay_seconds = 10;

    SHR_FUNC_INIT_VARS(unit);
    if (enable)
    {

        SHR_IF_ERR_EXIT(dnx_hbmc_traffic_to_hbm_stop(unit));

        if (hbm_is_empty != NULL)
        {
            sal_sleep(emptying_delay_seconds);
            SHR_IF_ERR_EXIT(dnx_hbmc_traffic_is_empty_get(unit, hbm_is_empty));
        }
    }
    else
    {

        SHR_IF_ERR_EXIT(dnx_hbmc_traffic_to_hbm_restore(unit));
        if (hbm_is_empty != NULL)
        {
            *hbm_is_empty = TRUE;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

#if UNUSED_CODE_FOR_DEBUG

shr_error_e
dnx_hbmc_is_traffic_allowed_into_dram(
    int unit,
    uint8 *allow_traffic_to_dram)
{
    int dram_in_use;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_ingress_congestion_db.sync_manager.dram_in_use.get(unit, &dram_in_use));

    *allow_traffic_to_dram = ! !dram_in_use;

exit:
    SHR_FUNC_EXIT;
}

#endif

shr_error_e
dnx_hbmc_bist_status_get(
    int unit,
    int hbm_index,
    int channel,
    uint32 *read_cmd_counter,
    uint32 *write_cmd_counter,
    uint32 *read_data_counter)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_bist_status_get
                    (unit, hbm_index, channel, read_cmd_counter, write_cmd_counter, read_data_counter));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_parity_errors_get(
    int unit,
    int hbm_index,
    int channel,
    hbmc_parity_err_cnt_t * error_counters)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_parity_errors_get(unit, hbm_index, channel, error_counters));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_ecc_enable_get(
    int unit,
    int hbm_index,
    int channel,
    uint32 *is_enabled)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_ecc_enable_get(unit, hbm_index, channel, is_enabled));

exit:
    SHR_FUNC_EXIT;

}

shr_error_e
dnx_hbmc_ecc_errors_get(
    int unit,
    int hbm_index,
    int channel,
    hbmc_ecc_err_cnt_t * error_counters)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_ecc_errors_get(unit, hbm_index, channel, error_counters));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_power_down_cb_register_verify(
    int unit,
    uint32 flags,
    bcm_switch_dram_power_down_callback_t callback,
    void *userdata)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(callback, _SHR_E_PARAM, "callback");
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_power_down_cb_register(
    int unit,
    uint32 flags,
    bcm_switch_dram_power_down_callback_t callback,
    void *userdata)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnxc_ha_tmp_allow_access_enable(unit, UTILEX_SEQ_ALLOW_SW_STATE));

    SHR_INVOKE_VERIFY_DNXC(dnx_hbmc_power_down_cb_register_verify(unit, flags, callback, userdata));
    SHR_IF_ERR_EXIT(dnx_dram_db.power_down_callback.callback.set(unit, callback));
    SHR_IF_ERR_EXIT(dnx_dram_db.power_down_callback.userdata.set(unit, (dnx_power_down_callback_userdata_t) userdata));

    SHR_IF_ERR_EXIT(dnxc_ha_tmp_allow_access_disable(unit, UTILEX_SEQ_ALLOW_SW_STATE));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_hbmc_power_down_cb_unregister_verify(
    int unit,
    bcm_switch_dram_power_down_callback_t callback,
    void *userdata)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(callback, _SHR_E_PARAM, "callback");
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_power_down_cb_unregister(
    int unit,
    bcm_switch_dram_power_down_callback_t callback,
    void *userdata)
{
    uint8 is_init;
    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_hbmc_power_down_cb_unregister_verify(unit, callback, userdata));
    SHR_IF_ERR_EXIT(dnx_dram_db.is_init(unit, &is_init));
    if (is_init == FALSE)
    {
        SHR_EXIT();
    }
    SHR_IF_ERR_EXIT(dnx_dram_db.power_down_callback.callback.set(unit, NULL));
    SHR_IF_ERR_EXIT(dnx_dram_db.power_down_callback.userdata.set(unit, NULL));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_power_down(
    int unit)
{
    uint32 dram_bitmap[1];
    int nof_hbms;
    int hbm_index;
    bcm_switch_dram_power_down_callback_t power_down_callback;
    dnx_power_down_callback_userdata_t userdata;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_dram_db.power_down_callback.power_on.set(unit, 0));

    dram_bitmap[0] = dnx_data_dram.general_info.dram_info_get(unit)->dram_bitmap;
    nof_hbms = dnx_data_dram.general_info.max_nof_drams_get(unit);
    if (!dnx_data_dram.hbm.feature_get(unit, dnx_data_dram_hbm_apd_phy))
    {
        SHR_BIT_ITER(dram_bitmap, nof_hbms, hbm_index)
        {

            SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_reset_control_set(unit, hbm_index, 0));
        }
    }

    SHR_IF_ERR_EXIT(dnx_dram_db.power_down_callback.callback.get(unit, &power_down_callback));
    if (power_down_callback == NULL)
    {
        SHR_IF_ERR_EXIT(soc_dnxc_hard_reset(unit));
        SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Power down callback function does not exist. Device hard reset was made\n");
    }

    SHR_BIT_ITER(dram_bitmap, nof_hbms, hbm_index)
    {

        SHR_IF_ERR_EXIT(dnx_hbmc_cattrip_indication_mask_set(unit, hbm_index, 1));
    }

    SHR_IF_ERR_EXIT(dnx_dram_db.power_down_callback.userdata.get(unit, &userdata));
    power_down_callback(unit, 0, userdata);

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_reinit(
    int unit,
    uint32 flags)
{
    int is_dram_initialized;
    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_dram.hbm.feature_get(unit, dnx_data_dram_hbm_apd_phy))
    {

        SHR_IF_ERR_EXIT(dnx_hbmc_apd_phy_pll_init(unit));

        SHR_IF_ERR_EXIT(dnx_hbmc_apd_phy_init(unit));

        SHR_IF_ERR_EXIT(dnx_hbm_phy_bist(unit));

        SHR_IF_ERR_EXIT(dnx_hbmc_init_with_apd_phy(unit));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_dram_db.is_initialized.get(unit, &is_dram_initialized));
        if (!is_dram_initialized)
        {
            SHR_IF_ERR_EXIT(dnx_hbmc_init(unit));
        }

        SHR_IF_ERR_EXIT(dnx_dram_db.power_down_callback.power_on.set(unit, 1));

        SHR_IF_ERR_EXIT(dnx_hbmc_hbm_init_all(unit));
    }

    if (TRUE == dnx_data_dram.hbm.dram_temp_monitor_enable_get(unit))
    {
        SHR_IF_ERR_EXIT(dnx_hbmc_traffic_to_hbm_restore(unit));
    }

    if (dnx_hbmc_temp_monitor_check(unit))
    {
        SHR_IF_ERR_EXIT(dnx_hbmc_temp_monitor_resume(unit));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_vendor_info_to_sw_state_set(
    int unit,
    int hbm_index,
    hbm_dram_vendor_info_hbm_t * vendor_info)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(vendor_info, _SHR_E_PARAM, "vendor_info");

    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.gen2_test.set(unit, hbm_index, vendor_info->gen2_test));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.ecc.set(unit, hbm_index, vendor_info->ecc));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.density.set(unit, hbm_index, vendor_info->density));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.manufacturer_id.set(unit, hbm_index, vendor_info->manufacturer_id));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.
                    manufacturing_location.set(unit, hbm_index, vendor_info->manufacturing_location));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.manufacturing_year.set(unit, hbm_index, vendor_info->manufacturing_year));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.manufacturing_week.set(unit, hbm_index, vendor_info->manufacturing_week));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.serial_number.set(unit, hbm_index, 0, vendor_info->serial_number[0]));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.serial_number.set(unit, hbm_index, 1, vendor_info->serial_number[1]));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.addressing_mode.set(unit, hbm_index, vendor_info->addressing_mode));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.channel_available.set(unit, hbm_index, vendor_info->channel_available));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.hbm_stack_hight.set(unit, hbm_index, vendor_info->hbm_stack_hight));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.model_part_number.set(unit, hbm_index, vendor_info->model_part_number));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.is_init.set(unit, hbm_index, TRUE));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_vendor_info_from_sw_state_get(
    int unit,
    int hbm_index,
    hbm_dram_vendor_info_hbm_t * vendor_info)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(vendor_info, _SHR_E_PARAM, "vendor_info");

    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.is_init.get(unit, hbm_index, &vendor_info->is_init));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.gen2_test.get(unit, hbm_index, &vendor_info->gen2_test));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.ecc.get(unit, hbm_index, &vendor_info->ecc));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.density.get(unit, hbm_index, &vendor_info->density));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.manufacturer_id.get(unit, hbm_index, &vendor_info->manufacturer_id));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.
                    manufacturing_location.get(unit, hbm_index, &vendor_info->manufacturing_location));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.manufacturing_year.get(unit, hbm_index, &vendor_info->manufacturing_year));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.manufacturing_week.get(unit, hbm_index, &vendor_info->manufacturing_week));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.serial_number.get(unit, hbm_index, 0, &vendor_info->serial_number[0]));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.serial_number.get(unit, hbm_index, 1, &vendor_info->serial_number[1]));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.addressing_mode.get(unit, hbm_index, &vendor_info->addressing_mode));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.channel_available.get(unit, hbm_index, &vendor_info->channel_available));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.hbm_stack_hight.get(unit, hbm_index, &vendor_info->hbm_stack_hight));
    SHR_IF_ERR_EXIT(dnx_dram_db.vendor_info.model_part_number.get(unit, hbm_index, &vendor_info->model_part_number));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_device_id_to_vendor_info_decode(
    int unit,
    soc_dnx_hbm_device_id_t * device_id,
    hbm_dram_vendor_info_hbm_t * vendor_info)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(device_id, _SHR_E_PARAM, "device_id");
    SHR_NULL_CHECK(vendor_info, _SHR_E_PARAM, "vendor_info");

    SHR_BITCOPY_RANGE(&vendor_info->gen2_test, 0, device_id->device_id_raw, 81, 1);
    SHR_BITCOPY_RANGE(&vendor_info->ecc, 0, device_id->device_id_raw, 80, 1);
    SHR_BITCOPY_RANGE(&vendor_info->density, 0, device_id->device_id_raw, 76, 4);
    SHR_BITCOPY_RANGE(&vendor_info->manufacturer_id, 0, device_id->device_id_raw, 72, 4);
    SHR_BITCOPY_RANGE(&vendor_info->manufacturing_location, 0, device_id->device_id_raw, 68, 4);
    SHR_BITCOPY_RANGE(&vendor_info->manufacturing_year, 0, device_id->device_id_raw, 60, 8);
    SHR_BITCOPY_RANGE(&vendor_info->manufacturing_week, 0, device_id->device_id_raw, 52, 8);
    SHR_BITCOPY_RANGE(&vendor_info->serial_number[1], 0, device_id->device_id_raw, 50, 2);
    SHR_BITCOPY_RANGE(&vendor_info->serial_number[0], 0, device_id->device_id_raw, 18, 32);
    SHR_BITCOPY_RANGE(&vendor_info->addressing_mode, 0, device_id->device_id_raw, 16, 2);
    SHR_BITCOPY_RANGE(&vendor_info->channel_available, 0, device_id->device_id_raw, 8, 8);
    SHR_BITCOPY_RANGE(&vendor_info->hbm_stack_hight, 0, device_id->device_id_raw, 7, 1);
    SHR_BITCOPY_RANGE(&vendor_info->model_part_number, 0, device_id->device_id_raw, 0, 7);

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_hbmc_read_lfsr_loopback_bist_run(
    int unit,
    uint32 hbm_index,
    uint32 channel)
{
    uint32 temp_ecc;
    uint32 temp_dbi_read;
    uint32 temp_dbi_write;
    uint32 mr_orig_value = 0;
    hbmc_shmoo_bist_info_t loopback_default_info = { 0 };
    hbmc_shmoo_bist_err_cnt_t error_counters;
    SHR_FUNC_INIT_VARS(unit);

    loopback_default_info.write_weight = 0x0;
    loopback_default_info.read_weight = 0x1000;
    loopback_default_info.bist_timer_us = 0;
    loopback_default_info.bist_num_actions[0] = 0x10000000;
    loopback_default_info.bist_num_actions[1] = 0;
    loopback_default_info.bank_start_index = 0x00000000;
    loopback_default_info.bank_end_index = 0x0000001F;
    loopback_default_info.column_start_index = 0x00000000;
    loopback_default_info.column_end_index = 0x0000001F;
    loopback_default_info.row_start_index = 0x00000000;
    loopback_default_info.row_end_index = 0x00003FFF;
    loopback_default_info.bist_refresh_enable = 0;
    loopback_default_info.bist_ignore_address = 1;
    loopback_default_info.same_row_commands = 8;
    loopback_default_info.data_mode = DBAL_ENUM_FVAL_DRAM_BIST_MODE_PRBS;
    for (int i = 0; i < HBMC_SHMOO_BIST_NOF_PRBS_DATA_SEEDS; i++)
    {
        loopback_default_info.prbs_seeds[i] = 0xAAAAA;
    }

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hcc_configuration_ecc_dbi_get
                    (unit, hbm_index, channel, &temp_ecc, &temp_dbi_read, &temp_dbi_write));
    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hcc_configuration_ecc_dbi_set(unit, hbm_index, channel, 0, 0, 0));

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_mr_get(unit, hbm_index, channel, 7, &mr_orig_value));

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_mr_set(unit, hbm_index, channel, 7, 0x1));

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_mr_set(unit, hbm_index, channel, 7, 0xb));

    SHR_IF_ERR_EXIT(dnx_hbmc_bist_err_cnt_cb(unit, 0, hbm_index, channel, &error_counters));

    SHR_IF_ERR_EXIT(dnx_hbmc_bist_configuration_set(unit, hbm_index, channel, &loopback_default_info));
    SHR_IF_ERR_EXIT(dnx_hbmc_bist_start(unit, hbm_index, channel));

    SHR_IF_ERR_EXIT(dnx_hbmc_bist_run_done_poll(unit, hbm_index, channel));

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_hcc_configuration_ecc_dbi_set
                    (unit, hbm_index, channel, temp_ecc, temp_dbi_read, temp_dbi_write));

    SHR_IF_ERR_EXIT(dnx_hbmc_dbal_access_mr_set(unit, hbm_index, channel, 7, mr_orig_value));

exit:
    SHR_FUNC_EXIT;
}

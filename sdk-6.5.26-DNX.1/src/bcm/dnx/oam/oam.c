/** \file oam.c
 * 
 *
 * OAM procedures for DNX.
 *
 * The procedured include procedures to add,delete,get the
 * following oam_group_* , oam_endpoint_*,
 * oam_endpoint_action_*, oam_loss_* oam_delay_*,
 * oam_loopback_*, oam_action_*, oam_ais_*, oam_tst_*,
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_OAM

 /*
  * Include files.
  * {
  */
#include <soc/sand/shrextend/shrextend_debug.h>
#include <bcm/oam.h>
#include <soc/dnx/dbal/dbal.h>
#include <bcm/types.h>
#include "oam_internal.h"
#include "oam_counter.h"
#include "bcm_int/dnx/mpls/mpls.h"
#include "bcm_int/dnx/oam/oam_init.h"
#include <soc/dnx/swstate/auto_generated/access/oam_access.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_device.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_port.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_oam.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_bfd.h>
#include <soc/dnx/dnx_err_recovery_manager.h>
#include <bcm_int/dnx/cmn/dnxcmn.h>
#include <bcm_int/dnx/lif/in_lif_profile.h>
#include <bcm_int/dnx/lif/lif_lib.h>
#include <bcm_int/dnx/algo/lif_mngr/lif_mngr.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/access/algo_oam_access.h>
#include <bcm_int/dnx/field/field_entry.h>
#include "bcm_int/dnx/init/init_pp.h"
#include <src/bcm/dnx/oam/oamp_v1/oamp_v1_pe_infra.h>
#include <src/bcm/dnx/oam/oamp_v1/oamp_v1_pe.h>
#include <src/bcm/dnx/oam/oamp_v1/oam_oamp_v1.h>
/*
 * }
 */

/*
 * DEFINEs
 * {
 */
/** Index of LSB in MAC */
#define MAC_LSB_INDEX (UTILEX_PP_MAC_ADDRESS_NOF_U8 - 1)

/*
 * }
 */

/*
 * MACROs
 * {
 */
/** Check if a MAC address is unicast or multicast */
#define OAM_CLASSIFIER_CHECK_MAC_IS_UNICAST(mac_address) ((mac_address[0] & 0x1) != 1)
/** Set correct G_ACH_CHANNEL_TYPE_VALUE field according to the index */
#define DBAL_FIELD_G_ACH_CHANNEL_TYPE_VALUE_INDEX(index) (DBAL_FIELD_CFG_G_ACH_CHANNEL_TYPE_VALUE_1 + index)
/** Set correct G_ACH_LAYER_PROTOCOL_VALUE field according to the index */
#define DBAL_FIELD_G_ACH_LAYER_PROTOCOL_VALUE_INDEX(index) (DBAL_FIELD_CFG_G_ACH_LAYER_PROTOCOL_VALUE_1 + index)

/*
 * }
 */

/* Verify OAM event type */
#define DNX_OAM_EVENT_TYPE_VERIFY(event_types) \
    ((SHR_BITGET(event_types.w, bcmOAMEventEndpointCCMTimeout))         ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointCCMTimein))          ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointRemote))             ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointRemoteUp))           ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointPortDown))           ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointPortUp))             ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointInterfaceDown))      ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointInterfaceUp))        ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointInterfaceTesting))   ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointInterfaceUnkonwn))   ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointInterfaceDormant))   ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointInterfaceNotPresent))||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointInterfaceLLDown))    ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointSdSet))              ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointSdClear))            ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointSfSet))              ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointSfClear))            ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointDExcessSet))         ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointDMissmatch))         ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointDMissmerge))         ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointDAllClear)))

/* Verify OAM performance event type */
#define DNX_OAM_PERFORMANCE_EVENT_TYPE_VERIFY(event_types) \
    ((SHR_BITGET(event_types.w, bcmOAMEventEndpointDmStatistics))         ||\
     (SHR_BITGET(event_types.w, bcmOAMEventEndpointLmStatistics)))

 /*
  * Global and Static
  */
bcm_oam_event_cb _g_oam_event_cb[BCM_MAX_NUM_UNITS][bcmOAMEventCount];
bcm_oam_performance_event_cb _g_oam_performance_event_cb[BCM_MAX_NUM_UNITS][bcmOAMEventCount];
void *_g_oam_event_ud[BCM_MAX_NUM_UNITS][bcmOAMEventCount];

/** Add tcam entry to check if MDL matches 3 DMAC LSB bits */
static shr_error_e
dnx_oam_eth_dmac_mdl_match_tcam_entry_add(
    int unit,
    int mdl_bit_toggle_index,
    int eth_type_offset)
{
    int mdl_offset;
    int eth_type_width = 16;
    uint32 entry_handle_id;
    uint32 pkt_data[10] = { 0x0 };
    uint32 pkt_data_mask[10] = { 0x0 };
    uint32 zero_padding[3] = { 0x0 };
    uint32 oam_et = 0x8902;
    uint32 bits_mask;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Set data for 45 DMAC MSB bits */
    pkt_data[9] = 0x00000018;
    pkt_data[8] = 0x0c200003;
    pkt_data[7] = 0x00000000;

    /** Set data mask for 45 DMAC MSB bits */
    pkt_data_mask[9] = 0x00000fff;
    pkt_data_mask[8] = 0xffffffff;
    pkt_data_mask[7] = 0x80000000;

    /** Set data and mask for MDL in 3 DMAC LSB bits */
    pkt_data[7] = (mdl_bit_toggle_index % 2) << (28 + mdl_bit_toggle_index / 2);
    pkt_data_mask[7] |= (1 << (28 + mdl_bit_toggle_index / 2));

    /** Set data and mask for OAM eth type 0x8902 */
    bits_mask = (1 << eth_type_width) - 1;
    pkt_data[eth_type_offset / 32] = oam_et << (eth_type_offset % 32);
    pkt_data_mask[eth_type_offset / 32] = bits_mask << (eth_type_offset % 32);
    if (32 - eth_type_offset % 32 < eth_type_width)
    {
        bits_mask = (1 << (eth_type_width - (32 - eth_type_offset % 32))) - 1;
        pkt_data[eth_type_offset / 32 + 1] |= (oam_et >> (32 - eth_type_offset % 32)) & bits_mask;
        pkt_data_mask[eth_type_offset / 32 + 1] = bits_mask;
    }

    /** Set data and mask for MDL in OAM PDU */
    mdl_offset = eth_type_offset - 3;
    pkt_data[mdl_offset / 32] |= (((mdl_bit_toggle_index + 1) % 2) << ((mdl_offset % 32) + mdl_bit_toggle_index / 2));
    pkt_data_mask[mdl_offset / 32] |= (1 << ((mdl_offset % 32) + mdl_bit_toggle_index / 2));

    /** Get table handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_TCAM_IDENTIFICATION_DB, &entry_handle_id));

    SHR_IF_ERR_EXIT(dbal_entry_attribute_set(unit, entry_handle_id, DBAL_ENTRY_ATTR_PRIORITY, 3));

    /** setting key fields */
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPE_CURRENT_LAYER_MINUS_1, 0x0, 0x0);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPE_CURRENT_LAYER,
                               DBAL_ENUM_FVAL_LAYER_TYPES_ETHERNET);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_PROFILE, 0x0, 0x0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_NOF_VALID_OAM_LIFS, 0x0, 0x0);
    dbal_entry_key_field_arr32_masked_set(unit, entry_handle_id, DBAL_FIELD_PKT_DATA_AT_FWD_HEADER,
                                          pkt_data, pkt_data_mask);

    /** setting result fields */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TCAM_RESULT_TYPE, INST_SINGLE, 0x0);
    dbal_entry_value_field_arr32_set(unit, entry_handle_id, DBAL_FIELD_ZERO_PADDING_TCAM_IDENT, INST_SINGLE,
                                     zero_padding);
    /** set packet_is_oam to no */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PACKET_IS_OAM, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_MD_LEVEL, INST_SINGLE, 0x7);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_OPCODE, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_OFFSET, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_STAMP_OFFSET, INST_SINGLE, 0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_PCP, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_MY_CFM_MAC, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_LIF_TCAM_INSTRUCTION, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_IS_BFD, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_YOUR_DISCR, INST_SINGLE, 0x0);

    /** Commit table values */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** Delete tcam entry for checking if MDL matches 3 DMAC LSB bits */
static shr_error_e
dnx_oam_eth_dmac_mdl_match_tcam_entry_delete(
    int unit,
    int mdl_bit_toggle_index,
    int eth_type_offset)
{
    int mdl_offset;
    int eth_type_width = 16;
    uint32 entry_handle_id;
    uint32 entry_access_id;
    uint32 pkt_data[10] = { 0x0 };
    uint32 pkt_data_mask[10] = { 0x0 };
    uint32 oam_et = 0x8902;
    uint32 bits_mask;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Set data for 45 DMAC MSB bits */
    pkt_data[9] = 0x00000018;
    pkt_data[8] = 0x0c200003;
    pkt_data[7] = 0x00000000;

    /** Set data mask for 45 DMAC MSB bits */
    pkt_data_mask[9] = 0x00000fff;
    pkt_data_mask[8] = 0xffffffff;
    pkt_data_mask[7] = 0x80000000;

    /** Set data and mask for MDL in 3 DMAC LSB bits */
    pkt_data[7] = (mdl_bit_toggle_index % 2) << (28 + mdl_bit_toggle_index / 2);
    pkt_data_mask[7] |= (1 << (28 + mdl_bit_toggle_index / 2));

    /** Set data and mask for OAM eth type 0x8902 */
    bits_mask = (1 << eth_type_width) - 1;
    pkt_data[eth_type_offset / 32] = oam_et << (eth_type_offset % 32);
    pkt_data_mask[eth_type_offset / 32] = bits_mask << (eth_type_offset % 32);
    if (32 - eth_type_offset % 32 < eth_type_width)
    {
        bits_mask = (1 << (eth_type_width - (32 - eth_type_offset % 32))) - 1;
        pkt_data[eth_type_offset / 32 + 1] |= (oam_et >> (32 - eth_type_offset % 32)) & bits_mask;
        pkt_data_mask[eth_type_offset / 32 + 1] = bits_mask;
    }

    /** Set data and mask for MDL in OAM PDU */
    mdl_offset = eth_type_offset - 3;
    pkt_data[mdl_offset / 32] |= (((mdl_bit_toggle_index + 1) % 2) << ((mdl_offset % 32) + mdl_bit_toggle_index / 2));
    pkt_data_mask[mdl_offset / 32] |= (1 << ((mdl_offset % 32) + mdl_bit_toggle_index / 2));

    /** Get table handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_TCAM_IDENTIFICATION_DB, &entry_handle_id));

    /** setting key fields */
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPE_CURRENT_LAYER_MINUS_1, 0x0, 0x0);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPE_CURRENT_LAYER,
                               DBAL_ENUM_FVAL_LAYER_TYPES_ETHERNET);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_PROFILE, 0x0, 0x0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_NOF_VALID_OAM_LIFS, 0x0, 0x0);
    dbal_entry_key_field_arr32_masked_set(unit, entry_handle_id, DBAL_FIELD_PKT_DATA_AT_FWD_HEADER,
                                          pkt_data, pkt_data_mask);

    /** Get TCAM access id */
    SHR_IF_ERR_EXIT(dbal_entry_access_id_by_key_get(unit, entry_handle_id, &entry_access_id, DBAL_COMMIT));
    SHR_IF_ERR_EXIT(dbal_entry_handle_access_id_set(unit, entry_handle_id, entry_access_id));

    /** Commit entry clear */
    SHR_IF_ERR_EXIT(dbal_entry_clear(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Set enable/disable of checking if MDL matches 3 
 * DMAC LSB bits for Ethernent OAM function
 *
 * \param [in] unit -
 *     Relevant unit.
 * \param [in] control_value -
 *     set enabling when value is 1
 *     set disabling when value is 0
 * \return
 *   \retval Non-zero (!= _SHR_E_NONE) in case of an error
 *   \retval Zero (= _SHR_E_NONE) in case of NO ERROR
 */
shr_error_e
dnx_oam_eth_dmac_mdl_match_check_set(
    int unit,
    uint32 control_value)
{
    int i, j;
    int eth_type_offset;
    int num_of_tag_type;
    int num_of_mdl_bit_toggle;
    uint32 current_value = 0;
    SHR_FUNC_INIT_VARS(unit);

    /*
     * To catch the difference between 3 DMAC LSB bits and 3 bit MDL, 2 entries are added for each bit. 
     *   one entry: DMAC LSB bit is 0 and MDL bit is 1
     *   the other: DMAC LSB bit is 1 and MDL bit is 0
     * So 6 entries added.
     *
     * The simplified format of the key PKT_DATA_AT_FWD_HEADER as below,
     *   +-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-
     *   | 44 MSB bits DMAC  | 4 DMAC LSB bits | SMAC  | VLAN tags | Eth type | 3 bits MDL  |
     *   +-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-
     *   | 01:80:c2:00:00:3  | 0 0 0 0         | x.... | x........ | 8902     | 0 0 1       |
     *   |                   |   0 0 1         |       |           |          | 0 0 0       |
     *   |                   |   0 0 0         |       |           |          | 0 1 0       |
     *   |                   |   0 1 0         |       |           |          | 0 0 0       |
     *   |                   |   0 0 0         |       |           |          | 1 0 0       |
     *   |                   |   1 0 0         |       |           |          | 0 0 0       |
     *   +-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-
     *
     * Untag, single tag and double tag are all supporetd here. 
     * 6 entries for each tag type, 3*6=18 entries are added finally.
     */

    num_of_tag_type = 3;
    num_of_mdl_bit_toggle = 6;

    /** for untag packet, ethernet type offset is 188 in packet data at forward header */
    eth_type_offset = 188;

    SHR_IF_ERR_EXIT(algo_oam_db.eth_dmac_mdl_match_check.get(unit, &current_value));
    if (control_value > 0 && current_value > 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "checing mismatch between eth dmac and mdl is already enabled");
    }
    if (control_value == 0 && current_value == 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "checing mismatch between eth dmac and mdl is already disbled");
    }

    if (control_value)
    {
        /** loop for each tag type */
        for (i = 0; i < num_of_tag_type; i++)
        {
            /** loop for each mdl bit toggle */
            for (j = 0; j < num_of_mdl_bit_toggle; j++)
            {
                SHR_IF_ERR_EXIT(dnx_oam_eth_dmac_mdl_match_tcam_entry_add(unit, j, eth_type_offset));
            }
            /** for each tag type, ethernet type offset decreased by 32 bits */
            eth_type_offset -= 32;
        }
    }
    else
    {
        /** loop for each tag type */
        for (i = 0; i < num_of_tag_type; i++)
        {
            /** loop for each mdl bit toggle */
            for (j = 0; j < num_of_mdl_bit_toggle; j++)
            {
                SHR_IF_ERR_EXIT(dnx_oam_eth_dmac_mdl_match_tcam_entry_delete(unit, j, eth_type_offset));
            }
            /** for each tag type, ethernet type offset decreased by 32 bits */
            eth_type_offset -= 32;
        }
    }

    SHR_IF_ERR_EXIT(algo_oam_db.eth_dmac_mdl_match_check.set(unit, control_value));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 * Get enable/disable of checking if MDL matches 3 
 * DMAC LSB bits for Ethernent OAM function
 *
 * \param [in] unit -
 *     Relevant unit.
 * \param [in] control_value -
 *     value is 1 when enabled
 *     value is 0 when disabled
 * \return
 *   \retval Non-zero (!= _SHR_E_NONE) in case of an error
 *   \retval Zero (= _SHR_E_NONE) in case of NO ERROR
 */
shr_error_e
dnx_oam_eth_dmac_mdl_match_check_get(
    int unit,
    uint32 *control_value)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(algo_oam_db.eth_dmac_mdl_match_check.get(unit, control_value));

exit:
    SHR_FUNC_EXIT;
}

/** Add/Destory mpls tcam entry for oam over native eth */
static shr_error_e
dnx_oam_native_eth_over_pwe_classify_mpls_tcam_set(
    int unit,
    int is_set)
{
    uint32 entry_handle_id;
    uint32 entry_access_id;
    uint32 in_lif_profile_data = 0x0;
    uint32 in_lif_profile_mask = 1 << IN_LIF_PROFILE_NATIVE_INDEXED_MODE_START_BIT;
    uint32 pkt_data[10] = { 0x0 };
    uint32 pkt_data_mask[10] = { 0x0 };
    uint32 zero_padding[3] = { 0x0 };

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_TCAM_IDENTIFICATION_DB, &entry_handle_id));
    if (is_set)
    {
        SHR_IF_ERR_EXIT(dbal_entry_attribute_set(unit, entry_handle_id, DBAL_ENTRY_ATTR_PRIORITY, 3));
    }
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPE_CURRENT_LAYER_MINUS_1,
                               DBAL_ENUM_FVAL_LAYER_TYPES_MPLS_UNTERM);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPE_CURRENT_LAYER,
                               DBAL_ENUM_FVAL_LAYER_TYPES_ETHERNET);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_PROFILE,
                                      in_lif_profile_data, in_lif_profile_mask);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_NOF_VALID_OAM_LIFS, 0x0, 0x0);
    dbal_entry_key_field_arr32_masked_set(unit, entry_handle_id, DBAL_FIELD_PKT_DATA_AT_FWD_HEADER, pkt_data,
                                          pkt_data_mask);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TCAM_RESULT_TYPE, INST_SINGLE, 0x0);
    dbal_entry_value_field_arr32_set(unit, entry_handle_id, DBAL_FIELD_ZERO_PADDING_TCAM_IDENT, INST_SINGLE,
                                     zero_padding);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PACKET_IS_OAM, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_MD_LEVEL, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_OPCODE, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_OFFSET, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_STAMP_OFFSET, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_PCP, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_MY_CFM_MAC, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_LIF_TCAM_INSTRUCTION, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_IS_BFD, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_YOUR_DISCR, INST_SINGLE, 0x0);

    if (is_set)
    {
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }
    else
    {
        SHR_IF_ERR_EXIT(dbal_entry_access_id_by_key_get(unit, entry_handle_id, &entry_access_id, DBAL_COMMIT));
        SHR_IF_ERR_EXIT(dbal_entry_handle_access_id_set(unit, entry_handle_id, entry_access_id));
        SHR_IF_ERR_EXIT(dbal_entry_clear(unit, entry_handle_id, DBAL_COMMIT));
    }

    SHR_IF_ERR_EXIT(algo_oam_db.mpls_oam_native_eth_over_pwe_classify.set(unit, is_set));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** Get mpls tcam entry for oam over native eth */
static shr_error_e
dnx_oam_native_eth_over_pwe_classify_mpls_tcam_get(
    int unit,
    uint32 *is_set)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(algo_oam_db.mpls_oam_native_eth_over_pwe_classify.get(unit, is_set));

exit:
    SHR_FUNC_EXIT;
}

/** Set report mode */
static shr_error_e
dnx_oam_report_mode_set(
    int unit,
    bcm_oam_report_mode_type_t report_mode)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAMP_INIT_GENERAL_CFG, &entry_handle_id));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_REPORT_MODE, INST_SINGLE, (uint32) report_mode);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** Set report mode */
shr_error_e
dnx_oam_report_mode_get(
    int unit,
    uint32 *report_mode)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAMP_INIT_GENERAL_CFG, &entry_handle_id));

    /** Get report mode. */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_REPORT_MODE, INST_SINGLE, report_mode);

    /** Performing the action */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_oam_enable_next_received_slr_get(
    int unit,
    uint32 *value)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAMP_INIT_GENERAL_CFG, &entry_handle_id));

    /** Get report mode. */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_MEASURE_NEXT_RECEIVED_SLR_ENABLE, INST_SINGLE, value);

    /** Performing the action */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get RX/TX enable per opcode index.
* \par DIRECT INPUT:
*   \param [in] unit  -
*   Relevant unit.
*   \param [in] is_rx  -
*   Select which side to be updated, RX or TX.
*   \param [in] index  -
*   Index of register array. Indexing per Opcode-For-Count-Index.
*   \param [out] arg  -
*   Return enable or disable value.
* \par INDIRECT INPUT:
*   * none
* \par DIRECT OUTPUT:
*   shr_error_param - Return relevant error.
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * \ref dnx_oam_opcode_for_count_set
*/
shr_error_e
dnx_oam_opcode_for_count_get(
    int unit,
    uint8 is_rx,
    int index,
    uint32 *arg)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAMP_OPCODE_FOR_COUNT, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OPCODE_FOR_COUNT_INDEX, index);

    if (DNX_OAM_DISSECT_IS_RX_DIRECTION(is_rx))
    {
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_OPCODE_FOR_COUNT_RX_ENABLE, INST_SINGLE, arg);
    }
    else
    {
        dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_OPCODE_FOR_COUNT_TX_ENABLE, INST_SINGLE, arg);
    }

    /** Performing the action */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get TX/RX prefixes and shifts
* \par DIRECT INPUT:
*   \param [in] unit  -
*   Relevant unit.
*   \param [in] shift  -
*   Represent what should be the shift value in the register
* \par INDIRECT INPUT:
*   * none
* \par DIRECT OUTPUT:
*   shr_error_param - Return relevant error.
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * \ref dnx_oam_opcode_for_count_set
*/
static shr_error_e
dnx_oam_tx_rx_shift_counter_cfg_get(
    int unit,
    uint32 *shift)
{

    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAMP_INIT_GENERAL_CFG, &entry_handle_id));

    /** Since the RX and TX shifts are with same value, get and return only one of them. */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_RX_COUNTER_CFG_SHIFT, INST_SINGLE, shift);

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get rfc6374 punt/ignore action per opcode and pdu type
* \par DIRECT INPUT:
*   \param [in] unit  -
*   Relevant unit.
*   \param [in] control_code  -
*   Set action based on the control code
*   \param [in] is_response  -
*   indicates for response packet
*   \param [out] punt_2_ignore_1_pass_0  -
*   action
* \par INDIRECT INPUT:
*   * none
* \par DIRECT OUTPUT:
*   shr_error_param - Return relevant error.
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * \ref dnx_oam_rfc6374_rx_filter_table_set
*/
static shr_error_e
dnx_oam_rfc6374_rx_filter_table_get(
    int unit,
    int control_code,
    uint8 is_response,
    uint32 *punt_2_ignore_1_pass_0)
{

    uint32 punt_value = 0, ingnore_value = 0;
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAMP_MPLS_LM_DM_FILTER, &entry_handle_id));

    /** Setting key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_MPLS_LM_DM_CONTROL_CODE, control_code);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_MPLS_LM_DM_PDU_TYPE_IS_RESPONSE, is_response);

    /** Setting result fields */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_PUNT, INST_SINGLE, &punt_value);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_IGNORE, INST_SINGLE, &ingnore_value);

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
    *punt_2_ignore_1_pass_0 = (punt_value * 2) + (ingnore_value * 1);

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}
/**
* \brief
*  Map the actual OpCode value to OpCode for count index according to the table
* \par DIRECT INPUT:
*   \param [in] unit  -
*   Relevant unit.
*   \param [in] opcode  -
*   Represent the actual packet opcode in range 0-255.
*   \param [in] opcode_for_count_index  -
*   Represent the index for opcode for count in range 0-5.
* \par INDIRECT INPUT:
*   * none
* \par DIRECT OUTPUT:
*   shr_error_param - Return relevant error.
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * \ref dnx_oam_opcode_for_count_set
*/
static shr_error_e
dnx_oam_opcode_to_opcode_for_count_index(
    int unit,
    int opcode,
    int *opcode_for_count_index)
{

    SHR_FUNC_INIT_VARS(unit);

    if (opcode < 0 || opcode > 255)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Not supported Opcode, available range 0-255, actual %d", opcode);
    }

    switch (opcode)
    {
        /** Opcode "0" represent the BFD opcode*/
        case 0:
        case bcmOamOpcodeCCM:
            *opcode_for_count_index = 0;
            break;
        case bcmOamOpcodeLMM:
        case bcmOamOpcodeSLM:
        case bcmOamOpcode1SL:
            *opcode_for_count_index = 1;
            break;
        case bcmOamOpcodeLMR:
        case bcmOamOpcodeSLR:
            *opcode_for_count_index = 2;
            break;
        case bcmOamOpcodeDMM:
        case bcmOamOpcode1DM:
            *opcode_for_count_index = 3;
            break;
        case bcmOamOpcodeDMR:
            *opcode_for_count_index = 4;
            break;
        default:
            *opcode_for_count_index = 5;
            break;
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get an OAM Control entry.
* \param [in] unit  -
*   Relevant unit.
* \param [in] key  -
*   key.type - Type of Control being used
*   key.index - index from which to get control information.
* \param [out] arg -
*   Argument, in which to write the information from the get
*   procedure.
* \retval
*   shr_error_param - Wrong type was selected.
* \remark
*   * None
* \see
*   * \ref bcm_dnx_oam_control_indexed_set
*/
shr_error_e
bcm_dnx_oam_control_indexed_get(
    int unit,
    bcm_oam_control_key_t key,
    uint64 *arg)
{
    int opcode;
    uint32 enable, action = 0;
    uint64 MAX_RANGE;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    switch (key.type)
    {
        /** Get control value (enable/disable) per opcode for TX statistics*/
        case bcmOamControlOampStatsTxOpcode:
        {
            /** Map the actual OpCode value to OpCode index */
            SHR_IF_ERR_EXIT(dnx_oam_opcode_to_opcode_for_count_index(unit, key.index, &opcode));
            SHR_IF_ERR_EXIT(dnx_oam_opcode_for_count_get(unit, bcmOamControlOampStatsTxOpcode, opcode, &enable));
            COMPILER_64_SET(*arg, 0, enable);
        }
            break;
        /** Get control value (enable/disable) per opcode for RX statistics*/
        case bcmOamControlOampStatsRxOpcode:
        {
            SHR_IF_ERR_EXIT(dnx_oam_opcode_to_opcode_for_count_index(unit, key.index, &opcode));
            /** Enable RX per opcode counting */
            SHR_IF_ERR_EXIT(dnx_oam_opcode_for_count_get(unit, bcmOamControlOampStatsRxOpcode, opcode, &enable));
            COMPILER_64_SET(*arg, 0, enable);
        }
            break;
        /** Get action for Query packets */
        case bcmOamControlMplsLmDmOampActionPerQueryControlCode:
        {

            COMPILER_64_SET(MAX_RANGE, 0, 0x02);
            if (COMPILER_64_GT(key.index, MAX_RANGE))
            {
                /*
                 * Valid values are 0-2
                 */
                SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal query control code value.\n");
            }

           /** Set the action */
            SHR_IF_ERR_EXIT(dnx_oam_rfc6374_rx_filter_table_get(unit, key.index, 0 /* Query */ , &action));

            COMPILER_64_SET(*arg, 0, action);
        }
            break;
        /** Get action for Response packets */
        case bcmOamControlMplsLmDmOampActionPerResponseControlCode:
        {

            COMPILER_64_SET(MAX_RANGE, 0, 0x1D);
            if (COMPILER_64_GT(key.index, MAX_RANGE))
            {
                /*
                 * Valid values are 0-2
                 */
                SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal response control code value.\n");
            }

            /** Set the action */
            SHR_IF_ERR_EXIT(dnx_oam_rfc6374_rx_filter_table_get(unit, key.index, 1 /* Response */ , &action));

            COMPILER_64_SET(*arg, 0, action);
        }
            break;
        case bcmOamControlUpMepDmRecyclePort:
        {
            if (DNX_OAMP_IS_V1(unit))
            {
                /*
                 * get up mep TOD port
                 */
                SHR_IF_ERR_EXIT(dnx_up_mep_dm_recycle_port_get(unit, key.index, &action));
                COMPILER_64_SET(*arg, 0, action);
            }
        }
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Not supported bcm oam control index type");
    }

exit:
    SHR_FUNC_EXIT;
}

/** Get CPU port DP and TC values from OAMP_CPUPORT register */
shr_error_e
dnx_oam_cpu_port_dp_tc_get(
    int unit,
    uint32 *dp,
    uint32 *tc)
{

    uint32 entry_handle_id;
    int table;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    table = DBAL_TABLE_OAMP_INIT_CPU_PORT_CFG;
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table, &entry_handle_id));

    /** getting value fields */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_CPU_PORT_TC, INST_SINGLE, tc);
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_CPU_PORT_DP, INST_SINGLE, dp);

    /** Access the table */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set an TOD entry.
* \param [in] unit  -
*   Relevant unit.
* \param [in] is_ntp  -
*   Type of Control being used. "1" - Set NTP, else set 1588
* \param [in] tod -
*   Value that will be set.
* \retval
*   shr_error_none
* \remark
*   * None
* \see
*   * \ref bcm_dnx_oam_control_set
*/
shr_error_e
dnx_oam_tod_set(
    int unit,
    uint8 is_ntp,
    uint64 tod)
{
    uint32 entry_handle_id;
    uint32 tmp = 0;
    int tod_config_in_eci;
    int tod_config_in_ns;
    uint32 time_frac = COMPILER_64_LO(tod);
    uint32 time_sec = COMPILER_64_HI(tod);

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    {
        if (DNX_OAMP_IS_V1(unit))
        {
            tod_config_in_eci = dnx_data_oam.general.oam_tod_config_in_eci_get(unit);
            tod_config_in_ns = dnx_data_oam.general.oam_tod_config_in_ns_get(unit);

            if (tod_config_in_eci)
            {
                if (is_ntp)
                {

                    /*
                     * disable count_enable, clear load_once and time_control_active before reactive
                     */
                    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_NTP_TOD_CONFIGURATION, &entry_handle_id));
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_COUNT_ENABLE, INST_SINGLE, 0);
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LOAD_ONCE, INST_SINGLE, 0);
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TIME_CONTROL_ACTIVE, INST_SINGLE, 0);
                    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

                    /*
                     * write provided values
                     */
                    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_NTP_TOD_CONFIGURATION, &entry_handle_id));
                    /*
                     * write value to frac sec lower register
                     */
                    SHR_BITCOPY_RANGE(&tmp, 26, &time_frac, 0, 6);
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TIME_FRAC_SEC_LOWER, INST_SINGLE,
                                                 tmp);
                    /*
                     * write value to frac sec upper register
                     */
                    tmp = 0;
                    SHR_BITCOPY_RANGE(&tmp, 0, &time_frac, 6, 26);
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TIME_FRAC_SEC_UPPER, INST_SINGLE,
                                                 tmp);
                    /*
                     * write value to frequency register (4 nS in binary fraction)
                     */
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TIME_FREQ_CONTROL, INST_SINGLE,
                                                 dnx_data_oam.general.oam_ntp_time_freq_control_get(unit));
                    /*
                     * write value to time sec register
                     */
                    tmp = 0;
                    SHR_BITCOPY_RANGE(&tmp, 0, &time_sec, 1, 31);
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ONE_SEC, INST_SINGLE,
                                                 (time_sec & 0x00000001) != 0);

                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_UPPER_SEC, INST_SINGLE, tmp);
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_NTP_FREQ_CONTROL, INST_SINGLE,
                                                 dnx_data_oam.general.oam_ntp_freq_control_word_get(unit));

                    /*
                     * write 0x2 to select bit 32 mode.
                     */
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_EVENT_MUX_CONTROL, INST_SINGLE, 0x2);

                    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

                    /*
                     * load provided values
                     */
                    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_NTP_TOD_CONFIGURATION, &entry_handle_id));
                    /*
                     * load upper_sec, one_sec, frac_sec_upper, frac_sec_lower, time_freq_control
                     */
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LOAD_ONCE, INST_SINGLE, 1);
                    /*
                     * act as event_mux_control
                     */
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TIME_CONTROL_ACTIVE, INST_SINGLE, 1);
                    /*
                     * write to control register to load values
                     */
                    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

                    /*
                     * clear load_once and time_control_active, enable count_enable
                     */
                    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_NTP_TOD_CONFIGURATION, &entry_handle_id));
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LOAD_ONCE, INST_SINGLE, 0);
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TIME_CONTROL_ACTIVE, INST_SINGLE, 0);
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_COUNT_ENABLE, INST_SINGLE, 1);
                    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
                }
                else
                {
                    /*
                     * disable count_enable, clear load_once and time_control_active before reactive
                     */
                    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_1588_TOD_CONFIGURATION, &entry_handle_id));
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_COUNT_ENABLE, INST_SINGLE, 0);
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LOAD_ONCE, INST_SINGLE, 0);
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TIME_CONTROL_ACTIVE, INST_SINGLE, 0);
                    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

                    /*
                     * write provided values
                     */
                    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_1588_TOD_CONFIGURATION, &entry_handle_id));
                    /*
                     * write value to frac sec lower register
                     */
                    SHR_BITCOPY_RANGE(&tmp, 26, &time_frac, 0, 6);
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TIME_FRAC_SEC_LOWER, INST_SINGLE,
                                                 tmp);
                    /*
                     * write value to frac sec upper register
                     */
                    tmp = 0;
                    SHR_BITCOPY_RANGE(&tmp, 0, &time_frac, 6, 26);
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TIME_FRAC_SEC_UPPER, INST_SINGLE,
                                                 tmp);
                    /*
                     * write value to frequency register (4 nS)
                     */
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TIME_FREQ_CONTROL, INST_SINGLE,
                                                 dnx_data_oam.general.oam_IEEE_1588_time_freq_control_get(unit));
                    /*
                     * write value to time sec register
                     */
                    tmp = 0;
                    SHR_BITCOPY_RANGE(&tmp, 0, &time_sec, 1, 31);
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_ONE_SEC, INST_SINGLE,
                                                 (time_sec & 0x00000001) != 0);
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_UPPER_SEC, INST_SINGLE, tmp);

                    /*
                     * write 0x2 to select bit 32 mode.
                     */
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_EVENT_MUX_CONTROL, INST_SINGLE, 2);

                    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

                    /*
                     * load provided values
                     */
                    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_1588_TOD_CONFIGURATION, &entry_handle_id));
                    /*
                     * load upper_sec, one_sec, frac_sec_upper, frac_sec_lower, time_freq_control
                     */
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LOAD_ONCE, INST_SINGLE, 1);
                    /*
                     * act as event_mux_control
                     */
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TIME_CONTROL_ACTIVE, INST_SINGLE, 1);
                    /*
                     * write to control register to load values
                     */
                    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

                    /*
                     * clear load_once and time_control_active, enable count_enable
                     */
                    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_1588_TOD_CONFIGURATION, &entry_handle_id));
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LOAD_ONCE, INST_SINGLE, 0);
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TIME_CONTROL_ACTIVE, INST_SINGLE, 0);
                    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_COUNT_ENABLE, INST_SINGLE, 1);
                    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
                }
            }
            if (tod_config_in_ns)
            {
                /*
                 * Prepare the values in ns registers
                 */
                SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_1588_TOD_CONFIGURATION_NS, &entry_handle_id));

                tmp = 0;
                SHR_BITCOPY_RANGE(&tmp, 0, &time_frac, 22, 10);
                dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_NS_IEEE1588_TIME_FRAC_SEC_S2,
                                             INST_SINGLE, tmp);
                tmp = 0;
                SHR_BITCOPY_RANGE(&tmp, 10, &time_frac, 0, 21);
                dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_NS_IEEE1588_TIME_FRAC_SEC_S1,
                                             INST_SINGLE, tmp);

                tmp = 0;
                SHR_BITCOPY_RANGE(&tmp, 0, &time_sec, 1, 31);
                dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_NS_IEEE1588_TIME_SEC_LOWER_SEC,
                                             INST_SINGLE, tmp);
                dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_NS_IEEE1588_TIME_SEC_ONE_SEC,
                                             INST_SINGLE, (time_sec & 0x00000001) != 0);
                SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

                /*
                 * Load values :
                 * bit[2] = IEEE1588_TIME_FRAC_SEC_S1 load
                 * bit[3] = IEEE1588_TIME_FRAC_SEC_S2 load
                 * bit[4] = IEEE1588_TIME_ONE_SEC load
                 * bit[5] = IEEE1588_TIME_SEC_UPPER load (all 47b)
                 */
                SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_1588_TOD_CONFIGURATION_NS, &entry_handle_id));
                dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_NS_IEEE1588_TIME_CONTROL_LOAD_ENABLE,
                                             INST_SINGLE, 0x3c);
                SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            }
        }
    }
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get the last TOD value.
* \param [in] unit  -
*   Relevant unit.
* \param [in] is_ntp  -
*   Type of Control being used. "1" - Set NTP, else set 1588
* \param [out] tod -
*   Value that will be get.
* \retval
*   shr_error_none
* \remark
*   * None
* \see
*   * \ref bcm_dnx_oam_control_set
*/
shr_error_e
dnx_oam_tod_get(
    int unit,
    uint8 is_ntp,
    uint64 *tod)
{

    uint32 entry_handle_id;
    int table;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    if (is_ntp)
    {
        table = DBAL_TABLE_OAM_NTP_TOD_VALUE;
    }
    else
    {
        table = DBAL_TABLE_OAM_1588_TOD_VALUE;
    }
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table, &entry_handle_id));

    /** Get value */
    dbal_value_field64_request(unit, entry_handle_id, DBAL_FIELD_LAST_TOD_VALUE, INST_SINGLE, tod);

    /** Access the table */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}
/** Get the traffic priority from OAMP_ARBITER_WEIGHT register based on field*/
shr_error_e
dnx_oam_arp_weight_get(
    int unit,
    uint32 field_id,
    uint32 *arb_weight_value)
{

    uint32 entry_handle_id;
    int table;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    table = DBAL_TABLE_OAMP_ARBITER_WEIGHT;
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table, &entry_handle_id));

    /** setting value fields */
    dbal_value_field32_request(unit, entry_handle_id, field_id, INST_SINGLE, arb_weight_value);

    /** Access the table */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** Get the control code value for control code filed in RFC6374 PDU */
shr_error_e
dnx_oam_rfc_6374_control_code_get(
    int unit,
    uint8 is_lm,
    uint8 is_response,
    uint32 *control_value)
{

    uint32 entry_handle_id;
    int table;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    table = DBAL_TABLE_OAMP_RFC_6374_LM_DM_CONTROL_CODE;
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table, &entry_handle_id));

    if (is_lm)
    {
        if (is_response)
        {
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LM_RESPONSE, INST_SINGLE, control_value);
        }
        else
        {
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_LM_QUERY, INST_SINGLE, control_value);
        }
    }
    else
    {
        if (is_response)
        {
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_DM_RESPONSE, INST_SINGLE, control_value);
        }
        else
        {
            dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_DM_QUERY, INST_SINGLE, control_value);
        }
    }

    /** Access the table */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 *  * \brief -  get whether BFD over PHP packet classification has been enabled
 *
 *  \param [in] unit - Number of hardware unit used.
 *  \param [in] *is_set -  if  BFD over PHP packet classification is enabled
 *
 *  \return
 *  shr_error_e
 *
 *  \remark
 *
 *  \see
 *  None
 *  */
static shr_error_e
dnx_bfd_php_tcam_entry_get(
    int unit,
    int *is_set)
{
    uint32 entry_handle_id;
    uint32 entry_access_id;
    uint32 pkt_data[10] = { 0x0 };
    uint32 pkt_data_mask[10] = { 0x0 };
    bcm_ip_t dst_ip_addr = 0;
    shr_error_e rv = _SHR_E_NONE;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    *is_set = 0;
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_TCAM_IDENTIFICATION_DB, &entry_handle_id));

    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_PROFILE, 0x0, 0x0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_NOF_VALID_OAM_LIFS, 0x0, 0x0);
    /** Qualify DIP and UDP port*/
    dst_ip_addr = 0x7f000000;
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPE_CURRENT_LAYER_MINUS_1,
                               DBAL_ENUM_FVAL_LAYER_TYPES_ETHERNET);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPE_CURRENT_LAYER,
                               DBAL_ENUM_FVAL_LAYER_TYPES_IPV4);

    /** match ttl=1 and IP protocal=0x11 */
    pkt_data[7] = 0x11;
    pkt_data_mask[7] = 0xfff;
    pkt_data[6] = 0x1 << 28;
    pkt_data_mask[6] = 0xf << 28;

    /** match DIP of packet, which equal to local src_ip,300 bits starts from Ver of IP header to your-disc BFD(MSB 12bits)*/
    pkt_data[5] = dst_ip_addr >> 20;
    pkt_data_mask[5] = 0xff0;
    pkt_data[4] = dst_ip_addr << 12;
    pkt_data_mask[4] = 0;
           /** udp = 3784*/
    pkt_data[3] = 3784 << 12;
    pkt_data_mask[3] = 0xFFFF000;
    dbal_entry_key_field_arr32_masked_set(unit, entry_handle_id, DBAL_FIELD_PKT_DATA_AT_FWD_HEADER, pkt_data,
                                          pkt_data_mask);

    rv = dbal_entry_access_id_by_key_get(unit, entry_handle_id, &entry_access_id, DBAL_COMMIT);
    if (rv == _SHR_E_NOT_FOUND)
    {
        *is_set = 0;
    }
    else
    {
        SHR_IF_ERR_EXIT(rv);
        *is_set = 1;
    }
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get an OAM Control entry. This function is not supported.
* \param [in] unit  -
*   Relevant unit.
* \param [in] type  -
*   Type of Control being used
* \param [out] arg -
*   Argument, in which to write the information from the get
*   procedure.
* \retval
*   shr_error_unavail - Return unavailable.
* \remark
*   * None
* \see
*   * \ref bcm_dnx_oam_control_set
*/
shr_error_e
bcm_dnx_oam_control_get(
    int unit,
    bcm_oam_control_type_t type,
    uint64 *arg)
{
    uint32 counter_range_min;
    uint32 counter_range_max;
    uint32 arbiter_weight_value;
    uint32 shift_index;
    uint32 report_mode;
    uint32 slr_enable_value;
    uint32 mdl_ignore_value;
    uint32 dmac_mdl_match;
    uint32 dp, tc, dp_tc;
    uint32 control_code_value;
    uint32 value;
    uint32 ive_command;
    shr_error_e rv;
    /** bfd_php_tcam_is_set represents whether the tcam entry for BFD over PHP packet has been set */
    int bfd_php_tcam_is_set;
    /** bfd_php_tcam_enable means if the feature about BFD over PHP packet is supported */
    int bfd_php_tcam_enable;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    switch (type)
    {
            /*
             * Get lower boundary of counter range for non PCP counters
             */
        case bcmOamControlLmPcpCounterRangeMin:
        {
            /*
             * Get current counter range values Ingress and Egress will always have the same range, so we read the
             * ingress register only.
             */
            rv = dnx_oam_counter_global_range_get(unit, DNX_OAM_CLASSIFIER_INGRESS, &counter_range_min,
                                                  &counter_range_max);
            SHR_IF_ERR_EXIT(rv);

            COMPILER_64_SET(*arg, 0, counter_range_min);
        }
            break;
            /*
             * Get upper boundary of counter range for non PCP counters
             */
        case bcmOamControlLmPcpCounterRangeMax:
        {
            /*
             * Get current counter range values Ingress and Egress will always have the same range, so we read the
             * ingress register only.
             */
            rv = dnx_oam_counter_global_range_get(unit, DNX_OAM_CLASSIFIER_INGRESS, &counter_range_min,
                                                  &counter_range_max);
            SHR_IF_ERR_EXIT(rv);

            COMPILER_64_SET(*arg, 0, counter_range_max);
        }
            break;
        case bcmOamControlOampPuntPacketIntPri:
        {
            /*
             * Read the register, extract the fields, combine them and write to the output parameter
             */
            rv = dnx_oam_cpu_port_dp_tc_get(unit, &dp, &tc);
            SHR_IF_ERR_EXIT(rv);

            dp_tc = dp | (tc << 2);
            COMPILER_64_SET(*arg, 0, dp_tc);
        }
            break;
        /** Get TX/RX Shift value*/
        case bcmOamControlOampStatsShift:
        {
            SHR_IF_ERR_EXIT(dnx_oam_tx_rx_shift_counter_cfg_get(unit, &shift_index));
            COMPILER_64_SET(*arg, 0, shift_index);
        }
            break;
        case bcmOamControlReportMode:
        {
            SHR_IF_ERR_EXIT(dnx_oam_report_mode_get(unit, &report_mode));
            COMPILER_64_SET(*arg, 0, report_mode);
        }
            break;
        case bcmOamControlFlexibleDropPort:
        case bcmOamControlFlexibleDropCVlan:
        case bcmOamControlFlexibleDropSVlan:
        case bcmOamControlFlexibleDropCPlusSVlan:
        case bcmOamControlFlexibleDropVP:
        case bcmOamControlFlexibleDropEgressPort:
        case bcmOamControlFlexibleDropEgressCVlan:
        case bcmOamControlFlexibleDropEgressSVlan:
        case bcmOamControlFlexibleDropEgressCPlusSVlan:
        case bcmOamControlFlexibleDropEgressVP:
        case bcmOamControlFlexibleDropPasssiveSap:
        case bcmOamControlFlexibleDropEgressPasssiveSap:
        case bcmOamControlUnknownAchCount:
        case bcmOamControlNtpToD:
        {
            /*
             * Get current NTP TOD value
             */
            rv = dnx_oam_tod_get(unit, 1, arg);
            SHR_IF_ERR_EXIT(rv);
        }
            break;
        case bcmOamControl1588ToD:
        {
            /*
             * Get current 1588 TOD value
             */
            rv = dnx_oam_tod_get(unit, 0, arg);
            SHR_IF_ERR_EXIT(rv);
        }
            break;
        case bcmOamControlSrcMacLsbReserve:
        case bcmOamControlSrcMacLsbUnReserve:
        case bcmOamControlOampCCMWeight:
        {
            /**
             * Read the register, extract the fields, combine them and write to the output parameter
             */
            rv = dnx_oam_arp_weight_get(unit, DBAL_FIELD_TXM_ARB_WEIGHT, &arbiter_weight_value);
            COMPILER_64_SET(*arg, 0, arbiter_weight_value);
        }
            break;
        case bcmOamControlOampSATWeight:
        {
            /**
             * Read the register, extract the fields, combine them and write to the output parameter
             */
            rv = dnx_oam_arp_weight_get(unit, DBAL_FIELD_SAT_ARB_WEIGHT, &arbiter_weight_value);
            COMPILER_64_SET(*arg, 0, arbiter_weight_value);
        }
            break;
        case bcmOamControlOampResponseWeight:
        {
            /**
             * Read the register, extract the fields, combine them and write to the output parameter
             */
            rv = dnx_oam_arp_weight_get(unit, DBAL_FIELD_RSP_ARB_WEIGHT, &arbiter_weight_value);
            COMPILER_64_SET(*arg, 0, arbiter_weight_value);
        }
            break;
        case bcmOamControlEnableNextReceivedSlr:
        {
            SHR_IF_ERR_EXIT(dnx_oam_enable_next_received_slr_get(unit, &slr_enable_value));
            COMPILER_64_SET(*arg, 0, slr_enable_value);
        }
            break;
        case bcmOamControlMplsOamMdlIgnore:
        {
            SHR_IF_ERR_EXIT(dnx_oam_mpls_tp_mdl_ignore_get(unit, &mdl_ignore_value));
            COMPILER_64_SET(*arg, 0, mdl_ignore_value);
        }
            break;
        case bcmOamControlEthDmacMdlMatchCheck:
        {
            if (dnx_data_oam.general.feature_get(unit, dnx_data_oam_general_oam_dmac_mdl_match_check_control_support) ==
                1)
            {
                SHR_IF_ERR_EXIT(dnx_oam_eth_dmac_mdl_match_check_get(unit, &dmac_mdl_match));
                COMPILER_64_SET(*arg, 0, dmac_mdl_match);
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Not supported bcm oam control type");
            }
        }
            break;
        case bcmOamControlMplsLmQueryControlCode:
        {
            SHR_IF_ERR_EXIT(dnx_oam_rfc_6374_control_code_get
                            (unit, 1 /** LM */ , 0 /** Query */ , &control_code_value));
            COMPILER_64_SET(*arg, 0, control_code_value);
        }
            break;
        case bcmOamControlMplsLmResponderControlCode:
        {
            SHR_IF_ERR_EXIT(dnx_oam_rfc_6374_control_code_get
                            (unit, 1 /** LM */ , 1 /** Response */ , &control_code_value));
            COMPILER_64_SET(*arg, 0, control_code_value);
        }
            break;
        case bcmOamControlMplsDmQueryControlCode:
        {
            SHR_IF_ERR_EXIT(dnx_oam_rfc_6374_control_code_get
                            (unit, 0 /** DM */ , 0 /** Query */ , &control_code_value));
            COMPILER_64_SET(*arg, 0, control_code_value);
        }
            break;
        case bcmOamControlMplsDmResponderControlCode:
        {
            SHR_IF_ERR_EXIT(dnx_oam_rfc_6374_control_code_get
                            (unit, 0 /** DM */ , 1 /** Response */ , &control_code_value));
            COMPILER_64_SET(*arg, 0, control_code_value);
        }
            break;
        case bcmOamControlEnableBfdPhp:
        {
            bfd_php_tcam_enable =
                dnx_data_bfd.general.feature_get(unit, dnx_data_bfd_general_bfd_over_php_tcam_support);
            if (bfd_php_tcam_enable == 0)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG,
                             "BFD over PHP is supported naturally on the device and no additional config!\n");
            }
            SHR_IF_ERR_EXIT(dnx_bfd_php_tcam_entry_get(unit, &bfd_php_tcam_is_set));
            COMPILER_64_SET(*arg, 0, bfd_php_tcam_is_set);
        }
            break;
        case bcmOamControlIngressVlanEditClassDeleteOneVlanTag:
        {
            if (dnx_data_oam.oamp.feature_get(unit, dnx_data_oam_oamp_oamp_v2) == 0)
            {
                SHR_IF_ERR_EXIT(dnx_oam_oamp_v1_down_egress_inject_delete_one_vlan_ive_command_get(unit, &ive_command));
                COMPILER_64_SET(*arg, 0, ive_command);
            }
        }
            break;
        case bcmOamControlIngressVlanEditClassDeleteTwoVlanTags:
        {
            if (dnx_data_oam.oamp.feature_get(unit, dnx_data_oam_oamp_oamp_v2) == 0)
            {
                SHR_IF_ERR_EXIT(dnx_oam_oamp_v1_down_egress_inject_delete_two_vlan_ive_command_get(unit, &ive_command));
                COMPILER_64_SET(*arg, 0, ive_command);
            }
        }
            break;
        case bcmOamControlOampInjectedNetworkQos:
        {
            SHR_IF_ERR_EXIT(dnx_oam_oamp_tx_pph_network_qos_get(unit, &value));
            COMPILER_64_SET(*arg, 0, value);
        }
            break;
        case bcmOamControlNativeEthernetOverPweClassification:
        {
            SHR_IF_ERR_EXIT(dnx_oam_native_eth_over_pwe_classify_mpls_tcam_get(unit, &value));
            COMPILER_64_SET(*arg, 0, value);
        }
            break;

        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Not supported bcm oam control type");
    }

exit:
    SHR_FUNC_EXIT;
}

/** Set TX/RX prefixes and shifts */
static shr_error_e
dnx_oam_tx_rx_shift_counter_cfg_set(
    int unit,
    int shift)
{

    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAMP_INIT_GENERAL_CFG, &entry_handle_id));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TX_COUNTER_CFG_PREFIX, INST_SINGLE,
                                 0 /** TX prefix*/ );
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TX_COUNTER_CFG_SHIFT, INST_SINGLE, shift);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RX_COUNTER_CFG_PREFIX, INST_SINGLE,
                                 1 /** RX prefix*/ );
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_RX_COUNTER_CFG_SHIFT, INST_SINGLE, shift);

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set RX/TX enable per opcode index.
* \par DIRECT INPUT:
*   \param [in] unit  -
*   Relevant unit.
*   \param [in] is_rx  -
*   Select which side to be updated, RX or TX.
*   \param [in] index  -
*   Index of register array. Indexing per Opcode-For-Count-Index
*   \param [in] arg  -
*   Set enable or disable value.
* \par INDIRECT INPUT:
*   * none
* \par DIRECT OUTPUT:
*   shr_error_param - Return relevant error.
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * \ref dnx_oam_opcode_for_count_get
*/
shr_error_e
dnx_oam_opcode_for_count_set(
    int unit,
    uint8 is_rx,
    int index,
    uint8 arg)
{

    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAMP_OPCODE_FOR_COUNT, &entry_handle_id));

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_OPCODE_FOR_COUNT_INDEX, index);

    /** setting value fields */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OPCODE_FOR_COUNT, INST_SINGLE, index);
    if (DNX_OAM_DISSECT_IS_RX_DIRECTION(is_rx))
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OPCODE_FOR_COUNT_RX_ENABLE, INST_SINGLE, arg);
    }
    else
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OPCODE_FOR_COUNT_TX_ENABLE, INST_SINGLE, arg);
    }

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set rfc6374 punt/ignore action per opcode and pdu type
* \par DIRECT INPUT:
*   \param [in] unit  -
*   Relevant unit.
*   \param [in] control_code  -
*   Set action based on the control code
*   \param [in] is_response  -
*   indicates for response packet
*   \param [out] punt_2_ignore_1_pass_0  -
*   action
* \par INDIRECT INPUT:
*   * none
* \par DIRECT OUTPUT:
*   shr_error_param - Return relevant error.
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * \ref dnx_oam_rfc6374_rx_filter_table_get
*/
shr_error_e
dnx_oam_rfc6374_rx_filter_table_set(
    int unit,
    int control_code,
    uint8 is_response,
    uint32 punt_2_ignore_1_pass_0)
{

    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAMP_MPLS_LM_DM_FILTER, &entry_handle_id));

    /** Setting key field according to index */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_MPLS_LM_DM_CONTROL_CODE, control_code);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_MPLS_LM_DM_PDU_TYPE_IS_RESPONSE, is_response);

    if (punt_2_ignore_1_pass_0 == 0)    /* Enable the packet */
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IGNORE, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PUNT, INST_SINGLE, 0);
    }
    else if (punt_2_ignore_1_pass_0 == 1)       /* Ignore the packet */
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IGNORE, INST_SINGLE, 1);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PUNT, INST_SINGLE, 0);
    }
    else if (punt_2_ignore_1_pass_0 == 2)       /* Punt the packet */
    {
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_IGNORE, INST_SINGLE, 0);
        dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PUNT, INST_SINGLE, 1);
    }

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set an OAM Control entry.
* \param [in] unit  -
*   Relevant unit.
* \param [in] key  - Type of Control being used:
*   key.type - Type of Control being used
*       bcmOamControlOampStatsTxOpcode - Enable per opcode counting for TX side.
*       bcmOamControlOampStatsRxOpcode - Enable per opcode counting for TX side.
*   key.index - index to which will write.
* \param [in] arg -
*   Argument, containing information about the Control entry.
* \retval
*   shr_error_param - Wrong type was selected.
* \remark
*   * None
* \see
*   * \ref bcm_dnx_oam_control_indexed_get
*/
shr_error_e
bcm_dnx_oam_control_indexed_set(
    int unit,
    bcm_oam_control_key_t key,
    uint64 arg)
{
    shr_error_e rv;
    int opcode, action;
    uint64 is_enabled = COMPILER_64_INIT(0, 1);
    uint64 MAX_RANGE;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    switch (key.type)
    {
        /** Enable/Disable statistics per opcode counting for TX side */
        case bcmOamControlOampStatsTxOpcode:
        {
            /** Map the actual OpCode value to OpCode index */
            SHR_IF_ERR_EXIT(dnx_oam_opcode_to_opcode_for_count_index(unit, key.index, &opcode));
            if (COMPILER_64_EQ(arg, is_enabled))
            {
                /** Enable TX per opcode counting */
                rv = dnx_oam_opcode_for_count_set(unit, bcmOamControlOampStatsTxOpcode, opcode, TRUE);
            }
            else
            {
                /** Disable TX per opcode counting */
                rv = dnx_oam_opcode_for_count_set(unit, bcmOamControlOampStatsTxOpcode, opcode, FALSE);
            }

            SHR_IF_ERR_EXIT(rv);
        }
            break;
        /** Enable/Disable statistics per opcode counting for RX side */
        case bcmOamControlOampStatsRxOpcode:
        {
            SHR_IF_ERR_EXIT(dnx_oam_opcode_to_opcode_for_count_index(unit, key.index, &opcode));
            if (COMPILER_64_EQ(arg, is_enabled))
            {
                /** Enable RX per opcode counting */
                rv = dnx_oam_opcode_for_count_set(unit, bcmOamControlOampStatsRxOpcode, opcode, TRUE);
            }
            else
            {
                /** Disable RX per opcode counting */
                rv = dnx_oam_opcode_for_count_set(unit, bcmOamControlOampStatsRxOpcode, opcode, FALSE);
            }

            SHR_IF_ERR_EXIT(rv);
        }
            break;
        /** Set action to Query packets */
        case bcmOamControlMplsLmDmOampActionPerQueryControlCode:
        {

            /**
            * 0 - accept the packet
            * 1 - Ignore the packet
            * 2 - Punt the packet
            */
            action = COMPILER_64_LO(arg);
            COMPILER_64_SET(MAX_RANGE, 0, 0x02);
            if (COMPILER_64_GT(key.index, MAX_RANGE))
            {
                /*
                 * Valid values are 0-2
                 */
                SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal query control code value.\n");
            }
            COMPILER_64_SET(MAX_RANGE, 0, 0x2);
            if (COMPILER_64_GT(action, MAX_RANGE))
            {
                /*
                 * Valid values are 0-2
                 */
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Illegal arg value! Valid values are: 0 - accept the packet, 1 - Ignore the packet, 2 - Punt the packet, 3 - Set Punt and Ignore.\n");
            }

            /** Set the action */
            SHR_IF_ERR_EXIT(dnx_oam_rfc6374_rx_filter_table_set(unit, key.index, 0 /* Query */ , action));

        }
            break;
        /** Set action to Response packets */
        case bcmOamControlMplsLmDmOampActionPerResponseControlCode:
        {
            /**
            * 0 - accept the packet
            * 1 - Ignore the packet
            * 2 - Punt the packet
            */
            action = COMPILER_64_LO(arg);

            COMPILER_64_SET(MAX_RANGE, 0, 0x1D);
            if (COMPILER_64_GT(key.index, MAX_RANGE))
            {
                /*
                 * Valid values are 0-29
                 */
                SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal response control code value.\n");
            }
            COMPILER_64_SET(MAX_RANGE, 0, 0x2);
            if (COMPILER_64_GT(action, MAX_RANGE))
            {
                /*
                 * Valid values are 0-2
                 */
                SHR_ERR_EXIT(_SHR_E_PARAM,
                             "Illegal arg value! Valid values are: 0 - accept the packet, 1 - Ignore the packet, 2 - Punt the packet, 3 - Set Punt and Ignore.\n");
            }

            /** Set the action */
            SHR_IF_ERR_EXIT(dnx_oam_rfc6374_rx_filter_table_set(unit, key.index, 1 /* Response */ , action));
        }
            break;
        case bcmOamControlUpMepDmRecyclePort:
        {
            if (DNX_OAMP_IS_V1(unit))
            {
                /*
                 * Set up mep TOD dest
                 */
                action = COMPILER_64_LO(arg);
                rv = dnx_up_mep_dm_recycle_port_set(unit, key.index, action);
                SHR_IF_ERR_EXIT(rv);
            }
        }
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Not supported bcm oam control index type");
    }

exit:
    SHR_FUNC_EXIT;
}

/** Set CPU port DP and TC values to OAMP_CPUPORT register */
shr_error_e
dnx_oam_cpu_port_dp_tc_set(
    int unit,
    uint32 dp,
    uint32 tc)
{

    uint32 entry_handle_id;
    int table;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    table = DBAL_TABLE_OAMP_INIT_CPU_PORT_CFG;
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table, &entry_handle_id));

    /** setting value fields */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CPU_PORT_TC, INST_SINGLE, tc);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CPU_PORT_DP, INST_SINGLE, dp);

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** Set the traffic priority from OAMP_ARBITER_WEIGHT register based on field*/
shr_error_e
dnx_oam_arp_weight_set(
    int unit,
    uint32 field_id,
    uint32 arb_weight_value)
{

    uint32 entry_handle_id;
    int table;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    table = DBAL_TABLE_OAMP_ARBITER_WEIGHT;
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table, &entry_handle_id));

    /** setting value fields */
    dbal_entry_value_field32_set(unit, entry_handle_id, field_id, INST_SINGLE, arb_weight_value);

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** Set MEASURE_NEXT_RECEIVED_SLR_ENABLE */
static shr_error_e
dnx_oam_enable_next_received_slr_set(
    int unit,
    uint32 control_value)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAMP_INIT_GENERAL_CFG, &entry_handle_id));

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_MEASURE_NEXT_RECEIVED_SLR_ENABLE, INST_SINGLE,
                                 control_value);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/** Set the control code value for control code filed in RFC6374 PDU*/
shr_error_e
dnx_oam_rfc_6374_control_code_set(
    int unit,
    uint8 is_lm,
    uint8 is_response,
    uint32 control_value)
{

    uint32 entry_handle_id;
    int table;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    table = DBAL_TABLE_OAMP_RFC_6374_LM_DM_CONTROL_CODE;
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table, &entry_handle_id));

    if (is_lm)
    {
        if (is_response)
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LM_RESPONSE, INST_SINGLE, control_value);
        }
        else
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_LM_QUERY, INST_SINGLE, control_value);
        }
    }
    else
    {
        if (is_response)
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DM_RESPONSE, INST_SINGLE, control_value);
        }
        else
        {
            dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_DM_QUERY, INST_SINGLE, control_value);
        }
    }

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 *  * \brief -  Add oam tcam entry to classify BFD over PHP packet
 *
 *  \param [in] unit - Number of hardware unit used.
 *  \param [in] is_set -  add or destory
 *  \return
 *  shr_error_e
 *
 *  \remark
 *
 *  \see
 *  None
 *  */
static shr_error_e
dnx_bfd_php_tcam_entry_set(
    int unit,
    int is_set)
{
    uint32 entry_access_id;
    uint32 entry_handle_id;
    uint32 pkt_data[10] = { 0x0 };
    uint32 pkt_data_mask[10] = { 0x0 };
    bcm_ip_t dst_ip_addr = 0;
    uint32 zero_padding[3] = { 0x0 };
    uint32 my_disc = 0;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    my_disc = dnx_data_bfd.general.bfd_over_php_oam_tcam_oam_offset_get(unit);

    /** If Layer-Type[Fwd] is IPv4 and (DIP==127/8) and Next-Protocol is UDP and UDP destination port == 3784 then mark as BFD*/
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_TCAM_IDENTIFICATION_DB, &entry_handle_id));
    if (is_set)
    {
        SHR_IF_ERR_EXIT(dbal_entry_attribute_set(unit, entry_handle_id, DBAL_ENTRY_ATTR_PRIORITY, 3));
    }
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_IN_LIF_PROFILE, 0x0, 0x0);
    dbal_entry_key_field32_masked_set(unit, entry_handle_id, DBAL_FIELD_NOF_VALID_OAM_LIFS, 0x0, 0x0);
    /** Qualify DIP and UDP port*/
    dst_ip_addr = 0x7f000000;

    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPE_CURRENT_LAYER_MINUS_1,
                               DBAL_ENUM_FVAL_LAYER_TYPES_ETHERNET);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_LAYER_TYPE_CURRENT_LAYER,
                               DBAL_ENUM_FVAL_LAYER_TYPES_IPV4);
    /** 300 bits starts from Ver of IP header to your-disc BFD(MSB 12bits) */

    /** match ttl=1 (bit 228-235) and IP protocal=0x11 (bit 220-227)*/
    pkt_data[7] = 0x11;
    pkt_data_mask[7] = 0xfff;
    pkt_data[6] = 0x1 << 28;
    pkt_data_mask[6] = 0xf << 28;

    /** do not match ipv4 checksum(bit 204-219)*/
    /** do not match src ip(bit 172-203)*/
    /** match DIP of packet (bit 140-171)*/

    pkt_data[5] = dst_ip_addr >> 20;
    pkt_data_mask[5] = 0xff0;
    pkt_data[4] = dst_ip_addr << 12;
    pkt_data_mask[4] = 0;

    /** do not match udp src port (bit 124-139)*/
    /** udp dst port= 3784  (bit 108-123)*/
    pkt_data[3] = 3784 << 12;
    pkt_data_mask[3] = 0xFFFF000;

    /** do not match UDP length,BFD control header,and my-disc,your-disc (bit 0-107)*/
    dbal_entry_key_field_arr32_masked_set(unit, entry_handle_id, DBAL_FIELD_PKT_DATA_AT_FWD_HEADER, pkt_data,
                                          pkt_data_mask);

    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_PACKET_IS_OAM, INST_SINGLE, 0x1);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_MD_LEVEL, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_OPCODE, INST_SINGLE, 0xf);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_OFFSET, INST_SINGLE, my_disc);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_STAMP_OFFSET, INST_SINGLE, 0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_PCP, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_MY_CFM_MAC, INST_SINGLE, 0x0);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_LIF_TCAM_INSTRUCTION, INST_SINGLE, 0);
    /** MARK it to BFD*/
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_IS_BFD, INST_SINGLE, 0x1);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_YOUR_DISCR, INST_SINGLE, 0x1);
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_TCAM_RESULT_TYPE, INST_SINGLE, 0x0);
    dbal_entry_value_field_arr32_set(unit, entry_handle_id, DBAL_FIELD_ZERO_PADDING_TCAM_IDENT, INST_SINGLE,
                                     zero_padding);
    if (is_set)
    {
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }
    else
    {
        SHR_IF_ERR_EXIT(dbal_entry_access_id_by_key_get(unit, entry_handle_id, &entry_access_id, DBAL_COMMIT));
        SHR_IF_ERR_EXIT(dbal_entry_handle_access_id_set(unit, entry_handle_id, entry_access_id));
        SHR_IF_ERR_EXIT(dbal_entry_clear(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}
/**
* \brief
*  Set an OAM Control entry. This function is not supported.
* \param [in] unit  -
*   Relevant unit.
* \param [in] type  -
*   Type of Control being used
* \param [in] arg -
*   Argument, containing information about the Control entry.
* \retval
*   shr_error_unavail - Return unavailable.
* \remark
*   * None
* \see
*   * \ref bcm_dnx_oam_control_get
*/
shr_error_e
bcm_dnx_oam_control_set(
    int unit,
    bcm_oam_control_type_t type,
    uint64 arg)
{
    uint32 counter_range_min;
    uint32 counter_range_max;
    uint32 arbiter_weight_value;
    uint64 MAX_RANGE, counter_range_min_u64, counter_range_max_u64;
    uint32 DP_MASK, TC_MASK;
    uint32 dp, tc;
    shr_error_e rv;
    int bfd_php_tcam_enable;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    switch (type)
    {
            /*
             * Set lower boundary of counter range for non PCP counters
             */
        case bcmOamControlLmPcpCounterRangeMin:
        {
            /*
             * Get current counter range values Ingress and Egress will always have the same range, so we check for
             * validity for ingress only.
             */
            rv = dnx_oam_counter_global_range_get(unit, DNX_OAM_CLASSIFIER_INGRESS, &counter_range_min,
                                                  &counter_range_max);
            SHR_IF_ERR_EXIT(rv);

          /** Validity check for ingress */
            COMPILER_64_SET(counter_range_max_u64, 0, counter_range_max);
            if (COMPILER_64_GT(arg, counter_range_max_u64))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "llegal LM counter range min value. Must be below counter range max.\n");
            }

          /** Set the new ingress counter range value */
            rv = dnx_oam_counter_global_range_set(unit, DNX_OAM_CLASSIFIER_INGRESS, COMPILER_64_LO(arg),
                                                  counter_range_max);
            SHR_IF_ERR_EXIT(rv);

          /** Set the new egress counter range value */
            rv = dnx_oam_counter_global_range_set(unit, DNX_OAM_CLASSIFIER_EGRESS, COMPILER_64_LO(arg),
                                                  counter_range_max);
            SHR_IF_ERR_EXIT(rv);

        }
            break;
            /*
             * Set upper boundary of counter range for non PCP counters
             */
        case bcmOamControlLmPcpCounterRangeMax:
        {
            /*
             * Validity check - counter index must not be above DNX_MAX_COUNTER_RANGE
             */
            COMPILER_64_SET(MAX_RANGE, 0, DNX_MAX_COUNTER_RANGE);
            if (COMPILER_64_GT(arg, MAX_RANGE))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "llegal LM counter range max value\n");
            }

            /*
             * Get current counter range values Ingress and Egress will always have the same range, so we check for
             * validity for ingress only.
             */
            rv = dnx_oam_counter_global_range_get(unit, DNX_OAM_CLASSIFIER_INGRESS, &counter_range_min,
                                                  &counter_range_max);
            SHR_IF_ERR_EXIT(rv);

            COMPILER_64_SET(counter_range_min_u64, 0, counter_range_min);
            if (COMPILER_64_LT(arg, counter_range_min_u64))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "llegal LM counter range max value. Must be larger counter range min.\n");
            }

            rv = dnx_oam_counter_global_range_set(unit, DNX_OAM_CLASSIFIER_INGRESS, counter_range_min,
                                                  COMPILER_64_LO(arg));
            SHR_IF_ERR_EXIT(rv);

            rv = dnx_oam_counter_global_range_set(unit, DNX_OAM_CLASSIFIER_EGRESS, counter_range_min,
                                                  COMPILER_64_LO(arg));
            SHR_IF_ERR_EXIT(rv);
        }
            break;
        case bcmOamControlOampPuntPacketIntPri:
        {
            /*
             * Bits [1:0] of given value determine the color (DP), bits [4:2] determine the Traffic Class
             */
            COMPILER_64_SET(MAX_RANGE, 0, 0x001F);
            if (COMPILER_64_GT(arg, MAX_RANGE))
            {
                SHR_ERR_EXIT(_SHR_E_UNAVAIL, "Illegal DP and TC values\n");
            }
            DP_MASK = 0x0003;
            TC_MASK = 0x001C;
            dp = COMPILER_64_LO(arg) & DP_MASK; /* prepare dp value: (arg &0x3) */
            tc = (COMPILER_64_LO(arg) & TC_MASK) >> 2;  /* prepare tc value: (arg >> 2)&0x7 */
            rv = dnx_oam_cpu_port_dp_tc_set(unit, dp, tc);
            SHR_IF_ERR_EXIT(rv);
        }
            break;
        /**
        * Set TX/RX shift, which will be used in the formula
        * to calculate statistics counter id
        */
        case bcmOamControlOampStatsShift:
        {
            SHR_IF_ERR_EXIT(dnx_oam_tx_rx_shift_counter_cfg_set(unit, COMPILER_64_LO(arg)));
        }
            break;
        case bcmOamControlNativeEthernetOverPweClassification:
        {
            SHR_IF_ERR_EXIT(dnx_oam_native_eth_over_pwe_classify_mpls_tcam_set(unit, COMPILER_64_LO(arg)));
        }
            break;
        /**
         * Set report mode
         */
        case bcmOamControlReportMode:
        {
            SHR_IF_ERR_EXIT(dnx_oam_report_mode_set(unit, (bcm_oam_report_mode_type_t) COMPILER_64_LO(arg)));
        }
            break;
        case bcmOamControlFlexibleDropPort:
        case bcmOamControlFlexibleDropCVlan:
        case bcmOamControlFlexibleDropSVlan:
        case bcmOamControlFlexibleDropCPlusSVlan:
        case bcmOamControlFlexibleDropVP:
        case bcmOamControlFlexibleDropEgressPort:
        case bcmOamControlFlexibleDropEgressCVlan:
        case bcmOamControlFlexibleDropEgressSVlan:
        case bcmOamControlFlexibleDropEgressCPlusSVlan:
        case bcmOamControlFlexibleDropEgressVP:
        case bcmOamControlFlexibleDropPasssiveSap:
        case bcmOamControlFlexibleDropEgressPasssiveSap:
        case bcmOamControlUnknownAchCount:
        case bcmOamControlNtpToD:
        {
            /*
             * Set NTP TOD value
             */
            rv = dnx_oam_tod_set(unit, 1, arg);
            SHR_IF_ERR_EXIT(rv);

        }
            break;
        case bcmOamControl1588ToD:
        {
            /*
             * Set 1588 TOD value
             */
            rv = dnx_oam_tod_set(unit, 0, arg);
            SHR_IF_ERR_EXIT(rv);

        }
            break;
        case bcmOamControlSrcMacLsbReserve:
        case bcmOamControlSrcMacLsbUnReserve:
        case bcmOamControlOampCCMWeight:
        {
            /*
             * Validity check - priority value must not be above DNX_MAX_ARB_WEIGHT_RANGE
             */
            COMPILER_64_SET(MAX_RANGE, 0, DNX_MAX_ARB_WEIGHT_RANGE);
            if (COMPILER_64_GT(arg, MAX_RANGE))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal CCM weight value \n");
            }
            arbiter_weight_value = COMPILER_64_LO(arg);
            rv = dnx_oam_arp_weight_set(unit, DBAL_FIELD_TXM_ARB_WEIGHT, arbiter_weight_value);
            SHR_IF_ERR_EXIT(rv);
        }
            break;
        case bcmOamControlOampSATWeight:
        {
            /*
             * Validity check - priority value must not be above DNX_MAX_ARB_WEIGHT_RANGE
             */
            COMPILER_64_SET(MAX_RANGE, 0, DNX_MAX_ARB_WEIGHT_RANGE);
            if (COMPILER_64_GT(arg, MAX_RANGE))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal SAT/TST weight value\n");
            }
            arbiter_weight_value = COMPILER_64_LO(arg);
            rv = dnx_oam_arp_weight_set(unit, DBAL_FIELD_SAT_ARB_WEIGHT, arbiter_weight_value);
            SHR_IF_ERR_EXIT(rv);
        }
            break;
        case bcmOamControlOampResponseWeight:
        {
            /*
             * Validity check - priority value must not be above DNX_MAX_ARB_WEIGHT_RANGE
             */
            COMPILER_64_SET(MAX_RANGE, 0, DNX_MAX_ARB_WEIGHT_RANGE);
            if (COMPILER_64_GT(arg, MAX_RANGE))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal RSP weight value\n");
            }
            arbiter_weight_value = COMPILER_64_LO(arg);
            rv = dnx_oam_arp_weight_set(unit, DBAL_FIELD_RSP_ARB_WEIGHT, arbiter_weight_value);
            SHR_IF_ERR_EXIT(rv);
        }
            break;
        case bcmOamControlEnableNextReceivedSlr:
        {
            SHR_IF_ERR_EXIT(dnx_oam_enable_next_received_slr_set(unit, COMPILER_64_LO(arg)));
        }
            break;
        case bcmOamControlMplsOamMdlIgnore:
        {
            SHR_IF_ERR_EXIT(dnx_oam_mpls_tp_mdl_ignore_set(unit, COMPILER_64_LO(arg)));
        }
            break;
        case bcmOamControlEthDmacMdlMatchCheck:
        {
            if (dnx_data_oam.general.feature_get(unit, dnx_data_oam_general_oam_dmac_mdl_match_check_control_support) ==
                1)
            {
                SHR_IF_ERR_EXIT(dnx_oam_eth_dmac_mdl_match_check_set(unit, COMPILER_64_LO(arg)));
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "Not supported bcm oam control type");
            }
        }
            break;
        case bcmOamControlMplsLmQueryControlCode:
        {
            /*
             * Validity check - counter index must not be above DNX_MAX_CONTROL_CODE_QUERY_RANGE
             */
            COMPILER_64_SET(MAX_RANGE, 0, DNX_MAX_CONTROL_CODE_QUERY_RANGE);
            if (COMPILER_64_GT(arg, MAX_RANGE))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "llegal control code value! Allowed range is 0 - 2 \n");
            }
            SHR_IF_ERR_EXIT(dnx_oam_rfc_6374_control_code_set
                            (unit, 1 /** LM */ , 0 /** Query */ , COMPILER_64_LO(arg)));
        }
            break;
        case bcmOamControlMplsLmResponderControlCode:
        {
            /*
             * Validity check - counter index must not be above DNX_MAX_CONTROL_CODE_RESPONSE_RANGE
             */
            COMPILER_64_SET(MAX_RANGE, 0, DNX_MAX_CONTROL_CODE_RESPONSE_RANGE);
            if (COMPILER_64_GT(arg, MAX_RANGE))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "llegal control code value! Allowed range is 0 - 29 \n");
            }
            SHR_IF_ERR_EXIT(dnx_oam_rfc_6374_control_code_set
                            (unit, 1 /** LM */ , 1 /** Response */ , COMPILER_64_LO(arg)));
        }
            break;
        case bcmOamControlMplsDmQueryControlCode:
        {
            /*
             * Validity check - counter index must not be above DNX_MAX_CONTROL_CODE_QUERY_RANGE
             */
            COMPILER_64_SET(MAX_RANGE, 0, DNX_MAX_CONTROL_CODE_QUERY_RANGE);
            if (COMPILER_64_GT(arg, MAX_RANGE))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "llegal control code value! Allowed range is 0 - 2 \n");
            }
            SHR_IF_ERR_EXIT(dnx_oam_rfc_6374_control_code_set
                            (unit, 0 /** DM */ , 0 /** Query */ , COMPILER_64_LO(arg)));
        }
            break;
        case bcmOamControlMplsDmResponderControlCode:
        {
            /*
             * Validity check - counter index must not be above DNX_MAX_CONTROL_CODE_RESPONSE_RANGE
             */
            COMPILER_64_SET(MAX_RANGE, 0, DNX_MAX_CONTROL_CODE_RESPONSE_RANGE);
            if (COMPILER_64_GT(arg, MAX_RANGE))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "llegal control code value! Allowed range is 0 - 29 \n");
            }
            SHR_IF_ERR_EXIT(dnx_oam_rfc_6374_control_code_set
                            (unit, 0 /** DM */ , 1 /** Response */ , COMPILER_64_LO(arg)));
        }
            break;
        case bcmOamControlEnableBfdPhp:
        {
            bfd_php_tcam_enable =
                dnx_data_bfd.general.feature_get(unit, dnx_data_bfd_general_bfd_over_php_tcam_support);
            if (bfd_php_tcam_enable == 0)
            {
                SHR_ERR_EXIT(_SHR_E_CONFIG,
                             "BFD over PHP is supported naturally on the device and no additional config!\n");
            }
            SHR_IF_ERR_EXIT(dnx_bfd_php_tcam_entry_set(unit, COMPILER_64_LO(arg)));
        }
            break;
        case bcmOamControlIngressVlanEditClassDeleteOneVlanTag:
        {
            if (dnx_data_oam.oamp.feature_get(unit, dnx_data_oam_oamp_oamp_v2) == 0)
            {
                SHR_IF_ERR_EXIT(dnx_oam_oamp_v1_down_egress_inject_delete_one_vlan_ive_command_set
                                (unit, COMPILER_64_LO(arg)));
            }
        }
            break;
        case bcmOamControlIngressVlanEditClassDeleteTwoVlanTags:
        {
            if (dnx_data_oam.oamp.feature_get(unit, dnx_data_oam_oamp_oamp_v2) == 0)
            {
                SHR_IF_ERR_EXIT(dnx_oam_oamp_v1_down_egress_inject_delete_two_vlan_ive_command_set
                                (unit, COMPILER_64_LO(arg)));
            }
        }
            break;
        case bcmOamControlOampInjectedNetworkQos:
        {
            SHR_IF_ERR_EXIT(dnx_oam_oamp_tx_pph_network_qos_set(unit, COMPILER_64_LO(arg)));
        }
            break;

        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "Not supported bcm oam control type");
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Enable registration of OAM events.
* \par DIRECT INPUT:
*   \param [in] unit  -
*   Relevant unit.
*   \param [in] event_types -
*   Enable registration of these event_types
*   \param [in] cb -
*   Call back for the oam events.
*   \param [in] user_data -
*   Pointer to user data which will be returned when
*   callback is invoked
* \par INDIRECT INPUT:
*   * none
* \par DIRECT OUTPUT:
*   shr_error_param - invalid event_type
*   shr_error_exists - event already registered
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * Warmboot is not supported. Application has to
*   * re-register events after warmboot.
* \see
*   * \ref bcm_dnx_oam_event_register
*/
shr_error_e
bcm_dnx_oam_event_register(
    int unit,
    bcm_oam_event_types_t event_types,
    bcm_oam_event_cb cb,
    void *user_data)
{
    bcm_oam_event_type_t event_i;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    if (!(DNX_OAM_EVENT_TYPE_VERIFY(event_types)))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Event type not supported");
    }

    for (event_i = 0; event_i < bcmOAMEventCount; event_i++)
    {
        if (BCM_OAM_EVENT_TYPE_GET(event_types, event_i))
        {
            if (_g_oam_event_cb[unit][event_i] && (_g_oam_event_cb[unit][event_i] != cb))
            {
                /*
                 * A different callback is already registered for this event. Return error
                 */
                SHR_ERR_EXIT(_SHR_E_EXISTS, "EVENT %d already has a registered callback ", event_i);
            }
            _g_oam_event_cb[unit][event_i] = cb;
            _g_oam_event_ud[unit][event_i] = user_data;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Disable registration of OAM events.
* \par DIRECT INPUT:
*   \param [in] unit  -
*   Relevant unit.
*   \param [in] event_types -
*   Disable registration of these event_types
*   \param [in] cb -
*   Call back for the oam events.
* \par INDIRECT INPUT:
*   * none
* \par DIRECT OUTPUT:
*   shr_error_unavail - Return unavailable.
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * \ref bcm_dnx_oam_event_unregister
*/
shr_error_e
bcm_dnx_oam_event_unregister(
    int unit,
    bcm_oam_event_types_t event_types,
    bcm_oam_event_cb cb)
{
    bcm_oam_event_type_t event_i;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    for (event_i = 0; event_i < bcmOAMEventCount; event_i++)
    {
        if (BCM_OAM_EVENT_TYPE_GET(event_types, event_i))
        {
            if (_g_oam_event_cb[unit][event_i] && (_g_oam_event_cb[unit][event_i] != cb))
            {
                /*
                 * A different calblack is registered for this event. Return error
                 */
                SHR_ERR_EXIT(_SHR_E_EXISTS, "A different callback is registered for %d ", event_i);
            }
            _g_oam_event_cb[unit][event_i] = NULL;
            _g_oam_event_ud[unit][event_i] = NULL;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 *  \brief
 *   get the field from channel type table
 *  \param [in] unit  -
 *    Number of hardware unit used..
 *  \param [in] index  -
 *    Index in channel type table. range according to channel
 *    type table size
 *  \param [in] field_type  -
 *    field to retrieve from table. acceptablr values:
 *    DBAL_FIELD_CHANNEL_TYPE, DBAL_FIELD_FORMAT_TYPE &
 *    DBAL_FIELD_VALID
 *  \param [out] field_val-
 *    The field value we get from entry in channel type table.
 *  \return
 *   \retval Zero if no error was detected
 *   \retval Negative if error was detected. See \ref
 *           shr_error_e
 *  \remark
 *    None
 *  \see
 *
 */
static shr_error_e
dnx_oam_channel_type_rx_get_field(
    int unit,
    int index,
    dbal_fields_e field_type,
    uint32 *field_val)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(field_val, _SHR_E_PARAM, "field val");

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_CHANNEL_TYPE, &entry_handle_id));

    /** Setting key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INDEX, index);

    /** Setting pointers value to receive the fields */
    dbal_value_field32_request(unit, entry_handle_id, field_type, INST_SINGLE, field_val);

    /** Preforming the action after this call the pointers that we set in field32_request() */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 *  \brief
 *   get the field from channel type table
 *  \param [in] unit  -
 *    Number of hardware unit used..
 *  \param [in] index  -
 *    Index in channel type table. range according to channel
 *    type table size
 *  \param [out] channel_type-
 *    The channel_type value we get from entry in channel type
 *    table.
 *  \param [out] format_type-
 *    The format_type value we get from entry in channel type
 *    table.
 *  \param [out] packet_is_oam -
 *  The packet-is-oam value we get
 *    from entry in channel type table.
 *  \param [out] valid-
 *    The valid value we get from entry in channel type table.
 *  \return
 *   \retval Zero if no error was detected
 *   \retval Negative if error was detected. See \ref
 *           shr_error_e
 *  \remark
 *    None
 *  \see
 *
 */
static shr_error_e
dnx_oam_channel_type_rx_get_all_fields(
    int unit,
    int index,
    uint32 *channel_type,
    uint32 *format_type,
    uint32 *packet_is_oam,
    uint32 *valid)
{
    uint32 entry_handle_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(channel_type, _SHR_E_PARAM, "channel type");
    SHR_NULL_CHECK(format_type, _SHR_E_PARAM, "format type");
    SHR_NULL_CHECK(valid, _SHR_E_PARAM, "valid");

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_CHANNEL_TYPE, &entry_handle_id));

    /** Setting key fields */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INDEX, index);

    /** Setting pointers value to receive the fields */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_GET_ALL_FIELDS));

    /** Preforming the action after this call the pointers that we set in field32_request() */
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                    (unit, entry_handle_id, DBAL_FIELD_CHANNEL_TYPE, INST_SINGLE, channel_type));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                    (unit, entry_handle_id, DBAL_FIELD_FORMAT_TYPE, INST_SINGLE, format_type));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get
                    (unit, entry_handle_id, DBAL_FIELD_CHANNEL_TYPE_PACKET_IS_OAM, INST_SINGLE, packet_is_oam));
    SHR_IF_ERR_EXIT(dbal_entry_handle_value_field32_get(unit, entry_handle_id, DBAL_FIELD_VALID, INST_SINGLE, valid));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   get a list of custom channel types in  channel_type for
 *   a given OAM Format type. This function gets the RX side.
 * \param [in] unit  -
 *   Number of hardware unit used..
 * \param [in] expected_format_type  -
 *   OAM format type configured for all values.
 * \param [in] num_values -
 *    Number of values present in list_of_values_array.
 * \param [out] list_of_values -
 *    List of custom valus that will contain the channel type
 *    returned from function
 * \param [out] value_count -
 *    Pointer to the number of existing values. meaning the
 *    actaul number of values we have in channel_type table
 * \return
 *   \retval Zero if no error was detected
 *   \retval Negative if error was detected. See \ref
 *           shr_error_e
 * \remark
 *   * None
 * \see
 *
 */
static shr_error_e
dnx_oam_channel_type_rx_get_table(
    int unit,
    dbal_enum_value_field_oam_format_type_e expected_format_type,
    int num_values,
    int *list_of_values,
    int *value_count)
{
    uint32 channel_type_table_index, occupied_entry, entry_format_type;
    int val_index = 0, number_of_entries = 0;
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(list_of_values, _SHR_E_PARAM, "list of values");
    SHR_NULL_CHECK(value_count, _SHR_E_PARAM, "value count");

    SHR_IF_ERR_EXIT(dbal_tables_capacity_get(unit, DBAL_TABLE_OAM_CHANNEL_TYPE, &number_of_entries));

    for (channel_type_table_index = 0; channel_type_table_index < number_of_entries; channel_type_table_index++)
    {
        occupied_entry = 0;
        /** Break if we have exhausted the list of values */
        if (val_index >= num_values)
        {
            break;
        }
        SHR_IF_ERR_EXIT(dnx_oam_channel_type_rx_get_field
                        (unit, channel_type_table_index, DBAL_FIELD_VALID, &occupied_entry));
        /*
         * This means the entry is occupid and we need to check if this is a format for retrieving the channel type
         */
        if (occupied_entry == 1)
        {
            SHR_IF_ERR_EXIT(dnx_oam_channel_type_rx_get_field
                            (unit, channel_type_table_index, DBAL_FIELD_FORMAT_TYPE, &entry_format_type));
            /** format type required for retrieving the channel type */
            if (entry_format_type == expected_format_type)
            {
                SHR_IF_ERR_EXIT(dnx_oam_channel_type_rx_get_field
                                (unit, channel_type_table_index, DBAL_FIELD_CHANNEL_TYPE,
                                 (uint32 *) (&(list_of_values[val_index]))));
                val_index++;
            }
        }
    }
    *value_count = val_index;

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *  get the relavent format type for the mpls tp channel type
 *  input.
 * \param [in] unit  -
 *    Relevant unit.
 * \param [in] channel_type  -
 *    The type of mpls tp channel.
 *    values can be: bcmOamMplsTpChannelPweBfd,
 *    bcmOamMplsTpChannelPweonoam or bcmOamMplsTpChannelY1731
 * \param [out] format_type -
 *    OAM format type that will be used in channel type table .
 *    values can be: DBAL_ENUM_FVAL_OAM_FORMAT_TYPE_Y1731,
 *    DBAL_ENUM_FVAL_OAM_FORMAT_TYPE_BFD_RAW or
 *    DBAL_ENUM_FVAL_OAM_FORMAT_TYPE_RFC_6374
 * \param [out] internal_opcode -
 *    OAM internal opcode related to the channel type. Relevant for
 *    RFC6473 only.
 * \param [out] oam_stamp_offset -
 *    Offset for stamping OAM LM/DM OAM values
 * \return
 *   \retval Zero if no error was detected
 *   \retval Negative if error was detected. See \ref
 *           shr_error_e
 * \remark
 *     bcmOamMplsTpChannelPweonoam and
 *     bcmOamMplsTpChannelY1731 map to same format type
 * \see
 */
static shr_error_e
dnx_oam_mpls_tp_channel_type_to_format(
    int unit,
    bcm_oam_mpls_tp_channel_type_t channel_type,
    dbal_enum_value_field_oam_format_type_e * format_type,
    dbal_enum_value_field_oam_internal_opcode_e * internal_opcode,
    int *oam_stamp_offset)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(format_type, _SHR_E_PARAM, "format type");

    switch (channel_type)
    {
        case bcmOamMplsTpChannelPweonoam:
        case bcmOamMplsTpChannelY1731:
        {
            *format_type = DBAL_ENUM_FVAL_OAM_FORMAT_TYPE_Y1731;
            /*
             * Default Values
             */
            *internal_opcode = 0;
            *oam_stamp_offset = 0;
            break;
        }
        case bcmOamMplsTpChannelPweBfd:
        case bcmOamMplsTpChannelMplsTpBfd:
        {

            *format_type = DBAL_ENUM_FVAL_OAM_FORMAT_TYPE_BFD_RAW;
            /*
             * Default Values
             */
            *internal_opcode = 0;
            *oam_stamp_offset = 0;
            break;
        }
        case bcmOamMplsTpChannelMplsDirectLm:
        {

            *format_type = DBAL_ENUM_FVAL_OAM_FORMAT_TYPE_RFC_6374;
            *internal_opcode = DBAL_ENUM_FVAL_OAM_INTERNAL_OPCODE_ETH_LMM;
            *oam_stamp_offset = 0;
            break;
        }
        case bcmOamMplsTpChannelMplsDm:
        {

            *format_type = DBAL_ENUM_FVAL_OAM_FORMAT_TYPE_RFC_6374;
            *internal_opcode = DBAL_ENUM_FVAL_OAM_INTERNAL_OPCODE_ETH_DMM;
            *oam_stamp_offset = 0;
            break;
        }
        default:
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "Error: Unknown channel type, supported channel types  are: "
                         "bcmOamMplsTpChannelPweonoam, bcmOamMplsTpChannelY1731, bcmOamMplsTpChannelPweBfd, "
                         "and bcmOamMplsTpChannelMplsTpBfd \n");
            break;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   get a list of custom channel types in  channel_type for a
 *   given OAM Format type. This function sets the RX side.
 * \param [in] unit  -
 *    Relevant unit.
 * \param [in] channel_type  -
 *   Type of the mpls tp channel.
 * \param [in] num_values -
 *   Number of values to get with the Get procedure.
 * \param [out] list_of_values -
 *   Pointer to a list in which to
 *   write the information from the Get procedure
 *  \param [out] value_count -
 *    Pointer to the number of existing values
 * \return
 *   \retval Zero if no error was detected
 *   \retval Negative if error was detected. See \ref
 *           shr_error_e
 * \remark
 *     bcmOamMplsTpChannelPweonoam and bcmOamMplsTpChannelY1731
 *     map to same format type and thereofre the get function
 *     will return custom channel types for both
 *     bcm_oam_mpls_tp_channel_type fields
 * \see
 *  *  bcm_dnx_oam_mpls_tp_channel_type_rx_set
 *  *  bcm_dnx_oam_mpls_tp_channel_type_tx_get
 *  *  bcm_dnx_oam_mpls_tp_channel_type_tx_set
 */
shr_error_e
bcm_dnx_oam_mpls_tp_channel_type_rx_get(
    int unit,
    bcm_oam_mpls_tp_channel_type_t channel_type,
    int num_values,
    int *list_of_values,
    int *value_count)
{
    dbal_enum_value_field_oam_format_type_e format_type;
    dbal_enum_value_field_oam_internal_opcode_e internal_opcode;
    int oam_stamp_offset;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    /** Get format type accrding to channel type */
    SHR_IF_ERR_EXIT(dnx_oam_mpls_tp_channel_type_to_format
                    (unit, channel_type, &format_type, &internal_opcode, &oam_stamp_offset));
    /** Get custom channel types values for given  format type */
    SHR_IF_ERR_EXIT(dnx_oam_channel_type_rx_get_table(unit, format_type, num_values, list_of_values, value_count));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Get an entry from pemla_oam table channel type index
 * \param [in] unit  -
 *   Number of hardware unit used..
 * \param [in] channel_type_table_index  -
 *   index in channel type table.
 * \param [out] channel_type -
 *   the custom channel type value that should be added to entry
 * \param [out] layer_protocol -
 *   the layer protocol associated to the channel_type
 * \return
 *   \retval Zero if no error was detected
 *   \retval Negative if error was detected. See \ref
 *           shr_error_e
 *   * None
 * \remark
 *   None
 * \see
 *
 */
static shr_error_e
dnx_oam_pemla_oam_channel_type_get_entry(
    int unit,
    int channel_type_table_index,
    uint32 *channel_type,
    uint32 *layer_protocol)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Taking a handle of PEMLA_OAM table  */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_OAM, &entry_handle_id));

    dbal_value_field32_request(unit, entry_handle_id,
                               DBAL_FIELD_G_ACH_CHANNEL_TYPE_VALUE_INDEX(channel_type_table_index), INST_SINGLE,
                               channel_type);

    dbal_value_field32_request(unit, entry_handle_id,
                               DBAL_FIELD_G_ACH_LAYER_PROTOCOL_VALUE_INDEX(channel_type_table_index), INST_SINGLE,
                               layer_protocol);

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Set an entry in tables with OAM channel type and OAM format
 * \param [in] unit  -
 *   Number of hardware unit used..
 * \param [in] channel_type_table_index  -
 *   index in channel type table.
 * \param [in] format_type -
 *   OAM format type value  that should be added to entry.
 * \param [in] internal_opcode -
 *   OAM internal opcode that should be added to entry
 * \param [in] oam_stamp_offset -
 *   OAM stamp offset that should be added to entry
 * \param [in] channel_type -
 *   the custom channel type value that should be added to entry
 * \param [in] packet_is_oam -
 *   the packet-is-oam value that should be added to entry
 * \param [in] valid -
 *   valid field value that should be added to entry
 * \param [in] pemla_oam_channel_type_index  -
 *   index in pemla_oam table.
 * \return
 *   \retval Zero if no error was detected
 *   \retval Negative if error was detected. See \ref
 *           shr_error_e
 *   * None
 * \remark
 *   None
 * \see
 *
 */
shr_error_e
dnx_oam_channel_type_rx_set_entry(
    int unit,
    int channel_type_table_index,
    dbal_enum_value_field_oam_format_type_e format_type,
    dbal_enum_value_field_oam_internal_opcode_e internal_opcode,
    int oam_stamp_offset,
    int channel_type,
    int packet_is_oam,
    int valid,
    int pemla_oam_channel_type_index)
{
    uint32 entry_handle_id;
    dbal_enum_value_field_layer_types_e layer_type;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Taking a handle of  OAM CHANNEL TYPE table  */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_CHANNEL_TYPE, &entry_handle_id));

    /** Setting key field according to index */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INDEX, channel_type_table_index);

    /** Setting value field  channel_type  */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CHANNEL_TYPE, INST_SINGLE, channel_type);

    /** Setting value field  format_type  */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_FORMAT_TYPE, INST_SINGLE, format_type);

    /** Setting value field  internal_opcode  */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_INTERNAL_OPCODE, INST_SINGLE, internal_opcode);

    /** Setting value field  stamp_offset  */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_OAM_STAMP_OFFSET, INST_SINGLE, oam_stamp_offset);

    /** Setting value field  packet_is_oam */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_CHANNEL_TYPE_PACKET_IS_OAM, INST_SINGLE,
                                 packet_is_oam);

    /** Setting value field  to be VALID  */
    dbal_entry_value_field32_set(unit, entry_handle_id, DBAL_FIELD_VALID, INST_SINGLE, valid);

    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

    if (channel_type != DNX_MPLS_TP_VCCV_BFD_CHANNEL_TYPE_VALUE)
    {
        if (format_type == DBAL_ENUM_FVAL_OAM_FORMAT_TYPE_Y1731)
        {
                /** Taking a handle of PEMLA_OAM table  */
            SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_OAM, &entry_handle_id));
                /** Used to map oam type to channel_type*/

            layer_type = (dnx_init_pp_layer_types_value_get(unit, DBAL_ENUM_FVAL_LAYER_TYPES_Y_1731));

            dbal_entry_value_field32_set(unit, entry_handle_id,
                                         DBAL_FIELD_G_ACH_CHANNEL_TYPE_VALUE_INDEX(pemla_oam_channel_type_index),
                                         INST_SINGLE, channel_type);
            dbal_entry_value_field32_set(unit, entry_handle_id,
                                         DBAL_FIELD_G_ACH_LAYER_PROTOCOL_VALUE_INDEX(pemla_oam_channel_type_index),
                                         INST_SINGLE, layer_type);
                /** Preforming the action */
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

        }
    }
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Set a list of custom channel types in  channel_type for a
 *   given OAM Format type. This function sets the RX side.
 *   function goes through the  entries in table, finds a empty
 *   entry and sets a value from the user in the empty entry.
 *   The user can give a list of values, so function stops going
 *   through the table when all values in the list from user was
 *   set in empty entries or if we went through all the entries
 *   in tables. If there are not enough empty entries in table,
 *   the function will return an error.
 * \param [in] unit  -
 *   Number of hardware unit used..
 * \param [in] format_type  -
 *   OAM format type configured for all values.
 * \param [in] internal_opcode -
 *   OAM internal opcode that should be added to entry
 * \param [in] oam_stamp_offset -
 *   OAM stamp offset that should be added to entry
 * \param [in] num_values -
 *   Number of values present in list_of_values_array.
 * \param [in] list_of_values -
 *   List of custom valus that will be
 *   configured for channel type
 * \return
 *   \retval Zero if no error was detected
 *   \retval Negative if error was detected. See \ref
 *           shr_error_e
 * \remark
 *   in order not to reduce performance there is no check if
 *   entry already exists in HW, Meaning if user tries to set the
 *   same entry twice, it will occupy  2 entries
 * \see
 *
 */
static shr_error_e
dnx_oam_channel_type_rx_set_table(
    int unit,
    dbal_enum_value_field_oam_format_type_e format_type,
    dbal_enum_value_field_oam_internal_opcode_e internal_opcode,
    int oam_stamp_offset,
    int num_values,
    int *list_of_values)
{
    uint32 channel_type_table_index, occupied_entry, channel_type_entry;
    int val_index = 0, number_of_entries = 0;
    uint8 packet_is_oam = 1;
    int pemla_oam_channel_type_index = 0;
    int table_roam_cfg = 0;

    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(list_of_values, _SHR_E_PARAM, "list of values");

    /*
     * Look for free entry in OAM_CHANNEL_TYPE table 
     */
    SHR_IF_ERR_EXIT(dbal_tables_capacity_get(unit, DBAL_TABLE_OAM_CHANNEL_TYPE, &number_of_entries));

    for (channel_type_table_index = 0; channel_type_table_index < number_of_entries; channel_type_table_index++)
    {
        occupied_entry = 0;
        /*
         * Break if we have exhausted the list of values, meaning we set all input values
         */
        if (val_index >= num_values)
        {
            break;
        }
        SHR_IF_ERR_EXIT(dnx_oam_channel_type_rx_get_field
                        (unit, channel_type_table_index, DBAL_FIELD_VALID, &occupied_entry));
        /*
         * This means the entry is free and we can set a new entry, there is no check if entry already exists in HW,
         * Meaning if user tries to set the same entry twice, it will occupy 2 entries
         */
        if (occupied_entry == 0)
        {
            table_roam_cfg = dnx_data_oam.general.oam_nof_pemla_channel_types_get(unit);

            /*
             * Look for free entry in PEMLA_OAM table 
             */
            for (pemla_oam_channel_type_index = 0; pemla_oam_channel_type_index < table_roam_cfg;
                 pemla_oam_channel_type_index++)
            {
                SHR_IF_ERR_EXIT(dnx_oam_pemla_oam_channel_type_get_entry
                                (unit, pemla_oam_channel_type_index, &channel_type_entry, &occupied_entry));
                if (occupied_entry == 0)
                {
                    break;
                }
            }
            /*
             * if pamle_oam table is full and it's a Y1731 type, no entry will be added in the channel type tables 
             */
            if ((pemla_oam_channel_type_index < table_roam_cfg)
                || (format_type != DBAL_ENUM_FVAL_OAM_FORMAT_TYPE_Y1731))
            {
                SHR_IF_ERR_EXIT(dnx_oam_channel_type_rx_set_entry
                                (unit, channel_type_table_index, format_type, internal_opcode, oam_stamp_offset,
                                 list_of_values[val_index], packet_is_oam, 1, pemla_oam_channel_type_index));
                val_index++;
            }
        }
    }
    /** Did not write the all the values to table  */
    if (val_index < num_values)
    {
        SHR_ERR_EXIT(_SHR_E_RESOURCE,
                     "Not enough free entries. Number of values written, %d. Number of entries that should have been written: %d",
                     val_index, num_values);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Set a list of custom channel types for MPLS-TP channel types
 *   This function sets the RX side.
 * \param [in] unit  -
 *   Number of hardware unit used..
 * \param [in] channel_type  -
 *   Type of the mpls tp channel.
 * \param [in] num_values -
 *   Number of values present in list_of_values_array.
 * \param [in] list_of_values -
 *   List of custom valus that will
 *   be configured for channel type
 * \return
 *   \retval Zero if no error was detected
 *   \retval Negative if error was detected. See \ref
 *           shr_error_e
 * \remark
 *   * None
 * \see
 *   * bcm_dnx_oam_mpls_tp_channel_type_rx_get
 *   * bcm_dnx_oam_mpls_tp_channel_type_tx_get
 *   * bcm_dnx_oam_mpls_tp_channel_type_tx_set
 */
shr_error_e
bcm_dnx_oam_mpls_tp_channel_type_rx_set(
    int unit,
    bcm_oam_mpls_tp_channel_type_t channel_type,
    int num_values,
    int *list_of_values)
{
    dbal_enum_value_field_oam_format_type_e format_type;
    dbal_enum_value_field_oam_internal_opcode_e internal_opcode;
    int oam_stamp_offset;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    /** Get format type and opcode according to channel type */
    SHR_IF_ERR_EXIT(dnx_oam_mpls_tp_channel_type_to_format
                    (unit, channel_type, &format_type, &internal_opcode, &oam_stamp_offset));
    /** set custom channel types and format with values in list */
    SHR_IF_ERR_EXIT(dnx_oam_channel_type_rx_set_table
                    (unit, format_type, internal_opcode, oam_stamp_offset, num_values, list_of_values));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Clear entry from oam channel type,
 *   channel_type_table_index input. function will return Zero
 *   if no error was detected, Negative if error was detected.
 * \param [in] unit  -
 *   Number of hardware unit used..
 * \param [in] channel_type_table_index  -
 *   index in channel type table.
 */
static shr_error_e
dnx_oam_mpls_tp_channel_type_rx_clear_oam_channel_type_entry(
    int unit,
    int channel_type_table_index)
{
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Taking a handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_OAM_CHANNEL_TYPE, &entry_handle_id));

    /** Setting key fields according to index */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_INDEX, channel_type_table_index);

    /** clearing the entry */
    SHR_IF_ERR_EXIT(dbal_entry_clear(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Clear two field entry from pemla_oam
 *   table, meaning set all fields in table to be
 *   zero
 * \param [in] unit  -
 *   Number of hardware unit used..
 * \param [in] channel_type_table_index  -
 *   index in pemla_oam table.
 */
static shr_error_e
dnx_oam_mpls_tp_channel_type_rx_clear_pemla_oam_entry(
    int unit,
    int channel_type_table_index)
{
    uint32 entry_handle_id, channel_type = 0, format_type = 0;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

   /** Taking a handle of PEMLA_OAM table  */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_PEMLA_OAM, &entry_handle_id));

    /** Set Channel_type and layer_protocol values to zero*/
    dbal_entry_value_field32_set(unit, entry_handle_id,
                                 DBAL_FIELD_G_ACH_CHANNEL_TYPE_VALUE_INDEX(channel_type_table_index), INST_SINGLE,
                                 channel_type);
    dbal_entry_value_field32_set(unit, entry_handle_id,
                                 DBAL_FIELD_G_ACH_LAYER_PROTOCOL_VALUE_INDEX(channel_type_table_index), INST_SINGLE,
                                 format_type);
    /** Preforming the action */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   delete a list of custom channel types in  channel_type for
 *   a given OAM Format type. This function sets the RX side.
 * \param [in] unit  -
 *   Number of hardware unit used..
 * \param [in] format_type  -
 *   OAM format type configured for all values.
 * \param [in] num_values -
 *   Number of values present in list_of_values_array.
 * \param [in] list_of_values -
 *   List of custom valus that will be
 *   configured for channel type
 * \return
 *   \retval Zero if no error was detected
 *   \retval Negative if error was detected. See \ref
 *           shr_error_e
 * \remark
 *   * None
 * \see
 */
static shr_error_e
dnx_oam_channel_type_rx_delete_table(
    int unit,
    dbal_enum_value_field_oam_format_type_e format_type,
    int num_values,
    int *list_of_values)
{
    uint32 channel_type_table_index, occupied_entry, entry_format_type, entry_channel_type, packet_is_oam;
    uint32 layer_type;
    int val_index, match = 0, number_of_entries = 0;
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(list_of_values, _SHR_E_PARAM, "list of values");

    /*
     * nested loop because For each value in list, need to find a value in table first loop going through the list
     */
    for (val_index = 0; val_index < num_values; val_index++)
    {
        match = 0;

        SHR_IF_ERR_EXIT(dbal_tables_capacity_get(unit, DBAL_TABLE_OAM_CHANNEL_TYPE, &number_of_entries));
        /** second loop going through the oam_channel_type table */
        for (channel_type_table_index = 0; channel_type_table_index < number_of_entries; channel_type_table_index++)
        {
            occupied_entry = 0;
            SHR_IF_ERR_EXIT(dnx_oam_channel_type_rx_get_all_fields
                            (unit, channel_type_table_index, &entry_channel_type, &entry_format_type, &packet_is_oam,
                             &occupied_entry));
            /*
             * This means the entry is occupied and we need to check if entry should be deleted
             */
            if (occupied_entry == 1)
            {
                /** format type & channel type are equal to types  to delete */
                if (entry_format_type == format_type && entry_channel_type == list_of_values[val_index])
                {
                    /** delete entry, meaning set all fields to be zero */
                    SHR_IF_ERR_EXIT(dnx_oam_mpls_tp_channel_type_rx_clear_oam_channel_type_entry
                                    (unit, channel_type_table_index));

                    /*
                     * Clean pemla_oam entry 
                     */
                    if (format_type == DBAL_ENUM_FVAL_OAM_FORMAT_TYPE_Y1731)
                    {
                        number_of_entries = dnx_data_oam.general.oam_nof_pemla_channel_types_get(unit);

                        /*
                         * Find pemla_oam entry 
                         */
                        for (channel_type_table_index = 0; channel_type_table_index < number_of_entries;
                             channel_type_table_index++)
                        {
                            SHR_IF_ERR_EXIT(dnx_oam_pemla_oam_channel_type_get_entry
                                            (unit, channel_type_table_index, &entry_channel_type, &layer_type));
                            /*
                             * This means the entry is occupied and we need to check if entry should be deleted
                             */
                            if (entry_channel_type != 0)
                            {
                                /** format type & channel type are equal to types  to delete */
                                if (entry_channel_type == list_of_values[val_index])
                                {
                                    /** delete entry, meaning set all fields to be zero */
                                    SHR_IF_ERR_EXIT(dnx_oam_mpls_tp_channel_type_rx_clear_pemla_oam_entry
                                                    (unit, channel_type_table_index));

                                    break;
                                }
                            }
                        }
                    }
                    match = 1;
                    break;
                }
            }
        }

        /*
         * In case one of the list values is not found the API will remove all entires till the error of no match
         */
        if (match == 0)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "OAM channel type = %d to delete does not exist in HW , number of values deleted %d",
                         list_of_values[val_index], val_index);
        }
    }
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *  Delete mpls tp channel types according to vlaues in list - rx
 *  side.
 * \param [in] unit  -
 *   Relevant unit.
 * \param [in] channel_type  -
 *   Type of the mpls tp channel.
 * \param [in] num_values -
 *   Number of values to delete.
 * \param [in] list_of_values -
 *    Pointer to a list with valus to delete
 * \return
 *   \retval Zero if no error was detected
 *   \retval Negative if error was detected. See \ref
 *           shr_error_e
 * \remark
 *   * None
 * \see
 *   * bcm_dnx_oam_mpls_tp_channel_type_rx_get
 *   * bcm_dnx_oam_mpls_tp_channel_type_tx_get
 *   * bcm_dnx_oam_mpls_tp_channel_type_tx_set
*/
shr_error_e
bcm_dnx_oam_mpls_tp_channel_type_rx_delete(
    int unit,
    bcm_oam_mpls_tp_channel_type_t channel_type,
    int num_values,
    int *list_of_values)
{
    dbal_enum_value_field_oam_format_type_e format_type;
    dbal_enum_value_field_oam_internal_opcode_e internal_opcode;
    int oam_stamp_offset;
    int default_list_of_values[1], list_of_remaining_values[4];
    int num_of_values = 1, num_of_remaining_values;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    /** Get format type according to channel type */
    SHR_IF_ERR_EXIT(dnx_oam_mpls_tp_channel_type_to_format
                    (unit, channel_type, &format_type, &internal_opcode, &oam_stamp_offset));
    /** Delete entries according to channel types in list */
    SHR_IF_ERR_EXIT(dnx_oam_channel_type_rx_delete_table(unit, format_type, num_values, list_of_values));

    /** How many channels are left for this type? */
    SHR_IF_ERR_EXIT(bcm_oam_mpls_tp_channel_type_rx_get
                    (unit, channel_type, 4, list_of_remaining_values, &num_of_remaining_values));

    if ((list_of_values[0] == BFD_PWE_DEFAULT_CHANNEL) ||
        (list_of_values[0] == Y1731_PWE_GACH_DEFAULT_CHANNEL) ||
        (list_of_values[0] == Y1731_MPLS_TP_GACH_DEFAULT_CHANNEL) ||
        (list_of_values[0] == BFD_MPLS_TP_CC_GACH_DEFAULT_CHANNEL) ||
        (list_of_values[0] == RFC_6374_LM_DEFAULT_CHANNEL) || (list_of_values[0] == RFC_6374_DM_DEFAULT_CHANNEL))
    {
        /** If a default value is being intentionally deleted, skip this next part */
        SHR_EXIT();
    }

    if (num_of_remaining_values == 0)
    {
        /** No values left - set default value */

        /** Set to default value */
        switch (channel_type)
        {
            case bcmOamMplsTpChannelPweBfd:
                default_list_of_values[0] = BFD_PWE_DEFAULT_CHANNEL;
                break;

            case bcmOamMplsTpChannelPweonoam:
                default_list_of_values[0] = Y1731_PWE_GACH_DEFAULT_CHANNEL;
                break;

            case bcmOamMplsTpChannelY1731:
                default_list_of_values[0] = Y1731_MPLS_TP_GACH_DEFAULT_CHANNEL;
                break;

            case bcmOamMplsTpChannelMplsTpBfd:
                default_list_of_values[0] = BFD_MPLS_TP_CC_GACH_DEFAULT_CHANNEL;
                break;

            default:
                SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal channel type value %d\n", channel_type);
        }
        SHR_IF_ERR_EXIT(bcm_oam_mpls_tp_channel_type_rx_set(unit, channel_type, num_of_values, default_list_of_values));
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Verify inputs fot OAM opcode map set.
* \par DIRECT INPUT:
*   \param [in] unit  -
*    Relevant unit.
*   \param [in] opcode  -
*    Opcode to read.
*   \param [in] profile -
*    Profile in which to write the information from the set
*    procedure.
* \par INDIRECT INPUT:
*   * none
* \par DIRECT OUTPUT:
*   shr_error_e - Return error in case of illegal inputs.
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * \ref bcm_dnx_oam_opcode_map_set
*/
shr_error_e
dnx_oam_opcode_map_set_verify(
    int unit,
    int opcode,
    int profile)
{
    SHR_FUNC_INIT_VARS(unit);
    if ((opcode > 255) || (opcode < 0))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal OAM opcode");
    }
    if ((profile >= DBAL_NOF_ENUM_OAM_INTERNAL_OPCODE_VALUES) || (profile < 0))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal OAM opcode profile - %d", profile);
    }
exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Verify inputs fot OAM opcode map get.
* \par DIRECT INPUT:
*   \param [in] unit  -
*    Relevant unit.
*   \param [in] opcode  -
*    Opcode to read.
* \par INDIRECT INPUT:
*   * none
* \par DIRECT OUTPUT:
*   shr_error_e - Return error in case of illegal inputs.
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * \ref bcm_dnx_oam_opcode_map_get
*/
shr_error_e
dnx_oam_opcode_map_get_verify(
    int unit,
    int opcode)
{
    SHR_FUNC_INIT_VARS(unit);
    if ((opcode > 255) || (opcode < 0))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal OAM opcode");
    }
exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Get OAM opcode map. This function is not supported.
* \par DIRECT INPUT:
*   \param [in] unit  -
*    Relevant unit.
*   \param [in] opcode  -
*    Opcode to read.
*   \param [out] profile -
*    Profile in which to write the information from the Get
*    procedure.
* \par INDIRECT INPUT:
*   * none
* \par DIRECT OUTPUT:
*   shr_error_unavail - Return unavailable.
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * \ref bcm_dnx_oam_opcode_map_set
*/
shr_error_e
bcm_dnx_oam_opcode_map_get(
    int unit,
    int opcode,
    int *profile)
{
    dbal_enum_value_field_oam_internal_opcode_e internal_opcode;
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    SHR_IF_ERR_EXIT(dnx_oam_opcode_map_get_verify(unit, opcode));

    /*
     * Opcode map is the same for ingress and egress
     */
    SHR_IF_ERR_EXIT(dnx_oam_opcode_map_get(unit, 1, opcode, &internal_opcode));
    *profile = (int) internal_opcode;

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Set OAM opcode map. This function is not supported.
* \par DIRECT INPUT:
*   \param [in] unit  -
*    Relevant unit.
*   \param [in] opcode  -
*    Opcode to read.
*   \param [in] profile -
*    Profile containing the information to set.
* \par INDIRECT INPUT:
*   * none
* \par DIRECT OUTPUT:
*   shr_error_unavail - Return unavailable.
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * \ref bcm_dnx_oam_opcode_map_get
*/
shr_error_e
bcm_dnx_oam_opcode_map_set(
    int unit,
    int opcode,
    int profile)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_START(unit);

    SHR_IF_ERR_EXIT(dnx_oam_opcode_map_set_verify(unit, opcode, profile));

    SHR_IF_ERR_EXIT(dnx_oam_opcode_map_set(unit, opcode, (uint8) profile));

exit:
    DNX_ERR_RECOVERY_END(unit);
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Enable registration of OAM performance events. This function
*  is not supported.
* \par DIRECT INPUT:
*   \param [in] unit  -
*    Relevant unit.
*   \param [in] event_types  -
*    Event types to be enabled.
*   \param [in] cb -
*    Call-back for the oam performance events.
*   \param [in] user_data -
*    Pointer to user data, containing the information from the
*    Get procedure.
* \par INDIRECT INPUT:
*   * none
* \par DIRECT OUTPUT:
*   shr_error_unavail - Return unavailable.
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * \ref bcm_dnx_oam_performance_event_unregister
*/
shr_error_e
bcm_dnx_oam_performance_event_register(
    int unit,
    bcm_oam_event_types_t event_types,
    bcm_oam_performance_event_cb cb,
    void *user_data)
{
    bcm_oam_event_type_t event_i;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    if (!(DNX_OAM_PERFORMANCE_EVENT_TYPE_VERIFY(event_types)))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Event performance type not supported");
    }

    for (event_i = 0; event_i < bcmOAMEventCount; event_i++)
    {
        if (BCM_OAM_EVENT_TYPE_GET(event_types, event_i))
        {
            if (_g_oam_performance_event_cb[unit][event_i] && (_g_oam_performance_event_cb[unit][event_i] != cb))
            {
                /*
                 * A different callback is already registered for this event. Return error
                 */
                SHR_ERR_EXIT(_SHR_E_EXISTS, "EVENT %d already has a registered callback ", event_i);
            }
            _g_oam_performance_event_cb[unit][event_i] = cb;
            _g_oam_event_ud[unit][event_i] = user_data;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
* \brief
*  Disable registration of OAM performance events. This function
*  is not supported.
* \par DIRECT INPUT:
*   \param [in] unit  -
*    Relevant unit.
*   \param [in] event_types  -
*    Event types to be disabled.
*   \param [in] cb -
*    Call-back for the oam performance events.
* \par INDIRECT INPUT:
*   * none
* \par DIRECT OUTPUT:
*   shr_error_unavail - Return unavailable.
* \par INDIRECT OUTPUT:
*   * None
* \remark
*   * None
* \see
*   * \ref bcm_dnx_oam_performance_event_register
*/
shr_error_e
bcm_dnx_oam_performance_event_unregister(
    int unit,
    bcm_oam_event_types_t event_types,
    bcm_oam_performance_event_cb cb)
{

    bcm_oam_event_type_t event_i;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    for (event_i = 0; event_i < bcmOAMEventCount; event_i++)
    {
        if (BCM_OAM_EVENT_TYPE_GET(event_types, event_i))
        {
            if (_g_oam_performance_event_cb[unit][event_i] && (_g_oam_performance_event_cb[unit][event_i] != cb))
            {
                /*
                 * A different calblack is registered for this event. Return error
                 */
                SHR_ERR_EXIT(_SHR_E_EXISTS, "A different callback is registered for %d ", event_i);
            }
            _g_oam_performance_event_cb[unit][event_i] = NULL;
            _g_oam_event_ud[unit][event_i] = NULL;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * Argument verification for dnx_oam_my_cfm_mac_get
 */
static shr_error_e
dnx_my_cfm_mac_get_verify(
    int unit,
    uint32 flags,
    int core_id,
    uint32 port_id,
    bcm_mac_t my_cfm_mac,
    int32 check_mac_unicast)
{
    uint32 legal_flags, number_of_ports;
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(my_cfm_mac, _SHR_E_PARAM, "my_cfm_mac");

    /** Currenly, only one flag is defined */
    legal_flags = DNX_OAM_CLASSIFIER_INGRESS;

    if (flags & ~legal_flags)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Error: flags=0x%08X, only DNX_OAM_CLASSIFIER_INGRESS flag is allowed\n", flags);
    }

    /** Validate core - core all allowed */
    DNXCMN_CORE_VALIDATE(unit, core_id, TRUE);

    /** How many ports does this device have? */
    number_of_ports = dnx_data_port.general.nof_pp_ports_get(unit);

    if (port_id >= number_of_ports)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal value for port_id 0x%08X, must be between 0 and 0x%08X\n",
                     port_id, number_of_ports);
    }

    /** Only unicast mac addresses are relevant */
    if ((check_mac_unicast == TRUE) && !OAM_CLASSIFIER_CHECK_MAC_IS_UNICAST(my_cfm_mac))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal MAC %02X:%02X:%02X:%02X:%02X:%02X; must be unicast\n",
                     SAL_MAC_ADDR_LIST(my_cfm_mac));
    }

exit:
    SHR_FUNC_EXIT;
}

/*
 * Argument verification for dnx_oam_my_cfm_mac_add
 */
static shr_error_e
dnx_my_cfm_mac_verify(
    int unit,
    uint32 flags,
    int core_id,
    uint32 port_id,
    bcm_mac_t my_cfm_mac,
    int32 check_mac_unicast)
{
    int i;
    int rv;

    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_my_cfm_mac_get_verify(unit, flags, core_id, port_id, my_cfm_mac, check_mac_unicast));

   /** mac 00:00:00:00:00:00 is not allowed for my_cfm_mac */
    rv = _SHR_E_PARAM;
    for (i = 0; i < UTILEX_PP_MAC_ADDRESS_NOF_U8; i++)
    {
        if (my_cfm_mac[i] != 0)
        {
            rv = _SHR_E_NONE;
        }
    }
    SHR_IF_ERR_EXIT(rv);
exit:
    SHR_FUNC_EXIT;
}

/*
 * Argument verification for dnx_oam_my_cfm_mac_lsb_range_add
 */
static shr_error_e
dnx_my_cfm_mac_lsb_range_verify(
    int unit,
    uint32 flags,
    int core_id,
    uint32 port_id,
    bcm_mac_t my_cfm_mac,
    uint8 my_cfm_mac_lsb_min,
    uint8 my_cfm_mac_lsb_max)
{

    SHR_FUNC_INIT_VARS(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_my_cfm_mac_verify(unit, flags, core_id, port_id, my_cfm_mac, TRUE));
    if (my_cfm_mac_lsb_min > my_cfm_mac_lsb_max)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Error: my_cfm_mac_lsb_min=%d must not greater than my_cfm_mac_msb_max=%d\n",
                     my_cfm_mac_lsb_min, my_cfm_mac_lsb_max);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Utility function: for a given core and port, find the
 *  first LSB marked as "valid."
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] flags - currently only one in use,
 *          DMX_OAM_CLASSIFIER_INGRESS: ingress DB lookup
 *          (flag), or egress DB lookup (no flag)
 * \param [in] core_id - ID of core to which accessed table
 *        belongs.  Current possible values: 0, 1, or
 *        _SHR_CORE_ALL (to access both tables.)
 * \param [in] port_id - number of configured port
 * \param [out] first_lsb - pointer to which output value is
 *        written.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_my_cfm_mac_find_valid_lsb(
    int unit,
    uint32 flags,
    int core_id,
    uint32 port_id,
    uint32 *first_lsb)
{
    uint32 entry_handle_id;
    bcm_pbmp_t lsb_bmp;
    dbal_tables_e table_id;
    int bit_index;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /**
     *  No need to verify input parameters - already done by
     *  calling function
     */

    /** Get table */
    if (flags & DNX_OAM_CLASSIFIER_INGRESS)
    {
        table_id = DBAL_TABLE_INGRESS_PP_PORT;
    }
    else
    {
        table_id = DBAL_TABLE_EGRESS_PP_PORT;
    }
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table_id, &entry_handle_id));

    /** Set fixed parts of the key */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, port_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);

    /** Get bitmap */
    BCM_PBMP_CLEAR(lsb_bmp);
    dbal_value_field_arr32_request(unit, entry_handle_id, DBAL_FIELD_MY_CFM_MAC_LSB_MAP, INST_SINGLE, lsb_bmp.pbits);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

    /** Iterate over all possible values   */
    BCM_PBMP_ITER(lsb_bmp, bit_index)
    {
        /** Non-zero bit found - use index */
        break;
    }

    /** Return value */
    *first_lsb = bit_index;

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Utility function: read the MSB from a my_mac_cfm entry
 *  to the input array.
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] flags - currently only one in use,
 *          DMX_OAM_CLASSIFIER_INGRESS: ingress DB lookup
 *          (flag), or egress DB lookup (no flag)
 * \param [in] core_id - ID of core to which accessed table
 *        belongs.  Current possible values: 0, 1, or
 *        _SHR_CORE_ALL (to access both tables.)
 * \param [in] port_id - number of configured port
 * \param [out] input_msb - pointer to which result is written.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_my_cfm_mac_read_msb(
    int unit,
    uint32 flags,
    int core_id,
    uint32 port_id,
    bcm_mac_t input_msb)
{
    uint32 entry_handle_id;
    dbal_tables_e table_id;
    uint8 mac_msb[DBAL_FIELD_ARRAY_MAX_SIZE_IN_BYTES];
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /**
     *  No need to verify input parameters - already done by
     *  calling function
     */

    /** Get table */
    if (flags & DNX_OAM_CLASSIFIER_INGRESS)
    {
        table_id = DBAL_TABLE_INGRESS_PP_PORT;
    }
    else
    {
        table_id = DBAL_TABLE_EGRESS_PP_PORT;
    }
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table_id, &entry_handle_id));

    /** Set key */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, port_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);

    /** Get value */
    dbal_value_field_arr8_request(unit, entry_handle_id, DBAL_FIELD_MY_CFM_MAC_MSB, INST_SINGLE, mac_msb);

    /** Access the table */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

    /** Copy to provided pointer */
    sal_memcpy(input_msb, mac_msb, sizeof(bcm_mac_t) - 1);

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Utility function: read the LSB range from a
 *  my_mac_cfm entry
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] flags - currently only one in use,
 *          DMX_OAM_CLASSIFIER_INGRESS: ingress DB lookup
 *          (flag), or egress DB lookup (no flag)
 * \param [in] core_id - ID of core to which accessed table
 *        belongs.  Current possible values: 0, 1, or
 *        _SHR_CORE_ALL (to access both tables.)
 * \param [in] port_id - number of configured port
 * \param [out] lsb_min - pointer to which lsb min is written.
 * \param [out] lsb_max - pointer to which lsb max is written.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_my_cfm_mac_read_lsb(
    int unit,
    uint32 flags,
    int core_id,
    uint32 port_id,
    uint8 *lsb_min,
    uint8 *lsb_max)
{
    uint32 entry_handle_id;
    dbal_tables_e table_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /**
     *  No need to verify input parameters - already done by
     *  calling function
     */

    /** Get table */
    if (flags & DNX_OAM_CLASSIFIER_INGRESS)
    {
        table_id = DBAL_TABLE_INGRESS_PP_PORT;
    }
    else
    {
        table_id = DBAL_TABLE_EGRESS_PP_PORT;
    }
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table_id, &entry_handle_id));

    /** Set key */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, port_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);

    /** Get value */
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_MAC_LSBS_RANGE_MIN, INST_SINGLE, lsb_min);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_MAC_LSBS_RANGE_MAX, INST_SINGLE, lsb_max);

    /** Access the table */
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Utility function: compare the MSB from a my_mac_cfm entry
 *  to the input array.
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] flags - currently only one in use,
 *          DMX_OAM_CLASSIFIER_INGRESS: ingress DB lookup
 *          (flag), or egress DB lookup (no flag)
 * \param [in] core_id - ID of core to which accessed table
 *        belongs.  Current possible values: 0, 1, or
 *        _SHR_CORE_ALL (to access both tables.)
 * \param [in] port_id - number of configured port
 * \param [in] input_msb - Value to which configured MSB is
 *        compared.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_my_cfm_mac_compare_msb(
    int unit,
    uint32 flags,
    int core_id,
    uint32 port_id,
    bcm_mac_t input_msb)
{
    bcm_mac_t read_msb;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    dnx_my_cfm_mac_read_msb(unit, flags, core_id, port_id, read_msb);
    if (sal_memcmp(read_msb, input_msb, UTILEX_PP_MAC_ADDRESS_NOF_U8 - 1) != 0)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal MAC %02X:%02X:%02X:%02X:%02X:%02X; no match for existing MSB "
                     "%02X:%02X:%02X:%02X:%02X\n", SAL_MAC_ADDR_LIST(input_msb), read_msb[0],
                     read_msb[1], read_msb[2], read_msb[3], read_msb[4]);
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Utility function: for a given core and port,
 *  vheck if my_cfm_mac msb is null
 *
 * \param [in] unit - Number of hardware unit used.
 * \param [in] flags - currently only one in use,
 *          DMX_OAM_CLASSIFIER_INGRESS: ingress DB lookup
 *          (flag), or egress DB lookup (no flag)
 * \param [in] core_id - ID of core to which accessed table
 *        belongs.  Current possible values: 0, 1, or
 *        _SHR_CORE_ALL (to access both tables.)
 * \param [in] port_id - number of configured port
 * \param [out] my_cfm_mac_is_null - my_cfm_mac is null
 *        indication
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_my_cfm_mac_msb_is_null(
    int unit,
    uint32 flags,
    int core_id,
    uint32 port_id,
    uint8 *my_cfm_mac_is_null)
{
    bcm_mac_t my_cfm_mac_msb;
    bcm_mac_t null_msb;
    int i;

    SHR_FUNC_INIT_VARS(unit);

    for (i = 0; i < UTILEX_PP_MAC_ADDRESS_NOF_U8; i++)
    {
        null_msb[i] = 0;
    }

    dnx_my_cfm_mac_read_msb(unit, flags, core_id, port_id, my_cfm_mac_msb);

    *my_cfm_mac_is_null = 1;
    if (sal_memcmp(null_msb, my_cfm_mac_msb, UTILEX_PP_MAC_ADDRESS_NOF_U8 - 1) != 0)
    {
        *my_cfm_mac_is_null = 0;
    }

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

/*
 * See prototype definition in oam_internal.h for function description
 */
shr_error_e
dnx_oam_my_cfm_mac_get(
    int unit,
    uint32 flags,
    int core_id,
    uint32 port_id,
    bcm_mac_t my_cfm_mac,
    uint8 *my_cfm_mac_lsb_min,
    uint8 *my_cfm_mac_lsb_max)
{
    uint32 lsb;
    uint8 lsb_min = 0;
    uint8 lsb_max = 0;
    int i;
    int msb_is_null;
    int my_cfm_mac_by_range;
    bcm_mac_t null_msb;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Verify parameters */
    SHR_INVOKE_VERIFY_DNXC(dnx_my_cfm_mac_get_verify(unit, flags, core_id, port_id, my_cfm_mac, FALSE));

    /** First get MSB - one value per port */
    SHR_IF_ERR_EXIT(dnx_my_cfm_mac_read_msb(unit, flags, core_id, port_id, my_cfm_mac));

    my_cfm_mac_by_range = dnx_data_oam.general.oam_my_cfm_mac_by_range_get(unit);

    if (my_cfm_mac_by_range)
    {
       /** Can you find a valid LSB?  If so, return the first valid
        *  LSB found */
        SHR_IF_ERR_EXIT(dnx_my_cfm_mac_read_lsb(unit, flags, core_id, port_id, &lsb_min, &lsb_max));

        for (i = 0; i < UTILEX_PP_MAC_ADDRESS_NOF_U8; i++)
        {
            null_msb[i] = 0;
        }

        msb_is_null = 1;
        if (sal_memcmp(null_msb, my_cfm_mac, UTILEX_PP_MAC_ADDRESS_NOF_U8 - 1) != 0)
        {
            msb_is_null = 0;
        }

        if ((lsb_min == 0) && (lsb_max == 0) && (msb_is_null))
        {
            SHR_ERR_EXIT(_SHR_E_NOT_FOUND, "Error: no legal my_cfm_mac found in table\n");
        }
        lsb = lsb_min;
    }
    else
    {
       /** Can you find a valid LSB?  If so, return the first valid
        *  LSB found */
        SHR_IF_ERR_EXIT(dnx_my_cfm_mac_find_valid_lsb(unit, flags, core_id, port_id, &lsb));
        if (lsb > UTILEX_U8_MAX)
        {
            SHR_ERR_EXIT(_SHR_E_NOT_FOUND, "Error: no legal my_cfm_mac found in table\n");
        }
    }

    my_cfm_mac[MAC_LSB_INDEX] = lsb;
    *my_cfm_mac_lsb_min = lsb_min;
    *my_cfm_mac_lsb_max = lsb_max;

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 * See prototype definition in oam_internal.h for function description
 */
shr_error_e
dnx_oam_my_cfm_mac_range_add(
    int unit,
    uint32 flags,
    int core_id,
    uint32 port_id,
    bcm_mac_t my_cfm_mac)
{
    uint32 entry_handle_id;
    dbal_tables_e table_id;
    uint8 mac_lsb;
    uint8 my_cfm_mac_min;
    uint8 my_cfm_mac_max;
    uint8 my_cfm_mac_is_null;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Verify parameters */
    SHR_INVOKE_VERIFY_DNXC(dnx_my_cfm_mac_verify(unit, flags, core_id, port_id, my_cfm_mac, TRUE));

    mac_lsb = my_cfm_mac[MAC_LSB_INDEX];

    /** Get tables */
    if (flags & DNX_OAM_CLASSIFIER_INGRESS)
    {
        table_id = DBAL_TABLE_INGRESS_PP_PORT;
    }
    else
    {
        table_id = DBAL_TABLE_EGRESS_PP_PORT;
    }
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table_id, &entry_handle_id));

    /** Key for table */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, port_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_MAC_LSBS_RANGE_MIN, INST_SINGLE, &my_cfm_mac_min);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_MAC_LSBS_RANGE_MAX, INST_SINGLE, &my_cfm_mac_max);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

    SHR_IF_ERR_EXIT(dnx_my_cfm_mac_msb_is_null(unit, flags, core_id, port_id, &my_cfm_mac_is_null));

    /** Is there a valid my_mac_cfm? */
    if ((my_cfm_mac_min != 0) || (my_cfm_mac_max != 0) || (!my_cfm_mac_is_null))
    {
       /**
        *  Yes there is; MSB specified must match the one already in
        *  the table
        */
        SHR_IF_ERR_EXIT(dnx_my_cfm_mac_compare_msb(unit, flags, core_id, port_id, my_cfm_mac));

       /**
        *  There is/are (a) valid LSB(s) and the MSB matches.  Is
        *  the specified LSB already valid?
        */
        if ((mac_lsb >= my_cfm_mac_min) && (mac_lsb <= my_cfm_mac_max))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "MAC address %02X:%02X:%02X:%02X:%02X:%02X already in table\n",
                         SAL_MAC_ADDR_LIST(my_cfm_mac));
        }

       /** Set specified LSB value as valid */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, table_id, entry_handle_id));
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, port_id);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
        if (mac_lsb < my_cfm_mac_min)
        {
            dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_MAC_LSBS_RANGE_MIN, INST_SINGLE, mac_lsb);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
        }
        else if (mac_lsb > my_cfm_mac_max)
        {
            dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_MAC_LSBS_RANGE_MAX, INST_SINGLE, mac_lsb);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
        }
    }
    else
    {
       /** No there isn't; write the MSB to the table  */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, table_id, entry_handle_id));
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, port_id);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
        dbal_entry_value_field_arr8_set(unit, entry_handle_id, DBAL_FIELD_MY_CFM_MAC_MSB, INST_SINGLE, my_cfm_mac);
        dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_MAC_LSBS_RANGE_MIN, INST_SINGLE, mac_lsb);
        dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_MAC_LSBS_RANGE_MAX, INST_SINGLE, mac_lsb);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 * See prototype definition in oam_internal.h for function description
 */
shr_error_e
dnx_oam_my_cfm_mac_lsb_range_add(
    int unit,
    uint32 flags,
    int core_id,
    uint32 port_id,
    bcm_mac_t my_cfm_mac,
    uint8 my_cfm_mac_lsb_min,
    uint8 my_cfm_mac_lsb_max)
{
    uint32 entry_handle_id;
    dbal_tables_e table_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Verify parameters */
    SHR_INVOKE_VERIFY_DNXC(dnx_my_cfm_mac_lsb_range_verify(unit, flags, core_id, port_id,
                                                           my_cfm_mac, my_cfm_mac_lsb_min, my_cfm_mac_lsb_max));

    /** Get tables */
    if (flags & DNX_OAM_CLASSIFIER_INGRESS)
    {
        table_id = DBAL_TABLE_INGRESS_PP_PORT;
    }
    else
    {
        table_id = DBAL_TABLE_EGRESS_PP_PORT;
    }

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table_id, &entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, port_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
    dbal_entry_value_field_arr8_set(unit, entry_handle_id, DBAL_FIELD_MY_CFM_MAC_MSB, INST_SINGLE, my_cfm_mac);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_MAC_LSBS_RANGE_MIN, INST_SINGLE, my_cfm_mac_lsb_min);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_MAC_LSBS_RANGE_MAX, INST_SINGLE, my_cfm_mac_lsb_max);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 * See prototype definition in oam_internal.h for function description
 */
shr_error_e
dnx_oam_my_cfm_mac_add(
    int unit,
    uint32 flags,
    int core_id,
    uint32 port_id,
    bcm_mac_t my_cfm_mac)
{
    uint32 entry_handle_id, first_lsb, valid_lsb;
    dbal_tables_e table_id;
    bcm_pbmp_t lsb_bmp;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Verify parameters */
    SHR_INVOKE_VERIFY_DNXC(dnx_my_cfm_mac_verify(unit, flags, core_id, port_id, my_cfm_mac, TRUE));

    /** Get tables */
    if (flags & DNX_OAM_CLASSIFIER_INGRESS)
    {
        table_id = DBAL_TABLE_INGRESS_PP_PORT;
    }
    else
    {
        table_id = DBAL_TABLE_EGRESS_PP_PORT;
    }
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table_id, &entry_handle_id));

    /** Key for table */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, port_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);

    /** Get the LSB map; we'll need for reading and writing   */
    BCM_PBMP_CLEAR(lsb_bmp);
    dbal_value_field_arr32_request(unit, entry_handle_id, DBAL_FIELD_MY_CFM_MAC_LSB_MAP, INST_SINGLE, lsb_bmp.pbits);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

    /** Is there a valid my_mac_cfm? */
    SHR_IF_ERR_EXIT(dnx_my_cfm_mac_find_valid_lsb(unit, flags, core_id, port_id, &first_lsb));
    if (first_lsb <= UTILEX_U8_MAX)
    {
        /**
         *  Yes there is; MSB specified must match the one already in
         *  the table
         */
        SHR_IF_ERR_EXIT(dnx_my_cfm_mac_compare_msb(unit, flags, core_id, port_id, my_cfm_mac));

        /**
         *  There is/are (a) valid LSB(s) and the MSB matches.  Is
         *  the specified LSB already valid?
         */
        valid_lsb = BCM_PBMP_MEMBER(lsb_bmp, my_cfm_mac[MAC_LSB_INDEX]);
        if (valid_lsb == TRUE)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "MAC address %02X:%02X:%02X:%02X:%02X:%02X already in table\n",
                         SAL_MAC_ADDR_LIST(my_cfm_mac));
        }
    }
    else
    {
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, port_id);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
        /** No there isn't; write the MSB to the table  */
        dbal_entry_value_field_arr8_set(unit, entry_handle_id, DBAL_FIELD_MY_CFM_MAC_MSB, INST_SINGLE, my_cfm_mac);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    }

    /** Set specified LSB value as valid */
    BCM_PBMP_PORT_ADD(lsb_bmp, my_cfm_mac[MAC_LSB_INDEX]);
    SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, table_id, entry_handle_id));
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, port_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
    dbal_entry_value_field_arr32_set(unit, entry_handle_id, DBAL_FIELD_MY_CFM_MAC_LSB_MAP, INST_SINGLE, lsb_bmp.pbits);

    /** Access the table */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 * See prototype definition in oam_internal.h for function description
 */
shr_error_e
dnx_oam_my_cfm_mac_delete(
    int unit,
    uint32 flags,
    int core_id,
    uint32 port_id,
    bcm_mac_t my_cfm_mac)
{
    uint32 entry_handle_id, first_lsb, valid_lsb;
    dbal_tables_e table_id;
    bcm_pbmp_t lsb_bmp;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Verify parameters */
    SHR_INVOKE_VERIFY_DNXC(dnx_my_cfm_mac_verify(unit, flags, core_id, port_id, my_cfm_mac, TRUE));

    /** Get tables */
    if (flags & DNX_OAM_CLASSIFIER_INGRESS)
    {
        table_id = DBAL_TABLE_INGRESS_PP_PORT;
    }
    else
    {
        table_id = DBAL_TABLE_EGRESS_PP_PORT;
    }
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table_id, &entry_handle_id));

    /** Keys for entry   */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, port_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);

    /** Is there a valid my_mac_cfm? */
    SHR_IF_ERR_EXIT(dnx_my_cfm_mac_find_valid_lsb(unit, flags, core_id, port_id, &first_lsb));
    if (first_lsb > UTILEX_U8_MAX)
    {
        /** No there isn't - operation illegal */
        SHR_ERR_EXIT(_SHR_E_PARAM, "This port has no valid my_mac_cfm\n");
    }

    /** Is there an LSB to delete? */
    BCM_PBMP_CLEAR(lsb_bmp);
    dbal_value_field_arr32_request(unit, entry_handle_id, DBAL_FIELD_MY_CFM_MAC_LSB_MAP, INST_SINGLE, lsb_bmp.pbits);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));
    valid_lsb = BCM_PBMP_MEMBER(lsb_bmp, my_cfm_mac[MAC_LSB_INDEX]);
    if (valid_lsb == FALSE)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "MAC address %02X:%02X:%02X:%02X:%02X:%02X not found in table\n",
                     SAL_MAC_ADDR_LIST(my_cfm_mac));
    }

    /** LSB found; does the MSB match? */
    SHR_IF_ERR_EXIT(dnx_my_cfm_mac_compare_msb(unit, flags, core_id, port_id, my_cfm_mac));

    /** Set specified LSB value as invalid */
    BCM_PBMP_PORT_REMOVE(lsb_bmp, my_cfm_mac[MAC_LSB_INDEX]);
    dbal_entry_value_field_arr32_set(unit, entry_handle_id, DBAL_FIELD_MY_CFM_MAC_LSB_MAP, INST_SINGLE, lsb_bmp.pbits);

    /** Access the table */
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 * See prototype definition in oam_internal.h for function description
 */
shr_error_e
dnx_oam_my_cfm_mac_range_delete(
    int unit,
    uint32 flags,
    int core_id,
    uint32 port_id,
    bcm_mac_t my_cfm_mac)
{
    uint32 entry_handle_id;
    dbal_tables_e table_id;
    uint8 my_cfm_mac_min;
    uint8 my_cfm_mac_max;
    uint8 mac_lsb;
    uint8 my_cfm_mac_is_null;
    bcm_mac_t null_msb;
    int i;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    mac_lsb = my_cfm_mac[MAC_LSB_INDEX];

    /** Verify parameters */
    SHR_INVOKE_VERIFY_DNXC(dnx_my_cfm_mac_verify(unit, flags, core_id, port_id, my_cfm_mac, TRUE));

    /** Get tables */
    if (flags & DNX_OAM_CLASSIFIER_INGRESS)
    {
        table_id = DBAL_TABLE_INGRESS_PP_PORT;
    }
    else
    {
        table_id = DBAL_TABLE_EGRESS_PP_PORT;
    }
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table_id, &entry_handle_id));

    /** Keys for entry   */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, port_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_MAC_LSBS_RANGE_MIN, INST_SINGLE,
                              (uint8 *) &my_cfm_mac_min);
    dbal_value_field8_request(unit, entry_handle_id, DBAL_FIELD_MAC_LSBS_RANGE_MAX, INST_SINGLE,
                              (uint8 *) &my_cfm_mac_max);
    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

    SHR_IF_ERR_EXIT(dnx_my_cfm_mac_msb_is_null(unit, flags, core_id, port_id, &my_cfm_mac_is_null));

    /** Is there a valid my_mac_cfm? */
    if ((my_cfm_mac_min == 0) && (my_cfm_mac_max == 0) && (my_cfm_mac_is_null))
    {
       /** No there isn't - operation illegal */
        SHR_ERR_EXIT(_SHR_E_PARAM, "This port has no valid my_mac_cfm\n");
    }

    /** LSB found; does the MSB match? */
    SHR_IF_ERR_EXIT(dnx_my_cfm_mac_compare_msb(unit, flags, core_id, port_id, my_cfm_mac));

    /** MSB matches - Is LSB in the range ? */
    if ((mac_lsb > my_cfm_mac_max) || (mac_lsb < my_cfm_mac_min))
    {
       /** No - Error */
        SHR_ERR_EXIT(_SHR_E_PARAM, "MAC address %02X:%02X:%02X:%02X:%02X:%02X not found in table\n",
                     SAL_MAC_ADDR_LIST(my_cfm_mac));
    }
    else if ((mac_lsb - my_cfm_mac_min) <= (my_cfm_mac_max - mac_lsb))
    {
       /** mac_lsb is closer to my_cfm_min */
        if (my_cfm_mac_max == mac_lsb)
        {
            for (i = 0; i < UTILEX_PP_MAC_ADDRESS_NOF_U8; i++)
            {
                null_msb[i] = 0;
            }

            SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, table_id, entry_handle_id));
            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, port_id);
            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
            dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_MAC_LSBS_RANGE_MIN, INST_SINGLE, 0);
            dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_MAC_LSBS_RANGE_MAX, INST_SINGLE, 0);

          /** last lsb - clean my_cfm_mac MSB */
            dbal_entry_value_field_arr8_set(unit, entry_handle_id, DBAL_FIELD_MY_CFM_MAC_MSB, INST_SINGLE, null_msb);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            LOG_VERBOSE(BSL_LS_BCM_OAM, (BSL_META_U(unit, "My CFM MAC for port %d is cleared.\n"), port_id));
        }
        else
        {
            /*
             * mac is in my_cfm_mac range - Update range min
             */
            SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, table_id, entry_handle_id));
            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, port_id);
            dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
            dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_MAC_LSBS_RANGE_MIN, INST_SINGLE, mac_lsb + 1);
            SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
            LOG_VERBOSE(BSL_LS_BCM_OAM,
                        (BSL_META_U(unit, "My CFM MAC for port %d is updated. LSB Min %d,  LSB Max %d\n"), port_id,
                         (mac_lsb + 1), my_cfm_mac_max));
        }
    }
    else
    {
        /*
         * mac is in my_cfm_mac range - Update range max
         */
        SHR_IF_ERR_EXIT(DBAL_HANDLE_CLEAR(unit, table_id, entry_handle_id));
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, port_id);
        dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);
        dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_MAC_LSBS_RANGE_MAX, INST_SINGLE, mac_lsb - 1);
        SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
        LOG_VERBOSE(BSL_LS_BCM_OAM,
                    (BSL_META_U(unit, "My CFM MAC for port %d is updated. LSB Min %d,  LSB Max %d\n"), port_id,
                     my_cfm_mac_min, (mac_lsb - 1)));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 * See prototype definition in oam_internal.h for function description
 */
shr_error_e
dnx_oam_my_cfm_mac_range_clear(
    int unit,
    uint32 flags,
    int core_id,
    uint32 port_id)
{
    uint32 entry_handle_id;
    dbal_tables_e table_id;
    bcm_mac_t null_msb;
    int i = 0;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Get tables */
    if (flags & DNX_OAM_CLASSIFIER_INGRESS)
    {
        table_id = DBAL_TABLE_INGRESS_PP_PORT;
    }
    else
    {
        table_id = DBAL_TABLE_EGRESS_PP_PORT;
    }

    /** Take DBAL handle */
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table_id, &entry_handle_id));

    /** Set KEY field */
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_PP_PORT, port_id);
    dbal_entry_key_field32_set(unit, entry_handle_id, DBAL_FIELD_CORE_ID, core_id);

    for (i = 0; i < UTILEX_PP_MAC_ADDRESS_NOF_U8; i++)
    {
        null_msb[i] = 0;
    }

    /** Clear My CFM MAC */
    dbal_entry_value_field_arr8_set(unit, entry_handle_id, DBAL_FIELD_MY_CFM_MAC_MSB, INST_SINGLE, null_msb);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_MAC_LSBS_RANGE_MIN, INST_SINGLE, 0);
    dbal_entry_value_field8_set(unit, entry_handle_id, DBAL_FIELD_MAC_LSBS_RANGE_MAX, INST_SINGLE, 0);
    SHR_IF_ERR_EXIT(dbal_entry_commit(unit, entry_handle_id, DBAL_COMMIT));
    LOG_VERBOSE(BSL_LS_BCM_OAM, (BSL_META_U(unit, "My CFM MAC for port %d is cleared.\n"), port_id));

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Utility function: Form the GACH or CW given the
 *                            channel value
 *
 * \param [in] unit - Relevant unit
 * \param [in] channel - Channel value
 * \param [out] ach_header - CW/ACH header value
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
dnx_oam_mpls_tp_bfd_ach_header_form(
    int unit,
    uint32 *channel,
    uint32 *ach_header)
{
    /*
     * reserved, ach_ver, gach_indication are hard_coded as per RFC
     */
    uint32 reserved = 0;
    uint32 ach_ver = 0;
    uint32 gach_indication = 1;
    /** using array for coverity*/
    uint32 channel_arr[1] = { *channel };
    uint32 ach_header_arr[1] = { *ach_header };

    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(dbal_fields_field_type_struct_field_encode
                    (unit, DBAL_FIELD_TYPE_DEF_ACH_HEADER, DBAL_FIELD_CHANNEL_TYPE, channel_arr, ach_header_arr));
    SHR_IF_ERR_EXIT(dbal_fields_field_type_struct_field_encode
                    (unit, DBAL_FIELD_TYPE_DEF_ACH_HEADER, DBAL_FIELD_RESERVED, &reserved, ach_header_arr));
    SHR_IF_ERR_EXIT(dbal_fields_field_type_struct_field_encode
                    (unit, DBAL_FIELD_TYPE_DEF_ACH_HEADER, DBAL_FIELD_ACH_VER, &ach_ver, ach_header_arr));
    SHR_IF_ERR_EXIT(dbal_fields_field_type_struct_field_encode
                    (unit, DBAL_FIELD_TYPE_DEF_ACH_HEADER, DBAL_FIELD_GACH_INDICATION, &gach_indication,
                     ach_header_arr));

    *channel = channel_arr[0];
    *ach_header = ach_header_arr[0];

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Utility function: Get the channel value given the
 *                            ACH or CW
 *
 * \param [in] unit - Relevant unit
 * \param [in] ach_header - CW/ACH header value
 * \param [out] channel - Channel value
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
dnx_oam_mpls_tp_bfd_channel_value_get_from_ach_header(
    int unit,
    uint32 *ach_header,
    uint32 *channel)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(dbal_fields_field_type_struct_field_decode
                    (unit, DBAL_FIELD_TYPE_DEF_ACH_HEADER, DBAL_FIELD_CHANNEL_TYPE, channel, ach_header));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Get a channel type for MPLS-TP CW/ACH
 *   This function gets the TX side.
 * \param [in] unit  -
 *   Number of hardware unit used..
 * \param [in] channel_type  -
 *   Type of the mpls tp channel.
 * \param [out] value -
 *   value configured for channel type
 * \return
 *   \retval Zero if no error was detected
 *   \retval Negative if error was detected. See \ref
 *           shr_error_e
 * \remark
 *   * None
 * \see
 *   * bcm_dnx_oam_mpls_tp_channel_type_rx_get
 *   * bcm_dnx_oam_mpls_tp_channel_type_tx_get
 *   * bcm_dnx_oam_mpls_tp_channel_type_tx_set
 */
shr_error_e
bcm_dnx_oam_mpls_tp_channel_type_tx_get(
    int unit,
    bcm_oam_mpls_tp_channel_type_t channel_type,
    int *value)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    if (DNX_OAMP_IS_V1(unit))
    {
        switch (channel_type)
        {
            case bcmOamMplsTpChannelPweBfd:
                /*
                 * We always use index 0. We do not write into other indexes.
                 */
                SHR_IF_ERR_EXIT(dnx_oamp_v1_bfd_pwe_channel_value_get(unit, 0, (uint32 *) value));
                break;
            case bcmOamMplsTpChannelPweonoam:
                SHR_IF_ERR_EXIT(dnx_oamp_v1_y1731_mpls_tp_channel_value_get(unit, (uint32 *) value));
                break;
            case bcmOamMplsTpChannelY1731:
                SHR_IF_ERR_EXIT(dnx_oamp_v1_y1731_pwe_channel_value_get(unit, (uint32 *) value));
                break;
            case bcmOamMplsTpChannelMplsTpBfd:
                SHR_IF_ERR_EXIT(dnx_oamp_v1_bfd_pwe_channel_value_get(unit, 1, (uint32 *) value));
                break;
            default:
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid channel_type");
                break;
        }
    }
    else
    {
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Set a channel type for MPLS-TP CW/ACH
 *   This function sets the TX side.
 * \param [in] unit  -
 *   Number of hardware unit used..
 * \param [in] channel_type  -
 *   Type of the mpls tp channel.
 * \param [in] value -
 *   value to be configured for channel type
 * \return
 *   \retval Zero if no error was detected
 *   \retval Negative if error was detected. See \ref
 *           shr_error_e
 * \remark
 *   * None
 * \see
 *   * bcm_dnx_oam_mpls_tp_channel_type_rx_get
 *   * bcm_dnx_oam_mpls_tp_channel_type_tx_get
 *   * bcm_dnx_oam_mpls_tp_channel_type_tx_set
 */
shr_error_e
bcm_dnx_oam_mpls_tp_channel_type_tx_set(
    int unit,
    bcm_oam_mpls_tp_channel_type_t channel_type,
    int value)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    if (DNX_OAMP_IS_V1(unit))
    {
        switch (channel_type)
        {
            case bcmOamMplsTpChannelPweBfd:
                /*
                 * We always use index 0. We do not write into other indexes.
                 */
                SHR_IF_ERR_EXIT(dnx_oamp_v1_bfd_pwe_channel_value_set(unit, 0, value));
                break;
            case bcmOamMplsTpChannelPweonoam:
                SHR_IF_ERR_EXIT(dnx_oamp_v1_y1731_mpls_tp_channel_value_set(unit, value));
                break;
            case bcmOamMplsTpChannelY1731:
                SHR_IF_ERR_EXIT(dnx_oamp_v1_y1731_pwe_channel_value_set(unit, value));
                break;
            case bcmOamMplsTpChannelMplsTpBfd:
                SHR_IF_ERR_EXIT(dnx_oamp_v1_bfd_pwe_channel_value_set(unit, 1, value));
                break;
            default:
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid channel_type");
                break;
        }
    }
    else
    {
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *  Delete mpls tp channel types according to vlaues in list - tx
 *  side.
 * \param [in] unit  -
 *   Relevant unit.
 * \param [in] channel_type  -
 *   Type of the mpls tp channel.
 * \param [in] value -
 *    value to delete
 * \return
 *   \retval Zero if no error was detected
 *   \retval Negative if error was detected. See \ref
 *           shr_error_e
 * \remark
 *   * None
 * \see
 *   * bcm_dnx_oam_mpls_tp_channel_type_rx_get
 *   * bcm_dnx_oam_mpls_tp_channel_type_tx_get
 *   * bcm_dnx_oam_mpls_tp_channel_type_tx_set
*/
shr_error_e
bcm_dnx_oam_mpls_tp_channel_type_tx_delete(
    int unit,
    bcm_oam_mpls_tp_channel_type_t channel_type,
    int value)
{
    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    if (DNX_OAMP_IS_V1(unit))
    {
        switch (channel_type)
        {
            case bcmOamMplsTpChannelPweBfd:
                /*
                 * We always use index 0. We do not write into other indexes.
                 */
                SHR_IF_ERR_EXIT(dnx_oamp_v1_bfd_pwe_channel_value_delete(unit, 0, value));
                break;
            case bcmOamMplsTpChannelPweonoam:
                SHR_IF_ERR_EXIT(dnx_oamp_v1_y1731_mpls_tp_channel_value_set(unit, Y1731_MPLS_TP_GACH_DEFAULT_CHANNEL));
                break;
            case bcmOamMplsTpChannelY1731:
                SHR_IF_ERR_EXIT(dnx_oamp_v1_y1731_pwe_channel_value_set(unit, Y1731_PWE_GACH_DEFAULT_CHANNEL));
                break;
            case bcmOamMplsTpChannelMplsTpBfd:
                SHR_IF_ERR_EXIT(dnx_oamp_v1_bfd_pwe_channel_value_delete(unit, 1, value));
                break;
            default:
                SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid channel_type");
                break;
        }
    }
    else
    {
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * See prototype definition in oam_internal.h for function description
 */
shr_error_e
dnx_oam_channel_type_table_get_number_of_entries(
    int unit,
    int *number_of_entries)
{
    int table_oam_channel_type, table_roam_cfg;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(number_of_entries, _SHR_E_PARAM, "number of entries");

    SHR_IF_ERR_EXIT(dbal_tables_capacity_get(unit, DBAL_TABLE_OAM_CHANNEL_TYPE, &table_oam_channel_type));

    table_roam_cfg = dnx_data_oam.general.oam_nof_pemla_channel_types_get(unit);

    /** Compare and use the the smaller size */
    if (table_roam_cfg <= table_oam_channel_type)
    {
        *number_of_entries = table_roam_cfg;
    }
    else
    {
        *number_of_entries = table_oam_channel_type;
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

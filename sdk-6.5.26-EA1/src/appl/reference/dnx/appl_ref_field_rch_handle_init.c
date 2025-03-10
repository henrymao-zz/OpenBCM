/** \file appl_ref_rch_handle_init.c
 * 
 *
 * Application for removing the RCH header from recycled packets,
 * or modify the egress parsing params and fwd_layer_index for rch extended encapsulation packets.
 *
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_FLDTESTSDNX

 /*
  * Include files.
  * {
  */
/** soc */
#include <soc/schanmsg.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_field.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_port_pp.h>
/** shared */
#include <soc/sand/shrextend/shrextend_debug.h>
/** appl */
#include <appl/diag/sand/diag_sand_framework.h>
#include <appl/diag/sand/diag_sand_prt.h>
#include "appl_ref_field_rch_handle_init.h"
/** bcm */
#include <bcm/field.h>
#include <bcm/switch.h>
/** sal */
#include <sal/appl/sal.h>
#include <sal/core/libc.h>

/*
 * }
 */

/*
 * DEFINEs
 */

/*
 * MACROs
 * {
 */
/*
 * }
 */

 /*
  * Global and Static
  */

/**
 * \brief
 *   This function Configures a context and field group for removing the RCH header.
 *   application
 * \param [in] unit - The unit number.
 *
 * \return
 *   Error code (as per 'shr_error_e').
 * \see
 *   shr_error_e
 */
shr_error_e
appl_dnx_field_rch_remove_init(
    int unit)
{
    bcm_field_context_t context_id = dnx_data_field.context.default_rch_remove_context_get(unit);
    bcm_field_context_info_t context_info;
    bcm_field_presel_entry_id_t presel_entry_id;
    bcm_field_presel_entry_data_t presel_entry_data;
    bcm_field_qualifier_info_create_t qual_info;
    bcm_field_qualifier_info_get_t qual_info_get;
    bcm_field_qualify_t bytes_to_remove_header_udq;
    bcm_field_qualify_t bytes_to_remove_fix_udq;
    bcm_field_group_info_t fg_info;
    bcm_field_group_attach_info_t attach_info;
    bcm_field_entry_info_t tcam_entry_info;
    bcm_field_entry_t dummy_entry_id;
    bcm_field_group_t fg_id;
    int layer_record_offset_offset;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Create a context and use the bit we set in the port profile as a qualifier for its preselector.
     */
    bcm_field_context_info_t_init(&context_info);
    sal_strncpy_s((char *) (context_info.name), "RCH_REMOVE", sizeof(context_info.name));
    SHR_IF_ERR_EXIT(bcm_field_context_create
                    (unit, BCM_FIELD_FLAG_WITH_ID, bcmFieldStageIngressPMF3, &context_info, &context_id));
    bcm_field_presel_entry_id_info_init(&presel_entry_id);
    presel_entry_id.presel_id = dnx_data_field.preselector.default_rch_remove_presel_id_ipmf3_get(unit);
    presel_entry_id.stage = bcmFieldStageIngressPMF3;
    bcm_field_presel_entry_data_info_init(&presel_entry_data);
    presel_entry_data.nof_qualifiers = 1;
    presel_entry_data.context_id = context_id;
    presel_entry_data.entry_valid = TRUE;
    /** Check that the bit in the port profile is set */
    presel_entry_data.qual_data[0].qual_type = bcmFieldQualifyPortClassTrafficManagement;
    presel_entry_data.qual_data[0].qual_value = 4;
    presel_entry_data.qual_data[0].qual_mask = 7; /** 3 bits field */
    SHR_IF_ERR_EXIT(bcm_field_presel_set(unit, 0, &presel_entry_id, &presel_entry_data));

    /*
     * We now take the offset of the first header from the laye rrecord and use it in the
     * bcmFieldActionStartPacketStrip action to remove that header.
     * The bcmFieldActionStartPacketStrip action is broken to two parts:
     * bytes_to_remove_header - An indication of how many bytes to remove based on the header offset.
     * 0 means do not remove any by the header, 1 means remove up to the first layer.
     * bytes_to_remove_fix - Extra bytes to remove. Should be the size of the RCH header.
     */
    bcm_field_qualifier_info_create_t_init(&qual_info);
    qual_info.size = 2;
    sal_strncpy_s((char *) qual_info.name, "RCH_REMOVE_BYTES_TO_REMOVE_HEADER_Q", sizeof(qual_info.name));
    SHR_IF_ERR_EXIT(bcm_field_qualifier_create(unit, 0, &qual_info, &bytes_to_remove_header_udq));
    bcm_field_qualifier_info_create_t_init(&qual_info);
    qual_info.size = 7;
    sal_strncpy_s((char *) qual_info.name, "RCH_REMOVE_BYTES_TO_REMOVE_FIX_Q", sizeof(qual_info.name));
    SHR_IF_ERR_EXIT(bcm_field_qualifier_create(unit, 0, &qual_info, &bytes_to_remove_fix_udq));

    /*
     * If we had taken the size of the RCH header from the port profile, we would have taken the qualifier's offset.
     * SHR_IF_ERR_EXIT(bcm_field_qualifier_info_get
     *                 (unit, bcmFieldQualifyPortClassTrafficManagement, bcmFieldStageIngressPMF3, &qual_info_get));
     * tm_port_profile_offset = qual_info_get.offset;
     */

    /*
     * Get the offset of the layer offset within the layer record.
     */
    SHR_IF_ERR_EXIT(bcm_field_qualifier_info_get
                    (unit, bcmFieldQualifyLayerRecordOffset, bcmFieldStageIngressPMF3, &qual_info_get));
    layer_record_offset_offset = qual_info_get.offset;

    /*
     * Create the field group.
     */
    bcm_field_group_info_t_init(&fg_info);
    bcm_field_group_attach_info_t_init(&attach_info);
    fg_info.fg_type = bcmFieldGroupTypeDirectExtraction;
    fg_info.stage = bcmFieldStageIngressPMF3;

    /*
     * Set quals
     */
    fg_info.nof_quals = 2;
    fg_info.qual_types[0] = bytes_to_remove_header_udq;
    attach_info.key_info.qual_types[0] = fg_info.qual_types[0];
    attach_info.key_info.qual_info[0].input_type = bcmFieldInputTypeConst;
    /*
     * If we had placed the size of the RCH header in the port profile, we would have written 1 here to remove 
     * whatever may be before this header (like PTCH).
     */
    attach_info.key_info.qual_info[0].input_arg = 0;
    fg_info.qual_types[1] = bytes_to_remove_fix_udq;
    attach_info.key_info.qual_types[1] = fg_info.qual_types[1];
    /*
     * If we had placed the size of the RCH header in the port profile, we would have written bcmFieldInputTypeMetaData
     * with offset tm_port_profile_offset + bit_indicating_rch_port here. Another +1 if we also had the valid bit in there.
     */
    attach_info.key_info.qual_info[1].input_type = bcmFieldInputTypeLayerRecordsAbsolute;
    attach_info.key_info.qual_info[1].input_arg = 1;
    attach_info.key_info.qual_info[1].offset = layer_record_offset_offset;

    fg_info.nof_actions = 1;
    fg_info.action_types[0] = bcmFieldActionStartPacketStrip;
    /** If we had used the profile for valid bit, we would have a valid bit in the action. */
    fg_info.action_with_valid_bit[0] = FALSE;
    attach_info.payload_info.action_types[0] = fg_info.action_types[0];

    sal_strncpy_s((char *) fg_info.name, "RCH_REMOVE", sizeof(fg_info.name));
    SHR_IF_ERR_EXIT(bcm_field_group_add(unit, 0, &fg_info, &fg_id));

    attach_info.key_info.nof_quals = fg_info.nof_quals;
    attach_info.payload_info.nof_actions = fg_info.nof_actions;

    /** We set the position only for the example below of checking that the first layer is indeed RCH */
    attach_info.payload_info.action_info[0].priority = BCM_FIELD_ACTION_POSITION(0, 3);

    SHR_IF_ERR_EXIT(bcm_field_group_context_attach(unit, 0, fg_id, context_id, &attach_info));

    /*
     * At this point we are going to add a lookup to check that the first layer is RCH, and disable the action
     * bcmFieldActionStartPacketStrip otherwise. This is done just as an example and is not needed.
     */

    bcm_field_group_info_t_init(&fg_info);
    bcm_field_group_attach_info_t_init(&attach_info);
    fg_info.fg_type = bcmFieldGroupTypeTcam;
    fg_info.stage = bcmFieldStageIngressPMF3;
    fg_info.nof_quals = 1;
    fg_info.qual_types[0] = bcmFieldQualifyLayerRecordType;
    attach_info.key_info.qual_types[0] = fg_info.qual_types[0];
    attach_info.key_info.qual_info[0].input_type = bcmFieldInputTypeLayerRecordsAbsolute;
    attach_info.key_info.qual_info[0].input_arg = 0;
    fg_info.nof_actions = 1;
    fg_info.action_types[0] = bcmFieldActionInvalidNext;
    attach_info.payload_info.action_types[0] = fg_info.action_types[0];
    sal_strncpy_s((char *) fg_info.name, "RCH_FIRST_LAYER", sizeof(fg_info.name));
    SHR_IF_ERR_EXIT(bcm_field_group_add(unit, 0, &fg_info, &fg_id));
    attach_info.key_info.nof_quals = fg_info.nof_quals;
    attach_info.payload_info.nof_actions = fg_info.nof_actions;
    /** We set the position to be one above the position of the bcmFieldActionStartPacketStrip action. */
    attach_info.payload_info.action_info[0].priority = BCM_FIELD_ACTION_POSITION(0, 2);
    SHR_IF_ERR_EXIT(bcm_field_group_context_attach(unit, 0, fg_id, context_id, &attach_info));
    bcm_field_entry_info_t_init(&tcam_entry_info);
    /** Set the entry to qualify upon RCH layer type. */
    tcam_entry_info.entry_qual[0].type = bcmFieldQualifyLayerRecordType;
    tcam_entry_info.entry_qual[0].value[0] = bcmFieldLayerTypeRch;
    tcam_entry_info.entry_qual[0].mask[0] = 0x1F;
    /** Set the action to disable the action from the first field group.*/
    tcam_entry_info.entry_action[0].type = bcmFieldActionInvalidNext;
    /*
     * We create two entries. if the first layer is RCH, do nothing. otherwise, a default entry will diable the action
     * bcmFieldActionStartPacketStrip from the first field group.
     * Hre we do not save the entry IDs, as we will not be using them.
     */
    tcam_entry_info.priority = 0;
    tcam_entry_info.nof_entry_quals = 1;
    tcam_entry_info.nof_entry_actions = 0;
    SHR_IF_ERR_EXIT(bcm_field_entry_add(unit, 0, fg_id, &tcam_entry_info, &dummy_entry_id));
    tcam_entry_info.priority = 1;
    tcam_entry_info.nof_entry_quals = 0;
    tcam_entry_info.nof_entry_actions = 1;
    SHR_IF_ERR_EXIT(bcm_field_entry_add(unit, 0, fg_id, &tcam_entry_info, &dummy_entry_id));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   This function Configures a new context and field group for usage of RCH extended encapsulaion application.
 *   It is made in order to verify that egress packet meet the editing limitations
 *   Unlike other RCH scenarios, here the idea is not to remove the RCH in the ingress pipe, but to remove it in the ETPP.
 * \param [in] unit - The unit number.
 *
 * \return
 *   Error code (as per 'shr_error_e').
 * \see
 *   shr_error_e
 */
shr_error_e
appl_dnx_field_rch_extended_encap_init(
    int unit)
{
    bcm_field_context_t context_id = dnx_data_field.context.default_rch_extended_encap_context_get(unit);
    bcm_field_context_info_t context_info;
    bcm_field_presel_entry_id_t presel_entry_id;
    bcm_field_presel_entry_data_t presel_entry_data;
    bcm_field_group_info_t fg_info;
    bcm_field_group_attach_info_t attach_info;
    bcm_field_group_t fg_id;
    bcm_field_action_info_t action_info;
    bcm_field_action_t action_id_parsing_start_type, action_id_parsing_start_offset,
        action_id_fwd_layer_index, action_id_egress_parsing_index;
    uint32 hw_value[BCM_FIELD_ACTION_WIDTH_IN_WORDS] = { 0 };
    uint32 bcm_value[BCM_FIELD_ACTION_WIDTH_IN_WORDS] = { 0 };
    SHR_FUNC_INIT_VARS(unit);


    /*
     * Create a context and use the bit we set in the port profile as a qualifier for its preselector.
     */
    bcm_field_context_info_t_init(&context_info);
    sal_strncpy_s((char *) (context_info.name), "RCH_EXTENDED_ENCAP", sizeof(context_info.name));
    SHR_IF_ERR_EXIT(bcm_field_context_create
                    (unit, BCM_FIELD_FLAG_WITH_ID, bcmFieldStageIngressPMF3, &context_info, &context_id));
    bcm_field_presel_entry_id_info_init(&presel_entry_id);
    presel_entry_id.presel_id = dnx_data_field.preselector.default_rch_extended_encap_presel_id_ipmf3_get(unit);
    presel_entry_id.stage = bcmFieldStageIngressPMF3;
    bcm_field_presel_entry_data_info_init(&presel_entry_data);
    presel_entry_data.nof_qualifiers = 1;
    presel_entry_data.context_id = context_id;
    presel_entry_data.entry_valid = TRUE;
    /** Check that the bit in the port profile is set */
    presel_entry_data.qual_data[0].qual_type = bcmFieldQualifyPortClassTrafficManagement;
    presel_entry_data.qual_data[0].qual_value = 5;
    presel_entry_data.qual_data[0].qual_mask = 0x7;     /** 3 bits field */
    SHR_IF_ERR_EXIT(bcm_field_presel_set(unit, 0, &presel_entry_id, &presel_entry_data));

    /*
     * Create the field group.
     */
    bcm_field_group_info_t_init(&fg_info);
    bcm_field_group_attach_info_t_init(&attach_info);
    fg_info.fg_type = bcmFieldGroupTypeConst;
    fg_info.stage = bcmFieldStageIngressPMF3;

    /*
     * Set quals
     */
    fg_info.nof_quals = 0;

    bcm_field_action_info_t_init(&action_info);
    SHR_IF_ERR_EXIT(bcm_field_action_info_get
                    (unit, bcmFieldActionParsingStartType, bcmFieldStageIngressPMF3, &action_info));
    action_info.action_type = bcmFieldActionParsingStartTypeRaw;
    action_info.prefix_size = action_info.size;
    action_info.size = 0;
    bcm_value[0] = bcmFieldLayerTypeRch; /** use rch layer for setting rch_extended encapulation starting type */
    SHR_IF_ERR_EXIT(bcm_field_action_value_map
                    (unit, bcmFieldStageIngressPMF3, bcmFieldActionParsingStartType, bcm_value, hw_value));
    action_info.prefix_value = hw_value[0];
    action_info.stage = bcmFieldStageIngressPMF3;
    sal_strncpy_s((char *) (action_info.name), "parsingStartType", sizeof(action_info.name));
    SHR_IF_ERR_EXIT(bcm_field_action_create(unit, 0, &action_info, &action_id_parsing_start_type));

    bcm_field_action_info_t_init(&action_info);
    SHR_IF_ERR_EXIT(bcm_field_action_info_get
                    (unit, bcmFieldActionParsingStartOffset, bcmFieldStageIngressPMF3, &action_info));
    action_info.action_type = bcmFieldActionParsingStartOffset;
    action_info.prefix_size = action_info.size;
    action_info.size = 0;
    bcm_value[0] = 0;
    SHR_IF_ERR_EXIT(bcm_field_action_value_map
                    (unit, bcmFieldStageIngressPMF3, bcmFieldActionParsingStartOffset, bcm_value, hw_value));
    action_info.prefix_value = hw_value[0];
    action_info.stage = bcmFieldStageIngressPMF3;
    sal_strncpy_s((char *) (action_info.name), "parsingStartOffset", sizeof(action_info.name));
    SHR_IF_ERR_EXIT(bcm_field_action_create(unit, 0, &action_info, &action_id_parsing_start_offset));

    bcm_field_action_info_t_init(&action_info);
    SHR_IF_ERR_EXIT(bcm_field_action_info_get
                    (unit, bcmFieldActionForwardingLayerIndex, bcmFieldStageIngressPMF3, &action_info));
    action_info.action_type = bcmFieldActionForwardingLayerIndex;
    action_info.prefix_size = action_info.size;
    action_info.size = 0;
    action_info.prefix_value = 1;
    action_info.stage = bcmFieldStageIngressPMF3;
    sal_strncpy_s((char *) (action_info.name), "FwdLayerIndex", sizeof(action_info.name));
    SHR_IF_ERR_EXIT(bcm_field_action_create(unit, 0, &action_info, &action_id_fwd_layer_index));

    bcm_field_action_info_t_init(&action_info);
    SHR_IF_ERR_EXIT(bcm_field_action_info_get
                    (unit, bcmFieldActionEgressForwardingIndex, bcmFieldStageIngressPMF3, &action_info));
    action_info.action_type = bcmFieldActionEgressForwardingIndex;
    action_info.prefix_size = action_info.size;
    action_info.size = 0;
    action_info.prefix_value = 1;
    action_info.stage = bcmFieldStageIngressPMF3;
    sal_strncpy_s((char *) (action_info.name), "EgressParsingIndex", sizeof(action_info.name));
    SHR_IF_ERR_EXIT(bcm_field_action_create(unit, 0, &action_info, &action_id_egress_parsing_index));

    fg_info.nof_actions = 4;
    attach_info.payload_info.action_types[0] = fg_info.action_types[0] = action_id_parsing_start_type;
    attach_info.payload_info.action_types[1] = fg_info.action_types[1] = action_id_parsing_start_offset;
    attach_info.payload_info.action_types[2] = fg_info.action_types[2] = action_id_fwd_layer_index;
    attach_info.payload_info.action_types[3] = fg_info.action_types[3] = action_id_egress_parsing_index;

    fg_info.action_with_valid_bit[0] = FALSE;
    fg_info.action_with_valid_bit[1] = FALSE;
    fg_info.action_with_valid_bit[2] = FALSE;
    fg_info.action_with_valid_bit[3] = FALSE;

    sal_strncpy_s((char *) fg_info.name, "RCH_EXTENDED_ENCAP", sizeof(fg_info.name));
    SHR_IF_ERR_EXIT(bcm_field_group_add(unit, 0, &fg_info, &fg_id));

    attach_info.key_info.nof_quals = fg_info.nof_quals;
    attach_info.payload_info.nof_actions = fg_info.nof_actions;

    SHR_IF_ERR_EXIT(bcm_field_group_context_attach(unit, 0, fg_id, context_id, &attach_info));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
appl_dnx_field_rch_handle_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_IF_ERR_EXIT(appl_dnx_field_rch_extended_encap_init(unit));
    SHR_IF_ERR_EXIT(appl_dnx_field_rch_remove_init(unit));
exit:
    SHR_FUNC_EXIT;
}
/*
 * }
 */

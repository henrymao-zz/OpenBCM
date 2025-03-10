/*
 * Configuration example start:
 *
 * Test Scenario - start
  cint ../../../../src/examples/dnx/field/cint_field_range_qual.c
  cint
  int unit = 0;
  bcm_field_stage_t stage = bcmFieldStageIngressPMF1;
  bcm_field_context_t context_id = 0;
  cint_field_range_qual_l4_ops_main(unit, stage, context_id);
 * Test Scenario - end
 *
 * Configuration example end
 *
 * cint;
 * cint_reset();
 * exit;
 * cint ../../../src/examples/dnx/field/cint_field_range_qual.c
 * exit
 * ************************************************************************
 *
 * This CINT shows how to set a Range in L4 Dest and Src Port/Packet Header Size.
 * and use it as a qualifier.
 *
 * Configuration steps:
 * 1.Set a Range using bcm_field_range_set for needed Range Type(Packet Header Size or L4 SRC/DST Ports).
 * 2.Add a Fg with qualifier bcmFieldQualifyPacketLengthRangeCheck for packet header size and
 * bcmFieldQualifyL4PortRangeCheck for L4 SRC/DST ports.
 * 3.Attach the Fg to a context.
 * 4.Add an entry to the FG.
 *
 * Main functions:
 * cint_field_range_qual_packet_header_size_main(unit,stage,context_id);
 * cint_field_range_qual_l4_ops_main(unit,stage,context_id);
 *
 * Destroy function:
 * cint_field_range_qual_destroy(unit,stage,range_type,context_id);
 *
 */

/**
  * Global variables
  * {
  */
  /**
  * The entry_id. Used for creating and destroying the entry
  */
bcm_field_entry_t CINT_FIELD_RANGE_QUAL_ENTRY_ID;
/**
 * The range_info. Used for creating and destroying a range.
 */
bcm_field_range_info_t range_info;
/**
 * The ID of the FG. Used for creating and for deleting.
 */
bcm_field_group_t CINT_FIELD_RANGE_QUAL_FG_ID;
/**
 * The Range ID of the packet header size. Used for creating and reseting a range.
 */
bcm_field_range_t CINT_FIELD_RANGE_ID_PACKET_HEADER_SIZE = 1;
/**
 * The Range ID of L4 Ports. Used for creating and reseting a range.
 */
bcm_field_range_t CINT_FIELD_RANGE_ID_L4_PORT = 0;
/**
 * Global variables
 * }
 */
/**
 * \brief
 *
 *  This function sets all required HW
 *  configuration for bcm_field_group_add and bcm_field_group_context_attach
 *  and bcm_field_entry_add
 *  to be performed for IPMF1, IPMF2 and EPMF.
 *
 * \param [in] unit - The unit number.
 * \param [in] qual_type - The type of the qualifier used in the
 * bcm_field_group_add, bcm_field_group_context_attach, bcm_field_entry_add
 * \param [in] context_id - The ID of the context
 * \param [in] stage - The PMF stage
 * \param [in] qual_value - The value to qualify upon in the entry
 * \param [in] mask_value - The mask to qualify upon in the entry
 *
 * \return
 *  int - Error Type, in sense of bcm_error_t
 *
 */
int
cint_field_range_fg_create_context_attach_entry_add(
    int unit,
    bcm_field_qualify_t qual_type,
    bcm_field_context_t context_id,
    bcm_field_stage_t stage,
    uint32 qual_value,
    uint32 mask_value)
{
    bcm_field_group_info_t fg_info;
    bcm_field_group_attach_info_t attach_info;
    bcm_field_entry_info_t entry_info;
    void *dest_char;

    printf("Running: cint_field_range_fg_create_context_attach_entry_add()\n");

    bcm_field_group_info_t_init(&fg_info);

    fg_info.stage = stage;
    fg_info.fg_type = bcmFieldGroupTypeTcam;
    fg_info.nof_quals = 1;
    fg_info.nof_actions = 1;
    fg_info.qual_types[0] = qual_type;
    fg_info.action_types[0] = bcmFieldActionDropPrecedence;
    dest_char = &(fg_info.name[0]);
    sal_strncpy_s(dest_char, "range_qual_FG", sizeof(fg_info.name));
    /**
     * Add the FG.
     */
    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_add(unit, 0, &fg_info, &CINT_FIELD_RANGE_QUAL_FG_ID), "");


    bcm_field_group_attach_info_t_init(&attach_info);

    attach_info.key_info.nof_quals = 1;
    attach_info.payload_info.nof_actions = 1;
    attach_info.key_info.qual_types[0] = qual_type;
    attach_info.key_info.qual_info[0].input_type = bcmFieldInputTypeMetaData;
    attach_info.payload_info.action_types[0] = bcmFieldActionDropPrecedence;

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_context_attach(unit, 0, CINT_FIELD_RANGE_QUAL_FG_ID, context_id, &attach_info), "");


    bcm_field_entry_info_t_init(&entry_info);
    entry_info.priority = 1;

    entry_info.nof_entry_quals = 1;
    entry_info.entry_qual[0].type = qual_type;
    entry_info.entry_qual[0].value[0] = qual_value;
    entry_info.entry_qual[0].mask[0] = mask_value;

    entry_info.nof_entry_actions = 1;
    entry_info.entry_action[0].type = bcmFieldActionDropPrecedence;
    entry_info.entry_action[0].value[0] = BCM_FIELD_COLOR_YELLOW;

    BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_add(unit, 0, CINT_FIELD_RANGE_QUAL_FG_ID, &entry_info, &CINT_FIELD_RANGE_QUAL_ENTRY_ID), "");

    printf("FG %d was created and attached to the context %d\n", CINT_FIELD_RANGE_QUAL_FG_ID, context_id);

    return BCM_E_NONE;
}
/**
 *
 * \brief
 *
 *  This function sets the range for bcmFieldRangeTypePacketHeaderSize range type.
 *
 * \param [in] unit - The unit number.
 * \param [in] stage - The Field stage.
 * \param [in] context_id - The Id of the context
 *
 * \return
 *  int - Error Type, in sense of bcm_error_t
 */
int
cint_field_range_qual_packet_header_size_main(
    int unit,
    bcm_field_stage_t stage,
    bcm_field_context_t context_id)
{
    bcm_field_range_info_t range_info;
    uint32 qual_value;
    uint32 mask_value;

    printf("Running: cint_field_range_qual_packet_header_size_main()\n");
    /**
     * Init the fg_info structure.
     * Values are in Byte resolution
     */
    bcm_field_range_info_t_init(&range_info);
    range_info.range_type = bcmFieldRangeTypePacketHeaderSize;
    range_info.min_val = 75;
    range_info.max_val = 83;

    BCM_IF_ERROR_RETURN_MSG(bcm_field_range_set(unit, 0, stage, CINT_FIELD_RANGE_ID_PACKET_HEADER_SIZE, &range_info), "");

    /**
     * For packet_header_size ranges, qualifier is the value of the first range ID to which the packet_header_size fits.
     */
    qual_value = CINT_FIELD_RANGE_ID_PACKET_HEADER_SIZE;
    mask_value = 0x3;
    /**
     * Create a FG, attach it to a context and add an entry.
     */
    BCM_IF_ERROR_RETURN_MSG(cint_field_range_fg_create_context_attach_entry_add(unit, bcmFieldQualifyPacketLengthRangeCheck, context_id, stage, qual_value, mask_value), "");

    return BCM_E_NONE;
}
/**
 *
 * \brief
 *
 *  This function is setting a range for L4 Ops.
 *
 * \param [in] unit - The unit number.
 * \param [in] range_type - The type of the range set in the TCL test.
 * Can be bcmFieldRangeTypeL4SrcPort or bcmFieldRangeTypeL4DstPort
 * \param [in] stage - The field stage
 *
 * \return
 *  int - Error Type, in sense of bcm_error_t
 */
int
cint_field_range_qual_l4_ops_main(
    int unit,
    bcm_field_stage_t stage,
    bcm_field_context_t context_id)
{
    bcm_field_range_info_t range_info;
    uint32 qual_value;
    uint32 mask_value;
    printf("Running: cint_field_range_qual_l4_ops_main()\n");

    bcm_field_range_info_t_init(&range_info);
    range_info.range_type = bcmFieldRangeTypeL4SrcPort;
    range_info.min_val = 200;
    range_info.max_val = 2000;
    BCM_IF_ERROR_RETURN_MSG(bcm_field_range_set(unit, 0, stage, CINT_FIELD_RANGE_ID_L4_PORT, &range_info), "");


    bcm_field_range_info_t_init(&range_info);
    range_info.range_type = bcmFieldRangeTypeL4DstPort;
    range_info.min_val = 200;
    range_info.max_val = 2000;
    BCM_IF_ERROR_RETURN_MSG(bcm_field_range_set(unit, 0, stage, CINT_FIELD_RANGE_ID_L4_PORT, &range_info), "");

    /**
     * For L4 port ranges, the bit within the bitmap corresponding to a range_id is the range_id istelf.
     */
    qual_value = 1 << CINT_FIELD_RANGE_ID_L4_PORT;
    mask_value = 1 << CINT_FIELD_RANGE_ID_L4_PORT;
    /**
     * Create a FG, attach it to a context and add an entry.
     */
    BCM_IF_ERROR_RETURN_MSG(cint_field_range_fg_create_context_attach_entry_add(unit, bcmFieldQualifyL4PortRangeCheck, context_id, stage, qual_value, mask_value), "");

    return BCM_E_NONE;
}
/**
 * The destroy function of the test. It is deleting the whole configuration.
 *
 * \param [in] unit - The unit number.
 * \param [in] stage - The Field stage.
 * \param [in] context_id - The ID of the context.
 *
 *  \return
 *  int - Error Type, in sense of bcm_error_t.
 */
int
cint_field_range_qual_destroy(
    int unit,
    bcm_field_stage_t stage,
    bcm_field_range_type_t range_type,
    bcm_field_context_t context_id)
{
    /**
     *  Set the range with default values
     */
    if (range_type == bcmFieldRangeTypePacketHeaderSize)
    {
        bcm_field_range_info_t_init(&range_info);
        range_info.range_type = range_type;
        BCM_IF_ERROR_RETURN_MSG(bcm_field_range_set(unit, 0, stage, CINT_FIELD_RANGE_ID_PACKET_HEADER_SIZE, &range_info), "");

    }
    if (range_type == bcmFieldRangeTypeL4SrcPort || range_type == bcmFieldRangeTypeL4DstPort)
    {
        bcm_field_range_info_t_init(&range_info);
        range_info.range_type = bcmFieldRangeTypeL4SrcPort;
        BCM_IF_ERROR_RETURN_MSG(bcm_field_range_set(unit, 0, stage, CINT_FIELD_RANGE_ID_L4_PORT, &range_info), "");

        bcm_field_range_info_t_init(&range_info);
        range_info.range_type = bcmFieldRangeTypeL4DstPort;
        BCM_IF_ERROR_RETURN_MSG(bcm_field_range_set(unit, 0, stage, CINT_FIELD_RANGE_ID_L4_PORT, &range_info), "");

    }
    BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_delete(unit, CINT_FIELD_RANGE_QUAL_FG_ID, NULL, CINT_FIELD_RANGE_QUAL_ENTRY_ID), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_context_detach(unit, CINT_FIELD_RANGE_QUAL_FG_ID, context_id), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_delete(unit, CINT_FIELD_RANGE_QUAL_FG_ID), "");

    return BCM_E_NONE;
}

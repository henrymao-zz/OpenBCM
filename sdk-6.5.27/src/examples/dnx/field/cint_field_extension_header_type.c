 /*
 * Configuration example start:
 *
 * Test Scenario - start
  cint ../../../../src/examples/dnx/field/cint_field_extension_header_type.c
  cint;
  int unit = 0;
  bcm_field_context_t context_id = 0;
  uint32 ext_hdr_type = 4;
  cint_field_extension_header_type_main(unit, context_id, ext_hdr_type);
 * Test Scenario - end
 *
 * Configuration example end
 *
 *   Example of using bcmFieldQualifyExtensionHeaderType qualifier.
 *
 *   Configuration:
 *      1. Create Field group:
 *          Qualifer - IPv6 First Extension header
 *          Action - Update TC
 *      2. Attach field group to given context
 *      3. Add Entry with given ext_hdr_type
 */

int Cint_field_extension_header_type_tc_action_value = 6;

bcm_field_group_t Cint_field_extension_header_type_fg_id;
bcm_field_entry_t Cint_field_extension_header_type_entry_id;


/**
* \brief
*  Create a FG type TCAM with qualifier bcmFieldQualifyExtensionHeaderType
*  to show the usage of it.
* \param [in] unit        - Device Id
* \param [in] context_id  - Context to attach FG to
* \param [in] ext_hdr_type  - Extension header type value to qualify upon
* \return
*   int - Error Type
* \remark
*   * None
* \see
*   * None
*/
int cint_field_extension_header_type_main(
    int unit,
    bcm_field_context_t context_id,
    uint32 ext_hdr_type)
{
    bcm_field_group_info_t fg_info;
    bcm_field_group_attach_info_t attach_info;
    bcm_field_entry_info_t ent_info;
    void *dest_char;

    /** Create field group. */
    bcm_field_group_info_t_init(&fg_info);
    dest_char = &(fg_info.name[0]);
    sal_strncpy_s(dest_char, "ext_hdr_type_qual", sizeof(fg_info.name));
    fg_info.fg_type = bcmFieldGroupTypeTcam;
    fg_info.stage = bcmFieldStageIngressPMF1;

    /** Set quals */
    fg_info.nof_quals = 1;
    fg_info.qual_types[0] = bcmFieldQualifyExtensionHeaderType;
    /** Set actions */
    fg_info.nof_actions = 1;
    fg_info.action_types[0] = bcmFieldActionPrioIntNew;

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_add(unit, 0, &fg_info, &Cint_field_extension_header_type_fg_id), "");
    printf("Created TCAM field group (%d) in iPMF1 \n", Cint_field_extension_header_type_fg_id);

    bcm_field_group_attach_info_t_init(&attach_info);

    attach_info.key_info.nof_quals = fg_info.nof_quals;
    attach_info.payload_info.nof_actions = fg_info.nof_actions;
    attach_info.key_info.qual_types[0] = fg_info.qual_types[0]; 
    attach_info.payload_info.action_types[0] = fg_info.action_types[0];

    attach_info.key_info.qual_info[0].input_type = bcmFieldInputTypeLayerAbsolute;
    attach_info.key_info.qual_info[0].input_arg = 1;
    attach_info.key_info.qual_info[0].offset = 0;

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_context_attach(unit, 0, Cint_field_extension_header_type_fg_id, context_id, &attach_info), "");

    printf("Attached  FG (%d) to context (%d)\n", Cint_field_extension_header_type_fg_id, context_id);

    bcm_field_entry_info_t_init(&ent_info);
    ent_info.priority = 1;

    ent_info.nof_entry_quals = 1;
    ent_info.entry_qual[0].type = fg_info.qual_types[0];
    ent_info.entry_qual[0].value[0] = ext_hdr_type;
    ent_info.entry_qual[0].mask[0] = 0xff;

    ent_info.nof_entry_actions = 1;
    ent_info.entry_action[0].type = fg_info.action_types[0];
    ent_info.entry_action[0].value[0] = Cint_field_extension_header_type_tc_action_value;

    BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_add(unit, 0, Cint_field_extension_header_type_fg_id, &ent_info, &Cint_field_extension_header_type_entry_id), "");
    printf("Entry add: id:(0x%x) \n", Cint_field_extension_header_type_entry_id);
    
    return BCM_E_NONE;
}

/**
* \brief
*  Destroy all configuration done
* \param [in] unit        -  Device id
* \param [in] context_id        -  Context id
* \return
*   int - Error Type
* \remark
*   * None
* \see
*   * None
*/
int cint_field_extension_header_type_destroy(
    int unit,
    bcm_field_context_t context_id)
{
    bcm_field_entry_info_t ent_info;

    bcm_field_entry_info_t_init(&ent_info);
    BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_delete(unit, Cint_field_extension_header_type_fg_id, NULL, Cint_field_extension_header_type_entry_id), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_context_detach(unit,Cint_field_extension_header_type_fg_id, context_id), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_delete(unit, Cint_field_extension_header_type_fg_id), "");
    
    return BCM_E_NONE;
}


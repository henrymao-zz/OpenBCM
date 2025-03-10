/*
 * Configuration example start:
 *
 * Test Scenario - start
  cint ../../../../src/examples/dnx/field/cint_field_exem.c
  cint;
  int unit = 0;
  bcm_field_context_t context_id = 0;
  bcm_field_stage_t stage = bcmFieldStageIngressPMF1;
  int action_value = 2;
  cint_field_exem_main(unit, stage, context_id, action_value);
 * Test Scenario - end
 *
 * Configuration example end
 *
 *   This cint creates an EXEM field group for a specific stage, attaches it to a context and adds an entry to it.
 *   The function cint_field_exem_entry_update also shows an example of updating an exam entry.
 *
 */

/** Variables to save the object to be deleted.*/
bcm_field_group_t Cint_field_exem_fg_id;

int Cint_field_exem_ttl_value = 44;



 /**
* \brief
*  Updates the actions of an EXAM entry (the qualifiers cannot be updates for exact match, as there is no entry handle).
*  Disables the second action in the entry.
* \param [in] unit               - Device ID.
* \param [in] stage              - The field stage the field group was created in.
* \param [in] new_action_value_2 - Value to write to the second action in the entry.
* \return
*   int - Error Type
* \remark
*   * None
* \see
*   * None
*/
int cint_field_exem_entry_update(int unit, bcm_field_stage_t stage, int new_action_value_2)
{
 bcm_field_entry_info_t entry_info;
 int ii;
 

 bcm_field_entry_info_t_init(&entry_info);
 /* In order to identify the entry we update, we provide the same key information as when adding it. */
 /* Stage iPMF3 cannot qualify on the header, so it has one less qualifier.*/
 entry_info.nof_entry_quals = (stage != bcmFieldStageIngressPMF3)?(2):(1);
 entry_info.entry_qual[0].type = bcmFieldQualifyLayerRecordType;
 entry_info.entry_qual[0].value[0] = bcmFieldLayerTypeUdp;
 entry_info.entry_qual[1].type = bcmFieldQualifyIp4Ttl;
 entry_info.entry_qual[1].value[0] = Cint_field_exem_ttl_value;
 /* We change the value of the second action and remove the first action from the entry. */
 entry_info.nof_entry_actions = 1;
 entry_info.entry_action[0].type = bcmFieldActionDropPrecedence;
 entry_info.entry_action[0].value[0] = new_action_value_2;
 /* To update an entry, we set the flag BCM_FIELD_FLAG_UPDATE */
 BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_add(unit, BCM_FIELD_FLAG_UPDATE, Cint_field_exem_fg_id, &entry_info, NULL), "");

 return BCM_E_NONE;
  
}

 
 /**
 * \brief
 *  Configures EXEM field group, attaches it and adds an entry.
 * \param [in] unit           - Device ID.
 * \param [in] stage          - The field stage the field group is created in.
 * \param [in] context_id     - Context to attach FG to.
 * \param [in] action_value_1 - Value to write to the first action in the entry.
 * \param [in] action_value_2 - Value to write to the second action in the entry.
 * \return
 *   int - Error Type
 * \remark
 *   * None
 * \see
 *   * None
 */
 int cint_field_exem_main(int unit, bcm_field_stage_t stage, bcm_field_context_t context_id, int action_value_1, int action_value_2)
 {
    bcm_field_group_info_t fg_info;
    bcm_field_group_attach_info_t attach_info;
    bcm_field_entry_info_t entry_info;
    int ii;

    bcm_field_group_info_t_init(&fg_info);
    fg_info.fg_type = bcmFieldGroupTypeExactMatch;
    /* Stage iPMF3 cannot qualify on the header, so it has one less qualifier.*/
    fg_info.nof_quals = (stage != bcmFieldStageIngressPMF3)?(2):(1);
    fg_info.stage = stage;
    /* We provide the information for both qualifiers. if nof_quals==1, the second qualifier will be ignored.*/
    fg_info.qual_types[0] = bcmFieldQualifyLayerRecordType;
    fg_info.qual_types[1] = bcmFieldQualifyIp4Ttl;
    fg_info.nof_actions = 2;
    fg_info.action_types[0] = bcmFieldActionPrioIntNew;
    fg_info.action_types[1] = bcmFieldActionDropPrecedence;
    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_add(unit, 0, &fg_info, &Cint_field_exem_fg_id), "");
    
    bcm_field_group_attach_info_t_init(&attach_info);
    attach_info.key_info.nof_quals = fg_info.nof_quals;
    attach_info.payload_info.nof_actions = fg_info.nof_actions;
    for(ii = 0; ii < fg_info.nof_quals; ii++)
    {
        attach_info.key_info.qual_types[ii] = fg_info.qual_types[ii];
    }
    for(ii = 0; ii < fg_info.nof_actions; ii++)
    {
        attach_info.payload_info.action_types[ii] = fg_info.action_types[ii];
    }
    attach_info.key_info.qual_info[0].input_type = bcmFieldInputTypeLayerRecordsAbsolute;
    attach_info.key_info.qual_info[0].input_arg = 2;
    attach_info.key_info.qual_info[1].input_type = bcmFieldInputTypeLayerAbsolute;
    attach_info.key_info.qual_info[1].input_arg = 1;
    attach_info.key_info.qual_info[1].offset = 0;
    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_context_attach(unit, 0, Cint_field_exem_fg_id, context_id, &attach_info), "");

    printf("EXEM FG_ID(%d) was attached to context (%d) \n", Cint_field_exem_fg_id, context_id);

    bcm_field_entry_info_t_init(&entry_info);
    entry_info.nof_entry_quals = fg_info.nof_quals;
    entry_info.entry_qual[0].type = fg_info.qual_types[0];
    entry_info.entry_qual[0].value[0] = bcmFieldLayerTypeUdp;
    entry_info.entry_qual[1].type = fg_info.qual_types[1];
    entry_info.entry_qual[1].value[0] = Cint_field_exem_ttl_value;
    entry_info.nof_entry_actions = fg_info.nof_actions;
    entry_info.entry_action[0].type = fg_info.action_types[0];
    entry_info.entry_action[0].value[0] = action_value_1;
    entry_info.entry_action[1].type = fg_info.action_types[1];
    entry_info.entry_action[1].value[0] = action_value_2;
    BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_add(unit, 0, Cint_field_exem_fg_id, &entry_info, NULL), "");
        

    return BCM_E_NONE;
     
 }
 
/**
 * \brief
 *  Deletes the field group.
 * \param [in] unit        - Device ID.
 * \param [in] stage       - The field stage the field group is created in.
 * \param [in] context_id  - Context to detach FG from.
 * \return
 *   int - Error Type
 * \remark
 *   * None
 * \see
 *   * None
 */
int cint_field_exem_destroy(int unit, bcm_field_stage_t stage, bcm_field_context_t context_id)
{
    bcm_field_entry_qual_t entry_qual_info[BCM_FIELD_NUMBER_OF_QUALS_PER_GROUP];

    bcm_field_entry_qual_t_init(&(entry_qual_info[0]));
    entry_qual_info[0].type = bcmFieldQualifyLayerRecordType;
    entry_qual_info[0].value[0] = bcmFieldLayerTypeUdp;
    if (stage != bcmFieldStageIngressPMF3)
    {
        entry_qual_info[1].type = bcmFieldQualifyIp4Ttl;
        entry_qual_info[1].value[0] = Cint_field_exem_ttl_value;
    }
    BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_delete(unit, Cint_field_exem_fg_id, entry_qual_info, 0), "");
    printf("Deleted an entry of field group ID %d. Context %d.\n", Cint_field_exem_fg_id, context_id);

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_context_detach(unit, Cint_field_exem_fg_id, context_id), "");
    printf("Detach field group ID %d from context %d.\n", Cint_field_exem_fg_id, context_id);

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_delete(unit, Cint_field_exem_fg_id), "");
    printf("Delete field group ID %d.\n", Cint_field_exem_fg_id);
     
    return BCM_E_NONE;
}

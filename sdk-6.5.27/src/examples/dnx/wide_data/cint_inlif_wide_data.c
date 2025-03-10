/*
 * 
 This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 
 Copyright 2007-2022 Broadcom Inc. All rights reserved. File: cint_inlif_wide_data.c Purpose: example for IN-LIF wide data usage
 */

/*
 * 
 * Configuration:
 * 
 * Test Scenario - start
 * cint;
 * cint_reset();
 * exit;
  cint ../../../../src/examples/dnx/wide_data/cint_inlif_wide_data.c
  cint
  print run(); 
 * Test Scenario - end
 * 
 *  "Wide Data" Scenario configured in this cint (function inlif_wide_data_ac_mp__start_run):
 *  1. create AC-MP INGRESS and add WIDE_DATA flag: using API bcm_vlan_port_create 
 *      (contained flags:BCM_VLAN_PORT_CREATE_INGRESS_ONLY & BCM_VLAN_PORT_INGRESS_WIDE)     
 *  2. set the wide data for each IN-LIF gport_id, using API bcm_port_wide_data_set.
 *  3. Use the wide data as qualifier in the ingress PMF. 
 *      Set condition for VTT stage 1 or/and VTT stage 5. (Depend on the IN-LIF created: Native goes to VTT5, others to VTT1)
 *      Set an action.  
 *  Note: the wide data scenario is relevant for one of the following IN-LIF types:
 *      a. AC-MP INGRESS, using API bcm_vlan_port_create (flags contain: BCM_VLAN_PORT_CREATE_INGRESS_ONLY & BCM_VLAN_PORT_INGRESS_WIDE)
 *      b. AC-P2P INGRESS, using API bcm_vlan_port_create (flags contain: BCM_VLAN_PORT_INGRESS_WIDE)
 *      c. AC-NATIVE, using API bcm_vlan_port_create (flags contain BCM_VLAN_PORT_NATIVE & BCM_VLAN_PORT_INGRESS_WIDE)
 *      d. EXTENDER, using API bcm_extender_port_add (flags contain BCM_VLAN_PORT_INGRESS_WIDE)
 *
 *  "Wide Data Extension" Scenario configured in this cint (function inlif_wide_data_extension_ac_mp__start_run):
 *  1. create AC-MP INGRESS and add WIDE_DATA flag: using API bcm_vlan_port_create
 *      (contained flags:BCM_VLAN_PORT_CREATE_INGRESS_ONLY & BCM_VLAN_PORT_INGRESS_WIDE)
 *  2. set the wide data for each IN-LIF gport_id, using API bcm_port_wide_data_set.
 *  3. add in lif wide data extension entry using API bcm_switch_wide_data_extension_add
 *  4. Use the wide data extension as qualifier in the ingress PMF.
 *  Note: WIde data extension scenario is relevant just for AC INGRESS (VTT1 stage)
 */

/*  Main Struct  */
struct inlif_wide_data_param_s{
    uint64 wide_data;
    bcm_gport_t vlan_port_id;
    bcm_field_group_t acl_ipmf1_fg_id;
    bcm_field_entry_t ipmf1_entry_handle_1;
    bcm_field_entry_t ipmf1_entry_handle_2;    
};

inlif_wide_data_param_s g_inlif_wide_data;
int is_large_wide_data=0;   /*support 28 bits wide data*/
int create_udf_16lsb=0;     /*16lsb from contain0_24, 12msb from contain1_24*/

/* vlan_port_group_value used to select 16bits (at least) or 8bits wide data for AC MP:
 *      vlan_port_group_value=0: MP AC contains 16bits (at least) wide data
 *      vlan_port_group_value>0: MP AC contains 8bits wide data + protection include flush group
 */
int vlan_port_group_value=0;

/**
 * \brief - Initialization of main struct
 *  Function allow to re-write default values
 */
void
inlif_wide_data_init(
    uint32 wide_data)
{
    /** even though the sw api contain 64bits data, the max allowed is much smaller (defined by architecture) */
    COMPILER_64_ZERO(g_inlif_wide_data.wide_data);
    COMPILER_64_SET(g_inlif_wide_data.wide_data, 0x0, wide_data);
    g_inlif_wide_data.vlan_port_id = 0;
}

/**
* \brief - create AC-MP IN-LIF with wide data flag
*  \param [in] unit
*  \param [in] in_port
*  \param [in] vsi
*  \param [in] unit
*/
int
inlif_wide_data_ac_mp_create(
    int unit,
    int in_port,
    int vsi)
{
    bcm_vlan_port_t vlan_port;
    uint32 system_headers_mode = *(dnxc_data_get(unit,  "headers", "system_headers", "system_headers_mode", NULL));
    
    bcm_vlan_port_t_init(&vlan_port);
    vlan_port.port = in_port;
    vlan_port.vsi = vsi;
    vlan_port.criteria = BCM_VLAN_PORT_MATCH_PORT;

    /**JR mode*/
    if (system_headers_mode == 0)
    {
        vlan_port.flags = BCM_VLAN_PORT_INGRESS_WIDE;
    }
    else
    {
        vlan_port.flags = BCM_VLAN_PORT_INGRESS_WIDE;
    }
    
    /* 
     * Setting the group isn't required by the user for wide data purposes.
     * It's done only for the purpose of testing, in order ensure various of selected In-LIF format:
     * value 0 - large wide data (16 or 28 bits).
     * value 1 - short wide data (8bits starting from LSB user wide_data parameter),
     *          Note: On Q2A, VSI alway < 0x8000, so the group is needed to select between 8/16 bits.
     * value 32 - select XL LEARN INFO format, with 10 bits wide data
     *            (starting from bit 16 in user wide data -as set in API bcm_port_wide_data_set).

     */
     vlan_port.group = vlan_port_group_value;

    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_create(unit, &vlan_port), "");
    g_inlif_wide_data.vlan_port_id = vlan_port.vlan_port_id;
    return BCM_E_NONE;
}

/**
* \brief - function set an ingress acl rule.
*          qualifier type is bcmFieldQualifyAcInLifWideData or bcmFieldQualifyNativeAcInLifWideData
*          action is modify the DP value to BLACK.
*  \param [in] unit
*  \param [in] first_run - If TRUE configures the ACL, otherwise just adds a rule to an existing ACL.
*  \param [in] type - qualifier enum to determine the position of the qualifier wide data.
*                 possible values: bcmFieldQualifyAcInLifWideData/bcmFieldQualifyNativeAcInLifWideData
*  \param [in] mask_lo - specific bits which consider in the qualifier type.
*  \param [in] mask_hi - specific bits which consider in the qualifier type.
*  \param [in] data_lo - generic data used by the IN-LIF
*  \param [in] data_hi - generic data used by the IN-LIF
*  \param [in] ipmf1_context_id - iPMF1 context ID
*/
int inlif_wide_data_acl_run(
    int unit,
    int first_run,
    int type,
    uint32 mask_lo,
    uint32 mask_hi,
    uint32 data_lo,
    uint32 data_hi,
    bcm_field_context_t ipmf1_context_id)
{
    char error_msg[200]={0,};
    bcm_field_group_info_t fg_info;
    bcm_field_group_attach_info_t attach_info;
    bcm_field_entry_info_t entry_in_info;
    bcm_field_entry_t * entry_handle;

    entry_handle = (first_run == TRUE) ? &g_inlif_wide_data.ipmf1_entry_handle_1 : &g_inlif_wide_data.ipmf1_entry_handle_2;

    bcm_field_group_info_t_init(&fg_info);  
    fg_info.stage = bcmFieldStageIngressPMF1;
    fg_info.fg_type = bcmFieldGroupTypeTcam;
    fg_info.nof_quals = 1;
    fg_info.qual_types[0] = type;
    
    /**set the actions */
    fg_info.nof_actions = 1;
    fg_info.action_types[0] = bcmFieldActionDropPrecedence;
    
    if (first_run)
    {
        BCM_IF_ERROR_RETURN_MSG(bcm_field_group_add(unit, 0, &fg_info, &g_inlif_wide_data.acl_ipmf1_fg_id), "");

        /** prepare attach_info structure */
        bcm_field_group_attach_info_t_init(&attach_info);
        attach_info.key_info.nof_quals = fg_info.nof_quals;
        attach_info.payload_info.nof_actions = fg_info.nof_actions;
        attach_info.payload_info.action_types[0] = fg_info.action_types[0];

        attach_info.key_info.qual_types[0] = fg_info.qual_types[0];
        attach_info.key_info.qual_info[0].input_type = bcmFieldInputTypeMetaData;
        attach_info.key_info.qual_info[0].input_arg = 0;
    
        BCM_IF_ERROR_RETURN_MSG(bcm_field_group_context_attach(unit, 0, g_inlif_wide_data.acl_ipmf1_fg_id, ipmf1_context_id, &attach_info), "");
    }
    
    /** prepare entry_in_info structure */  
    bcm_field_entry_info_t_init(&entry_in_info);
    entry_in_info.priority = 2;
    entry_in_info.nof_entry_quals = 1;
    entry_in_info.nof_entry_actions = 1;    
    entry_in_info.entry_qual[0].type = fg_info.qual_types[0];
    entry_in_info.entry_qual[0].mask[0] = mask_lo;
    entry_in_info.entry_qual[0].value[0] = data_lo;
    if (type == bcmFieldQualifyAcInLifWideDataExtended)
    {
        entry_in_info.entry_qual[0].mask[1] = mask_hi;
        entry_in_info.entry_qual[0].value[1] = data_hi;
        entry_in_info.entry_qual[0].value[2] = 1; /** hit bit indication */
    }
    entry_in_info.entry_action[0].type = fg_info.action_types[0];
    /** set Dp=BLACK */
    entry_in_info.entry_action[0].value[0] = BCM_FIELD_COLOR_BLACK;
    snprintf(error_msg, sizeof(error_msg), "for context %d, fg_id %d", ipmf1_context_id, g_inlif_wide_data.acl_ipmf1_fg_id);
    BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_add(unit, 0, g_inlif_wide_data.acl_ipmf1_fg_id, &entry_in_info, entry_handle), error_msg);
    
    return BCM_E_NONE;
}
/**
* \brief - function do the following:
*           1. create AC-MP IN-LIF with wide data flag.
*           2. set wide data for the gport
*           3. create PMF rule based on the wide data. the rule is to change the DP to BLACK.
*           4. drop packets which have DP>= BLACK using ingress cosq API.
*  \param [in] unit
*  \param [in] in_port
*  \param [in] vsi
*  \param [in] unit
*  \param [in] wide_data - generic data used by the AC IN-LIF
*  \param [in] ipmf1_context_id - iPMF1 context ID
*/
int
inlif_wide_data_ac_mp__start_run(
    int unit,
    int in_port,
    int vsi,
    uint32 wide_data,
    bcm_field_context_t ipmf1_context_id)
{       
    uint64 data;

    printf("inlif_wide_data_ac_mp__start_run: unit=%d, in_port=%d, vsi=%d, wide_data=0x%X \n", 
            unit, in_port, vsi,wide_data);

    inlif_wide_data_init(wide_data);

    /** create AC MP basic bridge, using format that contain generic (wide) data */
    BCM_IF_ERROR_RETURN_MSG(inlif_wide_data_ac_mp_create(unit, in_port, vsi), "");
    
    /** set the wide data for the created gport */
    BCM_IF_ERROR_RETURN_MSG(bcm_port_wide_data_set(unit, g_inlif_wide_data.vlan_port_id, BCM_PORT_WIDE_DATA_INGRESS, 
                                g_inlif_wide_data.wide_data), "");
       
    /** configure acl rule based on wide data */
    BCM_IF_ERROR_RETURN_MSG(inlif_wide_data_acl_run(unit, 1, bcmFieldQualifyAcInLifWideData, 
            0xFFFFFFF, 0, COMPILER_64_LO(g_inlif_wide_data.wide_data), 0,
                                 ipmf1_context_id), "");
    
    /** drop packet which have DP >= 3 (BLACK) */
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_discard_set(unit, BCM_COSQ_DISCARD_ENABLE | BCM_COSQ_DISCARD_COLOR_BLACK), "");
    
    return BCM_E_NONE;
} 

/** Destroy ACL rule related  */
int inlif_wide_data_acl_destroy(int unit, int nof_entries, bcm_field_context_t ipmf1_context_id)
{
    char error_msg[200]={0,};
    bcm_field_context_t ctx;
    bcm_field_stage_t stage;

    if(nof_entries > 2)
    {
        printf("support up to two entries \n");
        return BCM_E_PARAM;        
    }
    if(nof_entries > 1)
    {
        snprintf(error_msg, sizeof(error_msg), "fg %d", g_inlif_wide_data.acl_ipmf1_fg_id);
        BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_delete(unit, g_inlif_wide_data.acl_ipmf1_fg_id, NULL, g_inlif_wide_data.ipmf1_entry_handle_2), error_msg);
    }
    snprintf(error_msg, sizeof(error_msg), "fg %d", g_inlif_wide_data.acl_ipmf1_fg_id);
    BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_delete(unit, g_inlif_wide_data.acl_ipmf1_fg_id, NULL, g_inlif_wide_data.ipmf1_entry_handle_1), error_msg);
    /** Sequence to destroy the context and delete the groups -
     *  for now is used the default context -  Cannot destroy
     *  context ID 0, since it is the default context */
    snprintf(error_msg, sizeof(error_msg), "fg %d from context %d", g_inlif_wide_data.acl_ipmf1_fg_id, ipmf1_context_id);
    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_context_detach(unit, g_inlif_wide_data.acl_ipmf1_fg_id, ipmf1_context_id), error_msg);
    snprintf(error_msg, sizeof(error_msg), "fg %d", g_inlif_wide_data.acl_ipmf1_fg_id);
    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_delete(unit, g_inlif_wide_data.acl_ipmf1_fg_id), error_msg);

    return BCM_E_NONE;
}

/**
* \brief - function do the following:
*           1. create AC-MP IN-LIF with wide data flag.
*           2. set wide data for the gport.
*           3. add wide data extension entry which extend the data size up to 58 bits.
*           3. create PMF rule based on the wide data extension value. the rule is to change the DP to BLACK.
*           4. drop packets which have DP>= BLACK using ingress cosq API.
*  \param [in] unit
*  \param [in] in_port
*  \param [in] vsi
*  \param [in] unit
*  \param [in] wide_data - generic data used by the AC IN-LIF
*  \param [in] wide_data_extension - extended data
*  \param [in] ipmf1_context_id - context_id in iPMF1.
*/
int
inlif_wide_data_extension_ac_mp__start_run(
    int unit,
    int in_port,
    int vsi,
    uint32 wide_data,
    uint32 wide_data_extension_lo,
    uint32 wide_data_extension_hi,
    bcm_field_context_t ipmf1_context_id)
{
    uint64 data;
    uint32 flags = 0;
    int mode;
    printf("inlif_wide_data_extension_ac_mp__start_run: unit=%d, in_port=%d, vsi=%d, wide_data=0x%X wide_data_extension={0x%X,0x%X}\n",
            unit, in_port, vsi,wide_data, wide_data_extension_hi, wide_data_extension_lo);

    inlif_wide_data_init(wide_data);

    /** create AC MP basic bridge, using format that contain generic (wide) data */
    BCM_IF_ERROR_RETURN_MSG(inlif_wide_data_ac_mp_create(unit, in_port, vsi), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_get(unit, bcmSwitchWideDataExtKeyMode, &mode),
        "type=bcmSwitchWideDataExtKeyMode");
    /** set the wide data extension  - key is the wide_data, result is the wide_data_extension value */
    bcm_switch_wide_data_extension_info_t info;
    if (mode == bcmSwitchWideDataExtKeyModeByWideData)
    {
        /** set the wide data for the created gport */
        BCM_IF_ERROR_RETURN_MSG(bcm_port_wide_data_set(unit, g_inlif_wide_data.vlan_port_id, BCM_PORT_WIDE_DATA_INGRESS,
                                    g_inlif_wide_data.wide_data), "");
        info.wide_data_key = wide_data;
    }
    else
    {
        info.gport_key = g_inlif_wide_data.vlan_port_id;
        flags |= BCM_SWITCH_WIDE_DATA_EXTENSION_GPORT_KEY;
    }

    COMPILER_64_SET(info.wide_data_result, wide_data_extension_hi, wide_data_extension_lo);
    BCM_IF_ERROR_RETURN_MSG(bcm_switch_wide_data_extension_add(unit, flags, &info), "");

    /** configure acl rule based on wide data extension */
    uint64 mask;
    /** qualifier format - {hitbit(1), data{58}} */
    BCM_IF_ERROR_RETURN_MSG(inlif_wide_data_acl_run(unit, 1, bcmFieldQualifyAcInLifWideDataExtended,
            0xFFFFFFFF, 0x7FFFFFF, wide_data_extension_lo, wide_data_extension_hi, ipmf1_context_id), "");

    /** drop packet which have DP >= 3 (BLACK) */
    BCM_IF_ERROR_RETURN_MSG(bcm_cosq_discard_set(unit, BCM_COSQ_DISCARD_ENABLE | BCM_COSQ_DISCARD_COLOR_BLACK), "");

    return BCM_E_NONE;
}

/*
 * Following cint is used for J2C and above...
 *
 */

bcm_field_presel_t ing_presel_id = 61;
bcm_field_entry_t ent_id;
bcm_field_group_t fg_id;
bcm_field_qualify_t qual_id, qual_id_1;
bcm_field_context_t ing_context_id;
int is_pmf_config=0;
/*
 * is_lif_update_after_arr variable to control additional logic.
 */
uint8 is_lif_update_after_arr=0;

int inlif_wide_data_general_create_udf_qual(int unit, bcm_field_qualify_t *udf_qual_id, char *qual_info)
{
    char error_msg[200]={0,};
    char qual_info_tmp[100];
    bcm_field_qualifier_info_create_t udf_qual_info;
    void *dest_char;

    bcm_field_qualifier_info_create_t_init(&udf_qual_info);
    if (is_large_wide_data) {
        udf_qual_info.size = create_udf_16lsb ? 16 : 12; /* support 28 bits wide-data */
        snprintf(qual_info_tmp, 100, "UDF Qual(%s): %s", create_udf_16lsb?"16lsb":"12msb", qual_info);
    } else {
        udf_qual_info.size = 8; /* alway 8 bits for each LIF type */
        snprintf(qual_info_tmp, 100, "UDF Qual(%s): %s", "8lsb", qual_info);
    }
    
    dest_char = &udf_qual_info.name[0];
    sal_strncpy_s(dest_char, qual_info_tmp, sizeof(udf_qual_info.name));

    snprintf(error_msg, sizeof(error_msg), "for %s", qual_info);
    BCM_IF_ERROR_RETURN_MSG(bcm_field_qualifier_create(unit, 0, &udf_qual_info, udf_qual_id), error_msg);
    return BCM_E_NONE;    
}

/*presel_id: hw index*/
int inlif_wide_data_general_presel(int unit, int presel_id)
{
    char error_msg[200]={0,};
    bcm_field_context_t context_id;
    bcm_field_context_info_t context_info;
    bcm_field_presel_entry_id_t presel_entry_id;
    bcm_field_presel_entry_data_t presel_entry_data;

    /*create context*/
    bcm_field_context_info_t_init(&context_info);
    snprintf(error_msg, sizeof(error_msg), "context for preset[%d]", presel_id);
    BCM_IF_ERROR_RETURN_MSG(bcm_field_context_create(unit, 0, bcmFieldStageIngressPMF1, &context_info, &context_id), error_msg);

    /*mapping traffic to context*/
    bcm_field_presel_entry_id_info_init(&presel_entry_id);
    presel_entry_id.presel_id = presel_id;
    presel_entry_id.stage = bcmFieldStageIngressPMF1;

    bcm_field_presel_entry_data_info_init(&presel_entry_data);
    presel_entry_data.context_id = context_id;
    presel_entry_data.entry_valid = TRUE;
    presel_entry_data.nof_qualifiers = 1;
    
    presel_entry_data.qual_data[0].qual_type = bcmFieldQualifyAcInLifWideData;
    presel_entry_data.qual_data[0].qual_arg = 0;
    presel_entry_data.qual_data[0].qual_value = 1;
    presel_entry_data.qual_data[0].qual_mask = 1;
    
    BCM_IF_ERROR_RETURN_MSG(bcm_field_presel_set(unit, 0, &presel_entry_id, &presel_entry_data), "");

    ing_context_id = context_id;
    return BCM_E_NONE;
}


int inlif_wide_data_general_pmf_clean(int unit, bcm_field_context_t context_id)
{
    bcm_field_presel_entry_id_t presel_entry_id;
    bcm_field_presel_entry_data_t presel_entry_data;

    BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_delete(unit, fg_id, NULL, ent_id), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_context_detach(unit, fg_id, context_id), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_delete(unit, fg_id), "");

    /*delete user-defined qualifiers*/
    BCM_IF_ERROR_RETURN_MSG(bcm_field_qualifier_destroy(unit, qual_id), "");

    /*clear presel entry and delete context*/
    /*
    char error_msg[200]={0,};
    bcm_field_presel_entry_id_info_init(&presel_entry_id);
    presel_entry_id.presel_id = ing_presel_id;
    presel_entry_id.stage = bcmFieldStageIngressPMF1;

    bcm_field_presel_entry_data_info_init(&presel_entry_data);
    presel_entry_data.entry_valid = FALSE;
    presel_entry_data.context_id = 0;
    snprintf(error_msg, sizeof(error_msg), "for Ingress context[%d]-presel_id[%d]", ing_context_id, ing_presel_id);
    BCM_IF_ERROR_RETURN_MSG(bcm_field_presel_set(unit, 0, &presel_entry_id, &presel_entry_data), error_msg);


    snprintf(error_msg, sizeof(error_msg), "for Ingress context %d", ing_context_id);
    BCM_IF_ERROR_RETURN_MSG(bcm_field_context_destroy(unit, bcmFieldStageIngressPMF1, ing_context_id), error_msg);
    */
    is_pmf_config=0;

    return BCM_E_NONE;
}

/***/
int inlif_wide_data_general_pmf_configure(int unit, int vtt_stage, int dest_port, uint32 wide_data, bcm_field_context_t ipmf1_context_id)
{

    bcm_field_group_info_t fg_info;
    bcm_field_group_attach_info_t attach_info;
    bcm_field_entry_info_t entry_info;
    void *dest_char;
    int sys_gport = 0;

    bcm_field_qualifier_info_get_t qual_info_get;

    if (is_pmf_config) {
        BCM_IF_ERROR_RETURN_MSG(inlif_wide_data_general_pmf_clean(unit, ing_context_id), "");
    }

    /*
    BCM_IF_ERROR_RETURN_MSG(inlif_wide_data_general_presel(unit, ing_presel_id), "");
    printf(">>>Pre-select set successfully!\n", qual_info_get.offset);
    */
    ing_context_id = ipmf1_context_id;

    /*create udf */
    BCM_IF_ERROR_RETURN_MSG(inlif_wide_data_general_create_udf_qual(unit, &qual_id, "wide-data"), "");

    /*Create FG*/
    bcm_field_group_info_t_init(&fg_info);  
    fg_info.stage = bcmFieldStageIngressPMF1;
    fg_info.fg_type = bcmFieldGroupTypeTcam;
    fg_info.nof_quals = 1;
    fg_info.qual_types[0] = bcmFieldQualifyPweInLifWideData;
    fg_info.nof_actions = 1;
    fg_info.action_types[0] = bcmFieldActionRedirect;

    dest_char = &fg_info.name[0];
    sal_strncpy_s(dest_char, "Wide-Data", sizeof(fg_info.name));
    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_add(unit, 0, &fg_info, &fg_id), "");
    printf("Create FG[%d] for inlif-wide-data!\n", fg_id);

    BCM_IF_ERROR_RETURN_MSG(bcm_field_qualifier_info_get(unit, bcmFieldQualifyPweInLifWideData, bcmFieldStageIngressPMF1, &qual_info_get), "");
    printf(">>>offset of PweInLifWideData is %d\n", qual_info_get.offset);
    
    bcm_field_group_attach_info_t_init(&attach_info);
    attach_info.key_info.nof_quals = fg_info.nof_quals;
    attach_info.key_info.qual_types[0] = fg_info.qual_types[0];
    attach_info.key_info.qual_info[0].input_type = bcmFieldInputTypeMetaData;
    attach_info.key_info.qual_info[0].input_arg = 0;

    if (is_lif_update_after_arr)
    {
        /*
         * Default mode: is_lif_update_after_arr = 1, always update wide data to 8msb
         */
         
        /*
         * UDF qual base is : bcmFieldQualifyAcInLifWideData
         * attach_info.key_info.qual_info[0].offset = qual_info_get.offset-(5-1)*8 + 12;
         */
    }
    else
    {
        /*
         * UDF qual offset calculation from container has following structure(lsb-->msb): 
         *  8b for VTT1, 8b for VTT2, 8b for VTT3, 8b VTT4 and 8b for VTT5.
         * UDF qual base is : bcmFieldQualifyAcInLifWideData
         */
        attach_info.key_info.qual_info[0].offset = qual_info_get.offset-(vtt_stage-1)*8 + 12;
    }
    
    
    printf(">>>UDF Qual offset is %d\n", attach_info.key_info.qual_info[0].offset);
    attach_info.payload_info.nof_actions = fg_info.nof_actions;
    attach_info.payload_info.action_types[0] = fg_info.action_types[0];

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_context_attach(unit, 0, fg_id, ing_context_id, &attach_info), "");


    BCM_GPORT_SYSTEM_PORT_ID_SET(sys_gport, dest_port);

    bcm_field_entry_info_t_init(&entry_info);
    entry_info.priority = 1;
    entry_info.nof_entry_quals = 1;
    entry_info.entry_qual[0].type = fg_info.qual_types[0];
    entry_info.entry_qual[0].value[0] = wide_data & 0xff;
    entry_info.entry_qual[0].mask[0] = 0xff;

    entry_info.nof_entry_actions = fg_info.nof_actions;
    entry_info.entry_action[0].type = fg_info.action_types[0];
    entry_info.entry_action[0].value[0] = sys_gport;
    
    BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_add(unit, 0, fg_id, &entry_info, &ent_id), "");
    printf("inlif_wide_data_general_pmf_configure successfully!\n");
    is_pmf_config=1;
    return BCM_E_NONE;
    
}


int inlif_wide_data_general_data_set(int unit, bcm_gport_t gport, uint32 data)
{
    uint64 wide_data;

    COMPILER_64_ZERO(wide_data);
    COMPILER_64_SET(wide_data, 0x0, data);

    BCM_IF_ERROR_RETURN_MSG(bcm_port_wide_data_set(unit, gport, BCM_PORT_WIDE_DATA_INGRESS, wide_data), "");

    return BCM_E_NONE;
}

/*
 * configure mpls service:
 *  - nof_labels: number of mpls tunnel label
 *  - always contain pwe label.
 */
int inlif_wide_data_mpls_service(int unit, int port1, int port2, int nof_labels)
{
    char error_msg[200]={0,};
    int ii, i;

    if (nof_labels > 3) 
    {
        printf(">>>Too many MPLS tunnel!\n");
        return -1;
    }

    init_default_vpls_params(unit);

    ac_port.port = port1;
    pwe_port.port = port2;

    /* add more term tunnel than default(one) if needed
     * 
     */
    if (nof_labels == 0) {
        mpls_term_tunnel[0].action = BCM_MPLS_SWITCH_ACTION_POP;
        mpls_term_tunnel[0].label = 0;
        /*pwe_port.mac_addr[5] = pwe_port.mac_addr[5] + nof_labels - 1;*/
    } else if ((nof_labels >= 1) && (nof_labels <=4)) {
        for (i = 0; i < nof_labels; i++) {
            mpls_term_tunnel[i].action = BCM_MPLS_SWITCH_ACTION_POP;
            mpls_term_tunnel[i].label = 6000+i;
        }
        /*pwe_port.mac_addr[5] = pwe_port.mac_addr[5] + nof_labels - 1;*/

    } else if (nof_labels == -1) {
        /* for VTT1, do nothing */
    } else {
        printf("Error, can't support too much tunnel label(max to 4)\n");
        return -1; 
    }    

    /** Configure control word to be used in case needed for special label */
    BCM_IF_ERROR_RETURN_MSG(bcm_switch_control_set(unit, bcmSwitchMplsPWControlWord, pwe_cw), "");

    /*
     * Configure AC and PWE ports
     */
    BCM_IF_ERROR_RETURN_MSG(vpls_configure_port_properties(unit, ac_port, 0 /* create_rif */ ), "ac_port");
    BCM_IF_ERROR_RETURN_MSG(vpls_configure_port_properties(unit, pwe_port, 1 /* create_rif */ ), "pwe_port");

    /*
     * create vlan based on the vsi (vpn) 
     */
    snprintf(error_msg, sizeof(error_msg), "Failed to create VLAN %d", vpn);
    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_create(unit, vpn), error_msg);
    pwe_term.forwarding_domain = vpn;

    /*
     * Configure L3 interfaces 
     */
    BCM_IF_ERROR_RETURN_MSG(vpls_create_l3_interfaces(unit, &pwe_port), "");

    /*
     * Configure an ARP entries
     */
    BCM_IF_ERROR_RETURN_MSG(vpls_create_arp_entry(unit, &pwe_port), "");
    printf("Going to load mpls_encap_tunnel[%d].l3_intf_id by 0x%08X\r\n", outer_mpls_tunnel_index, pwe_port.arp);
    mpls_encap_tunnel[outer_mpls_tunnel_index].l3_intf_id = pwe_port.arp;

    /*
     * Configure a push entry.
     */
    BCM_IF_ERROR_RETURN_MSG(vpls_create_mpls_tunnel(unit, mpls_encap_tunnel), "");
    pwe_port.tunnel_id = mpls_encap_tunnel[0].tunnel_id;

    /*
     * Configure fec entry 
     */
    BCM_IF_ERROR_RETURN_MSG(vpls_create_fec_entry(unit, ac_port.encap_fec_id, mpls_encap_tunnel[0].tunnel_id, pwe_port.port, 0), "");
    pwe_term.egress_tunnel_if = ac_port.encap_fec_id;

    /*
     * Configure a termination label for the ingress flow  
     */
    if (nof_labels > 0) {        
        BCM_IF_ERROR_RETURN_MSG(vpls_create_termination_stack(unit, mpls_term_tunnel), "");
    }

    /*
     * configure PWE tunnel - egress flow 
     */
    BCM_IF_ERROR_RETURN_MSG(vpls_mpls_port_add_encapsulation(unit, &pwe_encap), "");
    pwe_term.encap_id = pwe_encap.encap_id;

    /*
     * configure PWE tunnel - ingress flow 
     */
    BCM_IF_ERROR_RETURN_MSG(vpls_mpls_port_add_termination(unit, &pwe_term), "");

    /** define ac and pwe ports */
    
    /*AC also contain wide data*/
    is_contain_wide_data = 1;
    BCM_IF_ERROR_RETURN_MSG(vpls_vswitch_add_access_port(unit, &ac_port, vpn), "");

    /*
     * add l2 addresses to be defined as static - no learning needed
     */
    BCM_IF_ERROR_RETURN_MSG(vpls_l2_addr_add(unit, vpn, ac_port.mac_addr, pwe_term.mpls_port_id, ac_port.stat_id, ac_port.stat_pp_profile), "");
    BCM_IF_ERROR_RETURN_MSG(vpls_l2_addr_add(unit, vpn, ac_port.next_hop, ac_port.vlan_port_id, pwe_port.stat_id, pwe_port.stat_pp_profile), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_gport_add(unit, vpn, ac_port.port, BCM_VLAN_GPORT_ADD_INGRESS_ONLY), "for ac port");

    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_gport_add(unit, vpn, pwe_port.port, BCM_VLAN_GPORT_ADD_INGRESS_ONLY), "for pwe port");

    return BCM_E_NONE;
}


void inlif_wide_data_general_send_packet(int unit,int vtt_stage, int ac_port, int pw_port)
{
    char cmd[500] = {0};

    if (vtt_stage == 1) {
        snprintf(cmd, 500, "tx 1 psrc=%d data=000C0002000100000000cd1d91000005001100000112000c0002000091000005ffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20", ac_port);
    } else if (vtt_stage == 2) {
        snprintf(cmd, 500, "tx 1 psrc=%d data=000C0002000100000000cd1d81000005884700d80140001100000112000c0002000091000005ffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20", pw_port);
    } else if (vtt_stage == 3) {
        snprintf(cmd, 500, "tx 1 psrc=%d data=000C0002000100000000cd1d8100000588470177004000d80140001100000112000c0002000091000005ffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20", pw_port);
    } else if (vtt_stage == 4) {
        snprintf(cmd, 500, "tx 1 psrc=%d data=000C0002000100000000cd1d810000058847017700400177104000d80140001100000112000c0002000091000005ffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20", pw_port);
    } else if (vtt_stage == 5) {
        snprintf(cmd, 500, "tx 1 psrc=%d data=000C0002000100000000cd1d81000005884701770040017710400177204000d80140001100000112000c0002000091000005ffff000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20", pw_port);
    }
    bshell(unit, cmd);
}


/*
 *following test is on J2C and above

 * Test Scenario - start
 cint ../../../../src/examples/dnx/utility/cint_dnx_utils_global.c
 cint ../../../../src/examples/dnx/cint_dnx_ip_route_basic.c
 cint ../../../../src/examples/dnx/utility/cint_dnx_utils_vpls.c
 cint ../../../../src/examples/dnx/wide_data/cint_inlif_wide_data.c
 cint
 
 int unit = 0; 
 int rv = 0; 
 int in_port = 1018;
 int out_port = 1019;
 int redirect_port = 1020;
 int vtt_stage=5;
 print inlif_wide_data_general_service(unit,in_port,out_port, redirect_port, vtt_stage);
 exit;

 cint
 vtt_stage=1;
 print inlif_wide_data_general_pmf_configure(unit, vtt_stage, 1020, 0xab, ipmf1_context_id);
 print inlif_wide_data_general_data_set(unit, ac_port.vlan_port_id, 0xab);
 print inlif_wide_data_general_send_packet(unit, vtt_stage, in_port, out_port);
 exit;

 cint
 vtt_stage=2;
 print inlif_wide_data_general_pmf_configure(unit, vtt_stage, 1020, 0xef, ipmf1_context_id);
 print inlif_wide_data_general_send_packet(unit, vtt_stage, in_port, out_port);
 exit;

 cint
 vtt_stage=3;
 print inlif_wide_data_general_pmf_configure(unit, vtt_stage, 1020, 0xef, ipmf1_context_id);
 print inlif_wide_data_general_send_packet(unit, vtt_stage, in_port, out_port);
 exit;
 sig get name=dst
 
 cint
 vtt_stage=4;
 print inlif_wide_data_general_pmf_configure(unit, vtt_stage, 1020, 0xef, ipmf1_context_id);
 print inlif_wide_data_general_send_packet(unit, vtt_stage, in_port, out_port);
 exit;
 * Test Scenario - end


 */

int inlif_wide_data_general_service(int unit, int port1, int port2, int redirect_port, int vtt_stage, bcm_field_context_t ipmf1_context_id)
{
    char error_msg[200]={0,};
    uint32 wide_data=0;
    

    snprintf(error_msg, sizeof(error_msg), "for vtt - %d!", vtt_stage);
    BCM_IF_ERROR_RETURN_MSG(inlif_wide_data_mpls_service(unit,port1,port2,(vtt_stage-2)), error_msg);
    
    if ((vtt_stage > 1) && (vtt_stage <=5)) {
        wide_data = 0xef;
        BCM_IF_ERROR_RETURN_MSG(inlif_wide_data_general_data_set(unit, pwe_term.mpls_port_id, wide_data), error_msg);
        printf(">>>Set wide-data[%#x] for PWE[stage-%d]!\n", wide_data, vtt_stage);
    } else if (vtt_stage == 1) {
        wide_data = 0xab;
        BCM_IF_ERROR_RETURN_MSG(inlif_wide_data_general_data_set(unit, ac_port.vlan_port_id, wide_data), error_msg);
        printf(">>>Set wide-data[%#x] for AC[stage-%d]!\n", wide_data, vtt_stage);
    } else {
        printf("VTT stage[%d] can't support!\n", vtt_stage);
        return -1;
    }

    BCM_IF_ERROR_RETURN_MSG(inlif_wide_data_general_pmf_configure(unit, vtt_stage, redirect_port, wide_data, ipmf1_context_id), error_msg);

    /*optional to send packet*/
    /*
    inlif_wide_data_general_send_packet(unit, vtt_stage, port1, port2);
    */
    return BCM_E_NONE;
}


/*
 * Following cint is used for JR2 and above...
 *
 */

/*
 * ac_type: indicator for test type, the test is based on AC type.
 *
 *      0: P2MP with BCM_VLAN_PORT_MATCH_PORT
 *      1: P2MP with BCM_VLAN_PORT_MATCH_PORT_VLAN
 *      2: P2MP with BCM_VLAN_PORT_MATCH_PORT_CVLAN
 *      3: P2MP with BCM_VLAN_PORT_MATCH_PORT_VLAN_STACKED
 *      4: P2MP with BCM_VLAN_PORT_MATCH_PORT_SVLAN_STACKED
 *      5: P2MP with BCM_VLAN_PORT_MATCH_PORT_CVLAN_STACKED
 *      6: P2P with BCM_VLAN_PORT_MATCH_PORT
 *      7: P2P with BCM_VLAN_PORT_MATCH_PORT_VLAN
 *      8: P2P with BCM_VLAN_PORT_MATCH_PORT_CVLAN
 *      9: P2P with BCM_VLAN_PORT_MATCH_PORT_VLAN_STACKED
 *      10: P2P with BCM_VLAN_PORT_MATCH_PORT_SVLAN_STACKED
 *      11: P2P with BCM_VLAN_PORT_MATCH_PORT_CVLAN_STACKED
 *
 */
int ac_type=0;
int ac_type_pp_start_index = 6;
struct ac_info_s
{
    bcm_vlan_port_match_t criteria;
    bcm_gport_t port; 
    bcm_vlan_t match_vlan;
    bcm_vlan_t match_inner_vlan;
    uint32 flags;
};

ac_info_s large_ac_info[12] = {
/* from here - index 0 - the below LIFs are MP: */
    {BCM_VLAN_PORT_MATCH_PORT,              200, 0, 0, 0},
    {BCM_VLAN_PORT_MATCH_PORT_VLAN,         200, 10, 0, 0},
    {BCM_VLAN_PORT_MATCH_PORT_CVLAN,        200, 10, 0, 0},
    {BCM_VLAN_PORT_MATCH_PORT_VLAN_STACKED, 200, 10, 20, 0},
    {BCM_VLAN_PORT_MATCH_PORT_SVLAN_STACKED,200, 10, 20, 0},
    {BCM_VLAN_PORT_MATCH_PORT_CVLAN_STACKED,200, 10, 20, 0},
/* from here - index 6 - the below LIFs are P2P */
    {BCM_VLAN_PORT_MATCH_PORT,              200, 0, 0, 0},
    {BCM_VLAN_PORT_MATCH_PORT_VLAN,         200, 10, 0, 0},
    {BCM_VLAN_PORT_MATCH_PORT_CVLAN,        200, 10, 0, 0},
    {BCM_VLAN_PORT_MATCH_PORT_VLAN_STACKED, 200, 10, 20, 0},
    {BCM_VLAN_PORT_MATCH_PORT_SVLAN_STACKED,200, 10, 20, 0},
    {BCM_VLAN_PORT_MATCH_PORT_CVLAN_STACKED,200, 10, 20, 0}  
};


/*
 * \brief - Create AC according to test type.
 *
 *  \param [in] unit
 *  \param [in] vsi: vsi for AC
 *  \param [in] ac_type: ac type(test type)
 */
int inlif_large_wide_data_ac_create(int unit, int vsi, int ac_type, int redirect_port)
{
    bcm_vlan_port_t vlan_port;
    
    bcm_vlan_port_t_init(&vlan_port);
    vlan_port.port = large_ac_info[ac_type].port;
    vlan_port.vsi = vsi;
    vlan_port.criteria = large_ac_info[ac_type].criteria;
    vlan_port.match_vlan = large_ac_info[ac_type].match_vlan;
    vlan_port.match_inner_vlan = large_ac_info[ac_type].match_inner_vlan;

    /*
     * following field should set to 0 to select the 28bits result type:
     *      vlan_port.group=0;
     *      vlan_port.ingress_failover_port_id=0
     */
    
    vlan_port.flags = BCM_VLAN_PORT_CREATE_INGRESS_ONLY | BCM_VLAN_PORT_INGRESS_WIDE | large_ac_info[ac_type].flags;

    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_create(unit, vlan_port), "");
    g_inlif_wide_data.vlan_port_id = vlan_port.vlan_port_id;


    if (ac_type >= ac_type_pp_start_index)
    {
        /* P2P LIF - perfrom cross-connect to make it P2P LIF*/
        bcm_vswitch_cross_connect_t gports;

        bcm_vswitch_cross_connect_t_init(&gports);

        gports.port1 = vlan_port.vlan_port_id;
        gports.port2 = redirect_port;
        gports.flags = BCM_VSWITCH_CROSS_CONNECT_DIRECTIONAL;
        BCM_IF_ERROR_RETURN_MSG(bcm_vswitch_cross_connect_add(unit, &gports), "");


    }
    return BCM_E_NONE;
}


/*
 * \brief - Clean the PMF setting: delete FG / UDF / entry, detach context.
 *
 *  \param [in] unit
 */
int inlif_large_wide_data_pmf_clean(int unit, bcm_field_context_t ipmf1_context_id)
{
    bcm_field_presel_entry_id_t presel_entry_id;
    bcm_field_presel_entry_data_t presel_entry_data;

    BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_delete(unit, fg_id, NULL, ent_id), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_context_detach(unit, fg_id, ipmf1_context_id), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_delete(unit, fg_id), "");

    is_pmf_config=0;

    return BCM_E_NONE;
}


/**
* \brief - 
*       PMF configuration for 28 bits wide data.
*       8lsb use bcmFieldQualifyAcInLifWideData, 20 msb use UDF qualifier.
*  \param [in] unit
*  \param [in] dest_port: redirect port
*  \param [in] data: wide data to set
*  \param [in] mask: mask for wide data
*/
int inlif_large_wide_data_pmf_configure(int unit, int dest_port, uint32 data, uint32 mask, bcm_field_context_t ipmf1_context_id)
{
    bcm_field_group_info_t fg_info;
    bcm_field_group_attach_info_t attach_info;
    bcm_field_entry_info_t entry_info;
    void *dest_char;
    int sys_gport = 0;
    bcm_field_qualifier_info_get_t qual_info_get;

    if (is_pmf_config) {
        BCM_IF_ERROR_RETURN_MSG(inlif_large_wide_data_pmf_clean(unit, ipmf1_context_id), "");
    }

    /*Create FG*/
    bcm_field_group_info_t_init(&fg_info);  
    fg_info.stage = bcmFieldStageIngressPMF1;
    fg_info.fg_type = bcmFieldGroupTypeTcam;
    fg_info.nof_quals = 1;
    fg_info.qual_types[0] = bcmFieldQualifyAcInLifWideData;
    fg_info.nof_actions = 1;
    fg_info.action_types[0] = bcmFieldActionRedirect;

    dest_char = &fg_info.name[0];
    sal_strncpy_s(dest_char, "Wide-Data filter", sizeof(fg_info.name));
    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_add(unit, 0, &fg_info, &fg_id), "");
    
    bcm_field_group_attach_info_t_init(&attach_info);
    attach_info.key_info.nof_quals = fg_info.nof_quals;
    attach_info.key_info.qual_types[0] = fg_info.qual_types[0];
    attach_info.key_info.qual_info[0].input_type = bcmFieldInputTypeMetaData;
    attach_info.key_info.qual_info[0].input_arg = 0;

    attach_info.payload_info.nof_actions = fg_info.nof_actions;
    attach_info.payload_info.action_types[0] = fg_info.action_types[0];

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_context_attach(unit, 0, fg_id, ipmf1_context_id, &attach_info), "");
    printf("Create FG[%d] for inlif-wide-data!\n", fg_id);
    
    BCM_GPORT_SYSTEM_PORT_ID_SET(sys_gport, dest_port);    
    bcm_field_entry_info_t_init(&entry_info);
    entry_info.priority = 1;
    entry_info.nof_entry_quals = 1;
    entry_info.entry_qual[0].type = fg_info.qual_types[0];
    entry_info.entry_qual[0].value[0] = data;
    entry_info.entry_qual[0].mask[0] = mask;

    entry_info.nof_entry_actions = fg_info.nof_actions;
    entry_info.entry_action[0].type = fg_info.action_types[0];
    entry_info.entry_action[0].value[0] = sys_gport;
    
    BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_add(unit, 0, fg_id, &entry_info, &ent_id), "");
    printf("inlif_large_wide_data_general_pmf_configure successfully!\n");

    is_pmf_config = 1;
    
    return BCM_E_NONE;
}


/*
 * \brief - build and send packet on cint according to AC type.
 *
 *  \param [in] unit
 *  \param [in] ac_type: ac type(test type)
 */
void inlif_large_wide_data_general_send_packet(int unit, int ac_type)
{
    char cmd[500] = {0};
    uint16 tpid_inner, tpid_outer;

    if (large_ac_info[ac_type].criteria == BCM_VLAN_PORT_MATCH_PORT) {
        snprintf(cmd, 500,
            "tx 1 psrc=%d data=00000000001100000000002208004500002A0000000040FFF881C0A80002C0A80001000102030405060708090A0B0C0D0E0F101112131415161718191a1b1c1d1f", 
            large_ac_info[ac_type].port);
    } else if (large_ac_info[ac_type].criteria == BCM_VLAN_PORT_MATCH_PORT_VLAN) {
        tpid_outer = 0x9100;
        snprintf(cmd, 500,
            "tx 1 psrc=%d data=000000000011000000000022%x%04x4500002A0000000040FFF881C0A80002C0A80001000102030405060708090A0B0C0D0E0F101112131415161718191a1b1c1d1f", 
            large_ac_info[ac_type].port,
            tpid_outer,
            large_ac_info[ac_type].match_vlan);
    } else if (large_ac_info[ac_type].criteria == BCM_VLAN_PORT_MATCH_PORT_CVLAN) {
        tpid_outer = 0x8100;
        snprintf(cmd, 500,
            "tx 1 psrc=%d data=000000000011000000000022%x%04x08004500002A0000000040FFF881C0A80002C0A80001000102030405060708090A0B0C0D0E0F101112131415161718191a1b1c1d1f", 
            large_ac_info[ac_type].port,
            tpid_outer,
            large_ac_info[ac_type].match_vlan);

    } else if (large_ac_info[ac_type].criteria == BCM_VLAN_PORT_MATCH_PORT_VLAN_STACKED) {
        tpid_outer = 0x9100;
        tpid_inner = 0x8100;
        snprintf(cmd, 500,
            "tx 1 psrc=%d data=000000000011000000000022%x%04x%x%04x08004500002A0000000040FFF881C0A80002C0A80001000102030405060708090A0B0C0D0E0F101112131415161718191a1b1c1d1f", 
            large_ac_info[ac_type].port,
            tpid_outer,
            large_ac_info[ac_type].match_vlan,
            tpid_inner,
            large_ac_info[ac_type].match_inner_vlan);

    } else if (large_ac_info[ac_type].criteria == BCM_VLAN_PORT_MATCH_PORT_SVLAN_STACKED) {
        tpid_outer = 0x9100;
        tpid_inner = 0x9100;
        snprintf(cmd, 500,
            "tx 1 psrc=%d data=000000000011000000000022%x%04x%x%04x08004500002A0000000040FFF881C0A80002C0A80001000102030405060708090A0B0C0D0E0F101112131415161718191a1b1c1d1f", 
            large_ac_info[ac_type].port,
            tpid_outer,
            large_ac_info[ac_type].match_vlan,
            tpid_inner,
            large_ac_info[ac_type].match_inner_vlan);
    } else if (large_ac_info[ac_type].criteria == BCM_VLAN_PORT_MATCH_PORT_CVLAN_STACKED) {
        tpid_outer = 0x8100;
        tpid_inner = 0x8100;
        snprintf(cmd, 500,
            "tx 1 psrc=%d data=000000000011000000000022%x%04x%x%04x08004500002A0000000040FFF881C0A80002C0A80001000102030405060708090A0B0C0D0E0F101112131415161718191a1b1c1d1f", 
            large_ac_info[ac_type].port,
            tpid_outer,
            large_ac_info[ac_type].match_vlan,
            tpid_inner,
            large_ac_info[ac_type].match_inner_vlan);
    }

    bshell(unit, cmd);
}


uint32 cint_inlif_wide_data_val = 0xfaabbcd;
/*
 * \brief - Main config for 28 bits generic data for AC(test type=ac_type).
 *
 *  \param [in] unit
 *  \param [in] in_port: input port
 *  \param [in] vsi: vsi of AC
 *  \param [in] redirect_port: output port
 *  \param [in] ipmf1_context_id: The context used by iPMF1
 */
int inlif_large_wide_data_general_service(int unit, int in_port, int vsi, int redirect_port, bcm_field_context_t ipmf1_context_id)
{
    int i;

    for (i = 0; i < 12; i++) {
        large_ac_info[i].port = in_port;
    }

    if (!is_pmf_config)
    {
        inlif_wide_data_init(cint_inlif_wide_data_val);
    }
    
    if (is_pmf_config) {
        BCM_IF_ERROR_RETURN_MSG(bcm_vlan_port_destroy(unit, g_inlif_wide_data.vlan_port_id), "");
    }
    
    BCM_IF_ERROR_RETURN_MSG(inlif_large_wide_data_ac_create(unit, vsi, ac_type, redirect_port), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_port_wide_data_set(unit, g_inlif_wide_data.vlan_port_id, BCM_PORT_WIDE_DATA_INGRESS, g_inlif_wide_data.wide_data), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_vlan_gport_add(unit, large_ac_info[ac_type].match_vlan, in_port, BCM_VLAN_GPORT_ADD_INGRESS_ONLY), "");
    
    is_large_wide_data=1;
    BCM_IF_ERROR_RETURN_MSG(inlif_large_wide_data_pmf_configure(unit, redirect_port, cint_inlif_wide_data_val, 0xfffffff, ipmf1_context_id), "");

    return BCM_E_NONE;
}

/*
 * \brief - step test based on test type, including sending packet(test type=ac_type).
 *
 *  \param [in] unit
 *  \param [in] in_port: input port
 *  \param [in] vsi: vsi of AC
 *  \param [in] redirect_port: output port
 *  \param [in] test_ac_type: test type
 */
int inlif_large_wide_data_step_test(int unit, int in_port, int vsi, int redirect_port, int test_ac_type)
{
    ac_type = test_ac_type;

    BCM_IF_ERROR_RETURN_MSG(inlif_large_wide_data_general_service(unit, in_port, vsi, redirect_port), "");

    BCM_IF_ERROR_RETURN_MSG(inlif_large_wide_data_general_send_packet(unit, ac_type), "");

    return BCM_E_NONE;
}

/*
 * L3 fwd setting
 */
int inlif_large_wide_data_l3_fwd_config(int unit, int vsi, int out_port)
{
    int out_vsi = 200;         
    int fec_id;
    int vrf = 2;
    int encap_id = 0x1384;  
    bcm_mac_t in_vsi_mac_address = { 0x00, 0x0c, 0x00, 0x02, 0x00, 0x01 };     
    bcm_mac_t out_vsi_mac_address = { 0x00, 0x0c, 0x00, 0x02, 0x00, 0x02 };    
    bcm_mac_t arp_next_hop_mac = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05 };        
    int32 route = 0x7fffff00;
    uint32 host = 0x7fffff02;
    uint32 mask = 0xfffffff0;
    bcm_vlan_port_t egr_vp;
    bcm_gport_t g_out_port;
    
    if (BCM_GPORT_IS_TRUNK(out_port))
    {
        g_out_port = out_port;
    } else {
        BCM_GPORT_SYSTEM_PORT_ID_SET(g_out_port, out_port);
    }

    bcm_l3_intf_t l3if;
    bcm_l3_intf_t_init(&l3if);
    l3if.l3a_flags = BCM_L3_WITH_ID;
    l3if.l3a_mac_addr = in_vsi_mac_address;
    l3if.l3a_intf_id = l3if.l3a_vid = vsi;
    l3if.dscp_qos.qos_map_id = 0;
    BCM_IF_ERROR_RETURN_MSG(bcm_l3_intf_create(unit, l3if), "for ingress");

    bcm_l3_intf_t_init(&l3if);
    l3if.l3a_flags = BCM_L3_WITH_ID;
    l3if.l3a_mac_addr = out_vsi_mac_address;
    l3if.l3a_intf_id = l3if.l3a_vid = out_vsi;
    l3if.dscp_qos.qos_map_id = 0;
    BCM_IF_ERROR_RETURN_MSG(bcm_l3_intf_create(unit, l3if), "for egress");

    bcm_l3_ingress_t l3_ing_if;
    bcm_l3_ingress_t_init(&l3_ing_if);
    l3_ing_if.flags = BCM_L3_INGRESS_WITH_ID;      
    l3_ing_if.vrf = vrf;
    l3_ing_if.qos_map_id = 0;
    BCM_IF_ERROR_RETURN_MSG(bcm_l3_ingress_create(unit, l3_ing_if, vsi), "");

    bcm_l3_egress_t l3eg;
    bcm_if_t l3egid_null;       
    int arp_id;
    bcm_l3_egress_t_init(&l3eg);
    l3eg.mac_addr = arp_next_hop_mac;
    l3eg.encap_id = encap_id;
    l3eg.vlan = out_vsi;
    l3eg.flags = 0;
    l3eg.flags2 = 0;
    if (*dnxc_data_get(unit, "l3", "feature", "separate_fwd_rpf_dbs", NULL))
    {
        l3eg.flags2 |= BCM_L3_FLAGS2_FWD_ONLY;
    }
    BCM_IF_ERROR_RETURN_MSG(bcm_l3_egress_create(unit, BCM_L3_EGRESS_ONLY, &l3eg, &l3egid_null), "");

    arp_id = l3eg.encap_id;
    
    bcm_l3_egress_t_init(&l3eg);
    bcm_if_t l3egid;
    l3eg.intf = arp_id;
    l3eg.encap_id = 0;
    l3eg.failover_id = 0;
    l3eg.port = g_out_port;
    l3eg.flags = 0;
    if (*dnxc_data_get(unit, "l3", "feature", "separate_fwd_rpf_dbs", NULL))
    {
        l3eg.flags2 |= BCM_L3_FLAGS2_FWD_ONLY;
    }
    BCM_IF_ERROR_RETURN_MSG(bcm_l3_egress_create(unit, BCM_L3_INGRESS_ONLY, &l3eg, &fec_id), "");

    int _l3_itf;
    BCM_L3_ITF_SET(&_l3_itf, BCM_L3_ITF_TYPE_FEC, fec_id); 


    /** IPv4 */
    bcm_l3_route_t route_entry;
    if (!*dnxc_data_get(unit, "l3", "fwd", "host_entry_support", NULL))
    {
        bcm_l3_route_t_init(route_entry);
        route_entry.l3a_subnet = host;
        route_entry.l3a_ip_mask = 0xffffffff;
        route_entry.l3a_vrf = vrf;
        route_entry.l3a_intf = _l3_itf;
        route_entry.l3a_flags2 |= BCM_L3_FLAGS2_FWD_ONLY;
        BCM_IF_ERROR_RETURN_MSG(bcm_l3_route_add(unit, route_entry), "");
    }
    else
    {
        bcm_l3_host_t host_entry;
        bcm_l3_host_t_init(host_entry);
        host_entry.l3a_ip_addr = host;
        host_entry.l3a_vrf = vrf;
        host_entry.l3a_intf = _l3_itf;       /* FEC-ID or OUTRIF */
        host_entry.encap_id = 0;
        BCM_IF_ERROR_RETURN_MSG(bcm_l3_host_add(unit, host_entry), "for IPv4");
    }

    bcm_l3_route_t_init(route_entry);
    route_entry.l3a_subnet = route;
    route_entry.l3a_ip_mask = mask;
    route_entry.l3a_vrf = vrf;
    route_entry.l3a_intf = _l3_itf;
    if (*dnxc_data_get(unit, "l3", "feature", "separate_fwd_rpf_dbs", NULL))
    {
        route_entry.l3a_flags2 |= BCM_L3_FLAGS2_FWD_ONLY;
    }
    BCM_IF_ERROR_RETURN_MSG(bcm_l3_route_add(unit, route_entry), "for IPv4");

    /** IPv6 */
    uint8 ip6_subnet[16] = {0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03};
    uint8 ip6_mask[16] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    bcm_l3_route_t l3route;
    bcm_l3_route_t_init(&l3route);
    sal_memcpy(l3route.l3a_ip6_net, ip6_subnet, 16);
    sal_memcpy(l3route.l3a_ip6_mask, ip6_mask, 16);
    l3route.l3a_intf = _l3_itf;
    l3route.l3a_vrf = vrf;
    l3route.l3a_flags = BCM_L3_IP6;
    if (*dnxc_data_get(unit, "l3", "feature", "separate_fwd_rpf_dbs", NULL))
    {
        l3route.l3a_flags2 |= BCM_L3_FLAGS2_FWD_ONLY;
    }
    BCM_IF_ERROR_RETURN_MSG(bcm_l3_route_add(unit, &l3route), "for IPv6");

    /** MPLS */
    bcm_mpls_label_t ingress_label=1000;
    bcm_mpls_tunnel_switch_t info;
    bcm_mpls_tunnel_switch_t_init(&info);
    info.label = ingress_label;
    info.ingress_if = vsi;
    info.egress_if = _l3_itf;
    info.egress_label.label = 2000;
    info.action = BCM_MPLS_SWITCH_ACTION_SWAP;
    info.flags = BCM_MPLS_SWITCH_TTL_DECREMENT;
    BCM_IF_ERROR_RETURN_MSG(bcm_mpls_tunnel_switch_create(unit, &info), "");
    
    return BCM_E_NONE;
}


/*
 * \brief - test to monitor the containers are not overwritten by other stage .
 *
 *  \param [in] unit
 *  \param [in] in_port: input port
 *  \param [in] out_port: L3 forwarding dest port
 *  \param [in] vsi: vsi of AC
 *  \param [in] redirect_port: redirect port
 *  \param [in] ipmf1_context_id: Context ID used by iPMF1
 */
int inlif_large_wide_data_l3_test(int unit, int vsi, int in_port, int out_port, int redirect_port, bcm_field_context_t ipmf1_context_id)
{

    /*
     * config for Ipv4/IPv6/MPLS 
     */
    BCM_IF_ERROR_RETURN_MSG(inlif_large_wide_data_l3_fwd_config(unit, vsi, out_port), "");
    
    /*
     * Set In AC wide data
     */
    BCM_IF_ERROR_RETURN_MSG(inlif_large_wide_data_general_service(unit, in_port, vsi, redirect_port, ipmf1_context_id), "");

    return BCM_E_NONE;
}


/*
 * PMF configuration to test IPvX tunnel wide data
 */
int ip_tunnel_wide_data_general_pmf_configure(int unit, int dest_port, uint32 wide_data, bcm_field_context_t ipmf1_context_id)
{

    bcm_field_group_info_t fg_info;
    bcm_field_group_attach_info_t attach_info;
    bcm_field_entry_info_t entry_info;
    void *dest_char;
    int sys_gport = 0;

    bcm_field_qualifier_info_get_t qual_info_get;

    if (is_pmf_config) {
        BCM_IF_ERROR_RETURN_MSG(inlif_wide_data_general_pmf_clean(unit, ing_context_id), "");
    }

    ing_context_id = ipmf1_context_id;

    /*Create FG*/
    bcm_field_group_info_t_init(&fg_info);  
    fg_info.stage = bcmFieldStageIngressPMF1;
    fg_info.fg_type = bcmFieldGroupTypeTcam;
    fg_info.nof_quals = 1;
    fg_info.qual_types[0] = bcmFieldQualifyIpTunnelInLifWideData;
    fg_info.nof_actions = 1;
    fg_info.action_types[0] = bcmFieldActionRedirect;

    dest_char = &fg_info.name[0];
    sal_strncpy_s(dest_char, "Wide-Data", sizeof(fg_info.name));
    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_add(unit, BCM_FIELD_FLAG_MSB_RESULT_ALIGN, &fg_info, &fg_id), "");
    printf("Create FG[%d] for inlif-wide-data!\n", fg_id);
    
    bcm_field_group_attach_info_t_init(&attach_info);
    attach_info.key_info.nof_quals = fg_info.nof_quals;
    attach_info.key_info.qual_types[0] = fg_info.qual_types[0];
    attach_info.key_info.qual_info[0].input_type = bcmFieldInputTypeMetaData;
    attach_info.key_info.qual_info[0].input_arg = 0;    
    
    attach_info.payload_info.nof_actions = fg_info.nof_actions;
    attach_info.payload_info.action_types[0] = fg_info.action_types[0];

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_context_attach(unit, 0, fg_id, ing_context_id, &attach_info), "");


    BCM_GPORT_SYSTEM_PORT_ID_SET(sys_gport, dest_port);

    bcm_field_entry_info_t_init(&entry_info);
    entry_info.priority = 1;
    entry_info.nof_entry_quals = 1;
    entry_info.entry_qual[0].type = fg_info.qual_types[0];
    entry_info.entry_qual[0].value[0] = wide_data & 0x3ff;

    entry_info.entry_qual[0].mask[0] = 0x3ff;

    entry_info.nof_entry_actions = fg_info.nof_actions;
    entry_info.entry_action[0].type = fg_info.action_types[0];
    entry_info.entry_action[0].value[0] = sys_gport;
    
    BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_add(unit, 0, fg_id, &entry_info, &ent_id), "");
    printf("inlif_wide_data_general_pmf_configure successfully!\n");
    is_pmf_config=1;
    return BCM_E_NONE;    
}

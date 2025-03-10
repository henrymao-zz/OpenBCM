/*
 * Configuration example start:
 *
 * Test Scenario - start
  cint ../../../../src/examples/dnx/field/cint_field_sniff.c
  cint;
  int unit = 0;
  bcm_field_context_t context_id = 0;
  cint_field_sniff_ingress_main(unit, context_id);
 * Test Scenario - end
 *
 * Configuration example end
 *
 * Show an example how PMF can generate Sniff Commands in Ingress and Egress using TCAM FG, also allows to add entries
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

bcm_field_group_t   cint_field_sniff_ingress_fg_id = 0;
bcm_field_group_t   cint_field_sniff_egress_fg_id = 0;


bcm_field_group_info_t cinf_field_sniff_ingress_fg_info;
bcm_field_group_info_t cinf_field_sniff_egress_fg_info;


/**
* \brief
*  This Function adds entries to Created FG's
*  The function should be called once per stage and configure only one of possible SNIFF actions
*  All Sniff CMD should be encoded as GPORT
*  Condition port should also be encoded as GPORT
* \param [in] unit        -  Device id
* \param [in] condition_port        -  Source system port to qualify upon
* \param [in] is_mirror        -  Mirror command should be configures as action, in case set other is_xx should be false
* \param [in] mirror_cmd        -  Mirror command to perform as action
* \param [in] is_snoop        -  Snoop command should be configures as action, in case set other is_xx should be false
* \param [in] snoop_cmd        -  Snoop command to perform as action
* \param [in] is_ss        -  Statistical_Samp command should be configures as action, in case set other is_xx should be false
* \param [in] ss_cmd        -  Statistical_Samp command to perform as action
* \param [out] cint_field_sniff_ent_id        -  entry id of created entry in TCAM
* \return
*   int - Error Type
* \remark
*   * None
* \see
*   * None
*/
int cint_field_sniff_entry_add(int unit,int is_egress,
                    bcm_gport_t condition_port,
                    int is_mirror,  bcm_gport_t mirror_cmd,
                    int is_snoop,  bcm_gport_t snoop_cmd,
                    int is_ss,    bcm_gport_t ss_cmd, bcm_field_entry_t *cint_field_sniff_ent_id)
{

    bcm_field_entry_info_t ent_info;
    bcm_field_group_t   fg_id = 0;
    bcm_field_group_info_t *fg_info;
    int action_type;
    int entry_id;
    int action_iter = 0;

    printf("Params passed: is_egr: %d, condition_port: %d  \n   is_mirror %d mirror_cmd %d\n    is_snoop %d snoop_cmd %d \n    is_ss %d ss_cmd %d \n " ,
            is_egress, condition_port, is_mirror ,mirror_cmd , is_snoop , snoop_cmd ,is_ss , ss_cmd);
    if(is_egress)
    {
        fg_id = cint_field_sniff_egress_fg_id;
        fg_info = &cinf_field_sniff_egress_fg_info;
        printf("Adding Entry to the ePMF\n");

    }
    else
    {
        fg_id = cint_field_sniff_ingress_fg_id;
        fg_info = &cinf_field_sniff_ingress_fg_info;
        printf("Adding Entry to the iPMF1\n");
    }
    bcm_field_entry_info_t_init(&ent_info);
    ent_info.priority = 1;
    ent_info.nof_entry_quals = fg_info->nof_quals;
    ent_info.entry_qual[0].type = fg_info->qual_types[0];
    ent_info.entry_qual[0].value[0] = condition_port;
    ent_info.entry_qual[0].mask[0] = 0xffff;

    ent_info.nof_entry_actions = (is_mirror) + (is_snoop) + (is_ss);
    if(is_mirror)
    {
        ent_info.entry_action[action_iter].type = fg_info->action_types[0];
        ent_info.entry_action[action_iter].value[0] = mirror_cmd;
        action_type = ent_info.entry_action[action_iter].type;
        printf("Trying to add mirror_cmd: condition_port: 0x%x  \n type %d Value 0x%x \n " ,
                ent_info.entry_qual[0].value[0], action_type ,ent_info.entry_action[0].value[0]);
        action_iter++;
    }
    if (is_snoop)
    {

        ent_info.entry_action[action_iter].type = fg_info->action_types[1];
        ent_info.entry_action[action_iter].value[0] = snoop_cmd;
        action_type = ent_info.entry_action[action_iter].type;
        printf("Trying to add snoop_cmd: condition_port: 0x%x  \n type %d Value 0x%x \n " ,
                ent_info.entry_qual[0].value[0], action_type ,ent_info.entry_action[0].value[0]);
        action_iter++;
        if(is_egress)
        {
            ent_info.nof_entry_actions +=1;
            ent_info.entry_action[action_iter].type = fg_info->action_types[2];
            ent_info.entry_action[action_iter].value[0] = snoop_cmd;
        }
    }
    if (is_ss)
    {
        if(is_egress)
        {
            printf("Egress does not support Statistical Sampling\n");
            return BCM_E_CONFIG;
        }
        ent_info.entry_action[action_iter].type = fg_info->action_types[2];
        ent_info.entry_action[action_iter].value[0] = ss_cmd;
        action_type = ent_info.entry_action[action_iter].type;
        printf("Trying to add ss_cmd: condition_port: 0x%x  \n type %d Value 0x%x \n " ,
                ent_info.entry_qual[0].value[0], action_type,ent_info.entry_action[0].value[0]);
    }


    BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_add(unit, 0, fg_id, &ent_info, cint_field_sniff_ent_id), "");

    entry_id = *cint_field_sniff_ent_id;
    printf("Entry added: condition port: %d sniff_cmd %d entry_id %d\n" ,condition_port, ent_info.entry_action[0].value[0],entry_id);

    return BCM_E_NONE;
}

/**
* \brief
*  Destroy all configuration done.
* \param [in] unit        -  Device id
* \param [in] ipmf1_context_id  -  iPMF1 context
* \param [in] epmf_context_id  -  ePMF context
* \return
*   int - Error Type
* \remark
*   * None
* \see
*   * None
*/
int cint_field_sniff_destroy(int unit, bcm_field_context_t ipmf1_context_id, bcm_field_context_t epmf_context_id)
{
    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_context_detach(unit, cint_field_sniff_ingress_fg_id, ipmf1_context_id), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_delete(unit, cint_field_sniff_ingress_fg_id), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_context_detach(unit, cint_field_sniff_egress_fg_id, epmf_context_id), "");

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_delete(unit, cint_field_sniff_egress_fg_id), "");


    return BCM_E_NONE;
}


int pp_mirror_port = 13;
int pp_snoop_port = 14;
int pp_ss_port = 15;

bcm_gport_t condition_port = 0;
bcm_gport_t mirror_cmd = 0;
bcm_gport_t snoop_cmd = 0;
bcm_gport_t ss_cmd = 0;

/**
* \brief
*  Configures FG in IPMF1.
*  Qualifer is SRC_PORT and the actions are SNIFF Commands - Mirror, Snoop, Statistical Sampling
* \param [in] unit        -  Device id
* \param [in] ipmf1_context_id  -  iPMF1 context
* \return
*   int - Error Type
* \remark
*   * None
* \see
*   * None
*/
int cint_field_sniff_ingress_main(int unit, bcm_field_context_t ipmf1_context_id)
{
    bcm_field_group_attach_info_t attach_info;
    bcm_field_context_info_t context_info;
    bcm_field_action_info_t action_info;
    void *dest_char;

    /** Create and attach TCAM group in iPMF1 */
    bcm_field_group_info_t_init(&cinf_field_sniff_ingress_fg_info);
    cinf_field_sniff_ingress_fg_info.fg_type = bcmFieldGroupTypeTcam;
    cinf_field_sniff_ingress_fg_info.stage = bcmFieldStageIngressPMF1;
    cinf_field_sniff_ingress_fg_info.nof_quals = 1;
    cinf_field_sniff_ingress_fg_info.qual_types[0] = bcmFieldQualifySrcPort;
    cinf_field_sniff_ingress_fg_info.nof_actions = 3;
    cinf_field_sniff_ingress_fg_info.action_types[0] = bcmFieldActionMirrorIngress;
    cinf_field_sniff_ingress_fg_info.action_types[1] = bcmFieldActionSnoop;
    cinf_field_sniff_ingress_fg_info.action_types[2] = bcmFieldActionStatSampling;

    dest_char = &(cinf_field_sniff_ingress_fg_info.name[0]);
    sal_strncpy_s(dest_char, "Sniff Rx", sizeof(cinf_field_sniff_ingress_fg_info.name));
    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_add(unit, 0, &cinf_field_sniff_ingress_fg_info, &cint_field_sniff_ingress_fg_id), "");

    printf("IPMF1 Created\n");

    bcm_field_group_attach_info_t_init(&attach_info);

    attach_info.key_info.nof_quals = cinf_field_sniff_ingress_fg_info.nof_quals;
    attach_info.key_info.qual_types[0] = cinf_field_sniff_ingress_fg_info.qual_types[0];
    attach_info.payload_info.nof_actions = cinf_field_sniff_ingress_fg_info.nof_actions;
    attach_info.payload_info.action_types[0] = cinf_field_sniff_ingress_fg_info.action_types[0];
    attach_info.payload_info.action_types[1] = cinf_field_sniff_ingress_fg_info.action_types[1];
    attach_info.payload_info.action_types[2] = cinf_field_sniff_ingress_fg_info.action_types[2];

    attach_info.key_info.qual_info[0].input_type = bcmFieldInputTypeMetaData;

    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_context_attach(unit, 0, cint_field_sniff_ingress_fg_id, ipmf1_context_id, &attach_info), "");

    
    printf("IPMF1 FG attached\n");
    return BCM_E_NONE;
}

/**
* \brief
*  Configures FG in ePMF.
*  Qualifer is SRC_PORT and the actions are SNIFF Commands - Mirror, Snoop, Statistical Sampling
* \param [in] unit        -  Device id
* \param [in] epmf_context_id -  ePMF context
* \return
*   int - Error Type
* \remark
*   * None
* \see
*   * None
*/
int cint_field_sniff_egress_main(int unit, bcm_field_context_t epmf_context_id)
{

    bcm_field_group_attach_info_t attach_info;
    bcm_field_context_info_t context_info;
    bcm_field_action_info_t action_info;
    void *dest_char;

    /** Create and attach TCAM group in ePMF */
    bcm_field_group_info_t_init(&cinf_field_sniff_egress_fg_info);
    cinf_field_sniff_egress_fg_info.fg_type = bcmFieldGroupTypeTcam;
    cinf_field_sniff_egress_fg_info.stage = bcmFieldStageEgress;
    cinf_field_sniff_egress_fg_info.nof_quals = 1;
    cinf_field_sniff_egress_fg_info.qual_types[0] = bcmFieldQualifySrcPort;
    cinf_field_sniff_egress_fg_info.nof_actions = 3;
    cinf_field_sniff_egress_fg_info.action_types[0] = bcmFieldActionMirrorEgress;
    cinf_field_sniff_egress_fg_info.action_types[1] = bcmFieldActionSnoop;
    cinf_field_sniff_egress_fg_info.action_types[2] = bcmFieldActionSnoopStrength;

    dest_char = &(cinf_field_sniff_egress_fg_info.name[0]);
    sal_strncpy_s(dest_char, "Sniff Tx", sizeof(cinf_field_sniff_egress_fg_info.name));
    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_add(unit, 0, &cinf_field_sniff_egress_fg_info, &cint_field_sniff_egress_fg_id), "");

    printf("ePMF1 FG Created\n");

    bcm_field_group_attach_info_t_init(&attach_info);

    attach_info.key_info.nof_quals = cinf_field_sniff_egress_fg_info.nof_quals;
    attach_info.key_info.qual_types[0] = cinf_field_sniff_egress_fg_info.qual_types[0];
    attach_info.payload_info.nof_actions = cinf_field_sniff_egress_fg_info.nof_actions;
    attach_info.payload_info.action_types[0] = cinf_field_sniff_egress_fg_info.action_types[0];
    attach_info.payload_info.action_types[1] = cinf_field_sniff_egress_fg_info.action_types[1];
    attach_info.payload_info.action_types[2] = cinf_field_sniff_egress_fg_info.action_types[2];

    attach_info.key_info.qual_info[0].input_type = bcmFieldInputTypeMetaData;


    BCM_IF_ERROR_RETURN_MSG(bcm_field_group_context_attach(unit, 0, cint_field_sniff_egress_fg_id, epmf_context_id, &attach_info), "");

    
    printf("ePMF1 FG Attached\n");
    return BCM_E_NONE;
}

/**
* \brief
*  Example of how the main and destroy functions of ingress can be used
* \param [in] unit        -  Device id
* \param [in] destroy_conig - if TRUE the configuration that was made by example will be removed
* \param [in] ipmf1_context_id -  iPMF1 context
* \return
*   int - Error Type
* \remark
*   * None
* \see
*   * None
*/
int cint_field_sniff_ingress_config(int unit, int destroy_config, bcm_field_context_t ipmf1_context_id)
{
    /**Create entry in ingress pmf one for each type Mirror/Snoop/Statistical Sampling*/
    bcm_field_entry_t ipmf1_ent_id;
    bcm_gport_t snoop_gport;

    /**Creat TCAM field group in ingress PMF*/
    BCM_IF_ERROR_RETURN_MSG(cint_field_sniff_ingress_main(unit, ipmf1_context_id), "");


    int trap_id;
    BCM_IF_ERROR_RETURN_MSG(bcm_rx_trap_type_create(unit,0,bcmRxTrapUserDefine, &trap_id), "");

    bcm_rx_trap_config_t trap_config;
    bcm_rx_trap_config_t_init(&trap_config);
    trap_config.snoop_cmnd = BCM_GPORT_MIRROR_GET(snoop_cmd);
    BCM_IF_ERROR_RETURN_MSG(bcm_rx_trap_set(unit, trap_id, &trap_config), "");

    
    BCM_GPORT_TRAP_SET (snoop_gport, trap_id, 0, 7);

    /**Add 1 entry for Mirror,snoop,ss in ingress PMF*/
    BCM_IF_ERROR_RETURN_MSG(cint_field_sniff_entry_add(unit, FALSE, condition_port, TRUE, mirror_cmd, TRUE, snoop_gport, TRUE, ss_cmd, &ipmf1_ent_id), "");


    if(destroy_config)
    {
        BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_delete(unit,cint_field_sniff_ingress_fg_id,NULL,ipmf1_ent_id), "");

    }

    return BCM_E_NONE;
}

/**
* \brief
*  Example of how the main and destroy functions of egress can be used
* \param [in] unit        -  Device id
* \param [in] destroy_conig - if TRUE the configuration that was made by example will be removed
* \param [in] epmf_context_id - ePMF context
* \return
*   int - Error Type
* \remark
*   * None
* \see
*   * None
*/
int cint_field_sniff_egress_config(int unit, int destroy_config, bcm_field_context_t epmf_context_id)
{
    /**Create entry in egress pmf one for each type Mirror/Snoop (Statistical Sampling action not present in Egress)*/
    bcm_field_entry_t epmf_ent_id;
    bcm_gport_t snoop_gport;

    /**Creat TCAM field group in egress PMF*/
    BCM_IF_ERROR_RETURN_MSG(cint_field_sniff_egress_main(unit, epmf_context_id), "");


    int snoop_id = BCM_GPORT_MIRROR_GET(snoop_cmd);
    BCM_GPORT_TRAP_SET (snoop_gport, snoop_id, 0, 7);

    /**Add 1 entry for Mirror,snoop,ss in egress PMF*/
    BCM_IF_ERROR_RETURN_MSG(cint_field_sniff_entry_add(unit, TRUE, condition_port, TRUE, mirror_cmd, TRUE, snoop_gport, FALSE, ss_cmd, &epmf_ent_id), "");


    if(destroy_config)
    {
        BCM_IF_ERROR_RETURN_MSG(bcm_field_entry_delete(unit,cint_field_sniff_egress_fg_id,NULL,epmf_ent_id), "");

    }

    return BCM_E_NONE;
}

/**
* \brief
*  Exmaple of how the main and destroy functions can be used
* \param [in] unit        -  Device id
* \param [in] destroy_conig - if TRUE the configuration that was made by example will be removed
* \param [in] ipmf1_context_id - iPMF1 context
* \param [in] epmf_context_id - ePMF context
* \return
*   int - Error Type
* \remark
*   * None
* \see
*   * None
*/
int cint_field_sniff_example(int unit, int destroy_config, bcm_field_context_t ipmf1_context_id, bcm_field_context_t epmf_context_id)
{
    bcm_mirror_destination_t mirror_dest;
    bcm_mirror_destination_t snoop_dest;
    bcm_mirror_destination_t ss_dest;
    bcm_gport_t mirror_dest_port;
    bcm_gport_t snoop_dest_port;
    bcm_gport_t ss_dest_port;

    /** Mirror */
    bcm_mirror_destination_t_init(&mirror_dest);
    BCM_GPORT_SYSTEM_PORT_ID_SET(mirror_dest_port, pp_mirror_port);
    BCM_GPORT_LOCAL_SET(mirror_dest.gport, mirror_dest_port);
    BCM_GPORT_SYSTEM_PORT_ID_SET(condition_port, 1);
    BCM_IF_ERROR_RETURN_MSG(bcm_mirror_destination_create(unit,&mirror_dest), "");

    mirror_cmd = mirror_dest.mirror_dest_id;
    printf("Created Mirror Profile 0x%x \n",mirror_cmd);

    /** Snoop */
    bcm_mirror_destination_t_init(&snoop_dest);
    BCM_GPORT_SYSTEM_PORT_ID_SET(snoop_dest_port ,pp_snoop_port);
    BCM_GPORT_LOCAL_SET(snoop_dest.gport, snoop_dest_port);
    BCM_GPORT_SYSTEM_PORT_ID_SET(condition_port , 1);
    snoop_dest.flags |= BCM_MIRROR_DEST_IS_SNOOP;
    BCM_IF_ERROR_RETURN_MSG(bcm_mirror_destination_create(unit,&snoop_dest), "");

    snoop_cmd = snoop_dest.mirror_dest_id;
    printf("Created Snoop Profile 0x%x \n", snoop_cmd);    
    
    /** Statistical Sampling */
    bcm_mirror_destination_t_init(&ss_dest);
    BCM_GPORT_SYSTEM_PORT_ID_SET(ss_dest_port ,pp_ss_port);
    BCM_GPORT_LOCAL_SET(ss_dest.gport, ss_dest_port);
    BCM_GPORT_SYSTEM_PORT_ID_SET(condition_port , 1);
    ss_dest.flags |= BCM_MIRROR_DEST_IS_STAT_SAMPLE;
    BCM_IF_ERROR_RETURN_MSG(bcm_mirror_destination_create(unit,&ss_dest), "");

    ss_cmd = ss_dest.mirror_dest_id;
    printf("Created ss Profile 0x%x \n",ss_cmd);

    /** Configure Ingress PMF */
    BCM_IF_ERROR_RETURN_MSG(cint_field_sniff_ingress_config(unit, destroy_config, ipmf1_context_id), "");


    /** Configure Egress PMF */
    BCM_IF_ERROR_RETURN_MSG(cint_field_sniff_egress_config(unit, destroy_config, epmf_context_id), "");

    /** Destroy all configuration that was done */
    if(destroy_config)
    {
        BCM_IF_ERROR_RETURN_MSG(bcm_mirror_destination_destroy(unit,ss_cmd), "");
        BCM_IF_ERROR_RETURN_MSG(bcm_mirror_destination_destroy(unit,snoop_cmd), "");
        BCM_IF_ERROR_RETURN_MSG(bcm_mirror_destination_destroy(unit,mirror_cmd), "");
        BCM_IF_ERROR_RETURN_MSG(cint_field_sniff_destroy(unit,ipmf1_context_id,epmf_context_id), "");

    }
    return BCM_E_NONE;
}

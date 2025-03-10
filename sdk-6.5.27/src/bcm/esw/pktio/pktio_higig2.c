/*! \file pktio_higig2.c
 *
 * Higig2 access interface.
 *
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifdef INCLUDE_PKTIO
#include <pktio_dep.h>
#include <bcm/pktio.h>
#include <bcmpkt/bcmpkt_higig_defs.h>

/******************************************************************************
 * Local definitions
 ******************************************************************************/
#define BSL_LOG_MODULE BSL_LS_BCM_PKTIO

/*! Get a field from HG2 header. */
typedef uint32_t (*hg2_field_get_f)(uint32_t *hghdr);

/*! Set a field within HG2 header. */
typedef void (*hg2_field_set_f)(uint32_t *hghdr, uint32_t val);

/******************************************************************************
 * Private functions
 ******************************************************************************/
static uint32_t
pktio_hg2_start_get(uint32_t *hghdr)
{
    return HIGIG2_STARTf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_start_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_STARTf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_mcst_get(uint32_t *hghdr)
{
    return HIGIG2_MCSTf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_mcst_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_MCSTf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_tc_get(uint32_t *hghdr)
{
    return HIGIG2_TCf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_tc_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_TCf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_dest_modid_mgidh_get(uint32_t *hghdr)
{
    return HIGIG2_DST_MODID_MGIDHf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_dest_modid_mgidh_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_DST_MODID_MGIDHf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_dest_port_mgidl_get(uint32_t *hghdr)
{
    return HIGIG2_DST_PORT_MGIDLf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_dest_port_mgidl_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_DST_PORT_MGIDLf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_src_modid_get(uint32_t *hghdr)
{
    return HIGIG2_SRC_MODIDf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_src_modid_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_SRC_MODIDf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_src_port_get(uint32_t *hghdr)
{
    return HIGIG2_SRC_PIDf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_src_port_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_SRC_PIDf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_lbid_get(uint32_t *hghdr)
{
    return HIGIG2_LBIDf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_lbid_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_LBIDf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_dp_get(uint32_t *hghdr)
{
    return HIGIG2_DPf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_dp_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_DPf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ehv_get(uint32_t *hghdr)
{
    return HIGIG2_EHVf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ehv_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_EHVf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_cc_get(uint32_t *hghdr)
{
    return HIGIG2_CCf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_cc_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_CCf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd_type_get(uint32_t *hghdr)
{
    return HIGIG2_PPD_TYPEf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd_type_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD_TYPEf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_dst_t_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_DST_Tf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_dst_t_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_DST_Tf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_dst_tgid_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_DST_TGIDf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_dst_tgid_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_DST_TGIDf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_ingress_tagged_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_INGRESS_TAGGEDf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_ingress_tagged_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_INGRESS_TAGGEDf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_mirror_only_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_MIRROR_ONLYf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_mirror_only_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_MIRROR_ONLYf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_mirror_done_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_MIRROR_DONEf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_mirror_done_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_MIRROR_DONEf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_mirror_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_MIRRORf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_mirror_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_MIRRORf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_label_overlay_type_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_LABEL_OVERLAY_TYPEf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_label_overlay_type_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_LABEL_OVERLAY_TYPEf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_l3_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_L3f_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_l3_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_L3f_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_label_present_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_LABEL_PRESENTf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_label_present_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_LABEL_PRESENTf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_vc_label_19_16_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_VC_LABEL_19_16f_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_vc_label_19_16_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_VC_LABEL_19_16f_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_vc_label_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_VC_LABELf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_vc_label_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_VC_LABELf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_orig_src_modid_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_ORIG_SRC_MODIDf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_orig_src_modid_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_ORIG_SRC_MODIDf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_orig_src_port_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_ORIG_SRC_PORTf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_orig_src_port_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_ORIG_SRC_PORTf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_mirror_classification_tag_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_MIRROR_CLASSIFICATION_TAGf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_mirror_classification_tag_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_MIRROR_CLASSIFICATION_TAGf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_rep_id_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_REP_IDf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_rep_id_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_REP_IDf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_vid_high_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_VID_HIGHf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_vid_high_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_VID_HIGHf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_vid_low_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_VID_LOWf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_vid_low_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_VID_LOWf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_pfm_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_PFMf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_pfm_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_PFMf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_src_t_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_SRC_Tf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_src_t_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_SRC_Tf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_preserve_dscp_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_PRESERVE_DSCPf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_preserve_dscp_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_PRESERVE_DSCPf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_preserve_dot1p_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_PRESERVE_DOT1Pf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_preserve_dot1p_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_PRESERVE_DOT1Pf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_opcode_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_OPCODEf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_opcode_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_OPCODEf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd0_hdr_ext_len_get(uint32_t *hghdr)
{
    return HIGIG2_PPD0_HDR_EXT_LENf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd0_hdr_ext_len_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD0_HDR_EXT_LENf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd1_classification_tag_get(uint32_t *hghdr)
{
    return HIGIG2_PPD1_CLASSIFICATION_TAGf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd1_classification_tag_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD1_CLASSIFICATION_TAGf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd1_vid_high_get(uint32_t *hghdr)
{
    return HIGIG2_PPD1_VID_HIGHf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd1_vid_high_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD1_VID_HIGHf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd1_vid_low_get(uint32_t *hghdr)
{
    return HIGIG2_PPD1_VID_LOWf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd1_vid_low_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD1_VID_LOWf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd1_pfm_get(uint32_t *hghdr)
{
    return HIGIG2_PPD1_PFMf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd1_pfm_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD1_PFMf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd1_src_t_get(uint32_t *hghdr)
{
    return HIGIG2_PPD1_SRC_Tf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd1_src_t_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD1_SRC_Tf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd1_opcode_get(uint32_t *hghdr)
{
    return HIGIG2_PPD1_OPCODEf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd1_opcode_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD1_OPCODEf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd1_hdr_ext_len_get(uint32_t *hghdr)
{
    return HIGIG2_PPD1_HDR_EXT_LENf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd1_hdr_ext_len_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD1_HDR_EXT_LENf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd2_multipoint_get(uint32_t *hghdr)
{
    return HIGIG2_PPD2_MULTIPOINTf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd2_multipoint_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD2_MULTIPOINTf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd2_fwd_type_get(uint32_t *hghdr)
{
    return HIGIG2_PPD2_FWD_TYPEf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd2_fwd_type_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD2_FWD_TYPEf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd2_vni_mid_get(uint32_t *hghdr)
{
    return HIGIG2_PPD2_VNI_MIDf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd2_vni_mid_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD2_VNI_MIDf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd2_vni_low_get(uint32_t *hghdr)
{
    return HIGIG2_PPD2_VNI_LOWf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd2_vni_low_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD2_VNI_LOWf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd2_dest_vp_get(uint32_t *hghdr)
{
    return HIGIG2_PPD2_DEST_VPf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd2_dest_vp_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD2_DEST_VPf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd2_rep_id_15_0_get(uint32_t *hghdr)
{
    return HIGIG2_PPD2_REP_ID_15_0f_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd2_rep_id_15_0_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD2_REP_ID_15_0f_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd2_source_vp_get(uint32_t *hghdr)
{
    return HIGIG2_PPD2_SOURCE_VPf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd2_source_vp_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD2_SOURCE_VPf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd2_mirror_get(uint32_t *hghdr)
{
    return HIGIG2_PPD2_MIRRORf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd2_mirror_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD2_MIRRORf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd2_do_not_modify_get(uint32_t *hghdr)
{
    return HIGIG2_PPD2_DO_NOT_MODIFYf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd2_do_not_modify_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD2_DO_NOT_MODIFYf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd2_do_not_learn_get(uint32_t *hghdr)
{
    return HIGIG2_PPD2_DO_NOT_LEARNf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd2_do_not_learn_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD2_DO_NOT_LEARNf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd2_lag_failover_get(uint32_t *hghdr)
{
    return HIGIG2_PPD2_LAG_FAILOVERf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd2_lag_failover_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD2_LAG_FAILOVERf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd2_rep_id_17_16_get(uint32_t *hghdr)
{
    return HIGIG2_PPD2_REP_ID_17_16f_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd2_rep_id_17_16_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD2_REP_ID_17_16f_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd2_opcode_get(uint32_t *hghdr)
{
    return HIGIG2_PPD2_OPCODEf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd2_opcode_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD2_OPCODEf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd2_vni_high_get(uint32_t *hghdr)
{
    return HIGIG2_PPD2_VNI_HIGHf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd2_vni_high_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD2_VNI_HIGHf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd2_preserve_dscp_get(uint32_t *hghdr)
{
    return HIGIG2_PPD2_PRESERVE_DSCPf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd2_preserve_dscp_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD2_PRESERVE_DSCPf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd2_preserve_dot1p_get(uint32_t *hghdr)
{
    return HIGIG2_PPD2_PRESERVE_DOT1Pf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd2_preserve_dot1p_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD2_PRESERVE_DOT1Pf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd2_dest_type_get(uint32_t *hghdr)
{
    return HIGIG2_PPD2_DEST_TYPEf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd2_dest_type_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD2_DEST_TYPEf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd2_source_type_get(uint32_t *hghdr)
{
    return HIGIG2_PPD2_SOURCE_TYPEf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd2_source_type_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD2_SOURCE_TYPEf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd3_dta_container_get(uint32_t *hghdr)
{
    return HIGIG2_PPD3_PPD3_DATA_CONTAINERf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd3_dta_container_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD3_PPD3_DATA_CONTAINERf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd3_source_info_get(uint32_t *hghdr)
{
    return HIGIG2_PPD3_SOURCE_INFOf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd3_source_info_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD3_SOURCE_INFOf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd3_preserve_dscp_get(uint32_t *hghdr)
{
    return HIGIG2_PPD3_PRESERVE_DSCPf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd3_preserve_dscp_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD3_PRESERVE_DSCPf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd3_preserve_dot1p_get(uint32_t *hghdr)
{
    return HIGIG2_PPD3_PRESERVE_DOT1Pf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd3_preserve_dot1p_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD3_PRESERVE_DOT1Pf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd3_do_not_learn_get(uint32_t *hghdr)
{
    return HIGIG2_PPD3_DO_NOT_LEARNf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd3_do_not_learn_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD3_DO_NOT_LEARNf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd3_source_type_get(uint32_t *hghdr)
{
    return HIGIG2_PPD3_SOURCE_TYPEf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd3_source_type_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD3_SOURCE_TYPEf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd3_opcode_get(uint32_t *hghdr)
{
    return HIGIG2_PPD3_OPCODEf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd3_opcode_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD3_OPCODEf_SET(*(HIGIG2_t *)hghdr, val);
}

static uint32_t
pktio_hg2_ppd3_container_type_get(uint32_t *hghdr)
{
    return HIGIG2_PPD3_PPD3_CONTAINER_TYPEf_GET(*(HIGIG2_t *)hghdr);
}

static void
pktio_hg2_ppd3_container_type_set(uint32_t *hghdr, uint32_t val)
{
    HIGIG2_PPD3_PPD3_CONTAINER_TYPEf_SET(*(HIGIG2_t *)hghdr, val);
}

static hg2_field_get_f pktio_hg2_field_get[BCM_PKTIO_HG2_FID_COUNT] = {
    /* Common */
    pktio_hg2_start_get,
    pktio_hg2_mcst_get,
    pktio_hg2_tc_get,
    pktio_hg2_dest_modid_mgidh_get,
    pktio_hg2_dest_port_mgidl_get,
    pktio_hg2_src_modid_get,
    pktio_hg2_src_port_get,
    pktio_hg2_lbid_get,
    pktio_hg2_dp_get,
    pktio_hg2_ehv_get,
    pktio_hg2_cc_get,
    pktio_hg2_ppd_type_get,
    /* PPD0 */
    pktio_hg2_ppd0_dst_t_get,
    pktio_hg2_ppd0_dst_tgid_get,
    pktio_hg2_ppd0_ingress_tagged_get,
    pktio_hg2_ppd0_mirror_only_get,
    pktio_hg2_ppd0_mirror_done_get,
    pktio_hg2_ppd0_mirror_get,
    pktio_hg2_ppd0_label_overlay_type_get,
    pktio_hg2_ppd0_l3_get,
    pktio_hg2_ppd0_label_present_get,
    pktio_hg2_ppd0_vc_label_19_16_get,
    pktio_hg2_ppd0_vc_label_get,
    pktio_hg2_ppd0_rep_id_get,
    pktio_hg2_ppd0_orig_src_modid_get,
    pktio_hg2_ppd0_orig_src_port_get,
    pktio_hg2_ppd0_mirror_classification_tag_get,
    pktio_hg2_ppd0_vid_high_get,
    pktio_hg2_ppd0_vid_low_get,
    pktio_hg2_ppd0_pfm_get,
    pktio_hg2_ppd0_src_t_get,
    pktio_hg2_ppd0_preserve_dscp_get,
    pktio_hg2_ppd0_preserve_dot1p_get,
    pktio_hg2_ppd0_opcode_get,
    pktio_hg2_ppd0_hdr_ext_len_get,
    /* PPD1 */
    pktio_hg2_ppd1_classification_tag_get,
    pktio_hg2_ppd1_vid_high_get,
    pktio_hg2_ppd1_vid_low_get,
    pktio_hg2_ppd1_pfm_get,
    pktio_hg2_ppd1_src_t_get,
    pktio_hg2_ppd1_opcode_get,
    pktio_hg2_ppd1_hdr_ext_len_get,
    /* PPD2 */
    pktio_hg2_ppd2_multipoint_get,
    pktio_hg2_ppd2_fwd_type_get,
    pktio_hg2_ppd2_vni_mid_get,
    pktio_hg2_ppd2_vni_low_get,
    pktio_hg2_ppd2_dest_vp_get,
    pktio_hg2_ppd2_rep_id_15_0_get,
    pktio_hg2_ppd2_source_vp_get,
    pktio_hg2_ppd2_mirror_get,
    pktio_hg2_ppd2_do_not_modify_get,
    pktio_hg2_ppd2_do_not_learn_get,
    pktio_hg2_ppd2_lag_failover_get,
    pktio_hg2_ppd2_rep_id_17_16_get,
    pktio_hg2_ppd2_opcode_get,
    pktio_hg2_ppd2_vni_high_get,
    pktio_hg2_ppd2_preserve_dscp_get,
    pktio_hg2_ppd2_preserve_dot1p_get,
    pktio_hg2_ppd2_dest_type_get,
    pktio_hg2_ppd2_source_type_get,
    /* PPD3 */
    pktio_hg2_ppd3_dta_container_get,
    pktio_hg2_ppd3_source_info_get,
    pktio_hg2_ppd3_preserve_dscp_get,
    pktio_hg2_ppd3_preserve_dot1p_get,
    pktio_hg2_ppd3_do_not_learn_get,
    pktio_hg2_ppd3_source_type_get,
    pktio_hg2_ppd3_opcode_get,
    pktio_hg2_ppd3_container_type_get,
};

static hg2_field_set_f pktio_hg2_field_set[BCM_PKTIO_HG2_FID_COUNT] = {
    /* Common */
    pktio_hg2_start_set,
    pktio_hg2_mcst_set,
    pktio_hg2_tc_set,
    pktio_hg2_dest_modid_mgidh_set,
    pktio_hg2_dest_port_mgidl_set,
    pktio_hg2_src_modid_set,
    pktio_hg2_src_port_set,
    pktio_hg2_lbid_set,
    pktio_hg2_dp_set,
    pktio_hg2_ehv_set,
    pktio_hg2_cc_set,
    pktio_hg2_ppd_type_set,
    /* PPD0 */
    pktio_hg2_ppd0_dst_t_set,
    pktio_hg2_ppd0_dst_tgid_set,
    pktio_hg2_ppd0_ingress_tagged_set,
    pktio_hg2_ppd0_mirror_only_set,
    pktio_hg2_ppd0_mirror_done_set,
    pktio_hg2_ppd0_mirror_set,
    pktio_hg2_ppd0_label_overlay_type_set,
    pktio_hg2_ppd0_l3_set,
    pktio_hg2_ppd0_label_present_set,
    pktio_hg2_ppd0_vc_label_19_16_set,
    pktio_hg2_ppd0_vc_label_set,
    pktio_hg2_ppd0_rep_id_set,
    pktio_hg2_ppd0_orig_src_modid_set,
    pktio_hg2_ppd0_orig_src_port_set,
    pktio_hg2_ppd0_mirror_classification_tag_set,
    pktio_hg2_ppd0_vid_high_set,
    pktio_hg2_ppd0_vid_low_set,
    pktio_hg2_ppd0_pfm_set,
    pktio_hg2_ppd0_src_t_set,
    pktio_hg2_ppd0_preserve_dscp_set,
    pktio_hg2_ppd0_preserve_dot1p_set,
    pktio_hg2_ppd0_opcode_set,
    pktio_hg2_ppd0_hdr_ext_len_set,
    /* PPD1 */
    pktio_hg2_ppd1_classification_tag_set,
    pktio_hg2_ppd1_vid_high_set,
    pktio_hg2_ppd1_vid_low_set,
    pktio_hg2_ppd1_pfm_set,
    pktio_hg2_ppd1_src_t_set,
    pktio_hg2_ppd1_opcode_set,
    pktio_hg2_ppd1_hdr_ext_len_set,
    /* PPD2 */
    pktio_hg2_ppd2_multipoint_set,
    pktio_hg2_ppd2_fwd_type_set,
    pktio_hg2_ppd2_vni_mid_set,
    pktio_hg2_ppd2_vni_low_set,
    pktio_hg2_ppd2_dest_vp_set,
    pktio_hg2_ppd2_rep_id_15_0_set,
    pktio_hg2_ppd2_source_vp_set,
    pktio_hg2_ppd2_mirror_set,
    pktio_hg2_ppd2_do_not_modify_set,
    pktio_hg2_ppd2_do_not_learn_set,
    pktio_hg2_ppd2_lag_failover_set,
    pktio_hg2_ppd2_rep_id_17_16_set,
    pktio_hg2_ppd2_opcode_set,
    pktio_hg2_ppd2_vni_high_set,
    pktio_hg2_ppd2_preserve_dscp_set,
    pktio_hg2_ppd2_preserve_dot1p_set,
    pktio_hg2_ppd2_dest_type_set,
    pktio_hg2_ppd2_source_type_set,
    /* PPD3 */
    pktio_hg2_ppd3_dta_container_set,
    pktio_hg2_ppd3_source_info_set,
    pktio_hg2_ppd3_preserve_dscp_set,
    pktio_hg2_ppd3_preserve_dot1p_set,
    pktio_hg2_ppd3_do_not_learn_set,
    pktio_hg2_ppd3_source_type_set,
    pktio_hg2_ppd3_opcode_set,
    pktio_hg2_ppd3_container_type_set,
};
/******************************************************************************
 * Public functions
 ******************************************************************************/
int
bcmi_esw_pktio_hg2_fid_support_get(int unit, bcm_pktio_bitmap_t *support)
{
    int i = 0;

    SHR_FUNC_ENTER(unit);

    SHR_NULL_CHECK(support, SHR_E_PARAM);

    for (i = BCM_PKTIO_HG2_FID_START; i < BCM_PKTIO_HG2_FID_COUNT; i++) {
        SHR_BITSET(support->pbits, i);
    }

exit:
    SHR_FUNC_EXIT();
}

int
bcmi_esw_pktio_hg2_field_get(
    int unit,
    uint32_t *hghdr,
    int fid,
    uint32_t *val)
{
    SHR_FUNC_ENTER(unit);

    SHR_NULL_CHECK(hghdr, SHR_E_PARAM);
    SHR_NULL_CHECK(val, SHR_E_PARAM);
    if (fid < BCM_PKTIO_HG2_FID_START || fid >= BCM_PKTIO_HG2_FID_COUNT) {
        SHR_RETURN_VAL_EXIT(SHR_E_PARAM);
    }

    *val = pktio_hg2_field_get[fid](hghdr);

exit:
    SHR_FUNC_EXIT();
}

int
bcmi_esw_pktio_hg2_field_set(
    int unit,
    uint32_t *hghdr,
    int fid,
    uint32_t val)
{
    SHR_FUNC_ENTER(unit);

    SHR_NULL_CHECK(hghdr, SHR_E_PARAM);
    if (fid < BCM_PKTIO_HG2_FID_START || fid >= BCM_PKTIO_HG2_FID_COUNT) {
        SHR_RETURN_VAL_EXIT(SHR_E_PARAM);
    }

    pktio_hg2_field_set[fid](hghdr, val);

exit:
    SHR_FUNC_EXIT();
}

#endif /* INCLUDE_PKTIO */

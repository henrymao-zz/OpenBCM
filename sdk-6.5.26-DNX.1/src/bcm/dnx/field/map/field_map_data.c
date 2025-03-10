/** \file field_map_data.c
 * 
 *
 * Data for bcm to dnx and dnx to HW mapping
 *
 * This file implements mapping from BCM to DNX qualifiers and access for per DNX qualifier/action information
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_FLDPROCDNX
/*
 * Include files.
 * {
 */

#include <soc/sand/shrextend/shrextend_debug.h>
#include <shared/utilex/utilex_rhlist.h>
#include <bcm_int/dnx/field/field_map.h>
#include <soc/dnx/utils/dnx_pp_programmability_utils.h>
#include <soc/dnx/swstate/auto_generated/access/dnx_field_access.h>
#include <soc/dnx/dbal/dbal_string_mgmt.h>

#include "field_map_local.h"
/*
 * }Include files
 */

/* *INDENT-OFF* */
const dnx_field_context_param_t context_param_set[bcmFieldContextParamCount][bcmFieldStageCount] = {
    [bcmFieldContextParamTypeSystemHeaderProfile] = {
        [bcmFieldStageIngressPMF1] = {  DBAL_TABLE_FIELD_IPMF1_CONTEXT_GENERAL,
                                        {DBAL_FIELD_FIELD_PMF_CTX_ID},
                                        {DBAL_FIELD_SYSTEM_HEADER_PROFILE},
                                        dnx_field_convert_context_sys_header_profile},
    },
    [bcmFieldContextParamTypeKeyVal] = {
        [bcmFieldStageIngressPMF1] = {  DBAL_TABLE_FIELD_PMF_CONTEXT_GENERAL,
                                        {DBAL_FIELD_FIELD_PMF_CTX_ID, DBAL_FIELD_FIELD_PMF_STAGE},
                                        {DBAL_FIELD_PROGRAM_KEY_GEN_VAR},
                                        dnx_field_convert_context_param_key_val},
        [bcmFieldStageIngressPMF3] = {  DBAL_TABLE_FIELD_PMF_CONTEXT_GENERAL,
                                        {DBAL_FIELD_FIELD_PMF_CTX_ID, DBAL_FIELD_FIELD_PMF_STAGE},
                                        {DBAL_FIELD_PROGRAM_KEY_GEN_VAR},
                                        dnx_field_convert_context_param_key_val},
    },
    [bcmFieldContextParamTypeSystemHeaderStrip] = {
        [bcmFieldStageIngressPMF2] = {  DBAL_TABLE_FIELD_IPMF2_CONTEXT_GENERAL,
                                        {DBAL_FIELD_FIELD_PMF_CTX_ID},
                                        {DBAL_FIELD_NUM_LAYERS_TO_REMOVE, DBAL_FIELD_NUM_BYTES_TO_REMOVE},
                                        dnx_field_convert_context_param_header_strip}
    },
    [bcmFieldContextParamTypeFlushLearnEnable] = {
        [bcmFieldStageIngressPMF2] = {  DBAL_TABLE_FIELD_PMF_ELEPHANT_LEARN_CFG,
                                        {DBAL_FIELD_FIELD_PMF_CTX_ID},
                                        {DBAL_FIELD_ELEPHANT_LEARN_ENABLE},
                                        dnx_field_convert_context_param_learn_enable}
    },
};

const dnx_field_range_map_t range_map_legacy[DNX_FIELD_RANGE_TYPE_NOF][DNX_FIELD_STAGE_NOF] = {
    [DNX_FIELD_RANGE_TYPE_L4_SRC_PORT] = {
        [DNX_FIELD_STAGE_IPMF1] =    {"L4SRC",
                                       DBAL_TABLE_FIELD_IPMF1_L4_OPS_RANGES,
                                       DBAL_FIELD_FIELD_PMF_RANGE_ID,
                                       DBAL_FIELD_MIN_SRC_L4_PORT ,DBAL_FIELD_MAX_SRC_L4_PORT,
                                       FALSE,
                                     },
        [DNX_FIELD_STAGE_EPMF] =     {"L4SRC",
                                       DBAL_TABLE_FIELD_EPMF_L4_OPS_RANGES,
                                       DBAL_FIELD_FIELD_PMF_RANGE_ID,
                                       DBAL_FIELD_MIN_SRC_L4_PORT ,DBAL_FIELD_MAX_SRC_L4_PORT,
                                       FALSE,
                                      },
    },
    [DNX_FIELD_RANGE_TYPE_L4_DST_PORT] = {
        [DNX_FIELD_STAGE_IPMF1] =    {"L4DST",
                                       DBAL_TABLE_FIELD_IPMF1_L4_OPS_RANGES,
                                       DBAL_FIELD_FIELD_PMF_RANGE_ID,
                                       DBAL_FIELD_MIN_DEST_L4_PORT ,DBAL_FIELD_MAX_DEST_L4_PORT,
                                       FALSE,
                                     },
        [DNX_FIELD_STAGE_EPMF] =     {"L4DST",
                                       DBAL_TABLE_FIELD_EPMF_L4_OPS_RANGES,
                                       DBAL_FIELD_FIELD_PMF_RANGE_ID,
                                       DBAL_FIELD_MIN_DEST_L4_PORT ,DBAL_FIELD_MAX_DEST_L4_PORT,
                                       FALSE,
                                      },
    },
    [DNX_FIELD_RANGE_TYPE_OUT_LIF] = {
        [DNX_FIELD_STAGE_IPMF1] =    {"OutLif",
                                       DBAL_TABLE_FIELD_IPMF1_OUT_LIF_RANGES,
                                       DBAL_FIELD_FIELD_PMF_RANGE_ID,
                                       DBAL_FIELD_OUT_LIF_RANGE_MIN_N, DBAL_FIELD_OUT_LIF_RANGE_MAX_N,
                                       TRUE,
                                     },
        [DNX_FIELD_STAGE_IPMF3] =    {"OutLif",
                                      DBAL_TABLE_FIELD_IPMF3_OUT_LIF_RANGES,
                                      DBAL_FIELD_FIELD_PMF_RANGE_ID,
                                      DBAL_FIELD_OUT_LIF_RANGE_MIN_N, DBAL_FIELD_OUT_LIF_RANGE_MAX_N,
                                      TRUE,
                                      }
    },
    [DNX_FIELD_RANGE_TYPE_PKT_HDR_SIZE] = {
        [DNX_FIELD_STAGE_IPMF1] =    {"PktHeaderSize",
                                       DBAL_TABLE_FIELD_IPMF1_PKT_HDR_SIZE_RANGE,
                                       DBAL_FIELD_FIELD_PMF_RANGE_ID,
                                       DBAL_FIELD_PKT_HDR_SIZE_RANGE_MIN, DBAL_FIELD_PKT_HDR_SIZE_RANGE_MAX,
                                       TRUE,
                                      },
    },
};

/*
 * Context Selection related data below
 * {
 */
/*
 * Inside maps all CS qualifiers are listed, ones that has no bcm qualifier located yet are in comments *
 */
static const dnx_field_cs_qual_e dnx_ipmf1_cs_qual_layer_type[] = {
    /** We allow The FW layer to be -7 to 7.*/
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_1,
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_2,
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_3,
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_4,
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_5,
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_6,
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_MINUS_1,
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_0,
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_1,
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_2,
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_3,
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_4,
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_5,
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_6,
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_MINUS_1,
};
static const dnx_field_cs_qual_e dnx_ipmf1_cs_qual_inlif_profile_map[] = {
    DNX_FIELD_CS_QUAL_IN_LIF_PROFILE_MAP_0,
    DNX_FIELD_CS_QUAL_IN_LIF_PROFILE_MAP_1,
};
static const dnx_field_cs_qual_e dnx_ipmf1_cs_qual_outlif_range[] = {
    DNX_FIELD_CS_QUAL_OUT_LIF_RANGE_0,
    DNX_FIELD_CS_QUAL_OUT_LIF_RANGE_1,
};
static const dnx_field_cs_qual_e dnx_ipmf1_cs_qual_fwd_layer_qual[] = {
    DNX_FIELD_CS_QUAL_FWD_LAYER_QUAL_MINUS_1,
    DNX_FIELD_CS_QUAL_FWD_LAYER_QUAL_0,
    DNX_FIELD_CS_QUAL_FWD_LAYER_QUAL_1,
    DNX_FIELD_CS_QUAL_FWD_LAYER_QUAL_2,
};

static const dnx_field_cs_qual_map_t dnx_ipmf1_cs_qual_map[bcmFieldQualifyCount] = {
        [bcmFieldQualifyPortClassPacketProcessing]  = {1, DNX_FIELD_CS_QUAL_IN_PORT_CS_PROFILE, },
        [bcmFieldQualifyPortClassTrafficManagement] = {1, DNX_FIELD_CS_QUAL_PTC_CS_PROFILE, },

        [bcmFieldQualifyPtch]                    = {1, DNX_FIELD_CS_QUAL_PRT_QUALIFIER_RAW, },
        [bcmFieldQualifyAppTypeRaw]              = {1, DNX_FIELD_CS_QUAL_ACL_CONTEXT_PROFILE, },
        [bcmFieldQualifyAppType]                 = {1, DNX_FIELD_CS_QUAL_ACL_CONTEXT_PROFILE, BCM_TO_DNX_ADDITIONAL_OBJ , NULL, 0, NULL, NULL, dnx_field_convert_app_type_context_profile},
        [bcmFieldQualifyAppTypePredefinedRaw]    = {1, DNX_FIELD_CS_QUAL_FWD_CONTEXT_PROFILE, },
        [bcmFieldQualifyAppTypePredefined]       = {1, DNX_FIELD_CS_QUAL_FWD_CONTEXT_PROFILE, BCM_TO_DNX_ADDITIONAL_OBJ , NULL, 0, NULL, NULL, dnx_field_convert_app_type_predef_only},
        [bcmFieldQualifyForwardingLayerIndex]    = {1, DNX_FIELD_CS_QUAL_FWD_LAYER_INDEX, },
        [bcmFieldQualifyRxTrapCode]              = {1, DNX_FIELD_CS_QUAL_CPU_TRAP_CODE, },
        [bcmFieldQualifyInVportClass]            = {sizeof(dnx_ipmf1_cs_qual_inlif_profile_map) / sizeof(dnx_field_cs_qual_e),
                                                    DNX_FIELD_CS_QUAL_INVALID, 0, (dnx_field_cs_qual_e *) dnx_ipmf1_cs_qual_inlif_profile_map,0,NULL,NULL,dnx_field_verify_in_lif_profile_size },
        [bcmFieldQualifyVPortRangeCheck]         = {sizeof(dnx_ipmf1_cs_qual_outlif_range) / sizeof(dnx_field_cs_qual_e),
                                                    DNX_FIELD_CS_QUAL_INVALID,0 , (dnx_field_cs_qual_e *) dnx_ipmf1_cs_qual_outlif_range},
        [bcmFieldQualifyVlanFormatRaw]           = {1, DNX_FIELD_CS_QUAL_PMF_TAG_STRUCTURE, },
        [bcmFieldQualifyVlanFormat]              = {1, DNX_FIELD_CS_QUAL_PMF_TAG_STRUCTURE, BCM_TO_DNX_ADDITIONAL_OBJ , NULL, 0, NULL, NULL,
                                                    dnx_field_convert_vlan_format},

        [bcmFieldQualifyExternalHit0]            = {1, DNX_FIELD_CS_QUAL_ELK_FOUND_RESULT_0, },
        [bcmFieldQualifyExternalHit1]            = {1, DNX_FIELD_CS_QUAL_ELK_FOUND_RESULT_1, },
        [bcmFieldQualifyExternalHit2]            = {1, DNX_FIELD_CS_QUAL_ELK_FOUND_RESULT_2, },
        [bcmFieldQualifyExternalHit3]            = {1, DNX_FIELD_CS_QUAL_ELK_FOUND_RESULT_3, },
        [bcmFieldQualifyExternalHit4]            = {1, DNX_FIELD_CS_QUAL_ELK_FOUND_RESULT_4, },
        [bcmFieldQualifyExternalHit5]            = {1, DNX_FIELD_CS_QUAL_ELK_FOUND_RESULT_5, },
        [bcmFieldQualifyExternalHit6]            = {1, DNX_FIELD_CS_QUAL_ELK_FOUND_RESULT_6, },
        [bcmFieldQualifyExternalHit7]            = {1, DNX_FIELD_CS_QUAL_ELK_FOUND_RESULT_7, },

        [bcmFieldQualifyForwardingTypeRaw]       = {sizeof(dnx_ipmf1_cs_qual_layer_type) / sizeof(dnx_field_cs_qual_e),
                                                    DNX_FIELD_CS_QUAL_INVALID,0, (dnx_field_cs_qual_e *) dnx_ipmf1_cs_qual_layer_type, 7},
        [bcmFieldQualifyForwardingType]          = {sizeof(dnx_ipmf1_cs_qual_layer_type) / sizeof(dnx_field_cs_qual_e),
                                                    DNX_FIELD_CS_QUAL_INVALID, BCM_TO_DNX_ADDITIONAL_OBJ, (dnx_field_cs_qual_e *) dnx_ipmf1_cs_qual_layer_type, 7,
                                                    NULL, NULL, dnx_field_convert_forwarding_type},

        [bcmFieldQualifyForwardingLayerQualifier]= {sizeof(dnx_ipmf1_cs_qual_fwd_layer_qual) / sizeof(dbal_fields_e),
                                                    DNX_FIELD_CS_QUAL_INVALID, 0, (dnx_field_cs_qual_e *) dnx_ipmf1_cs_qual_fwd_layer_qual, 1},
        [bcmFieldQualifyTracePacket]             = {1, DNX_FIELD_CS_QUAL_TRACE_PACKET, },


        [bcmFieldQualifyAcInLifWideData]         = {1, DNX_FIELD_CS_QUAL_AC_IN_LIF_WIDE_DATA, },

};

static const dnx_field_cs_qual_e dnx_ipmf2_cs_qual_cascaded_key_qual[] = {
    DNX_FIELD_CS_QUAL_PMF1_TCAM_ACTION_0_MSB,
    DNX_FIELD_CS_QUAL_PMF1_TCAM_ACTION_1_MSB,
    DNX_FIELD_CS_QUAL_PMF1_TCAM_ACTION_2_MSB,
    DNX_FIELD_CS_QUAL_PMF1_TCAM_ACTION_3_MSB,
    DNX_FIELD_CS_QUAL_PMF1_EXEM_PAYLOAD_MSB,
};

static const dnx_field_cs_qual_map_t dnx_ipmf2_cs_qual_map[bcmFieldQualifyCount] = {

     /**
      * bcmFieldQualifyContextId should not be exposed, this is managed by SDK
      * 1) Cascaded from is mentioned in Context Create API of iPMF2 stage - saved in SW state and profile allocated
      * 2) There is no reason to switch context to iPMF2 unless additional Qualifier in CS is used
      *    (otherwise user can use iPMF1 context configuration)
      *    When the presel set API will be called for context in iPMF2 (with additional qualifier) then SDK also set
      *    the qualifier of context profile which was saved previously
      * */
    /*[bcmFieldQualifyContextId]               = {1, DNX_FIELD_CS_QUAL_PMF1_PROGRAM_SELECTION_PROFILE},*/
    /*
     * In Jericho there were tcam_action lsb instead
     */
    [bcmFieldQualifyCascadedKeyValue]        = {sizeof(dnx_ipmf2_cs_qual_cascaded_key_qual) / sizeof(dnx_field_cs_qual_e),
                                                DNX_FIELD_CS_QUAL_INVALID,0 , (dnx_field_cs_qual_e *) dnx_ipmf2_cs_qual_cascaded_key_qual,
                                                0, dnx_field_convert_cs_qual_type_cascaded_group,
                                                dnx_field_convert_cs_qual_type_cascaded_group_back, NULL},

    [bcmFieldQualifyStateTableData]          = {1, DNX_FIELD_CS_QUAL_STATE_TABLE_DATA_READ, 0,
                                                NULL, 0, NULL, NULL, NULL},
    [bcmFieldQualifyStateTableDataWrite]     = {1, DNX_FIELD_CS_QUAL_STATE_TABLE_DATA_WRITE, 0,
                                                NULL, 0, NULL, NULL, NULL},
    /**
     * using bcmFieldQualifyCompareKeysResult0, bcmFieldQualifyCompareKeysResult1 as CS qualifiers, each has 3 bits:
     * bit 2 = greater than
     * bit 1 = equal
     * bit 0 = smaller than
     */
    [bcmFieldQualifyCompareKeysResult0]      = {1, DNX_FIELD_CS_QUAL_CMP_OUTPUT_PAIR_1, },
    [bcmFieldQualifyCompareKeysResult1]      = {1, DNX_FIELD_CS_QUAL_CMP_OUTPUT_PAIR_2, },

};

static const dnx_field_cs_qual_e dnx_ipmf3_cs_qual_outlif_range[] = {
    DNX_FIELD_CS_QUAL_OUT_LIF_RANGE_0,
    DNX_FIELD_CS_QUAL_OUT_LIF_RANGE_1,
    DNX_FIELD_CS_QUAL_OUT_LIF_RANGE_2,
    DNX_FIELD_CS_QUAL_OUT_LIF_RANGE_3,
};

static const dnx_field_cs_qual_map_t dnx_ipmf3_cs_qual_map[bcmFieldQualifyCount] = {
    [bcmFieldQualifyPortClassPacketProcessing]  = {1, DNX_FIELD_CS_QUAL_IN_PORT_CS_PROFILE, },
    [bcmFieldQualifyPortClassTrafficManagement] = {1, DNX_FIELD_CS_QUAL_PTC_CS_PROFILE, },
    [bcmFieldQualifyForwardingTypeRaw]          = {1, DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_0, },
    [bcmFieldQualifyForwardingType]             = {1, DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_0, BCM_TO_DNX_ADDITIONAL_OBJ, NULL, 0, NULL, NULL,
                                                   dnx_field_convert_forwarding_type},
    [bcmFieldQualifyForwardingLayerQualifier]   = {1, DNX_FIELD_CS_QUAL_FWD_LAYER_QUALIFIER, },
    [bcmFieldQualifyContextId]                  = {1, DNX_FIELD_CS_QUAL_ACL_CONTEXT_PROFILE, },
    [bcmFieldQualifyRpfEcmpMode]                = {1, DNX_FIELD_CS_QUAL_RPF_ECMP_MODE, },
    [bcmFieldQualifyDstType]                    = {1, DNX_FIELD_CS_QUAL_CS_DESTINATION, },
    [bcmFieldQualifyVPortRangeCheck]            = {sizeof(dnx_ipmf3_cs_qual_outlif_range) / sizeof(dnx_field_cs_qual_e),
                                                   DNX_FIELD_CS_QUAL_INVALID, 0, (dnx_field_cs_qual_e *) dnx_ipmf3_cs_qual_outlif_range},

    [bcmFieldQualifyRxTrapProfile]              = {1, DNX_FIELD_CS_QUAL_TRAP_CODE_PROFILE, },

};

static const dnx_field_cs_qual_e dnx_epmf_cs_qual_fwd_layer_type[] = {
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_MINUS_1,
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_0,
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_1,
    DNX_FIELD_CS_QUAL_FWD_LAYER_TYPE_2,
};
static const dnx_field_cs_qual_e dnx_epmf_cs_qual_fwd_layer_qual[] = {
    DNX_FIELD_CS_QUAL_FWD_LAYER_QUAL_MINUS_1,
    DNX_FIELD_CS_QUAL_FWD_LAYER_QUAL_0,
    DNX_FIELD_CS_QUAL_FWD_LAYER_QUAL_1,
};

static const dnx_field_cs_qual_e dnx_epmf_cs_qual_outlif_profile[] = {
    DNX_FIELD_CS_QUAL_PMF_OUT_LIF_PROFILE,
    DNX_FIELD_CS_QUAL_PMF_OUT_LIF_1_PROFILE,
    DNX_FIELD_CS_QUAL_PMF_OUT_LIF_2_PROFILE,
    DNX_FIELD_CS_QUAL_PMF_OUT_LIF_3_PROFILE,
};

static const dnx_field_cs_qual_map_t dnx_epmf_cs_qual_map[bcmFieldQualifyCount] = {
        [bcmFieldQualifyPortClassPacketProcessing]  = {1, DNX_FIELD_CS_QUAL_PP_PORT_PMF_CS_PROFILE, },
        [bcmFieldQualifyPortClassTrafficManagement] = {1, DNX_FIELD_CS_QUAL_TM_PORT_PMF_CS_PROFILE, },
        [bcmFieldQualifyContextIdRaw]               = {1, DNX_FIELD_CS_QUAL_FWD_CODE, },
        [bcmFieldQualifyContextId]                  = {1, DNX_FIELD_CS_QUAL_FWD_CODE, BCM_TO_DNX_ADDITIONAL_OBJ , NULL, 0, NULL, NULL, dnx_field_convert_forwarding_context},
        [bcmFieldQualifyVlanFormatRaw]              = {1, DNX_FIELD_CS_QUAL_PMF_TAG_STRUCTURE, },
        [bcmFieldQualifyVlanFormat]                 = {1, DNX_FIELD_CS_QUAL_PMF_TAG_STRUCTURE,BCM_TO_DNX_ADDITIONAL_OBJ,},
        [bcmFieldQualifyPphPresent]                 = {1, DNX_FIELD_CS_QUAL_PPH_PRESENT, },
        [bcmFieldQualifyLearnExtensionPresent]      = {1, DNX_FIELD_CS_QUAL_LEARN_EXTENSION_PRESENT, },
        [bcmFieldQualifyFheiSize]                   = {1, DNX_FIELD_CS_QUAL_FHEI_SIZE, },
        [bcmFieldQualifyOutVportClass]              = {sizeof(dnx_epmf_cs_qual_outlif_profile) / sizeof(dnx_field_cs_qual_e),
                                                       DNX_FIELD_CS_QUAL_INVALID, 0, (dnx_field_cs_qual_e *) dnx_epmf_cs_qual_outlif_profile},
        [bcmFieldQualifyOutVportClassLast]          = {1, DNX_FIELD_CS_QUAL_PMF_OUTERMOST_OUT_LIF_PROFILE, },
        [bcmFieldQualifyInterfaceClassL2]           = {1, DNX_FIELD_CS_QUAL_PMF_OUT_RIF_PROFILE, },
        [bcmFieldQualifyDstClassField]              = {1,DNX_FIELD_CS_QUAL_PPH_VALUE_1, },
        [bcmFieldQualifySrcClassField]              = {1,DNX_FIELD_CS_QUAL_PPH_VALUE_2_LSB, },
        [bcmFieldQualifyUDHBase0]                    = {1, DNX_FIELD_CS_QUAL_UDH_BASE_0, },
        [bcmFieldQualifyUDHBase1]                    = {1, DNX_FIELD_CS_QUAL_UDH_BASE_1, },
        [bcmFieldQualifyUDHBase2]                    = {1, DNX_FIELD_CS_QUAL_UDH_BASE_2, },
        [bcmFieldQualifyUDHBase3]                    = {1, DNX_FIELD_CS_QUAL_UDH_BASE_3, },
        [bcmFieldQualifyForwardingTypeRaw]           = {sizeof(dbal_fields_e),
                                                        DNX_FIELD_CS_QUAL_INVALID, 0, (dnx_field_cs_qual_e *) dnx_epmf_cs_qual_fwd_layer_type, 1},
        [bcmFieldQualifyForwardingType]             = {sizeof(dbal_fields_e),
                                                       DNX_FIELD_CS_QUAL_INVALID, BCM_TO_DNX_ADDITIONAL_OBJ, (dnx_field_cs_qual_e *) dnx_epmf_cs_qual_fwd_layer_type,
                                                       1, NULL, NULL, dnx_field_convert_forwarding_type},
        [bcmFieldQualifyForwardingLayerQualifier]   = {sizeof(dnx_epmf_cs_qual_fwd_layer_qual) / sizeof(dnx_field_cs_qual_e),
                                                       DNX_FIELD_CS_QUAL_INVALID, 0,
                                                       (dnx_field_cs_qual_e *) dnx_epmf_cs_qual_fwd_layer_qual, 1},
        [bcmFieldQualifyInVportClass0]               = {1, DNX_FIELD_CS_QUAL_IN_LIF_PROFILE_0, },



        [bcmFieldQualifyFtmhAsePresent]            = {1, DNX_FIELD_CS_QUAL_APP_SPECIFIC_EXTENSION_PRESENT, },
        [bcmFieldQualifyFtmhAseType]               = {1, DNX_FIELD_CS_QUAL_APP_SPECIFIC_EXTENSION_LSB, },
        [bcmFieldQualifyUDHBaseFieldCs]             = {1, DNX_FIELD_CS_QUAL_UDH_BASE_PMF_CS_VAR, },
};

static const dnx_field_cs_qual_e dnx_external_cs_qual_fwd_layer_type[] = {
    DNX_FIELD_CS_QUAL_LAYER_TYPE_PREVIOUS_LAYER,
    DNX_FIELD_CS_QUAL_LAYER_TYPE_CURRENT_LAYER,
    DNX_FIELD_CS_QUAL_LAYER_TYPE_NEXT_LAYER,
};
static const dnx_field_cs_qual_e dnx_external_cs_qual_fwd_layer_qual[] = {
    DNX_FIELD_CS_QUAL_LAYER_QUALIFIER_PREVIOUS_LAYER,
    DNX_FIELD_CS_QUAL_LAYER_QUALIFIER_CURRENT_LAYER,
    DNX_FIELD_CS_QUAL_LAYER_QUALIFIER_NEXT_LAYER,
};

static const dnx_field_cs_qual_map_t dnx_external_cs_qual_map[bcmFieldQualifyCount] = {
/**
  * bcmFieldQualifyContextId should not be exposed, this is managed by SDK
  * All presels to a dymanic Apptype (the only kind) include the context of the Apptype they cascaded from.
  * Uses DNX_FIELD_CS_QUAL_CURRENT_ACL_CONTEXT_PROFILE.
  * */
    [bcmFieldQualifyForwardingLayerQualifier]= {sizeof(dnx_external_cs_qual_fwd_layer_qual) / sizeof(dnx_field_cs_qual_e),
                                                DNX_FIELD_CS_QUAL_INVALID, 0, (dnx_field_cs_qual_e *) dnx_external_cs_qual_fwd_layer_qual, 1},
    [bcmFieldQualifyForwardingTypeRaw]          = {sizeof(dnx_external_cs_qual_fwd_layer_type) / sizeof(dnx_field_cs_qual_e),
                                                       DNX_FIELD_CS_QUAL_INVALID, 0, (dnx_field_cs_qual_e *) dnx_external_cs_qual_fwd_layer_type, 1},
    [bcmFieldQualifyForwardingType]          = {sizeof(dnx_external_cs_qual_fwd_layer_type) / sizeof(dbal_fields_e),
                                                DNX_FIELD_CS_QUAL_INVALID, BCM_TO_DNX_ADDITIONAL_OBJ, (dnx_field_cs_qual_e *) dnx_external_cs_qual_fwd_layer_type,
                                                1, NULL, NULL, dnx_field_convert_forwarding_type},
    [bcmFieldQualifyForwardingLayerIndex]    = {1, DNX_FIELD_CS_QUAL_FWD_LAYER_INDEX, },
    [bcmFieldQualifyForwardingProfile]       = {1, DNX_FIELD_CS_QUAL_FWD_DOMAIN_PROFILE, },
    [bcmFieldQualifyIpMulticastCompatible]   = {1, DNX_FIELD_CS_QUAL_IS_COMPATIBLE_MULTICAST, },
    [bcmFieldQualifyRxTrapCode]              = {1, DNX_FIELD_CS_QUAL_INGRESS_TRAP_CODE, },
    [bcmFieldQualifyVlanFormatRaw]           = {1, DNX_FIELD_CS_QUAL_PMF_TAG_STRUCTURE, },
    [bcmFieldQualifyVlanFormat]              = {1, DNX_FIELD_CS_QUAL_PMF_TAG_STRUCTURE, BCM_TO_DNX_ADDITIONAL_OBJ , NULL, 0, NULL, NULL,
                                                dnx_field_convert_vlan_format},
    [bcmFieldQualifyPortClassPacketProcessing]  = {1, DNX_FIELD_CS_QUAL_PP_PORT_PROFILE, },
    [bcmFieldQualifyPortClassTrafficManagement] = {1, DNX_FIELD_CS_QUAL_PORT_TERMINATION_PTC_PROFILE, },
};
/* *INDENT-ON* */

/*
 * End of Context Selection related data
 * }
 */

/* *INDENT-OFF* */
/*
 * Qualifier related data below
 * {
 */


/*
 * Qualifier related data below
 * {
 */


const char *bcm_qual_description[bcmFieldQualifyCount] = {

    [bcmFieldQualifyDstMac]                = "Destination MAC address",
    [bcmFieldQualifySrcMac]                = "Source MAC address",
    [bcmFieldQualifyEtherTypeUntagged]     = "802.1 Ethernet Type, only for untagged frames",

    [bcmFieldQualifyTpid]                  = "VLAN TPID, offset of the value is inside the VLAN tag. Need to add the offset where the tag start in the Layer (inner/outer..)",
    [bcmFieldQualifyVlanId]                = "VLAN ID, offset of the value is inside the VLAN tag. Need to add the offset where the tag start in the Layer (inner/outer..)",
    [bcmFieldQualifyVlanPri]               = "VLAN P-bits , offset of the value is inside the VLAN tag. Need to add the offset where the tag start in the Layer (inner/outer..)",
    [bcmFieldQualifyVlanCfi]               = "VLAN CFI , offset of the value is inside the VLAN tag. Need to add the offset where the tag start in the Layer (inner/outer..)",
    [bcmFieldQualifyVlanPriCfi]            = "VLAN P-bits and CFI , offset of the value is inside the VLAN tag. Need to add the offset where the tag start in the Layer (inner/outer..)",

    [bcmFieldQualifyArpSenderIp4]          = "Sender IPv4 field of ARP header",
    [bcmFieldQualifyArpTargetIp4]          = "Target IPv4 field of ARP header",
    [bcmFieldQualifyArpOpcode]             = "Opcode field of ARP header.",

    [bcmFieldQualifyMplsLabel]             = "MPLS Label  ",
    [bcmFieldQualifyMplsLabelId]           = "ID field of MPLS Label",
    [bcmFieldQualifyMplsLabelTtl]          = "TTL field of MPLS Label",
    [bcmFieldQualifyMplsLabelBos]          = "BOS field of MPLS Label",
    [bcmFieldQualifyMplsLabelExp]          = "TTL field of MPLS Label",

    [bcmFieldQualifySrcIp]                 = "Packet Source IP address",
    [bcmFieldQualifyDstIp]                 = "Packet destination IP address",
    [bcmFieldQualifyIpFlags]               = "IP Flags Field",

    [bcmFieldQualifySrcIp6]                = "IPv6 Source address",
    [bcmFieldQualifyDstIp6]                = "IPv6 destination address",

    [bcmFieldQualifySrcIp6High]            = "Source IPv6 Address (High/Upper 64 bits, 64 MSB)",
    [bcmFieldQualifyDstIp6High]            = "Destination IPv6 Address (High/Upper 64 bits, 64 MSB)",
    [bcmFieldQualifySrcIp6Low]             = "Source IPv6 Address (Low/Lower 64 bits, 64 LSB)",
    [bcmFieldQualifyDstIp6Low]             = "Destination IPv6 Address (Low/Lower 64 bits, 64 LSB)",
    [bcmFieldQualifyIp6FlowLabel]          = "IPv6 Flow Label.",

    [bcmFieldQualifyL4DstPort]             = "L4 destination port",
    [bcmFieldQualifyL4SrcPort]             = "L4 source port",
    [bcmFieldQualifyTcpControl]            = "TCP control Flags",

    [bcmFieldQualifyIpFrag]                  = "IP fragments",
    [bcmFieldQualifyLayerRecordType]         = "Qualifies on the Layer Record Type. For possible values look at bcm_field_layer_type_t",
    [bcmFieldQualifyLayerRecordOffset]       = "Qualifies on the Layer Record Offset",
    [bcmFieldQualifyLayerRecordQualifier]    = "Qualifies on the Layer Record qualifier",
    [bcmFieldQualifyEthernetMulticast]       = "Qualify on Ethernet packets which destination MAC address is multicast (MAC-DA[40] is set)",
    [bcmFieldQualifyEthernetBroadcast]       = "Qualify on Ethernet packets which destination MAC address is broadcast (MAC-DA[47:0] is all 1).",
    [bcmFieldQualifyEthernetFirstTpidExist]  = "Qualify on Ethernet packets which their first Vlan TPID exists.",
    [bcmFieldQualifyEthernetFirstTpidIndex]  = "Qualify on Ethernet packets  first Vlan TPID Index",
    [bcmFieldQualifyEthernetSecondTpidExist] = "Qualify on Ethernet packets which their second Vlan TPID exists.",
    [bcmFieldQualifyEthernetSecondTpidIndex] = "Qualify on Ethernet packets  second Vlan TPID Index",
    [bcmFieldQualifyEthernetThirdTpidExist]  = "Qualify on Ethernet packets which their third Vlan TPID exists.",
    [bcmFieldQualifyEthernetThirdTpidIndex]  = "Qualify on Ethernet packets  third Vlan TPID Index",
    [bcmFieldQualifyIpMulticastCompatible]   = "Packet is compatible for multicast. ",
    [bcmFieldQualifyIpHasOptions]            = "Qualify on IPv4 packets where the IP Header include options.",
    [bcmFieldQualifyIpFirstFrag]             = "Qualify on IPv4 packets where the IP Header is fragmented and this is the first fragment.",
    [bcmFieldQualifyIpTunnelType]            = "Qualify on IPv4 TunnelType (see bcmFieldTunnelXXX).",
    [bcmFieldQualifyIpTunnelTypeRaw]         = "Raw Qualify on IPv4 TunnelType.",
    [bcmFieldQualifyIp6MulticastCompatible]  = "Qualify on IPv6 packets which their DIP is Multicast (8msb are 0xFF).",
    [bcmFieldQualifyIp6FirstAdditionalHeaderExist]  = "Qualify on IPv6 packets first additional header exists",
    [bcmFieldQualifyIp6FirstAdditionalHeader]    = "Qualify on IPv6 packets first additional header",
    [bcmFieldQualifyIp6SecondAdditionalHeaderExist]  = "Qualify on IPv6 packets second additional header exists",
    [bcmFieldQualifyIp6SecondAdditionalHeader]   = "Qualify on IPv6 packets second additional header",
    [bcmFieldQualifyItmhPphType]                 = "Qualify on Ingress TM Header PPH type",
    [bcmFieldQualifyL4PortRangeCheck]            = "Qualify on L4 Ops (L4 source and dest ports) range. The qualifier is a bitmap and not specific range id, "
                                                   "it means if range 2 was configured and the qualifier is hit, the entry value is expected to be 0x100",
    [bcmFieldQualifyRangeFirstHit0]              = "Qualify on L4 Ops Extended Encoder0. Encoder0 can be configured to consider a certain subset of range types, "
                                                   "so that for the chosen subset, the encoder will output 8b at max that consists of 1 valid bit (indicates if "
                                                   "at least one hit occurred inside the subset of chosen ranges) and 7b of the first hit index, the valid 1b "
                                                   "offset is dynamically allocated according to the number of chosen range types in the subset (i.e offset is "
                                                   "6 when 1 type is selected, 7 when 2-3 types are selected, and 8 when 4 types are selected).",
    [bcmFieldQualifyRangeFirstHit1]              = "See bcmFieldQualifyRangeFirstHit0",
    [bcmFieldQualifyRangeFirstHit2]              = "See bcmFieldQualifyRangeFirstHit0",
    [bcmFieldQualifyRangeFirstHit3]              = "See bcmFieldQualifyRangeFirstHit0",
    [bcmFieldQualifyGeneratedTtl]                = "Qualify on Packet's generate Time-To-Live",
    [bcmFieldQualifyColor]                       = "Qualify based on packet color, value should be one of BCM_FIELD_COLOR_XXX",
    [bcmFieldQualifyPacketIsIEEE1588]            = "Indicating whether the packet is 1588",
    [bcmFieldQualifyIEEE1588Encapsulation]       = "IEEE-1588 Encapsulation according to bcm_field_IEEE1588Encap_t",
    [bcmFieldQualifyIEEE1588CompensateTimeStamp] = "IEEE-1588 update time stamp",
    [bcmFieldQualifyIEEE1588Command]             = "Command used by egress pipeline, indicating if CF(correction field) needs to be update",
    [bcmFieldQualifyIEEE1588HeaderOffset]        = "This field indicates the offset in bytes  of the IEEE-1588 header",
    [bcmFieldQualifyRxTrapCodeForSnoop]          = "Qualify on Snoop Code",
    [bcmFieldQualifyRxTrapCode]                  = "Qualify on RX Trap Code",
    [bcmFieldQualifyRxTrapData]                  = "Qualify on RX Trap qualifier",
    [bcmFieldQualifyRxTrapStrength]              = "Qualify on RX Trap Strength",
    [bcmFieldQualifyDstRpfGport]                 = "RPF destination (gport) for the RPF check",
    [bcmFieldQualifyKeyGenVar]                   = "Match on configured key Gen Variable (values that was configured for context)",
    [bcmFieldQualifySrcPort]                     = "Qualify on source port, value should be encoded as SYS_PORT GPORT Type",
    [bcmFieldQualifySrcModPortGport]             = "Qualify on Source module/port pair, value should be encoded as SYS_PORT GPORT Type",
    [bcmFieldQualifyDstPort]                     = "Qualify on destination port, all ingress stages expect raw value, egress expects GPORT encoded as SYS_PORT",
    [bcmFieldQualifyDstMulticastGroup]           = "Multicast Group id, encoded as GPORT",
    [bcmFieldQualifyFlowId]                      = "Qualify on destination Flow-Id",
    [bcmFieldQualifyDstL3Egress]                 = "L3 Egress Interface, Raw value of SYS_PORT",
    [bcmFieldQualifyOamUpMep]                    = "It indicates if the OAM packet is vUP-MEP (sent to a destination in the network, as opposed to a specific port)",
    [bcmFieldQualifyOamSubtype]                  = "In OAM the packet type is specified in the OAM header and mapped to a subtype in the hardware",
    [bcmFieldQualifyOamStampOffset]              = "indicates the offset to the position, in the OAM header, where the ToD or counter value should be stamped relative to the start of packet",
    [bcmFieldQualifyOamHeaderOffset]             = "indicates the offset of the OAM header relative to the start of packet (as opposed to start of header-offset)",
    [bcmFieldQualifyOamMepId]                    = "If MEP is handled in OAMP, then the OAM-ID is the MEP-ID (equivalent to the index used to access the MEP DB). ",
    [bcmFieldQualifyOamMeterDisable]             = "attribute that is passed to the PMF and can also be configured by the user per MEP.",
    [bcmFieldQualifyPacketSize]                  = " Packet size in Bytes.",
    [bcmFieldQualifyInVPort0]                    = "In LIF 0, value should be GPORT with sub-type LIF",
    [bcmFieldQualifyInVPort1]                    = "In LIF 1, value should be GPORT with sub-type LIF",
    [bcmFieldQualifyOutVPort0]                   = "Out LIF 0, value should be GPORT with sub-type LIF",
    [bcmFieldQualifyOutVPort1]                   = "Out LIF 1, value should be GPORT with sub-type LIF",
    [bcmFieldQualifyOutVPort2]                   = "Out LIF 2, value should be GPORT with sub-type LIF",
    [bcmFieldQualifyOutVPort3]                   = "Out LIF 3, value should be GPORT with sub-type LIF",
    [bcmFieldQualifyTrunkHashResult]             = "Trunk Hash Result (i.e., the Load-balancing Key)",
    [bcmFieldQualifyIntPriority]                 = "Internal priority (TC)",
    [bcmFieldQualifyExternalHit0]                = "External Lookup Hit 0",
    [bcmFieldQualifyExternalHit1]                = "External Lookup Hit 1",
    [bcmFieldQualifyExternalHit2]                = "External Lookup Hit 2",
    [bcmFieldQualifyExternalHit3]                = "External Lookup Hit 3",
    [bcmFieldQualifyExternalHit4]                = "External Lookup Hit 4",
    [bcmFieldQualifyExternalHit5]                = "External Lookup Hit 5",
    [bcmFieldQualifyExternalHit6]                = "External Lookup Hit 6",
    [bcmFieldQualifyExternalHit7]                = "External Lookup Hit 7",
    [bcmFieldQualifyInVportClass0]               = "In-LIF Profile 0",
    [bcmFieldQualifyInVportClass1]               = "In-LIF Profile 1",
    [bcmFieldQualifyOutVportClass]               = "Out-LIF Profile",
    [bcmFieldQualifyOutVportClass0]              = "Out-LIF Profile 0",
    [bcmFieldQualifyOutVportClass1]              = "Out-LIF Profile 1",
    [bcmFieldQualifyOutVportClass2]              = "Out-LIF Profile 2",
    [bcmFieldQualifyOutVportClass3]              = "Out-LIF Profile 3",
    [bcmFieldQualifyOutVportClassLast]           = "Last Out-LIF Profile",
    [bcmFieldQualifyTranslatedOuterVlanId ]      = "Translated Outer VLAN ID  ",
    [bcmFieldQualifyTranslatedOuterVlanPri]      = "Translated Outer VLAN priority" ,
    [bcmFieldQualifyTranslatedOuterVlanCfi]      = "Translated Outer VLAN CFI" ,
    [bcmFieldQualifyTranslatedInnerVlanId ]      = "Translated inner VLAN Id" ,
    [bcmFieldQualifyTranslatedInnerVlanPri]      = "Translated inner VLAN priority" ,
    [bcmFieldQualifyTranslatedInnerVlanCfi]      = "Translated inner VLAN CFI" ,
    [bcmFieldQualifyVlanAction]                  = "Vlan translation action  ID" ,
    [bcmFieldQualifyInPort]                      = "Ingress Port, value should be encoded as LOCAL GPORT Type. Includes core ID, and can be used by entries for all cores.",
    [bcmFieldQualifyInPortWithoutCore]           = "Ingress Port, value should be encoded as LOCAL GPORT Type. Does not include the core ID, caution should be taken when not adding entry by core.",
    [bcmFieldQualifyPacketLengthRangeCheck]      = "Packet length range, range id which packet matched upon",
    [bcmFieldQualifyVlanFormat]                  = "Incoming vlan structure format (untagged/single/double/priority-tagged), value should be set of BCM_FIELD_VLAN_FORMAT_ flags",
    [bcmFieldQualifyL2Learn]                     = "L2 learn enable",
    [bcmFieldQualifyTrillEgressRbridge]          = "Egress RBridge Nickname",
    [bcmFieldQualifyISid]                        = "I-SID (MAC-in-MAC lookup-id)",
    [bcmFieldQualifyMplsForwardingLabelAction]   = "MPLS forwarding label action.",
    [bcmFieldQualifyVrf]                         = "VRF Id",
    [bcmFieldQualifyVpn]                         = "VSI Id",
    [bcmFieldQualifyForwardingLayerIndex]        = "Qualify on the Forwarding Layer Index",
    [bcmFieldQualifyInterfaceClassL2]            = "VSI Profile",
    [bcmFieldQualifyIncomingIpIfClass]           = "RIF profile ",
    [bcmFieldQualifyAcInLifWideData]             = "Qualifies on the Ac in-lif wide(generic) data. In case of Context Selection it is only 8 bits.",
    [bcmFieldQualifyNativeAcInLifWideData]       = "Qualifies on the native Ac in-lif wide(generic) data",
    [bcmFieldQualifyPweInLifWideData]            = "Qualifies on the Pwe in-lif wide(generic) data.",
    [bcmFieldQualifyIpTunnelInLifWideData]       = "Qualifies on the Ip Tunnel in-lif wide(generic) data.",
    [bcmFieldQualifyHashValue]                   = "Hash value",
    [bcmFieldQualifyNetworkLoadBalanceKey]       = "Network Load Balance Key",
    [bcmFieldQualifyEcmpLoadBalanceKey0]         = "ECMP Load Balance Key 0",
    [bcmFieldQualifyEcmpLoadBalanceKey1]         = "ECMP Load Balance Key 1",
    [bcmFieldQualifyEcmpLoadBalanceKey2]         = "ECMP Load Balance Key 2",
    [bcmFieldQualifyStateTableData]              = "state Table payload, as read from state table",
    [bcmFieldQualifyStateTableDataWrite]         = "state Table payload, as written to state table",
    [bcmFieldQualifyCompareKeysResult0]          = "compare keys result 0",
    [bcmFieldQualifyCompareKeysResult1]          = "compare keys result 1",
    [bcmFieldQualifyCompareKeysTcam0]            = "compare keys and TCAM result 0",
    [bcmFieldQualifyCompareKeysTcam1]            = "compare keys and TCAM result 1",
    [bcmFieldQualifyUDHData0]                    = "User Defined Header 0 payload MS bits of UDH",
    [bcmFieldQualifyUDHData1]                    = "User Defined Header 1 payload",
    [bcmFieldQualifyUDHData2]                    = "User Defined Header 2 payload",
    [bcmFieldQualifyUDHData3]                    = "User Defined Header 3 payload LS bits of UDH",
    [bcmFieldQualifyUDHBase0]                    = "User Defined Header 0 encoded type and size - value 1: type PMF size 32b",
    [bcmFieldQualifyUDHBase1]                    = "User Defined Header 1 encoded type and size - value 1: type PMF size 32b",
    [bcmFieldQualifyUDHBase2]                    = "User Defined Header 2 encoded type and size - value 1: type PMF size 32b",
    [bcmFieldQualifyUDHBase3]                    = "User Defined Header 3 encoded type and size - value 1: type PMF size 32b",
    [bcmFieldQualifyUDHData0Ext]                 = "User Defined Header 0 Extension",
    [bcmFieldQualifyUDHData1Ext]                 = "User Defined Header 1 Extension",
    [bcmFieldQualifyUDHBaseFieldCs]              = "User Defined Header Base CS var",
    [bcmFieldQualifyPortClassPacketProcessing]   = "PP port profile",
    [bcmFieldQualifyPortClassTrafficManagement]  = "TM port profile",
    [bcmFieldQualifyPortClassPacketProcessingGeneralData] = "PP port general data",
    [bcmFieldQualifyOutPortTrafficManagement]    = "Out TM-port",
    [bcmFieldQualifyDstClassField]               = "PPH Value 1, supported for JR1 mode only",
    [bcmFieldQualifySrcClassField]               = "PPH Value 2, supported for JR1 mode only",
    [bcmFieldQualifyInInterface]                 = "Ingress Logical Interface (LIF/RIF), value should be encoded as L3 interface",
    [bcmFieldQualifyOutInterface]                = "Egress Logical Interface (LIF/RIF), should be encoded as L3 interface",
    [bcmFieldQualifyFhei]                        = "DNX FHEI header field",
    [bcmFieldQualifyFheiSize]                    = "DNX FHEI header size in bytes",
    [bcmFieldQualifyRepCopy]                     = "qualify on Copy type. For possible values look at bcm_field_rep_copy_type_t",
    [bcmFieldQualifyEcnValue]                    = "qualify on metadata ECN / congestion info (including CNI)",
    [bcmFieldQualifyOamTsSystemHeader]           = "FTMH Application specific extension",
    [bcmFieldQualifyIPTProfile]                  = "Qualifies upon IPT Profile (End Of Packet Editing).",
    [bcmFieldQualifyRxSnoopCode]                 = "qualify upon Snoop profile",
    [bcmFieldQualifyOutPort]                     = "Egress port, value should be encoded as LOCAL GPORT Type. Does not include the core ID, caution should be taken when not adding entry by core.",
    [bcmFieldQualifyStackingRoute]               = "Stacking Route History bitmap",
    [bcmFieldQualifyContainer]                   = "This qualifier will be used as container in IPMF3, to receive the action buffer, when performing cascading between IPMF1/2 and IPMF3.",
    [bcmFieldQualifyRxSnoopStrength]             = "Snoop Strength",
    [bcmFieldQualifyStatSamplingCode]            = "Statistical Sampling Code value",
    [bcmFieldQualifyStatSamplingQualifier]       = "Statistical Sampling qualifier value",
    [bcmFieldQualifyRpfEcmpMode]                 = "RPF ECMP mode",
    [bcmFieldQualifyStatOamLM]                   = "OAM LM counter value, the index of the values are bcmFieldStatOamLmIndexXXX",
    [bcmFieldQualifyStatOamLMRaw]                = "OAM LM counter raw value",
    [bcmFieldQualifyBierStringOffset]            = "Qualifies upon Bier string offset.",
    [bcmFieldQualifyBierStringSize]              = "Qualifies upon Bier string size.",
    [bcmFieldQualifyPacketIsBier]                = "Qualifies upon Bier packets.",
    [bcmFieldQualifyTracePacket]                 = "Qualifies upon Packets that Trace was set for them",
    [bcmFieldQualifyForwardingAdditionalInfo]    = "Qualifies on the Forwarding additional info.",
    [bcmFieldQualifyStatId0]                     = "Qualifies on statistics ID 0.",
    [bcmFieldQualifyStatId1]                     = "Qualifies on statistics ID 1.",
    [bcmFieldQualifyStatId2]                     = "Qualifies on statistics ID 2.",
    [bcmFieldQualifyStatId3]                     = "Qualifies on statistics ID 3.",
    [bcmFieldQualifyStatId4]                     = "Qualifies on statistics ID 4.",
    [bcmFieldQualifyStatId5]                     = "Qualifies on statistics ID 5.",
    [bcmFieldQualifyStatId6]                     = "Qualifies on statistics ID 6.",
    [bcmFieldQualifyStatId7]                     = "Qualifies on statistics ID 7.",
    [bcmFieldQualifyStatId8]                     = "Qualifies on statistics ID 8.",
    [bcmFieldQualifyStatId9]                     = "Qualifies on statistics ID 9.",
    [bcmFieldQualifyStatProfile0]                = "Qualifies on statistics profile 0.",
    [bcmFieldQualifyStatProfile1]                = "Qualifies on statistics profile 1.",
    [bcmFieldQualifyStatProfile2]                = "Qualifies on statistics profile 2.",
    [bcmFieldQualifyStatProfile3]                = "Qualifies on statistics profile 3.",
    [bcmFieldQualifyStatProfile4]                = "Qualifies on statistics profile 4.",
    [bcmFieldQualifyStatProfile5]                = "Qualifies on statistics profile 5.",
    [bcmFieldQualifyStatProfile6]                = "Qualifies on statistics profile 6.",
    [bcmFieldQualifyStatProfile7]                = "Qualifies on statistics profile 7.",
    [bcmFieldQualifyStatProfile8]                = "Qualifies on statistics profile 8.",
    [bcmFieldQualifyStatProfile9]                = "Qualifies on statistics profile 9.",
    [bcmFieldQualifyExtStat0]                    = "Qualifies on External Statistics ID 0.",
    [bcmFieldQualifyExtStat1]                    = "Qualifies on External Statistics ID 1.",
    [bcmFieldQualifyExtStat2]                    = "Qualifies on External Statistics ID 2.",
    [bcmFieldQualifyExtStat3]                    = "Qualifies on External Statistics ID 3.",
    [bcmFieldQualifyExtStatProfile0]             = "Qualifies on External Statistics profile 0.",
    [bcmFieldQualifyExtStatProfile1]             = "Qualifies on External Statistics profile 1.",
    [bcmFieldQualifyExtStatProfile2]             = "Qualifies on External Statistics profile 2.",
    [bcmFieldQualifyExtStatProfile3]             = "Qualifies on External Statistics profile 3.",
    [bcmFieldQualifyStatMetaData]                = "Qualifies on Statistics meta data.",
    [bcmFieldQualifyPphPresent]                  = "Qualifies on PPH present field in ITMH.",
    [bcmFieldQualifyPacketProcessingInVportClass]= "Qualifies on PPH In-LIF profile.",
    [bcmFieldQualifyIp6NextHeader]               = "Next protocol field in IPv6 Header",
    [bcmFieldQualifyIp6HopLimit]                 = "Hop Count field in IPv6 Header",
    [bcmFieldQualifyIp6TrafficClass]             = "Traffic class field in IPv6 Header",
    [bcmFieldQualifyIp4Protocol]                 = "Qualify Upon IPv4 Protocol.",
    [bcmFieldQualifyIp4Tos]                      = "Qualify Upon IPv4 TOS.",
    [bcmFieldQualifyIp4Ttl]                      = "Qualify Upon IPv4 TTL.",
    [bcmFieldQualifyAceEntryId]                  = "Qualify Upon Ace Entry ID.",
    [bcmFieldQualifyNetworkQos]                  = "Qualify Upon Network Qos.",
    [bcmFieldQualifyPtch]                        = "Opaque attribute field of the Injected packets. Part of the PTCH_2 header",
    [bcmFieldQualifyAppType]                     = "Packet Application type used by the ACL lookup. Can be either predefined (bcm_field_AppType_t) or user defined.",
    [bcmFieldQualifyInVportClass]                = "Qualify on the profile of an in LIF encoded as Gport",
    [bcmFieldQualifyVPortRangeCheck]             = "Virtual Port Range Check Results",
    [bcmFieldQualifyForwardingType]              = "This qualifier should be used together with input_arg, to indicate which layer number relative to forwarding layer to qualify upon,possible layer types are: bcmFieldLayerTypeXXX",
    [bcmFieldQualifyForwardingLayerQualifier]    = "This qualifier should be used together with input_arg, to indicate which layer number relative to forwarding layer to qualify upon, qualifies Layer Qualifiers (look for layer record qualifiers in UM)",
    [bcmFieldQualifyCascadedKeyValue]            = "Value of key cascaded from prior group in cascade",
    [bcmFieldQualifyContextId]                   = "In iPMF3 qualifies on the iPMF2 Context Id. In ePMF, qualifies on the FORWARD_CODE.",
    [bcmFieldQualifyForwardingProfile]           = "Qualifies on the Forwarding Profile.",
    [bcmFieldQualifyDstGport]                    = "Qualifies packet according to destination encoded as trap code.",
    [bcmFieldQualifyExtensionHeaderType]         = "Qualifies on Next Header Field in First Extension Header.",
    [bcmFieldQualifyInVPort0Raw]                    = "Qualifies on In LIF 0 input expects raw value.",
    [bcmFieldQualifyInVPort1Raw]                    = "Qualifies on In LIF 1 input expects raw value.",
    [bcmFieldQualifyOutVPort0Raw]                   = "Qualifies on Out LIF 0 input expects raw value.",
    [bcmFieldQualifyOutVPort1Raw]                   = "Qualifies on Out LIF 1 input expects raw value.",
    [bcmFieldQualifyOutVPort2Raw]                   = "Qualifies on Out LIF 2 input expects raw value.",
    [bcmFieldQualifyOutVPort3Raw]                   = "Qualifies on Out LIF 3 input expects raw value.",
    [bcmFieldQualifyAppTypePredefined]              = "The predefined AppType (bcm_field_AppType_t) used by the forwarding lookup.",
    [bcmFieldQualifyDstSysPortExt]              = "Qualifes upon TM Destination extension header",
    [bcmFieldQualifyDstSysPortExtPresent]       = "Qualifes upon if TM Destination extension header is present",
    [bcmFieldQualifyMirrorCode]              = "Matches on Mirror Code.",
    [bcmFieldQualifyMirrorData]              = "Matches on Mirror Data (qualifier).",
    [bcmFieldQualifyLearnData]                   = "Qualifies on data field in the Learn Info",
    [bcmFieldQualifyLearnSrcMac]                 = "Qualifies on learn source MAC",
    [bcmFieldQualifyLearnVsi]                    = "Qualifies on learn VSI",
    [bcmFieldQualifyLearnVlan]                   = "Qualifies on learn VLAN",
    [bcmFieldQualifyLearnStationMove]            = "Qualifies on learn Station move",
    [bcmFieldQualifyLearnMatch]                  = "Qualifies on learn Match",
    [bcmFieldQualifyLearnFound]                  = "Qualifies on learn Found",
    [bcmFieldQualifyLearnExpectedWon]            = "Qualifies on learn Expected Won",
    [bcmFieldQualifyVrfValue]                    = "Qualifies on the VRF part of forwarding data, without checking that the type is VRF.",
    [bcmFieldQualifySaLookupAcceptedStrength]    = "Qualifies on Accepted strength LSB returned from SA Lookup result. Qualifier is only relevant for bridged packets.",
    [bcmFieldQualifyLayerRecordTypeRaw]         = "Qualifies on the Layer Record Type. For possible values look at bcm_field_layer_type_t, input expects raw value.",
    [bcmFieldQualifySrcPortRaw]                 = "Qualifies on source port, input expects raw value.",
    [bcmFieldQualifyInPortWithoutCoreRaw]       = "Qualifies on Ingress Port. Does not include the core ID, caution should be taken when not adding entry by core, input expects raw value.",
    [bcmFieldQualifyVlanFormatRaw]              = "Qualifies on Incoming vlan structure format (untagged/single/double/priority-tagged), input expects raw value.",
    [bcmFieldQualifyInPortRaw]                  = "Qualifies on Ingress Port. Includes core ID, and can be used by entries for all cores, input expects raw value.",
    [bcmFieldQualifyColorRaw]                   = "Qualifies on packet color, input expects raw value.",
    [bcmFieldQualifyDstPortRaw]                 = "Qualifies on destination port, input expects raw value.",
    [bcmFieldQualifyOutPortRaw]                 = "Qualifies on Egress port. Does not include the core ID, caution should be taken when not adding entry by core, input expects raw value.",
    [bcmFieldQualifyPacketRes]                  = "When TRUE packet lookup result was Unknown Destination",
    [bcmFieldQualifyDstRpfValid]                = "Checks if the RPF Destination is valid.",
    [bcmFieldQualifyRpfOutVPort]                = "Qualifies on the RPF OUT LIF. Value should be GPORT with sub-type LIF.",
    [bcmFieldQualifyRpfOutInterface]            = "Qualifies on the RPF OUT LIF. Value should be L3 interface.",
    [bcmFieldQualifyRpfOutVPortRaw]               = "Qualifies on the RPF OUT LIF.",
    [bcmFieldQualifyRpfRouteValid]              = "Qualifies on the RPF Route valid.",
    [bcmFieldQualifyEcmpGroup]                  = "Qualifies on the ECMP group.",
    [bcmFieldQualifyIp4DstMulticast]            = "Qualify on IPv4 packets which their DIP is Multicast.",
    [bcmFieldQualifyOamInLifIdValid]            = "Qualifies if the LIF that has been found is an OAM LIF.",
    [bcmFieldQualifyOamInLifId]                 = "Qualifies on the last OAM LIF that has been found.",
    [bcmFieldQualifyLearnExtensionPresent]      = "Qualifies on whether PPH learn extension is present.",
    [bcmFieldQualifyMcastPkt]                   = "All ingress replicas will have this values set to 1.",
    [bcmFieldQualifyAppTypeRaw]                 = "Qualifies on packet Application type used by the ACL lookup. Can be either predefined or user defined. Input expects raw value.",
    [bcmFieldQualifyAppTypePredefinedRaw]       = "Qualifies on the predefined AppType used by the forwarding lookup. Input expects raw value.",
    [bcmFieldQualifyForwardingTypeRaw]          = "Same qualifier as bcmFieldQualifyForwardingType just doesnt have mapping function, i.e.input expects raw value (HW value).",
    [bcmFieldQualifyContextIdRaw]               = "In ePMF, qualifies on the FORWARD_CODE, and expects raw value.",
    [bcmFieldQualifyFtmhAsePresent]             = "Qualify packet on FTMH ASE present field.",
    [bcmFieldQualifyFtmhAseType]                = "Qualify packet on FTMH ASE type value.",
    [bcmFieldQualifyVipValid]                   = "Qualifies on SLLB Virtual Wire VW_VIP_VALID.",
    [bcmFieldQualifyVipId]                      = "Qualifies on SLLB Virtual Wire VW_VIP_ID.",
    [bcmFieldQualifyVIPMemberReference]         = "Qualifies on SLLB Virtual Wire VW_MEMBER_REFERENCE.",
    [bcmFieldQualifyPccHit]                     = "Qualifies on SLLB Virtual Wire VW_PCC_HIT.",
    [bcmFieldQualifyL2Format]                   = "Qualify on the type of the frame (see bcmFieldL2FormatXXX)",
    [bcmFieldQualifyRxTrapProfile]              = "Qualifies on Trap profile.",
    [bcmFieldQualifyAcInLifWideDataExtended]    = "Qualify on the Ac in-lif wide(generic) extended data: value[0]=32 LSB of the data value[1]=26b MSB of the data value[2]=hit_bit",
    [bcmFieldQualifyAcInLifWideDataExtendedRaw] = "Qualify on the Ac in-lif wide(generic) extended data. Input expects raw value.",
    [bcmFieldQualifyDstClassL2]                 = "Qualify on the MACT entry_group.",
    [bcmFieldQualifyIPv6FragmentedNonFirst]     = "Qualify on IPv6 packets where the IP Header is both fragmented and also not the first fragment.",
    [bcmFieldQualifyIPv4FragmentedNonFirst]     = "Qualify on IPv4 packets where the IP Header is both fragmented and also not the first fragment.",
    [bcmFieldQualifyIpMcFallbacktoBridge]       = "Qualify on IP MC packets that fallback2bridge.",
    [bcmFieldQualifyRchTimeStamp]               = "Qualify on RCH timestamp.",
    [bcmFieldQualifyRchForwardingAdditioalInfo] = "Qualify on the RCH forwarding additional info.",
    [bcmFieldQualifyRchType]                    = "Qualify on the type of RCH flow.",
    [bcmFieldQualifyRchVisibility]              = "Qualify on whether visibility for RCH is set.",
    [bcmFieldQualifyDstType]                    = "Qualify on 8MSB of destination, which indicate destination type. The endocding can be found in Arch guide (Destination Port Encoding).",
    [bcmFieldQualifyFecStatId0]                 = "Qualify on FER statistics ID 0.",
    [bcmFieldQualifyFecStatId1]                 = "Qualify on FER statistics ID 1.",
    [bcmFieldQualifyFecStatId2]                 = "Qualify on FER statistics ID 2.",
    [bcmFieldQualifyL3SrcBindHit]               = "Qualify on l3 source binding lookup Hit.",
    [bcmFieldQualifyVisibility]                 = "Qualify on whether FTMH visibility is set.",
    [bcmFieldQualifySrv6GsidNextSi]             = "Qualify on SRv6 GSID next segment index.",
    [bcmFieldQualifySrv6GsidNextGsid]           = "Qualify on SRv6 GSID next GSID.",
};

const dnx_field_qual_map_t dnx_global_qual_map[bcmFieldQualifyCount] = {
        /*
         * SW qualifiers, same for all stages. None currently in use.
         */
        /*
         * {
         * Header qualifiers, stage will be inserted by mapping routine, class is always HEADER
         */
        [bcmFieldQualifyDstMac]                = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_MAC_DST),             },
        [bcmFieldQualifySrcMac]                = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_MAC_SRC),             },
        [bcmFieldQualifyEtherTypeUntagged]     = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_ETHERTYPE),           },

        [bcmFieldQualifyTpid]                  = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_VLAN_TPID),           },
        [bcmFieldQualifyVlanId]                = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_VLAN_ID),             },
        [bcmFieldQualifyVlanPri]               = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_VLAN_PRI),            },
        [bcmFieldQualifyVlanCfi]               = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_VLAN_CFI),            },
        [bcmFieldQualifyVlanPriCfi]            = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_VLAN_PRI_CFI),        },

        [bcmFieldQualifyArpSenderIp4]          = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_ARP_SENDER_IP),       },
        [bcmFieldQualifyArpTargetIp4]          = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_ARP_TARGET_IP),       },
        [bcmFieldQualifyArpOpcode]             = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_ARP_OPCODE),          },

        [bcmFieldQualifyMplsLabel]             = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_MPLS_LABEL),          },
        [bcmFieldQualifyMplsLabelId]           = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_MPLS_LABEL_ID),       },
        [bcmFieldQualifyMplsLabelTtl]          = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_MPLS_TTL),            },
        [bcmFieldQualifyMplsLabelBos]          = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_MPLS_BOS),            },
        [bcmFieldQualifyMplsLabelExp]          = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_MPLS_TC),             },

        [bcmFieldQualifySrcIp]                 = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_IPV4_SRC),            },
        [bcmFieldQualifyDstIp]                 = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_IPV4_DST),            },
        [bcmFieldQualifyIp4Tos]                = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_IPV4_TOS),            },
        [bcmFieldQualifyIp4Ttl]                = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_IPV4_TTL),            },
        [bcmFieldQualifyIp4Protocol]           = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_IPV4_PROTOCOL),       },
        [bcmFieldQualifyIpFlags]               = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_IPV4_FLAGS),          },

        [bcmFieldQualifySrcIp6]                = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_IPV6_SIP),            },
        [bcmFieldQualifyDstIp6]                = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_IPV6_DIP),            },
        [bcmFieldQualifySrcIp6High]            = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_IPV6_SIP_HIGH),       },
        [bcmFieldQualifyDstIp6High]            = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_IPV6_DIP_HIGH),       },
        [bcmFieldQualifySrcIp6Low]             = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_IPV6_SIP_LOW),        },
        [bcmFieldQualifyDstIp6Low]             = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_IPV6_DIP_LOW),        },
        [bcmFieldQualifyIp6FlowLabel]          = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_IPV6_FLOW_LABEL),     },
        [bcmFieldQualifyIp6NextHeader]       = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_IPV6_NEXT_HEADER),    },
        [bcmFieldQualifyIp6HopLimit]           = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_IPV6_HOP_LIMIT),      },
        [bcmFieldQualifyIp6TrafficClass]       = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_IPV6_TC),             },
        [bcmFieldQualifyExtensionHeaderType]   = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_IPV6_1ST_EXTENSION_NEXT_HEADER),  },

        [bcmFieldQualifyL4DstPort]             = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_L4_DST_PORT),         },
        [bcmFieldQualifyL4SrcPort]             = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_L4_SRC_PORT),         },
        [bcmFieldQualifyTcpControl]            = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_TCP_CTL),             },

        [bcmFieldQualifyRchTimeStamp]          = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_RCH_TIME_STAMP),      },
        [bcmFieldQualifyRchForwardingAdditioalInfo]  = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_RCH_FORWARDING_ADDITIONAL_INFO),       },
        [bcmFieldQualifyRchType]               = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_RCH_TYPE)             },
        [bcmFieldQualifyRchVisibility]         = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_HEADER, 0, DNX_FIELD_HEADER_QUAL_RCH_VISIBILITY)       },
        /*
         * }
         */
        /*
         * Layer Record Based BCM Qualifiers
         * Stage not relevan since its global and relevant for all stages
         * {
         */
        [bcmFieldQualifyIpFrag]                  = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_IPV4_IS_FRAGMENTED),},
        [bcmFieldQualifyLayerRecordTypeRaw]      = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_PROTOCOL), },
        [bcmFieldQualifyLayerRecordType]         = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_PROTOCOL), BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_forwarding_type},
        [bcmFieldQualifyLayerRecordOffset]       = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_OFFSET),},
        [bcmFieldQualifyLayerRecordQualifier]    = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_QUALIFIER),},
        [bcmFieldQualifyEthernetMulticast]       = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_ETH_IS_DA_MC),},
        [bcmFieldQualifyEthernetBroadcast]       = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_ETH_IS_DA_BC),},
        [bcmFieldQualifyEthernetFirstTpidExist]  = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_ETH_1ST_TPID_EXIST),},
        [bcmFieldQualifyEthernetFirstTpidIndex]  = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_ETH_1ST_TPID_INDEX),},
        [bcmFieldQualifyEthernetSecondTpidExist] = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_ETH_2ND_TPID_EXIST),},
        [bcmFieldQualifyEthernetSecondTpidIndex] = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_ETH_2ND_TPID_INDEX),},
        [bcmFieldQualifyEthernetThirdTpidExist]  = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_ETH_3RD_TPID_EXIST),},
        [bcmFieldQualifyEthernetThirdTpidIndex]  = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_ETH_3RD_TPID_INDEX),},
        [bcmFieldQualifyL2Format]                = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_ETH_FRAME_TYPE), 0, dnx_field_convert_l2_format},
        [bcmFieldQualifyIp4DstMulticast]         = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_IPV4_IS_MC),},
        [bcmFieldQualifyIpHasOptions]            = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_IPV4_HAS_OPTION),},
        [bcmFieldQualifyIpFirstFrag]             = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_IPV4_IS_1ST_FRAGMENT),},
        [bcmFieldQualifyIpTunnelTypeRaw]         = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_IPV4_TUNNEL_TYPE), },
        [bcmFieldQualifyIpTunnelType]            = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_IPV4_TUNNEL_TYPE),BCM_TO_DNX_ADDITIONAL_OBJ , dnx_field_convert_tunnel_type},
        [bcmFieldQualifyIPv4FragmentedNonFirst]  = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_IPV4_FRAGMENTED_NON_FIRST),},
        [bcmFieldQualifyIp6MulticastCompatible]  = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_IPV6_IS_MC),},
        [bcmFieldQualifyIp6FirstAdditionalHeaderExist]  = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_IPV6_1ST_ADD_HEADER_EXIST),},
        [bcmFieldQualifyIp6FirstAdditionalHeader]  = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_IPV6_1ST_ADD_HEADER), 0, dnx_field_convert_ip6_additional_header},
        [bcmFieldQualifyIp6SecondAdditionalHeaderExist] = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_IPV6_2ND_ADD_HEADER_EXISTS),},
        [bcmFieldQualifyIp6SecondAdditionalHeader] = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_IPV6_2ND_ADD_HEADER),0 , dnx_field_convert_ip6_additional_header},
        [bcmFieldQualifyIPv6FragmentedNonFirst]  = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_IPV6_FRAGMENTED_NON_FIRST),},
        [bcmFieldQualifyItmhPphType]             = {DNX_QUAL(DNX_FIELD_QUAL_CLASS_LAYER_RECORD, 0, DNX_FIELD_LR_QUAL_ITMH_PPH_TYPE),},

        /*
         * }
         */
};

/*
 * BCM to DNX set maps per stage
 */
/*
 * End of BCM to DNX set maps per stage
 * {
 */
static const dnx_field_qual_map_t dnx_external_meta_qual_map[bcmFieldQualifyCount] = {

/*External*/    [bcmFieldQualifyGeneratedTtl]                = {DNX_FIELD_QUAL_IN_TTL,                         },
/*External*/    [bcmFieldQualifyIpMulticastCompatible]       = {DNX_FIELD_QUAL_PACKET_IS_COMPATIBLE_MC,        },
/*External*/    [bcmFieldQualifyColorRaw]                    = {DNX_FIELD_QUAL_DP,                             },
/*External*/    [bcmFieldQualifyColor]                       = {DNX_FIELD_QUAL_DP, BCM_TO_DNX_ADDITIONAL_OBJ , dnx_field_convert_color },
/*External*/    [bcmFieldQualifyPacketIsIEEE1588]            = {DNX_FIELD_QUAL_PACKET_IS_IEEE1588,             },
/*External*/    [bcmFieldQualifyIEEE1588Encapsulation]       = {DNX_FIELD_QUAL_IEEE1588_ENCAPSULATION,         },
/*External*/    [bcmFieldQualifyIEEE1588CompensateTimeStamp] = {DNX_FIELD_QUAL_IEEE1588_COMPENSATE_TIME_STAMP, },
/*External*/    [bcmFieldQualifyIEEE1588Command]             = {DNX_FIELD_QUAL_IEEE1588_COMMAND,               },
/*External*/    [bcmFieldQualifyIEEE1588HeaderOffset]        = {DNX_FIELD_QUAL_IEEE1588_HEADER_OFFSET,         },
/*External*/    [bcmFieldQualifyRxTrapCodeForSnoop]          = {DNX_FIELD_QUAL_SNOOP_CODE,                     },
/*External*/    [bcmFieldQualifyRxTrapCode]                  = {DNX_FIELD_QUAL_FWD_ACTION_CPU_TRAP_CODE,       },
/*External*/    [bcmFieldQualifyRxTrapData]                  = {DNX_FIELD_QUAL_FWD_ACTION_CPU_TRAP_QUAL,       },
/*External*/    [bcmFieldQualifyRxTrapStrength]              = {DNX_FIELD_QUAL_FWD_ACTION_STRENGTH,            },
/*External*/    [bcmFieldQualifyDstRpfGport]                 = {DNX_FIELD_QUAL_RPF_DST,                        },
/*External*/    [bcmFieldQualifyDstRpfValid]                 = {DNX_FIELD_QUAL_RPF_DST_VALID,},
/*External*/    [bcmFieldQualifyRpfRouteValid]               = {DNX_FIELD_QUAL_RPF_ROUTE_VALID,},
/*External*/    [bcmFieldQualifySrcPortRaw]                  = {DNX_FIELD_QUAL_SRC_SYS_PORT, },
/*External*/    [bcmFieldQualifySrcPort]                     = {DNX_FIELD_QUAL_SRC_SYS_PORT, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_sys_port_gport_to_port },
/*External*/    [bcmFieldQualifySrcModPortGport]             = {DNX_FIELD_QUAL_SRC_SYS_PORT,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_sys_port_gport_to_port},
/*External*/    [bcmFieldQualifyDstPort]                     = {DNX_FIELD_QUAL_FWD_ACTION_DESTINATION, },
/*External*/    [bcmFieldQualifyDstMulticastGroup]           = {DNX_FIELD_QUAL_FWD_ACTION_DESTINATION,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_dst},
/*External*/    [bcmFieldQualifyOamStampOffset]              = {DNX_FIELD_QUAL_OAM_STAMP_OFFSET,               },
/*External*/    [bcmFieldQualifyOamHeaderOffset]             = {DNX_FIELD_QUAL_OAM_OFFSET,                     },
/*External*/    [bcmFieldQualifyPacketSize]                  = {DNX_FIELD_QUAL_PACKET_HEADER_SIZE,             },
/*External*/    [bcmFieldQualifyInVPort0Raw]                 = {DNX_FIELD_QUAL_GLOB_IN_LIF_0, },
/*External*/    [bcmFieldQualifyInVPort1Raw]                 = {DNX_FIELD_QUAL_GLOB_IN_LIF_1, },
/*External*/    [bcmFieldQualifyOutVPort0Raw]                = {DNX_FIELD_QUAL_GLOB_OUT_LIF_0, },
/*External*/    [bcmFieldQualifyOutVPort1Raw]                = {DNX_FIELD_QUAL_GLOB_OUT_LIF_1, },
/*External*/    [bcmFieldQualifyInVPort0]                    = {DNX_FIELD_QUAL_GLOB_IN_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_in_lif},
/*External*/    [bcmFieldQualifyInVPort1]                    = {DNX_FIELD_QUAL_GLOB_IN_LIF_1,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_in_lif},
/*External*/    [bcmFieldQualifyOutVPort0]                   = {DNX_FIELD_QUAL_GLOB_OUT_LIF_0,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*External*/    [bcmFieldQualifyOutVPort1]                   = {DNX_FIELD_QUAL_GLOB_OUT_LIF_1,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*External*/    [bcmFieldQualifyInInterface]                 = {DNX_FIELD_QUAL_GLOB_IN_LIF_0,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*External*/    [bcmFieldQualifyOutInterface]                = {DNX_FIELD_QUAL_GLOB_OUT_LIF_0,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*External*/    [bcmFieldQualifyTrunkHashResult]             = {DNX_FIELD_QUAL_LAG_LB_KEY,                     },
/*External*/    [bcmFieldQualifyIntPriority]                 = {DNX_FIELD_QUAL_TC,                             },
/*External*/    [bcmFieldQualifyInVportClass0]               = {DNX_FIELD_QUAL_IN_LIF_PROFILE_0,               },
/*External*/    [bcmFieldQualifyInVportClass1]               = {DNX_FIELD_QUAL_IN_LIF_PROFILE_1,               },
/*External*/    [bcmFieldQualifyInPortWithoutCoreRaw]           = {DNX_FIELD_QUAL_PP_PORT, },
/*External*/    [bcmFieldQualifyInPortWithoutCore]           = {DNX_FIELD_QUAL_PP_PORT, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_port_without_core},
/*External*/    [bcmFieldQualifyVlanFormatRaw]                  = {DNX_FIELD_QUAL_INCOMING_TAG_STRUCTURE, },
/*External*/    [bcmFieldQualifyVlanFormat]                  = {DNX_FIELD_QUAL_INCOMING_TAG_STRUCTURE,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_vlan_format},
/*External*/    [bcmFieldQualifyL2Learn]                     = {DNX_FIELD_QUAL_INGRESS_LEARN_ENABLE,           },
/*External*/    [bcmFieldQualifyMplsForwardingLabelAction]   = {DNX_FIELD_QUAL_EEI,     },
/*External*/    [bcmFieldQualifyTrillEgressRbridge]          = {DNX_FIELD_QUAL_EEI,BCM_TO_DNX_ADDITIONAL_OBJ},
/*External*/    [bcmFieldQualifyISid]                        = {DNX_FIELD_QUAL_EEI,BCM_TO_DNX_ADDITIONAL_OBJ},
/*External*/    [bcmFieldQualifyVrf]                         = {DNX_FIELD_QUAL_FWD_DOMAIN,                     },
/*External*/    [bcmFieldQualifyInterfaceClassL2]            = {DNX_FIELD_QUAL_PMF_ETH_RIF_PROFILE,  },
/*External*/    [bcmFieldQualifyIncomingIpIfClass]           = {DNX_FIELD_QUAL_PMF_ETH_RIF_PROFILE, BCM_TO_DNX_ADDITIONAL_OBJ },
/*External*/    [bcmFieldQualifyAcInLifWideData]             = {DNX_FIELD_QUAL_AC_IN_LIF_WIDE_DATA,            },
/*External*/    [bcmFieldQualifyTracePacket]                 = {DNX_FIELD_QUAL_TRACE_PACKET,                   },
/*External*/    [bcmFieldQualifyForwardingAdditionalInfo]    = {DNX_FIELD_QUAL_FWD_LAYER_ADDITIONAL_INFO,                   },
/*External*/    [bcmFieldQualifyStatId0]                 = {DNX_FIELD_QUAL_FLP_STATISTICS_ID_0,    },
/*External*/    [bcmFieldQualifyStatId1]                 = {DNX_FIELD_QUAL_FLP_STATISTICS_ID_1,    },
/*External*/    [bcmFieldQualifyStatId2]                 = {DNX_FIELD_QUAL_FLP_STATISTICS_ID_2,    },
/*External*/    [bcmFieldQualifyStatId3]                 = {DNX_FIELD_QUAL_FLP_STATISTICS_ID_3,    },
/*External*/    [bcmFieldQualifyStatId4]                 = {DNX_FIELD_QUAL_FLP_STATISTICS_ID_4,    },
/*External*/    [bcmFieldQualifyStatId5]                 = {DNX_FIELD_QUAL_FLP_STATISTICS_ID_5,    },
/*External*/    [bcmFieldQualifyStatProfile0]            = {DNX_FIELD_QUAL_FLP_STATISTICS_ATR_0,   },
/*External*/    [bcmFieldQualifyStatProfile1]            = {DNX_FIELD_QUAL_FLP_STATISTICS_ATR_1,   },
/*External*/    [bcmFieldQualifyStatProfile2]            = {DNX_FIELD_QUAL_FLP_STATISTICS_ATR_2,   },
/*External*/    [bcmFieldQualifyStatProfile3]            = {DNX_FIELD_QUAL_FLP_STATISTICS_ATR_3,   },
/*External*/    [bcmFieldQualifyStatProfile4]            = {DNX_FIELD_QUAL_FLP_STATISTICS_ATR_4,   },
/*External*/    [bcmFieldQualifyStatProfile5]            = {DNX_FIELD_QUAL_FLP_STATISTICS_ATR_5,   },
/*External*/    [bcmFieldQualifyStatMetaData]            = {DNX_FIELD_QUAL_STATISTICS_META_DATA,   },
/*External*/    [bcmFieldQualifyNetworkQos]              = {DNX_FIELD_QUAL_NWK_QOS, },
/*External*/    [bcmFieldQualifyMirrorCode]                   = {DNX_FIELD_QUAL_MIRROR_CODE,},
/*External*/    [bcmFieldQualifyVrfValue]                     = {DNX_FIELD_QUAL_VRF_VALUE,},
/*External*/    [bcmFieldQualifySaLookupAcceptedStrength]     = {DNX_FIELD_QUAL_RPF_DEFAULT_ROUTE_FOUND,},
/*External*/    [bcmFieldQualifyRpfOutVPortRaw]              = {DNX_FIELD_QUAL_RPF_OUT_LIF, },
/*External*/    [bcmFieldQualifyRpfOutVPort]                 = {DNX_FIELD_QUAL_RPF_OUT_LIF,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*External*/    [bcmFieldQualifyRpfOutInterface]             = {DNX_FIELD_QUAL_RPF_OUT_LIF,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*External*/    [bcmFieldQualifyPacketRes]                   = {DNX_FIELD_QUAL_UNKNOWN_ADDRESS, },
/*External*/    [bcmFieldQualifyOamInLifIdValid]             = {DNX_FIELD_QUAL_VTT_OAM_LIF_0_VALID,},
/*External*/    [bcmFieldQualifyOamInLifId]                  = {DNX_FIELD_QUAL_VTT_OAM_LIF_0,},
/*External*/    [bcmFieldQualifyEcnValue]                    = {DNX_FIELD_QUAL_ECN,},
/*External*/    [bcmFieldQualifyVipValid]                    = {DNX_FIELD_QUAL_VW_VIP_VALID,},
/*External*/    [bcmFieldQualifyVipId]                       = {DNX_FIELD_QUAL_VW_VIP_ID,},
/*External*/    [bcmFieldQualifyVIPMemberReference]          = {DNX_FIELD_QUAL_VW_MEMBER_REFERENCE,},
/*External*/    [bcmFieldQualifyPccHit]                      = {DNX_FIELD_QUAL_VW_PCC_HIT,},
/*External*/    [bcmFieldQualifyAcInLifWideDataExtendedRaw]  = {DNX_FIELD_QUAL_AC_IN_LIF_WIDE_DATA_EXTENDED, },
/*External*/    [bcmFieldQualifyAcInLifWideDataExtended]     = {DNX_FIELD_QUAL_AC_IN_LIF_WIDE_DATA_EXTENDED,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ac_in_lif_wide_data_extended},
/*External*/    [bcmFieldQualifyDstClassL2]                  = {DNX_FIELD_QUAL_MACT_ENTRY_GROUPING, },
/*External*/    [bcmFieldQualifyL3SrcBindHit]                = {DNX_FIELD_QUAL_L3SRCBIND_HIT,},
};

static const dnx_field_qual_map_t dnx_ipmf1_meta_qual_map[bcmFieldQualifyCount] = {

/*iPMF1*/    [bcmFieldQualifyL4PortRangeCheck]            = {DNX_FIELD_QUAL_L4OPS,                          },
/*iPMF1*/    [bcmFieldQualifyRangeFirstHit0]              = {DNX_FIELD_QUAL_ENCODER0,                 },
/*iPMF1*/    [bcmFieldQualifyRangeFirstHit1]              = {DNX_FIELD_QUAL_ENCODER1,                 },
/*iPMF1*/    [bcmFieldQualifyRangeFirstHit2]              = {DNX_FIELD_QUAL_ENCODER2,                 },
/*iPMF1*/    [bcmFieldQualifyRangeFirstHit3]              = {DNX_FIELD_QUAL_ENCODER3,                 },
/*iPMF1*/    [bcmFieldQualifyGeneratedTtl]                = {DNX_FIELD_QUAL_IN_TTL,                         },
/*iPMF1*/    [bcmFieldQualifyIpMulticastCompatible]       = {DNX_FIELD_QUAL_PACKET_IS_COMPATIBLE_MC,        },
/*iPMF1*/    [bcmFieldQualifyColorRaw]                    = {DNX_FIELD_QUAL_DP, },
/*iPMF1*/    [bcmFieldQualifyColor]                       = {DNX_FIELD_QUAL_DP, BCM_TO_DNX_ADDITIONAL_OBJ , dnx_field_convert_color },
/*iPMF1*/    [bcmFieldQualifyPacketIsIEEE1588]            = {DNX_FIELD_QUAL_PACKET_IS_IEEE1588,             },
/*iPMF1*/    [bcmFieldQualifyIEEE1588Encapsulation]       = {DNX_FIELD_QUAL_IEEE1588_ENCAPSULATION,         },
/*iPMF1*/    [bcmFieldQualifyIEEE1588CompensateTimeStamp] = {DNX_FIELD_QUAL_IEEE1588_COMPENSATE_TIME_STAMP, },
/*iPMF1*/    [bcmFieldQualifyIEEE1588Command]             = {DNX_FIELD_QUAL_IEEE1588_COMMAND,               },
/*iPMF1*/    [bcmFieldQualifyIEEE1588HeaderOffset]        = {DNX_FIELD_QUAL_IEEE1588_HEADER_OFFSET,         },
/*iPMF1*/    [bcmFieldQualifyRxTrapCodeForSnoop]          = {DNX_FIELD_QUAL_SNOOP_CODE,                     },
/*iPMF1*/    [bcmFieldQualifyRxTrapCode]                  = {DNX_FIELD_QUAL_FWD_ACTION_CPU_TRAP_CODE,       },
/*iPMF1*/    [bcmFieldQualifyRxTrapData]                  = {DNX_FIELD_QUAL_FWD_ACTION_CPU_TRAP_QUAL,       },
/*iPMF1*/    [bcmFieldQualifyRxTrapStrength]              = {DNX_FIELD_QUAL_FWD_ACTION_STRENGTH,            },
/*iPMF1*/    [bcmFieldQualifyDstRpfGport]                 = {DNX_FIELD_QUAL_RPF_DST,                        },
/*iPMF1*/    [bcmFieldQualifyDstRpfValid]                 = {DNX_FIELD_QUAL_RPF_DST_VALID,},
/*iPMF1*/    [bcmFieldQualifyRpfRouteValid]               = {DNX_FIELD_QUAL_RPF_ROUTE_VALID,},
/*iPMF1*/    [bcmFieldQualifyKeyGenVar]                   = {DNX_FIELD_QUAL_CONTEXT_KEY_GEN_VAR,            },
/*iPMF1*/    [bcmFieldQualifySrcPortRaw]                  = {DNX_FIELD_QUAL_SRC_SYS_PORT, },
/*iPMF1*/    [bcmFieldQualifySrcPort]                     = {DNX_FIELD_QUAL_SRC_SYS_PORT,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_sys_port_gport_to_port},
/*iPMF1*/    [bcmFieldQualifySrcModPortGport]             = {DNX_FIELD_QUAL_SRC_SYS_PORT,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_sys_port_gport_to_port},
/*iPMF1*/    [bcmFieldQualifyDstPort]                     = {DNX_FIELD_QUAL_FWD_ACTION_DESTINATION, },
/*iPMF1*/    [bcmFieldQualifyDstMulticastGroup]           = {DNX_FIELD_QUAL_FWD_ACTION_DESTINATION,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_dst},
/*iPMF1*/    [bcmFieldQualifyOamUpMep]                    = {DNX_FIELD_QUAL_OAM_UP_MEP,                     },
/*iPMF1*/    [bcmFieldQualifyOamSubtype]                  = {DNX_FIELD_QUAL_OAM_SUB_TYPE,                   },
/*iPMF1*/    [bcmFieldQualifyOamStampOffset]              = {DNX_FIELD_QUAL_OAM_STAMP_OFFSET,               },
/*iPMF1*/    [bcmFieldQualifyOamHeaderOffset]             = {DNX_FIELD_QUAL_OAM_OFFSET,                     },
/*iPMF1*/    [bcmFieldQualifyOamMepId]                    = {DNX_FIELD_QUAL_OAM_ID,                         },
/*iPMF1*/    [bcmFieldQualifyOamMeterDisable]             = {DNX_FIELD_QUAL_OAM_METER_DISABLE,              },
/*iPMF1*/    [bcmFieldQualifyPacketSize]                  = {DNX_FIELD_QUAL_PACKET_HEADER_SIZE,             },
/*iPMF1*/    [bcmFieldQualifyInVPort0Raw]                 = {DNX_FIELD_QUAL_GLOB_IN_LIF_0, },
/*iPMF1*/    [bcmFieldQualifyInVPort1Raw]                 = {DNX_FIELD_QUAL_GLOB_IN_LIF_1, },
/*iPMF1*/    [bcmFieldQualifyOutVPort0Raw]                = {DNX_FIELD_QUAL_GLOB_OUT_LIF_0, },
/*iPMF1*/    [bcmFieldQualifyOutVPort1Raw]                = {DNX_FIELD_QUAL_GLOB_OUT_LIF_1, },
/*iPMF1*/    [bcmFieldQualifyInVPort0]                    = {DNX_FIELD_QUAL_GLOB_IN_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_in_lif},
/*iPMF1*/    [bcmFieldQualifyInVPort1]                    = {DNX_FIELD_QUAL_GLOB_IN_LIF_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_in_lif},
/*iPMF1*/    [bcmFieldQualifyOutVPort0]                   = {DNX_FIELD_QUAL_GLOB_OUT_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*iPMF1*/    [bcmFieldQualifyOutVPort1]                   = {DNX_FIELD_QUAL_GLOB_OUT_LIF_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*iPMF1*/    [bcmFieldQualifyInInterface]                 = {DNX_FIELD_QUAL_GLOB_IN_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*iPMF1*/    [bcmFieldQualifyOutInterface]                = {DNX_FIELD_QUAL_GLOB_OUT_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*iPMF1*/    [bcmFieldQualifyTrunkHashResult]             = {DNX_FIELD_QUAL_LAG_LB_KEY,                     },
/*iPMF1*/    [bcmFieldQualifyIntPriority]                 = {DNX_FIELD_QUAL_TC,                             },
/*iPMF1*/    [bcmFieldQualifyExternalHit0]                = {DNX_FIELD_QUAL_ELK_LKP_HIT_0,                  },
/*iPMF1*/    [bcmFieldQualifyExternalHit1]                = {DNX_FIELD_QUAL_ELK_LKP_HIT_1,                  },
/*iPMF1*/    [bcmFieldQualifyExternalHit2]                = {DNX_FIELD_QUAL_ELK_LKP_HIT_2,                  },
/*iPMF1*/    [bcmFieldQualifyExternalHit3]                = {DNX_FIELD_QUAL_ELK_LKP_HIT_3,                  },
/*iPMF1*/    [bcmFieldQualifyExternalHit4]                = {DNX_FIELD_QUAL_ELK_LKP_HIT_4,                  },
/*iPMF1*/    [bcmFieldQualifyExternalHit5]                = {DNX_FIELD_QUAL_ELK_LKP_HIT_5,                  },
/*iPMF1*/    [bcmFieldQualifyExternalHit6]                = {DNX_FIELD_QUAL_ELK_LKP_HIT_6,                  },
/*iPMF1*/    [bcmFieldQualifyExternalHit7]                = {DNX_FIELD_QUAL_ELK_LKP_HIT_7,                  },
/*iPMF1*/    [bcmFieldQualifyInVportClass0]               = {DNX_FIELD_QUAL_IN_LIF_PROFILE_0,               },
/*iPMF1*/    [bcmFieldQualifyInVportClass1]               = {DNX_FIELD_QUAL_IN_LIF_PROFILE_1,               },
/*iPMF1*/    [bcmFieldQualifyTranslatedOuterVlanId ]      = {DNX_FIELD_QUAL_VLAN_EDIT_VID_1,                },
/*iPMF1*/    [bcmFieldQualifyTranslatedOuterVlanPri]      = {DNX_FIELD_QUAL_VLAN_EDIT_PCP_1,                },
/*iPMF1*/    [bcmFieldQualifyTranslatedOuterVlanCfi]      = {DNX_FIELD_QUAL_VLAN_EDIT_DEI_1,                },
/*iPMF1*/    [bcmFieldQualifyTranslatedInnerVlanId ]      = {DNX_FIELD_QUAL_VLAN_EDIT_VID_2,                },
/*iPMF1*/    [bcmFieldQualifyTranslatedInnerVlanPri]      = {DNX_FIELD_QUAL_VLAN_EDIT_PCP_2,                },
/*iPMF1*/    [bcmFieldQualifyTranslatedInnerVlanCfi]      = {DNX_FIELD_QUAL_VLAN_EDIT_DEI_2,                },
/*iPMF1*/    [bcmFieldQualifyVlanAction]                  = {DNX_FIELD_QUAL_VLAN_EDIT_CMD_INDEX,            },
/*iPMF1*/    [bcmFieldQualifyInPortRaw]                   = {DNX_FIELD_QUAL_IN_PORT, },
/*iPMF1*/    [bcmFieldQualifyInPortWithoutCoreRaw]        = {DNX_FIELD_QUAL_PP_PORT, },
/*iPMF1*/    [bcmFieldQualifyInPort]                      = {DNX_FIELD_QUAL_IN_PORT, BCM_TO_DNX_ADDITIONAL_OBJ , dnx_field_convert_gport_to_port_with_core},
/*iPMF1*/    [bcmFieldQualifyInPortWithoutCore]           = {DNX_FIELD_QUAL_PP_PORT, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_port_without_core},
/*iPMF1*/    [bcmFieldQualifyPacketLengthRangeCheck]      = {DNX_FIELD_QUAL_PACKET_HEADER_SIZE_RANGE,       },
/*iPMF1*/    [bcmFieldQualifyVlanFormatRaw]               = {DNX_FIELD_QUAL_INCOMING_TAG_STRUCTURE, },
/*iPMF1*/    [bcmFieldQualifyVlanFormat]                  = {DNX_FIELD_QUAL_INCOMING_TAG_STRUCTURE,  BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_vlan_format},
/*iPMF1*/    [bcmFieldQualifyL2Learn]                     = {DNX_FIELD_QUAL_INGRESS_LEARN_ENABLE,           },
/*iPMF1*/    [bcmFieldQualifyMplsForwardingLabelAction]   = {DNX_FIELD_QUAL_EEI,     },
/*iPMF1*/    [bcmFieldQualifyTrillEgressRbridge]          = {DNX_FIELD_QUAL_EEI, BCM_TO_DNX_ADDITIONAL_OBJ},
/*iPMF1*/    [bcmFieldQualifyISid]                        = {DNX_FIELD_QUAL_EEI, BCM_TO_DNX_ADDITIONAL_OBJ},
/*iPMF1*/    [bcmFieldQualifyVrf]                         = {DNX_FIELD_QUAL_FWD_DOMAIN,},
/*iPMF1*/    [bcmFieldQualifyVpn]                         = {DNX_FIELD_QUAL_FWD_DOMAIN,BCM_TO_DNX_ADDITIONAL_OBJ},
/*iPMF1*/    [bcmFieldQualifyForwardingLayerIndex]        = {DNX_FIELD_QUAL_FWD_LAYER_INDEX,                },
/*iPMF1*/    [bcmFieldQualifyInterfaceClassL2]            = {DNX_FIELD_QUAL_PMF_ETH_RIF_PROFILE,            },
/*iPMF1*/    [bcmFieldQualifyIncomingIpIfClass]           = {DNX_FIELD_QUAL_PMF_ETH_RIF_PROFILE,BCM_TO_DNX_ADDITIONAL_OBJ},
/*iPMF1*/    [bcmFieldQualifyAcInLifWideData]             = {DNX_FIELD_QUAL_AC_IN_LIF_WIDE_DATA,            },
/*iPMF1*/    [bcmFieldQualifyNativeAcInLifWideData]       = {DNX_FIELD_QUAL_NATIVE_AC_IN_LIF_WIDE_DATA,     },
/*iPMF1*/    [bcmFieldQualifyPweInLifWideData]            = {DNX_FIELD_QUAL_PWE_IN_LIF_WIDE_DATA,           },
/*iPMF1*/    [bcmFieldQualifyIpTunnelInLifWideData]       = {DNX_FIELD_QUAL_IP_TUNNEL_IN_LIF_WIDE_DATA,     },
/*iPMF1*/    [bcmFieldQualifyPortClassPacketProcessing]   = {DNX_FIELD_QUAL_PP_PORT_PMF_PROFILE,            },
/*iPMF1*/    [bcmFieldQualifyPortClassTrafficManagement]  = {DNX_FIELD_QUAL_TM_PORT_PMF_PROFILE,            },
/*iPMF1*/    [bcmFieldQualifyPortClassPacketProcessingGeneralData] = {DNX_FIELD_QUAL_PP_PORT_PMF_GENERAL_DATA, },
/*iPMF1*/    [bcmFieldQualifyBierStringOffset]            = {DNX_FIELD_QUAL_BIER_STR_OFFSET,                },
/*iPMF1*/    [bcmFieldQualifyBierStringSize]              = {DNX_FIELD_QUAL_BIER_STR_SIZE,                  },
/*iPMF1*/    [bcmFieldQualifyPacketIsBier]                = {DNX_FIELD_QUAL_PACKET_IS_BIER,                 },
/*iPMF1*/    [bcmFieldQualifyTracePacket]                 = {DNX_FIELD_QUAL_TRACE_PACKET,                   },
/*iPMF1*/    [bcmFieldQualifyForwardingAdditionalInfo]    = {DNX_FIELD_QUAL_FWD_LAYER_ADDITIONAL_INFO,                   },
/*iPMF1*/    [bcmFieldQualifyStatId0]                 = {DNX_FIELD_QUAL_STATISTICS_ID_0,        },
/*iPMF1*/    [bcmFieldQualifyStatId1]                 = {DNX_FIELD_QUAL_STATISTICS_ID_1,        },
/*iPMF1*/    [bcmFieldQualifyStatId2]                 = {DNX_FIELD_QUAL_STATISTICS_ID_2,        },
/*iPMF1*/    [bcmFieldQualifyStatId3]                 = {DNX_FIELD_QUAL_STATISTICS_ID_3,        },
/*iPMF1*/    [bcmFieldQualifyStatId4]                 = {DNX_FIELD_QUAL_STATISTICS_ID_4,        },
/*iPMF1*/    [bcmFieldQualifyStatId5]                 = {DNX_FIELD_QUAL_STATISTICS_ID_5,        },
/*iPMF1*/    [bcmFieldQualifyStatId6]                 = {DNX_FIELD_QUAL_STATISTICS_ID_6,        },
/*iPMF1*/    [bcmFieldQualifyStatId7]                 = {DNX_FIELD_QUAL_STATISTICS_ID_7,        },
/*iPMF1*/    [bcmFieldQualifyStatId8]                 = {DNX_FIELD_QUAL_STATISTICS_ID_8,        },
/*iPMF1*/    [bcmFieldQualifyStatId9]                 = {DNX_FIELD_QUAL_STATISTICS_ID_9,        },
/*iPMF1*/    [bcmFieldQualifyStatProfile0]            = {DNX_FIELD_QUAL_STATISTICS_ATR_0,       },
/*iPMF1*/    [bcmFieldQualifyStatProfile1]            = {DNX_FIELD_QUAL_STATISTICS_ATR_1,       },
/*iPMF1*/    [bcmFieldQualifyStatProfile2]            = {DNX_FIELD_QUAL_STATISTICS_ATR_2,       },
/*iPMF1*/    [bcmFieldQualifyStatProfile3]            = {DNX_FIELD_QUAL_STATISTICS_ATR_3,       },
/*iPMF1*/    [bcmFieldQualifyStatProfile4]            = {DNX_FIELD_QUAL_STATISTICS_ATR_4,       },
/*iPMF1*/    [bcmFieldQualifyStatProfile5]            = {DNX_FIELD_QUAL_STATISTICS_ATR_5,       },
/*iPMF1*/    [bcmFieldQualifyStatProfile6]            = {DNX_FIELD_QUAL_STATISTICS_ATR_6,       },
/*iPMF1*/    [bcmFieldQualifyStatProfile7]            = {DNX_FIELD_QUAL_STATISTICS_ATR_7,       },
/*iPMF1*/    [bcmFieldQualifyStatProfile8]            = {DNX_FIELD_QUAL_STATISTICS_ATR_8,       },
/*iPMF1*/    [bcmFieldQualifyStatProfile9]            = {DNX_FIELD_QUAL_STATISTICS_ATR_9,       },
/*iPMF1*/    [bcmFieldQualifyExtStat0]                = {DNX_FIELD_QUAL_EXT_STATISTICS_ID_0,    },
/*iPMF1*/    [bcmFieldQualifyExtStat1]                = {DNX_FIELD_QUAL_EXT_STATISTICS_ID_1,    },
/*iPMF1*/    [bcmFieldQualifyExtStat2]                = {DNX_FIELD_QUAL_EXT_STATISTICS_ID_2,    },
/*iPMF1*/    [bcmFieldQualifyExtStat3]                = {DNX_FIELD_QUAL_EXT_STATISTICS_ID_3,    },
/*iPMF1*/    [bcmFieldQualifyExtStatProfile0]         = {DNX_FIELD_QUAL_EXT_STATISTICS_ATR_0,   },
/*iPMF1*/    [bcmFieldQualifyExtStatProfile1]         = {DNX_FIELD_QUAL_EXT_STATISTICS_ATR_1,   },
/*iPMF1*/    [bcmFieldQualifyExtStatProfile2]         = {DNX_FIELD_QUAL_EXT_STATISTICS_ATR_2,   },
/*iPMF1*/    [bcmFieldQualifyExtStatProfile3]         = {DNX_FIELD_QUAL_EXT_STATISTICS_ATR_3,   },
/*iPMF1*/    [bcmFieldQualifyStatMetaData]            = {DNX_FIELD_QUAL_STATISTICS_META_DATA,   },
/*iPMF1*/    [bcmFieldQualifyEcmpLoadBalanceKey0]     = {DNX_FIELD_QUAL_ECMP_LB_KEY_0,          },
/*iPMF1*/    [bcmFieldQualifyEcmpLoadBalanceKey1]     = {DNX_FIELD_QUAL_ECMP_LB_KEY_1,          },
/*iPMF1*/    [bcmFieldQualifyEcmpLoadBalanceKey2]     = {DNX_FIELD_QUAL_ECMP_LB_KEY_2,          },
/*iPMF1*/    [bcmFieldQualifyNetworkQos]              = {DNX_FIELD_QUAL_NWK_QOS, },
/*iPMF1*/    [bcmFieldQualifyMirrorCode]                  = {DNX_FIELD_QUAL_MIRROR_CODE,},
/*iPMF1*/    [bcmFieldQualifyPtch]                        = {DNX_FIELD_QUAL_PRT_QUALIFIER,},
/*iPMF1*/    [bcmFieldQualifyLearnData]                   = {DNX_FIELD_QUAL_LEARN_DATA,},
/*iPMF1*/    [bcmFieldQualifyLearnSrcMac]                 = {DNX_FIELD_QUAL_LEARN_SRC_MAC,},
/*iPMF1*/    [bcmFieldQualifyLearnVsi]                    = {DNX_FIELD_QUAL_LEARN_VSI,},
/*iPMF1*/    [bcmFieldQualifyLearnVlan]                   = {DNX_FIELD_QUAL_LEARN_VLAN,},
/*iPMF1*/    [bcmFieldQualifyLearnStationMove]            = {DNX_FIELD_QUAL_LEARN_STATION_MOVE,},
/*iPMF1*/    [bcmFieldQualifyLearnMatch]                  = {DNX_FIELD_QUAL_LEARN_MATCH,},
/*iPMF1*/    [bcmFieldQualifyLearnFound]                  = {DNX_FIELD_QUAL_LEARN_FOUND,},
/*iPMF1*/    [bcmFieldQualifyLearnExpectedWon]            = {DNX_FIELD_QUAL_LEARN_EXPECTED_WON,},
/*iPMF1*/    [bcmFieldQualifyVrfValue]                    = {DNX_FIELD_QUAL_VRF_VALUE,},
/*iPMF1*/    [bcmFieldQualifySaLookupAcceptedStrength]    = {DNX_FIELD_QUAL_RPF_DEFAULT_ROUTE_FOUND,},
/*iPMF1*/    [bcmFieldQualifyRpfOutVPortRaw]              = {DNX_FIELD_QUAL_RPF_OUT_LIF, },
/*iPMF1*/    [bcmFieldQualifyRpfOutVPort]                 = {DNX_FIELD_QUAL_RPF_OUT_LIF, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*iPMF1*/    [bcmFieldQualifyRpfOutInterface]             = {DNX_FIELD_QUAL_RPF_OUT_LIF, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*iPMF1*/    [bcmFieldQualifyPacketRes]                   = {DNX_FIELD_QUAL_UNKNOWN_ADDRESS, },
/*iPMF1*/    [bcmFieldQualifyEcnValue]                    = {DNX_FIELD_QUAL_ECN,},
/*iPMF1*/    [bcmFieldQualifyVipValid]                    = {DNX_FIELD_QUAL_VW_VIP_VALID,},
/*iPMF1*/    [bcmFieldQualifyVipId]                       = {DNX_FIELD_QUAL_VW_VIP_ID,},
/*iPMF1*/    [bcmFieldQualifyVIPMemberReference]          = {DNX_FIELD_QUAL_VW_MEMBER_REFERENCE,},
/*iPMF1*/    [bcmFieldQualifyPccHit]                      = {DNX_FIELD_QUAL_VW_PCC_HIT,},
/*iPMF1*/    [bcmFieldQualifyAcInLifWideDataExtendedRaw]  = {DNX_FIELD_QUAL_AC_IN_LIF_WIDE_DATA_EXTENDED, },
/*iPMF1*/    [bcmFieldQualifyAcInLifWideDataExtended]     = {DNX_FIELD_QUAL_AC_IN_LIF_WIDE_DATA_EXTENDED, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ac_in_lif_wide_data_extended},
/*iPMF1*/    [bcmFieldQualifyDstClassL2]                  = {DNX_FIELD_QUAL_MACT_ENTRY_GROUPING, },
/*iPMF1*/    [bcmFieldQualifyAppTypeRaw]                  = {DNX_FIELD_QUAL_MKX_OPCODE, },
/*iPMF1*/    [bcmFieldQualifyAppType]                     = {DNX_FIELD_QUAL_MKX_OPCODE, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_app_type_opcode},
/*iPMF1*/    [bcmFieldQualifyL3SrcBindHit]                = {DNX_FIELD_QUAL_L3SRCBIND_HIT, },
/*iPMF1*/    [bcmFieldQualifySrv6GsidNextSi]              = {DNX_FIELD_QUAL_SRV6_GSID_NEXT_SI},
/*iPMF1*/    [bcmFieldQualifySrv6GsidNextGsid]            = {DNX_FIELD_QUAL_SRV6_GSID_NEXT_GSID},

};

static const dnx_field_qual_map_t dnx_ipmf2_meta_qual_map[bcmFieldQualifyCount] = {
/*iPMF2*/    [bcmFieldQualifyHashValue]                   = {DNX_FIELD_QUAL_TRJ_HASH,                       },
/*iPMF2*/    [bcmFieldQualifyNetworkLoadBalanceKey]       = {DNX_FIELD_QUAL_NWK_LB_KEY,                     },
/*iPMF2*/    [bcmFieldQualifyEcmpLoadBalanceKey0]         = {DNX_FIELD_QUAL_ECMP_LB_KEY_0,                  },
/*iPMF2*/    [bcmFieldQualifyEcmpLoadBalanceKey1]         = {DNX_FIELD_QUAL_ECMP_LB_KEY_1,                  },
/*iPMF2*/    [bcmFieldQualifyEcmpLoadBalanceKey2]         = {DNX_FIELD_QUAL_ECMP_LB_KEY_2,                  },
/*iPMF2*/    [bcmFieldQualifyStateTableData]              = {DNX_FIELD_QUAL_STATE_TABLE_DATA,               },
/*iPMF2*/    [bcmFieldQualifyCompareKeysResult0]          = {DNX_FIELD_QUAL_CMP_KEY_0_DECODED,              },
/*iPMF2*/    [bcmFieldQualifyCompareKeysResult1]          = {DNX_FIELD_QUAL_CMP_KEY_1_DECODED,              },
/*iPMF2*/    [bcmFieldQualifyCompareKeysTcam0]            = {DNX_FIELD_QUAL_CMP_KEY_TCAM_0_DECODED,         },
/*iPMF2*/    [bcmFieldQualifyCompareKeysTcam1]            = {DNX_FIELD_QUAL_CMP_KEY_TCAM_1_DECODED,         },

};

static const dnx_field_qual_map_t dnx_ipmf3_meta_qual_map[bcmFieldQualifyCount] = {
/*iPMF3*/    [bcmFieldQualifyGeneratedTtl]                = {DNX_FIELD_QUAL_IN_TTL,                         },
/*iPMF3*/    [bcmFieldQualifyPacketIsIEEE1588]            = {DNX_FIELD_QUAL_PACKET_IS_IEEE1588,             },
/*iPMF3*/    [bcmFieldQualifyIEEE1588Encapsulation]       = {DNX_FIELD_QUAL_IEEE1588_ENCAPSULATION,         },
/*iPMF3*/    [bcmFieldQualifyIEEE1588CompensateTimeStamp] = {DNX_FIELD_QUAL_IEEE1588_COMPENSATE_TIME_STAMP, },
/*iPMF3*/    [bcmFieldQualifyIEEE1588Command]             = {DNX_FIELD_QUAL_IEEE1588_COMMAND,               },
/*iPMF3*/    [bcmFieldQualifyIEEE1588HeaderOffset]        = {DNX_FIELD_QUAL_IEEE1588_HEADER_OFFSET,         },
/*iPMF3*/    [bcmFieldQualifyStackingRoute]               = {DNX_FIELD_QUAL_STACKING_ROUTE_HISTORY_BITMAP,  },
/*iPMF3*/    [bcmFieldQualifyDstRpfGport]                 = {DNX_FIELD_QUAL_RPF_DST,                        },
/*iPMF3*/    [bcmFieldQualifyDstRpfValid]                 = {DNX_FIELD_QUAL_RPF_DST_VALID,                  },
/*iPMF3*/    [bcmFieldQualifyKeyGenVar]                   = {DNX_FIELD_QUAL_CONTEXT_KEY_GEN_VAR,            },
/*iPMF3*/    [bcmFieldQualifySrcPortRaw]                  = {DNX_FIELD_QUAL_SRC_SYS_PORT,                   },
/*iPMF3*/    [bcmFieldQualifySrcPort]                     = {DNX_FIELD_QUAL_SRC_SYS_PORT,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_sys_port_gport_to_port},
/*iPMF3*/    [bcmFieldQualifySrcModPortGport]             = {DNX_FIELD_QUAL_SRC_SYS_PORT,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_sys_port_gport_to_port},
/*iPMF3*/    [bcmFieldQualifyInPortRaw]                   = {DNX_FIELD_QUAL_IN_PORT,                        },
/*iPMF3*/    [bcmFieldQualifyInPort]                      = {DNX_FIELD_QUAL_IN_PORT,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_port_with_core},
/*iPMF3*/    [bcmFieldQualifyInPortWithoutCoreRaw]        = {DNX_FIELD_QUAL_PP_PORT, },
/*iPMF3*/    [bcmFieldQualifyInPortWithoutCore]           = {DNX_FIELD_QUAL_PP_PORT,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_port_without_core},
/*iPMF3*/    [bcmFieldQualifyRxTrapCodeForSnoop]          = {DNX_FIELD_QUAL_SNOOP_CODE,                     },
/*iPMF3*/    [bcmFieldQualifyRxSnoopStrength]             = {DNX_FIELD_QUAL_SNOOP_STRENGTH,                 },
/*iPMF3*/    [bcmFieldQualifyOamUpMep]                    = {DNX_FIELD_QUAL_OAM_UP_MEP,                     },
/*iPMF3*/    [bcmFieldQualifyOamSubtype]                  = {DNX_FIELD_QUAL_OAM_SUB_TYPE,                   },
/*iPMF3*/    [bcmFieldQualifyOamStampOffset]              = {DNX_FIELD_QUAL_OAM_STAMP_OFFSET,               },
/*iPMF3*/    [bcmFieldQualifyOamHeaderOffset]             = {DNX_FIELD_QUAL_OAM_OFFSET,                     },
/*iPMF3*/    [bcmFieldQualifyOamMepId]                    = {DNX_FIELD_QUAL_OAM_ID,                         },
/*iPMF3*/    [bcmFieldQualifyInVPort0Raw]                 = {DNX_FIELD_QUAL_GLOB_IN_LIF_0},
/*iPMF3*/    [bcmFieldQualifyInVPort1Raw]                 = {DNX_FIELD_QUAL_GLOB_IN_LIF_1 },
/*iPMF3*/    [bcmFieldQualifyOutVPort0Raw]                = {DNX_FIELD_QUAL_GLOB_OUT_LIF_0 },
/*iPMF3*/    [bcmFieldQualifyOutVPort1Raw]                = {DNX_FIELD_QUAL_GLOB_OUT_LIF_1 },
/*iPMF3*/    [bcmFieldQualifyOutVPort2Raw]                = {DNX_FIELD_QUAL_GLOB_OUT_LIF_2 },
/*iPMF3*/    [bcmFieldQualifyOutVPort3Raw]                = {DNX_FIELD_QUAL_GLOB_OUT_LIF_3},
/*iPMF3*/    [bcmFieldQualifyInVPort0]                    = {DNX_FIELD_QUAL_GLOB_IN_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_in_lif},
/*iPMF3*/    [bcmFieldQualifyInVPort1]                    = {DNX_FIELD_QUAL_GLOB_IN_LIF_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_in_lif},
/*iPMF3*/    [bcmFieldQualifyOutVPort0]                   = {DNX_FIELD_QUAL_GLOB_OUT_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*iPMF3*/    [bcmFieldQualifyOutVPort1]                   = {DNX_FIELD_QUAL_GLOB_OUT_LIF_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*iPMF3*/    [bcmFieldQualifyOutVPort2]                   = {DNX_FIELD_QUAL_GLOB_OUT_LIF_2, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*iPMF3*/    [bcmFieldQualifyOutVPort3]                   = {DNX_FIELD_QUAL_GLOB_OUT_LIF_3, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*iPMF3*/    [bcmFieldQualifyInInterface]                 = {DNX_FIELD_QUAL_GLOB_IN_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*iPMF3*/    [bcmFieldQualifyOutInterface]                = {DNX_FIELD_QUAL_GLOB_OUT_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*iPMF3*/    [bcmFieldQualifyDstPort]                     = {DNX_FIELD_QUAL_FWD_ACTION_DESTINATION},
/*iPMF3*/    [bcmFieldQualifyDstGport]                    = {DNX_FIELD_QUAL_FWD_ACTION_DESTINATION, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_trap_gport_to_hw_dest},
/*iPMF3*/    [bcmFieldQualifyTrunkHashResult]             = {DNX_FIELD_QUAL_LAG_LB_KEY,                     },
/*iPMF3*/    [bcmFieldQualifyInVportClass0]               = {DNX_FIELD_QUAL_IN_LIF_PROFILE_0,               },
/*iPMF3*/    [bcmFieldQualifyInVportClass1]               = {DNX_FIELD_QUAL_IN_LIF_PROFILE_1,               },
/*iPMF3*/    [bcmFieldQualifyTranslatedOuterVlanId ]      = {DNX_FIELD_QUAL_VLAN_EDIT_VID_1,                },
/*iPMF3*/    [bcmFieldQualifyTranslatedOuterVlanPri]      = {DNX_FIELD_QUAL_VLAN_EDIT_PCP_1,                },
/*iPMF3*/    [bcmFieldQualifyTranslatedOuterVlanCfi]      = {DNX_FIELD_QUAL_VLAN_EDIT_DEI_1,                },
/*iPMF3*/    [bcmFieldQualifyTranslatedInnerVlanId ]      = {DNX_FIELD_QUAL_VLAN_EDIT_VID_2,                },
/*iPMF3*/    [bcmFieldQualifyTranslatedInnerVlanPri]      = {DNX_FIELD_QUAL_VLAN_EDIT_PCP_2,                },
/*iPMF3*/    [bcmFieldQualifyTranslatedInnerVlanCfi]      = {DNX_FIELD_QUAL_VLAN_EDIT_DEI_2,                },
/*iPMF3*/    [bcmFieldQualifyVlanAction]                  = {DNX_FIELD_QUAL_VLAN_EDIT_CMD_INDEX,            },
/*iPMF3*/    [bcmFieldQualifyL2Learn]                     = {DNX_FIELD_QUAL_INGRESS_LEARN_ENABLE,           },
/*iPMF3*/    [bcmFieldQualifyMplsForwardingLabelAction]   = {DNX_FIELD_QUAL_EEI,                            },
/*iPMF3*/    [bcmFieldQualifyTrillEgressRbridge]          = {DNX_FIELD_QUAL_EEI, BCM_TO_DNX_ADDITIONAL_OBJ  },
/*iPMF3*/    [bcmFieldQualifyISid]                        = {DNX_FIELD_QUAL_EEI, BCM_TO_DNX_ADDITIONAL_OBJ  },
/*iPMF3*/    [bcmFieldQualifyVrf]                         = {DNX_FIELD_QUAL_FWD_DOMAIN,                      },
/*iPMF3*/    [bcmFieldQualifyVpn]                         = {DNX_FIELD_QUAL_FWD_DOMAIN,BCM_TO_DNX_ADDITIONAL_OBJ  },
/*iPMF3*/    [bcmFieldQualifyContainer]                   = {DNX_FIELD_QUAL_GENERAL_DATA_PMF_CONTAINER      },
/*iPMF3*/    [bcmFieldQualifyIPTProfile]                  = {DNX_FIELD_QUAL_END_OF_PACKET_EDITING,          },
/*iPMF3*/    [bcmFieldQualifyRxTrapCode]                  = {DNX_FIELD_QUAL_FWD_ACTION_CPU_TRAP_CODE,       },
/*iPMF3*/    [bcmFieldQualifyRxTrapData]                  = {DNX_FIELD_QUAL_FWD_ACTION_CPU_TRAP_QUAL,       },
/*iPMF3*/    [bcmFieldQualifyUDHData0]                    = {DNX_FIELD_QUAL_USER_HEADER_1,                  },
/*iPMF3*/    [bcmFieldQualifyUDHData1]                    = {DNX_FIELD_QUAL_USER_HEADER_2,                  },
/*iPMF3*/    [bcmFieldQualifyUDHData2]                    = {DNX_FIELD_QUAL_USER_HEADER_3,                  },
/*iPMF3*/    [bcmFieldQualifyUDHData3]                    = {DNX_FIELD_QUAL_USER_HEADER_4,                  },
/*iPMF3*/    [bcmFieldQualifyUDHBase0]                    = {DNX_FIELD_QUAL_USER_HEADER_1_TYPE,             },
/*iPMF3*/    [bcmFieldQualifyUDHBase1]                    = {DNX_FIELD_QUAL_USER_HEADER_2_TYPE,             },
/*iPMF3*/    [bcmFieldQualifyUDHBase2]                    = {DNX_FIELD_QUAL_USER_HEADER_3_TYPE,             },
/*iPMF3*/    [bcmFieldQualifyUDHBase3]                    = {DNX_FIELD_QUAL_USER_HEADER_4_TYPE,             },
/*iPMF3*/    [bcmFieldQualifyUDHData0Ext]                 = {DNX_FIELD_QUAL_USER_HEADER_1_EXT,              },
/*iPMF3*/    [bcmFieldQualifyUDHData1Ext]                 = {DNX_FIELD_QUAL_USER_HEADER_2_EXT,              },
/*iPMF3*/    [bcmFieldQualifyRxTrapStrength]              = {DNX_FIELD_QUAL_FWD_ACTION_STRENGTH             },
/*iPMF3*/    [bcmFieldQualifyColorRaw]                    = {DNX_FIELD_QUAL_FWD_ACTION_DP,               },
/*iPMF3*/    [bcmFieldQualifyColor]                       = {DNX_FIELD_QUAL_FWD_ACTION_DP, BCM_TO_DNX_ADDITIONAL_OBJ , dnx_field_convert_color },
/*iPMF3*/    [bcmFieldQualifyIntPriority]                 = {DNX_FIELD_QUAL_FWD_ACTION_TC,                  },
/*iPMF3*/    [bcmFieldQualifyStatSamplingCode]            = {DNX_FIELD_QUAL_STATISTICAL_SAMPLING_CODE,      },
/*iPMF3*/    [bcmFieldQualifyStatSamplingQualifier]       = {DNX_FIELD_QUAL_STATISTICAL_SAMPLING_QUALIFIER, },
/*iPMF3*/    [bcmFieldQualifyRpfEcmpMode]                 = {DNX_FIELD_QUAL_RPF_ECMP_MODE, },
/*iPMF3*/    [bcmFieldQualifyInterfaceClassL2]            = {DNX_FIELD_QUAL_PMF_ETH_RIF_PROFILE, },
/*iPMF3*/    [bcmFieldQualifyIncomingIpIfClass]           = {DNX_FIELD_QUAL_PMF_ETH_RIF_PROFILE,BCM_TO_DNX_ADDITIONAL_OBJ },
/*iPMF3*/    [bcmFieldQualifyStatOamLMRaw]                = {DNX_FIELD_QUAL_STAT_OBJ_LM_READ_INDEX, },
/*iPMF3*/    [bcmFieldQualifyStatOamLM]                   = {DNX_FIELD_QUAL_STAT_OBJ_LM_READ_INDEX ,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_lm_index},
/*iPMF3*/    [bcmFieldQualifyForwardingLayerIndex]        = {DNX_FIELD_QUAL_FWD_LAYER_INDEX,                },
/*iPMF3*/    [bcmFieldQualifyPortClassPacketProcessing]   = {DNX_FIELD_QUAL_PP_PORT_PMF_PROFILE,            },
/*iPMF3*/    [bcmFieldQualifyPortClassTrafficManagement]  = {DNX_FIELD_QUAL_TM_PORT_PMF_PROFILE,            },
/*iPMF3*/    [bcmFieldQualifyPortClassPacketProcessingGeneralData] = {DNX_FIELD_QUAL_PP_PORT_PMF_GENERAL_DATA, },
/*iPMF3*/    [bcmFieldQualifyFlowId]                      = {DNX_FIELD_QUAL_LATENCY_FLOW_ID,                },
/*iPMF3*/    [bcmFieldQualifyBierStringOffset]            = {DNX_FIELD_QUAL_BIER_STR_OFFSET,                },
/*iPMF3*/    [bcmFieldQualifyBierStringSize]              = {DNX_FIELD_QUAL_BIER_STR_SIZE,                  },
/*iPMF3*/    [bcmFieldQualifyPacketIsBier]                = {DNX_FIELD_QUAL_PACKET_IS_BIER,                 },
/*iPMF3*/    [bcmFieldQualifyForwardingAdditionalInfo]    = {DNX_FIELD_QUAL_FWD_LAYER_ADDITIONAL_INFO,      },
/*iPMF3*/    [bcmFieldQualifyStatMetaData]                = {DNX_FIELD_QUAL_STATISTICS_META_DATA,   },
/*iPMF3*/    [bcmFieldQualifyNetworkQos]                  = {DNX_FIELD_QUAL_NWK_QOS, },
/*iPMF3*/    [bcmFieldQualifyMirrorCode]                   = {DNX_FIELD_QUAL_MIRROR_CODE,},
/*iPMF3*/    [bcmFieldQualifyMirrorData]                   = {DNX_FIELD_QUAL_MIRROR_QUALIFIER,},
/*iPMF3*/    [bcmFieldQualifyLearnData]                   = {DNX_FIELD_QUAL_LEARN_DATA,},
/*iPMF3*/    [bcmFieldQualifyLearnSrcMac]                 = {DNX_FIELD_QUAL_LEARN_SRC_MAC,},
/*iPMF3*/    [bcmFieldQualifyLearnVsi]                    = {DNX_FIELD_QUAL_LEARN_VSI,},
/*iPMF3*/    [bcmFieldQualifyLearnVlan]                   = {DNX_FIELD_QUAL_LEARN_VLAN,},
/*iPMF3*/    [bcmFieldQualifyLearnStationMove]            = {DNX_FIELD_QUAL_LEARN_STATION_MOVE,},
/*iPMF3*/    [bcmFieldQualifyLearnMatch]                  = {DNX_FIELD_QUAL_LEARN_MATCH,},
/*iPMF3*/    [bcmFieldQualifyLearnFound]                  = {DNX_FIELD_QUAL_LEARN_FOUND,},
/*iPMF3*/    [bcmFieldQualifyLearnExpectedWon]            = {DNX_FIELD_QUAL_LEARN_EXPECTED_WON,},
/*iPMF3*/    [bcmFieldQualifyVrfValue]                    = {DNX_FIELD_QUAL_VRF_VALUE,},
/*iPMF3*/    [bcmFieldQualifyEcmpGroup]                   = {DNX_FIELD_QUAL_RPF_ECMP_GROUP,},
/*iPMF3*/    [bcmFieldQualifyEcnValue]                    = {DNX_FIELD_QUAL_CONGESTION_INFO,},
/*iPMF3*/    [bcmFieldQualifyFecStatId0]                  = {DNX_FIELD_QUAL_FER_STATISTICS_OBJ_ID_0,},
/*iPMF3*/    [bcmFieldQualifyFecStatId1]                  = {DNX_FIELD_QUAL_FER_STATISTICS_OBJ_ID_1,},
/*iPMF3*/    [bcmFieldQualifyFecStatId2]                  = {DNX_FIELD_QUAL_FER_STATISTICS_OBJ_ID_2,},

};

static const dnx_field_qual_map_t dnx_epmf_meta_qual_map[bcmFieldQualifyCount] = {
/*ePMF*/    [bcmFieldQualifyFhei]                        = {DNX_FIELD_QUAL_FHEI_EXT,                 },
/*ePMF*/    [bcmFieldQualifyFheiSize]                    = {DNX_FIELD_QUAL_PPH_FHEI_SIZE,            },
/*ePMF*/    [bcmFieldQualifyRepCopy]                     = {DNX_FIELD_QUAL_FTMH_TM_ACTION_TYPE, 0, dnx_field_convert_rep_copy_type},
/*ePMF*/    [bcmFieldQualifySrcPortRaw]                  = {DNX_FIELD_QUAL_FTMH_SRC_SYS_PORT, },
/*ePMF*/    [bcmFieldQualifySrcPort]                     = {DNX_FIELD_QUAL_FTMH_SRC_SYS_PORT, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_sys_port_gport_to_port},
/*ePMF*/    [bcmFieldQualifySrcModPortGport]             = {DNX_FIELD_QUAL_FTMH_SRC_SYS_PORT,   BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_sys_port_gport_to_port},
/*ePMF*/    [bcmFieldQualifyDstPortRaw]                  = {DNX_FIELD_QUAL_DST_SYS_PORT, },
/*ePMF*/    [bcmFieldQualifyDstL3Egress]                 = {DNX_FIELD_QUAL_DST_SYS_PORT, BCM_TO_DNX_ADDITIONAL_OBJ, },
/*ePMF*/    [bcmFieldQualifyDstPort]                     = {DNX_FIELD_QUAL_DST_SYS_PORT,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_sys_port_gport_to_port},
/*ePMF*/    [bcmFieldQualifyDstMulticastGroup]           = {DNX_FIELD_QUAL_DST_SYS_PORT,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_sys_port_gport_to_port },
/*ePMF*/    [bcmFieldQualifyDstClassField]               = {DNX_FIELD_QUAL_PPH_VALUE1,               },
/*ePMF*/    [bcmFieldQualifySrcClassField]               = {DNX_FIELD_QUAL_PPH_VALUE2,               },
/*ePMF*/    [bcmFieldQualifyEcnValue]                    = {DNX_FIELD_QUAL_FTMH_CNI,                 },
/*ePMF*/    [bcmFieldQualifyStackingRoute]               = {DNX_FIELD_QUAL_STACKING_EXT,  },
/*ePMF*/    /* In order for Application Specific Extension to be OAMTS first bit should be 0 */
/*ePMF*/    [bcmFieldQualifyOamTsSystemHeader]           = {DNX_FIELD_QUAL_APPLICATION_SPECIFIC_EXT, },
/*ePMF*/    [bcmFieldQualifyInVPort0Raw]                 = {DNX_FIELD_QUAL_GLOB_IN_LIF_0, },
/*ePMF*/    [bcmFieldQualifyOutVPort0Raw]                = {DNX_FIELD_QUAL_GLOB_OUT_LIF_0, },
/*ePMF*/    [bcmFieldQualifyOutVPort1Raw]                = {DNX_FIELD_QUAL_GLOB_OUT_LIF_1, },
/*ePMF*/    [bcmFieldQualifyOutVPort2Raw]                = {DNX_FIELD_QUAL_GLOB_OUT_LIF_2, },
/*ePMF*/    [bcmFieldQualifyOutVPort3Raw]                = {DNX_FIELD_QUAL_GLOB_OUT_LIF_3, },
/*ePMF*/    [bcmFieldQualifyInVPort0]                    = {DNX_FIELD_QUAL_GLOB_IN_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_in_lif},
/*ePMF*/    [bcmFieldQualifyOutVPort0]                   = {DNX_FIELD_QUAL_GLOB_OUT_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*ePMF*/    [bcmFieldQualifyOutVPort1]                   = {DNX_FIELD_QUAL_GLOB_OUT_LIF_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*ePMF*/    [bcmFieldQualifyOutVPort2]                   = {DNX_FIELD_QUAL_GLOB_OUT_LIF_2, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*ePMF*/    [bcmFieldQualifyOutVPort3]                   = {DNX_FIELD_QUAL_GLOB_OUT_LIF_3, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*ePMF*/    [bcmFieldQualifyInInterface]                 = {DNX_FIELD_QUAL_GLOB_IN_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*ePMF*/    [bcmFieldQualifyOutInterface]                = {DNX_FIELD_QUAL_GLOB_OUT_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*ePMF*/    [bcmFieldQualifyOutPortRaw]                  = {DNX_FIELD_QUAL_OUT_PP_PORT, },
/*ePMF*/    [bcmFieldQualifyOutPort]                     = {DNX_FIELD_QUAL_OUT_PP_PORT, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_port_without_core},
/*ePMF*/    [bcmFieldQualifyTrunkHashResult]             = {DNX_FIELD_QUAL_LB_KEY,                   },
/*ePMF*/    [bcmFieldQualifyNetworkLoadBalanceKey]       = {DNX_FIELD_QUAL_NWK_KEY,                  },
/*ePMF*/    [bcmFieldQualifyInVportClass0]               = {DNX_FIELD_QUAL_IN_LIF_PROFILE_0,         },
/*ePMF*/    [bcmFieldQualifyVrf]                         = {DNX_FIELD_QUAL_PPH_FWD_DOMAIN, },
/*ePMF*/    [bcmFieldQualifyVpn]                         = {DNX_FIELD_QUAL_PPH_FWD_DOMAIN,BCM_TO_DNX_ADDITIONAL_OBJ },
/*ePMF*/    [bcmFieldQualifyIPTProfile]                  = {DNX_FIELD_QUAL_PPH_END_OF_PACKET_EDITING,},
/*ePMF*/    [bcmFieldQualifyL4PortRangeCheck]            = {DNX_FIELD_QUAL_L4_PORT_IN_RANGE          },
/*ePMF*/    [bcmFieldQualifyGeneratedTtl]                = {DNX_FIELD_QUAL_PPH_TTL,                  },
/*ePMF*/    [bcmFieldQualifyColorRaw]                    = {DNX_FIELD_QUAL_FTMH_DP, },
/*ePMF*/    [bcmFieldQualifyColor]                       = {DNX_FIELD_QUAL_FTMH_DP, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_color },
/*ePMF*/    [bcmFieldQualifyIntPriority]                 = {DNX_FIELD_QUAL_FTMH_TC,                  },
/*ePMF*/    [bcmFieldQualifyRxSnoopStrength]             = {DNX_FIELD_QUAL_SNOOP_STRENGTH,           },
/*ePMF*/    [bcmFieldQualifyUDHData0]                    = {DNX_FIELD_QUAL_USER_HEADER_1,            },
/*ePMF*/    [bcmFieldQualifyUDHData1]                    = {DNX_FIELD_QUAL_USER_HEADER_2,            },
/*ePMF*/    [bcmFieldQualifyUDHData2]                    = {DNX_FIELD_QUAL_USER_HEADER_3,            },
/*ePMF*/    [bcmFieldQualifyUDHData3]                    = {DNX_FIELD_QUAL_USER_HEADER_4,            },
/*ePMF*/    [bcmFieldQualifyUDHBase0]                    = {DNX_FIELD_QUAL_USER_HEADER_1_TYPE,       },
/*ePMF*/    [bcmFieldQualifyUDHBase1]                    = {DNX_FIELD_QUAL_USER_HEADER_2_TYPE,       },
/*ePMF*/    [bcmFieldQualifyUDHBase2]                    = {DNX_FIELD_QUAL_USER_HEADER_3_TYPE,       },
/*ePMF*/    [bcmFieldQualifyUDHBase3]                    = {DNX_FIELD_QUAL_USER_HEADER_4_TYPE,       },
/*ePMF*/    [bcmFieldQualifyUDHData0Ext]                 = {DNX_FIELD_QUAL_USER_HEADER_1_EXT,        },
/*ePMF*/    [bcmFieldQualifyUDHData1Ext]                 = {DNX_FIELD_QUAL_USER_HEADER_2_EXT,        },
/*ePMF*/    [bcmFieldQualifyRxTrapStrength]              = {DNX_FIELD_QUAL_FWD_ACTION_STRENGTH,      },
/*ePMF*/    [bcmFieldQualifyRxSnoopCode]                 = {DNX_FIELD_QUAL_SNOOP_ACTION_PROFILE_INDEX,},
/*ePMF*/    [bcmFieldQualifyOutVportClass]               = {DNX_FIELD_QUAL_OUT_LIF_PROFILE,},
/*ePMF*/    [bcmFieldQualifyOutVportClass0]              = {DNX_FIELD_QUAL_OUT_LIF_PROFILE, BCM_TO_DNX_ADDITIONAL_OBJ},
/*ePMF*/    [bcmFieldQualifyOutVportClass1]              = {DNX_FIELD_QUAL_OUT_LIF_PROFILE_1,},
/*ePMF*/    [bcmFieldQualifyOutVportClass2]              = {DNX_FIELD_QUAL_OUT_LIF_PROFILE_2,},
/*ePMF*/    [bcmFieldQualifyOutVportClass3]              = {DNX_FIELD_QUAL_OUT_LIF_PROFILE_3,},
/*ePMF*/    [bcmFieldQualifyInterfaceClassL2]            = {DNX_FIELD_QUAL_PMF_ETH_RIF_PROFILE       },
/*ePMF*/    [bcmFieldQualifyPortClassPacketProcessing]   = {DNX_FIELD_QUAL_PP_PORT_PMF_PROFILE,      },
/*ePMF*/    [bcmFieldQualifyPortClassTrafficManagement]  = {DNX_FIELD_QUAL_TM_PORT_PMF_PROFILE,      },
/*ePMF*/    [bcmFieldQualifyOutPortTrafficManagement]    = {DNX_FIELD_QUAL_PP_DSP,                   },
/*ePMF*/    [bcmFieldQualifyForwardingAdditionalInfo]    = {DNX_FIELD_QUAL_PPH_FWD_LAYER_ADDITIONAL_INFO, },
/*ePMF*/    [bcmFieldQualifyPphPresent]                  = {DNX_FIELD_QUAL_FTMH_PPH_PRESENT,         },
/*ePMF*/    [bcmFieldQualifyPacketProcessingInVportClass] = {DNX_FIELD_QUAL_PPH_IN_LIF_PROFILE,         },
/*ePMF*/    [bcmFieldQualifyRxTrapCode]                  = {DNX_FIELD_QUAL_FWD_ACTION_PROFILE_INDEX, },
/*ePMF*/    [bcmFieldQualifyAceEntryId]                  = {DNX_FIELD_QUAL_CUD_OUTLIF_OR_MCDB_PTR, },
/*ePMF*/    [bcmFieldQualifyNetworkQos]                  = {DNX_FIELD_QUAL_PPH_NWK_QOS, },
/*ePMF*/    [bcmFieldQualifyDstSysPortExt]               = {DNX_FIELD_QUAL_TM_DESTINATION_EXT, },
/*ePMF*/    [bcmFieldQualifyVrfValue]                    = {DNX_FIELD_QUAL_PPH_VRF_VALUE},
/*ePMF*/    [bcmFieldQualifyDstSysPortExtPresent]        = {DNX_FIELD_QUAL_FTMH_TM_DESTINATION_EXT_PRESENT, },
/*ePMF*/    [bcmFieldQualifyLearnData]                   = {DNX_FIELD_QUAL_LEARN_EXT_DATA,},
/*ePMF*/    [bcmFieldQualifyLearnSrcMac]                 = {DNX_FIELD_QUAL_LEARN_EXT_SRC_MAC,},
/*ePMF*/    [bcmFieldQualifyLearnVsi]                    = {DNX_FIELD_QUAL_LEARN_EXT_VSI,},
/*ePMF*/    [bcmFieldQualifyLearnVlan]                   = {DNX_FIELD_QUAL_LEARN_EXT_VLAN,},
/*ePMF*/    [bcmFieldQualifyLearnExtensionPresent]       = {DNX_FIELD_QUAL_PPH_LEARN_EXT_PRESENT,},
/*ePMF*/    [bcmFieldQualifyMcastPkt]                    = {DNX_FIELD_QUAL_FTMH_TM_ACTION_IS_MC,},
/*ePMF*/    [bcmFieldQualifyFtmhAsePresent]              = {DNX_FIELD_QUAL_FTMH_APPLICATION_SPECIFIC_EXT_PRESENT,},
/*ePMF*/    [bcmFieldQualifyIpMcFallbacktoBridge]        = {DNX_FIELD_QUAL_IP_MC_SHOULD_BE_BRIDGED,},
/*ePMF*/    [bcmFieldQualifyForwardingLayerIndex]        = {DNX_FIELD_QUAL_PPH_FWD_LAYER_INDEX,},
/*ePMF*/    [bcmFieldQualifyVisibility]                  = {DNX_FIELD_QUAL_FTMH_VISIBILITY,},
};

static const dnx_field_qual_map_t dnx_l4ops_meta_qual_map[bcmFieldQualifyCount] = {
    [bcmFieldQualifyVrf]                      = {DNX_FIELD_QUAL_FWD_DOMAIN, },
    [bcmFieldQualifyInVPort0]                 = {DNX_FIELD_QUAL_GLOB_IN_LIF_0, },
    [bcmFieldQualifyInVPort1]                 = {DNX_FIELD_QUAL_GLOB_IN_LIF_1, },
    [bcmFieldQualifyOutVPort0]                = {DNX_FIELD_QUAL_GLOB_OUT_LIF_0, },
    [bcmFieldQualifyOutVPort1]                = {DNX_FIELD_QUAL_GLOB_OUT_LIF_1, },
};

/*
 * End of BCM to DNX set maps per stage
 * }
 */
/*
 * DNX QUAL data structures array
 * {
 */

const dnx_field_header_qual_info_t dnx_header_qual_info[DNX_FIELD_HEADER_QUAL_NOF] = {
        /*  DNX Qualifier ID                           Name                  DBAL Field ID,   Size, Offset, Signal info, Valid, BCM Qual */
           [DNX_FIELD_HEADER_QUAL_MAC_DST]          = {"ETH0.DA",            DBAL_FIELD_MAC_DST, 48, 0},
           [DNX_FIELD_HEADER_QUAL_MAC_SRC]          = {"ETH0.SA",            DBAL_FIELD_MAC_SRC, 48, 48},
           [DNX_FIELD_HEADER_QUAL_ETHERTYPE]        = {"ETH0.Type",          DBAL_FIELD_ETHERTYPE, 16, 96},
           /*
            * VLAN Header Qualifiers
            */
           [DNX_FIELD_HEADER_QUAL_VLAN_TPID]        = {"VLAN.TPID",          DBAL_FIELD_VLAN_TPID, 16, 0},
           [DNX_FIELD_HEADER_QUAL_VLAN_ID]          = {"VLAN.VID",           DBAL_FIELD_VLAN_ID, 12, 20},
           [DNX_FIELD_HEADER_QUAL_VLAN_PRI]         = {"VLAN.PCP",           DBAL_FIELD_VLAN_PRI, 3, 16},
           [DNX_FIELD_HEADER_QUAL_VLAN_CFI]         = {"VLAN.DEI",           DBAL_FIELD_VLAN_CFI, 1, 19},
           [DNX_FIELD_HEADER_QUAL_VLAN_TCI]         = {"VLAN.TCI",           DBAL_FIELD_VLAN_TCI, 16, 16},
           [DNX_FIELD_HEADER_QUAL_VLAN_PRI_CFI]     = {"VLAN.PRI_CFI",       DBAL_FIELD_VLAN_PRI_CFI, 4, 20},
           /*
            * IPv4 Header Qualifiers
            */
           [DNX_FIELD_HEADER_QUAL_IPV4_TOS]         = {"IPv4.TOS",           DBAL_FIELD_IPV4_TOS, 8, 8},
           [DNX_FIELD_HEADER_QUAL_IPV4_DSCP]        = {"IPv4.TOS.DSCP",      DBAL_FIELD_IPV4_DSCP, 6, 8},
           [DNX_FIELD_HEADER_QUAL_IPV4_ECN]         = {"IPv4.TOS.ECN",       DBAL_FIELD_IPV4_ECN, 2, 14},
           [DNX_FIELD_HEADER_QUAL_IPV4_FLAGS]       = {"IPv4.Flags",         DBAL_FIELD_IPV4_FLAGS, 3, 48},
           [DNX_FIELD_HEADER_QUAL_IPV4_TTL]         = {"IPv4.TTL",           DBAL_FIELD_IPV4_TTL, 8, 64},
           [DNX_FIELD_HEADER_QUAL_IPV4_PROTOCOL]    = {"IPv4.Protocol",      DBAL_FIELD_IPV4_PROTOCOL, 8, 72},
           [DNX_FIELD_HEADER_QUAL_IPV4_SRC]         = {"IPv4.SIP",           DBAL_FIELD_IPV4_SIP, 32, 96},
           [DNX_FIELD_HEADER_QUAL_IPV4_DST]         = {"IPv4.DIP",           DBAL_FIELD_IPV4_DIP, 32, 128},
           /*
            * IPv6 Header Qualifiers
            */
           [DNX_FIELD_HEADER_QUAL_IPV6_SIP]         = {"IPv6.SIP",           DBAL_FIELD_IPV6_SIP, 128, 64},
           [DNX_FIELD_HEADER_QUAL_IPV6_DIP]         = {"IPv6.DIP",           DBAL_FIELD_IPV6_DIP, 128, 192},
           [DNX_FIELD_HEADER_QUAL_IPV6_SIP_LOW]     = {"IPv6.SIP.Low",       DBAL_FIELD_IPV6_SIP_LOW, 64, 128},
           [DNX_FIELD_HEADER_QUAL_IPV6_SIP_HIGH]    = {"IPv6.SIP.High",      DBAL_FIELD_IPV6_SIP_HIGH, 64, 64},
           [DNX_FIELD_HEADER_QUAL_IPV6_DIP_LOW]     = {"IPv6.DIP.Low",       DBAL_FIELD_IPV6_DIP_LOW, 64, 256},
           [DNX_FIELD_HEADER_QUAL_IPV6_DIP_HIGH]    = {"IPv6.DIP.High",      DBAL_FIELD_IPV6_DIP_HIGH, 64, 192},
           [DNX_FIELD_HEADER_QUAL_IPV6_TC]          = {"IPv6.Traffic_Class", DBAL_FIELD_IPV6_TC, 8, 4},
           [DNX_FIELD_HEADER_QUAL_IPV6_FLOW_LABEL]  = {"IPv6.Flow_Label",    DBAL_FIELD_IPV6_FLOW_LABEL, 20, 12},
           [DNX_FIELD_HEADER_QUAL_IPV6_NEXT_HEADER] = {"IPv6.Next_Header",   DBAL_FIELD_IPV6_NEXT_HEADER, 8, 48},
           [DNX_FIELD_HEADER_QUAL_IPV6_HOP_LIMIT]   = {"IPv6.Hop_Limit",     DBAL_FIELD_IPV6_HOP_LIMIT, 8, 56},
           [DNX_FIELD_HEADER_QUAL_IPV6_1ST_EXTENSION_NEXT_HEADER]   = {"IPv6_With_Ext.Ext.Next_Header", DBAL_FIELD_IPV6_1ST_EXTENSION_NEXT_HEADER, 8, 320},
           /*
            * TCP/UDP Common Fields
            */
           [DNX_FIELD_HEADER_QUAL_L4_SRC_PORT]      = {"UDP.Src_Port",       DBAL_FIELD_L4_SRC_PORT, 16, 0},
           [DNX_FIELD_HEADER_QUAL_L4_DST_PORT]      = {"UDP.Dst_Port",       DBAL_FIELD_L4_DST_PORT, 16, 16},
           /*
            * MPLS Header Qualifiers
            */
           [DNX_FIELD_HEADER_QUAL_MPLS_LABEL]       = {"MPLS",               DBAL_FIELD_MPLS_HEADER, 32, 0},
           [DNX_FIELD_HEADER_QUAL_MPLS_LABEL_ID]    = {"MPLS.Label",         DBAL_FIELD_MPLS_LABEL, 20, 0},
           [DNX_FIELD_HEADER_QUAL_MPLS_TC]          = {"MPLS.EXP",           DBAL_FIELD_MPLS_TC, 3, 20},
           [DNX_FIELD_HEADER_QUAL_MPLS_BOS]         = {"MPLS.BOS",           DBAL_FIELD_MPLS_BOS, 1, 23},
           [DNX_FIELD_HEADER_QUAL_MPLS_TTL]         = {"MPLS.TTL",           DBAL_FIELD_MPLS_TTL, 8, 24},
           /*
            * ARP Header Qualifiers
            */
           [DNX_FIELD_HEADER_QUAL_ARP_OPCODE]       = {"ARP.Opcode",         DBAL_FIELD_ARP_OPCODE, 16, 48},
           [DNX_FIELD_HEADER_QUAL_ARP_SENDER_IP]    = {"ARP.Sender_IP",      DBAL_FIELD_ARP_SENDER_IP, 32, 112},
           [DNX_FIELD_HEADER_QUAL_ARP_TARGET_IP]    = {"ARP.Target_IP",      DBAL_FIELD_ARP_TARGET_IP, 32, 192},
           /*
            * TCP Requested Fields
            */
           [DNX_FIELD_HEADER_QUAL_TCP_CTL]          = {"TCP.Control.Base",         DBAL_FIELD_TCP_CTL, 6, 106},
           /*
            * RCH Header Qualifiers
            */
           [DNX_FIELD_HEADER_QUAL_RCH_TIME_STAMP]    = {"RCH.TS",            DBAL_FIELD_RCH_TIME_STAMP , 1, 4},
           [DNX_FIELD_HEADER_QUAL_RCH_FORWARDING_ADDITIONAL_INFO]    = {"RCH.FAI",           DBAL_FIELD_RCH_FORWARDING_ADDITIONAL_INFO , 4, 132},
           [DNX_FIELD_HEADER_QUAL_RCH_TYPE]          = {"RCH.RCH_Type",      DBAL_FIELD_RCH_TYPE , 4, 0},
           [DNX_FIELD_HEADER_QUAL_RCH_VISIBILITY]    = {"RCH.Vis",           DBAL_FIELD_RCH_VISIBILITY , 1, 32},

};

const dnx_field_sw_qual_info_t dnx_sw_qual_info[DNX_FIELD_SW_QUAL_NOF] = {
 /* DNX Qualifier ID                           Size, Field ID           Offset, Index, FFC Type*/
 /* Pure SW qualifier - currently only one */
    [DNX_FIELD_SW_QUAL_ALL_ZERO]    = {DBAL_FIELD_ALL_ZERO, 32}
};

/*
 * End of DNX Qualifier data
 * }
 */

const dnx_field_qual_input_type_info_t dnx_input_type_info[DNX_FIELD_INPUT_TYPE_NOF] = {
    [DNX_FIELD_INPUT_TYPE_LAYER_FWD]               = {TRUE, 0xd /* 1101 */},
    [DNX_FIELD_INPUT_TYPE_LAYER_ABSOLUTE]          = {TRUE, 0xd /* 1101 */},
    [DNX_FIELD_INPUT_TYPE_META_DATA]               = {TRUE, 0xb /* 1011 */},
    [DNX_FIELD_INPUT_TYPE_CONST]                   = {TRUE, 0xb /* 1011 */},
    [DNX_FIELD_INPUT_TYPE_LAYER_RECORDS_FWD]       = {TRUE, 0xf /* 1111 */},
    [DNX_FIELD_INPUT_TYPE_LAYER_RECORDS_ABSOLUTE]  = {TRUE, 0xf /* 1111 */},
    [DNX_FIELD_INPUT_TYPE_EXTERNAL]                = {TRUE, 0xb /* 1011 */},
};
/*
 * End of qualifier related data
 * }
 */

/*
 * Action related data below
 * {
 */


const char *bcm_action_description[bcmFieldActionCount] = {
    [bcmFieldActionSnoop]                  = "Snoop matched packets, input can be either a snoop command: value[0] = Mirror Gport, value[1]=snoop qualifier, value[2]=snoop strength OR: snoop code: value[0] = Trap Gport, value[1]=snoop qualifier, at egress stage refers only to the snoop ID (strength is not relevant, and can be changed using bcmFieldActionSnoopStrength action)",
    [bcmFieldActionSnoopStrength]          = "updates the snoop strength",
    [bcmFieldActionPphPresentSet]          = "Create Packet Processing and Time Stamp headers if injected",
    [bcmFieldActionPrioIntNew]             = "TC update",
    [bcmFieldActionDropPrecedence]         = "Set Packet's Drop Precedence, the values are BCM_FIELD_COLOR_XXX",
    [bcmFieldActionForward]                = "Forward Destination Raw value, setting to 1's will drop the packet",
    [bcmFieldActionRedirectMcast]          = "Redirect to Multicast Group Id.",
    [bcmFieldActionRedirect     ]          = "Redirect packet to to destination. value[0]=GPORT value[1]=Qualifier.",
    [bcmFieldActionFabricHeaderSet]        = "Change System Header Profile, bcm_field_system_header_profile_t",
    [bcmFieldActionUDHData0]               = "Set the Payload for User Defined Header 0",
    [bcmFieldActionUDHData1]               = "Set the Payload for User Defined Header 1",
    [bcmFieldActionUDHData2]               = "Set the Payload for User Defined Header 2",
    [bcmFieldActionUDHData3]               = "Set the Payload for User Defined Header 3",
    [bcmFieldActionUDHBase]                = "Set the Base for All  User Defined Header 0-3, UDHBase0 is at LSB",
    [bcmFieldActionUDHBase0]               = "Set the Base for User Defined Header 0",
    [bcmFieldActionUDHBase1]               = "Set the Base for User Defined Header 1",
    [bcmFieldActionUDHBase2]               = "Set the Base for User Defined Header 2",
    [bcmFieldActionUDHBase3]               = "Set the Base for User Defined Header 3",
    [bcmFieldActionUDHData0Ext]            = "Set the Extension for User Defined Header 0",
    [bcmFieldActionUDHData1Ext]            = "Set the Extension for User Defined Header 1",
    [bcmFieldActionVlanActionSetNew]       = "Modify the VLAN Action Set Id ",
    [bcmFieldActionOuterVlanPrioNew]       = "Replace outer VLAN tag priority",
    [bcmFieldActionOuterVlanNew]           = "Replace outer VLAN Id",
    [bcmFieldActionInnerVlanPrioNew]       = "Replace inner VLAN tag priority",
    [bcmFieldActionInnerVlanNew]           = "Replace inner VLAN Id",
    [bcmFieldActionUsePolicerResult]       = "Specify/override where policer result will be used for matched packets",
    [bcmFieldActionSystemHeaderSet]        = "Modify EEI",
    [bcmFieldActionVSQ]                    = "Assign matching packets to specified VSQ",
    [bcmFieldActionAdmitProfile]           = "Admit Profile",
    [bcmFieldActionIEEE1588]               = "Setting various parameters for 1588 frames. Bits(0:7): header_offset. Bit(8): encapsulation. Bits(9:10) command. Bit(11): compensate_time_stamp. Bit(12): packet_is_ieee1588.",
    [bcmFieldActionSrcGportNew]            = "Set the Source-Port ",
    [bcmFieldActionTtlSet]                 = "new TTL",
    [bcmFieldActionLatencyFlowId]          = "change the latency flow-Id. value[0] valid. value[1]: latency_flow_id. value[2]: latency_flow_profile.",
    [bcmFieldActionIngressGportSet]        = "Set a new ingress Global Lif encoded, Values should be Encoded as GPORT",
    [bcmFieldActionInterfaceClassVPort]    = "set Inlif profile",
    [bcmFieldActionMirrorIngress]          = "set mirror, value should be encoded as  GPORT Type Mirror for mirror command",
    [bcmFieldActionStackingRouteNew]       = "Replace the value of the stacking route",
    [bcmFieldActionOam]                    = "Changes 4 OAM signals. value[0]: OAM-Stamp-Offset. value[1]: OAM-offset. value[2]: OAM-Sub-Type. value[3]: OAM-Up-Mep.",
    [bcmFieldActionPphSnoopCode]           = "Set the PPH Snoop code value (Reserved Bits)",
    [bcmFieldActionTrap]                   = "Set Trap code, use TRAP GPORT type value[0]=TRAP_GPORT value[1]=Trap Qualifier. at egress stage refers only to the TRAP ID (strength is not relevant, and can be changed using bcmFieldActionTrapStrength action)",
    [bcmFieldActionTrapStrength]           = "Updates the Trap Strength. Use TRAP Gport ",
    [bcmFieldActionOutVport0]              = "change outlif 0, value should be encoded as a GPORT with LIF subtype",
    [bcmFieldActionOutVport1]              = "change outlif 1, value should be encoded as a GPORT with LIF subtype",
    [bcmFieldActionOutVport2]              = "change outlif 2, value should be encoded as a GPORT with LIF subtype",
    [bcmFieldActionOutVport3]              = "change outlif 3, value should be encoded as a GPORT with LIF subtype",
    [bcmFieldActionOutInterface0]          = "change outlif 0, value should be encoded as type interface.",
    [bcmFieldActionOutInterface1]          = "change outlif 1, value should be encoded as type interface.",
    [bcmFieldActionOutInterface2]          = "change outlif 2, value should be encoded as type interface.",
    [bcmFieldActionOutInterface3]          = "change outlif 3, value should be encoded as type interface.",
    [bcmFieldActionVrfSet]                 = "Set VRF. value[0]: fwd_domain_id.",
    [bcmFieldActionVSwitchNew]             = "New VSI. value[0]: fwd_domain_id.",
    [bcmFieldActionFwdDomain]              = "New Forward Domain. value[0]: fwd_domain_id. value[1]: fwd_domain_profile.",
    [bcmFieldActionContainer]              = "This action will be used as container in IPMF2, to parse the action buffer, when performing cascading between IPMF2 and IPMF3.",
    [bcmFieldActionCbts]                   = "Changing tunnel priority for CBTS. For each hierarchy takes a mask of current 3LSB and performs bitwise OR with the value. [0:2] Hierarchy 1 TP mask [3:5] Hierarchy 1 TP value [6:8] Hierarchy 2 TP mask [9:1] Hierarchy 2 TP value [12:14] Hierarchy 3 TP mask [15:17] Hierarchy 3 TP value [18] valid bit.",
    [bcmFieldActionIPTProfile]            = "IPT Profile action (used for instrumentation)",
    [bcmFieldActionStatId0]                = "Updates statistics ID 0",
    [bcmFieldActionStatId1]                = "Updates statistics ID 1",
    [bcmFieldActionStatId2]                = "Updates statistics ID 2",
    [bcmFieldActionStatId3]                = "Updates statistics ID 3",
    [bcmFieldActionStatId4]                = "Updates statistics ID 4",
    [bcmFieldActionStatId5]                = "Updates statistics ID 5",
    [bcmFieldActionStatId6]                = "Updates statistics ID 6",
    [bcmFieldActionStatId7]                = "Updates statistics ID 7",
    [bcmFieldActionStatId8]                = "Updates statistics ID 8",
    [bcmFieldActionStatId9]                = "Updates statistics ID 9",
    [bcmFieldActionStatProfile0]           = "Updates statistics profile 0. In ePMF indicates which value to read. In iPMF1/2/3: value[0]: is_meter. value[1]: is_lm. value[2]: type. value[3]: valid.",
    [bcmFieldActionStatProfile1]           = "Updates statistics profile 1. In ePMF indicates which value to read. In iPMF1/2/3: value[0]: is_meter. value[1]: is_lm. value[2]: type. value[3]: valid.",
    [bcmFieldActionStatProfile2]           = "Updates statistics profile 2. value[0]: is_meter. value[1]: is_lm. value[2]: type. value[3]: valid.",
    [bcmFieldActionStatProfile3]           = "Updates statistics profile 3. value[0]: is_meter. value[1]: is_lm. value[2]: type. value[3]: valid.",
    [bcmFieldActionStatProfile4]           = "Updates statistics profile 4. value[0]: is_meter. value[1]: is_lm. value[2]: type. value[3]: valid.",
    [bcmFieldActionStatProfile5]           = "Updates statistics profile 5. value[0]: is_meter. value[1]: is_lm. value[2]: type. value[3]: valid.",
    [bcmFieldActionStatProfile6]           = "Updates statistics profile 6. value[0]: is_meter. value[1]: is_lm. value[2]: type. value[3]: valid.",
    [bcmFieldActionStatProfile7]           = "Updates statistics profile 7. value[0]: is_meter. value[1]: is_lm. value[2]: type. value[3]: valid.",
    [bcmFieldActionStatProfile8]           = "Updates statistics profile 8. value[0]: is_meter. value[1]: is_lm. value[2]: type. value[3]: valid.",
    [bcmFieldActionStatProfile9]           = "Updates statistics profile 9. value[0]: is_meter. value[1]: is_lm. value[2]: type. value[3]: valid.",
    [bcmFieldActionIngressTimeStampInsert] ="Insert IPIPE time stamp",
    [bcmFieldActionStatMetaData]           = "Set statistics metaData",
    [bcmFieldActionInvalidNext]            = "Invalid next Action macro Id",
    [bcmFieldActionExtStat0]               = "Update External Statistics ID 0. value[0]: object_stat_id. value[1]: opcode. value[2]: valid. ",
    [bcmFieldActionExtStat1]               = "Update External Statistics ID 1. value[0]: object_stat_id. value[1]: opcode.",
    [bcmFieldActionExtStat2]               = "Update External Statistics ID 2. value[0]: object_stat_id. value[1]: opcode.",
    [bcmFieldActionExtStat3]               = "Update External Statistics ID 3. value[0]: object_stat_id. value[1]: opcode.",
    [bcmFieldActionForwardingTypeMeterMap] = "Maps L2 forwarding type to one of the general meters",
    [bcmFieldActionStatSampling]           = "Update statistical sampling value, value encoded as Mirror Gport",
    [bcmFieldActionStatOamLM]              = "Update the counter of OAM LM, the index of the values are bcmFieldStatOamLmIndexXXX",
    [bcmFieldActionStatOamLMRaw]           = "Update the counter of OAM LM with a raw value",
    [bcmFieldActionForwardingLayerIndex]   = "Update forwarding layer index",
    [bcmFieldActionVisibilityEnable]       = "Enables visibility for current packet",
    [bcmFieldActionVisibilityClear]        = "Disables visibility for current packet",
    [bcmFieldActionInVport0]               = "Change the In Lif0, value should be encoded as a GPORT with LIF subtype",
    [bcmFieldActionInVport1]               = "Change the In Lif1, value should be encoded as a GPORT with LIF subtype",
    [bcmFieldActionInInterface0]           = "Change the In Lif0, value should be encoded as an interface",
    [bcmFieldActionInInterface1]           = "Change the In Lif1, value should be encoded as an interface",
    [bcmFieldActionSmallExemLearn]         = "Updates the Small Exact Match learn info (IPMF2 only).",
    [bcmFieldActionPacketTraceEnable]      = "Enable Trace packet",
    [bcmFieldActionEcnNew]                 = "Change metadata ECN / congestion info (including CNI)",
    [bcmFieldActionDrop]                   = "Discard packet",
    [bcmFieldActionStat0]                  = "Stat meter object. value[0]: stat_meter_obj_cmd. value[1]: stat_meter_obj_id",
    [bcmFieldActionStat1]                  = "Stat counter object. value[0]: stat_counter_obj_cmd. value[1]: stat_counter_obj_id. value[2]: valid.",
    [bcmFieldActionMirrorEgress]           = "Update the mirror profile, mirror_cmd should be encoded as MIRROR Gport",
    [bcmFieldActionVoid]                   = "Void action, adds bits to the payload buffer without automatically associating an action for them. Used for cascading, FEM, added EFES or padding. All actions on an external lookup are void.",
    [bcmFieldActionTrunkHashKeySet]        = "Set the Trunk Hash Key",
    [bcmFieldActionNetworkLoadBalanceKey]  = "Set the network load balancing Key",
    [bcmFieldActionParsingStartType]      = "Indicate the layer type that egress parser should consider",
    [bcmFieldActionParsingStartOffset]    = "Indicate from which offset egress parser should start parsing (all info before that will not be parsed).",
    [bcmFieldActionEgressForwardingIndex] = "Indicate for egress parser which layer is the Forwarding layer.",
    [bcmFieldActionIPTCommand]            = "IPT Profile command. value[0]: int_commnad. value[1]: int_profile.",
    [bcmFieldActionStartPacketStrip]      = "Strip the start of packet. value[0]: bcm_field_start_packet_strip_t value[1]: extra bytes to remove.",
    [bcmFieldActionEstimatedStartPacketStrip] = "Estimated bytes to remove at the start of packet.",
    [bcmFieldActionLearnSrcPortNew]       = "Replace the learnt packet source Port",
    [bcmFieldActionAceContextValue]       = "Updates programmable value per ACE context, bcm_field_ace_context_t. Up to four different values can be given in value[0-3], although some may be mutually exclusive",
    [bcmFieldActionQosMapIdNew]           = "Set the QoS profile ",
    [bcmFieldActionAceEntryId]            = "Pointer to the ACE entry ID",
    [bcmFieldActionOutPortTrafficManagement] = "Updates the Out-TM port",
    [bcmFieldActionOutPortPacketProcessing] = "Updates the Out-PP port",
    [bcmFieldActionPpDsp]                 = "Set PP-DSP",
    [bcmFieldActionBierStringOffset]         = "Updates Bier string offset.",
    [bcmFieldActionBierStringSize]           = "Updates Bier string size.",
    [bcmFieldActionPacketIsBier]          = "Updates is Bier packet.",
    [bcmFieldActionEventor]               = "Enable push data to eventor.",
    [bcmFieldActionForwardingAdditionalInfo]  = "Updates forwarding additional information.",
    [bcmFieldActionSystemHeaderSizeAdjust]  = "System Header Size adjust.",
    [bcmFieldActionInVportClass0]           = "Updates the profile of an in LIF encoded as Gport.",
    [bcmFieldActionInVportClass1]           = "Updates the profile of an in LIF encoded as Gport.",
    [bcmFieldActionNetworkQos]           = "Updates Network Qos value",
    [bcmFieldActionIngressDoNotLearn]             = "Disable Ingress learning",
    [bcmFieldActionEgressDoNotLearn]             = "Disable Egress learning",
    [bcmFieldActionInVport0Raw]               = "Change the In Lif0, with raw value.",
    [bcmFieldActionInVport1Raw]               = "Change the In Lif1, with raw value.",
    [bcmFieldActionOutVport0Raw]              = "Change the Out Lif 0, with raw value.",
    [bcmFieldActionOutVport1Raw]              = "Change the Out Lif 1, with raw value.",
    [bcmFieldActionOutVport2Raw]              = "Change the Out Lif 2, with raw value.",
    [bcmFieldActionOutVport3Raw]              = "Change the Out Lif 3, with raw value.",
    [bcmFieldActionAppendPointerCompensation]  = "Configures pointer to header append compensation value.",
    [bcmFieldActionIngressTimeStampInsertValid]  = "Insert ingress timestamp. Overrides the time stamp in TSH header.",
    [bcmFieldActionSnoopRaw]  = "Snoop matched packets, input should be raw value. At egress stage refers only to the snoop ID (strength is not relevant, and can be changed using bcmFieldActionSnoopStrength action)",
    [bcmFieldActionDropPrecedenceRaw]  = "Set Packet's Drop Precedence, input expects raw value.",
    [bcmFieldActionFabricHeaderSetRaw]  = "Change System Header Profile, input expects raw value.",
    [bcmFieldActionSrcGportNewRaw]  = "Set the Source-Port, input expects raw value.",
    [bcmFieldActionLatencyFlowIdRaw]  = "Change the latency flow-Id, input expects raw value.",
    [bcmFieldActionMirrorIngressRaw]  = "Set mirror in ingress, input expects raw value.",
    [bcmFieldActionOamRaw]  = "Changes 4 OAM signals (OAM-Stamp-Offset, OAM-offset, OAM-Sub-Type, OAM-Up-Mep), input expects raw value.",
    [bcmFieldActionTrapRaw]  = "Set Trap code, input should be raw value. At egress stage refers only to the TRAP ID (strength is not relevant, and can be changed using bcmFieldActionTrapStrength action).",
    [bcmFieldActionVrfSetRaw]  = "Set VRF, input expects raw value.",
    [bcmFieldActionFwdDomainRaw]     = "Set Fwd Domain, input expects raw value",
    [bcmFieldActionStatProfile0Raw]  = "Updates statistics profile 0. Input expects raw value.",
    [bcmFieldActionStatProfile1Raw]  = "Updates statistics profile 1. Input expects raw value.",
    [bcmFieldActionStatProfile2Raw]  = "Updates statistics profile 2. Input expects raw value.",
    [bcmFieldActionStatProfile3Raw]  = "Updates statistics profile 3. Input expects raw value.",
    [bcmFieldActionStatProfile4Raw]  = "Updates statistics profile 4. Input expects raw value.",
    [bcmFieldActionStatProfile5Raw]  = "Updates statistics profile 5. Input expects raw value.",
    [bcmFieldActionStatProfile6Raw]  = "Updates statistics profile 6. Input expects raw value.",
    [bcmFieldActionStatProfile7Raw]  = "Updates statistics profile 7. Input expects raw value.",
    [bcmFieldActionStatProfile8Raw]  = "Updates statistics profile 8. Input expects raw value.",
    [bcmFieldActionStatProfile9Raw]  = "Updates statistics profile 9. Input expects raw value.",
    [bcmFieldActionExtStat0Raw]  = "Update External Statistics ID 0. Input expects raw value.",
    [bcmFieldActionExtStat1Raw]  = "Update External Statistics ID 1. Input expects raw value.",
    [bcmFieldActionExtStat2Raw]  = "Update External Statistics ID 2. Input expects raw value.",
    [bcmFieldActionExtStat3Raw]  = "Update External Statistics ID 3. Input expects raw value.",
    [bcmFieldActionStatSamplingRaw]  = "Update statistical sampling value, input expects raw value.",
    [bcmFieldActionStartPacketStripRaw]  = "Strip the start of packet. Refers to bcm_field_start_packet_strip_t. Input expects raw value.",
    [bcmFieldActionParsingStartTypeRaw]  = "Indicate the layer type that egress parser should consider, input expects raw value.",
    [bcmFieldActionParsingStartOffsetRaw]  = "Indicate from which offset egress parser should start parsing (all info before that will not be parsed). Input expects raw value.",
    [bcmFieldActionIPTCommandRaw]  = "IPT Profile command. Input expects raw value.",
    [bcmFieldActionMirrorEgressRaw]  = "Update the egress mirror profile, input expects raw value.",
    [bcmFieldActionTrapStrengthRaw]  = "Updates the Trap Strength, input expects raw value.",
    [bcmFieldActionSnoopStrengthRaw]  = "Updates the Snoop Strength, input expects raw value.",
    [bcmFieldActionAceContextValueRaw]  = "Updates programmable value per ACE context, input expects raw value.",
    [bcmFieldActionStat0Raw]  = "Stat meter object. Input expects raw value.",
    [bcmFieldActionStat1Raw]  = "Stat counter object. Input expects raw value.",
    [bcmFieldActionIpMulticastCompatible]  = "Designates when a Compatible MC procedure found a match.",
    [bcmFieldActionRpfOutVport]  = "Updates the RPF OUT LIF. value[0]: route_valid, value[1]: default_route_found, value[2]: rpf_out_lif (encoded as GPORT with LIF subtype)",
    [bcmFieldActionRpfOutInterface]  = "Updates the RPF OUT LIF. value[0]: route_valid, value[1]: default_route_found, value[2]: rpf_out_lif (encoded as L3 interface)",
    [bcmFieldActionRpfOutVportRaw]  = "Updates the RPF OUT LIF. Input expects raw value.",
    [bcmFieldActionL3Switch]  = "Sets packet destination, input expects L3 interface.",
    [bcmFieldActionLearnRaw0]  = "Updates learn info 0.",
    [bcmFieldActionLearnRaw1]  = "Updates learn info 1.",
    [bcmFieldActionLearnRaw2]  = "Updates learn info 2.",
    [bcmFieldActionLearnRaw3]  = "Updates learn info 3.",
    [bcmFieldActionLearnRaw4]  = "Updates learn info 4.",
    [bcmFieldActionLearnOrTransplant]  = "Updates learn or transplant bit.",
    [bcmFieldActionLearnKey0]  = "Updates bits 31:0 of learn info key.",
    [bcmFieldActionLearnKey1]  = "Updates bits 63:32 of learn info key.",
    [bcmFieldActionLearnKey2]  = "Updates learn info key and app_db_index. value[0]: bits 79:64 of learn info ley, value[1] app_db_index.",
    [bcmFieldActionLearnKey2Raw]  = "Updates learn info key and app_db_index. Key is at the LSB.",
    [bcmFieldActionLearnPayload0]  = "Updates bits 31:0 of learn info data (payload).",
    [bcmFieldActionLearnPayload1]  = "Updates bits 63:32 of learn info data (payload).",
    [bcmFieldActionLearnEntryFormatIndex]  = "Updates entry format index in learn info.",
    [bcmFieldActionDstRpfGportNew]  = "Set the RPF Destination.",
    [bcmFieldActionDstRpfGportNewValid]  = "Set the RPF Destination Valid.",
    [bcmFieldActionDstRpfGportNewRaw]  = "Set the RPF Destination. Input expects raw value.",
    [bcmFieldActionPrtQualifier] = "Update prt qualifier",
    [bcmFieldActionDstClassField]  = "Set the pph value1. Input expects raw value.",
    [bcmFieldActionSrcClassField]  = "Set the pph value2. Input expects raw value.",
    [bcmFieldActionClassField]  = "Set the fhei_ext low 32 bits. Input expects raw value.",
    [bcmFieldActionRepCopy]  = "Set the copy type. For possible values look at bcm_field_rep_copy_type_t.",
    [bcmFieldActionDoNotChangeTtl] = "Do not decrement TTL",
    [bcmFieldActionContextId] = "In ePMF, updates FORWARD_CODE.",
    [bcmFieldActionContextIdRaw] = "In ePMF, updates FORWARD_CODE. Input expects raw value.",
    [bcmFieldActionEesEntry0]                   = "EES entry bits 0:29.",
    [bcmFieldActionEesEntry1]                   = "EES entry bits 30:59.",
    [bcmFieldActionEesEntry2]                   = "EES entry bits 60:89.",
    [bcmFieldActionEesEntry3]                   = "EES entry bits 90:119.",
    [bcmFieldActionEesEntry4]                   = "EES entry bits 120:126.",
    [bcmFieldActionEesEntryLocationProfile]     = "EES entry push profile.",
    [bcmFieldActionEesEntryLocationProfileRaw]  = "EES entry push profile. Input expects raw value.",
    [bcmFieldActionOutVportToStamp]             = "Write to OUTLIF TO STAMP field.",
};

const dnx_field_action_map_t dnx_global_action_map[bcmFieldActionCount] = {
    [bcmFieldActionVoid]              = {DNX_ACTION(DNX_FIELD_ACTION_CLASS_SW, 0, DNX_FIELD_SW_ACTION_VOID)},
};

static const dnx_field_action_map_t dnx_ipmf1_action_map[bcmFieldActionCount] = {
/*iPMF1*/    [bcmFieldActionSnoopRaw]               = {DNX_FIELD_ACTION_SNOOP, },
/*iPMF1*/    [bcmFieldActionSnoop]                  = {DNX_FIELD_ACTION_SNOOP, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ingress_snoop_gport_to_code},
/*iPMF1*/    [bcmFieldActionPphPresentSet]          = {DNX_FIELD_ACTION_PPH_TYPE},
/*iPMF1*/    [bcmFieldActionPrioIntNew]             = {DNX_FIELD_ACTION_TC, },
/*iPMF1*/    [bcmFieldActionDropPrecedenceRaw]      = {DNX_FIELD_ACTION_DP, },
/*iPMF1*/    [bcmFieldActionDropPrecedence]         = {DNX_FIELD_ACTION_DP, BCM_TO_DNX_ADDITIONAL_OBJ ,dnx_field_convert_color},
/*iPMF1*/    [bcmFieldActionForward]                = {DNX_FIELD_ACTION_DST_DATA, },
/*iPMF1*/    [bcmFieldActionRedirectMcast]          = {DNX_FIELD_ACTION_DST_DATA, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_dst},
/*iPMF1*/    [bcmFieldActionRedirect]               = {DNX_FIELD_ACTION_DST_DATA, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_dst_plus_qual},
/*iPMF1*/    [bcmFieldActionL3Switch]               = {DNX_FIELD_ACTION_DST_DATA, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_dst},
/*iPMF1*/    [bcmFieldActionFabricHeaderSetRaw]     = {DNX_FIELD_ACTION_SYSTEM_HEADER_PROFILE_INDEX, },
/*iPMF1*/    [bcmFieldActionFabricHeaderSet]        = {DNX_FIELD_ACTION_SYSTEM_HEADER_PROFILE_INDEX, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_system_header_profile},
/*iPMF1*/    [bcmFieldActionUDHData0]               = {DNX_FIELD_ACTION_USER_HEADER_1},
/*iPMF1*/    [bcmFieldActionUDHData1]               = {DNX_FIELD_ACTION_USER_HEADER_2},
/*iPMF1*/    [bcmFieldActionUDHData2]               = {DNX_FIELD_ACTION_USER_HEADER_3},
/*iPMF1*/    [bcmFieldActionUDHData3]               = {DNX_FIELD_ACTION_USER_HEADER_4},
/*iPMF1*/    [bcmFieldActionUDHBase0]               = {DNX_FIELD_ACTION_USER_HEADER_1_TYPE},
/*iPMF1*/    [bcmFieldActionUDHBase1]               = {DNX_FIELD_ACTION_USER_HEADER_2_TYPE},
/*iPMF1*/    [bcmFieldActionUDHBase2]               = {DNX_FIELD_ACTION_USER_HEADER_3_TYPE},
/*iPMF1*/    [bcmFieldActionUDHBase3]               = {DNX_FIELD_ACTION_USER_HEADER_4_TYPE},
/*iPMF1*/    [bcmFieldActionUDHData0Ext]            = {DNX_FIELD_ACTION_USER_HEADER_1_EXT},
/*iPMF1*/    [bcmFieldActionUDHData1Ext]            = {DNX_FIELD_ACTION_USER_HEADER_2_EXT},
/*iPMF1*/    [bcmFieldActionVlanActionSetNew]       = {DNX_FIELD_ACTION_VLAN_EDIT_CMD_INDEX},
/*iPMF1*/    [bcmFieldActionOuterVlanPrioNew]       = {DNX_FIELD_ACTION_VLAN_EDIT_PCP_DEI_1},
/*iPMF1*/    [bcmFieldActionOuterVlanNew]           = {DNX_FIELD_ACTION_VLAN_EDIT_VID_1},
/*iPMF1*/    [bcmFieldActionInnerVlanPrioNew]       = {DNX_FIELD_ACTION_VLAN_EDIT_PCP_DEI_2},
/*iPMF1*/    [bcmFieldActionInnerVlanNew]           = {DNX_FIELD_ACTION_VLAN_EDIT_VID_2},
/*iPMF1*/    [bcmFieldActionUsePolicerResult]       = {DNX_FIELD_ACTION_DP_METER_COMMAND},
/*iPMF1*/    [bcmFieldActionSystemHeaderSet]        = {DNX_FIELD_ACTION_EEI},
/*iPMF1*/    [bcmFieldActionVSQ]                    = {DNX_FIELD_ACTION_ST_VSQ_PTR},
/*iPMF1*/    [bcmFieldActionAdmitProfile]           = {DNX_FIELD_ACTION_ADMT_PROFILE},
/*iPMF1*/    [bcmFieldActionIEEE1588]               = {DNX_FIELD_ACTION_IEEE1588_DATA},
/*iPMF1*/    [bcmFieldActionSrcGportNewRaw]         = {DNX_FIELD_ACTION_SRC_SYS_PORT, },
/*iPMF1*/    [bcmFieldActionSrcGportNew]            = {DNX_FIELD_ACTION_SRC_SYS_PORT, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_sys_port_gport_to_port},
/*iPMF1*/    [bcmFieldActionTtlSet]                 = {DNX_FIELD_ACTION_IN_TTL},
/*iPMF1*/    [bcmFieldActionLatencyFlowIdRaw]       = {DNX_FIELD_ACTION_LATENCY_FLOW, },
/*iPMF1*/    [bcmFieldActionLatencyFlowId]          = {DNX_FIELD_ACTION_LATENCY_FLOW, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_latency_flow_id},
/*iPMF1*/    [bcmFieldActionInVport0Raw]            = {DNX_FIELD_ACTION_GLOB_IN_LIF_0, },
/*iPMF1*/    [bcmFieldActionInVport1Raw]            = {DNX_FIELD_ACTION_GLOB_IN_LIF_1, },
/*iPMF1*/    [bcmFieldActionIngressGportSet]        = {DNX_FIELD_ACTION_GLOB_IN_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_in_lif},
/*iPMF1*/    [bcmFieldActionInVport0]               = {DNX_FIELD_ACTION_GLOB_IN_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_in_lif},
/*iPMF1*/    [bcmFieldActionInVport1]               = {DNX_FIELD_ACTION_GLOB_IN_LIF_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_in_lif},
/*iPMF1*/    [bcmFieldActionInInterface0]           = {DNX_FIELD_ACTION_GLOB_IN_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*iPMF1*/    [bcmFieldActionInInterface1]           = {DNX_FIELD_ACTION_GLOB_IN_LIF_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*iPMF1*/    [bcmFieldActionInVportClass0]          = {DNX_FIELD_ACTION_IN_LIF_PROFILE_0},
/*iPMF1*/    [bcmFieldActionInVportClass1]          = {DNX_FIELD_ACTION_IN_LIF_PROFILE_1},
/*iPMF1*/    [bcmFieldActionMirrorIngressRaw]       = {DNX_FIELD_ACTION_MIRROR_DATA, },
/*iPMF1*/    [bcmFieldActionMirrorIngress]          = {DNX_FIELD_ACTION_MIRROR_DATA, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ingress_sniff_gport_to_code},
/*iPMF1*/    [bcmFieldActionStackingRouteNew]       = {DNX_FIELD_ACTION_STACKING_ROUTE_HISTORY_BITMAP},
/*iPMF1*/    [bcmFieldActionOamRaw]                 = {DNX_FIELD_ACTION_OAM_DATA, },
/*iPMF1*/    [bcmFieldActionOam]                    = {DNX_FIELD_ACTION_OAM_DATA, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_oam},
/*iPMF1*/    [bcmFieldActionPphSnoopCode]           = {DNX_FIELD_ACTION_PPH_RESERVED},
/*iPMF1*/    [bcmFieldActionTrapRaw]                = {DNX_FIELD_ACTION_TRAP, },
/*iPMF1*/    [bcmFieldActionTrap]                   = {DNX_FIELD_ACTION_TRAP, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_trap_gport},
/*iPMF1*/    [bcmFieldActionOutVport0Raw]           = {DNX_FIELD_ACTION_GLOB_OUT_LIF_0, },
/*iPMF1*/    [bcmFieldActionOutVport1Raw]           = {DNX_FIELD_ACTION_GLOB_OUT_LIF_1, },
/*iPMF1*/    [bcmFieldActionOutVport2Raw]           = {DNX_FIELD_ACTION_GLOB_OUT_LIF_2, },
/*iPMF1*/    [bcmFieldActionOutVport3Raw]           = {DNX_FIELD_ACTION_GLOB_OUT_LIF_3, },
/*iPMF1*/    [bcmFieldActionOutVport0]              = {DNX_FIELD_ACTION_GLOB_OUT_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*iPMF1*/    [bcmFieldActionOutVport1]              = {DNX_FIELD_ACTION_GLOB_OUT_LIF_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*iPMF1*/    [bcmFieldActionOutVport2]              = {DNX_FIELD_ACTION_GLOB_OUT_LIF_2, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*iPMF1*/    [bcmFieldActionOutVport3]              = {DNX_FIELD_ACTION_GLOB_OUT_LIF_3, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*iPMF1*/    [bcmFieldActionOutInterface0]          = {DNX_FIELD_ACTION_GLOB_OUT_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*iPMF1*/    [bcmFieldActionOutInterface1]          = {DNX_FIELD_ACTION_GLOB_OUT_LIF_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*iPMF1*/    [bcmFieldActionOutInterface2]          = {DNX_FIELD_ACTION_GLOB_OUT_LIF_2, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*iPMF1*/    [bcmFieldActionOutInterface3]          = {DNX_FIELD_ACTION_GLOB_OUT_LIF_3, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*iPMF1*/    [bcmFieldActionVrfSetRaw]              = {DNX_FIELD_ACTION_FWD_DOMAIN, },
/*iPMF1*/    [bcmFieldActionVrfSet]                 = {DNX_FIELD_ACTION_FWD_DOMAIN, BCM_TO_DNX_ADDITIONAL_OBJ, },
/*iPMF1*/    [bcmFieldActionVSwitchNew]             = {DNX_FIELD_ACTION_FWD_DOMAIN, BCM_TO_DNX_ADDITIONAL_OBJ, },
/*iPMF1*/    [bcmFieldActionFwdDomain]              = {DNX_FIELD_ACTION_FWD_DOMAIN_WITH_PROFILE, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_fwd_domain},
/*iPMF1*/    [bcmFieldActionFwdDomainRaw]           = {DNX_FIELD_ACTION_FWD_DOMAIN_WITH_PROFILE },
/*iPMF1*/    [bcmFieldActionContainer]              = {DNX_FIELD_ACTION_GENERAL_DATA3},
/*iPMF1*/    [bcmFieldActionCbts]                   = {DNX_FIELD_ACTION_PEM_GENERAL_DATA_CBTS},
/*iPMF1*/    [bcmFieldActionEgressForwardingIndex]  = {DNX_FIELD_ACTION_EGRESS_PARSING_INDEX},
/*iPMF1*/    [bcmFieldActionIPTProfile]             = {DNX_FIELD_ACTION_END_OF_PACKET_EDITING},
/*iPMF1*/    [bcmFieldActionStatId0]                = {DNX_FIELD_ACTION_STATISTICS_ID_0},
/*iPMF1*/    [bcmFieldActionStatId1]                = {DNX_FIELD_ACTION_STATISTICS_ID_1},
/*iPMF1*/    [bcmFieldActionStatId2]                = {DNX_FIELD_ACTION_STATISTICS_ID_2},
/*iPMF1*/    [bcmFieldActionStatId3]                = {DNX_FIELD_ACTION_STATISTICS_ID_3},
/*iPMF1*/    [bcmFieldActionStatId4]                = {DNX_FIELD_ACTION_STATISTICS_ID_4},
/*iPMF1*/    [bcmFieldActionStatId5]                = {DNX_FIELD_ACTION_STATISTICS_ID_5},
/*iPMF1*/    [bcmFieldActionStatId6]                = {DNX_FIELD_ACTION_STATISTICS_ID_6},
/*iPMF1*/    [bcmFieldActionStatId7]                = {DNX_FIELD_ACTION_STATISTICS_ID_7},
/*iPMF1*/    [bcmFieldActionStatId8]                = {DNX_FIELD_ACTION_STATISTICS_ID_8},
/*iPMF1*/    [bcmFieldActionStatId9]                = {DNX_FIELD_ACTION_STATISTICS_ID_9},
/*iPMF1*/    [bcmFieldActionStatProfile0Raw]        = {DNX_FIELD_ACTION_STATISTICS_ATR_0, },
/*iPMF1*/    [bcmFieldActionStatProfile1Raw]        = {DNX_FIELD_ACTION_STATISTICS_ATR_1, },
/*iPMF1*/    [bcmFieldActionStatProfile2Raw]        = {DNX_FIELD_ACTION_STATISTICS_ATR_2, },
/*iPMF1*/    [bcmFieldActionStatProfile3Raw]        = {DNX_FIELD_ACTION_STATISTICS_ATR_3, },
/*iPMF1*/    [bcmFieldActionStatProfile4Raw]        = {DNX_FIELD_ACTION_STATISTICS_ATR_4, },
/*iPMF1*/    [bcmFieldActionStatProfile5Raw]        = {DNX_FIELD_ACTION_STATISTICS_ATR_5, },
/*iPMF1*/    [bcmFieldActionStatProfile6Raw]        = {DNX_FIELD_ACTION_STATISTICS_ATR_6, },
/*iPMF1*/    [bcmFieldActionStatProfile7Raw]        = {DNX_FIELD_ACTION_STATISTICS_ATR_7, },
/*iPMF1*/    [bcmFieldActionStatProfile8Raw]        = {DNX_FIELD_ACTION_STATISTICS_ATR_8, },
/*iPMF1*/    [bcmFieldActionStatProfile9Raw]        = {DNX_FIELD_ACTION_STATISTICS_ATR_9, },
/*iPMF1*/    [bcmFieldActionExtStat0Raw]            = {DNX_FIELD_ACTION_EXT_STATISTICS_0, },
/*iPMF1*/    [bcmFieldActionExtStat1Raw]            = {DNX_FIELD_ACTION_EXT_STATISTICS_1, },
/*iPMF1*/    [bcmFieldActionExtStat2Raw]            = {DNX_FIELD_ACTION_EXT_STATISTICS_2, },
/*iPMF1*/    [bcmFieldActionExtStat3Raw]            = {DNX_FIELD_ACTION_EXT_STATISTICS_3, },
/*iPMF1*/    [bcmFieldActionStatProfile0]           = {DNX_FIELD_ACTION_STATISTICS_ATR_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF1*/    [bcmFieldActionStatProfile1]           = {DNX_FIELD_ACTION_STATISTICS_ATR_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF1*/    [bcmFieldActionStatProfile2]           = {DNX_FIELD_ACTION_STATISTICS_ATR_2, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF1*/    [bcmFieldActionStatProfile3]           = {DNX_FIELD_ACTION_STATISTICS_ATR_3, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF1*/    [bcmFieldActionStatProfile4]           = {DNX_FIELD_ACTION_STATISTICS_ATR_4, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF1*/    [bcmFieldActionStatProfile5]           = {DNX_FIELD_ACTION_STATISTICS_ATR_5, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF1*/    [bcmFieldActionStatProfile6]           = {DNX_FIELD_ACTION_STATISTICS_ATR_6, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF1*/    [bcmFieldActionStatProfile7]           = {DNX_FIELD_ACTION_STATISTICS_ATR_7, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF1*/    [bcmFieldActionStatProfile8]           = {DNX_FIELD_ACTION_STATISTICS_ATR_8, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF1*/    [bcmFieldActionStatProfile9]           = {DNX_FIELD_ACTION_STATISTICS_ATR_9, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF1*/    [bcmFieldActionExtStat0]               = {DNX_FIELD_ACTION_EXT_STATISTICS_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ext_stat_with_valid},
/*iPMF1*/    [bcmFieldActionExtStat1]               = {DNX_FIELD_ACTION_EXT_STATISTICS_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ext_stat},
/*iPMF1*/    [bcmFieldActionExtStat2]               = {DNX_FIELD_ACTION_EXT_STATISTICS_2, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ext_stat},
/*iPMF1*/    [bcmFieldActionExtStat3]               = {DNX_FIELD_ACTION_EXT_STATISTICS_3, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ext_stat},
/*iPMF1*/    [bcmFieldActionIngressTimeStampInsert] = {DNX_FIELD_ACTION_INGRESS_TIME_STAMP},
/*iPMF1*/    [bcmFieldActionStatMetaData]           = {DNX_FIELD_ACTION_STATISTICS_META_DATA},
/*iPMF1*/    [bcmFieldActionInvalidNext]            = {DNX_FIELD_ACTION_INVALIDATE_NEXT},
/*iPMF1*/    [bcmFieldActionForwardingTypeMeterMap] = {DNX_FIELD_ACTION_STATISTICS_OBJECT_10},
/*iPMF1*/    [bcmFieldActionStatSamplingRaw]        = {DNX_FIELD_ACTION_STATISTICAL_SAMPLING, },
/*iPMF1*/    [bcmFieldActionStatSampling]           = {DNX_FIELD_ACTION_STATISTICAL_SAMPLING, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ingress_sniff_gport_to_code},
/*iPMF1*/    [bcmFieldActionStatOamLMRaw]           = {DNX_FIELD_ACTION_STAT_OBJ_LM_READ_INDEX, },
/*iPMF1*/    [bcmFieldActionStatOamLM]              = {DNX_FIELD_ACTION_STAT_OBJ_LM_READ_INDEX,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_lm_index},
/*iPMF1*/    [bcmFieldActionForwardingLayerIndex]   = {DNX_FIELD_ACTION_FWD_LAYER_INDEX},
/*iPMF1*/    [bcmFieldActionVisibilityEnable]       = {DNX_FIELD_ACTION_VISIBILITY},
/*iPMF1*/    [bcmFieldActionVisibilityClear]        = {DNX_FIELD_ACTION_VISIBILITY_CLEAR},
/*iPMF1*/    [bcmFieldActionSmallExemLearn]         = {DNX_FIELD_ACTION_ELEPHANT_PAYLOAD},
/*iPMF1*/    [bcmFieldActionPacketTraceEnable]      = {DNX_FIELD_ACTION_TRACE_PACKET_ACT},
/*iPMF1*/    [bcmFieldActionBierStringOffset]       = {DNX_FIELD_ACTION_BIER_STR_OFFSET},
/*iPMF1*/    [bcmFieldActionBierStringSize]         = {DNX_FIELD_ACTION_BIER_STR_SIZE},
/*iPMF1*/    [bcmFieldActionPacketIsBier]           = {DNX_FIELD_ACTION_PACKET_IS_BIER},
/*iPMF1*/    [bcmFieldActionEventor]                = {DNX_FIELD_ACTION_EVENTOR},
/*iPMF1*/    [bcmFieldActionForwardingAdditionalInfo]  = {DNX_FIELD_ACTION_FWD_LAYER_ADDITIONAL_INFO},
/*iPMF1*/    [bcmFieldActionNetworkQos]             = {DNX_FIELD_ACTION_NWK_QOS},
/*iPMF1*/    [bcmFieldActionIngressDoNotLearn]             = {DNX_FIELD_ACTION_INGRESS_LEARN_ENABLE},
/*iPMF1*/    [bcmFieldActionEgressDoNotLearn]             = {DNX_FIELD_ACTION_EGRESS_LEARN_ENABLE},
/*iPMF1*/    [bcmFieldActionIngressTimeStampInsertValid]    = {DNX_FIELD_ACTION_INGRESS_TIME_STAMP_OVERRIDE},
/*iPMF1*/    [bcmFieldActionIpMulticastCompatible]     = {DNX_FIELD_ACTION_PACKET_IS_COMPATIBLE_MC, },
/*iPMF1*/    [bcmFieldActionDstRpfGportNewRaw]         = {DNX_FIELD_ACTION_RPF_DST, },
/*iPMF1*/    [bcmFieldActionDstRpfGportNew]            = {DNX_FIELD_ACTION_RPF_DST, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_dst},
/*iPMF1*/    [bcmFieldActionDstRpfGportNewValid]       = {DNX_FIELD_ACTION_RPF_DST_VALID, },
/*iPMF1*/    [bcmFieldActionRpfOutVportRaw]            = {DNX_FIELD_ACTION_RPF_OUT_LIF, },
/*iPMF1*/    [bcmFieldActionRpfOutVport]               = {DNX_FIELD_ACTION_RPF_OUT_LIF, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_rpf_out_lif_encoded},
/*iPMF1*/    [bcmFieldActionRpfOutInterface]           = {DNX_FIELD_ACTION_RPF_OUT_LIF, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_rpf_out_lif_encoded},
/*iPMF1*/    [bcmFieldActionLearnRaw0]                 = {DNX_FIELD_ACTION_LEARN_INFO_0, },
/*iPMF1*/    [bcmFieldActionLearnRaw1]                 = {DNX_FIELD_ACTION_LEARN_INFO_1, },
/*iPMF1*/    [bcmFieldActionLearnRaw2]                 = {DNX_FIELD_ACTION_LEARN_INFO_2, },
/*iPMF1*/    [bcmFieldActionLearnRaw3]                 = {DNX_FIELD_ACTION_LEARN_INFO_3, },
/*iPMF1*/    [bcmFieldActionLearnRaw4]                 = {DNX_FIELD_ACTION_LEARN_INFO_4, },
/*iPMF1*/    [bcmFieldActionLearnOrTransplant]         = {DNX_FIELD_ACTION_LEARN_OR_TRANSPLANT, },
/*iPMF1*/    [bcmFieldActionLearnKey0]                 = {DNX_FIELD_ACTION_LEARN_INFO_KEY_0, },
/*iPMF1*/    [bcmFieldActionLearnKey1]                 = {DNX_FIELD_ACTION_LEARN_INFO_KEY_1, },
/*iPMF1*/    [bcmFieldActionLearnKey2Raw]              = {DNX_FIELD_ACTION_LEARN_INFO_KEY_2_APP_DB_INDEX, },
/*iPMF1*/    [bcmFieldActionLearnKey2]                 = {DNX_FIELD_ACTION_LEARN_INFO_KEY_2_APP_DB_INDEX, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_learn_info_key_2},
/*iPMF1*/    [bcmFieldActionLearnPayload0]             = {DNX_FIELD_ACTION_LEARN_INFO_PAYLOAD_0, },
/*iPMF1*/    [bcmFieldActionLearnPayload1]             = {DNX_FIELD_ACTION_LEARN_INFO_PAYLOAD_1, },
/*iPMF1*/    [bcmFieldActionLearnEntryFormatIndex]     = {DNX_FIELD_ACTION_LEARN_INFO_FORMAT_INDEX, },
/*iPMF1*/    [bcmFieldActionEcnNew]                    = {DNX_FIELD_ACTION_CONGESTION_INFO},
/*iPMF1*/    [bcmFieldActionPrtQualifier]              = {DNX_FIELD_ACTION_PRT_QUALIFIER},
};

static const dnx_field_action_map_t dnx_ipmf3_action_map[bcmFieldActionCount] = {
/*iPMF3*/    [bcmFieldActionSnoopRaw]              = {DNX_FIELD_ACTION_SNOOP, },
/*iPMF3*/    [bcmFieldActionSnoop]                 = {DNX_FIELD_ACTION_SNOOP, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ingress_snoop_gport_to_code},
/*iPMF3*/    [bcmFieldActionPphPresentSet]         = {DNX_FIELD_ACTION_PPH_TYPE},
/*iPMF3*/    [bcmFieldActionPrioIntNew]            = {DNX_FIELD_ACTION_TC,},
/*iPMF3*/    [bcmFieldActionDropPrecedenceRaw]     = {DNX_FIELD_ACTION_DP, },
/*iPMF3*/    [bcmFieldActionDropPrecedence]        = {DNX_FIELD_ACTION_DP, BCM_TO_DNX_ADDITIONAL_OBJ ,dnx_field_convert_color},
/*iPMF3*/    [bcmFieldActionForward]               = {DNX_FIELD_ACTION_DST_DATA, },
/*iPMF3*/    [bcmFieldActionRedirectMcast]         = {DNX_FIELD_ACTION_DST_DATA,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_dst},
/*iPMF3*/    [bcmFieldActionRedirect     ]         = {DNX_FIELD_ACTION_DST_DATA,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_dst_plus_qual},
/*iPMF3*/    [bcmFieldActionL3Switch]              = {DNX_FIELD_ACTION_DST_DATA,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_dst},
/*iPMF3*/    [bcmFieldActionStartPacketStripRaw]   = {DNX_FIELD_ACTION_BYTES_TO_REMOVE, },
/*iPMF3*/    [bcmFieldActionStartPacketStrip]      = {DNX_FIELD_ACTION_BYTES_TO_REMOVE, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_packet_strip},
/*iPMF3*/    [bcmFieldActionVlanActionSetNew]      = {DNX_FIELD_ACTION_VLAN_EDIT_CMD_INDEX},
/*iPMF3*/    [bcmFieldActionOuterVlanPrioNew]      = {DNX_FIELD_ACTION_VLAN_EDIT_PCP_DEI_1},
/*iPMF3*/    [bcmFieldActionOuterVlanNew]          = {DNX_FIELD_ACTION_VLAN_EDIT_VID_1},
/*iPMF3*/    [bcmFieldActionInnerVlanPrioNew]      = {DNX_FIELD_ACTION_VLAN_EDIT_PCP_DEI_2},
/*iPMF3*/    [bcmFieldActionInnerVlanNew]          = {DNX_FIELD_ACTION_VLAN_EDIT_VID_2},
/*iPMF3*/    [bcmFieldActionUsePolicerResult]      = {DNX_FIELD_ACTION_DP_METER_COMMAND},
/*iPMF3*/    [bcmFieldActionSystemHeaderSet]       = {DNX_FIELD_ACTION_EEI},
/*iPMF3*/    [bcmFieldActionVSQ]                   = {DNX_FIELD_ACTION_ST_VSQ_PTR},
/*iPMF3*/    [bcmFieldActionAdmitProfile]          = {DNX_FIELD_ACTION_ADMT_PROFILE},
/*iPMF3*/    [bcmFieldActionIEEE1588]              = {DNX_FIELD_ACTION_IEEE1588_DATA},
/*iPMF3*/    [bcmFieldActionSrcGportNewRaw]        = {DNX_FIELD_ACTION_SRC_SYS_PORT, },
/*iPMF3*/    [bcmFieldActionSrcGportNew]           = {DNX_FIELD_ACTION_SRC_SYS_PORT, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_sys_port_gport_to_port},
/*iPMF3*/    [bcmFieldActionTtlSet]                = {DNX_FIELD_ACTION_IN_TTL},
/*iPMF3*/    [bcmFieldActionLatencyFlowIdRaw]      = {DNX_FIELD_ACTION_LATENCY_FLOW, },
/*iPMF3*/    [bcmFieldActionLatencyFlowId]         = {DNX_FIELD_ACTION_LATENCY_FLOW, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_latency_flow_id},
/*iPMF3*/    [bcmFieldActionInVport0Raw]           = {DNX_FIELD_ACTION_GLOB_IN_LIF_0, },
/*iPMF3*/    [bcmFieldActionInVport1Raw]           = {DNX_FIELD_ACTION_GLOB_IN_LIF_1, },
/*iPMF3*/    [bcmFieldActionIngressGportSet]       = {DNX_FIELD_ACTION_GLOB_IN_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_in_lif},
/*iPMF3*/    [bcmFieldActionInVport0]              = {DNX_FIELD_ACTION_GLOB_IN_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_in_lif},
/*iPMF3*/    [bcmFieldActionInVport1]              = {DNX_FIELD_ACTION_GLOB_IN_LIF_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_in_lif},
/*iPMF3*/    [bcmFieldActionInInterface0]          = {DNX_FIELD_ACTION_GLOB_IN_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*iPMF3*/    [bcmFieldActionInInterface1]          = {DNX_FIELD_ACTION_GLOB_IN_LIF_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*iPMF3*/    [bcmFieldActionInVportClass0]         = {DNX_FIELD_ACTION_IN_LIF_PROFILE_0},
/*iPMF3*/    [bcmFieldActionInVportClass1]         = {DNX_FIELD_ACTION_IN_LIF_PROFILE_1},
/*iPMF3*/    [bcmFieldActionMirrorIngressRaw]      = {DNX_FIELD_ACTION_MIRROR_DATA, },
/*iPMF3*/    [bcmFieldActionMirrorIngress]         = {DNX_FIELD_ACTION_MIRROR_DATA, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ingress_sniff_gport_to_code},
/*iPMF3*/    [bcmFieldActionStackingRouteNew]      = {DNX_FIELD_ACTION_STACKING_ROUTE_HISTORY_BITMAP},
/*iPMF3*/    [bcmFieldActionOamRaw]                = {DNX_FIELD_ACTION_OAM_DATA, },
/*iPMF3*/    [bcmFieldActionOam]                   = {DNX_FIELD_ACTION_OAM_DATA, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_oam},
/*iPMF3*/    [bcmFieldActionPphSnoopCode]          = {DNX_FIELD_ACTION_PPH_RESERVED},
/*iPMF3*/    [bcmFieldActionTrapRaw]               = {DNX_FIELD_ACTION_TRAP, },
/*iPMF3*/    [bcmFieldActionTrap]                  = {DNX_FIELD_ACTION_TRAP, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_trap_gport},
/*iPMF3*/    [bcmFieldActionOutVport0Raw]          = {DNX_FIELD_ACTION_GLOB_OUT_LIF_0, },
/*iPMF3*/    [bcmFieldActionOutVport1Raw]          = {DNX_FIELD_ACTION_GLOB_OUT_LIF_1, },
/*iPMF3*/    [bcmFieldActionOutVport2Raw]          = {DNX_FIELD_ACTION_GLOB_OUT_LIF_2, },
/*iPMF3*/    [bcmFieldActionOutVport3Raw]          = {DNX_FIELD_ACTION_GLOB_OUT_LIF_3, },
/*iPMF3*/    [bcmFieldActionOutVport0]             = {DNX_FIELD_ACTION_GLOB_OUT_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*iPMF3*/    [bcmFieldActionOutVport1]             = {DNX_FIELD_ACTION_GLOB_OUT_LIF_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*iPMF3*/    [bcmFieldActionOutVport2]             = {DNX_FIELD_ACTION_GLOB_OUT_LIF_2, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*iPMF3*/    [bcmFieldActionOutVport3]             = {DNX_FIELD_ACTION_GLOB_OUT_LIF_3, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*iPMF3*/    [bcmFieldActionOutInterface0]         = {DNX_FIELD_ACTION_GLOB_OUT_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*iPMF3*/    [bcmFieldActionOutInterface1]         = {DNX_FIELD_ACTION_GLOB_OUT_LIF_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*iPMF3*/    [bcmFieldActionOutInterface2]         = {DNX_FIELD_ACTION_GLOB_OUT_LIF_2, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*iPMF3*/    [bcmFieldActionOutInterface3]         = {DNX_FIELD_ACTION_GLOB_OUT_LIF_3, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*iPMF3*/    [bcmFieldActionVSwitchNew]            = {DNX_FIELD_ACTION_FWD_DOMAIN,},
/*iPMF3*/    [bcmFieldActionVrfSet]                = {DNX_FIELD_ACTION_FWD_DOMAIN, BCM_TO_DNX_ADDITIONAL_OBJ},
/*iPMF3*/    [bcmFieldActionTrunkHashKeySet]       = {DNX_FIELD_ACTION_LAG_LB_KEY},
/*iPMF3*/    [bcmFieldActionNetworkLoadBalanceKey] = {DNX_FIELD_ACTION_NWK_LB_KEY},
/*iPMF3*/    [bcmFieldActionParsingStartTypeRaw]   = {DNX_FIELD_ACTION_PARSING_START_TYPE, },
/*iPMF3*/    [bcmFieldActionParsingStartType]      = {DNX_FIELD_ACTION_PARSING_START_TYPE, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_parsing_start_type},
/*iPMF3*/    [bcmFieldActionParsingStartOffsetRaw] = {DNX_FIELD_ACTION_PARSING_START_OFFSET, },
/*iPMF3*/    [bcmFieldActionParsingStartOffset]    = {DNX_FIELD_ACTION_PARSING_START_OFFSET, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_parsing_start_offset},
/*iPMF3*/    [bcmFieldActionEgressForwardingIndex] = {DNX_FIELD_ACTION_EGRESS_PARSING_INDEX},
/*iPMF3*/    [bcmFieldActionUDHData0]              = {DNX_FIELD_ACTION_USER_HEADER_1},
/*iPMF3*/    [bcmFieldActionUDHData1]              = {DNX_FIELD_ACTION_USER_HEADER_2},
/*iPMF3*/    [bcmFieldActionUDHData2]              = {DNX_FIELD_ACTION_USER_HEADER_3},
/*iPMF3*/    [bcmFieldActionUDHData3]              = {DNX_FIELD_ACTION_USER_HEADER_4},
/*iPMF3*/    [bcmFieldActionUDHBase]               = {DNX_FIELD_ACTION_USER_HEADERS_TYPE},
/*iPMF3*/    [bcmFieldActionUDHData0Ext]           = {DNX_FIELD_ACTION_USER_HEADER_1_EXT},
/*iPMF3*/    [bcmFieldActionUDHData1Ext]           = {DNX_FIELD_ACTION_USER_HEADER_2_EXT},
/*iPMF3*/    [bcmFieldActionIPTCommandRaw]         = {DNX_FIELD_ACTION_INT_DATA,},
/*iPMF3*/    [bcmFieldActionIPTCommand]            = {DNX_FIELD_ACTION_INT_DATA, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ipt_command},
/*iPMF3*/    [bcmFieldActionStatId0]               = {DNX_FIELD_ACTION_STATISTICS_ID_0},
/*iPMF3*/    [bcmFieldActionStatId1]               = {DNX_FIELD_ACTION_STATISTICS_ID_1},
/*iPMF3*/    [bcmFieldActionStatId2]               = {DNX_FIELD_ACTION_STATISTICS_ID_2},
/*iPMF3*/    [bcmFieldActionStatId3]               = {DNX_FIELD_ACTION_STATISTICS_ID_3},
/*iPMF3*/    [bcmFieldActionStatId4]               = {DNX_FIELD_ACTION_STATISTICS_ID_4},
/*iPMF3*/    [bcmFieldActionStatId5]               = {DNX_FIELD_ACTION_STATISTICS_ID_5},
/*iPMF3*/    [bcmFieldActionStatId6]               = {DNX_FIELD_ACTION_STATISTICS_ID_6},
/*iPMF3*/    [bcmFieldActionStatId7]               = {DNX_FIELD_ACTION_STATISTICS_ID_7},
/*iPMF3*/    [bcmFieldActionStatId8]               = {DNX_FIELD_ACTION_STATISTICS_ID_8},
/*iPMF3*/    [bcmFieldActionStatId9]               = {DNX_FIELD_ACTION_STATISTICS_ID_9},
/*iPMF3*/    [bcmFieldActionStatProfile0Raw]       = {DNX_FIELD_ACTION_STATISTICS_ATR_0, },
/*iPMF3*/    [bcmFieldActionStatProfile1Raw]       = {DNX_FIELD_ACTION_STATISTICS_ATR_1, },
/*iPMF3*/    [bcmFieldActionStatProfile2Raw]       = {DNX_FIELD_ACTION_STATISTICS_ATR_2, },
/*iPMF3*/    [bcmFieldActionStatProfile3Raw]       = {DNX_FIELD_ACTION_STATISTICS_ATR_3, },
/*iPMF3*/    [bcmFieldActionStatProfile4Raw]       = {DNX_FIELD_ACTION_STATISTICS_ATR_4, },
/*iPMF3*/    [bcmFieldActionStatProfile5Raw]       = {DNX_FIELD_ACTION_STATISTICS_ATR_5, },
/*iPMF3*/    [bcmFieldActionStatProfile6Raw]       = {DNX_FIELD_ACTION_STATISTICS_ATR_6, },
/*iPMF3*/    [bcmFieldActionStatProfile7Raw]       = {DNX_FIELD_ACTION_STATISTICS_ATR_7, },
/*iPMF3*/    [bcmFieldActionStatProfile8Raw]       = {DNX_FIELD_ACTION_STATISTICS_ATR_8, },
/*iPMF3*/    [bcmFieldActionStatProfile9Raw]       = {DNX_FIELD_ACTION_STATISTICS_ATR_9, },
/*iPMF3*/    [bcmFieldActionStatProfile0]          = {DNX_FIELD_ACTION_STATISTICS_ATR_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF3*/    [bcmFieldActionStatProfile1]          = {DNX_FIELD_ACTION_STATISTICS_ATR_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF3*/    [bcmFieldActionStatProfile2]          = {DNX_FIELD_ACTION_STATISTICS_ATR_2, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF3*/    [bcmFieldActionStatProfile3]          = {DNX_FIELD_ACTION_STATISTICS_ATR_3, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF3*/    [bcmFieldActionStatProfile4]          = {DNX_FIELD_ACTION_STATISTICS_ATR_4, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF3*/    [bcmFieldActionStatProfile5]          = {DNX_FIELD_ACTION_STATISTICS_ATR_5, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF3*/    [bcmFieldActionStatProfile6]          = {DNX_FIELD_ACTION_STATISTICS_ATR_6, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF3*/    [bcmFieldActionStatProfile7]          = {DNX_FIELD_ACTION_STATISTICS_ATR_7, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF3*/    [bcmFieldActionStatProfile8]          = {DNX_FIELD_ACTION_STATISTICS_ATR_8, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF3*/    [bcmFieldActionStatProfile9]          = {DNX_FIELD_ACTION_STATISTICS_ATR_9, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_profile},
/*iPMF3*/    [bcmFieldActionStatMetaData]          = {DNX_FIELD_ACTION_STATISTICS_META_DATA},
/*iPMF3*/    [bcmFieldActionInvalidNext]           = {DNX_FIELD_ACTION_INVALIDATE_NEXT},
/*iPMF3*/    [bcmFieldActionExtStat0Raw]           = {DNX_FIELD_ACTION_EXT_STATISTICS_0, },
/*iPMF3*/    [bcmFieldActionExtStat1Raw]           = {DNX_FIELD_ACTION_EXT_STATISTICS_1, },
/*iPMF3*/    [bcmFieldActionExtStat2Raw]           = {DNX_FIELD_ACTION_EXT_STATISTICS_2, },
/*iPMF3*/    [bcmFieldActionExtStat3Raw]           = {DNX_FIELD_ACTION_EXT_STATISTICS_3, },
/*iPMF3*/    [bcmFieldActionExtStat0]              = {DNX_FIELD_ACTION_EXT_STATISTICS_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ext_stat_with_valid},
/*iPMF3*/    [bcmFieldActionExtStat1]              = {DNX_FIELD_ACTION_EXT_STATISTICS_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ext_stat},
/*iPMF3*/    [bcmFieldActionExtStat2]              = {DNX_FIELD_ACTION_EXT_STATISTICS_2, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ext_stat},
/*iPMF3*/    [bcmFieldActionExtStat3]              = {DNX_FIELD_ACTION_EXT_STATISTICS_3, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ext_stat},
/*iPMF3*/    [bcmFieldActionForwardingTypeMeterMap]= {DNX_FIELD_ACTION_STATISTICS_OBJECT_10},
/*iPMF3*/    [bcmFieldActionStatSamplingRaw]       = {DNX_FIELD_ACTION_STATISTICAL_SAMPLING, },
/*iPMF3*/    [bcmFieldActionStatSampling]          = {DNX_FIELD_ACTION_STATISTICAL_SAMPLING, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ingress_sniff_gport_to_code},
/*iPMF3*/    [bcmFieldActionIPTProfile]            = {DNX_FIELD_ACTION_END_OF_PACKET_EDITING},
/*iPMF3*/    [bcmFieldActionStatOamLMRaw]          = {DNX_FIELD_ACTION_STAT_OBJ_LM_READ_INDEX, },
/*iPMF3*/    [bcmFieldActionStatOamLM]             = {DNX_FIELD_ACTION_STAT_OBJ_LM_READ_INDEX,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_lm_index},
/*iPMF3*/    [bcmFieldActionForwardingLayerIndex]  = {DNX_FIELD_ACTION_FWD_LAYER_INDEX},
/*iPMF3*/    [bcmFieldActionVisibilityEnable]      = {DNX_FIELD_ACTION_VISIBILITY},
/*iPMF3*/    [bcmFieldActionBierStringOffset]      = {DNX_FIELD_ACTION_BIER_STR_OFFSET},
/*iPMF3*/    [bcmFieldActionBierStringSize]        = {DNX_FIELD_ACTION_BIER_STR_SIZE},
/*iPMF3*/    [bcmFieldActionPacketIsBier]          = {DNX_FIELD_ACTION_PACKET_IS_BIER},
/*iPMF3*/    [bcmFieldActionForwardingAdditionalInfo]  = {DNX_FIELD_ACTION_FWD_LAYER_ADDITIONAL_INFO},
/*iPMF3*/    [bcmFieldActionSystemHeaderSizeAdjust]      = {DNX_FIELD_ACTION_SYSTEM_HEADER_SIZE_ADJUST},
/*iPMF3*/    [bcmFieldActionNetworkQos]             = {DNX_FIELD_ACTION_NWK_QOS},
/*iPMF3*/    [bcmFieldActionAppendPointerCompensation]  = {DNX_FIELD_ACTION_NWK_HEADER_APPEND_SIZE},
/*iPMF3*/    [bcmFieldActionIngressTimeStampInsertValid]    = {DNX_FIELD_ACTION_INGRESS_TIME_STAMP_OVERRIDE},
/*iPMF3*/    [bcmFieldActionLearnRaw0]                = {DNX_FIELD_ACTION_LEARN_INFO_0, },
/*iPMF3*/    [bcmFieldActionLearnRaw1]                = {DNX_FIELD_ACTION_LEARN_INFO_1, },
/*iPMF3*/    [bcmFieldActionLearnRaw2]                = {DNX_FIELD_ACTION_LEARN_INFO_2, },
/*iPMF3*/    [bcmFieldActionLearnRaw3]                = {DNX_FIELD_ACTION_LEARN_INFO_3, },
/*iPMF3*/    [bcmFieldActionLearnRaw4]                = {DNX_FIELD_ACTION_LEARN_INFO_4, },
/*iPMF3*/    [bcmFieldActionLearnOrTransplant]        = {DNX_FIELD_ACTION_LEARN_OR_TRANSPLANT, },
/*iPMF3*/    [bcmFieldActionLearnKey0]                = {DNX_FIELD_ACTION_LEARN_INFO_KEY_0, },
/*iPMF3*/    [bcmFieldActionLearnKey1]                = {DNX_FIELD_ACTION_LEARN_INFO_KEY_1, },
/*iPMF3*/    [bcmFieldActionLearnKey2Raw]             = {DNX_FIELD_ACTION_LEARN_INFO_KEY_2_APP_DB_INDEX, },
/*iPMF3*/    [bcmFieldActionLearnKey2]                = {DNX_FIELD_ACTION_LEARN_INFO_KEY_2_APP_DB_INDEX, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_learn_info_key_2},
/*iPMF3*/    [bcmFieldActionLearnPayload0]            = {DNX_FIELD_ACTION_LEARN_INFO_PAYLOAD_0, },
/*iPMF3*/    [bcmFieldActionLearnPayload1]            = {DNX_FIELD_ACTION_LEARN_INFO_PAYLOAD_1, },
/*iPMF3*/    [bcmFieldActionLearnEntryFormatIndex]    = {DNX_FIELD_ACTION_LEARN_INFO_FORMAT_INDEX, },
/*iPMF3*/    [bcmFieldActionEcnNew]                   = {DNX_FIELD_ACTION_CONGESTION_INFO},
/*iPMF3*/    [bcmFieldActionFabricHeaderSetRaw]       = {DNX_FIELD_ACTION_SYSTEM_HEADER_PROFILE_INDEX, },
/*iPMF3*/    [bcmFieldActionFabricHeaderSet]          = {DNX_FIELD_ACTION_SYSTEM_HEADER_PROFILE_INDEX, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_system_header_profile},
/*iPMF3*/    [bcmFieldActionRepCopy]                  = {DNX_FIELD_ACTION_TM_ACTION_TYPE, 0, dnx_field_convert_rep_copy_type},
};

static const dnx_field_action_map_t dnx_epmf_action_map[bcmFieldActionCount] = {

/*ePMF*/    [bcmFieldActionPrioIntNew]                  = {DNX_FIELD_ACTION_TC, },
/*ePMF*/    [bcmFieldActionDropPrecedenceRaw]           = {DNX_FIELD_ACTION_DP, },
/*ePMF*/    [bcmFieldActionDropPrecedence]              = {DNX_FIELD_ACTION_DP, BCM_TO_DNX_ADDITIONAL_OBJ ,dnx_field_convert_color},
/*ePMF*/    [bcmFieldActionIPTProfile]                  = {DNX_FIELD_ACTION_END_OF_PACKET_EDITING},
/*ePMF*/    [bcmFieldActionTtlSet]                      = {DNX_FIELD_ACTION_PPH_TTL},
/*ePMF*/    [bcmFieldActionAceContextValueRaw]          = {DNX_FIELD_ACTION_ACE_CONTEXT_VALUE, },
/*ePMF*/    [bcmFieldActionAceContextValue]             = {DNX_FIELD_ACTION_ACE_CONTEXT_VALUE, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ace_context},
/*ePMF*/    [bcmFieldActionQosMapIdNew]                 = {DNX_FIELD_ACTION_COS_PROFILE},
/*ePMF*/    [bcmFieldActionEcnNew]                      = {DNX_FIELD_ACTION_CNI},
/*ePMF*/    [bcmFieldActionLearnSrcPortNew]             = {DNX_FIELD_ACTION_SRC_SYS_PORT},
/*ePMF*/    [bcmFieldActionInvalidNext]                 = {DNX_FIELD_ACTION_INVALIDATE_NEXT},
/*ePMF*/    [bcmFieldActionOutVport0Raw]                = {DNX_FIELD_ACTION_GLOB_OUT_LIF_0 ,},
/*ePMF*/    [bcmFieldActionOutVport1Raw]                = {DNX_FIELD_ACTION_GLOB_OUT_LIF_1, },
/*ePMF*/    [bcmFieldActionOutVport2Raw]                = {DNX_FIELD_ACTION_GLOB_OUT_LIF_2, },
/*ePMF*/    [bcmFieldActionOutVport3Raw]                = {DNX_FIELD_ACTION_GLOB_OUT_LIF_3, },
/*ePMF*/    [bcmFieldActionOutVport0]                   = {DNX_FIELD_ACTION_GLOB_OUT_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*ePMF*/    [bcmFieldActionOutVport1]                   = {DNX_FIELD_ACTION_GLOB_OUT_LIF_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*ePMF*/    [bcmFieldActionOutVport2]                   = {DNX_FIELD_ACTION_GLOB_OUT_LIF_2, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*ePMF*/    [bcmFieldActionOutVport3]                   = {DNX_FIELD_ACTION_GLOB_OUT_LIF_3, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif},
/*ePMF*/    [bcmFieldActionOutInterface0]               = {DNX_FIELD_ACTION_GLOB_OUT_LIF_0, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*ePMF*/    [bcmFieldActionOutInterface1]               = {DNX_FIELD_ACTION_GLOB_OUT_LIF_1, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*ePMF*/    [bcmFieldActionOutInterface2]               = {DNX_FIELD_ACTION_GLOB_OUT_LIF_2, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*ePMF*/    [bcmFieldActionOutInterface3]               = {DNX_FIELD_ACTION_GLOB_OUT_LIF_3, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif},
/*ePMF*/    [bcmFieldActionForwardingLayerIndex]        = {DNX_FIELD_ACTION_FWD_LAYER_INDEX, },
/*ePMF*/    [bcmFieldActionNetworkQos]                  = {DNX_FIELD_ACTION_NWK_QOS, },
/*ePMF*/    [bcmFieldActionClassField]                  = {DNX_FIELD_ACTION_FHEI_EXT_31_00, },
/*ePMF*/    [bcmFieldActionMirrorEgressRaw]             = {DNX_FIELD_ACTION_MIRROR_PROFILE, },
/*ePMF*/    [bcmFieldActionMirrorEgress]                = {DNX_FIELD_ACTION_MIRROR_PROFILE, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_egress_sniff_gport_to_profile},
            
/*ePMF*/    [bcmFieldActionStat0]                       = {DNX_FIELD_ACTION_ACE_STAT0_COUNTER},
            
/*ePMF*/    [bcmFieldActionStat1]                       = {DNX_FIELD_ACTION_ACE_STAT1_COUNTER},
/*ePMF*/    [bcmFieldActionStat0Raw]                    = {DNX_FIELD_ACTION_ACE_STAT0_COUNTER},
/*ePMF*/    [bcmFieldActionStat1Raw]                    = {DNX_FIELD_ACTION_ACE_STAT1_COUNTER},
/*ePMF*/    [bcmFieldActionAceEntryId]                  = {DNX_FIELD_ACTION_CUD_OUTLIF_OR_MCDB_PTR},
/*ePMF*/    [bcmFieldActionStatId0]                     = {DNX_FIELD_ACTION_PMF_COUNTER_0_PTR},
/*ePMF*/    [bcmFieldActionStatProfile0]                = {DNX_FIELD_ACTION_PMF_COUNTER_0_PROFILE},
/*ePMF*/    [bcmFieldActionStatId1]                     = {DNX_FIELD_ACTION_PMF_COUNTER_1_PTR},
/*ePMF*/    [bcmFieldActionStatProfile1]                = {DNX_FIELD_ACTION_PMF_COUNTER_1_PROFILE},
/*ePMF*/    [bcmFieldActionOutPortTrafficManagement]    = {DNX_FIELD_ACTION_PP_DSP},
/*ePMF*/    [bcmFieldActionOutPortPacketProcessing]     = {DNX_FIELD_ACTION_OUT_PP_PORT},
/*ePMF*/    [bcmFieldActionPpDsp]                       = {DNX_FIELD_ACTION_FTMH_PP_DSP},
/*ePMF*/    [bcmFieldActionTrap]                        = {DNX_FIELD_ACTION_TRAP, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_egress_trap_id},
/*ePMF*/    [bcmFieldActionTrapRaw]                     = {DNX_FIELD_ACTION_TRAP},
/*ePMF*/    [bcmFieldActionTrapStrengthRaw]             = {DNX_FIELD_ACTION_PMF_FWD_STRENGTH, },
/*ePMF*/    [bcmFieldActionTrapStrength]                = {DNX_FIELD_ACTION_PMF_FWD_STRENGTH, BCM_TO_DNX_ADDITIONAL_OBJ , dnx_field_convert_egress_trap_gport_to_strength},
/*ePMF*/    [bcmFieldActionSnoopRaw]                    = {DNX_FIELD_ACTION_SNOOP , },
/*ePMF*/    [bcmFieldActionSnoopStrengthRaw]            = {DNX_FIELD_ACTION_SNOOP_STRENGTH, },
/*ePMF*/    
/*ePMF*/    [bcmFieldActionSnoop]                       = {DNX_FIELD_ACTION_SNOOP , BCM_TO_DNX_ADDITIONAL_OBJ , dnx_field_convert_egress_sniff_gport_to_profile},
/*ePMF*/    [bcmFieldActionSnoopStrength]               = {DNX_FIELD_ACTION_SNOOP_STRENGTH, BCM_TO_DNX_ADDITIONAL_OBJ , dnx_field_convert_egress_snoop_gport_to_strength},
/*ePMF*/    [bcmFieldActionDrop]                        = {DNX_FIELD_ACTION_DISCARD},
/*ePMF*/    [bcmFieldActionEstimatedStartPacketStrip]   = {DNX_FIELD_ACTION_EBTR_SOP_DELTA, },
/*ePMF*/    [bcmFieldActionDoNotChangeTtl]              = {DNX_FIELD_ACTION_FAI_DO_NOT_DECREMENT_TTL, },
/*ePMF*/    [bcmFieldActionContextIdRaw]                = {DNX_FIELD_ACTION_FORWARD_CODE, },
/*ePMF*/    [bcmFieldActionContextId]                   = {DNX_FIELD_ACTION_FORWARD_CODE, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_forwarding_context},
/*ePMF*/    [bcmFieldActionEesEntry0]                   = {DNX_FIELD_ACTION_EES_ENTRY_29_0, },
/*ePMF*/    [bcmFieldActionEesEntry1]                   = {DNX_FIELD_ACTION_EES_ENTRY_59_30, },
/*ePMF*/    [bcmFieldActionEesEntry2]                   = {DNX_FIELD_ACTION_EES_ENTRY_89_60, },
/*ePMF*/    [bcmFieldActionEesEntry3]                   = {DNX_FIELD_ACTION_EES_ENTRY_119_90, },
/*ePMF*/    [bcmFieldActionEesEntry4]                   = {DNX_FIELD_ACTION_EES_ENTRY_TYPE, },
/*ePMF*/    [bcmFieldActionEesEntryLocationProfile]     = {DNX_FIELD_ACTION_EES_ENTRY_PUSH_PROFILE, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ees_location_profile},
/*ePMF*/    [bcmFieldActionEesEntryLocationProfileRaw]  = {DNX_FIELD_ACTION_EES_ENTRY_PUSH_PROFILE, },
/*ePMF*/    [bcmFieldActionOutVportToStamp]             = {DNX_FIELD_ACTION_OUTLIF_TO_STAMP},
/*ePMF*/    [bcmFieldActionUDHData0]                    = {DNX_FIELD_ACTION_USER_HEADER_1},
/*ePMF*/    [bcmFieldActionUDHData1]                    = {DNX_FIELD_ACTION_USER_HEADER_2},
/*ePMF*/    [bcmFieldActionUDHData2]                    = {DNX_FIELD_ACTION_USER_HEADER_3},
/*ePMF*/    [bcmFieldActionUDHData3]                    = {DNX_FIELD_ACTION_USER_HEADER_4},
/*ePMF*/    [bcmFieldActionUDHBase]                     = {DNX_FIELD_ACTION_USER_HEADERS_TYPE},
/*ePMF*/    [bcmFieldActionUDHData0Ext]                 = {DNX_FIELD_ACTION_USER_HEADER_1_EXT},
/*ePMF*/    [bcmFieldActionUDHData1Ext]                 = {DNX_FIELD_ACTION_USER_HEADER_2_EXT},
/*ePMF*/    [bcmFieldActionOamLmBasePtr]                = {DNX_FIELD_ACTION_ACE_STAT_LM_ENTRY},
/*ePMF*/    [bcmFieldActionStatOamLMRaw]                = {DNX_FIELD_ACTION_STAT_OBJ_LM_READ_INDEX, },
/*ePMF*/    [bcmFieldActionStatOamLM]                   = {DNX_FIELD_ACTION_STAT_OBJ_LM_READ_INDEX,BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_stat_lm_index},


};
static const dnx_field_action_map_t dnx_ace_action_map[bcmFieldActionCount] = {
/*ACE*/    [bcmFieldActionPrioIntNew]         = {DNX_FIELD_ACTION_TC,              },
/*ACE*/    [bcmFieldActionDropPrecedenceRaw]  = {DNX_FIELD_ACTION_DP, },
/*ACE*/    [bcmFieldActionDropPrecedence]     = {DNX_FIELD_ACTION_DP, BCM_TO_DNX_ADDITIONAL_OBJ ,dnx_field_convert_color},
/*ACE*/    [bcmFieldActionIPTProfile]         = {DNX_FIELD_ACTION_END_OF_PACKET_EDITING},
/*ACE*/    [bcmFieldActionInterfaceClassVPort]= {DNX_FIELD_ACTION_PPH_IN_LIF_PROFILE },
/*ACE*/    [bcmFieldActionTtlSet]             = {DNX_FIELD_ACTION_PPH_TTL},
/*ACE*/    [bcmFieldActionAceContextValueRaw] = {DNX_FIELD_ACTION_ACE_CONTEXT_VALUE, },
/*ACE*/    [bcmFieldActionAceContextValue]    = {DNX_FIELD_ACTION_ACE_CONTEXT_VALUE, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ace_context},
/*ACE*/    [bcmFieldActionEcnNew]             = {DNX_FIELD_ACTION_CNI},
/*ACE*/    [bcmFieldActionStat0Raw]           = {DNX_FIELD_ACTION_ACE_STAT_METER_OBJ_CMD_ID, },
/*ACE*/    [bcmFieldActionStat1Raw]           = {DNX_FIELD_ACTION_ACE_STAT_OBJ_CMD_ID_VALID, },
/*ACE*/    [bcmFieldActionStat0]              = {DNX_FIELD_ACTION_ACE_STAT_METER_OBJ_CMD_ID, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ace_stat_meter_object},
/*ACE*/    [bcmFieldActionStat1]              = {DNX_FIELD_ACTION_ACE_STAT_OBJ_CMD_ID_VALID, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_ace_stat_counter_object},
/*ACE*/    [bcmFieldActionLearnSrcPortNew]    = {DNX_FIELD_ACTION_SRC_SYS_PORT},
/*ACE*/    [bcmFieldActionInvalidNext]        = {DNX_FIELD_ACTION_INVALIDATE_NEXT},
/*ACE*/    [bcmFieldActionOutVport0Raw]       = {DNX_FIELD_ACTION_OUT_LIF0_CUD_OUT_LIF0VALID,},
/*ACE*/    [bcmFieldActionOutVport1Raw]       = {DNX_FIELD_ACTION_OUT_LIF1_CUD_OUT_LIF1VALID, },
/*ACE*/    [bcmFieldActionOutVport2Raw]       = {DNX_FIELD_ACTION_OUT_LIF2_CUD_OUT_LIF2VALID, },
/*ACE*/    [bcmFieldActionOutVport3Raw]       = {DNX_FIELD_ACTION_OUT_LIF3_CUD_OUT_LIF3VALID, },
/*ACE*/    [bcmFieldActionOutVport0]          = {DNX_FIELD_ACTION_OUT_LIF0_CUD_OUT_LIF0VALID, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif_add_valid},
/*ACE*/    [bcmFieldActionOutVport1]          = {DNX_FIELD_ACTION_OUT_LIF1_CUD_OUT_LIF1VALID, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif_add_valid},
/*ACE*/    [bcmFieldActionOutVport2]          = {DNX_FIELD_ACTION_OUT_LIF2_CUD_OUT_LIF2VALID, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif_add_valid},
/*ACE*/    [bcmFieldActionOutVport3]          = {DNX_FIELD_ACTION_OUT_LIF3_CUD_OUT_LIF3VALID, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_gport_to_global_out_lif_add_valid},
/*ACE*/    [bcmFieldActionOutInterface0]      = {DNX_FIELD_ACTION_OUT_LIF0_CUD_OUT_LIF0VALID, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif_add_valid},
/*ACE*/    [bcmFieldActionOutInterface1]      = {DNX_FIELD_ACTION_OUT_LIF1_CUD_OUT_LIF1VALID, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif_add_valid},
/*ACE*/    [bcmFieldActionOutInterface2]      = {DNX_FIELD_ACTION_OUT_LIF2_CUD_OUT_LIF2VALID, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif_add_valid},
/*ACE*/    [bcmFieldActionOutInterface3]      = {DNX_FIELD_ACTION_OUT_LIF3_CUD_OUT_LIF3VALID, BCM_TO_DNX_ADDITIONAL_OBJ, dnx_field_convert_rif_intf_to_lif_add_valid},
/*ACE*/    [bcmFieldActionForwardingAdditionalInfo]    = {DNX_FIELD_ACTION_FWD_LAYER_ADDITIONAL_INFO},
/*ACE*/    [bcmFieldActionForwardingLayerIndex]  = {DNX_FIELD_ACTION_FWD_LAYER_INDEX, },
/*ACE*/    [bcmFieldActionNetworkQos]            = {DNX_FIELD_ACTION_NWK_QOS, },
/*ACE*/    [bcmFieldActionDstClassField]         = {DNX_FIELD_ACTION_PPH_VALUE1, },
/*ACE*/    [bcmFieldActionSrcClassField]         = {DNX_FIELD_ACTION_PPH_VALUE2, },
/*ACE*/    [bcmFieldActionClassField]            = {DNX_FIELD_ACTION_FHEI_EXT31TO00, },
/*ACE*/    [bcmFieldActionVisibilityEnable]      = {DNX_FIELD_ACTION_VISIBILITY, },
};

const dnx_field_base_action_info_t dnx_sw_action_info[DNX_FIELD_SW_ACTION_NOF] = {
    [DNX_FIELD_SW_ACTION_VOID]                                  = {DBAL_FIELD_VOID, 32}
};

/*
 * End of action related data
 * }
 */

const dnx_field_map_stage_info_t dnx_field_map_stage_info[DNX_FIELD_STAGE_NOF] = {
    [DNX_FIELD_STAGE_IPMF1] = {
        .pp_stage                            = DNX_PP_STAGE_IPMF1,
        .bcm_stage                           = bcmFieldStageIngressPMF1,
        /** DNX to HW/DBAL mapping for context select quals */
        .cs_table_id                         = DBAL_TABLE_TCAM_CS_IPMF1,
        .cs_hit_indication_table_id          = DBAL_TABLE_KLEAP_IPMF1_TCAM_HIT_INDICATION,
        /** DNX to HW/DBAL mapping for actions */
        .action_field_id                     = DBAL_FIELD_IPMF1_ACTION,
        /** BCM to DNX maps for cs/quals/actions */
        .cs_qual_map                         = dnx_ipmf1_cs_qual_map,
        .meta_qual_map                       = dnx_ipmf1_meta_qual_map,
        .static_action_id_map                = dnx_ipmf1_action_map,
        /** KBR/FFC parameters per stage */
        .ffc_instruction                                 = DBAL_FIELD_IPMF1_FFC_INSTRUCTION,
        .ctx_id                                          = DBAL_FIELD_FIELD_PMF_CTX_ID,
        .key_field                                       = DBAL_FIELD_FIELD_KEY,
        .ffc_table                                       = DBAL_TABLE_KLEAP_IPMF1_FFC_INSTRUCTION,
        .ffc_type_field_a[DNX_FIELD_FFC_RELATIVE_HEADER] = DBAL_FIELD_IPMF1_FFC_RELATIVE_HEADER,
        .ffc_type_field_a[DNX_FIELD_FFC_ABSOLUTE_HEADER] = DBAL_FIELD_IPMF1_FFC_HEADER,
        .ffc_type_field_a[DNX_FIELD_FFC_LITERALLY]       = DBAL_FIELD_IPMF1_FFC_LITERALLY,
        .ffc_type_field_a[DNX_FIELD_FFC_LAYER_RECORD]    = DBAL_FIELD_IPMF1_FFC_LAYER_RECORD,
    },
    [DNX_FIELD_STAGE_IPMF2] = {
        .pp_stage                            = DNX_PP_STAGE_IPMF2,
        .bcm_stage                           = bcmFieldStageIngressPMF2,
        /** DNX to HW/DBAL mapping for context select quals */
        .cs_table_id                         = DBAL_TABLE_TCAM_CS_IPMF2,
        .cs_hit_indication_table_id          = DBAL_TABLE_KLEAP_IPMF2_TCAM_HIT_INDICATION,
        /** DNX to HW/DBAL mapping for actions */
        .action_field_id                     = DBAL_FIELD_IPMF1_ACTION,
        /** BCM to DNX maps for cs/quals/actions */
        .cs_qual_map                         = dnx_ipmf2_cs_qual_map,
        .meta_qual_map                       = dnx_ipmf2_meta_qual_map,
        .static_action_id_map                = dnx_ipmf1_action_map,
        /** KBR/FFC parameters per stage */
        .ffc_instruction                                 = DBAL_FIELD_IPMF2_FFC_INSTRUCTION,
        .ctx_id                                          = DBAL_FIELD_FIELD_PMF_CTX_ID,
        .key_field                                       = DBAL_FIELD_FIELD_KEY,
        .ffc_table                                       = DBAL_TABLE_KLEAP_IPMF2_FFC_INSTRUCTION,
        .ffc_type_field_a[DNX_FIELD_FFC_RELATIVE_HEADER] = DBAL_FIELD_EMPTY,
        .ffc_type_field_a[DNX_FIELD_FFC_ABSOLUTE_HEADER] = DBAL_FIELD_EMPTY,
        .ffc_type_field_a[DNX_FIELD_FFC_LITERALLY]       = DBAL_FIELD_IPMF2_FFC_LITERALLY,
        .ffc_type_field_a[DNX_FIELD_FFC_LAYER_RECORD]    = DBAL_FIELD_EMPTY,
    },
    [DNX_FIELD_STAGE_IPMF3] = {
        .pp_stage                            = DNX_PP_STAGE_IPMF3,
        .bcm_stage                           = bcmFieldStageIngressPMF3,
        /** DNX to HW/DBAL mapping for context select quals */
        .cs_table_id                         = DBAL_TABLE_TCAM_CS_IPMF3,
        .cs_hit_indication_table_id          = DBAL_TABLE_KLEAP_IPMF3_TCAM_HIT_INDICATION,
        /** DNX to HW/DBAL mapping for actions */
        .action_field_id                     = DBAL_FIELD_IPMF3_ACTION,
        /** BCM to DNX maps for cs/quals/actions */
        .cs_qual_map                         = dnx_ipmf3_cs_qual_map,
        .meta_qual_map                       = dnx_ipmf3_meta_qual_map,
        .static_action_id_map                = dnx_ipmf3_action_map,
        /** KBR/FFC parameters per stage */
        .ffc_instruction                                 = DBAL_FIELD_IPMF3_FFC_INSTRUCTION,
        .ctx_id                                          = DBAL_FIELD_FIELD_PMF_CTX_ID,
        .key_field                                       = DBAL_FIELD_FIELD_KEY,
        .ffc_table                                       = DBAL_TABLE_KLEAP_IPMF3_FFC_INSTRUCTION,
        .ffc_type_field_a[DNX_FIELD_FFC_RELATIVE_HEADER] = DBAL_FIELD_EMPTY,
        .ffc_type_field_a[DNX_FIELD_FFC_ABSOLUTE_HEADER] = DBAL_FIELD_EMPTY,
        .ffc_type_field_a[DNX_FIELD_FFC_LITERALLY]       = DBAL_FIELD_IPMF3_FFC_LITERALLY,
        .ffc_type_field_a[DNX_FIELD_FFC_LAYER_RECORD]    = DBAL_FIELD_IPMF3_FFC_LAYER_RECORD,
    },
    [DNX_FIELD_STAGE_EPMF]  = {
        .pp_stage                            = DNX_PP_STAGE_EPMF,
        .bcm_stage                           = bcmFieldStageEgress,
        /** DNX to HW/DBAL mapping for context select quals */
        .cs_table_id                         = DBAL_TABLE_TCAM_CS_EPMF,
        .cs_hit_indication_table_id          = DBAL_TABLE_KLEAP_EPMF_TCAM_HIT_INDICATION,
        /** DNX to HW/DBAL mapping for actions */
        .action_field_id                     = DBAL_FIELD_EPMF_ACTION,
        /** BCM to DNX maps for cs/quals/actions */
        .cs_qual_map                         = dnx_epmf_cs_qual_map,
        .meta_qual_map                       = dnx_epmf_meta_qual_map,
        .static_action_id_map                = dnx_epmf_action_map,
        /** KBR/FFC parameters per stage */
        .ffc_instruction                                 = DBAL_FIELD_EPMF_FFC_INSTRUCTION,
        .ctx_id                                          = DBAL_FIELD_FIELD_PMF_CTX_ID,
        .key_field                                       = DBAL_FIELD_FIELD_KEY,
        .ffc_table                                       = DBAL_TABLE_KLEAP_E_PMF_FFC_INSTRUCTION,
        .ffc_type_field_a[DNX_FIELD_FFC_RELATIVE_HEADER] = DBAL_FIELD_EPMF_FFC_RELATIVE_HEADER,
        .ffc_type_field_a[DNX_FIELD_FFC_ABSOLUTE_HEADER] = DBAL_FIELD_EPMF_FFC_HEADER,
        .ffc_type_field_a[DNX_FIELD_FFC_LITERALLY]       = DBAL_FIELD_EPMF_FFC_LITERALLY,
        .ffc_type_field_a[DNX_FIELD_FFC_LAYER_RECORD]    = DBAL_FIELD_EPMF_FFC_LAYER_RECORD,
    },
    [DNX_FIELD_STAGE_EXTERNAL] = {
        .pp_stage                            = DNX_PP_STAGE_IFWD2,
        .bcm_stage                           = bcmFieldStageExternal,
        /** DNX to HW/DBAL mapping for context select quals */
        .cs_table_id                         = DBAL_TABLE_FWD_ACL_CONTEXT_SELECTION,
        /** BCM to DNX maps for cs/quals/actions */
        .cs_qual_map                         = dnx_external_cs_qual_map,
        .meta_qual_map                       = dnx_external_meta_qual_map,
        /** KBR/FFC parameters per stage */
        .ffc_instruction                                 = DBAL_FIELD_FWD12_FFC_INSTRUCTION,
        .ctx_id                                          = DBAL_FIELD_CONTEXT_PROFILE,
        .key_field                                       = DBAL_FIELD_FWD12_KBR_ID,
        .ffc_table                                       = DBAL_TABLE_KLEAP_FWD12_FFC_INSTRUCTION,
        .ffc_type_field_a[DNX_FIELD_FFC_RELATIVE_HEADER] = DBAL_FIELD_FWD12_FFC_RELATIVE_HEADER,
        .ffc_type_field_a[DNX_FIELD_FFC_ABSOLUTE_HEADER] = DBAL_FIELD_FWD12_FFC_HEADER,
        .ffc_type_field_a[DNX_FIELD_FFC_LITERALLY]       = DBAL_FIELD_FWD12_FFC_LITERALLY,
        .ffc_type_field_a[DNX_FIELD_FFC_LAYER_RECORD]    = DBAL_FIELD_FWD12_FFC_LAYER_RECORD,
    },
    [DNX_FIELD_STAGE_ACE] = {
        .pp_stage                            = DNX_PP_STAGE_ACE,
        .bcm_stage                           = bcmFieldStageEgressExtension,
        /** DNX to HW/DBAL mapping for actions */
        .action_field_id                     = DBAL_FIELD_ACE_ACTION,
        /** BCM to DNX map for actions */
        .static_action_id_map                = dnx_ace_action_map,
    },
    [DNX_FIELD_STAGE_L4_OPS] = {
        /** DNX to HW/DBAL mapping for qualifiers */
        /** BCM to DNX maps for cs/quals/actions */
        .meta_qual_map                       = dnx_l4ops_meta_qual_map,
        /** KBR/FFC parameters per stage */
        .ffc_instruction                                 = DBAL_FIELD_L4OPS_FFC_INSTRUCTION,
        .ffc_table                                       = DBAL_TABLE_FIELD_IPMF1_L4_OPS_RANGES_FFC_CFG,
        .ffc_type_field_a[DNX_FIELD_FFC_RELATIVE_HEADER] = DBAL_FIELD_L4OPS_FFC_RELATIVE_HEADER,
        .ffc_type_field_a[DNX_FIELD_FFC_ABSOLUTE_HEADER] = DBAL_FIELD_L4OPS_FFC_HEADER,
        .ffc_type_field_a[DNX_FIELD_FFC_LITERALLY]       = DBAL_FIELD_L4OPS_FFC_LITERALLY,
        .ffc_type_field_a[DNX_FIELD_FFC_LAYER_RECORD]    = DBAL_FIELD_L4OPS_FFC_LAYER_RECORD,
    },
};

const dnx_field_static_apptype_map_t dnx_field_standard_1_static_apptype_map[bcmFieldAppTypeCount] = {
        [bcmFieldAppTypeL2]                       = { .opcode_id = DBAL_ENUM_FVAL_FORWARD_APP_TYPES_BRIDGE_SVL, },
        [bcmFieldAppTypeTrafficManagement]        = { .opcode_id = DBAL_ENUM_FVAL_FORWARD_APP_TYPES_NOP, },
        [bcmFieldAppTypeIp4UcastRpf]              = { .opcode_id = DBAL_ENUM_FVAL_FORWARD_APP_TYPES_IPV4_UNICAST_PRIVATE_W_UC_RPF, },
        [bcmFieldAppTypeIp6UcastRpf]              = { .opcode_id = DBAL_ENUM_FVAL_FORWARD_APP_TYPES_IPV6_UNICAST_PRIVATE_W_UC_RPF, },
        [bcmFieldAppTypeIp4McastRpf]              = { .opcode_id = DBAL_ENUM_FVAL_FORWARD_APP_TYPES_IPV4_MULTICAST_PRIVATE_W_UC_RPF, },
        [bcmFieldAppTypeIp6McastRpf]              = { .opcode_id = DBAL_ENUM_FVAL_FORWARD_APP_TYPES_IPV6_MULTICAST_PRIVATE_W_UC_RPF, },
        [bcmFieldAppTypeMpls]                     = { .opcode_id = DBAL_ENUM_FVAL_FORWARD_APP_TYPES_MPLS, },
        [bcmFieldAppTypeVip4]                     = { .opcode_id = DBAL_ENUM_FVAL_FORWARD_APP_TYPES_VIRTUAL_IPV4_PRIVATE_UC, },
        [bcmFieldAppTypeVip6]                     = { .opcode_id = DBAL_ENUM_FVAL_FORWARD_APP_TYPES_VIRTUAL_IPV6_PRIVATE_UC, },
        [bcmFieldAppTypeVip4Direct]               = { .opcode_id = DBAL_ENUM_FVAL_FORWARD_APP_TYPES_SIMPLE_IPV4_PRIVATE_UC, },
        [bcmFieldAppTypeVip6Direct]               = { .opcode_id = DBAL_ENUM_FVAL_FORWARD_APP_TYPES_SIMPLE_IPV6_PRIVATE_UC, },
        [bcmFieldAppTypeSrv6Endpoint]             = { .opcode_id = DBAL_ENUM_FVAL_FORWARD_APP_TYPES_SRV6_ENDPOINT_CLASSIC, },
        [bcmFieldAppTypeSrv6UsidEndpoint]         = { .opcode_id = DBAL_ENUM_FVAL_FORWARD_APP_TYPES_SRV6_ENDPOINT_USID, },
        [bcmFieldAppTypeSrv6GsidEndpoint]         = { .opcode_id = DBAL_ENUM_FVAL_FORWARD_APP_TYPES_SRV6_ENDPOINT_GSID, },
        [bcmFieldAppTypeSrv6UsidExtendedEndpoint] = { .opcode_id = DBAL_ENUM_FVAL_FORWARD_APP_TYPES_SRV6_ENDPOINT_USID_NO_DEFAULT, },
        [bcmFieldAppTypeL2VpnDirect]              = { .opcode_id = DBAL_ENUM_FVAL_FORWARD_APP_TYPES_ETHERNET_P2P, },
};

dnx_field_static_opcode_info_t dnx_field_static_opcode_info[DNX_FIELD_EXTERNAL_MAX_STATIC_OPCODES_NOF] = { { 0 } };

static const dnx_field_map_port_profile_info_t dnx_field_map_port_profile_info[bcmPortClassCount] = {
        /** Profiles for ports.*/
        [bcmPortClassFieldIngressPMF1PacketProcessingPort]    = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_PORT,
                .dbal_table_id = DBAL_TABLE_FIELD_PMF_PP_PORT_INFO_IPMF1, .dbal_key_field = DBAL_FIELD_PP_PORT,
                .dbal_result_field = DBAL_FIELD_IN_PORT_PMF_DATA,    },
        [bcmPortClassFieldIngressPMF3PacketProcessingPort]    = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_PORT,
                .dbal_table_id = DBAL_TABLE_FIELD_PMF_PP_PORT_INFO_IPMF3, .dbal_key_field = DBAL_FIELD_PP_PORT,
                .dbal_result_field = DBAL_FIELD_IN_PORT_PMF_DATA,    },
        [bcmPortClassFieldEgressPacketProcessingPort]        = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_PORT,
                .dbal_table_id = DBAL_TABLE_FIELD_PMF_PP_PORT_INFO_EPMF, .dbal_key_field = DBAL_FIELD_PP_PORT,
                .dbal_result_field = DBAL_FIELD_OUT_PP_PORT_PMF_DATA,},
        [bcmPortClassFieldIngressPMF1TrafficManagementPort]   = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_PORT,
                .dbal_table_id = DBAL_TABLE_FIELD_PMF_PTC_INFO_IPMF1, .dbal_key_field = DBAL_FIELD_PTC,
                .dbal_result_field = DBAL_FIELD_PTC_PMF_DATA,    },
        [bcmPortClassFieldIngressPMF3TrafficManagementPort]   = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_PORT,
                .dbal_table_id = DBAL_TABLE_FIELD_PMF_PTC_INFO_IPMF3, .dbal_key_field = DBAL_FIELD_PTC,
                .dbal_result_field = DBAL_FIELD_PTC_PMF_DATA,    },
        [bcmPortClassFieldEgressTrafficManagementPort]   = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_PORT,
                .dbal_table_id = DBAL_TABLE_FIELD_PMF_OUT_TM_PORT_INFO_EPMF, .dbal_key_field = DBAL_FIELD_OUT_TM_PORT,
                .dbal_result_field = DBAL_FIELD_OUT_TM_PORT_PMF_DATA,    },
        [bcmPortClassFieldIngressPMF1PacketProcessingPortCs]    = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_PORT,
                .dbal_table_id = DBAL_TABLE_FIELD_PMF_PP_PORT_INFO_IPMF1, .dbal_key_field = DBAL_FIELD_PP_PORT,
                .dbal_result_field = DBAL_FIELD_PP_PORT_CS_PROFILE,    },
        [bcmPortClassFieldIngressPMF3PacketProcessingPortCs]    = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_PORT,
                .dbal_table_id = DBAL_TABLE_FIELD_PMF_PP_PORT_INFO_IPMF3, .dbal_key_field = DBAL_FIELD_PP_PORT,
                .dbal_result_field = DBAL_FIELD_PP_PORT_CS_PROFILE,    },
        [bcmPortClassFieldEgressPacketProcessingPortCs]    = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_PORT,
                .dbal_table_id = DBAL_TABLE_FIELD_PMF_PP_PORT_INFO_EPMF, .dbal_key_field = DBAL_FIELD_PP_PORT,
                .dbal_result_field = DBAL_FIELD_OUT_PP_PORT_CS_PROFILE,    },
        [bcmPortClassFieldExternalPacketProcessingPortCs]    = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_PORT,
                .dbal_table_id = DBAL_TABLE_FIELD_PMF_PP_PORT_INFO_IFWD, .dbal_key_field = DBAL_FIELD_PP_PORT,
                .dbal_result_field = DBAL_FIELD_PP_PORT_CS_PROFILE,    },
        [bcmPortClassFieldIngressPMF1TrafficManagementPortCs]    = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_PORT,
                .dbal_table_id = DBAL_TABLE_FIELD_PMF_PTC_INFO_IPMF1, .dbal_key_field = DBAL_FIELD_PTC,
                .dbal_result_field = DBAL_FIELD_PTC_CS_PROFILE,    },
        [bcmPortClassFieldIngressPMF3TrafficManagementPortCs]    = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_PORT,
                .dbal_table_id = DBAL_TABLE_FIELD_PMF_PTC_INFO_IPMF3, .dbal_key_field = DBAL_FIELD_PTC,
                .dbal_result_field = DBAL_FIELD_PTC_CS_PROFILE,    },
        [bcmPortClassFieldExternalTrafficManagementPortCs]    = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_PORT,
                .dbal_table_id = DBAL_TABLE_FIELD_PMF_PTC_INFO_IFWD, .dbal_key_field = DBAL_FIELD_PTC,
                .dbal_result_field = DBAL_FIELD_PTC_CS_PROFILE,    },
        [bcmPortClassFieldIngressPMF1PacketProcessingPortGeneralData]    = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_PORT_GENERAL_DATA,
                .dbal_table_id = DBAL_TABLE_FIELD_PMF_PP_PORT_INFO_IPMF1, .dbal_key_field = DBAL_FIELD_PP_PORT,
                .dbal_result_field = DBAL_FIELD_IN_PORT_PMF_DATA,    },
        [bcmPortClassFieldIngressPMF1PacketProcessingPortGeneralDataHigh]    = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_PORT_GENERAL_DATA_HIGH,
                .dbal_table_id = DBAL_TABLE_FIELD_PMF_PP_PORT_INFO_IPMF1, .dbal_key_field = DBAL_FIELD_PP_PORT,
                .dbal_result_field = DBAL_FIELD_IN_PORT_PMF_DATA,    },
        [bcmPortClassFieldIngressPMF3PacketProcessingPortGeneralData]    = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_PORT_GENERAL_DATA,
                .dbal_table_id = DBAL_TABLE_FIELD_PMF_PP_PORT_INFO_IPMF3, .dbal_key_field = DBAL_FIELD_PP_PORT,
                .dbal_result_field = DBAL_FIELD_IN_PORT_PMF_DATA,    },
        [bcmPortClassFieldIngressPMF3PacketProcessingPortGeneralDataHigh]    = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_PORT_GENERAL_DATA_HIGH,
                .dbal_table_id = DBAL_TABLE_FIELD_PMF_PP_PORT_INFO_IPMF3, .dbal_key_field = DBAL_FIELD_PP_PORT,
                .dbal_result_field = DBAL_FIELD_IN_PORT_PMF_DATA,    },

        /** Profiles for LIF/RIF.*/
        [bcmPortClassFieldIngressVport]    = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_IN_LIF_INGRESS, },
        [bcmPortClassFieldEgressVport]    = {
                .port_profile_type = DNX_FIELD_PORT_PROFILE_TYPE_OUT_ETH_RIF_EGRESS, },
};

/**see H file: field_map_local.h */
shr_error_e
dnx_field_map_port_profile_type_get(
    int unit,
    bcm_port_class_t bcm_port_class,
    dnx_field_port_porfile_type_e * port_profile_type_p)
{
    SHR_FUNC_INIT_VARS(unit);

    DNX_FIELD_NCM_PORT_CLASS_VERIFY(bcm_port_class);

    (*port_profile_type_p) = dnx_field_map_port_profile_info[bcm_port_class].port_profile_type;
    if((*port_profile_type_p) == DNX_FIELD_PORT_PROFILE_TYPE_INVALID)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "BCM port class:%d is unsupported for field map.\n", bcm_port_class);
    }

exit:
    SHR_FUNC_EXIT;
}

/**see H file: field_map_local.h */
shr_error_e
dnx_field_map_port_profile_info_get(
    int unit,
    bcm_port_class_t bcm_port_class,
    dnx_field_map_port_profile_info_t * port_profile_info_p)
{
    SHR_FUNC_INIT_VARS(unit);

    DNX_FIELD_NCM_PORT_CLASS_VERIFY(bcm_port_class);

    sal_memcpy(port_profile_info_p, &dnx_field_map_port_profile_info[bcm_port_class], sizeof(*port_profile_info_p));
    if(port_profile_info_p->port_profile_type == DNX_FIELD_PORT_PROFILE_TYPE_INVALID)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "BCM port class:%d is unsupported for field map.\n", bcm_port_class);
    }
exit:
    SHR_FUNC_EXIT;
}

/**See header of dnx_field_map_static_opcode_to_apptype_get in field_map.h */
shr_error_e
dnx_field_map_static_opcode_to_apptype_get(
    int unit,
    uint32 static_opcode_id,
    bcm_field_AppType_t * apptype_p)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(apptype_p, _SHR_E_PARAM, "apptype_p");

    if (static_opcode_id >= (sizeof(dnx_field_static_opcode_info) / sizeof(dnx_field_static_opcode_info[0])))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Opcode %d is out of range for predefined opcodes (0-%d)\n",
                     static_opcode_id,
                     ((int)(sizeof(dnx_field_static_opcode_info) / sizeof(dnx_field_static_opcode_info[0]))) - 1);
    }

    if (dnx_field_static_opcode_info[static_opcode_id].is_valid == 0)
    {
        SHR_SET_CURRENT_ERR(_SHR_E_NOT_FOUND);
        SHR_EXIT();
    }

    (*apptype_p) = dnx_field_static_opcode_info[static_opcode_id].app_type;

exit:
    SHR_FUNC_EXIT;
}

/**See header of dnx_field_map_static_opcode_to_cs_profile_get in field_map.h */
shr_error_e
dnx_field_map_static_opcode_to_cs_profile_get(
    int unit,
    uint32 static_opcode_id,
    uint32 * cs_profile_p)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(cs_profile_p, _SHR_E_PARAM, "cs_profile_p");

    if (static_opcode_id >= (sizeof(dnx_field_static_opcode_info) / sizeof(dnx_field_static_opcode_info[0])))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Opcode %d is out of range for predefined opcodes (0-%d)\n",
                     static_opcode_id,
                     ((int)(sizeof(dnx_field_static_opcode_info) / sizeof(dnx_field_static_opcode_info[0]))) - 1);
    }

    if (dnx_field_static_opcode_info[static_opcode_id].is_valid == 0)
    {
        SHR_SET_CURRENT_ERR(_SHR_E_NOT_FOUND);
        SHR_EXIT();
    }

    (*cs_profile_p) = dnx_field_static_opcode_info[static_opcode_id].cs_profile_id;

exit:
    SHR_FUNC_EXIT;
}

/**See header of dnx_field_map_standard_1_predefined_apptype_to_opcode_get in field_map.h */
shr_error_e
dnx_field_map_standard_1_predefined_apptype_to_opcode_get(
    int unit,
    bcm_field_AppType_t apptype,
    uint32 * static_opcode_id_p)
{
    uint32 opcode_id;
    SHR_FUNC_INIT_VARS(unit);
    SHR_NULL_CHECK(static_opcode_id_p, _SHR_E_PARAM, "static_opcode_id_p");

    if ((apptype >=
         (sizeof(dnx_field_standard_1_static_apptype_map) / sizeof(dnx_field_standard_1_static_apptype_map[0])))
        || (((int) apptype) < 0))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Apptype %d is out of range for predefined apptype. Range is %d-%d.\n",
                     apptype, 0,
                     ((int)(sizeof(dnx_field_standard_1_static_apptype_map) /
                            sizeof(dnx_field_standard_1_static_apptype_map[0]))) - 1);
    }
    opcode_id = dnx_field_standard_1_static_apptype_map[apptype].opcode_id;

    if (opcode_id == DBAL_ENUM_FVAL_FORWARD_APP_TYPES_INVALID)
    {
        SHR_SET_CURRENT_ERR(_SHR_E_NOT_FOUND);
        SHR_EXIT();
    }

    (*static_opcode_id_p) = opcode_id;

exit:
    SHR_FUNC_EXIT;
}

/* *INDENT-ON* */


/*
 *         
 * 
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *     
 * DO NOT EDIT THIS FILE!
 *
 */

#include <bcm/port.h>
#include <bcm_int/dnx/port/imb/imb_common.h>
#include <bcm_int/dnx/port/imb/imb_internal.h>
#include <soc/portmod/portmod.h>
#include <soc/dnx/swstate/auto_generated/access/dnx_port_imb_access.h>
#include <soc/dnx/swstate/auto_generated/types/dnx_port_imb_types.h>
#include <soc/sand/shrextend/shrextend_debug.h>
#include <bcm_int/dnx/port/imb/imb.h>
#include <bcm_int/dnx/port/imb/imb_dispatch.h>

const enum_mapping_t imb_dispatch_type_t_mapping[] = {
    {"None", imbDispatchTypeNone},
#ifdef BCM_DNX2_SUPPORT
    {"Imb_cdu", imbDispatchTypeImb_cdu},
#endif /* BCM_DNX2_SUPPORT */
#ifdef BCM_DNX2_SUPPORT
    {"Imb_clu", imbDispatchTypeImb_clu},
#endif /* BCM_DNX2_SUPPORT */
#ifdef BCM_DNX2_SUPPORT
    {"Imb_ile", imbDispatchTypeImb_ile},
#endif /* BCM_DNX2_SUPPORT */
#ifdef BCM_DNX2_SUPPORT
    {"Imb_ilu", imbDispatchTypeImb_ilu},
#endif /* BCM_DNX2_SUPPORT */
#ifdef BCM_DNX2_SUPPORT
    {"Imb_feu_phy", imbDispatchTypeImb_feu_phy},
#endif /* BCM_DNX2_SUPPORT */
    {"Imb_fabric", imbDispatchTypeImb_fabric},
#ifdef BCM_DNX2_SUPPORT
    {"Imb_cdu_shr", imbDispatchTypeImb_cdu_shr},
#endif /* BCM_DNX2_SUPPORT */
#ifdef BCM_DNX2_SUPPORT
    {"Imb_framer", imbDispatchTypeImb_framer},
#endif /* BCM_DNX2_SUPPORT */
#ifdef BCM_DNX2_SUPPORT
    {"Imb_otnu_phy", imbDispatchTypeImb_otnu_phy},
#endif /* BCM_DNX2_SUPPORT */
    {NULL, 0}
};

const enum_mapping_t imb_prd_properties_t_mapping[] = {
    {"IgnoreIpDscp", imbImbPrdIgnoreIpDscp},
    {"IgnoreMplsExp", imbImbPrdIgnoreMplsExp},
    {"IgnoreInnerTag", imbImbPrdIgnoreInnerTag},
    {"IgnoreOuterTag", imbImbPrdIgnoreOuterTag},
    {"DefaultPriority", imbImbPrdDefaultPriority},
    {NULL, 0}
};

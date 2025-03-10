
/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifndef _DNX_DATA_MAX_L2_H_

#define _DNX_DATA_MAX_L2_H_




#ifndef BCM_DNX_SUPPORT
#error "This file is for use by DNX (JR2) family only!"
#endif


#define DNX_DATA_MAX_L2_GENERAL_VSI_OFFSET_SHIFT (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_GENERAL_VSI_OFFSET_SHIFT
#define DNX_DATA_MAX_L2_GENERAL_VSI_OFFSET_SHIFT (70)

#endif 

#define DNX_DATA_MAX_L2_GENERAL_LIF_OFFSET_SHIFT (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_GENERAL_LIF_OFFSET_SHIFT
#define DNX_DATA_MAX_L2_GENERAL_LIF_OFFSET_SHIFT (-74)

#endif 


#define DNX_DATA_MAX_L2_GENERAL_LEM_NOF_DBS (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_GENERAL_LEM_NOF_DBS

#define DNX_DATA_MAX_L2_GENERAL_LEM_NOF_DBS (1)

#endif 


#define DNX_DATA_MAX_L2_VSI_NOF_VSI_AGING_PROFILES (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_VSI_NOF_VSI_AGING_PROFILES

#define DNX_DATA_MAX_L2_VSI_NOF_VSI_AGING_PROFILES (32)

#endif 


#define DNX_DATA_MAX_L2_VSI_NOF_EVENT_FORWARDING_PROFILES (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_VSI_NOF_EVENT_FORWARDING_PROFILES

#define DNX_DATA_MAX_L2_VSI_NOF_EVENT_FORWARDING_PROFILES (4)

#endif 


#define DNX_DATA_MAX_L2_VSI_NOF_VSI_LEARNING_PROFILES (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_VSI_NOF_VSI_LEARNING_PROFILES

#define DNX_DATA_MAX_L2_VSI_NOF_VSI_LEARNING_PROFILES (32)

#endif 


#define DNX_DATA_MAX_L2_VLAN_DOMAIN_NOF_VLAN_DOMAINS (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_VLAN_DOMAIN_NOF_VLAN_DOMAINS

#define DNX_DATA_MAX_L2_VLAN_DOMAIN_NOF_VLAN_DOMAINS (2048)

#endif 


#define DNX_DATA_MAX_L2_VLAN_DOMAIN_NOF_BITS_NEXT_LAYER_NETWORK_DOMAIN (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_VLAN_DOMAIN_NOF_BITS_NEXT_LAYER_NETWORK_DOMAIN

#define DNX_DATA_MAX_L2_VLAN_DOMAIN_NOF_BITS_NEXT_LAYER_NETWORK_DOMAIN (11)

#endif 


#define DNX_DATA_MAX_L2_DMA_FLUSH_NOF_DMA_ENTRIES (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_DMA_FLUSH_NOF_DMA_ENTRIES

#define DNX_DATA_MAX_L2_DMA_FLUSH_NOF_DMA_ENTRIES (128)

#endif 


#define DNX_DATA_MAX_L2_DMA_FLUSH_DB_NOF_DMA_RULES (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_DMA_FLUSH_DB_NOF_DMA_RULES

#define DNX_DATA_MAX_L2_DMA_FLUSH_DB_NOF_DMA_RULES (16)

#endif 


#define DNX_DATA_MAX_L2_DMA_FLUSH_DB_NOF_DMA_RULES_PER_TABLE (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_DMA_FLUSH_DB_NOF_DMA_RULES_PER_TABLE

#define DNX_DATA_MAX_L2_DMA_FLUSH_DB_NOF_DMA_RULES_PER_TABLE (8)

#endif 


#define DNX_DATA_MAX_L2_DMA_FLUSH_DB_RULE_SIZE (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_DMA_FLUSH_DB_RULE_SIZE

#define DNX_DATA_MAX_L2_DMA_FLUSH_DB_RULE_SIZE (67)

#endif 


#define DNX_DATA_MAX_L2_DMA_FLUSH_DB_DATA_SIZE (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_DMA_FLUSH_DB_DATA_SIZE

#define DNX_DATA_MAX_L2_DMA_FLUSH_DB_DATA_SIZE (25)

#endif 


#define DNX_DATA_MAX_L2_DMA_FLUSH_GROUP_SIZE (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_DMA_FLUSH_GROUP_SIZE

#define DNX_DATA_MAX_L2_DMA_FLUSH_GROUP_SIZE (4)

#endif 


#define DNX_DATA_MAX_L2_AGE_AND_FLUSH_MACHINE_MAX_AGE_STATES (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_AGE_AND_FLUSH_MACHINE_MAX_AGE_STATES

#define DNX_DATA_MAX_L2_AGE_AND_FLUSH_MACHINE_MAX_AGE_STATES (8)

#endif 


#define DNX_DATA_MAX_L2_OLP_LPKGV_SHIFT (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_OLP_LPKGV_SHIFT

#define DNX_DATA_MAX_L2_OLP_LPKGV_SHIFT (26)

#endif 


#define DNX_DATA_MAX_L2_OLP_LPKGV_MASK  (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_OLP_LPKGV_MASK

#define DNX_DATA_MAX_L2_OLP_LPKGV_MASK  (63)

#endif 


#define DNX_DATA_MAX_L2_OLP_LPKGV_WITH_OUTLIF (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_OLP_LPKGV_WITH_OUTLIF

#define DNX_DATA_MAX_L2_OLP_LPKGV_WITH_OUTLIF (32)

#endif 


#define DNX_DATA_MAX_L2_OLP_LPKGV_WO_OUTLIF (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_OLP_LPKGV_WO_OUTLIF

#define DNX_DATA_MAX_L2_OLP_LPKGV_WO_OUTLIF (48)

#endif 


#define DNX_DATA_MAX_L2_OLP_DESTINATION_OFFSET (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_OLP_DESTINATION_OFFSET

#define DNX_DATA_MAX_L2_OLP_DESTINATION_OFFSET (37)

#endif 


#define DNX_DATA_MAX_L2_OLP_OUTLIF_OFFSET (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_OLP_OUTLIF_OFFSET

#define DNX_DATA_MAX_L2_OLP_OUTLIF_OFFSET (8)

#endif 


#define DNX_DATA_MAX_L2_OLP_EEI_OFFSET  (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_OLP_EEI_OFFSET

#define DNX_DATA_MAX_L2_OLP_EEI_OFFSET  (6)

#endif 


#define DNX_DATA_MAX_L2_OLP_FEC_OFFSET  (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_OLP_FEC_OFFSET

#define DNX_DATA_MAX_L2_OLP_FEC_OFFSET  (37)

#endif 


#define DNX_DATA_MAX_L2_OLP_JR_MODE_ENHANCED_PERFORMANCE_ENABLE (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_L2_OLP_JR_MODE_ENHANCED_PERFORMANCE_ENABLE

#define DNX_DATA_MAX_L2_OLP_JR_MODE_ENHANCED_PERFORMANCE_ENABLE (1)

#endif 


#define DNX_DATA_MAX_L2_OLP_OLP_LEARNING_BLOCK_ID (1)




#endif 



/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifndef _DNX_DATA_MAX_SPB_H_

#define _DNX_DATA_MAX_SPB_H_




#ifndef BCM_DNX_SUPPORT
#error "This file is for use by DNX (JR2) family only!"
#endif



#define DNX_DATA_MAX_SPB_OCB_NOF_BLOCKS (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_SPB_OCB_NOF_BLOCKS

#define DNX_DATA_MAX_SPB_OCB_NOF_BLOCKS (8)

#endif 

#define DNX_DATA_MAX_SPB_OCB_NOF_RINGS  (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_SPB_OCB_NOF_RINGS
#define DNX_DATA_MAX_SPB_OCB_NOF_RINGS  (2)

#endif 

#define DNX_DATA_MAX_SPB_OCB_NOF_BANKS_PER_RING (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_SPB_OCB_NOF_BANKS_PER_RING
#define DNX_DATA_MAX_SPB_OCB_NOF_BANKS_PER_RING (16)

#endif 

#define DNX_DATA_MAX_SPB_OCB_NOF_PTRS_PER_BANK (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_SPB_OCB_NOF_PTRS_PER_BANK
#define DNX_DATA_MAX_SPB_OCB_NOF_PTRS_PER_BANK (4096)

#endif 

#define DNX_DATA_MAX_SPB_OCB_OTP_DEFECTIVE_BANK_NOF_BITS (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_SPB_OCB_OTP_DEFECTIVE_BANK_NOF_BITS
#define DNX_DATA_MAX_SPB_OCB_OTP_DEFECTIVE_BANK_NOF_BITS (4)

#endif 

#define DNX_DATA_MAX_SPB_OCB_OTP_IS_ANY_BANK_DEFECTIVE_NOF_BITS (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_SPB_OCB_OTP_IS_ANY_BANK_DEFECTIVE_NOF_BITS
#define DNX_DATA_MAX_SPB_OCB_OTP_IS_ANY_BANK_DEFECTIVE_NOF_BITS (1)

#endif 

#define DNX_DATA_MAX_SPB_OCB_NOF_LOGICAL_BANKS (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_SPB_OCB_NOF_LOGICAL_BANKS
#define DNX_DATA_MAX_SPB_OCB_NOF_LOGICAL_BANKS (32)

#endif 

#define DNX_DATA_MAX_SPB_OCB_BANK_FULL_TH_FOR_CFG (1)

#define DNX_DATA_MAX_SPB_OCB_BUFFER_PTR_NOF_BITS (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_SPB_OCB_BUFFER_PTR_NOF_BITS
#define DNX_DATA_MAX_SPB_OCB_BUFFER_PTR_NOF_BITS (12)

#endif 




#endif 



/* *INDENT-OFF* */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifndef _DNX_DATA_MAX_PTP_H_

#define _DNX_DATA_MAX_PTP_H_




#ifndef BCM_DNX_SUPPORT
#error "This file is for use by DNX (JR2) family only!"
#endif



#define DNX_DATA_MAX_PTP_GENERAL_NOF_PORT_PROFILES (1)
#ifdef BCM_DNX2_SUPPORT

#undef DNX_DATA_MAX_PTP_GENERAL_NOF_PORT_PROFILES

#define DNX_DATA_MAX_PTP_GENERAL_NOF_PORT_PROFILES (4)

#endif 




#endif 


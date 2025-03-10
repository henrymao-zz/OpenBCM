/*
 * 
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * KNETSync Management
 */

#include <bcm/knet.h>
#include <bcm/error.h>
#include <bcm_int/common/knetsync.h>
#include <shared/bsl.h>

/*
 * Function:
 *      bcm_esw_knetsync_init
 * Purpose:
 *      Initialize the KNETSync subsystem and Firmware.
 * Parameters:
 *      unit - (IN) Unit number.
 * Returns:
 *      BCM_E_xxx
 * Notes:
 */
int 
bcm_esw_knetsync_init(int unit)
{
#ifndef INCLUDE_KNET
    return BCM_E_UNAVAIL;
#else
    int rv;
    _bcm_knetsync_info_t knetsync_info;

    sal_memset(&knetsync_info, 0, sizeof(knetsync_info));

    rv = bcm_common_knetsync_init(unit, knetsync_info);
    return BCM_SUCCESS(rv) ? BCM_E_NONE : rv; 
#endif
}

/*
 * Function:
 *      bcm_esw_knetsync_deinit
 * Purpose:
 *      Deinitialize the knetsync networking subsystem and firmware.
 * Parameters:
 *      unit - (IN) Unit number.
 * Returns:
 *      BCM_E_xxx
 * Notes:
 */
int 
bcm_esw_knetsync_deinit(int unit)
{
#ifndef INCLUDE_KNET
    return BCM_E_UNAVAIL;
#else
    int rv;
    rv = bcm_common_knetsync_deinit(unit);

    return BCM_SUCCESS(rv) ? BCM_E_NONE : rv; 
#endif
}

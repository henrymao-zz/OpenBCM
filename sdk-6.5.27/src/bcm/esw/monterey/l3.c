/*
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * File:    l3.c
 * Purpose: Monterey L3 function implementations
 */

#include <shared/bsl.h>

#include <soc/defs.h>
#if defined(INCLUDE_L3) && defined(BCM_MONTEREY_SUPPORT)

#include <bcm/debug.h>
#include <bcm/error.h>
/*
 * Function:
 *      _bcm_monterey_ecmp_rh_dynamic_size_encode
 * Purpose:
 *      Encode ECMP resilient hashing flow set size.
 * Parameters:
 *      dynamic_size - (IN) Number of flow sets.
 *      encoded_value - (OUT) Encoded value.
 * Returns:
 *      BCM_E_xxx
 */
int
_bcm_monterey_ecmp_rh_dynamic_size_encode(int dynamic_size, int *encoded_value)
{
    switch (dynamic_size) {
        case 8:
            *encoded_value = 1;
            break;
        case 16:
            *encoded_value = 2;
            break;
        case 32:
            *encoded_value = 3;
            break;
        case 64:
            *encoded_value = 4;
            break;
        case 128:
            *encoded_value = 5;
            break;
        case 256:
            *encoded_value = 6;
            break;
        case 512:
            *encoded_value = 7;
            break;
        case 1024:
            *encoded_value = 8;
            break;
        default:
            return BCM_E_PARAM;
    }

    return BCM_E_NONE;
}

/*
 * Function:
 *      _bcm_monterey_ecmp_rh_dynamic_size_decode
 * Purpose:
 *      Decode ECMP resilient hashing flow set size.
 * Parameters:
 *      encoded_value - (IN) Encoded value.
 *      dynamic_size - (OUT) Number of flow sets.
 * Returns:
 *      BCM_E_xxx
 */
int
_bcm_monterey_ecmp_rh_dynamic_size_decode(int encoded_value, int *dynamic_size)
{
    switch (encoded_value) {
        case 1:
            *dynamic_size = 8;
            break;
        case 2:
            *dynamic_size = 16;
            break;
        case 3:
            *dynamic_size = 32;
            break;
        case 4:
            *dynamic_size = 64;
            break;
        case 5:
            *dynamic_size = 128;
            break;
        case 6:
            *dynamic_size = 256;
            break;
        case 7:
            *dynamic_size = 512;
            break;
        case 8:
            *dynamic_size = 1024;
            break;
        default:
            return BCM_E_INTERNAL;
    }

    return BCM_E_NONE;
}

#endif /* INCLUDE_L3 && BCM_MONTEREY_SUPPORT  */

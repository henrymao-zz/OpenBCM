/*
 * 
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 * Test for verifying KBP sdk ver compatibility with the SW sdk ver
 */

#include <soc/defs.h>
#if (defined(BCM_88675_A0) || defined(BCM_DNX_SUPPORT)) && defined(INCLUDE_KBP) && !defined(BCM_88030)

#if defined(BCM_88675_A0) && defined(INCLUDE_KBP) && !defined(BCM_88030)
#include <soc/dpp/ARAD/arad_kbp.h>
#endif

#if defined(BCM_88675_A0)
#include <soc/dpp/JER/JER_PP/jer_pp_kaps.h>
#include <soc/dpp/JER/JER_PP/jer_pp_kaps_diag.h>
#endif

#if defined(BCM_DNX_SUPPORT) && defined(INCLUDE_KBP)
#include "../diag/dnx/kbp/diag_dnx_kbp.h"
#endif

#include <sal/types.h>
#include <appl/diag/test.h>

int
kbp_sdk_ver_test(int u, args_t *a, void *p)
{
    int rv = 0;

#if defined(BCM_88675_A0) && defined(INCLUDE_KBP) && !defined(BCM_88030)
    rv = jer_pp_kbp_sdk_ver_test(u);
#endif
#if defined(BCM_DNX_SUPPORT)
    rv = dnx_kbp_diag_sdk_ver_cmd(u, a, p);
#endif

    if (rv != 0)
    {
        test_error(u, "KBP SDK version test failed!!!\n");
        return rv;
    }

    return rv;
}

#endif


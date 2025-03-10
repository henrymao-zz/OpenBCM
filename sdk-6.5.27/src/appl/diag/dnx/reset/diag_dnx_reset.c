/** \file diag_dnx_reset.c
 *
 * Diagnostics device reset.
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_PORT

/*************
 * INCLUDES  *
 *************/
/*shared*/
#include <shared/bsl.h>
/*appl*/
#include <appl/diag/sand/diag_sand_framework.h>
#include <appl/diag/cmdlist.h>

/*soc*/
/** allow drv.h include excplictly */
#ifdef _SOC_DRV_H
#undef _SOC_DRV_H
#endif
#include <soc/dnx/drv.h>

/*************
 *  DEFINES  *
 *************/

/*************
 *  MACROES  *
 *************/

/*************
 * FUNCTIONS *
 *************/

shr_error_e
sh_dnx_reset_cmd(
    int unit,
    args_t * args,
    sh_sand_control_t * sand_control)
{
    int soft_reset, access_only, soft_reset_no_fabric, duration;
    int without_fabric, without_ile;
    sal_usecs_t t1 = 0, t2 = 0;

    SHR_FUNC_INIT_VARS(unit);

    SH_SAND_GET_BOOL("soft", soft_reset);
    SH_SAND_GET_BOOL("soft_NoFabric", soft_reset_no_fabric);
    SH_SAND_GET_BOOL("ACCessOnly", access_only);
    SH_SAND_GET_INT32("NoFabric", without_fabric);
    SH_SAND_GET_INT32("NoElk", without_ile);
    SH_SAND_GET_BOOL("DURation", duration);

    if (duration)
    {
        t1 = sal_time_usecs();
    }
    if (soft_reset)
    {
        /*
         * Currently, we only support 3 combinations slow soft reest ==> NoFabric=0 & NoElk=0; soft reest ==>
         * NoFabric=1 & NoElk=0; fast soft reset ==> NoFabric=1 & NoElk=1; 
         */
        /*
         * slow soft reset 
         */
        if (without_fabric == 0 && without_ile == 0)
        {
            SHR_IF_ERR_EXIT(soc_dnx_device_reset(unit, SOC_DNX_RESET_MODE_BLOCKS_AND_FABRIC_SOFT_RESET, 0, 0));
        }
        else if (without_fabric == 1 && without_ile == 0)
        {
            SHR_IF_ERR_EXIT(soc_dnx_device_reset(unit, SOC_DNX_RESET_MODE_BLOCKS_SOFT_RESET, 0, 0));
        }
        else if (without_fabric == 1 && without_ile == 1)
        {
            SHR_IF_ERR_EXIT(soc_dnx_device_reset(unit, SOC_DNX_RESET_MODE_BLOCKS_SOFT_RESET,
                                                 SOC_DNX_RESET_MODE_FLAG_WITHOUT_ILE, 0));
        }
        else if (without_fabric == 0 && without_ile == 1)
        {
            SHR_IF_ERR_EXIT(soc_dnx_device_reset(unit, SOC_DNX_RESET_MODE_BLOCKS_AND_FABRIC_SOFT_RESET,
                                                 SOC_DNX_RESET_MODE_FLAG_WITHOUT_ILE, 0));
        }
    }
    else if (soft_reset_no_fabric)
    {
        SHR_IF_ERR_EXIT(soc_dnx_device_reset(unit, SOC_DNX_RESET_MODE_BLOCKS_SOFT_RESET, 0, 0));
    }
    else if (access_only)
    {
        SHR_IF_ERR_EXIT(soc_dnx_device_reset(unit, SOC_DNX_RESET_MODE_REG_ACCESS, 0, 0));
    }
    else if (ARG_CUR(args))
    {
        int rv;

        /** invoke legacy command */
        rv = sh_device_reset(unit, args);
        if (rv != CMD_OK)
        {
            SHR_CLI_EXIT(_SHR_E_FAIL, "Legacy DeviceReset command failed\n");
        }
    }

    if (duration)
    {
        t2 = sal_time_usecs();
        cli_out("The duration of reset is: %d\n", t2 - t1);
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * List of the supported commands, pointer to command function and command usage function.
 */

sh_sand_man_t sh_dnx_reset_man = {
    .brief = "Reset device",
    .full = "Reset device according to provided mode (soft, Accessonly, etc..).\n"
        "This command also supports legacy der command calls",
    .examples = "Soft\n" "Soft NoFabric=1\n" "Soft NoFabric=1 NoElk=1 DURation",
};

sh_sand_option_t sh_dnx_reset_options[] = {
/* *INDENT-OFF* */
    {"SoFT",          SAL_FIELD_TYPE_BOOL,  "Perform Soft reset",                "No", NULL},
    {"SoFT_NoFabric", SAL_FIELD_TYPE_BOOL,  "Perform Soft reset without Fabric", "No", NULL, NULL, SH_SAND_ARG_QUIET},
    {"ACCessOnly",    SAL_FIELD_TYPE_BOOL,  "Init in Access-only mode",          "No", NULL, NULL, SH_SAND_ARG_QUIET},
    {"mode",          SAL_FIELD_TYPE_INT32, "Legacy command mode",               "0",  NULL, NULL, SH_SAND_ARG_FREE | SH_SAND_ARG_QUIET},
    {"action",        SAL_FIELD_TYPE_INT32, "Legacy command action",             "0",  NULL, NULL, SH_SAND_ARG_FREE | SH_SAND_ARG_QUIET},
    {"NoFabric",      SAL_FIELD_TYPE_INT32, "Perform Soft reset exclude fabric", "0",  NULL, "0-1"},
    {"NoElk",         SAL_FIELD_TYPE_INT32, "Perform Soft reset excluding elk and FEC used by ILKN PORTs (both ELK and data)", "0", NULL, "0-1"},
    {"DURation",      SAL_FIELD_TYPE_BOOL,  "Export the duration of the reset",  "No", NULL},
    {NULL}
/* *INDENT-ON* */
};

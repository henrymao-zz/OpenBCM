/** \file dnxc/swstate/auto_generated/diagnostic/swstate_commandline.c
 *
 * sw state functions definitions
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 *
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_SWSTATEDNX_GENERAL

#include "swstate_commandline.h"
#include <appl/diag/dnxc/swstate/diagnostic_config.h>
#include <appl/diag/dnxc/swstate/diag_dnxc_sw_state_logging.h>
#include <appl/diag/sand/diag_sand_framework.h>
#include <appl/diag/sand/diag_sand_utils.h>
#include <soc/dnxc/swstate/dnx_sw_state_dump.h>
#include "adapter_commandline.h"
#include "multithread_analyzer_commandline.h"
#include "sw_state_external_commandline.h"
#if defined(BCM_DNX_SUPPORT) || defined(BCM_DNXF_SUPPORT)
#include "wb_engine_commandline.h"
#endif /* defined(BCM_DNX_SUPPORT) || defined(BCM_DNXF_SUPPORT)*/ 
#if defined(DNX_SW_STATE_DIAGNOSTIC)


sh_sand_cmd_t sh_dnxc_swstate_cmds[] = {
    {"adapter", NULL, sh_dnx_swstate_adapter_cmds, NULL, &dnx_swstate_adapter_man},
    {"multithread_analyzer", NULL, sh_dnx_swstate_multithread_analyzer_cmds, NULL, &dnx_swstate_multithread_analyzer_man},
    {"sw_state_external", NULL, sh_dnx_swstate_sw_state_external_cmds, NULL, &dnx_swstate_sw_state_external_man},
#if defined(BCM_DNX_SUPPORT) || defined(BCM_DNXF_SUPPORT)
    {"wb_engine", NULL, sh_dnx_swstate_wb_engine_cmds, NULL, &dnx_swstate_wb_engine_man},
#endif /* defined(BCM_DNX_SUPPORT) || defined(BCM_DNXF_SUPPORT)*/ 
    {"config", NULL, dnxc_swstate_config_cmds, NULL, &dnxc_swstate_config_man},
#if defined(DNX_SW_STATE_LOGGING)
    {"logger", NULL, dnxc_swstate_logging_cmds, NULL, &dnxc_swstate_logging_man},
#endif
    {"dump", sh_dnxc_swstate_dump_cmd, NULL, dnxc_swstate_dump_options, &dnxc_swstate_dump_man},
    {"size_get", sh_dnxc_swstate_size_get_cmd, NULL, dnxc_swstate_size_get_options, &dnxc_swstate_size_get_man},
    {NULL}
};


shr_error_e sh_dnxc_swstate_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control)
{

    SHR_FUNC_INIT_VARS(unit);

    sh_dnx_swstate_adapter_dump_cmd(unit, args, sand_control);
    sh_dnx_swstate_multithread_analyzer_dump_cmd(unit, args, sand_control);
    sh_dnx_swstate_sw_state_external_dump_cmd(unit, args, sand_control);
#if defined(BCM_DNX_SUPPORT) || defined(BCM_DNXF_SUPPORT)
    sh_dnx_swstate_wb_engine_dump_cmd(unit, args, sand_control);
#endif /* defined(BCM_DNX_SUPPORT) || defined(BCM_DNXF_SUPPORT)*/ 
    goto exit;
exit:
    SHR_FUNC_EXIT;
}



shr_error_e sh_dnxc_swstate_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control)
{

    SHR_FUNC_INIT_VARS(unit);

    cli_out("%-34s", "adapter: ");
    sh_dnx_swstate_adapter_size_get_cmd(unit, args, sand_control);
    cli_out("%-34s", "multithread_analyzer: ");
    sh_dnx_swstate_multithread_analyzer_size_get_cmd(unit, args, sand_control);
    cli_out("%-34s", "sw_state_external: ");
    sh_dnx_swstate_sw_state_external_size_get_cmd(unit, args, sand_control);
#if defined(BCM_DNX_SUPPORT) || defined(BCM_DNXF_SUPPORT)
    cli_out("%-34s", "wb_engine: ");
    sh_dnx_swstate_wb_engine_size_get_cmd(unit, args, sand_control);
#endif /* defined(BCM_DNX_SUPPORT) || defined(BCM_DNXF_SUPPORT)*/ 
    goto exit;
exit:
    SHR_FUNC_EXIT;
}



sh_sand_option_t dnxc_swstate_dump_options[] = {
    {"nocontent",      SAL_FIELD_TYPE_BOOL, "Decision if to perform content dump or to print the access tree.",  "false"},
    {"typefilter",     SAL_FIELD_TYPE_STR,  "Filter for the variable type.",         ""},
    {"namefilter",     SAL_FIELD_TYPE_STR,  "Filter for the variable name.",         ""},
    {NULL}
};


sh_sand_option_t dnxc_swstate_size_get_options[] = {
    {NULL}
};


sh_sand_man_t dnxc_swstate_dump_man = {
    "swstate dump",
    "print the swstate data",
    "swstate dump",
    "swstate dump nocontent=false typefilter="" namefilter="" ",
};


sh_sand_man_t dnxc_swstate_size_get_man = {
    "swstate size_get",
    "print the swstate modules sizes",
    "swstate size_get",
    "swstate size_get nocontent=false typefilter="" namefilter="" ",
};


sh_sand_man_t sh_dnxc_swstate_man = {
    cmd_dnxc_swstate_desc,
    NULL,
    NULL,
    NULL,
};


const char cmd_dnxc_swstate_desc[] = "swstate root";


#endif /* DNX_SW_STATE_DIAGNOSTIC */
#undef BSL_LOG_MODULE

/** \file diag_dnx_fabric.c
 * 
 * diagnostic pack for fabric
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_APPLDNX_FABRIC

/*
 * INCLUDE FILES:
 * {
 */
 /*
  * shared
  */
#include <shared/bsl.h>
#include <shared/utilex/utilex_integer_arithmetic.h>

/*appl*/
#include <appl/diag/diag.h>
#include <appl/diag/sand/diag_sand_framework.h>
#include <appl/diag/sand/diag_sand_prt.h>

/*dnx-data*/
#include <soc/dnx/dnx_data/auto_generated/dnx_data_fabric.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_device.h>

/*bcm*/
#include <bcm/fabric.h>
#include <bcm_int/dnx/fabric/fabric_if.h>
#include <bcm_int/dnx/init/init.h>

/*soc*/
#include <soc/dnxc/dnxc_defs.h>
#include <soc/dnxc/fabric.h>
/** allow drv.h include explicitly */
#ifdef _SOC_DRV_H
#undef _SOC_DRV_H
#endif
#include <soc/drv.h>
#include <soc/dnxc/drv_dnxc_utils.h>

/*sal*/
#include <sal/appl/sal.h>

/*
 * }
 */

 /*
  * LOCAL DEFINEs:
  * {
  */

#define DIAG_DNX_PORT_RANGE_STR_LENGTH      (SOC_MAX_NUM_PORTS + 3)

 /*
  * LOCAL DEFINEs:
  * }
  */

 /*
  * LOCAL TYPEs:
  * }
  */

 /*
  * LOCAL TYPEs:
  * }
  */

/*
 * LOCAL FUNCTIONs:
 * {
 */

/*
 * LOCAL FUNCTIONs:
 * }
 */

/*
 * LOCAL DIAG PACK:
 * {
 */

/*
 * Reachability
 */

/* *INDENT-OFF* */
sh_sand_man_t dnx_fabric_mesh_man = {
    .brief =    "Diagnostic for mesh mode",
    .compatibility = "Available in fabric mesh mode only"
};
/* *INDENT-ON* */

shr_error_e
sh_cmd_is_dnx_mesh(
    int unit,
    rhlist_t * test_list)
{
    SHR_FUNC_INIT_VARS(unit);

    if (SOC_IS_DNXF(unit))      /* DNXF - not supported */
    {
        SHR_SET_CURRENT_ERR(_SHR_E_UNIT);
    }
    else if (SOC_IS_DNX(unit))
    {
        char *connect_mode = soc_property_get_str(unit, "fabric_connect_mode");
        /** Should return success only if the mode is defined and is MESH. otherwise ERROR */
        if ((connect_mode == NULL)
            || sal_strncasecmp(connect_mode, "MESH", SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH))
        {
            SHR_SET_CURRENT_ERR(_SHR_E_NOT_FOUND);
        }
    }
    else
    {   /** Should not reach this choice - just in case - any other is just wrong unit */
        SHR_SET_CURRENT_ERR(_SHR_E_UNIT);
    }

    SHR_FUNC_EXIT;
}

shr_error_e
sh_cmd_is_dnx_clos(
    int unit,
    rhlist_t * test_list)
{
    SHR_FUNC_INIT_VARS(unit);

    if (SOC_IS_DNXF(unit))      /* DNXF - not supported */
    {
        SHR_SET_CURRENT_ERR(_SHR_E_UNIT);
    }
    else if (SOC_IS_DNX(unit))
    {
        char *connect_mode = soc_property_get_str(unit, "fabric_connect_mode");
        /** Should return success only if the mode is defined and is FE(clos) otherwise ERROR */
        if ((connect_mode == NULL) || sal_strncasecmp(connect_mode, "FE", SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH))
        {
            SHR_SET_CURRENT_ERR(_SHR_E_NOT_FOUND);
        }
    }
    else
    {   /** Should not reach this choice - just in case - any other is just wrong unit */
        SHR_SET_CURRENT_ERR(_SHR_E_UNIT);
    }

    SHR_FUNC_EXIT;
}

/**
 * \brief - display fabric mesh info
 */
shr_error_e
cmd_dnx_fabric_mesh(
    int unit,
    args_t * args,
    sh_sand_control_t * sand_control)
{
    int i, j, dest;
    char *mesh_type = NULL;
    int is_mesh_mc;
    int fap_id_group_count;
    soc_module_t *fap_id_group_array = NULL;
    int links_group_count;
    soc_module_t links_group_array[DNX_DATA_MAX_FABRIC_LINKS_NOF_LINKS];
    _shr_pbmp_t group_bmp, link_bmp;
    char range_format_buf[DIAG_DNX_PORT_RANGE_STR_LENGTH];
    int nof_dest = dnx_data_fabric.mesh.nof_dest_get(unit);
    int max_nof_fap_ids_per_device = dnx_data_device.general.max_nof_fap_ids_per_device_get(unit);
    PRT_INIT_VARS;
    SHR_FUNC_INIT_VARS(unit);

    SHR_ALLOC_SET_ZERO(fap_id_group_array, sizeof(soc_module_t) * max_nof_fap_ids_per_device, "fap_id_group_array",
                       "%s%s%s\r\n", EMPTY, EMPTY, EMPTY);

    is_mesh_mc = (dnx_data_fabric.mesh.multicast_enable_get(unit) == 1);
    mesh_type = is_mesh_mc ? "Mesh_MC" : "Mesh";

    /*
     * Print mesh diag topic
     */
    LOG_CLI(("MESH DIAG\n"));

    /*
     * Print fabric mesh table
     */
    PRT_TITLE_SET("Fabric Mesh Type: %s", mesh_type);
    PRT_COLUMN_ADD("Group Dest");
    PRT_COLUMN_ADD("FAP IDs");
    PRT_COLUMN_ADD("Links");

    for (i = 0; i < nof_dest; ++i)
    {
        int group_id = i;

        PRT_ROW_ADD(PRT_ROW_SEP_NONE);
        PRT_CELL_SET("%d", group_id);
        dest = BCM_FABRIC_GROUP_MODID_SET(group_id);
        SHR_IF_ERR_EXIT(bcm_fabric_modid_group_get(unit, dest,
                                                   dnx_data_device.general.max_nof_fap_ids_per_device_get(unit),
                                                   fap_id_group_array, &fap_id_group_count));
        SHR_IF_ERR_EXIT(bcm_fabric_link_topology_get(unit, dest,
                                                     DNX_DATA_MAX_FABRIC_LINKS_NOF_LINKS,
                                                     &links_group_count, links_group_array));

        _SHR_PBMP_CLEAR(group_bmp);
        _SHR_PBMP_CLEAR(link_bmp);
        if (fap_id_group_count)
        {
            for (j = 0; j < fap_id_group_count; ++j)
            {
                _SHR_PBMP_PORT_ADD(group_bmp, fap_id_group_array[j]);
            }
            shr_pbmp_range_format(group_bmp, range_format_buf, DIAG_DNX_PORT_RANGE_STR_LENGTH);
            PRT_CELL_SET("%s", range_format_buf);
        }
        else
        {
            PRT_CELL_SET("-");
        }
        if (links_group_count)
        {
            for (j = 0; j < links_group_count; ++j)
            {
                _SHR_PBMP_PORT_ADD(link_bmp, links_group_array[j]);
            }
            shr_pbmp_range_format(link_bmp, range_format_buf, DIAG_DNX_PORT_RANGE_STR_LENGTH);
            PRT_CELL_SET("%s", range_format_buf);
        }
        else
        {
            PRT_CELL_SET("-");
        }
    }

    PRT_COMMITX;
exit:
    SHR_FREE(fap_id_group_array);
    PRT_FREE;
    SHR_FUNC_EXIT;
}

/* *INDENT-OFF* */
/* Link the values in the two enums*/
sh_sand_enum_t dnx_fabric_force_enum_table[] = {
    {"FABRIC",  DNX_FABRIC_FORCE_FABRIC,    "Force Fabric"},
    {"LOCAL",    DNX_FABRIC_FORCE_LOCAL,    "Force Local Core (need to specify core ID)"},
    {"DEFAULT", DNX_FABRIC_FORCE_RESTORE,   "Restore default"},
    {NULL}
};

static sh_sand_enum_t dnx_fabric_force_core[] = {
    { /** No need to define value if plugin_str was defined */
     .string = "max",
     .desc = "Number of device cores",
     .value = 0,
     .plugin_str = "DNX_DATA.device.general.nof_cores-1"},
    {NULL}
};

sh_sand_man_t dnx_fabric_force_man = {
    .brief    = "Diagnostic for fabric force.",
    .full     = "Map packets with all destination IDs to fabric/local core 0/local core 1.\n"
                "Not to be done when traffic is enabled.\n"
                "To disable traffic, use bcm_stk_module_enable and bcm_fabric_control_set with bcmFabricControlCellsEnable parameter.",
    .synopsis = "<fabric/local/default> [core=<core_id>]",
    .examples = "fabric\n"
                "local core=0\n"
                "default",
    .compatibility = "Available in fabric FE(clos) mode only"
};
sh_sand_option_t dnx_fabric_force_options[] = {
/* Option name   Option Type             Description    Default    Option Extension                        Valid Range     Flags*/
    {"type",    SAL_FIELD_TYPE_ENUM,   "force type",   "fabric",   (void *)dnx_fabric_force_enum_table,    NULL,           SH_SAND_ARG_FREE},
    {"core",    SAL_FIELD_TYPE_INT32,  "core ID",      "-1",       (void *)dnx_fabric_force_core,          "0-max",        },
    {NULL}
};

/* *INDENT-ON* */

/**
 * \brief - fabric force command
 */
shr_error_e
cmd_dnx_fabric_force(
    int unit,
    args_t * args,
    sh_sand_control_t * sand_control)
{
    int force, core_id;
    SHR_FUNC_INIT_VARS(unit);

    SH_SAND_GET_ENUM("type", force);
    SH_SAND_GET_INT32("core", core_id);

    if (core_id == -1)
    {
        core_id = DNX_FABRIC_FORCE_CORE_ALL_CORES;
    }

    if ((force != DNX_FABRIC_FORCE_LOCAL) && (core_id != DNX_FABRIC_FORCE_CORE_ALL_CORES))
    {
        SHR_CLI_EXIT(_SHR_E_PARAM, "Option CORE can be provided only together with the LOCAL option!\n");
    }

    if ((force == DNX_FABRIC_FORCE_LOCAL) && (core_id == DNX_FABRIC_FORCE_CORE_ALL_CORES))
    {
        SHR_CLI_EXIT(_SHR_E_PARAM, "Option CORE must be provided when using the LOCAL option!\n");
    }

    switch (force)
    {
        case DNX_FABRIC_FORCE_LOCAL:
            SHR_IF_ERR_EXIT(dnx_force_traffic_fabric(unit, FALSE));
            SHR_IF_ERR_EXIT(dnx_force_traffic_local(unit, core_id));
            break;
        case DNX_FABRIC_FORCE_FABRIC:
            SHR_IF_ERR_EXIT(dnx_force_traffic_local(unit, DNX_FABRIC_FORCE_CORE_ALL_CORES));
            SHR_IF_ERR_EXIT(dnx_force_traffic_fabric(unit, TRUE));
            break;
        case DNX_FABRIC_FORCE_RESTORE:
            SHR_IF_ERR_EXIT(dnx_force_traffic_local(unit, DNX_FABRIC_FORCE_CORE_ALL_CORES));
            SHR_IF_ERR_EXIT(dnx_force_traffic_fabric(unit, FALSE));
            break;
        default:
            SHR_CLI_EXIT(_SHR_E_PARAM, "Illegal option!\n");
            break;
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Check if fabric is available in the device
 */
shr_error_e
sh_cmd_is_fabric_available(
    int unit,
    rhlist_t * test_list)
{
    SHR_FUNC_INIT_VARS(unit);

    if (SOC_IS_DNX(unit))
    {
        /** Not supported for devices without fabric */
        if (!dnx_data_fabric.links.nof_links_get(unit))
        {
            SHR_SET_CURRENT_ERR(_SHR_E_UNIT);
        }
    }

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Check if device is from DNX family and fabric is available in the device
 */
shr_error_e
sh_cmd_is_dnx_with_fabric_available(
    int unit,
    rhlist_t * test_list)
{
    int rv = _SHR_E_NONE;
    SHR_FUNC_INIT_VARS(unit);

    if (!SOC_IS_DNX(unit))
    {
        SHR_SET_CURRENT_ERR(_SHR_E_UNIT);
    }

    rv = sh_cmd_is_fabric_available(unit, test_list);
    if (rv != _SHR_E_NONE)
    {
        SHR_SET_CURRENT_ERR(_SHR_E_UNIT);
    }

    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Check if device is from DNX family and fabric is NOT available in the device
 */
shr_error_e
sh_cmd_is_dnx_with_fabric_unvailable(
    int unit,
    rhlist_t * test_list)
{
    int rv = _SHR_E_NONE;
    SHR_FUNC_INIT_VARS(unit);

    if (!SOC_IS_DNX(unit))
    {
        SHR_SET_CURRENT_ERR(_SHR_E_UNIT);
    }

    rv = sh_cmd_is_fabric_available(unit, test_list);

    if (rv == _SHR_E_NONE)
    {
        SHR_SET_CURRENT_ERR(_SHR_E_UNIT);
    }

    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Check if device is from DNX family and fabric adaptive shaper is NOT available in the device
 */
static shr_error_e
sh_cmd_is_dnx_with_fabric_cgm_adaptive_shaper_unvailable(
    int unit,
    rhlist_t * test_list)
{
    SHR_FUNC_INIT_VARS(unit);


    if (!dnx_data_fabric.cgm.feature_get(unit, dnx_data_fabric_cgm_is_adaptive_mnol_shaper_supported) &&
        !dnx_data_fabric.cgm.feature_get(unit, dnx_data_fabric_cgm_is_adaptive_tfl_shaper_supported))
    {
        SHR_SET_CURRENT_ERR(_SHR_E_NOT_FOUND);
    }

    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Check if device is has limited ability to desplay adaptive shaper watermark values
 */
static shr_error_e
sh_cmd_is_dnx_with_fabric_cgm_adaptive_shaper_limited_watermarks_unavailable(
    int unit,
    rhlist_t * test_list)
{
    SHR_FUNC_INIT_VARS(unit);


    if (!dnx_data_fabric.cgm.feature_get(unit, dnx_data_fabric_cgm_is_adaptive_shaper_watermarks_limited))
    {
        SHR_SET_CURRENT_ERR(_SHR_E_UNIT);
    }

    SHR_FUNC_EXIT;
}

/**
 * \brief
 *   Check if device is from DNX family and fabric adaptive shaper is NOT available in the device
 */
static shr_error_e
sh_cmd_is_dnx_with_fabric_cgm_adaptive_shaper_regular_watermarks_unavailable(
    int unit,
    rhlist_t * test_list)
{
    SHR_FUNC_INIT_VARS(unit);


    if (dnx_data_fabric.cgm.feature_get(unit, dnx_data_fabric_cgm_is_adaptive_shaper_watermarks_limited))
    {
        SHR_SET_CURRENT_ERR(_SHR_E_UNIT);
    }

    SHR_FUNC_EXIT;
}

/**
 * \brief - display adaptive shaper status
 */
static shr_error_e
sh_dnx_fabric_cgm_adaptive_shaper_status(
    int unit,
    args_t * args,
    sh_sand_control_t * sand_control,
    int is_limited_watermarks)
{
    uint32 min_watermark_a, min_watermark_b;
    uint32 max_watermark_a, max_watermark_b;
    uint32 is_tfl_enabled, is_mnol_enabled;
    int adaptive_shaper_factor_bits_nof;
    int max_supported_value;

    PRT_INIT_VARS;
    SHR_FUNC_INIT_VARS(unit);

    PRT_TITLE_SET("Watermarks");

    PRT_COLUMN_ADD_FLEX(PRT_FLEX_ASCII, "Indication");
    PRT_COLUMN_ADD_FLEX(PRT_FLEX_ASCII, "TFL");
    PRT_COLUMN_ADD_FLEX(PRT_FLEX_ASCII, "MNOL");

    SHR_IF_ERR_EXIT(dnx_fabric_cgm_control_adaptive_watermark_factor_get(unit,
                                                                         DBAL_TABLE_FABRIC_CGM_ADAPTIVE_SHAPER_TFL_CONTROL,
                                                                         &is_tfl_enabled, &min_watermark_a,
                                                                         &max_watermark_a));

    SHR_IF_ERR_EXIT(dnx_fabric_cgm_control_adaptive_watermark_factor_get(unit,
                                                                         DBAL_TABLE_FABRIC_CGM_ADAPTIVE_SHAPER_MNOL_CONTROL,
                                                                         &is_mnol_enabled, &min_watermark_b,
                                                                         &max_watermark_b));

    /** if is_limited_watermarks, Values above 100.1% should not be trusted */
    adaptive_shaper_factor_bits_nof = dnx_data_fabric.dbal.adaptive_shaper_factor_bits_nof_get(unit);
    if (is_limited_watermarks)
    {
        adaptive_shaper_factor_bits_nof -= 1;
    }
    max_supported_value = UTILEX_BIT(adaptive_shaper_factor_bits_nof);

    PRT_ROW_ADD(PRT_ROW_SEP_NONE);
    PRT_CELL_SET("%s", "min_watermark");
    if (is_tfl_enabled)
    {
        if (min_watermark_a > max_supported_value)
        {
            PRT_CELL_SET("%s", "Invalid");
        }
        else
        {
            PRT_CELL_SET("%d", min_watermark_a);
        }
    }
    else
    {
        PRT_CELL_SET("%s", "Disabled");
    }
    if (is_mnol_enabled)
    {
        if (min_watermark_b > max_supported_value)
        {
            PRT_CELL_SET("%s", "Invalid");
        }
        else
        {
            PRT_CELL_SET("%d", min_watermark_b);
        }
    }
    else
    {
        PRT_CELL_SET("%s", "Disabled");
    }

    PRT_ROW_ADD(PRT_ROW_SEP_NONE);
    PRT_CELL_SET("%s", "max_watermark");

    if (is_tfl_enabled)
    {
        if (max_watermark_a > max_supported_value)
        {
            PRT_CELL_SET("%s", "Invalid");
        }
        else
        {
            PRT_CELL_SET("%d", max_watermark_a);
        }
    }
    else
    {
        PRT_CELL_SET("%s", "Disabled");
    }
    if (is_mnol_enabled)
    {
        if (max_watermark_b > max_supported_value)
        {
            PRT_CELL_SET("%s", "Invalid");
        }
        else
        {
            PRT_CELL_SET("%d", max_watermark_b);
        }
    }
    else
    {
        PRT_CELL_SET("%s", "Disabled");
    }

    PRT_COMMITX;
exit:
    PRT_FREE;
    SHR_FUNC_EXIT;
}

/**
 * \brief - display adaptive shaper status
 */
static shr_error_e
sh_dnx_fabric_cgm_adaptive_shaper_status_limited_watermarks(
    int unit,
    args_t * args,
    sh_sand_control_t * sand_control)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(sh_dnx_fabric_cgm_adaptive_shaper_status(unit, args, sand_control, 1));
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - display adaptive shaper status
 */
static shr_error_e
sh_dnx_fabric_cgm_adaptive_shaper_status_regular_watermarks(
    int unit,
    args_t * args,
    sh_sand_control_t * sand_control)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(sh_dnx_fabric_cgm_adaptive_shaper_status(unit, args, sand_control, 0));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
sh_cmd_is_dnx_cgm(
    int unit,
    rhlist_t * test_list)
{
    SHR_FUNC_INIT_VARS(unit);

    if (SOC_IS_DNXF(unit))      /* DNXF - not supported */
    {
        SHR_SET_CURRENT_ERR(_SHR_E_UNIT);
    }
    else if (SOC_IS_DNX(unit))
    {
        if (sh_cmd_is_fabric_available(unit, test_list) != _SHR_E_NONE)
        {
            SHR_SET_CURRENT_ERR(_SHR_E_NOT_FOUND);
            SHR_EXIT();
        }

        if (!dnx_data_fabric.general.feature_get(unit, dnx_data_fabric_general_blocks_exist))
        {
            SHR_SET_CURRENT_ERR(_SHR_E_NOT_FOUND);
        }
    }
    else
    {   /** Should not reach this choice - just in case - any other is just wrong unit */
        SHR_SET_CURRENT_ERR(_SHR_E_UNIT);
    }

exit:
    SHR_FUNC_EXIT;
}


/* *INDENT-OFF* */
static sh_sand_man_t sh_dnx_fabric_cgm_adaptive_shaper_status_man = {
    .brief = "display adaptive shaper status",
};

static sh_sand_man_t sh_dnx_fabric_cgm_adaptive_shaper_status_limited_watermarks_man = {
    .brief = "display adaptive shaper status",
    .full = "display adaptive shaper status\n"
            "Watermark values above 1024 (100.1%) will not be displayed since they cannot be trusted to be accurate."
};

static sh_sand_man_t sh_dnx_fabric_cgm_adaptive_shaper_man = {
    .brief = "display fabric cgm adaptive shaper diagnostics and configuration",
};

static sh_sand_cmd_t sh_dnx_fabric_cgm_adaptive_shaper_cmds[] = {
    /*keyword, action,                                                      command, options,   man                                                                 Flags   Presence Callback*/
    {"status", sh_dnx_fabric_cgm_adaptive_shaper_status_regular_watermarks, NULL,    NULL,      &sh_dnx_fabric_cgm_adaptive_shaper_status_man,                      NULL,   NULL, SH_CMD_CONDITIONAL * SH_CMD_NO_XML_VERIFY, sh_cmd_is_dnx_with_fabric_cgm_adaptive_shaper_regular_watermarks_unavailable},
    {"status", sh_dnx_fabric_cgm_adaptive_shaper_status_limited_watermarks, NULL,    NULL,      &sh_dnx_fabric_cgm_adaptive_shaper_status_limited_watermarks_man,   NULL,   NULL, SH_CMD_CONDITIONAL * SH_CMD_NO_XML_VERIFY, sh_cmd_is_dnx_with_fabric_cgm_adaptive_shaper_limited_watermarks_unavailable},
    {NULL}
};

sh_sand_man_t dnx_fabric_cgm_man = {
    .brief =    "display fabric cgm related diagnostics",
};

sh_sand_cmd_t sh_dnx_fabric_cgm_cmds[] = {
    /*keyword,            action,                                   command,   options,                                man                                     gs               Presence Callback*/
    {"adaptive_shaper",   NULL,         sh_dnx_fabric_cgm_adaptive_shaper_cmds, NULL,    &sh_dnx_fabric_cgm_adaptive_shaper_man, NULL, NULL, SH_CMD_CONDITIONAL, sh_cmd_is_dnx_with_fabric_cgm_adaptive_shaper_unvailable},
    {NULL}
};
/* *INDENT-ON* */

/*
 * }
 */
